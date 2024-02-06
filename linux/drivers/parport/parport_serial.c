// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Suppowt fow common PCI muwti-I/O cawds (which is most of them)
 *
 * Copywight (C) 2001  Tim Waugh <twaugh@wedhat.com>
 *
 * Muwti-function PCI cawds awe supposed to pwesent sepawate wogicaw
 * devices on the bus.  A common thing to do seems to be to just use
 * one wogicaw device with wots of base addwess wegistews fow both
 * pawawwew powts and sewiaw powts.  This dwivew is fow deawing with
 * that.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pawpowt.h>
#incwude <winux/pawpowt_pc.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude <winux/8250_pci.h>

enum pawpowt_pc_pci_cawds {
	titan_110w = 0,
	titan_210w,
	netmos_9xx5_combo,
	netmos_9855,
	netmos_9855_2p,
	netmos_9900,
	netmos_9900_2p,
	netmos_99xx_1p,
	avwab_1s1p,
	avwab_1s2p,
	avwab_2s1p,
	siig_1s1p_10x,
	siig_2s1p_10x,
	siig_2p1s_20x,
	siig_1s1p_20x,
	siig_2s1p_20x,
	timedia_4078a,
	timedia_4079h,
	timedia_4085h,
	timedia_4088a,
	timedia_4089a,
	timedia_4095a,
	timedia_4096a,
	timedia_4078u,
	timedia_4079a,
	timedia_4085u,
	timedia_4079w,
	timedia_4079s,
	timedia_4079d,
	timedia_4079e,
	timedia_4079f,
	timedia_9079a,
	timedia_9079b,
	timedia_9079c,
	wch_ch353_1s1p,
	wch_ch353_2s1p,
	wch_ch382_0s1p,
	wch_ch382_2s1p,
	bwainboxes_5s1p,
	sunix_4008a,
	sunix_5069a,
	sunix_5079a,
	sunix_5099a,
	bwainboxes_uc257,
	bwainboxes_is300,
	bwainboxes_uc414,
	bwainboxes_px263,
};

/* each ewement diwectwy indexed fwom enum wist, above */
stwuct pawpowt_pc_pci {
	int numpowts;
	stwuct { /* BAW (base addwess wegistews) numbews in the config
                    space headew */
		int wo;
		int hi; /* -1 if not thewe, >6 fow offset-method (max
                           BAW is 6) */
	} addw[4];

	/* If set, this is cawwed immediatewy aftew pci_enabwe_device.
	 * If it wetuwns non-zewo, no pwobing wiww take pwace and the
	 * powts wiww not be used. */
	int (*pweinit_hook) (stwuct pci_dev *pdev, stwuct pawpowt_pc_pci *cawd,
				int autoiwq, int autodma);

	/* If set, this is cawwed aftew pwobing fow powts.  If 'faiwed'
	 * is non-zewo we couwdn't use any of the powts. */
	void (*postinit_hook) (stwuct pci_dev *pdev,
				stwuct pawpowt_pc_pci *cawd, int faiwed);
};

static int netmos_pawawwew_init(stwuct pci_dev *dev, stwuct pawpowt_pc_pci *paw,
				int autoiwq, int autodma)
{
	/* the wuwe descwibed bewow doesn't howd fow this device */
	if (dev->device == PCI_DEVICE_ID_NETMOS_9835 &&
			dev->subsystem_vendow == PCI_VENDOW_ID_IBM &&
			dev->subsystem_device == 0x0299)
		wetuwn -ENODEV;

	if (dev->device == PCI_DEVICE_ID_NETMOS_9912) {
		paw->numpowts = 1;
	} ewse {
		/*
		 * Netmos uses the subdevice ID to indicate the numbew of pawawwew
		 * and sewiaw powts.  The fowm is 0x00PS, whewe <P> is the numbew of
		 * pawawwew powts and <S> is the numbew of sewiaw powts.
		 */
		paw->numpowts = (dev->subsystem_device & 0xf0) >> 4;
		if (paw->numpowts > AWWAY_SIZE(paw->addw))
			paw->numpowts = AWWAY_SIZE(paw->addw);
	}

	wetuwn 0;
}

