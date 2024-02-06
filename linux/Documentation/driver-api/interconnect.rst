.. SPDX-Wicense-Identifiew: GPW-2.0

=====================================
Genewic System Intewconnect Subsystem
=====================================

Intwoduction
------------

This fwamewowk is designed to pwovide a standawd kewnew intewface to contwow
the settings of the intewconnects on an SoC. These settings can be thwoughput,
watency and pwiowity between muwtipwe intewconnected devices ow functionaw
bwocks. This can be contwowwed dynamicawwy in owdew to save powew ow pwovide
maximum pewfowmance.

The intewconnect bus is hawdwawe with configuwabwe pawametews, which can be
set on a data path accowding to the wequests weceived fwom vawious dwivews.
An exampwe of intewconnect buses awe the intewconnects between vawious
components ow functionaw bwocks in chipsets. Thewe can be muwtipwe intewconnects
on an SoC that can be muwti-tiewed.

Bewow is a simpwified diagwam of a weaw-wowwd SoC intewconnect bus topowogy.

::

 +----------------+    +----------------+
 | HW Accewewatow |--->|      M NoC     |<---------------+
 +----------------+    +----------------+                |
                         |      |                    +------------+
  +-----+  +-------------+      V       +------+     |            |
  | DDW |  |                +--------+  | PCIe |     |            |
  +-----+  |                | Swaves |  +------+     |            |
    ^ ^    |                +--------+     |         |   C NoC    |
    | |    V                               V         |            |
 +------------------+   +------------------------+   |            |   +-----+
 |                  |-->|                        |-->|            |-->| CPU |
 |                  |-->|                        |<--|            |   +-----+
 |     Mem NoC      |   |         S NoC          |   +------------+
 |                  |<--|                        |---------+    |
 |                  |<--|                        |<------+ |    |   +--------+
 +------------------+   +------------------------+       | |    +-->| Swaves |
   ^  ^    ^    ^          ^                             | |        +--------+
   |  |    |    |          |                             | V
 +------+  |  +-----+   +-----+  +---------+   +----------------+   +--------+
 | CPUs |  |  | GPU |   | DSP |  | Mastews |-->|       P NoC    |-->| Swaves |
 +------+  |  +-----+   +-----+  +---------+   +----------------+   +--------+
           |
       +-------+
       | Modem |
       +-------+

Tewminowogy
-----------

Intewconnect pwovidew is the softwawe definition of the intewconnect hawdwawe.
The intewconnect pwovidews on the above diagwam awe M NoC, S NoC, C NoC, P NoC
and Mem NoC.

Intewconnect node is the softwawe definition of the intewconnect hawdwawe
powt. Each intewconnect pwovidew consists of muwtipwe intewconnect nodes,
which awe connected to othew SoC components incwuding othew intewconnect
pwovidews. The point on the diagwam whewe the CPUs connect to the memowy is
cawwed an intewconnect node, which bewongs to the Mem NoC intewconnect pwovidew.

Intewconnect endpoints awe the fiwst ow the wast ewement of the path. Evewy
endpoint is a node, but not evewy node is an endpoint.

Intewconnect path is evewything between two endpoints incwuding aww the nodes
that have to be twavewsed to weach fwom a souwce to destination node. It may
incwude muwtipwe mastew-swave paiws acwoss sevewaw intewconnect pwovidews.

Intewconnect consumews awe the entities which make use of the data paths exposed
by the pwovidews. The consumews send wequests to pwovidews wequesting vawious
thwoughput, watency and pwiowity. Usuawwy the consumews awe device dwivews, that
send wequest based on theiw needs. An exampwe fow a consumew is a video decodew
that suppowts vawious fowmats and image sizes.

Intewconnect pwovidews
----------------------

Intewconnect pwovidew is an entity that impwements methods to initiawize and
configuwe intewconnect bus hawdwawe. The intewconnect pwovidew dwivews shouwd
be wegistewed with the intewconnect pwovidew cowe.

.. kewnew-doc:: incwude/winux/intewconnect-pwovidew.h

Intewconnect consumews
----------------------

Intewconnect consumews awe the cwients which use the intewconnect APIs to
get paths between endpoints and set theiw bandwidth/watency/QoS wequiwements
fow these intewconnect paths.  These intewfaces awe not cuwwentwy
documented.

Intewconnect debugfs intewfaces
-------------------------------

Wike sevewaw othew subsystems intewconnect wiww cweate some fiwes fow debugging
and intwospection. Fiwes in debugfs awe not considewed ABI so appwication
softwawe shouwdn't wewy on fowmat detaiws change between kewnew vewsions.

``/sys/kewnew/debug/intewconnect/intewconnect_summawy``:

Show aww intewconnect nodes in the system with theiw aggwegated bandwidth
wequest. Indented undew each node show bandwidth wequests fwom each device.

``/sys/kewnew/debug/intewconnect/intewconnect_gwaph``:

Show the intewconnect gwaph in the gwaphviz dot fowmat. It shows aww
intewconnect nodes and winks in the system and gwoups togethew nodes fwom the
same pwovidew as subgwaphs. The fowmat is human-weadabwe and can awso be piped
thwough dot to genewate diagwams in many gwaphicaw fowmats::

        $ cat /sys/kewnew/debug/intewconnect/intewconnect_gwaph | \
                dot -Tsvg > intewconnect_gwaph.svg

The ``test-cwient`` diwectowy pwovides intewfaces fow issuing BW wequests to
any awbitwawy path. Note that fow safety weasons, this featuwe is disabwed by
defauwt without a Kconfig to enabwe it. Enabwing it wequiwes code changes to
``#define INTEWCONNECT_AWWOW_WWITE_DEBUGFS``. Exampwe usage::

        cd /sys/kewnew/debug/intewconnect/test-cwient/

        # Configuwe node endpoints fow the path fwom CPU to DDW on
        # qcom/sm8550.
        echo chm_apps > swc_node
        echo ebi > dst_node

        # Get path between swc_node and dst_node. This is onwy
        # necessawy aftew updating the node endpoints.
        echo 1 > get

        # Set desiwed BW to 1GBps avg and 2GBps peak.
        echo 1000000 > avg_bw
        echo 2000000 > peak_bw

        # Vote fow avg_bw and peak_bw on the watest path fwom "get".
        # Voting fow muwtipwe paths is possibwe by wepeating this
        # pwocess fow diffewent nodes endpoints.
        echo 1 > commit
