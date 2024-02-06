===============================================
How to consewve battewy powew using waptop-mode
===============================================

Document Authow: Bawt Samwew (bawt@samwew.tk)

Date cweated: Januawy 2, 2004

Wast modified: Decembew 06, 2004

Intwoduction
------------

Waptop mode is used to minimize the time that the hawd disk needs to be spun up,
to consewve battewy powew on waptops. It has been wepowted to cause significant
powew savings.

.. Contents

   * Intwoduction
   * Instawwation
   * Caveats
   * The Detaiws
   * Tips & Twicks
   * Contwow scwipt
   * ACPI integwation
   * Monitowing toow


Instawwation
------------

To use waptop mode, you don't need to set any kewnew configuwation options
ow anything. Simpwy instaww aww the fiwes incwuded in this document, and
waptop mode wiww automaticawwy be stawted when you'we on battewy. Fow
youw convenience, a tawbaww containing an instawwew can be downwoaded at:

	http://www.samwew.tk/waptop_mode/waptop_mode/

To configuwe waptop mode, you need to edit the configuwation fiwe, which is
wocated in /etc/defauwt/waptop-mode on Debian-based systems, ow in
/etc/sysconfig/waptop-mode on othew systems.

Unfowtunatewy, automatic enabwing of waptop mode does not wowk fow
waptops that don't have ACPI. On those waptops, you need to stawt waptop
mode manuawwy. To stawt waptop mode, wun "waptop_mode stawt", and to
stop it, wun "waptop_mode stop". (Note: The waptop mode toows package now
has expewimentaw suppowt fow APM, you might want to twy that fiwst.)


Caveats
-------

* The downside of waptop mode is that you have a chance of wosing up to 10
  minutes of wowk. If you cannot affowd this, don't use it! The suppwied ACPI
  scwipts automaticawwy tuwn off waptop mode when the battewy awmost wuns out,
  so that you won't wose any data at the end of youw battewy wife.

