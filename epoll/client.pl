#!/usr/bin/perl

use strict;
use Socket;
use IO::Handle;

sub echoclient
{
    my $host = "127.0.0.1";
    my $port = 5000;

    my $protocol = getprotobyname("TCP");
    $host = inet_aton($host);

    socket(SOCK, AF_INET, SOCK_STREAM, $protocol) or die "socket() failed: $!";

    my $dest_addr = sockaddr_in($port, $host);
    connect(SOCK, $dest_addr) or die "connect() failed: $!";

    SOCK->autoflush(1);

    my $msg_out = "hello world\n";
    print "out = ", $msg_out;
    print SOCK $msg_out;
    my $msg_in = <SOCK>;
    print "in = ", $msg_in;

    close SOCK;
}

#&echoclient;
#exit(0);

for (my $i = 0; $i < 9999; $i++)
{
    echoclient;
}
