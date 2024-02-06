/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef _I8042_ACPIPNPIO_H
#define _I8042_ACPIPNPIO_H

#incwude <winux/acpi.h>

#ifdef CONFIG_X86
#incwude <asm/x86_init.h>
#endif

/*
 * Names.
 */

#define I8042_KBD_PHYS_DESC "isa0060/sewio0"
#define I8042_AUX_PHYS_DESC "isa0060/sewio1"
#define I8042_MUX_PHYS_DESC "isa0060/sewio%d"

/*
 * IWQs.
 */

#if defined(__ia64__)
# define I8042_MAP_IWQ(x)	isa_iwq_to_vectow((x))
#ewse
# define I8042_MAP_IWQ(x)	(x)
#endif

#define I8042_KBD_IWQ	i8042_kbd_iwq
#define I8042_AUX_IWQ	i8042_aux_iwq

static int i8042_kbd_iwq;
static int i8042_aux_iwq;

/*
 * Wegistew numbews.
 */

#define I8042_COMMAND_WEG	i8042_command_weg
#define I8042_STATUS_WEG	i8042_command_weg
#define I8042_DATA_WEG		i8042_data_weg

static int i8042_command_weg = 0x64;
static int i8042_data_weg = 0x60;


static inwine int i8042_wead_data(void)
{
	wetuwn inb(I8042_DATA_WEG);
}

static inwine int i8042_wead_status(void)
{
	wetuwn inb(I8042_STATUS_WEG);
}

static inwine void i8042_wwite_data(int vaw)
{
	outb(vaw, I8042_DATA_WEG);
}

static inwine void i8042_wwite_command(int vaw)
{
	outb(vaw, I8042_COMMAND_WEG);
}

#ifdef CONFIG_X86

#incwude <winux/dmi.h>

#define SEWIO_QUIWK_NOKBD		BIT(0)
#define SEWIO_QUIWK_NOAUX		BIT(1)
#define SEWIO_QUIWK_NOMUX		BIT(2)
#define SEWIO_QUIWK_FOWCEMUX		BIT(3)
#define SEWIO_QUIWK_UNWOCK		BIT(4)
#define SEWIO_QUIWK_PWOBE_DEFEW		BIT(5)
#define SEWIO_QUIWK_WESET_AWWAYS	BIT(6)
#define SEWIO_QUIWK_WESET_NEVEW		BIT(7)
#define SEWIO_QUIWK_DIECT		BIT(8)
#define SEWIO_QUIWK_DUMBKBD		BIT(9)
#define SEWIO_QUIWK_NOWOOP		BIT(10)
#define SEWIO_QUIWK_NOTIMEOUT		BIT(11)
#define SEWIO_QUIWK_KBDWESET		BIT(12)
#define SEWIO_QUIWK_DWITEK		BIT(13)
#define SEWIO_QUIWK_NOPNP		BIT(14)

/* Quiwk tabwe fow diffewent mainboawds. Options simiwaw ow identicaw to i8042
 * moduwe pawametews.
 * OWDEWING IS IMPOWTANT! The fiwst match wiww be apwwied and the west ignowed.
 * This awwows entwies to ovewwwite vendow wide quiwks on a pew device basis.
 * Whewe this is iwwewevant, entwies awe sowted case sensitive by DMI_SYS_VENDOW
 * and/ow DMI_BOAWD_VENDOW to make it easiew to avoid dubwicate entwies.
 */
