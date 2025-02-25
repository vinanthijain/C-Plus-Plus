Operating System:
----------------

File Access:
	Sequential Access - Information in the file is processed in order, one record after the other.Compilers will use this
	Direct Access - allow programs to read and write records rapidly in no particular order.Databases are often of this type.

Holes in a file:
A hole in a file refers to a portion of a file that is logically allocated but does not consume actual storage on disk. It often appears in sparse files, which are files designed to save disk space when large regions of the file contain only zeros.

Why Create Holes?
To save disk space: Instead of physically storing zeros, the file system only stores metadata indicating the presence of a hole.
Used in applications like database snapshots, disk images, or virtual memory swap files, where zero-filled regions are common.
	int fd = open("file_with_hole", O_CREAT | O_WRONLY, 0644);
    write(fd, "Hello", 5);
    lseek(fd, 1024 * 1024, SEEK_SET);
    write(fd, "World", 5);
This creates a file with a hole of approximately 1 MB between "Hello" and "World"

Sparse File:
A sparse file is a type of file that allows parts of its data to remain unallocated (i.e., not physically stored on disk).
dd if=/dev/zero of=sparse_file bs=1 count=0 seek=1G //Creates a sparse file

Sticky Bit: 
The sticky bit is a permission setting in Unix-like operating systems that can be applied to directories. It is primarily used to control user access to files in a shared directory.

Without a sticky bit: Any user with write permissions to the directory can delete or modify any file within it.
With a sticky bit: Only the file owner, the directory owner, or the root user can delete or modify files in the directory.
chmod +t directory_name //Add a sticky bit

Inode:
An inode (index node) is a data structure in a file system that stores information about a file or directory, like its type, size, permissions, ownership, and link count.
The link count in an inode tracks the number of references (or "links") to that file or directory.

File table:
The file table is an array of pointers to kernel file structures representing open files. When making file- I/O system calls, processes refer to files by an integer, known as a file descriptor (fd), that the kernel uses to index into this table.

Fork: Process is created.
Clone: Thread is created.

The clone() system call behaves identically to fork() , except that it accepts as arguments a set of flags that dictate what resources are shared between the parent and child (whereas a process created with fork() shares no resources with its parent).

CLONE_FS File-system information is shared.
CLONE_VM The same memory space is shared.
CLONE_SIGHAND Signal handlers are shared.
CLONE_FILES The set of open files is shared.

Scheduling:
Fair Scheduling
It eliminates time slices in the traditional sense. Instead of time slices, all processes are allotted a proportion of the processor’s time. CFS calculates how long a process should run as a function of the total number of runnable processes.
To start, CFS says that if there are N runnable processes, then each should be afforded 1/N of the processor’s time. CFS then adjusts this allotment by weighting each process’s allotment by its nice value. Processes with the default nice value have a weight of 1—their priority is unchanged. Processes with a smaller nice value (higher priority) receive a higher weight, while processes with a larger nice value (lower priority) receive a lower weight. CFS then runs each process for a “time slice” proportional to the process’s weight divided by the total weight of all runnable processes.
To calculate the actual length of time a process runs, CFS relies on a configurable variable called target latency, which is the interval of time during which every runnable task should run at least once. For example, assume that the target latency is 10 milliseconds. Further assume that we have two runnable processes of the same priority.Each of these processes has the same weight and therefore receives the same proportion of the processor’s time. In this case, with a target latency of 10 milliseconds, the first process runs for 5 milliseconds, then the other process runs for 5 milliseconds, then the first process runs for 5 milliseconds again, and so forth. If we have 10 runnable processes, then CFS will run each for a millisecond before repeating. But what if we had, say, 1,000 processes? Each process would run for 1 microsecond if we followed the procedure just described. Due to switching costs, scheduling processes for such short lengths of time is inefficient. CFS consequently relies on a second configurable variable, the minimum granularity, which is a minimum length of time any process is allotted the processor. All processes, regardless of the target latency, will run for at least the minimum granularity.
Real-Time Scheduling
Scheduling is done based on FCFS and Round Robin.In both cases, each process has a priority in addition to its scheduling class. The scheduler always runs the process with the highest priority. Among processes of equal priority, it runs the process that has been waiting longest.

