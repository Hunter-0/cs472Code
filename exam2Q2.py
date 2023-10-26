def openCsvData(filename):
    data = []  # https://stackoverflow.com/questions/77056038/reading-file-and-list-tuple-iteration
    with open(filename, 'r') as file:
        for line in file:
            line = line.strip()
            x, y = map(int, line.split(','))
            data.append((x, y))
    print(data)


csvfile = "e2p2data.csv"
openCsvData(csvfile)

