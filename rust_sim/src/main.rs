use std::collections::HashMap;
use std::collections::HashSet;
use rand::seq::SliceRandom;
use std::io;
// use num_cpus;

/**********************************************************
 * 
**********************************************************/
fn _get_num_trials() -> usize {
    
    let trials: usize;

    //  loop until valid input
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
    let boxes: HashMap<usize, usize> = randomized.iter().enumerate().map(|(i, num)| (i, *num)).collect::<HashMap<usize, usize>>();

    // return the hashmap
    return boxes;
}


fn find_chain(boxes: &mut HashMap<usize, usize>, box_num: usize) -> bool {
    // get the first number in the chain from the first box
    let mut num: usize = *boxes.get(&box_num).unwrap();

    // length is always at minimum 1
    let mut length: usize = 1;

    // keep track of visited boxes
    let mut visited_boxes: HashSet<usize> = vec![box_num].into_iter().collect();

    // while the chain length is 50 or less 
    // and the chain is not complete
    while (length < 51) && (num != box_num) {
        // add new box to visited boxes
        visited_boxes.insert(num);

        // update num and length
        length += 1;
        num = *boxes.get(&num).unwrap();
    }

    // remove boxes that have been visited
    boxes.retain(|&key, _ | !visited_boxes.contains(&key));

    // return the success of the trial
    return length < 51;
}


fn run_trial() -> bool {
    // create a new shuffle of boxes for this trial
    let mut boxes: HashMap<usize, usize> = shuffle_boxes();

    // iterate through all the box numbers
    for box_num in 1..100 {

        // skip this iteration if the box number is already been
        // discovered in another chain
        if boxes.contains_key(&box_num) {

            // find chain 
            // return false if the chain is longer than 50
            if !find_chain(&mut boxes, box_num) {
                return false;
            }
            
            // check if there are 50 or less boxes left
            // in this case, the game is winning as the chains 
            // left are <= 50
            if boxes.len() < 51 {
                break;
            }
        }
    }

    // return winning game
    return true;
}


fn main() {
    // get the number of trials that the user wants to simulate
    // let trials: usize = get_num_trials();
    // println!("Running {} trials", trials);

    run_trial();
    
}