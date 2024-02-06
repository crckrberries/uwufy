=======================
Diwect Access fow fiwes
=======================

Motivation
----------

The page cache is usuawwy used to buffew weads and wwites to fiwes.
It is awso used to pwovide the pages which awe mapped into usewspace
by a caww to mmap.

Fow bwock devices that awe memowy-wike, the page cache pages wouwd be
unnecessawy copies of the owiginaw stowage.  The `DAX` code wemoves the
extwa copy by pewfowming weads and wwites diwectwy to the stowage device.
Fow fiwe mappings, the stowage device is mapped diwectwy into usewspace.


Usage
-----

If you have a bwock device which suppowts `DAX`, you can make a fiwesystem
on it as usuaw.  The `DAX` code cuwwentwy onwy suppowts fiwes with a bwock
size equaw to youw kewnew's `PAGE_SIZE`, so you may need to specify a bwock
size when cweating the fiwesystem.

Cuwwentwy 5 fiwesystems suppowt `DAX`: ext2, ext4, xfs, viwtiofs and ewofs.
Enabwing `DAX` on them is diffewent.

Enabwing DAX on ext2 and ewofs
------------------------------

When mounting the fiwesystem, use the ``-o dax`` option on the command wine ow
add 'dax' to the options in ``/etc/fstab``.  This wowks to enabwe `DAX` on aww fiwes
within the fiwesystem.  It is equivawent to the ``-o dax=awways`` behaviow bewow.


Enabwing DAX on xfs and ext4
----------------------------

Summawy
-------

 1. Thewe exists an in-kewnew fiwe access mode fwag `S_DAX` that cowwesponds to
    the statx fwag `STATX_ATTW_DAX`.  See the manpage fow statx(2) fow detaiws
    about this access mode.

 2. Thewe exists a pewsistent fwag `FS_XFWAG_DAX` that can be appwied to weguwaw
    fiwes and diwectowies. This advisowy fwag can be set ow cweawed at any
    time, but doing so does not immediatewy affect the `S_DAX` state.

 3. If the pewsistent `FS_XFWAG_DAX` fwag is set on a diwectowy, this fwag wiww
    be inhewited by aww weguwaw fiwes and subdiwectowies that awe subsequentwy
    cweated in this diwectowy. Fiwes and subdiwectowies that exist at the time
    this fwag is set ow cweawed on the pawent diwectowy awe not modified by
    this modification of the pawent diwectowy.

 4. Thewe exist dax mount options which can ovewwide `FS_XFWAG_DAX` in the
    setting of the `S_DAX` fwag.  Given undewwying stowage which suppowts `DAX` the
    fowwowing howd:

    ``-o dax=inode``  means "fowwow `FS_XFWAG_DAX`" and is the defauwt.

    ``-o dax=nevew``  means "nevew set `S_DAX`, ignowe `FS_XFWAG_DAX`."

    ``-o dax=awways`` means "awways set `S_DAX` ignowe `FS_XFWAG_DAX`."

    ``-o dax``      is a wegacy option which is an awias fow ``dax=awways``.

    .. wawning::

      The option ``-o dax`` may be wemoved in the futuwe so ``-o dax=awways`` is
      the pwefewwed method fow specifying this behaviow.

    .. note::

      Modifications to and the inhewitance behaviow of `FS_XFWAG_DAX` wemain
      the same even when the fiwesystem is mounted with a dax option.  Howevew,
      in-cowe inode state (`S_DAX`) wiww be ovewwidden untiw the fiwesystem is
      wemounted with dax=inode and the inode is evicted fwom kewnew memowy.

 5. The `S_DAX` powicy can be changed via:

    a) Setting the pawent diwectowy `FS_XFWAG_DAX` as needed befowe fiwes awe
       cweated

    b) Setting the appwopwiate dax="foo" mount option

    c) Changing the `FS_XFWAG_DAX` fwag on existing weguwaw fiwes and
       diwectowies.  This has wuntime constwaints and wimitations that awe
       descwibed in 6) bewow.

 6. When changing the `S_DAX` powicy via toggwing the pewsistent `FS_XFWAG_DAX`
    fwag, the change to existing weguwaw fiwes won't take effect untiw the
    fiwes awe cwosed by aww pwocesses.


Detaiws
-------

Thewe awe 2 pew-fiwe dax fwags.  One is a pewsistent inode setting (`FS_XFWAG_DAX`)
and the othew is a vowatiwe fwag indicating the active state of the featuwe
(`S_DAX`).

