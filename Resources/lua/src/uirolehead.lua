
local ui_root       = nil
local ui_csb        = nil
local ui_hpbar      = nil
local ui_mpbar      = nil
local ui_hpText     = nil
local ui_mpText     = nil
local ui_nameText   = nil
-- ui创建的入口
function uiCreate_rolehead()
    ui_root = UIBaseNode:create()
    ui_root:setLocalZOrder(UIZorder.order_mainfront)
    -- 初始化ui
    local function initcsb()
        ui_csb = ccs.GUIReader:getInstance():widgetFromBinaryFile("ui/roleui/roleui.csb")
        ui_root:addChild(ui_csb)
        ui_root:setCsbRoot(ui_csb)
        ui_root:addCsbPlist("ui/roleui/roleui0.plist")

        ui_hpbar = ccui.Helper:seekWidgetByName(ui_csb,"hpbar")
        ui_mpbar = ccui.Helper:seekWidgetByName(ui_csb,"mpbar")
        ui_hpText = ccui.Helper:seekWidgetByName(ui_csb,"hptext")
        ui_mpText = ccui.Helper:seekWidgetByName(ui_csb,"mptext")
        ui_nameText = ccui.Helper:seekWidgetByName(ui_csb,"name")
    end
    ui_root:setInitCsbFunc(initcsb)

    -- 刷新信息
    local function refreshInfo()
        
        local mainData = ObjectDataMgr:getInstance():getMainObjectData()
        local hp = mainData:getHP()
        local hpm = mainData:getHPMax()
        local mp = mainData:getMP()
        local mpm = mainData:getMPMax()
        local name = mainData:getName()
     
        ui_hpbar:setPercent(hp / hpm * 100)
        ui_mpbar:setPercent(mp / mpm * 100)
        ui_hpText:setString(hp .. "/" .. hpm)
        ui_mpText:setString(mp .. "/" .. mpm)
        ui_nameText:setString(name)
    end

    -- ui显示
    local function onShow(sender, event)
        refreshInfo()
    end 
    local Id_uishow = UIManager:getInstance():getDispatcher():addGameEventListener(GameEventId.ui_show,onShow,ui_root)

    -- ui隐藏
    local function onHide(sender, event)

    end 
    local Id_uihide = UIManager:getInstance():getDispatcher():addGameEventListener(GameEventId.ui_hide,onHide,ui_root)

    -- ui销毁
    local function onDestroy(sender, event)

         cclog("--------onDestroy")
    end 
    local Id_uidestroy = UIManager:getInstance():getDispatcher():addGameEventListener(GameEventId.ui_destroy,onDestroy,ui_root)


      -- 血量变化
    local function onHpChange(sender, event)
         refreshInfo()
    end 
    local Id_hpChange = UIManager:getInstance():getDispatcher():addGameEventListener(GameEventId.hp_change,onHpChange,ui_root)

    return ui_root
end 

