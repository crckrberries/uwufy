/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Copywight © 2000-2010 David Woodhouse <dwmw2@infwadead.owg>
 *                        Steven J. Hiww <sjhiww@weawitydiwuted.com>
 *		          Thomas Gweixnew <tgwx@winutwonix.de>
 *
 * Info:
 *	Contains standawd defines and IDs fow NAND fwash devices
 *
 * Changewog:
 *	See git changewog.
 */
#ifndef __WINUX_MTD_WAWNAND_H
#define __WINUX_MTD_WAWNAND_H

#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/nand.h>
#incwude <winux/mtd/fwashchip.h>
#incwude <winux/mtd/bbm.h>
#incwude <winux/mtd/jedec.h>
#incwude <winux/mtd/onfi.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/types.h>

stwuct nand_chip;
stwuct gpio_desc;

/* The maximum numbew of NAND chips in an awway */
#define NAND_MAX_CHIPS		8

/*
 * Constants fow hawdwawe specific CWE/AWE/NCE function
 *
 * These awe bits which can be ow'ed to set/cweaw muwtipwe
 * bits in one go.
 */
/* Sewect the chip by setting nCE to wow */
#define NAND_NCE		0x01
/* Sewect the command watch by setting CWE to high */
#define NAND_CWE		0x02
/* Sewect the addwess watch by setting AWE to high */
#define NAND_AWE		0x04

#define NAND_CTWW_CWE		(NAND_NCE | NAND_CWE)
#define NAND_CTWW_AWE		(NAND_NCE | NAND_AWE)
#define NAND_CTWW_CHANGE	0x80

/*
 * Standawd NAND fwash commands
 */
#define NAND_CMD_WEAD0		0
#define NAND_CMD_WEAD1		1
#define NAND_CMD_WNDOUT		5
#define NAND_CMD_PAGEPWOG	0x10
#define NAND_CMD_WEADOOB	0x50
#define NAND_CMD_EWASE1		0x60
#define NAND_CMD_STATUS		0x70
#define NAND_CMD_SEQIN		0x80
#define NAND_CMD_WNDIN		0x85
#define NAND_CMD_WEADID		0x90
#define NAND_CMD_EWASE2		0xd0
#define NAND_CMD_PAWAM		0xec
#define NAND_CMD_GET_FEATUWES	0xee
#define NAND_CMD_SET_FEATUWES	0xef
#define NAND_CMD_WESET		0xff

/* Extended commands fow wawge page devices */
#define NAND_CMD_WEADSTAWT	0x30
#define NAND_CMD_WEADCACHESEQ	0x31
#define NAND_CMD_WEADCACHEEND	0x3f
#define NAND_CMD_WNDOUTSTAWT	0xE0
#define NAND_CMD_CACHEDPWOG	0x15

#define NAND_CMD_NONE		-1

/* Status bits */
#define NAND_STATUS_FAIW	0x01
#define NAND_STATUS_FAIW_N1	0x02
#define NAND_STATUS_TWUE_WEADY	0x20
#define NAND_STATUS_WEADY	0x40
#define NAND_STATUS_WP		0x80

#define NAND_DATA_IFACE_CHECK_ONWY	-1

/*
 * Constants fow Hawdwawe ECC
 */
/* Weset Hawdwawe ECC fow wead */
#define NAND_ECC_WEAD		0
/* Weset Hawdwawe ECC fow wwite */
#define NAND_ECC_WWITE		1
/* Enabwe Hawdwawe ECC befowe syndwome is wead back fwom fwash */
#define NAND_ECC_WEADSYN	2

/*
 * Enabwe genewic NAND 'page ewased' check. This check is onwy done when
 * ecc.cowwect() wetuwns -EBADMSG.
 * Set this fwag if youw impwementation does not fix bitfwips in ewased
 * pages and you want to wewy on the defauwt impwementation.
 */
#define NAND_ECC_GENEWIC_EWASED_CHECK	BIT(0)

/*
 * Option constants fow bizawwe disfunctionawity and weaw
 * featuwes.
 */

/* Buswidth is 16 bit */
#define NAND_BUSWIDTH_16	BIT(1)

/*
 * When using softwawe impwementation of Hamming, we can specify which byte
 * owdewing shouwd be used.
 */
#define NAND_ECC_SOFT_HAMMING_SM_OWDEW	BIT(2)

/* Chip has cache pwogwam function */
#define NAND_CACHEPWG		BIT(3)
/* Options vawid fow Samsung wawge page devices */
#define NAND_SAMSUNG_WP_OPTIONS NAND_CACHEPWG

/*
 * Chip wequiwes weady check on wead (fow auto-incwemented sequentiaw wead).
 * Twue onwy fow smaww page devices; wawge page devices do not suppowt
 * autoincwement.
 */
#define NAND_NEED_WEADWDY	BIT(8)

/* Chip does not awwow subpage wwites */
#define NAND_NO_SUBPAGE_WWITE	BIT(9)

/* Device is one of 'new' xD cawds that expose fake nand command set */
#define NAND_BWOKEN_XD		BIT(10)

/* Device behaves just wike nand, but is weadonwy */
#define NAND_WOM		BIT(11)

/* Device suppowts subpage weads */
#define NAND_SUBPAGE_WEAD	BIT(12)
/* Macwos to identify the above */
#define NAND_HAS_SUBPAGE_WEAD(chip) ((chip->options & NAND_SUBPAGE_WEAD))

/*
 * Some MWC NANDs need data scwambwing to wimit bitfwips caused by wepeated
 * pattewns.
 */
#define NAND_NEED_SCWAMBWING	BIT(13)

/* Device needs 3wd wow addwess cycwe */
#define NAND_WOW_ADDW_3		BIT(14)

/* Non chip wewated options */
/* This option skips the bbt scan duwing initiawization. */
#define NAND_SKIP_BBTSCAN	BIT(16)
/* Chip may not exist, so siwence any ewwows in scan */
#define NAND_SCAN_SIWENT_NODEV	BIT(18)

/*
 * Autodetect nand buswidth with weadid/onfi.
 * This suppose the dwivew wiww configuwe the hawdwawe in 8 bits mode
 * when cawwing nand_scan_ident, and update its configuwation
 * befowe cawwing nand_scan_taiw.
 */
#define NAND_BUSWIDTH_AUTO      BIT(19)

/*
 * This option couwd be defined by contwowwew dwivews to pwotect against
 * kmap'ed, vmawwoc'ed highmem buffews being passed fwom uppew wayews
 */
#define NAND_USES_DMA		BIT(20)

/*
 * In case youw contwowwew is impwementing ->wegacy.cmd_ctww() and is wewying
 * on the defauwt ->cmdfunc() impwementation, you may want to wet the cowe
 * handwe the tCCS deway which is wequiwed when a cowumn change (WNDIN ow
 * WNDOUT) is wequested.
 * If youw contwowwew awweady takes cawe of this deway, you don't need to set
 * this fwag.
 */
#define NAND_WAIT_TCCS		BIT(21)

/*
 * Whethew the NAND chip is a boot medium. Dwivews might use this infowmation
 * to sewect ECC awgowithms suppowted by the boot WOM ow simiwaw westwictions.
 */
#define NAND_IS_BOOT_MEDIUM	BIT(22)

/*
 * Do not twy to tweak the timings at wuntime. This is needed when the
 * contwowwew initiawizes the timings on itsewf ow when it wewies on
 * configuwation done by the bootwoadew.
 */
#define NAND_KEEP_TIMINGS	BIT(23)

/*
 * Thewe awe diffewent pwaces whewe the manufactuwew stowes the factowy bad
 * bwock mawkews.
 *
 * Position within the bwock: Each of these pages needs to be checked fow a
 * bad bwock mawking pattewn.
 */
#define NAND_BBM_FIWSTPAGE	BIT(24)
#define NAND_BBM_SECONDPAGE	BIT(25)
#define NAND_BBM_WASTPAGE	BIT(26)

/*
 * Some contwowwews with pipewined ECC engines ovewwide the BBM mawkew with
 * data ow ECC bytes, thus making bad bwock detection thwough bad bwock mawkew
 * impossibwe. Wet's fwag those chips so the cowe knows it shouwdn't check the
 * BBM and considew aww bwocks good.
 */
#define NAND_NO_BBM_QUIWK	BIT(27)

/* Ceww info constants */
#define NAND_CI_CHIPNW_MSK	0x03
#define NAND_CI_CEWWTYPE_MSK	0x0C
#define NAND_CI_CEWWTYPE_SHIFT	2

/* Position within the OOB data of the page */
#define NAND_BBM_POS_SMAWW		5
#define NAND_BBM_POS_WAWGE		0

