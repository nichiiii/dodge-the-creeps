#include "OrangeCharacter.hpp"

namespace godot{

    OrangeCharacter::OrangeCharacter(){
        return;
    }
    OrangeCharacter::~OrangeCharacter(){
        return;
    }
    void OrangeCharacter::setSpeed(float c_speed) {
        speed = c_speed;
    }
    float OrangeCharacter::getSpeed() {
        return speed;
    }
    void OrangeCharacter ::_bind_methods(){
        ClassDB :: bind_method(D_METHOD("get_speed"), &OrangeCharacter::getSpeed);
        ClassDB :: bind_method(D_METHOD("set_speed", "c_speed"), &OrangeCharacter::setSpeed);
        ClassDB :: bind_method(D_METHOD("_on_body_entered", "area"), &OrangeCharacter::_on_body_entered);
        ClassDB :: bind_method(D_METHOD("start", "c_pos"), &OrangeCharacter::start);
        ClassDB :: bind_method(D_METHOD("end"), &OrangeCharacter::end);

        ADD_PROPERTY(PropertyInfo(Variant :: FLOAT, "speed"), "set_speed", "get_speed" );
        ADD_SIGNAL(MethodInfo("C_Hit"));
    };
    
      void OrangeCharacter::_ready(){

        C_animation = get_node<AnimatedSprite2D>("char_animation");
        areaScanner = get_node<Area2D>("area_scanner");
        
        if(areaScanner) {
            areaShape = areaScanner->get_node<CollisionShape2D>("area_shape");
            areaScanner->connect("body_entered", Callable(this,"_on_body_entered"));
        }
        if (C_animation) return;
        else  UtilityFunctions::print("cant init");
        
    };

    void OrangeCharacter ::_process(double delta){

        Vector2 direction = (*input).get_vector("ui_left", "ui_right", "ui_up", "ui_down");
        Rect2 getRect = get_viewport_rect();
        Vector2 VP_vec = getRect.size;

        Vector2 pos = get_position();
        Vector2 velo = direction.normalized() * speed;

        pos += velo * (float) delta;
        pos.x = UtilityFunctions::clamp(pos.x, 0.0f, VP_vec.x);
        pos.y = UtilityFunctions::clamp(pos.y, 0.0f, VP_vec.y);
        set_position(pos);

        move_animation(direction);
    };

    void OrangeCharacter::_on_body_entered(Node *body){
        emit_signal("C_Hit");
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

    void OrangeCharacter::start(Vector2 pos){
        set_position(pos);
        areaShape->set_deferred("disabled", false);
        set_process_mode(ProcessMode::PROCESS_MODE_INHERIT);
        set_visible(true);
       
    }

    void OrangeCharacter::end(){
        set_process_mode(ProcessMode::PROCESS_MODE_DISABLED);
        set_visible(false);
        areaShape->set_deferred("disabled", true);
    }
}
