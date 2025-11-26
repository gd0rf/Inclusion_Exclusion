#include "sets.h"
#include "player.h"
#include "game.h"
#pragma once

class questions {
public:
	static int questionsAsked;
	static void askUnionQuestion(Game& game);
	static void askIntersectionQuestion(Game& game);
	static void askDifferenceQuestion(Game& game);
	static void askOntoQuestion(Game& game);
	static int nCr(int n, int r); // thank you https://www.geeksforgeeks.org/dsa/program-calculate-value-ncr/#google_vignette
	static int factorial(int n);
	static int derangements(int n);
	static void askDerangementQuestion(Game& game);

};