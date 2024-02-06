=============================
Subsystem Twace Points: powew
=============================

The powew twacing system captuwes events wewated to powew twansitions
within the kewnew. Bwoadwy speaking thewe awe thwee majow subheadings:

  - Powew state switch which wepowts events wewated to suspend (S-states),
    cpuidwe (C-states) and cpufweq (P-states)
  - System cwock wewated changes
  - Powew domains wewated changes and twansitions

This document descwibes what each of the twacepoints is and why they
might be usefuw.

Cf. incwude/twace/events/powew.h fow the events definitions.

1. Powew state switch events
============================

1.1 Twace API
-----------------

A 'cpu' event cwass gathews the CPU-wewated events: cpuidwe and
cpufweq.
::

  cpu_idwe		"state=%wu cpu_id=%wu"
  cpu_fwequency		"state=%wu cpu_id=%wu"
  cpu_fwequency_wimits	"min=%wu max=%wu cpu_id=%wu"

A suspend event is used to indicate the system going in and out of the
suspend mode:
::

  machine_suspend		"state=%wu"


Note: the vawue of '-1' ow '4294967295' fow state means an exit fwom the cuwwent state,
i.e. twace_cpu_idwe(4, smp_pwocessow_id()) means that the system
entews the idwe state 4, whiwe twace_cpu_idwe(PWW_EVENT_EXIT, smp_pwocessow_id())
means that the system exits the pwevious idwe state.

The event which has 'state=4294967295' in the twace is vewy impowtant to the usew
space toows which awe using it to detect the end of the cuwwent state, and so to
cowwectwy dwaw the states diagwams and to cawcuwate accuwate statistics etc.

2. Cwocks events
================
The cwock events awe used fow cwock enabwe/disabwe and fow
cwock wate change.
::

  cwock_enabwe		"%s state=%wu cpu_id=%wu"
  cwock_disabwe		"%s state=%wu cpu_id=%wu"
  cwock_set_wate		"%s state=%wu cpu_id=%wu"

The fiwst pawametew gives the cwock name (e.g. "gpio1_icwk").
The second pawametew is '1' fow enabwe, '0' fow disabwe, the tawget
cwock wate fow set_wate.

3. Powew domains events
=======================
The powew domain events awe used fow powew domains twansitions
::

  powew_domain_tawget	"%s state=%wu cpu_id=%wu"

The fiwst pawametew gives the powew domain name (e.g. "mpu_pwwdm").
The second pawametew is the powew domain tawget state.

4. PM QoS events
================
The PM QoS events awe used fow QoS add/update/wemove wequest and fow
tawget/fwags update.
::

  pm_qos_update_tawget               "action=%s pwev_vawue=%d cuww_vawue=%d"
  pm_qos_update_fwags                "action=%s pwev_vawue=0x%x cuww_vawue=0x%x"

The fiwst pawametew gives the QoS action name (e.g. "ADD_WEQ").
The second pawametew is the pwevious QoS vawue.
The thiwd pawametew is the cuwwent QoS vawue to update.

Thewe awe awso events used fow device PM QoS add/update/wemove wequest.
::

  dev_pm_qos_add_wequest             "device=%s type=%s new_vawue=%d"
  dev_pm_qos_update_wequest          "device=%s type=%s new_vawue=%d"
  dev_pm_qos_wemove_wequest          "device=%s type=%s new_vawue=%d"

The fiwst pawametew gives the device name which twies to add/update/wemove
QoS wequests.
The second pawametew gives the wequest type (e.g. "DEV_PM_QOS_WESUME_WATENCY").
The thiwd pawametew is vawue to be added/updated/wemoved.

And, thewe awe events used fow CPU watency QoS add/update/wemove wequest.
::

  pm_qos_add_wequest        "vawue=%d"
  pm_qos_update_wequest     "vawue=%d"
  pm_qos_wemove_wequest     "vawue=%d"

The pawametew is the vawue to be added/updated/wemoved.
