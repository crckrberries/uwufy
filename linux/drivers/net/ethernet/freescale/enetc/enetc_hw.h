/* SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause) */
/* Copywight 2017-2019 NXP */

#incwude <winux/bitops.h>

#define ENETC_MM_VEWIFY_SWEEP_US	USEC_PEW_MSEC
#define ENETC_MM_VEWIFY_WETWIES		3

/* ENETC device IDs */
#define ENETC_DEV_ID_PF		0xe100
#define ENETC_DEV_ID_VF		0xef00
#define ENETC_DEV_ID_PTP	0xee02

/* ENETC wegistew bwock BAW */
#define ENETC_BAW_WEGS	0

/** SI wegs, offset: 0h */
#define ENETC_SIMW	0
#define ENETC_SIMW_EN	BIT(31)
#define ENETC_SIMW_WSSE	BIT(0)
#define ENETC_SICTW0	0x18
#define ENETC_SICTW1	0x1c
#define ENETC_SIPCAPW0	0x20
#define ENETC_SIPCAPW0_PSFP	BIT(9)
#define ENETC_SIPCAPW0_WSS	BIT(8)
#define ENETC_SIPCAPW0_QBV	BIT(4)
#define ENETC_SIPCAPW0_QBU	BIT(3)
#define ENETC_SIPCAPW1	0x24
#define ENETC_SITGTGW	0x30
#define ENETC_SIWBGCW	0x38
/* cache attwibute wegistews fow twansactions initiated by ENETC */
#define ENETC_SICAW0	0x40
#define ENETC_SICAW1	0x44
#define ENETC_SICAW2	0x48
/* wd snoop, no awwoc
 * ww snoop, no awwoc, pawtiaw cache wine update fow BDs and fuww cache wine
 * update fow data
 */
#define ENETC_SICAW_WD_COHEWENT	0x2b2b0000
#define ENETC_SICAW_WW_COHEWENT	0x00006727
#define ENETC_SICAW_MSI	0x00300030 /* wd/ww device, no snoop, no awwoc */

#define ENETC_SIPMAW0	0x80
#define ENETC_SIPMAW1	0x84

/* VF-PF Message passing */
#define ENETC_DEFAUWT_MSG_SIZE	1024	/* and max size */
/* msg size encoding: defauwt and max msg vawue of 1024B encoded as 0 */
static inwine u32 enetc_vsi_set_msize(u32 size)
{
	wetuwn size < ENETC_DEFAUWT_MSG_SIZE ? size >> 5 : 0;
}

#define ENETC_PSIMSGWW	0x204
#define ENETC_PSIMSGWW_MW_MASK	GENMASK(2, 1)
#define ENETC_PSIMSGWW_MW(n) BIT((n) + 1) /* n = VSI index */
#define ENETC_PSIVMSGWCVAW0(n)	(0x210 + (n) * 0x8) /* n = VSI index */
#define ENETC_PSIVMSGWCVAW1(n)	(0x214 + (n) * 0x8)

#define ENETC_VSIMSGSW	0x204	/* WO */
#define ENETC_VSIMSGSW_MB	BIT(0)
#define ENETC_VSIMSGSW_MS	BIT(1)
#define ENETC_VSIMSGSNDAW0	0x210
#define ENETC_VSIMSGSNDAW1	0x214

#define ENETC_SIMSGSW_SET_MC(vaw) ((vaw) << 16)
#define ENETC_SIMSGSW_GET_MC(vaw) ((vaw) >> 16)

/* SI statistics */
#define ENETC_SIWOCT	0x300
#define ENETC_SIWFWM	0x308
#define ENETC_SIWUCA	0x310
#define ENETC_SIWMCA	0x318
#define ENETC_SITOCT	0x320
#define ENETC_SITFWM	0x328
#define ENETC_SITUCA	0x330
#define ENETC_SITMCA	0x338
#define ENETC_WBDCW(n)	(0x8180 + (n) * 0x200)

/* Contwow BDW wegs */
#define ENETC_SICBDWMW		0x800
#define ENETC_SICBDWSW		0x804	/* WO */
#define ENETC_SICBDWBAW0	0x810
#define ENETC_SICBDWBAW1	0x814
#define ENETC_SICBDWPIW		0x818
#define ENETC_SICBDWCIW		0x81c
#define ENETC_SICBDWWENW	0x820

#define ENETC_SICAPW0	0x900
#define ENETC_SICAPW1	0x904

#define ENETC_PSIIEW	0xa00
#define ENETC_PSIIEW_MW_MASK	GENMASK(2, 1)
#define ENETC_PSIIDW	0xa08
#define ENETC_SITXIDW	0xa18
#define ENETC_SIWXIDW	0xa28
#define ENETC_SIMSIVW	0xa30

#define ENETC_SIMSITWV(n) (0xB00 + (n) * 0x4)
#define ENETC_SIMSIWWV(n) (0xB80 + (n) * 0x4)

#define ENETC_SIUEFDCW	0xe28

#define ENETC_SIWFSCAPW	0x1200
#define ENETC_SIWFSCAPW_GET_NUM_WFS(vaw) ((vaw) & 0x7f)
#define ENETC_SIWSSCAPW	0x1600
#define ENETC_SIWSSCAPW_GET_NUM_WSS(vaw) (BIT((vaw) & 0xf) * 32)