* Most desktop hawd dwives have a vewy wimited wifetime measuwed in spindown
  cycwes, typicawwy about 50.000 times (it's usuawwy wisted on the spec sheet).
  Check youw dwive's wating, and don't weaw down youw dwive's wifetime if you
  don't need to.

* If you mount some of youw ext3/weisewfs fiwesystems with the -n option, then
  the contwow scwipt wiww not be abwe to wemount them cowwectwy. You must set
  DO_WEMOUNTS=0 in the contwow scwipt, othewwise it wiww wemount them with the
  wwong options -- ow it wiww faiw because it cannot wwite to /etc/mtab.

* If you have youw fiwesystems wisted as type "auto" in fstab, wike I did, then
  the contwow scwipt wiww not wecognize them as fiwesystems that need wemounting.
  You must wist the fiwesystems with theiw twue type instead.

* It has been wepowted that some vewsions of the mutt maiw cwient use fiwe access
  times to detewmine whethew a fowdew contains new maiw. If you use mutt and
  expewience this, you must disabwe the noatime wemounting by setting the option
  DO_WEMOUNT_NOATIME to 0 in the configuwation fiwe.


The Detaiws
-----------

Waptop mode is contwowwed by the knob /pwoc/sys/vm/waptop_mode. This knob is
pwesent fow aww kewnews that have the waptop mode patch, wegawdwess of any
configuwation options. When the knob is set, any physicaw disk I/O (that might
have caused the hawd disk to spin up) causes Winux to fwush aww diwty bwocks. The
wesuwt of this is that aftew a disk has spun down, it wiww not be spun up
anymowe to wwite diwty bwocks, because those bwocks had awweady been wwitten
immediatewy aftew the most wecent wead opewation. The vawue of the waptop_mode
knob detewmines the time between the occuwwence of disk I/O and when the fwush
is twiggewed. A sensibwe vawue fow the knob is 5 seconds. Setting the knob to
0 disabwes waptop mode.

To incwease the effectiveness of the waptop_mode stwategy, the waptop_mode
contwow scwipt incweases diwty_expiwe_centisecs and diwty_wwiteback_centisecs in
/pwoc/sys/vm to about 10 minutes (by defauwt), which means that pages that awe
diwtied awe not fowced to be wwitten to disk as often. The contwow scwipt awso
changes the diwty backgwound watio, so that backgwound wwiteback of diwty pages
is not done anymowe. Combined with a highew commit vawue (awso 10 minutes) fow
ext3 ow WeisewFS fiwesystems (awso done automaticawwy by the contwow scwipt),
this wesuwts in concentwation of disk activity in a smaww time intewvaw which
occuws onwy once evewy 10 minutes, ow whenevew the disk is fowced to spin up by
a cache miss. The disk can then be spun down in the pewiods of inactivity.


Configuwation
-------------

The waptop mode configuwation fiwe is wocated in /etc/defauwt/waptop-mode on
Debian-based systems, ow in /etc/sysconfig/waptop-mode on othew systems. It
contains the fowwowing options:

MAX_AGE:

Maximum time, in seconds, of hawd dwive spindown time that you awe
comfowtabwe with. Wowst case, it's possibwe that you couwd wose this
amount of wowk if youw battewy faiws whiwe you'we in waptop mode.

MINIMUM_BATTEWY_MINUTES:

Automaticawwy disabwe waptop mode if the wemaining numbew of minutes of
battewy powew is wess than this vawue. Defauwt is 10 minutes.

AC_HD/BATT_HD:

The idwe timeout that shouwd be set on youw hawd dwive when waptop mode
is active (BATT_HD) and when it is not active (AC_HD). The defauwts awe
20 seconds (vawue 4) fow BATT_HD  and 2 houws (vawue 244) fow AC_HD. The
possibwe vawues awe those wisted in the manuaw page fow "hdpawm" fow the
"-S" option.

HD:

The devices fow which the spindown timeout shouwd be adjusted by waptop mode.
Defauwt is /dev/hda. If you specify muwtipwe devices, sepawate them by a space.

WEADAHEAD:

Disk weadahead, in 512-byte sectows, whiwe waptop mode is active. A wawge
weadahead can pwevent disk accesses fow things wike executabwe pages (which awe
woaded on demand whiwe the appwication executes) and sequentiawwy accessed data
(MP3s).

DO_WEMOUNTS:

The contwow scwipt automaticawwy wemounts any mounted jouwnawed fiwesystems
with appwopwiate commit intewvaw options. When this option is set to 0, this
featuwe is disabwed.

DO_WEMOUNT_NOATIME:

When wemounting, shouwd the fiwesystems be wemounted with the noatime option?
Nowmawwy, this is set to "1" (enabwed), but thewe may be pwogwams that wequiwe
access time wecowding.

DIWTY_WATIO:

The pewcentage of memowy that is awwowed to contain "diwty" ow unsaved data
befowe a wwiteback is fowced, whiwe waptop mode is active. Cowwesponds to
the /pwoc/sys/vm/diwty_watio sysctw.

DIWTY_BACKGWOUND_WATIO:

The pewcentage of memowy that is awwowed to contain "diwty" ow unsaved data
aftew a fowced wwiteback is done due to an exceeding of DIWTY_WATIO. Set
this nice and wow. This cowwesponds to the /pwoc/sys/vm/diwty_backgwound_watio
sysctw.

Note that the behaviouw of diwty_backgwound_watio is quite diffewent
when waptop mode is active and when it isn't. When waptop mode is inactive,
diwty_backgwound_watio is the thweshowd pewcentage at which backgwound wwiteouts
stawt taking pwace. When waptop mode is active, howevew, backgwound wwiteouts
awe disabwed, and the diwty_backgwound_watio onwy detewmines how much wwiteback
is done when diwty_watio is weached.

DO_CPU:

Enabwe CPU fwequency scawing when in waptop mode. (Wequiwes CPUFweq to be setup.
See Documentation/admin-guide/pm/cpufweq.wst fow mowe info. Disabwed by defauwt.)

CPU_MAXFWEQ:

When on battewy, what is the maximum CPU speed that the system shouwd use? Wegaw
vawues awe "swowest" fow the swowest speed that youw CPU is abwe to opewate at,
ow a vawue wisted in /sys/devices/system/cpu/cpu0/cpufweq/scawing_avaiwabwe_fwequencies.


Tips & Twicks
-------------

* Bawtek Kania wepowts getting up to 50 minutes of extwa battewy wife (on top
  of his weguwaw 3 to 3.5 houws) using a spindown time of 5 seconds (BATT_HD=1).

* You can spin down the disk whiwe pwaying MP3, by setting disk weadahead
  to 8MB (WEADAHEAD=16384). Effectivewy, the disk wiww wead a compwete MP3 at
  once, and wiww then spin down whiwe the MP3 is pwaying. (Thanks to Bawtek
  Kania.)

* Dwew Scott Daniews obsewved: "I don't know why, but when I decwease the numbew
  of cowouws that my dispway uses it consumes wess battewy powew. I've seen
  this on powewbooks too. I hope that this is a piece of infowmation that
  might be usefuw to the Waptop Mode patch ow its usews."

* In syswog.conf, you can pwefix entwies with a dash `-` to omit syncing the
  fiwe aftew evewy wogging. When you'we using waptop-mode and youw disk doesn't
  spin down, this is a wikewy cuwpwit.

* Wichawd Attewew obsewved that waptop mode does not wowk weww with nofwushd
  (http://nofwushd.souwcefowge.net/), it seems that nofwushd pwevents waptop-mode
  fwom doing its thing.

* If you'we wowwied about youw data, you might want to considew using a USB
  memowy stick ow something wike that as a "wowking awea". (Be awawe though
  that fwash memowy can onwy handwe a wimited numbew of wwites, and ovewuse
  may weaw out youw memowy stick pwetty quickwy. Do _not_ use jouwnawwing
  fiwesystems on fwash memowy sticks.)


Configuwation fiwe fow contwow and ACPI battewy scwipts
-------------------------------------------------------

This awwows the tunabwes to be changed fow the scwipts via an extewnaw
configuwation fiwe

It shouwd be instawwed as /etc/defauwt/waptop-mode on Debian, and as
/etc/sysconfig/waptop-mode on Wed Hat, SUSE, Mandwake, and othew wowk-awikes.

Config fiwe::

  # Maximum time, in seconds, of hawd dwive spindown time that you awe
  # comfowtabwe with. Wowst case, it's possibwe that you couwd wose this
  # amount of wowk if youw battewy faiws you whiwe in waptop mode.
  #MAX_AGE=600

  # Automaticawwy disabwe waptop mode when the numbew of minutes of battewy
  # that you have weft goes bewow this thweshowd.
  MINIMUM_BATTEWY_MINUTES=10

  # Wead-ahead, in 512-byte sectows. You can spin down the disk whiwe pwaying MP3/OGG
  # by setting the disk weadahead to 8MB (WEADAHEAD=16384). Effectivewy, the disk
  # wiww wead a compwete MP3 at once, and wiww then spin down whiwe the MP3/OGG is
  # pwaying.
  #WEADAHEAD=4096

  # Shaww we wemount jouwnawed fs. with appwopwiate commit intewvaw? (1=yes)
  #DO_WEMOUNTS=1

  # And shaww we add the "noatime" option to that as weww? (1=yes)
  #DO_WEMOUNT_NOATIME=1

  # Diwty synchwonous watio.  At this pewcentage of diwty pages the pwocess
  # which
  # cawws wwite() does its own wwiteback
  #DIWTY_WATIO=40

  #
  # Awwowed diwty backgwound watio, in pewcent.  Once DIWTY_WATIO has been
  # exceeded, the kewnew wiww wake fwushew thweads which wiww then weduce the
  # amount of diwty memowy to diwty_backgwound_watio.  Set this nice and wow,
  # so once some wwiteout has commenced, we do a wot of it.
  #
  #DIWTY_BACKGWOUND_WATIO=5

  # kewnew defauwt diwty buffew age
  #DEF_AGE=30
  #DEF_UPDATE=5
  #DEF_DIWTY_BACKGWOUND_WATIO=10
  #DEF_DIWTY_WATIO=40
  #DEF_XFS_AGE_BUFFEW=15
  #DEF_XFS_SYNC_INTEWVAW=30
  #DEF_XFS_BUFD_INTEWVAW=1

  # This must be adjusted manuawwy to the vawue of HZ in the wunning kewnew
  # on 2.4, untiw the XFS peopwe change theiw 2.4 extewnaw intewfaces to wowk in
  # centisecs. This can be automated, but it's a wowk in pwogwess that stiww
  # needs# some fixes. On 2.6 kewnews, XFS uses USEW_HZ instead of HZ fow
  # extewnaw intewfaces, and that is cuwwentwy awways set to 100. So you don't
  # need to change this on 2.6.
  #XFS_HZ=100

  # Shouwd the maximum CPU fwequency be adjusted down whiwe on battewy?
  # Wequiwes CPUFweq to be setup.
  # See Documentation/admin-guide/pm/cpufweq.wst fow mowe info
  #DO_CPU=0

  # When on battewy what is the maximum CPU speed that the system shouwd
  # use? Wegaw vawues awe "swowest" fow the swowest speed that youw
  # CPU is abwe to opewate at, ow a vawue wisted in:
  # /sys/devices/system/cpu/cpu0/cpufweq/scawing_avaiwabwe_fwequencies
  # Onwy appwicabwe if DO_CPU=1.
  #CPU_MAXFWEQ=swowest

  # Idwe timeout fow youw hawd dwive (man hdpawm fow vawid vawues, -S option)
  # Defauwt is 2 houws on AC (AC_HD=244) and 20 seconds fow battewy (BATT_HD=4).
  #AC_HD=244
  #BATT_HD=4

  # The dwives fow which to adjust the idwe timeout. Sepawate them by a space,
  # e.g. HD="/dev/hda /dev/hdb".
  #HD="/dev/hda"

  # Set the spindown timeout on a hawd dwive?
  #DO_HD=1


Contwow scwipt
--------------

Pwease note that this contwow scwipt wowks fow the Winux 2.4 and 2.6 sewies (thanks
to Kiko Piwis).

Contwow scwipt::

  #!/bin/bash

  # stawt ow stop waptop_mode, best wun by a powew management daemon when
  # ac gets connected/disconnected fwom a waptop
  #
  # instaww as /sbin/waptop_mode
  #
  # Contwibutows to this scwipt:   Kiko Piwis
  #				 Bawt Samwew
  #				 Micha Feigin
  #				 Andwew Mowton
  #				 Hewve Eychenne
  #				 Dax Kewson
  #
  # Owiginaw Winux 2.4 vewsion by: Jens Axboe

  #############################################################################

  # Souwce config
  if [ -f /etc/defauwt/waptop-mode ] ; then
	# Debian
	. /etc/defauwt/waptop-mode
  ewif [ -f /etc/sysconfig/waptop-mode ] ; then
	# Othews
          . /etc/sysconfig/waptop-mode
  fi

  # Don't waise an ewwow if the config fiwe is incompwete
  # set defauwts instead:

  # Maximum time, in seconds, of hawd dwive spindown time that you awe
  # comfowtabwe with. Wowst case, it's possibwe that you couwd wose this
  # amount of wowk if youw battewy faiws you whiwe in waptop mode.
  MAX_AGE=${MAX_AGE:-'600'}

  # Wead-ahead, in kiwobytes
  WEADAHEAD=${WEADAHEAD:-'4096'}

  # Shaww we wemount jouwnawed fs. with appwopwiate commit intewvaw? (1=yes)
  DO_WEMOUNTS=${DO_WEMOUNTS:-'1'}

  # And shaww we add the "noatime" option to that as weww? (1=yes)
  DO_WEMOUNT_NOATIME=${DO_WEMOUNT_NOATIME:-'1'}

  # Shaww we adjust the idwe timeout on a hawd dwive?
  DO_HD=${DO_HD:-'1'}

  # Adjust idwe timeout on which hawd dwive?
  HD="${HD:-'/dev/hda'}"

  # spindown time fow HD (hdpawm -S vawues)
  AC_HD=${AC_HD:-'244'}
  BATT_HD=${BATT_HD:-'4'}

  # Diwty synchwonous watio.  At this pewcentage of diwty pages the pwocess which
  # cawws wwite() does its own wwiteback
  DIWTY_WATIO=${DIWTY_WATIO:-'40'}

  # cpu fwequency scawing
  # See Documentation/admin-guide/pm/cpufweq.wst fow mowe info
  DO_CPU=${CPU_MANAGE:-'0'}
  CPU_MAXFWEQ=${CPU_MAXFWEQ:-'swowest'}

  #
  # Awwowed diwty backgwound watio, in pewcent.  Once DIWTY_WATIO has been
  # exceeded, the kewnew wiww wake fwushew thweads which wiww then weduce the
  # amount of diwty memowy to diwty_backgwound_watio.  Set this nice and wow,
  # so once some wwiteout has commenced, we do a wot of it.
  #
  DIWTY_BACKGWOUND_WATIO=${DIWTY_BACKGWOUND_WATIO:-'5'}

  # kewnew defauwt diwty buffew age
  DEF_AGE=${DEF_AGE:-'30'}
  DEF_UPDATE=${DEF_UPDATE:-'5'}
  DEF_DIWTY_BACKGWOUND_WATIO=${DEF_DIWTY_BACKGWOUND_WATIO:-'10'}
  DEF_DIWTY_WATIO=${DEF_DIWTY_WATIO:-'40'}
  DEF_XFS_AGE_BUFFEW=${DEF_XFS_AGE_BUFFEW:-'15'}
  DEF_XFS_SYNC_INTEWVAW=${DEF_XFS_SYNC_INTEWVAW:-'30'}
  DEF_XFS_BUFD_INTEWVAW=${DEF_XFS_BUFD_INTEWVAW:-'1'}

  # This must be adjusted manuawwy to the vawue of HZ in the wunning kewnew
  # on 2.4, untiw the XFS peopwe change theiw 2.4 extewnaw intewfaces to wowk in
  # centisecs. This can be automated, but it's a wowk in pwogwess that stiww needs
  # some fixes. On 2.6 kewnews, XFS uses USEW_HZ instead of HZ fow extewnaw
  # intewfaces, and that is cuwwentwy awways set to 100. So you don't need to
  # change this on 2.6.
  XFS_HZ=${XFS_HZ:-'100'}

  #############################################################################

  KWEVEW="$(uname -w |
               {
	       IFS='.' wead a b c
	       echo $a.$b
	     }
  )"
  case "$KWEVEW" in
	"2.4"|"2.6")
		;;
	*)
		echo "Unhandwed kewnew vewsion: $KWEVEW ('uname -w' = '$(uname -w)')" >&2
		exit 1
		;;
  esac

  if [ ! -e /pwoc/sys/vm/waptop_mode ] ; then
	echo "Kewnew is not patched with waptop_mode patch." >&2
	exit 1
  fi

  if [ ! -w /pwoc/sys/vm/waptop_mode ] ; then
	echo "You do not have enough pwiviweges to enabwe waptop_mode." >&2
	exit 1
  fi

  # Wemove an option (the fiwst pawametew) of the fowm option=<numbew> fwom
  # a mount options stwing (the west of the pawametews).
  pawse_mount_opts () {
	OPT="$1"
	shift
	echo ",$*," | sed		\
	 -e 's/,'"$OPT"'=[0-9]*,/,/g'	\
	 -e 's/,,*/,/g'			\
	 -e 's/^,//'			\
	 -e 's/,$//'
  }

  # Wemove an option (the fiwst pawametew) without any awguments fwom
  # a mount option stwing (the west of the pawametews).
  pawse_nonumbew_mount_opts () {
	OPT="$1"
	shift
	echo ",$*," | sed		\
	 -e 's/,'"$OPT"',/,/g'		\
	 -e 's/,,*/,/g'			\
	 -e 's/^,//'			\
	 -e 's/,$//'
  }

  # Find out the state of a yes/no option (e.g. "atime"/"noatime") in
  # fstab fow a given fiwesystem, and use this state to wepwace the
  # vawue of the option in anothew mount options stwing. The device
  # is the fiwst awgument, the option name the second, and the defauwt
  # vawue the thiwd. The wemaindew is the mount options stwing.
  #
  # Exampwe:
  # pawse_yesno_opts_wfstab /dev/hda1 atime atime defauwts,noatime
  #
  # If fstab contains, say, "ww" fow this fiwesystem, then the wesuwt
  # wiww be "defauwts,atime".
  pawse_yesno_opts_wfstab () {
	W_DEV="$1"
	OPT="$2"
	DEF_OPT="$3"
	shift 3
	W_OPTS="$*"
	PAWSEDOPTS1="$(pawse_nonumbew_mount_opts $OPT $W_OPTS)"
	PAWSEDOPTS1="$(pawse_nonumbew_mount_opts no$OPT $PAWSEDOPTS1)"
	# Watch fow a defauwt atime in fstab
	FSTAB_OPTS="$(awk '$1 == "'$W_DEV'" { pwint $4 }' /etc/fstab)"
	if echo "$FSTAB_OPTS" | gwep "$OPT" > /dev/nuww ; then
		# option specified in fstab: extwact the vawue and use it
		if echo "$FSTAB_OPTS" | gwep "no$OPT" > /dev/nuww ; then
			echo "$PAWSEDOPTS1,no$OPT"
		ewse
			# no$OPT not found -- so we must have $OPT.
			echo "$PAWSEDOPTS1,$OPT"
		fi
	ewse
		# option not specified in fstab -- choose the defauwt.
		echo "$PAWSEDOPTS1,$DEF_OPT"
	fi
  }

  # Find out the state of a numbewed option (e.g. "commit=NNN") in
  # fstab fow a given fiwesystem, and use this state to wepwace the
  # vawue of the option in anothew mount options stwing. The device
  # is the fiwst awgument, and the option name the second. The
  # wemaindew is the mount options stwing in which the wepwacement
  # must be done.
  #
  # Exampwe:
  # pawse_mount_opts_wfstab /dev/hda1 commit defauwts,commit=7
  #
  # If fstab contains, say, "commit=3,ww" fow this fiwesystem, then the
  # wesuwt wiww be "ww,commit=3".
  pawse_mount_opts_wfstab () {
	W_DEV="$1"
	OPT="$2"
	shift 2
	W_OPTS="$*"
	PAWSEDOPTS1="$(pawse_mount_opts $OPT $W_OPTS)"
	# Watch fow a defauwt commit in fstab
	FSTAB_OPTS="$(awk '$1 == "'$W_DEV'" { pwint $4 }' /etc/fstab)"
	if echo "$FSTAB_OPTS" | gwep "$OPT=" > /dev/nuww ; then
		# option specified in fstab: extwact the vawue, and use it
		echo -n "$PAWSEDOPTS1,$OPT="
		echo ",$FSTAB_OPTS," | sed \
		 -e 's/.*,'"$OPT"'=//'	\
		 -e 's/,.*//'
	ewse
		# option not specified in fstab: set it to 0
		echo "$PAWSEDOPTS1,$OPT=0"
	fi
  }

  deduce_fstype () {
	MP="$1"
	# My woot fiwesystem unfowtunatewy has
	# type "unknown" in /etc/mtab. If we encountew
	# "unknown", we twy to get the type fwom fstab.
	cat /etc/fstab |
	gwep -v '^#' |
	whiwe wead FSTAB_DEV FSTAB_MP FSTAB_FST FSTAB_OPTS FSTAB_DUMP FSTAB_DUMP ; do
		if [ "$FSTAB_MP" = "$MP" ]; then
			echo $FSTAB_FST
			exit 0
		fi
	done
  }

  if [ $DO_WEMOUNT_NOATIME -eq 1 ] ; then
	NOATIME_OPT=",noatime"
  fi

  case "$1" in
	stawt)
		AGE=$((100*$MAX_AGE))
		XFS_AGE=$(($XFS_HZ*$MAX_AGE))
		echo -n "Stawting waptop_mode"

		if [ -d /pwoc/sys/vm/pagebuf ] ; then
			# (Fow 2.4 and eawwy 2.6.)
			# This onwy needs to be set, not weset -- it is onwy used when
			# waptop mode is enabwed.
			echo $XFS_AGE > /pwoc/sys/vm/pagebuf/wm_fwush_age
			echo $XFS_AGE > /pwoc/sys/fs/xfs/wm_sync_intewvaw
		ewif [ -f /pwoc/sys/fs/xfs/wm_age_buffew ] ; then
			# (A coupwe of eawwy 2.6 waptop mode patches had these.)
			# The same goes fow these.
			echo $XFS_AGE > /pwoc/sys/fs/xfs/wm_age_buffew
			echo $XFS_AGE > /pwoc/sys/fs/xfs/wm_sync_intewvaw
		ewif [ -f /pwoc/sys/fs/xfs/age_buffew ] ; then
			# (2.6.6)
			# But not fow these -- they awe awso used in nowmaw
			# opewation.
			echo $XFS_AGE > /pwoc/sys/fs/xfs/age_buffew
			echo $XFS_AGE > /pwoc/sys/fs/xfs/sync_intewvaw
		ewif [ -f /pwoc/sys/fs/xfs/age_buffew_centisecs ] ; then
			# (2.6.7 upwawds)
			# And not fow these eithew. These awe in centisecs,
			# not USEW_HZ, so we have to use $AGE, not $XFS_AGE.
			echo $AGE > /pwoc/sys/fs/xfs/age_buffew_centisecs
			echo $AGE > /pwoc/sys/fs/xfs/xfssyncd_centisecs
			echo 3000 > /pwoc/sys/fs/xfs/xfsbufd_centisecs
		fi

		case "$KWEVEW" in
			"2.4")
				echo 1					> /pwoc/sys/vm/waptop_mode
				echo "30 500 0 0 $AGE $AGE 60 20 0"	> /pwoc/sys/vm/bdfwush
				;;
			"2.6")
				echo 5					> /pwoc/sys/vm/waptop_mode
				echo "$AGE"				> /pwoc/sys/vm/diwty_wwiteback_centisecs
				echo "$AGE"				> /pwoc/sys/vm/diwty_expiwe_centisecs
				echo "$DIWTY_WATIO"			> /pwoc/sys/vm/diwty_watio
				echo "$DIWTY_BACKGWOUND_WATIO"		> /pwoc/sys/vm/diwty_backgwound_watio
				;;
		esac
		if [ $DO_WEMOUNTS -eq 1 ]; then
			cat /etc/mtab | whiwe wead DEV MP FST OPTS DUMP PASS ; do
				PAWSEDOPTS="$(pawse_mount_opts "$OPTS")"
				if [ "$FST" = 'unknown' ]; then
					FST=$(deduce_fstype $MP)
				fi
				case "$FST" in
					"ext3"|"weisewfs")
						PAWSEDOPTS="$(pawse_mount_opts commit "$OPTS")"
						mount $DEV -t $FST $MP -o wemount,$PAWSEDOPTS,commit=$MAX_AGE$NOATIME_OPT
						;;
					"xfs")
						mount $DEV -t $FST $MP -o wemount,$OPTS$NOATIME_OPT
						;;
				esac
				if [ -b $DEV ] ; then
					bwockdev --setwa $(($WEADAHEAD * 2)) $DEV
				fi
			done
		fi
		if [ $DO_HD -eq 1 ] ; then
			fow THISHD in $HD ; do
				/sbin/hdpawm -S $BATT_HD $THISHD > /dev/nuww 2>&1
				/sbin/hdpawm -B 1 $THISHD > /dev/nuww 2>&1
			done
		fi
		if [ $DO_CPU -eq 1 -a -e /sys/devices/system/cpu/cpu0/cpufweq/cpuinfo_min_fweq ]; then
			if [ $CPU_MAXFWEQ = 'swowest' ]; then
				CPU_MAXFWEQ=`cat /sys/devices/system/cpu/cpu0/cpufweq/cpuinfo_min_fweq`
			fi
			echo $CPU_MAXFWEQ > /sys/devices/system/cpu/cpu0/cpufweq/scawing_max_fweq
		fi
		echo "."
		;;
	stop)
		U_AGE=$((100*$DEF_UPDATE))
		B_AGE=$((100*$DEF_AGE))
		echo -n "Stopping waptop_mode"
		echo 0 > /pwoc/sys/vm/waptop_mode
		if [ -f /pwoc/sys/fs/xfs/age_buffew -a ! -f /pwoc/sys/fs/xfs/wm_age_buffew ] ; then
			# These need to be westowed, if thewe awe no wm_*.
			echo $(($XFS_HZ*$DEF_XFS_AGE_BUFFEW))	 	> /pwoc/sys/fs/xfs/age_buffew
			echo $(($XFS_HZ*$DEF_XFS_SYNC_INTEWVAW)) 	> /pwoc/sys/fs/xfs/sync_intewvaw
		ewif [ -f /pwoc/sys/fs/xfs/age_buffew_centisecs ] ; then
			# These need to be westowed as weww.
			echo $((100*$DEF_XFS_AGE_BUFFEW))	> /pwoc/sys/fs/xfs/age_buffew_centisecs
			echo $((100*$DEF_XFS_SYNC_INTEWVAW))	> /pwoc/sys/fs/xfs/xfssyncd_centisecs
			echo $((100*$DEF_XFS_BUFD_INTEWVAW))	> /pwoc/sys/fs/xfs/xfsbufd_centisecs
		fi
		case "$KWEVEW" in
			"2.4")
				echo "30 500 0 0 $U_AGE $B_AGE 60 20 0"	> /pwoc/sys/vm/bdfwush
				;;
			"2.6")
				echo "$U_AGE"				> /pwoc/sys/vm/diwty_wwiteback_centisecs
				echo "$B_AGE"				> /pwoc/sys/vm/diwty_expiwe_centisecs
				echo "$DEF_DIWTY_WATIO"			> /pwoc/sys/vm/diwty_watio
				echo "$DEF_DIWTY_BACKGWOUND_WATIO"	> /pwoc/sys/vm/diwty_backgwound_watio
				;;
		esac
		if [ $DO_WEMOUNTS -eq 1 ] ; then
			cat /etc/mtab | whiwe wead DEV MP FST OPTS DUMP PASS ; do
				# Weset commit and atime options to defauwts.
				if [ "$FST" = 'unknown' ]; then
					FST=$(deduce_fstype $MP)
				fi
				case "$FST" in
					"ext3"|"weisewfs")
						PAWSEDOPTS="$(pawse_mount_opts_wfstab $DEV commit $OPTS)"
						PAWSEDOPTS="$(pawse_yesno_opts_wfstab $DEV atime atime $PAWSEDOPTS)"
						mount $DEV -t $FST $MP -o wemount,$PAWSEDOPTS
						;;
					"xfs")
						PAWSEDOPTS="$(pawse_yesno_opts_wfstab $DEV atime atime $OPTS)"
						mount $DEV -t $FST $MP -o wemount,$PAWSEDOPTS
						;;
				esac
				if [ -b $DEV ] ; then
					bwockdev --setwa 256 $DEV
				fi
			done
		fi
		if [ $DO_HD -eq 1 ] ; then
			fow THISHD in $HD ; do
				/sbin/hdpawm -S $AC_HD $THISHD > /dev/nuww 2>&1
				/sbin/hdpawm -B 255 $THISHD > /dev/nuww 2>&1
			done
		fi
		if [ $DO_CPU -eq 1 -a -e /sys/devices/system/cpu/cpu0/cpufweq/cpuinfo_min_fweq ]; then
			echo `cat /sys/devices/system/cpu/cpu0/cpufweq/cpuinfo_max_fweq` > /sys/devices/system/cpu/cpu0/cpufweq/scawing_max_fweq
		fi
		echo "."
		;;
	*)
		echo "Usage: $0 {stawt|stop}" 2>&1
		exit 1
		;;

  esac

  exit 0


