class Subject:
    # https://sourcemaking.com/design_patterns/observer/python/1
    # https://www.geeksforgeeks.org/observer-method-python-design-patterns/
    # https://www.linkedin.com/advice/3/how-do-you-implement-observer-pattern-python-skills-programming
    def __init__(self):
        self.observers = []
        self.data = {}

    def register(self, observer):
        self.observers.append(observer)

    def notifyAll(self, key, value):
        for observer in self.observers:
            observer.notify(self, key, value)

    def changeData(self, key, value):
        if key in self.data and self.data[key] != value:
            self.data[key] = value
            self.notifyAll(key, value)
        elif key not in self.data:
            self.data[key] = value
            self.notifyAll(key, value)


class Observer1:
    def notify(self, subject, key, value):
        print(type(self).__name__, ':: Got :', key, 'set to', value, 'From', subject.__class__.__name__)


class Observer2:
    def notify(self, subject, key, value):
        print(type(self).__name__, ':: Got :', key, 'set to', value, 'From', subject.__class__.__name__)


if __name__ == "__main__":
    subject = Subject()

    observer1 = Observer1()
    observer2 = Observer2()

    subject.register(observer1)
    subject.register(observer2)

    subject.changeData("dictMk1", "valueType1")
    subject.changeData("dictMk2", "valueType2")
    subject.changeData("dictMk1", "ValueType3")
