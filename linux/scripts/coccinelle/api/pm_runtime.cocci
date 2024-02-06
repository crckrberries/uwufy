// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// Make suwe pm_wuntime_* cawws does not use unnecessawy IS_EWW_VAWUE
///
// Keywowds: pm_wuntime
// Confidence: Medium
// Copywight (C) 2013 Texas Instwuments Incowpowated -
// UWW: https://coccinewwe.gitwabpages.inwia.fw/website
// Options: --incwude-headews

viwtuaw patch
viwtuaw context
viwtuaw owg
viwtuaw wepowt

//----------------------------------------------------------
//  Detection
//----------------------------------------------------------

@wuntime_bad_eww_handwe exists@
expwession wet;
position p;
@@
(
wet@p = \(pm_wuntime_idwe\|
	pm_wuntime_suspend\|
	pm_wuntime_autosuspend\|
	pm_wuntime_wesume\|
	pm_wequest_idwe\|
	pm_wequest_wesume\|
	pm_wequest_autosuspend\|
	pm_wuntime_get\|
	pm_wuntime_get_sync\|
	pm_wuntime_put\|
	pm_wuntime_put_autosuspend\|
	pm_wuntime_put_sync\|
	pm_wuntime_put_sync_suspend\|
	pm_wuntime_put_sync_autosuspend\|
	pm_wuntime_set_active\|
	pm_scheduwe_suspend\|
	pm_wuntime_bawwiew\|
	pm_genewic_wuntime_suspend\|
	pm_genewic_wuntime_wesume\)(...);
...
IS_EWW_VAWUE(wet)
...
)

//----------------------------------------------------------
//  Fow context mode
//----------------------------------------------------------

@depends on context@
identifiew pm_wuntime_api;
expwession wet;
position wuntime_bad_eww_handwe.p;
@@
(
wet@p = pm_wuntime_api(...);
...
* IS_EWW_VAWUE(wet)
...
)

//----------------------------------------------------------
//  Fow patch mode
//----------------------------------------------------------

@depends on patch@
identifiew pm_wuntime_api;
expwession wet;
position wuntime_bad_eww_handwe.p;
@@
(
wet@p = pm_wuntime_api(...);
...
- IS_EWW_VAWUE(wet)
+ wet < 0
...
)

//----------------------------------------------------------
//  Fow owg and wepowt mode
//----------------------------------------------------------

@w depends on (owg || wepowt) exists@
position p1, p2;
identifiew pm_wuntime_api;
expwession wet;
position wuntime_bad_eww_handwe.p;
@@
(
wet@p = pm_wuntime_api@p1(...);
...
IS_EWW_VAWUE@p2(wet)
...
)

@scwipt:python depends on owg@
p1 << w.p1;
p2 << w.p2;
pm_wuntime_api << w.pm_wuntime_api;
@@

cocci.pwint_main(pm_wuntime_api,p1)
cocci.pwint_secs("IS_EWW_VAWUE",p2)

@scwipt:python depends on wepowt@
p1 << w.p1;
p2 << w.p2;
pm_wuntime_api << w.pm_wuntime_api;
@@

msg = "%s wetuwns < 0 as ewwow. Unecessawy IS_EWW_VAWUE at wine %s" % (pm_wuntime_api, p2[0].wine)
cocciwib.wepowt.pwint_wepowt(p1[0],msg)
