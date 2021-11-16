#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace std;

void setSize(sf::Sprite& sprite, int width, int height) {

    auto dim = sprite.getLocalBounds();
    sprite.setScale((float) width / dim.width, (float) height / dim.height);

}

struct Pincel {

    sf::Font font;
    sf::Text text;
    sf::RenderWindow& window;

        Pincel(sf::RenderWindow& window) : window{window} {
            if(!font.loadFromFile("fonts/04B_30__.ttf"))
                cout<<"Font Loader error";
            text.setFont(font);
        }

        void write(string str, int x, int y, int size, int cont) {
            text.setString(str);
            text.setCharacterSize(size);
            text.setPosition(x, y);
            if(cont==0)
               text.setFillColor(sf::Color::White);
            else if(cont==1)
                text.setFillColor(sf::Color::Yellow);
            else if(cont==2)
                text.setFillColor(sf::Color::Red);
            else if(cont==3)
                text.setFillColor(sf::Color::Blue);
            else if(cont==4)
                text.setFillColor(sf::Color::Green);
            else if(cont==5)
                text.setFillColor(sf::Color::Magenta);
            else if(cont==6)
                text.setFillColor(sf::Color::Cyan);
            else if(cont==7)
                text.setFillColor(sf::Color::Black);
            window.draw(text);
        }

};

struct Bubble {

    int x;
    int y;
    char letter;
    int speed;

    bool alive {true};
    static const int radius {20};

    Bubble(int x, int y, char letter, int speed) : x{x}, y{y}, letter{letter}, speed{speed} {
    }

    void update() {
        y += speed;
    }

    void draw(sf::RenderWindow& window) {
        static Pincel pincel(window);
        int cont = rand() % 8;
        pincel.write(string(1, letter), x, y, Bubble::radius*3, cont);
    }

};

struct Board {

    sf::RenderWindow& window;
    vector<Bubble> bubbles;
    int hits {0};
    int misses {0};
    int cont{0};
    Pincel pincel;

    Board(sf::RenderWindow& window) : window {window}, pincel {window} {
    }

    void update() {
        if(this->check_new_bubbles()) {
            this->add_new_bubble();
        }
        for(Bubble& bubble : bubbles) {
            bubble.update();
        }
        this->mark_outside();
        this->remove_dead_bubbles();
    }

    void remove_dead_bubbles() {
        vector<Bubble> live;
        for(Bubble bubble : bubbles) {
            if(bubble.alive) {
                live.push_back(bubble);
            }
        }
        this->bubbles = live;
    }

    void mark_outside() {
        for(Bubble& bubble : bubbles) {
            if(bubble.y + 2 * Bubble::radius > (int)window.getSize().y) {
                if(bubble.alive) {
                    bubble.alive = false;
                    this->misses++;
                }
            }
        }
    }

    void mark_by_hit(char letter) {
        for(Bubble& bubble : bubbles) {
            if(bubble.letter==letter){
                bubble.alive = false;
                this->hits++;
                if(this->misses>0)
                    this->cont++;
                if(cont==10) {
                    this->misses--;
                    this->cont = 0;
                }
                return;
            }
        }
        this->misses++;
    }

    bool check_new_bubbles() {
        static const int new_bubble_timeout {30};
        static int new_bubble_timer {0};

        new_bubble_timer--;
        if(new_bubble_timer<=0) {
            new_bubble_timer = new_bubble_timeout;
            return true;
        }
        return false;
    }

    void add_new_bubble() {
        int x = rand() % ((int)window.getSize().x - 2*Bubble::radius);
        int y = -2 * Bubble::radius;
        int speed = rand() % 3 + 3;
        char letter = rand() % 26 + 'A';
        bubbles.push_back(Bubble(x, y, letter, speed));

    }
    void draw() {
        pincel.write("Hits: " + to_string(this->hits) + " Misses: " + to_string(this->misses), 10, 10, 20, 0);
        pincel.write("Bubbles: " + to_string(this->bubbles.size()), 10, 30, 20, 0);
        for(Bubble& bubble : bubbles) {
            bubble.draw(window);
        }
    }
};

struct Game {
    sf::RenderWindow window;
    Board board;
    function<void()> on_update;
    sf::Sprite sprite;

    Game(sf::Sprite sprite) : window(sf::VideoMode(900,650), "Bubbles"), board(window), sprite{sprite} {
        this->on_update = [&]() {
            this->gameplay();
        };
        window.setFramerateLimit(60);
    }

    void process_events() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type==sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::TextEntered) {
                char code = static_cast<char>(event.text.unicode);
                code = toupper(code);
                board.mark_by_hit(code);
            }
        }
    }

    void gameplay() {
        board.update();
        window.clear(sf::Color::Black);
        window.draw(sprite);
        board.draw();
        window.display();

        if(board.misses > 10) {
            this->on_update = [&]() {
                this->gameover();
            };
        }
    }

    void gameover() {
        Pincel pincel(window);
        window.clear(sf::Color::Red);
        pincel.write("Game over", 200, 200, 70, 7);
        window.display();
    }

    void main_loop() {
        while(window.isOpen()) {
            process_events();
            on_update();
        }
    }

};

int main () {
    sf::Texture texture;
    if (!texture.loadFromFile("images/fundo.jpg")) {
        cout << "Error loading texture" << endl;
        exit(1);
    }
    sf::Sprite sprite(texture);
    setSize(sprite, 900, 650);
    sprite.setPosition(0, 0);

    Game game(sprite);
    game.main_loop();

}