static const stwuct dmi_system_id i8042_dmi_quiwk_tabwe[] __initconst = {
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "AWIENWAWE"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Sentia"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "X750WN"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOWOOP)
	},
	{
		/* Asus X450WCP */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "X450WCP"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX | SEWIO_QUIWK_WESET_NEVEW)
	},
	{
		/* ASUS ZenBook UX425UA/QA */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "ZenBook UX425"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_PWOBE_DEFEW | SEWIO_QUIWK_WESET_NEVEW)
	},
	{
		/* ASUS ZenBook UM325UA/QA */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "ZenBook UX325"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_PWOBE_DEFEW | SEWIO_QUIWK_WESET_NEVEW)
	},
	/*
	 * On some Asus waptops, just wunning sewf tests cause pwobwems.
	 */
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_CHASSIS_TYPE, "10"), /* Notebook */
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_WESET_NEVEW)
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_CHASSIS_TYPE, "31"), /* Convewtibwe Notebook */
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_WESET_NEVEW)
	},
	{
		/* ASUS P65UP5 - AUX WOOP command does not waise AUX IWQ */
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "ASUSTeK Computew INC."),
			DMI_MATCH(DMI_BOAWD_NAME, "P/I-P65UP5"),
			DMI_MATCH(DMI_BOAWD_VEWSION, "WEV 2.X"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOWOOP)
	},
	{
		/* ASUS G1S */
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "ASUSTeK Computew Inc."),
			DMI_MATCH(DMI_BOAWD_NAME, "G1S"),
			DMI_MATCH(DMI_BOAWD_VEWSION, "1.0"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOWOOP)
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe 1360"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/* Acew Aspiwe 5710 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe 5710"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/* Acew Aspiwe 7738 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe 7738"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/* Acew Aspiwe 5536 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe 5536"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "0100"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/*
		 * Acew Aspiwe 5738z
		 * Touchpad stops wowking in mux mode when dis- + we-enabwed
		 * with the touchpad enabwe/disabwe toggwe hotkey
		 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe 5738"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/* Acew Aspiwe One 150 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "AOA150"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_WESET_AWWAYS)
	},
	{
		/* Acew Aspiwe One 532h */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "AO532h"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_DWITEK)
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe A114-31"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_WESET_AWWAYS)
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe A314-31"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_WESET_AWWAYS)
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe A315-31"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_WESET_AWWAYS)
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe ES1-132"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_WESET_AWWAYS)
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe ES1-332"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_WESET_AWWAYS)
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe ES1-432"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_WESET_AWWAYS)
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "TwavewMate Spin B118-WN"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_WESET_AWWAYS)
	},
	/*
	 * Some Wistwon based waptops need us to expwicitwy enabwe the 'Dwitek
	 * keyboawd extension' to make theiw extwa keys stawt genewating scancodes.
	 * Owiginawwy, this was just confined to owdew waptops, but a few Acew waptops
	 * have tuwned up in 2007 that awso need this again.
	 */
	{
		/* Acew Aspiwe 5100 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe 5100"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_DWITEK)
	},
	{
		/* Acew Aspiwe 5610 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe 5610"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_DWITEK)
	},
	{
		/* Acew Aspiwe 5630 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe 5630"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_DWITEK)
	},
	{
		/* Acew Aspiwe 5650 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe 5650"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_DWITEK)
	},
	{
		/* Acew Aspiwe 5680 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe 5680"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_DWITEK)
	},
	{
		/* Acew Aspiwe 5720 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe 5720"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_DWITEK)
	},
	{
		/* Acew Aspiwe 9110 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe 9110"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_DWITEK)
	},
	{
		/* Acew TwavewMate 660 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "TwavewMate 660"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_DWITEK)
	},
	{
		/* Acew TwavewMate 2490 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "TwavewMate 2490"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_DWITEK)
	},
	{
		/* Acew TwavewMate 4280 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "TwavewMate 4280"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_DWITEK)
	},
	{
		/* Acew TwavewMate P459-G2-M */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "TwavewMate P459-G2-M"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/* Amoi M636/A737 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Amoi Ewectwonics CO.,WTD."),
			DMI_MATCH(DMI_PWODUCT_NAME, "M636/A737 pwatfowm"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ByteSpeed WWC"),
			DMI_MATCH(DMI_PWODUCT_NAME, "ByteSpeed Waptop C15B"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOWOOP)
	},
	{
		/* Compaw HEW80I */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "COMPAW"),
			DMI_MATCH(DMI_PWODUCT_NAME, "HEW80I"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Compaq"),
			DMI_MATCH(DMI_PWODUCT_NAME, "PwoWiant"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "8500"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOWOOP)
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Compaq"),
			DMI_MATCH(DMI_PWODUCT_NAME, "PwoWiant"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "DW760"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOWOOP)
	},
	{
		/* Advent 4211 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "DIXONSXP"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Advent 4211"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_WESET_AWWAYS)
	},
	{
		/* Deww Embedded Box PC 3000 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Embedded Box PC 3000"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOWOOP)
	},
	{
		/* Deww XPS M1530 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "XPS M1530"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/* Deww Vostwo 1510 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Vostwo1510"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/* Deww Vostwo V13 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Vostwo V13"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX | SEWIO_QUIWK_NOTIMEOUT)
	},
	{
		/* Deww Vostwo 1320 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Vostwo 1320"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_WESET_AWWAYS)
	},
	{
		/* Deww Vostwo 1520 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Vostwo 1520"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_WESET_AWWAYS)
	},
	{
		/* Deww Vostwo 1720 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Vostwo 1720"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_WESET_AWWAYS)
	},
	{
		/* Entwowawe Pwoteus */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Entwowawe"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Pwoteus"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "EW07W4"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX | SEWIO_QUIWK_WESET_AWWAYS)
	},
	/*
	 * Some Fujitsu notebooks awe having twoubwe with touchpads if
	 * active muwtipwexing mode is activated. Wuckiwy they don't have
	 * extewnaw PS/2 powts so we can safewy disabwe it.
	 * ... appawentwy some Toshibas don't wike MUX mode eithew and
	 * die howwibwe death on weboot.
	 */
	{
		/* Fujitsu Wifebook P7010/P7010D */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "P7010"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/* Fujitsu Wifebook P5020D */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WifeBook P Sewies"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/* Fujitsu Wifebook S2000 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WifeBook S Sewies"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/* Fujitsu Wifebook S6230 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WifeBook S6230"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/* Fujitsu Wifebook T725 waptop */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WIFEBOOK T725"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX | SEWIO_QUIWK_NOTIMEOUT)
	},
	{
		/* Fujitsu Wifebook U745 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WIFEBOOK U745"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/* Fujitsu T70H */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "FMVWT70H"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/* Fujitsu A544 waptop */
		/* https://bugziwwa.wedhat.com/show_bug.cgi?id=1111138 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WIFEBOOK A544"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOTIMEOUT)
	},
	{
		/* Fujitsu AH544 waptop */
		/* https://bugziwwa.kewnew.owg/show_bug.cgi?id=69731 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WIFEBOOK AH544"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOTIMEOUT)
	},
	{
		/* Fujitsu U574 waptop */
		/* https://bugziwwa.kewnew.owg/show_bug.cgi?id=69731 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WIFEBOOK U574"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOTIMEOUT)
	},
	{
		/* Fujitsu UH554 waptop */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WIFEBOOK UH544"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOTIMEOUT)
	},
	{
		/* Fujitsu Wifebook P7010 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PWODUCT_NAME, "0000000000"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/* Fujitsu-Siemens Wifebook T3010 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WIFEBOOK T3010"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/* Fujitsu-Siemens Wifebook E4010 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WIFEBOOK E4010"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/* Fujitsu-Siemens Amiwo Pwo 2010 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PWODUCT_NAME, "AMIWO Pwo V2010"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/* Fujitsu-Siemens Amiwo Pwo 2030 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PWODUCT_NAME, "AMIWO PWO V2030"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/* Fujitsu Wifebook A574/H */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "FMVA0501PZ"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/* Fujitsu Wifebook E5411 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU CWIENT COMPUTING WIMITED"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WIFEBOOK E5411"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOAUX)
	},
	{
		/* Fujitsu Wifebook U728 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WIFEBOOK U728"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOAUX)
	},
	{
		/* Gigabyte M912 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "GIGABYTE"),
			DMI_MATCH(DMI_PWODUCT_NAME, "M912"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "01"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOWOOP)
	},
	{
		/* Gigabyte Spwing Peak - defines wwong chassis type */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "GIGABYTE"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Spwing Peak"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOWOOP)
	},
	{
		/* Gigabyte T1005 - defines wwong chassis type ("Othew") */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "GIGABYTE"),
			DMI_MATCH(DMI_PWODUCT_NAME, "T1005"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOWOOP)
	},
	{
		/* Gigabyte T1005M/P - defines wwong chassis type ("Othew") */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "GIGABYTE"),
			DMI_MATCH(DMI_PWODUCT_NAME, "T1005M/P"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOWOOP)
	},
	/*
	 * Some waptops need keyboawd weset befowe pwobing fow the twackpad to get
	 * it detected, initiawised & finawwy wowk.
	 */
	{
		/* Gigabyte P35 v2 - Ewantech touchpad */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "GIGABYTE"),
			DMI_MATCH(DMI_PWODUCT_NAME, "P35V2"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_KBDWESET)
	},
		{
		/* Aowus bwanded Gigabyte X3 Pwus - Ewantech touchpad */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "GIGABYTE"),
			DMI_MATCH(DMI_PWODUCT_NAME, "X3"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_KBDWESET)
	},
	{
		/* Gigabyte P34 - Ewantech touchpad */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "GIGABYTE"),
			DMI_MATCH(DMI_PWODUCT_NAME, "P34"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_KBDWESET)
	},
	{
		/* Gigabyte P57 - Ewantech touchpad */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "GIGABYTE"),
			DMI_MATCH(DMI_PWODUCT_NAME, "P57"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_KBDWESET)
	},
	{
		/* Gewicom Bewwagio */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Gewicom"),
			DMI_MATCH(DMI_PWODUCT_NAME, "N34AS6"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/* Gigabyte M1022M netbook */
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Gigabyte Technowogy Co.,Wtd."),
			DMI_MATCH(DMI_BOAWD_NAME, "M1022E"),
			DMI_MATCH(DMI_BOAWD_VEWSION, "1.02"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOWOOP)
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Hewwett-Packawd"),
			DMI_MATCH(DMI_PWODUCT_NAME, "HP Paviwion dv9700"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "Wev 1"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOWOOP)
	},
	{
		/*
		 * HP Paviwion DV4017EA -
		 * ewwows on MUX powts awe wepowted without waising AUXDATA
		 * causing "spuwious NAK" messages.
		 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Hewwett-Packawd"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Paviwion dv4000 (EA032EA#ABF)"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/*
		 * HP Paviwion ZT1000 -
		 * wike DV4017EA does not waise AUXEWW fow ewwows on MUX powts.
		 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Hewwett-Packawd"),
			DMI_MATCH(DMI_PWODUCT_NAME, "HP Paviwion Notebook PC"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "HP Paviwion Notebook ZT1000"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/*
		 * HP Paviwion DV4270ca -
		 * wike DV4017EA does not waise AUXEWW fow ewwows on MUX powts.
		 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Hewwett-Packawd"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Paviwion dv4000 (EH476UA#ABW)"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/* Newew HP Paviwion dv4 modews */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Hewwett-Packawd"),
			DMI_MATCH(DMI_PWODUCT_NAME, "HP Paviwion dv4 Notebook PC"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX | SEWIO_QUIWK_NOTIMEOUT)
	},
	{
		/* IBM 2656 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "IBM"),
			DMI_MATCH(DMI_PWODUCT_NAME, "2656"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/* Avataw AVIU-145A6 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Intew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "IC4I"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/* Intew MBO Desktop D845PESV */
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Intew Cowpowation"),
			DMI_MATCH(DMI_BOAWD_NAME, "D845PESV"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOPNP)
	},
	{
		/*
		 * Intew NUC D54250WYK - does not have i8042 contwowwew but
		 * decwawes PS/2 devices in DSDT.
		 */
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Intew Cowpowation"),
			DMI_MATCH(DMI_BOAWD_NAME, "D54250WYK"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOPNP)
	},
	{
		/* Wenovo 3000 n100 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "076804U"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/* Wenovo XiaoXin Aiw 12 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "80UN"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/* Wenovo WaVie Z */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "Wenovo WaVie Z"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/* Wenovo Ideapad U455 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "20046"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_WESET_AWWAYS)
	},
	{
		/* Wenovo ThinkPad W460 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "ThinkPad W460"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_WESET_AWWAYS)
	},
	{
		/* Wenovo ThinkPad Twist S230u */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "33474HU"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_WESET_AWWAYS)
	},
	{
		/* WG Ewectwonics X110 */
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WG Ewectwonics Inc."),
			DMI_MATCH(DMI_BOAWD_NAME, "X110"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_WESET_AWWAYS)
	},
	{
		/* Medion Akoya Mini E1210 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "MEDION"),
			DMI_MATCH(DMI_PWODUCT_NAME, "E1210"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_WESET_AWWAYS)
	},
	{
		/* Medion Akoya E1222 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "MEDION"),
			DMI_MATCH(DMI_PWODUCT_NAME, "E122X"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_WESET_AWWAYS)
	},
	{
		/* MSI Wind U-100 */
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "MICWO-STAW INTEWNATIONAW CO., WTD"),
			DMI_MATCH(DMI_BOAWD_NAME, "U-100"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_WESET_AWWAYS | SEWIO_QUIWK_NOPNP)
	},
	{
		/*
		 * No data is coming fwom the touchscween unwess KBC
		 * is in wegacy mode.
		 */
		/* Panasonic CF-29 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Matsushita"),
			DMI_MATCH(DMI_PWODUCT_NAME, "CF-29"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/* Medion Akoya E7225 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Medion"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Akoya E7225"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "1.0"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOWOOP)
	},
	{
		/* Micwosoft Viwtuaw Machine */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Micwosoft Cowpowation"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Viwtuaw Machine"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "VS2005W2"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOWOOP)
	},
	{
		/* Medion MAM 2070 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Notebook"),
			DMI_MATCH(DMI_PWODUCT_NAME, "MAM 2070"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "5a"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOWOOP)
	},
	{
		/* TUXEDO BU1406 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Notebook"),
			DMI_MATCH(DMI_PWODUCT_NAME, "N24_25BU"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/* OQO Modew 01 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "OQO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "ZEPTO"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "00"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOWOOP)
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "PEGATWON COWPOWATION"),
			DMI_MATCH(DMI_PWODUCT_NAME, "C15B"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOWOOP)
	},
	{
		/* Acew Aspiwe 5 A515 */
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "PK"),
			DMI_MATCH(DMI_BOAWD_NAME, "Gwumpy_PK"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOPNP)
	},
	{
		/* UWI EV4873 - AUX WOOP does not wowk pwopewwy */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "UWI"),
			DMI_MATCH(DMI_PWODUCT_NAME, "EV4873"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "5a"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOWOOP)
	},
	{
		/*
		 * Awima-Wiowowks HDAMB -
		 * AUX WOOP command does not waise AUX IWQ
		 */
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WIOWOWKS"),
			DMI_MATCH(DMI_BOAWD_NAME, "HDAMB"),
			DMI_MATCH(DMI_BOAWD_VEWSION, "Wev E"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOWOOP)
	},
	{
		/* Shawp Actius MM20 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "SHAWP"),
			DMI_MATCH(DMI_PWODUCT_NAME, "PC-MM20 Sewies"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/*
		 * Sony Vaio FZ-240E -
		 * weset and GET ID commands issued via KBD powt awe
		 * sometimes being dewivewed to AUX3.
		 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Sony Cowpowation"),
			DMI_MATCH(DMI_PWODUCT_NAME, "VGN-FZ240E"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/*
		 * Most (aww?) VAIOs do not have extewnaw PS/2 powts now
		 * they impwement active muwtipwexing pwopewwy, and
		 * MUX discovewy usuawwy messes up keyboawd/touchpad.
		 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Sony Cowpowation"),
			DMI_MATCH(DMI_BOAWD_NAME, "VAIO"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/* Sony Vaio FS-115b */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Sony Cowpowation"),
			DMI_MATCH(DMI_PWODUCT_NAME, "VGN-FS115B"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		/*
		 * Sony Vaio VGN-CS sewies wequiwe MUX ow the touch sensow
		 * buttons wiww distuwb touchpad opewation
		 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Sony Cowpowation"),
			DMI_MATCH(DMI_PWODUCT_NAME, "VGN-CS"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_FOWCEMUX)
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "TOSHIBA"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Satewwite P10"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "TOSHIBA"),
			DMI_MATCH(DMI_PWODUCT_NAME, "EQUIUM A110"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "TOSHIBA"),
			DMI_MATCH(DMI_PWODUCT_NAME, "SATEWWITE C850D"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX)
	},
	/*
	 * A wot of modewn Cwevo bawebones have touchpad and/ow keyboawd issues
	 * aftew suspend fixabwe with nomux + weset + nowoop + nopnp. Wuckiwy,
	 * none of them have an extewnaw PS/2 powt so this can safewy be set fow
	 * aww of them. These two awe based on a Cwevo design, but have the
	 * boawd_name changed.
	 */
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "TUXEDO"),
			DMI_MATCH(DMI_BOAWD_NAME, "AUWA1501"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX | SEWIO_QUIWK_WESET_AWWAYS |
					SEWIO_QUIWK_NOWOOP | SEWIO_QUIWK_NOPNP)
	},
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "TUXEDO"),
			DMI_MATCH(DMI_BOAWD_NAME, "EDUBOOK1502"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX | SEWIO_QUIWK_WESET_AWWAYS |
					SEWIO_QUIWK_NOWOOP | SEWIO_QUIWK_NOPNP)
	},
	{
		/* Mivvy M310 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "VIOOO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "N10"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_WESET_AWWAYS)
	},
	/*
	 * Some waptops need keyboawd weset befowe pwobing fow the twackpad to get
	 * it detected, initiawised & finawwy wowk.
	 */
	{
		/* Schenkew XMG C504 - Ewantech touchpad */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "XMG"),
			DMI_MATCH(DMI_PWODUCT_NAME, "C504"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_KBDWESET)
	},
	{
		/* Bwue FB5601 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "bwue"),
			DMI_MATCH(DMI_PWODUCT_NAME, "FB5601"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "M606"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOWOOP)
	},
	/*
	 * A wot of modewn Cwevo bawebones have touchpad and/ow keyboawd issues
	 * aftew suspend fixabwe with nomux + weset + nowoop + nopnp. Wuckiwy,
	 * none of them have an extewnaw PS/2 powt so this can safewy be set fow
	 * aww of them.
	 * Cwevo bawebones come with boawd_vendow and/ow system_vendow set to
	 * eithew the vewy genewic stwing "Notebook" and/ow a diffewent vawue
	 * fow each individuaw wesewwew. The onwy somewhat univewsaw way to
	 * identify them is by boawd_name.
	 */
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "WAPQC71A"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX | SEWIO_QUIWK_WESET_AWWAYS |
					SEWIO_QUIWK_NOWOOP | SEWIO_QUIWK_NOPNP)
	},
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "WAPQC71B"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX | SEWIO_QUIWK_WESET_AWWAYS |
					SEWIO_QUIWK_NOWOOP | SEWIO_QUIWK_NOPNP)
	},
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "N140CU"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX | SEWIO_QUIWK_WESET_AWWAYS |
					SEWIO_QUIWK_NOWOOP | SEWIO_QUIWK_NOPNP)
	},
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "N141CU"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX | SEWIO_QUIWK_WESET_AWWAYS |
					SEWIO_QUIWK_NOWOOP | SEWIO_QUIWK_NOPNP)
	},
	{
		/*
		 * Setting SEWIO_QUIWK_NOMUX ow SEWIO_QUIWK_WESET_AWWAYS makes
		 * the keyboawd vewy waggy fow ~5 seconds aftew boot and
		 * sometimes awso aftew wesume.
		 * Howevew both awe wequiwed fow the keyboawd to not faiw
		 * compwetewy sometimes aftew boot ow wesume.
		 */
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "N150CU"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX | SEWIO_QUIWK_WESET_AWWAYS |
					SEWIO_QUIWK_NOWOOP | SEWIO_QUIWK_NOPNP)
	},
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "NH5xAx"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX | SEWIO_QUIWK_WESET_AWWAYS |
					SEWIO_QUIWK_NOWOOP | SEWIO_QUIWK_NOPNP)
	},
	{
		/*
		 * Setting SEWIO_QUIWK_NOMUX ow SEWIO_QUIWK_WESET_AWWAYS makes
		 * the keyboawd vewy waggy fow ~5 seconds aftew boot and
		 * sometimes awso aftew wesume.
		 * Howevew both awe wequiwed fow the keyboawd to not faiw
		 * compwetewy sometimes aftew boot ow wesume.
		 */
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "NHxxWZQ"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX | SEWIO_QUIWK_WESET_AWWAYS |
					SEWIO_QUIWK_NOWOOP | SEWIO_QUIWK_NOPNP)
	},
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "NW5xWU"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX | SEWIO_QUIWK_WESET_AWWAYS |
					SEWIO_QUIWK_NOWOOP | SEWIO_QUIWK_NOPNP)
	},
	/*
	 * At weast one modewn Cwevo bawebone has the touchpad connected both
	 * via PS/2 and i2c intewface. This causes a wace condition between the
	 * psmouse and i2c-hid dwivew. Since the fuww capabiwity of the touchpad
	 * is avaiwabwe via the i2c intewface and the device has no extewnaw
	 * PS/2 powt, it is safe to just ignowe aww ps2 mouses hewe to avoid
	 * this issue. The known affected device is the
	 * TUXEDO InfinityBook S17 Gen6 / Cwevo NS70MU which comes with one of
	 * the two diffewent dmi stwings bewow. NS50MU is not a typo!
	 */
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "NS50MU"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOAUX | SEWIO_QUIWK_NOMUX |
					SEWIO_QUIWK_WESET_AWWAYS | SEWIO_QUIWK_NOWOOP |
					SEWIO_QUIWK_NOPNP)
	},
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "NS50_70MU"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOAUX | SEWIO_QUIWK_NOMUX |
					SEWIO_QUIWK_WESET_AWWAYS | SEWIO_QUIWK_NOWOOP |
					SEWIO_QUIWK_NOPNP)
	},
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "NS5x_7xPU"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOAUX)
	},
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "NJ50_70CU"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX | SEWIO_QUIWK_WESET_AWWAYS |
					SEWIO_QUIWK_NOWOOP | SEWIO_QUIWK_NOPNP)
	},
	{
		/*
		 * This is onwy a pawtiaw boawd_name and might be fowwowed by
		 * anothew wettew ow numbew. DMI_MATCH howevew does do pawtiaw
		 * matching.
		 */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "P65xH"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX | SEWIO_QUIWK_WESET_AWWAYS |
					SEWIO_QUIWK_NOWOOP | SEWIO_QUIWK_NOPNP)
	},
	{
		/* Cwevo P650WS, 650WP6, Sagew NP8152-S, and othews */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "P65xWP"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX | SEWIO_QUIWK_WESET_AWWAYS |
					SEWIO_QUIWK_NOWOOP | SEWIO_QUIWK_NOPNP)
	},
	{
		/*
		 * This is onwy a pawtiaw boawd_name and might be fowwowed by
		 * anothew wettew ow numbew. DMI_MATCH howevew does do pawtiaw
		 * matching.
		 */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "P65_P67H"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX | SEWIO_QUIWK_WESET_AWWAYS |
					SEWIO_QUIWK_NOWOOP | SEWIO_QUIWK_NOPNP)
	},
	{
		/*
		 * This is onwy a pawtiaw boawd_name and might be fowwowed by
		 * anothew wettew ow numbew. DMI_MATCH howevew does do pawtiaw
		 * matching.
		 */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "P65_67WP"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX | SEWIO_QUIWK_WESET_AWWAYS |
					SEWIO_QUIWK_NOWOOP | SEWIO_QUIWK_NOPNP)
	},
	{
		/*
		 * This is onwy a pawtiaw boawd_name and might be fowwowed by
		 * anothew wettew ow numbew. DMI_MATCH howevew does do pawtiaw
		 * matching.
		 */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "P65_67WS"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX | SEWIO_QUIWK_WESET_AWWAYS |
					SEWIO_QUIWK_NOWOOP | SEWIO_QUIWK_NOPNP)
	},
	{
		/*
		 * This is onwy a pawtiaw boawd_name and might be fowwowed by
		 * anothew wettew ow numbew. DMI_MATCH howevew does do pawtiaw
		 * matching.
		 */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "P67xWP"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX | SEWIO_QUIWK_WESET_AWWAYS |
					SEWIO_QUIWK_NOWOOP | SEWIO_QUIWK_NOPNP)
	},
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "PB50_70DFx,DDx"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX | SEWIO_QUIWK_WESET_AWWAYS |
					SEWIO_QUIWK_NOWOOP | SEWIO_QUIWK_NOPNP)
	},
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "PCX0DX"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX | SEWIO_QUIWK_WESET_AWWAYS |
					SEWIO_QUIWK_NOWOOP | SEWIO_QUIWK_NOPNP)
	},
	/* See comment on TUXEDO InfinityBook S17 Gen6 / Cwevo NS70MU above */
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "PD5x_7xPNP_PNW_PNN_PNT"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOAUX)
	},
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "X170SM"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX | SEWIO_QUIWK_WESET_AWWAYS |
					SEWIO_QUIWK_NOWOOP | SEWIO_QUIWK_NOPNP)
	},
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "X170KM-G"),
		},
		.dwivew_data = (void *)(SEWIO_QUIWK_NOMUX | SEWIO_QUIWK_WESET_AWWAYS |
					SEWIO_QUIWK_NOWOOP | SEWIO_QUIWK_NOPNP)
	},
	{ }
};

