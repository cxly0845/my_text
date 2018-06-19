
var HelloWorldLayer = cc.Layer.extend({
    sprite:null,
    ctor:function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        /////////////////////////////
        // 2. add a menu item with "X" image, which is clicked to quit the program
        //    you may modify it.
        // ask the window size
        var size = cc.winSize;

        /////////////////////////////
        // 3. add your codes below...
        // add a label shows "Hello World"
        // create and initialize a label
        var helloLabel = new cc.LabelTTF("Hello World", "Arial", 38);
        // position the label on the center of the screen
        helloLabel.x = size.width / 2;
        helloLabel.y = size.height / 2 + 200;
        // add the label as a child to this layer
        this.addChild(helloLabel, 5);

        // add "HelloWorld" splash screen"
        this.sprite = new cc.Sprite(res.HelloWorld_png);
        this.sprite.attr({
            x: size.width / 2,
            y: size.height / 2
        });
        this.addChild(this.sprite, 0);

        var bjsprite = cc.Sprite.create(res.bjSprite);
        bjsprite.attr({
            x: size.width / 2 - 250,
            y: size.height / 2 + 100
        });
        this.addChild(bjsprite,3);

        return true;
    },
    onEnter:function(){
        this._super();
        var helloLabele1 = new cc.LabelTTF("开始游戏","Arial",50);
        var size = cc.winSize;
        helloLabele1.x = size.width / 2;
        helloLabele1.y = size.height/2-200;
        this.addChild(helloLabele1);
    }
});

var HelloWorldScene = cc.Scene.extend({
    ctor:function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});




