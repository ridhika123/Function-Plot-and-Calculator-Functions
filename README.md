# Function Plot and Calculator Functions

## Prompt
Imagine you've been transported back to 1990 and you have been called on to write part of the plot functionality for a soon-to-be popular line of graphing calculators. How would you solve the problem?

We don't have real graphing calculators at our disposal, but the terminal will serve as a reasonable proxy. One original line of graphing calculators allowed the user to enter a generic function with text like y=2*sin(x)-x^3. Calculating values like that is certainly straightforward enough in C, but getting the correct locations of the dots on the screen takes some thought.

Now, what tasks might our plotter need to do? Let's try to answer that question, building up a list of (eventual) functions we'll need to write.

* Draw graphs. Better make a function for that. We can store the values to be plotted in an array.
* Convert indices. Before we can store a mathematical function value f(x) into an array at values[index], we need a way to convert the array index to the mathematical function input x.
* Find ranges. In order to see all of a function on the screen, we'll need to find its minimum and maximum (calculated) function value over the plotted domain.
* Quantize values. To determine which of the discrete rows to draw a marker for the function, we'll need to quantize those continuous values, which is to say convert them into discrete integers.
* Test everything. Of course, we'll want to rigorously test all these pieces to make sure they work correctly.

We'll probably think of some other stuff along the way, but often writing out comments and working from the top down to the details as we stub out functions helps us figure that out. Now, let's go to work.

Write a program called plot.c that will contain the functions for generating the plots and testing the procedures within, all according to the following specifications.

Note that because we'll be drawing to a screen with very coarse resolution, we'll be using float variable types; the double type has far more precision than necessary. Except in specialized hardware such as GPUs or DSPs, it is rare on today's general computer systems for there to be any significant performance difference between these two types.

## Response
The program containing the functions and testing is [here](https://github.com/ridhika123/Plot/blob/main/plot.c).
