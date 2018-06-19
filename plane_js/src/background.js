//背景层，实现背景移动
var BackgroundLayer = cc.Layer.extend({
    gameBackground1 : null,
    gameBackground2 : null,
    size : null,

    ctor : function(){
        this._super();

        this.size = cc.winSize;

        var sf = cc.spriteFrameCache.getSpriteFrame("background.png");
        this.gameBackground1 = new cc.Sprite(sf);
        this.gameBackground1.attr({
            x : this.size.width / 2,
            y : this.size.height / 2
        });
        this.addChild(this.gameBackground1);

        this.gameBackground2 = new cc.Sprite(sf);
        this.gameBackground2.attr({
            x : this.size.width / 2,
            y : this.size.height - 2
        });
        this.addChild(this.gameBackground2);

        this.scheduleUpdate();
        return true;
    },

    update : function(dt){
        if(this.gameBackground1.y <=  -this.size.height/2 +2){
            this.gameBackground1.y = this.size.height / 2;
        };
       this.gameBackground1.y  -= 2;
       this.gameBackground2.y = this.gameBackground1.y +  this.size.height -2;
    },


});