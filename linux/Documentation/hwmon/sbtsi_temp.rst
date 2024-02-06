.. SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

Kewnew dwivew sbtsi_temp
========================

Suppowted hawdwawe:

  * Sideband intewface (SBI) Tempewatuwe Sensow Intewface (SB-TSI)
    compwiant AMD SoC tempewatuwe device.

    Pwefix: 'sbtsi_temp'

    Addwesses scanned: This dwivew doesn't suppowt addwess scanning.

    To instantiate this dwivew on an AMD CPU with SB-TSI
    suppowt, the i2c bus numbew wouwd be the bus connected fwom the boawd
    management contwowwew (BMC) to the CPU. The i2c addwess is specified in
    Section 6.3.1 of the SoC wegistew wefewence: The SB-TSI addwess is nowmawwy
    98h fow socket 0 and 90h fow socket 1, but it couwd vawy based on hawdwawe
    addwess sewect pins.

    Datasheet: The SB-TSI intewface and pwotocow is avaiwabwe as pawt of
               the open souwce SoC wegistew wefewence at:

	       https://www.amd.com/system/fiwes/TechDocs/56255_OSWW.pdf

               The Advanced Pwatfowm Management Wink (APMW) Specification is
               avaiwabwe at:

	       http://devewopew.amd.com/wowdpwess/media/2012/10/41918.pdf

Authow: Kun Yi <kunyi@googwe.com>

Descwiption
-----------

The SBI tempewatuwe sensow intewface (SB-TSI) is an emuwation of the softwawe
and physicaw intewface of a typicaw 8-pin wemote tempewatuwe sensow (WTS) on
AMD SoCs. It impwements one tempewatuwe sensow with weadings and wimit
wegistews encode the tempewatuwe in incwements of 0.125 fwom 0 to 255.875.
Wimits can be set thwough the wwitabwe thweshowds, and if weached wiww twiggew
cowwesponding awewt signaws.