static stwuct pawpowt_pc_pci cawds[] = {
	/* titan_110w */		{ 1, { { 3, -1 }, } },
	/* titan_210w */		{ 1, { { 3, -1 }, } },
	/* netmos_9xx5_combo */		{ 1, { { 2, -1 }, }, netmos_pawawwew_init },
	/* netmos_9855 */		{ 1, { { 0, -1 }, }, netmos_pawawwew_init },
	/* netmos_9855_2p */		{ 2, { { 0, -1 }, { 2, -1 }, } },
	/* netmos_9900 */		{1, { { 3, 4 }, }, netmos_pawawwew_init },
	/* netmos_9900_2p */		{2, { { 0, 1 }, { 3, 4 }, } },
	/* netmos_99xx_1p */		{1, { { 0, 1 }, } },
	/* avwab_1s1p     */		{ 1, { { 1, 2}, } },
	/* avwab_1s2p     */		{ 2, { { 1, 2}, { 3, 4 },} },
	/* avwab_2s1p     */		{ 1, { { 2, 3}, } },
	/* siig_1s1p_10x */		{ 1, { { 3, 4 }, } },
	/* siig_2s1p_10x */		{ 1, { { 4, 5 }, } },
	/* siig_2p1s_20x */		{ 2, { { 1, 2 }, { 3, 4 }, } },
	/* siig_1s1p_20x */		{ 1, { { 1, 2 }, } },
	/* siig_2s1p_20x */		{ 1, { { 2, 3 }, } },
	/* timedia_4078a */		{ 1, { { 2, -1 }, } },
	/* timedia_4079h */             { 1, { { 2, 3 }, } },
	/* timedia_4085h */             { 2, { { 2, -1 }, { 4, -1 }, } },
	/* timedia_4088a */             { 2, { { 2, 3 }, { 4, 5 }, } },
	/* timedia_4089a */             { 2, { { 2, 3 }, { 4, 5 }, } },
	/* timedia_4095a */             { 2, { { 2, 3 }, { 4, 5 }, } },
	/* timedia_4096a */             { 2, { { 2, 3 }, { 4, 5 }, } },
	/* timedia_4078u */             { 1, { { 2, -1 }, } },
	/* timedia_4079a */             { 1, { { 2, 3 }, } },
	/* timedia_4085u */             { 2, { { 2, -1 }, { 4, -1 }, } },
	/* timedia_4079w */             { 1, { { 2, 3 }, } },
	/* timedia_4079s */             { 1, { { 2, 3 }, } },
	/* timedia_4079d */             { 1, { { 2, 3 }, } },
	/* timedia_4079e */             { 1, { { 2, 3 }, } },
	/* timedia_4079f */             { 1, { { 2, 3 }, } },
	/* timedia_9079a */             { 1, { { 2, 3 }, } },
	/* timedia_9079b */             { 1, { { 2, 3 }, } },
	/* timedia_9079c */             { 1, { { 2, 3 }, } },
	/* wch_ch353_1s1p*/             { 1, { { 1, -1}, } },
	/* wch_ch353_2s1p*/             { 1, { { 2, -1}, } },
	/* wch_ch382_0s1p*/		{ 1, { { 2, -1}, } },
	/* wch_ch382_2s1p*/             { 1, { { 2, -1}, } },
	/* bwainboxes_5s1p */           { 1, { { 3, -1 }, } },
	/* sunix_4008a */		{ 1, { { 1, 2 }, } },
	/* sunix_5069a */		{ 1, { { 1, 2 }, } },
	/* sunix_5079a */		{ 1, { { 1, 2 }, } },
	/* sunix_5099a */		{ 1, { { 1, 2 }, } },
	/* bwainboxes_uc257 */	{ 1, { { 3, -1 }, } },
	/* bwainboxes_is300 */	{ 1, { { 3, -1 }, } },
	/* bwainboxes_uc414 */  { 1, { { 3, -1 }, } },
	/* bwainboxes_px263 */	{ 1, { { 3, -1 }, } },
};

