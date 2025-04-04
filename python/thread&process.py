# import time
# import threading

# mylist = []

# def job(n):
#     mylist.append(n)
#     print(f"Worker number {n}")

#     # print(f"worker number {n}:")
#     # v = 0
#     # for i in range(10000):
#     #     for j in range(20000):
#     #         v += i * j
#     # print(f"Worker number {n}: done")

# def test_single_job():
#     begin = time.time()
#     job(0)
#     end = time.time()

#     print("Single job done")
#     print(f"Working time {end-begin} s")

# def test():
#     workers = []

#     begin = time.time()

#     for i in range(24):
#         worker = threading.Thread(target= job, args = (i,))
#         workers.append(worker)
#         worker.start()

#     for worker in workers:
#         worker.join()

#     end = time.time()

#     print("Done")
#     print(f"Working time {end-begin} s")

#     print(len(mylist))
#     print(mylist)
# if __name__ == "__main__":
#     test()

#================================================================================

import multiprocessing
import time
from multiprocessing import Queue
from multiprocessing import Pipe

mylist = []

def job(n, pipe):
    pipe.send(n)
    v = 0
    for i in range(10000):
        v += 1
    print(f"Worker number {n}: done")
    print(len(mylist))
    print(mylist)



def test_single_job():
    begin = time.time()
    job(0)
    end = time.time()

    print("Single job done")
    print(f"Working time {end-begin} s")

def test():
    
    workers = []

    pipes = []

    begin = time.time()

    for i in range(24):
        pipeParent, pipeChild = Pipe()

        worker = multiprocessing.Process(target= job, args = (i, pipeChild))
        workers.append(worker)
        pipes.append(pipeParent)
        worker.start()

    for worker in workers:
        worker.join()

    mylist = []

    number = 0
    new_pipes = pipes

    while number < 24:
        for p in new_pipes:
            data = p.recv()
            if data is not None:
                number += 1

                mylist.append(data)
                pipes.remove(p)

        new_pipes = pipes

        time.sleep(1)

    end = time.time()

    print("Done")
    print(f"Working time {end-begin} s")

    print(len(mylist))
    print(mylist)
if __name__ == "__main__":
    test()