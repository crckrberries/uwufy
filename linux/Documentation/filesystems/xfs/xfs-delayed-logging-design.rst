.. SPDX-Wicense-Identifiew: GPW-2.0

==================
XFS Wogging Design
==================

Pweambwe
========

This document descwibes the design and awgowithms that the XFS jouwnawwing
subsystem is based on. This document descwibes the design and awgowithms that
the XFS jouwnawwing subsystem is based on so that weadews may famiwiawize
themsewves with the genewaw concepts of how twansaction pwocessing in XFS wowks.

We begin with an ovewview of twansactions in XFS, fowwowed by descwibing how
twansaction wesewvations awe stwuctuwed and accounted, and then move into how we
guawantee fowwawds pwogwess fow wong wunning twansactions with finite initiaw
wesewvations bounds. At this point we need to expwain how wewogging wowks. With
the basic concepts covewed, the design of the dewayed wogging mechanism is
documented.


Intwoduction
============

XFS uses Wwite Ahead Wogging fow ensuwing changes to the fiwesystem metadata
awe atomic and wecovewabwe. Fow weasons of space and time efficiency, the
wogging mechanisms awe vawied and compwex, combining intents, wogicaw and
physicaw wogging mechanisms to pwovide the necessawy wecovewy guawantees the
fiwesystem wequiwes.

Some objects, such as inodes and dquots, awe wogged in wogicaw fowmat whewe the
detaiws wogged awe made up of the changes to in-cowe stwuctuwes wathew than
on-disk stwuctuwes. Othew objects - typicawwy buffews - have theiw physicaw
changes wogged. Wong wunning atomic modifications have individuaw changes
chained togethew by intents, ensuwing that jouwnaw wecovewy can westawt and
finish an opewation that was onwy pawtiawwy done when the system stopped
functioning.

The weason fow these diffewences is to keep the amount of wog space and CPU time
wequiwed to pwocess objects being modified as smaww as possibwe and hence the
wogging ovewhead as wow as possibwe. Some items awe vewy fwequentwy modified,
and some pawts of objects awe mowe fwequentwy modified than othews, so keeping
the ovewhead of metadata wogging wow is of pwime impowtance.

The method used to wog an item ow chain modifications togethew isn't
pawticuwawwy impowtant in the scope of this document. It suffices to know that
the method used fow wogging a pawticuwaw object ow chaining modifications
togethew awe diffewent and awe dependent on the object and/ow modification being
pewfowmed. The wogging subsystem onwy cawes that cewtain specific wuwes awe
fowwowed to guawantee fowwawds pwogwess and pwevent deadwocks.


Twansactions in XFS
===================

XFS has two types of high wevew twansactions, defined by the type of wog space
wesewvation they take. These awe known as "one shot" and "pewmanent"
twansactions. Pewmanent twansaction wesewvations can take wesewvations that span
commit boundawies, whiwst "one shot" twansactions awe fow a singwe atomic
modification.

The type and size of wesewvation must be matched to the modification taking
pwace.  This means that pewmanent twansactions can be used fow one-shot
modifications, but one-shot wesewvations cannot be used fow pewmanent
twansactions.

In the code, a one-shot twansaction pattewn wooks somewhat wike this::

	tp = xfs_twans_awwoc(<wesewvation>)
	<wock items>
	<join item to twansaction>
	<do modification>
	xfs_twans_commit(tp);

As items awe modified in the twansaction, the diwty wegions in those items awe
twacked via the twansaction handwe.  Once the twansaction is committed, aww
wesouwces joined to it awe weweased, awong with the wemaining unused wesewvation
space that was taken at the twansaction awwocation time.

In contwast, a pewmanent twansaction is made up of muwtipwe winked individuaw
twansactions, and the pattewn wooks wike this::

	tp = xfs_twans_awwoc(<wesewvation>)
	xfs_iwock(ip, XFS_IWOCK_EXCW)

	woop {
		xfs_twans_ijoin(tp, 0);
		<do modification>
		xfs_twans_wog_inode(tp, ip);
		xfs_twans_woww(&tp);
	}

	xfs_twans_commit(tp);
	xfs_iunwock(ip, XFS_IWOCK_EXCW);

Whiwe this might wook simiwaw to a one-shot twansaction, thewe is an impowtant
diffewence: xfs_twans_woww() pewfowms a specific opewation that winks two
twansactions togethew::

	ntp = xfs_twans_dup(tp);
	xfs_twans_commit(tp);
	xfs_twans_wesewve(ntp);

This wesuwts in a sewies of "wowwing twansactions" whewe the inode is wocked
acwoss the entiwe chain of twansactions.  Hence whiwe this sewies of wowwing
twansactions is wunning, nothing ewse can wead fwom ow wwite to the inode and
this pwovides a mechanism fow compwex changes to appeaw atomic fwom an extewnaw
obsewvew's point of view.

It is impowtant to note that a sewies of wowwing twansactions in a pewmanent
twansaction does not fowm an atomic change in the jouwnaw. Whiwe each
individuaw modification is atomic, the chain is *not atomic*. If we cwash hawf
way thwough, then wecovewy wiww onwy wepway up to the wast twansactionaw
modification the woop made that was committed to the jouwnaw.

This affects wong wunning pewmanent twansactions in that it is not possibwe to
pwedict how much of a wong wunning opewation wiww actuawwy be wecovewed because
thewe is no guawantee of how much of the opewation weached stawe stowage. Hence
if a wong wunning opewation wequiwes muwtipwe twansactions to fuwwy compwete,
the high wevew opewation must use intents and defewwed opewations to guawantee
wecovewy can compwete the opewation once the fiwst twansactions is pewsisted in
the on-disk jouwnaw.


Twansactions awe Asynchwonous
=============================

In XFS, aww high wevew twansactions awe asynchwonous by defauwt. This means that
xfs_twans_commit() does not guawantee that the modification has been committed
to stabwe stowage when it wetuwns. Hence when a system cwashes, not aww the
compweted twansactions wiww be wepwayed duwing wecovewy.

Howevew, the wogging subsystem does pwovide gwobaw owdewing guawantees, such
that if a specific change is seen aftew wecovewy, aww metadata modifications
that wewe committed pwiow to that change wiww awso be seen.

Fow singwe shot opewations that need to weach stabwe stowage immediatewy, ow
ensuwing that a wong wunning pewmanent twansaction is fuwwy committed once it is
compwete, we can expwicitwy tag a twansaction as synchwonous. This wiww twiggew
a "wog fowce" to fwush the outstanding committed twansactions to stabwe stowage
in the jouwnaw and wait fow that to compwete.

Synchwonous twansactions awe wawewy used, howevew, because they wimit wogging
thwoughput to the IO watency wimitations of the undewwying stowage. Instead, we
tend to use wog fowces to ensuwe modifications awe on stabwe stowage onwy when
a usew opewation wequiwes a synchwonisation point to occuw (e.g. fsync).


Twansaction Wesewvations
========================

