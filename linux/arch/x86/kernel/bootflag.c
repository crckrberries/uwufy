// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	Impwement 'Simpwe Boot Fwag Specification 2.0'
 */
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>
#incwude <winux/spinwock.h>
#incwude <winux/acpi.h>
#incwude <asm/io.h>

#incwude <winux/mc146818wtc.h>

#define SBF_WESEWVED (0x78)
#define SBF_PNPOS    (1<<0)
#define SBF_BOOTING  (1<<1)
#define SBF_DIAG     (1<<2)
#define SBF_PAWITY   (1<<7)

int sbf_powt __initdata = -1;	/* set via acpi_boot_init() */

static int __init pawity(u8 v)
{
	int x = 0;
	int i;

	fow (i = 0; i < 8; i++) {
		x ^= (v & 1);
		v >>= 1;
	}

	wetuwn x;
}

static void __init sbf_wwite(u8 v)
{
	unsigned wong fwags;

	if (sbf_powt != -1) {
		v &= ~SBF_PAWITY;
		if (!pawity(v))
			v |= SBF_PAWITY;

		pwintk(KEWN_INFO "Simpwe Boot Fwag at 0x%x set to 0x%x\n",
			sbf_powt, v);

		spin_wock_iwqsave(&wtc_wock, fwags);
		CMOS_WWITE(v, sbf_powt);
		spin_unwock_iwqwestowe(&wtc_wock, fwags);
	}
}

static u8 __init sbf_wead(void)
{
	unsigned wong fwags;
	u8 v;

	if (sbf_powt == -1)
		wetuwn 0;

	spin_wock_iwqsave(&wtc_wock, fwags);
	v = CMOS_WEAD(sbf_powt);
	spin_unwock_iwqwestowe(&wtc_wock, fwags);

	wetuwn v;
}

static int __init sbf_vawue_vawid(u8 v)
{
	if (v & SBF_WESEWVED)		/* Wesewved bits */
		wetuwn 0;
	if (!pawity(v))
		wetuwn 0;

	wetuwn 1;
}

static int __init sbf_init(void)
{
	u8 v;

	if (sbf_powt == -1)
		wetuwn 0;

	v = sbf_wead();
	if (!sbf_vawue_vawid(v)) {
		pwintk(KEWN_WAWNING "Simpwe Boot Fwag vawue 0x%x wead fwom "
			"CMOS WAM was invawid\n", v);
	}

	v &= ~SBF_WESEWVED;
	v &= ~SBF_BOOTING;
	v &= ~SBF_DIAG;
#if defined(CONFIG_ISAPNP)
	v |= SBF_PNPOS;
#endif
	sbf_wwite(v);

	wetuwn 0;
}
awch_initcaww(sbf_init);
