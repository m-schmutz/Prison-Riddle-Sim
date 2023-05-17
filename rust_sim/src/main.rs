use rand::seq::SliceRandom;
use std::collections::HashSet;

/******************************************************************
This function takes in a vector representing the boxes and a
hashset that is the boxes that have already been visited

This returns an i8 that is the length of the chain
The highest value that this function will return is 51 
as at that point finding the rest of the chain is redundant 
******************************************************************/
fn discover_chain(boxes: Vec<i8>, index: i8, visited_boxes: &mut HashSet<i8>) -> i8{
    // track the length of this chain
    // the minimum length of a chain is 1 (a box containing its own number)
    let mut length = 1;

    // store the value of the box that is the start of the chain
    // the index is the box that we are starting our search at
    let start = index;

    // add the start box to the set of visited boxes
    visited_boxes.insert(start);

    // num is the value in the first box
    // it is updated to find the next box in the sequence
    let mut num = boxes[index as usize];

    // while we are not back at the start of the chain
    while num != start && length <= 50{
        // increment the length of the chain
        length += 1;
        
        // add next box number to set of visited boxes
        visited_boxes.insert(num);

        // update the value of num
        // num becomes the value contained in the box of its previous value
        // if num = 5; then its next value becomes the value contained in box 5
        num = boxes[num as usize];
    }

    // return the length of the list
    return length;
}


fn find_chains(boxes: Vec<i8>){
    // create hashset to track which boxes have already been visited
    let mut visited_boxes: HashSet<i8> = HashSet::new();
}







fn main() {
    //let boxes: Vec<i8> = (0..100).collect();
    let boxes: Vec<i8> = (0..10).collect();

    // make mutable copy of the boxes
    let mut copy: Vec<i8> = boxes.clone();
    
    // shuffle the boxes
    copy.shuffle(&mut rand::thread_rng());

    println!("copy = {:?}", copy);
    
    let mut visited_boxes: HashSet<i8> = HashSet::new();

    let result = discover_chain(copy, 0, &mut visited_boxes);

    println!("the result is {}", result);
}
