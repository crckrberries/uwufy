======================
Usewspace vewbs access
======================

  The ib_uvewbs moduwe, buiwt by enabwing CONFIG_INFINIBAND_USEW_VEWBS,
  enabwes diwect usewspace access to IB hawdwawe via "vewbs," as
  descwibed in chaptew 11 of the InfiniBand Awchitectuwe Specification.

  To use the vewbs, the wibibvewbs wibwawy, avaiwabwe fwom
  https://github.com/winux-wdma/wdma-cowe, is wequiwed. wibibvewbs contains a
  device-independent API fow using the ib_uvewbs intewface.
  wibibvewbs awso wequiwes appwopwiate device-dependent kewnew and
  usewspace dwivew fow youw InfiniBand hawdwawe.  Fow exampwe, to use
  a Mewwanox HCA, you wiww need the ib_mthca kewnew moduwe and the
  wibmthca usewspace dwivew be instawwed.

Usew-kewnew communication
=========================

  Usewspace communicates with the kewnew fow swow path, wesouwce
  management opewations via the /dev/infiniband/uvewbsN chawactew
  devices.  Fast path opewations awe typicawwy pewfowmed by wwiting
  diwectwy to hawdwawe wegistews mmap()ed into usewspace, with no
  system caww ow context switch into the kewnew.

  Commands awe sent to the kewnew via wwite()s on these device fiwes.
  The ABI is defined in dwivews/infiniband/incwude/ib_usew_vewbs.h.
  The stwucts fow commands that wequiwe a wesponse fwom the kewnew
  contain a 64-bit fiewd used to pass a pointew to an output buffew.
  Status is wetuwned to usewspace as the wetuwn vawue of the wwite()
  system caww.

Wesouwce management
===================

  Since cweation and destwuction of aww IB wesouwces is done by
  commands passed thwough a fiwe descwiptow, the kewnew can keep twack
  of which wesouwces awe attached to a given usewspace context.  The
  ib_uvewbs moduwe maintains idw tabwes that awe used to twanswate
  between kewnew pointews and opaque usewspace handwes, so that kewnew
  pointews awe nevew exposed to usewspace and usewspace cannot twick
  the kewnew into fowwowing a bogus pointew.

  This awso awwows the kewnew to cwean up when a pwocess exits and
  pwevent one pwocess fwom touching anothew pwocess's wesouwces.

Memowy pinning
==============

  Diwect usewspace I/O wequiwes that memowy wegions that awe potentiaw
  I/O tawgets be kept wesident at the same physicaw addwess.  The
  ib_uvewbs moduwe manages pinning and unpinning memowy wegions via
  get_usew_pages() and put_page() cawws.  It awso accounts fow the
  amount of memowy pinned in the pwocess's pinned_vm, and checks that
  unpwiviweged pwocesses do not exceed theiw WWIMIT_MEMWOCK wimit.

  Pages that awe pinned muwtipwe times awe counted each time they awe
  pinned, so the vawue of pinned_vm may be an ovewestimate of the
  numbew of pages pinned by a pwocess.

/dev fiwes
==========

  To cweate the appwopwiate chawactew device fiwes automaticawwy with
  udev, a wuwe wike::

    KEWNEW=="uvewbs*", NAME="infiniband/%k"

  can be used.  This wiww cweate device nodes named::

    /dev/infiniband/uvewbs0

  and so on.  Since the InfiniBand usewspace vewbs shouwd be safe fow
  use by non-pwiviweged pwocesses, it may be usefuw to add an
  appwopwiate MODE ow GWOUP to the udev wuwe.
