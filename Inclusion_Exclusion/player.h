#pragma once
#include <string>
#include <set>
#include <vector>
#include <iostream>
#include "sets.h"

class player {
public: 
	std::string name;
	int health;
	std::string status;
	std::string msg;
	int confidence;

	void createPlayer(const std::string& playerName, int confidence) {
		name = playerName;
		health = 100;
		this->confidence = confidence;
		status = R"(===================
||               |
||               0
||              \|/
||               |
||              / \
||
||
||
||
==========)";


	}
	void displayStatus() const {
		std::cout << "Player: " << name << "\n";
		std::cout << "Health: " << health << "\n";
		std::cout << msg << "\n";
		std::cout << status << "\n";
	}
	void takeDamage(int damage) {
		health -= damage;
		if (health <= 0) {
			health = 0;
			msg = "Well looks like you weren't as confident as you assumed were you?";
			status = R"(
===================
||				 |
||				 
||			    
||			    
||				
||
||
||
||
||               0--
==========
)";
		} else if (health <= 30) {
			msg = "Looks like you're out of chances";
			status = R"(
===================
||               |
||               0
||               |
||               |
||              
||
||
||
||
||
==========
)";
		} else if(health <= 50) {
			msg = "Not a lot left to lose";
			status = R"(
===================
||               |
||               0
||              \|
||               |
||              
||
||
||
||
||
==========
)";
		}
		else if (health <= 70) {
			msg = "Not bad, but you can do better!";
			status = R"(
===================
||               |
||               0
||              \|/
||               |
||              
||
||
||
||
||
==========
)";
		}
		else if (health <= 80) {
			msg = "Guess we'll just have to take a peice to help you remember";
			status = R"(
===================
||               |
||               0
||              \|/
||               |
||              / 
||
||
||
||
||
==========
)";
		}
	}
};