def find_gold(bag, bags):
    if bag in bags and bags[bag]:
        count = 0
        for b in bags[bag]:
            if b == "shinygoldbag":
                return 1
            else:
                count += find_gold(b, bags)
        return count
    else:
        return 0

def part_one():
    bags = {}
    with open("input", 'r') as f:
        for line in f:
            line = line.strip(".\n")
            bag = "".join(line.split(" ")[:3])
            if bag[-4:] == "bags":
                bag = bag[:-1]
            contains = "".join(line.split(" ")[3: ])
            if not contains == "containnootherbags":
                contains = contains.split(",")
                c = {contains[0][8:]}
                if len(contains) > 1:
                    c |= {x[1:] for x in contains[1:]}
                c = {x[:-1] if x[-4:] == "bags" else x for x in c}
                bags[bag] = c
    count = 0
    for bag in bags.keys():
        if find_gold(bag, bags):
            count += 1
    print(f"Part one completed. {count} bags can contain shiny gold bags.")

def count_bags(bag, bags_count):
    if not bag in bags_count:
        return 1
    else:
        count = 1
        for b in bags_count[bag]:
            count += int(b[0]) * count_bags(b[1:], bags_count)
        return count

def part_two():
    bag_count = {}
    
    with open("input", 'r') as f:
        for line in f:
            line = line.strip(".\n")
            bag = "".join(line.split(" ")[:3])
            if bag[-4:] == "bags":
                bag = bag[:-1]
            contains = "".join(line.split(" ")[3: ])
            if not contains == "containnootherbags":
                contains = contains.split(",")
                c = {contains[0][7:]}
                if len(contains) > 1:
                    c |= {x for x in contains[1:]}
                c = {x[:-1] if x[-4:] == "bags" else x for x in c}
                bag_count[bag] = c

    count = count_bags("shinygoldbag", bag_count)
    print(f"Part two completed. A shiny gold bag contains {count - 1} bags.")

if __name__ == "__main__":
    part_one()
    part_two()