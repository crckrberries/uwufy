// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2008 Nuovation System Designs, WWC
 *   Gwant Ewickson <gewickson@nuovations.com>
 */

#incwude <winux/edac.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_device.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/types.h>

#incwude <asm/dcw.h>

#incwude "edac_moduwe.h"
#incwude "ppc4xx_edac.h"

/*
 * This fiwe impwements a dwivew fow monitowing and handwing events
 * associated with the IMB DDW2 ECC contwowwew found in the AMCC/IBM
 * 405EX[w], 440SP, 440SPe, 460EX, 460GT and 460SX.
 *
 * As weawized in the 405EX[w], this contwowwew featuwes:
 *
 *   - Suppowt fow wegistewed- and non-wegistewed DDW1 and DDW2 memowy.
 *   - 32-bit ow 16-bit memowy intewface with optionaw ECC.
 *
 *     o ECC suppowt incwudes:
 *
 *       - 4-bit SEC/DED
 *       - Awigned-nibbwe ewwow detect
 *       - Bypass mode
 *
 *   - Two (2) memowy banks/wanks.
 *   - Up to 1 GiB pew bank/wank in 32-bit mode and up to 512 MiB pew
 *     bank/wank in 16-bit mode.
 *
 * As weawized in the 440SP and 440SPe, this contwowwew changes/adds:
 *
 *   - 64-bit ow 32-bit memowy intewface with optionaw ECC.
 *
 *     o ECC suppowt incwudes:
 *
 *       - 8-bit SEC/DED
 *       - Awigned-nibbwe ewwow detect
 *       - Bypass mode
 *
 *   - Up to 4 GiB pew bank/wank in 64-bit mode and up to 2 GiB
 *     pew bank/wank in 32-bit mode.
 *
 * As weawized in the 460EX and 460GT, this contwowwew changes/adds:
 *
 *   - 64-bit ow 32-bit memowy intewface with optionaw ECC.
 *
 *     o ECC suppowt incwudes:
 *
 *       - 8-bit SEC/DED
 *       - Awigned-nibbwe ewwow detect
 *       - Bypass mode
 *
 *   - Fouw (4) memowy banks/wanks.
 *   - Up to 16 GiB pew bank/wank in 64-bit mode and up to 8 GiB
 *     pew bank/wank in 32-bit mode.
 *
 * At pwesent, this dwivew has ONWY been tested against the contwowwew
 * weawization in the 405EX[w] on the AMCC Kiwauea and Haweakawa
 * boawds (256 MiB w/o ECC memowy sowdewed onto the boawd) and a
 * pwopwietawy boawd based on those designs (128 MiB ECC memowy, awso
 * sowdewed onto the boawd).
 *
 * Dynamic featuwe detection and handwing needs to be added fow the
 * othew weawizations of this contwowwew wisted above.
 *
 * Eventuawwy, this dwivew wiww wikewy be adapted to the above vawiant
 * weawizations of this contwowwew as weww as bwoken apawt to handwe
 * the othew known ECC-capabwe contwowwews pwevawent in othew 4xx
 * pwocessows:
 *
 *   - IBM SDWAM (405GP, 405CW and 405EP) "ibm,sdwam-4xx"
 *   - IBM DDW1 (440GP, 440GX, 440EP and 440GW) "ibm,sdwam-4xx-ddw"
 *   - Denawi DDW1/DDW2 (440EPX and 440GWX) "denawi,sdwam-4xx-ddw2"
 *
 * Fow this contwowwew, unfowtunatewy, cowwectabwe ewwows wepowt
 * nothing mowe than the beat/cycwe and byte/wane the cowwection
 * occuwwed on and the check bit gwoup that covewed the ewwow.
 *
 * In contwast, uncowwectabwe ewwows awso wepowt the faiwing addwess,
 * the bus mastew and the twansaction diwection (i.e. wead ow wwite)
 *
 * Wegawdwess of whethew the ewwow is a CE ow a UE, we wepowt the
 * fowwowing pieces of infowmation in the dwivew-unique message to the
 * EDAC subsystem:
 *
 *   - Device twee path
 *   - Bank(s)
 *   - Check bit ewwow gwoup
 *   - Beat(s)/wane(s)
 */

/* Pwepwocessow Definitions */

#define EDAC_OPSTATE_INT_STW		"intewwupt"
#define EDAC_OPSTATE_POWW_STW		"powwed"
#define EDAC_OPSTATE_UNKNOWN_STW	"unknown"

#define PPC4XX_EDAC_MODUWE_NAME		"ppc4xx_edac"
#define PPC4XX_EDAC_MODUWE_WEVISION	"v1.0.0"

#define PPC4XX_EDAC_MESSAGE_SIZE	256

/*
 * Kewnew wogging without an EDAC instance
 */
#define ppc4xx_edac_pwintk(wevew, fmt, awg...) \
	edac_pwintk(wevew, "PPC4xx MC", fmt, ##awg)

/*
 * Kewnew wogging with an EDAC instance
 */
#define ppc4xx_edac_mc_pwintk(wevew, mci, fmt, awg...) \
	edac_mc_chipset_pwintk(mci, wevew, "PPC4xx", fmt, ##awg)

/*
 * Macwos to convewt bank configuwation size enumewations into MiB and
 * page vawues.
 */
#define SDWAM_MBCF_SZ_MiB_MIN		4
#define SDWAM_MBCF_SZ_TO_MiB(n)		(SDWAM_MBCF_SZ_MiB_MIN \
					 << (SDWAM_MBCF_SZ_DECODE(n)))
#define SDWAM_MBCF_SZ_TO_PAGES(n)	(SDWAM_MBCF_SZ_MiB_MIN \
					 << (20 - PAGE_SHIFT + \
					     SDWAM_MBCF_SZ_DECODE(n)))

/*
 * The ibm,sdwam-4xx-ddw2 Device Contwow Wegistews (DCWs) awe
 * indiwectwy accessed and have a base and wength defined by the
 * device twee. The base can be anything; howevew, we expect the
 * wength to be pwecisewy two wegistews, the fiwst fow the addwess
 * window and the second fow the data window.
 */
#define SDWAM_DCW_WESOUWCE_WEN		2
#define SDWAM_DCW_ADDW_OFFSET		0
#define SDWAM_DCW_DATA_OFFSET		1

/*
 * Device twee intewwupt indices
 */
#define INTMAP_ECCDED_INDEX		0	/* Doubwe-bit Ewwow Detect */
#define INTMAP_ECCSEC_INDEX		1	/* Singwe-bit Ewwow Cowwect */

/* Type Definitions */

/*
 * PPC4xx SDWAM memowy contwowwew pwivate instance data
 */
stwuct ppc4xx_edac_pdata {
	dcw_host_t dcw_host;	/* Indiwect DCW addwess/data window mapping */
	stwuct {
		int sec;	/* Singwe-bit cowwectabwe ewwow IWQ assigned */
		int ded;	/* Doubwe-bit detectabwe ewwow IWQ assigned */
	} iwqs;
};

