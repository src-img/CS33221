#include <iostream>
#include <fstream>
#include <vector>

int main() {
    //file input & validation
    std::ifstream inputFile;
    inputFile.open("in.txt");
    if(!inputFile) {
        std::cout << "Failed to open file! Terminating program."; 
        std::exit(1);
    }

    //variables ---------------------------------------------------------------
    int n = 0; //processes
    int m = 0; //resources
    char current; //current char being read from file
    std::vector<int> available(0);
    std::vector<std::vector <int>> max(0);
    std::vector<std::vector <int>> allocation(0);
    int column = 0; //stupidest way to do it probably but this tracks what column of the matrix it's in

    //populating available, max, & allocation
    while(!inputFile.eof()) {
        inputFile.get(current);
        if (int(current) - int('0') >= 0 && int(current) - int('0') <= 9) {
            switch(column) {
                case 0: {
                    if (allocation.size() <= n) allocation.resize(n + 1);
                    allocation[n].push_back(int(current) - int('0'));
                    break;
                }
                case 1: {
                    if (max.size() <= n) max.resize(n + 1);
                    max[n].push_back(int(current) - int('0'));
                    break;
                }
                case 2: {
                    available.push_back(int(current) - int('0'));
                    break;
                }
                ++m;
            }
        }
        else if (current ==',') {
            m = 0;
            ++column;
        }
        else if(current =='\n') {
            n++;
            column = 0;
        }
    }
    inputFile.close();
    ++n; //processes were counted starting at 0
    ++m; //resources were also counted starting at 0
    //these ought to now be the actual legit #s of resources and processes :)

    //populating need
    std::vector<std::vector <int>> need(n, std::vector<int>(m)); //preallocating vector
    for (int i = 0; i < n; ++i)  {
        for(int j = 0; j < m; ++j) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    //saftey check <3 -----------------------------------------------------
    //saftey algorithm initalization
    std::vector <int> work(m);
    for(int i = 0; i < m; ++i) {
        work[i] = available[i];
    }
    std::vector <int> finish(n);
    for(int i = 0; i < n; ++i) {
        finish[i] = 0; //nothing's finished.
    }

    int order = 0;
    std::vector <int> safeSeq;

    for (int i = 0; i < n; ++i) { //goes through processes
        for (int j = 0; j < n; ++j) {  //look for unfinished process
            if (finish[j] == 0) {
                int flag = 0; //danger bool. currently safe

                for (int k = 0; k < m; ++k) { //looks for need <= work
                    if (need[j][k] > available[k]) { //if need is bigger than work, set danger flag to true, then leave to find a better order
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0) {//if no danger
                    finish[j] = 1; //that process is finished!
                    safeSeq.push_back(j); //adds process to safe sequence
                    for (int l = 0; l < m; ++l) {
                       available[l] += allocation[j][l]; //adds allocated resource to available
                    }
                }
            }
        }
    }
    
    //saftey report <3 --------------------------------------------------------------------------------

    int flag = 0; //danger bool 2. currently no danger

    for(int i = 0; i < n; ++i) { //check if safe
        if(finish[i] == 0) { //if the process isn't finished, there are Problems
            flag = 1; //there are problems: offical announcement
            std::cout << "Unsafe sequence!!"; //let the user know too
        }
        break; //one problem is enough. don't bother with the loop
    }

    if (flag == 0) { //it's safe! print the order
        std::cout << "Safe sequence:\n";
        for (int i = 0; i < n; ++i) {
            std::cout << (i + 1) << ": Process " << safeSeq[i] << "\n";
        }
    }
}