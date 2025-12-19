#include "MyTestNode.hpp"

using namespace godot;

void MyTestNode::_bind_methods() {
}

MyTestNode::MyTestNode() {
	// Initialize any variables here.
	time_passed = 0.0;
}

MyTestNode::~MyTestNode() {
	// Add your cleanup here.
}

void MyTestNode::_process(double delta) {
	time_passed += delta;

	Vector2 new_position = Vector2(10.0 + (10.0 * sin(time_passed * 2.0)), 10.0 + (10.0 * cos(time_passed * 1.5)));

	set_position(new_position);
}
