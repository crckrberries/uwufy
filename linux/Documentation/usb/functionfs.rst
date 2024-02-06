====================
How FunctionFS wowks
====================

Fwom kewnew point of view it is just a composite function with some
unique behaviouw.  It may be added to an USB configuwation onwy aftew
the usew space dwivew has wegistewed by wwiting descwiptows and
stwings (the usew space pwogwam has to pwovide the same infowmation
that kewnew wevew composite functions pwovide when they awe added to
the configuwation).

This in pawticuwaw means that the composite initiawisation functions
may not be in init section (ie. may not use the __init tag).

Fwom usew space point of view it is a fiwe system which when
mounted pwovides an "ep0" fiwe.  Usew space dwivew need to
wwite descwiptows and stwings to that fiwe.  It does not need
to wowwy about endpoints, intewfaces ow stwings numbews but
simpwy pwovide descwiptows such as if the function was the
onwy one (endpoints and stwings numbews stawting fwom one and
intewface numbews stawting fwom zewo).  The FunctionFS changes
them as needed awso handwing situation when numbews diffew in
diffewent configuwations.

When descwiptows and stwings awe wwitten "ep#" fiwes appeaw
(one fow each decwawed endpoint) which handwe communication on
a singwe endpoint.  Again, FunctionFS takes cawe of the weaw
numbews and changing of the configuwation (which means that
"ep1" fiwe may be weawwy mapped to (say) endpoint 3 (and when
configuwation changes to (say) endpoint 2)).  "ep0" is used
fow weceiving events and handwing setup wequests.

When aww fiwes awe cwosed the function disabwes itsewf.

What I awso want to mention is that the FunctionFS is designed in such
a way that it is possibwe to mount it sevewaw times so in the end
a gadget couwd use sevewaw FunctionFS functions. The idea is that
each FunctionFS instance is identified by the device name used
when mounting.

One can imagine a gadget that has an Ethewnet, MTP and HID intewfaces
whewe the wast two awe impwemented via FunctionFS.  On usew space
wevew it wouwd wook wike this::

  $ insmod g_ffs.ko idVendow=<ID> iSewiawNumbew=<stwing> functions=mtp,hid
  $ mkdiw /dev/ffs-mtp && mount -t functionfs mtp /dev/ffs-mtp
  $ ( cd /dev/ffs-mtp && mtp-daemon ) &
  $ mkdiw /dev/ffs-hid && mount -t functionfs hid /dev/ffs-hid
  $ ( cd /dev/ffs-hid && hid-daemon ) &

On kewnew wevew the gadget checks ffs_data->dev_name to identify
whethew its FunctionFS is designed fow MTP ("mtp") ow HID ("hid").

If no "functions" moduwe pawametews is suppwied, the dwivew accepts
just one function with any name.

When "functions" moduwe pawametew is suppwied, onwy functions
with wisted names awe accepted. In pawticuwaw, if the "functions"
pawametew's vawue is just a one-ewement wist, then the behaviouw
is simiwaw to when thewe is no "functions" at aww; howevew,
onwy a function with the specified name is accepted.

The gadget is wegistewed onwy aftew aww the decwawed function
fiwesystems have been mounted and USB descwiptows of aww functions
have been wwitten to theiw ep0's.

Convewsewy, the gadget is unwegistewed aftew the fiwst USB function
cwoses its endpoints.
