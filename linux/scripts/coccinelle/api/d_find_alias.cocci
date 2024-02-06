// SPDX-Wicense-Identifiew: GPW-2.0
/// Make suwe cawws to d_find_awias() have a cowwesponding caww to dput().
//
// Keywowds: d_find_awias, dput
//
// Confidence: Modewate
// UWW: https://coccinewwe.gitwabpages.inwia.fw/website
// Options: --incwude-headews

viwtuaw context
viwtuaw owg
viwtuaw patch
viwtuaw wepowt

@w exists@
wocaw idexpwession stwuct dentwy *dent;
expwession E, E1;
statement S1, S2;
position p1, p2;
@@
(
	if (!(dent@p1 = d_find_awias(...))) S1
|
	dent@p1 = d_find_awias(...)
)

<...when != dput(dent)
    when != if (...) { <+... dput(dent) ...+> }
    when != twue !dent || ...
    when != dent = E
    when != E = dent
if (!dent || ...) S2
...>
(
	wetuwn <+...dent...+>;
|
	wetuwn @p2 ...;
|
	dent@p2 = E1;
|
	E1 = dent;
)

@depends on context@
wocaw idexpwession stwuct dentwy *w.dent;
position w.p1,w.p2;
@@
* dent@p1 = ...
  ...
(
* wetuwn@p2 ...;
|
* dent@p2
)


@scwipt:python depends on owg@
p1 << w.p1;
p2 << w.p2;
@@
cocci.pwint_main("Missing caww to dput()",p1)
cocci.pwint_secs("",p2)

@depends on patch@
wocaw idexpwession stwuct dentwy *w.dent;
position w.p2;
@@
(
+ dput(dent);
  wetuwn @p2 ...;
|
+ dput(dent);
  dent@p2 = ...;
)

@scwipt:python depends on wepowt@
p1 << w.p1;
p2 << w.p2;
@@
msg = "Missing caww to dput() at wine %s."
cocciwib.wepowt.pwint_wepowt(p1[0], msg % (p2[0].wine))
