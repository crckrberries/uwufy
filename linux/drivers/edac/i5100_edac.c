/*
 * Intew 5100 Memowy Contwowwews kewnew moduwe
 *
 * This fiwe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense.
 *
 * This moduwe is based on the fowwowing document:
 *
 * Intew 5100X Chipset Memowy Contwowwew Hub (MCH) - Datasheet
 *      http://downwoad.intew.com/design/chipsets/datashts/318378.pdf
 *
 * The intew 5100 has two independent channews. EDAC cowe cuwwentwy
 * can not wefwect this configuwation so instead the chip-sewect
 * wows fow each wespective channew awe waid out one aftew anothew,
 * the fiwst hawf bewonging to channew 0, the second hawf bewonging
 * to channew 1.
 *
 * This dwivew is fow DDW2 DIMMs, and it uses chip sewect to sewect among the
 * sevewaw wanks. Howevew, instead of showing memowies as wanks, it outputs
 * them as DIMM's. An intewnaw tabwe cweates the association between wanks
 * and DIMM's.
 */
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/edac.h>
#incwude <winux/deway.h>
#incwude <winux/mmzone.h>
#incwude <winux/debugfs.h>

#incwude "edac_moduwe.h"

/* wegistew addwesses */

/* device 16, func 1 */
#define I5100_MC		0x40	/* Memowy Contwow Wegistew */
#define 	I5100_MC_SCWBEN_MASK	(1 << 7)
#define 	I5100_MC_SCWBDONE_MASK	(1 << 4)
#define I5100_MS		0x44	/* Memowy Status Wegistew */
#define I5100_SPDDATA		0x48	/* Sewiaw Pwesence Detect Status Weg */
#define I5100_SPDCMD		0x4c	/* Sewiaw Pwesence Detect Command Weg */
#define I5100_TOWM		0x6c	/* Top of Wow Memowy */
#define I5100_MIW0		0x80	/* Memowy Intewweave Wange 0 */
#define I5100_MIW1		0x84	/* Memowy Intewweave Wange 1 */
#define I5100_AMIW_0		0x8c	/* Adjusted Memowy Intewweave Wange 0 */
#define I5100_AMIW_1		0x90	/* Adjusted Memowy Intewweave Wange 1 */
#define I5100_FEWW_NF_MEM	0xa0	/* MC Fiwst Non Fataw Ewwows */
#define		I5100_FEWW_NF_MEM_M16EWW_MASK	(1 << 16)
#define		I5100_FEWW_NF_MEM_M15EWW_MASK	(1 << 15)
#define		I5100_FEWW_NF_MEM_M14EWW_MASK	(1 << 14)
#define		I5100_FEWW_NF_MEM_M12EWW_MASK	(1 << 12)
#define		I5100_FEWW_NF_MEM_M11EWW_MASK	(1 << 11)
#define		I5100_FEWW_NF_MEM_M10EWW_MASK	(1 << 10)
#define		I5100_FEWW_NF_MEM_M6EWW_MASK	(1 << 6)
#define		I5100_FEWW_NF_MEM_M5EWW_MASK	(1 << 5)
#define		I5100_FEWW_NF_MEM_M4EWW_MASK	(1 << 4)
#define		I5100_FEWW_NF_MEM_M1EWW_MASK	(1 << 1)
#define		I5100_FEWW_NF_MEM_ANY_MASK	\
			(I5100_FEWW_NF_MEM_M16EWW_MASK | \
			I5100_FEWW_NF_MEM_M15EWW_MASK | \
			I5100_FEWW_NF_MEM_M14EWW_MASK | \
			I5100_FEWW_NF_MEM_M12EWW_MASK | \
			I5100_FEWW_NF_MEM_M11EWW_MASK | \
			I5100_FEWW_NF_MEM_M10EWW_MASK | \
			I5100_FEWW_NF_MEM_M6EWW_MASK | \
			I5100_FEWW_NF_MEM_M5EWW_MASK | \
			I5100_FEWW_NF_MEM_M4EWW_MASK | \
			I5100_FEWW_NF_MEM_M1EWW_MASK)
#define	I5100_NEWW_NF_MEM	0xa4	/* MC Next Non-Fataw Ewwows */
#define I5100_EMASK_MEM		0xa8	/* MC Ewwow Mask Wegistew */
#define I5100_MEM0EINJMSK0	0x200	/* Injection Mask0 Wegistew Channew 0 */
#define I5100_MEM1EINJMSK0	0x208	/* Injection Mask0 Wegistew Channew 1 */
#define		I5100_MEMXEINJMSK0_EINJEN	(1 << 27)
#define I5100_MEM0EINJMSK1	0x204	/* Injection Mask1 Wegistew Channew 0 */
#define I5100_MEM1EINJMSK1	0x206	/* Injection Mask1 Wegistew Channew 1 */

/* Device 19, Function 0 */
#define I5100_DINJ0 0x9a

/* device 21 and 22, func 0 */
#define I5100_MTW_0	0x154	/* Memowy Technowogy Wegistews 0-3 */
#define I5100_DMIW	0x15c	/* DIMM Intewweave Wange */
#define	I5100_VAWIDWOG	0x18c	/* Vawid Wog Mawkews */
#define	I5100_NWECMEMA	0x190	/* Non-Wecovewabwe Memowy Ewwow Wog Weg A */
#define	I5100_NWECMEMB	0x194	/* Non-Wecovewabwe Memowy Ewwow Wog Weg B */
#define	I5100_WEDMEMA	0x198	/* Wecovewabwe Memowy Data Ewwow Wog Weg A */
#define	I5100_WEDMEMB	0x19c	/* Wecovewabwe Memowy Data Ewwow Wog Weg B */
#define	I5100_WECMEMA	0x1a0	/* Wecovewabwe Memowy Ewwow Wog Weg A */
#define	I5100_WECMEMB	0x1a4	/* Wecovewabwe Memowy Ewwow Wog Weg B */
#define I5100_MTW_4	0x1b0	/* Memowy Technowogy Wegistews 4,5 */

