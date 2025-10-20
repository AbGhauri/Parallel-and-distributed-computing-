//
//  main.cpp
//  OpenMPTest
//
//  Created by Akhzar Nazir on 26/08/2025.
//

#include <iostream>
#include <omp.h>

// OpenMP: Parallel Programming Model (API) on Shared Memory Systems
// Pragma omp parallel for reduction (+:sum_parallel)
// Parallel if (val)
// Master and Slave thread

//1. Parallel Region
//#pragma omp parallel → start a parallel region.
//#pragma omp parallel for → parallelize a loop.
//#pragma omp parallel sections → run independent tasks in parallel.
//#pragma omp parallel section → run independent tasks in parallel.

//2. Work Sharing Constructs
// Difference between omp and for
//#pragma omp for → distribute loop iterations among threads.
//#pragma omp sections / #pragma omp section → assign different tasks to threads.
//#pragma omp single → one thread executes the block.
//#pragma omp master → only master thread (thread 0) executes.

// Race Condition
// Avoid Race Condition

//3. Synchronization
//#pragma omp barrier → all threads wait until everyone reaches this point.
//#pragma omp critical → only one thread at a time executes this block.
//#pragma omp atomic → atomic update of a shared variable.
//#pragma omp ordered → enforce sequential order inside a loop.
//#pragma omp flush → synchronize memory visibility across threads.

//4. Data Sharing Attributes (used inside parallel or for)
//private(var) → each thread gets its own copy of var.
//shared(var) → variable is shared among all threads.
//firstprivate(var) → each thread gets a private copy, initialized with original value.
//lastprivate(var) → after parallel region, the variable keeps the value from the last iteration.
//default(shared|none) → sets default sharing behavior.


// Master Threads Concept
// Worker Threads Concept
// Race Condition
// Shared and Private Variables
// Context Switching (20 threads running on 12 cores)
//    You only have 6 physical + 12 logical (total = 12).
//    The extra 8 beyond 12 will just be oversubscribed threads, handled by OS scheduling.
// #pragma omp parallel private(tid)
// #pragma omp parallel for
// Atomic and Critical
// Shared and Private Variables
// Critical Section
// Difference between Critical Section and Atomic
// Race condition with for loop, Race condition other than for ?

using namespace std;

void test (int val){
#pragma omp parallel if (val)
    if (omp_in_parallel()){
        printf("val = %d, parallelized with %d thread \n",val, omp_get_num_threads());
    }else{
        printf("val = %d, Serialized \n",val);
    }
}

