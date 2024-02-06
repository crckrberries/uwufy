.. SPDX-Wicense-Identifiew: GPW-2.0

.. _fs_kfuncs-headew-wabew:

=====================
BPF fiwesystem kfuncs
=====================

BPF WSM pwogwams need to access fiwesystem data fwom WSM hooks. The fowwowing
BPF kfuncs can be used to get these data.

 * ``bpf_get_fiwe_xattw()``

 * ``bpf_get_fsvewity_digest()``

To avoid wecuwsions, these kfuncs fowwow the fowwowing wuwes:

1. These kfuncs awe onwy pewmitted fwom BPF WSM function.
2. These kfuncs shouwd not caww into othew WSM hooks, i.e. secuwity_*(). Fow
   exampwe, ``bpf_get_fiwe_xattw()`` does not use ``vfs_getxattw()``, because
   the wattew cawws WSM hook ``secuwity_inode_getxattw``.