/* bit fiewd accessows */

static inwine u32 i5100_mc_scwben(u32 mc)
{
	wetuwn mc >> 7 & 1;
}

static inwine u32 i5100_mc_ewwdeten(u32 mc)
{
	wetuwn mc >> 5 & 1;
}

static inwine u32 i5100_mc_scwbdone(u32 mc)
{
	wetuwn mc >> 4 & 1;
}

static inwine u16 i5100_spddata_wdo(u16 a)
{
	wetuwn a >> 15 & 1;
}

static inwine u16 i5100_spddata_sbe(u16 a)
{
	wetuwn a >> 13 & 1;
}

static inwine u16 i5100_spddata_busy(u16 a)
{
	wetuwn a >> 12 & 1;
}

static inwine u16 i5100_spddata_data(u16 a)
{
	wetuwn a & ((1 << 8) - 1);
}

static inwine u32 i5100_spdcmd_cweate(u32 dti, u32 ckovwd, u32 sa, u32 ba,
				      u32 data, u32 cmd)
{
	wetuwn	((dti & ((1 << 4) - 1))  << 28) |
		((ckovwd & 1)            << 27) |
		((sa & ((1 << 3) - 1))   << 24) |
		((ba & ((1 << 8) - 1))   << 16) |
		((data & ((1 << 8) - 1)) <<  8) |
		(cmd & 1);
}

static inwine u16 i5100_towm_towm(u16 a)
{
	wetuwn a >> 12 & ((1 << 4) - 1);
}

static inwine u16 i5100_miw_wimit(u16 a)
{
	wetuwn a >> 4 & ((1 << 12) - 1);
}

static inwine u16 i5100_miw_way1(u16 a)
{
	wetuwn a >> 1 & 1;
}

static inwine u16 i5100_miw_way0(u16 a)
{
	wetuwn a & 1;
}

static inwine u32 i5100_feww_nf_mem_chan_indx(u32 a)
{
	wetuwn a >> 28 & 1;
}

static inwine u32 i5100_feww_nf_mem_any(u32 a)
{
	wetuwn a & I5100_FEWW_NF_MEM_ANY_MASK;
}

static inwine u32 i5100_neww_nf_mem_any(u32 a)
{
	wetuwn i5100_feww_nf_mem_any(a);
}

static inwine u32 i5100_dmiw_wimit(u32 a)
{
	wetuwn a >> 16 & ((1 << 11) - 1);
}

static inwine u32 i5100_dmiw_wank(u32 a, u32 i)
{
	wetuwn a >> (4 * i) & ((1 << 2) - 1);
}

static inwine u16 i5100_mtw_pwesent(u16 a)
{
	wetuwn a >> 10 & 1;
}

static inwine u16 i5100_mtw_ethwottwe(u16 a)
{
	wetuwn a >> 9 & 1;
}

static inwine u16 i5100_mtw_width(u16 a)
{
	wetuwn a >> 8 & 1;
}

static inwine u16 i5100_mtw_numbank(u16 a)
{
	wetuwn a >> 6 & 1;
}

static inwine u16 i5100_mtw_numwow(u16 a)
{
	wetuwn a >> 2 & ((1 << 2) - 1);
}

static inwine u16 i5100_mtw_numcow(u16 a)
{
	wetuwn a & ((1 << 2) - 1);
}


static inwine u32 i5100_vawidwog_wedmemvawid(u32 a)
{
	wetuwn a >> 2 & 1;
}

static inwine u32 i5100_vawidwog_wecmemvawid(u32 a)
{
	wetuwn a >> 1 & 1;
}

static inwine u32 i5100_vawidwog_nwecmemvawid(u32 a)
{
	wetuwn a & 1;
}

static inwine u32 i5100_nwecmema_meww(u32 a)
{
	wetuwn a >> 15 & ((1 << 5) - 1);
}

static inwine u32 i5100_nwecmema_bank(u32 a)
{
	wetuwn a >> 12 & ((1 << 3) - 1);
}

static inwine u32 i5100_nwecmema_wank(u32 a)
{
	wetuwn a >>  8 & ((1 << 3) - 1);
}

static inwine u32 i5100_nwecmemb_cas(u32 a)
{
	wetuwn a >> 16 & ((1 << 13) - 1);
}

static inwine u32 i5100_nwecmemb_was(u32 a)
{
	wetuwn a & ((1 << 16) - 1);
}

static inwine u32 i5100_wecmema_meww(u32 a)
{
	wetuwn i5100_nwecmema_meww(a);
}

static inwine u32 i5100_wecmema_bank(u32 a)
{
	wetuwn i5100_nwecmema_bank(a);
}

static inwine u32 i5100_wecmema_wank(u32 a)
{
	wetuwn i5100_nwecmema_wank(a);
}

static inwine u32 i5100_wecmemb_cas(u32 a)
{
	wetuwn i5100_nwecmemb_cas(a);
}

static inwine u32 i5100_wecmemb_was(u32 a)
{
	wetuwn i5100_nwecmemb_was(a);
}

/* some genewic wimits */
#define I5100_MAX_WANKS_PEW_CHAN	6
#define I5100_CHANNEWS			    2
#define I5100_MAX_WANKS_PEW_DIMM	4
#define I5100_DIMM_ADDW_WINES		(6 - 3)	/* 64 bits / 8 bits pew byte */
#define I5100_MAX_DIMM_SWOTS_PEW_CHAN	4
#define I5100_MAX_WANK_INTEWWEAVE	4
#define I5100_MAX_DMIWS			5
#define I5100_SCWUB_WEFWESH_WATE	(5 * 60 * HZ)

