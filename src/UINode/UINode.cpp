
#include "UINode.hpp"
#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/label.hpp>

#include <godot_cpp/classes/v_box_container.hpp>

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
        ClassDB::bind_method(D_METHOD("on_timer_gameOver"), &UINode::on_timer_gameOver);

        ADD_SIGNAL(MethodInfo("S_easy"));
        ADD_SIGNAL(MethodInfo("S_medium"));
        ADD_SIGNAL(MethodInfo("S_extreme"));
        ADD_SIGNAL(MethodInfo("returnToMain"));
    }
   
    void UINode::_ready(){
        getNodes();
        if(categBtnContainer){
            easy = categBtnContainer -> get_node<Button>("easy");
            medium = categBtnContainer -> get_node<Button>("medium");
            extreme = categBtnContainer -> get_node<Button>("extreme");
            connectNodes();
        }
    }
    void UINode::getNodes(){
        scoreLabel =  get_node<Label>("scoreLabel");
        message = get_node<Label>("message");
        categBtnContainer = get_node<VBoxContainer>("categBtnContainer");
        messageTimer= get_node<Timer>("messageTimer");
    }
    void UINode::connectNodes(){
        if(easy) easy->connect("pressed", Callable(this, "on_pressed_easy"));
        if(medium) medium->connect("pressed", Callable(this, "on_pressed_medium"));
        if(extreme) extreme->connect("pressed", Callable(this, "on_pressed_extreme"));
        if(messageTimer) messageTimer->connect("timeout", Callable(this, "on_timer_gameOver"));
    }

    void UINode::setMessage(String mess){
        if(!message) return;
        message-> set_text(mess);
    }
    String UINode::setReadyText(int index){
        return readyMessage[index];
    }
    void UINode::setScore(int score){
        String setScore = String::num_int64(score);
        scoreLabel->set_text(setScore);
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
     void UINode::on_timer_gameOver(){
        emit_signal("returnToMain");
    }

    void UINode::hideButtons(){
        easy->set_visible(false);
        easy->set_process_mode(ProcessMode::PROCESS_MODE_DISABLED);
        medium->set_visible(false);
        medium->set_process_mode(ProcessMode::PROCESS_MODE_DISABLED);
        extreme->set_visible(false);
        extreme->set_process_mode(ProcessMode::PROCESS_MODE_DISABLED);

        message->set_text("");
        scoreLabel->set_visible(true);
    }

    void UINode::showButtons(){
        easy->set_visible(true);
        easy->set_process_mode(ProcessMode::PROCESS_MODE_INHERIT);
        medium->set_visible(true);
        medium->set_process_mode(ProcessMode::PROCESS_MODE_INHERIT);
        extreme->set_visible(true);
        extreme->set_process_mode(ProcessMode::PROCESS_MODE_INHERIT);

        message->set_text("Dodge the Creeps");
        scoreLabel->set_visible(false);
        scoreLabel ->set_text("0");
    }

    void UINode::startMessageTimer(){
        messageTimer -> start();
    }
}

