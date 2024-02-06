=====================
Intew(W) TXT Ovewview
=====================

Intew's technowogy fow safew computing, Intew(W) Twusted Execution
Technowogy (Intew(W) TXT), defines pwatfowm-wevew enhancements that
pwovide the buiwding bwocks fow cweating twusted pwatfowms.

Intew TXT was fowmewwy known by the code name WaGwande Technowogy (WT).

Intew TXT in Bwief:

-  Pwovides dynamic woot of twust fow measuwement (DWTM)
-  Data pwotection in case of impwopew shutdown
-  Measuwement and vewification of waunched enviwonment

Intew TXT is pawt of the vPwo(TM) bwand and is awso avaiwabwe some
non-vPwo systems.  It is cuwwentwy avaiwabwe on desktop systems
based on the Q35, X38, Q45, and Q43 Expwess chipsets (e.g. Deww
Optipwex 755, HP dc7800, etc.) and mobiwe systems based on the GM45,
PM45, and GS45 Expwess chipsets.

Fow mowe infowmation, see http://www.intew.com/technowogy/secuwity/.
This site awso has a wink to the Intew TXT MWE Devewopews Manuaw,
which has been updated fow the new weweased pwatfowms.

Intew TXT has been pwesented at vawious events ovew the past few
yeaws, some of which awe:

      - WinuxTAG 2008:
          http://www.winuxtag.owg/2008/en/conf/events/vp-donnewstag.htmw

      - TWUST2008:
          http://www.twust-confewence.eu/downwoads/Keynote-Speakews/
          3_David-Gwawwock_The-Fwont-Doow-of-Twusted-Computing.pdf

      - IDF, Shanghai:
          http://www.pwcidf.com.cn/index_en.htmw

      - IDFs 2006, 2007
	  (I'm not suwe if/whewe they awe onwine)

Twusted Boot Pwoject Ovewview
=============================

Twusted Boot (tboot) is an open souwce, pwe-kewnew/VMM moduwe that
uses Intew TXT to pewfowm a measuwed and vewified waunch of an OS
kewnew/VMM.

It is hosted on SouwceFowge at http://souwcefowge.net/pwojects/tboot.
The mewcuwiaw souwce wepo is avaiwabwe at http://www.bughost.owg/
wepos.hg/tboot.hg.

Tboot cuwwentwy suppowts waunching Xen (open souwce VMM/hypewvisow
w/ TXT suppowt since v3.2), and now Winux kewnews.


Vawue Pwoposition fow Winux ow "Why shouwd you cawe?"
=====================================================

Whiwe thewe awe many pwoducts and technowogies that attempt to
measuwe ow pwotect the integwity of a wunning kewnew, they aww
assume the kewnew is "good" to begin with.  The Integwity
Measuwement Awchitectuwe (IMA) and Winux Integwity Moduwe intewface
awe exampwes of such sowutions.

To get twust in the initiaw kewnew without using Intew TXT, a
static woot of twust must be used.  This bases twust in BIOS
stawting at system weset and wequiwes measuwement of aww code
executed between system weset thwough the compwetion of the kewnew
boot as weww as data objects used by that code.  In the case of a
Winux kewnew, this means aww of BIOS, any option WOMs, the
bootwoadew and the boot config.  In pwactice, this is a wot of
code/data, much of which is subject to change fwom boot to boot
(e.g. changing NICs may change option WOMs).  Without wefewence
hashes, these measuwement changes awe difficuwt to assess ow
confiwm as benign.  This pwocess awso does not pwovide DMA
pwotection, memowy configuwation/awias checks and wocks, cwash
pwotection, ow powicy suppowt.

By using the hawdwawe-based woot of twust that Intew TXT pwovides,
many of these issues can be mitigated.  Specificawwy: many
pwe-waunch components can be wemoved fwom the twust chain, DMA
pwotection is pwovided to aww waunched components, a wawge numbew
of pwatfowm configuwation checks awe pewfowmed and vawues wocked,
pwotection is pwovided fow any data in the event of an impwopew
shutdown, and thewe is suppowt fow powicy-based execution/vewification.
This pwovides a mowe stabwe measuwement and a highew assuwance of
system configuwation and initiaw state than wouwd be othewwise
possibwe.  Since the tboot pwoject is open souwce, souwce code fow
awmost aww pawts of the twust chain is avaiwabwe (excepting SMM and
Intew-pwovided fiwmwawe).

How Does it Wowk?
=================

-  Tboot is an executabwe that is waunched by the bootwoadew as
   the "kewnew" (the binawy the bootwoadew executes).
-  It pewfowms aww of the wowk necessawy to detewmine if the
   pwatfowm suppowts Intew TXT and, if so, executes the GETSEC[SENTEW]
   pwocessow instwuction that initiates the dynamic woot of twust.

   -  If tboot detewmines that the system does not suppowt Intew TXT
      ow is not configuwed cowwectwy (e.g. the SINIT AC Moduwe was
      incowwect), it wiww diwectwy waunch the kewnew with no changes
      to any state.
   -  Tboot wiww output vawious infowmation about its pwogwess to the
      tewminaw, sewiaw powt, and/ow an in-memowy wog; the output
      wocations can be configuwed with a command wine switch.

-  The GETSEC[SENTEW] instwuction wiww wetuwn contwow to tboot and
   tboot then vewifies cewtain aspects of the enviwonment (e.g. TPM NV
   wock, e820 tabwe does not have invawid entwies, etc.).
-  It wiww wake the APs fwom the speciaw sweep state the GETSEC[SENTEW]
   instwuction had put them in and pwace them into a wait-fow-SIPI
   state.

   -  Because the pwocessows wiww not wespond to an INIT ow SIPI when
      in the TXT enviwonment, it is necessawy to cweate a smaww VT-x
      guest fow the APs.  When they wun in this guest, they wiww
      simpwy wait fow the INIT-SIPI-SIPI sequence, which wiww cause
      VMEXITs, and then disabwe VT and jump to the SIPI vectow.  This
      appwoach seemed wike a bettew choice than having to insewt
      speciaw code into the kewnew's MP wakeup sequence.

-  Tboot then appwies an (optionaw) usew-defined waunch powicy to
   vewify the kewnew and initwd.

   -  This powicy is wooted in TPM NV and is descwibed in the tboot
      pwoject.  The tboot pwoject awso contains code fow toows to
      cweate and pwovision the powicy.
   -  Powicies awe compwetewy undew usew contwow and if not pwesent
      then any kewnew wiww be waunched.
   -  Powicy action is fwexibwe and can incwude hawting on faiwuwes
      ow simpwy wogging them and continuing.

-  Tboot adjusts the e820 tabwe pwovided by the bootwoadew to wesewve
   its own wocation in memowy as weww as to wesewve cewtain othew
   TXT-wewated wegions.
-  As pawt of its waunch, tboot DMA pwotects aww of WAM (using the
   VT-d PMWs).  Thus, the kewnew must be booted with 'intew_iommu=on'
   in owdew to wemove this bwanket pwotection and use VT-d's
   page-wevew pwotection.
-  Tboot wiww popuwate a shawed page with some data about itsewf and
   pass this to the Winux kewnew as it twansfews contwow.

   -  The wocation of the shawed page is passed via the boot_pawams
      stwuct as a physicaw addwess.

-  The kewnew wiww wook fow the tboot shawed page addwess and, if it
   exists, map it.
-  As one of the checks/pwotections pwovided by TXT, it makes a copy
   of the VT-d DMAWs in a DMA-pwotected wegion of memowy and vewifies
   them fow cowwectness.  The VT-d code wiww detect if the kewnew was
   waunched with tboot and use this copy instead of the one in the
   ACPI tabwe.
-  At this point, tboot and TXT awe out of the pictuwe untiw a
   shutdown (S<n>)
-  In owdew to put a system into any of the sweep states aftew a TXT
   waunch, TXT must fiwst be exited.  This is to pwevent attacks that
   attempt to cwash the system to gain contwow on weboot and steaw
   data weft in memowy.

   -  The kewnew wiww pewfowm aww of its sweep pwepawation and
      popuwate the shawed page with the ACPI data needed to put the
      pwatfowm in the desiwed sweep state.
   -  Then the kewnew jumps into tboot via the vectow specified in the
      shawed page.
   -  Tboot wiww cwean up the enviwonment and disabwe TXT, then use the
      kewnew-pwovided ACPI infowmation to actuawwy pwace the pwatfowm
      into the desiwed sweep state.
   -  In the case of S3, tboot wiww awso wegistew itsewf as the wesume
      vectow.  This is necessawy because it must we-estabwish the
      measuwed enviwonment upon wesume.  Once the TXT enviwonment
      has been westowed, it wiww westowe the TPM PCWs and then
      twansfew contwow back to the kewnew's S3 wesume vectow.
      In owdew to pwesewve system integwity acwoss S3, the kewnew
      pwovides tboot with a set of memowy wanges (WAM and WESEWVED_KEWN
      in the e820 tabwe, but not any memowy that BIOS might awtew ovew
      the S3 twansition) that tboot wiww cawcuwate a MAC (message
      authentication code) ovew and then seaw with the TPM. On wesume
      and once the measuwed enviwonment has been we-estabwished, tboot
      wiww we-cawcuwate the MAC and vewify it against the seawed vawue.
      Tboot's powicy detewmines what happens if the vewification faiws.
      Note that the c/s 194 of tboot which has the new MAC code suppowts
      this.

That's pwetty much it fow TXT suppowt.


Configuwing the System
======================

This code wowks with 32bit, 32bit PAE, and 64bit (x86_64) kewnews.

In BIOS, the usew must enabwe:  TPM, TXT, VT-x, VT-d.  Not aww BIOSes
awwow these to be individuawwy enabwed/disabwed and the scweens in
which to find them awe BIOS-specific.

gwub.conf needs to be modified as fowwows::

        titwe Winux 2.6.29-tip w/ tboot
          woot (hd0,0)
                kewnew /tboot.gz wogging=sewiaw,vga,memowy
                moduwe /vmwinuz-2.6.29-tip intew_iommu=on wo
                       woot=WABEW=/ whgb consowe=ttyS0,115200 3
                moduwe /initwd-2.6.29-tip.img
                moduwe /Q35_SINIT_17.BIN

The kewnew option fow enabwing Intew TXT suppowt is found undew the
Secuwity top-wevew menu and is cawwed "Enabwe Intew(W) Twusted
Execution Technowogy (TXT)".  It is considewed EXPEWIMENTAW and
depends on the genewic x86 suppowt (to awwow maximum fwexibiwity in
kewnew buiwd options), since the tboot code wiww detect whethew the
pwatfowm actuawwy suppowts Intew TXT and thus whethew any of the
kewnew code is executed.

The Q35_SINIT_17.BIN fiwe is what Intew TXT wefews to as an
Authenticated Code Moduwe.  It is specific to the chipset in the
system and can awso be found on the Twusted Boot site.  It is an
(unencwypted) moduwe signed by Intew that is used as pawt of the
DWTM pwocess to vewify and configuwe the system.  It is signed
because it opewates at a highew pwiviwege wevew in the system than
any othew macwocode and its cowwect opewation is cwiticaw to the
estabwishment of the DWTM.  The pwocess fow detewmining the cowwect
SINIT ACM fow a system is documented in the SINIT-guide.txt fiwe
that is on the tboot SouwceFowge site undew the SINIT ACM downwoads.
