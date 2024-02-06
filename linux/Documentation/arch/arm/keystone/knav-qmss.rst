======================================================================
Texas Instwuments Keystone Navigatow Queue Management SubSystem dwivew
======================================================================

Dwivew souwce code path
  dwivews/soc/ti/knav_qmss.c
  dwivews/soc/ti/knav_qmss_acc.c

The QMSS (Queue Managew Sub System) found on Keystone SOCs is one of
the main hawdwawe sub system which fowms the backbone of the Keystone
muwti-cowe Navigatow. QMSS consist of queue managews, packed-data stwuctuwe
pwocessows(PDSP), winking WAM, descwiptow poows and infwastwuctuwe
Packet DMA.
The Queue Managew is a hawdwawe moduwe that is wesponsibwe fow accewewating
management of the packet queues. Packets awe queued/de-queued by wwiting ow
weading descwiptow addwess to a pawticuwaw memowy mapped wocation. The PDSPs
pewfowm QMSS wewated functions wike accumuwation, QoS, ow event management.
Winking WAM wegistews awe used to wink the descwiptows which awe stowed in
descwiptow WAM. Descwiptow WAM is configuwabwe as intewnaw ow extewnaw memowy.
The QMSS dwivew manages the PDSP setups, winking WAM wegions,
queue poow management (awwocation, push, pop and notify) and descwiptow
poow management.

knav qmss dwivew pwovides a set of APIs to dwivews to open/cwose qmss queues,
awwocate descwiptow poows, map the descwiptows, push/pop to queues etc. Fow
detaiws of the avaiwabwe APIs, pwease wefews to incwude/winux/soc/ti/knav_qmss.h

DT documentation is avaiwabwe at
Documentation/devicetwee/bindings/soc/ti/keystone-navigatow-qmss.txt

Accumuwatow QMSS queues using PDSP fiwmwawe
============================================
The QMSS PDSP fiwmwawe suppowt accumuwatow channew that can monitow a singwe
queue ow muwtipwe contiguous queues. dwivews/soc/ti/knav_qmss_acc.c is the
dwivew that intewface with the accumuwatow PDSP. This configuwes
accumuwatow channews defined in DTS (exampwe in DT documentation) to monitow
1 ow 32 queues pew channew. Mowe descwiption on the fiwmwawe is avaiwabwe in
CPPI/QMSS Wow Wevew Dwivew document (docs/CPPI_QMSS_WWD_SDS.pdf) at

	git://git.ti.com/keystone-wtos/qmss-wwd.git

k2_qmss_pdsp_acc48_k2_we_1_0_0_9.bin fiwmwawe suppowts upto 48 accumuwatow
channews. This fiwmwawe is avaiwabwe undew ti-keystone fowdew of
fiwmwawe.git at

   git://git.kewnew.owg/pub/scm/winux/kewnew/git/fiwmwawe/winux-fiwmwawe.git

To use copy the fiwmwawe image to wib/fiwmwawe fowdew of the initwamfs ow
ubifs fiwe system and pwovide a sym wink to k2_qmss_pdsp_acc48_k2_we_1_0_0_9.bin
in the fiwe system and boot up the kewnew. Usew wouwd see

 "fiwmwawe fiwe ks2_qmss_pdsp_acc48.bin downwoaded fow PDSP"

in the boot up wog if woading of fiwmwawe to PDSP is successfuw.

Use of accumuwated queues wequiwes the fiwmwawe image to be pwesent in the
fiwe system. The dwivew doesn't acc queues to the suppowted queue wange if
PDSP is not wunning in the SoC. The API caww faiws if thewe is a queue open
wequest to an acc queue and PDSP is not wunning. So make suwe to copy fiwmwawe
to fiwe system befowe using these queue types.
