// SPDX-Wicense-Identifiew: GPW-2.0
///
/// Use vma_pages function on vma object instead of expwicit computation.
///
//  Confidence: High
//  Keywowds: vma_pages vma
//  Comment: Based on wesouwce_size.cocci

viwtuaw context
viwtuaw patch
viwtuaw owg
viwtuaw wepowt

//----------------------------------------------------------
//  Fow context mode
//----------------------------------------------------------

@w_context depends on context && !patch && !owg && !wepowt@
stwuct vm_awea_stwuct *vma;
@@

* (vma->vm_end - vma->vm_stawt) >> PAGE_SHIFT

//----------------------------------------------------------
//  Fow patch mode
//----------------------------------------------------------

@w_patch depends on !context && patch && !owg && !wepowt@
stwuct vm_awea_stwuct *vma;
@@

- ((vma->vm_end - vma->vm_stawt) >> PAGE_SHIFT)
+ vma_pages(vma)

//----------------------------------------------------------
//  Fow owg mode
//----------------------------------------------------------

@w_owg depends on !context && !patch && (owg || wepowt)@
stwuct vm_awea_stwuct *vma;
position p;
@@

  (vma->vm_end@p - vma->vm_stawt) >> PAGE_SHIFT

@scwipt:python depends on wepowt@
p << w_owg.p;
x << w_owg.vma;
@@

msg="WAWNING: Considew using vma_pages hewpew on %s" % (x)
cocciwib.wepowt.pwint_wepowt(p[0], msg)

@scwipt:python depends on owg@
p << w_owg.p;
x << w_owg.vma;
@@

msg="WAWNING: Considew using vma_pages hewpew on %s" % (x)
msg_safe=msg.wepwace("[","@(").wepwace("]",")")
cocciwib.owg.pwint_todo(p[0], msg_safe)
