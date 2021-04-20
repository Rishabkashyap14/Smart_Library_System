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
  res.sendFile(path.join(__dirname, './remove_book.html'));
});

app.get('/saveData', (req, res) => {
  res.sendFile(path.join(__dirname, './home.html'));
});

const removeBook = (Book_id, Book_name) => {
  const compiler = "g++";
  const version = "-std=c++11";
  const out ="-o";
  const infile = "remove_code_runner.cpp";
  const otherfile = "Book.cpp";
  const utilities = "Utilities.cpp"
  const outfile = "remove_code_runner.out";
  const flags = "-lsqlite3"

  execFile(compiler, [version,infile, otherfile, utilities, out, outfile, flags], (err, stdout, stderr) => {
    if (err) {
      console.log(err);
    } else {
      let executable = `./${outfile}`;
      execFile(executable ,[Book_id, Book_name],(err, stdout, stderr) => {
        if (err) {
          console.log(err);
        } else {
          execFile("echo", [Book_id, Book_name], { shell: true }, (err, stdout, stderr) => {
            if (err) {
              console.log(err);
            } else {
              console.log(`what is printed to the console: ${stdout}`);
            }
          });
        }
      })
    }
  })
};

const displayBook = async(Book_id) => {
  const compiler = "g++";
  const version = "-std=c++11";
  const out ="-o";
  const infile = "displayBook_code_runner.cpp";
  const otherfile = "Book.cpp";
  const utilities = "Utilities.cpp"
  const outfile = "displayBook_code_runner.out";
  const flags = "-lsqlite3"
  var output;

  await execFile(compiler, [version,infile, otherfile, utilities, out, outfile, flags])
      let executable = `./${outfile}`;
      const { stdout, stderr } = await execFile(executable ,[Book_id])
              console.log(`what is printed to the console: ${stdout}`);
              return(stdout);
};

app.get('/getData', async (req, res) => {
  const { Book_id } = req.query;
  console.log(Book_id, "HEHEHEHEHEHEHEHEHEH");
  let output = await displayBook(Book_id);
  output = (output.split("\n"));
  let obj = {}
  output.filter(line => line!='')
  output.map(line => { x = line.split("="); obj[x[0]?x[0].trim(): x[0]] = x[1]?x[1].trim(): x[1]});
  console.log(obj);
  res.json({output : obj})
})

app.post('/saveData', (req, res) => {
    const { Book_id, Book_name } = req.body;
    removeBook(Book_id, Book_name);
    res.redirect("/saveData")
})

app.listen(8080, function() {
  console.log('Server running at http://127.0.0.1:8080/');
});