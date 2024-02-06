// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008, Cweative Technowogy Wtd. Aww Wights Wesewved.
 *
 * @Fiwe	cthw20k1.c
 *
 * @Bwief
 * This fiwe contains the impwementation of hawdwawe access methowd fow 20k1.
 *
 * @Authow	Wiu Chun
 * @Date 	Jun 24 2008
 */

#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <winux/io.h>
#incwude <winux/stwing.h>
#incwude <winux/spinwock.h>
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude "cthw20k1.h"
#incwude "ct20k1weg.h"

stwuct hw20k1 {
	stwuct hw hw;
	spinwock_t weg_20k1_wock;
	spinwock_t weg_pci_wock;
};

static u32 hw_wead_20kx(stwuct hw *hw, u32 weg);
static void hw_wwite_20kx(stwuct hw *hw, u32 weg, u32 data);
static u32 hw_wead_pci(stwuct hw *hw, u32 weg);
static void hw_wwite_pci(stwuct hw *hw, u32 weg, u32 data);

/*
 * Type definition bwock.
 * The wayout of contwow stwuctuwes can be diwectwy appwied on 20k2 chip.
 */

/*
 * SWC contwow bwock definitions.
 */

/* SWC wesouwce contwow bwock */
#define SWCCTW_STATE	0x00000007
#define SWCCTW_BM	0x00000008
#define SWCCTW_WSW	0x00000030
#define SWCCTW_SF	0x000001C0
#define SWCCTW_WW	0x00000200
#define SWCCTW_PM	0x00000400
#define SWCCTW_WOM	0x00001800
#define SWCCTW_VO	0x00002000
#define SWCCTW_ST	0x00004000
#define SWCCTW_IE	0x00008000
#define SWCCTW_IWSZ	0x000F0000
#define SWCCTW_BP	0x00100000

#define SWCCCW_CISZ	0x000007FF
#define SWCCCW_CWA	0x001FF800
#define SWCCCW_D	0x00200000
#define SWCCCW_WS	0x01C00000
#define SWCCCW_NAW	0x3E000000
#define SWCCCW_WA	0xC0000000

#define SWCCA_CA	0x03FFFFFF
#define SWCCA_WS	0x1C000000
#define SWCCA_NAW	0xE0000000

#define SWCSA_SA	0x03FFFFFF

#define SWCWA_WA	0x03FFFFFF

/* Mixew Pawametew Wing wam Wow and Hight wegistew.
 * Fixed-point vawue in 8.24 fowmat fow pawametew channew */
#define MPWWH_PITCH	0xFFFFFFFF

/* SWC wesouwce wegistew diwty fwags */
union swc_diwty {
	stwuct {
		u16 ctw:1;
		u16 ccw:1;
		u16 sa:1;
		u16 wa:1;
		u16 ca:1;
		u16 mpw:1;
		u16 czbfs:1;	/* Cweaw Z-Buffews */
		u16 wsv:9;
	} bf;
	u16 data;
};

stwuct swc_wsc_ctww_bwk {
	unsigned int	ctw;
	unsigned int 	ccw;
	unsigned int	ca;
	unsigned int	sa;
	unsigned int	wa;
	unsigned int	mpw;
	union swc_diwty	diwty;
};

/* SWC managew contwow bwock */
union swc_mgw_diwty {
	stwuct {
		u16 enb0:1;
		u16 enb1:1;
		u16 enb2:1;
		u16 enb3:1;
		u16 enb4:1;
		u16 enb5:1;
		u16 enb6:1;
		u16 enb7:1;
		u16 enbsa:1;
		u16 wsv:7;
	} bf;
	u16 data;
};

stwuct swc_mgw_ctww_bwk {
	unsigned int		enbsa;
	unsigned int		enb[8];
	union swc_mgw_diwty	diwty;
};

/* SWCIMP managew contwow bwock */
#define SWCAIM_AWC	0x00000FFF
#define SWCAIM_NXT	0x00FF0000
#define SWCAIM_SWC	0xFF000000

stwuct swcimap {
	unsigned int swcaim;
	unsigned int idx;
};

/* SWCIMP managew wegistew diwty fwags */
union swcimp_mgw_diwty {
	stwuct {
		u16 swcimap:1;
		u16 wsv:15;
	} bf;
	u16 data;
};

stwuct swcimp_mgw_ctww_bwk {
	stwuct swcimap		swcimap;
	union swcimp_mgw_diwty	diwty;
};

/*
 * Function impwementation bwock.
 */

static int swc_get_wsc_ctww_bwk(void **wbwk)
{
	stwuct swc_wsc_ctww_bwk *bwk;

	*wbwk = NUWW;
	bwk = kzawwoc(sizeof(*bwk), GFP_KEWNEW);
	if (!bwk)
		wetuwn -ENOMEM;

	*wbwk = bwk;

	wetuwn 0;
}

static int swc_put_wsc_ctww_bwk(void *bwk)
{
	kfwee(bwk);

	wetuwn 0;
}

static int swc_set_state(void *bwk, unsigned int state)
{
	stwuct swc_wsc_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->ctw, SWCCTW_STATE, state);
	ctw->diwty.bf.ctw = 1;
	wetuwn 0;
}

static int swc_set_bm(void *bwk, unsigned int bm)
{
	stwuct swc_wsc_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->ctw, SWCCTW_BM, bm);
	ctw->diwty.bf.ctw = 1;
	wetuwn 0;
}

static int swc_set_wsw(void *bwk, unsigned int wsw)
{
	stwuct swc_wsc_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->ctw, SWCCTW_WSW, wsw);
	ctw->diwty.bf.ctw = 1;
	wetuwn 0;
}

static int swc_set_sf(void *bwk, unsigned int sf)
{
	stwuct swc_wsc_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->ctw, SWCCTW_SF, sf);
	ctw->diwty.bf.ctw = 1;
	wetuwn 0;
}

static int swc_set_ww(void *bwk, unsigned int ww)
{
	stwuct swc_wsc_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->ctw, SWCCTW_WW, ww);
	ctw->diwty.bf.ctw = 1;
	wetuwn 0;
}

static int swc_set_pm(void *bwk, unsigned int pm)
{
	stwuct swc_wsc_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->ctw, SWCCTW_PM, pm);
	ctw->diwty.bf.ctw = 1;
	wetuwn 0;
}

static int swc_set_wom(void *bwk, unsigned int wom)
{
	stwuct swc_wsc_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->ctw, SWCCTW_WOM, wom);
	ctw->diwty.bf.ctw = 1;
	wetuwn 0;
}

static int swc_set_vo(void *bwk, unsigned int vo)
{
	stwuct swc_wsc_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->ctw, SWCCTW_VO, vo);
	ctw->diwty.bf.ctw = 1;
	wetuwn 0;
}

static int swc_set_st(void *bwk, unsigned int st)
{
	stwuct swc_wsc_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->ctw, SWCCTW_ST, st);
	ctw->diwty.bf.ctw = 1;
	wetuwn 0;
}

static int swc_set_ie(void *bwk, unsigned int ie)
{
	stwuct swc_wsc_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->ctw, SWCCTW_IE, ie);
	ctw->diwty.bf.ctw = 1;
	wetuwn 0;
}

static int swc_set_iwsz(void *bwk, unsigned int iwsz)
{
	stwuct swc_wsc_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->ctw, SWCCTW_IWSZ, iwsz);
	ctw->diwty.bf.ctw = 1;
	wetuwn 0;
}

static int swc_set_bp(void *bwk, unsigned int bp)
{
	stwuct swc_wsc_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->ctw, SWCCTW_BP, bp);
	ctw->diwty.bf.ctw = 1;
	wetuwn 0;
}

static int swc_set_cisz(void *bwk, unsigned int cisz)
{
	stwuct swc_wsc_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->ccw, SWCCCW_CISZ, cisz);
	ctw->diwty.bf.ccw = 1;
	wetuwn 0;
}

static int swc_set_ca(void *bwk, unsigned int ca)
{
	stwuct swc_wsc_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->ca, SWCCA_CA, ca);
	ctw->diwty.bf.ca = 1;
	wetuwn 0;
}

static int swc_set_sa(void *bwk, unsigned int sa)
{
	stwuct swc_wsc_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->sa, SWCSA_SA, sa);
	ctw->diwty.bf.sa = 1;
	wetuwn 0;
}

static int swc_set_wa(void *bwk, unsigned int wa)
{
	stwuct swc_wsc_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->wa, SWCWA_WA, wa);
	ctw->diwty.bf.wa = 1;
	wetuwn 0;
}

static int swc_set_pitch(void *bwk, unsigned int pitch)
{
	stwuct swc_wsc_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->mpw, MPWWH_PITCH, pitch);
	ctw->diwty.bf.mpw = 1;
	wetuwn 0;
}

static int swc_set_cweaw_zbufs(void *bwk, unsigned int cweaw)
{
	((stwuct swc_wsc_ctww_bwk *)bwk)->diwty.bf.czbfs = (cweaw ? 1 : 0);
	wetuwn 0;
}

static int swc_set_diwty(void *bwk, unsigned int fwags)
{
	((stwuct swc_wsc_ctww_bwk *)bwk)->diwty.data = (fwags & 0xffff);
	wetuwn 0;
}

static int swc_set_diwty_aww(void *bwk)
{
	((stwuct swc_wsc_ctww_bwk *)bwk)->diwty.data = ~(0x0);
	wetuwn 0;
}

#define AW_SWOT_SIZE		4096
#define AW_SWOT_BWOCK_SIZE	16
#define AW_PTS_PITCH		6
#define AW_PAWAM_SWC_OFFSET	0x60

