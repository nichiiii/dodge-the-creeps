#pragma once

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/classes/marker2d.hpp>
#include "OrangeCharacter/OrangeCharacter.hpp"

namespace godot{
    class MainNode : public Node2D{
        GDCLASS(MainNode, Node2D)

        protected:
            static void _bind_methods();
            int score = 0;

            Timer* scoreTimer = nullptr;
            Timer* mobspawn = nullptr;
            Timer* startTimer = nullptr;
            Ref<PackedScene> mob_scene = nullptr;
            OrangeCharacter* character = nullptr;

            Marker2D* startingPoint = nullptr;

            Vector2 setStartingPoint;

            void set_mob_scene(const Ref<PackedScene> scene);
                       
            Ref<PackedScene> get_mob_scene();
        public:
            MainNode();
            ~MainNode();

            void _ready() override;
            void _on_character_hit();
            void new_game();
 
    };
}