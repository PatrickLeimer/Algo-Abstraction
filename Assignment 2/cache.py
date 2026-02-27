from pathlib import Path
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

            for s in self.cache: #n^2 ahh
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


def parseInputFile(path):
    tokens = path.read_text().split()

    k = int(tokens[0])
    m = int(tokens[1])
    reqTokens = tokens[2:]
    rl = list(map(int, reqTokens[:m]))

    return k, m, rl

def runCaches(k, rl):
    fifo = FIFO(k)
    lru = LRU(k)
    opt = OPTFF(k)

    fifo.handleRequests(rl)
    lru.handleRequests(rl)
    opt.handleRequests(rl)

    return (
        f"FIFO  : {fifo.miss_count}\n"
        f"LRU   : {lru.miss_count}\n"
        f"OPTFF : {opt.miss_count}\n"
    )

def main():
    here = Path(__file__).resolve().parent
    in_files = sorted(here.glob("*.in"))

    if not in_files:
        print("No .in files found in:", here)
        return

    for in_path in in_files:
        out_path = in_path.with_suffix(".out")
        k, m, rl = parseInputFile(in_path)
        output = runCaches(k, rl)
        out_path.write_text(output)
        print(f"Wrote {out_path.name} (from {in_path.name})")

if __name__ == "__main__":
    main()          

#Note for Patrick: Question 3 looks like a variation of the exchange proof we saw in class but for caching instead           
            
                
                    

