
#include "MainNode.hpp"

#include <EnemMob/EnemMob.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <UINode/UINode.hpp>
#include <godot_cpp/classes/path_follow2d.hpp>
#include <OrangeCharacter/OrangeCharacter.hpp>
#include <godot_cpp/classes/path2d.hpp>
#include <godot_cpp/classes/marker2d.hpp>
#include <godot_cpp/classes/timer.hpp>

namespace godot{

    MainNode::MainNode(){
        return;
    }
    MainNode::~MainNode(){
        return;
    }

    void MainNode::_bind_methods(){
            ClassDB::bind_method(D_METHOD("on_gameOver"), &MainNode::on_gameOver);
            ClassDB::bind_method(D_METHOD("on_score_timer_timeout"), &MainNode::on_score_timer_timeout);
            ClassDB::bind_method(D_METHOD("on_start_timer_timeout"), &MainNode::on_start_timer_timeout);
            ClassDB::bind_method(D_METHOD("on_mob_timer_timeout"), &MainNode::on_mob_timer_timeout);
            ClassDB::bind_method(D_METHOD("on_S_easy"), &MainNode::on_S_easy);
            ClassDB::bind_method(D_METHOD("on_S_medium"), &MainNode::on_S_medium);
            ClassDB::bind_method(D_METHOD("on_S_extreme"), &MainNode::on_S_extreme);
            ClassDB::bind_method(D_METHOD("on_returnToMain"), &MainNode::on_returnToMain);
    }

    void MainNode::_ready(){      
        preloadScn = ResourceLoader::get_singleton();
        if(preloadScn){
            mob_scene = preloadScn -> load("res://scenes/enem_mob.tscn");
        }
        getNodes();
        nodeConnection();
        mobTimer -> start();
    }

    /*NODES SETUP*/
    void MainNode::getNodes(){
        mobTimer = get_node<Timer>("mobTimer");
        scoreTimer = get_node<Timer>("scoreTimer");
        startingPoint = get_node<Marker2D>("starting_point");
        startTimer = get_node<Timer>("startTimer");
        character = get_node<OrangeCharacter>("OrangeCharacter");
        MobSpawnLocation= get_node<Path2D>("MobSpawnLocation");
        uinode = get_node<UINode>("UINode");

        if(MobSpawnLocation) path = MobSpawnLocation->get_node<PathFollow2D>("Path");
    }
    void MainNode::nodeConnection(){
        if(character) character->connect("C_Hit", Callable(this, "on_gameOver"));
        if(scoreTimer) scoreTimer->connect("timeout", Callable(this,"on_score_timer_timeout"));
        if(startTimer) startTimer->connect("timeout", Callable(this,"on_start_timer_timeout"));
        if(mobTimer) mobTimer->connect("timeout", Callable(this,"on_mob_timer_timeout")) ;
        if(uinode){
            uinode -> connect("S_easy", Callable(this, "on_S_easy"));
            uinode -> connect("S_medium", Callable(this, "on_S_medium"));
            uinode -> connect("S_extreme", Callable(this, "on_S_extreme"));
            uinode -> connect ("returnToMain", Callable(this,"on_returnToMain"));
        }
    }
    
    /*TRIGGER BY SIGNAL METHODS*/
    void MainNode::on_gameOver(){ //on character hit
        MobMaxSpeed = 0.0;
        MobMinSpeed = 0.0;
        score = 0;
        scoreTimer->stop();
        mobTimer->stop();
        character -> call_deferred("end");
        uinode->setMessage("Game Over");
        uinode->startMessageTimer();
    }
    void MainNode::on_score_timer_timeout(){
        uinode->setScore(score);
        score++;
    }

    void MainNode::on_start_timer_timeout(){
        if(MsgStartIndex >= 3){
            startGame();
            return;
        }
        uinode->setMessage(uinode->setReadyText(MsgStartIndex));
        MsgStartIndex++;
    }
   
    void MainNode::on_mob_timer_timeout(){
        if(!mob_scene.is_valid()) return;
        EnemMob* mob = Object::cast_to<EnemMob>(mob_scene->instantiate());
        if(!mob) return;
        path->set_progress_ratio(UtilityFunctions::randf());
        mob->set_position(path -> get_position());

        float direction = (path -> get_rotation()) + Math_PI / 2;
        direction += UtilityFunctions::randf_range(-Math_PI / 4, Math_PI / 4);
        mob->set_rotation(direction);

        if (MobMinSpeed && MobMaxSpeed){
            mob->setMinSpeed(MobMinSpeed);
            mob->setMaxSpeed(MobMaxSpeed);
        }
        Vector2 mob_velocity = Vector2(UtilityFunctions::randf_range(mob->getMinSpeed(),mob->getMaxSpeed()), 0);
        mob->set_linear_velocity(mob_velocity.rotated(direction));
        add_child(mob);
    }
   
    void MainNode::on_S_easy(){
        hideUIandStartTimer();
    }
    void MainNode::on_S_medium(){
        hideUIandStartTimer();
        MobMaxSpeed = 700;
        MobMinSpeed  = 500;
    }
    void MainNode::on_S_extreme(){
        hideUIandStartTimer();
        MobMaxSpeed = 1100;
        MobMinSpeed  = 700;
    }

    void MainNode::on_returnToMain(){
        uinode->showButtons();
        mobTimer->start();
    }
   
    /*REUSABLE METHODS*/
    void MainNode::newGame(){
        if(!startingPoint) return;
            getStartingPoint = startingPoint->get_position();
            character->start(getStartingPoint);
    }
    void MainNode::hideUIandStartTimer(){
        uinode->hideButtons();
        mobTimer->stop();
        startTimer->start();
    }
    void MainNode:: startGame(){
        uinode->setMessage("");
        startTimer -> stop();
        MsgStartIndex = 0;
        mobTimer -> start();
        scoreTimer -> start();
        newGame();
    }
}
