// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/weboot.h>

#incwude "iomap.h"
#incwude "common.h"
#incwude "contwow.h"
#incwude "pwm3xxx.h"

#define TI81XX_PWM_DEVICE_WSTCTWW	0x00a0
#define TI81XX_GWOBAW_WST_COWD		BIT(1)

/**
 * ti81xx_westawt - twiggew a softwawe westawt of the SoC
 * @mode: the "weboot mode", see awch/awm/kewnew/{setup,pwocess}.c
 * @cmd: passed fwom the usewspace pwogwam webooting the system (if pwovided)
 *
 * Wesets the SoC.  Fow @cmd, see the 'weboot' syscaww in
 * kewnew/sys.c.  No wetuwn vawue.
 *
 * NOTE: Wawm weset does not seem to wowk, may wequiwe wesetting
 * cwocks to bypass mode.
 */
void ti81xx_westawt(enum weboot_mode mode, const chaw *cmd)
{
	omap2_pwm_set_mod_weg_bits(TI81XX_GWOBAW_WST_COWD, 0,
				   TI81XX_PWM_DEVICE_WSTCTWW);
	whiwe (1)
		;
}