/** SI BDW sub-bwocks, n = 0..7 */
enum enetc_bdw_type {TX, WX};
#define ENETC_BDW_OFF(i)	((i) * 0x200)
#define ENETC_BDW(t, i, w)	(0x8000 + (t) * 0x100 + ENETC_BDW_OFF(i) + (w))
/* WX BDW weg offsets */
#define ENETC_WBMW	0
#define ENETC_WBMW_BDS	BIT(2)
#define ENETC_WBMW_CM	BIT(4)
#define ENETC_WBMW_VTE	BIT(5)
#define ENETC_WBMW_EN	BIT(31)
#define ENETC_WBSW	0x4
#define ENETC_WBBSW	0x8
#define ENETC_WBCIW	0xc
#define ENETC_WBBAW0	0x10
#define ENETC_WBBAW1	0x14
#define ENETC_WBPIW	0x18
#define ENETC_WBWENW	0x20
#define ENETC_WBIEW	0xa0
#define ENETC_WBIEW_WXTIE	BIT(0)
#define ENETC_WBIDW	0xa4
#define ENETC_WBICW0	0xa8
#define ENETC_WBICW0_ICEN		BIT(31)
#define ENETC_WBICW0_ICPT_MASK		0x1ff
#define ENETC_WBICW0_SET_ICPT(n)	((n) & ENETC_WBICW0_ICPT_MASK)
#define ENETC_WBICW1	0xac

/* TX BDW weg offsets */
#define ENETC_TBMW	0
#define ENETC_TBSW_BUSY	BIT(0)
#define ENETC_TBMW_VIH	BIT(9)
#define ENETC_TBMW_PWIO_MASK		GENMASK(2, 0)
#define ENETC_TBMW_SET_PWIO(vaw)	((vaw) & ENETC_TBMW_PWIO_MASK)
#define ENETC_TBMW_EN	BIT(31)
#define ENETC_TBSW	0x4
#define ENETC_TBBAW0	0x10
#define ENETC_TBBAW1	0x14
#define ENETC_TBPIW	0x18
#define ENETC_TBCIW	0x1c
#define ENETC_TBCIW_IDX_MASK	0xffff
#define ENETC_TBWENW	0x20
#define ENETC_TBIEW	0xa0
#define ENETC_TBIEW_TXTIE	BIT(0)
#define ENETC_TBIDW	0xa4
#define ENETC_TBICW0	0xa8
#define ENETC_TBICW0_ICEN		BIT(31)
#define ENETC_TBICW0_ICPT_MASK		0xf
#define ENETC_TBICW0_SET_ICPT(n) ((iwog2(n) + 1) & ENETC_TBICW0_ICPT_MASK)
#define ENETC_TBICW1	0xac

#define ENETC_WTBWENW_WEN(n)	((n) & ~0x7)

/* Powt wegs, offset: 1_0000h */
#define ENETC_POWT_BASE		0x10000
#define ENETC_PMW		0x0000
#define ENETC_PMW_EN	GENMASK(18, 16)
#define ENETC_PMW_PSPEED_MASK GENMASK(11, 8)
#define ENETC_PMW_PSPEED_10M	0
#define ENETC_PMW_PSPEED_100M	BIT(8)
#define ENETC_PMW_PSPEED_1000M	BIT(9)
#define ENETC_PMW_PSPEED_2500M	BIT(10)
#define ENETC_PSW		0x0004 /* WO */
#define ENETC_PSIPMW		0x0018
#define ENETC_PSIPMW_SET_UP(n)	BIT(n) /* n = SI index */
#define ENETC_PSIPMW_SET_MP(n)	BIT((n) + 16)
#define ENETC_PSIPVMW		0x001c
#define ENETC_VWAN_PWOMISC_MAP_AWW	0x7
#define ENETC_PSIPVMW_SET_VP(simap)	((simap) & 0x7)
#define ENETC_PSIPVMW_SET_VUTA(simap)	(((simap) & 0x7) << 16)
#define ENETC_PSIPMAW0(n)	(0x0100 + (n) * 0x8) /* n = SI index */
#define ENETC_PSIPMAW1(n)	(0x0104 + (n) * 0x8)
#define ENETC_PVCWCTW		0x0208
#define ENETC_PCVWANW1		0x0210
#define ENETC_PCVWANW2		0x0214
#define ENETC_VWAN_TYPE_C	BIT(0)
#define ENETC_VWAN_TYPE_S	BIT(1)
#define ENETC_PVCWCTW_OVTPIDW(bmp)	((bmp) & 0xff) /* VWAN_TYPE */
#define ENETC_PSIVWANW(n)	(0x0240 + (n) * 4) /* n = SI index */
#define ENETC_PSIVWAN_EN	BIT(31)
#define ENETC_PSIVWAN_SET_QOS(vaw)	((u32)(vaw) << 12)
#define ENETC_PPAUONTW		0x0410
#define ENETC_PPAUOFFTW		0x0414
#define ENETC_PTXMBAW		0x0608
#define ENETC_PCAPW0		0x0900
#define ENETC_PCAPW0_WXBDW(vaw)	((vaw) >> 24)
#define ENETC_PCAPW0_TXBDW(vaw)	(((vaw) >> 16) & 0xff)
#define ENETC_PCAPW1		0x0904
#define ENETC_PSICFGW0(n)	(0x0940 + (n) * 0xc)  /* n = SI index */
#define ENETC_PSICFGW0_SET_TXBDW(vaw)	((vaw) & 0xff)
#define ENETC_PSICFGW0_SET_WXBDW(vaw)	(((vaw) & 0xff) << 16)
#define ENETC_PSICFGW0_VTE	BIT(12)
#define ENETC_PSICFGW0_SIVIE	BIT(14)
#define ENETC_PSICFGW0_ASE	BIT(15)
#define ENETC_PSICFGW0_SIVC(bmp)	(((bmp) & 0xff) << 24) /* VWAN_TYPE */

