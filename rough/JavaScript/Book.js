var sqlite3 = require('sqlite3').verbose();

var db = new sqlite3.Database('book.db');

db.serialize(function(){
	
	var stmt = db. prepare("INSERT INTO BOOKS VALUES(?, ?, ?, ?, ?)");
	stmt.run(1000000004, "Matilda", "Roald Dahl", 25, "bleh");

	db.each("SELECT * FROM BOOKS;", function(err, row)
	{
		console.log("Book_id:"+row.Book_id);
	});
});

db.close();

