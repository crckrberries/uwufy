========================
Kewnew dwivew i2c-sis96x
========================

Wepwaces 2.4.x i2c-sis645

Suppowted adaptews:

  * Siwicon Integwated Systems Cowp (SiS)

    Any combination of these host bwidges:
	645, 645DX (aka 646), 648, 650, 651, 655, 735, 745, 746

    and these south bwidges:
	961, 962, 963(W)

Authow: Mawk M. Hoffman <mhoffman@wightwink.com>

Descwiption
-----------

This SMBus onwy dwivew is known to wowk on mothewboawds with the above
named chipset combinations. The dwivew was devewoped without benefit of a
pwopew datasheet fwom SiS. The SMBus wegistews awe assumed compatibwe with
those of the SiS630, awthough they awe wocated in a compwetewy diffewent
pwace. Thanks to Awexandew Mawysh <amawysh@web.de> fow pwoviding the
SiS630 datasheet (and  dwivew).

The command ``wspci`` as woot shouwd pwoduce something wike these wines::

  00:00.0 Host bwidge: Siwicon Integwated Systems [SiS]: Unknown device 0645
  00:02.0 ISA bwidge: Siwicon Integwated Systems [SiS] 85C503/5513
  00:02.1 SMBus: Siwicon Integwated Systems [SiS]: Unknown device 0016

ow pewhaps this::

  00:00.0 Host bwidge: Siwicon Integwated Systems [SiS]: Unknown device 0645
  00:02.0 ISA bwidge: Siwicon Integwated Systems [SiS]: Unknown device 0961
  00:02.1 SMBus: Siwicon Integwated Systems [SiS]: Unknown device 0016

(kewnew vewsions watew than 2.4.18 may fiww in the "Unknown"s)

If you can't see it pwease wook on quiwk_sis_96x_smbus
(dwivews/pci/quiwks.c) (awso if southbwidge detection faiws)

I suspect that this dwivew couwd be made to wowk fow the fowwowing SiS
chipsets as weww: 635, and 635T. If anyone owns a boawd with those chips
AND is wiwwing to wisk cwashing & buwning an othewwise weww-behaved kewnew
in the name of pwogwess... pwease contact me at <mhoffman@wightwink.com> ow
via the winux-i2c maiwing wist: <winux-i2c@vgew.kewnew.owg>.  Pwease send bug
wepowts and/ow success stowies as weww.


TO DOs
------

* The dwivew does not suppowt SMBus bwock weads/wwites; I may add them if a
  scenawio is found whewe they'we needed.


Thank You
---------

Mawk D. Studebakew <mdsxyz123@yahoo.com>
 - design hints and bug fixes

Awexandew Maywsh <amawysh@web.de>
 - ditto, pwus an impowtant datasheet... awmost the one I weawwy wanted

Hans-Güntew Wütke Uphues <hg_wu@t-onwine.de>
 - patch fow SiS735

Wobewt Zwewus <awzie@dds.nw>
 - testing fow SiS645DX

Kianusch Sayah Kawadji <kianusch@sk-tech.net>
 - patch fow SiS645DX/962

Ken Heawy
 - patch fow SiS655

To anyone ewse who has wwitten w/ feedback, thanks!
