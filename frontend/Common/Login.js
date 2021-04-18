var express = require('express');
const path = require('path');
var bodyParser = require('body-parser');
const { execFile } = require('child_process');

var app = express();
app.use(bodyParser());
app.use(express.static(path.join(__dirname, '/')));
	
app.get('', (req, res) => {
  res.sendFile(path.join(__dirname, './Signup.html'));
});

app.get('/saveData', (req, res) => {
  res.sendFile(path.join(__dirname, './home.html'));
});


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

app.post('/saveData', (req, res) => {
	console.log(req.body);
    const { User_Id, Name, Password, Email } = req.body;
    console.log(Name);
    console.log(Password);
    console.log(Email);
    createUser(User_Id, Name, Password, Email);
    res.redirect("/saveData");
})

app.listen(8082, function() {
  console.log('Server running at http://127.0.0.1:8082/');
});


/* 
function openNav() {
  document.getElementById("mySidenav").style.width = "250px";
}

function closeNav() {
  document.getElementById("mySidenav").style.width = "0";
}
const button = document.querySelector('.btn')
const form   = document.querySelector('.form')

button.addEventListener('click', function() {
   form.classList.add('form--no') 
});*/

