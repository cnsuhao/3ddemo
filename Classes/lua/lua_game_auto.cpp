#include "lua_game_auto.hpp"
#include "GameDispatcher.h"
#include "GameEvent.h"
#include "UIManager.h"
#include "UIBaseNode.h"
#include "ObjectDataMgr.h"
#include "ObjectData.h"
#include "GameObjectMgr.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_cocosgame_UIBaseNode_setCsbFrame(lua_State* tolua_S)
{
    int argc = 0;
    UIBaseNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UIBaseNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UIBaseNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_UIBaseNode_setCsbFrame'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ui::Widget* arg0;

        ok &= luaval_to_object<cocos2d::ui::Widget>(tolua_S, 2, "ccui.Widget",&arg0);
        if(!ok)
            return 0;
        cobj->setCsbFrame(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "UIBaseNode:setCsbFrame",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UIBaseNode_setCsbFrame'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_UIBaseNode_scheduleRemoveCsb(lua_State* tolua_S)
{
    int argc = 0;
    UIBaseNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UIBaseNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UIBaseNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_UIBaseNode_scheduleRemoveCsb'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "UIBaseNode:scheduleRemoveCsb");
        if(!ok)
            return 0;
        cobj->scheduleRemoveCsb(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "UIBaseNode:scheduleRemoveCsb",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UIBaseNode_scheduleRemoveCsb'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_UIBaseNode_hide(lua_State* tolua_S)
{
    int argc = 0;
    UIBaseNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UIBaseNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UIBaseNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_UIBaseNode_hide'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->hide();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "UIBaseNode:hide",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UIBaseNode_hide'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_UIBaseNode_setCsbRoot(lua_State* tolua_S)
{
    int argc = 0;
    UIBaseNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UIBaseNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UIBaseNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_UIBaseNode_setCsbRoot'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ui::Layout* arg0;

        ok &= luaval_to_object<cocos2d::ui::Layout>(tolua_S, 2, "ccui.Layout",&arg0);
        if(!ok)
            return 0;
        cobj->setCsbRoot(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "UIBaseNode:setCsbRoot",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UIBaseNode_setCsbRoot'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_UIBaseNode_show(lua_State* tolua_S)
{
    int argc = 0;
    UIBaseNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UIBaseNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UIBaseNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_UIBaseNode_show'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->show();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "UIBaseNode:show",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UIBaseNode_show'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_UIBaseNode_update(lua_State* tolua_S)
{
    int argc = 0;
    UIBaseNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UIBaseNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UIBaseNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_UIBaseNode_update'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "UIBaseNode:update");
        if(!ok)
            return 0;
        cobj->update(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "UIBaseNode:update",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UIBaseNode_update'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_UIBaseNode_setInitCsbFunc(lua_State* tolua_S)
{
    int argc = 0;
    UIBaseNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UIBaseNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UIBaseNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_UIBaseNode_setInitCsbFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::function<void ()> arg0;

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
            return 0;
        cobj->setInitCsbFunc(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "UIBaseNode:setInitCsbFunc",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UIBaseNode_setInitCsbFunc'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_UIBaseNode_isShow(lua_State* tolua_S)
{
    int argc = 0;
    UIBaseNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UIBaseNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UIBaseNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_UIBaseNode_isShow'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->isShow();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "UIBaseNode:isShow",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UIBaseNode_isShow'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_UIBaseNode_init(lua_State* tolua_S)
{
    int argc = 0;
    UIBaseNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UIBaseNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UIBaseNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_UIBaseNode_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "UIBaseNode:init",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UIBaseNode_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_UIBaseNode_addCsbPlist(lua_State* tolua_S)
{
    int argc = 0;
    UIBaseNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UIBaseNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UIBaseNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_UIBaseNode_addCsbPlist'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "UIBaseNode:addCsbPlist");
        if(!ok)
            return 0;
        cobj->addCsbPlist(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "UIBaseNode:addCsbPlist",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UIBaseNode_addCsbPlist'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_UIBaseNode_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"UIBaseNode",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        UIBaseNode* ret = UIBaseNode::create();
        object_to_luaval<UIBaseNode>(tolua_S, "UIBaseNode",(UIBaseNode*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "UIBaseNode:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UIBaseNode_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocosgame_UIBaseNode_constructor(lua_State* tolua_S)
{
    int argc = 0;
    UIBaseNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new UIBaseNode();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"UIBaseNode");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "UIBaseNode:UIBaseNode",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UIBaseNode_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocosgame_UIBaseNode_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (UIBaseNode)");
    return 0;
}

int lua_register_cocosgame_UIBaseNode(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"UIBaseNode");
    tolua_cclass(tolua_S,"UIBaseNode","UIBaseNode","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"UIBaseNode");
        tolua_function(tolua_S,"new",lua_cocosgame_UIBaseNode_constructor);
        tolua_function(tolua_S,"setCsbFrame",lua_cocosgame_UIBaseNode_setCsbFrame);
        tolua_function(tolua_S,"scheduleRemoveCsb",lua_cocosgame_UIBaseNode_scheduleRemoveCsb);
        tolua_function(tolua_S,"hide",lua_cocosgame_UIBaseNode_hide);
        tolua_function(tolua_S,"setCsbRoot",lua_cocosgame_UIBaseNode_setCsbRoot);
        tolua_function(tolua_S,"show",lua_cocosgame_UIBaseNode_show);
        tolua_function(tolua_S,"update",lua_cocosgame_UIBaseNode_update);
        tolua_function(tolua_S,"setInitCsbFunc",lua_cocosgame_UIBaseNode_setInitCsbFunc);
        tolua_function(tolua_S,"isShow",lua_cocosgame_UIBaseNode_isShow);
        tolua_function(tolua_S,"init",lua_cocosgame_UIBaseNode_init);
        tolua_function(tolua_S,"addCsbPlist",lua_cocosgame_UIBaseNode_addCsbPlist);
        tolua_function(tolua_S,"create", lua_cocosgame_UIBaseNode_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(UIBaseNode).name();
    g_luaType[typeName] = "UIBaseNode";
    g_typeCast["UIBaseNode"] = "UIBaseNode";
    return 1;
}

int lua_cocosgame_GameEvent_getParamStr(lua_State* tolua_S)
{
    int argc = 0;
    GameEvent* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameEvent",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameEvent*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_GameEvent_getParamStr'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        std::string ret = cobj->getParamStr();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameEvent:getParamStr",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameEvent_getParamStr'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_GameEvent_getEventId(lua_State* tolua_S)
{
    int argc = 0;
    GameEvent* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameEvent",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameEvent*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_GameEvent_getEventId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = (int)cobj->getEventId();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameEvent:getEventId",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameEvent_getEventId'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_GameEvent_getParamInt1(lua_State* tolua_S)
{
    int argc = 0;
    GameEvent* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameEvent",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameEvent*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_GameEvent_getParamInt1'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getParamInt1();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameEvent:getParamInt1",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameEvent_getParamInt1'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_GameEvent_init(lua_State* tolua_S)
{
    int argc = 0;
    GameEvent* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameEvent",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameEvent*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_GameEvent_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        GameEventId arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "GameEvent:init");
        if(!ok)
            return 0;
        cobj->init(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameEvent:init",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameEvent_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_GameEvent_getParamInt2(lua_State* tolua_S)
{
    int argc = 0;
    GameEvent* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameEvent",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameEvent*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_GameEvent_getParamInt2'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getParamInt2();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameEvent:getParamInt2",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameEvent_getParamInt2'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_GameEvent_setParamInt1(lua_State* tolua_S)
{
    int argc = 0;
    GameEvent* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameEvent",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameEvent*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_GameEvent_setParamInt1'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "GameEvent:setParamInt1");
        if(!ok)
            return 0;
        cobj->setParamInt1(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameEvent:setParamInt1",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameEvent_setParamInt1'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_GameEvent_setParamInt2(lua_State* tolua_S)
{
    int argc = 0;
    GameEvent* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameEvent",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameEvent*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_GameEvent_setParamInt2'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "GameEvent:setParamInt2");
        if(!ok)
            return 0;
        cobj->setParamInt2(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameEvent:setParamInt2",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameEvent_setParamInt2'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_GameEvent_setParamStr(lua_State* tolua_S)
{
    int argc = 0;
    GameEvent* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameEvent",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameEvent*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_GameEvent_setParamStr'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "GameEvent:setParamStr");
        if(!ok)
            return 0;
        cobj->setParamStr(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameEvent:setParamStr",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameEvent_setParamStr'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_GameEvent_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"GameEvent",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        GameEventId arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "GameEvent:create");
        if(!ok)
            return 0;
        GameEvent* ret = GameEvent::create(arg0);
        object_to_luaval<GameEvent>(tolua_S, "GameEvent",(GameEvent*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "GameEvent:create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameEvent_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocosgame_GameEvent_constructor(lua_State* tolua_S)
{
    int argc = 0;
    GameEvent* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new GameEvent();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"GameEvent");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameEvent:GameEvent",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameEvent_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocosgame_GameEvent_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (GameEvent)");
    return 0;
}

int lua_register_cocosgame_GameEvent(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"GameEvent");
    tolua_cclass(tolua_S,"GameEvent","GameEvent","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"GameEvent");
        tolua_function(tolua_S,"new",lua_cocosgame_GameEvent_constructor);
        tolua_function(tolua_S,"getParamStr",lua_cocosgame_GameEvent_getParamStr);
        tolua_function(tolua_S,"getEventId",lua_cocosgame_GameEvent_getEventId);
        tolua_function(tolua_S,"getParamInt1",lua_cocosgame_GameEvent_getParamInt1);
        tolua_function(tolua_S,"init",lua_cocosgame_GameEvent_init);
        tolua_function(tolua_S,"getParamInt2",lua_cocosgame_GameEvent_getParamInt2);
        tolua_function(tolua_S,"setParamInt1",lua_cocosgame_GameEvent_setParamInt1);
        tolua_function(tolua_S,"setParamInt2",lua_cocosgame_GameEvent_setParamInt2);
        tolua_function(tolua_S,"setParamStr",lua_cocosgame_GameEvent_setParamStr);
        tolua_function(tolua_S,"create", lua_cocosgame_GameEvent_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(GameEvent).name();
    g_luaType[typeName] = "GameEvent";
    g_typeCast["GameEvent"] = "GameEvent";
    return 1;
}

int lua_cocosgame_UICreateEvent_setUIBaseNode(lua_State* tolua_S)
{
    int argc = 0;
    UICreateEvent* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UICreateEvent",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UICreateEvent*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_UICreateEvent_setUIBaseNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        UIBaseNode* arg0;

        ok &= luaval_to_object<UIBaseNode>(tolua_S, 2, "UIBaseNode",&arg0);
        if(!ok)
            return 0;
        cobj->setUIBaseNode(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "UICreateEvent:setUIBaseNode",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UICreateEvent_setUIBaseNode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_UICreateEvent_getUIType(lua_State* tolua_S)
{
    int argc = 0;
    UICreateEvent* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UICreateEvent",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UICreateEvent*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_UICreateEvent_getUIType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getUIType();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "UICreateEvent:getUIType",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UICreateEvent_getUIType'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_UICreateEvent_setUIType(lua_State* tolua_S)
{
    int argc = 0;
    UICreateEvent* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UICreateEvent",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UICreateEvent*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_UICreateEvent_setUIType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "UICreateEvent:setUIType");
        if(!ok)
            return 0;
        cobj->setUIType(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "UICreateEvent:setUIType",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UICreateEvent_setUIType'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_UICreateEvent_getUIBaseNode(lua_State* tolua_S)
{
    int argc = 0;
    UICreateEvent* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UICreateEvent",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UICreateEvent*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_UICreateEvent_getUIBaseNode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        UIBaseNode* ret = cobj->getUIBaseNode();
        object_to_luaval<UIBaseNode>(tolua_S, "UIBaseNode",(UIBaseNode*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "UICreateEvent:getUIBaseNode",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UICreateEvent_getUIBaseNode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_UICreateEvent_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"UICreateEvent",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        GameEventId arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "UICreateEvent:create");
        if(!ok)
            return 0;
        UICreateEvent* ret = UICreateEvent::create(arg0);
        object_to_luaval<UICreateEvent>(tolua_S, "UICreateEvent",(UICreateEvent*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "UICreateEvent:create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UICreateEvent_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocosgame_UICreateEvent_constructor(lua_State* tolua_S)
{
    int argc = 0;
    UICreateEvent* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new UICreateEvent();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"UICreateEvent");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "UICreateEvent:UICreateEvent",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UICreateEvent_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocosgame_UICreateEvent_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (UICreateEvent)");
    return 0;
}

int lua_register_cocosgame_UICreateEvent(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"UICreateEvent");
    tolua_cclass(tolua_S,"UICreateEvent","UICreateEvent","GameEvent",nullptr);

    tolua_beginmodule(tolua_S,"UICreateEvent");
        tolua_function(tolua_S,"new",lua_cocosgame_UICreateEvent_constructor);
        tolua_function(tolua_S,"setUIBaseNode",lua_cocosgame_UICreateEvent_setUIBaseNode);
        tolua_function(tolua_S,"getUIType",lua_cocosgame_UICreateEvent_getUIType);
        tolua_function(tolua_S,"setUIType",lua_cocosgame_UICreateEvent_setUIType);
        tolua_function(tolua_S,"getUIBaseNode",lua_cocosgame_UICreateEvent_getUIBaseNode);
        tolua_function(tolua_S,"create", lua_cocosgame_UICreateEvent_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(UICreateEvent).name();
    g_luaType[typeName] = "UICreateEvent";
    g_typeCast["UICreateEvent"] = "UICreateEvent";
    return 1;
}

int lua_cocosgame_GameDispatcher_cancelPaused(lua_State* tolua_S)
{
    int argc = 0;
    GameDispatcher* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameDispatcher",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameDispatcher*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_GameDispatcher_cancelPaused'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->cancelPaused();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameDispatcher:cancelPaused",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameDispatcher_cancelPaused'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_GameDispatcher_resumOnce(lua_State* tolua_S)
{
    int argc = 0;
    GameDispatcher* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameDispatcher",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameDispatcher*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_GameDispatcher_resumOnce'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->resumOnce();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameDispatcher:resumOnce",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameDispatcher_resumOnce'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_GameDispatcher_getIsCacheEvents(lua_State* tolua_S)
{
    int argc = 0;
    GameDispatcher* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameDispatcher",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameDispatcher*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_GameDispatcher_getIsCacheEvents'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->getIsCacheEvents();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameDispatcher:getIsCacheEvents",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameDispatcher_getIsCacheEvents'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_GameDispatcher_init(lua_State* tolua_S)
{
    int argc = 0;
    GameDispatcher* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameDispatcher",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameDispatcher*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_GameDispatcher_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameDispatcher:init",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameDispatcher_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_GameDispatcher_clearCacheEvents(lua_State* tolua_S)
{
    int argc = 0;
    GameDispatcher* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameDispatcher",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameDispatcher*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_GameDispatcher_clearCacheEvents'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->clearCacheEvents();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameDispatcher:clearCacheEvents",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameDispatcher_clearCacheEvents'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_GameDispatcher_dispatcherGameEvent(lua_State* tolua_S)
{
    int argc = 0;
    GameDispatcher* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameDispatcher",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameDispatcher*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_GameDispatcher_dispatcherGameEvent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        GameEvent* arg0;
        cocos2d::Ref* arg1;

        ok &= luaval_to_object<GameEvent>(tolua_S, 2, "GameEvent",&arg0);

        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 3, "cc.Ref",&arg1);
        if(!ok)
            return 0;
        cobj->dispatcherGameEvent(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameDispatcher:dispatcherGameEvent",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameDispatcher_dispatcherGameEvent'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_GameDispatcher_addGameEventListener(lua_State* tolua_S)
{
    int argc = 0;
    GameDispatcher* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameDispatcher",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameDispatcher*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_GameDispatcher_addGameEventListener'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        std::function<void (cocos2d::Ref *, GameEvent *)> arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "GameDispatcher:addGameEventListener");

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
        if(!ok)
            return 0;
        int ret = cobj->addGameEventListener(arg0, arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    if (argc == 3) 
    {
        int arg0;
        std::function<void (cocos2d::Ref *, GameEvent *)> arg1;
        cocos2d::Ref* arg2;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "GameDispatcher:addGameEventListener");

        do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;

        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 4, "cc.Ref",&arg2);
        if(!ok)
            return 0;
        int ret = cobj->addGameEventListener(arg0, arg1, arg2);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameDispatcher:addGameEventListener",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameDispatcher_addGameEventListener'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_GameDispatcher_doEmptyEvent(lua_State* tolua_S)
{
    int argc = 0;
    GameDispatcher* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameDispatcher",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameDispatcher*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_GameDispatcher_doEmptyEvent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->doEmptyEvent();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameDispatcher:doEmptyEvent",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameDispatcher_doEmptyEvent'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_GameDispatcher_removeGameEventListener(lua_State* tolua_S)
{
    int argc = 0;
    GameDispatcher* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameDispatcher",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameDispatcher*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_GameDispatcher_removeGameEventListener'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Ref* arg0;

        ok &= luaval_to_object<cocos2d::Ref>(tolua_S, 2, "cc.Ref",&arg0);
        if(!ok)
            return 0;
        cobj->removeGameEventListener(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameDispatcher:removeGameEventListener",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameDispatcher_removeGameEventListener'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_GameDispatcher_dispatcherGameEventAndPause(lua_State* tolua_S)
{
    int argc = 0;
    GameDispatcher* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameDispatcher",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameDispatcher*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_GameDispatcher_dispatcherGameEventAndPause'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        GameEvent* arg0;

        ok &= luaval_to_object<GameEvent>(tolua_S, 2, "GameEvent",&arg0);
        if(!ok)
            return 0;
        cobj->dispatcherGameEventAndPause(arg0);
        return 0;
    }
    if (argc == 2) 
    {
        GameEvent* arg0;
        bool arg1;

        ok &= luaval_to_object<GameEvent>(tolua_S, 2, "GameEvent",&arg0);

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "GameDispatcher:dispatcherGameEventAndPause");
        if(!ok)
            return 0;
        cobj->dispatcherGameEventAndPause(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameDispatcher:dispatcherGameEventAndPause",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameDispatcher_dispatcherGameEventAndPause'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_GameDispatcher_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"GameDispatcher",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        GameDispatcher* ret = GameDispatcher::create();
        object_to_luaval<GameDispatcher>(tolua_S, "GameDispatcher",(GameDispatcher*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "GameDispatcher:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameDispatcher_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocosgame_GameDispatcher_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"GameDispatcher",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        GameDispatcher* ret = GameDispatcher::getInstance();
        object_to_luaval<GameDispatcher>(tolua_S, "GameDispatcher",(GameDispatcher*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "GameDispatcher:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameDispatcher_getInstance'.",&tolua_err);
#endif
    return 0;
}
int lua_cocosgame_GameDispatcher_constructor(lua_State* tolua_S)
{
    int argc = 0;
    GameDispatcher* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new GameDispatcher();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"GameDispatcher");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameDispatcher:GameDispatcher",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameDispatcher_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocosgame_GameDispatcher_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (GameDispatcher)");
    return 0;
}

int lua_register_cocosgame_GameDispatcher(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"GameDispatcher");
    tolua_cclass(tolua_S,"GameDispatcher","GameDispatcher","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"GameDispatcher");
        tolua_function(tolua_S,"new",lua_cocosgame_GameDispatcher_constructor);
        tolua_function(tolua_S,"cancelPaused",lua_cocosgame_GameDispatcher_cancelPaused);
        tolua_function(tolua_S,"resumOnce",lua_cocosgame_GameDispatcher_resumOnce);
        tolua_function(tolua_S,"getIsCacheEvents",lua_cocosgame_GameDispatcher_getIsCacheEvents);
        tolua_function(tolua_S,"init",lua_cocosgame_GameDispatcher_init);
        tolua_function(tolua_S,"clearCacheEvents",lua_cocosgame_GameDispatcher_clearCacheEvents);
        tolua_function(tolua_S,"dispatcherGameEvent",lua_cocosgame_GameDispatcher_dispatcherGameEvent);
        tolua_function(tolua_S,"addGameEventListener",lua_cocosgame_GameDispatcher_addGameEventListener);
        tolua_function(tolua_S,"doEmptyEvent",lua_cocosgame_GameDispatcher_doEmptyEvent);
        tolua_function(tolua_S,"removeGameEventListener",lua_cocosgame_GameDispatcher_removeGameEventListener);
        tolua_function(tolua_S,"dispatcherGameEventAndPause",lua_cocosgame_GameDispatcher_dispatcherGameEventAndPause);
        tolua_function(tolua_S,"create", lua_cocosgame_GameDispatcher_create);
        tolua_function(tolua_S,"getInstance", lua_cocosgame_GameDispatcher_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(GameDispatcher).name();
    g_luaType[typeName] = "GameDispatcher";
    g_typeCast["GameDispatcher"] = "GameDispatcher";
    return 1;
}

int lua_cocosgame_UIManager_getFullWidthScale(lua_State* tolua_S)
{
    int argc = 0;
    UIManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UIManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UIManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_UIManager_getFullWidthScale'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getFullWidthScale();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "UIManager:getFullWidthScale",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UIManager_getFullWidthScale'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_UIManager_loadUI(lua_State* tolua_S)
{
    int argc = 0;
    UIManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UIManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UIManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_UIManager_loadUI'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "UIManager:loadUI");
        if(!ok)
            return 0;
        cobj->loadUI(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "UIManager:loadUI",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UIManager_loadUI'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_UIManager_getUI(lua_State* tolua_S)
{
    int argc = 0;
    UIManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UIManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UIManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_UIManager_getUI'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        UIType arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "UIManager:getUI");
        if(!ok)
            return 0;
        UIBaseNode* ret = cobj->getUI(arg0);
        object_to_luaval<UIBaseNode>(tolua_S, "UIBaseNode",(UIBaseNode*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "UIManager:getUI",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UIManager_getUI'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_UIManager_hideWithCreate(lua_State* tolua_S)
{
    int argc = 0;
    UIManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UIManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UIManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_UIManager_hideWithCreate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        UIType arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "UIManager:hideWithCreate");
        if(!ok)
            return 0;
        cobj->hideWithCreate(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "UIManager:hideWithCreate",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UIManager_hideWithCreate'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_UIManager_setIsAutoFight(lua_State* tolua_S)
{
    int argc = 0;
    UIManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UIManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UIManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_UIManager_setIsAutoFight'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "UIManager:setIsAutoFight");
        if(!ok)
            return 0;
        cobj->setIsAutoFight(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "UIManager:setIsAutoFight",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UIManager_setIsAutoFight'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_UIManager_isShow(lua_State* tolua_S)
{
    int argc = 0;
    UIManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UIManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UIManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_UIManager_isShow'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        UIType arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "UIManager:isShow");
        if(!ok)
            return 0;
        bool ret = cobj->isShow(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "UIManager:isShow",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UIManager_isShow'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_UIManager_getDispatcher(lua_State* tolua_S)
{
    int argc = 0;
    UIManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UIManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UIManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_UIManager_getDispatcher'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        GameDispatcher* ret = cobj->getDispatcher();
        object_to_luaval<GameDispatcher>(tolua_S, "GameDispatcher",(GameDispatcher*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "UIManager:getDispatcher",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UIManager_getDispatcher'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_UIManager_getUISize(lua_State* tolua_S)
{
    int argc = 0;
    UIManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UIManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UIManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_UIManager_getUISize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Size ret = cobj->getUISize();
        size_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "UIManager:getUISize",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UIManager_getUISize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_UIManager_hideUI(lua_State* tolua_S)
{
    int argc = 0;
    UIManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UIManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UIManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_UIManager_hideUI'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        UIType arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "UIManager:hideUI");
        if(!ok)
            return 0;
        cobj->hideUI(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "UIManager:hideUI",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UIManager_hideUI'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_UIManager_init(lua_State* tolua_S)
{
    int argc = 0;
    UIManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UIManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UIManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_UIManager_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "UIManager:init",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UIManager_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_UIManager_getFullScreenScale(lua_State* tolua_S)
{
    int argc = 0;
    UIManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UIManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UIManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_UIManager_getFullScreenScale'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getFullScreenScale();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "UIManager:getFullScreenScale",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UIManager_getFullScreenScale'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_UIManager_getFullHeightScale(lua_State* tolua_S)
{
    int argc = 0;
    UIManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UIManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UIManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_UIManager_getFullHeightScale'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getFullHeightScale();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "UIManager:getFullHeightScale",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UIManager_getFullHeightScale'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_UIManager_getUIScale(lua_State* tolua_S)
{
    int argc = 0;
    UIManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UIManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UIManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_UIManager_getUIScale'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getUIScale();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "UIManager:getUIScale",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UIManager_getUIScale'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_UIManager_createUI(lua_State* tolua_S)
{
    int argc = 0;
    UIManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UIManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UIManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_UIManager_createUI'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        UIType arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "UIManager:createUI");
        if(!ok)
            return 0;
        UIBaseNode* ret = cobj->createUI(arg0);
        object_to_luaval<UIBaseNode>(tolua_S, "UIBaseNode",(UIBaseNode*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "UIManager:createUI",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UIManager_createUI'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_UIManager_showUI(lua_State* tolua_S)
{
    int argc = 0;
    UIManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UIManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UIManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_UIManager_showUI'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        UIType arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "UIManager:showUI");
        if(!ok)
            return 0;
        UIBaseNode* ret = cobj->showUI(arg0);
        object_to_luaval<UIBaseNode>(tolua_S, "UIBaseNode",(UIBaseNode*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "UIManager:showUI",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UIManager_showUI'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_UIManager_destroyInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"UIManager",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        UIManager::destroyInstance();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "UIManager:destroyInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UIManager_destroyInstance'.",&tolua_err);
#endif
    return 0;
}
int lua_cocosgame_UIManager_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"UIManager",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        UIManager* ret = UIManager::create();
        object_to_luaval<UIManager>(tolua_S, "UIManager",(UIManager*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "UIManager:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UIManager_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocosgame_UIManager_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"UIManager",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        UIManager* ret = UIManager::getInstance();
        object_to_luaval<UIManager>(tolua_S, "UIManager",(UIManager*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "UIManager:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UIManager_getInstance'.",&tolua_err);
#endif
    return 0;
}
int lua_cocosgame_UIManager_constructor(lua_State* tolua_S)
{
    int argc = 0;
    UIManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new UIManager();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"UIManager");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "UIManager:UIManager",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_UIManager_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocosgame_UIManager_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (UIManager)");
    return 0;
}

int lua_register_cocosgame_UIManager(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"UIManager");
    tolua_cclass(tolua_S,"UIManager","UIManager","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"UIManager");
        tolua_function(tolua_S,"new",lua_cocosgame_UIManager_constructor);
        tolua_function(tolua_S,"getFullWidthScale",lua_cocosgame_UIManager_getFullWidthScale);
        tolua_function(tolua_S,"loadUI",lua_cocosgame_UIManager_loadUI);
        tolua_function(tolua_S,"getUI",lua_cocosgame_UIManager_getUI);
        tolua_function(tolua_S,"hideWithCreate",lua_cocosgame_UIManager_hideWithCreate);
        tolua_function(tolua_S,"setIsAutoFight",lua_cocosgame_UIManager_setIsAutoFight);
        tolua_function(tolua_S,"isShow",lua_cocosgame_UIManager_isShow);
        tolua_function(tolua_S,"getDispatcher",lua_cocosgame_UIManager_getDispatcher);
        tolua_function(tolua_S,"getUISize",lua_cocosgame_UIManager_getUISize);
        tolua_function(tolua_S,"hideUI",lua_cocosgame_UIManager_hideUI);
        tolua_function(tolua_S,"init",lua_cocosgame_UIManager_init);
        tolua_function(tolua_S,"getFullScreenScale",lua_cocosgame_UIManager_getFullScreenScale);
        tolua_function(tolua_S,"getFullHeightScale",lua_cocosgame_UIManager_getFullHeightScale);
        tolua_function(tolua_S,"getUIScale",lua_cocosgame_UIManager_getUIScale);
        tolua_function(tolua_S,"createUI",lua_cocosgame_UIManager_createUI);
        tolua_function(tolua_S,"showUI",lua_cocosgame_UIManager_showUI);
        tolua_function(tolua_S,"destroyInstance", lua_cocosgame_UIManager_destroyInstance);
        tolua_function(tolua_S,"create", lua_cocosgame_UIManager_create);
        tolua_function(tolua_S,"getInstance", lua_cocosgame_UIManager_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(UIManager).name();
    g_luaType[typeName] = "UIManager";
    g_typeCast["UIManager"] = "UIManager";
    return 1;
}

int lua_cocosgame_ObjectData_setName(lua_State* tolua_S)
{
    int argc = 0;
    ObjectData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ObjectData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ObjectData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_ObjectData_setName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ObjectData:setName");
        if(!ok)
            return 0;
        cobj->setName(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ObjectData:setName",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_ObjectData_setName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_ObjectData_getMPMax(lua_State* tolua_S)
{
    int argc = 0;
    ObjectData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ObjectData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ObjectData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_ObjectData_getMPMax'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getMPMax();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ObjectData:getMPMax",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_ObjectData_getMPMax'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_ObjectData_setWeaponId(lua_State* tolua_S)
{
    int argc = 0;
    ObjectData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ObjectData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ObjectData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_ObjectData_setWeaponId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ObjectData:setWeaponId");
        if(!ok)
            return 0;
        cobj->setWeaponId(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ObjectData:setWeaponId",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_ObjectData_setWeaponId'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_ObjectData_getName(lua_State* tolua_S)
{
    int argc = 0;
    ObjectData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ObjectData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ObjectData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_ObjectData_getName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        std::string ret = cobj->getName();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ObjectData:getName",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_ObjectData_getName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_ObjectData_getHPMax(lua_State* tolua_S)
{
    int argc = 0;
    ObjectData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ObjectData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ObjectData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_ObjectData_getHPMax'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getHPMax();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ObjectData:getHPMax",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_ObjectData_getHPMax'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_ObjectData_getTileMapPos(lua_State* tolua_S)
{
    int argc = 0;
    ObjectData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ObjectData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ObjectData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_ObjectData_getTileMapPos'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Point ret = cobj->getTileMapPos();
        point_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ObjectData:getTileMapPos",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_ObjectData_getTileMapPos'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_ObjectData_init(lua_State* tolua_S)
{
    int argc = 0;
    ObjectData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ObjectData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ObjectData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_ObjectData_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 8) 
    {
        int arg0;
        int arg1;
        ActDir arg2;
        ActMotion arg3;
        cocos2d::Point arg4;
        std::string arg5;
        int arg6;
        int arg7;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ObjectData:init");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ObjectData:init");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ObjectData:init");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "ObjectData:init");

        ok &= luaval_to_point(tolua_S, 6, &arg4, "ObjectData:init");

        ok &= luaval_to_std_string(tolua_S, 7,&arg5, "ObjectData:init");

        ok &= luaval_to_int32(tolua_S, 8,(int *)&arg6, "ObjectData:init");

        ok &= luaval_to_int32(tolua_S, 9,(int *)&arg7, "ObjectData:init");
        if(!ok)
            return 0;
        cobj->init(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        return 0;
    }
    if (argc == 9) 
    {
        int arg0;
        int arg1;
        ActDir arg2;
        ActMotion arg3;
        cocos2d::Point arg4;
        std::string arg5;
        int arg6;
        int arg7;
        int arg8;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ObjectData:init");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ObjectData:init");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ObjectData:init");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "ObjectData:init");

        ok &= luaval_to_point(tolua_S, 6, &arg4, "ObjectData:init");

        ok &= luaval_to_std_string(tolua_S, 7,&arg5, "ObjectData:init");

        ok &= luaval_to_int32(tolua_S, 8,(int *)&arg6, "ObjectData:init");

        ok &= luaval_to_int32(tolua_S, 9,(int *)&arg7, "ObjectData:init");

        ok &= luaval_to_int32(tolua_S, 10,(int *)&arg8, "ObjectData:init");
        if(!ok)
            return 0;
        cobj->init(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ObjectData:init",argc, 8);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_ObjectData_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_ObjectData_getMP(lua_State* tolua_S)
{
    int argc = 0;
    ObjectData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ObjectData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ObjectData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_ObjectData_getMP'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getMP();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ObjectData:getMP",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_ObjectData_getMP'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_ObjectData_getHP(lua_State* tolua_S)
{
    int argc = 0;
    ObjectData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ObjectData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ObjectData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_ObjectData_getHP'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getHP();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ObjectData:getHP",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_ObjectData_getHP'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_ObjectData_setRect(lua_State* tolua_S)
{
    int argc = 0;
    ObjectData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ObjectData",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ObjectData*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_ObjectData_setRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "ObjectData:setRect");
        if(!ok)
            return 0;
        cobj->setRect(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ObjectData:setRect",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_ObjectData_setRect'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_ObjectData_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ObjectData",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        ObjectData* ret = ObjectData::create();
        object_to_luaval<ObjectData>(tolua_S, "ObjectData",(ObjectData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ObjectData:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_ObjectData_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocosgame_ObjectData_constructor(lua_State* tolua_S)
{
    int argc = 0;
    ObjectData* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new ObjectData();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ObjectData");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ObjectData:ObjectData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_ObjectData_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocosgame_ObjectData_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ObjectData)");
    return 0;
}

int lua_register_cocosgame_ObjectData(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ObjectData");
    tolua_cclass(tolua_S,"ObjectData","ObjectData","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"ObjectData");
        tolua_function(tolua_S,"new",lua_cocosgame_ObjectData_constructor);
        tolua_function(tolua_S,"setName",lua_cocosgame_ObjectData_setName);
        tolua_function(tolua_S,"getMPMax",lua_cocosgame_ObjectData_getMPMax);
        tolua_function(tolua_S,"setWeaponId",lua_cocosgame_ObjectData_setWeaponId);
        tolua_function(tolua_S,"getName",lua_cocosgame_ObjectData_getName);
        tolua_function(tolua_S,"getHPMax",lua_cocosgame_ObjectData_getHPMax);
        tolua_function(tolua_S,"getTileMapPos",lua_cocosgame_ObjectData_getTileMapPos);
        tolua_function(tolua_S,"init",lua_cocosgame_ObjectData_init);
        tolua_function(tolua_S,"getMP",lua_cocosgame_ObjectData_getMP);
        tolua_function(tolua_S,"getHP",lua_cocosgame_ObjectData_getHP);
        tolua_function(tolua_S,"setRect",lua_cocosgame_ObjectData_setRect);
        tolua_function(tolua_S,"create", lua_cocosgame_ObjectData_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(ObjectData).name();
    g_luaType[typeName] = "ObjectData";
    g_typeCast["ObjectData"] = "ObjectData";
    return 1;
}

int lua_cocosgame_ObjectDataMgr_clearObjectDatas(lua_State* tolua_S)
{
    int argc = 0;
    ObjectDataMgr* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ObjectDataMgr",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ObjectDataMgr*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_ObjectDataMgr_clearObjectDatas'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->clearObjectDatas();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ObjectDataMgr:clearObjectDatas",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_ObjectDataMgr_clearObjectDatas'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_ObjectDataMgr_getMainObjectData(lua_State* tolua_S)
{
    int argc = 0;
    ObjectDataMgr* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ObjectDataMgr",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ObjectDataMgr*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_ObjectDataMgr_getMainObjectData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        ObjectData* ret = cobj->getMainObjectData();
        object_to_luaval<ObjectData>(tolua_S, "ObjectData",(ObjectData*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ObjectDataMgr:getMainObjectData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_ObjectDataMgr_getMainObjectData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_ObjectDataMgr_initData(lua_State* tolua_S)
{
    int argc = 0;
    ObjectDataMgr* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ObjectDataMgr",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ObjectDataMgr*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_ObjectDataMgr_initData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->initData();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ObjectDataMgr:initData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_ObjectDataMgr_initData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_ObjectDataMgr_getMainPlayerJob(lua_State* tolua_S)
{
    int argc = 0;
    ObjectDataMgr* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ObjectDataMgr",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ObjectDataMgr*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_ObjectDataMgr_getMainPlayerJob'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getMainPlayerJob();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ObjectDataMgr:getMainPlayerJob",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_ObjectDataMgr_getMainPlayerJob'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_ObjectDataMgr_setMainData(lua_State* tolua_S)
{
    int argc = 0;
    ObjectDataMgr* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ObjectDataMgr",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ObjectDataMgr*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_ObjectDataMgr_setMainData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ObjectDataMgr:setMainData");
        if(!ok)
            return 0;
        cobj->setMainData(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ObjectDataMgr:setMainData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_ObjectDataMgr_setMainData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_ObjectDataMgr_addPlayerData(lua_State* tolua_S)
{
    int argc = 0;
    ObjectDataMgr* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ObjectDataMgr",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ObjectDataMgr*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_ObjectDataMgr_addPlayerData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        ObjectData* arg0;

        ok &= luaval_to_object<ObjectData>(tolua_S, 2, "ObjectData",&arg0);
        if(!ok)
            return 0;
        cobj->addPlayerData(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ObjectDataMgr:addPlayerData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_ObjectDataMgr_addPlayerData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_ObjectDataMgr_getPlayList(lua_State* tolua_S)
{
    int argc = 0;
    ObjectDataMgr* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ObjectDataMgr",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ObjectDataMgr*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_ObjectDataMgr_getPlayList'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        std::vector<ObjectData *, std::allocator<ObjectData *> > ret = cobj->getPlayList();
        //object_to_luaval<std::vector<ObjectData , std::allocator<ObjectData > >>(tolua_S, "std::vector<ObjectData *, std::allocator<ObjectData *> >",(std::vector<ObjectData *, std::allocator<ObjectData *> >)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ObjectDataMgr:getPlayList",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_ObjectDataMgr_getPlayList'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_ObjectDataMgr_destroyInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ObjectDataMgr",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        ObjectDataMgr::destroyInstance();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ObjectDataMgr:destroyInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_ObjectDataMgr_destroyInstance'.",&tolua_err);
#endif
    return 0;
}
int lua_cocosgame_ObjectDataMgr_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ObjectDataMgr",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        ObjectDataMgr* ret = ObjectDataMgr::getInstance();
        object_to_luaval<ObjectDataMgr>(tolua_S, "ObjectDataMgr",(ObjectDataMgr*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "ObjectDataMgr:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_ObjectDataMgr_getInstance'.",&tolua_err);
#endif
    return 0;
}
int lua_cocosgame_ObjectDataMgr_constructor(lua_State* tolua_S)
{
    int argc = 0;
    ObjectDataMgr* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new ObjectDataMgr();
        tolua_pushusertype(tolua_S,(void*)cobj,"ObjectDataMgr");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "ObjectDataMgr:ObjectDataMgr",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_ObjectDataMgr_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocosgame_ObjectDataMgr_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ObjectDataMgr)");
    return 0;
}

int lua_register_cocosgame_ObjectDataMgr(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ObjectDataMgr");
    tolua_cclass(tolua_S,"ObjectDataMgr","ObjectDataMgr","",nullptr);

    tolua_beginmodule(tolua_S,"ObjectDataMgr");
        tolua_function(tolua_S,"new",lua_cocosgame_ObjectDataMgr_constructor);
        tolua_function(tolua_S,"clearObjectDatas",lua_cocosgame_ObjectDataMgr_clearObjectDatas);
        tolua_function(tolua_S,"getMainObjectData",lua_cocosgame_ObjectDataMgr_getMainObjectData);
        tolua_function(tolua_S,"initData",lua_cocosgame_ObjectDataMgr_initData);
        tolua_function(tolua_S,"getMainPlayerJob",lua_cocosgame_ObjectDataMgr_getMainPlayerJob);
        tolua_function(tolua_S,"setMainData",lua_cocosgame_ObjectDataMgr_setMainData);
        tolua_function(tolua_S,"addPlayerData",lua_cocosgame_ObjectDataMgr_addPlayerData);
        tolua_function(tolua_S,"getPlayList",lua_cocosgame_ObjectDataMgr_getPlayList);
        tolua_function(tolua_S,"destroyInstance", lua_cocosgame_ObjectDataMgr_destroyInstance);
        tolua_function(tolua_S,"getInstance", lua_cocosgame_ObjectDataMgr_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(ObjectDataMgr).name();
    g_luaType[typeName] = "ObjectDataMgr";
    g_typeCast["ObjectDataMgr"] = "ObjectDataMgr";
    return 1;
}

int lua_cocosgame_GameObjectMgr_getNearGameObject(lua_State* tolua_S)
{
    int argc = 0;
    GameObjectMgr* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameObjectMgr",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameObjectMgr*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_GameObjectMgr_getNearGameObject'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        GameObject* arg0;

        ok &= luaval_to_object<GameObject>(tolua_S, 2, "GameObject",&arg0);
        if(!ok)
            return 0;
        GameObject* ret = cobj->getNearGameObject(arg0);
        object_to_luaval<GameObject>(tolua_S, "GameObject",(GameObject*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameObjectMgr:getNearGameObject",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameObjectMgr_getNearGameObject'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_GameObjectMgr_getMainGamePlayer(lua_State* tolua_S)
{
    int argc = 0;
    GameObjectMgr* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameObjectMgr",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameObjectMgr*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_GameObjectMgr_getMainGamePlayer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        GamePlayer* ret = cobj->getMainGamePlayer();
        object_to_luaval<GamePlayer>(tolua_S, "GamePlayer",(GamePlayer*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameObjectMgr:getMainGamePlayer",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameObjectMgr_getMainGamePlayer'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_GameObjectMgr_isExistGameObject(lua_State* tolua_S)
{
    int argc = 0;
    GameObjectMgr* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameObjectMgr",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameObjectMgr*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_GameObjectMgr_isExistGameObject'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        GameObject* arg0;
        cocos2d::Point arg1;

        ok &= luaval_to_object<GameObject>(tolua_S, 2, "GameObject",&arg0);

        ok &= luaval_to_point(tolua_S, 3, &arg1, "GameObjectMgr:isExistGameObject");
        if(!ok)
            return 0;
        bool ret = cobj->isExistGameObject(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameObjectMgr:isExistGameObject",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameObjectMgr_isExistGameObject'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_GameObjectMgr_clearGameOjects(lua_State* tolua_S)
{
    int argc = 0;
    GameObjectMgr* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameObjectMgr",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameObjectMgr*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_GameObjectMgr_clearGameOjects'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->clearGameOjects();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameObjectMgr:clearGameOjects",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameObjectMgr_clearGameOjects'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_GameObjectMgr_mainPlayerGoToFarestChuanSongPT(lua_State* tolua_S)
{
    int argc = 0;
    GameObjectMgr* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameObjectMgr",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameObjectMgr*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_GameObjectMgr_mainPlayerGoToFarestChuanSongPT'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->mainPlayerGoToFarestChuanSongPT();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameObjectMgr:mainPlayerGoToFarestChuanSongPT",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameObjectMgr_mainPlayerGoToFarestChuanSongPT'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_GameObjectMgr_setReorderChildDirty(lua_State* tolua_S)
{
    int argc = 0;
    GameObjectMgr* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameObjectMgr",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameObjectMgr*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_GameObjectMgr_setReorderChildDirty'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "GameObjectMgr:setReorderChildDirty");
        if(!ok)
            return 0;
        cobj->setReorderChildDirty(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameObjectMgr:setReorderChildDirty",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameObjectMgr_setReorderChildDirty'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_GameObjectMgr_sortAllChildren(lua_State* tolua_S)
{
    int argc = 0;
    GameObjectMgr* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameObjectMgr",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameObjectMgr*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_GameObjectMgr_sortAllChildren'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->sortAllChildren();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameObjectMgr:sortAllChildren",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameObjectMgr_sortAllChildren'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_GameObjectMgr_init(lua_State* tolua_S)
{
    int argc = 0;
    GameObjectMgr* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameObjectMgr",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameObjectMgr*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_GameObjectMgr_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameObjectMgr:init",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameObjectMgr_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_GameObjectMgr_loadObjects(lua_State* tolua_S)
{
    int argc = 0;
    GameObjectMgr* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameObjectMgr",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameObjectMgr*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_GameObjectMgr_loadObjects'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->loadObjects();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameObjectMgr:loadObjects",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameObjectMgr_loadObjects'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_GameObjectMgr_clickGameObjec(lua_State* tolua_S)
{
    int argc = 0;
    GameObjectMgr* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"GameObjectMgr",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (GameObjectMgr*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocosgame_GameObjectMgr_clickGameObjec'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Point arg0;

        ok &= luaval_to_point(tolua_S, 2, &arg0, "GameObjectMgr:clickGameObjec");
        if(!ok)
            return 0;
        bool ret = cobj->clickGameObjec(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameObjectMgr:clickGameObjec",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameObjectMgr_clickGameObjec'.",&tolua_err);
#endif

    return 0;
}
int lua_cocosgame_GameObjectMgr_destroyInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"GameObjectMgr",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        GameObjectMgr::destroyInstance();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "GameObjectMgr:destroyInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameObjectMgr_destroyInstance'.",&tolua_err);
#endif
    return 0;
}
int lua_cocosgame_GameObjectMgr_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"GameObjectMgr",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        GameObjectMgr* ret = GameObjectMgr::getInstance();
        object_to_luaval<GameObjectMgr>(tolua_S, "GameObjectMgr",(GameObjectMgr*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "GameObjectMgr:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameObjectMgr_getInstance'.",&tolua_err);
#endif
    return 0;
}
int lua_cocosgame_GameObjectMgr_constructor(lua_State* tolua_S)
{
    int argc = 0;
    GameObjectMgr* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new GameObjectMgr();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"GameObjectMgr");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameObjectMgr:GameObjectMgr",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocosgame_GameObjectMgr_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocosgame_GameObjectMgr_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (GameObjectMgr)");
    return 0;
}

int lua_register_cocosgame_GameObjectMgr(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"GameObjectMgr");
    tolua_cclass(tolua_S,"GameObjectMgr","GameObjectMgr","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"GameObjectMgr");
        tolua_function(tolua_S,"new",lua_cocosgame_GameObjectMgr_constructor);
        tolua_function(tolua_S,"getNearGameObject",lua_cocosgame_GameObjectMgr_getNearGameObject);
        tolua_function(tolua_S,"getMainGamePlayer",lua_cocosgame_GameObjectMgr_getMainGamePlayer);
        tolua_function(tolua_S,"isExistGameObject",lua_cocosgame_GameObjectMgr_isExistGameObject);
        tolua_function(tolua_S,"clearGameOjects",lua_cocosgame_GameObjectMgr_clearGameOjects);
        tolua_function(tolua_S,"mainPlayerGoToFarestChuanSongPT",lua_cocosgame_GameObjectMgr_mainPlayerGoToFarestChuanSongPT);
        tolua_function(tolua_S,"setReorderChildDirty",lua_cocosgame_GameObjectMgr_setReorderChildDirty);
        tolua_function(tolua_S,"sortAllChildren",lua_cocosgame_GameObjectMgr_sortAllChildren);
        tolua_function(tolua_S,"init",lua_cocosgame_GameObjectMgr_init);
        tolua_function(tolua_S,"loadObjects",lua_cocosgame_GameObjectMgr_loadObjects);
        tolua_function(tolua_S,"clickGameObjec",lua_cocosgame_GameObjectMgr_clickGameObjec);
        tolua_function(tolua_S,"destroyInstance", lua_cocosgame_GameObjectMgr_destroyInstance);
        tolua_function(tolua_S,"getInstance", lua_cocosgame_GameObjectMgr_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(GameObjectMgr).name();
    g_luaType[typeName] = "GameObjectMgr";
    g_typeCast["GameObjectMgr"] = "GameObjectMgr";
    return 1;
}
TOLUA_API int register_all_cocosgame(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,nullptr,0);
	tolua_beginmodule(tolua_S,nullptr);

	lua_register_cocosgame_GameEvent(tolua_S);
	lua_register_cocosgame_ObjectDataMgr(tolua_S);
	lua_register_cocosgame_ObjectData(tolua_S);
	lua_register_cocosgame_GameDispatcher(tolua_S);
	lua_register_cocosgame_UIManager(tolua_S);
	lua_register_cocosgame_UICreateEvent(tolua_S);
	lua_register_cocosgame_GameObjectMgr(tolua_S);
	lua_register_cocosgame_UIBaseNode(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

