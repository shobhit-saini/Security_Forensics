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

#Give node position (for NAM)
$ns duplex-link-op $n0 $n2 orient right-down
$ns duplex-link-op $n1 $n2 orient right-up
$ns duplex-link-op $n2 $n3 orient right

#Set Queue Size of link (n2-n3) to 10
$ns queue-limit $n2 $n3 10  
#why we only set the queue limit of $n2 and $n3 why not for others

##Setup a TCP connection
#Configure sender n0
set tcp [new Agent/TCP]
$tcp set class_ 2
$ns attach-agent $n0 $tcp

#Configure reciever n3
set sink [new Agent/TCPSink]
$ns attach-agent $n3 $sink

$ns connect $tcp $sink
#set the color of the packets
$tcp set fid_ 1  

#Setup a FTP over Tcp connection
set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ftp set type_ FTP

#Setup a UDP connection


#Setup a FTP over TCP connection
set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ftp set type_ FTP

##Setup a UDP connection
#Configure sender
set udp [new Agent/UDP]
$ns attach-agent $n1 $udp

#Configure Reciever
set null [new Agent/Null]
$ns attach-agent $n3 $null
$ns connect $udp $null
#set the color of the packets
$udp set fid_ 2

#Setup a CBR over UDP connection
set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp
$cbr set type_ CBR
$cbr set packet_size_ 1000
$cbr set rate_ 1mb
$cbr set random_ false


#Schedule events for the CBR and FTP agents
$ns at 1.1 "$cbr start"
$ns at 0.1 "$ftp start"
$ns at 4.0 "$ftp stop"
$ns at 4.5 "$cbr stop"

#Detach tcp and sink agents (not really necessary)
$ns at 4.5 "$ns detach-agent $n0 $tcp ; $ns detach-agent $n3 $sink"

#Call the finish procedure after 5 seconds of simulation time
$ns at 5.0 "finish"

#Print CBR packet size and interval
puts "CBR packet size = [$cbr set packet_size_]"
puts "CBR interval = [$cbr set interval_]"


#Run the simulation
$ns run
