# Basic building blocks of C++

For this assignment you will code using some of the basic building blocks of C++: vectors, functions, and classes.  

## The PEP vector class -- technical note

To ensure you are using `vector` correctly, for this work you will be using a version specially adapted for this assignment.  It is used by all the skeleton code provided, and involves writing:

`#include "vector.h"`  
`using pep::vector;`  

... instead of the usual:

`#include <vector>`  
`using std::vector;`  

This should not affect your solution, but note that outwith this assignment you should use the regular std vector implementation where appropriate.


# Buy low, sell high

The price of a given commodity, can be represented by a vector of prices.  For instance:

`vector<int> prices {28, 18, 20, 26, 24};`  

To maximise profit, we would want to buy low and sell high -- in this case, buy at time 1 (when the cost is 18), sell at time 3 (when the cost is 26).

In `Trade.h` implement a function `bestBuySellTime` that takes a vector of prices and returns a `Trade' object with the buy and sell time that maximises profit.  This function does not live inside any class -- it is to be defined as a global function.  *(Note that as the price vector may be large, avoid copying it within your implementation.)*

To perform some basic testing on your code, once you have implemented the function (or at least declared it) `TestTrade.cpp` defines a simple test harness.  To compile this, run:

`g++ -std=c++11 -o TestTrade TestTrade.cpp`  

If it compiles, you can then run:

`./TestTrade`  



# A circular buffer

## What is a circular buffer?

Circular buffers use a fixed-size block of memory to temporary buffer data.  For instance, keypresses on the keyboard put characters in the buffer; and when the operating system is ready to process them, it reads characters from the buffer.

The buffer starts as being empty.  For instance, if we had a buffer of size 5 it would look like:

`[   |   |   |   |   ]`  


If we then write 'a' and 'b' into the buffer it would look like:

`[ a | b |   |   |   ]`  


...and then removing the next item in the buffer would give:

`[   | b |   |   |   ]`  


If we continue to write elements into the buffer, e.g. 'c', 'd', 'e', 'f' then when the end is reached, elements start being written into any spare space at the start:

`[ f | b | c | d | e ]`  


At this point the buffer is full.  We can't write any more data to it -- in the case of keyboard buffers, the computer would start beeping.  We can though remove an element, which always removes the *oldest*, i.e. the letter 'b', which would leave the buffer:

`[ f |   | c | d | e ]`  

We could then remove the next element (c), or as there is now a space again, write another character into the buffer.

## Implement a circular buffer

In the file`CircularBuffer.h` complete the definition of the CircularBuffer class.  Your implementation should be based on a vector of characters.

The constructor of the class should take the capacity of the buffer as an argument.  There should be no default constructor.

It needs to have the functions:  
1. `count()` which returns how many things are in the buffer  
2. `full()` which returns true *iff* the buffer is full  
3. `add()` which takes a character and adds it to the buffer (you can assume the buffer is not full)  
4. `remove()` which removes and returns the next character from the buffer (you can assume the buffer is not empty)  
 
Once you have provided the constructor and functions, you can test your code using `TestCircularBuffer.cpp`.  To compile this, run:

`g++ -std=c++11 -o TestCircularBuffer TestCircularBuffer.cpp`  

If it compiles, you can then run:

`./TestCircularBuffer`  

As well as being confident your solution behaves correctly, you should ensure that any functions that should be `const` (because they do not change the buffer) are marked as const; and ensure you use the initialisation syntax with your constructor to appropriately initialise the vector to be the right size.

# Items to collect on a map

For this piece of coursework, you will write code to store and work with a map of items to collect, each of which is available for just 15 minutes starting at a certain number of seconds past the hour.  You then will write an algorithm that finds a route that (attempts to) collect them all.

# Part (i): The Item class

Items are described by four properties:

- Their latitude (a number in degrees, e.g. 51.75087595155126)
- Their longitude (a number in degrees, e.g. -0.33483137537806396)
- A string ID
- The time at which they become available: an integral number of seconds past the hour

In Item.h, make a class Item that contains these as private member variables.

Give the class an appropriate constructor that initialises these four variables to the arguments passed to the constructor (passed in the above order).

Implement an `operator<<` function for printing out Item objects, so that the following code will work:

`Item strand(51.5115, -0.116, "StrandCampus", 600);`  
`cout << strand << endl;`  

...and will produce output of the form:

`{latitude, longitude, "ID", time}`

...in this case:

`{51.5115, -0.116, "StrandCampus", 600}`  


Once you have done this, create a class function `distanceTo` that will take another Item, and return the distance to it in metres.  To compute this distance, use the [Haversine Formula](http://andrew.hedges.name/experiments/haversine/), which can be implemented using the following pseudo-code:

`dlon = lon2 - lon1`  
`dlat = lat2 - lat1`  
`a = pow((sin(dlat/2)), 2) + cos(lat1) * cos(lat2) * pow((sin(dlon/2)), 2)`  
`c = 2 * atan2( sqrt(a), sqrt(1-a) )`  
`distance = R * c (where R is the radius of the Earth)`  

Note that this pseudo-code assumes the latitude and longitude are in *radians*, whereas your class stores them in degrees, so you will need to convert them to radians first.  `cos`, `sin` and the other trignometric functions can be obtained by putting `#include <cmath>` at the top of Item.h.  You should assume `R`, the radius of the earth in metres, is 6373000.

