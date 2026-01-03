import re, z3

ans = 0

for line in open(0):
    comps = line.strip().split(' ')
    buttons = [set(map(int, x[1:-1].split(','))) for x in comps[1:-1]]
    joltages = list(map(int, comps[-1][1:-1].split(',')))

    o = z3.Optimize()
    vars = z3.Ints(f"n{i}" for i in range(len(buttons)))
    for var in vars:
        o.add(var >= 0)

    for i, joltage in enumerate(joltages):
        equation = 0
        for b, button in enumerate(buttons):
            if i in button:
                equation += vars[b]
        o.add(equation == joltage)

    o.minimize(sum(vars))
    o.check()
    ans += o.model().eval(sum(vars)).as_long()

print(ans)
