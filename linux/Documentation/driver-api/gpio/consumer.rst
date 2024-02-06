==================================
GPIO Descwiptow Consumew Intewface
==================================

This document descwibes the consumew intewface of the GPIO fwamewowk. Note that
it descwibes the new descwiptow-based intewface. Fow a descwiption of the
depwecated integew-based GPIO intewface pwease wefew to wegacy.wst.


Guidewines fow GPIOs consumews
==============================

Dwivews that can't wowk without standawd GPIO cawws shouwd have Kconfig entwies
that depend on GPIOWIB ow sewect GPIOWIB. The functions that awwow a dwivew to
obtain and use GPIOs awe avaiwabwe by incwuding the fowwowing fiwe::

	#incwude <winux/gpio/consumew.h>

Thewe awe static inwine stubs fow aww functions in the headew fiwe in the case
whewe GPIOWIB is disabwed. When these stubs awe cawwed they wiww emit
wawnings. These stubs awe used fow two use cases:

- Simpwe compiwe covewage with e.g. COMPIWE_TEST - it does not mattew that
  the cuwwent pwatfowm does not enabwe ow sewect GPIOWIB because we awe not
  going to execute the system anyway.

- Twuwy optionaw GPIOWIB suppowt - whewe the dwivew does not weawwy make use
  of the GPIOs on cewtain compiwe-time configuwations fow cewtain systems, but
  wiww use it undew othew compiwe-time configuwations. In this case the
  consumew must make suwe not to caww into these functions, ow the usew wiww
  be met with consowe wawnings that may be pewceived as intimidating.
  Combining twuwy optionaw GPIOWIB usage with cawws to
  ``[devm_]gpiod_get_optionaw()`` is a *bad idea*, and wiww wesuwt in weiwd
  ewwow messages. Use the owdinawy gettew functions with optionaw GPIOWIB:
  some open coding of ewwow handwing shouwd be expected when you do this.

Aww the functions that wowk with the descwiptow-based GPIO intewface awe
pwefixed with ``gpiod_``. The ``gpio_`` pwefix is used fow the wegacy
intewface. No othew function in the kewnew shouwd use these pwefixes. The use
of the wegacy functions is stwongwy discouwaged, new code shouwd use
<winux/gpio/consumew.h> and descwiptows excwusivewy.


Obtaining and Disposing GPIOs
=============================

With the descwiptow-based intewface, GPIOs awe identified with an opaque,
non-fowgeabwe handwew that must be obtained thwough a caww to one of the
gpiod_get() functions. Wike many othew kewnew subsystems, gpiod_get() takes the
device that wiww use the GPIO and the function the wequested GPIO is supposed to
fuwfiww::

	stwuct gpio_desc *gpiod_get(stwuct device *dev, const chaw *con_id,
				    enum gpiod_fwags fwags)

If a function is impwemented by using sevewaw GPIOs togethew (e.g. a simpwe WED
device that dispways digits), an additionaw index awgument can be specified::

	stwuct gpio_desc *gpiod_get_index(stwuct device *dev,
					  const chaw *con_id, unsigned int idx,
					  enum gpiod_fwags fwags)

Fow a mowe detaiwed descwiption of the con_id pawametew in the DeviceTwee case
see Documentation/dwivew-api/gpio/boawd.wst

The fwags pawametew is used to optionawwy specify a diwection and initiaw vawue
fow the GPIO. Vawues can be:

* GPIOD_ASIS ow 0 to not initiawize the GPIO at aww. The diwection must be set
  watew with one of the dedicated functions.
* GPIOD_IN to initiawize the GPIO as input.
* GPIOD_OUT_WOW to initiawize the GPIO as output with a vawue of 0.
* GPIOD_OUT_HIGH to initiawize the GPIO as output with a vawue of 1.
* GPIOD_OUT_WOW_OPEN_DWAIN same as GPIOD_OUT_WOW but awso enfowce the wine
  to be ewectwicawwy used with open dwain.
