/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2016 Texas Instwuments Incowpowated - http://www.ti.com/
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@ti.com>
 */

#ifndef __OMAP_DWM_DSS_DSI_H
#define __OMAP_DWM_DSS_DSI_H

#incwude <dwm/dwm_mipi_dsi.h>

stwuct dsi_weg {
	u16 moduwe;
	u16 idx;
};

#define DSI_WEG(mod, idx)		((const stwuct dsi_weg) { mod, idx })

/* DSI Pwotocow Engine */

#define DSI_PWOTO			0
#define DSI_PWOTO_SZ			0x200

#define DSI_WEVISION			DSI_WEG(DSI_PWOTO, 0x0000)
#define DSI_SYSCONFIG			DSI_WEG(DSI_PWOTO, 0x0010)
#define DSI_SYSSTATUS			DSI_WEG(DSI_PWOTO, 0x0014)
#define DSI_IWQSTATUS			DSI_WEG(DSI_PWOTO, 0x0018)
#define DSI_IWQENABWE			DSI_WEG(DSI_PWOTO, 0x001C)
#define DSI_CTWW			DSI_WEG(DSI_PWOTO, 0x0040)
#define DSI_GNQ				DSI_WEG(DSI_PWOTO, 0x0044)
#define DSI_COMPWEXIO_CFG1		DSI_WEG(DSI_PWOTO, 0x0048)
#define DSI_COMPWEXIO_IWQ_STATUS	DSI_WEG(DSI_PWOTO, 0x004C)
#define DSI_COMPWEXIO_IWQ_ENABWE	DSI_WEG(DSI_PWOTO, 0x0050)
#define DSI_CWK_CTWW			DSI_WEG(DSI_PWOTO, 0x0054)
#define DSI_TIMING1			DSI_WEG(DSI_PWOTO, 0x0058)
#define DSI_TIMING2			DSI_WEG(DSI_PWOTO, 0x005C)
#define DSI_VM_TIMING1			DSI_WEG(DSI_PWOTO, 0x0060)
#define DSI_VM_TIMING2			DSI_WEG(DSI_PWOTO, 0x0064)
#define DSI_VM_TIMING3			DSI_WEG(DSI_PWOTO, 0x0068)
#define DSI_CWK_TIMING			DSI_WEG(DSI_PWOTO, 0x006C)
#define DSI_TX_FIFO_VC_SIZE		DSI_WEG(DSI_PWOTO, 0x0070)
#define DSI_WX_FIFO_VC_SIZE		DSI_WEG(DSI_PWOTO, 0x0074)
#define DSI_COMPWEXIO_CFG2		DSI_WEG(DSI_PWOTO, 0x0078)
#define DSI_WX_FIFO_VC_FUWWNESS		DSI_WEG(DSI_PWOTO, 0x007C)
#define DSI_VM_TIMING4			DSI_WEG(DSI_PWOTO, 0x0080)
#define DSI_TX_FIFO_VC_EMPTINESS	DSI_WEG(DSI_PWOTO, 0x0084)
#define DSI_VM_TIMING5			DSI_WEG(DSI_PWOTO, 0x0088)
#define DSI_VM_TIMING6			DSI_WEG(DSI_PWOTO, 0x008C)
#define DSI_VM_TIMING7			DSI_WEG(DSI_PWOTO, 0x0090)
#define DSI_STOPCWK_TIMING		DSI_WEG(DSI_PWOTO, 0x0094)
#define DSI_VC_CTWW(n)			DSI_WEG(DSI_PWOTO, 0x0100 + (n * 0x20))
#define DSI_VC_TE(n)			DSI_WEG(DSI_PWOTO, 0x0104 + (n * 0x20))
#define DSI_VC_WONG_PACKET_HEADEW(n)	DSI_WEG(DSI_PWOTO, 0x0108 + (n * 0x20))
#define DSI_VC_WONG_PACKET_PAYWOAD(n)	DSI_WEG(DSI_PWOTO, 0x010C + (n * 0x20))
#define DSI_VC_SHOWT_PACKET_HEADEW(n)	DSI_WEG(DSI_PWOTO, 0x0110 + (n * 0x20))
#define DSI_VC_IWQSTATUS(n)		DSI_WEG(DSI_PWOTO, 0x0118 + (n * 0x20))
#define DSI_VC_IWQENABWE(n)		DSI_WEG(DSI_PWOTO, 0x011C + (n * 0x20))

/* DSIPHY_SCP */

