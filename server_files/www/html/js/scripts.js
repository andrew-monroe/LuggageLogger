// //http://api.wolframalpha.com/v2/query?input=pi&appid=QVH4Q7-W8QGGVT8H2
//
// var xhr = new XMLHttpRequest();
// xhr.open("GET", "http://api.wolframalpha.com/v2/query?input=pi&appid=QVH4Q7-W8QGGVT8H2", false);
// xhr.send();
//
// console.log(xhr.status);
// console.log(xhr.statusText);

// jQuery cross domain ajax
// $.get("http://api.wolframalpha.com/v2/query?input=pi&appid=QVH4Q7-W8QGGVT8H2").done(function (data) {
//     console.log(data);
// });

function graph(chart_id) {
  generateNewData(chart_id.id);
  var chartName = "";
  var units = "";

  if(chart_id.id == "accelerometer"){
    console.log("accelerometer");
    chartName = "accelerometer";
    units = "Acceleration(ms^2)";
  }
  else if(chart_id.id == "gyro"){
    console.log("gyro graph");
    chartName = "gyro graph";
    units = "Rotation(rads/s)";
  }
  else{
    console.log("barometer graph");
    chartName = "barometer graph";
    units = "Pressure(pascals)";
  }
  var chart = new CanvasJS.Chart(chart_id,
  {
    zoomEnabled: true,
    title:{
      text: chartName
    },
    animationEnabled: true,
    axisX:{
      title: "Time(s)",
      labelAngle: 30
    },

    axisY :{
      title: units,
      includeZero:false
    },

    data: data  // random generator below

  });

  chart.render();
}

 var limit = 100000;    //increase number of dataPoints by increasing this

 var y = 0;
 var data = []; var dataSeries = { type: "line" };
 var dataPoints = [];

 function generateNewData(chart){
   console.log("type: "+chart);
   y = 0;
   data = []; dataSeries = { type: "line" };
   dataPoints = [];
   for (var i = 0; i < array_size-2; i += 1) {
    // y += (Math.random() * 10 - 5);
    if(chart=="accelerometer"){
      // console.log("accl chart");
      console.log(items[i][0]);
      y = parseInt(items[i][1]);
      // console.log(items[i][0]);
      // y=5;
    }
    else if(chart=="gyro"){
      // y=items[i][1];
      y = parseInt(items[i][0]);
    }
    else{
      // y=items[i][2];
      y = parseInt(items[i][2]);
    }
    dataPoints.push({
      x: i,
      y: y
    });
  }
  dataSeries.dataPoints = dataPoints;
  data.push(dataSeries);
}




function plotIfChecked() {
  $('.canvasjs-chart-container').remove();
  if(document.getElementById('accelerometer_checkbox').checked) {
    graph(accelerometer);
    console.log("accelerometer_checkbox");
    console.log(items);
  }
  if(document.getElementById('gyro_checkbox').checked) {
    graph(gyro);
    console.log("gyro_checkbox");
  }
  if(document.getElementById('barometer_checkbox').checked) {
    graph(barometer);
    console.log("barometer_checkbox");
  }
}





var client = new XMLHttpRequest();
var fullText = "";
var array_size;
var read = 0;
var items = [
  [1, 2, 3]
];

client.open('GET', 'resources/data.txt');
client.onreadystatechange = function() {
  storeData(client.responseText);
}
client.send();

function storeData(data){
  // console.log(data);
  fullText = data;
  if(read != 0){
    items = [
      [1, 2, 3]
    ];
    array_size = (fullText.split(/\r\n|\r|\n/).length -1);
    makeArray();
  } else {
    read++;
  }
}

function makeArray(){
  var tmp;
  console.log("sfd");
  arrayOfLines = fullText.match(/[^\r\n]+/g);
  arrayOfLines.splice(0, 1);
  // console.log(arrayOfLines);
  for (var i = 0, len = arrayOfLines.length; i < len; i++) {
    // someFn(arr[i]);
    tmp = arrayOfLines[i].split(" ");
    items.push([tmp[0],tmp[1],tmp[2]]);
  }

  items.splice(0, 1);
  items.splice(arrayOfLines.length-1,1);

  console.log(items);

}