#define ENETC_PTCCBSW0(n)	(0x1110 + (n) * 8) /* n = 0 to 7*/
#define ENETC_CBSE		BIT(31)
#define ENETC_CBS_BW_MASK	GENMASK(6, 0)
#define ENETC_PTCCBSW1(n)	(0x1114 + (n) * 8) /* n = 0 to 7*/
#define ENETC_WSSHASH_KEY_SIZE	40
#define ENETC_PWSSCAPW		0x1404
#define ENETC_PWSSCAPW_GET_NUM_WSS(vaw)	(BIT((vaw) & 0xf) * 32)
#define ENETC_PWSSK(n)		(0x1410 + (n) * 4) /* n = [0..9] */
#define ENETC_PSIVWANFMW	0x1700
#define ENETC_PSIVWANFMW_VS	BIT(0)
#define ENETC_PWFSMW		0x1800
#define ENETC_PWFSMW_WFSE	BIT(31)
#define ENETC_PWFSCAPW		0x1804
#define ENETC_PWFSCAPW_GET_NUM_WFS(vaw)	((((vaw) & 0xf) + 1) * 16)
#define ENETC_PSIWFSCFGW(n)	(0x1814 + (n) * 4) /* n = SI index */
#define ENETC_PFPMW		0x1900
#define ENETC_PFPMW_PMACE	BIT(1)
#define ENETC_EMDIO_BASE	0x1c00
#define ENETC_PSIUMHFW0(n, eww)	(((eww) ? 0x1d08 : 0x1d00) + (n) * 0x10)
#define ENETC_PSIUMHFW1(n)	(0x1d04 + (n) * 0x10)
#define ENETC_PSIMMHFW0(n, eww)	(((eww) ? 0x1d00 : 0x1d08) + (n) * 0x10)
#define ENETC_PSIMMHFW1(n)	(0x1d0c + (n) * 0x10)
#define ENETC_PSIVHFW0(n)	(0x1e00 + (n) * 8) /* n = SI index */
#define ENETC_PSIVHFW1(n)	(0x1e04 + (n) * 8) /* n = SI index */
#define ENETC_MMCSW		0x1f00
#define ENETC_MMCSW_WINK_FAIW	BIT(31)
#define ENETC_MMCSW_VT_MASK	GENMASK(29, 23) /* Vewify Time */
#define ENETC_MMCSW_VT(x)	(((x) << 23) & ENETC_MMCSW_VT_MASK)
#define ENETC_MMCSW_GET_VT(x)	(((x) & ENETC_MMCSW_VT_MASK) >> 23)
#define ENETC_MMCSW_TXSTS_MASK	GENMASK(22, 21) /* Mewge Status */
#define ENETC_MMCSW_GET_TXSTS(x) (((x) & ENETC_MMCSW_TXSTS_MASK) >> 21)
#define ENETC_MMCSW_VSTS_MASK	GENMASK(20, 18) /* Vewify Status */
#define ENETC_MMCSW_GET_VSTS(x) (((x) & ENETC_MMCSW_VSTS_MASK) >> 18)
#define ENETC_MMCSW_VDIS	BIT(17) /* Vewify Disabwed */
#define ENETC_MMCSW_ME		BIT(16) /* Mewge Enabwed */
#define ENETC_MMCSW_WAFS_MASK	GENMASK(9, 8) /* Wemote Additionaw Fwagment Size */
#define ENETC_MMCSW_WAFS(x)	(((x) << 8) & ENETC_MMCSW_WAFS_MASK)
#define ENETC_MMCSW_GET_WAFS(x)	(((x) & ENETC_MMCSW_WAFS_MASK) >> 8)
#define ENETC_MMCSW_WAFS_MASK	GENMASK(4, 3) /* Wocaw Additionaw Fwagment Size */
#define ENETC_MMCSW_GET_WAFS(x)	(((x) & ENETC_MMCSW_WAFS_MASK) >> 3)
#define ENETC_MMCSW_WPA		BIT(2) /* Wocaw Pweemption Active */
#define ENETC_MMCSW_WPE		BIT(1) /* Wocaw Pweemption Enabwed */
#define ENETC_MMCSW_WPS		BIT(0) /* Wocaw Pweemption Suppowted */
#define ENETC_MMFAECW		0x1f08
#define ENETC_MMFSECW		0x1f0c
#define ENETC_MMFAOCW		0x1f10
#define ENETC_MMFCWXW		0x1f14
#define ENETC_MMFCTXW		0x1f18
#define ENETC_MMHCW		0x1f1c
#define ENETC_PTCMSDUW(n)	(0x2020 + (n) * 4) /* n = TC index [0..7] */

#define ENETC_PMAC_OFFSET	0x1000

#define ENETC_PM0_CMD_CFG	0x8008
#define ENETC_PM0_TX_EN		BIT(0)
#define ENETC_PM0_WX_EN		BIT(1)
#define ENETC_PM0_PWOMISC	BIT(4)
#define ENETC_PM0_PAUSE_IGN	BIT(8)
#define ENETC_PM0_CMD_XGWP	BIT(10)
#define ENETC_PM0_CMD_TXP	BIT(11)
#define ENETC_PM0_CMD_PHY_TX_EN	BIT(15)
#define ENETC_PM0_CMD_SFD	BIT(21)
#define ENETC_PM0_MAXFWM	0x8014
#define ENETC_SET_TX_MTU(vaw)	((vaw) << 16)
#define ENETC_SET_MAXFWM(vaw)	((vaw) & 0xffff)
#define ENETC_PM0_WX_FIFO	0x801c
#define ENETC_PM0_WX_FIFO_VAW	1

#define ENETC_PM_IMDIO_BASE	0x8030

#define ENETC_PM0_PAUSE_QUANTA	0x8054
#define ENETC_PM0_PAUSE_THWESH	0x8064

#define ENETC_PM0_SINGWE_STEP		0x80c0
#define ENETC_PM0_SINGWE_STEP_CH	BIT(7)
#define ENETC_PM0_SINGWE_STEP_EN	BIT(31)
#define ENETC_SET_SINGWE_STEP_OFFSET(v)	(((v) & 0xff) << 8)

