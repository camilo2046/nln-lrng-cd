// Start an initially empty mongod database instance
 mongod --dbpath ../data-sh-1/

// Connect to it with the shell and week6.js loaded:
 mongo --shell localhost/week6 week6.js

// Run homework.init()
 homework.init()

// It will take some time to run as it inserts quite a few documents. When it is done run 
 db.trades.stats()

// Stop the mongod process. Now, restart the mongod process adding the option --shardsvr
 mongod --shardsvr --dbpath ../data-sh-1/

// Start a mongo config server
 mongod --configsvr --dbpath ../data-sh-1-config/

// Start a mongos:
 mongos --configdb localhost:27019

// Connect to mongos with the shell: 
 mongo --shell localhost/week6 week6.js

// Add the first shard ("your_host_name:27018"). 
 sh.addShard ("localhost:27018")
 sh.status ()
 
// Verify that the week6.trades data is visible via mongos. 
// Note at this point the week6 database isn't "sharding enabled" but its data is still visible via mongos
 db.trades.find().pretty()
 db.trades.count()
 db.trades.stats()

// Run homework.a() 
 homework.a()

// Now enable sharding for the week6 database
 sh.enableSharding ("week6")
 sh.status ()

// Then shard the trades collection on the compound shard key ticker plus time. 
// Note to shard a collection, you must have an index on the shard key, so you will need to create the index first: 
 db.trades.createIndex ({"ticker" : 1, "time" : 1});
 sh.shardCollection ("week6.trades", {"ticker" : 1, "time" : 1})

// After sharding the collection, look at the chunks which exist:
 use config
 db.chunks.find()
 db.chunks.find({}, {min:1,max:1,shard:1,_id:0,ns:1})

// Run homework.b() 
 homework.b()
 
// Let's now add a new shard. Run another mongod as the new shard on a new port number. Use --shardsvr.  
 mongod --shardsvr --port 27020 --dbpath ../data-sh-2/
 
// Then add the shard to the cluster 
 sh.addShard ("localhost:27020")
 sh.status ()

// You can confirm the above worked by running homework.check1()
 homework.check1() 
 
// Now wait for the balancer to move data among the two shards more evenly. Periodically run
 use config
 db.chunks.find( { ns:"week6.trades" }, {min:1,max:1,shard:1,_id:0} ).sort({min:1})
 db.chunks.aggregate ([
                          { $match : { ns : "week6.trades" } } , 
                          { $group : { _id : "$shard", n : { $sum : 1 } } }
                      ])

// Run homework.c() 
 homework.c()
