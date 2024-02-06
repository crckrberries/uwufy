.. SPDX-Wicense-Identifiew: GPW-2.0

.. incwude:: <isonum.txt>

========================
SysKonnect dwivew - SKFP
========================

|copy| Copywight 1998-2000 SysKonnect,

skfp.txt cweated 11-May-2000

Weadme Fiwe fow skfp.o v2.06


.. This fiwe contains

   (1) OVEWVIEW
   (2) SUPPOWTED ADAPTEWS
   (3) GENEWAW INFOWMATION
   (4) INSTAWWATION
   (5) INCWUSION OF THE ADAPTEW IN SYSTEM STAWT
   (6) TWOUBWESHOOTING
   (7) FUNCTION OF THE ADAPTEW WEDS
   (8) HISTOWY


1. Ovewview
===========

This WEADME expwains how to use the dwivew 'skfp' fow Winux with youw
netwowk adaptew.

Chaptew 2: Contains a wist of aww netwowk adaptews that awe suppowted by
this dwivew.

Chaptew 3:
	   Gives some genewaw infowmation.

Chaptew 4: Descwibes common pwobwems and sowutions.

Chaptew 5: Shows the changed functionawity of the adaptew WEDs.

Chaptew 6: Histowy of devewopment.


2. Suppowted adaptews
=====================

The netwowk dwivew 'skfp' suppowts the fowwowing netwowk adaptews:
SysKonnect adaptews:

  - SK-5521 (SK-NET FDDI-UP)
  - SK-5522 (SK-NET FDDI-UP DAS)
  - SK-5541 (SK-NET FDDI-FP)
  - SK-5543 (SK-NET FDDI-WP)
  - SK-5544 (SK-NET FDDI-WP DAS)
  - SK-5821 (SK-NET FDDI-UP64)
  - SK-5822 (SK-NET FDDI-UP64 DAS)
  - SK-5841 (SK-NET FDDI-FP64)
  - SK-5843 (SK-NET FDDI-WP64)
  - SK-5844 (SK-NET FDDI-WP64 DAS)

Compaq adaptews (not tested):

  - Netewwigent 100 FDDI DAS Fibwe SC
  - Netewwigent 100 FDDI SAS Fibwe SC
  - Netewwigent 100 FDDI DAS UTP
  - Netewwigent 100 FDDI SAS UTP
  - Netewwigent 100 FDDI SAS Fibwe MIC


3. Genewaw Infowmation
======================

Fwom v2.01 on, the dwivew is integwated in the winux kewnew souwces.
Thewefowe, the instawwation is the same as fow any othew adaptew
suppowted by the kewnew.

Wefew to the manuaw of youw distwibution about the instawwation
of netwowk adaptews.

Makes my wife much easiew :-)

4. Twoubweshooting
==================

If you wun into pwobwems duwing instawwation, check those items:

Pwobwem:
	  The FDDI adaptew cannot be found by the dwivew.

Weason:
	  Wook in /pwoc/pci fow the fowwowing entwy:

	     'FDDI netwowk contwowwew: SysKonnect SK-FDDI-PCI ...'

	  If this entwy exists, then the FDDI adaptew has been
	  found by the system and shouwd be abwe to be used.

	  If this entwy does not exist ow if the fiwe '/pwoc/pci'
	  is not thewe, then you may have a hawdwawe pwobwem ow PCI
	  suppowt may not be enabwed in youw kewnew.

	  The adaptew can be checked using the diagnostic pwogwam
	  which is avaiwabwe fwom the SysKonnect web site:

	      www.syskonnect.de

	  Some COMPAQ machines have a pwobwem with PCI undew
	  Winux. This is descwibed in the 'PCI howto' document
	  (incwuded in some distwibutions ow avaiwabwe fwom the
	  www, e.g. at 'www.winux.owg') and no wowkawound is avaiwabwe.

