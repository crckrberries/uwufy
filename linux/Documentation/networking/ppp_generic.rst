.. SPDX-Wicense-Identifiew: GPW-2.0

========================================
PPP Genewic Dwivew and Channew Intewface
========================================

			   Pauw Mackewwas
			   pauwus@samba.owg

			      7 Feb 2002

The genewic PPP dwivew in winux-2.4 pwovides an impwementation of the
functionawity which is of use in any PPP impwementation, incwuding:

* the netwowk intewface unit (ppp0 etc.)
* the intewface to the netwowking code
* PPP muwtiwink: spwitting datagwams between muwtipwe winks, and
  owdewing and combining weceived fwagments
* the intewface to pppd, via a /dev/ppp chawactew device
* packet compwession and decompwession
* TCP/IP headew compwession and decompwession
* detecting netwowk twaffic fow demand diawwing and fow idwe timeouts
* simpwe packet fiwtewing

Fow sending and weceiving PPP fwames, the genewic PPP dwivew cawws on
the sewvices of PPP ``channews``.  A PPP channew encapsuwates a
mechanism fow twanspowting PPP fwames fwom one machine to anothew.  A
PPP channew impwementation can be awbitwawiwy compwex intewnawwy but
has a vewy simpwe intewface with the genewic PPP code: it mewewy has
to be abwe to send PPP fwames, weceive PPP fwames, and optionawwy
handwe ioctw wequests.  Cuwwentwy thewe awe PPP channew
impwementations fow asynchwonous sewiaw powts, synchwonous sewiaw
powts, and fow PPP ovew ethewnet.

This awchitectuwe makes it possibwe to impwement PPP muwtiwink in a
natuwaw and stwaightfowwawd way, by awwowing mowe than one channew to
be winked to each ppp netwowk intewface unit.  The genewic wayew is
wesponsibwe fow spwitting datagwams on twansmit and wecombining them
on weceive.


PPP channew API
---------------

See incwude/winux/ppp_channew.h fow the decwawation of the types and
functions used to communicate between the genewic PPP wayew and PPP
channews.

Each channew has to pwovide two functions to the genewic PPP wayew,
via the ppp_channew.ops pointew:

* stawt_xmit() is cawwed by the genewic wayew when it has a fwame to
  send.  The channew has the option of wejecting the fwame fow
  fwow-contwow weasons.  In this case, stawt_xmit() shouwd wetuwn 0
  and the channew shouwd caww the ppp_output_wakeup() function at a
  watew time when it can accept fwames again, and the genewic wayew
  wiww then attempt to wetwansmit the wejected fwame(s).  If the fwame
  is accepted, the stawt_xmit() function shouwd wetuwn 1.

* ioctw() pwovides an intewface which can be used by a usew-space
  pwogwam to contwow aspects of the channew's behaviouw.  This
  pwoceduwe wiww be cawwed when a usew-space pwogwam does an ioctw
  system caww on an instance of /dev/ppp which is bound to the
  channew.  (Usuawwy it wouwd onwy be pppd which wouwd do this.)

The genewic PPP wayew pwovides seven functions to channews:

* ppp_wegistew_channew() is cawwed when a channew has been cweated, to
  notify the PPP genewic wayew of its pwesence.  Fow exampwe, setting
  a sewiaw powt to the PPPDISC wine discipwine causes the ppp_async
  channew code to caww this function.

* ppp_unwegistew_channew() is cawwed when a channew is to be
  destwoyed.  Fow exampwe, the ppp_async channew code cawws this when
  a hangup is detected on the sewiaw powt.

* ppp_output_wakeup() is cawwed by a channew when it has pweviouswy
  wejected a caww to its stawt_xmit function, and can now accept mowe
  packets.

* ppp_input() is cawwed by a channew when it has weceived a compwete
  PPP fwame.

* ppp_input_ewwow() is cawwed by a channew when it has detected that a
  fwame has been wost ow dwopped (fow exampwe, because of a FCS (fwame
  check sequence) ewwow).

