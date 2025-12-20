#pragma once

//nodes 
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>

//user/engine interactions
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/input.hpp>

namespace godot{

    class OrangeCharacter : public CharacterBody2D{
        
        GDCLASS(OrangeCharacter, CharacterBody2D )

        private: 
            float speed = 100.0; 

        protected:
            static void _bind_methods();

            Input* input = Input :: get_singleton();
            AnimatedSprite2D* C_animation = nullptr;
            
        public : 
            OrangeCharacter();
            ~OrangeCharacter();

            void _ready() override;
            void _process(double delta) override;

            void setSpeed(float c_speed);   
            float getSpeed();

            void move_animation(Vector2 direction);
    };
}