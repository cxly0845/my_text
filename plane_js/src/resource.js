var res = {
    HelloWorld_png : "res/HelloWorld.png",
    SpriteFrame_Cache : "res/AirplaneResource/ui/shoot_background.plist",
    Game_star : "res/AirplaneResource/game_start.png",
    Shoot_png : "res/AirplaneResource/ui/shoot.plist",
    game_music : "res/AirplaneResource/sound/game_music.mp3",
    game_bullet : "res/AirplaneResource/sound/bullet.mp3",
    game_button : "res/AirplaneResource/sound/button.mp3",
    lable   :   "res/AirplaneResource/font/font.fnt",
    enemy1_down : "res/AirplaneResource/sound/enemy1_down.mp3",
    enemy2_down : "res/AirplaneResource/sound/enemy2_down.mp3",
    enemy3_down : "res/AirplaneResource/sound/enemy3_down.mp3",
    game_over  : "res/AirplaneResource/sound/game_over.mp3",
    big_spaceship : "res/AirplaneResource/sound/big_spaceship_flying.mp3",
    Game_reagain : "res/AirplaneResource/game_Reagain.png",

};

var g_resources = [];
for (var i in res) {
    g_resources.push(res[i]);
}
