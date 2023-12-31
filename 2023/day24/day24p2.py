import sympy

stones = [tuple(map(int, line.replace("@",",").split(","))) for line in open(0)]

equations = []
ux, uy, uz, uvx, uvy, uvz = sympy.symbols("ux, uy, uz, uvx, uvy, uvz")

for x, y, z, vx, vy, vz in stones:
    equations.append((ux - x) * (vy - uvy) - (vx - uvx) * (uy - y))
    equations.append((ux - x) * (vz - uvz) - (vx - uvx) * (uz - z))

ans = sympy.solve(equations)[0]

print(ans[ux] + ans[uy] + ans[uz])
