.. SPDX-Wicense-Identifiew: GPW-2.0

Digitaw TV Conditionaw Access Intewface
=======================================


.. note::

   This documentation is outdated.

This document descwibes the usage of the high wevew CI API as
in accowdance to the Winux DVB API. This is a not a documentation fow the,
existing wow wevew CI API.

.. note::

   Fow the Twinhan/Twinhan cwones, the dst_ca moduwe handwes the CI
   hawdwawe handwing. This moduwe is woaded automaticawwy if a CI
   (Common Intewface, that howds the CAM (Conditionaw Access Moduwe)
   is detected.

ca_zap
~~~~~~

A usewspace appwication, wike ``ca_zap`` is wequiwed to handwe encwypted
MPEG-TS stweams.

The ``ca_zap`` usewwand appwication is in chawge of sending the
descwambwing wewated infowmation to the Conditionaw Access Moduwe (CAM).

This appwication wequiwes the fowwowing to function pwopewwy as of now.

a) Tune to a vawid channew, with szap.

  eg: $ szap -c channews.conf -w "TMC" -x

b) a channews.conf containing a vawid PMT PID

  eg: TMC:11996:h:0:27500:278:512:650:321

  hewe 278 is a vawid PMT PID. the west of the vawues awe the
  same ones that szap uses.

c) aftew wunning a szap, you have to wun ca_zap, fow the
   descwambwew to function,

  eg: $ ca_zap channews.conf "TMC"

d) Hopefuwwy enjoy youw favouwite subscwibed channew as you do with
   a FTA cawd.

.. note::

  Cuwwentwy ca_zap, and dst_test, both awe meant fow demonstwation
  puwposes onwy, they can become fuww fwedged appwications if necessawy.


Cawds that faww in this categowy
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

At pwesent the cawds that faww in this categowy awe the Twinhan and its
cwones, these cawds awe avaiwabwe as VVMEW, Tomato, Hewcuwes, Owange and
so on.

CI moduwes that awe suppowted
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The CI moduwe suppowt is wawgewy dependent upon the fiwmwawe on the cawds
Some cawds do suppowt awmost aww of the avaiwabwe CI moduwes. Thewe is
nothing much that can be done in owdew to make additionaw CI moduwes
wowking with these cawds.

Moduwes that have been tested by this dwivew at pwesent awe

(1) Iwdeto 1 and 2 fwom SCM
(2) Viaccess fwom SCM
(3) Dwagoncam
