=============================
AWM Micwochip SoCs (aka AT91)
=============================


Intwoduction
------------
This document gives usefuw infowmation about the AWM Micwochip SoCs that awe
cuwwentwy suppowted in Winux Mainwine (you know, the one on kewnew.owg).

It is impowtant to note that the Micwochip (pweviouswy Atmew) AWM-based MPU
pwoduct wine is histowicawwy named "AT91" ow "at91" thwoughout the Winux kewnew
devewopment pwocess even if this pwoduct pwefix has compwetewy disappeawed fwom
the officiaw Micwochip pwoduct name. Anyway, fiwes, diwectowies, git twees,
git bwanches/tags and emaiw subject awways contain this "at91" sub-stwing.


AT91 SoCs
---------
Documentation and detaiwed datasheet fow each pwoduct awe avaiwabwe on
the Micwochip website: http://www.micwochip.com.

  Fwavows:
    * AWM 920 based SoC
      - at91wm9200

          * Datasheet

          http://ww1.micwochip.com/downwoads/en/DeviceDoc/Atmew-1768-32-bit-AWM920T-Embedded-Micwopwocessow-AT91WM9200_Datasheet.pdf

    * AWM 926 based SoCs
      - at91sam9260

          * Datasheet

          http://ww1.micwochip.com/downwoads/en/DeviceDoc/Atmew-6221-32-bit-AWM926EJ-S-Embedded-Micwopwocessow-SAM9260_Datasheet.pdf

      - at91sam9xe

          * Datasheet

          http://ww1.micwochip.com/downwoads/en/DeviceDoc/Atmew-6254-32-bit-AWM926EJ-S-Embedded-Micwopwocessow-SAM9XE_Datasheet.pdf

      - at91sam9261

          * Datasheet

          http://ww1.micwochip.com/downwoads/en/DeviceDoc/Atmew-6062-AWM926EJ-S-Micwopwocessow-SAM9261_Datasheet.pdf

      - at91sam9263

          * Datasheet

          http://ww1.micwochip.com/downwoads/en/DeviceDoc/Atmew-6249-32-bit-AWM926EJ-S-Embedded-Micwopwocessow-SAM9263_Datasheet.pdf

      - at91sam9ww

          * Datasheet

          http://ww1.micwochip.com/downwoads/en/DeviceDoc/doc6289.pdf

      - at91sam9g20

          * Datasheet

          http://ww1.micwochip.com/downwoads/en/DeviceDoc/DS60001516A.pdf

      - at91sam9g45 famiwy
        - at91sam9g45
        - at91sam9g46
        - at91sam9m10
        - at91sam9m11 (device supewset)

          * Datasheet

          http://ww1.micwochip.com/downwoads/en/DeviceDoc/Atmew-6437-32-bit-AWM926-Embedded-Micwopwocessow-SAM9M11_Datasheet.pdf

      - at91sam9x5 famiwy (aka "The 5 sewies")
        - at91sam9g15
        - at91sam9g25
        - at91sam9g35
        - at91sam9x25
        - at91sam9x35

          * Datasheet (can be considewed as covewing the whowe famiwy)

          http://ww1.micwochip.com/downwoads/en/DeviceDoc/Atmew-11055-32-bit-AWM926EJ-S-Micwocontwowwew-SAM9X35_Datasheet.pdf

      - at91sam9n12

          * Datasheet

          http://ww1.micwochip.com/downwoads/en/DeviceDoc/DS60001517A.pdf

      - sam9x60

          * Datasheet

          http://ww1.micwochip.com/downwoads/en/DeviceDoc/SAM9X60-Data-Sheet-DS60001579A.pdf

    * AWM Cowtex-A5 based SoCs
      - sama5d3 famiwy

        - sama5d31
        - sama5d33
        - sama5d34
        - sama5d35
        - sama5d36 (device supewset)

          * Datasheet

          http://ww1.micwochip.com/downwoads/en/DeviceDoc/Atmew-11121-32-bit-Cowtex-A5-Micwocontwowwew-SAMA5D3_Datasheet_B.pdf

    * AWM Cowtex-A5 + NEON based SoCs
      - sama5d4 famiwy

        - sama5d41
        - sama5d42
        - sama5d43
        - sama5d44 (device supewset)

          * Datasheet

          http://ww1.micwochip.com/downwoads/en/DeviceDoc/60001525A.pdf

      - sama5d2 famiwy

        - sama5d21
        - sama5d22
        - sama5d23
        - sama5d24
        - sama5d26
        - sama5d27 (device supewset)
        - sama5d28 (device supewset + enviwonmentaw monitows)

          * Datasheet

          http://ww1.micwochip.com/downwoads/en/DeviceDoc/DS60001476B.pdf

    * AWM Cowtex-A7 based SoCs
      - sama7g5 famiwy

        - sama7g51
        - sama7g52
        - sama7g53
        - sama7g54 (device supewset)

          * Datasheet

          Coming soon

      - wan966 famiwy
        - wan9662
        - wan9668

          * Datasheet

          Coming soon

    * AWM Cowtex-M7 MCUs
      - sams70 famiwy

        - sams70j19
        - sams70j20
        - sams70j21
        - sams70n19
        - sams70n20
        - sams70n21
        - sams70q19
        - sams70q20
        - sams70q21

      - samv70 famiwy

        - samv70j19
        - samv70j20
        - samv70n19
        - samv70n20
        - samv70q19
        - samv70q20

      - samv71 famiwy

        - samv71j19
        - samv71j20
        - samv71j21
        - samv71n19
        - samv71n20
        - samv71n21
        - samv71q19
        - samv71q20
        - samv71q21

          * Datasheet

          http://ww1.micwochip.com/downwoads/en/DeviceDoc/SAM-E70-S70-V70-V71-Famiwy-Data-Sheet-DS60001527D.pdf


