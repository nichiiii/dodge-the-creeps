#pragma once

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/classes/marker2d.hpp>
#include <OrangeCharacter/OrangeCharacter.hpp>
#include <godot_cpp/classes/rigid_body2d.hpp>
#include <godot_cpp/classes/path2d.hpp>
#include <godot_cpp/classes/path_follow2d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <EnemMob/EnemMob.hpp>
#include <godot_cpp/classes/button.hpp>
#include <UINode/UINode.hpp>
#include<godot_cpp/classes/engine.hpp>

namespace godot{
    class MainNode : public Node2D{
        GDCLASS(MainNode, Node2D)
        protected:
            static void _bind_methods();
            int score = 0;
            int MsgStartIndex = 0;
            //gameNodes
                Timer* scoreTimer = nullptr;
                Timer* mobTimer = nullptr;
                Timer* startTimer = nullptr;
                Ref<PackedScene> mob_scene = nullptr;
                OrangeCharacter* character = nullptr;
                Path2D* MobSpawnLocation = nullptr;
                PathFollow2D* path = nullptr;
                Marker2D* startingPoint = nullptr;
                Vector2 getStartingPoint;
                UINode* uinode = nullptr;
            //mobSpeed
                float MobMinSpeed = 0.0;
                float MobMaxSpeed = 0.0;
            //mobScene
                void set_mob_scene(const Ref<PackedScene> scene);
                Ref<PackedScene> get_mob_scene();
            //timers
                void on_score_timer_timeout();
                void on_start_timer_timeout();
                void on_mob_timer_timeout();
            //TriggerSignal Methods
                void on_gameOver();
                void on_S_easy();
                void on_S_medium();
                void on_S_extreme();
                void on_returnToMain();
            //reusable codes
                void hideUIandStartTimer();
                void nodeConnection();
                void getNodes();       
                void startGame();   
                void newGame();  

        public:
            MainNode();
            ~MainNode();

            void _ready() override;
    };
}

//add labels
//add signals
