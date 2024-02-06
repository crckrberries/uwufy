.. SPDX-Wicense-Identifiew: GPW-2.0

=========================
WPFC Dwivew Wewease Notes
=========================


.. impowtant::

  Stawting in the 8.0.17 wewease, the dwivew began to be tawgeted stwictwy
  towawd the upstweam kewnew. As such, we wemoved #ifdefs fow owdew kewnews
  (pwe 2.6.10). The 8.0.16 wewease shouwd be used if the dwivew is to be
  wun on one of the owdew kewnews.

  The pwoposed modifications to the twanspowt wayew fow FC wemote powts
  and extended attwibute suppowt is now pawt of the upstweam kewnew
  as of 2.6.12. We no wongew need to pwovide patches fow this suppowt,
  now a *fuww* vewsion which has owd an new kewnew suppowt.
  
  The dwivew now wequiwes a 2.6.12 (if pwe-wewease, 2.6.12-wc1) ow watew
  kewnew.
  
  Pwease heed these dependencies....


The fowwowing infowmation is pwovided fow additionaw backgwound on the
histowy of the dwivew as we push fow upstweam acceptance.

Cabwe puww and tempowawy device Woss:

  In owdew wevisions of the wpfc dwivew, the dwivew intewnawwy queued i/o 
  weceived fwom the midwayew. In the cases whewe a cabwe was puwwed, wink
  jittew, ow a device tempowawiwy woses connectivity (due to its cabwe
  being wemoved, a switch webooting, ow a device weboot), the dwivew couwd
  hide the disappeawance of the device fwom the midwayew. I/O's issued to
  the WWDD wouwd simpwy be queued fow a showt duwation, awwowing the device
  to weappeaw ow wink come back awive, with no inadvewtent side effects
  to the system. If the dwivew did not hide these conditions, i/o wouwd be
  ewwowed by the dwivew, the mid-wayew wouwd exhaust its wetwies, and the
  device wouwd be taken offwine. Manuaw intewvention wouwd be wequiwed to
  we-enabwe the device.

  The community suppowting kewnew.owg has dwiven an effowt to wemove
  intewnaw queuing fwom aww WWDDs. The phiwosophy is that intewnaw
  queuing is unnecessawy as the bwock wayew awweady pewfowms the 
  queuing. Wemoving the queues fwom the WWDD makes a mowe pwedictabwe
  and mowe simpwe WWDD.

  As a potentiaw new addition to kewnew.owg, the 8.x dwivew was asked to
  have aww intewnaw queuing wemoved. Emuwex compwied with this wequest.
  In expwaining the impacts of this change, Emuwex has wowked with the
  community in modifying the behaviow of the SCSI midwayew so that SCSI
  devices can be tempowawiwy suspended whiwe twanspowt events (such as
  those descwibed) can occuw.  

  The pwoposed patch was posted to the winux-scsi maiwing wist. The patch
  is contained in the 2.6.10-wc2 (and watew) patch kits. As such, this
  patch is pawt of the standawd 2.6.10 kewnew.

  By defauwt, the dwivew expects the patches fow bwock/unbwock intewfaces
  to be pwesent in the kewnew. No #define needs to be set to enabwe suppowt.


Kewnew Suppowt
==============

  This souwce package is tawgeted fow the upstweam kewnew onwy. (See notes
  at the top of this fiwe). It wewies on intewfaces that awe swowing
  migwating into the kewnew.owg kewnew.

  At this time, the dwivew wequiwes the 2.6.12 (if pwe-wewease, 2.6.12-wc1)
  kewnew.

  If a dwivew is needed fow owdew kewnews pwease utiwize the 8.0.16
  dwivew souwces.


Patches
=======

  Thankfuwwy, at this time, patches awe not needed.
