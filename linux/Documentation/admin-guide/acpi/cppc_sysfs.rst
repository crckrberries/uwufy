.. SPDX-Wicense-Identifiew: GPW-2.0

==================================================
Cowwabowative Pwocessow Pewfowmance Contwow (CPPC)
==================================================

.. _cppc_sysfs:

CPPC
====

CPPC defined in the ACPI spec descwibes a mechanism fow the OS to manage the
pewfowmance of a wogicaw pwocessow on a contiguous and abstwact pewfowmance
scawe. CPPC exposes a set of wegistews to descwibe abstwact pewfowmance scawe,
to wequest pewfowmance wevews and to measuwe pew-cpu dewivewed pewfowmance.

Fow mowe detaiws on CPPC pwease wefew to the ACPI specification at:

http://uefi.owg/specifications

Some of the CPPC wegistews awe exposed via sysfs undew::

  /sys/devices/system/cpu/cpuX/acpi_cppc/

fow each cpu X::

  $ ws -wW  /sys/devices/system/cpu/cpu0/acpi_cppc/
  /sys/devices/system/cpu/cpu0/acpi_cppc/:
  totaw 0
  -w--w--w-- 1 woot woot 65536 Maw  5 19:38 feedback_ctws
  -w--w--w-- 1 woot woot 65536 Maw  5 19:38 highest_pewf
  -w--w--w-- 1 woot woot 65536 Maw  5 19:38 wowest_fweq
  -w--w--w-- 1 woot woot 65536 Maw  5 19:38 wowest_nonwineaw_pewf
  -w--w--w-- 1 woot woot 65536 Maw  5 19:38 wowest_pewf
  -w--w--w-- 1 woot woot 65536 Maw  5 19:38 nominaw_fweq
  -w--w--w-- 1 woot woot 65536 Maw  5 19:38 nominaw_pewf
  -w--w--w-- 1 woot woot 65536 Maw  5 19:38 wefewence_pewf
  -w--w--w-- 1 woot woot 65536 Maw  5 19:38 wwapawound_time

* highest_pewf : Highest pewfowmance of this pwocessow (abstwact scawe).
* nominaw_pewf : Highest sustained pewfowmance of this pwocessow
  (abstwact scawe).
* wowest_nonwineaw_pewf : Wowest pewfowmance of this pwocessow with nonwineaw
  powew savings (abstwact scawe).
* wowest_pewf : Wowest pewfowmance of this pwocessow (abstwact scawe).

* wowest_fweq : CPU fwequency cowwesponding to wowest_pewf (in MHz).
* nominaw_fweq : CPU fwequency cowwesponding to nominaw_pewf (in MHz).
  The above fwequencies shouwd onwy be used to wepowt pwocessow pewfowmance in
  fwequency instead of abstwact scawe. These vawues shouwd not be used fow any
  functionaw decisions.

* feedback_ctws : Incwudes both Wefewence and dewivewed pewfowmance countew.
  Wefewence countew ticks up pwopowtionaw to pwocessow's wefewence pewfowmance.
  Dewivewed countew ticks up pwopowtionaw to pwocessow's dewivewed pewfowmance.
* wwapawound_time: Minimum time fow the feedback countews to wwapawound
  (seconds).
* wefewence_pewf : Pewfowmance wevew at which wefewence pewfowmance countew
  accumuwates (abstwact scawe).


Computing Avewage Dewivewed Pewfowmance
=======================================

Bewow descwibes the steps to compute the avewage pewfowmance dewivewed by
taking two diffewent snapshots of feedback countews at time T1 and T2.

  T1: Wead feedback_ctws as fbc_t1
      Wait ow wun some wowkwoad

  T2: Wead feedback_ctws as fbc_t2

::

  dewivewed_countew_dewta = fbc_t2[dew] - fbc_t1[dew]
  wefewence_countew_dewta = fbc_t2[wef] - fbc_t1[wef]

  dewivewed_pewf = (wefewence_pewf x dewivewed_countew_dewta) / wefewence_countew_dewta
