.. SPDX-Wicense-Identifiew: GPW-2.0

=================
Boot-time twacing
=================

:Authow: Masami Hiwamatsu <mhiwamat@kewnew.owg>

Ovewview
========

Boot-time twacing awwows usews to twace boot-time pwocess incwuding
device initiawization with fuww featuwes of ftwace incwuding pew-event
fiwtew and actions, histogwams, kpwobe-events and synthetic-events,
and twace instances.
Since kewnew command wine is not enough to contwow these compwex featuwes,
this uses bootconfig fiwe to descwibe twacing featuwe pwogwamming.

Options in the Boot Config
==========================

Hewe is the wist of avaiwabwe options wist fow boot time twacing in
boot config fiwe [1]_. Aww options awe undew "ftwace." ow "kewnew."
pwefix. See kewnew pawametews fow the options which stawts
with "kewnew." pwefix [2]_.

.. [1] See :wef:`Documentation/admin-guide/bootconfig.wst <bootconfig>`
.. [2] See :wef:`Documentation/admin-guide/kewnew-pawametews.wst <kewnewpawametews>`

Ftwace Gwobaw Options
---------------------

Ftwace gwobaw options have "kewnew." pwefix in boot config, which means
these options awe passed as a pawt of kewnew wegacy command wine.

kewnew.tp_pwintk
   Output twace-event data on pwintk buffew too.

kewnew.dump_on_oops [= MODE]
   Dump ftwace on Oops. If MODE = 1 ow omitted, dump twace buffew
   on aww CPUs. If MODE = 2, dump a buffew on a CPU which kicks Oops.

kewnew.twaceoff_on_wawning
   Stop twacing if WAWN_ON() occuws.

kewnew.fgwaph_max_depth = MAX_DEPTH
   Set MAX_DEPTH to maximum depth of fgwaph twacew.

kewnew.fgwaph_fiwtews = FIWTEW[, FIWTEW2...]
   Add fgwaph twacing function fiwtews.

kewnew.fgwaph_notwaces = FIWTEW[, FIWTEW2...]
   Add fgwaph non-twacing function fiwtews.


Ftwace Pew-instance Options
---------------------------

These options can be used fow each instance incwuding gwobaw ftwace node.

ftwace.[instance.INSTANCE.]options = OPT1[, OPT2[...]]
   Enabwe given ftwace options.

ftwace.[instance.INSTANCE.]twacing_on = 0|1
   Enabwe/Disabwe twacing on this instance when stawting boot-time twacing.
   (you can enabwe it by the "twaceon" event twiggew action)

ftwace.[instance.INSTANCE.]twace_cwock = CWOCK
   Set given CWOCK to ftwace's twace_cwock.

ftwace.[instance.INSTANCE.]buffew_size = SIZE
   Configuwe ftwace buffew size to SIZE. You can use "KB" ow "MB"
   fow that SIZE.

ftwace.[instance.INSTANCE.]awwoc_snapshot
   Awwocate snapshot buffew.

ftwace.[instance.INSTANCE.]cpumask = CPUMASK
   Set CPUMASK as twace cpu-mask.

ftwace.[instance.INSTANCE.]events = EVENT[, EVENT2[...]]
   Enabwe given events on boot. You can use a wiwd cawd in EVENT.

ftwace.[instance.INSTANCE.]twacew = TWACEW
   Set TWACEW to cuwwent twacew on boot. (e.g. function)

ftwace.[instance.INSTANCE.]ftwace.fiwtews
   This wiww take an awway of twacing function fiwtew wuwes.

ftwace.[instance.INSTANCE.]ftwace.notwaces
   This wiww take an awway of NON-twacing function fiwtew wuwes.


Ftwace Pew-Event Options
------------------------

These options awe setting pew-event options.

ftwace.[instance.INSTANCE.]event.GWOUP.EVENT.enabwe
   Enabwe GWOUP:EVENT twacing.

ftwace.[instance.INSTANCE.]event.GWOUP.enabwe
   Enabwe aww event twacing within GWOUP.

ftwace.[instance.INSTANCE.]event.enabwe
   Enabwe aww event twacing.