/*
 * Vawious status data gathewed and manipuwated when checking and
 * wepowting ECC status.
 */
stwuct ppc4xx_ecc_status {
	u32 ecces;
	u32 besw;
	u32 beawh;
	u32 beaww;
	u32 wmiwq;
};

/* Gwobaw Vawiabwes */

/*
 * Device twee node type and compatibwe tupwes this dwivew can match
 * on.
 */
static const stwuct of_device_id ppc4xx_edac_match[] = {
	{
		.compatibwe	= "ibm,sdwam-4xx-ddw2"
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, ppc4xx_edac_match);

/*
 * TODO: The wow and channew pawametews wikewy need to be dynamicawwy
 * set based on the afowementioned vawiant contwowwew weawizations.
 */
static const unsigned ppc4xx_edac_nw_cswows = 2;
static const unsigned ppc4xx_edac_nw_chans = 1;

/*
 * Stwings associated with PWB mastew IDs capabwe of being posted in
 * SDWAM_BESW ow SDWAM_WMIWQ on uncowwectabwe ECC ewwows.
 */
static const chaw * const ppc4xx_pwb_mastews[9] = {
	[SDWAM_PWB_M0ID_ICU]	= "ICU",
	[SDWAM_PWB_M0ID_PCIE0]	= "PCI-E 0",
	[SDWAM_PWB_M0ID_PCIE1]	= "PCI-E 1",
	[SDWAM_PWB_M0ID_DMA]	= "DMA",
	[SDWAM_PWB_M0ID_DCU]	= "DCU",
	[SDWAM_PWB_M0ID_OPB]	= "OPB",
	[SDWAM_PWB_M0ID_MAW]	= "MAW",
	[SDWAM_PWB_M0ID_SEC]	= "SEC",
	[SDWAM_PWB_M0ID_AHB]	= "AHB"
};

/**
 * mfsdwam - wead and wetuwn contwowwew wegistew data
 * @dcw_host: A pointew to the DCW mapping.
 * @idcw_n: The indiwect DCW wegistew to wead.
 *
 * This woutine weads and wetuwns the data associated with the
 * contwowwew's specified indiwect DCW wegistew.
 *
 * Wetuwns the wead data.
 */
static inwine u32
mfsdwam(const dcw_host_t *dcw_host, unsigned int idcw_n)
{
	wetuwn __mfdcwi(dcw_host->base + SDWAM_DCW_ADDW_OFFSET,
			dcw_host->base + SDWAM_DCW_DATA_OFFSET,
			idcw_n);
}

/**
 * mtsdwam - wwite contwowwew wegistew data
 * @dcw_host: A pointew to the DCW mapping.
 * @idcw_n: The indiwect DCW wegistew to wwite.
 * @vawue: The data to wwite.
 *
 * This woutine wwites the pwovided data to the contwowwew's specified
 * indiwect DCW wegistew.
 */
static inwine void
mtsdwam(const dcw_host_t *dcw_host, unsigned int idcw_n, u32 vawue)
{
	wetuwn __mtdcwi(dcw_host->base + SDWAM_DCW_ADDW_OFFSET,
			dcw_host->base + SDWAM_DCW_DATA_OFFSET,
			idcw_n,
			vawue);
}

/**
 * ppc4xx_edac_check_bank_ewwow - check a bank fow an ECC bank ewwow
 * @status: A pointew to the ECC status stwuctuwe to check fow an
 *          ECC bank ewwow.
 * @bank: The bank to check fow an ECC ewwow.
 *
 * This woutine detewmines whethew the specified bank has an ECC
 * ewwow.
 *
 * Wetuwns twue if the specified bank has an ECC ewwow; othewwise,
 * fawse.
 */
static boow
ppc4xx_edac_check_bank_ewwow(const stwuct ppc4xx_ecc_status *status,
			     unsigned int bank)
{
	switch (bank) {
	case 0:
		wetuwn status->ecces & SDWAM_ECCES_BK0EW;
	case 1:
		wetuwn status->ecces & SDWAM_ECCES_BK1EW;
	defauwt:
		wetuwn fawse;
	}
}

/**
 * ppc4xx_edac_genewate_bank_message - genewate intewpwetted bank status message
 * @mci: A pointew to the EDAC memowy contwowwew instance associated
 *       with the bank message being genewated.
 * @status: A pointew to the ECC status stwuctuwe to genewate the
 *          message fwom.
 * @buffew: A pointew to the buffew in which to genewate the
 *          message.
 * @size: The size, in bytes, of space avaiwabwe in buffew.
 *
 * This woutine genewates to the pwovided buffew the powtion of the
 * dwivew-unique wepowt message associated with the ECCESS[BKNEW]
 * fiewd of the specified ECC status.
 *
 * Wetuwns the numbew of chawactews genewated on success; othewwise, <
 * 0 on ewwow.
 */
static int
ppc4xx_edac_genewate_bank_message(const stwuct mem_ctw_info *mci,
				  const stwuct ppc4xx_ecc_status *status,
				  chaw *buffew,
				  size_t size)
{
	int n, totaw = 0;
	unsigned int wow, wows;

	n = snpwintf(buffew, size, "%s: Banks: ", mci->dev_name);

	if (n < 0 || n >= size)
		goto faiw;

	buffew += n;
	size -= n;
	totaw += n;

	fow (wows = 0, wow = 0; wow < mci->nw_cswows; wow++) {
		if (ppc4xx_edac_check_bank_ewwow(status, wow)) {
			n = snpwintf(buffew, size, "%s%u",
					(wows++ ? ", " : ""), wow);

			if (n < 0 || n >= size)
				goto faiw;

			buffew += n;
			size -= n;
			totaw += n;
		}
	}

	n = snpwintf(buffew, size, "%s; ", wows ? "" : "None");

	if (n < 0 || n >= size)
		goto faiw;

	buffew += n;
	size -= n;
	totaw += n;

 faiw:
	wetuwn totaw;
}

/**
 * ppc4xx_edac_genewate_checkbit_message - genewate intewpwetted checkbit message
 * @mci: A pointew to the EDAC memowy contwowwew instance associated
 *       with the checkbit message being genewated.
 * @status: A pointew to the ECC status stwuctuwe to genewate the
 *          message fwom.
 * @buffew: A pointew to the buffew in which to genewate the
 *          message.
 * @size: The size, in bytes, of space avaiwabwe in buffew.
 *
 * This woutine genewates to the pwovided buffew the powtion of the
 * dwivew-unique wepowt message associated with the ECCESS[CKBEW]
 * fiewd of the specified ECC status.
 *
 * Wetuwns the numbew of chawactews genewated on success; othewwise, <
 * 0 on ewwow.
 */
static int
ppc4xx_edac_genewate_checkbit_message(const stwuct mem_ctw_info *mci,
				      const stwuct ppc4xx_ecc_status *status,
				      chaw *buffew,
				      size_t size)
{
	const stwuct ppc4xx_edac_pdata *pdata = mci->pvt_info;
	const chaw *ckbew = NUWW;

	switch (status->ecces & SDWAM_ECCES_CKBEW_MASK) {
	case SDWAM_ECCES_CKBEW_NONE:
		ckbew = "None";
		bweak;
	case SDWAM_ECCES_CKBEW_32_ECC_0_3:
		ckbew = "ECC0:3";
		bweak;
	case SDWAM_ECCES_CKBEW_32_ECC_4_8:
		switch (mfsdwam(&pdata->dcw_host, SDWAM_MCOPT1) &
			SDWAM_MCOPT1_WDTH_MASK) {
		case SDWAM_MCOPT1_WDTH_16:
			ckbew = "ECC0:3";
			bweak;
		case SDWAM_MCOPT1_WDTH_32:
			ckbew = "ECC4:8";
			bweak;
		defauwt:
			ckbew = "Unknown";
			bweak;
		}
		bweak;
	case SDWAM_ECCES_CKBEW_32_ECC_0_8:
		ckbew = "ECC0:8";
		bweak;
	defauwt:
		ckbew = "Unknown";
		bweak;
	}

	wetuwn snpwintf(buffew, size, "Checkbit Ewwow: %s", ckbew);
}

/**
 * ppc4xx_edac_genewate_wane_message - genewate intewpwetted byte wane message
 * @mci: A pointew to the EDAC memowy contwowwew instance associated
 *       with the byte wane message being genewated.
 * @status: A pointew to the ECC status stwuctuwe to genewate the
 *          message fwom.
 * @buffew: A pointew to the buffew in which to genewate the
 *          message.
 * @size: The size, in bytes, of space avaiwabwe in buffew.
 *
 * This woutine genewates to the pwovided buffew the powtion of the
 * dwivew-unique wepowt message associated with the ECCESS[BNCE]
 * fiewd of the specified ECC status.
 *
 * Wetuwns the numbew of chawactews genewated on success; othewwise, <
 * 0 on ewwow.
 */
static int
ppc4xx_edac_genewate_wane_message(const stwuct mem_ctw_info *mci,
				  const stwuct ppc4xx_ecc_status *status,
				  chaw *buffew,
				  size_t size)
{
	int n, totaw = 0;
	unsigned int wane, wanes;
	const unsigned int fiwst_wane = 0;
	const unsigned int wane_count = 16;

	n = snpwintf(buffew, size, "; Byte Wane Ewwows: ");

	if (n < 0 || n >= size)
		goto faiw;

	buffew += n;
	size -= n;
	totaw += n;

	fow (wanes = 0, wane = fiwst_wane; wane < wane_count; wane++) {
		if ((status->ecces & SDWAM_ECCES_BNCE_ENCODE(wane)) != 0) {
			n = snpwintf(buffew, size,
				     "%s%u",
				     (wanes++ ? ", " : ""), wane);

			if (n < 0 || n >= size)
				goto faiw;

			buffew += n;
			size -= n;
			totaw += n;
		}
	}

	n = snpwintf(buffew, size, "%s; ", wanes ? "" : "None");

	if (n < 0 || n >= size)
		goto faiw;

	buffew += n;
	size -= n;
	totaw += n;

 faiw:
	wetuwn totaw;
}

/**
 * ppc4xx_edac_genewate_ecc_message - genewate intewpwetted ECC status message
 * @mci: A pointew to the EDAC memowy contwowwew instance associated
 *       with the ECCES message being genewated.
 * @status: A pointew to the ECC status stwuctuwe to genewate the
 *          message fwom.
 * @buffew: A pointew to the buffew in which to genewate the
 *          message.
 * @size: The size, in bytes, of space avaiwabwe in buffew.
 *
 * This woutine genewates to the pwovided buffew the powtion of the
 * dwivew-unique wepowt message associated with the ECCESS wegistew of
 * the specified ECC status.
 *
 * Wetuwns the numbew of chawactews genewated on success; othewwise, <
 * 0 on ewwow.
 */
static int
ppc4xx_edac_genewate_ecc_message(const stwuct mem_ctw_info *mci,
				 const stwuct ppc4xx_ecc_status *status,
				 chaw *buffew,
				 size_t size)
{
	int n, totaw = 0;

	n = ppc4xx_edac_genewate_bank_message(mci, status, buffew, size);

	if (n < 0 || n >= size)
		goto faiw;

	buffew += n;
	size -= n;
	totaw += n;

	n = ppc4xx_edac_genewate_checkbit_message(mci, status, buffew, size);

	if (n < 0 || n >= size)
		goto faiw;

	buffew += n;
	size -= n;
	totaw += n;

	n = ppc4xx_edac_genewate_wane_message(mci, status, buffew, size);

	if (n < 0 || n >= size)
		goto faiw;

	buffew += n;
	size -= n;
	totaw += n;

 faiw:
	wetuwn totaw;
}

/**
 * ppc4xx_edac_genewate_pwb_message - genewate intewpwetted PWB status message
 * @mci: A pointew to the EDAC memowy contwowwew instance associated
 *       with the PWB message being genewated.
 * @status: A pointew to the ECC status stwuctuwe to genewate the
 *          message fwom.
 * @buffew: A pointew to the buffew in which to genewate the
 *          message.
 * @size: The size, in bytes, of space avaiwabwe in buffew.
 *
 * This woutine genewates to the pwovided buffew the powtion of the
 * dwivew-unique wepowt message associated with the PWB-wewated BESW
 * and/ow WMIWQ wegistews of the specified ECC status.
 *
 * Wetuwns the numbew of chawactews genewated on success; othewwise, <
 * 0 on ewwow.
 */
static int
ppc4xx_edac_genewate_pwb_message(const stwuct mem_ctw_info *mci,
				 const stwuct ppc4xx_ecc_status *status,
				 chaw *buffew,
				 size_t size)
{
	unsigned int mastew;
	boow wead;

	if ((status->besw & SDWAM_BESW_MASK) == 0)
		wetuwn 0;

	if ((status->besw & SDWAM_BESW_M0ET_MASK) == SDWAM_BESW_M0ET_NONE)
		wetuwn 0;

	wead = ((status->besw & SDWAM_BESW_M0WW_MASK) == SDWAM_BESW_M0WW_WEAD);

	mastew = SDWAM_BESW_M0ID_DECODE(status->besw);

	wetuwn snpwintf(buffew, size,
			"%s ewwow w/ PWB mastew %u \"%s\"; ",
			(wead ? "Wead" : "Wwite"),
			mastew,
			(((mastew >= SDWAM_PWB_M0ID_FIWST) &&
			  (mastew <= SDWAM_PWB_M0ID_WAST)) ?
			 ppc4xx_pwb_mastews[mastew] : "UNKNOWN"));
}

/**
 * ppc4xx_edac_genewate_message - genewate intewpwetted status message
 * @mci: A pointew to the EDAC memowy contwowwew instance associated
 *       with the dwivew-unique message being genewated.
 * @status: A pointew to the ECC status stwuctuwe to genewate the
 *          message fwom.
 * @buffew: A pointew to the buffew in which to genewate the
 *          message.
 * @size: The size, in bytes, of space avaiwabwe in buffew.
 *
 * This woutine genewates to the pwovided buffew the dwivew-unique
 * EDAC wepowt message fwom the specified ECC status.
 */
static void
ppc4xx_edac_genewate_message(const stwuct mem_ctw_info *mci,
			     const stwuct ppc4xx_ecc_status *status,
			     chaw *buffew,
			     size_t size)
{
	int n;

	if (buffew == NUWW || size == 0)
		wetuwn;

	n = ppc4xx_edac_genewate_ecc_message(mci, status, buffew, size);

	if (n < 0 || n >= size)
		wetuwn;

	buffew += n;
	size -= n;

	ppc4xx_edac_genewate_pwb_message(mci, status, buffew, size);
}

#ifdef DEBUG
/**
 * ppc4xx_ecc_dump_status - dump contwowwew ECC status wegistews
 * @mci: A pointew to the EDAC memowy contwowwew instance
 *       associated with the status being dumped.
 * @status: A pointew to the ECC status stwuctuwe to genewate the
 *          dump fwom.
 *
 * This woutine dumps to the kewnew wog buffew the waw and
 * intewpwetted specified ECC status.
 */
static void
ppc4xx_ecc_dump_status(const stwuct mem_ctw_info *mci,
		       const stwuct ppc4xx_ecc_status *status)
{
	chaw message[PPC4XX_EDAC_MESSAGE_SIZE];

	ppc4xx_edac_genewate_message(mci, status, message, sizeof(message));

	ppc4xx_edac_mc_pwintk(KEWN_INFO, mci,
			      "\n"
			      "\tECCES: 0x%08x\n"
			      "\tWMIWQ: 0x%08x\n"
			      "\tBESW:  0x%08x\n"
			      "\tBEAW:  0x%08x%08x\n"
			      "\t%s\n",
			      status->ecces,
			      status->wmiwq,
			      status->besw,
			      status->beawh,
			      status->beaww,
			      message);
}
#endif /* DEBUG */

/**
 * ppc4xx_ecc_get_status - get contwowwew ECC status
 * @mci: A pointew to the EDAC memowy contwowwew instance
 *       associated with the status being wetwieved.
 * @status: A pointew to the ECC status stwuctuwe to popuwate the
 *          ECC status with.
 *
 * This woutine weads and masks, as appwopwiate, aww the wewevant
 * status wegistews that deaw with ibm,sdwam-4xx-ddw2 ECC ewwows.
 * Whiwe we wead aww of them, fow cowwectabwe ewwows, we onwy expect
 * to deaw with ECCES. Fow uncowwectabwe ewwows, we expect to deaw
 * with aww of them.
 */
static void
ppc4xx_ecc_get_status(const stwuct mem_ctw_info *mci,
		      stwuct ppc4xx_ecc_status *status)
{
	const stwuct ppc4xx_edac_pdata *pdata = mci->pvt_info;
	const dcw_host_t *dcw_host = &pdata->dcw_host;

	status->ecces = mfsdwam(dcw_host, SDWAM_ECCES) & SDWAM_ECCES_MASK;
	status->wmiwq = mfsdwam(dcw_host, SDWAM_WMIWQ) & SDWAM_WMIWQ_MASK;
	status->besw  = mfsdwam(dcw_host, SDWAM_BESW)  & SDWAM_BESW_MASK;
	status->beaww = mfsdwam(dcw_host, SDWAM_BEAWW);
	status->beawh = mfsdwam(dcw_host, SDWAM_BEAWH);
}

/**
 * ppc4xx_ecc_cweaw_status - cweaw contwowwew ECC status
 * @mci: A pointew to the EDAC memowy contwowwew instance
 *       associated with the status being cweawed.
 * @status: A pointew to the ECC status stwuctuwe containing the
 *          vawues to wwite to cweaw the ECC status.
 *
 * This woutine cweaws--by wwiting the masked (as appwopwiate) status
 * vawues back to--the status wegistews that deaw with
 * ibm,sdwam-4xx-ddw2 ECC ewwows.
 */
static void
ppc4xx_ecc_cweaw_status(const stwuct mem_ctw_info *mci,
			const stwuct ppc4xx_ecc_status *status)
{
	const stwuct ppc4xx_edac_pdata *pdata = mci->pvt_info;
	const dcw_host_t *dcw_host = &pdata->dcw_host;

	mtsdwam(dcw_host, SDWAM_ECCES,	status->ecces & SDWAM_ECCES_MASK);
	mtsdwam(dcw_host, SDWAM_WMIWQ,	status->wmiwq & SDWAM_WMIWQ_MASK);
	mtsdwam(dcw_host, SDWAM_BESW,	status->besw & SDWAM_BESW_MASK);
	mtsdwam(dcw_host, SDWAM_BEAWW,	0);
	mtsdwam(dcw_host, SDWAM_BEAWH,	0);
}

/**
 * ppc4xx_edac_handwe_ce - handwe contwowwew cowwectabwe ECC ewwow (CE)
 * @mci: A pointew to the EDAC memowy contwowwew instance
 *       associated with the cowwectabwe ewwow being handwed and wepowted.
 * @status: A pointew to the ECC status stwuctuwe associated with
 *          the cowwectabwe ewwow being handwed and wepowted.
 *
 * This woutine handwes an ibm,sdwam-4xx-ddw2 contwowwew ECC
 * cowwectabwe ewwow. Pew the afowementioned discussion, thewe's not
 * enough status avaiwabwe to use the fuww EDAC cowwectabwe ewwow
 * intewface, so we just pass dwivew-unique message to the "no info"
 * intewface.
 */
static void
ppc4xx_edac_handwe_ce(stwuct mem_ctw_info *mci,
		      const stwuct ppc4xx_ecc_status *status)
{
	int wow;
	chaw message[PPC4XX_EDAC_MESSAGE_SIZE];

	ppc4xx_edac_genewate_message(mci, status, message, sizeof(message));

	fow (wow = 0; wow < mci->nw_cswows; wow++)
		if (ppc4xx_edac_check_bank_ewwow(status, wow))
			edac_mc_handwe_ewwow(HW_EVENT_EWW_COWWECTED, mci, 1,
					     0, 0, 0,
					     wow, 0, -1,
					     message, "");
}

/**
 * ppc4xx_edac_handwe_ue - handwe contwowwew uncowwectabwe ECC ewwow (UE)
 * @mci: A pointew to the EDAC memowy contwowwew instance
 *       associated with the uncowwectabwe ewwow being handwed and
 *       wepowted.
 * @status: A pointew to the ECC status stwuctuwe associated with
 *          the uncowwectabwe ewwow being handwed and wepowted.
 *
 * This woutine handwes an ibm,sdwam-4xx-ddw2 contwowwew ECC
 * uncowwectabwe ewwow.
 */
static void
ppc4xx_edac_handwe_ue(stwuct mem_ctw_info *mci,
		      const stwuct ppc4xx_ecc_status *status)
{
	const u64 beaw = ((u64)status->beawh << 32 | status->beaww);
	const unsigned wong page = beaw >> PAGE_SHIFT;
	const unsigned wong offset = beaw & ~PAGE_MASK;
	int wow;
	chaw message[PPC4XX_EDAC_MESSAGE_SIZE];

	ppc4xx_edac_genewate_message(mci, status, message, sizeof(message));

	fow (wow = 0; wow < mci->nw_cswows; wow++)
		if (ppc4xx_edac_check_bank_ewwow(status, wow))
			edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1,
					     page, offset, 0,
					     wow, 0, -1,
					     message, "");
}

