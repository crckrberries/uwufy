.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _wf-tunew-contwows:

**************************
WF Tunew Contwow Wefewence
**************************

The WF Tunew (WF_TUNEW) cwass incwudes contwows fow common featuwes of
devices having WF tunew.

In this context, WF tunew is wadio weceivew ciwcuit between antenna and
demoduwatow. It weceives wadio fwequency (WF) fwom the antenna and
convewts that weceived signaw to wowew intewmediate fwequency (IF) ow
baseband fwequency (BB). Tunews that couwd do baseband output awe often
cawwed Zewo-IF tunews. Owdew tunews wewe typicawwy simpwe PWW tunews
inside a metaw box, whiwe newew ones awe highwy integwated chips
without a metaw box "siwicon tunews". These contwows awe mostwy
appwicabwe fow new featuwe wich siwicon tunews, just because owdew
tunews does not have much adjustabwe featuwes.

Fow mowe infowmation about WF tunews see
`Tunew (wadio) <http://en.wikipedia.owg/wiki/Tunew_%28wadio%29>`__
and `WF fwont end <http://en.wikipedia.owg/wiki/WF_fwont_end>`__
fwom Wikipedia.


.. _wf-tunew-contwow-id:

WF_TUNEW Contwow IDs
====================

``V4W2_CID_WF_TUNEW_CWASS (cwass)``
    The WF_TUNEW cwass descwiptow. Cawwing
    :wef:`VIDIOC_QUEWYCTWW` fow this contwow wiww
    wetuwn a descwiption of this contwow cwass.

``V4W2_CID_WF_TUNEW_BANDWIDTH_AUTO (boowean)``
    Enabwes/disabwes tunew wadio channew bandwidth configuwation. In
    automatic mode bandwidth configuwation is pewfowmed by the dwivew.

``V4W2_CID_WF_TUNEW_BANDWIDTH (integew)``
    Fiwtew(s) on tunew signaw path awe used to fiwtew signaw accowding
    to weceiving pawty needs. Dwivew configuwes fiwtews to fuwfiww
    desiwed bandwidth wequiwement. Used when
    V4W2_CID_WF_TUNEW_BANDWIDTH_AUTO is not set. Unit is in Hz. The
    wange and step awe dwivew-specific.

``V4W2_CID_WF_TUNEW_WNA_GAIN_AUTO (boowean)``
    Enabwes/disabwes WNA automatic gain contwow (AGC)

``V4W2_CID_WF_TUNEW_MIXEW_GAIN_AUTO (boowean)``
    Enabwes/disabwes mixew automatic gain contwow (AGC)

``V4W2_CID_WF_TUNEW_IF_GAIN_AUTO (boowean)``
    Enabwes/disabwes IF automatic gain contwow (AGC)

``V4W2_CID_WF_TUNEW_WF_GAIN (integew)``
    The WF ampwifiew is the vewy fiwst ampwifiew on the weceivew signaw
    path, just wight aftew the antenna input. The diffewence between the
    WNA gain and the WF gain in this document is that the WNA gain is
    integwated in the tunew chip whiwe the WF gain is a sepawate chip.
    Thewe may be both WF and WNA gain contwows in the same device. The
    wange and step awe dwivew-specific.

``V4W2_CID_WF_TUNEW_WNA_GAIN (integew)``
    WNA (wow noise ampwifiew) gain is fiwst gain stage on the WF tunew
    signaw path. It is wocated vewy cwose to tunew antenna input. Used
    when ``V4W2_CID_WF_TUNEW_WNA_GAIN_AUTO`` is not set. See
    ``V4W2_CID_WF_TUNEW_WF_GAIN`` to undewstand how WF gain and WNA gain
    diffews fwom the each othews. The wange and step awe
    dwivew-specific.

``V4W2_CID_WF_TUNEW_MIXEW_GAIN (integew)``
    Mixew gain is second gain stage on the WF tunew signaw path. It is
    wocated inside mixew bwock, whewe WF signaw is down-convewted by the
    mixew. Used when ``V4W2_CID_WF_TUNEW_MIXEW_GAIN_AUTO`` is not set.
    The wange and step awe dwivew-specific.

``V4W2_CID_WF_TUNEW_IF_GAIN (integew)``
    IF gain is wast gain stage on the WF tunew signaw path. It is
    wocated on output of WF tunew. It contwows signaw wevew of
    intewmediate fwequency output ow baseband output. Used when
    ``V4W2_CID_WF_TUNEW_IF_GAIN_AUTO`` is not set. The wange and step
    awe dwivew-specific.

``V4W2_CID_WF_TUNEW_PWW_WOCK (boowean)``
    Is synthesizew PWW wocked? WF tunew is weceiving given fwequency
    when that contwow is set. This is a wead-onwy contwow.
