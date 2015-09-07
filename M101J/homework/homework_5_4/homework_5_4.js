db.zips.aggregate ([
					  // Extract first character of the city
					  {"$project" : {"_id" : false, "first_char" : {"$substr" : ["$city", 0, 1]}, "pop" : true}},
					  
					  // Get cities which start with a digit [0-9]
					  {"$match" : {"first_char" : {"$in" : ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"]}}},
					  
					  // Get the total population
					  {"$group" : {"_id" : null, "sum_pop" : {"$sum" : "$pop"}}}
]);

