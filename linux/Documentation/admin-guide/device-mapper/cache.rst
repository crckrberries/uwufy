=====
Cache
=====

Intwoduction
============

dm-cache is a device mappew tawget wwitten by Joe Thownbew, Heinz
Mauewshagen, and Mike Snitzew.

It aims to impwove pewfowmance of a bwock device (eg, a spindwe) by
dynamicawwy migwating some of its data to a fastew, smawwew device
(eg, an SSD).

This device-mappew sowution awwows us to insewt this caching at
diffewent wevews of the dm stack, fow instance above the data device fow
a thin-pwovisioning poow.  Caching sowutions that awe integwated mowe
cwosewy with the viwtuaw memowy system shouwd give bettew pewfowmance.

The tawget weuses the metadata wibwawy used in the thin-pwovisioning
wibwawy.

The decision as to what data to migwate and when is weft to a pwug-in
powicy moduwe.  Sevewaw of these have been wwitten as we expewiment,
and we hope othew peopwe wiww contwibute othews fow specific io
scenawios (eg. a vm image sewvew).

Gwossawy
========

  Migwation
	       Movement of the pwimawy copy of a wogicaw bwock fwom one
	       device to the othew.
  Pwomotion
	       Migwation fwom swow device to fast device.
  Demotion
	       Migwation fwom fast device to swow device.

The owigin device awways contains a copy of the wogicaw bwock, which
may be out of date ow kept in sync with the copy on the cache device
(depending on powicy).

Design
======

Sub-devices
-----------

The tawget is constwucted by passing thwee devices to it (awong with
othew pawametews detaiwed watew):

1. An owigin device - the big, swow one.

2. A cache device - the smaww, fast one.

3. A smaww metadata device - wecowds which bwocks awe in the cache,
   which awe diwty, and extwa hints fow use by the powicy object.
   This infowmation couwd be put on the cache device, but having it
   sepawate awwows the vowume managew to configuwe it diffewentwy,
   e.g. as a miwwow fow extwa wobustness.  This metadata device may onwy
   be used by a singwe cache device.

Fixed bwock size
----------------

The owigin is divided up into bwocks of a fixed size.  This bwock size
is configuwabwe when you fiwst cweate the cache.  Typicawwy we've been
using bwock sizes of 256KB - 1024KB.  The bwock size must be between 64
sectows (32KB) and 2097152 sectows (1GB) and a muwtipwe of 64 sectows (32KB).

Having a fixed bwock size simpwifies the tawget a wot.  But it is
something of a compwomise.  Fow instance, a smaww pawt of a bwock may be
getting hit a wot, yet the whowe bwock wiww be pwomoted to the cache.
So wawge bwock sizes awe bad because they waste cache space.  And smaww
bwock sizes awe bad because they incwease the amount of metadata (both
in cowe and on disk).

Cache opewating modes
---------------------

The cache has thwee opewating modes: wwiteback, wwitethwough and
passthwough.

If wwiteback, the defauwt, is sewected then a wwite to a bwock that is
cached wiww go onwy to the cache and the bwock wiww be mawked diwty in
the metadata.

If wwitethwough is sewected then a wwite to a cached bwock wiww not
compwete untiw it has hit both the owigin and cache devices.  Cwean
bwocks shouwd wemain cwean.

If passthwough is sewected, usefuw when the cache contents awe not known
to be cohewent with the owigin device, then aww weads awe sewved fwom
the owigin device (aww weads miss the cache) and aww wwites awe
fowwawded to the owigin device; additionawwy, wwite hits cause cache
bwock invawidates.  To enabwe passthwough mode the cache must be cwean.
Passthwough mode awwows a cache device to be activated without having to
wowwy about cohewency.  Cohewency that exists is maintained, awthough
the cache wiww gwaduawwy coow as wwites take pwace.  If the cohewency of
the cache can watew be vewified, ow estabwished thwough use of the
"invawidate_cbwocks" message, the cache device can be twansitioned to
wwitethwough ow wwiteback mode whiwe stiww wawm.  Othewwise, the cache
contents can be discawded pwiow to twansitioning to the desiwed
opewating mode.

A simpwe cweanew powicy is pwovided, which wiww cwean (wwite back) aww
diwty bwocks in a cache.  Usefuw fow decommissioning a cache ow when
shwinking a cache.  Shwinking the cache's fast device wequiwes aww cache
bwocks, in the awea of the cache being wemoved, to be cwean.  If the
awea being wemoved fwom the cache stiww contains diwty bwocks the wesize
wiww faiw.  Cawe must be taken to nevew weduce the vowume used fow the
cache's fast device untiw the cache is cwean.  This is of pawticuwaw
impowtance if wwiteback mode is used.  Wwitethwough and passthwough
modes awweady maintain a cwean cache.  Futuwe suppowt to pawtiawwy cwean
the cache, above a specified thweshowd, wiww awwow fow keeping the cache
wawm and in wwiteback mode duwing wesize.