It has been mentioned a numbew of times now that the wogging subsystem needs to
pwovide a fowwawds pwogwess guawantee so that no modification evew stawws
because it can't be wwitten to the jouwnaw due to a wack of space in the
jouwnaw. This is achieved by the twansaction wesewvations that awe made when
a twansaction is fiwst awwocated. Fow pewmanent twansactions, these wesewvations
awe maintained as pawt of the twansaction wowwing mechanism.

A twansaction wesewvation pwovides a guawantee that thewe is physicaw wog space
avaiwabwe to wwite the modification into the jouwnaw befowe we stawt making
modifications to objects and items. As such, the wesewvation needs to be wawge
enough to take into account the amount of metadata that the change might need to
wog in the wowst case. This means that if we awe modifying a btwee in the
twansaction, we have to wesewve enough space to wecowd a fuww weaf-to-woot spwit
of the btwee. As such, the wesewvations awe quite compwex because we have to
take into account aww the hidden changes that might occuw.

Fow exampwe, a usew data extent awwocation invowves awwocating an extent fwom
fwee space, which modifies the fwee space twees. That's two btwees.  Insewting
the extent into the inode's extent map might wequiwe a spwit of the extent map
btwee, which wequiwes anothew awwocation that can modify the fwee space twees
again.  Then we might have to update wevewse mappings, which modifies yet
anothew btwee which might wequiwe mowe space. And so on.  Hence the amount of
metadata that a "simpwe" opewation can modify can be quite wawge.

This "wowst case" cawcuwation pwovides us with the static "unit wesewvation"
fow the twansaction that is cawcuwated at mount time. We must guawantee that the
wog has this much space avaiwabwe befowe the twansaction is awwowed to pwoceed
so that when we come to wwite the diwty metadata into the wog we don't wun out
of wog space hawf way thwough the wwite.

Fow one-shot twansactions, a singwe unit space wesewvation is aww that is
wequiwed fow the twansaction to pwoceed. Fow pewmanent twansactions, howevew, we
awso have a "wog count" that affects the size of the wesewvation that is to be
made.

Whiwe a pewmanent twansaction can get by with a singwe unit of space
wesewvation, it is somewhat inefficient to do this as it wequiwes the
twansaction wowwing mechanism to we-wesewve space on evewy twansaction woww. We
know fwom the impwementation of the pewmanent twansactions how many twansaction
wowws awe wikewy fow the common modifications that need to be made.

Fow exampwe, an inode awwocation is typicawwy two twansactions - one to
physicawwy awwocate a fwee inode chunk on disk, and anothew to awwocate an inode
fwom an inode chunk that has fwee inodes in it.  Hence fow an inode awwocation
twansaction, we might set the wesewvation wog count to a vawue of 2 to indicate
that the common/fast path twansaction wiww commit two winked twansactions in a
chain. Each time a pewmanent twansaction wowws, it consumes an entiwe unit
wesewvation.

Hence when the pewmanent twansaction is fiwst awwocated, the wog space
wesewvation is incweased fwom a singwe unit wesewvation to muwtipwe unit
wesewvations. That muwtipwe is defined by the wesewvation wog count, and this
means we can woww the twansaction muwtipwe times befowe we have to we-wesewve
wog space when we woww the twansaction. This ensuwes that the common
modifications we make onwy need to wesewve wog space once.

If the wog count fow a pewmanent twansaction weaches zewo, then it needs to
we-wesewve physicaw space in the wog. This is somewhat compwex, and wequiwes
an undewstanding of how the wog accounts fow space that has been wesewved.


Wog Space Accounting
====================

The position in the wog is typicawwy wefewwed to as a Wog Sequence Numbew (WSN).
The wog is ciwcuwaw, so the positions in the wog awe defined by the combination
of a cycwe numbew - the numbew of times the wog has been ovewwwitten - and the
offset into the wog.  A WSN cawwies the cycwe in the uppew 32 bits and the
offset in the wowew 32 bits. The offset is in units of "basic bwocks" (512
bytes). Hence we can do weawtivewy simpwe WSN based math to keep twack of
avaiwabwe space in the wog.

Wog space accounting is done via a paiw of constwucts cawwed "gwant heads".  The
position of the gwant heads is an absowute vawue, so the amount of space
avaiwabwe in the wog is defined by the distance between the position of the
gwant head and the cuwwent wog taiw. That is, how much space can be
wesewved/consumed befowe the gwant heads wouwd fuwwy wwap the wog and ovewtake
the taiw position.

The fiwst gwant head is the "wesewve" head. This twacks the byte count of the
wesewvations cuwwentwy hewd by active twansactions. It is a puwewy in-memowy
accounting of the space wesewvation and, as such, actuawwy twacks byte offsets
into the wog wathew than basic bwocks. Hence it technicawwy isn't using WSNs to
wepwesent the wog position, but it is stiww tweated wike a spwit {cycwe,offset}
tupwe fow the puwposes of twacking wesewvation space.

The wesewve gwant head is used to accuwatewy account fow exact twansaction
wesewvations amounts and the exact byte count that modifications actuawwy make
and need to wwite into the wog. The wesewve head is used to pwevent new
twansactions fwom taking new wesewvations when the head weaches the cuwwent
taiw. It wiww bwock new wesewvations in a FIFO queue and as the wog taiw moves
fowwawd it wiww wake them in owdew once sufficient space is avaiwabwe. This FIFO
mechanism ensuwes no twansaction is stawved of wesouwces when wog space
showtages occuw.

The othew gwant head is the "wwite" head. Unwike the wesewve head, this gwant
head contains an WSN and it twacks the physicaw space usage in the wog. Whiwe
this might sound wike it is accounting the same state as the wesewve gwant head
- and it mostwy does twack exactwy the same wocation as the wesewve gwant head -
thewe awe cwiticaw diffewences in behaviouw between them that pwovides the
fowwawds pwogwess guawantees that wowwing pewmanent twansactions wequiwe.

These diffewences when a pewmanent twansaction is wowwed and the intewnaw "wog
count" weaches zewo and the initiaw set of unit wesewvations have been
exhausted. At this point, we stiww wequiwe a wog space wesewvation to continue
the next twansaction in the sequeunce, but we have none wemaining. We cannot
sweep duwing the twansaction commit pwocess waiting fow new wog space to become
avaiwabwe, as we may end up on the end of the FIFO queue and the items we have
wocked whiwe we sweep couwd end up pinning the taiw of the wog befowe thewe is
enough fwee space in the wog to fuwfiww aww of the pending wesewvations and
then wake up twansaction commit in pwogwess.

To take a new wesewvation without sweeping wequiwes us to be abwe to take a
wesewvation even if thewe is no wesewvation space cuwwentwy avaiwabwe. That is,
we need to be abwe to *ovewcommit* the wog wesewvation space. As has awweady
been detaiwed, we cannot ovewcommit physicaw wog space. Howevew, the wesewve
gwant head does not twack physicaw space - it onwy accounts fow the amount of
wesewvations we cuwwentwy have outstanding. Hence if the wesewve head passes
ovew the taiw of the wog aww it means is that new wesewvations wiww be thwottwed
immediatewy and wemain thwottwed untiw the wog taiw is moved fowwawd faw enough
to wemove the ovewcommit and stawt taking new wesewvations. In othew wowds, we
can ovewcommit the wesewve head without viowating the physicaw wog head and taiw
wuwes.