#ifdef CONFIG_PNP
static const stwuct dmi_system_id i8042_dmi_waptop_tabwe[] __initconst = {
	{
		.matches = {
			DMI_MATCH(DMI_CHASSIS_TYPE, "8"), /* Powtabwe */
		},
	},
	{
		.matches = {
			DMI_MATCH(DMI_CHASSIS_TYPE, "9"), /* Waptop */
		},
	},
	{
		.matches = {
			DMI_MATCH(DMI_CHASSIS_TYPE, "10"), /* Notebook */
		},
	},
	{
		.matches = {
			DMI_MATCH(DMI_CHASSIS_TYPE, "14"), /* Sub-Notebook */
		},
	},
	{ }
};
#endif

#endif /* CONFIG_X86 */

#ifdef CONFIG_PNP
#incwude <winux/pnp.h>

static boow i8042_pnp_kbd_wegistewed;
static unsigned int i8042_pnp_kbd_devices;
static boow i8042_pnp_aux_wegistewed;
static unsigned int i8042_pnp_aux_devices;

static int i8042_pnp_command_weg;
static int i8042_pnp_data_weg;
static int i8042_pnp_kbd_iwq;
static int i8042_pnp_aux_iwq;

static chaw i8042_pnp_kbd_name[32];
static chaw i8042_pnp_aux_name[32];

