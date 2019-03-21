# Project 1 - Scrunching Integers

## Due Feb. 13 at 11:59 PM

## Project Description

For this project, you need to keep a large list of integers between +/- 1000 in the smallest space possible space. The numbers will be randomly distributed between -1000 and +1000. The maximum number of elements in this list is 4096. 

A C "char" variable is too small to keep a member of this list. A "char" only goes to +/- 127. An "int" will hold large enough numbers, but takes 32 bits, and that's a lot of wasted space. Your job is to find a way to store the list in memory, using the least possible space. 

You may assume that the numbers from the list will be saved to memory, in order, and will be retrieved a single time, in order. You will be given a space to work with that consists of an array of long (64 bit) integers that will be large enough to hold the entire list. You must use this memory to store the numbers. (No static, global, or malloc'ed memory may be used.) You may assume that all entries in the store are initialized to zero. Once the entire list has been entered, your "score" will be based on how many of the long integers you need to store the entire list. The fewer longs required, the better the grade, assuming that the proper values are returned. 

I have provided several files for you to make this job easier, and so you can concentrate on the job at hand. The API for your code is specified in `packInt.h`, which contains the following function prototypes:

```
	void putInt(int value, long store[]);
	int storeUsed(long store[]);
	int getInt(long store[]);
```  

The putInt function should take the value specified as the argument, and save it in the store. The storeUsed function should return the number of entries in store required to store the current list of numbers. The getInt function should return the next entry in the list of numbers, starting with the first number the first time getInt is called, then the next number when getInt is called again, and so on. You may assume that getInt will be called exactly the same number of times that putInt was called. You may not change these function prototypes.
	
Your code, the definitions for these three functions, should be included in a file called "packInt.c". 

Just to make life easier, I have included an example "packInt.c" file which stores 2 numbers in each store array member by using an "int" to store each number. Since two "int"s fit in each "long", I will need to use 50 store entries to store 100 numbers... plus a little overhead for book-keeping. If we keep track of (# of numbers saved)/(# of store entries used), we get a "score" of just under 2 with this very simple scheme. Clearly, a better job can be done. It's pretty easy to store 100 numbers in about 25 store entries and get a score just under 4, but I've found ways to do even better. My best was a score of about 5.8, but there may be schemes I haven't though of that do even better. Can you improve on my score?

You may assume that before the first call to `putInt`, store is initialized to all zeroes, that there will be many calls to `putInt`, followed by a single call to `storeUsed`, followed by many calls to `getInt`. You may also assume that `getInt` will be called the same number of times as `putInt` was called. No other call order is allowed. 
	
A test infrastructure is provided in the file "testPack.c" that reads a list of numbers from the file whose file name is specified in the first command line argument, invokes `putInt` on each one, invokes the `storeUsed` function to see how much of the store you used, then invokes `getInt` repeatedly and checks to make sure you retrieved the correct values. You should not need to modify this code.

I have also provided a test case generator in a file called "makeTest.c". This program takes a single command line argument - the number of values to put in a list, and then writes that many random numbers between -1000 and +1000 to standard output.

Finally, I have include a "Makefile" to make an executable, make test cases, and run the test cases using the executable. If you run `make test` in the project directory, the make command will use the Makefile to 

1) compile your code into an executable called testPack, if necessary
2) compile the test case generator into an executable called makeTest, if necessary
3) Run the makeTest executable to produce 3 test case files --- test1.txt which contains 10 entries, test2.txt which has 2000, and test3.txt which has 3000, if necessary
4) Run your testPack executable against all three test cases.

## Strategies

I found, in most cases, it was easiest to keep track of the index of the number in the list as my single "overhead" piece of information. (There was one very sophisticated implementation I had to track of the number of bits used instead, but it turned out that strategy didn't work very well.) You will see, in the example packInt.c file I provided that I used positive numbers while adding numbers to the store, but then started at zero, and used negative numbers to retrieve from the store.  Remember, you can have up to 4096 members of the list, so you need to make sure you have enough room to store large numbers for the overhead... even larger than entries of the list itself.

Next, remember that each store entry contains 64 bits. The trick is to make sure you are using as few bits as possible to store each number... but that you have enough bits to keep track of larger as well as smaller numbers. I find it very useful to reference the [Powers of Two Quick Reference](http://www.cs.binghamton.edu/~tbartens/CS220_Spring_2019/PowersOfTwo.html) page referenced as supplemental material from the class web page in cases like these. 

Remember in C, you need to use special bit-twiddling operations such as bitwise AND, bitwise OR, and left and right shifting to access individual bits or sets of bits within a larger variable. This project is a good exercise for learning about how to use these bit-twiddling operations. Oh, and don't forget. when you shift a signed integer to the right, the result is padded on the left with the sign bit, but if you shift an unsigned integer to the right, the result is padded on the left with zeroes.

When debugging, I found that at first, my bugs affected all numbers when I stored or retrieved those numbers. These are fairly easy to debug using gdb (the Gnu Debugger) by stepping through the code. However, eventually I got to special case code that was fairly deep into the list.  In these cases, using gdb, I found that it was useful to set conditional breakpoints, using gdb commands like `break testPack.c:19 if (n==72)`, which allows me to debug the 73rd item in the list.

If you are lost or stuck on a specific problem, please contact either a TA or the Professor, either during office hours or via e-mail. These projects are here to help you learn, not to get you frustrated, and we know how frustrating that sneaky bug can be!

## Submitting your Code

When you are finished editing and testing your code, make sure to commit and push your repository (which should contain the same set of files I provided to you) using git.  Then, do a `git rev-parse HEAD` from the project directory to get the hash code associated with the commit. Cut and paste that hashCode into the Project 1 submission area in the Project Submissions folder under Content for CS-220 in myCourses. You may submit as many times as you wish up to the deadline of midnight on Feb. 13, but only the last submission will be graded.

## Grading your Submission

You code will be compared against all other CS-220 student submissions. If you wrote your own project code, it will be different enough from other students so that there will be no problem - even if you worked as a team on the concepts. If you cut and paste your code, or if your code is cut and pasted by someone else, even if you modify variable names, comments, white space, etc. it will be considered plagiarism, and result in a zero grade.

If you turn in your code late, 10 points will be deducted for each 24 hours late, unless you have received an extension from the professor.

Missing or lack of attempt to solve the problem will result in a zero grade.

If your code does not compile, or has an obvious bug, I will try to fix your code, deducting 15 points for each fix. Bugs include things like using global variables (static storage) to store numbers or overhead, incorrect reporting of storeUsed values, extra debug prints to stdout, as well as any compiler error. If you seriously tried to do the assignment, but need more than 3 fixes, you will get a 60 point deduction.

There will be a 5 point deduction for each class of compiler warning generated by your code. 

Your code will be run against 3 valid but random test cases, and up to 10 points will be deducted per test case, depending on the score you get, compared to the best score I can get. If you get equal or better, no points will be deducted.

Remember, this is the first of four projects, and the lowest project score will be dropped - so if you are totally lost, don't worry too much. You will have a chance to recover. However, projects tend to get more difficult as the semester progresses, so take some time to see if you can get a decent score on this one.
