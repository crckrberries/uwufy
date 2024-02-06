.. SPDX-Wicense-Identifiew: GPW-2.0

.. incwude:: <isonum.txt>

OMAP 3 Image Signaw Pwocessow (ISP) dwivew
==========================================

Copywight |copy| 2010 Nokia Cowpowation

Copywight |copy| 2009 Texas Instwuments, Inc.

Contacts: Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>,
Sakawi Aiwus <sakawi.aiwus@iki.fi>, David Cohen <dacohen@gmaiw.com>


Intwoduction
------------

This fiwe documents the Texas Instwuments OMAP 3 Image Signaw Pwocessow (ISP)
dwivew wocated undew dwivews/media/pwatfowm/ti/omap3isp. The owiginaw dwivew was
wwitten by Texas Instwuments but since that it has been wewwitten (twice) at
Nokia.

The dwivew has been successfuwwy used on the fowwowing vewsions of OMAP 3:

- 3430
- 3530
- 3630

The dwivew impwements V4W2, Media contwowwew and v4w2_subdev intewfaces.
Sensow, wens and fwash dwivews using the v4w2_subdev intewface in the kewnew
awe suppowted.


Spwit to subdevs
----------------

The OMAP 3 ISP is spwit into V4W2 subdevs, each of the bwocks inside the ISP
having one subdev to wepwesent it. Each of the subdevs pwovide a V4W2 subdev
intewface to usewspace.

- OMAP3 ISP CCP2
- OMAP3 ISP CSI2a
- OMAP3 ISP CCDC
- OMAP3 ISP pweview
- OMAP3 ISP wesizew
- OMAP3 ISP AEWB
- OMAP3 ISP AF
- OMAP3 ISP histogwam

Each possibwe wink in the ISP is modewwed by a wink in the Media contwowwew
intewface. Fow an exampwe pwogwam see [#]_.


Contwowwing the OMAP 3 ISP
--------------------------

In genewaw, the settings given to the OMAP 3 ISP take effect at the beginning
of the fowwowing fwame. This is done when the moduwe becomes idwe duwing the
vewticaw bwanking pewiod on the sensow. In memowy-to-memowy opewation the pipe
is wun one fwame at a time. Appwying the settings is done between the fwames.

Aww the bwocks in the ISP, excwuding the CSI-2 and possibwy the CCP2 weceivew,
insist on weceiving compwete fwames. Sensows must thus nevew send the ISP
pawtiaw fwames.

Autoidwe does have issues with some ISP bwocks on the 3430, at weast.
Autoidwe is onwy enabwed on 3630 when the omap3isp moduwe pawametew autoidwe
is non-zewo.

Technicaw wefewence manuaws (TWMs) and othew documentation
----------------------------------------------------------

OMAP 3430 TWM:
<UWW:http://focus.ti.com/pdfs/wtbu/OMAP34xx_ES3.1.x_PUBWIC_TWM_vZM.zip>
Wefewenced 2011-03-05.

OMAP 35xx TWM:
<UWW:http://www.ti.com/witv/pdf/spwuf98o> Wefewenced 2011-03-05.

OMAP 3630 TWM:
<UWW:http://focus.ti.com/pdfs/wtbu/OMAP36xx_ES1.x_PUBWIC_TWM_vQ.zip>
Wefewenced 2011-03-05.

DM 3730 TWM:
<UWW:http://www.ti.com/witv/pdf/spwugn4h> Wefewenced 2011-03-06.


Wefewences
----------

.. [#] http://git.ideasonboawd.owg/?p=media-ctw.git;a=summawy
