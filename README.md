# FBnTaskSheduling

# Lab 3 - Research of disciplines of service of requests at limited resources
# Theory
Foreground-background is a scheduling algorithm that is used to control an execution of multiple processes on a single processor. It is based on two waiting lists, the first one is called foreground because this is the one in which all processes initially enter, and the second one is called background because all processes, after using all of their execution time in foreground, are moved to background.

When a process becomes ready it begins its execution in foreground immediately, forcing the processor to give up execution of the current process in the background and execute the newly created process for a predefined period. This period is usually 2 or more quanta. If the process is not finished after its execution in the foreground it is moved to background waiting list where it will be executed only when the foreground list is empty. After being moved to the background, the process is then run longer than before, usually 4 quanta. The time of execution is increased because the process obviously needs more than 2 quanta to finish (this is the reason it was moved to background). This gives the process the opportunity to finish within this newly designated time. If the process does not finish after this, it is then preempted and moved to the end of the background list.

# Realization

There are two streams in the program. One is used by the TaskSheduler class to process requests in queues, the other thread is used to generate tasks and send them to the first thread for processing.

# Functions 
taskSheduler::addTask(Task t)
To add task on process.

taskSheduler::work()
To start work with the tasks.

taskSheduler::getQueuesCount()
To get count of queues.

taskSheduler::setStop()
To stop accepting tasks.

![Result](https://github.com/Andrey2102/FBnTaskSheduling/blob/main/%D0%97%D0%B0%D0%BF%D0%B8%D1%81%D0%B0%D1%82%D0%B8.PNG)




















