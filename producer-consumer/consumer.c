#include "header.h"

int main() {
    //create memory object
    int sharedMem = shm_open("/tableMemory", O_CREAT | O_RDWR, 0777); /*name,
                                                                        create it if it's nonexistent |
                                                                        open it up for read/write |
                                                                        close if it's borked,
                                                                        directory permissions..? MAN7's were broken; open documentation has... more? I don't understand them...*/
    if (sharedMem == -1) errExit("shm_open");
    if (ftruncate(sharedMem, sizeof(table)) == -1) errExit("ftruncate");//if truncating sharedMem to the size of the table returns an error, something is wrong. believe this is for issues w the size

    //map to memory
    table *consumer = mmap(NULL, sizeof(*consumer), PROT_READ | PROT_WRITE, MAP_SHARED, sharedMem, 0); /*maps the table into physical memory?
                                                                                                        memory address,
                                                                                                        length of the mapping,
                                                                                                        can be written to | read,
                                                                                                        other processes can see this mapping,
                                                                                                        file descriptor???,
                                                                                                        offset*/
    if (consumer == MAP_FAILED) errExit("mmap");//if mapping returned a failed error :(((((

    for (int i = 0; i < tableMax; ++i) {
        sem_wait(&consumer ->occupied);
        consumer -> buffer[i] = '?';
        printf("%s", "removed value from table slot ");
	    printf("%d", i + 1);
	    printf("%s", "\n");
        sem_post(&consumer -> vacant);
    }

    //consuming
    // int consumed = 0;
    // while (consumed < maxLoops) {
    //     while(consumer->buffer[0] == '?' && consumer->buffer[1] == '?'); //busywork. while buffer has Nothing In It do nothing
    //     if (sem_wait(&consumer->occupied) == -1) errExit("sem_wait");//locks occupied; if it returns an error, exit
    //     for (int i = 0; i < tableMax; ++i) { //consumes thing from table
    //         consumer->buffer[i] = '?'; //removes thing from table
    //         printf("%s", "removed value from table slot ");
	//         printf("%d", i + 1);
	//         printf("%s", "\n");
    //     }
    //     ++consumed;
    //     if (sem_post(&consumer->vacant) == -1) errExit("sem_post"); //unlocks vacant; if it returns an error, exit
    // }
    //++consumed;
    shm_unlink("/tableMemory"); //closes shared memory

    exit(EXIT_SUCCESS);

}
