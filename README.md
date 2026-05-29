Multi-Level Process Scheduler System (BLG223E)
A robust, multi-level process scheduling simulation implemented in C++ for the BLG223E Data Structures course at Istanbul Technical University (ITU).
The project models a complex Operating System process scheduler using custom-built hierarchical data structures (Deque, Queue, and Stack) without relying on the Standard Template Library (STL). It includes comprehensive behavioral verification using the modern munit testing framework.
🛠️ System Architecture and Data Structures
The simulation models process generation, dynamic entry, execution, and failure tracking through an interconnected network of custom data structures:
1. Process Core (type_process)
PROCESS Struct: Represents the atomic unit of execution, tracking a unique process ID (pid) and its implementation priority.
2. Hierarchical Queue Layer (process_queue)
PROCESS_QUEUE Struct: A fixed-size array-based queue (QUEUE_SIZE = 5) representing a batch of tasks. Processes from initial_processes.txt are batched into these queues based on their isHead property.
3. High-Level Scheduler (process_manager)
PROCESS_MANAGER Struct: Implemented as a Circular Double-Ended Queue (Deque) with a capacity of MAX_PROCESS = 50. It handles execution priorities by allowing efficient process queues to be inserted or deleted from both the front and rear boundaries.
4. Dynamic Execution and Failure Pipelines
INSERTION_QUEUE: A FIFO queue tracking dynamic workloads (arriving_processes.txt) injected into the simulation at specific runtime loops (iteration).
FAILURE_STACK: A LIFO array-based stack (MAX_FAILED = 10) designed to capture and hold process queues that fail strict algorithmic assertions during the core simulation loop (e.g., fault conditions like pid % 8 == 0).
📂 Project Directory Layout
src/: Implementation files (.cpp) containing core simulation and data structure logic.
include/: Header declarations (.h) with class and struct definitions.
lib/munit/: Integrated munit testing framework core.
tests/: Test execution suites and behavioral test cases.
initial_processes.txt: Static boot-up workload configuration.
arriving_processes.txt: Runtime dynamically arriving workload configuration.
Makefile: Multi-target compilation configuration.
runme.sh: Environment initialization script.
🚀 Building and Running
Prerequisites
Ensure you have a C++ toolchain (g++ or clang) and standard utilities installed (make, sh).
Quick Start
To configure your local environment and run the complete pipeline with a single command, execute:
sh runme.sh
Manual Compilation via Makefile
Compile both primary binaries and test suites: make
Run the main scheduler simulation: ./bin/main
Clean compiled objects and binaries: make clean
🧪 Unit Verification Suite
Reliability is ensured via isolated test suites managed through munit. The suite evaluates structural integrity, file parsers, and edge states.
To run the complete test suite, execute: ./bin/tests
Verified Behaviors:
State isolation upon initializing the PROCESS_MANAGER and INSERTION_QUEUE.
Structural conversion constraints when streaming flat input configurations into multi-level process entities.
Dynamic interruption checks verifying that FAILURE_STACK accurately sequesters faulted execution streams during runtime stress testing.
