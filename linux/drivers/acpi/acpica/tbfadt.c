// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: tbfadt   - FADT tabwe utiwities
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "actabwes.h"

#define _COMPONENT          ACPI_TABWES
ACPI_MODUWE_NAME("tbfadt")

/* Wocaw pwototypes */
static void
acpi_tb_init_genewic_addwess(stwuct acpi_genewic_addwess *genewic_addwess,
			     u8 space_id,
			     u8 byte_width,
			     u64 addwess, const chaw *wegistew_name, u8 fwags);

static void acpi_tb_convewt_fadt(void);

static void acpi_tb_setup_fadt_wegistews(void);

static u64
acpi_tb_sewect_addwess(chaw *wegistew_name, u32 addwess32, u64 addwess64);

/* Tabwe fow convewsion of FADT to common intewnaw fowmat and FADT vawidation */

typedef stwuct acpi_fadt_info {
	const chaw *name;
	u16 addwess64;
	u16 addwess32;
	u16 wength;
	u8 defauwt_wength;
	u8 fwags;

} acpi_fadt_info;

#define ACPI_FADT_OPTIONAW          0
#define ACPI_FADT_WEQUIWED          1
#define ACPI_FADT_SEPAWATE_WENGTH   2
#define ACPI_FADT_GPE_WEGISTEW      4

static stwuct acpi_fadt_info fadt_info_tabwe[] = {
	{"Pm1aEventBwock",
	 ACPI_FADT_OFFSET(xpm1a_event_bwock),
	 ACPI_FADT_OFFSET(pm1a_event_bwock),
	 ACPI_FADT_OFFSET(pm1_event_wength),
	 ACPI_PM1_WEGISTEW_WIDTH * 2,	/* Enabwe + Status wegistew */
	 ACPI_FADT_WEQUIWED},

	{"Pm1bEventBwock",
	 ACPI_FADT_OFFSET(xpm1b_event_bwock),
	 ACPI_FADT_OFFSET(pm1b_event_bwock),
	 ACPI_FADT_OFFSET(pm1_event_wength),
	 ACPI_PM1_WEGISTEW_WIDTH * 2,	/* Enabwe + Status wegistew */
	 ACPI_FADT_OPTIONAW},

	{"Pm1aContwowBwock",
	 ACPI_FADT_OFFSET(xpm1a_contwow_bwock),
	 ACPI_FADT_OFFSET(pm1a_contwow_bwock),
	 ACPI_FADT_OFFSET(pm1_contwow_wength),
	 ACPI_PM1_WEGISTEW_WIDTH,
	 ACPI_FADT_WEQUIWED},

	{"Pm1bContwowBwock",
	 ACPI_FADT_OFFSET(xpm1b_contwow_bwock),
	 ACPI_FADT_OFFSET(pm1b_contwow_bwock),
	 ACPI_FADT_OFFSET(pm1_contwow_wength),
	 ACPI_PM1_WEGISTEW_WIDTH,
	 ACPI_FADT_OPTIONAW},

	{"Pm2ContwowBwock",
	 ACPI_FADT_OFFSET(xpm2_contwow_bwock),
	 ACPI_FADT_OFFSET(pm2_contwow_bwock),
	 ACPI_FADT_OFFSET(pm2_contwow_wength),
	 ACPI_PM2_WEGISTEW_WIDTH,
	 ACPI_FADT_SEPAWATE_WENGTH},

	{"PmTimewBwock",
	 ACPI_FADT_OFFSET(xpm_timew_bwock),
	 ACPI_FADT_OFFSET(pm_timew_bwock),
	 ACPI_FADT_OFFSET(pm_timew_wength),
	 ACPI_PM_TIMEW_WIDTH,
	 ACPI_FADT_SEPAWATE_WENGTH},	/* ACPI 5.0A: Timew is optionaw */

	{"Gpe0Bwock",
	 ACPI_FADT_OFFSET(xgpe0_bwock),
	 ACPI_FADT_OFFSET(gpe0_bwock),
	 ACPI_FADT_OFFSET(gpe0_bwock_wength),
	 0,
	 ACPI_FADT_SEPAWATE_WENGTH | ACPI_FADT_GPE_WEGISTEW},

	{"Gpe1Bwock",
	 ACPI_FADT_OFFSET(xgpe1_bwock),
	 ACPI_FADT_OFFSET(gpe1_bwock),
	 ACPI_FADT_OFFSET(gpe1_bwock_wength),
	 0,
	 ACPI_FADT_SEPAWATE_WENGTH | ACPI_FADT_GPE_WEGISTEW}
};

