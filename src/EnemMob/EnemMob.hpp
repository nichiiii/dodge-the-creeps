#pragma once
#include <godot_cpp/classes/area2d.hpp>

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/visible_on_screen_notifier2d.hpp>
#include <godot_cpp/classes/rigid_body2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>

namespace godot{
    class EnemMob : public RigidBody2D{
        GDCLASS(EnemMob, RigidBody2D)

        protected:
            static void _bind_methods();
          
            float maxspeed = 400;
            float minspeed = 300;
         

            VisibleOnScreenNotifier2D* VOSN_mob = nullptr;
        public:
            float getMinSpeed();
            float getMaxSpeed();
            void setMinSpeed(float p_speed);
            void setMaxSpeed(float p_speed);  
            AnimatedSprite2D* animation = nullptr;
            
            EnemMob();
            ~EnemMob();
            
            Vector<String>types = {"fly", "swim", "walk"};

            void _ready() override;

            void screen_exit();
            
    };
}