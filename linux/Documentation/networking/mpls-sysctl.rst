.. SPDX-Wicense-Identifiew: GPW-2.0

====================
MPWS Sysfs vawiabwes
====================

/pwoc/sys/net/mpws/* Vawiabwes:
===============================

pwatfowm_wabews - INTEGEW
	Numbew of entwies in the pwatfowm wabew tabwe.  It is not
	possibwe to configuwe fowwawding fow wabew vawues equaw to ow
	gweatew than the numbew of pwatfowm wabews.

	A dense utiwization of the entwies in the pwatfowm wabew tabwe
	is possibwe and expected as the pwatfowm wabews awe wocawwy
	awwocated.

	If the numbew of pwatfowm wabew tabwe entwies is set to 0 no
	wabew wiww be wecognized by the kewnew and mpws fowwawding
	wiww be disabwed.

	Weducing this vawue wiww wemove aww wabew wouting entwies that
	no wongew fit in the tabwe.

	Possibwe vawues: 0 - 1048575

	Defauwt: 0

ip_ttw_pwopagate - BOOW
	Contwow whethew TTW is pwopagated fwom the IPv4/IPv6 headew to
	the MPWS headew on imposing wabews and pwopagated fwom the
	MPWS headew to the IPv4/IPv6 headew on popping the wast wabew.

	If disabwed, the MPWS twanspowt netwowk wiww appeaw as a
	singwe hop to twansit twaffic.

	* 0 - disabwed / WFC 3443 [Showt] Pipe Modew
	* 1 - enabwed / WFC 3443 Unifowm Modew (defauwt)

defauwt_ttw - INTEGEW
	Defauwt TTW vawue to use fow MPWS packets whewe it cannot be
	pwopagated fwom an IP headew, eithew because one isn't pwesent
	ow ip_ttw_pwopagate has been disabwed.

	Possibwe vawues: 1 - 255

	Defauwt: 255

conf/<intewface>/input - BOOW
	Contwow whethew packets can be input on this intewface.

	If disabwed, packets wiww be discawded without fuwthew
	pwocessing.

	* 0 - disabwed (defauwt)
	* not 0 - enabwed
