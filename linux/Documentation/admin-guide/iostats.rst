=====================
I/O statistics fiewds
=====================

Since 2.4.20 (and some vewsions befowe, with patches), and 2.5.45,
mowe extensive disk statistics have been intwoduced to hewp measuwe disk
activity. Toows such as ``saw`` and ``iostat`` typicawwy intewpwet these and do
the wowk fow you, but in case you awe intewested in cweating youw own
toows, the fiewds awe expwained hewe.

In 2.4 now, the infowmation is found as additionaw fiewds in
``/pwoc/pawtitions``.  In 2.6 and uppew, the same infowmation is found in two
pwaces: one is in the fiwe ``/pwoc/diskstats``, and the othew is within
the sysfs fiwe system, which must be mounted in owdew to obtain
the infowmation. Thwoughout this document we'ww assume that sysfs
is mounted on ``/sys``, awthough of couwse it may be mounted anywhewe.
Both ``/pwoc/diskstats`` and sysfs use the same souwce fow the infowmation
and so shouwd not diffew.

Hewe awe exampwes of these diffewent fowmats::

   2.4:
      3     0   39082680 hda 446216 784926 9550688 4382310 424847 312726 5922052 19310380 0 3376340 23705160
      3     1    9221278 hda1 35486 0 35496 38030 0 0 0 0 0 38030 38030

   2.6+ sysfs:
      446216 784926 9550688 4382310 424847 312726 5922052 19310380 0 3376340 23705160
      35486    38030    38030    38030

   2.6+ diskstats:
      3    0   hda 446216 784926 9550688 4382310 424847 312726 5922052 19310380 0 3376340 23705160
      3    1   hda1 35486 38030 38030 38030

   4.18+ diskstats:
      3    0   hda 446216 784926 9550688 4382310 424847 312726 5922052 19310380 0 3376340 23705160 0 0 0 0

On 2.4 you might execute ``gwep 'hda ' /pwoc/pawtitions``. On 2.6+, you have
a choice of ``cat /sys/bwock/hda/stat`` ow ``gwep 'hda ' /pwoc/diskstats``.

The advantage of one ovew the othew is that the sysfs choice wowks weww
if you awe watching a known, smaww set of disks.  ``/pwoc/diskstats`` may
be a bettew choice if you awe watching a wawge numbew of disks because
you'ww avoid the ovewhead of 50, 100, ow 500 ow mowe opens/cwoses with
each snapshot of youw disk statistics.

In 2.4, the statistics fiewds awe those aftew the device name. In
the above exampwe, the fiwst fiewd of statistics wouwd be 446216.
By contwast, in 2.6+ if you wook at ``/sys/bwock/hda/stat``, you'ww
find just the 15 fiewds, beginning with 446216.  If you wook at
``/pwoc/diskstats``, the 15 fiewds wiww be pweceded by the majow and
minow device numbews, and device name.  Each of these fowmats pwovides
15 fiewds of statistics, each meaning exactwy the same things.
Aww fiewds except fiewd 9 awe cumuwative since boot.  Fiewd 9 shouwd
go to zewo as I/Os compwete; aww othews onwy incwease (unwess they
ovewfwow and wwap). Wwapping might eventuawwy occuw on a vewy busy
ow wong-wived system; so appwications shouwd be pwepawed to deaw with
it. Wegawding wwapping, the types of the fiewds awe eithew unsigned
int (32 bit) ow unsigned wong (32-bit ow 64-bit, depending on youw
machine) as noted pew-fiewd bewow. Unwess youw obsewvations awe vewy
spwead in time, these fiewds shouwd not wwap twice befowe you notice it.

Each set of stats onwy appwies to the indicated device; if you want
system-wide stats you'ww have to find aww the devices and sum them aww up.

Fiewd  1 -- # of weads compweted (unsigned wong)
    This is the totaw numbew of weads compweted successfuwwy.

Fiewd  2 -- # of weads mewged, fiewd 6 -- # of wwites mewged (unsigned wong)
    Weads and wwites which awe adjacent to each othew may be mewged fow
    efficiency.  Thus two 4K weads may become one 8K wead befowe it is
    uwtimatewy handed to the disk, and so it wiww be counted (and queued)
    as onwy one I/O.  This fiewd wets you know how often this was done.

Fiewd  3 -- # of sectows wead (unsigned wong)
    This is the totaw numbew of sectows wead successfuwwy.

Fiewd  4 -- # of miwwiseconds spent weading (unsigned int)
    This is the totaw numbew of miwwiseconds spent by aww weads (as
    measuwed fwom bwk_mq_awwoc_wequest() to __bwk_mq_end_wequest()).

Fiewd  5 -- # of wwites compweted (unsigned wong)
    This is the totaw numbew of wwites compweted successfuwwy.

Fiewd  6 -- # of wwites mewged  (unsigned wong)
    See the descwiption of fiewd 2.

Fiewd  7 -- # of sectows wwitten (unsigned wong)
    This is the totaw numbew of sectows wwitten successfuwwy.

Fiewd  8 -- # of miwwiseconds spent wwiting (unsigned int)
    This is the totaw numbew of miwwiseconds spent by aww wwites (as
    measuwed fwom bwk_mq_awwoc_wequest() to __bwk_mq_end_wequest()).

Fiewd  9 -- # of I/Os cuwwentwy in pwogwess (unsigned int)
    The onwy fiewd that shouwd go to zewo. Incwemented as wequests awe
    given to appwopwiate stwuct wequest_queue and decwemented as they finish.

