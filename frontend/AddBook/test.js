/* Set the width of the side navigation to 250px */
function openNav() {
  document.getElementById("mySidenav").style.width = "250px";
}

/* Set the width of the side navigation to 0 */
function closeNav() {
  document.getElementById("mySidenav").style.width = "0";
}

Module.onRuntimeInitialized = _ => {
  const  addBookCpp = Module.cwrap('add_book');
  addBookCpp();
 };

var book_id=getElementById("Book_id");
var book_name=getElementById("Book_name");
var author=getElementById("Author");
var copies=getElementById("Copies");
var book_desc=getElementById("Book_Description");

var db = openDatabase('book.db', '1.0', 'my first database', 2 * 1024 * 1024);
var db = openDatabase('mydb', '1.0', 'my first database', 2 * 1024 * 1024);
db.transaction(function (tx) {
  tx.executeSql('CREATE TABLE BOOKS(Book_id NUMERIC(10) NOT NULL,Book_name VARCHAR(50) NOT NULL,Author CHAR(20) NOT NULL,Description VARCHAR(100),Copies NUMERIC(10) NOT NULL,PRIMARY KEY (Book_id))');
  tx.executeSql("INSERT INTO BOOKS VALUES(1000000001, 'The Wheel of Time - The Eye of the World', 'Robert Jordan', 'The wheel weaves as the wheel wills', 10)");
});
