#include <bits/stdc++.h>
using namespace std;

class LCABinaryLifting {
public:
    int n;                   // Number of nodes
    int LOG;                 // Maximum power such that 2^LOG >= n
    vector<vector<int>> parent; // parent[node][j] is the 2^j-th ancestor of node
    vector<int> depth;       // Depth of each node from the root
    vector<vector<int>> adj; // Adjacency list

    // Constructor: initializes the tree with n nodes.
    LCABinaryLifting(int n) : n(n) {
        // Compute LOG such that (1 << LOG) >= n
        LOG = 0;
        while ((1 << LOG) <= n) ++LOG;
        parent.assign(n, vector<int>(LOG, -1));
        depth.assign(n, 0);
        adj.assign(n, vector<int>());
    }

    // Add an undirected edge between nodes u and v.
    void addEdge(int u, int v) {
        if (u < 0 || u >= n || v < 0 || v >= n) {
            cerr << "Error: Node index out of range.\n";
            return;
        }
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // DFS to initialize depths and immediate parents.
    void dfs(int node, int par) {
        parent[node][0] = par;
        for (int neighbor : adj[node]) {
            if (neighbor == par)
                continue;
            depth[neighbor] = depth[node] + 1;
            dfs(neighbor, node);
        }
    }

    // Preprocesses the tree for LCA queries.
    // Use the provided root (default is 0) to start the DFS.
    // (Note: if the tree is disconnected, you may need to call DFS on each component.)
    // T.C: O(n log n) for preprocessing.
    void preprocess(int root = 0) {
        if (n == 0) return;  // Handle empty tree edge-case.
        dfs(root, -1);
        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i < n; i++) {
                if (parent[i][j - 1] != -1)
                    parent[i][j] = parent[parent[i][j - 1]][j - 1];
                else
                    parent[i][j] = -1;
            }
        }
    }

    // Returns the lowest common ancestor of nodes u and v.
    // Returns -1 if either u or v is invalid.
    // T.C: O(LOG n) for each query.
    int getLCA(int u, int v) {
        if (u < 0 || u >= n || v < 0 || v >= n) {
            cerr << "Error: Query node index out of range.\n";
            return -1;
        }

        // If necessary, swap u and v so that u is always the deeper node.
        if (depth[u] < depth[v])
            swap(u, v);

        // Lift u to the same depth as v.
        for (int j = LOG - 1; j >= 0; j--) {
            if (u == -1) break;
            if (depth[u] - (1 << j) >= depth[v])
                u = parent[u][j];
        }

        // Now, if both nodes are equal, we've found the LCA.
        if (u == v)
            return u;

        // Lift both u and v until their parents are the same.
        for (int j = LOG - 1; j >= 0; j--) {
            if (parent[u][j] != parent[v][j]) {
                u = parent[u][j];
                v = parent[v][j];
            }
        }

        return parent[u][0];  // Their immediate parent is the LCA.
    }
};

int main() {
    // Example: Build a tree with 7 nodes (0 through 6)
    // Tree structure:
    //         0
    //        / \
    //       1   2
    //      / \  / \
    //     3  4 5   6
    int n = 7;
    LCABinaryLifting lcaSolver(n);

    // Add edges for the tree.
    lcaSolver.addEdge(0, 1);
    lcaSolver.addEdge(0, 2);
    lcaSolver.addEdge(1, 3);
    lcaSolver.addEdge(1, 4);
    lcaSolver.addEdge(2, 5);
    lcaSolver.addEdge(2, 6);

    // Preprocess all nodes with 0 as the root.
    lcaSolver.preprocess(0);

    // Some sample queries:
    vector<pair<int, int>> queries = {
        {3, 4}, // Expected LCA: 1  
        {3, 5}, // Expected LCA: 0  
        {4, 6}, // Expected LCA: 0  
        {5, 6}, // Expected LCA: 2  
        {3, 3}  // Corner case: same node; Expected LCA: 3  
    };

    for (auto &q : queries) {
        int u = q.first, v = q.second;
        int lca = lcaSolver.getLCA(u, v);
        if (lca != -1)
            cout << "LCA of " << u << " and " << v << " is: " << lca << "\n";
    }

    return 0;
}
