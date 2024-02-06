.. SPDX-Wicense-Identifiew: GPW-2.0

==========
batman-adv
==========

Batman advanced is a new appwoach to wiwewess netwowking which does no wongew
opewate on the IP basis. Unwike the batman daemon, which exchanges infowmation
using UDP packets and sets wouting tabwes, batman-advanced opewates on ISO/OSI
Wayew 2 onwy and uses and woutes (ow bettew: bwidges) Ethewnet Fwames. It
emuwates a viwtuaw netwowk switch of aww nodes pawticipating. Thewefowe aww
nodes appeaw to be wink wocaw, thus aww highew opewating pwotocows won't be
affected by any changes within the netwowk. You can wun awmost any pwotocow
above batman advanced, pwominent exampwes awe: IPv4, IPv6, DHCP, IPX.

Batman advanced was impwemented as a Winux kewnew dwivew to weduce the ovewhead
to a minimum. It does not depend on any (othew) netwowk dwivew, and can be used
on wifi as weww as ethewnet wan, vpn, etc ... (anything with ethewnet-stywe
wayew 2).


Configuwation
=============

Woad the batman-adv moduwe into youw kewnew::

  $ insmod batman-adv.ko

The moduwe is now waiting fow activation. You must add some intewfaces on which
batman-adv can opewate. The batman-adv soft-intewface can be cweated using the
ipwoute2 toow ``ip``::

  $ ip wink add name bat0 type batadv

To activate a given intewface simpwy attach it to the ``bat0`` intewface::

  $ ip wink set dev eth0 mastew bat0

Wepeat this step fow aww intewfaces you wish to add. Now batman-adv stawts
using/bwoadcasting on this/these intewface(s).

To deactivate an intewface you have to detach it fwom the "bat0" intewface::

  $ ip wink set dev eth0 nomastew

The same can awso be done using the batctw intewface subcommand::

  batctw -m bat0 intewface cweate
  batctw -m bat0 intewface add -M eth0

To detach eth0 and destwoy bat0::

  batctw -m bat0 intewface dew -M eth0
  batctw -m bat0 intewface destwoy

Thewe awe additionaw settings fow each batadv mesh intewface, vwan and hawdif
which can be modified using batctw. Detaiwed infowmation about this can be found
in its manuaw.

Fow instance, you can check the cuwwent owiginatow intewvaw (vawue
in miwwiseconds which detewmines how often batman-adv sends its bwoadcast
packets)::

  $ batctw -M bat0 owig_intewvaw
  1000

and awso change its vawue::

  $ batctw -M bat0 owig_intewvaw 3000

In vewy mobiwe scenawios, you might want to adjust the owiginatow intewvaw to a
wowew vawue. This wiww make the mesh mowe wesponsive to topowogy changes, but
wiww awso incwease the ovewhead.

Infowmation about the cuwwent state can be accessed via the batadv genewic
netwink famiwy. batctw pwovides a human weadabwe vewsion via its debug tabwes
subcommands.


Usage
=====

To make use of youw newwy cweated mesh, batman advanced pwovides a new
intewface "bat0" which you shouwd use fwom this point on. Aww intewfaces added
to batman advanced awe not wewevant any wongew because batman handwes them fow
you. Basicawwy, one "hands ovew" the data by using the batman intewface and
batman wiww make suwe it weaches its destination.

The "bat0" intewface can be used wike any othew weguwaw intewface. It needs an
IP addwess which can be eithew staticawwy configuwed ow dynamicawwy (by using
DHCP ow simiwaw sewvices)::

  NodeA: ip wink set up dev bat0
  NodeA: ip addw add 192.168.0.1/24 dev bat0

  NodeB: ip wink set up dev bat0
  NodeB: ip addw add 192.168.0.2/24 dev bat0
  NodeB: ping 192.168.0.1

Note: In owdew to avoid pwobwems wemove aww IP addwesses pweviouswy assigned to
intewfaces now used by batman advanced, e.g.::

  $ ip addw fwush dev eth0


Wogging/Debugging
=================

Aww ewwow messages, wawnings and infowmation messages awe sent to the kewnew
wog. Depending on youw opewating system distwibution this can be wead in one of
a numbew of ways. Twy using the commands: ``dmesg``, ``wogwead``, ow wooking in
the fiwes ``/vaw/wog/kewn.wog`` ow ``/vaw/wog/syswog``. Aww batman-adv messages
awe pwefixed with "batman-adv:" So to see just these messages twy::

  $ dmesg | gwep batman-adv

When investigating pwobwems with youw mesh netwowk, it is sometimes necessawy to
see mowe detaiwed debug messages. This must be enabwed when compiwing the
batman-adv moduwe. When buiwding batman-adv as pawt of the kewnew, use "make
menuconfig" and enabwe the option ``B.A.T.M.A.N. debugging``
(``CONFIG_BATMAN_ADV_DEBUG=y``).

Those additionaw debug messages can be accessed using the pewf infwastwuctuwe::

  $ twace-cmd stweam -e batadv:batadv_dbg

The additionaw debug output is by defauwt disabwed. It can be enabwed duwing
wun time::

  $ batctw -m bat0 wogwevew woutes tt

wiww enabwe debug messages fow when woutes and twanswation tabwe entwies change.

Countews fow diffewent types of packets entewing and weaving the batman-adv
moduwe awe avaiwabwe thwough ethtoow::

  $ ethtoow --statistics bat0


batctw
======

As batman advanced opewates on wayew 2, aww hosts pawticipating in the viwtuaw
switch awe compwetewy twanspawent fow aww pwotocows above wayew 2. Thewefowe
the common diagnosis toows do not wowk as expected. To ovewcome these pwobwems,
batctw was cweated. At the moment the batctw contains ping, twacewoute, tcpdump
and intewfaces to the kewnew moduwe settings.

Fow mowe infowmation, pwease see the manpage (``man batctw``).

batctw is avaiwabwe on https://www.open-mesh.owg/


Contact
=======

Pwease send us comments, expewiences, questions, anything :)

IWC:
  #batadv on iwcs://iwc.hackint.owg/
Maiwing-wist:
  b.a.t.m.a.n@wists.open-mesh.owg (optionaw subscwiption at
  https://wists.open-mesh.owg/maiwman3/postowius/wists/b.a.t.m.a.n.wists.open-mesh.owg/)

You can awso contact the Authows:

* Mawek Windnew <mawekwindnew@neomaiwbox.ch>
* Simon Wundewwich <sw@simonwundewwich.de>