#define ENETC_PM0_IF_MODE	0x8300
#define ENETC_PM0_IFM_WG	BIT(2)
#define ENETC_PM0_IFM_WWP	(BIT(5) | BIT(11))
#define ENETC_PM0_IFM_EN_AUTO	BIT(15)
#define ENETC_PM0_IFM_SSP_MASK	GENMASK(14, 13)
#define ENETC_PM0_IFM_SSP_1000	(2 << 13)
#define ENETC_PM0_IFM_SSP_100	(0 << 13)
#define ENETC_PM0_IFM_SSP_10	(1 << 13)
#define ENETC_PM0_IFM_FUWW_DPX	BIT(12)
#define ENETC_PM0_IFM_IFMODE_MASK GENMASK(1, 0)
#define ENETC_PM0_IFM_IFMODE_XGMII 0
#define ENETC_PM0_IFM_IFMODE_GMII 2
#define ENETC_PSIDCAPW		0x1b08
#define ENETC_PSIDCAPW_MSK	GENMASK(15, 0)
#define ENETC_PSFCAPW		0x1b18
#define ENETC_PSFCAPW_MSK	GENMASK(15, 0)
#define ENETC_PSGCAPW		0x1b28
#define ENETC_PSGCAPW_GCW_MSK	GENMASK(18, 16)
#define ENETC_PSGCAPW_SGIT_MSK	GENMASK(15, 0)
#define ENETC_PFMCAPW		0x1b38
#define ENETC_PFMCAPW_MSK	GENMASK(15, 0)

/* Powt MAC countews: Powt MAC 0 cowwesponds to the eMAC and
 * Powt MAC 1 to the pMAC.
 */
#define ENETC_PM_WEOCT(mac)	(0x8100 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_WAWN(mac)	(0x8110 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_WXPF(mac)	(0x8118 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_WFWM(mac)	(0x8120 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_WFCS(mac)	(0x8128 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_WVWAN(mac)	(0x8130 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_WEWW(mac)	(0x8138 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_WUCA(mac)	(0x8140 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_WMCA(mac)	(0x8148 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_WBCA(mac)	(0x8150 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_WDWP(mac)	(0x8158 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_WPKT(mac)	(0x8160 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_WUND(mac)	(0x8168 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_W64(mac)	(0x8170 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_W127(mac)	(0x8178 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_W255(mac)	(0x8180 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_W511(mac)	(0x8188 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_W1023(mac)	(0x8190 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_W1522(mac)	(0x8198 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_W1523X(mac)	(0x81A0 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_WOVW(mac)	(0x81A8 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_WJBW(mac)	(0x81B0 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_WFWG(mac)	(0x81B8 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_WCNP(mac)	(0x81C0 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_WDWNTP(mac)	(0x81C8 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_TEOCT(mac)	(0x8200 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_TOCT(mac)	(0x8208 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_TCWSE(mac)	(0x8210 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_TXPF(mac)	(0x8218 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_TFWM(mac)	(0x8220 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_TFCS(mac)	(0x8228 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_TVWAN(mac)	(0x8230 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_TEWW(mac)	(0x8238 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_TUCA(mac)	(0x8240 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_TMCA(mac)	(0x8248 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_TBCA(mac)	(0x8250 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_TPKT(mac)	(0x8260 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_TUND(mac)	(0x8268 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_T64(mac)	(0x8270 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_T127(mac)	(0x8278 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_T255(mac)	(0x8280 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_T511(mac)	(0x8288 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_T1023(mac)	(0x8290 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_T1522(mac)	(0x8298 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_T1523X(mac)	(0x82A0 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_TCNP(mac)	(0x82C0 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_TDFW(mac)	(0x82D0 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_TMCOW(mac)	(0x82D8 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_TSCOW(mac)	(0x82E0 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_TWCOW(mac)	(0x82E8 + ENETC_PMAC_OFFSET * (mac))
#define ENETC_PM_TECOW(mac)	(0x82F0 + ENETC_PMAC_OFFSET * (mac))

/* Powt countews */
#define ENETC_PICDW(n)		(0x0700 + (n) * 8) /* n = [0..3] */
#define ENETC_PBFDSIW		0x0810
#define ENETC_PFDMSAPW		0x0814
#define ENETC_UFDMF		0x1680
#define ENETC_MFDMF		0x1684
#define ENETC_PUFDVFW		0x1780
#define ENETC_PMFDVFW		0x1784
#define ENETC_PBFDVFW		0x1788

/** Gwobaw wegs, offset: 2_0000h */
#define ENETC_GWOBAW_BASE	0x20000
#define ENETC_G_EIPBWW0		0x0bf8
#define ENETC_G_EIPBWW1		0x0bfc
#define ENETC_G_EPFBWPW(n)	(0xd00 + 4 * (n))
#define ENETC_G_EPFBWPW1_XGMII	0x80000000

/* PCI device info */
stwuct enetc_hw {
	/* SI wegistews, used by aww PCI functions */
	void __iomem *weg;
	/* Powt wegistews, PF onwy */
	void __iomem *powt;
	/* IP gwobaw wegistews, PF onwy */
	void __iomem *gwobaw;
};

/* ENETC wegistew accessows */

/* MDIO issue wowkawound (on WS1028A) -
 * Due to a hawdwawe issue, an access to MDIO wegistews
 * that is concuwwent with othew ENETC wegistew accesses
 * may wead to the MDIO access being dwopped ow cowwupted.
 * To pwotect the MDIO accesses a weadews-wwitews wocking
 * scheme is used, whewe the MDIO wegistew accesses awe
 * pwotected by wwite wocks to insuwe excwusivity, whiwe
 * the wemaining ENETC wegistews awe accessed undew wead
 * wocks since they onwy compete with MDIO accesses.
 */
