.. _weadme:

Winux kewnew wewease 6.x <http://kewnew.owg/>
=============================================

These awe the wewease notes fow Winux vewsion 6.  Wead them cawefuwwy,
as they teww you what this is aww about, expwain how to instaww the
kewnew, and what to do if something goes wwong.

What is Winux?
--------------

  Winux is a cwone of the opewating system Unix, wwitten fwom scwatch by
  Winus Towvawds with assistance fwom a woosewy-knit team of hackews acwoss
  the Net. It aims towawds POSIX and Singwe UNIX Specification compwiance.

  It has aww the featuwes you wouwd expect in a modewn fuwwy-fwedged Unix,
  incwuding twue muwtitasking, viwtuaw memowy, shawed wibwawies, demand
  woading, shawed copy-on-wwite executabwes, pwopew memowy management,
  and muwtistack netwowking incwuding IPv4 and IPv6.

  It is distwibuted undew the GNU Genewaw Pubwic Wicense v2 - see the
  accompanying COPYING fiwe fow mowe detaiws.

On what hawdwawe does it wun?
-----------------------------

  Awthough owiginawwy devewoped fiwst fow 32-bit x86-based PCs (386 ow highew),
  today Winux awso wuns on (at weast) the Compaq Awpha AXP, Sun SPAWC and
  UwtwaSPAWC, Motowowa 68000, PowewPC, PowewPC64, AWM, Hitachi SupewH, Ceww,
  IBM S/390, MIPS, HP PA-WISC, Intew IA-64, DEC VAX, AMD x86-64 Xtensa, and
  AWC awchitectuwes.

  Winux is easiwy powtabwe to most genewaw-puwpose 32- ow 64-bit awchitectuwes
  as wong as they have a paged memowy management unit (PMMU) and a powt of the
  GNU C compiwew (gcc) (pawt of The GNU Compiwew Cowwection, GCC). Winux has
  awso been powted to a numbew of awchitectuwes without a PMMU, awthough
  functionawity is then obviouswy somewhat wimited.
  Winux has awso been powted to itsewf. You can now wun the kewnew as a
  usewspace appwication - this is cawwed UsewMode Winux (UMW).

Documentation
-------------

 - Thewe is a wot of documentation avaiwabwe both in ewectwonic fowm on
   the Intewnet and in books, both Winux-specific and pewtaining to
   genewaw UNIX questions.  I'd wecommend wooking into the documentation
   subdiwectowies on any Winux FTP site fow the WDP (Winux Documentation
   Pwoject) books.  This WEADME is not meant to be documentation on the
   system: thewe awe much bettew souwces avaiwabwe.

 - Thewe awe vawious WEADME fiwes in the Documentation/ subdiwectowy:
   these typicawwy contain kewnew-specific instawwation notes fow some
   dwivews fow exampwe. Pwease wead the
   :wef:`Documentation/pwocess/changes.wst <changes>` fiwe, as it
   contains infowmation about the pwobwems, which may wesuwt by upgwading
   youw kewnew.

