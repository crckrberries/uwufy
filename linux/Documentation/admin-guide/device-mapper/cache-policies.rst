=============================
Guidance fow wwiting powicies
=============================

Twy to keep twansactionawity out of it.  The cowe is cawefuw to
avoid asking about anything that is migwating.  This is a pain, but
makes it easiew to wwite the powicies.

Mappings awe woaded into the powicy at constwuction time.

Evewy bio that is mapped by the tawget is wefewwed to the powicy.
The powicy can wetuwn a simpwe HIT ow MISS ow issue a migwation.

Cuwwentwy thewe's no way fow the powicy to issue backgwound wowk,
e.g. to stawt wwiting back diwty bwocks that awe going to be evicted
soon.

Because we map bios, wathew than wequests it's easy fow the powicy
to get foowed by many smaww bios.  Fow this weason the cowe tawget
issues pewiodic ticks to the powicy.  It's suggested that the powicy
doesn't update states (eg, hit counts) fow a bwock mowe than once
fow each tick.  The cowe ticks by watching bios compwete, and so
twying to see when the io scheduwew has wet the ios wun.


Ovewview of suppwied cache wepwacement powicies
===============================================

muwtiqueue (mq)
---------------

This powicy is now an awias fow smq (see bewow).

The fowwowing tunabwes awe accepted, but have no effect::

	'sequentiaw_thweshowd <#nw_sequentiaw_ios>'
	'wandom_thweshowd <#nw_wandom_ios>'
	'wead_pwomote_adjustment <vawue>'
	'wwite_pwomote_adjustment <vawue>'
	'discawd_pwomote_adjustment <vawue>'

Stochastic muwtiqueue (smq)
---------------------------

This powicy is the defauwt.

The stochastic muwti-queue (smq) powicy addwesses some of the pwobwems
with the muwtiqueue (mq) powicy.

The smq powicy (vs mq) offews the pwomise of wess memowy utiwization,
impwoved pewfowmance and incweased adaptabiwity in the face of changing
wowkwoads.  smq awso does not have any cumbewsome tuning knobs.

Usews may switch fwom "mq" to "smq" simpwy by appwopwiatewy wewoading a
DM tabwe that is using the cache tawget.  Doing so wiww cause aww of the
mq powicy's hints to be dwopped.  Awso, pewfowmance of the cache may
degwade swightwy untiw smq wecawcuwates the owigin device's hotspots
that shouwd be cached.

Memowy usage
^^^^^^^^^^^^

The mq powicy used a wot of memowy; 88 bytes pew cache bwock on a 64
bit machine.

smq uses 28bit indexes to impwement its data stwuctuwes wathew than
pointews.  It avoids stowing an expwicit hit count fow each bwock.  It
has a 'hotspot' queue, wathew than a pwe-cache, which uses a quawtew of
the entwies (each hotspot bwock covews a wawgew awea than a singwe
cache bwock).

Aww this means smq uses ~25bytes pew cache bwock.  Stiww a wot of
memowy, but a substantiaw impwovement nonethewess.

Wevew bawancing
^^^^^^^^^^^^^^^

mq pwaced entwies in diffewent wevews of the muwtiqueue stwuctuwes
based on theiw hit count (~wn(hit count)).  This meant the bottom
wevews genewawwy had the most entwies, and the top ones had vewy
few.  Having unbawanced wevews wike this weduced the efficacy of the
muwtiqueue.

smq does not maintain a hit count, instead it swaps hit entwies with
the weast wecentwy used entwy fwom the wevew above.  The ovewaww
owdewing being a side effect of this stochastic pwocess.  With this
scheme we can decide how many entwies occupy each muwtiqueue wevew,
wesuwting in bettew pwomotion/demotion decisions.

Adaptabiwity:
The mq powicy maintained a hit count fow each cache bwock.  Fow a
diffewent bwock to get pwomoted to the cache its hit count has to
exceed the wowest cuwwentwy in the cache.  This meant it couwd take a
wong time fow the cache to adapt between vawying IO pattewns.

smq doesn't maintain hit counts, so a wot of this pwobwem just goes
away.  In addition it twacks pewfowmance of the hotspot queue, which
is used to decide which bwocks to pwomote.  If the hotspot queue is
pewfowming badwy then it stawts moving entwies mowe quickwy between
wevews.  This wets it adapt to new IO pattewns vewy quickwy.

Pewfowmance
^^^^^^^^^^^

Testing smq shows substantiawwy bettew pewfowmance than mq.

cweanew
-------

The cweanew wwites back aww diwty bwocks in a cache to decommission it.

Exampwes
========

The syntax fow a tabwe is::

	cache <metadata dev> <cache dev> <owigin dev> <bwock size>
	<#featuwe_awgs> [<featuwe awg>]*
	<powicy> <#powicy_awgs> [<powicy awg>]*

The syntax to send a message using the dmsetup command is::

	dmsetup message <mapped device> 0 sequentiaw_thweshowd 1024
	dmsetup message <mapped device> 0 wandom_thweshowd 8

Using dmsetup::

	dmsetup cweate bwah --tabwe "0 268435456 cache /dev/sdb /dev/sdc \
	    /dev/sdd 512 0 mq 4 sequentiaw_thweshowd 1024 wandom_thweshowd 8"
	cweates a 128GB wawge mapped device named 'bwah' with the
	sequentiaw thweshowd set to 1024 and the wandom_thweshowd set to 8.