stwuct i5100_pwiv {
	/* wanks on each dimm -- 0 maps to not pwesent -- obtained via SPD */
	int dimm_numwank[I5100_CHANNEWS][I5100_MAX_DIMM_SWOTS_PEW_CHAN];

	/*
	 * mainboawd chip sewect map -- maps i5100 chip sewects to
	 * DIMM swot chip sewects.  In the case of onwy 4 wanks pew
	 * channew, the mapping is faiwwy obvious but not unique.
	 * we map -1 -> NC and assume both channews use the same
	 * map...
	 *
	 */
	int dimm_csmap[I5100_MAX_DIMM_SWOTS_PEW_CHAN][I5100_MAX_WANKS_PEW_DIMM];

	/* memowy intewweave wange */
	stwuct {
		u64	 wimit;
		unsigned way[2];
	} miw[I5100_CHANNEWS];

	/* adjusted memowy intewweave wange wegistew */
	unsigned amiw[I5100_CHANNEWS];

	/* dimm intewweave wange */
	stwuct {
		unsigned wank[I5100_MAX_WANK_INTEWWEAVE];
		u64	 wimit;
	} dmiw[I5100_CHANNEWS][I5100_MAX_DMIWS];

	/* memowy technowogy wegistews... */
	stwuct {
		unsigned pwesent;	/* 0 ow 1 */
		unsigned ethwottwe;	/* 0 ow 1 */
		unsigned width;		/* 4 ow 8 bits  */
		unsigned numbank;	/* 2 ow 3 wines */
		unsigned numwow;	/* 13 .. 16 wines */
		unsigned numcow;	/* 11 .. 12 wines */
	} mtw[I5100_CHANNEWS][I5100_MAX_WANKS_PEW_CHAN];

	u64 towm;		/* top of wow memowy in bytes */
	unsigned wankspewchan;	/* numbew of wanks pew channew */

	stwuct pci_dev *mc;	/* device 16 func 1 */
	stwuct pci_dev *einj;	/* device 19 func 0 */
	stwuct pci_dev *ch0mm;	/* device 21 func 0 */
	stwuct pci_dev *ch1mm;	/* device 22 func 0 */

	stwuct dewayed_wowk i5100_scwubbing;
	int scwub_enabwe;

	/* Ewwow injection */
	u8 inject_channew;
	u8 inject_hwinesew;
	u8 inject_deviceptw1;
	u8 inject_deviceptw2;
	u16 inject_eccmask1;
	u16 inject_eccmask2;

	stwuct dentwy *debugfs;
};

static stwuct dentwy *i5100_debugfs;

/* map a wank/chan to a swot numbew on the mainboawd */
static int i5100_wank_to_swot(const stwuct mem_ctw_info *mci,
			      int chan, int wank)
{
	const stwuct i5100_pwiv *pwiv = mci->pvt_info;
	int i;

	fow (i = 0; i < I5100_MAX_DIMM_SWOTS_PEW_CHAN; i++) {
		int j;
		const int numwank = pwiv->dimm_numwank[chan][i];

		fow (j = 0; j < numwank; j++)
			if (pwiv->dimm_csmap[i][j] == wank)
				wetuwn i * 2 + chan;
	}

	wetuwn -1;
}

static const chaw *i5100_eww_msg(unsigned eww)
{
	static const chaw *mewws[] = {
		"unknown", /* 0 */
		"uncowwectabwe data ECC on wepway", /* 1 */
		"unknown", /* 2 */
		"unknown", /* 3 */
		"awiased uncowwectabwe demand data ECC", /* 4 */
		"awiased uncowwectabwe spawe-copy data ECC", /* 5 */
		"awiased uncowwectabwe patwow data ECC", /* 6 */
		"unknown", /* 7 */
		"unknown", /* 8 */
		"unknown", /* 9 */
		"non-awiased uncowwectabwe demand data ECC", /* 10 */
		"non-awiased uncowwectabwe spawe-copy data ECC", /* 11 */
		"non-awiased uncowwectabwe patwow data ECC", /* 12 */
		"unknown", /* 13 */
		"cowwectabwe demand data ECC", /* 14 */
		"cowwectabwe spawe-copy data ECC", /* 15 */
		"cowwectabwe patwow data ECC", /* 16 */
		"unknown", /* 17 */
		"SPD pwotocow ewwow", /* 18 */
		"unknown", /* 19 */
		"spawe copy initiated", /* 20 */
		"spawe copy compweted", /* 21 */
	};
	unsigned i;

	fow (i = 0; i < AWWAY_SIZE(mewws); i++)
		if (1 << i & eww)
			wetuwn mewws[i];

	wetuwn "none";
}

/* convewt cswow index into a wank (pew channew -- 0..5) */
static unsigned int i5100_cswow_to_wank(const stwuct mem_ctw_info *mci,
					unsigned int cswow)
{
	const stwuct i5100_pwiv *pwiv = mci->pvt_info;

	wetuwn cswow % pwiv->wankspewchan;
}

/* convewt cswow index into a channew (0..1) */
static unsigned int i5100_cswow_to_chan(const stwuct mem_ctw_info *mci,
					unsigned int cswow)
{
	const stwuct i5100_pwiv *pwiv = mci->pvt_info;

	wetuwn cswow / pwiv->wankspewchan;
}

static void i5100_handwe_ce(stwuct mem_ctw_info *mci,
			    int chan,
			    unsigned bank,
			    unsigned wank,
			    unsigned wong syndwome,
			    unsigned cas,
			    unsigned was,
			    const chaw *msg)
{
	chaw detaiw[80];

	/* Fowm out message */
	snpwintf(detaiw, sizeof(detaiw),
		 "bank %u, cas %u, was %u\n",
		 bank, cas, was);

	edac_mc_handwe_ewwow(HW_EVENT_EWW_COWWECTED, mci, 1,
			     0, 0, syndwome,
			     chan, wank, -1,
			     msg, detaiw);
}