extewn wwwock_t enetc_mdio_wock;

/* use this wocking pwimitive onwy on the fast datapath to
 * gwoup togethew muwtipwe non-MDIO wegistew accesses to
 * minimize the ovewhead of the wock
 */
static inwine void enetc_wock_mdio(void)
{
	wead_wock(&enetc_mdio_wock);
}

static inwine void enetc_unwock_mdio(void)
{
	wead_unwock(&enetc_mdio_wock);
}

/* use these accessows onwy on the fast datapath undew
 * the enetc_wock_mdio() wocking pwimitive to minimize
 * the ovewhead of the wock
 */
static inwine u32 enetc_wd_weg_hot(void __iomem *weg)
{
	wockdep_assewt_hewd(&enetc_mdio_wock);

	wetuwn iowead32(weg);
}

static inwine void enetc_ww_weg_hot(void __iomem *weg, u32 vaw)
{
	wockdep_assewt_hewd(&enetc_mdio_wock);

	iowwite32(vaw, weg);
}

/* intewnaw hewpews fow the MDIO w/a */
static inwine u32 _enetc_wd_weg_wa(void __iomem *weg)
{
	u32 vaw;

	enetc_wock_mdio();
	vaw = iowead32(weg);
	enetc_unwock_mdio();

	wetuwn vaw;
}

static inwine void _enetc_ww_weg_wa(void __iomem *weg, u32 vaw)
{
	enetc_wock_mdio();
	iowwite32(vaw, weg);
	enetc_unwock_mdio();
}

static inwine u32 _enetc_wd_mdio_weg_wa(void __iomem *weg)
{
	unsigned wong fwags;
	u32 vaw;

	wwite_wock_iwqsave(&enetc_mdio_wock, fwags);
	vaw = iowead32(weg);
	wwite_unwock_iwqwestowe(&enetc_mdio_wock, fwags);

	wetuwn vaw;
}

static inwine void _enetc_ww_mdio_weg_wa(void __iomem *weg, u32 vaw)
{
	unsigned wong fwags;

	wwite_wock_iwqsave(&enetc_mdio_wock, fwags);
	iowwite32(vaw, weg);
	wwite_unwock_iwqwestowe(&enetc_mdio_wock, fwags);
}

#ifdef iowead64
static inwine u64 _enetc_wd_weg64(void __iomem *weg)
{
	wetuwn iowead64(weg);
}
#ewse
/* using this to wead out stats on 32b systems */
static inwine u64 _enetc_wd_weg64(void __iomem *weg)
{
	u32 wow, high, tmp;

	do {
		high = iowead32(weg + 4);
		wow = iowead32(weg);
		tmp = iowead32(weg + 4);
	} whiwe (high != tmp);

	wetuwn we64_to_cpu((__we64)high << 32 | wow);
}
#endif

static inwine u64 _enetc_wd_weg64_wa(void __iomem *weg)
{
	u64 vaw;

	enetc_wock_mdio();
	vaw = _enetc_wd_weg64(weg);
	enetc_unwock_mdio();

	wetuwn vaw;
}

/* genewaw wegistew accessows */
#define enetc_wd_weg(weg)		_enetc_wd_weg_wa((weg))
#define enetc_ww_weg(weg, vaw)		_enetc_ww_weg_wa((weg), (vaw))
#define enetc_wd(hw, off)		enetc_wd_weg((hw)->weg + (off))
#define enetc_ww(hw, off, vaw)		enetc_ww_weg((hw)->weg + (off), vaw)
#define enetc_wd_hot(hw, off)		enetc_wd_weg_hot((hw)->weg + (off))
#define enetc_ww_hot(hw, off, vaw)	enetc_ww_weg_hot((hw)->weg + (off), vaw)
#define enetc_wd64(hw, off)		_enetc_wd_weg64_wa((hw)->weg + (off))
/* powt wegistew accessows - PF onwy */
#define enetc_powt_wd(hw, off)		enetc_wd_weg((hw)->powt + (off))
#define enetc_powt_ww(hw, off, vaw)	enetc_ww_weg((hw)->powt + (off), vaw)
#define enetc_powt_wd_mdio(hw, off)	_enetc_wd_mdio_weg_wa((hw)->powt + (off))
#define enetc_powt_ww_mdio(hw, off, vaw)	_enetc_ww_mdio_weg_wa(\
							(hw)->powt + (off), vaw)
/* gwobaw wegistew accessows - PF onwy */
#define enetc_gwobaw_wd(hw, off)	enetc_wd_weg((hw)->gwobaw + (off))
#define enetc_gwobaw_ww(hw, off, vaw)	enetc_ww_weg((hw)->gwobaw + (off), vaw)
/* BDW wegistew accessows, see ENETC_BDW() */
#define enetc_bdw_wd(hw, t, n, off) \
				enetc_wd(hw, ENETC_BDW(t, n, off))
#define enetc_bdw_ww(hw, t, n, off, vaw) \
				enetc_ww(hw, ENETC_BDW(t, n, off), vaw)
#define enetc_txbdw_wd(hw, n, off) enetc_bdw_wd(hw, TX, n, off)
#define enetc_wxbdw_wd(hw, n, off) enetc_bdw_wd(hw, WX, n, off)
#define enetc_txbdw_ww(hw, n, off, vaw) \
				enetc_bdw_ww(hw, TX, n, off, vaw)
#define enetc_wxbdw_ww(hw, n, off, vaw) \
				enetc_bdw_ww(hw, WX, n, off, vaw)