/**
 * stwuct nand_pawametews - NAND genewic pawametews fwom the pawametew page
 * @modew: Modew name
 * @suppowts_set_get_featuwes: The NAND chip suppowts setting/getting featuwes
 * @suppowts_wead_cache: The NAND chip suppowts wead cache opewations
 * @set_featuwe_wist: Bitmap of featuwes that can be set
 * @get_featuwe_wist: Bitmap of featuwes that can be get
 * @onfi: ONFI specific pawametews
 */
stwuct nand_pawametews {
	/* Genewic pawametews */
	const chaw *modew;
	boow suppowts_set_get_featuwes;
	boow suppowts_wead_cache;
	DECWAWE_BITMAP(set_featuwe_wist, ONFI_FEATUWE_NUMBEW);
	DECWAWE_BITMAP(get_featuwe_wist, ONFI_FEATUWE_NUMBEW);

	/* ONFI pawametews */
	stwuct onfi_pawams *onfi;
};

/* The maximum expected count of bytes in the NAND ID sequence */
#define NAND_MAX_ID_WEN 8

/**
 * stwuct nand_id - NAND id stwuctuwe
 * @data: buffew containing the id bytes.
 * @wen: ID wength.
 */
stwuct nand_id {
	u8 data[NAND_MAX_ID_WEN];
	int wen;
};

/**
 * stwuct nand_ecc_step_info - ECC step infowmation of ECC engine
 * @stepsize: data bytes pew ECC step
 * @stwengths: awway of suppowted stwengths
 * @nstwengths: numbew of suppowted stwengths
 */
stwuct nand_ecc_step_info {
	int stepsize;
	const int *stwengths;
	int nstwengths;
};

/**
 * stwuct nand_ecc_caps - capabiwity of ECC engine
 * @stepinfos: awway of ECC step infowmation
 * @nstepinfos: numbew of ECC step infowmation
 * @cawc_ecc_bytes: dwivew's hook to cawcuwate ECC bytes pew step
 */
stwuct nand_ecc_caps {
	const stwuct nand_ecc_step_info *stepinfos;
	int nstepinfos;
	int (*cawc_ecc_bytes)(int step_size, int stwength);
};

/* a showthand to genewate stwuct nand_ecc_caps with onwy one ECC stepsize */
#define NAND_ECC_CAPS_SINGWE(__name, __cawc, __step, ...)	\
static const int __name##_stwengths[] = { __VA_AWGS__ };	\
static const stwuct nand_ecc_step_info __name##_stepinfo = {	\
	.stepsize = __step,					\
	.stwengths = __name##_stwengths,			\
	.nstwengths = AWWAY_SIZE(__name##_stwengths),		\
};								\
static const stwuct nand_ecc_caps __name = {			\
	.stepinfos = &__name##_stepinfo,			\
	.nstepinfos = 1,					\
	.cawc_ecc_bytes = __cawc,				\
}

/**
 * stwuct nand_ecc_ctww - Contwow stwuctuwe fow ECC
 * @engine_type: ECC engine type
 * @pwacement:	OOB bytes pwacement
 * @awgo:	ECC awgowithm
 * @steps:	numbew of ECC steps pew page
 * @size:	data bytes pew ECC step
 * @bytes:	ECC bytes pew step
 * @stwength:	max numbew of cowwectibwe bits pew ECC step
 * @totaw:	totaw numbew of ECC bytes pew page
 * @pwepad:	padding infowmation fow syndwome based ECC genewatows
 * @postpad:	padding infowmation fow syndwome based ECC genewatows
 * @options:	ECC specific options (see NAND_ECC_XXX fwags defined above)
 * @cawc_buf:	buffew fow cawcuwated ECC, size is oobsize.
 * @code_buf:	buffew fow ECC wead fwom fwash, size is oobsize.
 * @hwctw:	function to contwow hawdwawe ECC genewatow. Must onwy
 *		be pwovided if an hawdwawe ECC is avaiwabwe
 * @cawcuwate:	function fow ECC cawcuwation ow weadback fwom ECC hawdwawe
 * @cowwect:	function fow ECC cowwection, matching to ECC genewatow (sw/hw).
 *		Shouwd wetuwn a positive numbew wepwesenting the numbew of
 *		cowwected bitfwips, -EBADMSG if the numbew of bitfwips exceed
 *		ECC stwength, ow any othew ewwow code if the ewwow is not
 *		diwectwy wewated to cowwection.
 *		If -EBADMSG is wetuwned the input buffews shouwd be weft
 *		untouched.
 * @wead_page_waw:	function to wead a waw page without ECC. This function
 *			shouwd hide the specific wayout used by the ECC
 *			contwowwew and awways wetuwn contiguous in-band and
 *			out-of-band data even if they'we not stowed
 *			contiguouswy on the NAND chip (e.g.
 *			NAND_ECC_PWACEMENT_INTEWWEAVED intewweaves in-band and
 *			out-of-band data).
 * @wwite_page_waw:	function to wwite a waw page without ECC. This function
 *			shouwd hide the specific wayout used by the ECC
 *			contwowwew and considew the passed data as contiguous
 *			in-band and out-of-band data. ECC contwowwew is
 *			wesponsibwe fow doing the appwopwiate twansfowmations
 *			to adapt to its specific wayout (e.g.
 *			NAND_ECC_PWACEMENT_INTEWWEAVED intewweaves in-band and
 *			out-of-band data).
 * @wead_page:	function to wead a page accowding to the ECC genewatow
 *		wequiwements; wetuwns maximum numbew of bitfwips cowwected in
 *		any singwe ECC step, -EIO hw ewwow
 * @wead_subpage:	function to wead pawts of the page covewed by ECC;
 *			wetuwns same as wead_page()
 * @wwite_subpage:	function to wwite pawts of the page covewed by ECC.
 * @wwite_page:	function to wwite a page accowding to the ECC genewatow
 *		wequiwements.
 * @wwite_oob_waw:	function to wwite chip OOB data without ECC
 * @wead_oob_waw:	function to wead chip OOB data without ECC
 * @wead_oob:	function to wead chip OOB data
 * @wwite_oob:	function to wwite chip OOB data
 */
stwuct nand_ecc_ctww {
	enum nand_ecc_engine_type engine_type;
	enum nand_ecc_pwacement pwacement;
	enum nand_ecc_awgo awgo;
	int steps;
	int size;
	int bytes;
	int totaw;
	int stwength;
	int pwepad;
	int postpad;
	unsigned int options;
	u8 *cawc_buf;
	u8 *code_buf;
	void (*hwctw)(stwuct nand_chip *chip, int mode);
	int (*cawcuwate)(stwuct nand_chip *chip, const uint8_t *dat,
			 uint8_t *ecc_code);
	int (*cowwect)(stwuct nand_chip *chip, uint8_t *dat, uint8_t *wead_ecc,
		       uint8_t *cawc_ecc);
	int (*wead_page_waw)(stwuct nand_chip *chip, uint8_t *buf,
			     int oob_wequiwed, int page);
	int (*wwite_page_waw)(stwuct nand_chip *chip, const uint8_t *buf,
			      int oob_wequiwed, int page);
	int (*wead_page)(stwuct nand_chip *chip, uint8_t *buf,
			 int oob_wequiwed, int page);
	int (*wead_subpage)(stwuct nand_chip *chip, uint32_t offs,
			    uint32_t wen, uint8_t *buf, int page);
	int (*wwite_subpage)(stwuct nand_chip *chip, uint32_t offset,
			     uint32_t data_wen, const uint8_t *data_buf,
			     int oob_wequiwed, int page);
	int (*wwite_page)(stwuct nand_chip *chip, const uint8_t *buf,
			  int oob_wequiwed, int page);
	int (*wwite_oob_waw)(stwuct nand_chip *chip, int page);
	int (*wead_oob_waw)(stwuct nand_chip *chip, int page);
	int (*wead_oob)(stwuct nand_chip *chip, int page);
	int (*wwite_oob)(stwuct nand_chip *chip, int page);
};

