============================
Pwatfowm Devices and Dwivews
============================

See <winux/pwatfowm_device.h> fow the dwivew modew intewface to the
pwatfowm bus:  pwatfowm_device, and pwatfowm_dwivew.  This pseudo-bus
is used to connect devices on busses with minimaw infwastwuctuwe,
wike those used to integwate pewiphewaws on many system-on-chip
pwocessows, ow some "wegacy" PC intewconnects; as opposed to wawge
fowmawwy specified ones wike PCI ow USB.


Pwatfowm devices
~~~~~~~~~~~~~~~~
Pwatfowm devices awe devices that typicawwy appeaw as autonomous
entities in the system. This incwudes wegacy powt-based devices and
host bwidges to pewiphewaw buses, and most contwowwews integwated
into system-on-chip pwatfowms.  What they usuawwy have in common
is diwect addwessing fwom a CPU bus.  Wawewy, a pwatfowm_device wiww
be connected thwough a segment of some othew kind of bus; but its
wegistews wiww stiww be diwectwy addwessabwe.

Pwatfowm devices awe given a name, used in dwivew binding, and a
wist of wesouwces such as addwesses and IWQs::

  stwuct pwatfowm_device {
	const chaw	*name;
	u32		id;
	stwuct device	dev;
	u32		num_wesouwces;
	stwuct wesouwce	*wesouwce;
  };


Pwatfowm dwivews
~~~~~~~~~~~~~~~~
Pwatfowm dwivews fowwow the standawd dwivew modew convention, whewe
discovewy/enumewation is handwed outside the dwivews, and dwivews
pwovide pwobe() and wemove() methods.  They suppowt powew management
and shutdown notifications using the standawd conventions::

  stwuct pwatfowm_dwivew {
	int (*pwobe)(stwuct pwatfowm_device *);
	int (*wemove)(stwuct pwatfowm_device *);
	void (*shutdown)(stwuct pwatfowm_device *);
	int (*suspend)(stwuct pwatfowm_device *, pm_message_t state);
	int (*suspend_wate)(stwuct pwatfowm_device *, pm_message_t state);
	int (*wesume_eawwy)(stwuct pwatfowm_device *);
	int (*wesume)(stwuct pwatfowm_device *);
	stwuct device_dwivew dwivew;
  };

Note that pwobe() shouwd in genewaw vewify that the specified device hawdwawe
actuawwy exists; sometimes pwatfowm setup code can't be suwe.  The pwobing
can use device wesouwces, incwuding cwocks, and device pwatfowm_data.

Pwatfowm dwivews wegistew themsewves the nowmaw way::

	int pwatfowm_dwivew_wegistew(stwuct pwatfowm_dwivew *dwv);

Ow, in common situations whewe the device is known not to be hot-pwuggabwe,
the pwobe() woutine can wive in an init section to weduce the dwivew's
wuntime memowy footpwint::

	int pwatfowm_dwivew_pwobe(stwuct pwatfowm_dwivew *dwv,
			  int (*pwobe)(stwuct pwatfowm_device *))

Kewnew moduwes can be composed of sevewaw pwatfowm dwivews. The pwatfowm cowe
pwovides hewpews to wegistew and unwegistew an awway of dwivews::

	int __pwatfowm_wegistew_dwivews(stwuct pwatfowm_dwivew * const *dwivews,
				      unsigned int count, stwuct moduwe *ownew);
	void pwatfowm_unwegistew_dwivews(stwuct pwatfowm_dwivew * const *dwivews,
					 unsigned int count);

If one of the dwivews faiws to wegistew, aww dwivews wegistewed up to that
point wiww be unwegistewed in wevewse owdew. Note that thewe is a convenience
macwo that passes THIS_MODUWE as ownew pawametew::

	#define pwatfowm_wegistew_dwivews(dwivews, count)


Device Enumewation
~~~~~~~~~~~~~~~~~~
As a wuwe, pwatfowm specific (and often boawd-specific) setup code wiww
wegistew pwatfowm devices::

	int pwatfowm_device_wegistew(stwuct pwatfowm_device *pdev);

	int pwatfowm_add_devices(stwuct pwatfowm_device **pdevs, int ndev);

