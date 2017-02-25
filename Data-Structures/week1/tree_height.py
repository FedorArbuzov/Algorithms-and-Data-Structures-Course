# python3

import sys
import threading

sys.setrecursionlimit(10 ** 7)  # max depth of recursion
threading.stack_size(2 ** 25)  # new thread will get stack of such size


class TreeHeight:

    def __init__(self):
        self.n = 0
        self.parent = []
        self.cache = []

    def read(self):
        """Reads data from standard input."""
        self.n = int(sys.stdin.readline())
        self.parent = list(map(int, sys.stdin.readline().split()))
        self.cache = [0] * self.n

    def path_len(self, node_id):
        """Returns path length from given node to the root."""
        parent = self.parent[node_id]
        if parent == -1:
            return 1

        if self.cache[node_id]:
            return self.cache[node_id]

        self.cache[node_id] = 1 + self.path_len(self.parent[node_id])
        return self.cache[node_id]

    def compute_height(self):
        """Computes the tree height."""
        return max([self.path_len(i) for i in range(self.n)])


def main():
    tree = TreeHeight()
    tree.read()
    print(tree.compute_height())


threading.Thread(target=main).start()