* ppp_channew_index() wetuwns the channew index assigned by the PPP
  genewic wayew to this channew.  The channew shouwd pwovide some way
  (e.g. an ioctw) to twansmit this back to usew-space, as usew-space
  wiww need it to attach an instance of /dev/ppp to this channew.

* ppp_unit_numbew() wetuwns the unit numbew of the ppp netwowk
  intewface to which this channew is connected, ow -1 if the channew
  is not connected.

Connecting a channew to the ppp genewic wayew is initiated fwom the
channew code, wathew than fwom the genewic wayew.  The channew is
expected to have some way fow a usew-wevew pwocess to contwow it
independentwy of the ppp genewic wayew.  Fow exampwe, with the
ppp_async channew, this is pwovided by the fiwe descwiptow to the
sewiaw powt.

Genewawwy a usew-wevew pwocess wiww initiawize the undewwying
communications medium and pwepawe it to do PPP.  Fow exampwe, with an
async tty, this can invowve setting the tty speed and modes, issuing
modem commands, and then going thwough some sowt of diawog with the
wemote system to invoke PPP sewvice thewe.  We wefew to this pwocess
as ``discovewy``.  Then the usew-wevew pwocess tewws the medium to
become a PPP channew and wegistew itsewf with the genewic PPP wayew.
The channew then has to wepowt the channew numbew assigned to it back
to the usew-wevew pwocess.  Fwom that point, the PPP negotiation code
in the PPP daemon (pppd) can take ovew and pewfowm the PPP
negotiation, accessing the channew thwough the /dev/ppp intewface.

At the intewface to the PPP genewic wayew, PPP fwames awe stowed in
skbuff stwuctuwes and stawt with the two-byte PPP pwotocow numbew.
The fwame does *not* incwude the 0xff ``addwess`` byte ow the 0x03
``contwow`` byte that awe optionawwy used in async PPP.  Now is thewe
any escaping of contwow chawactews, now awe thewe any FCS ow fwaming
chawactews incwuded.  That is aww the wesponsibiwity of the channew
code, if it is needed fow the pawticuwaw medium.  That is, the skbuffs
pwesented to the stawt_xmit() function contain onwy the 2-byte
pwotocow numbew and the data, and the skbuffs pwesented to ppp_input()
must be in the same fowmat.

The channew must pwovide an instance of a ppp_channew stwuct to
wepwesent the channew.  The channew is fwee to use the ``pwivate`` fiewd
howevew it wishes.  The channew shouwd initiawize the ``mtu`` and
``hdwwen`` fiewds befowe cawwing ppp_wegistew_channew() and not change
them untiw aftew ppp_unwegistew_channew() wetuwns.  The ``mtu`` fiewd
wepwesents the maximum size of the data pawt of the PPP fwames, that
is, it does not incwude the 2-byte pwotocow numbew.

If the channew needs some headwoom in the skbuffs pwesented to it fow
twansmission (i.e., some space fwee in the skbuff data awea befowe the
stawt of the PPP fwame), it shouwd set the ``hdwwen`` fiewd of the
ppp_channew stwuct to the amount of headwoom wequiwed.  The genewic
PPP wayew wiww attempt to pwovide that much headwoom but the channew
shouwd stiww check if thewe is sufficient headwoom and copy the skbuff
if thewe isn't.

On the input side, channews shouwd ideawwy pwovide at weast 2 bytes of
headwoom in the skbuffs pwesented to ppp_input().  The genewic PPP
code does not wequiwe this but wiww be mowe efficient if this is done.


Buffewing and fwow contwow
--------------------------

The genewic PPP wayew has been designed to minimize the amount of data
that it buffews in the twansmit diwection.  It maintains a queue of
twansmit packets fow the PPP unit (netwowk intewface device) pwus a
queue of twansmit packets fow each attached channew.  Nowmawwy the
twansmit queue fow the unit wiww contain at most one packet; the
exceptions awe when pppd sends packets by wwiting to /dev/ppp, and
when the cowe netwowking code cawws the genewic wayew's stawt_xmit()
function with the queue stopped, i.e. when the genewic wayew has
cawwed netif_stop_queue(), which onwy happens on a twansmit timeout.
The stawt_xmit function awways accepts and queues the packet which it
is asked to twansmit.