Management of Physical Memory:
•ZONE DMA - devices can only access the lower 16 MB of physical memory using DMA .On these systems, the first 16MB of physical memory comprise ZONE DMA
•ZONE DMA32 - devices can only access the lower 4GB of physical memory using DMA .On these systems, the first 16MB of physical memory comprise ZONE DMA
•ZONE HIGHMEM - the kernel is mapped into the first 896 MB of the address space; the remaining memory is referred to as high memory and is allocated from ZONE HIGHMEM .
•ZONE Normal - comprises everything else —the normal, regularly mapped pages

kmalloc() service allocates entire physical pages on demand but then splits them into smaller pieces.Memory regions claimed by the kmalloc() system are allocated permanently until they are freed explicitly with a corresponding call to kfree()
Another strategy adopted by Linux for allocating kernel memory is known as slab allocation. A slab is used for allocating memory for kernel data structures

The page cache is the kernel’s main cache for files and is the main mechanism through which I/O to block devices is performed.

Virtual Memory:
--------------

The logical view organizes the address space into regions, with metadata stored in vm_area_struct.
The physical view focuses on the actual storage and mapping of pages, managed via the page tables.
The kernel uses page-management routines to handle page faults and other memory-related operations, allowing the two views to interact seamlessly.
1. Logical View of the Address Space
Definition:
The logical view describes the layout of the address space as understood by the virtual memory system. This view defines how memory regions are logically organized.

Address Space Regions:

The address space is divided into non-overlapping regions.
Each region represents a continuous, page-aligned subset of the address space.
Each region has specific properties, such as:
Permissions (read, write, execute).
Associated files (e.g., shared libraries, mapped files).
vm_area_struct:

Internally, each region is represented by a structure called vm_area_struct.
This structure holds the region's attributes and metadata.
Efficient Lookups:

To find which region corresponds to a given virtual address, the regions are stored in a balanced binary tree, enabling fast lookups.
2. Physical View of the Address Space
Definition:
The physical view describes the actual location of each page of virtual memory, whether it is in physical memory (RAM) or on disk (in case of paging/swapping).

Hardware Page Tables:

The physical view is stored in the page tables, which are hardware structures that map virtual addresses to physical memory locations.
Page-Management Routines:

When a process tries to access a page that is not in memory (e.g., on disk), the kernel invokes routines to manage the page:
These routines handle page faults (e.g., load the page from disk into RAM).They ensure the page is mapped into the process's page table.

Each vm_area_struct in the logical view points to a table of functions that implement page-management functionality for the corresponding memory region.These functions handle operations like:Reading or writing to unavailable pages.Mapping files into memory.
By abstracting the management of different memory regions into these functions, the central memory-management code doesn’t need to deal with the specific details of each type of memory region.

Lifetime of a Virtual Address Space:
===================================
The kernel creates a new virtual address space in two situations: when a process runs a new program with the exec() system call and when a new process is created by the fork() system call. The first case is easy. When a new program is executed, the process is given a new, completely empty virtual address space. It is up to the routines for loading the program to populate the address space with virtual memory regions.The second case, creating a new process with fork() , involves creating a complete copy of the existing process’s virtual address space. The kernel copies the parent process’s vm area struct descriptors, then creates a new set of page tables for the child. The parent’s page tables are copied directly into the child’s, and the reference count of each page covered is incremented. Thus, after the fork, the parent and child share the same physical pages of memory in their address spaces.

Virtual memory is a memory management technique that provides an “idealized” view of memory to applications, allowing them to use more memory than is physically available in the system. It abstracts the physical memory by using a combination of hardware and software to give processes their own virtual address space. Here's an overview:

How Virtual Memory Works:
Address Translation:

Virtual memory uses a page table to map virtual addresses to physical addresses.
The CPU generates virtual addresses, which are then translated into physical addresses using a memory management unit (MMU).
Paging:

Memory is divided into small, fixed-size units called pages (usually 4 KB in size).
The operating system swaps pages in and out of physical memory from a storage device (like a hard disk or SSD) to manage memory demands.
Demand Paging:

