#include "header.h"

int main() {
    srand(time(NULL)); //sets random seed for the random char :)
    //create memory object
    
    int sharedMem = shm_open("/tableMemory", O_CREAT | O_RDWR, 0777); /*name,
                                                                        create it if it's nonexistent |
                                                                        open it up for read/write |
                                                                        close if it's borked,
                                                                        directory permissions..? MAN7's were broken; open documentation has... more? I don't understand them...*/
    if (sharedMem == -1) errExit("shm_open");
    
    if (ftruncate(sharedMem, sizeof(table)) == -1) errExit("ftruncate");//if truncating sharedMem to the size of the table returns an error, something is wrong. believe this is for issues w the size

    //map to memory
    table *producer = mmap(NULL, sizeof(*producer), PROT_READ | PROT_WRITE, MAP_SHARED, sharedMem, 0); /*maps the table into physical memory?
                                                                                                        memory address,
                                                                                                        length of the mapping,
                                                                                                        can be written to | read,
                                                                                                        other processes can see this mapping,
                                                                                                        file descriptor???,
                                                                                                        offset*/
    if (producer == MAP_FAILED) errExit("mmap");//if mapping returned a failed error :(((((

    //create semaphores. address, these things are shared so make sure they're in shared memory, inital value
    if (sem_init(&producer->vacant, 1, tableMax) == -1) errExit("sem_init-vacant"); // 2 vacant spaces
    if (sem_init(&producer->occupied, 1, 0) == -1) errExit("sem_init-occupied"); // 0 occupied spaces
                   
    // ensuring buffer's empty
    for (int i = 0; i < tableMax; ++i){
        producer->buffer[i] = '?';
    }

for (int i = 0; i < tableMax; ++i) {
    sem_wait(&producer ->vacant);
    char thing = (char) ((rand() % 26) + ((int) ('a')));
    producer -> buffer[i] = thing;
    printf("%s", "added '");
	printf("%c", thing);
	printf("%s", "' to table.\n");
    sem_post(&producer->occupied);
}

    //producing
    // int produced = 0;
    // while (produced < maxLoops) {
    //     while(producer->buffer[0] != '?' && producer->buffer[1] != '?'); //busywork. while buffer has Thing In It do nothing
    //     if (sem_wait(&producer->vacant) == -1) errExit("sem_wait");  //locks vacant; if it returns an error, exit 
    //     char thing = 'a';
    //     for (int i = 0; i < tableMax; ++i) { //produces thing to throw in the table
    //         thing = (char) ((rand() % 26) + ((int) ('a')));
    //         producer->buffer[i] = thing; //throws thing in table
    //         printf("%s", "added '");
	//         printf("%c", thing);
	//         printf("%s", "' to table.\n");
    //     }
    //     ++produced;
    //     if (sem_post(&producer->occupied) == -1) errExit("sem_post"); //unlocks occupied; if it returns an error, exit
    // }
    //shm_unlink("/tableMemory"); //closes shared memory

    exit(EXIT_SUCCESS);

}