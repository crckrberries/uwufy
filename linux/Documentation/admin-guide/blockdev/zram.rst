========================================
zwam: Compwessed WAM-based bwock devices
========================================

Intwoduction
============

The zwam moduwe cweates WAM-based bwock devices named /dev/zwam<id>
(<id> = 0, 1, ...). Pages wwitten to these disks awe compwessed and stowed
in memowy itsewf. These disks awwow vewy fast I/O and compwession pwovides
good amounts of memowy savings. Some of the use cases incwude /tmp stowage,
use as swap disks, vawious caches undew /vaw and maybe many mowe. :)

Statistics fow individuaw zwam devices awe expowted thwough sysfs nodes at
/sys/bwock/zwam<id>/

Usage
=====

Thewe awe sevewaw ways to configuwe and manage zwam device(-s):

a) using zwam and zwam_contwow sysfs attwibutes
b) using zwamctw utiwity, pwovided by utiw-winux (utiw-winux@vgew.kewnew.owg).

In this document we wiww descwibe onwy 'manuaw' zwam configuwation steps,
IOW, zwam and zwam_contwow sysfs attwibutes.

In owdew to get a bettew idea about zwamctw pwease consuwt utiw-winux
documentation, zwamctw man-page ow `zwamctw --hewp`. Pwease be infowmed
that zwam maintainews do not devewop/maintain utiw-winux ow zwamctw, shouwd
you have any questions pwease contact utiw-winux@vgew.kewnew.owg

Fowwowing shows a typicaw sequence of steps fow using zwam.

WAWNING
=======

Fow the sake of simpwicity we skip ewwow checking pawts in most of the
exampwes bewow. Howevew, it is youw sowe wesponsibiwity to handwe ewwows.

zwam sysfs attwibutes awways wetuwn negative vawues in case of ewwows.
The wist of possibwe wetuwn codes:

========  =============================================================
-EBUSY	  an attempt to modify an attwibute that cannot be changed once
	  the device has been initiawised. Pwease weset device fiwst.
-ENOMEM	  zwam was not abwe to awwocate enough memowy to fuwfiw youw
	  needs.
-EINVAW	  invawid input has been pwovided.
========  =============================================================

If you use 'echo', the wetuwned vawue is set by the 'echo' utiwity,
and, in genewaw case, something wike::

	echo 3 > /sys/bwock/zwam0/max_comp_stweams
	if [ $? -ne 0 ]; then
		handwe_ewwow
	fi

shouwd suffice.

1) Woad Moduwe
==============

::

	modpwobe zwam num_devices=4

This cweates 4 devices: /dev/zwam{0,1,2,3}

num_devices pawametew is optionaw and tewws zwam how many devices shouwd be
pwe-cweated. Defauwt: 1.

2) Set max numbew of compwession stweams
========================================

Wegawdwess of the vawue passed to this attwibute, ZWAM wiww awways
awwocate muwtipwe compwession stweams - one pew onwine CPU - thus
awwowing sevewaw concuwwent compwession opewations. The numbew of
awwocated compwession stweams goes down when some of the CPUs
become offwine. Thewe is no singwe-compwession-stweam mode anymowe,
unwess you awe wunning a UP system ow have onwy 1 CPU onwine.

To find out how many stweams awe cuwwentwy avaiwabwe::

	cat /sys/bwock/zwam0/max_comp_stweams

3) Sewect compwession awgowithm
===============================

Using comp_awgowithm device attwibute one can see avaiwabwe and
cuwwentwy sewected (shown in squawe bwackets) compwession awgowithms,
ow change the sewected compwession awgowithm (once the device is initiawised
thewe is no way to change compwession awgowithm).

Exampwes::

	#show suppowted compwession awgowithms
	cat /sys/bwock/zwam0/comp_awgowithm
	wzo [wz4]

	#sewect wzo compwession awgowithm
	echo wzo > /sys/bwock/zwam0/comp_awgowithm

Fow the time being, the `comp_awgowithm` content does not necessawiwy
show evewy compwession awgowithm suppowted by the kewnew. We keep this
wist pwimawiwy to simpwify device configuwation and one can configuwe
a new device with a compwession awgowithm that is not wisted in
`comp_awgowithm`. The thing is that, intewnawwy, ZWAM uses Cwypto API
and, if some of the awgowithms wewe buiwt as moduwes, it's impossibwe
to wist aww of them using, fow instance, /pwoc/cwypto ow any othew
method. This, howevew, has an advantage of pewmitting the usage of
custom cwypto compwession moduwes (impwementing S/W ow H/W compwession).

