//碰撞检测层

var Collision = cc.Layer.extend({
    myHero : null,
    bulletLayer : null,
    enemyLayer : null,
    score   : "000000",
    title2  : null,
    ctor : function(){
        this._super();
        return true;
    },

    onEnter : function(){
        this._super();

        this.myHero = this.getParent().getChildByTag(1);
        cc.log(this.myHero.name);
        this.bulletLayer = this.getParent().getChildByTag(2);
        cc.log(this.bulletLayer.name);
        this.enemyLayer = this.getParent().getChildByTag(3);
        cc.log(this.enemyLayer.name);

        var title1 = new cc.LabelTTF("分数：","Arial", 30);
        title1.x = 250;
        title1.y = 838;
        this.addChild(title1);
        this.title2 = new cc.LabelBMFont(this.score,res.lable);
        this.title2.x = 380;
        this.title2.y = 838;
        this.addChild(this.title2);

        this.scheduleUpdate();

    },

    update : function(dt){
        this.bulletCollision();
        this.myHeroCollision();
    },

    bulletCollision : function(){           //子弹碰撞敌机检测
        for(var i = 0; i < this.bulletLayer.bulletManager.length; i++){
            var bullet = this.bulletLayer.bulletManager[i];
            for(var j = 0; j < this.enemyLayer.EnemytManager.length; j++){
                var enemy = this.enemyLayer.EnemytManager[j];
                var rect1 = bullet.getBoundingBox();
                var rect2 = enemy.getBoundingBox();
                if(cc.rectIntersectsRect(rect1,rect2)){
                    this.bulletLayer.bulletManager.splice(i,1);
                    //bullet.release();
                    bullet.stopAllActions();
                    bullet.removeFromParent();
                    //cc.log("碰撞检测。。。。。。")
                    enemy.life--;
                    this.myHero.score++;
                    if(enemy.life <= 0){
                        this.enemyLayer.EnemytManager.splice(j,1);
                        //enemy.release();
                        enemy.stopAllActions();
                        this.myHero.score += enemy.score;
                        enemy.explosion();
                    }else{
                        enemy.action_hit();
                    };
                    if(this.myHero.score <10) {
                        this.score = "00000" + this.myHero.score;
                    }else if(this.myHero.score>=10 && this.myHero.score < 99){
                        this.score = "0000" + this.myHero.score;
                    }else if(this.myHero.score >= 100 && this.myHero.score < 999){
                        this.score = "000" + this.myHero.score;
                    }else if(this.myHero.score >= 1000 && this.myHero.score < 9999){
                        this.score = "00" + this.myHero.score;
                    }else if(this.myHero.score >= 10000 && this.myHero.score < 99999){
                        this.score = "0" + this.myHero.score;
                    }else{
                        this.score = this.myHero.score;
                    };
                    this.title2.setString(this.score);
                };

            };
        };

    },

    myHeroCollision : function(){
        for(var i = 0; i < this.enemyLayer.EnemytManager.length; i++){
            var enemy = this.enemyLayer.EnemytManager[i];
            var rect1 = enemy.getBoundingBox();
            var rect2 = this.myHero.getBoundingBox();
            rect1.width -= 25;
            rect1.height -=30;
            rect2.width -= 25;
            rect2.height -=10;
            rect2.y += 20;
            if(cc.rectIntersectsRect(rect1,rect2)){
                this.myHero.MyHeroSprite.stopAllActions();
                this.bulletLayer.stopLaunchBullet1();
                this.bulletLayer.stopLanuchBullet2();
                this.myHero.remove_Listener();
                this.myHero.explosion();
                this.unscheduleUpdate();
            };

        };
    },

    onExit : function(){
        this._super();

        this.unscheduleUpdate();
    }


});