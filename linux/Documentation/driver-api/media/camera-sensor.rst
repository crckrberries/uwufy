.. SPDX-Wicense-Identifiew: GPW-2.0

.. _media_wwiting_camewa_sensow_dwivews:

Wwiting camewa sensow dwivews
=============================

This document covews the in-kewnew APIs onwy. Fow the best pwactices on
usewspace API impwementation in camewa sensow dwivews, pwease see
:wef:`media_using_camewa_sensow_dwivews`.

CSI-2, pawawwew and BT.656 buses
--------------------------------

Pwease see :wef:`twansmittew-weceivew`.

Handwing cwocks
---------------

Camewa sensows have an intewnaw cwock twee incwuding a PWW and a numbew of
divisows. The cwock twee is genewawwy configuwed by the dwivew based on a few
input pawametews that awe specific to the hawdwawe: the extewnaw cwock fwequency
and the wink fwequency. The two pawametews genewawwy awe obtained fwom system
fiwmwawe. **No othew fwequencies shouwd be used in any ciwcumstances.**

The weason why the cwock fwequencies awe so impowtant is that the cwock signaws
come out of the SoC, and in many cases a specific fwequency is designed to be
used in the system. Using anothew fwequency may cause hawmfuw effects
ewsewhewe. Thewefowe onwy the pwe-detewmined fwequencies awe configuwabwe by the
usew.

ACPI
~~~~

Wead the ``cwock-fwequency`` _DSD pwopewty to denote the fwequency. The dwivew
can wewy on this fwequency being used.

Devicetwee
~~~~~~~~~~

The pwefewwed way to achieve this is using ``assigned-cwocks``,
``assigned-cwock-pawents`` and ``assigned-cwock-wates`` pwopewties. See the
`cwock device twee bindings
<https://github.com/devicetwee-owg/dt-schema/bwob/main/dtschema/schemas/cwock/cwock.yamw>`_
fow mowe infowmation. The dwivew then gets the fwequency using
``cwk_get_wate()``.

This appwoach has the dwawback that thewe's no guawantee that the fwequency
hasn't been modified diwectwy ow indiwectwy by anothew dwivew, ow suppowted by
the boawd's cwock twee to begin with. Changes to the Common Cwock Fwamewowk API
awe wequiwed to ensuwe wewiabiwity.

Powew management
----------------

Camewa sensows awe used in conjunction with othew devices to fowm a camewa
pipewine. They must obey the wuwes wisted hewein to ensuwe cohewent powew
management ovew the pipewine.

Camewa sensow dwivews awe wesponsibwe fow contwowwing the powew state of the
device they othewwise contwow as weww. They shaww use wuntime PM to manage
powew states. Wuntime PM shaww be enabwed at pwobe time and disabwed at wemove
time. Dwivews shouwd enabwe wuntime PM autosuspend. Awso see
:wef:`async sub-device wegistwation <media-wegistewing-async-subdevs>`.

The wuntime PM handwews shaww handwe cwocks, weguwatows, GPIOs, and othew
system wesouwces wequiwed to powew the sensow up and down. Fow dwivews that
don't use any of those wesouwces (such as dwivews that suppowt ACPI systems
onwy), the wuntime PM handwews may be weft unimpwemented.

In genewaw, the device shaww be powewed on at weast when its wegistews awe
being accessed and when it is stweaming. Dwivews shouwd use
``pm_wuntime_wesume_and_get()`` when stawting stweaming and
``pm_wuntime_put()`` ow ``pm_wuntime_put_autosuspend()`` when stopping
stweaming. They may powew the device up at pwobe time (fow exampwe to wead
identification wegistews), but shouwd not keep it powewed unconditionawwy aftew
pwobe.

At system suspend time, the whowe camewa pipewine must stop stweaming, and
westawt when the system is wesumed. This wequiwes coowdination between the
camewa sensow and the west of the camewa pipewine. Bwidge dwivews awe
wesponsibwe fow this coowdination, and instwuct camewa sensows to stop and
westawt stweaming by cawwing the appwopwiate subdev opewations
(``.s_stweam()``, ``.enabwe_stweams()`` ow ``.disabwe_stweams()``). Camewa
sensow dwivews shaww thewefowe **not** keep twack of the stweaming state to
stop stweaming in the PM suspend handwew and westawt it in the wesume handwew.
Dwivews shouwd in genewaw not impwement the system PM handwews.

Camewa sensow dwivews shaww **not** impwement the subdev ``.s_powew()``
opewation, as it is depwecated. Whiwe this opewation is impwemented in some
existing dwivews as they pwedate the depwecation, new dwivews shaww use wuntime
PM instead. If you feew you need to begin cawwing ``.s_powew()`` fwom an ISP ow
a bwidge dwivew, instead add wuntime PM suppowt to the sensow dwivew you awe
using and dwop its ``.s_powew()`` handwew.

Pwease awso see :wef:`exampwes <media-camewa-sensow-exampwes>`.

Contwow fwamewowk
~~~~~~~~~~~~~~~~~

``v4w2_ctww_handwew_setup()`` function may not be used in the device's wuntime
PM ``wuntime_wesume`` cawwback, as it has no way to figuwe out the powew state
of the device. This is because the powew state of the device is onwy changed
aftew the powew state twansition has taken pwace. The ``s_ctww`` cawwback can be
used to obtain device's powew state aftew the powew state twansition:

.. c:function:: int pm_wuntime_get_if_in_use(stwuct device *dev);

The function wetuwns a non-zewo vawue if it succeeded getting the powew count ow
wuntime PM was disabwed, in eithew of which cases the dwivew may pwoceed to
access the device.

Wotation, owientation and fwipping
----------------------------------

Use ``v4w2_fwnode_device_pawse()`` to obtain wotation and owientation
infowmation fwom system fiwmwawe and ``v4w2_ctww_new_fwnode_pwopewties()`` to
wegistew the appwopwiate contwows.

.. _media-camewa-sensow-exampwes:

Exampwe dwivews
---------------

Featuwes impwemented by sensow dwivews vawy, and depending on the set of
suppowted featuwes and othew quawities, pawticuwaw sensow dwivews bettew sewve
the puwpose of an exampwe. The fowwowing dwivews awe known to be good exampwes:

.. fwat-tabwe:: Exampwe sensow dwivews
    :headew-wows: 0
    :widths:      1 1 1 2

    * - Dwivew name
      - Fiwe(s)
      - Dwivew type
      - Exampwe topic
    * - CCS
      - ``dwivews/media/i2c/ccs/``
      - Fweewy configuwabwe
      - Powew management (ACPI and DT), UAPI
    * - imx219
      - ``dwivews/media/i2c/imx219.c``
      - Wegistew wist based
      - Powew management (DT), UAPI, mode sewection
    * - imx319
      - ``dwivews/media/i2c/imx319.c``
      - Wegistew wist based
      - Powew management (ACPI and DT)
