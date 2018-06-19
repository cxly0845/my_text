//游戏运行场景
var GameLayer = cc.Layer.extend({
    MyHero : null,
    ctor : function(){
        this._super();

        var size  = cc.winSize;

        var backgroundLayer = new BackgroundLayer();
        this.addChild(backgroundLayer);

        this.MyHero = new MyHero();
        this.MyHero.attr({
            x : size.width / 2,
            y : size.height / 2 -350
         });
        this.addChild(this.MyHero,0,1);

        //播放背景音乐
        var audio = cc.audioEngine;
        audio.playMusic(res.game_music,true);
        audio.setMusicVolume(0.5);

        this.scheduleOnce(this.addBulletLayer,3);
        this.scheduleOnce(this.addEnemyLayer,3);

        return true;
    },

    addBulletLayer : function(){
        this.addChild(new BulletLayer(),0,2);
    },
    addEnemyLayer : function(){
        this.addChild(new EnemyLayer(),0,3);
        var collision = new Collision();
        this.addChild(collision);
    }


});

var GameScene = cc.Scene.extend({
    ctor : function(){
        this._super();
        var gameLayer = new GameLayer();
        this.addChild(gameLayer);

        return true;
    },

});