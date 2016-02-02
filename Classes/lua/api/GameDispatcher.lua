
--------------------------------
-- @module GameDispatcher
-- @extend Node
-- @parent_module 

--------------------------------
-- 
-- @function [parent=#GameDispatcher] cancelPaused 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#GameDispatcher] resumOnce 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#GameDispatcher] getIsCacheEvents 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#GameDispatcher] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#GameDispatcher] clearCacheEvents 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#GameDispatcher] dispatcherGameEvent 
-- @param self
-- @param #GameEvent gEvent
-- @param #cc.Ref pSender
        
--------------------------------
-- 
-- @function [parent=#GameDispatcher] addGameEventListener 
-- @param self
-- @param #int id
-- @param #function callfunc
-- @param #cc.Ref target
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#GameDispatcher] doEmptyEvent 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#GameDispatcher] removeGameEventListener 
-- @param self
-- @param #cc.Ref target
        
--------------------------------
-- 
-- @function [parent=#GameDispatcher] dispatcherGameEventAndPause 
-- @param self
-- @param #GameEvent gEvent
-- @param #bool isCache
        
--------------------------------
-- 
-- @function [parent=#GameDispatcher] create 
-- @param self
-- @return GameDispatcher#GameDispatcher ret (return value: GameDispatcher)
        
--------------------------------
-- 
-- @function [parent=#GameDispatcher] getInstance 
-- @param self
-- @return GameDispatcher#GameDispatcher ret (return value: GameDispatcher)
        
--------------------------------
-- 
-- @function [parent=#GameDispatcher] GameDispatcher 
-- @param self
        
return nil
