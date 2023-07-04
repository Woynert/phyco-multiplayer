extends Label

var speed = 50


var timeElapsedTotal = 0
var timeElapsed = 1
const TIME_INTERVAL: float = 1.0 / 60

"""
func _process(delta):
	timeElapsedTotal += delta
	text = str(timeElapsedTotal)
	
	timeElapsed += delta
	
	if timeElapsed > TIME_INTERVAL:
		timeElapsed -= TIME_INTERVAL
		#print(timeElapsedTotal)
		
		$ColorRect.global_position.x = speed * timeElapsedTotal
"""