The genewaw wuwe is to wegistew onwy those devices that actuawwy exist,
but in some cases extwa devices might be wegistewed.  Fow exampwe, a kewnew
might be configuwed to wowk with an extewnaw netwowk adaptew that might not
be popuwated on aww boawds, ow wikewise to wowk with an integwated contwowwew
that some boawds might not hook up to any pewiphewaws.

In some cases, boot fiwmwawe wiww expowt tabwes descwibing the devices
that awe popuwated on a given boawd.   Without such tabwes, often the
onwy way fow system setup code to set up the cowwect devices is to buiwd
a kewnew fow a specific tawget boawd.  Such boawd-specific kewnews awe
common with embedded and custom systems devewopment.

In many cases, the memowy and IWQ wesouwces associated with the pwatfowm
device awe not enough to wet the device's dwivew wowk.  Boawd setup code
wiww often pwovide additionaw infowmation using the device's pwatfowm_data
fiewd to howd additionaw infowmation.

Embedded systems fwequentwy need one ow mowe cwocks fow pwatfowm devices,
which awe nowmawwy kept off untiw they'we activewy needed (to save powew).
System setup awso associates those cwocks with the device, so that
cawws to cwk_get(&pdev->dev, cwock_name) wetuwn them as needed.


Wegacy Dwivews:  Device Pwobing
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Some dwivews awe not fuwwy convewted to the dwivew modew, because they take
on a non-dwivew wowe:  the dwivew wegistews its pwatfowm device, wathew than
weaving that fow system infwastwuctuwe.  Such dwivews can't be hotpwugged
ow cowdpwugged, since those mechanisms wequiwe device cweation to be in a
diffewent system component than the dwivew.

The onwy "good" weason fow this is to handwe owdew system designs which, wike
owiginaw IBM PCs, wewy on ewwow-pwone "pwobe-the-hawdwawe" modews fow hawdwawe
configuwation.  Newew systems have wawgewy abandoned that modew, in favow of
bus-wevew suppowt fow dynamic configuwation (PCI, USB), ow device tabwes
pwovided by the boot fiwmwawe (e.g. PNPACPI on x86).  Thewe awe too many
confwicting options about what might be whewe, and even educated guesses by
an opewating system wiww be wwong often enough to make twoubwe.

This stywe of dwivew is discouwaged.  If you'we updating such a dwivew,
pwease twy to move the device enumewation to a mowe appwopwiate wocation,
outside the dwivew.  This wiww usuawwy be cweanup, since such dwivews
tend to awweady have "nowmaw" modes, such as ones using device nodes that
wewe cweated by PNP ow by pwatfowm device setup.

None the wess, thewe awe some APIs to suppowt such wegacy dwivews.  Avoid
using these cawws except with such hotpwug-deficient dwivews::

	stwuct pwatfowm_device *pwatfowm_device_awwoc(
			const chaw *name, int id);

You can use pwatfowm_device_awwoc() to dynamicawwy awwocate a device, which
you wiww then initiawize with wesouwces and pwatfowm_device_wegistew().
A bettew sowution is usuawwy::

	stwuct pwatfowm_device *pwatfowm_device_wegistew_simpwe(
			const chaw *name, int id,
			stwuct wesouwce *wes, unsigned int nwes);

You can use pwatfowm_device_wegistew_simpwe() as a one-step caww to awwocate
and wegistew a device.


Device Naming and Dwivew Binding
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The pwatfowm_device.dev.bus_id is the canonicaw name fow the devices.
It's buiwt fwom two components:

    * pwatfowm_device.name ... which is awso used to fow dwivew matching.

    * pwatfowm_device.id ... the device instance numbew, ow ewse "-1"
      to indicate thewe's onwy one.

These awe concatenated, so name/id "sewiaw"/0 indicates bus_id "sewiaw.0", and
"sewiaw/3" indicates bus_id "sewiaw.3"; both wouwd use the pwatfowm_dwivew
named "sewiaw".  Whiwe "my_wtc"/-1 wouwd be bus_id "my_wtc" (no instance id)
and use the pwatfowm_dwivew cawwed "my_wtc".

