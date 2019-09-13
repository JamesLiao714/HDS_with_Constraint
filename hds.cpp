#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<cmath>
using namespace std;

vector<vector<int> >disk(10010);

vector<int>A; //access.in

vector<int>R;//for ele
vector<int>R2; //for sp
vector<int>R3;// for ins

ofstream outFiles("access.out", ios::out);
int flag[20000];
int flag2[20000];


int cnt = 1;
int cons; //QOS constraint
int N;
vector<int> extreme(20000, 0);

void print(vector<int>v) //output function
{
	for(int i =0 ;i < N; ++i)
	{
		outFiles << cnt << ":" << v[i] <<endl;
		cnt++;
	}
}


int check_legal_ins(int j, int i)//after inserting j, check that nums after j dont exceed imit; 
{
	if(i < cons)
		return 1;
	int beg;
	if(j > cons)
		beg = j;
	else
		beg = cons;
	for(int x = beg; x < i; ++x)
	{
		if(extreme[R3[x] - 1]  < x + 1) // new ind will be x + 1(R) r start with 0 , so extreme - 1;
			return 0;
	}
	return 1;
}

int cal(vector<int>v)
{
	int dist = 0;
	int prev = 0;
	for(int i = 0; i <N; ++i)
	{
		dist += abs(A[v[i] - 1] - prev);
		prev = A[v[i] - 1];
	} 
	return dist;
}

int ins()
{
	int dist, prev;
	for(int i = 0; i < N ; ++i) // order the num of A[]
	{
		int ins_ind, ins_dist;
		int c = 0;  
		if(i == 0)
		{
			R3.push_back(1);// first num to be put in vector R
		}
		else
		{
			int beg;
			if(i - cons < 0)
				beg = 0; // ex: the frontier for i = 1(constraint = 2) to insert is 0  
			else
				beg = i - cons; // ex: the frontier for i = 5(constraint = 2) to insert is 5 - 2= 3 
			//run R.size()=i - 1
			
			ins_dist = abs(A[i] - A[R3.back() - 1]);
			for(int j = beg; j <i; ++j)//insertion check 1.shortest place 2.dont make others off limit
			{
				 //cout << "j: " << j <<endl;
				if(check_legal_ins(j, i))
				{ 	
					int front ;
					if(j < 1)
						front = 0;
					else
						front = A[R3[j - 1] - 1] ;
					
					int back = A[R3[j] - 1]; 
					//cout << front <<" f b " << back <<endl;
					int ins = abs(back - A[i]) + abs(A[i] - front) - abs(back - front);
					//cout <<R3[j] << "j  " << ins_dist <<endl;
					if(ins < ins_dist)
					{
						c = 1;
						ins_dist = ins;
						ins_ind = j;		
					}
				}
			}
			if(c == 1)
			{
				R3.insert(R3.begin() + ins_ind, i + 1); // insert i + 1(A[i]) to R in right place	
			}
			else
			{
				R3.push_back(i+1);
			}
		}
	}
	
	dist = cal(R3);
	return dist;
} 




int elevator(int small, int large) // use elevator to find shortest route with constraint
{
	int dist = 0, prev = 0, p =0; 
	int mid = (small + large) / 2;
	//find first 
	for(int i = small; i <= large; ++i)
	{
		if(disk[i].size()!=0 && disk[i].front() <= 1 + cons)
		{
			R.push_back(disk[i][0]);
			//cout << disk[i][0] <<endl;
			dist = i; 
			flag[disk[i].front()] = 0;
			disk[i].erase(disk[i].begin());// pop front			
			prev = i;
			p = i;
			break;
		}
	}
	//N-

	int j = 2;
	while(1)
	{
		if(j > N)
			break;
		
		for(int i = prev; i >= small; --i)
		{
			while(disk[i].size()!=0)
			{
				if(cons >= abs(disk[i].front() - j))
				{
					//cout <<flag[j - cons] <<endl;
					if(j - cons > 0)
					{
						if(flag[j - cons] == -1)
						{
				
							if(disk[i].front() != j - cons)
								break;
						}

					}
				
					dist+=abs(i - p); //distance
					//cout << abs(i - p)<<endl;
					R.push_back(disk[i][0]);
					//cout << disk[i][0] <<endl;
					flag[disk[i].front()] = 0;
					disk[i].erase(disk[i].begin());// pop front	
					j++;		
					p = i;
				}
				else
				{
					break;
				}
			}
			
		}	


		for(int i = small; i <= large; ++i)
		{
	
			while(disk[i].size()!=0)
			{
				if(cons >= abs(disk[i].front() - j))
				{
					if(j - cons > 0)
					{
						if(flag[j - cons] == -1)
						{
				
							if(disk[i].front() != j - cons)
								break;

						}

					}
					dist+=abs(i - p); //distance
					//cout << abs(i - p)<<endl;
					R.push_back(disk[i][0]);
					//cout << disk[i][0] <<endl;
					flag[disk[i].front()] = 0;
					disk[i].erase(disk[i].begin());// pop front	
					j++;		
					p = i;
				}
				else
				{
					break;
				}
			}
		}	
		prev = large;
	}

	return dist;
}