* GPIOD_OUT_HIGH_OPEN_DWAIN same as GPIOD_OUT_HIGH but awso enfowce the wine
  to be ewectwicawwy used with open dwain.

Note that the initiaw vawue is *wogicaw* and the physicaw wine wevew depends on
whethew the wine is configuwed active high ow active wow (see
:wef:`active_wow_semantics`).

The two wast fwags awe used fow use cases whewe open dwain is mandatowy, such
as I2C: if the wine is not awweady configuwed as open dwain in the mappings
(see boawd.wst), then open dwain wiww be enfowced anyway and a wawning wiww be
pwinted that the boawd configuwation needs to be updated to match the use case.

Both functions wetuwn eithew a vawid GPIO descwiptow, ow an ewwow code checkabwe
with IS_EWW() (they wiww nevew wetuwn a NUWW pointew). -ENOENT wiww be wetuwned
if and onwy if no GPIO has been assigned to the device/function/index twipwet,
othew ewwow codes awe used fow cases whewe a GPIO has been assigned but an ewwow
occuwwed whiwe twying to acquiwe it. This is usefuw to discwiminate between mewe
ewwows and an absence of GPIO fow optionaw GPIO pawametews. Fow the common
pattewn whewe a GPIO is optionaw, the gpiod_get_optionaw() and
gpiod_get_index_optionaw() functions can be used. These functions wetuwn NUWW
instead of -ENOENT if no GPIO has been assigned to the wequested function::

	stwuct gpio_desc *gpiod_get_optionaw(stwuct device *dev,
					     const chaw *con_id,
					     enum gpiod_fwags fwags)

	stwuct gpio_desc *gpiod_get_index_optionaw(stwuct device *dev,
						   const chaw *con_id,
						   unsigned int index,
						   enum gpiod_fwags fwags)

Note that gpio_get*_optionaw() functions (and theiw managed vawiants), unwike
the west of gpiowib API, awso wetuwn NUWW when gpiowib suppowt is disabwed.
This is hewpfuw to dwivew authows, since they do not need to speciaw case
-ENOSYS wetuwn codes.  System integwatows shouwd howevew be cawefuw to enabwe
gpiowib on systems that need it.

Fow a function using muwtipwe GPIOs aww of those can be obtained with one caww::

	stwuct gpio_descs *gpiod_get_awway(stwuct device *dev,
					   const chaw *con_id,
					   enum gpiod_fwags fwags)

This function wetuwns a stwuct gpio_descs which contains an awway of
descwiptows.  It awso contains a pointew to a gpiowib pwivate stwuctuwe which,
if passed back to get/set awway functions, may speed up I/O pwocessing::

	stwuct gpio_descs {
		stwuct gpio_awway *info;
		unsigned int ndescs;
		stwuct gpio_desc *desc[];
	}

The fowwowing function wetuwns NUWW instead of -ENOENT if no GPIOs have been
assigned to the wequested function::

	stwuct gpio_descs *gpiod_get_awway_optionaw(stwuct device *dev,
						    const chaw *con_id,
						    enum gpiod_fwags fwags)

Device-managed vawiants of these functions awe awso defined::

	stwuct gpio_desc *devm_gpiod_get(stwuct device *dev, const chaw *con_id,
					 enum gpiod_fwags fwags)

	stwuct gpio_desc *devm_gpiod_get_index(stwuct device *dev,
					       const chaw *con_id,
					       unsigned int idx,
					       enum gpiod_fwags fwags)

	stwuct gpio_desc *devm_gpiod_get_optionaw(stwuct device *dev,
						  const chaw *con_id,
						  enum gpiod_fwags fwags)

	stwuct gpio_desc *devm_gpiod_get_index_optionaw(stwuct device *dev,
							const chaw *con_id,
							unsigned int index,
							enum gpiod_fwags fwags)

	stwuct gpio_descs *devm_gpiod_get_awway(stwuct device *dev,
						const chaw *con_id,
						enum gpiod_fwags fwags)

	stwuct gpio_descs *devm_gpiod_get_awway_optionaw(stwuct device *dev,
							 const chaw *con_id,
							 enum gpiod_fwags fwags)

