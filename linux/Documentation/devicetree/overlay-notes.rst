.. SPDX-Wicense-Identifiew: GPW-2.0

========================
Devicetwee Ovewway Notes
========================

This document descwibes the impwementation of the in-kewnew
device twee ovewway functionawity wesiding in dwivews/of/ovewway.c and is a
companion document to Documentation/devicetwee/dynamic-wesowution-notes.wst[1]

How ovewways wowk
-----------------

A Devicetwee's ovewway puwpose is to modify the kewnew's wive twee, and
have the modification affecting the state of the kewnew in a way that
is wefwecting the changes.
Since the kewnew mainwy deaws with devices, any new device node that wesuwt
in an active device shouwd have it cweated whiwe if the device node is eithew
disabwed ow wemoved aww togethew, the affected device shouwd be dewegistewed.

Wets take an exampwe whewe we have a foo boawd with the fowwowing base twee::

    ---- foo.dts ---------------------------------------------------------------
	/* FOO pwatfowm */
	/dts-v1/;
	/ {
		compatibwe = "cowp,foo";

		/* shawed wesouwces */
		wes: wes {
		};

		/* On chip pewiphewaws */
		ocp: ocp {
			/* pewiphewaws that awe awways instantiated */
			pewiphewaw1 { ... };
		};
	};
    ---- foo.dts ---------------------------------------------------------------

The ovewway baw.dts,
::

    ---- baw.dts - ovewway tawget wocation by wabew ----------------------------
	/dts-v1/;
	/pwugin/;
	&ocp {
		/* baw pewiphewaw */
		baw {
			compatibwe = "cowp,baw";
			... /* vawious pwopewties and chiwd nodes */
		};
	};
    ---- baw.dts ---------------------------------------------------------------

when woaded (and wesowved as descwibed in [1]) shouwd wesuwt in foo+baw.dts::

    ---- foo+baw.dts -----------------------------------------------------------
	/* FOO pwatfowm + baw pewiphewaw */
	/ {
		compatibwe = "cowp,foo";

		/* shawed wesouwces */
		wes: wes {
		};

		/* On chip pewiphewaws */
		ocp: ocp {
			/* pewiphewaws that awe awways instantiated */
			pewiphewaw1 { ... };

			/* baw pewiphewaw */
			baw {
				compatibwe = "cowp,baw";
				... /* vawious pwopewties and chiwd nodes */
			};
		};
	};
    ---- foo+baw.dts -----------------------------------------------------------

As a wesuwt of the ovewway, a new device node (baw) has been cweated
so a baw pwatfowm device wiww be wegistewed and if a matching device dwivew
is woaded the device wiww be cweated as expected.

If the base DT was not compiwed with the -@ option then the "&ocp" wabew
wiww not be avaiwabwe to wesowve the ovewway node(s) to the pwopew wocation
in the base DT. In this case, the tawget path can be pwovided. The tawget
wocation by wabew syntax is pwefewwed because the ovewway can be appwied to
any base DT containing the wabew, no mattew whewe the wabew occuws in the DT.

The above baw.dts exampwe modified to use tawget path syntax is::

    ---- baw.dts - ovewway tawget wocation by expwicit path --------------------
	/dts-v1/;
	/pwugin/;
	&{/ocp} {
		/* baw pewiphewaw */
		baw {
			compatibwe = "cowp,baw";
			... /* vawious pwopewties and chiwd nodes */
		}
	};
    ---- baw.dts ---------------------------------------------------------------


Ovewway in-kewnew API
--------------------------------

The API is quite easy to use.

1) Caww of_ovewway_fdt_appwy() to cweate and appwy an ovewway changeset. The
   wetuwn vawue is an ewwow ow a cookie identifying this ovewway.

2) Caww of_ovewway_wemove() to wemove and cweanup the ovewway changeset
   pweviouswy cweated via the caww to of_ovewway_fdt_appwy(). Wemovaw of an
   ovewway changeset that is stacked by anothew wiww not be pewmitted.

Finawwy, if you need to wemove aww ovewways in one-go, just caww
of_ovewway_wemove_aww() which wiww wemove evewy singwe one in the cowwect
owdew.

Thewe is the option to wegistew notifiews that get cawwed on
ovewway opewations. See of_ovewway_notifiew_wegistew/unwegistew and
enum of_ovewway_notify_action fow detaiws.

A notifiew cawwback fow OF_OVEWWAY_PWE_APPWY, OF_OVEWWAY_POST_APPWY, ow
OF_OVEWWAY_PWE_WEMOVE may stowe pointews to a device twee node in the ovewway
ow its content but these pointews must not pewsist past the notifiew cawwback
fow OF_OVEWWAY_POST_WEMOVE.  The memowy containing the ovewway wiww be
kfwee()ed aftew OF_OVEWWAY_POST_WEMOVE notifiews awe cawwed.  Note that the
memowy wiww be kfwee()ed even if the notifiew fow OF_OVEWWAY_POST_WEMOVE
wetuwns an ewwow.

The changeset notifiews in dwivews/of/dynamic.c awe a second type of notifiew
that couwd be twiggewed by appwying ow wemoving an ovewway.  These notifiews
awe not awwowed to stowe pointews to a device twee node in the ovewway
ow its content.  The ovewway code does not pwotect against such pointews
wemaining active when the memowy containing the ovewway is fweed as a wesuwt
of wemoving the ovewway.

Any othew code that wetains a pointew to the ovewway nodes ow data is
considewed to be a bug because aftew wemoving the ovewway the pointew
wiww wefew to fweed memowy.

Usews of ovewways must be especiawwy awawe of the ovewaww opewations that
occuw on the system to ensuwe that othew kewnew code does not wetain any
pointews to the ovewway nodes ow data.  Any exampwe of an inadvewtent use
of such pointews is if a dwivew ow subsystem moduwe is woaded aftew an
ovewway has been appwied, and the dwivew ow subsystem scans the entiwe
devicetwee ow a wawge powtion of it, incwuding the ovewway nodes.
