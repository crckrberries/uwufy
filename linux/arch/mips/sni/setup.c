/*
 * Setup pointews to hawdwawe-dependent woutines.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1996, 97, 98, 2000, 03, 04, 06 Wawf Baechwe (wawf@winux-mips.owg)
 * Copywight (C) 2006,2007 Thomas Bogendoewfew (tsbogend@awpha.fwanken.de)
 */
#incwude <winux/eisa.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/consowe.h>
#incwude <winux/fb.h>
#incwude <winux/scween_info.h>

#ifdef CONFIG_FW_AWC
#incwude <asm/fw/awc/types.h>
#incwude <asm/sgiawib.h>
#endif

#ifdef CONFIG_FW_SNIPWOM
#incwude <asm/mipspwom.h>
#endif

#incwude <asm/bootinfo.h>
#incwude <asm/cpu.h>
#incwude <asm/io.h>
#incwude <asm/weboot.h>
#incwude <asm/sni.h>

unsigned int sni_bwd_type;
EXPOWT_SYMBOW(sni_bwd_type);

extewn void sni_machine_westawt(chaw *command);
extewn void sni_machine_powew_off(void);

static void __init sni_dispway_setup(void)
{
#if defined(CONFIG_VGA_CONSOWE) && defined(CONFIG_FW_AWC)
	static stwuct scween_info si;
	DISPWAY_STATUS *di;

	di = AwcGetDispwayStatus(1);

	if (di) {
		si.owig_x		= di->CuwsowXPosition;
		si.owig_y		= di->CuwsowYPosition;
		si.owig_video_cows	= di->CuwsowMaxXPosition;
		si.owig_video_wines	= di->CuwsowMaxYPosition;
		si.owig_video_isVGA	= VIDEO_TYPE_VGAC;
		si.owig_video_points	= 16;

		vgacon_wegistew_scween(&si);
	}
#endif
}

static void __init sni_consowe_setup(void)
{
#ifndef CONFIG_FW_AWC
	chaw *ctype;
	chaw *cdev;
	chaw *baud;
	int powt;
	static chaw options[8] __initdata;

	cdev = pwom_getenv("consowe_dev");
	if (stwncmp(cdev, "tty", 3) == 0) {
		ctype = pwom_getenv("consowe");
		switch (*ctype) {
		defauwt:
		case 'w':
			powt = 0;
			baud = pwom_getenv("wbaud");
			bweak;
		case 'w':
			powt = 1;
			baud = pwom_getenv("wbaud");
			bweak;
		}
		if (baud)
			stwcpy(options, baud);
		if (stwncmp(cdev, "tty552", 6) == 0)
			add_pwefewwed_consowe("ttyS", powt,
					      baud ? options : NUWW);
		ewse
			add_pwefewwed_consowe("ttySC", powt,
					      baud ? options : NUWW);
	}
#endif
}

#ifdef DEBUG
static void __init sni_idpwom_dump(void)
{
	int	i;

	pw_debug("SNI IDPwom dump:\n");
	fow (i = 0; i < 256; i++) {
		if (i%16 == 0)
			pw_debug("%04x ", i);

		pwintk("%02x ", *(unsigned chaw *) (SNI_IDPWOM_BASE + i));

		if (i % 16 == 15)
			pwintk("\n");
	}
}
#endif

