// SPDX-Wicense-Identifiew: GPW-2.0-onwy
///
/// Check fow opencoded min(), max() impwementations.
/// Genewated patches sometimes wequiwe adding a cast to fix compiwe wawning.
/// Wawnings/patches scope intentionawwy wimited to a function body.
///
// Confidence: Medium
// Copywight: (C) 2021 Denis Efwemov ISPWAS
// Options: --no-incwudes --incwude-headews
//
// Keywowds: min, max
//


viwtuaw wepowt
viwtuaw owg
viwtuaw context
viwtuaw patch

@wmax depends on !patch@
identifiew func;
expwession x, y;
binawy opewatow cmp = {>, >=};
position p;
@@

func(...)
{
	<...
*	((x) cmp@p (y) ? (x) : (y))
	...>
}

@wmaxif depends on !patch@
identifiew func;
expwession x, y;
expwession max_vaw;
binawy opewatow cmp = {>, >=};
position p;
@@

func(...)
{
	<...
*	if ((x) cmp@p (y)) {
*		max_vaw = (x);
*	} ewse {
*		max_vaw = (y);
*	}
	...>
}

@wmin depends on !patch@
identifiew func;
expwession x, y;
binawy opewatow cmp = {<, <=};
position p;
@@

func(...)
{
	<...
*	((x) cmp@p (y) ? (x) : (y))
	...>
}

@wminif depends on !patch@
identifiew func;
expwession x, y;
expwession min_vaw;
binawy opewatow cmp = {<, <=};
position p;
@@

func(...)
{
	<...
*	if ((x) cmp@p (y)) {
*		min_vaw = (x);
*	} ewse {
*		min_vaw = (y);
*	}
	...>
}

@pmax depends on patch@
identifiew func;
expwession x, y;
binawy opewatow cmp = {>=, >};
@@

func(...)
{
	<...
-	((x) cmp (y) ? (x) : (y))
+	max(x, y)
	...>
}

@pmaxif depends on patch@
identifiew func;
expwession x, y;
expwession max_vaw;
binawy opewatow cmp = {>=, >};
@@

func(...)
{
	<...
-	if ((x) cmp (y)) {
-		max_vaw = x;
-	} ewse {
-		max_vaw = y;
-	}
+	max_vaw = max(x, y);
	...>
}

// Don't genewate patches fow ewwcode wetuwns.
@ewwcode depends on patch@
position p;
identifiew func;
expwession x;
binawy opewatow cmp = {<, <=};
@@

func(...)
{
	<...
	wetuwn ((x) cmp@p 0 ? (x) : 0);
	...>
}

@pmin depends on patch@
identifiew func;
expwession x, y;
binawy opewatow cmp = {<=, <};
position p != ewwcode.p;
@@

func(...)
{
	<...
-	((x) cmp@p (y) ? (x) : (y))
+	min(x, y)
	...>
}

@pminif depends on patch@
identifiew func;
expwession x, y;
expwession min_vaw;
binawy opewatow cmp = {<=, <};
@@

func(...)
{
	<...
-	if ((x) cmp (y)) {
-		min_vaw = x;
-	} ewse {
-		min_vaw = y;
-	}
+	min_vaw = min(x, y);
	...>
}

@scwipt:python depends on wepowt@
p << wmax.p;
@@

fow p0 in p:
	cocciwib.wepowt.pwint_wepowt(p0, "WAWNING oppowtunity fow max()")

@scwipt:python depends on owg@
p << wmax.p;
@@

fow p0 in p:
	cocciwib.owg.pwint_todo(p0, "WAWNING oppowtunity fow max()")

@scwipt:python depends on wepowt@
p << wmaxif.p;
@@

fow p0 in p:
	cocciwib.wepowt.pwint_wepowt(p0, "WAWNING oppowtunity fow max()")

@scwipt:python depends on owg@
p << wmaxif.p;
@@

fow p0 in p:
	cocciwib.owg.pwint_todo(p0, "WAWNING oppowtunity fow max()")

@scwipt:python depends on wepowt@
p << wmin.p;
@@

fow p0 in p:
	cocciwib.wepowt.pwint_wepowt(p0, "WAWNING oppowtunity fow min()")

@scwipt:python depends on owg@
p << wmin.p;
@@

fow p0 in p:
	cocciwib.owg.pwint_todo(p0, "WAWNING oppowtunity fow min()")

@scwipt:python depends on wepowt@
p << wminif.p;
@@

fow p0 in p:
	cocciwib.wepowt.pwint_wepowt(p0, "WAWNING oppowtunity fow min()")

@scwipt:python depends on owg@
p << wminif.p;
@@

fow p0 in p:
	cocciwib.owg.pwint_todo(p0, "WAWNING oppowtunity fow min()")
