"""Custom topology example

Two directly connected switches plus a host for each switch:

   host --- switch --- switch --- host

Adding the 'topos' dict with a key/value pair to generate our newly defined
topology enables one to pass in '--topo=mytopo' from the command line.
"""

from mininet.topo import Topo

class MyTopo( Topo ):
    "Simple topology example."

    def __init__( self ):
        "Create custom topo."

        # Initialize topology
        Topo.__init__( self )

        # Add hosts and switches
        leftHost1 = self.addHost( 'h1' )
        leftHost2 = self.addHost( 'h2' )
        rightHost1 = self.addHost( 'h3' )
        rightHost2 = self.addHost( 'h4' )
        rootSwitch = self.addSwitch('s1')
        leftSwitch = self.addSwitch('s2')
        rightSwitch = self.addSwitch( 's3' )
        rightmostSwitch = self.addSwitch( 's4' )
        bottomleftSwitch = self.addSwitch('s5')
        bottomrightSwitch = self.addSwitch('s6')

        # Add links
        self.addLink( leftHost1, leftSwitch )
        self.addLink( leftHost2, leftSwitch )
        self.addLink( leftSwitch, rootSwitch )
        self.addLink( rootSwitch, rightSwitch )
        self.addLink( rightSwitch, rightmostSwitch )
        self.addLink( rightSwitch, bottomleftSwitch )
        self.addLink( bottomleftSwitch, bottomrightSwitch )
        self.addLink( bottomrightSwitch, rightmostSwitch )
        self.addLink( bottomleftSwitch, rightHost1 )
        self.addLink( bottomleftSwitch, rightHost2 )



topos = { 'mytopo': ( lambda: MyTopo() ) }
