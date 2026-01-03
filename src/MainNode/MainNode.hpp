#pragma once


#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

namespace godot{
//Forward declarations
    class UINode;
    class OrangeCharacter;
    class Path2D;
    class PathFollow2D;
    class Marker2D;
    class Timer;

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
                ResourceLoader*  preloadScn = nullptr;
                OrangeCharacter* character = nullptr;
                Path2D* MobSpawnLocation = nullptr;
                PathFollow2D* path = nullptr;
                Marker2D* startingPoint = nullptr;
                Vector2 getStartingPoint;
                UINode* uinode = nullptr;
            //mobSpeed
                float MobMinSpeed = 0.0;
                float MobMaxSpeed = 0.0;
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

