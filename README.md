# Philosophers 🍝

A solution to the classic Dining Philosophers Problem implemented in C, demonstrating synchronization and thread management.

## Overview

The Dining Philosophers Problem is a classic synchronization problem that illustrates challenges in concurrent programming. This implementation uses threads and mutexes to prevent deadlocks and ensure proper resource sharing between philosophers.

## Features

- Thread-safe implementation using mutexes
- Deadlock prevention with proper locking strategies
- Configurable parameters for number of philosophers, time to die, eat, sleep, and optional meal counts
- Real-time monitoring of philosopher states
- Memory leak-free with proper cleanup

## Installation

Clone the repository and build the project:
```bash
git clone <your-repository-url>
cd philosophers
make
```
## Usage

Run the program with the following arguments:
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
Parameters:
- ```n_philo```: Number of philosophers (and forks)
- ```t_die```: Time in milliseconds before a philosopher dies if they don't eat
- ```t_eat```: Time in milliseconds it takes for a philosopher to eat
- ```t_sleep```: Time in milliseconds a philosopher spends sleeping
- ```times_eat``` (optional): If specified, the simulation stops when all philosophers have eaten at least this many times

Examples:
```bash
./philo 5 800 200 200
./philo 4 410 200 200 7
./philo 200 410 200 200
```
## Output

The program displays philosopher actions in the format:
[timestamp_in_ms] [philosopher_id] [action]

Possible actions:
- is thinking
- has taken a fork
- is eating
- is sleeping
- died

Example output:
[0000100] 1 has taken a fork
[0000100] 1 is eating
[0000300] 1 is sleeping
[0000500] 1 is thinking

## Building

```make``` - Build the project
```make clean``` - Remove object files
```make fclean``` - Remove object files and executable
```make re``` - Rebuild the project

## Implementation Details

- Threads: Each philosopher runs in its own thread
- Mutexes: Forks are protected by mutex locks
- Timing: Uses precise millisecond timing
- Memory Management: Proper allocation and cleanup
- Error Handling: Comprehensive input validation and error checking

## Rules

1. Philosophers alternate between thinking, eating, and sleeping
2. A philosopher needs two forks to eat
3. A philosopher dies if they don't eat within time_to_die milliseconds
4. The program stops when a philosopher dies or all philosophers have eaten the required number of times

## Notes

- All times are in milliseconds
- The program ensures no data races or deadlocks
- Input values are validated for correctness
- The solution is efficient and handles edge cases

## Author

Samuel Bruma

## License

This project is part of the 42 Common Core.
