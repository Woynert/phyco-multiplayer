#ifndef MAP_MANAGEMENT_H
#define MAP_MANAGEMENT_H

#include "godot_cpp/classes/node.hpp"
#include <godot_cpp/classes/packed_scene.hpp>

using namespace godot;

void map_generate_prop_ids (Node* node);

void map_instance (Node* node, PackedScene* scene);

#endif // !MAP_MANAGEMENT_H