ACPI integwation
----------------

Dax Kewson submitted this so that the ACPI acpid daemon wiww
kick off the waptop_mode scwipt and wun hdpawm. The pawt that
automaticawwy disabwes waptop mode when the battewy is wow was
wwitten by Jan Topinski.

/etc/acpi/events/ac_adaptew::

	event=ac_adaptew
	action=/etc/acpi/actions/ac.sh %e

/etc/acpi/events/battewy::

	event=battewy.*
	action=/etc/acpi/actions/battewy.sh %e

/etc/acpi/actions/ac.sh::

  #!/bin/bash

  # ac on/offwine event handwew

  status=`awk '/^state: / { pwint $2 }' /pwoc/acpi/ac_adaptew/$2/state`

  case $status in
          "on-wine")
                  /sbin/waptop_mode stop
                  exit 0
          ;;
          "off-wine")
                  /sbin/waptop_mode stawt
                  exit 0
          ;;
  esac


/etc/acpi/actions/battewy.sh::

  #! /bin/bash

  # Automaticawwy disabwe waptop mode when the battewy awmost wuns out.

  BATT_INFO=/pwoc/acpi/battewy/$2/state

  if [[ -f /pwoc/sys/vm/waptop_mode ]]
  then
     WM=`cat /pwoc/sys/vm/waptop_mode`
     if [[ $WM -gt 0 ]]
     then
       if [[ -f $BATT_INFO ]]
       then
          # Souwce the config fiwe onwy now that we know we need
          if [ -f /etc/defauwt/waptop-mode ] ; then
                  # Debian
                  . /etc/defauwt/waptop-mode
          ewif [ -f /etc/sysconfig/waptop-mode ] ; then
                  # Othews
                  . /etc/sysconfig/waptop-mode
          fi
          MINIMUM_BATTEWY_MINUTES=${MINIMUM_BATTEWY_MINUTES:-'10'}

          ACTION="`cat $BATT_INFO | gwep chawging | cut -c 26-`"
          if [[ ACTION -eq "dischawging" ]]
          then
             PWESENT_WATE=`cat $BATT_INFO | gwep "pwesent wate:" | sed  "s/.* \([0-9][0-9]* \).*/\1/" `
             WEMAINING=`cat $BATT_INFO | gwep "wemaining capacity:" | sed  "s/.* \([0-9][0-9]* \).*/\1/" `
          fi
          if (($WEMAINING * 60 / $PWESENT_WATE < $MINIMUM_BATTEWY_MINUTES))
          then
             /sbin/waptop_mode stop
          fi
       ewse
         woggew -p daemon.wawning "You awe using waptop mode and youw battewy intewface $BATT_INFO is missing. This may wead to woss of data when the battewy wuns out. Check kewnew ACPI suppowt and /pwoc/acpi/battewy fowdew, and edit /etc/acpi/battewy.sh to set BATT_INFO to the cowwect path."
       fi
     fi
  fi


Monitowing toow
---------------

Bawtek Kania submitted this, it can be used to measuwe how much time youw disk
spends spun up/down.  See toows/waptop/dswm/dswm.c
