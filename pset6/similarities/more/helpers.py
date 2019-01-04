from enum import Enum


class Operation(Enum):
    """Operations"""

    DELETED = 1
    INSERTED = 2
    SUBSTITUTED = 3

    def __str__(self):
        return str(self.name.lower())
    
def print_m(matrix):
    for i in matrix:
        print(i)
    print(matrix)


def distances(a, b):
    """Calculate edit distance from a to b"""
    if a is None or b is None:
        return [[]]
    if a == "" and b == "":
        return [ [ (0,)]]
    
    matrix = [[0 for i in range(len(b) + 1)] for j in range(len(a) + 1)]
    for i in range(1, len(b) + 1):
        matrix[0][i] = (i, Operation.INSERTED)
    
    for i in range(1, len(a) + 1):
        matrix[i][0] = (i, Operation.DELETED)
    
    for i in range(1, len(a) + 1):
        for j in range(1,len(b) + 1):
            deletion, _ = matrix[i-1][j]
            insertion, _ = matrix[i][j-1]
            
            deletion += 1
            insertion += 1
            
            
            if matrix[i-1][j-1] == 0:
                substitution = 0
            else:
                substitution, _ = matrix[i-1][j-1]
            
            if not a[i - 1] == b[j - 1]:
                substitution += 1
            
            if min(deletion, insertion, substitution) == deletion:
                matrix[i][j] = (min(deletion, insertion, substitution), Operation.DELETED)
            elif min(deletion, insertion, substitution) == insertion:
                matrix[i][j] = (min(deletion, insertion, substitution), Operation.INSERTED)
            else:
                matrix[i][j] = (min(deletion, insertion, substitution), Operation.SUBSTITUTED)
    
    matrix[0][0] = (0,None)
    return matrix