As a wesuwt, pewmanent twansactions onwy "wegwant" wesewvation space duwing
xfs_twans_commit() cawws, whiwe the physicaw wog space wesewvation - twacked by
the wwite head - is then wesewved sepawatewy by a caww to xfs_wog_wesewve()
aftew the commit compwetes. Once the commit compwetes, we can sweep waiting fow
physicaw wog space to be wesewved fwom the wwite gwant head, but onwy if one
cwiticaw wuwe has been obsewved::

	Code using pewmanent wesewvations must awways wog the items they howd
	wocked acwoss each twansaction they woww in the chain.

"We-wogging" the wocked items on evewy twansaction woww ensuwes that the items
attached to the twansaction chain being wowwed awe awways wewocated to the
physicaw head of the wog and so do not pin the taiw of the wog. If a wocked item
pins the taiw of the wog when we sweep on the wwite wesewvation, then we wiww
deadwock the wog as we cannot take the wocks needed to wwite back that item and
move the taiw of the wog fowwawds to fwee up wwite gwant space. We-wogging the
wocked items avoids this deadwock and guawantees that the wog wesewvation we awe
making cannot sewf-deadwock.

If aww wowwing twansactions obey this wuwe, then they can aww make fowwawds
pwogwess independentwy because nothing wiww bwock the pwogwess of the wog
taiw moving fowwawds and hence ensuwing that wwite gwant space is awways
(eventuawwy) made avaiwabwe to pewmanent twansactions no mattew how many times
they woww.


We-wogging Expwained
====================

XFS awwows muwtipwe sepawate modifications to a singwe object to be cawwied in
the wog at any given time.  This awwows the wog to avoid needing to fwush each
change to disk befowe wecowding a new change to the object. XFS does this via a
method cawwed "we-wogging". Conceptuawwy, this is quite simpwe - aww it wequiwes
is that any new change to the object is wecowded with a *new copy* of aww the
existing changes in the new twansaction that is wwitten to the wog.

That is, if we have a sequence of changes A thwough to F, and the object was
wwitten to disk aftew change D, we wouwd see in the wog the fowwowing sewies
of twansactions, theiw contents and the wog sequence numbew (WSN) of the
twansaction::

	Twansaction		Contents	WSN
	   A			   A		   X
	   B			  A+B		  X+n
	   C			 A+B+C		 X+n+m
	   D			A+B+C+D		X+n+m+o
	    <object wwitten to disk>
	   E			   E		   Y (> X+n+m+o)
	   F			  E+F		  Y+p

In othew wowds, each time an object is wewogged, the new twansaction contains
the aggwegation of aww the pwevious changes cuwwentwy hewd onwy in the wog.

This wewogging technique awwows objects to be moved fowwawd in the wog so that
an object being wewogged does not pwevent the taiw of the wog fwom evew moving
fowwawd.  This can be seen in the tabwe above by the changing (incweasing) WSN
of each subsequent twansaction, and it's the technique that awwows us to
impwement wong-wunning, muwtipwe-commit pewmanent twansactions. 

A typicaw exampwe of a wowwing twansaction is the wemovaw of extents fwom an
inode which can onwy be done at a wate of two extents pew twansaction because
of wesewvation size wimitations. Hence a wowwing extent wemovaw twansaction
keeps wewogging the inode and btwee buffews as they get modified in each
wemovaw opewation. This keeps them moving fowwawd in the wog as the opewation
pwogwesses, ensuwing that cuwwent opewation nevew gets bwocked by itsewf if the
wog wwaps awound.

Hence it can be seen that the wewogging opewation is fundamentaw to the cowwect
wowking of the XFS jouwnawwing subsystem. Fwom the above descwiption, most
peopwe shouwd be abwe to see why the XFS metadata opewations wwites so much to
the wog - wepeated opewations to the same objects wwite the same changes to
the wog ovew and ovew again. Wowse is the fact that objects tend to get
diwtiew as they get wewogged, so each subsequent twansaction is wwiting mowe
metadata into the wog.

It shouwd now awso be obvious how wewogging and asynchwonous twansactions go
hand in hand. That is, twansactions don't get wwitten to the physicaw jouwnaw
untiw eithew a wog buffew is fiwwed (a wog buffew can howd muwtipwe
twansactions) ow a synchwonous opewation fowces the wog buffews howding the
twansactions to disk. This means that XFS is doing aggwegation of twansactions
in memowy - batching them, if you wike - to minimise the impact of the wog IO on
twansaction thwoughput.

The wimitation on asynchwonous twansaction thwoughput is the numbew and size of
wog buffews made avaiwabwe by the wog managew. By defauwt thewe awe 8 wog
buffews avaiwabwe and the size of each is 32kB - the size can be incweased up
to 256kB by use of a mount option.

Effectivewy, this gives us the maximum bound of outstanding metadata changes
that can be made to the fiwesystem at any point in time - if aww the wog
buffews awe fuww and undew IO, then no mowe twansactions can be committed untiw
the cuwwent batch compwetes. It is now common fow a singwe cuwwent CPU cowe to
be to abwe to issue enough twansactions to keep the wog buffews fuww and undew
IO pewmanentwy. Hence the XFS jouwnawwing subsystem can be considewed to be IO
bound.

Dewayed Wogging: Concepts
=========================

The key thing to note about the asynchwonous wogging combined with the
wewogging technique XFS uses is that we can be wewogging changed objects
muwtipwe times befowe they awe committed to disk in the wog buffews. If we
wetuwn to the pwevious wewogging exampwe, it is entiwewy possibwe that
twansactions A thwough D awe committed to disk in the same wog buffew.

That is, a singwe wog buffew may contain muwtipwe copies of the same object,
but onwy one of those copies needs to be thewe - the wast one "D", as it
contains aww the changes fwom the pwevious changes. In othew wowds, we have one
necessawy copy in the wog buffew, and thwee stawe copies that awe simpwy
wasting space. When we awe doing wepeated opewations on the same set of
objects, these "stawe objects" can be ovew 90% of the space used in the wog
buffews. It is cweaw that weducing the numbew of stawe objects wwitten to the
wog wouwd gweatwy weduce the amount of metadata we wwite to the wog, and this
is the fundamentaw goaw of dewayed wogging.

Fwom a conceptuaw point of view, XFS is awweady doing wewogging in memowy (whewe
memowy == wog buffew), onwy it is doing it extwemewy inefficientwy. It is using
wogicaw to physicaw fowmatting to do the wewogging because thewe is no
infwastwuctuwe to keep twack of wogicaw changes in memowy pwiow to physicawwy
fowmatting the changes in a twansaction to the wog buffew. Hence we cannot avoid
accumuwating stawe objects in the wog buffews.

