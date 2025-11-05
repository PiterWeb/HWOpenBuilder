local Component = {inputs = {}, outputs = {}, behavior = function () end}

function Component:new(o, inputs, outputs, behavior)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    self.inputs = inputs or {}
    self.outputs = outputs or {}
    self.behavior = behavior or function() end
    return o
end

function Component:update()
    local outputs = self.behavior(table.unpack(self.inputs))
    for i, output in ipairs(outputs) do
        self.outputs[i] = output
    end
end

return Component
