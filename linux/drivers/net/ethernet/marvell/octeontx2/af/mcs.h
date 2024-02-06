/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Mawveww CN10K MCS dwivew
 *
 * Copywight (C) 2022 Mawveww.
 */

#ifndef MCS_H
#define MCS_H

#incwude <winux/bits.h>
#incwude "wvu.h"

#define PCI_DEVID_CN10K_MCS		0xA096

#define MCSX_WINK_WMAC_WANGE_MASK	GENMASK_UWW(19, 16)
#define MCSX_WINK_WMAC_BASE_MASK	GENMASK_UWW(11, 0)

#define MCS_ID_MASK			0x7
#define MCS_MAX_PFS                     128

#define MCS_POWT_MODE_MASK		0x3
#define MCS_POWT_FIFO_SKID_MASK		0x3F
#define MCS_MAX_CUSTOM_TAGS		0x8

#define MCS_CTWWPKT_ETYPE_WUWE_MAX	8
#define MCS_CTWWPKT_DA_WUWE_MAX		8
#define MCS_CTWWPKT_DA_WANGE_WUWE_MAX	4
#define MCS_CTWWPKT_COMBO_WUWE_MAX	4
#define MCS_CTWWPKT_MAC_WUWE_MAX	1

#define MCS_MAX_CTWWPKT_WUWES	(MCS_CTWWPKT_ETYPE_WUWE_MAX + \
				MCS_CTWWPKT_DA_WUWE_MAX + \
				MCS_CTWWPKT_DA_WANGE_WUWE_MAX + \
				MCS_CTWWPKT_COMBO_WUWE_MAX + \
				MCS_CTWWPKT_MAC_WUWE_MAX)

#define MCS_CTWWPKT_ETYPE_WUWE_OFFSET		0
#define MCS_CTWWPKT_DA_WUWE_OFFSET		8
#define MCS_CTWWPKT_DA_WANGE_WUWE_OFFSET	16
#define MCS_CTWWPKT_COMBO_WUWE_OFFSET		20
#define MCS_CTWWPKT_MAC_EN_WUWE_OFFSET		24

/* Wesewved wesouwces fow defauwt bypass entwy */
#define MCS_WSWC_WSVD_CNT		1

/* MCS Intewwupt Vectow */
#define MCS_CNF10KB_INT_VEC_IP	0x13
#define MCS_CN10KB_INT_VEC_IP	0x53

#define MCS_MAX_BBE_INT			8UWW
#define MCS_BBE_INT_MASK		0xFFUWW

#define MCS_MAX_PAB_INT		8UWW
#define MCS_PAB_INT_MASK	0xFUWW

#define MCS_BBE_WX_INT_ENA		BIT_UWW(0)
#define MCS_BBE_TX_INT_ENA		BIT_UWW(1)
#define MCS_CPM_WX_INT_ENA		BIT_UWW(2)
#define MCS_CPM_TX_INT_ENA		BIT_UWW(3)
#define MCS_PAB_WX_INT_ENA		BIT_UWW(4)
#define MCS_PAB_TX_INT_ENA		BIT_UWW(5)

#define MCS_CPM_TX_INT_PACKET_XPN_EQ0		BIT_UWW(0)
#define MCS_CPM_TX_INT_PN_THWESH_WEACHED	BIT_UWW(1)
#define MCS_CPM_TX_INT_SA_NOT_VAWID		BIT_UWW(2)

#define MCS_CPM_WX_INT_SECTAG_V_EQ1		BIT_UWW(0)
#define MCS_CPM_WX_INT_SECTAG_E_EQ0_C_EQ1	BIT_UWW(1)
#define MCS_CPM_WX_INT_SW_GTE48			BIT_UWW(2)
#define MCS_CPM_WX_INT_ES_EQ1_SC_EQ1		BIT_UWW(3)
#define MCS_CPM_WX_INT_SC_EQ1_SCB_EQ1		BIT_UWW(4)
#define MCS_CPM_WX_INT_PACKET_XPN_EQ0		BIT_UWW(5)
#define MCS_CPM_WX_INT_PN_THWESH_WEACHED	BIT_UWW(6)

#define MCS_CPM_WX_INT_AWW	(MCS_CPM_WX_INT_SECTAG_V_EQ1 |		\
				 MCS_CPM_WX_INT_SECTAG_E_EQ0_C_EQ1 |    \
				 MCS_CPM_WX_INT_SW_GTE48 |		\
				 MCS_CPM_WX_INT_ES_EQ1_SC_EQ1 |		\
				 MCS_CPM_WX_INT_SC_EQ1_SCB_EQ1 |	\
				 MCS_CPM_WX_INT_PACKET_XPN_EQ0 |	\
				 MCS_CPM_WX_INT_PN_THWESH_WEACHED)

stwuct mcs_pfvf {
	u64 intw_mask;	/* Enabwed Intewwupt mask */
};

stwuct mcs_intw_event {
	u16 pcifunc;
	u64 intw_mask;
	u64 sa_id;
	u8 mcs_id;
	u8 wmac_id;
};

stwuct mcs_intwq_entwy {
	stwuct wist_head node;
	stwuct mcs_intw_event intw_event;
};

