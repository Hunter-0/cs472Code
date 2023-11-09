class Square: # https://refactoring.guru/design-patterns/command/python/example
    def __init__(self, i, j, k):
        self.number = i
        self.x = j
        self.y = k
        self.length = 0

    def scale(self, factor):
        self.length *= factor

    def move(self, newX, newY):
        self.x = newX
        self.y = newY


class Command:
    def execute(self):
        pass

    def undo(self):
        pass


class Create(Command):
    def __init__(self, sgms, i, j):
        self.sgms = sgms
        self.i = i
        self.j = j

    def execute(self):
        self.sgms.createSquare(self.i, self.j)

    def undo(self):
        self.sgms.removeSquare(self.i)


class Move(Command):
    def __init__(self, sgms, i, j, k):
        self.sgms = sgms
        self.i = i
        self.j = j
        self.k = k
        self.old = None

    def execute(self):
        self.old = (self.i, self.sgms.squares[self.i].x, self.sgms.squares[self.i].y)
        self.sgms.moveSquare(self.i, self.j, self.k)

    def undo(self):
        i, j, k = self.old
        self.sgms.moveSquare(i, j, k)


class Scale(Command):
    def __init__(self, sgms, i, j):
        self.sgms = sgms
        self.i = i
        self.j = j
        self.old = None

    def execute(self):
        self.old = (self.i, self.sgms.squares[self.i].length)
        self.sgms.scaleSquare(self.i, self.j)

    def undo(self):
        i, j = self.old
        self.sgms.scaleSquare(i, j)


class RedoSquare(Command):
    def execute(self):
        if self.sgms.lastUndo is not None:
            self.sgms.doCommand(self.sgms.lastUndo)


class SGMS:
    def __init__(self):
        self.squares = {}
        self.history = []
        self.counter = -1
        self.lastUndo = None

    def createSquare(self, i, j):
        square = Square(i, 0, 0)
        square.length = j
        self.squares[i] = square

    def moveSquare(self, i, j, k):
        if i in self.squares:
            square = self.squares[i]
            square.move(j, k)
        else:
            print("Square {} not found.".format(i))

    def scaleSquare(self, i, j):
        if i in self.squares:
            square = self.squares[i]
            square.scale(j)
        else:
            print("Square {} not found.".format(i))

    def removeSquare(self, i):
        if i in self.squares:
            del self.squares[i]

    def doCommand(self, command):
        self.counter += 1
        if self.counter < len(self.history):
            self.history = self.history[:self.counter]

        command.execute()
        self.history.append(command)
        self.lastUndo = None

    def undoCommand(self):
        if self.counter >= 0:
            lastCommand = self.history[self.counter]
            lastCommand.undo()
            self.counter -= 1
            self.lastUndo = lastCommand

    def RedoSquare(self):
        if self.counter < len(self.history) - 1:
            self.counter += 1
            nextCommand = self.history[self.counter]
            nextCommand.execute()
            self.lastUndo = nextCommand

    def printSquares(self):
        print("Square number, center points of square, length")
        for i, square in self.squares.items():
            print("({}, {}, {}, {})".format(i, square.x, square.y, square.length))


sgms = SGMS()

while True:
    print("C i j    : Create square i at (0,0) with length j.")
    print("M i j k  : Move square i to (j, k).")
    print("S i j    : Scale square i by j. Positives make it larger, negatives make it smaller.")
    print("U        : Undo the last C, M, or S command.")
    print("R        : Redo last command that was undone, only valid after a U command.")
    print("P        : Print statistics for all squares in system.")
    print("X        : End program.")

    index = input("Enter a command: ").split()

    cmd = index[0].lower()
    if cmd == "c":
        i = int(index[1])
        j = int(index[2])
        create = Create(sgms, i, j)
        sgms.doCommand(create)
    elif cmd == "m":
        i = int(index[1])
        j = int(index[2])
        k = int(index[3])
        move = Move(sgms, i, j, k)
        sgms.doCommand(move)
    elif cmd == "s":
        i = int(index[1])
        j = float(index[2])
        scale = Scale(sgms, i, j)
        sgms.doCommand(scale)
    elif cmd == "u":
        sgms.undoCommand()
    elif cmd == "r":
        sgms.RedoSquare()
    elif cmd == "p":
        sgms.printSquares()
    elif cmd == "x":
        break
    else:
        print("Error, enter a valid option.")
