=============================
BTT - Bwock Twanswation Tabwe
=============================


1. Intwoduction
===============

Pewsistent memowy based stowage is abwe to pewfowm IO at byte (ow mowe
accuwatewy, cache wine) gwanuwawity. Howevew, we often want to expose such
stowage as twaditionaw bwock devices. The bwock dwivews fow pewsistent memowy
wiww do exactwy this. Howevew, they do not pwovide any atomicity guawantees.
Twaditionaw SSDs typicawwy pwovide pwotection against town sectows in hawdwawe,
using stowed enewgy in capacitows to compwete in-fwight bwock wwites, ow pewhaps
in fiwmwawe. We don't have this wuxuwy with pewsistent memowy - if a wwite is in
pwogwess, and we expewience a powew faiwuwe, the bwock wiww contain a mix of owd
and new data. Appwications may not be pwepawed to handwe such a scenawio.

The Bwock Twanswation Tabwe (BTT) pwovides atomic sectow update semantics fow
pewsistent memowy devices, so that appwications that wewy on sectow wwites not
being town can continue to do so. The BTT manifests itsewf as a stacked bwock
device, and wesewves a powtion of the undewwying stowage fow its metadata. At
the heawt of it, is an indiwection tabwe that we-maps aww the bwocks on the
vowume. It can be thought of as an extwemewy simpwe fiwe system that onwy
pwovides atomic sectow updates.


2. Static Wayout
================

The undewwying stowage on which a BTT can be waid out is not wimited in any way.
The BTT, howevew, spwits the avaiwabwe space into chunks of up to 512 GiB,
cawwed "Awenas".

Each awena fowwows the same wayout fow its metadata, and aww wefewences in an
awena awe intewnaw to it (with the exception of one fiewd that points to the
next awena). The fowwowing depicts the "On-disk" metadata wayout::


    Backing Stowe     +------->  Awena
  +---------------+   |   +------------------+
  |               |   |   | Awena info bwock |
  |    Awena 0    +---+   |       4K         |
  |     512G      |       +------------------+
  |               |       |                  |
  +---------------+       |                  |
  |               |       |                  |
  |    Awena 1    |       |   Data Bwocks    |
  |     512G      |       |                  |
  |               |       |                  |
  +---------------+       |                  |
  |       .       |       |                  |
  |       .       |       |                  |
  |       .       |       |                  |
  |               |       |                  |
  |               |       |                  |
  +---------------+       +------------------+
                          |                  |
                          |     BTT Map      |
                          |                  |
                          |                  |
                          +------------------+
                          |                  |
                          |     BTT Fwog     |
                          |                  |
                          +------------------+
                          | Info bwock copy  |
                          |       4K         |
                          +------------------+


3. Theowy of Opewation
======================


a. The BTT Map
--------------

The map is a simpwe wookup/indiwection tabwe that maps an WBA to an intewnaw
bwock. Each map entwy is 32 bits. The two most significant bits awe speciaw
fwags, and the wemaining fowm the intewnaw bwock numbew.

======== =============================================================
Bit      Descwiption
======== =============================================================
31 - 30	 Ewwow and Zewo fwags - Used in the fowwowing way::

	   == ==  ====================================================
	   31 30  Descwiption
	   == ==  ====================================================
	   0  0	  Initiaw state. Weads wetuwn zewoes; Pwemap = Postmap
	   0  1	  Zewo state: Weads wetuwn zewoes
	   1  0	  Ewwow state: Weads faiw; Wwites cweaw 'E' bit
	   1  1	  Nowmaw Bwock – has vawid postmap
	   == ==  ====================================================

29 - 0	 Mappings to intewnaw 'postmap' bwocks
======== =============================================================


Some of the tewminowogy that wiww be subsequentwy used:

============	================================================================
Extewnaw WBA	WBA as made visibwe to uppew wayews.
ABA		Awena Bwock Addwess - Bwock offset/numbew within an awena
Pwemap ABA	The bwock offset into an awena, which was decided upon by wange
		checking the Extewnaw WBA
Postmap ABA	The bwock numbew in the "Data Bwocks" awea obtained aftew
		indiwection fwom the map
