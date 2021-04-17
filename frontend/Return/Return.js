var express = require('express');
const path = require('path');
const sqlite3 = require('sqlite3').verbose();
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

/*
const getFees = (User_Id) => {
  let db = new sqlite3.Database('book.db', (err) => {
  if (err) {
    console.error(err.message);
  }
  console.log('Connected to the book database.');
});
  db.get(`SELECT Fees FROM USERS WHERE User_id=?`,[User_Id], (err, row) => {
    if (err) {
      console.error(err.message);
    }
    console.log(row.Fees);
  });
  db.close((err) => {
  if (err) {
    console.error(err.message);
  }
  console.log('Close the database connection.');
});
};
*/

/*
const getFees = (User_Id) => {
	let db = new sqlite3.Database('./book.db');
	let sql = `SELECT Fees FROM TRANSACTIONS WHERE User_id = ?`;
	let Fees=0;
	
	db.get(sql, [User_Id], (err, row) => {
		if(err) {
			return console.error(err.message);
		}
	return row
		? console.log(row.Fees)
		: console.log(`No Fees found with the user`);
	db.close();
});
*/

app.post('/saveData', (req, res) => {
    const { User_Id, Book_name } = req.body;
    returnBook(User_Id, Book_name);
    getFees(User_Id);
    res.redirect("/saveData");
})

app.listen(8082, function() {
  console.log('Server running at http://127.0.0.1:8082/');
});
