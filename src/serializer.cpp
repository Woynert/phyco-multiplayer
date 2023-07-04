#include <godot_cpp/classes/scene_tree.hpp>
#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/classes/stream_peer_buffer.hpp"
#include <godot_cpp/classes/input.hpp>
#include "godot_cpp/variant/typed_array.hpp"
#include "packets.h"
#include "server/observer.h"

using namespace godot;

void serialize_inputs (Ref<StreamPeerBuffer> buf) {

	//auto input = Input::get_singleton();
	//int hKey = input->is_action_pressed("gm_right") - input->is_action_pressed("gm_left");
	//int vKey = input->is_action_pressed("gm_down") - input->is_action_pressed("gm_up");
	//bool running = input->is_action_pressed("gm_run");

	auto input = Input::get_singleton();

	// TODO: What happends when write fails?

	PacketInput::Write(
		buf,
		input->is_action_pressed("ui_up"),
		input->is_action_pressed("ui_left"),
		input->is_action_pressed("ui_down"),
		input->is_action_pressed("ui_right"),
		input->is_action_pressed("ui_select"),
		input->is_action_pressed("ui_enter")
	);

}

// converts the world into a serialized

void serialize_game_state (Ref<StreamPeerBuffer> buf, Node* serverRoot) {

    // TODO: Generalize group constant

    SceneTree* tree = serverRoot->get_tree();
    TypedArray<Node> obs = tree->get_nodes_in_group("observer");
	TypedArray<Node> nodes = TypedArray<Node>();

	Observer* observer;
	Node* node;

	for (int i = 0; i < obs.size(); i ++)
	{
		observer = Object::cast_to<Observer>(obs[i]);
		if (!observer)
			continue;

		node = Object::cast_to<Node>(observer->get_node());
		if (!node)
			continue;

		nodes.append(node);
	}



	PacketGameState::Write(buf, nodes);
}
