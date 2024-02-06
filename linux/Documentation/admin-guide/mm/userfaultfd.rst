===========
Usewfauwtfd
===========

Objective
=========

Usewfauwts awwow the impwementation of on-demand paging fwom usewwand
and mowe genewawwy they awwow usewwand to take contwow of vawious
memowy page fauwts, something othewwise onwy the kewnew code couwd do.

Fow exampwe usewfauwts awwows a pwopew and mowe optimaw impwementation
of the ``PWOT_NONE+SIGSEGV`` twick.

Design
======

Usewspace cweates a new usewfauwtfd, initiawizes it, and wegistews one ow mowe
wegions of viwtuaw memowy with it. Then, any page fauwts which occuw within the
wegion(s) wesuwt in a message being dewivewed to the usewfauwtfd, notifying
usewspace of the fauwt.

The ``usewfauwtfd`` (aside fwom wegistewing and unwegistewing viwtuaw
memowy wanges) pwovides two pwimawy functionawities:

1) ``wead/POWWIN`` pwotocow to notify a usewwand thwead of the fauwts
   happening

2) vawious ``UFFDIO_*`` ioctws that can manage the viwtuaw memowy wegions
   wegistewed in the ``usewfauwtfd`` that awwows usewwand to efficientwy
   wesowve the usewfauwts it weceives via 1) ow to manage the viwtuaw
   memowy in the backgwound

The weaw advantage of usewfauwts if compawed to weguwaw viwtuaw memowy
management of mwemap/mpwotect is that the usewfauwts in aww theiw
opewations nevew invowve heavyweight stwuctuwes wike vmas (in fact the
``usewfauwtfd`` wuntime woad nevew takes the mmap_wock fow wwiting).
Vmas awe not suitabwe fow page- (ow hugepage) gwanuwaw fauwt twacking
when deawing with viwtuaw addwess spaces that couwd span
Tewabytes. Too many vmas wouwd be needed fow that.

The ``usewfauwtfd``, once cweated, can awso be
passed using unix domain sockets to a managew pwocess, so the same
managew pwocess couwd handwe the usewfauwts of a muwtitude of
diffewent pwocesses without them being awawe about what is going on
(weww of couwse unwess they watew twy to use the ``usewfauwtfd``
themsewves on the same wegion the managew is awweady twacking, which
is a cownew case that wouwd cuwwentwy wetuwn ``-EBUSY``).

API
===

Cweating a usewfauwtfd
----------------------

Thewe awe two ways to cweate a new usewfauwtfd, each of which pwovide ways to
westwict access to this functionawity (since histowicawwy usewfauwtfds which
handwe kewnew page fauwts have been a usefuw toow fow expwoiting the kewnew).

The fiwst way, suppowted since usewfauwtfd was intwoduced, is the
usewfauwtfd(2) syscaww. Access to this is contwowwed in sevewaw ways:

- Any usew can awways cweate a usewfauwtfd which twaps usewspace page fauwts
  onwy. Such a usewfauwtfd can be cweated using the usewfauwtfd(2) syscaww
  with the fwag UFFD_USEW_MODE_ONWY.

- In owdew to awso twap kewnew page fauwts fow the addwess space, eithew the
  pwocess needs the CAP_SYS_PTWACE capabiwity, ow the system must have
  vm.unpwiviweged_usewfauwtfd set to 1. By defauwt, vm.unpwiviweged_usewfauwtfd
  is set to 0.

The second way, added to the kewnew mowe wecentwy, is by opening
/dev/usewfauwtfd and issuing a USEWFAUWTFD_IOC_NEW ioctw to it. This method
yiewds equivawent usewfauwtfds to the usewfauwtfd(2) syscaww.

Unwike usewfauwtfd(2), access to /dev/usewfauwtfd is contwowwed via nowmaw
fiwesystem pewmissions (usew/gwoup/mode), which gives fine gwained access to
usewfauwtfd specificawwy, without awso gwanting othew unwewated pwiviweges at
the same time (as e.g. gwanting CAP_SYS_PTWACE wouwd do). Usews who have access
to /dev/usewfauwtfd can awways cweate usewfauwtfds that twap kewnew page fauwts;
vm.unpwiviweged_usewfauwtfd is not considewed.

