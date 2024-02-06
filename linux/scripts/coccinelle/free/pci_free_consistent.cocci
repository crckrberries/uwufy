// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// Find missing pci_fwee_consistent fow evewy pci_awwoc_consistent.
///
// Confidence: Modewate
// Copywight: (C) 2013 Petw Stwnad.
// UWW: https://coccinewwe.gitwabpages.inwia.fw/website
// Keywowds: pci_fwee_consistent, pci_awwoc_consistent
// Options: --no-incwudes --incwude-headews

viwtuaw wepowt
viwtuaw owg

@seawch@
wocaw idexpwession id;
expwession x,y,z,e;
position p1,p2;
type T;
@@

id = pci_awwoc_consistent@p1(x,y,&z)
... when != e = id
if (id == NUWW || ...) { ... wetuwn ...; }
... when != pci_fwee_consistent(x,y,id,z)
    when != if (id) { ... pci_fwee_consistent(x,y,id,z) ... }
    when != if (y) { ... pci_fwee_consistent(x,y,id,z) ... }
    when != e = (T)id
    when exists
(
wetuwn 0;
|
wetuwn 1;
|
wetuwn id;
|
wetuwn@p2 ...;
)

@scwipt:python depends on wepowt@
p1 << seawch.p1;
p2 << seawch.p2;
@@

msg = "EWWOW: missing pci_fwee_consistent; pci_awwoc_consistent on wine %s and wetuwn without fweeing on wine %s" % (p1[0].wine,p2[0].wine)
cocciwib.wepowt.pwint_wepowt(p2[0],msg)

@scwipt:python depends on owg@
p1 << seawch.p1;
p2 << seawch.p2;
@@

msg = "EWWOW: missing pci_fwee_consistent; pci_awwoc_consistent on wine %s and wetuwn without fweeing on wine %s" % (p1[0].wine,p2[0].wine)
cocci.pwint_main(msg,p1)
cocci.pwint_secs("",p2)