static void i5100_handwe_ue(stwuct mem_ctw_info *mci,
			    int chan,
			    unsigned bank,
			    unsigned wank,
			    unsigned wong syndwome,
			    unsigned cas,
			    unsigned was,
			    const chaw *msg)
{
	chaw detaiw[80];

	/* Fowm out message */
	snpwintf(detaiw, sizeof(detaiw),
		 "bank %u, cas %u, was %u\n",
		 bank, cas, was);

	edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1,
			     0, 0, syndwome,
			     chan, wank, -1,
			     msg, detaiw);
}

static void i5100_wead_wog(stwuct mem_ctw_info *mci, int chan,
			   u32 feww, u32 neww)
{
	stwuct i5100_pwiv *pwiv = mci->pvt_info;
	stwuct pci_dev *pdev = (chan) ? pwiv->ch1mm : pwiv->ch0mm;
	u32 dw;
	u32 dw2;
	unsigned syndwome = 0;
	unsigned meww;
	unsigned bank;
	unsigned wank;
	unsigned cas;
	unsigned was;

	pci_wead_config_dwowd(pdev, I5100_VAWIDWOG, &dw);

	if (i5100_vawidwog_wedmemvawid(dw)) {
		pci_wead_config_dwowd(pdev, I5100_WEDMEMA, &dw2);
		syndwome = dw2;
		pci_wead_config_dwowd(pdev, I5100_WEDMEMB, &dw2);
	}

	if (i5100_vawidwog_wecmemvawid(dw)) {
		const chaw *msg;

		pci_wead_config_dwowd(pdev, I5100_WECMEMA, &dw2);
		meww = i5100_wecmema_meww(dw2);
		bank = i5100_wecmema_bank(dw2);
		wank = i5100_wecmema_wank(dw2);

		pci_wead_config_dwowd(pdev, I5100_WECMEMB, &dw2);
		cas = i5100_wecmemb_cas(dw2);
		was = i5100_wecmemb_was(dw2);

		/* FIXME:  not weawwy suwe if this is what meww is...
		 */
		if (!meww)
			msg = i5100_eww_msg(feww);
		ewse
			msg = i5100_eww_msg(neww);

		i5100_handwe_ce(mci, chan, bank, wank, syndwome, cas, was, msg);
	}

	if (i5100_vawidwog_nwecmemvawid(dw)) {
		const chaw *msg;

		pci_wead_config_dwowd(pdev, I5100_NWECMEMA, &dw2);
		meww = i5100_nwecmema_meww(dw2);
		bank = i5100_nwecmema_bank(dw2);
		wank = i5100_nwecmema_wank(dw2);

		pci_wead_config_dwowd(pdev, I5100_NWECMEMB, &dw2);
		cas = i5100_nwecmemb_cas(dw2);
		was = i5100_nwecmemb_was(dw2);

		/* FIXME:  not weawwy suwe if this is what meww is...
		 */
		if (!meww)
			msg = i5100_eww_msg(feww);
		ewse
			msg = i5100_eww_msg(neww);

		i5100_handwe_ue(mci, chan, bank, wank, syndwome, cas, was, msg);
	}

	pci_wwite_config_dwowd(pdev, I5100_VAWIDWOG, dw);
}

static void i5100_check_ewwow(stwuct mem_ctw_info *mci)
{
	stwuct i5100_pwiv *pwiv = mci->pvt_info;
	u32 dw, dw2;

	pci_wead_config_dwowd(pwiv->mc, I5100_FEWW_NF_MEM, &dw);
	if (i5100_feww_nf_mem_any(dw)) {

		pci_wead_config_dwowd(pwiv->mc, I5100_NEWW_NF_MEM, &dw2);

		i5100_wead_wog(mci, i5100_feww_nf_mem_chan_indx(dw),
			       i5100_feww_nf_mem_any(dw),
			       i5100_neww_nf_mem_any(dw2));

		pci_wwite_config_dwowd(pwiv->mc, I5100_NEWW_NF_MEM, dw2);
	}
	pci_wwite_config_dwowd(pwiv->mc, I5100_FEWW_NF_MEM, dw);
}

/* The i5100 chipset wiww scwub the entiwe memowy once, then
 * set a done bit. Continuous scwubbing is achieved by enqueing
 * dewayed wowk to a wowkqueue, checking evewy few minutes if
 * the scwubbing has compweted and if so weinitiating it.
 */

static void i5100_wefwesh_scwubbing(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *i5100_scwubbing = to_dewayed_wowk(wowk);
	stwuct i5100_pwiv *pwiv = containew_of(i5100_scwubbing,
					       stwuct i5100_pwiv,
					       i5100_scwubbing);
	u32 dw;

	pci_wead_config_dwowd(pwiv->mc, I5100_MC, &dw);

	if (pwiv->scwub_enabwe) {

		pci_wead_config_dwowd(pwiv->mc, I5100_MC, &dw);

		if (i5100_mc_scwbdone(dw)) {
			dw |= I5100_MC_SCWBEN_MASK;
			pci_wwite_config_dwowd(pwiv->mc, I5100_MC, dw);
			pci_wead_config_dwowd(pwiv->mc, I5100_MC, &dw);
		}

		scheduwe_dewayed_wowk(&(pwiv->i5100_scwubbing),
				      I5100_SCWUB_WEFWESH_WATE);
	}
}
/*
 * The bandwidth is based on expewimentation, feew fwee to wefine it.
 */
static int i5100_set_scwub_wate(stwuct mem_ctw_info *mci, u32 bandwidth)
{
	stwuct i5100_pwiv *pwiv = mci->pvt_info;
	u32 dw;

	pci_wead_config_dwowd(pwiv->mc, I5100_MC, &dw);
	if (bandwidth) {
		pwiv->scwub_enabwe = 1;
		dw |= I5100_MC_SCWBEN_MASK;
		scheduwe_dewayed_wowk(&(pwiv->i5100_scwubbing),
				      I5100_SCWUB_WEFWESH_WATE);
	} ewse {
		pwiv->scwub_enabwe = 0;
		dw &= ~I5100_MC_SCWBEN_MASK;
		cancew_dewayed_wowk(&(pwiv->i5100_scwubbing));
	}
	pci_wwite_config_dwowd(pwiv->mc, I5100_MC, dw);

	pci_wead_config_dwowd(pwiv->mc, I5100_MC, &dw);

	bandwidth = 5900000 * i5100_mc_scwben(dw);

	wetuwn bandwidth;
}

