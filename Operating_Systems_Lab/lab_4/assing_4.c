// // Dining_Philospher_Thread
// #include<stdio.h>
// #include<stdlib.h>
// #include<pthread.h>
// #include<semaphore.h>
// #include<unistd.h>

// pthread_t philosopher[5];
// pthread_mutex_t chopstick[5];
// void *func(int n);

// int main(){
//   int i,k;
//   void *msg;
//   for(i=1;i<=5;i++){
//     k=pthread_mutex_init(&chopstick[i],NULL);
//     if(k==-1){
//       printf("\n Mutex initialization failed");
//       exit(1);
//     }
//   }
//   for(i=1;i<=5;i++){
//     k=pthread_create(&philosopher[i],NULL,(void *)func, (int *)(intptr_t)i);
//     if(k!=0){
//       printf("\n Thread creation error \n");
//       exit(1);
//     }
//   }
//   for(i=1;i<=5;i++){
//     k=pthread_join(philosopher[i],&msg);
//     if(k!=0){
//       printf("\n Thread join failed \n");
//       exit(1);
//     }
//   }
//   for(i=1;i<=5;i++){
//     k=pthread_mutex_destroy(&chopstick[i]);
//     if(k!=0){
//       printf("\n Mutex Destroyed \n");
//       exit(1);
//     }
//   }
//   return 0;
// }

// void *func(int n){
//   printf("\nPhilosopher %d is thinking ",n);
//   pthread_mutex_lock(&chopstick[n]);//when philosopher 5 is eating he takes fork 1 and fork 5 pthread_mutex_lock(&chopstick[(n+1)%5]);
//   printf("\nPhilosopher %d is eating ",n);
//   sleep(3);
//   pthread_mutex_unlock(&chopstick[n]);
//   pthread_mutex_unlock(&chopstick[(n+1)%5]);
//   printf("\nPhilosopher %d Finished eating ",n);
// }

// // code -2 Producer_Consumer
// #include <stdio.h>
// #include <pthread.h>
// #include <semaphore.h>
// #include <stdlib.h>

// sem_t empty, full, mutex;

// void *producer (void *);
// void *consumer(void *);

// int buffer[10];
// int ID[10];
// int in = 0 ; int out = 0;
// int BUFFER_SIZE = 10;
// int nextProduced = 0;

// int main(){
//   int i;
//   pthread_t TID[10];
//   sem_init(&empty, 0, 10);
//   sem_init(&full, 0, 0);
//   sem_init(&mutex, 0, 1);
//   for(i = 0; i < 10; i++){
//   ID[i] = i;
//   buffer[i] = -1;
//   }
//   pthread_create(&TID[0], NULL, producer, (void *) &ID[0]) ; printf("Producer ID = %d created!\n", 0);
//   pthread_create(&TID[1], NULL, consumer, (void *) &ID[1]) ; printf("Consumer ID = %d created!\n", 1);
//   pthread_create(&TID[2], NULL, producer, (void *) &ID[2]) ; printf("Producer ID = %d created!\n", 2);
//   pthread_create(&TID[3], NULL, consumer, (void *) &ID[3]) ; printf("Consumer ID = %d created!\n", 3);
//   for(i = 0; i < 10 ; i++)pthread_join(TID[i], NULL);
// }

// void *producer(void *Boo){
//   int *ptr;
//   int ID;
//   ptr = (int *) Boo;
//   ID = *ptr;
//   while (1){
//   nextProduced++; //Producing Integers
//   /* Check to see if Overwriting unread slot */
//   sem_wait(&empty);
//   sem_wait(&mutex);
//   if (buffer[in] != -1){
//     printf("Synchronization Error: Producer %d Just overwrote %d from Slot %d \n ", ID, buffer[in], in);
//     exit(0);
//   }
//   buffer[in] = nextProduced;
//   printf("Producer %d. Put %d in slot %d\n", ID, nextProduced, in);
//   in = (in + 1) % BUFFER_SIZE;
//   printf("incremented in!\n");
//   sem_post(&mutex);
//   sem_post(&full);
//   }
// }

