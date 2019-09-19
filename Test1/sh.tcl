#Make a NS simulator 
set ns [new Simulator]

set ftr [open out.tr w]
$ns trace-all $ftr

set tr [open out.nam w]
$ns namtrace-all $tr


#Define different colors for data flows (for NAM)
$ns color 1 Red
$ns color 2 Green
$ns color 3 Yellow


# Create the nodes:
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]


# Create the links:
$ns duplex-link $n0 $n2 1Mb 100ms DropTail
$ns duplex-link $n1 $n2 1Mb 100ms DropTail


# Set Queue Size of link (n0-n2) to 10
$ns queue-limit $n0 $n2 10


# Give node position (for NAM)
$ns duplex-link-op $n0 $n2 orient left-down
$ns duplex-link-op $n1 $n2 orient right-up


###################UDP Connection between 1 and 2 nodes##############################
set udp [new Agent/UDP]
$ns attach-agent $n1 $udp
set null [new Agent/Null]
$ns attach-agent $n2 $null

###################TCP Connection between 0 and 3 nodes###############################
set tcp [new Agent/TCP]
set sink [new Agent/TCPSink]
$ns attach-agent $n0 $tcp
$ns attach-agent $n2 $sink
	
$ns connect $tcp $sink
$ns connect $udp $null

# Setup a FTP over TCP connection
set ftp [new Application/FTP]
$ftp attach-agent $tcp

set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp

# Define a 'finish' procedure
proc finish {} {
	global ns ftr tr
	$ns flush-trace
	close $ftr
	close $tr
	exec nam out.nam &
	exec xgraph conges.xg  &
	exit
}

$tcp set window_ 2000
$tcp set packetSize_ 1024

$cbr set packetSize_ 512
$cbr set interval_ 0.1

# plotWindow
proc plotting { tcp1 file1 } {

global ns
set conges [ $tcp1 set cwnd_]
set now [$ns now]
puts $file1 "$now $conges"
$ns at [expr $now+0.1] "plotting $tcp1 $file1"
}



set file1 [open conges.xg w]
$ns at 0.1 "plotting $tcp $file1"
$ns at 0.1 " $ftp start"
$ns at 0.1 "$cbr start"
$ns at 100.0 " $ftp  stop"
$ns at 100.0 "$cbr stop"
$ns at 125.0 "finish"
$ns run


