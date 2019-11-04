# Time-Triggered-System
Time-Triggered Cooperative &amp; Preemptive Scheduler

This is a simple example of a time-triggered co-operative and preemptive mixed scheduler, based on the designs by Dr Michael J. Pont (see http://www.safetty.net/training/beginners) 

You can download the **complete book** (PDF file) [here](https://www.safetty.net/download/pont_pttes_2001.pdf)

# Quick Start

- First of all, we have to configure the Systick timer, and call `SCH_Update` in interrupt service routine.
- Second , after the initialization of hardware, before the main loop, we need to call the function `hSCH_Init` to initialize some Scheduler's data.
- Then, add the tasks, use the function `SCH_Add_Task` .
- Now, we can start the scheduler by `SCH_Start` . In the main loop, we need to exec `hSCH_Dispatch_Tasks` .

# Examples

The picture used below and some contents come form [here](https://github.com/chrispbarlow/arduino-tasks). Thank the author!

## Basic Usage

```c
SCH_Add_Task((TASK_SCH *)Task_C, 0, 1, 1, 1);//exec once every 1 systicks(eg:10ms)
SCH_Add_Task((TASK_SCH *)Task_D, 0, 5, 1, 1);//exec once every 5 systicks
```

![eg-1](https://raw.githubusercontent.com/zhangyaaoo/ImageBed/master/pttes/eg-1.png)

## Increase task priority

**The task that we creates earlier has a higher priority.** 

```c
SCH_Add_Task((TASK_SCH *)Task_D, 0, 5, 1, 1);//exec once every 5 systicks(eg:10ms)
SCH_Add_Task((TASK_SCH *)Task_C, 0, 1, 1, 1);//exec once every 1 systicks
```

![eg-2](https://raw.githubusercontent.com/zhangyaaoo/ImageBed/master/pttes/eg-2.png)

## Delayed exec of task

```c
SCH_Add_Task((TASK_SCH *)Task_A, 0, 5, 1, 1);//exec once every 1 systicks(eg:10ms)
SCH_Add_Task((TASK_SCH *)Task_B, 1, 10, 1, 1);//exec once every 10 systicks
```

![eg-3](https://raw.githubusercontent.com/zhangyaaoo/ImageBed/master/pttes/eg-3.png)

The task B will be delayed by one systick, from `SCH_Start` on. 

Task A will run every 50 ms starting at tick 0. Task B will run every 100 ms, but has an offset of 1, so it will first run in tick 1. It doesn't matter that Task B takes longer than 1 tick, because there is enough space for it to complete before Task A is run again.

But it's better not to let task takes longer than one systick.

And, the differrent delay time of task can let tasks execued staggered. This is what the delay  time matters.

## Preemptive Task

Here is an example:

![eg-4](https://raw.githubusercontent.com/zhangyaaoo/ImageBed/master/pttes/eg-4.png)

In the situation, Task E takes longer than 2 ticks and is a lower priority than task C, which is required to run in every tick.

Using standard (cooperative) scheduling, this will result in undesirable behaviour (priority inversion). Task C has to wait for Task E to complete, so even though it has a higher priority, it misses execution slots and runs late when Task E does complete.

This can be overcome by allowing Task C to interrupt Task E when it needs to run. This is known as 'task preemption' and is acheived by giving the fourth param `0` , like below: 

```c
SCH_Add_Task((TASK_SCH *)Task_C, 0, 1, 0, 1);//exec preempted, fourth param is 0
```

Now the tasks execute as required, with Task C maintaining its higher priority:

![eg-5](https://raw.githubusercontent.com/zhangyaaoo/ImageBed/master/pttes/eg-5.png)

**Task C should be very short**, and it takes up a little time.

# Task-oriented design 

1. convert long tasks (scheduled at infrequent intervals) into much shorter tasks (scheduled at frequent intervals). 将耗时长的任务拆分我频繁执行的小任务。

2. replace multiple tasks with a single task that performs different activities depending on the current state of the system. （状态机）。