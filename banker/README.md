# Banker's Algorithm
## Description
This project models the "safe state" algorithm portion of the Banker's Algorithm. Input matricies for allocation, maximum, and available are provided via `in.txt`. The table below demonstrates the format of the provided `in.txt`:

||Allocation|Max|Available|
|---|---|---|---|
|P0|010|753|332|
|P1|200|322||
|P2|302|902||
|P3|211|222||
|P4|002|433||

## Output
If a safe state is successfully found, the sequence will be printed like so:
`Safe sequence:`

`1: Process 1`

`2: Process 3`

`3: Process 4`

`4: Process 0`

`5: Process 2`

If a safe state is _not_ found, `Unsafe sequence!!` is printed.

## Compilation & Running
Compilation:
`$ g++ banker.cpp -o banker`

Running:
`$ ./banker `

## Personal Challenges
Vectors are tricky! I've not used C++ in a bitm and it took me a while to get back into the swing of it. Figuring out how to implement matricies and correctly resize the vectors took most of the project time.
Additionally, parsing the file was unexpectedly challenging. My main priority was keeping the code as straightforward as possible, and I feel the switch ended up being a tidy way of logically chunking out the 3 different matricies.

## Resources

`https://www.studytonight.com/operating-system/bankers-algorithm` was referenced for code implementation of checking the safe state.

Section 7.5.3 of  Silberschatz, Baer Galvin, and Gagne's "Operating Systems Concepts" was referenced for overall conceptualization of the problem.