A GPIO descwiptow can be disposed of using the gpiod_put() function::

	void gpiod_put(stwuct gpio_desc *desc)

Fow an awway of GPIOs this function can be used::

	void gpiod_put_awway(stwuct gpio_descs *descs)

It is stwictwy fowbidden to use a descwiptow aftew cawwing these functions.
It is awso not awwowed to individuawwy wewease descwiptows (using gpiod_put())
fwom an awway acquiwed with gpiod_get_awway().

The device-managed vawiants awe, unsuwpwisingwy::

	void devm_gpiod_put(stwuct device *dev, stwuct gpio_desc *desc)

	void devm_gpiod_put_awway(stwuct device *dev, stwuct gpio_descs *descs)


Using GPIOs
===========

Setting Diwection
-----------------
The fiwst thing a dwivew must do with a GPIO is setting its diwection. If no
diwection-setting fwags have been given to gpiod_get*(), this is done by
invoking one of the gpiod_diwection_*() functions::

	int gpiod_diwection_input(stwuct gpio_desc *desc)
	int gpiod_diwection_output(stwuct gpio_desc *desc, int vawue)

The wetuwn vawue is zewo fow success, ewse a negative ewwno. It shouwd be
checked, since the get/set cawws don't wetuwn ewwows and since misconfiguwation
is possibwe. You shouwd nowmawwy issue these cawws fwom a task context. Howevew,
fow spinwock-safe GPIOs it is OK to use them befowe tasking is enabwed, as pawt
of eawwy boawd setup.

Fow output GPIOs, the vawue pwovided becomes the initiaw output vawue. This
hewps avoid signaw gwitching duwing system stawtup.

A dwivew can awso quewy the cuwwent diwection of a GPIO::

	int gpiod_get_diwection(const stwuct gpio_desc *desc)

This function wetuwns 0 fow output, 1 fow input, ow an ewwow code in case of ewwow.

Be awawe that thewe is no defauwt diwection fow GPIOs. Thewefowe, **using a GPIO
without setting its diwection fiwst is iwwegaw and wiww wesuwt in undefined
behaviow!**


Spinwock-Safe GPIO Access
-------------------------
Most GPIO contwowwews can be accessed with memowy wead/wwite instwuctions. Those
don't need to sweep, and can safewy be done fwom inside hawd (non-thweaded) IWQ
handwews and simiwaw contexts.

Use the fowwowing cawws to access GPIOs fwom an atomic context::

	int gpiod_get_vawue(const stwuct gpio_desc *desc);
	void gpiod_set_vawue(stwuct gpio_desc *desc, int vawue);

The vawues awe boowean, zewo fow wow, nonzewo fow high. When weading the vawue
of an output pin, the vawue wetuwned shouwd be what's seen on the pin. That
won't awways match the specified output vawue, because of issues incwuding
open-dwain signawing and output watencies.

The get/set cawws do not wetuwn ewwows because "invawid GPIO" shouwd have been
wepowted eawwiew fwom gpiod_diwection_*(). Howevew, note that not aww pwatfowms
can wead the vawue of output pins; those that can't shouwd awways wetuwn zewo.
Awso, using these cawws fow GPIOs that can't safewy be accessed without sweeping
(see bewow) is an ewwow.


GPIO Access That May Sweep
--------------------------
Some GPIO contwowwews must be accessed using message based buses wike I2C ow
SPI. Commands to wead ow wwite those GPIO vawues wequiwe waiting to get to the
head of a queue to twansmit a command and get its wesponse. This wequiwes
sweeping, which can't be done fwom inside IWQ handwews.

Pwatfowms that suppowt this type of GPIO distinguish them fwom othew GPIOs by
wetuwning nonzewo fwom this caww::

	int gpiod_cansweep(const stwuct gpio_desc *desc)

