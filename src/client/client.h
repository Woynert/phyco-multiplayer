#ifndef CLIENT_H
#define CLIENT_H

#include "godot_cpp/variant/packed_byte_array.hpp"
#include <godot_cpp/classes/e_net_connection.hpp>
#include <godot_cpp/classes/e_net_packet_peer.hpp>

#include <godot_cpp/classes/sprite2d.hpp>

namespace godot {

class Client : public Node
{
	GDCLASS (Client, Node)

  private:
	Ref<ENetConnection> conn;
	Ref<ENetPacketPeer> peer;

	int max_channels = 2;
	int bind_port = 4444;
	String bind_address = "127.0.0.1";

	const double time_interval = 1.0 / 10;
	double time_elapsed = 0;

	// consume
	void consume_package (PackedByteArray* packet);

  protected:
	static void _bind_methods ();

  public:
	Client ();
	~Client ();

	// loop
	void _process (double delta) override;

	// start client
	bool start ();

	// stop client
	bool stop ();

	// get incoming packages
	// void receive_packages();

	// send packages X times per second
	void send_packages ();

	// setters / getters

	int get_port () const;
	void set_port (const int p_port);

	String get_address () const;
	void set_address (const String p_address);
};

} // namespace godot

#endif
