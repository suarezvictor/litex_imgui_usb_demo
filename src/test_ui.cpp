#include "imgui_custom.h"

#if 0
#include "implot.h"
#include "implot.cpp"
#include "implot_items.cpp"
#include "implot_demo.cpp"

void Demo_Plot()
{
  ImGui::Begin("Plot");

    static ImPlot::ScrollingBuffer sdata1, sdata2;
    ImVec2 mouse = ImGui::GetMousePos();
    static float t = 0;
    t += ImGui::GetIO().DeltaTime;
    sdata1.AddPoint(t, mouse.x / VIDEO_FRAMEBUFFER_HRES);
    sdata2.AddPoint(t, mouse.y / VIDEO_FRAMEBUFFER_VRES);

    static float history = 10.0f;
    static ImPlotAxisFlags flags = ImPlotAxisFlags_NoTickLabels;

    if (ImPlot::BeginPlot("##Scrolling", ImVec2(-1,150))) {
        ImPlot::SetupAxes(NULL, NULL, flags, flags);
        ImPlot::SetupAxisLimits(ImAxis_X1,t - history, t, ImGuiCond_Always);
        ImPlot::SetupAxisLimits(ImAxis_Y1,0,1);
        //ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL,0.5f);
        ImPlot::PlotLine("Mouse X", &sdata1.Data[0].x, &sdata1.Data[0].y, sdata1.Data.size(), 0, sdata1.Offset, 2*sizeof(float));
        ImPlot::PlotLine("Mouse Y", &sdata2.Data[0].x, &sdata2.Data[0].y, sdata2.Data.size(), 0, sdata2.Offset, 2*sizeof(float));
        ImPlot::EndPlot();
    }

  ImGui::End();
}
#endif

extern "C" {
uint16_t audio_volume=0xFFFF;
uint16_t audio_param[]={880};
}

ImColor do_test_ui()
{
  static bool init = true;
  if(init)
  {
    init = false;
    ImGui::CreateContext();
    //ImPlot::CreateContext();  
  }
  
  ImGuiIO& io = ImGui::GetIO();

  static int color_r = 0x80, color_g = 0, color_b = 0;
#if 0
  ImGui::ShowDemoWindow(NULL); //tested working
#endif

#if 0
  //ImPlot::ShowDemoWindow(NULL); //full demo
  ImGui::SetNextWindowPos(ImVec2(400, 250));        
  ImGui::SetNextWindowSize(ImVec2(200, 200));
  Demo_Plot();
#endif

#if 1
  ImGui::SetNextWindowPos(ImVec2(100, 100));        
  ImGui::SetNextWindowSize(ImVec2(180, 100));
  ImGui::Begin("Color");
  ImGui::SliderInt("R", &color_r, 0, 255);
  ImGui::SliderInt("G", &color_g, 0, 255);
  ImGui::SliderInt("B", &color_b, 0, 255);
  ImGui::End();
#endif

#if 1
  ImGui::SetNextWindowPos(ImVec2(100, 210));        
  ImGui::SetNextWindowSize(ImVec2(250, 80));
  ImGui::Begin("Audio");
  int vol=100*audio_volume/0xFFFF, freq=audio_param[0];
  ImGui::SliderInt("Volume", &vol, 0, 100);
  ImGui::SliderInt("Frequency", &freq, 440, 440*4);
  ImGui::End();
  audio_volume = (0xFFFF*vol+50)/100; //linear, should be in dB
  audio_param[0]=freq;
#endif

#if 1
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
  ImGui::Text("%d", int(io.Framerate+.5));
  ImGui::End();
#endif

  return IM_COL32(color_r, color_g, color_b, 0);
}