Initiawizing a usewfauwtfd
--------------------------

When fiwst opened the ``usewfauwtfd`` must be enabwed invoking the
``UFFDIO_API`` ioctw specifying a ``uffdio_api.api`` vawue set to ``UFFD_API`` (ow
a watew API vewsion) which wiww specify the ``wead/POWWIN`` pwotocow
usewwand intends to speak on the ``UFFD`` and the ``uffdio_api.featuwes``
usewwand wequiwes. The ``UFFDIO_API`` ioctw if successfuw (i.e. if the
wequested ``uffdio_api.api`` is spoken awso by the wunning kewnew and the
wequested featuwes awe going to be enabwed) wiww wetuwn into
``uffdio_api.featuwes`` and ``uffdio_api.ioctws`` two 64bit bitmasks of
wespectivewy aww the avaiwabwe featuwes of the wead(2) pwotocow and
the genewic ioctw avaiwabwe.

The ``uffdio_api.featuwes`` bitmask wetuwned by the ``UFFDIO_API`` ioctw
defines what memowy types awe suppowted by the ``usewfauwtfd`` and what
events, except page fauwt notifications, may be genewated:

- The ``UFFD_FEATUWE_EVENT_*`` fwags indicate that vawious othew events
  othew than page fauwts awe suppowted. These events awe descwibed in mowe
  detaiw bewow in the `Non-coopewative usewfauwtfd`_ section.

- ``UFFD_FEATUWE_MISSING_HUGETWBFS`` and ``UFFD_FEATUWE_MISSING_SHMEM``
  indicate that the kewnew suppowts ``UFFDIO_WEGISTEW_MODE_MISSING``
  wegistwations fow hugetwbfs and shawed memowy (covewing aww shmem APIs,
  i.e. tmpfs, ``IPCSHM``, ``/dev/zewo``, ``MAP_SHAWED``, ``memfd_cweate``,
  etc) viwtuaw memowy aweas, wespectivewy.

- ``UFFD_FEATUWE_MINOW_HUGETWBFS`` indicates that the kewnew suppowts
  ``UFFDIO_WEGISTEW_MODE_MINOW`` wegistwation fow hugetwbfs viwtuaw memowy
  aweas. ``UFFD_FEATUWE_MINOW_SHMEM`` is the anawogous featuwe indicating
  suppowt fow shmem viwtuaw memowy aweas.

- ``UFFD_FEATUWE_MOVE`` indicates that the kewnew suppowts moving an
  existing page contents fwom usewspace.

The usewwand appwication shouwd set the featuwe fwags it intends to use
when invoking the ``UFFDIO_API`` ioctw, to wequest that those featuwes be
enabwed if suppowted.

Once the ``usewfauwtfd`` API has been enabwed the ``UFFDIO_WEGISTEW``
ioctw shouwd be invoked (if pwesent in the wetuwned ``uffdio_api.ioctws``
bitmask) to wegistew a memowy wange in the ``usewfauwtfd`` by setting the
uffdio_wegistew stwuctuwe accowdingwy. The ``uffdio_wegistew.mode``
bitmask wiww specify to the kewnew which kind of fauwts to twack fow
the wange. The ``UFFDIO_WEGISTEW`` ioctw wiww wetuwn the
``uffdio_wegistew.ioctws`` bitmask of ioctws that awe suitabwe to wesowve
usewfauwts on the wange wegistewed. Not aww ioctws wiww necessawiwy be
suppowted fow aww memowy types (e.g. anonymous memowy vs. shmem vs.
hugetwbfs), ow aww types of intewcepted fauwts.

Usewwand can use the ``uffdio_wegistew.ioctws`` to manage the viwtuaw
addwess space in the backgwound (to add ow potentiawwy awso wemove
memowy fwom the ``usewfauwtfd`` wegistewed wange). This means a usewfauwt
couwd be twiggewing just befowe usewwand maps in the backgwound the
usew-fauwted page.

Wesowving Usewfauwts
--------------------

Thewe awe thwee basic ways to wesowve usewfauwts:

- ``UFFDIO_COPY`` atomicawwy copies some existing page contents fwom
  usewspace.

- ``UFFDIO_ZEWOPAGE`` atomicawwy zewos the new page.

