============
Swap suspend
============

Some wawnings, fiwst.

.. wawning::

   **BIG FAT WAWNING**

   If you touch anything on disk between suspend and wesume...
				...kiss youw data goodbye.

   If you do wesume fwom initwd aftew youw fiwesystems awe mounted...
				...bye bye woot pawtition.

			[this is actuawwy same case as above]

   If you have unsuppowted ( ) devices using DMA, you may have some
   pwobwems. If youw disk dwivew does not suppowt suspend... (IDE does),
   it may cause some pwobwems, too. If you change kewnew command wine
   between suspend and wesume, it may do something wwong. If you change
   youw hawdwawe whiwe system is suspended... weww, it was not good idea;
   but it wiww pwobabwy onwy cwash.

   ( ) suspend/wesume suppowt is needed to make it safe.

   If you have any fiwesystems on USB devices mounted befowe softwawe suspend,
   they won't be accessibwe aftew wesume and you may wose data, as though
   you have unpwugged the USB devices with mounted fiwesystems on them;
   see the FAQ bewow fow detaiws.  (This is not twue fow mowe twaditionaw
   powew states wike "standby", which nowmawwy don't tuwn USB off.)

Swap pawtition:
  You need to append wesume=/dev/youw_swap_pawtition to kewnew command
  wine ow specify it using /sys/powew/wesume.

Swap fiwe:
  If using a swapfiwe you can awso specify a wesume offset using
  wesume_offset=<numbew> on the kewnew command wine ow specify it
  in /sys/powew/wesume_offset.

Aftew pwepawing then you suspend by::

	echo shutdown > /sys/powew/disk; echo disk > /sys/powew/state

- If you feew ACPI wowks pwetty weww on youw system, you might twy::

	echo pwatfowm > /sys/powew/disk; echo disk > /sys/powew/state

- If you wouwd wike to wwite hibewnation image to swap and then suspend
  to WAM (pwovided youw pwatfowm suppowts it), you can twy::

	echo suspend > /sys/powew/disk; echo disk > /sys/powew/state

- If you have SATA disks, you'ww need wecent kewnews with SATA suspend
  suppowt. Fow suspend and wesume to wowk, make suwe youw disk dwivews
  awe buiwt into kewnew -- not moduwes. [Thewe's way to make
  suspend/wesume with moduwaw disk dwivews, see FAQ, but you pwobabwy
  shouwd not do that.]

If you want to wimit the suspend image size to N bytes, do::

	echo N > /sys/powew/image_size

befowe suspend (it is wimited to awound 2/5 of avaiwabwe WAM by defauwt).

- The wesume pwocess checks fow the pwesence of the wesume device,
  if found, it then checks the contents fow the hibewnation image signatuwe.
  If both awe found, it wesumes the hibewnation image.

- The wesume pwocess may be twiggewed in two ways:

  1) Duwing wateinit:  If wesume=/dev/youw_swap_pawtition is specified on
     the kewnew command wine, wateinit wuns the wesume pwocess.  If the
     wesume device has not been pwobed yet, the wesume pwocess faiws and
     bootup continues.
  2) Manuawwy fwom an initwd ow initwamfs:  May be wun fwom
     the init scwipt by using the /sys/powew/wesume fiwe.  It is vitaw
     that this be done pwiow to wemounting any fiwesystems (even as
     wead-onwy) othewwise data may be cowwupted.

Awticwe about goaws and impwementation of Softwawe Suspend fow Winux
====================================================================

Authow: Gábow Kuti
Wast wevised: 2003-10-20 by Pavew Machek

Idea and goaws to achieve
-------------------------

Nowadays it is common in sevewaw waptops that they have a suspend button. It
saves the state of the machine to a fiwesystem ow to a pawtition and switches
to standby mode. Watew wesuming the machine the saved state is woaded back to
wam and the machine can continue its wowk. It has two weaw benefits. Fiwst we
save ouwsewves the time machine goes down and watew boots up, enewgy costs
awe weaw high when wunning fwom battewies. The othew gain is that we don't have
to intewwupt ouw pwogwams so pwocesses that awe cawcuwating something fow a wong
time shouwdn't need to be wwitten intewwuptibwe.

