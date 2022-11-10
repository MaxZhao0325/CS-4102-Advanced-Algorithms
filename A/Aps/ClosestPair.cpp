/**
 * CS4102 Spring 2022 - Unit A Programming 
 *********************************************
 * Collaboration Policy: You are encouraged to collaborate with up to 3 other
 * students, but all work submitted must be your own independently written
 * solution. List the computing ids of all of your collaborators in the
 * comments at the top of each submitted file. Do not share written notes,
 * documents (including Google docs, Overleaf docs, discussion notes, PDFs), or
 * code. Do not seek published or online solutions, including pseudocode, for
 * this assignment. If you use any published or online resources (which may not
 * include solutions) when completing this assignment, be sure to cite them. Do
 * not submit a solution that you are unable to explain orally to a member of
 * the course staff. Any solutions that share similar text/code will be
 * considered in breach of this policy. Please refer to the syllabus for a
 * complete description of the collaboration policy.
 *********************************
 * Your Computing ID: hz9xs
 * Collaborators: none
 * Sources: Introduction to Algorithms, Cormen
 **************************************/
#include<string>
#include<vector>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;

class ClosestPair {
    public:

        /**
         * This is the method that should set off the computation
         * of closest pair.  It takes as input a vector containing lines of input
         * as strings.  You should parse that input and then call a
         * subroutine that you write to compute the closest pair distances
         * and return those values from this method.
         *
         * @return the distances between the closest pair and second closest pair
         * with closest at position 0 and second at position 1 
         */
        vector<double> compute(vector<string> fileData) {
            // create a vector of vector to store the list of points
            vector<vector<double> > map = intermediate(fileData);
            
            //if there is a vertical line, change it to horizontal
            int turn = 0;
            for(int o = 0; o < map.size()-1; o++){
                if (map[o][0] != map[o+1][0]){
                    turn = 1;
                }
            }
            if (turn == 0){
                for (int j = 0; j < map.size(); j++){
                    iter_swap(map[j].begin(), map[j].begin() + 1);
                }
            }
            
            // sort the list by x
            sort(map.begin(), map.end());
            
            // using algo to find the answer
            
            vector<double> closest = algorithm(map);
            vector<double> temp;
            if (closest[0] > closest[1]){
                temp.push_back(closest[1]);
                temp.push_back(closest[0]);
            }
            else{
                temp = closest;
            }
            return temp;
        }
    
        vector<vector<double> > intermediate(vector<string> fileData){
            vector<vector<double> > map;
            for (int i = 0; i < fileData.size(); i++){
                // current string
                string current = fileData[i];
                // there might be a blank line at the end of the file
                if (current != ""){
                    vector<double> temp;
                    int index = current.find(" ");
                    double x = std::stod(current.substr(0, index));
                    double y = std::stod(current.substr(index+1));
                    temp.push_back(x);
                    temp.push_back(y);
                    map.push_back(temp);
                }
            }
            return map;
        }
    
        vector<double> algorithm(vector<vector<double> > map){
            vector<double> output;
            // base case: when there are only three or two points left
            if (map.size() == 3){
                double x = distance(map[0],map[1]);
                double y = distance(map[0],map[2]);
                double z = distance(map[1],map[2]);
                // return two smallest
                output.push_back(min(x, y));
                output.push_back(min(max(x, y), z));
                return output;
            }
            if (map.size() == 2){
                output.push_back(distance(map[0],map[1]));
                output.push_back(1000000000.0);
                //cout << output[0] << " " << output[1] << endl;
                return output;
            }
            // DIVIDE
            // create the left and right sublist to do recursion
            vector<vector<double> > left;
            vector<vector<double> > right;
            // two cases: odd and even
            if (map.size()%2 == 0){
                for (int i = 0; i < map.size()/2; i++){
                    left.push_back(map[i]);
                }
                // fulfill the right sublist
                for (int i = map.size()/2; i < map.size(); i++){
                    right.push_back(map[i]);
                }
            }
            else{
                for (int i = 0; i < map.size()/2; i++){
                    left.push_back(map[i]);
                }
                // fulfill the right sublist
                for (int i = map.size()/2 + 1; i < map.size(); i++){
                    right.push_back(map[i]);
                }
            }
            
            // Recursively compute the closest pair of points in each list
            vector<double> minLeft = algorithm(left);
            vector<double> minRight = algorithm(right);
//            if (map.size() == 3){
//                cout << minLeft[0] << " " << minLeft[1] << endl;
//                cout << minRight[0] << " " << minRight[1] << endl;
//            }
            
            // CONQUER
            // median of the map
            double median_x;
            if (map.size()%2 == 0){
                median_x = (map[map.size()/2][0] + map[map.size()/2-1][0])/2.0;
            }
            else{
                median_x = map[map.size()/2][0];
            }
            // Construct list of points in the runway
            vector<double> mini = minimum(minLeft, minRight);
//            if (map.size() == 5){
//                cout << mini[0] << " " << mini[1] << endl;
//            }
            double reference_limit = max(mini[0], mini[1]);
            vector<vector<double> > runway_points;
            //cout << reference_limit << " " << median_x << endl;
            // construct left runway and right runway
            vector<vector<double> > left_runway;
            vector<vector<double> > right_runway;
            for (int k = 0; k < map.size(); k++){
                if ((median_x + reference_limit) > map[k][0] && map[k][0] > (median_x - reference_limit)){
                    runway_points.push_back(map[k]);
                    if (map[k][0] <= median_x){
                        left_runway.push_back(map[k]);
                    }
                    if (map[k][0] >= median_x){
                        right_runway.push_back(map[k]);
                    }
                }
            }
//            if (map.size() == 5){
//                for (int x = 0; x < left_runway.size(); x++){
//                    cout << left_runway[x][0] << " " << left_runway[x][1] << endl;
//                }
//                cout << endl;
//                for (int y = 0; y < right_runway.size(); y++){
//                    cout << right_runway[y][0] << " " << right_runway[y][1] << endl;
//                }
//            }
            // sort runway points by y coordinates
            for (int q = 0; q < runway_points.size(); q++){
                iter_swap(runway_points[q].begin(), runway_points[q].begin() + 1);
            }
            sort(runway_points.begin(), runway_points.end());
            for (int q = 0; q < runway_points.size(); q++){
                iter_swap(runway_points[q].begin(), runway_points[q].begin() + 1);
            }
//            if (map.size() == 5){
//                for (int y = 0; y < runway_points.size(); y++){
//                    cout << runway_points[y][0] << " " << runway_points[y][1] << endl;
//                }
//            }
            // Compare each point in runway to 7 points above it and save the two closest pairs
            //cout << runway_points.size() <<endl;
            vector<double> runway_minimum;
            if (runway_points.size()!=0){
                 runway_minimum = runwayComparison(runway_points, left_runway, right_runway);
            }
            else{
                runway_minimum.push_back(1000000000.0);
                runway_minimum.push_back(1000000000.0);
            }
            //cout << runway_minimum[0] << " " << runway_minimum[1] << endl;
            // Output two closest pairs among left, right, and runway points
            output = minimum(mini, runway_minimum);
            //cout << output[0] << " " << output[1] << endl;
            //cout << mini[0] << " " << mini[1] << endl;
            return output;
        }
        
