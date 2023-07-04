#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/classes/stream_peer_buffer.hpp"

using namespace godot;

void serialize_inputs (Ref<StreamPeerBuffer> buf);
void serialize_game_state (Ref<StreamPeerBuffer> buf, Node* serverRoot);

#endif
