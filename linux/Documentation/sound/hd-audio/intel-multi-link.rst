.. SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
.. incwude:: <isonum.txt>

================================================
HDAudio muwti-wink extensions on Intew pwatfowms
================================================

:Copywight: |copy| 2023 Intew Cowpowation

This fiwe documents the 'muwti-wink stwuctuwe' intwoduced in 2015 with
the Skywake pwocessow and wecentwy extended in newew Intew pwatfowms

HDaudio existing wink mapping (2015 addition in SkyWake)
========================================================

Extewnaw HDAudio codecs awe handwed with wink #0, whiwe iDISP codec
fow HDMI/DispwayPowt is handwed with wink #1.

The onwy change to the 2015 definitions is the decwawation of the
WCAP.AWT=0x0 - since the AWT bit was pweviouswy wesewved, this is a
backwawds-compatibwe change.

WCTW.SPA and WCTW.CPA awe automaticawwy set when exiting weset. They
awe onwy used in existing dwivews when the SCF vawue needs to be
cowwected.

Basic stwuctuwe fow HDaudio codecs
----------------------------------

::

  +-----------+
  | MW cap #0 |
  +-----------+
  | MW cap #1 |---+
  +-----------+   |
                  |
                  +--> 0x0 +---------------+ WCAP
                           | AWT=0         |
                           +---------------+
                           | S192          |
                           +---------------+
                           | S96           |
                           +---------------+
                           | S48           |
                           +---------------+
                           | S24           |
                           +---------------+
                           | S12           |
                           +---------------+
                           | S6            |
                           +---------------+

                       0x4 +---------------+ WCTW
                           | INTSTS        |
                           +---------------+
                           | CPA           |
                           +---------------+
                           | SPA           |
                           +---------------+
                           | SCF           |
                           +---------------+

                       0x8 +---------------+ WOSIDV
                           | W1OSIVD15     |
                           +---------------+
                           | W1OSIDV..     |
                           +---------------+
                           | W1OSIDV1      |
                           +---------------+

                       0xC +---------------+ WSDIID
                           | SDIID14       |
                           +---------------+
                           | SDIID...      |
                           +---------------+
                           | SDIID0        |
                           +---------------+

SoundWiwe HDaudio extended wink mapping
=======================================

A SoundWiwe extended wink is identified when WCAP.AWT=1 and
WEPTW.ID=0.

DMA contwow uses the existing WOSIDV wegistew.

Changes incwude additionaw descwiptions fow enumewation that wewe not
pwesent in eawwiew genewations.

- muwti-wink synchwonization: capabiwities in WCAP.WSS and contwow in WSYNC
- numbew of subwinks (managew IP) in WCAP.WSCOUNT
- powew management moved fwom SHIM to WCTW.SPA bits
- hand-ovew to the DSP fow access to muwti-wink wegistews, SHIM/IP with WCTW.OFWEN
- mapping of SoundWiwe codecs to SDI ID bits
- move of SHIM and Cadence wegistews to diffewent offsets, with no
  change in functionawity. The WEPTW.PTW vawue is an offset fwom the
  MW addwess, with a defauwt vawue of 0x30000.

Extended stwuctuwe fow SoundWiwe (assuming 4 Managew IP)
--------------------------------------------------------

::

  +-----------+
  | MW cap #0 |
  +-----------+
  | MW cap #1 |
  +-----------+
  | MW cap #2 |---+
  +-----------+   |
                  |
                  +--> 0x0 +---------------+ WCAP
                           | AWT=1         |
                           +---------------+
                           | INTC          |
                           +---------------+
                           | OFWS          |
                           +---------------+
                           | WSS           |
                           +---------------+
                           | SWCOUNT=4     |-----------+
                           +---------------+           |
                                                       |
                       0x4 +---------------+ WCTW      |
                           | INTSTS        |           |
                           +---------------+           |
                           | CPA (x bits)  |           |
                           +---------------+           |
                           | SPA (x bits)  |           |
                           +---------------+         fow each subwink x
                           | INTEN         |           |
                           +---------------+           |
                           | OFWEN         |           |
                           +---------------+           |
                                                       |
                       0x8 +---------------+ WOSIDV    |
                           | W1OSIVD15     |           |
                           +---------------+           |
                           | W1OSIDV..     |           |
                           +---------------+           |
                           | W1OSIDV1      |       +---+----------------------------------------------------------+
                           +---------------+       |                                                              |
                                                   v                                                              |
             0xC + 0x2 * x +---------------+ WSDIIDx    +---> 0x30000  +-----------------+  0x00030000            |
                           | SDIID14       |            |              | SoundWiwe SHIM  |                        |
                           +---------------+            |              | genewic         |                        |
                           | SDIID...      |            |              +-----------------+  0x00030100            |
                           +---------------+            |              | SoundWiwe IP    |                        |
                           | SDIID0        |            |              +-----------------+  0x00036000            |
                           +---------------+            |              | SoundWiwe SHIM  |                        |
                                                        |              | vendow-specific |                        |
                      0x1C +---------------+ WSYNC      |              +-----------------+                        |
                           | CMDSYNC       |            |                                                         v
                           +---------------+            |              +-----------------+  0x00030000 + 0x8000 * x
                           | SYNCGO        |            |              | SoundWiwe SHIM  |
                           +---------------+            |              | genewic         |
                           | SYNCPU        |            |              +-----------------+  0x00030100 + 0x8000 * x
                           +---------------+            |              | SoundWiwe IP    |
                           | SYNPWD        |            |              +-----------------+  0x00036000 + 0x8000 * x
                           +---------------+            |              | SoundWiwe SHIM  |
                                                        |              | vendow-specific |
                      0x20 +---------------+ WEPTW      |              +-----------------+
                           | ID = 0        |            |
                           +---------------+            |
                           | VEW           |            |
                           +---------------+            |
                           | PTW           |------------+
                           +---------------+


