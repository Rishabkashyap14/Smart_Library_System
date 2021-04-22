var express = require('express');
const path = require('path');
var bodyParser = require('body-parser');
const { execFile : exec } = require('child_process');
const util = require('util');
const execFile = util.promisify(exec);

var app = express();
app.use(bodyParser());
app.use(express.static(path.join(__dirname, '/')));

app.get('', (req, res) => {
  res.sendFile(path.join(__dirname, './Display_fees.html'));
});


app.get('/saveData', (req, res) => {
  res.sendFile(path.join(__dirname, './home.html'));
});

const displayFees = async (User_id) => {
	const compiler = "g++";
  	const version = "-std=c++11";
  	const out ="-o";
  	const infile = "displayFees_code_runner.cpp";
  	const otherfile1 = "User.cpp";
  	const otherfile2 = "Book.cpp";
  	const otherfile3 = "BookRelatedOperations.cpp";
  	const utilities = "Utilities.cpp"
  	const outfile = "displayFees_code_runner.out";
  	const flags = "-lsqlite3";
  
  await execFile(compiler, [version,infile, otherfile1, otherfile2, otherfile3, utilities, out, outfile, flags])
      let executable = `./${outfile}`;
      const { stdout, stderr } = await execFile(executable ,[User_id])
              console.log(`what is printed to the console: ${stdout}`);
              return(stdout);
};

app.get('/displayFees', async (req, res) => {
  const { User_id } = req.query;
  let output = await displayFees(User_id);
  output = (output.split("\n"));
  let obj = {}
  output.filter(line => line!='')
  output.map(line => { x = line.split("="); obj[x[0]?x[0].trim(): x[0]] = x[1]?x[1].trim(): x[1]});
  console.log(obj);
  res.json({output : obj})
})

app.listen(8080, function() {
  console.log('Server running at http://127.0.0.1:8080/');
});
