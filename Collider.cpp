#include "Collider.hpp"

void Collider::update()
{
        manifolds.clear();

        for (int i = 0; i < bodies.size(); ++i) {
                for (int j = i + 1; j < bodies.size(); ++j) {
                        auto a = bodies[i];
                        auto b = bodies[j];

                        c2Manifold manifold;
                        c2Collide(a->get(), nullptr, a->type,
                                        b->get(), nullptr, b->type,
                                        &manifold);

                        if (manifold.count > 0) {
                                manifolds.push_back(manifold);
                                solveCollision(a, b, manifold);
                        }
                }
        }
}

void Collider::registerBody(std::shared_ptr<Body> body)
{
        bodies.push_back(body);
}

Raycast Collider::raycast(float x, float y, float dx, float dy, float t)
{
        c2Ray ray;
        ray.p = c2V(x, y);
        ray.d = c2Norm(c2V(dx, dy));
        ray.t = t;

        Raycast result;

        for (auto body : bodies) {
                c2Raycast cast;
                if (c2CastRay(ray, body->get(), nullptr, body->type, &cast)) {
                        if (cast.t < result.t || result.t == -1) {
                                result.hit = true;
                                result.t = cast.t;
                                c2v impact = c2Impact(ray, cast.t);
                                result.x = impact.x;
                                result.y = impact.y;
                        }
                }
        }

        return result;
}

void Collider::solveCollision(std::shared_ptr<Body> a, std::shared_ptr<Body> b,
                const c2Manifold& manifold)
{
        c2v toMove = c2Mulvs(manifold.normal, manifold.depths[0]);

        if (a->dynamic && !b->dynamic) {
                a->move(-toMove.x, -toMove.y);
        } else if (!a->dynamic && b->dynamic) {
                b->move(toMove.x, toMove.y);
        }
}
