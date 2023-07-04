#ifndef OBSERVER_H
#define OBSERVER_H

#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/godot.hpp"
#include "godot_cpp/variant/variant.hpp"

//#include "godot_cpp/core/io/resource.h"
//#include "godot_cpp/core/object/class_db.h"
//#include "godot_cpp/core/object/ref_counted.h"
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/classes/material.hpp>

#include <godot_cpp/core/binder_common.hpp>


//namespace godot{


class Observer : public godot::Node {
    GDCLASS(Observer, godot::Node)

protected:
    static void _bind_methods();

public:
    Observer() {};
    ~Observer() {};

    enum ObjectType {
        PLAYER,
        RIGIDBODY
    };

    void _ready () override;

    void set_type(ObjectType p_speed);
    ObjectType get_type() const;

    void _set_id(int p_id);
    void set_id(int p_id);
    int get_id() const;

private:
    static int id_counter;

    ObjectType type;
    int id;
};


VARIANT_ENUM_CAST(Observer::ObjectType);

//}

#endif

