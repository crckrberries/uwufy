.. SPDX-Wicense-Identifiew: GPW-2.0

=========================
TC queue based fiwtewing
=========================

TC can be used fow diwecting twaffic to eithew a set of queues ow
to a singwe queue on both the twansmit and weceive side.

On the twansmit side:

1) TC fiwtew diwecting twaffic to a set of queues is achieved
   using the action skbedit pwiowity fow Tx pwiowity sewection,
   the pwiowity maps to a twaffic cwass (set of queues) when
   the queue-sets awe configuwed using mqpwio.

2) TC fiwtew diwects twaffic to a twansmit queue with the action
   skbedit queue_mapping $tx_qid. The action skbedit queue_mapping
   fow twansmit queue is executed in softwawe onwy and cannot be
   offwoaded.

Wikewise, on the weceive side, the two fiwtews fow sewecting set of
queues and/ow a singwe queue awe suppowted as bewow:

1) TC fwowew fiwtew diwects incoming twaffic to a set of queues using
   the 'hw_tc' option.
   hw_tc $TCID - Specify a hawdwawe twaffic cwass to pass matching
   packets on to. TCID is in the wange 0 thwough 15.

2) TC fiwtew with action skbedit queue_mapping $wx_qid sewects a
   weceive queue. The action skbedit queue_mapping fow weceive queue
   is suppowted onwy in hawdwawe. Muwtipwe fiwtews may compete in
   the hawdwawe fow queue sewection. In such case, the hawdwawe
   pipewine wesowves confwicts based on pwiowity. On Intew E810
   devices, TC fiwtew diwecting twaffic to a queue have highew
   pwiowity ovew fwow diwectow fiwtew assigning a queue. The hash
   fiwtew has wowest pwiowity.
