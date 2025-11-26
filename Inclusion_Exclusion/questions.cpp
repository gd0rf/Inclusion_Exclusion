#include "player.h"
#include "sets.h"
#include "game.h"
#include "questions.h"
#include <iostream>
#include <sstream>
#include <set>
#include <vector>

std::set<int> getPlayerSet();
int questions::questionsAsked = 0;

void questions::askUnionQuestion(Game& game) {
	if (questionsAsked < 3) {
		std::cout << "What is the size of the union of Set A and Set B? ";
		int userAnswer;
		std::cin >> userAnswer;
		std::set<int> unionSet = game.setA.getUnion(game.setB);
		if (userAnswer == static_cast<int>(unionSet.size())) {
			std::cout << "Correct! Well done.\n";
			game.currentPlayer.confidence += 5;
		}
		else {
			std::cout << "Incorrect. The correct answer was " << unionSet.size() << ".\n";
			game.currentPlayer.takeDamage(10);
			game.currentPlayer.confidence -= 5;
		}
	}
	else {
		std::cout << "What is the set for the union of Set A and Set B? \n";
		std::cout << "Enter the elements separated by spaces: \n";
		std::set<int> unionSet = game.setA.getUnion(game.setB);
		
		std::set<int> inputSet = getPlayerSet();
		if(unionSet == inputSet) {
			std::cout << "Correct, that's a suprise.\n";
			game.currentPlayer.confidence += 5;
		} else {
			std::cout << "Sorry, that's not even close! The correct answer was: ";
			for (const auto& elem : unionSet) {
				std::cout << elem << " ";
			}
			std::cout << std::endl;
			game.currentPlayer.takeDamage(10);
			game.currentPlayer.confidence -= 5;
		}

	}

	questionsAsked++;
}

void questions::askIntersectionQuestion(Game& game) {
	if (questionsAsked < 3) {
		std::cout << "What is the size of the intersection of Set A and Set B? ";
		int userAnswer;
		std::cin >> userAnswer;
		std::set<int> intersectionSet = game.setA.getIntersection(game.setB);
		if (userAnswer == static_cast<int>(intersectionSet.size())) {
			std::cout << "Correct! Well done.\n";
			game.currentPlayer.confidence += 5;
		}
		else {
			std::cout << "Incorrect. The correct answer was " << intersectionSet.size() << ".\n";
			game.currentPlayer.takeDamage(10);
			game.currentPlayer.confidence -= 5;

		}
	}
	else{

		std::cout << "What is the set for the intersection of Set A and Set B? \n";
		std::cout << "Enter the elements separated by spaces: \n";
		std::set<int> intersectionSet = game.setA.getIntersection(game.setB);
		
		std::set<int> inputSet = getPlayerSet();
		if(intersectionSet == inputSet) {
			std::cout << "Correct, that's a suprise.\n";
			game.currentPlayer.confidence += 5;
		} else {
			std::cout << "Sorry, that's not even close! The correct answer was: ";
			for (const auto& elem : intersectionSet) {
				std::cout << elem << " ";
			}
			std::cout << std::endl;
			game.currentPlayer.takeDamage(10);
			game.currentPlayer.confidence -= 5;

		}
	}


	questionsAsked++;
}

void questions::askDifferenceQuestion(Game& game)
{
	if (questionsAsked < 3) {
		std::cout << "What is the size of the difference of Set A minus Set B (A - B)? ";
		int userAnswer;
		std::cin >> userAnswer;

		std::set<int> differenceSet;
		for (const auto& elem : game.setA.elements) {
			if (game.setB.elements.count(elem) == 0) {
				differenceSet.insert(elem);
			}
		}

		if (userAnswer == static_cast<int>(differenceSet.size())) {
			std::cout << "Correct! Well done.\n";
			game.currentPlayer.confidence += 5;
		}
		else {
			std::cout << "Incorrect. The correct answer was " << differenceSet.size() << ".\n";
			game.currentPlayer.takeDamage(10);
			game.currentPlayer.confidence -= 5;
		}
	}
	else {
		std::cout << "What are the elements of the difference Set A - Set B?\n";
		std::cout << "Enter the elements separated by spaces: \n";

		std::set<int> differenceSet;
		for (const auto& elem : game.setA.elements) {
			if (game.setB.elements.count(elem) == 0) {
				differenceSet.insert(elem);
			}
		}

		std::set<int> inputSet = getPlayerSet();
		if (differenceSet == inputSet) {
			std::cout << "Correct, that's a surprise.\n";
			game.currentPlayer.confidence += 5;
		}
		else {
			std::cout << "Sorry, that's not correct. The correct answer was: ";
			for (const auto& elem : differenceSet) {
				std::cout << elem << " ";
			}
			std::cout << std::endl;
			game.currentPlayer.takeDamage(10);
			game.currentPlayer.confidence -= 5;
		}
	}

	questionsAsked++;
}