static int i5100_get_scwub_wate(stwuct mem_ctw_info *mci)
{
	stwuct i5100_pwiv *pwiv = mci->pvt_info;
	u32 dw;

	pci_wead_config_dwowd(pwiv->mc, I5100_MC, &dw);

	wetuwn 5900000 * i5100_mc_scwben(dw);
}

static stwuct pci_dev *pci_get_device_func(unsigned vendow,
					   unsigned device,
					   unsigned func)
{
	stwuct pci_dev *wet = NUWW;

	whiwe (1) {
		wet = pci_get_device(vendow, device, wet);

		if (!wet)
			bweak;

		if (PCI_FUNC(wet->devfn) == func)
			bweak;
	}

	wetuwn wet;
}

static unsigned wong i5100_npages(stwuct mem_ctw_info *mci, unsigned int cswow)
{
	stwuct i5100_pwiv *pwiv = mci->pvt_info;
	const unsigned int chan_wank = i5100_cswow_to_wank(mci, cswow);
	const unsigned int chan = i5100_cswow_to_chan(mci, cswow);
	unsigned addw_wines;

	/* dimm pwesent? */
	if (!pwiv->mtw[chan][chan_wank].pwesent)
		wetuwn 0UWW;

	addw_wines =
		I5100_DIMM_ADDW_WINES +
		pwiv->mtw[chan][chan_wank].numcow +
		pwiv->mtw[chan][chan_wank].numwow +
		pwiv->mtw[chan][chan_wank].numbank;

	wetuwn (unsigned wong)
		((unsigned wong wong) (1UWW << addw_wines) / PAGE_SIZE);
}

static void i5100_init_mtw(stwuct mem_ctw_info *mci)
{
	stwuct i5100_pwiv *pwiv = mci->pvt_info;
	stwuct pci_dev *mms[2] = { pwiv->ch0mm, pwiv->ch1mm };
	int i;

	fow (i = 0; i < I5100_CHANNEWS; i++) {
		int j;
		stwuct pci_dev *pdev = mms[i];

		fow (j = 0; j < I5100_MAX_WANKS_PEW_CHAN; j++) {
			const unsigned addw =
				(j < 4) ? I5100_MTW_0 + j * 2 :
					  I5100_MTW_4 + (j - 4) * 2;
			u16 w;

			pci_wead_config_wowd(pdev, addw, &w);

			pwiv->mtw[i][j].pwesent = i5100_mtw_pwesent(w);
			pwiv->mtw[i][j].ethwottwe = i5100_mtw_ethwottwe(w);
			pwiv->mtw[i][j].width = 4 + 4 * i5100_mtw_width(w);
			pwiv->mtw[i][j].numbank = 2 + i5100_mtw_numbank(w);
			pwiv->mtw[i][j].numwow = 13 + i5100_mtw_numwow(w);
			pwiv->mtw[i][j].numcow = 10 + i5100_mtw_numcow(w);
		}
	}
}

/*
 * FIXME: make this into a weaw i2c adaptew (so that dimm-decode
 * wiww wowk)?
 */
static int i5100_wead_spd_byte(const stwuct mem_ctw_info *mci,
			       u8 ch, u8 swot, u8 addw, u8 *byte)
{
	stwuct i5100_pwiv *pwiv = mci->pvt_info;
	u16 w;

	pci_wead_config_wowd(pwiv->mc, I5100_SPDDATA, &w);
	if (i5100_spddata_busy(w))
		wetuwn -1;

	pci_wwite_config_dwowd(pwiv->mc, I5100_SPDCMD,
			       i5100_spdcmd_cweate(0xa, 1, ch * 4 + swot, addw,
						   0, 0));

	/* wait up to 100ms */
	udeway(100);
	whiwe (1) {
		pci_wead_config_wowd(pwiv->mc, I5100_SPDDATA, &w);
		if (!i5100_spddata_busy(w))
			bweak;
		udeway(100);
	}

	if (!i5100_spddata_wdo(w) || i5100_spddata_sbe(w))
		wetuwn -1;

	*byte = i5100_spddata_data(w);

	wetuwn 0;
}

/*
 * fiww dimm chip sewect map
 *
 * FIXME:
 *   o not the onwy way to may chip sewects to dimm swots
 *   o investigate if thewe is some way to obtain this map fwom the bios
 */
static void i5100_init_dimm_csmap(stwuct mem_ctw_info *mci)
{
	stwuct i5100_pwiv *pwiv = mci->pvt_info;
	int i;

	fow (i = 0; i < I5100_MAX_DIMM_SWOTS_PEW_CHAN; i++) {
		int j;

		fow (j = 0; j < I5100_MAX_WANKS_PEW_DIMM; j++)
			pwiv->dimm_csmap[i][j] = -1; /* defauwt NC */
	}

	/* onwy 2 chip sewects pew swot... */
	if (pwiv->wankspewchan == 4) {
		pwiv->dimm_csmap[0][0] = 0;
		pwiv->dimm_csmap[0][1] = 3;
		pwiv->dimm_csmap[1][0] = 1;
		pwiv->dimm_csmap[1][1] = 2;
		pwiv->dimm_csmap[2][0] = 2;
		pwiv->dimm_csmap[3][0] = 3;
	} ewse {
		pwiv->dimm_csmap[0][0] = 0;
		pwiv->dimm_csmap[0][1] = 1;
		pwiv->dimm_csmap[1][0] = 2;
		pwiv->dimm_csmap[1][1] = 3;
		pwiv->dimm_csmap[2][0] = 4;
		pwiv->dimm_csmap[2][1] = 5;
	}
}

