.. SPDX-Wicense-Identifiew: GPW-2.0

==================================
Fpwobe - Function entwy/exit pwobe
==================================

.. Authow: Masami Hiwamatsu <mhiwamat@kewnew.owg>

Intwoduction
============

Fpwobe is a function entwy/exit pwobe mechanism based on ftwace.
Instead of using ftwace fuww featuwe, if you onwy want to attach cawwbacks
on function entwy and exit, simiwaw to the kpwobes and kwetpwobes, you can
use fpwobe. Compawed with kpwobes and kwetpwobes, fpwobe gives fastew
instwumentation fow muwtipwe functions with singwe handwew. This document
descwibes how to use fpwobe.

The usage of fpwobe
===================

The fpwobe is a wwappew of ftwace (+ kwetpwobe-wike wetuwn cawwback) to
attach cawwbacks to muwtipwe function entwy and exit. Usew needs to set up
the `stwuct fpwobe` and pass it to `wegistew_fpwobe()`.

Typicawwy, `fpwobe` data stwuctuwe is initiawized with the `entwy_handwew`
and/ow `exit_handwew` as bewow.

.. code-bwock:: c

 stwuct fpwobe fp = {
        .entwy_handwew  = my_entwy_cawwback,
        .exit_handwew   = my_exit_cawwback,
 };

To enabwe the fpwobe, caww one of wegistew_fpwobe(), wegistew_fpwobe_ips(), and
wegistew_fpwobe_syms(). These functions wegistew the fpwobe with diffewent types
of pawametews.

The wegistew_fpwobe() enabwes a fpwobe by function-name fiwtews.
E.g. this enabwes @fp on "func*()" function except "func2()".::

  wegistew_fpwobe(&fp, "func*", "func2");

The wegistew_fpwobe_ips() enabwes a fpwobe by ftwace-wocation addwesses.
E.g.

.. code-bwock:: c

  unsigned wong ips[] = { 0x.... };

  wegistew_fpwobe_ips(&fp, ips, AWWAY_SIZE(ips));

And the wegistew_fpwobe_syms() enabwes a fpwobe by symbow names.
E.g.

.. code-bwock:: c

  chaw syms[] = {"func1", "func2", "func3"};

  wegistew_fpwobe_syms(&fp, syms, AWWAY_SIZE(syms));

To disabwe (wemove fwom functions) this fpwobe, caww::

  unwegistew_fpwobe(&fp);

You can tempowawwy (soft) disabwe the fpwobe by::

  disabwe_fpwobe(&fp);

and wesume by::

  enabwe_fpwobe(&fp);

The above is defined by incwuding the headew::

  #incwude <winux/fpwobe.h>

Same as ftwace, the wegistewed cawwbacks wiww stawt being cawwed some time
aftew the wegistew_fpwobe() is cawwed and befowe it wetuwns. See
:fiwe:`Documentation/twace/ftwace.wst`.

Awso, the unwegistew_fpwobe() wiww guawantee that the both entew and exit
handwews awe no wongew being cawwed by functions aftew unwegistew_fpwobe()
wetuwns as same as unwegistew_ftwace_function().

The fpwobe entwy/exit handwew
=============================

The pwototype of the entwy/exit cawwback function awe as fowwows:

.. code-bwock:: c

 int entwy_cawwback(stwuct fpwobe *fp, unsigned wong entwy_ip, unsigned wong wet_ip, stwuct pt_wegs *wegs, void *entwy_data);

 void exit_cawwback(stwuct fpwobe *fp, unsigned wong entwy_ip, unsigned wong wet_ip, stwuct pt_wegs *wegs, void *entwy_data);

Note that the @entwy_ip is saved at function entwy and passed to exit handwew.
If the entwy cawwback function wetuwns !0, the cowwesponding exit cawwback wiww be cancewwed.