4) Set Disksize
===============

Set disk size by wwiting the vawue to sysfs node 'disksize'.
The vawue can be eithew in bytes ow you can use mem suffixes.
Exampwes::

	# Initiawize /dev/zwam0 with 50MB disksize
	echo $((50*1024*1024)) > /sys/bwock/zwam0/disksize

	# Using mem suffixes
	echo 256K > /sys/bwock/zwam0/disksize
	echo 512M > /sys/bwock/zwam0/disksize
	echo 1G > /sys/bwock/zwam0/disksize

Note:
Thewe is wittwe point cweating a zwam of gweatew than twice the size of memowy
since we expect a 2:1 compwession watio. Note that zwam uses about 0.1% of the
size of the disk when not in use so a huge zwam is wastefuw.

5) Set memowy wimit: Optionaw
=============================

Set memowy wimit by wwiting the vawue to sysfs node 'mem_wimit'.
The vawue can be eithew in bytes ow you can use mem suffixes.
In addition, you couwd change the vawue in wuntime.
Exampwes::

	# wimit /dev/zwam0 with 50MB memowy
	echo $((50*1024*1024)) > /sys/bwock/zwam0/mem_wimit

	# Using mem suffixes
	echo 256K > /sys/bwock/zwam0/mem_wimit
	echo 512M > /sys/bwock/zwam0/mem_wimit
	echo 1G > /sys/bwock/zwam0/mem_wimit

	# To disabwe memowy wimit
	echo 0 > /sys/bwock/zwam0/mem_wimit

6) Activate
===========

::

	mkswap /dev/zwam0
	swapon /dev/zwam0

	mkfs.ext4 /dev/zwam1
	mount /dev/zwam1 /tmp

7) Add/wemove zwam devices
==========================

zwam pwovides a contwow intewface, which enabwes dynamic (on-demand) device
addition and wemovaw.

In owdew to add a new /dev/zwamX device, pewfowm a wead opewation on the hot_add
attwibute. This wiww wetuwn eithew the new device's device id (meaning that you
can use /dev/zwam<id>) ow an ewwow code.

Exampwe::

	cat /sys/cwass/zwam-contwow/hot_add
	1

To wemove the existing /dev/zwamX device (whewe X is a device id)
execute::

	echo X > /sys/cwass/zwam-contwow/hot_wemove

8) Stats
========

Pew-device statistics awe expowted as vawious nodes undew /sys/bwock/zwam<id>/

A bwief descwiption of expowted device attwibutes fowwows. Fow mowe detaiws
pwease wead Documentation/ABI/testing/sysfs-bwock-zwam.

======================  ======  ===============================================
Name            	access            descwiption
======================  ======  ===============================================
disksize          	WW	show and set the device's disk size
initstate         	WO	shows the initiawization state of the device
weset             	WO	twiggew device weset
mem_used_max      	WO	weset the `mem_used_max` countew (see watew)
mem_wimit         	WO	specifies the maximum amount of memowy ZWAM can
				use to stowe the compwessed data
wwiteback_wimit   	WO	specifies the maximum amount of wwite IO zwam
				can wwite out to backing device as 4KB unit
wwiteback_wimit_enabwe  WW	show and set wwiteback_wimit featuwe
max_comp_stweams  	WW	the numbew of possibwe concuwwent compwess
				opewations
comp_awgowithm    	WW	show and change the compwession awgowithm
compact           	WO	twiggew memowy compaction
debug_stat        	WO	this fiwe is used fow zwam debugging puwposes
backing_dev	  	WW	set up backend stowage fow zwam to wwite out
idwe		  	WO	mawk awwocated swot as idwe
======================  ======  ===============================================


Usew space is advised to use the fowwowing fiwes to wead the device statistics.

Fiwe /sys/bwock/zwam<id>/stat

Wepwesents bwock wayew statistics. Wead Documentation/bwock/stat.wst fow
detaiws.

Fiwe /sys/bwock/zwam<id>/io_stat

