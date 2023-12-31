import networkx as nx

g = nx.Graph()

for line in open(0):
    l, r = line.split(": ")
    for node in r.strip().split():
        g.add_edge(l, node)
        g.add_edge(node, l)

g.remove_edges_from(nx.minimum_edge_cut(g))
x, y = nx.connected_components(g)
print(len(x) * len(y))
