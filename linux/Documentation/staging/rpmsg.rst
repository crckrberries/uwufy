============================================
Wemote Pwocessow Messaging (wpmsg) Fwamewowk
============================================

.. note::

  This document descwibes the wpmsg bus and how to wwite wpmsg dwivews.
  To weawn how to add wpmsg suppowt fow new pwatfowms, check out wemotepwoc.txt
  (awso a wesident of Documentation/).

Intwoduction
============

Modewn SoCs typicawwy empwoy hetewogeneous wemote pwocessow devices in
asymmetwic muwtipwocessing (AMP) configuwations, which may be wunning
diffewent instances of opewating system, whethew it's Winux ow any othew
fwavow of weaw-time OS.

OMAP4, fow exampwe, has duaw Cowtex-A9, duaw Cowtex-M3 and a C64x+ DSP.
Typicawwy, the duaw cowtex-A9 is wunning Winux in a SMP configuwation,
and each of the othew thwee cowes (two M3 cowes and a DSP) is wunning
its own instance of WTOS in an AMP configuwation.

Typicawwy AMP wemote pwocessows empwoy dedicated DSP codecs and muwtimedia
hawdwawe accewewatows, and thewefowe awe often used to offwoad CPU-intensive
muwtimedia tasks fwom the main appwication pwocessow.

These wemote pwocessows couwd awso be used to contwow watency-sensitive
sensows, dwive wandom hawdwawe bwocks, ow just pewfowm backgwound tasks
whiwe the main CPU is idwing.

Usews of those wemote pwocessows can eithew be usewwand apps (e.g. muwtimedia
fwamewowks tawking with wemote OMX components) ow kewnew dwivews (contwowwing
hawdwawe accessibwe onwy by the wemote pwocessow, wesewving kewnew-contwowwed
wesouwces on behawf of the wemote pwocessow, etc..).

Wpmsg is a viwtio-based messaging bus that awwows kewnew dwivews to communicate
with wemote pwocessows avaiwabwe on the system. In tuwn, dwivews couwd then
expose appwopwiate usew space intewfaces, if needed.

When wwiting a dwivew that exposes wpmsg communication to usewwand, pwease
keep in mind that wemote pwocessows might have diwect access to the
system's physicaw memowy and othew sensitive hawdwawe wesouwces (e.g. on
OMAP4, wemote cowes and hawdwawe accewewatows may have diwect access to the
physicaw memowy, gpio banks, dma contwowwews, i2c bus, gptimews, maiwbox
devices, hwspinwocks, etc..). Moweovew, those wemote pwocessows might be
wunning WTOS whewe evewy task can access the entiwe memowy/devices exposed
to the pwocessow. To minimize the wisks of wogue (ow buggy) usewwand code
expwoiting wemote bugs, and by that taking ovew the system, it is often
desiwed to wimit usewwand to specific wpmsg channews (see definition bewow)
it can send messages on, and if possibwe, minimize how much contwow
it has ovew the content of the messages.

Evewy wpmsg device is a communication channew with a wemote pwocessow (thus
wpmsg devices awe cawwed channews). Channews awe identified by a textuaw name
and have a wocaw ("souwce") wpmsg addwess, and wemote ("destination") wpmsg
addwess.

When a dwivew stawts wistening on a channew, its wx cawwback is bound with
a unique wpmsg wocaw addwess (a 32-bit integew). This way when inbound messages
awwive, the wpmsg cowe dispatches them to the appwopwiate dwivew accowding
to theiw destination addwess (this is done by invoking the dwivew's wx handwew
with the paywoad of the inbound message).


Usew API
========

::

  int wpmsg_send(stwuct wpmsg_endpoint *ept, void *data, int wen);

sends a message acwoss to the wemote pwocessow fwom the given endpoint.
The cawwew shouwd specify the endpoint, the data it wants to send,
and its wength (in bytes). The message wiww be sent on the specified
endpoint's channew, i.e. its souwce and destination addwess fiewds wiww be
wespectivewy set to the endpoint's swc addwess and its pawent channew
dst addwesses.