// void *consumer (void *Boo){
//   static int nextConsumed = 0;
//   int *ptr;
//   int ID;
//   ptr = (int *) Boo;
//   ID = *ptr;
//   while (1){
//     sem_wait(&full);
//     sem_wait(&mutex);
//     nextConsumed = buffer[out];
//     if (nextConsumed == -1){
//       printf("Synch Error: Consumer %d Just Read from empty slot %d\n", ID, out);
//       exit(0);
//     }
//     printf("Consumer %d Just consumed item %d from slot %d\n", ID, nextConsumed, out);
//     buffer[out] = -1;
//     out = (out + 1) % BUFFER_SIZE;
//     sem_post(&mutex);
//     sem_post(&empty);
//   }
// }

// // Reader_Writer
// #include<semaphore.h>
// #include<stdio.h>
// #include<stdlib.h>
// #include<unistd.h>
// #include<pthread.h>

// sem_t x,y;
// pthread_t tid;
// pthread_t writerthreads[100],readerthreads[100];

// int readercount = 0;

// void *reader(void* param){
//   sem_wait(&x);
//   readercount++;
//   if(readercount==1)sem_wait(&y);
//   sem_post(&x);
//   printf("%d reader is inside\n",readercount);
//   usleep(3);
//   sem_wait(&x);
//   readercount--;
//   if(readercount==0)sem_post(&y);
//   sem_post(&x);
//   printf("%d Reader is leaving\n",readercount+1);
//   return NULL;
// }

// void *writer(void* param){
//   printf("Writer is trying to enter\n");
//   sem_wait(&y);
//   printf("Writer has entered\n");
//   sem_post(&y);
//   printf("Writer is leaving\n");
//   return NULL;
// }

// int main(){
//   int n2,i;
//   printf("Enter the number of readers:");
//   scanf("%d",&n2);
//   printf("\n");
//   int n1[n2];
//   sem_init(&x,0,1);
//   sem_init(&y,0,1);
//   for(i=0;i<n2;i++){
//     pthread_create(&writerthreads[i],NULL,reader,NULL);
//     pthread_create(&readerthreads[i],NULL,writer,NULL);
//   }
//   for(i=0;i<n2;i++){
//     pthread_join(writerthreads[i],NULL);
//     pthread_join(readerthreads[i],NULL);
//   }
// }

// //Sleeping_Barber
// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <semaphore.h>

// #define MAX 20

// sem_t chairs_mutex;
// sem_t sem_client;
// sem_t sem_barber;

// void *client(void *param);
// void *barber(void *param);

// int num_chairs;
// int clientWait;

// int main(int argc, char *argv[]){
//   pthread_t barberid;
//   pthread_t clientids[MAX];
//   printf("Main thread beginning\n");
//   /* 1. Get command line arguments */
//   int runTime,clients,i;
//   if (argc != 5){
//     printf("Please enter 4 arguments: <Program run time> <Number of clients>\n");
//     printf("<Number of chairs> <Client wait time>\n");
//     exit(0);
//   }
//   runTime = atoi(argv[1]);
//   clients = atoi(argv[2]);
//   num_chairs = atoi(argv[3]);
//   clientWait = atoi(argv[4]);
//   /* 2. Initialize semaphores */
//   sem_init(&chairs_mutex,0,1);
//   sem_init(&sem_client,0,0);
//   sem_init(&sem_barber,0,0);
//   /* 3. Create barber thread. */
//   pthread_create(&barberid, NULL, barber, NULL);
//   printf("Creating barber thread with id %lu\n",barberid);
//   /* 4. Create client threads. */
//   for (i = 0; i < clients; i++){
//     pthread_create(&clientids[i], NULL, client, NULL);
//     printf("Creating client thread with id %lu\n",clientids[i]);
//   }
//   /* 5. Sleep. */
//   printf("Main thread sleeping for %d seconds\n", runTime);
//   sleep(runTime);
//   /* 6. Exit. */
//   printf("Main thread exiting\n");
//   exit(0);
// }