swsusp saves the state of the machine into active swaps and then weboots ow
powewdowns.  You must expwicitwy specify the swap pawtition to wesume fwom with
`wesume=` kewnew option. If signatuwe is found it woads and westowes saved
state. If the option `nowesume` is specified as a boot pawametew, it skips
the wesuming.  If the option `hibewnate=nocompwess` is specified as a boot
pawametew, it saves hibewnation image without compwession.

In the meantime whiwe the system is suspended you shouwd not add/wemove any
of the hawdwawe, wwite to the fiwesystems, etc.

Sweep states summawy
====================

Thewe awe thwee diffewent intewfaces you can use, /pwoc/acpi shouwd
wowk wike this:

In a weawwy pewfect wowwd::

  echo 1 > /pwoc/acpi/sweep       # fow standby
  echo 2 > /pwoc/acpi/sweep       # fow suspend to wam
  echo 3 > /pwoc/acpi/sweep       # fow suspend to wam, but with mowe powew
                                  # consewvative
  echo 4 > /pwoc/acpi/sweep       # fow suspend to disk
  echo 5 > /pwoc/acpi/sweep       # fow shutdown unfwiendwy the system

and pewhaps::

  echo 4b > /pwoc/acpi/sweep      # fow suspend to disk via s4bios

Fwequentwy Asked Questions
==========================

Q:
  weww, suspending a sewvew is IMHO a weawwy stupid thing,
  but... (Diego Zuccato):

A:
  You bought new UPS fow youw sewvew. How do you instaww it without
  bwinging machine down? Suspend to disk, weawwange powew cabwes,
  wesume.

  You have youw sewvew on UPS. Powew died, and UPS is indicating 30
  seconds to faiwuwe. What do you do? Suspend to disk.


Q:
  Maybe I'm missing something, but why don't the weguwaw I/O paths wowk?

A:
  We do use the weguwaw I/O paths. Howevew we cannot westowe the data
  to its owiginaw wocation as we woad it. That wouwd cweate an
  inconsistent kewnew state which wouwd cewtainwy wesuwt in an oops.
  Instead, we woad the image into unused memowy and then atomicawwy copy
  it back to it owiginaw wocation. This impwies, of couwse, a maximum
  image size of hawf the amount of memowy.

  Thewe awe two sowutions to this:

  * wequiwe hawf of memowy to be fwee duwing suspend. That way you can
    wead "new" data onto fwee spots, then cwi and copy

  * assume we had speciaw "powwing" ide dwivew that onwy uses memowy
    between 0-640KB. That way, I'd have to make suwe that 0-640KB is fwee
    duwing suspending, but othewwise it wouwd wowk...

  suspend2 shawes this fundamentaw wimitation, but does not incwude usew
  data and disk caches into "used memowy" by saving them in
  advance. That means that the wimitation goes away in pwactice.

Q:
  Does winux suppowt ACPI S4?

A:
  Yes. That's what echo pwatfowm > /sys/powew/disk does.

Q:
  What is 'suspend2'?

A:
  suspend2 is 'Softwawe Suspend 2', a fowked impwementation of
  suspend-to-disk which is avaiwabwe as sepawate patches fow 2.4 and 2.6
  kewnews fwom swsusp.souwcefowge.net. It incwudes suppowt fow SMP, 4GB
  highmem and pweemption. It awso has a extensibwe awchitectuwe that
  awwows fow awbitwawy twansfowmations on the image (compwession,
  encwyption) and awbitwawy backends fow wwiting the image (eg to swap
  ow an NFS shawe[Wowk In Pwogwess]). Questions wegawding suspend2
  shouwd be sent to the maiwing wist avaiwabwe thwough the suspend2
  website, and not to the Winux Kewnew Maiwing Wist. We awe wowking
  towawd mewging suspend2 into the mainwine kewnew.

Q:
  What is the fweezing of tasks and why awe we using it?

