import queue
class situation:
    # def __init__(self,sit):
    #     self.value = sit.value
    #     self.numberOfBoxes = sit.numberOfBoxes
    #     self.boxesCords = sit.boxesCords
    #     self.magazineBoy = sit.magazineBoy
    def __init__(self,sit=None):
        if sit == None:
            self.non_copy_constructor()
        else:
            self.copy_constructor(sit)
    def __lt__(self, other):
        return self.value < other.value
    def non_copy_constructor(self):
        self.value = 0
        self.numberOfBoxes = 0
        self.boxesCords = []
        self.magazineBoy = (0,0)
    def copy_constructor(self,sit):
        self.value = sit.value
        self.numberOfBoxes = sit.numberOfBoxes
        self.boxesCords = []
        for box in sit.boxesCords:
            self.boxesCords.append(box)
        self.magazineBoy = sit.magazineBoy
    def encodeToString(self):
        slowo = str(self.value)+str(self.numberOfBoxes)+str(self.magazineBoy[0])+str(self.magazineBoy[1])
        for box in self.boxesCords:
            slowo+=str(box[0])+str(box[1])
        return slowo

q = queue.PriorityQueue()
moves=[(1,0),(-1,0),(0,1),(0,-1)]
movesMapping={(1,0):"D",(-1,0):"U",(0,1):"R",(0,-1):"L"}
T = {}
hashMap = {}

def aStar(sit):
    licznik = 0
    for box in sit.boxesCords:
        if T[box]=='G':
            licznik+=1
    return sit.numberOfBoxes-licznik

def search(sit):
    sit.value = aStar(sit)
    firstHash = sit.encodeToString()
    hashMap[firstHash] = ""
    q.put(sit)
    while not q.empty():
        s = q.get()
        baseHash = s.encodeToString()
        for direction in moves:
            sprim = situation(s)
            wasBox = 0
            for index in range(sprim.numberOfBoxes):
                if sprim.boxesCords[index] == (sprim.magazineBoy[0]+direction[0],sprim.magazineBoy[1]+direction[1]):
                    wasBox = 1
                    if T[sprim.boxesCords[index][0]+direction[0],sprim.boxesCords[index][1]+direction[1]]!='W':
                        boxBlocked = 0
                        for boxprim in sprim.boxesCords:
                            if (boxprim[0],boxprim[1])==(sprim.boxesCords[index][0]+direction[0],sprim.boxesCords[index][1]+direction[1]):
                                boxBlocked=1
                                break
                        if boxBlocked==1:
                            break
                        sprim.magazineBoy = (sprim.magazineBoy[0]+direction[0],sprim.magazineBoy[1]+direction[1])
                        sprim.boxesCords[index] = (sprim.boxesCords[index][0]+direction[0],sprim.boxesCords[index][1]+direction[1])
                        sprim.value = aStar(sprim) + len(hashMap[baseHash])
                        toHash = sprim.encodeToString()
                        if not toHash in hashMap:
                            slowo = hashMap[baseHash]
                            slowo += movesMapping[direction]
                            hashMap[toHash] = slowo
                            if sprim.value == len(hashMap[baseHash]):
                                return hashMap[toHash]
                            q.put(sprim)
                        break
                    break
            if wasBox==0 and T[sprim.magazineBoy[0]+direction[0],sprim.magazineBoy[1]+direction[1]]!='W':
                sprim.magazineBoy = (sprim.magazineBoy[0]+direction[0],sprim.magazineBoy[1]+direction[1])
                sprim.value = aStar(sprim) + len(hashMap[baseHash])
                toHash = sprim.encodeToString()
                if not toHash in hashMap:
                    slowo = hashMap[baseHash]
                    slowo += movesMapping[direction]
                    hashMap[toHash] = slowo
                    if sprim.value == len(hashMap[baseHash]):
                        return hashMap[toHash]
                    q.put(sprim)
file = open("zad_input.txt","r")
lines = file.readlines()
x = 0
y = 0
start = situation()
for line in lines:
    for letter in line:
        if letter!="\n":
            if letter == 'K':
                start.magazineBoy = (x,y)
                T[x,y] = '.'
            if letter == 'B':
                start.numberOfBoxes+=1
                start.boxesCords.append((x,y))
                T[x,y] = '.'
            if letter == '*':
                start.numberOfBoxes+=1
                start.boxesCords.append((x,y))
                T[x,y] = 'G'
            if letter == '+':
                start.magazineBoy = (x,y)
                T[x,y] = 'G'
            if letter == 'G' or letter == 'W' or letter == '.':
                T[x,y]=letter
            y+=1
    x+=1
    y=0
out = open("zad_output.txt","w")
out.write("%s" % search(start))
file.close()
out.close()
