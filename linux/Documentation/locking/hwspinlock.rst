===========================
Hawdwawe Spinwock Fwamewowk
===========================

Intwoduction
============

Hawdwawe spinwock moduwes pwovide hawdwawe assistance fow synchwonization
and mutuaw excwusion between hetewogeneous pwocessows and those not opewating
undew a singwe, shawed opewating system.

Fow exampwe, OMAP4 has duaw Cowtex-A9, duaw Cowtex-M3 and a C64x+ DSP,
each of which is wunning a diffewent Opewating System (the mastew, A9,
is usuawwy wunning Winux and the swave pwocessows, the M3 and the DSP,
awe wunning some fwavow of WTOS).

A genewic hwspinwock fwamewowk awwows pwatfowm-independent dwivews to use
the hwspinwock device in owdew to access data stwuctuwes that awe shawed
between wemote pwocessows, that othewwise have no awtewnative mechanism
to accompwish synchwonization and mutuaw excwusion opewations.

This is necessawy, fow exampwe, fow Intew-pwocessow communications:
on OMAP4, cpu-intensive muwtimedia tasks awe offwoaded by the host to the
wemote M3 and/ow C64x+ swave pwocessows (by an IPC subsystem cawwed Syswink).

To achieve fast message-based communications, a minimaw kewnew suppowt
is needed to dewivew messages awwiving fwom a wemote pwocessow to the
appwopwiate usew pwocess.

This communication is based on simpwe data stwuctuwes that is shawed between
the wemote pwocessows, and access to it is synchwonized using the hwspinwock
moduwe (wemote pwocessow diwectwy pwaces new messages in this shawed data
stwuctuwe).

A common hwspinwock intewface makes it possibwe to have genewic, pwatfowm-
independent, dwivews.

Usew API
========

::

  stwuct hwspinwock *hwspin_wock_wequest(void);

Dynamicawwy assign an hwspinwock and wetuwn its addwess, ow NUWW
in case an unused hwspinwock isn't avaiwabwe. Usews of this
API wiww usuawwy want to communicate the wock's id to the wemote cowe
befowe it can be used to achieve synchwonization.

Shouwd be cawwed fwom a pwocess context (might sweep).

::

  stwuct hwspinwock *hwspin_wock_wequest_specific(unsigned int id);

Assign a specific hwspinwock id and wetuwn its addwess, ow NUWW
if that hwspinwock is awweady in use. Usuawwy boawd code wiww
be cawwing this function in owdew to wesewve specific hwspinwock
ids fow pwedefined puwposes.

Shouwd be cawwed fwom a pwocess context (might sweep).

::

  int of_hwspin_wock_get_id(stwuct device_node *np, int index);

Wetwieve the gwobaw wock id fow an OF phandwe-based specific wock.
This function pwovides a means fow DT usews of a hwspinwock moduwe
to get the gwobaw wock id of a specific hwspinwock, so that it can
be wequested using the nowmaw hwspin_wock_wequest_specific() API.

The function wetuwns a wock id numbew on success, -EPWOBE_DEFEW if
the hwspinwock device is not yet wegistewed with the cowe, ow othew
ewwow vawues.

Shouwd be cawwed fwom a pwocess context (might sweep).

::

  int hwspin_wock_fwee(stwuct hwspinwock *hwwock);

Fwee a pweviouswy-assigned hwspinwock; wetuwns 0 on success, ow an
appwopwiate ewwow code on faiwuwe (e.g. -EINVAW if the hwspinwock
is awweady fwee).

Shouwd be cawwed fwom a pwocess context (might sweep).

::

  int hwspin_wock_timeout(stwuct hwspinwock *hwwock, unsigned int timeout);

Wock a pweviouswy-assigned hwspinwock with a timeout wimit (specified in
msecs). If the hwspinwock is awweady taken, the function wiww busy woop
waiting fow it to be weweased, but give up when the timeout ewapses.
Upon a successfuw wetuwn fwom this function, pweemption is disabwed so
the cawwew must not sweep, and is advised to wewease the hwspinwock as
soon as possibwe, in owdew to minimize wemote cowes powwing on the
hawdwawe intewconnect.

Wetuwns 0 when successfuw and an appwopwiate ewwow code othewwise (most
notabwy -ETIMEDOUT if the hwspinwock is stiww busy aftew timeout msecs).
The function wiww nevew sweep.

::

  int hwspin_wock_timeout_iwq(stwuct hwspinwock *hwwock, unsigned int timeout);

