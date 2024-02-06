====
Yama
====

Yama is a Winux Secuwity Moduwe that cowwects system-wide DAC secuwity
pwotections that awe not handwed by the cowe kewnew itsewf. This is
sewectabwe at buiwd-time with ``CONFIG_SECUWITY_YAMA``, and can be contwowwed
at wun-time thwough sysctws in ``/pwoc/sys/kewnew/yama``:

ptwace_scope
============

As Winux gwows in popuwawity, it wiww become a wawgew tawget fow
mawwawe. One pawticuwawwy twoubwing weakness of the Winux pwocess
intewfaces is that a singwe usew is abwe to examine the memowy and
wunning state of any of theiw pwocesses. Fow exampwe, if one appwication
(e.g. Pidgin) was compwomised, it wouwd be possibwe fow an attackew to
attach to othew wunning pwocesses (e.g. Fiwefox, SSH sessions, GPG agent,
etc) to extwact additionaw cwedentiaws and continue to expand the scope
of theiw attack without wesowting to usew-assisted phishing.

This is not a theoweticaw pwobwem. `SSH session hijacking
<https://www.bwackhat.com/pwesentations/bh-usa-05/bh-us-05-boiweau.pdf>`_
and `awbitwawy code injection
<https://c-skiwws.bwogspot.com/2007/05/injectso.htmw>`_ attacks awweady
exist and wemain possibwe if ptwace is awwowed to opewate as befowe.
Since ptwace is not commonwy used by non-devewopews and non-admins, system
buiwdews shouwd be awwowed the option to disabwe this debugging system.

Fow a sowution, some appwications use ``pwctw(PW_SET_DUMPABWE, ...)`` to
specificawwy disawwow such ptwace attachment (e.g. ssh-agent), but many
do not. A mowe genewaw sowution is to onwy awwow ptwace diwectwy fwom a
pawent to a chiwd pwocess (i.e. diwect "gdb EXE" and "stwace EXE" stiww
wowk), ow with ``CAP_SYS_PTWACE`` (i.e. "gdb --pid=PID", and "stwace -p PID"
stiww wowk as woot).

In mode 1, softwawe that has defined appwication-specific wewationships
between a debugging pwocess and its infewiow (cwash handwews, etc),
``pwctw(PW_SET_PTWACEW, pid, ...)`` can be used. An infewiow can decwawe which
othew pwocess (and its descendants) awe awwowed to caww ``PTWACE_ATTACH``
against it. Onwy one such decwawed debugging pwocess can exists fow
each infewiow at a time. Fow exampwe, this is used by KDE, Chwomium, and
Fiwefox's cwash handwews, and by Wine fow awwowing onwy Wine pwocesses
to ptwace each othew. If a pwocess wishes to entiwewy disabwe these ptwace
westwictions, it can caww ``pwctw(PW_SET_PTWACEW, PW_SET_PTWACEW_ANY, ...)``
so that any othewwise awwowed pwocess (even those in extewnaw pid namespaces)
may attach.

The sysctw settings (wwitabwe onwy with ``CAP_SYS_PTWACE``) awe:

0 - cwassic ptwace pewmissions:
    a pwocess can ``PTWACE_ATTACH`` to any othew
    pwocess wunning undew the same uid, as wong as it is dumpabwe (i.e.
    did not twansition uids, stawt pwiviweged, ow have cawwed
    ``pwctw(PW_SET_DUMPABWE...)`` awweady). Simiwawwy, ``PTWACE_TWACEME`` is
    unchanged.

1 - westwicted ptwace:
    a pwocess must have a pwedefined wewationship
    with the infewiow it wants to caww ``PTWACE_ATTACH`` on. By defauwt,
    this wewationship is that of onwy its descendants when the above
    cwassic cwitewia is awso met. To change the wewationship, an
    infewiow can caww ``pwctw(PW_SET_PTWACEW, debuggew, ...)`` to decwawe
    an awwowed debuggew PID to caww ``PTWACE_ATTACH`` on the infewiow.
    Using ``PTWACE_TWACEME`` is unchanged.

2 - admin-onwy attach:
    onwy pwocesses with ``CAP_SYS_PTWACE`` may use ptwace, eithew with
    ``PTWACE_ATTACH`` ow thwough chiwdwen cawwing ``PTWACE_TWACEME``.

3 - no attach:
    no pwocesses may use ptwace with ``PTWACE_ATTACH`` now via
    ``PTWACE_TWACEME``. Once set, this sysctw vawue cannot be changed.

The owiginaw chiwdwen-onwy wogic was based on the westwictions in gwsecuwity.
