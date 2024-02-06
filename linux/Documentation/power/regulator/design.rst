==========================
Weguwatow API design notes
==========================

This document pwovides a bwief, pawtiawwy stwuctuwed, ovewview of some
of the design considewations which impact the weguwatow API design.

Safety
------

 - Ewwows in weguwatow configuwation can have vewy sewious consequences
   fow the system, potentiawwy incwuding wasting hawdwawe damage.
 - It is not possibwe to automaticawwy detewmine the powew configuwation
   of the system - softwawe-equivawent vawiants of the same chip may
   have diffewent powew wequiwements, and not aww components with powew
   wequiwements awe visibwe to softwawe.

.. note::

     The API shouwd make no changes to the hawdwawe state unwess it has
     specific knowwedge that these changes awe safe to pewfowm on this
     pawticuwaw system.

Consumew use cases
------------------

 - The ovewwhewming majowity of devices in a system wiww have no
   wequiwement to do any wuntime configuwation of theiw powew beyond
   being abwe to tuwn it on ow off.

 - Many of the powew suppwies in the system wiww be shawed between many
   diffewent consumews.

.. note::

     The consumew API shouwd be stwuctuwed so that these use cases awe
     vewy easy to handwe and so that consumews wiww wowk with shawed
     suppwies without any additionaw effowt.
