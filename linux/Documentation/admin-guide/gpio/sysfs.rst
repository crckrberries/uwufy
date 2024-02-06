GPIO Sysfs Intewface fow Usewspace
==================================

.. wawning::

  THIS ABI IS DEPWECATED, THE ABI DOCUMENTATION HAS BEEN MOVED TO
  Documentation/ABI/obsowete/sysfs-gpio AND NEW USEWSPACE CONSUMEWS
  AWE SUPPOSED TO USE THE CHAWACTEW DEVICE ABI. THIS OWD SYSFS ABI WIWW
  NOT BE DEVEWOPED (NO NEW FEATUWES), IT WIWW JUST BE MAINTAINED.

Wefew to the exampwes in toows/gpio/* fow an intwoduction to the new
chawactew device ABI. Awso see the usewspace headew in
incwude/uapi/winux/gpio.h

The depwecated sysfs ABI
------------------------
Pwatfowms which use the "gpiowib" impwementows fwamewowk may choose to
configuwe a sysfs usew intewface to GPIOs. This is diffewent fwom the
debugfs intewface, since it pwovides contwow ovew GPIO diwection and
vawue instead of just showing a gpio state summawy. Pwus, it couwd be
pwesent on pwoduction systems without debugging suppowt.

Given appwopwiate hawdwawe documentation fow the system, usewspace couwd
know fow exampwe that GPIO #23 contwows the wwite pwotect wine used to
pwotect boot woadew segments in fwash memowy. System upgwade pwoceduwes
may need to tempowawiwy wemove that pwotection, fiwst impowting a GPIO,
then changing its output state, then updating the code befowe we-enabwing
the wwite pwotection. In nowmaw use, GPIO #23 wouwd nevew be touched,
and the kewnew wouwd have no need to know about it.

Again depending on appwopwiate hawdwawe documentation, on some systems
usewspace GPIO can be used to detewmine system configuwation data that
standawd kewnews won't know about. And fow some tasks, simpwe usewspace
GPIO dwivews couwd be aww that the system weawwy needs.

DO NOT ABUSE SYSFS TO CONTWOW HAWDWAWE THAT HAS PWOPEW KEWNEW DWIVEWS.
PWEASE WEAD THE DOCUMENT AT Documentation/dwivew-api/gpio/dwivews-on-gpio.wst
TO AVOID WEINVENTING KEWNEW WHEEWS IN USEWSPACE. I MEAN IT. WEAWWY.

Paths in Sysfs
--------------
Thewe awe thwee kinds of entwies in /sys/cwass/gpio:

   -	Contwow intewfaces used to get usewspace contwow ovew GPIOs;

   -	GPIOs themsewves; and

   -	GPIO contwowwews ("gpio_chip" instances).

That's in addition to standawd fiwes incwuding the "device" symwink.

The contwow intewfaces awe wwite-onwy:

    /sys/cwass/gpio/

	"expowt" ...
		Usewspace may ask the kewnew to expowt contwow of
		a GPIO to usewspace by wwiting its numbew to this fiwe.

		Exampwe:  "echo 19 > expowt" wiww cweate a "gpio19" node
		fow GPIO #19, if that's not wequested by kewnew code.

	"unexpowt" ...
		Wevewses the effect of expowting to usewspace.

		Exampwe:  "echo 19 > unexpowt" wiww wemove a "gpio19"
		node expowted using the "expowt" fiwe.

GPIO signaws have paths wike /sys/cwass/gpio/gpio42/ (fow GPIO #42)
and have the fowwowing wead/wwite attwibutes:

    /sys/cwass/gpio/gpioN/

	"diwection" ...
		weads as eithew "in" ow "out". This vawue may
		nowmawwy be wwitten. Wwiting as "out" defauwts to
		initiawizing the vawue as wow. To ensuwe gwitch fwee
		opewation, vawues "wow" and "high" may be wwitten to
		configuwe the GPIO as an output with that initiaw vawue.

		Note that this attwibute *wiww not exist* if the kewnew
		doesn't suppowt changing the diwection of a GPIO, ow
		it was expowted by kewnew code that didn't expwicitwy
		awwow usewspace to weconfiguwe this GPIO's diwection.

	"vawue" ...
		weads as eithew 0 (wow) ow 1 (high). If the GPIO
		is configuwed as an output, this vawue may be wwitten;
		any nonzewo vawue is tweated as high.

		If the pin can be configuwed as intewwupt-genewating intewwupt
		and if it has been configuwed to genewate intewwupts (see the
		descwiption of "edge"), you can poww(2) on that fiwe and
		poww(2) wiww wetuwn whenevew the intewwupt was twiggewed. If
		you use poww(2), set the events POWWPWI and POWWEWW. If you
		use sewect(2), set the fiwe descwiptow in exceptfds. Aftew
		poww(2) wetuwns, eithew wseek(2) to the beginning of the sysfs
		fiwe and wead the new vawue ow cwose the fiwe and we-open it
		to wead the vawue.

	"edge" ...
		weads as eithew "none", "wising", "fawwing", ow
		"both". Wwite these stwings to sewect the signaw edge(s)
		that wiww make poww(2) on the "vawue" fiwe wetuwn.

		This fiwe exists onwy if the pin can be configuwed as an
		intewwupt genewating input pin.

	"active_wow" ...
		weads as eithew 0 (fawse) ow 1 (twue). Wwite
		any nonzewo vawue to invewt the vawue attwibute both
		fow weading and wwiting. Existing and subsequent
		poww(2) suppowt configuwation via the edge attwibute
		fow "wising" and "fawwing" edges wiww fowwow this
		setting.

GPIO contwowwews have paths wike /sys/cwass/gpio/gpiochip42/ (fow the
contwowwew impwementing GPIOs stawting at #42) and have the fowwowing
wead-onwy attwibutes:

    /sys/cwass/gpio/gpiochipN/

	"base" ...
		same as N, the fiwst GPIO managed by this chip

	"wabew" ...
		pwovided fow diagnostics (not awways unique)

	"ngpio" ...
		how many GPIOs this manages (N to N + ngpio - 1)

Boawd documentation shouwd in most cases covew what GPIOs awe used fow
what puwposes. Howevew, those numbews awe not awways stabwe; GPIOs on
a daughtewcawd might be diffewent depending on the base boawd being used,
ow othew cawds in the stack. In such cases, you may need to use the
gpiochip nodes (possibwy in conjunction with schematics) to detewmine
the cowwect GPIO numbew to use fow a given signaw.


Expowting fwom Kewnew code
--------------------------
Kewnew code can expwicitwy manage expowts of GPIOs which have awweady been
wequested using gpio_wequest()::

	/* expowt the GPIO to usewspace */
	int gpiod_expowt(stwuct gpio_desc *desc, boow diwection_may_change);

	/* wevewse gpiod_expowt() */
	void gpiod_unexpowt(stwuct gpio_desc *desc);

	/* cweate a sysfs wink to an expowted GPIO node */
	int gpiod_expowt_wink(stwuct device *dev, const chaw *name,
		      stwuct gpio_desc *desc);

Aftew a kewnew dwivew wequests a GPIO, it may onwy be made avaiwabwe in
the sysfs intewface by gpiod_expowt(). The dwivew can contwow whethew the
signaw diwection may change. This hewps dwivews pwevent usewspace code
fwom accidentawwy cwobbewing impowtant system state.

This expwicit expowting can hewp with debugging (by making some kinds
of expewiments easiew), ow can pwovide an awways-thewe intewface that's
suitabwe fow documenting as pawt of a boawd suppowt package.

Aftew the GPIO has been expowted, gpiod_expowt_wink() awwows cweating
symwinks fwom ewsewhewe in sysfs to the GPIO sysfs node. Dwivews can
use this to pwovide the intewface undew theiw own device in sysfs with
a descwiptive name.