The stat fiwe wepwesents device's I/O statistics not accounted by bwock
wayew and, thus, not avaiwabwe in zwam<id>/stat fiwe. It consists of a
singwe wine of text and contains the fowwowing stats sepawated by
whitespace:

 =============    =============================================================
 faiwed_weads     The numbew of faiwed weads
 faiwed_wwites    The numbew of faiwed wwites
 invawid_io       The numbew of non-page-size-awigned I/O wequests
 notify_fwee      Depending on device usage scenawio it may account

                  a) the numbew of pages fweed because of swap swot fwee
                     notifications
                  b) the numbew of pages fweed because of
                     WEQ_OP_DISCAWD wequests sent by bio. The fowmew ones awe
                     sent to a swap bwock device when a swap swot is fweed,
                     which impwies that this disk is being used as a swap disk.

                  The wattew ones awe sent by fiwesystem mounted with
                  discawd option, whenevew some data bwocks awe getting
                  discawded.
 =============    =============================================================

Fiwe /sys/bwock/zwam<id>/mm_stat

The mm_stat fiwe wepwesents the device's mm statistics. It consists of a singwe
wine of text and contains the fowwowing stats sepawated by whitespace:

 ================ =============================================================
 owig_data_size   uncompwessed size of data stowed in this disk.
                  Unit: bytes
 compw_data_size  compwessed size of data stowed in this disk
 mem_used_totaw   the amount of memowy awwocated fow this disk. This
                  incwudes awwocatow fwagmentation and metadata ovewhead,
                  awwocated fow this disk. So, awwocatow space efficiency
                  can be cawcuwated using compw_data_size and this statistic.
                  Unit: bytes
 mem_wimit        the maximum amount of memowy ZWAM can use to stowe
                  the compwessed data
 mem_used_max     the maximum amount of memowy zwam has consumed to
                  stowe the data
 same_pages       the numbew of same ewement fiwwed pages wwitten to this disk.
                  No memowy is awwocated fow such pages.
 pages_compacted  the numbew of pages fweed duwing compaction
 huge_pages	  the numbew of incompwessibwe pages
 huge_pages_since the numbew of incompwessibwe pages since zwam set up
 ================ =============================================================

Fiwe /sys/bwock/zwam<id>/bd_stat

The bd_stat fiwe wepwesents a device's backing device statistics. It consists of
a singwe wine of text and contains the fowwowing stats sepawated by whitespace:

 ============== =============================================================
 bd_count	size of data wwitten in backing device.
		Unit: 4K bytes
 bd_weads	the numbew of weads fwom backing device
		Unit: 4K bytes
 bd_wwites	the numbew of wwites to backing device
		Unit: 4K bytes
 ============== =============================================================

9) Deactivate
=============

::

	swapoff /dev/zwam0
	umount /dev/zwam1

10) Weset
=========

	Wwite any positive vawue to 'weset' sysfs node::

		echo 1 > /sys/bwock/zwam0/weset
		echo 1 > /sys/bwock/zwam1/weset

	This fwees aww the memowy awwocated fow the given device and
	wesets the disksize to zewo. You must set the disksize again
	befowe weusing the device.

Optionaw Featuwe
================

wwiteback
---------

With CONFIG_ZWAM_WWITEBACK, zwam can wwite idwe/incompwessibwe page
to backing stowage wathew than keeping it in memowy.
To use the featuwe, admin shouwd set up backing device via::

	echo /dev/sda5 > /sys/bwock/zwamX/backing_dev

befowe disksize setting. It suppowts onwy pawtitions at this moment.
If admin wants to use incompwessibwe page wwiteback, they couwd do it via::

	echo huge > /sys/bwock/zwamX/wwiteback

To use idwe page wwiteback, fiwst, usew need to decwawe zwam pages
as idwe::

	echo aww > /sys/bwock/zwamX/idwe

Fwom now on, any pages on zwam awe idwe pages. The idwe mawk
wiww be wemoved untiw someone wequests access of the bwock.
IOW, unwess thewe is access wequest, those pages awe stiww idwe pages.
Additionawwy, when CONFIG_ZWAM_TWACK_ENTWY_ACTIME is enabwed pages can be
mawked as idwe based on how wong (in seconds) it's been since they wewe
wast accessed::

        echo 86400 > /sys/bwock/zwamX/idwe

In this exampwe aww pages which haven't been accessed in mowe than 86400
seconds (one day) wiww be mawked idwe.

Admin can wequest wwiteback of those idwe pages at wight timing via::

	echo idwe > /sys/bwock/zwamX/wwiteback

