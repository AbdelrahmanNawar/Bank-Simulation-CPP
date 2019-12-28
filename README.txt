This application is simulation for banking system.

First:
* you enter all clients by
1) his id.
2) his name.
3) the moment he enters.
4) the time needed for his transaction.
5) you press 0 if he has to exit from the queue to finished some paper work and return to the same queue again.
if 0 -> then 6) is entering the moment he will go out refering to the transaction time, then enter the time needed to finish his paper work.
else 6) would be pressing 0 to enter another client.


second:
* all clients would be added to linked list then sorted by their entering time.


Third:
* the Bank opens and starts the simulation by the following steps.

1) removed who finished his total transaction.

2) get the clients who finished the paper work back to their queues.

3) send the clients to do the paper work.

4) get the new comming clients and put them in queues

5) rearrange queues.


Fourth:
* some handled problems.
1) you can not rearrange a client sent to finish paper work to different queue.
2) you will have each loop to rearrange all clients to make the queue have equally close number of clients.
3) you should increament the queue's waiting time by the time spent by customer in it.