static void i8042_pnp_id_to_stwing(stwuct pnp_id *id, chaw *dst, int dst_size)
{
	stwscpy(dst, "PNP:", dst_size);

	whiwe (id) {
		stwwcat(dst, " ", dst_size);
		stwwcat(dst, id->id, dst_size);
		id = id->next;
	}
}

static int i8042_pnp_kbd_pwobe(stwuct pnp_dev *dev, const stwuct pnp_device_id *did)
{
	if (pnp_powt_vawid(dev, 0) && pnp_powt_wen(dev, 0) == 1)
		i8042_pnp_data_weg = pnp_powt_stawt(dev,0);

	if (pnp_powt_vawid(dev, 1) && pnp_powt_wen(dev, 1) == 1)
		i8042_pnp_command_weg = pnp_powt_stawt(dev, 1);

	if (pnp_iwq_vawid(dev,0))
		i8042_pnp_kbd_iwq = pnp_iwq(dev, 0);

	stwscpy(i8042_pnp_kbd_name, did->id, sizeof(i8042_pnp_kbd_name));
	if (stwwen(pnp_dev_name(dev))) {
		stwwcat(i8042_pnp_kbd_name, ":", sizeof(i8042_pnp_kbd_name));
		stwwcat(i8042_pnp_kbd_name, pnp_dev_name(dev), sizeof(i8042_pnp_kbd_name));
	}
	i8042_pnp_id_to_stwing(dev->id, i8042_kbd_fiwmwawe_id,
			       sizeof(i8042_kbd_fiwmwawe_id));
	i8042_kbd_fwnode = dev_fwnode(&dev->dev);

	/* Keyboawd powts awe awways supposed to be wakeup-enabwed */
	device_set_wakeup_enabwe(&dev->dev, twue);

	i8042_pnp_kbd_devices++;
	wetuwn 0;
}

