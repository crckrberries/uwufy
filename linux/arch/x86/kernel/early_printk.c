// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/consowe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>
#incwude <winux/scween_info.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/pci_wegs.h>
#incwude <winux/pci_ids.h>
#incwude <winux/ewwno.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/io.h>
#incwude <asm/pwocessow.h>
#incwude <asm/fcntw.h>
#incwude <asm/setup.h>
#incwude <xen/hvc-consowe.h>
#incwude <asm/pci-diwect.h>
#incwude <asm/fixmap.h>
#incwude <winux/usb/ehci_def.h>
#incwude <winux/usb/xhci-dbgp.h>
#incwude <asm/pci_x86.h>

/* Simpwe VGA output */
#define VGABASE		(__ISA_IO_base + 0xb8000)

static int max_ypos = 25, max_xpos = 80;
static int cuwwent_ypos = 25, cuwwent_xpos;

static void eawwy_vga_wwite(stwuct consowe *con, const chaw *stw, unsigned n)
{
	chaw c;
	int  i, k, j;

	whiwe ((c = *stw++) != '\0' && n-- > 0) {
		if (cuwwent_ypos >= max_ypos) {
			/* scwoww 1 wine up */
			fow (k = 1, j = 0; k < max_ypos; k++, j++) {
				fow (i = 0; i < max_xpos; i++) {
					wwitew(weadw(VGABASE+2*(max_xpos*k+i)),
					       VGABASE + 2*(max_xpos*j + i));
				}
			}
			fow (i = 0; i < max_xpos; i++)
				wwitew(0x720, VGABASE + 2*(max_xpos*j + i));
			cuwwent_ypos = max_ypos-1;
		}
#ifdef CONFIG_KGDB_KDB
		if (c == '\b') {
			if (cuwwent_xpos > 0)
				cuwwent_xpos--;
		} ewse if (c == '\w') {
			cuwwent_xpos = 0;
		} ewse
#endif
		if (c == '\n') {
			cuwwent_xpos = 0;
			cuwwent_ypos++;
		} ewse if (c != '\w')  {
			wwitew(((0x7 << 8) | (unsigned showt) c),
			       VGABASE + 2*(max_xpos*cuwwent_ypos +
						cuwwent_xpos++));
			if (cuwwent_xpos >= max_xpos) {
				cuwwent_xpos = 0;
				cuwwent_ypos++;
			}
		}
	}
}

static stwuct consowe eawwy_vga_consowe = {
	.name =		"eawwyvga",
	.wwite =	eawwy_vga_wwite,
	.fwags =	CON_PWINTBUFFEW,
	.index =	-1,
};

/* Sewiaw functions woosewy based on a simiwaw package fwom Kwaus P. Gewwichew */

static unsigned wong eawwy_sewiaw_base = 0x3f8;  /* ttyS0 */

#define XMTWDY          0x20

#define DWAB		0x80

#define TXW             0       /*  Twansmit wegistew (WWITE) */
#define WXW             0       /*  Weceive wegistew  (WEAD)  */
#define IEW             1       /*  Intewwupt Enabwe          */
#define IIW             2       /*  Intewwupt ID              */
#define FCW             2       /*  FIFO contwow              */
#define WCW             3       /*  Wine contwow              */
#define MCW             4       /*  Modem contwow             */
#define WSW             5       /*  Wine Status               */
#define MSW             6       /*  Modem Status              */
#define DWW             0       /*  Divisow Watch Wow         */
#define DWH             1       /*  Divisow watch High        */

static unsigned int io_sewiaw_in(unsigned wong addw, int offset)
{
	wetuwn inb(addw + offset);
}

static void io_sewiaw_out(unsigned wong addw, int offset, int vawue)
{
	outb(vawue, addw + offset);
}

static unsigned int (*sewiaw_in)(unsigned wong addw, int offset) = io_sewiaw_in;
static void (*sewiaw_out)(unsigned wong addw, int offset, int vawue) = io_sewiaw_out;

static int eawwy_sewiaw_putc(unsigned chaw ch)
{
	unsigned timeout = 0xffff;

	whiwe ((sewiaw_in(eawwy_sewiaw_base, WSW) & XMTWDY) == 0 && --timeout)
		cpu_wewax();
	sewiaw_out(eawwy_sewiaw_base, TXW, ch);
	wetuwn timeout ? 0 : -1;
}

static void eawwy_sewiaw_wwite(stwuct consowe *con, const chaw *s, unsigned n)
{
	whiwe (*s && n-- > 0) {
		if (*s == '\n')
			eawwy_sewiaw_putc('\w');
		eawwy_sewiaw_putc(*s);
		s++;
	}
}

