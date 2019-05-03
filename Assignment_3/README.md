# Assignment_3 Face Routing

### Explanation

How do we send messages nowadays and how can we assure we send it to the right person? The answer is obvious, via internet of course. But how it works? This is a simple program simulate one of the geographic routing  a routing principle that relies on geographic routing a routing principle that relies on geographic position -- face routing. Face routing is mainly proposed for wireless networks. First assume each node in the network graph has three main information: source node, it's own neighbor nodes and destination node, the rest is unknown. Since other informations are unknown how can we send out our packet all the way from source to destination?
* Generate the network graph to planar graph (No crossing link)
* When sending message, the message can be seen as a packet. The packet will have 5 important informations: source, destination, last hop, next hop and previous intersection point
* Initialize the packet when message generate and push into the queue of source
* Get next hop is the core of this program and I generalize 5 cases to discuss
    1. **Case 1: current node is intersection point**
        Draw a line from current to destination (SD), all the crossing point on the line are called intersection point. If intersection point is also a node on the network than, walk from destination to current via SD with right hand touching SD and turn left when encounering current intersection point. This can do by using simple trigonometric. Vector v1=from current to destination. Vector v2=from current to it's neighbors. Using arccos to find the smallest angle and that node is the next hop.
    2. **Case 2: next node won't cross source destination line**
        In face routing, we hope most of the time we are in the same side of SD, we want to minimize the crossing condition. Same as case 1 we will have two vector. v1=from current to last hop. v2=from current to every other neighbor. First we find all the angle and get neighbor (n1) with smallest angle. Check if n1 is on the same side as current node (base line is SD). If same next hop is n1
    3. **Case 3: if the intersection point has seen before cross the line**
        If n1 cross SD, than find the intersection point. If the intersection point has seen before than we simply cross the line and next hop is n1
    4. **Case 4: if calculate angle from intersection point can cross the line than cross the line**
        If the intersection we find at case 3 haven't seen before than we update the intersection in packet to this one. Again walk from destination to this intersection point with right hand touching SD, turn left when encountering intersection point. If from this calculation it tells us to cross the line than we cross the line. Next hop is n1
    5. **Case 5: if stay at current node**
        The outcome of calculation from case 4 may tell us to stay on current node. Than what we do is to specify last hop as intersection point or n1. And calculate again check from case 2 to case 5. The loop will stop when it finally find the next hop. Don't worry for infinite loop, because we assume the network graph is connected.
    6. Note: If the case 1-4 any one is matched than it return immediately. Only when case 5 happens will go into loop.
* After getting the next hop, we send out the packet.

P.S. How to specify the angle
![](https://i.imgur.com/2tXsnKu.png)

### How to use this program

1. Open terminal and change directory to this program's directory ex: Assignment_3
2. type `make`
3. Then the executable file `assignment_3` should be in this directory
4. Then execute the program `./assignment_3`
5. The result file `result.txt` should be in this directory after the execution.
6. Also the screen will print out more detailed information of the condition in every state.