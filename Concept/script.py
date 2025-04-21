

from typing import Iterable

SAT_INDEXES: list[tuple[int,int]] = [
    (1,5),
    (2,6),
    (3,7),
    (4,8),
    (0,8),
    (1,9),
    (0,7),
    (1,8),
    (2,9),
    (2,9),
    (1,2),
    (2,3),
    (4,5),
    (5,6),
    (6,7),
    (7,8),
    (8,9),
    (0,3),
    (1,4),
    (2,5),
    (3,6),
    (4,7),
    (5,8),
    (0,2),
    (3,5),
]


def xorNext(sequence: list[int], valueIndexes: Iterable[int]) -> int:
    xorValue = False
    for index in valueIndexes:
        xorValue ^= True if sequence[index] == 1 else False
    return int(xorValue)

def rotateNext(sequence: list[int], nextValueIndexes: Iterable[int]) -> list[int]:
    first = xorNext(sequence, nextValueIndexes)
    newSequence = [first] + sequence[:-1]
    return newSequence


def generateSequences(satValueIndexes: list[tuple[int,int]]) -> list[list[int]]:
    motherSequence = [1] * 10

    sequences: list[list[int]] = []
    
    specialSequences: list[list[int]] = []
    for _ in satValueIndexes:
        specialSequences.append([1] * 10)
        sequences.append([])

    
    for _ in range(1023):
        for index, pair in enumerate(satValueIndexes):
            specialSequence = specialSequences[index]
            motherSequenceValue = motherSequence[-1]
            specialSequenceValue = xorNext(specialSequence, pair)
            nextValue = motherSequenceValue ^ specialSequenceValue
            sequences[index].append(nextValue)
            specialSequences[index] = rotateNext(specialSequence, [1,2,5,7,8,9])

            

        motherSequence = rotateNext(motherSequence, [2,9])

    return sequences

def scalarProduct(a: list[int], b: list[int]) -> int:
    return sum(x * y for x, y in zip(a, b))

def convertSequence(seq: list[int]) -> list[int]:
    return [-1 if s == 0 else 1 for s in seq]

def crossCorrelate(sequences: list[list[int]], sumSignal: list[int]):
    scalars: list[list[int]] = [[] for _ in range(len(sequences))]
    min = [(0, 0) for _ in range(len(sequences))]
    max = [(0, 0) for _ in range(len(sequences))]
    for d in range(len(sumSignal)):
        for index, sequence in enumerate(sequences):
            sequence = convertSequence(sequence)
            scalar = scalarProduct(sequence, sumSignal)

            if scalar < min[index][0]:
                min[index] = (scalar, d)
            if scalar > max[index][0]:
                max[index] = (scalar, d)


            scalars[index].append(scalar)
        
        sumSignal = [sumSignal[-1]] + sumSignal[:-1]
            
    for i in range(len(min)):
        print(f"SAT {i}: min: {min[i][0]} (delta {min[i][1]}) | max: {max[i][0]} (delta {max[i][1]})")
    # print(scalars)


def readFile(filename: str) -> list[int]:
    with open(filename, "r") as file:
        lines = file.readlines()
        line = lines[0]
        return [int(s) for s in line.split(" ") if s]

if __name__ == "__main__":
    sequences = generateSequences(SAT_INDEXES)
    sumSignal = readFile("gps_sequence_1.txt")

    crossCorrelate(sequences, sumSignal)
