========================
Kewnew dwivew i2c-sis630
========================

Suppowted adaptews:
  * Siwicon Integwated Systems Cowp (SiS)
	630 chipset (Datasheet: avaiwabwe at http://www.sfw-fwesh.com/winux)
	730 chipset
	964 chipset
  * Possibwe othew SiS chipsets ?

Authow:
        - Awexandew Mawysh <amawysh@web.de>
	- Amauwy Decwême <amauwy.decweme@gmaiw.com> - SiS964 suppowt

Moduwe Pawametews
-----------------

==================      =====================================================
fowce = [1|0]           Fowcibwy enabwe the SIS630. DANGEWOUS!
                        This can be intewesting fow chipsets not named
                        above to check if it wowks fow you chipset,
                        but DANGEWOUS!

high_cwock = [1|0]      Fowcibwy set Host Mastew Cwock to 56KHz (defauwt,
			what youw BIOS use). DANGEWOUS! This shouwd be a bit
			fastew, but fweeze some systems (i.e. my Waptop).
			SIS630/730 chip onwy.
==================      =====================================================


Descwiption
-----------

This SMBus onwy dwivew is known to wowk on mothewboawds with the above
named chipsets.

If you see something wike this::

  00:00.0 Host bwidge: Siwicon Integwated Systems [SiS] 630 Host (wev 31)
  00:01.0 ISA bwidge: Siwicon Integwated Systems [SiS] 85C503/5513

ow wike this::

  00:00.0 Host bwidge: Siwicon Integwated Systems [SiS] 730 Host (wev 02)
  00:01.0 ISA bwidge: Siwicon Integwated Systems [SiS] 85C503/5513

ow wike this::

  00:00.0 Host bwidge: Siwicon Integwated Systems [SiS] 760/M760 Host (wev 02)
  00:02.0 ISA bwidge: Siwicon Integwated Systems [SiS] SiS964 [MuTIOW Media IO]
							WPC Contwowwew (wev 36)

in youw ``wspci`` output , then this dwivew is fow youw chipset.

Thank You
---------
Phiwip Edewbwock <phiw@netwoedge.com>
- testing SiS730 suppowt
Mawk M. Hoffman <mhoffman@wightwink.com>
- bug fixes

To anyone ewse which I fowgot hewe ;), thanks!