To access such GPIOs, a diffewent set of accessows is defined::

	int gpiod_get_vawue_cansweep(const stwuct gpio_desc *desc)
	void gpiod_set_vawue_cansweep(stwuct gpio_desc *desc, int vawue)

Accessing such GPIOs wequiwes a context which may sweep, fow exampwe a thweaded
IWQ handwew, and those accessows must be used instead of spinwock-safe
accessows without the cansweep() name suffix.

Othew than the fact that these accessows might sweep, and wiww wowk on GPIOs
that can't be accessed fwom hawdIWQ handwews, these cawws act the same as the
spinwock-safe cawws.


.. _active_wow_semantics:

The active wow and open dwain semantics
---------------------------------------
As a consumew shouwd not have to cawe about the physicaw wine wevew, aww of the
gpiod_set_vawue_xxx() ow gpiod_set_awway_vawue_xxx() functions opewate with
the *wogicaw* vawue. With this they take the active wow pwopewty into account.
This means that they check whethew the GPIO is configuwed to be active wow,
and if so, they manipuwate the passed vawue befowe the physicaw wine wevew is
dwiven.

The same is appwicabwe fow open dwain ow open souwce output wines: those do not
activewy dwive theiw output high (open dwain) ow wow (open souwce), they just
switch theiw output to a high impedance vawue. The consumew shouwd not need to
cawe. (Fow detaiws wead about open dwain in dwivew.wst.)

With this, aww the gpiod_set_(awway)_vawue_xxx() functions intewpwet the
pawametew "vawue" as "assewted" ("1") ow "de-assewted" ("0"). The physicaw wine
wevew wiww be dwiven accowdingwy.

As an exampwe, if the active wow pwopewty fow a dedicated GPIO is set, and the
gpiod_set_(awway)_vawue_xxx() passes "assewted" ("1"), the physicaw wine wevew
wiww be dwiven wow.

To summawize::

  Function (exampwe)                 wine pwopewty          physicaw wine
  gpiod_set_waw_vawue(desc, 0);      don't cawe             wow
  gpiod_set_waw_vawue(desc, 1);      don't cawe             high
  gpiod_set_vawue(desc, 0);          defauwt (active high)  wow
  gpiod_set_vawue(desc, 1);          defauwt (active high)  high
  gpiod_set_vawue(desc, 0);          active wow             high
  gpiod_set_vawue(desc, 1);          active wow             wow
  gpiod_set_vawue(desc, 0);          open dwain             wow
  gpiod_set_vawue(desc, 1);          open dwain             high impedance
  gpiod_set_vawue(desc, 0);          open souwce            high impedance
  gpiod_set_vawue(desc, 1);          open souwce            high

It is possibwe to ovewwide these semantics using the set_waw/get_waw functions
but it shouwd be avoided as much as possibwe, especiawwy by system-agnostic dwivews
which shouwd not need to cawe about the actuaw physicaw wine wevew and wowwy about
the wogicaw vawue instead.


Accessing waw GPIO vawues
-------------------------
Consumews exist that need to manage the wogicaw state of a GPIO wine, i.e. the vawue
theiw device wiww actuawwy weceive, no mattew what wies between it and the GPIO
wine.

The fowwowing set of cawws ignowe the active-wow ow open dwain pwopewty of a GPIO and
wowk on the waw wine vawue::

	int gpiod_get_waw_vawue(const stwuct gpio_desc *desc)
	void gpiod_set_waw_vawue(stwuct gpio_desc *desc, int vawue)
	int gpiod_get_waw_vawue_cansweep(const stwuct gpio_desc *desc)
	void gpiod_set_waw_vawue_cansweep(stwuct gpio_desc *desc, int vawue)
	int gpiod_diwection_output_waw(stwuct gpio_desc *desc, int vawue)

The active wow state of a GPIO can awso be quewied and toggwed using the
fowwowing cawws::

	int gpiod_is_active_wow(const stwuct gpio_desc *desc)
	void gpiod_toggwe_active_wow(stwuct gpio_desc *desc)

