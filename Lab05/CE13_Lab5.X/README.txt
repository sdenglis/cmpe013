/*****************
 *Samuel English *
 *CMPE13/L       *
 *Lab 05         *
 *5/04/2019      *
 *****************/

>> Collaboration with others: NONE

1.) Timing Results:
Target halted. Stopwatch cycle count = 211571 (211.571 ms)
Target halted. Stopwatch cycle count = 112218 (112.218 ms)   // Selection Sort
Target halted. Stopwatch cycle count = 678445 (678.445 ms)
Target halted. Stopwatch cycle count = 24809 (24.809 ms)     // Insertion Sort

>> In the end, InsertionSort() ended up beating SelectionSort() in terms of efficiency and clock speed.
>> While it took over 110 ms for SS, IS deftly beat it with a solid 25 ms -> more than 4x faster!
>> The reason for this time discrepancy being that insertion sort's inner loop deals with previously-sorted elements.
>> Thus, it gives itself leniency to find the correct location through comparisons rather than the brute-force iteration
>> techniques associated with selection sort. In other words, selection sort has to search the entire unsorted list,
>> whereas insertion sort acts by searching the already sorted section to find where to place the next element.

2.) Summary:

>> In a word, the lab was to get us students acquainted with multiple items and concepts within C: namely, 
>> this lab prepared us to use and define structures, manipulate sub-members, use defines and conditions.
>> There wasn't anything specfically new, except for malloc() and free(), which were just extensions of
>> things we already knew. I gained lots of experience in pointers, memory allocation as well as sorting
>> algorithms, all being applicable to other projects, the foundations for later ideas.

3.) Approach:

>> My approach to the lab was as I've done previously. This time around, I was blessed with a head-start;
>> I was able to finish most of the LinkedList.c during the weekend, allowing myself time to debug and
>> work on the sort.c during the week. I still find it rather challenging yet tedious, having the lab due
>> in the middle of the week. It forces me to either put off other assignments due the same day, or
>> wait to finish the lab the day of. Fortunately, having read the lab manual, gathering resources and 
>> attending lecture, things went fairly smoothly. The only issue I had was with the InsertionSort() function
>> simply because the pseudo-code posted in the lab manual was partially incorrect.

4.) Comments:

>> In the end, I have officially finished the assignment not only to the best of my abilities, but also up
>> to the standards specified within the lab manual. I didn't actually have to spend a ton of time on this
>> assignment, but I didn't have a lot of time to work with in the first place. One of my main complaints 
>> is the due date: lots of other classes have a majority of their weekly coursework due in the middle of
>> the weeek; this creates an unnecessary amount of pressure on us, attempting to complete each coding project
>> before midnight, while also completing other requirements for other things. In the future, I think that,
>> for this lab specifically, there could have been more information regarding the sorting mechanisms as well
>> as the pseudo-code. The discussions during class were very helpful.
