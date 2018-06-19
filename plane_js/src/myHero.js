//我方飞机类,实现思路：将飞机精灵与节点结合成完整飞机
var MyHero = cc.Node.extend({
    MyHeroSprite : null,
    name : "主角飞机",
    score : 0,
    listener : null,
    id  : 0,

    ctor : function(){
        this._super();

        MyHero.id++;
        this.id = MyHero.id;
        cc.log("英雄飞机的ID是:" + this.id + "   #####################");

        this.setContentSize(cc.size(102,126));
        this.anchorX = 0.5;
        this.anchorY = 0.5;
        this.setTag(1);

        var sf = cc.spriteFrameCache.getSpriteFrame("hero1.png");
        this.MyHeroSprite = new cc.Sprite(sf);
        this.MyHeroSprite.attr({
            x : this.getContentSize().width / 2,
            y : this.getContentSize().height / 2
        });
        this.addChild(this.MyHeroSprite);
        return true;
    },

    onEnter : function(){
        this._super();
        this.MyHeroSprite.runAction(cc.sequence(cc.delayTime(1),cc.blink(2,3),
            cc.callFunc(this.myHeroSprite_jet,this),cc.callFunc(this.touch_Listener,this)));
    },


     myHeroSprite_jet : function(){
        var animation = new cc.Animation();
        animation.addSpriteFrame(this.MyHeroSprite.getSpriteFrame());
        var sf = cc.spriteFrameCache.getSpriteFrame("hero2.png");
        animation.addSpriteFrame(sf);
        animation.setDelayPerUnit(0.08);
        var animate = new cc.Animate(animation);
        this.MyHeroSprite.runAction(cc.repeatForever(animate));
    },

    touch_Listener : function(){
        var myhero  = null;
        this.listener = cc.EventListener.create({
            event : cc.EventListener.TOUCH_ONE_BY_ONE,
            swallowTouches : true,
            onTouchBegan : function(touch,event){
                myhero = event.getCurrentTarget();
                var point = touch.getLocationInView();
                var box = myhero.getBoundingBox();
                if(cc.rectContainsPoint(box,point)) {
                    return true;
                }else {
                    return false;
                };
            },
            onTouchMoved : function(touch,event){
                 var point = touch.getLocationInView();
                 var Previous_point = touch.getPreviousLocationInView();
                 myhero = event.getCurrentTarget();
                 myhero.setPosition(point);
                 if(point.x < Previous_point.x ){       //设置飞机倾斜角度

                 };
                 if(point.x > Previous_point.x ){       //设置飞机倾斜角度

                 };
                 if((myhero.x  <= 3)){
                     myhero.x = 3;
                 }else if(myhero.x  >= 480 -7){
                     myhero.x = 480 -7;
                };
                if((myhero.y - myhero.getContentSize().height/2) <= -50){
                     myhero.y = myhero.getContentSize().height/2 - 50;
                }else if((myhero.y + myhero.getContentSize().height/2) >= 852){
                     myhero.y = 852 - myhero.getContentSize().height/2;
                };
            },
            onTouchEnded : function (touch,event){

            },

        });
        cc.eventManager.addListener(this.listener,this);
    },

    remove_Listener : function(){
        cc.eventManager.removeListener(this.listener);
    },

    explosion : function(){
        cc.audioEngine.playEffect(res.game_over,false);
        var animation = new cc.Animation();
        for(var i = 1; i < 5; i++){
            var name =  "hero_blowup_n" + i + ".png";
            var sp = cc.spriteFrameCache.getSpriteFrame(name);
            animation.addSpriteFrame(sp);
        };
        animation.setDelayPerUnit(0.15);
        var animate = new cc.Animate(animation);
        this.MyHeroSprite.runAction(cc.sequence(animate,cc.callFunc(this.reStart,this)));
    },

    reStart : function(){
        var scene = new GameOverScene();
        cc.director.runScene( new cc.TransitionPageTurn(0.8,scene,true));
    },

    onExit :function(){
        this._super();

        MyHero.id--;
    }

});

MyHero.id = 0;