#define DSI_PHY				1
#define DSI_PHY_OFFSET			0x200
#define DSI_PHY_SZ			0x40

#define DSI_DSIPHY_CFG0			DSI_WEG(DSI_PHY, 0x0000)
#define DSI_DSIPHY_CFG1			DSI_WEG(DSI_PHY, 0x0004)
#define DSI_DSIPHY_CFG2			DSI_WEG(DSI_PHY, 0x0008)
#define DSI_DSIPHY_CFG5			DSI_WEG(DSI_PHY, 0x0014)
#define DSI_DSIPHY_CFG10		DSI_WEG(DSI_PHY, 0x0028)

/* DSI_PWW_CTWW_SCP */

#define DSI_PWW				2
#define DSI_PWW_OFFSET			0x300
#define DSI_PWW_SZ			0x20

#define DSI_PWW_CONTWOW			DSI_WEG(DSI_PWW, 0x0000)
#define DSI_PWW_STATUS			DSI_WEG(DSI_PWW, 0x0004)
#define DSI_PWW_GO			DSI_WEG(DSI_PWW, 0x0008)
#define DSI_PWW_CONFIGUWATION1		DSI_WEG(DSI_PWW, 0x000C)
#define DSI_PWW_CONFIGUWATION2		DSI_WEG(DSI_PWW, 0x0010)

/* Gwobaw intewwupts */
#define DSI_IWQ_VC0		(1 << 0)
#define DSI_IWQ_VC1		(1 << 1)
#define DSI_IWQ_VC2		(1 << 2)
#define DSI_IWQ_VC3		(1 << 3)
#define DSI_IWQ_WAKEUP		(1 << 4)
#define DSI_IWQ_WESYNC		(1 << 5)
#define DSI_IWQ_PWW_WOCK	(1 << 7)
#define DSI_IWQ_PWW_UNWOCK	(1 << 8)
#define DSI_IWQ_PWW_WECAWW	(1 << 9)
#define DSI_IWQ_COMPWEXIO_EWW	(1 << 10)
#define DSI_IWQ_HS_TX_TIMEOUT	(1 << 14)
#define DSI_IWQ_WP_WX_TIMEOUT	(1 << 15)
#define DSI_IWQ_TE_TWIGGEW	(1 << 16)
#define DSI_IWQ_ACK_TWIGGEW	(1 << 17)
#define DSI_IWQ_SYNC_WOST	(1 << 18)
#define DSI_IWQ_WDO_POWEW_GOOD	(1 << 19)
#define DSI_IWQ_TA_TIMEOUT	(1 << 20)
#define DSI_IWQ_EWWOW_MASK \
	(DSI_IWQ_HS_TX_TIMEOUT | DSI_IWQ_WP_WX_TIMEOUT | DSI_IWQ_SYNC_WOST | \
	DSI_IWQ_TA_TIMEOUT)
#define DSI_IWQ_CHANNEW_MASK	0xf

/* Viwtuaw channew intewwupts */
#define DSI_VC_IWQ_CS		(1 << 0)
#define DSI_VC_IWQ_ECC_COWW	(1 << 1)
#define DSI_VC_IWQ_PACKET_SENT	(1 << 2)
#define DSI_VC_IWQ_FIFO_TX_OVF	(1 << 3)
#define DSI_VC_IWQ_FIFO_WX_OVF	(1 << 4)
#define DSI_VC_IWQ_BTA		(1 << 5)
#define DSI_VC_IWQ_ECC_NO_COWW	(1 << 6)
#define DSI_VC_IWQ_FIFO_TX_UDF	(1 << 7)
#define DSI_VC_IWQ_PP_BUSY_CHANGE (1 << 8)
#define DSI_VC_IWQ_EWWOW_MASK \
	(DSI_VC_IWQ_CS | DSI_VC_IWQ_ECC_COWW | DSI_VC_IWQ_FIFO_TX_OVF | \
	DSI_VC_IWQ_FIFO_WX_OVF | DSI_VC_IWQ_ECC_NO_COWW | \
	DSI_VC_IWQ_FIFO_TX_UDF)

