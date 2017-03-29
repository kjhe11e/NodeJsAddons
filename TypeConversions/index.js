var typeConversions = require('./build/Release/typeConversions');

console.log("Original num is 10");
var returnedNum = typeConversions.passNumber(10);
console.log("Modified value (+10) is " + returnedNum);

console.log("Original num is 11.5");
returnedNum = typeConversions.passNumber(11.5);
console.log("Modified value (+10) is " + returnedNum);

console.log("String is Hello");
var str = typeConversions.reverseStr("Hello");
console.log("Reversed string is " + str);