int main() {
//    omp_set_num_threads(5);

//    test(0);
//    test(2);
//    test(2);

    // 12 Threads 222 Threads OS ne Context Switching ki

//    omp_set_num_threads(222);

//#pragma omp parallel
//    {
//        for (int x = 1; x<=10; x++) {
//            printf("x = %d \n",x);
//        }
//    }

    int sum = 0;

#pragma omp parallel
    {
    #pragma omp atomic
        sum+=1;
    }
    printf("Sum = %d \n",sum);

//    printf("Paralle for Start from Here \n");
//    int sumforparallel = 0;
//#pragma omp parallel for
//    {
//        for (int x = 1; x<=100; x++) {
//            sumforparallel+=1;
////            printf("for = xxxxxxx = %d \n",x);
//        }
//    }
//    printf("sumforparallel = %d \n",sumforparallel);
//
//
//    int sumforserial = 0;
//    printf("Serial Program \n");
//    for (int x = 1; x<=100; x++) {
//        sumforserial+=1;
////        printf("for Serial = %d \n",x);
//    }
//    printf("sumforserial = %d \n",sumforserial);
//
//
//



//    double stime, etime;
//    stime = omp_get_wtime();
//    // Serially
//    int serial_sum = 0;
//    for (int x =1; x<=10; x++) {
//        serial_sum+=1;
//    }
//    etime = omp_get_wtime();
//    printf("Serial ka time = %f \n",etime-stime);
//
//    // Parallel
//    stime = omp_get_wtime();
//    int parallel_sum = 0;
//    #pragma omp parallel for reduction(+:parallel_sum)
//        {
//        // Serially
//        for (int x =1; x<=10; x++) {
//            parallel_sum+=1;
//        }
//    }
//    etime = omp_get_wtime();
//    printf("Parallel ka time = %f \n",etime-stime);




//#pragma omp sections
//        {
//    #pragma omp section
//            {
//                // Do what you want
//                printf("Fahad \n");
//            }
//    #pragma omp section
//        {
//            // Do what you want
//            printf("Fahad 123 \n");
//
//        }
//    #pragma omp section
//        {
//            // Do what you want
//            printf("Fahad 456 \n");
//
//        }
//    #pragma omp section
//        {
//            // Do what you want
//            printf("Fahad 7878\n");
//
//        }
//    }



//        printf("In the name of Allah \n");




//    }


//    printf("====================== \n");








//#pragma omp master
//    {
//        printf("I am master Thread \n");
//    }
//
//    int sum = 0; // Shared Variable
//
//    for (int x = 0; x<=1400; x++) {
//        sum+=1;
//    }
//
//    printf("Serial --  %d \n",sum);
//
//    int sum1 = 0; // Shared Variable
//    #pragma omp parallel for reduction (+:sum1)
//    {
//        for (int x = 0; x<=1400; x++) {
//            sum1+=1;
//        }
//    }


//#pragma omp parallel
//    {
//        int c = 0;
//
//    }
//
//    printf("Paralle %d \n",sum1);































    // cui01

//    printf("I Am Master Thread \n");

//    for (int x = 1; x<=3; x++) {
//        printf("I am for loop in Serial \n");
//    }

//    #pragma omp parallel // 12 Times
//    {
//        for (int x = 1; x<=3; x++) {
//            printf("I am for loop inside parallel \n");
//        }
//    }

//    int sum1 = 0;
//    for (int x = 1; x<=12; x++) {
//        sum1+=1;
////            printf("%d \n",omp_get_thread_num());
//    }
//    printf("sum1 = %d \n",sum1);

//    int sum = 0; // Shared Variable among all threads
//    // OpenMP 5.1
//    #pragma omp parallel for reduction(+:sum)
//    {
//        for (int x = 1; x<=12; x++) {
//            sum+=1;
//            printf("sum = %d \n",omp_get_thread_num());
//        }
//    }

//    printf("Sum = %d \n",sum);


//    #pragma omp parallel private (aa)
//    {
////        printf("In the name of Allah \n");
////        printf("====================================== \n");
//        aa+=1;
//        printf("aa+=1 = %d \n",aa);
//
////        int a = 10; // Private
//
//    }







//        int sum = 0;   // shared variable
//
//        #pragma omp parallel for
//        {
//        for (int i = 0; i < 10; i++) {
//            sum += 1;   // race condition here!
//            }
//        }
//        printf("Final sum = %d\n", sum);



//    int nthreads, tid; // By Defaults is Shared variable
//
//    #pragma omp master
//        {
//            int count = 1; // by default is privtae variable
//            printf("This is master thread \n");
//        }
//
//    #pragma omp parallel
//        {
////            printf("This is Parallel Threads \n");
//            printf("omp_get_num_threads() %d \n",omp_get_num_threads());
//        }
//
//    printf("omp_get_num_threads() %d \n",omp_get_num_threads());










//    int nthreads, tid;

        /* Fork a team of threads with each thread having a private tid variable */
//        #pragma omp parallel private(tid)
//        {
//            /* Obtain and print thread id */
//            tid = omp_get_thread_num();
//            printf("Hello World from thread = %d\n", tid);
//
//            /* Only master thread does this */
//            if (tid == 0)
//            {
//                nthreads = omp_get_num_threads();
//                printf("Number of threads = %d\n", nthreads);
//            }
//
//        }
        /* All threads join master thread and terminate */



    return 0;
















   //    int n = 1230000;
   //    double start, end;
   //    start = omp_get_wtime();
   //    int sum_serial = 0;
   //    for (int i =0; i<n; i++){
   //        sum_serial+=1;
   //    }
   //    end = omp_get_wtime();
   //    printf("Sum Serial = %d, Time = %f \n",sum_serial,end-start);
   //
   //
   //    start = omp_get_wtime();
   //    int sum_parallel = 0;
   //    #pragma omp parallel for reduction(+:sum_parallel)
   //    for (int i =0; i<n; i++){
   //        sum_parallel+=1;
   //    }
   //    end = omp_get_wtime();
   //    printf("Sum Parallel = %d, Time = %f \n",sum_parallel,end-start);


// omp_set_num_threads(1000);

// Directives hain jo Compiler ko Instructions detay hain keh yeh karo
//#pragma omp parallel
//    {
//        count++;
//        printf("In the name of Allah %d \n", count);
//    }

//    printf("======================================================\n");

//    omp_set_num_threads(4);
//    int id;
//    #pragma omp parallel
//    {
//        for (int a = 1; a<=4; a++){
//            printf("In the name of Allah %d \n", a);
//        }

//        id = omp_get_thread_num();
//        printf("In the name of Allah %d \n", id);
//    }

//    omp_set_num_threads(4);   // Ask OpenMP to use 4 threads
//       #pragma omp parallel
//       {
//           #pragma omp sections
//           {
//               #pragma omp section
//               {
//                   printf("Thread %d: Task A (loading data)\n", omp_get_thread_num());
//               }
//               #pragma omp section
//               {
//                   printf("Thread %d: Task B (processing data)\n", omp_get_thread_num());
//               }
//               #pragma omp section
//               {
//                   printf("Thread %d: Task C (saving results)\n", omp_get_thread_num());
//               }
//               #pragma omp section
//               {
//                   printf("Thread %d: Task D (logging info)\n", omp_get_thread_num());
//               }
//           }
//       }


    // Why Parallel Loop is Slower than Serial(Sequential)
    // Thread Creation, Synchronisation and other overhead took some extra time








//        int n = 1200000;   // Small loop size
//        double start, end;
//
//        // --- Serial Version ---
//        start = omp_get_wtime();
//        int sum_serial = 0;
//        for (int i = 0; i < n; i++) {
//            sum_serial += i;
//        }
//        end = omp_get_wtime();
//        printf("Serial Sum = %d, Time = %f seconds\n", sum_serial, end - start);
//
//        // --- Parallel Version ---
//        start = omp_get_wtime();
//        int sum_parallel = 0;
//        // This will use static scheduling by default
//        #pragma omp parallel for reduction(+:sum_parallel)
//        for (int i = 0; i < n; i++) {
//            sum_parallel += i;
//        }
//        end = omp_get_wtime();
//        printf("Parallel Sum = %d, Time = %f seconds\n", sum_parallel, end - start);


    // Shared and Private Variables
    // Shared -> Shared among all threads
    // Each thread has its own local copy
    // int id; will be shared by default
    // Meaning: all threads access the same single memory location for id.
    // Each thread will overwrite id with its own thread number → race condition.
    // int a; Which is declared inside the #pragma omp parallel is private by default this means each thread has its own copy of a


//    #pragma omp parallel private(id)
//        {
//            for (int a = 1; a <= 4; a++) {
//                printf("Thread %d → a = %d\n", omp_get_thread_num(), a);
//        }
//            id = omp_get_thread_num();
//            printf("Thread %d → id = %d\n", omp_get_thread_num(), id);
//        }

    // Critical Section prevents multiple threads from accessing a section of code at the same time

//    return 0;
}


