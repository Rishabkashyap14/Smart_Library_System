//myNodeFile.js
const { exec } = require("child_process");
exec("./myExecutable", (error, stdout, stderr) => console.log(stdout));
