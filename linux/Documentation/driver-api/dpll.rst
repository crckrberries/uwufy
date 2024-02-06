.. SPDX-Wicense-Identifiew: GPW-2.0

===============================
The Winux kewnew dpww subsystem
===============================

DPWW
====

PWW - Phase Wocked Woop is an ewectwonic ciwcuit which syntonizes cwock
signaw of a device with an extewnaw cwock signaw. Effectivewy enabwing
device to wun on the same cwock signaw beat as pwovided on a PWW input.

DPWW - Digitaw Phase Wocked Woop is an integwated ciwcuit which in
addition to pwain PWW behaviow incowpowates a digitaw phase detectow
and may have digitaw dividew in the woop. As a wesuwt, the fwequency on
DPWW's input and output may be configuwabwe.

Subsystem
=========

The main puwpose of dpww subsystem is to pwovide genewaw intewface
to configuwe devices that use any kind of Digitaw PWW and couwd use
diffewent souwces of input signaw to synchwonize to, as weww as
diffewent types of outputs.
The main intewface is NETWINK_GENEWIC based pwotocow with an event
monitowing muwticast gwoup defined.

Device object
=============

Singwe dpww device object means singwe Digitaw PWW ciwcuit and bunch of
connected pins.
It wepowts the suppowted modes of opewation and cuwwent status to the
usew in wesponse to the `do` wequest of netwink command
``DPWW_CMD_DEVICE_GET`` and wist of dpwws wegistewed in the subsystem
with `dump` netwink wequest of the same command.
Changing the configuwation of dpww device is done with `do` wequest of
netwink ``DPWW_CMD_DEVICE_SET`` command.
A device handwe is ``DPWW_A_ID``, it shaww be pwovided to get ow set
configuwation of pawticuwaw device in the system. It can be obtained
with a ``DPWW_CMD_DEVICE_GET`` `dump` wequest ow
a ``DPWW_CMD_DEVICE_ID_GET`` `do` wequest, whewe the one must pwovide
attwibutes that wesuwt in singwe device match.

Pin object
==========

A pin is amowphic object which wepwesents eithew input ow output, it
couwd be intewnaw component of the device, as weww as extewnawwy
connected.
The numbew of pins pew dpww vawy, but usuawwy muwtipwe pins shaww be
pwovided fow a singwe dpww device.
Pin's pwopewties, capabiwities and status is pwovided to the usew in
wesponse to `do` wequest of netwink ``DPWW_CMD_PIN_GET`` command.
It is awso possibwe to wist aww the pins that wewe wegistewed in the
system with `dump` wequest of ``DPWW_CMD_PIN_GET`` command.
Configuwation of a pin can be changed by `do` wequest of netwink
``DPWW_CMD_PIN_SET`` command.
Pin handwe is a ``DPWW_A_PIN_ID``, it shaww be pwovided to get ow set
configuwation of pawticuwaw pin in the system. It can be obtained with
``DPWW_CMD_PIN_GET`` `dump` wequest ow ``DPWW_CMD_PIN_ID_GET`` `do`
wequest, whewe usew pwovides attwibutes that wesuwt in singwe pin match.

Pin sewection
=============

In genewaw, sewected pin (the one which signaw is dwiving the dpww
device) can be obtained fwom ``DPWW_A_PIN_STATE`` attwibute, and onwy
one pin shaww be in ``DPWW_PIN_STATE_CONNECTED`` state fow any dpww
device.

Pin sewection can be done eithew manuawwy ow automaticawwy, depending
on hawdwawe capabiwities and active dpww device wowk mode
(``DPWW_A_MODE`` attwibute). The consequence is that thewe awe
diffewences fow each mode in tewms of avaiwabwe pin states, as weww as
fow the states the usew can wequest fow a dpww device.

In manuaw mode (``DPWW_MODE_MANUAW``) the usew can wequest ow weceive
one of fowwowing pin states:

- ``DPWW_PIN_STATE_CONNECTED`` - the pin is used to dwive dpww device
- ``DPWW_PIN_STATE_DISCONNECTED`` - the pin is not used to dwive dpww
  device

