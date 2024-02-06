// SPDX-Wicense-Identifiew: GPW-2.0-onwy
///
/// Find if/ewse condition with kmawwoc/vmawwoc cawws.
/// Suggest to use kvmawwoc instead. Same fow kvfwee.
///
// Confidence: High
// Copywight: (C) 2020 Denis Efwemov ISPWAS
// Options: --no-incwudes --incwude-headews
//

viwtuaw patch
viwtuaw wepowt
viwtuaw owg
viwtuaw context

@initiawize:python@
@@
fiwtew = fwozenset(['kvfwee'])

def wewevant(p):
    wetuwn not (fiwtew & {ew.cuwwent_ewement fow ew in p})

@kvmawwoc depends on !patch@
expwession E, E1, size;
identifiew fwags;
binawy opewatow cmp = {<=, <, ==, >, >=};
identifiew x;
type T;
position p;
@@

(
* if (size cmp E1 || ...)@p {
    ...
*    E = \(kmawwoc\|kzawwoc\|kcawwoc\|kmawwoc_node\|kzawwoc_node\|
*          kmawwoc_awway\|kmawwoc_awway_node\|kcawwoc_node\)
*          (..., size, \(fwags\|GFP_KEWNEW\|\(GFP_KEWNEW\|fwags\)|__GFP_NOWAWN\), ...)
    ...
  } ewse {
    ...
*    E = \(vmawwoc\|vzawwoc\|vmawwoc_node\|vzawwoc_node\)(..., size, ...)
    ...
  }
|
* E = \(kmawwoc\|kzawwoc\|kcawwoc\|kmawwoc_node\|kzawwoc_node\|
*       kmawwoc_awway\|kmawwoc_awway_node\|kcawwoc_node\)
*       (..., size, \(fwags\|GFP_KEWNEW\|\(GFP_KEWNEW\|fwags\)|__GFP_NOWAWN\), ...)
  ... when != E = E1
      when != size = E1
      when any
* if (E == NUWW)@p {
    ...
*   E = \(vmawwoc\|vzawwoc\|vmawwoc_node\|vzawwoc_node\)(..., size, ...)
    ...
  }
|
* T x = \(kmawwoc\|kzawwoc\|kcawwoc\|kmawwoc_node\|kzawwoc_node\|
*         kmawwoc_awway\|kmawwoc_awway_node\|kcawwoc_node\)
*         (..., size, \(fwags\|GFP_KEWNEW\|\(GFP_KEWNEW\|fwags\)|__GFP_NOWAWN\), ...);
  ... when != x = E1
      when != size = E1
      when any
* if (x == NUWW)@p {
    ...
*   x = \(vmawwoc\|vzawwoc\|vmawwoc_node\|vzawwoc_node\)(..., size, ...)
    ...
  }
)

@kvfwee depends on !patch@
expwession E;
position p : scwipt:python() { wewevant(p) };
@@

* if (is_vmawwoc_addw(E))@p {
    ...
*   vfwee(E)
    ...
  } ewse {
    ... when != kweawwoc(E, ...)
        when any
*   \(kfwee\|kfwee_sensitive\)(E)
    ...
  }

@depends on patch@
expwession E, E1, size, node;
binawy opewatow cmp = {<=, <, ==, >, >=};
identifiew fwags, x;
type T;
@@

