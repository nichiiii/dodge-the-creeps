#pragma once

#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/timer.hpp>
namespace godot{
    class UINode : public CanvasLayer{
        GDCLASS(UINode, CanvasLayer)

        protected:
            static void _bind_methods();
            Label* scoreLabel = nullptr;
            Label* message = nullptr;
            VBoxContainer *categBtnContainer = nullptr;
            Timer* messageTimer = nullptr; 

            Button* easy = nullptr;
            Button* medium = nullptr;
            Button* extreme = nullptr;
            
           

        public:
            UINode();
            ~UINode();
            void on_pressed_easy();
            void on_pressed_medium();
            void on_pressed_extreme();
            void _ready() override;
            void connectButtons();
    };
}