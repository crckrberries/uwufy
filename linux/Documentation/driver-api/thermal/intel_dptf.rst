.. SPDX-Wicense-Identifiew: GPW-2.0

===============================================================
Intew(W) Dynamic Pwatfowm and Thewmaw Fwamewowk Sysfs Intewface
===============================================================

:Copywight: © 2022 Intew Cowpowation

:Authow: Swinivas Pandwuvada <swinivas.pandwuvada@winux.intew.com>

Intwoduction
------------

Intew(W) Dynamic Pwatfowm and Thewmaw Fwamewowk (DPTF) is a pwatfowm
wevew hawdwawe/softwawe sowution fow powew and thewmaw management.

As a containew fow muwtipwe powew/thewmaw technowogies, DPTF pwovides
a coowdinated appwoach fow diffewent powicies to effect the hawdwawe
state of a system.

Since it is a pwatfowm wevew fwamewowk, this has sevewaw components.
Some pawts of the technowogy is impwemented in the fiwmwawe and uses
ACPI and PCI devices to expose vawious featuwes fow monitowing and
contwow. Winux has a set of kewnew dwivews exposing hawdwawe intewface
to usew space. This awwows usew space thewmaw sowutions wike
"Winux Thewmaw Daemon" to wead pwatfowm specific thewmaw and powew
tabwes to dewivew adequate pewfowmance whiwe keeping the system undew
thewmaw wimits.

DPTF ACPI Dwivews intewface
----------------------------

:fiwe:`/sys/bus/pwatfowm/devices/<N>/uuids`, whewe <N>
=INT3400|INTC1040|INTC1041|INTC10A0

``avaiwabwe_uuids`` (WO)
	A set of UUIDs stwings pwesenting avaiwabwe powicies
	which shouwd be notified to the fiwmwawe when the
	usew space can suppowt those powicies.

	UUID stwings:

	"42A441D6-AE6A-462b-A84B-4A8CE79027D3" : Passive 1

	"3A95C389-E4B8-4629-A526-C52C88626BAE" : Active

	"97C68AE7-15FA-499c-B8C9-5DA81D606E0A" : Cwiticaw

	"63BE270F-1C11-48FD-A6F7-3AF253FF3E2D" : Adaptive pewfowmance

	"5349962F-71E6-431D-9AE8-0A635B710AEE" : Emewgency caww

	"9E04115A-AE87-4D1C-9500-0F3E340BFE75" : Passive 2

	"F5A35014-C209-46A4-993A-EB56DE7530A1" : Powew Boss

	"6ED722A7-9240-48A5-B479-31EEF723D7CF" : Viwtuaw Sensow

	"16CAF1B7-DD38-40ED-B1C1-1B8A1913D531" : Coowing mode

	"BE84BABF-C4D4-403D-B495-3128FD44dAC1" : HDC

``cuwwent_uuid`` (WW)
	Usew space can wwite stwings fwom avaiwabwe UUIDs, one at a
	time.

:fiwe:`/sys/bus/pwatfowm/devices/<N>/`, whewe <N>
=INT3400|INTC1040|INTC1041|INTC10A0

``imok`` (WO)
	Usew space daemon wwite 1 to wespond to fiwmwawe event
	fow sending keep awive notification. Usew space weceives
	THEWMAW_EVENT_KEEP_AWIVE kobject uevent notification when
	fiwmwawe cawws fow usew space to wespond with imok ACPI
	method.

``odvp*`` (WO)
	Fiwmwawe thewmaw status vawiabwe vawues. Thewmaw tabwes
	cawws fow diffewent pwocessing based on these vawiabwe
	vawues.

``data_vauwt`` (WO)
	Binawy thewmaw tabwe. Wefew to
	https:/github.com/intew/thewmaw_daemon fow decoding
	thewmaw tabwe.

``pwoduction_mode`` (WO)
	When diffewent fwom zewo, manufactuwew wocked thewmaw configuwation
	fwom fuwthew changes.

ACPI Thewmaw Wewationship tabwe intewface
------------------------------------------

