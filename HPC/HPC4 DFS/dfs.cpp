#include<iostream>
#include<omp.h>
#include<chrono>
#include<time.h>

using namespace std;
using namespace std::chrono;

class Node
{
  public:
	int val;
	Node *left;
	Node *right;

	Node(int val)
	{
		this->val = val;
		this->left = NULL;
		this->right = NULL;
	}
};

void serial_dfs(Node *t)
{
	if(t == NULL)
		return;

	serial_dfs(t->left);
	cout<<t->val<<"  ";
	serial_dfs(t->right);
}

void parallel_dfs(Node *t)
{
	if(t == NULL)
		return;

	#pragma omp parallel sections
	{
		#pragma omp section
		{
			parallel_dfs(t->left);
      std::cout<<t->val<<"  ";
		}



		#pragma omp section
		{
			parallel_dfs(t->right);
		}
	}
}
void inorderTraverse_Task(Node *t)
{
		// Generating task to traverse Left Subtree by the team of threads
 		if(t->left!=NULL){
		#pragma omp task
    		inorderTraverse_Task(t->left);
		}

		#pragma omp taskwait
		printf("%d ", t->val);

		//Generating task to traverse Right Subtree by the  team of thread
 		if(t->right!=NULL){
		#pragma omp task
    		inorderTraverse_Task(t->right);
    		}

		#pragma omp taskwait
}

int main()
{
	int n = 10000;
	int arr[n];

	for(int i=0;i<n;i++)
		arr[i] = rand()%100;

	Node *root = NULL;

	if(root == NULL)
	{
		Node *node = new Node(arr[0]);
		root  = node;
	}

	for(int i=1;i<n;i++)
	{
		Node *n = new Node(arr[i]);
		Node *temp = root;

		while(temp != NULL)
		{using namespace std::chrono;
			if(temp->val > arr[i])
			{
				if(temp->left != NULL)
					temp = temp->left;
				else
				{
					temp->left = n;
					break;
				}
			}

			else
			{
				if(temp->right != NULL)
					temp = temp->right;
				else
				{
					temp->right = n;
					break;
				}
			}
		}
	}

	time_point<system_clock> start,end;

	start = system_clock::now();
	serial_dfs(root);
	end = system_clock::now();
	duration<double> t = end-start;
	cout<<"The time required for serial is :- "<<t.count()*1000<<endl;

	start = system_clock::now();
	parallel_dfs(root);
	end = system_clock::now();
	t = end-start;
	cout<<"The time required for parallel is :- "<<t.count()*1000<<endl;

  start = system_clock::now();
	inorderTraverse_Task(root);
	end = system_clock::now();
	t = end-start;
	cout<<"The time required for parallel inoerder is :- "<<t.count()*1000<<endl;
	return 0;
}


/*
Description :Uses OpenMP-3.0 Task Construct which is an efficient approah.
Whenever a thread encounters a task construct,a new explicit task, An explicit
task may be executed by any thread in the current team, in parallel with other
tasks.In this approach the several task can be executed in parallel.

@param : starting pointer of the tree
*/
/*
void inorderTraverse_Task(struct node *r)
{
		// Generating task to traverse Left Subtree
		   by the team of threads
 		if(r->left!=NULL){
		#pragma omp task
                        inorderTraverse_Task(r->left);
		}

		#pragma omp taskwait
		//printf("%d ", r->info);

		//Generating task to traverse Right Subtree by the
		   team of thread
 		if(r->right!=NULL){
		#pragma omp task
                                inorderTraverse_Task(r->right);
                }

		#pragma omp taskwait
}
*/
/*
Description :Uses OpenMP-2.5 parallel - section  directive.
whenever a thread encounter the parallel region it creates the team of
threads. When the thread in a team encounter the section directive it
execute the section region. Then the sections will be executed by different
threads parallely.This approach can be costly, however, because
of the overhead of parallel region creation, the risk of oversubscribing
system resources, difficulties in load balancing, and different behaviors
of different implementations

@param : starting pointer of the tree
*/
/*
void inorderTraverse_Wtask(struct node *r)
{
       // Create the parallel region
	#pragma omp parallel sections num_threads(1)
	{
	 	// Creating section to traverse the
		   Left subtree by a thread 1 //
                #pragma omp section
				{
                	if(r->left!=NULL)
                    {
					    inorderTraverse_Wtask(r->left);

					}
					//printf("%d ", r->info);
                }
	 	// Creating section to traverse the Right subtree by a thread 2
                #pragma omp section
                if(r->right!=NULL){
                                inorderTraverse_Wtask(r->right);
                }
	}

}
*/