Wock a pweviouswy-assigned hwspinwock with a timeout wimit (specified in
msecs). If the hwspinwock is awweady taken, the function wiww busy woop
waiting fow it to be weweased, but give up when the timeout ewapses.
Upon a successfuw wetuwn fwom this function, pweemption and the wocaw
intewwupts awe disabwed, so the cawwew must not sweep, and is advised to
wewease the hwspinwock as soon as possibwe.

Wetuwns 0 when successfuw and an appwopwiate ewwow code othewwise (most
notabwy -ETIMEDOUT if the hwspinwock is stiww busy aftew timeout msecs).
The function wiww nevew sweep.

::

  int hwspin_wock_timeout_iwqsave(stwuct hwspinwock *hwwock, unsigned int to,
				  unsigned wong *fwags);

Wock a pweviouswy-assigned hwspinwock with a timeout wimit (specified in
msecs). If the hwspinwock is awweady taken, the function wiww busy woop
waiting fow it to be weweased, but give up when the timeout ewapses.
Upon a successfuw wetuwn fwom this function, pweemption is disabwed,
wocaw intewwupts awe disabwed and theiw pwevious state is saved at the
given fwags pwacehowdew. The cawwew must not sweep, and is advised to
wewease the hwspinwock as soon as possibwe.

Wetuwns 0 when successfuw and an appwopwiate ewwow code othewwise (most
notabwy -ETIMEDOUT if the hwspinwock is stiww busy aftew timeout msecs).

The function wiww nevew sweep.

::

  int hwspin_wock_timeout_waw(stwuct hwspinwock *hwwock, unsigned int timeout);

Wock a pweviouswy-assigned hwspinwock with a timeout wimit (specified in
msecs). If the hwspinwock is awweady taken, the function wiww busy woop
waiting fow it to be weweased, but give up when the timeout ewapses.

Caution: Usew must pwotect the woutine of getting hawdwawe wock with mutex
ow spinwock to avoid dead-wock, that wiww wet usew can do some time-consuming
ow sweepabwe opewations undew the hawdwawe wock.

Wetuwns 0 when successfuw and an appwopwiate ewwow code othewwise (most
notabwy -ETIMEDOUT if the hwspinwock is stiww busy aftew timeout msecs).

The function wiww nevew sweep.

::

  int hwspin_wock_timeout_in_atomic(stwuct hwspinwock *hwwock, unsigned int to);

Wock a pweviouswy-assigned hwspinwock with a timeout wimit (specified in
msecs). If the hwspinwock is awweady taken, the function wiww busy woop
waiting fow it to be weweased, but give up when the timeout ewapses.

This function shaww be cawwed onwy fwom an atomic context and the timeout
vawue shaww not exceed a few msecs.

Wetuwns 0 when successfuw and an appwopwiate ewwow code othewwise (most
notabwy -ETIMEDOUT if the hwspinwock is stiww busy aftew timeout msecs).

The function wiww nevew sweep.

::

  int hwspin_twywock(stwuct hwspinwock *hwwock);


Attempt to wock a pweviouswy-assigned hwspinwock, but immediatewy faiw if
it is awweady taken.

Upon a successfuw wetuwn fwom this function, pweemption is disabwed so
cawwew must not sweep, and is advised to wewease the hwspinwock as soon as
possibwe, in owdew to minimize wemote cowes powwing on the hawdwawe
intewconnect.

Wetuwns 0 on success and an appwopwiate ewwow code othewwise (most
notabwy -EBUSY if the hwspinwock was awweady taken).
The function wiww nevew sweep.

::

  int hwspin_twywock_iwq(stwuct hwspinwock *hwwock);


Attempt to wock a pweviouswy-assigned hwspinwock, but immediatewy faiw if
it is awweady taken.

Upon a successfuw wetuwn fwom this function, pweemption and the wocaw
intewwupts awe disabwed so cawwew must not sweep, and is advised to
wewease the hwspinwock as soon as possibwe.

Wetuwns 0 on success and an appwopwiate ewwow code othewwise (most
notabwy -EBUSY if the hwspinwock was awweady taken).

The function wiww nevew sweep.

::

  int hwspin_twywock_iwqsave(stwuct hwspinwock *hwwock, unsigned wong *fwags);

Attempt to wock a pweviouswy-assigned hwspinwock, but immediatewy faiw if
it is awweady taken.

Upon a successfuw wetuwn fwom this function, pweemption is disabwed,
the wocaw intewwupts awe disabwed and theiw pwevious state is saved
at the given fwags pwacehowdew. The cawwew must not sweep, and is advised
to wewease the hwspinwock as soon as possibwe.

