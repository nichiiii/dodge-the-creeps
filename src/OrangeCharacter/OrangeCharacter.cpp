#include "OrangeCharacter.hpp"

namespace godot{

    void OrangeCharacter ::_bind_methods(){

        ClassDB :: bind_method(D_METHOD("get_speed"), &OrangeCharacter::getSpeed);
        ClassDB :: bind_method(D_METHOD("set_speed", "c_speed"), &OrangeCharacter::setSpeed);

        ADD_PROPERTY(PropertyInfo(Variant :: FLOAT, "speed"), "set_speed", "get_speed" );

    };

    OrangeCharacter ::OrangeCharacter(){
        UtilityFunctions :: print("OrangeCharacter is created");
    };

    OrangeCharacter ::~OrangeCharacter(){
        UtilityFunctions :: print("OrangeCharacter is destroyed");
    };

    void OrangeCharacter::setSpeed(float const c_speed) {
        speed = c_speed;
    }

    float OrangeCharacter::getSpeed() {
        return speed;
    }

    void OrangeCharacter ::_process(double delta){
        
        Input* input = Input :: get_singleton();
        Vector2 direction = input -> get_vector("ui_left", "ui_right", "ui_up", "ui_down");

        Vector2 velocity = direction.normalized() * speed;

        set_velocity(velocity);
        move_and_slide();
    };
}
