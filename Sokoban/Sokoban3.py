import queue
class situation:
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
        visited = {}
        visited[s.magazineBoy] = 1
        bfs = queue.Queue()
        bfs.put((s.magazineBoy[0],s.magazineBoy[1],""))
        while not bfs.empty():
            cords = bfs.get()
            for move in moves:
                wasBox = 0
                for index in range(s.numberOfBoxes):
                    if (cords[0]+move[0],cords[1]+move[1])==s.boxesCords[index]:
                        wasBox = 1
                        if T[s.boxesCords[index][0]+move[0],s.boxesCords[index][1]+move[1]]!='W':
                            boxBlocked = 0
                            for box in s.boxesCords:
                                if box == (s.boxesCords[index][0]+move[0],s.boxesCords[index][1]+move[1]):
                                    boxBlocked = 1
                                    break
                            if boxBlocked == 0:
                                sprim = situation(s)
                                sprim.magazineBoy = (cords[0]+move[0],cords[1]+move[1])
                                sprim.boxesCords[index] = (sprim.boxesCords[index][0]+move[0],sprim.boxesCords[index][1]+move[1])
                                sprim.value = aStar(sprim)
                                toHash = sprim.encodeToString()
                                if not toHash in hashMap:
                                    slowo = hashMap[baseHash]
                                    slowo += cords[2]
                                    slowo += movesMapping[move]
                                    hashMap[toHash] = slowo
                                    if sprim.value == 0:
                                        return hashMap[toHash]
                                    q.put(sprim)
                                break
                            break
                        break
                if wasBox == 0:
                    if T[cords[0]+move[0],cords[1]+move[1]] != 'W' and (not (cords[0]+move[0],cords[1]+move[1]) in visited):
                        visited[cords[0]+move[0],cords[1]+move[1]] = 1
                        bfs.put((cords[0]+move[0],cords[1]+move[1],cords[2]+movesMapping[move]))


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
outcik = search(start)
out.write("%s" % outcik)
file.close()
out.close()
