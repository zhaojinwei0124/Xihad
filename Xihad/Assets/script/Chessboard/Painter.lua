local defaultColorTable = {
	Reachable   = Color.white, 
	Selected 	= Color.black,
	Destination = Color.cyan,
	Attack      = Color.orange,
	Castable    = Color.magenta,
}
defaultColorTable.__index = defaultColorTable

local Painter = {
	colorTable = nil,
}
Painter.__index = Painter

function Painter.new(colorTable)
	colorTable = colorTable or {}
	
	return setmetatable({
			colorTable = setmetatable(colorTable, defaultColorTable)
		}, Painter)
end

function Painter:mark(tiles, type)
	if not tiles then return end
	
	local color = Color.new(self.colorTable[type])
	
	local handle = {}
	for _, tile in ipairs(tiles) do
		local terrian = tile:getTerrain()
		local idx = terrian:pushColor(color)
		handle[terrian] = idx
	end
	
	return handle
end

function Painter:clear(handle)
	if not handle then return end
	
	for terrian, idx in pairs(handle) do
		terrian:removeColor(idx)
	end
end

return Painter