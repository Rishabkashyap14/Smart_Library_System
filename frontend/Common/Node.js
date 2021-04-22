var express = require('express');
const path = require('path');
const sqlite3 = require('sqlite3').verbose();
var bodyParser = require('body-parser');
const { execFile } = require('child_process');
const util = require('util');
//const { execFile_1 : exec } = require('child_process');
const execFile_1 = util.promisify(execFile);


var app = express();
app.use(bodyParser());
app.use(express.static(path.join(__dirname, '/')));

/*Declarations of all get tags*/
app.get('', (req, res) => {
  res.sendFile(path.join(__dirname, './home.html'));
});

app.get('/Signup', (req, res) => {
  res.sendFile(path.join(__dirname, './home.html'));
});

app.get('/Home', (req, res) => {
  res.sendFile(path.join(__dirname, './home.html'));
});

app.get('/Issue', (req, res) => {
  res.sendFile(path.join(__dirname, './home.html'));
});

app.get('/Return', (req, res) => {
  res.sendFile(path.join(__dirname, './CalcFine.html'));
});

app.get('/Add', (req, res) => {
  res.sendFile(path.join(__dirname, './home.html'));
});

app.get('/Remove', (req, res) => {
  res.sendFile(path.join(__dirname, './home.html'));
});

app.get('/calcFine', (req, res) => {
  res.sendFile(path.join(__dirname, './home.html'));
});


/* Functions */
const createUser = (User_Id, Name, Password, Email) => {
	const compiler = "g++";
  	const version = "-std=c++11";
  	const out ="-o";
  	const infile = "user_code_runner.cpp";
  	const otherfile = "User.cpp";
  	const utilities = "Utilities.cpp"
  	const outfile = "user_code_runner.out";
  	const flags = "-lsqlite3"
  
  execFile(compiler, [version,infile, otherfile, utilities, out, outfile, flags], (err, stdout, stderr) => {
    if (err) {
      console.log(err);
    } else {
      let executable = `./${outfile}`;
      execFile(executable ,[User_Id, Name, Password, Email],(err, stdout, stderr) => {
        if (err) {
          console.log(err);
        } else {
          execFile("echo", [User_Id, Name, Password, Email], { shell: true }, (err, stdout, stderr) => {
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

const issueBook = (Book_name, User_Id) => {
	const compiler = "g++";
  	const version = "-std=c++11";
  	const out ="-o";
  	const infile = "issue_code_runner.cpp";
  	const otherfile1 = "User.cpp";
  	const otherfile2 = "Book.cpp";
  	const otherfile3 = "BookRelatedOperations.cpp";
  	const utilities = "Utilities.cpp"
  	const outfile = "issue_code_runner.out";
  	const flags = "-lsqlite3";
  
  execFile(compiler, [version,infile, otherfile1, otherfile2, otherfile3, utilities, out, outfile, flags], (err, stdout, stderr) => {
    if (err) {
      console.log(err);
    } else {
      let executable = `./${outfile}`;
      execFile(executable ,[Book_name, User_Id],(err, stdout, stderr) => {
        if (err) {
          console.log(err);
        } else {
          execFile("echo", [Book_name, User_Id], { shell: true }, (err, stdout, stderr) => {
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

const addBook = (Book_id, Book_name, Author, Book_Description, Copies) => {
  const compiler = "g++";
  const version = "-std=c++11";
  const out ="-o";
  const infile = "code-runner.cpp";
  const otherfile = "Book.cpp";
  const utilities = "Utilities.cpp"
  const outfile = "code-runner.out";
  const flags = "-lsqlite3"
  var output;

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
              output = stdout;
            }
          });
        }
      })
    }
  })
};

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

  await execFile_1(compiler, [version,infile, otherfile, utilities, out, outfile, flags])
      let executable = `./${outfile}`;
      const { stdout, stderr } = await execFile_1(executable ,[Book_id])
              console.log(`what is printed to the console: ${stdout}`);
              return(stdout);
};

const getFine = (User_id, Book_name) => {
	const compiler = "g++";
  	const version = "-std=c++11";
  	const out ="-o";
  	const infile = "calcFees_code_runner.cpp";
  	const otherfile1 = "User.cpp";
  	const otherfile2 = "Book.cpp";
  	const otherfile3 = "BookRelatedOperations.cpp";
  	const utilities = "Utilities.cpp"
  	const outfile = "calcFees_code_runner.out";
  	const flags = "-lsqlite3";
  
  execFile(compiler, [version, infile, otherfile1, otherfile2, otherfile3, utilities, out, outfile, flags], (err, stdout, stderr) => {
    if (err) {
      console.log(err);
    } else {
      let executable = `./${outfile}`;
      execFile(executable ,[User_id, Book_name],(err, stdout, stderr) => {
        if (err) {
          console.log(err);
        } else {
          execFile("echo", [User_id, Book_name], { shell: true }, (err, stdout, stderr) => {
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
  
  await execFile_1(compiler, [version,infile, otherfile1, otherfile2, otherfile3, utilities, out, outfile, flags])
      let executable = `./${outfile}`;
      const { stdout, stderr } = await execFile_1(executable ,[User_id])
              console.log(`what is printed to the console: ${stdout}`);
              return(stdout);
};

/* get functions for printing info*/
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


app.get('/getData', async (req, res) => {
  const { Book_id } = req.query;
  let output = await displayBook(Book_id);
  output = (output.split("\n"));
  let obj = {}
  output.filter(line => line!='')
  output.map(line => { x = line.split("="); obj[x[0]?x[0].trim(): x[0]] = x[1]?x[1].trim(): x[1]});
  console.log(obj);
  res.json({output : obj})
})



/*Posting Function data online*/
app.post('/Signup', (req, res) => {
	console.log(req.body);
    const { User_Id, Name, Password, Email } = req.body;
    console.log(Name);
    console.log(Password);
    console.log(Email);
    createUser(User_Id, Name, Password, Email);
    res.redirect("/Signup");
})

app.post('/Issue', (req, res) => {
    const { Book_name, User_Id } = req.body;
    console.log(Book_name);
    console.log(User_Id);
    issueBook(Book_name, User_Id);
    res.redirect("/Issue");
})

app.post('/Return', (req, res) => {
    const { User_Id, Book_name } = req.body;
    returnBook(User_Id, Book_name);
    res.redirect("/Return");
})


app.post('/Add', (req, res) => {
    const { Book_id, Book_name, Author, Book_Description, Copies } = req.body;
    addBook(Book_id, Book_name, Author, Book_Description, Copies);
    console.log("Added book successfully");
    res.redirect("/Add");
})

app.post('/Remove', (req, res) => {
    const { Book_id, Book_name } = req.body;
    removeBook(Book_id, Book_name);
    res.redirect("/Remove");
})

app.post('/calcFine', (req, res) => {
    const { User_id, Book_name } = req.body;
    getFine(User_id, Book_name);
    res.redirect("/calcFine");
})

app.post('/Home', (req, res) => {
    res.redirect("/Home")
})

app.listen(8080, function() {
  console.log('Server running at http://127.0.0.1:8080/');
});
