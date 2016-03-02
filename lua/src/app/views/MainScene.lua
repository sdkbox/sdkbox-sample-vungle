
local MainScene = class("MainScene", cc.load("mvc").ViewBase)

function MainScene:onCreate()
    print("Sample Startup")

    local label = cc.Label:createWithSystemFont("QUIT", "sans", 32)
    local quit = cc.MenuItemLabel:create(label)
    quit:onClicked(function()
        os.exit(0)
    end)
    local size = label:getContentSize()
    local menu = cc.Menu:create(quit)
    menu:setPosition(display.right - size.width / 2 - 16, display.bottom + size.height / 2 + 16)
    self:addChild(menu)

    self:setupTestMenu()
end

function MainScene:setupTestMenu()
    cc.MenuItemFont:setFontName("sans")
    local size = cc.Director:getInstance():getWinSize()

    local coin = 0
    local coinLabel = cc.Label:createWithSystemFont("0", "sans", 32)
    coinLabel:setPosition(size.width / 2, size.height - 80)
    self:addChild(coinLabel)

    -- init plugin
    sdkbox.PluginVungle:init()
    sdkbox.PluginVungle:setListener(function(name, args)
        if "onVungleCacheAvailable" == name then
            print("onVungleCacheAvailable")
        elseif "onVungleStarted" ==  name then
            print("onVungleStarted")
        elseif "onVungleFinished" ==  name then
            print("onVungleFinished")
        elseif "onVungleAdViewed" ==  name then
            -- args = isComplete
            local complete = "complete"
            if not args then
                complete = "not complete"
            end
            printf("onVungleAdViewed: %s", complete)
        elseif "onVungleAdReward" ==  name then
            -- args = name
            printf("onVungleAdReward: %s", tostring(args))
            coin = coin + 1
            coinLabel:setString(tostring(coin))
        end
    end)

    local menu = cc.Menu:create(
        cc.MenuItemFont:create("show video"):onClicked(function()
            sdkbox.PluginVungle:show("video")
            print("sdkbox.PluginVungle:show(\"video\")")
        end),
        cc.MenuItemFont:create("show reward"):onClicked(function()
            sdkbox.PluginVungle:show("reward")
            print("sdkbox.PluginVungle:show(\"reward\")")
        end)
    )

    menu:alignItemsVerticallyWithPadding(5)
    menu:setPosition(size.width/2, size.height/2)
    self:addChild(menu)
end

return MainScene
