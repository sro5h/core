#ifndef _COLLIDER_HPP
#define _COLLIDER_HPP

#include <memory>
#include <vector>
#include "tinyc2.h"

class Body {
public:
        Body(C2_TYPE type, bool dynamic) : type(type), dynamic(dynamic) {}
        virtual ~Body() {}

        virtual void move(float x, float y) = 0;
        virtual void moveTo(float x, float y) = 0;

        virtual float getX() = 0;
        virtual float getY() = 0;

        virtual const void* get() = 0;

        C2_TYPE type;
        bool dynamic;
};

class CircleBody : public Body {
public:
        CircleBody(float r, float x, float y, bool dynamic = false);

        void move(float x, float y);
        void moveTo(float x, float y);

        float getX();
        float getY();

        const void* get();

        c2Circle body;
};

class AabbBody : public Body {
public:
        AabbBody(float w, float h, float x, float y, bool dynamic = false);

        void move(float x, float y);
        void moveTo(float x, float y);

        float getX();
        float getY();

        const void* get();

        c2AABB body;
};

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
