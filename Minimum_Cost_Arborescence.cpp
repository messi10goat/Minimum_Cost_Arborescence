'''
Harsh Mittal
2018eeb1150@iitrpr.ac.in
https://github.com/messi10goat
'''

#include<bits/stdc++.h>
#include<stdio.h>
using namespace std;

//---------------------------
int minimum(int a, int b)
{
	if(a>b)
		return b;
	else
		return a;
}
//---------------------------
int iselementofstack(int num, int stack[], int top)
{
	for(int i=0;i<top;i++)
	{
		if(stack[i]==num)
			return 1;
	}
	return 0;
}

//--------------------------
int iselementofsupernode(int num, int stack[], int top)
{
	for(int i=0;i<top;i++)
	{
		if(stack[i]==num)
			return 1;
	}
	return 0;
}

//--------------------------
int newa(int arr[], int n)
{
	for(int i=0;i<n;i++)
	{
		if(arr[i]==0)
			return i;
	}
	return -1;
}

//---------------------------
int rev(int num, int arr[], int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		if(arr[i]==num)
			return i;
	}
	return -1;
}

//---------------------------
int supernodeindexs(int stack[], int n)
{
	int min = stack[0];
	for(int i=0;i<n;i++)
	{
		if(min>stack[i])
			min=stack[i];
	}
	return min;
}

//---------------------------

void mincostarboro(vector<int> adj_list[], int n)
{
	//cout <<"reached here\n";
	int i,j,k;
	vector<int> copy1[n];
	vector<int> copy2[n];

	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			copy1[i].push_back(-1);
			copy2[i].push_back(-1);
		}
	}

	int min[n];
	for(i=0;i<n;i++)
	{
		min[i]=-1;
	}


	// storing minimum inedge for each vertex
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(min[i]==-1)
			{
				min[i]=adj_list[j][i];
			}
			else if(adj_list[j][i]!=-1)
			{
				min[i]=minimum(min[i],adj_list[j][i]);
			}
		}
	}
	//--

	// storing graph in copy1 with subtracted in min values
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(adj_list[i][j]==-1)
				copy1[i][j]=-1;
			else
			{
				copy1[i][j]= adj_list[i][j]-min[j];
			}
		}
	}
	
	//--

	// transfering atmost 1 zero weight inedge from copy1 to copy 2
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(copy1[j][i]==0)
			{
				copy2[j][i]=0;
				break;
			}
		}
	}
	//--

	// Finding cycle in copy2 if any and storing it in stack
	int checked[n];
	for(i=0;i<n;i++)
		checked[i]=0;
	int stack[n];
	int top=0;

	int t=n;
	int a=0;
	int cycle=0;
	while(1)
	{
		if(a==-1)
			break;
		checked[a]=1;
		for(i=0;i<n;i++)
		{
			if(copy2[i][a]==0)
			{
				break;
			}
		}
		if(i==n)
		{
			a = newa(checked,n);
			top=0;
			continue;
		}
		else if(iselementofstack(i,stack,top)==0)   
		{
			stack[top]=a;
			top++;
			a = i;
			continue;
		}
		else
		{
			stack[top]=a;
			top++;
			cycle=1;
			break;
		}

	}
	//--


	if(cycle==0)   //no cycle
	{
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{

				if(copy2[i][j]!=0)
				{
					adj_list[i][j]=-1;
				}

			}
		}
		return;
	}

	// cycle is present of 'top' number of vertices stored in 'stack[]'  array
	int m = n+1-top;
	int exp[m], com[n];
	int count=0;

	int supernodeindex = supernodeindexs(stack, top);

	for(i=0;i<n;i++)
	{
		if(count==supernodeindex)
			count++;
		if(iselementofsupernode(i,stack,top))
		{
			com[i]=supernodeindex;
		}
		else
		{
			com[i]= count;
			count++;
		}
	}

	
	// Making future refernece for compress and expand
	for(i=0;i<m;i++)
	{
		if(i!=supernodeindex)
		{
			exp[i] = rev(i,com,n);
			continue;
		}
		else
		{
			exp[i] = rev(i,com,n);
			continue;
		}
	}

	//--
	vector<int> temporary[m];

	for(i=0;i<m;i++)
	{
		for(j=0;j<m;j++)
		{
			temporary[i].push_back(-1);
		}
	}

	// Made a m*m graph with supernode
	int fa1, fa2;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			fa1 = com[i];
			fa2 = com[j];
			if(fa1==fa2)
				continue;

			
			else if(copy1[j][i]!=-1)
			{
				if(temporary[fa2][fa1]==-1)
					temporary[fa2][fa1]= copy1[j][i];
				else
					temporary[fa2][fa1]= minimum(temporary[fa2][fa1], copy1[j][i]);
			}
		}
	}
	
	//--

	mincostarboro(temporary,m);
	

	vector<int> final[n];
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			final[i].push_back(-1);
		}
	}
	int b,c1,c2,temp;
	for(i=0;i<m;i++)
	{
		for(j=0;j<m;j++)
		{
			if(temporary[i][j]==-1)
				continue;
			a=exp[i]; b=exp[j];
			c1 = iselementofsupernode(a,stack,top);
			c2 = iselementofsupernode(b,stack,top);
			
			
			if(c1 || c2)
			{
				if(c2)   //inedge to the supernode
				{
					temp=a;
					int weight = temporary[i][j];
					for(k=0;k<top;k++)
					{
						if(copy1[temp][stack[k]]==weight)
						{
							final[temp][stack[k]]=adj_list[temp][stack[k]];
							break;
						}
					}

				} 

				else   //outedge form supernode
				{
					temp=b;
					int weight = temporary[i][j];
					for(k=0;k<top;k++)
					{
						if(copy1[stack[k]][temp]==weight)
						{
							final[stack[k]][temp]=adj_list[stack[k]][temp];
							k=top;
						}
					}
				}

			}
			else
			{
				final[a][b]=adj_list[a][b];
				continue;
			}

		}
	}

	//cout<<"check";
	/*for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			cout<<final[i][j]<<"  ";

		cout<<"\n";
	}*/
	vector<int> tab1[n];
	vector<int> tab2[n];
	vector<int> tab3[n];
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			tab1[i].push_back(-1);
			tab2[i].push_back(-1);
			tab3[i].push_back(-1);
		}
	}

	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			tab1[i][j]=final[j][i];
			tab2[i][j]=adj_list[j][i];
			tab3[i][j]=copy2[j][i];
			//printf("%d  ",adj_list[i][j]);
		}
		//printf("\n");
	}

	int okay=0;
	//printf("df = %d\n",adj_list[1][2]);

	for(i=0;i<n;i++)
	{
		okay=0;
		for(int ak=0;ak<i;ak++)
		{
			okay=0;
		}
		for(j=0;j<n && iselementofsupernode(i,stack,top);j++)
		{
			if(tab1[i][j]!=-1)
				okay=1;
		}
		if(okay)
			continue;
		if(iselementofsupernode(i,stack,top))
		{
			for(j=0;j<n;j++)
			{
				 if(tab3[i][j]==0)
				 	tab1[i][j]= tab2[i][j];
			}
		}
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			tab2[i][j]=tab1[i][j];
		}
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			adj_list[i][j]=tab2[j][i];
		}
	}
	/*

printf("n = %d\n",n);
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			cout<<adj_list[i][j]<<"  ";
		}
		printf("\n");
	}
*/



}


