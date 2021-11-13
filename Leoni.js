var mysql = require('mysql');
var express = require('express');
var app = express();
var express = require('express');
var app = express();
app.set('port', process.env.PORT || 3333);
app.listen(app.get('port'), function () {
  console.log('Express started on https://leoni.com:' +
    app.get('port') + '; press Ctrl-C to terminate.');

});





//jwt begin


con = mysql.createConnection({
    host: "localhost",
    user: "root",
    password: "",
    database: "leoni_lines"
  });


app.get('/mh1/:line_number/:state/:segment/:RT_RATIO/:START_TIM/:V_type', (req, res) => {


  


    //if (err) throw err;
    console.log("Connected!");
    con.query("UPDATE `mh1` SET `DISPLAY_LINE` = '" + req.params.state + "' WHERE (`mh1`.`V_Type` like '%" + req.params.V_type + "%' and `mh1`.`Segment` like '%" + req.params.segment + "%')", function (err, result, fields) {
      if (err) throw err;
      res.setHeader("Access-Control-Allow-Origin", "*")
      res.setHeader("Access-Control-Allow-Credentials", "true");
      res.setHeader("Access-Control-Max-Age", "1800");
      res.setHeader("Access-Control-Allow-Headers", "content-type");
      res.setHeader("Access-Control-Allow-Methods", "PUT, POST, GET, DELETE, PATCH, OPTIONS");
      res.type('text/plain');
      res.send(result)

    });


});


app.get('/mh2/:line_number/:state/:segment/:RT_RATIO/:START_TIM/:V_type', (req, res) => {




 
   // if (err) throw err;
    console.log("Connected!");
    con.query("UPDATE `mh2` SET `DISPLAY_LINE` = '" + req.params.state + "' WHERE (`mh2`.`V_Type` like '%" + req.params.V_type + "%' and `mh2`.`Segment` like '%" + req.params.segment + "%')", function (err, result, fields) {
      if (err) throw err;
      res.setHeader("Access-Control-Allow-Origin", "*")
      res.setHeader("Access-Control-Allow-Credentials", "true");
      res.setHeader("Access-Control-Max-Age", "1800");
      res.setHeader("Access-Control-Allow-Headers", "content-type");
      res.setHeader("Access-Control-Allow-Methods", "PUT, POST, GET, DELETE, PATCH, OPTIONS");
      res.type('text/plain');
      res.send(result)

    });
 



});





app.post('/:line_number/:state/:RT_RATIO/:START_TIME', function (req, res) {
  line_state = req.params;
  res.setHeader("Access-Control-Allow-Origin", "*")
  res.type('text/plain');
  console.log(req.params);

  res.send(line_state);


});

app.get('/mh1', (req, res) => {

 

  
    //if (err) throw err;
    console.log("Connected /mh1");
    con.query("SELECT LINE_NUMBER,RT_RATIO,STATE,START_TIME,A_DURATION,D_DURATION,V_Type FROM MH1 where DISPLAY_LINE=1", function (err, result, fields) {
      if (err) throw err;
      res.setHeader("Access-Control-Allow-Origin", "*")
      res.setHeader("Access-Control-Allow-Credentials", "true");
      res.setHeader("Access-Control-Max-Age", "1800");
      res.setHeader("Access-Control-Allow-Headers", "content-type");
      res.setHeader("Access-Control-Allow-Methods", "PUT, POST, GET, DELETE, PATCH, OPTIONS");
      res.type('text/plain');
      res.send(result)

    });
 



});
app.get('/MH2', (req, res) => {

  //con = mysql.createConnection({
   // host: "localhost",
   // user: "root",
  //  password: "",
  //  database: "leoni_lines"
//  });

 
    //if (err) throw err;
    console.log("Connected mh2");
    con.query("SELECT LINE_NUMBER,RT_RATIO,STATE,START_TIME,A_DURATION,D_DURATION,V_Type FROM MH2 where DISPLAY_LINE=1", function (err, result, fields) {
      if (err) throw err;
      res.setHeader("Access-Control-Allow-Origin", "*")
      res.setHeader("Access-Control-Allow-Credentials", "true");
      res.setHeader("Access-Control-Max-Age", "1800");
      res.setHeader("Access-Control-Allow-Headers", "content-type");
      res.setHeader("Access-Control-Allow-Methods", "PUT, POST, GET, DELETE, PATCH, OPTIONS");
      res.type('text/plain');
      res.send(result)

    });
 



});
app.get('/apperance', (req, res) => {
  

 
   // if (err) throw err;
    console.log("Connected!");
    con.query("SELECT * FROM appearance", function (err, result, fields) {
      if (err) throw err;
      res.setHeader("Access-Control-Allow-Origin", "*")
      res.setHeader("Access-Control-Allow-Credentials", "true");
      res.setHeader("Access-Control-Max-Age", "1800");
      res.setHeader("Access-Control-Allow-Headers", "content-type");
      res.setHeader("Access-Control-Allow-Methods", "PUT, POST, GET, DELETE, PATCH, OPTIONS");
      res.type('text/plain');
      res.send(result)

    });


});
app.get('/Vordawagen_state/:V_type', (req, res) => {

 
 
   // if (err) throw err;
    console.log("Connected /Vordawagen_state/:V_type'");
    con.query("SELECT DISPLAY_LINE FROM MH1 where V_type like'%" + req.params.V_type + "%'", function (err, result, fields) {
      if (err) throw err;
      res.setHeader("Access-Control-Allow-Origin", "*")
      res.setHeader("Access-Control-Allow-Credentials", "true");
      res.setHeader("Access-Control-Max-Age", "1800");
      res.setHeader("Access-Control-Allow-Headers", "content-type");
      res.setHeader("Access-Control-Allow-Methods", "PUT, POST, GET, DELETE, PATCH, OPTIONS");
      res.type('text/plain');
      res.send(result)

    });

});

