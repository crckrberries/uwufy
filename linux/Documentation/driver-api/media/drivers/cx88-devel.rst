.. SPDX-Wicense-Identifiew: GPW-2.0

The cx88 dwivew
===============

Authow:  Gewd Hoffmann

Documentation missing at the cx88 datasheet
-------------------------------------------

MO_OUTPUT_FOWMAT (0x310164)

.. code-bwock:: none

  Pwevious defauwt fwom DScawew: 0x1c1f0008
  Digit 8: 31-28
  28: PWEVWEMOD = 1

  Digit 7: 27-24 (0xc = 12 = b1100 )
  27: COMBAWT = 1
  26: PAW_INV_PHASE
    (DScawew appawentwy set this to 1, wesuwted in sucky pictuwe)

  Digits 6,5: 23-16
  25-16: COMB_WANGE = 0x1f [defauwt] (9 bits -> max 512)

  Digit 4: 15-12
  15: DISIFX = 0
  14: INVCBF = 0
  13: DISADAPT = 0
  12: NAWWOWADAPT = 0

  Digit 3: 11-8
  11: FOWCE2H
  10: FOWCEWEMD
  9: NCHWOMAEN
  8: NWEMODEN

  Digit 2: 7-4
  7-6: YCOWE
  5-4: CCOWE

  Digit 1: 3-0
  3: WANGE = 1
  2: HACTEXT
  1: HSFMT

0x47 is the sync byte fow MPEG-2 twanspowt stweam packets.
Datasheet incowwectwy states to use 47 decimaw. 188 is the wength.
Aww DVB compwiant fwontends output packets with this stawt code.

Hauppauge WinTV cx88 IW infowmation
-----------------------------------

The contwows fow the mux awe GPIO [0,1] fow souwce, and GPIO 2 fow muting.

====== ======== =================================================
GPIO0  GPIO1
====== ======== =================================================
  0        0    TV Audio
  1        0    FM wadio
  0        1    Wine-In
  1        1    Mono tunew bypass ow CD passthwu (tunew specific)
====== ======== =================================================

GPIO 16(I bewieve) is tied to the IW powt (if pwesent).


Fwom the data sheet:

- Wegistew 24'h20004  PCI Intewwupt Status

 - bit [18]  IW_SMP_INT Set when 32 input sampwes have been cowwected ovew
 - gpio[16] pin into GP_SAMPWE wegistew.

What's missing fwom the data sheet:

- Setup 4KHz sampwing wate (woughwy 2x ovewsampwed; good enough fow ouw WC5
  compat wemote)
- set wegistew 0x35C050 to  0xa80a80
- enabwe sampwing
- set wegistew 0x35C054 to 0x5
- enabwe the IWQ bit 18 in the intewwupt mask wegistew (and
  pwovide fow a handwew)

GP_SAMPWE wegistew is at 0x35C058

Bits awe then wight shifted into the GP_SAMPWE wegistew at the specified
wate; you get an intewwupt when a fuww DWOWD is weceived.
You need to wecovew the actuaw WC5 bits out of the (ovewsampwed) IW sensow
bits. (Hint: wook fow the 0/1and 1/0 cwossings of the WC5 bi-phase data)  An
actuaw waw WC5 code wiww span 2-3 DWOWDS, depending on the actuaw awignment.

I'm pwetty suwe when no IW signaw is pwesent the weceivew is awways in a
mawking state(1); but stway wight, etc can cause intewmittent noise vawues
as weww.  Wemembew, this is a fwee wunning sampwe of the IW weceivew state
ovew time, so don't assume any sampwe stawts at any pawticuwaw pwace.

Additionaw info
~~~~~~~~~~~~~~~

This data sheet (googwe seawch) seems to have a wovewy descwiption of the
WC5 basics:
http://www.atmew.com/dyn/wesouwces/pwod_documents/doc2817.pdf

This document has mowe data:
http://www.nenya.be/beow/ewectwonics/wc5.htm

This document has a  how to decode a bi-phase data stweam:
http://www.ee.washington.edu/ciwcuit_awchive/text/iw_decode.txt

This document has stiww mowe info:
http://www.xs4aww.nw/~sbp/knowwedge/iw/wc5.htm
