# Assignment 2 - Cache Eviction Policies

## Student Information
- Name(s): Julio Andres Leonardi - UFID: 78976797
- Name(s): Patrick Leimer - UFID: 88717127

## Problem Summary
This project implements and compares three cache eviction policies on the same request sequence:
- FIFO (First-In, First-Out)
- LRU (Least Recently Used)
- OPTFF (Belady's farthest-in-future optimal offline policy)

For each request:
- Hit: requested item is already in cache
- Miss: requested item is not in cache, so it must be inserted (and one item is evicted if the cache is full)

## Repository Layout
- `cache.py` - implementation and runner
- `example.in`, `example1.in`, `example2.in`, `q2BadSeq.in` - input files
- `example.out`, `example1.out`, `example2.out`, `q2BadSeq.out` - generated outputs

## Build / Dependencies
- Python 3.x
- Standard library only (`pathlib`, `queue`, `argparse`)

## How to Run
Run all `.in` files in `Assignment 2` and generate corresponding `.out` files:

```bash
python "Assignment 2/cache.py"
```

## Input Format
Each input file uses:

```text
k m
r1
r2
...
rm
```

Where:
- `k >= 1` is cache capacity
- `m >= 0` is number of requests
- The file must contain exactly `m` request IDs after the first line

## Output Format
For each input file:

```text
FIFO  : <number_of_misses>
LRU   : <number_of_misses>
OPTFF : <number_of_misses>
```

## Written Component

### Question 1: Empirical Comparison
Using three nontrivial input files (`m >= 50`):

| Input File | k | m   | FIFO | LRU | OPTFF |
|---|---:|---:|---:|---:|---:|
| `example.in`  | 5 | 60  | 27  | 30  | 19 |
| `example1.in` | 3 | 200 | 159 | 164 | 98 |
| `example2.in` | 8 | 100 | 47  | 56  | 26 |

Comments:
- OPTFF has the fewest misses on all three files.
- FIFO outperforms LRU on these specific sequences.
- In general, FIFO vs LRU depends on the request pattern; one is not always better than the other.

### Question 2: Bad Sequence for LRU or FIFO (k = 3)
A sequence where OPTFF is strictly better than LRU exists.

Use:

```text
k = 3
requests: 1, 2, 3, 4, 1, 2, 3, 4
```

Observed misses (`q2BadSeq.in`):
- FIFO: 8
- LRU: 8
- OPTFF: 5

Reasoning:
- LRU/FIFO make local eviction choices that cause repeated faults in this cycle.
- OPTFF evicts the page whose next use is farthest in the future, preventing some near-future misses.

### Question 3: Proof that OPTFF is Optimal (Exchange Argument)
Let OPTFF be Belady’s Farthest-in-Future algorithm.  
Let ( A ) be any offline algorithm that knows the full request sequence.  
Prove that the number of misses of OPTFF is no larger than that of ( A ) on any fixed sequence.

Proof (by contradiction):
- Assume OPTFF is not optimal, in this case, that the number of misses of OPTFF is larger than that of an optimal offline algorithm A* on a fixed sequence.
- Let $i_1, i_2,...$ be OPTFF's evictions (upon missing), and let $j_1, j_2,...$ be those evictions of an optimal offline algorithm A*.
- Choose A* so that $i_1=j_1, i_2=j_2, ..., i_r=j_r$ for the largest possible r.
- At the first difference (r+1), both algorithms are in the same cache state and experience a miss.  
OPTFF evicts $i_{r+1}$ (farthest next use), and A* evicts $j_{r+1}$.
- Define A' to be the same as A* except it evicts the same as OPTFF $i_{r+1}$.
- Since $i_{r+1}$ is requested no earlier than $j_{r+1}$, this exchange cannot increase future misses.
- Thus A' is still optimal (number of misses is no larger than A*) but agrees with OPTFF for at least r+1 steps,  
contradicting the maximum of r, making OPTFF optimal.

---

## Reproducibility
A grader can:
1. `git clone https://github.com/PatrickLeimer/Algo-Abstraction.git`
2. Run `python "Assignment 2/cache.py"`
3. Verify generated `.out` files match expected results shown above.
