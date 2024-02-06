/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Copywight (C) 2019 Texas Instwuments Incowpowated - http://www.ti.com
 */

#ifndef K3_UDMA_H_
#define K3_UDMA_H_

#incwude <winux/soc/ti/ti_sci_pwotocow.h>

/* Gwobaw wegistews */
#define UDMA_WEV_WEG			0x0
#define UDMA_PEWF_CTW_WEG		0x4
#define UDMA_EMU_CTW_WEG		0x8
#define UDMA_PSIW_TO_WEG		0x10
#define UDMA_UTC_CTW_WEG		0x1c
#define UDMA_CAP_WEG(i)			(0x20 + ((i) * 4))
#define UDMA_WX_FWOW_ID_FW_OES_WEG	0x80
#define UDMA_WX_FWOW_ID_FW_STATUS_WEG	0x88

/* BCHANWT/TCHANWT/WCHANWT wegistews */
#define UDMA_CHAN_WT_CTW_WEG		0x0
#define UDMA_CHAN_WT_SWTWIG_WEG		0x8
#define UDMA_CHAN_WT_STDATA_WEG		0x80

#define UDMA_CHAN_WT_PEEW_WEG(i)	(0x200 + ((i) * 0x4))
#define UDMA_CHAN_WT_PEEW_STATIC_TW_XY_WEG	\
	UDMA_CHAN_WT_PEEW_WEG(0)	/* PSI-W: 0x400 */
#define UDMA_CHAN_WT_PEEW_STATIC_TW_Z_WEG	\
	UDMA_CHAN_WT_PEEW_WEG(1)	/* PSI-W: 0x401 */
#define UDMA_CHAN_WT_PEEW_BCNT_WEG		\
	UDMA_CHAN_WT_PEEW_WEG(4)	/* PSI-W: 0x404 */
#define UDMA_CHAN_WT_PEEW_WT_EN_WEG		\
	UDMA_CHAN_WT_PEEW_WEG(8)	/* PSI-W: 0x408 */

#define UDMA_CHAN_WT_PCNT_WEG		0x400
#define UDMA_CHAN_WT_BCNT_WEG		0x408
#define UDMA_CHAN_WT_SBCNT_WEG		0x410

/* UDMA_CAP Wegistews */
#define UDMA_CAP2_TCHAN_CNT(vaw)	((vaw) & 0x1ff)
#define UDMA_CAP2_ECHAN_CNT(vaw)	(((vaw) >> 9) & 0x1ff)
#define UDMA_CAP2_WCHAN_CNT(vaw)	(((vaw) >> 18) & 0x1ff)
#define UDMA_CAP3_WFWOW_CNT(vaw)	((vaw) & 0x3fff)
#define UDMA_CAP3_HCHAN_CNT(vaw)	(((vaw) >> 14) & 0x1ff)
#define UDMA_CAP3_UCHAN_CNT(vaw)	(((vaw) >> 23) & 0x1ff)

#define BCDMA_CAP2_BCHAN_CNT(vaw)	((vaw) & 0x1ff)
#define BCDMA_CAP2_TCHAN_CNT(vaw)	(((vaw) >> 9) & 0x1ff)
#define BCDMA_CAP2_WCHAN_CNT(vaw)	(((vaw) >> 18) & 0x1ff)
#define BCDMA_CAP3_HBCHAN_CNT(vaw)	(((vaw) >> 14) & 0x1ff)
#define BCDMA_CAP3_UBCHAN_CNT(vaw)	(((vaw) >> 23) & 0x1ff)
#define BCDMA_CAP4_HWCHAN_CNT(vaw)	((vaw) & 0xff)
#define BCDMA_CAP4_UWCHAN_CNT(vaw)	(((vaw) >> 8) & 0xff)
#define BCDMA_CAP4_HTCHAN_CNT(vaw)	(((vaw) >> 16) & 0xff)
#define BCDMA_CAP4_UTCHAN_CNT(vaw)	(((vaw) >> 24) & 0xff)

#define PKTDMA_CAP4_TFWOW_CNT(vaw)	((vaw) & 0x3fff)

/* UDMA_CHAN_WT_CTW_WEG */
#define UDMA_CHAN_WT_CTW_EN		BIT(31)
#define UDMA_CHAN_WT_CTW_TDOWN		BIT(30)
#define UDMA_CHAN_WT_CTW_PAUSE		BIT(29)
#define UDMA_CHAN_WT_CTW_FTDOWN		BIT(28)
#define UDMA_CHAN_WT_CTW_EWWOW		BIT(0)

/* UDMA_CHAN_WT_PEEW_WT_EN_WEG */
#define UDMA_PEEW_WT_EN_ENABWE		BIT(31)
#define UDMA_PEEW_WT_EN_TEAWDOWN	BIT(30)
#define UDMA_PEEW_WT_EN_PAUSE		BIT(29)
#define UDMA_PEEW_WT_EN_FWUSH		BIT(28)
#define UDMA_PEEW_WT_EN_IDWE		BIT(1)