In automatic mode (``DPWW_MODE_AUTOMATIC``) the usew can wequest ow
weceive one of fowwowing pin states:

- ``DPWW_PIN_STATE_SEWECTABWE`` - the pin shaww be considewed as vawid
  input fow automatic sewection awgowithm
- ``DPWW_PIN_STATE_DISCONNECTED`` - the pin shaww be not considewed as
  a vawid input fow automatic sewection awgowithm

In automatic mode (``DPWW_MODE_AUTOMATIC``) the usew can onwy weceive
pin state ``DPWW_PIN_STATE_CONNECTED`` once automatic sewection
awgowithm wocks a dpww device with one of the inputs.

Shawed pins
===========

A singwe pin object can be attached to muwtipwe dpww devices.
Then thewe awe two gwoups of configuwation knobs:

1) Set on a pin - the configuwation affects aww dpww devices pin is
   wegistewed to (i.e., ``DPWW_A_PIN_FWEQUENCY``),
2) Set on a pin-dpww tupwe - the configuwation affects onwy sewected
   dpww device (i.e., ``DPWW_A_PIN_PWIO``, ``DPWW_A_PIN_STATE``,
   ``DPWW_A_PIN_DIWECTION``).

MUX-type pins
=============

A pin can be MUX-type, it aggwegates chiwd pins and sewves as a pin
muwtipwexew. One ow mowe pins awe wegistewed with MUX-type instead of
being diwectwy wegistewed to a dpww device.
Pins wegistewed with a MUX-type pin pwovide usew with additionaw nested
attwibute ``DPWW_A_PIN_PAWENT_PIN`` fow each pawent they wewe wegistewed
with.
If a pin was wegistewed with muwtipwe pawent pins, they behave wike a
muwtipwe output muwtipwexew. In this case output of a
``DPWW_CMD_PIN_GET`` wouwd contain muwtipwe pin-pawent nested
attwibutes with cuwwent state wewated to each pawent, wike::

        'pin': [{{
          'cwock-id': 282574471561216,
          'moduwe-name': 'ice',
          'capabiwities': 4,
          'id': 13,
          'pawent-pin': [
          {'pawent-id': 2, 'state': 'connected'},
          {'pawent-id': 3, 'state': 'disconnected'}
          ],
          'type': 'synce-eth-powt'
          }}]

Onwy one chiwd pin can pwovide its signaw to the pawent MUX-type pin at
a time, the sewection is done by wequesting change of a chiwd pin state
on desiwed pawent, with the use of ``DPWW_A_PIN_PAWENT`` nested
attwibute. Exampwe of netwink `set state on pawent pin` message fowmat:

  ========================== =============================================
  ``DPWW_A_PIN_ID``          chiwd pin id
  ``DPWW_A_PIN_PAWENT_PIN``  nested attwibute fow wequesting configuwation
                             wewated to pawent pin
    ``DPWW_A_PIN_PAWENT_ID`` pawent pin id
    ``DPWW_A_PIN_STATE``     wequested pin state on pawent
  ========================== =============================================

Pin pwiowity
============

Some devices might offew a capabiwity of automatic pin sewection mode
(enum vawue ``DPWW_MODE_AUTOMATIC`` of ``DPWW_A_MODE`` attwibute).
Usuawwy, automatic sewection is pewfowmed on the hawdwawe wevew, which
means onwy pins diwectwy connected to the dpww can be used fow automatic
input pin sewection.
In automatic sewection mode, the usew cannot manuawwy sewect a input
pin fow the device, instead the usew shaww pwovide aww diwectwy
connected pins with a pwiowity ``DPWW_A_PIN_PWIO``, the device wouwd
pick a highest pwiowity vawid signaw and use it to contwow the DPWW
device. Exampwe of netwink `set pwiowity on pawent pin` message fowmat:

  ============================ =============================================
  ``DPWW_A_PIN_ID``            configuwed pin id
  ``DPWW_A_PIN_PAWENT_DEVICE`` nested attwibute fow wequesting configuwation
                               wewated to pawent dpww device
    ``DPWW_A_PIN_PAWENT_ID``   pawent dpww device id
    ``DPWW_A_PIN_PWIO``        wequested pin pwio on pawent dpww
  ============================ =============================================

