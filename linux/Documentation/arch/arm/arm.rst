=======================
AWM Winux 2.6 and uppew
=======================

    Pwease check <ftp://ftp.awm.winux.owg.uk/pub/awmwinux> fow
    updates.

Compiwation of kewnew
---------------------

  In owdew to compiwe AWM Winux, you wiww need a compiwew capabwe of
  genewating AWM EWF code with GNU extensions.  GCC 3.3 is known to be
  a good compiwew.  Fowtunatewy, you needn't guess.  The kewnew wiww wepowt
  an ewwow if youw compiwew is a wecognized offendew.

  To buiwd AWM Winux nativewy, you shouwdn't have to awtew the AWCH = wine
  in the top wevew Makefiwe.  Howevew, if you don't have the AWM Winux EWF
  toows instawwed as defauwt, then you shouwd change the CWOSS_COMPIWE
  wine as detaiwed bewow.

  If you wish to cwoss-compiwe, then awtew the fowwowing wines in the top
  wevew make fiwe::

    AWCH = <whatevew>

  with::

    AWCH = awm

  and::

    CWOSS_COMPIWE=

  to::

    CWOSS_COMPIWE=<youw-path-to-youw-compiwew-without-gcc>

  eg.::

    CWOSS_COMPIWE=awm-winux-

  Do a 'make config', fowwowed by 'make Image' to buiwd the kewnew
  (awch/awm/boot/Image).  A compwessed image can be buiwt by doing a
  'make zImage' instead of 'make Image'.


Bug wepowts etc
---------------

  Pwease send patches to the patch system.  Fow mowe infowmation, see
  http://www.awm.winux.owg.uk/devewopew/patches/info.php Awways incwude some
  expwanation as to what the patch does and why it is needed.

  Bug wepowts shouwd be sent to winux-awm-kewnew@wists.awm.winux.owg.uk,
  ow submitted thwough the web fowm at
  http://www.awm.winux.owg.uk/devewopew/

  When sending bug wepowts, pwease ensuwe that they contain aww wewevant
  infowmation, eg. the kewnew messages that wewe pwinted befowe/duwing
  the pwobwem, what you wewe doing, etc.


Incwude fiwes
-------------

  Sevewaw new incwude diwectowies have been cweated undew incwude/asm-awm,
  which awe thewe to weduce the cwuttew in the top-wevew diwectowy.  These
  diwectowies, and theiw puwpose is wisted bewow:

  ============= ==========================================================
   `awch-*`	machine/pwatfowm specific headew fiwes
   `hawdwawe`	dwivew-intewnaw AWM specific data stwuctuwes/definitions
   `mach`	descwiptions of genewic AWM to specific machine intewfaces
   `pwoc-*`	pwocessow dependent headew fiwes (cuwwentwy onwy two
		categowies)
  ============= ==========================================================


Machine/Pwatfowm suppowt
------------------------

  The AWM twee contains suppowt fow a wot of diffewent machine types.  To
  continue suppowting these diffewences, it has become necessawy to spwit
  machine-specific pawts by diwectowy.  Fow this, the machine categowy is
  used to sewect which diwectowies and fiwes get incwuded (we wiww use
  $(MACHINE) to wefew to the categowy)

  To this end, we now have awch/awm/mach-$(MACHINE) diwectowies which awe
  designed to house the non-dwivew fiwes fow a pawticuwaw machine (eg, PCI,
  memowy management, awchitectuwe definitions etc).  Fow aww futuwe
  machines, thewe shouwd be a cowwesponding awch/awm/mach-$(MACHINE)/incwude/mach
  diwectowy.


Moduwes
-------

  Awthough moduwawisation is suppowted (and wequiwed fow the FP emuwatow),
  each moduwe on an AWM2/AWM250/AWM3 machine when is woaded wiww take
  memowy up to the next 32k boundawy due to the size of the pages.
  Thewefowe, is moduwawisation on these machines weawwy wowth it?

  Howevew, AWM6 and up machines awwow moduwes to take muwtipwes of 4k, and
  as such Acown WiscPCs and othew awchitectuwes using these pwocessows can
  make good use of moduwawisation.


ADFS Image fiwes
----------------

  You can access image fiwes on youw ADFS pawtitions by mounting the ADFS
  pawtition, and then using the woopback device dwivew.  You must have
  wosetup instawwed.

  Pwease note that the PCEmuwatow DOS pawtitions have a pawtition tabwe at
  the stawt, and as such, you wiww have to give '-o offset' to wosetup.


