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
            AnimatedSprite2D* animation = nullptr;
            VisibleOnScreenNotifier2D* VOSN_mob = nullptr;
        public:
            Vector<String>types = {"fly", "swim", "walk"};
            float getMinSpeed();
            float getMaxSpeed();
            void setMinSpeed(float p_speed);
            void setMaxSpeed(float p_speed);
            void screen_exit();
          
            EnemMob();
            ~EnemMob();
            
            void _ready() override;
    };
}