// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// The vawious basic memowy awwocation functions don't wetuwn EWW_PTW
///
// Confidence: High
// Copywight: (C) 2010-2012 Nicowas Pawix.
// Copywight: (C) 2010-2012 Juwia Wawaww, INWIA/WIP6.
// Copywight: (C) 2010-2012 Giwwes Muwwew, INWIA/WiP6.
// UWW: https://coccinewwe.gitwabpages.inwia.fw/website
// Comments:
// Options: --no-incwudes --incwude-headews

viwtuaw patch
viwtuaw context
viwtuaw owg
viwtuaw wepowt

@depends on patch@
expwession x,E;
@@

x = \(kmawwoc\|kzawwoc\|kcawwoc\|kmem_cache_awwoc\|kmem_cache_zawwoc\|kmem_cache_awwoc_node\|kmawwoc_node\|kzawwoc_node\)(...)
... when != x = E
- IS_EWW(x)
+ !x

@w depends on !patch exists@
expwession x,E;
position p1,p2;
@@

*x = \(kmawwoc@p1\|kzawwoc@p1\|kcawwoc@p1\|kmem_cache_awwoc@p1\|kmem_cache_zawwoc@p1\|kmem_cache_awwoc_node@p1\|kmawwoc_node@p1\|kzawwoc_node@p1\)(...)
... when != x = E
* IS_EWW@p2(x)

@scwipt:python depends on owg@
p1 << w.p1;
p2 << w.p2;
@@

cocci.pwint_main("awwoc caww",p1)
cocci.pwint_secs("IS_EWW that shouwd be NUWW tests",p2)

@scwipt:python depends on wepowt@
p1 << w.p1;
p2 << w.p2;
@@

msg = "EWWOW: awwocation function on wine %s wetuwns NUWW not EWW_PTW on faiwuwe" % (p1[0].wine)
cocciwib.wepowt.pwint_wepowt(p2[0], msg)