//int main() {
//
//#pragma omp parallel num_threads(8) proc_bind(spread)
//{
//    int tid = omp_get_thread_num();
//    printf("SAMP Code %d\n",tid);
//    // Each thread runs on a different "place" (spread out across sockets/cores)
//}
//
//    #pragma omp parallel
//    {
//       printf("Hello from thread %d of %d\n",
//              omp_get_thread_num(), omp_get_num_threads());
//    }
//
//    const int N = 1000000;
//    int sum = 0;
//
//    printf("OpenMP version: %d\n", _OPENMP);
//
//    // Below code will run on Apple Mac 2018 but on Linux not on MacOS
//    #pragma omp target teams distribute parallel for
//    for (int i=0; i<10; i++) {
//        printf("I am testing is this supporting GPU or not ?: \n");
////        C[i] = A[i] + B[i];
//    }
//
//    #pragma omp parallel for reduction(+:sum)
//    for (int i = 0; i < N; i++) {
//        sum += i;
//    }
//
//    cout << "Sum = " << sum << endl;
//
//    const int N1 = 1000000;
//    int sum1 = 0;
//
//    for (int i = 0; i < N1; i++) {
//        sum1 += i;
//    }
//
//    cout << "Sum = " << sum1 << endl;
//
//    return 0;
//}