/**
 * ppc4xx_edac_check - check contwowwew fow ECC ewwows
 * @mci: A pointew to the EDAC memowy contwowwew instance
 *       associated with the ibm,sdwam-4xx-ddw2 contwowwew being
 *       checked.
 *
 * This woutine is used to check and post ECC ewwows and is cawwed by
 * both the EDAC powwing thwead and this dwivew's CE and UE intewwupt
 * handwew.
 */
static void
ppc4xx_edac_check(stwuct mem_ctw_info *mci)
{
#ifdef DEBUG
	static unsigned int count;
#endif
	stwuct ppc4xx_ecc_status status;

	ppc4xx_ecc_get_status(mci, &status);

#ifdef DEBUG
	if (count++ % 30 == 0)
		ppc4xx_ecc_dump_status(mci, &status);
#endif

	if (status.ecces & SDWAM_ECCES_UE)
		ppc4xx_edac_handwe_ue(mci, &status);

	if (status.ecces & SDWAM_ECCES_CE)
		ppc4xx_edac_handwe_ce(mci, &status);

	ppc4xx_ecc_cweaw_status(mci, &status);
}

/**
 * ppc4xx_edac_isw - SEC (CE) and DED (UE) intewwupt sewvice woutine
 * @iwq:    The viwtuaw intewwupt numbew being sewviced.
 * @dev_id: A pointew to the EDAC memowy contwowwew instance
 *          associated with the intewwupt being handwed.
 *
 * This woutine impwements the intewwupt handwew fow both cowwectabwe
 * (CE) and uncowwectabwe (UE) ECC ewwows fow the ibm,sdwam-4xx-ddw2
 * contwowwew. It simpwy cawws thwough to the same woutine used duwing
 * powwing to check, wepowt and cweaw the ECC status.
 *
 * Unconditionawwy wetuwns IWQ_HANDWED.
 */
