//
//  KeyboardListener.cpp
//  KeyListener
//
//  Created by Greg Flynn on 18/04/2014.
//  Copyright (c) 2014 Greg Flynn. All rights reserved.
//

#include <iostream>
#include <SFML/Window/Keyboard.hpp>
#include "drone.h"


bool emergency = false;
bool flying = false;

int main(){
    
    while(true){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
            // take off and landing key
            if(emergency){
                std::cout<<"Emergency in progress \nuse r to reset";
            }
            else if(!flying){
                std::cout<<"Taking off";
                getDrone()->takeoff();
                flying = true;
            }
            else{
                std::cout<<"Landing";
                getDrone()->land()
                flying = false;

                }
            }
        while(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
            continue;
            
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            // take off and landing key
            if(!emergency){
                std::cout<<"\nMayday";
                emergency = true;
                flying = false;
                getDrone->emergencyStop();
            }

        }
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
            // stop emergencies
            if(emergency){
            std::cout<<"\nCancel Mayday";
            emergency = false;
                getDrone->resetEmergencyStop();
            }
        }
        
    }
    
    return 0;
}