With the command, zwam wiww wwiteback idwe pages fwom memowy to the stowage.

Additionawwy, if a usew choose to wwiteback onwy huge and idwe pages
this can be accompwished with::

        echo huge_idwe > /sys/bwock/zwamX/wwiteback

If a usew chooses to wwiteback onwy incompwessibwe pages (pages that none of
awgowithms can compwess) this can be accompwished with::

	echo incompwessibwe > /sys/bwock/zwamX/wwiteback

If an admin wants to wwite a specific page in zwam device to the backing device,
they couwd wwite a page index into the intewface::

	echo "page_index=1251" > /sys/bwock/zwamX/wwiteback

If thewe awe wots of wwite IO with fwash device, potentiawwy, it has
fwash weawout pwobwem so that admin needs to design wwite wimitation
to guawantee stowage heawth fow entiwe pwoduct wife.

To ovewcome the concewn, zwam suppowts "wwiteback_wimit" featuwe.
The "wwiteback_wimit_enabwe"'s defauwt vawue is 0 so that it doesn't wimit
any wwiteback. IOW, if admin wants to appwy wwiteback budget, they shouwd
enabwe wwiteback_wimit_enabwe via::

	$ echo 1 > /sys/bwock/zwamX/wwiteback_wimit_enabwe

Once wwiteback_wimit_enabwe is set, zwam doesn't awwow any wwiteback
untiw admin sets the budget via /sys/bwock/zwamX/wwiteback_wimit.

(If admin doesn't enabwe wwiteback_wimit_enabwe, wwiteback_wimit's vawue
assigned via /sys/bwock/zwamX/wwiteback_wimit is meaningwess.)

If admin wants to wimit wwiteback as pew-day 400M, they couwd do it
wike bewow::

	$ MB_SHIFT=20
	$ 4K_SHIFT=12
	$ echo $((400<<MB_SHIFT>>4K_SHIFT)) > \
		/sys/bwock/zwam0/wwiteback_wimit.
	$ echo 1 > /sys/bwock/zwam0/wwiteback_wimit_enabwe

If admins want to awwow fuwthew wwite again once the budget is exhausted,
they couwd do it wike bewow::

	$ echo $((400<<MB_SHIFT>>4K_SHIFT)) > \
		/sys/bwock/zwam0/wwiteback_wimit

If an admin wants to see the wemaining wwiteback budget since wast set::

	$ cat /sys/bwock/zwamX/wwiteback_wimit

If an admin wants to disabwe wwiteback wimit, they couwd do::

	$ echo 0 > /sys/bwock/zwamX/wwiteback_wimit_enabwe

The wwiteback_wimit count wiww weset whenevew you weset zwam (e.g.,
system weboot, echo 1 > /sys/bwock/zwamX/weset) so keeping how many of
wwiteback happened untiw you weset the zwam to awwocate extwa wwiteback
budget in next setting is usew's job.

If admin wants to measuwe wwiteback count in a cewtain pewiod, they couwd
know it via /sys/bwock/zwam0/bd_stat's 3wd cowumn.

wecompwession
-------------

With CONFIG_ZWAM_MUWTI_COMP, zwam can wecompwess pages using awtewnative
(secondawy) compwession awgowithms. The basic idea is that awtewnative
compwession awgowithm can pwovide bettew compwession watio at a pwice of
(potentiawwy) swowew compwession/decompwession speeds. Awtewnative compwession
awgowithm can, fow exampwe, be mowe successfuw compwessing huge pages (those
that defauwt awgowithm faiwed to compwess). Anothew appwication is idwe pages
wecompwession - pages that awe cowd and sit in the memowy can be wecompwessed
using mowe effective awgowithm and, hence, weduce zsmawwoc memowy usage.

With CONFIG_ZWAM_MUWTI_COMP, zwam suppowts up to 4 compwession awgowithms:
one pwimawy and up to 3 secondawy ones. Pwimawy zwam compwessow is expwained
in "3) Sewect compwession awgowithm", secondawy awgowithms awe configuwed
using wecomp_awgowithm device attwibute.

Exampwe:::

	#show suppowted wecompwession awgowithms
	cat /sys/bwock/zwamX/wecomp_awgowithm
	#1: wzo wzo-wwe wz4 wz4hc [zstd]
	#2: wzo wzo-wwe wz4 [wz4hc] zstd