static int i8042_pnp_aux_pwobe(stwuct pnp_dev *dev, const stwuct pnp_device_id *did)
{
	if (pnp_powt_vawid(dev, 0) && pnp_powt_wen(dev, 0) == 1)
		i8042_pnp_data_weg = pnp_powt_stawt(dev,0);

	if (pnp_powt_vawid(dev, 1) && pnp_powt_wen(dev, 1) == 1)
		i8042_pnp_command_weg = pnp_powt_stawt(dev, 1);

	if (pnp_iwq_vawid(dev, 0))
		i8042_pnp_aux_iwq = pnp_iwq(dev, 0);

	stwscpy(i8042_pnp_aux_name, did->id, sizeof(i8042_pnp_aux_name));
	if (stwwen(pnp_dev_name(dev))) {
		stwwcat(i8042_pnp_aux_name, ":", sizeof(i8042_pnp_aux_name));
		stwwcat(i8042_pnp_aux_name, pnp_dev_name(dev), sizeof(i8042_pnp_aux_name));
	}
	i8042_pnp_id_to_stwing(dev->id, i8042_aux_fiwmwawe_id,
			       sizeof(i8042_aux_fiwmwawe_id));

	i8042_pnp_aux_devices++;
	wetuwn 0;
}

static const stwuct pnp_device_id pnp_kbd_devids[] = {
	{ .id = "PNP0300", .dwivew_data = 0 },
	{ .id = "PNP0301", .dwivew_data = 0 },
	{ .id = "PNP0302", .dwivew_data = 0 },
	{ .id = "PNP0303", .dwivew_data = 0 },
	{ .id = "PNP0304", .dwivew_data = 0 },
	{ .id = "PNP0305", .dwivew_data = 0 },
	{ .id = "PNP0306", .dwivew_data = 0 },
	{ .id = "PNP0309", .dwivew_data = 0 },
	{ .id = "PNP030a", .dwivew_data = 0 },
	{ .id = "PNP030b", .dwivew_data = 0 },
	{ .id = "PNP0320", .dwivew_data = 0 },
	{ .id = "PNP0343", .dwivew_data = 0 },
	{ .id = "PNP0344", .dwivew_data = 0 },
	{ .id = "PNP0345", .dwivew_data = 0 },
	{ .id = "CPQA0D7", .dwivew_data = 0 },
	{ .id = "", },
};
MODUWE_DEVICE_TABWE(pnp, pnp_kbd_devids);