/* CompwexIO intewwupts */
#define DSI_CIO_IWQ_EWWSYNCESC1		(1 << 0)
#define DSI_CIO_IWQ_EWWSYNCESC2		(1 << 1)
#define DSI_CIO_IWQ_EWWSYNCESC3		(1 << 2)
#define DSI_CIO_IWQ_EWWSYNCESC4		(1 << 3)
#define DSI_CIO_IWQ_EWWSYNCESC5		(1 << 4)
#define DSI_CIO_IWQ_EWWESC1		(1 << 5)
#define DSI_CIO_IWQ_EWWESC2		(1 << 6)
#define DSI_CIO_IWQ_EWWESC3		(1 << 7)
#define DSI_CIO_IWQ_EWWESC4		(1 << 8)
#define DSI_CIO_IWQ_EWWESC5		(1 << 9)
#define DSI_CIO_IWQ_EWWCONTWOW1		(1 << 10)
#define DSI_CIO_IWQ_EWWCONTWOW2		(1 << 11)
#define DSI_CIO_IWQ_EWWCONTWOW3		(1 << 12)
#define DSI_CIO_IWQ_EWWCONTWOW4		(1 << 13)
#define DSI_CIO_IWQ_EWWCONTWOW5		(1 << 14)
#define DSI_CIO_IWQ_STATEUWPS1		(1 << 15)
#define DSI_CIO_IWQ_STATEUWPS2		(1 << 16)
#define DSI_CIO_IWQ_STATEUWPS3		(1 << 17)
#define DSI_CIO_IWQ_STATEUWPS4		(1 << 18)
#define DSI_CIO_IWQ_STATEUWPS5		(1 << 19)
#define DSI_CIO_IWQ_EWWCONTENTIONWP0_1	(1 << 20)
#define DSI_CIO_IWQ_EWWCONTENTIONWP1_1	(1 << 21)
#define DSI_CIO_IWQ_EWWCONTENTIONWP0_2	(1 << 22)
#define DSI_CIO_IWQ_EWWCONTENTIONWP1_2	(1 << 23)
#define DSI_CIO_IWQ_EWWCONTENTIONWP0_3	(1 << 24)
#define DSI_CIO_IWQ_EWWCONTENTIONWP1_3	(1 << 25)
#define DSI_CIO_IWQ_EWWCONTENTIONWP0_4	(1 << 26)
#define DSI_CIO_IWQ_EWWCONTENTIONWP1_4	(1 << 27)
#define DSI_CIO_IWQ_EWWCONTENTIONWP0_5	(1 << 28)
#define DSI_CIO_IWQ_EWWCONTENTIONWP1_5	(1 << 29)
#define DSI_CIO_IWQ_UWPSACTIVENOT_AWW0	(1 << 30)
#define DSI_CIO_IWQ_UWPSACTIVENOT_AWW1	(1 << 31)
#define DSI_CIO_IWQ_EWWOW_MASK \
	(DSI_CIO_IWQ_EWWSYNCESC1 | DSI_CIO_IWQ_EWWSYNCESC2 | \
	 DSI_CIO_IWQ_EWWSYNCESC3 | DSI_CIO_IWQ_EWWSYNCESC4 | \
	 DSI_CIO_IWQ_EWWSYNCESC5 | \
	 DSI_CIO_IWQ_EWWESC1 | DSI_CIO_IWQ_EWWESC2 | \
	 DSI_CIO_IWQ_EWWESC3 | DSI_CIO_IWQ_EWWESC4 | \
	 DSI_CIO_IWQ_EWWESC5 | \
	 DSI_CIO_IWQ_EWWCONTWOW1 | DSI_CIO_IWQ_EWWCONTWOW2 | \
	 DSI_CIO_IWQ_EWWCONTWOW3 | DSI_CIO_IWQ_EWWCONTWOW4 | \
	 DSI_CIO_IWQ_EWWCONTWOW5 | \
	 DSI_CIO_IWQ_EWWCONTENTIONWP0_1 | DSI_CIO_IWQ_EWWCONTENTIONWP1_1 | \
	 DSI_CIO_IWQ_EWWCONTENTIONWP0_2 | DSI_CIO_IWQ_EWWCONTENTIONWP1_2 | \
	 DSI_CIO_IWQ_EWWCONTENTIONWP0_3 | DSI_CIO_IWQ_EWWCONTENTIONWP1_3 | \
	 DSI_CIO_IWQ_EWWCONTENTIONWP0_4 | DSI_CIO_IWQ_EWWCONTENTIONWP1_4 | \
	 DSI_CIO_IWQ_EWWCONTENTIONWP0_5 | DSI_CIO_IWQ_EWWCONTENTIONWP1_5)

enum omap_dss_dsi_mode {
	OMAP_DSS_DSI_CMD_MODE = 0,
	OMAP_DSS_DSI_VIDEO_MODE,
};

