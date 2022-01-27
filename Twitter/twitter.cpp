#include <iostream>
#include <set>
#include <map>
#include <list>

using namespace std;

class Tweet{
    int id;
    string username;
    string msg;
    set<string> likes;
    Tweet* rt = nullptr;
    bool deleted = false;
public:
    Tweet(int id, string username, string msg) : id{id}, username{username}, msg{msg} {

    }

    string getLikes() {
        int i=0;
        string mylikes{};
        for(auto like : likes) {
            i++;
            if(i != (int)likes.size()) {
                mylikes+=like;
                mylikes+=", ";
            }
            else
               mylikes+=like;
        }
        return mylikes;
    }
    
    void like(string username) {
        likes.insert(username);
    }

    void setRt(Tweet *tw) {
        rt = tw;
    }

    void setDeleted() {
        deleted = true;
        likes.clear();
        username = "";
        msg = "esse tweet foi deletado";
    }

    bool isDeleted() {
        if(deleted == false)
            return false;
        return true;
    }

    string getUsername() {
        return username;
    }

    int getId() {
        return id;
    }

    string getMsg() {
        return msg;
    }

    friend ostream& operator<<(ostream& os, Tweet* tweet) {
        if(tweet->rt != nullptr) {
            cout<<tweet->rt->id<<":"<<tweet->rt->username<<" ("<<tweet->rt->msg<<")";
            int i = 0;
            for(auto like : tweet->rt->likes) {
                i++;
                os<<" [";
                if(i == (int)tweet->rt->likes.size())
                    os<<like;
                else
                    os<<like<<", ";
                os<<"]";
            }
            os<<endl<<"   ";
        }
        os<<tweet->id<<":"<<tweet->username<<" ("<<tweet->msg<<")";
        if((int)tweet->likes.size()>0) {
            os<<" [";
            int i = 0;
            for(auto like : tweet->likes) {
                i++;
                if(i == (int)tweet->likes.size())
                    os<<like;
                else
                    os<<like<<", ";
            }
            os<<"]";
        }
        return os;
    }
};

class Inbox{
    map<int, Tweet*> timeline;
    map<int, Tweet*> myTweets;
public:
    Inbox() {
        
    }

    void storeInTimeline(Tweet* tweet) {
        timeline[tweet->getId()] = tweet;
    }

    void storeInMyTweets(Tweet* tweet) {
        myTweets[tweet->getId()] = tweet;
    }
    
    void rmMsgsFrom(string username) {
        list<int> aux;
        for(auto time : timeline) {
            if(time.second->getUsername() == username) {
                aux.push_back(time.first);
            }
        }
        for(auto it : aux) {
            timeline.erase(it);
        }
    }

    list<Tweet*> getMyTweets() {
        list<Tweet*> MyTweets;
        for(auto myt : myTweets) {
            MyTweets.push_back(myt.second);
        }
        return MyTweets;
    }
    
    friend ostream& operator<<(ostream& os, Inbox inbox) {
        for(auto time : inbox.timeline) {
            os<<time.second<<endl;
        }
    }
};

class User{
    string username;
    Inbox inbox;
    map<string, User*> followers;
    map<string, User*> following;
public:
    User(string username) : username{username} {

    }

    void follow(User *other) {
        other->followers[username] = this;
        following[other->username] = other;
    }

    string getUsername() {
        return username;
    }

    void sendTweet(Tweet *tw) {
        inbox.storeInTimeline(tw);
        inbox.storeInMyTweets(tw);

        for(auto user : followers) {
            user.second->inbox.storeInTimeline(tw);
        }
    }

    Inbox getInbox() {
        return inbox;
    }

    void unfollow(string other) {
        User* user = following[other];
        following.erase(other);

        inbox.rmMsgsFrom(other);
        
        user->followers.erase(username);
    }

    void unfollowAll() {
        auto aux = following;
        for(auto follow : aux) {
            this->unfollow(follow.first);
        }
    }

    void rejectAll() {
        auto aux = followers;
        for(auto follower : aux) {
            follower.second->unfollow(username);
        }
    }

    friend ostream& operator<<(ostream& os, const User* user) {
        os<<"seguidos [";
        int i = 0;
        for(auto follow : user->following) {
            i++;    
            if(i == (int)user->following.size()) {
                os<<follow.second->getUsername();
            }
            else
                os<<follow.second->getUsername()<<", ";
        }
        os<<"]"<<endl;
        os<<"seguidores [";
        i = 0;
        for(auto follower : user->followers) {
            i++;
            if(i == (int)user->followers.size()) {
                os<<follower.second->getUsername();
            }
            else
                os<<follower.second->getUsername()<<", ";
        }
        os<<"]"<<endl;
        return os;
    }
};

