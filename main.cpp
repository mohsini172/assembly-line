#include<stdio.h>
#define NUM_LINE 3
#define NUM_STATION 4
int min(int a, int b, int c) {
        if(a<b && a<c)
            return a;
        else if(b<a && b<c)
            return b;
        else if(c<a && c<b)
            return c;
        
    }



int n=4;
int carAssemblyRec(int a[][NUM_STATION], int t[][NUM_STATION], int *e, int *x,int n,int line){  
    if(n == 0){  
        return e[line] + a[line][0];  
    }  

    int T0 =10000000;  
    int T1 =10000000;  
    int T3 =10000000;
    if(line == 0){      
        T0 = min(carAssemblyRec(a, t, e, x, n-1, 0) + a[0][n],             
                            carAssemblyRec(a, t, e, x, n-1, 1) + t[1][n] + a[0][n],
                            carAssemblyRec(a, t, e, x, n-1, 2) + t[2][n] + a[0][n]
                            );    
    }else if(line == 1){       
        T1 = min(carAssemblyRec(a, t, e, x, n-1, 1) + a[1][n],             
                            carAssemblyRec(a, t, e, x, n-1, 0) + t[0][n] + a[1][n],
                            carAssemblyRec(a, t, e, x, n-1, 2) + t[2][n] + a[1][n]
                            );   

    }   
    else if(line == 2){
        T3 = min(carAssemblyRec(a, t, e, x, n-1, 2) + a[2][n],
                            carAssemblyRec(a, t, e, x, n-1, 0) + t[0][n] + a[2][n],
                            carAssemblyRec(a, t, e, x, n-1, 1) + t[1][n] + a[2][n]
                            );
    }

    return min(T0, T1, T3);  
} 


int findWithRecursive(int a[][NUM_STATION], int t[][NUM_STATION], int *e, int *x){
	return min(carAssemblyRec(a, t, e, x,4,0)+x[0],carAssemblyRec(a, t, e, x,4,1)+x[1],carAssemblyRec(a, t, e, x,4,2)+x[2]);
}


int carAssembly(int a[][NUM_STATION], int t[][NUM_STATION], int *e, int *x)
{
    int T1[NUM_STATION], T2[NUM_STATION], T3[NUM_STATION], i;
 
    T1[0] = e[0] + a[0][0]; // time taken to leave first station in line 1
    T2[0] = e[1] + a[1][0]; // time taken to leave first station in line 2
    T3[0] = e[2] + a[2][0];
    // Fill tables T1[] and T2[] using the above given recursive relations
    for (i = 1; i < NUM_STATION; ++i)
    {
        T1[i] = min(T1[i-1] + a[0][i], T2[i-1] + t[1][i] + a[0][i], T3[i-1] + t[2][i]+a[0][i]);
        T2[i] = min(T2[i-1] + a[1][i], T1[i-1] + t[0][i] + a[1][i], T3[i-1] + t[2][i] + a[1][i]);
        T3[i] = min(T3[i-1] + a[2][i], T1[i-1] + t[0][i] + a[2][i], T2[i-1] + t[1][i] + a[2][i]);
    }
 
    // Consider exit times and retutn minimum
    return min(T1[NUM_STATION-1] + x[0], T2[NUM_STATION-1] + x[1], T3[NUM_STATION-1] + x[2]);
}


bool test1(){
	int a[][NUM_STATION] = {{4, 5, 3, 2},
                {3, 10, 1, 4},
                {2, 1, 4, 1}};
    int t[][NUM_STATION] = {{0, 7, 4, 5},
                {0, 9, 2, 8},
                {1, 1, 1,10}};
                
    int e[] = {10, 12, 11}, x[] = {18, 7,1};
 
    int temp = findWithRecursive(a, t, e, x);
 	int temp2 = carAssembly(a, t, e, x);
    if(temp==temp2){
    	printf("Test1 Passed\n");
    	return true;
	}
	else{
		printf("Test1 Failed");
		return true;
	}
	
}


bool test2(){
	int a[][NUM_STATION] = {{4, 5, 3, 2},
                {3, 10, 1, 4},
                {1, 1, 1, 1}};
    int t[][NUM_STATION] = {{0, 7, 4, 5},
                {0, 9, 2, 8},
                {1, 1, 1,1}};
                
    int e[] = {10, 12, 1}, x[] = {18, 7,1};
 
    int temp = findWithRecursive(a, t, e, x);
    int temp2 = carAssembly(a, t, e, x);
    if(temp==6 && temp2==6){
    	printf("Test2 Passed");
    	return true;
	}
	else{
		printf("Test2 failed");
		return false;
	}
}

int main()
{
    test1();
    test2();
    return 0;
}
