open Reprocessing;

let screen_width = 600;
let screen_height = 600;
let gravity = 22.;
let initial_jump_force = -22.;

type fruitType = | Apple | Orange | Banana | Coconut | Pineapple | Watermelon

type fruit = {
  posX: int,
  posY: int,
  velX: float,
  velY: float,
  fruitType,
  image: imageT
};

type cutFruitList = {
  apple1: imageT,
  orange1: imageT,
  banana1: imageT,
  coconut1: imageT,
  pineapple1: imageT,
  watermelon1: imageT,
  apple2: imageT,
  orange2: imageT,
  banana2: imageT,
  coconut2: imageT,
  pineapple2: imageT,
  watermelon2: imageT
}

type state = {
  fruits: list(fruit),
  cutFruits: list(fruit),
  timeElapsed: float,
  fruitList: list(imageT),
  cutFruitList
}

let generateCutFruit = (cutFruitList, fruit) => {
  let firstHalf = switch fruit.fruitType {
  | Apple => cutFruitList.apple1
  | Orange => cutFruitList.orange1
  | Banana => cutFruitList.banana1
  | Coconut => cutFruitList.coconut1
  | Pineapple => cutFruitList.pineapple1
  | Watermelon => cutFruitList.watermelon1
  };
  let secondHalf = switch fruit.fruitType {
  | Apple => cutFruitList.apple2
  | Orange => cutFruitList.orange2
  | Banana => cutFruitList.banana2
  | Coconut => cutFruitList.coconut2
  | Pineapple => cutFruitList.pineapple2
  | Watermelon => cutFruitList.watermelon2
  };

  [
    {
      ...fruit,
      posX: fruit.posX + 5,
      image: firstHalf
    },
    {
      ...fruit,
      posX: fruit.posX - 5,
      image: secondHalf
    }
  ]
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
    cutFruitList: {
      apple1: Draw.loadImage(~filename="assets/apple_half_1.png", ~isPixel=true, env),
      orange1: Draw.loadImage(~filename="assets/orange_half_1.png", ~isPixel=true, env),
      banana1: Draw.loadImage(~filename="assets/banana_half_1.png", ~isPixel=true, env),
      coconut1: Draw.loadImage(~filename="assets/coconut_half_1.png", ~isPixel=true, env),
      pineapple1: Draw.loadImage(~filename="assets/pineapple_half_1.png", ~isPixel=true, env),
      watermelon1: Draw.loadImage(~filename="assets/watermelon_half_1.png", ~isPixel=true, env),
      apple2: Draw.loadImage(~filename="assets/apple_half_2.png", ~isPixel=true, env),
      orange2: Draw.loadImage(~filename="assets/orange_half_2.png", ~isPixel=true, env),
      banana2: Draw.loadImage(~filename="assets/banana_half_2.png", ~isPixel=true, env),
      coconut2: Draw.loadImage(~filename="assets/coconut_half_2.png", ~isPixel=true, env),
      pineapple2: Draw.loadImage(~filename="assets/pineapple_half_2.png", ~isPixel=true, env),
      watermelon2: Draw.loadImage(~filename="assets/watermelon_half_2.png", ~isPixel=true, env),
    },
    fruits: [],
    cutFruits: [],
    timeElapsed: 0.
  };
};

let generateFruit = (fruitList, env) => {
  velY: initial_jump_force,
  velX: Random.float(10.) -. 5.,
  posX: Random.int(screen_width),
  posY: screen_height,
  fruitType: Apple,
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
  let mousePos = Env.mouse(env);
  let fruits = updateFruits(state.fruits, deltaTime);
  let cutFruits = updateFruits(state.cutFruits, deltaTime);
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
  cutFruits |> List.iter(fruitState =>
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
  {
    ...state,
    timeElapsed: state.timeElapsed +. deltaTime,
    fruits: (Random.float(1.) > 0.99) ? [generateFruit(state.fruitList, env), ...fruits] : fruits,
    cutFruits: (Random.float(1.) > 0.80) ? List.append(cutFruits, generateCutFruit(state.cutFruitList, generateFruit(state.fruitList, env))) : cutFruits,
  }
};

run(~setup, ~draw, ());