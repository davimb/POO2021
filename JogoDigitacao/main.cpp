#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace std;

struct Pincel {

    sf::Font font;
    sf::Text text;
    sf::RenderWindow& window;

        Pincel(sf::RenderWindow& window) : window{window} {
            if(!font.loadFromFile("hocus.ttf"))
                cout<<"Font Loader error";
            text.setFont(font);
        }

        void write(string str, int x, int y, int size, sf::Color color) {
            text.setString(str);
            text.setCharacterSize(size);
            text.setPosition(x, y);
            text.setFillColor(color);
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
        sf::CircleShape circle(Bubble::radius);
        circle.setPosition(x, y);
        circle.setFillColor(sf::Color::White);
        window.draw(circle);

        static Pincel pincel(window);
        pincel.write(string(1, letter), x+0.5*Bubble::radius, y, Bubble::radius*2, sf::Color::Blue);
    }
};

struct Board {

    sf::RenderWindow& window;
    vector<Bubble> bubbles;
    int hits {0};
    int misses {0};
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
        int speed = rand() % 5 + 1;
        char letter = rand() % 26 + 'A';
        bubbles.push_back(Bubble(x, y, letter, speed));

    }
    void draw() {
        pincel.write("Hits: " + to_string(this->hits) + " Misses: " + to_string(this->misses), 10, 10, 20, sf::Color::White);
        pincel.write("Bubbles: " + to_string(this->bubbles.size()), 10, 30, 20, sf::Color::White);
        for(Bubble& bubble : bubbles) {
            bubble.draw(window);
        }
    }
};

struct Game {
    sf::RenderWindow window;
    Board board;
    function<void()> on_update;

    Game() : window(sf::VideoMode(800,600), "Bubbles"), board(window) {
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
        pincel.write("Game over", 230, 230, 100, sf::Color::Black);
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
    Game game;
    game.main_loop();

}
