import sys

# detect incorrect usage
if len(sys.argv) < 2 or len(sys.argv) > 3:
    print("Usage: python genranges.py <UnicodeData file> [Blocks file]")
    exit(0)

# load unicode data
unicodedata = []
with open(sys.argv[1]) as udatafile:
    lines = udatafile.readlines()
    unicodedata = [line.split(';') for line in lines]

# load block ranges from file (just for helpful comments in resulting code)
blocks = []
if len(sys.argv) == 3:
    with open(sys.argv[2]) as blockfile:
        lines = blockfile.readlines()
        blockdata = [line.split(';') for line in lines]
        blocks = [line[0].split('..') + [line[1].lstrip().rstrip()] for line in blockdata if len(line) == 2 and line[0][0] in '0123456789abcdef']

for block in blocks:
    block[0] = int(block[0], 16)
    block[1] = int(block[1], 16)

# binary search of block ranges
def findblock(code):
    left, right = 0, len(blocks) - 1
    while True:
        mid = (left + right) // 2
        if right == mid or left == mid:
            break
        if code >= blocks[left][0] and code <= blocks[left][1]:
            return blocks[left][2]
        elif code >= blocks[right][0] and code <= blocks[right][1]:
            return blocks[right][2]
        if code >= blocks[mid][0] and code <= blocks[mid][1]:
            return blocks[mid][2]
        elif code < blocks[mid][0]:
            right = mid
        else:
            left = mid
    return ""

# all unicode categories
categories = [
    'Cc', 'Cf', 'Cn', 'Co', 'Cs',
    'LC', 'Ll', 'Lm', 'Lo', 'Lt', 'Lu',
    'Mc', 'Me', 'Mn', 
    'Nd', 'Nl', 'No',
    'Pc', 'Pd', 'Pe', 'Pf', 'Pi', 'Po', 'Ps',
    'Sc', 'Sk', 'Sm', 'So', 
    'Zl', 'Zp', 'Zs',
    'C', 'L', 'M', 'N', 'P', 'S', 'Z' # overarching categories
]

# compute ranges
rangeset = { cat: [] for cat in categories }
prev_block = ""

def add_code(cat, code):
    global prev_block
    if rangeset[cat] and rangeset[cat][-1][1] + 1 == code:
        rangeset[cat][-1][1] += 1
    else:
        block = findblock(code) if blocks else ""
        if block == prev_block:
            block = ""
        else:
            prev_block = block
        rangeset[cat].append([code, code, block])

for line in unicodedata:
    code = int(line[0], 16)
    cat = line[2]
    add_code(cat, code)
    add_code(cat[0:1], code)

# compress sequences of odd or even codes
compressed_set = { cat: [] for cat in categories }
for cat, ranges in rangeset.items():
    for r in ranges:
        compressed = compressed_set[cat]
        if r[1] != r[0] or not compressed:
            compressed.append(r)
        else:
            last = compressed[-1]
            if len(last) == 3 and last[1] != last[0]: # no compression, or previous element is a range
                compressed.append(r)
                continue 
            status = 'even' if r[0] % 2 == 0 else 'odd'
            prev_status = 'even' if last[0] % 2 == 0 else 'odd'
            if len(last) == 4:
                prev_status = last[3]
            if status != prev_status or r[0] - last[1] != 2: # incompatible
                compressed.append(r) 
            else:
                last[1] = r[0]
                if len(last) == 3:
                    last.append(status)

# code generation
for cat, ranges in compressed_set.items():
    print("{ // ", cat)
    for r in ranges:
        line = "\t"
        left = hex(r[0])
        right = hex(r[1])
        if len(r) == 4:
            bit = " | EVEN_BIT" if r[3] == 'even' else " | ODD_BIT"
            left += bit
            right += bit
        line += "{{ {}, {} }},".format(left, right)
        if r[2]:
            line += " // {}".format(r[2])
        print(line)
    print("};")