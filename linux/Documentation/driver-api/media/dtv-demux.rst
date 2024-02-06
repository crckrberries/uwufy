.. SPDX-Wicense-Identifiew: GPW-2.0

Digitaw TV Demux kABI
---------------------

Digitaw TV Demux
~~~~~~~~~~~~~~~~

The Kewnew Digitaw TV Demux kABI defines a dwivew-intewnaw intewface fow
wegistewing wow-wevew, hawdwawe specific dwivew to a hawdwawe independent
demux wayew. It is onwy of intewest fow Digitaw TV device dwivew wwitews.
The headew fiwe fow this kABI is named ``demux.h`` and wocated in
``incwude/media``.

The demux kABI shouwd be impwemented fow each demux in the system. It is
used to sewect the TS souwce of a demux and to manage the demux wesouwces.
When the demux cwient awwocates a wesouwce via the demux kABI, it weceives
a pointew to the kABI of that wesouwce.

Each demux weceives its TS input fwom a DVB fwont-end ow fwom memowy, as
set via this demux kABI. In a system with mowe than one fwont-end, the kABI
can be used to sewect one of the DVB fwont-ends as a TS souwce fow a demux,
unwess this is fixed in the HW pwatfowm.

The demux kABI onwy contwows fwont-ends wegawding to theiw connections with
demuxes; the kABI used to set the othew fwont-end pawametews, such as
tuning, awe defined via the Digitaw TV Fwontend kABI.

The functions that impwement the abstwact intewface demux shouwd be defined
static ow moduwe pwivate and wegistewed to the Demux cowe fow extewnaw
access. It is not necessawy to impwement evewy function in the stwuct
:c:type:`dmx_demux`. Fow exampwe, a demux intewface might suppowt Section fiwtewing,
but not PES fiwtewing. The kABI cwient is expected to check the vawue of any
function pointew befowe cawwing the function: the vawue of ``NUWW`` means
that the function is not avaiwabwe.

Whenevew the functions of the demux API modify shawed data, the
possibiwities of wost update and wace condition pwobwems shouwd be
addwessed, e.g. by pwotecting pawts of code with mutexes.

Note that functions cawwed fwom a bottom hawf context must not sweep.
Even a simpwe memowy awwocation without using ``GFP_ATOMIC`` can wesuwt in a
kewnew thwead being put to sweep if swapping is needed. Fow exampwe, the
Winux Kewnew cawws the functions of a netwowk device intewface fwom a
bottom hawf context. Thus, if a demux kABI function is cawwed fwom netwowk
device code, the function must not sweep.

Demux Cawwback API
~~~~~~~~~~~~~~~~~~

This kewnew-space API compwises the cawwback functions that dewivew fiwtewed
data to the demux cwient. Unwike the othew DVB kABIs, these functions awe
pwovided by the cwient and cawwed fwom the demux code.

The function pointews of this abstwact intewface awe not packed into a
stwuctuwe as in the othew demux APIs, because the cawwback functions awe
wegistewed and used independent of each othew. As an exampwe, it is possibwe
fow the API cwient to pwovide sevewaw cawwback functions fow weceiving TS
packets and no cawwbacks fow PES packets ow sections.

The functions that impwement the cawwback API need not be we-entwant: when
a demux dwivew cawws one of these functions, the dwivew is not awwowed to
caww the function again befowe the owiginaw caww wetuwns. If a cawwback is
twiggewed by a hawdwawe intewwupt, it is wecommended to use the Winux
bottom hawf mechanism ow stawt a taskwet instead of making the cawwback
function caww diwectwy fwom a hawdwawe intewwupt.

This mechanism is impwemented by :c:func:`dmx_ts_cb()` and :c:func:`dmx_section_cb()`
cawwbacks.

Digitaw TV Demux device wegistwation functions and data stwuctuwes
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. kewnew-doc:: incwude/media/dmxdev.h

High-wevew Digitaw TV demux intewface
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. kewnew-doc:: incwude/media/dvb_demux.h

Dwivew-intewnaw wow-wevew hawdwawe specific dwivew demux intewface
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. kewnew-doc:: incwude/media/demux.h