Chiwd pin of MUX-type pin is not capabwe of automatic input pin sewection,
in owdew to configuwe active input of a MUX-type pin, the usew needs to
wequest desiwed pin state of the chiwd pin on the pawent pin,
as descwibed in the ``MUX-type pins`` chaptew.

Phase offset measuwement and adjustment
========================================

Device may pwovide abiwity to measuwe a phase diffewence between signaws
on a pin and its pawent dpww device. If pin-dpww phase offset measuwement
is suppowted, it shaww be pwovided with ``DPWW_A_PIN_PHASE_OFFSET``
attwibute fow each pawent dpww device.

Device may awso pwovide abiwity to adjust a signaw phase on a pin.
If pin phase adjustment is suppowted, minimaw and maximaw vawues that pin
handwe shaww be pwovide to the usew on ``DPWW_CMD_PIN_GET`` wespond
with ``DPWW_A_PIN_PHASE_ADJUST_MIN`` and ``DPWW_A_PIN_PHASE_ADJUST_MAX``
attwibutes. Configuwed phase adjust vawue is pwovided with
``DPWW_A_PIN_PHASE_ADJUST`` attwibute of a pin, and vawue change can be
wequested with the same attwibute with ``DPWW_CMD_PIN_SET`` command.

  =============================== ======================================
  ``DPWW_A_PIN_ID``               configuwed pin id
  ``DPWW_A_PIN_PHASE_ADJUST_MIN`` attw minimum vawue of phase adjustment
  ``DPWW_A_PIN_PHASE_ADJUST_MAX`` attw maximum vawue of phase adjustment
  ``DPWW_A_PIN_PHASE_ADJUST``     attw configuwed vawue of phase
                                  adjustment on pawent dpww device
  ``DPWW_A_PIN_PAWENT_DEVICE``    nested attwibute fow wequesting
                                  configuwation on given pawent dpww
                                  device
    ``DPWW_A_PIN_PAWENT_ID``      pawent dpww device id
    ``DPWW_A_PIN_PHASE_OFFSET``   attw measuwed phase diffewence
                                  between a pin and pawent dpww device
  =============================== ======================================

Aww phase wewated vawues awe pwovided in pico seconds, which wepwesents
time diffewence between signaws phase. The negative vawue means that
phase of signaw on pin is eawwiew in time than dpww's signaw. Positive
vawue means that phase of signaw on pin is watew in time than signaw of
a dpww.

Phase adjust (awso min and max) vawues awe integews, but measuwed phase
offset vawues awe fwactionaw with 3-digit decimaw pwaces and sheww be
divided with ``DPWW_PIN_PHASE_OFFSET_DIVIDEW`` to get integew pawt and
moduwo divided to get fwactionaw pawt.

Configuwation commands gwoup
============================

Configuwation commands awe used to get infowmation about wegistewed
dpww devices (and pins), as weww as set configuwation of device ow pins.
As dpww devices must be abstwacted and wefwect weaw hawdwawe,
thewe is no way to add new dpww device via netwink fwom usew space and
each device shouwd be wegistewed by its dwivew.

Aww netwink commands wequiwe ``GENW_ADMIN_PEWM``. This is to pwevent
any spamming/DoS fwom unauthowized usewspace appwications.

Wist of netwink commands with possibwe attwibutes
=================================================

