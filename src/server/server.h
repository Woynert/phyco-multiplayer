#ifndef SERVER_H
#define SERVER_H

#include "godot_cpp/classes/packed_scene.hpp"
#include "godot_cpp/variant/packed_byte_array.hpp"
#include <godot_cpp/classes/e_net_connection.hpp>
#include <godot_cpp/classes/sprite2d.hpp>

#include "vector"
#include "player_struct.hpp"

namespace godot{

class Server : public Node {
    GDCLASS(Server, Node)

protected:
    static void _bind_methods();

//private:
public:


	Ref<ENetConnection> conn;
	int max_peers = 2;
	int max_channels = 2;
	int bind_port = 4444;
	String bind_address = "0.0.0.0";

	//const double time_interval = 1.0 / 10;
	const double time_interval = 1.0 / 2;
	double time_elapsed = 0;

	// player managment

	std::vector<bool> available_slots;
	std::vector<PlayerStruct*> slots;

	// consume

	void consume_package(PackedByteArray* packet);


    Server();
    ~Server();

    void _process(double delta) override;

	bool start();

	bool stop();

	bool goto_level(PackedScene* scene);

	// get incoming packages
	//void receive_packages();

	// send packages X times per second
	void send_to_all_peers(PackedByteArray packet);

};

}

#endif