Only the pages currently needed are loaded into RAM, reducing memory usage and allowing multiple processes to run concurrently.
Swap Space:

When physical memory is exhausted, the OS moves inactive pages to a reserved area on disk called the swap space, freeing up RAM for active processes.
Advantages:
Isolation and Security: Each process operates in its own virtual address space, preventing interference between processes.
Efficient Memory Usage: It allows multiple processes to share physical memory efficiently, as only necessary parts of programs are loaded.
Large Address Space: Programs can use more memory than physically available, as the virtual address space is much larger.
Disadvantages:
Performance Overhead: Translating addresses and swapping pages between memory and disk can cause latency.
Disk Usage: Heavy use of swap space can degrade system performance (a condition known as thrashing).
Example in Linux:
The Linux kernel uses a virtual memory system based on demand paging and employs structures like vm_area_struct to manage memory regions of a process.

The EXT4 file system is organized into 
superblocks, 
block groups, 
inodes, 
data blocks, with additional features like 
journaling and 
extent trees 

** Preemptive and Cooperative Scheduling:

In preemptive scheduling, the OS has control over which process gets the CPU and for how long. A process can be forcibly removed from the CPU by the OS to allow another process to run.

Key Features:
The scheduler interrupts a running process to assign the CPU to another process.
A context switch occurs when a process is preempted.
Common in modern multitasking OSes (e.g., Linux, Windows, macOS).
Advantages:
Responsiveness: Critical tasks or higher-priority processes can preempt lower-priority ones.
Fairness: All processes get a chance to execute within a given timeframe.
Efficient resource use: Prevents a single process from monopolizing the CPU.
Disadvantages:
Overhead: Frequent context switches can slow down the system.
Complexity: Implementing preemptive schedulers requires careful handling of concurrency and synchronization.

In cooperative scheduling, the running process voluntarily yields control of the CPU, allowing other processes to execute.

Key Features:
The OS does not forcibly interrupt a process; the running process decides when to relinquish the CPU.
Relies on well-behaved processes to yield control appropriately.
Advantages:
Low Overhead: No context switching unless a process explicitly yields, reducing scheduler overhead.
Simplicity: Easier to implement since the OS doesn't need to handle preemption.
Disadvantages:
Unresponsiveness: A misbehaving process can monopolize the CPU, starving other processes.
Lack of Fairness: Processes must voluntarily yield, which may not happen promptly.
Examples:
Legacy systems like Windows 3.x and Mac OS 9.
Some embedded systems where simplicity is preferred over multitasking.

** Physical memory Vs Virtual memory:

Virtual memory is, among other things, an abstraction to give the programmer the illusion of having infinite memory available on their system.

