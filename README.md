# GitLite-A-Simplified-Version-Control-System
A simplified Git-like version control system in C++ that stores CSV data in tree structures (AVL, B-Tree, Red-Black) as separate files. Processes data line-by-line to minimize memory usage while supporting branches, commits, and efficient change detection using Merkle trees.





GitLite: A Simplified Version Control System
Project Overview
GitLite is a simplified version control system inspired by Git, implemented in C++ using tree data structures. The system efficiently handles versioning and data synchronization, addressing challenges in collaborative environments when working with large files.
Key Features

Multiple Server Support: Set up and manage multiple servers for version control and file synchronization
Tree-Based Data Structure: Choose between AVL Tree, B Tree, or Red-Black Tree for organizing data
Efficient Data Storage: Store tree nodes in separate files to optimize memory usage
Branching System: Create and manage different branches for parallel development
Commit History: Track changes with detailed logs and messages
Data Integrity: Detect data corruption through Merkle Tree hash verification
Efficient Change Transfer: Transfer only modified parts of the tree rather than entire datasets

Core Functionalities

Repository Initialization (init): Create a new repository, select tree type, and organize CSV data
Version Control (commit): Save changes with descriptive messages
Branch Management (branch, checkout): Create and switch between development branches
History Tracking (log): View commit history with timestamps and messages
Branch Operations (merge, delete-branch): Manage project branches
System Status (current-branch, branches): Monitor repository state
Persistence (save, load): Save and restore repository state

Technical Implementation

Written in C++ with focus on efficient data structures
Uses cryptographic hashing for data integrity verification
Implements Merkle Trees for efficient change detection
Supports hash generation via custom algorithm or SHA-256
Optimized for handling large datasets with minimal memory usage

Purpose
This system aims to provide a secure, efficient, and cost-effective version control solution that:

Ensures data integrity
Facilitates easy collaboration
Reduces redundancy in data transfers
Optimizes storage and bandwidth usage

GitLite is particularly valuable for teams working with large files who need to track changes effectively without the overhead of transferring entire files after each modification.RetryAadd another feature that this project doest load the whole data into proccessor but read the file line by line and stores it in the file based  tree choosen by user (AVL tree , red lack tree )EditGitLite: A Simplified Version Control System
Project Overview
GitLite is a simplified version control system inspired by Git, implemented in C++ using tree data structures. The system efficiently handles versioning and data synchronization, addressing challenges in collaborative environments when working with large files.
Key Features

Multiple Server Support: Set up and manage multiple servers for version control and file synchronization
Tree-Based Data Structure: Choose between AVL Tree, B Tree, or Red-Black Tree for organizing data
Efficient Data Storage: Store tree nodes in separate files to optimize memory usage
Memory-Efficient Processing: Read and process large files line by line without loading entire datasets into memory
File-Based Tree Storage: Each node of the chosen tree structure (AVL, Red-Black, B Tree) is stored in separate files rather than in RAM
Branching System: Create and manage different branches for parallel development
Commit History: Track changes with detailed logs and messages
Data Integrity: Detect data corruption through Merkle Tree hash verification
Efficient Change Transfer: Transfer only modified parts of the tree rather than entire datasets

Core Functionalities

Repository Initialization (init): Create a new repository, select tree type, and organize CSV data
Line-by-Line Processing: Process large CSV files one line at a time to minimize memory usage
Disk-Based Tree Structure: Store and manage tree nodes in the file system rather than RAM
Version Control (commit): Save changes with descriptive messages
Branch Management (branch, checkout): Create and switch between development branches
History Tracking (log): View commit history with timestamps and messages
Branch Operations (merge, delete-branch): Manage project branches
System Status (current-branch, branches): Monitor repository state
Persistence (save, load): Save and restore repository state

Technical Implementation

Written in C++ with focus on efficient data structures
Uses cryptographic hashing for data integrity verification
Implements Merkle Trees for efficient change detection
Supports hash generation via custom algorithm or SHA-256
Optimized for handling large datasets with minimal memory usage through line-by-line processing
File-based tree nodes to reduce RAM requirements and support massive datasets

Purpose
This system aims to provide a secure, efficient, and cost-effective version control solution that:

Ensures data integrity
Facilitates easy collaboration
Reduces redundancy in data transfers
Optimizes storage and bandwidth usage
Minimizes memory consumption by avoiding full dataset loading

GitLite is particularly valuable for teams working with large files who need to track changes effectively without the overhead of transferring entire files after each modification or loading entire datasets into memory.