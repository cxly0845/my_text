var Enemy = cc.Sprite.extend({
    layer : null,
    name  : 0,
    score : 0,
    ctor : function(string){
        this._super(string);

        Enemy.id++;
        this.name = Enemy.id;
        this.x = Math.round(Math.random()*481);
        this.y = 850+this.getContentSize().height/2;
        //cc.log(this.getContentSize().height);

        return true;
    },
    onEnter : function(){
        this._super();
        this.layer = this.getParent();

        var action = cc.moveTo(this.layer.EnemySpeed,cc.p(this.x,-this.getContentSize().height/2));
        this.runAction(cc.sequence(action,cc.callFunc(this.deleteEnemy,this)));
    },
    deleteEnemy : function(){
        for(var i = 0; i < this.layer.EnemytManager.length; i++){
            if(this.layer.EnemytManager[i] === this){
                this.layer.EnemytManager.splice(i,1);
                //this.release();
                this.removeFromParent();
                //cc.log(".............我亲爱的老师  张雪芬.............");
            };
        };
    },
    explosion : function(){             //爆炸方法，需要重写,爆炸后接着从父节点中移除

    },
    action_hit : function(){            //受到攻击执行的动作，需重写

    }

});
Enemy.id = 0;

var Enemy1 = Enemy.extend({
    life : 1,       //飞机生命
    ctor : function(){
        this._super("#enemy1.png");
        this.score = 3;
        return true;
    },
    explosion : function(){
        var animation = new cc.Animation();
        for(var i = 1; i < 5; i++){
            var string = "enemy1_down" + i + ".png";
            var sp = cc.spriteFrameCache.getSpriteFrame(string);
            animation.addSpriteFrame(sp);
        };
        animation.setDelayPerUnit(0.15);
        var animate = new cc.Animate(animation);
        cc.audioEngine.playEffect(res.enemy1_down,false);
        this.runAction(cc.sequence(animate,cc.callFunc(function(){
            this.removeFromParent();
        },this)));

    },
});

var Enemy2 = Enemy.extend({
    life : 12,
    ctor : function(){
        this._super("#enemy2.png");
        this.score = 8;
        return true;
    },
    explosion : function(){
        cc.audioEngine.playEffect(res.enemy3_down,false);
        var animation = new cc.Animation();
        for(var i = 1; i < 5; i++){
            var string = "enemy2_down" + i + ".png";
            var sp = cc.spriteFrameCache.getSpriteFrame(string);
            animation.addSpriteFrame(sp);
        };
        animation.setDelayPerUnit(0.2);
        var animate = new cc.Animate(animation);
        this.runAction(cc.sequence(animate,cc.callFunc(function(){
            this.removeFromParent();
        },this)));

    },
    action_hit : function(){
        var animation = new cc.Animation();
        animation.addSpriteFrame(this.getSpriteFrame());
        var sp = cc.spriteFrameCache.getSpriteFrame("enemy2_hit.png");
        animation.addSpriteFrame(sp);
        animation.addSpriteFrame(this.getSpriteFrame());
        animation.setDelayPerUnit(0.02);
        var animate = new cc.Animate(animation);
        this.runAction(animate);
    }
});

var Enemy3 = Enemy.extend({
    life : 20,
    audio_id : 0,
    ctor : function(){
        this._super("#enemy3_n1.png");
        this.score = 15;
        return true;
    },
    onEnter : function(){
        this._super();

        this.audio_id = cc.audioEngine.playEffect(res.big_spaceship,true);
        var animation = new cc.Animation();
        var sp = this.getSpriteFrame();
        animation.addSpriteFrame(sp);
        sp = cc.spriteFrameCache.getSpriteFrame("enemy3_n2.png");
        animation.addSpriteFrame(sp);
        animation.setDelayPerUnit(0.2);
        var animate = new cc.Animate(animation);
        this.runAction(cc.repeatForever(animate));

    },
    explosion : function(){
        cc.audioEngine.stopEffect(this.audio_id);
        cc.audioEngine.playEffect(res.enemy2_down,false);
        var animation = new cc.Animation();
        for(var i = 1; i < 7; i++){
            var string = "enemy3_down" + i + ".png";
            var sp = cc.spriteFrameCache.getSpriteFrame(string);
            animation.addSpriteFrame(sp);
        };
        animation.setDelayPerUnit(0.2);
        var animate = new cc.Animate(animation);
        this.runAction(cc.sequence(animate,cc.callFunc(function(){
            this.removeFromParent();
        },this)));

    },
    action_hit : function(){
        var animation = new cc.Animation();
        animation.addSpriteFrame(this.getSpriteFrame());
        var sp = cc.spriteFrameCache.getSpriteFrame("enemy3_hit.png");
        animation.addSpriteFrame(sp);
        animation.addSpriteFrame(this.getSpriteFrame());
        animation.setDelayPerUnit(0.02);
        var animate = new cc.Animate(animation);
        this.runAction(animate);
    }
});


//敌机管理层
var EnemyLayer = cc.Layer.extend({
    EnemytManager : [],         //敌机管理器
    speed : 1.5,                //敌机出场速度
    EnemySpeed : 8,             //敌机飞行速度
    time  : 0,
    name  : "敌机管理层",
    ctor : function(){
        this._super();

        this.schedule(this.onlodeEnemy,this.speed,cc.RepeatForever,0,"name1");
        this.schedule(this.myUpdate,10,cc.RepeatForever,0,"name2");
        return true;
    },
    onlodeEnemy : function(dt){
        this.time += dt;
        var sum = Math.round(Math.random()*8 + 1);
        if(sum > 3){
            var enemy = new Enemy1;
            this.addChild(enemy);
            this.EnemytManager.push(enemy);
            //this.retain();
        };
        if(sum >= 2 && sum <= 3 && this.time >= 8){
            var enemy = new Enemy2;
            this.addChild(enemy);
            this.EnemytManager.push(enemy);
            //this.retain();
        };
        if(sum === 1 && this.time >= 20){
            var enemy = new Enemy3;
            this.addChild(enemy);
            this.EnemytManager.push(enemy);
            //this.retain();
        };

    },

    onExit : function(){
        this._super();

        this.unscheduleAllCallbacks();
        this.removeAllChildren();
        this.EnemytManager.splice(0,this.EnemytManager.length);
    },

    myUpdate : function(){
        if(this.EnemySpeed > 0){
            this.EnemySpeed -= 0.3;
        };
        if(this.speed > 0.5){
            this.speed -= 0.1;
        }
        cc.log("########敌机速度改变#############");

    }

});