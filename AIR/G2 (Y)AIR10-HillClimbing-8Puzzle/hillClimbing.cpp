#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;
/*
**  8Puzzle Problem Solution using Hill Climbing...Not Guaranteed to give an optimal solution....
*	1 2 3				1 2 3
*	4 5 6	(Initial State)	=>	4 5 6 (Goal State)
*	7 X 8				7 8 X
*/
class State {
public:
    int** board;
    int heuristicValue;
    int parentIndex;

    State() {
        board = (int**) malloc(3 * sizeof(int*));
        for(int i=0; i<3; i+=1) {
            board[i] = (int*) malloc(3 * sizeof(int));
        }
        heuristicValue = 0;
        parentIndex = -1;
    }

    State(const State& s) {
        board = (int**) malloc(3 * sizeof(int*));
        for(int i=0; i<3; i+=1) {
            board[i] = (int*) malloc(3 * sizeof(int));
            for(int j=0; j<3; j+=1)
                board[i][j] = s.board[i][j];
        }
        heuristicValue = 8;
        parentIndex = -1;
    }

    void display() {
        for(int i=0; i<3; i+=1) {
            printf("%d %d %d\n", board[i][0], board[i][1], board[i][2]);
        }
    }
//Accept Board Configuration
    void input() {
        int element;
        for(int i=0; i<3; i+=1) {
            for(int j=0; j<3; j+=1) {
                scanf("%d", &board[i][j]);
            }
        }
    }
//  positions=	0 1 2
//		3 4 5
//		6 7 8
//Returns position of Black Block (for val 0 in our case)
    int getBlankSpot() {
        for(int i=0; i<3; i+=1) {
            for(int j=0; j<3; j+=1) {
                if(board[i][j] == 0)
                    return i*3 + j;
            }
        }
    }
//Heurisitic function
    int getHeuristicValue(const State& s) {
        int tempHeuristicValue = 0;
        for(int i=0; i<3; i+=1) {
            for(int j=0; j<3; j+=1) {
                if(board[i][j] != s.board[i][j])
                    tempHeuristicValue += 1;
            }
        }
        heuristicValue = tempHeuristicValue;
        return tempHeuristicValue;
    }

    void moveUp(int row, int column) {
        board[row][column] = board[row-1][column];
        board[row-1][column] = 0;
    }

    void moveDown(int row, int column) {
        board[row][column] = board[row+1][column];
        board[row+1][column] = 0;
    }

    void moveLeft(int row, int column) {
        board[row][column] = board[row][column-1];
        board[row][column-1] = 0;
    }

    void moveRight(int row, int column) {
        board[row][column] = board[row][column+1];
        board[row][column+1] = 0;
    }
};

class HillClimbingAlgorithm {
    State initialState;
    State goalState;
    vector<State> stateList;
    vector<State> tempList;

public:
    HillClimbingAlgorithm(){}//Constructor
//lowestScore giving node from tempList
    int getLowestScore() {	//Get successor with lowest score,.ie. most preferred solution
        int size = tempList.size();
        int index = -1;
        int min = 65535;
        for(int i=0; i<size; i+=1) {
            if(min > tempList[i].heuristicValue) {
                min = tempList[i].heuristicValue;
                index = i;
            }
        }

        return index;
    }
	//Adds all possible states to the tempList after clearing the tempList...
    void getPossibleStates(State& s) {
        int position = s.getBlankSpot();
        int row = position / 3;
        int column = position % 3;
	//Clear the tempList to record successors of currentState....
        tempList.clear();

        if(column != 0) {
            State temp1(s);
            temp1.moveLeft(row, column);
            temp1.heuristicValue = temp1.getHeuristicValue(goalState);
            tempList.push_back(temp1);
        }

        if(row < 2) {
            State temp2(s);
            temp2.moveDown(row, column);
            temp2.heuristicValue = temp2.getHeuristicValue(goalState);
            tempList.push_back(temp2);
        }

        if(row > 0) {
            State temp3(s);
            temp3.moveUp(row, column);
            temp3.heuristicValue = temp3.getHeuristicValue(goalState);
            tempList.push_back(temp3);
        }

        if(column != 2) {
            State temp4(s);
            temp4.moveRight(row, column);
            temp4.heuristicValue = temp4.getHeuristicValue(goalState);
            tempList.push_back(temp4);
        }
    }

    void initiateAlgorithm() {
        printf("Enter the initial state: :");
        initialState.input();
        stateList.push_back(initialState);

        printf("Enter the goal state: : ");
        goalState.input();

        printf("\n----- Start State -----\n");
        initialState.display();

        printf("\n----- Goal State -----\n");
        goalState.display();
        //Actual hill climging algorithm
        State currentState, nextState;


	       //Initialize current state to inital state
        initialState.heuristicValue = initialState.getHeuristicValue(goalState);
        initialState.parentIndex = -1;

        currentState =  initialState;
        getPossibleStates(currentState);
        int lowestIndex = getLowestScore();
        nextState = tempList[lowestIndex];

        while(nextState.heuristicValue < currentState.heuristicValue) {
            currentState = nextState;
            getPossibleStates(stateList[stateList.size() - 1]);//Adds all possible successors to tempList
            lowestIndex = getLowestScore();//index of node with lowestScore in tempList.
            nextState = tempList[lowestIndex];
            stateList.push_back(nextState);//stateList contains all the nodes that have been visited along the path to reach goal state
        }

        stateList.push_back(goalState);

        printf("\n----- Steps -----"+stateList.size()+"\n");
        for(int i=0; i<stateList.size(); i+=1) {
            stateList[i].display();
            printf("\n");
        }
    }
};

int main() {
    HillClimbingAlgorithm hca;
    hca.initiateAlgorithm();

    return 0;
}

/*=========SIMPLE HILL CLIMBING ALGORITHM======================
Step 1 : Evaluate the initial state. If it is a goal state then stop and return success. Otherwise, make initial state as current state.

Step 2 : Loop until the solution state is found or there are no new operators present which can be applied to the current state.

a) Select a state that has not been yet applied to the current state and apply it to produce a new state.

b) Perform these to evaluate new state
    i. If the current state is a goal state, then stop and return success.
    ii. If it is better than the current state, then make it current state and proceed further.
    iii. If it is not better than the current state, then continue in the loop until a solution is found.

Step 3 : Exit.

****=============STEEPEST ASCENT HILL CLIMBING ALGORITHM===============
Step 1 : Evaluate the initial state. If it is goal state then exit else make the current state as initial state
Step 2 : Repeat these steps until a solution is found or current state does not change

i. Let ‘target’ be a state such that any successor of the current state will be better than it;

ii. for each operator that applies to the current state
     a. apply the new operator and create a new state
     b. evaluate the new state
     c. if this state is goal state then quit else compare with ‘target’
     d. if this state is better than ‘target’, set this state as ‘target’
     e. if target is better than current state set current state to Target

Step 3 : Exit

*/
