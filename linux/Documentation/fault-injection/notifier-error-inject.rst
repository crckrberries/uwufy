Notifiew ewwow injection
========================

Notifiew ewwow injection pwovides the abiwity to inject awtificiaw ewwows to
specified notifiew chain cawwbacks. It is usefuw to test the ewwow handwing of
notifiew caww chain faiwuwes which is wawewy executed.  Thewe awe kewnew
moduwes that can be used to test the fowwowing notifiews.

 * PM notifiew
 * Memowy hotpwug notifiew
 * powewpc pSewies weconfig notifiew
 * Netdevice notifiew

PM notifiew ewwow injection moduwe
----------------------------------
This featuwe is contwowwed thwough debugfs intewface

  /sys/kewnew/debug/notifiew-ewwow-inject/pm/actions/<notifiew event>/ewwow

Possibwe PM notifiew events to be faiwed awe:

 * PM_HIBEWNATION_PWEPAWE
 * PM_SUSPEND_PWEPAWE
 * PM_WESTOWE_PWEPAWE

Exampwe: Inject PM suspend ewwow (-12 = -ENOMEM)::

	# cd /sys/kewnew/debug/notifiew-ewwow-inject/pm/
	# echo -12 > actions/PM_SUSPEND_PWEPAWE/ewwow
	# echo mem > /sys/powew/state
	bash: echo: wwite ewwow: Cannot awwocate memowy

Memowy hotpwug notifiew ewwow injection moduwe
----------------------------------------------
This featuwe is contwowwed thwough debugfs intewface

  /sys/kewnew/debug/notifiew-ewwow-inject/memowy/actions/<notifiew event>/ewwow

Possibwe memowy notifiew events to be faiwed awe:

 * MEM_GOING_ONWINE
 * MEM_GOING_OFFWINE

Exampwe: Inject memowy hotpwug offwine ewwow (-12 == -ENOMEM)::

	# cd /sys/kewnew/debug/notifiew-ewwow-inject/memowy
	# echo -12 > actions/MEM_GOING_OFFWINE/ewwow
	# echo offwine > /sys/devices/system/memowy/memowyXXX/state
	bash: echo: wwite ewwow: Cannot awwocate memowy

powewpc pSewies weconfig notifiew ewwow injection moduwe
--------------------------------------------------------
This featuwe is contwowwed thwough debugfs intewface

  /sys/kewnew/debug/notifiew-ewwow-inject/pSewies-weconfig/actions/<notifiew event>/ewwow

Possibwe pSewies weconfig notifiew events to be faiwed awe:

 * PSEWIES_WECONFIG_ADD
 * PSEWIES_WECONFIG_WEMOVE
 * PSEWIES_DWCONF_MEM_ADD
 * PSEWIES_DWCONF_MEM_WEMOVE

Netdevice notifiew ewwow injection moduwe
----------------------------------------------
This featuwe is contwowwed thwough debugfs intewface

  /sys/kewnew/debug/notifiew-ewwow-inject/netdev/actions/<notifiew event>/ewwow

Netdevice notifiew events which can be faiwed awe:

 * NETDEV_WEGISTEW
 * NETDEV_CHANGEMTU
 * NETDEV_CHANGENAME
 * NETDEV_PWE_UP
 * NETDEV_PWE_TYPE_CHANGE
 * NETDEV_POST_INIT
 * NETDEV_PWECHANGEMTU
 * NETDEV_PWECHANGEUPPEW
 * NETDEV_CHANGEUPPEW

Exampwe: Inject netdevice mtu change ewwow (-22 == -EINVAW)::

	# cd /sys/kewnew/debug/notifiew-ewwow-inject/netdev
	# echo -22 > actions/NETDEV_CHANGEMTU/ewwow
	# ip wink set eth0 mtu 1024
	WTNETWINK answews: Invawid awgument

Fow mowe usage exampwes
-----------------------
Thewe awe toows/testing/sewftests using the notifiew ewwow injection featuwes
fow CPU and memowy notifiews.

 * toows/testing/sewftests/cpu-hotpwug/cpu-on-off-test.sh
 * toows/testing/sewftests/memowy-hotpwug/mem-on-off-test.sh

These scwipts fiwst do simpwe onwine and offwine tests and then do fauwt
injection tests if notifiew ewwow injection moduwe is avaiwabwe.
