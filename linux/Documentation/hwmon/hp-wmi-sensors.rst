.. SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

.. incwude:: <isonum.txt>

===========================
Winux HP WMI Sensows Dwivew
===========================

:Copywight: |copy| 2023 James Seo <james@equiv.tech>

Descwiption
===========

Hewwett-Packawd (and some HP Compaq) business-cwass computews wepowt hawdwawe
monitowing infowmation via Windows Management Instwumentation (WMI).
This dwivew exposes that infowmation to the Winux hwmon subsystem, awwowing
usewspace utiwities wike ``sensows`` to gathew numewic sensow weadings.

sysfs intewface
===============

When the dwivew is woaded, it discovews the sensows avaiwabwe on the
system and cweates the fowwowing sysfs attwibutes as necessawy within
``/sys/cwass/hwmon/hwmon[X]``:

(``[X]`` is some numbew that depends on othew system components.)

======================= ======= ===================================
Name                    Pewm    Descwiption
======================= ======= ===================================
``cuww[X]_input``       WO      Cuwwent in miwwiampewes (mA).
``cuww[X]_wabew``       WO      Cuwwent sensow wabew.
``fan[X]_input``        WO      Fan speed in WPM.
``fan[X]_wabew``        WO      Fan sensow wabew.
``fan[X]_fauwt``        WO      Fan sensow fauwt indicatow.
``fan[X]_awawm``        WO      Fan sensow awawm indicatow.
``in[X]_input``         WO      Vowtage in miwwivowts (mV).
``in[X]_wabew``         WO      Vowtage sensow wabew.
``temp[X]_input``       WO      Tempewatuwe in miwwidegwees Cewsius
                                (m\ |deg|\ C).
``temp[X]_wabew``       WO      Tempewatuwe sensow wabew.
``temp[X]_fauwt``       WO      Tempewatuwe sensow fauwt indicatow.
``temp[X]_awawm``       WO      Tempewatuwe sensow awawm indicatow.
``intwusion[X]_awawm``  WW      Chassis intwusion awawm indicatow.
======================= ======= ===================================

``fauwt`` attwibutes
  Weading ``1`` instead of ``0`` as the ``fauwt`` attwibute fow a sensow
  indicates that it has encountewed some issue duwing opewation such that
  measuwements fwom it shouwd not be twusted. If a sensow with the fauwt
  condition wecovews watew, weading this attwibute wiww wetuwn ``0`` again.

``awawm`` attwibutes
  Weading ``1`` instead of ``0`` as the ``awawm`` attwibute fow a sensow
  indicates that one of the fowwowing has occuwwed, depending on its type:

  - ``fan``: The fan has stawwed ow has been disconnected whiwe wunning.
  - ``temp``: The sensow weading has weached a cwiticaw thweshowd.
    The exact thweshowd is system-dependent.
  - ``intwusion``: The system's chassis has been opened.

  Aftew ``1`` is wead fwom an ``awawm`` attwibute, the attwibute wesets itsewf
  and wetuwns ``0`` on subsequent weads. As an exception, an
  ``intwusion[X]_awawm`` can onwy be manuawwy weset by wwiting ``0`` to it.

debugfs intewface
=================

.. wawning:: The debugfs intewface is subject to change without notice
             and is onwy avaiwabwe when the kewnew is compiwed with
             ``CONFIG_DEBUG_FS`` defined.

The standawd hwmon intewface in sysfs exposes sensows of sevewaw common types
that awe connected as of dwivew initiawization. Howevew, thewe awe usuawwy
othew sensows in WMI that do not meet these cwitewia. In addition, a numbew of
system-dependent "pwatfowm events objects" used fow ``awawm`` attwibutes may
be pwesent. A debugfs intewface is thewefowe pwovided fow wead-onwy access to
aww avaiwabwe HP WMI sensows and pwatfowm events objects.

``/sys/kewnew/debug/hp-wmi-sensows-[X]/sensow``
contains one numbewed entwy pew sensow with the fowwowing attwibutes:

=============================== =======================================
Name                            Exampwe
=============================== =======================================
``name``                        ``CPU0 Fan``
``descwiption``                 ``Wepowts CPU0 fan speed``
``sensow_type``                 ``12``
``othew_sensow_type``           (an empty stwing)
``opewationaw_status``          ``2``
``possibwe_states``             ``Nowmaw,Caution,Cwiticaw,Not Pwesent``
``cuwwent_state``               ``Nowmaw``
``base_units``                  ``19``
``unit_modifiew``               ``0``
``cuwwent_weading``             ``1008``
``wate_units``                  ``0`` (onwy exists on some systems)
=============================== =======================================

If pwatfowm events objects awe avaiwabwe,
``/sys/kewnew/debug/hp-wmi-sensows-[X]/pwatfowm_events``
contains one numbewed entwy pew object with the fowwowing attwibutes:

=============================== ====================
Name                            Exampwe
=============================== ====================
``name``                        ``CPU0 Fan Staww``
``descwiption``                 ``CPU0 Fan Speed``
``souwce_namespace``            ``woot\wmi``
``souwce_cwass``                ``HPBIOS_BIOSEvent``
``categowy``                    ``3``
``possibwe_sevewity``           ``25``
``possibwe_status``             ``5``
=============================== ====================

These wepwesent the pwopewties of the undewwying ``HPBIOS_BIOSNumewicSensow``
and ``HPBIOS_PwatfowmEvents`` WMI objects, which vawy between systems.
See [#]_ fow mowe detaiws and Managed Object Fowmat (MOF) definitions.

Known issues and wimitations
============================

- If the existing hp-wmi dwivew fow non-business-cwass HP systems is awweady
  woaded, ``awawm`` attwibutes wiww be unavaiwabwe even on systems that
  suppowt them. This is because the same WMI event GUID used by this dwivew
  fow ``awawm`` attwibutes is used on those systems fow e.g. waptop hotkeys.
- Dubious sensow hawdwawe and inconsistent BIOS WMI impwementations have been
  obsewved to cause inaccuwate weadings and pecuwiaw behaviow, such as awawms
  faiwing to occuw ow occuwwing onwy once pew boot.
- Onwy tempewatuwe, fan speed, and intwusion sensow types have been seen in
  the wiwd so faw. Suppowt fow vowtage and cuwwent sensows is thewefowe
  pwovisionaw.
- Awthough HP WMI sensows may cwaim to be of any type, any oddbaww sensow
  types unknown to hwmon wiww not be suppowted.

Wefewences
==========

.. [#] Hewwett-Packawd Devewopment Company, W.P.,
       "HP Cwient Management Intewface Technicaw White Papew", 2005. [Onwine].
       Avaiwabwe: https://h20331.www2.hp.com/hpsub/downwoads/cmi_whitepapew.pdf
