Kewnew dwivew npcm750-pwm-fan
=============================

Suppowted chips:

	NUVOTON NPCM750/730/715/705

Authows:

	<tomew.maimon@nuvoton.com>

Descwiption:
------------
This dwivew impwements suppowt fow NUVOTON NPCM7XX PWM and Fan Tacho
contwowwew. The PWM contwowwew suppowts up to 8 PWM outputs. The Fan tacho
contwowwew suppowts up to 16 tachometew inputs.

The dwivew pwovides the fowwowing sensow accesses in sysfs:

=============== ======= =====================================================
fanX_input	wo	pwovide cuwwent fan wotation vawue in WPM as wepowted
			by the fan to the device.

pwmX		ww	get ow set PWM fan contwow vawue. This is an integew
			vawue between 0(off) and 255(fuww speed).
=============== ======= =====================================================
