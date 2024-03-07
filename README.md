# Dining Philosophers Problem

This project provides a solution to the Dining Philosophers Problem implemented in C.


## Overview

The Dining Philosophers Problem is a classic concurrency problem in which multiple philosophers sit at a round table. Each philosopher has a bowl of spaghetti in front of them, and forks are placed between each pair of adjacent philosophers. To eat, a philosopher needs to hold two forks, one in each hand. However, they must also alternate between thinking, eating, and sleeping.

The challenge in this problem is to avoid deadlocks and ensure that no philosopher starves while maximizing parallelism. Deadlock occurs when each philosopher holds one fork and waits indefinitely for the other, while starvation happens when a philosopher is unable to acquire both forks for an extended period, preventing them from eating indefinitely. Effective solutions to this problem require careful synchronization and resource allocation to ensure fairness and efficiency.

It's important to note that the philosophers do not communicate with each other and are not aware of the state of others. They simply follow the defined rules for picking up forks and eating without considering what other philosophers are doing.

<img  src="https://cdn.discordapp.com/attachments/1021438070727381063/1210259840891617352/Design_sem_nome_4.png?ex=65e9e94f&is=65d7744f&hm=162c1b6285df9edc49a8055cae9da1452982f8c2f85d353e05112fe841d9cc6d&"  width="200"  height="200">

## Usage

1. Clone the repository:

    ```bash
    git clone https://github.com/IsabelaGenial/42_Philosophers
    ```

2. Compile the code:

    ```bash
    cd 42_Philosophers
    make
    ```

3. Run the program:

    ```bash
    ./dining_philosophers "number_of_philosophers" "time_to_die" "time_to_eat" "time_to_sleep" [number_of_times_each_philosopher_must_eat]
    ```

## Configuration

- **number_of_philosophers:** The number of philosophers and also the number of forks.
- **time_to_die (in milliseconds):** If a philosopher hasn’t started eating within time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
- **time_to_eat (in milliseconds):** The time it takes for a philosopher to eat. During this time, they need to hold two forks.
- **time_to_sleep (in milliseconds):** The time a philosopher spends sleeping.
- **number_of_times_each_philosopher_must_eat (optional argument):** If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops.

## How it works

In my solution, I addressed the problem of resource contention by introducing a strategy where philosophers alternate between accessing forks on their left and right sides. Specifically, even-numbered philosophers (Philosopher 0, 2, 4, etc.) start by attempting to acquire the fork on their right side, while odd-numbered philosophers (Philosopher 1, 3, 5, etc.) start by attempting to acquire the fork on their left side.

This strategy effectively blocks odd-numbered philosophers from accessing the resource, allowing even-numbered philosophers to use the forks on their right side without interference. This creates parallelism between the even-numbered philosophers. Once they complete their meal, the odd-numbered philosophers are then allowed to access the forks on their left side, allowing them to proceed with their meals without interference from the even-numbered philosophers.

By alternating between the left and right sides for accessing forks based on the philosopher's number, my solution prevents deadlock and ensures that all philosophers eventually get access to the resources they need to eat.

<div>
<img  src="https://cdn.discordapp.com/attachments/1021438070727381063/1215410192444031056/Philosopher_Project_Flowchart_-_Exemplo_de_fluxograma_de_central_de_atendimento_5.png?ex=65fca5f3&is=65ea30f3&hm=6b213dacb460312ee5dae0b06e53a6be0d8c1a47ba58ec0720bd91d628c84340&"  width=""  height="450">
<div/>
    
## Routine of philosophers
<div>
<img  src="https://cdn.discordapp.com/attachments/1021438070727381063/1215410192444031056/Philosopher_Project_Flowchart_-_Exemplo_de_fluxograma_de_central_de_atendimento_5.png?ex=65fca5f3&is=65ea30f3&hm=6b213dacb460312ee5dae0b06e53a6be0d8c1a47ba58ec0720bd91d628c84340&"  width=""  height="450">
<div/>