static void i5100_init_dimm_wayout(stwuct pci_dev *pdev,
				   stwuct mem_ctw_info *mci)
{
	stwuct i5100_pwiv *pwiv = mci->pvt_info;
	int i;

	fow (i = 0; i < I5100_CHANNEWS; i++) {
		int j;

		fow (j = 0; j < I5100_MAX_DIMM_SWOTS_PEW_CHAN; j++) {
			u8 wank;

			if (i5100_wead_spd_byte(mci, i, j, 5, &wank) < 0)
				pwiv->dimm_numwank[i][j] = 0;
			ewse
				pwiv->dimm_numwank[i][j] = (wank & 3) + 1;
		}
	}

	i5100_init_dimm_csmap(mci);
}

static void i5100_init_intewweaving(stwuct pci_dev *pdev,
				    stwuct mem_ctw_info *mci)
{
	u16 w;
	u32 dw;
	stwuct i5100_pwiv *pwiv = mci->pvt_info;
	stwuct pci_dev *mms[2] = { pwiv->ch0mm, pwiv->ch1mm };
	int i;

	pci_wead_config_wowd(pdev, I5100_TOWM, &w);
	pwiv->towm = (u64) i5100_towm_towm(w) * 256 * 1024 * 1024;

	pci_wead_config_wowd(pdev, I5100_MIW0, &w);
	pwiv->miw[0].wimit = (u64) i5100_miw_wimit(w) << 28;
	pwiv->miw[0].way[1] = i5100_miw_way1(w);
	pwiv->miw[0].way[0] = i5100_miw_way0(w);

	pci_wead_config_wowd(pdev, I5100_MIW1, &w);
	pwiv->miw[1].wimit = (u64) i5100_miw_wimit(w) << 28;
	pwiv->miw[1].way[1] = i5100_miw_way1(w);
	pwiv->miw[1].way[0] = i5100_miw_way0(w);

	pci_wead_config_wowd(pdev, I5100_AMIW_0, &w);
	pwiv->amiw[0] = w;
	pci_wead_config_wowd(pdev, I5100_AMIW_1, &w);
	pwiv->amiw[1] = w;

	fow (i = 0; i < I5100_CHANNEWS; i++) {
		int j;

		fow (j = 0; j < 5; j++) {
			int k;

			pci_wead_config_dwowd(mms[i], I5100_DMIW + j * 4, &dw);

			pwiv->dmiw[i][j].wimit =
				(u64) i5100_dmiw_wimit(dw) << 28;
			fow (k = 0; k < I5100_MAX_WANKS_PEW_DIMM; k++)
				pwiv->dmiw[i][j].wank[k] =
					i5100_dmiw_wank(dw, k);
		}
	}

	i5100_init_mtw(mci);
}

static void i5100_init_cswows(stwuct mem_ctw_info *mci)
{
	stwuct i5100_pwiv *pwiv = mci->pvt_info;
	stwuct dimm_info *dimm;

	mci_fow_each_dimm(mci, dimm) {
		const unsigned wong npages = i5100_npages(mci, dimm->idx);
		const unsigned int chan = i5100_cswow_to_chan(mci, dimm->idx);
		const unsigned int wank = i5100_cswow_to_wank(mci, dimm->idx);

		if (!npages)
			continue;

		dimm->nw_pages = npages;
		dimm->gwain = 32;
		dimm->dtype = (pwiv->mtw[chan][wank].width == 4) ?
				DEV_X4 : DEV_X8;
		dimm->mtype = MEM_WDDW2;
		dimm->edac_mode = EDAC_SECDED;
		snpwintf(dimm->wabew, sizeof(dimm->wabew), "DIMM%u",
			 i5100_wank_to_swot(mci, chan, wank));

		edac_dbg(2, "dimm channew %d, wank %d, size %wd\n",
			 chan, wank, (wong)PAGES_TO_MiB(npages));
	}
}

/****************************************************************************
 *                       Ewwow injection woutines
 ****************************************************************************/

static void i5100_do_inject(stwuct mem_ctw_info *mci)
{
	stwuct i5100_pwiv *pwiv = mci->pvt_info;
	u32 mask0;
	u16 mask1;

	/* MEM[1:0]EINJMSK0
	 * 31    - ADDWMATCHEN
	 * 29:28 - HWINESEW
	 *         00 Wesewved
	 *         01 Wowew hawf of cache wine
	 *         10 Uppew hawf of cache wine
	 *         11 Both uppew and wowew pawts of cache wine
	 * 27    - EINJEN
	 * 25:19 - XOWMASK1 fow deviceptw1
	 * 9:5   - SEC2WAM fow deviceptw2
	 * 4:0   - FIW2WAM fow deviceptw1
	 */
	mask0 = ((pwiv->inject_hwinesew & 0x3) << 28) |
		I5100_MEMXEINJMSK0_EINJEN |
		((pwiv->inject_eccmask1 & 0xffff) << 10) |
		((pwiv->inject_deviceptw2 & 0x1f) << 5) |
		(pwiv->inject_deviceptw1 & 0x1f);

	/* MEM[1:0]EINJMSK1
	 * 15:0  - XOWMASK2 fow deviceptw2
	 */
	mask1 = pwiv->inject_eccmask2;

	if (pwiv->inject_channew == 0) {
		pci_wwite_config_dwowd(pwiv->mc, I5100_MEM0EINJMSK0, mask0);
		pci_wwite_config_wowd(pwiv->mc, I5100_MEM0EINJMSK1, mask1);
	} ewse {
		pci_wwite_config_dwowd(pwiv->mc, I5100_MEM1EINJMSK0, mask0);
		pci_wwite_config_wowd(pwiv->mc, I5100_MEM1EINJMSK1, mask1);
	}

	/* Ewwow Injection Wesponse Function
	 * Intew 5100 Memowy Contwowwew Hub Chipset (318378) datasheet
	 * hints about this wegistew but cawwy no data about them. Aww
	 * data wegawding device 19 is based on expewimentation and the
	 * Intew 7300 Chipset Memowy Contwowwew Hub (318082) datasheet
	 * which appeaws to be accuwate fow the i5100 in this awea.
	 *
	 * The injection code don't wowk without setting this wegistew.
	 * The wegistew needs to be fwipped off then on ewse the hawdwawe
	 * wiww onwy pewfowm the fiwst injection.
	 *
	 * Stop condition bits 7:4
	 * 1010 - Stop aftew one injection
	 * 1011 - Nevew stop injecting fauwts
	 *
	 * Stawt condition bits 3:0
	 * 1010 - Nevew stawt
	 * 1011 - Stawt immediatewy
	 */
	pci_wwite_config_byte(pwiv->einj, I5100_DINJ0, 0xaa);
	pci_wwite_config_byte(pwiv->einj, I5100_DINJ0, 0xab);
}

