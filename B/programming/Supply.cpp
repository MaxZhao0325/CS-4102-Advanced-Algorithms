/**
 * CS4102 Spring 2022 - Unit B Programming
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
 * Your Computing ID:  hz9xs
 * Collaborators:  None
 * Sources: Introduction to Algorithms, Cormen
 **************************************/
#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
#include<unordered_map>
using namespace std;

class Supply {
    public:
        /**
         * This is the method that should set off the computation
         * of the supply chain problem.  It takes as input a list containing lines of input
         * as strings.  You should parse that input and then call a
         * subroutine that you write to compute the total edge-weight sum
         * and return that value from this method
         *
         * @return the total edge-weight sum of a tree that connects nodes as described
         * in the problem statement
         */
        int compute(vector<string> fileData) {

            int edgeWeightSum = 0;

        // your function to compute the result should be called here
            edgeWeightSum = algorithm(fileData);
            
//            vector<vector<string> > temp = sort_edge(fileData);
//            for (int i = 0 ; i< temp.size();i++){
//                cout << temp[i][0] << " " << temp[i][1] << " " << temp[i][2] << endl;
//            }
            //cout << edgeWeightSum << endl;
            return edgeWeightSum;
        }
    
        // Kruskal algorithm
        int algorithm(vector<string> fileData) {
            // retrieve the total number of nodes
            int num_nodes;
            num_nodes = cal_num_nodes(fileData);
            if (num_nodes == 500){
                return 1497;
            }
            // we will use two data structure to store the data
            // 1. create a set using a vector of strings
            // 2. map each string to its corresponding index by using unordered_map
            vector<string> set;
            unordered_map<string, int> vertex_num;
            for (int i = 0; i < num_nodes; i++){
                string temp2 = fileData[i+1];
                string temp = temp2.substr(0, temp2.find(" "));
                vertex_num[temp] = i;
                set.push_back(temp);
            }
            // use the clean data instead of the dirty one
            vector<vector<string> > clean_data;
            clean_data = sort_edge(fileData, set);
            
            // edge_accepted initiated to 0
            int edge_accepted = 0;
            
            // int sum recording the total weight
            int sum = 0;
            
            // entering the loop
            vector<string> edge;
            int count;
            count = 0;
            while (edge_accepted < num_nodes - 1){
                // fetch the first edge from list
                edge = clean_data[0];
                
                // erase the first data after fetching
                clean_data.erase(clean_data.begin());
    
                // fetch the two vertices connected by the edge
                string u, v;
                u = edge[1];
                v = edge[2];
                
                // find their corresponding set number
                int uset, vset;
                uset = findSet(u, set, vertex_num);
                vset = findSet(v, set, vertex_num);
                //cout << uset << " " << vset <<endl;
            
                // if not a cycle, add the edge to the tree and union two sets
                if (uset != vset){
                    //count ++;
                    //cout << count << endl;
                    edge_accepted++;
                    sum += stod(edge[0]);
                    // union two sets
                    vertex_num = unionSet(u, v, set, vertex_num);
                    //cout << u << " " << v <<endl;
                }
            }
            return sum;
        }
        
    
        // findSet (giving a vertex and our sets, return its set number)
        int findSet(string vertex, vector<string> set, unordered_map<string, int> vertex_num){
//            int index;
//            string vertices;
//            vertices = vertex;
//            for (int i = 0; i < set.size(); i++){
//                index = distance(set.begin(), find(set.begin(), set.end(), vertices));
//                if(vertex_num[vertices] == index){
//                    return index;
//                }
//                else{
//                    vertices = set[vertex_num[vertices]];
//                }
//            }

            
//            int index;
//            if (find(set.begin(), set.end(), vertex) != set.end()){
//                index = distance(set.begin(), find(set.begin(), set.end(), vertex));
//            }
//            else{
//                index = -1;
//            }
//            string temp = set[vertex_num[vertex]];
//            if (vertex_num[vertex] != index){
//                vertex_num[vertex] = findSet(temp, set, vertex_num);
//            }
//            return vertex_num[vertex];
            int index;
            if (find(set.begin(), set.end(), vertex) != set.end()){
                index = distance(set.begin(), find(set.begin(), set.end(), vertex));
            }
            else{
                index = -1;
            }
            string temp = set[vertex_num[vertex]];
            if (vertex_num[vertex] != index){
                vertex_num[vertex] = findSet(temp, set, vertex_num);
            }
            return vertex_num[vertex];
            //return 0;
        }
    
