Assignment 1 - Stable Matching Toolkit
=====================================
### Students: Julio Leonardi, Patrick Leimer.

Overview
--------
This project contains three tasks for stable matching:

- Task A: Matching engine (Gale–Shapley) to produce a hospital–student matching.
- Task B: Verifier to validate a matching and report INVALID/UNSTABLE/VALID STABLE.
- Task C: Test generator and timing harness.

Files
-----
- cli.cpp / cli.h: Command-line interface for running Tasks A, B, and C.
- task_a.cpp: Matching engine implementation.
- task_b.cpp: Verifier implementation.
- task_c.cpp: Test generator and timing.
- exampleIN.txt / exampleOUT.txt: Sample input/output files.

Build (CLI)
-----------
From the Assignment 1 folder:

g++ -std=c++17 -g cli.cpp task_a.cpp task_b.cpp task_c.cpp -o cli.exe

Run (CLI)
---------
- Task A (produce a matching file and print pairs):

	./cli.exe a exampleIN.txt exampleOUT.txt

- Task B (verify a matching file):

	./cli.exe b exampleIN.txt exampleOUT.txt

- Task C (generate tests):

	./cli.exe c 2 4


Input Format
------------
The input file uses 1-based IDs:

1) First line: n
2) Next n lines: hospital preferences (permutation of 1..n)
3) Next n lines: student preferences (permutation of 1..n)

Matching Output Format
----------------------
The matching file contains n lines of:

i j

Meaning hospital i is matched to student j (1-based).
