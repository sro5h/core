#ifndef _COLLIDER_HPP
#define _COLLIDER_HPP

#include <memory>
#include <vector>
#include "Body.hpp"

struct Raycast {
        Raycast() : hit(false), t(-1) {}

        bool hit;
        float t;
        float x;
        float y;
};

class Collider {
public:
        std::shared_ptr<CircleBody> createCircleBody(float r, float x, float y);
        std::shared_ptr<AabbBody> createAabbBody(float w, float h, float x, float y);

        Raycast raycast(float x, float y, float dx, float dy, float t);

        void update();

private:
        void solveCollision(std::shared_ptr<Body> a, std::shared_ptr<Body> b,
                        const c2Manifold& manifold);

        std::vector<std::shared_ptr<Body>> bodies;
        // For debug purposes
        std::vector<c2Manifold> manifolds;
};

#endif // _COLLIDER_HPP
