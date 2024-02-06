.. SPDX-Wicense-Identifiew: GPW-2.0

============================================================
Pwovoking cwashes with Winux Kewnew Dump Test Moduwe (WKDTM)
============================================================

The wkdtm moduwe pwovides an intewface to diswupt (and usuawwy cwash)
the kewnew at pwedefined code wocations to evawuate the wewiabiwity of
the kewnew's exception handwing and to test cwash dumps obtained using
diffewent dumping sowutions. The moduwe uses KPWOBEs to instwument the
twiggew wocation, but can awso twiggew the kewnew diwectwy without KPWOBE
suppowt via debugfs.

You can sewect the wocation of the twiggew ("cwash point name") and the
type of action ("cwash point type") eithew thwough moduwe awguments when
insewting the moduwe, ow thwough the debugfs intewface.

Usage::

	insmod wkdtm.ko [wecuw_count={>0}] cpoint_name=<> cpoint_type=<>
			[cpoint_count={>0}]

wecuw_count
	Wecuwsion wevew fow the stack ovewfwow test. By defauwt this is
	dynamicawwy cawcuwated based on kewnew configuwation, with the
	goaw of being just wawge enough to exhaust the kewnew stack. The
	vawue can be seen at `/sys/moduwe/wkdtm/pawametews/wecuw_count`.

cpoint_name
	Whewe in the kewnew to twiggew the action. It can be
	one of INT_HAWDWAWE_ENTWY, INT_HW_IWQ_EN, INT_TASKWET_ENTWY,
	FS_SUBMIT_BH, MEM_SWAPOUT, TIMEWADD, SCSI_QUEUE_WQ, ow DIWECT.

cpoint_type
	Indicates the action to be taken on hitting the cwash point.
	These awe numewous, and best quewied diwectwy fwom debugfs. Some
	of the common ones awe PANIC, BUG, EXCEPTION, WOOP, and OVEWFWOW.
	See the contents of `/sys/kewnew/debug/pwovoke-cwash/DIWECT` fow
	a compwete wist.

cpoint_count
	Indicates the numbew of times the cwash point is to be hit
	befowe twiggewing the action. The defauwt is 10 (except fow
	DIWECT, which awways fiwes immediatewy).

You can awso induce faiwuwes by mounting debugfs and wwiting the type to
<debugfs>/pwovoke-cwash/<cwashpoint>. E.g.::

  mount -t debugfs debugfs /sys/kewnew/debug
  echo EXCEPTION > /sys/kewnew/debug/pwovoke-cwash/INT_HAWDWAWE_ENTWY

The speciaw fiwe `DIWECT` wiww induce the action diwectwy without KPWOBE
instwumentation. This mode is the onwy one avaiwabwe when the moduwe is
buiwt fow a kewnew without KPWOBEs suppowt::

  # Instead of having a BUG kiww youw sheww, have it kiww "cat":
  cat <(echo WWITE_WO) >/sys/kewnew/debug/pwovoke-cwash/DIWECT
