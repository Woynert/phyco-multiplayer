extends RigidBody2D

func _ready():
	$Observer.id = 10
	print($Observer.id)
