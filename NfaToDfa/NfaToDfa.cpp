/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : NfaToDfa.cpp

 * Creation Date : Friday 10 July 2015 12:04:37 AM IST

 * Last Modified : Sunday 12 July 2015 02:35:02 AM IST

 _._._._._._._._._._._._._._._._._._._._._.*/

#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <queue>
#include <set>
using namespace std;

#define MAX 64 //maximum number of states in the dfa must be 64 only. 
typedef unsigned long long ULL;
int STATES, SYMBOLS;
int start_state;
vector<int> final_states;
vector<ULL> epsclosure (MAX, -1);

void epsilonClosure (int curr_node, unsigned long long &seen, vector<vector<vector<int> > > &table) {

    unsigned long long _one = 1;

    if (epsclosure[curr_node] != -1) {
        seen |= epsclosure[curr_node];
        return;
    }

    if ((seen & (_one << curr_node))) return;
    seen |= (_one << curr_node);

    for (int i = 0; i < int(table[curr_node][0].size()); ++i) {
        if (table[curr_node][0][i] != -1)
            epsilonClosure (table[curr_node][0][i], seen, table);
    }

}

unsigned long long startEpsilonClosure (int start_node, vector<vector<vector<int> > > &table) {

    if (epsclosure[start_node] != -1) return epsclosure[start_node];

    unsigned long long flag = 0;
    epsilonClosure(start_node, flag, table);
    return epsclosure[start_node] = flag;
}

int giveTypeOfState (int state) {
    int ret = 0; 
    ULL _one = 1;
    for (int i = 0; i < STATES; ++i) {

        if ( (state & (_one << i)) ) {
            for (int j = 0; j < int(final_states.size()); ++j) {
                if (i == final_states[j]) ret |= 2;
            }
        }
    }
    return ret;

}


void subsetConstruction (vector<vector<vector<int> > > &table) {
    //1) Find the starting state using the epsilon closure of the starting state of the epsilon NFA
    vector<vector<vector<int> > > dfatable;
    unsigned long long dfastart_state = startEpsilonClosure (start_state, table);


    for (int i = 1; i <= SYMBOLS; ++i) cout << " " << i ;
    cout << endl;
    
    cout << "->";

    /*Start the construction*/
    queue <ULL> Q; 
    set <ULL> seen;
    Q.push(dfastart_state);
    seen.insert (dfastart_state);

    ULL _one = 1;

    while (int(Q.size()) > 0) {
        ULL curr_state = Q.front();
        Q.pop();
        ULL go_state = 0;
        if (giveTypeOfState (curr_state) == 2) {
            cout << "*";
        }
        else {
            cout << " ";
        }

        cout << curr_state;


        for (int i = 1; i <= SYMBOLS; ++i) {

            go_state = 0;
            for (int j = 0; j < STATES; ++j) {
                if (curr_state & (_one << j)) {
                    for (int k = 0; k < (int) table[j][i].size(); k++) {
                        if (table[j][i][k] != -1) {
                            go_state |= (_one << table[j][i][k]);
                        }
                    }
                }
            }
            if (go_state == 0) {
                //No transitions on this input symbol
                cout << " " << -1;
                continue;
            }
            else {
                //find epsilon transitions for this set

                for (int j = 0; j < STATES; ++j) {
                    if (go_state & (_one << j)) {
                        go_state |= startEpsilonClosure (j, table);
                    }
                }

                    cout << " " << go_state;
                if (seen.find(go_state) == seen.end()) {
                    seen.insert (go_state);
                    Q.push (go_state);
                }
            }


        }
        cout << endl;
    }
}

vector<int> parseInputStates(char buff[]) {
    if (*buff == '-') {
        return vector<int> (1, -1);
    }
    vector<int> ret;
    int num = 0;
    while(*buff != '\0') {
        if (*buff == ',') {
            ret.push_back (num);
            num = 0;
        }
        else
            num = (num * 10) + (*buff - '0');
        buff++;
    }
    ret.push_back(num);
    return ret;
}



/*
 *
 * This should be preceeded by a method to validate the input format.*/
vector<vector<vector<int> > > parseInput() {

    vector<vector<vector<int> > > ret;

    cin >> STATES >> SYMBOLS;
    cin >> start_state;
    int no_of_final_states;
    cin >> no_of_final_states;

    for (int i = 0; i < no_of_final_states; ++i) {
        int temp;
        cin >> temp;
        final_states.push_back (temp);
    }

    char buff[25];
/*The symbols are indexed from 0, 1, ... . For e.g., if you use a,b , this is mapped to 0,1 .*/
    for (int i = 0; i < STATES; ++i) {
        vector<vector<int> > table_temp;
        for (int j = 0; j < SYMBOLS+1; ++j) { //+1 for the epsilon state
            scanf ("%s", buff);
            table_temp.push_back (parseInputStates(buff));
        }
        ret.push_back(table_temp);
    }
    return ret;
}

int main() {
    vector<vector<vector<int> > > table = parseInput();
    subsetConstruction (table);
    return 0;
}
