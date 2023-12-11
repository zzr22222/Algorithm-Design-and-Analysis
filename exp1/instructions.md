**Project Name:** Performance Analysis of Sorting Algorithms

**Project Goal:** 

1. Implement selection sort, bubble sort, merge sort, quick sort, and insertion sort algorithms.
2. Use the size of the array to be sorted, *n*, as the input scale. Fix *n* and randomly generate 20 test samples to calculate the *average runtime* for different sorting algorithms across these 20 samples.
3. Repeat the experiment in step 2 with n=10000,20000,30000,40000,50000*n*=10000,20000,30000,40000,50000, etc., and plot the relationship between the average runtime of different sorting algorithms on 20 random samples and the input scale *n*.
4. Plot both the theoretically analyzed efficiency curves and the empirically measured efficiency curves. Note: Since the empirical efficiency is based on runtime and theoretical efficiency on the number of basic operations performed, an adjustment in their correspondence is needed. Adjustment approach: Use the runtime data of the input scale at 10000 as a reference point, calculate the theoretical runtime for other input sizes, draw the theoretical runtime curves for different scales, and compare them with the empirically measured efficiency curves. Are the empirical analysis and theoretical analysis consistent? If not, please explain the reasons for the inconsistency.
5. Now, given 1 billion data points (each data point being four bytes), quickly select the top ten largest numbers, and verify the correctness of the algorithm on smaller-scale data.