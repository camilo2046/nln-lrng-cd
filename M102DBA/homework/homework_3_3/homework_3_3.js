db.products.createIndex ({"for" : 1});

// Q1
db.products.find ({"for" : "ac3"});
db.products.find ({"for" : "ac3"}).count ();

// Q2
var exp = db.products.explain ("executionStats");
exp.find ({"for" : "ac3"});

// Q3
var exp = db.products.explain ("executionStats");
exp.find ({"for" : "ac3"});
