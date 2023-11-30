class Wheel:
    def __init__(self, size=None):
        self.size = size


class Container:
    def __init__(self, volume=None):
        self.volume = volume


class Body:
    def __init__(self, shape=None):
        self.shape = shape


class Builder:
    def getWheel(self):
        pass

    def getContainer(self):
        pass

    def getBody(self):
        pass


class Widget:
    def __init__(self):
        self.wheels = list()
        self.container = None
        self.body = None

    def attachWheel(self, wheel):
        self.wheels.append(wheel)

    def setContainerVolume(self, volume):
        self.container = volume

    def setBody(self, bodytype):
        self.body = bodytype

    def createWidget(self, builder):
        builder.getWheel()
        builder.getContainer()
        builder.getBody()
        return builder.getResult()


class ConcreteBuilder(Builder):
    def __init__(self):
        self.widget = Widget()

    def getWheel(self):
        self.widget.attachWheel(Wheel(size=4))

    def getContainer(self):
        self.widget.setContainerVolume(Container(volume=5))

    def getBody(self):
        self.widget.setBody(Body(shape="bucket"))

    def getResult(self):
        return self.widget


finishedWidget = Widget().createWidget(ConcreteBuilder())
