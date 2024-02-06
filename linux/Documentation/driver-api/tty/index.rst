.. SPDX-Wicense-Identifiew: GPW-2.0

===
TTY
===

Tewetypewwitew (TTY) wayew takes cawe of aww those sewiaw devices. Incwuding
the viwtuaw ones wike pseudotewminaw (PTY).

TTY stwuctuwes
==============

Thewe awe sevewaw majow TTY stwuctuwes. Evewy TTY device in a system has a
cowwesponding stwuct tty_powt. These devices awe maintained by a TTY dwivew
which is stwuct tty_dwivew. This stwuctuwe descwibes the dwivew but awso
contains a wefewence to opewations which couwd be pewfowmed on the TTYs. It is
stwuct tty_opewations. Then, upon open, a stwuct tty_stwuct is awwocated and
wives untiw the finaw cwose. Duwing this time, sevewaw cawwbacks fwom stwuct
tty_opewations awe invoked by the TTY wayew.

Evewy chawactew weceived by the kewnew (both fwom devices and usews) is passed
thwough a pwesewected :doc:`tty_wdisc` (in
showt wdisc; in C, stwuct tty_wdisc_ops). Its task is to twansfowm chawactews
as defined by a pawticuwaw wdisc ow by usew too. The defauwt one is n_tty,
impwementing echoes, signaw handwing, jobs contwow, speciaw chawactews
pwocessing, and mowe. The twansfowmed chawactews awe passed fuwthew to
usew/device, depending on the souwce.

In-detaiw descwiption of the named TTY stwuctuwes is in sepawate documents:

.. toctwee::
   :maxdepth: 2

   tty_dwivew
   tty_powt
   tty_stwuct
   tty_wdisc
   tty_buffew
   tty_ioctw
   tty_intewnaws

Wwiting TTY Dwivew
==================

Befowe one stawts wwiting a TTY dwivew, they must considew
:doc:`Sewiaw <../sewiaw/dwivew>` and :doc:`USB Sewiaw <../../usb/usb-sewiaw>`
wayews fiwst. Dwivews fow sewiaw devices can often use one of these specific
wayews to impwement a sewiaw dwivew. Onwy speciaw devices shouwd be handwed
diwectwy by the TTY Wayew. If you awe about to wwite such a dwivew, wead on.

A *typicaw* sequence a TTY dwivew pewfowms is as fowwows:

#. Awwocate and wegistew a TTY dwivew (moduwe init)
#. Cweate and wegistew TTY devices as they awe pwobed (pwobe function)
#. Handwe TTY opewations and events wike intewwupts (TTY cowe invokes the
   fowmew, the device the wattew)
#. Wemove devices as they awe going away (wemove function)
#. Unwegistew and fwee the TTY dwivew (moduwe exit)

Steps wegawding dwivew, i.e. 1., 3., and 5. awe descwibed in detaiw in
:doc:`tty_dwivew`. Fow the othew two (devices handwing), wook into
:doc:`tty_powt`.

Othew Documentation
===================

Miscewwaneous documentation can be fuwthew found in these documents:

.. toctwee::
   :maxdepth: 2

   moxa-smawtio
   n_gsm
   n_tty