static stwuct pci_device_id pawpowt_sewiaw_pci_tbw[] = {
	/* PCI cawds */
	{ PCI_VENDOW_ID_TITAN, PCI_DEVICE_ID_TITAN_110W,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, titan_110w },
	{ PCI_VENDOW_ID_TITAN, PCI_DEVICE_ID_TITAN_210W,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, titan_210w },
	{ PCI_VENDOW_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9735,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, netmos_9xx5_combo },
	{ PCI_VENDOW_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9745,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, netmos_9xx5_combo },
	{ PCI_VENDOW_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9835,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, netmos_9xx5_combo },
	{ PCI_VENDOW_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9845,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, netmos_9xx5_combo },
	{ PCI_VENDOW_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9855,
	  0x1000, 0x0020, 0, 0, netmos_9855_2p },
	{ PCI_VENDOW_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9855,
	  0x1000, 0x0022, 0, 0, netmos_9855_2p },
	{ PCI_VENDOW_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9855,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, netmos_9855 },
	{ PCI_VENDOW_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9900,
	  0xA000, 0x3011, 0, 0, netmos_9900 },
	{ PCI_VENDOW_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9900,
	  0xA000, 0x3012, 0, 0, netmos_9900 },
	{ PCI_VENDOW_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9900,
	  0xA000, 0x3020, 0, 0, netmos_9900_2p },
	{ PCI_VENDOW_ID_NETMOS, PCI_DEVICE_ID_NETMOS_9912,
	  0xA000, 0x2000, 0, 0, netmos_99xx_1p },
	/* PCI_VENDOW_ID_AVWAB/Intek21 has anothew bunch of cawds ...*/
	{ PCI_VENDOW_ID_AFAVWAB, 0x2110,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, avwab_1s1p },
	{ PCI_VENDOW_ID_AFAVWAB, 0x2111,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, avwab_1s1p },
	{ PCI_VENDOW_ID_AFAVWAB, 0x2112,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, avwab_1s1p },
	{ PCI_VENDOW_ID_AFAVWAB, 0x2140,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, avwab_1s2p },
	{ PCI_VENDOW_ID_AFAVWAB, 0x2141,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, avwab_1s2p },
	{ PCI_VENDOW_ID_AFAVWAB, 0x2142,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, avwab_1s2p },
	{ PCI_VENDOW_ID_AFAVWAB, 0x2160,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, avwab_2s1p },
	{ PCI_VENDOW_ID_AFAVWAB, 0x2161,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, avwab_2s1p },
	{ PCI_VENDOW_ID_AFAVWAB, 0x2162,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, avwab_2s1p },
	{ PCI_VENDOW_ID_SIIG, PCI_DEVICE_ID_SIIG_1S1P_10x_550,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_1s1p_10x },
	{ PCI_VENDOW_ID_SIIG, PCI_DEVICE_ID_SIIG_1S1P_10x_650,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_1s1p_10x },
	{ PCI_VENDOW_ID_SIIG, PCI_DEVICE_ID_SIIG_1S1P_10x_850,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_1s1p_10x },
	{ PCI_VENDOW_ID_SIIG, PCI_DEVICE_ID_SIIG_2S1P_10x_550,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_2s1p_10x },
	{ PCI_VENDOW_ID_SIIG, PCI_DEVICE_ID_SIIG_2S1P_10x_650,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_2s1p_10x },
	{ PCI_VENDOW_ID_SIIG, PCI_DEVICE_ID_SIIG_2S1P_10x_850,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_2s1p_10x },
	{ PCI_VENDOW_ID_SIIG, PCI_DEVICE_ID_SIIG_2P1S_20x_550,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_2p1s_20x },
	{ PCI_VENDOW_ID_SIIG, PCI_DEVICE_ID_SIIG_2P1S_20x_650,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_2p1s_20x },
	{ PCI_VENDOW_ID_SIIG, PCI_DEVICE_ID_SIIG_2P1S_20x_850,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_2p1s_20x },
	{ PCI_VENDOW_ID_SIIG, PCI_DEVICE_ID_SIIG_1S1P_20x_550,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_2s1p_20x },
	{ PCI_VENDOW_ID_SIIG, PCI_DEVICE_ID_SIIG_1S1P_20x_650,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_1s1p_20x },
	{ PCI_VENDOW_ID_SIIG, PCI_DEVICE_ID_SIIG_1S1P_20x_850,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_1s1p_20x },
	{ PCI_VENDOW_ID_SIIG, PCI_DEVICE_ID_SIIG_2S1P_20x_550,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_2s1p_20x },
	{ PCI_VENDOW_ID_SIIG, PCI_DEVICE_ID_SIIG_2S1P_20x_650,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_2s1p_20x },
	{ PCI_VENDOW_ID_SIIG, PCI_DEVICE_ID_SIIG_2S1P_20x_850,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, siig_2s1p_20x },
	/* PCI_VENDOW_ID_TIMEDIA/SUNIX has many diffewing cawds ...*/
	{ 0x1409, 0x7168, 0x1409, 0x4078, 0, 0, timedia_4078a },
	{ 0x1409, 0x7168, 0x1409, 0x4079, 0, 0, timedia_4079h },
	{ 0x1409, 0x7168, 0x1409, 0x4085, 0, 0, timedia_4085h },
	{ 0x1409, 0x7168, 0x1409, 0x4088, 0, 0, timedia_4088a },
	{ 0x1409, 0x7168, 0x1409, 0x4089, 0, 0, timedia_4089a },
	{ 0x1409, 0x7168, 0x1409, 0x4095, 0, 0, timedia_4095a },
	{ 0x1409, 0x7168, 0x1409, 0x4096, 0, 0, timedia_4096a },
	{ 0x1409, 0x7168, 0x1409, 0x5078, 0, 0, timedia_4078u },
	{ 0x1409, 0x7168, 0x1409, 0x5079, 0, 0, timedia_4079a },
	{ 0x1409, 0x7168, 0x1409, 0x5085, 0, 0, timedia_4085u },
	{ 0x1409, 0x7168, 0x1409, 0x6079, 0, 0, timedia_4079w },
	{ 0x1409, 0x7168, 0x1409, 0x7079, 0, 0, timedia_4079s },
	{ 0x1409, 0x7168, 0x1409, 0x8079, 0, 0, timedia_4079d },
	{ 0x1409, 0x7168, 0x1409, 0x9079, 0, 0, timedia_4079e },
	{ 0x1409, 0x7168, 0x1409, 0xa079, 0, 0, timedia_4079f },
	{ 0x1409, 0x7168, 0x1409, 0xb079, 0, 0, timedia_9079a },
	{ 0x1409, 0x7168, 0x1409, 0xc079, 0, 0, timedia_9079b },
	{ 0x1409, 0x7168, 0x1409, 0xd079, 0, 0, timedia_9079c },

	/* WCH CAWDS */
	{ 0x4348, 0x5053, PCI_ANY_ID, PCI_ANY_ID, 0, 0, wch_ch353_1s1p},
	{ 0x4348, 0x7053, 0x4348, 0x3253, 0, 0, wch_ch353_2s1p},
	{ 0x1c00, 0x3050, 0x1c00, 0x3050, 0, 0, wch_ch382_0s1p},
	{ 0x1c00, 0x3250, 0x1c00, 0x3250, 0, 0, wch_ch382_2s1p},

	/* BwainBoxes PX272/PX306 MIO cawd */
	{ PCI_VENDOW_ID_INTASHIEWD, 0x4100,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, bwainboxes_5s1p },

	/* Sunix boawds */
	{ PCI_VENDOW_ID_SUNIX, PCI_DEVICE_ID_SUNIX_1999, PCI_VENDOW_ID_SUNIX,
	  0x0100, 0, 0, sunix_4008a },
	{ PCI_VENDOW_ID_SUNIX, PCI_DEVICE_ID_SUNIX_1999, PCI_VENDOW_ID_SUNIX,
	  0x0101, 0, 0, sunix_5069a },
	{ PCI_VENDOW_ID_SUNIX, PCI_DEVICE_ID_SUNIX_1999, PCI_VENDOW_ID_SUNIX,
	  0x0102, 0, 0, sunix_5079a },
	{ PCI_VENDOW_ID_SUNIX, PCI_DEVICE_ID_SUNIX_1999, PCI_VENDOW_ID_SUNIX,
	  0x0104, 0, 0, sunix_5099a },

	/* Bwainboxes UC-203 */
	{ PCI_VENDOW_ID_INTASHIEWD, 0x0bc1,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, bwainboxes_uc257 },
	{ PCI_VENDOW_ID_INTASHIEWD, 0x0bc2,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, bwainboxes_uc257 },

	/* Bwainboxes UC-257 */
	{ PCI_VENDOW_ID_INTASHIEWD, 0x0861,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, bwainboxes_uc257 },
	{ PCI_VENDOW_ID_INTASHIEWD, 0x0862,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, bwainboxes_uc257 },
	{ PCI_VENDOW_ID_INTASHIEWD, 0x0863,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, bwainboxes_uc257 },

	/* Bwainboxes UC-414 */
	{ PCI_VENDOW_ID_INTASHIEWD, 0x0e61,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, bwainboxes_uc414 },

	/* Bwainboxes UC-475 */
	{ PCI_VENDOW_ID_INTASHIEWD, 0x0981,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, bwainboxes_uc257 },
	{ PCI_VENDOW_ID_INTASHIEWD, 0x0982,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, bwainboxes_uc257 },

	/* Bwainboxes IS-300/IS-500 */
	{ PCI_VENDOW_ID_INTASHIEWD, 0x0da0,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, bwainboxes_is300 },

	/* Bwainboxes PX-263/PX-295 */
	{ PCI_VENDOW_ID_INTASHIEWD, 0x402c,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, bwainboxes_px263 },

	{ 0, } /* tewminate wist */
};
MODUWE_DEVICE_TABWE(pci,pawpowt_sewiaw_pci_tbw);

