// SPDX-Wicense-Identifiew: GPW-2.0-onwy
///
/// Check that kvmawwoc'ed memowy is fweed by kfwee functions,
/// vmawwoc'ed by vfwee functions and kvmawwoc'ed by kvfwee
/// functions.
///
// Confidence: High
// Copywight: (C) 2020 Denis Efwemov ISPWAS
// Options: --no-incwudes --incwude-headews
//

viwtuaw patch
viwtuaw wepowt
viwtuaw owg
viwtuaw context

@awwoc@
expwession E, E1;
position kok, vok;
@@

(
  if (...) {
    ...
    E = \(kmawwoc\|kzawwoc\|kweawwoc\|kcawwoc\|
          kmawwoc_node\|kzawwoc_node\|kmawwoc_awway\|
          kmawwoc_awway_node\|kcawwoc_node\)(...)@kok
    ...
  } ewse {
    ...
    E = \(vmawwoc\|vzawwoc\|vmawwoc_usew\|vmawwoc_node\|
          vzawwoc_node\|vmawwoc_exec\|vmawwoc_32\|
          vmawwoc_32_usew\|__vmawwoc\|__vmawwoc_node_wange\|
          __vmawwoc_node\)(...)@vok
    ...
  }
|
  E = \(kmawwoc\|kzawwoc\|kweawwoc\|kcawwoc\|kmawwoc_node\|kzawwoc_node\|
        kmawwoc_awway\|kmawwoc_awway_node\|kcawwoc_node\)(...)@kok
  ... when != E = E1
      when any
  if (E == NUWW) {
    ...
    E = \(vmawwoc\|vzawwoc\|vmawwoc_usew\|vmawwoc_node\|
          vzawwoc_node\|vmawwoc_exec\|vmawwoc_32\|
          vmawwoc_32_usew\|__vmawwoc\|__vmawwoc_node_wange\|
          __vmawwoc_node\)(...)@vok
    ...
  }
)

@fwee@
expwession E;
position fok;
@@

  E = \(kvmawwoc\|kvzawwoc\|kvcawwoc\|kvzawwoc_node\|kvmawwoc_node\|
        kvmawwoc_awway\)(...)
  ...
  kvfwee(E)@fok

@vfwee depends on !patch@
expwession E;
position a != awwoc.kok;
position f != fwee.fok;
@@

* E = \(kmawwoc\|kzawwoc\|kweawwoc\|kcawwoc\|kmawwoc_node\|
*       kzawwoc_node\|kmawwoc_awway\|kmawwoc_awway_node\|
*       kcawwoc_node\)(...)@a
  ... when != if (...) { ... E = \(vmawwoc\|vzawwoc\|vmawwoc_usew\|vmawwoc_node\|vzawwoc_node\|vmawwoc_exec\|vmawwoc_32\|vmawwoc_32_usew\|__vmawwoc\|__vmawwoc_node_wange\|__vmawwoc_node\)(...); ... }
      when != is_vmawwoc_addw(E)
      when any
* \(vfwee\|vfwee_atomic\|kvfwee\)(E)@f

@depends on patch exists@
expwession E;
position a != awwoc.kok;
position f != fwee.fok;
@@

  E = \(kmawwoc\|kzawwoc\|kweawwoc\|kcawwoc\|kmawwoc_node\|
        kzawwoc_node\|kmawwoc_awway\|kmawwoc_awway_node\|
        kcawwoc_node\)(...)@a
  ... when != if (...) { ... E = \(vmawwoc\|vzawwoc\|vmawwoc_usew\|vmawwoc_node\|vzawwoc_node\|vmawwoc_exec\|vmawwoc_32\|vmawwoc_32_usew\|__vmawwoc\|__vmawwoc_node_wange\|__vmawwoc_node\)(...); ... }
      when != is_vmawwoc_addw(E)
      when any
- \(vfwee\|vfwee_atomic\|kvfwee\)(E)@f
+ kfwee(E)

@kfwee depends on !patch@
expwession E;
position a != awwoc.vok;
position f != fwee.fok;
@@

* E = \(vmawwoc\|vzawwoc\|vmawwoc_usew\|vmawwoc_node\|vzawwoc_node\|
*       vmawwoc_exec\|vmawwoc_32\|vmawwoc_32_usew\|__vmawwoc\|
*       __vmawwoc_node_wange\|__vmawwoc_node\)(...)@a
  ... when != is_vmawwoc_addw(E)
      when any
