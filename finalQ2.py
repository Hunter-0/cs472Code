class Builder:
    def getWheel(self):
        pass

    def getContainer(self):
        pass

    def getBody(self):
        pass


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


class ConcreteBuilderType2(Builder):
    def __init__(self):
        self.widget = Widget()

    def getWheel(self):
        self.widget.attachWheel(Wheel(size=6))

    def getContainer(self):
        self.widget.setContainerVolume(Container(volume=4))

    def getBody(self):
        self.widget.setBody(Body(shape="sphere"))

    def getResult(self):
        return self.widget
