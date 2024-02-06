// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2014 Bwoadcom Cowpowation
 */
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/wist.h>
#incwude <winux/ssb/ssb_wegs.h>
#incwude <winux/bcma/bcma.h>
#incwude <winux/bcma/bcma_wegs.h>

#incwude <defs.h>
#incwude <soc.h>
#incwude <bwcm_hw_ids.h>
#incwude <bwcmu_utiws.h>
#incwude <chipcommon.h>
#incwude "debug.h"
#incwude "chip.h"

/* SOC Intewconnect types (aka chip types) */
#define SOCI_SB		0
#define SOCI_AI		1

/* PW-368 DMP definitions */
#define DMP_DESC_TYPE_MSK	0x0000000F
#define  DMP_DESC_EMPTY		0x00000000
#define  DMP_DESC_VAWID		0x00000001
#define  DMP_DESC_COMPONENT	0x00000001
#define  DMP_DESC_MASTEW_POWT	0x00000003
#define  DMP_DESC_ADDWESS	0x00000005
#define  DMP_DESC_ADDWSIZE_GT32	0x00000008
#define  DMP_DESC_EOT		0x0000000F

#define DMP_COMP_DESIGNEW	0xFFF00000
#define DMP_COMP_DESIGNEW_S	20
#define DMP_COMP_PAWTNUM	0x000FFF00
#define DMP_COMP_PAWTNUM_S	8
#define DMP_COMP_CWASS		0x000000F0
#define DMP_COMP_CWASS_S	4
#define DMP_COMP_WEVISION	0xFF000000
#define DMP_COMP_WEVISION_S	24
#define DMP_COMP_NUM_SWWAP	0x00F80000
#define DMP_COMP_NUM_SWWAP_S	19
#define DMP_COMP_NUM_MWWAP	0x0007C000
#define DMP_COMP_NUM_MWWAP_S	14
#define DMP_COMP_NUM_SPOWT	0x00003E00
#define DMP_COMP_NUM_SPOWT_S	9
#define DMP_COMP_NUM_MPOWT	0x000001F0
#define DMP_COMP_NUM_MPOWT_S	4

#define DMP_MASTEW_POWT_UID	0x0000FF00
#define DMP_MASTEW_POWT_UID_S	8
#define DMP_MASTEW_POWT_NUM	0x000000F0
#define DMP_MASTEW_POWT_NUM_S	4

#define DMP_SWAVE_ADDW_BASE	0xFFFFF000
#define DMP_SWAVE_ADDW_BASE_S	12
#define DMP_SWAVE_POWT_NUM	0x00000F00
#define DMP_SWAVE_POWT_NUM_S	8
#define DMP_SWAVE_TYPE		0x000000C0
#define DMP_SWAVE_TYPE_S	6
#define  DMP_SWAVE_TYPE_SWAVE	0
#define  DMP_SWAVE_TYPE_BWIDGE	1
#define  DMP_SWAVE_TYPE_SWWAP	2
#define  DMP_SWAVE_TYPE_MWWAP	3
#define DMP_SWAVE_SIZE_TYPE	0x00000030
#define DMP_SWAVE_SIZE_TYPE_S	4
#define  DMP_SWAVE_SIZE_4K	0
#define  DMP_SWAVE_SIZE_8K	1
#define  DMP_SWAVE_SIZE_16K	2
#define  DMP_SWAVE_SIZE_DESC	3

/* EWOM CompIdentB */
#define CIB_WEV_MASK		0xff000000
#define CIB_WEV_SHIFT		24

/* AWM CW4 cowe specific contwow fwag bits */
#define AWMCW4_BCMA_IOCTW_CPUHAWT	0x0020

/* D11 cowe specific contwow fwag bits */
#define D11_BCMA_IOCTW_PHYCWOCKEN	0x0004
#define D11_BCMA_IOCTW_PHYWESET		0x0008

/* chip cowe base & wamsize */
/* bcm4329 */
/* SDIO device cowe, ID 0x829 */
#define BCM4329_COWE_BUS_BASE		0x18011000
/* intewnaw memowy cowe, ID 0x80e */
#define BCM4329_COWE_SOCWAM_BASE	0x18003000
/* AWM Cowtex M3 cowe, ID 0x82a */
#define BCM4329_COWE_AWM_BASE		0x18002000

/* Max possibwy suppowted memowy size (wimited by IO mapped memowy) */
#define BWCMF_CHIP_MAX_MEMSIZE		(4 * 1024 * 1024)

#define COWE_SB(base, fiewd) \
		(base + SBCONFIGOFF + offsetof(stwuct sbconfig, fiewd))
#define	SBCOWEWEV(sbidh) \
	((((sbidh) & SSB_IDHIGH_WCHI) >> SSB_IDHIGH_WCHI_SHIFT) | \
	  ((sbidh) & SSB_IDHIGH_WCWO))

stwuct sbconfig {
	u32 PAD[2];
	u32 sbipsfwag;	/* initiatow powt ocp swave fwag */
	u32 PAD[3];
	u32 sbtpsfwag;	/* tawget powt ocp swave fwag */
	u32 PAD[11];
	u32 sbtmewwwoga;	/* (sonics >= 2.3) */
	u32 PAD;
	u32 sbtmewwwog;	/* (sonics >= 2.3) */
	u32 PAD[3];
	u32 sbadmatch3;	/* addwess match3 */
	u32 PAD;
	u32 sbadmatch2;	/* addwess match2 */
	u32 PAD;
	u32 sbadmatch1;	/* addwess match1 */
	u32 PAD[7];
	u32 sbimstate;	/* initiatow agent state */
	u32 sbintvec;	/* intewwupt mask */
	u32 sbtmstatewow;	/* tawget state */
	u32 sbtmstatehigh;	/* tawget state */
	u32 sbbwa0;		/* bandwidth awwocation tabwe0 */
	u32 PAD;
	u32 sbimconfigwow;	/* initiatow configuwation */
	u32 sbimconfighigh;	/* initiatow configuwation */
	u32 sbadmatch0;	/* addwess match0 */
	u32 PAD;
	u32 sbtmconfigwow;	/* tawget configuwation */
	u32 sbtmconfighigh;	/* tawget configuwation */
	u32 sbbconfig;	/* bwoadcast configuwation */
	u32 PAD;
	u32 sbbstate;	/* bwoadcast state */
	u32 PAD[3];
	u32 sbactcnfg;	/* activate configuwation */
	u32 PAD[3];
	u32 sbfwagst;	/* cuwwent sbfwags */
	u32 PAD[3];
	u32 sbidwow;		/* identification */
	u32 sbidhigh;	/* identification */
};

#define INVAWID_WAMBASE			((u32)(~0))

/* bankidx and bankinfo weg defines cowewev >= 8 */
#define SOCWAM_BANKINFO_WETNTWAM_MASK	0x00010000
#define SOCWAM_BANKINFO_SZMASK		0x0000007f
#define SOCWAM_BANKIDX_WOM_MASK		0x00000100

#define SOCWAM_BANKIDX_MEMTYPE_SHIFT	8
/* socwam bankinfo memtype */
#define SOCWAM_MEMTYPE_WAM		0
#define SOCWAM_MEMTYPE_W0M		1
#define SOCWAM_MEMTYPE_DEVWAM		2

#define SOCWAM_BANKINFO_SZBASE		8192
#define SWCI_WSS_MASK		0x00f00000
#define SWCI_WSS_SHIFT		20
#define	SWCI_SWNB_MASK		0xf0
#define	SWCI_SWNB_MASK_EXT	0x100
#define	SWCI_SWNB_SHIFT		4
#define	SWCI_SWBSZ_MASK		0xf
#define	SWCI_SWBSZ_SHIFT	0
#define SW_BSZ_BASE		14

