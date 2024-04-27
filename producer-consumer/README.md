# Producer/Consumer Problem
## Description
This project models the producer/consumer problem. The producer generates a random alphabetical character and puts it in shared memory; the consumer removes it. The shared memory cannot hold more than 2 characters at a time; this is managed using semaphores. The project is intended to run on Linux operating systems. The processes finish when the consumer has nothing left to consume.
## Compilation
The consumer and producer are disparate files, and must be compiled as such. To compile, run:
`$ gcc producer.c -pthread -lrt -o producer\n`
`$ gcc consumer.c -pthread -lrt -o consumer\n`
`$ ./producer & ./consumer &`

## Demo

https://github.com/src-img/CS33221/assets/79075375/582646b8-b39a-44cc-9571-c2db05567003