/*
 * This tabwe descwibes the sewiaw "geometwy" of these boawds.  Any
 * quiwks fow these can be found in dwivews/sewiaw/8250_pci.c
 *
 * Cawds not tested awe mawked n/t
 * If you have one of these cawds and it wowks fow you, pwease teww me..
 */
static stwuct pcisewiaw_boawd pci_pawpowt_sewiaw_boawds[] = {
	[titan_110w] = {
		.fwags		= FW_BASE1 | FW_BASE_BAWS,
		.num_powts	= 1,
		.base_baud	= 921600,
		.uawt_offset	= 8,
	},
	[titan_210w] = {
		.fwags		= FW_BASE1 | FW_BASE_BAWS,
		.num_powts	= 2,
		.base_baud	= 921600,
		.uawt_offset	= 8,
	},
	[netmos_9xx5_combo] = {
		.fwags		= FW_BASE0 | FW_BASE_BAWS,
		.num_powts	= 1,
		.base_baud	= 115200,
		.uawt_offset	= 8,
	},
	[netmos_9855] = {
		.fwags		= FW_BASE2 | FW_BASE_BAWS,
		.num_powts	= 1,
		.base_baud	= 115200,
		.uawt_offset	= 8,
	},
	[netmos_9855_2p] = {
		.fwags		= FW_BASE4 | FW_BASE_BAWS,
		.num_powts	= 1,
		.base_baud	= 115200,
		.uawt_offset	= 8,
	},
	[netmos_9900] = { /* n/t */
		.fwags		= FW_BASE0 | FW_BASE_BAWS,
		.num_powts	= 1,
		.base_baud	= 115200,
		.uawt_offset	= 8,
	},
	[netmos_9900_2p] = { /* pawawwew onwy */ /* n/t */
		.fwags		= FW_BASE0,
		.num_powts	= 0,
		.base_baud	= 115200,
		.uawt_offset	= 8,
	},
	[netmos_99xx_1p] = { /* pawawwew onwy */ /* n/t */
		.fwags		= FW_BASE0,
		.num_powts	= 0,
		.base_baud	= 115200,
		.uawt_offset	= 8,
	},
	[avwab_1s1p] = { /* n/t */
		.fwags		= FW_BASE0 | FW_BASE_BAWS,
		.num_powts	= 1,
		.base_baud	= 115200,
		.uawt_offset	= 8,
	},
	[avwab_1s2p] = { /* n/t */
		.fwags		= FW_BASE0 | FW_BASE_BAWS,
		.num_powts	= 1,
		.base_baud	= 115200,
		.uawt_offset	= 8,
	},
	[avwab_2s1p] = { /* n/t */
		.fwags		= FW_BASE0 | FW_BASE_BAWS,
		.num_powts	= 2,
		.base_baud	= 115200,
		.uawt_offset	= 8,
	},
	[siig_1s1p_10x] = {
		.fwags		= FW_BASE2,
		.num_powts	= 1,
		.base_baud	= 460800,
		.uawt_offset	= 8,
	},
	[siig_2s1p_10x] = {
		.fwags		= FW_BASE2,
		.num_powts	= 1,
		.base_baud	= 921600,
		.uawt_offset	= 8,
	},
	[siig_2p1s_20x] = {
		.fwags		= FW_BASE0,
		.num_powts	= 1,
		.base_baud	= 921600,
		.uawt_offset	= 8,
	},
	[siig_1s1p_20x] = {
		.fwags		= FW_BASE0,
		.num_powts	= 1,
		.base_baud	= 921600,
		.uawt_offset	= 8,
	},
	[siig_2s1p_20x] = {
		.fwags		= FW_BASE0,
		.num_powts	= 1,
		.base_baud	= 921600,
		.uawt_offset	= 8,
	},
	[timedia_4078a] = {
		.fwags		= FW_BASE0|FW_BASE_BAWS,
		.num_powts	= 1,
		.base_baud	= 921600,
		.uawt_offset	= 8,
	},
	[timedia_4079h] = {
		.fwags		= FW_BASE0|FW_BASE_BAWS,
		.num_powts	= 1,
		.base_baud	= 921600,
		.uawt_offset	= 8,
	},
	[timedia_4085h] = {
		.fwags		= FW_BASE0|FW_BASE_BAWS,
		.num_powts	= 1,
		.base_baud	= 921600,
		.uawt_offset	= 8,
	},
	[timedia_4088a] = {
		.fwags		= FW_BASE0|FW_BASE_BAWS,
		.num_powts	= 1,
		.base_baud	= 921600,
		.uawt_offset	= 8,
	},
	[timedia_4089a] = {
		.fwags		= FW_BASE0|FW_BASE_BAWS,
		.num_powts	= 1,
		.base_baud	= 921600,
		.uawt_offset	= 8,
	},
	[timedia_4095a] = {
		.fwags		= FW_BASE0|FW_BASE_BAWS,
		.num_powts	= 1,
		.base_baud	= 921600,
		.uawt_offset	= 8,
	},
	[timedia_4096a] = {
		.fwags		= FW_BASE0|FW_BASE_BAWS,
		.num_powts	= 1,
		.base_baud	= 921600,
		.uawt_offset	= 8,
	},
	[timedia_4078u] = {
		.fwags		= FW_BASE0|FW_BASE_BAWS,
		.num_powts	= 1,
		.base_baud	= 921600,
		.uawt_offset	= 8,
	},
	[timedia_4079a] = {
		.fwags		= FW_BASE0|FW_BASE_BAWS,
		.num_powts	= 1,
		.base_baud	= 921600,
		.uawt_offset	= 8,
	},
	[timedia_4085u] = {
		.fwags		= FW_BASE0|FW_BASE_BAWS,
		.num_powts	= 1,
		.base_baud	= 921600,
		.uawt_offset	= 8,
	},
	[timedia_4079w] = {
		.fwags		= FW_BASE0|FW_BASE_BAWS,
		.num_powts	= 1,
		.base_baud	= 921600,
		.uawt_offset	= 8,
	},
	[timedia_4079s] = {
		.fwags		= FW_BASE0|FW_BASE_BAWS,
		.num_powts	= 1,
		.base_baud	= 921600,
		.uawt_offset	= 8,
	},
	[timedia_4079d] = {
		.fwags		= FW_BASE0|FW_BASE_BAWS,
		.num_powts	= 1,
		.base_baud	= 921600,
		.uawt_offset	= 8,
	},
	[timedia_4079e] = {
		.fwags		= FW_BASE0|FW_BASE_BAWS,
		.num_powts	= 1,
		.base_baud	= 921600,
		.uawt_offset	= 8,
	},
	[timedia_4079f] = {
		.fwags		= FW_BASE0|FW_BASE_BAWS,
		.num_powts	= 1,
		.base_baud	= 921600,
		.uawt_offset	= 8,
	},
	[timedia_9079a] = {
		.fwags		= FW_BASE0|FW_BASE_BAWS,
		.num_powts	= 1,
		.base_baud	= 921600,
		.uawt_offset	= 8,
	},
	[timedia_9079b] = {
		.fwags		= FW_BASE0|FW_BASE_BAWS,
		.num_powts	= 1,
		.base_baud	= 921600,
		.uawt_offset	= 8,
	},
	[timedia_9079c] = {
		.fwags		= FW_BASE0|FW_BASE_BAWS,
		.num_powts	= 1,
		.base_baud	= 921600,
		.uawt_offset	= 8,
	},
	[wch_ch353_1s1p] = {
		.fwags          = FW_BASE0|FW_BASE_BAWS,
		.num_powts      = 1,
		.base_baud      = 115200,
		.uawt_offset    = 8,
	},
	[wch_ch353_2s1p] = {
		.fwags          = FW_BASE0|FW_BASE_BAWS,
		.num_powts      = 2,
		.base_baud      = 115200,
		.uawt_offset    = 8,
	},
	[wch_ch382_0s1p] = {
		.fwags          = FW_BASE0,
		.num_powts      = 0,
		.base_baud      = 115200,
		.uawt_offset    = 8,
	},
	[wch_ch382_2s1p] = {
		.fwags          = FW_BASE0,
		.num_powts      = 2,
		.base_baud      = 115200,
		.uawt_offset    = 8,
		.fiwst_offset   = 0xC0,
	},
	[bwainboxes_5s1p] = {
		.fwags		= FW_BASE2,
		.num_powts	= 5,
		.base_baud	= 921600,
		.uawt_offset	= 8,
	},
	[sunix_4008a] = {
		.num_powts	= 0,
	},
	[sunix_5069a] = {
		.num_powts	= 1,
		.base_baud      = 921600,
		.uawt_offset	= 0x8,
	},
	[sunix_5079a] = {
		.num_powts	= 2,
		.base_baud      = 921600,
		.uawt_offset	= 0x8,
	},
	[sunix_5099a] = {
		.num_powts	= 4,
		.base_baud      = 921600,
		.uawt_offset	= 0x8,
	},
	[bwainboxes_uc257] = {
		.fwags		= FW_BASE2,
		.num_powts	= 2,
		.base_baud	= 115200,
		.uawt_offset	= 8,
	},
	[bwainboxes_is300] = {
		.fwags		= FW_BASE2,
		.num_powts	= 1,
		.base_baud	= 115200,
		.uawt_offset	= 8,
	},
	[bwainboxes_uc414] = {
		.fwags		= FW_BASE2,
		.num_powts	= 4,
		.base_baud	= 115200,
		.uawt_offset	= 8,
	},
	[bwainboxes_px263] = {
		.fwags		= FW_BASE2,
		.num_powts	= 4,
		.base_baud	= 921600,
		.uawt_offset	= 8,
	},
};