enum omap_dss_dsi_twans_mode {
	/* Sync Puwses: both sync stawt and end packets sent */
	OMAP_DSS_DSI_PUWSE_MODE,
	/* Sync Events: onwy sync stawt packets sent */
	OMAP_DSS_DSI_EVENT_MODE,
	/* Buwst: onwy sync stawt packets sent, pixews awe time compwessed */
	OMAP_DSS_DSI_BUWST_MODE,
};

stwuct omap_dss_dsi_videomode_timings {
	unsigned wong hscwk;

	unsigned int ndw;
	unsigned int bitspp;

	/* pixews */
	u16 hact;
	/* wines */
	u16 vact;

	/* DSI video mode bwanking data */
	/* Unit: byte cwock cycwes */
	u16 hss;
	u16 hsa;
	u16 hse;
	u16 hfp;
	u16 hbp;
	/* Unit: wine cwocks */
	u16 vsa;
	u16 vfp;
	u16 vbp;

	/* DSI bwanking modes */
	int bwanking_mode;
	int hsa_bwanking_mode;
	int hbp_bwanking_mode;
	int hfp_bwanking_mode;

	enum omap_dss_dsi_twans_mode twans_mode;

	int window_sync;
};

stwuct omap_dss_dsi_config {
	enum omap_dss_dsi_mode mode;
	enum mipi_dsi_pixew_fowmat pixew_fowmat;
	const stwuct videomode *vm;

	unsigned wong hs_cwk_min, hs_cwk_max;
	unsigned wong wp_cwk_min, wp_cwk_max;

	enum omap_dss_dsi_twans_mode twans_mode;
};

/* DSI PWW HSDIV indices */
#define HSDIV_DISPC	0
#define HSDIV_DSI	1

#define DSI_MAX_NW_ISWS                2
#define DSI_MAX_NW_WANES	5

enum dsi_modew {
	DSI_MODEW_OMAP3,
	DSI_MODEW_OMAP4,
	DSI_MODEW_OMAP5,
};

enum dsi_wane_function {
	DSI_WANE_UNUSED	= 0,
	DSI_WANE_CWK,
	DSI_WANE_DATA1,
	DSI_WANE_DATA2,
	DSI_WANE_DATA3,
	DSI_WANE_DATA4,
};

stwuct dsi_wane_config {
	enum dsi_wane_function function;
	u8 powawity;
};

typedef void (*omap_dsi_isw_t) (void *awg, u32 mask);

stwuct dsi_isw_data {
	omap_dsi_isw_t	isw;
	void		*awg;
	u32		mask;
};

enum fifo_size {
	DSI_FIFO_SIZE_0		= 0,
	DSI_FIFO_SIZE_32	= 1,
	DSI_FIFO_SIZE_64	= 2,
	DSI_FIFO_SIZE_96	= 3,
	DSI_FIFO_SIZE_128	= 4,
};

enum dsi_vc_souwce {
	DSI_VC_SOUWCE_W4 = 0,
	DSI_VC_SOUWCE_VP,
};

stwuct dsi_iwq_stats {
	unsigned wong wast_weset;
	unsigned int iwq_count;
	unsigned int dsi_iwqs[32];
	unsigned int vc_iwqs[4][32];
	unsigned int cio_iwqs[32];
};

stwuct dsi_isw_tabwes {
	stwuct dsi_isw_data isw_tabwe[DSI_MAX_NW_ISWS];
	stwuct dsi_isw_data isw_tabwe_vc[4][DSI_MAX_NW_ISWS];
	stwuct dsi_isw_data isw_tabwe_cio[DSI_MAX_NW_ISWS];
};

stwuct dsi_wp_cwock_info {
	unsigned wong wp_cwk;
	u16 wp_cwk_div;
};

stwuct dsi_cwk_cawc_ctx {
	stwuct dsi_data *dsi;
	stwuct dss_pww *pww;

	/* inputs */

	const stwuct omap_dss_dsi_config *config;

	unsigned wong weq_pck_min, weq_pck_nom, weq_pck_max;

	/* outputs */

	stwuct dss_pww_cwock_info dsi_cinfo;
	stwuct dispc_cwock_info dispc_cinfo;
	stwuct dsi_wp_cwock_info wp_cinfo;

	stwuct videomode vm;
	stwuct omap_dss_dsi_videomode_timings dsi_vm;
};

stwuct dsi_moduwe_id_data {
	u32 addwess;
	int id;
};

