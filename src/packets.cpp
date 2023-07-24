#include "godot_cpp/classes/object.hpp"
#include "godot_cpp/godot.hpp"
#include "godot_cpp/variant/array.hpp"
#include "godot_cpp/variant/packed_byte_array.hpp"
#include "godot_cpp/variant/string.hpp"
#include "godot_cpp/variant/typed_array.hpp"
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/rigid_body2d.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/stream_peer.hpp>
#include <godot_cpp/classes/stream_peer_buffer.hpp>
#include <godot_cpp/variant/packed_byte_array.hpp>

#include "godot_cpp/variant/utility_functions.hpp"
#include "packets.h"

using namespace godot;

PACKET_TYPE get_packet_type (Ref<StreamPeerBuffer> buffer)
{
	buffer->seek (0);
	uint8_t type_int = buffer->get_8 ();
	PACKET_TYPE type = (PACKET_TYPE)type_int;
	return type;
}

bool PacketJoinRequest::Write (Ref<StreamPeerBuffer> buffer, String username)
{

	// length limit

	int64_t length = username.length ();
	if (username.length () > 250)
		return false;

	buffer->put_8 ((int8_t)type);

	buffer->put_8 ((int8_t)username.length ());
	buffer->put_data (username.to_ascii_buffer ());

	return true;
}

bool PacketJoinRequest::Read (Ref<StreamPeerBuffer> buffer)
{

	// TODO: Error check

	int8_t length = buffer->get_8 ();

	if (length < 1)
		return false;

	String username = buffer->get_string (length);
	this->username = username;

	return true;
}

bool PacketQuitRequest::Write (Ref<StreamPeerBuffer> buffer)
{
	buffer->put_8 ((int8_t)type);
	return true;
}

bool PacketInput::Write (
	Ref<StreamPeerBuffer> buffer, bool w, bool a, bool s, bool d, bool action1,
	bool action2)
{

	// 00000000
	// wasd1200

	uint8_t input = (w << 7) + (a << 6) + (s << 5) + (d << 4) + (action1 << 3) +
					(action2 << 2);

	buffer->put_8 ((int8_t)type);
	buffer->put_u8 (input);

	return true;
}

bool PacketInput::Read (Ref<StreamPeerBuffer> buffer)
{

	uint8_t input = buffer->get_u8 ();

	this->w = (input >> 7) & 1;
	this->a = (input >> 6) & 1;
	this->s = (input >> 5) & 1;
	this->d = (input >> 4) & 1;
	this->action1 = (input >> 3) & 1;
	this->action2 = (input >> 2) & 1;

	return true;
};

bool PacketJoinRequestAck::Write (Ref<StreamPeerBuffer> buffer)
{
	buffer->put_8 ((int8_t)type);
	return true;
}

bool PacketGameState::Write (
	Ref<StreamPeerBuffer> buffer, TypedArray<RigidBody2D> objs)
{
	buffer->put_8 ((int8_t)type);

	// number of objects to update
	// TODO: What to do when too many objects?

	int amount = objs.size ();
	UtilityFunctions::print (amount);

	buffer->put_u8 (amount);

	// object:
	// id
	// global position x, y
	// global rotation
	// linear velocity x, y
	// angular velocity

	for (int i = 0; i < amount; i++) {
		RigidBody2D* o = Object::cast_to<RigidBody2D> (objs[i]);

		// TODO: Use assert or some debug mechanism
		if (o == nullptr)
			return false;

		Vector2 pos = o->get_global_position ();
		Vector2 vel = o->get_linear_velocity ();

		buffer->put_float (pos.x);
		buffer->put_float (pos.y);
		buffer->put_float (o->get_global_rotation ());
		buffer->put_float (vel.x);
		buffer->put_float (vel.y);
		buffer->put_float (o->get_angular_velocity ());
	}

	return true;
}

bool PacketGameState::Read (Ref<StreamPeerBuffer> buffer)
{

	int amount = buffer->get_u8 ();

	UtilityFunctions::print (amount);

	for (int i = 0; i < amount; i++) {
		// TODO: declare vars outside
		double posx = buffer->get_float ();
		double posy = buffer->get_float ();
		Vector2 pos = Vector2 (posx, posy);
		double rotation = buffer->get_float ();
		double velx = buffer->get_float ();
		double vely = buffer->get_float ();
		Vector2 vel = Vector2 (velx, vely);
		double angvel = buffer->get_float ();

		// print it

		UtilityFunctions::print (pos, rotation, vel, angvel);
	}

	return true;
}