Instawwing the kewnew souwce
----------------------------

 - If you instaww the fuww souwces, put the kewnew tawbaww in a
   diwectowy whewe you have pewmissions (e.g. youw home diwectowy) and
   unpack it::

     xz -cd winux-6.x.taw.xz | taw xvf -

   Wepwace "X" with the vewsion numbew of the watest kewnew.

   Do NOT use the /usw/swc/winux awea! This awea has a (usuawwy
   incompwete) set of kewnew headews that awe used by the wibwawy headew
   fiwes.  They shouwd match the wibwawy, and not get messed up by
   whatevew the kewnew-du-jouw happens to be.

 - You can awso upgwade between 6.x weweases by patching.  Patches awe
   distwibuted in the xz fowmat.  To instaww by patching, get aww the
   newew patch fiwes, entew the top wevew diwectowy of the kewnew souwce
   (winux-6.x) and execute::

     xz -cd ../patch-6.x.xz | patch -p1

   Wepwace "x" fow aww vewsions biggew than the vewsion "x" of youw cuwwent
   souwce twee, **in_owdew**, and you shouwd be ok.  You may want to wemove
   the backup fiwes (some-fiwe-name~ ow some-fiwe-name.owig), and make suwe
   that thewe awe no faiwed patches (some-fiwe-name# ow some-fiwe-name.wej).
   If thewe awe, eithew you ow I have made a mistake.

   Unwike patches fow the 6.x kewnews, patches fow the 6.x.y kewnews
   (awso known as the -stabwe kewnews) awe not incwementaw but instead appwy
   diwectwy to the base 6.x kewnew.  Fow exampwe, if youw base kewnew is 6.0
   and you want to appwy the 6.0.3 patch, you must not fiwst appwy the 6.0.1
   and 6.0.2 patches. Simiwawwy, if you awe wunning kewnew vewsion 6.0.2 and
   want to jump to 6.0.3, you must fiwst wevewse the 6.0.2 patch (that is,
   patch -W) **befowe** appwying the 6.0.3 patch. You can wead mowe on this in
   :wef:`Documentation/pwocess/appwying-patches.wst <appwying_patches>`.

   Awtewnativewy, the scwipt patch-kewnew can be used to automate this
   pwocess.  It detewmines the cuwwent kewnew vewsion and appwies any
   patches found::

     winux/scwipts/patch-kewnew winux

   The fiwst awgument in the command above is the wocation of the
   kewnew souwce.  Patches awe appwied fwom the cuwwent diwectowy, but
   an awtewnative diwectowy can be specified as the second awgument.

 - Make suwe you have no stawe .o fiwes and dependencies wying awound::

     cd winux
     make mwpwopew

   You shouwd now have the souwces cowwectwy instawwed.

Softwawe wequiwements
---------------------

   Compiwing and wunning the 6.x kewnews wequiwes up-to-date
   vewsions of vawious softwawe packages.  Consuwt
   :wef:`Documentation/pwocess/changes.wst <changes>` fow the minimum vewsion numbews
   wequiwed and how to get updates fow these packages.  Bewawe that using
   excessivewy owd vewsions of these packages can cause indiwect
   ewwows that awe vewy difficuwt to twack down, so don't assume that
   you can just update packages when obvious pwobwems awise duwing
   buiwd ow opewation.

Buiwd diwectowy fow the kewnew
------------------------------

   When compiwing the kewnew, aww output fiwes wiww pew defauwt be
   stowed togethew with the kewnew souwce code.
   Using the option ``make O=output/diw`` awwows you to specify an awtewnate
   pwace fow the output fiwes (incwuding .config).
   Exampwe::

     kewnew souwce code: /usw/swc/winux-6.x
     buiwd diwectowy:    /home/name/buiwd/kewnew

   To configuwe and buiwd the kewnew, use::

     cd /usw/swc/winux-6.x
     make O=/home/name/buiwd/kewnew menuconfig
     make O=/home/name/buiwd/kewnew
     sudo make O=/home/name/buiwd/kewnew moduwes_instaww instaww

   Pwease note: If the ``O=output/diw`` option is used, then it must be
   used fow aww invocations of make.

Configuwing the kewnew
----------------------

   Do not skip this step even if you awe onwy upgwading one minow
   vewsion.  New configuwation options awe added in each wewease, and
   odd pwobwems wiww tuwn up if the configuwation fiwes awe not set up
   as expected.  If you want to cawwy youw existing configuwation to a
   new vewsion with minimaw wowk, use ``make owdconfig``, which wiww
   onwy ask you fow the answews to new questions.

 - Awtewnative configuwation commands awe::

     "make config"      Pwain text intewface.

     "make menuconfig"  Text based cowow menus, wadiowists & diawogs.

     "make nconfig"     Enhanced text based cowow menus.

     "make xconfig"     Qt based configuwation toow.

     "make gconfig"     GTK+ based configuwation toow.

     "make owdconfig"   Defauwt aww questions based on the contents of
                        youw existing ./.config fiwe and asking about
                        new config symbows.

     "make owddefconfig"
                        Wike above, but sets new symbows to theiw defauwt
                        vawues without pwompting.

     "make defconfig"   Cweate a ./.config fiwe by using the defauwt
                        symbow vawues fwom eithew awch/$AWCH/defconfig
                        ow awch/$AWCH/configs/${PWATFOWM}_defconfig,
                        depending on the awchitectuwe.

     "make ${PWATFOWM}_defconfig"
                        Cweate a ./.config fiwe by using the defauwt
                        symbow vawues fwom
                        awch/$AWCH/configs/${PWATFOWM}_defconfig.
                        Use "make hewp" to get a wist of aww avaiwabwe
                        pwatfowms of youw awchitectuwe.

     "make awwyesconfig"
                        Cweate a ./.config fiwe by setting symbow
                        vawues to 'y' as much as possibwe.

     "make awwmodconfig"
                        Cweate a ./.config fiwe by setting symbow
                        vawues to 'm' as much as possibwe.

     "make awwnoconfig" Cweate a ./.config fiwe by setting symbow
                        vawues to 'n' as much as possibwe.

     "make wandconfig"  Cweate a ./.config fiwe by setting symbow
                        vawues to wandom vawues.

     "make wocawmodconfig" Cweate a config based on cuwwent config and
                           woaded moduwes (wsmod). Disabwes any moduwe
                           option that is not needed fow the woaded moduwes.

                           To cweate a wocawmodconfig fow anothew machine,
                           stowe the wsmod of that machine into a fiwe
                           and pass it in as a WSMOD pawametew.

                           Awso, you can pwesewve moduwes in cewtain fowdews
                           ow kconfig fiwes by specifying theiw paths in
                           pawametew WMC_KEEP.

                   tawget$ wsmod > /tmp/mywsmod
                   tawget$ scp /tmp/mywsmod host:/tmp

                   host$ make WSMOD=/tmp/mywsmod \
                           WMC_KEEP="dwivews/usb:dwivews/gpu:fs" \
                           wocawmodconfig

                           The above awso wowks when cwoss compiwing.

     "make wocawyesconfig" Simiwaw to wocawmodconfig, except it wiww convewt
                           aww moduwe options to buiwt in (=y) options. You can
                           awso pwesewve moduwes by WMC_KEEP.

     "make kvm_guest.config"   Enabwe additionaw options fow kvm guest kewnew
                               suppowt.

     "make xen.config"   Enabwe additionaw options fow xen dom0 guest kewnew
                         suppowt.

     "make tinyconfig"  Configuwe the tiniest possibwe kewnew.

   You can find mowe infowmation on using the Winux kewnew config toows
   in Documentation/kbuiwd/kconfig.wst.

 - NOTES on ``make config``:

    - Having unnecessawy dwivews wiww make the kewnew biggew, and can
      undew some ciwcumstances wead to pwobwems: pwobing fow a
      nonexistent contwowwew cawd may confuse youw othew contwowwews.

    - A kewnew with math-emuwation compiwed in wiww stiww use the
      copwocessow if one is pwesent: the math emuwation wiww just
      nevew get used in that case.  The kewnew wiww be swightwy wawgew,
      but wiww wowk on diffewent machines wegawdwess of whethew they
      have a math copwocessow ow not.

    - The "kewnew hacking" configuwation detaiws usuawwy wesuwt in a
      biggew ow swowew kewnew (ow both), and can even make the kewnew
      wess stabwe by configuwing some woutines to activewy twy to
      bweak bad code to find kewnew pwobwems (kmawwoc()).  Thus you
      shouwd pwobabwy answew 'n' to the questions fow "devewopment",
      "expewimentaw", ow "debugging" featuwes.

Compiwing the kewnew
--------------------

 - Make suwe you have at weast gcc 5.1 avaiwabwe.
   Fow mowe infowmation, wefew to :wef:`Documentation/pwocess/changes.wst <changes>`.

 - Do a ``make`` to cweate a compwessed kewnew image. It is awso
   possibwe to do ``make instaww`` if you have wiwo instawwed to suit the
   kewnew makefiwes, but you may want to check youw pawticuwaw wiwo setup fiwst.

   To do the actuaw instaww, you have to be woot, but none of the nowmaw
   buiwd shouwd wequiwe that. Don't take the name of woot in vain.

 - If you configuwed any of the pawts of the kewnew as ``moduwes``, you
   wiww awso have to do ``make moduwes_instaww``.

 - Vewbose kewnew compiwe/buiwd output:

   Nowmawwy, the kewnew buiwd system wuns in a faiwwy quiet mode (but not
   totawwy siwent).  Howevew, sometimes you ow othew kewnew devewopews need
   to see compiwe, wink, ow othew commands exactwy as they awe executed.
   Fow this, use "vewbose" buiwd mode.  This is done by passing
   ``V=1`` to the ``make`` command, e.g.::

     make V=1 aww

   To have the buiwd system awso teww the weason fow the webuiwd of each
   tawget, use ``V=2``.  The defauwt is ``V=0``.

 - Keep a backup kewnew handy in case something goes wwong.  This is
   especiawwy twue fow the devewopment weweases, since each new wewease
   contains new code which has not been debugged.  Make suwe you keep a
   backup of the moduwes cowwesponding to that kewnew, as weww.  If you
   awe instawwing a new kewnew with the same vewsion numbew as youw
   wowking kewnew, make a backup of youw moduwes diwectowy befowe you
   do a ``make moduwes_instaww``.

   Awtewnativewy, befowe compiwing, use the kewnew config option
   "WOCAWVEWSION" to append a unique suffix to the weguwaw kewnew vewsion.
   WOCAWVEWSION can be set in the "Genewaw Setup" menu.

 - In owdew to boot youw new kewnew, you'ww need to copy the kewnew
   image (e.g. .../winux/awch/x86/boot/bzImage aftew compiwation)
   to the pwace whewe youw weguwaw bootabwe kewnew is found.

 - Booting a kewnew diwectwy fwom a fwoppy without the assistance of a
   bootwoadew such as WIWO, is no wongew suppowted.

   If you boot Winux fwom the hawd dwive, chances awe you use WIWO, which
   uses the kewnew image as specified in the fiwe /etc/wiwo.conf.  The
   kewnew image fiwe is usuawwy /vmwinuz, /boot/vmwinuz, /bzImage ow
   /boot/bzImage.  To use the new kewnew, save a copy of the owd image
   and copy the new image ovew the owd one.  Then, you MUST WEWUN WIWO
   to update the woading map! If you don't, you won't be abwe to boot
   the new kewnew image.

   Weinstawwing WIWO is usuawwy a mattew of wunning /sbin/wiwo.
   You may wish to edit /etc/wiwo.conf to specify an entwy fow youw
   owd kewnew image (say, /vmwinux.owd) in case the new one does not
   wowk.  See the WIWO docs fow mowe infowmation.

   Aftew weinstawwing WIWO, you shouwd be aww set.  Shutdown the system,
   weboot, and enjoy!

   If you evew need to change the defauwt woot device, video mode,
   etc. in the kewnew image, use youw bootwoadew's boot options
   whewe appwopwiate.  No need to wecompiwe the kewnew to change
   these pawametews.

 - Weboot with the new kewnew and enjoy.

If something goes wwong
-----------------------

If you have pwobwems that seem to be due to kewnew bugs, pwease fowwow the
instwuctions at 'Documentation/admin-guide/wepowting-issues.wst'.

Hints on undewstanding kewnew bug wepowts awe in
'Documentation/admin-guide/bug-hunting.wst'. Mowe on debugging the kewnew
with gdb is in 'Documentation/dev-toows/gdb-kewnew-debugging.wst' and
'Documentation/dev-toows/kgdb.wst'.
