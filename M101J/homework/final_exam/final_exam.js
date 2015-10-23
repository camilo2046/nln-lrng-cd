// Question 1 //

// Shell: mongorestore -d enron -c messages --drop dump/enron/messages.bson

use enron;
db.messages.count ();

// Without Aggregation Framework
db.messages.count ({"headers.From" : "andrew.fastow@enron.com", "headers.To" : "john.lavorato@enron.com"});
db.messages.count ({"headers.From" : "andrew.fastow@enron.com", "headers.To" : "jeff.skilling@enron.com"});

// With Aggregation Framework
db.messages.aggregate ([
                           {"$match" : {"headers.From" : "andrew.fastow@enron.com"}},
                           {"$unwind" : "$headers.To"},
                           {"$match" : {"headers.To" : "john.lavorato@enron.com"}},
                           {"$group" : {"_id" : null, "count_messages" : {"$sum" : 1}}}
                       ]);
db.messages.aggregate ([
                           {"$match" : {"headers.From" : "andrew.fastow@enron.com"}},
                           {"$unwind" : "$headers.To"},
                           {"$match" : {"headers.To" : "jeff.skilling@enron.com"}},
                           {"$group" : {"_id" : null, "count_messages" : {"$sum" : 1}}}
                       ]);

// Question 2 //

db.messages.aggregate ([
                           {"$project" : {"_id" : "$_id", "_from" : "$headers.From", "_to" : "$headers.To"}},
                           {"$unwind" : "$_to"},
                           {"$group" : {"_id" : {"_id" : "$_id", "_from" : "$_from"}, "_to" : {"$addToSet" : "$_to"}}},
                           {"$unwind" : "$_to"},
                           {"$group" : {"_id" : {"_from" : "$_id._from", "_to" : "$_to"}, "count_messages" : {"$sum" : 1}}},
                           {"$sort" : {"count_messages" : -1, "_id._to" : 1}},
                           {"$group" : {"_id" : null , "max_to" : {"$first" : "$_id._to"}, "max_from" : {"$first" : "$_id._from"}}}
                       ]);

db.messages.aggregate ([
                           {"$project" : {"_id" : "$_id", "_from" : "$headers.From", "_to" : "$headers.To"}},
                           {"$unwind" : "$_to"},
                           {"$group" : {"_id" : {"_id" : "$_id", "_from" : "$_from"}, "_to" : {"$addToSet" : "$_to"}}},
                           {"$unwind" : "$_to"},
                           {"$group" : {"_id" : {"_from" : "$_id._from", "_to" : "$_to"}, "count_messages" : {"$sum" : 1}}},
                           {"$sort" : {"count_messages" : -1}},
                           {"$limit" : 1}
                       ]);

// Question 3

db.messages.find ({"headers.Message-ID" : "<8147308.1075851042335.JavaMail.evans@thyme>"}).pretty ();
db.messages.update ({"headers.Message-ID" : "<8147308.1075851042335.JavaMail.evans@thyme>"}, {"$push" : {"headers.To" : "mrpotatohead@10gen.com"}});

// Question 4 (JAVA based)

// In Shell: mongoimport -d blog -c posts --drop posts.json
// In Shell: Run question_4 mvn project (with BlogController as main class): mvn compile exec:java -Dexec.mainClass=course.BlogController

// Question 5

use m101;

var num_data_test_a = 10;
var num_data_test_b = 10;
var num_data_test_c = 10;

// _id index - NO

db.stuff.drop ();

for (var i = 0; i < num_data_test_a; i++) {

    for (var j = 0; j < num_data_test_b; j++) {

        for (var k = 0; k < num_data_test_c; k++) {

            db.stuff.insert ({"a" : i, "b" : j, "c" : k});
        }
    }
}

db.stuff.explain ().find ({'a':{'$lt':10000}, 'b':{'$gt': 5000}}, {'a':1, 'c':1}).sort ({'c':-1});

// a1_b1 index - YES

db.stuff.drop ();

for (var i = 0; i < num_data_test_a; i++) {

    for (var j = 0; j < num_data_test_b; j++) {

        for (var k = 0; k < num_data_test_c; k++) {

            db.stuff.insert ({"a" : i, "b" : j, "c" : k});
        }
    }
}

db.stuff.createIndex ({"a" : 1, "b" : 1});
db.stuff.explain ().find ({'a':{'$lt':10000}, 'b':{'$gt': 5000}}, {'a':1, 'c':1}).sort ({'c':-1});

// a1_c1 index - YES

db.stuff.drop ();

for (var i = 0; i < num_data_test_a; i++) {

    for (var j = 0; j < num_data_test_b; j++) {

        for (var k = 0; k < num_data_test_c; k++) {

            db.stuff.insert ({"a" : i, "b" : j, "c" : k});
        }
    }
}

db.stuff.createIndex ({"a" : 1, "c" : 1});
db.stuff.explain ().find ({'a':{'$lt':10000}, 'b':{'$gt': 5000}}, {'a':1, 'c':1}).sort ({'c':-1});

// c1_index - YES

db.stuff.drop ();

for (var i = 0; i < num_data_test_a; i++) {

    for (var j = 0; j < num_data_test_b; j++) {

        for (var k = 0; k < num_data_test_c; k++) {

            db.stuff.insert ({"a" : i, "b" : j, "c" : k});
        }
    }
}

db.stuff.createIndex ({"c" : 1});
db.stuff.explain ().find ({'a':{'$lt':10000}, 'b':{'$gt': 5000}}, {'a':1, 'c':1}).sort ({'c':-1});

// a1_b1_c-1 index - YES

db.stuff.drop ();

for (var i = 0; i < num_data_test_a; i++) {

    for (var j = 0; j < num_data_test_b; j++) {

        for (var k = 0; k < num_data_test_c; k++) {

            db.stuff.insert ({"a" : i, "b" : j, "c" : k});
        }
    }
}

db.stuff.createIndex ({"a" : 1, "b" : 1, "c" : -1});
db.stuff.explain ().find ({'a':{'$lt':10000}, 'b':{'$gt': 5000}}, {'a':1, 'c':1}).sort ({'c':-1});

// Question 6 (Theory)

// Question 7

// In Shell: mongoimport -d m101 -c albums --drop albums.json
// In Shell: mongoimport -d m101 -c images --drop images.json

use m101;

db.images.find ({"tags" : "sunrises"}).count ();

db.albums.createIndex ({"images" : 1});

var cursor_images = db.images.find ({}, {"_id" : true});

while (cursor_images.hasNext ()) {
	
	current_cursor_image = cursor_images.next ();
	print (current_cursor_image["_id"]);
	
	var count_cursor_albums = db.albums.find ({"images" : current_cursor_image["_id"]}).count ();
	
	if (count_cursor_albums <= 0) {
		
		db.images.remove ({"_id" : current_cursor_image["_id"]});
	}
}

db.images.find ().count ();
db.images.find ({"tags" : "sunrises"}).count ();

// Question 8 (JAVA based)

// In Shell: Run question_8 mvn project (with InsertTest as main class): mvn compile exec:java -Dexec.mainClass=course.InsertTest

// Question 9 (Theory)

// Question 10 (Theory)