int questions::nCr(int n, int r) {

	double sum = 1;

	// Calculate the value of n choose
	// r using the binomial coefficient formula
	for (int i = 1; i <= r; i++) {

		sum = sum * (n - r + i) / i;
	}
	return (int)sum;
}

int questions::factorial(int n) {
	int result = 1;
	for (int i = 2; i <= n; ++i) result *= i;
	return result;
}

int questions::derangements(int n) {
	if (n == 0) return 1;
	if (n == 1) return 0;
	int result = 0;
	for (int k = 0; k <= n; ++k) {
		int term = nCr(n, k) * factorial(n - k);
		if (k % 2 == 0)
			result += term;
		else
			result -= term;
	}
	return result;
}

void questions::askDerangementQuestion(Game& game) {
	int n = static_cast<int>(game.setA.elements.size());
	std::cout << "How many derangements (permutations with no element in its original position) ";
	std::cout << "are there for Set A with " << n << " elements?\n";

	int userAnswer;
	std::cin >> userAnswer;

	int correctAnswer = derangements(n);

	if (userAnswer == correctAnswer) {
		std::cout << "Correct! Well done.\n";
		game.currentPlayer.confidence += 5;
	}
	else {
		std::cout << "Incorrect. The correct answer was " << correctAnswer << ".\n";
		game.currentPlayer.takeDamage(10);
		game.currentPlayer.confidence -= 5;
	}

	questionsAsked++;
}

void questions::askOntoQuestion(Game& game) {
	// Placeholder for future implementation
	std::cout << "How many onto functions can be formed from Set A to the first 3 elements of Set B?\n";
	std::cout << "Set A: ";
	game.setA.displaySet();
	int count = 0;
	int countToShow;
	if (questionsAsked < 3) {
		countToShow = 1 + (rand() % 3);  
	}
	else {
		countToShow = 3 + (rand() % 5);
	}
	std::cout << "\nFirst " + countToShow;
	std::cout << " elements of Set B: ";
	std::set<int> firstX;
	for (const auto& elem : game.setB.elements) {
		std::cout << elem << " ";
		firstX.insert(elem);
		count++;
		if (count == countToShow) break;
	}
	std::cout << std::endl;
	int power = static_cast<int>(game.setA.elements.size());
	int total =  firstX.size()^ (static_cast<int>(game.setA.elements.size()));
	std::vector<int> jValues;
	for (int i = 1; i < firstX.size() + 1; i++) {
				int j = nCr(firstX.size(), i) * (firstX.size() - i) ^ power;
				if (i % 2 == 0) {
					j = -j;
				}
				jValues.push_back(j);
	}
	int sum = 0;
	for(int i =0; i < jValues.size(); i++) {
		sum += jValues[i];
	}
	int ontoFunctions = total + sum;

	std::cout << "Enter your answer: ";
	int userAnswer;
	std::cin >> userAnswer;
	if (userAnswer == ontoFunctions) {
		std::cout << "Correct! Well done.\n";
		game.currentPlayer.confidence += 5;
	}
	else {
		std::cout << "Incorrect. The correct answer was " << ontoFunctions << ".\n";
		game.currentPlayer.takeDamage(10);
		game.currentPlayer.confidence -= 5;
	}

	questionsAsked++;
}

std::set<int> getPlayerSet() {
	std::set<int> mySet;
	std::string line;
	std::getline(std::cin, line);

	std::stringstream ss(line); 
	int num;

	while (ss >> num) {
		mySet.insert(num);
	}

	return mySet;
}