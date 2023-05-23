use rand::seq::SliceRandom;
use std::collections::HashMap;
use std::io;
// use num_cpus;

/**********************************************************
 * 
**********************************************************/
fn get_user_num() -> usize {

    let mut num: usize = 0;

    let mut input: String = String::new();
    
    // loop until user supplies a valid number
    loop {
        io::stdin().read_line(&mut input).expect("ERROR: Failed to read input.");

        // match on valid number 
        match input.trim().parse::<usize>(){

            // case for valid number given
            Ok(valid_number) => {
                num = valid_number;
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

    return num;
}


// fn randomize_boxes() -> HashMap<usize, usize> {
fn randomize_boxes() -> Vec<usize> {
    // randomize the box's numbers
    let mut randomized: Vec<usize> = (0..100).collect();
    randomized.shuffle(&mut rand::thread_rng());

    return randomized;
}



fn main() {
    // get the number of trials that the user wants to simulate
    println!("Enter the number of trials you want to simulate:");
    let trials: usize = get_user_num();

    println!("Running {} trials", trials);

    let boxes: Vec<usize> = randomize_boxes();

    println!("Boxes: {:?}", boxes);

}
