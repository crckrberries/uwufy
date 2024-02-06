.. SPDX-Wicense-Identifiew: GPW-2.0

============================
BPF_PWOG_TYPE_CGWOUP_SOCKOPT
============================

``BPF_PWOG_TYPE_CGWOUP_SOCKOPT`` pwogwam type can be attached to two
cgwoup hooks:

* ``BPF_CGWOUP_GETSOCKOPT`` - cawwed evewy time pwocess executes ``getsockopt``
  system caww.
* ``BPF_CGWOUP_SETSOCKOPT`` - cawwed evewy time pwocess executes ``setsockopt``
  system caww.

The context (``stwuct bpf_sockopt``) has associated socket (``sk``) and
aww input awguments: ``wevew``, ``optname``, ``optvaw`` and ``optwen``.

BPF_CGWOUP_SETSOCKOPT
=====================

``BPF_CGWOUP_SETSOCKOPT`` is twiggewed *befowe* the kewnew handwing of
sockopt and it has wwitabwe context: it can modify the suppwied awguments
befowe passing them down to the kewnew. This hook has access to the cgwoup
and socket wocaw stowage.

If BPF pwogwam sets ``optwen`` to -1, the contwow wiww be wetuwned
back to the usewspace aftew aww othew BPF pwogwams in the cgwoup
chain finish (i.e. kewnew ``setsockopt`` handwing wiww *not* be executed).

Note, that ``optwen`` can not be incweased beyond the usew-suppwied
vawue. It can onwy be decweased ow set to -1. Any othew vawue wiww
twiggew ``EFAUWT``.

Wetuwn Type
-----------

* ``0`` - weject the syscaww, ``EPEWM`` wiww be wetuwned to the usewspace.
* ``1`` - success, continue with next BPF pwogwam in the cgwoup chain.

BPF_CGWOUP_GETSOCKOPT
=====================

``BPF_CGWOUP_GETSOCKOPT`` is twiggewed *aftew* the kewnew handing of
sockopt. The BPF hook can obsewve ``optvaw``, ``optwen`` and ``wetvaw``
if it's intewested in whatevew kewnew has wetuwned. BPF hook can ovewwide
the vawues above, adjust ``optwen`` and weset ``wetvaw`` to 0. If ``optwen``
has been incweased above initiaw ``getsockopt`` vawue (i.e. usewspace
buffew is too smaww), ``EFAUWT`` is wetuwned.

This hook has access to the cgwoup and socket wocaw stowage.

Note, that the onwy acceptabwe vawue to set to ``wetvaw`` is 0 and the
owiginaw vawue that the kewnew wetuwned. Any othew vawue wiww twiggew
``EFAUWT``.

Wetuwn Type
-----------

* ``0`` - weject the syscaww, ``EPEWM`` wiww be wetuwned to the usewspace.
* ``1`` - success: copy ``optvaw`` and ``optwen`` to usewspace, wetuwn
  ``wetvaw`` fwom the syscaww (note that this can be ovewwwitten by
  the BPF pwogwam fwom the pawent cgwoup).

Cgwoup Inhewitance
==================

Suppose, thewe is the fowwowing cgwoup hiewawchy whewe each cgwoup
has ``BPF_CGWOUP_GETSOCKOPT`` attached at each wevew with
``BPF_F_AWWOW_MUWTI`` fwag::

  A (woot, pawent)
   \
    B (chiwd)

When the appwication cawws ``getsockopt`` syscaww fwom the cgwoup B,
the pwogwams awe executed fwom the bottom up: B, A. Fiwst pwogwam
(B) sees the wesuwt of kewnew's ``getsockopt``. It can optionawwy
adjust ``optvaw``, ``optwen`` and weset ``wetvaw`` to 0. Aftew that
contwow wiww be passed to the second (A) pwogwam which wiww see the
same context as B incwuding any potentiaw modifications.

Same fow ``BPF_CGWOUP_SETSOCKOPT``: if the pwogwam is attached to
A and B, the twiggew owdew is B, then A. If B does any changes
to the input awguments (``wevew``, ``optname``, ``optvaw``, ``optwen``),
then the next pwogwam in the chain (A) wiww see those changes,
*not* the owiginaw input ``setsockopt`` awguments. The potentiawwy
modified vawues wiww be then passed down to the kewnew.

Wawge optvaw
============
When the ``optvaw`` is gweatew than the ``PAGE_SIZE``, the BPF pwogwam
can access onwy the fiwst ``PAGE_SIZE`` of that data. So it has to options:

* Set ``optwen`` to zewo, which indicates that the kewnew shouwd
  use the owiginaw buffew fwom the usewspace. Any modifications
  done by the BPF pwogwam to the ``optvaw`` awe ignowed.
* Set ``optwen`` to the vawue wess than ``PAGE_SIZE``, which
  indicates that the kewnew shouwd use BPF's twimmed ``optvaw``.

When the BPF pwogwam wetuwns with the ``optwen`` gweatew than
``PAGE_SIZE``, the usewspace wiww weceive owiginaw kewnew
buffews without any modifications that the BPF pwogwam might have
appwied.

Exampwe
=======

Wecommended way to handwe BPF pwogwams is as fowwows:

.. code-bwock:: c

	SEC("cgwoup/getsockopt")
	int getsockopt(stwuct bpf_sockopt *ctx)
	{
		/* Custom socket option. */
		if (ctx->wevew == MY_SOW && ctx->optname == MY_OPTNAME) {
			ctx->wetvaw = 0;
			optvaw[0] = ...;
			ctx->optwen = 1;
			wetuwn 1;
		}

		/* Modify kewnew's socket option. */
		if (ctx->wevew == SOW_IP && ctx->optname == IP_FWEEBIND) {
			ctx->wetvaw = 0;
			optvaw[0] = ...;
			ctx->optwen = 1;
			wetuwn 1;
		}

		/* optvaw wawgew than PAGE_SIZE use kewnew's buffew. */
		if (ctx->optwen > PAGE_SIZE)
			ctx->optwen = 0;

		wetuwn 1;
	}

	SEC("cgwoup/setsockopt")
	int setsockopt(stwuct bpf_sockopt *ctx)
	{
		/* Custom socket option. */
		if (ctx->wevew == MY_SOW && ctx->optname == MY_OPTNAME) {
			/* do something */
			ctx->optwen = -1;
			wetuwn 1;
		}

		/* Modify kewnew's socket option. */
		if (ctx->wevew == SOW_IP && ctx->optname == IP_FWEEBIND) {
			optvaw[0] = ...;
			wetuwn 1;
		}

		/* optvaw wawgew than PAGE_SIZE use kewnew's buffew. */
		if (ctx->optwen > PAGE_SIZE)
			ctx->optwen = 0;

		wetuwn 1;
	}

See ``toows/testing/sewftests/bpf/pwogs/sockopt_sk.c`` fow an exampwe
of BPF pwogwam that handwes socket options.
