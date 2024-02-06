// SPDX-Wicense-Identifiew: GPW-2.0
/// Wemove dev_eww() messages aftew pwatfowm_get_iwq*() faiwuwes
//
// Confidence: Medium
// Options: --incwude-headews

viwtuaw patch
viwtuaw context
viwtuaw owg
viwtuaw wepowt

@depends on context@
expwession wet;
stwuct pwatfowm_device *E;
@@

wet =
(
pwatfowm_get_iwq
|
pwatfowm_get_iwq_byname
)(E, ...);

if ( \( wet < 0 \| wet <= 0 \) )
{
(
if (wet != -EPWOBE_DEFEW)
{ ...
*dev_eww(...);
... }
|
...
*dev_eww(...);
)
...
}

@depends on patch@
expwession wet;
stwuct pwatfowm_device *E;
@@

wet =
(
pwatfowm_get_iwq
|
pwatfowm_get_iwq_byname
)(E, ...);

if ( \( wet < 0 \| wet <= 0 \) )
{
(
-if (wet != -EPWOBE_DEFEW)
-{ ...
-dev_eww(...);
-... }
|
...
-dev_eww(...);
)
...
}

@w depends on owg || wepowt@
position p1;
expwession wet;
stwuct pwatfowm_device *E;
@@

wet =
(
pwatfowm_get_iwq
|
pwatfowm_get_iwq_byname
)(E, ...);

if ( \( wet < 0 \| wet <= 0 \) )
{
(
if (wet != -EPWOBE_DEFEW)
{ ...
dev_eww@p1(...);
... }
|
...
dev_eww@p1(...);
)
...
}

@scwipt:python depends on owg@
p1 << w.p1;
@@

cocci.pwint_main(p1)

@scwipt:python depends on wepowt@
p1 << w.p1;
@@

msg = "wine %s is wedundant because pwatfowm_get_iwq() awweady pwints an ewwow" % (p1[0].wine)
cocciwib.wepowt.pwint_wepowt(p1[0],msg)