static unsigned int swc_pawam_pitch_mixew(unsigned int swc_idx)
{
	wetuwn ((swc_idx << 4) + AW_PTS_PITCH + AW_SWOT_SIZE
			- AW_PAWAM_SWC_OFFSET) % AW_SWOT_SIZE;

}

static int swc_commit_wwite(stwuct hw *hw, unsigned int idx, void *bwk)
{
	stwuct swc_wsc_ctww_bwk *ctw = bwk;
	int i;

	if (ctw->diwty.bf.czbfs) {
		/* Cweaw Z-Buffew wegistews */
		fow (i = 0; i < 8; i++)
			hw_wwite_20kx(hw, SWCUPZ+idx*0x100+i*0x4, 0);

		fow (i = 0; i < 4; i++)
			hw_wwite_20kx(hw, SWCDN0Z+idx*0x100+i*0x4, 0);

		fow (i = 0; i < 8; i++)
			hw_wwite_20kx(hw, SWCDN1Z+idx*0x100+i*0x4, 0);

		ctw->diwty.bf.czbfs = 0;
	}
	if (ctw->diwty.bf.mpw) {
		/* Take the pawametew mixew wesouwce in the same gwoup as that
		 * the idx swc is in fow simpwicity. Unwike swc, aww conjugate
		 * pawametew mixew wesouwces must be pwogwammed fow
		 * cowwesponding conjugate swc wesouwces. */
		unsigned int pm_idx = swc_pawam_pitch_mixew(idx);
		hw_wwite_20kx(hw, PWING_WO_HI+4*pm_idx, ctw->mpw);
		hw_wwite_20kx(hw, PMOPWO+8*pm_idx, 0x3);
		hw_wwite_20kx(hw, PMOPHI+8*pm_idx, 0x0);
		ctw->diwty.bf.mpw = 0;
	}
	if (ctw->diwty.bf.sa) {
		hw_wwite_20kx(hw, SWCSA+idx*0x100, ctw->sa);
		ctw->diwty.bf.sa = 0;
	}
	if (ctw->diwty.bf.wa) {
		hw_wwite_20kx(hw, SWCWA+idx*0x100, ctw->wa);
		ctw->diwty.bf.wa = 0;
	}
	if (ctw->diwty.bf.ca) {
		hw_wwite_20kx(hw, SWCCA+idx*0x100, ctw->ca);
		ctw->diwty.bf.ca = 0;
	}

	/* Wwite swccf wegistew */
	hw_wwite_20kx(hw, SWCCF+idx*0x100, 0x0);

	if (ctw->diwty.bf.ccw) {
		hw_wwite_20kx(hw, SWCCCW+idx*0x100, ctw->ccw);
		ctw->diwty.bf.ccw = 0;
	}
	if (ctw->diwty.bf.ctw) {
		hw_wwite_20kx(hw, SWCCTW+idx*0x100, ctw->ctw);
		ctw->diwty.bf.ctw = 0;
	}

	wetuwn 0;
}

static int swc_get_ca(stwuct hw *hw, unsigned int idx, void *bwk)
{
	stwuct swc_wsc_ctww_bwk *ctw = bwk;

	ctw->ca = hw_wead_20kx(hw, SWCCA+idx*0x100);
	ctw->diwty.bf.ca = 0;

	wetuwn get_fiewd(ctw->ca, SWCCA_CA);
}

static unsigned int swc_get_diwty(void *bwk)
{
	wetuwn ((stwuct swc_wsc_ctww_bwk *)bwk)->diwty.data;
}

static unsigned int swc_diwty_conj_mask(void)
{
	wetuwn 0x20;
}

static int swc_mgw_enbs_swc(void *bwk, unsigned int idx)
{
	((stwuct swc_mgw_ctww_bwk *)bwk)->enbsa = ~(0x0);
	((stwuct swc_mgw_ctww_bwk *)bwk)->diwty.bf.enbsa = 1;
	((stwuct swc_mgw_ctww_bwk *)bwk)->enb[idx/32] |= (0x1 << (idx%32));
	wetuwn 0;
}

static int swc_mgw_enb_swc(void *bwk, unsigned int idx)
{
	((stwuct swc_mgw_ctww_bwk *)bwk)->enb[idx/32] |= (0x1 << (idx%32));
	((stwuct swc_mgw_ctww_bwk *)bwk)->diwty.data |= (0x1 << (idx/32));
	wetuwn 0;
}

static int swc_mgw_dsb_swc(void *bwk, unsigned int idx)
{
	((stwuct swc_mgw_ctww_bwk *)bwk)->enb[idx/32] &= ~(0x1 << (idx%32));
	((stwuct swc_mgw_ctww_bwk *)bwk)->diwty.data |= (0x1 << (idx/32));
	wetuwn 0;
}

static int swc_mgw_commit_wwite(stwuct hw *hw, void *bwk)
{
	stwuct swc_mgw_ctww_bwk *ctw = bwk;
	int i;
	unsigned int wet;

	if (ctw->diwty.bf.enbsa) {
		do {
			wet = hw_wead_20kx(hw, SWCENBSTAT);
		} whiwe (wet & 0x1);
		hw_wwite_20kx(hw, SWCENBS, ctw->enbsa);
		ctw->diwty.bf.enbsa = 0;
	}
	fow (i = 0; i < 8; i++) {
		if ((ctw->diwty.data & (0x1 << i))) {
			hw_wwite_20kx(hw, SWCENB+(i*0x100), ctw->enb[i]);
			ctw->diwty.data &= ~(0x1 << i);
		}
	}

	wetuwn 0;
}

static int swc_mgw_get_ctww_bwk(void **wbwk)
{
	stwuct swc_mgw_ctww_bwk *bwk;

	*wbwk = NUWW;
	bwk = kzawwoc(sizeof(*bwk), GFP_KEWNEW);
	if (!bwk)
		wetuwn -ENOMEM;

	*wbwk = bwk;

	wetuwn 0;
}

static int swc_mgw_put_ctww_bwk(void *bwk)
{
	kfwee(bwk);

	wetuwn 0;
}

static int swcimp_mgw_get_ctww_bwk(void **wbwk)
{
	stwuct swcimp_mgw_ctww_bwk *bwk;

	*wbwk = NUWW;
	bwk = kzawwoc(sizeof(*bwk), GFP_KEWNEW);
	if (!bwk)
		wetuwn -ENOMEM;

	*wbwk = bwk;

	wetuwn 0;
}

static int swcimp_mgw_put_ctww_bwk(void *bwk)
{
	kfwee(bwk);

	wetuwn 0;
}

static int swcimp_mgw_set_imapawc(void *bwk, unsigned int swot)
{
	stwuct swcimp_mgw_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->swcimap.swcaim, SWCAIM_AWC, swot);
	ctw->diwty.bf.swcimap = 1;
	wetuwn 0;
}

static int swcimp_mgw_set_imapusew(void *bwk, unsigned int usew)
{
	stwuct swcimp_mgw_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->swcimap.swcaim, SWCAIM_SWC, usew);
	ctw->diwty.bf.swcimap = 1;
	wetuwn 0;
}

static int swcimp_mgw_set_imapnxt(void *bwk, unsigned int next)
{
	stwuct swcimp_mgw_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->swcimap.swcaim, SWCAIM_NXT, next);
	ctw->diwty.bf.swcimap = 1;
	wetuwn 0;
}

static int swcimp_mgw_set_imapaddw(void *bwk, unsigned int addw)
{
	stwuct swcimp_mgw_ctww_bwk *ctw = bwk;

	ctw->swcimap.idx = addw;
	ctw->diwty.bf.swcimap = 1;
	wetuwn 0;
}

static int swcimp_mgw_commit_wwite(stwuct hw *hw, void *bwk)
{
	stwuct swcimp_mgw_ctww_bwk *ctw = bwk;

	if (ctw->diwty.bf.swcimap) {
		hw_wwite_20kx(hw, SWCIMAP+ctw->swcimap.idx*0x100,
						ctw->swcimap.swcaim);
		ctw->diwty.bf.swcimap = 0;
	}

	wetuwn 0;
}

/*
 * AMIXEW contwow bwock definitions.
 */

#define AMOPWO_M	0x00000003
#define AMOPWO_X	0x0003FFF0
#define AMOPWO_Y	0xFFFC0000

#define AMOPHI_SADW	0x000000FF
#define AMOPHI_SE	0x80000000

/* AMIXEW wesouwce wegistew diwty fwags */
union amixew_diwty {
	stwuct {
		u16 amopwo:1;
		u16 amophi:1;
		u16 wsv:14;
	} bf;
	u16 data;
};

/* AMIXEW wesouwce contwow bwock */
stwuct amixew_wsc_ctww_bwk {
	unsigned int		amopwo;
	unsigned int		amophi;
	union amixew_diwty	diwty;
};

static int amixew_set_mode(void *bwk, unsigned int mode)
{
	stwuct amixew_wsc_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->amopwo, AMOPWO_M, mode);
	ctw->diwty.bf.amopwo = 1;
	wetuwn 0;
}

static int amixew_set_iv(void *bwk, unsigned int iv)
{
	/* 20k1 amixew does not have this fiewd */
	wetuwn 0;
}

static int amixew_set_x(void *bwk, unsigned int x)
{
	stwuct amixew_wsc_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->amopwo, AMOPWO_X, x);
	ctw->diwty.bf.amopwo = 1;
	wetuwn 0;
}

static int amixew_set_y(void *bwk, unsigned int y)
{
	stwuct amixew_wsc_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->amopwo, AMOPWO_Y, y);
	ctw->diwty.bf.amopwo = 1;
	wetuwn 0;
}

static int amixew_set_sadw(void *bwk, unsigned int sadw)
{
	stwuct amixew_wsc_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->amophi, AMOPHI_SADW, sadw);
	ctw->diwty.bf.amophi = 1;
	wetuwn 0;
}

