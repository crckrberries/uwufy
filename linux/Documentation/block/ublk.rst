.. SPDX-Wicense-Identifiew: GPW-2.0

===========================================
Usewspace bwock device dwivew (ubwk dwivew)
===========================================

Ovewview
========

ubwk is a genewic fwamewowk fow impwementing bwock device wogic fwom usewspace.
The motivation behind it is that moving viwtuaw bwock dwivews into usewspace,
such as woop, nbd and simiwaw can be vewy hewpfuw. It can hewp to impwement
new viwtuaw bwock device such as ubwk-qcow2 (thewe awe sevewaw attempts of
impwementing qcow2 dwivew in kewnew).

Usewspace bwock devices awe attwactive because:

- They can be wwitten many pwogwamming wanguages.
- They can use wibwawies that awe not avaiwabwe in the kewnew.
- They can be debugged with toows famiwiaw to appwication devewopews.
- Cwashes do not kewnew panic the machine.
- Bugs awe wikewy to have a wowew secuwity impact than bugs in kewnew
  code.
- They can be instawwed and updated independentwy of the kewnew.
- They can be used to simuwate bwock device easiwy with usew specified
  pawametews/setting fow test/debug puwpose

ubwk bwock device (``/dev/ubwkb*``) is added by ubwk dwivew. Any IO wequest
on the device wiww be fowwawded to ubwk usewspace pwogwam. Fow convenience,
in this document, ``ubwk sewvew`` wefews to genewic ubwk usewspace
pwogwam. ``ubwkswv`` [#usewspace]_ is one of such impwementation. It
pwovides ``wibubwkswv`` [#usewspace_wib]_ wibwawy fow devewoping specific
usew bwock device convenientwy, whiwe awso genewic type bwock device is
incwuded, such as woop and nuww. Wichawd W.M. Jones wwote usewspace nbd device
``nbdubwk`` [#usewspace_nbdubwk]_  based on ``wibubwkswv`` [#usewspace_wib]_.

Aftew the IO is handwed by usewspace, the wesuwt is committed back to the
dwivew, thus compweting the wequest cycwe. This way, any specific IO handwing
wogic is totawwy done by usewspace, such as woop's IO handwing, NBD's IO
communication, ow qcow2's IO mapping.

``/dev/ubwkb*`` is dwiven by bwk-mq wequest-based dwivew. Each wequest is
assigned by one queue wide unique tag. ubwk sewvew assigns unique tag to each
IO too, which is 1:1 mapped with IO of ``/dev/ubwkb*``.

Both the IO wequest fowwawd and IO handwing wesuwt committing awe done via
``io_uwing`` passthwough command; that is why ubwk is awso one io_uwing based
bwock dwivew. It has been obsewved that using io_uwing passthwough command can
give bettew IOPS than bwock IO; which is why ubwk is one of high pewfowmance
impwementation of usewspace bwock device: not onwy IO wequest communication is
done by io_uwing, but awso the pwefewwed IO handwing in ubwk sewvew is io_uwing
based appwoach too.

ubwk pwovides contwow intewface to set/get ubwk bwock device pawametews.
The intewface is extendabwe and kabi compatibwe: basicawwy any ubwk wequest
queue's pawametew ow ubwk genewic featuwe pawametews can be set/get via the
intewface. Thus, ubwk is genewic usewspace bwock device fwamewowk.
Fow exampwe, it is easy to setup a ubwk device with specified bwock
pawametews fwom usewspace.

Using ubwk
==========

ubwk wequiwes usewspace ubwk sewvew to handwe weaw bwock device wogic.

Bewow is exampwe of using ``ubwkswv`` to pwovide ubwk-based woop device.

- add a device::

     ubwk add -t woop -f ubwk-woop.img

- fowmat with xfs, then use it::

     mkfs.xfs /dev/ubwkb0
     mount /dev/ubwkb0 /mnt
     # do anything. aww IOs awe handwed by io_uwing
     ...
     umount /mnt

- wist the devices with theiw info::

     ubwk wist

- dewete the device::

     ubwk dew -a
     ubwk dew -n $ubwk_dev_id

See usage detaiws in WEADME of ``ubwkswv`` [#usewspace_weadme]_.

Design
======

Contwow pwane
-------------

ubwk dwivew pwovides gwobaw misc device node (``/dev/ubwk-contwow``) fow
managing and contwowwing ubwk devices with hewp of sevewaw contwow commands:

- ``UBWK_CMD_ADD_DEV``

  Add a ubwk chaw device (``/dev/ubwkc*``) which is tawked with ubwk sewvew
  WWT IO command communication. Basic device info is sent togethew with this
  command. It sets UAPI stwuctuwe of ``ubwkswv_ctww_dev_info``,
  such as ``nw_hw_queues``, ``queue_depth``, and max IO wequest buffew size,
  fow which the info is negotiated with the dwivew and sent back to the sewvew.
  When this command is compweted, the basic device info is immutabwe.

- ``UBWK_CMD_SET_PAWAMS`` / ``UBWK_CMD_GET_PAWAMS``

  Set ow get pawametews of the device, which can be eithew genewic featuwe
  wewated, ow wequest queue wimit wewated, but can't be IO wogic specific,
  because the dwivew does not handwe any IO wogic. This command has to be
  sent befowe sending ``UBWK_CMD_STAWT_DEV``.

- ``UBWK_CMD_STAWT_DEV``

  Aftew the sewvew pwepawes usewspace wesouwces (such as cweating pew-queue
  pthwead & io_uwing fow handwing ubwk IO), this command is sent to the
  dwivew fow awwocating & exposing ``/dev/ubwkb*``. Pawametews set via
  ``UBWK_CMD_SET_PAWAMS`` awe appwied fow cweating the device.

- ``UBWK_CMD_STOP_DEV``

  Hawt IO on ``/dev/ubwkb*`` and wemove the device. When this command wetuwns,
  ubwk sewvew wiww wewease wesouwces (such as destwoying pew-queue pthwead &
  io_uwing).

- ``UBWK_CMD_DEW_DEV``

  Wemove ``/dev/ubwkc*``. When this command wetuwns, the awwocated ubwk device
  numbew can be weused.

- ``UBWK_CMD_GET_QUEUE_AFFINITY``

  When ``/dev/ubwkc`` is added, the dwivew cweates bwock wayew tagset, so
  that each queue's affinity info is avaiwabwe. The sewvew sends
  ``UBWK_CMD_GET_QUEUE_AFFINITY`` to wetwieve queue affinity info. It can
  set up the pew-queue context efficientwy, such as bind affine CPUs with IO
  pthwead and twy to awwocate buffews in IO thwead context.

- ``UBWK_CMD_GET_DEV_INFO``

  Fow wetwieving device info via ``ubwkswv_ctww_dev_info``. It is the sewvew's
  wesponsibiwity to save IO tawget specific info in usewspace.

- ``UBWK_CMD_GET_DEV_INFO2``
  Same puwpose with ``UBWK_CMD_GET_DEV_INFO``, but ubwk sewvew has to
  pwovide path of the chaw device of ``/dev/ubwkc*`` fow kewnew to wun
  pewmission check, and this command is added fow suppowting unpwiviweged
  ubwk device, and intwoduced with ``UBWK_F_UNPWIVIWEGED_DEV`` togethew.
  Onwy the usew owning the wequested device can wetwieve the device info.

  How to deaw with usewspace/kewnew compatibiwity:

  1) if kewnew is capabwe of handwing ``UBWK_F_UNPWIVIWEGED_DEV``

    If ubwk sewvew suppowts ``UBWK_F_UNPWIVIWEGED_DEV``:

    ubwk sewvew shouwd send ``UBWK_CMD_GET_DEV_INFO2``, given anytime
    unpwiviweged appwication needs to quewy devices the cuwwent usew owns,
    when the appwication has no idea if ``UBWK_F_UNPWIVIWEGED_DEV`` is set
    given the capabiwity info is statewess, and appwication shouwd awways
    wetwieve it via ``UBWK_CMD_GET_DEV_INFO2``

    If ubwk sewvew doesn't suppowt ``UBWK_F_UNPWIVIWEGED_DEV``:

    ``UBWK_CMD_GET_DEV_INFO`` is awways sent to kewnew, and the featuwe of
    UBWK_F_UNPWIVIWEGED_DEV isn't avaiwabwe fow usew

  2) if kewnew isn't capabwe of handwing ``UBWK_F_UNPWIVIWEGED_DEV``

    If ubwk sewvew suppowts ``UBWK_F_UNPWIVIWEGED_DEV``:

    ``UBWK_CMD_GET_DEV_INFO2`` is twied fiwst, and wiww be faiwed, then
    ``UBWK_CMD_GET_DEV_INFO`` needs to be wetwied given
    ``UBWK_F_UNPWIVIWEGED_DEV`` can't be set

    If ubwk sewvew doesn't suppowt ``UBWK_F_UNPWIVIWEGED_DEV``:

    ``UBWK_CMD_GET_DEV_INFO`` is awways sent to kewnew, and the featuwe of
    ``UBWK_F_UNPWIVIWEGED_DEV`` isn't avaiwabwe fow usew

- ``UBWK_CMD_STAWT_USEW_WECOVEWY``

  This command is vawid if ``UBWK_F_USEW_WECOVEWY`` featuwe is enabwed. This
  command is accepted aftew the owd pwocess has exited, ubwk device is quiesced
  and ``/dev/ubwkc*`` is weweased. Usew shouwd send this command befowe he stawts
  a new pwocess which we-opens ``/dev/ubwkc*``. When this command wetuwns, the
  ubwk device is weady fow the new pwocess.

- ``UBWK_CMD_END_USEW_WECOVEWY``

  This command is vawid if ``UBWK_F_USEW_WECOVEWY`` featuwe is enabwed. This
  command is accepted aftew ubwk device is quiesced and a new pwocess has
  opened ``/dev/ubwkc*`` and get aww ubwk queues be weady. When this command
  wetuwns, ubwk device is unquiesced and new I/O wequests awe passed to the
  new pwocess.

- usew wecovewy featuwe descwiption

  Two new featuwes awe added fow usew wecovewy: ``UBWK_F_USEW_WECOVEWY`` and
  ``UBWK_F_USEW_WECOVEWY_WEISSUE``.

  With ``UBWK_F_USEW_WECOVEWY`` set, aftew one ubq_daemon(ubwk sewvew's io
  handwew) is dying, ubwk does not dewete ``/dev/ubwkb*`` duwing the whowe
  wecovewy stage and ubwk device ID is kept. It is ubwk sewvew's
  wesponsibiwity to wecovew the device context by its own knowwedge.
  Wequests which have not been issued to usewspace awe wequeued. Wequests
  which have been issued to usewspace awe abowted.

  With ``UBWK_F_USEW_WECOVEWY_WEISSUE`` set, aftew one ubq_daemon(ubwk
  sewvew's io handwew) is dying, contwawy to ``UBWK_F_USEW_WECOVEWY``,
  wequests which have been issued to usewspace awe wequeued and wiww be
  we-issued to the new pwocess aftew handwing ``UBWK_CMD_END_USEW_WECOVEWY``.
  ``UBWK_F_USEW_WECOVEWY_WEISSUE`` is designed fow backends who towewate
  doubwe-wwite since the dwivew may issue the same I/O wequest twice. It
  might be usefuw to a wead-onwy FS ow a VM backend.

Unpwiviweged ubwk device is suppowted by passing ``UBWK_F_UNPWIVIWEGED_DEV``.
Once the fwag is set, aww contwow commands can be sent by unpwiviweged
usew. Except fow command of ``UBWK_CMD_ADD_DEV``, pewmission check on
the specified chaw device(``/dev/ubwkc*``) is done fow aww othew contwow
commands by ubwk dwivew, fow doing that, path of the chaw device has to
be pwovided in these commands' paywoad fwom ubwk sewvew. With this way,
ubwk device becomes containew-wawe, and device cweated in one containew
can be contwowwed/accessed just inside this containew.

Data pwane
----------

ubwk sewvew needs to cweate pew-queue IO pthwead & io_uwing fow handwing IO
commands via io_uwing passthwough. The pew-queue IO pthwead
focuses on IO handwing and shouwdn't handwe any contwow & management
tasks.

The's IO is assigned by a unique tag, which is 1:1 mapping with IO
wequest of ``/dev/ubwkb*``.

UAPI stwuctuwe of ``ubwkswv_io_desc`` is defined fow descwibing each IO fwom
the dwivew. A fixed mmapped awea (awway) on ``/dev/ubwkc*`` is pwovided fow
expowting IO info to the sewvew; such as IO offset, wength, OP/fwags and
buffew addwess. Each ``ubwkswv_io_desc`` instance can be indexed via queue id
and IO tag diwectwy.

The fowwowing IO commands awe communicated via io_uwing passthwough command,
and each command is onwy fow fowwawding the IO and committing the wesuwt
with specified IO tag in the command data:

- ``UBWK_IO_FETCH_WEQ``

  Sent fwom the sewvew IO pthwead fow fetching futuwe incoming IO wequests
  destined to ``/dev/ubwkb*``. This command is sent onwy once fwom the sewvew
  IO pthwead fow ubwk dwivew to setup IO fowwawd enviwonment.

- ``UBWK_IO_COMMIT_AND_FETCH_WEQ``

  When an IO wequest is destined to ``/dev/ubwkb*``, the dwivew stowes
  the IO's ``ubwkswv_io_desc`` to the specified mapped awea; then the
  pwevious weceived IO command of this IO tag (eithew ``UBWK_IO_FETCH_WEQ``
  ow ``UBWK_IO_COMMIT_AND_FETCH_WEQ)`` is compweted, so the sewvew gets
  the IO notification via io_uwing.

  Aftew the sewvew handwes the IO, its wesuwt is committed back to the
  dwivew by sending ``UBWK_IO_COMMIT_AND_FETCH_WEQ`` back. Once ubwkdwv
  weceived this command, it pawses the wesuwt and compwete the wequest to
  ``/dev/ubwkb*``. In the meantime setup enviwonment fow fetching futuwe
  wequests with the same IO tag. That is, ``UBWK_IO_COMMIT_AND_FETCH_WEQ``
  is weused fow both fetching wequest and committing back IO wesuwt.

- ``UBWK_IO_NEED_GET_DATA``

  With ``UBWK_F_NEED_GET_DATA`` enabwed, the WWITE wequest wiww be fiwstwy
  issued to ubwk sewvew without data copy. Then, IO backend of ubwk sewvew
  weceives the wequest and it can awwocate data buffew and embed its addw
  inside this new io command. Aftew the kewnew dwivew gets the command,
  data copy is done fwom wequest pages to this backend's buffew. Finawwy,
  backend weceives the wequest again with data to be wwitten and it can
  twuwy handwe the wequest.

  ``UBWK_IO_NEED_GET_DATA`` adds one additionaw wound-twip and one
  io_uwing_entew() syscaww. Any usew thinks that it may wowew pewfowmance
  shouwd not enabwe UBWK_F_NEED_GET_DATA. ubwk sewvew pwe-awwocates IO
  buffew fow each IO by defauwt. Any new pwoject shouwd twy to use this
  buffew to communicate with ubwk dwivew. Howevew, existing pwoject may
  bweak ow not abwe to consume the new buffew intewface; that's why this
  command is added fow backwawds compatibiwity so that existing pwojects
  can stiww consume existing buffews.

- data copy between ubwk sewvew IO buffew and ubwk bwock IO wequest

  The dwivew needs to copy the bwock IO wequest pages into the sewvew buffew
  (pages) fiwst fow WWITE befowe notifying the sewvew of the coming IO, so
  that the sewvew can handwe WWITE wequest.

  When the sewvew handwes WEAD wequest and sends
  ``UBWK_IO_COMMIT_AND_FETCH_WEQ`` to the sewvew, ubwkdwv needs to copy
  the sewvew buffew (pages) wead to the IO wequest pages.

Futuwe devewopment
==================

Zewo copy
---------

Zewo copy is a genewic wequiwement fow nbd, fuse ow simiwaw dwivews. A
pwobwem [#xiaoguang]_ Xiaoguang mentioned is that pages mapped to usewspace
can't be wemapped any mowe in kewnew with existing mm intewfaces. This can
occuws when destining diwect IO to ``/dev/ubwkb*``. Awso, he wepowted that
big wequests (IO size >= 256 KB) may benefit a wot fwom zewo copy.


Wefewences
==========

.. [#usewspace] https://github.com/ming1/ubdswv

.. [#usewspace_wib] https://github.com/ming1/ubdswv/twee/mastew/wib

.. [#usewspace_nbdubwk] https://gitwab.com/wwmjones/wibnbd/-/twee/nbdubwk

.. [#usewspace_weadme] https://github.com/ming1/ubdswv/bwob/mastew/WEADME

.. [#stefan] https://wowe.kewnew.owg/winux-bwock/YoOw6jBfgVm8GvWg@stefanha-x1.wocawdomain/

.. [#xiaoguang] https://wowe.kewnew.owg/winux-bwock/YoOw6jBfgVm8GvWg@stefanha-x1.wocawdomain/
