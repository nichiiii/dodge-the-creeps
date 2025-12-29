#pragma once

//nodes 
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>

//user/engine interactions
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/input.hpp>

namespace godot{

    class OrangeCharacter : public CharacterBody2D{
        
        GDCLASS(OrangeCharacter, CharacterBody2D )

        private: 
            float speed = 600.0; 

        protected:
            static void _bind_methods();

            Input* input = Input :: get_singleton();
            AnimatedSprite2D* C_animation = nullptr;
            Area2D* areaScanner = nullptr;
            CollisionShape2D* areaShape = nullptr;
            
        public : 
            OrangeCharacter();
            ~OrangeCharacter();

            //GODOT LIFECYCLE
            void _ready() override;
            void _process(double delta) override;
            //EXPORTING SPEED
            void setSpeed(float c_speed);   
            float getSpeed();
            //SIGNALS 
            void _on_body_entered(Node *body);
            //OTHERS
            void move_animation(Vector2 direction);
            void start(Vector2 pos);
            void end();
    
    };
}