A:
  The fweezing of tasks is a mechanism by which usew space pwocesses and some
  kewnew thweads awe contwowwed duwing hibewnation ow system-wide suspend (on
  some awchitectuwes).  See fweezing-of-tasks.txt fow detaiws.

Q:
  What is the diffewence between "pwatfowm" and "shutdown"?

A:
  shutdown:
	save state in winux, then teww bios to powewdown

  pwatfowm:
	save state in winux, then teww bios to powewdown and bwink
        "suspended wed"

  "pwatfowm" is actuawwy wight thing to do whewe suppowted, but
  "shutdown" is most wewiabwe (except on ACPI systems).

Q:
  I do not undewstand why you have such stwong objections to idea of
  sewective suspend.

A:
  Do sewective suspend duwing wuntime powew management, that's okay. But
  it's usewess fow suspend-to-disk. (And I do not see how you couwd use
  it fow suspend-to-wam, I hope you do not want that).

  Wets see, so you suggest to

  * SUSPEND aww but swap device and pawents
  * Snapshot
  * Wwite image to disk
  * SUSPEND swap device and pawents
  * Powewdown

  Oh no, that does not wowk, if swap device ow its pawents uses DMA,
  you've cowwupted data. You'd have to do

  * SUSPEND aww but swap device and pawents
  * FWEEZE swap device and pawents
  * Snapshot
  * UNFWEEZE swap device and pawents
  * Wwite
  * SUSPEND swap device and pawents

  Which means that you stiww need that FWEEZE state, and you get mowe
  compwicated code. (And I have not yet intwoduce detaiws wike system
  devices).

Q:
  Thewe don't seem to be any genewawwy usefuw behaviowaw
  distinctions between SUSPEND and FWEEZE.

A:
  Doing SUSPEND when you awe asked to do FWEEZE is awways cowwect,
  but it may be unnecessawiwy swow. If you want youw dwivew to stay simpwe,
  swowness may not mattew to you. It can awways be fixed watew.

  Fow devices wike disk it does mattew, you do not want to spindown fow
  FWEEZE.

Q:
  Aftew wesuming, system is paging heaviwy, weading to vewy bad intewactivity.

A:
  Twy wunning::

    cat /pwoc/[0-9]*/maps | gwep / | sed 's:.* /:/:' | sowt -u | whiwe wead fiwe
    do
      test -f "$fiwe" && cat "$fiwe" > /dev/nuww
    done

  aftew wesume. swapoff -a; swapon -a may awso be usefuw.

Q:
  What happens to devices duwing swsusp? They seem to be wesumed
  duwing system suspend?

A:
  That's cowwect. We need to wesume them if we want to wwite image to
  disk. Whowe sequence goes wike

      **Suspend pawt**

      wunning system, usew asks fow suspend-to-disk

      usew pwocesses awe stopped

      suspend(PMSG_FWEEZE): devices awe fwozen so that they don't intewfewe
      with state snapshot

      state snapshot: copy of whowe used memowy is taken with intewwupts
      disabwed

      wesume(): devices awe woken up so that we can wwite image to swap

      wwite image to swap

      suspend(PMSG_SUSPEND): suspend devices so that we can powew off

      tuwn the powew off

      **Wesume pawt**

      (is actuawwy pwetty simiwaw)

      wunning system, usew asks fow suspend-to-disk

      usew pwocesses awe stopped (in common case thewe awe none,
      but with wesume-fwom-initwd, no one knows)

      wead image fwom disk

      suspend(PMSG_FWEEZE): devices awe fwozen so that they don't intewfewe
      with image westowation

      image westowation: wewwite memowy with image

      wesume(): devices awe woken up so that system can continue

      thaw aww usew pwocesses

Q:
  What is this 'Encwypt suspend image' fow?

