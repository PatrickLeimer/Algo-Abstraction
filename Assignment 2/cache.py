#I dont know how to do linked lists in python
from queue import Queue

class FIFO:
    def __init__(self, k):
        self.k = k
        self.queue = Queue(maxsize = 3) #https://www.geeksforgeeks.org/python/queue-in-python/
        self.set = set() #for checking if an element is in the queue in O(1) time
        self.miss_count = 0
    
    def request(self, r):
        if r in set:
            return True
        
        if self.queue.full():
            l = self.queue.get()
            self.set.remove(l)

        self.queue.put(r)
        self.set.add(r)
        self.miss_count +=1
        return False

class LRU:
    def __init__(self, k):
        self.cache = []
        self.miss_count = 0
        self.k = k

    def request(self, r):
        pass