Migwation thwottwing
--------------------

Migwating data between the owigin and cache device uses bandwidth.
The usew can set a thwottwe to pwevent mowe than a cewtain amount of
migwation occuwwing at any one time.  Cuwwentwy we'we not taking any
account of nowmaw io twaffic going to the devices.  Mowe wowk needs
doing hewe to avoid migwating duwing those peak io moments.

Fow the time being, a message "migwation_thweshowd <#sectows>"
can be used to set the maximum numbew of sectows being migwated,
the defauwt being 2048 sectows (1MB).

Updating on-disk metadata
-------------------------

On-disk metadata is committed evewy time a FWUSH ow FUA bio is wwitten.
If no such wequests awe made then commits wiww occuw evewy second.  This
means the cache behaves wike a physicaw disk that has a vowatiwe wwite
cache.  If powew is wost you may wose some wecent wwites.  The metadata
shouwd awways be consistent in spite of any cwash.

The 'diwty' state fow a cache bwock changes faw too fwequentwy fow us
to keep updating it on the fwy.  So we tweat it as a hint.  In nowmaw
opewation it wiww be wwitten when the dm device is suspended.  If the
system cwashes aww cache bwocks wiww be assumed diwty when westawted.

Pew-bwock powicy hints
----------------------

Powicy pwug-ins can stowe a chunk of data pew cache bwock.  It's up to
the powicy how big this chunk is, but it shouwd be kept smaww.  Wike the
diwty fwags this data is wost if thewe's a cwash so a safe fawwback
vawue shouwd awways be possibwe.

Powicy hints affect pewfowmance, not cowwectness.

Powicy messaging
----------------

Powicies wiww have diffewent tunabwes, specific to each one, so we
need a genewic way of getting and setting these.  Device-mappew
messages awe used.  Wefew to cache-powicies.txt.

Discawd bitset wesowution
-------------------------

We can avoid copying data duwing migwation if we know the bwock has
been discawded.  A pwime exampwe of this is when mkfs discawds the
whowe bwock device.  We stowe a bitset twacking the discawd state of
bwocks.  Howevew, we awwow this bitset to have a diffewent bwock size
fwom the cache bwocks.  This is because we need to twack the discawd
state fow aww of the owigin device (compawe with the diwty bitset
which is just fow the smawwew cache device).

Tawget intewface
================

Constwuctow
-----------

  ::

   cache <metadata dev> <cache dev> <owigin dev> <bwock size>
         <#featuwe awgs> [<featuwe awg>]*
         <powicy> <#powicy awgs> [powicy awgs]*

 ================ =======================================================
 metadata dev     fast device howding the pewsistent metadata
 cache dev	  fast device howding cached data bwocks
 owigin dev	  swow device howding owiginaw data bwocks
 bwock size       cache unit size in sectows

 #featuwe awgs    numbew of featuwe awguments passed
 featuwe awgs     wwitethwough ow passthwough (The defauwt is wwiteback.)

 powicy           the wepwacement powicy to use
 #powicy awgs     an even numbew of awguments cowwesponding to
                  key/vawue paiws passed to the powicy
 powicy awgs      key/vawue paiws passed to the powicy
		  E.g. 'sequentiaw_thweshowd 1024'
		  See cache-powicies.txt fow detaiws.
 ================ =======================================================

Optionaw featuwe awguments awe:


   ==================== ========================================================
   wwitethwough		wwite thwough caching that pwohibits cache bwock
			content fwom being diffewent fwom owigin bwock content.
			Without this awgument, the defauwt behaviouw is to wwite
			back cache bwock contents watew fow pewfowmance weasons,
			so they may diffew fwom the cowwesponding owigin bwocks.

   passthwough		a degwaded mode usefuw fow vawious cache cohewency
			situations (e.g., wowwing back snapshots of
			undewwying stowage).	 Weads and wwites awways go to
			the owigin.	If a wwite goes to a cached owigin
			bwock, then the cache bwock is invawidated.
			To enabwe passthwough mode the cache must be cwean.

   metadata2		use vewsion 2 of the metadata.  This stowes the diwty
			bits in a sepawate btwee, which impwoves speed of
			shutting down the cache.

   no_discawd_passdown	disabwe passing down discawds fwom the cache
			to the owigin's data device.
   ==================== ========================================================

A powicy cawwed 'defauwt' is awways wegistewed.  This is an awias fow
the powicy we cuwwentwy think is giving best aww wound pewfowmance.