//---------------------------


int main()
{
	int t,i,j,k;
	cin >> t;
	while(t)
	{
	    //cout << "output" << t<< "\n";
		t--;
		int n,m,s;
		cin >>n >>s >>m;
		s--;
		vector<int> adj_list[n];
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				adj_list[i].push_back(-1);
			}
		}

		int u,v,w;
		for(i=0;i<m;i++)                         //filling edges
		{
			cin >>u >>v >>w;
			u--;
			v--;
			if(u==v || v==s)
				continue;
			else if(adj_list[u][v]==-1)
				adj_list[u][v]=w;
			else
			{
				if(adj_list[u][v]>w)
					adj_list[u][v]=w;
			}
		}
		 //-
		
		int sum=0;

		int visited[n];              // BFS for getting unreachable nodes

		for(i=0;i<n;i++)
			visited[i]=0;

		int queue[n];
		queue[0]=s;
		int start=0, end=0, p;
		while(start<=end)
		{
			p=queue[start];
			start++;
			visited[p]=1;
			for(j=0;j<n;j++)
			{
				if(adj_list[p][j]!=-1 && visited[j]==0)
				{
					end++;
					queue[end]=j;
					visited[j]++;
				}
			}
		}

		//if(visited[i]==0) then it is impossible to reach vertex i
		for(i=0;i<n;i++)
		{
			if(visited[i]==0)
			{
				for(j=0;j<n;j++)
				{
					adj_list[i][j]=-1;
					adj_list[j][i]=-1;
				}
			}
		}

		vector<int> lastie[n];
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				lastie[i].push_back(-1);
			}
		}
		//now adj_list is final graph with everything reachable

		mincostarboro(adj_list, n);

		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				lastie[i][j] = adj_list[i][j];
				if(adj_list[i][j]!=-1)
				{
					sum=sum+adj_list[i][j];
				}
			}
		}
		cout <<sum<<" ";


		int dist[n];
		int parent[n];
		int visited2[n];
		for(i=0;i<n;i++)
			dist[i]=0;
		for(i=0;i<n;i++)
		{
			visited2[i]=0;
			parent[i]=-1;
			if(visited[i]==0)
				dist[i]=-1;
		}

		dist[s]=0;
		//int queue[n];
		parent[s]=0;
		queue[0]=s;
		start=0; end=0;
		while(start<=end)
		{
			p=queue[start];
			start++;
			visited2[p]=1;
			for(j=0;j<n;j++)
			{
				if(adj_list[p][j]!=-1 && visited2[j]==0)
				{
					parent[j]=p;
					end++;
					queue[end]=j;
					visited2[j]++;
					dist[j]=dist[p]+adj_list[p][j];
				}
			}
		}
		for(i=0;i<n;i++)
			printf("%d ",dist[i]);

		printf("# ");
		for(i=0;i<n;i++)
		{
			if(i==s)
				printf("0 ");
			else if(parent[i]==-1)
				printf("-1 ");
			else
				printf("%d ",parent[i]+1);
		}
		printf("\n");

	}
}