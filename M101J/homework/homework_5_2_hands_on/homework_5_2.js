db.small_zips.aggregate ([
							// Get cities in California (CA) and New York (NY) 
							{"$match" : {"state" : {"$in" : ["CA", "NY"]}}},
							
							// Get city population (A city might have multiple zip codes)
							{"$group" : {"_id" : {"city" : "$city"}, "city_pop" : {"$sum" : "$pop"}}},
							
							// Get cities with populations over 25000
							{"$match" : {"city_pop" : {"$gt" : 25000}}},

							// Calculate the average population 
							{"$group" : {"_id" : null, "avg_pop" : {"$avg" : "$city_pop"}}}

]);
