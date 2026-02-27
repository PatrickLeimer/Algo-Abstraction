#I dont know how to do linked lists in python
from queue import Queue


#TODO: Add a function to FIFO and LRU that handles the entire list of requests. 
class FIFO:
    def __init__(self, k):
        self.k = k
        self.queue = Queue(maxsize = k) #https://www.geeksforgeeks.org/python/queue-in-python/
        self.set = set() #for checking if an element is in the queue in O(1) time
        self.miss_count = 0
    
    def request(self, r):
        if r in self.set:
            return True
        
        if self.queue.full():
            l = self.queue.get()
            self.set.remove(l)

        self.queue.put(r)
        self.set.add(r)
        self.miss_count +=1
        return False
    
    def handleRequests(self, rl): #rl is supposed to be the list with requests
        for r in rl:
            self.request(r)

class LRU: #I would normaly do a linked list with a hashmap for this, Ill just change the postion on the list
    def __init__(self, k):
        self.cache = []
        self.miss_count = 0
        self.k = k

    def request(self, r):
        if r in self.cache:
            self.cache.remove(r)
            self.cache.append(r) #add at the end
            return True
        
        if len(self.cache) == self.k:
            self.cache.pop(0) #remove at the beggining
            
        self.cache.append(r)
        self.miss_count += 1
        return False
    
    def handleRequests(self, rl): 
        for r in rl:
            self.request(r)

#I am guessing an optimal approach would have some form of max heap, I dont want to do allat  
class OPTFF: #This approach uses information from future requests, so all requests must be handled/looked at at the same time
    def __init__(self, k):
        self.cache = []
        self.miss_count = 0
        self.k = k

    def handleRequests(self, rl):
        for i  in range(len(rl)):
            r = rl[i]
            if r in self.cache:
                continue

            self.miss_count +=1
                
            if len(self.cache) < self.k:
                 self.cache.append(r)
                 continue

            max_dist = -1
            value = None

            for s in self.ache: #n^2 ahh
                try: #trying to avoid out of range exceptions
                    j = rl.index(s, i + 1)
                    dist = j - i
                except ValueError:
                    dist = float('inf')

                if dist > max_dist:
                    max_dist = dist
                    value = s
                
            self.cache.remove(value)
            self.cache.append(r)
            
                
           
            
                
                    

