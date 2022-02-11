/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 * stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 *
 * **Hint**: think recursively!
 *
 * @note You may modify the stack as long as you restore it to its original
 * values.
 *
 * @note You may use only two local variables of type T in your function.
 * Note that this function is templatized on the stack's type, so stacks of
 * objects overloading the + operator can be summed.
 *
 * @note We are using the Standard Template Library (STL) stack in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param s A stack holding values to sum.
 * @return  The sum of all the elements in the stack, leaving the original
 *          stack in the same state (unchanged).
 */
template <typename T>
T sum(stack<T>& s)
{
    if(s.empty()) {return 0;}
    
    // Your code here
    decltype(s.top()) x = s.top();
    s.pop();
    decltype(sum(s)) n = sum(s);
    s.push(x);
    return n + x;
     // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of square bracket characters, [, ], and other
 * characters. This function will return true if and only if the square bracket
 * characters in the given string are balanced. For this to be true, all
 * brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is
 * balanced, "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is
 * balanced.
 *
 * For this function, you may only create a single local variable of type
 * `stack<char>`! No other stack or queue local objects may be declared. Note
 * that you may still declare and use other local variables of primitive types.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return      Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{
    int l = 0;
    int r = 0;
    stack<char> output;
    while(input.empty() == false){
        if(input.front() == '[') {l++;}
        if(input.front() == ']') {r++;}
        if(r > l) {return false;}
        input.pop();
    }
    if ( l == r ) {return true;}
    else{return  false;}
    // @TODO: Make less optimistic
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 *
 * **Hint**: You'll want to make a local stack variable.
 *
 * @note Any "leftover" numbers should be handled as if their block was
 * complete.
 *
 * @note We are using the Standard Template Library (STL) queue in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param q A queue of items to be scrambled
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;
    queue<T> q2;
    // optional: queue<T> q2;

    for(int i = 0; q.empty() != true; i++){
        if (i%2 == 0){
           for(int j = i;( j > 0) && (q.empty() != true); j-- ) {
                s.push(q.front());
                q.pop();
            }
            while(s.empty() != true){
                q2.push(s.top());
                s.pop();
            }
        }
        if (i%2 == 1){
            for(int j = i;( j > 0) && (q.empty() != true); j--){
                q2.push(q.front());
                q.pop();
            }
        }  
    }  
    while(q2.empty() != true) {
        q.push(q2.front());
        q2.pop();
    }
    
 }
        
    

    // Your code here

}   