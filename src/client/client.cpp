#include "godot_cpp/classes/e_net_connection.hpp"
#include "godot_cpp/classes/global_constants.hpp"
#include "godot_cpp/classes/stream_peer_buffer.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/core/error_macros.hpp"
#include "godot_cpp/godot.hpp"
#include "godot_cpp/variant/array.hpp"
#include "godot_cpp/variant/packed_byte_array.hpp"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/e_net_packet_peer.hpp>

#include "client.h"
#include "../packets.h"
#include "../serializer.h"

using namespace godot;

void Client::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_port"), &Client::get_port);
	ClassDB::bind_method(D_METHOD("set_port", "p_port"), &Client::set_port);
	ClassDB::add_property(
		"Client",
		PropertyInfo(Variant::INT, "port", PROPERTY_HINT_NONE),
		"set_port", "get_port"
	);

	ClassDB::bind_method(D_METHOD("get_address"), &Client::get_address);
	ClassDB::bind_method(D_METHOD("set_address", "p_address"), &Client::set_address);
	ClassDB::add_property(
		"Client",
		PropertyInfo(Variant::STRING, "address"),
		"set_address", "get_address"
	);

	ClassDB::bind_method(D_METHOD("start"), &Client::start);
}

Client::Client() {
    // Initialize any variables here
	//conn.instantiate();
}

Client::~Client() {
    // Add your cleanup here

}

bool Client::start() {


	if (!conn.is_valid()) {

		conn.instantiate();

		if (!conn.is_valid())
			return false;

		// TODO: Error check, and specify reason

		Error err = conn->create_host(1, max_channels);

		if (err != OK){
			return false;
		}

	}

	UtilityFunctions::print("add: ", bind_address, " port: ", bind_port);
	UtilityFunctions::print("connecting");
		
	peer = conn->connect_to_host(bind_address, bind_port, max_channels);

	if (!peer.is_valid())
		return false;

	if (peer.ptr() == NULL){
		return false;
	}

	UtilityFunctions::print("Connected?", peer);
	UtilityFunctions::print("peer is active?", peer->is_active());
	UtilityFunctions::print("peer info", peer->get_remote_address());
	UtilityFunctions::print("peer info", peer->get_state());

	set_process(true);
	return true;
}

bool Client::stop() {
	set_process(false);

	if (!conn.is_valid())
		return true;

	conn->destroy();

	return true;
}

void Client::_process(double delta) {
    if (Engine::get_singleton()->is_editor_hint())
        return;

	// step

	time_elapsed += delta;

	if (time_elapsed > time_interval){

		int times = (int) (time_elapsed / time_interval);
		time_elapsed -= times * time_interval;

		// send state
		//send_packages();
	}

	if (!conn.is_valid()){
		return;
	}

	// listen to new packages

	Array pull = conn->service();

	int event_int = (int)pull[0];
	ENetConnection::EventType event = (ENetConnection::EventType) event_int;

	// get peer 

	Ref<ENetPacketPeer> peer = Object::cast_to<ENetPacketPeer>(pull[1]);


	switch (event) {
		case ENetConnection::EVENT_CONNECT: {
			UtilityFunctions::print("EVENT_CONNECT");

			if (peer == nullptr)
			{
				UtilityFunctions::print("Warning: Null peer", peer);
				return;
			}

			this->peer = peer;

		}
		break;
		case ENetConnection::EVENT_DISCONNECT: {
			UtilityFunctions::print("EVENT_DISCONNECT");
		}
		break;
		case ENetConnection::EVENT_RECEIVE: {
			UtilityFunctions::print("EVENT_RECEIVE");

			PackedByteArray data = peer->get_packet();
			this->consume_package(&data);
		}
		break;
		case ENetConnection::EVENT_ERROR: {
			UtilityFunctions::print("EVENT_ERROR");
		}
		break;
		case ENetConnection::EVENT_NONE: {
			//UtilityFunctions::print("EVENT_NONE");
		}
		break;
		default:
		break;
	}
}

void Client::consume_package (PackedByteArray* packet) {

	Ref<StreamPeerBuffer> buf;
	buf.instantiate();
	buf->put_data(*packet);

	PACKET_TYPE type = get_packet_type(buf);

	switch (type) {
		case PACKET_TYPE::JOIN_REQUEST_ACK:
			UtilityFunctions::print("Received: JOIN_REQUEST_ACK");
			break;

		case PACKET_TYPE::GAME_STATE:
			{
				UtilityFunctions::print("Received: GAME_STATE");
				PacketGameState packet;
				packet.Read(buf);

			}
			break;

		default:
			break;
	}
}

void Client::send_packages () {

	// TODO: Print errors or warnings

	if (!peer.is_valid())
		return;

	if (!peer->is_active())
		return;

	// get user inputs

	Ref<StreamPeerBuffer> buf;
	buf.instantiate();

	if (!buf.is_valid())
		return;

	serialize_inputs(buf);

	// send

	peer->send(0, buf->get_data_array(), ENetPacketPeer::FLAG_UNRELIABLE_FRAGMENT);
}

// setters getters


int Client::get_port () const {
	return bind_port;
}

void Client::set_port (const int p_port){
	bind_port = p_port;
}

String Client::get_address () const {
	return bind_address;
}

void Client::set_address (const String p_address){
	bind_address = p_address;
}
