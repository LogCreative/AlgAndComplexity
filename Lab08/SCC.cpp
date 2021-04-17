#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
//Please put this source code in the same directory with SCC.in
//And do NOT change the file name.
/*
This function computes the number of Strongly Connected Components in a graph
Args:
    n: The number of nodes in the graph. The nodes are indexed as 0~n-1
    edge: The edges in the graph. For each element (a,b) in edge, it means
          there is a directed edge from a to b
          Notice that there may exists multiple edge and self-loop
Return:
    The number of strongly connected components in the graph.
*/

class Digraph {
public:
    Digraph(int _n) {
        n = _n;
        G = vector<vector<int>>(n);
    }
    void addEdge(pair<int, int> e) {
        G[e.first].push_back(e.second);
    }
    Digraph reverse() {
        Digraph GR(n);
        for (int i = 0; i < n; ++i)
            for (int end : G[i])
                GR.addEdge(make_pair(end, i));
        return GR;
    }
    vector<int> dfs() {
        visited = vector<bool>(n, false);
        visiting = vector<int>();
        for (int i = 0; i < n; ++i)
            if(!visited[i])
                dfs(i);
        return visiting;
    }
    int SCC(vector<int> order) {
        int count = 0;
        visited = vector<bool>(n, false);
        ofstream fscc;
        fscc.open("partition.txt");
        for (int node : order) {
            if (!visited[node]) {
                visiting = vector<int>();
                dfs(node);
                ++count;
                for (int v : visiting)
                    fscc << v << ' ';
                fscc << endl;
            }
        }
        fscc.close();
        return count;
    }
private:
    int n;
    vector<vector<int>> G;
    vector<bool> visited;
    vector<int> visiting;
    void dfs(int node) {
        visited[node] = true;
        for (int adj : G[node])
            if(!visited[adj])
                dfs(adj);
        visiting.push_back(node);
    }
};

int SCC(int n, vector<pair<int,int>>& edge) {
    Digraph G(n);
    for (auto e : edge)
        G.addEdge(e);
    Digraph GR = G.reverse();
    vector<int> visiting = GR.dfs();
    reverse(visiting.begin(), visiting.end());
    return G.SCC(visiting);
}
//Please do NOT modify anything in main(). Thanks!
int main()
{
    int m,n;
    vector<pair<int,int>> edge;
    ifstream fin;
    ofstream fout;
    fin.open("SCC.in");
    cout<<fin.is_open()<<endl;
    fin>>n>>m;
    cout<<n<<" "<<m<<endl;
    int tmp1,tmp2;
    for(int i=0;i<m;i++)
    {
        fin>>tmp1>>tmp2;
        edge.push_back(pair<int,int>(tmp1,tmp2));
    }
    fin.close();
    int ans=SCC(n,edge);
    fout.open("SCC.out");
    fout<<ans<<'\n';
    fout.close();
    return 0;
}
