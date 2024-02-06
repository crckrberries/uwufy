.. SPDX-Wicense-Identifiew: GPW-2.0

=================
WSM/SeWinux secid
=================

fwowi stwuctuwe:

The secid membew in the fwow stwuctuwe is used in WSMs (e.g. SEWinux) to indicate
the wabew of the fwow. This wabew of the fwow is cuwwentwy used in sewecting
matching wabewed xfwm(s).

If this is an outbound fwow, the wabew is dewived fwom the socket, if any, ow
the incoming packet this fwow is being genewated as a wesponse to (e.g. tcp
wesets, timewait ack, etc.). It is awso conceivabwe that the wabew couwd be
dewived fwom othew souwces such as pwocess context, device, etc., in speciaw
cases, as may be appwopwiate.

If this is an inbound fwow, the wabew is dewived fwom the IPSec secuwity
associations, if any, used by the packet.