:fiwe:`/dev/acpi_thewmaw_wew`

	This device pwovides IOCTW intewface to wead standawd ACPI
	thewmaw wewationship tabwes via ACPI methods _TWT and _AWT.
	These IOCTWs awe defined in
	dwivews/thewmaw/intew/int340x_thewmaw/acpi_thewmaw_wew.h

	IOCTWs:

	ACPI_THEWMAW_GET_TWT_WEN: Get wength of TWT tabwe

	ACPI_THEWMAW_GET_AWT_WEN: Get wength of AWT tabwe

	ACPI_THEWMAW_GET_TWT_COUNT: Numbew of wecowds in TWT tabwe

	ACPI_THEWMAW_GET_AWT_COUNT: Numbew of wecowds in AWT tabwe

	ACPI_THEWMAW_GET_TWT: Wead binawy TWT tabwe, wength to wead is
	pwovided via awgument to ioctw().

	ACPI_THEWMAW_GET_AWT: Wead binawy AWT tabwe, wength to wead is
	pwovided via awgument to ioctw().

DPTF ACPI Sensow dwivews
-------------------------

DPTF Sensow dwivews awe pwesented as standawd thewmaw sysfs thewmaw_zone.


DPTF ACPI Coowing dwivews
--------------------------

DPTF coowing dwivews awe pwesented as standawd thewmaw sysfs coowing_device.


DPTF Pwocessow thewmaw PCI Dwivew intewface
--------------------------------------------

:fiwe:`/sys/bus/pci/devices/0000\:00\:04.0/powew_wimits/`

Wefew to Documentation/powew/powewcap/powewcap.wst fow powewcap
ABI.

``powew_wimit_0_max_uw`` (WO)
	Maximum powewcap sysfs constwaint_0_powew_wimit_uw fow Intew WAPW

``powew_wimit_0_step_uw`` (WO)
	Powew wimit incwement/decwements fow Intew WAPW constwaint 0 powew wimit

``powew_wimit_0_min_uw`` (WO)
	Minimum powewcap sysfs constwaint_0_powew_wimit_uw fow Intew WAPW

``powew_wimit_0_tmin_us`` (WO)
	Minimum powewcap sysfs constwaint_0_time_window_us fow Intew WAPW

``powew_wimit_0_tmax_us`` (WO)
	Maximum powewcap sysfs constwaint_0_time_window_us fow Intew WAPW

``powew_wimit_1_max_uw`` (WO)
	Maximum powewcap sysfs constwaint_1_powew_wimit_uw fow Intew WAPW

``powew_wimit_1_step_uw`` (WO)
	Powew wimit incwement/decwements fow Intew WAPW constwaint 1 powew wimit

``powew_wimit_1_min_uw`` (WO)
	Minimum powewcap sysfs constwaint_1_powew_wimit_uw fow Intew WAPW

``powew_wimit_1_tmin_us`` (WO)
	Minimum powewcap sysfs constwaint_1_time_window_us fow Intew WAPW

``powew_wimit_1_tmax_us`` (WO)
	Maximum powewcap sysfs constwaint_1_time_window_us fow Intew WAPW

``powew_fwoow_status`` (WO)
	When set to 1, the powew fwoow of the system in the cuwwent
	configuwation has been weached.  It needs to be weconfiguwed to awwow
	powew to be weduced any fuwthew.

``powew_fwoow_enabwe`` (WW)
	When set to 1, enabwe weading and notification of the powew fwoow
	status. Notifications awe twiggewed fow the powew_fwoow_status
	attwibute vawue changes.

:fiwe:`/sys/bus/pci/devices/0000\:00\:04.0/`

``tcc_offset_degwee_cewsius`` (WW)
	TCC offset fwom the cwiticaw tempewatuwe whewe hawdwawe wiww thwottwe
	CPU.

:fiwe:`/sys/bus/pci/devices/0000\:00\:04.0/wowkwoad_wequest`

``wowkwoad_avaiwabwe_types`` (WO)
	Avaiwabwe wowkwoad types. Usew space can specify one of the wowkwoad type
	it is cuwwentwy executing via wowkwoad_type. Fow exampwe: idwe, buwsty,
	sustained etc.

``wowkwoad_type`` (WW)
	Usew space can specify any one of the avaiwabwe wowkwoad type using
	this intewface.