app.get('/mh1/:line_number/:state/:RT_RATIO/:START_TIM/:V_type', (req, res) => {


  

 
   // if (err) throw err;
    console.log("Connected!");
    con.query("UPDATE `mh1` SET `DISPLAY_LINE` = '" + req.params.state + "' WHERE `mh1`.`V_Type` like '%" + req.params.V_type + "%'", function (err, result, fields) {
      if (err) throw err;
      res.setHeader("Access-Control-Allow-Origin", "*")
      res.setHeader("Access-Control-Allow-Credentials", "true");
      res.setHeader("Access-Control-Max-Age", "1800");
      res.setHeader("Access-Control-Allow-Headers", "content-type");
      res.setHeader("Access-Control-Allow-Methods", "PUT, POST, GET, DELETE, PATCH, OPTIONS");
      res.type('text/plain');
      res.send(result)

    });


});


app.get('/mh2/:line_number/:state/:RT_RATIO/:START_TIM/:V_type', (req, res) => {


  

  //con.connect(function (err) {
    //if (err) throw err;
    console.log("Connected!");
    con.query("UPDATE `mh1` SET `DISPLAY_LINE` = '" + req.params.state + "' WHERE `mh1`.`V_Type` like '%" + req.params.V_type + "%'", function (err, result, fields) {
      if (err) throw err;
      res.setHeader("Access-Control-Allow-Origin", "*")
      res.setHeader("Access-Control-Allow-Credentials", "true");
      res.setHeader("Access-Control-Max-Age", "1800");
      res.setHeader("Access-Control-Allow-Headers", "content-type");
      res.setHeader("Access-Control-Allow-Methods", "PUT, POST, GET, DELETE, PATCH, OPTIONS");
      res.type('text/plain');
      res.send(result)

    });
  //});

});




function msToTime(s) {

  // Pad to 2 or 3 digits, default is 2
  function pad(n, z) {
    z = z || 2;
    return ('00' + n).slice(-z);
  }

  var ms = s % 1000;
  s = (s - ms) / 1000;
  var secs = s % 60;
  s = (s - secs) / 60;
  var mins = s % 60;
  var hrs = (s - mins) / 60;

  return pad(hrs) + ':' + pad(mins) + ':' + pad(secs) + ':' + pad(ms, 3);
}

function addTimes(startTime, endTime) {
  var times = [0, 0, 0]
  var max = times.length

  var a = (startTime || '').split(':')
  var b = (endTime || '').split(':')

  // normalize time values
  for (var i = 0; i < max; i++) {
    a[i] = isNaN(parseInt(a[i])) ? 0 : parseInt(a[i])
    b[i] = isNaN(parseInt(b[i])) ? 0 : parseInt(b[i])
  }

  // store time values
  for (var i = 0; i < max; i++) {
    times[i] = a[i] + b[i]
  }

  var hours = times[0]
  var minutes = times[1]
  var seconds = times[2]

  if (seconds >= 60) {
    var m = (seconds / 60) << 0
    minutes += m
    seconds -= 60 * m
  }

  if (minutes >= 60) {
    var h = (minutes / 60) << 0
    hours += h
    minutes -= 60 * h
  }

  return ('0' + hours).slice(-2) + ':' + ('0' + minutes).slice(-2) + ':' + ('0' + seconds).slice(-2)
}

