# Assignment 3 - Highest Value Longest Common Sequence

## Student Information
- Name(s): Julio Andres Leonardi - UFID: 78976797
- Name(s): Patrick Leimer - UFID: 88717127

## Problem Summary

## Repository Layout

## Build / Dependencies
- Python 3.x

## How to Run
Run all `.in` files in `Assignment 3` and generate corresponding `.out` files:

```bash
python "Assignment 3/main.py"
```

## Input Format
Each input file uses:

```text
K
x1 v1
x2 v2
...
xK vK
A
B
```

Where:
- `K` is the number of characters in the alphabet
- Each of the next `K` lines contains a character and its value
- `A` is the first string
- `B` is the second string

## Output Format

For each input file, print:

```text
(a single integer)
(one optimal common subsequence)
```

Specifically:

```text
9
cb
```

Where:
- The first line is the maximum value of a common subsequence of `A` and `B`.
- The second line is one optimal common subsequence that achieves this value.
- If multiple optimal subsequences exist, any one may be printed.

## Reproducibility
A grader can:
1. `git clone https://github.com/PatrickLeimer/Algo-Abstraction.git`
2. Run `python "Assignment 3/main.py"`
3. Verify generated `.out` files match expected results shown above.
