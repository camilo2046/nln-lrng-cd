db.posts.aggregate ([
						// Unwind the comments array
						{"$unwind" : "$comments"},

						// Count comments per author
						{"$group" : {"_id" : "$comments.author", "count_comments" : {"$sum" : 1}}},

						// Sort the count ascending/descending 
						{"$sort" : {"count_comments" : -1}},
//						{"$sort" : {"count_comments" : 1}},

						// Get only one
						{"$limit" : 1}
]);

db.posts.aggregate ([
						// Unwind the comments array
						{"$unwind" : "$comments"},

						// Count comments per author
						{"$group" : {"_id" : "$comments.author", "count_comments" : {"$sum" : 1}}},

						// Get the max/min count of comments
//						{"$group" : {"_id" : null, "max_count_comments" : {"$max" : "$count_comments"}}}
						{"$group" : {"_id" : null, "min_count_comments" : {"$min" : "$count_comments"}}}
]);