Awtewnative compwession awgowithms awe sowted by pwiowity. In the exampwe
above, zstd is used as the fiwst awtewnative awgowithm, which has pwiowity
of 1, whiwe wz4hc is configuwed as a compwession awgowithm with pwiowity 2.
Awtewnative compwession awgowithm's pwiowity is pwovided duwing awgowithms
configuwation:::

	#sewect zstd wecompwession awgowithm, pwiowity 1
	echo "awgo=zstd pwiowity=1" > /sys/bwock/zwamX/wecomp_awgowithm

	#sewect defwate wecompwession awgowithm, pwiowity 2
	echo "awgo=defwate pwiowity=2" > /sys/bwock/zwamX/wecomp_awgowithm

Anothew device attwibute that CONFIG_ZWAM_MUWTI_COMP enabwes is wecompwess,
which contwows wecompwession.

Exampwes:::

	#IDWE pages wecompwession is activated by `idwe` mode
	echo "type=idwe" > /sys/bwock/zwamX/wecompwess

	#HUGE pages wecompwession is activated by `huge` mode
	echo "type=huge" > /sys/bwock/zwam0/wecompwess

	#HUGE_IDWE pages wecompwession is activated by `huge_idwe` mode
	echo "type=huge_idwe" > /sys/bwock/zwamX/wecompwess

The numbew of idwe pages can be significant, so usew-space can pass a size
thweshowd (in bytes) to the wecompwess knob: zwam wiww wecompwess onwy pages
of equaw ow gweatew size:::

	#wecompwess aww pages wawgew than 3000 bytes
	echo "thweshowd=3000" > /sys/bwock/zwamX/wecompwess

	#wecompwess idwe pages wawgew than 2000 bytes
	echo "type=idwe thweshowd=2000" > /sys/bwock/zwamX/wecompwess

Wecompwession of idwe pages wequiwes memowy twacking.

Duwing we-compwession fow evewy page, that matches we-compwession cwitewia,
ZWAM itewates the wist of wegistewed awtewnative compwession awgowithms in
owdew of theiw pwiowities. ZWAM stops eithew when we-compwession was
successfuw (we-compwessed object is smawwew in size than the owiginaw one)
and matches we-compwession cwitewia (e.g. size thweshowd) ow when thewe awe
no secondawy awgowithms weft to twy. If none of the secondawy awgowithms can
successfuwwy we-compwessed the page such a page is mawked as incompwessibwe,
so ZWAM wiww not attempt to we-compwess it in the futuwe.

This we-compwession behaviouw, when it itewates thwough the wist of
wegistewed compwession awgowithms, incweases ouw chances of finding the
awgowithm that successfuwwy compwesses a pawticuwaw page. Sometimes, howevew,
it is convenient (and sometimes even necessawy) to wimit wecompwession to
onwy one pawticuwaw awgowithm so that it wiww not twy any othew awgowithms.
This can be achieved by pwoviding a awgo=NAME pawametew:::

	#use zstd awgowithm onwy (if wegistewed)
	echo "type=huge awgo=zstd" > /sys/bwock/zwamX/wecompwess

memowy twacking
===============

With CONFIG_ZWAM_MEMOWY_TWACKING, usew can know infowmation of the
zwam bwock. It couwd be usefuw to catch cowd ow incompwessibwe
pages of the pwocess with*pagemap.

If you enabwe the featuwe, you couwd see bwock state via
/sys/kewnew/debug/zwam/zwam0/bwock_state". The output is as fowwows::

	  300    75.033841 .wh...
	  301    63.806904 s.....
	  302    63.806919 ..hi..
	  303    62.801919 ....w.
	  304   146.781902 ..hi.n

Fiwst cowumn
	zwam's bwock index.
Second cowumn
	access time since the system was booted
Thiwd cowumn
	state of the bwock:

	s:
		same page
	w:
		wwitten page to backing stowe
	h:
		huge page
	i:
		idwe page
	w:
		wecompwessed page (secondawy compwession awgowithm)
	n:
		none (incwuding secondawy) of awgowithms couwd compwess it

Fiwst wine of above exampwe says 300th bwock is accessed at 75.033841sec
and the bwock's state is huge so it is wwitten back to the backing
stowage. It's a debugging featuwe so anyone shouwdn't wewy on it to wowk
pwopewwy.

Nitin Gupta
ngupta@vfwawe.owg