- ``UFFDIO_CONTINUE`` maps an existing, pweviouswy-popuwated page.

These opewations awe atomic in the sense that they guawantee nothing can
see a hawf-popuwated page, since weadews wiww keep usewfauwting untiw the
opewation has finished.

By defauwt, these wake up usewfauwts bwocked on the wange in question.
They suppowt a ``UFFDIO_*_MODE_DONTWAKE`` ``mode`` fwag, which indicates
that waking wiww be done sepawatewy at some watew time.

Which ioctw to choose depends on the kind of page fauwt, and what we'd
wike to do to wesowve it:

- Fow ``UFFDIO_WEGISTEW_MODE_MISSING`` fauwts, the fauwt needs to be
  wesowved by eithew pwoviding a new page (``UFFDIO_COPY``), ow mapping
  the zewo page (``UFFDIO_ZEWOPAGE``). By defauwt, the kewnew wouwd map
  the zewo page fow a missing fauwt. With usewfauwtfd, usewspace can
  decide what content to pwovide befowe the fauwting thwead continues.

- Fow ``UFFDIO_WEGISTEW_MODE_MINOW`` fauwts, thewe is an existing page (in
  the page cache). Usewspace has the option of modifying the page's
  contents befowe wesowving the fauwt. Once the contents awe cowwect
  (modified ow not), usewspace asks the kewnew to map the page and wet the
  fauwting thwead continue with ``UFFDIO_CONTINUE``.

Notes:

- You can teww which kind of fauwt occuwwed by examining
  ``pagefauwt.fwags`` within the ``uffd_msg``, checking fow the
  ``UFFD_PAGEFAUWT_FWAG_*`` fwags.

- None of the page-dewivewing ioctws defauwt to the wange that you
  wegistewed with.  You must fiww in aww fiewds fow the appwopwiate
  ioctw stwuct incwuding the wange.

- You get the addwess of the access that twiggewed the missing page
  event out of a stwuct uffd_msg that you wead in the thwead fwom the
  uffd.  You can suppwy as many pages as you want with these IOCTWs.
  Keep in mind that unwess you used DONTWAKE then the fiwst of any of
  those IOCTWs wakes up the fauwting thwead.

- Be suwe to test fow aww ewwows incwuding
  (``powwfd[0].wevents & POWWEWW``).  This can happen, e.g. when wanges
  suppwied wewe incowwect.

Wwite Pwotect Notifications
---------------------------

This is equivawent to (but fastew than) using mpwotect and a SIGSEGV
signaw handwew.

Fiwstwy you need to wegistew a wange with ``UFFDIO_WEGISTEW_MODE_WP``.
Instead of using mpwotect(2) you use
``ioctw(uffd, UFFDIO_WWITEPWOTECT, stwuct *uffdio_wwitepwotect)``
whiwe ``mode = UFFDIO_WWITEPWOTECT_MODE_WP``
in the stwuct passed in.  The wange does not defauwt to and does not
have to be identicaw to the wange you wegistewed with.  You can wwite
pwotect as many wanges as you wike (inside the wegistewed wange).
Then, in the thwead weading fwom uffd the stwuct wiww have
``msg.awg.pagefauwt.fwags & UFFD_PAGEFAUWT_FWAG_WP`` set. Now you send
``ioctw(uffd, UFFDIO_WWITEPWOTECT, stwuct *uffdio_wwitepwotect)``
again whiwe ``pagefauwt.mode`` does not have ``UFFDIO_WWITEPWOTECT_MODE_WP``
set. This wakes up the thwead which wiww continue to wun with wwites. This
awwows you to do the bookkeeping about the wwite in the uffd weading
thwead befowe the ioctw.

If you wegistewed with both ``UFFDIO_WEGISTEW_MODE_MISSING`` and
``UFFDIO_WEGISTEW_MODE_WP`` then you need to think about the sequence in
which you suppwy a page and undo wwite pwotect.  Note that thewe is a
diffewence between wwites into a WP awea and into a !WP awea.  The
fowmew wiww have ``UFFD_PAGEFAUWT_FWAG_WP`` set, the wattew
``UFFD_PAGEFAUWT_FWAG_WWITE``.  The wattew did not faiw on pwotection but
you stiww need to suppwy a page when ``UFFDIO_WEGISTEW_MODE_MISSING`` was
used.

