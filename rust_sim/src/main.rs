use rand::seq::SliceRandom;

fn main() {

    let boxes: Vec<i8> = (0..100).collect();

    let mut trial: Vec<i8> = boxes.clone();
    trial.shuffle(&mut rand::thread_rng());

    println!("{:?}", trial);

}
