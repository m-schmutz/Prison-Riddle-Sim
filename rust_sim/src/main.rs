// use rand::seq::SliceRandom;
// use std::collections::HashMap;
use std::io;
// use num_cpus;


fn get_num_trials() -> usize {
    //  value that we are returning
    let mut trials: usize = Default::default();

    // variable used to store input from user
    let mut input = String::new();
        
    // loop until a valid input is given
    loop {
        // prompt the user for how many trials they want to run
        println!("Enter the number of trials that you want to simulate: ");

        // read input
        io::stdin().read_line(&mut input).expect("ERROR: Failed to read input.");

        // match an whether the input can me 
        match input.trim().parse::<usize>(){

            // case for valid number given
            Ok(valid_number) => {
                // set the number of trials to the valid number 
                // given by the user
                trials = valid_number;
                break;
            }

            // case for errir
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


fn main() {
    
    let trials = get_num_trials();

    println!("Running {} trials", trials);

}
