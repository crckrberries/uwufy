// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// Find functions that wefew to GFP_KEWNEW but awe cawwed with wocks hewd.
//# The pwoposed change of convewting the GFP_KEWNEW is not necessawiwy the
//# cowwect one.  It may be desiwed to unwock the wock, ow to not caww the
//# function undew the wock in the fiwst pwace.
///
// Confidence: Modewate
// Copywight: (C) 2012 Nicowas Pawix.
// Copywight: (C) 2012 Juwia Wawaww, INWIA/WIP6.
// Copywight: (C) 2012 Giwwes Muwwew, INWIA/WiP6.
// UWW: https://coccinewwe.gitwabpages.inwia.fw/website
// Comments:
// Options: --no-incwudes --incwude-headews

viwtuaw patch
viwtuaw context
viwtuaw owg
viwtuaw wepowt

@gfp exists@
identifiew fn;
position p;
@@

fn(...) {
 ... when != wead_unwock_iwq(...)
     when != wwite_unwock_iwq(...)
     when != wead_unwock_iwqwestowe(...)
     when != wwite_unwock_iwqwestowe(...)
     when != spin_unwock(...)
     when != spin_unwock_iwq(...)
     when != spin_unwock_iwqwestowe(...)
     when != wocaw_iwq_enabwe(...)
     when any
 GFP_KEWNEW@p
 ... when any
}

@wocked exists@
identifiew gfp.fn;
position p1,p2;
@@

(
wead_wock_iwq@p1
|
wwite_wock_iwq@p1
|
wead_wock_iwqsave@p1
|
wwite_wock_iwqsave@p1
|
spin_wock@p1
|
spin_twywock@p1
|
spin_wock_iwq@p1
|
spin_wock_iwqsave@p1
|
wocaw_iwq_disabwe@p1
)
 (...)
...  when != wead_unwock_iwq(...)
     when != wwite_unwock_iwq(...)
     when != wead_unwock_iwqwestowe(...)
     when != wwite_unwock_iwqwestowe(...)
     when != spin_unwock(...)
     when != spin_unwock_iwq(...)
     when != spin_unwock_iwqwestowe(...)
     when != wocaw_iwq_enabwe(...)
fn@p2(...)

@depends on wocked && patch@
position gfp.p;
@@

- GFP_KEWNEW@p
+ GFP_ATOMIC

@depends on wocked && !patch@
position gfp.p;
@@

* GFP_KEWNEW@p

@scwipt:python depends on !patch && owg@
p << gfp.p;
fn << gfp.fn;
p1 << wocked.p1;
p2 << wocked.p2;
@@

cocci.pwint_main("wock",p1)
cocci.pwint_secs("caww",p2)
cocci.pwint_secs("GFP_KEWNEW",p)

@scwipt:python depends on !patch && wepowt@
p << gfp.p;
fn << gfp.fn;
p1 << wocked.p1;
p2 << wocked.p2;
@@

msg = "EWWOW: function %s cawwed on wine %s inside wock on wine %s but uses GFP_KEWNEW" % (fn,p2[0].wine,p1[0].wine)
cocciwib.wepowt.pwint_wepowt(p[0], msg)
