# CS4102 Spring 2022 -- Unit D Programming
#################################
# Collaboration Policy: You are encouraged to collaborate with up to 3 other
# students, but all work submitted must be your own independently written
# solution. List the computing ids of all of your collaborators in the comment
# at the top of your java or python file. Do not seek published or online
# solutions for any assignments. If you use any published or online resources
# (which may not include solutions) when completing this assignment, be sure to
# cite them. Do not submit a solution that you are unable to explain orally to a
# member of the course staff.
#################################
# Your Computing ID: hz9xs
# Collaborators: None
# Sources: Introduction to Algorithms, Cormen
#################################


class TilingDino:
    def __init__(self):
        return

    # This is the method that should set off the computation
    # of tiling dino.  It takes as input a list lines of input
    # as strings.  You should parse that input, find a tiling,
    # and return a list of strings representing the tiling
    #
    # @return the list of strings representing the tiling
    def compute(self, lines):
        #print(len(lines))
        #print(len(lines[0]))

        # if size of the black graph is odd, then there is no way we can do the tiling
        num = 0
        for a in range(len(lines)):
            for b in range(len(lines[0])):
                if (lines[a][b]=="#"):
                    num+=1
        if(num%2==1):
            #return ["1"]
            return ["impossible"]

        # given a graph, we need to find the useful points inside and classify them to left and right
        left = []
        right = []    
        for i in range(len(lines)):
            for j in range(len(lines[0])):
                if(i%2==0):
                    if (j%2==0 and lines[i][j]=="#"):
                        left.append((i,j))
                    if (j%2==1 and lines[i][j]=="#"):
                        right.append((i,j))
                if(i%2==1):
                    if (j%2==1 and lines[i][j]=="#"):
                        left.append((i,j))
                    if (j%2==0 and lines[i][j]=="#"):
                        right.append((i,j))
                        
        # if left length does not equal to right length, we can't pair every nodes
        if (len(left)!=len(right)):
            #return [str(len(left))+" "+str(len(right))]
            return ["impossible"]

        # if their length equals, we make the algo to solve problem
        # recursive call function used to determine whether a given left node can be matched to any avaliable right node
        def recursive(self, u, match, used_v):
            for v in range (len(right)):
                if (graph[u][v] and (used_v[v]==0)):
                    used_v[v] = 1
                    if ((match[v]==-1) or (recursive(self,match[v],match,used_v))):
                        match[v] = u
                        return True
            return False
        
        # construct the graph (the map between left node and right node)
        global graph 
        graph = [[0 for k in range(len(left))] for l in range(len(right))]
        for i in range(len(left)):
            items = left[i]
            for j in range(len(right)):
                if (items[0]+1<len(lines)):
                    if ((items[0]+1,items[1]) == right[j]):
                        graph[i][j] = 1
                if (items[0]-1>=0):
                    if ((items[0]-1,items[1]) == right[j]):
                        graph[i][j] = 1
                if (items[1]+1<len(lines[0])):
                    if ((items[0],items[1]+1) == right[j]):
                        graph[i][j] = 1
                if (items[1]-1>=0):
                    if ((items[0],items[1]-1) == right[j]):
                        graph[i][j] = 1
        #print(right)
        #print(graph)

        # here we check every possible left node and calculate the maximum number of left points that can be matched to the right counterpart
        # at the beginning, all target points do not have matches so their values are -1
        # and we need to use this match_point to trace back the edge
        global match
        match  = [-1]*len(right)

        # need a counter
        count = 0
        global used_v
        for p in range(len(left)):
            # initially all right points have not been seen so all 0 and we need to refresh this list for each loop
            used_v = [0]*len(right)
            if (recursive(self, p, match, used_v)==True):
                count+=1

        # if count does not equal to the number of left node, then not all points can be paired, then fail
        if (count != len(right)):
            #return ["123"]
            return ["impossible"]

        # if there is no black box in the graph, we should return impossible
        if (len(left)==0 or len(right)==0):
            #return ["1234"]
            return ["impossible"]

        # if count matches the number of node, then we trace back each edge and return the result
        result=[]
        for h in range(len(match)):
            # if there is some v matched to u, add it to the result
            if (match[h]!=-1):
                result.append(str(left[match[h]][1]) + " " + str(left[match[h]][0]) + " "+ str(right[h][1])+ " " + str(right[h][0]))
        #print(len(result))
        return result
                