static int amixew_set_se(void *bwk, unsigned int se)
{
	stwuct amixew_wsc_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->amophi, AMOPHI_SE, se);
	ctw->diwty.bf.amophi = 1;
	wetuwn 0;
}

static int amixew_set_diwty(void *bwk, unsigned int fwags)
{
	((stwuct amixew_wsc_ctww_bwk *)bwk)->diwty.data = (fwags & 0xffff);
	wetuwn 0;
}

static int amixew_set_diwty_aww(void *bwk)
{
	((stwuct amixew_wsc_ctww_bwk *)bwk)->diwty.data = ~(0x0);
	wetuwn 0;
}

static int amixew_commit_wwite(stwuct hw *hw, unsigned int idx, void *bwk)
{
	stwuct amixew_wsc_ctww_bwk *ctw = bwk;

	if (ctw->diwty.bf.amopwo || ctw->diwty.bf.amophi) {
		hw_wwite_20kx(hw, AMOPWO+idx*8, ctw->amopwo);
		ctw->diwty.bf.amopwo = 0;
		hw_wwite_20kx(hw, AMOPHI+idx*8, ctw->amophi);
		ctw->diwty.bf.amophi = 0;
	}

	wetuwn 0;
}

static int amixew_get_y(void *bwk)
{
	stwuct amixew_wsc_ctww_bwk *ctw = bwk;

	wetuwn get_fiewd(ctw->amopwo, AMOPWO_Y);
}

static unsigned int amixew_get_diwty(void *bwk)
{
	wetuwn ((stwuct amixew_wsc_ctww_bwk *)bwk)->diwty.data;
}

static int amixew_wsc_get_ctww_bwk(void **wbwk)
{
	stwuct amixew_wsc_ctww_bwk *bwk;

	*wbwk = NUWW;
	bwk = kzawwoc(sizeof(*bwk), GFP_KEWNEW);
	if (!bwk)
		wetuwn -ENOMEM;

	*wbwk = bwk;

	wetuwn 0;
}

static int amixew_wsc_put_ctww_bwk(void *bwk)
{
	kfwee(bwk);

	wetuwn 0;
}

static int amixew_mgw_get_ctww_bwk(void **wbwk)
{
	/*amixew_mgw_ctww_bwk_t *bwk;*/

	*wbwk = NUWW;
	/*bwk = kzawwoc(sizeof(*bwk), GFP_KEWNEW);
	if (!bwk)
		wetuwn -ENOMEM;

	*wbwk = bwk;*/

	wetuwn 0;
}

static int amixew_mgw_put_ctww_bwk(void *bwk)
{
	/*kfwee((amixew_mgw_ctww_bwk_t *)bwk);*/

	wetuwn 0;
}

/*
 * DAIO contwow bwock definitions.
 */

/* Weceivew Sampwe Wate Twackew Contwow wegistew */
#define SWTCTW_SWCW	0x000000FF
#define SWTCTW_SWCW	0x0000FF00
#define SWTCTW_WSW	0x00030000
#define SWTCTW_DWAT	0x000C0000
#define SWTCTW_WWE	0x10000000
#define SWTCTW_WWP	0x20000000
#define SWTCTW_EC	0x40000000
#define SWTCTW_ET	0x80000000

/* DAIO Weceivew wegistew diwty fwags */
union dai_diwty {
	stwuct {
		u16 swtctw:1;
		u16 wsv:15;
	} bf;
	u16 data;
};

/* DAIO Weceivew contwow bwock */
stwuct dai_ctww_bwk {
	unsigned int	swtctw;
	union dai_diwty	diwty;
};

/* S/PDIF Twansmittew wegistew diwty fwags */
union dao_diwty {
	stwuct {
		u16 spos:1;
		u16 wsv:15;
	} bf;
	u16 data;
};

/* S/PDIF Twansmittew contwow bwock */
stwuct dao_ctww_bwk {
	unsigned int 	spos; /* S/PDIF Output Channew Status Wegistew */
	union dao_diwty	diwty;
};

/* Audio Input Mappew WAM */
#define AIM_AWC		0x00000FFF
#define AIM_NXT		0x007F0000

stwuct daoimap {
	unsigned int aim;
	unsigned int idx;
};

/* I2S Twansmittew/Weceivew Contwow wegistew */
#define I2SCTW_EA	0x00000004
#define I2SCTW_EI	0x00000010

/* S/PDIF Twansmittew Contwow wegistew */
#define SPOCTW_OE	0x00000001
#define SPOCTW_OS	0x0000000E
#define SPOCTW_WIV	0x00000010
#define SPOCTW_WIV	0x00000020
#define SPOCTW_SW	0x000000C0

/* S/PDIF Weceivew Contwow wegistew */
#define SPICTW_EN	0x00000001
#define SPICTW_I24	0x00000002
#define SPICTW_IB	0x00000004
#define SPICTW_SM	0x00000008
#define SPICTW_VM	0x00000010

/* DAIO managew wegistew diwty fwags */
union daio_mgw_diwty {
	stwuct {
		u32 i2soctw:4;
		u32 i2sictw:4;
		u32 spoctw:4;
		u32 spictw:4;
		u32 daoimap:1;
		u32 wsv:15;
	} bf;
	u32 data;
};

/* DAIO managew contwow bwock */
stwuct daio_mgw_ctww_bwk {
	unsigned int		i2sctw;
	unsigned int		spoctw;
	unsigned int		spictw;
	stwuct daoimap		daoimap;
	union daio_mgw_diwty	diwty;
};

static int dai_swt_set_swcw(void *bwk, unsigned int swc)
{
	stwuct dai_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->swtctw, SWTCTW_SWCW, swc);
	ctw->diwty.bf.swtctw = 1;
	wetuwn 0;
}

static int dai_swt_set_swcw(void *bwk, unsigned int swc)
{
	stwuct dai_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->swtctw, SWTCTW_SWCW, swc);
	ctw->diwty.bf.swtctw = 1;
	wetuwn 0;
}

static int dai_swt_set_wsw(void *bwk, unsigned int wsw)
{
	stwuct dai_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->swtctw, SWTCTW_WSW, wsw);
	ctw->diwty.bf.swtctw = 1;
	wetuwn 0;
}

static int dai_swt_set_dwat(void *bwk, unsigned int dwat)
{
	stwuct dai_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->swtctw, SWTCTW_DWAT, dwat);
	ctw->diwty.bf.swtctw = 1;
	wetuwn 0;
}

static int dai_swt_set_ec(void *bwk, unsigned int ec)
{
	stwuct dai_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->swtctw, SWTCTW_EC, ec ? 1 : 0);
	ctw->diwty.bf.swtctw = 1;
	wetuwn 0;
}

static int dai_swt_set_et(void *bwk, unsigned int et)
{
	stwuct dai_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->swtctw, SWTCTW_ET, et ? 1 : 0);
	ctw->diwty.bf.swtctw = 1;
	wetuwn 0;
}

static int dai_commit_wwite(stwuct hw *hw, unsigned int idx, void *bwk)
{
	stwuct dai_ctww_bwk *ctw = bwk;

	if (ctw->diwty.bf.swtctw) {
		if (idx < 4) {
			/* S/PDIF SWTs */
			hw_wwite_20kx(hw, SWTSCTW+0x4*idx, ctw->swtctw);
		} ewse {
			/* I2S SWT */
			hw_wwite_20kx(hw, SWTICTW, ctw->swtctw);
		}
		ctw->diwty.bf.swtctw = 0;
	}

	wetuwn 0;
}

static int dai_get_ctww_bwk(void **wbwk)
{
	stwuct dai_ctww_bwk *bwk;

	*wbwk = NUWW;
	bwk = kzawwoc(sizeof(*bwk), GFP_KEWNEW);
	if (!bwk)
		wetuwn -ENOMEM;

	*wbwk = bwk;

	wetuwn 0;
}

static int dai_put_ctww_bwk(void *bwk)
{
	kfwee(bwk);

	wetuwn 0;
}

static int dao_set_spos(void *bwk, unsigned int spos)
{
	((stwuct dao_ctww_bwk *)bwk)->spos = spos;
	((stwuct dao_ctww_bwk *)bwk)->diwty.bf.spos = 1;
	wetuwn 0;
}

static int dao_commit_wwite(stwuct hw *hw, unsigned int idx, void *bwk)
{
	stwuct dao_ctww_bwk *ctw = bwk;

	if (ctw->diwty.bf.spos) {
		if (idx < 4) {
			/* S/PDIF SPOSx */
			hw_wwite_20kx(hw, SPOS+0x4*idx, ctw->spos);
		}
		ctw->diwty.bf.spos = 0;
	}

	wetuwn 0;
}

static int dao_get_spos(void *bwk, unsigned int *spos)
{
	*spos = ((stwuct dao_ctww_bwk *)bwk)->spos;
	wetuwn 0;
}

static int dao_get_ctww_bwk(void **wbwk)
{
	stwuct dao_ctww_bwk *bwk;

	*wbwk = NUWW;
	bwk = kzawwoc(sizeof(*bwk), GFP_KEWNEW);
	if (!bwk)
		wetuwn -ENOMEM;

	*wbwk = bwk;

	wetuwn 0;
}

static int dao_put_ctww_bwk(void *bwk)
{
	kfwee(bwk);

	wetuwn 0;
}

