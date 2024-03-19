import re

class Address(object):
    def __init__(self):
        self.mask = ()
        self.memory = {}
    
    def parse_instr(self, instr):
        x = re.compile(r'^mem\[(\d+)\] = (\d+)\s?$')
        match = re.findall(x, instr)
        if match:
            match = match[0]
            self.memory[match[0]] = (int(match[1]) | self.mask[0]) & self.mask[1]
    
    def print(self):
        for key, value in self.memory.items():
            print(f"{key}: {value}")
    
    def sum(self):
        return sum(self.memory.values())

def make_mask(line):
    s = (line.strip())[7:]

    x = ['0'] * 36
    y = ['1'] * 36

    for (i, char) in enumerate(s):
        if char == 'X':
            continue
        elif char == '0':
            y[i] = '0'
        elif char == '1':
            x[i] = '1'
        else:
            print(f"Strange character {char} found.")
            continue
    
    x = ''.join(x)
    y = ''.join(y)
    return int(x, base=2), int(y, base=2)

class Address2(object):
    def __init__(self):
        self.masks = []
        self.memory = {}
    
    def parse_instr(self, instr):
        x = re.compile(r'^mem\[(\d+)\] = (\d+)\s?$')
        match = re.findall(x, instr)
        if match:
            match = match[0]
            for m in range(1, len(self.masks), 2):
                a = ((int(match[0]) | self.masks[0]) | self.masks[m]) & self.masks[m+1]
                self.memory[a] = int(match[1])
    
    def print(self):
        for key, value in self.memory.items():
            print(f"{key}: {value}")
    
    def sum(self):
        return sum(self.memory.values())

def make_mask_2(line):
    s = (line.strip())[7:]
    x = ['0'] * 36
    count = 0
    positions = []

    for (i, char) in enumerate(s):
        if char == 'X':
            count += 1
            positions.append(i)    
        elif char == '0':
            continue
        elif char == '1':
            x[i] = '1'
        else:
            print(f"Strange character {char} found.")
            continue

    masks = [''.join(x)]
    for r in range(0, 2**count):
        a = ['0'] * 36
        b = ['1'] * 36
        r = f"{r:0{len(positions)}b}"
        changed = [False, False]
        for i, d in enumerate(r):
            if d == '1':
                a[positions[i]] = '1'
                changed[0] = True
            else:
                b[positions[i]] = '0'
                changed[1] = True
        masks.append(''.join(a))
        masks.append(''.join(b))
    return list(map(lambda x: int(x, base=2), masks))

def part_one():
    addr = Address()
    with open("input", 'r') as f:
        for line in f:
            if "mask" in line:
                addr.mask = make_mask(line)
            else:
                addr.parse_instr(line)
    print(f"Part one completed. The sum is {addr.sum()}")

def part_two():
    addr = Address2()
    with open("input", 'r') as f:
        for line in f:
            if "mask" in line:
                addr.masks = make_mask_2(line)
            else:
                addr.parse_instr(line)
    print(f"Part two completed. The sum is {addr.sum()}")

if __name__ == "__main__":
    part_one()
    part_two()