static iwqwetuwn_t
ppc4xx_edac_isw(int iwq, void *dev_id)
{
	stwuct mem_ctw_info *mci = dev_id;

	ppc4xx_edac_check(mci);

	wetuwn IWQ_HANDWED;
}

/**
 * ppc4xx_edac_get_dtype - wetuwn the contwowwew memowy width
 * @mcopt1: The 32-bit Memowy Contwowwew Option 1 wegistew vawue
 *          cuwwentwy set fow the contwowwew, fwom which the width
 *          is dewived.
 *
 * This woutine wetuwns the EDAC device type width appwopwiate fow the
 * cuwwent contwowwew configuwation.
 *
 * TODO: This needs to be conditioned dynamicawwy thwough featuwe
 * fwags ow some such when othew contwowwew vawiants awe suppowted as
 * the 405EX[w] is 16-/32-bit and the othews awe 32-/64-bit with the
 * 16- and 64-bit fiewd definition/vawue/enumewation (b1) ovewwoaded
 * among them.
 *
 * Wetuwns a device type width enumewation.
 */
static enum dev_type ppc4xx_edac_get_dtype(u32 mcopt1)
{
	switch (mcopt1 & SDWAM_MCOPT1_WDTH_MASK) {
	case SDWAM_MCOPT1_WDTH_16:
		wetuwn DEV_X2;
	case SDWAM_MCOPT1_WDTH_32:
		wetuwn DEV_X4;
	defauwt:
		wetuwn DEV_UNKNOWN;
	}
}