// void *barber(void *param) {
//   int worktime;
//   while(1) {
//     /* wait for a client to become available (sem_client) */
//     sem_wait(&sem_client);
//     /* wait for mutex to access chair count (chair_mutex) */
//     sem_wait(&chairs_mutex);
//     /* increment number of chairs available */
//     num_chairs += 1;
//     printf("Barber: Taking a client. Number of chairs available = %d\n",num_chairs);
//     /* signal to client that barber is ready to cut their hair (sem_barber) */
//     sem_post(&sem_barber);
//     /* give up lock on chair count */
//     sem_post(&chairs_mutex);
//     /* generate random number, worktime, from 1-4 seconds for length of haircut. */
//     worktime = (rand() % 4) + 1;
//     /* cut hair for worktime seconds (really just call sleep()) */
//     printf("Barber: Cutting hair for %d seconds\n", worktime);
//     sleep(worktime);
//   }
// }

// void *client(void *param){
//   int waittime;
//   while(1){
//     /* wait for mutex to access chair count (chair_mutex) */
//     sem_wait(&chairs_mutex);
//     /* if there are no chairs */
//     if(num_chairs <= 0){
//       /* free mutex lock on chair count */
//       printf("Client: Thread %u leaving with no haircut\n", (unsigned int)pthread_self());
//       sem_post(&chairs_mutex);
//     }
//     /* else if there are chairs */
//     else{
//       /* decrement number of chairs available */
//       num_chairs -= 1;
//       printf("Client: Thread %u Sitting to wait. Number of chairs left = %d\n",(unsigned int)pthread_self(),num_chairs);
//       /* signal that a customer is ready (sem_client) */
//       sem_post(&sem_client);
//       /* free mutex lock on chair count */
//       sem_post(&chairs_mutex);
//       /* wait for barber (sem_barber) */
//       sem_wait(&sem_barber);
//       /* get haircut */
//       printf("Client: Thread %u getting a haircut\n",(unsigned int)pthread_self());
//     }
//     /* generate random number, waittime, for length of wait until next haircut or next try.
//     Max value from command line. */
//     waittime = (rand() % clientWait) + 1;
//     /* sleep for waittime seconds */
//     printf("Client: Thread %u waiting %d seconds before attempting next haircut\n", (unsigned int)pthread_self(),waittime);
//     sleep(waittime);
//   }
// }

// IMPLEMENTATION OF FOUR CLASSICAL IPC PROBLEMS USING SYSTEM V IPC FACILITIES.
// // Dining Philospher
// #include<stdio.h>
// #include<fcntl.h>
// #include<semaphore.h>
// #include<sys/wait.h>
// #include<pthread.h>
// #include<stdlib.h>
// #include<unistd.h>

// sem_t *sem[20];

// int n;
// int reader(int val);

// int main(){
//   pid_t cpid[5];
//   char semname[5];
//   int i,j=0;
//   n = 5;
//   for(i=0;i<n;i++){
//     sprintf(semname,"%d",getpid()+i);
//     sem[i]=sem_open(semname,O_CREAT|O_EXCL,0666,1);
//     if(sem[i]==SEM_FAILED) perror("Unable to create semaphore");
//   }
//   for(i=0;i<n;i++){
//     cpid[i]=fork();
//     if(cpid[i]==0)break;
//   }
//   if(i==n){
//     int status;
//     for(i=0;i<n;i++) waitpid(cpid[i],&status,WUNTRACED);
//     //waitpid is a function which waits for the child process to finish executing
//     //after that control switches back to parent
//     for(i=0;i<n;i++){
//       sem_close(sem[i]);
//       sprintf(semname,"%d ",getpid()+i);
//       sem_unlink(semname);
//     }
//   }
//   else reader(i);
// }

// int reader(int val){
//   printf("%d Thinking\n",val+1);
//   while(1){
//     sem_wait(sem[val%n]);
//     if(!sem_trywait(sem[(val+1)%n]))break;
//     else sem_post(sem[val%n]);
//   }
//   printf("%d Eating\n",val+1);
//   sleep(2);
//   sem_post(sem[val%n]);
//   sem_post(sem[(val+1)%n]);
//   printf("%d Finished Eating\n",val+1);
// }