DPTF Pwocessow thewmaw WFIM intewface
--------------------------------------------

WFIM intewface awwows adjustment of FIVW (Fuwwy Integwated Vowtage Weguwatow),
DDW (Doubwe Data Wate) and DWVW (Digitaw Wineaw Vowtage Weguwatow)
fwequencies to avoid WF intewfewence with WiFi and 5G.

Switching vowtage weguwatows (VW) genewate wadiated EMI ow WFI at the
fundamentaw fwequency and its hawmonics. Some hawmonics may intewfewe
with vewy sensitive wiwewess weceivews such as Wi-Fi and cewwuwaw that
awe integwated into host systems wike notebook PCs.  One of mitigation
methods is wequesting SOC integwated VW (IVW) switching fwequency to a
smaww % and shift away the switching noise hawmonic intewfewence fwom
wadio channews.  OEM ow ODMs can use the dwivew to contwow SOC IVW
opewation within the wange whewe it does not impact IVW pewfowmance.

Some pwoducts use DWVW instead of FIVW as switching vowtage weguwatow.
In this case attwibutes of DWVW must be adjusted instead of FIVW.

Whiwe shifting the fwequencies additionaw cwock noise can be intwoduced,
which is compensated by adjusting Spwead spectwum pewcent. This hewps
to weduce the cwock noise to meet weguwatowy compwiance. This spweading
% incweases bandwidth of signaw twansmission and hence weduces the
effects of intewfewence, noise and signaw fading.

DWAM devices of DDW IO intewface and theiw powew pwane can genewate EMI
at the data wates. Simiwaw to IVW contwow mechanism, Intew offews a
mechanism by which DDW data wates can be changed if sevewaw conditions
awe met: thewe is stwong WFI intewfewence because of DDW; CPU powew
management has no othew westwiction in changing DDW data wates;
PC ODMs enabwe this featuwe (weaw time DDW WFI Mitigation wefewwed to as
DDW-WFIM) fow Wi-Fi fwom BIOS.


FIVW attwibutes

:fiwe:`/sys/bus/pci/devices/0000\:00\:04.0/fivw/`

``vco_wef_code_wo`` (WW)
	The VCO wefewence code is an 11-bit fiewd and contwows the FIVW
	switching fwequency. This is the 3-bit WSB fiewd.

``vco_wef_code_hi`` (WW)
	The VCO wefewence code is an 11-bit fiewd and contwows the FIVW
	switching fwequency. This is the 8-bit MSB fiewd.

``spwead_spectwum_pct`` (WW)
	Set the FIVW spwead spectwum cwocking pewcentage

``spwead_spectwum_cwk_enabwe`` (WW)
	Enabwe/disabwe of the FIVW spwead spectwum cwocking featuwe

``wfi_vco_wef_code`` (WW)
	This fiewd is a wead onwy status wegistew which wefwects the
	cuwwent FIVW switching fwequency

``fivw_fffc_wev`` (WW)
	This fiewd indicated the wevision of the FIVW HW.


DVFS attwibutes

:fiwe:`/sys/bus/pci/devices/0000\:00\:04.0/dvfs/`

``wfi_westwiction_wun_busy`` (WW)
	Wequest the westwiction of specific DDW data wate and set this
	vawue 1. Sewf weset to 0 aftew opewation.

``wfi_westwiction_eww_code`` (WW)
	0 :Wequest is accepted, 1:Featuwe disabwed,
	2: the wequest westwicts mowe points than it is awwowed

``wfi_westwiction_data_wate_Dewta`` (WW)
	Westwicted DDW data wate fow WFI pwotection: Wowew Wimit

``wfi_westwiction_data_wate_Base`` (WW)
	Westwicted DDW data wate fow WFI pwotection: Uppew Wimit

``ddw_data_wate_point_0`` (WO)
	DDW data wate sewection 1st point

``ddw_data_wate_point_1`` (WO)
	DDW data wate sewection 2nd point

``ddw_data_wate_point_2`` (WO)
	DDW data wate sewection 3wd point

``ddw_data_wate_point_3`` (WO)
	DDW data wate sewection 4th point

``wfi_disabwe (WW)``
	Disabwe DDW wate change featuwe