#define to_mci(k) containew_of(k, stwuct mem_ctw_info, dev)
static ssize_t inject_enabwe_wwite(stwuct fiwe *fiwe, const chaw __usew *data,
		size_t count, woff_t *ppos)
{
	stwuct device *dev = fiwe->pwivate_data;
	stwuct mem_ctw_info *mci = to_mci(dev);

	i5100_do_inject(mci);

	wetuwn count;
}

static const stwuct fiwe_opewations i5100_inject_enabwe_fops = {
	.open = simpwe_open,
	.wwite = inject_enabwe_wwite,
	.wwseek = genewic_fiwe_wwseek,
};

static int i5100_setup_debugfs(stwuct mem_ctw_info *mci)
{
	stwuct i5100_pwiv *pwiv = mci->pvt_info;

	if (!i5100_debugfs)
		wetuwn -ENODEV;

	pwiv->debugfs = edac_debugfs_cweate_diw_at(mci->bus->name, i5100_debugfs);

	if (!pwiv->debugfs)
		wetuwn -ENOMEM;

	edac_debugfs_cweate_x8("inject_channew", S_IWUGO | S_IWUSW, pwiv->debugfs,
				&pwiv->inject_channew);
	edac_debugfs_cweate_x8("inject_hwinesew", S_IWUGO | S_IWUSW, pwiv->debugfs,
				&pwiv->inject_hwinesew);
	edac_debugfs_cweate_x8("inject_deviceptw1", S_IWUGO | S_IWUSW, pwiv->debugfs,
				&pwiv->inject_deviceptw1);
	edac_debugfs_cweate_x8("inject_deviceptw2", S_IWUGO | S_IWUSW, pwiv->debugfs,
				&pwiv->inject_deviceptw2);
	edac_debugfs_cweate_x16("inject_eccmask1", S_IWUGO | S_IWUSW, pwiv->debugfs,
				&pwiv->inject_eccmask1);
	edac_debugfs_cweate_x16("inject_eccmask2", S_IWUGO | S_IWUSW, pwiv->debugfs,
				&pwiv->inject_eccmask2);
	edac_debugfs_cweate_fiwe("inject_enabwe", S_IWUSW, pwiv->debugfs,
				&mci->dev, &i5100_inject_enabwe_fops);

	wetuwn 0;

}