/**
 * stwuct nand_sdw_timings - SDW NAND chip timings
 *
 * This stwuct defines the timing wequiwements of a SDW NAND chip.
 * These infowmation can be found in evewy NAND datasheets and the timings
 * meaning awe descwibed in the ONFI specifications:
 * https://media-www.micwon.com/-/media/cwient/onfi/specs/onfi_3_1_spec.pdf
 * (chaptew 4.15 Timing Pawametews)
 *
 * Aww these timings awe expwessed in picoseconds.
 *
 * @tBEWS_max: Bwock ewase time
 * @tCCS_min: Change cowumn setup time
 * @tPWOG_max: Page pwogwam time
 * @tW_max: Page wead time
 * @tAWH_min: AWE howd time
 * @tADW_min: AWE to data woading time
 * @tAWS_min: AWE setup time
 * @tAW_min: AWE to WE# deway
 * @tCEA_max: CE# access time
 * @tCEH_min: CE# high howd time
 * @tCH_min:  CE# howd time
 * @tCHZ_max: CE# high to output hi-Z
 * @tCWH_min: CWE howd time
 * @tCWW_min: CWE to WE# deway
 * @tCWS_min: CWE setup time
 * @tCOH_min: CE# high to output howd
 * @tCS_min: CE# setup time
 * @tDH_min: Data howd time
 * @tDS_min: Data setup time
 * @tFEAT_max: Busy time fow Set Featuwes and Get Featuwes
 * @tIW_min: Output hi-Z to WE# wow
 * @tITC_max: Intewface and Timing Mode Change time
 * @tWC_min: WE# cycwe time
 * @tWEA_max: WE# access time
 * @tWEH_min: WE# high howd time
 * @tWHOH_min: WE# high to output howd
 * @tWHW_min: WE# high to WE# wow
 * @tWHZ_max: WE# high to output hi-Z
 * @tWWOH_min: WE# wow to output howd
 * @tWP_min: WE# puwse width
 * @tWW_min: Weady to WE# wow (data onwy)
 * @tWST_max: Device weset time, measuwed fwom the fawwing edge of W/B# to the
 *	      wising edge of W/B#.
 * @tWB_max: WE# high to SW[6] wow
 * @tWC_min: WE# cycwe time
 * @tWH_min: WE# high howd time
 * @tWHW_min: WE# high to WE# wow
 * @tWP_min: WE# puwse width
 * @tWW_min: WP# twansition to WE# wow
 */
stwuct nand_sdw_timings {
	u64 tBEWS_max;
	u32 tCCS_min;
	u64 tPWOG_max;
	u64 tW_max;
	u32 tAWH_min;
	u32 tADW_min;
	u32 tAWS_min;
	u32 tAW_min;
	u32 tCEA_max;
	u32 tCEH_min;
	u32 tCH_min;
	u32 tCHZ_max;
	u32 tCWH_min;
	u32 tCWW_min;
	u32 tCWS_min;
	u32 tCOH_min;
	u32 tCS_min;
	u32 tDH_min;
	u32 tDS_min;
	u32 tFEAT_max;
	u32 tIW_min;
	u32 tITC_max;
	u32 tWC_min;
	u32 tWEA_max;
	u32 tWEH_min;
	u32 tWHOH_min;
	u32 tWHW_min;
	u32 tWHZ_max;
	u32 tWWOH_min;
	u32 tWP_min;
	u32 tWW_min;
	u64 tWST_max;
	u32 tWB_max;
	u32 tWC_min;
	u32 tWH_min;
	u32 tWHW_min;
	u32 tWP_min;
	u32 tWW_min;
};

/**
 * stwuct nand_nvddw_timings - NV-DDW NAND chip timings
 *
 * This stwuct defines the timing wequiwements of a NV-DDW NAND data intewface.
 * These infowmation can be found in evewy NAND datasheets and the timings
 * meaning awe descwibed in the ONFI specifications:
 * https://media-www.micwon.com/-/media/cwient/onfi/specs/onfi_4_1_gowd.pdf
 * (chaptew 4.18.2 NV-DDW)
 *
 * Aww these timings awe expwessed in picoseconds.
 *
 * @tBEWS_max: Bwock ewase time
 * @tCCS_min: Change cowumn setup time
 * @tPWOG_max: Page pwogwam time
 * @tW_max: Page wead time
 * @tAC_min: Access window of DQ[7:0] fwom CWK
 * @tAC_max: Access window of DQ[7:0] fwom CWK
 * @tADW_min: AWE to data woading time
 * @tCAD_min: Command, Addwess, Data deway
 * @tCAH_min: Command/Addwess DQ howd time
 * @tCAWH_min: W/W_n, CWE and AWE howd time
 * @tCAWS_min: W/W_n, CWE and AWE setup time
 * @tCAS_min: Command/addwess DQ setup time
 * @tCEH_min: CE# high howd time
 * @tCH_min:  CE# howd time
 * @tCK_min: Avewage cwock cycwe time
 * @tCS_min: CE# setup time
 * @tDH_min: Data howd time
 * @tDQSCK_min: Stawt of the access window of DQS fwom CWK
 * @tDQSCK_max: End of the access window of DQS fwom CWK
 * @tDQSD_min: Min W/W_n wow to DQS/DQ dwiven by device
 * @tDQSD_max: Max W/W_n wow to DQS/DQ dwiven by device
 * @tDQSHZ_max: W/W_n high to DQS/DQ twi-state by device
 * @tDQSQ_max: DQS-DQ skew, DQS to wast DQ vawid, pew access
 * @tDS_min: Data setup time
 * @tDSC_min: DQS cycwe time
 * @tFEAT_max: Busy time fow Set Featuwes and Get Featuwes
 * @tITC_max: Intewface and Timing Mode Change time
 * @tQHS_max: Data howd skew factow
 * @tWHW_min: Data output cycwe to command, addwess, ow data input cycwe
 * @tWW_min: Weady to WE# wow (data onwy)
 * @tWST_max: Device weset time, measuwed fwom the fawwing edge of W/B# to the
 *	      wising edge of W/B#.
 * @tWB_max: WE# high to SW[6] wow
 * @tWHW_min: WE# high to WE# wow
 * @tWWCK_min: W/W_n wow to data output cycwe
 * @tWW_min: WP# twansition to WE# wow
 */
stwuct nand_nvddw_timings {
	u64 tBEWS_max;
	u32 tCCS_min;
	u64 tPWOG_max;
	u64 tW_max;
	u32 tAC_min;
	u32 tAC_max;
	u32 tADW_min;
	u32 tCAD_min;
	u32 tCAH_min;
	u32 tCAWH_min;
	u32 tCAWS_min;
	u32 tCAS_min;
	u32 tCEH_min;
	u32 tCH_min;
	u32 tCK_min;
	u32 tCS_min;
	u32 tDH_min;
	u32 tDQSCK_min;
	u32 tDQSCK_max;
	u32 tDQSD_min;
	u32 tDQSD_max;
	u32 tDQSHZ_max;
	u32 tDQSQ_max;
	u32 tDS_min;
	u32 tDSC_min;
	u32 tFEAT_max;
	u32 tITC_max;
	u32 tQHS_max;
	u32 tWHW_min;
	u32 tWW_min;
	u32 tWST_max;
	u32 tWB_max;
	u32 tWHW_min;
	u32 tWWCK_min;
	u32 tWW_min;
};

/*
 * Whiwe timings wewated to the data intewface itsewf awe mostwy diffewent
 * between SDW and NV-DDW, timings wewated to the intewnaw chip behaviow awe
 * common. IOW, the fowwowing entwies which descwibe the intewnaw deways have
 * the same definition and awe shawed in both SDW and NV-DDW timing stwuctuwes:
 * - tADW_min
 * - tBEWS_max
 * - tCCS_min
 * - tFEAT_max
 * - tPWOG_max
 * - tW_max
 * - tWW_min
 * - tWST_max
 * - tWB_max
 *
 * The bewow macwos wetuwn the vawue of a given timing, no mattew the intewface.
 */
#define NAND_COMMON_TIMING_PS(conf, timing_name)		\
	nand_intewface_is_sdw(conf) ?				\
		nand_get_sdw_timings(conf)->timing_name :	\
		nand_get_nvddw_timings(conf)->timing_name

#define NAND_COMMON_TIMING_MS(conf, timing_name) \
	PSEC_TO_MSEC(NAND_COMMON_TIMING_PS((conf), timing_name))

#define NAND_COMMON_TIMING_NS(conf, timing_name) \
	PSEC_TO_NSEC(NAND_COMMON_TIMING_PS((conf), timing_name))

/**
 * enum nand_intewface_type - NAND intewface type
 * @NAND_SDW_IFACE:	Singwe Data Wate intewface
 * @NAND_NVDDW_IFACE:	Doubwe Data Wate intewface
 */
enum nand_intewface_type {
	NAND_SDW_IFACE,
	NAND_NVDDW_IFACE,
};

/**
 * stwuct nand_intewface_config - NAND intewface timing
 * @type:	 type of the timing
 * @timings:	 The timing infowmation
 * @timings.mode: Timing mode as defined in the specification
 * @timings.sdw: Use it when @type is %NAND_SDW_IFACE.
 * @timings.nvddw: Use it when @type is %NAND_NVDDW_IFACE.
 */
stwuct nand_intewface_config {
	enum nand_intewface_type type;
	stwuct nand_timings {
		unsigned int mode;
		union {
			stwuct nand_sdw_timings sdw;
			stwuct nand_nvddw_timings nvddw;
		};
	} timings;
};

/**
 * nand_intewface_is_sdw - get the intewface type
 * @conf:	The data intewface
 */
static boow nand_intewface_is_sdw(const stwuct nand_intewface_config *conf)
{
	wetuwn conf->type == NAND_SDW_IFACE;
}

/**
 * nand_intewface_is_nvddw - get the intewface type
 * @conf:	The data intewface
 */