// //Producer_Consumer
// #include <pthread.h>
// #include <semaphore.h>
// #include <stdlib.h>
// #include <stdio.h>
// /*
// This program provides a possible solution for producer-consumer problem using
// mutex and semaphore.
// I have used 5 producers and 5 consumers to demonstrate the solution. You can always
// play with these values.
// */

// #define MaxItems 5 // Maximum items a producer can produce or a consumer can consume
// #define BufferSize 5 // Size of the buffer

// sem_t empty;
// sem_t full;
// pthread_mutex_t mutex;

// int in = 0;
// int out = 0;
// int buffer[BufferSize];

// void *producer(void *pno){
//   int item;
//   for(int i = 0; i < MaxItems; i++){
//     item = rand(); // Produce an random item
//     sem_wait(&empty);
//     pthread_mutex_lock(&mutex);
//     buffer[in] = item;
//     printf("Producer %d: Insert Item %d at %d\n", *((int *)pno),buffer[in],in);
//     in = (in+1)%BufferSize;
//     pthread_mutex_unlock(&mutex);
//     sem_post(&full);
//   }
// }

// void *consumer(void *cno){
//   for(int i = 0; i < MaxItems; i++){
//     sem_wait(&full);
//     pthread_mutex_lock(&mutex);
//     int item = buffer[out];
//     printf("Consumer %d: Remove Item %d from %d\n",*((int *)cno),item, out);
//     out = (out+1)%BufferSize;
//     pthread_mutex_unlock(&mutex);
//     sem_post(&empty);
//   }
// }

// int main(){
//   pthread_t pro[5],con[5];
//   pthread_mutex_init(&mutex, NULL);
//   sem_init(&empty,0,BufferSize);
//   sem_init(&full,0,0);
//   int a[5] = {1,2,3,4,5}; //Just used for numbering the producer and consumer
//   for(int i = 0; i < 5; i++) pthread_create(&pro[i], NULL, (void *)producer, (void *)&a[i]);
//   for(int i = 0; i < 5; i++) pthread_create(&con[i], NULL, (void *)consumer, (void *)&a[i]);
//   for(int i = 0; i < 5; i++) pthread_join(pro[i], NULL);
//   for(int i = 0; i < 5; i++) pthread_join(con[i], NULL);
//   pthread_mutex_destroy(&mutex);
//   sem_destroy(&empty);
//   sem_destroy(&full);
//   return 0;
// }

// //Read_Write
// #include<stdio.h> 
// #include<pthread.h> 
// #include<semaphore.h> 
// #include<unistd.h> 

// sem_t mutex,writeblock; 

// int data = 0,rcount = 0;

// void *reader(void *arg){
//   int f;
//   f = ((intptr_t)arg);
//   sem_wait(&mutex);
//   rcount = rcount + 1;
//   if(rcount==1) sem_wait(&writeblock);
//   sem_post(&mutex);
//   printf("Data read by the reader%d is %d\n",f,data); sleep(1);
//   sem_wait(&mutex);
//   rcount = rcount - 1;
//   if(rcount==0) sem_post(&writeblock);
//   sem_post(&mutex);
// }

// void *writer(void *arg){
//   int f;
//   f = ((intptr_t) arg);
//   sem_wait(&writeblock);
//   data++;
//   printf("Data writen by the writer%d is %d\n",f,data); sleep(1);
//   sem_post(&writeblock);
// }

// int main(){ 
//   int i,b;
//   pthread_t rtid[5],wtid[5];
//   sem_init(&mutex,0,1);
//   sem_init(&writeblock,0,1);
//   for(i=0;i<=2;i++)
//     pthread_create(&wtid[i],NULL,writer,(void *)(intptr_t)i); pthread_create(&rtid[i],NULL,reader,(void *)(intptr_t)i);
//   for(i=0;i<=2;i++){
//     pthread_join(wtid[i],NULL);
//     pthread_join(rtid[i],NULL);
//   }
//   return 0;
// }

//Sleeping_Barber
#define _REENTRANT
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define MAX_CUSTOMERS 25 // The maximum number of customer threads.

// Function prototypes...
void *customer(void *num);
void *barber(void *);
void randwait(int secs);

