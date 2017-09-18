#ifndef _COLLIDER_HPP
#define _COLLIDER_HPP

#include <memory>
#include <vector>
#include "Body.hpp"

class Collider {
public:
        std::shared_ptr<CircleBody> createCircleBody(float r, float x, float y);
        std::shared_ptr<AabbBody> createAabbBody(float w, float h, float x, float y);

        void update();

private:
        void solveCollision(std::shared_ptr<Body> a, std::shared_ptr<Body> b,
                        const c2Manifold& manifold);

        std::vector<std::shared_ptr<Body>> bodies;
        // For debug purposes
        std::vector<c2Manifold> manifolds;
};

#endif // _COLLIDER_HPP
