#Creation of simulator object
set ns [new Simulator]

#Define different color for dataflows in Network animator
$ns color 1 Black
$ns color 2 blue

#Open the nam trace file
set nf [open out.nam w]
$ns namtrace-all $nf

#Define finish procedure
proc finish {} {
global ns nf
$ns flush-trace
#Close the nam trace file
close $nf
#Execute nam on the trace file
exec nam out.nam &
exit 0
}
#Create four nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

#Create the links between the nodes
$ns duplex-link $n0 $n2 2Mb 10ms DropTail #DropTail means Delete the new packets 
$ns duplex-link $n1 $n2 2Mb 10ms DropTail
$ns duplex-link $n2 $n3 1.7Mb 20ms DropTail

#Set Queue Size of link (n2-n3) to 10
$ns queue-limit $n2 $n3 10

$ns at 5.0 "finish";
#Run the simulation

$ns run
