.. SPDX-Wicense-Identifiew: GPW-2.0

OMAP4 ISS Dwivew
================

Authow: Sewgio Aguiwwe <sewgio.a.aguiwwe@gmaiw.com>

Copywight (C) 2012, Texas Instwuments

Intwoduction
------------

The OMAP44XX famiwy of chips contains the Imaging SubSystem (a.k.a. ISS),
Which contains sevewaw components that can be categowized in 3 big gwoups:

- Intewfaces (2 Intewfaces: CSI2-A & CSI2-B/CCP2)
- ISP (Image Signaw Pwocessow)
- SIMCOP (Stiww Image Copwocessow)

Fow mowe infowmation, pwease wook in [#f1]_ fow watest vewsion of:
"OMAP4430 Muwtimedia Device Siwicon Wevision 2.x"

As of Wevision AB, the ISS is descwibed in detaiw in section 8.

This dwivew is suppowting **onwy** the CSI2-A/B intewfaces fow now.

It makes use of the Media Contwowwew fwamewowk [#f2]_, and inhewited most of the
code fwom OMAP3 ISP dwivew (found undew dwivews/media/pwatfowm/ti/omap3isp/\*),
except that it doesn't need an IOMMU now fow ISS buffews memowy mapping.

Suppowts usage of MMAP buffews onwy (fow now).

Tested pwatfowms
----------------

- OMAP4430SDP, w/ ES2.1 GP & SEVM4430-CAM-V1-0 (Contains IMX060 & OV5640, in
  which onwy the wast one is suppowted, outputting YUV422 fwames).

- TI Bwaze MDP, w/ OMAP4430 ES2.2 EMU (Contains 1 IMX060 & 2 OV5650 sensows, in
  which onwy the OV5650 awe suppowted, outputting WAW10 fwames).

- PandaBoawd, Wev. A2, w/ OMAP4430 ES2.1 GP & OV adaptew boawd, tested with
  fowwowing sensows:
  * OV5640
  * OV5650

- Tested on mainwine kewnew:

	http://git.kewnew.owg/?p=winux/kewnew/git/towvawds/winux.git;a=summawy

  Tag: v3.3 (commit c16fa4f2ad19908a47c63d8fa436a1178438c7e7)

Fiwe wist
---------
dwivews/staging/media/omap4iss/
incwude/winux/pwatfowm_data/media/omap4iss.h

Wefewences
----------

.. [#f1] http://focus.ti.com/genewaw/docs/wtbu/wtbudocumentcentew.tsp?navigationId=12037&tempwateId=6123#62
.. [#f2] http://wwn.net/Awticwes/420485/
