package course;

import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import com.mongodb.client.model.Sorts;
import com.mongodb.operation.UpdateOperation;
import java.util.ArrayList;
import java.util.Date;
import org.bson.Document;

import java.util.List;
import org.bson.conversions.Bson;

/* Insert first post via mongo-shell (for the blog project to run)

    db.posts.insert (
                        {
                            "title" : "Martians to use MongoDB",
                            "author" : "test_user",
                            "body" : "Representatives from the planet Mars announced today that the planet would adopt MongoDB as a planetary standard. Head Martian Flipblip said that MongoDB was the perfect tool to store the diversity of life that exists on Mars.",
                            "permalink" : "martians_to_use_mongodb",
                            "tags" : [
                                "martians",
                                "seti",
                                "nosql",
                                "worlddomination"
                            ],
                            "comments" : [ ],
                            "date" : ISODate("2013-03-11T01:54:53.692Z")
                        });

*/

public class BlogPostDAO {
    MongoCollection<Document> postsCollection;

    public BlogPostDAO(final MongoDatabase blogDatabase) {
        postsCollection = blogDatabase.getCollection("posts");
    }

    // Return a single post corresponding to a permalink
    public Document findByPermalink(String permalink) {

        Document post = null;
        
        Bson filterPermalink = new Document ("permalink", permalink);
        post = postsCollection.find (filterPermalink).first ();
        
        return post;
    }

    // Return a list of posts in descending order. Limit determines
    // how many posts are returned.
    public List<Document> findByDateDescending(int limit) {

        // Return a list of DBObjects, each one a post from the posts collection
        List<Document> posts = null;
        
        Bson sortDate = Sorts.descending ("date");
        
        posts = postsCollection.find  ()
                               .sort  (sortDate)
                               .limit (limit)
                               .into  (new ArrayList<Document> ());

        return posts;
    }


    public String addPost(String title, String body, List tags, String username) {

        System.out.println("inserting blog entry " + title + " " + body);

        String permalink = title.replaceAll("\\s", "_"); // whitespace becomes _
        permalink = permalink.replaceAll("\\W", ""); // get rid of non alphanumeric
        permalink = permalink.toLowerCase();

        // Remember that a valid post has the following keys:
        // author, body, permalink, tags, comments, date
        //
        // A few hints:
        // - Don't forget to create an empty list of comments
        // - for the value of the date key, today's datetime is fine.
        // - tags are already in list form that implements suitable interface.
        // - we created the permalink for you above.

        // Build the post object and insert it
        Document post = new Document();
        
        post = post.append ("author"   , username)
                   .append ("title"    , title)
                   .append ("body"     , body)
                   .append ("permalink", permalink)
                   .append ("tags"     , tags)
                   .append ("comments" , new ArrayList<String> ())
                   .append ("date"     , new Date ());
        
        postsCollection.insertOne (post);

        return permalink;
    }




    // White space to protect the innocent








    // Append a comment to a blog post
    public void addPostComment(final String name, final String email, final String body,
                               final String permalink) {

        // Hints:
        // - email is optional and may come in NULL. Check for that.
        // - best solution uses an update command to the database and a suitable
        //   operator to append the comment on to any existing list of comments
        
        Bson filterDocument          = new Document ("permalink", permalink);
        Document postCommentDocument = new Document ("author", name).append ("body", body);
        
        if (email != null)
        {
            postCommentDocument = postCommentDocument.append ("email", email);
        }
        
        Bson replacementDocument     = new Document ("$push", new Document ("comments", postCommentDocument));
        
        postsCollection.updateOne (filterDocument, replacementDocument);
    }
}