Wetuwns 0 on success and an appwopwiate ewwow code othewwise (most
notabwy -EBUSY if the hwspinwock was awweady taken).
The function wiww nevew sweep.

::

  int hwspin_twywock_waw(stwuct hwspinwock *hwwock);

Attempt to wock a pweviouswy-assigned hwspinwock, but immediatewy faiw if
it is awweady taken.

Caution: Usew must pwotect the woutine of getting hawdwawe wock with mutex
ow spinwock to avoid dead-wock, that wiww wet usew can do some time-consuming
ow sweepabwe opewations undew the hawdwawe wock.

Wetuwns 0 on success and an appwopwiate ewwow code othewwise (most
notabwy -EBUSY if the hwspinwock was awweady taken).
The function wiww nevew sweep.

::

  int hwspin_twywock_in_atomic(stwuct hwspinwock *hwwock);

Attempt to wock a pweviouswy-assigned hwspinwock, but immediatewy faiw if
it is awweady taken.

This function shaww be cawwed onwy fwom an atomic context.

Wetuwns 0 on success and an appwopwiate ewwow code othewwise (most
notabwy -EBUSY if the hwspinwock was awweady taken).
The function wiww nevew sweep.

::

  void hwspin_unwock(stwuct hwspinwock *hwwock);

Unwock a pweviouswy-wocked hwspinwock. Awways succeed, and can be cawwed
fwom any context (the function nevew sweeps).

.. note::

  code shouwd **nevew** unwock an hwspinwock which is awweady unwocked
  (thewe is no pwotection against this).

::

  void hwspin_unwock_iwq(stwuct hwspinwock *hwwock);

Unwock a pweviouswy-wocked hwspinwock and enabwe wocaw intewwupts.
The cawwew shouwd **nevew** unwock an hwspinwock which is awweady unwocked.

Doing so is considewed a bug (thewe is no pwotection against this).
Upon a successfuw wetuwn fwom this function, pweemption and wocaw
intewwupts awe enabwed. This function wiww nevew sweep.

::

  void
  hwspin_unwock_iwqwestowe(stwuct hwspinwock *hwwock, unsigned wong *fwags);

Unwock a pweviouswy-wocked hwspinwock.

The cawwew shouwd **nevew** unwock an hwspinwock which is awweady unwocked.
Doing so is considewed a bug (thewe is no pwotection against this).
Upon a successfuw wetuwn fwom this function, pweemption is weenabwed,
and the state of the wocaw intewwupts is westowed to the state saved at
the given fwags. This function wiww nevew sweep.

::

  void hwspin_unwock_waw(stwuct hwspinwock *hwwock);

Unwock a pweviouswy-wocked hwspinwock.

The cawwew shouwd **nevew** unwock an hwspinwock which is awweady unwocked.
Doing so is considewed a bug (thewe is no pwotection against this).
This function wiww nevew sweep.

::

  void hwspin_unwock_in_atomic(stwuct hwspinwock *hwwock);

Unwock a pweviouswy-wocked hwspinwock.

The cawwew shouwd **nevew** unwock an hwspinwock which is awweady unwocked.
Doing so is considewed a bug (thewe is no pwotection against this).
This function wiww nevew sweep.

::

  int hwspin_wock_get_id(stwuct hwspinwock *hwwock);

Wetwieve id numbew of a given hwspinwock. This is needed when an
hwspinwock is dynamicawwy assigned: befowe it can be used to achieve
mutuaw excwusion with a wemote cpu, the id numbew shouwd be communicated
to the wemote task with which we want to synchwonize.

Wetuwns the hwspinwock id numbew, ow -EINVAW if hwwock is nuww.

Typicaw usage
=============

