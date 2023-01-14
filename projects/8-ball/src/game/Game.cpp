#include "Game.hpp"

#include <iostream>

#include "../objects/Point.hpp"

Game::Game() {}

void Game::run() {
    init_field();

    while (true) {
        menu("main");

        char input;
        std::cin >> input;
        std::cin.ignore();

        cls();

        switch (input) {
            case 'c':
                change();
                break;
            case 'f':
                print_field();
                std::cout << "Press enter to continue...";
                std::cin.ignore();
                break;
            case 'h':
                hit();
                std::cout << "Press enter to continue...";
                std::cin.get();
                break;
            case 'i':
                init_field();
                break;
            case 'q':
                exit(0);
            default:
                std::cout << "Invalid input" << std::endl;
        }
    }
}

// Init field

void Game::init_field() {
    menu("init");
    Point end_points[4];
    std::cout << "Enter the end points of the field" << std::endl;
    std::cin >> end_points[0] >> end_points[1] >> end_points[2] >> end_points[3];
    std::cout << "Enter the starting position of the ball" << std::endl;
    Point starting_pos;
    std::cin >> starting_pos;
    double ball_radius;
    std::cout << "Enter the radius of the ball" << std::endl;
    std::cin >> ball_radius;

    this->field = Field(end_points[0], end_points[1], end_points[2], end_points[3], starting_pos, ball_radius);
}

// Change

void Game::change() {
    menu("change");

    char input;
    std::cin >> input;

    switch (input) {
        case 'f':
            change_field();
        case 'b':
            change_ball();
            break;
        case 'p':
            change_ball_starting_posstion();
        case 'r':
            reset_ball_pos();
        default:
            std::cout << "Invalid input" << std::endl;
            break;
    }
}

void Game::change_field() {
    menu("field");
    std::cin >> field;
}

void Game::change_ball() {
    menu("ball");
    // std::cin >> field.get_ball();
}

void Game::change_ball_starting_posstion() {
    char input;
    switch (input) {
        case 'n': {
            int x, y;
            std::cout << "Enter the new starting possition: " << std::endl;
            std::cin >> x >> y;
            std::cin.ignore();
            field.set_starting_pos(Point(x, y));
        }
        case 'c':
            field.set_starting_pos(field.get_ball().getPos());
        default:
            std::cout << "Invalid input" << std::endl;
            break;
    }
}

void Game::reset_ball_pos() { field.reset_ball_pos(); }

// Print field

void Game::print_field() { std::cout << field << std::endl; }

// Hit ball

void Game::hit() {
    Point direction;
    double power;

    std::cout << "Enter direction: " << std::endl;
    std::cin >> direction;
    std::cout << "Enter power: " << std::endl;
    std::cin >> power;
    std::cin.ignore();

    field.hit_ball(direction, power);
}

// Menu

void Game::cls() { std::cout << "\033[2J\033[1;1H\n"; }

void Game::menu(std::string type) {
    cls();

    if (type == "init") {
        std::cout << "---Welcome to 8-ball pool simulator!---" << std::endl;
        std::cout << "By K.D.X | Kalyan #13" << std::endl << std::endl;
        std::cout << "Create a field:" << std::endl;
    } else if (type == "change") {
        std::cout << "---Change---" << std::endl;
        std::cout << "f - Change field" << std::endl;
        std::cout << "b - Change ball" << std::endl;
        std::cout << "p - Change ball's starting position" << std::endl;
        std::cout << "r - Reset ball's position" << std::endl;
    } else if (type == "field") {
        std::cout << "---Change Field---" << std::endl;
        std::cout << "Enter new field: " << std::endl;
    } else if (type == "ball") {
        std::cout << "---Change Ball---" << std::endl;
        std::cout << "Enter new ball: " << std::endl;
    } else if (type == "pos") {
        std::cout << "---Change Starting Position---" << std::endl;
        std::cout << "n - Set new starting position" << std::endl;
        std::cout << "c - Set current ball's coordinates as a startomg position"
                  << std::endl;
    } else if (type == "main") {
        std::cout << "---Menu---" << std::endl;
        std::cout << "c - Change anything..." << std::endl;
        std::cout << "f - Print field information" << std::endl;
        std::cout << "h - Hit ball" << std::endl;
        std::cout << "i - (re)Initialize field" << std::endl;
        std::cout << "q - Quit" << std::endl;
        std::cout << "Enter your choice: " << std::endl;
    }
}

Game::~Game() {}