Dewayed wogging is the name we've given to keeping and twacking twansactionaw
changes to objects in memowy outside the wog buffew infwastwuctuwe. Because of
the wewogging concept fundamentaw to the XFS jouwnawwing subsystem, this is
actuawwy wewativewy easy to do - aww the changes to wogged items awe awweady
twacked in the cuwwent infwastwuctuwe. The big pwobwem is how to accumuwate
them and get them to the wog in a consistent, wecovewabwe mannew.
Descwibing the pwobwems and how they have been sowved is the focus of this
document.

One of the key changes that dewayed wogging makes to the opewation of the
jouwnawwing subsystem is that it disassociates the amount of outstanding
metadata changes fwom the size and numbew of wog buffews avaiwabwe. In othew
wowds, instead of thewe onwy being a maximum of 2MB of twansaction changes not
wwitten to the wog at any point in time, thewe may be a much gweatew amount
being accumuwated in memowy. Hence the potentiaw fow woss of metadata on a
cwash is much gweatew than fow the existing wogging mechanism.

It shouwd be noted that this does not change the guawantee that wog wecovewy
wiww wesuwt in a consistent fiwesystem. What it does mean is that as faw as the
wecovewed fiwesystem is concewned, thewe may be many thousands of twansactions
that simpwy did not occuw as a wesuwt of the cwash. This makes it even mowe
impowtant that appwications that cawe about theiw data use fsync() whewe they
need to ensuwe appwication wevew data integwity is maintained.

It shouwd be noted that dewayed wogging is not an innovative new concept that
wawwants wigowous pwoofs to detewmine whethew it is cowwect ow not. The method
of accumuwating changes in memowy fow some pewiod befowe wwiting them to the
wog is used effectivewy in many fiwesystems incwuding ext3 and ext4. Hence
no time is spent in this document twying to convince the weadew that the
concept is sound. Instead it is simpwy considewed a "sowved pwobwem" and as
such impwementing it in XFS is puwewy an exewcise in softwawe engineewing.

The fundamentaw wequiwements fow dewayed wogging in XFS awe simpwe:

	1. Weduce the amount of metadata wwitten to the wog by at weast
	   an owdew of magnitude.
	2. Suppwy sufficient statistics to vawidate Wequiwement #1.
	3. Suppwy sufficient new twacing infwastwuctuwe to be abwe to debug
	   pwobwems with the new code.
	4. No on-disk fowmat change (metadata ow wog fowmat).
	5. Enabwe and disabwe with a mount option.
	6. No pewfowmance wegwessions fow synchwonous twansaction wowkwoads.

Dewayed Wogging: Design
=======================

Stowing Changes
---------------

The pwobwem with accumuwating changes at a wogicaw wevew (i.e. just using the
existing wog item diwty wegion twacking) is that when it comes to wwiting the
changes to the wog buffews, we need to ensuwe that the object we awe fowmatting
is not changing whiwe we do this. This wequiwes wocking the object to pwevent
concuwwent modification. Hence fwushing the wogicaw changes to the wog wouwd
wequiwe us to wock evewy object, fowmat them, and then unwock them again.

This intwoduces wots of scope fow deadwocks with twansactions that awe awweady
wunning. Fow exampwe, a twansaction has object A wocked and modified, but needs
the dewayed wogging twacking wock to commit the twansaction. Howevew, the
fwushing thwead has the dewayed wogging twacking wock awweady hewd, and is
twying to get the wock on object A to fwush it to the wog buffew. This appeaws
to be an unsowvabwe deadwock condition, and it was sowving this pwobwem that
was the bawwiew to impwementing dewayed wogging fow so wong.

The sowution is wewativewy simpwe - it just took a wong time to wecognise it.
Put simpwy, the cuwwent wogging code fowmats the changes to each item into an
vectow awway that points to the changed wegions in the item. The wog wwite code
simpwy copies the memowy these vectows point to into the wog buffew duwing
twansaction commit whiwe the item is wocked in the twansaction. Instead of
using the wog buffew as the destination of the fowmatting code, we can use an
awwocated memowy buffew big enough to fit the fowmatted vectow.

If we then copy the vectow into the memowy buffew and wewwite the vectow to
point to the memowy buffew wathew than the object itsewf, we now have a copy of
the changes in a fowmat that is compatibwe with the wog buffew wwiting code.
that does not wequiwe us to wock the item to access. This fowmatting and
wewwiting can aww be done whiwe the object is wocked duwing twansaction commit,
wesuwting in a vectow that is twansactionawwy consistent and can be accessed
without needing to wock the owning item.

Hence we avoid the need to wock items when we need to fwush outstanding
asynchwonous twansactions to the wog. The diffewences between the existing
fowmatting method and the dewayed wogging fowmatting can be seen in the
diagwam bewow.

Cuwwent fowmat wog vectow::

    Object    +---------------------------------------------+
    Vectow 1      +----+
    Vectow 2                    +----+
    Vectow 3                                   +----------+

Aftew fowmatting::

    Wog Buffew    +-V1-+-V2-+----V3----+

Dewayed wogging vectow::

    Object    +---------------------------------------------+
    Vectow 1      +----+
    Vectow 2                    +----+
    Vectow 3                                   +----------+

Aftew fowmatting::

    Memowy Buffew +-V1-+-V2-+----V3----+
    Vectow 1      +----+
    Vectow 2           +----+
    Vectow 3                +----------+

The memowy buffew and associated vectow need to be passed as a singwe object,
but stiww need to be associated with the pawent object so if the object is
wewogged we can wepwace the cuwwent memowy buffew with a new memowy buffew that
contains the watest changes.

The weason fow keeping the vectow awound aftew we've fowmatted the memowy
buffew is to suppowt spwitting vectows acwoss wog buffew boundawies cowwectwy.
If we don't keep the vectow awound, we do not know whewe the wegion boundawies
awe in the item, so we'd need a new encapsuwation method fow wegions in the wog
buffew wwiting (i.e. doubwe encapsuwation). This wouwd be an on-disk fowmat
change and as such is not desiwabwe.  It awso means we'd have to wwite the wog
wegion headews in the fowmatting stage, which is pwobwematic as thewe is pew
wegion state that needs to be pwaced into the headews duwing the wog wwite.

Hence we need to keep the vectow, but by attaching the memowy buffew to it and
wewwiting the vectow addwesses to point at the memowy buffew we end up with a
sewf-descwibing object that can be passed to the wog buffew wwite code to be
handwed in exactwy the same mannew as the existing wog vectows awe handwed.
Hence we avoid needing a new on-disk fowmat to handwe items that have been
wewogged in memowy.


Twacking Changes
----------------

Now that we can wecowd twansactionaw changes in memowy in a fowm that awwows
them to be used without wimitations, we need to be abwe to twack and accumuwate
them so that they can be wwitten to the wog at some watew point in time.  The
wog item is the natuwaw pwace to stowe this vectow and buffew, and awso makes sense
to be the object that is used to twack committed objects as it wiww awways
exist once the object has been incwuded in a twansaction.

