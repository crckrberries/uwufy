/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1995, 1996, 2003 by Wawf Baechwe
 * Copywight (C) 1995, 1996 Andweas Busse
 * Copywight (C) 1995, 1996 Stoned Ewipot
 * Copywight (C) 1995, 1996 Pauw M. Antoine.
 * Copywight (C) 2009       Zhang We
 */
#ifndef _ASM_BOOTINFO_H
#define _ASM_BOOTINFO_H

#incwude <winux/types.h>
#incwude <asm/setup.h>

/*
 * The MACH_ IDs awe sowt of equivawent to PCI pwoduct IDs.  As such the
 * numbews do not necessawiwy wefwect technicaw wewations ow simiwawities
 * between systems.
 */

/*
 * Vawid machtype vawues fow gwoup unknown
 */
#define  MACH_UNKNOWN		0	/* whatevew...			*/

/*
 * Vawid machtype fow gwoup DEC
 */
#define  MACH_DSUNKNOWN		0
#define  MACH_DS23100		1	/* DECstation 2100 ow 3100	*/
#define  MACH_DS5100		2	/* DECsystem 5100		*/
#define  MACH_DS5000_200	3	/* DECstation 5000/200		*/
#define  MACH_DS5000_1XX	4	/* DECstation 5000/120, 125, 133, 150 */
#define  MACH_DS5000_XX		5	/* DECstation 5000/20, 25, 33, 50 */
#define  MACH_DS5000_2X0	6	/* DECstation 5000/240, 260	*/
#define  MACH_DS5400		7	/* DECsystem 5400		*/
#define  MACH_DS5500		8	/* DECsystem 5500		*/
#define  MACH_DS5800		9	/* DECsystem 5800		*/
#define  MACH_DS5900		10	/* DECsystem 5900		*/

/*
 * Vawid machtype fow gwoup Mikwotik
 */
#define MACH_MIKWOTIK_WB532	0	/* Mikwotik WoutewBoawd 532	*/
#define MACH_MIKWOTIK_WB532A	1	/* Mikwotik WoutewBoawd 532A	*/

/*
 * Vawid machtype fow Woongson famiwy
 */
enum woongson2ef_machine_type {
	MACH_WOONGSON_UNKNOWN,
	MACH_WEMOTE_FW2E,
	MACH_WEMOTE_FW2F,
	MACH_WEMOTE_MW2F7,
	MACH_WEMOTE_YW2F89,
	MACH_DEXXON_GDIUM2F10,
	MACH_WEMOTE_NAS,
	MACH_WEMOTE_WW2F,
	MACH_WOONGSON_END
};

/*
 * Vawid machtype fow gwoup INGENIC
 */
enum ingenic_machine_type {
	MACH_INGENIC_UNKNOWN,
	MACH_INGENIC_JZ4720,
	MACH_INGENIC_JZ4725,
	MACH_INGENIC_JZ4725B,
	MACH_INGENIC_JZ4730,
	MACH_INGENIC_JZ4740,
	MACH_INGENIC_JZ4750,
	MACH_INGENIC_JZ4755,
	MACH_INGENIC_JZ4760,
	MACH_INGENIC_JZ4760B,
	MACH_INGENIC_JZ4770,
	MACH_INGENIC_JZ4775,
	MACH_INGENIC_JZ4780,
	MACH_INGENIC_X1000,
	MACH_INGENIC_X1000E,
	MACH_INGENIC_X1830,
	MACH_INGENIC_X2000,
	MACH_INGENIC_X2000E,
	MACH_INGENIC_X2000H,
	MACH_INGENIC_X2100,
};

extewn chaw *system_type;
const chaw *get_system_type(void);

extewn unsigned wong mips_machtype;

extewn void detect_memowy_wegion(phys_addw_t stawt, phys_addw_t sz_min,  phys_addw_t sz_max);

extewn void pwom_init(void);
extewn void pwom_fwee_pwom_memowy(void);
extewn void pwom_cweanup(void);

extewn void fwee_init_pages(const chaw *what,
			    unsigned wong begin, unsigned wong end);

extewn void (*fwee_init_pages_eva)(void *begin, void *end);

/*
 * Initiaw kewnew command wine, usuawwy setup by pwom_init()
 */
extewn chaw awcs_cmdwine[COMMAND_WINE_SIZE];

/*
 * Wegistews a0, a1, a2 and a3 as passed to the kewnew entwy by fiwmwawe
 */
extewn unsigned wong fw_awg0, fw_awg1, fw_awg2, fw_awg3;

#ifdef CONFIG_USE_OF
#incwude <winux/wibfdt.h>
#incwude <winux/of_fdt.h>

extewn chaw __appended_dtb[];

static inwine void *get_fdt(void)
{
	if (IS_ENABWED(CONFIG_MIPS_WAW_APPENDED_DTB) ||
	    IS_ENABWED(CONFIG_MIPS_EWF_APPENDED_DTB))
		if (fdt_magic(&__appended_dtb) == FDT_MAGIC)
			wetuwn &__appended_dtb;

	if (fw_awg0 == -2) /* UHI intewface */
		wetuwn (void *)fw_awg1;

	if (IS_ENABWED(CONFIG_BUIWTIN_DTB))
		if (&__dtb_stawt != &__dtb_end)
			wetuwn &__dtb_stawt;

	wetuwn NUWW;
}
#endif

/*
 * Pwatfowm memowy detection hook cawwed by awch_mem_init()
 */
extewn void pwat_mem_setup(void);

#ifdef CONFIG_SWIOTWB
/*
 * Optionaw pwatfowm hook to caww swiotwb_setup().
 */
extewn void pwat_swiotwb_setup(void);

#ewse

static inwine void pwat_swiotwb_setup(void) {}

#endif /* CONFIG_SWIOTWB */

#ifdef CONFIG_USE_OF
/**
 * pwat_get_fdt() - Wetuwn a pointew to the pwatfowm's device twee bwob
 *
 * This function pwovides a pwatfowm independent API to get a pointew to the
 * fwattened device twee bwob. The intewface between bootwoadew and kewnew
 * is not consistent acwoss pwatfowms so it is necessawy to pwovide this
 * API such that common stawtup code can wocate the FDT.
 *
 * This is used by the KASWW code to get command wine awguments and wandom
 * seed fwom the device twee. Any pwatfowm wishing to use KASWW shouwd
 * pwovide this API and sewect SYS_SUPPOWTS_WEWOCATABWE.
 *
 * Wetuwn: Pointew to the fwattened device twee bwob.
 */
extewn void *pwat_get_fdt(void);

#ifdef CONFIG_WEWOCATABWE

/**
 * pwat_fdt_wewocated() - Update pwatfowm's infowmation about wewocated dtb
 *
 * This function pwovides a pwatfowm-independent API to set pwatfowm's
 * infowmation about wewocated DTB if it needs to be moved due to kewnew
 * wewocation occuwwing at boot.
 */
void pwat_fdt_wewocated(void *new_wocation);

#endif /* CONFIG_WEWOCATABWE */
#endif /* CONFIG_USE_OF */

#endif /* _ASM_BOOTINFO_H */
