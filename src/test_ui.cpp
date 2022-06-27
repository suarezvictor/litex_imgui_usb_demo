uint32_t do_test_ui()

    {
        
        ImGui::NewFrame();
        static int color_r = 0, color_g = 0, color_b = 0;
#if 0
        ImGui::ShowDemoWindow(NULL); //tested working
#else
        ImGui::SetNextWindowSize(ImVec2(180, 100));
        ImGui::Begin("Color");
        ImGui::SliderInt("R", &color_r, 0, 255);
        ImGui::SliderInt("G", &color_g, 0, 255);
        ImGui::SliderInt("B", &color_b, 0, 255);
        ImGui::End();
        /*
        ImGui::Begin("FPS");
        ImGui::Text("%d", int(io.Framerate)); 
        ImGui::End();
        */     
        static char inputstr[128] = ""; //initial value
        ImGui::Begin("Input Text");
        ImGui::InputText("textid", inputstr, IM_ARRAYSIZE(inputstr));
        //if(ImGui::IsWindowAppearing())
        //  ImGui::SetKeyboardFocusHere(0);
        ImGui::End();
#endif

        ImGui::Render();
        return color_b | (color_g <<8 ) | (color_r << 16);
    }

