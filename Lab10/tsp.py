import math
import networkx as nx

def compute_distance(coord1, coord2):
    x1, y1 = coord1
    x2, y2 = coord2
    distance = math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2) * 1000
    return distance

def tsp_greedy(activities):
    G = nx.Graph()

    for i in activities:
        G.add_node(i)

    for i in range(len(activities)):
        for j in range(i + 1, len(activities)):
            activity1 = activities[i]
            activity2 = activities[j]
            distance = compute_distance(activity1[1:], activity2[1:])
            G.add_edge(activity1[0], activity2[0], weight=distance)

    mst = nx.minimum_spanning_tree(G)
    tour = list(nx.dfs_preorder_nodes(mst, source="Rest"))

    tour.append("Rest")
    return tour

def parse_input():
    N = int(input())
    activities = []

    for _ in range(N):
        activity, venue, latitude, longitude = input().split()
        activities.append((activity, float(latitude), float(longitude)))

    return activities

def main():
    activities = parse_input()

    tour = tsp_greedy(activities)

    total_distance = 0.0

    for i in range(len(tour) - 1):
        activity1 = next(a for a in activities if a[0] == tour[i])
        activity2 = next(a for a in activities if a[0] == tour[i + 1])
        distance = compute_distance(activity1[1:], activity2[1:])
        total_distance += distance

    print(round(total_distance, 3))

    for activity in tour:
        print(activity)

if __name__ == '__main__':
    main()

"""
Sources: 
https://networkx.org/documentation/stable/_modules/networkx/algorithms/approximation/traveling_salesman.html#greedy_tsp
https://networkx.org/documentation/stable/reference/algorithms/generated/networkx.algorithms.approximation.traveling_salesman.greedy_tsp.html#networkx.algorithms.approximation.traveling_salesman.greedy_tsp
"""