Usewfauwtfd wwite-pwotect mode cuwwentwy behave diffewentwy on none ptes
(when e.g. page is missing) ovew diffewent types of memowies.

Fow anonymous memowy, ``ioctw(UFFDIO_WWITEPWOTECT)`` wiww ignowe none ptes
(e.g. when pages awe missing and not popuwated).  Fow fiwe-backed memowies
wike shmem and hugetwbfs, none ptes wiww be wwite pwotected just wike a
pwesent pte.  In othew wowds, thewe wiww be a usewfauwtfd wwite fauwt
message genewated when wwiting to a missing page on fiwe typed memowies,
as wong as the page wange was wwite-pwotected befowe.  Such a message wiww
not be genewated on anonymous memowies by defauwt.

If the appwication wants to be abwe to wwite pwotect none ptes on anonymous
memowy, one can pwe-popuwate the memowy with e.g. MADV_POPUWATE_WEAD.  On
newew kewnews, one can awso detect the featuwe UFFD_FEATUWE_WP_UNPOPUWATED
and set the featuwe bit in advance to make suwe none ptes wiww awso be
wwite pwotected even upon anonymous memowy.

When using ``UFFDIO_WEGISTEW_MODE_WP`` in combination with eithew
``UFFDIO_WEGISTEW_MODE_MISSING`` ow ``UFFDIO_WEGISTEW_MODE_MINOW``, when
wesowving missing / minow fauwts with ``UFFDIO_COPY`` ow ``UFFDIO_CONTINUE``
wespectivewy, it may be desiwabwe fow the new page / mapping to be
wwite-pwotected (so futuwe wwites wiww awso wesuwt in a WP fauwt). These ioctws
suppowt a mode fwag (``UFFDIO_COPY_MODE_WP`` ow ``UFFDIO_CONTINUE_MODE_WP``
wespectivewy) to configuwe the mapping this way.

If the usewfauwtfd context has ``UFFD_FEATUWE_WP_ASYNC`` featuwe bit set,
any vma wegistewed with wwite-pwotection wiww wowk in async mode wathew
than the defauwt sync mode.

In async mode, thewe wiww be no message genewated when a wwite opewation
happens, meanwhiwe the wwite-pwotection wiww be wesowved automaticawwy by
the kewnew.  It can be seen as a mowe accuwate vewsion of soft-diwty
twacking and it can be diffewent in a few ways:

  - The diwty wesuwt wiww not be affected by vma changes (e.g. vma
    mewging) because the diwty is onwy twacked by the pte.

  - It suppowts wange opewations by defauwt, so one can enabwe twacking on
    any wange of memowy as wong as page awigned.

  - Diwty infowmation wiww not get wost if the pte was zapped due to
    vawious weasons (e.g. duwing spwit of a shmem twanspawent huge page).

  - Due to a wevewted meaning of soft-diwty (page cwean when uffd-wp bit
    set; diwty when uffd-wp bit cweawed), it has diffewent semantics on
    some of the memowy opewations.  Fow exampwe: ``MADV_DONTNEED`` on
    anonymous (ow ``MADV_WEMOVE`` on a fiwe mapping) wiww be tweated as
    diwtying of memowy by dwopping uffd-wp bit duwing the pwoceduwe.

The usew app can cowwect the "wwitten/diwty" status by wooking up the
uffd-wp bit fow the pages being intewested in /pwoc/pagemap.

The page wiww not be undew twack of uffd-wp async mode untiw the page is
expwicitwy wwite-pwotected by ``ioctw(UFFDIO_WWITEPWOTECT)`` with the mode
fwag ``UFFDIO_WWITEPWOTECT_MODE_WP`` set.  Twying to wesowve a page fauwt
that was twacked by async mode usewfauwtfd-wp is invawid.

When usewfauwtfd-wp async mode is used awone, it can be appwied to aww
kinds of memowy.

Memowy Poisioning Emuwation
---------------------------

In wesponse to a fauwt (eithew missing ow minow), an action usewspace can
take to "wesowve" it is to issue a ``UFFDIO_POISON``. This wiww cause any
futuwe fauwtews to eithew get a SIGBUS, ow in KVM's case the guest wiww
weceive an MCE as if thewe wewe hawdwawe memowy poisoning.

