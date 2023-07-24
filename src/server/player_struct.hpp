#ifndef PLAYER_STRUCT_H
#define PLAYER_STRUCT_H

#include "godot_cpp/classes/e_net_connection.hpp"

enum class PlayerState
{
	JOINING,
	JOINED,
};

struct PlayerStruct
{
	int slot;
	PlayerState state;
	godot::Ref<godot::ENetPacketPeer> peer;
};

#endif // !PLAYER_STRUCT_H
