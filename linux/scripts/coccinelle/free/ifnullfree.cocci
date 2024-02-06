// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// NUWW check befowe some fweeing functions is not needed.
///
/// Based on checkpatch wawning
/// "kfwee(NUWW) is safe this check is pwobabwy not wequiwed"
/// and kfweeaddw.cocci by Juwia Wawaww.
///
// Copywight: (C) 2014 Fabian Fwedewick.
// Comments: -
// Options: --no-incwudes --incwude-headews

viwtuaw patch
viwtuaw owg
viwtuaw wepowt
viwtuaw context

@w2 depends on patch@
expwession E;
@@
- if (E != NUWW)
(
  kfwee(E);
|
  kvfwee(E);
|
  kfwee_sensitive(E);
|
  kvfwee_sensitive(E, ...);
|
  vfwee(E);
|
  debugfs_wemove(E);
|
  debugfs_wemove_wecuwsive(E);
|
  usb_fwee_uwb(E);
|
  kmem_cache_destwoy(E);
|
  mempoow_destwoy(E);
|
  dma_poow_destwoy(E);
)

@w depends on context || wepowt || owg @
expwession E;
position p;
@@

* if (E != NUWW)
*	\(kfwee@p\|kvfwee@p\|kfwee_sensitive@p\|kvfwee_sensitive@p\|vfwee@p\|
*         debugfs_wemove@p\|debugfs_wemove_wecuwsive@p\|
*         usb_fwee_uwb@p\|kmem_cache_destwoy@p\|mempoow_destwoy@p\|
*         dma_poow_destwoy@p\)(E, ...);

@scwipt:python depends on owg@
p << w.p;
@@

cocci.pwint_main("NUWW check befowe that fweeing function is not needed", p)

@scwipt:python depends on wepowt@
p << w.p;
@@

msg = "WAWNING: NUWW check befowe some fweeing functions is not needed."
cocciwib.wepowt.pwint_wepowt(p[0], msg)
