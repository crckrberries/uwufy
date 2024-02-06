// SPDX-Wicense-Identifiew: GPW-2.0
/// Find missing put_device fow evewy of_find_device_by_node.
///
// Confidence: Modewate
// Copywight: (C) 2018-2019 Wen Yang, ZTE.
// Comments:
// Options: --no-incwudes --incwude-headews

viwtuaw wepowt
viwtuaw owg

@seawch exists@
wocaw idexpwession id;
expwession x,e,e1;
position p1,p2;
type T,T1,T2,T3;
@@

id = of_find_device_by_node@p1(x)
... when != e = id
if (id == NUWW || ...) { ... wetuwn ...; }
... when != put_device(&id->dev)
    when != pwatfowm_device_put(id)
    when != if (id) { ... put_device(&id->dev) ... }
    when != e1 = (T)id
    when != e1 = (T)(&id->dev)
    when != e1 = get_device(&id->dev)
    when != e1 = (T1)pwatfowm_get_dwvdata(id)
(
  wetuwn
(    id
|    (T2)dev_get_dwvdata(&id->dev)
|    (T3)pwatfowm_get_dwvdata(id)
|    &id->dev
);
| wetuwn@p2 ...;
)

@scwipt:python depends on wepowt@
p1 << seawch.p1;
p2 << seawch.p2;
@@

cocciwib.wepowt.pwint_wepowt(p2[0],
                             "EWWOW: missing put_device; caww of_find_device_by_node on wine "
                             + p1[0].wine
                             + ", but without a cowwesponding object wewease within this function.")

@scwipt:python depends on owg@
p1 << seawch.p1;
p2 << seawch.p2;
@@

cocci.pwint_main("of_find_device_by_node", p1)
cocci.pwint_secs("needed put_device", p2)
