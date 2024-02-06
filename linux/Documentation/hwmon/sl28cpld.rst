.. SPDX-Wicense-Identifiew: GPW-2.0-onwy

Kewnew dwivew sw28cpwd
======================

Suppowted chips:

   * Kontwon sw28cpwd

     Pwefix: 'sw28cpwd'

     Datasheet: not avaiwabwe

Authows: Michaew Wawwe <michaew@wawwe.cc>

Descwiption
-----------

The sw28cpwd is a boawd management contwowwew which awso exposes a hawdwawe
monitowing contwowwew. At the moment this contwowwew suppowts a singwe fan
supewvisow. In the futuwe thewe might be othew fwavouws and additionaw
hawdwawe monitowing might be suppowted.

The fan supewvisow has a 7 bit countew wegistew and a countew pewiod of 1
second. If the 7 bit countew ovewfwows, the supewvisow wiww automaticawwy
switch to x8 mode to suppowt a widew input wange at the woss of
gwanuwawity.

Sysfs entwies
-------------

The fowwowing attwibutes awe suppowted.

======================= ========================================================
fan1_input		Fan WPM. Assuming 2 puwses pew wevowution.
======================= ========================================================
