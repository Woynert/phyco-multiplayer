#ifndef PACKETS
#define PACKETS

#include <godot_cpp/classes/node.hpp>
#include "godot_cpp/variant/packed_byte_array.hpp"
#include "godot_cpp/variant/string.hpp"
#include "godot_cpp/godot.hpp"
#include <godot_cpp/classes/stream_peer_buffer.hpp>
#include <godot_cpp/classes/stream_peer.hpp>
#include <godot_cpp/classes/rigid_body2d.hpp>

using namespace godot;

enum class PACKET_TYPE
{

    // client packets

    JOIN_REQUEST,
    QUIT_REQUEST,
    INPUT,

    // server packets

    JOIN_REQUEST_ACK,
    GAME_STATE,
};

struct Packet
{
    PACKET_TYPE type;

    Packet (){};
    virtual ~Packet(){};
};

PACKET_TYPE get_packet_type(Ref<StreamPeerBuffer> buffer);

// client packets

struct PacketJoinRequest: public Packet
{
    static const PACKET_TYPE type = PACKET_TYPE::JOIN_REQUEST;

    String username;

    static bool Write (Ref<StreamPeerBuffer> buffer, String username);
    bool Read (Ref<StreamPeerBuffer> buffer);
};

struct PacketQuitRequest: public Packet
{
    static const PACKET_TYPE type = PACKET_TYPE::QUIT_REQUEST;

    static bool Write (Ref<StreamPeerBuffer> buffer);
};

struct PacketInput: public Packet
{
    static const PACKET_TYPE type = PACKET_TYPE::INPUT;

    bool w;
    bool a;
    bool s;
    bool d;
    bool action1;
    bool action2;

    static bool Write ( Ref<StreamPeerBuffer> buffer,
        bool w, bool a, bool s, bool d,
        bool action1, bool action2
    );
    bool Read (Ref<StreamPeerBuffer> buffer);
};

// server packets

struct PacketJoinRequestAck: public Packet
{
    static const PACKET_TYPE type = PACKET_TYPE::JOIN_REQUEST_ACK;

    static bool Write (Ref<StreamPeerBuffer> buffer);
};

struct PacketGameState: public Packet
{
    static const PACKET_TYPE type = PACKET_TYPE::GAME_STATE;

    static bool Write (Ref<StreamPeerBuffer> buffer, TypedArray<RigidBody2D> objs);
    bool Read (Ref<StreamPeerBuffer> buffer);
};

#endif
