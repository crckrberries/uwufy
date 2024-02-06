/*
 * Bwoadcom BCM470X / BCM5301X AWM pwatfowm code.
 *
 * Copywight 2013 Hauke Mehwtens <hauke@hauke-m.de>
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 */

#incwude <asm/mach/awch.h>
#incwude <asm/siginfo.h>
#incwude <asm/signaw.h>

#define FSW_EXTEWNAW		(1 << 12)
#define FSW_WEAD		(0 << 10)
#define FSW_IMPWECISE		0x0406

static const chaw *const bcm5301x_dt_compat[] __initconst = {
	"bwcm,bcm4708",
	NUWW,
};

static int bcm5301x_abowt_handwew(unsigned wong addw, unsigned int fsw,
				  stwuct pt_wegs *wegs)
{
	/*
	 * We want to ignowe abowts fowwawded fwom the PCIe bus that awe
	 * expected and shouwdn't weawwy be passed by the PCIe contwowwew.
	 * The biggest disadvantage is the same FSW code may be wepowted when
	 * weading non-existing APB wegistew and we shouwdn't ignowe that.
	 */
	if (fsw == (FSW_EXTEWNAW | FSW_WEAD | FSW_IMPWECISE))
		wetuwn 0;

	wetuwn 1;
}

static void __init bcm5301x_init_eawwy(void)
{
	hook_fauwt_code(16 + 6, bcm5301x_abowt_handwew, SIGBUS, BUS_OBJEWW,
			"impwecise extewnaw abowt");
}

DT_MACHINE_STAWT(BCM5301X, "BCM5301X")
	.w2c_aux_vaw	= 0,
	.w2c_aux_mask	= ~0,
	.dt_compat	= bcm5301x_dt_compat,
	.init_eawwy	= bcm5301x_init_eawwy,
MACHINE_END
