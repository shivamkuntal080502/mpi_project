# Distributed Treasure Hunt Game using MPI + OpenMP

A multiplayer console-based parallel game built using MPI (Message Passing Interface) and OpenMP in C++.

Each MPI process acts as an independent player moving inside a shared grid to find a hidden treasure. The first player to reach the treasure wins the game.

---

## Features

* Distributed multiplayer gameplay using MPI
* Parallel movement logic using OpenMP
* Real-time grid visualization
* Randomized player movement
* Treasure detection system
* Winner announcement
* Scalable with multiple processes
* High Performance Computing (HPC) concepts

---

## Tech Stack

* C++
* MPI
* OpenMP
* Linux / Ubuntu

---

## Concepts Used

### MPI Concepts

* `MPI_Init`
* `MPI_Comm_rank`
* `MPI_Comm_size`
* `MPI_Bcast`
* `MPI_Gather`
* `MPI_Finalize`

### OpenMP Concepts

* Parallel regions
* Concurrent movement simulation
* Shared memory parallelism

---

## Project Structure

```bash
mpi-treasure-hunt/
│
├── treasure_hunt.cpp
├── README.md
└── screenshots/
```

---

## Installation

### Install MPI

#### Ubuntu/Debian

```bash
sudo apt update
sudo apt install mpich
```

### Verify Installation

```bash
mpic++ --version
```

---

## Compilation

```bash
mpic++ -fopenmp treasure_hunt.cpp -o game
```

---

## Running the Game

Run with 4 players (MPI processes):

```bash
mpirun -np 4 ./game
```

---

## Game Rules

* Every MPI process acts as a player.
* Players move randomly inside a 10x10 grid.
* A treasure is hidden at a secret location.
* The first player reaching the treasure wins.
* The game ends automatically after a winner is found.

---

## Sample Output

```bash
Treasure Hidden at Secret Location!

Turn 1

========================
. . . . . . . . . .
. . . . . . . . . .
. . . . . . . . . .
. . . 0 . . . . . .
. . . . . . . . . .
. . . . T . . . . .
. . . . . . . . . .
. . . . . 1 . . . .
. . . . . . . 2 . .
. . . . . . . . . 3
========================

Player 2 found the treasure!

Game Finished
Execution Time: 5.231 seconds
```

---

## How It Works

### Step 1: Initialize MPI

Each process gets a unique rank ID.

### Step 2: Generate Treasure

The master process creates the treasure location.

### Step 3: Broadcast Treasure Coordinates

Treasure position is shared with all processes using `MPI_Bcast`.

### Step 4: Parallel Movement

Each process computes movement using OpenMP.

### Step 5: Gather Player Positions

Master process collects all player locations using `MPI_Gather`.

### Step 6: Winner Detection

If any player reaches the treasure, the game ends.

---

## Future Improvements

* GUI version using SDL/OpenGL
* Multiplayer networking
* AI-based bots
* Distributed battle royale mode
* Obstacles and power-ups
* Dynamic map generation
* Leaderboard system

---

## Suggested GitHub Screenshots

You can add:

* Terminal gameplay screenshots
* Grid updates
* Multiple player movement
* Winner announcement

Place them inside:

```bash
screenshots/
```

---

## Why This Project?

This project demonstrates:

* Parallel Computing
* Distributed Systems
* Inter-process communication
* Hybrid MPI + OpenMP programming
* Real-world HPC concepts

It is much more interesting than traditional MPI assignments and looks great on GitHub and Resume.

---

## Resume Description

> Developed a distributed multiplayer Treasure Hunt game using MPI and OpenMP featuring parallel player movement, inter-process communication, and real-time game state synchronization.

---

## Tags

```text
MPI OpenMP HPC Parallel-Computing Distributed-Systems Cpp Multiplayer-Game
```

---

## Author

Shivam Kuntal
B.Tech AI & Data Engineering
MNIT Jaipur
