from nltk import sent_tokenize

def lines(a, b):
    """Return lines in both a and b"""
    
    if a is None or b is None:
        return []
    lists = []
    for i in a.split("\n"):
        if i in b.split("\n") and not i in lists:
            lists.append(i)
    return lists


def sentences(a, b):
    """Return sentences in both a and b"""

    lists = []
    if a is None or b is None:
        return []
    
    for i in sent_tokenize(a):
        if i in sent_tokenize(b) and not i in lists:
            lists.append(i)
    return lists


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    if a is None or b is None:
        return []
    lists = []
    alist = []
    blist = []
    for i in range(0,len(a) - n + 1):
        alist.append(a[i : i + n])
    for i in range(0,len(b) - n + 1):
        blist.append(b[i : i + n])
    
    for i in alist:
        if i in blist and not i in lists:
            lists.append(i)
    return lists