class Controller{
    int nextTweetId{};
    map<string, User*> users;
    map<int, Tweet*> tweets;

    bool existeUser(string username) {
        auto it = users.find(username);
        if(it == users.end())
            return false;
        return true;
    }

public:
    Controller() {

    }

    void addUser(string username) {
        if(!existeUser(username)) {
            User* user = new User(username);
            users[username] = user;
        }
        else {
            throw runtime_error("Usuario ja existe");
        }
    }

    void follow(string username, string other) {
        if(existeUser(username) and existeUser(other)) {
            users[username]->follow(users[other]);
        }
        else
            throw runtime_error("Usuario nao existe");
    }

    void unfollow(string username, string other) {
        if(existeUser(username) and existeUser(other)) {
            users[username]->unfollow(other);
        }
        else
            throw runtime_error("Usuario nao existe");
    }

    void createTweet(string username, string msg) {
        if(existeUser(username)) {
            Tweet* tweet = new Tweet(nextTweetId, username, msg);
            tweets[nextTweetId] = tweet;
            nextTweetId++;
            users[username]->sendTweet(tweet);
        }
        else
            throw runtime_error("Usuario nao existe");
    }

    void getTimeline(string username) {
        if(existeUser(username)) {
            cout<<users[username]->getInbox();
        }
        else
            throw runtime_error("Usuario nao existe");
    }

    void like(string username, int id) {
        auto it = tweets.find(id);
        if(it != tweets.end())
            tweets[id]->like(username);
        else
            throw runtime_error("Tweet nao existe");
    }

    void sendRt(string username, int twId, string rtMsg) {
        if(existeUser(username) and !tweets[twId]->isDeleted()) {
            Tweet*  tweet = new Tweet(nextTweetId, username, rtMsg);
            tweets[nextTweetId] = tweet;
            nextTweetId++;
            
            tweets[twId]->setRt(tweet);
        }
        else if(!existeUser(username))
            throw runtime_error("Usuario nao existe");
        else
            throw runtime_error("Tweet apagado");
    }

    void rmUser(string username) {
        list<Tweet*> mytweets = users[username]->getInbox().getMyTweets();

        for(auto myt : mytweets) {
            if(!myt->isDeleted()) {
                myt->setDeleted();
            }
        }
        users[username]->unfollowAll();
        users[username]->rejectAll();
        users.erase(username);
    }

    friend ostream& operator<<(ostream& os, const Controller control) {
        for(auto user : control.users) {
            os<<user.first<<endl<<user.second;
        }
        return os;
    }
};

int main () {
    Controller controle;
    string cmd{};
    
    while(cmd!="end") {
        cout<<"$";
        cin>>cmd;

        try {
            if(cmd=="add") { //
                string username;
                cin>>username;

                controle.addUser(username);
            }
            else if(cmd=="follow") { //
                string username, other;
                cin>>username>>other;

                controle.follow(username, other);
            }
            else if(cmd=="unfollow") { 
                string username, other;
                cin>>username>>other;

                controle.unfollow(username, other);
            }
            else if(cmd=="twittar") { //
                string username, msg;
                cin>>username;
                cin.get();
                getline(cin, msg);

                controle.createTweet(username, msg);
            }
            else if(cmd=="timeline") { //
                string username;
                cin>>username;

                controle.getTimeline(username);
            }
            else if(cmd=="like") { //
                string username;
                int id;
                cin>>username>>id;

                controle.like(username, id);
            }
            else if(cmd=="rt") { //
                string username, msg;
                int id;
                cin>>username>>id;
                cin.get();
                getline(cin, msg);

                controle.sendRt(username, id, msg);
            }
            if(cmd=="rm") {
                string username;
                cin>>username;

                controle.rmUser(username);    
            }
            if(cmd=="show") { //
            cout<<controle; 
            }
        } catch (runtime_error e) {
            cout<<"erro: "<<e.what()<<endl;
        }
    }
}

/*
add goku
add sara
add tina
show
follow goku sara
follow goku tina
follow sara tina
show
twittar sara hoje estou triste
twittar tina ganhei chocolate
twittar sara partiu ru
twittar tina chocolate ruim
twittar goku internet maldita
timeline goku
unfollow goku sara
*/  