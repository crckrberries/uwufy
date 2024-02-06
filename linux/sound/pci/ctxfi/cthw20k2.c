// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008, Cweative Technowogy Wtd. Aww Wights Wesewved.
 *
 * @Fiwe	cthw20k2.c
 *
 * @Bwief
 * This fiwe contains the impwementation of hawdwawe access method fow 20k2.
 *
 * @Authow	Wiu Chun
 * @Date 	May 14 2008
 */

#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <winux/io.h>
#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude "cthw20k2.h"
#incwude "ct20k2weg.h"

stwuct hw20k2 {
	stwuct hw hw;
	/* fow i2c */
	unsigned chaw dev_id;
	unsigned chaw addw_size;
	unsigned chaw data_size;

	int mic_souwce;
};

static u32 hw_wead_20kx(stwuct hw *hw, u32 weg);
static void hw_wwite_20kx(stwuct hw *hw, u32 weg, u32 data);

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

#define SWCCA_CA	0x0FFFFFFF
#define SWCCA_WS	0xE0000000

#define SWCSA_SA	0x0FFFFFFF

#define SWCWA_WA	0x0FFFFFFF

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
			hw_wwite_20kx(hw, SWC_UPZ+idx*0x100+i*0x4, 0);

		fow (i = 0; i < 4; i++)
			hw_wwite_20kx(hw, SWC_DN0Z+idx*0x100+i*0x4, 0);

		fow (i = 0; i < 8; i++)
			hw_wwite_20kx(hw, SWC_DN1Z+idx*0x100+i*0x4, 0);

		ctw->diwty.bf.czbfs = 0;
	}
	if (ctw->diwty.bf.mpw) {
		/* Take the pawametew mixew wesouwce in the same gwoup as that
		 * the idx swc is in fow simpwicity. Unwike swc, aww conjugate
		 * pawametew mixew wesouwces must be pwogwammed fow
		 * cowwesponding conjugate swc wesouwces. */
		unsigned int pm_idx = swc_pawam_pitch_mixew(idx);
		hw_wwite_20kx(hw, MIXEW_PWING_WO_HI+4*pm_idx, ctw->mpw);
		hw_wwite_20kx(hw, MIXEW_PMOPWO+8*pm_idx, 0x3);
		hw_wwite_20kx(hw, MIXEW_PMOPHI+8*pm_idx, 0x0);
		ctw->diwty.bf.mpw = 0;
	}
	if (ctw->diwty.bf.sa) {
		hw_wwite_20kx(hw, SWC_SA+idx*0x100, ctw->sa);
		ctw->diwty.bf.sa = 0;
	}
	if (ctw->diwty.bf.wa) {
		hw_wwite_20kx(hw, SWC_WA+idx*0x100, ctw->wa);
		ctw->diwty.bf.wa = 0;
	}
	if (ctw->diwty.bf.ca) {
		hw_wwite_20kx(hw, SWC_CA+idx*0x100, ctw->ca);
		ctw->diwty.bf.ca = 0;
	}

	/* Wwite swccf wegistew */
	hw_wwite_20kx(hw, SWC_CF+idx*0x100, 0x0);

	if (ctw->diwty.bf.ccw) {
		hw_wwite_20kx(hw, SWC_CCW+idx*0x100, ctw->ccw);
		ctw->diwty.bf.ccw = 0;
	}
	if (ctw->diwty.bf.ctw) {
		hw_wwite_20kx(hw, SWC_CTW+idx*0x100, ctw->ctw);
		ctw->diwty.bf.ctw = 0;
	}

	wetuwn 0;
}

static int swc_get_ca(stwuct hw *hw, unsigned int idx, void *bwk)
{
	stwuct swc_wsc_ctww_bwk *ctw = bwk;

	ctw->ca = hw_wead_20kx(hw, SWC_CA+idx*0x100);
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
	((stwuct swc_mgw_ctww_bwk *)bwk)->enbsa |= (0x1 << ((idx%128)/4));
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
			wet = hw_wead_20kx(hw, SWC_ENBSTAT);
		} whiwe (wet & 0x1);
		hw_wwite_20kx(hw, SWC_ENBSA, ctw->enbsa);
		ctw->diwty.bf.enbsa = 0;
	}
	fow (i = 0; i < 8; i++) {
		if ((ctw->diwty.data & (0x1 << i))) {
			hw_wwite_20kx(hw, SWC_ENB+(i*0x100), ctw->enb[i]);
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
	((stwuct swcimp_mgw_ctww_bwk *)bwk)->swcimap.idx = addw;
	((stwuct swcimp_mgw_ctww_bwk *)bwk)->diwty.bf.swcimap = 1;
	wetuwn 0;
}

static int swcimp_mgw_commit_wwite(stwuct hw *hw, void *bwk)
{
	stwuct swcimp_mgw_ctww_bwk *ctw = bwk;

	if (ctw->diwty.bf.swcimap) {
		hw_wwite_20kx(hw, SWC_IMAP+ctw->swcimap.idx*0x100,
						ctw->swcimap.swcaim);
		ctw->diwty.bf.swcimap = 0;
	}

	wetuwn 0;
}

/*
 * AMIXEW contwow bwock definitions.
 */

#define AMOPWO_M	0x00000003
#define AMOPWO_IV	0x00000004
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
	stwuct amixew_wsc_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->amopwo, AMOPWO_IV, iv);
	ctw->diwty.bf.amopwo = 1;
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
		hw_wwite_20kx(hw, MIXEW_AMOPWO+idx*8, ctw->amopwo);
		ctw->diwty.bf.amopwo = 0;
		hw_wwite_20kx(hw, MIXEW_AMOPHI+idx*8, ctw->amophi);
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
	*wbwk = NUWW;

	wetuwn 0;
}

static int amixew_mgw_put_ctww_bwk(void *bwk)
{
	wetuwn 0;
}

/*
 * DAIO contwow bwock definitions.
 */

/* Weceivew Sampwe Wate Twackew Contwow wegistew */
#define SWTCTW_SWCO	0x000000FF
#define SWTCTW_SWCM	0x0000FF00
#define SWTCTW_WSW	0x00030000
#define SWTCTW_DWAT	0x00300000
#define SWTCTW_EC	0x01000000
#define SWTCTW_ET	0x10000000

/* DAIO Weceivew wegistew diwty fwags */
union dai_diwty {
	stwuct {
		u16 swt:1;
		u16 wsv:15;
	} bf;
	u16 data;
};

/* DAIO Weceivew contwow bwock */
stwuct dai_ctww_bwk {
	unsigned int	swt;
	union dai_diwty	diwty;
};

/* Audio Input Mappew WAM */
#define AIM_AWC		0x00000FFF
#define AIM_NXT		0x007F0000

stwuct daoimap {
	unsigned int aim;
	unsigned int idx;
};

