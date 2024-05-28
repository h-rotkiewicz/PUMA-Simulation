#include "animEng.h"

#include <algorithm>

void ShaderManager::updateShader(const Camera &camera) {
  auto UpdateShader = [&camera](Shader &S, ModelState &state) {
    S.use();
    glm::mat4 view(1.0f);
    glm::mat4 projection(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)Settings::SCR_WIDTH / (float)Settings::SCR_HEIGHT, 0.1f, 100.0f);
    // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    view = glm::lookAt(camera.cameraPosition, camera.getCameraTarget(), camera.getCameraUp());

    S.setMat4("projection", projection);
    S.setMat4("view", view);
    S.setVec3("lightColor", Settings::lightColor);
    S.setVec3("lightPos",
              camera.cameraPosition);  // I think it makes sense for max visibility
    S.setVec3("viewPos", camera.cameraPosition);

    glm::mat4 model(1.0f);
    model = glm::translate(model, state.position);
    (model = glm::rotate(model, glm::radians(state.angle), state.axis)) == glm::mat4(1.0f) ? state.isRotating = false : state.isRotating = true;
    S.setMat4("model", model);
  };
  for (auto &shader : ShaderMap) UpdateShader(shader.second, StateMap.at(shader.first));
}

void ShaderManager::RotatePart(RobotParts part, float angle) {
  // Example Rotation
  StateMap.at(part).angle += angle;
}

std::unordered_map<RobotParts, Shader> const &ShaderManager::getShaderMap() const { return ShaderMap; }

void ShaderManager::addShader(RobotParts part, Shader &&shader, glm::vec3 axis) {
  ShaderMap.emplace(part, std::move(shader));
  ModelState state{.angle = 0, .axis = axis, .position{0, 0, 0}};
  StateMap.emplace(part, state);
}
void ShaderManager::render(std::unordered_map<RobotParts, Part> const &rendercontainer, GLFWwindow *window) const {
  for (const auto &[RobotPart, part] : rendercontainer) {
    if (StateMap.at(RobotPart).isRotating) {
      ShaderMap.at(RobotPart).use();
      std::for_each(rendercontainer.find(RobotPart), rendercontainer.end(), [&StateMap = StateMap, &RobotPart = RobotPart](auto const &Elem) {
        Elem.second.Render();
      });
      break;
    } else {
      ShaderMap.at(RobotPart).use();
      part.Render();
    }
  }
  CheckForErrors("render");
  glfwSwapBuffers(window);
  glfwPollEvents();
}