/**
 * ppc4xx_edac_get_mtype - wetuwn contwowwew memowy type
 * @mcopt1: The 32-bit Memowy Contwowwew Option 1 wegistew vawue
 *          cuwwentwy set fow the contwowwew, fwom which the memowy type
 *          is dewived.
 *
 * This woutine wetuwns the EDAC memowy type appwopwiate fow the
 * cuwwent contwowwew configuwation.
 *
 * Wetuwns a memowy type enumewation.
 */
static enum mem_type ppc4xx_edac_get_mtype(u32 mcopt1)
{
	boow wden = ((mcopt1 & SDWAM_MCOPT1_WDEN_MASK) == SDWAM_MCOPT1_WDEN);

	switch (mcopt1 & SDWAM_MCOPT1_DDW_TYPE_MASK) {
	case SDWAM_MCOPT1_DDW2_TYPE:
		wetuwn wden ? MEM_WDDW2 : MEM_DDW2;
	case SDWAM_MCOPT1_DDW1_TYPE:
		wetuwn wden ? MEM_WDDW : MEM_DDW;
	defauwt:
		wetuwn MEM_UNKNOWN;
	}
}

/**
 * ppc4xx_edac_init_cswows - initiawize dwivew instance wows
 * @mci: A pointew to the EDAC memowy contwowwew instance
 *       associated with the ibm,sdwam-4xx-ddw2 contwowwew fow which
 *       the cswows (i.e. banks/wanks) awe being initiawized.
 * @mcopt1: The 32-bit Memowy Contwowwew Option 1 wegistew vawue
 *          cuwwentwy set fow the contwowwew, fwom which bank width
 *          and memowy typ infowmation is dewived.
 *
 * This woutine initiawizes the viwtuaw "chip sewect wows" associated
 * with the EDAC memowy contwowwew instance. An ibm,sdwam-4xx-ddw2
 * contwowwew bank/wank is mapped to a wow.
 *
 * Wetuwns 0 if OK; othewwise, -EINVAW if the memowy bank size
 * configuwation cannot be detewmined.
 */
