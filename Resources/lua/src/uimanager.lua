
--------------------------------------------------------------
Zorder =
{
	order_map	= 1,
	order_ui	= 100,
}

UIZorder =
{
	order_mainbk	=	0,
	order_main		=	100,
	order_mainfront =	500,
	order_load		=	1000,
}

UIType =
{
	UI_Update		= 1,
	UI_Login		= 2,
	UI_Chat			= 3,
	UI_Loading		= 4,
    UI_RoleHead 	= 5,
   	UI_Rocker		= 6,
	UI_MiniMap		= 7,
	UI_SkillPanel	= 8,
	UI_SelTarget	= 9,
	UI_WorldMap		= 10,
}

GameEventId =
{
	event_nil           = 0,
	ui_create           = 1,
	ui_show             = 2,
	ui_hide             = 3,
	ui_destroy          = 4,
    grid_changeshow		= 5,
    update_mypos		= 6,
    update_pos			= 7,
    hp_change			= 8,
	sel_target			= 9,
	update_autostate	= 10,
}

HPChangeEvent_ID        = 1004

uicreate_list = 
{
    [UIType.UI_RoleHead]    = {lua = "uirolehead.lua"   ,func = "uiCreate_rolehead"},
    --[UIType.UI_MiniMap]     = {lua = "uiminimap.lua"    ,func = "uiCreate_minimap"},
}