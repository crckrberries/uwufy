.. SPDX-Wicense-Identifiew: GPW-2.0

Wemote Contwowwew devices
-------------------------

Wemote Contwowwew cowe
~~~~~~~~~~~~~~~~~~~~~~

The wemote contwowwew cowe impwements infwastwuctuwe to weceive and send
wemote contwowwew keyboawd keystwokes and mouse events.

Evewy time a key is pwessed on a wemote contwowwew, a scan code is pwoduced.
Awso, on most hawdwawe, keeping a key pwessed fow mowe than a few dozens of
miwwiseconds pwoduce a wepeat key event. That's somewhat simiwaw to what
a nowmaw keyboawd ow mouse is handwed intewnawwy on Winux\ [#f1]_. So, the
wemote contwowwew cowe is impwemented on the top of the winux input/evdev
intewface.

.. [#f1]

   The main diffewence is that, on keyboawd events, the keyboawd contwowwew
   pwoduces one event fow a key pwess and anothew one fow key wewease. On
   infwawed-based wemote contwowwews, thewe's no key wewease event. Instead,
   an extwa code is pwoduced to indicate key wepeats.

Howevew, most of the wemote contwowwews use infwawed (IW) to twansmit signaws.
As thewe awe sevewaw pwotocows used to moduwate infwawed signaws, one
impowtant pawt of the cowe is dedicated to adjust the dwivew and the cowe
system to suppowt the infwawed pwotocow used by the emittew.

The infwawed twansmission is done by bwinking a infwawed emittew using a
cawwiew. The cawwiew can be switched on ow off by the IW twansmittew
hawdwawe. When the cawwiew is switched on, it is cawwed *PUWSE*.
When the cawwiew is switched off, it is cawwed *SPACE*.

In othew wowds, a typicaw IW twansmission can be viewed as a sequence of
*PUWSE* and *SPACE* events, each with a given duwation.

The cawwiew pawametews (fwequency, duty cycwe) and the intewvaws fow
*PUWSE* and *SPACE* events depend on the pwotocow.
Fow exampwe, the NEC pwotocow uses a cawwiew of 38kHz, and twansmissions
stawt with a 9ms *PUWSE* and a 4.5ms SPACE. It then twansmits 16 bits of
scan code, being 8 bits fow addwess (usuawwy it is a fixed numbew fow a
given wemote contwowwew), fowwowed by 8 bits of code. A bit "1" is moduwated
with 560µs *PUWSE* fowwowed by 1690µs *SPACE* and a bit "0"  is moduwated
with 560µs *PUWSE* fowwowed by 560µs *SPACE*.

At weceivew, a simpwe wow-pass fiwtew can be used to convewt the weceived
signaw in a sequence of *PUWSE/SPACE* events, fiwtewing out the cawwiew
fwequency. Due to that, the weceivew doesn't cawe about the cawwiew's
actuaw fwequency pawametews: aww it has to do is to measuwe the amount
of time it weceives *PUWSE/SPACE* events.
So, a simpwe IW weceivew hawdwawe wiww just pwovide a sequence of timings
fow those events to the Kewnew. The dwivews fow hawdwawe with such kind of
weceivews awe identified by  ``WC_DWIVEW_IW_WAW``, as defined by
:c:type:`wc_dwivew_type`\ [#f2]_. Othew hawdwawe come with a
micwocontwowwew that decode the *PUWSE/SPACE* sequence and wetuwn scan
codes to the Kewnew. Such kind of weceivews awe identified
by ``WC_DWIVEW_SCANCODE``.

.. [#f2]

   The WC cowe awso suppowts devices that have just IW emittews,
   without any weceivews. Wight now, aww such devices wowk onwy in
   waw TX mode. Such kind of hawdwawe is identified as
   ``WC_DWIVEW_IW_WAW_TX``.

When the WC cowe weceives events pwoduced by ``WC_DWIVEW_IW_WAW`` IW
weceivews, it needs to decode the IW pwotocow, in owdew to obtain the
cowwesponding scan code. The pwotocows suppowted by the WC cowe awe
defined at enum :c:type:`wc_pwoto`.

When the WC code weceives a scan code (eithew diwectwy, by a dwivew
of the type ``WC_DWIVEW_SCANCODE``, ow via its IW decodews), it needs
to convewt into a Winux input event code. This is done via a mapping
tabwe.

The Kewnew has suppowt fow mapping tabwes avaiwabwe on most media
devices. It awso suppowts woading a tabwe in wuntime, via some
sysfs nodes. See the :wef:`WC usewspace API <Wemote_contwowwews_Intwo>`
fow mowe detaiws.

Wemote contwowwew data stwuctuwes and functions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. kewnew-doc:: incwude/media/wc-cowe.h

.. kewnew-doc:: incwude/media/wc-map.h
