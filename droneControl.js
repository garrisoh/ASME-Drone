var ardrone = require('ar-drone');
var leap = require('leapjs');

var drone = ardrone.createClient();

// clamps a value between -1.0 and 1.0
function clamp(value) {
	return (value < -1.0) ? -1.0 : (value > 1.0) ? 1.0 : value
}

// keyboard stuff
process.stdin.setEncoding('utf8');

var isFlying = false;

process.stdin.on('readable', function(chunk) {
	var chunk = process.stdin.read();

	if (chunk === null) {
		return;
	}

	// takeoff/landing logic
	if (chunk === '\n' && !isFlying) {
		isFlying = true;
		console.log("Prepare for takeoff...");
		drone.ftrim();
		drone.takeoff();
	} else if (chunk === '\n' && isFlying) {
		isFlying = false;
		console.log("Begin landing sequence...");
		drone.land();
	}
});

var calibrated = false;
var verticalCenter = 0.0;

// leap listener loops on each frame
leap.loop(function (frame) {

	if (!isFlying) {
		return;
	}

	// check that there are hands
	if (!(frame.hands.length > 0)) {
		calibrated = false;
		drone.stop();
		return;
	}

	// weird thing to note, hands is in the order of entry into the field
	// ie, the first hand entered is index 0 (regardless of left/right)
	if (!(frame.hands[0].fingers.length > 2)) {
		calibrated = false;
		drone.stop();
		return;
	}

	var palmPos = frame.hands[0].palmPosition;

	// normalize position
	var box = frame.interactionBox;
	var normalizedPos = box.normalizePoint(palmPos, false);

	// calibrate, with -1.0 as smallest and 1.0 as largest
	if (!calibrated) {
		verticalCenter = (normalizedPos[1] - 0.5) * 2.0;
        	calibrated = true;
	}

	// get vertical speed based on center point
	var vertSpeed = (normalizedPos[1] - 0.5) * 2.0 - verticalCenter;

	//console.log('Pitch: ' + clamp(-1.0 * frame.hands[0].pitch()) + ' Roll: ' + clamp(-1.0 * frame.hands[0].roll()) + ' Speed: ' + clamp(vertSpeed));

	// drone stuff
	if (frame.hands[0].pitch() > 0.0) {
		drone.back(clamp(frame.hands[0].pitch()));
	} else {
		drone.front(clamp(frame.hands[0].pitch() * -1.0));
	}

	if (frame.hands[0].roll() > 0.0) {
		drone.left(clamp(frame.hands[0].roll()));
	} else {
		drone.right(clamp(frame.hands[0].roll() * -1.0));
	}

	if (vertSpeed > 0.0) {
		drone.up(clamp(vertSpeed));
	} else {
		drone.down(clamp(vertSpeed * -1.0));
	}

	/*if (frame.hands.length > 1) {
		if (leftmost(frame.hands).yaw() > 0.0) {
			drone.clockwise(clamp(leftmost(frame.hands).yaw()));
		} else {
			drone.counterClockwise(clamp(leftmost(frame.hands).yaw()) * -1.0);
		}
	}*/
});

function leftmost(handList) {
	var leftmost = 0;
	for (var i=0; i < handList.length; i++) {
		if (handList[i].x < handList[leftmost].x) {
			leftmost = i;
		}
	}
	
	return handList[leftmost];
}

console.log('Press enter/return to toggle takeoff/landing sequence');
