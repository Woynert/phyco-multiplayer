extends RigidBody2D

var walkingForce = 2000
var jumpForce = 500
var repellentForce = 100
var repellentReach = 100
@onready var gravity: float = ProjectSettings.get_setting("physics/2d/default_gravity", 980)

func _ready():
	pass

func _integrate_forces(state):
	
	#apply_force(Vector2(0, gravity))
	var hKey = int(Input.is_action_pressed("ui_right")) - int(Input.is_action_pressed("ui_left"))
	
	if (Input.is_action_just_pressed("ui_up")):
		apply_impulse(Vector2(0, -jumpForce))
		
	"""
	if (Input.is_action_pressed("ui_select")):
		var cubies = get_tree().get_nodes_in_group("cubi")
		for c in cubies:
			if c is RigidBody2D:
				
				var dir = c.global_position - global_position
				var nearness = 1 - min(1, dir.length() / repellentReach)
				
				c.apply_impulse(dir.normalized() * repellentForce * nearness)
	"""
		
	linear_velocity.x = hKey * walkingForce
	#apply_force(Vector2(hKey * walkingForce,0))
	
	pass

func _physics_process(delta):
	
	"""
	var hKey = int(Input.is_action_pressed("ui_right")) - int(Input.is_action_pressed("ui_left"))
	
	if (Input.is_action_just_pressed("ui_up")):
		apply_impulse(Vector2(0, -jumpForce))
		
	if (Input.is_action_pressed("ui_select")):
		var cubies = get_tree().get_nodes_in_group("cubi")
		for c in cubies:
			if c is RigidBody2D:
				
				var dir = c.global_position - global_position
				var nearness = 1 - min(1, dir.length() / repellentReach)
				
				c.apply_impulse(dir.normalized() * repellentForce * nearness)
		

	apply_force(Vector2(hKey * walkingForce,0))"""
	pass
	
