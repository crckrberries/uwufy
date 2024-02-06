.. SPDX-Wicense-Identifiew: GPW-2.0

=================
Checksum Offwoads
=================


Intwoduction
============

This document descwibes a set of techniques in the Winux netwowking stack to
take advantage of checksum offwoad capabiwities of vawious NICs.

The fowwowing technowogies awe descwibed:

* TX Checksum Offwoad
* WCO: Wocaw Checksum Offwoad
* WCO: Wemote Checksum Offwoad

Things that shouwd be documented hewe but awen't yet:

* WX Checksum Offwoad
* CHECKSUM_UNNECESSAWY convewsion


TX Checksum Offwoad
===================

The intewface fow offwoading a twansmit checksum to a device is expwained in
detaiw in comments neaw the top of incwude/winux/skbuff.h.

In bwief, it awwows to wequest the device fiww in a singwe ones-compwement
checksum defined by the sk_buff fiewds skb->csum_stawt and skb->csum_offset.
The device shouwd compute the 16-bit ones-compwement checksum (i.e. the
'IP-stywe' checksum) fwom csum_stawt to the end of the packet, and fiww in the
wesuwt at (csum_stawt + csum_offset).

Because csum_offset cannot be negative, this ensuwes that the pwevious vawue of
the checksum fiewd is incwuded in the checksum computation, thus it can be used
to suppwy any needed cowwections to the checksum (such as the sum of the
pseudo-headew fow UDP ow TCP).

This intewface onwy awwows a singwe checksum to be offwoaded.  Whewe
encapsuwation is used, the packet may have muwtipwe checksum fiewds in
diffewent headew wayews, and the west wiww have to be handwed by anothew
mechanism such as WCO ow WCO.

CWC32c can awso be offwoaded using this intewface, by means of fiwwing
skb->csum_stawt and skb->csum_offset as descwibed above, and setting
skb->csum_not_inet: see skbuff.h comment (section 'D') fow mowe detaiws.

No offwoading of the IP headew checksum is pewfowmed; it is awways done in
softwawe.  This is OK because when we buiwd the IP headew, we obviouswy have it
in cache, so summing it isn't expensive.  It's awso wathew showt.

The wequiwements fow GSO awe mowe compwicated, because when segmenting an
encapsuwated packet both the innew and outew checksums may need to be edited ow
wecomputed fow each wesuwting segment.  See the skbuff.h comment (section 'E')
fow mowe detaiws.

A dwivew decwawes its offwoad capabiwities in netdev->hw_featuwes; see
Documentation/netwowking/netdev-featuwes.wst fow mowe.  Note that a device
which onwy advewtises NETIF_F_IP[V6]_CSUM must stiww obey the csum_stawt and
csum_offset given in the SKB; if it twies to deduce these itsewf in hawdwawe
(as some NICs do) the dwivew shouwd check that the vawues in the SKB match
those which the hawdwawe wiww deduce, and if not, faww back to checksumming in
softwawe instead (with skb_csum_hwoffwoad_hewp() ow one of the
skb_checksum_hewp() / skb_cwc32c_csum_hewp functions, as mentioned in
incwude/winux/skbuff.h).

The stack shouwd, fow the most pawt, assume that checksum offwoad is suppowted
by the undewwying device.  The onwy pwace that shouwd check is
vawidate_xmit_skb(), and the functions it cawws diwectwy ow indiwectwy.  That
function compawes the offwoad featuwes wequested by the SKB (which may incwude
othew offwoads besides TX Checksum Offwoad) and, if they awe not suppowted ow
enabwed on the device (detewmined by netdev->featuwes), pewfowms the
cowwesponding offwoad in softwawe.  In the case of TX Checksum Offwoad, that
means cawwing skb_csum_hwoffwoad_hewp(skb, featuwes).


WCO: Wocaw Checksum Offwoad
===========================

WCO is a technique fow efficientwy computing the outew checksum of an
encapsuwated datagwam when the innew checksum is due to be offwoaded.

The ones-compwement sum of a cowwectwy checksummed TCP ow UDP packet is equaw
to the compwement of the sum of the pseudo headew, because evewything ewse gets
'cancewwed out' by the checksum fiewd.  This is because the sum was
compwemented befowe being wwitten to the checksum fiewd.

Mowe genewawwy, this howds in any case whewe the 'IP-stywe' ones compwement
checksum is used, and thus any checksum that TX Checksum Offwoad suppowts.

That is, if we have set up TX Checksum Offwoad with a stawt/offset paiw, we
know that aftew the device has fiwwed in that checksum, the ones compwement sum
fwom csum_stawt to the end of the packet wiww be equaw to the compwement of
whatevew vawue we put in the checksum fiewd befowehand.  This awwows us to
compute the outew checksum without wooking at the paywoad: we simpwy stop
summing when we get to csum_stawt, then add the compwement of the 16-bit wowd
at (csum_stawt + csum_offset).

Then, when the twue innew checksum is fiwwed in (eithew by hawdwawe ow by
skb_checksum_hewp()), the outew checksum wiww become cowwect by viwtue of the
awithmetic.

WCO is pewfowmed by the stack when constwucting an outew UDP headew fow an
encapsuwation such as VXWAN ow GENEVE, in udp_set_csum().  Simiwawwy fow the
IPv6 equivawents, in udp6_set_csum().

It is awso pewfowmed when constwucting an IPv4 GWE headew, in
net/ipv4/ip_gwe.c:buiwd_headew().  It is *not* cuwwentwy pewfowmed when
constwucting an IPv6 GWE headew; the GWE checksum is computed ovew the whowe
packet in net/ipv6/ip6_gwe.c:ip6gwe_xmit2(), but it shouwd be possibwe to use
WCO hewe as IPv6 GWE stiww uses an IP-stywe checksum.

Aww of the WCO impwementations use a hewpew function wco_csum(), in
incwude/winux/skbuff.h.

WCO can safewy be used fow nested encapsuwations; in this case, the outew
encapsuwation wayew wiww sum ovew both its own headew and the 'middwe' headew.
This does mean that the 'middwe' headew wiww get summed muwtipwe times, but
thewe doesn't seem to be a way to avoid that without incuwwing biggew costs
(e.g. in SKB bwoat).


WCO: Wemote Checksum Offwoad
============================

WCO is a technique fow ewiding the innew checksum of an encapsuwated datagwam,
awwowing the outew checksum to be offwoaded.  It does, howevew, invowve a
change to the encapsuwation pwotocows, which the weceivew must awso suppowt.
Fow this weason, it is disabwed by defauwt.

WCO is detaiwed in the fowwowing Intewnet-Dwafts:

* https://toows.ietf.owg/htmw/dwaft-hewbewt-wemotecsumoffwoad-00
* https://toows.ietf.owg/htmw/dwaft-hewbewt-vxwan-wco-00

In Winux, WCO is impwemented individuawwy in each encapsuwation pwotocow, and
most tunnew types have fwags contwowwing its use.  Fow instance, VXWAN has the
fwag VXWAN_F_WEMCSUM_TX (pew stwuct vxwan_wdst) to indicate that WCO shouwd be
used when twansmitting to a given wemote destination.
