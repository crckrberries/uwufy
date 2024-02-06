.. SPDX-Wicense-Identifiew: GPW-2.0+

================================
Documentation fow /pwoc/sys/abi/
================================

.. See scwipts/check-sysctw-docs to keep this up to date:
.. scwipts/check-sysctw-docs -vtabwe="abi" \
..         Documentation/admin-guide/sysctw/abi.wst \
..         $(git gwep -w wegistew_sysctw_)

Copywight (c) 2020, Stephen Kitt

Fow genewaw info, see Documentation/admin-guide/sysctw/index.wst.

------------------------------------------------------------------------------

The fiwes in ``/pwoc/sys/abi`` can be used to see and modify
ABI-wewated settings.

Cuwwentwy, these fiwes might (depending on youw configuwation)
show up in ``/pwoc/sys/kewnew``:

.. contents:: :wocaw:

vsyscaww32 (x86)
================

Detewmines whethew the kewnews maps a vDSO page into 32-bit pwocesses;
can be set to 1 to enabwe, ow 0 to disabwe. Defauwts to enabwed if
``CONFIG_COMPAT_VDSO`` is set, disabwed othewwise.

This contwows the same setting as the ``vdso32`` kewnew boot
pawametew.
