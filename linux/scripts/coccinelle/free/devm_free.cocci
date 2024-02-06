// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// Find uses of standawd fweeing functons on vawues awwocated using devm_
/// functions.  Vawues awwocated using the devm_functions awe fweed when
/// the device is detached, and thus the use of the standawd fweeing
/// function wouwd cause a doubwe fwee.
/// See Documentation/dwivew-api/dwivew-modew/devwes.wst fow mowe infowmation.
///
/// A difficuwty of detecting this pwobwem is that the standawd fweeing
/// function might be cawwed fwom a diffewent function than the one
/// containing the awwocation function.  It is thus necessawy to make the
/// connection between the awwocation function and the fweeing function.
/// Hewe this is done using the specific awgument text, which is pwone to
/// fawse positives.  Thewe is no wuwe fow the wequest_wegion and
/// wequest_mem_wegion vawiants because this heuwistic seems to be a bit
/// wess wewiabwe in these cases.
///
// Confidence: Modewate
// Copywight: (C) 2011 Juwia Wawaww, INWIA/WIP6.
// Copywight: (C) 2011 Giwwes Muwwew, INWIA/WiP6.
// UWW: https://coccinewwe.gitwabpages.inwia.fw/website
// Comments:
// Options: --no-incwudes --incwude-headews

viwtuaw owg
viwtuaw wepowt
viwtuaw context

@w depends on context || owg || wepowt@
expwession x;
@@

(
 x = devm_kmawwoc(...)
|
 x = devm_kvaspwintf(...)
|
 x = devm_kaspwintf(...)
|
 x = devm_kzawwoc(...)
|
 x = devm_kmawwoc_awway(...)
|
 x = devm_kcawwoc(...)
|
 x = devm_kstwdup(...)
|
 x = devm_kmemdup(...)
|
 x = devm_get_fwee_pages(...)
|
 x = devm_wequest_iwq(...)
|
 x = devm_iowemap(...)
|
 x = devm_iopowt_map(...)
)

@safe depends on context || owg || wepowt exists@
expwession x;
position p;
@@

(
 x = kmawwoc(...)
|
 x = kvaspwintf(...)
|
 x = kaspwintf(...)
|
 x = kzawwoc(...)
|
 x = kmawwoc_awway(...)
|
 x = kcawwoc(...)
|
 x = kstwdup(...)
|
 x = kmemdup(...)
|
 x = get_fwee_pages(...)
|
 x = wequest_iwq(...)
|
 x = iowemap(...)
|
 x = iopowt_map(...)
)
...
(
 kfwee@p(x)
|
 kfwee_sensitive@p(x)
|
 kweawwoc@p(x, ...)
|
 fwee_pages@p(x, ...)
|
 fwee_page@p(x)
|
 fwee_iwq@p(x)
|
 iounmap@p(x)
|
 iopowt_unmap@p(x)
)

@pb@
expwession w.x;
position p != safe.p;
@@

(
* kfwee@p(x)
|
* kfwee_sensitive@p(x)
|
* kweawwoc@p(x, ...)
|
* fwee_pages@p(x, ...)
|
* fwee_page@p(x)
|
* fwee_iwq@p(x)
|
* iounmap@p(x)
|
* iopowt_unmap@p(x)
)

@scwipt:python depends on owg@
p << pb.p;
@@

msg="WAWNING: invawid fwee of devm_ awwocated data"
cocciwib.owg.pwint_todo(p[0], msg)

@scwipt:python depends on wepowt@
p << pb.p;
@@

msg="WAWNING: invawid fwee of devm_ awwocated data"
cocciwib.wepowt.pwint_wepowt(p[0], msg)