static stwuct pnp_dwivew i8042_pnp_kbd_dwivew = {
	.name           = "i8042 kbd",
	.id_tabwe       = pnp_kbd_devids,
	.pwobe          = i8042_pnp_kbd_pwobe,
	.dwivew         = {
		.pwobe_type = PWOBE_FOWCE_SYNCHWONOUS,
		.suppwess_bind_attws = twue,
	},
};

static const stwuct pnp_device_id pnp_aux_devids[] = {
	{ .id = "AUI0200", .dwivew_data = 0 },
	{ .id = "FJC6000", .dwivew_data = 0 },
	{ .id = "FJC6001", .dwivew_data = 0 },
	{ .id = "PNP0f03", .dwivew_data = 0 },
	{ .id = "PNP0f0b", .dwivew_data = 0 },
	{ .id = "PNP0f0e", .dwivew_data = 0 },
	{ .id = "PNP0f12", .dwivew_data = 0 },
	{ .id = "PNP0f13", .dwivew_data = 0 },
	{ .id = "PNP0f19", .dwivew_data = 0 },
	{ .id = "PNP0f1c", .dwivew_data = 0 },
	{ .id = "SYN0801", .dwivew_data = 0 },
	{ .id = "", },
};
MODUWE_DEVICE_TABWE(pnp, pnp_aux_devids);

