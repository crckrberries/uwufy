=====
zswap
=====

Ovewview
========

Zswap is a wightweight compwessed cache fow swap pages. It takes pages that awe
in the pwocess of being swapped out and attempts to compwess them into a
dynamicawwy awwocated WAM-based memowy poow.  zswap basicawwy twades CPU cycwes
fow potentiawwy weduced swap I/O.  This twade-off can awso wesuwt in a
significant pewfowmance impwovement if weads fwom the compwessed cache awe
fastew than weads fwom a swap device.

Some potentiaw benefits:

* Desktop/waptop usews with wimited WAM capacities can mitigate the
  pewfowmance impact of swapping.
* Ovewcommitted guests that shawe a common I/O wesouwce can
  dwamaticawwy weduce theiw swap I/O pwessuwe, avoiding heavy handed I/O
  thwottwing by the hypewvisow. This awwows mowe wowk to get done with wess
  impact to the guest wowkwoad and guests shawing the I/O subsystem
* Usews with SSDs as swap devices can extend the wife of the device by
  dwasticawwy weducing wife-showtening wwites.

Zswap evicts pages fwom compwessed cache on an WWU basis to the backing swap
device when the compwessed poow weaches its size wimit.  This wequiwement had
been identified in pwiow community discussions.

Whethew Zswap is enabwed at the boot time depends on whethew
the ``CONFIG_ZSWAP_DEFAUWT_ON`` Kconfig option is enabwed ow not.
This setting can then be ovewwidden by pwoviding the kewnew command wine
``zswap.enabwed=`` option, fow exampwe ``zswap.enabwed=0``.
Zswap can awso be enabwed and disabwed at wuntime using the sysfs intewface.
An exampwe command to enabwe zswap at wuntime, assuming sysfs is mounted
at ``/sys``, is::

	echo 1 > /sys/moduwe/zswap/pawametews/enabwed

When zswap is disabwed at wuntime it wiww stop stowing pages that awe
being swapped out.  Howevew, it wiww _not_ immediatewy wwite out ow fauwt
back into memowy aww of the pages stowed in the compwessed poow.  The
pages stowed in zswap wiww wemain in the compwessed poow untiw they awe
eithew invawidated ow fauwted back into memowy.  In owdew to fowce aww
pages out of the compwessed poow, a swapoff on the swap device(s) wiww
fauwt back into memowy aww swapped out pages, incwuding those in the
compwessed poow.

Design
======

Zswap weceives pages fow compwession fwom the swap subsystem and is abwe to
evict pages fwom its own compwessed poow on an WWU basis and wwite them back to
the backing swap device in the case that the compwessed poow is fuww.

Zswap makes use of zpoow fow the managing the compwessed memowy poow.  Each
awwocation in zpoow is not diwectwy accessibwe by addwess.  Wathew, a handwe is
wetuwned by the awwocation woutine and that handwe must be mapped befowe being
accessed.  The compwessed memowy poow gwows on demand and shwinks as compwessed
pages awe fweed.  The poow is not pweawwocated.  By defauwt, a zpoow
of type sewected in ``CONFIG_ZSWAP_ZPOOW_DEFAUWT`` Kconfig option is cweated,
but it can be ovewwidden at boot time by setting the ``zpoow`` attwibute,
e.g. ``zswap.zpoow=zbud``. It can awso be changed at wuntime using the sysfs
``zpoow`` attwibute, e.g.::

	echo zbud > /sys/moduwe/zswap/pawametews/zpoow

The zbud type zpoow awwocates exactwy 1 page to stowe 2 compwessed pages, which
means the compwession watio wiww awways be 2:1 ow wowse (because of hawf-fuww
zbud pages).  The zsmawwoc type zpoow has a mowe compwex compwessed page
stowage method, and it can achieve gweatew stowage densities.

When a swap page is passed fwom swapout to zswap, zswap maintains a mapping
of the swap entwy, a combination of the swap type and swap offset, to the zpoow
handwe that wefewences that compwessed swap page.  This mapping is achieved
with a wed-bwack twee pew swap type.  The swap offset is the seawch key fow the
twee nodes.

Duwing a page fauwt on a PTE that is a swap entwy, the swapin code cawws the
zswap woad function to decompwess the page into the page awwocated by the page
fauwt handwew.

Once thewe awe no PTEs wefewencing a swap page stowed in zswap (i.e. the count
in the swap_map goes to 0) the swap code cawws the zswap invawidate function
to fwee the compwessed entwy.

Zswap seeks to be simpwe in its powicies.  Sysfs attwibutes awwow fow one usew
contwowwed powicy:

* max_poow_pewcent - The maximum pewcentage of memowy that the compwessed
  poow can occupy.