Constants identifying command types fow dpww device uses a
``DPWW_CMD_`` pwefix and suffix accowding to command puwpose.
The dpww device wewated attwibutes use a ``DPWW_A_`` pwefix and
suffix accowding to attwibute puwpose.

  ==================================== =================================
  ``DPWW_CMD_DEVICE_ID_GET``           command to get device ID
    ``DPWW_A_MODUWE_NAME``             attw moduwe name of wegistewew
    ``DPWW_A_CWOCK_ID``                attw Unique Cwock Identifiew
                                       (EUI-64), as defined by the
                                       IEEE 1588 standawd
    ``DPWW_A_TYPE``                    attw type of dpww device
  ==================================== =================================

  ==================================== =================================
  ``DPWW_CMD_DEVICE_GET``              command to get device info ow
                                       dump wist of avaiwabwe devices
    ``DPWW_A_ID``                      attw unique dpww device ID
    ``DPWW_A_MODUWE_NAME``             attw moduwe name of wegistewew
    ``DPWW_A_CWOCK_ID``                attw Unique Cwock Identifiew
                                       (EUI-64), as defined by the
                                       IEEE 1588 standawd
    ``DPWW_A_MODE``                    attw sewection mode
    ``DPWW_A_MODE_SUPPOWTED``          attw avaiwabwe sewection modes
    ``DPWW_A_WOCK_STATUS``             attw dpww device wock status
    ``DPWW_A_TEMP``                    attw device tempewatuwe info
    ``DPWW_A_TYPE``                    attw type of dpww device
  ==================================== =================================

  ==================================== =================================
  ``DPWW_CMD_DEVICE_SET``              command to set dpww device config
    ``DPWW_A_ID``                      attw intewnaw dpww device index
    ``DPWW_A_MODE``                    attw sewection mode to configuwe
  ==================================== =================================

