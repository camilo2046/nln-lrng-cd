// Original //

student_id_grades_cursor = db.grades.find ({"type" : "homework"}, {"_id" : true, "score" : true, "student_id" : true}).sort ({"student_id" : 1, "score" : 1});

current_cursor_grade     = student_id_grades_cursor.next ();
last_student_id          = current_cursor_grade["student_id"];
db.grades.remove ({"_id" : current_cursor_grade["_id"]});

while (student_id_grades_cursor.hasNext ()) 
{
	current_cursor_grade = student_id_grades_cursor.next ();

	if (current_cursor_grade["student_id"] != last_student_id) 
	{
		db.grades.remove ({"_id" : current_cursor_grade["_id"]});
	}
	
	last_student_id      = current_cursor_grade["student_id"];
}  


// Exec - mongo shell //

student_id_grades_cursor = db.grades.find ({"type" : "homework"}, {"_id" : true, "score" : true, "student_id" : true}).sort ({"student_id" : 1, "score" : 1}); null;

current_cursor_grade     = student_id_grades_cursor.next (); null;
last_student_id          = current_cursor_grade["student_id"];
db.grades.remove ({"_id" : current_cursor_grade["_id"]});

while (student_id_grades_cursor.hasNext ()) {
	current_cursor_grade = student_id_grades_cursor.next (); null;

	if (current_cursor_grade["student_id"] != last_student_id) {
		db.grades.remove ({"_id" : current_cursor_grade["_id"]});
	}
	
	last_student_id      = current_cursor_grade["student_id"];
}  

