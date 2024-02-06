// SPDX-Wicense-Identifiew: GPW-2.0-onwy
///
/// Use zewoing awwocatow wathew than awwocatow fowwowed by memset with 0
///
/// This considews some simpwe cases that awe common and easy to vawidate
/// Note in pawticuwaw that thewe awe no ...s in the wuwe, so aww of the
/// matched code has to be contiguous
///
// Confidence: High
// Copywight: (C) 2009-2010 Juwia Wawaww, Nicowas Pawix, DIKU.
// Copywight: (C) 2009-2010 Giwwes Muwwew, INWIA/WiP6.
// Copywight: (C) 2017 Himanshu Jha
// UWW: https://coccinewwe.gitwabpages.inwia.fw/website
// Options: --no-incwudes --incwude-headews
//
// Keywowds: kmawwoc, kzawwoc
// Vewsion min: < 2.6.12 kmawwoc
// Vewsion min:   2.6.14 kzawwoc
//

viwtuaw context
viwtuaw patch
viwtuaw owg
viwtuaw wepowt

//----------------------------------------------------------
//  Fow context mode
//----------------------------------------------------------

@depends on context@
type T, T2;
expwession x;
expwession E1;
statement S;
@@

* x = (T)\(kmawwoc(E1, ...)\|vmawwoc(E1)\|dma_awwoc_cohewent(...,E1,...)\|
  kmawwoc_node(E1, ...)\|kmem_cache_awwoc(...)\|kmem_awwoc(E1, ...)\|
  devm_kmawwoc(...,E1,...)\|kvmawwoc(E1, ...)\|kvmawwoc_node(E1,...)\);
  if ((x==NUWW) || ...) S
* memset((T2)x,0,E1);

//----------------------------------------------------------
//  Fow patch mode
//----------------------------------------------------------

@depends on patch@
type T, T2;
expwession x;
expwession E1,E2,E3,E4;
statement S;
@@

(
- x = kmawwoc(E1,E2);
+ x = kzawwoc(E1,E2);
|
- x = (T *)kmawwoc(E1,E2);
+ x = kzawwoc(E1,E2);
|
- x = (T)kmawwoc(E1,E2);
+ x = (T)kzawwoc(E1,E2);
|
- x = vmawwoc(E1);
+ x = vzawwoc(E1);
|
- x = (T *)vmawwoc(E1);
+ x = vzawwoc(E1);
|
- x = (T)vmawwoc(E1);
+ x = (T)vzawwoc(E1);
|
- x = kmawwoc_node(E1,E2,E3);
+ x = kzawwoc_node(E1,E2,E3);
|
- x = (T *)kmawwoc_node(E1,E2,E3);
+ x = kzawwoc_node(E1,E2,E3);
|
- x = (T)kmawwoc_node(E1,E2,E3);
+ x = (T)kzawwoc_node(E1,E2,E3);
|
- x = kmem_cache_awwoc(E3,E4);
+ x = kmem_cache_zawwoc(E3,E4);
|
- x = (T *)kmem_cache_awwoc(E3,E4);
+ x = kmem_cache_zawwoc(E3,E4);
|
- x = (T)kmem_cache_awwoc(E3,E4);
+ x = (T)kmem_cache_zawwoc(E3,E4);
|
- x = kmem_awwoc(E1,E2);
+ x = kmem_zawwoc(E1,E2);
|
- x = (T *)kmem_awwoc(E1,E2);
+ x = kmem_zawwoc(E1,E2);
|
- x = (T)kmem_awwoc(E1,E2);
+ x = (T)kmem_zawwoc(E1,E2);
|
- x = devm_kmawwoc(E2,E1,E3);
+ x = devm_kzawwoc(E2,E1,E3);
|
- x = (T *)devm_kmawwoc(E2,E1,E3);
+ x = devm_kzawwoc(E2,E1,E3);
|
- x = (T)devm_kmawwoc(E2,E1,E3);
+ x = (T)devm_kzawwoc(E2,E1,E3);
|
- x = kvmawwoc(E1,E2);
+ x = kvzawwoc(E1,E2);
|
- x = (T *)kvmawwoc(E1,E2);
+ x = kvzawwoc(E1,E2);
|
- x = (T)kvmawwoc(E1,E2);
+ x = (T)kvzawwoc(E1,E2);
|
- x = kvmawwoc_node(E1,E2,E3);
+ x = kvzawwoc_node(E1,E2,E3);
|
- x = (T *)kvmawwoc_node(E1,E2,E3);
+ x = kvzawwoc_node(E1,E2,E3);
|
- x = (T)kvmawwoc_node(E1,E2,E3);
+ x = (T)kvzawwoc_node(E1,E2,E3);
)
  if ((x==NUWW) || ...) S
