# besozad zendan, sokht jegram

import copy
import random
import math
import sys

# define basic parameter
Temp = 1.0
zarib = 0.99



def get_sudoku(sudoku):
    """get sudoku in fortmat of number and dots"""
    sudoku_grid = [int(char) for char in sudoku]

    # Convert the list of integers to a 2D list (9x9 grid)
    sudoku_2d_grid = [sudoku_grid[i:i+9] for i in range(0, 81, 9)]

    return sudoku_2d_grid


def print_sudoku(sudoku) : 
    """ print out the sudoku"""
    print("\n\n\n")
    for i in range(9):
        line = ""
        if i == 3 or i == 6:
            print("------+-------+------")

        for j in range(9):
            if j == 3 or j == 6:
                line += "| "
            line += str(sudoku[i][j]) + " "

        print(line)


def sudoku_initial_state(sudoku):
    """change all the number of suduku to `1` to mark the place"""
    for i in range(9):
        for j in range(9):
            if sudoku[i][j] != 0:
                    sudoku[i][j] = 1
    return sudoku


def batman_filler(sudoku):
    """fill sudoku with random number that are not repeated in the 3x3 block that they are in"""

    # two dynamic nasty for loop to procees each block
    for i in range(0,9,3):
        for j in range(0,9,3):
            lst = []

            # check list for existing number and add them into `lst`
            for z in range(i,i+3):
                for h in range(j,j+3):
                    if sudoku[z][h] != 0:
                        lst.append(sudoku[z][h])

            # fill sudoku block with random int that not exist in the block 
            for z in range(i,i+3):
                for h in range(j,j+3):
                        
                        # an loop to generate first non-exist number in range 1-9 that not exist in `lst`
                        if  sudoku[z][h] == 0:

                            while True:
                                x = random.randint(1,9)
                                if x not in lst:
                                    lst.append(x)
                                    sudoku[z][h] = x
                                    break
    return sudoku


def cost_calculator(sudoku):
    """calculate the cost with below algorithm:
    - if a number was repeated in row or column
    - if a number was repeated in 3x3"""
    cost = 0
    for i in sudoku:
        cost += 9 - len(list(set(i)))

    for j in range(0,9):
        lst = []
        for m in range(0,9):
            lst.append(sudoku[m][j])    
        cost += 9- len(list(set(lst)))
    
    return cost



def random_successor(sudoku,state_sudoku):
    """
    - first choose an random block and ensure that have an blank cell in it
    - second choose tow random cell in that block and ensures that they are not the given number
    - third change their value with each other
    """

    # choose a random block
    flag = 1
    while flag:
        random_block_row = random.choice((0,3,6))
        random_block_column = random.choice((0,3,6))

        for i in state_sudoku[random_block_row:random_block_row+3]:
            if 1 in i[random_block_column:random_block_column+3]:
                flag = 0
                break
                
    # choose Two random cell in above block
    ## first one
    while True:
        random_cell_row_one = random.randint(random_block_row,random_block_row+2)
        random_cell_column_one = random.randint(random_block_column,random_block_column+2)
        if state_sudoku[random_cell_row_one][random_cell_column_one] != 1:
            break
    
    ## second one
    while True:
        random_cell_row_two = random.randint(random_block_row,random_block_row+2)
        random_cell_column_two = random.randint(random_block_column,random_block_column+2)
        if state_sudoku[random_cell_row_two][random_cell_column_two] != 1 and (random_cell_row_two != random_cell_row_one or random_cell_column_two != random_cell_column_one):
            break
    

    # change their value with each other
    tempnum = sudoku[random_cell_row_one][random_cell_column_one]
    sudoku[random_cell_row_one][random_cell_column_one] = sudoku[random_cell_row_two][random_cell_column_two]
    sudoku[random_cell_row_two][random_cell_column_two] = tempnum

    return sudoku


def probility(new_cost, old_cost, T):
    """calculate the probility of accept"""
    global flag_for_stuck_reset
    cost_differ = -1 * (new_cost - old_cost)
    power = cost_differ / T
    x = math.exp(power)
    print(f"pr : {x} , cost diffr : {cost_differ}")
    return x


def successor_handler(sudoku, state_sudoku,zarib, T, cost):
    """handle accepting the new state and genrating new state"""

    # genrate new state
    temp_sudoku = random_successor(copy.deepcopy(sudoku),state_sudoku)
    
    # calculate the cost
    new_cost = cost_calculator(temp_sudoku)

    if new_cost < cost :
        # accept the new state
        return temp_sudoku, new_cost, T * zarib
    else:
        # check the probility and accept if it was true
        if probility(new_cost, cost, T) >= random.uniform(0,1):
            return temp_sudoku, new_cost, T * zarib
        else:
            # rejecting the new state
            return sudoku, cost, T



def root():
    global Temp,zarib
    
    # getting sudoku from user
    sudoku_input = sys.argv[1]
    main_sudoku = get_sudoku(sudoku_input)

    # print the given sudoku
    print_sudoku(main_sudoku)

    # building the fixed sudoku
    sudoku_state = copy.deepcopy(main_sudoku)
    sudoku_state = sudoku_initial_state(sudoku_state)

    # ranomlly fill sudoku
    main_sudoku = batman_filler(main_sudoku)
    print_sudoku(main_sudoku)

    # calculate the inial cost 
    cost = cost_calculator(main_sudoku)

    # counter for when it get stuck in a local minimum
    stuck_counter = 0 

    # genrate new state and calculate the cost 
    while cost != 0:

        old_cost = cost

        # randomlly generate a new state 
        main_sudoku, cost, Temp = successor_handler(main_sudoku,sudoku_state, zarib,Temp,cost)

        # print cost to track the process
        print(f"Cost: {cost}, Temp: {Temp}\n\n")

        # to increase `stuck_counter` when it get stuck in one cost
        if old_cost == cost:
            stuck_counter += 1
        else:
            stuck_counter = 0
        
        # check if the algorithm stuck, then increase temp 
        if stuck_counter >= 80:
            print(stuck_counter)

            if cost >= 6: 
                Temp += 0.05
            else:
                Temp += 0.005
            stuck_counter = 0
    
    # print the sudoku in a pretty formt
    print_sudoku(main_sudoku)


if __name__ == "__main__":
    root()

# good example to give run algorithm with
"""run program like this
python3 sudoku-SA.py 000150704000070000006400000050007000048000000010503060500900007003000009000680501
"""