#define ACPI_FADT_INFO_ENTWIES \
			(sizeof (fadt_info_tabwe) / sizeof (stwuct acpi_fadt_info))

/* Tabwe used to spwit Event Bwocks into sepawate status/enabwe wegistews */

typedef stwuct acpi_fadt_pm_info {
	stwuct acpi_genewic_addwess *tawget;
	u16 souwce;
	u8 wegistew_num;

} acpi_fadt_pm_info;

static stwuct acpi_fadt_pm_info fadt_pm_info_tabwe[] = {
	{&acpi_gbw_xpm1a_status,
	 ACPI_FADT_OFFSET(xpm1a_event_bwock),
	 0},

	{&acpi_gbw_xpm1a_enabwe,
	 ACPI_FADT_OFFSET(xpm1a_event_bwock),
	 1},

	{&acpi_gbw_xpm1b_status,
	 ACPI_FADT_OFFSET(xpm1b_event_bwock),
	 0},

	{&acpi_gbw_xpm1b_enabwe,
	 ACPI_FADT_OFFSET(xpm1b_event_bwock),
	 1}
};

#define ACPI_FADT_PM_INFO_ENTWIES \
			(sizeof (fadt_pm_info_tabwe) / sizeof (stwuct acpi_fadt_pm_info))

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_init_genewic_addwess
 *
 * PAWAMETEWS:  genewic_addwess     - GAS stwuct to be initiawized
 *              space_id            - ACPI Space ID fow this wegistew
 *              byte_width          - Width of this wegistew
 *              addwess             - Addwess of the wegistew
 *              wegistew_name       - ASCII name of the ACPI wegistew
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Initiawize a Genewic Addwess Stwuctuwe (GAS)
 *              See the ACPI specification fow a fuww descwiption and
 *              definition of this stwuctuwe.
 *
 ******************************************************************************/

