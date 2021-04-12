import cgi
form = cgi.FieldStorage()
book = form.getvalue(book_id);
f = open("demofile2.txt", "a")
f.write(str(book))
f.close()
