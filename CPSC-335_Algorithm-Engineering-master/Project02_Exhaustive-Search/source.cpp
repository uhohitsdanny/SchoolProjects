// Assignment 2: Topology recognition problem                                   
// Sangyong Jin, Danny Navarro, Shelley Pham

// Given a network with n>3 nodes and a weight matrix W[0..n−1, 0..n−1] of      
// positive integers, of a weighted, connected undirected graph modeling        
// a network, decide whether the network is one of the topologies, if any:      
// ring, star, fully connected mesh. Note: represent infinity by the value 100.
// INPUT: a positive integer n and a list of n^2 positive values          
// OUTPUT: message "ring" or "star" or "complete" or "neither"                  

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <chrono>
#include <fstream>
#include <string>

using namespace std;

void print_to_file(int n, int W[][100], string topology, double seconds);

int main() {
	char repeat = 'y';
	double seconds = 0;
	string topology;

	int n, i, j, count, center;
	int W[100][100];
	bool cond;

	// display the header                                                         
	cout << endl << "CPSC 335-x - Programming Assignment #2" << endl;
	cout << "Topology recognition algorithm" << endl;
	cout << "Enter the number of nodes in the topology" << endl;
	// read the number of nodes                                                   
	cin >> n;
	// read the weight matrix                                                     
	cout << "Enter the positive weights, 100 for infinity" << endl;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			cin >> W[i][j];

	cout << "The topology is" << endl;

	// Start the chronograph to time the execution of the algorithm               
	auto start = chrono::high_resolution_clock::now();
	count = 0;
	cond = true;
	// loop to check whether the topology is a ring       
	for (i = 0; i < n; i++) {
		// YOU NEED TO IMPLEMENT THIS LOOP
		for (j = 0; j < n; j++) {
			//count number of edges connected to the vertex
			if (W[i][j] != 0 && W[i][j] != 100)
				count++;
		}
		//if there's not exactly 2 edges connected to the vertex, it's not a ring
		if (count != 2) { cond = false; break; }

		count = 0; //reset counter
	}

	// End the chronograph to time the loop       
	auto end = chrono::high_resolution_clock::now();

	if (cond) {
		topology = "ring";
		cout << topology << endl;
		int microseconds = chrono::duration_cast<chrono::microseconds>(end - start).count();
		seconds = microseconds / 1E6;
		cout << "elapsed time: " << seconds << " seconds" << endl;
		print_to_file(n, W, topology, seconds);
		system("pause");
		return EXIT_SUCCESS;
	}
	//for personal checking
	else {
		cout << "Not a ring" << endl;
		cout << "A ring should have 2 edges connected to each vertex" << endl;
		cout << "Stopped at: [" << i << ", " << j << "]" << endl;
		if (count > 2)
			cout << "This is not a ring because there are " << count << " edges connected to a vertex" << endl << endl;
	}


	// Start the chronograph to time the execution of the algorithm             
	start = chrono::high_resolution_clock::now();

	count = 0;
	cond = true;
	center = 0;
	// loop to check whether the topology is a star                               
	for (i = 0; i < n; i++) {
		// YOU NEED TO IMPLEMENT THIS LOOP
		for (j = 0; j < n; j++) {
			//count the number of edges 
			if (W[i][j] != 0 && W[i][j] != 100)
				count++;
		}

		//if there's already a center and there's more than 1 edge, it's not a star
		if (center == 1 && count > 1) { cond = false; break; }
		//if there's a vertex with n-1 edges, it could be a star
		if (count == n - 1) { center = 1; }

		count = 0; //reset counter
	}
	//if we reached the end of the matrix and has no center, then it's not a star
	if (center == 0) { cond = false; }

	// End the chronograph to time the loop       
	end = chrono::high_resolution_clock::now();

	if (cond && (center == 1)) {
		int microseconds = chrono::duration_cast<chrono::microseconds>(end - start).count();
		seconds = microseconds / 1E6;
		topology = "star";
		cout << topology << endl;
		cout << "elapsed time: " << seconds << " seconds" << endl;
		print_to_file(n, W, topology, seconds);
		system("pause");
		return EXIT_SUCCESS;
	}
	//for personal checking
	else {
		cout << "Not a star" << endl;
		cout << "A star should include one vertex with " << n - 1 << " edges and other vertices have 1 edge connected to the center" << endl;
		cout << "Stopped at: [" << i << ", " << j << "]" << endl;
		if (count > n - 1)
			cout << "This is not a star because there are " << count << " edges connected to a vertex" << endl;
		if (center == 0)
			cout << "This is not a star because there's no center" << endl;
		cout << endl;
	}

	// Start the chronograph to time the execution of the algorithm             
	start = chrono::high_resolution_clock::now();

	cond = true;
	// loop to check whether the topology is a fully connected mesh
	for (i = 1; i < n; i++) {
		// YOU NEED TO IMPLEMENT THIS LOOP
		for (j = 0; j < i; j++) {
			//check whether there exist a vertex that's not connected to another one
			if (W[i][j] == 100) { cond = false; break; }
		}
		//if there exist a vertex that's not connected to another existing vertex, it's not a mesh
		if (!cond) { break; }
	}

	// End the chronograph to time the loop       
	end = chrono::high_resolution_clock::now();

	if (cond) {
		topology = "fully connected mesh";
		cout << topology << endl;

		int microseconds = chrono::duration_cast<chrono::microseconds>(end - start).count();
		seconds = microseconds / 1E6;
		cout << "elapsed time: " << seconds << " seconds" << endl;
		print_to_file(n, W, topology, seconds);
	}
	else {
		//for personal checking
		cout << "Not a mesh" << endl;
		cout << "A mesh should include all vertices that have " << n - 1 << " edges connected to one another" << endl;
		cout << "Stopped at: [" << i << ", " << j << "]" << endl;
		cout << "This is not a mesh because there are " << count << " edges connected to a vertex" << endl << endl;

		topology = "neither";
		cout << topology << endl;
		int microseconds = chrono::duration_cast<chrono::microseconds>(end - start).count();
		seconds = microseconds / 1E6;
		cout << "elapsed time: " << seconds << " seconds" << endl;
		print_to_file(n, W, topology, seconds);
	}

	system("pause");

	return EXIT_SUCCESS;
}

void print_to_file(int n, int W[][100], string topology, double seconds) {
	//asks if user wants to output result to textfile
	char ans;
	cout << "Do you want to save these results to a textfile? (y/n): ";
	cin >> ans;
	if (ans == 'y' || ans == 'Y') {
		ofstream resultfile("topology.txt");
		if (resultfile.is_open()) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					resultfile << W[i][j] << " ";
				}
				resultfile << endl;
			}
			resultfile << "\nThe topology is a " << topology << endl;
			resultfile << "Elapsed time: " << seconds << " seconds" << endl;
		}
	}
}