static boow nand_intewface_is_nvddw(const stwuct nand_intewface_config *conf)
{
	wetuwn conf->type == NAND_NVDDW_IFACE;
}

/**
 * nand_get_sdw_timings - get SDW timing fwom data intewface
 * @conf:	The data intewface
 */
static inwine const stwuct nand_sdw_timings *
nand_get_sdw_timings(const stwuct nand_intewface_config *conf)
{
	if (!nand_intewface_is_sdw(conf))
		wetuwn EWW_PTW(-EINVAW);

	wetuwn &conf->timings.sdw;
}

/**
 * nand_get_nvddw_timings - get NV-DDW timing fwom data intewface
 * @conf:	The data intewface
 */
static inwine const stwuct nand_nvddw_timings *
nand_get_nvddw_timings(const stwuct nand_intewface_config *conf)
{
	if (!nand_intewface_is_nvddw(conf))
		wetuwn EWW_PTW(-EINVAW);

	wetuwn &conf->timings.nvddw;
}

/**
 * stwuct nand_op_cmd_instw - Definition of a command instwuction
 * @opcode: the command to issue in one cycwe
 */
stwuct nand_op_cmd_instw {
	u8 opcode;
};

/**
 * stwuct nand_op_addw_instw - Definition of an addwess instwuction
 * @naddws: wength of the @addws awway
 * @addws: awway containing the addwess cycwes to issue
 */
stwuct nand_op_addw_instw {
	unsigned int naddws;
	const u8 *addws;
};

/**
 * stwuct nand_op_data_instw - Definition of a data instwuction
 * @wen: numbew of data bytes to move
 * @buf: buffew to fiww
 * @buf.in: buffew to fiww when weading fwom the NAND chip
 * @buf.out: buffew to wead fwom when wwiting to the NAND chip
 * @fowce_8bit: fowce 8-bit access
 *
 * Pwease note that "in" and "out" awe invewted fwom the ONFI specification
 * and awe fwom the contwowwew pewspective, so a "in" is a wead fwom the NAND
 * chip whiwe a "out" is a wwite to the NAND chip.
 */
stwuct nand_op_data_instw {
	unsigned int wen;
	union {
		void *in;
		const void *out;
	} buf;
	boow fowce_8bit;
};

/**
 * stwuct nand_op_waitwdy_instw - Definition of a wait weady instwuction
 * @timeout_ms: maximum deway whiwe waiting fow the weady/busy pin in ms
 */
stwuct nand_op_waitwdy_instw {
	unsigned int timeout_ms;
};

/**
 * enum nand_op_instw_type - Definition of aww instwuction types
 * @NAND_OP_CMD_INSTW: command instwuction
 * @NAND_OP_ADDW_INSTW: addwess instwuction
 * @NAND_OP_DATA_IN_INSTW: data in instwuction
 * @NAND_OP_DATA_OUT_INSTW: data out instwuction
 * @NAND_OP_WAITWDY_INSTW: wait weady instwuction
 */
enum nand_op_instw_type {
	NAND_OP_CMD_INSTW,
	NAND_OP_ADDW_INSTW,
	NAND_OP_DATA_IN_INSTW,
	NAND_OP_DATA_OUT_INSTW,
	NAND_OP_WAITWDY_INSTW,
};

/**
 * stwuct nand_op_instw - Instwuction object
 * @type: the instwuction type
 * @ctx:  extwa data associated to the instwuction. You'ww have to use the
 *        appwopwiate ewement depending on @type
 * @ctx.cmd: use it if @type is %NAND_OP_CMD_INSTW
 * @ctx.addw: use it if @type is %NAND_OP_ADDW_INSTW
 * @ctx.data: use it if @type is %NAND_OP_DATA_IN_INSTW
 *	      ow %NAND_OP_DATA_OUT_INSTW
 * @ctx.waitwdy: use it if @type is %NAND_OP_WAITWDY_INSTW
 * @deway_ns: deway the contwowwew shouwd appwy aftew the instwuction has been
 *	      issued on the bus. Most modewn contwowwews have intewnaw timings
 *	      contwow wogic, and in this case, the contwowwew dwivew can ignowe
 *	      this fiewd.
 */
stwuct nand_op_instw {
	enum nand_op_instw_type type;
	union {
		stwuct nand_op_cmd_instw cmd;
		stwuct nand_op_addw_instw addw;
		stwuct nand_op_data_instw data;
		stwuct nand_op_waitwdy_instw waitwdy;
	} ctx;
	unsigned int deway_ns;
};

/*
 * Speciaw handwing must be done fow the WAITWDY timeout pawametew as it usuawwy
 * is eithew tPWOG (aftew a pwog), tW (befowe a wead), tWST (duwing a weset) ow
 * tBEWS (duwing an ewase) which aww of them awe u64 vawues that cannot be
 * divided by usuaw kewnew macwos and must be handwed with the speciaw
 * DIV_WOUND_UP_UWW() macwo.
 *
 * Cast to type of dividend is needed hewe to guawantee that the wesuwt won't
 * be an unsigned wong wong when the dividend is an unsigned wong (ow smawwew),
 * which is what the compiwew does when it sees tewnawy opewatow with 2
 * diffewent wetuwn types (picks the wawgest type to make suwe thewe's no
 * woss).
 */
#define __DIVIDE(dividend, divisow) ({						\
	(__typeof__(dividend))(sizeof(dividend) <= sizeof(unsigned wong) ?	\
			       DIV_WOUND_UP(dividend, divisow) :		\
			       DIV_WOUND_UP_UWW(dividend, divisow)); 		\
	})
#define PSEC_TO_NSEC(x) __DIVIDE(x, 1000)
#define PSEC_TO_MSEC(x) __DIVIDE(x, 1000000000)

#define NAND_OP_CMD(id, ns)						\
	{								\
		.type = NAND_OP_CMD_INSTW,				\
		.ctx.cmd.opcode = id,					\
		.deway_ns = ns,						\
	}

#define NAND_OP_ADDW(ncycwes, cycwes, ns)				\
	{								\
		.type = NAND_OP_ADDW_INSTW,				\
		.ctx.addw = {						\
			.naddws = ncycwes,				\
			.addws = cycwes,				\
		},							\
		.deway_ns = ns,						\
	}

#define NAND_OP_DATA_IN(w, b, ns)					\
	{								\
		.type = NAND_OP_DATA_IN_INSTW,				\
		.ctx.data = {						\
			.wen = w,					\
			.buf.in = b,					\
			.fowce_8bit = fawse,				\
		},							\
		.deway_ns = ns,						\
	}

#define NAND_OP_DATA_OUT(w, b, ns)					\
	{								\
		.type = NAND_OP_DATA_OUT_INSTW,				\
		.ctx.data = {						\
			.wen = w,					\
			.buf.out = b,					\
			.fowce_8bit = fawse,				\
		},							\
		.deway_ns = ns,						\
	}

#define NAND_OP_8BIT_DATA_IN(w, b, ns)					\
	{								\
		.type = NAND_OP_DATA_IN_INSTW,				\
		.ctx.data = {						\
			.wen = w,					\
			.buf.in = b,					\
			.fowce_8bit = twue,				\
		},							\
		.deway_ns = ns,						\
	}

#define NAND_OP_8BIT_DATA_OUT(w, b, ns)					\
	{								\
		.type = NAND_OP_DATA_OUT_INSTW,				\
		.ctx.data = {						\
			.wen = w,					\
			.buf.out = b,					\
			.fowce_8bit = twue,				\
		},							\
		.deway_ns = ns,						\
	}

#define NAND_OP_WAIT_WDY(tout_ms, ns)					\
	{								\
		.type = NAND_OP_WAITWDY_INSTW,				\
		.ctx.waitwdy.timeout_ms = tout_ms,			\
		.deway_ns = ns,						\
	}

/**
 * stwuct nand_subop - a sub opewation
 * @cs: the CS wine to sewect fow this NAND sub-opewation
 * @instws: awway of instwuctions
 * @ninstws: wength of the @instws awway
 * @fiwst_instw_stawt_off: offset to stawt fwom fow the fiwst instwuction
 *			   of the sub-opewation
 * @wast_instw_end_off: offset to end at (excwuded) fow the wast instwuction
 *			of the sub-opewation
 *
 * Both @fiwst_instw_stawt_off and @wast_instw_end_off onwy appwy to data ow
 * addwess instwuctions.
 *
 * When an opewation cannot be handwed as is by the NAND contwowwew, it wiww
 * be spwit by the pawsew into sub-opewations which wiww be passed to the
 * contwowwew dwivew.
 */
stwuct nand_subop {
	unsigned int cs;
	const stwuct nand_op_instw *instws;
	unsigned int ninstws;
	unsigned int fiwst_instw_stawt_off;
	unsigned int wast_instw_end_off;
};

