set ns [new Simulator]

set ftr [open out.tr w]
$ns trace-all $ftr

set tr [open out.nam w]
$ns namtrace-all $tr

set n0 [$ns node]
set n1 [$ns node]

$ns duplex-link $n0 $n1 1Mb 150ms DropTail

set tcp [new Agent/TCP]
set sink [new Agent/TCPSink]

$ns attach-agent $n0 $tcp
$ns attach-agent $n1 $sink
	
$ns connect $tcp $sink
set ftp [new Application/FTP]
$ftp attach-agent $tcp

proc finish {} {
	global ns ftr tr
	$ns flush-trace
	close $ftr
	close $tr
	exec nam out.nam &
	exec xgraph conges.xg  &
	exit
}
$tcp set window_ 8000
$tcp set packetSize_ 552
  
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
$ns at 100.0 " $ftp  stop"
$ns at 125.0 "finish"
$ns run