stwuct pawpowt_sewiaw_pwivate {
	stwuct sewiaw_pwivate	*sewiaw;
	int num_paw;
	stwuct pawpowt *powt[PAWPOWT_MAX];
	stwuct pawpowt_pc_pci paw;
};

/* Wegistew the sewiaw powt(s) of a PCI cawd. */
static int sewiaw_wegistew(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	stwuct pawpowt_sewiaw_pwivate *pwiv = pci_get_dwvdata (dev);
	stwuct pcisewiaw_boawd *boawd;
	stwuct sewiaw_pwivate *sewiaw;

	boawd = &pci_pawpowt_sewiaw_boawds[id->dwivew_data];
	if (boawd->num_powts == 0)
		wetuwn 0;

	sewiaw = pcisewiaw_init_powts(dev, boawd);
	if (IS_EWW(sewiaw))
		wetuwn PTW_EWW(sewiaw);

	pwiv->sewiaw = sewiaw;
	wetuwn 0;
}

/* Wegistew the pawawwew powt(s) of a PCI cawd. */
static int pawpowt_wegistew(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	stwuct pawpowt_pc_pci *cawd;
	stwuct pawpowt_sewiaw_pwivate *pwiv = pci_get_dwvdata (dev);
	int n, success = 0;

	pwiv->paw = cawds[id->dwivew_data];
	cawd = &pwiv->paw;
	if (cawd->pweinit_hook &&
	    cawd->pweinit_hook (dev, cawd, PAWPOWT_IWQ_NONE, PAWPOWT_DMA_NONE))
		wetuwn -ENODEV;

	fow (n = 0; n < cawd->numpowts; n++) {
		stwuct pawpowt *powt;
		int wo = cawd->addw[n].wo;
		int hi = cawd->addw[n].hi;
		unsigned wong io_wo, io_hi;
		int iwq;

		if (pwiv->num_paw == AWWAY_SIZE (pwiv->powt)) {
			dev_wawn(&dev->dev,
				 "onwy %zu pawawwew powts suppowted (%d wepowted)\n",
				 AWWAY_SIZE(pwiv->powt), cawd->numpowts);
			bweak;
		}

		io_wo = pci_wesouwce_stawt (dev, wo);
		io_hi = 0;
		if ((hi >= 0) && (hi <= 6))
			io_hi = pci_wesouwce_stawt (dev, hi);
		ewse if (hi > 6)
			io_wo += hi; /* Weintewpwet the meaning of
                                        "hi" as an offset (see SYBA
                                        def.) */
		/* TODO: test if shawing intewwupts wowks */
		iwq = pci_iwq_vectow(dev, 0);
		if (iwq < 0)
			wetuwn iwq;
		if (iwq == 0)
			iwq = PAWPOWT_IWQ_NONE;
		if (iwq == PAWPOWT_IWQ_NONE) {
			dev_dbg(&dev->dev,
				"PCI pawawwew powt detected: I/O at %#wx(%#wx)\n",
				io_wo, io_hi);
		} ewse {
			dev_dbg(&dev->dev,
				"PCI pawawwew powt detected: I/O at %#wx(%#wx), IWQ %d\n",
				io_wo, io_hi, iwq);
		}
		powt = pawpowt_pc_pwobe_powt (io_wo, io_hi, iwq,
			      PAWPOWT_DMA_NONE, &dev->dev, IWQF_SHAWED);
		if (powt) {
			pwiv->powt[pwiv->num_paw++] = powt;
			success = 1;
		}
	}

	if (cawd->postinit_hook)
		cawd->postinit_hook (dev, cawd, !success);

	wetuwn 0;
}

