#pragma once 
#include <godot_cpp/classes/sprite2d.hpp>

namespace godot {

    class MyTestNode : public Sprite2D {
        GDCLASS(MyTestNode, Sprite2D)

        private:
            double time_passed;

        protected:
            static void _bind_methods();

        public:
            MyTestNode();
            ~MyTestNode();
        
            void _process(double delta) override;
    };

}
