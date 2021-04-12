const sqlite3 = require('sqlite3').verbose();
let db = new sqlite3.Database('/home/rishab/rughwork/JavaScript/book.db', sqlite3.OPEN_READWRITE, (err) => {
	if (err) {
		console.error(err.message);
  	}
	console.log('Connected to the book.db database.');
});

db.serialize(() => {
	db.each(`SELECT * FROM BOOKS`, (err, row) => {
		if (err) {
			console.error(err.message);
		}
		console.log(row.Book_id + "\t" + row.Book_name);
	});
});

