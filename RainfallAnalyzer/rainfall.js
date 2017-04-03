var rainfallAddon = require("./cpp/build/Release/rainfall");

var location = {
  latitude: 41.74, longitude: -74.01,
    samples: [
      {date: "2016-03-21", rainfall: 2},
      {date: "2016-04-01", rainfall: 0.5},
      {date: "2016-04-02", rainfall: 3}
    ]
};

var avg = rainfallAddon.avgRainfall(location);
console.log("Average rainfall is (cm): " + avg);

var data = rainfallAddon.getRainfallData(location);
console.log("Mean rainfall is: " + data.mean);
console.log("Median rainfall is: " + data.median);
console.log("Standard deviation is: " + data.standardDeviation);
console.log("Sample size, n, is: " + data.n);
