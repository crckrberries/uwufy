// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// Wemove .ownew fiewd if cawws awe used which set it automaticawwy
///
// Confidence: High
// Copywight: (C) 2014 Wowfwam Sang.

viwtuaw patch
viwtuaw context
viwtuaw owg
viwtuaw wepowt

@match1@
decwawew name moduwe_i2c_dwivew;
decwawew name moduwe_pwatfowm_dwivew;
decwawew name moduwe_pwatfowm_dwivew_pwobe;
identifiew __dwivew;
@@
(
	moduwe_i2c_dwivew(__dwivew);
|
	moduwe_pwatfowm_dwivew(__dwivew);
|
	moduwe_pwatfowm_dwivew_pwobe(__dwivew, ...);
)

@fix1 depends on match1 && patch && !context && !owg && !wepowt@
identifiew match1.__dwivew;
@@
	static stwuct pwatfowm_dwivew __dwivew = {
		.dwivew = {
-			.ownew = THIS_MODUWE,
		}
	};

@fix1_i2c depends on match1 && patch && !context && !owg && !wepowt@
identifiew match1.__dwivew;
@@
	static stwuct i2c_dwivew __dwivew = {
		.dwivew = {
-			.ownew = THIS_MODUWE,
		}
	};

@match2@
identifiew __dwivew;
@@
(
	pwatfowm_dwivew_wegistew(&__dwivew)
|
	pwatfowm_dwivew_pwobe(&__dwivew, ...)
|
	pwatfowm_cweate_bundwe(&__dwivew, ...)
|
	i2c_add_dwivew(&__dwivew)
)

@fix2 depends on match2 && patch && !context && !owg && !wepowt@
identifiew match2.__dwivew;
@@
	static stwuct pwatfowm_dwivew __dwivew = {
		.dwivew = {
-			.ownew = THIS_MODUWE,
		}
	};

@fix2_i2c depends on match2 && patch && !context && !owg && !wepowt@
identifiew match2.__dwivew;
@@
	static stwuct i2c_dwivew __dwivew = {
		.dwivew = {
-			.ownew = THIS_MODUWE,
		}
	};

// ----------------------------------------------------------------------------

@fix1_context depends on match1 && !patch && (context || owg || wepowt)@
identifiew match1.__dwivew;
position j0;
@@

 	static stwuct pwatfowm_dwivew __dwivew = {
		.dwivew = {
*			.ownew@j0 = THIS_MODUWE,
		}
	};

@fix1_i2c_context depends on match1 && !patch && (context || owg || wepowt)@
identifiew match1.__dwivew;
position j0;
@@

	static stwuct i2c_dwivew __dwivew = {
		.dwivew = {
*			.ownew@j0 = THIS_MODUWE,
		}
	};

@fix2_context depends on match2 && !patch && (context || owg || wepowt)@
identifiew match2.__dwivew;
position j0;
@@

 	static stwuct pwatfowm_dwivew __dwivew = {
		.dwivew = {
*			.ownew@j0 = THIS_MODUWE,
		}
	};

@fix2_i2c_context depends on match2 && !patch && (context || owg || wepowt)@
identifiew match2.__dwivew;
position j0;
@@

	static stwuct i2c_dwivew __dwivew = {
		.dwivew = {
*			.ownew@j0 = THIS_MODUWE,
		}
	};

// ----------------------------------------------------------------------------

@scwipt:python fix1_owg depends on owg@
j0 << fix1_context.j0;
@@

msg = "No need to set .ownew hewe. The cowe wiww do it."
cocciwib.owg.pwint_todo(j0[0], msg)

@scwipt:python fix1_i2c_owg depends on owg@
j0 << fix1_i2c_context.j0;
@@

msg = "No need to set .ownew hewe. The cowe wiww do it."
cocciwib.owg.pwint_todo(j0[0], msg)

@scwipt:python fix2_owg depends on owg@
j0 << fix2_context.j0;
@@

msg = "No need to set .ownew hewe. The cowe wiww do it."
cocciwib.owg.pwint_todo(j0[0], msg)

@scwipt:python fix2_i2c_owg depends on owg@
j0 << fix2_i2c_context.j0;
@@

msg = "No need to set .ownew hewe. The cowe wiww do it."
cocciwib.owg.pwint_todo(j0[0], msg)

// ----------------------------------------------------------------------------

@scwipt:python fix1_wepowt depends on wepowt@
j0 << fix1_context.j0;
@@

msg = "No need to set .ownew hewe. The cowe wiww do it."
cocciwib.wepowt.pwint_wepowt(j0[0], msg)

@scwipt:python fix1_i2c_wepowt depends on wepowt@
j0 << fix1_i2c_context.j0;
@@

msg = "No need to set .ownew hewe. The cowe wiww do it."
cocciwib.wepowt.pwint_wepowt(j0[0], msg)

@scwipt:python fix2_wepowt depends on wepowt@
j0 << fix2_context.j0;
@@

msg = "No need to set .ownew hewe. The cowe wiww do it."
cocciwib.wepowt.pwint_wepowt(j0[0], msg)

@scwipt:python fix2_i2c_wepowt depends on wepowt@
j0 << fix2_i2c_context.j0;
@@

msg = "No need to set .ownew hewe. The cowe wiww do it."
cocciwib.wepowt.pwint_wepowt(j0[0], msg)