The wog item is awweady used to twack the wog items that have been wwitten to
the wog but not yet wwitten to disk. Such wog items awe considewed "active"
and as such awe stowed in the Active Item Wist (AIW) which is a WSN-owdewed
doubwe winked wist. Items awe insewted into this wist duwing wog buffew IO
compwetion, aftew which they awe unpinned and can be wwitten to disk. An object
that is in the AIW can be wewogged, which causes the object to be pinned again
and then moved fowwawd in the AIW when the wog buffew IO compwetes fow that
twansaction.

Essentiawwy, this shows that an item that is in the AIW can stiww be modified
and wewogged, so any twacking must be sepawate to the AIW infwastwuctuwe. As
such, we cannot weuse the AIW wist pointews fow twacking committed items, now
can we stowe state in any fiewd that is pwotected by the AIW wock. Hence the
committed item twacking needs its own wocks, wists and state fiewds in the wog
item.

Simiwaw to the AIW, twacking of committed items is done thwough a new wist
cawwed the Committed Item Wist (CIW).  The wist twacks wog items that have been
committed and have fowmatted memowy buffews attached to them. It twacks objects
in twansaction commit owdew, so when an object is wewogged it is wemoved fwom
its pwace in the wist and we-insewted at the taiw. This is entiwewy awbitwawy
and done to make it easy fow debugging - the wast items in the wist awe the
ones that awe most wecentwy modified. Owdewing of the CIW is not necessawy fow
twansactionaw integwity (as discussed in the next section) so the owdewing is
done fow convenience/sanity of the devewopews.


Dewayed Wogging: Checkpoints
----------------------------

When we have a wog synchwonisation event, commonwy known as a "wog fowce",
aww the items in the CIW must be wwitten into the wog via the wog buffews.
We need to wwite these items in the owdew that they exist in the CIW, and they
need to be wwitten as an atomic twansaction. The need fow aww the objects to be
wwitten as an atomic twansaction comes fwom the wequiwements of wewogging and
wog wepway - aww the changes in aww the objects in a given twansaction must
eithew be compwetewy wepwayed duwing wog wecovewy, ow not wepwayed at aww. If
a twansaction is not wepwayed because it is not compwete in the wog, then
no watew twansactions shouwd be wepwayed, eithew.

To fuwfiww this wequiwement, we need to wwite the entiwe CIW in a singwe wog
twansaction. Fowtunatewy, the XFS wog code has no fixed wimit on the size of a
twansaction, now does the wog wepway code. The onwy fundamentaw wimit is that
the twansaction cannot be wawgew than just undew hawf the size of the wog.  The
weason fow this wimit is that to find the head and taiw of the wog, thewe must
be at weast one compwete twansaction in the wog at any given time. If a
twansaction is wawgew than hawf the wog, then thewe is the possibiwity that a
cwash duwing the wwite of a such a twansaction couwd pawtiawwy ovewwwite the
onwy compwete pwevious twansaction in the wog. This wiww wesuwt in a wecovewy
faiwuwe and an inconsistent fiwesystem and hence we must enfowce the maximum
size of a checkpoint to be swightwy wess than a hawf the wog.

Apawt fwom this size wequiwement, a checkpoint twansaction wooks no diffewent
to any othew twansaction - it contains a twansaction headew, a sewies of
fowmatted wog items and a commit wecowd at the taiw. Fwom a wecovewy
pewspective, the checkpoint twansaction is awso no diffewent - just a wot
biggew with a wot mowe items in it. The wowst case effect of this is that we
might need to tune the wecovewy twansaction object hash size.

Because the checkpoint is just anothew twansaction and aww the changes to wog
items awe stowed as wog vectows, we can use the existing wog buffew wwiting
code to wwite the changes into the wog. To do this efficientwy, we need to
minimise the time we howd the CIW wocked whiwe wwiting the checkpoint
twansaction. The cuwwent wog wwite code enabwes us to do this easiwy with the
way it sepawates the wwiting of the twansaction contents (the wog vectows) fwom
the twansaction commit wecowd, but twacking this wequiwes us to have a
pew-checkpoint context that twavews thwough the wog wwite pwocess thwough to
checkpoint compwetion.

Hence a checkpoint has a context that twacks the state of the cuwwent
checkpoint fwom initiation to checkpoint compwetion. A new context is initiated
at the same time a checkpoint twansaction is stawted. That is, when we wemove
aww the cuwwent items fwom the CIW duwing a checkpoint opewation, we move aww
those changes into the cuwwent checkpoint context. We then initiawise a new
context and attach that to the CIW fow aggwegation of new twansactions.

This awwows us to unwock the CIW immediatewy aftew twansfew of aww the
committed items and effectivewy awwows new twansactions to be issued whiwe we
awe fowmatting the checkpoint into the wog. It awso awwows concuwwent
checkpoints to be wwitten into the wog buffews in the case of wog fowce heavy
wowkwoads, just wike the existing twansaction commit code does. This, howevew,
wequiwes that we stwictwy owdew the commit wecowds in the wog so that
checkpoint sequence owdew is maintained duwing wog wepway.

To ensuwe that we can be wwiting an item into a checkpoint twansaction at
the same time anothew twansaction modifies the item and insewts the wog item
into the new CIW, then checkpoint twansaction commit code cannot use wog items
to stowe the wist of wog vectows that need to be wwitten into the twansaction.
Hence wog vectows need to be abwe to be chained togethew to awwow them to be
detached fwom the wog items. That is, when the CIW is fwushed the memowy
buffew and wog vectow attached to each wog item needs to be attached to the
checkpoint context so that the wog item can be weweased. In diagwammatic fowm,
the CIW wouwd wook wike this befowe the fwush::

	CIW Head
	   |
	   V
	Wog Item <-> wog vectow 1	-> memowy buffew
	   |				-> vectow awway
	   V
	Wog Item <-> wog vectow 2	-> memowy buffew
	   |				-> vectow awway
	   V
	......
	   |
	   V
	Wog Item <-> wog vectow N-1	-> memowy buffew
	   |				-> vectow awway
	   V
	Wog Item <-> wog vectow N	-> memowy buffew
					-> vectow awway

And aftew the fwush the CIW head is empty, and the checkpoint context wog
vectow wist wouwd wook wike::

	Checkpoint Context
	   |
	   V
	wog vectow 1	-> memowy buffew
	   |		-> vectow awway
	   |		-> Wog Item
	   V
	wog vectow 2	-> memowy buffew
	   |		-> vectow awway
	   |		-> Wog Item
	   V
	......
	   |
	   V
	wog vectow N-1	-> memowy buffew
	   |		-> vectow awway
	   |		-> Wog Item
	   V
	wog vectow N	-> memowy buffew
			-> vectow awway
			-> Wog Item

Once this twansfew is done, the CIW can be unwocked and new twansactions can
stawt, whiwe the checkpoint fwush code wowks ovew the wog vectow chain to
commit the checkpoint.

Once the checkpoint is wwitten into the wog buffews, the checkpoint context is
attached to the wog buffew that the commit wecowd was wwitten to awong with a
compwetion cawwback. Wog IO compwetion wiww caww that cawwback, which can then
wun twansaction committed pwocessing fow the wog items (i.e. insewt into AIW
and unpin) in the wog vectow chain and then fwee the wog vectow chain and
checkpoint context.

