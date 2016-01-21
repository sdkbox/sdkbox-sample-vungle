
var HelloWorldLayer = cc.Layer.extend({
    sprite:null,
    ctor:function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        cc.log("Sample Startup")

        this.createTestMenu();

        var winsize = cc.winSize;

        var logo = new cc.Sprite("res/Logo.png");
        var logoSize = logo.getContentSize();
        logo.x = logoSize.width / 2;
        logo.y = winsize.height - logoSize.height / 2;
        this.addChild(logo);

        var quit = new cc.MenuItemLabel(new cc.LabelTTF("QUIT", "sans", 32), function() {
            cc.log("QUIT");
        });
        var menu = new cc.Menu(quit);
        var size = quit.getContentSize();
        menu.x = winsize.width - size.width / 2 - 16;
        menu.y = size.height / 2 + 16;
        this.addChild(menu);

        return true;
    },

    createTestMenu:function() {
        cc.MenuItemFont.setFontName("sans");
        var size = cc.Director.getInstance().getWinSize();

        // init plugin
        sdkbox.PluginVungle.init();
        sdkbox.PluginVungle.setListener({
            onVungleCacheAvailable : function() {
                cc.log("onVungleCacheAvailable");
            },
            onVungleStarted : function() {
                cc.log("onVungleStarted");
            },
            onVungleFinished : function() {
                cc.log("onVungleFinished");
            },
            onVungleAdViewed : function(isComplete) {
                cc.log("onVungleAdViewed" + isComplete.toString());
            },
            onVungleAdReward : function(name) {
                cc.log("reward received:" + name);
            }
        })

        var menu = new cc.Menu(
            new cc.MenuItemFont("show video", function() {
                sdkbox.PluginVungle.show("video");
                cc.log("sdkbox.PluginVungle.show(\"video\")");
            }),
            new cc.MenuItemFont("show reward", function() {
                sdkbox.PluginVungle.show("reward");
                cc.log("sdkbox.PluginVungle.show(\"reward\")");
            })
        );

        menu.alignItemsVerticallyWithPadding(5);
        menu.x = size.width/2;
        menu.y = size.height/2;
        this.addChild(menu);
    }
});

var HelloWorldScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});