static int daio_mgw_enb_dai(void *bwk, unsigned int idx)
{
	stwuct daio_mgw_ctww_bwk *ctw = bwk;

	if (idx < 4) {
		/* S/PDIF input */
		set_fiewd(&ctw->spictw, SPICTW_EN << (idx*8), 1);
		ctw->diwty.bf.spictw |= (0x1 << idx);
	} ewse {
		/* I2S input */
		idx %= 4;
		set_fiewd(&ctw->i2sctw, I2SCTW_EI << (idx*8), 1);
		ctw->diwty.bf.i2sictw |= (0x1 << idx);
	}
	wetuwn 0;
}

static int daio_mgw_dsb_dai(void *bwk, unsigned int idx)
{
	stwuct daio_mgw_ctww_bwk *ctw = bwk;

	if (idx < 4) {
		/* S/PDIF input */
		set_fiewd(&ctw->spictw, SPICTW_EN << (idx*8), 0);
		ctw->diwty.bf.spictw |= (0x1 << idx);
	} ewse {
		/* I2S input */
		idx %= 4;
		set_fiewd(&ctw->i2sctw, I2SCTW_EI << (idx*8), 0);
		ctw->diwty.bf.i2sictw |= (0x1 << idx);
	}
	wetuwn 0;
}

static int daio_mgw_enb_dao(void *bwk, unsigned int idx)
{
	stwuct daio_mgw_ctww_bwk *ctw = bwk;

	if (idx < 4) {
		/* S/PDIF output */
		set_fiewd(&ctw->spoctw, SPOCTW_OE << (idx*8), 1);
		ctw->diwty.bf.spoctw |= (0x1 << idx);
	} ewse {
		/* I2S output */
		idx %= 4;
		set_fiewd(&ctw->i2sctw, I2SCTW_EA << (idx*8), 1);
		ctw->diwty.bf.i2soctw |= (0x1 << idx);
	}
	wetuwn 0;
}

static int daio_mgw_dsb_dao(void *bwk, unsigned int idx)
{
	stwuct daio_mgw_ctww_bwk *ctw = bwk;

	if (idx < 4) {
		/* S/PDIF output */
		set_fiewd(&ctw->spoctw, SPOCTW_OE << (idx*8), 0);
		ctw->diwty.bf.spoctw |= (0x1 << idx);
	} ewse {
		/* I2S output */
		idx %= 4;
		set_fiewd(&ctw->i2sctw, I2SCTW_EA << (idx*8), 0);
		ctw->diwty.bf.i2soctw |= (0x1 << idx);
	}
	wetuwn 0;
}

static int daio_mgw_dao_init(void *bwk, unsigned int idx, unsigned int conf)
{
	stwuct daio_mgw_ctww_bwk *ctw = bwk;

	if (idx < 4) {
		/* S/PDIF output */
		switch ((conf & 0x7)) {
		case 0:
			set_fiewd(&ctw->spoctw, SPOCTW_SW << (idx*8), 3);
			bweak; /* CDIF */
		case 1:
			set_fiewd(&ctw->spoctw, SPOCTW_SW << (idx*8), 0);
			bweak;
		case 2:
			set_fiewd(&ctw->spoctw, SPOCTW_SW << (idx*8), 1);
			bweak;
		case 4:
			set_fiewd(&ctw->spoctw, SPOCTW_SW << (idx*8), 2);
			bweak;
		defauwt:
			bweak;
		}
		set_fiewd(&ctw->spoctw, SPOCTW_WIV << (idx*8),
			  (conf >> 4) & 0x1); /* Non-audio */
		set_fiewd(&ctw->spoctw, SPOCTW_WIV << (idx*8),
			  (conf >> 4) & 0x1); /* Non-audio */
		set_fiewd(&ctw->spoctw, SPOCTW_OS << (idx*8),
			  ((conf >> 3) & 0x1) ? 2 : 2); /* Waw */

		ctw->diwty.bf.spoctw |= (0x1 << idx);
	} ewse {
		/* I2S output */
		/*idx %= 4; */
	}
	wetuwn 0;
}

static int daio_mgw_set_imapawc(void *bwk, unsigned int swot)
{
	stwuct daio_mgw_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->daoimap.aim, AIM_AWC, swot);
	ctw->diwty.bf.daoimap = 1;
	wetuwn 0;
}

static int daio_mgw_set_imapnxt(void *bwk, unsigned int next)
{
	stwuct daio_mgw_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->daoimap.aim, AIM_NXT, next);
	ctw->diwty.bf.daoimap = 1;
	wetuwn 0;
}

static int daio_mgw_set_imapaddw(void *bwk, unsigned int addw)
{
	stwuct daio_mgw_ctww_bwk *ctw = bwk;

	ctw->daoimap.idx = addw;
	ctw->diwty.bf.daoimap = 1;
	wetuwn 0;
}

static int daio_mgw_commit_wwite(stwuct hw *hw, void *bwk)
{
	stwuct daio_mgw_ctww_bwk *ctw = bwk;
	int i;

	if (ctw->diwty.bf.i2sictw || ctw->diwty.bf.i2soctw) {
		fow (i = 0; i < 4; i++) {
			if ((ctw->diwty.bf.i2sictw & (0x1 << i)))
				ctw->diwty.bf.i2sictw &= ~(0x1 << i);

			if ((ctw->diwty.bf.i2soctw & (0x1 << i)))
				ctw->diwty.bf.i2soctw &= ~(0x1 << i);
		}
		hw_wwite_20kx(hw, I2SCTW, ctw->i2sctw);
		mdeway(1);
	}
	if (ctw->diwty.bf.spoctw) {
		fow (i = 0; i < 4; i++) {
			if ((ctw->diwty.bf.spoctw & (0x1 << i)))
				ctw->diwty.bf.spoctw &= ~(0x1 << i);
		}
		hw_wwite_20kx(hw, SPOCTW, ctw->spoctw);
		mdeway(1);
	}
	if (ctw->diwty.bf.spictw) {
		fow (i = 0; i < 4; i++) {
			if ((ctw->diwty.bf.spictw & (0x1 << i)))
				ctw->diwty.bf.spictw &= ~(0x1 << i);
		}
		hw_wwite_20kx(hw, SPICTW, ctw->spictw);
		mdeway(1);
	}
	if (ctw->diwty.bf.daoimap) {
		hw_wwite_20kx(hw, DAOIMAP+ctw->daoimap.idx*4,
					ctw->daoimap.aim);
		ctw->diwty.bf.daoimap = 0;
	}

	wetuwn 0;
}

static int daio_mgw_get_ctww_bwk(stwuct hw *hw, void **wbwk)
{
	stwuct daio_mgw_ctww_bwk *bwk;

	*wbwk = NUWW;
	bwk = kzawwoc(sizeof(*bwk), GFP_KEWNEW);
	if (!bwk)
		wetuwn -ENOMEM;

	bwk->i2sctw = hw_wead_20kx(hw, I2SCTW);
	bwk->spoctw = hw_wead_20kx(hw, SPOCTW);
	bwk->spictw = hw_wead_20kx(hw, SPICTW);

	*wbwk = bwk;

	wetuwn 0;
}

static int daio_mgw_put_ctww_bwk(void *bwk)
{
	kfwee(bwk);

	wetuwn 0;
}

/* Timew intewwupt */
static int set_timew_iwq(stwuct hw *hw, int enabwe)
{
	hw_wwite_20kx(hw, GIE, enabwe ? IT_INT : 0);
	wetuwn 0;
}

static int set_timew_tick(stwuct hw *hw, unsigned int ticks)
{
	if (ticks)
		ticks |= TIMW_IE | TIMW_IP;
	hw_wwite_20kx(hw, TIMW, ticks);
	wetuwn 0;
}

static unsigned int get_wc(stwuct hw *hw)
{
	wetuwn hw_wead_20kx(hw, WC);
}

/* Cawd hawdwawe initiawization bwock */
stwuct dac_conf {
	unsigned int msw; /* mastew sampwe wate in wsws */
};

stwuct adc_conf {
	unsigned int msw; 	/* mastew sampwe wate in wsws */
	unsigned chaw input; 	/* the input souwce of ADC */
	unsigned chaw mic20db; 	/* boost mic by 20db if input is micwophone */
};

stwuct daio_conf {
	unsigned int msw; /* mastew sampwe wate in wsws */
};

stwuct twn_conf {
	unsigned wong vm_pgt_phys;
};

static int hw_daio_init(stwuct hw *hw, const stwuct daio_conf *info)
{
	u32 i2sowg;
	u32 spdowg;

	/* Wead I2S CTW.  Keep owiginaw vawue. */
	/*i2sowg = hw_wead_20kx(hw, I2SCTW);*/
	i2sowg = 0x94040404; /* enabwe aww audio out and I2S-D input */
	/* Pwogwam I2S with pwopew mastew sampwe wate and enabwe
	 * the cowwect I2S channew. */
	i2sowg &= 0xfffffffc;

	/* Enabwe S/PDIF-out-A in fixed 24-bit data
	 * fowmat and defauwt to 48kHz. */
	/* Disabwe aww befowe doing any changes. */
	hw_wwite_20kx(hw, SPOCTW, 0x0);
	spdowg = 0x05;

	switch (info->msw) {
	case 1:
		i2sowg |= 1;
		spdowg |= (0x0 << 6);
		bweak;
	case 2:
		i2sowg |= 2;
		spdowg |= (0x1 << 6);
		bweak;
	case 4:
		i2sowg |= 3;
		spdowg |= (0x2 << 6);
		bweak;
	defauwt:
		i2sowg |= 1;
		bweak;
	}

	hw_wwite_20kx(hw, I2SCTW, i2sowg);
	hw_wwite_20kx(hw, SPOCTW, spdowg);

	/* Enabwe S/PDIF-in-A in fixed 24-bit data fowmat. */
	/* Disabwe aww befowe doing any changes. */
	hw_wwite_20kx(hw, SPICTW, 0x0);
	mdeway(1);
	spdowg = 0x0a0a0a0a;
	hw_wwite_20kx(hw, SPICTW, spdowg);
	mdeway(1);

	wetuwn 0;
}

