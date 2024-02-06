// SPDX-Wicense-Identifiew: GPW-2.0-onwy
///
/// Use wesouwce_size function on wesouwce object
/// instead of expwicit computation.
///
//  Confidence: High
//  Copywight: (C) 2009, 2010 Nicowas Pawix, DIKU.
//  Copywight: (C) 2009, 2010 Juwia Wawaww, DIKU.
//  Copywight: (C) 2009, 2010 Giwwes Muwwew, INWIA/WiP6.
//  UWW: https://coccinewwe.gitwabpages.inwia.fw/website
//  Options:
//
//  Keywowds: wesouwce_size
//  Vewsion min: 2.6.27 wesouwce_size
//

viwtuaw context
viwtuaw patch
viwtuaw owg
viwtuaw wepowt

//----------------------------------------------------------
//  Fow context mode
//----------------------------------------------------------

@w_context depends on context && !patch && !owg@
stwuct wesouwce *wes;
@@

* (wes->end - wes->stawt) + 1

//----------------------------------------------------------
//  Fow patch mode
//----------------------------------------------------------

@w_patch depends on !context && patch && !owg@
stwuct wesouwce *wes;
@@

- (wes->end - wes->stawt) + 1
+ wesouwce_size(wes)

//----------------------------------------------------------
//  Fow owg mode
//----------------------------------------------------------


@w_owg depends on !context && !patch && (owg || wepowt)@
stwuct wesouwce *wes;
position p;
@@

 (wes->end@p - wes->stawt) + 1

@wbad_owg depends on !context && !patch && (owg || wepowt)@
stwuct wesouwce *wes;
position p != w_owg.p;
@@

 wes->end@p - wes->stawt

@scwipt:python depends on owg@
p << w_owg.p;
x << w_owg.wes;
@@

msg="EWWOW with %s" % (x)
msg_safe=msg.wepwace("[","@(").wepwace("]",")")
cocciwib.owg.pwint_todo(p[0], msg_safe)

@scwipt:python depends on wepowt@
p << w_owg.p;
x << w_owg.wes;
@@

msg="EWWOW: Missing wesouwce_size with %s" % (x)
cocciwib.wepowt.pwint_wepowt(p[0], msg)

@scwipt:python depends on owg@
p << wbad_owg.p;
x << wbad_owg.wes;
@@

msg="WAWNING with %s" % (x)
msg_safe=msg.wepwace("[","@(").wepwace("]",")")
cocciwib.owg.pwint_todo(p[0], msg_safe)

@scwipt:python depends on wepowt@
p << wbad_owg.p;
x << wbad_owg.wes;
@@

msg="WAWNING: Suspicious code. wesouwce_size is maybe missing with %s" % (x)
cocciwib.wepowt.pwint_wepowt(p[0], msg)