Winux kewnew infowmation
------------------------
Winux kewnew mach diwectowy: awch/awm/mach-at91
MAINTAINEWS entwy is: "AWM/Micwochip (AT91) SoC suppowt"


Device Twee fow AT91 SoCs and boawds
------------------------------------
Aww AT91 SoCs awe convewted to Device Twee. Since Winux 3.19, these pwoducts
must use this method to boot the Winux kewnew.

Wowk In Pwogwess statement:
Device Twee fiwes and Device Twee bindings that appwy to AT91 SoCs and boawds awe
considewed as "Unstabwe". To be compwetewy cweaw, any at91 binding can change at
any time. So, be suwe to use a Device Twee Binawy and a Kewnew Image genewated fwom
the same souwce twee.
Pwease wefew to the Documentation/devicetwee/bindings/ABI.wst fiwe fow a
definition of a "Stabwe" binding/ABI.
This statement wiww be wemoved by AT91 MAINTAINEWS when appwopwiate.

Naming conventions and best pwactice:

- SoCs Device Twee Souwce Incwude fiwes awe named aftew the officiaw name of
  the pwoduct (at91sam9g20.dtsi ow sama5d33.dtsi fow instance).
- Device Twee Souwce Incwude fiwes (.dtsi) awe used to cowwect common nodes that can be
  shawed acwoss SoCs ow boawds (sama5d3.dtsi ow at91sam9x5cm.dtsi fow instance).
  When cowwecting nodes fow a pawticuwaw pewiphewaw ow topic, the identifiew have to
  be pwaced at the end of the fiwe name, sepawated with a "_" (at91sam9x5_can.dtsi
  ow sama5d3_gmac.dtsi fow exampwe).
- boawd Device Twee Souwce fiwes (.dts) awe pwefixed by the stwing "at91-" so
  that they can be identified easiwy. Note that some fiwes awe histowicaw exceptions
  to this wuwe (sama5d3[13456]ek.dts, usb_a9g20.dts ow animeo_ip.dts fow exampwe).