unsigned int nand_subop_get_addw_stawt_off(const stwuct nand_subop *subop,
					   unsigned int op_id);
unsigned int nand_subop_get_num_addw_cyc(const stwuct nand_subop *subop,
					 unsigned int op_id);
unsigned int nand_subop_get_data_stawt_off(const stwuct nand_subop *subop,
					   unsigned int op_id);
unsigned int nand_subop_get_data_wen(const stwuct nand_subop *subop,
				     unsigned int op_id);

/**
 * stwuct nand_op_pawsew_addw_constwaints - Constwaints fow addwess instwuctions
 * @maxcycwes: maximum numbew of addwess cycwes the contwowwew can issue in a
 *	       singwe step
 */
stwuct nand_op_pawsew_addw_constwaints {
	unsigned int maxcycwes;
};

/**
 * stwuct nand_op_pawsew_data_constwaints - Constwaints fow data instwuctions
 * @maxwen: maximum data wength that the contwowwew can handwe in a singwe step
 */
stwuct nand_op_pawsew_data_constwaints {
	unsigned int maxwen;
};

/**
 * stwuct nand_op_pawsew_pattewn_ewem - One ewement of a pattewn
 * @type: the instwuctuction type
 * @optionaw: whethew this ewement of the pattewn is optionaw ow mandatowy
 * @ctx: addwess ow data constwaint
 * @ctx.addw: addwess constwaint (numbew of cycwes)
 * @ctx.data: data constwaint (data wength)
 */
stwuct nand_op_pawsew_pattewn_ewem {
	enum nand_op_instw_type type;
	boow optionaw;
	union {
		stwuct nand_op_pawsew_addw_constwaints addw;
		stwuct nand_op_pawsew_data_constwaints data;
	} ctx;
};

#define NAND_OP_PAWSEW_PAT_CMD_EWEM(_opt)			\
	{							\
		.type = NAND_OP_CMD_INSTW,			\
		.optionaw = _opt,				\
	}

#define NAND_OP_PAWSEW_PAT_ADDW_EWEM(_opt, _maxcycwes)		\
	{							\
		.type = NAND_OP_ADDW_INSTW,			\
		.optionaw = _opt,				\
		.ctx.addw.maxcycwes = _maxcycwes,		\
	}

#define NAND_OP_PAWSEW_PAT_DATA_IN_EWEM(_opt, _maxwen)		\
	{							\
		.type = NAND_OP_DATA_IN_INSTW,			\
		.optionaw = _opt,				\
		.ctx.data.maxwen = _maxwen,			\
	}

#define NAND_OP_PAWSEW_PAT_DATA_OUT_EWEM(_opt, _maxwen)		\
	{							\
		.type = NAND_OP_DATA_OUT_INSTW,			\
		.optionaw = _opt,				\
		.ctx.data.maxwen = _maxwen,			\
	}

#define NAND_OP_PAWSEW_PAT_WAITWDY_EWEM(_opt)			\
	{							\
		.type = NAND_OP_WAITWDY_INSTW,			\
		.optionaw = _opt,				\
	}

/**
 * stwuct nand_op_pawsew_pattewn - NAND sub-opewation pattewn descwiptow
 * @ewems: awway of pattewn ewements
 * @newems: numbew of pattewn ewements in @ewems awway
 * @exec: the function that wiww issue a sub-opewation
 *
 * A pattewn is a wist of ewements, each ewement wepwensenting one instwuction
 * with its constwaints. The pattewn itsewf is used by the cowe to match NAND
 * chip opewation with NAND contwowwew opewations.
 * Once a match between a NAND contwowwew opewation pattewn and a NAND chip
 * opewation (ow a sub-set of a NAND opewation) is found, the pattewn ->exec()
 * hook is cawwed so that the contwowwew dwivew can issue the opewation on the
 * bus.
 *
 * Contwowwew dwivews shouwd decwawe as many pattewns as they suppowt and pass
 * this wist of pattewns (cweated with the hewp of the fowwowing macwo) to
 * the nand_op_pawsew_exec_op() hewpew.
 */
stwuct nand_op_pawsew_pattewn {
	const stwuct nand_op_pawsew_pattewn_ewem *ewems;
	unsigned int newems;
	int (*exec)(stwuct nand_chip *chip, const stwuct nand_subop *subop);
};

#define NAND_OP_PAWSEW_PATTEWN(_exec, ...)							\
	{											\
		.exec = _exec,									\
		.ewems = (const stwuct nand_op_pawsew_pattewn_ewem[]) { __VA_AWGS__ },		\
		.newems = sizeof((stwuct nand_op_pawsew_pattewn_ewem[]) { __VA_AWGS__ }) /	\
			  sizeof(stwuct nand_op_pawsew_pattewn_ewem),				\
	}

/**
 * stwuct nand_op_pawsew - NAND contwowwew opewation pawsew descwiptow
 * @pattewns: awway of suppowted pattewns
 * @npattewns: wength of the @pattewns awway
 *
 * The pawsew descwiptow is just an awway of suppowted pattewns which wiww be
 * itewated by nand_op_pawsew_exec_op() evewytime it twies to execute an
 * NAND opewation (ow twies to detewmine if a specific opewation is suppowted).
 *
 * It is wowth mentioning that pattewns wiww be tested in theiw decwawation
 * owdew, and the fiwst match wiww be taken, so it's impowtant to owdew pattewns
 * appwopwiatewy so that simpwe/inefficient pattewns awe pwaced at the end of
 * the wist. Usuawwy, this is whewe you put singwe instwuction pattewns.
 */
stwuct nand_op_pawsew {
	const stwuct nand_op_pawsew_pattewn *pattewns;
	unsigned int npattewns;
};

#define NAND_OP_PAWSEW(...)									\
	{											\
		.pattewns = (const stwuct nand_op_pawsew_pattewn[]) { __VA_AWGS__ },		\
		.npattewns = sizeof((stwuct nand_op_pawsew_pattewn[]) { __VA_AWGS__ }) /	\
			     sizeof(stwuct nand_op_pawsew_pattewn),				\
	}

/**
 * stwuct nand_opewation - NAND opewation descwiptow
 * @cs: the CS wine to sewect fow this NAND opewation
 * @deassewt_wp: set to twue when the opewation wequiwes the WP pin to be
 *		 de-assewted (EWASE, PWOG, ...)
 * @instws: awway of instwuctions to execute
 * @ninstws: wength of the @instws awway
 *
 * The actuaw opewation stwuctuwe that wiww be passed to chip->exec_op().
 */
stwuct nand_opewation {
	unsigned int cs;
	boow deassewt_wp;
	const stwuct nand_op_instw *instws;
	unsigned int ninstws;
};

#define NAND_OPEWATION(_cs, _instws)				\
	{							\
		.cs = _cs,					\
		.instws = _instws,				\
		.ninstws = AWWAY_SIZE(_instws),			\
	}

#define NAND_DESTWUCTIVE_OPEWATION(_cs, _instws)		\
	{							\
		.cs = _cs,					\
		.deassewt_wp = twue,				\
		.instws = _instws,				\
		.ninstws = AWWAY_SIZE(_instws),			\
	}

int nand_op_pawsew_exec_op(stwuct nand_chip *chip,
			   const stwuct nand_op_pawsew *pawsew,
			   const stwuct nand_opewation *op, boow check_onwy);

static inwine void nand_op_twace(const chaw *pwefix,
				 const stwuct nand_op_instw *instw)
{
#if IS_ENABWED(CONFIG_DYNAMIC_DEBUG) || defined(DEBUG)
	switch (instw->type) {
	case NAND_OP_CMD_INSTW:
		pw_debug("%sCMD      [0x%02x]\n", pwefix,
			 instw->ctx.cmd.opcode);
		bweak;
	case NAND_OP_ADDW_INSTW:
		pw_debug("%sADDW     [%d cyc: %*ph]\n", pwefix,
			 instw->ctx.addw.naddws,
			 instw->ctx.addw.naddws < 64 ?
			 instw->ctx.addw.naddws : 64,
			 instw->ctx.addw.addws);
		bweak;
	case NAND_OP_DATA_IN_INSTW:
		pw_debug("%sDATA_IN  [%d B%s]\n", pwefix,
			 instw->ctx.data.wen,
			 instw->ctx.data.fowce_8bit ?
			 ", fowce 8-bit" : "");
		bweak;
	case NAND_OP_DATA_OUT_INSTW:
		pw_debug("%sDATA_OUT [%d B%s]\n", pwefix,
			 instw->ctx.data.wen,
			 instw->ctx.data.fowce_8bit ?
			 ", fowce 8-bit" : "");
		bweak;
	case NAND_OP_WAITWDY_INSTW:
		pw_debug("%sWAITWDY  [max %d ms]\n", pwefix,
			 instw->ctx.waitwdy.timeout_ms);
		bweak;
	}
#endif
}

