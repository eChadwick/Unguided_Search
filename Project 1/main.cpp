//
//  main.cpp
//  Project 1
//
//  Created by Chadwick,Eric on 1/25/18.
//  Copyright © 2018 Eric Chadwick. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
using namespace std;

// Calculates the probability of winning when presented with num_tokens on your turn and saves it to solutions array.
//
// @param num_tokens is the number of tokens for which the win probability will be calculated.
// @param solved is an array that will hold the solutions to probabilities already calculated.
// @return is a pair in which the second element is the number of possible outcomes from num_tokens and the first element is the number
//         of those that are wins.
pair<double, double> win_prob(int num_tokens, pair<double, double> solved[]){
    // If already solved for num_tokens, return cached solution value.
    if(solved[num_tokens].second != 0)
        return solved[num_tokens];
    // Base case.  With 1 token you are hosed.
    else if(num_tokens == 1){
        solved[num_tokens].first = 0;
        solved[num_tokens].second = 1;
        cout << "1 token - win probability: 0.0000%, best move: take 1, result 0.0000% win probability." << endl;
        return solved[num_tokens];
    // Do the calculation.
    } else {
        pair<double, double> temp_prob(0,0);                    // This will be used to hold the working win probability at this node.
        pair<double, double> worst_opponent_prob(1,1);          // Win probability of worst child node.
        int take = 0;                                           // Take this many to generate worst child node.
        
        // Generate children of current node. These represent the possible states on opponent's turn.
        for(int i = floor(num_tokens / 2); i > 0; i--){
            // calcuate the win probability of child node (probability of opponent win).
            pair<double, double> child_prob = win_prob(num_tokens - i, solved);
            // If this child is the worst win probability, save the probability and the number of tokens taken to achieve it.
            if(child_prob.first / child_prob.second <= worst_opponent_prob.first / worst_opponent_prob.second){
                    worst_opponent_prob = child_prob;
                    take = i;
            }
            // Sum total outcomes and losing outcomes of children (i.e. winning outcomes of parent node).
            temp_prob.first += child_prob.second - child_prob.first;
            temp_prob.second += child_prob.second;
        }
        // Cache solution for this node.
        solved[num_tokens] = temp_prob;
        // Print out relevent info.
        cout << fixed << setprecision(4);
        cout << num_tokens << " tokens - win probability: " << temp_prob.first / temp_prob.second * 100 << "%, best move: take " << take <<
            " result " << (1 - (worst_opponent_prob.first / worst_opponent_prob.second)) * 100 << "%"<<
            " win probability." << endl;
        // Return probability with num_tokens
        return temp_prob;
    }
}

int main() {
    pair<double, double> p_solutions[501];
    cout << "If it is your turn with: " << endl;
    win_prob(500, p_solutions);
    
    return 0;
}