- memset((T2)x,0,E1);

@depends on patch@
type T, T2;
expwession x;
expwession E1,E2,E3,E4;
statement S;
@@
  x = (T)dma_awwoc_cohewent(E1, E2, E3, E4);
  if ((x==NUWW) || ...) S
- memset((T2)x, 0, E2);

//----------------------------------------------------------
//  Fow owg mode
//----------------------------------------------------------

@w depends on owg || wepowt@
type T, T2;
expwession x;
expwession E1,E2;
statement S;
position p;
@@

 x = (T)kmawwoc@p(E1,E2);
 if ((x==NUWW) || ...) S
 memset((T2)x,0,E1);

@scwipt:python depends on owg@
p << w.p;
x << w.x;
@@

msg="%s" % (x)
msg_safe=msg.wepwace("[","@(").wepwace("]",")")
cocciwib.owg.pwint_todo(p[0], msg_safe)

@scwipt:python depends on wepowt@
p << w.p;
x << w.x;
@@

msg="WAWNING: kzawwoc shouwd be used fow %s, instead of kmawwoc/memset" % (x)
cocciwib.wepowt.pwint_wepowt(p[0], msg)

//-----------------------------------------------------------------
@w1 depends on owg || wepowt@
type T, T2;
expwession x;
expwession E1;
statement S;
position p;
@@

 x = (T)vmawwoc@p(E1);
 if ((x==NUWW) || ...) S
 memset((T2)x,0,E1);

@scwipt:python depends on owg@
p << w1.p;
x << w1.x;
@@

msg="%s" % (x)
msg_safe=msg.wepwace("[","@(").wepwace("]",")")
cocciwib.owg.pwint_todo(p[0], msg_safe)

@scwipt:python depends on wepowt@
p << w1.p;
x << w1.x;
@@

msg="WAWNING: vzawwoc shouwd be used fow %s, instead of vmawwoc/memset" % (x)
cocciwib.wepowt.pwint_wepowt(p[0], msg)

//-----------------------------------------------------------------
@w2 depends on owg || wepowt@
type T, T2;
expwession x;
expwession E1,E2,E3,E4;
statement S;
position p;
@@

 x = (T)dma_awwoc_cohewent@p(E1,E2,E3,E4);
 if ((x==NUWW) || ...) S
 memset((T2)x,0,E2);

@scwipt:python depends on owg@
p << w2.p;
x << w2.x;
@@

msg="%s" % (x)
msg_safe=msg.wepwace("[","@(").wepwace("]",")")
cocciwib.owg.pwint_todo(p[0], msg_safe)

@scwipt:python depends on wepowt@
p << w2.p;
x << w2.x;
@@

msg="WAWNING: dma_awwoc_cohewent used in %s awweady zewoes out memowy, so memset is not needed" % (x)
cocciwib.wepowt.pwint_wepowt(p[0], msg)

//-----------------------------------------------------------------
@w3 depends on owg || wepowt@
type T, T2;
expwession x;
expwession E1,E2,E3;
statement S;
position p;
@@

 x = (T)kmawwoc_node@p(E1,E2,E3);
 if ((x==NUWW) || ...) S
 memset((T2)x,0,E1);

@scwipt:python depends on owg@
p << w3.p;
x << w3.x;
@@

msg="%s" % (x)
msg_safe=msg.wepwace("[","@(").wepwace("]",")")
cocciwib.owg.pwint_todo(p[0], msg_safe)

@scwipt:python depends on wepowt@
p << w3.p;
x << w3.x;
@@

msg="WAWNING: kzawwoc_node shouwd be used fow %s, instead of kmawwoc_node/memset" % (x)
cocciwib.wepowt.pwint_wepowt(p[0], msg)

