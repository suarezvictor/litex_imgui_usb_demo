ImColor do_test_ui()
{
  ImGuiIO& io = ImGui::GetIO();

  static int color_r = 0x80, color_g = 0, color_b = 0;
#if 1
  ImGui::ShowDemoWindow(NULL); //tested working
#endif

#if 0
  ImGui::SetNextWindowSize(ImVec2(180, 100));
  ImGui::Begin("Color");
  ImGui::SliderInt("R", &color_r, 0, 255);
  ImGui::SliderInt("G", &color_g, 0, 255);
  ImGui::SliderInt("B", &color_b, 0, 255);
  ImGui::End();
#endif

#if 0
  static char inputstr[128] = ""; //initial value
  ImGui::SetNextWindowPos(ImVec2(200, 300));        
  ImGui::SetNextWindowSize(ImVec2(180, 60));
  ImGui::Begin("Input Text");
  if(ImGui::IsWindowAppearing())
    ImGui::SetKeyboardFocusHere();
  ImGui::InputText("textid", inputstr, IM_ARRAYSIZE(inputstr));
  
  ImGui::End();
#endif

#if 1
  ImGui::SetNextWindowPos(ImVec2(500, 100));        
  ImGui::Begin("FPS");
  ImGui::Text("%d", int(io.Framerate));
  ImGui::End();
#endif

  return IM_COL32(color_r, color_g, color_b, 0);
}

