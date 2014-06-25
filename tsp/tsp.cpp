#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

typedef struct Node{
	unsigned int index, clr, degree;
	vector<unsigned int> neighbors;
	set<unsigned int> constraints;	// List of colors that it can't take
	vector<unsigned int> clr_options;
} node;

int main(){
	ios_base::sync_with_stdio(false);
	unsigned int N,u,v;
	cin>>N>>E;
	vector<node*> node_list;
	vector<pair<int,int> > node_order;	// <degree,node>
	// Initialising nodes
	for(int i=0;i<N;i++){
		node* temp = new node;
		temp->index = i;
		temp->clr = -1;
		temp->degree = 0;
		node_list.push_back(temp);
	}
	// Constructing the graph using Adjacency list
	for(int i=0;i<E;i++){
		cin>>u>>v;
		node_list[u]->neighbors.push_back(v);
		node_list[u]->degree++;
		node_list[v]->neighbors.push_back(u);
		node_list[v]->degree++;
		// cout<<node_list[u]->index<<","<<node_list[v]->index<<endl;
	}
	// Set order of degree
	for(int i=0;i<N;i++){
		node_order.push_back(make_pair(-node_list[i]->degree,i));
	}
	sort(node_order.begin(), node_order.end());
	cout<<"Sorted order:";
	for(int i=0;i<N;i++){
		cout<<" "<<node_order[i].second;
	}
	cout<<endl;
	unsigned int max_clr = 1;	// Number of colors used so far
	// Apply colors to nodes
	for(int i=0;i<N;i++){
		node* temp = node_list[node_order[i].second];
		cout<<"Current node is:\t"<<temp->index<<" with degree:\t"<<temp->degree<<endl;
		unsigned int clr;
		for(clr=0;clr<max_clr;clr++){
			cout<<"\t Color:\t"<<clr;
			if(temp->constraints.find(clr)==temp->constraints.end()){
				// Valid color found
				cout<<"\tValid!"<<endl;
				temp->clr_options.push_back(clr);
			}else{
				cout<<"\tinvalid\n";
			}
		}
		if(temp->clr_options.empty()){
			max_clr = clr+1;
			temp->clr_options.push_back(clr);
			cout<<"New color being used\n"<<"\t Color:\t"<<clr<<"\tValid!"<<endl;
		}
		
		temp->clr = temp->clr_options[0];			// Making a arbitrary choice here without backtracking! Hence it may not be optimal!
		
		for(int j=0;j<temp->neighbors.size();j++){
			node_list[temp->neighbors[j]]->constraints.insert(temp->clr);
			cout<<"constraints updated for: "<<temp->neighbors[j]<<"\t";
			set<unsigned int>::iterator it;
			node* neighbor = node_list[temp->neighbors[0]];
			for(it=neighbor->constraints.begin();it!=neighbor->constraints.end();++it)
				cout<<' '<<*it;
			cout<<endl;
		}
		cout<<endl;
	}

	// Print output
	cout<<max_clr<<" 0\n";
	for(int i=0;i<N;i++){
		cout<<node_list[i]->clr<<" ";
	}
	cout<<endl<<endl;

	// Print alternatives to the solution
	for(int i=0;i<N;i++){
		node* temp = node_list[i];
		cout<<i<<":"<<temp->clr<<"\t";
		for(int j=0;j<temp->clr_options.size();j++){
			cout<<temp->clr_options[j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}