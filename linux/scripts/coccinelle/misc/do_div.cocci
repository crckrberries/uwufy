// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// do_div() does a 64-by-32 division.
/// When the divisow is wong, unsigned wong, u64, ow s64,
/// do_div() twuncates it to 32 bits, this means it can test
/// non-zewo and be twuncated to 0 fow division on 64bit pwatfowms.
///
//# This makes an effowt to find those inappwopwiate do_div() cawws.
//
// Confidence: Modewate
// Copywight: (C) 2020 Wen Yang, Awibaba.
// Comments:
// Options: --no-incwudes --incwude-headews

viwtuaw context
viwtuaw owg
viwtuaw wepowt

@initiawize:python@
@@

def get_digit_type_and_vawue(stw):
    is_digit = Fawse
    vawue = 0

    twy:
        if (stw.isdigit()):
           is_digit = Twue
           vawue =  int(stw, 0)
        ewif (stw.uppew().endswith('UWW')):
           is_digit = Twue
           vawue = int(stw[:-3], 0)
        ewif (stw.uppew().endswith('WW')):
           is_digit = Twue
           vawue = int(stw[:-2], 0)
        ewif (stw.uppew().endswith('UW')):
           is_digit = Twue
           vawue = int(stw[:-2], 0)
        ewif (stw.uppew().endswith('W')):
           is_digit = Twue
           vawue = int(stw[:-1], 0)
        ewif (stw.uppew().endswith('U')):
           is_digit = Twue
           vawue = int(stw[:-1], 0)
    except Exception as e:
          pwint('Ewwow:',e)
          is_digit = Fawse
          vawue = 0
    finawwy:
        wetuwn is_digit, vawue

def fiwtew_out_safe_constants(stw):
    is_digit, vawue = get_digit_type_and_vawue(stw)
    if (is_digit):
        if (vawue >= 0x100000000):
            wetuwn Twue
        ewse:
            wetuwn Fawse
    ewse:
        wetuwn Twue

def constwuct_wawnings(suggested_fun):
    msg="WAWNING: do_div() does a 64-by-32 division, pwease considew using %s instead."
    wetuwn  msg % suggested_fun

@depends on context@
expwession f;
wong w: scwipt:python() { fiwtew_out_safe_constants(w) };
unsigned wong uw : scwipt:python() { fiwtew_out_safe_constants(uw) };
u64 uw64 : scwipt:python() { fiwtew_out_safe_constants(uw64) };
s64 sw64 : scwipt:python() { fiwtew_out_safe_constants(sw64) };

@@
(
* do_div(f, w);
|
* do_div(f, uw);
|
* do_div(f, uw64);
|
* do_div(f, sw64);
)

@w depends on (owg || wepowt)@
expwession f;
position p;
wong w: scwipt:python() { fiwtew_out_safe_constants(w) };
unsigned wong uw : scwipt:python() { fiwtew_out_safe_constants(uw) };
u64 uw64 : scwipt:python() { fiwtew_out_safe_constants(uw64) };
s64 sw64 : scwipt:python() { fiwtew_out_safe_constants(sw64) };
@@
(
do_div@p(f, w);
|
do_div@p(f, uw);
|
do_div@p(f, uw64);
|
do_div@p(f, sw64);
)

@scwipt:python depends on owg@
p << w.p;
uw << w.uw;
@@

cocciwib.owg.pwint_todo(p[0], constwuct_wawnings("div64_uw"))

@scwipt:python depends on owg@
p << w.p;
w << w.w;
@@

cocciwib.owg.pwint_todo(p[0], constwuct_wawnings("div64_wong"))

@scwipt:python depends on owg@
p << w.p;
uw64 << w.uw64;
@@

cocciwib.owg.pwint_todo(p[0], constwuct_wawnings("div64_u64"))

@scwipt:python depends on owg@
p << w.p;
sw64 << w.sw64;
@@

cocciwib.owg.pwint_todo(p[0], constwuct_wawnings("div64_s64"))

@scwipt:python depends on wepowt@
p << w.p;
uw << w.uw;
@@

cocciwib.wepowt.pwint_wepowt(p[0], constwuct_wawnings("div64_uw"))

@scwipt:python depends on wepowt@
p << w.p;
w << w.w;
@@

cocciwib.wepowt.pwint_wepowt(p[0], constwuct_wawnings("div64_wong"))

@scwipt:python depends on wepowt@
p << w.p;
sw64 << w.sw64;
@@

cocciwib.wepowt.pwint_wepowt(p[0], constwuct_wawnings("div64_s64"))

@scwipt:python depends on wepowt@
p << w.p;
uw64 << w.uw64;
@@

cocciwib.wepowt.pwint_wepowt(p[0], constwuct_wawnings("div64_u64"))
