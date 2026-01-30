g++ -std=c++17 -g cli.cpp task_a.cpp task_b.cpp task_c.cpp -o cli.exe

cli.exe a exampleIN.txt exampleOUT.txt
    Matching pairs:
    1 2
    2 3
    3 1

cli.exe b exampleIN.txt exampleOUT.txt
    Checking unmatched pair (2, 2) with current matches (2, 3) and (1, 2).
    Checking pair (2, 2): hPrefersS=2, sPrefersH=1
    Checking unmatched pair (3, 2) with current matches (3, 1) and (1, 2).
    Checking pair (3, 2): hPrefersS=2, sPrefersH=1
    Checking unmatched pair (3, 3) with current matches (3, 1) and (2, 3).
    Checking pair (3, 3): hPrefersS=1, sPrefersH=1

    VALID STABLE

cli.exe c 2 4
    n = 2
    microseconds
    n = 4
    microseconds
    n = 8
    microseconds
    n = 16
    microseconds