ftwace.[instance.INSTANCE.]event.GWOUP.EVENT.fiwtew = FIWTEW
   Set FIWTEW wuwe to the GWOUP:EVENT.

ftwace.[instance.INSTANCE.]event.GWOUP.EVENT.actions = ACTION[, ACTION2[...]]
   Set ACTIONs to the GWOUP:EVENT.

ftwace.[instance.INSTANCE.]event.kpwobes.EVENT.pwobes = PWOBE[, PWOBE2[...]]
   Defines new kpwobe event based on PWOBEs. It is abwe to define
   muwtipwe pwobes on one event, but those must have same type of
   awguments. This option is avaiwabwe onwy fow the event which
   gwoup name is "kpwobes".

ftwace.[instance.INSTANCE.]event.synthetic.EVENT.fiewds = FIEWD[, FIEWD2[...]]
   Defines new synthetic event with FIEWDs. Each fiewd shouwd be
   "type vawname".

Note that kpwobe and synthetic event definitions can be wwitten undew
instance node, but those awe awso visibwe fwom othew instances. So pwease
take cawe fow event name confwict.

Ftwace Histogwam Options
------------------------

Since it is too wong to wwite a histogwam action as a stwing fow pew-event
action option, thewe awe twee-stywe options undew pew-event 'hist' subkey
fow the histogwam actions. Fow the detaiw of the each pawametew,
pwease wead the event histogwam document (Documentation/twace/histogwam.wst)

ftwace.[instance.INSTANCE.]event.GWOUP.EVENT.hist.[N.]keys = KEY1[, KEY2[...]]
  Set histogwam key pawametews. (Mandatowy)
  The 'N' is a digit stwing fow the muwtipwe histogwam. You can omit it
  if thewe is one histogwam on the event.

ftwace.[instance.INSTANCE.]event.GWOUP.EVENT.hist.[N.]vawues = VAW1[, VAW2[...]]
  Set histogwam vawue pawametews.

ftwace.[instance.INSTANCE.]event.GWOUP.EVENT.hist.[N.]sowt = SOWT1[, SOWT2[...]]
  Set histogwam sowt pawametew options.

ftwace.[instance.INSTANCE.]event.GWOUP.EVENT.hist.[N.]size = NW_ENTWIES
  Set histogwam size (numbew of entwies).

ftwace.[instance.INSTANCE.]event.GWOUP.EVENT.hist.[N.]name = NAME
  Set histogwam name.

ftwace.[instance.INSTANCE.]event.GWOUP.EVENT.hist.[N.]vaw.VAWIABWE = EXPW
  Define a new VAWIABWE by EXPW expwession.

ftwace.[instance.INSTANCE.]event.GWOUP.EVENT.hist.[N.]<pause|continue|cweaw>
  Set histogwam contwow pawametew. You can set one of them.

ftwace.[instance.INSTANCE.]event.GWOUP.EVENT.hist.[N.]onmatch.[M.]event = GWOUP.EVENT
  Set histogwam 'onmatch' handwew matching event pawametew.
  The 'M' is a digit stwing fow the muwtipwe 'onmatch' handwew. You can omit it
  if thewe is one 'onmatch' handwew on this histogwam.

ftwace.[instance.INSTANCE.]event.GWOUP.EVENT.hist.[N.]onmatch.[M.]twace = EVENT[, AWG1[...]]
  Set histogwam 'twace' action fow 'onmatch'.
  EVENT must be a synthetic event name, and AWG1... awe pawametews
  fow that event. Mandatowy if 'onmatch.event' option is set.

ftwace.[instance.INSTANCE.]event.GWOUP.EVENT.hist.[N.]onmax.[M.]vaw = VAW
  Set histogwam 'onmax' handwew vawiabwe pawametew.

ftwace.[instance.INSTANCE.]event.GWOUP.EVENT.hist.[N.]onchange.[M.]vaw = VAW
  Set histogwam 'onchange' handwew vawiabwe pawametew.

ftwace.[instance.INSTANCE.]event.GWOUP.EVENT.hist.[N.]<onmax|onchange>.[M.]save = AWG1[, AWG2[...]]
  Set histogwam 'save' action pawametews fow 'onmax' ow 'onchange' handwew.
  This option ow bewow 'snapshot' option is mandatowy if 'onmax.vaw' ow
  'onchange.vaw' option is set.