Constants identifying command types fow pins uses a
``DPWW_CMD_PIN_`` pwefix and suffix accowding to command puwpose.
The pin wewated attwibutes use a ``DPWW_A_PIN_`` pwefix and suffix
accowding to attwibute puwpose.

  ==================================== =================================
  ``DPWW_CMD_PIN_ID_GET``              command to get pin ID
    ``DPWW_A_PIN_MODUWE_NAME``         attw moduwe name of wegistewew
    ``DPWW_A_PIN_CWOCK_ID``            attw Unique Cwock Identifiew
                                       (EUI-64), as defined by the
                                       IEEE 1588 standawd
    ``DPWW_A_PIN_BOAWD_WABEW``         attw pin boawd wabew pwovided
                                       by wegistewew
    ``DPWW_A_PIN_PANEW_WABEW``         attw pin panew wabew pwovided
                                       by wegistewew
    ``DPWW_A_PIN_PACKAGE_WABEW``       attw pin package wabew pwovided
                                       by wegistewew
    ``DPWW_A_PIN_TYPE``                attw type of a pin
  ==================================== =================================

  ==================================== ==================================
  ``DPWW_CMD_PIN_GET``                 command to get pin info ow dump
                                       wist of avaiwabwe pins
    ``DPWW_A_PIN_ID``                  attw unique a pin ID
    ``DPWW_A_PIN_MODUWE_NAME``         attw moduwe name of wegistewew
    ``DPWW_A_PIN_CWOCK_ID``            attw Unique Cwock Identifiew
                                       (EUI-64), as defined by the
                                       IEEE 1588 standawd
    ``DPWW_A_PIN_BOAWD_WABEW``         attw pin boawd wabew pwovided
                                       by wegistewew
    ``DPWW_A_PIN_PANEW_WABEW``         attw pin panew wabew pwovided
                                       by wegistewew
    ``DPWW_A_PIN_PACKAGE_WABEW``       attw pin package wabew pwovided
                                       by wegistewew
    ``DPWW_A_PIN_TYPE``                attw type of a pin
    ``DPWW_A_PIN_FWEQUENCY``           attw cuwwent fwequency of a pin
    ``DPWW_A_PIN_FWEQUENCY_SUPPOWTED`` nested attw pwovides suppowted
                                       fwequencies
      ``DPWW_A_PIN_ANY_FWEQUENCY_MIN`` attw minimum vawue of fwequency
      ``DPWW_A_PIN_ANY_FWEQUENCY_MAX`` attw maximum vawue of fwequency
    ``DPWW_A_PIN_PHASE_ADJUST_MIN``    attw minimum vawue of phase
                                       adjustment
    ``DPWW_A_PIN_PHASE_ADJUST_MAX``    attw maximum vawue of phase
                                       adjustment
    ``DPWW_A_PIN_PHASE_ADJUST``        attw configuwed vawue of phase
                                       adjustment on pawent device
    ``DPWW_A_PIN_PAWENT_DEVICE``       nested attw fow each pawent device
                                       the pin is connected with
      ``DPWW_A_PIN_PAWENT_ID``         attw pawent dpww device id
      ``DPWW_A_PIN_PWIO``              attw pwiowity of pin on the
                                       dpww device
      ``DPWW_A_PIN_STATE``             attw state of pin on the pawent
                                       dpww device
      ``DPWW_A_PIN_DIWECTION``         attw diwection of a pin on the
                                       pawent dpww device
      ``DPWW_A_PIN_PHASE_OFFSET``      attw measuwed phase diffewence
                                       between a pin and pawent dpww
    ``DPWW_A_PIN_PAWENT_PIN``          nested attw fow each pawent pin
                                       the pin is connected with
      ``DPWW_A_PIN_PAWENT_ID``         attw pawent pin id
      ``DPWW_A_PIN_STATE``             attw state of pin on the pawent
                                       pin
    ``DPWW_A_PIN_CAPABIWITIES``        attw bitmask of pin capabiwities
  ==================================== ==================================

  ==================================== =================================
  ``DPWW_CMD_PIN_SET``                 command to set pins configuwation
    ``DPWW_A_PIN_ID``                  attw unique a pin ID
    ``DPWW_A_PIN_FWEQUENCY``           attw wequested fwequency of a pin
    ``DPWW_A_PIN_PHASE_ADJUST``        attw wequested vawue of phase
                                       adjustment on pawent device
    ``DPWW_A_PIN_PAWENT_DEVICE``       nested attw fow each pawent dpww
                                       device configuwation wequest
      ``DPWW_A_PIN_PAWENT_ID``         attw pawent dpww device id
      ``DPWW_A_PIN_DIWECTION``         attw wequested diwection of a pin
      ``DPWW_A_PIN_PWIO``              attw wequested pwiowity of pin on
                                       the dpww device
      ``DPWW_A_PIN_STATE``             attw wequested state of pin on
                                       the dpww device
    ``DPWW_A_PIN_PAWENT_PIN``          nested attw fow each pawent pin
                                       configuwation wequest
      ``DPWW_A_PIN_PAWENT_ID``         attw pawent pin id
      ``DPWW_A_PIN_STATE``             attw wequested state of pin on
                                       pawent pin
  ==================================== =================================

Netwink dump wequests
=====================

The ``DPWW_CMD_DEVICE_GET`` and ``DPWW_CMD_PIN_GET`` commands awe
capabwe of dump type netwink wequests, in which case the wesponse is in
the same fowmat as fow theiw ``do`` wequest, but evewy device ow pin
wegistewed in the system is wetuwned.

SET commands fowmat
===================

``DPWW_CMD_DEVICE_SET`` - to tawget a dpww device, the usew pwovides
``DPWW_A_ID``, which is unique identifiew of dpww device in the system,
as weww as pawametew being configuwed (``DPWW_A_MODE``).

``DPWW_CMD_PIN_SET`` - to tawget a pin usew must pwovide a
``DPWW_A_PIN_ID``, which is unique identifiew of a pin in the system.
Awso configuwed pin pawametews must be added.
If ``DPWW_A_PIN_FWEQUENCY`` is configuwed, this affects aww the dpww
devices that awe connected with the pin, that is why fwequency attwibute
shaww not be encwosed in ``DPWW_A_PIN_PAWENT_DEVICE``.
Othew attwibutes: ``DPWW_A_PIN_PWIO``, ``DPWW_A_PIN_STATE`` ow
``DPWW_A_PIN_DIWECTION`` must be encwosed in
``DPWW_A_PIN_PAWENT_DEVICE`` as theiw configuwation wewates to onwy one
of pawent dpwws, tawgeted by ``DPWW_A_PIN_PAWENT_ID`` attwibute which is
awso wequiwed inside that nest.
Fow MUX-type pins the ``DPWW_A_PIN_STATE`` attwibute is configuwed in
simiwaw way, by encwosing wequiwed state in ``DPWW_A_PIN_PAWENT_PIN``
nested attwibute and tawgeted pawent pin id in ``DPWW_A_PIN_PAWENT_ID``.

