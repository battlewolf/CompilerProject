/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : NfaToDfa.cpp

 * Creation Date : Friday 10 July 2015 12:04:37 AM IST

 * Last Modified : Saturday 11 July 2015 03:54:40 PM IST

 _._._._._._._._._._._._._._._._._._._._._.*/

#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <queue>
#include <set>
using namespace std;
typedef unsigned long long ULL;
int STATES, SYMBOLS;
int start_state;
vector<int> final_states;


void epsilonClosure (int curr_node, unsigned long long &seen, vector<vector<vector<int> > > &table) {
    if ((seen & (1L << curr_node))) return;
    seen |= (1L << curr_node);

    for (int i = 0; i < int(table[curr_node][0].size()); ++i) {
        if (table[curr_node][0][i] != -1)
            epsilonClosure (table[curr_node][0][i], seen, table);
    }

}

unsigned long long startEpsilonClosure (int start_node, vector<vector<vector<int> > > &table) {
    unsigned long long flag = 0;
    epsilonClosure(start_state, flag, table);
    return flag;
}

void subsetConstruction (vector<vector<vector<int> > > &table) {
    //1) Find the starting state using the epsilon closure of the starting state of the epsilon NFA

    vector<vector<vector<int> > > dfatable;
    unsigned long long dfastart_state = startEpsilonClosure (start_state, table);

    queue <ULL> Q; 
    set <ULL> seen;
    Q.push(dfastart_state);
    seen.insert (dfastart_state);

    ULL _one = 1;

    while (int(Q.size()) > 0) {
        ULL curr_state = Q.front();
        Q.pop();
        ULL go_state = 0;
        cout << curr_state << endl;
        
        
        for (int i = 1; i <= SYMBOLS; ++i) {

            go_state = 0;
            for (int j = 0; j < STATES; ++j) {
                if (curr_state & (_one << j)) {
                    for (int k = 0; k < (int) table[j][i].size(); k++) {
                        if (table[j][i][k] != -1) {
                            go_state |= table[j][i][k];
                        }
                    }
                }
            }

            if (go_state == 0) {
            
                continue;
            }
            else {
                
            }

        }

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

    for (int i = 0; i < STATES; ++i) {
        vector<vector<int> > table_temp;
        for (int j = 0; j < SYMBOLS+1; ++j) { //+1 for the epsilon state
            scanf ("%s", buff);
            table_temp.push_back (parseInputStates(buff));
        }
        ret.push_back(table_temp);
    }
    /*
       for (int i = 0; i < STATES; ++i) {
       for (int j = 0; j < SYMBOLS + 1; ++j) {
       cout << i << " " << j << " : ";
       for (int k = 0; k < int(ret[i][j].size()); ++k) {
       cout << ret[i][j][k] << " ";
       }
       cout << endl;
       }
       }
       */
    return ret;
}

int main() {
    vector<vector<vector<int> > > table = parseInput();
    subsetConstruction (table);




    return 0;
}