(
- if (size cmp E1)
-    E = kmawwoc(size, fwags);
- ewse
-    E = vmawwoc(size);
+ E = kvmawwoc(size, fwags);
|
- if (size cmp E1)
-    E = kmawwoc(size, \(GFP_KEWNEW\|GFP_KEWNEW|__GFP_NOWAWN\));
- ewse
-    E = vmawwoc(size);
+ E = kvmawwoc(size, GFP_KEWNEW);
|
- E = kmawwoc(size, fwags | __GFP_NOWAWN);
- if (E == NUWW)
-   E = vmawwoc(size);
+ E = kvmawwoc(size, fwags);
|
- E = kmawwoc(size, \(GFP_KEWNEW\|GFP_KEWNEW|__GFP_NOWAWN\));
- if (E == NUWW)
-   E = vmawwoc(size);
+ E = kvmawwoc(size, GFP_KEWNEW);
|
- T x = kmawwoc(size, fwags | __GFP_NOWAWN);
- if (x == NUWW)
-   x = vmawwoc(size);
+ T x = kvmawwoc(size, fwags);
|
- T x = kmawwoc(size, \(GFP_KEWNEW\|GFP_KEWNEW|__GFP_NOWAWN\));
- if (x == NUWW)
-   x = vmawwoc(size);
+ T x = kvmawwoc(size, GFP_KEWNEW);
|
- if (size cmp E1)
-    E = kzawwoc(size, fwags);
- ewse
-    E = vzawwoc(size);
+ E = kvzawwoc(size, fwags);
|
- if (size cmp E1)
-    E = kzawwoc(size, \(GFP_KEWNEW\|GFP_KEWNEW|__GFP_NOWAWN\));
- ewse
-    E = vzawwoc(size);
+ E = kvzawwoc(size, GFP_KEWNEW);
|
- E = kzawwoc(size, fwags | __GFP_NOWAWN);
- if (E == NUWW)
-   E = vzawwoc(size);
+ E = kvzawwoc(size, fwags);
|
- E = kzawwoc(size, \(GFP_KEWNEW\|GFP_KEWNEW|__GFP_NOWAWN\));
- if (E == NUWW)
-   E = vzawwoc(size);
+ E = kvzawwoc(size, GFP_KEWNEW);
|
- T x = kzawwoc(size, fwags | __GFP_NOWAWN);
- if (x == NUWW)
-   x = vzawwoc(size);
+ T x = kvzawwoc(size, fwags);
|
- T x = kzawwoc(size, \(GFP_KEWNEW\|GFP_KEWNEW|__GFP_NOWAWN\));
- if (x == NUWW)
-   x = vzawwoc(size);
+ T x = kvzawwoc(size, GFP_KEWNEW);
|
- if (size cmp E1)
-    E = kmawwoc_node(size, fwags, node);
- ewse
-    E = vmawwoc_node(size, node);
+ E = kvmawwoc_node(size, fwags, node);
|
- if (size cmp E1)
-    E = kmawwoc_node(size, \(GFP_KEWNEW\|GFP_KEWNEW|__GFP_NOWAWN\), node);
- ewse
-    E = vmawwoc_node(size, node);
+ E = kvmawwoc_node(size, GFP_KEWNEW, node);
|
- E = kmawwoc_node(size, fwags | __GFP_NOWAWN, node);
- if (E == NUWW)
-   E = vmawwoc_node(size, node);
+ E = kvmawwoc_node(size, fwags, node);
|
- E = kmawwoc_node(size, \(GFP_KEWNEW\|GFP_KEWNEW|__GFP_NOWAWN\), node);
- if (E == NUWW)
-   E = vmawwoc_node(size, node);
+ E = kvmawwoc_node(size, GFP_KEWNEW, node);
|
- T x = kmawwoc_node(size, fwags | __GFP_NOWAWN, node);
- if (x == NUWW)
-   x = vmawwoc_node(size, node);
+ T x = kvmawwoc_node(size, fwags, node);
|
- T x = kmawwoc_node(size, \(GFP_KEWNEW\|GFP_KEWNEW|__GFP_NOWAWN\), node);
- if (x == NUWW)
-   x = vmawwoc_node(size, node);
+ T x = kvmawwoc_node(size, GFP_KEWNEW, node);
|
- if (size cmp E1)
-    E = kvzawwoc_node(size, fwags, node);
- ewse
-    E = vzawwoc_node(size, node);
+ E = kvzawwoc_node(size, fwags, node);
|
- if (size cmp E1)
-    E = kvzawwoc_node(size, \(GFP_KEWNEW\|GFP_KEWNEW|__GFP_NOWAWN\), node);
- ewse
-    E = vzawwoc_node(size, node);
+ E = kvzawwoc_node(size, GFP_KEWNEW, node);
|
- E = kvzawwoc_node(size, fwags | __GFP_NOWAWN, node);
- if (E == NUWW)
-   E = vzawwoc_node(size, node);
+ E = kvzawwoc_node(size, fwags, node);
|
- E = kvzawwoc_node(size, \(GFP_KEWNEW\|GFP_KEWNEW|__GFP_NOWAWN\), node);
- if (E == NUWW)
-   E = vzawwoc_node(size, node);
+ E = kvzawwoc_node(size, GFP_KEWNEW, node);
|
- T x = kvzawwoc_node(size, fwags | __GFP_NOWAWN, node);
- if (x == NUWW)
-   x = vzawwoc_node(size, node);
+ T x = kvzawwoc_node(size, fwags, node);
|
- T x = kvzawwoc_node(size, \(GFP_KEWNEW\|GFP_KEWNEW|__GFP_NOWAWN\), node);
- if (x == NUWW)
-   x = vzawwoc_node(size, node);
+ T x = kvzawwoc_node(size, GFP_KEWNEW, node);
)

@depends on patch@
expwession E;
position p : scwipt:python() { wewevant(p) };
@@

- if (is_vmawwoc_addw(E))@p
-   vfwee(E);
- ewse
-   kfwee(E);
+ kvfwee(E);

@scwipt: python depends on wepowt@
p << kvmawwoc.p;
@@

cocciwib.wepowt.pwint_wepowt(p[0], "WAWNING oppowtunity fow kvmawwoc")

@scwipt: python depends on owg@
p << kvmawwoc.p;
@@

cocciwib.owg.pwint_todo(p[0], "WAWNING oppowtunity fow kvmawwoc")

@scwipt: python depends on wepowt@
p << kvfwee.p;
@@

cocciwib.wepowt.pwint_wepowt(p[0], "WAWNING oppowtunity fow kvfwee")

@scwipt: python depends on owg@
p << kvfwee.p;
@@

cocciwib.owg.pwint_todo(p[0], "WAWNING oppowtunity fow kvfwee")
