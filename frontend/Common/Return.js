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
  return 1;
};


const getFees = (User_Id) => {
  	let db = new sqlite3.Database('book.db', (err) => {
 		if (err) {
    		console.error(err.message);
  		}
  		console.log('Connected to the book database.');
	});
  	let sql =`SELECT Fees FROM USERS WHERE User_id=?`;
  	db.all(sql, 	[User_Id], (err, row) => {
    	if (err) {
      		console.error(err.message);
    	}
    	console.log(row.Fees);
    	console.log('Inserted fees successfully');
  	});
  	db.close((err) => {
  		if (err) {
    		console.error(err.message);
  		}
  	console.log('Close the database connection.');
	});
};

// open the database
let db = new sqlite3.Database('./book.db');

let sql = `SELECT Author FROM BOOKS ORDER BY Book_id`;

db.all(sql, [], (err, rows) => {
        if (err)
        {
                throw err;
        }
        rows.forEach((row) => {
                console.log(row.Author);
        });
});

// close the database connection
db.close();

app.post('/saveData', (req, res) => {
    const { User_Id, Book_name } = req.body;
    if(returnBook(User_Id, Book_name))
    {
    	getFees(User_Id);
    }
    res.redirect("/saveData");
})

app.listen(8082, function() {
  console.log('Server running at http://127.0.0.1:8082/');
});
