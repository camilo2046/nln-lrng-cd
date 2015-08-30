use m101;

var num_documents = 100000;

for (var i = 0; i < num_documents; i++) {
	
	db.products.insert ({"sku" : i, "price" : i, "description" : "Description " + i, "category" : i % 15, "brand" : i % 30, "reviews" : [{"author" : "Author " + (i % 30), "content" : "Content " + (i % 1000)}, {"author" : "Author " + (i % 300), "content" : "Content " + (i % 10000)}]});
}

db.products.createIndex ({"sku" : 1}, {"unique" : true});
db.products.createIndex ({"price" : -1});
db.products.createIndex ({"description" : 1});
db.products.createIndex ({"category" : 1, "brand" : 1});
db.products.createIndex ({"reviews.author" : 1});

var exp_obj = db.products.explain ()

exp_obj.find ( { $and : [ { price : { $gt : 30 } },{ price : { $lt : 50 } } ]} ).sort( { brand : 1 } );
exp_obj.find ( { 'brand' : "GE" } ).sort( { price : 1 } )
exp_obj.find ( { brand : 'GE' } ).sort( { category : 1, brand : -1 } )
exp_obj.find ( { 'brand' : "GE" } ) 

db.products.drop ()
