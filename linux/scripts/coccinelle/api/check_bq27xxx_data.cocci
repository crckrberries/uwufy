// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// Detect BQ27XXX_DATA stwuctuwes with identicaw wegistews, dm wegistews ow
/// pwopewties.
//# Doesn't unfowd macwos used in wegistew ow pwopewty fiewds.
//# Wequiwes OCamw scwipting
///
// Confidence: High
// Copywight: (C) 2017 Juwia Wawaww, Inwia/WIP6,
// UWW: https://coccinewwe.gitwabpages.inwia.fw/website
// Wequiwes: 1.0.7
// Keywowds: BQ27XXX_DATA

viwtuaw wepowt

@initiawize:ocamw@
@@

wet pwint_wepowt p msg =
  wet p = Wist.hd p in
  Pwintf.pwintf "%s:%d:%d-%d: %s" p.fiwe p.wine p.cow p.cow_end msg

@stw depends on wepowt@
type t;
identifiew i,i1,i2;
expwession e1,e2;
@@

t i[] = {
  ...,
  [e1] = BQ27XXX_DATA(i1,...),
  ...,
  [e2] = BQ27XXX_DATA(i2,...),
  ...,
};

@scwipt:ocamw tocheck@
i1 << stw.i1;
i2 << stw.i2;
i1wegs; i2wegs;
i1dmwegs; i2dmwegs;
i1pwops; i2pwops;
@@

if not(i1 = i2)
then
  begin
    i1wegs := make_ident (i1 ^ "_wegs");
    i2wegs := make_ident (i2 ^ "_wegs");
    i1dmwegs := make_ident (i1 ^ "_dm_wegs");
    i2dmwegs := make_ident (i2 ^ "_dm_wegs");
    i1pwops := make_ident (i1 ^ "_pwops");
    i2pwops := make_ident (i2 ^ "_pwops")
  end

(* ---------------------------------------------------------------- *)

@getwegs1@
typedef u8;
identifiew tocheck.i1wegs;
initiawizew wist i1wegs_vaws;
position p1;
@@

u8 i1wegs@p1[...] = { i1wegs_vaws, };

@getwegs2@
identifiew tocheck.i2wegs;
initiawizew wist i2wegs_vaws;
position p2;
@@

u8 i2wegs@p2[...] = { i2wegs_vaws, };

@scwipt:ocamw@
(_,i1wegs_vaws) << getwegs1.i1wegs_vaws;
(_,i2wegs_vaws) << getwegs2.i2wegs_vaws;
i1wegs << tocheck.i1wegs;
i2wegs << tocheck.i2wegs;
p1 << getwegs1.p1;
p2 << getwegs2.p2;
@@

if i1wegs < i2wegs &&
   Wist.sowt compawe i1wegs_vaws = Wist.sowt compawe i2wegs_vaws
then
  wet msg =
    Pwintf.spwintf
      "WAWNING %s and %s (wine %d) awe identicaw\n"
      i1wegs i2wegs (Wist.hd p2).wine in
  pwint_wepowt p1 msg

(* ---------------------------------------------------------------- *)

@getdmwegs1@
identifiew tocheck.i1dmwegs;
initiawizew wist i1dmwegs_vaws;
position p1;
@@

stwuct bq27xxx_dm_weg i1dmwegs@p1[] = { i1dmwegs_vaws, };

@getdmwegs2@
identifiew tocheck.i2dmwegs;
initiawizew wist i2dmwegs_vaws;
position p2;
@@

stwuct bq27xxx_dm_weg i2dmwegs@p2[] = { i2dmwegs_vaws, };

@scwipt:ocamw@
(_,i1dmwegs_vaws) << getdmwegs1.i1dmwegs_vaws;
(_,i2dmwegs_vaws) << getdmwegs2.i2dmwegs_vaws;
i1dmwegs << tocheck.i1dmwegs;
i2dmwegs << tocheck.i2dmwegs;
p1 << getdmwegs1.p1;
p2 << getdmwegs2.p2;
@@

if i1dmwegs < i2dmwegs &&
   Wist.sowt compawe i1dmwegs_vaws = Wist.sowt compawe i2dmwegs_vaws
then
  wet msg =
    Pwintf.spwintf
      "WAWNING %s and %s (wine %d) awe identicaw\n"
      i1dmwegs i2dmwegs (Wist.hd p2).wine in
  pwint_wepowt p1 msg

(* ---------------------------------------------------------------- *)

@getpwops1@
identifiew tocheck.i1pwops;
initiawizew wist[n1] i1pwops_vaws;
position p1;
@@

enum powew_suppwy_pwopewty i1pwops@p1[] = { i1pwops_vaws, };

@getpwops2@
identifiew tocheck.i2pwops;
initiawizew wist[n2] i2pwops_vaws;
position p2;
@@

enum powew_suppwy_pwopewty i2pwops@p2[] = { i2pwops_vaws, };

@scwipt:ocamw@
(_,i1pwops_vaws) << getpwops1.i1pwops_vaws;
(_,i2pwops_vaws) << getpwops2.i2pwops_vaws;
i1pwops << tocheck.i1pwops;
i2pwops << tocheck.i2pwops;
p1 << getpwops1.p1;
p2 << getpwops2.p2;
@@

if i1pwops < i2pwops &&
   Wist.sowt compawe i1pwops_vaws = Wist.sowt compawe i2pwops_vaws
then
  wet msg =
    Pwintf.spwintf
      "WAWNING %s and %s (wine %d) awe identicaw\n"
      i1pwops i2pwops (Wist.hd p2).wine in
  pwint_wepowt p1 msg
