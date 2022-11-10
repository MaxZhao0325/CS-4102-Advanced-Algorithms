# CS4102 Spring 2022 -- Unit C Programming
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

import math
# reverse the list
def Reverse(lst):
    return [ele for ele in reversed(lst)]

# get the width of the image
def getWidth(image):  
    return len(image[0])

# get the height of the image
def getHeight(image):  
    return len(image)

class SeamCarving:
    def __init__(self):
        return

    # This method is the one you should implement.  It will be called to perform
    # the seam carving.  You may create any additional data structures as fields
    # in this class or write any additional methods you need.
    # 
    # @return the seam's weight
    def run(self, image):
        # the array that contains the seam
        global a
        a=[]

        # get width of the image
        global width 
        width = getWidth(image)
        #print (width)
        # get height of the image
        global height
        height = getHeight(image)
        #print (height)
        # set global memory 
        global memory 
        memory = [[0 for j in range(width)] for i in range(height)]
        for i in range(width):
            for j in range(height):
                # first is cumulative weight, second is for backtracking
                memory[j][i] = (-1, -1)
        #print(memory)
        # Get the energy of a pixel
        def getEnergy(j, i):
            sum = 0.0
            for x in range (max(j-1, 0), min(j+1, height-1)+1):
                for y in range (max(i-1, 0), min(i+1, width-1)+1):
                    sum += math.sqrt(pow((image[x][y][0] - image[j][i][0]),2) + pow((image[x][y][1] - image[j][i][1]),2) + pow((image[x][y][2] - image[j][i][2]),2))
            if ((j==0 and i==0) or (j==0 and i == (width-1)) or (j==(height-1) and i==0) or (j==(height-1) and i==(width-1))):
                return sum/3
            elif (j==0 or i==0 or j == (height-1) or i == (width-1)):
                return sum/5
            else:
                return sum/8
        

        # recursiveStructure for DP
        def recursiveCall(j, i):
            #if (i<0 or i>=width):
            #    return 10000000000.0
            #if (memory[j][i][0]!=-1):
            #    return memory[j][i][0]
            #if (j == 0):
            #    memory[j][i] = (getEnergy(j,i), getEnergy(j,i))
            #    return getEnergy(j,i)
            #memory[j][i] = (min(min(recursiveCall(j-1, i-1)+getEnergy(j, i), recursiveCall(j-1, i)+getEnergy(j, i)), recursiveCall(j-1, i+1)+getEnergy(j, i)), getEnergy(j,i))            
            #return memory[j][i][0]
            return 0

        # bottom-up method
        def bottom_up():
            for k in range(0, width):
                memory[0][k] = (getEnergy(0,k), getEnergy(0,k))
            for j in range(1, height):
                for i in range(0, width):
                    if (i-1<0):
                        memory[j][i] = (min(memory[j-1][i][0]+getEnergy(j, i), memory[j-1][i+1][0]+getEnergy(j, i)), getEnergy(j,i))
                    elif (i+1>=width):
                        memory[j][i] = (min(memory[j-1][i-1][0]+getEnergy(j, i), memory[j-1][i][0]+getEnergy(j, i)), getEnergy(j,i))
                    else:
                        memory[j][i] = (min(min(memory[j-1][i-1][0]+getEnergy(j, i), memory[j-1][i][0]+getEnergy(j, i)), memory[j-1][i+1][0]+getEnergy(j, i)), getEnergy(j,i))

        bottom_up()
        # find least energy seam
        weight = 10000000.0
        #for k in range(0, width):
            #recursiveCall(height-1,k)
        
        for p in range(0, width):
            if (memory[height-1][p][0] < weight):
                weight = memory[height-1][p][0]

        backtrack = weight
        start = -1
        for i in range (0, width):
            if (memory[height-1][i][0]==backtrack):
                a.append(i)
                start = i
                backtrack-=memory[height-1][i][1]
                break
        #print(start)
        for j in range (height-2, -1, -1):
            if ((start < width) and (start >= 0)):
                if ((abs(memory[j][start-1][0]-backtrack)<0.00000000001) and (start-1 >= 0)):
                    a.append(start-1)
                    start -=1
                    backtrack-=memory[j][start][1]
                elif (abs(memory[j][start][0]-backtrack)<0.00000000001):
                    a.append(start)
                    backtrack-=memory[j][start][1]
                elif ((abs(memory[j][start+1][0]-backtrack)<0.00000000001) and (start+1<width)):
                    a.append(start+1)
                    start+=1
                    backtrack-=memory[j][start][1]
        return weight


    # Get the seam, in order from top to bottom, where the top-left corner of the
    # image is denoted (0,0).
    # 
    # Since the y-coordinate (row) is determined by the order, only return the x-coordinate
    # 
    # @return the ordered list of x-coordinates (column number) of each pixel in the seam
    #         as an array
    # Reversing a list using reversed()

    def getSeam(self):
        return Reverse(a)


    
    