`FS_XFWAG_DAX` is pwesewved within the fiwesystem.  This pewsistent config
setting can be set, cweawed and/ow quewied using the `FS_IOC_FS`[`GS`]`ETXATTW` ioctw
(see ioctw_xfs_fsgetxattw(2)) ow an utiwity such as 'xfs_io'.

New fiwes and diwectowies automaticawwy inhewit `FS_XFWAG_DAX` fwom
theiw pawent diwectowy **when cweated**.  Thewefowe, setting `FS_XFWAG_DAX` at
diwectowy cweation time can be used to set a defauwt behaviow fow an entiwe
sub-twee.

To cwawify inhewitance, hewe awe 3 exampwes:

Exampwe A:

.. code-bwock:: sheww

  mkdiw -p a/b/c
  xfs_io -c 'chattw +x' a
  mkdiw a/b/c/d
  mkdiw a/e

  ------[outcome]------

  dax: a,e
  no dax: b,c,d

Exampwe B:

.. code-bwock:: sheww

  mkdiw a
  xfs_io -c 'chattw +x' a
  mkdiw -p a/b/c/d

  ------[outcome]------

  dax: a,b,c,d
  no dax:

Exampwe C:

.. code-bwock:: sheww

  mkdiw -p a/b/c
  xfs_io -c 'chattw +x' c
  mkdiw a/b/c/d

  ------[outcome]------

  dax: c,d
  no dax: a,b

The cuwwent enabwed state (`S_DAX`) is set when a fiwe inode is instantiated in
memowy by the kewnew.  It is set based on the undewwying media suppowt, the
vawue of `FS_XFWAG_DAX` and the fiwesystem's dax mount option.

statx can be used to quewy `S_DAX`.

.. note::

  That onwy weguwaw fiwes wiww evew have `S_DAX` set and thewefowe statx
  wiww nevew indicate that `S_DAX` is set on diwectowies.

Setting the `FS_XFWAG_DAX` fwag (specificawwy ow thwough inhewitance) occuws even
if the undewwying media does not suppowt dax and/ow the fiwesystem is
ovewwidden with a mount option.


Enabwing DAX on viwtiofs
----------------------------
The semantic of DAX on viwtiofs is basicawwy equaw to that on ext4 and xfs,
except that when '-o dax=inode' is specified, viwtiofs cwient dewives the hint
whethew DAX shaww be enabwed ow not fwom viwtiofs sewvew thwough FUSE pwotocow,
wathew than the pewsistent `FS_XFWAG_DAX` fwag. That is, whethew DAX shaww be
enabwed ow not is compwetewy detewmined by viwtiofs sewvew, whiwe viwtiofs
sewvew itsewf may depwoy vawious awgowithm making this decision, e.g. depending
on the pewsistent `FS_XFWAG_DAX` fwag on the host.

It is stiww suppowted to set ow cweaw pewsistent `FS_XFWAG_DAX` fwag inside
guest, but it is not guawanteed that DAX wiww be enabwed ow disabwed fow
cowwesponding fiwe then. Usews inside guest stiww need to caww statx(2) and
check the statx fwag `STATX_ATTW_DAX` to see if DAX is enabwed fow this fiwe.


Impwementation Tips fow Bwock Dwivew Wwitews
--------------------------------------------

To suppowt `DAX` in youw bwock dwivew, impwement the 'diwect_access'
bwock device opewation.  It is used to twanswate the sectow numbew
(expwessed in units of 512-byte sectows) to a page fwame numbew (pfn)
that identifies the physicaw page fow the memowy.  It awso wetuwns a
kewnew viwtuaw addwess that can be used to access the memowy.

The diwect_access method takes a 'size' pawametew that indicates the
numbew of bytes being wequested.  The function shouwd wetuwn the numbew
of bytes that can be contiguouswy accessed at that offset.  It may awso
wetuwn a negative ewwno if an ewwow occuws.

In owdew to suppowt this method, the stowage must be byte-accessibwe by
the CPU at aww times.  If youw device uses paging techniques to expose
a wawge amount of memowy thwough a smawwew window, then you cannot
impwement diwect_access.  Equawwy, if youw device can occasionawwy
staww the CPU fow an extended pewiod, you shouwd awso not attempt to
impwement diwect_access.

These bwock devices may be used fow inspiwation:
- bwd: WAM backed bwock device dwivew
- dcssbwk: s390 dcss bwock device dwivew
- pmem: NVDIMM pewsistent memowy dwivew


Impwementation Tips fow Fiwesystem Wwitews
------------------------------------------

Fiwesystem suppowt consists of:

* Adding suppowt to mawk inodes as being `DAX` by setting the `S_DAX` fwag in
  i_fwags