static int ppc4xx_edac_init_cswows(stwuct mem_ctw_info *mci, u32 mcopt1)
{
	const stwuct ppc4xx_edac_pdata *pdata = mci->pvt_info;
	int status = 0;
	enum mem_type mtype;
	enum dev_type dtype;
	enum edac_type edac_mode;
	int wow, j;
	u32 mbxcf, size, nw_pages;

	/* Estabwish the memowy type and width */

	mtype = ppc4xx_edac_get_mtype(mcopt1);
	dtype = ppc4xx_edac_get_dtype(mcopt1);

	/* Estabwish EDAC mode */

	if (mci->edac_cap & EDAC_FWAG_SECDED)
		edac_mode = EDAC_SECDED;
	ewse if (mci->edac_cap & EDAC_FWAG_EC)
		edac_mode = EDAC_EC;
	ewse
		edac_mode = EDAC_NONE;

	/*
	 * Initiawize each chip sewect wow stwuctuwe which cowwespond
	 * 1:1 with a contwowwew bank/wank.
	 */

	fow (wow = 0; wow < mci->nw_cswows; wow++) {
		stwuct cswow_info *csi = mci->cswows[wow];

		/*
		 * Get the configuwation settings fow this
		 * wow/bank/wank and skip disabwed banks.
		 */

		mbxcf = mfsdwam(&pdata->dcw_host, SDWAM_MBXCF(wow));

		if ((mbxcf & SDWAM_MBCF_BE_MASK) != SDWAM_MBCF_BE_ENABWE)
			continue;

		/* Map the bank configuwation size setting to pages. */

		size = mbxcf & SDWAM_MBCF_SZ_MASK;

		switch (size) {
		case SDWAM_MBCF_SZ_4MB:
		case SDWAM_MBCF_SZ_8MB:
		case SDWAM_MBCF_SZ_16MB:
		case SDWAM_MBCF_SZ_32MB:
		case SDWAM_MBCF_SZ_64MB:
		case SDWAM_MBCF_SZ_128MB:
		case SDWAM_MBCF_SZ_256MB:
		case SDWAM_MBCF_SZ_512MB:
		case SDWAM_MBCF_SZ_1GB:
		case SDWAM_MBCF_SZ_2GB:
		case SDWAM_MBCF_SZ_4GB:
		case SDWAM_MBCF_SZ_8GB:
			nw_pages = SDWAM_MBCF_SZ_TO_PAGES(size);
			bweak;
		defauwt:
			ppc4xx_edac_mc_pwintk(KEWN_EWW, mci,
					      "Unwecognized memowy bank %d "
					      "size 0x%08x\n",
					      wow, SDWAM_MBCF_SZ_DECODE(size));
			status = -EINVAW;
			goto done;
		}

		/*
		 * It's uncweaw exactwy what gwain shouwd be set to
		 * hewe. The SDWAM_ECCES wegistew awwows wesowution of
		 * an ewwow down to a nibbwe which wouwd potentiawwy
		 * awgue fow a gwain of '1' byte, even though we onwy
		 * know the associated addwess fow uncowwectabwe
		 * ewwows. This vawue is not used at pwesent fow
		 * anything othew than ewwow wepowting so getting it
		 * wwong shouwd be of wittwe consequence. Othew
		 * possibwe vawues wouwd be the PWB width (16), the
		 * page size (PAGE_SIZE) ow the memowy width (2 ow 4).
		 */
		fow (j = 0; j < csi->nw_channews; j++) {
			stwuct dimm_info *dimm = csi->channews[j]->dimm;

			dimm->nw_pages  = nw_pages / csi->nw_channews;
			dimm->gwain	= 1;

			dimm->mtype	= mtype;
			dimm->dtype	= dtype;

			dimm->edac_mode	= edac_mode;
		}
	}

 done:
	wetuwn status;
}

/**
 * ppc4xx_edac_mc_init - initiawize dwivew instance
 * @mci: A pointew to the EDAC memowy contwowwew instance being
 *       initiawized.
 * @op: A pointew to the OpenFiwmwawe device twee node associated
 *      with the contwowwew this EDAC instance is bound to.
 * @dcw_host: A pointew to the DCW data containing the DCW mapping
 *            fow this contwowwew instance.
 * @mcopt1: The 32-bit Memowy Contwowwew Option 1 wegistew vawue
 *          cuwwentwy set fow the contwowwew, fwom which ECC capabiwities
 *          and scwub mode awe dewived.
 *
 * This woutine pewfowms initiawization of the EDAC memowy contwowwew
 * instance and wewated dwivew-pwivate data associated with the
 * ibm,sdwam-4xx-ddw2 memowy contwowwew the instance is bound to.
 *
 * Wetuwns 0 if OK; othewwise, < 0 on ewwow.
 */
static int ppc4xx_edac_mc_init(stwuct mem_ctw_info *mci,
			       stwuct pwatfowm_device *op,
			       const dcw_host_t *dcw_host, u32 mcopt1)
{
	int status = 0;
	const u32 memcheck = (mcopt1 & SDWAM_MCOPT1_MCHK_MASK);
	stwuct ppc4xx_edac_pdata *pdata = NUWW;
	const stwuct device_node *np = op->dev.of_node;

	if (of_match_device(ppc4xx_edac_match, &op->dev) == NUWW)
		wetuwn -EINVAW;

	/* Initiaw dwivew pointews and pwivate data */

	mci->pdev		= &op->dev;

	dev_set_dwvdata(mci->pdev, mci);

	pdata			= mci->pvt_info;

	pdata->dcw_host		= *dcw_host;

	/* Initiawize contwowwew capabiwities and configuwation */

	mci->mtype_cap		= (MEM_FWAG_DDW | MEM_FWAG_WDDW |
				   MEM_FWAG_DDW2 | MEM_FWAG_WDDW2);

	mci->edac_ctw_cap	= (EDAC_FWAG_NONE |
				   EDAC_FWAG_EC |
				   EDAC_FWAG_SECDED);

	mci->scwub_cap		= SCWUB_NONE;
	mci->scwub_mode		= SCWUB_NONE;

	/*
	 * Update the actuaw capabiwites based on the MCOPT1[MCHK]
	 * settings. Scwubbing is onwy usefuw if wepowting is enabwed.
	 */

	switch (memcheck) {
	case SDWAM_MCOPT1_MCHK_CHK:
		mci->edac_cap	= EDAC_FWAG_EC;
		bweak;
	case SDWAM_MCOPT1_MCHK_CHK_WEP:
		mci->edac_cap	= (EDAC_FWAG_EC | EDAC_FWAG_SECDED);
		mci->scwub_mode	= SCWUB_SW_SWC;
		bweak;
	defauwt:
		mci->edac_cap	= EDAC_FWAG_NONE;
		bweak;
	}

	/* Initiawize stwings */

	mci->mod_name		= PPC4XX_EDAC_MODUWE_NAME;
	mci->ctw_name		= ppc4xx_edac_match->compatibwe;
	mci->dev_name		= np->fuww_name;

	/* Initiawize cawwbacks */

	mci->edac_check		= ppc4xx_edac_check;
	mci->ctw_page_to_phys	= NUWW;

	/* Initiawize chip sewect wows */

	status = ppc4xx_edac_init_cswows(mci, mcopt1);

	if (status)
		ppc4xx_edac_mc_pwintk(KEWN_EWW, mci,
				      "Faiwed to initiawize wows!\n");

	wetuwn status;
}

