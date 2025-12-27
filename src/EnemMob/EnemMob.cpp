#include "EnemMob.hpp"

namespace godot{

    EnemMob::EnemMob(){
        return;
    }
    EnemMob::~EnemMob(){
        return;
    }
    
    void EnemMob::_bind_methods(){
        ClassDB::bind_method(D_METHOD("screen_exit"), &EnemMob::screen_exit);

        ClassDB::bind_method(D_METHOD("setMaxSpeed", "maxspeed"), &EnemMob::setMaxSpeed);
        ClassDB::bind_method(D_METHOD("setMinSpeed", "minspeed"), &EnemMob::setMinSpeed);
        ClassDB::bind_method(D_METHOD("getMaxSpeed"), &EnemMob::getMaxSpeed);
        ClassDB::bind_method(D_METHOD("getMinSpeed"), &EnemMob::getMinSpeed);

        ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "minspeed"), "setMinSpeed", "getMinSpeed");
        ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "maxspeed"), "setMaxSpeed", "getMaxSpeed"); 
    }

    float EnemMob::getMaxSpeed(){
        return maxspeed;
    }
    float EnemMob::getMinSpeed(){
        return minspeed;
    }
    void EnemMob::setMaxSpeed(float maxspeed){
        this->maxspeed = maxspeed;
    }
    void EnemMob::setMinSpeed(float minspeed){
        this->minspeed = minspeed;
    } 
    void EnemMob::screen_exit(){
        animation->stop();
        queue_free();
    }
    
    void EnemMob::_ready(){
        VOSN_mob = get_node<VisibleOnScreenNotifier2D>("onExitNotifier");      
        animation = get_node<AnimatedSprite2D>("mob_sprites");

        if(VOSN_mob) VOSN_mob-> connect("screen_exited", Callable(this, "screen_exit"));
        
        if(animation) animation->play(types[UtilityFunctions::randi_range(0, (types.size() - 1))]);
        
        else return;
    }

 
}