def knapsack(W, wt, val, n):
    if n == 0 or W == 0:
        return 0, []

    if wt[n - 1] > W:
        return knapsack(W, wt, val, n - 1)

    # get the included vertices
    include_val, include_indices = knapsack(W - wt[n - 1], wt, val, n - 1)
    include_val += val[n - 1]

    # building the list of vertices used
    include_indices = include_indices + [n]

    # get the excluded vertices
    exclude_val, exclude_indices = knapsack(W, wt, val, n - 1)

    # getting the max value
    if include_val > exclude_val:
        return include_val, include_indices
    else:
        return exclude_val, exclude_indices


if __name__ == "__main__":
    W = int(input())
    N = int(input())

    wt = []
    val = []

    for i in range(N):
        x, y, z = input().split()
        wt.append(int(y))
        val.append(int(z))

    max_val, selected_indices = knapsack(W, wt, val, N)

    print(max_val)
    selected_indices.reverse()
    for i in selected_indices:
        print(i)


# Reference: https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/