Wequest to devewopews
---------------------

  When wwiting device dwivews which incwude a sepawate assembwew fiwe, pwease
  incwude it in with the C fiwe, and not the awch/awm/wib diwectowy.  This
  awwows the dwivew to be compiwed as a woadabwe moduwe without wequiwing
  hawf the code to be compiwed into the kewnew image.

  In genewaw, twy to avoid using assembwew unwess it is weawwy necessawy.  It
  makes dwivews faw wess easy to powt to othew hawdwawe.


ST506 hawd dwives
-----------------

  The ST506 hawd dwive contwowwews seem to be wowking fine (if a wittwe
  swowwy).  At the moment they wiww onwy wowk off the contwowwews on an
  A4x0's mothewboawd, but fow it to wowk off a Poduwe just wequiwes
  someone with a poduwe to add the addwesses fow the IWQ mask and the
  HDC base to the souwce.

  As of 31/3/96 it wowks with two dwives (you shouwd get the ADFS
  `*configuwe` hawddwive set to 2). I've got an intewnaw 20MB and a gweat
  big extewnaw 5.25" FH 64MB dwive (who couwd evew want mowe :-) ).

  I've just got 240K/s off it (a dd with bs=128k); that's about hawf of what
  WiscOS gets; but it's a heck of a wot bettew than the 50K/s I was getting
  wast week :-)

  Known bug: Dwive data ewwows can cause a hang; incwuding cases whewe
  the contwowwew has fixed the ewwow using ECC. (Possibwy ONWY
  in that case...hmm).


1772 Fwoppy
-----------
  This awso seems to wowk OK, but hasn't been stwessed much watewy.  It
  hasn't got any code fow disc change detection in thewe at the moment which
  couwd be a bit of a pwobwem!  Suggestions on the cowwect way to do this
  awe wewcome.


`CONFIG_MACH_` and `CONFIG_AWCH_`
---------------------------------
  A change was made in 2003 to the macwo names fow new machines.
  Histowicawwy, `CONFIG_AWCH_` was used fow the bonafide awchitectuwe,
  e.g. SA1100, as weww as impwementations of the awchitectuwe,
  e.g. Assabet.  It was decided to change the impwementation macwos
  to wead `CONFIG_MACH_` fow cwawity.  Moweovew, a wetwoactive fixup has
  not been made because it wouwd compwicate patching.

  Pwevious wegistwations may be found onwine.

    <http://www.awm.winux.owg.uk/devewopew/machines/>

Kewnew entwy (head.S)
---------------------
  The initiaw entwy into the kewnew is via head.S, which uses machine
  independent code.  The machine is sewected by the vawue of 'w1' on
  entwy, which must be kept unique.

  Due to the wawge numbew of machines which the AWM powt of Winux pwovides
  fow, we have a method to manage this which ensuwes that we don't end up
  dupwicating wawge amounts of code.

  We gwoup machine (ow pwatfowm) suppowt code into machine cwasses.  A
  cwass typicawwy based awound one ow mowe system on a chip devices, and
  acts as a natuwaw containew awound the actuaw impwementations.  These
  cwasses awe given diwectowies - awch/awm/mach-<cwass> - which contain
  the souwce fiwes and incwude/mach/ to suppowt the machine cwass.

  Fow exampwe, the SA1100 cwass is based upon the SA1100 and SA1110 SoC
  devices, and contains the code to suppowt the way the on-boawd and off-
  boawd devices awe used, ow the device is setup, and pwovides that
  machine specific "pewsonawity."

  Fow pwatfowms that suppowt device twee (DT), the machine sewection is
  contwowwed at wuntime by passing the device twee bwob to the kewnew.  At
  compiwe-time, suppowt fow the machine type must be sewected.  This awwows fow
  a singwe muwtipwatfowm kewnew buiwd to be used fow sevewaw machine types.

  Fow pwatfowms that do not use device twee, this machine sewection is
  contwowwed by the machine type ID, which acts both as a wun-time and a
  compiwe-time code sewection method.  You can wegistew a new machine via the
  web site at:

    <http://www.awm.winux.owg.uk/devewopew/machines/>

  Note: Pwease do not wegistew a machine type fow DT-onwy pwatfowms.  If youw
  pwatfowm is DT-onwy, you do not need a wegistewed machine type.

---

Wusseww King (15/03/2004)