int sp()
{
	int prev = 0;
	int t_dist = 0;
	for(int i = 0; i < N; ++i)
	{
		int s_ind = 10000000;//shortest indext
		int s_dist = 10000000;
		int dist;
		if(i < cons) // i = 0 1 that is  1 2 
		{
			for(int j = 0; j <= i + cons; ++j)//find shortest 
			{
				if(j >= N)
					break;
				if(flag2[j] == 0)
				{
					
					dist = abs(A[j] - prev);
					//cout << "dist"<<dist <<endl;
					if(dist < s_dist)
					{
						s_ind = j;
						s_dist = dist;
					}
				}
			}
			t_dist += s_dist;
			prev = A[s_ind];
			flag2[s_ind] = 1;
			R2.push_back(s_ind + 1);
		}
		else
		{
			if(flag2[i - cons] == 0)
			{
				t_dist +=  abs(A[i - cons] - prev);
				prev = A[i - cons];
				flag2[i - cons] = 1;
				R2.push_back(i - cons +1);
			}
			else
			{
				for(int j = i - cons; j <= i + cons; ++j)
				{
					if(j >= N)
						break;
					if(flag2[j] == 0)
					{

						dist = abs(A[j] - prev);
						//cout << "dist"<<dist <<endl;
						if(dist < s_dist)
						{
							s_ind = j;
							s_dist = dist;
						}
					}
				}
				t_dist += s_dist;
				prev = A[s_ind];
				flag2[s_ind] = 1;
				R2.push_back(s_ind + 1);	
			}
		}
	}
	return t_dist;
}
 

int main(int argc, char** argv)
{
	ifstream inFile(argv[1], ios::in); //input file
	cons = stoi(argv[2]); //QOS constraint
	int small = 1000000;
	int big = 0;// small and largest disk num
	string line;
	
	for(int i = 0; i < 20000; ++i)
	{
		extreme[i] = i + cons;
		flag[i] = -1;
		flag2[i] = 0;
	}
	while(getline(inFile, line,'\n'))
	{
		int ind, num;
		sscanf(line.c_str(), "%d:%d\n", &ind, &num);
		A.push_back(num);
		if(small > num)
			small = num;
		if(big < num)
			big = num;
		disk[num].push_back(ind); //no increment needed
	}
	inFile.close();//close file
	N = A.size();//N 


	int dist_i , dist_e, dist_s ;//distance from different algorithm
	//cout << " hi" <<endl;
	dist_e = elevator(small, big);
	//cout << "ele: "<<dist_e <<endl;
	//cout << cal(R) <<endl;
	dist_s = sp();
	//cout << "sp: "<<dist_s <<endl;
	//cout << cal(R2) <<endl;
	dist_i= ins();
	//cout << "ins: "<<dist_i <<endl;
	//cout << cal(R3) <<endl;
	
	if(dist_e < dist_s && dist_e < dist_i)
	{
		cout <<"(elevator)The total seek distance is " <<dist_e <<endl;
		print(R);//out put result to output filr
	}
	else if(dist_s < dist_i)
	{
		cout <<"(shortest path)The total seek distance is " <<dist_s <<endl;
		print(R2);//out put result to output filr
	}
	else
	{
		cout <<"(insertion)The total seek distance is " <<dist_i <<endl;
		print(R3);//out put result to output filr
	}
	
	return 0;
}

