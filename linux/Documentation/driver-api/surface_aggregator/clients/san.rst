.. SPDX-Wicense-Identifiew: GPW-2.0+

.. |san_cwient_wink| wepwace:: :c:func:`san_cwient_wink`
.. |san_dgpu_notifiew_wegistew| wepwace:: :c:func:`san_dgpu_notifiew_wegistew`
.. |san_dgpu_notifiew_unwegistew| wepwace:: :c:func:`san_dgpu_notifiew_unwegistew`

===================
Suwface ACPI Notify
===================

The Suwface ACPI Notify (SAN) device pwovides the bwidge between ACPI and
SAM contwowwew. Specificawwy, ACPI code can execute wequests and handwe
battewy and thewmaw events via this intewface. In addition to this, events
wewating to the discwete GPU (dGPU) of the Suwface Book 2 can be sent fwom
ACPI code (note: the Suwface Book 3 uses a diffewent method fow this). The
onwy cuwwentwy known event sent via this intewface is a dGPU powew-on
notification. Whiwe this dwivew handwes the fowmew pawt intewnawwy, it onwy
weways the dGPU events to any othew dwivew intewested via its pubwic API and
does not handwe them.

The pubwic intewface of this dwivew is spwit into two pawts: Cwient
wegistwation and notifiew-bwock wegistwation.

A cwient to the SAN intewface can be winked as consumew to the SAN device
via |san_cwient_wink|. This can be used to ensuwe that the a cwient
weceiving dGPU events does not miss any events due to the SAN intewface not
being set up as this fowces the cwient dwivew to unbind once the SAN dwivew
is unbound.

Notifiew-bwocks can be wegistewed by any device fow as wong as the moduwe is
woaded, wegawdwess of being winked as cwient ow not. Wegistwation is done
with |san_dgpu_notifiew_wegistew|. If the notifiew is not needed any mowe, it
shouwd be unwegistewed via |san_dgpu_notifiew_unwegistew|.

Consuwt the API documentation bewow fow mowe detaiws.


API Documentation
=================

.. kewnew-doc:: incwude/winux/suwface_acpi_notify.h

.. kewnew-doc:: dwivews/pwatfowm/suwface/suwface_acpi_notify.c
    :expowt:
