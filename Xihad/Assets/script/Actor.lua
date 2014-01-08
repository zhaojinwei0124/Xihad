--- 
-- 控制AI进行动作的控制协程
-- @module Actor
-- @autor wangxuanyi
-- @license MIT
-- @copyright NextRPG

local PathFinder = require "PathFinder"
local RandomStrategy = require "RandomStrategy"
local Chessboard = require "Chessboard"

---
-- @thread cothread
-- @tparam Strategy strategy
local Actor = {
	
}

function Actor.new( o, object )
	o = o or {}
	setmetatable(o, {__index = Actor})
	assert(o.manager)

	o.strategy = RandomStrategy.new{object = object}
	o:initThread(  )
	return o
end

---
-- cothread从上次中断的地方返回继续执行
-- @... 传入任意长参数...
function Actor:run( ... )
	coroutine.resume( self.cothread, ... )
end

function Actor:initThread(  )
	self.cothread = coroutine.create(function ( scheduler )
		while true do
			local object    = self.object
			local strategy  = self.strategy
			local manager   = self.manager			
			local character = object:findComponent(c"Character")
			local tile      = character:tile()

			manager.currentCharacter = object

			PathFinder:getReachableTiles(tile, character:getProperty("maxAP"))
			local point = strategy:judgeTile()
			-- runAsync
			manager:onSelectTile(Chessboard:tileAt(point))
			PathFinder:cleanUp()			
			coroutine.resume(scheduler)

			scheduler = coroutine.yield()
		end
	end)
end


return Actor