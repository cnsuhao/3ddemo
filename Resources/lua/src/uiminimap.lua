
local ui_root   = nil
local ui_csb    = nil
local ui_label  = nil
local ui_btnfight = nil
local d_isAuto  = 0
-- ui创建的入口
function uiCreate_minimap()
    ui_root = UIBaseNode:create()
    ui_root:setLocalZOrder(UIZorder.order_mainfront)
    -- 初始化ui
    local function initcsb()
        ui_csb = ccs.GUIReader:getInstance():widgetFromBinaryFile("ui/minimap/minimap.csb")
        ui_root:addChild(ui_csb)
        ui_root:setCsbRoot(ui_csb)
        ui_root:addCsbPlist("ui/minimap/minimap0.plist")
        -- 地图位置
        ui_label = ccui.Helper:seekWidgetByName(ui_csb,"Label_pos")
        -- 点击开关格子
        local btn_map = ccui.Helper:seekWidgetByName(ui_csb,"Image_quan")
        local function touchMapEvent(sender, touchType)
            if touchType == ccui.TouchEventType.ended then
			
				--UIManager:getInstance():showUI(UIType.UI_WorldMap)
                local gEvent = GameEvent:create(GameEventId.grid_changeshow)
                UIManager:getInstance():getDispatcher():dispatcherGameEvent(gEvent, ui_root)
            end
        end
        btn_map:setTouchEnabled(true)
        btn_map:addTouchEventListener(touchMapEvent)

        -- 点击自动战斗
        ui_btnfight = ccui.Helper:seekWidgetByName(ui_csb,"zhandoubtn")
        local function touchZhanDouBtnEvent(sender, touchType)
            if touchType == ccui.TouchEventType.ended then
                if d_isAuto == 0 then
                    UIManager:getInstance():setIsAutoFight(true)
                else
                    UIManager:getInstance():setIsAutoFight(false)
                end
            end
        end
        ui_btnfight:setTouchEnabled(true)
        ui_btnfight:addTouchEventListener(touchZhanDouBtnEvent)


        -- 点击传送
        ui_btnchuan = ccui.Helper:seekWidgetByName(ui_csb,"chuansongbtn")
        local function touchChuanSongBtnEvent(sender, touchType)
            if touchType == ccui.TouchEventType.ended then
                GameObjectMgr:getInstance():mainPlayerGoToFarestChuanSongPT()
            end
        end
		ui_btnchuan:setVisible(false)
        ui_btnchuan:setTouchEnabled(true)
        ui_btnchuan:addTouchEventListener(touchChuanSongBtnEvent)

    end
    ui_root:setInitCsbFunc(initcsb)

    -- 刷新地图位置
    local function refreshMapPos()
        local pos = ObjectDataMgr:getInstance():getMainObjectData():getTileMapPos()
        print(pos.x .. "   " .. pos.y)
        ui_label:setString(string.format("(%d,%d)", pos.x, pos.y))
    end

    -- 刷新位置
    local function onRefreshMyMapPos(sender, event)
        refreshMapPos()
    end 
    local Id_updatemypos = GameDispatcher:getInstance():addGameEventListener(GameEventId.update_mypos,onRefreshMyMapPos,ui_root)

    -- ui显示
    local function onShow(sender, event)

        cclog("--------onShow")
        -- 刷新地图位置
        refreshMapPos()
    end 
    local Id_uishow = UIManager:getInstance():getDispatcher():addGameEventListener(GameEventId.ui_show,onShow,ui_root)

    -- ui隐藏
    local function onHide(sender, event)

        cclog("--------onHide")

    end 
    local Id_uihide = UIManager:getInstance():getDispatcher():addGameEventListener(GameEventId.ui_hide,onHide,ui_root)

    -- ui销毁
    local function onDestroy(sender, event)

         cclog("--------onDestroy")
    end 
    local Id_uidestroy = UIManager:getInstance():getDispatcher():addGameEventListener(GameEventId.ui_destroy,onDestroy,ui_root)


	-- 自动战斗状态变化
    local function onAutoStateChange(sender, event)
		d_isAuto = event:getParamInt1()
		ui_btnfight:loadTextureNormal(string.format("minimap/zidongzhandoubtn%d.png", d_isAuto + 1),1)

		print("自动战斗状态变化")
    end 
    local Id_autoStateChange = UIManager:getInstance():getDispatcher():addGameEventListener(GameEventId.update_autostate,onAutoStateChange,ui_root)


    return ui_root
end 