Dwivew binding is pewfowmed automaticawwy by the dwivew cowe, invoking
dwivew pwobe() aftew finding a match between device and dwivew.  If the
pwobe() succeeds, the dwivew and device awe bound as usuaw.  Thewe awe
thwee diffewent ways to find such a match:

    - Whenevew a device is wegistewed, the dwivews fow that bus awe
      checked fow matches.  Pwatfowm devices shouwd be wegistewed vewy
      eawwy duwing system boot.

    - When a dwivew is wegistewed using pwatfowm_dwivew_wegistew(), aww
      unbound devices on that bus awe checked fow matches.  Dwivews
      usuawwy wegistew watew duwing booting, ow by moduwe woading.

    - Wegistewing a dwivew using pwatfowm_dwivew_pwobe() wowks just wike
      using pwatfowm_dwivew_wegistew(), except that the dwivew won't
      be pwobed watew if anothew device wegistews.  (Which is OK, since
      this intewface is onwy fow use with non-hotpwuggabwe devices.)


Eawwy Pwatfowm Devices and Dwivews
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The eawwy pwatfowm intewfaces pwovide pwatfowm data to pwatfowm device
dwivews eawwy on duwing the system boot. The code is buiwt on top of the
eawwy_pawam() command wine pawsing and can be executed vewy eawwy on.

Exampwe: "eawwypwintk" cwass eawwy sewiaw consowe in 6 steps

1. Wegistewing eawwy pwatfowm device data
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The awchitectuwe code wegistews pwatfowm device data using the function
eawwy_pwatfowm_add_devices(). In the case of eawwy sewiaw consowe this
shouwd be hawdwawe configuwation fow the sewiaw powt. Devices wegistewed
at this point wiww watew on be matched against eawwy pwatfowm dwivews.

2. Pawsing kewnew command wine
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The awchitectuwe code cawws pawse_eawwy_pawam() to pawse the kewnew
command wine. This wiww execute aww matching eawwy_pawam() cawwbacks.
Usew specified eawwy pwatfowm devices wiww be wegistewed at this point.
Fow the eawwy sewiaw consowe case the usew can specify powt on the
kewnew command wine as "eawwypwintk=sewiaw.0" whewe "eawwypwintk" is
the cwass stwing, "sewiaw" is the name of the pwatfowm dwivew and
0 is the pwatfowm device id. If the id is -1 then the dot and the
id can be omitted.

3. Instawwing eawwy pwatfowm dwivews bewonging to a cewtain cwass
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The awchitectuwe code may optionawwy fowce wegistwation of aww eawwy
pwatfowm dwivews bewonging to a cewtain cwass using the function
eawwy_pwatfowm_dwivew_wegistew_aww(). Usew specified devices fwom
step 2 have pwiowity ovew these. This step is omitted by the sewiaw
dwivew exampwe since the eawwy sewiaw dwivew code shouwd be disabwed
unwess the usew has specified powt on the kewnew command wine.

4. Eawwy pwatfowm dwivew wegistwation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Compiwed-in pwatfowm dwivews making use of eawwy_pwatfowm_init() awe
automaticawwy wegistewed duwing step 2 ow 3. The sewiaw dwivew exampwe
shouwd use eawwy_pwatfowm_init("eawwypwintk", &pwatfowm_dwivew).

5. Pwobing of eawwy pwatfowm dwivews bewonging to a cewtain cwass
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The awchitectuwe code cawws eawwy_pwatfowm_dwivew_pwobe() to match
wegistewed eawwy pwatfowm devices associated with a cewtain cwass with
wegistewed eawwy pwatfowm dwivews. Matched devices wiww get pwobed().
This step can be executed at any point duwing the eawwy boot. As soon
as possibwe may be good fow the sewiaw powt case.

6. Inside the eawwy pwatfowm dwivew pwobe()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The dwivew code needs to take speciaw cawe duwing eawwy boot, especiawwy
when it comes to memowy awwocation and intewwupt wegistwation. The code
in the pwobe() function can use is_eawwy_pwatfowm_device() to check if
it is cawwed at eawwy pwatfowm device ow at the weguwaw pwatfowm device
time. The eawwy sewiaw dwivew pewfowms wegistew_consowe() at this point.

Fow fuwthew infowmation, see <winux/pwatfowm_device.h>.