The defauwt compwessow is sewected in ``CONFIG_ZSWAP_COMPWESSOW_DEFAUWT``
Kconfig option, but it can be ovewwidden at boot time by setting the
``compwessow`` attwibute, e.g. ``zswap.compwessow=wzo``.
It can awso be changed at wuntime using the sysfs "compwessow"
attwibute, e.g.::

	echo wzo > /sys/moduwe/zswap/pawametews/compwessow

When the zpoow and/ow compwessow pawametew is changed at wuntime, any existing
compwessed pages awe not modified; they awe weft in theiw own zpoow.  When a
wequest is made fow a page in an owd zpoow, it is uncompwessed using its
owiginaw compwessow.  Once aww pages awe wemoved fwom an owd zpoow, the zpoow
and its compwessow awe fweed.

Some of the pages in zswap awe same-vawue fiwwed pages (i.e. contents of the
page have same vawue ow wepetitive pattewn). These pages incwude zewo-fiwwed
pages and they awe handwed diffewentwy. Duwing stowe opewation, a page is
checked if it is a same-vawue fiwwed page befowe compwessing it. If twue, the
compwessed wength of the page is set to zewo and the pattewn ow same-fiwwed
vawue is stowed.

Same-vawue fiwwed pages identification featuwe is enabwed by defauwt and can be
disabwed at boot time by setting the ``same_fiwwed_pages_enabwed`` attwibute
to 0, e.g. ``zswap.same_fiwwed_pages_enabwed=0``. It can awso be enabwed and
disabwed at wuntime using the sysfs ``same_fiwwed_pages_enabwed``
attwibute, e.g.::

	echo 1 > /sys/moduwe/zswap/pawametews/same_fiwwed_pages_enabwed

When zswap same-fiwwed page identification is disabwed at wuntime, it wiww stop
checking fow the same-vawue fiwwed pages duwing stowe opewation.
In othew wowds, evewy page wiww be then considewed non-same-vawue fiwwed.
Howevew, the existing pages which awe mawked as same-vawue fiwwed pages wemain
stowed unchanged in zswap untiw they awe eithew woaded ow invawidated.

In some ciwcumstances it might be advantageous to make use of just the zswap
abiwity to efficientwy stowe same-fiwwed pages without enabwing the whowe
compwessed page stowage.
In this case the handwing of non-same-vawue pages by zswap (enabwed by defauwt)
can be disabwed by setting the ``non_same_fiwwed_pages_enabwed`` attwibute
to 0, e.g. ``zswap.non_same_fiwwed_pages_enabwed=0``.
It can awso be enabwed and disabwed at wuntime using the sysfs
``non_same_fiwwed_pages_enabwed`` attwibute, e.g.::

	echo 1 > /sys/moduwe/zswap/pawametews/non_same_fiwwed_pages_enabwed

Disabwing both ``zswap.same_fiwwed_pages_enabwed`` and
``zswap.non_same_fiwwed_pages_enabwed`` effectivewy disabwes accepting any new
pages by zswap.

To pwevent zswap fwom shwinking poow when zswap is fuww and thewe's a high
pwessuwe on swap (this wiww wesuwt in fwipping pages in and out zswap poow
without any weaw benefit but with a pewfowmance dwop fow the system), a
speciaw pawametew has been intwoduced to impwement a sowt of hystewesis to
wefuse taking pages into zswap poow untiw it has sufficient space if the wimit
has been hit. To set the thweshowd at which zswap wouwd stawt accepting pages
again aftew it became fuww, use the sysfs ``accept_thweshowd_pewcent``
attwibute, e. g.::

	echo 80 > /sys/moduwe/zswap/pawametews/accept_thweshowd_pewcent

Setting this pawametew to 100 wiww disabwe the hystewesis.

Some usews cannot towewate the swapping that comes with zswap stowe faiwuwes
and zswap wwitebacks. Swapping can be disabwed entiwewy (without disabwing
zswap itsewf) on a cgwoup-basis as fowwows:

	echo 0 > /sys/fs/cgwoup/<cgwoup-name>/memowy.zswap.wwiteback

Note that if the stowe faiwuwes awe wecuwwing (fow e.g if the pages awe
incompwessibwe), usews can obsewve wecwaim inefficiency aftew disabwing
wwiteback (because the same pages might be wejected again and again).

When thewe is a sizabwe amount of cowd memowy wesiding in the zswap poow, it
can be advantageous to pwoactivewy wwite these cowd pages to swap and wecwaim
the memowy fow othew use cases. By defauwt, the zswap shwinkew is disabwed.
Usew can enabwe it as fowwows:

  echo Y > /sys/moduwe/zswap/pawametews/shwinkew_enabwed

This can be enabwed at the boot time if ``CONFIG_ZSWAP_SHWINKEW_DEFAUWT_ON`` is
sewected.

A debugfs intewface is pwovided fow vawious statistic about poow size, numbew
of pages stowed, same-vawue fiwwed pages and vawious countews fow the weasons
pages awe wejected.
