open Reprocessing;

let screen_width = 600;
let screen_height = 600;

type fruitState = {
  posX: int,
  posY: int,
  image: imageT,
};

let setup = env => {
  Env.size(~width=screen_width, ~height=screen_height, env);
  {
    posX: 0,
    posY: screen_height,
    image: Draw.loadImage(~filename="assets/apple.png", ~isPixel=true, env),
  };
};

let draw = (state, env) => {
  Draw.clear(env);
  Draw.subImage(
    state.image,
    ~pos=(state.posX, state.posY),
    ~width=300,
    ~height=300,
    ~texPos=(0, 0),
    ~texWidth=551,
    ~texHeight=600,
    env,
  );
  {...state, posY: state.posY - 1};
};

run(~setup, ~draw, ());