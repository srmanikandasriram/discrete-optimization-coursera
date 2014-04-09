#include <iostream>
#include <vector>
#include <set>
using namespace std;

typedef struct Node{
	unsigned int index, clr;
	vector<unsigned int> neighbors;
	set<unsigned int> constraints;	// List of colors that it can't take
} node;

int main(){
	ios_base::sync_with_stdio(false);
	unsigned int N,E,u,v;
	cin>>N>>E;
	vector<node*> node_list;
	// Initialising nodes
	for(int i=0;i<N;i++){
		node* temp = new node;
		temp->index = i;
		temp->clr = -1;
		node_list.push_back(temp);
	}
	// Constructing the graph using Adjacency list
	for(int i=0;i<E;i++){
		cin>>u>>v;
		node_list[u]->neighbors.push_back(v);
		node_list[v]->neighbors.push_back(u);
		// cout<<node_list[u]->index<<","<<node_list[v]->index<<endl;
	}
	unsigned int max_clr = 1;	// Number of colors used so far
	// Apply colors to nodes
	for(int i=0;i<N;i++){
		node* temp = node_list[i];
		// cout<<"Current node is:\t"<<node_list[i]->index<<endl;
		bool clr_assigned = false;
		unsigned int clr;
		for(clr=0;clr<max_clr;clr++){
			// cout<<"\t Color:\t"<<clr;
			if(temp->constraints.find(clr)==temp->constraints.end()){
				// Valid color found
				// cout<<"\tValid!"<<endl;
				clr_assigned = true;
				break;
			}else{
				// cout<<"\tinvalid\n";
			}
		}
		if(!clr_assigned){
			max_clr = clr+1;
		}
		temp->clr = clr;
		// cout<<"Adding constraints to:\t";
		for(int j=0;j<temp->neighbors.size();j++){
			node_list[temp->neighbors[j]]->constraints.insert(clr);
			// cout<<temp->neighbors[j]<<" ";
		}
		// cout<<endl;
	}

	// Print output
	cout<<max_clr<<" 1\n";
	for(int i=0;i<N;i++){
		cout<<node_list[i]->clr<<" ";
	}
	cout<<endl;

	return 0;
}