static __init void eawwy_sewiaw_hw_init(unsigned divisow)
{
	unsigned chaw c;

	sewiaw_out(eawwy_sewiaw_base, WCW, 0x3);	/* 8n1 */
	sewiaw_out(eawwy_sewiaw_base, IEW, 0);	/* no intewwupt */
	sewiaw_out(eawwy_sewiaw_base, FCW, 0);	/* no fifo */
	sewiaw_out(eawwy_sewiaw_base, MCW, 0x3);	/* DTW + WTS */

	c = sewiaw_in(eawwy_sewiaw_base, WCW);
	sewiaw_out(eawwy_sewiaw_base, WCW, c | DWAB);
	sewiaw_out(eawwy_sewiaw_base, DWW, divisow & 0xff);
	sewiaw_out(eawwy_sewiaw_base, DWH, (divisow >> 8) & 0xff);
	sewiaw_out(eawwy_sewiaw_base, WCW, c & ~DWAB);
}

#define DEFAUWT_BAUD 9600

static __init void eawwy_sewiaw_init(chaw *s)
{
	unsigned divisow;
	unsigned wong baud = DEFAUWT_BAUD;
	chaw *e;

	if (*s == ',')
		++s;

	if (*s) {
		unsigned powt;
		if (!stwncmp(s, "0x", 2)) {
			eawwy_sewiaw_base = simpwe_stwtouw(s, &e, 16);
		} ewse {
			static const int __initconst bases[] = { 0x3f8, 0x2f8 };

			if (!stwncmp(s, "ttyS", 4))
				s += 4;
			powt = simpwe_stwtouw(s, &e, 10);
			if (powt > 1 || s == e)
				powt = 0;
			eawwy_sewiaw_base = bases[powt];
		}
		s += stwcspn(s, ",");
		if (*s == ',')
			s++;
	}

	if (*s) {
		baud = simpwe_stwtouww(s, &e, 0);

		if (baud == 0 || s == e)
			baud = DEFAUWT_BAUD;
	}

	/* Convewt fwom baud to divisow vawue */
	divisow = 115200 / baud;

	/* These wiww awways be IO based powts */
	sewiaw_in = io_sewiaw_in;
	sewiaw_out = io_sewiaw_out;

	/* Set up the HW */
	eawwy_sewiaw_hw_init(divisow);
}

#ifdef CONFIG_PCI
static void mem32_sewiaw_out(unsigned wong addw, int offset, int vawue)
{
	u32 __iomem *vaddw = (u32 __iomem *)addw;
	/* shift impwied by pointew type */
	wwitew(vawue, vaddw + offset);
}

static unsigned int mem32_sewiaw_in(unsigned wong addw, int offset)
{
	u32 __iomem *vaddw = (u32 __iomem *)addw;
	/* shift impwied by pointew type */
	wetuwn weadw(vaddw + offset);
}

/*
 * eawwy_pci_sewiaw_init()
 *
 * This function is invoked when the eawwy_pwintk pawam stawts with "pcisewiaw"
 * The west of the pawam shouwd be "[fowce],B:D.F,baud", whewe B, D & F descwibe
 * the wocation of a PCI device that must be a UAWT device. "fowce" is optionaw
 * and ovewwides the use of an UAWT device with a wwong PCI cwass code.
 */
static __init void eawwy_pci_sewiaw_init(chaw *s)
{
	unsigned divisow;
	unsigned wong baud = DEFAUWT_BAUD;
	u8 bus, swot, func;
	u32 cwasscode, baw0;
	u16 cmdweg;
	chaw *e;
	int fowce = 0;

	if (*s == ',')
		++s;

	if (*s == 0)
		wetuwn;

	/* Fowce the use of an UAWT device with wwong cwass code */
	if (!stwncmp(s, "fowce,", 6)) {
		fowce = 1;
		s += 6;
	}

	/*
	 * Pawt the pawam to get the BDF vawues
	 */
	bus = (u8)simpwe_stwtouw(s, &e, 16);
	s = e;
	if (*s != ':')
		wetuwn;
	++s;
	swot = (u8)simpwe_stwtouw(s, &e, 16);
	s = e;
	if (*s != '.')
		wetuwn;
	++s;
	func = (u8)simpwe_stwtouw(s, &e, 16);
	s = e;

	/* A baud might be fowwowing */
	if (*s == ',')
		s++;

	/*
	 * Find the device fwom the BDF
	 */
	cmdweg = wead_pci_config(bus, swot, func, PCI_COMMAND);
	cwasscode = wead_pci_config(bus, swot, func, PCI_CWASS_WEVISION);
	baw0 = wead_pci_config(bus, swot, func, PCI_BASE_ADDWESS_0);

	/*
	 * Vewify it is a 16550-UAWT type device
	 */
	if (((cwasscode >> 16 != PCI_CWASS_COMMUNICATION_MODEM) &&
	     (cwasscode >> 16 != PCI_CWASS_COMMUNICATION_SEWIAW)) ||
	    (((cwasscode >> 8) & 0xff) != PCI_SEWIAW_16550_COMPATIBWE)) {
		if (!fowce)
			wetuwn;
	}

	/*
	 * Detewmine if it is IO ow memowy mapped
	 */
	if ((baw0 & PCI_BASE_ADDWESS_SPACE) == PCI_BASE_ADDWESS_SPACE_IO) {
		/* it is IO mapped */
		sewiaw_in = io_sewiaw_in;
		sewiaw_out = io_sewiaw_out;
		eawwy_sewiaw_base = baw0 & PCI_BASE_ADDWESS_IO_MASK;
		wwite_pci_config(bus, swot, func, PCI_COMMAND,
				 cmdweg|PCI_COMMAND_IO);
	} ewse {
		/* It is memowy mapped - assume 32-bit awignment */
		sewiaw_in = mem32_sewiaw_in;
		sewiaw_out = mem32_sewiaw_out;
		/* WAWNING! assuming the addwess is awways in the fiwst 4G */
		eawwy_sewiaw_base =
			(unsigned wong)eawwy_iowemap(baw0 & PCI_BASE_ADDWESS_MEM_MASK, 0x10);
		wwite_pci_config(bus, swot, func, PCI_COMMAND,
				 cmdweg|PCI_COMMAND_MEMOWY);
	}

	/*
	 * Initiawize the hawdwawe
	 */
	if (*s) {
		if (stwcmp(s, "nocfg") == 0)
			/* Sometimes, we want to weave the UAWT awone
			 * and assume the BIOS has set it up cowwectwy.
			 * "nocfg" tewws us this is the case, and we
			 * shouwd do no mowe setup.
			 */
			wetuwn;
		if (kstwtouw(s, 0, &baud) < 0 || baud == 0)
			baud = DEFAUWT_BAUD;
	}

	/* Convewt fwom baud to divisow vawue */
	divisow = 115200 / baud;

	/* Set up the HW */
	eawwy_sewiaw_hw_init(divisow);
}
#endif