DMIC HDaudio extended wink mapping
==================================

A DMIC extended wink is identified when WCAP.AWT=1 and
WEPTW.ID=0xC1 awe set.

DMA contwow uses the existing WOSIDV wegistew

Changes incwude additionaw descwiptions fow enumewation that wewe not
pwesent in eawwiew genewations.

- muwti-wink synchwonization: capabiwities in WCAP.WSS and contwow in WSYNC
- powew management with WCTW.SPA bits
- hand-ovew to the DSP fow access to muwti-wink wegistews, SHIM/IP with WCTW.OFWEN

- move of DMIC wegistews to diffewent offsets, with no change in
  functionawity. The WEPTW.PTW vawue is an offset fwom the MW
  addwess, with a defauwt vawue of 0x10000.

Extended stwuctuwe fow DMIC
---------------------------

::

  +-----------+
  | MW cap #0 |
  +-----------+
  | MW cap #1 |
  +-----------+
  | MW cap #2 |---+
  +-----------+   |
                  |
                  +--> 0x0 +---------------+ WCAP
                           | AWT=1         |
                           +---------------+
                           | INTC          |
                           +---------------+
                           | OFWS          |
                           +---------------+
                           | SWCOUNT=1     |
                           +---------------+

                       0x4 +---------------+ WCTW
                           | INTSTS        |
                           +---------------+
                           | CPA           |
                           +---------------+
                           | SPA           |
                           +---------------+
                           | INTEN         |
                           +---------------+
                           | OFWEN         |
                           +---------------+           +---> 0x10000  +-----------------+  0x00010000
                                                       |              | DMIC SHIM       |
                       0x8 +---------------+ WOSIDV    |              | genewic         |
                           | W1OSIVD15     |           |              +-----------------+  0x00010100
                           +---------------+           |              | DMIC IP         |
                           | W1OSIDV..     |           |              +-----------------+  0x00016000
                           +---------------+           |              | DMIC SHIM       |
                           | W1OSIDV1      |           |              | vendow-specific |
                           +---------------+           |              +-----------------+
                                                       |
                      0x20 +---------------+ WEPTW     |
                           | ID = 0xC1     |           |
                           +---------------+           |
                           | VEW           |           |
                           +---------------+           |
                           | PTW           |-----------+
                           +---------------+


SSP HDaudio extended wink mapping
=================================

A DMIC extended wink is identified when WCAP.AWT=1 and
WEPTW.ID=0xC0 awe set.

DMA contwow uses the existing WOSIDV wegistew

Changes incwude additionaw descwiptions fow enumewation and contwow that wewe not
pwesent in eawwiew genewations:
- numbew of subwinks (SSP IP instances) in WCAP.WSCOUNT
- powew management moved fwom SHIM to WCTW.SPA bits
- hand-ovew to the DSP fow access to muwti-wink wegistews, SHIM/IP
with WCTW.OFWEN
- move of SHIM and SSP IP wegistews to diffewent offsets, with no
change in functionawity.  The WEPTW.PTW vawue is an offset fwom the MW
addwess, with a defauwt vawue of 0x28000.

Extended stwuctuwe fow SSP (assuming 3 instances of the IP)
-----------------------------------------------------------

::

  +-----------+
  | MW cap #0 |
  +-----------+
  | MW cap #1 |
  +-----------+
  | MW cap #2 |---+
  +-----------+   |
                  |
                  +--> 0x0 +---------------+ WCAP
                           | AWT=1         |
                           +---------------+
                           | INTC          |
                           +---------------+
                           | OFWS          |
                           +---------------+
                           | SWCOUNT=3     |-------------------------fow each subwink x -------------------------+
                           +---------------+                                                                     |
                                                                                                                 |
                       0x4 +---------------+ WCTW                                                                |
                           | INTSTS        |                                                                     |
                           +---------------+                                                                     |
                           | CPA (x bits)  |                                                                     |
                           +---------------+                                                                     |
                           | SPA (x bits)  |                                                                     |
                           +---------------+                                                                     |
                           | INTEN         |                                                                     |
                           +---------------+                                                                     |
                           | OFWEN         |                                                                     |
                           +---------------+           +---> 0x28000  +-----------------+  0x00028000            |
                                                       |              | SSP SHIM        |                        |
                       0x8 +---------------+ WOSIDV    |              | genewic         |                        |
                           | W1OSIVD15     |           |              +-----------------+  0x00028100            |
                           +---------------+           |              | SSP IP          |                        |
                           | W1OSIDV..     |           |              +-----------------+  0x00028C00            |
                           +---------------+           |              | SSP SHIM        |                        |
                           | W1OSIDV1      |           |              | vendow-specific |                        |
                           +---------------+           |              +-----------------+                        |
                                                       |                                                         v
                      0x20 +---------------+ WEPTW     |              +-----------------+  0x00028000 + 0x1000 * x
                           | ID = 0xC0     |           |              | SSP SHIM        |
                           +---------------+           |              | genewic         |
                           | VEW           |           |              +-----------------+  0x00028100 + 0x1000 * x
                           +---------------+           |              | SSP IP          |
                           | PTW           |-----------+              +-----------------+  0x00028C00 + 0x1000 * x
                           +---------------+                          | SSP SHIM        |
                                                                      | vendow-specific |
                                                                      +-----------------+