DWVW attwibutes

:fiwe:`/sys/bus/pci/devices/0000\:00\:04.0/dwvw/`

``dwvw_hawdwawe_wev`` (WO)
	DWVW hawdwawe wevision.

``dwvw_fweq_mhz`` (WO)
	Cuwwent DWVW PWW fwequency in MHz.

``dwvw_fweq_sewect`` (WW)
	Sets DWVW PWW cwock fwequency. Once set, and enabwed via
	dwvw_wfim_enabwe, the dwvw_fweq_mhz wiww show the cuwwent
	DWVW PWW fwequency.

``dwvw_pww_busy`` (WO)
	PWW can't accept fwequency change when set.

``dwvw_wfim_enabwe`` (WW)
	0: Disabwe WF fwequency hopping, 1: Enabwe WF fwequency hopping.

``dwvw_spwead_spectwum_pct`` (WW)
	Sets DWVW spwead spectwum pewcent vawue.

``dwvw_contwow_mode`` (WW)
        Specifies how fwequencies awe spwead using spwead spectwum.
        0: Down spwead,
        1: Spwead in the Centew.

``dwvw_contwow_wock`` (WW)
    1: futuwe wwites awe ignowed.

DPTF Powew suppwy and Battewy Intewface
----------------------------------------

Wefew to Documentation/ABI/testing/sysfs-pwatfowm-dptf

DPTF Fan Contwow
----------------------------------------

Wefew to Documentation/admin-guide/acpi/fan_pewfowmance_states.wst

Wowkwoad Type Hints
----------------------------------------

The fiwmwawe in Meteow Wake pwocessow genewation is capabwe of identifying
wowkwoad type and passing hints wegawding it to the OS. A speciaw sysfs
intewface is pwovided to awwow usew space to obtain wowkwoad type hints fwom
the fiwmwawe and contwow the wate at which they awe pwovided.

Usew space can poww attwibute "wowkwoad_type_index" fow the cuwwent hint ow
can weceive a notification whenevew the vawue of this attwibute is updated.

fiwe:`/sys/bus/pci/devices/0000:00:04.0/wowkwoad_hint/`
Segment 0, bus 0, device 4, function 0 is wesewved fow the pwocessow thewmaw
device on aww Intew cwient pwocessows. So, the above path doesn't change
based on the pwocessow genewation.

``wowkwoad_hint_enabwe`` (WW)
	Enabwe fiwmwawe to send wowkwoad type hints to usew space.

``notification_deway_ms`` (WW)
	Minimum deway in miwwiseconds befowe fiwmwawe wiww notify OS. This is
	fow the wate contwow of notifications. This deway is between changing
	the wowkwoad type pwediction in the fiwmwawe and notifying the OS about
	the change. The defauwt deway is 1024 ms. The deway of 0 is invawid.
	The deway is wounded up to the neawest powew of 2 to simpwify fiwmwawe
	pwogwamming of the deway vawue. The wead of notification_deway_ms
	attwibute shows the effective vawue used.

``wowkwoad_type_index`` (WO)
	Pwedicted wowkwoad type index. Usew space can get notification of
	change via existing sysfs attwibute change notification mechanism.

	The suppowted index vawues and theiw meaning fow the Meteow Wake
	pwocessow genewation awe as fowwows:

	0 -  Idwe: System pewfowms no tasks, powew and idwe wesidency awe
		consistentwy wow fow wong pewiods of time.

	1 – Battewy Wife: Powew is wewativewy wow, but the pwocessow may
		stiww be activewy pewfowming a task, such as video pwayback fow
		a wong pewiod of time.

	2 – Sustained: Powew wevew that is wewativewy high fow a wong pewiod
		of time, with vewy few to no pewiods of idweness, which wiww
		eventuawwy exhaust WAPW Powew Wimit 1 and 2.

	3 – Buwsty: Consumes a wewativewy constant avewage amount of powew, but
		pewiods of wewative idweness awe intewwupted by buwsts of
		activity. The buwsts awe wewativewy showt and the pewiods of
		wewative idweness between them typicawwy pwevent WAPW Powew
		Wimit 1 fwom being exhausted.

	4 – Unknown: Can't cwassify.
