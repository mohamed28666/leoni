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
    con.query("UPDATE `mh1` SET `DISPLAY_LINE` = '"+req.params.state+"' WHERE (`mh1`.`V_Type` like '%"+req.params.V_type+"%' and `mh1`.`Segment` like '%"+req.params.segment+"%')", function (err, result, fields) {
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
    con.query("UPDATE `mh2` SET `DISPLAY_LINE` = '"+req.params.state+"' WHERE (`mh2`.`V_Type` like '%"+req.params.V_type+"%' and `mh2`.`Segment` like '%"+req.params.segment+"%')", function (err, result, fields) {
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
    console.log("Connected!");
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
    console.log("Connected!");
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
    console.log("Connected!");
    con.query("SELECT DISPLAY_LINE FROM MH1 where V_type like'%"+req.params.V_type+"%'", function (err, result, fields) {
      if (err) throw err;
      res.setHeader("Access-Control-Allow-Origin", "*")
      res.setHeader("Access-Control-Allow-Credentials", "true");
      res.setHeader("Access-Control-Max-Age", "1800");
      res.setHeader("Access-Control-Allow-Headers", "content-type");
      res.setHeader("Access-Control-Allow-Methods", "PUT, POST, GET, DELETE, PATCH, OPTIONS");
      res.type('text/plain');
      res.send(result)

    });
  });});