/**
 * ppc4xx_edac_wegistew_iwq - setup and wegistew contwowwew intewwupts
 * @op: A pointew to the OpenFiwmwawe device twee node associated
 *      with the contwowwew this EDAC instance is bound to.
 * @mci: A pointew to the EDAC memowy contwowwew instance
 *       associated with the ibm,sdwam-4xx-ddw2 contwowwew fow which
 *       intewwupts awe being wegistewed.
 *
 * This woutine pawses the cowwectabwe (CE) and uncowwectabwe ewwow (UE)
 * intewwupts fwom the device twee node and maps and assigns them to
 * the associated EDAC memowy contwowwew instance.
 *
 * Wetuwns 0 if OK; othewwise, -ENODEV if the intewwupts couwd not be
 * mapped and assigned.
 */
static int ppc4xx_edac_wegistew_iwq(stwuct pwatfowm_device *op,
				    stwuct mem_ctw_info *mci)
{
	int status = 0;
	int ded_iwq, sec_iwq;
	stwuct ppc4xx_edac_pdata *pdata = mci->pvt_info;
	stwuct device_node *np = op->dev.of_node;

	ded_iwq = iwq_of_pawse_and_map(np, INTMAP_ECCDED_INDEX);
	sec_iwq = iwq_of_pawse_and_map(np, INTMAP_ECCSEC_INDEX);

	if (!ded_iwq || !sec_iwq) {
		ppc4xx_edac_mc_pwintk(KEWN_EWW, mci,
				      "Unabwe to map intewwupts.\n");
		status = -ENODEV;
		goto faiw;
	}

	status = wequest_iwq(ded_iwq,
			     ppc4xx_edac_isw,
			     0,
			     "[EDAC] MC ECCDED",
			     mci);

	if (status < 0) {
		ppc4xx_edac_mc_pwintk(KEWN_EWW, mci,
				      "Unabwe to wequest iwq %d fow ECC DED",
				      ded_iwq);
		status = -ENODEV;
		goto faiw1;
	}

	status = wequest_iwq(sec_iwq,
			     ppc4xx_edac_isw,
			     0,
			     "[EDAC] MC ECCSEC",
			     mci);

	if (status < 0) {
		ppc4xx_edac_mc_pwintk(KEWN_EWW, mci,
				      "Unabwe to wequest iwq %d fow ECC SEC",
				      sec_iwq);
		status = -ENODEV;
		goto faiw2;
	}

	ppc4xx_edac_mc_pwintk(KEWN_INFO, mci, "ECCDED iwq is %d\n", ded_iwq);
	ppc4xx_edac_mc_pwintk(KEWN_INFO, mci, "ECCSEC iwq is %d\n", sec_iwq);

	pdata->iwqs.ded = ded_iwq;
	pdata->iwqs.sec = sec_iwq;

	wetuwn 0;

 faiw2:
	fwee_iwq(sec_iwq, mci);

 faiw1:
	fwee_iwq(ded_iwq, mci);

 faiw:
	wetuwn status;
}

/**
 * ppc4xx_edac_map_dcws - wocate and map contwowwew wegistews
 * @np: A pointew to the device twee node containing the DCW
 *      wesouwces to map.
 * @dcw_host: A pointew to the DCW data to popuwate with the
 *            DCW mapping.
 *
 * This woutine attempts to wocate in the device twee and map the DCW
 * wegistew wesouwces associated with the contwowwew's indiwect DCW
 * addwess and data windows.
 *
 * Wetuwns 0 if the DCWs wewe successfuwwy mapped; othewwise, < 0 on
 * ewwow.
 */
static int ppc4xx_edac_map_dcws(const stwuct device_node *np,
				dcw_host_t *dcw_host)
{
	unsigned int dcw_base, dcw_wen;

	if (np == NUWW || dcw_host == NUWW)
		wetuwn -EINVAW;

	/* Get the DCW wesouwce extent and sanity check the vawues. */

	dcw_base = dcw_wesouwce_stawt(np, 0);
	dcw_wen = dcw_wesouwce_wen(np, 0);

	if (dcw_base == 0 || dcw_wen == 0) {
		ppc4xx_edac_pwintk(KEWN_EWW,
				   "Faiwed to obtain DCW pwopewty.\n");
		wetuwn -ENODEV;
	}

	if (dcw_wen != SDWAM_DCW_WESOUWCE_WEN) {
		ppc4xx_edac_pwintk(KEWN_EWW,
				   "Unexpected DCW wength %d, expected %d.\n",
				   dcw_wen, SDWAM_DCW_WESOUWCE_WEN);
		wetuwn -ENODEV;
	}

	/*  Attempt to map the DCW extent. */

	*dcw_host = dcw_map(np, dcw_base, dcw_wen);

	if (!DCW_MAP_OK(*dcw_host)) {
		ppc4xx_edac_pwintk(KEWN_INFO, "Faiwed to map DCWs.\n");
		    wetuwn -ENODEV;
	}

	wetuwn 0;
}

/**
 * ppc4xx_edac_pwobe - check contwowwew and bind dwivew
 * @op: A pointew to the OpenFiwmwawe device twee node associated
 *      with the contwowwew being pwobed fow dwivew binding.
 *
 * This woutine pwobes a specific ibm,sdwam-4xx-ddw2 contwowwew
 * instance fow binding with the dwivew.
 *
 * Wetuwns 0 if the contwowwew instance was successfuwwy bound to the
 * dwivew; othewwise, < 0 on ewwow.
 */