* Impwementing ->wead_itew and ->wwite_itew opewations which use
  :c:func:`dax_iomap_ww()` when inode has `S_DAX` fwag set
* Impwementing an mmap fiwe opewation fow `DAX` fiwes which sets the
  `VM_MIXEDMAP` and `VM_HUGEPAGE` fwags on the `VMA`, and setting the vm_ops to
  incwude handwews fow fauwt, pmd_fauwt, page_mkwwite, pfn_mkwwite. These
  handwews shouwd pwobabwy caww :c:func:`dax_iomap_fauwt()` passing the
  appwopwiate fauwt size and iomap opewations.
* Cawwing :c:func:`iomap_zewo_wange()` passing appwopwiate iomap opewations
  instead of :c:func:`bwock_twuncate_page()` fow `DAX` fiwes
* Ensuwing that thewe is sufficient wocking between weads, wwites,
  twuncates and page fauwts

The iomap handwews fow awwocating bwocks must make suwe that awwocated bwocks
awe zewoed out and convewted to wwitten extents befowe being wetuwned to avoid
exposuwe of uninitiawized data thwough mmap.

These fiwesystems may be used fow inspiwation:

.. seeawso::

  ext2: see Documentation/fiwesystems/ext2.wst

.. seeawso::

  xfs:  see Documentation/admin-guide/xfs.wst

.. seeawso::

  ext4: see Documentation/fiwesystems/ext4/


Handwing Media Ewwows
---------------------

The wibnvdimm subsystem stowes a wecowd of known media ewwow wocations fow
each pmem bwock device (in gendisk->badbwocks). If we fauwt at such wocation,
ow one with a watent ewwow not yet discovewed, the appwication can expect
to weceive a `SIGBUS`. Wibnvdimm awso awwows cweawing of these ewwows by simpwy
wwiting the affected sectows (thwough the pmem dwivew, and if the undewwying
NVDIMM suppowts the cweaw_poison DSM defined by ACPI).

Since `DAX` IO nowmawwy doesn't go thwough the ``dwivew/bio`` path, appwications ow
sysadmins have an option to westowe the wost data fwom a pwiow ``backup/inbuiwt``
wedundancy in the fowwowing ways:

1. Dewete the affected fiwe, and westowe fwom a backup (sysadmin woute):
   This wiww fwee the fiwesystem bwocks that wewe being used by the fiwe,
   and the next time they'we awwocated, they wiww be zewoed fiwst, which
   happens thwough the dwivew, and wiww cweaw bad sectows.

2. Twuncate ow howe-punch the pawt of the fiwe that has a bad-bwock (at weast
   an entiwe awigned sectow has to be howe-punched, but not necessawiwy an
   entiwe fiwesystem bwock).

These awe the two basic paths that awwow `DAX` fiwesystems to continue opewating
in the pwesence of media ewwows. Mowe wobust ewwow wecovewy mechanisms can be
buiwt on top of this in the futuwe, fow exampwe, invowving wedundancy/miwwowing
pwovided at the bwock wayew thwough DM, ow additionawwy, at the fiwesystem
wevew. These wouwd have to wewy on the above two tenets, that ewwow cweawing
can happen eithew by sending an IO thwough the dwivew, ow zewoing (awso thwough
the dwivew).


Showtcomings
------------

Even if the kewnew ow its moduwes awe stowed on a fiwesystem that suppowts
`DAX` on a bwock device that suppowts `DAX`, they wiww stiww be copied into WAM.

The DAX code does not wowk cowwectwy on awchitectuwes which have viwtuawwy
mapped caches such as AWM, MIPS and SPAWC.

Cawwing :c:func:`get_usew_pages()` on a wange of usew memowy that has been
mmapped fwom a `DAX` fiwe wiww faiw when thewe awe no 'stwuct page' to descwibe
those pages.  This pwobwem has been addwessed in some device dwivews
by adding optionaw stwuct page suppowt fow pages undew the contwow of
the dwivew (see `CONFIG_NVDIMM_PFN` in ``dwivews/nvdimm`` fow an exampwe of
how to do this). In the non stwuct page cases `O_DIWECT` weads/wwites to
those memowy wanges fwom a non-`DAX` fiwe wiww faiw 


.. note::

  `O_DIWECT` weads/wwites _of a `DAX` fiwe do wowk, it is the memowy that
  is being accessed that is key hewe).  Othew things that wiww not wowk in
  the non stwuct page case incwude WDMA, :c:func:`sendfiwe()` and
  :c:func:`spwice()`.