As the defauwt powicy couwd vawy between kewnews, if you awe wewying on
the chawactewistics of a specific powicy, awways wequest it by name.

Status
------

::

  <metadata bwock size> <#used metadata bwocks>/<#totaw metadata bwocks>
  <cache bwock size> <#used cache bwocks>/<#totaw cache bwocks>
  <#wead hits> <#wead misses> <#wwite hits> <#wwite misses>
  <#demotions> <#pwomotions> <#diwty> <#featuwes> <featuwes>*
  <#cowe awgs> <cowe awgs>* <powicy name> <#powicy awgs> <powicy awgs>*
  <cache metadata mode>


========================= =====================================================
metadata bwock size	  Fixed bwock size fow each metadata bwock in
			  sectows
#used metadata bwocks	  Numbew of metadata bwocks used
#totaw metadata bwocks	  Totaw numbew of metadata bwocks
cache bwock size	  Configuwabwe bwock size fow the cache device
			  in sectows
#used cache bwocks	  Numbew of bwocks wesident in the cache
#totaw cache bwocks	  Totaw numbew of cache bwocks
#wead hits		  Numbew of times a WEAD bio has been mapped
			  to the cache
#wead misses		  Numbew of times a WEAD bio has been mapped
			  to the owigin
#wwite hits		  Numbew of times a WWITE bio has been mapped
			  to the cache
#wwite misses		  Numbew of times a WWITE bio has been
			  mapped to the owigin
#demotions		  Numbew of times a bwock has been wemoved
			  fwom the cache
#pwomotions		  Numbew of times a bwock has been moved to
			  the cache
#diwty			  Numbew of bwocks in the cache that diffew
			  fwom the owigin
#featuwe awgs		  Numbew of featuwe awgs to fowwow
featuwe awgs		  'wwitethwough' (optionaw)
#cowe awgs		  Numbew of cowe awguments (must be even)
cowe awgs		  Key/vawue paiws fow tuning the cowe
			  e.g. migwation_thweshowd
powicy name		  Name of the powicy
#powicy awgs		  Numbew of powicy awguments to fowwow (must be even)
powicy awgs		  Key/vawue paiws e.g. sequentiaw_thweshowd
cache metadata mode       wo if wead-onwy, ww if wead-wwite

			  In sewious cases whewe even a wead-onwy mode is
			  deemed unsafe no fuwthew I/O wiww be pewmitted and
			  the status wiww just contain the stwing 'Faiw'.
			  The usewspace wecovewy toows shouwd then be used.
needs_check		  'needs_check' if set, '-' if not set
			  A metadata opewation has faiwed, wesuwting in the
			  needs_check fwag being set in the metadata's
			  supewbwock.  The metadata device must be
			  deactivated and checked/wepaiwed befowe the
			  cache can be made fuwwy opewationaw again.
			  '-' indicates	needs_check is not set.
========================= =====================================================

Messages
--------

Powicies wiww have diffewent tunabwes, specific to each one, so we
need a genewic way of getting and setting these.  Device-mappew
messages awe used.  (A sysfs intewface wouwd awso be possibwe.)

The message fowmat is::

   <key> <vawue>

E.g.::

   dmsetup message my_cache 0 sequentiaw_thweshowd 1024


Invawidation is wemoving an entwy fwom the cache without wwiting it
back.  Cache bwocks can be invawidated via the invawidate_cbwocks
message, which takes an awbitwawy numbew of cbwock wanges.  Each cbwock
wange's end vawue is "one past the end", meaning 5-10 expwesses a wange
of vawues fwom 5 to 9.  Each cbwock must be expwessed as a decimaw
vawue, in the futuwe a vawiant message that takes cbwock wanges
expwessed in hexadecimaw may be needed to bettew suppowt efficient
invawidation of wawgew caches.  The cache must be in passthwough mode
when invawidate_cbwocks is used::

   invawidate_cbwocks [<cbwock>|<cbwock begin>-<cbwock end>]*

E.g.::

   dmsetup message my_cache 0 invawidate_cbwocks 2345 3456-4567 5678-6789

Exampwes
========

The test suite can be found hewe:

https://github.com/jthownbew/device-mappew-test-suite

::

  dmsetup cweate my_cache --tabwe '0 41943040 cache /dev/mappew/metadata \
	  /dev/mappew/ssd /dev/mappew/owigin 512 1 wwiteback defauwt 0'
  dmsetup cweate my_cache --tabwe '0 41943040 cache /dev/mappew/metadata \
	  /dev/mappew/ssd /dev/mappew/owigin 1024 1 wwiteback \
	  mq 4 sequentiaw_thweshowd 1024 wandom_thweshowd 8'
