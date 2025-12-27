#include "UINode.hpp"


namespace godot{
    UINode::UINode(){
        return;
    }
    UINode::~UINode(){
        return;
    }

    void UINode::_bind_methods(){
        ClassDB::bind_method(D_METHOD("on_pressed_easy"), &UINode::on_pressed_easy);
        ClassDB::bind_method(D_METHOD("on_pressed_medium"), &UINode::on_pressed_medium);
        ClassDB::bind_method(D_METHOD("on_pressed_extreme"), &UINode::on_pressed_extreme);

        ADD_SIGNAL(MethodInfo("S_easy"));
        ADD_SIGNAL(MethodInfo("S_medium"));
        ADD_SIGNAL(MethodInfo("S_extreme"));
    }
   
    void UINode::_ready(){
        scoreLabel =  get_node<Label>("scoreLabel");
        message = get_node<Label>("message");
        categBtnContainer = get_node<VBoxContainer>("categBtnContainer");
        messageTimer= get_node<Timer>("messageTimer");
        if(categBtnContainer){
            connectButtons();
        }
    }
    
    void UINode::on_pressed_easy(){
        emit_signal("S_easy");
    }
    void UINode::on_pressed_medium(){
        emit_signal("S_medium");
    }
    void UINode::on_pressed_extreme(){
        emit_signal("S_extreme");
    }

    void UINode::connectButtons(){
        easy = categBtnContainer -> get_node<Button>("easy");
        medium = categBtnContainer -> get_node<Button>("medium");
        extreme = categBtnContainer -> get_node<Button>("extreme");

        if(easy) easy->connect("pressed", Callable(this, "on_pressed_easy"));
        if(medium) medium->connect("pressed", Callable(this, "on_pressed_medium"));
        if(extreme) extreme->connect("pressed", Callable(this, "on_pressed_extreme"));
    }
}

