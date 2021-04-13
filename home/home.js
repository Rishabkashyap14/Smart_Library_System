var express = require('express');
const path = require('path');
var bodyParser = require('body-parser');
const { execFile } = require('child_process');

var app = express();
app.use(bodyParser()); 

app.get('', (req, res) => {
  res.sendFile(path.join(__dirname, './home.html'));
})

app.listen(8080, function() {
  console.log('Server running at http://127.0.0.1:8080/');
});

