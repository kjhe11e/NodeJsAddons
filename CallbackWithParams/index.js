const callbackWithParams = require('./build/Release/callbackWithParams');

var callMe = function(message) {
  if(message) {
    console.log(message);
  }
  else {
    console.log("Got the call");
  }
}

callbackWithParams.callThis(callMe);
callbackWithParams.callThisWithThis(callMe, "Important message");