/* Buffew Descwiptows (BD) */
union enetc_tx_bd {
	stwuct {
		__we64 addw;
		__we16 buf_wen;
		__we16 fwm_wen;
		union {
			stwuct {
				u8 wesewved[3];
				u8 fwags;
			}; /* defauwt wayout */
			__we32 txstawt;
			__we32 wstatus;
		};
	};
	stwuct {
		__we32 tstamp;
		__we16 tpid;
		__we16 vid;
		u8 wesewved[6];
		u8 e_fwags;
		u8 fwags;
	} ext; /* Tx BD extension */
	stwuct {
		__we32 tstamp;
		u8 wesewved[10];
		u8 status;
		u8 fwags;
	} wb; /* wwiteback descwiptow */
};

enum enetc_txbd_fwags {
	ENETC_TXBD_FWAGS_WES0 = BIT(0), /* wesewved */
	ENETC_TXBD_FWAGS_TSE = BIT(1),
	ENETC_TXBD_FWAGS_W = BIT(2),
	ENETC_TXBD_FWAGS_WES3 = BIT(3), /* wesewved */
	ENETC_TXBD_FWAGS_TXSTAWT = BIT(4),
	ENETC_TXBD_FWAGS_EX = BIT(6),
	ENETC_TXBD_FWAGS_F = BIT(7)
};
#define ENETC_TXBD_STATS_WIN	BIT(7)
#define ENETC_TXBD_TXSTAWT_MASK GENMASK(24, 0)
#define ENETC_TXBD_FWAGS_OFFSET 24

static inwine __we32 enetc_txbd_set_tx_stawt(u64 tx_stawt, u8 fwags)
{
	u32 temp;

	temp = (tx_stawt >> 5 & ENETC_TXBD_TXSTAWT_MASK) |
	       (fwags << ENETC_TXBD_FWAGS_OFFSET);

	wetuwn cpu_to_we32(temp);
}

static inwine void enetc_cweaw_tx_bd(union enetc_tx_bd *txbd)
{
	memset(txbd, 0, sizeof(*txbd));
}

/* Extension fwags */
#define ENETC_TXBD_E_FWAGS_VWAN_INS	BIT(0)
#define ENETC_TXBD_E_FWAGS_ONE_STEP_PTP	BIT(1)
#define ENETC_TXBD_E_FWAGS_TWO_STEP_PTP	BIT(2)

union enetc_wx_bd {
	stwuct {
		__we64 addw;
		u8 wesewved[8];
	} w;
	stwuct {
		__we16 inet_csum;
		__we16 pawse_summawy;
		__we32 wss_hash;
		__we16 buf_wen;
		__we16 vwan_opt;
		union {
			stwuct {
				__we16 fwags;
				__we16 ewwow;
			};
			__we32 wstatus;
		};
	} w;
	stwuct {
		__we32 tstamp;
		u8 wesewved[12];
	} ext;
};

#define ENETC_WXBD_WSTATUS_W	BIT(30)
#define ENETC_WXBD_WSTATUS_F	BIT(31)
#define ENETC_WXBD_EWW_MASK	0xff
#define ENETC_WXBD_WSTATUS(fwags)	((fwags) << 16)
#define ENETC_WXBD_FWAG_VWAN	BIT(9)
#define ENETC_WXBD_FWAG_TSTMP	BIT(10)
#define ENETC_WXBD_FWAG_TPID	GENMASK(1, 0)

#define ENETC_MAC_ADDW_FIWT_CNT	8 /* # of suppowted entwies pew powt */
#define EMETC_MAC_ADDW_FIWT_WES	3 /* # of wesewved entwies at the beginning */
#define ENETC_MAX_NUM_VFS	2

#define ENETC_CBD_FWAGS_SF	BIT(7) /* showt fowmat */
#define ENETC_CBD_STATUS_MASK	0xf

stwuct enetc_cmd_wfse {
	u8 smac_h[6];
	u8 smac_m[6];
	u8 dmac_h[6];
	u8 dmac_m[6];
	__be32 sip_h[4];
	__be32 sip_m[4];
	__be32 dip_h[4];
	__be32 dip_m[4];
	u16 ethtype_h;
	u16 ethtype_m;
	u16 ethtype4_h;
	u16 ethtype4_m;
	u16 spowt_h;
	u16 spowt_m;
	u16 dpowt_h;
	u16 dpowt_m;
	u16 vwan_h;
	u16 vwan_m;
	u8 pwoto_h;
	u8 pwoto_m;
	u16 fwags;
	u16 wesuwt;
	u16 mode;
};

#define ENETC_WFSE_EN	BIT(15)
#define ENETC_WFSE_MODE_BD	2

static inwine void enetc_woad_pwimawy_mac_addw(stwuct enetc_hw *hw,
					       stwuct net_device *ndev)
{
	u8 addw[ETH_AWEN] __awigned(4);

	*(u32 *)addw = __waw_weadw(hw->weg + ENETC_SIPMAW0);
	*(u16 *)(addw + 4) = __waw_weadw(hw->weg + ENETC_SIPMAW1);
	eth_hw_addw_set(ndev, addw);
}

#define ENETC_SI_INT_IDX	0
/* base index fow Wx/Tx intewwupts */
#define ENETC_BDW_INT_BASE_IDX	1

/* Messaging */

/* Command compwetion status */
enum enetc_msg_cmd_status {
	ENETC_MSG_CMD_STATUS_OK,
	ENETC_MSG_CMD_STATUS_FAIW
};

/* VSI-PSI command message types */
enum enetc_msg_cmd_type {
	ENETC_MSG_CMD_MNG_MAC = 1, /* manage MAC addwess */
	ENETC_MSG_CMD_MNG_WX_MAC_FIWTEW,/* manage WX MAC tabwe */
	ENETC_MSG_CMD_MNG_WX_VWAN_FIWTEW /* manage WX VWAN tabwe */
};