        // calculate the distance between two points
        double distance(vector<double> point1, vector<double> point2){
            double xDistance = point2[0] - point1[0];
            double yDistance = point2[1] - point1[1];
            return sqrt(pow(xDistance,2) + pow(yDistance,2));
        }
    
        // choose two minimum values from four doubles
        vector<double> minimum(vector<double> minleft, vector<double> minright){
            vector<double> miniTwo;
            double minimum1 = minleft[0];
            double minimum2 = minleft[1];
            if (minimum1 > minimum2){
                if (minright[0] < minimum1){
                    minimum1 = minright[0];
                    if (minimum1 > minimum2){
                        if (minright[1] < minimum1){
                            minimum1 = minright[1];
                        }
                    }
                    else{
                        if (minright[1] < minimum2){
                            minimum2 = minright[1];
                        }
                    }
                }
                else{
                    if (minright[1] < minimum1){
                        minimum1 = minright[1];
                    }
                    else{
                        if (minright[1] < minimum2){
                            minimum2 = minright[1];
                        }
                    }
                }
            }
            else{
                if (minright[0] < minimum2){
                    minimum2 = minright[0];
                    if (minimum2 > minimum1){
                        if (minright[1] < minimum2){
                            minimum2 = minright[1];
                        }
                    }
                    else{
                        if (minright[1] < minimum1){
                            minimum1 = minright[1];
                        }
                    }
                }
                else{
                    if (minright[1] < minimum2){
                        minimum2 = minright[1];
                    }
                    else{
                        if (minright[1] < minimum1){
                            minimum1 = minright[1];
                        }
                    }
                }
            }
            miniTwo.push_back(minimum1);
            miniTwo.push_back(minimum2);
            return miniTwo;
        }
        // compare the run way points and find two smallest distant pair.
        vector<double> runwayComparison(vector<vector<double> > runway, vector<vector<double> > left_runway, vector<vector<double> > right_runway){
            vector<double> result;
            double mini1 = 100000000.0;
            double mini2 = 100000000.0;
                for (int i = 0; i < runway.size() - 1; i++){
                    for (int j = 1 + i; j < 8 + i; j++){
                        if (j < runway.size()){
                            if (((find(left_runway.begin(), left_runway.end(), runway[i]) != left_runway.end()) && (find(right_runway.begin(), right_runway.end(), runway[j]) != right_runway.end())) || ((find(left_runway.begin(), left_runway.end(), runway[j]) != left_runway.end()) && (find(right_runway.begin(), right_runway.end(), runway[i]) != right_runway.end()))){
                                if (mini1 > mini2){
                                    if (distance(runway[i], runway[j]) < mini1){
                                        mini1 = distance(runway[i], runway[j]);
                                    }
                                    
                                }
                                else{
                                    if (distance(runway[i], runway[j]) < mini2){
                                        mini2 = distance(runway[i], runway[j]);
                                    }
                                }
                            }
                        }
                    }
                }
            result.push_back(mini1);
            result.push_back(mini2);
            //cout << mini1 << " " << mini2 << endl;
            return result;
        }
};