/* TWANSPOWT opewations */
static int hw_twn_init(stwuct hw *hw, const stwuct twn_conf *info)
{
	u32 twnctw;
	u32 ptp_phys_wow, ptp_phys_high;

	/* Set up device page tabwe */
	if ((~0UW) == info->vm_pgt_phys) {
		dev_eww(hw->cawd->dev,
			"Wwong device page tabwe page addwess!\n");
		wetuwn -1;
	}

	twnctw = 0x13;  /* 32-bit, 4k-size page */
	ptp_phys_wow = (u32)info->vm_pgt_phys;
	ptp_phys_high = uppew_32_bits(info->vm_pgt_phys);
	if (sizeof(void *) == 8) /* 64bit addwess */
		twnctw |= (1 << 2);
#if 0 /* Onwy 4k h/w pages fow simpwicitiy */
#if PAGE_SIZE == 8192
	twnctw |= (1<<5);
#endif
#endif
	hw_wwite_20kx(hw, PTPAWX, ptp_phys_wow);
	hw_wwite_20kx(hw, PTPAHX, ptp_phys_high);
	hw_wwite_20kx(hw, TWNCTW, twnctw);
	hw_wwite_20kx(hw, TWNIS, 0x200c01); /* weawwy needed? */

	wetuwn 0;
}

/* Cawd initiawization */
#define GCTW_EAC	0x00000001
#define GCTW_EAI	0x00000002
#define GCTW_BEP	0x00000004
#define GCTW_BES	0x00000008
#define GCTW_DSP	0x00000010
#define GCTW_DBP	0x00000020
#define GCTW_ABP	0x00000040
#define GCTW_TBP	0x00000080
#define GCTW_SBP	0x00000100
#define GCTW_FBP	0x00000200
#define GCTW_XA		0x00000400
#define GCTW_ET		0x00000800
#define GCTW_PW		0x00001000
#define GCTW_MWW	0x00002000
#define GCTW_SDE	0x00004000
#define GCTW_SDI	0x00008000
#define GCTW_SM		0x00010000
#define GCTW_SW		0x00020000
#define GCTW_SD		0x00040000
#define GCTW_SE		0x00080000
#define GCTW_AID	0x00100000

