#include "godot_cpp/classes/e_net_connection.hpp"
#include "godot_cpp/classes/e_net_packet_peer.hpp"
#include "godot_cpp/classes/object.hpp"
#include "godot_cpp/classes/packed_scene.hpp"
#include "godot_cpp/classes/stream_peer_buffer.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/core/error_macros.hpp"
#include "godot_cpp/godot.hpp"
#include "godot_cpp/variant/array.hpp"
#include "godot_cpp/variant/packed_byte_array.hpp"
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "../map_management.h"
#include "../packets.h"
#include "../serializer.h"
#include "server.h"
#include "slot_management.hpp"

using namespace godot;

void Server::_bind_methods ()
{
	ClassDB::bind_method (D_METHOD ("start"), &Server::start);
	ClassDB::bind_method (D_METHOD ("stop"), &Server::stop);
	ClassDB::bind_method (
		D_METHOD ("goto_level", "p_scene"), &Server::goto_level);
}

Server::Server ()
{
	// initialize available slots

	this->available_slots.resize (this->max_peers, true);
	this->slots.resize (this->max_peers, nullptr);
}

Server::~Server ()
{
	// Add your cleanup here
}

bool Server::start ()
{

	if (!conn.is_valid ()) {

		conn.instantiate ();

		if (!conn.is_valid ())
			return false;
	}

	// start host

	Error err = conn->create_host_bound (
		bind_address, bind_port, max_peers, max_channels);

	if (err != OK) {
		return false;
	}

	set_process (true);

	return true;
}

bool Server::stop ()
{
	set_process (false);

	if (!conn.is_valid ())
		return true;

	conn->destroy ();

	return true;
}

bool Server::goto_level (PackedScene* scene)
{
	map_instance (this, scene);

	map_generate_prop_ids (this);

	return true;
}

void Server::send_to_all_peers (PackedByteArray packet)
{
	for (int i = 0; i < this->max_peers; i++) {
		if (!this->available_slots[i]) {
			PlayerStruct* player = this->slots[i];
			Ref<ENetPacketPeer> peer = player->peer;

			peer->send (0, packet, ENetPacketPeer::FLAG_UNRELIABLE_FRAGMENT);
		}
	}
}

void Server::_process (double delta)
{

	if (Engine::get_singleton ()->is_editor_hint ())
		return;

	if (!conn.is_valid ()) {
		return;
	}

	// step

	time_elapsed += delta;

	if (time_elapsed > time_interval) {

		int times = (int)(time_elapsed / time_interval);
		time_elapsed -= times * time_interval;

		// send state

		// TODO: Check server state
		// TODO: Send custom state to each client

		Ref<StreamPeerBuffer> buff;
		buff.instantiate ();

		serialize_game_state (buff, this);
		this->send_to_all_peers (buff->get_data_array ());

		// send_packages();

		show_slots_info (this);
	}

	// listen to new packages
	// TODO: object_cast? how to safely check wheter this cast fails

	// UtilityFunctions::print("connection check");

	Array pull = conn->service ();

	// get event type

	int event_int = (int)pull[0];
	ENetConnection::EventType event = (ENetConnection::EventType)event_int;

	// get peer

	Ref<ENetPacketPeer> peer = Object::cast_to<ENetPacketPeer> (pull[1]);

	// PackedByteArray* data = new PackedByteArray(pull[1]);
	// Ref<PackedByteArray> data = pull.pop_at(1);

	switch (event) {
	case ENetConnection::EVENT_CONNECT: {

		UtilityFunctions::print ("EVENT_CONNECT");
		UtilityFunctions::print (peer);

		// check slot availability

		int slot = get_available_slot (this);

		// no space left

		if (slot == -1) {
			return;
		}

		// add new peer

		add_player_to_slot (this, slot, peer);

	} break;
	case ENetConnection::EVENT_DISCONNECT: {
		UtilityFunctions::print ("EVENT_DISCONNECT");

		free_slot (this, peer);
	} break;
	case ENetConnection::EVENT_RECEIVE: {
		UtilityFunctions::print ("EVENT_RECEIVE");

		// consume_package(data);
	} break;
	case ENetConnection::EVENT_ERROR: {
		UtilityFunctions::print ("EVENT_ERROR");
	} break;
	case ENetConnection::EVENT_NONE: {
		// UtilityFunctions::print("EVENT_NONE");
	} break;
	default:
		break;
	}
}

void Server::consume_package (PackedByteArray* packet)
{

	Ref<StreamPeerBuffer> buf;
	buf.instantiate ();
	buf->put_data (*packet);

	PACKET_TYPE type = get_packet_type (buf);

	switch (type) {
	case PACKET_TYPE::JOIN_REQUEST:
		UtilityFunctions::print ("Received: JOIN_REQUEST");
		break;

	case PACKET_TYPE::INPUT:
		UtilityFunctions::print ("Received: INPUT");
		break;
	}
}
