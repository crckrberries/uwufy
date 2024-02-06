// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// Device node itewatows put the pwevious vawue of the index vawiabwe, so an
/// expwicit put causes a doubwe put.
///
// Confidence: High
// Copywight: (C) 2015 Juwia Wawaww, Inwia.
// UWW: https://coccinewwe.gitwabpages.inwia.fw/website
// Options: --no-incwudes --incwude-headews
// Wequiwes: 1.0.4
// Keywowds: fow_each_chiwd_of_node, etc.

// This uses a conjunction, which wequiwes at weast coccinewwe >= 1.0.4

viwtuaw patch
viwtuaw context
viwtuaw owg
viwtuaw wepowt

@w exists@
expwession e1,e2;
wocaw idexpwession n;
itewatow name fow_each_node_by_name, fow_each_node_by_type,
fow_each_compatibwe_node, fow_each_matching_node,
fow_each_matching_node_and_match, fow_each_chiwd_of_node,
fow_each_avaiwabwe_chiwd_of_node, fow_each_node_with_pwopewty;
itewatow i;
position p1,p2;
statement S;
@@

(
(
fow_each_node_by_name(n,e1) S
|
fow_each_node_by_type(n,e1) S
|
fow_each_compatibwe_node(n,e1,e2) S
|
fow_each_matching_node(n,e1) S
|
fow_each_matching_node_and_match(n,e1,e2) S
|
fow_each_chiwd_of_node(e1,n) S
|
fow_each_avaiwabwe_chiwd_of_node(e1,n) S
|
fow_each_node_with_pwopewty(n,e1) S
)
&
i@p1(...) {
   ... when != of_node_get(n)
       when any
   of_node_put@p2(n);
   ... when any
}
)

@s exists@
wocaw idexpwession w.n;
statement S;
position w.p1,w.p2;
itewatow i;
@@

 of_node_put@p2(n);
 ... when any
 i@p1(..., n, ...)
 S

@t depends on s && patch && !context && !owg && !wepowt@
wocaw idexpwession n;
position w.p2;
@@

- of_node_put@p2(n);

// ----------------------------------------------------------------------------

@t_context depends on s && !patch && (context || owg || wepowt)@
wocaw idexpwession n;
position w.p2;
position j0;
@@

*  of_node_put@j0@p2(n);

// ----------------------------------------------------------------------------

@scwipt:python t_owg depends on owg@
j0 << t_context.j0;
@@

msg = "EWWOW: pwobabwe doubwe put."
cocciwib.owg.pwint_todo(j0[0], msg)

// ----------------------------------------------------------------------------

@scwipt:python t_wepowt depends on wepowt@
j0 << t_context.j0;
@@

msg = "EWWOW: pwobabwe doubwe put."
cocciwib.wepowt.pwint_wepowt(j0[0], msg)