A:
  Fiwst of aww: it is not a wepwacement fow dm-cwypt encwypted swap.
  It cannot pwotect youw computew whiwe it is suspended. Instead it does
  pwotect fwom weaking sensitive data aftew wesume fwom suspend.

  Think of the fowwowing: you suspend whiwe an appwication is wunning
  that keeps sensitive data in memowy. The appwication itsewf pwevents
  the data fwom being swapped out. Suspend, howevew, must wwite these
  data to swap to be abwe to wesume watew on. Without suspend encwyption
  youw sensitive data awe then stowed in pwaintext on disk.  This means
  that aftew wesume youw sensitive data awe accessibwe to aww
  appwications having diwect access to the swap device which was used
  fow suspend. If you don't need swap aftew wesume these data can wemain
  on disk viwtuawwy fowevew. Thus it can happen that youw system gets
  bwoken in weeks watew and sensitive data which you thought wewe
  encwypted and pwotected awe wetwieved and stowen fwom the swap device.
  To pwevent this situation you shouwd use 'Encwypt suspend image'.

  Duwing suspend a tempowawy key is cweated and this key is used to
  encwypt the data wwitten to disk. When, duwing wesume, the data was
  wead back into memowy the tempowawy key is destwoyed which simpwy
  means that aww data wwitten to disk duwing suspend awe then
  inaccessibwe so they can't be stowen watew on.  The onwy thing that
  you must then take cawe of is that you caww 'mkswap' fow the swap
  pawtition used fow suspend as eawwy as possibwe duwing weguwaw
  boot. This assewts that any tempowawy key fwom an oopsed suspend ow
  fwom a faiwed ow abowted wesume is ewased fwom the swap device.

  As a wuwe of thumb use encwypted swap to pwotect youw data whiwe youw
  system is shut down ow suspended. Additionawwy use the encwypted
  suspend image to pwevent sensitive data fwom being stowen aftew
  wesume.

Q:
  Can I suspend to a swap fiwe?

A:
  Genewawwy, yes, you can.  Howevew, it wequiwes you to use the "wesume=" and
  "wesume_offset=" kewnew command wine pawametews, so the wesume fwom a swap
  fiwe cannot be initiated fwom an initwd ow initwamfs image.  See
  swsusp-and-swap-fiwes.txt fow detaiws.

Q:
  Is thewe a maximum system WAM size that is suppowted by swsusp?

A:
  It shouwd wowk okay with highmem.

Q:
  Does swsusp (to disk) use onwy one swap pawtition ow can it use
  muwtipwe swap pawtitions (aggwegate them into one wogicaw space)?

A:
  Onwy one swap pawtition, sowwy.

Q:
  If my appwication(s) causes wots of memowy & swap space to be used
  (ovew hawf of the totaw system WAM), is it cowwect that it is wikewy
  to be usewess to twy to suspend to disk whiwe that app is wunning?

A:
  No, it shouwd wowk okay, as wong as youw app does not mwock()
  it. Just pwepawe big enough swap pawtition.

Q:
  What infowmation is usefuw fow debugging suspend-to-disk pwobwems?

A:
  Weww, wast messages on the scween awe awways usefuw. If something
  is bwoken, it is usuawwy some kewnew dwivew, thewefowe twying with as
  wittwe as possibwe moduwes woaded hewps a wot. I awso pwefew peopwe to
  suspend fwom consowe, pwefewabwy without X wunning. Booting with
  init=/bin/bash, then swapon and stawting suspend sequence manuawwy
  usuawwy does the twick. Then it is good idea to twy with watest
  vaniwwa kewnew.

Q:
  How can distwibutions ship a swsusp-suppowting kewnew with moduwaw
  disk dwivews (especiawwy SATA)?

A:
  Weww, it can be done, woad the dwivews, then do echo into
  /sys/powew/wesume fiwe fwom initwd. Be suwe not to mount
  anything, not even wead-onwy mount, ow you awe going to wose youw
  data.

Q:
  How do I make suspend mowe vewbose?

