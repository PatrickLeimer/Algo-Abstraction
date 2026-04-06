from pathlib import Path


def parseInputFile(path):
    tokens = path.read_text().split()

    k = int(tokens[0])
    sA = tokens[-2]
    sB = tokens[-1]

    # Middle section is K pairs: x1 v1 x2 v2 ... xK vK
    pair_tokens = tokens[1:1 + (2 * k)]
    keys = pair_tokens[0::2]
    vals = list(map(int, pair_tokens[1::2]))

    xDict = dict(zip(keys, vals))

    return k, sA, sB, xDict


def hvlcs(A, B, xDict):
    m, n = len(A), len(B)

    dp = [[0] * (n + 1) for _ in range(m + 1)] # Build 2d array

    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if A[i - 1] == B[j - 1]:
                dp[i][j] = dp[i - 1][j - 1] + xDict.get(A[i - 1], 0)
            else:
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])

    # Backtracking to get solution
    solution = []
    i, j = m, n
    while i > 0 and j > 0:
        if A[i - 1] == B[j - 1]:
            solution.append(A[i - 1])
            i -= 1
            j -= 1
        elif dp[i - 1][j] >= dp[i][j - 1]:
            i -= 1
        else:
            j -= 1

    solution.reverse()
    return dp[m][n], "".join(solution)


if __name__ == "__main__":
    path = Path(__file__).resolve().parent.parent / "example.in"
    k, sA, sB, xDict = parseInputFile(path)
    max_val, subseq = hvlcs(sA, sB, xDict)
    print(max_val)
    print(subseq)


    """
    dp[i][j] = max value of a common subsequence of sA[0..i-1] and sB[0..j-1]

    Recurrence:
      - If sA[i-1] == sB[j-1]:
            dp[i][j] = dp[i-1][j-1] + v(sA[i-1])
      - Else:
            dp[i][j] = max(dp[i-1][j], dp[i][j-1])

    Base case: dp[0][j] = dp[i][0] = 0 for all i, j
    """