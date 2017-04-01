var createJsObjects = require('./build/Release/createJsObjects');

var object = createJsObjects.createObj({x:12, y:10});


console.log("Sum of 12+10 is " + object.sum);
console.log("Product of 12*10 is " + object.product);