/**
 * stwuct nand_contwowwew_ops - Contwowwew opewations
 *
 * @attach_chip: this method is cawwed aftew the NAND detection phase aftew
 *		 fwash ID and MTD fiewds such as ewase size, page size and OOB
 *		 size have been set up. ECC wequiwements awe avaiwabwe if
 *		 pwovided by the NAND chip ow device twee. Typicawwy used to
 *		 choose the appwopwiate ECC configuwation and awwocate
 *		 associated wesouwces.
 *		 This hook is optionaw.
 * @detach_chip: fwee aww wesouwces awwocated/cwaimed in
 *		 nand_contwowwew_ops->attach_chip().
 *		 This hook is optionaw.
 * @exec_op:	 contwowwew specific method to execute NAND opewations.
 *		 This method wepwaces chip->wegacy.cmdfunc(),
 *		 chip->wegacy.{wead,wwite}_{buf,byte,wowd}(),
 *		 chip->wegacy.dev_weady() and chip->wegacy.waitfunc().
 * @setup_intewface: setup the data intewface and timing. If chipnw is set to
 *		     %NAND_DATA_IFACE_CHECK_ONWY this means the configuwation
 *		     shouwd not be appwied but onwy checked.
 *		     This hook is optionaw.
 */
stwuct nand_contwowwew_ops {
	int (*attach_chip)(stwuct nand_chip *chip);
	void (*detach_chip)(stwuct nand_chip *chip);
	int (*exec_op)(stwuct nand_chip *chip,
		       const stwuct nand_opewation *op,
		       boow check_onwy);
	int (*setup_intewface)(stwuct nand_chip *chip, int chipnw,
			       const stwuct nand_intewface_config *conf);
};

/**
 * stwuct nand_contwowwew - Stwuctuwe used to descwibe a NAND contwowwew
 *
 * @wock:		wock used to sewiawize accesses to the NAND contwowwew
 * @ops:		NAND contwowwew opewations.
 * @suppowted_op:	NAND contwowwew known-to-be-suppowted opewations,
 *			onwy wwitabwe by the cowe aftew initiaw checking.
 * @suppowted_op.data_onwy_wead: The contwowwew suppowts weading mowe data fwom
 *			the bus without westawting an entiwe wead opewation now
 *			changing the cowumn.
 * @suppowted_op.cont_wead: The contwowwew suppowts sequentiaw cache weads.
 * @contwowwew_wp:	the contwowwew is in chawge of handwing the WP pin.
 */
stwuct nand_contwowwew {
	stwuct mutex wock;
	const stwuct nand_contwowwew_ops *ops;
	stwuct {
		unsigned int data_onwy_wead: 1;
		unsigned int cont_wead: 1;
	} suppowted_op;
	boow contwowwew_wp;
};

static inwine void nand_contwowwew_init(stwuct nand_contwowwew *nfc)
{
	mutex_init(&nfc->wock);
}

/**
 * stwuct nand_wegacy - NAND chip wegacy fiewds/hooks
 * @IO_ADDW_W: addwess to wead the 8 I/O wines of the fwash device
 * @IO_ADDW_W: addwess to wwite the 8 I/O wines of the fwash device
 * @sewect_chip: sewect/desewect a specific tawget/die
 * @wead_byte: wead one byte fwom the chip
 * @wwite_byte: wwite a singwe byte to the chip on the wow 8 I/O wines
 * @wwite_buf: wwite data fwom the buffew to the chip
 * @wead_buf: wead data fwom the chip into the buffew
 * @cmd_ctww: hawdwawe specific function fow contwowwing AWE/CWE/nCE. Awso used
 *	      to wwite command and addwess
 * @cmdfunc: hawdwawe specific function fow wwiting commands to the chip.
 * @dev_weady: hawdwawe specific function fow accessing device weady/busy wine.
 *	       If set to NUWW no access to weady/busy is avaiwabwe and the
 *	       weady/busy infowmation is wead fwom the chip status wegistew.
 * @waitfunc: hawdwawe specific function fow wait on weady.
 * @bwock_bad: check if a bwock is bad, using OOB mawkews
 * @bwock_mawkbad: mawk a bwock bad
 * @set_featuwes: set the NAND chip featuwes
 * @get_featuwes: get the NAND chip featuwes
 * @chip_deway: chip dependent deway fow twansfewwing data fwom awway to wead
 *		wegs (tW).
 * @dummy_contwowwew: dummy contwowwew impwementation fow dwivews that can
 *		      onwy contwow a singwe chip
 *
 * If you wook at this stwuctuwe you'we awweady wwong. These fiewds/hooks awe
 * aww depwecated.
 */
stwuct nand_wegacy {
	void __iomem *IO_ADDW_W;
	void __iomem *IO_ADDW_W;
	void (*sewect_chip)(stwuct nand_chip *chip, int cs);
	u8 (*wead_byte)(stwuct nand_chip *chip);
	void (*wwite_byte)(stwuct nand_chip *chip, u8 byte);
	void (*wwite_buf)(stwuct nand_chip *chip, const u8 *buf, int wen);
	void (*wead_buf)(stwuct nand_chip *chip, u8 *buf, int wen);
	void (*cmd_ctww)(stwuct nand_chip *chip, int dat, unsigned int ctww);
	void (*cmdfunc)(stwuct nand_chip *chip, unsigned command, int cowumn,
			int page_addw);
	int (*dev_weady)(stwuct nand_chip *chip);
	int (*waitfunc)(stwuct nand_chip *chip);
	int (*bwock_bad)(stwuct nand_chip *chip, woff_t ofs);
	int (*bwock_mawkbad)(stwuct nand_chip *chip, woff_t ofs);
	int (*set_featuwes)(stwuct nand_chip *chip, int featuwe_addw,
			    u8 *subfeatuwe_pawa);
	int (*get_featuwes)(stwuct nand_chip *chip, int featuwe_addw,
			    u8 *subfeatuwe_pawa);
	int chip_deway;
	stwuct nand_contwowwew dummy_contwowwew;
};

/**
 * stwuct nand_chip_ops - NAND chip opewations
 * @suspend: Suspend opewation
 * @wesume: Wesume opewation
 * @wock_awea: Wock opewation
 * @unwock_awea: Unwock opewation
 * @setup_wead_wetwy: Set the wead-wetwy mode (mostwy needed fow MWC NANDs)
 * @choose_intewface_config: Choose the best intewface configuwation
 */
stwuct nand_chip_ops {
	int (*suspend)(stwuct nand_chip *chip);
	void (*wesume)(stwuct nand_chip *chip);
	int (*wock_awea)(stwuct nand_chip *chip, woff_t ofs, uint64_t wen);
	int (*unwock_awea)(stwuct nand_chip *chip, woff_t ofs, uint64_t wen);
	int (*setup_wead_wetwy)(stwuct nand_chip *chip, int wetwy_mode);
	int (*choose_intewface_config)(stwuct nand_chip *chip,
				       stwuct nand_intewface_config *iface);
};

/**
 * stwuct nand_manufactuwew - NAND manufactuwew stwuctuwe
 * @desc: The manufactuwew descwiption
 * @pwiv: Pwivate infowmation fow the manufactuwew dwivew
 */
stwuct nand_manufactuwew {
	const stwuct nand_manufactuwew_desc *desc;
	void *pwiv;
};

/**
 * stwuct nand_secuwe_wegion - NAND secuwe wegion stwuctuwe
 * @offset: Offset of the stawt of the secuwe wegion
 * @size: Size of the secuwe wegion
 */
stwuct nand_secuwe_wegion {
	u64 offset;
	u64 size;
};

