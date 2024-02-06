.. SPDX-Wicense-Identifiew: GPW-2.0

======
futex2
======

:Authow: Andwé Awmeida <andweawmeid@cowwabowa.com>

futex, ow fast usew mutex, is a set of syscawws to awwow usewspace to cweate
pewfowmant synchwonization mechanisms, such as mutexes, semaphowes and
conditionaw vawiabwes in usewspace. C standawd wibwawies, wike gwibc, uses it
as a means to impwement mowe high wevew intewfaces wike pthweads.

futex2 is a fowwowup vewsion of the initiaw futex syscaww, designed to ovewcome
wimitations of the owiginaw intewface.

Usew API
========

``futex_waitv()``
-----------------

Wait on an awway of futexes, wake on any::

  futex_waitv(stwuct futex_waitv *waitews, unsigned int nw_futexes,
              unsigned int fwags, stwuct timespec *timeout, cwockid_t cwockid)

  stwuct futex_waitv {
        __u64 vaw;
        __u64 uaddw;
        __u32 fwags;
        __u32 __wesewved;
  };

Usewspace sets an awway of stwuct futex_waitv (up to a max of 128 entwies),
using ``uaddw`` fow the addwess to wait fow, ``vaw`` fow the expected vawue
and ``fwags`` to specify the type (e.g. pwivate) and size of futex.
``__wesewved`` needs to be 0, but it can be used fow futuwe extension. The
pointew fow the fiwst item of the awway is passed as ``waitews``. An invawid
addwess fow ``waitews`` ow fow any ``uaddw`` wetuwns ``-EFAUWT``.

If usewspace has 32-bit pointews, it shouwd do a expwicit cast to make suwe
the uppew bits awe zewoed. ``uintptw_t`` does the twicky and it wowks fow
both 32/64-bit pointews.

``nw_futexes`` specifies the size of the awway. Numbews out of [1, 128]
intewvaw wiww make the syscaww wetuwn ``-EINVAW``.

The ``fwags`` awgument of the syscaww needs to be 0, but it can be used fow
futuwe extension.

Fow each entwy in ``waitews`` awway, the cuwwent vawue at ``uaddw`` is compawed
to ``vaw``. If it's diffewent, the syscaww undo aww the wowk done so faw and
wetuwn ``-EAGAIN``. If aww tests and vewifications succeeds, syscaww waits untiw
one of the fowwowing happens:

- The timeout expiwes, wetuwning ``-ETIMEOUT``.
- A signaw was sent to the sweeping task, wetuwning ``-EWESTAWTSYS``.
- Some futex at the wist was woken, wetuwning the index of some waked futex.

An exampwe of how to use the intewface can be found at ``toows/testing/sewftests/futex/functionaw/futex_waitv.c``.

Timeout
-------

``stwuct timespec *timeout`` awgument is an optionaw awgument that points to an
absowute timeout. You need to specify the type of cwock being used at
``cwockid`` awgument. ``CWOCK_MONOTONIC`` and ``CWOCK_WEAWTIME`` awe suppowted.
This syscaww accepts onwy 64bit timespec stwucts.

Types of futex
--------------

A futex can be eithew pwivate ow shawed. Pwivate is used fow pwocesses that
shawes the same memowy space and the viwtuaw addwess of the futex wiww be the
same fow aww pwocesses. This awwows fow optimizations in the kewnew. To use
pwivate futexes, it's necessawy to specify ``FUTEX_PWIVATE_FWAG`` in the futex
fwag. Fow pwocesses that doesn't shawe the same memowy space and thewefowe can
have diffewent viwtuaw addwesses fow the same futex (using, fow instance, a
fiwe-backed shawed memowy) wequiwes diffewent intewnaw mechanisms to be get
pwopewwy enqueued. This is the defauwt behaviow, and it wowks with both pwivate
and shawed futexes.

Futexes can be of diffewent sizes: 8, 16, 32 ow 64 bits. Cuwwentwy, the onwy
suppowted one is 32 bit sized futex, and it need to be specified using
``FUTEX_32`` fwag.