To test your code, you can use ItemTest.cpp.  To compile to an executable `ItemTest`, run:

`g++ -std=c++11 -o ItemTest ItemTest.cpp`  

Note that this will only work once you have implemented the constructor and functions discussed above.

# Part (ii): A Map of Items

In, Item.h, make another class `MapOfItems`.  You need to define this *after the Item* class.  It needs to have:

- a private member variable that stores a vector of `Item's
- a public function 'addItem' for adding an item to the end of this vector
- a public function 'size()' for returning the size of this vector

Note that where relevant, these should use `const`.


# Part (iii): Taking a tour of the Map

For this part of the assignment, you will implement a greedy algorithm that finds an order in which to visit the Items, allowing for a walking speed between them, and during the times at which they are available (i.e. from a given number of seconds past the hour, until 15 minutes after).

It should be in a class function called `getTour`, implemented within the MapOfItems class.  It should take a walking speed as an argument.  The tour should take no longer than 3600 seconds; that is, the last item you visit, must be visited before 3600.  It should return the tour as a `vector` of `Item`s.

The algorithm specification is as follows:

- The tour must finish before time 3600.
- The tour must start at the Item that is available first, at the time it becomes available.  For instance, if there are five items on the map, available from times 3,10,14,16,18, the item at time 3 would be visited first, at time 3.  (That is, the current time is 3.)
- Then, repeatedly:
  - For each Item *I* that hasn't been visited yet, 
    - Calculate the time that it would take to walk from the previous Item visited, to *I* (using the distance between them, and the walking speed).  This time, plus the current time, is the time that *I* would be visited -- if we went there next.  This time is denoted *visit(I)*.
    - If *visit(I)* is too late (more than fifteen minutes after the item appears), we can't visit that Item
    - If it's too early (before the time at which the item appears), we would need to wait at *I* until it appeared.  This is okay. but we would set *visit(I)* to the time at which *I* appears.
  - The next item to visit is then the one with the smallest *visit(I)*: add this to the tour, and set the current time to *visit(I)*..
  - Or, if we are too late for all the remaining Items, the tour has finished.  (Yes, it might not be able to visit all the items.)
- The function then returns the tour


To test your implementation, use MapOfItemsTest.cpp.  To compile to an executable `MapOfItemsTest`:

`g++ -std=c++11 -o MapOfItemsTest MapOfItemsTest.cpp`  




