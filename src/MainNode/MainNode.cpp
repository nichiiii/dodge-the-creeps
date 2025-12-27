#include "MainNode.hpp"

namespace godot{

    MainNode::MainNode(){
        return;
    }
    MainNode::~MainNode(){
        return;
    }

    void MainNode::_bind_methods(){
        //exports
        ClassDB::bind_method(D_METHOD("get_mob_scene"), &MainNode::get_mob_scene);
        ClassDB::bind_method(D_METHOD("set_mob_scene", "scene"), &MainNode::set_mob_scene);
        //orangeCharacter
        ClassDB::bind_method(D_METHOD("_on_character_hit"), &MainNode::_on_character_hit);
        //timer
        ClassDB::bind_method(D_METHOD("on_score_timer_timeout"), &MainNode::on_score_timer_timeout);
        ClassDB::bind_method(D_METHOD("on_start_timer_timeout"), &MainNode::on_start_timer_timeout);
        ClassDB::bind_method(D_METHOD("on_mob_timer_timeout"), &MainNode::on_mob_timer_timeout);
        //signalsCatcher
        ClassDB::bind_method(D_METHOD("on_S_easy"), &MainNode::on_S_easy);
        ClassDB::bind_method(D_METHOD("on_S_medium"), &MainNode::on_S_medium);
        ClassDB::bind_method(D_METHOD("on_S_extreme"), &MainNode::on_S_extreme);
        
        
        ADD_PROPERTY(PropertyInfo(Variant :: OBJECT, "mob_scene", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_mob_scene", "get_mob_scene");
    }

    void MainNode::set_mob_scene(const Ref<PackedScene> scene){
        mob_scene = scene;
    }
         
    Ref<PackedScene> MainNode::get_mob_scene(){
        return mob_scene;
    }

    void MainNode::_ready(){

        mobTimer = get_node<Timer>("mobTimer");
        scoreTimer = get_node<Timer>("scoreTimer");
        startingPoint = get_node<Marker2D>("starting_point");
        startTimer = get_node<Timer>("startTimer");
        character = get_node<OrangeCharacter>("OrangeCharacter");
        MobSpawnLocation=get_node<Path2D>("MobSpawnLocation");
        uinode = get_node<UINode>("UINode");
        
        if (Engine::get_singleton()->is_editor_hint()) set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);

        if(startingPoint){
           getStartingPoint = startingPoint->get_position();
           UtilityFunctions::print(getStartingPoint);
        }
        if(character) character->connect("C_Hit", Callable(this, "_on_character_hit"));
        if(scoreTimer) scoreTimer->connect("timeout", Callable(this,"on_score_timer_timeout"));
        if(startTimer) startTimer->connect("timeout", Callable(this,"on_start_timer_timeout"));
        if(mobTimer) mobTimer->connect("timeout", Callable(this,"on_mob_timer_timeout")) ;
        if(MobSpawnLocation) path = MobSpawnLocation->get_node<PathFollow2D>("Path");
        if(uinode){
            uinode -> connect("S_easy", Callable(this, "on_S_easy"));
            uinode -> connect("S_medium", Callable(this, "on_S_medium"));
            uinode -> connect("S_extreme", Callable(this, "on_S_extreme"));
        }
        if(mob_scene.is_valid()) UtilityFunctions::print(mob_scene);
        mobTimer -> start();
    }

    void MainNode::_on_character_hit(){ //GAMEOVER METHOD
        scoreTimer->stop();
        mobTimer->stop();
        character->queue_free();
        UtilityFunctions::print("Orange Character was hit");
        return ;
    }

    void MainNode::new_game(){
        score = 0;
        character->start(getStartingPoint);
    }

    void MainNode::on_score_timer_timeout(){
        score++;
    }
    void MainNode::on_start_timer_timeout(){
        mobTimer -> start();
        scoreTimer -> start();
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
        return;
    }
    void MainNode::on_S_medium(){
        
        return;
    }
    void MainNode::on_S_extreme(){
        return;
    }
}


//ready mobspawn
//start game: terminante mob spawn for 3 sec
