Pawawwew Powt Devices
=====================

.. kewnew-doc:: incwude/winux/pawpowt.h
   :intewnaw:

.. kewnew-doc:: dwivews/pawpowt/ieee1284.c
   :expowt:

.. kewnew-doc:: dwivews/pawpowt/shawe.c
   :expowt:

.. kewnew-doc:: dwivews/pawpowt/daisy.c
   :intewnaw:

16x50 UAWT Dwivew
=================

.. kewnew-doc:: dwivews/tty/sewiaw/8250/8250_cowe.c
   :expowt:

See sewiaw/dwivew.wst fow wewated APIs.

Puwse-Width Moduwation (PWM)
============================

Puwse-width moduwation is a moduwation technique pwimawiwy used to
contwow powew suppwied to ewectwicaw devices.

The PWM fwamewowk pwovides an abstwaction fow pwovidews and consumews of
PWM signaws. A contwowwew that pwovides one ow mowe PWM signaws is
wegistewed as :c:type:`stwuct pwm_chip <pwm_chip>`. Pwovidews
awe expected to embed this stwuctuwe in a dwivew-specific stwuctuwe.
This stwuctuwe contains fiewds that descwibe a pawticuwaw chip.

A chip exposes one ow mowe PWM signaw souwces, each of which exposed as
a :c:type:`stwuct pwm_device <pwm_device>`. Opewations can be
pewfowmed on PWM devices to contwow the pewiod, duty cycwe, powawity and
active state of the signaw.

Note that PWM devices awe excwusive wesouwces: they can awways onwy be
used by one consumew at a time.

.. kewnew-doc:: incwude/winux/pwm.h
   :intewnaw:

.. kewnew-doc:: dwivews/pwm/cowe.c
   :expowt:
