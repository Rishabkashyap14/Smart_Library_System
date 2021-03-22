# Test Cases for various scenarios
### Introduction
This module goes through the various test cases we have looked into for each of the modules covered in the project. 

### What does it do?
Each of the test cases look into a possible scenario that may or may not occur within the module, such as a syntax or possible semantic error

### Format of test cases
It will be divided into three main columns, consisting of the input given, the expected output and the actual output. 

### How does it detect faults?
The user entered output is placed in the last column and compared against the expected output.
- If the two of them match, it returns false
- If the actual output deviates from the expected output, then it returs true  
In this way we can point out the sources of possible errors that have not been taken care of instead of counting the ones already accounted for.
