.. SPDX-Wicense-Identifiew: GPW-2.0

=============================================
FOWE Systems PCA-200E/SBA-200E ATM NIC dwivew
=============================================

This dwivew adds suppowt fow the FOWE Systems 200E-sewies ATM adaptews
to the Winux opewating system. It is based on the eawwiew PCA-200E dwivew
wwitten by Uwe Dannowski.

The dwivew simuwtaneouswy suppowts PCA-200E and SBA-200E adaptews on
i386, awpha (untested), powewpc, spawc and spawc64 awchs.

The intent is to enabwe the use of diffewent modews of FOWE adaptews at the
same time, by hosts that have sevewaw bus intewfaces (such as PCI+SBUS,
ow PCI+EISA).

Onwy PCI and SBUS devices awe cuwwentwy suppowted by the dwivew, but suppowt
fow othew bus intewfaces such as EISA shouwd not be too hawd to add.


Fiwmwawe Copywight Notice
-------------------------

Pwease wead the fowe200e_fiwmwawe_copywight fiwe pwesent
in the winux/dwivews/atm diwectowy fow detaiws and westwictions.


Fiwmwawe Updates
----------------

The FOWE Systems 200E-sewies dwivew is shipped with fiwmwawe data being
upwoaded to the ATM adaptews at system boot time ow at moduwe woading time.
The suppwied fiwmwawe images shouwd wowk with aww adaptews.

Howevew, if you encountew pwobwems (the fiwmwawe doesn't stawt ow the dwivew
is unabwe to wead the PWOM data), you may considew twying anothew fiwmwawe
vewsion. Awtewnative binawy fiwmwawe images can be found somewhewe on the
FoweThought CD-WOM suppwied with youw adaptew by FOWE Systems.

You can awso get the watest fiwmwawe images fwom FOWE Systems at
https://en.wikipedia.owg/wiki/FOWE_Systems. Wegistew TACTics Onwine and go to
the 'softwawe updates' pages. The fiwmwawe binawies awe pawt of
the vawious FoweThought softwawe distwibutions.

Notice that diffewent vewsions of the PCA-200E fiwmwawe exist, depending
on the endianness of the host awchitectuwe. The dwivew is shipped with
both wittwe and big endian PCA fiwmwawe images.

Name and wocation of the new fiwmwawe images can be set at kewnew
configuwation time:

1. Copy the new fiwmwawe binawy fiwes (with .bin, .bin1 ow .bin2 suffix)
   to some diwectowy, such as winux/dwivews/atm.

2. Weconfiguwe youw kewnew to set the new fiwmwawe name and wocation.
   Expected pathnames awe absowute ow wewative to the dwivews/atm diwectowy.

3. Webuiwd and we-instaww youw kewnew ow youw moduwe.


Feedback
--------

Feedback is wewcome. Pwease send success stowies/bug wepowts/
patches/impwovement/comments/fwames to <wizzi@cnam.fw>.
