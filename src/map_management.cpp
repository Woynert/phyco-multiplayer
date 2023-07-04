#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/classes/scene_tree.hpp"
#include "godot_cpp/variant/typed_array.hpp"
#include <godot_cpp/classes/packed_scene.hpp>

#include "godot_cpp/variant/utility_functions.hpp"
#include "server/observer.h"

using namespace godot;

void map_generate_prop_ids (Node* node)
{
	SceneTree* tree = node->get_tree();
    TypedArray<Node> objs = tree->get_nodes_in_group("observer");
	//Observer* o;

	UtilityFunctions::print("size", objs.size());



	for (int i = 0; i < 2; i++)
	{
		UtilityFunctions::print("---");

		//o = Object::cast_to<Observer>(objs[i]);
        Observer* o = Object::cast_to<Observer>(objs[i]);

		if (!o)
			continue;

		o->_set_id(i);

		UtilityFunctions::print(i, " ", o->get_id(), " ", o->get_name());

	}

	UtilityFunctions::print("finished");
}

// instances an scene

void map_instance (Node* node, PackedScene* scene) 
{
	// clean

	TypedArray<Node> children = node->get_children();
	Node* child;

	for (int i = 0; i < children.size(); i++) {
		child = Object::cast_to<Node>(children[i]);
		child->queue_free();
	}

	// instance scene under

	Node* map = scene->instantiate();
	node->add_child(map);

}

