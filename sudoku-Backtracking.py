#sudoku phase1

def get_input():
    """Get the Puzzle in one line format.
    Example's:
    - ....49..2
    - .5.4....."""
    board = []
    print("Enter puzzle in one line format:\n")
    for i in range(9):
        i = input(">")
        tmp = []
        for j in i:
            if j ==".":
                tmp.append(0)
            else:
                tmp.append(int(j))
        board.append(tmp)
    return board


def print_board(board):
    """Prints the given `board`"""
    print("\t\tSOLVED PUZZLE:")
    print("+","-"*5,"+","-"*5,"+","-"*5,"+")
    for i in range(9):
        print("|", end=" ")
        for j in range(9):
            print(board[i][j] , end=" ")
            if (j+1)%3==0 and j>0 and j <7:
                print("|", end=" ")
        print("|")
        if (i+1)%3==0 and i>0:
            print("+","-"*5,"+","-"*5,"+","-"*5,"+")


def is_right(board, row, column, x):
    """check if x is valid for the cell in the given `row` and `column`"""
    # check row and column
    if x in board[row]:
        return False
    
    for i in range(9):
        if board[i][column] == x:
            return False
    
    # check the smaller square
    row_s = 3 * (row // 3)
    column_s = 3 * (column // 3)
    for i in range(row_s, row_s + 3):
        for j in range(column_s, column_s + 3):
            if board[i][j] == x:
                return False
    return True


def empty(board):
    """it will look for an empty cell and in case couldn't find it, it will return '-','-' """
    for i in range(9):
        for j in range(9):
            if board[i][j] == 0:
                return i,j
    return "-","-"


def solver(board):
    """solver is used to solve the puzzle"""
    row,column = empty(board)
    if row == '-':
        return True
    for x in range(1,10):
        if is_right(board, row, column, x):
            board[row][column] = x
            if solver(board) :
                return board
            else:
                board[row][column] = 0
    return False


def runner():
    board = get_input()
    result = solver(board) 
    if result :
        print("HUH i solve it. i guess im brilliant :/")
        print_board(board)
    else:
        print("cant solve it.")

runner()