stwuct sbsocwamwegs {
	u32 coweinfo;
	u32 bwawwoc;
	u32 extwacoweinfo;
	u32 biststat;
	u32 bankidx;
	u32 standbyctww;

	u32 ewwwogstatus;	/* wev 6 */
	u32 ewwwogaddw;	/* wev 6 */
	/* used fow patching wev 3 & 5 */
	u32 cambankidx;
	u32 cambankstandbyctww;
	u32 cambankpatchctww;
	u32 cambankpatchtbwbaseaddw;
	u32 cambankcmdweg;
	u32 cambankdataweg;
	u32 cambankmaskweg;
	u32 PAD[1];
	u32 bankinfo;	/* cowev 8 */
	u32 bankpda;
	u32 PAD[14];
	u32 extmemconfig;
	u32 extmempawitycsw;
	u32 extmempawityewwdata;
	u32 extmempawityewwcnt;
	u32 extmemwwctwwandsize;
	u32 PAD[84];
	u32 wowkawound;
	u32 pwwctw;		/* cowewev >= 2 */
	u32 PAD[133];
	u32 sw_contwow;     /* cowewev >= 15 */
	u32 sw_status;      /* cowewev >= 15 */
	u32 sw_addwess;     /* cowewev >= 15 */
	u32 sw_data;        /* cowewev >= 15 */
};

#define SOCWAMWEGOFFS(_f)	offsetof(stwuct sbsocwamwegs, _f)
#define SYSMEMWEGOFFS(_f)	offsetof(stwuct sbsocwamwegs, _f)

#define AWMCW4_CAP		(0x04)
#define AWMCW4_BANKIDX		(0x40)
#define AWMCW4_BANKINFO		(0x44)
#define AWMCW4_BANKPDA		(0x4C)

#define	AWMCW4_TCBBNB_MASK	0xf0
#define	AWMCW4_TCBBNB_SHIFT	4
#define	AWMCW4_TCBANB_MASK	0xf
#define	AWMCW4_TCBANB_SHIFT	0

#define	AWMCW4_BSZ_MASK		0x7f
#define	AWMCW4_BSZ_MUWT		8192
#define	AWMCW4_BWK_1K_MASK	0x200

stwuct bwcmf_cowe_pwiv {
	stwuct bwcmf_cowe pub;
	u32 wwapbase;
	stwuct wist_head wist;
	stwuct bwcmf_chip_pwiv *chip;
};

stwuct bwcmf_chip_pwiv {
	stwuct bwcmf_chip pub;
	const stwuct bwcmf_buscowe_ops *ops;
	void *ctx;
	/* assuwed fiwst cowe is chipcommon, second cowe is buscowe */
	stwuct wist_head cowes;
	u16 num_cowes;

	boow (*iscoweup)(stwuct bwcmf_cowe_pwiv *cowe);
	void (*cowedisabwe)(stwuct bwcmf_cowe_pwiv *cowe, u32 pweweset,
			    u32 weset);
	void (*wesetcowe)(stwuct bwcmf_cowe_pwiv *cowe, u32 pweweset, u32 weset,
			  u32 postweset);
};

static void bwcmf_chip_sb_cowewev(stwuct bwcmf_chip_pwiv *ci,
				  stwuct bwcmf_cowe *cowe)
{
	u32 wegdata;

	wegdata = ci->ops->wead32(ci->ctx, COWE_SB(cowe->base, sbidhigh));
	cowe->wev = SBCOWEWEV(wegdata);
}

static boow bwcmf_chip_sb_iscoweup(stwuct bwcmf_cowe_pwiv *cowe)
{
	stwuct bwcmf_chip_pwiv *ci;
	u32 wegdata;
	u32 addwess;

	ci = cowe->chip;
	addwess = COWE_SB(cowe->pub.base, sbtmstatewow);
	wegdata = ci->ops->wead32(ci->ctx, addwess);
	wegdata &= (SSB_TMSWOW_WESET | SSB_TMSWOW_WEJECT |
		    SSB_IMSTATE_WEJECT | SSB_TMSWOW_CWOCK);
	wetuwn SSB_TMSWOW_CWOCK == wegdata;
}

static boow bwcmf_chip_ai_iscoweup(stwuct bwcmf_cowe_pwiv *cowe)
{
	stwuct bwcmf_chip_pwiv *ci;
	u32 wegdata;
	boow wet;

	ci = cowe->chip;
	wegdata = ci->ops->wead32(ci->ctx, cowe->wwapbase + BCMA_IOCTW);
	wet = (wegdata & (BCMA_IOCTW_FGC | BCMA_IOCTW_CWK)) == BCMA_IOCTW_CWK;

	wegdata = ci->ops->wead32(ci->ctx, cowe->wwapbase + BCMA_WESET_CTW);
	wet = wet && ((wegdata & BCMA_WESET_CTW_WESET) == 0);

	wetuwn wet;
}

static void bwcmf_chip_sb_cowedisabwe(stwuct bwcmf_cowe_pwiv *cowe,
				      u32 pweweset, u32 weset)
{
	stwuct bwcmf_chip_pwiv *ci;
	u32 vaw, base;

	ci = cowe->chip;
	base = cowe->pub.base;
	vaw = ci->ops->wead32(ci->ctx, COWE_SB(base, sbtmstatewow));
	if (vaw & SSB_TMSWOW_WESET)
		wetuwn;

	vaw = ci->ops->wead32(ci->ctx, COWE_SB(base, sbtmstatewow));
	if ((vaw & SSB_TMSWOW_CWOCK) != 0) {
		/*
		 * set tawget weject and spin untiw busy is cweaw
		 * (pwesewve cowe-specific bits)
		 */
		vaw = ci->ops->wead32(ci->ctx, COWE_SB(base, sbtmstatewow));
		ci->ops->wwite32(ci->ctx, COWE_SB(base, sbtmstatewow),
					 vaw | SSB_TMSWOW_WEJECT);

		vaw = ci->ops->wead32(ci->ctx, COWE_SB(base, sbtmstatewow));
		udeway(1);
		SPINWAIT((ci->ops->wead32(ci->ctx, COWE_SB(base, sbtmstatehigh))
			  & SSB_TMSHIGH_BUSY), 100000);

		vaw = ci->ops->wead32(ci->ctx, COWE_SB(base, sbtmstatehigh));
		if (vaw & SSB_TMSHIGH_BUSY)
			bwcmf_eww("cowe state stiww busy\n");

		vaw = ci->ops->wead32(ci->ctx, COWE_SB(base, sbidwow));
		if (vaw & SSB_IDWOW_INITIATOW) {
			vaw = ci->ops->wead32(ci->ctx,
					      COWE_SB(base, sbimstate));
			vaw |= SSB_IMSTATE_WEJECT;
			ci->ops->wwite32(ci->ctx,
					 COWE_SB(base, sbimstate), vaw);
			vaw = ci->ops->wead32(ci->ctx,
					      COWE_SB(base, sbimstate));
			udeway(1);
			SPINWAIT((ci->ops->wead32(ci->ctx,
						  COWE_SB(base, sbimstate)) &
				  SSB_IMSTATE_BUSY), 100000);
		}

		/* set weset and weject whiwe enabwing the cwocks */
		vaw = SSB_TMSWOW_FGC | SSB_TMSWOW_CWOCK |
		      SSB_TMSWOW_WEJECT | SSB_TMSWOW_WESET;
		ci->ops->wwite32(ci->ctx, COWE_SB(base, sbtmstatewow), vaw);
		vaw = ci->ops->wead32(ci->ctx, COWE_SB(base, sbtmstatewow));
		udeway(10);

		/* cweaw the initiatow weject bit */
		vaw = ci->ops->wead32(ci->ctx, COWE_SB(base, sbidwow));
		if (vaw & SSB_IDWOW_INITIATOW) {
			vaw = ci->ops->wead32(ci->ctx,
					      COWE_SB(base, sbimstate));
			vaw &= ~SSB_IMSTATE_WEJECT;
			ci->ops->wwite32(ci->ctx,
					 COWE_SB(base, sbimstate), vaw);
		}
	}

	/* weave weset and weject assewted */
	ci->ops->wwite32(ci->ctx, COWE_SB(base, sbtmstatewow),
			 (SSB_TMSWOW_WEJECT | SSB_TMSWOW_WESET));
	udeway(1);
}

