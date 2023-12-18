#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);
string getFilePath(const string& fileName);
void writeFile(const string& path);
void readFile(const string& path);
bool IsLeapYear(int year);
/*
 * Complete the 'getMinCost' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER k
 *  3. 2D_INTEGER_ARRAY plans
 */

long getMinCost(int n, int k, vector<vector<int>> plans) {
		auto minCost(plans);
		//It will order the Vector 2D by cost
		// To the Lower to Higher Cost
        for (int j = 0; j < plans.size(); j++) {
            for (int i = 0; i < plans.size() - 1; i++) {
				if (plans[i][3] > plans[i+1][3]) {
					minCost[0] = plans[i + 1];
					plans[i+1] = plans[i];
					plans[i] = minCost[0];
				}
            }
        }

        int countDays = 0;
        int coreStill = 0;
        bool satisfiedCores = false;
        int sumCost= 0;

        while (countDays <= n){
			coreStill = k;
			satisfiedCores = false;
			countDays++;
			for (vector<int> plan : plans) {
				//check viability of the day
				// plan[ a0, a1, ...] a0 and a1 viability between inclusive
				if ((plan[0] <= countDays && plan[1]>=countDays)&& !satisfiedCores){

					if (plan[2]>=coreStill ){
 						sumCost += coreStill*plan[3];
						satisfiedCores = true;
					}else{

 						sumCost+= plan[2] * plan[3];
						coreStill = coreStill - plan[2];
						if (coreStill <= 0){
 						satisfiedCores = false;
						}
					}
				}
			}
        }

        return sumCost;
}

using namespace std;
int main()
{

	fstream my_file;
	my_file.open("cost.txt", ios::in);
	if (!my_file) {
		cout << "No such file";
	}
	//********* Days required **************
	string n_temp;
    getline(my_file, n_temp);
    int n  = stoi(ltrim(rtrim(n_temp)));
	//********* Cores Required per day ************
    string k_temp;
    getline(my_file, k_temp);
    int k = stoi(ltrim(rtrim(k_temp)));
	//********* Plans Available ************
    string plans_rows_temp;
    getline(my_file, plans_rows_temp);
    int plans_rows = stoi(ltrim(rtrim(plans_rows_temp)));

    //********* Plans [a0,a1,a2, a3] => 4 items ************
    // a0 = day of the week available
    // a1 = day of the week available
    // a2 = Core available at the day specified from a0 and a1
    // a3 = price of each a2 required.
    string plans_columns_temp;
    getline(my_file, plans_columns_temp); // 4
    int plans_columns = stoi(ltrim(rtrim(plans_columns_temp)));

    // Just to facilitate to split the item read from file
    // To make easy to know how many column each rows has
    vector<vector<int>> plans(plans_rows);

    // This loop will take care of each row
    for (int i = 0; i < plans_rows; i++) {
        plans[i].resize(plans_columns);

        string plans_row_temp_temp;
        getline(my_file, plans_row_temp_temp);

        vector<string> plans_row_temp = split(rtrim(plans_row_temp_temp));
        // This loop will take care of each column of the current row
        for (int j = 0; j < plans_columns; j++) {
            int plans_row_item = stoi(plans_row_temp[j]);

            plans[i][j] = plans_row_item;
        }
    }
    // Challenge > get Minimum Cost;
    long result = getMinCost(n, k, plans);

    //my_file << result << "\n";
    cout << result;
    my_file.close();

    return 0;
}




string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}




string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}



vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}



string getFilePath(const string& fileName) {
	string path = __FILE__; //gets source code path, include file name
	path = path.substr(0, 1 + path.find_last_of('\\')); //removes file name
	path += fileName; //adds input file to path
	path = "\\" + path;
	return path;
}

void writeFile(const string& path) {
	ofstream os{ path };
	if (!os) cout << "file create error" << endl;
	for (int i = 0; i < 15; ++i) {
		os << i << endl;
	}
	os.close();
}

void readFile(const string& path) {
	ifstream is{ path };
	if (!is) cout << "file open error" << endl;
	int val = -1;
	while (is >> val) {
		cout << val << endl;
	}
	is.close();
}
