mkdir data
mkdir data/logs
mkdir data/z1
mkdir data/z2
mkdir data/z3

mongod --logpath ../data/logs/a.log --smallfiles --oplogSize 50 --port 27001 --dbpath ../data/z1 --replSet z
mongod --logpath ../data/logs/b.log --smallfiles --oplogSize 50 --port 27002 --dbpath ../data/z2 --replSet z
mongod --logpath ../data/logs/c.log --smallfiles --oplogSize 50 --port 27003 --dbpath ../data/z3 --replSet z

mongo --shell --port 27003 question_1/a.js

// Question 1 //

db.foo.insert( { _id : 1 }, { writeConcern : { w : 2 } } );
db.foo.insert( { _id : 2 }, { writeConcern : { w : 2 } } );
db.foo.insert( { _id : 3 }, { writeConcern : { w : 2 } } );
    
var a_conn = connect ("localhost:27001/admin");
a_conn.shutdownServer ();
rs.status ();

db.foo.insert( { _id : 4 } );
db.foo.insert( { _id : 5 } );
db.foo.insert( { _id : 6 } );

mongod --logpath ../data/logs/a.log --smallfiles --oplogSize 50 --port 27001 --dbpath ../data/z1 --replSet z
rs.status ();

rs.slaveOk ();
db.foo.find();

// Question 2 //

var a_conn = connect ("localhost:27001/admin");
a_conn.shutdownServer ();
rs.status ();

db.foo.drop();
db.foo.insert( { _id : 1 }, { writeConcern : { w : 2 } } );
db.foo.insert( { _id : 2 }, { writeConcern : { w : 2 } } );
db.foo.insert( { _id : 3 }, { writeConcern : { w : 2 } } );
var a = connect("localhost:27001/admin");
a.shutdownServer();
rs.status();
db.foo.insert( { _id : 4 } )
db.foo.insert( { _id : 5 } )
db.foo.insert( { _id : 6 } )

ps -A | grep mongod
# should see the 27003 and 27002 ones running (only)
ps ax | grep mongo | grep 27003 | awk '{print $1}' | xargs kill
# wait a little for the shutdown perhaps...then:
ps -A | grep mongod
# should get that just the arbiter is present…

mongod --logpath ../data/logs/a.log --smallfiles --oplogSize 50 --port 27001 --dbpath ../data/z1 --replSet z
rs.status ();

db.foo.find(); // 3 docs
db.foo.insert( { _id : "last" } );

mongod --logpath ../data/logs/c.log --smallfiles --oplogSize 50 --port 27003 --dbpath ../data/z3 --replSet z
rs.status ();

db.foo.find() // 4 docs in 27001
db.foo.find() // 4 docs in 27003

// Question 3 //

bsondump ../data/z3/rollback/ *.bson // Found 3 docs

// Question 4 //

mongo --shell --port 27001 question_1/a.js

var x = rs.reconfig(                                                                                    
	{ _id:'z',                                                                                              
	  members:[                                                                                             
		{ _id:1, host:'localhost:27001' },                                                                   
		{ _id:2, host:'localhost:27002', "arbiterOnly" : true },                                                                   
		{ _id:3, host:'localhost:27003', "priority" : 0, "hidden" : false}                                                                    
	  ]                                                                                             
	}
);  
rs.status ();

mongo --shell --port 27003 question_1/a.js
part4 ();

// Question 5  //

db.postings.insert ({
                        _id : 1,
                        author : 'joe',
                        title : 'Too big to fail',
                        text : '...',
                        tags : [ 'business', 'finance' ],
                        when : ISODate("2008-11-03"),
                        views : 23002,
                        votes : 4,
                        voters : ['joe', 'jane', 'bob', 'somesh'],
                        comments : [
                                       { commenter : 'allan', 
                                         comment : 'Well, i dont think so…', 
                                         flagged : false, 
                                         plus : 2 
                                       }
                                   ]
                    });

db.postings.createIndex ( { "comments.flagged" : true } );

db.postings.createIndex ( { "voters" : true }, {"unique" : true, "dropDups" : true});
db.postings.update( { _id: 1}, { $inc : {votes:1}, $push : {voters:'joe'} } );

db.postings.update( { _id: 1, voters:{$ne:'joe'} }, { $inc : {votes:1}, $push : {voters:'joe'} } ); 
db.postings.update( { _id: 1, voters:{$ne:'test1'} }, { $inc : {votes:1}, $push : {voters:'test1'} } ); 
db.postings.update( { _id: 1, voters:{$ne:'test1'} }, { $inc : {votes:1}, $push : {voters:'test1'} } ); 

// Question 6 (Theory) //

// Question 7 (Theory) //

// Question 8 //

mongod --configsvr --logpath ../data/logs/config.log --smallfiles --oplogSize 50 --port 27019 --dbpath ../data-sh/config/ 
mongorestore --host localhost --port 27019 question_8/gene_backup/gene_backup/config_server/

mongo --shell --port 27019
db;
db.chunks.find().sort({_id:1}).next().lastmodEpoch.getTimestamp().toUTCString().substr(20,6);

// Question 9 //

db.shards.find();
db.shards.update ({"_id" : "s1"}, {"$set" : {"host" : "localhost:27501"}});
db.shards.update ({"_id" : "s2"}, {"$set" : {"host" : "localhost:27601"}});
db.shards.find();

mongod --logpath ../data/logs/s1.log --smallfiles --oplogSize 50 --port 27501 --dbpath ../data-sh/s1/
mongod --logpath ../data/logs/s2.log --smallfiles --oplogSize 50 --port 27601 --dbpath ../data-sh/s2/

mongorestore --host localhost --port 27501 question_8/gene_backup/gene_backup/s1/
mongorestore --host localhost --port 27601 question_8/gene_backup/gene_backup/s2/

mongos --configdb localhost:27019 

mongo
use snps;
var x = db.elegans.aggregate( [ { $match : { N2 : "T" } } , { $group : { _id:"$N2" , n : { $sum : 1 } } } ] ).next(); print( x.n );

// Question 10 //

use snps;
db.elegans.createIndex ({N2:1,mutant:1});
db.elegans.find({N2:"T",mutant:"A"}).limit(5).explain("executionStats");