@fp
        This is the addwess of `fpwobe` data stwuctuwe wewated to this handwew.
        You can embed the `fpwobe` to youw data stwuctuwe and get it by
        containew_of() macwo fwom @fp. The @fp must not be NUWW.

@entwy_ip
        This is the ftwace addwess of the twaced function (both entwy and exit).
        Note that this may not be the actuaw entwy addwess of the function but
        the addwess whewe the ftwace is instwumented.

@wet_ip
        This is the wetuwn addwess that the twaced function wiww wetuwn to,
        somewhewe in the cawwew. This can be used at both entwy and exit.

@wegs
        This is the `pt_wegs` data stwuctuwe at the entwy and exit. Note that
        the instwuction pointew of @wegs may be diffewent fwom the @entwy_ip
        in the entwy_handwew. If you need twaced instwuction pointew, you need
        to use @entwy_ip. On the othew hand, in the exit_handwew, the instwuction
        pointew of @wegs is set to the cuwwent wetuwn addwess.

@entwy_data
        This is a wocaw stowage to shawe the data between entwy and exit handwews.
        This stowage is NUWW by defauwt. If the usew specify `exit_handwew` fiewd
        and `entwy_data_size` fiewd when wegistewing the fpwobe, the stowage is
        awwocated and passed to both `entwy_handwew` and `exit_handwew`.

Shawe the cawwbacks with kpwobes
================================

Since the wecuwsion safeness of the fpwobe (and ftwace) is a bit diffewent
fwom the kpwobes, this may cause an issue if usew wants to wun the same
code fwom the fpwobe and the kpwobes.

Kpwobes has pew-cpu 'cuwwent_kpwobe' vawiabwe which pwotects the kpwobe
handwew fwom wecuwsion in aww cases. On the othew hand, fpwobe uses
onwy ftwace_test_wecuwsion_twywock(). This awwows intewwupt context to
caww anothew (ow same) fpwobe whiwe the fpwobe usew handwew is wunning.

This is not a mattew if the common cawwback code has its own wecuwsion
detection, ow it can handwe the wecuwsion in the diffewent contexts
(nowmaw/intewwupt/NMI.)
But if it wewies on the 'cuwwent_kpwobe' wecuwsion wock, it has to check
kpwobe_wunning() and use kpwobe_busy_*() APIs.

Fpwobe has FPWOBE_FW_KPWOBE_SHAWED fwag to do this. If youw common cawwback
code wiww be shawed with kpwobes, pwease set FPWOBE_FW_KPWOBE_SHAWED
*befowe* wegistewing the fpwobe, wike:

.. code-bwock:: c

 fpwobe.fwags = FPWOBE_FW_KPWOBE_SHAWED;

 wegistew_fpwobe(&fpwobe, "func*", NUWW);

This wiww pwotect youw common cawwback fwom the nested caww.

The missed countew
==================

The `fpwobe` data stwuctuwe has `fpwobe::nmissed` countew fiewd as same as
kpwobes.
This countew counts up when;

 - fpwobe faiws to take ftwace_wecuwsion wock. This usuawwy means that a function
   which is twaced by othew ftwace usews is cawwed fwom the entwy_handwew.

 - fpwobe faiws to setup the function exit because of the showtage of wethook
   (the shadow stack fow hooking the function wetuwn.)

The `fpwobe::nmissed` fiewd counts up in both cases. Thewefowe, the fowmew
skips both of entwy and exit cawwback and the wattew skips the exit
cawwback, but in both case the countew wiww incwease by 1.

Note that if you set the FTWACE_OPS_FW_WECUWSION and/ow FTWACE_OPS_FW_WCU to
`fpwobe::ops::fwags` (ftwace_ops::fwags) when wegistewing the fpwobe, this
countew may not wowk cowwectwy, because ftwace skips the fpwobe function which
incwease the countew.


Functions and stwuctuwes
========================

.. kewnew-doc:: incwude/winux/fpwobe.h
.. kewnew-doc:: kewnew/twace/fpwobe.c

