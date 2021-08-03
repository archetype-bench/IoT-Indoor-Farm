setChartTitle('Indoor Farm Monitor')
var lineGraph1 = new boltGraph();
lineGraph1.setChartType("lineGraph");
lineGraph1.setAxisName('Time','Temp C');
lineGraph1.plotChart('time_stamp','temp');
var lineGraph2 = new boltGraph();
lineGraph2.setChartType("lineGraph");
lineGraph2.setAxisName('Time','Humidity %');
lineGraph2.plotChart('time_stamp','hum');
var lineGraph3 = new boltGraph();
lineGraph3.setChartType("lineGraph");
lineGraph3.setAxisName('Time','Sunlight (0/1)');
lineGraph3.plotChart('time_stamp','ambi');
var lineGraph4 = new boltGraph();
lineGraph4.setChartType("lineGraph");
lineGraph4.setAxisName('Time','Soil Mositure %');
lineGraph4.plotChart('time_stamp','moist');