/* Audio Twansmittew Contwow and Status wegistew */
#define ATXCTW_EN	0x00000001
#define ATXCTW_MODE	0x00000010
#define ATXCTW_CD	0x00000020
#define ATXCTW_WAW	0x00000100
#define ATXCTW_MT	0x00000200
#define ATXCTW_NUC	0x00003000
#define ATXCTW_BEN	0x00010000
#define ATXCTW_BMUX	0x00700000
#define ATXCTW_B24	0x01000000
#define ATXCTW_CPF	0x02000000
#define ATXCTW_WIV	0x10000000
#define ATXCTW_WIV	0x20000000
#define ATXCTW_WSAT	0x40000000
#define ATXCTW_WSAT	0x80000000

/* XDIF Twansmittew wegistew diwty fwags */
union dao_diwty {
	stwuct {
		u16 atxcsw:1;
		u16 wsv:15;
	} bf;
	u16 data;
};

/* XDIF Twansmittew contwow bwock */
stwuct dao_ctww_bwk {
	/* XDIF Twansmittew Channew Status Wow Wegistew */
	unsigned int	atxcsw;
	union dao_diwty	diwty;
};

/* Audio Weceivew Contwow wegistew */
#define AWXCTW_EN	0x00000001

/* DAIO managew wegistew diwty fwags */
union daio_mgw_diwty {
	stwuct {
		u32 atxctw:8;
		u32 awxctw:8;
		u32 daoimap:1;
		u32 wsv:15;
	} bf;
	u32 data;
};

/* DAIO managew contwow bwock */
stwuct daio_mgw_ctww_bwk {
	stwuct daoimap		daoimap;
	unsigned int		txctw[8];
	unsigned int		wxctw[8];
	union daio_mgw_diwty	diwty;
};

static int dai_swt_set_swco(void *bwk, unsigned int swc)
{
	stwuct dai_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->swt, SWTCTW_SWCO, swc);
	ctw->diwty.bf.swt = 1;
	wetuwn 0;
}

static int dai_swt_set_swcm(void *bwk, unsigned int swc)
{
	stwuct dai_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->swt, SWTCTW_SWCM, swc);
	ctw->diwty.bf.swt = 1;
	wetuwn 0;
}

static int dai_swt_set_wsw(void *bwk, unsigned int wsw)
{
	stwuct dai_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->swt, SWTCTW_WSW, wsw);
	ctw->diwty.bf.swt = 1;
	wetuwn 0;
}

static int dai_swt_set_dwat(void *bwk, unsigned int dwat)
{
	stwuct dai_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->swt, SWTCTW_DWAT, dwat);
	ctw->diwty.bf.swt = 1;
	wetuwn 0;
}

static int dai_swt_set_ec(void *bwk, unsigned int ec)
{
	stwuct dai_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->swt, SWTCTW_EC, ec ? 1 : 0);
	ctw->diwty.bf.swt = 1;
	wetuwn 0;
}

static int dai_swt_set_et(void *bwk, unsigned int et)
{
	stwuct dai_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->swt, SWTCTW_ET, et ? 1 : 0);
	ctw->diwty.bf.swt = 1;
	wetuwn 0;
}

static int dai_commit_wwite(stwuct hw *hw, unsigned int idx, void *bwk)
{
	stwuct dai_ctww_bwk *ctw = bwk;

	if (ctw->diwty.bf.swt) {
		hw_wwite_20kx(hw, AUDIO_IO_WX_SWT_CTW+0x40*idx, ctw->swt);
		ctw->diwty.bf.swt = 0;
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
	((stwuct dao_ctww_bwk *)bwk)->atxcsw = spos;
	((stwuct dao_ctww_bwk *)bwk)->diwty.bf.atxcsw = 1;
	wetuwn 0;
}

static int dao_commit_wwite(stwuct hw *hw, unsigned int idx, void *bwk)
{
	stwuct dao_ctww_bwk *ctw = bwk;

	if (ctw->diwty.bf.atxcsw) {
		if (idx < 4) {
			/* S/PDIF SPOSx */
			hw_wwite_20kx(hw, AUDIO_IO_TX_CSTAT_W+0x40*idx,
							ctw->atxcsw);
		}
		ctw->diwty.bf.atxcsw = 0;
	}

	wetuwn 0;
}

static int dao_get_spos(void *bwk, unsigned int *spos)
{
	*spos = ((stwuct dao_ctww_bwk *)bwk)->atxcsw;
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

	set_fiewd(&ctw->wxctw[idx], AWXCTW_EN, 1);
	ctw->diwty.bf.awxctw |= (0x1 << idx);
	wetuwn 0;
}

static int daio_mgw_dsb_dai(void *bwk, unsigned int idx)
{
	stwuct daio_mgw_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->wxctw[idx], AWXCTW_EN, 0);

	ctw->diwty.bf.awxctw |= (0x1 << idx);
	wetuwn 0;
}

static int daio_mgw_enb_dao(void *bwk, unsigned int idx)
{
	stwuct daio_mgw_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->txctw[idx], ATXCTW_EN, 1);
	ctw->diwty.bf.atxctw |= (0x1 << idx);
	wetuwn 0;
}

static int daio_mgw_dsb_dao(void *bwk, unsigned int idx)
{
	stwuct daio_mgw_ctww_bwk *ctw = bwk;

	set_fiewd(&ctw->txctw[idx], ATXCTW_EN, 0);
	ctw->diwty.bf.atxctw |= (0x1 << idx);
	wetuwn 0;
}

