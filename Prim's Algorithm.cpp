#include <iostream>

//Create a macro for MAX integer value
#define I 32675

//Globals
//Cost adjacency matrix which will represent 7 verticies 
//We will make it 8x8 ignoring the first row/column 0
//This cost adjacency matrix will hold the adjacent verticies and their weights
//This will be an undirected graph, so there will be duplicates
//While iterating through the adjacency matrix, we only need to iterate 
//through the upper triangle or the lower triangle 
int cost[][8] = {
	{I,I,I,I,I,I,I,I},
	{I,I,25,I,I,I,5,I},
	{I,25,I,12,I,I,I,10}, 
	{I,I,12,I,8,I,I,I}, 
	{I,I,I,8,I,16,I,14}, 
	{I,I,I,I,16,I,20,18}, 
	{I,5,I,I,I,20,I,I}, 
	{I,I,10,I,14,18,I,I}, };


//We also need a near array, which will represent the closest edge
//between two verticies, based on the already visited verticies 
//The index represents a vertex, along with element within the index
//We are looking for the closest edges so we can initialize each element
//with INF
//We will be using 1-7 to represent the vertex, and ignore 0
int near[8] = { I,I,I,I,I,I,I,I };

//We will use a 2 x 6 matrix to represent the solution, where we will
//place the vertex pair that is the closest through each iteration
//To represent the shortest path using Prim's algorithm
int t[2][6];



int main() {

	//Prim's Algorithm

	//Declare variables
	int i, j, k, u, v, n = 7,min = I;

	//Initialize stage:
	//To start off, we must iterate through the cost adjacency list and 
	//locate the minimum cost edge. We can do so by iterating through the list
	//Since there are duplicates we only have to iterate through the upper
	//Half of the matrix
	//We can use a double for loop to iterate through it
	//We are starting from 1 in our for loop since we are ignoring 0
	
	//The first loop will scan through the rows
	for (i = 1; i <= n; i++) {

		//The second loop will scan through columns, but we should not scan through
		//all the columns, just the upper triangle portion, so j can start from i
		for (j = i; j <= n; j++) {

			//Through each iteration, check if i/j edge is less than min
			//if so replace min, and take note of i and j in two new variables
			//u and v
			if (cost[i][j] < min) {

				min = cost[i][j];
				u = i;
				v = j;
			}
		}
	}

	//With this initial step, we have found the very first vertex pair that 
	//has the smallest cost , we want to insert u and v within our solution matrix t
	t[0][0] = u;
	t[1][0] = v;

	//Likewise, after updating our solution matrix, we need to update our near array
	//to show the nearest verticies from each other, based on the vertexes visted
	//so far we have only visted u and v
	//Since we have already visted u and v, we will set them to 0 in near
	//to represent that they have already been visited
	near[u] = 0;
	near[v] = 0;

	//Now we can update the near array
	for (i = 1; i <= n; i++) {

		//I is a vertex, so now we check whether u or v is closer
		//The closer one gets inserted
		//All values 

		if(near[i] != 0){

			if (cost[i][u] < cost[i][v]) {
				near[i] = u;
			}
			else {
				near[i] = v;
			}

		}
	}

	//Initialization done
	
	//Now we have to include the rest of the edges which are going to be
	//repeated steps from before
	//We can create a for loop that will continue until every vertex pair 
	//is filled within our solution matrix, since we initialize it with a 
	//vertex pair already we can start at 1
	for (i = 1; i < n - 1; i++) {


		//We want min here because it first get initialized to min
		//And then once it goes into the for loop, it keeps that value
		//and finds the min
		min = I;

		//The first thing we can do, is check the near array
		//and figure out the next minimum vertex pair
		//We can use a for loop to iterate through the near array
		for (j = 1; j <= n; j++) {

			
			 
			//Find out which pair is minimum
			if ( near[j] != 0 && cost[j][near[j]] < min ) {

				//We want to assign k with j, in order to figure out if 
				//k is the nearest while updating near

				k = j;
				min = cost[j][near[j]];
			}
		}
		//Once we found our vertex pair, we can insert it into our solution matrix
		//its i'th row because we initialized it beforoe, and our outer for loop
		//is iterating through our solution matrix
		t[0][i] = k;
		t[1][i] = near[k];
		/*std::cout << "(" << t[0][i] << "," << t[1][i] << ")" << std::endl;*/
		//Once we insert it intion the solution matrix, we then modify the 
		//near array to show k has been visited
		near[k] = 0;

		//Now we have to check if k is the new closest in the near array
		//We can iterate through near again checking for k
		for (j = 1; j <= n; j++) {
			//Check if k is the new minimum
			if (near[j] != 0 && cost[j][k] < cost[j][near[j]]  ) {
				near[j] = k;
			}
		}
	}

	//Now we can print the solution
	for (i = 0; i < n - 1; i++) {
		std::cout << "(" << t[0][i] << "," << t[1][i] << ")" << std::endl;
	}


	return 0;
}