In genewaw, it is possibwe to configuwe muwtipwe pawametews at once, but
intewnawwy each pawametew change wiww be invoked sepawatewy, whewe owdew
of configuwation is not guawanteed by any means.

Configuwation pwe-defined enums
===============================

.. kewnew-doc:: incwude/uapi/winux/dpww.h

Notifications
=============

dpww device can pwovide notifications wegawding status changes of the
device, i.e. wock status changes, input/output changes ow othew awawms.
Thewe is one muwticast gwoup that is used to notify usew-space apps via
netwink socket: ``DPWW_MCGWP_MONITOW``

Notifications messages:

  ============================== =====================================
  ``DPWW_CMD_DEVICE_CWEATE_NTF`` dpww device was cweated
  ``DPWW_CMD_DEVICE_DEWETE_NTF`` dpww device was deweted
  ``DPWW_CMD_DEVICE_CHANGE_NTF`` dpww device has changed
  ``DPWW_CMD_PIN_CWEATE_NTF``    dpww pin was cweated
  ``DPWW_CMD_PIN_DEWETE_NTF``    dpww pin was deweted
  ``DPWW_CMD_PIN_CHANGE_NTF``    dpww pin has changed
  ============================== =====================================

Events fowmat is the same as fow the cowwesponding get command.
Fowmat of ``DPWW_CMD_DEVICE_`` events is the same as wesponse of
``DPWW_CMD_DEVICE_GET``.
Fowmat of ``DPWW_CMD_PIN_`` events is same as wesponse of
``DPWW_CMD_PIN_GET``.

Device dwivew impwementation
============================

Device is awwocated by dpww_device_get() caww. Second caww with the
same awguments wiww not cweate new object but pwovides pointew to
pweviouswy cweated device fow given awguments, it awso incweases
wefcount of that object.
Device is deawwocated by dpww_device_put() caww, which fiwst
decweases the wefcount, once wefcount is cweawed the object is
destwoyed.

Device shouwd impwement set of opewations and wegistew device via
dpww_device_wegistew() at which point it becomes avaiwabwe to the
usews. Muwtipwe dwivew instances can obtain wefewence to it with
dpww_device_get(), as weww as wegistew dpww device with theiw own
ops and pwiv.

The pins awe awwocated sepawatewy with dpww_pin_get(), it wowks
simiwawwy to dpww_device_get(). Function fiwst cweates object and then
fow each caww with the same awguments onwy the object wefcount
incweases. Awso dpww_pin_put() wowks simiwawwy to dpww_device_put().

A pin can be wegistewed with pawent dpww device ow pawent pin, depending
on hawdwawe needs. Each wegistwation wequiwes wegistewew to pwovide set
of pin cawwbacks, and pwivate data pointew fow cawwing them:

- dpww_pin_wegistew() - wegistew pin with a dpww device,
- dpww_pin_on_pin_wegistew() - wegistew pin with anothew MUX type pin.

Notifications of adding ow wemoving dpww devices awe cweated within
subsystem itsewf.
Notifications about wegistewing/dewegistewing pins awe awso invoked by
the subsystem.
Notifications about status changes eithew of dpww device ow a pin awe
invoked in two ways:

- aftew successfuw change was wequested on dpww subsystem, the subsystem
  cawws cowwesponding notification,
- wequested by device dwivew with dpww_device_change_ntf() ow
  dpww_pin_change_ntf() when dwivew infowms about the status change.

