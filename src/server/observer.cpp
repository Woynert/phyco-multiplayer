#include "godot_cpp/classes/global_constants.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/core/error_macros.hpp"
#include "godot_cpp/godot.hpp"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>

#include "observer.h"

using namespace godot;

void Observer::_bind_methods() {
    //PropertyInfo(Variant::INT, "type", PROPERTY_HINT_RANGE, "0,20,0.01"),

    ClassDB::bind_method(D_METHOD("get_type"), &Observer::get_type);
    ClassDB::bind_method(D_METHOD("set_type", "type"), &Observer::set_type);

    ClassDB::bind_method(D_METHOD("get_id"), &Observer::get_id);
    ClassDB::bind_method(D_METHOD("set_id", "id"), &Observer::set_id);

    ADD_PROPERTY(
        PropertyInfo(Variant::INT, "type", PROPERTY_HINT_ENUM, "Player,RigidBody"),
        "set_type", "get_type"
    );

    ADD_PROPERTY(
        PropertyInfo(Variant::INT, "id", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_EDITOR | PROPERTY_USAGE_READ_ONLY),
        "set_id", "get_id"
    );

    BIND_ENUM_CONSTANT(PLAYER);
	BIND_ENUM_CONSTANT(RIGIDBODY);

}

void Observer::_ready() 
{
    // add parent to observer group

    auto parent = get_parent();
    parent->add_to_group("observer");
};

void Observer::set_type(Observer::ObjectType p_type){
    type = p_type;
}

Observer::ObjectType Observer::get_type() const {
    return type;
}

void Observer::_set_id(int p_id) 
{
    id = p_id;
}

void Observer::set_id(int p_id) 
{
    return;
}

int Observer::get_id() const
{
    return id;
}

// state serializers



