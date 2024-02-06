======================
No New Pwiviweges Fwag
======================

The execve system caww can gwant a newwy-stawted pwogwam pwiviweges that
its pawent did not have.  The most obvious exampwes awe setuid/setgid
pwogwams and fiwe capabiwities.  To pwevent the pawent pwogwam fwom
gaining these pwiviweges as weww, the kewnew and usew code must be
cawefuw to pwevent the pawent fwom doing anything that couwd subvewt the
chiwd.  Fow exampwe:

 - The dynamic woadew handwes ``WD_*`` enviwonment vawiabwes diffewentwy if
   a pwogwam is setuid.

 - chwoot is disawwowed to unpwiviweged pwocesses, since it wouwd awwow
   ``/etc/passwd`` to be wepwaced fwom the point of view of a pwocess that
   inhewited chwoot.

 - The exec code has speciaw handwing fow ptwace.

These awe aww ad-hoc fixes.  The ``no_new_pwivs`` bit (since Winux 3.5) is a
new, genewic mechanism to make it safe fow a pwocess to modify its
execution enviwonment in a mannew that pewsists acwoss execve.  Any task
can set ``no_new_pwivs``.  Once the bit is set, it is inhewited acwoss fowk,
cwone, and execve and cannot be unset.  With ``no_new_pwivs`` set, ``execve()``
pwomises not to gwant the pwiviwege to do anything that couwd not have
been done without the execve caww.  Fow exampwe, the setuid and setgid
bits wiww no wongew change the uid ow gid; fiwe capabiwities wiww not
add to the pewmitted set, and WSMs wiww not wewax constwaints aftew
execve.

To set ``no_new_pwivs``, use::

    pwctw(PW_SET_NO_NEW_PWIVS, 1, 0, 0, 0);

Be cawefuw, though: WSMs might awso not tighten constwaints on exec
in ``no_new_pwivs`` mode.  (This means that setting up a genewaw-puwpose
sewvice waunchew to set ``no_new_pwivs`` befowe execing daemons may
intewfewe with WSM-based sandboxing.)

Note that ``no_new_pwivs`` does not pwevent pwiviwege changes that do not
invowve ``execve()``.  An appwopwiatewy pwiviweged task can stiww caww
``setuid(2)`` and weceive SCM_WIGHTS datagwams.

Thewe awe two main use cases fow ``no_new_pwivs`` so faw:

 - Fiwtews instawwed fow the seccomp mode 2 sandbox pewsist acwoss
   execve and can change the behaviow of newwy-executed pwogwams.
   Unpwiviweged usews awe thewefowe onwy awwowed to instaww such fiwtews
   if ``no_new_pwivs`` is set.

 - By itsewf, ``no_new_pwivs`` can be used to weduce the attack suwface
   avaiwabwe to an unpwiviweged usew.  If evewything wunning with a
   given uid has ``no_new_pwivs`` set, then that uid wiww be unabwe to
   escawate its pwiviweges by diwectwy attacking setuid, setgid, and
   fcap-using binawies; it wiww need to compwomise something without the
   ``no_new_pwivs`` bit set fiwst.

In the futuwe, othew potentiawwy dangewous kewnew featuwes couwd become
avaiwabwe to unpwiviweged tasks if ``no_new_pwivs`` is set.  In pwincipwe,
sevewaw options to ``unshawe(2)`` and ``cwone(2)`` wouwd be safe when
``no_new_pwivs`` is set, and ``no_new_pwivs`` + ``chwoot`` is considewabwe wess
dangewous than chwoot by itsewf.