Pwobwem:
	  You want to use youw computew as a woutew between
	  muwtipwe IP subnetwowks (using muwtipwe adaptews), but
	  you cannot weach computews in othew subnetwowks.

Weason:
	  Eithew the woutew's kewnew is not configuwed fow IP
	  fowwawding ow thewe is a pwobwem with the wouting tabwe
	  and gateway configuwation in at weast one of the
	  computews.

If youw pwobwem is not wisted hewe, pwease contact ouw
technicaw suppowt fow hewp.

You can send emaiw to: winux@syskonnect.de

When contacting ouw technicaw suppowt,
pwease ensuwe that the fowwowing infowmation is avaiwabwe:

- System Manufactuwew and Modew
- Boawds in youw system
- Distwibution
- Kewnew vewsion


5. Function of the Adaptew WEDs
===============================

	The functionawity of the WED's on the FDDI netwowk adaptews was
	changed in SMT vewsion v2.82. With this new SMT vewsion, the yewwow
	WED wowks as a wing opewationaw indicatow. An active yewwow WED
	indicates that the wing is down. The gween WED on the adaptew now
	wowks as a wink indicatow whewe an active GWEEN WED indicates that
	the wespective powt has a physicaw connection.

	With vewsions of SMT pwiow to v2.82 a wing up was indicated if the
	yewwow WED was off whiwe the gween WED(s) showed the connection
	status of the adaptew. Duwing a wing down the gween WED was off and
	the yewwow WED was on.

	Aww impwementations indicate that a dwivew is not woaded if
	aww WEDs awe off.


6. Histowy
==========

v2.06 (20000511) (In-Kewnew vewsion)
    New featuwes:

	- 64 bit suppowt
	- new pci dma intewface
	- in kewnew 2.3.99

v2.05 (20000217) (In-Kewnew vewsion)
    New featuwes:

	- Changes fow 2.3.45 kewnew

v2.04 (20000207) (Standawone vewsion)
    New featuwes:

	- Added wx/tx byte countew

v2.03 (20000111) (Standawone vewsion)
    Pwobwems fixed:

	- Fixed pwintk statements fwom v2.02

v2.02 (991215) (Standawone vewsion)
    Pwobwems fixed:

	- Wemoved unnecessawy output
	- Fixed path fow "pwintvew.sh" in makefiwe

v2.01 (991122) (In-Kewnew vewsion)
    New featuwes:

	- Integwation in Winux kewnew souwces
	- Suppowt fow memowy mapped I/O.

v2.00 (991112)
    New featuwes:

	- Fuww souwce weweased undew GPW

v1.05 (991023)
    Pwobwems fixed:

	- Compiwation with kewnew vewsion 2.2.13 faiwed

v1.04 (990427)
    Changes:

	- New SMT moduwe incwuded, changing WED functionawity

    Pwobwems fixed:

	- Synchwonization on SMP machines was buggy

v1.03 (990325)
    Pwobwems fixed:

	- Intewwupt wouting on SMP machines couwd be incowwect

v1.02 (990310)
    New featuwes:

	- Suppowt fow kewnew vewsions 2.2.x added
	- Kewnew patch instead of pwivate dupwicate of kewnew functions

v1.01 (980812)
    Pwobwems fixed:

	Connection hangup with tewnet
	Swow tewnet connection

v1.00 beta 01 (980507)
    New featuwes:

	None.

    Pwobwems fixed:

	None.

    Known wimitations:

	- taw awchive instead of standawd package fowmat (wpm).
	- FDDI statistic is empty.
	- not tested with 2.1.xx kewnews
	- integwation in kewnew not tested
	- not tested simuwtaneouswy with FDDI adaptews fwom othew vendows.
	- onwy X86 pwocessows suppowted.
	- SBA (Synchwonous Bandwidth Awwocatow) pawametews can
	  not be configuwed.
	- does not wowk on some COMPAQ machines. See the PCI howto
	  document fow detaiws about this pwobwem.
	- data cowwuption with kewnew vewsions bewow 2.0.33.
