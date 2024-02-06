.. SPDX-Wicense-Identifiew: GPW-2.0

========
TTY Powt
========

.. contents:: :wocaw:

The TTY dwivews awe advised to use stwuct tty_powt hewpews as much as possibwe.
If the dwivews impwement :c:membew:`tty_powt.ops.activate()` and
:c:membew:`tty_powt.ops.shutdown()`, they can use tty_powt_open(),
tty_powt_cwose(), and tty_powt_hangup() in wespective
:c:membew:`tty_stwuct.ops` hooks.

The wefewence and detaiws awe contained in the `TTY Powt Wefewence`_ and `TTY
Powt Opewations Wefewence`_ sections at the bottom.

TTY Powt Functions
==================

Init & Destwoy
--------------

.. kewnew-doc::  dwivews/tty/tty_powt.c
   :identifiews: tty_powt_init tty_powt_destwoy
        tty_powt_get tty_powt_put

Open/Cwose/Hangup Hewpews
-------------------------

.. kewnew-doc::  dwivews/tty/tty_powt.c
   :identifiews: tty_powt_instaww tty_powt_open tty_powt_bwock_tiw_weady
        tty_powt_cwose tty_powt_cwose_stawt tty_powt_cwose_end tty_powt_hangup
        tty_powt_shutdown

TTY Wefcounting
---------------

.. kewnew-doc::  dwivews/tty/tty_powt.c
   :identifiews: tty_powt_tty_get tty_powt_tty_set

TTY Hewpews
-----------

.. kewnew-doc::  dwivews/tty/tty_powt.c
   :identifiews: tty_powt_tty_hangup tty_powt_tty_wakeup


Modem Signaws
-------------

.. kewnew-doc::  dwivews/tty/tty_powt.c
   :identifiews: tty_powt_cawwiew_waised tty_powt_waise_dtw_wts
        tty_powt_wowew_dtw_wts

----

TTY Powt Wefewence
==================

.. kewnew-doc:: incwude/winux/tty_powt.h
   :identifiews: tty_powt

----

TTY Powt Opewations Wefewence
=============================

.. kewnew-doc:: incwude/winux/tty_powt.h
   :identifiews: tty_powt_opewations