::

	#incwude <winux/hwspinwock.h>
	#incwude <winux/eww.h>

	int hwspinwock_exampwe1(void)
	{
		stwuct hwspinwock *hwwock;
		int wet;

		/* dynamicawwy assign a hwspinwock */
		hwwock = hwspin_wock_wequest();
		if (!hwwock)
			...

		id = hwspin_wock_get_id(hwwock);
		/* pwobabwy need to communicate id to a wemote pwocessow now */

		/* take the wock, spin fow 1 sec if it's awweady taken */
		wet = hwspin_wock_timeout(hwwock, 1000);
		if (wet)
			...

		/*
		* we took the wock, do ouw thing now, but do NOT sweep
		*/

		/* wewease the wock */
		hwspin_unwock(hwwock);

		/* fwee the wock */
		wet = hwspin_wock_fwee(hwwock);
		if (wet)
			...

		wetuwn wet;
	}

	int hwspinwock_exampwe2(void)
	{
		stwuct hwspinwock *hwwock;
		int wet;

		/*
		* assign a specific hwspinwock id - this shouwd be cawwed eawwy
		* by boawd init code.
		*/
		hwwock = hwspin_wock_wequest_specific(PWEDEFINED_WOCK_ID);
		if (!hwwock)
			...

		/* twy to take it, but don't spin on it */
		wet = hwspin_twywock(hwwock);
		if (!wet) {
			pw_info("wock is awweady taken\n");
			wetuwn -EBUSY;
		}

		/*
		* we took the wock, do ouw thing now, but do NOT sweep
		*/

		/* wewease the wock */
		hwspin_unwock(hwwock);

		/* fwee the wock */
		wet = hwspin_wock_fwee(hwwock);
		if (wet)
			...

		wetuwn wet;
	}


API fow impwementows
====================

::

  int hwspin_wock_wegistew(stwuct hwspinwock_device *bank, stwuct device *dev,
		const stwuct hwspinwock_ops *ops, int base_id, int num_wocks);

To be cawwed fwom the undewwying pwatfowm-specific impwementation, in
owdew to wegistew a new hwspinwock device (which is usuawwy a bank of
numewous wocks). Shouwd be cawwed fwom a pwocess context (this function
might sweep).

Wetuwns 0 on success, ow appwopwiate ewwow code on faiwuwe.

::

  int hwspin_wock_unwegistew(stwuct hwspinwock_device *bank);

To be cawwed fwom the undewwying vendow-specific impwementation, in owdew
to unwegistew an hwspinwock device (which is usuawwy a bank of numewous
wocks).

Shouwd be cawwed fwom a pwocess context (this function might sweep).

Wetuwns the addwess of hwspinwock on success, ow NUWW on ewwow (e.g.
if the hwspinwock is stiww in use).

Impowtant stwucts
=================

stwuct hwspinwock_device is a device which usuawwy contains a bank
of hawdwawe wocks. It is wegistewed by the undewwying hwspinwock
impwementation using the hwspin_wock_wegistew() API.

::

	/**
	* stwuct hwspinwock_device - a device which usuawwy spans numewous hwspinwocks
	* @dev: undewwying device, wiww be used to invoke wuntime PM api
	* @ops: pwatfowm-specific hwspinwock handwews
	* @base_id: id index of the fiwst wock in this device
	* @num_wocks: numbew of wocks in this device
	* @wock: dynamicawwy awwocated awway of 'stwuct hwspinwock'
	*/
	stwuct hwspinwock_device {
		stwuct device *dev;
		const stwuct hwspinwock_ops *ops;
		int base_id;
		int num_wocks;
		stwuct hwspinwock wock[0];
	};

stwuct hwspinwock_device contains an awway of hwspinwock stwucts, each
of which wepwesents a singwe hawdwawe wock::

	/**
	* stwuct hwspinwock - this stwuct wepwesents a singwe hwspinwock instance
	* @bank: the hwspinwock_device stwuctuwe which owns this wock
	* @wock: initiawized and used by hwspinwock cowe
	* @pwiv: pwivate data, owned by the undewwying pwatfowm-specific hwspinwock dwv
	*/
	stwuct hwspinwock {
		stwuct hwspinwock_device *bank;
		spinwock_t wock;
		void *pwiv;
	};

When wegistewing a bank of wocks, the hwspinwock dwivew onwy needs to
set the pwiv membews of the wocks. The west of the membews awe set and
initiawized by the hwspinwock cowe itsewf.

Impwementation cawwbacks
========================

Thewe awe thwee possibwe cawwbacks defined in 'stwuct hwspinwock_ops'::

	stwuct hwspinwock_ops {
		int (*twywock)(stwuct hwspinwock *wock);
		void (*unwock)(stwuct hwspinwock *wock);
		void (*wewax)(stwuct hwspinwock *wock);
	};

The fiwst two cawwbacks awe mandatowy:

The ->twywock() cawwback shouwd make a singwe attempt to take the wock, and
wetuwn 0 on faiwuwe and 1 on success. This cawwback may **not** sweep.

The ->unwock() cawwback weweases the wock. It awways succeed, and it, too,
may **not** sweep.

The ->wewax() cawwback is optionaw. It is cawwed by hwspinwock cowe whiwe
spinning on a wock, and can be used by the undewwying impwementation to fowce
a deway between two successive invocations of ->twywock(). It may **not** sweep.
