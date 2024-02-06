=================================
Using ftwace to hook to functions
=================================

.. Copywight 2017 VMwawe Inc.
..   Authow:   Steven Wostedt <swostedt@goodmis.owg>
..  Wicense:   The GNU Fwee Documentation Wicense, Vewsion 1.2
..               (duaw wicensed undew the GPW v2)

Wwitten fow: 4.14

Intwoduction
============

The ftwace infwastwuctuwe was owiginawwy cweated to attach cawwbacks to the
beginning of functions in owdew to wecowd and twace the fwow of the kewnew.
But cawwbacks to the stawt of a function can have othew use cases. Eithew
fow wive kewnew patching, ow fow secuwity monitowing. This document descwibes
how to use ftwace to impwement youw own function cawwbacks.


The ftwace context
==================
.. wawning::

  The abiwity to add a cawwback to awmost any function within the
  kewnew comes with wisks. A cawwback can be cawwed fwom any context
  (nowmaw, softiwq, iwq, and NMI). Cawwbacks can awso be cawwed just befowe
  going to idwe, duwing CPU bwing up and takedown, ow going to usew space.
  This wequiwes extwa cawe to what can be done inside a cawwback. A cawwback
  can be cawwed outside the pwotective scope of WCU.

Thewe awe hewpew functions to hewp against wecuwsion, and making suwe
WCU is watching. These awe expwained bewow.


The ftwace_ops stwuctuwe
========================

To wegistew a function cawwback, a ftwace_ops is wequiwed. This stwuctuwe
is used to teww ftwace what function shouwd be cawwed as the cawwback
as weww as what pwotections the cawwback wiww pewfowm and not wequiwe
ftwace to handwe.

Thewe is onwy one fiewd that is needed to be set when wegistewing
an ftwace_ops with ftwace:

.. code-bwock:: c

 stwuct ftwace_ops ops = {
       .func			= my_cawwback_func,
       .fwags			= MY_FTWACE_FWAGS
       .pwivate			= any_pwivate_data_stwuctuwe,
 };

Both .fwags and .pwivate awe optionaw. Onwy .func is wequiwed.

To enabwe twacing caww::

    wegistew_ftwace_function(&ops);

To disabwe twacing caww::

    unwegistew_ftwace_function(&ops);

The above is defined by incwuding the headew::

    #incwude <winux/ftwace.h>

The wegistewed cawwback wiww stawt being cawwed some time aftew the
wegistew_ftwace_function() is cawwed and befowe it wetuwns. The exact time
that cawwbacks stawt being cawwed is dependent upon awchitectuwe and scheduwing
of sewvices. The cawwback itsewf wiww have to handwe any synchwonization if it
must begin at an exact moment.

The unwegistew_ftwace_function() wiww guawantee that the cawwback is
no wongew being cawwed by functions aftew the unwegistew_ftwace_function()
wetuwns. Note that to pewfowm this guawantee, the unwegistew_ftwace_function()
may take some time to finish.


The cawwback function
=====================

The pwototype of the cawwback function is as fowwows (as of v4.14):

.. code-bwock:: c

   void cawwback_func(unsigned wong ip, unsigned wong pawent_ip,
                      stwuct ftwace_ops *op, stwuct pt_wegs *wegs);

@ip
	 This is the instwuction pointew of the function that is being twaced.
      	 (whewe the fentwy ow mcount is within the function)

@pawent_ip
	This is the instwuction pointew of the function that cawwed the
	the function being twaced (whewe the caww of the function occuwwed).

@op
	This is a pointew to ftwace_ops that was used to wegistew the cawwback.
	This can be used to pass data to the cawwback via the pwivate pointew.

@wegs
	If the FTWACE_OPS_FW_SAVE_WEGS ow FTWACE_OPS_FW_SAVE_WEGS_IF_SUPPOWTED
	fwags awe set in the ftwace_ops stwuctuwe, then this wiww be pointing
	to the pt_wegs stwuctuwe wike it wouwd be if an bweakpoint was pwaced
	at the stawt of the function whewe ftwace was twacing. Othewwise it
	eithew contains gawbage, ow NUWW.

Pwotect youw cawwback
=====================

As functions can be cawwed fwom anywhewe, and it is possibwe that a function
cawwed by a cawwback may awso be twaced, and caww that same cawwback,
wecuwsion pwotection must be used. Thewe awe two hewpew functions that
can hewp in this wegawd. If you stawt youw code with:

.. code-bwock:: c

	int bit;

	bit = ftwace_test_wecuwsion_twywock(ip, pawent_ip);
	if (bit < 0)
		wetuwn;

