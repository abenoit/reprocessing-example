open Reprocessing;

let screenWidth = 600;
let screenHeight = 600;
let gravity = 22.;
let initialJumpForce = (-22.);

type fruitType =
  | Apple
  | Orange
  | Banana
  | Coconut
  | Pineapple
  | Watermelon;

type fruit = {
  posX: int,
  posY: int,
  velX: float,
  velY: float,
  fruitType,
  image: imageT,
};
type assets = {
  apple: imageT,
  orange: imageT,
  banana: imageT,
  coconut: imageT,
  pineapple: imageT,
  watermelon: imageT,
  appleHalf1: imageT,
  orangeHalf1: imageT,
  bananaHalf1: imageT,
  coconutHalf1: imageT,
  pineappleHalf1: imageT,
  watermelonHalf1: imageT,
  appleHalf2: imageT,
  orangeHalf2: imageT,
  bananaHalf2: imageT,
  coconutHalf2: imageT,
  pineappleHalf2: imageT,
  watermelonHalf2: imageT,
};

type state = {
  fruits: list(fruit),
  cutFruits: list(fruit),
  timeElapsed: float,
  fruitList: list(imageT),
  assets,
};

let generateCutFruit = (assets, fruit) => {
  let firstHalf =
    switch (fruit.fruitType) {
    | Apple => assets.appleHalf1
    | Orange => assets.orangeHalf1
    | Banana => assets.bananaHalf1
    | Coconut => assets.coconutHalf1
    | Pineapple => assets.pineappleHalf1
    | Watermelon => assets.watermelonHalf1
    };
  let secondHalf =
    switch (fruit.fruitType) {
    | Apple => assets.appleHalf2
    | Orange => assets.orangeHalf2
    | Banana => assets.bananaHalf2
    | Coconut => assets.coconutHalf2
    | Pineapple => assets.pineappleHalf2
    | Watermelon => assets.watermelonHalf2
    };

  [
    {
      ...fruit,
      posX: fruit.posX + Random.int(5) - 10,
      posY: fruit.posY + Random.int(5) - 10,
      velX: fruit.velX +. Random.float(5.) -. 10.,
      velY: fruit.velY +. Random.float(5.) -. 10.,
      image: firstHalf,
    },
    {
      ...fruit,
      posX: fruit.posX + Random.int(5) - 10,
      posY: fruit.posY + Random.int(5) - 10,
      velX: fruit.velX +. Random.float(5.) -. 10.,
      velY: fruit.velY +. Random.float(5.) -. 10.,
      image: secondHalf,
    },
  ];
};

let loadImage = (env, name) =>
  Draw.loadImage(~filename="assets/" ++ name ++ ".png", ~isPixel=true, env);

let loadAssets = env => {
  apple: loadImage(env, "apple"),
  orange: loadImage(env, "apple"),
  banana: loadImage(env, "apple"),
  coconut: loadImage(env, "apple"),
  pineapple: loadImage(env, "apple"),
  watermelon: loadImage(env, "apple"),
  appleHalf1: loadImage(env, "apple_half_1"),
  orangeHalf1: loadImage(env, "orange_half_1"),
  bananaHalf1: loadImage(env, "banana_half_1"),
  coconutHalf1: loadImage(env, "coconut_half_1"),
  pineappleHalf1: loadImage(env, "pineapple_half_1"),
  watermelonHalf1: loadImage(env, "watermelon_half_1"),
  appleHalf2: loadImage(env, "apple_half_2"),
  orangeHalf2: loadImage(env, "orange_half_2"),
  bananaHalf2: loadImage(env, "banana_half_2"),
  coconutHalf2: loadImage(env, "coconut_half_2"),
  pineappleHalf2: loadImage(env, "pineapple_half_2"),
  watermelonHalf2: loadImage(env, "watermelon_half_2"),
};

let getImageForFruitType = (assets, fruitType) =>
  switch (fruitType) {
  | Apple => assets.apple
  | Orange => assets.orange
  | Banana => assets.banana
  | Coconut => assets.coconut
  | Pineapple => assets.pineapple
  | Watermelon => assets.watermelon
  };

let setup = env => {
  Env.size(~width=screenWidth, ~height=screenHeight, env);
  {
    assets: loadAssets(env),
    fruitList: [
      Draw.loadImage(~filename="assets/apple.png", ~isPixel=true, env),
      Draw.loadImage(~filename="assets/orange.png", ~isPixel=true, env),
      Draw.loadImage(~filename="assets/banana.png", ~isPixel=true, env),
      Draw.loadImage(~filename="assets/coconut.png", ~isPixel=true, env),
      Draw.loadImage(~filename="assets/pineapple.png", ~isPixel=true, env),
      Draw.loadImage(~filename="assets/watermelon.png", ~isPixel=true, env),
    ],
    fruits: [],
    cutFruits: [],
    timeElapsed: 0.,
  };
};

let generateFruitType = () => {
  let allFruitTypes = [Apple, Orange, Banana, Coconut, Pineapple, Watermelon];
  List.nth(allFruitTypes, Random.int(allFruitTypes |> List.length));
};

let generateFruit = assets => {
  let fruitType = generateFruitType();

  {
    velY: initialJumpForce,
    velX: Random.float(10.) -. 5.,
    posX: Random.int(screenWidth),
    posY: screenHeight,
    fruitType,
    image: getImageForFruitType(assets, fruitType),
  };
};

let updateFruit = (deltaTime, fruitState) => {
  ...fruitState,
  posX: fruitState.posX + int_of_float(fruitState.velX),
  posY: fruitState.posY + int_of_float(fruitState.velY),
  velY: fruitState.velY +. gravity *. deltaTime,
};

let updateFruits = (fruits, deltaTime) => {
  List.map(updateFruit(deltaTime), fruits);
};

let draw = (state, env) => {
  let deltaTime = Env.deltaTime(env);
  Draw.clear(env);
  let mousePos = Env.mouse(env);
  let fruits = updateFruits(state.fruits, deltaTime);
  let cutFruits = updateFruits(state.cutFruits, deltaTime);
  fruits
  |> List.iter(fruitState =>
       Draw.subImage(
         fruitState.image,
         ~pos=(fruitState.posX, fruitState.posY),
         ~width=100,
         ~height=100,
         ~texPos=(0, 0),
         ~texWidth=800,
         ~texHeight=800,
         env,
       )
     );
  cutFruits
  |> List.iter(fruitState =>
       Draw.subImage(
         fruitState.image,
         ~pos=(fruitState.posX, fruitState.posY),
         ~width=100,
         ~height=100,
         ~texPos=(0, 0),
         ~texWidth=800,
         ~texHeight=800,
         env,
       )
     );
  {
    ...state,
    timeElapsed: state.timeElapsed +. deltaTime,
    fruits:
      Random.float(1.) > 0.99
        ? [generateFruit(state.assets), ...fruits] : fruits,
    cutFruits:
      Random.float(1.) > 0.80
        ? List.append(
            cutFruits,
            generateCutFruit(state.assets, generateFruit(state.assets)),
          )
        : cutFruits,
  };
};

run(~setup, ~draw, ());