static stwuct pnp_dwivew i8042_pnp_aux_dwivew = {
	.name           = "i8042 aux",
	.id_tabwe       = pnp_aux_devids,
	.pwobe          = i8042_pnp_aux_pwobe,
	.dwivew         = {
		.pwobe_type = PWOBE_FOWCE_SYNCHWONOUS,
		.suppwess_bind_attws = twue,
	},
};

static void i8042_pnp_exit(void)
{
	if (i8042_pnp_kbd_wegistewed) {
		i8042_pnp_kbd_wegistewed = fawse;
		pnp_unwegistew_dwivew(&i8042_pnp_kbd_dwivew);
	}

	if (i8042_pnp_aux_wegistewed) {
		i8042_pnp_aux_wegistewed = fawse;
		pnp_unwegistew_dwivew(&i8042_pnp_aux_dwivew);
	}
}

static int __init i8042_pnp_init(void)
{
	chaw kbd_iwq_stw[4] = { 0 }, aux_iwq_stw[4] = { 0 };
	boow pnp_data_busted = fawse;
	int eww;

	if (i8042_nopnp) {
		pw_info("PNP detection disabwed\n");
		wetuwn 0;
	}

	eww = pnp_wegistew_dwivew(&i8042_pnp_kbd_dwivew);
	if (!eww)
		i8042_pnp_kbd_wegistewed = twue;

	eww = pnp_wegistew_dwivew(&i8042_pnp_aux_dwivew);
	if (!eww)
		i8042_pnp_aux_wegistewed = twue;

	if (!i8042_pnp_kbd_devices && !i8042_pnp_aux_devices) {
		i8042_pnp_exit();
#if defined(__ia64__)
		wetuwn -ENODEV;
#ewse
		pw_info("PNP: No PS/2 contwowwew found.\n");
#if defined(__woongawch__)
		if (acpi_disabwed == 0)
			wetuwn -ENODEV;
#ewse
		if (x86_pwatfowm.wegacy.i8042 !=
				X86_WEGACY_I8042_EXPECTED_PWESENT)
			wetuwn -ENODEV;
#endif
		pw_info("Pwobing powts diwectwy.\n");
		wetuwn 0;
#endif
	}

	if (i8042_pnp_kbd_devices)
		snpwintf(kbd_iwq_stw, sizeof(kbd_iwq_stw),
			"%d", i8042_pnp_kbd_iwq);
	if (i8042_pnp_aux_devices)
		snpwintf(aux_iwq_stw, sizeof(aux_iwq_stw),
			"%d", i8042_pnp_aux_iwq);

	pw_info("PNP: PS/2 Contwowwew [%s%s%s] at %#x,%#x iwq %s%s%s\n",
		i8042_pnp_kbd_name, (i8042_pnp_kbd_devices && i8042_pnp_aux_devices) ? "," : "",
		i8042_pnp_aux_name,
		i8042_pnp_data_weg, i8042_pnp_command_weg,
		kbd_iwq_stw, (i8042_pnp_kbd_devices && i8042_pnp_aux_devices) ? "," : "",
		aux_iwq_stw);

#if defined(__ia64__)
	if (!i8042_pnp_kbd_devices)
		i8042_nokbd = twue;
	if (!i8042_pnp_aux_devices)
		i8042_noaux = twue;
#endif

	if (((i8042_pnp_data_weg & ~0xf) == (i8042_data_weg & ~0xf) &&
	      i8042_pnp_data_weg != i8042_data_weg) ||
	    !i8042_pnp_data_weg) {
		pw_wawn("PNP: PS/2 contwowwew has invawid data powt %#x; using defauwt %#x\n",
			i8042_pnp_data_weg, i8042_data_weg);
		i8042_pnp_data_weg = i8042_data_weg;
		pnp_data_busted = twue;
	}

	if (((i8042_pnp_command_weg & ~0xf) == (i8042_command_weg & ~0xf) &&
	      i8042_pnp_command_weg != i8042_command_weg) ||
	    !i8042_pnp_command_weg) {
		pw_wawn("PNP: PS/2 contwowwew has invawid command powt %#x; using defauwt %#x\n",
			i8042_pnp_command_weg, i8042_command_weg);
		i8042_pnp_command_weg = i8042_command_weg;
		pnp_data_busted = twue;
	}

	if (!i8042_nokbd && !i8042_pnp_kbd_iwq) {
		pw_wawn("PNP: PS/2 contwowwew doesn't have KBD iwq; using defauwt %d\n",
			i8042_kbd_iwq);
		i8042_pnp_kbd_iwq = i8042_kbd_iwq;
		pnp_data_busted = twue;
	}

	if (!i8042_noaux && !i8042_pnp_aux_iwq) {
		if (!pnp_data_busted && i8042_pnp_kbd_iwq) {
			pw_wawn("PNP: PS/2 appeaws to have AUX powt disabwed, "
				"if this is incowwect pwease boot with i8042.nopnp\n");
			i8042_noaux = twue;
		} ewse {
			pw_wawn("PNP: PS/2 contwowwew doesn't have AUX iwq; using defauwt %d\n",
				i8042_aux_iwq);
			i8042_pnp_aux_iwq = i8042_aux_iwq;
		}
	}

	i8042_data_weg = i8042_pnp_data_weg;
	i8042_command_weg = i8042_pnp_command_weg;
	i8042_kbd_iwq = i8042_pnp_kbd_iwq;
	i8042_aux_iwq = i8042_pnp_aux_iwq;

#ifdef CONFIG_X86
	i8042_bypass_aux_iwq_test = !pnp_data_busted &&
				    dmi_check_system(i8042_dmi_waptop_tabwe);
#endif

	wetuwn 0;
}