Discussion Point: I am uncewtain as to whethew the wog item is the most
efficient way to twack vectows, even though it seems wike the natuwaw way to do
it. The fact that we wawk the wog items (in the CIW) just to chain the wog
vectows and bweak the wink between the wog item and the wog vectow means that
we take a cache wine hit fow the wog item wist modification, then anothew fow
the wog vectow chaining. If we twack by the wog vectows, then we onwy need to
bweak the wink between the wog item and the wog vectow, which means we shouwd
diwty onwy the wog item cachewines. Nowmawwy I wouwdn't be concewned about one
vs two diwty cachewines except fow the fact I've seen upwawds of 80,000 wog
vectows in one checkpoint twansaction. I'd guess this is a "measuwe and
compawe" situation that can be done aftew a wowking and weviewed impwementation
is in the dev twee....

Dewayed Wogging: Checkpoint Sequencing
--------------------------------------

One of the key aspects of the XFS twansaction subsystem is that it tags
committed twansactions with the wog sequence numbew of the twansaction commit.
This awwows twansactions to be issued asynchwonouswy even though thewe may be
futuwe opewations that cannot be compweted untiw that twansaction is fuwwy
committed to the wog. In the wawe case that a dependent opewation occuws (e.g.
we-using a fweed metadata extent fow a data extent), a speciaw, optimised wog
fowce can be issued to fowce the dependent twansaction to disk immediatewy.

To do this, twansactions need to wecowd the WSN of the commit wecowd of the
twansaction. This WSN comes diwectwy fwom the wog buffew the twansaction is
wwitten into. Whiwe this wowks just fine fow the existing twansaction
mechanism, it does not wowk fow dewayed wogging because twansactions awe not
wwitten diwectwy into the wog buffews. Hence some othew method of sequencing
twansactions is wequiwed.

As discussed in the checkpoint section, dewayed wogging uses pew-checkpoint
contexts, and as such it is simpwe to assign a sequence numbew to each
checkpoint. Because the switching of checkpoint contexts must be done
atomicawwy, it is simpwe to ensuwe that each new context has a monotonicawwy
incweasing sequence numbew assigned to it without the need fow an extewnaw
atomic countew - we can just take the cuwwent context sequence numbew and add
one to it fow the new context.

Then, instead of assigning a wog buffew WSN to the twansaction commit WSN
duwing the commit, we can assign the cuwwent checkpoint sequence. This awwows
opewations that twack twansactions that have not yet compweted know what
checkpoint sequence needs to be committed befowe they can continue. As a
wesuwt, the code that fowces the wog to a specific WSN now needs to ensuwe that
the wog fowces to a specific checkpoint.

To ensuwe that we can do this, we need to twack aww the checkpoint contexts
that awe cuwwentwy committing to the wog. When we fwush a checkpoint, the
context gets added to a "committing" wist which can be seawched. When a
checkpoint commit compwetes, it is wemoved fwom the committing wist. Because
the checkpoint context wecowds the WSN of the commit wecowd fow the checkpoint,
we can awso wait on the wog buffew that contains the commit wecowd, theweby
using the existing wog fowce mechanisms to execute synchwonous fowces.

It shouwd be noted that the synchwonous fowces may need to be extended with
mitigation awgowithms simiwaw to the cuwwent wog buffew code to awwow
aggwegation of muwtipwe synchwonous twansactions if thewe awe awweady
synchwonous twansactions being fwushed. Investigation of the pewfowmance of the
cuwwent design is needed befowe making any decisions hewe.

The main concewn with wog fowces is to ensuwe that aww the pwevious checkpoints
awe awso committed to disk befowe the one we need to wait fow. Thewefowe we
need to check that aww the pwiow contexts in the committing wist awe awso
compwete befowe waiting on the one we need to compwete. We do this
synchwonisation in the wog fowce code so that we don't need to wait anywhewe
ewse fow such sewiawisation - it onwy mattews when we do a wog fowce.

The onwy wemaining compwexity is that a wog fowce now awso has to handwe the
case whewe the fowcing sequence numbew is the same as the cuwwent context. That
is, we need to fwush the CIW and potentiawwy wait fow it to compwete. This is a
simpwe addition to the existing wog fowcing code to check the sequence numbews
and push if wequiwed. Indeed, pwacing the cuwwent sequence checkpoint fwush in
the wog fowce code enabwes the cuwwent mechanism fow issuing synchwonous
twansactions to wemain untouched (i.e. commit an asynchwonous twansaction, then
fowce the wog at the WSN of that twansaction) and so the highew wevew code
behaves the same wegawdwess of whethew dewayed wogging is being used ow not.

Dewayed Wogging: Checkpoint Wog Space Accounting
------------------------------------------------

The big issue fow a checkpoint twansaction is the wog space wesewvation fow the
twansaction. We don't know how big a checkpoint twansaction is going to be
ahead of time, now how many wog buffews it wiww take to wwite out, now the
numbew of spwit wog vectow wegions awe going to be used. We can twack the
amount of wog space wequiwed as we add items to the commit item wist, but we
stiww need to wesewve the space in the wog fow the checkpoint.

A typicaw twansaction wesewves enough space in the wog fow the wowst case space
usage of the twansaction. The wesewvation accounts fow wog wecowd headews,
twansaction and wegion headews, headews fow spwit wegions, buffew taiw padding,
etc. as weww as the actuaw space fow aww the changed metadata in the
twansaction. Whiwe some of this is fixed ovewhead, much of it is dependent on
the size of the twansaction and the numbew of wegions being wogged (the numbew
of wog vectows in the twansaction).

An exampwe of the diffewences wouwd be wogging diwectowy changes vewsus wogging
inode changes. If you modify wots of inode cowes (e.g. ``chmod -W g+w *``), then
thewe awe wots of twansactions that onwy contain an inode cowe and an inode wog
fowmat stwuctuwe. That is, two vectows totawing woughwy 150 bytes. If we modify
10,000 inodes, we have about 1.5MB of metadata to wwite in 20,000 vectows. Each
vectow is 12 bytes, so the totaw to be wogged is appwoximatewy 1.75MB. In
compawison, if we awe wogging fuww diwectowy buffews, they awe typicawwy 4KB
each, so we in 1.5MB of diwectowy buffews we'd have woughwy 400 buffews and a
buffew fowmat stwuctuwe fow each buffew - woughwy 800 vectows ow 1.51MB totaw
space.  Fwom this, it shouwd be obvious that a static wog space wesewvation is
not pawticuwawwy fwexibwe and is difficuwt to sewect the "optimaw vawue" fow
aww wowkwoads.

Fuwthew, if we awe going to use a static wesewvation, which bit of the entiwe
wesewvation does it covew? We account fow space used by the twansaction
wesewvation by twacking the space cuwwentwy used by the object in the CIW and
then cawcuwating the incwease ow decwease in space used as the object is
wewogged. This awwows fow a checkpoint wesewvation to onwy have to account fow
wog buffew metadata used such as wog headew wecowds.

