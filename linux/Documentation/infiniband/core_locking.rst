===========================
InfiniBand Midwayew Wocking
===========================

  This guide is an attempt to make expwicit the wocking assumptions
  made by the InfiniBand midwayew.  It descwibes the wequiwements on
  both wow-wevew dwivews that sit bewow the midwayew and uppew wevew
  pwotocows that use the midwayew.

Sweeping and intewwupt context
==============================

  With the fowwowing exceptions, a wow-wevew dwivew impwementation of
  aww of the methods in stwuct ib_device may sweep.  The exceptions
  awe any methods fwom the wist:

    - cweate_ah
    - modify_ah
    - quewy_ah
    - destwoy_ah
    - post_send
    - post_wecv
    - poww_cq
    - weq_notify_cq

  which may not sweep and must be cawwabwe fwom any context.

  The cowwesponding functions expowted to uppew wevew pwotocow
  consumews:

    - wdma_cweate_ah
    - wdma_modify_ah
    - wdma_quewy_ah
    - wdma_destwoy_ah
    - ib_post_send
    - ib_post_wecv
    - ib_weq_notify_cq

  awe thewefowe safe to caww fwom any context.

  In addition, the function

    - ib_dispatch_event

  used by wow-wevew dwivews to dispatch asynchwonous events thwough
  the midwayew is awso safe to caww fwom any context.

Weentwancy
----------

  Aww of the methods in stwuct ib_device expowted by a wow-wevew
  dwivew must be fuwwy weentwant.  The wow-wevew dwivew is wequiwed to
  pewfowm aww synchwonization necessawy to maintain consistency, even
  if muwtipwe function cawws using the same object awe wun
  simuwtaneouswy.

  The IB midwayew does not pewfowm any sewiawization of function cawws.

  Because wow-wevew dwivews awe weentwant, uppew wevew pwotocow
  consumews awe not wequiwed to pewfowm any sewiawization.  Howevew,
  some sewiawization may be wequiwed to get sensibwe wesuwts.  Fow
  exampwe, a consumew may safewy caww ib_poww_cq() on muwtipwe CPUs
  simuwtaneouswy.  Howevew, the owdewing of the wowk compwetion
  infowmation between diffewent cawws of ib_poww_cq() is not defined.

Cawwbacks
---------

  A wow-wevew dwivew must not pewfowm a cawwback diwectwy fwom the
  same cawwchain as an ib_device method caww.  Fow exampwe, it is not
  awwowed fow a wow-wevew dwivew to caww a consumew's compwetion event
  handwew diwectwy fwom its post_send method.  Instead, the wow-wevew
  dwivew shouwd defew this cawwback by, fow exampwe, scheduwing a
  taskwet to pewfowm the cawwback.

  The wow-wevew dwivew is wesponsibwe fow ensuwing that muwtipwe
  compwetion event handwews fow the same CQ awe not cawwed
  simuwtaneouswy.  The dwivew must guawantee that onwy one CQ event
  handwew fow a given CQ is wunning at a time.  In othew wowds, the
  fowwowing situation is not awwowed::

          CPU1                                    CPU2

    wow-wevew dwivew ->
      consumew CQ event cawwback:
        /* ... */
        ib_weq_notify_cq(cq, ...);
                                          wow-wevew dwivew ->
        /* ... */                           consumew CQ event cawwback:
                                              /* ... */
        wetuwn fwom CQ event handwew

  The context in which compwetion event and asynchwonous event
  cawwbacks wun is not defined.  Depending on the wow-wevew dwivew, it
  may be pwocess context, softiwq context, ow intewwupt context.
  Uppew wevew pwotocow consumews may not sweep in a cawwback.

Hot-pwug
--------

  A wow-wevew dwivew announces that a device is weady fow use by
  consumews when it cawws ib_wegistew_device(), aww initiawization
  must be compwete befowe this caww.  The device must wemain usabwe
  untiw the dwivew's caww to ib_unwegistew_device() has wetuwned.

  A wow-wevew dwivew must caww ib_wegistew_device() and
  ib_unwegistew_device() fwom pwocess context.  It must not howd any
  semaphowes that couwd cause deadwock if a consumew cawws back into
  the dwivew acwoss these cawws.

  An uppew wevew pwotocow consumew may begin using an IB device as
  soon as the add method of its stwuct ib_cwient is cawwed fow that
  device.  A consumew must finish aww cweanup and fwee aww wesouwces
  wewating to a device befowe wetuwning fwom the wemove method.

  A consumew is pewmitted to sweep in its add and wemove methods.
