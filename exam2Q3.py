def openCsvData(filename):
    data = []  # https://stackoverflow.com/questions/77056038/reading-file-and-list-tuple-iteration
    with open(filename, 'r') as file:
        for line in file:
            line = line.strip()
            x, y = map(int, line.split(','))
            data.append((x, y))
    return data


def doMath(x, y, z):
    a, b = x
    z0, z1 = z
    c = y
    result = a * z0 + b * z1 - c
    if result > 0:
        return 1
    elif result < 0:
        return -1
    else:
        return 0


def convexHull(points):
    n = len(points)
    hullPoints = []

    for i in range(n):
        for j in range(i + 1, n):
            sameSide = False

            for k in range(n):
                if k != i and k != j:
                    sideResult = doMath(points[i], points[j], points[k])
                    if sideResult != 0:
                        if sideResult == doMath(points[i], points[j], points[k - 1]):
                            sameSide = True

            if sameSide:
                if points[i] not in hullPoints:
                    hullPoints = hullPoints + [points[i]]
                if points[j] not in hullPoints:
                    hullPoints = hullPoints + [points[j]]

    return hullPoints


csvfile = "e2p2data.csv"
csvData = openCsvData(csvfile)
hullPoints = convexHull(csvData)

for point in hullPoints:
    print(point)
