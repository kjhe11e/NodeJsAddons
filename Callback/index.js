const callback = require('./build/Release/callback');

var callMe = function() {
  console.log("Got the call");
}

callback.callThis(callMe);
