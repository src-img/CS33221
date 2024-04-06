# Producer/Consumer Problem
## Description
This project models the producer/consumer problem. The producer generates a random alphabetical character and puts it in shared memory; the consumer removes it. The shared memory cannot hold more than 2 characters at a time; this is managed using semaphores. The project is intended to run on Linux operating systems.
## Compilation
The consumer and producer are disparate files, and must be compiled as such. To compile, run:
`$ gcc producer.c -pthread -lrt -o producer\n`
`$ gcc consumer.c -pthread -lrt -o consumer\n`
`$ ./producer & ./consumer &`

## Demo
https://github.com/src-img/CS33221/assets/79075375/6f5cab04-50b7-48a3-86df-b053867ba04d

## Disclaimer
The claims mentioned above are lofty at best. To put it frankly: This thing is broken, and I've no idea why. The consumer is more broken than the producer, as it doesn't exit corrently. While debugging, I found putting a print statement after the consumer's shared memory allocation caused it to not exit with an error immediately, so the print statement is staying in.
Things I have tried:
- Compiling on Wasp
  - Changing Wasp access permissions
- All sorts of shm_open() modes
- Populating the table with ints
- Compiling in Codespaces
- sleep() used before and during the critical sections

The conclusion I've come to is the shared memory is Wrong. That's the thing that gives me the error; the amount of values in and out of the table varies every compilation in ways it is not meant to. I'm not sure if the behavior of "table is fully populated, then fully unpopulated" is expected; I don't think it is, but that's the behavior regardless. I have no idea how to fix the shared memory; I've tried every list of arguments I can imagine, to no avail.

This is my own fault, of course. I neglected to start the assignment until Thursday, and pigeonholed myself into tutor-less circumstances. I intend to shake them down for answers when they open back up, so if this changes mid-grading, that's why, but--that is past the deadline. What is in the repository right now is the best I could come up with after about 9 hours of working on it. Sorry it's such a nightmare mess.
