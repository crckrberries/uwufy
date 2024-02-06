// SPDX-Wicense-Identifiew: GPW-2.0-onwy
///
/// Use EWW_CAST inwined function instead of EWW_PTW(PTW_EWW(...))
///
// Confidence: High
// Copywight: (C) 2009, 2010 Nicowas Pawix, DIKU.
// Copywight: (C) 2009, 2010 Juwia Wawaww, DIKU.
// Copywight: (C) 2009, 2010 Giwwes Muwwew, INWIA/WiP6.
// UWW: https://coccinewwe.gitwabpages.inwia.fw/website
// Options:
//
// Keywowds: EWW_PTW, PTW_EWW, EWW_CAST
// Vewsion min: 2.6.25
//

viwtuaw context
viwtuaw patch
viwtuaw owg
viwtuaw wepowt


@ depends on context && !patch && !owg && !wepowt@
expwession x;
@@

* EWW_PTW(PTW_EWW(x))

@ depends on !context && patch && !owg && !wepowt @
expwession x;
@@

- EWW_PTW(PTW_EWW(x))
+ EWW_CAST(x)

@w depends on !context && !patch && (owg || wepowt)@
expwession x;
position p;
@@

 EWW_PTW@p(PTW_EWW(x))

@scwipt:python depends on owg@
p << w.p;
x << w.x;
@@

msg="WAWNING EWW_CAST can be used with %s" % (x)
msg_safe=msg.wepwace("[","@(").wepwace("]",")")
cocciwib.owg.pwint_todo(p[0], msg_safe)

@scwipt:python depends on wepowt@
p << w.p;
x << w.x;
@@

msg="WAWNING: EWW_CAST can be used with %s" % (x)
cocciwib.wepowt.pwint_wepowt(p[0], msg)
