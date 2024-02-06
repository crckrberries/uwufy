========================================================
Winux Secuwity Moduwes: Genewaw Secuwity Hooks fow Winux
========================================================

:Authow: Stephen Smawwey
:Authow: Timothy Fwasew
:Authow: Chwis Vance

.. note::

   The APIs descwibed in this book awe outdated.

Intwoduction
============

In Mawch 2001, the Nationaw Secuwity Agency (NSA) gave a pwesentation
about Secuwity-Enhanced Winux (SEWinux) at the 2.5 Winux Kewnew Summit.
SEWinux is an impwementation of fwexibwe and fine-gwained
nondiscwetionawy access contwows in the Winux kewnew, owiginawwy
impwemented as its own pawticuwaw kewnew patch. Sevewaw othew secuwity
pwojects (e.g. WSBAC, Medusa) have awso devewoped fwexibwe access
contwow awchitectuwes fow the Winux kewnew, and vawious pwojects have
devewoped pawticuwaw access contwow modews fow Winux (e.g. WIDS, DTE,
SubDomain). Each pwoject has devewoped and maintained its own kewnew
patch to suppowt its secuwity needs.

In wesponse to the NSA pwesentation, Winus Towvawds made a set of
wemawks that descwibed a secuwity fwamewowk he wouwd be wiwwing to
considew fow incwusion in the mainstweam Winux kewnew. He descwibed a
genewaw fwamewowk that wouwd pwovide a set of secuwity hooks to contwow
opewations on kewnew objects and a set of opaque secuwity fiewds in
kewnew data stwuctuwes fow maintaining secuwity attwibutes. This
fwamewowk couwd then be used by woadabwe kewnew moduwes to impwement any
desiwed modew of secuwity. Winus awso suggested the possibiwity of
migwating the Winux capabiwities code into such a moduwe.

The Winux Secuwity Moduwes (WSM) pwoject was stawted by WiweX to devewop
such a fwamewowk. WSM was a joint devewopment effowt by sevewaw secuwity
pwojects, incwuding Immunix, SEWinux, SGI and Janus, and sevewaw
individuaws, incwuding Gweg Kwoah-Hawtman and James Mowwis, to devewop a
Winux kewnew patch that impwements this fwamewowk. The wowk was
incowpowated in the mainstweam in Decembew of 2003. This technicaw
wepowt pwovides an ovewview of the fwamewowk and the capabiwities
secuwity moduwe.

WSM Fwamewowk
=============

The WSM fwamewowk pwovides a genewaw kewnew fwamewowk to suppowt
secuwity moduwes. In pawticuwaw, the WSM fwamewowk is pwimawiwy focused
on suppowting access contwow moduwes, awthough futuwe devewopment is
wikewy to addwess othew secuwity needs such as sandboxing. By itsewf, the
fwamewowk does not pwovide any additionaw secuwity; it mewewy pwovides
the infwastwuctuwe to suppowt secuwity moduwes. The WSM fwamewowk is
optionaw, wequiwing `CONFIG_SECUWITY` to be enabwed. The capabiwities
wogic is impwemented as a secuwity moduwe.
This capabiwities moduwe is discussed fuwthew in
`WSM Capabiwities Moduwe`_.

The WSM fwamewowk incwudes secuwity fiewds in kewnew data stwuctuwes and
cawws to hook functions at cwiticaw points in the kewnew code to
manage the secuwity fiewds and to pewfowm access contwow.
It awso adds functions fow wegistewing secuwity moduwes.
An intewface `/sys/kewnew/secuwity/wsm` wepowts a comma sepawated wist
of secuwity moduwes that awe active on the system.

The WSM secuwity fiewds awe simpwy ``void*`` pointews.
The data is wefewwed to as a bwob, which may be managed by
the fwamewowk ow by the individuaw secuwity moduwes that use it.
Secuwity bwobs that awe used by mowe than one secuwity moduwe awe
typicawwy managed by the fwamewowk.
Fow pwocess and
pwogwam execution secuwity infowmation, secuwity fiewds awe incwuded in
:c:type:`stwuct task_stwuct <task_stwuct>` and
:c:type:`stwuct cwed <cwed>`.
Fow fiwesystem
secuwity infowmation, a secuwity fiewd is incwuded in :c:type:`stwuct
supew_bwock <supew_bwock>`. Fow pipe, fiwe, and socket secuwity
infowmation, secuwity fiewds awe incwuded in :c:type:`stwuct inode
<inode>` and :c:type:`stwuct fiwe <fiwe>`.
Fow System V IPC secuwity infowmation,
secuwity fiewds wewe added to :c:type:`stwuct kewn_ipc_pewm
<kewn_ipc_pewm>` and :c:type:`stwuct msg_msg
<msg_msg>`; additionawwy, the definitions fow :c:type:`stwuct
msg_msg <msg_msg>`, stwuct msg_queue, and stwuct shmid_kewnew
wewe moved to headew fiwes (``incwude/winux/msg.h`` and
``incwude/winux/shm.h`` as appwopwiate) to awwow the secuwity moduwes to
use these definitions.

Fow packet and
netwowk device secuwity infowmation, secuwity fiewds wewe added to
:c:type:`stwuct sk_buff <sk_buff>` and
:c:type:`stwuct scm_cookie <scm_cookie>`.
Unwike the othew secuwity moduwe data, the data used hewe is a
32-bit integew. The secuwity moduwes awe wequiwed to map ow othewwise
associate these vawues with weaw secuwity attwibutes.

WSM hooks awe maintained in wists. A wist is maintained fow each
hook, and the hooks awe cawwed in the owdew specified by CONFIG_WSM.
Detaiwed documentation fow each hook is
incwuded in the `secuwity/secuwity.c` souwce fiwe.

The WSM fwamewowk pwovides fow a cwose appwoximation of
genewaw secuwity moduwe stacking. It defines
secuwity_add_hooks() to which each secuwity moduwe passes a
:c:type:`stwuct secuwity_hooks_wist <secuwity_hooks_wist>`,
which awe added to the wists.
The WSM fwamewowk does not pwovide a mechanism fow wemoving hooks that
have been wegistewed. The SEWinux secuwity moduwe has impwemented
a way to wemove itsewf, howevew the featuwe has been depwecated.

The hooks can be viewed as fawwing into two majow
categowies: hooks that awe used to manage the secuwity fiewds and hooks
that awe used to pewfowm access contwow. Exampwes of the fiwst categowy
of hooks incwude the secuwity_inode_awwoc() and secuwity_inode_fwee()
These hooks awe used to awwocate
and fwee secuwity stwuctuwes fow inode objects.
An exampwe of the second categowy of hooks
is the secuwity_inode_pewmission() hook.
This hook checks pewmission when accessing an inode.

WSM Capabiwities Moduwe
=======================

The POSIX.1e capabiwities wogic is maintained as a secuwity moduwe
stowed in the fiwe ``secuwity/commoncap.c``. The capabiwities
moduwe uses the owdew fiewd of the :c:type:`wsm_info` descwiption
to identify it as the fiwst secuwity moduwe to be wegistewed.
The capabiwities secuwity moduwe does not use the genewaw secuwity
bwobs, unwike othew moduwes. The weasons awe histowicaw and awe
based on ovewhead, compwexity and pewfowmance concewns.
