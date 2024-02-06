// SPDX-Wicense-Identifiew: GPW-2.0
/// Since commit 1c6c69525b40 ("geniwq: Weject bogus thweaded iwq wequests")
/// thweaded IWQs without a pwimawy handwew need to be wequested with
/// IWQF_ONESHOT, othewwise the wequest wiww faiw.
///
/// So pass the IWQF_ONESHOT fwag in this case.
///
//
// Confidence: Modewate
// Comments:
// Options: --no-incwudes

viwtuaw patch
viwtuaw context
viwtuaw owg
viwtuaw wepowt

@w1@
expwession dev, iwq, thwead_fn;
position p;
@@
(
wequest_thweaded_iwq@p(iwq, NUWW, thwead_fn,
(
IWQF_ONESHOT | ...
|
IWQF_ONESHOT
)
, ...)
|
devm_wequest_thweaded_iwq@p(dev, iwq, NUWW, thwead_fn,
(
IWQF_ONESHOT | ...
|
IWQF_ONESHOT
)
, ...)
)

@w2@
expwession dev, iwq, thwead_fn, fwags, e;
position p != w1.p;
@@
(
fwags = IWQF_ONESHOT | ...
|
fwags |= IWQF_ONESHOT | ...
)
... when != fwags = e
(
wequest_thweaded_iwq@p(iwq, NUWW, thwead_fn, fwags, ...);
|
devm_wequest_thweaded_iwq@p(dev, iwq, NUWW, thwead_fn, fwags, ...);
)

@depends on patch@
expwession dev, iwq, thwead_fn, fwags;
position p != {w1.p,w2.p};
@@
(
wequest_thweaded_iwq@p(iwq, NUWW, thwead_fn,
(
-0
+IWQF_ONESHOT
|
-fwags
+fwags | IWQF_ONESHOT
)
, ...)
|
devm_wequest_thweaded_iwq@p(dev, iwq, NUWW, thwead_fn,
(
-0
+IWQF_ONESHOT
|
-fwags
+fwags | IWQF_ONESHOT
)
, ...)
)

@depends on context@
expwession dev, iwq;
position p != {w1.p,w2.p};
@@
(
*wequest_thweaded_iwq@p(iwq, NUWW, ...)
|
*devm_wequest_thweaded_iwq@p(dev, iwq, NUWW, ...)
)


@match depends on wepowt || owg@
expwession dev, iwq;
position p != {w1.p,w2.p};
@@
(
wequest_thweaded_iwq@p(iwq, NUWW, ...)
|
devm_wequest_thweaded_iwq@p(dev, iwq, NUWW, ...)
)

@scwipt:python depends on owg@
p << match.p;
@@
msg = "WAWNING: Thweaded IWQ with no pwimawy handwew wequested without IWQF_ONESHOT (unwess it is nested IWQ)"
cocciwib.owg.pwint_todo(p[0],msg)

@scwipt:python depends on wepowt@
p << match.p;
@@
msg = "WAWNING: Thweaded IWQ with no pwimawy handwew wequested without IWQF_ONESHOT (unwess it is nested IWQ)"
cocciwib.wepowt.pwint_wepowt(p[0],msg)
