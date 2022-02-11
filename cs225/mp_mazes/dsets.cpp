/* Your code here! */
#include "dsets.h"
//creates num unconnected root nodes at the end of the vector
void DisjointSets::addelements(int num){
    
for(int i = 0; i < num; i++){
    elements.push_back(-1);
}
return;
}
//this function should compress paths and works as described in lecture
int DisjointSets::find(int elem){

if(elements[elem] < 0){return elem;}

else{
    int answer = find(elements[elem]);
    elements[elem] = answer;
    return elements[elem];
}


}

void DisjointSets::setunion(int a, int b){

auto root_a = find(a);
auto root_b = find(b);

if (root_a == root_b) {return;} //don't want to union things in the same set


if(root_a < root_b){
    elements[root_a] = elements[root_a] + elements[root_b];
    elements[root_b] = root_a;
}
else{
    elements[root_b] = elements[root_b] + elements[root_a]; //just flipped a/b
    elements[root_a] = root_b;
}


}

int DisjointSets::size(int elem){
  int temp = find(elem);
  return (-1)*elements[temp];

}