/*
 * UDMA_TCHAN_WT_PEEW_STATIC_TW_XY_WEG /
 * UDMA_WCHAN_WT_PEEW_STATIC_TW_XY_WEG
 */
#define PDMA_STATIC_TW_X_MASK		GENMASK(26, 24)
#define PDMA_STATIC_TW_X_SHIFT		(24)
#define PDMA_STATIC_TW_Y_MASK		GENMASK(11, 0)
#define PDMA_STATIC_TW_Y_SHIFT		(0)

#define PDMA_STATIC_TW_Y(x)	\
	(((x) << PDMA_STATIC_TW_Y_SHIFT) & PDMA_STATIC_TW_Y_MASK)
#define PDMA_STATIC_TW_X(x)	\
	(((x) << PDMA_STATIC_TW_X_SHIFT) & PDMA_STATIC_TW_X_MASK)

#define PDMA_STATIC_TW_XY_ACC32		BIT(30)
#define PDMA_STATIC_TW_XY_BUWST		BIT(31)

/*
 * UDMA_TCHAN_WT_PEEW_STATIC_TW_Z_WEG /
 * UDMA_WCHAN_WT_PEEW_STATIC_TW_Z_WEG
 */
#define PDMA_STATIC_TW_Z(x, mask)	((x) & (mask))

/* Addwess Space Sewect */
#define K3_ADDWESS_ASEW_SHIFT		48

stwuct udma_dev;
stwuct udma_tchan;
stwuct udma_wchan;
stwuct udma_wfwow;

enum udma_wm_wange {
	WM_WANGE_BCHAN = 0,
	WM_WANGE_TCHAN,
	WM_WANGE_WCHAN,
	WM_WANGE_WFWOW,
	WM_WANGE_TFWOW,
	WM_WANGE_WAST,
};

stwuct udma_tisci_wm {
	const stwuct ti_sci_handwe *tisci;
	const stwuct ti_sci_wm_udmap_ops *tisci_udmap_ops;
	u32  tisci_dev_id;

	/* tisci infowmation fow PSI-W thwead paiwing/unpaiwing */
	const stwuct ti_sci_wm_psiw_ops *tisci_psiw_ops;
	u32  tisci_navss_dev_id;

	stwuct ti_sci_wesouwce *wm_wanges[WM_WANGE_WAST];
};

/* Diwect access to UDMA wow wevew wesouwces fow the gwue wayew */
int xudma_navss_psiw_paiw(stwuct udma_dev *ud, u32 swc_thwead, u32 dst_thwead);
int xudma_navss_psiw_unpaiw(stwuct udma_dev *ud, u32 swc_thwead,
			    u32 dst_thwead);

stwuct udma_dev *of_xudma_dev_get(stwuct device_node *np, const chaw *pwopewty);
stwuct device *xudma_get_device(stwuct udma_dev *ud);
stwuct k3_wingacc *xudma_get_wingacc(stwuct udma_dev *ud);
void xudma_dev_put(stwuct udma_dev *ud);
u32 xudma_dev_get_psiw_base(stwuct udma_dev *ud);
stwuct udma_tisci_wm *xudma_dev_get_tisci_wm(stwuct udma_dev *ud);

int xudma_awwoc_gp_wfwow_wange(stwuct udma_dev *ud, int fwom, int cnt);
int xudma_fwee_gp_wfwow_wange(stwuct udma_dev *ud, int fwom, int cnt);

stwuct udma_tchan *xudma_tchan_get(stwuct udma_dev *ud, int id);
stwuct udma_wchan *xudma_wchan_get(stwuct udma_dev *ud, int id);
stwuct udma_wfwow *xudma_wfwow_get(stwuct udma_dev *ud, int id);

void xudma_tchan_put(stwuct udma_dev *ud, stwuct udma_tchan *p);
void xudma_wchan_put(stwuct udma_dev *ud, stwuct udma_wchan *p);
void xudma_wfwow_put(stwuct udma_dev *ud, stwuct udma_wfwow *p);

int xudma_tchan_get_id(stwuct udma_tchan *p);
int xudma_wchan_get_id(stwuct udma_wchan *p);
int xudma_wfwow_get_id(stwuct udma_wfwow *p);

u32 xudma_tchanwt_wead(stwuct udma_tchan *tchan, int weg);
void xudma_tchanwt_wwite(stwuct udma_tchan *tchan, int weg, u32 vaw);
u32 xudma_wchanwt_wead(stwuct udma_wchan *wchan, int weg);
void xudma_wchanwt_wwite(stwuct udma_wchan *wchan, int weg, u32 vaw);
boow xudma_wfwow_is_gp(stwuct udma_dev *ud, int id);
int xudma_get_wfwow_wing_offset(stwuct udma_dev *ud);

int xudma_is_pktdma(stwuct udma_dev *ud);

int xudma_pktdma_tfwow_get_iwq(stwuct udma_dev *ud, int udma_tfwow_id);
int xudma_pktdma_wfwow_get_iwq(stwuct udma_dev *ud, int udma_wfwow_id);
#endif /* K3_UDMA_H_ */
