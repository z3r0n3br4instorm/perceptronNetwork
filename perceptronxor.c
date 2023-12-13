#include<stdio.h>
#include<stdlib.h>
#include<time.h>

float returnRandomNumber(int x, int y) {
    srand(time(NULL));
    return (float)rand() / RAND_MAX * (x + y);
}

int perceptron(int x, int y, float w1, float w2, float b) {
    float fx;
    fx = (x * w1) + (y * w2) + b;
    if (fx > 0) {
        return 1;
    } else {
        return 0;
    } 
}

int main() {
/*
	We would require 4 Perceptrons to simulate an XOR gate.
		Perceptron    		Weights		Input 1		Input 2		Outputs		True Outputs
	
	AND PERCEPTRON X2 =		w1A, w2A	  x                y		  zA	         trueOutAnd 
	OR PERCEPTRON	  =		w1B, w2B          x                y              zB             trueOutOR
!	NOT PERCEPTRON 	  =             w1C, w1C          x                x              zC             trueOutNOT (PROBLEMATIC !) (BIAS CALCULATION)


*/
    float b1, b2, b3;
    float w1A, w2A, w1B, w2B, w1C, w2C; 
    int x[4] = {0, 1, 0, 1};
    int y[4] = {0, 0, 1, 1};
    int iter;
    int trueOutAnd[4] = {0, 0, 0, 1};
    int trueOutOR[4] = {0, 1, 1, 1};
    int trueOutNOT[4] = {1, 0, 1, 0};

    w1A = 1; // Initialize weights with random values
    w2A = 1;
    w1B = 1;
    w2B = 1;
    w1C = 1;
    w2C = 1;
    b1 = 0;
    b2 = 0;
    b3 = 0;

    printf("Weights : w1A = %f, w2A = %f, w1B = %f, w2B = %f, w1C = %f, w2C = %f\n", w1A, w2A, w1B, w2B, w1C, w2C);

    iter = 0;
    printf("Initializing Training Sequence\n");
    
    // Training the perceptrons
    // AND
    while (iter < 1) {
        for (int i = 0; i < 4; i++) { 
            while (trueOutAnd[i] != perceptron(x[i], y[i], w1A, w2A, b1)) {
                b1 -= 1;
            }
			printf("outputs matched for loop round %d\n",i );
            if (trueOutAnd[i] != perceptron(x[i], y[i], w1A, w2A, b1)) {
                iter = 0;
            } else {
                iter = 1;
            }
        }
    }
    iter = 0;
    printf("AND Neuron Trained\n");

    // OR
    while (iter < 1) {
        for (int i = 0; i < 4; i++) { 
            while (trueOutOR[i] != perceptron(x[i], y[i], w1B, w2B, b2)) {
                b2 += 1;
            }
			printf("outputs matched for loop round %d\n",i );
            if (trueOutOR[i] != perceptron(x[i], y[i], w1B, w2B, b2)) {
                iter = 0;
            } else {
                iter = 1;
            }
        }
    }
    iter = 0;
    printf("OR Neuron Trained\n");

    // // NOT
	// while (iter < 1) {
	// 	for (int i = 0; i < 4; i++) {
	// 		while (trueOutNOT[i] != perceptron(x[i], 0, w1C, w2C, b3)) { // Use 0 as the second input (single input for NOT)
	// 			b3 -= 0.1;
	// 		}
	// 		printf("outputs matched for loop round %d\n",i );
	// 		if (trueOutNOT[i] != perceptron(x[i], 0, w1C, w2C, b3)) { // Use 0 as the second input (single input for NOT)
	// 			iter = 0;
	// 		} else {
	// 			iter = 1;
	// 		}
	// 	}
	// }

    // printf("NOT Neuron Trained\n");

    printf("Outputs : zA = ");
    for (int i = 0; i < 4; i++) { // Change i <= 4 to i < 4
        printf("%d ", perceptron(x[i], y[i], w1A, w2A, b1));
    }
    printf("\n");

    printf("Outputs : zB = ");
    for (int i = 0; i < 4; i++) { // Change i <= 4 to i < 4
        printf("%d ", perceptron(x[i], y[i], w1B, w2B, b2));
    }
    printf("\n");

    // printf("Outputs : zC = ");
    // for (int i = 0; i < 4; i++) { // Change i <= 4 to i < 4
    //     printf("%d ", perceptron(x[i], x[i], w1C, w2C, b3));
    // }
    // printf("\n");

    //Building the XOR network
    int xor[4] = {0,0,0,0};
    printf("XOR Gate Output :");
    for (int i =0; i < 4; i++){
	xor[i] = perceptron(perceptron(x[i], !(y[i]), w1A, w2A, b1), perceptron(!(x[i]), y[i], w1A, w2A, b1), w1B, w2B, b2);
	printf(" %d", xor[i]);
    }
    printf("\n");

    return 0;
}
