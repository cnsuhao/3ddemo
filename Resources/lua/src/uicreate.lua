
--------------------------------------------------


-- 所有ui创建的入口
local function onCreateUI(sender, event)

    local uitype = event:getUIType()
    
    for i,v in pairs(uicreate_list) do
        if i == uitype then
            require(v.lua)
            local ui = _G[v.func]()
            event:setUIBaseNode(ui)
            break
        end
    end

end 

local Id_uicreate = GameDispatcher:getInstance():addGameEventListener(GameEventId.ui_create,onCreateUI)

cclog("Id_uicreate");