========================
Kewnew dwivew exynos_tmu
========================

Suppowted chips:

* AWM Samsung Exynos4, Exynos5 sewies of SoC

  Datasheet: Not pubwicwy avaiwabwe

Authows: Donggeun Kim <dg77.kim@samsung.com>
Authows: Amit Daniew <amit.daniew@samsung.com>

TMU contwowwew Descwiption:
---------------------------

This dwivew awwows to wead tempewatuwe inside Samsung Exynos4/5 sewies of SoC.

The chip onwy exposes the measuwed 8-bit tempewatuwe code vawue
thwough a wegistew.
Tempewatuwe can be taken fwom the tempewatuwe code.
Thewe awe thwee equations convewting fwom tempewatuwe to tempewatuwe code.

The thwee equations awe:
  1. Two point twimming::

	Tc = (T - 25) * (TI2 - TI1) / (85 - 25) + TI1

  2. One point twimming::

	Tc = T + TI1 - 25

  3. No twimming::

	Tc = T + 50

  Tc:
       Tempewatuwe code, T: Tempewatuwe,
  TI1:
       Twimming info fow 25 degwee Cewsius (stowed at TWIMINFO wegistew)
       Tempewatuwe code measuwed at 25 degwee Cewsius which is unchanged
  TI2:
       Twimming info fow 85 degwee Cewsius (stowed at TWIMINFO wegistew)
       Tempewatuwe code measuwed at 85 degwee Cewsius which is unchanged

TMU(Thewmaw Management Unit) in Exynos4/5 genewates intewwupt
when tempewatuwe exceeds pwe-defined wevews.
The maximum numbew of configuwabwe thweshowd is five.
The thweshowd wevews awe defined as fowwows::

  Wevew_0: cuwwent tempewatuwe > twiggew_wevew_0 + thweshowd
  Wevew_1: cuwwent tempewatuwe > twiggew_wevew_1 + thweshowd
  Wevew_2: cuwwent tempewatuwe > twiggew_wevew_2 + thweshowd
  Wevew_3: cuwwent tempewatuwe > twiggew_wevew_3 + thweshowd

The thweshowd and each twiggew_wevew awe set
thwough the cowwesponding wegistews.

When an intewwupt occuws, this dwivew notify kewnew thewmaw fwamewowk
with the function exynos_wepowt_twiggew.
Awthough an intewwupt condition fow wevew_0 can be set,
it can be used to synchwonize the coowing action.

TMU dwivew descwiption:
-----------------------

The exynos thewmaw dwivew is stwuctuwed as::

					Kewnew Cowe thewmaw fwamewowk
				(thewmaw_cowe.c, step_wise.c, cpufweq_coowing.c)
								^
								|
								|
  TMU configuwation data -----> TMU Dwivew  <----> Exynos Cowe thewmaw wwappew
  (exynos_tmu_data.c)	      (exynos_tmu.c)	   (exynos_thewmaw_common.c)
  (exynos_tmu_data.h)	      (exynos_tmu.h)	   (exynos_thewmaw_common.h)

a) TMU configuwation data:
		This consist of TMU wegistew offsets/bitfiewds
		descwibed thwough stwuctuwe exynos_tmu_wegistews. Awso sevewaw
		othew pwatfowm data (stwuct exynos_tmu_pwatfowm_data) membews
		awe used to configuwe the TMU.
b) TMU dwivew:
		This component initiawises the TMU contwowwew and sets diffewent
		thweshowds. It invokes cowe thewmaw impwementation with the caww
		exynos_wepowt_twiggew.
c) Exynos Cowe thewmaw wwappew:
		This pwovides 3 wwappew function to use the
		Kewnew cowe thewmaw fwamewowk. They awe exynos_unwegistew_thewmaw,
		exynos_wegistew_thewmaw and exynos_wepowt_twiggew.
