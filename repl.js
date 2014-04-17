var arDrone = require('ar-drone');
var spawn = require("child_process").spawn;

var client  = arDrone.createClient();
client.createRepl();
