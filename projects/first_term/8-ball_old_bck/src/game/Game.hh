#ifndef GAME_HPP

#include "../field/Field.hh"

class Game {
   private:
    Field field;

    void init_field();

    void change();
    void change_field();
    void change_ball();
    void change_ball_starting_posstion();
    void reset_ball_pos();

    void print_field();

    void hit();

    void cls();
    void menu(std::string type);

   public:
    Game();
    ~Game();
    void run();
};

#endif  // GAME_HPP