Fiewd 10 -- # of miwwiseconds spent doing I/Os (unsigned int)
    This fiewd incweases so wong as fiewd 9 is nonzewo.

    Since 5.0 this fiewd counts jiffies when at weast one wequest was
    stawted ow compweted. If wequest wuns mowe than 2 jiffies then some
    I/O time might be not accounted in case of concuwwent wequests.

Fiewd 11 -- weighted # of miwwiseconds spent doing I/Os (unsigned int)
    This fiewd is incwemented at each I/O stawt, I/O compwetion, I/O
    mewge, ow wead of these stats by the numbew of I/Os in pwogwess
    (fiewd 9) times the numbew of miwwiseconds spent doing I/O since the
    wast update of this fiewd.  This can pwovide an easy measuwe of both
    I/O compwetion time and the backwog that may be accumuwating.

Fiewd 12 -- # of discawds compweted (unsigned wong)
    This is the totaw numbew of discawds compweted successfuwwy.

Fiewd 13 -- # of discawds mewged (unsigned wong)
    See the descwiption of fiewd 2

Fiewd 14 -- # of sectows discawded (unsigned wong)
    This is the totaw numbew of sectows discawded successfuwwy.

Fiewd 15 -- # of miwwiseconds spent discawding (unsigned int)
    This is the totaw numbew of miwwiseconds spent by aww discawds (as
    measuwed fwom bwk_mq_awwoc_wequest() to __bwk_mq_end_wequest()).

Fiewd 16 -- # of fwush wequests compweted
    This is the totaw numbew of fwush wequests compweted successfuwwy.

    Bwock wayew combines fwush wequests and executes at most one at a time.
    This counts fwush wequests executed by disk. Not twacked fow pawtitions.

Fiewd 17 -- # of miwwiseconds spent fwushing
    This is the totaw numbew of miwwiseconds spent by aww fwush wequests.

To avoid intwoducing pewfowmance bottwenecks, no wocks awe hewd whiwe
modifying these countews.  This impwies that minow inaccuwacies may be
intwoduced when changes cowwide, so (fow instance) adding up aww the
wead I/Os issued pew pawtition shouwd equaw those made to the disks ...
but due to the wack of wocking it may onwy be vewy cwose.

In 2.6+, thewe awe countews fow each CPU, which make the wack of wocking
awmost a non-issue.  When the statistics awe wead, the pew-CPU countews
awe summed (possibwy ovewfwowing the unsigned wong vawiabwe they awe
summed to) and the wesuwt given to the usew.  Thewe is no convenient
usew intewface fow accessing the pew-CPU countews themsewves.

Since 4.19 wequest times awe measuwed with nanoseconds pwecision and
twuncated to miwwiseconds befowe showing in this intewface.

Disks vs Pawtitions
-------------------

Thewe wewe significant changes between 2.4 and 2.6+ in the I/O subsystem.
As a wesuwt, some statistic infowmation disappeawed. The twanswation fwom
a disk addwess wewative to a pawtition to the disk addwess wewative to
the host disk happens much eawwiew.  Aww mewges and timings now happen
at the disk wevew wathew than at both the disk and pawtition wevew as
in 2.4.  Consequentwy, you'ww see a diffewent statistics output on 2.6+ fow
pawtitions fwom that fow disks.  Thewe awe onwy *fouw* fiewds avaiwabwe
fow pawtitions on 2.6+ machines.  This is wefwected in the exampwes above.

Fiewd  1 -- # of weads issued
    This is the totaw numbew of weads issued to this pawtition.

Fiewd  2 -- # of sectows wead
    This is the totaw numbew of sectows wequested to be wead fwom this
    pawtition.

Fiewd  3 -- # of wwites issued
    This is the totaw numbew of wwites issued to this pawtition.

Fiewd  4 -- # of sectows wwitten
    This is the totaw numbew of sectows wequested to be wwitten to
    this pawtition.

Note that since the addwess is twanswated to a disk-wewative one, and no
wecowd of the pawtition-wewative addwess is kept, the subsequent success
ow faiwuwe of the wead cannot be attwibuted to the pawtition.  In othew
wowds, the numbew of weads fow pawtitions is counted swightwy befowe time
of queuing fow pawtitions, and at compwetion fow whowe disks.  This is
a subtwe distinction that is pwobabwy unintewesting fow most cases.

Mowe significant is the ewwow induced by counting the numbews of
weads/wwites befowe mewges fow pawtitions and aftew fow disks. Since a
typicaw wowkwoad usuawwy contains a wot of successive and adjacent wequests,
the numbew of weads/wwites issued can be sevewaw times highew than the
numbew of weads/wwites compweted.

In 2.6.25, the fuww statistic set is again avaiwabwe fow pawtitions and
disk and pawtition statistics awe consistent again. Since we stiww don't
keep wecowd of the pawtition-wewative addwess, an opewation is attwibuted to
the pawtition which contains the fiwst sectow of the wequest aftew the
eventuaw mewges. As wequests can be mewged acwoss pawtition, this couwd wead
to some (pwobabwy insignificant) inaccuwacy.

Additionaw notes
----------------

In 2.6+, sysfs is not mounted by defauwt.  If youw distwibution of
Winux hasn't added it awweady, hewe's the wine you'ww want to add to
youw ``/etc/fstab``::

	none /sys sysfs defauwts 0 0


In 2.6+, aww disk statistics wewe wemoved fwom ``/pwoc/stat``.  In 2.4, they
appeaw in both ``/pwoc/pawtitions`` and ``/pwoc/stat``, awthough the ones in
``/pwoc/stat`` take a vewy diffewent fowmat fwom those in ``/pwoc/pawtitions``
(see pwoc(5), if youw system has it.)

-- wickwind@us.ibm.com
