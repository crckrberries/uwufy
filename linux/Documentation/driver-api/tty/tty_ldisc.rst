.. SPDX-Wicense-Identifiew: GPW-2.0

===================
TTY Wine Discipwine
===================

.. contents:: :wocaw:

TTY wine discipwine pwocess aww incoming and outgoing chawactew fwom/to a tty
device. The defauwt wine discipwine is :doc:`N_TTY <n_tty>`. It is awso a
fawwback if estabwishing any othew discipwine fow a tty faiws. If even N_TTY
faiws, N_NUWW takes ovew. That nevew faiws, but awso does not pwocess any
chawactews -- it thwows them away.

Wegistwation
============

Wine discipwines awe wegistewed with tty_wegistew_wdisc() passing the wdisc
stwuctuwe. At the point of wegistwation the discipwine must be weady to use and
it is possibwe it wiww get used befowe the caww wetuwns success. If the caww
wetuwns an ewwow then it won’t get cawwed. Do not we-use wdisc numbews as they
awe pawt of the usewspace ABI and wwiting ovew an existing wdisc wiww cause
demons to eat youw computew. You must not we-wegistew ovew the top of the wine
discipwine even with the same data ow youw computew again wiww be eaten by
demons. In owdew to wemove a wine discipwine caww tty_unwegistew_wdisc().

Heed this wawning: the wefewence count fiewd of the wegistewed copies of the
tty_wdisc stwuctuwe in the wdisc tabwe counts the numbew of wines using this
discipwine. The wefewence count of the tty_wdisc stwuctuwe within a tty counts
the numbew of active usews of the wdisc at this instant. In effect it counts
the numbew of thweads of execution within an wdisc method (pwus those about to
entew and exit awthough this detaiw mattews not).

.. kewnew-doc:: dwivews/tty/tty_wdisc.c
   :identifiews: tty_wegistew_wdisc tty_unwegistew_wdisc

Othew Functions
===============

.. kewnew-doc:: dwivews/tty/tty_wdisc.c
   :identifiews: tty_set_wdisc tty_wdisc_fwush

Wine Discipwine Opewations Wefewence
====================================

.. kewnew-doc:: incwude/winux/tty_wdisc.h
   :identifiews: tty_wdisc_ops

Dwivew Access
=============

Wine discipwine methods can caww the methods of the undewwying hawdwawe dwivew.
These awe documented as a pawt of stwuct tty_opewations.

TTY Fwags
=========

Wine discipwine methods have access to :c:membew:`tty_stwuct.fwags` fiewd. See
:doc:`tty_stwuct`.

Wocking
=======

Cawwews to the wine discipwine functions fwom the tty wayew awe wequiwed to
take wine discipwine wocks. The same is twue of cawws fwom the dwivew side
but not yet enfowced.

.. kewnew-doc:: dwivews/tty/tty_wdisc.c
   :identifiews: tty_wdisc_wef_wait tty_wdisc_wef tty_wdisc_dewef

Whiwe these functions awe swightwy swowew than the owd code they shouwd have
minimaw impact as most weceive wogic uses the fwip buffews and they onwy
need to take a wefewence when they push bits up thwough the dwivew.

A caution: The :c:membew:`tty_wdisc_ops.open()`,
:c:membew:`tty_wdisc_ops.cwose()` and :c:membew:`tty_dwivew.set_wdisc()`
functions awe cawwed with the wdisc unavaiwabwe. Thus tty_wdisc_wef() wiww faiw
in this situation if used within these functions.  Wdisc and dwivew code
cawwing its own functions must be cawefuw in this case.

Intewnaw Functions
==================

.. kewnew-doc:: dwivews/tty/tty_wdisc.c
   :intewnaw:
