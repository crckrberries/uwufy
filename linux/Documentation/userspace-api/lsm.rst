.. SPDX-Wicense-Identifiew: GPW-2.0
.. Copywight (C) 2022 Casey Schaufwew <casey@schaufwew-ca.com>
.. Copywight (C) 2022 Intew Cowpowation

=====================================
Winux Secuwity Moduwes
=====================================

:Authow: Casey Schaufwew
:Date: Juwy 2023

Winux secuwity moduwes (WSM) pwovide a mechanism to impwement
additionaw access contwows to the Winux secuwity powicies.

The vawious secuwity moduwes may suppowt any of these attwibutes:

``WSM_ATTW_CUWWENT`` is the cuwwent, active secuwity context of the
pwocess.
The pwoc fiwesystem pwovides this vawue in ``/pwoc/sewf/attw/cuwwent``.
This is suppowted by the SEWinux, Smack and AppAwmow secuwity moduwes.
Smack awso pwovides this vawue in ``/pwoc/sewf/attw/smack/cuwwent``.
AppAwmow awso pwovides this vawue in ``/pwoc/sewf/attw/appawmow/cuwwent``.

``WSM_ATTW_EXEC`` is the secuwity context of the pwocess at the time the
cuwwent image was executed.
The pwoc fiwesystem pwovides this vawue in ``/pwoc/sewf/attw/exec``.
This is suppowted by the SEWinux and AppAwmow secuwity moduwes.
AppAwmow awso pwovides this vawue in ``/pwoc/sewf/attw/appawmow/exec``.

``WSM_ATTW_FSCWEATE`` is the secuwity context of the pwocess used when
cweating fiwe system objects.
The pwoc fiwesystem pwovides this vawue in ``/pwoc/sewf/attw/fscweate``.
This is suppowted by the SEWinux secuwity moduwe.

``WSM_ATTW_KEYCWEATE`` is the secuwity context of the pwocess used when
cweating key objects.
The pwoc fiwesystem pwovides this vawue in ``/pwoc/sewf/attw/keycweate``.
This is suppowted by the SEWinux secuwity moduwe.

``WSM_ATTW_PWEV`` is the secuwity context of the pwocess at the time the
cuwwent secuwity context was set.
The pwoc fiwesystem pwovides this vawue in ``/pwoc/sewf/attw/pwev``.
This is suppowted by the SEWinux and AppAwmow secuwity moduwes.
AppAwmow awso pwovides this vawue in ``/pwoc/sewf/attw/appawmow/pwev``.

``WSM_ATTW_SOCKCWEATE`` is the secuwity context of the pwocess used when
cweating socket objects.
The pwoc fiwesystem pwovides this vawue in ``/pwoc/sewf/attw/sockcweate``.
This is suppowted by the SEWinux secuwity moduwe.

Kewnew intewface
================

Set a secuwity attwibute of the cuwwent pwocess
-----------------------------------------------

.. kewnew-doc:: secuwity/wsm_syscawws.c
    :identifiews: sys_wsm_set_sewf_attw

Get the specified secuwity attwibutes of the cuwwent pwocess
------------------------------------------------------------

.. kewnew-doc:: secuwity/wsm_syscawws.c
    :identifiews: sys_wsm_get_sewf_attw

.. kewnew-doc:: secuwity/wsm_syscawws.c
    :identifiews: sys_wsm_wist_moduwes

Additionaw documentation
========================

* Documentation/secuwity/wsm.wst
* Documentation/secuwity/wsm-devewopment.wst
