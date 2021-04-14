var express = require('express');
const path = require('path');
var bodyParser = require('body-parser');
const { execFile } = require('child_process');

var app = express();
app.use(bodyParser());
app.use(express.static(path.join(__dirname, '/')));
	
app.get('', (req, res) => {
  res.sendFile(path.join(__dirname, './Return.html'));
});

app.get('/saveData', (req, res) => {
  res.sendFile(path.join(__dirname, './home.html'));
});


const returnBook = (User_Id, Book_name) => {
	const compiler = "g++";
  	const version = "-std=c++11";
  	const out ="-o";
  	const infile = "return_code_runner.cpp";
  	const otherfile1 = "User.cpp";
  	const otherfile2 = "Book.cpp";
  	const otherfile3 = "BookRelatedOperations.cpp";
  	const utilities = "Utilities.cpp"
  	const outfile = "return_code_runner.out";
  	const flags = "-lsqlite3";
  
  execFile(compiler, [version, infile, otherfile1, otherfile2, otherfile3, utilities, out, outfile, flags], (err, stdout, stderr) => {
    if (err) {
      console.log(err);
    } else {
      let executable = `./${outfile}`;
      execFile(executable ,[User_Id, Book_name],(err, stdout, stderr) => {
        if (err) {
          console.log(err);
        } else {
          execFile("echo", [User_Id, Book_name], { shell: true }, (err, stdout, stderr) => {
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
    const { User_Id, Book_name } = req.body;
    console.log(User_Id);
    console.log(Book_name);
    returnBook(User_Id, Book_name);
    res.redirect("/saveData");
})

app.listen(8082, function() {
  console.log('Server running at http://127.0.0.1:8082/');
});
