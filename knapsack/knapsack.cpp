#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
using namespace std;

vector<pair<int,int> > Item;
// No. of decision variables is n
// Capacity of Knapsack is K

// bool pairCompareRatio(pair<int,int> i, pair<int,int> j) { return (float(i.first)/i.second)>(float(j.first)/j.second);}

// Bellman Equations
// int O(int k, int j){
// 	if(j==0){
// 		return 0;
// 	}else if(Item[j].second<=k){
// 		return max(O(k,j-1),Item[j].first+O(k-Item[j].second,j-1));
// 	}else{
// 		return O(k,j-1);
// 	}
// }

int main(){
	unsigned int i, j, n, K, temp_v, temp_w;	// Number of items and Capacity are Non-negative
	// cout<<"Taking input values"<<endl;
	cin>>n>>K;
	for(i=0;i<n;i++){
		cin>>temp_v>>temp_w;
		Item.push_back(make_pair(temp_v,temp_w));
	}
	// cout<<"Items read: "<<Item.size()<<endl;
	// sort(Item.begin(), Item.end(), pairCompareRatio);
	// cout<<"Sorted order"<<endl;
	// for(i=0;i<n;i++){
	// 	cout<<Item[i].first<<" "<<Item[i].second<<endl;
	// }
	// cout<<"Optimal value "<<O(K,n-1)<<endl;

	// Initializing table
	vector<vector<int> > DPM;
	int val1, val2;
	// cout<<"Constructing DPM"<<endl;
	for(i=0;i<=n;i++){
		vector<int> col;
		for(j=0;j<=K;j++){
			val1 = i>0?DPM[i-1][j]:0;
			val2 = ((i>0)&&(j>=Item[i-1].second))?DPM[i-1][j-Item[i-1].second]+Item[i-1].first:0;
			// cout<<i<<","<<j<<"\t"<<val1<<","<<val2<<endl;
			col.push_back(max(val1,val2));
		}
		DPM.push_back(col);
	}

	// Traceback
	// cout<<"DPM Table:"<<endl;
	// for(i=0;i<=K;i++){
	// 	for(j=0;j<=n;j++){
	// 		cout<<DPM[j][i]<<" ";
	// 	}
	// 	cout<<endl;
	// }
	
	vector<int> X; // Decision variable
	unsigned int val=0;
	for(i=n,j=K;i>0;i--){
		if(j<=0||DPM[i][j]==DPM[i-1][j]){
			X.push_back(0);
			// cout<<"Not Selected"<<endl;
		}else{
			X.push_back(1);
			j -= Item[i-1].second;
			val += Item[i-1].first;
			// cout<<"Selected"<<endl;
		}
	}
	// cout<<"Done"<<endl;
	cout<<val<<" "<<1<<endl;
	for(int m=n-1;m>=0;m--){
		cout<<X[m]<<" ";
	}
	cout<<endl;
	return 1;
}