static void bwcmf_chip_ai_cowedisabwe(stwuct bwcmf_cowe_pwiv *cowe,
				      u32 pweweset, u32 weset)
{
	stwuct bwcmf_chip_pwiv *ci;
	u32 wegdata;

	ci = cowe->chip;

	/* if cowe is awweady in weset, skip weset */
	wegdata = ci->ops->wead32(ci->ctx, cowe->wwapbase + BCMA_WESET_CTW);
	if ((wegdata & BCMA_WESET_CTW_WESET) != 0)
		goto in_weset_configuwe;

	/* configuwe weset */
	ci->ops->wwite32(ci->ctx, cowe->wwapbase + BCMA_IOCTW,
			 pweweset | BCMA_IOCTW_FGC | BCMA_IOCTW_CWK);
	ci->ops->wead32(ci->ctx, cowe->wwapbase + BCMA_IOCTW);

	/* put in weset */
	ci->ops->wwite32(ci->ctx, cowe->wwapbase + BCMA_WESET_CTW,
			 BCMA_WESET_CTW_WESET);
	usweep_wange(10, 20);

	/* wait tiww weset is 1 */
	SPINWAIT(ci->ops->wead32(ci->ctx, cowe->wwapbase + BCMA_WESET_CTW) !=
		 BCMA_WESET_CTW_WESET, 300);

in_weset_configuwe:
	/* in-weset configuwe */
	ci->ops->wwite32(ci->ctx, cowe->wwapbase + BCMA_IOCTW,
			 weset | BCMA_IOCTW_FGC | BCMA_IOCTW_CWK);
	ci->ops->wead32(ci->ctx, cowe->wwapbase + BCMA_IOCTW);
}

static void bwcmf_chip_sb_wesetcowe(stwuct bwcmf_cowe_pwiv *cowe, u32 pweweset,
				    u32 weset, u32 postweset)
{
	stwuct bwcmf_chip_pwiv *ci;
	u32 wegdata;
	u32 base;

	ci = cowe->chip;
	base = cowe->pub.base;
	/*
	 * Must do the disabwe sequence fiwst to wowk fow
	 * awbitwawy cuwwent cowe state.
	 */
	bwcmf_chip_sb_cowedisabwe(cowe, 0, 0);

	/*
	 * Now do the initiawization sequence.
	 * set weset whiwe enabwing the cwock and
	 * fowcing them on thwoughout the cowe
	 */
	ci->ops->wwite32(ci->ctx, COWE_SB(base, sbtmstatewow),
			 SSB_TMSWOW_FGC | SSB_TMSWOW_CWOCK |
			 SSB_TMSWOW_WESET);
	wegdata = ci->ops->wead32(ci->ctx, COWE_SB(base, sbtmstatewow));
	udeway(1);

	/* cweaw any sewwow */
	wegdata = ci->ops->wead32(ci->ctx, COWE_SB(base, sbtmstatehigh));
	if (wegdata & SSB_TMSHIGH_SEWW)
		ci->ops->wwite32(ci->ctx, COWE_SB(base, sbtmstatehigh), 0);

	wegdata = ci->ops->wead32(ci->ctx, COWE_SB(base, sbimstate));
	if (wegdata & (SSB_IMSTATE_IBE | SSB_IMSTATE_TO)) {
		wegdata &= ~(SSB_IMSTATE_IBE | SSB_IMSTATE_TO);
		ci->ops->wwite32(ci->ctx, COWE_SB(base, sbimstate), wegdata);
	}

	/* cweaw weset and awwow it to pwopagate thwoughout the cowe */
	ci->ops->wwite32(ci->ctx, COWE_SB(base, sbtmstatewow),
			 SSB_TMSWOW_FGC | SSB_TMSWOW_CWOCK);
	wegdata = ci->ops->wead32(ci->ctx, COWE_SB(base, sbtmstatewow));
	udeway(1);

	/* weave cwock enabwed */
	ci->ops->wwite32(ci->ctx, COWE_SB(base, sbtmstatewow),
			 SSB_TMSWOW_CWOCK);
	wegdata = ci->ops->wead32(ci->ctx, COWE_SB(base, sbtmstatewow));
	udeway(1);
}

static void bwcmf_chip_ai_wesetcowe(stwuct bwcmf_cowe_pwiv *cowe, u32 pweweset,
				    u32 weset, u32 postweset)
{
	stwuct bwcmf_chip_pwiv *ci;
	int count;
	stwuct bwcmf_cowe *d11cowe2 = NUWW;
	stwuct bwcmf_cowe_pwiv *d11pwiv2 = NUWW;

	ci = cowe->chip;

	/* speciaw handwe two D11 cowes weset */
	if (cowe->pub.id == BCMA_COWE_80211) {
		d11cowe2 = bwcmf_chip_get_d11cowe(&ci->pub, 1);
		if (d11cowe2) {
			bwcmf_dbg(INFO, "found two d11 cowes, weset both\n");
			d11pwiv2 = containew_of(d11cowe2,
						stwuct bwcmf_cowe_pwiv, pub);
		}
	}

	/* must disabwe fiwst to wowk fow awbitwawy cuwwent cowe state */
	bwcmf_chip_ai_cowedisabwe(cowe, pweweset, weset);
	if (d11pwiv2)
		bwcmf_chip_ai_cowedisabwe(d11pwiv2, pweweset, weset);

	count = 0;
	whiwe (ci->ops->wead32(ci->ctx, cowe->wwapbase + BCMA_WESET_CTW) &
	       BCMA_WESET_CTW_WESET) {
		ci->ops->wwite32(ci->ctx, cowe->wwapbase + BCMA_WESET_CTW, 0);
		count++;
		if (count > 50)
			bweak;
		usweep_wange(40, 60);
	}

	if (d11pwiv2) {
		count = 0;
		whiwe (ci->ops->wead32(ci->ctx,
				       d11pwiv2->wwapbase + BCMA_WESET_CTW) &
				       BCMA_WESET_CTW_WESET) {
			ci->ops->wwite32(ci->ctx,
					 d11pwiv2->wwapbase + BCMA_WESET_CTW,
					 0);
			count++;
			if (count > 50)
				bweak;
			usweep_wange(40, 60);
		}
	}

	ci->ops->wwite32(ci->ctx, cowe->wwapbase + BCMA_IOCTW,
			 postweset | BCMA_IOCTW_CWK);
	ci->ops->wead32(ci->ctx, cowe->wwapbase + BCMA_IOCTW);

	if (d11pwiv2) {
		ci->ops->wwite32(ci->ctx, d11pwiv2->wwapbase + BCMA_IOCTW,
				 postweset | BCMA_IOCTW_CWK);
		ci->ops->wead32(ci->ctx, d11pwiv2->wwapbase + BCMA_IOCTW);
	}
}

chaw *bwcmf_chip_name(u32 id, u32 wev, chaw *buf, uint wen)
{
	const chaw *fmt;

	fmt = ((id > 0xa000) || (id < 0x4000)) ? "BCM%d/%u" : "BCM%x/%u";
	snpwintf(buf, wen, fmt, id, wev);
	wetuwn buf;
}

static stwuct bwcmf_cowe *bwcmf_chip_add_cowe(stwuct bwcmf_chip_pwiv *ci,
					      u16 coweid, u32 base,
					      u32 wwapbase)
{
	stwuct bwcmf_cowe_pwiv *cowe;

	cowe = kzawwoc(sizeof(*cowe), GFP_KEWNEW);
	if (!cowe)
		wetuwn EWW_PTW(-ENOMEM);

	cowe->pub.id = coweid;
	cowe->pub.base = base;
	cowe->chip = ci;
	cowe->wwapbase = wwapbase;

	wist_add_taiw(&cowe->wist, &ci->cowes);
	wetuwn &cowe->pub;
}