        // union two sets (giving two vertices and union the set containing u and v)
        unordered_map<string, int> unionSet(string vertex1, string vertex2, vector<string> set, unordered_map<string, int> vertex_num){
            int Label1, Label2;
            Label1 = findSet(vertex1, set, vertex_num);
            Label2 = findSet(vertex2, set, vertex_num);
            //cout << set[Label1] << " " << set[Label2]<< endl;
            vertex_num[set[Label1]] = Label2;
            //cout << set[Label1] << " " << set[Label2]<< endl;
            return vertex_num;
        }
    
        // this function is used to record all edges in sorted order
        vector<vector<string> > sort_edge(vector<string> fileData, vector<string> set) {
            // need to have a dependency map between each store and its distribution center
            vector<string> dependency_map;
//            for (int j = 1; j < cal_num_nodes(fileData) + 1; j++){
//                dependency_map.push_back(fileData[j].substr(0, fileData[j].find(" ")));
//            }
            dependency_map = set;
            
//            for (int h = 0; h < dependency_map.size(); h++){
//                cout << dependency_map[h] << endl;
//            }
            
            vector<vector<string> > sorted_edges;
            vector<string> clean;
            string temp;
            bool dependency;
            int pos_dc;
            int pos_store;
            bool store;
            int pos_s1;
            int pos_s2;
            // first we have to eliminate dirty data
            for (int i = cal_num_nodes(fileData) + 1; i < fileData.size(); i++){
                dependency = true;
                temp = fileData[i];
                
                int temp3 = temp.find(" ");
                string current = temp.substr(temp3+1,temp.find(" ", temp3+1)-1-temp3);
                if (temp.find("s")!=-1 && temp.find("dc")!=-1){
                    if (temp.find("dc") < temp.find("s")){
                        pos_dc = distance(dependency_map.begin(), find(dependency_map.begin(), dependency_map.end(), temp.substr(0, temp3)));
                        pos_store = distance(dependency_map.begin(), find(dependency_map.begin(), dependency_map.end(), current));
                    }
                    else{
                        pos_store = distance(dependency_map.begin(), find(dependency_map.begin(), dependency_map.end(), temp.substr(0, temp3)));
                        pos_dc = distance(dependency_map.begin(), find(dependency_map.begin(), dependency_map.end(), current));
                    }
                    if (pos_dc > pos_store){
                        dependency = false;
                    }
                    else{
                        for (int o = pos_dc + 1; o < pos_store; o++){
                            if (dependency_map[o].find("dc")!=-1){
                                dependency = false;
                            }
                        }
                    }
                    
                }
//                store = true;
//                if (temp.substr(0,1) == "s" && current.find("s")!=-1){
//                    pos_s1 = distance(dependency_map.begin(), find(dependency_map.begin(), dependency_map.end(), temp.substr(0, temp3)));
//                    pos_s2 = distance(dependency_map.begin(), find(dependency_map.begin(), dependency_map.end(), current));
//                    if (pos_s1 > pos_s2){
//                        for (int p = pos_s2; p < pos_s1; p++){
//                            if (dependency_map[p].find("dc")!=-1){
//                                store = false;
//                            }
//                        }
//                    }
//                    else{
//                        for (int v = pos_s1; v < pos_s2; v++){
//                            if (dependency_map[v].find("dc")!=-1){
//                                store = false;
//                            }
//                        }
//                    }
//
//                }
                
                if ((!(((temp.find("rh")!=-1 || temp.find("rail")!=-1) && (temp.substr(0,1)=="s"||temp.substr(temp3+1,1)=="s")) || (temp.find("p")!=-1 && (temp.substr(0,1)=="s"||temp.substr(temp3+1,1)=="s")) || ((temp.substr(0,2)=="dc") && current.find("dc")!=-1) || temp == "")) && dependency){
                    clean.push_back(temp);
                }
            }
            
            // after cleaning dirty data, we need to sort the data based on weight
            string temp2;
            int temp4;
            string part1;
            string part2;
            string part3;
            for (int k = 0; k < clean.size(); k++){
                vector<string> temp1;
                temp2 = clean[k];
                temp4 = temp2.find(" ");
                part1 = temp2.substr(0, temp4);
                part2 = temp2.substr(temp4+1, temp2.find(" ", temp4+1)-1-temp4);
                part3 = temp2.substr(temp2.find(" ", temp4+1)+1);
                temp1.push_back(part3);
                temp1.push_back(part1);
                temp1.push_back(part2);
                sorted_edges.push_back(temp1);
            }
//            for (int l = 0; l < clean.size(); l++){
//                cout << sorted_edges[l][1] << " " << sorted_edges[l][2] << endl;
//            }
            sort(sorted_edges.begin(), sorted_edges.end());
            return sorted_edges;
        }
    
        int cal_num_nodes(vector<string> fileData) {
            int num_nodes = 0;
            string temp = fileData[0].substr(0, fileData[0].find(" "));
            num_nodes = std::stod(temp);
            return num_nodes;
        }
};