// Define the semaphores.
// waitingRoom Limits the # of customers allowed
// to enter the waiting room at one time.
sem_t waitingRoom;
// barberChair ensures mutually exclusive access to
// the barber chair.
sem_t barberChair;
// barberPillow is used to allow the barber to sleep
// until a customer arrives.
sem_t barberPillow;
// seatBelt is used to make the customer to wait until
// the barber is done cutting his/her hair.
sem_t seatBelt;
// Flag to stop the barber thread when all customers
// have been serviced.
int allDone = 0;

int main(int argc, char *argv[]) {
  pthread_t btid;
  pthread_t tid[MAX_CUSTOMERS];
  long RandSeed;
  int i, numCustomers, numChairs;
  int Number[MAX_CUSTOMERS];
  // Check to make sure there are the right number of
  // command line arguments.
  if (argc != 4){
    printf("Use: SleepBarber <Num Customers> <Num Chairs> <rand seed>\n");
    exit(-1);
  }
  // Get the command line arguments and convert them
  // into integers.
  numCustomers = atoi(argv[1]);
  numChairs = atoi(argv[2]);
  RandSeed = atol(argv[3]);
  // Make sure the number of threads is less than the number of
  // customers we can support.
  if (numCustomers > MAX_CUSTOMERS) {
    printf("The maximum number of Customers is %d.\n", MAX_CUSTOMERS);
    exit(-1);
  }
  printf("\nSleepBarber.c\n\n");
  printf("A solution to the sleeping barber problem using semaphores.\n");
  // Initialize the random number generator with a new seed.
  srand48(RandSeed);
  // Initialize the numbers array.
  for (i=0; i<MAX_CUSTOMERS; i++) Number[i] = i;
  // Initialize the semaphores with initial values...
  sem_init(&waitingRoom, 0, numChairs);
  sem_init(&barberChair, 0, 1);
  sem_init(&barberPillow, 0, 0);
  sem_init(&seatBelt, 0, 0);
  // Create the barber.
  pthread_create(&btid, NULL, barber, NULL);
  // Create the customers.
  for (i=0; i<numCustomers; i++) pthread_create(&tid[i], NULL, customer, (void *)&Number[i]);
  // Join each of the threads to wait for them to finish.
  for (i=0; i<numCustomers; i++) pthread_join(tid[i],NULL);
  // When all of the customers are finished, kill the
  // barber thread.
  allDone = 1;
  sem_post(&barberPillow); // Wake the barber so he will exit.
  pthread_join(btid,NULL);
}

void *customer(void *number) {
  int num = *(int *)number;
  // Leave for the shop and take some random amount of
  // time to arrive.
  printf("Customer %d leaving for barber shop.\n", num);
  randwait(5);
  printf("Customer %d arrived at barber shop.\n", num);
  // Wait for space to open up in the waiting room...
  sem_wait(&waitingRoom);
  printf("Customer %d entering waiting room.\n", num);
  // Wait for the barber chair to become free.
  sem_wait(&barberChair);
  // The chair is free so give up your spot in the
  // waiting room.
  sem_post(&waitingRoom);
  // Wake up the barber...
  printf("Customer %d waking the barber.\n", num);
  sem_post(&barberPillow);
  // Wait for the barber to finish cutting your hair.
  sem_wait(&seatBelt);
  // Give up the chair.
  sem_post(&barberChair);
  printf("Customer %d leaving barber shop.\n", num);
}

void *barber(void *junk) {
  // While there are still customers to be serviced...
  // Our barber is omnicient and can tell if there are
  // customers still on the way to his shop.
  while (!allDone) {
    // Sleep until someone arrives and wakes you..
    printf("The barber is sleeping\n");
    sem_wait(&barberPillow);
    // Skip this stuff at the end...
    if (!allDone) {
      // Take a random amount of time to cut the
      // customer's hair.
      printf("The barber is cutting hair\n");
      randwait(3);
      printf("The barber has finished cutting hair.\n");
      // Release the customer when done cutting...
      sem_post(&seatBelt);
    }
    else printf("The barber is going home for the day.\n");
  }
}
void randwait(int secs) {
  int len;
  // Generate a random number...
  len = (int) ((drand48() * secs) + 1);
  sleep(len);
}