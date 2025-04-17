import multiprocessing
import time
from multiprocessing import Pipe

def jobConsumer (pipe):
    while True:
        msg = pipe.recv()
        if msg == 'DONE':
            break
        print("Consumer done")

def jobProducer(pipe, number):
    for i in range(number):
        pipe.send(1024 * " ")
    pipe.send('DONE')
    print("Producer done")

def test():
    for number in [10**4, 10**5, 10**6]:
        pipeParent, pipeChild = Pipe()

        consumer = multiprocessing.Process(target=jobConsumer, args=(pipeChild,))
        consumer.start()

        begin = time.time()

        jobProducer(pipeParent, number)
        consumer.join()

        end = time.time()

        print(f"{end-begin} s")

if __name__ == '__main__':
    test()