/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include "lua_game_manual.hpp"
#include "lua_cocos2dx_ui_auto.hpp"
#include "cocos2d.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "CCLuaValue.h"
#include "ui/CocosGUI.h"
#include "CCLuaEngine.h"
#include "GameDispatcher.h"
using namespace ui;

static int handleDispatcherEvent(int handler, cocos2d::Ref* sender, GameEvent* event)
{
    LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
    
    stack->pushObject(sender, "cc.Ref");
	stack->pushObject(event, "GameEvent");
    stack->executeFunctionByHandler(handler, 2);
    stack->clean();
    
    return 0;
}


static int handleFunc(int handler)
{
	LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
	stack->executeFunctionByHandler(handler, 0);
	stack->clean();
	return 0;
}

static int lua_GameDispatcher_addTouchEventListener(lua_State* L)
{
    if (nullptr == L)
        return 0;
	bool ok = true;
    int argc = 0;
	GameDispatcher* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(L,1,"GameDispatcher",0,&tolua_err)) goto tolua_lerror;
#endif
    
	self = static_cast<GameDispatcher*>(tolua_tousertype(L, 1, 0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_Widget_addTouchEventListener'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(L) - 1;
	if (2 == argc)
	{
		int arg0;
		LUA_FUNCTION arg1;
		ok &= luaval_to_int32(L, 2, (int *)&arg0, "GameDispatcher:addGameEventListener");
		if (!ok) return 0;
		arg1 = (toluafix_ref_function(L, 3, 0));
		if (!ok) return 0;
		int ret = self->addGameEventListener(arg0, [=](cocos2d::Ref* ref, GameEvent* event){
			handleDispatcherEvent(arg1, ref, event);
		});
		tolua_pushnumber(L, (lua_Number)ret);
		// ScriptHandlerMgr::getInstance()->addCustomHandler((void*)self, handler);
		return 1;
	}
    if (3 == argc)
	{
		int arg0;
		LUA_FUNCTION arg1;
		cocos2d::Ref* arg2;
		ok &= luaval_to_int32(L, 2, (int *)&arg0, "GameDispatcher:addGameEventListener");
		if (!ok) return 0;
		arg1 = (toluafix_ref_function(L, 3, 0));
		if (!ok) return 0;
		ok &= luaval_to_object<cocos2d::Ref>(L, 4, "cc.Ref", &arg2);
		if (!ok) return 0;
		int ret = self->addGameEventListener(arg0,[=](cocos2d::Ref* ref, GameEvent* event){
			handleDispatcherEvent(arg1, ref, event);
		}, arg2);
		tolua_pushnumber(L, (lua_Number)ret);
       // ScriptHandlerMgr::getInstance()->addCustomHandler((void*)self, handler);
        return 1;
    }
    CCLOG("'addTouchEventListener' function of Widget has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'addTouchEventListener'.",&tolua_err);
    return 0;
#endif
}

static void extendGameDispatcher(lua_State* L)
{
    lua_pushstring(L, "GameDispatcher");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
		tolua_function(L, "addGameEventListener", lua_GameDispatcher_addTouchEventListener);
    }
    lua_pop(L, 1);
}

static int lua_UIBaseNode_setInitCsbFunc(lua_State* L)
{
	if (nullptr == L)
		return 0;
	bool ok = true;
	int argc = 0;
	UIBaseNode* self = nullptr;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertype(L, 1, "UIBaseNode", 0, &tolua_err)) goto tolua_lerror;
#endif

	self = static_cast<UIBaseNode*>(tolua_tousertype(L, 1, 0));

#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L, "invalid 'self' in function 'lua_cocos2dx_Widget_addTouchEventListener'\n", NULL);
		return 0;
	}
#endif

	argc = lua_gettop(L) - 1;
	if (1 == argc)
	{
		LUA_FUNCTION arg0;
		arg0 = (toluafix_ref_function(L, 2, 0));
		if (!ok) return 0;
		self->setInitCsbFunc(
			[=](){handleFunc(arg0);}
		);
		// ScriptHandlerMgr::getInstance()->addCustomHandler((void*)self, handler);
		return 0;
	}

	CCLOG("'addTouchEventListener' function of Widget has wrong number of arguments: %d, was expecting %d\n", argc, 1);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(L, "#ferror in function 'addTouchEventListener'.", &tolua_err);
	return 0;
#endif
}

static void extenUIdBaseNodeDispatcher(lua_State* L)
{
	lua_pushstring(L, "UIBaseNode");
	lua_rawget(L, LUA_REGISTRYINDEX);
	if (lua_istable(L, -1))
	{
		tolua_function(L, "setInitCsbFunc", lua_UIBaseNode_setInitCsbFunc);
	}
	lua_pop(L, 1);
}



int register_all_game_manual(lua_State* L)
{
    if (nullptr == L)
        return 0;
	extendGameDispatcher(L);
	extenUIdBaseNodeDispatcher(L);
    return 0;
}
