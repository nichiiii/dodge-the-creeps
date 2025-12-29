#pragma once

#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <iostream>

namespace godot{
    class UINode : public CanvasLayer{
        GDCLASS(UINode, CanvasLayer)

        protected:
            static void _bind_methods();
            Label* scoreLabel = nullptr;
            Label* message = nullptr;
            VBoxContainer *categBtnContainer = nullptr;
            Timer* messageTimer = nullptr; 
            Vector <String> readyMessage = {"Ready", "Set", "Dodge"};
            Button* easy = nullptr;
            Button* medium = nullptr;
            Button* extreme = nullptr;
            void on_pressed_easy();
            void on_pressed_medium();
            void on_pressed_extreme();
           
            void connectNodes();
            void getNodes();
           
            
        public:
            UINode();
            ~UINode();
            void _ready() override;
            void hideButtons();
            void showButtons();
            void setMessage(String mess);
            void setScore(int score);
            void on_timer_gameOver();
            void startMessageTimer();
            String setReadyText(int index);
            
    };
}