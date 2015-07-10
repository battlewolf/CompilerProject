/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : NfaToDfa.cpp

* Creation Date : Friday 10 July 2015 12:04:37 AM IST

* Last Modified : Friday 10 July 2015 03:41:27 AM IST

_._._._._._._._._._._._._._._._._._._._._.*/

#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

int STATES, SYMBOLS;
int start_state;
vector<int> final_states;


void epsilonClosure (int curr_node, long long &seen, vector<vector<vector<int> > > &table) {
    if ((seen & (1L << curr_node))) return;
    seen |= (1L << curr_node);
    
    for (int i = 0; i < int(table[curr_node][0].size()); ++i) {
        epsilonClosure (table[curr_node][0][i], seen, table);
    }

}

long long startEpsilonClosure (int start_node, vector<vector<vector<int> > > &table) {
    long long flag = 0;
    epsilonClosure(start_state, flag, table);
    return flag;
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





    return 0;
}
