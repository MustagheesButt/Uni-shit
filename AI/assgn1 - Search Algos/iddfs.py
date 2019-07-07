import copy

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
    depth = 1

    status = DFS(init_config, depth)

    while status != True and depth <= 20:
        depth += 1
        status = DFS(init_config, depth)

def DFS(config, depth):
    stack = []
    stack.append([config])
    
    visited = []
    visited.append(config)
    
    while (len(stack) != 0):
        path = stack.pop()

        # depth check
        if len(path) > depth:
            continue
        
        # prepare to extend
        neighbours = get_neighours(path[len(path) - 1])

        # check if any neighbour is the goal, if not then extend
        for neighbour in neighbours:
            if neighbour == goal:
                print("Goal found at depth: " + str(depth))
                print(path + goal)
                return True
            elif neighbour not in visited:
                stack.append(path + [neighbour])
                visited.append(neighbour)
    
    # couldnt find goal
    return False

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

if __name__ == "__main__":
    main()