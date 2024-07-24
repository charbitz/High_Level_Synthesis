# Description
***This repo contains all 6 requested assignments of the course **Hogh Level Synthesis** of the 9th semester.***

* **This repo is for demonstration purposes only**

## Assignment 1

### Exercise 1:
* Write a C++ function that accepts an unsigned 32-bit integer (unsigned int) number and counts the number of bits that are equal to one. Prepare a test program that will test the function for pseudo-random input numbers.

### Exercise 2:
* Write a C++ function that calculates the checksum of a number of type unsigned int. Again, prepare a test program to check the correct functionality of your function.

## Assignment 2

### Exercise 1:
* For some given examples, choose the minimum number of bits required to fully represent the result.

### Exercise 2:
* You are asked to write two functions in C++. The first function takes as input a signed integer of W bits (ac_int<W,true>) and computes its Canonical Signed Digit (CSD) representation. The second function takes the CSD representation of a constant and a signed integer and computes their product using shifts and additions/subtractions. Prepare a test program that will test the function for pseudo-random input numbers.

### Exercise 3:
* You want to design a run-length encoding circuit. Your circuit receives 4-bit unsigned integers via an ac_channel (i.e., ac_channel<ac_int<4,false>> &in). After ensuring that the channel has at least 10 values stored, you need to encode them so that consecutive occurrences of the same value are transmitted as the value and the number of times it appears. The encoded pairs (value, count) should be output serially to an output channel ac_channel<ac_int<4,false>> &out each time they are ready. Additionally, create a flexible test program in C++ to test your circuit.

## Assignment 3

### Exercise 1:
<!-- ### Exercise 2:
### Exercise 3: -->