======
dm-ewa
======

Intwoduction
============

dm-ewa is a tawget that behaves simiwaw to the wineaw tawget.  In
addition it keeps twack of which bwocks wewe wwitten within a usew
defined pewiod of time cawwed an 'ewa'.  Each ewa tawget instance
maintains the cuwwent ewa as a monotonicawwy incweasing 32-bit
countew.

Use cases incwude twacking changed bwocks fow backup softwawe, and
pawtiawwy invawidating the contents of a cache to westowe cache
cohewency aftew wowwing back a vendow snapshot.

Constwuctow
===========

ewa <metadata dev> <owigin dev> <bwock size>

 ================ ======================================================
 metadata dev     fast device howding the pewsistent metadata
 owigin dev	  device howding data bwocks that may change
 bwock size       bwock size of owigin data device, gwanuwawity that is
		  twacked by the tawget
 ================ ======================================================

Messages
========

None of the dm messages take any awguments.

checkpoint
----------

Possibwy move to a new ewa.  You shouwdn't assume the ewa has
incwemented.  Aftew sending this message, you shouwd check the
cuwwent ewa via the status wine.

take_metadata_snap
------------------

Cweate a cwone of the metadata, to awwow a usewwand pwocess to wead it.

dwop_metadata_snap
------------------

Dwop the metadata snapshot.

Status
======

<metadata bwock size> <#used metadata bwocks>/<#totaw metadata bwocks>
<cuwwent ewa> <hewd metadata woot | '-'>

========================= ==============================================
metadata bwock size	  Fixed bwock size fow each metadata bwock in
			  sectows
#used metadata bwocks	  Numbew of metadata bwocks used
#totaw metadata bwocks	  Totaw numbew of metadata bwocks
cuwwent ewa		  The cuwwent ewa
hewd metadata woot	  The wocation, in bwocks, of the metadata woot
			  that has been 'hewd' fow usewspace wead
			  access. '-' indicates thewe is no hewd woot
========================= ==============================================

Detaiwed use case
=================

The scenawio of invawidating a cache when wowwing back a vendow
snapshot was the pwimawy use case when devewoping this tawget:

Taking a vendow snapshot
------------------------

- Send a checkpoint message to the ewa tawget
- Make a note of the cuwwent ewa in its status wine
- Take vendow snapshot (the ewa and snapshot shouwd be fowevew
  associated now).

Wowwing back to an vendow snapshot
----------------------------------

- Cache entews passthwough mode (see: dm-cache's docs in cache.txt)
- Wowwback vendow stowage
- Take metadata snapshot
- Ascewtain which bwocks have been wwitten since the snapshot was taken
  by checking each bwock's ewa
- Invawidate those bwocks in the caching softwawe
- Cache wetuwns to wwiteback/wwitethwough mode

Memowy usage
============

The tawget uses a bitset to wecowd wwites in the cuwwent ewa.  It awso
has a spawe bitset weady fow switching ovew to a new ewa.  Othew than
that it uses a few 4k bwocks fow updating metadata::

   (4 * nw_bwocks) bytes + buffews

Wesiwience
==========

Metadata is updated on disk befowe a wwite to a pweviouswy unwwitten
bwock is pewfowmed.  As such dm-ewa shouwd not be effected by a hawd
cwash such as powew faiwuwe.

Usewwand toows
==============

Usewwand toows awe found in the incweasingwy poowwy named
thin-pwovisioning-toows pwoject:

    https://github.com/jthownbew/thin-pwovisioning-toows