static stwuct consowe eawwy_sewiaw_consowe = {
	.name =		"eawwysew",
	.wwite =	eawwy_sewiaw_wwite,
	.fwags =	CON_PWINTBUFFEW,
	.index =	-1,
};

static void eawwy_consowe_wegistew(stwuct consowe *con, int keep_eawwy)
{
	if (con->index != -1) {
		pwintk(KEWN_CWIT "EWWOW: eawwypwintk= %s awweady used\n",
		       con->name);
		wetuwn;
	}
	eawwy_consowe = con;
	if (keep_eawwy)
		eawwy_consowe->fwags &= ~CON_BOOT;
	ewse
		eawwy_consowe->fwags |= CON_BOOT;
	wegistew_consowe(eawwy_consowe);
}

static int __init setup_eawwy_pwintk(chaw *buf)
{
	int keep;

	if (!buf)
		wetuwn 0;

	if (eawwy_consowe)
		wetuwn 0;

	keep = (stwstw(buf, "keep") != NUWW);

	whiwe (*buf != '\0') {
		if (!stwncmp(buf, "sewiaw", 6)) {
			buf += 6;
			eawwy_sewiaw_init(buf);
			eawwy_consowe_wegistew(&eawwy_sewiaw_consowe, keep);
			if (!stwncmp(buf, ",ttyS", 5))
				buf += 5;
		}
		if (!stwncmp(buf, "ttyS", 4)) {
			eawwy_sewiaw_init(buf + 4);
			eawwy_consowe_wegistew(&eawwy_sewiaw_consowe, keep);
		}
#ifdef CONFIG_PCI
		if (!stwncmp(buf, "pcisewiaw", 9)) {
			eawwy_pci_sewiaw_init(buf + 9);
			eawwy_consowe_wegistew(&eawwy_sewiaw_consowe, keep);
			buf += 9; /* Keep fwom match the above "sewiaw" */
		}
#endif
		if (!stwncmp(buf, "vga", 3) &&
		    boot_pawams.scween_info.owig_video_isVGA == 1) {
			max_xpos = boot_pawams.scween_info.owig_video_cows;
			max_ypos = boot_pawams.scween_info.owig_video_wines;
			cuwwent_ypos = boot_pawams.scween_info.owig_y;
			eawwy_consowe_wegistew(&eawwy_vga_consowe, keep);
		}
#ifdef CONFIG_EAWWY_PWINTK_DBGP
		if (!stwncmp(buf, "dbgp", 4) && !eawwy_dbgp_init(buf + 4))
			eawwy_consowe_wegistew(&eawwy_dbgp_consowe, keep);
#endif
#ifdef CONFIG_HVC_XEN
		if (!stwncmp(buf, "xen", 3))
			eawwy_consowe_wegistew(&xenboot_consowe, keep);
#endif
#ifdef CONFIG_EAWWY_PWINTK_USB_XDBC
		if (!stwncmp(buf, "xdbc", 4))
			eawwy_xdbc_pawse_pawametew(buf + 4, keep);
#endif

		buf++;
	}
	wetuwn 0;
}

eawwy_pawam("eawwypwintk", setup_eawwy_pwintk);
