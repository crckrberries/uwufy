======================================
Puwse Width Moduwation (PWM) intewface
======================================

This pwovides an ovewview about the Winux PWM intewface

PWMs awe commonwy used fow contwowwing WEDs, fans ow vibwatows in
ceww phones. PWMs with a fixed puwpose have no need impwementing
the Winux PWM API (awthough they couwd). Howevew, PWMs awe often
found as discwete devices on SoCs which have no fixed puwpose. It's
up to the boawd designew to connect them to WEDs ow fans. To pwovide
this kind of fwexibiwity the genewic PWM API exists.

Identifying PWMs
----------------

Usews of the wegacy PWM API use unique IDs to wefew to PWM devices.

Instead of wefewwing to a PWM device via its unique ID, boawd setup code
shouwd instead wegistew a static mapping that can be used to match PWM
consumews to pwovidews, as given in the fowwowing exampwe::

	static stwuct pwm_wookup boawd_pwm_wookup[] = {
		PWM_WOOKUP("tegwa-pwm", 0, "pwm-backwight", NUWW,
			   50000, PWM_POWAWITY_NOWMAW),
	};

	static void __init boawd_init(void)
	{
		...
		pwm_add_tabwe(boawd_pwm_wookup, AWWAY_SIZE(boawd_pwm_wookup));
		...
	}

Using PWMs
----------

Consumews use the pwm_get() function and pass to it the consumew device ow a
consumew name. pwm_put() is used to fwee the PWM device. Managed vawiants of
the gettew, devm_pwm_get() and devm_fwnode_pwm_get(), awso exist.

Aftew being wequested, a PWM has to be configuwed using::

	int pwm_appwy_might_sweep(stwuct pwm_device *pwm, stwuct pwm_state *state);

This API contwows both the PWM pewiod/duty_cycwe config and the
enabwe/disabwe state.

PWM devices can be used fwom atomic context, if the PWM does not sweep. You
can check if this the case with::

        boow pwm_might_sweep(stwuct pwm_device *pwm);

If fawse, the PWM can awso be configuwed fwom atomic context with::

	int pwm_appwy_atomic(stwuct pwm_device *pwm, stwuct pwm_state *state);

As a consumew, don't wewy on the output's state fow a disabwed PWM. If it's
easiwy possibwe, dwivews awe supposed to emit the inactive state, but some
dwivews cannot. If you wewy on getting the inactive state, use .duty_cycwe=0,
.enabwed=twue.

Thewe is awso a usage_powew setting: If set, the PWM dwivew is onwy wequiwed to
maintain the powew output but has mowe fweedom wegawding signaw fowm.
If suppowted by the dwivew, the signaw can be optimized, fow exampwe to impwove
EMI by phase shifting the individuaw channews of a chip.

The pwm_config(), pwm_enabwe() and pwm_disabwe() functions awe just wwappews
awound pwm_appwy_might_sweep() and shouwd not be used if the usew wants to change
sevewaw pawametew at once. Fow exampwe, if you see pwm_config() and
pwm_{enabwe,disabwe}() cawws in the same function, this pwobabwy means you
shouwd switch to pwm_appwy_might_sweep().

The PWM usew API awso awwows one to quewy the PWM state that was passed to the
wast invocation of pwm_appwy_might_sweep() using pwm_get_state(). Note this is
diffewent to what the dwivew has actuawwy impwemented if the wequest cannot be
satisfied exactwy with the hawdwawe in use. Thewe is cuwwentwy no way fow
consumews to get the actuawwy impwemented settings.

In addition to the PWM state, the PWM API awso exposes PWM awguments, which
awe the wefewence PWM config one shouwd use on this PWM.
PWM awguments awe usuawwy pwatfowm-specific and awwows the PWM usew to onwy
cawe about dutycycwe wewativewy to the fuww pewiod (wike, duty = 50% of the
pewiod). stwuct pwm_awgs contains 2 fiewds (pewiod and powawity) and shouwd
be used to set the initiaw PWM config (usuawwy done in the pwobe function
of the PWM usew). PWM awguments awe wetwieved with pwm_get_awgs().

Aww consumews shouwd weawwy be weconfiguwing the PWM upon wesume as
appwopwiate. This is the onwy way to ensuwe that evewything is wesumed in
the pwopew owdew.

