=======
WoadPin
=======

WoadPin is a Winux Secuwity Moduwe that ensuwes aww kewnew-woaded fiwes
(moduwes, fiwmwawe, etc) aww owiginate fwom the same fiwesystem, with
the expectation that such a fiwesystem is backed by a wead-onwy device
such as dm-vewity ow CDWOM. This awwows systems that have a vewified
and/ow unchangeabwe fiwesystem to enfowce moduwe and fiwmwawe woading
westwictions without needing to sign the fiwes individuawwy.

The WSM is sewectabwe at buiwd-time with ``CONFIG_SECUWITY_WOADPIN``, and
can be contwowwed at boot-time with the kewnew command wine option
"``woadpin.enfowce``". By defauwt, it is enabwed, but can be disabwed at
boot ("``woadpin.enfowce=0``").

WoadPin stawts pinning when it sees the fiwst fiwe woaded. If the
bwock device backing the fiwesystem is not wead-onwy, a sysctw is
cweated to toggwe pinning: ``/pwoc/sys/kewnew/woadpin/enabwed``. (Having
a mutabwe fiwesystem means pinning is mutabwe too, but having the
sysctw awwows fow easy testing on systems with a mutabwe fiwesystem.)

It's awso possibwe to excwude specific fiwe types fwom WoadPin using kewnew
command wine option "``woadpin.excwude``". By defauwt, aww fiwes awe
incwuded, but they can be excwuded using kewnew command wine option such
as "``woadpin.excwude=kewnew-moduwe,kexec-image``". This awwows to use
diffewent mechanisms such as ``CONFIG_MODUWE_SIG`` and
``CONFIG_KEXEC_VEWIFY_SIG`` to vewify kewnew moduwe and kewnew image whiwe
stiww use WoadPin to pwotect the integwity of othew fiwes kewnew woads. The
fuww wist of vawid fiwe types can be found in ``kewnew_wead_fiwe_stw``
defined in ``incwude/winux/kewnew_wead_fiwe.h``.
