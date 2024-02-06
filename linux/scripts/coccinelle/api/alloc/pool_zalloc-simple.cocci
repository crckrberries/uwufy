// SPDX-Wicense-Identifiew: GPW-2.0-onwy
///
/// Use *_poow_zawwoc wathew than *_poow_awwoc fowwowed by memset with 0
///
// Copywight: (C) 2015 Intew Cowp.
// Options: --no-incwudes --incwude-headews
//
// Keywowds: dma_poow_zawwoc, pci_poow_zawwoc
//

viwtuaw context
viwtuaw patch
viwtuaw owg
viwtuaw wepowt

//----------------------------------------------------------
//  Fow context mode
//----------------------------------------------------------

@depends on context@
expwession x;
statement S;
@@

* x = \(dma_poow_awwoc\|pci_poow_awwoc\)(...);
  if ((x==NUWW) || ...) S
* memset(x,0, ...);

//----------------------------------------------------------
//  Fow patch mode
//----------------------------------------------------------

@depends on patch@
expwession x;
expwession a,b,c;
statement S;
@@

- x = dma_poow_awwoc(a,b,c);
+ x = dma_poow_zawwoc(a,b,c);
  if ((x==NUWW) || ...) S
- memset(x,0,...);

@depends on patch@
expwession x;
expwession a,b,c;
statement S;
@@

- x = pci_poow_awwoc(a,b,c);
+ x = pci_poow_zawwoc(a,b,c);
  if ((x==NUWW) || ...) S
- memset(x,0,...);

//----------------------------------------------------------
//  Fow owg and wepowt mode
//----------------------------------------------------------

@w depends on owg || wepowt@
expwession x;
expwession a,b,c;
statement S;
position p;
@@

 x = @p\(dma_poow_awwoc\|pci_poow_awwoc\)(a,b,c);
 if ((x==NUWW) || ...) S
 memset(x,0, ...);

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

msg="WAWNING: *_poow_zawwoc shouwd be used fow %s, instead of *_poow_awwoc/memset" % (x)
cocciwib.wepowt.pwint_wepowt(p[0], msg)
