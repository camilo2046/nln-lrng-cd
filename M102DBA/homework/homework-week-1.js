// Week 1 Homework

// Homework 1-1

// In shell: mongod --dbpath data 
db.isMaster().maxBsonObjectSize

// Homework 1-2

// In shell: mongoimport -db pcat -c products < products.json
db.products.find( { type : "case" } ).count()

// Homework 1-3

db.products.find( { brand : "ACME" } )

// Homework 1-4

var c = db.products.find( { }, { name : 1, _id : 0 } ).sort( { name : 1 } ); while( c.hasNext() ) { print( c.next().name); } 
var c = db.products.find( { } ).sort( { name : 1 } ); c.forEach( function( doc ) { print( doc.name ) } ); 

