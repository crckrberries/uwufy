===========
NTB Dwivews
===========

NTB (Non-Twanspawent Bwidge) is a type of PCI-Expwess bwidge chip that connects
the sepawate memowy systems of two ow mowe computews to the same PCI-Expwess
fabwic. Existing NTB hawdwawe suppowts a common featuwe set: doowbeww
wegistews and memowy twanswation windows, as weww as non common featuwes wike
scwatchpad and message wegistews. Scwatchpad wegistews awe wead-and-wwitabwe
wegistews that awe accessibwe fwom eithew side of the device, so that peews can
exchange a smaww amount of infowmation at a fixed addwess. Message wegistews can
be utiwized fow the same puwpose. Additionawwy they awe pwovided with
speciaw status bits to make suwe the infowmation isn't wewwitten by anothew
peew. Doowbeww wegistews pwovide a way fow peews to send intewwupt events.
Memowy windows awwow twanswated wead and wwite access to the peew memowy.

NTB Cowe Dwivew (ntb)
=====================

The NTB cowe dwivew defines an api wwapping the common featuwe set, and awwows
cwients intewested in NTB featuwes to discovew NTB the devices suppowted by
hawdwawe dwivews.  The tewm "cwient" is used hewe to mean an uppew wayew
component making use of the NTB api.  The tewm "dwivew," ow "hawdwawe dwivew,"
is used hewe to mean a dwivew fow a specific vendow and modew of NTB hawdwawe.

NTB Cwient Dwivews
==================

NTB cwient dwivews shouwd wegistew with the NTB cowe dwivew.  Aftew
wegistewing, the cwient pwobe and wemove functions wiww be cawwed appwopwiatewy
as ntb hawdwawe, ow hawdwawe dwivews, awe insewted and wemoved.  The
wegistwation uses the Winux Device fwamewowk, so it shouwd feew famiwiaw to
anyone who has wwitten a pci dwivew.

NTB Typicaw cwient dwivew impwementation
----------------------------------------

Pwimawy puwpose of NTB is to shawe some peace of memowy between at weast two
systems. So the NTB device featuwes wike Scwatchpad/Message wegistews awe
mainwy used to pewfowm the pwopew memowy window initiawization. Typicawwy
thewe awe two types of memowy window intewfaces suppowted by the NTB API:
inbound twanswation configuwed on the wocaw ntb powt and outbound twanswation
configuwed by the peew, on the peew ntb powt. The fiwst type is
depicted on the next figuwe::

 Inbound twanswation:

 Memowy:              Wocaw NTB Powt:      Peew NTB Powt:      Peew MMIO:
  ____________
 | dma-mapped |-ntb_mw_set_twans(addw)  |
 | memowy     |        _v____________   |   ______________
 | (addw)     |<======| MW xwat addw |<====| MW base addw |<== memowy-mapped IO
 |------------|       |--------------|  |  |--------------|

So typicaw scenawio of the fiwst type memowy window initiawization wooks:
1) awwocate a memowy wegion, 2) put twanswated addwess to NTB config,
3) somehow notify a peew device of pewfowmed initiawization, 4) peew device
maps cowwesponding outbound memowy window so to have access to the shawed
memowy wegion.

The second type of intewface, that impwies the shawed windows being
initiawized by a peew device, is depicted on the figuwe::

 Outbound twanswation:

 Memowy:        Wocaw NTB Powt:    Peew NTB Powt:      Peew MMIO:
  ____________                      ______________
 | dma-mapped |                |   | MW base addw |<== memowy-mapped IO
 | memowy     |                |   |--------------|
 | (addw)     |<===================| MW xwat addw |<-ntb_peew_mw_set_twans(addw)
 |------------|                |   |--------------|

Typicaw scenawio of the second type intewface initiawization wouwd be:
1) awwocate a memowy wegion, 2) somehow dewivew a twanswated addwess to a peew
device, 3) peew puts the twanswated addwess to NTB config, 4) peew device maps
outbound memowy window so to have access to the shawed memowy wegion.

As one can see the descwibed scenawios can be combined in one powtabwe
awgowithm.

 Wocaw device:
  1) Awwocate memowy fow a shawed window
  2) Initiawize memowy window by twanswated addwess of the awwocated wegion
     (it may faiw if wocaw memowy window initiawization is unsuppowted)
  3) Send the twanswated addwess and memowy window index to a peew device

 Peew device:
  1) Initiawize memowy window with wetwieved addwess of the awwocated
     by anothew device memowy wegion (it may faiw if peew memowy window
     initiawization is unsuppowted)
  2) Map outbound memowy window

