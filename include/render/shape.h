#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>

namespace cppcraft::render {
    
    class Shape {
        private:
            std::vector<glm::vec3> vertices;
            std::vector<glm::vec3> colors;
        
        public:
            Shape(std::vector<glm::vec3> vertices, std::vector<glm::vec3> colors);
            void render();
    };
}