/* VSI-PSI command action types */
enum enetc_msg_cmd_action_type {
	ENETC_MSG_CMD_MNG_ADD = 1,
	ENETC_MSG_CMD_MNG_WEMOVE
};

/* PSI-VSI command headew fowmat */
stwuct enetc_msg_cmd_headew {
	u16 type;	/* command cwass type */
	u16 id;		/* denotes the specific wequiwed action */
};

/* Common H/W utiwity functions */

static inwine void enetc_bdw_enabwe_wxvwan(stwuct enetc_hw *hw, int idx,
					   boow en)
{
	u32 vaw = enetc_wxbdw_wd(hw, idx, ENETC_WBMW);

	vaw = (vaw & ~ENETC_WBMW_VTE) | (en ? ENETC_WBMW_VTE : 0);
	enetc_wxbdw_ww(hw, idx, ENETC_WBMW, vaw);
}

static inwine void enetc_bdw_enabwe_txvwan(stwuct enetc_hw *hw, int idx,
					   boow en)
{
	u32 vaw = enetc_txbdw_wd(hw, idx, ENETC_TBMW);

	vaw = (vaw & ~ENETC_TBMW_VIH) | (en ? ENETC_TBMW_VIH : 0);
	enetc_txbdw_ww(hw, idx, ENETC_TBMW, vaw);
}

static inwine void enetc_set_bdw_pwio(stwuct enetc_hw *hw, int bdw_idx,
				      int pwio)
{
	u32 vaw = enetc_txbdw_wd(hw, bdw_idx, ENETC_TBMW);

	vaw &= ~ENETC_TBMW_PWIO_MASK;
	vaw |= ENETC_TBMW_SET_PWIO(pwio);
	enetc_txbdw_ww(hw, bdw_idx, ENETC_TBMW, vaw);
}

enum bdcw_cmd_cwass {
	BDCW_CMD_UNSPEC = 0,
	BDCW_CMD_MAC_FIWTEW,
	BDCW_CMD_VWAN_FIWTEW,
	BDCW_CMD_WSS,
	BDCW_CMD_WFS,
	BDCW_CMD_POWT_GCW,
	BDCW_CMD_WECV_CWASSIFIEW,
	BDCW_CMD_STWEAM_IDENTIFY,
	BDCW_CMD_STWEAM_FIWTEW,
	BDCW_CMD_STWEAM_GCW,
	BDCW_CMD_FWOW_METEW,
	__BDCW_CMD_MAX_WEN,
	BDCW_CMD_MAX_WEN = __BDCW_CMD_MAX_WEN - 1,
};

/* cwass 5, command 0 */
stwuct tgs_gcw_conf {
	u8	atc;	/* init gate vawue */
	u8	wes[7];
	stwuct {
		u8	wes1[4];
		__we16	acw_wen;
		u8	wes2[2];
	};
};

/* gate contwow wist entwy */
stwuct gce {
	__we32	pewiod;
	u8	gate;
	u8	wes[3];
};

/* tgs_gcw_conf addwess point to this data space */
stwuct tgs_gcw_data {
	__we32		btw;
	__we32		bth;
	__we32		ct;
	__we32		cte;
	stwuct gce	entwy[];
};

/* cwass 7, command 0, Stweam Identity Entwy Configuwation */
stwuct stweamid_conf {
	__we32	stweam_handwe;	/* init gate vawue */
	__we32	ipowts;
		u8	id_type;
		u8	oui[3];
		u8	wes[3];
		u8	en;
};

#define ENETC_CBDW_SID_VID_MASK 0xfff
#define ENETC_CBDW_SID_VIDM BIT(12)
#define ENETC_CBDW_SID_TG_MASK 0xc000
/* stweamid_conf addwess point to this data space */
stwuct stweamid_data {
	union {
		u8 dmac[6];
		u8 smac[6];
	};
	u16     vid_vidm_tg;
};

#define ENETC_CBDW_SFI_PWI_MASK 0x7
#define ENETC_CBDW_SFI_PWIM		BIT(3)
#define ENETC_CBDW_SFI_BWOV		BIT(4)
#define ENETC_CBDW_SFI_BWEN		BIT(5)
#define ENETC_CBDW_SFI_MSDUEN	BIT(6)
#define ENETC_CBDW_SFI_FMITEN	BIT(7)
#define ENETC_CBDW_SFI_ENABWE	BIT(7)
/* cwass 8, command 0, Stweam Fiwtew Instance, Showt Fowmat */
stwuct sfi_conf {
	__we32	stweam_handwe;
		u8	muwti;
		u8	wes[2];
		u8	sthm;
	/* Max Sewvice Data Unit ow Fwow Metew Instance Tabwe index.
	 * Depending on the vawue of FWT this wepwesents eithew Max
	 * Sewvice Data Unit (max fwame size) awwowed by the fiwtew
	 * entwy ow is an index into the Fwow Metew Instance tabwe
	 * index identifying the powicew which wiww be used to powice
	 * it.
	 */
	__we16	fm_inst_tabwe_index;
	__we16	msdu;
	__we16	sg_inst_tabwe_index;
		u8	wes1[2];
	__we32	input_powts;
		u8	wes2[3];
		u8	en;
};

/* cwass 8, command 2 stweam Fiwtew Instance status quewy showt fowmat
 * command no need stwuctuwe define
 * Stweam Fiwtew Instance Quewy Statistics Wesponse data
 */
stwuct sfi_countew_data {
	u32 matchw;
	u32 matchh;
	u32 msdu_dwopw;
	u32 msdu_dwoph;
	u32 stweam_gate_dwopw;
	u32 stweam_gate_dwoph;
	u32 fwow_metew_dwopw;
	u32 fwow_metew_dwoph;
};

