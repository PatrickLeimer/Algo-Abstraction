from pathlib import Path


def parseInputFile(path):
    tokens = path.read_text().split()
    print(f"Tokens: {tokens}")

    k = int(tokens[0])
    sA = tokens[-2]
    sB = tokens[-1]

    # Middle section is K pairs: x1 v1 x2 v2 ... xK vK
    pair_tokens = tokens[1:1 + (2 * k)]
    keys = pair_tokens[0::2]
    vals = list(map(int, pair_tokens[1::2]))
    print(f"Keys: {keys}, Values: {vals}")
    
    xDict = dict(zip(keys, vals))

    print(f"k: {k}, sA: {sA}, sB: {sB}, xDict: {xDict}")
    return k, sA, sB, xDict



if __name__ == "__main__":
    path = Path(__file__).resolve().parent.parent / "example.in"
    k, sA, sB, xDict = parseInputFile(path)