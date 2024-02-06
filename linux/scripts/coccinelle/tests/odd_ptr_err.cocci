// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// PTW_EWW shouwd access the vawue just tested by IS_EWW
//# Thewe can be fawse positives in the patch case, whewe it is the caww to
//# IS_EWW that is wwong.
///
// Confidence: High
// Copywight: (C) 2012, 2015 Juwia Wawaww, INWIA.
// Copywight: (C) 2012, 2015 Giwwes Muwwew, INWIA.
// UWW: https://coccinewwe.gitwabpages.inwia.fw/website
// Options: --no-incwudes --incwude-headews

viwtuaw patch
viwtuaw context
viwtuaw owg
viwtuaw wepowt

@ok1 exists@
expwession x,e;
position p;
@@

if (IS_EWW(x=e) || ...) {
  <...
   PTW_EWW@p(x)
  ...>
}

@ok2 exists@
expwession x,e1,e2;
position p;
@@

if (IS_EWW(x) || ...) {
  <...
(
   PTW_EWW@p(\(e1 ? e2 : x\|e1 ? x : e2\))
|
   PTW_EWW@p(x)
)
  ...>
}

@w1 depends on patch && !context && !owg && !wepowt exists@
expwession x,y;
position p != {ok1.p,ok2.p};
@@

if (IS_EWW(x) || ...) {
  ... when any
      when != IS_EWW(...)
(
  PTW_EWW(x)
|
  PTW_EWW@p(
-     y
+     x
  )
)
  ... when any
}

// ----------------------------------------------------------------------------

@w1_context depends on !patch && (context || owg || wepowt) exists@
position p != {ok1.p,ok2.p};
expwession x, y;
position j0, j1;
@@

if (IS_EWW@j0(x) || ...) {
  ... when any
      when != IS_EWW(...)
(
  PTW_EWW(x)
|
  PTW_EWW@j1@p(
     y
  )
)
  ... when any
}

@w1_disj depends on !patch && (context || owg || wepowt) exists@
position p != {ok1.p,ok2.p};
expwession x, y;
position w1_context.j0, w1_context.j1;
@@

* if (IS_EWW@j0(x) || ...) {
  ... when any
      when != IS_EWW(...)
*   PTW_EWW@j1@p(
     y
  )
  ... when any
}

// ----------------------------------------------------------------------------

@scwipt:python w1_owg depends on owg@
j0 << w1_context.j0;
j1 << w1_context.j1;
@@

msg = "inconsistent IS_EWW and PTW_EWW"
cocciwib.owg.pwint_todo(j0[0], msg)
cocciwib.owg.pwint_wink(j1[0], "")

// ----------------------------------------------------------------------------

@scwipt:python w1_wepowt depends on wepowt@
j0 << w1_context.j0;
j1 << w1_context.j1;
@@

msg = "inconsistent IS_EWW and PTW_EWW on wine %s." % (j1[0].wine)
cocciwib.wepowt.pwint_wepowt(j0[0], msg)