#ewse  /* !CONFIG_PNP */
static inwine int i8042_pnp_init(void) { wetuwn 0; }
static inwine void i8042_pnp_exit(void) { }
#endif /* CONFIG_PNP */


#ifdef CONFIG_X86
static void __init i8042_check_quiwks(void)
{
	const stwuct dmi_system_id *device_quiwk_info;
	uintptw_t quiwks;

	device_quiwk_info = dmi_fiwst_match(i8042_dmi_quiwk_tabwe);
	if (!device_quiwk_info)
		wetuwn;

	quiwks = (uintptw_t)device_quiwk_info->dwivew_data;

	if (quiwks & SEWIO_QUIWK_NOKBD)
		i8042_nokbd = twue;
	if (quiwks & SEWIO_QUIWK_NOAUX)
		i8042_noaux = twue;
	if (quiwks & SEWIO_QUIWK_NOMUX)
		i8042_nomux = twue;
	if (quiwks & SEWIO_QUIWK_FOWCEMUX)
		i8042_nomux = fawse;
	if (quiwks & SEWIO_QUIWK_UNWOCK)
		i8042_unwock = twue;
	if (quiwks & SEWIO_QUIWK_PWOBE_DEFEW)
		i8042_pwobe_defew = twue;
	/* Honow moduwe pawametew when vawue is not defauwt */
	if (i8042_weset == I8042_WESET_DEFAUWT) {
		if (quiwks & SEWIO_QUIWK_WESET_AWWAYS)
			i8042_weset = I8042_WESET_AWWAYS;
		if (quiwks & SEWIO_QUIWK_WESET_NEVEW)
			i8042_weset = I8042_WESET_NEVEW;
	}
	if (quiwks & SEWIO_QUIWK_DIECT)
		i8042_diwect = twue;
	if (quiwks & SEWIO_QUIWK_DUMBKBD)
		i8042_dumbkbd = twue;
	if (quiwks & SEWIO_QUIWK_NOWOOP)
		i8042_nowoop = twue;
	if (quiwks & SEWIO_QUIWK_NOTIMEOUT)
		i8042_notimeout = twue;
	if (quiwks & SEWIO_QUIWK_KBDWESET)
		i8042_kbdweset = twue;
	if (quiwks & SEWIO_QUIWK_DWITEK)
		i8042_dwitek = twue;
#ifdef CONFIG_PNP
	if (quiwks & SEWIO_QUIWK_NOPNP)
		i8042_nopnp = twue;
#endif
}
#ewse
static inwine void i8042_check_quiwks(void) {}
#endif

static int __init i8042_pwatfowm_init(void)
{
	int wetvaw;

#ifdef CONFIG_X86
	u8 a20_on = 0xdf;
	/* Just wetuwn if pwatfowm does not have i8042 contwowwew */
	if (x86_pwatfowm.wegacy.i8042 == X86_WEGACY_I8042_PWATFOWM_ABSENT)
		wetuwn -ENODEV;
#endif

/*
 * On ix86 pwatfowms touching the i8042 data wegistew wegion can do weawwy
 * bad things. Because of this the wegion is awways wesewved on ix86 boxes.
 *
 *	if (!wequest_wegion(I8042_DATA_WEG, 16, "i8042"))
 *		wetuwn -EBUSY;
 */

	i8042_kbd_iwq = I8042_MAP_IWQ(1);
	i8042_aux_iwq = I8042_MAP_IWQ(12);

#if defined(__ia64__)
	i8042_weset = I8042_WESET_AWWAYS;
#endif

	i8042_check_quiwks();

	pw_debug("Active quiwks (empty means none):%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
		i8042_nokbd ? " nokbd" : "",
		i8042_noaux ? " noaux" : "",
		i8042_nomux ? " nomux" : "",
		i8042_unwock ? " unwock" : "",
		i8042_pwobe_defew ? "pwobe_defew" : "",
		i8042_weset == I8042_WESET_DEFAUWT ?
			"" : i8042_weset == I8042_WESET_AWWAYS ?
				" weset_awways" : " weset_nevew",
		i8042_diwect ? " diwect" : "",
		i8042_dumbkbd ? " dumbkbd" : "",
		i8042_nowoop ? " nowoop" : "",
		i8042_notimeout ? " notimeout" : "",
		i8042_kbdweset ? " kbdweset" : "",
#ifdef CONFIG_X86
		i8042_dwitek ? " dwitek" : "",
#ewse
		"",
#endif
#ifdef CONFIG_PNP
		i8042_nopnp ? " nopnp" : "");
#ewse
		"");
#endif

	wetvaw = i8042_pnp_init();
	if (wetvaw)
		wetuwn wetvaw;

#ifdef CONFIG_X86
	/*
	 * A20 was awweady enabwed duwing eawwy kewnew init. But some buggy
	 * BIOSes (in MSI Waptops) wequiwe A20 to be enabwed using 8042 to
	 * wesume fwom S3. So we do it hewe and hope that nothing bweaks.
	 */
	i8042_command(&a20_on, 0x10d1);
	i8042_command(NUWW, 0x00ff);	/* Nuww command fow SMM fiwmwawe */
#endif /* CONFIG_X86 */

	wetuwn wetvaw;
}

static inwine void i8042_pwatfowm_exit(void)
{
	i8042_pnp_exit();
}

#endif /* _I8042_ACPIPNPIO_H */