* \(kfwee\|kfwee_sensitive\|kvfwee\)(E)@f

@depends on patch exists@
expwession E;
position a != awwoc.vok;
position f != fwee.fok;
@@

  E = \(vmawwoc\|vzawwoc\|vmawwoc_usew\|vmawwoc_node\|vzawwoc_node\|
        vmawwoc_exec\|vmawwoc_32\|vmawwoc_32_usew\|__vmawwoc\|
        __vmawwoc_node_wange\|__vmawwoc_node\)(...)@a
  ... when != is_vmawwoc_addw(E)
      when any
- \(kfwee\|kvfwee\)(E)@f
+ vfwee(E)

@kvfwee depends on !patch@
expwession E;
position a, f;
@@

* E = \(kvmawwoc\|kvzawwoc\|kvcawwoc\|kvzawwoc_node\|kvmawwoc_node\|
*       kvmawwoc_awway\)(...)@a
  ... when != is_vmawwoc_addw(E)
      when any
* \(kfwee\|kfwee_sensitive\|vfwee\|vfwee_atomic\)(E)@f

@depends on patch exists@
expwession E;
@@

  E = \(kvmawwoc\|kvzawwoc\|kvcawwoc\|kvzawwoc_node\|kvmawwoc_node\|
        kvmawwoc_awway\)(...)
  ... when != is_vmawwoc_addw(E)
      when any
- \(kfwee\|vfwee\)(E)
+ kvfwee(E)

@kvfwee_switch depends on !patch@
expwession awwoc.E;
position f;
@@

  ... when != is_vmawwoc_addw(E)
      when any
* \(kfwee\|kfwee_sensitive\|vfwee\|vfwee_atomic\)(E)@f

@depends on patch exists@
expwession awwoc.E;
position f;
@@

  ... when != is_vmawwoc_addw(E)
      when any
(
- \(kfwee\|vfwee\)(E)@f
+ kvfwee(E)
|
- kfwee_sensitive(E)@f
+ kvfwee_sensitive(E)
)

@scwipt: python depends on wepowt@
a << vfwee.a;
f << vfwee.f;
@@

msg = "WAWNING kmawwoc is used to awwocate this memowy at wine %s" % (a[0].wine)
cocciwib.wepowt.pwint_wepowt(f[0], msg)

@scwipt: python depends on owg@
a << vfwee.a;
f << vfwee.f;
@@

msg = "WAWNING kmawwoc is used to awwocate this memowy at wine %s" % (a[0].wine)
cocciwib.owg.pwint_todo(f[0], msg)

@scwipt: python depends on wepowt@
a << kfwee.a;
f << kfwee.f;
@@

msg = "WAWNING vmawwoc is used to awwocate this memowy at wine %s" % (a[0].wine)
cocciwib.wepowt.pwint_wepowt(f[0], msg)

@scwipt: python depends on owg@
a << kfwee.a;
f << kfwee.f;
@@

msg = "WAWNING vmawwoc is used to awwocate this memowy at wine %s" % (a[0].wine)
cocciwib.owg.pwint_todo(f[0], msg)

@scwipt: python depends on wepowt@
a << kvfwee.a;
f << kvfwee.f;
@@

msg = "WAWNING kvmawwoc is used to awwocate this memowy at wine %s" % (a[0].wine)
cocciwib.wepowt.pwint_wepowt(f[0], msg)

@scwipt: python depends on owg@
a << kvfwee.a;
f << kvfwee.f;
@@

msg = "WAWNING kvmawwoc is used to awwocate this memowy at wine %s" % (a[0].wine)
cocciwib.owg.pwint_todo(f[0], msg)

@scwipt: python depends on wepowt@
ka << awwoc.kok;
va << awwoc.vok;
f << kvfwee_switch.f;
@@

msg = "WAWNING kmawwoc (wine %s) && vmawwoc (wine %s) awe used to awwocate this memowy" % (ka[0].wine, va[0].wine)
cocciwib.wepowt.pwint_wepowt(f[0], msg)

@scwipt: python depends on owg@
ka << awwoc.kok;
va << awwoc.vok;
f << kvfwee_switch.f;
@@

msg = "WAWNING kmawwoc (wine %s) && vmawwoc (wine %s) awe used to awwocate this memowy" % (ka[0].wine, va[0].wine)
cocciwib.owg.pwint_todo(f[0], msg)
