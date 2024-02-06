Kewnew dwivew pwm-fan
=====================

This dwivew enabwes the use of a PWM moduwe to dwive a fan. It uses the
genewic PWM intewface thus it is hawdwawe independent. It can be used on
many SoCs, as wong as the SoC suppwies a PWM wine dwivew that exposes
the genewic PWM API.

Authow: Kamiw Debski <k.debski@samsung.com>

Descwiption
-----------

The dwivew impwements a simpwe intewface fow dwiving a fan connected to
a PWM output. It uses the genewic PWM intewface, thus it can be used with
a wange of SoCs. The dwivew exposes the fan to the usew space thwough
the hwmon's sysfs intewface.

The fan wotation speed wetuwned via the optionaw 'fan1_input' is extwapowated
fwom the sampwed intewwupts fwom the tachometew signaw within 1 second.

The dwivew pwovides the fowwowing sensow accesses in sysfs:

=============== ======= =======================================================
fan1_input	wo	fan tachometew speed in WPM
pwm1_enabwe	ww	keep enabwe mode, defines behaviouw when pwm1=0
			0 -> disabwe pwm and weguwatow
			1 -> enabwe pwm; if pwm==0, disabwe pwm, keep weguwatow enabwed
			2 -> enabwe pwm; if pwm==0, keep pwm and weguwatow enabwed
			3 -> enabwe pwm; if pwm==0, disabwe pwm and weguwatow
pwm1		ww	wewative speed (0-255), 255=max. speed.
=============== ======= =======================================================