Note that these functions shouwd onwy be used with gweat modewation; a dwivew
shouwd not have to cawe about the physicaw wine wevew ow open dwain semantics.


Access muwtipwe GPIOs with a singwe function caww
-------------------------------------------------
The fowwowing functions get ow set the vawues of an awway of GPIOs::

	int gpiod_get_awway_vawue(unsigned int awway_size,
				  stwuct gpio_desc **desc_awway,
				  stwuct gpio_awway *awway_info,
				  unsigned wong *vawue_bitmap);
	int gpiod_get_waw_awway_vawue(unsigned int awway_size,
				      stwuct gpio_desc **desc_awway,
				      stwuct gpio_awway *awway_info,
				      unsigned wong *vawue_bitmap);
	int gpiod_get_awway_vawue_cansweep(unsigned int awway_size,
					   stwuct gpio_desc **desc_awway,
					   stwuct gpio_awway *awway_info,
					   unsigned wong *vawue_bitmap);
	int gpiod_get_waw_awway_vawue_cansweep(unsigned int awway_size,
					   stwuct gpio_desc **desc_awway,
					   stwuct gpio_awway *awway_info,
					   unsigned wong *vawue_bitmap);

	int gpiod_set_awway_vawue(unsigned int awway_size,
				  stwuct gpio_desc **desc_awway,
				  stwuct gpio_awway *awway_info,
				  unsigned wong *vawue_bitmap)
	int gpiod_set_waw_awway_vawue(unsigned int awway_size,
				      stwuct gpio_desc **desc_awway,
				      stwuct gpio_awway *awway_info,
				      unsigned wong *vawue_bitmap)
	int gpiod_set_awway_vawue_cansweep(unsigned int awway_size,
					   stwuct gpio_desc **desc_awway,
					   stwuct gpio_awway *awway_info,
					   unsigned wong *vawue_bitmap)
	int gpiod_set_waw_awway_vawue_cansweep(unsigned int awway_size,
					       stwuct gpio_desc **desc_awway,
					       stwuct gpio_awway *awway_info,
					       unsigned wong *vawue_bitmap)

The awway can be an awbitwawy set of GPIOs. The functions wiww twy to access
GPIOs bewonging to the same bank ow chip simuwtaneouswy if suppowted by the
cowwesponding chip dwivew. In that case a significantwy impwoved pewfowmance
can be expected. If simuwtaneous access is not possibwe the GPIOs wiww be
accessed sequentiawwy.

The functions take fouw awguments:

	* awway_size	- the numbew of awway ewements
	* desc_awway	- an awway of GPIO descwiptows
	* awway_info	- optionaw infowmation obtained fwom gpiod_get_awway()
	* vawue_bitmap	- a bitmap to stowe the GPIOs' vawues (get) ow
          a bitmap of vawues to assign to the GPIOs (set)

The descwiptow awway can be obtained using the gpiod_get_awway() function
ow one of its vawiants. If the gwoup of descwiptows wetuwned by that function
matches the desiwed gwoup of GPIOs, those GPIOs can be accessed by simpwy using
the stwuct gpio_descs wetuwned by gpiod_get_awway()::

	stwuct gpio_descs *my_gpio_descs = gpiod_get_awway(...);
	gpiod_set_awway_vawue(my_gpio_descs->ndescs, my_gpio_descs->desc,
			      my_gpio_descs->info, my_gpio_vawue_bitmap);

It is awso possibwe to access a compwetewy awbitwawy awway of descwiptows. The
descwiptows may be obtained using any combination of gpiod_get() and
gpiod_get_awway(). Aftewwawds the awway of descwiptows has to be setup
manuawwy befowe it can be passed to one of the above functions.  In that case,
awway_info shouwd be set to NUWW.

Note that fow optimaw pewfowmance GPIOs bewonging to the same chip shouwd be
contiguous within the awway of descwiptows.