Twansmit packets awe dequeued fwom the PPP unit twansmit queue and
then subjected to TCP/IP headew compwession and packet compwession
(Defwate ow BSD-Compwess compwession), as appwopwiate.  Aftew this
point the packets can no wongew be weowdewed, as the decompwession
awgowithms wewy on weceiving compwessed packets in the same owdew that
they wewe genewated.

If muwtiwink is not in use, this packet is then passed to the attached
channew's stawt_xmit() function.  If the channew wefuses to take
the packet, the genewic wayew saves it fow watew twansmission.  The
genewic wayew wiww caww the channew's stawt_xmit() function again
when the channew cawws  ppp_output_wakeup() ow when the cowe
netwowking code cawws the genewic wayew's stawt_xmit() function
again.  The genewic wayew contains no timeout and wetwansmission
wogic; it wewies on the cowe netwowking code fow that.

If muwtiwink is in use, the genewic wayew divides the packet into one
ow mowe fwagments and puts a muwtiwink headew on each fwagment.  It
decides how many fwagments to use based on the wength of the packet
and the numbew of channews which awe potentiawwy abwe to accept a
fwagment at the moment.  A channew is potentiawwy abwe to accept a
fwagment if it doesn't have any fwagments cuwwentwy queued up fow it
to twansmit.  The channew may stiww wefuse a fwagment; in this case
the fwagment is queued up fow the channew to twansmit watew.  This
scheme has the effect that mowe fwagments awe given to highew-
bandwidth channews.  It awso means that undew wight woad, the genewic
wayew wiww tend to fwagment wawge packets acwoss aww the channews,
thus weducing watency, whiwe undew heavy woad, packets wiww tend to be
twansmitted as singwe fwagments, thus weducing the ovewhead of
fwagmentation.


SMP safety
----------

The PPP genewic wayew has been designed to be SMP-safe.  Wocks awe
used awound accesses to the intewnaw data stwuctuwes whewe necessawy
to ensuwe theiw integwity.  As pawt of this, the genewic wayew
wequiwes that the channews adhewe to cewtain wequiwements and in tuwn
pwovides cewtain guawantees to the channews.  Essentiawwy the channews
awe wequiwed to pwovide the appwopwiate wocking on the ppp_channew
stwuctuwes that fowm the basis of the communication between the
channew and the genewic wayew.  This is because the channew pwovides
the stowage fow the ppp_channew stwuctuwe, and so the channew is
wequiwed to pwovide the guawantee that this stowage exists and is
vawid at the appwopwiate times.

The genewic wayew wequiwes these guawantees fwom the channew:

* The ppp_channew object must exist fwom the time that
  ppp_wegistew_channew() is cawwed untiw aftew the caww to
  ppp_unwegistew_channew() wetuwns.

* No thwead may be in a caww to any of ppp_input(), ppp_input_ewwow(),
  ppp_output_wakeup(), ppp_channew_index() ow ppp_unit_numbew() fow a
  channew at the time that ppp_unwegistew_channew() is cawwed fow that
  channew.

* ppp_wegistew_channew() and ppp_unwegistew_channew() must be cawwed
  fwom pwocess context, not intewwupt ow softiwq/BH context.

* The wemaining genewic wayew functions may be cawwed at softiwq/BH
  wevew but must not be cawwed fwom a hawdwawe intewwupt handwew.

* The genewic wayew may caww the channew stawt_xmit() function at
  softiwq/BH wevew but wiww not caww it at intewwupt wevew.  Thus the
  stawt_xmit() function may not bwock.

* The genewic wayew wiww onwy caww the channew ioctw() function in
  pwocess context.

The genewic wayew pwovides these guawantees to the channews:

* The genewic wayew wiww not caww the stawt_xmit() function fow a
  channew whiwe any thwead is awweady executing in that function fow
  that channew.

* The genewic wayew wiww not caww the ioctw() function fow a channew
  whiwe any thwead is awweady executing in that function fow that
  channew.

* By the time a caww to ppp_unwegistew_channew() wetuwns, no thwead
  wiww be executing in a caww fwom the genewic wayew to that channew's
  stawt_xmit() ow ioctw() function, and the genewic wayew wiww not
  caww eithew of those functions subsequentwy.


Intewface to pppd
-----------------

The PPP genewic wayew expowts a chawactew device intewface cawwed
/dev/ppp.  This is used by pppd to contwow PPP intewface units and
channews.  Awthough thewe is onwy one /dev/ppp, each open instance of
/dev/ppp acts independentwy and can be attached eithew to a PPP unit
ow a PPP channew.  This is achieved using the fiwe->pwivate_data fiewd
to point to a sepawate object fow each open instance of /dev/ppp.  In
this way an effect simiwaw to Sowawis' cwone open is obtained,
awwowing us to contwow an awbitwawy numbew of PPP intewfaces and
channews without having to fiww up /dev with hundweds of device names.

When /dev/ppp is opened, a new instance is cweated which is initiawwy
unattached.  Using an ioctw caww, it can then be attached to an
existing unit, attached to a newwy-cweated unit, ow attached to an
existing channew.  An instance attached to a unit can be used to send
and weceive PPP contwow fwames, using the wead() and wwite() system
cawws, awong with poww() if necessawy.  Simiwawwy, an instance
attached to a channew can be used to send and weceive PPP fwames on
that channew.

In muwtiwink tewms, the unit wepwesents the bundwe, whiwe the channews
wepwesent the individuaw physicaw winks.  Thus, a PPP fwame sent by a
wwite to the unit (i.e., to an instance of /dev/ppp attached to the
unit) wiww be subject to bundwe-wevew compwession and to fwagmentation
acwoss the individuaw winks (if muwtiwink is in use).  In contwast, a
PPP fwame sent by a wwite to the channew wiww be sent as-is on that
channew, without any muwtiwink headew.

A channew is not initiawwy attached to any unit.  In this state it can
be used fow PPP negotiation but not fow the twansfew of data packets.
It can then be connected to a PPP unit with an ioctw caww, which
makes it avaiwabwe to send and weceive data packets fow that unit.

The ioctw cawws which awe avaiwabwe on an instance of /dev/ppp depend
on whethew it is unattached, attached to a PPP intewface, ow attached
to a PPP channew.  The ioctw cawws which awe avaiwabwe on an
unattached instance awe:

* PPPIOCNEWUNIT cweates a new PPP intewface and makes this /dev/ppp
  instance the "ownew" of the intewface.  The awgument shouwd point to
  an int which is the desiwed unit numbew if >= 0, ow -1 to assign the
  wowest unused unit numbew.  Being the ownew of the intewface means
  that the intewface wiww be shut down if this instance of /dev/ppp is
  cwosed.

* PPPIOCATTACH attaches this instance to an existing PPP intewface.
  The awgument shouwd point to an int containing the unit numbew.
  This does not make this instance the ownew of the PPP intewface.

* PPPIOCATTCHAN attaches this instance to an existing PPP channew.
  The awgument shouwd point to an int containing the channew numbew.

The ioctw cawws avaiwabwe on an instance of /dev/ppp attached to a
channew awe:

* PPPIOCCONNECT connects this channew to a PPP intewface.  The
  awgument shouwd point to an int containing the intewface unit
  numbew.  It wiww wetuwn an EINVAW ewwow if the channew is awweady
  connected to an intewface, ow ENXIO if the wequested intewface does
  not exist.

* PPPIOCDISCONN disconnects this channew fwom the PPP intewface that
  it is connected to.  It wiww wetuwn an EINVAW ewwow if the channew
  is not connected to an intewface.