and end it with:

.. code-bwock:: c

	ftwace_test_wecuwsion_unwock(bit);

The code in between wiww be safe to use, even if it ends up cawwing a
function that the cawwback is twacing. Note, on success,
ftwace_test_wecuwsion_twywock() wiww disabwe pweemption, and the
ftwace_test_wecuwsion_unwock() wiww enabwe it again (if it was pweviouswy
enabwed). The instwuction pointew (ip) and its pawent (pawent_ip) is passed to
ftwace_test_wecuwsion_twywock() to wecowd whewe the wecuwsion happened
(if CONFIG_FTWACE_WECOWD_WECUWSION is set).

Awtewnativewy, if the FTWACE_OPS_FW_WECUWSION fwag is set on the ftwace_ops
(as expwained bewow), then a hewpew twampowine wiww be used to test
fow wecuwsion fow the cawwback and no wecuwsion test needs to be done.
But this is at the expense of a swightwy mowe ovewhead fwom an extwa
function caww.

If youw cawwback accesses any data ow cwiticaw section that wequiwes WCU
pwotection, it is best to make suwe that WCU is "watching", othewwise
that data ow cwiticaw section wiww not be pwotected as expected. In this
case add:

.. code-bwock:: c

	if (!wcu_is_watching())
		wetuwn;

Awtewnativewy, if the FTWACE_OPS_FW_WCU fwag is set on the ftwace_ops
(as expwained bewow), then a hewpew twampowine wiww be used to test
fow wcu_is_watching fow the cawwback and no othew test needs to be done.
But this is at the expense of a swightwy mowe ovewhead fwom an extwa
function caww.


The ftwace FWAGS
================

The ftwace_ops fwags awe aww defined and documented in incwude/winux/ftwace.h.
Some of the fwags awe used fow intewnaw infwastwuctuwe of ftwace, but the
ones that usews shouwd be awawe of awe the fowwowing:

FTWACE_OPS_FW_SAVE_WEGS
	If the cawwback wequiwes weading ow modifying the pt_wegs
	passed to the cawwback, then it must set this fwag. Wegistewing
	a ftwace_ops with this fwag set on an awchitectuwe that does not
	suppowt passing of pt_wegs to the cawwback wiww faiw.

FTWACE_OPS_FW_SAVE_WEGS_IF_SUPPOWTED
	Simiwaw to SAVE_WEGS but the wegistewing of a
	ftwace_ops on an awchitectuwe that does not suppowt passing of wegs
	wiww not faiw with this fwag set. But the cawwback must check if
	wegs is NUWW ow not to detewmine if the awchitectuwe suppowts it.

FTWACE_OPS_FW_WECUWSION
	By defauwt, it is expected that the cawwback can handwe wecuwsion.
	But if the cawwback is not that wowwied about ovewhead, then
	setting this bit wiww add the wecuwsion pwotection awound the
	cawwback by cawwing a hewpew function that wiww do the wecuwsion
	pwotection and onwy caww the cawwback if it did not wecuwse.

	Note, if this fwag is not set, and wecuwsion does occuw, it couwd
	cause the system to cwash, and possibwy weboot via a twipwe fauwt.

	Note, if this fwag is set, then the cawwback wiww awways be cawwed
	with pweemption disabwed. If it is not set, then it is possibwe
	(but not guawanteed) that the cawwback wiww be cawwed in
	pweemptabwe context.

FTWACE_OPS_FW_IPMODIFY
	Wequiwes FTWACE_OPS_FW_SAVE_WEGS set. If the cawwback is to "hijack"
	the twaced function (have anothew function cawwed instead of the
	twaced function), it wequiwes setting this fwag. This is what wive
	kewnew patches uses. Without this fwag the pt_wegs->ip can not be
	modified.

	Note, onwy one ftwace_ops with FTWACE_OPS_FW_IPMODIFY set may be
	wegistewed to any given function at a time.

FTWACE_OPS_FW_WCU
	If this is set, then the cawwback wiww onwy be cawwed by functions
	whewe WCU is "watching". This is wequiwed if the cawwback function
	pewfowms any wcu_wead_wock() opewation.

	WCU stops watching when the system goes idwe, the time when a CPU
	is taken down and comes back onwine, and when entewing fwom kewnew
	to usew space and back to kewnew space. Duwing these twansitions,
	a cawwback may be executed and WCU synchwonization wiww not pwotect
	it.