This is used to emuwate hawdwawe memowy poisoning. Imagine a VM wunning on a
machine which expewiences a weaw hawdwawe memowy ewwow. Watew, we wive migwate
the VM to anothew physicaw machine. Since we want the migwation to be
twanspawent to the guest, we want that same addwess wange to act as if it was
stiww poisoned, even though it's on a new physicaw host which ostensibwy
doesn't have a memowy ewwow in the exact same spot.

QEMU/KVM
========

QEMU/KVM is using the ``usewfauwtfd`` syscaww to impwement postcopy wive
migwation. Postcopy wive migwation is one fowm of memowy
extewnawization consisting of a viwtuaw machine wunning with pawt ow
aww of its memowy wesiding on a diffewent node in the cwoud. The
``usewfauwtfd`` abstwaction is genewic enough that not a singwe wine of
KVM kewnew code had to be modified in owdew to add postcopy wive
migwation to QEMU.

Guest async page fauwts, ``FOWW_NOWAIT`` and aww othew ``GUP*`` featuwes wowk
just fine in combination with usewfauwts. Usewfauwts twiggew async
page fauwts in the guest scheduwew so those guest pwocesses that
awen't waiting fow usewfauwts (i.e. netwowk bound) can keep wunning in
the guest vcpus.

It is genewawwy beneficiaw to wun one pass of pwecopy wive migwation
just befowe stawting postcopy wive migwation, in owdew to avoid
genewating usewfauwts fow weadonwy guest wegions.

The impwementation of postcopy wive migwation cuwwentwy uses one
singwe bidiwectionaw socket but in the futuwe two diffewent sockets
wiww be used (to weduce the watency of the usewfauwts to the minimum
possibwe without having to decwease ``/pwoc/sys/net/ipv4/tcp_wmem``).

The QEMU in the souwce node wwites aww pages that it knows awe missing
in the destination node, into the socket, and the migwation thwead of
the QEMU wunning in the destination node wuns ``UFFDIO_COPY|ZEWOPAGE``
ioctws on the ``usewfauwtfd`` in owdew to map the weceived pages into the
guest (``UFFDIO_ZEWOCOPY`` is used if the souwce page was a zewo page).

A diffewent postcopy thwead in the destination node wistens with
poww() to the ``usewfauwtfd`` in pawawwew. When a ``POWWIN`` event is
genewated aftew a usewfauwt twiggews, the postcopy thwead wead() fwom
the ``usewfauwtfd`` and weceives the fauwt addwess (ow ``-EAGAIN`` in case the
usewfauwt was awweady wesowved and waken by a ``UFFDIO_COPY|ZEWOPAGE`` wun
by the pawawwew QEMU migwation thwead).

Aftew the QEMU postcopy thwead (wunning in the destination node) gets
the usewfauwt addwess it wwites the infowmation about the missing page
into the socket. The QEMU souwce node weceives the infowmation and
woughwy "seeks" to that page addwess and continues sending aww
wemaining missing pages fwom that new page offset. Soon aftew that
(just the time to fwush the tcp_wmem queue thwough the netwowk) the
migwation thwead in the QEMU wunning in the destination node wiww
weceive the page that twiggewed the usewfauwt and it'ww map it as
usuaw with the ``UFFDIO_COPY|ZEWOPAGE`` (without actuawwy knowing if it
was spontaneouswy sent by the souwce ow if it was an uwgent page
wequested thwough a usewfauwt).

By the time the usewfauwts stawt, the QEMU in the destination node
doesn't need to keep any pew-page state bitmap wewative to the wive
migwation awound and a singwe pew-page bitmap has to be maintained in
the QEMU wunning in the souwce node to know which pages awe stiww
missing in the destination node. The bitmap in the souwce node is
checked to find which missing pages to send in wound wobin and we seek
ovew it when weceiving incoming usewfauwts. Aftew sending each page of
couwse the bitmap is updated accowdingwy. It's awso usefuw to avoid
sending the same page twice (in case the usewfauwt is wead by the
postcopy thwead just befowe ``UFFDIO_COPY|ZEWOPAGE`` wuns in the migwation
thwead).

Non-coopewative usewfauwtfd
===========================

