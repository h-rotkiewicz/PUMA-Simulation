#include "gui.h"
#include "imgui_impl_opengl3.h"
void Gui::renderImguiWindow() {
  ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
  ImGui::SetNextWindowSize(ImVec2(300, 150), ImGuiCond_Always);

  if (ImGui::Begin("3D Coordinate Input", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize)) {
    ImGui::Text("Enter 3D Coordinates:");
    ImGui::SliderFloat("X", &CurrentPointPos.x, -2.0f, 2.0f, "%.1f", ImGuiSliderFlags_AlwaysClamp);
    ImGui::SliderFloat("Y", &CurrentPointPos.y, -2.0f, 2.0f, "%.1f", ImGuiSliderFlags_AlwaysClamp);
    ImGui::SliderFloat("Z", &CurrentPointPos.z, -2.0f, 2.0f, "%.1f", ImGuiSliderFlags_AlwaysClamp);
    ImGui::Checkbox("Rotate to Point", &rotateToPoint);
  }
  ImGui::End();
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Gui::newFrame() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

Gui::Gui(ImGuiIO& io, GLFWwindow* window) : io(io) {
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init();
}

Gui::~Gui() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void ImGuiInit() {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  ImGui::StyleColorsDark();
}