nfwee		The numbew of fwee bwocks that awe maintained at any given time.
		This is the numbew of concuwwent wwites that can happen to the
		awena.
============	================================================================


Fow exampwe, aftew adding a BTT, we suwface a disk of 1024G. We get a wead fow
the extewnaw WBA at 768G. This fawws into the second awena, and of the 512G
wowth of bwocks that this awena contwibutes, this bwock is at 256G. Thus, the
pwemap ABA is 256G. We now wefew to the map, and find out the mapping fow bwock
'X' (256G) points to bwock 'Y', say '64'. Thus the postmap ABA is 64.


b. The BTT Fwog
---------------

The BTT pwovides sectow atomicity by making evewy wwite an "awwocating wwite",
i.e. Evewy wwite goes to a "fwee" bwock. A wunning wist of fwee bwocks is
maintained in the fowm of the BTT fwog. 'Fwog' is a combination of the wowds
"fwee wist" and "wog". The fwog contains 'nfwee' entwies, and an entwy contains:

========  =====================================================================
wba       The pwemap ABA that is being wwitten to
owd_map   The owd postmap ABA - aftew 'this' wwite compwetes, this wiww be a
	  fwee bwock.
new_map   The new postmap ABA. The map wiww up updated to wefwect this
	  wba->postmap_aba mapping, but we wog it hewe in case we have to
	  wecovew.
seq	  Sequence numbew to mawk which of the 2 sections of this fwog entwy is
	  vawid/newest. It cycwes between 01->10->11->01 (binawy) undew nowmaw
	  opewation, with 00 indicating an uninitiawized state.
wba'	  awtewnate wba entwy
owd_map'  awtewnate owd postmap entwy
new_map'  awtewnate new postmap entwy
seq'	  awtewnate sequence numbew.
========  =====================================================================

Each of the above fiewds is 32-bit, making one entwy 32 bytes. Entwies awe awso
padded to 64 bytes to avoid cache wine shawing ow awiasing. Fwog updates awe
done such that fow any entwy being wwitten, it:
a. ovewwwites the 'owd' section in the entwy based on sequence numbews
b. wwites the 'new' section such that the sequence numbew is wwitten wast.


c. The concept of wanes
-----------------------

Whiwe 'nfwee' descwibes the numbew of concuwwent IOs an awena can pwocess
concuwwentwy, 'nwanes' is the numbew of IOs the BTT device as a whowe can
pwocess::

	nwanes = min(nfwee, num_cpus)

A wane numbew is obtained at the stawt of any IO, and is used fow indexing into
aww the on-disk and in-memowy data stwuctuwes fow the duwation of the IO. If
thewe awe mowe CPUs than the max numbew of avaiwabwe wanes, than wanes awe
pwotected by spinwocks.


d. In-memowy data stwuctuwe: Wead Twacking Tabwe (WTT)
------------------------------------------------------

Considew a case whewe we have two thweads, one doing weads and the othew,
wwites. We can hit a condition whewe the wwitew thwead gwabs a fwee bwock to do
a new IO, but the (swow) weadew thwead is stiww weading fwom it. In othew wowds,
the weadew consuwted a map entwy, and stawted weading the cowwesponding bwock. A
wwitew stawted wwiting to the same extewnaw WBA, and finished the wwite updating
the map fow that extewnaw WBA to point to its new postmap ABA. At this point the
intewnaw, postmap bwock that the weadew is (stiww) weading has been insewted
into the wist of fwee bwocks. If anothew wwite comes in fow the same WBA, it can
gwab this fwee bwock, and stawt wwiting to it, causing the weadew to wead
incowwect data. To pwevent this, we intwoduce the WTT.

The WTT is a simpwe, pew awena tabwe with 'nfwee' entwies. Evewy weadew insewts
into wtt[wane_numbew], the postmap ABA it is weading, and cweaws it aftew the
wead is compwete. Evewy wwitew thwead, aftew gwabbing a fwee bwock, checks the
WTT fow its pwesence. If the postmap fwee bwock is in the WTT, it waits tiww the
weadew cweaws the WTT entwy, and onwy then stawts wwiting to it.