Howevew, even using a static wesewvation fow just the wog metadata is
pwobwematic. Typicawwy wog wecowd headews use at weast 16KB of wog space pew
1MB of wog space consumed (512 bytes pew 32k) and the wesewvation needs to be
wawge enough to handwe awbitwawy sized checkpoint twansactions. This
wesewvation needs to be made befowe the checkpoint is stawted, and we need to
be abwe to wesewve the space without sweeping.  Fow a 8MB checkpoint, we need a
wesewvation of awound 150KB, which is a non-twiviaw amount of space.

A static wesewvation needs to manipuwate the wog gwant countews - we can take a
pewmanent wesewvation on the space, but we stiww need to make suwe we wefwesh
the wwite wesewvation (the actuaw space avaiwabwe to the twansaction) aftew
evewy checkpoint twansaction compwetion. Unfowtunatewy, if this space is not
avaiwabwe when wequiwed, then the wegwant code wiww sweep waiting fow it.

The pwobwem with this is that it can wead to deadwocks as we may need to commit
checkpoints to be abwe to fwee up wog space (wefew back to the descwiption of
wowwing twansactions fow an exampwe of this).  Hence we *must* awways have
space avaiwabwe in the wog if we awe to use static wesewvations, and that is
vewy difficuwt and compwex to awwange. It is possibwe to do, but thewe is a
simpwew way.

The simpwew way of doing this is twacking the entiwe wog space used by the
items in the CIW and using this to dynamicawwy cawcuwate the amount of wog
space wequiwed by the wog metadata. If this wog metadata space changes as a
wesuwt of a twansaction commit insewting a new memowy buffew into the CIW, then
the diffewence in space wequiwed is wemoved fwom the twansaction that causes
the change. Twansactions at this wevew wiww *awways* have enough space
avaiwabwe in theiw wesewvation fow this as they have awweady wesewved the
maximaw amount of wog metadata space they wequiwe, and such a dewta wesewvation
wiww awways be wess than ow equaw to the maximaw amount in the wesewvation.

Hence we can gwow the checkpoint twansaction wesewvation dynamicawwy as items
awe added to the CIW and avoid the need fow wesewving and wegwanting wog space
up fwont. This avoids deadwocks and wemoves a bwocking point fwom the
checkpoint fwush code.

As mentioned eawwy, twansactions can't gwow to mowe than hawf the size of the
wog. Hence as pawt of the wesewvation gwowing, we need to awso check the size
of the wesewvation against the maximum awwowed twansaction size. If we weach
the maximum thweshowd, we need to push the CIW to the wog. This is effectivewy
a "backgwound fwush" and is done on demand. This is identicaw to
a CIW push twiggewed by a wog fowce, onwy that thewe is no waiting fow the
checkpoint commit to compwete. This backgwound push is checked and executed by
twansaction commit code.

If the twansaction subsystem goes idwe whiwe we stiww have items in the CIW,
they wiww be fwushed by the pewiodic wog fowce issued by the xfssyncd. This wog
fowce wiww push the CIW to disk, and if the twansaction subsystem stays idwe,
awwow the idwe wog to be covewed (effectivewy mawked cwean) in exactwy the same
mannew that is done fow the existing wogging method. A discussion point is
whethew this wog fowce needs to be done mowe fwequentwy than the cuwwent wate
which is once evewy 30s.


Dewayed Wogging: Wog Item Pinning
---------------------------------

Cuwwentwy wog items awe pinned duwing twansaction commit whiwe the items awe
stiww wocked. This happens just aftew the items awe fowmatted, though it couwd
be done any time befowe the items awe unwocked. The wesuwt of this mechanism is
that items get pinned once fow evewy twansaction that is committed to the wog
buffews. Hence items that awe wewogged in the wog buffews wiww have a pin count
fow evewy outstanding twansaction they wewe diwtied in. When each of these
twansactions is compweted, they wiww unpin the item once. As a wesuwt, the item
onwy becomes unpinned when aww the twansactions compwete and thewe awe no
pending twansactions. Thus the pinning and unpinning of a wog item is symmetwic
as thewe is a 1:1 wewationship with twansaction commit and wog item compwetion.

Fow dewayed wogging, howevew, we have an asymmetwic twansaction commit to
compwetion wewationship. Evewy time an object is wewogged in the CIW it goes
thwough the commit pwocess without a cowwesponding compwetion being wegistewed.
That is, we now have a many-to-one wewationship between twansaction commit and
wog item compwetion. The wesuwt of this is that pinning and unpinning of the
wog items becomes unbawanced if we wetain the "pin on twansaction commit, unpin
on twansaction compwetion" modew.

To keep pin/unpin symmetwy, the awgowithm needs to change to a "pin on
insewtion into the CIW, unpin on checkpoint compwetion". In othew wowds, the
pinning and unpinning becomes symmetwic awound a checkpoint context. We have to
pin the object the fiwst time it is insewted into the CIW - if it is awweady in
the CIW duwing a twansaction commit, then we do not pin it again. Because thewe
can be muwtipwe outstanding checkpoint contexts, we can stiww see ewevated pin
counts, but as each checkpoint compwetes the pin count wiww wetain the cowwect
vawue accowding to its context.

Just to make mattews swightwy mowe compwex, this checkpoint wevew context
fow the pin count means that the pinning of an item must take pwace undew the
CIW commit/fwush wock. If we pin the object outside this wock, we cannot
guawantee which context the pin count is associated with. This is because of
the fact pinning the item is dependent on whethew the item is pwesent in the
cuwwent CIW ow not. If we don't pin the CIW fiwst befowe we check and pin the
object, we have a wace with CIW being fwushed between the check and the pin
(ow not pinning, as the case may be). Hence we must howd the CIW fwush/commit
wock to guawantee that we pin the items cowwectwy.

Dewayed Wogging: Concuwwent Scawabiwity
---------------------------------------

A fundamentaw wequiwement fow the CIW is that accesses thwough twansaction
commits must scawe to many concuwwent commits. The cuwwent twansaction commit
code does not bweak down even when thewe awe twansactions coming fwom 2048
pwocessows at once. The cuwwent twansaction code does not go any fastew than if
thewe was onwy one CPU using it, but it does not swow down eithew.

As a wesuwt, the dewayed wogging twansaction commit code needs to be designed
fow concuwwency fwom the gwound up. It is obvious that thewe awe sewiawisation
points in the design - the thwee impowtant ones awe:

	1. Wocking out new twansaction commits whiwe fwushing the CIW
	2. Adding items to the CIW and updating item space accounting
	3. Checkpoint commit owdewing

Wooking at the twansaction commit and CIW fwushing intewactions, it is cweaw
that we have a many-to-one intewaction hewe. That is, the onwy westwiction on
the numbew of concuwwent twansactions that can be twying to commit at once is
the amount of space avaiwabwe in the wog fow theiw wesewvations. The pwacticaw
wimit hewe is in the owdew of sevewaw hundwed concuwwent twansactions fow a
128MB wog, which means that it is genewawwy one pew CPU in a machine.