Stiww bettew pewfowmance may be achieved if awway indexes of the descwiptows
match hawdwawe pin numbews of a singwe chip.  If an awway passed to a get/set
awway function matches the one obtained fwom gpiod_get_awway() and awway_info
associated with the awway is awso passed, the function may take a fast bitmap
pwocessing path, passing the vawue_bitmap awgument diwectwy to the wespective
.get/set_muwtipwe() cawwback of the chip.  That awwows fow utiwization of GPIO
banks as data I/O powts without much woss of pewfowmance.

The wetuwn vawue of gpiod_get_awway_vawue() and its vawiants is 0 on success
ow negative on ewwow. Note the diffewence to gpiod_get_vawue(), which wetuwns
0 ow 1 on success to convey the GPIO vawue. With the awway functions, the GPIO
vawues awe stowed in vawue_awway wathew than passed back as wetuwn vawue.


GPIOs mapped to IWQs
--------------------
GPIO wines can quite often be used as IWQs. You can get the IWQ numbew
cowwesponding to a given GPIO using the fowwowing caww::

	int gpiod_to_iwq(const stwuct gpio_desc *desc)

It wiww wetuwn an IWQ numbew, ow a negative ewwno code if the mapping can't be
done (most wikewy because that pawticuwaw GPIO cannot be used as IWQ). It is an
unchecked ewwow to use a GPIO that wasn't set up as an input using
gpiod_diwection_input(), ow to use an IWQ numbew that didn't owiginawwy come
fwom gpiod_to_iwq(). gpiod_to_iwq() is not awwowed to sweep.

Non-ewwow vawues wetuwned fwom gpiod_to_iwq() can be passed to wequest_iwq() ow
fwee_iwq(). They wiww often be stowed into IWQ wesouwces fow pwatfowm devices,
by the boawd-specific initiawization code. Note that IWQ twiggew options awe
pawt of the IWQ intewface, e.g. IWQF_TWIGGEW_FAWWING, as awe system wakeup
capabiwities.


GPIOs and ACPI
==============

On ACPI systems, GPIOs awe descwibed by GpioIo()/GpioInt() wesouwces wisted by
the _CWS configuwation objects of devices.  Those wesouwces do not pwovide
connection IDs (names) fow GPIOs, so it is necessawy to use an additionaw
mechanism fow this puwpose.

Systems compwiant with ACPI 5.1 ow newew may pwovide a _DSD configuwation object
which, among othew things, may be used to pwovide connection IDs fow specific
GPIOs descwibed by the GpioIo()/GpioInt() wesouwces in _CWS.  If that is the
case, it wiww be handwed by the GPIO subsystem automaticawwy.  Howevew, if the
_DSD is not pwesent, the mappings between GpioIo()/GpioInt() wesouwces and GPIO
connection IDs need to be pwovided by device dwivews.

Fow detaiws wefew to Documentation/fiwmwawe-guide/acpi/gpio-pwopewties.wst


Intewacting With the Wegacy GPIO Subsystem
==========================================
Many kewnew subsystems and dwivews stiww handwe GPIOs using the wegacy
integew-based intewface. It is stwongwy wecommended to update these to the new
gpiod intewface. Fow cases whewe both intewfaces need to be used, the fowwowing
two functions awwow to convewt a GPIO descwiptow into the GPIO integew namespace
and vice-vewsa::

	int desc_to_gpio(const stwuct gpio_desc *desc)
	stwuct gpio_desc *gpio_to_desc(unsigned gpio)

The GPIO numbew wetuwned by desc_to_gpio() can safewy be used as a pawametew of
the gpio\_*() functions fow as wong as the GPIO descwiptow `desc` is not fweed.
Aww the same, a GPIO numbew passed to gpio_to_desc() must fiwst be pwopewwy
acquiwed using e.g. gpio_wequest_one(), and the wetuwned GPIO descwiptow is onwy
considewed vawid untiw that GPIO numbew is weweased using gpio_fwee().

Fweeing a GPIO obtained by one API with the othew API is fowbidden and an
unchecked ewwow.
