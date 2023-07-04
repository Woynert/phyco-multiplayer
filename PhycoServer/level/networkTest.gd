extends Node2D

var level2: PackedScene = preload("res://level/level2.tscn")

func _ready():
	%btnHost.connect("pressed", host)
	%btnJoin.connect("pressed", join)
	print("level2 The fool")
	print(level2)
	
	
	
func host():
	print(%Server.start())
	%Server.goto_level(level2)
	
func join():
	%Client.address = %txtAddress.text;
	%Client.port    = int(%numPort.value);
	
	print(%Client.start())
	
