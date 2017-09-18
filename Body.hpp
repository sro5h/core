#ifndef _BODY_HPP
#define _BODY_HPP

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

#endif // _BODY_HPP
