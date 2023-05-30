use rand::seq::SliceRandom;
use std::collections::HashMap;
use std::hash::Hash;
use std::io;
// use num_cpus;

/**********************************************************
 * 
**********************************************************/
fn _get_num_trials() -> usize {
    
    let trials: usize;

    loop {
        println!("Enter the number of trials that you want to simulate: ");
        
        // get user input
        let mut input: String = String::new();
        io::stdin().read_line(&mut input).expect("ERROR: Failed to read input.");

        // match on valid number 
        match input.trim().parse::<usize>(){

            // case for valid number given
            Ok(valid_number) => {
                trials = valid_number;
                break;
            }

            // case for error
            Err(_) => {
                // print error message and clear the string
                println!("Error: \'{}\' is not a valid number", input.trim());
                input.truncate(0);
            }
        }
    }
    // return the number of trials
    return trials;
}


fn shuffle_boxes() -> HashMap<usize, usize> {
    // shuffle the boxes
    let mut randomized: Vec<usize> = (0..100).collect();
    randomized.shuffle(&mut rand::thread_rng());


    // convert the vector to a hashmap
    let boxes = randomized.iter().enumerate().map(|(i, num)| (i, *num)).collect::<HashMap<usize, usize>>();

    // return the hashmap
    return boxes;
}


fn run_trial(boxes: HashMap<usize, usize>) -> bool {
    // 
    for (box_num, number) in boxes.iter(){
        println!("box_num: {} | number: {}", box_num,  number);
    }

    return false;
}



fn main() {
    // get the number of trials that the user wants to simulate
    // let trials: usize = get_num_trials();
    // println!("Running {} trials", trials);

    let boxes = shuffle_boxes();

    run_trial(boxes);
    
}