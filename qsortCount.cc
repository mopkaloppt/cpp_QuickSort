#include <iostream>
#include <ctime>
#include <cstdlib>
// Q5 
/* 
	Avg case = theta n lg n
	n because it compares every element, lg n because it splits 
	
	Worst case = n^2
	pick the worst pivot (the one that doesn't split the array e.g. 
	the smallest number because no other numbers will be less than it)

	Why you unlikely to observe worst case runtime in practice?
	- Because the probability of getting worst case is 1/n 
	1/n(1/n-1)(1/n-2) = 1/n! 
	and if you pick the pivot randomly, it's unlikely ever gonna happen 
	that you'd pick the worst pivot everytime. 

	In-place or stable sort? Why?
	- Not in-place 
	because creating tmp for swapping needs an extra memory location 
	while you wait for the recursive call to come back all those extras 
	are still in the stack

	- Not stable because you pick the pivot randomly everytime 
	example: 3 4 6 7 4 -> 4 4 6 7 3 :swap(x[a], x[p]);


*/

int * x;
int comps; // Q2

void swap(int & a, int & b) {
	int tmp = a;
	a = b;
	b = tmp;
}

int randint(int a, int b) {
	return a + (rand() % (b - a + 1));
}

// Q4
float c(int n){
	if(n<=1)return 0;
	float sum = 0.0;
	for(int m=1;m <=n; m++){
		sum += n-1 +c(m-1) + c(n-m);
	}
	return sum / n;
	// C(n) = sum(from m=1 to n)[n-1+C(m-1)+C(n-m)]/n
}

// Q3
int qc (int n) {
	int pivot;
	if (n <= 1) return 0;

	pivot = randint(0, n);
	// recurrence relation for quicksort avg. case
	return n-1 + qc(pivot) + qc(n-pivot-1);
}


void quicksort(int a, int b) {
	if (a >= b) return;
	int p = randint(a,b); // pivot
	swap(x[a], x[p]);
	int m = a;
	int i;
	// in-place partition:
	for (i = a+1; i <= b; i++) {
		if (x[i] < x[a]) {
			swap(x[++m], x[i]);
		}
		comps++;
	}
	swap(x[a],x[m]);
	quicksort(a, m-1);
	quicksort(m+1, b);
}

#define NN 1000

int main(int argc, char *argv[]) {
	srand(time(0));

	// change the following code
	int repetitions = 100, j;     //Q2 run for 100 repetitions
	x = new int[NN];
	j = repetitions;
	while (j>0) {
		for (int i=0; i<NN; ++i) {
			x[i] = rand() % NN;
		}
	
		quicksort(0, NN-1);
		j--;
	}

	std::cout << "comps: " << comps << std::endl;
	std::cout << "Avg # of comps: " << comps/repetitions << std::endl;
	std::cout << "Avg of qc: " << qc(NN) << std::endl;

	// for (int i=0; i<NN; ++i) {
	// 	std::cout << x[i] << " ";
	// }
	// std::cout << std::endl;

	delete[] x;
	return 0;
}

