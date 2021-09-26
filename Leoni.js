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





app.get('/mh1/:line_number/:state/:segment/:RT_RATIO/:START_TIM/:V_type', (req, res) => {


  con = mysql.createConnection({
    host: "localhost",
    user: "root",
    password: "",
    database: "leoni_lines"
  });

  con.connect(function (err) {
    if (err) throw err;
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

});


app.get('/mh2/:line_number/:state/:segment/:RT_RATIO/:START_TIM/:V_type', (req, res) => {


  con = mysql.createConnection({
    host: "localhost",
    user: "root",
    password: "",
    database: "leoni_lines"
  });

  con.connect(function (err) {
    if (err) throw err;
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



});





app.post('/:line_number/:state/:RT_RATIO/:START_TIME', function (req, res) {
  line_state = req.params;
  res.setHeader("Access-Control-Allow-Origin", "*")
  res.type('text/plain');
  console.log(req.params);

  res.send(line_state);


});

app.get('/mh1', (req, res) => {

  con = mysql.createConnection({
    host: "localhost",
    user: "root",
    password: "",
    database: "leoni_lines"
  });

  con.connect(function (err) {
    if (err) throw err;
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



});
app.get('/MH2', (req, res) => {

  con = mysql.createConnection({
    host: "localhost",
    user: "root",
    password: "",
    database: "leoni_lines"
  });

  con.connect(function (err) {
    if (err) throw err;
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



});
app.get('/apperance', (req, res) => {
  con = mysql.createConnection({
    host: "localhost",
    user: "root",
    password: "",
    database: "leoni_lines"
  });

  con.connect(function (err) {
    if (err) throw err;
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

});
app.get('/Vordawagen_state/:V_type', (req, res) => {

  con = mysql.createConnection({
    host: "localhost",
    user: "root",
    password: "",
    database: "leoni_lines"
  });

  con.connect(function (err) {
    if (err) throw err;
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
});

app.get('/mh1/:line_number/:state/:RT_RATIO/:START_TIM/:V_type', (req, res) => {


  con = mysql.createConnection({
    host: "localhost",
    user: "root",
    password: "",
    database: "leoni_lines"
  });

  con.connect(function (err) {
    if (err) throw err;
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

});


app.get('/mh2/:line_number/:state/:RT_RATIO/:START_TIM/:V_type', (req, res) => {


  con = mysql.createConnection({
    host: "localhost",
    user: "root",
    password: "",
    database: "leoni_lines"
  });

  con.connect(function (err) {
    if (err) throw err;
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

app.get('/:line_number/:elapsed', (req, res) => {

  con = mysql.createConnection({
    host: "localhost",
    user: "root",
    password: "",
    database: "leoni_lines"
  });

  con.connect(function (err) {
   

    if (err) throw err;
    console.log("Connected! /:line_number/:elapsed'");
    con.query("SELECT A_DURATION from mh1 where `LINE_NUMBER` = '" + req.params.line_number + "'", function (err, result, fields) {
      if (err) throw err;

 let old_activeduration
    let new_activeduration

      res.setHeader("Access-Control-Allow-Origin", "*")
      res.setHeader("Access-Control-Allow-Credentials", "true");
      res.setHeader("Access-Control-Max-Age", "1800");
      res.setHeader("Access-Control-Allow-Headers", "content-type");
      res.setHeader("Access-Control-Allow-Methods", "PUT, POST, GET, DELETE, PATCH, OPTIONS");
      res.type('text/plain');
      old_activeduration = result[0].A_DURATION;
      // res.send("elapsed :"msToTime(req.params.elapsed )+"  old :  "+ old_activeduration)

      new_activeduration = addTimes(old_activeduration, msToTime(req.params.elapsed))

      con.query("UPDATE `mh1` SET `A_DURATION` = '" + new_activeduration + "' WHERE `mh1`.`LINE_NUMBER` = '" + req.params.line_number + "'", function (err, result, fields) {
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
   
    


  });

});


