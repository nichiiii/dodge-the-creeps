#pragma once
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/input.hpp>

namespace godot{

    class OrangeCharacter : public CharacterBody2D{
        
        GDCLASS(OrangeCharacter, CharacterBody2D )

        private: 
            float speed = 100.0; 

        protected:
            static void _bind_methods();
            
        public : 
            OrangeCharacter();
            ~OrangeCharacter();
            
            void _process(double delta) override;

            void setSpeed(float const c_speed);

            float getSpeed();
    };
}