app.get('/arduino/:mh/:line_number/:elapsed/:starttime/:state/:Nbre_brettes', (req, res) => {


  let ts = Date.now();

  let date_ob = new Date(ts);
  let hours = date_ob.getHours()
hours = ("0" +hours).slice(-2);
// current minutes
let minutes = date_ob.getMinutes();
minutes = ("0" +minutes).slice(-2);
// current seconds
let seconds = date_ob.getSeconds();
   seconds = ("0" +seconds).slice(-2);
  let month = date_ob.getMonth();

  let year = date_ob.getFullYear();

  con = mysql.createConnection({
    host: "localhost",
    user: "root",
    password: "",
    database: "leoni_lines"
  });

 // con.connect(function (err) {
   

   // if (err) throw err;
    console.log("Connected! /arduino/:mh/:line_number/:elapsed/:starttime/:state/:N_brette'");
    con.query("SELECT A_DURATION from `"+req.params.mh+"` where `LINE_NUMBER` = '" + req.params.line_number + "'", function (err, result, fields) {
      if (err) throw err;

 let old_activeduration
    let new_activeduration
    res.setHeader("Date",hours+":"+minutes+":"+seconds);
      res.setHeader("Access-Control-Allow-Origin", "*");
      res.setHeader("Access-Control-Allow-Credentials", "true");
      res.setHeader("Access-Control-Max-Age", "1800");
      res.setHeader("Access-Control-Allow-Headers", "content-type");
      res.setHeader("Access-Control-Allow-Methods", "PUT, POST, GET, DELETE, PATCH, OPTIONS");
      res.type('text/plain');
      old_activeduration = result[0].A_DURATION;
      // res.send("elapsed :"msToTime(req.params.elapsed )+"  old :  "+ old_activeduration)

      new_activeduration = addTimes(old_activeduration, msToTime(req.params.elapsed))

      con.query("UPDATE `"+req.params.mh+"` SET `A_DURATION` = '" + new_activeduration + "',`RT_RATIO`='"+req.params.Nbre_brettes+"',`STATE`='"+req.params.state+"',`START_TIME`='"+req.params.starttime+ "' WHERE `"+req.params.mh+"`.`LINE_NUMBER` = '" + req.params.line_number + "'", function (err, result, fields) {
        if (err) throw err;
  
  
  
        res.setHeader("Access-Control-Allow-Origin", "*")
        res.setHeader("Access-Control-Allow-Credentials", "true");
        res.setHeader("Access-Control-Max-Age", "1800");
        res.setHeader("Access-Control-Allow-Headers", "content-type");
        res.setHeader("Access-Control-Allow-Methods", "PUT, POST, GET, DELETE, PATCH, OPTIONS");
        res.type('text/plain');
        res.send(result)
        
        console.log(result)
  
      });






    });
   
    


  //});

});

app.get('/time', (req, res) => {


  
  let ts = Date.now();

  let date_ob = new Date(ts);
  let hours = ("0"+date_ob.getHours()).slice(-2);;

// current minutes
let minutes = ("0"+date_ob.getMinutes()).slice(-2);;

// current seconds
let seconds = date_ob.getSeconds();
  let date = date_ob.getDate();
  let month = date_ob.getMonth() + 1;
  let year = date_ob.getFullYear();
  
  // prints date & time in YYYY-MM-DD format
  console.log(year + "-" + month + "-" + date);
 
  
      res.setHeader("Access-Control-Allow-Origin", "*")
      res.setHeader("Access-Control-Allow-Credentials", "true");
      res.setHeader("Access-Control-Max-Age", "1800");
      res.setHeader("Access-Control-Allow-Headers", "content-type");
      res.setHeader("Access-Control-Allow-Methods", "PUT, POST, GET, DELETE, PATCH, OPTIONS");
      res.type('text/plain');
      res.send(    hours +":"+minutes+":"+seconds+"  "+year + "-" + month + "-" + date)

   
     
});