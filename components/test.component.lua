local Component = require "components/component"

local adder_behavior = function(a, b)
    print(a + b)
    local result = a + b
    return { result }
end

local adder = Component:new { inputs = { 1, 2 }, outputs = { 0 }, behavior = adder_behavior }

return adder