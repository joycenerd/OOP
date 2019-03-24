# Assignment_2 Online Resource Allocation

### Explanation

This is related to real world problem. Both request and resource will appear from time to time, and each resource can be used by numerous requests and so does each request can be assigned to numerous resources. But at last each resource can only accept one request. The question is to find as many <request,resource> pair as possible. If using deterministic algorithm then the accepted request may be lower than half of the total request, so I use randomize algorithm. For every new request, I generate a random number as the request's weight. If the resource can be used by more than one request, I matched the one with the largest weight to the resource. The accepted request may be more than half of the total requests at this point. At last, output the number of total satisfied request and all the matching pair.

### How to use this program

1. Open terminal and change directory to this program's directory ex: Assignment_2
2. type `make`
3. Then the executable file `assignment_2` should be in this directory
4. Then execute the program `./assignment_2`
5. The result file `result.txt` should be in this directory after the execution.