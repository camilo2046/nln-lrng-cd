db.grades.aggregate ([
						// Unwind the scores array
						{"$unwind" : "$scores"},
						
						// Dont include quizzes
						{"$match" : {"scores.type" : {"$ne" : "quiz"}}},
						
						// Get student class average
						{"$group" : {"_id" : {"student_id" : "$student_id", "class_id" : "$class_id"}, "avg_student_score" : {"$avg" : "$scores.score"}}},
						
						// Get class average
						{"$group" : {"_id" : {"class_id" : "$_id.class_id"}, "avg_class_score" : {"$avg" : "$avg_student_score"}}},
						
						// Sort the count ascending/descending 
						{"$sort" : {"avg_class_score" : -1}},
						
						// Get only one
						{"$limit" : 1}
]);