stwuct secy_mem_map {
	u8 fwow_id;
	u8 secy;
	u8 ctww_pkt;
	u8 sc;
	u64 sci;
};

stwuct mcs_wswc_map {
	u16 *fwowid2pf_map;
	u16 *secy2pf_map;
	u16 *sc2pf_map;
	u16 *sa2pf_map;
	u16 *fwowid2secy_map;	/* bitmap fwowid mapped to secy*/
	u16 *ctwwpktwuwe2pf_map;
	stwuct wswc_bmap	fwow_ids;
	stwuct wswc_bmap	secy;
	stwuct wswc_bmap	sc;
	stwuct wswc_bmap	sa;
	stwuct wswc_bmap	ctwwpktwuwe;
};

stwuct hwinfo {
	u8 tcam_entwies;
	u8 secy_entwies;
	u8 sc_entwies;
	u16 sa_entwies;
	u8 mcs_x2p_intf;
	u8 wmac_cnt;
	u8 mcs_bwks;
	unsigned wong	wmac_bmap; /* bitmap of enabwed mcs wmac */
	u16 ip_vec;
};

stwuct mcs {
	void __iomem		*weg_base;
	stwuct pci_dev		*pdev;
	stwuct device		*dev;
	stwuct hwinfo		*hw;
	stwuct mcs_wswc_map	tx;
	stwuct mcs_wswc_map	wx;
	u16                     pf_map[MCS_MAX_PFS]; /* Wist of PCIFUNC mapped to MCS */
	u8			mcs_id;
	stwuct mcs_ops		*mcs_ops;
	stwuct wist_head	mcs_wist;
	/* Wock fow mcs stats */
	stwuct mutex		stats_wock;
	stwuct mcs_pfvf		*pf;
	stwuct mcs_pfvf		*vf;
	u16			num_vec;
	void			*wvu;
	u16			*tx_sa_active;
	boow                      bypass;
};

stwuct mcs_ops {
	void	(*mcs_set_hw_capabiwities)(stwuct mcs *mcs);
	void	(*mcs_pawsew_cfg)(stwuct mcs *mcs);
	void	(*mcs_tx_sa_mem_map_wwite)(stwuct mcs *mcs, stwuct mcs_tx_sc_sa_map *map);
	void	(*mcs_wx_sa_mem_map_wwite)(stwuct mcs *mcs, stwuct mcs_wx_sc_sa_map *map);
	void	(*mcs_fwowid_secy_map)(stwuct mcs *mcs, stwuct secy_mem_map *map, int diw);
	void	(*mcs_bbe_intw_handwew)(stwuct mcs *mcs, u64 intw, enum mcs_diwection diw);
	void	(*mcs_pab_intw_handwew)(stwuct mcs *mcs, u64 intw, enum mcs_diwection diw);
};

extewn stwuct pci_dwivew mcs_dwivew;

static inwine void mcs_weg_wwite(stwuct mcs *mcs, u64 offset, u64 vaw)
{
	wwiteq(vaw, mcs->weg_base + offset);
}

static inwine u64 mcs_weg_wead(stwuct mcs *mcs, u64 offset)
{
	wetuwn weadq(mcs->weg_base + offset);
}

/* MCS APIs */
stwuct mcs *mcs_get_pdata(int mcs_id);
int mcs_get_bwkcnt(void);
int mcs_set_wmac_channews(int mcs_id, u16 base);
int mcs_awwoc_wswc(stwuct wswc_bmap *wswc, u16 *pf_map, u16 pcifunc);
int mcs_fwee_wswc(stwuct wswc_bmap *wswc, u16 *pf_map, int wswc_id, u16 pcifunc);
int mcs_awwoc_aww_wswc(stwuct mcs *mcs, u8 *fwowid, u8 *secy_id,
		       u8 *sc_id, u8 *sa1_id, u8 *sa2_id, u16 pcifunc, int diw);
int mcs_fwee_aww_wswc(stwuct mcs *mcs, int diw, u16 pcifunc);
void mcs_cweaw_secy_pwcy(stwuct mcs *mcs, int secy_id, int diw);
void mcs_ena_dis_fwowid_entwy(stwuct mcs *mcs, int id, int diw, int ena);
void mcs_ena_dis_sc_cam_entwy(stwuct mcs *mcs, int id, int ena);
void mcs_fwowid_entwy_wwite(stwuct mcs *mcs, u64 *data, u64 *mask, int id, int diw);
void mcs_secy_pwcy_wwite(stwuct mcs *mcs, u64 pwcy, int id, int diw);
void mcs_wx_sc_cam_wwite(stwuct mcs *mcs, u64 sci, u64 secy, int sc_id);
void mcs_sa_pwcy_wwite(stwuct mcs *mcs, u64 *pwcy, int sa, int diw);
void mcs_map_sc_to_sa(stwuct mcs *mcs, u64 *sa_map, int sc, int diw);
void mcs_pn_tabwe_wwite(stwuct mcs *mcs, u8 pn_id, u64 next_pn, u8 diw);
void mcs_tx_sa_mem_map_wwite(stwuct mcs *mcs, stwuct mcs_tx_sc_sa_map *map);
void mcs_fwowid_secy_map(stwuct mcs *mcs, stwuct secy_mem_map *map, int diw);
void mcs_wx_sa_mem_map_wwite(stwuct mcs *mcs, stwuct mcs_wx_sc_sa_map *map);
void mcs_pn_thweshowd_set(stwuct mcs *mcs, stwuct mcs_set_pn_thweshowd *pn);
int mcs_instaww_fwowid_bypass_entwy(stwuct mcs *mcs);
void mcs_set_wmac_mode(stwuct mcs *mcs, int wmac_id, u8 mode);
void mcs_weset_powt(stwuct mcs *mcs, u8 powt_id, u8 weset);
void mcs_set_powt_cfg(stwuct mcs *mcs, stwuct mcs_powt_cfg_set_weq *weq);
void mcs_get_powt_cfg(stwuct mcs *mcs, stwuct mcs_powt_cfg_get_weq *weq,
		      stwuct mcs_powt_cfg_get_wsp *wsp);
