open Reprocessing;

let screen_width = 600;
let screen_height = 600;
let gravity = 22.;
let initial_jump_force = -22.;

type fruitState = {
  posX: int,
  posY: int,
  velX: float,
  velY: float,
  image: imageT,
};

type state = {
  fruits: list(fruitState),
  timeElapsed: float,
  fruitList: list(imageT)
}
/* Draw.loadImage(~filename="assets/apple.png", ~isPixel=true, env), */
let setup = env => {
  Env.size(~width=screen_width, ~height=screen_height, env);
  {
    fruitList: [
      Draw.loadImage(~filename="assets/apple.png", ~isPixel=true, env),
      Draw.loadImage(~filename="assets/orange.png", ~isPixel=true, env),
      Draw.loadImage(~filename="assets/banana.png", ~isPixel=true, env),
      Draw.loadImage(~filename="assets/coconut.png", ~isPixel=true, env),
      Draw.loadImage(~filename="assets/pineapple.png", ~isPixel=true, env),
      Draw.loadImage(~filename="assets/watermelon.png", ~isPixel=true, env),
    ],
    fruits: [],
    timeElapsed: 0.
  };
};

let generateFruit = (fruitList, env) => {
  velY: initial_jump_force,
  velX: Random.float(10.) -. 5.,
  posX: Random.int(screen_width),
  posY: screen_height,
  image: List.nth(fruitList, Random.int(fruitList |> List.length))
}

let updateFruit = (deltaTime, fruitState) => {
    ...fruitState,
    posX: fruitState.posX + int_of_float(fruitState.velX),
    posY: fruitState.posY + int_of_float(fruitState.velY),
    velY: fruitState.velY +. gravity *. deltaTime
}

let updateFruits = (fruits, deltaTime) => {
  List.map(updateFruit(deltaTime), fruits)
}

let draw = (state, env) => {
  let deltaTime = Env.deltaTime(env);
  Draw.clear(env);
  let fruits = updateFruits(state.fruits, deltaTime);
  fruits |> List.iter(fruitState =>
    Draw.subImage(
      fruitState.image,
      ~pos=(fruitState.posX, fruitState.posY),
      ~width=100,
      ~height=100,
      ~texPos=(0, 0),
      ~texWidth=800,
      ~texHeight=800,
      env,
    ));
  
  /* print_endline(string_of_int(int_of_float(state.timeElapsed *. 1000.) mod 2000)); */
  {
    ...state,
    timeElapsed: state.timeElapsed +. deltaTime,
    fruits: int_of_float(state.timeElapsed *. 1000.) mod 2000 > 1900 ? [generateFruit(state.fruitList, env), ...fruits] : fruits,
  }
};

run(~setup, ~draw, ());