#include "gdextension_interface.h"
#include "godot_cpp/classes/e_net_connection.hpp"
#include "godot_cpp/classes/e_net_packet_peer.hpp"
#include "godot_cpp/variant/utility_functions.hpp"
#include "player_struct.hpp"
#include "server.h"
#include <cstdlib>

int get_available_slot (godot::Server* server)
{
    for (int i = 0; i < server->max_peers; i++)
    {
        if (server->available_slots[i])
            return i;
    }

    return -1;
}

bool add_player_to_slot (
    godot::Server* server,
    int slot,
    godot::Ref<godot::ENetPacketPeer> peer
    )
{
    server->available_slots[slot] = false;

    // create player struct

    PlayerStruct* player = new PlayerStruct();
    player->peer = peer;
    player->slot = slot;
    player->state = PlayerState::JOINING;

    server->slots[slot] = player;

    return true;
}

int get_slot_from_peer (
    godot::Server* server,
    godot::Ref<godot::ENetPacketPeer> peer
    )
{

    for (int i = 0; i < server->max_peers; i++)
    {
        if (!server->available_slots[i])
        {
            PlayerStruct* player = server->slots[i];

            if (player->peer == peer)
                return i;
        }
    }

    return -1;
};

bool free_slot (
    godot::Server* server,
    godot::Ref<godot::ENetPacketPeer> peer
    )
{

    int slot = get_slot_from_peer(server, peer);
    if (slot == -1)
        return false;

    server->available_slots[slot] = true;

    PlayerStruct* player = server->slots[slot];

    // TODO: How to properly free a godot Object?
    //std::free(*player->peer)
    GDExtensionClassFreeInstance(*player->peer);
    std::free(player);

    server->slots[slot] = nullptr;
    return true;
};

void show_slots_info (godot::Server* server) 
{
    for (int i = 0; i < server->max_peers; i++)
    {
        if (!server->available_slots[i])
        {
            PlayerStruct* player = server->slots[i];
            godot::UtilityFunctions::print(i, " ", player->peer);
        }
    }
}

