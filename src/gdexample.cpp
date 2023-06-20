#include "gdexample.h"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/core/error_macros.hpp"
#include "godot_cpp/godot.hpp"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>

using namespace godot;

void GDExample::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_speed"), &GDExample::get_speed);
    ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &GDExample::set_speed);
    ClassDB::add_property(
        "GDExample",
        PropertyInfo(Variant::FLOAT, "speed", PROPERTY_HINT_RANGE, "0,20,0.01"),
        "set_speed", "get_speed"
    );

    ADD_SIGNAL(MethodInfo("position_changed", PropertyInfo(Variant::OBJECT, "node"), PropertyInfo(Variant::VECTOR2, "new_pos")));
}

GDExample::GDExample() {
    // Initialize any variables here
    time_emit = 0.0;
    speed = 10.0;
}

GDExample::~GDExample() {
    // Add your cleanup here
}

void GDExample::_physics_process(double delta){
    if (Engine::get_singleton()->is_editor_hint())
        return;

    Vector2 pos = get_global_position();
    set_position(Vector2(pos.x + speed * delta, pos.y));

    // emit signal

    time_emit += delta;
    if (time_emit > 1.0) {
        emit_signal("position_changed", this, get_global_position());
        UtilityFunctions::print("Emmitting signal");

        time_emit = 0.0;
    }
}

// setters / getters

void GDExample::set_speed(const double p_speed) {
    speed = p_speed;
}

double GDExample::get_speed() const {
    return speed;
}
