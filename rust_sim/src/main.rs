use rand::seq::SliceRandom;
use std::collections::HashSet;
use std::io;

/******************************************************************
This function takes in a vector representing the boxes and a
hashset that is the boxes that have already been visited

This returns an i8 that is the length of the chain
The highest value that this function will return is 51 
as at that point finding the rest of the chain is redundant 
******************************************************************/
fn discover_chain(boxes: &Vec<i8>, index: i8, visited_boxes: &mut HashSet<i8>) -> i8 {
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


/******************************************************************
This function takes in a vector representing the boxes and returns
true if the prisoners will win the game or false if they will not
******************************************************************/
fn check_shuffle(boxes: Vec<i8>) -> bool {
    // create hashset to track which boxes have already been visited
    let mut visited_boxes: HashSet<i8> = HashSet::new();

    // loop through each of the boxes
    for index in 0..50{
        
        // check if the box is already been visited
        // if it has been found, move to next iteration 
        if visited_boxes.contains(&(index as i8)){
            continue;
        }

        // check if the chain is longer than 50
        // return false if it is as the prisoners will fail
        if discover_chain(&boxes, index as i8, &mut visited_boxes) > 50 {
            return false;
        }
    }

    // return true if all chains are shorter than 50
    return true;
}


/******************************************************************
This function gets input from the user and returns a Result
that is either a u32 or the invalid string that the user entered
******************************************************************/
fn get_input() -> Result<u32, String> {
    // prompt the user
    println!("Enter the number of trials that you want to simulate");
    
    // create new string
    let mut input = String::new();

    // read input and handle possible error
    io::stdin().read_line(&mut input)
        .expect("Failed to read input");

    // return Result that is either the u32 number
    // or the input as a string if it is invalid
    match input.trim().parse() {
        Ok(trials) => Ok(trials),
        Err(_) => Err(input),
    }
}


/******************************************************************
This function returns a u32 after prompting the user for how many 
trials that they want to simulate. This function handles bad input 
and will not return until valid input is given.
******************************************************************/
fn get_num_trials() -> u32 {
    // variable to store the number of trials that the user
    // wants to simulate
    let mut trials: u32 = Default::default();

    // loop until valid input is given
    while true {
        // get user input
        let input = get_input();

        // use match to handle bad input
        match input {
            // if the input is a valid u32, set trials to input
            // and break the loop
            Ok(input) => {
                trials = input;
                break;
            }

            // otherwise print error message and loop again
            Err(input) => {
                println!("Error: \'{}\' is not a valid u32", input.trim())
            }
        }
    }

    // return the valid input
    return trials;
}




fn main() {

    let trials = get_num_trials();

    println!("Simulating {} trials", trials);
    
}




    // //let boxes: Vec<i8> = (0..100).collect();
    // let boxes: Vec<i8> = (0..10).collect();

    // // make mutable copy of the boxes
    // let mut copy: Vec<i8> = boxes.clone();
    
    // // shuffle the boxes
    // copy.shuffle(&mut rand::thread_rng());

    // println!("copy = {:?}", copy);

    // let result = check_shuffle(copy);

    // println!("result = {}", result);