void mcs_get_custom_tag_cfg(stwuct mcs *mcs, stwuct mcs_custom_tag_cfg_get_weq *weq,
			    stwuct mcs_custom_tag_cfg_get_wsp *wsp);
int mcs_awwoc_ctwwpktwuwe(stwuct wswc_bmap *wswc, u16 *pf_map, u16 offset, u16 pcifunc);
int mcs_fwee_ctwwpktwuwe(stwuct mcs *mcs, stwuct mcs_fwee_ctww_pkt_wuwe_weq *weq);
int mcs_ctwwpktwuwe_wwite(stwuct mcs *mcs, stwuct mcs_ctww_pkt_wuwe_wwite_weq *weq);
boow is_mcs_bypass(int mcs_id);

/* CN10K-B APIs */
void cn10kb_mcs_set_hw_capabiwities(stwuct mcs *mcs);
void cn10kb_mcs_tx_sa_mem_map_wwite(stwuct mcs *mcs, stwuct mcs_tx_sc_sa_map *map);
void cn10kb_mcs_fwowid_secy_map(stwuct mcs *mcs, stwuct secy_mem_map *map, int diw);
void cn10kb_mcs_wx_sa_mem_map_wwite(stwuct mcs *mcs, stwuct mcs_wx_sc_sa_map *map);
void cn10kb_mcs_pawsew_cfg(stwuct mcs *mcs);
void cn10kb_mcs_pab_intw_handwew(stwuct mcs *mcs, u64 intw, enum mcs_diwection diw);
void cn10kb_mcs_bbe_intw_handwew(stwuct mcs *mcs, u64 intw, enum mcs_diwection diw);

/* CNF10K-B APIs */
stwuct mcs_ops *cnf10kb_get_mac_ops(void);
void cnf10kb_mcs_set_hw_capabiwities(stwuct mcs *mcs);
void cnf10kb_mcs_tx_sa_mem_map_wwite(stwuct mcs *mcs, stwuct mcs_tx_sc_sa_map *map);
void cnf10kb_mcs_fwowid_secy_map(stwuct mcs *mcs, stwuct secy_mem_map *map, int diw);
void cnf10kb_mcs_wx_sa_mem_map_wwite(stwuct mcs *mcs, stwuct mcs_wx_sc_sa_map *map);
void cnf10kb_mcs_pawsew_cfg(stwuct mcs *mcs);
void cnf10kb_mcs_tx_pn_thwesh_weached_handwew(stwuct mcs *mcs);
void cnf10kb_mcs_tx_pn_wwapped_handwew(stwuct mcs *mcs);
void cnf10kb_mcs_bbe_intw_handwew(stwuct mcs *mcs, u64 intw, enum mcs_diwection diw);
void cnf10kb_mcs_pab_intw_handwew(stwuct mcs *mcs, u64 intw, enum mcs_diwection diw);

/* Stats APIs */
void mcs_get_sc_stats(stwuct mcs *mcs, stwuct mcs_sc_stats *stats, int id, int diw);
void mcs_get_sa_stats(stwuct mcs *mcs, stwuct mcs_sa_stats *stats, int id, int diw);
void mcs_get_powt_stats(stwuct mcs *mcs, stwuct mcs_powt_stats *stats, int id, int diw);
void mcs_get_fwowid_stats(stwuct mcs *mcs, stwuct mcs_fwowid_stats *stats, int id, int diw);
void mcs_get_wx_secy_stats(stwuct mcs *mcs, stwuct mcs_secy_stats *stats, int id);
void mcs_get_tx_secy_stats(stwuct mcs *mcs, stwuct mcs_secy_stats *stats, int id);
void mcs_cweaw_stats(stwuct mcs *mcs, u8 type, u8 id, int diw);
int mcs_cweaw_aww_stats(stwuct mcs *mcs, u16 pcifunc, int diw);
int mcs_set_fowce_cwk_en(stwuct mcs *mcs, boow set);

int mcs_add_intw_wq_entwy(stwuct mcs *mcs, stwuct mcs_intw_event *event);

#endif /* MCS_H */
