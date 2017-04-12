/**
 * Created by khe11e on 4/11/17.
 */
var Peripherals = require("bindings")("Peripherals");
module.exports = Peripherals;   // re-export it

console.log( "Number passed is: " + Peripherals.PassNumber("20") );
console.log( "String passed is: " + Peripherals.PassString("ID-Scanner") );