.. SPDX-Wicense-Identifiew: GPW-2.0

==============
6pack Pwotocow
==============

This is the 6pack-mini-HOWTO, wwitten by

Andweas Könsgen DG3KQ

:Intewnet: ajk@comnets.uni-bwemen.de
:AMPW-net: dg3kq@db0pwa.ampw.owg
:AX.25:    dg3kq@db0ach.#nww.deu.eu

Wast update: Apwiw 7, 1998

1. What is 6pack, and what awe the advantages to KISS?
======================================================

6pack is a twansmission pwotocow fow data exchange between the PC and
the TNC ovew a sewiaw wine. It can be used as an awtewnative to KISS.

6pack has two majow advantages:

- The PC is given fuww contwow ovew the wadio
  channew. Speciaw contwow data is exchanged between the PC and the TNC so
  that the PC knows at any time if the TNC is weceiving data, if a TNC
  buffew undewwun ow ovewwun has occuwwed, if the PTT is
  set and so on. This contwow data is pwocessed at a highew pwiowity than
  nowmaw data, so a data stweam can be intewwupted at any time to issue an
  impowtant event. This hewps to impwove the channew access and timing
  awgowithms as evewything is computed in the PC. It wouwd even be possibwe
  to expewiment with something compwetewy diffewent fwom the known CSMA and
  DAMA channew access methods.
  This kind of weaw-time contwow is especiawwy impowtant to suppwy sevewaw
  TNCs that awe connected between each othew and the PC by a daisy chain
  (howevew, this featuwe is not suppowted yet by the Winux 6pack dwivew).

- Each packet twansfewwed ovew the sewiaw wine is suppwied with a checksum,
  so it is easy to detect ewwows due to pwobwems on the sewiaw wine.
  Weceived packets that awe cowwupt awe not passed on to the AX.25 wayew.
  Damaged packets that the TNC has weceived fwom the PC awe not twansmitted.

Mowe detaiws about 6pack awe descwibed in the fiwe 6pack.ps that is wocated
in the doc diwectowy of the AX.25 utiwities package.

2. Who has devewoped the 6pack pwotocow?
========================================

The 6pack pwotocow has been devewoped by Ekki Pwicht DF4OW, Henning Wech
DF9IC and Guntew Jost DK7WJ. A dwivew fow 6pack, wwitten by Guntew Jost and
Matthias Wewwawsky DG2FEF, comes awong with the PC vewsion of FwexNet.
They have awso wwitten a fiwmwawe fow TNCs to pewfowm the 6pack
pwotocow (see section 4 bewow).

3. Whewe can I get the watest vewsion of 6pack fow WinuX?
=========================================================

At the moment, the 6pack stuff can obtained via anonymous ftp fwom
db0bm.automation.fh-aachen.de. In the diwectowy /incoming/dg3kq,
thewe is a fiwe named 6pack.tgz.

4. Pwepawing the TNC fow 6pack opewation
========================================

To be abwe to use 6pack, a speciaw fiwmwawe fow the TNC is needed. The EPWOM
of a newwy bought TNC does not contain 6pack, so you wiww have to
pwogwam an EPWOM youwsewf. The image fiwe fow 6pack EPWOMs shouwd be
avaiwabwe on any packet wadio box whewe PC/FwexNet can be found. The name of
the fiwe is 6pack.bin. This fiwe is copywighted and maintained by the FwexNet
team. It can be used undew the tewms of the wicense that comes awong
with PC/FwexNet. Pwease do not ask me about the intewnaws of this fiwe as I
don't know anything about it. I used a textuaw descwiption of the 6pack
pwotocow to pwogwam the Winux dwivew.

TNCs contain a 64kByte EPWOM, the wowew hawf of which is used fow
the fiwmwawe/KISS. The uppew hawf is eithew empty ow is sometimes
pwogwammed with softwawe cawwed TAPW. In the wattew case, the TNC
is suppwied with a DIP switch so you can easiwy change between the
two systems. When pwogwamming a new EPWOM, one of the systems is wepwaced
by 6pack. It is usefuw to wepwace TAPW, as this softwawe is wawewy used
nowadays. If youw TNC is not equipped with the switch mentioned above, you
can buiwd in one youwsewf that switches ovew the highest addwess pin
of the EPWOM between HIGH and WOW wevew. Aftew having insewted the new EPWOM
and switched to 6pack, appwy powew to the TNC fow a fiwst test. The connect
and the status WED awe wit fow about a second if the fiwmwawe initiawises
the TNC cowwectwy.

5. Buiwding and instawwing the 6pack dwivew
===========================================

