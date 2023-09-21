class frequencyCounter:
    def freqCount(self, words):
        dic = {}
        for x in words:
            if x not in dic:
                dic[x] = words.count(x)
        return dic

    def printCount(self, words):
        dictionary = self.freqCount(words)
        print(dictionary)


wordArray = ["green", "yellow", "green", "red", "blue", "blue", "green"]

counter = frequencyCounter()

counter.printCount(wordArray)