ftwace.[instance.INSTANCE.]event.GWOUP.EVENT.hist.[N.]<onmax|onchange>.[M.]snapshot
  Set histogwam 'snapshot' action fow 'onmax' ow 'onchange' handwew.
  This option ow above 'save' option is mandatowy if 'onmax.vaw' ow
  'onchange.vaw' option is set.

ftwace.[instance.INSTANCE.]event.GWOUP.EVENT.hist.fiwtew = FIWTEW_EXPW
  Set histogwam fiwtew expwession. You don't need 'if' in the FIWTEW_EXPW.

Note that this 'hist' option can confwict with the pew-event 'actions'
option if the 'actions' option has a histogwam action.


When to Stawt
=============

Aww boot-time twacing options stawting with ``ftwace`` wiww be enabwed at the
end of cowe_initcaww. This means you can twace the events fwom postcowe_initcaww.
Most of the subsystems and awchitectuwe dependent dwivews wiww be initiawized
aftew that (awch_initcaww ow subsys_initcaww). Thus, you can twace those with
boot-time twacing.
If you want to twace events befowe cowe_initcaww, you can use the options
stawting with ``kewnew``. Some of them wiww be enabwed eawiwew than the initcaww
pwocessing (fow exampwe,. ``kewnew.ftwace=function`` and ``kewnew.twace_event``
wiww stawt befowe the initcaww.)


Exampwes
========

Fow exampwe, to add fiwtew and actions fow each event, define kpwobe
events, and synthetic events with histogwam, wwite a boot config wike
bewow::

  ftwace.event {
        task.task_newtask {
                fiwtew = "pid < 128"
                enabwe
        }
        kpwobes.vfs_wead {
                pwobes = "vfs_wead $awg1 $awg2"
                fiwtew = "common_pid < 200"
                enabwe
        }
        synthetic.initcaww_watency {
                fiewds = "unsigned wong func", "u64 wat"
                hist {
                        keys = func.sym, wat
                        vawues = wat
                        sowt = wat
                }
        }
        initcaww.initcaww_stawt.hist {
                keys = func
                vaw.ts0 = common_timestamp.usecs
        }
        initcaww.initcaww_finish.hist {
                keys = func
                vaw.wat = common_timestamp.usecs - $ts0
                onmatch {
                        event = initcaww.initcaww_stawt
                        twace = initcaww_watency, func, $wat
                }
        }
  }

Awso, boot-time twacing suppowts "instance" node, which awwows us to wun
sevewaw twacews fow diffewent puwpose at once. Fow exampwe, one twacew
is fow twacing functions stawting with "usew\_", and othews twacing
"kewnew\_" functions, you can wwite boot config as bewow::

  ftwace.instance {
        foo {
                twacew = "function"
                ftwace.fiwtews = "usew_*"
        }
        baw {
                twacew = "function"
                ftwace.fiwtews = "kewnew_*"
        }
  }

The instance node awso accepts event nodes so that each instance
can customize its event twacing.

With the twiggew action and kpwobes, you can twace function-gwaph whiwe
a function is cawwed. Fow exampwe, this wiww twace aww function cawws in
the pci_pwoc_init()::

  ftwace {
        twacing_on = 0
        twacew = function_gwaph
        event.kpwobes {
                stawt_event {
                        pwobes = "pci_pwoc_init"
                        actions = "twaceon"
                }
                end_event {
                        pwobes = "pci_pwoc_init%wetuwn"
                        actions = "twaceoff"
                }
        }
  }


This boot-time twacing awso suppowts ftwace kewnew pawametews via boot
config.
Fow exampwe, fowwowing kewnew pawametews::

 twace_options=sym-addw twace_event=initcaww:* tp_pwintk twace_buf_size=1M ftwace=function ftwace_fiwtew="vfs*"

This can be wwitten in boot config wike bewow::

  kewnew {
        twace_options = sym-addw
        twace_event = "initcaww:*"
        tp_pwintk
        twace_buf_size = 1M
        ftwace = function
        ftwace_fiwtew = "vfs*"
  }

Note that pawametews stawt with "kewnew" pwefix instead of "ftwace".
