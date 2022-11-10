#include<string>
#include<vector>
#include<cmath>
#include<iostream>
using namespace std;

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

int main(){
    vector<double> left;
    vector<double> right;
    left.push_back(10000000000.0);
    left.push_back(10000000000.0);
    right.push_back(10200000000000);
    right.push_back(10200000000000);
    vector<double> x;
    x = minimum(left, right);
    cout << x[0] << " " << x[1] << endl;
    return 0;
}