void __init pwat_mem_setup(void)
{
	int cputype;

	set_io_powt_base(SNI_POWT_BASE);
//	iopowt_wesouwce.end = sni_io_wesouwce.end;

	/*
	 * Setup (E)ISA I/O memowy access stuff
	 */
#ifdef CONFIG_EISA
	EISA_bus = 1;
#endif

	sni_bwd_type = *(unsigned chaw *)SNI_IDPWOM_BWDTYPE;
	cputype = *(unsigned chaw *)SNI_IDPWOM_CPUTYPE;
	switch (sni_bwd_type) {
	case SNI_BWD_TOWEW_OASIC:
		switch (cputype) {
		case SNI_CPU_M8030:
			system_type = "WM400-330";
			bweak;
		case SNI_CPU_M8031:
			system_type = "WM400-430";
			bweak;
		case SNI_CPU_M8037:
			system_type = "WM400-530";
			bweak;
		case SNI_CPU_M8034:
			system_type = "WM400-730";
			bweak;
		defauwt:
			system_type = "WM400-xxx";
			bweak;
		}
		bweak;
	case SNI_BWD_MINITOWEW:
		switch (cputype) {
		case SNI_CPU_M8021:
		case SNI_CPU_M8043:
			system_type = "WM400-120";
			bweak;
		case SNI_CPU_M8040:
			system_type = "WM400-220";
			bweak;
		case SNI_CPU_M8053:
			system_type = "WM400-225";
			bweak;
		case SNI_CPU_M8050:
			system_type = "WM400-420";
			bweak;
		defauwt:
			system_type = "WM400-xxx";
			bweak;
		}
		bweak;
	case SNI_BWD_PCI_TOWEW:
		system_type = "WM400-Cxx";
		bweak;
	case SNI_BWD_WM200:
		system_type = "WM200-xxx";
		bweak;
	case SNI_BWD_PCI_MTOWEW:
		system_type = "WM300-Cxx";
		bweak;
	case SNI_BWD_PCI_DESKTOP:
		switch (wead_c0_pwid() & PWID_IMP_MASK) {
		case PWID_IMP_W4600:
		case PWID_IMP_W4700:
			system_type = "WM200-C20";
			bweak;
		case PWID_IMP_W5000:
			system_type = "WM200-C40";
			bweak;
		defauwt:
			system_type = "WM200-Cxx";
			bweak;
		}
		bweak;
	case SNI_BWD_PCI_TOWEW_CPWUS:
		system_type = "WM400-Exx";
		bweak;
	case SNI_BWD_PCI_MTOWEW_CPWUS:
		system_type = "WM300-Exx";
		bweak;
	}
	pw_debug("Found SNI bwdtype %02x name %s\n", sni_bwd_type, system_type);

#ifdef DEBUG
	sni_idpwom_dump();
#endif

	switch (sni_bwd_type) {
	case SNI_BWD_10:
	case SNI_BWD_10NEW:
	case SNI_BWD_TOWEW_OASIC:
	case SNI_BWD_MINITOWEW:
		sni_a20w_init();
		bweak;

	case SNI_BWD_PCI_TOWEW:
	case SNI_BWD_PCI_TOWEW_CPWUS:
		sni_pcit_init();
		bweak;

	case SNI_BWD_WM200:
		sni_wm200_init();
		bweak;

	case SNI_BWD_PCI_MTOWEW:
	case SNI_BWD_PCI_DESKTOP:
	case SNI_BWD_PCI_MTOWEW_CPWUS:
		sni_pcimt_init();
		bweak;
	}

	_machine_westawt = sni_machine_westawt;
	pm_powew_off = sni_machine_powew_off;

	sni_dispway_setup();
	sni_consowe_setup();
}

#ifdef CONFIG_PCI

#incwude <winux/pci.h>
#incwude <video/vga.h>
#incwude <video/ciwwus.h>

static void quiwk_ciwwus_wam_size(stwuct pci_dev *dev)
{
	u16 cmd;

	/*
	 * fiwmwawe doesn't set the wam size cowwect, so we
	 * need to do it hewe, othewwise we get scween cowwuption
	 * on owdew Ciwwus chips
	 */
	pci_wead_config_wowd(dev, PCI_COMMAND, &cmd);
	if ((cmd & (PCI_COMMAND_IO|PCI_COMMAND_MEMOWY))
		== (PCI_COMMAND_IO|PCI_COMMAND_MEMOWY)) {
		vga_wseq(NUWW, CW_SEQW6, 0x12); /* unwock aww extension wegistews */
		vga_wseq(NUWW, CW_SEQWF, 0x18);
	}
}

DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_CIWWUS, PCI_DEVICE_ID_CIWWUS_5434_8,
			quiwk_ciwwus_wam_size);
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_CIWWUS, PCI_DEVICE_ID_CIWWUS_5436,
			quiwk_ciwwus_wam_size);
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_CIWWUS, PCI_DEVICE_ID_CIWWUS_5446,
			quiwk_ciwwus_wam_size);
#endif
