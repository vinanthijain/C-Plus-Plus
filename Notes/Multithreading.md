** Multithreading:

Threads are same as normal tasks but clone() systemcall is passsed to specify the below resources are shared
The address space(CLONE_VM)
filesystem resource(CLONE_FS)
file descriptor(CLONE_FILES)
signal handlers(CLONE_SIGHAND)

Q: What is the meaning of joining a thread?
A: A thread, in most cases the parent, joining another thread means that the caller is blocking until the other thread finished execution. It's e.g. a way of synchronizing termination of a process with multiple threads.  

Q: What is the drawback of using too many threads
A: Too many context switches which involve constant backups of ALU registers into memory and thus slow down the system.

Q: What happens if two threads in the same process try to access each others memory regions?
A: When two threads in the same process attempt to access each other's memory regions without proper synchronization mechanisms, it can lead to what is commonly known as a data race. A data race occurs when two or more threads concurrently access shared data, and at least one of them modifies the data. The behavior of the program becomes undefined, and it can result in various issues like Race Conditions,Inconsistent State,Corruption of Data,Crashes and Undefined Behavior.

Q: Why does this code randomly dead-lock ( https://godbolt.org/z/hzMd31v9Y )
A: The two mutex are locked in different order, bonus points: use lock_guard / unique_lock

Q: How are the thread functions arguments in C++ 11 is passed ? ( Pass by value or reference ?) Can you pass it by reference ?
A: when you create a thread using the std::thread class, the arguments to the thread function are generally passed by value. However, you can pass arguments by reference or using std::ref to achieve a form of pass by reference.

** LockGuard :

lock_guard's constructor calls mutex lock and its destructor unlocks the mutex.
Unique_lock is a kind of lock_guard but in case of unique_lock we can lock/unlock anytime. If we do not unlock, it happens by default in desctructor.
If we use std::thread and want to pass member variables, we have to pass Objects also as an parameter.

we cant use this when 2 threads intersect each other
ie in below case
a.lock();
b.lock();
a.unlock();
b.unlock();

There are 3 types of lock guard
lock guard
unique_lock
scoped_lock


Q: What is a scheduler in general doing
A: It allocates CPU-time on various cores to diffferent threads based on priority and different scheduling algorithms like RR, FSFS, ...

** Read-Write Locks:

A read-write lock allows multiple readers to access a shared resource simultaneously but gives exclusive access to writers.

A Readers-Writers Lock is a synchronization mechanism that allows multiple threads to read shared data simultaneously but grants exclusive access to a single thread for writing. This ensures data consistency while maximizing concurrency.

Key Features:
Usage: Useful when read operations are more frequent than write operations.
Mechanism:
Multiple threads can hold a read lock concurrently.
Only one thread can hold a write lock at a time, and no readers are allowed during writing.
Advantages:
Improves performance when many threads only need to read data.
Prevents writers from being interrupted by readers.
Disadvantages:
Can cause reader starvation, where writers wait indefinitely due to continuous reader activity.

** SpinLock: 

A spin lock is a synchronization primitive where a thread continuously checks (or "spins") on a shared resource until it becomes available.

 A spinlock means blocking on a conditional without switching to an idle state and thus prevents context swiching away from the thread. Should only be used when it's certain that the block will only last for a very short period. Mainly used in kernelcode.

 A spin lock is a synchronization primitive where a thread continuously checks (or "spins") on a shared resource until it becomes available.

Key Features:
Usage: Suitable for short critical sections where the wait time is expected to be very short.
Mechanism:
A thread attempting to acquire the lock enters a loop and keeps checking if the lock is free.
Once the lock is free, it acquires it and proceeds.
Advantages:
Low overhead: No context switching is involved if the wait time is short.
Useful in scenarios where threads are expected to hold the lock for very short durations.
Disadvantages:
Wastes CPU cycles while "spinning," especially if the wait time is long.
Can lead to performance degradation on systems with heavy contention.

Ex for Spinlock:

atomic_flag flag = ATOMIC_FLAG_INIT; 
void thread_function(int id) 
{ 
    for (int i = 0; i < 5; ++i) { 
        while (flag.test_and_set(memory_order_acquire)) { 
        } 
        // Acquire lock 
        cout << "Thread " << id << " is running." << endl; 
        flag.clear(memory_order_release); // Release lock 
    } 
} 

** std::atomic
std::atomic is a C++ standard library template that provides atomic operations for variables shared by multiple threads. It ensures that these operations are performed atomically, without interference from other threads. This helps in avoiding race conditions and ensures consistency in concurrent programming.

** Atomic Variables:

atomic<int> counter(0); // Atomic integer 
  
void testAtomic()
{
        counter.fetch_add(1);
}
int main()
{
        thread t1(testAtomic);
        thread t2(testAtomic);
        t1.join();
        t2.join();
        cout<<"Counter="<<counter.load()<<endl;
}


** Deadlock:
If two or even more threads are in state where one blocks the other and thus none of them will be unblocked until termination of the process.
A deadlock occurs when two or more threads are waiting for resources that each thread holds, and none can proceed.

Conditions for Deadlock (Coffman conditions):
Mutual Exclusion: At least one resource must be held in a non-shareable mode.
Hold and Wait: A thread is holding one resource while waiting for another.
No Preemption: Resources cannot be forcibly taken away.
Circular Wait: A circular chain of threads exists where each thread is waiting for a resource held by the next.

Avoidance Strategies:
Resource ordering: Always acquire resources in a specific order.
Timeouts: Use timeouts to break deadlocks.
Deadlock detection: Monitor the system to detect and resolve deadlocks dynamically.

**Condition variable:

A condition variable is a synchronization primitive used to block a thread until a specific condition is met. It enables threads to communicate by signaling when a condition has changed, allowing one or more threads to proceed.

How it Works:
A condition variable is always used with a mutex to avoid race conditions.
Threads can:
Wait on the condition variable, releasing the mutex and sleeping until notified.
Notify one or all waiting threads to wake up and re-check the condition.
Key Methods:
wait(std::unique_lock<std::mutex>& lock): Blocks the thread until notified. It automatically releases the mutex while waiting and re-acquires it before returning.
notify_one(): Wakes up one waiting thread.
notify_all(): Wakes up all waiting threads.


** Difference between mutex and Semaphore:
    Ownership:
    Mutex: Ownership is strict. Only the thread that locked the mutex can unlock it.
    Semaphore: No strict ownership. Any thread can signal a semaphore, regardless of which thread performed the wait.
    Usage Model:

    Mutex: Typically used to protect a single resource or a critical section of code, ensuring only one thread can access it at a time.
    Semaphore: Can be used to manage access to a limited number of identical resources or to implement more complex synchronization patterns (like controlling access to multiple resources or managing resource pools).
    Blocking Behavior:

    Mutex: A thread trying to lock a locked mutex will block until the mutex is unlocked.
    Semaphore: A thread performing a wait on a semaphore with a count of zero will block until the count becomes positive.
    Deadlocks:

    Mutex: If a thread locks a mutex and forgets to unlock it, or if two threads wait for each other’s mutexes, a deadlock can occur.
    Semaphore: Deadlocks can also occur with semaphores if not used carefully, especially if multiple semaphores are involved.
    Counting:

    Mutex: Binary, it’s either locked or unlocked.
    Semaphore: Can count, allowing multiple threads to proceed if the count is greater than one.

** Thread vs Process

    A process is an independent program in execution, with its own memory space, code, data, and system resources. Each process operates in its own virtual address space and has its own set of resources (e.g., file descriptors, memory). Processes are isolated from each other, meaning that one process cannot directly access the memory of another process.
    A thread, often referred to as a lightweight process, is a smaller unit of execution within a process. Threads share the same memory space and resources of their parent process, but they execute independently. Multiple threads within the same process can read and write to the same variables and data structures.

 ** Notes:
1.If an exception is thrown before calling join on the thread, the program terminates
2.If you want to lock a mutex multiple times without unlocking, use recursive mutex.It expects same number of unlocks as locks
3.Timed mutex is same as mutex but with try_lock_until,try_lock_for
4.When shared locks are used, other threads can access the data.It is used when we are sure that code will not modify
5.call_once is used to ensure that the thread executing that is not disturbed until it finishes it.once_flag is is used to achieve this
    std::once_flag flag;
    std::call_once(flag,[]()){}