Virtual memory mappings are made to correspond to actual physical addresses. The operating system creates and deals with these mappings - utilizing the page table, among other data structures to maintain the mappings. Virtual memory mappings are always found in the page table or some similar data structure (in case of other implementations of virtual memory, we maybe shouldn't call it the "page table"). The page table is in physical memory as well - often in kernel-reserved spaces that user programs cannot write over.

** File Access:
	Sequential Access - Information in the file is processed in order, one record after the other.Compilers will use this
	Direct Access - allow programs to read and write records rapidly in no particular order.Databases are often of this type.

** Holes in a file:
A hole in a file refers to a portion of a file that is logically allocated but does not consume actual storage on disk. It often appears in sparse files, which are files designed to save disk space when large regions of the file contain only zeros.

** Why Create Holes?
To save disk space: Instead of physically storing zeros, the file system only stores metadata indicating the presence of a hole.
Used in applications like database snapshots, disk images, or virtual memory swap files, where zero-filled regions are common.
	int fd = open("file_with_hole", O_CREAT | O_WRONLY, 0644);
    write(fd, "Hello", 5);
    lseek(fd, 1024 * 1024, SEEK_SET);
    write(fd, "World", 5);
This creates a file with a hole of approximately 1 MB between "Hello" and "World"

** Sparse File:
A sparse file is a type of file that allows parts of its data to remain unallocated (i.e., not physically stored on disk).
dd if=/dev/zero of=sparse_file bs=1 count=0 seek=1G //Creates a sparse file

** Sticky Bit: 
The sticky bit is a permission setting in Unix-like operating systems that can be applied to directories. It is primarily used to control user access to files in a shared directory.

Without a sticky bit: Any user with write permissions to the directory can delete or modify any file within it.
With a sticky bit: Only the file owner, the directory owner, or the root user can delete or modify files in the directory.
chmod +t directory_name //Add a sticky bit

** Inode:
An inode (index node) is a data structure in a file system that stores information about a file or directory, like its type, size, permissions, ownership, and link count.
The link count in an inode tracks the number of references (or "links") to that file or directory.

** File table:
The file table is an array of pointers to kernel file structures representing open files. When making file- I/O system calls, processes refer to files by an integer, known as a file descriptor (fd), that the kernel uses to index into this table.

Fork: Process is created.
Clone: Thread is created.

The clone() system call behaves identically to fork() , except that it accepts as arguments a set of flags that dictate what resources are shared between the parent and child (whereas a process created with fork() shares no resources with its parent).

CLONE_FS File-system information is shared.
CLONE_VM The same memory space is shared.
CLONE_SIGHAND Signal handlers are shared.
CLONE_FILES The set of open files is shared.

** Scheduling:
Fair Scheduling
It eliminates time slices in the traditional sense. Instead of time slices, all processes are allotted a proportion of the processor’s time. CFS calculates how long a process should run as a function of the total number of runnable processes.
To start, CFS says that if there are N runnable processes, then each should be afforded 1/N of the processor’s time. CFS then adjusts this allotment by weighting each process’s allotment by its nice value. Processes with the default nice value have a weight of 1—their priority is unchanged. Processes with a smaller nice value (higher priority) receive a higher weight, while processes with a larger nice value (lower priority) receive a lower weight. CFS then runs each process for a “time slice” proportional to the process’s weight divided by the total weight of all runnable processes.
To calculate the actual length of time a process runs, CFS relies on a configurable variable called target latency, which is the interval of time during which every runnable task should run at least once. For example, assume that the target latency is 10 milliseconds. Further assume that we have two runnable processes of the same priority.Each of these processes has the same weight and therefore receives the same proportion of the processor’s time. In this case, with a target latency of 10 milliseconds, the first process runs for 5 milliseconds, then the other process runs for 5 milliseconds, then the first process runs for 5 milliseconds again, and so forth. If we have 10 runnable processes, then CFS will run each for a millisecond before repeating. But what if we had, say, 1,000 processes? Each process would run for 1 microsecond if we followed the procedure just described. Due to switching costs, scheduling processes for such short lengths of time is inefficient. CFS consequently relies on a second configurable variable, the minimum granularity, which is a minimum length of time any process is allotted the processor. All processes, regardless of the target latency, will run for at least the minimum granularity.
Real-Time Scheduling
Scheduling is done based on FCFS and Round Robin.In both cases, each process has a priority in addition to its scheduling class. The scheduler always runs the process with the highest priority. Among processes of equal priority, it runs the process that has been waiting longest.

Management of Physical Memory:
•ZONE DMA - devices can only access the lower 16 MB of physical memory using DMA .On these systems, the first 16MB of physical memory comprise ZONE DMA
•ZONE DMA32 - devices can only access the lower 4GB of physical memory using DMA .On these systems, the first 16MB of physical memory comprise ZONE DMA
•ZONE HIGHMEM - the kernel is mapped into the first 896 MB of the address space; the remaining memory is referred to as high memory and is allocated from ZONE HIGHMEM .
•ZONE Normal - comprises everything else —the normal, regularly mapped pages

kmalloc() service allocates entire physical pages on demand but then splits them into smaller pieces.Memory regions claimed by the kmalloc() system are allocated permanently until they are freed explicitly with a corresponding call to kfree()
Another strategy adopted by Linux for allocating kernel memory is known as slab allocation. A slab is used for allocating memory for kernel data structures

The page cache is the kernel’s main cache for files and is the main mechanism through which I/O to block devices is performed.

** Virtual Memory:
The logical view organizes the address space into regions, with metadata stored in vm_area_struct.
The physical view focuses on the actual storage and mapping of pages, managed via the page tables.
The kernel uses page-management routines to handle page faults and other memory-related operations, allowing the two views to interact seamlessly.
1. Logical View of the Address Space
Definition:
The logical view describes the layout of the address space as understood by the virtual memory system. This view defines how memory regions are logically organized.

** Address Space Regions:
The address space is divided into non-overlapping regions.
Each region represents a continuous, page-aligned subset of the address space.
Each region has specific properties, such as:
Permissions (read, write, execute).
Associated files (e.g., shared libraries, mapped files).
vm_area_struct:

Internally, each region is represented by a structure called vm_area_struct.
This structure holds the region's attributes and metadata.
Efficient Lookups:

To find which region corresponds to a given virtual address, the regions are stored in a balanced binary tree, enabling fast lookups.
2. Physical View of the Address Space
Definition:
The physical view describes the actual location of each page of virtual memory, whether it is in physical memory (RAM) or on disk (in case of paging/swapping).

** Hardware Page Tables:
The physical view is stored in the page tables, which are hardware structures that map virtual addresses to physical memory locations.
Page-Management Routines:

When a process tries to access a page that is not in memory (e.g., on disk), the kernel invokes routines to manage the page:
These routines handle page faults (e.g., load the page from disk into RAM).They ensure the page is mapped into the process's page table.

Each vm_area_struct in the logical view points to a table of functions that implement page-management functionality for the corresponding memory region.These functions handle operations like:Reading or writing to unavailable pages.Mapping files into memory.
By abstracting the management of different memory regions into these functions, the central memory-management code doesn’t need to deal with the specific details of each type of memory region.

** Lifetime of a Virtual Address Space:
The kernel creates a new virtual address space in two situations: when a process runs a new program with the exec() system call and when a new process is created by the fork() system call. The first case is easy. When a new program is executed, the process is given a new, completely empty virtual address space. It is up to the routines for loading the program to populate the address space with virtual memory regions.The second case, creating a new process with fork() , involves creating a complete copy of the existing process’s virtual address space. The kernel copies the parent process’s vm area struct descriptors, then creates a new set of page tables for the child. The parent’s page tables are copied directly into the child’s, and the reference count of each page covered is incremented. Thus, after the fork, the parent and child share the same physical pages of memory in their address spaces.

Virtual memory is a memory management technique that provides an “idealized” view of memory to applications, allowing them to use more memory than is physically available in the system. It abstracts the physical memory by using a combination of hardware and software to give processes their own virtual address space. Here's an overview:

** How Virtual Memory Works:
** Address Translation:
Virtual memory uses a page table to map virtual addresses to physical addresses.
The CPU generates virtual addresses, which are then translated into physical addresses using a memory management unit (MMU).
Paging:

Memory is divided into small, fixed-size units called pages (usually 4 KB in size).
The operating system swaps pages in and out of physical memory from a storage device (like a hard disk or SSD) to manage memory demands.
Demand Paging:

Only the pages currently needed are loaded into RAM, reducing memory usage and allowing multiple processes to run concurrently.
Swap Space:

When physical memory is exhausted, the OS moves inactive pages to a reserved area on disk called the swap space, freeing up RAM for active processes.
Advantages:
Isolation and Security: Each process operates in its own virtual address space, preventing interference between processes.
Efficient Memory Usage: It allows multiple processes to share physical memory efficiently, as only necessary parts of programs are loaded.
Large Address Space: Programs can use more memory than physically available, as the virtual address space is much larger.
Disadvantages:
Performance Overhead: Translating addresses and swapping pages between memory and disk can cause latency.
Disk Usage: Heavy use of swap space can degrade system performance (a condition known as thrashing).
Example in Linux:
The Linux kernel uses a virtual memory system based on demand paging and employs structures like vm_area_struct to manage memory regions of a process.

The EXT4 file system is organized into 
superblocks, 
block groups, 
inodes, 
data blocks, with additional features like 
journaling and 
extent trees 
