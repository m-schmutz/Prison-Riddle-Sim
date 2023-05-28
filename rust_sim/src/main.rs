// use rand::seq::SliceRandom;
use std::collections::HashMap;
use std::io;
// use num_cpus;

/**********************************************************
 * 
**********************************************************/
fn get_num_trials() -> usize {
    
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


fn run_trial(boxes: HashMap<i8, i8>) -> bool {
    


    return false;
}



fn main() {
    // get the number of trials that the user wants to simulate
    let trials: usize = get_num_trials();

    println!("Running {} trials", trials);

}