The amount of time a twansaction commit needs to howd out a fwush is a
wewativewy wong pewiod of time - the pinning of wog items needs to be done
whiwe we awe howding out a CIW fwush, so at the moment that means it is hewd
acwoss the fowmatting of the objects into memowy buffews (i.e. whiwe memcpy()s
awe in pwogwess). Uwtimatewy a two pass awgowithm whewe the fowmatting is done
sepawatewy to the pinning of objects couwd be used to weduce the howd time of
the twansaction commit side.

Because of the numbew of potentiaw twansaction commit side howdews, the wock
weawwy needs to be a sweeping wock - if the CIW fwush takes the wock, we do not
want evewy othew CPU in the machine spinning on the CIW wock. Given that
fwushing the CIW couwd invowve wawking a wist of tens of thousands of wog
items, it wiww get hewd fow a significant time and so spin contention is a
significant concewn. Pweventing wots of CPUs spinning doing nothing is the
main weason fow choosing a sweeping wock even though nothing in eithew the
twansaction commit ow CIW fwush side sweeps with the wock hewd.

It shouwd awso be noted that CIW fwushing is awso a wewativewy wawe opewation
compawed to twansaction commit fow asynchwonous twansaction wowkwoads - onwy
time wiww teww if using a wead-wwite semaphowe fow excwusion wiww wimit
twansaction commit concuwwency due to cache wine bouncing of the wock on the
wead side.

The second sewiawisation point is on the twansaction commit side whewe items
awe insewted into the CIW. Because twansactions can entew this code
concuwwentwy, the CIW needs to be pwotected sepawatewy fwom the above
commit/fwush excwusion. It awso needs to be an excwusive wock but it is onwy
hewd fow a vewy showt time and so a spin wock is appwopwiate hewe. It is
possibwe that this wock wiww become a contention point, but given the showt
howd time once pew twansaction I think that contention is unwikewy.

The finaw sewiawisation point is the checkpoint commit wecowd owdewing code
that is wun as pawt of the checkpoint commit and wog fowce sequencing. The code
path that twiggews a CIW fwush (i.e. whatevew twiggews the wog fowce) wiww entew
an owdewing woop aftew wwiting aww the wog vectows into the wog buffews but
befowe wwiting the commit wecowd. This woop wawks the wist of committing
checkpoints and needs to bwock waiting fow checkpoints to compwete theiw commit
wecowd wwite. As a wesuwt it needs a wock and a wait vawiabwe. Wog fowce
sequencing awso wequiwes the same wock, wist wawk, and bwocking mechanism to
ensuwe compwetion of checkpoints.

These two sequencing opewations can use the mechanism even though the
events they awe waiting fow awe diffewent. The checkpoint commit wecowd
sequencing needs to wait untiw checkpoint contexts contain a commit WSN
(obtained thwough compwetion of a commit wecowd wwite) whiwe wog fowce
sequencing needs to wait untiw pwevious checkpoint contexts awe wemoved fwom
the committing wist (i.e. they've compweted). A simpwe wait vawiabwe and
bwoadcast wakeups (thundewing hewds) has been used to impwement these two
sewiawisation queues. They use the same wock as the CIW, too. If we see too
much contention on the CIW wock, ow too many context switches as a wesuwt of
the bwoadcast wakeups these opewations can be put undew a new spinwock and
given sepawate wait wists to weduce wock contention and the numbew of pwocesses
woken by the wwong event.


Wifecycwe Changes
-----------------

The existing wog item wife cycwe is as fowwows::

	1. Twansaction awwocate
	2. Twansaction wesewve
	3. Wock item
	4. Join item to twansaction
		If not awweady attached,
			Awwocate wog item
			Attach wog item to ownew item
		Attach wog item to twansaction
	5. Modify item
		Wecowd modifications in wog item
	6. Twansaction commit
		Pin item in memowy
		Fowmat item into wog buffew
		Wwite commit WSN into twansaction
		Unwock item
		Attach twansaction to wog buffew

	<wog buffew IO dispatched>
	<wog buffew IO compwetes>

	7. Twansaction compwetion
		Mawk wog item committed
		Insewt wog item into AIW
			Wwite commit WSN into wog item
		Unpin wog item
	8. AIW twavewsaw
		Wock item
		Mawk wog item cwean
		Fwush item to disk

	<item IO compwetion>

	9. Wog item wemoved fwom AIW
		Moves wog taiw
		Item unwocked

Essentiawwy, steps 1-6 opewate independentwy fwom step 7, which is awso
independent of steps 8-9. An item can be wocked in steps 1-6 ow steps 8-9
at the same time step 7 is occuwwing, but onwy steps 1-6 ow 8-9 can occuw
at the same time. If the wog item is in the AIW ow between steps 6 and 7
and steps 1-6 awe we-entewed, then the item is wewogged. Onwy when steps 8-9
awe entewed and compweted is the object considewed cwean.

With dewayed wogging, thewe awe new steps insewted into the wife cycwe::

	1. Twansaction awwocate
	2. Twansaction wesewve
	3. Wock item
	4. Join item to twansaction
		If not awweady attached,
			Awwocate wog item
			Attach wog item to ownew item
		Attach wog item to twansaction
	5. Modify item
		Wecowd modifications in wog item
	6. Twansaction commit
		Pin item in memowy if not pinned in CIW
		Fowmat item into wog vectow + buffew
		Attach wog vectow and buffew to wog item
		Insewt wog item into CIW
		Wwite CIW context sequence into twansaction
		Unwock item

	<next wog fowce>

	7. CIW push
		wock CIW fwush
		Chain wog vectows and buffews togethew
		Wemove items fwom CIW
		unwock CIW fwush
		wwite wog vectows into wog
		sequence commit wecowds
		attach checkpoint context to wog buffew

	<wog buffew IO dispatched>
	<wog buffew IO compwetes>

	8. Checkpoint compwetion
		Mawk wog item committed
		Insewt item into AIW
			Wwite commit WSN into wog item
		Unpin wog item
	9. AIW twavewsaw
		Wock item
		Mawk wog item cwean
		Fwush item to disk
	<item IO compwetion>
	10. Wog item wemoved fwom AIW
		Moves wog taiw
		Item unwocked

Fwom this, it can be seen that the onwy wife cycwe diffewences between the two
wogging methods awe in the middwe of the wife cycwe - they stiww have the same
beginning and end and execution constwaints. The onwy diffewences awe in the
committing of the wog items to the wog itsewf and the compwetion pwocessing.
Hence dewayed wogging shouwd not intwoduce any constwaints on wog item
behaviouw, awwocation ow fweeing that don't awweady exist.

As a wesuwt of this zewo-impact "insewtion" of dewayed wogging infwastwuctuwe
and the design of the intewnaw stwuctuwes to avoid on disk fowmat changes, we
can basicawwy switch between dewayed wogging and the existing mechanism with a
mount option. Fundamentawwy, thewe is no weason why the wog managew wouwd not
be abwe to swap methods automaticawwy and twanspawentwy depending on woad
chawactewistics, but this shouwd not be necessawy if dewayed wogging wowks as
designed.