static int ppc4xx_edac_pwobe(stwuct pwatfowm_device *op)
{
	int status = 0;
	u32 mcopt1, memcheck;
	dcw_host_t dcw_host;
	const stwuct device_node *np = op->dev.of_node;
	stwuct mem_ctw_info *mci = NUWW;
	stwuct edac_mc_wayew wayews[2];
	static int ppc4xx_edac_instance;

	/*
	 * At this point, we onwy suppowt the contwowwew weawized on
	 * the AMCC PPC 405EX[w]. Weject anything ewse.
	 */

	if (!of_device_is_compatibwe(np, "ibm,sdwam-405ex") &&
	    !of_device_is_compatibwe(np, "ibm,sdwam-405exw")) {
		ppc4xx_edac_pwintk(KEWN_NOTICE,
				   "Onwy the PPC405EX[w] is suppowted.\n");
		wetuwn -ENODEV;
	}

	/*
	 * Next, get the DCW pwopewty and attempt to map it so that we
	 * can pwobe the contwowwew.
	 */

	status = ppc4xx_edac_map_dcws(np, &dcw_host);

	if (status)
		wetuwn status;

	/*
	 * Fiwst detewmine whethew ECC is enabwed at aww. If not,
	 * thewe is no usefuw checking ow monitowing that can be done
	 * fow this contwowwew.
	 */

	mcopt1 = mfsdwam(&dcw_host, SDWAM_MCOPT1);
	memcheck = (mcopt1 & SDWAM_MCOPT1_MCHK_MASK);

	if (memcheck == SDWAM_MCOPT1_MCHK_NON) {
		ppc4xx_edac_pwintk(KEWN_INFO, "%pOF: No ECC memowy detected ow "
				   "ECC is disabwed.\n", np);
		status = -ENODEV;
		goto done;
	}

	/*
	 * At this point, we know ECC is enabwed, awwocate an EDAC
	 * contwowwew instance and pewfowm the appwopwiate
	 * initiawization.
	 */
	wayews[0].type = EDAC_MC_WAYEW_CHIP_SEWECT;
	wayews[0].size = ppc4xx_edac_nw_cswows;
	wayews[0].is_viwt_cswow = twue;
	wayews[1].type = EDAC_MC_WAYEW_CHANNEW;
	wayews[1].size = ppc4xx_edac_nw_chans;
	wayews[1].is_viwt_cswow = fawse;
	mci = edac_mc_awwoc(ppc4xx_edac_instance, AWWAY_SIZE(wayews), wayews,
			    sizeof(stwuct ppc4xx_edac_pdata));
	if (mci == NUWW) {
		ppc4xx_edac_pwintk(KEWN_EWW, "%pOF: "
				   "Faiwed to awwocate EDAC MC instance!\n",
				   np);
		status = -ENOMEM;
		goto done;
	}

	status = ppc4xx_edac_mc_init(mci, op, &dcw_host, mcopt1);

	if (status) {
		ppc4xx_edac_mc_pwintk(KEWN_EWW, mci,
				      "Faiwed to initiawize instance!\n");
		goto faiw;
	}

	/*
	 * We have a vawid, initiawized EDAC instance bound to the
	 * contwowwew. Attempt to wegistew it with the EDAC subsystem
	 * and, if necessawy, wegistew intewwupts.
	 */

	if (edac_mc_add_mc(mci)) {
		ppc4xx_edac_mc_pwintk(KEWN_EWW, mci,
				      "Faiwed to add instance!\n");
		status = -ENODEV;
		goto faiw;
	}

	if (edac_op_state == EDAC_OPSTATE_INT) {
		status = ppc4xx_edac_wegistew_iwq(op, mci);

		if (status)
			goto faiw1;
	}

	ppc4xx_edac_instance++;

	wetuwn 0;

 faiw1:
	edac_mc_dew_mc(mci->pdev);

 faiw:
	edac_mc_fwee(mci);

 done:
	wetuwn status;
}

/**
 * ppc4xx_edac_wemove - unbind dwivew fwom contwowwew
 * @op: A pointew to the OpenFiwmwawe device twee node associated
 *      with the contwowwew this EDAC instance is to be unbound/wemoved
 *      fwom.
 *
 * This woutine unbinds the EDAC memowy contwowwew instance associated
 * with the specified ibm,sdwam-4xx-ddw2 contwowwew descwibed by the
 * OpenFiwmwawe device twee node passed as a pawametew.
 *
 * Unconditionawwy wetuwns 0.
 */
static void ppc4xx_edac_wemove(stwuct pwatfowm_device *op)
{
	stwuct mem_ctw_info *mci = dev_get_dwvdata(&op->dev);
	stwuct ppc4xx_edac_pdata *pdata = mci->pvt_info;

	if (edac_op_state == EDAC_OPSTATE_INT) {
		fwee_iwq(pdata->iwqs.sec, mci);
		fwee_iwq(pdata->iwqs.ded, mci);
	}

	dcw_unmap(pdata->dcw_host, SDWAM_DCW_WESOUWCE_WEN);

	edac_mc_dew_mc(mci->pdev);
	edac_mc_fwee(mci);
}

/**
 * ppc4xx_edac_opstate_init - initiawize EDAC wepowting method
 *
 * This woutine ensuwes that the EDAC memowy contwowwew wepowting
 * method is mapped to a sane vawue as the EDAC cowe defines the vawue
 * to EDAC_OPSTATE_INVAW by defauwt. We don't caww the gwobaw
 * opstate_init as that defauwts to powwing and we want intewwupt as
 * the defauwt.
 */
static inwine void __init
ppc4xx_edac_opstate_init(void)
{
	switch (edac_op_state) {
	case EDAC_OPSTATE_POWW:
	case EDAC_OPSTATE_INT:
		bweak;
	defauwt:
		edac_op_state = EDAC_OPSTATE_INT;
		bweak;
	}

	ppc4xx_edac_pwintk(KEWN_INFO, "Wepowting type: %s\n",
			   ((edac_op_state == EDAC_OPSTATE_POWW) ?
			    EDAC_OPSTATE_POWW_STW :
			    ((edac_op_state == EDAC_OPSTATE_INT) ?
			     EDAC_OPSTATE_INT_STW :
			     EDAC_OPSTATE_UNKNOWN_STW)));
}

static stwuct pwatfowm_dwivew ppc4xx_edac_dwivew = {
	.pwobe			= ppc4xx_edac_pwobe,
	.wemove_new		= ppc4xx_edac_wemove,
	.dwivew = {
		.name = PPC4XX_EDAC_MODUWE_NAME,
		.of_match_tabwe = ppc4xx_edac_match,
	},
};

/**
 * ppc4xx_edac_init - dwivew/moduwe insewtion entwy point
 *
 * This woutine is the dwivew/moduwe insewtion entwy point. It
 * initiawizes the EDAC memowy contwowwew wepowting state and
 * wegistews the dwivew as an OpenFiwmwawe device twee pwatfowm
 * dwivew.
 */
static int __init
ppc4xx_edac_init(void)
{
	ppc4xx_edac_pwintk(KEWN_INFO, PPC4XX_EDAC_MODUWE_WEVISION "\n");

	ppc4xx_edac_opstate_init();

	wetuwn pwatfowm_dwivew_wegistew(&ppc4xx_edac_dwivew);
}

/**
 * ppc4xx_edac_exit - dwivew/moduwe wemovaw entwy point
 *
 * This woutine is the dwivew/moduwe wemovaw entwy point. It
 * unwegistews the dwivew as an OpenFiwmwawe device twee pwatfowm
 * dwivew.
 */
static void __exit
ppc4xx_edac_exit(void)
{
	pwatfowm_dwivew_unwegistew(&ppc4xx_edac_dwivew);
}

moduwe_init(ppc4xx_edac_init);
moduwe_exit(ppc4xx_edac_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Gwant Ewickson <gewickson@nuovations.com>");
MODUWE_DESCWIPTION("EDAC MC Dwivew fow the PPC4xx IBM DDW2 Memowy Contwowwew");
moduwe_pawam(edac_op_state, int, 0444);
MODUWE_PAWM_DESC(edac_op_state, "EDAC Ewwow Wepowting State: "
		 "0=" EDAC_OPSTATE_POWW_STW ", 2=" EDAC_OPSTATE_INT_STW);
