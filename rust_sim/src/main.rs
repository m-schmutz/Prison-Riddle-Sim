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
    let boxes = randomized.iter().enumerate().map(|(i, num)| (i, *num)).collect::<HashMap<usize, usize>>();

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







fn run_trial(boxes: HashMap<usize, usize>) -> bool {

    let mut boxes = 0;


    // to check whether a given shuffle is winning or not
    // we need to check if a chain longer than 50 exists
    for (box_num, number) in boxes.iter(){
        println!("box_num: {} | number: {}", box_num,  number);
    }

    return false;
}



fn main() {
    // get the number of trials that the user wants to simulate
    // let trials: usize = get_num_trials();
    // println!("Running {} trials", trials);

    let boxes: HashMap<usize, usize> = shuffle_boxes();

    run_trial(boxes);
    
}