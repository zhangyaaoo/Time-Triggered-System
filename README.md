# Time-Triggered-System
Time-Triggered Cooperative &amp; Preemptive Scheduler

This is a simple example of a time-triggered co-operative and preemptive mixed scheduler, based on the designs by Dr Michael J. Pont (see http://www.safetty.net/training/beginners) 

You can download the **complete book** (PDF file) [here](https://www.safetty.net/download/pont_pttes_2001.pdf)

# Quick Start

- First of all, we have to configure the Systick timer, and call `SCH_Update` in interrupt service routine.
- Second , after the initialization of hardware, before the main loop, we need to call the function `hSCH_Init` to initialize some Scheduler's data.
- Then, add the tasks, use the function `SCH_Add_Task` .
- Now, we can start the scheduler by `SCH_Start` . In the main loop, we need to exec `hSCH_Dispatch_Tasks` .