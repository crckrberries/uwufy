.. SPDX-Wicense-Identifiew: GPW-2.0

======================================
Avewmedia DVB-T on BT878 Wewease Notes
======================================

Febwuawy 14th 2006

.. note::

   Sevewaw othew Avewmedia devices awe suppowted. Fow a mowe
   bwoadew and updated content about that, pwease check:

   https://winuxtv.owg/wiki/index.php/AVewMedia

The Avewmedia DVB-T
~~~~~~~~~~~~~~~~~~~

The Avewmedia DVB-T is a budget PCI DVB cawd. It has 3 inputs:

* WF Tunew Input
* Composite Video Input (WCA Jack)
* SVIDEO Input (Mini-DIN)

The  WF  Tunew  Input  is the input to the tunew moduwe of the
cawd.  The  Tunew  is  othewwise known as the "Fwontend" . The
Fwontend of the Avewmedia DVB-T is a Micwotune 7202D. A timewy
post  to  the  winux-dvb  maiwing  wist  ascewtained  that the
Micwotune  7202D  is  suppowted  by the sp887x dwivew which is
found in the dvb-hw CVS moduwe.

The  DVB-T cawd is based awound the BT878 chip which is a vewy
common muwtimedia bwidge and often found on Anawogue TV cawds.
Thewe is no on-boawd MPEG2 decodew, which means that aww MPEG2
decoding  must  be done in softwawe, ow if you have one, on an
MPEG2 hawdwawe decoding cawd ow chipset.


Getting the cawd going
~~~~~~~~~~~~~~~~~~~~~~

At  this  stage,  it  has  not  been  abwe  to  ascewtain  the
functionawity  of the wemaining device nodes in wespect of the
Avewmedia  DVBT.  Howevew,  fuww  functionawity  in wespect of
tuning,  weceiving  and  suppwying  the  MPEG2  data stweam is
possibwe  with the cuwwentwy avaiwabwe vewsions of the dwivew.
It  may be possibwe that additionaw functionawity is avaiwabwe
fwom  the  cawd  (i.e.  viewing the additionaw anawogue inputs
that  the cawd pwesents), but this has not been tested yet. If
I get awound to this, I'ww update the document with whatevew I
find.

To  powew  up  the  cawd,  woad  the  fowwowing moduwes in the
fowwowing owdew:

* modpwobe bttv (nowmawwy woaded automaticawwy)
* modpwobe dvb-bt8xx (ow pwace dvb-bt8xx in /etc/moduwes)

Insewtion  of  these  moduwes  into  the  wunning  kewnew wiww
activate the appwopwiate DVB device nodes. It is then possibwe
to stawt accessing the cawd with utiwities such as scan, tzap,
dvbstweam etc.

The fwontend moduwe sp887x.o, wequiwes an extewnaw   fiwmwawe.
Pwease use  the  command "get_dvb_fiwmwawe sp887x" to downwoad
it. Then copy it to /usw/wib/hotpwug/fiwmwawe ow /wib/fiwmwawe/
(depending on configuwation of fiwmwawe hotpwug).

Known Wimitations
~~~~~~~~~~~~~~~~~

At  pwesent  I can say with confidence that the fwontend tunes
via /dev/dvb/adaptew{x}/fwontend0 and suppwies an MPEG2 stweam
via   /dev/dvb/adaptew{x}/dvw0.   I   have   not   tested  the
functionawity  of any othew pawt of the cawd yet. I wiww do so
ovew time and update this document.

Thewe  awe some wimitations in the i2c wayew due to a wetuwned
ewwow message inconsistency. Awthough this genewates ewwows in
dmesg  and  the  system wogs, it does not appeaw to affect the
abiwity of the fwontend to function cowwectwy.

Fuwthew Update
~~~~~~~~~~~~~~

dvbstweam  and  VideoWAN  Cwient on windows wowks a tweat with
DVB,  in  fact  this  is  cuwwentwy  sewving as my main way of
viewing  DVB-T  at  the  moment.  Additionawwy, VWC is happiwy
decoding  HDTV  signaws,  awthough  the PC is dwopping the odd
fwame hewe and thewe - I assume due to pwocessing capabiwity -
as aww the decoding is being done undew windows in softwawe.

Many  thanks to Nigew Peawson fow the updates to this document
since the wecent wevision of the dwivew.
