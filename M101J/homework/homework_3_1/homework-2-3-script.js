// Original //

student_id_grades_cursor = db.students.find ();

while (student_id_grades_cursor.hasNext ()) 
{
	current_cursor_grade = student_id_grades_cursor.next ();
	min_homework_grade   = null;
	
	for (var idx_score = 0; i < current_cursor_grade["scores"]; i++)
	{
		if (current_cursor_grade["scores"][idx_score]["type"] == "homework")
		{
			if ((min_homework_grade == null) || (min_homework_grade > current_cursor_grade["scores"][idx_score]["score"]))
			{
				min_homework_grade = current_cursor_grade["scores"][idx_score]["score"];
			}
		}
	}
	
	db.students.update ({"_id" : current_cursor_grade["_id"]}, {$pull : {"scores" : {"type" : "homework", "score" : min_homework_grade}}});
}

// Exec - mongo shell //

student_id_grades_cursor = db.students.find (); null;

while (student_id_grades_cursor.hasNext ()) {
	current_cursor_grade = student_id_grades_cursor.next (); null;
	min_homework_grade   = null;
	
	for (var idx_score = 0; idx_score < current_cursor_grade["scores"].length; idx_score++) {
		if (current_cursor_grade["scores"][idx_score]["type"] == "homework") {
			if ((min_homework_grade == null) || (min_homework_grade > current_cursor_grade["scores"][idx_score]["score"])) {
				min_homework_grade = current_cursor_grade["scores"][idx_score]["score"];
			}
		}
	}
	
	db.students.update ({"_id" : current_cursor_grade["_id"]}, {$pull : {"scores" : {"type" : "homework", "score" : min_homework_grade}}}); null;
}


