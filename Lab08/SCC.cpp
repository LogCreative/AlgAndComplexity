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
int SCC(int n, vector<pair<int,int>>& edge) {
    return edge.size();
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
