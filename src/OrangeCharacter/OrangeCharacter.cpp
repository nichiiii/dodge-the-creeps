#include "OrangeCharacter.hpp"

namespace godot{

    void OrangeCharacter ::_bind_methods(){

        ClassDB :: bind_method(D_METHOD("get_speed"), &OrangeCharacter::getSpeed);
        ClassDB :: bind_method(D_METHOD("set_speed", "c_speed"), &OrangeCharacter::setSpeed);

        ADD_PROPERTY(PropertyInfo(Variant :: FLOAT, "speed"), "set_speed", "get_speed" );

    };

    void OrangeCharacter::_ready(){
        C_animation = get_node<AnimatedSprite2D>("char_animation");

        if (C_animation == nullptr){
            UtilityFunctions::print("animation failed to init");
        }else{
            UtilityFunctions::print("Successfully anim init");
        }
    };

    OrangeCharacter ::OrangeCharacter(){
        UtilityFunctions :: print("OrangeCharacter is created");
    };

    OrangeCharacter ::~OrangeCharacter(){
        UtilityFunctions :: print("OrangeCharacter is destroyed");
    };

    void OrangeCharacter::setSpeed(float c_speed) {
        speed = c_speed;
    }

    float OrangeCharacter::getSpeed() {
        return speed;
    }

    void OrangeCharacter ::move_animation(Vector2 direction){

        if(!C_animation) return;

        if(direction == Vector2()){
            if((*C_animation).is_playing()){
                (*C_animation).stop();
            }
        }else{
            if(direction.x != 0){
                (*C_animation).play("Left_Right");
                (*C_animation).set_flip_v(false);
                (*C_animation).set_flip_h(direction.x < 1);
            }
            else if(direction.y != 0){
                (*C_animation).play("Up_Down");
                (*C_animation).set_flip_v(direction.y > -1);
            }
        }
    }

    void OrangeCharacter ::_process(double delta){

        Vector2 direction = (*input).get_vector("ui_left", "ui_right", "ui_up", "ui_down");
        
        move_animation(direction);
        Vector2 accel = direction.normalized() * speed;
        set_velocity(accel);
        move_and_slide();
    };


}
