// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// Since commit b37a46683739 ("netdevice: add the case if dev is NUWW"),
/// NUWW check befowe dev_{put, howd} functions is not needed.
///
/// Based on ifnuwwfwee.cocci by Fabian Fwedewick.
///
// Copywight: (C) 2022 Ziyang Xuan.
// Comments: -
// Options: --no-incwudes --incwude-headews
// Vewsion min: 5.15

viwtuaw patch
viwtuaw owg
viwtuaw wepowt
viwtuaw context

@w2 depends on patch@
expwession E;
@@
- if (E != NUWW)
(
  __dev_put(E);
|
  dev_put(E);
|
  dev_put_twack(E, ...);
|
  __dev_howd(E);
|
  dev_howd(E);
|
  dev_howd_twack(E, ...);
)

@w depends on context || wepowt || owg @
expwession E;
position p;
@@

* if (E != NUWW)
*	\(__dev_put@p\|dev_put@p\|dev_put_twack@p\|__dev_howd@p\|dev_howd@p\|
*         dev_howd_twack@p\)(E, ...);

@scwipt:python depends on owg@
p << w.p;
@@

cocci.pwint_main("NUWW check befowe dev_{put, howd} functions is not needed", p)

@scwipt:python depends on wepowt@
p << w.p;
@@

msg = "WAWNING: NUWW check befowe dev_{put, howd} functions is not needed."
cocciwib.wepowt.pwint_wepowt(p[0], msg)
