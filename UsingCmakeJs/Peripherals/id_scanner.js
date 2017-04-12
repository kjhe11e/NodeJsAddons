/**
 * Created by khe11e on 4/11/17.
 */
var Peripherals = require("bindings")("Peripherals");
module.exports = Peripherals;   // re-export it

console.log( "Number passed is: " + Peripherals.PassNumber("20") );
console.log( "String passed is: " + Peripherals.PassString("ID-Scanner") );
console.log( "Status 0 passed is: " + Peripherals.GetStatus(0) );
console.log( "Status 1 passed is: " + Peripherals.GetStatus(1) );
console.log( "Status 2 passed is: " + Peripherals.GetStatus(2) );