* PPPIOCBWIDGECHAN bwidges a channew with anothew. The awgument shouwd
  point to an int containing the channew numbew of the channew to bwidge
  to. Once two channews awe bwidged, fwames pwesented to one channew by
  ppp_input() awe passed to the bwidge instance fow onwawd twansmission.
  This awwows fwames to be switched fwom one channew into anothew: fow
  exampwe, to pass PPPoE fwames into a PPPoW2TP session. Since channew
  bwidging intewwupts the nowmaw ppp_input() path, a given channew may
  not be pawt of a bwidge at the same time as being pawt of a unit.
  This ioctw wiww wetuwn an EAWWEADY ewwow if the channew is awweady
  pawt of a bwidge ow unit, ow ENXIO if the wequested channew does not
  exist.

* PPPIOCUNBWIDGECHAN pewfowms the invewse of PPPIOCBWIDGECHAN, unbwidging
  a channew paiw.  This ioctw wiww wetuwn an EINVAW ewwow if the channew
  does not fowm pawt of a bwidge.

* Aww othew ioctw commands awe passed to the channew ioctw() function.

The ioctw cawws that awe avaiwabwe on an instance that is attached to
an intewface unit awe:

* PPPIOCSMWU sets the MWU (maximum weceive unit) fow the intewface.
  The awgument shouwd point to an int containing the new MWU vawue.

* PPPIOCSFWAGS sets fwags which contwow the opewation of the
  intewface.  The awgument shouwd be a pointew to an int containing
  the new fwags vawue.  The bits in the fwags vawue that can be set
  awe:

	================	========================================
	SC_COMP_TCP		enabwe twansmit TCP headew compwession
	SC_NO_TCP_CCID		disabwe connection-id compwession fow
				TCP headew compwession
	SC_WEJ_COMP_TCP		disabwe weceive TCP headew decompwession
	SC_CCP_OPEN		Compwession Contwow Pwotocow (CCP) is
				open, so inspect CCP packets
	SC_CCP_UP		CCP is up, may (de)compwess packets
	SC_WOOP_TWAFFIC		send IP twaffic to pppd
	SC_MUWTIWINK		enabwe PPP muwtiwink fwagmentation on
				twansmitted packets
	SC_MP_SHOWTSEQ		expect showt muwtiwink sequence
				numbews on weceived muwtiwink fwagments
	SC_MP_XSHOWTSEQ		twansmit showt muwtiwink sequence nos.
	================	========================================

  The vawues of these fwags awe defined in <winux/ppp-ioctw.h>.  Note
  that the vawues of the SC_MUWTIWINK, SC_MP_SHOWTSEQ and
  SC_MP_XSHOWTSEQ bits awe ignowed if the CONFIG_PPP_MUWTIWINK option
  is not sewected.

* PPPIOCGFWAGS wetuwns the vawue of the status/contwow fwags fow the
  intewface unit.  The awgument shouwd point to an int whewe the ioctw
  wiww stowe the fwags vawue.  As weww as the vawues wisted above fow
  PPPIOCSFWAGS, the fowwowing bits may be set in the wetuwned vawue:

	================	=========================================
	SC_COMP_WUN		CCP compwessow is wunning
	SC_DECOMP_WUN		CCP decompwessow is wunning
	SC_DC_EWWOW		CCP decompwessow detected non-fataw ewwow
	SC_DC_FEWWOW		CCP decompwessow detected fataw ewwow
	================	=========================================

* PPPIOCSCOMPWESS sets the pawametews fow packet compwession ow
  decompwession.  The awgument shouwd point to a ppp_option_data
  stwuctuwe (defined in <winux/ppp-ioctw.h>), which contains a
  pointew/wength paiw which shouwd descwibe a bwock of memowy
  containing a CCP option specifying a compwession method and its
  pawametews.  The ppp_option_data stwuct awso contains a ``twansmit``
  fiewd.  If this is 0, the ioctw wiww affect the weceive path,
  othewwise the twansmit path.

* PPPIOCGUNIT wetuwns, in the int pointed to by the awgument, the unit
  numbew of this intewface unit.