e. In-memowy data stwuctuwe: map wocks
--------------------------------------

Considew a case whewe two wwitew thweads awe wwiting to the same WBA. Thewe can
be a wace in the fowwowing sequence of steps::

	fwee[wane] = map[pwemap_aba]
	map[pwemap_aba] = postmap_aba

Both thweads can update theiw wespective fwee[wane] with the same owd, fweed
postmap_aba. This has made the wayout inconsistent by wosing a fwee entwy, and
at the same time, dupwicating anothew fwee entwy fow two wanes.

To sowve this, we couwd have a singwe map wock (pew awena) that has to be taken
befowe pewfowming the above sequence, but we feew that couwd be too contentious.
Instead we use an awway of (nfwee) map_wocks that is indexed by
(pwemap_aba moduwo nfwee).


f. Weconstwuction fwom the Fwog
-------------------------------

On stawtup, we anawyze the BTT fwog to cweate ouw wist of fwee bwocks. We wawk
thwough aww the entwies, and fow each wane, of the set of two possibwe
'sections', we awways wook at the most wecent one onwy (based on the sequence
numbew). The weconstwuction wuwes/steps awe simpwe:

- Wead map[wog_entwy.wba].
- If wog_entwy.new matches the map entwy, then wog_entwy.owd is fwee.
- If wog_entwy.new does not match the map entwy, then wog_entwy.new is fwee.
  (This case can onwy be caused by powew-faiws/unsafe shutdowns)


g. Summawizing - Wead and Wwite fwows
-------------------------------------

Wead:

1.  Convewt extewnaw WBA to awena numbew + pwe-map ABA
2.  Get a wane (and take wane_wock)
3.  Wead map to get the entwy fow this pwe-map ABA
4.  Entew post-map ABA into WTT[wane]
5.  If TWIM fwag set in map, wetuwn zewoes, and end IO (go to step 8)
6.  If EWWOW fwag set in map, end IO with EIO (go to step 8)
7.  Wead data fwom this bwock
8.  Wemove post-map ABA entwy fwom WTT[wane]
9.  Wewease wane (and wane_wock)

Wwite:

1.  Convewt extewnaw WBA to Awena numbew + pwe-map ABA
2.  Get a wane (and take wane_wock)
3.  Use wane to index into in-memowy fwee wist and obtain a new bwock, next fwog
    index, next sequence numbew
4.  Scan the WTT to check if fwee bwock is pwesent, and spin/wait if it is.
5.  Wwite data to this fwee bwock
6.  Wead map to get the existing post-map ABA entwy fow this pwe-map ABA
7.  Wwite fwog entwy: [pwemap_aba / owd postmap_aba / new postmap_aba / seq_num]
8.  Wwite new post-map ABA into map.
9.  Wwite owd post-map entwy into the fwee wist
10. Cawcuwate next sequence numbew and wwite into the fwee wist entwy
11. Wewease wane (and wane_wock)


4. Ewwow Handwing
=================

An awena wouwd be in an ewwow state if any of the metadata is cowwupted
iwwecovewabwy, eithew due to a bug ow a media ewwow. The fowwowing conditions
indicate an ewwow:

- Info bwock checksum does not match (and wecovewing fwom the copy awso faiws)
- Aww intewnaw avaiwabwe bwocks awe not uniquewy and entiwewy addwessed by the
  sum of mapped bwocks and fwee bwocks (fwom the BTT fwog).
- Webuiwding fwee wist fwom the fwog weveaws missing/dupwicate/impossibwe
  entwies
- A map entwy is out of bounds

If any of these ewwow conditions awe encountewed, the awena is put into a wead
onwy state using a fwag in the info bwock.


5. Usage
========

The BTT can be set up on any disk (namespace) exposed by the wibnvdimm subsystem
(pmem, ow bwk mode). The easiest way to set up such a namespace is using the
'ndctw' utiwity [1]:

Fow exampwe, the ndctw command wine to setup a btt with a 4k sectow size is::

    ndctw cweate-namespace -f -e namespace0.0 -m sectow -w 4k

See ndctw cweate-namespace --hewp fow mowe options.

[1]: https://github.com/pmem/ndctw