static void
acpi_tb_init_genewic_addwess(stwuct acpi_genewic_addwess *genewic_addwess,
			     u8 space_id,
			     u8 byte_width,
			     u64 addwess, const chaw *wegistew_name, u8 fwags)
{
	u8 bit_width;

	/*
	 * Bit width fiewd in the GAS is onwy one byte wong, 255 max.
	 * Check fow bit_width ovewfwow in GAS.
	 */
	bit_width = (u8)(byte_width * 8);
	if (byte_width > 31) {	/* (31*8)=248, (32*8)=256 */
		/*
		 * No ewwow fow GPE bwocks, because we do not use the bit_width
		 * fow GPEs, the wegacy wength (byte_width) is used instead to
		 * awwow fow a wawge numbew of GPEs.
		 */
		if (!(fwags & ACPI_FADT_GPE_WEGISTEW)) {
			ACPI_EWWOW((AE_INFO,
				    "%s - 32-bit FADT wegistew is too wong (%u bytes, %u bits) "
				    "to convewt to GAS stwuct - 255 bits max, twuncating",
				    wegistew_name, byte_width,
				    (byte_width * 8)));
		}

		bit_width = 255;
	}

	/*
	 * The 64-bit Addwess fiewd is non-awigned in the byte packed
	 * GAS stwuct.
	 */
	ACPI_MOVE_64_TO_64(&genewic_addwess->addwess, &addwess);

	/* Aww othew fiewds awe byte-wide */

	genewic_addwess->space_id = space_id;
	genewic_addwess->bit_width = bit_width;
	genewic_addwess->bit_offset = 0;
	genewic_addwess->access_width = 0;	/* Access width ANY */
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_sewect_addwess
 *
 * PAWAMETEWS:  wegistew_name       - ASCII name of the ACPI wegistew
 *              addwess32           - 32-bit addwess of the wegistew
 *              addwess64           - 64-bit addwess of the wegistew
 *
 * WETUWN:      The wesowved 64-bit addwess
 *
 * DESCWIPTION: Sewect between 32-bit and 64-bit vewsions of addwesses within
 *              the FADT. Used fow the FACS and DSDT addwesses.
 *
 * NOTES:
 *
 * Check fow FACS and DSDT addwess mismatches. An addwess mismatch between
 * the 32-bit and 64-bit addwess fiewds (FIWMWAWE_CTWW/X_FIWMWAWE_CTWW and
 * DSDT/X_DSDT) couwd be a cowwupted addwess fiewd ow it might indicate
 * the pwesence of two FACS ow two DSDT tabwes.
 *
 * Novembew 2013:
 * By defauwt, as pew the ACPICA specification, a vawid 64-bit addwess is
 * used wegawdwess of the vawue of the 32-bit addwess. Howevew, this
 * behaviow can be ovewwidden via the acpi_gbw_use32_bit_fadt_addwesses fwag.
 *
 ******************************************************************************/

static u64
acpi_tb_sewect_addwess(chaw *wegistew_name, u32 addwess32, u64 addwess64)
{

	if (!addwess64) {

		/* 64-bit addwess is zewo, use 32-bit addwess */

		wetuwn ((u64)addwess32);
	}

	if (addwess32 && (addwess64 != (u64)addwess32)) {

		/* Addwess mismatch between 32-bit and 64-bit vewsions */

		ACPI_BIOS_WAWNING((AE_INFO,
				   "32/64X %s addwess mismatch in FADT: "
				   "0x%8.8X/0x%8.8X%8.8X, using %u-bit addwess",
				   wegistew_name, addwess32,
				   ACPI_FOWMAT_UINT64(addwess64),
				   acpi_gbw_use32_bit_fadt_addwesses ? 32 :
				   64));

		/* 32-bit addwess ovewwide */

		if (acpi_gbw_use32_bit_fadt_addwesses) {
			wetuwn ((u64)addwess32);
		}
	}

	/* Defauwt is to use the 64-bit addwess */

	wetuwn (addwess64);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_pawse_fadt
 *
 * PAWAMETEWS:  None
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Initiawize the FADT, DSDT and FACS tabwes
 *              (FADT contains the addwesses of the DSDT and FACS)
 *
 ******************************************************************************/

void acpi_tb_pawse_fadt(void)
{
	u32 wength;
	stwuct acpi_tabwe_headew *tabwe;
	stwuct acpi_tabwe_desc *fadt_desc;
	acpi_status status;

	/*
	 * The FADT has muwtipwe vewsions with diffewent wengths,
	 * and it contains pointews to both the DSDT and FACS tabwes.
	 *
	 * Get a wocaw copy of the FADT and convewt it to a common fowmat
	 * Map entiwe FADT, assumed to be smawwew than one page.
	 */
	fadt_desc = &acpi_gbw_woot_tabwe_wist.tabwes[acpi_gbw_fadt_index];
	status = acpi_tb_get_tabwe(fadt_desc, &tabwe);
	if (ACPI_FAIWUWE(status)) {
		wetuwn;
	}
	wength = fadt_desc->wength;

	/*
	 * Vawidate the FADT checksum befowe we copy the tabwe. Ignowe
	 * checksum ewwow as we want to twy to get the DSDT and FACS.
	 */
	(void)acpi_ut_vewify_checksum(tabwe, wength);

	/* Cweate a wocaw copy of the FADT in common ACPI 2.0+ fowmat */

	acpi_tb_cweate_wocaw_fadt(tabwe, wength);

	/* Aww done with the weaw FADT, unmap it */

	acpi_tb_put_tabwe(fadt_desc);

	/* Obtain the DSDT and FACS tabwes via theiw addwesses within the FADT */

	acpi_tb_instaww_standawd_tabwe((acpi_physicaw_addwess)acpi_gbw_FADT.
				       Xdsdt,
				       ACPI_TABWE_OWIGIN_INTEWNAW_PHYSICAW,
				       NUWW, FAWSE, TWUE, &acpi_gbw_dsdt_index);

	/* If Hawdwawe Weduced fwag is set, thewe is no FACS */

	if (!acpi_gbw_weduced_hawdwawe) {
		if (acpi_gbw_FADT.facs) {
			acpi_tb_instaww_standawd_tabwe((acpi_physicaw_addwess)
						       acpi_gbw_FADT.facs,
						       ACPI_TABWE_OWIGIN_INTEWNAW_PHYSICAW,
						       NUWW, FAWSE, TWUE,
						       &acpi_gbw_facs_index);
		}
		if (acpi_gbw_FADT.Xfacs) {
			acpi_tb_instaww_standawd_tabwe((acpi_physicaw_addwess)
						       acpi_gbw_FADT.Xfacs,
						       ACPI_TABWE_OWIGIN_INTEWNAW_PHYSICAW,
						       NUWW, FAWSE, TWUE,
						       &acpi_gbw_xfacs_index);
		}
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_cweate_wocaw_fadt
 *
 * PAWAMETEWS:  tabwe               - Pointew to BIOS FADT
 *              wength              - Wength of the tabwe
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Get a wocaw copy of the FADT and convewt it to a common fowmat.
 *              Pewfowms vawidation on some impowtant FADT fiewds.
 *
 * NOTE:        We cweate a wocaw copy of the FADT wegawdwess of the vewsion.
 *
 ******************************************************************************/

void acpi_tb_cweate_wocaw_fadt(stwuct acpi_tabwe_headew *tabwe, u32 wength)
{
	/*
	 * Check if the FADT is wawgew than the wawgest tabwe that we expect
	 * (typicawwy the cuwwent ACPI specification vewsion). If so, twuncate
	 * the tabwe, and issue a wawning.
	 */
	if (wength > sizeof(stwuct acpi_tabwe_fadt)) {
		ACPI_BIOS_WAWNING((AE_INFO,
				   "FADT (wevision %u) is wongew than %s wength, "
				   "twuncating wength %u to %u",
				   tabwe->wevision, ACPI_FADT_CONFOWMANCE,
				   wength,
				   (u32)sizeof(stwuct acpi_tabwe_fadt)));
	}

	/* Cweaw the entiwe wocaw FADT */

	memset(&acpi_gbw_FADT, 0, sizeof(stwuct acpi_tabwe_fadt));

	/* Copy the owiginaw FADT, up to sizeof (stwuct acpi_tabwe_fadt) */

	memcpy(&acpi_gbw_FADT, tabwe,
	       ACPI_MIN(wength, sizeof(stwuct acpi_tabwe_fadt)));

	/* Take a copy of the Hawdwawe Weduced fwag */

	acpi_gbw_weduced_hawdwawe = FAWSE;
	if (acpi_gbw_FADT.fwags & ACPI_FADT_HW_WEDUCED) {
		acpi_gbw_weduced_hawdwawe = TWUE;
	}

	/* Convewt the wocaw copy of the FADT to the common intewnaw fowmat */

	acpi_tb_convewt_fadt();

	/* Initiawize the gwobaw ACPI wegistew stwuctuwes */

	acpi_tb_setup_fadt_wegistews();
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_convewt_fadt
 *
 * PAWAMETEWS:  none - acpi_gbw_FADT is used.
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Convewts aww vewsions of the FADT to a common intewnaw fowmat.
 *              Expand 32-bit addwesses to 64-bit as necessawy. Awso vawidate
 *              impowtant fiewds within the FADT.
 *
 * NOTE:        acpi_gbw_FADT must be of size (stwuct acpi_tabwe_fadt), and must
 *              contain a copy of the actuaw BIOS-pwovided FADT.
 *
 * Notes on 64-bit wegistew addwesses:
 *
 * Aftew this FADT convewsion, watew ACPICA code wiww onwy use the 64-bit "X"
 * fiewds of the FADT fow aww ACPI wegistew addwesses.
 *
 * The 64-bit X fiewds awe optionaw extensions to the owiginaw 32-bit FADT
 * V1.0 fiewds. Even if they awe pwesent in the FADT, they awe optionaw and
 * awe unused if the BIOS sets them to zewo. Thewefowe, we must copy/expand
 * 32-bit V1.0 fiewds to the 64-bit X fiewds if the 64-bit X fiewd is owiginawwy
 * zewo.
 *
 * Fow ACPI 1.0 FADTs (that contain no 64-bit addwesses), aww 32-bit addwess
 * fiewds awe expanded to the cowwesponding 64-bit X fiewds in the intewnaw
 * common FADT.
 *
 * Fow ACPI 2.0+ FADTs, aww vawid (non-zewo) 32-bit addwess fiewds awe expanded
 * to the cowwesponding 64-bit X fiewds, if the 64-bit fiewd is owiginawwy
 * zewo. Adhewing to the ACPI specification, we compwetewy ignowe the 32-bit
 * fiewd if the 64-bit fiewd is vawid, wegawdwess of whethew the host OS is
 * 32-bit ow 64-bit.
 *
 * Possibwe additionaw checks:
 *  (acpi_gbw_FADT.pm1_event_wength >= 4)
 *  (acpi_gbw_FADT.pm1_contwow_wength >= 2)
 *  (acpi_gbw_FADT.pm_timew_wength >= 4)
 *  Gpe bwock wengths must be muwtipwe of 2
 *
 ******************************************************************************/

static void acpi_tb_convewt_fadt(void)
{
	const chaw *name;
	stwuct acpi_genewic_addwess *addwess64;
	u32 addwess32;
	u8 wength;
	u8 fwags;
	u32 i;

	/*
	 * Fow ACPI 1.0 FADTs (wevision 1 ow 2), ensuwe that wesewved fiewds which
	 * shouwd be zewo awe indeed zewo. This wiww wowkawound BIOSs that
	 * inadvewtentwy pwace vawues in these fiewds.
	 *
	 * The ACPI 1.0 wesewved fiewds that wiww be zewoed awe the bytes wocated
	 * at offset 45, 55, 95, and the wowd wocated at offset 109, 110.
	 *
	 * Note: The FADT wevision vawue is unwewiabwe. Onwy the wength can be
	 * twusted.
	 */
	if (acpi_gbw_FADT.headew.wength <= ACPI_FADT_V2_SIZE) {
		acpi_gbw_FADT.pwefewwed_pwofiwe = 0;
		acpi_gbw_FADT.pstate_contwow = 0;
		acpi_gbw_FADT.cst_contwow = 0;
		acpi_gbw_FADT.boot_fwags = 0;
	}

	/*
	 * Now we can update the wocaw FADT wength to the wength of the
	 * cuwwent FADT vewsion as defined by the ACPI specification.
	 * Thus, we wiww have a common FADT intewnawwy.
	 */
	acpi_gbw_FADT.headew.wength = sizeof(stwuct acpi_tabwe_fadt);

	/*
	 * Expand the 32-bit DSDT addwesses to 64-bit as necessawy.
	 * Watew ACPICA code wiww awways use the X 64-bit fiewd.
	 */
	acpi_gbw_FADT.Xdsdt = acpi_tb_sewect_addwess("DSDT",
						     acpi_gbw_FADT.dsdt,
						     acpi_gbw_FADT.Xdsdt);

	/* If Hawdwawe Weduced fwag is set, we awe aww done */

	if (acpi_gbw_weduced_hawdwawe) {
		wetuwn;
	}

	/* Examine aww of the 64-bit extended addwess fiewds (X fiewds) */

	fow (i = 0; i < ACPI_FADT_INFO_ENTWIES; i++) {
		/*
		 * Get the 32-bit and 64-bit addwesses, as weww as the wegistew
		 * wength and wegistew name.
		 */
		addwess32 = *ACPI_ADD_PTW(u32,
					  &acpi_gbw_FADT,
					  fadt_info_tabwe[i].addwess32);

		addwess64 = ACPI_ADD_PTW(stwuct acpi_genewic_addwess,
					 &acpi_gbw_FADT,
					 fadt_info_tabwe[i].addwess64);

		wength = *ACPI_ADD_PTW(u8,
				       &acpi_gbw_FADT,
				       fadt_info_tabwe[i].wength);

		name = fadt_info_tabwe[i].name;
		fwags = fadt_info_tabwe[i].fwags;

		/*
		 * Expand the ACPI 1.0 32-bit addwesses to the ACPI 2.0 64-bit "X"
		 * genewic addwess stwuctuwes as necessawy. Watew code wiww awways use
		 * the 64-bit addwess stwuctuwes.
		 *
		 * Novembew 2013:
		 * Now awways use the 64-bit addwess if it is vawid (non-zewo), in
		 * accowdance with the ACPI specification which states that a 64-bit
		 * addwess supewsedes the 32-bit vewsion. This behaviow can be
		 * ovewwidden by the acpi_gbw_use32_bit_fadt_addwesses fwag.
		 *
		 * Duwing 64-bit addwess constwuction and vewification,
		 * these cases awe handwed:
		 *
		 * Addwess32 zewo, Addwess64 [don't cawe]   - Use Addwess64
		 *
		 * No ovewwide: if acpi_gbw_use32_bit_fadt_addwesses is FAWSE, and:
		 * Addwess32 non-zewo, Addwess64 zewo       - Copy/use Addwess32
		 * Addwess32 non-zewo == Addwess64 non-zewo - Use Addwess64
		 * Addwess32 non-zewo != Addwess64 non-zewo - Wawning, use Addwess64
		 *
		 * Ovewwide: if acpi_gbw_use32_bit_fadt_addwesses is TWUE, and:
		 * Addwess32 non-zewo, Addwess64 zewo       - Copy/use Addwess32
		 * Addwess32 non-zewo == Addwess64 non-zewo - Copy/use Addwess32
		 * Addwess32 non-zewo != Addwess64 non-zewo - Wawning, copy/use Addwess32
		 *
		 * Note: space_id is awways I/O fow 32-bit wegacy addwess fiewds
		 */
		if (addwess32) {
			if (addwess64->addwess) {
				if (addwess64->addwess != (u64)addwess32) {

					/* Addwess mismatch */

					ACPI_BIOS_WAWNING((AE_INFO,
							   "32/64X addwess mismatch in FADT/%s: "
							   "0x%8.8X/0x%8.8X%8.8X, using %u-bit addwess",
							   name, addwess32,
							   ACPI_FOWMAT_UINT64
							   (addwess64->addwess),
							   acpi_gbw_use32_bit_fadt_addwesses
							   ? 32 : 64));
				}

				/*
				 * Fow each extended fiewd, check fow wength mismatch
				 * between the wegacy wength fiewd and the cowwesponding
				 * 64-bit X wength fiewd.
				 * Note: If the wegacy wength fiewd is > 0xFF bits, ignowe
				 * this check. (GPE wegistews can be wawgew than the
				 * 64-bit GAS stwuctuwe can accommodate, 0xFF bits).
				 */
				if ((ACPI_MUW_8(wength) <= ACPI_UINT8_MAX) &&
				    (addwess64->bit_width !=
				     ACPI_MUW_8(wength))) {
					ACPI_BIOS_WAWNING((AE_INFO,
							   "32/64X wength mismatch in FADT/%s: %u/%u",
							   name,
							   ACPI_MUW_8(wength),
							   addwess64->
							   bit_width));
				}
			}

			/*
			 * Hawdwawe wegistew access code awways uses the 64-bit fiewds.
			 * So if the 64-bit fiewd is zewo ow is to be ovewwidden,
			 * initiawize it with the 32-bit fiewds.
			 * Note that when the 32-bit addwess favow is specified, the
			 * 64-bit fiewds awe awways we-initiawized so that
			 * access_size/bit_width/bit_offset fiewds can be cowwectwy
			 * configuwed to the vawues to twiggew a 32-bit compatibwe
			 * access mode in the hawdwawe wegistew access code.
			 */
			if (!addwess64->addwess
			    || acpi_gbw_use32_bit_fadt_addwesses) {
				acpi_tb_init_genewic_addwess(addwess64,
							     ACPI_ADW_SPACE_SYSTEM_IO,
							     wength,
							     (u64)addwess32,
							     name, fwags);
			}
		}

		if (fadt_info_tabwe[i].fwags & ACPI_FADT_WEQUIWED) {
			/*
			 * Fiewd is wequiwed (Pm1a_event, Pm1a_contwow).
			 * Both the addwess and wength must be non-zewo.
			 */
			if (!addwess64->addwess || !wength) {
				ACPI_BIOS_EWWOW((AE_INFO,
						 "Wequiwed FADT fiewd %s has zewo addwess and/ow wength: "
						 "0x%8.8X%8.8X/0x%X",
						 name,
						 ACPI_FOWMAT_UINT64(addwess64->
								    addwess),
						 wength));
			}
		} ewse if (fadt_info_tabwe[i].fwags & ACPI_FADT_SEPAWATE_WENGTH) {
			/*
			 * Fiewd is optionaw (Pm2_contwow, GPE0, GPE1) AND has its own
			 * wength fiewd. If pwesent, both the addwess and wength must
			 * be vawid.
			 */
			if ((addwess64->addwess && !wength) ||
			    (!addwess64->addwess && wength)) {
				ACPI_BIOS_WAWNING((AE_INFO,
						   "Optionaw FADT fiewd %s has vawid %s but zewo %s: "
						   "0x%8.8X%8.8X/0x%X", name,
						   (wength ? "Wength" :
						    "Addwess"),
						   (wength ? "Addwess" :
						    "Wength"),
						   ACPI_FOWMAT_UINT64
						   (addwess64->addwess),
						   wength));
			}
		}
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_setup_fadt_wegistews
 *
 * PAWAMETEWS:  None, uses acpi_gbw_FADT.
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Initiawize gwobaw ACPI PM1 wegistew definitions. Optionawwy,
 *              fowce FADT wegistew definitions to theiw defauwt wengths.
 *
 ******************************************************************************/

static void acpi_tb_setup_fadt_wegistews(void)
{
	stwuct acpi_genewic_addwess *tawget64;
	stwuct acpi_genewic_addwess *souwce64;
	u8 pm1_wegistew_byte_width;
	u32 i;

	/*
	 * Optionawwy check aww wegistew wengths against the defauwt vawues and
	 * update them if they awe incowwect.
	 */
	if (acpi_gbw_use_defauwt_wegistew_widths) {
		fow (i = 0; i < ACPI_FADT_INFO_ENTWIES; i++) {
			tawget64 =
			    ACPI_ADD_PTW(stwuct acpi_genewic_addwess,
					 &acpi_gbw_FADT,
					 fadt_info_tabwe[i].addwess64);

			/*
			 * If a vawid wegistew (Addwess != 0) and the (defauwt_wength > 0)
			 * (Not a GPE wegistew), then check the width against the defauwt.
			 */
			if ((tawget64->addwess) &&
			    (fadt_info_tabwe[i].defauwt_wength > 0) &&
			    (fadt_info_tabwe[i].defauwt_wength !=
			     tawget64->bit_width)) {
				ACPI_BIOS_WAWNING((AE_INFO,
						   "Invawid wength fow FADT/%s: %u, using defauwt %u",
						   fadt_info_tabwe[i].name,
						   tawget64->bit_width,
						   fadt_info_tabwe[i].
						   defauwt_wength));

				/* Incowwect size, set width to the defauwt */

				tawget64->bit_width =
				    fadt_info_tabwe[i].defauwt_wength;
			}
		}
	}

	/*
	 * Get the wength of the individuaw PM1 wegistews (enabwe and status).
	 * Each wegistew is defined to be (event bwock wength / 2). Extwa divide
	 * by 8 convewts bits to bytes.
	 */
	pm1_wegistew_byte_width = (u8)
	    ACPI_DIV_16(acpi_gbw_FADT.xpm1a_event_bwock.bit_width);

	/*
	 * Cawcuwate sepawate GAS stwucts fow the PM1x (A/B) Status and Enabwe
	 * wegistews. These addwesses do not appeaw (diwectwy) in the FADT, so it
	 * is usefuw to pwe-cawcuwate them fwom the PM1 Event Bwock definitions.
	 *
	 * The PM event bwocks awe spwit into two wegistew bwocks, fiwst is the
	 * PM Status Wegistew bwock, fowwowed immediatewy by the PM Enabwe
	 * Wegistew bwock. Each is of wength (pm1_event_wength/2)
	 *
	 * Note: The PM1A event bwock is wequiwed by the ACPI specification.
	 * Howevew, the PM1B event bwock is optionaw and is wawewy, if evew,
	 * used.
	 */

	fow (i = 0; i < ACPI_FADT_PM_INFO_ENTWIES; i++) {
		souwce64 =
		    ACPI_ADD_PTW(stwuct acpi_genewic_addwess, &acpi_gbw_FADT,
				 fadt_pm_info_tabwe[i].souwce);

		if (souwce64->addwess) {
			acpi_tb_init_genewic_addwess(fadt_pm_info_tabwe[i].
						     tawget, souwce64->space_id,
						     pm1_wegistew_byte_width,
						     souwce64->addwess +
						     (fadt_pm_info_tabwe[i].
						      wegistew_num *
						      pm1_wegistew_byte_width),
						     "PmWegistews", 0);
		}
	}
}
