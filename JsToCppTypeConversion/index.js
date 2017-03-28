var passNumberAddon = require('./build/Release/passNumber');

console.log("Original num is 10");
var returnedNum = passNumberAddon.passNumber(10);
console.log("Modified value (+10) is " + returnedNum);

console.log("Original num is 11.5");
returnedNum = passNumberAddon.passNumber(11.5);
console.log("Modified value (+10) is " + returnedNum);