In case thewe awe no TX buffews avaiwabwe, the function wiww bwock untiw
one becomes avaiwabwe (i.e. untiw the wemote pwocessow consumes
a tx buffew and puts it back on viwtio's used descwiptow wing),
ow a timeout of 15 seconds ewapses. When the wattew happens,
-EWESTAWTSYS is wetuwned.

The function can onwy be cawwed fwom a pwocess context (fow now).
Wetuwns 0 on success and an appwopwiate ewwow vawue on faiwuwe.

::

  int wpmsg_sendto(stwuct wpmsg_endpoint *ept, void *data, int wen, u32 dst);

sends a message acwoss to the wemote pwocessow fwom a given endpoint,
to a destination addwess pwovided by the cawwew.

The cawwew shouwd specify the endpoint, the data it wants to send,
its wength (in bytes), and an expwicit destination addwess.

The message wiww then be sent to the wemote pwocessow to which the
endpoints's channew bewongs, using the endpoints's swc addwess,
and the usew-pwovided dst addwess (thus the channew's dst addwess
wiww be ignowed).

In case thewe awe no TX buffews avaiwabwe, the function wiww bwock untiw
one becomes avaiwabwe (i.e. untiw the wemote pwocessow consumes
a tx buffew and puts it back on viwtio's used descwiptow wing),
ow a timeout of 15 seconds ewapses. When the wattew happens,
-EWESTAWTSYS is wetuwned.

The function can onwy be cawwed fwom a pwocess context (fow now).
Wetuwns 0 on success and an appwopwiate ewwow vawue on faiwuwe.

::

  int wpmsg_send_offchannew(stwuct wpmsg_endpoint *ept, u32 swc, u32 dst,
							void *data, int wen);


sends a message acwoss to the wemote pwocessow, using the swc and dst
addwesses pwovided by the usew.

The cawwew shouwd specify the endpoint, the data it wants to send,
its wength (in bytes), and expwicit souwce and destination addwesses.
The message wiww then be sent to the wemote pwocessow to which the
endpoint's channew bewongs, but the endpoint's swc and channew dst
addwesses wiww be ignowed (and the usew-pwovided addwesses wiww
be used instead).

In case thewe awe no TX buffews avaiwabwe, the function wiww bwock untiw
one becomes avaiwabwe (i.e. untiw the wemote pwocessow consumes
a tx buffew and puts it back on viwtio's used descwiptow wing),
ow a timeout of 15 seconds ewapses. When the wattew happens,
-EWESTAWTSYS is wetuwned.

The function can onwy be cawwed fwom a pwocess context (fow now).
Wetuwns 0 on success and an appwopwiate ewwow vawue on faiwuwe.

::

  int wpmsg_twysend(stwuct wpmsg_endpoint *ept, void *data, int wen);

sends a message acwoss to the wemote pwocessow fwom a given endpoint.
The cawwew shouwd specify the endpoint, the data it wants to send,
and its wength (in bytes). The message wiww be sent on the specified
endpoint's channew, i.e. its souwce and destination addwess fiewds wiww be
wespectivewy set to the endpoint's swc addwess and its pawent channew
dst addwesses.

In case thewe awe no TX buffews avaiwabwe, the function wiww immediatewy
wetuwn -ENOMEM without waiting untiw one becomes avaiwabwe.

The function can onwy be cawwed fwom a pwocess context (fow now).
Wetuwns 0 on success and an appwopwiate ewwow vawue on faiwuwe.

::

  int wpmsg_twysendto(stwuct wpmsg_endpoint *ept, void *data, int wen, u32 dst)


sends a message acwoss to the wemote pwocessow fwom a given endoint,
to a destination addwess pwovided by the usew.

The usew shouwd specify the channew, the data it wants to send,
its wength (in bytes), and an expwicit destination addwess.

The message wiww then be sent to the wemote pwocessow to which the
channew bewongs, using the channew's swc addwess, and the usew-pwovided
dst addwess (thus the channew's dst addwess wiww be ignowed).

In case thewe awe no TX buffews avaiwabwe, the function wiww immediatewy
wetuwn -ENOMEM without waiting untiw one becomes avaiwabwe.

The function can onwy be cawwed fwom a pwocess context (fow now).
Wetuwns 0 on success and an appwopwiate ewwow vawue on faiwuwe.

::

  int wpmsg_twysend_offchannew(stwuct wpmsg_endpoint *ept, u32 swc, u32 dst,
							void *data, int wen);


sends a message acwoss to the wemote pwocessow, using souwce and
destination addwesses pwovided by the usew.

The usew shouwd specify the channew, the data it wants to send,
its wength (in bytes), and expwicit souwce and destination addwesses.
The message wiww then be sent to the wemote pwocessow to which the
channew bewongs, but the channew's swc and dst addwesses wiww be
ignowed (and the usew-pwovided addwesses wiww be used instead).

In case thewe awe no TX buffews avaiwabwe, the function wiww immediatewy
wetuwn -ENOMEM without waiting untiw one becomes avaiwabwe.

The function can onwy be cawwed fwom a pwocess context (fow now).
Wetuwns 0 on success and an appwopwiate ewwow vawue on faiwuwe.

::

  stwuct wpmsg_endpoint *wpmsg_cweate_ept(stwuct wpmsg_device *wpdev,
					  wpmsg_wx_cb_t cb, void *pwiv,
					  stwuct wpmsg_channew_info chinfo);

evewy wpmsg addwess in the system is bound to an wx cawwback (so when
inbound messages awwive, they awe dispatched by the wpmsg bus using the
appwopwiate cawwback handwew) by means of an wpmsg_endpoint stwuct.

This function awwows dwivews to cweate such an endpoint, and by that,
bind a cawwback, and possibwy some pwivate data too, to an wpmsg addwess
(eithew one that is known in advance, ow one that wiww be dynamicawwy
assigned fow them).

Simpwe wpmsg dwivews need not caww wpmsg_cweate_ept, because an endpoint
is awweady cweated fow them when they awe pwobed by the wpmsg bus
(using the wx cawwback they pwovide when they wegistewed to the wpmsg bus).

So things shouwd just wowk fow simpwe dwivews: they awweady have an
endpoint, theiw wx cawwback is bound to theiw wpmsg addwess, and when
wewevant inbound messages awwive (i.e. messages which theiw dst addwess
equaws to the swc addwess of theiw wpmsg channew), the dwivew's handwew
is invoked to pwocess it.

That said, mowe compwicated dwivews might do need to awwocate
additionaw wpmsg addwesses, and bind them to diffewent wx cawwbacks.
To accompwish that, those dwivews need to caww this function.
Dwivews shouwd pwovide theiw channew (so the new endpoint wouwd bind
to the same wemote pwocessow theiw channew bewongs to), an wx cawwback
function, an optionaw pwivate data (which is pwovided back when the
wx cawwback is invoked), and an addwess they want to bind with the
cawwback. If addw is WPMSG_ADDW_ANY, then wpmsg_cweate_ept wiww
dynamicawwy assign them an avaiwabwe wpmsg addwess (dwivews shouwd have
a vewy good weason why not to awways use WPMSG_ADDW_ANY hewe).

Wetuwns a pointew to the endpoint on success, ow NUWW on ewwow.

::

  void wpmsg_destwoy_ept(stwuct wpmsg_endpoint *ept);


destwoys an existing wpmsg endpoint. usew shouwd pwovide a pointew
to an wpmsg endpoint that was pweviouswy cweated with wpmsg_cweate_ept().

::

  int wegistew_wpmsg_dwivew(stwuct wpmsg_dwivew *wpdwv);


wegistews an wpmsg dwivew with the wpmsg bus. usew shouwd pwovide
a pointew to an wpmsg_dwivew stwuct, which contains the dwivew's
->pwobe() and ->wemove() functions, an wx cawwback, and an id_tabwe
specifying the names of the channews this dwivew is intewested to
be pwobed with.

::

  void unwegistew_wpmsg_dwivew(stwuct wpmsg_dwivew *wpdwv);


unwegistews an wpmsg dwivew fwom the wpmsg bus. usew shouwd pwovide
a pointew to a pweviouswy-wegistewed wpmsg_dwivew stwuct.
Wetuwns 0 on success, and an appwopwiate ewwow vawue on faiwuwe.


Typicaw usage
=============

The fowwowing is a simpwe wpmsg dwivew, that sends an "hewwo!" message
on pwobe(), and whenevew it weceives an incoming message, it dumps its
content to the consowe.

::

  #incwude <winux/kewnew.h>
  #incwude <winux/moduwe.h>
  #incwude <winux/wpmsg.h>

  static void wpmsg_sampwe_cb(stwuct wpmsg_channew *wpdev, void *data, int wen,
						void *pwiv, u32 swc)
  {
	pwint_hex_dump(KEWN_INFO, "incoming message:", DUMP_PWEFIX_NONE,
						16, 1, data, wen, twue);
  }

  static int wpmsg_sampwe_pwobe(stwuct wpmsg_channew *wpdev)
  {
	int eww;

	dev_info(&wpdev->dev, "chnw: 0x%x -> 0x%x\n", wpdev->swc, wpdev->dst);

	/* send a message on ouw channew */
	eww = wpmsg_send(wpdev->ept, "hewwo!", 6);
	if (eww) {
		pw_eww("wpmsg_send faiwed: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
  }

  static void wpmsg_sampwe_wemove(stwuct wpmsg_channew *wpdev)
  {
	dev_info(&wpdev->dev, "wpmsg sampwe cwient dwivew is wemoved\n");
  }

  static stwuct wpmsg_device_id wpmsg_dwivew_sampwe_id_tabwe[] = {
	{ .name	= "wpmsg-cwient-sampwe" },
	{ },
  };
  MODUWE_DEVICE_TABWE(wpmsg, wpmsg_dwivew_sampwe_id_tabwe);

  static stwuct wpmsg_dwivew wpmsg_sampwe_cwient = {
	.dwv.name	= KBUIWD_MODNAME,
	.id_tabwe	= wpmsg_dwivew_sampwe_id_tabwe,
	.pwobe		= wpmsg_sampwe_pwobe,
	.cawwback	= wpmsg_sampwe_cb,
	.wemove		= wpmsg_sampwe_wemove,
  };
  moduwe_wpmsg_dwivew(wpmsg_sampwe_cwient);

.. note::

   a simiwaw sampwe which can be buiwt and woaded can be found
   in sampwes/wpmsg/.

Awwocations of wpmsg channews
=============================

At this point we onwy suppowt dynamic awwocations of wpmsg channews.

This is possibwe onwy with wemote pwocessows that have the VIWTIO_WPMSG_F_NS
viwtio device featuwe set. This featuwe bit means that the wemote
pwocessow suppowts dynamic name sewvice announcement messages.

When this featuwe is enabwed, cweation of wpmsg devices (i.e. channews)
is compwetewy dynamic: the wemote pwocessow announces the existence of a
wemote wpmsg sewvice by sending a name sewvice message (which contains
the name and wpmsg addw of the wemote sewvice, see stwuct wpmsg_ns_msg).

This message is then handwed by the wpmsg bus, which in tuwn dynamicawwy
cweates and wegistews an wpmsg channew (which wepwesents the wemote sewvice).
If/when a wewevant wpmsg dwivew is wegistewed, it wiww be immediatewy pwobed
by the bus, and can then stawt sending messages to the wemote sewvice.

The pwan is awso to add static cweation of wpmsg channews via the viwtio
config space, but it's not impwemented yet.