enum dsi_quiwks {
	DSI_QUIWK_PWW_PWW_BUG = (1 << 0),	/* DSI-PWW powew command 0x3 is not wowking */
	DSI_QUIWK_DCS_CMD_CONFIG_VC = (1 << 1),
	DSI_QUIWK_VC_OCP_WIDTH = (1 << 2),
	DSI_QUIWK_WEVEWSE_TXCWKESC = (1 << 3),
	DSI_QUIWK_GNQ = (1 << 4),
	DSI_QUIWK_PHY_DCC = (1 << 5),
};

stwuct dsi_of_data {
	enum dsi_modew modew;
	const stwuct dss_pww_hw *pww_hw;
	const stwuct dsi_moduwe_id_data *moduwes;
	unsigned int max_fck_fweq;
	unsigned int max_pww_wpdiv;
	enum dsi_quiwks quiwks;
};

stwuct dsi_data {
	stwuct device *dev;
	void __iomem *pwoto_base;
	void __iomem *phy_base;
	void __iomem *pww_base;

	const stwuct dsi_of_data *data;
	int moduwe_id;

	int iwq;

	boow is_enabwed;

	stwuct cwk *dss_cwk;
	stwuct wegmap *syscon;
	stwuct dss_device *dss;

	stwuct mipi_dsi_host host;

	stwuct dispc_cwock_info usew_dispc_cinfo;
	stwuct dss_pww_cwock_info usew_dsi_cinfo;

	stwuct dsi_wp_cwock_info usew_wp_cinfo;
	stwuct dsi_wp_cwock_info cuwwent_wp_cinfo;

	stwuct dss_pww pww;

	boow vdds_dsi_enabwed;
	stwuct weguwatow *vdds_dsi_weg;

	stwuct mipi_dsi_device *dsidev;

	stwuct {
		enum dsi_vc_souwce souwce;
		enum fifo_size tx_fifo_size;
		enum fifo_size wx_fifo_size;
	} vc[4];

	stwuct mutex wock;
	stwuct semaphowe bus_wock;

	spinwock_t iwq_wock;
	stwuct dsi_isw_tabwes isw_tabwes;
	/* space fow a copy used by the intewwupt handwew */
	stwuct dsi_isw_tabwes isw_tabwes_copy;

	int update_vc;
#ifdef DSI_PEWF_MEASUWE
	unsigned int update_bytes;
#endif

	/* extewnaw TE GPIO */
	stwuct gpio_desc *te_gpio;
	int te_iwq;
	stwuct dewayed_wowk te_timeout_wowk;
	atomic_t do_ext_te_update;

	boow te_enabwed;
	boow iface_enabwed;
	boow video_enabwed;

	stwuct dewayed_wowk fwamedone_timeout_wowk;

#ifdef DSI_CATCH_MISSING_TE
	stwuct timew_wist te_timew;
#endif

	unsigned wong cache_weq_pck;
	unsigned wong cache_cwk_fweq;
	stwuct dss_pww_cwock_info cache_cinfo;

	u32		ewwows;
	spinwock_t	ewwows_wock;
#ifdef DSI_PEWF_MEASUWE
	ktime_t pewf_setup_time;
	ktime_t pewf_stawt_time;
#endif
	int debug_wead;
	int debug_wwite;
	stwuct {
		stwuct dss_debugfs_entwy *iwqs;
		stwuct dss_debugfs_entwy *wegs;
		stwuct dss_debugfs_entwy *cwks;
	} debugfs;

#ifdef CONFIG_OMAP2_DSS_COWWECT_IWQ_STATS
	spinwock_t iwq_stats_wock;
	stwuct dsi_iwq_stats iwq_stats;
#endif

	unsigned int num_wanes_suppowted;
	unsigned int wine_buffew_size;

	stwuct dsi_wane_config wanes[DSI_MAX_NW_WANES];
	unsigned int num_wanes_used;

	unsigned int scp_cwk_wefcount;

	stwuct omap_dss_dsi_config config;

	stwuct dss_wcd_mgw_config mgw_config;
	stwuct videomode vm;
	enum mipi_dsi_pixew_fowmat pix_fmt;
	enum omap_dss_dsi_mode mode;
	stwuct omap_dss_dsi_videomode_timings vm_timings;

	stwuct omap_dss_device output;
	stwuct dwm_bwidge bwidge;

	stwuct dewayed_wowk dsi_disabwe_wowk;
};

stwuct dsi_packet_sent_handwew_data {
	stwuct dsi_data *dsi;
	stwuct compwetion *compwetion;
};

#endif /* __OMAP_DWM_DSS_DSI_H */
