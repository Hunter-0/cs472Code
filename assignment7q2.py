class Shape: # https://www.geeksforgeeks.org/bridge-design-pattern/#
    def __init__(self, formatter): # https://refactoring.guru/design-patterns/bridge/python/example
        self.formatter = formatter

    def draw(self):
        pass


class Formatter:
    def formatCircle(self, x, y, radius):
        pass

    def formatSquare(self, x, y, side):
        pass

    def formatPolygon(self, points):
        pass


class ScreenFormatter(Formatter):
    def formatCircle(self, x, y, radius):
        print("Screen   : Drawing Circle at ({}, {}) with radius {}.".format(x, y, radius))

    def formatSquare(self, x, y, side):
        print("Screen   : Drawing Square at ({}, {}) with side length {}.".format(x, y, side))

    def formatPolygon(self, points):
        print("Screen   : Drawing Polygon with points {}".format(points))


class PrinterFormatter(Formatter):
    def formatCircle(self, x, y, radius):
        print("Printer  : Printing Circle at ({}, {}) with radius {}.".format(x, y, radius))

    def formatSquare(self, x, y, side):
        print("Printer  : Printing Square at ({}, {}) with side length {}.".format(x, y, side))

    def formatPolygon(self, points):
        print("Printer  : Printing Polygon with points {}.".format(points))


class XMLFormatter(Formatter):
    def formatCircle(self, x, y, radius):
        print("XML      : Constructing XML for Circle at ({}, {}) with radius {}.".format(x, y, radius))

    def formatSquare(self, x, y, side):
        print("XML      : Constructing XML for Square at ({}, {}) with side length {}.".format(x, y, side))

    def formatPolygon(self, points):
        print("XML      : Constructing XML for Polygon with points {}.".format(points))


class Circle(Shape):
    def draw(self, x, y, radius):
        self.formatter.formatCircle(x, y, radius)


class Square(Shape):
    def draw(self, x, y, side):
        self.formatter.formatSquare(x, y, side)


class Polygon(Shape):
    def draw(self, points):
        self.formatter.formatPolygon(points)


Circle(ScreenFormatter()).draw(250, 150, 50)
Square(PrinterFormatter()).draw(400, 400, 25)
Polygon(XMLFormatter()).draw([(100, 100), (200, 200), (300, 300)])