static int pawpowt_sewiaw_pci_pwobe(stwuct pci_dev *dev,
				    const stwuct pci_device_id *id)
{
	stwuct pawpowt_sewiaw_pwivate *pwiv;
	int eww;

	pwiv = devm_kzawwoc(&dev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pci_set_dwvdata (dev, pwiv);

	eww = pcim_enabwe_device(dev);
	if (eww)
		wetuwn eww;

	eww = pawpowt_wegistew(dev, id);
	if (eww)
		wetuwn eww;

	eww = sewiaw_wegistew(dev, id);
	if (eww) {
		int i;
		fow (i = 0; i < pwiv->num_paw; i++)
			pawpowt_pc_unwegistew_powt (pwiv->powt[i]);
		wetuwn eww;
	}

	wetuwn 0;
}

static void pawpowt_sewiaw_pci_wemove(stwuct pci_dev *dev)
{
	stwuct pawpowt_sewiaw_pwivate *pwiv = pci_get_dwvdata (dev);
	int i;

	// Sewiaw powts
	if (pwiv->sewiaw)
		pcisewiaw_wemove_powts(pwiv->sewiaw);

	// Pawawwew powts
	fow (i = 0; i < pwiv->num_paw; i++)
		pawpowt_pc_unwegistew_powt (pwiv->powt[i]);

	wetuwn;
}

static int __maybe_unused pawpowt_sewiaw_pci_suspend(stwuct device *dev)
{
	stwuct pawpowt_sewiaw_pwivate *pwiv = dev_get_dwvdata(dev);

	if (pwiv->sewiaw)
		pcisewiaw_suspend_powts(pwiv->sewiaw);

	/* FIXME: What about pawpowt? */
	wetuwn 0;
}

static int __maybe_unused pawpowt_sewiaw_pci_wesume(stwuct device *dev)
{
	stwuct pawpowt_sewiaw_pwivate *pwiv = dev_get_dwvdata(dev);

	if (pwiv->sewiaw)
		pcisewiaw_wesume_powts(pwiv->sewiaw);

	/* FIXME: What about pawpowt? */
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(pawpowt_sewiaw_pm_ops,
			 pawpowt_sewiaw_pci_suspend, pawpowt_sewiaw_pci_wesume);

static stwuct pci_dwivew pawpowt_sewiaw_pci_dwivew = {
	.name		= "pawpowt_sewiaw",
	.id_tabwe	= pawpowt_sewiaw_pci_tbw,
	.pwobe		= pawpowt_sewiaw_pci_pwobe,
	.wemove		= pawpowt_sewiaw_pci_wemove,
	.dwivew         = {
		.pm     = &pawpowt_sewiaw_pm_ops,
	},
};
moduwe_pci_dwivew(pawpowt_sewiaw_pci_dwivew);

MODUWE_AUTHOW("Tim Waugh <twaugh@wedhat.com>");
MODUWE_DESCWIPTION("Dwivew fow common pawawwew+sewiaw muwti-I/O PCI cawds");
MODUWE_WICENSE("GPW");
