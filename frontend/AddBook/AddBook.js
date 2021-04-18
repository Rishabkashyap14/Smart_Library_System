var express = require('express');
const path = require('path');
var bodyParser = require('body-parser');
const { execFile } = require('child_process');

var app = express();
app.use(bodyParser());
app.use(express.static(path.join(__dirname, '/')));

app.get('', (req, res) => {
  res.sendFile(path.join(__dirname, './test.html'));
});

app.get('/saveData', (req, res) => {
  res.sendFile(path.join(__dirname, './home.html'));
});

const addBook = (Book_id, Book_name, Author, Book_Description, Copies) => {
  const compiler = "g++";
  const version = "-std=c++11";
  const out ="-o";
  const infile = "code-runner.cpp";
  const otherfile = "Book.cpp";
  const utilities = "Utilities.cpp"
  const outfile = "code-runner.out";
  const flags = "-lsqlite3"

  execFile(compiler, [version,infile, otherfile, utilities, out, outfile, flags], (err, stdout, stderr) => {
    if (err) {
      console.log(err);
    } else {
      let executable = `./${outfile}`;
      execFile(executable ,[Book_id, Book_name, Author, Book_Description, Copies],(err, stdout, stderr) => {
        if (err) {
          console.log(err);
        } else {
          execFile("echo", [Book_id, Book_name, Author, Book_Description, Copies], { shell: true }, (err, stdout, stderr) => {
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

app.post('/saveData', (req, res) => {
    const { Book_id, Book_name, Author, Book_Description, Copies } = req.body;
    addBook(Book_id, Book_name, Author, Book_Description, Copies);
    res.redirect("/saveData")
})

app.listen(8080, function() {
  console.log('Server running at http://127.0.0.1:8080/');
});