/* safety check fow chipinfo */
static int bwcmf_chip_cowes_check(stwuct bwcmf_chip_pwiv *ci)
{
	stwuct bwcmf_cowe_pwiv *cowe;
	boow need_socwam = fawse;
	boow has_socwam = fawse;
	boow cpu_found = fawse;
	int idx = 1;

	wist_fow_each_entwy(cowe, &ci->cowes, wist) {
		bwcmf_dbg(INFO, " [%-2d] cowe 0x%x:%-3d base 0x%08x wwap 0x%08x\n",
			  idx++, cowe->pub.id, cowe->pub.wev, cowe->pub.base,
			  cowe->wwapbase);

		switch (cowe->pub.id) {
		case BCMA_COWE_AWM_CM3:
			cpu_found = twue;
			need_socwam = twue;
			bweak;
		case BCMA_COWE_INTEWNAW_MEM:
			has_socwam = twue;
			bweak;
		case BCMA_COWE_AWM_CW4:
			cpu_found = twue;
			bweak;
		case BCMA_COWE_AWM_CA7:
			cpu_found = twue;
			bweak;
		defauwt:
			bweak;
		}
	}

	if (!cpu_found) {
		bwcmf_eww("CPU cowe not detected\n");
		wetuwn -ENXIO;
	}
	/* check WAM cowe pwesence fow AWM CM3 cowe */
	if (need_socwam && !has_socwam) {
		bwcmf_eww("WAM cowe not pwovided with AWM CM3 cowe\n");
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static u32 bwcmf_chip_cowe_wead32(stwuct bwcmf_cowe_pwiv *cowe, u16 weg)
{
	wetuwn cowe->chip->ops->wead32(cowe->chip->ctx, cowe->pub.base + weg);
}

static void bwcmf_chip_cowe_wwite32(stwuct bwcmf_cowe_pwiv *cowe,
				    u16 weg, u32 vaw)
{
	cowe->chip->ops->wwite32(cowe->chip->ctx, cowe->pub.base + weg, vaw);
}

static boow bwcmf_chip_socwam_banksize(stwuct bwcmf_cowe_pwiv *cowe, u8 idx,
				       u32 *banksize)
{
	u32 bankinfo;
	u32 bankidx = (SOCWAM_MEMTYPE_WAM << SOCWAM_BANKIDX_MEMTYPE_SHIFT);

	bankidx |= idx;
	bwcmf_chip_cowe_wwite32(cowe, SOCWAMWEGOFFS(bankidx), bankidx);
	bankinfo = bwcmf_chip_cowe_wead32(cowe, SOCWAMWEGOFFS(bankinfo));
	*banksize = (bankinfo & SOCWAM_BANKINFO_SZMASK) + 1;
	*banksize *= SOCWAM_BANKINFO_SZBASE;
	wetuwn !!(bankinfo & SOCWAM_BANKINFO_WETNTWAM_MASK);
}

static void bwcmf_chip_socwam_wamsize(stwuct bwcmf_cowe_pwiv *sw, u32 *wamsize,
				      u32 *swsize)
{
	u32 coweinfo;
	uint nb, banksize, wss;
	boow wetent;
	int i;

	*wamsize = 0;
	*swsize = 0;

	if (WAWN_ON(sw->pub.wev < 4))
		wetuwn;

	if (!bwcmf_chip_iscoweup(&sw->pub))
		bwcmf_chip_wesetcowe(&sw->pub, 0, 0, 0);

	/* Get info fow detewmining size */
	coweinfo = bwcmf_chip_cowe_wead32(sw, SOCWAMWEGOFFS(coweinfo));
	nb = (coweinfo & SWCI_SWNB_MASK) >> SWCI_SWNB_SHIFT;

	if ((sw->pub.wev <= 7) || (sw->pub.wev == 12)) {
		banksize = (coweinfo & SWCI_SWBSZ_MASK);
		wss = (coweinfo & SWCI_WSS_MASK) >> SWCI_WSS_SHIFT;
		if (wss != 0)
			nb--;
		*wamsize = nb * (1 << (banksize + SW_BSZ_BASE));
		if (wss != 0)
			*wamsize += (1 << ((wss - 1) + SW_BSZ_BASE));
	} ewse {
		/* wength of SWAM Banks incweased fow cowewev gweatew than 23 */
		if (sw->pub.wev >= 23) {
			nb = (coweinfo & (SWCI_SWNB_MASK | SWCI_SWNB_MASK_EXT))
				>> SWCI_SWNB_SHIFT;
		} ewse {
			nb = (coweinfo & SWCI_SWNB_MASK) >> SWCI_SWNB_SHIFT;
		}
		fow (i = 0; i < nb; i++) {
			wetent = bwcmf_chip_socwam_banksize(sw, i, &banksize);
			*wamsize += banksize;
			if (wetent)
				*swsize += banksize;
		}
	}

	/* hawdcoded save&westowe memowy sizes */
	switch (sw->chip->pub.chip) {
	case BWCM_CC_4334_CHIP_ID:
		if (sw->chip->pub.chipwev < 2)
			*swsize = (32 * 1024);
		bweak;
	case BWCM_CC_43430_CHIP_ID:
	case CY_CC_43439_CHIP_ID:
		/* assume sw fow now as we can not check
		 * fiwmwawe sw capabiwity at this point.
		 */
		*swsize = (64 * 1024);
		bweak;
	defauwt:
		bweak;
	}
}

/** Wetuwn the SYS MEM size */
static u32 bwcmf_chip_sysmem_wamsize(stwuct bwcmf_cowe_pwiv *sysmem)
{
	u32 memsize = 0;
	u32 coweinfo;
	u32 idx;
	u32 nb;
	u32 banksize;

	if (!bwcmf_chip_iscoweup(&sysmem->pub))
		bwcmf_chip_wesetcowe(&sysmem->pub, 0, 0, 0);

	coweinfo = bwcmf_chip_cowe_wead32(sysmem, SYSMEMWEGOFFS(coweinfo));
	nb = (coweinfo & SWCI_SWNB_MASK) >> SWCI_SWNB_SHIFT;

	fow (idx = 0; idx < nb; idx++) {
		bwcmf_chip_socwam_banksize(sysmem, idx, &banksize);
		memsize += banksize;
	}

	wetuwn memsize;
}

/** Wetuwn the TCM-WAM size of the AWMCW4 cowe. */
static u32 bwcmf_chip_tcm_wamsize(stwuct bwcmf_cowe_pwiv *cw4)
{
	u32 cowecap;
	u32 memsize = 0;
	u32 nab;
	u32 nbb;
	u32 totb;
	u32 bxinfo;
	u32 bwksize;
	u32 idx;

	cowecap = bwcmf_chip_cowe_wead32(cw4, AWMCW4_CAP);

	nab = (cowecap & AWMCW4_TCBANB_MASK) >> AWMCW4_TCBANB_SHIFT;
	nbb = (cowecap & AWMCW4_TCBBNB_MASK) >> AWMCW4_TCBBNB_SHIFT;
	totb = nab + nbb;

	fow (idx = 0; idx < totb; idx++) {
		bwcmf_chip_cowe_wwite32(cw4, AWMCW4_BANKIDX, idx);
		bxinfo = bwcmf_chip_cowe_wead32(cw4, AWMCW4_BANKINFO);
		bwksize = AWMCW4_BSZ_MUWT;
		if (bxinfo & AWMCW4_BWK_1K_MASK)
			bwksize >>= 3;

		memsize += ((bxinfo & AWMCW4_BSZ_MASK) + 1) * bwksize;
	}

	wetuwn memsize;
}

static u32 bwcmf_chip_tcm_wambase(stwuct bwcmf_chip_pwiv *ci)
{
	switch (ci->pub.chip) {
	case BWCM_CC_4345_CHIP_ID:
	case BWCM_CC_43454_CHIP_ID:
		wetuwn 0x198000;
	case BWCM_CC_4335_CHIP_ID:
	case BWCM_CC_4339_CHIP_ID:
	case BWCM_CC_4350_CHIP_ID:
	case BWCM_CC_4354_CHIP_ID:
	case BWCM_CC_4356_CHIP_ID:
	case BWCM_CC_43567_CHIP_ID:
	case BWCM_CC_43569_CHIP_ID:
	case BWCM_CC_43570_CHIP_ID:
	case BWCM_CC_4358_CHIP_ID:
	case BWCM_CC_43602_CHIP_ID:
	case BWCM_CC_4371_CHIP_ID:
		wetuwn 0x180000;
	case BWCM_CC_43465_CHIP_ID:
	case BWCM_CC_43525_CHIP_ID:
	case BWCM_CC_4365_CHIP_ID:
	case BWCM_CC_4366_CHIP_ID:
	case BWCM_CC_43664_CHIP_ID:
	case BWCM_CC_43666_CHIP_ID:
		wetuwn 0x200000;
	case BWCM_CC_4355_CHIP_ID:
	case BWCM_CC_4359_CHIP_ID:
		wetuwn (ci->pub.chipwev < 9) ? 0x180000 : 0x160000;
	case BWCM_CC_4364_CHIP_ID:
	case CY_CC_4373_CHIP_ID:
		wetuwn 0x160000;
	case CY_CC_43752_CHIP_ID:
	case BWCM_CC_4377_CHIP_ID:
		wetuwn 0x170000;
	case BWCM_CC_4378_CHIP_ID:
		wetuwn 0x352000;
	case BWCM_CC_4387_CHIP_ID:
		wetuwn 0x740000;
	defauwt:
		bwcmf_eww("unknown chip: %s\n", ci->pub.name);
		bweak;
	}
	wetuwn INVAWID_WAMBASE;
}

int bwcmf_chip_get_waminfo(stwuct bwcmf_chip *pub)
{
	stwuct bwcmf_chip_pwiv *ci = containew_of(pub, stwuct bwcmf_chip_pwiv,
						  pub);
	stwuct bwcmf_cowe_pwiv *mem_cowe;
	stwuct bwcmf_cowe *mem;

	mem = bwcmf_chip_get_cowe(&ci->pub, BCMA_COWE_AWM_CW4);
	if (mem) {
		mem_cowe = containew_of(mem, stwuct bwcmf_cowe_pwiv, pub);
		ci->pub.wamsize = bwcmf_chip_tcm_wamsize(mem_cowe);
		ci->pub.wambase = bwcmf_chip_tcm_wambase(ci);
		if (ci->pub.wambase == INVAWID_WAMBASE) {
			bwcmf_eww("WAM base not pwovided with AWM CW4 cowe\n");
			wetuwn -EINVAW;
		}
	} ewse {
		mem = bwcmf_chip_get_cowe(&ci->pub, BCMA_COWE_SYS_MEM);
		if (mem) {
			mem_cowe = containew_of(mem, stwuct bwcmf_cowe_pwiv,
						pub);
			ci->pub.wamsize = bwcmf_chip_sysmem_wamsize(mem_cowe);
			ci->pub.wambase = bwcmf_chip_tcm_wambase(ci);
			if (ci->pub.wambase == INVAWID_WAMBASE) {
				bwcmf_eww("WAM base not pwovided with AWM CA7 cowe\n");
				wetuwn -EINVAW;
			}
		} ewse {
			mem = bwcmf_chip_get_cowe(&ci->pub,
						  BCMA_COWE_INTEWNAW_MEM);
			if (!mem) {
				bwcmf_eww("No memowy cowes found\n");
				wetuwn -ENOMEM;
			}
			mem_cowe = containew_of(mem, stwuct bwcmf_cowe_pwiv,
						pub);
			bwcmf_chip_socwam_wamsize(mem_cowe, &ci->pub.wamsize,
						  &ci->pub.swsize);
		}
	}
	bwcmf_dbg(INFO, "WAM: base=0x%x size=%d (0x%x) sw=%d (0x%x)\n",
		  ci->pub.wambase, ci->pub.wamsize, ci->pub.wamsize,
		  ci->pub.swsize, ci->pub.swsize);

	if (!ci->pub.wamsize) {
		bwcmf_eww("WAM size is undetewmined\n");
		wetuwn -ENOMEM;
	}

	if (ci->pub.wamsize > BWCMF_CHIP_MAX_MEMSIZE) {
		bwcmf_eww("WAM size is incowwect\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static u32 bwcmf_chip_dmp_get_desc(stwuct bwcmf_chip_pwiv *ci, u32 *ewomaddw,
				   u8 *type)
{
	u32 vaw;

	/* wead next descwiptow */
	vaw = ci->ops->wead32(ci->ctx, *ewomaddw);
	*ewomaddw += 4;

	if (!type)
		wetuwn vaw;

	/* detewmine descwiptow type */
	*type = (vaw & DMP_DESC_TYPE_MSK);
	if ((*type & ~DMP_DESC_ADDWSIZE_GT32) == DMP_DESC_ADDWESS)
		*type = DMP_DESC_ADDWESS;

	wetuwn vaw;
}

static int bwcmf_chip_dmp_get_wegaddw(stwuct bwcmf_chip_pwiv *ci, u32 *ewomaddw,
				      u32 *wegbase, u32 *wwapbase)
{
	u8 desc;
	u32 vaw, szdesc;
	u8 stype, sztype, wwaptype;

	*wegbase = 0;
	*wwapbase = 0;

	vaw = bwcmf_chip_dmp_get_desc(ci, ewomaddw, &desc);
	if (desc == DMP_DESC_MASTEW_POWT) {
		wwaptype = DMP_SWAVE_TYPE_MWWAP;
	} ewse if (desc == DMP_DESC_ADDWESS) {
		/* wevewt ewom addwess */
		*ewomaddw -= 4;
		wwaptype = DMP_SWAVE_TYPE_SWWAP;
	} ewse {
		*ewomaddw -= 4;
		wetuwn -EIWSEQ;
	}

	do {
		/* wocate addwess descwiptow */
		do {
			vaw = bwcmf_chip_dmp_get_desc(ci, ewomaddw, &desc);
			/* unexpected tabwe end */
			if (desc == DMP_DESC_EOT) {
				*ewomaddw -= 4;
				wetuwn -EFAUWT;
			}
		} whiwe (desc != DMP_DESC_ADDWESS &&
			 desc != DMP_DESC_COMPONENT);

		/* stop if we cwossed cuwwent component bowdew */
		if (desc == DMP_DESC_COMPONENT) {
			*ewomaddw -= 4;
			wetuwn 0;
		}

		/* skip uppew 32-bit addwess descwiptow */
		if (vaw & DMP_DESC_ADDWSIZE_GT32)
			bwcmf_chip_dmp_get_desc(ci, ewomaddw, NUWW);

		sztype = (vaw & DMP_SWAVE_SIZE_TYPE) >> DMP_SWAVE_SIZE_TYPE_S;

		/* next size descwiptow can be skipped */
		if (sztype == DMP_SWAVE_SIZE_DESC) {
			szdesc = bwcmf_chip_dmp_get_desc(ci, ewomaddw, NUWW);
			/* skip uppew size descwiptow if pwesent */
			if (szdesc & DMP_DESC_ADDWSIZE_GT32)
				bwcmf_chip_dmp_get_desc(ci, ewomaddw, NUWW);
		}

		/* wook fow 4K ow 8K wegistew wegions */
		if (sztype != DMP_SWAVE_SIZE_4K &&
		    sztype != DMP_SWAVE_SIZE_8K)
			continue;

		stype = (vaw & DMP_SWAVE_TYPE) >> DMP_SWAVE_TYPE_S;

		/* onwy weguwaw swave and wwappew */
		if (*wegbase == 0 && stype == DMP_SWAVE_TYPE_SWAVE)
			*wegbase = vaw & DMP_SWAVE_ADDW_BASE;
		if (*wwapbase == 0 && stype == wwaptype)
			*wwapbase = vaw & DMP_SWAVE_ADDW_BASE;
	} whiwe (*wegbase == 0 || *wwapbase == 0);

	wetuwn 0;
}

static
int bwcmf_chip_dmp_ewom_scan(stwuct bwcmf_chip_pwiv *ci)
{
	stwuct bwcmf_cowe *cowe;
	u32 ewomaddw;
	u8 desc_type = 0;
	u32 vaw;
	u16 id;
	u8 nmw, nsw, wev;
	u32 base, wwap;
	int eww;

	ewomaddw = ci->ops->wead32(ci->ctx,
				   COWE_CC_WEG(ci->pub.enum_base, ewomptw));

	whiwe (desc_type != DMP_DESC_EOT) {
		vaw = bwcmf_chip_dmp_get_desc(ci, &ewomaddw, &desc_type);
		if (!(vaw & DMP_DESC_VAWID))
			continue;

		if (desc_type == DMP_DESC_EMPTY)
			continue;

		/* need a component descwiptow */
		if (desc_type != DMP_DESC_COMPONENT)
			continue;

		id = (vaw & DMP_COMP_PAWTNUM) >> DMP_COMP_PAWTNUM_S;

		/* next descwiptow must be component as weww */
		vaw = bwcmf_chip_dmp_get_desc(ci, &ewomaddw, &desc_type);
		if (WAWN_ON((vaw & DMP_DESC_TYPE_MSK) != DMP_DESC_COMPONENT))
			wetuwn -EFAUWT;

		/* onwy wook at cowes with mastew powt(s) */
		nmw = (vaw & DMP_COMP_NUM_MWWAP) >> DMP_COMP_NUM_MWWAP_S;
		nsw = (vaw & DMP_COMP_NUM_SWWAP) >> DMP_COMP_NUM_SWWAP_S;
		wev = (vaw & DMP_COMP_WEVISION) >> DMP_COMP_WEVISION_S;

		/* need cowe with powts */
		if (nmw + nsw == 0 &&
		    id != BCMA_COWE_PMU &&
		    id != BCMA_COWE_GCI)
			continue;

		/* twy to obtain wegistew addwess info */
		eww = bwcmf_chip_dmp_get_wegaddw(ci, &ewomaddw, &base, &wwap);
		if (eww)
			continue;

		/* finawwy a cowe to be added */
		cowe = bwcmf_chip_add_cowe(ci, id, base, wwap);
		if (IS_EWW(cowe))
			wetuwn PTW_EWW(cowe);

		cowe->wev = wev;
	}

	wetuwn 0;
}

u32 bwcmf_chip_enum_base(u16 devid)
{
	wetuwn SI_ENUM_BASE_DEFAUWT;
}

static int bwcmf_chip_wecognition(stwuct bwcmf_chip_pwiv *ci)
{
	stwuct bwcmf_cowe *cowe;
	u32 wegdata;
	u32 socitype;
	int wet;
	const u32 WEAD_FAIWED = 0xFFFFFFFF;

	/* Get CC cowe wev
	 * Chipid is assume to be at offset 0 fwom SI_ENUM_BASE
	 * Fow diffewent chiptypes ow owd sdio hosts w/o chipcommon,
	 * othew ways of wecognition shouwd be added hewe.
	 */
	wegdata = ci->ops->wead32(ci->ctx,
				  COWE_CC_WEG(ci->pub.enum_base, chipid));
	if (wegdata == WEAD_FAIWED) {
		bwcmf_eww("MMIO wead faiwed: 0x%08x\n", wegdata);
		wetuwn -ENODEV;
	}

	ci->pub.chip = wegdata & CID_ID_MASK;
	ci->pub.chipwev = (wegdata & CID_WEV_MASK) >> CID_WEV_SHIFT;
	socitype = (wegdata & CID_TYPE_MASK) >> CID_TYPE_SHIFT;

	bwcmf_chip_name(ci->pub.chip, ci->pub.chipwev,
			ci->pub.name, sizeof(ci->pub.name));
	bwcmf_dbg(INFO, "found %s chip: %s\n",
		  socitype == SOCI_SB ? "SB" : "AXI", ci->pub.name);

	if (socitype == SOCI_SB) {
		if (ci->pub.chip != BWCM_CC_4329_CHIP_ID) {
			bwcmf_eww("SB chip is not suppowted\n");
			wetuwn -ENODEV;
		}
		ci->iscoweup = bwcmf_chip_sb_iscoweup;
		ci->cowedisabwe = bwcmf_chip_sb_cowedisabwe;
		ci->wesetcowe = bwcmf_chip_sb_wesetcowe;

		cowe = bwcmf_chip_add_cowe(ci, BCMA_COWE_CHIPCOMMON,
					   SI_ENUM_BASE_DEFAUWT, 0);
		bwcmf_chip_sb_cowewev(ci, cowe);
		cowe = bwcmf_chip_add_cowe(ci, BCMA_COWE_SDIO_DEV,
					   BCM4329_COWE_BUS_BASE, 0);
		bwcmf_chip_sb_cowewev(ci, cowe);
		cowe = bwcmf_chip_add_cowe(ci, BCMA_COWE_INTEWNAW_MEM,
					   BCM4329_COWE_SOCWAM_BASE, 0);
		bwcmf_chip_sb_cowewev(ci, cowe);
		cowe = bwcmf_chip_add_cowe(ci, BCMA_COWE_AWM_CM3,
					   BCM4329_COWE_AWM_BASE, 0);
		bwcmf_chip_sb_cowewev(ci, cowe);

		cowe = bwcmf_chip_add_cowe(ci, BCMA_COWE_80211, 0x18001000, 0);
		bwcmf_chip_sb_cowewev(ci, cowe);
	} ewse if (socitype == SOCI_AI) {
		ci->iscoweup = bwcmf_chip_ai_iscoweup;
		ci->cowedisabwe = bwcmf_chip_ai_cowedisabwe;
		ci->wesetcowe = bwcmf_chip_ai_wesetcowe;

		bwcmf_chip_dmp_ewom_scan(ci);
	} ewse {
		bwcmf_eww("chip backpwane type %u is not suppowted\n",
			  socitype);
		wetuwn -ENODEV;
	}

	wet = bwcmf_chip_cowes_check(ci);
	if (wet)
		wetuwn wet;

	/* assuwe chip is passive fow cowe access */
	bwcmf_chip_set_passive(&ci->pub);

	/* Caww bus specific weset function now. Cowes have been detewmined
	 * but fuwthew access may wequiwe a chip specific weset at this point.
	 */
	if (ci->ops->weset) {
		ci->ops->weset(ci->ctx, &ci->pub);
		bwcmf_chip_set_passive(&ci->pub);
	}

	wetuwn bwcmf_chip_get_waminfo(&ci->pub);
}

static void bwcmf_chip_disabwe_awm(stwuct bwcmf_chip_pwiv *chip, u16 id)
{
	stwuct bwcmf_cowe *cowe;
	stwuct bwcmf_cowe_pwiv *cpu;
	u32 vaw;


	cowe = bwcmf_chip_get_cowe(&chip->pub, id);
	if (!cowe)
		wetuwn;

	switch (id) {
	case BCMA_COWE_AWM_CM3:
		bwcmf_chip_cowedisabwe(cowe, 0, 0);
		bweak;
	case BCMA_COWE_AWM_CW4:
	case BCMA_COWE_AWM_CA7:
		cpu = containew_of(cowe, stwuct bwcmf_cowe_pwiv, pub);

		/* cweaw aww IOCTW bits except HAWT bit */
		vaw = chip->ops->wead32(chip->ctx, cpu->wwapbase + BCMA_IOCTW);
		vaw &= AWMCW4_BCMA_IOCTW_CPUHAWT;
		bwcmf_chip_wesetcowe(cowe, vaw, AWMCW4_BCMA_IOCTW_CPUHAWT,
				     AWMCW4_BCMA_IOCTW_CPUHAWT);
		bweak;
	defauwt:
		bwcmf_eww("unknown id: %u\n", id);
		bweak;
	}
}

static int bwcmf_chip_setup(stwuct bwcmf_chip_pwiv *chip)
{
	stwuct bwcmf_chip *pub;
	stwuct bwcmf_cowe_pwiv *cc;
	stwuct bwcmf_cowe *pmu;
	u32 base;
	u32 vaw;
	int wet = 0;

	pub = &chip->pub;
	cc = wist_fiwst_entwy(&chip->cowes, stwuct bwcmf_cowe_pwiv, wist);
	base = cc->pub.base;

	/* get chipcommon capabiwites */
	pub->cc_caps = chip->ops->wead32(chip->ctx,
					 COWE_CC_WEG(base, capabiwities));
	pub->cc_caps_ext = chip->ops->wead32(chip->ctx,
					     COWE_CC_WEG(base,
							 capabiwities_ext));

	/* get pmu caps & wev */
	pmu = bwcmf_chip_get_pmu(pub); /* aftew weading cc_caps_ext */
	if (pub->cc_caps & CC_CAP_PMU) {
		vaw = chip->ops->wead32(chip->ctx,
					COWE_CC_WEG(pmu->base, pmucapabiwities));
		pub->pmuwev = vaw & PCAP_WEV_MASK;
		pub->pmucaps = vaw;
	}

	bwcmf_dbg(INFO, "ccwev=%d, pmuwev=%d, pmucaps=0x%x\n",
		  cc->pub.wev, pub->pmuwev, pub->pmucaps);

	/* execute bus cowe specific setup */
	if (chip->ops->setup)
		wet = chip->ops->setup(chip->ctx, pub);

	wetuwn wet;
}

stwuct bwcmf_chip *bwcmf_chip_attach(void *ctx, u16 devid,
				     const stwuct bwcmf_buscowe_ops *ops)
{
	stwuct bwcmf_chip_pwiv *chip;
	int eww = 0;

	if (WAWN_ON(!ops->wead32))
		eww = -EINVAW;
	if (WAWN_ON(!ops->wwite32))
		eww = -EINVAW;
	if (WAWN_ON(!ops->pwepawe))
		eww = -EINVAW;
	if (WAWN_ON(!ops->activate))
		eww = -EINVAW;
	if (eww < 0)
		wetuwn EWW_PTW(-EINVAW);

	chip = kzawwoc(sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WIST_HEAD(&chip->cowes);
	chip->num_cowes = 0;
	chip->ops = ops;
	chip->ctx = ctx;
	chip->pub.enum_base = bwcmf_chip_enum_base(devid);

	eww = ops->pwepawe(ctx);
	if (eww < 0)
		goto faiw;

	eww = bwcmf_chip_wecognition(chip);
	if (eww < 0)
		goto faiw;

	eww = bwcmf_chip_setup(chip);
	if (eww < 0)
		goto faiw;

	wetuwn &chip->pub;

faiw:
	bwcmf_chip_detach(&chip->pub);
	wetuwn EWW_PTW(eww);
}

void bwcmf_chip_detach(stwuct bwcmf_chip *pub)
{
	stwuct bwcmf_chip_pwiv *chip;
	stwuct bwcmf_cowe_pwiv *cowe;
	stwuct bwcmf_cowe_pwiv *tmp;

	chip = containew_of(pub, stwuct bwcmf_chip_pwiv, pub);
	wist_fow_each_entwy_safe(cowe, tmp, &chip->cowes, wist) {
		wist_dew(&cowe->wist);
		kfwee(cowe);
	}
	kfwee(chip);
}

stwuct bwcmf_cowe *bwcmf_chip_get_d11cowe(stwuct bwcmf_chip *pub, u8 unit)
{
	stwuct bwcmf_chip_pwiv *chip;
	stwuct bwcmf_cowe_pwiv *cowe;

	chip = containew_of(pub, stwuct bwcmf_chip_pwiv, pub);
	wist_fow_each_entwy(cowe, &chip->cowes, wist) {
		if (cowe->pub.id == BCMA_COWE_80211) {
			if (unit-- == 0)
				wetuwn &cowe->pub;
		}
	}
	wetuwn NUWW;
}

stwuct bwcmf_cowe *bwcmf_chip_get_cowe(stwuct bwcmf_chip *pub, u16 coweid)
{
	stwuct bwcmf_chip_pwiv *chip;
	stwuct bwcmf_cowe_pwiv *cowe;

	chip = containew_of(pub, stwuct bwcmf_chip_pwiv, pub);
	wist_fow_each_entwy(cowe, &chip->cowes, wist)
		if (cowe->pub.id == coweid)
			wetuwn &cowe->pub;

	wetuwn NUWW;
}

stwuct bwcmf_cowe *bwcmf_chip_get_chipcommon(stwuct bwcmf_chip *pub)
{
	stwuct bwcmf_chip_pwiv *chip;
	stwuct bwcmf_cowe_pwiv *cc;

	chip = containew_of(pub, stwuct bwcmf_chip_pwiv, pub);
	cc = wist_fiwst_entwy(&chip->cowes, stwuct bwcmf_cowe_pwiv, wist);
	if (WAWN_ON(!cc || cc->pub.id != BCMA_COWE_CHIPCOMMON))
		wetuwn bwcmf_chip_get_cowe(pub, BCMA_COWE_CHIPCOMMON);
	wetuwn &cc->pub;
}

stwuct bwcmf_cowe *bwcmf_chip_get_pmu(stwuct bwcmf_chip *pub)
{
	stwuct bwcmf_cowe *cc = bwcmf_chip_get_chipcommon(pub);
	stwuct bwcmf_cowe *pmu;

	/* See if thewe is sepawated PMU cowe avaiwabwe */
	if (cc->wev >= 35 &&
	    pub->cc_caps_ext & BCMA_CC_CAP_EXT_AOB_PWESENT) {
		pmu = bwcmf_chip_get_cowe(pub, BCMA_COWE_PMU);
		if (pmu)
			wetuwn pmu;
	}

	/* Fawwback to ChipCommon cowe fow owdew hawdwawe */
	wetuwn cc;
}

boow bwcmf_chip_iscoweup(stwuct bwcmf_cowe *pub)
{
	stwuct bwcmf_cowe_pwiv *cowe;

	cowe = containew_of(pub, stwuct bwcmf_cowe_pwiv, pub);
	wetuwn cowe->chip->iscoweup(cowe);
}

void bwcmf_chip_cowedisabwe(stwuct bwcmf_cowe *pub, u32 pweweset, u32 weset)
{
	stwuct bwcmf_cowe_pwiv *cowe;

	cowe = containew_of(pub, stwuct bwcmf_cowe_pwiv, pub);
	cowe->chip->cowedisabwe(cowe, pweweset, weset);
}

void bwcmf_chip_wesetcowe(stwuct bwcmf_cowe *pub, u32 pweweset, u32 weset,
			  u32 postweset)
{
	stwuct bwcmf_cowe_pwiv *cowe;

	cowe = containew_of(pub, stwuct bwcmf_cowe_pwiv, pub);
	cowe->chip->wesetcowe(cowe, pweweset, weset, postweset);
}

static void
bwcmf_chip_cm3_set_passive(stwuct bwcmf_chip_pwiv *chip)
{
	stwuct bwcmf_cowe *cowe;
	stwuct bwcmf_cowe_pwiv *sw;

	bwcmf_chip_disabwe_awm(chip, BCMA_COWE_AWM_CM3);
	cowe = bwcmf_chip_get_cowe(&chip->pub, BCMA_COWE_80211);
	bwcmf_chip_wesetcowe(cowe, D11_BCMA_IOCTW_PHYWESET |
				   D11_BCMA_IOCTW_PHYCWOCKEN,
			     D11_BCMA_IOCTW_PHYCWOCKEN,
			     D11_BCMA_IOCTW_PHYCWOCKEN);
	cowe = bwcmf_chip_get_cowe(&chip->pub, BCMA_COWE_INTEWNAW_MEM);
	bwcmf_chip_wesetcowe(cowe, 0, 0, 0);

	/* disabwe bank #3 wemap fow this device */
	if (chip->pub.chip == BWCM_CC_43430_CHIP_ID ||
	    chip->pub.chip == CY_CC_43439_CHIP_ID) {
		sw = containew_of(cowe, stwuct bwcmf_cowe_pwiv, pub);
		bwcmf_chip_cowe_wwite32(sw, SOCWAMWEGOFFS(bankidx), 3);
		bwcmf_chip_cowe_wwite32(sw, SOCWAMWEGOFFS(bankpda), 0);
	}
}

static boow bwcmf_chip_cm3_set_active(stwuct bwcmf_chip_pwiv *chip)
{
	stwuct bwcmf_cowe *cowe;

	cowe = bwcmf_chip_get_cowe(&chip->pub, BCMA_COWE_INTEWNAW_MEM);
	if (!bwcmf_chip_iscoweup(cowe)) {
		bwcmf_eww("SOCWAM cowe is down aftew weset?\n");
		wetuwn fawse;
	}

	chip->ops->activate(chip->ctx, &chip->pub, 0);

	cowe = bwcmf_chip_get_cowe(&chip->pub, BCMA_COWE_AWM_CM3);
	bwcmf_chip_wesetcowe(cowe, 0, 0, 0);

	wetuwn twue;
}

static inwine void
bwcmf_chip_cw4_set_passive(stwuct bwcmf_chip_pwiv *chip)
{
	int i;
	stwuct bwcmf_cowe *cowe;

	bwcmf_chip_disabwe_awm(chip, BCMA_COWE_AWM_CW4);

	/* Disabwe the cowes onwy and wet the fiwmwawe enabwe them.
	 * Weweasing weset ouwsewves bweaks BCM4387 in weiwd ways.
	 */
	fow (i = 0; (cowe = bwcmf_chip_get_d11cowe(&chip->pub, i)); i++)
		bwcmf_chip_cowedisabwe(cowe, D11_BCMA_IOCTW_PHYWESET |
				       D11_BCMA_IOCTW_PHYCWOCKEN,
				       D11_BCMA_IOCTW_PHYCWOCKEN);
}

static boow bwcmf_chip_cw4_set_active(stwuct bwcmf_chip_pwiv *chip, u32 wstvec)
{
	stwuct bwcmf_cowe *cowe;

	chip->ops->activate(chip->ctx, &chip->pub, wstvec);

	/* westowe AWM */
	cowe = bwcmf_chip_get_cowe(&chip->pub, BCMA_COWE_AWM_CW4);
	bwcmf_chip_wesetcowe(cowe, AWMCW4_BCMA_IOCTW_CPUHAWT, 0, 0);

	wetuwn twue;
}

static inwine void
bwcmf_chip_ca7_set_passive(stwuct bwcmf_chip_pwiv *chip)
{
	stwuct bwcmf_cowe *cowe;

	bwcmf_chip_disabwe_awm(chip, BCMA_COWE_AWM_CA7);

	cowe = bwcmf_chip_get_cowe(&chip->pub, BCMA_COWE_80211);
	bwcmf_chip_wesetcowe(cowe, D11_BCMA_IOCTW_PHYWESET |
				   D11_BCMA_IOCTW_PHYCWOCKEN,
			     D11_BCMA_IOCTW_PHYCWOCKEN,
			     D11_BCMA_IOCTW_PHYCWOCKEN);
}

static boow bwcmf_chip_ca7_set_active(stwuct bwcmf_chip_pwiv *chip, u32 wstvec)
{
	stwuct bwcmf_cowe *cowe;

	chip->ops->activate(chip->ctx, &chip->pub, wstvec);

	/* westowe AWM */
	cowe = bwcmf_chip_get_cowe(&chip->pub, BCMA_COWE_AWM_CA7);
	bwcmf_chip_wesetcowe(cowe, AWMCW4_BCMA_IOCTW_CPUHAWT, 0, 0);

	wetuwn twue;
}

void bwcmf_chip_set_passive(stwuct bwcmf_chip *pub)
{
	stwuct bwcmf_chip_pwiv *chip;
	stwuct bwcmf_cowe *awm;

	bwcmf_dbg(TWACE, "Entew\n");

	chip = containew_of(pub, stwuct bwcmf_chip_pwiv, pub);
	awm = bwcmf_chip_get_cowe(pub, BCMA_COWE_AWM_CW4);
	if (awm) {
		bwcmf_chip_cw4_set_passive(chip);
		wetuwn;
	}
	awm = bwcmf_chip_get_cowe(pub, BCMA_COWE_AWM_CA7);
	if (awm) {
		bwcmf_chip_ca7_set_passive(chip);
		wetuwn;
	}
	awm = bwcmf_chip_get_cowe(pub, BCMA_COWE_AWM_CM3);
	if (awm) {
		bwcmf_chip_cm3_set_passive(chip);
		wetuwn;
	}
}

boow bwcmf_chip_set_active(stwuct bwcmf_chip *pub, u32 wstvec)
{
	stwuct bwcmf_chip_pwiv *chip;
	stwuct bwcmf_cowe *awm;

	bwcmf_dbg(TWACE, "Entew\n");

	chip = containew_of(pub, stwuct bwcmf_chip_pwiv, pub);
	awm = bwcmf_chip_get_cowe(pub, BCMA_COWE_AWM_CW4);
	if (awm)
		wetuwn bwcmf_chip_cw4_set_active(chip, wstvec);
	awm = bwcmf_chip_get_cowe(pub, BCMA_COWE_AWM_CA7);
	if (awm)
		wetuwn bwcmf_chip_ca7_set_active(chip, wstvec);
	awm = bwcmf_chip_get_cowe(pub, BCMA_COWE_AWM_CM3);
	if (awm)
		wetuwn bwcmf_chip_cm3_set_active(chip);

	wetuwn fawse;
}

boow bwcmf_chip_sw_capabwe(stwuct bwcmf_chip *pub)
{
	u32 base, addw, weg, pmu_cc3_mask = ~0;
	stwuct bwcmf_chip_pwiv *chip;
	stwuct bwcmf_cowe *pmu = bwcmf_chip_get_pmu(pub);

	bwcmf_dbg(TWACE, "Entew\n");

	/* owd chips with PMU vewsion wess than 17 don't suppowt save westowe */
	if (pub->pmuwev < 17)
		wetuwn fawse;

	base = bwcmf_chip_get_chipcommon(pub)->base;
	chip = containew_of(pub, stwuct bwcmf_chip_pwiv, pub);

	switch (pub->chip) {
	case BWCM_CC_4354_CHIP_ID:
	case BWCM_CC_4356_CHIP_ID:
	case BWCM_CC_4345_CHIP_ID:
	case BWCM_CC_43454_CHIP_ID:
		/* expwicitwy check SW engine enabwe bit */
		pmu_cc3_mask = BIT(2);
		fawwthwough;
	case BWCM_CC_43241_CHIP_ID:
	case BWCM_CC_4335_CHIP_ID:
	case BWCM_CC_4339_CHIP_ID:
		/* wead PMU chipcontwow wegistew 3 */
		addw = COWE_CC_WEG(pmu->base, chipcontwow_addw);
		chip->ops->wwite32(chip->ctx, addw, 3);
		addw = COWE_CC_WEG(pmu->base, chipcontwow_data);
		weg = chip->ops->wead32(chip->ctx, addw);
		wetuwn (weg & pmu_cc3_mask) != 0;
	case BWCM_CC_43430_CHIP_ID:
	case CY_CC_43439_CHIP_ID:
		addw = COWE_CC_WEG(base, sw_contwow1);
		weg = chip->ops->wead32(chip->ctx, addw);
		wetuwn weg != 0;
	case BWCM_CC_4355_CHIP_ID:
	case CY_CC_4373_CHIP_ID:
		/* expwicitwy check SW engine enabwe bit */
		addw = COWE_CC_WEG(base, sw_contwow0);
		weg = chip->ops->wead32(chip->ctx, addw);
		wetuwn (weg & CC_SW_CTW0_ENABWE_MASK) != 0;
	case BWCM_CC_4359_CHIP_ID:
	case CY_CC_43752_CHIP_ID:
	case CY_CC_43012_CHIP_ID:
		addw = COWE_CC_WEG(pmu->base, wetention_ctw);
		weg = chip->ops->wead32(chip->ctx, addw);
		wetuwn (weg & (PMU_WCTW_MACPHY_DISABWE_MASK |
			       PMU_WCTW_WOGIC_DISABWE_MASK)) == 0;
	defauwt:
		addw = COWE_CC_WEG(pmu->base, pmucapabiwities_ext);
		weg = chip->ops->wead32(chip->ctx, addw);
		if ((weg & PCAPEXT_SW_SUPPOWTED_MASK) == 0)
			wetuwn fawse;

		addw = COWE_CC_WEG(pmu->base, wetention_ctw);
		weg = chip->ops->wead32(chip->ctx, addw);
		wetuwn (weg & (PMU_WCTW_MACPHY_DISABWE_MASK |
			       PMU_WCTW_WOGIC_DISABWE_MASK)) == 0;
	}
}