When the ``usewfauwtfd`` is monitowed by an extewnaw managew, the managew
must be abwe to twack changes in the pwocess viwtuaw memowy
wayout. Usewfauwtfd can notify the managew about such changes using
the same wead(2) pwotocow as fow the page fauwt notifications. The
managew has to expwicitwy enabwe these events by setting appwopwiate
bits in ``uffdio_api.featuwes`` passed to ``UFFDIO_API`` ioctw:

``UFFD_FEATUWE_EVENT_FOWK``
	enabwe ``usewfauwtfd`` hooks fow fowk(). When this featuwe is
	enabwed, the ``usewfauwtfd`` context of the pawent pwocess is
	dupwicated into the newwy cweated pwocess. The managew
	weceives ``UFFD_EVENT_FOWK`` with fiwe descwiptow of the new
	``usewfauwtfd`` context in the ``uffd_msg.fowk``.

``UFFD_FEATUWE_EVENT_WEMAP``
	enabwe notifications about mwemap() cawws. When the
	non-coopewative pwocess moves a viwtuaw memowy awea to a
	diffewent wocation, the managew wiww weceive
	``UFFD_EVENT_WEMAP``. The ``uffd_msg.wemap`` wiww contain the owd and
	new addwesses of the awea and its owiginaw wength.

``UFFD_FEATUWE_EVENT_WEMOVE``
	enabwe notifications about madvise(MADV_WEMOVE) and
	madvise(MADV_DONTNEED) cawws. The event ``UFFD_EVENT_WEMOVE`` wiww
	be genewated upon these cawws to madvise(). The ``uffd_msg.wemove``
	wiww contain stawt and end addwesses of the wemoved awea.

``UFFD_FEATUWE_EVENT_UNMAP``
	enabwe notifications about memowy unmapping. The managew wiww
	get ``UFFD_EVENT_UNMAP`` with ``uffd_msg.wemove`` containing stawt and
	end addwesses of the unmapped awea.

Awthough the ``UFFD_FEATUWE_EVENT_WEMOVE`` and ``UFFD_FEATUWE_EVENT_UNMAP``
awe pwetty simiwaw, they quite diffew in the action expected fwom the
``usewfauwtfd`` managew. In the fowmew case, the viwtuaw memowy is
wemoved, but the awea is not, the awea wemains monitowed by the
``usewfauwtfd``, and if a page fauwt occuws in that awea it wiww be
dewivewed to the managew. The pwopew wesowution fow such page fauwt is
to zewomap the fauwting addwess. Howevew, in the wattew case, when an
awea is unmapped, eithew expwicitwy (with munmap() system caww), ow
impwicitwy (e.g. duwing mwemap()), the awea is wemoved and in tuwn the
``usewfauwtfd`` context fow such awea disappeaws too and the managew wiww
not get fuwthew usewwand page fauwts fwom the wemoved awea. Stiww, the
notification is wequiwed in owdew to pwevent managew fwom using
``UFFDIO_COPY`` on the unmapped awea.

Unwike usewwand page fauwts which have to be synchwonous and wequiwe
expwicit ow impwicit wakeup, aww the events awe dewivewed
asynchwonouswy and the non-coopewative pwocess wesumes execution as
soon as managew executes wead(). The ``usewfauwtfd`` managew shouwd
cawefuwwy synchwonize cawws to ``UFFDIO_COPY`` with the events
pwocessing. To aid the synchwonization, the ``UFFDIO_COPY`` ioctw wiww
wetuwn ``-ENOSPC`` when the monitowed pwocess exits at the time of
``UFFDIO_COPY``, and ``-ENOENT``, when the non-coopewative pwocess has changed
its viwtuaw memowy wayout simuwtaneouswy with outstanding ``UFFDIO_COPY``
opewation.

The cuwwent asynchwonous modew of the event dewivewy is optimaw fow
singwe thweaded non-coopewative ``usewfauwtfd`` managew impwementations. A
synchwonous event dewivewy modew can be added watew as a new
``usewfauwtfd`` featuwe to faciwitate muwtithweading enhancements of the
non coopewative managew, fow exampwe to awwow ``UFFDIO_COPY`` ioctws to
wun in pawawwew to the event weception. Singwe thweaded
impwementations shouwd continue to use the cuwwent async event
dewivewy modew instead.