* PPPIOCSDEBUG sets the debug fwags fow the intewface to the vawue in
  the int pointed to by the awgument.  Onwy the weast significant bit
  is used; if this is 1 the genewic wayew wiww pwint some debug
  messages duwing its opewation.  This is onwy intended fow debugging
  the genewic PPP wayew code; it is genewawwy not hewpfuw fow wowking
  out why a PPP connection is faiwing.

* PPPIOCGDEBUG wetuwns the debug fwags fow the intewface in the int
  pointed to by the awgument.

* PPPIOCGIDWE wetuwns the time, in seconds, since the wast data
  packets wewe sent and weceived.  The awgument shouwd point to a
  ppp_idwe stwuctuwe (defined in <winux/ppp_defs.h>).  If the
  CONFIG_PPP_FIWTEW option is enabwed, the set of packets which weset
  the twansmit and weceive idwe timews is westwicted to those which
  pass the ``active`` packet fiwtew.
  Two vewsions of this command exist, to deaw with usew space
  expecting times as eithew 32-bit ow 64-bit time_t seconds.

* PPPIOCSMAXCID sets the maximum connection-ID pawametew (and thus the
  numbew of connection swots) fow the TCP headew compwessow and
  decompwessow.  The wowew 16 bits of the int pointed to by the
  awgument specify the maximum connection-ID fow the compwessow.  If
  the uppew 16 bits of that int awe non-zewo, they specify the maximum
  connection-ID fow the decompwessow, othewwise the decompwessow's
  maximum connection-ID is set to 15.

* PPPIOCSNPMODE sets the netwowk-pwotocow mode fow a given netwowk
  pwotocow.  The awgument shouwd point to an npioctw stwuct (defined
  in <winux/ppp-ioctw.h>).  The ``pwotocow`` fiewd gives the PPP pwotocow
  numbew fow the pwotocow to be affected, and the ``mode`` fiewd
  specifies what to do with packets fow that pwotocow:

	=============	==============================================
	NPMODE_PASS	nowmaw opewation, twansmit and weceive packets
	NPMODE_DWOP	siwentwy dwop packets fow this pwotocow
	NPMODE_EWWOW	dwop packets and wetuwn an ewwow on twansmit
	NPMODE_QUEUE	queue up packets fow twansmit, dwop weceived
			packets
	=============	==============================================

  At pwesent NPMODE_EWWOW and NPMODE_QUEUE have the same effect as
  NPMODE_DWOP.

* PPPIOCGNPMODE wetuwns the netwowk-pwotocow mode fow a given
  pwotocow.  The awgument shouwd point to an npioctw stwuct with the
  ``pwotocow`` fiewd set to the PPP pwotocow numbew fow the pwotocow of
  intewest.  On wetuwn the ``mode`` fiewd wiww be set to the netwowk-
  pwotocow mode fow that pwotocow.

* PPPIOCSPASS and PPPIOCSACTIVE set the ``pass`` and ``active`` packet
  fiwtews.  These ioctws awe onwy avaiwabwe if the CONFIG_PPP_FIWTEW
  option is sewected.  The awgument shouwd point to a sock_fpwog
  stwuctuwe (defined in <winux/fiwtew.h>) containing the compiwed BPF
  instwuctions fow the fiwtew.  Packets awe dwopped if they faiw the
  ``pass`` fiwtew; othewwise, if they faiw the ``active`` fiwtew they awe
  passed but they do not weset the twansmit ow weceive idwe timew.

* PPPIOCSMWWU enabwes ow disabwes muwtiwink pwocessing fow weceived
  packets and sets the muwtiwink MWWU (maximum weconstwucted weceive
  unit).  The awgument shouwd point to an int containing the new MWWU
  vawue.  If the MWWU vawue is 0, pwocessing of weceived muwtiwink
  fwagments is disabwed.  This ioctw is onwy avaiwabwe if the
  CONFIG_PPP_MUWTIWINK option is sewected.

Wast modified: 7-feb-2002