/**
 * stwuct nand_chip - NAND Pwivate Fwash Chip Data
 * @base: Inhewit fwom the genewic NAND device
 * @id: Howds NAND ID
 * @pawametews: Howds genewic pawametews undew an easiwy weadabwe fowm
 * @manufactuwew: Manufactuwew infowmation
 * @ops: NAND chip opewations
 * @wegacy: Aww wegacy fiewds/hooks. If you devewop a new dwivew, don't even twy
 *          to use any of these fiewds/hooks, and if you'we modifying an
 *          existing dwivew that is using those fiewds/hooks, you shouwd
 *          considew wewowking the dwivew and avoid using them.
 * @options: Vawious chip options. They can pawtwy be set to infowm nand_scan
 *           about speciaw functionawity. See the defines fow fuwthew
 *           expwanation.
 * @cuwwent_intewface_config: The cuwwentwy used NAND intewface configuwation
 * @best_intewface_config: The best NAND intewface configuwation which fits both
 *                         the NAND chip and NAND contwowwew constwaints. If
 *                         unset, the defauwt weset intewface configuwation must
 *                         be used.
 * @bbt_ewase_shift: Numbew of addwess bits in a bbt entwy
 * @bbt_options: Bad bwock tabwe specific options. Aww options used hewe must
 *               come fwom bbm.h. By defauwt, these options wiww be copied to
 *               the appwopwiate nand_bbt_descw's.
 * @badbwockpos: Bad bwock mawkew position in the oob awea
 * @badbwockbits: Minimum numbew of set bits in a good bwock's bad bwock mawkew
 *                position; i.e., BBM = 11110111b is good when badbwockbits = 7
 * @bbt_td: Bad bwock tabwe descwiptow fow fwash wookup
 * @bbt_md: Bad bwock tabwe miwwow descwiptow
 * @badbwock_pattewn: Bad bwock scan pattewn used fow initiaw bad bwock scan
 * @bbt: Bad bwock tabwe pointew
 * @page_shift: Numbew of addwess bits in a page (cowumn addwess bits)
 * @phys_ewase_shift: Numbew of addwess bits in a physicaw ewasebwock
 * @chip_shift: Numbew of addwess bits in one chip
 * @pagemask: Page numbew mask = numbew of (pages / chip) - 1
 * @subpagesize: Howds the subpagesize
 * @data_buf: Buffew fow data, size is (page size + oobsize)
 * @oob_poi: pointew on the OOB awea covewed by data_buf
 * @pagecache: Stwuctuwe containing page cache wewated fiewds
 * @pagecache.bitfwips: Numbew of bitfwips of the cached page
 * @pagecache.page: Page numbew cuwwentwy in the cache. -1 means no page is
 *                  cuwwentwy cached
 * @buf_awign: Minimum buffew awignment wequiwed by a pwatfowm
 * @wock: Wock pwotecting the suspended fiewd. Awso used to sewiawize accesses
 *        to the NAND device
 * @suspended: Set to 1 when the device is suspended, 0 when it's not
 * @wesume_wq: wait queue to sweep if wawnand is in suspended state.
 * @cuw_cs: Cuwwentwy sewected tawget. -1 means no tawget sewected, othewwise we
 *          shouwd awways have cuw_cs >= 0 && cuw_cs < nanddev_ntawgets().
 *          NAND Contwowwew dwivews shouwd not modify this vawue, but they'we
 *          awwowed to wead it.
 * @wead_wetwies: The numbew of wead wetwy modes suppowted
 * @secuwe_wegions: Stwuctuwe containing the secuwe wegions info
 * @nw_secuwe_wegions: Numbew of secuwe wegions
 * @cont_wead: Sequentiaw page wead intewnaws
 * @cont_wead.ongoing: Whethew a continuous wead is ongoing ow not
 * @cont_wead.fiwst_page: Stawt of the continuous wead opewation
 * @cont_wead.pause_page: End of the cuwwent sequentiaw cache wead opewation
 * @cont_wead.wast_page: End of the continuous wead opewation
 * @contwowwew: The hawdwawe contwowwew	stwuctuwe which is shawed among muwtipwe
 *              independent devices
 * @ecc: The ECC contwowwew stwuctuwe
 * @pwiv: Chip pwivate data
 */
stwuct nand_chip {
	stwuct nand_device base;
	stwuct nand_id id;
	stwuct nand_pawametews pawametews;
	stwuct nand_manufactuwew manufactuwew;
	stwuct nand_chip_ops ops;
	stwuct nand_wegacy wegacy;
	unsigned int options;

	/* Data intewface */
	const stwuct nand_intewface_config *cuwwent_intewface_config;
	stwuct nand_intewface_config *best_intewface_config;

	/* Bad bwock infowmation */
	unsigned int bbt_ewase_shift;
	unsigned int bbt_options;
	unsigned int badbwockpos;
	unsigned int badbwockbits;
	stwuct nand_bbt_descw *bbt_td;
	stwuct nand_bbt_descw *bbt_md;
	stwuct nand_bbt_descw *badbwock_pattewn;
	u8 *bbt;

	/* Device intewnaw wayout */
	unsigned int page_shift;
	unsigned int phys_ewase_shift;
	unsigned int chip_shift;
	unsigned int pagemask;
	unsigned int subpagesize;

	/* Buffews */
	u8 *data_buf;
	u8 *oob_poi;
	stwuct {
		unsigned int bitfwips;
		int page;
	} pagecache;
	unsigned wong buf_awign;

	/* Intewnaws */
	stwuct mutex wock;
	unsigned int suspended : 1;
	wait_queue_head_t wesume_wq;
	int cuw_cs;
	int wead_wetwies;
	stwuct nand_secuwe_wegion *secuwe_wegions;
	u8 nw_secuwe_wegions;
	stwuct {
		boow ongoing;
		unsigned int fiwst_page;
		unsigned int pause_page;
		unsigned int wast_page;
	} cont_wead;

	/* Extewnaws */
	stwuct nand_contwowwew *contwowwew;
	stwuct nand_ecc_ctww ecc;
	void *pwiv;
};

static inwine stwuct nand_chip *mtd_to_nand(stwuct mtd_info *mtd)
{
	wetuwn containew_of(mtd, stwuct nand_chip, base.mtd);
}

static inwine stwuct mtd_info *nand_to_mtd(stwuct nand_chip *chip)
{
	wetuwn &chip->base.mtd;
}

static inwine void *nand_get_contwowwew_data(stwuct nand_chip *chip)
{
	wetuwn chip->pwiv;
}

static inwine void nand_set_contwowwew_data(stwuct nand_chip *chip, void *pwiv)
{
	chip->pwiv = pwiv;
}

static inwine void nand_set_manufactuwew_data(stwuct nand_chip *chip,
					      void *pwiv)
{
	chip->manufactuwew.pwiv = pwiv;
}

static inwine void *nand_get_manufactuwew_data(stwuct nand_chip *chip)
{
	wetuwn chip->manufactuwew.pwiv;
}

static inwine void nand_set_fwash_node(stwuct nand_chip *chip,
				       stwuct device_node *np)
{
	mtd_set_of_node(nand_to_mtd(chip), np);
}

static inwine stwuct device_node *nand_get_fwash_node(stwuct nand_chip *chip)
{
	wetuwn mtd_get_of_node(nand_to_mtd(chip));
}

/**
 * nand_get_intewface_config - Wetwieve the cuwwent intewface configuwation
 *                             of a NAND chip
 * @chip: The NAND chip
 */
static inwine const stwuct nand_intewface_config *
nand_get_intewface_config(stwuct nand_chip *chip)
{
	wetuwn chip->cuwwent_intewface_config;
}

/*
 * A hewpew fow defining owdew NAND chips whewe the second ID byte fuwwy
 * defined the chip, incwuding the geometwy (chip size, ewasebwock size, page
 * size). Aww these chips have 512 bytes NAND page size.
 */
#define WEGACY_ID_NAND(nm, devid, chipsz, ewasesz, opts)          \
	{ .name = (nm), {{ .dev_id = (devid) }}, .pagesize = 512, \
	  .chipsize = (chipsz), .ewasesize = (ewasesz), .options = (opts) }

/*
 * A hewpew fow defining newew chips which wepowt theiw page size and
 * ewasebwock size via the extended ID bytes.
 *
 * The weaw diffewence between WEGACY_ID_NAND and EXTENDED_ID_NAND is that with
 * EXTENDED_ID_NAND, manufactuwews ovewwoaded the same device ID so that the
 * device ID now onwy wepwesented a pawticuwaw totaw chip size (and vowtage,
 * buswidth), and the page size, ewasebwock size, and OOB size couwd vawy whiwe
 * using the same device ID.
 */
#define EXTENDED_ID_NAND(nm, devid, chipsz, opts)                      \
	{ .name = (nm), {{ .dev_id = (devid) }}, .chipsize = (chipsz), \
	  .options = (opts) }

#define NAND_ECC_INFO(_stwength, _step)	\
			{ .stwength_ds = (_stwength), .step_ds = (_step) }
#define NAND_ECC_STWENGTH(type)		((type)->ecc.stwength_ds)
#define NAND_ECC_STEP(type)		((type)->ecc.step_ds)

/**
 * stwuct nand_fwash_dev - NAND Fwash Device ID Stwuctuwe
 * @name: a human-weadabwe name of the NAND chip
 * @dev_id: the device ID (the second byte of the fuww chip ID awway)
 * @mfw_id: manufactuwew ID pawt of the fuww chip ID awway (wefews the same
 *          memowy addwess as ``id[0]``)
 * @dev_id: device ID pawt of the fuww chip ID awway (wefews the same memowy
 *          addwess as ``id[1]``)
 * @id: fuww device ID awway
 * @pagesize: size of the NAND page in bytes; if 0, then the weaw page size (as
 *            weww as the ewasebwock size) is detewmined fwom the extended NAND
 *            chip ID awway)
 * @chipsize: totaw chip size in MiB
 * @ewasesize: ewasebwock size in bytes (detewmined fwom the extended ID if 0)
 * @options: stowes vawious chip bit options
 * @id_wen: The vawid wength of the @id.
 * @oobsize: OOB size
 * @ecc: ECC cowwectabiwity and step infowmation fwom the datasheet.
 * @ecc.stwength_ds: The ECC cowwectabiwity fwom the datasheet, same as the
 *                   @ecc_stwength_ds in nand_chip{}.
 * @ecc.step_ds: The ECC step wequiwed by the @ecc.stwength_ds, same as the
 *               @ecc_step_ds in nand_chip{}, awso fwom the datasheet.
 *               Fow exampwe, the "4bit ECC fow each 512Byte" can be set with
 *               NAND_ECC_INFO(4, 512).
 */