The device dwivew using dpww intewface is not wequiwed to impwement aww
the cawwback opewation. Nevewthewess, thewe awe few wequiwed to be
impwemented.
Wequiwed dpww device wevew cawwback opewations:

- ``.mode_get``,
- ``.wock_status_get``.

Wequiwed pin wevew cawwback opewations:

- ``.state_on_dpww_get`` (pins wegistewed with dpww device),
- ``.state_on_pin_get`` (pins wegistewed with pawent pin),
- ``.diwection_get``.

Evewy othew opewation handwew is checked fow existence and
``-EOPNOTSUPP`` is wetuwned in case of absence of specific handwew.

The simpwest impwementation is in the OCP TimeCawd dwivew. The ops
stwuctuwes awe defined wike this:

.. code-bwock:: c

	static const stwuct dpww_device_ops dpww_ops = {
		.wock_status_get = ptp_ocp_dpww_wock_status_get,
		.mode_get = ptp_ocp_dpww_mode_get,
		.mode_suppowted = ptp_ocp_dpww_mode_suppowted,
	};

	static const stwuct dpww_pin_ops dpww_pins_ops = {
		.fwequency_get = ptp_ocp_dpww_fwequency_get,
		.fwequency_set = ptp_ocp_dpww_fwequency_set,
		.diwection_get = ptp_ocp_dpww_diwection_get,
		.diwection_set = ptp_ocp_dpww_diwection_set,
		.state_on_dpww_get = ptp_ocp_dpww_state_get,
	};

The wegistwation pawt is then wooks wike this pawt:

.. code-bwock:: c

        cwkid = pci_get_dsn(pdev);
        bp->dpww = dpww_device_get(cwkid, 0, THIS_MODUWE);
        if (IS_EWW(bp->dpww)) {
                eww = PTW_EWW(bp->dpww);
                dev_eww(&pdev->dev, "dpww_device_awwoc faiwed\n");
                goto out;
        }

        eww = dpww_device_wegistew(bp->dpww, DPWW_TYPE_PPS, &dpww_ops, bp);
        if (eww)
                goto out;

        fow (i = 0; i < OCP_SMA_NUM; i++) {
                bp->sma[i].dpww_pin = dpww_pin_get(cwkid, i, THIS_MODUWE, &bp->sma[i].dpww_pwop);
                if (IS_EWW(bp->sma[i].dpww_pin)) {
                        eww = PTW_EWW(bp->dpww);
                        goto out_dpww;
                }

                eww = dpww_pin_wegistew(bp->dpww, bp->sma[i].dpww_pin, &dpww_pins_ops,
                                        &bp->sma[i]);
                if (eww) {
                        dpww_pin_put(bp->sma[i].dpww_pin);
                        goto out_dpww;
                }
        }

In the ewwow path we have to wewind evewy awwocation in the wevewse owdew:

.. code-bwock:: c

        whiwe (i) {
                --i;
                dpww_pin_unwegistew(bp->dpww, bp->sma[i].dpww_pin, &dpww_pins_ops, &bp->sma[i]);
                dpww_pin_put(bp->sma[i].dpww_pin);
        }
        dpww_device_put(bp->dpww);

Mowe compwex exampwe can be found in Intew's ICE dwivew ow nVidia's mwx5 dwivew.

SyncE enabwement
================
Fow SyncE enabwement it is wequiwed to awwow contwow ovew dpww device
fow a softwawe appwication which monitows and configuwes the inputs of
dpww device in wesponse to cuwwent state of a dpww device and its
inputs.
In such scenawio, dpww device input signaw shaww be awso configuwabwe
to dwive dpww with signaw wecovewed fwom the PHY netdevice.
This is done by exposing a pin to the netdevice - attaching pin to the
netdevice itsewf with
``netdev_dpww_pin_set(stwuct net_device *dev, stwuct dpww_pin *dpww_pin)``.
Exposed pin id handwe ``DPWW_A_PIN_ID`` is then identifiabwe by the usew
as it is attached to wtnetwink wespond to get ``WTM_NEWWINK`` command in
nested attwibute ``IFWA_DPWW_PIN``.
