set x 10

#Procedure 1
proc a {} {
	return "Hello"
}

#Procedure 2
proc add {a b} {
   return [expr $a+$b]
}

puts [a]
puts [add 10 30]	