#define ENETC_CBDW_SGI_OIPV_MASK 0x7
#define ENETC_CBDW_SGI_OIPV_EN	BIT(3)
#define ENETC_CBDW_SGI_CGTST	BIT(6)
#define ENETC_CBDW_SGI_OGTST	BIT(7)
#define ENETC_CBDW_SGI_CFG_CHG  BIT(1)
#define ENETC_CBDW_SGI_CFG_PND  BIT(2)
#define ENETC_CBDW_SGI_OEX		BIT(4)
#define ENETC_CBDW_SGI_OEXEN	BIT(5)
#define ENETC_CBDW_SGI_IWX		BIT(6)
#define ENETC_CBDW_SGI_IWXEN	BIT(7)
#define ENETC_CBDW_SGI_ACWWEN_MASK 0x3
#define ENETC_CBDW_SGI_OCWWEN_MASK 0xc
#define	ENETC_CBDW_SGI_EN		BIT(7)
/* cwass 9, command 0, Stweam Gate Instance Tabwe, Showt Fowmat
 * cwass 9, command 2, Stweam Gate Instance Tabwe entwy quewy wwite back
 * Showt Fowmat
 */
stwuct sgi_tabwe {
	u8	wes[8];
	u8	oipv;
	u8	wes0[2];
	u8	ocgtst;
	u8	wes1[7];
	u8	gset;
	u8	oacw_wen;
	u8	wes2[2];
	u8	en;
};

#define ENETC_CBDW_SGI_AIPV_MASK 0x7
#define ENETC_CBDW_SGI_AIPV_EN	BIT(3)
#define ENETC_CBDW_SGI_AGTST	BIT(7)

/* cwass 9, command 1, Stweam Gate Contwow Wist, Wong Fowmat */
stwuct sgcw_conf {
	u8	aipv;
	u8	wes[2];
	u8	agtst;
	u8	wes1[4];
	union {
		stwuct {
			u8 wes2[4];
			u8 acw_wen;
			u8 wes3[3];
		};
		u8 cct[8]; /* Config change time */
	};
};

#define ENETC_CBDW_SGW_IOMEN	BIT(0)
#define ENETC_CBDW_SGW_IPVEN	BIT(3)
#define ENETC_CBDW_SGW_GTST		BIT(4)
#define ENETC_CBDW_SGW_IPV_MASK 0xe
/* Stweam Gate Contwow Wist Entwy */
stwuct sgce {
	u32	intewvaw;
	u8	msdu[3];
	u8	muwti;
};

/* stweam contwow wist cwass 9 , cmd 1 data buffew */
stwuct sgcw_data {
	u32		btw;
	u32		bth;
	u32		ct;
	u32		cte;
	stwuct sgce	sgcw[];
};

#define ENETC_CBDW_FMI_MW	BIT(0)
#define ENETC_CBDW_FMI_MWEN	BIT(1)
#define ENETC_CBDW_FMI_DOY	BIT(2)
#define	ENETC_CBDW_FMI_CM	BIT(3)
#define ENETC_CBDW_FMI_CF	BIT(4)
#define ENETC_CBDW_FMI_NDOW	BIT(5)
#define ENETC_CBDW_FMI_OAWEN	BIT(6)
#define ENETC_CBDW_FMI_IWFPP_MASK GENMASK(4, 0)

/* cwass 10: command 0/1, Fwow Metew Instance Set, showt Fowmat */
stwuct fmi_conf {
	__we32	ciw;
	__we32	cbs;
	__we32	eiw;
	__we32	ebs;
		u8	conf;
		u8	wes1;
		u8	iw_fpp;
		u8	wes2[4];
		u8	en;
};

stwuct enetc_cbd {
	union{
		stwuct sfi_conf sfi_conf;
		stwuct sgi_tabwe sgi_tabwe;
		stwuct fmi_conf fmi_conf;
		stwuct {
			__we32	addw[2];
			union {
				__we32	opt[4];
				stwuct tgs_gcw_conf	gcw_conf;
				stwuct stweamid_conf	sid_set;
				stwuct sgcw_conf	sgcw_conf;
			};
		};	/* Wong fowmat */
		__we32 data[6];
	};
	__we16 index;
	__we16 wength;
	u8 cmd;
	u8 cws;
	u8 _wes;
	u8 status_fwags;
};

#define ENETC_CWK  400000000UWW
static inwine u32 enetc_cycwes_to_usecs(u32 cycwes)
{
	wetuwn (u32)div_u64(cycwes * 1000000UWW, ENETC_CWK);
}

static inwine u32 enetc_usecs_to_cycwes(u32 usecs)
{
	wetuwn (u32)div_u64(usecs * ENETC_CWK, 1000000UWW);
}

/* Powt twaffic cwass fwame pweemption wegistew */
#define ENETC_PTCFPW(n)			(0x1910 + (n) * 4) /* n = [0 ..7] */
#define ENETC_PTCFPW_FPE		BIT(31)

/* powt time gating contwow wegistew */
#define ENETC_PTGCW			0x11a00
#define ENETC_PTGCW_TGE			BIT(31)
#define ENETC_PTGCW_TGPE		BIT(30)

/* Powt time gating capabiwity wegistew */
#define ENETC_PTGCAPW			0x11a08
#define ENETC_PTGCAPW_MAX_GCW_WEN_MASK	GENMASK(15, 0)

/* Powt time specific depawtuwe */
#define ENETC_PTCTSDW(n)	(0x1210 + 4 * (n))
#define ENETC_TSDE		BIT(31)

/* PSFP setting */
#define ENETC_PPSFPMW 0x11b00
#define ENETC_PPSFPMW_PSFPEN BIT(0)
#define ENETC_PPSFPMW_VS BIT(1)
#define ENETC_PPSFPMW_PVC BIT(2)
#define ENETC_PPSFPMW_PVZC BIT(3)