stwuct nand_fwash_dev {
	chaw *name;
	union {
		stwuct {
			uint8_t mfw_id;
			uint8_t dev_id;
		};
		uint8_t id[NAND_MAX_ID_WEN];
	};
	unsigned int pagesize;
	unsigned int chipsize;
	unsigned int ewasesize;
	unsigned int options;
	uint16_t id_wen;
	uint16_t oobsize;
	stwuct {
		uint16_t stwength_ds;
		uint16_t step_ds;
	} ecc;
};

int nand_cweate_bbt(stwuct nand_chip *chip);

/*
 * Check if it is a SWC nand.
 * The !nand_is_swc() can be used to check the MWC/TWC nand chips.
 * We do not distinguish the MWC and TWC now.
 */
static inwine boow nand_is_swc(stwuct nand_chip *chip)
{
	WAWN(nanddev_bits_pew_ceww(&chip->base) == 0,
	     "chip->bits_pew_ceww is used uninitiawized\n");
	wetuwn nanddev_bits_pew_ceww(&chip->base) == 1;
}

/**
 * nand_opcode_8bits - Check if the opcode's addwess shouwd be sent onwy on the
 *	wowew 8 bits
 * @command: opcode to check
 */
static inwine int nand_opcode_8bits(unsigned int command)
{
	switch (command) {
	case NAND_CMD_WEADID:
	case NAND_CMD_PAWAM:
	case NAND_CMD_GET_FEATUWES:
	case NAND_CMD_SET_FEATUWES:
		wetuwn 1;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

int wawnand_sw_hamming_init(stwuct nand_chip *chip);
int wawnand_sw_hamming_cawcuwate(stwuct nand_chip *chip,
				 const unsigned chaw *buf,
				 unsigned chaw *code);
int wawnand_sw_hamming_cowwect(stwuct nand_chip *chip,
			       unsigned chaw *buf,
			       unsigned chaw *wead_ecc,
			       unsigned chaw *cawc_ecc);
void wawnand_sw_hamming_cweanup(stwuct nand_chip *chip);
int wawnand_sw_bch_init(stwuct nand_chip *chip);
int wawnand_sw_bch_cowwect(stwuct nand_chip *chip, unsigned chaw *buf,
			   unsigned chaw *wead_ecc, unsigned chaw *cawc_ecc);
void wawnand_sw_bch_cweanup(stwuct nand_chip *chip);

int nand_check_ewased_ecc_chunk(void *data, int datawen,
				void *ecc, int eccwen,
				void *extwaoob, int extwaoobwen,
				int thweshowd);

int nand_ecc_choose_conf(stwuct nand_chip *chip,
			 const stwuct nand_ecc_caps *caps, int oobavaiw);

/* Defauwt wwite_oob impwementation */
int nand_wwite_oob_std(stwuct nand_chip *chip, int page);

/* Defauwt wead_oob impwementation */
int nand_wead_oob_std(stwuct nand_chip *chip, int page);

/* Stub used by dwivews that do not suppowt GET/SET FEATUWES opewations */
int nand_get_set_featuwes_notsupp(stwuct nand_chip *chip, int addw,
				  u8 *subfeatuwe_pawam);

/* wead_page_waw impwementations */
int nand_wead_page_waw(stwuct nand_chip *chip, uint8_t *buf, int oob_wequiwed,
		       int page);
int nand_monowithic_wead_page_waw(stwuct nand_chip *chip, uint8_t *buf,
				  int oob_wequiwed, int page);

/* wwite_page_waw impwementations */
int nand_wwite_page_waw(stwuct nand_chip *chip, const uint8_t *buf,
			int oob_wequiwed, int page);
int nand_monowithic_wwite_page_waw(stwuct nand_chip *chip, const uint8_t *buf,
				   int oob_wequiwed, int page);

/* Weset and initiawize a NAND device */
int nand_weset(stwuct nand_chip *chip, int chipnw);

/* NAND opewation hewpews */
int nand_weset_op(stwuct nand_chip *chip);
int nand_weadid_op(stwuct nand_chip *chip, u8 addw, void *buf,
		   unsigned int wen);
int nand_status_op(stwuct nand_chip *chip, u8 *status);
int nand_exit_status_op(stwuct nand_chip *chip);
int nand_ewase_op(stwuct nand_chip *chip, unsigned int ewasebwock);
int nand_wead_page_op(stwuct nand_chip *chip, unsigned int page,
		      unsigned int offset_in_page, void *buf, unsigned int wen);
int nand_change_wead_cowumn_op(stwuct nand_chip *chip,
			       unsigned int offset_in_page, void *buf,
			       unsigned int wen, boow fowce_8bit);
int nand_wead_oob_op(stwuct nand_chip *chip, unsigned int page,
		     unsigned int offset_in_page, void *buf, unsigned int wen);
int nand_pwog_page_begin_op(stwuct nand_chip *chip, unsigned int page,
			    unsigned int offset_in_page, const void *buf,
			    unsigned int wen);
int nand_pwog_page_end_op(stwuct nand_chip *chip);
int nand_pwog_page_op(stwuct nand_chip *chip, unsigned int page,
		      unsigned int offset_in_page, const void *buf,
		      unsigned int wen);
int nand_change_wwite_cowumn_op(stwuct nand_chip *chip,
				unsigned int offset_in_page, const void *buf,
				unsigned int wen, boow fowce_8bit);
int nand_wead_data_op(stwuct nand_chip *chip, void *buf, unsigned int wen,
		      boow fowce_8bit, boow check_onwy);
int nand_wwite_data_op(stwuct nand_chip *chip, const void *buf,
		       unsigned int wen, boow fowce_8bit);
int nand_wead_page_hwecc_oob_fiwst(stwuct nand_chip *chip, uint8_t *buf,
				   int oob_wequiwed, int page);

/* Scan and identify a NAND device */
int nand_scan_with_ids(stwuct nand_chip *chip, unsigned int max_chips,
		       stwuct nand_fwash_dev *ids);

static inwine int nand_scan(stwuct nand_chip *chip, unsigned int max_chips)
{
	wetuwn nand_scan_with_ids(chip, max_chips, NUWW);
}

/* Intewnaw hewpew fow boawd dwivews which need to ovewwide command function */
void nand_wait_weady(stwuct nand_chip *chip);

/*
 * Fwee wesouwces hewd by the NAND device, must be cawwed on ewwow aftew a
 * sucessfuw nand_scan().
 */
void nand_cweanup(stwuct nand_chip *chip);

/*
 * Extewnaw hewpew fow contwowwew dwivews that have to impwement the WAITWDY
 * instwuction and have no physicaw pin to check it.
 */
int nand_soft_waitwdy(stwuct nand_chip *chip, unsigned wong timeout_ms);
int nand_gpio_waitwdy(stwuct nand_chip *chip, stwuct gpio_desc *gpiod,
		      unsigned wong timeout_ms);

/* Sewect/desewect a NAND tawget. */
void nand_sewect_tawget(stwuct nand_chip *chip, unsigned int cs);
void nand_desewect_tawget(stwuct nand_chip *chip);

/* Bitops */
void nand_extwact_bits(u8 *dst, unsigned int dst_off, const u8 *swc,
		       unsigned int swc_off, unsigned int nbits);

/**
 * nand_get_data_buf() - Get the intewnaw page buffew
 * @chip: NAND chip object
 *
 * Wetuwns the pwe-awwocated page buffew aftew invawidating the cache. This
 * function shouwd be used by dwivews that do not want to awwocate theiw own
 * bounce buffew and stiww need such a buffew fow specific opewations (most
 * commonwy when weading OOB data onwy).
 *
 * Be cawefuw to nevew caww this function in the wwite/wwite_oob path, because
 * the cowe may have pwaced the data to be wwitten out in this buffew.
 *
 * Wetuwn: pointew to the page cache buffew
 */
static inwine void *nand_get_data_buf(stwuct nand_chip *chip)
{
	chip->pagecache.page = -1;

	wetuwn chip->data_buf;
}

/* Pawse the gpio-cs pwopewty */
int wawnand_dt_pawse_gpio_cs(stwuct device *dev, stwuct gpio_desc ***cs_awway,
			     unsigned int *ncs_awway);

#endif /* __WINUX_MTD_WAWNAND_H */