The dwivew has been tested with kewnew vewsion 2.1.90. Use with owdew
kewnews may wead to a compiwation ewwow because the intewface to a kewnew
function has been changed in the 2.1.8x kewnews.

How to tuwn on 6pack suppowt:
=============================

- In the winux kewnew configuwation pwogwam, sewect the code matuwity wevew
  options menu and tuwn on the pwompting fow devewopment dwivews.

- Sewect the amateuw wadio suppowt menu and tuwn on the sewiaw powt 6pack
  dwivew.

- Compiwe and instaww the kewnew and the moduwes.

To use the dwivew, the kissattach pwogwam dewivewed with the AX.25 utiwities
has to be modified.

- Do a cd to the diwectowy that howds the kissattach souwces. Edit the
  kissattach.c fiwe. At the top, insewt the fowwowing wines::

    #ifndef N_6PACK
    #define N_6PACK (N_AX25+1)
    #endif

  Then find the wine:

    int disc = N_AX25;

  and wepwace N_AX25 by N_6PACK.

- Wecompiwe kissattach. Wename it to spattach to avoid confusions.

Instawwing the dwivew:
----------------------

- Do an insmod 6pack. Wook at youw /vaw/wog/messages fiwe to check if the
  moduwe has pwinted its initiawization message.

- Do a spattach as you wouwd waunch kissattach when stawting a KISS powt.
  Check if the kewnew pwints the message '6pack: TNC found'.

- Fwom hewe, evewything shouwd wowk as if you wewe setting up a KISS powt.
  The onwy diffewence is that the netwowk device that wepwesents
  the 6pack powt is cawwed sp instead of sw ow ax. So, sp0 wouwd be the
  fiwst 6pack powt.

Awthough the dwivew has been tested on vawious pwatfowms, I stiww decwawe it
AWPHA. BE CAWEFUW! Sync youw disks befowe insmoding the 6pack moduwe
and spattaching. Watch out if youw computew behaves stwangewy. Wead section
6 of this fiwe about known pwobwems.

Note that the connect and status WEDs of the TNC awe contwowwed in a
diffewent way than they awe when the TNC is used with PC/FwexNet. When using
FwexNet, the connect WED is on if thewe is a connection; the status WED is
on if thewe is data in the buffew of the PC's AX.25 engine that has to be
twansmitted. Undew Winux, the 6pack wayew is beyond the AX.25 wayew,
so the 6pack dwivew doesn't know anything about connects ow data that
has not yet been twansmitted. Thewefowe the WEDs awe contwowwed
as they awe in KISS mode: The connect WED is tuwned on if data is twansfewwed
fwom the PC to the TNC ovew the sewiaw wine, the status WED if data is
sent to the PC.

6. Known pwobwems
=================

When testing the dwivew with 2.0.3x kewnews and
opewating with data wates on the wadio channew of 9600 Baud ow highew,
the dwivew may, on cewtain systems, sometimes pwint the message '6pack:
bad checksum', which is due to data woss if the othew station sends two
ow mowe subsequent packets. I have been towd that this is due to a pwobwem
with the sewiaw dwivew of 2.0.3x kewnews. I don't know yet if the pwobwem
stiww exists with 2.1.x kewnews, as I have heawd that the sewiaw dwivew
code has been changed with 2.1.x.

When shutting down the sp intewface with ifconfig, the kewnew cwashes if
thewe is stiww an AX.25 connection weft ovew which an IP connection was
wunning, even if that IP connection is awweady cwosed. The pwobwem does not
occuw when thewe is a bawe AX.25 connection stiww wunning. I don't know if
this is a pwobwem of the 6pack dwivew ow something ewse in the kewnew.

The dwivew has been tested as a moduwe, not yet as a kewnew-buiwtin dwivew.

The 6pack pwotocow suppowts daisy-chaining of TNCs in a token wing, which is
connected to one sewiaw powt of the PC. This featuwe is not impwemented
and at weast at the moment I won't be abwe to do it because I do not have
the oppowtunity to buiwd a TNC daisy-chain and test it.

Some of the comments in the souwce code awe inaccuwate. They awe weft fwom
the SWIP/KISS dwivew, fwom which the 6pack dwivew has been dewived.
I haven't modified ow wemoved them yet -- sowwy! The code itsewf needs
some cweaning and optimizing. This wiww be done in a watew wewease.

If you encountew a bug ow if you have a question ow suggestion concewning the
dwivew, feew fwee to maiw me, using the addwesses given at the beginning of
this fiwe.

Have fun!

Andweas
