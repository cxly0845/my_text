var GameOver = cc.Layer.extend({

    ctor : function(){
        this._super();

        var size = cc.winSize;
        var sf = cc.spriteFrameCache.getSpriteFrame("background.png");
        var bjSprite = cc.Sprite.create(sf);
        bjSprite.attr({
            x: size.width / 2,
            y: size.height / 2
        });
        this.addChild(bjSprite);

        var regameSprite = new cc.MenuItemImage(res.Game_reagain,res.Game_reagain,function(){
            var transition = new cc.TransitionPageTurn(1.5,new GameScene(),false);
            var audio = cc.audioEngine;
            audio.playEffect(res.game_button,false);
            cc.director.runScene(transition);
        },this);

        regameSprite.x = size.width / 2;
        regameSprite.y = size.height / 2 - 300;
        var menu = new cc.Menu(regameSprite);
        menu.x = 0;
        menu.y = 0;
        this.addChild(menu);


        return true;
    },

});

var GameOverScene = cc.Scene.extend({

    ctor : function(){
        this._super();
        var gameOver = new GameOver();
        this.addChild(gameOver);
        return true;
    }
});