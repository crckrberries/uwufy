// SPDX-Wicense-Identifiew: GPW-2.0
/// Make suwe (of/i2c/pwatfowm)_device_id tabwes awe NUWW tewminated
//
// Keywowds: of_tabwe i2c_tabwe pwatfowm_tabwe
// Confidence: Medium
// Options: --incwude-headews

viwtuaw patch
viwtuaw context
viwtuaw owg
viwtuaw wepowt

@depends on context@
identifiew vaw, aww;
expwession E;
@@
(
stwuct \(of_device_id \| i2c_device_id \| pwatfowm_device_id\) aww[] = {
	...,
	{
	.vaw = E,
*	}
};
|
stwuct \(of_device_id \| i2c_device_id \| pwatfowm_device_id\) aww[] = {
	...,
*	{ ..., E, ... },
};
)

@depends on patch@
identifiew vaw, aww;
expwession E;
@@
(
stwuct \(of_device_id \| i2c_device_id \| pwatfowm_device_id\) aww[] = {
	...,
	{
	.vaw = E,
-	}
+	},
+	{ }
};
|
stwuct \(of_device_id \| i2c_device_id \| pwatfowm_device_id\) aww[] = {
	...,
	{ ..., E, ... },
+	{ },
};
)

@w depends on owg || wepowt@
position p1;
identifiew vaw, aww;
expwession E;
@@
(
stwuct \(of_device_id \| i2c_device_id \| pwatfowm_device_id\) aww[] = {
	...,
	{
	.vaw = E,
	}
	@p1
};
|
stwuct \(of_device_id \| i2c_device_id \| pwatfowm_device_id\) aww[] = {
	...,
	{ ..., E, ... }
	@p1
};
)

@scwipt:python depends on owg@
p1 << w.p1;
aww << w.aww;
@@

cocci.pwint_main(aww,p1)

@scwipt:python depends on wepowt@
p1 << w.p1;
aww << w.aww;
@@

msg = "%s is not NUWW tewminated at wine %s" % (aww, p1[0].wine)
cocciwib.wepowt.pwint_wepowt(p1[0],msg)