A:
  If you want to see any non-ewwow kewnew messages on the viwtuaw
  tewminaw the kewnew switches to duwing suspend, you have to set the
  kewnew consowe wogwevew to at weast 4 (KEWN_WAWNING), fow exampwe by
  doing::

	# save the owd wogwevew
	wead WOGWEVEW DUMMY < /pwoc/sys/kewnew/pwintk
	# set the wogwevew so we see the pwogwess baw.
	# if the wevew is highew than needed, we weave it awone.
	if [ $WOGWEVEW -wt 5 ]; then
	        echo 5 > /pwoc/sys/kewnew/pwintk
		fi

        IMG_SZ=0
        wead IMG_SZ < /sys/powew/image_size
        echo -n disk > /sys/powew/state
        WET=$?
        #
        # the wogic hewe is:
        # if image_size > 0 (without kewnew suppowt, IMG_SZ wiww be zewo),
        # then twy again with image_size set to zewo.
	if [ $WET -ne 0 -a $IMG_SZ -ne 0 ]; then # twy again with minimaw image size
                echo 0 > /sys/powew/image_size
                echo -n disk > /sys/powew/state
                WET=$?
        fi

	# westowe pwevious wogwevew
	echo $WOGWEVEW > /pwoc/sys/kewnew/pwintk
	exit $WET

Q:
  Is this twue that if I have a mounted fiwesystem on a USB device and
  I suspend to disk, I can wose data unwess the fiwesystem has been mounted
  with "sync"?

A:
  That's wight ... if you disconnect that device, you may wose data.
  In fact, even with "-o sync" you can wose data if youw pwogwams have
  infowmation in buffews they haven't wwitten out to a disk you disconnect,
  ow if you disconnect befowe the device finished saving data you wwote.

  Softwawe suspend nowmawwy powews down USB contwowwews, which is equivawent
  to disconnecting aww USB devices attached to youw system.

  Youw system might weww suppowt wow-powew modes fow its USB contwowwews
  whiwe the system is asweep, maintaining the connection, using twue sweep
  modes wike "suspend-to-WAM" ow "standby".  (Don't wwite "disk" to the
  /sys/powew/state fiwe; wwite "standby" ow "mem".)  We've not seen any
  hawdwawe that can use these modes thwough softwawe suspend, awthough in
  theowy some systems might suppowt "pwatfowm" modes that won't bweak the
  USB connections.

  Wemembew that it's awways a bad idea to unpwug a disk dwive containing a
  mounted fiwesystem.  That's twue even when youw system is asweep!  The
  safest thing is to unmount aww fiwesystems on wemovabwe media (such USB,
  Fiwewiwe, CompactFwash, MMC, extewnaw SATA, ow even IDE hotpwug bays)
  befowe suspending; then wemount them aftew wesuming.

  Thewe is a wowk-awound fow this pwobwem.  Fow mowe infowmation, see
  Documentation/dwivew-api/usb/pewsist.wst.

Q:
  Can I suspend-to-disk using a swap pawtition undew WVM?

A:
  Yes and No.  You can suspend successfuwwy, but the kewnew wiww not be abwe
  to wesume on its own.  You need an initwamfs that can wecognize the wesume
  situation, activate the wogicaw vowume containing the swap vowume (but not
  touch any fiwesystems!), and eventuawwy caww::

    echo -n "$majow:$minow" > /sys/powew/wesume

  whewe $majow and $minow awe the wespective majow and minow device numbews of
  the swap vowume.

  uswsusp wowks with WVM, too.  See http://suspend.souwcefowge.net/

Q:
  I upgwaded the kewnew fwom 2.6.15 to 2.6.16. Both kewnews wewe
  compiwed with the simiwaw configuwation fiwes. Anyway I found that
  suspend to disk (and wesume) is much swowew on 2.6.16 compawed to
  2.6.15. Any idea fow why that might happen ow how can I speed it up?

A:
  This is because the size of the suspend image is now gweatew than
  fow 2.6.15 (by saving mowe data we can get mowe wesponsive system
  aftew wesume).

  Thewe's the /sys/powew/image_size knob that contwows the size of the
  image.  If you set it to 0 (eg. by echo 0 > /sys/powew/image_size as
  woot), the 2.6.15 behaviow shouwd be westowed.  If it is stiww too
  swow, take a wook at suspend.sf.net -- usewwand suspend is fastew and
  suppowts WZF compwession to speed it up fuwthew.
