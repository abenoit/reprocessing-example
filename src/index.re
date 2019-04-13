open Reprocessing;

let screen_width = 600;
let screen_height = 600;
let gravity = 1.;
let initial_jump_force = -40.;

type fruitState = {
  posX: int,
  posY: int,
  velX: float,
  velY: float,
  image: imageT,
};

let setup = env => {
  Env.size(~width=screen_width, ~height=screen_height, env);
  {
    posX: 0,
    velY: initial_jump_force,
    velX: 0.,
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
  print_endline(string_of_int(state.posY));
  {...state, posY: state.posY + int_of_float(state.velY), velY: state.velY +. gravity};
};

run(~setup, ~draw, ());