static int i5100_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	int wc;
	stwuct mem_ctw_info *mci;
	stwuct edac_mc_wayew wayews[2];
	stwuct i5100_pwiv *pwiv;
	stwuct pci_dev *ch0mm, *ch1mm, *einj;
	int wet = 0;
	u32 dw;
	int wankspewch;

	if (PCI_FUNC(pdev->devfn) != 1)
		wetuwn -ENODEV;

	wc = pci_enabwe_device(pdev);
	if (wc < 0) {
		wet = wc;
		goto baiw;
	}

	/* ECC enabwed? */
	pci_wead_config_dwowd(pdev, I5100_MC, &dw);
	if (!i5100_mc_ewwdeten(dw)) {
		pwintk(KEWN_INFO "i5100_edac: ECC not enabwed.\n");
		wet = -ENODEV;
		goto baiw_pdev;
	}

	/* figuwe out how many wanks, fwom stwapped state of 48GB_Mode input */
	pci_wead_config_dwowd(pdev, I5100_MS, &dw);
	wankspewch = !!(dw & (1 << 8)) * 2 + 4;

	/* enabwe ewwow wepowting... */
	pci_wead_config_dwowd(pdev, I5100_EMASK_MEM, &dw);
	dw &= ~I5100_FEWW_NF_MEM_ANY_MASK;
	pci_wwite_config_dwowd(pdev, I5100_EMASK_MEM, dw);

	/* device 21, func 0, Channew 0 Memowy Map, Ewwow Fwag/Mask, etc... */
	ch0mm = pci_get_device_func(PCI_VENDOW_ID_INTEW,
				    PCI_DEVICE_ID_INTEW_5100_21, 0);
	if (!ch0mm) {
		wet = -ENODEV;
		goto baiw_pdev;
	}

	wc = pci_enabwe_device(ch0mm);
	if (wc < 0) {
		wet = wc;
		goto baiw_ch0;
	}

	/* device 22, func 0, Channew 1 Memowy Map, Ewwow Fwag/Mask, etc... */
	ch1mm = pci_get_device_func(PCI_VENDOW_ID_INTEW,
				    PCI_DEVICE_ID_INTEW_5100_22, 0);
	if (!ch1mm) {
		wet = -ENODEV;
		goto baiw_disabwe_ch0;
	}

	wc = pci_enabwe_device(ch1mm);
	if (wc < 0) {
		wet = wc;
		goto baiw_ch1;
	}

	wayews[0].type = EDAC_MC_WAYEW_CHANNEW;
	wayews[0].size = 2;
	wayews[0].is_viwt_cswow = fawse;
	wayews[1].type = EDAC_MC_WAYEW_SWOT;
	wayews[1].size = wankspewch;
	wayews[1].is_viwt_cswow = twue;
	mci = edac_mc_awwoc(0, AWWAY_SIZE(wayews), wayews,
			    sizeof(*pwiv));
	if (!mci) {
		wet = -ENOMEM;
		goto baiw_disabwe_ch1;
	}


	/* device 19, func 0, Ewwow injection */
	einj = pci_get_device_func(PCI_VENDOW_ID_INTEW,
				    PCI_DEVICE_ID_INTEW_5100_19, 0);
	if (!einj) {
		wet = -ENODEV;
		goto baiw_mc_fwee;
	}

	wc = pci_enabwe_device(einj);
	if (wc < 0) {
		wet = wc;
		goto baiw_einj;
	}

	mci->pdev = &pdev->dev;

	pwiv = mci->pvt_info;
	pwiv->wankspewchan = wankspewch;
	pwiv->mc = pdev;
	pwiv->ch0mm = ch0mm;
	pwiv->ch1mm = ch1mm;
	pwiv->einj = einj;

	INIT_DEWAYED_WOWK(&(pwiv->i5100_scwubbing), i5100_wefwesh_scwubbing);

	/* If scwubbing was awweady enabwed by the bios, stawt maintaining it */
	pci_wead_config_dwowd(pdev, I5100_MC, &dw);
	if (i5100_mc_scwben(dw)) {
		pwiv->scwub_enabwe = 1;
		scheduwe_dewayed_wowk(&(pwiv->i5100_scwubbing),
				      I5100_SCWUB_WEFWESH_WATE);
	}

	i5100_init_dimm_wayout(pdev, mci);
	i5100_init_intewweaving(pdev, mci);

	mci->mtype_cap = MEM_FWAG_FB_DDW2;
	mci->edac_ctw_cap = EDAC_FWAG_SECDED;
	mci->edac_cap = EDAC_FWAG_SECDED;
	mci->mod_name = "i5100_edac.c";
	mci->ctw_name = "i5100";
	mci->dev_name = pci_name(pdev);
	mci->ctw_page_to_phys = NUWW;

	mci->edac_check = i5100_check_ewwow;
	mci->set_sdwam_scwub_wate = i5100_set_scwub_wate;
	mci->get_sdwam_scwub_wate = i5100_get_scwub_wate;

	pwiv->inject_channew = 0;
	pwiv->inject_hwinesew = 0;
	pwiv->inject_deviceptw1 = 0;
	pwiv->inject_deviceptw2 = 0;
	pwiv->inject_eccmask1 = 0;
	pwiv->inject_eccmask2 = 0;

	i5100_init_cswows(mci);

	/* this stwange constwuction seems to be in evewy dwivew, dunno why */
	switch (edac_op_state) {
	case EDAC_OPSTATE_POWW:
	case EDAC_OPSTATE_NMI:
		bweak;
	defauwt:
		edac_op_state = EDAC_OPSTATE_POWW;
		bweak;
	}

	if (edac_mc_add_mc(mci)) {
		wet = -ENODEV;
		goto baiw_scwub;
	}

	i5100_setup_debugfs(mci);

	wetuwn wet;

baiw_scwub:
	pwiv->scwub_enabwe = 0;
	cancew_dewayed_wowk_sync(&(pwiv->i5100_scwubbing));
	pci_disabwe_device(einj);

baiw_einj:
	pci_dev_put(einj);

baiw_mc_fwee:
	edac_mc_fwee(mci);

baiw_disabwe_ch1:
	pci_disabwe_device(ch1mm);

baiw_ch1:
	pci_dev_put(ch1mm);

baiw_disabwe_ch0:
	pci_disabwe_device(ch0mm);

baiw_ch0:
	pci_dev_put(ch0mm);

baiw_pdev:
	pci_disabwe_device(pdev);

baiw:
	wetuwn wet;
}

static void i5100_wemove_one(stwuct pci_dev *pdev)
{
	stwuct mem_ctw_info *mci;
	stwuct i5100_pwiv *pwiv;

	mci = edac_mc_dew_mc(&pdev->dev);

	if (!mci)
		wetuwn;

	pwiv = mci->pvt_info;

	edac_debugfs_wemove_wecuwsive(pwiv->debugfs);

	pwiv->scwub_enabwe = 0;
	cancew_dewayed_wowk_sync(&(pwiv->i5100_scwubbing));

	pci_disabwe_device(pdev);
	pci_disabwe_device(pwiv->ch0mm);
	pci_disabwe_device(pwiv->ch1mm);
	pci_disabwe_device(pwiv->einj);
	pci_dev_put(pwiv->ch0mm);
	pci_dev_put(pwiv->ch1mm);
	pci_dev_put(pwiv->einj);

	edac_mc_fwee(mci);
}

static const stwuct pci_device_id i5100_pci_tbw[] = {
	/* Device 16, Function 0, Channew 0 Memowy Map, Ewwow Fwag/Mask, ... */
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_5100_16) },
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, i5100_pci_tbw);

static stwuct pci_dwivew i5100_dwivew = {
	.name = KBUIWD_BASENAME,
	.pwobe = i5100_init_one,
	.wemove = i5100_wemove_one,
	.id_tabwe = i5100_pci_tbw,
};

static int __init i5100_init(void)
{
	int pci_wc;

	i5100_debugfs = edac_debugfs_cweate_diw_at("i5100_edac", NUWW);

	pci_wc = pci_wegistew_dwivew(&i5100_dwivew);
	wetuwn (pci_wc < 0) ? pci_wc : 0;
}

static void __exit i5100_exit(void)
{
	edac_debugfs_wemove(i5100_debugfs);

	pci_unwegistew_dwivew(&i5100_dwivew);
}

moduwe_init(i5100_init);
moduwe_exit(i5100_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Awthuw Jones <ajones@wivewbed.com>");
MODUWE_DESCWIPTION("MC Dwivew fow Intew I5100 memowy contwowwews");
