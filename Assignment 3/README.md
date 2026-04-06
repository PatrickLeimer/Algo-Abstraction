# Assignment 3 - Highest Value Longest Common Sequence

## Student Information
- Patrick Leimer — UFID: 88717127
- Julio Andres Leonardi — UFID: 78976797

## Problem Summary
Given two strings A and B over a fixed alphabet where each character has a nonneg integer value, compute a common subsequence of A and B that maximizes total value. Output the maximum value and one optimal subsequence.

## Repository Layout
```
Assignment 3/
├── src/
│   └── main.py              # HVLCS implementation
├── q1nputFiles/
│   └── 1.in – 10.in         # Nontrivial test inputs (strings of length ≥ 25)
├── example.in               # Worked example from assignment
├── *.out                    # Generated output files (created on run)
└── Question 1 - Sheet1.pdf  # Runtime graph for Question 1
```

## Dependencies
- Python 3.x (no third-party libraries required)

## How to Run
Run all `.in` files in the `Assignment 3` directory and generate corresponding `.out` files:

```bash
python "Assignment 3/src/main.py"
```

To reproduce the worked example specifically:
```bash
# example.in is in Assignment 3/ — running main.py picks it up automatically
python "Assignment 3/src/main.py"
# Output written to Assignment 3/example.out
```

## Example Input (`example.in`)
```
3
a 2
b 4
c 5
aacb
caab
```

## Expected Output (`example.out`)
```
9
cb
```
Val(cb) = 5 + 4 = 9.

## Assumptions
- All character values are nonneg integers.
- Input files follow the format exactly: K, then K lines of `char value`, then string A, then string B.
- Characters not listed in the alphabet default to value 0.
- If multiple optimal subsequences exist, any one is acceptable.

---

## Written Component

### Question 1: Empirical Comparison
See `Question 1 - Sheet1.pdf` for the runtime graph across 10 nontrivial input files (strings of length ≥ 25). Runtimes were measured using `time.perf_counter()` around the core `hvlcs()` call and printed to stdout when running `main.py`.

### Question 2: Recurrence Equation

Let `dp[i][j]` = maximum value of any common subsequence of `sA[0..i-1]` and `sB[0..j-1]`.

**Recurrence:**
```
           { 0                                  if i = 0 or j = 0
dp[i][j] = { dp[i-1][j-1] + v(sA[i-1])         if sA[i-1] == sB[j-1]
           { max(dp[i-1][j], dp[i][j-1])         otherwise
```

**Base case:** `dp[0][j] = dp[i][0] = 0` for all i, j — an empty string has no common subsequence.

**Correctness:** When two characters match, we extend the best solution found so far by including that character's value; when they don't, we take the best solution achievable by skipping one character from either string — covering all possible cases exhaustively.

**Worked example table** (sA = `aacb`, sB = `caab`):
```
      ""   a    a    c    b
  ""   0   0    0    0    0
   c   0   0    0    5    5
   a   0   2    2    5    5
   a   0   2    4    5    5
   b   0   2    4    5    9
```
Answer: `dp[4][4] = 9`, traceback gives subsequence `cb`.

### Question 3: Big-Oh

**Runtime:** O(m · n), where m = |A| and n = |B|.

We fill an (m+1) × (n+1) table with each cell taking O(1) work, and the backtrack traversal is O(m + n). The dominant term is O(m · n).
