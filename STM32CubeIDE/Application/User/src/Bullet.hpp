#ifndef BULLET_HPP
#define BULLET_HPP
#include "Entity.hpp"


class Bullet : public Entity {
    public:
        Bullet();
        void update();
        void draw();
        bool active;
    private:
        int speed;
};
#endif