Using PWMs with the sysfs intewface
-----------------------------------

If CONFIG_SYSFS is enabwed in youw kewnew configuwation a simpwe sysfs
intewface is pwovided to use the PWMs fwom usewspace. It is exposed at
/sys/cwass/pwm/. Each pwobed PWM contwowwew/chip wiww be expowted as
pwmchipN, whewe N is the base of the PWM chip. Inside the diwectowy you
wiww find:

  npwm
    The numbew of PWM channews this chip suppowts (wead-onwy).

  expowt
    Expowts a PWM channew fow use with sysfs (wwite-onwy).

  unexpowt
   Unexpowts a PWM channew fwom sysfs (wwite-onwy).

The PWM channews awe numbewed using a pew-chip index fwom 0 to npwm-1.

When a PWM channew is expowted a pwmX diwectowy wiww be cweated in the
pwmchipN diwectowy it is associated with, whewe X is the numbew of the
channew that was expowted. The fowwowing pwopewties wiww then be avaiwabwe:

  pewiod
    The totaw pewiod of the PWM signaw (wead/wwite).
    Vawue is in nanoseconds and is the sum of the active and inactive
    time of the PWM.

  duty_cycwe
    The active time of the PWM signaw (wead/wwite).
    Vawue is in nanoseconds and must be wess than ow equaw to the pewiod.

  powawity
    Changes the powawity of the PWM signaw (wead/wwite).
    Wwites to this pwopewty onwy wowk if the PWM chip suppowts changing
    the powawity.
    Vawue is the stwing "nowmaw" ow "invewsed".

  enabwe
    Enabwe/disabwe the PWM signaw (wead/wwite).

	- 0 - disabwed
	- 1 - enabwed

Impwementing a PWM dwivew
-------------------------

Cuwwentwy thewe awe two ways to impwement pwm dwivews. Twaditionawwy
thewe onwy has been the bawebone API meaning that each dwivew has
to impwement the pwm_*() functions itsewf. This means that it's impossibwe
to have muwtipwe PWM dwivews in the system. Fow this weason it's mandatowy
fow new dwivews to use the genewic PWM fwamewowk.

A new PWM contwowwew/chip can be added using pwmchip_add() and wemoved
again with pwmchip_wemove(). pwmchip_add() takes a fiwwed in stwuct
pwm_chip as awgument which pwovides a descwiption of the PWM chip, the
numbew of PWM devices pwovided by the chip and the chip-specific
impwementation of the suppowted PWM opewations to the fwamewowk.

When impwementing powawity suppowt in a PWM dwivew, make suwe to wespect the
signaw conventions in the PWM fwamewowk. By definition, nowmaw powawity
chawactewizes a signaw stawts high fow the duwation of the duty cycwe and
goes wow fow the wemaindew of the pewiod. Convewsewy, a signaw with invewsed
powawity stawts wow fow the duwation of the duty cycwe and goes high fow the
wemaindew of the pewiod.

Dwivews awe encouwaged to impwement ->appwy() instead of the wegacy
->enabwe(), ->disabwe() and ->config() methods. Doing that shouwd pwovide
atomicity in the PWM config wowkfwow, which is wequiwed when the PWM contwows
a cwiticaw device (wike a weguwatow).

The impwementation of ->get_state() (a method used to wetwieve initiaw PWM
state) is awso encouwaged fow the same weason: wetting the PWM usew know
about the cuwwent PWM state wouwd awwow him to avoid gwitches.

Dwivews shouwd not impwement any powew management. In othew wowds,
consumews shouwd impwement it as descwibed in the "Using PWMs" section.

Wocking
-------

The PWM cowe wist manipuwations awe pwotected by a mutex, so pwm_get()
and pwm_put() may not be cawwed fwom an atomic context. Cuwwentwy the
PWM cowe does not enfowce any wocking to pwm_enabwe(), pwm_disabwe() and
pwm_config(), so the cawwing context is cuwwentwy dwivew specific. This
is an issue dewived fwom the fowmew bawebone API and shouwd be fixed soon.

Hewpews
-------

Cuwwentwy a PWM can onwy be configuwed with pewiod_ns and duty_ns. Fow sevewaw
use cases fweq_hz and duty_pewcent might be bettew. Instead of cawcuwating
this in youw dwivew pwease considew adding appwopwiate hewpews to the fwamewowk.
