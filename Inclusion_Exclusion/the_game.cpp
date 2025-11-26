#include <iostream>
#include <string>
#include <cstring>
#include <thread>
#include <atomic>
#include <functional>
#include "sets.h"
#include "player.h"
#include "game.h"
#include "questions.h"

Game* game;

void intializeGame();

void the_game() {
    game = new Game();
    intializeGame();
    int totalQuestions = 10;
    int question1PerType = totalQuestions / 4;
    std::cout << "\n\n\n\nBe careful how you answer the questions, you might just lose a leg!\n";
    std::cout << "\nHere's your current status:\n";
    game->currentPlayer.displayStatus();
    std::cout << "\n\nYou must complete a totale of 10 questions but you cannot exceed more then 3 questions on two topics and 2 questions on the remaining two topics.\n";
    std::cout << "For every question you get correct the chance of a larger set increases and the questions become more difficult.\n";
    for (int i = 0; i < totalQuestions; i++) {


        std::cout << "You have a set of " << game->setA.getSize() << " " << game->setA.getTopicString() << " " << game->setA.getGroupTypeString();
        std::cout << " and you have a set of " << game->setB.getSize() << " " << game->setB.getTopicString() << " " << game->setB.getGroupTypeString() << "indicated by numbers" << std::endl;

        std::cout << "Set A: ";
        game->setA.displaySet();
        std::cout << "\nSet B: ";
        game->setB.displaySet();
        std::cout << std::endl;
        std::cout << "Question " << (i + 1) << ":\n";
        std::cout << "Choose a question type:\n";
        std::cout << "[1] Union\n";
        std::cout << "[2] Intersection\n";
        std::cout << "[3] Difference\n";
        std::cout << "[4] Onto Functions\n";
        char choice;
        std::cin >> choice;
        switch (choice) {
        case '1':
            questions::askUnionQuestion(*game);
            break;
        case '2':
            questions::askIntersectionQuestion(*game);
            break;
        case '3':
            questions::askDifferenceQuestion(*game);
            break;
        case '4':
            questions::askOntoQuestion(*game);
            break;
        default:
            std::cout << "Invalid choice, skipping question.\n";
            i--; // don't count invalid choice as a question
            continue;
        };
        std::cout << "\nYour current status:\n";
        game->currentPlayer.displayStatus();
        if (game->currentPlayer.health <= 0) {
            break;

        }

        if(game->currentPlayer.confidence < 0) {
            game->currentPlayer.confidence = 0;
		}

    }

    if (game->currentPlayer.health == 100) {

    }else if(game->currentPlayer.health >= 70) {
        std::cout << "Well done, you survived with most of your limbs intact!\n";
    }
    else if (game->currentPlayer.health >= 40) {
        std::cout << "You made it through, but just barely. Better luck next time!\n";
    }
    else if(game->currentPlayer.health >= 10){
        std::cout << "You survived, but at what cost? Reflect on your confidence and try again.\n";
    }
    else {
		std::cout << "You didn't make it this time. Perhaps reconsider your confidence before playing again.\n";
    }
	delete game;
}

void intializeGame() {
    std::cout << "Looks like you want to play. No going back now!\n";
    std::cout << "We're friends aren't we? You can call me Jigsaw. What's your name?\n";
    std::string playerName;
    std::cin >> playerName;
    std::cout << "Hello " << playerName << ". Let's begin.\n";

    int confidence;
    std::cout << "How confident are you feeling today? (0-50): ";
    std::cin >> confidence;
    while (confidence < 0 || confidence > 50) {
        std::cout << "Come on now, be honest. Pick a number between 0 and 50: ";
        std::cin >> confidence;
    }
    std::cout << "Confidence set to " << confidence << ".\n";

    game->currentPlayer.createPlayer(playerName, confidence);
    std::cout << "Well well well, let's put that to the test shall we?\n";


    // Seed once at start
    srand(static_cast<unsigned int>(time(0)));

    int lowerBound = 1;
    int upperBound = 50;

    // Decide randomly if A/B will be students or teachers
    int groups = rand() % 2;

    if (groups == 0) {
        game->setA.createSetWithOptionalOverlap("Set A", lowerBound, upperBound, confidence, GroupType::Students);
        game->setB.createSetWithOptionalOverlap("Set B", lowerBound, upperBound, confidence, GroupType::Students, &game->setA, 0.9);
    }
    else {
        game->setA.createSetWithOptionalOverlap("Set A", lowerBound, upperBound, confidence, GroupType::Teachers);
        game->setB.createSetWithOptionalOverlap("Set B", lowerBound, upperBound, confidence, GroupType::Students, &game->setA, 0.9);
    }
}
