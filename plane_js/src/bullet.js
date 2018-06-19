//子弹类,继承Sprite

var BulletSprite = cc.Sprite.extend({
    id : 0,
    speed : 800,
    ctor : function (name){
        this._super(name);
        BulletSprite.id ++;
        this.id = BulletSprite.id;
        return true;
    },

    onEnter : function() {
        this._super();

        var BulletDistanct = 858 - this.y;
        var time = BulletDistanct / this.speed;
        var action = cc.moveTo(time, cc.p(this.x, 858),);  //注明：时间不能是负数
        this.runAction(cc.sequence(action,cc.callFunc(this.deleteBullet,this)));
    },
    deleteBullet : function(){
        var layer = this.getParent();
        var that = this;
        for(var i = 0; i < (layer.bulletManager.length); i++){
            if(layer.bulletManager[i] === that){
                layer.bulletManager.splice(i,1);
                //this.release();
                this.removeFromParent();
                BulletSprite.id--;
            };
        };
    }

});
BulletSprite.id = 0;

//子弹管理层
var BulletLayer = cc.Layer.extend({
    bulletManager : [],    //子弹管理器
    speed : 0.15,          //子弹发射速度
    name  : "子弹管理层",
    ctor : function(){
        this._super();
        this.x = 0;
        this.y = 0;

        this.setTag(2);
        return true;
    },
    onEnter : function(){
        this._super();
        this.launchBullet1();
        //this.launchBullet2();
    },
    launchBullet1 : function(){
        this.schedule(this.createBullet1,this.speed,cc.RepeatForever,0,null);
    },
    launchBullet2 : function(){
        this.schedule(this.createBullet2,this.speed,cc.RepeatForever,0,null);
    },

    createBullet1 : function(){
        var bullet = new BulletSprite("#bullet2.png");
        //bullet.retain();
        this.bulletManager.push(bullet);
        var myHero = this.getParent().MyHero;
        bullet.x = myHero.x + 2;
        bullet.y = myHero.y + myHero.getContentSize().height / 2 + 6;
        var audio = cc.audioEngine;
        audio.playEffect(res.game_bullet,false);
        this.addChild(bullet);
    },
    createBullet2 : function(){
        var bullet1 = new BulletSprite("#bullet1.png");
        var bullet2 = new BulletSprite("#bullet1.png");
        this.bulletManager.push(bullet1);
        this.bulletManager.push(bullet2);
        var myHero = this.getParent().MyHero;
        bullet1.x = myHero.x + 33;
        bullet1.y = myHero.y + 20;
        bullet2.x = myHero.x - 33;
        bullet2.y = myHero.y + 20;
        var audio = cc.audioEngine;
        audio.playEffect(res.game_bullet,false);
        this.addChild(bullet1);
        this.addChild(bullet2);
    },
    stopLaunchBullet1 : function(){
        this.unschedule(this.launchBullet1);
    },
    stopLanuchBullet2 : function(){
        this.unschedule(this.createBullet2);
    },

    onExit : function(){
        this._super();

        this.unscheduleAllCallbacks();
        this.removeAllChildren();
        this.bulletManager.splice(0,this.bulletManager.length);
    }

});