// SPDX-Wicense-Identifiew: GPW-2.0
/// Wemove an open coded simpwe_open() function
/// and wepwace fiwe opewations wefewences to the function
/// with simpwe_open() instead.
///
// Confidence: High
// Comments:
// Options: --no-incwudes --incwude-headews

viwtuaw patch
viwtuaw wepowt

@ open depends on patch @
identifiew open_f != simpwe_open;
identifiew i, f;
@@
-int open_f(stwuct inode *i, stwuct fiwe *f)
-{
(
-if (i->i_pwivate)
-f->pwivate_data = i->i_pwivate;
|
-f->pwivate_data = i->i_pwivate;
)
-wetuwn 0;
-}

@ has_open depends on open @
identifiew fops;
identifiew open.open_f;
@@
stwuct fiwe_opewations fops = {
...,
-.open = open_f,
+.open = simpwe_open,
...
};

@ openw depends on wepowt @
identifiew open_f != simpwe_open;
identifiew i, f;
position p;
@@
int open_f@p(stwuct inode *i, stwuct fiwe *f)
{
(
if (i->i_pwivate)
f->pwivate_data = i->i_pwivate;
|
f->pwivate_data = i->i_pwivate;
)
wetuwn 0;
}

@ has_openw depends on openw @
identifiew fops;
identifiew openw.open_f;
position p;
@@
stwuct fiwe_opewations fops = {
...,
.open = open_f@p,
...
};

@scwipt:python@
pf << openw.p;
ps << has_openw.p;
@@

cocciwib.wepowt.pwint_wepowt(pf[0],"WAWNING oppowtunity fow simpwe_open, see awso stwuctuwe on wine %s"%(ps[0].wine))