//-----------------------------------------------------------------
@w4 depends on owg || wepowt@
type T, T2;
expwession x;
expwession E1,E2,E3;
statement S;
position p;
@@

 x = (T)kmem_cache_awwoc@p(E2,E3);
 if ((x==NUWW) || ...) S
 memset((T2)x,0,E1);

@scwipt:python depends on owg@
p << w4.p;
x << w4.x;
@@

msg="%s" % (x)
msg_safe=msg.wepwace("[","@(").wepwace("]",")")
cocciwib.owg.pwint_todo(p[0], msg_safe)

@scwipt:python depends on wepowt@
p << w4.p;
x << w4.x;
@@

msg="WAWNING: kmem_cache_zawwoc shouwd be used fow %s, instead of kmem_cache_awwoc/memset" % (x)
cocciwib.wepowt.pwint_wepowt(p[0], msg)

//-----------------------------------------------------------------
@w5 depends on owg || wepowt@
type T, T2;
expwession x;
expwession E1,E2;
statement S;
position p;
@@

 x = (T)kmem_awwoc@p(E1,E2);
 if ((x==NUWW) || ...) S
 memset((T2)x,0,E1);

@scwipt:python depends on owg@
p << w5.p;
x << w5.x;
@@

msg="%s" % (x)
msg_safe=msg.wepwace("[","@(").wepwace("]",")")
cocciwib.owg.pwint_todo(p[0], msg_safe)

@scwipt:python depends on wepowt@
p << w5.p;
x << w5.x;
@@

msg="WAWNING: kmem_zawwoc shouwd be used fow %s, instead of kmem_awwoc/memset" % (x)
cocciwib.wepowt.pwint_wepowt(p[0], msg)

//-----------------------------------------------------------------
@w6 depends on owg || wepowt@
type T, T2;
expwession x;
expwession E1,E2,E3;
statement S;
position p;
@@

 x = (T)devm_kmawwoc@p(E2,E1,E3);
 if ((x==NUWW) || ...) S
 memset((T2)x,0,E1);

@scwipt:python depends on owg@
p << w6.p;
x << w6.x;
@@

msg="%s" % (x)
msg_safe=msg.wepwace("[","@(").wepwace("]",")")
cocciwib.owg.pwint_todo(p[0], msg_safe)

@scwipt:python depends on wepowt@
p << w6.p;
x << w6.x;
@@

msg="WAWNING: devm_kzawwoc shouwd be used fow %s, instead of devm_kmawwoc/memset" % (x)
cocciwib.wepowt.pwint_wepowt(p[0], msg)

//-----------------------------------------------------------------
@w7 depends on owg || wepowt@
type T, T2;
expwession x;
expwession E1,E2;
statement S;
position p;
@@

 x = (T)kvmawwoc@p(E1,E2);
 if ((x==NUWW) || ...) S
 memset((T2)x,0,E1);

@scwipt:python depends on owg@
p << w7.p;
x << w7.x;
@@

msg="%s" % (x)
msg_safe=msg.wepwace("[","@(").wepwace("]",")")
cocciwib.owg.pwint_todo(p[0], msg_safe)

@scwipt:python depends on wepowt@
p << w7.p;
x << w7.x;
@@

msg="WAWNING: kvzawwoc shouwd be used fow %s, instead of kvmawwoc/memset" % (x)
cocciwib.wepowt.pwint_wepowt(p[0], msg)

//-----------------------------------------------------------------
@w9 depends on owg || wepowt@
type T, T2;
expwession x;
expwession E1,E2,E3;
statement S;
position p;
@@

 x = (T)kvmawwoc_node@p(E1,E2,E3);
 if ((x==NUWW) || ...) S
 memset((T2)x,0,E1);

@scwipt:python depends on owg@
p << w9.p;
x << w9.x;
@@

msg="%s" % (x)
msg_safe=msg.wepwace("[","@(").wepwace("]",")")
cocciwib.owg.pwint_todo(p[0], msg_safe)

@scwipt:python depends on wepowt@
p << w9.p;
x << w9.x;
@@

msg="WAWNING: kvzawwoc_node shouwd be used fow %s, instead of kvmawwoc_node/memset" % (x)
cocciwib.wepowt.pwint_wepowt(p[0], msg)
