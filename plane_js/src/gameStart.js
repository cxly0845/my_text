//游戏开始画面场景
var GameStartLayer = cc.Layer.extend({

    ctor : function (){
        this._super();

        var size = cc.winSize;

        cc.spriteFrameCache.addSpriteFrames(res.SpriteFrame_Cache);
        cc.spriteFrameCache.addSpriteFrames(res.Shoot_png);

        var sf = cc.spriteFrameCache.getSpriteFrame("background.png");
        var bjSprite = cc.Sprite.create(sf);
        bjSprite.attr({
            x: size.width / 2,
            y: size.height / 2
        });
        this.addChild(bjSprite);

        sf = cc.spriteFrameCache.getSpriteFrame("shoot_copyright.png");
        var shoot_copyright = cc.Sprite.create(sf);
        shoot_copyright.attr({
            x : size.width / 2,
            y : size.height / 2 + 200
        });
        this.addChild(shoot_copyright);

        sf = cc.spriteFrameCache.getSpriteFrame("game_loading1.png");
        var game_loading1 = cc.Sprite.create(sf);
        game_loading1.attr({
            x : size.width / 2,
            y : size.height / 2 - 50
        });
        this.addChild(game_loading1);

        var animation = new cc.Animation();
        for(var i = 1; i < 5; i++) {
            var game_string = "game_loading" + i + ".png";
            animation.addSpriteFrame(game_string);
        }
        animation.setDelayPerUnit(0.35);
        var animate = new cc.Animate(animation);
        game_loading1.runAction(new cc.RepeatForever(animate));

        var game_start = new cc.MenuItemImage(res.Game_star,res.Game_star,function() {
            var transition = new cc.TransitionPageTurn(1.5,new GameScene(),false);
            var audio = cc.audioEngine;
            audio.playEffect(res.game_button,false);
            cc.director.runScene(transition);
        },this);
        game_start.x = size.width / 2;
        game_start.y = size.height / 2 - 200;

        var game_start_menu = new cc.Menu(game_start);
        game_start_menu.x = 0;
        game_start_menu.y = 0;
        this.addChild(game_start_menu);

        return true;
    }

});

var GameStartScene = cc.Scene.extend({
    ctor : function(){
        this._super();
        var layer = new GameStartLayer();
        this.addChild(layer);
    }
});