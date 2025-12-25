#include "MainNode.hpp"

namespace godot{

    MainNode::MainNode(){
        return;
    }
    MainNode::~MainNode(){
        return;
    }

    void MainNode::_bind_methods(){

        ClassDB::bind_method(D_METHOD("get_mob_scene"), &MainNode::get_mob_scene);
        ClassDB::bind_method(D_METHOD("set_mob_scene", "scene"), &MainNode::set_mob_scene);
        ClassDB::bind_method(D_METHOD("_on_character_hit"), &MainNode::_on_character_hit);

        ADD_PROPERTY(PropertyInfo(Variant :: OBJECT, "mob_scene", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_mob_scene", "get_mob_scene");
    }

  

    void MainNode::set_mob_scene(const Ref<PackedScene> scene){
        this->mob_scene = scene;
    }
         
    Ref<PackedScene> MainNode::get_mob_scene(){
        return mob_scene;
    }

    void MainNode::_ready(){

        mobspawn = get_node<Timer>("mobTimer");
        scoreTimer = get_node<Timer>("scoreTimer");
        startingPoint = get_node<Marker2D>("starting_point");
        startTimer = get_node<Timer>("startTimer");
        character = get_node<OrangeCharacter>("OrangeCharacter");

        if(startingPoint){
           setStartingPoint = startingPoint->get_position();
           UtilityFunctions::print(setStartingPoint);
        }
        if(character){
            character-> connect("C_Hit", Callable(this, "_on_character_hit"));
        }
    }

    void MainNode::_on_character_hit(){
        scoreTimer->stop();
        mobspawn->stop();
        UtilityFunctions::print("helo");
        return ;
    }

    void MainNode::new_game(){
        score = 0;
        character->start(setStartingPoint);

    }

   
    
}