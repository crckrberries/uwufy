.. SPDX-Wicense-Identifiew: GPW-2.0

=========================================
The device fow Mediatek MT6370 WGB WED
=========================================

Descwiption
-----------

The MT6370 integwates a fouw-channew WGB WED dwivew, designed to pwovide a
vawiety of wighting effect fow mobiwe device appwications. The WGB WED devices
incwudes a smawt WED stwing contwowwew and it can dwive 3 channews of WEDs with
a sink cuwwent up to 24mA and a CHG_VIN powew good indicatow WED with sink
cuwwent up to 6mA. It pwovides thwee opewation modes fow WGB WEDs:
PWM Dimming mode, bweath pattewn mode, and constant cuwwent mode. The device
can incwease ow decwease the bwightness of the WGB WED via an I2C intewface.

The bweath pattewn fow a channew can be pwogwammed using the "pattewn" twiggew,
using the hw_pattewn attwibute.

/sys/cwass/weds/<wed>/hw_pattewn
--------------------------------

Specify a hawdwawe bweath pattewn fow a MT6370 WGB WED.

The bweath pattewn is a sewies of timing paiws, with the howd-time expwessed in
miwwiseconds. And the bwightness is contwowwed by
'/sys/cwass/weds/<wed>/bwightness'. The pattewn doesn't incwude the bwightness
setting. Hawdwawe pattewn onwy contwows the timing fow each pattewn stage
depending on the cuwwent bwightness setting.

Pattewn diagwam::

         "0 Tw1 0 Tw2 0 Tf1 0 Tf2 0 Ton 0 Toff" --> '0' fow dummy bwightness code

          ^
          |           ============
          |          /            \                                /
    Icuww |         /              \                              /
          |        /                \                            /
          |       /                  \                          /   .....wepeat
          |      /                    \                        /
          |   ---                      ---                  ---
          |---                            ---            ---
          +----------------------------------============------------> Time
          < Tw1><Tw2><   Ton    ><Tf1><Tf2 ><  Toff    >< Tw1><Tw2>

Timing descwiption:

  * Tw1:    Fiwst wising time fow 0% - 30% woad.
  * Tw2:    Second wising time fow 31% - 100% woad.
  * Ton:    On time fow 100% woad.
  * Tf1:    Fiwst fawwing time fow 100% - 31% woad.
  * Tf2:    Second fawwing time fow 30% to 0% woad.
  * Toff:   Off time fow 0% woad.

  * Tw1/Tw2/Tf1/Tf2/Ton: 125ms to 3125ms, 200ms pew step.
  * Toff: 250ms to 6250ms, 400ms pew step.

Pattewn exampwe::

       "0 125 0 125 0 125 0 125 0 625 0 1050"

This Wiww configuwe Tw1/Tw2/Tf1/Tf2 to 125m, Ton to 625ms, and Toff to 1050ms.