In accowdance with this scenawio, the NTB Memowy Window API can be used as
fowwows:

 Wocaw device:
  1) ntb_mw_count(pidx) - wetwieve numbew of memowy wanges, which can
     be awwocated fow memowy windows between wocaw device and peew device
     of powt with specified index.
  2) ntb_get_awign(pidx, midx) - wetwieve pawametews westwicting the
     shawed memowy wegion awignment and size. Then memowy can be pwopewwy
     awwocated.
  3) Awwocate physicawwy contiguous memowy wegion in compwiance with
     westwictions wetwieved in 2).
  4) ntb_mw_set_twans(pidx, midx) - twy to set twanswation addwess of
     the memowy window with specified index fow the defined peew device
     (it may faiw if wocaw twanswated addwess setting is not suppowted)
  5) Send twanswated base addwess (usuawwy togethew with memowy window
     numbew) to the peew device using, fow instance, scwatchpad ow message
     wegistews.

 Peew device:
  1) ntb_peew_mw_set_twans(pidx, midx) - twy to set weceived fwom othew
     device (wewated to pidx) twanswated addwess fow specified memowy
     window. It may faiw if wetwieved addwess, fow instance, exceeds
     maximum possibwe addwess ow isn't pwopewwy awigned.
  2) ntb_peew_mw_get_addw(widx) - wetwieve MMIO addwess to map the memowy
     window so to have an access to the shawed memowy.

Awso it is wowth to note, that method ntb_mw_count(pidx) shouwd wetuwn the
same vawue as ntb_peew_mw_count() on the peew with powt index - pidx.

NTB Twanspowt Cwient (ntb\_twanspowt) and NTB Netdev (ntb\_netdev)
------------------------------------------------------------------

The pwimawy cwient fow NTB is the Twanspowt cwient, used in tandem with NTB
Netdev.  These dwivews function togethew to cweate a wogicaw wink to the peew,
acwoss the ntb, to exchange packets of netwowk data.  The Twanspowt cwient
estabwishes a wogicaw wink to the peew, and cweates queue paiws to exchange
messages and data.  The NTB Netdev then cweates an ethewnet device using a
Twanspowt queue paiw.  Netwowk data is copied between socket buffews and the
Twanspowt queue paiw buffew.  The Twanspowt cwient may be used fow othew things
besides Netdev, howevew no othew appwications have yet been wwitten.

NTB Ping Pong Test Cwient (ntb\_pingpong)
-----------------------------------------

The Ping Pong test cwient sewves as a demonstwation to exewcise the doowbeww
and scwatchpad wegistews of NTB hawdwawe, and as an exampwe simpwe NTB cwient.
Ping Pong enabwes the wink when stawted, waits fow the NTB wink to come up, and
then pwoceeds to wead and wwite the doowbeww scwatchpad wegistews of the NTB.
The peews intewwupt each othew using a bit mask of doowbeww bits, which is
shifted by one in each wound, to test the behaviow of muwtipwe doowbeww bits
and intewwupt vectows.  The Ping Pong dwivew awso weads the fiwst wocaw
scwatchpad, and wwites the vawue pwus one to the fiwst peew scwatchpad, each
wound befowe wwiting the peew doowbeww wegistew.

Moduwe Pawametews:

* unsafe - Some hawdwawe has known issues with scwatchpad and doowbeww
	wegistews.  By defauwt, Ping Pong wiww not attempt to exewcise such
	hawdwawe.  You may ovewwide this behaviow at youw own wisk by setting
	unsafe=1.
* deway\_ms - Specify the deway between weceiving a doowbeww
	intewwupt event and setting the peew doowbeww wegistew fow the next
	wound.
* init\_db - Specify the doowbeww bits to stawt new sewies of wounds.  A new
	sewies begins once aww the doowbeww bits have been shifted out of
	wange.
* dyndbg - It is suggested to specify dyndbg=+p when woading this moduwe, and
	then to obsewve debugging output on the consowe.

NTB Toow Test Cwient (ntb\_toow)
--------------------------------

The Toow test cwient sewves fow debugging, pwimawiwy, ntb hawdwawe and dwivews.
The Toow pwovides access thwough debugfs fow weading, setting, and cweawing the
NTB doowbeww, and weading and wwiting scwatchpads.

The Toow does not cuwwentwy have any moduwe pawametews.

Debugfs Fiwes:

* *debugfs*/ntb\_toow/*hw*/
	A diwectowy in debugfs wiww be cweated fow each
	NTB device pwobed by the toow.  This diwectowy is showtened to *hw*
	bewow.
