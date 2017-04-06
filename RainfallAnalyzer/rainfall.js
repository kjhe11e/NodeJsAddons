var rainfallAddon = require("./cpp/build/Release/rainfall");

var testLocation = {
  latitude: 41.74, longitude: -74.01,
    samples: [
      {date: "2016-03-21", rainfall: 2},
      {date: "2016-04-01", rainfall: 0.5},
      {date: "2016-04-02", rainfall: 3}
    ]
};

var avg = rainfallAddon.avgRainfall(testLocation);
console.log("Average rainfall is (cm): " + avg);

var data = rainfallAddon.getSingleLocationRainfallData(testLocation);
console.log("Mean rainfall is: " + data.mean);
console.log("Median rainfall is: " + data.median);
console.log("Standard deviation is: " + data.standardDeviation);
console.log("Sample size, n, is: " + data.n);

var randomNum = function(max) {
  return Math.round(max * Math.random() * 100) / 100;
};

var locations = [];
for(var i = 0; i < 10; i++) {
  var loc = {
    latitude: randomNum(180),
    longitude: randomNum(180),
    samples: [
      {date: "2017-03-10", rainfall: randomNum(3)},
      {date: "2017-03-11", rainfall: randomNum(3)},
      {date: "2017-03-12", rainfall: randomNum(3)},
      {date: "2017-03-13", rainfall: randomNum(3)}
    ]
  }
  locations.push(loc);
}

var totalResults = rainfallAddon.getAllRainfallData(locations);

var i = 0;
totalResults.forEach(function(result) {
  console.log("Result for location " + i);
  console.log("--------------------------");
  console.log("\tLatitude: " + locations[i].latitude.toFixed(2));
  console.log("\tLongitude: " + locations[i].longitude.toFixed(2));
  console.log("\tAvg rainfall: " + result.mean.toFixed(2) + "cm");
  console.log("\tMedian rainfall: " + result.median.toFixed(2) + "cm");
  console.log("\tStandard deviation: " + result.standardDeviation.toFixed(2) + "cm");
  console.log("\tNumber of samples: " + result.n);
  console.log();
  i++;
});