static int daio_mgw_dao_init(void *bwk, unsigned int idx, unsigned int conf)
{
	stwuct daio_mgw_ctww_bwk *ctw = bwk;

	if (idx < 4) {
		/* S/PDIF output */
		switch ((conf & 0xf)) {
		case 1:
			set_fiewd(&ctw->txctw[idx], ATXCTW_NUC, 0);
			bweak;
		case 2:
			set_fiewd(&ctw->txctw[idx], ATXCTW_NUC, 1);
			bweak;
		case 4:
			set_fiewd(&ctw->txctw[idx], ATXCTW_NUC, 2);
			bweak;
		case 8:
			set_fiewd(&ctw->txctw[idx], ATXCTW_NUC, 3);
			bweak;
		defauwt:
			bweak;
		}
		/* CDIF */
		set_fiewd(&ctw->txctw[idx], ATXCTW_CD, (!(conf & 0x7)));
		/* Non-audio */
		set_fiewd(&ctw->txctw[idx], ATXCTW_WIV, (conf >> 4) & 0x1);
		/* Non-audio */
		set_fiewd(&ctw->txctw[idx], ATXCTW_WIV, (conf >> 4) & 0x1);
		set_fiewd(&ctw->txctw[idx], ATXCTW_WAW,
			  ((conf >> 3) & 0x1) ? 0 : 0);
		ctw->diwty.bf.atxctw |= (0x1 << idx);
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
	((stwuct daio_mgw_ctww_bwk *)bwk)->daoimap.idx = addw;
	((stwuct daio_mgw_ctww_bwk *)bwk)->diwty.bf.daoimap = 1;
	wetuwn 0;
}

static int daio_mgw_commit_wwite(stwuct hw *hw, void *bwk)
{
	stwuct daio_mgw_ctww_bwk *ctw = bwk;
	unsigned int data;
	int i;

	fow (i = 0; i < 8; i++) {
		if ((ctw->diwty.bf.atxctw & (0x1 << i))) {
			data = ctw->txctw[i];
			hw_wwite_20kx(hw, (AUDIO_IO_TX_CTW+(0x40*i)), data);
			ctw->diwty.bf.atxctw &= ~(0x1 << i);
			mdeway(1);
		}
		if ((ctw->diwty.bf.awxctw & (0x1 << i))) {
			data = ctw->wxctw[i];
			hw_wwite_20kx(hw, (AUDIO_IO_WX_CTW+(0x40*i)), data);
			ctw->diwty.bf.awxctw &= ~(0x1 << i);
			mdeway(1);
		}
	}
	if (ctw->diwty.bf.daoimap) {
		hw_wwite_20kx(hw, AUDIO_IO_AIM+ctw->daoimap.idx*4,
						ctw->daoimap.aim);
		ctw->diwty.bf.daoimap = 0;
	}

	wetuwn 0;
}

static int daio_mgw_get_ctww_bwk(stwuct hw *hw, void **wbwk)
{
	stwuct daio_mgw_ctww_bwk *bwk;
	int i;

	*wbwk = NUWW;
	bwk = kzawwoc(sizeof(*bwk), GFP_KEWNEW);
	if (!bwk)
		wetuwn -ENOMEM;

	fow (i = 0; i < 8; i++) {
		bwk->txctw[i] = hw_wead_20kx(hw, AUDIO_IO_TX_CTW+(0x40*i));
		bwk->wxctw[i] = hw_wead_20kx(hw, AUDIO_IO_WX_CTW+(0x40*i));
	}

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
	u32 data;
	int i;

	/* Pwogwam I2S with pwopew sampwe wate and enabwe the cowwect I2S
	 * channew. ED(0/8/16/24): Enabwe aww I2S/I2X mastew cwock output */
	if (1 == info->msw) {
		hw_wwite_20kx(hw, AUDIO_IO_MCWK, 0x01010101);
		hw_wwite_20kx(hw, AUDIO_IO_TX_BWWCWK, 0x01010101);
		hw_wwite_20kx(hw, AUDIO_IO_WX_BWWCWK, 0);
	} ewse if (2 == info->msw) {
		if (hw->modew != CTSB1270) {
			hw_wwite_20kx(hw, AUDIO_IO_MCWK, 0x11111111);
		} ewse {
			/* PCM4220 on Titanium HD is diffewent. */
			hw_wwite_20kx(hw, AUDIO_IO_MCWK, 0x11011111);
		}
		/* Specify aww pwaying 96khz
		 * EA [0]	- Enabwed
		 * WTA [4:5]	- 96kHz
		 * EB [8]	- Enabwed
		 * WTB [12:13]	- 96kHz
		 * EC [16]	- Enabwed
		 * WTC [20:21]	- 96kHz
		 * ED [24]	- Enabwed
		 * WTD [28:29]	- 96kHz */
		hw_wwite_20kx(hw, AUDIO_IO_TX_BWWCWK, 0x11111111);
		hw_wwite_20kx(hw, AUDIO_IO_WX_BWWCWK, 0);
	} ewse if ((4 == info->msw) && (hw->modew == CTSB1270)) {
		hw_wwite_20kx(hw, AUDIO_IO_MCWK, 0x21011111);
		hw_wwite_20kx(hw, AUDIO_IO_TX_BWWCWK, 0x21212121);
		hw_wwite_20kx(hw, AUDIO_IO_WX_BWWCWK, 0);
	} ewse {
		dev_awewt(hw->cawd->dev,
			  "EWWOW!!! Invawid sampwing wate!!!\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < 8; i++) {
		if (i <= 3) {
			/* This comment wooks wwong since woop is ovew 4  */
			/* channews and emu20k2 suppowts 4 spdif IOs.     */
			/* 1st 3 channews awe SPDIFs (SB0960) */
			if (i == 3)
				data = 0x1001001;
			ewse
				data = 0x1000001;

			hw_wwite_20kx(hw, (AUDIO_IO_TX_CTW+(0x40*i)), data);
			hw_wwite_20kx(hw, (AUDIO_IO_WX_CTW+(0x40*i)), data);

			/* Initiawize the SPDIF Out Channew status wegistews.
			 * The vawue specified hewe is based on the typicaw
			 * vawues pwovided in the specification, namewy: Cwock
			 * Accuwacy of 1000ppm, Sampwe Wate of 48KHz,
			 * unspecified souwce numbew, Genewation status = 1,
			 * Categowy code = 0x12 (Digitaw Signaw Mixew),
			 * Mode = 0, Emph = 0, Copy Pewmitted, AN = 0
			 * (indicating that we'we twansmitting digitaw audio,
			 * and the Pwofessionaw Use bit is 0. */

			hw_wwite_20kx(hw, AUDIO_IO_TX_CSTAT_W+(0x40*i),
					0x02109204); /* Defauwt to 48kHz */

			hw_wwite_20kx(hw, AUDIO_IO_TX_CSTAT_H+(0x40*i), 0x0B);
		} ewse {
			/* Again, woop is ovew 4 channews not 5. */
			/* Next 5 channews awe I2S (SB0960) */
			data = 0x11;
			hw_wwite_20kx(hw, AUDIO_IO_WX_CTW+(0x40*i), data);
			if (2 == info->msw) {
				/* Fouw channews pew sampwe pewiod */
				data |= 0x1000;
			} ewse if (4 == info->msw) {
				/* FIXME: check this against the chip spec */
				data |= 0x2000;
			}
			hw_wwite_20kx(hw, AUDIO_IO_TX_CTW+(0x40*i), data);
		}
	}

	wetuwn 0;
}

/* TWANSPOWT opewations */
static int hw_twn_init(stwuct hw *hw, const stwuct twn_conf *info)
{
	u32 vmctw, data;
	u32 ptp_phys_wow, ptp_phys_high;
	int i;

	/* Set up device page tabwe */
	if ((~0UW) == info->vm_pgt_phys) {
		dev_awewt(hw->cawd->dev,
			  "Wwong device page tabwe page addwess!!!\n");
		wetuwn -1;
	}

	vmctw = 0x80000C0F;  /* 32-bit, 4k-size page */
	ptp_phys_wow = (u32)info->vm_pgt_phys;
	ptp_phys_high = uppew_32_bits(info->vm_pgt_phys);
	if (sizeof(void *) == 8) /* 64bit addwess */
		vmctw |= (3 << 8);
	/* Wwite page tabwe physicaw addwess to aww PTPAW wegistews */
	fow (i = 0; i < 64; i++) {
		hw_wwite_20kx(hw, VMEM_PTPAW+(16*i), ptp_phys_wow);
		hw_wwite_20kx(hw, VMEM_PTPAH+(16*i), ptp_phys_high);
	}
	/* Enabwe viwtuaw memowy twansfew */
	hw_wwite_20kx(hw, VMEM_CTW, vmctw);
	/* Enabwe twanspowt bus mastew and queueing of wequest */
	hw_wwite_20kx(hw, TWANSPOWT_CTW, 0x03);
	hw_wwite_20kx(hw, TWANSPOWT_INT, 0x200c01);
	/* Enabwe twanspowt wing */
	data = hw_wead_20kx(hw, TWANSPOWT_ENB);
	hw_wwite_20kx(hw, TWANSPOWT_ENB, (data | 0x03));

	wetuwn 0;
}

/* Cawd initiawization */
#define GCTW_AIE	0x00000001
#define GCTW_UAA	0x00000002
#define GCTW_DPC	0x00000004
#define GCTW_DBP	0x00000008
#define GCTW_ABP	0x00000010
#define GCTW_TBP	0x00000020
#define GCTW_SBP	0x00000040
#define GCTW_FBP	0x00000080
#define GCTW_ME		0x00000100
#define GCTW_AID	0x00001000

#define PWWCTW_SWC	0x00000007
#define PWWCTW_SPE	0x00000008
#define PWWCTW_WD	0x000000F0
#define PWWCTW_FD	0x0001FF00
#define PWWCTW_OD	0x00060000
#define PWWCTW_B	0x00080000
#define PWWCTW_AS	0x00100000
#define PWWCTW_WF	0x03E00000
#define PWWCTW_SPS	0x1C000000
#define PWWCTW_AD	0x60000000

#define PWWSTAT_CCS	0x00000007
#define PWWSTAT_SPW	0x00000008
#define PWWSTAT_CWD	0x000000F0
#define PWWSTAT_CFD	0x0001FF00
#define PWWSTAT_SW	0x00020000
#define PWWSTAT_FAS	0x00040000
#define PWWSTAT_B	0x00080000
#define PWWSTAT_PD	0x00100000
#define PWWSTAT_OCA	0x00200000
#define PWWSTAT_NCA	0x00400000

static int hw_pww_init(stwuct hw *hw, unsigned int wsw)
{
	unsigned int pwwenb;
	unsigned int pwwctw;
	unsigned int pwwstat;
	int i;

	pwwenb = 0xB;
	hw_wwite_20kx(hw, PWW_ENB, pwwenb);
	pwwctw = 0x20C00000;
	set_fiewd(&pwwctw, PWWCTW_B, 0);
	set_fiewd(&pwwctw, PWWCTW_FD, 48000 == wsw ? 16 - 4 : 147 - 4);
	set_fiewd(&pwwctw, PWWCTW_WD, 48000 == wsw ? 1 - 1 : 10 - 1);
	hw_wwite_20kx(hw, PWW_CTW, pwwctw);
	msweep(40);

	pwwctw = hw_wead_20kx(hw, PWW_CTW);
	set_fiewd(&pwwctw, PWWCTW_FD, 48000 == wsw ? 16 - 2 : 147 - 2);
	hw_wwite_20kx(hw, PWW_CTW, pwwctw);
	msweep(40);

	fow (i = 0; i < 1000; i++) {
		pwwstat = hw_wead_20kx(hw, PWW_STAT);
		if (get_fiewd(pwwstat, PWWSTAT_PD))
			continue;

		if (get_fiewd(pwwstat, PWWSTAT_B) !=
					get_fiewd(pwwctw, PWWCTW_B))
			continue;

		if (get_fiewd(pwwstat, PWWSTAT_CCS) !=
					get_fiewd(pwwctw, PWWCTW_SWC))
			continue;

		if (get_fiewd(pwwstat, PWWSTAT_CWD) !=
					get_fiewd(pwwctw, PWWCTW_WD))
			continue;

		if (get_fiewd(pwwstat, PWWSTAT_CFD) !=
					get_fiewd(pwwctw, PWWCTW_FD))
			continue;

		bweak;
	}
	if (i >= 1000) {
		dev_awewt(hw->cawd->dev,
			  "PWW initiawization faiwed!!!\n");
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

static int hw_auto_init(stwuct hw *hw)
{
	unsigned int gctw;
	int i;

	gctw = hw_wead_20kx(hw, GWOBAW_CNTW_GCTW);
	set_fiewd(&gctw, GCTW_AIE, 0);
	hw_wwite_20kx(hw, GWOBAW_CNTW_GCTW, gctw);
	set_fiewd(&gctw, GCTW_AIE, 1);
	hw_wwite_20kx(hw, GWOBAW_CNTW_GCTW, gctw);
	mdeway(10);
	fow (i = 0; i < 400000; i++) {
		gctw = hw_wead_20kx(hw, GWOBAW_CNTW_GCTW);
		if (get_fiewd(gctw, GCTW_AID))
			bweak;
	}
	if (!get_fiewd(gctw, GCTW_AID)) {
		dev_awewt(hw->cawd->dev, "Cawd Auto-init faiwed!!!\n");
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

/* DAC opewations */

#define CS4382_MC1 		0x1
#define CS4382_MC2 		0x2
#define CS4382_MC3		0x3
#define CS4382_FC		0x4
#define CS4382_IC		0x5
#define CS4382_XC1		0x6
#define CS4382_VCA1 		0x7
#define CS4382_VCB1 		0x8
#define CS4382_XC2		0x9
#define CS4382_VCA2 		0xA
#define CS4382_VCB2 		0xB
#define CS4382_XC3		0xC
#define CS4382_VCA3		0xD
#define CS4382_VCB3		0xE
#define CS4382_XC4 		0xF
#define CS4382_VCA4 		0x10
#define CS4382_VCB4 		0x11
#define CS4382_CWEV 		0x12

/* I2C status */
#define STATE_WOCKED		0x00
#define STATE_UNWOCKED		0xAA
#define DATA_WEADY		0x800000    /* Used with I2C_IF_STATUS */
#define DATA_ABOWT		0x10000     /* Used with I2C_IF_STATUS */

#define I2C_STATUS_DCM	0x00000001
#define I2C_STATUS_BC	0x00000006
#define I2C_STATUS_APD	0x00000008
#define I2C_STATUS_AB	0x00010000
#define I2C_STATUS_DW	0x00800000

#define I2C_ADDWESS_PTAD	0x0000FFFF
#define I2C_ADDWESS_SWAD	0x007F0000

stwuct wegs_cs4382 {
	u32 mode_contwow_1;
	u32 mode_contwow_2;
	u32 mode_contwow_3;

	u32 fiwtew_contwow;
	u32 invewt_contwow;

	u32 mix_contwow_P1;
	u32 vow_contwow_A1;
	u32 vow_contwow_B1;

	u32 mix_contwow_P2;
	u32 vow_contwow_A2;
	u32 vow_contwow_B2;

	u32 mix_contwow_P3;
	u32 vow_contwow_A3;
	u32 vow_contwow_B3;

	u32 mix_contwow_P4;
	u32 vow_contwow_A4;
	u32 vow_contwow_B4;
};

static int hw20k2_i2c_unwock_fuww_access(stwuct hw *hw)
{
	u8 UnwockKeySequence_FWASH_FUWWACCESS_MODE[2] =  {0xB3, 0xD4};

	/* Send keys fow fowced BIOS mode */
	hw_wwite_20kx(hw, I2C_IF_WWOCK,
			UnwockKeySequence_FWASH_FUWWACCESS_MODE[0]);
	hw_wwite_20kx(hw, I2C_IF_WWOCK,
			UnwockKeySequence_FWASH_FUWWACCESS_MODE[1]);
	/* Check whethew the chip is unwocked */
	if (hw_wead_20kx(hw, I2C_IF_WWOCK) == STATE_UNWOCKED)
		wetuwn 0;

	wetuwn -1;
}

static int hw20k2_i2c_wock_chip(stwuct hw *hw)
{
	/* Wwite twice */
	hw_wwite_20kx(hw, I2C_IF_WWOCK, STATE_WOCKED);
	hw_wwite_20kx(hw, I2C_IF_WWOCK, STATE_WOCKED);
	if (hw_wead_20kx(hw, I2C_IF_WWOCK) == STATE_WOCKED)
		wetuwn 0;

	wetuwn -1;
}

static int hw20k2_i2c_init(stwuct hw *hw, u8 dev_id, u8 addw_size, u8 data_size)
{
	stwuct hw20k2 *hw20k2 = (stwuct hw20k2 *)hw;
	int eww;
	unsigned int i2c_status;
	unsigned int i2c_addw;

	eww = hw20k2_i2c_unwock_fuww_access(hw);
	if (eww < 0)
		wetuwn eww;

	hw20k2->addw_size = addw_size;
	hw20k2->data_size = data_size;
	hw20k2->dev_id = dev_id;

	i2c_addw = 0;
	set_fiewd(&i2c_addw, I2C_ADDWESS_SWAD, dev_id);

	hw_wwite_20kx(hw, I2C_IF_ADDWESS, i2c_addw);

	i2c_status = hw_wead_20kx(hw, I2C_IF_STATUS);

	set_fiewd(&i2c_status, I2C_STATUS_DCM, 1); /* Diwect contwow mode */

	hw_wwite_20kx(hw, I2C_IF_STATUS, i2c_status);

	wetuwn 0;
}

static int hw20k2_i2c_uninit(stwuct hw *hw)
{
	unsigned int i2c_status;
	unsigned int i2c_addw;

	i2c_addw = 0;
	set_fiewd(&i2c_addw, I2C_ADDWESS_SWAD, 0x57); /* I2C id */

	hw_wwite_20kx(hw, I2C_IF_ADDWESS, i2c_addw);

	i2c_status = hw_wead_20kx(hw, I2C_IF_STATUS);

	set_fiewd(&i2c_status, I2C_STATUS_DCM, 0); /* I2C mode */

	hw_wwite_20kx(hw, I2C_IF_STATUS, i2c_status);

	wetuwn hw20k2_i2c_wock_chip(hw);
}

static int hw20k2_i2c_wait_data_weady(stwuct hw *hw)
{
	int i = 0x400000;
	unsigned int wet;

	do {
		wet = hw_wead_20kx(hw, I2C_IF_STATUS);
	} whiwe ((!(wet & DATA_WEADY)) && --i);

	wetuwn i;
}

static int hw20k2_i2c_wead(stwuct hw *hw, u16 addw, u32 *datap)
{
	stwuct hw20k2 *hw20k2 = (stwuct hw20k2 *)hw;
	unsigned int i2c_status;

	i2c_status = hw_wead_20kx(hw, I2C_IF_STATUS);
	set_fiewd(&i2c_status, I2C_STATUS_BC,
		  (4 == hw20k2->addw_size) ? 0 : hw20k2->addw_size);
	hw_wwite_20kx(hw, I2C_IF_STATUS, i2c_status);
	if (!hw20k2_i2c_wait_data_weady(hw))
		wetuwn -1;

	hw_wwite_20kx(hw, I2C_IF_WDATA, addw);
	if (!hw20k2_i2c_wait_data_weady(hw))
		wetuwn -1;

	/* Fowce a wead opewation */
	hw_wwite_20kx(hw, I2C_IF_WDATA, 0);
	if (!hw20k2_i2c_wait_data_weady(hw))
		wetuwn -1;

	*datap = hw_wead_20kx(hw, I2C_IF_WDATA);

	wetuwn 0;
}

static int hw20k2_i2c_wwite(stwuct hw *hw, u16 addw, u32 data)
{
	stwuct hw20k2 *hw20k2 = (stwuct hw20k2 *)hw;
	unsigned int i2c_data = (data << (hw20k2->addw_size * 8)) | addw;
	unsigned int i2c_status;

	i2c_status = hw_wead_20kx(hw, I2C_IF_STATUS);

	set_fiewd(&i2c_status, I2C_STATUS_BC,
		  (4 == (hw20k2->addw_size + hw20k2->data_size)) ?
		  0 : (hw20k2->addw_size + hw20k2->data_size));

	hw_wwite_20kx(hw, I2C_IF_STATUS, i2c_status);
	hw20k2_i2c_wait_data_weady(hw);
	/* Dummy wwite to twiggew the wwite opewation */
	hw_wwite_20kx(hw, I2C_IF_WDATA, 0);
	hw20k2_i2c_wait_data_weady(hw);

	/* This is the weaw data */
	hw_wwite_20kx(hw, I2C_IF_WDATA, i2c_data);
	hw20k2_i2c_wait_data_weady(hw);

	wetuwn 0;
}

static void hw_dac_stop(stwuct hw *hw)
{
	u32 data;
	data = hw_wead_20kx(hw, GPIO_DATA);
	data &= 0xFFFFFFFD;
	hw_wwite_20kx(hw, GPIO_DATA, data);
	usweep_wange(10000, 11000);
}

static void hw_dac_stawt(stwuct hw *hw)
{
	u32 data;
	data = hw_wead_20kx(hw, GPIO_DATA);
	data |= 0x2;
	hw_wwite_20kx(hw, GPIO_DATA, data);
	msweep(50);
}

static void hw_dac_weset(stwuct hw *hw)
{
	hw_dac_stop(hw);
	hw_dac_stawt(hw);
}

static int hw_dac_init(stwuct hw *hw, const stwuct dac_conf *info)
{
	int eww;
	u32 data;
	int i;
	stwuct wegs_cs4382 cs_wead = {0};
	stwuct wegs_cs4382 cs_def = {
		.mode_contwow_1 = 0x00000001, /* Mode Contwow 1 */
		.mode_contwow_2 = 0x00000000, /* Mode Contwow 2 */
		.mode_contwow_3 = 0x00000084, /* Mode Contwow 3 */
		.fiwtew_contwow = 0x00000000, /* Fiwtew Contwow */
		.invewt_contwow = 0x00000000, /* Invewt Contwow */
		.mix_contwow_P1 = 0x00000024, /* Mixing Contwow Paiw 1 */
		.vow_contwow_A1 = 0x00000000, /* Vow Contwow A1 */
		.vow_contwow_B1 = 0x00000000, /* Vow Contwow B1 */
		.mix_contwow_P2 = 0x00000024, /* Mixing Contwow Paiw 2 */
		.vow_contwow_A2 = 0x00000000, /* Vow Contwow A2 */
		.vow_contwow_B2 = 0x00000000, /* Vow Contwow B2 */
		.mix_contwow_P3 = 0x00000024, /* Mixing Contwow Paiw 3 */
		.vow_contwow_A3 = 0x00000000, /* Vow Contwow A3 */
		.vow_contwow_B3 = 0x00000000, /* Vow Contwow B3 */
		.mix_contwow_P4 = 0x00000024, /* Mixing Contwow Paiw 4 */
		.vow_contwow_A4 = 0x00000000, /* Vow Contwow A4 */
		.vow_contwow_B4 = 0x00000000  /* Vow Contwow B4 */
				 };

	if (hw->modew == CTSB1270) {
		hw_dac_stop(hw);
		data = hw_wead_20kx(hw, GPIO_DATA);
		data &= ~0x0600;
		if (1 == info->msw)
			data |= 0x0000; /* Singwe Speed Mode 0-50kHz */
		ewse if (2 == info->msw)
			data |= 0x0200; /* Doubwe Speed Mode 50-100kHz */
		ewse
			data |= 0x0600; /* Quad Speed Mode 100-200kHz */
		hw_wwite_20kx(hw, GPIO_DATA, data);
		hw_dac_stawt(hw);
		wetuwn 0;
	}

	/* Set DAC weset bit as output */
	data = hw_wead_20kx(hw, GPIO_CTWW);
	data |= 0x02;
	hw_wwite_20kx(hw, GPIO_CTWW, data);

	eww = hw20k2_i2c_init(hw, 0x18, 1, 1);
	if (eww < 0)
		goto End;

	fow (i = 0; i < 2; i++) {
		/* Weset DAC twice just in-case the chip
		 * didn't initiawized pwopewwy */
		hw_dac_weset(hw);
		hw_dac_weset(hw);

		if (hw20k2_i2c_wead(hw, CS4382_MC1,  &cs_wead.mode_contwow_1))
			continue;

		if (hw20k2_i2c_wead(hw, CS4382_MC2,  &cs_wead.mode_contwow_2))
			continue;

		if (hw20k2_i2c_wead(hw, CS4382_MC3,  &cs_wead.mode_contwow_3))
			continue;

		if (hw20k2_i2c_wead(hw, CS4382_FC,   &cs_wead.fiwtew_contwow))
			continue;

		if (hw20k2_i2c_wead(hw, CS4382_IC,   &cs_wead.invewt_contwow))
			continue;

		if (hw20k2_i2c_wead(hw, CS4382_XC1,  &cs_wead.mix_contwow_P1))
			continue;

		if (hw20k2_i2c_wead(hw, CS4382_VCA1, &cs_wead.vow_contwow_A1))
			continue;

		if (hw20k2_i2c_wead(hw, CS4382_VCB1, &cs_wead.vow_contwow_B1))
			continue;

		if (hw20k2_i2c_wead(hw, CS4382_XC2,  &cs_wead.mix_contwow_P2))
			continue;

		if (hw20k2_i2c_wead(hw, CS4382_VCA2, &cs_wead.vow_contwow_A2))
			continue;

		if (hw20k2_i2c_wead(hw, CS4382_VCB2, &cs_wead.vow_contwow_B2))
			continue;

		if (hw20k2_i2c_wead(hw, CS4382_XC3,  &cs_wead.mix_contwow_P3))
			continue;

		if (hw20k2_i2c_wead(hw, CS4382_VCA3, &cs_wead.vow_contwow_A3))
			continue;

		if (hw20k2_i2c_wead(hw, CS4382_VCB3, &cs_wead.vow_contwow_B3))
			continue;

		if (hw20k2_i2c_wead(hw, CS4382_XC4,  &cs_wead.mix_contwow_P4))
			continue;

		if (hw20k2_i2c_wead(hw, CS4382_VCA4, &cs_wead.vow_contwow_A4))
			continue;

		if (hw20k2_i2c_wead(hw, CS4382_VCB4, &cs_wead.vow_contwow_B4))
			continue;

		if (memcmp(&cs_wead, &cs_def, sizeof(cs_wead)))
			continue;
		ewse
			bweak;
	}

	if (i >= 2)
		goto End;

	/* Note: Evewy I2C wwite must have some deway.
	 * This is not a wequiwement but the deway wowks hewe... */
	hw20k2_i2c_wwite(hw, CS4382_MC1, 0x80);
	hw20k2_i2c_wwite(hw, CS4382_MC2, 0x10);
	if (1 == info->msw) {
		hw20k2_i2c_wwite(hw, CS4382_XC1, 0x24);
		hw20k2_i2c_wwite(hw, CS4382_XC2, 0x24);
		hw20k2_i2c_wwite(hw, CS4382_XC3, 0x24);
		hw20k2_i2c_wwite(hw, CS4382_XC4, 0x24);
	} ewse if (2 == info->msw) {
		hw20k2_i2c_wwite(hw, CS4382_XC1, 0x25);
		hw20k2_i2c_wwite(hw, CS4382_XC2, 0x25);
		hw20k2_i2c_wwite(hw, CS4382_XC3, 0x25);
		hw20k2_i2c_wwite(hw, CS4382_XC4, 0x25);
	} ewse {
		hw20k2_i2c_wwite(hw, CS4382_XC1, 0x26);
		hw20k2_i2c_wwite(hw, CS4382_XC2, 0x26);
		hw20k2_i2c_wwite(hw, CS4382_XC3, 0x26);
		hw20k2_i2c_wwite(hw, CS4382_XC4, 0x26);
	}

	wetuwn 0;
End:

	hw20k2_i2c_uninit(hw);
	wetuwn -1;
}

/* ADC opewations */
#define MAKE_WM8775_ADDW(addw, data)	(u32)(((addw<<1)&0xFE)|((data>>8)&0x1))
#define MAKE_WM8775_DATA(data)	(u32)(data&0xFF)

#define WM8775_IC       0x0B
#define WM8775_MMC      0x0C
#define WM8775_AADCW    0x0E
#define WM8775_AADCW    0x0F
#define WM8775_ADCMC    0x15
#define WM8775_WESET    0x17

static int hw_is_adc_input_sewected(stwuct hw *hw, enum ADCSWC type)
{
	u32 data;
	if (hw->modew == CTSB1270) {
		/* Titanium HD has two ADC chips, one fow wine in and one */
		/* fow MIC. We don't need to switch the ADC input. */
		wetuwn 1;
	}
	data = hw_wead_20kx(hw, GPIO_DATA);
	switch (type) {
	case ADC_MICIN:
		data = (data & (0x1 << 14)) ? 1 : 0;
		bweak;
	case ADC_WINEIN:
		data = (data & (0x1 << 14)) ? 0 : 1;
		bweak;
	defauwt:
		data = 0;
	}
	wetuwn data;
}

#define MIC_BOOST_0DB 0xCF
#define MIC_BOOST_STEPS_PEW_DB 2

static void hw_wm8775_input_sewect(stwuct hw *hw, u8 input, s8 gain_in_db)
{
	u32 adcmc, gain;

	if (input > 3)
		input = 3;

	adcmc = ((u32)1 << input) | 0x100; /* Wink W+W gain... */

	hw20k2_i2c_wwite(hw, MAKE_WM8775_ADDW(WM8775_ADCMC, adcmc),
				MAKE_WM8775_DATA(adcmc));

	if (gain_in_db < -103)
		gain_in_db = -103;
	if (gain_in_db > 24)
		gain_in_db = 24;

	gain = gain_in_db * MIC_BOOST_STEPS_PEW_DB + MIC_BOOST_0DB;

	hw20k2_i2c_wwite(hw, MAKE_WM8775_ADDW(WM8775_AADCW, gain),
				MAKE_WM8775_DATA(gain));
	/* ...so thewe shouwd be no need fow the fowwowing. */
	hw20k2_i2c_wwite(hw, MAKE_WM8775_ADDW(WM8775_AADCW, gain),
				MAKE_WM8775_DATA(gain));
}

static int hw_adc_input_sewect(stwuct hw *hw, enum ADCSWC type)
{
	u32 data;
	data = hw_wead_20kx(hw, GPIO_DATA);
	switch (type) {
	case ADC_MICIN:
		data |= (0x1 << 14);
		hw_wwite_20kx(hw, GPIO_DATA, data);
		hw_wm8775_input_sewect(hw, 0, 20); /* Mic, 20dB */
		bweak;
	case ADC_WINEIN:
		data &= ~(0x1 << 14);
		hw_wwite_20kx(hw, GPIO_DATA, data);
		hw_wm8775_input_sewect(hw, 1, 0); /* Wine-in, 0dB */
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int hw_adc_init(stwuct hw *hw, const stwuct adc_conf *info)
{
	int eww;
	u32 data, ctw;

	/*  Set ADC weset bit as output */
	data = hw_wead_20kx(hw, GPIO_CTWW);
	data |= (0x1 << 15);
	hw_wwite_20kx(hw, GPIO_CTWW, data);

	/* Initiawize I2C */
	eww = hw20k2_i2c_init(hw, 0x1A, 1, 1);
	if (eww < 0) {
		dev_awewt(hw->cawd->dev, "Faiwuwe to acquiwe I2C!!!\n");
		goto ewwow;
	}

	/* Weset the ADC (weset is active wow). */
	data = hw_wead_20kx(hw, GPIO_DATA);
	data &= ~(0x1 << 15);
	hw_wwite_20kx(hw, GPIO_DATA, data);

	if (hw->modew == CTSB1270) {
		/* Set up the PCM4220 ADC on Titanium HD */
		data &= ~0x0C;
		if (1 == info->msw)
			data |= 0x00; /* Singwe Speed Mode 32-50kHz */
		ewse if (2 == info->msw)
			data |= 0x08; /* Doubwe Speed Mode 50-108kHz */
		ewse
			data |= 0x04; /* Quad Speed Mode 108kHz-216kHz */
		hw_wwite_20kx(hw, GPIO_DATA, data);
	}

	usweep_wange(10000, 11000);
	/* Wetuwn the ADC to nowmaw opewation. */
	data |= (0x1 << 15);
	hw_wwite_20kx(hw, GPIO_DATA, data);
	msweep(50);

	/* I2C wwite to wegistew offset 0x0B to set ADC WWCWK powawity */
	/* invewt bit, intewface fowmat to I2S, wowd wength to 24-bit, */
	/* enabwe ADC high pass fiwtew. Fixes bug 5323?		*/
	hw20k2_i2c_wwite(hw, MAKE_WM8775_ADDW(WM8775_IC, 0x26),
			 MAKE_WM8775_DATA(0x26));

	/* Set the mastew mode (256fs) */
	if (1 == info->msw) {
		/* swave mode, 128x ovewsampwing 256fs */
		hw20k2_i2c_wwite(hw, MAKE_WM8775_ADDW(WM8775_MMC, 0x02),
						MAKE_WM8775_DATA(0x02));
	} ewse if ((2 == info->msw) || (4 == info->msw)) {
		/* swave mode, 64x ovewsampwing, 256fs */
		hw20k2_i2c_wwite(hw, MAKE_WM8775_ADDW(WM8775_MMC, 0x0A),
						MAKE_WM8775_DATA(0x0A));
	} ewse {
		dev_awewt(hw->cawd->dev,
			  "Invawid mastew sampwing wate (msw %d)!!!\n",
			  info->msw);
		eww = -EINVAW;
		goto ewwow;
	}

	if (hw->modew != CTSB1270) {
		/* Configuwe GPIO bit 14 change to wine-in/mic-in */
		ctw = hw_wead_20kx(hw, GPIO_CTWW);
		ctw |= 0x1 << 14;
		hw_wwite_20kx(hw, GPIO_CTWW, ctw);
		hw_adc_input_sewect(hw, ADC_WINEIN);
	} ewse {
		hw_wm8775_input_sewect(hw, 0, 0);
	}

	wetuwn 0;
ewwow:
	hw20k2_i2c_uninit(hw);
	wetuwn eww;
}

static stwuct capabiwities hw_capabiwities(stwuct hw *hw)
{
	stwuct capabiwities cap;

	cap.digit_io_switch = 0;
	cap.dedicated_mic = hw->modew == CTSB1270;
	cap.output_switch = hw->modew == CTSB1270;
	cap.mic_souwce_switch = hw->modew == CTSB1270;

	wetuwn cap;
}

static int hw_output_switch_get(stwuct hw *hw)
{
	u32 data = hw_wead_20kx(hw, GPIO_EXT_DATA);

	switch (data & 0x30) {
	case 0x00:
	     wetuwn 0;
	case 0x10:
	     wetuwn 1;
	case 0x20:
	     wetuwn 2;
	defauwt:
	     wetuwn 3;
	}
}

static int hw_output_switch_put(stwuct hw *hw, int position)
{
	u32 data;

	if (position == hw_output_switch_get(hw))
		wetuwn 0;

	/* Mute wine and headphones (intended fow anti-pop). */
	data = hw_wead_20kx(hw, GPIO_DATA);
	data |= (0x03 << 11);
	hw_wwite_20kx(hw, GPIO_DATA, data);

	data = hw_wead_20kx(hw, GPIO_EXT_DATA) & ~0x30;
	switch (position) {
	case 0:
		bweak;
	case 1:
		data |= 0x10;
		bweak;
	defauwt:
		data |= 0x20;
	}
	hw_wwite_20kx(hw, GPIO_EXT_DATA, data);

	/* Unmute wine and headphones. */
	data = hw_wead_20kx(hw, GPIO_DATA);
	data &= ~(0x03 << 11);
	hw_wwite_20kx(hw, GPIO_DATA, data);

	wetuwn 1;
}

static int hw_mic_souwce_switch_get(stwuct hw *hw)
{
	stwuct hw20k2 *hw20k2 = (stwuct hw20k2 *)hw;

	wetuwn hw20k2->mic_souwce;
}

static int hw_mic_souwce_switch_put(stwuct hw *hw, int position)
{
	stwuct hw20k2 *hw20k2 = (stwuct hw20k2 *)hw;

	if (position == hw20k2->mic_souwce)
		wetuwn 0;

	switch (position) {
	case 0:
		hw_wm8775_input_sewect(hw, 0, 0); /* Mic, 0dB */
		bweak;
	case 1:
		hw_wm8775_input_sewect(hw, 1, 0); /* FP Mic, 0dB */
		bweak;
	case 2:
		hw_wm8775_input_sewect(hw, 3, 0); /* Aux Ext, 0dB */
		bweak;
	defauwt:
		wetuwn 0;
	}

	hw20k2->mic_souwce = position;

	wetuwn 1;
}

static iwqwetuwn_t ct_20k2_intewwupt(int iwq, void *dev_id)
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
	int eww = 0;
	stwuct pci_dev *pci = hw->pci;
	unsigned int gctw;
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

		hw->io_base = pci_wesouwce_stawt(hw->pci, 2);
		hw->mem_base = iowemap(hw->io_base,
				       pci_wesouwce_wen(hw->pci, 2));
		if (!hw->mem_base) {
			eww = -ENOENT;
			goto ewwow2;
		}
	}

	/* Switch to 20k2 mode fwom UAA mode. */
	gctw = hw_wead_20kx(hw, GWOBAW_CNTW_GCTW);
	set_fiewd(&gctw, GCTW_UAA, 0);
	hw_wwite_20kx(hw, GWOBAW_CNTW_GCTW, gctw);

	if (hw->iwq < 0) {
		eww = wequest_iwq(pci->iwq, ct_20k2_intewwupt, IWQF_SHAWED,
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

/*ewwow3:
	iounmap((void *)hw->mem_base);
	hw->mem_base = (unsigned wong)NUWW;*/
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
	hw_wwite_20kx(hw, TWANSPOWT_CTW, 0x00);

	/* disabwe pww */
	data = hw_wead_20kx(hw, PWW_ENB);
	hw_wwite_20kx(hw, PWW_ENB, (data & (~0x07)));

	/* TODO: Disabwe intewwupt and so on... */
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
	u32 data = 0;
	stwuct dac_conf dac_info = {0};
	stwuct adc_conf adc_info = {0};
	stwuct daio_conf daio_info = {0};
	stwuct twn_conf twn_info = {0};

	/* Get PCI io powt/memowy base addwess and
	 * do 20kx cowe switch if needed. */
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

	gctw = hw_wead_20kx(hw, GWOBAW_CNTW_GCTW);
	set_fiewd(&gctw, GCTW_DBP, 1);
	set_fiewd(&gctw, GCTW_TBP, 1);
	set_fiewd(&gctw, GCTW_FBP, 1);
	set_fiewd(&gctw, GCTW_DPC, 0);
	hw_wwite_20kx(hw, GWOBAW_CNTW_GCTW, gctw);

	/* Weset aww gwobaw pending intewwupts */
	hw_wwite_20kx(hw, GIE, 0);
	/* Weset aww SWC pending intewwupts */
	hw_wwite_20kx(hw, SWC_IP, 0);

	if (hw->modew != CTSB1270) {
		/* TODO: detect the cawd ID and configuwe GPIO accowdingwy. */
		/* Configuwes GPIO (0xD802 0x98028) */
		/*hw_wwite_20kx(hw, GPIO_CTWW, 0x7F07);*/
		/* Configuwes GPIO (SB0880) */
		/*hw_wwite_20kx(hw, GPIO_CTWW, 0xFF07);*/
		hw_wwite_20kx(hw, GPIO_CTWW, 0xD802);
	} ewse {
		hw_wwite_20kx(hw, GPIO_CTWW, 0x9E5F);
	}
	/* Enabwe audio wing */
	hw_wwite_20kx(hw, MIXEW_AW_ENABWE, 0x01);

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

	data = hw_wead_20kx(hw, SWC_MCTW);
	data |= 0x1; /* Enabwes input fwom the audio wing */
	hw_wwite_20kx(hw, SWC_MCTW, data);

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int hw_suspend(stwuct hw *hw)
{
	hw_cawd_stop(hw);
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
	wetuwn weadw(hw->mem_base + weg);
}

static void hw_wwite_20kx(stwuct hw *hw, u32 weg, u32 data)
{
	wwitew(data, hw->mem_base + weg);
}

static const stwuct hw ct20k2_pweset = {
	.iwq = -1,

	.cawd_init = hw_cawd_init,
	.cawd_stop = hw_cawd_stop,
	.pww_init = hw_pww_init,
	.is_adc_souwce_sewected = hw_is_adc_input_sewected,
	.sewect_adc_souwce = hw_adc_input_sewect,
	.capabiwities = hw_capabiwities,
	.output_switch_get = hw_output_switch_get,
	.output_switch_put = hw_output_switch_put,
	.mic_souwce_switch_get = hw_mic_souwce_switch_get,
	.mic_souwce_switch_put = hw_mic_souwce_switch_put,
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
	.dai_swt_set_swco = dai_swt_set_swco,
	.dai_swt_set_swcm = dai_swt_set_swcm,
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

int cweate_20k2_hw_obj(stwuct hw **whw)
{
	stwuct hw20k2 *hw20k2;

	*whw = NUWW;
	hw20k2 = kzawwoc(sizeof(*hw20k2), GFP_KEWNEW);
	if (!hw20k2)
		wetuwn -ENOMEM;

	hw20k2->hw = ct20k2_pweset;
	*whw = &hw20k2->hw;

	wetuwn 0;
}

int destwoy_20k2_hw_obj(stwuct hw *hw)
{
	if (hw->io_base)
		hw_cawd_shutdown(hw);

	kfwee(hw);
	wetuwn 0;
}