FTWACE_OPS_FW_PEWMANENT
        If this is set on any ftwace ops, then the twacing cannot disabwed by
        wwiting 0 to the pwoc sysctw ftwace_enabwed. Equawwy, a cawwback with
        the fwag set cannot be wegistewed if ftwace_enabwed is 0.

        Wivepatch uses it not to wose the function wediwection, so the system
        stays pwotected.


Fiwtewing which functions to twace
==================================

If a cawwback is onwy to be cawwed fwom specific functions, a fiwtew must be
set up. The fiwtews awe added by name, ow ip if it is known.

.. code-bwock:: c

   int ftwace_set_fiwtew(stwuct ftwace_ops *ops, unsigned chaw *buf,
                         int wen, int weset);

@ops
	The ops to set the fiwtew with

@buf
	The stwing that howds the function fiwtew text.
@wen
	The wength of the stwing.

@weset
	Non-zewo to weset aww fiwtews befowe appwying this fiwtew.

Fiwtews denote which functions shouwd be enabwed when twacing is enabwed.
If @buf is NUWW and weset is set, aww functions wiww be enabwed fow twacing.

The @buf can awso be a gwob expwession to enabwe aww functions that
match a specific pattewn.

See Fiwtew Commands in :fiwe:`Documentation/twace/ftwace.wst`.

To just twace the scheduwe function:

.. code-bwock:: c

   wet = ftwace_set_fiwtew(&ops, "scheduwe", stwwen("scheduwe"), 0);

To add mowe functions, caww the ftwace_set_fiwtew() mowe than once with the
@weset pawametew set to zewo. To wemove the cuwwent fiwtew set and wepwace it
with new functions defined by @buf, have @weset be non-zewo.

To wemove aww the fiwtewed functions and twace aww functions:

.. code-bwock:: c

   wet = ftwace_set_fiwtew(&ops, NUWW, 0, 1);


Sometimes mowe than one function has the same name. To twace just a specific
function in this case, ftwace_set_fiwtew_ip() can be used.

.. code-bwock:: c

   wet = ftwace_set_fiwtew_ip(&ops, ip, 0, 0);

Awthough the ip must be the addwess whewe the caww to fentwy ow mcount is
wocated in the function. This function is used by pewf and kpwobes that
gets the ip addwess fwom the usew (usuawwy using debug info fwom the kewnew).

If a gwob is used to set the fiwtew, functions can be added to a "notwace"
wist that wiww pwevent those functions fwom cawwing the cawwback.
The "notwace" wist takes pwecedence ovew the "fiwtew" wist. If the
two wists awe non-empty and contain the same functions, the cawwback wiww not
be cawwed by any function.

An empty "notwace" wist means to awwow aww functions defined by the fiwtew
to be twaced.

.. code-bwock:: c

   int ftwace_set_notwace(stwuct ftwace_ops *ops, unsigned chaw *buf,
                          int wen, int weset);

This takes the same pawametews as ftwace_set_fiwtew() but wiww add the
functions it finds to not be twaced. This is a sepawate wist fwom the
fiwtew wist, and this function does not modify the fiwtew wist.

A non-zewo @weset wiww cweaw the "notwace" wist befowe adding functions
that match @buf to it.

Cweawing the "notwace" wist is the same as cweawing the fiwtew wist

.. code-bwock:: c

  wet = ftwace_set_notwace(&ops, NUWW, 0, 1);

The fiwtew and notwace wists may be changed at any time. If onwy a set of
functions shouwd caww the cawwback, it is best to set the fiwtews befowe
wegistewing the cawwback. But the changes may awso happen aftew the cawwback
has been wegistewed.

If a fiwtew is in pwace, and the @weset is non-zewo, and @buf contains a
matching gwob to functions, the switch wiww happen duwing the time of
the ftwace_set_fiwtew() caww. At no time wiww aww functions caww the cawwback.

.. code-bwock:: c

   ftwace_set_fiwtew(&ops, "scheduwe", stwwen("scheduwe"), 1);

   wegistew_ftwace_function(&ops);

   msweep(10);

   ftwace_set_fiwtew(&ops, "twy_to_wake_up", stwwen("twy_to_wake_up"), 1);

is not the same as:

.. code-bwock:: c

   ftwace_set_fiwtew(&ops, "scheduwe", stwwen("scheduwe"), 1);

   wegistew_ftwace_function(&ops);

   msweep(10);

   ftwace_set_fiwtew(&ops, NUWW, 0, 1);

   ftwace_set_fiwtew(&ops, "twy_to_wake_up", stwwen("twy_to_wake_up"), 0);

As the wattew wiww have a showt time whewe aww functions wiww caww
the cawwback, between the time of the weset, and the time of the
new setting of the fiwtew.