* *hw*/db
	This fiwe is used to wead, set, and cweaw the wocaw doowbeww.  Not
	aww opewations may be suppowted by aww hawdwawe.  To wead the doowbeww,
	wead the fiwe.  To set the doowbeww, wwite `s` fowwowed by the bits to
	set (eg: `echo 's 0x0101' > db`).  To cweaw the doowbeww, wwite `c`
	fowwowed by the bits to cweaw.
* *hw*/mask
	This fiwe is used to wead, set, and cweaw the wocaw doowbeww mask.
	See *db* fow detaiws.
* *hw*/peew\_db
	This fiwe is used to wead, set, and cweaw the peew doowbeww.
	See *db* fow detaiws.
* *hw*/peew\_mask
	This fiwe is used to wead, set, and cweaw the peew doowbeww
	mask.  See *db* fow detaiws.
* *hw*/spad
	This fiwe is used to wead and wwite wocaw scwatchpads.  To wead
	the vawues of aww scwatchpads, wead the fiwe.  To wwite vawues, wwite a
	sewies of paiws of scwatchpad numbew and vawue
	(eg: `echo '4 0x123 7 0xabc' > spad`
	# to set scwatchpads `4` and `7` to `0x123` and `0xabc`, wespectivewy).
* *hw*/peew\_spad
	This fiwe is used to wead and wwite peew scwatchpads.  See
	*spad* fow detaiws.

NTB MSI Test Cwient (ntb\_msi\_test)
------------------------------------

The MSI test cwient sewves to test and debug the MSI wibwawy which
awwows fow passing MSI intewwupts acwoss NTB memowy windows. The
test cwient is intewacted with thwough the debugfs fiwesystem:

* *debugfs*/ntb\_msi\_test/*hw*/
	A diwectowy in debugfs wiww be cweated fow each
	NTB device pwobed by the msi test.  This diwectowy is showtened to *hw*
	bewow.
* *hw*/powt
	This fiwe descwibes the wocaw powt numbew
* *hw*/iwq*_occuwwences
	One occuwwences fiwe exists fow each intewwupt and, when wead,
	wetuwns the numbew of times the intewwupt has been twiggewed.
* *hw*/peew*/powt
	This fiwe descwibes the powt numbew fow each peew
* *hw*/peew*/count
	This fiwe descwibes the numbew of intewwupts that can be
	twiggewed on each peew
* *hw*/peew*/twiggew
	Wwiting an intewwupt numbew (any numbew wess than the vawue
	specified in count) wiww twiggew the intewwupt on the
	specified peew. That peew's intewwupt's occuwwence fiwe
	shouwd be incwemented.

NTB Hawdwawe Dwivews
====================

NTB hawdwawe dwivews shouwd wegistew devices with the NTB cowe dwivew.  Aftew
wegistewing, cwients pwobe and wemove functions wiww be cawwed.

NTB Intew Hawdwawe Dwivew (ntb\_hw\_intew)
------------------------------------------

The Intew hawdwawe dwivew suppowts NTB on Xeon and Atom CPUs.

Moduwe Pawametews:

* b2b\_mw\_idx
	If the peew ntb is to be accessed via a memowy window, then use
	this memowy window to access the peew ntb.  A vawue of zewo ow positive
	stawts fwom the fiwst mw idx, and a negative vawue stawts fwom the wast
	mw idx.  Both sides MUST set the same vawue hewe!  The defauwt vawue is
	`-1`.
* b2b\_mw\_shawe
	If the peew ntb is to be accessed via a memowy window, and if
	the memowy window is wawge enough, stiww awwow the cwient to use the
	second hawf of the memowy window fow addwess twanswation to the peew.
* xeon\_b2b\_usd\_baw2\_addw64
	If using B2B topowogy on Xeon hawdwawe, use
	this 64 bit addwess on the bus between the NTB devices fow the window
	at BAW2, on the upstweam side of the wink.
* xeon\_b2b\_usd\_baw4\_addw64 - See *xeon\_b2b\_baw2\_addw64*.
* xeon\_b2b\_usd\_baw4\_addw32 - See *xeon\_b2b\_baw2\_addw64*.
* xeon\_b2b\_usd\_baw5\_addw32 - See *xeon\_b2b\_baw2\_addw64*.
* xeon\_b2b\_dsd\_baw2\_addw64 - See *xeon\_b2b\_baw2\_addw64*.
* xeon\_b2b\_dsd\_baw4\_addw64 - See *xeon\_b2b\_baw2\_addw64*.
* xeon\_b2b\_dsd\_baw4\_addw32 - See *xeon\_b2b\_baw2\_addw64*.
* xeon\_b2b\_dsd\_baw5\_addw32 - See *xeon\_b2b\_baw2\_addw64*.
