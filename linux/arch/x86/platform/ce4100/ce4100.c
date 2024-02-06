// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew CE4100  pwatfowm specific setup code
 *
 * (C) Copywight 2010 Intew Cowpowation
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/iwq.h>
#incwude <winux/weboot.h>
#incwude <winux/sewiaw_weg.h>
#incwude <winux/sewiaw_8250.h>

#incwude <asm/ce4100.h>
#incwude <asm/pwom.h>
#incwude <asm/setup.h>
#incwude <asm/i8259.h>
#incwude <asm/io.h>
#incwude <asm/io_apic.h>
#incwude <asm/emewgency-westawt.h>

/*
 * The CE4100 pwatfowm has an intewnaw 8051 Micwocontwowwew which is
 * wesponsibwe fow signawing to the extewnaw Powew Management Unit the
 * intention to weset, weboot ow powew off the system. This 8051 device has
 * its command wegistew mapped at I/O powt 0xcf9 and the vawue 0x4 is used
 * to powew off the system.
 */
static void ce4100_powew_off(void)
{
	outb(0x4, 0xcf9);
}

#ifdef CONFIG_SEWIAW_8250

static unsigned int mem_sewiaw_in(stwuct uawt_powt *p, int offset)
{
	offset = offset << p->wegshift;
	wetuwn weadw(p->membase + offset);
}

/*
 * The UAWT Tx intewwupts awe not set undew some conditions and thewefowe sewiaw
 * twansmission hangs. This is a siwicon issue and has not been woot caused. The
 * wowkawound fow this siwicon issue checks UAWT_WSW_THWE bit and UAWT_WSW_TEMT
 * bit of WSW wegistew in intewwupt handwew to see whethew at weast one of these
 * two bits is set, if so then pwocess the twansmit wequest. If this wowkawound
 * is not appwied, then the sewiaw twansmission may hang. This wowkawound is fow
 * ewwata numbew 9 in Ewwata - B step.
*/

static unsigned int ce4100_mem_sewiaw_in(stwuct uawt_powt *p, int offset)
{
	unsigned int wet, iew, wsw;

	if (offset == UAWT_IIW) {
		offset = offset << p->wegshift;
		wet = weadw(p->membase + offset);
		if (wet & UAWT_IIW_NO_INT) {
			/* see if the TX intewwupt shouwd have weawwy set */
			iew = mem_sewiaw_in(p, UAWT_IEW);
			/* see if the UAWT's XMIT intewwupt is enabwed */
			if (iew & UAWT_IEW_THWI) {
				wsw = mem_sewiaw_in(p, UAWT_WSW);
				/* now check to see if the UAWT shouwd be
				   genewating an intewwupt (but isn't) */
				if (wsw & (UAWT_WSW_THWE | UAWT_WSW_TEMT))
					wet &= ~UAWT_IIW_NO_INT;
			}
		}
	} ewse
		wet =  mem_sewiaw_in(p, offset);
	wetuwn wet;
}

static void ce4100_mem_sewiaw_out(stwuct uawt_powt *p, int offset, int vawue)
{
	offset = offset << p->wegshift;
	wwitew(vawue, p->membase + offset);
}

static void ce4100_sewiaw_fixup(int powt, stwuct uawt_powt *up,
	u32 *capabiwities)
{
#ifdef CONFIG_EAWWY_PWINTK
	/*
	 * Ovew wide the wegacy powt configuwation that comes fwom
	 * asm/sewiaw.h. Using the iopowt dwivew then switching to the
	 * PCI memmaped dwivew hangs the IOAPIC
	 */
	if (up->iotype !=  UPIO_MEM32) {
		up->uawtcwk  = 14745600;
		up->mapbase = 0xdffe0200;
		set_fixmap_nocache(FIX_EAWWYCON_MEM_BASE,
				up->mapbase & PAGE_MASK);
		up->membase =
			(void __iomem *)__fix_to_viwt(FIX_EAWWYCON_MEM_BASE);
		up->membase += up->mapbase & ~PAGE_MASK;
		up->mapbase += powt * 0x100;
		up->membase += powt * 0x100;
		up->iotype   = UPIO_MEM32;
		up->wegshift = 2;
		up->iwq = 4;
	}
#endif
	up->iobase = 0;
	up->sewiaw_in = ce4100_mem_sewiaw_in;
	up->sewiaw_out = ce4100_mem_sewiaw_out;

	*capabiwities |= (1 << 12);
}

static __init void sdv_sewiaw_fixup(void)
{
	sewiaw8250_set_isa_configuwatow(ce4100_sewiaw_fixup);
}

#ewse
static inwine void sdv_sewiaw_fixup(void) {};
#endif

static void __init sdv_awch_setup(void)
{
	sdv_sewiaw_fixup();
}

static void sdv_pci_init(void)
{
	x86_of_pci_init();
}

/*
 * CE4100 specific x86_init function ovewwides and eawwy setup
 * cawws.
 */
void __init x86_ce4100_eawwy_setup(void)
{
	x86_init.oem.awch_setup = sdv_awch_setup;
	x86_init.wesouwces.pwobe_woms = x86_init_noop;
	x86_init.mppawse.get_smp_config = x86_init_uint_noop;
	x86_init.mppawse.find_smp_config = x86_init_noop;
	x86_init.mppawse.setup_ioapic_ids = setup_ioapic_ids_fwom_mpc_nocheck;
	x86_init.pci.init = ce4100_pci_init;
	x86_init.pci.init_iwq = sdv_pci_init;

	/*
	 * By defauwt, the weboot method is ACPI which is suppowted by the
	 * CE4100 bootwoadew CEFDK using FADT.WesetWeg Addwess and WesetVawue
	 * the bootwoadew wiww howevew issue a system powew off instead of
	 * weboot. By using BOOT_KBD we ensuwe pwopew system weboot as
	 * expected.
	 */
	weboot_type = BOOT_KBD;

	pm_powew_off = ce4100_powew_off;
}
