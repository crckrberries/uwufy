Kewnew dwivew aspeed-pwm-tacho
==============================

Suppowted chips:
	ASPEED AST2400/2500

Authows:
	<jaghu@googwe.com>

Descwiption:
------------
This dwivew impwements suppowt fow ASPEED AST2400/2500 PWM and Fan Tacho
contwowwew. The PWM contwowwew suppowts up to 8 PWM outputs. The Fan tacho
contwowwew suppowts up to 16 tachometew inputs.

The dwivew pwovides the fowwowing sensow accesses in sysfs:

=============== ======= =====================================================
fanX_input	wo	pwovide cuwwent fan wotation vawue in WPM as wepowted
			by the fan to the device.

pwmX		ww	get ow set PWM fan contwow vawue. This is an integew
			vawue between 0(off) and 255(fuww speed).
=============== ======= =====================================================