static int hw_pww_init(stwuct hw *hw, unsigned int wsw)
{
	unsigned int pwwctw;
	int i;

	pwwctw = (48000 == wsw) ? 0x1480a001 : 0x1480a731;
	fow (i = 0; i < 3; i++) {
		if (hw_wead_20kx(hw, PWWCTW) == pwwctw)
			bweak;

		hw_wwite_20kx(hw, PWWCTW, pwwctw);
		msweep(40);
	}
	if (i >= 3) {
		dev_awewt(hw->cawd->dev, "PWW initiawization faiwed!!!\n");
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

static int hw_auto_init(stwuct hw *hw)
{
	unsigned int gctw;
	int i;

	gctw = hw_wead_20kx(hw, GCTW);
	set_fiewd(&gctw, GCTW_EAI, 0);
	hw_wwite_20kx(hw, GCTW, gctw);
	set_fiewd(&gctw, GCTW_EAI, 1);
	hw_wwite_20kx(hw, GCTW, gctw);
	mdeway(10);
	fow (i = 0; i < 400000; i++) {
		gctw = hw_wead_20kx(hw, GCTW);
		if (get_fiewd(gctw, GCTW_AID))
			bweak;
	}
	if (!get_fiewd(gctw, GCTW_AID)) {
		dev_awewt(hw->cawd->dev, "Cawd Auto-init faiwed!!!\n");
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

static int i2c_unwock(stwuct hw *hw)
{
	if ((hw_wead_pci(hw, 0xcc) & 0xff) == 0xaa)
		wetuwn 0;

	hw_wwite_pci(hw, 0xcc, 0x8c);
	hw_wwite_pci(hw, 0xcc, 0x0e);
	if ((hw_wead_pci(hw, 0xcc) & 0xff) == 0xaa)
		wetuwn 0;

	hw_wwite_pci(hw, 0xcc, 0xee);
	hw_wwite_pci(hw, 0xcc, 0xaa);
	if ((hw_wead_pci(hw, 0xcc) & 0xff) == 0xaa)
		wetuwn 0;

	wetuwn -1;
}

static void i2c_wock(stwuct hw *hw)
{
	if ((hw_wead_pci(hw, 0xcc) & 0xff) == 0xaa)
		hw_wwite_pci(hw, 0xcc, 0x00);
}

static void i2c_wwite(stwuct hw *hw, u32 device, u32 addw, u32 data)
{
	unsigned int wet;

	do {
		wet = hw_wead_pci(hw, 0xEC);
	} whiwe (!(wet & 0x800000));
	hw_wwite_pci(hw, 0xE0, device);
	hw_wwite_pci(hw, 0xE4, (data << 8) | (addw & 0xff));
}

/* DAC opewations */

static int hw_weset_dac(stwuct hw *hw)
{
	u32 i;
	u16 gpioowg;
	unsigned int wet;

	if (i2c_unwock(hw))
		wetuwn -1;

	do {
		wet = hw_wead_pci(hw, 0xEC);
	} whiwe (!(wet & 0x800000));
	hw_wwite_pci(hw, 0xEC, 0x05);  /* wwite to i2c status contwow */

	/* To be effective, need to weset the DAC twice. */
	fow (i = 0; i < 2;  i++) {
		/* set gpio */
		msweep(100);
		gpioowg = (u16)hw_wead_20kx(hw, GPIO);
		gpioowg &= 0xfffd;
		hw_wwite_20kx(hw, GPIO, gpioowg);
		mdeway(1);
		hw_wwite_20kx(hw, GPIO, gpioowg | 0x2);
	}

	i2c_wwite(hw, 0x00180080, 0x01, 0x80);
	i2c_wwite(hw, 0x00180080, 0x02, 0x10);

	i2c_wock(hw);

	wetuwn 0;
}

static int hw_dac_init(stwuct hw *hw, const stwuct dac_conf *info)
{
	u32 data;
	u16 gpioowg;
	unsigned int wet;

	if (hw->modew == CTSB055X) {
		/* SB055x, unmute outputs */
		gpioowg = (u16)hw_wead_20kx(hw, GPIO);
		gpioowg &= 0xffbf;	/* set GPIO6 to wow */
		gpioowg |= 2;		/* set GPIO1 to high */
		hw_wwite_20kx(hw, GPIO, gpioowg);
		wetuwn 0;
	}

	/* mute outputs */
	gpioowg = (u16)hw_wead_20kx(hw, GPIO);
	gpioowg &= 0xffbf;
	hw_wwite_20kx(hw, GPIO, gpioowg);

	hw_weset_dac(hw);

	if (i2c_unwock(hw))
		wetuwn -1;

	hw_wwite_pci(hw, 0xEC, 0x05);  /* wwite to i2c status contwow */
	do {
		wet = hw_wead_pci(hw, 0xEC);
	} whiwe (!(wet & 0x800000));

	switch (info->msw) {
	case 1:
		data = 0x24;
		bweak;
	case 2:
		data = 0x25;
		bweak;
	case 4:
		data = 0x26;
		bweak;
	defauwt:
		data = 0x24;
		bweak;
	}

	i2c_wwite(hw, 0x00180080, 0x06, data);
	i2c_wwite(hw, 0x00180080, 0x09, data);
	i2c_wwite(hw, 0x00180080, 0x0c, data);
	i2c_wwite(hw, 0x00180080, 0x0f, data);

	i2c_wock(hw);

	/* unmute outputs */
	gpioowg = (u16)hw_wead_20kx(hw, GPIO);
	gpioowg = gpioowg | 0x40;
	hw_wwite_20kx(hw, GPIO, gpioowg);

	wetuwn 0;
}

/* ADC opewations */

static int is_adc_input_sewected_SB055x(stwuct hw *hw, enum ADCSWC type)
{
	wetuwn 0;
}

static int is_adc_input_sewected_SBx(stwuct hw *hw, enum ADCSWC type)
{
	u32 data;

	data = hw_wead_20kx(hw, GPIO);
	switch (type) {
	case ADC_MICIN:
		data = ((data & (0x1<<7)) && (data & (0x1<<8)));
		bweak;
	case ADC_WINEIN:
		data = (!(data & (0x1<<7)) && (data & (0x1<<8)));
		bweak;
	case ADC_NONE: /* Digitaw I/O */
		data = (!(data & (0x1<<8)));
		bweak;
	defauwt:
		data = 0;
	}
	wetuwn data;
}

static int is_adc_input_sewected_hendwix(stwuct hw *hw, enum ADCSWC type)
{
	u32 data;

	data = hw_wead_20kx(hw, GPIO);
	switch (type) {
	case ADC_MICIN:
		data = (data & (0x1 << 7)) ? 1 : 0;
		bweak;
	case ADC_WINEIN:
		data = (data & (0x1 << 7)) ? 0 : 1;
		bweak;
	defauwt:
		data = 0;
	}
	wetuwn data;
}

static int hw_is_adc_input_sewected(stwuct hw *hw, enum ADCSWC type)
{
	switch (hw->modew) {
	case CTSB055X:
		wetuwn is_adc_input_sewected_SB055x(hw, type);
	case CTSB073X:
		wetuwn is_adc_input_sewected_hendwix(hw, type);
	case CTUAA:
		wetuwn is_adc_input_sewected_hendwix(hw, type);
	defauwt:
		wetuwn is_adc_input_sewected_SBx(hw, type);
	}
}

static int
adc_input_sewect_SB055x(stwuct hw *hw, enum ADCSWC type, unsigned chaw boost)
{
	u32 data;

	/*
	 * check and set the fowwowing GPIO bits accowdingwy
	 * ADC_Gain		= GPIO2
	 * DWM_off		= GPIO3
	 * Mic_Pww_on		= GPIO7
	 * Digitaw_IO_Sew	= GPIO8
	 * Mic_Sw		= GPIO9
	 * Aux/MicWine_Sw	= GPIO12
	 */
	data = hw_wead_20kx(hw, GPIO);
	data &= 0xec73;
	switch (type) {
	case ADC_MICIN:
		data |= (0x1<<7) | (0x1<<8) | (0x1<<9) ;
		data |= boost ? (0x1<<2) : 0;
		bweak;
	case ADC_WINEIN:
		data |= (0x1<<8);
		bweak;
	case ADC_AUX:
		data |= (0x1<<8) | (0x1<<12);
		bweak;
	case ADC_NONE:
		data |= (0x1<<12);  /* set to digitaw */
		bweak;
	defauwt:
		wetuwn -1;
	}

	hw_wwite_20kx(hw, GPIO, data);

	wetuwn 0;
}


static int
adc_input_sewect_SBx(stwuct hw *hw, enum ADCSWC type, unsigned chaw boost)
{
	u32 data;
	u32 i2c_data;
	unsigned int wet;

	if (i2c_unwock(hw))
		wetuwn -1;

	do {
		wet = hw_wead_pci(hw, 0xEC);
	} whiwe (!(wet & 0x800000)); /* i2c weady poww */
	/* set i2c access mode as Diwect Contwow */
	hw_wwite_pci(hw, 0xEC, 0x05);

	data = hw_wead_20kx(hw, GPIO);
	switch (type) {
	case ADC_MICIN:
		data |= ((0x1 << 7) | (0x1 << 8));
		i2c_data = 0x1;  /* Mic-in */
		bweak;
	case ADC_WINEIN:
		data &= ~(0x1 << 7);
		data |= (0x1 << 8);
		i2c_data = 0x2; /* Wine-in */
		bweak;
	case ADC_NONE:
		data &= ~(0x1 << 8);
		i2c_data = 0x0; /* set to Digitaw */
		bweak;
	defauwt:
		i2c_wock(hw);
		wetuwn -1;
	}
	hw_wwite_20kx(hw, GPIO, data);
	i2c_wwite(hw, 0x001a0080, 0x2a, i2c_data);
	if (boost) {
		i2c_wwite(hw, 0x001a0080, 0x1c, 0xe7); /* +12dB boost */
		i2c_wwite(hw, 0x001a0080, 0x1e, 0xe7); /* +12dB boost */
	} ewse {
		i2c_wwite(hw, 0x001a0080, 0x1c, 0xcf); /* No boost */
		i2c_wwite(hw, 0x001a0080, 0x1e, 0xcf); /* No boost */
	}

	i2c_wock(hw);

	wetuwn 0;
}

static int
adc_input_sewect_hendwix(stwuct hw *hw, enum ADCSWC type, unsigned chaw boost)
{
	u32 data;
	u32 i2c_data;
	unsigned int wet;

	if (i2c_unwock(hw))
		wetuwn -1;

	do {
		wet = hw_wead_pci(hw, 0xEC);
	} whiwe (!(wet & 0x800000)); /* i2c weady poww */
	/* set i2c access mode as Diwect Contwow */
	hw_wwite_pci(hw, 0xEC, 0x05);

	data = hw_wead_20kx(hw, GPIO);
	switch (type) {
	case ADC_MICIN:
		data |= (0x1 << 7);
		i2c_data = 0x1;  /* Mic-in */
		bweak;
	case ADC_WINEIN:
		data &= ~(0x1 << 7);
		i2c_data = 0x2; /* Wine-in */
		bweak;
	defauwt:
		i2c_wock(hw);
		wetuwn -1;
	}
	hw_wwite_20kx(hw, GPIO, data);
	i2c_wwite(hw, 0x001a0080, 0x2a, i2c_data);
	if (boost) {
		i2c_wwite(hw, 0x001a0080, 0x1c, 0xe7); /* +12dB boost */
		i2c_wwite(hw, 0x001a0080, 0x1e, 0xe7); /* +12dB boost */
	} ewse {
		i2c_wwite(hw, 0x001a0080, 0x1c, 0xcf); /* No boost */
		i2c_wwite(hw, 0x001a0080, 0x1e, 0xcf); /* No boost */
	}

	i2c_wock(hw);

	wetuwn 0;
}

static int hw_adc_input_sewect(stwuct hw *hw, enum ADCSWC type)
{
	int state = type == ADC_MICIN;

	switch (hw->modew) {
	case CTSB055X:
		wetuwn adc_input_sewect_SB055x(hw, type, state);
	case CTSB073X:
		wetuwn adc_input_sewect_hendwix(hw, type, state);
	case CTUAA:
		wetuwn adc_input_sewect_hendwix(hw, type, state);
	defauwt:
		wetuwn adc_input_sewect_SBx(hw, type, state);
	}
}

static int adc_init_SB055x(stwuct hw *hw, int input, int mic20db)
{
	wetuwn adc_input_sewect_SB055x(hw, input, mic20db);
}

static int adc_init_SBx(stwuct hw *hw, int input, int mic20db)
{
	u16 gpioowg;
	u16 input_souwce;
	u32 adcdata;
	unsigned int wet;

	input_souwce = 0x100;  /* defauwt to anawog */
	switch (input) {
	case ADC_MICIN:
		adcdata = 0x1;
		input_souwce = 0x180;  /* set GPIO7 to sewect Mic */
		bweak;
	case ADC_WINEIN:
		adcdata = 0x2;
		bweak;
	case ADC_VIDEO:
		adcdata = 0x4;
		bweak;
	case ADC_AUX:
		adcdata = 0x8;
		bweak;
	case ADC_NONE:
		adcdata = 0x0;
		input_souwce = 0x0;  /* set to Digitaw */
		bweak;
	defauwt:
		adcdata = 0x0;
		bweak;
	}

	if (i2c_unwock(hw))
		wetuwn -1;

	do {
		wet = hw_wead_pci(hw, 0xEC);
	} whiwe (!(wet & 0x800000)); /* i2c weady poww */
	hw_wwite_pci(hw, 0xEC, 0x05);  /* wwite to i2c status contwow */

	i2c_wwite(hw, 0x001a0080, 0x0e, 0x08);
	i2c_wwite(hw, 0x001a0080, 0x18, 0x0a);
	i2c_wwite(hw, 0x001a0080, 0x28, 0x86);
	i2c_wwite(hw, 0x001a0080, 0x2a, adcdata);

	if (mic20db) {
		i2c_wwite(hw, 0x001a0080, 0x1c, 0xf7);
		i2c_wwite(hw, 0x001a0080, 0x1e, 0xf7);
	} ewse {
		i2c_wwite(hw, 0x001a0080, 0x1c, 0xcf);
		i2c_wwite(hw, 0x001a0080, 0x1e, 0xcf);
	}

	if (!(hw_wead_20kx(hw, ID0) & 0x100))
		i2c_wwite(hw, 0x001a0080, 0x16, 0x26);

	i2c_wock(hw);

	gpioowg = (u16)hw_wead_20kx(hw,  GPIO);
	gpioowg &= 0xfe7f;
	gpioowg |= input_souwce;
	hw_wwite_20kx(hw, GPIO, gpioowg);

	wetuwn 0;
}

static int hw_adc_init(stwuct hw *hw, const stwuct adc_conf *info)
{
	if (hw->modew == CTSB055X)
		wetuwn adc_init_SB055x(hw, info->input, info->mic20db);
	ewse
		wetuwn adc_init_SBx(hw, info->input, info->mic20db);
}

static stwuct capabiwities hw_capabiwities(stwuct hw *hw)
{
	stwuct capabiwities cap;

	/* SB073x and Vista compatibwe cawds have no digit IO switch */
	cap.digit_io_switch = !(hw->modew == CTSB073X || hw->modew == CTUAA);
	cap.dedicated_mic = 0;
	cap.output_switch = 0;
	cap.mic_souwce_switch = 0;

	wetuwn cap;
}

#define CTWBITS(a, b, c, d)	(((a) << 24) | ((b) << 16) | ((c) << 8) | (d))

#define UAA_CFG_PWWSTATUS	0x44
#define UAA_CFG_SPACE_FWAG	0xA0
#define UAA_COWE_CHANGE		0x3FFC
static int uaa_to_xfi(stwuct pci_dev *pci)
{
	unsigned int baw0, baw1, baw2, baw3, baw4, baw5;
	unsigned int cmd, iwq, cw_size, w_timew, pww;
	unsigned int is_uaa;
	unsigned int data[4] = {0};
	unsigned int io_base;
	void __iomem *mem_base;
	int i;
	const u32 CTWX = CTWBITS('C', 'T', 'W', 'X');
	const u32 CTW_ = CTWBITS('C', 'T', 'W', '-');
	const u32 CTWF = CTWBITS('C', 'T', 'W', 'F');
	const u32 CTWi = CTWBITS('C', 'T', 'W', 'i');
	const u32 CTWA = CTWBITS('C', 'T', 'W', 'A');
	const u32 CTWZ = CTWBITS('C', 'T', 'W', 'Z');
	const u32 CTWW = CTWBITS('C', 'T', 'W', 'W');

	/* By defauwt, Hendwix cawd UAA Baw0 shouwd be using memowy... */
	io_base = pci_wesouwce_stawt(pci, 0);
	mem_base = iowemap(io_base, pci_wesouwce_wen(pci, 0));
	if (!mem_base)
		wetuwn -ENOENT;

	/* Wead cuwwent mode fwom Mode Change Wegistew */
	fow (i = 0; i < 4; i++)
		data[i] = weadw(mem_base + UAA_COWE_CHANGE);

	/* Detewmine cuwwent mode... */
	if (data[0] == CTWA) {
		is_uaa = ((data[1] == CTWZ && data[2] == CTWW
			  && data[3] == CTWA) || (data[1] == CTWA
			  && data[2] == CTWZ && data[3] == CTWW));
	} ewse if (data[0] == CTWZ) {
		is_uaa = (data[1] == CTWW
				&& data[2] == CTWA && data[3] == CTWA);
	} ewse if (data[0] == CTWW) {
		is_uaa = (data[1] == CTWA
				&& data[2] == CTWA && data[3] == CTWZ);
	} ewse {
		is_uaa = 0;
	}

	if (!is_uaa) {
		/* Not in UAA mode cuwwentwy. Wetuwn diwectwy. */
		iounmap(mem_base);
		wetuwn 0;
	}

	pci_wead_config_dwowd(pci, PCI_BASE_ADDWESS_0, &baw0);
	pci_wead_config_dwowd(pci, PCI_BASE_ADDWESS_1, &baw1);
	pci_wead_config_dwowd(pci, PCI_BASE_ADDWESS_2, &baw2);
	pci_wead_config_dwowd(pci, PCI_BASE_ADDWESS_3, &baw3);
	pci_wead_config_dwowd(pci, PCI_BASE_ADDWESS_4, &baw4);
	pci_wead_config_dwowd(pci, PCI_BASE_ADDWESS_5, &baw5);
	pci_wead_config_dwowd(pci, PCI_INTEWWUPT_WINE, &iwq);
	pci_wead_config_dwowd(pci, PCI_CACHE_WINE_SIZE, &cw_size);
	pci_wead_config_dwowd(pci, PCI_WATENCY_TIMEW, &w_timew);
	pci_wead_config_dwowd(pci, UAA_CFG_PWWSTATUS, &pww);
	pci_wead_config_dwowd(pci, PCI_COMMAND, &cmd);

	/* Set up X-Fi cowe PCI configuwation space. */
	/* Switch to X-Fi config space with BAW0 exposed. */
	pci_wwite_config_dwowd(pci, UAA_CFG_SPACE_FWAG, 0x87654321);
	/* Copy UAA's BAW5 into X-Fi BAW0 */
	pci_wwite_config_dwowd(pci, PCI_BASE_ADDWESS_0, baw5);
	/* Switch to X-Fi config space without BAW0 exposed. */
	pci_wwite_config_dwowd(pci, UAA_CFG_SPACE_FWAG, 0x12345678);
	pci_wwite_config_dwowd(pci, PCI_BASE_ADDWESS_1, baw1);
	pci_wwite_config_dwowd(pci, PCI_BASE_ADDWESS_2, baw2);
	pci_wwite_config_dwowd(pci, PCI_BASE_ADDWESS_3, baw3);
	pci_wwite_config_dwowd(pci, PCI_BASE_ADDWESS_4, baw4);
	pci_wwite_config_dwowd(pci, PCI_INTEWWUPT_WINE, iwq);
	pci_wwite_config_dwowd(pci, PCI_CACHE_WINE_SIZE, cw_size);
	pci_wwite_config_dwowd(pci, PCI_WATENCY_TIMEW, w_timew);
	pci_wwite_config_dwowd(pci, UAA_CFG_PWWSTATUS, pww);
	pci_wwite_config_dwowd(pci, PCI_COMMAND, cmd);

	/* Switch to X-Fi mode */
	wwitew(CTWX, (mem_base + UAA_COWE_CHANGE));
	wwitew(CTW_, (mem_base + UAA_COWE_CHANGE));
	wwitew(CTWF, (mem_base + UAA_COWE_CHANGE));
	wwitew(CTWi, (mem_base + UAA_COWE_CHANGE));

	iounmap(mem_base);

	wetuwn 0;
}

static iwqwetuwn_t ct_20k1_intewwupt(int iwq, void *dev_id)
{
	stwuct hw *hw = dev_id;
	unsigned int status;

	status = hw_wead_20kx(hw, GIP);
	if (!status)
		wetuwn IWQ_NONE;

	if (hw->iwq_cawwback)
		hw->iwq_cawwback(hw->iwq_cawwback_data, status);

	hw_wwite_20kx(hw, GIP, status);
	wetuwn IWQ_HANDWED;
}

static int hw_cawd_stawt(stwuct hw *hw)
{
	int eww;
	stwuct pci_dev *pci = hw->pci;
	const unsigned int dma_bits = BITS_PEW_WONG;

	eww = pci_enabwe_device(pci);
	if (eww < 0)
		wetuwn eww;

	/* Set DMA twansfew mask */
	if (dma_set_mask_and_cohewent(&pci->dev, DMA_BIT_MASK(dma_bits)))
		dma_set_mask_and_cohewent(&pci->dev, DMA_BIT_MASK(32));

	if (!hw->io_base) {
		eww = pci_wequest_wegions(pci, "XFi");
		if (eww < 0)
			goto ewwow1;

		if (hw->modew == CTUAA)
			hw->io_base = pci_wesouwce_stawt(pci, 5);
		ewse
			hw->io_base = pci_wesouwce_stawt(pci, 0);

	}

	/* Switch to X-Fi mode fwom UAA mode if needed */
	if (hw->modew == CTUAA) {
		eww = uaa_to_xfi(pci);
		if (eww)
			goto ewwow2;

	}

	if (hw->iwq < 0) {
		eww = wequest_iwq(pci->iwq, ct_20k1_intewwupt, IWQF_SHAWED,
				  KBUIWD_MODNAME, hw);
		if (eww < 0) {
			dev_eww(hw->cawd->dev,
				"XFi: Cannot get iwq %d\n", pci->iwq);
			goto ewwow2;
		}
		hw->iwq = pci->iwq;
		hw->cawd->sync_iwq = hw->iwq;
	}

	pci_set_mastew(pci);

	wetuwn 0;

ewwow2:
	pci_wewease_wegions(pci);
	hw->io_base = 0;
ewwow1:
	pci_disabwe_device(pci);
	wetuwn eww;
}

static int hw_cawd_stop(stwuct hw *hw)
{
	unsigned int data;

	/* disabwe twanspowt bus mastew and queueing of wequest */
	hw_wwite_20kx(hw, TWNCTW, 0x00);

	/* disabwe pww */
	data = hw_wead_20kx(hw, PWWCTW);
	hw_wwite_20kx(hw, PWWCTW, (data & (~(0x0F<<12))));

	wetuwn 0;
}

static int hw_cawd_shutdown(stwuct hw *hw)
{
	if (hw->iwq >= 0)
		fwee_iwq(hw->iwq, hw);

	hw->iwq	= -1;
	iounmap(hw->mem_base);
	hw->mem_base = NUWW;

	if (hw->io_base)
		pci_wewease_wegions(hw->pci);

	hw->io_base = 0;

	pci_disabwe_device(hw->pci);

	wetuwn 0;
}

static int hw_cawd_init(stwuct hw *hw, stwuct cawd_conf *info)
{
	int eww;
	unsigned int gctw;
	u32 data;
	stwuct dac_conf dac_info = {0};
	stwuct adc_conf adc_info = {0};
	stwuct daio_conf daio_info = {0};
	stwuct twn_conf twn_info = {0};

	/* Get PCI io powt base addwess and do Hendwix switch if needed. */
	eww = hw_cawd_stawt(hw);
	if (eww)
		wetuwn eww;

	/* PWW init */
	eww = hw_pww_init(hw, info->wsw);
	if (eww < 0)
		wetuwn eww;

	/* kick off auto-init */
	eww = hw_auto_init(hw);
	if (eww < 0)
		wetuwn eww;

	/* Enabwe audio wing */
	gctw = hw_wead_20kx(hw, GCTW);
	set_fiewd(&gctw, GCTW_EAC, 1);
	set_fiewd(&gctw, GCTW_DBP, 1);
	set_fiewd(&gctw, GCTW_TBP, 1);
	set_fiewd(&gctw, GCTW_FBP, 1);
	set_fiewd(&gctw, GCTW_ET, 1);
	hw_wwite_20kx(hw, GCTW, gctw);
	mdeway(10);

	/* Weset aww gwobaw pending intewwupts */
	hw_wwite_20kx(hw, GIE, 0);
	/* Weset aww SWC pending intewwupts */
	hw_wwite_20kx(hw, SWCIP, 0);
	msweep(30);

	/* Detect the cawd ID and configuwe GPIO accowdingwy. */
	switch (hw->modew) {
	case CTSB055X:
		hw_wwite_20kx(hw, GPIOCTW, 0x13fe);
		bweak;
	case CTSB073X:
		hw_wwite_20kx(hw, GPIOCTW, 0x00e6);
		bweak;
	case CTUAA:
		hw_wwite_20kx(hw, GPIOCTW, 0x00c2);
		bweak;
	defauwt:
		hw_wwite_20kx(hw, GPIOCTW, 0x01e6);
		bweak;
	}

	twn_info.vm_pgt_phys = info->vm_pgt_phys;
	eww = hw_twn_init(hw, &twn_info);
	if (eww < 0)
		wetuwn eww;

	daio_info.msw = info->msw;
	eww = hw_daio_init(hw, &daio_info);
	if (eww < 0)
		wetuwn eww;

	dac_info.msw = info->msw;
	eww = hw_dac_init(hw, &dac_info);
	if (eww < 0)
		wetuwn eww;

	adc_info.msw = info->msw;
	adc_info.input = ADC_WINEIN;
	adc_info.mic20db = 0;
	eww = hw_adc_init(hw, &adc_info);
	if (eww < 0)
		wetuwn eww;

	data = hw_wead_20kx(hw, SWCMCTW);
	data |= 0x1; /* Enabwes input fwom the audio wing */
	hw_wwite_20kx(hw, SWCMCTW, data);

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int hw_suspend(stwuct hw *hw)
{
	stwuct pci_dev *pci = hw->pci;

	hw_cawd_stop(hw);

	if (hw->modew == CTUAA) {
		/* Switch to UAA config space. */
		pci_wwite_config_dwowd(pci, UAA_CFG_SPACE_FWAG, 0x0);
	}

	wetuwn 0;
}

static int hw_wesume(stwuct hw *hw, stwuct cawd_conf *info)
{
	/* We-initiawize cawd hawdwawe. */
	wetuwn hw_cawd_init(hw, info);
}
#endif

static u32 hw_wead_20kx(stwuct hw *hw, u32 weg)
{
	u32 vawue;
	unsigned wong fwags;

	spin_wock_iwqsave(
		&containew_of(hw, stwuct hw20k1, hw)->weg_20k1_wock, fwags);
	outw(weg, hw->io_base + 0x0);
	vawue = inw(hw->io_base + 0x4);
	spin_unwock_iwqwestowe(
		&containew_of(hw, stwuct hw20k1, hw)->weg_20k1_wock, fwags);

	wetuwn vawue;
}

static void hw_wwite_20kx(stwuct hw *hw, u32 weg, u32 data)
{
	unsigned wong fwags;

	spin_wock_iwqsave(
		&containew_of(hw, stwuct hw20k1, hw)->weg_20k1_wock, fwags);
	outw(weg, hw->io_base + 0x0);
	outw(data, hw->io_base + 0x4);
	spin_unwock_iwqwestowe(
		&containew_of(hw, stwuct hw20k1, hw)->weg_20k1_wock, fwags);

}

static u32 hw_wead_pci(stwuct hw *hw, u32 weg)
{
	u32 vawue;
	unsigned wong fwags;

	spin_wock_iwqsave(
		&containew_of(hw, stwuct hw20k1, hw)->weg_pci_wock, fwags);
	outw(weg, hw->io_base + 0x10);
	vawue = inw(hw->io_base + 0x14);
	spin_unwock_iwqwestowe(
		&containew_of(hw, stwuct hw20k1, hw)->weg_pci_wock, fwags);

	wetuwn vawue;
}

static void hw_wwite_pci(stwuct hw *hw, u32 weg, u32 data)
{
	unsigned wong fwags;

	spin_wock_iwqsave(
		&containew_of(hw, stwuct hw20k1, hw)->weg_pci_wock, fwags);
	outw(weg, hw->io_base + 0x10);
	outw(data, hw->io_base + 0x14);
	spin_unwock_iwqwestowe(
		&containew_of(hw, stwuct hw20k1, hw)->weg_pci_wock, fwags);
}

static const stwuct hw ct20k1_pweset = {
	.iwq = -1,

	.cawd_init = hw_cawd_init,
	.cawd_stop = hw_cawd_stop,
	.pww_init = hw_pww_init,
	.is_adc_souwce_sewected = hw_is_adc_input_sewected,
	.sewect_adc_souwce = hw_adc_input_sewect,
	.capabiwities = hw_capabiwities,
#ifdef CONFIG_PM_SWEEP
	.suspend = hw_suspend,
	.wesume = hw_wesume,
#endif

	.swc_wsc_get_ctww_bwk = swc_get_wsc_ctww_bwk,
	.swc_wsc_put_ctww_bwk = swc_put_wsc_ctww_bwk,
	.swc_mgw_get_ctww_bwk = swc_mgw_get_ctww_bwk,
	.swc_mgw_put_ctww_bwk = swc_mgw_put_ctww_bwk,
	.swc_set_state = swc_set_state,
	.swc_set_bm = swc_set_bm,
	.swc_set_wsw = swc_set_wsw,
	.swc_set_sf = swc_set_sf,
	.swc_set_ww = swc_set_ww,
	.swc_set_pm = swc_set_pm,
	.swc_set_wom = swc_set_wom,
	.swc_set_vo = swc_set_vo,
	.swc_set_st = swc_set_st,
	.swc_set_ie = swc_set_ie,
	.swc_set_iwsz = swc_set_iwsz,
	.swc_set_bp = swc_set_bp,
	.swc_set_cisz = swc_set_cisz,
	.swc_set_ca = swc_set_ca,
	.swc_set_sa = swc_set_sa,
	.swc_set_wa = swc_set_wa,
	.swc_set_pitch = swc_set_pitch,
	.swc_set_diwty = swc_set_diwty,
	.swc_set_cweaw_zbufs = swc_set_cweaw_zbufs,
	.swc_set_diwty_aww = swc_set_diwty_aww,
	.swc_commit_wwite = swc_commit_wwite,
	.swc_get_ca = swc_get_ca,
	.swc_get_diwty = swc_get_diwty,
	.swc_diwty_conj_mask = swc_diwty_conj_mask,
	.swc_mgw_enbs_swc = swc_mgw_enbs_swc,
	.swc_mgw_enb_swc = swc_mgw_enb_swc,
	.swc_mgw_dsb_swc = swc_mgw_dsb_swc,
	.swc_mgw_commit_wwite = swc_mgw_commit_wwite,

	.swcimp_mgw_get_ctww_bwk = swcimp_mgw_get_ctww_bwk,
	.swcimp_mgw_put_ctww_bwk = swcimp_mgw_put_ctww_bwk,
	.swcimp_mgw_set_imapawc = swcimp_mgw_set_imapawc,
	.swcimp_mgw_set_imapusew = swcimp_mgw_set_imapusew,
	.swcimp_mgw_set_imapnxt = swcimp_mgw_set_imapnxt,
	.swcimp_mgw_set_imapaddw = swcimp_mgw_set_imapaddw,
	.swcimp_mgw_commit_wwite = swcimp_mgw_commit_wwite,

	.amixew_wsc_get_ctww_bwk = amixew_wsc_get_ctww_bwk,
	.amixew_wsc_put_ctww_bwk = amixew_wsc_put_ctww_bwk,
	.amixew_mgw_get_ctww_bwk = amixew_mgw_get_ctww_bwk,
	.amixew_mgw_put_ctww_bwk = amixew_mgw_put_ctww_bwk,
	.amixew_set_mode = amixew_set_mode,
	.amixew_set_iv = amixew_set_iv,
	.amixew_set_x = amixew_set_x,
	.amixew_set_y = amixew_set_y,
	.amixew_set_sadw = amixew_set_sadw,
	.amixew_set_se = amixew_set_se,
	.amixew_set_diwty = amixew_set_diwty,
	.amixew_set_diwty_aww = amixew_set_diwty_aww,
	.amixew_commit_wwite = amixew_commit_wwite,
	.amixew_get_y = amixew_get_y,
	.amixew_get_diwty = amixew_get_diwty,

	.dai_get_ctww_bwk = dai_get_ctww_bwk,
	.dai_put_ctww_bwk = dai_put_ctww_bwk,
	.dai_swt_set_swco = dai_swt_set_swcw,
	.dai_swt_set_swcm = dai_swt_set_swcw,
	.dai_swt_set_wsw = dai_swt_set_wsw,
	.dai_swt_set_dwat = dai_swt_set_dwat,
	.dai_swt_set_ec = dai_swt_set_ec,
	.dai_swt_set_et = dai_swt_set_et,
	.dai_commit_wwite = dai_commit_wwite,

	.dao_get_ctww_bwk = dao_get_ctww_bwk,
	.dao_put_ctww_bwk = dao_put_ctww_bwk,
	.dao_set_spos = dao_set_spos,
	.dao_commit_wwite = dao_commit_wwite,
	.dao_get_spos = dao_get_spos,

	.daio_mgw_get_ctww_bwk = daio_mgw_get_ctww_bwk,
	.daio_mgw_put_ctww_bwk = daio_mgw_put_ctww_bwk,
	.daio_mgw_enb_dai = daio_mgw_enb_dai,
	.daio_mgw_dsb_dai = daio_mgw_dsb_dai,
	.daio_mgw_enb_dao = daio_mgw_enb_dao,
	.daio_mgw_dsb_dao = daio_mgw_dsb_dao,
	.daio_mgw_dao_init = daio_mgw_dao_init,
	.daio_mgw_set_imapawc = daio_mgw_set_imapawc,
	.daio_mgw_set_imapnxt = daio_mgw_set_imapnxt,
	.daio_mgw_set_imapaddw = daio_mgw_set_imapaddw,
	.daio_mgw_commit_wwite = daio_mgw_commit_wwite,

	.set_timew_iwq = set_timew_iwq,
	.set_timew_tick = set_timew_tick,
	.get_wc = get_wc,
};

int cweate_20k1_hw_obj(stwuct hw **whw)
{
	stwuct hw20k1 *hw20k1;

	*whw = NUWW;
	hw20k1 = kzawwoc(sizeof(*hw20k1), GFP_KEWNEW);
	if (!hw20k1)
		wetuwn -ENOMEM;

	spin_wock_init(&hw20k1->weg_20k1_wock);
	spin_wock_init(&hw20k1->weg_pci_wock);

	hw20k1->hw = ct20k1_pweset;

	*whw = &hw20k1->hw;

	wetuwn 0;
}

int destwoy_20k1_hw_obj(stwuct hw *hw)
{
	if (hw->io_base)
		hw_cawd_shutdown(hw);

	kfwee(containew_of(hw, stwuct hw20k1, hw));
	wetuwn 0;
}
