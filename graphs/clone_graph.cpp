// https://leetcode.com/problems/clone-graph/

#include <bits/stdc++.h>
using namespace std;


// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution {
public:
    Node* cloneGraph(Node* node) {
        // perform bfs and store the neighbor nodes, then add them to the 

        if (!node) return NULL;

        unordered_set<Node*> vis;
        unordered_map<Node*, Node*> ini;

        queue<pair<Node*, Node*>> q;
        Node* clone_root = new Node(node->val);

        q.push({node, clone_root});

        while(!q.empty())
        {
            auto temp_node = q.front();
            q.pop();

            Node* curr = temp_node.first;
            Node* clone = temp_node.second;

            int num_neighbors = curr->neighbors.size();

            vector<Node*>& real_neighbors = curr->neighbors;
            vector<Node*>& clone_neighbors = clone->neighbors;

            for(int i = 0; i < num_neighbors; i++)
            {
                Node* r_neighbor = real_neighbors[i];
                Node* c_neighbor;

                // check if neighbor already ini
                if(ini.find(r_neighbor) == ini.end())
                {
                    c_neighbor = new Node(r_neighbor->val);
                    ini[r_neighbor] = c_neighbor;
                }
                else c_neighbor = ini[r_neighbor];

                // check if we need to add the neighbor as a ref
                if(vis.find(r_neighbor) == vis.end())
                {
                    clone_neighbors.push_back(c_neighbor);
                    c_neighbor->neighbors.push_back(clone);
                    q.push({r_neighbor, c_neighbor}); 
                }
            }

            vis.insert(curr);
        }
        
        return clone_root;
    }
};