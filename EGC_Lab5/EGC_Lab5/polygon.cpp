//
// Created by adi on 09.03.2022.
//

#include "polygon.h"

namespace egc {


    polygon::polygon() {

    }

    void polygon::addVertex(vec3 vertex) {

        this->vertices.push_back(vertex);
    }

    void polygon::clearVertices() {

        this->vertices.clear();
    }

    void polygon::draw(SDL_Renderer *windowRenderer) {

        if (this->vertices.size() >= 2) {
            std::vector<vec3> transformedVertices = this->vertices;
            for (size_t i = 0; i < this->vertices.size(); i++) {
                transformedVertices.at(i) = this->transformationMatrix * this->vertices.at(i);
            }
            SDL_SetRenderDrawColor(windowRenderer, 0, 0, 255, 255);

            for (int i = 0; i + 1 < this->vertices.size(); i++)
                SDL_RenderDrawLine(
                    windowRenderer,
                    static_cast<int>(transformedVertices.at(i).x),
                    static_cast<int>(transformedVertices.at(i).y),
                    static_cast<int>(transformedVertices.at(i + 1).x),
                    static_cast<int>(transformedVertices.at(i + 1).y));
            SDL_RenderDrawLine(
                windowRenderer,
                static_cast<int>(transformedVertices.at(this->vertices.size() - 1).x),
                static_cast<int>(transformedVertices.at(this->vertices.size() - 1).y),
                static_cast<int>(transformedVertices.at(0).x),
                static_cast<int>(transformedVertices.at(0).y));
        }
    }


}