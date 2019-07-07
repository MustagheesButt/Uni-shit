import copy
import math
from collections import deque

init_config = [
    ['8', '4', '7'],
    ['1', '6', '5'],
    ['2', '3', ' ']
]

goal = [
    ['1', '8', '7'],
    ['2', ' ', '6'],
    ['3', '4', '5']
]

def main():
    BestFS(init_config)

def BestFS(config):
    queue = deque()
    queue.append([config])
    
    visited = []
    visited.append(config)
    
    while (len(queue) != 0):
        path = queue.popleft()
        parent = copy.deepcopy(path[len(path) - 1])

        # prepare to extend
        neighbours = get_neighours(parent)
        
        scores = []
        for neighbour in neighbours:
            scores.append(calc_score(neighbour))
        
        # sort according to heuristic scores
        sorted_neighbours = [x for _,x in sorted(zip(scores, neighbours))]

        # check if any neighbour is the goal, if not then extend
        for neighbour in sorted_neighbours:
            if neighbour == goal:
                print("Goal found at depth: " + str(len(path)))
                print(path + goal)
                return len(path)
            elif neighbour not in visited:
                queue.append(path + [neighbour])
                visited.append(neighbour)
    
    # couldnt find goal
    print("Could not find goal.")
    return -1

# computes all possible mutations of given config
def get_neighours(config):
    mutations = []
    for i in range(3):
        if ' ' in config[i]:
            j = config[i].index(' ')
            new_moves = [
                (i - 1, j), (i + 1, j),
                (i, j + 1), (i, j - 1)
            ]

            for a, b in new_moves:
                if (a >= 0 and b >= 0) and (a < 3 and b < 3):
                    temp = copy.deepcopy(config)
                    temp[i][j], temp[a][b] = temp[a][b], temp[i][j]
                    mutations.append(temp)
            break
    
    return mutations

# heuristic function
def calc_score(config):
   #return tiles_in_place(config)
   #return manhattan_distance(config)
   return euclidean_distance(config)

def g (config):
    return 0

def manhattan_distance(config):
    sum = 0

    for i in range(3):
        for j in range(3):
            for k in range(3):
                for l in range(3):
                    if goal[i][j] != ' ' and goal[i][j] == config[k][l]:
                        sum += (abs(i - k) + abs(j - l))

    return sum

def euclidean_distance(config):
    sum = 0

    for i in range(3):
        for j in range(3):
            for k in range(3):
                for l in range(3):
                    if goal[i][j] != ' ' and goal[i][j] == config[k][l]:
                        sum += math.sqrt((i - k)**2 + abs(j - l)**2)

    return sum

def tiles_in_place(config):
    score = 0
    for i in range(3):
        for j in range(3):
            if config[i][j] == goal[i][j]:
                score += 1

    return score

if __name__ == "__main__":
    main()