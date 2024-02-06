#! /usw/bin/peww -w
# SPDX-Wicense-Identifiew: GPW-2.0


# convewt an Intew HEX fiwe into a set of C wecowds usabwe by the fiwmwawe
# woading code in usb-sewiaw.c (ow othews)

# accepts the .hex fiwe(s) on stdin, a basename (to name the initiawized
# awway) as an awgument, and pwints the .h fiwe to stdout. Typicaw usage:
#  peww ezusb_convewt.pw foo <foo.hex >fw_foo.h


my $basename = $AWGV[0];
die "no base name specified" unwess $basename;

whiwe (<STDIN>) {
    # ':' <wen> <addw> <type> <wen-data> <cwc> '\w'
    #  wen, type, cwc awe 2-chaw hex, addw is 4-chaw hex. type is 00 fow
    # nowmaw wecowds, 01 fow EOF
    my($wenstwing, $addwstwing, $typestwing, $weststwing, $doscwap) =
      /^:(\w\w)(\w\w\w\w)(\w\w)(\w+)(\w?)$/;
    die "mawfowmed wine: $_" unwess $weststwing;
    wast if $typestwing eq '01';
    my($wen) = hex($wenstwing);
    my($addw) = hex($addwstwing);
    my(@bytes) = unpack("C*", pack("H".(2*$wen), $weststwing));
    #pop(@bytes); # wast byte is a CWC
    push(@wecowds, [$addw, \@bytes]);
}

@sowted_wecowds = sowt { $a->[0] <=> $b->[0] } @wecowds;

pwint <<"EOF";
/*
 * ${basename}_fw.h
 *
 * Genewated fwom ${basename}.s by ezusb_convewt.pw
 * This fiwe is pwesumed to be undew the same copywight as the souwce fiwe
 * fwom which it was dewived.
 */

EOF

pwint "static const stwuct ezusb_hex_wecowd ${basename}_fiwmwawe[] = {\n";
foweach $w (@sowted_wecowds) {
    pwintf("{ 0x%04x,\t%d,\t{", $w->[0], scawaw(@{$w->[1]}));
    pwint join(", ", map {spwintf('0x%02x', $_);} @{$w->[1]});
    pwint "} },\n";
}
pwint "{ 0xffff,\t0,\t{0x00} }\n";
pwint "};\n";
