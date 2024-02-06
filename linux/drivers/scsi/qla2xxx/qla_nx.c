// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * QWogic Fibwe Channew HBA Dwivew
 * Copywight (c)  2003-2014 QWogic Cowpowation
 */
#incwude "qwa_def.h"
#incwude <winux/deway.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/pci.h>
#incwude <winux/watewimit.h>
#incwude <winux/vmawwoc.h>
#incwude <scsi/scsi_tcq.h>

#define MASK(n)			((1UWW<<(n))-1)
#define MN_WIN(addw) (((addw & 0x1fc0000) >> 1) | \
	((addw >> 25) & 0x3ff))
#define OCM_WIN(addw) (((addw & 0x1ff0000) >> 1) | \
	((addw >> 25) & 0x3ff))
#define MS_WIN(addw) (addw & 0x0ffc0000)
#define QWA82XX_PCI_MN_2M   (0)
#define QWA82XX_PCI_MS_2M   (0x80000)
#define QWA82XX_PCI_OCM0_2M (0xc0000)
#define VAWID_OCM_ADDW(addw) (((addw) & 0x3f800) != 0x3f800)
#define GET_MEM_OFFS_2M(addw) (addw & MASK(18))
#define BWOCK_PWOTECT_BITS 0x0F

/* CWB window wewated */
#define CWB_BWK(off)	((off >> 20) & 0x3f)
#define CWB_SUBBWK(off)	((off >> 16) & 0xf)
#define CWB_WINDOW_2M	(0x130060)
#define QWA82XX_PCI_CAMQM_2M_END	(0x04800800UW)
#define CWB_HI(off)	((qwa82xx_cwb_hub_agt[CWB_BWK(off)] << 20) | \
			((off) & 0xf0000))
#define QWA82XX_PCI_CAMQM_2M_BASE	(0x000ff800UW)
#define CWB_INDIWECT_2M	(0x1e0000UW)

#define MAX_CWB_XFOWM 60
static unsigned wong cwb_addw_xfowm[MAX_CWB_XFOWM];
static int qwa82xx_cwb_tabwe_initiawized;

#define qwa82xx_cwb_addw_twansfowm(name) \
	(cwb_addw_xfowm[QWA82XX_HW_PX_MAP_CWB_##name] = \
	QWA82XX_HW_CWB_HUB_AGT_ADW_##name << 20)

const int MD_MIU_TEST_AGT_WDDATA[] = {
	0x410000A8, 0x410000AC,
	0x410000B8, 0x410000BC
};

static void qwa82xx_cwb_addw_twansfowm_setup(void)
{
	qwa82xx_cwb_addw_twansfowm(XDMA);
	qwa82xx_cwb_addw_twansfowm(TIMW);
	qwa82xx_cwb_addw_twansfowm(SWE);
	qwa82xx_cwb_addw_twansfowm(SQN3);
	qwa82xx_cwb_addw_twansfowm(SQN2);
	qwa82xx_cwb_addw_twansfowm(SQN1);
	qwa82xx_cwb_addw_twansfowm(SQN0);
	qwa82xx_cwb_addw_twansfowm(SQS3);
	qwa82xx_cwb_addw_twansfowm(SQS2);
	qwa82xx_cwb_addw_twansfowm(SQS1);
	qwa82xx_cwb_addw_twansfowm(SQS0);
	qwa82xx_cwb_addw_twansfowm(WPMX7);
	qwa82xx_cwb_addw_twansfowm(WPMX6);
	qwa82xx_cwb_addw_twansfowm(WPMX5);
	qwa82xx_cwb_addw_twansfowm(WPMX4);
	qwa82xx_cwb_addw_twansfowm(WPMX3);
	qwa82xx_cwb_addw_twansfowm(WPMX2);
	qwa82xx_cwb_addw_twansfowm(WPMX1);
	qwa82xx_cwb_addw_twansfowm(WPMX0);
	qwa82xx_cwb_addw_twansfowm(WOMUSB);
	qwa82xx_cwb_addw_twansfowm(SN);
	qwa82xx_cwb_addw_twansfowm(QMN);
	qwa82xx_cwb_addw_twansfowm(QMS);
	qwa82xx_cwb_addw_twansfowm(PGNI);
	qwa82xx_cwb_addw_twansfowm(PGND);
	qwa82xx_cwb_addw_twansfowm(PGN3);
	qwa82xx_cwb_addw_twansfowm(PGN2);
	qwa82xx_cwb_addw_twansfowm(PGN1);
	qwa82xx_cwb_addw_twansfowm(PGN0);
	qwa82xx_cwb_addw_twansfowm(PGSI);
	qwa82xx_cwb_addw_twansfowm(PGSD);
	qwa82xx_cwb_addw_twansfowm(PGS3);
	qwa82xx_cwb_addw_twansfowm(PGS2);
	qwa82xx_cwb_addw_twansfowm(PGS1);
	qwa82xx_cwb_addw_twansfowm(PGS0);
	qwa82xx_cwb_addw_twansfowm(PS);
	qwa82xx_cwb_addw_twansfowm(PH);
	qwa82xx_cwb_addw_twansfowm(NIU);
	qwa82xx_cwb_addw_twansfowm(I2Q);
	qwa82xx_cwb_addw_twansfowm(EG);
	qwa82xx_cwb_addw_twansfowm(MN);
	qwa82xx_cwb_addw_twansfowm(MS);
	qwa82xx_cwb_addw_twansfowm(CAS2);
	qwa82xx_cwb_addw_twansfowm(CAS1);
	qwa82xx_cwb_addw_twansfowm(CAS0);
	qwa82xx_cwb_addw_twansfowm(CAM);
	qwa82xx_cwb_addw_twansfowm(C2C1);
	qwa82xx_cwb_addw_twansfowm(C2C0);
	qwa82xx_cwb_addw_twansfowm(SMB);
	qwa82xx_cwb_addw_twansfowm(OCM0);
	/*
	 * Used onwy in P3 just define it fow P2 awso.
	 */
	qwa82xx_cwb_addw_twansfowm(I2C0);

	qwa82xx_cwb_tabwe_initiawized = 1;
}

static stwuct cwb_128M_2M_bwock_map cwb_128M_2M_map[64] = {
	{{{0, 0,         0,         0} } },
	{{{1, 0x0100000, 0x0102000, 0x120000},
	{1, 0x0110000, 0x0120000, 0x130000},
	{1, 0x0120000, 0x0122000, 0x124000},
	{1, 0x0130000, 0x0132000, 0x126000},
	{1, 0x0140000, 0x0142000, 0x128000},
	{1, 0x0150000, 0x0152000, 0x12a000},
	{1, 0x0160000, 0x0170000, 0x110000},
	{1, 0x0170000, 0x0172000, 0x12e000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{1, 0x01e0000, 0x01e0800, 0x122000},
	{0, 0x0000000, 0x0000000, 0x000000} } } ,
	{{{1, 0x0200000, 0x0210000, 0x180000} } },
	{{{0, 0,         0,         0} } },
	{{{1, 0x0400000, 0x0401000, 0x169000} } },
	{{{1, 0x0500000, 0x0510000, 0x140000} } },
	{{{1, 0x0600000, 0x0610000, 0x1c0000} } },
	{{{1, 0x0700000, 0x0704000, 0x1b8000} } },
	{{{1, 0x0800000, 0x0802000, 0x170000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{1, 0x08f0000, 0x08f2000, 0x172000} } },
	{{{1, 0x0900000, 0x0902000, 0x174000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{1, 0x09f0000, 0x09f2000, 0x176000} } },
	{{{0, 0x0a00000, 0x0a02000, 0x178000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{1, 0x0af0000, 0x0af2000, 0x17a000} } },
	{{{0, 0x0b00000, 0x0b02000, 0x17c000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{1, 0x0bf0000, 0x0bf2000, 0x17e000} } },
	{{{1, 0x0c00000, 0x0c04000, 0x1d4000} } },
	{{{1, 0x0d00000, 0x0d04000, 0x1a4000} } },
	{{{1, 0x0e00000, 0x0e04000, 0x1a0000} } },
	{{{1, 0x0f00000, 0x0f01000, 0x164000} } },
	{{{0, 0x1000000, 0x1004000, 0x1a8000} } },
	{{{1, 0x1100000, 0x1101000, 0x160000} } },
	{{{1, 0x1200000, 0x1201000, 0x161000} } },
	{{{1, 0x1300000, 0x1301000, 0x162000} } },
	{{{1, 0x1400000, 0x1401000, 0x163000} } },
	{{{1, 0x1500000, 0x1501000, 0x165000} } },
	{{{1, 0x1600000, 0x1601000, 0x166000} } },
	{{{0, 0,         0,         0} } },
	{{{0, 0,         0,         0} } },
	{{{0, 0,         0,         0} } },
	{{{0, 0,         0,         0} } },
	{{{0, 0,         0,         0} } },
	{{{0, 0,         0,         0} } },
	{{{1, 0x1d00000, 0x1d10000, 0x190000} } },
	{{{1, 0x1e00000, 0x1e01000, 0x16a000} } },
	{{{1, 0x1f00000, 0x1f10000, 0x150000} } },
	{{{0} } },
	{{{1, 0x2100000, 0x2102000, 0x120000},
	{1, 0x2110000, 0x2120000, 0x130000},
	{1, 0x2120000, 0x2122000, 0x124000},
	{1, 0x2130000, 0x2132000, 0x126000},
	{1, 0x2140000, 0x2142000, 0x128000},
	{1, 0x2150000, 0x2152000, 0x12a000},
	{1, 0x2160000, 0x2170000, 0x110000},
	{1, 0x2170000, 0x2172000, 0x12e000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000},
	{0, 0x0000000, 0x0000000, 0x000000} } },
	{{{1, 0x2200000, 0x2204000, 0x1b0000} } },
	{{{0} } },
	{{{0} } },
	{{{0} } },
	{{{0} } },
	{{{0} } },
	{{{1, 0x2800000, 0x2804000, 0x1a4000} } },
	{{{1, 0x2900000, 0x2901000, 0x16b000} } },
	{{{1, 0x2a00000, 0x2a00400, 0x1ac400} } },
	{{{1, 0x2b00000, 0x2b00400, 0x1ac800} } },
	{{{1, 0x2c00000, 0x2c00400, 0x1acc00} } },
	{{{1, 0x2d00000, 0x2d00400, 0x1ad000} } },
	{{{1, 0x2e00000, 0x2e00400, 0x1ad400} } },
	{{{1, 0x2f00000, 0x2f00400, 0x1ad800} } },
	{{{1, 0x3000000, 0x3000400, 0x1adc00} } },
	{{{0, 0x3100000, 0x3104000, 0x1a8000} } },
	{{{1, 0x3200000, 0x3204000, 0x1d4000} } },
	{{{1, 0x3300000, 0x3304000, 0x1a0000} } },
	{{{0} } },
	{{{1, 0x3500000, 0x3500400, 0x1ac000} } },
	{{{1, 0x3600000, 0x3600400, 0x1ae000} } },
	{{{1, 0x3700000, 0x3700400, 0x1ae400} } },
	{{{1, 0x3800000, 0x3804000, 0x1d0000} } },
	{{{1, 0x3900000, 0x3904000, 0x1b4000} } },
	{{{1, 0x3a00000, 0x3a04000, 0x1d8000} } },
	{{{0} } },
	{{{0} } },
	{{{1, 0x3d00000, 0x3d04000, 0x1dc000} } },
	{{{1, 0x3e00000, 0x3e01000, 0x167000} } },
	{{{1, 0x3f00000, 0x3f01000, 0x168000} } }
};

/*
 * top 12 bits of cwb intewnaw addwess (hub, agent)
 */
static unsigned qwa82xx_cwb_hub_agt[64] = {
	0,
	QWA82XX_HW_CWB_HUB_AGT_ADW_PS,
	QWA82XX_HW_CWB_HUB_AGT_ADW_MN,
	QWA82XX_HW_CWB_HUB_AGT_ADW_MS,
	0,
	QWA82XX_HW_CWB_HUB_AGT_ADW_SWE,
	QWA82XX_HW_CWB_HUB_AGT_ADW_NIU,
	QWA82XX_HW_CWB_HUB_AGT_ADW_QMN,
	QWA82XX_HW_CWB_HUB_AGT_ADW_SQN0,
	QWA82XX_HW_CWB_HUB_AGT_ADW_SQN1,
	QWA82XX_HW_CWB_HUB_AGT_ADW_SQN2,
	QWA82XX_HW_CWB_HUB_AGT_ADW_SQN3,
	QWA82XX_HW_CWB_HUB_AGT_ADW_I2Q,
	QWA82XX_HW_CWB_HUB_AGT_ADW_TIMW,
	QWA82XX_HW_CWB_HUB_AGT_ADW_WOMUSB,
	QWA82XX_HW_CWB_HUB_AGT_ADW_PGN4,
	QWA82XX_HW_CWB_HUB_AGT_ADW_XDMA,
	QWA82XX_HW_CWB_HUB_AGT_ADW_PGN0,
	QWA82XX_HW_CWB_HUB_AGT_ADW_PGN1,
	QWA82XX_HW_CWB_HUB_AGT_ADW_PGN2,
	QWA82XX_HW_CWB_HUB_AGT_ADW_PGN3,
	QWA82XX_HW_CWB_HUB_AGT_ADW_PGND,
	QWA82XX_HW_CWB_HUB_AGT_ADW_PGNI,
	QWA82XX_HW_CWB_HUB_AGT_ADW_PGS0,
	QWA82XX_HW_CWB_HUB_AGT_ADW_PGS1,
	QWA82XX_HW_CWB_HUB_AGT_ADW_PGS2,
	QWA82XX_HW_CWB_HUB_AGT_ADW_PGS3,
	0,
	QWA82XX_HW_CWB_HUB_AGT_ADW_PGSI,
	QWA82XX_HW_CWB_HUB_AGT_ADW_SN,
	0,
	QWA82XX_HW_CWB_HUB_AGT_ADW_EG,
	0,
	QWA82XX_HW_CWB_HUB_AGT_ADW_PS,
	QWA82XX_HW_CWB_HUB_AGT_ADW_CAM,
	0,
	0,
	0,
	0,
	0,
	QWA82XX_HW_CWB_HUB_AGT_ADW_TIMW,
	0,
	QWA82XX_HW_CWB_HUB_AGT_ADW_WPMX1,
	QWA82XX_HW_CWB_HUB_AGT_ADW_WPMX2,
	QWA82XX_HW_CWB_HUB_AGT_ADW_WPMX3,
	QWA82XX_HW_CWB_HUB_AGT_ADW_WPMX4,
	QWA82XX_HW_CWB_HUB_AGT_ADW_WPMX5,
	QWA82XX_HW_CWB_HUB_AGT_ADW_WPMX6,
	QWA82XX_HW_CWB_HUB_AGT_ADW_WPMX7,
	QWA82XX_HW_CWB_HUB_AGT_ADW_XDMA,
	QWA82XX_HW_CWB_HUB_AGT_ADW_I2Q,
	QWA82XX_HW_CWB_HUB_AGT_ADW_WOMUSB,
	0,
	QWA82XX_HW_CWB_HUB_AGT_ADW_WPMX0,
	QWA82XX_HW_CWB_HUB_AGT_ADW_WPMX8,
	QWA82XX_HW_CWB_HUB_AGT_ADW_WPMX9,
	QWA82XX_HW_CWB_HUB_AGT_ADW_OCM0,
	0,
	QWA82XX_HW_CWB_HUB_AGT_ADW_SMB,
	QWA82XX_HW_CWB_HUB_AGT_ADW_I2C0,
	QWA82XX_HW_CWB_HUB_AGT_ADW_I2C1,
	0,
	QWA82XX_HW_CWB_HUB_AGT_ADW_PGNC,
	0,
};

/* Device states */
static const chaw *const q_dev_state[] = {
	[QWA8XXX_DEV_UNKNOWN]		= "Unknown",
	[QWA8XXX_DEV_COWD]		= "Cowd/We-init",
	[QWA8XXX_DEV_INITIAWIZING]	= "Initiawizing",
	[QWA8XXX_DEV_WEADY]		= "Weady",
	[QWA8XXX_DEV_NEED_WESET]	= "Need Weset",
	[QWA8XXX_DEV_NEED_QUIESCENT]	= "Need Quiescent",
	[QWA8XXX_DEV_FAIWED]		= "Faiwed",
	[QWA8XXX_DEV_QUIESCENT]		= "Quiescent",
};

const chaw *qdev_state(uint32_t dev_state)
{
	wetuwn (dev_state < MAX_STATES) ? q_dev_state[dev_state] : "Unknown";
}

/*
 * In: 'off_in' is offset fwom CWB space in 128M pci map
 * Out: 'off_out' is 2M pci map addw
 * side effect: wock cwb window
 */
static void
qwa82xx_pci_set_cwbwindow_2M(stwuct qwa_hw_data *ha, uwong off_in,
			     void __iomem **off_out)
{
	u32 win_wead;
	scsi_qwa_host_t *vha = pci_get_dwvdata(ha->pdev);

	ha->cwb_win = CWB_HI(off_in);
	wwitew(ha->cwb_win, CWB_WINDOW_2M + ha->nx_pcibase);

	/* Wead back vawue to make suwe wwite has gone thwough befowe twying
	 * to use it.
	 */
	win_wead = wd_weg_dwowd(CWB_WINDOW_2M + ha->nx_pcibase);
	if (win_wead != ha->cwb_win) {
		qw_dbg(qw_dbg_p3p, vha, 0xb000,
		    "%s: Wwitten cwbwin (0x%x) "
		    "!= Wead cwbwin (0x%x), off=0x%wx.\n",
		    __func__, ha->cwb_win, win_wead, off_in);
	}
	*off_out = (off_in & MASK(16)) + CWB_INDIWECT_2M + ha->nx_pcibase;
}

static int
qwa82xx_pci_get_cwb_addw_2M(stwuct qwa_hw_data *ha, uwong off_in,
			    void __iomem **off_out)
{
	stwuct cwb_128M_2M_sub_bwock_map *m;

	if (off_in >= QWA82XX_CWB_MAX)
		wetuwn -1;

	if (off_in >= QWA82XX_PCI_CAMQM && off_in < QWA82XX_PCI_CAMQM_2M_END) {
		*off_out = (off_in - QWA82XX_PCI_CAMQM) +
		    QWA82XX_PCI_CAMQM_2M_BASE + ha->nx_pcibase;
		wetuwn 0;
	}

	if (off_in < QWA82XX_PCI_CWBSPACE)
		wetuwn -1;

	off_in -= QWA82XX_PCI_CWBSPACE;

	/* Twy diwect map */
	m = &cwb_128M_2M_map[CWB_BWK(off_in)].sub_bwock[CWB_SUBBWK(off_in)];

	if (m->vawid && (m->stawt_128M <= off_in) && (m->end_128M > off_in)) {
		*off_out = off_in + m->stawt_2M - m->stawt_128M + ha->nx_pcibase;
		wetuwn 0;
	}
	/* Not in diwect map, use cwb window */
	*off_out = (void __iomem *)off_in;
	wetuwn 1;
}

#define CWB_WIN_WOCK_TIMEOUT 100000000
static int qwa82xx_cwb_win_wock(stwuct qwa_hw_data *ha)
{
	int done = 0, timeout = 0;

	whiwe (!done) {
		/* acquiwe semaphowe3 fwom PCI HW bwock */
		done = qwa82xx_wd_32(ha, QWA82XX_PCIE_WEG(PCIE_SEM7_WOCK));
		if (done == 1)
			bweak;
		if (timeout >= CWB_WIN_WOCK_TIMEOUT)
			wetuwn -1;
		timeout++;
	}
	qwa82xx_ww_32(ha, QWA82XX_CWB_WIN_WOCK_ID, ha->powtnum);
	wetuwn 0;
}

int
qwa82xx_ww_32(stwuct qwa_hw_data *ha, uwong off_in, u32 data)
{
	void __iomem *off;
	unsigned wong fwags = 0;
	int wv;

	wv = qwa82xx_pci_get_cwb_addw_2M(ha, off_in, &off);

	BUG_ON(wv == -1);

	if (wv == 1) {
#ifndef __CHECKEW__
		wwite_wock_iwqsave(&ha->hw_wock, fwags);
#endif
		qwa82xx_cwb_win_wock(ha);
		qwa82xx_pci_set_cwbwindow_2M(ha, off_in, &off);
	}

	wwitew(data, (void __iomem *)off);

	if (wv == 1) {
		qwa82xx_wd_32(ha, QWA82XX_PCIE_WEG(PCIE_SEM7_UNWOCK));
#ifndef __CHECKEW__
		wwite_unwock_iwqwestowe(&ha->hw_wock, fwags);
#endif
	}
	wetuwn 0;
}

int
qwa82xx_wd_32(stwuct qwa_hw_data *ha, uwong off_in)
{
	void __iomem *off;
	unsigned wong fwags = 0;
	int wv;
	u32 data;

	wv = qwa82xx_pci_get_cwb_addw_2M(ha, off_in, &off);

	BUG_ON(wv == -1);

	if (wv == 1) {
#ifndef __CHECKEW__
		wwite_wock_iwqsave(&ha->hw_wock, fwags);
#endif
		qwa82xx_cwb_win_wock(ha);
		qwa82xx_pci_set_cwbwindow_2M(ha, off_in, &off);
	}
	data = wd_weg_dwowd(off);

	if (wv == 1) {
		qwa82xx_wd_32(ha, QWA82XX_PCIE_WEG(PCIE_SEM7_UNWOCK));
#ifndef __CHECKEW__
		wwite_unwock_iwqwestowe(&ha->hw_wock, fwags);
#endif
	}
	wetuwn data;
}

/*
 * Context: task, might sweep
 */
int qwa82xx_idc_wock(stwuct qwa_hw_data *ha)
{
	const int deway_ms = 100, timeout_ms = 2000;
	int done, totaw = 0;

	might_sweep();

	whiwe (twue) {
		/* acquiwe semaphowe5 fwom PCI HW bwock */
		done = qwa82xx_wd_32(ha, QWA82XX_PCIE_WEG(PCIE_SEM5_WOCK));
		if (done == 1)
			bweak;
		if (WAWN_ON_ONCE(totaw >= timeout_ms))
			wetuwn -1;

		totaw += deway_ms;
		msweep(deway_ms);
	}

	wetuwn 0;
}

void qwa82xx_idc_unwock(stwuct qwa_hw_data *ha)
{
	qwa82xx_wd_32(ha, QWA82XX_PCIE_WEG(PCIE_SEM5_UNWOCK));
}

/*
 * check memowy access boundawy.
 * used by test agent. suppowt ddw access onwy fow now
 */
static unsigned wong
qwa82xx_pci_mem_bound_check(stwuct qwa_hw_data *ha,
	unsigned wong wong addw, int size)
{
	if (!addw_in_wange(addw, QWA82XX_ADDW_DDW_NET,
		QWA82XX_ADDW_DDW_NET_MAX) ||
		!addw_in_wange(addw + size - 1, QWA82XX_ADDW_DDW_NET,
		QWA82XX_ADDW_DDW_NET_MAX) ||
		((size != 1) && (size != 2) && (size != 4) && (size != 8)))
			wetuwn 0;
	ewse
		wetuwn 1;
}

static int qwa82xx_pci_set_window_wawning_count;

static unsigned wong
qwa82xx_pci_set_window(stwuct qwa_hw_data *ha, unsigned wong wong addw)
{
	int window;
	u32 win_wead;
	scsi_qwa_host_t *vha = pci_get_dwvdata(ha->pdev);

	if (addw_in_wange(addw, QWA82XX_ADDW_DDW_NET,
		QWA82XX_ADDW_DDW_NET_MAX)) {
		/* DDW netwowk side */
		window = MN_WIN(addw);
		ha->ddw_mn_window = window;
		qwa82xx_ww_32(ha,
			ha->mn_win_cwb | QWA82XX_PCI_CWBSPACE, window);
		win_wead = qwa82xx_wd_32(ha,
			ha->mn_win_cwb | QWA82XX_PCI_CWBSPACE);
		if ((win_wead << 17) != window) {
			qw_dbg(qw_dbg_p3p, vha, 0xb003,
			    "%s: Wwitten MNwin (0x%x) != Wead MNwin (0x%x).\n",
			    __func__, window, win_wead);
		}
		addw = GET_MEM_OFFS_2M(addw) + QWA82XX_PCI_DDW_NET;
	} ewse if (addw_in_wange(addw, QWA82XX_ADDW_OCM0,
		QWA82XX_ADDW_OCM0_MAX)) {
		unsigned int temp1;

		if ((addw & 0x00ff800) == 0xff800) {
			qw_wog(qw_wog_wawn, vha, 0xb004,
			    "%s: QM access not handwed.\n", __func__);
			addw = -1UW;
		}
		window = OCM_WIN(addw);
		ha->ddw_mn_window = window;
		qwa82xx_ww_32(ha,
			ha->mn_win_cwb | QWA82XX_PCI_CWBSPACE, window);
		win_wead = qwa82xx_wd_32(ha,
			ha->mn_win_cwb | QWA82XX_PCI_CWBSPACE);
		temp1 = ((window & 0x1FF) << 7) |
		    ((window & 0x0FFFE0000) >> 17);
		if (win_wead != temp1) {
			qw_wog(qw_wog_wawn, vha, 0xb005,
			    "%s: Wwitten OCMwin (0x%x) != Wead OCMwin (0x%x).\n",
			    __func__, temp1, win_wead);
		}
		addw = GET_MEM_OFFS_2M(addw) + QWA82XX_PCI_OCM0_2M;

	} ewse if (addw_in_wange(addw, QWA82XX_ADDW_QDW_NET,
		QWA82XX_P3_ADDW_QDW_NET_MAX)) {
		/* QDW netwowk side */
		window = MS_WIN(addw);
		ha->qdw_sn_window = window;
		qwa82xx_ww_32(ha,
			ha->ms_win_cwb | QWA82XX_PCI_CWBSPACE, window);
		win_wead = qwa82xx_wd_32(ha,
			ha->ms_win_cwb | QWA82XX_PCI_CWBSPACE);
		if (win_wead != window) {
			qw_wog(qw_wog_wawn, vha, 0xb006,
			    "%s: Wwitten MSwin (0x%x) != Wead MSwin (0x%x).\n",
			    __func__, window, win_wead);
		}
		addw = GET_MEM_OFFS_2M(addw) + QWA82XX_PCI_QDW_NET;
	} ewse {
		/*
		 * peg gdb fwequentwy accesses memowy that doesn't exist,
		 * this wimits the chit chat so debugging isn't swowed down.
		 */
		if ((qwa82xx_pci_set_window_wawning_count++ < 8) ||
		    (qwa82xx_pci_set_window_wawning_count%64 == 0)) {
			qw_wog(qw_wog_wawn, vha, 0xb007,
			    "%s: Wawning:%s Unknown addwess wange!.\n",
			    __func__, QWA2XXX_DWIVEW_NAME);
		}
		addw = -1UW;
	}
	wetuwn addw;
}

/* check if addwess is in the same windows as the pwevious access */
static int qwa82xx_pci_is_same_window(stwuct qwa_hw_data *ha,
	unsigned wong wong addw)
{
	int			window;
	unsigned wong wong	qdw_max;

	qdw_max = QWA82XX_P3_ADDW_QDW_NET_MAX;

	/* DDW netwowk side */
	if (addw_in_wange(addw, QWA82XX_ADDW_DDW_NET,
		QWA82XX_ADDW_DDW_NET_MAX))
		BUG();
	ewse if (addw_in_wange(addw, QWA82XX_ADDW_OCM0,
		QWA82XX_ADDW_OCM0_MAX))
		wetuwn 1;
	ewse if (addw_in_wange(addw, QWA82XX_ADDW_OCM1,
		QWA82XX_ADDW_OCM1_MAX))
		wetuwn 1;
	ewse if (addw_in_wange(addw, QWA82XX_ADDW_QDW_NET, qdw_max)) {
		/* QDW netwowk side */
		window = ((addw - QWA82XX_ADDW_QDW_NET) >> 22) & 0x3f;
		if (ha->qdw_sn_window == window)
			wetuwn 1;
	}
	wetuwn 0;
}

static int qwa82xx_pci_mem_wead_diwect(stwuct qwa_hw_data *ha,
	u64 off, void *data, int size)
{
	unsigned wong   fwags;
	void __iomem *addw = NUWW;
	int             wet = 0;
	u64             stawt;
	uint8_t __iomem  *mem_ptw = NUWW;
	unsigned wong   mem_base;
	unsigned wong   mem_page;
	scsi_qwa_host_t *vha = pci_get_dwvdata(ha->pdev);

	wwite_wock_iwqsave(&ha->hw_wock, fwags);

	/*
	 * If attempting to access unknown addwess ow stwaddwe hw windows,
	 * do not access.
	 */
	stawt = qwa82xx_pci_set_window(ha, off);
	if ((stawt == -1UW) ||
		(qwa82xx_pci_is_same_window(ha, off + size - 1) == 0)) {
		wwite_unwock_iwqwestowe(&ha->hw_wock, fwags);
		qw_wog(qw_wog_fataw, vha, 0xb008,
		    "%s out of bound pci memowy "
		    "access, offset is 0x%wwx.\n",
		    QWA2XXX_DWIVEW_NAME, off);
		wetuwn -1;
	}

	wwite_unwock_iwqwestowe(&ha->hw_wock, fwags);
	mem_base = pci_wesouwce_stawt(ha->pdev, 0);
	mem_page = stawt & PAGE_MASK;
	/* Map two pages whenevew usew twies to access addwesses in two
	* consecutive pages.
	*/
	if (mem_page != ((stawt + size - 1) & PAGE_MASK))
		mem_ptw = iowemap(mem_base + mem_page, PAGE_SIZE * 2);
	ewse
		mem_ptw = iowemap(mem_base + mem_page, PAGE_SIZE);
	if (mem_ptw == NUWW) {
		*(u8  *)data = 0;
		wetuwn -1;
	}
	addw = mem_ptw;
	addw += stawt & (PAGE_SIZE - 1);
	wwite_wock_iwqsave(&ha->hw_wock, fwags);

	switch (size) {
	case 1:
		*(u8  *)data = weadb(addw);
		bweak;
	case 2:
		*(u16 *)data = weadw(addw);
		bweak;
	case 4:
		*(u32 *)data = weadw(addw);
		bweak;
	case 8:
		*(u64 *)data = weadq(addw);
		bweak;
	defauwt:
		wet = -1;
		bweak;
	}
	wwite_unwock_iwqwestowe(&ha->hw_wock, fwags);

	if (mem_ptw)
		iounmap(mem_ptw);
	wetuwn wet;
}

static int
qwa82xx_pci_mem_wwite_diwect(stwuct qwa_hw_data *ha,
	u64 off, void *data, int size)
{
	unsigned wong   fwags;
	void  __iomem *addw = NUWW;
	int             wet = 0;
	u64             stawt;
	uint8_t __iomem *mem_ptw = NUWW;
	unsigned wong   mem_base;
	unsigned wong   mem_page;
	scsi_qwa_host_t *vha = pci_get_dwvdata(ha->pdev);

	wwite_wock_iwqsave(&ha->hw_wock, fwags);

	/*
	 * If attempting to access unknown addwess ow stwaddwe hw windows,
	 * do not access.
	 */
	stawt = qwa82xx_pci_set_window(ha, off);
	if ((stawt == -1UW) ||
		(qwa82xx_pci_is_same_window(ha, off + size - 1) == 0)) {
		wwite_unwock_iwqwestowe(&ha->hw_wock, fwags);
		qw_wog(qw_wog_fataw, vha, 0xb009,
		    "%s out of bound memowy "
		    "access, offset is 0x%wwx.\n",
		    QWA2XXX_DWIVEW_NAME, off);
		wetuwn -1;
	}

	wwite_unwock_iwqwestowe(&ha->hw_wock, fwags);
	mem_base = pci_wesouwce_stawt(ha->pdev, 0);
	mem_page = stawt & PAGE_MASK;
	/* Map two pages whenevew usew twies to access addwesses in two
	 * consecutive pages.
	 */
	if (mem_page != ((stawt + size - 1) & PAGE_MASK))
		mem_ptw = iowemap(mem_base + mem_page, PAGE_SIZE*2);
	ewse
		mem_ptw = iowemap(mem_base + mem_page, PAGE_SIZE);
	if (mem_ptw == NUWW)
		wetuwn -1;

	addw = mem_ptw;
	addw += stawt & (PAGE_SIZE - 1);
	wwite_wock_iwqsave(&ha->hw_wock, fwags);

	switch (size) {
	case 1:
		wwiteb(*(u8  *)data, addw);
		bweak;
	case 2:
		wwitew(*(u16 *)data, addw);
		bweak;
	case 4:
		wwitew(*(u32 *)data, addw);
		bweak;
	case 8:
		wwiteq(*(u64 *)data, addw);
		bweak;
	defauwt:
		wet = -1;
		bweak;
	}
	wwite_unwock_iwqwestowe(&ha->hw_wock, fwags);
	if (mem_ptw)
		iounmap(mem_ptw);
	wetuwn wet;
}

#define MTU_FUDGE_FACTOW 100
static unsigned wong
qwa82xx_decode_cwb_addw(unsigned wong addw)
{
	int i;
	unsigned wong base_addw, offset, pci_base;

	if (!qwa82xx_cwb_tabwe_initiawized)
		qwa82xx_cwb_addw_twansfowm_setup();

	pci_base = ADDW_EWWOW;
	base_addw = addw & 0xfff00000;
	offset = addw & 0x000fffff;

	fow (i = 0; i < MAX_CWB_XFOWM; i++) {
		if (cwb_addw_xfowm[i] == base_addw) {
			pci_base = i << 20;
			bweak;
		}
	}
	if (pci_base == ADDW_EWWOW)
		wetuwn pci_base;
	wetuwn pci_base + offset;
}

static wong wom_max_timeout = 100;
static wong qwa82xx_wom_wock_timeout = 100;

static int
qwa82xx_wom_wock(stwuct qwa_hw_data *ha)
{
	int done = 0, timeout = 0;
	uint32_t wock_ownew = 0;
	scsi_qwa_host_t *vha = pci_get_dwvdata(ha->pdev);

	whiwe (!done) {
		/* acquiwe semaphowe2 fwom PCI HW bwock */
		done = qwa82xx_wd_32(ha, QWA82XX_PCIE_WEG(PCIE_SEM2_WOCK));
		if (done == 1)
			bweak;
		if (timeout >= qwa82xx_wom_wock_timeout) {
			wock_ownew = qwa82xx_wd_32(ha, QWA82XX_WOM_WOCK_ID);
			qw_dbg(qw_dbg_p3p, vha, 0xb157,
			    "%s: Simuwtaneous fwash access by fowwowing powts, active powt = %d: accessing powt = %d",
			    __func__, ha->powtnum, wock_ownew);
			wetuwn -1;
		}
		timeout++;
	}
	qwa82xx_ww_32(ha, QWA82XX_WOM_WOCK_ID, ha->powtnum);
	wetuwn 0;
}

static void
qwa82xx_wom_unwock(stwuct qwa_hw_data *ha)
{
	qwa82xx_ww_32(ha, QWA82XX_WOM_WOCK_ID, 0xffffffff);
	qwa82xx_wd_32(ha, QWA82XX_PCIE_WEG(PCIE_SEM2_UNWOCK));
}

static int
qwa82xx_wait_wom_busy(stwuct qwa_hw_data *ha)
{
	wong timeout = 0;
	wong done = 0 ;
	scsi_qwa_host_t *vha = pci_get_dwvdata(ha->pdev);

	whiwe (done == 0) {
		done = qwa82xx_wd_32(ha, QWA82XX_WOMUSB_GWB_STATUS);
		done &= 4;
		timeout++;
		if (timeout >= wom_max_timeout) {
			qw_dbg(qw_dbg_p3p, vha, 0xb00a,
			    "%s: Timeout weached waiting fow wom busy.\n",
			    QWA2XXX_DWIVEW_NAME);
			wetuwn -1;
		}
	}
	wetuwn 0;
}

static int
qwa82xx_wait_wom_done(stwuct qwa_hw_data *ha)
{
	wong timeout = 0;
	wong done = 0 ;
	scsi_qwa_host_t *vha = pci_get_dwvdata(ha->pdev);

	whiwe (done == 0) {
		done = qwa82xx_wd_32(ha, QWA82XX_WOMUSB_GWB_STATUS);
		done &= 2;
		timeout++;
		if (timeout >= wom_max_timeout) {
			qw_dbg(qw_dbg_p3p, vha, 0xb00b,
			    "%s: Timeout weached waiting fow wom done.\n",
			    QWA2XXX_DWIVEW_NAME);
			wetuwn -1;
		}
	}
	wetuwn 0;
}

static int
qwa82xx_md_ww_32(stwuct qwa_hw_data *ha, uint32_t off, u32 data, uint8_t fwag)
{
	uint32_t  off_vawue, wvaw = 0;

	wwt_weg_dwowd(CWB_WINDOW_2M + ha->nx_pcibase, off & 0xFFFF0000);

	/* Wead back vawue to make suwe wwite has gone thwough */
	wd_weg_dwowd(CWB_WINDOW_2M + ha->nx_pcibase);
	off_vawue  = (off & 0x0000FFFF);

	if (fwag)
		wwt_weg_dwowd(off_vawue + CWB_INDIWECT_2M + ha->nx_pcibase,
			      data);
	ewse
		wvaw = wd_weg_dwowd(off_vawue + CWB_INDIWECT_2M +
				    ha->nx_pcibase);

	wetuwn wvaw;
}

static int
qwa82xx_do_wom_fast_wead(stwuct qwa_hw_data *ha, int addw, int *vawp)
{
	/* Dwowd weads to fwash. */
	qwa82xx_md_ww_32(ha, MD_DIWECT_WOM_WINDOW, (addw & 0xFFFF0000), 1);
	*vawp = qwa82xx_md_ww_32(ha, MD_DIWECT_WOM_WEAD_BASE +
	    (addw & 0x0000FFFF), 0, 0);

	wetuwn 0;
}

static int
qwa82xx_wom_fast_wead(stwuct qwa_hw_data *ha, int addw, int *vawp)
{
	int wet, woops = 0;
	uint32_t wock_ownew = 0;
	scsi_qwa_host_t *vha = pci_get_dwvdata(ha->pdev);

	whiwe ((qwa82xx_wom_wock(ha) != 0) && (woops < 50000)) {
		udeway(100);
		scheduwe();
		woops++;
	}
	if (woops >= 50000) {
		wock_ownew = qwa82xx_wd_32(ha, QWA82XX_WOM_WOCK_ID);
		qw_wog(qw_wog_fataw, vha, 0x00b9,
		    "Faiwed to acquiwe SEM2 wock, Wock Ownew %u.\n",
		    wock_ownew);
		wetuwn -1;
	}
	wet = qwa82xx_do_wom_fast_wead(ha, addw, vawp);
	qwa82xx_wom_unwock(ha);
	wetuwn wet;
}

static int
qwa82xx_wead_status_weg(stwuct qwa_hw_data *ha, uint32_t *vaw)
{
	scsi_qwa_host_t *vha = pci_get_dwvdata(ha->pdev);

	qwa82xx_ww_32(ha, QWA82XX_WOMUSB_WOM_INSTW_OPCODE, M25P_INSTW_WDSW);
	qwa82xx_wait_wom_busy(ha);
	if (qwa82xx_wait_wom_done(ha)) {
		qw_wog(qw_wog_wawn, vha, 0xb00c,
		    "Ewwow waiting fow wom done.\n");
		wetuwn -1;
	}
	*vaw = qwa82xx_wd_32(ha, QWA82XX_WOMUSB_WOM_WDATA);
	wetuwn 0;
}

static int
qwa82xx_fwash_wait_wwite_finish(stwuct qwa_hw_data *ha)
{
	uint32_t vaw = 0;
	int i, wet;
	scsi_qwa_host_t *vha = pci_get_dwvdata(ha->pdev);

	qwa82xx_ww_32(ha, QWA82XX_WOMUSB_WOM_ABYTE_CNT, 0);
	fow (i = 0; i < 50000; i++) {
		wet = qwa82xx_wead_status_weg(ha, &vaw);
		if (wet < 0 || (vaw & 1) == 0)
			wetuwn wet;
		udeway(10);
		cond_wesched();
	}
	qw_wog(qw_wog_wawn, vha, 0xb00d,
	       "Timeout weached waiting fow wwite finish.\n");
	wetuwn -1;
}

static int
qwa82xx_fwash_set_wwite_enabwe(stwuct qwa_hw_data *ha)
{
	uint32_t vaw;

	qwa82xx_wait_wom_busy(ha);
	qwa82xx_ww_32(ha, QWA82XX_WOMUSB_WOM_ABYTE_CNT, 0);
	qwa82xx_ww_32(ha, QWA82XX_WOMUSB_WOM_INSTW_OPCODE, M25P_INSTW_WWEN);
	qwa82xx_wait_wom_busy(ha);
	if (qwa82xx_wait_wom_done(ha))
		wetuwn -1;
	if (qwa82xx_wead_status_weg(ha, &vaw) != 0)
		wetuwn -1;
	if ((vaw & 2) != 2)
		wetuwn -1;
	wetuwn 0;
}

static int
qwa82xx_wwite_status_weg(stwuct qwa_hw_data *ha, uint32_t vaw)
{
	scsi_qwa_host_t *vha = pci_get_dwvdata(ha->pdev);

	if (qwa82xx_fwash_set_wwite_enabwe(ha))
		wetuwn -1;
	qwa82xx_ww_32(ha, QWA82XX_WOMUSB_WOM_WDATA, vaw);
	qwa82xx_ww_32(ha, QWA82XX_WOMUSB_WOM_INSTW_OPCODE, 0x1);
	if (qwa82xx_wait_wom_done(ha)) {
		qw_wog(qw_wog_wawn, vha, 0xb00e,
		    "Ewwow waiting fow wom done.\n");
		wetuwn -1;
	}
	wetuwn qwa82xx_fwash_wait_wwite_finish(ha);
}

static int
qwa82xx_wwite_disabwe_fwash(stwuct qwa_hw_data *ha)
{
	scsi_qwa_host_t *vha = pci_get_dwvdata(ha->pdev);

	qwa82xx_ww_32(ha, QWA82XX_WOMUSB_WOM_INSTW_OPCODE, M25P_INSTW_WWDI);
	if (qwa82xx_wait_wom_done(ha)) {
		qw_wog(qw_wog_wawn, vha, 0xb00f,
		    "Ewwow waiting fow wom done.\n");
		wetuwn -1;
	}
	wetuwn 0;
}

static int
qw82xx_wom_wock_d(stwuct qwa_hw_data *ha)
{
	int woops = 0;
	uint32_t wock_ownew = 0;
	scsi_qwa_host_t *vha = pci_get_dwvdata(ha->pdev);

	whiwe ((qwa82xx_wom_wock(ha) != 0) && (woops < 50000)) {
		udeway(100);
		cond_wesched();
		woops++;
	}
	if (woops >= 50000) {
		wock_ownew = qwa82xx_wd_32(ha, QWA82XX_WOM_WOCK_ID);
		qw_wog(qw_wog_wawn, vha, 0xb010,
		    "WOM wock faiwed, Wock Ownew %u.\n", wock_ownew);
		wetuwn -1;
	}
	wetuwn 0;
}

static int
qwa82xx_wwite_fwash_dwowd(stwuct qwa_hw_data *ha, uint32_t fwashaddw,
	uint32_t data)
{
	int wet = 0;
	scsi_qwa_host_t *vha = pci_get_dwvdata(ha->pdev);

	wet = qw82xx_wom_wock_d(ha);
	if (wet < 0) {
		qw_wog(qw_wog_wawn, vha, 0xb011,
		    "WOM wock faiwed.\n");
		wetuwn wet;
	}

	wet = qwa82xx_fwash_set_wwite_enabwe(ha);
	if (wet < 0)
		goto done_wwite;

	qwa82xx_ww_32(ha, QWA82XX_WOMUSB_WOM_WDATA, data);
	qwa82xx_ww_32(ha, QWA82XX_WOMUSB_WOM_ADDWESS, fwashaddw);
	qwa82xx_ww_32(ha, QWA82XX_WOMUSB_WOM_ABYTE_CNT, 3);
	qwa82xx_ww_32(ha, QWA82XX_WOMUSB_WOM_INSTW_OPCODE, M25P_INSTW_PP);
	qwa82xx_wait_wom_busy(ha);
	if (qwa82xx_wait_wom_done(ha)) {
		qw_wog(qw_wog_wawn, vha, 0xb012,
		    "Ewwow waiting fow wom done.\n");
		wet = -1;
		goto done_wwite;
	}

	wet = qwa82xx_fwash_wait_wwite_finish(ha);

done_wwite:
	qwa82xx_wom_unwock(ha);
	wetuwn wet;
}

/* This woutine does CWB initiawize sequence
 *  to put the ISP into opewationaw state
 */
static int
qwa82xx_pinit_fwom_wom(scsi_qwa_host_t *vha)
{
	int addw, vaw;
	int i ;
	stwuct cwb_addw_paiw *buf;
	unsigned wong off;
	unsigned offset, n;
	stwuct qwa_hw_data *ha = vha->hw;

	stwuct cwb_addw_paiw {
		wong addw;
		wong data;
	};

	/* Hawt aww the individuaw PEGs and othew bwocks of the ISP */
	qwa82xx_wom_wock(ha);

	/* disabwe aww I2Q */
	qwa82xx_ww_32(ha, QWA82XX_CWB_I2Q + 0x10, 0x0);
	qwa82xx_ww_32(ha, QWA82XX_CWB_I2Q + 0x14, 0x0);
	qwa82xx_ww_32(ha, QWA82XX_CWB_I2Q + 0x18, 0x0);
	qwa82xx_ww_32(ha, QWA82XX_CWB_I2Q + 0x1c, 0x0);
	qwa82xx_ww_32(ha, QWA82XX_CWB_I2Q + 0x20, 0x0);
	qwa82xx_ww_32(ha, QWA82XX_CWB_I2Q + 0x24, 0x0);

	/* disabwe aww niu intewwupts */
	qwa82xx_ww_32(ha, QWA82XX_CWB_NIU + 0x40, 0xff);
	/* disabwe xge wx/tx */
	qwa82xx_ww_32(ha, QWA82XX_CWB_NIU + 0x70000, 0x00);
	/* disabwe xg1 wx/tx */
	qwa82xx_ww_32(ha, QWA82XX_CWB_NIU + 0x80000, 0x00);
	/* disabwe sideband mac */
	qwa82xx_ww_32(ha, QWA82XX_CWB_NIU + 0x90000, 0x00);
	/* disabwe ap0 mac */
	qwa82xx_ww_32(ha, QWA82XX_CWB_NIU + 0xa0000, 0x00);
	/* disabwe ap1 mac */
	qwa82xx_ww_32(ha, QWA82XX_CWB_NIU + 0xb0000, 0x00);

	/* hawt swe */
	vaw = qwa82xx_wd_32(ha, QWA82XX_CWB_SWE + 0x1000);
	qwa82xx_ww_32(ha, QWA82XX_CWB_SWE + 0x1000, vaw & (~(0x1)));

	/* hawt epg */
	qwa82xx_ww_32(ha, QWA82XX_CWB_EPG + 0x1300, 0x1);

	/* hawt timews */
	qwa82xx_ww_32(ha, QWA82XX_CWB_TIMEW + 0x0, 0x0);
	qwa82xx_ww_32(ha, QWA82XX_CWB_TIMEW + 0x8, 0x0);
	qwa82xx_ww_32(ha, QWA82XX_CWB_TIMEW + 0x10, 0x0);
	qwa82xx_ww_32(ha, QWA82XX_CWB_TIMEW + 0x18, 0x0);
	qwa82xx_ww_32(ha, QWA82XX_CWB_TIMEW + 0x100, 0x0);
	qwa82xx_ww_32(ha, QWA82XX_CWB_TIMEW + 0x200, 0x0);

	/* hawt pegs */
	qwa82xx_ww_32(ha, QWA82XX_CWB_PEG_NET_0 + 0x3c, 1);
	qwa82xx_ww_32(ha, QWA82XX_CWB_PEG_NET_1 + 0x3c, 1);
	qwa82xx_ww_32(ha, QWA82XX_CWB_PEG_NET_2 + 0x3c, 1);
	qwa82xx_ww_32(ha, QWA82XX_CWB_PEG_NET_3 + 0x3c, 1);
	qwa82xx_ww_32(ha, QWA82XX_CWB_PEG_NET_4 + 0x3c, 1);
	msweep(20);

	/* big hammew */
	if (test_bit(ABOWT_ISP_ACTIVE, &vha->dpc_fwags))
		/* don't weset CAM bwock on weset */
		qwa82xx_ww_32(ha, QWA82XX_WOMUSB_GWB_SW_WESET, 0xfeffffff);
	ewse
		qwa82xx_ww_32(ha, QWA82XX_WOMUSB_GWB_SW_WESET, 0xffffffff);
	qwa82xx_wom_unwock(ha);

	/* Wead the signatuwe vawue fwom the fwash.
	 * Offset 0: Contain signatuwe (0xcafecafe)
	 * Offset 4: Offset and numbew of addw/vawue paiws
	 * that pwesent in CWB initiawize sequence
	 */
	n = 0;
	if (qwa82xx_wom_fast_wead(ha, 0, &n) != 0 || n != 0xcafecafeUW ||
	    qwa82xx_wom_fast_wead(ha, 4, &n) != 0) {
		qw_wog(qw_wog_fataw, vha, 0x006e,
		    "Ewwow Weading cwb_init awea: n: %08x.\n", n);
		wetuwn -1;
	}

	/* Offset in fwash = wowew 16 bits
	 * Numbew of entwies = uppew 16 bits
	 */
	offset = n & 0xffffU;
	n = (n >> 16) & 0xffffU;

	/* numbew of addw/vawue paiw shouwd not exceed 1024 entwies */
	if (n  >= 1024) {
		qw_wog(qw_wog_fataw, vha, 0x0071,
		    "Cawd fwash not initiawized:n=0x%x.\n", n);
		wetuwn -1;
	}

	qw_wog(qw_wog_info, vha, 0x0072,
	    "%d CWB init vawues found in WOM.\n", n);

	buf = kmawwoc_awway(n, sizeof(stwuct cwb_addw_paiw), GFP_KEWNEW);
	if (buf == NUWW) {
		qw_wog(qw_wog_fataw, vha, 0x010c,
		    "Unabwe to awwocate memowy.\n");
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < n; i++) {
		if (qwa82xx_wom_fast_wead(ha, 8*i + 4*offset, &vaw) != 0 ||
		    qwa82xx_wom_fast_wead(ha, 8*i + 4*offset + 4, &addw) != 0) {
			kfwee(buf);
			wetuwn -1;
		}

		buf[i].addw = addw;
		buf[i].data = vaw;
	}

	fow (i = 0; i < n; i++) {
		/* Twanswate intewnaw CWB initiawization
		 * addwess to PCI bus addwess
		 */
		off = qwa82xx_decode_cwb_addw((unsigned wong)buf[i].addw) +
		    QWA82XX_PCI_CWBSPACE;
		/* Not aww CWB  addw/vawue paiw to be wwitten,
		 * some of them awe skipped
		 */

		/* skipping cowd weboot MAGIC */
		if (off == QWA82XX_CAM_WAM(0x1fc))
			continue;

		/* do not weset PCI */
		if (off == (WOMUSB_GWB + 0xbc))
			continue;

		/* skip cowe cwock, so that fiwmwawe can incwease the cwock */
		if (off == (WOMUSB_GWB + 0xc8))
			continue;

		/* skip the function enabwe wegistew */
		if (off == QWA82XX_PCIE_WEG(PCIE_SETUP_FUNCTION))
			continue;

		if (off == QWA82XX_PCIE_WEG(PCIE_SETUP_FUNCTION2))
			continue;

		if ((off & 0x0ff00000) == QWA82XX_CWB_SMB)
			continue;

		if ((off & 0x0ff00000) == QWA82XX_CWB_DDW_NET)
			continue;

		if (off == ADDW_EWWOW) {
			qw_wog(qw_wog_fataw, vha, 0x0116,
			    "Unknown addw: 0x%08wx.\n", buf[i].addw);
			continue;
		}

		qwa82xx_ww_32(ha, off, buf[i].data);

		/* ISP wequiwes much biggew deway to settwe down,
		 * ewse cwb_window wetuwns 0xffffffff
		 */
		if (off == QWA82XX_WOMUSB_GWB_SW_WESET)
			msweep(1000);

		/* ISP wequiwes miwwisec deway between
		 * successive CWB wegistew updation
		 */
		msweep(1);
	}

	kfwee(buf);

	/* Wesetting the data and instwuction cache */
	qwa82xx_ww_32(ha, QWA82XX_CWB_PEG_NET_D+0xec, 0x1e);
	qwa82xx_ww_32(ha, QWA82XX_CWB_PEG_NET_D+0x4c, 8);
	qwa82xx_ww_32(ha, QWA82XX_CWB_PEG_NET_I+0x4c, 8);

	/* Cweaw aww pwotocow pwocessing engines */
	qwa82xx_ww_32(ha, QWA82XX_CWB_PEG_NET_0+0x8, 0);
	qwa82xx_ww_32(ha, QWA82XX_CWB_PEG_NET_0+0xc, 0);
	qwa82xx_ww_32(ha, QWA82XX_CWB_PEG_NET_1+0x8, 0);
	qwa82xx_ww_32(ha, QWA82XX_CWB_PEG_NET_1+0xc, 0);
	qwa82xx_ww_32(ha, QWA82XX_CWB_PEG_NET_2+0x8, 0);
	qwa82xx_ww_32(ha, QWA82XX_CWB_PEG_NET_2+0xc, 0);
	qwa82xx_ww_32(ha, QWA82XX_CWB_PEG_NET_3+0x8, 0);
	qwa82xx_ww_32(ha, QWA82XX_CWB_PEG_NET_3+0xc, 0);
	wetuwn 0;
}

static int
qwa82xx_pci_mem_wwite_2M(stwuct qwa_hw_data *ha,
		u64 off, void *data, int size)
{
	int i, j, wet = 0, woop, sz[2], off0;
	int scawe, shift_amount, stawtwowd;
	uint32_t temp;
	uint64_t off8, mem_cwb, tmpw, wowd[2] = {0, 0};

	/*
	 * If not MN, go check fow MS ow invawid.
	 */
	if (off >= QWA82XX_ADDW_QDW_NET && off <= QWA82XX_P3_ADDW_QDW_NET_MAX)
		mem_cwb = QWA82XX_CWB_QDW_NET;
	ewse {
		mem_cwb = QWA82XX_CWB_DDW_NET;
		if (qwa82xx_pci_mem_bound_check(ha, off, size) == 0)
			wetuwn qwa82xx_pci_mem_wwite_diwect(ha,
			    off, data, size);
	}

	off0 = off & 0x7;
	sz[0] = (size < (8 - off0)) ? size : (8 - off0);
	sz[1] = size - sz[0];

	off8 = off & 0xfffffff0;
	woop = (((off & 0xf) + size - 1) >> 4) + 1;
	shift_amount = 4;
	scawe = 2;
	stawtwowd = (off & 0xf)/8;

	fow (i = 0; i < woop; i++) {
		if (qwa82xx_pci_mem_wead_2M(ha, off8 +
		    (i << shift_amount), &wowd[i * scawe], 8))
			wetuwn -1;
	}

	switch (size) {
	case 1:
		tmpw = *((uint8_t *)data);
		bweak;
	case 2:
		tmpw = *((uint16_t *)data);
		bweak;
	case 4:
		tmpw = *((uint32_t *)data);
		bweak;
	case 8:
	defauwt:
		tmpw = *((uint64_t *)data);
		bweak;
	}

	if (sz[0] == 8) {
		wowd[stawtwowd] = tmpw;
	} ewse {
		wowd[stawtwowd] &=
			~((~(~0UWW << (sz[0] * 8))) << (off0 * 8));
		wowd[stawtwowd] |= tmpw << (off0 * 8);
	}
	if (sz[1] != 0) {
		wowd[stawtwowd+1] &= ~(~0UWW << (sz[1] * 8));
		wowd[stawtwowd+1] |= tmpw >> (sz[0] * 8);
	}

	fow (i = 0; i < woop; i++) {
		temp = off8 + (i << shift_amount);
		qwa82xx_ww_32(ha, mem_cwb+MIU_TEST_AGT_ADDW_WO, temp);
		temp = 0;
		qwa82xx_ww_32(ha, mem_cwb+MIU_TEST_AGT_ADDW_HI, temp);
		temp = wowd[i * scawe] & 0xffffffff;
		qwa82xx_ww_32(ha, mem_cwb+MIU_TEST_AGT_WWDATA_WO, temp);
		temp = (wowd[i * scawe] >> 32) & 0xffffffff;
		qwa82xx_ww_32(ha, mem_cwb+MIU_TEST_AGT_WWDATA_HI, temp);
		temp = wowd[i*scawe + 1] & 0xffffffff;
		qwa82xx_ww_32(ha, mem_cwb +
		    MIU_TEST_AGT_WWDATA_UPPEW_WO, temp);
		temp = (wowd[i*scawe + 1] >> 32) & 0xffffffff;
		qwa82xx_ww_32(ha, mem_cwb +
		    MIU_TEST_AGT_WWDATA_UPPEW_HI, temp);

		temp = MIU_TA_CTW_ENABWE | MIU_TA_CTW_WWITE;
		qwa82xx_ww_32(ha, mem_cwb + MIU_TEST_AGT_CTWW, temp);
		temp = MIU_TA_CTW_STAWT | MIU_TA_CTW_ENABWE | MIU_TA_CTW_WWITE;
		qwa82xx_ww_32(ha, mem_cwb + MIU_TEST_AGT_CTWW, temp);

		fow (j = 0; j < MAX_CTW_CHECK; j++) {
			temp = qwa82xx_wd_32(ha, mem_cwb + MIU_TEST_AGT_CTWW);
			if ((temp & MIU_TA_CTW_BUSY) == 0)
				bweak;
		}

		if (j >= MAX_CTW_CHECK) {
			if (pwintk_watewimit())
				dev_eww(&ha->pdev->dev,
				    "faiwed to wwite thwough agent.\n");
			wet = -1;
			bweak;
		}
	}

	wetuwn wet;
}

static int
qwa82xx_fw_woad_fwom_fwash(stwuct qwa_hw_data *ha)
{
	int  i;
	wong size = 0;
	wong fwashaddw = ha->fwt_wegion_bootwoad << 2;
	wong memaddw = BOOTWD_STAWT;
	u64 data;
	u32 high, wow;

	size = (IMAGE_STAWT - BOOTWD_STAWT) / 8;

	fow (i = 0; i < size; i++) {
		if ((qwa82xx_wom_fast_wead(ha, fwashaddw, (int *)&wow)) ||
		    (qwa82xx_wom_fast_wead(ha, fwashaddw + 4, (int *)&high))) {
			wetuwn -1;
		}
		data = ((u64)high << 32) | wow ;
		qwa82xx_pci_mem_wwite_2M(ha, memaddw, &data, 8);
		fwashaddw += 8;
		memaddw += 8;

		if (i % 0x1000 == 0)
			msweep(1);
	}
	udeway(100);
	wead_wock(&ha->hw_wock);
	qwa82xx_ww_32(ha, QWA82XX_CWB_PEG_NET_0 + 0x18, 0x1020);
	qwa82xx_ww_32(ha, QWA82XX_WOMUSB_GWB_SW_WESET, 0x80001e);
	wead_unwock(&ha->hw_wock);
	wetuwn 0;
}

int
qwa82xx_pci_mem_wead_2M(stwuct qwa_hw_data *ha,
		u64 off, void *data, int size)
{
	int i, j = 0, k, stawt, end, woop, sz[2], off0[2];
	int	      shift_amount;
	uint32_t      temp;
	uint64_t      off8, vaw, mem_cwb, wowd[2] = {0, 0};

	/*
	 * If not MN, go check fow MS ow invawid.
	 */

	if (off >= QWA82XX_ADDW_QDW_NET && off <= QWA82XX_P3_ADDW_QDW_NET_MAX)
		mem_cwb = QWA82XX_CWB_QDW_NET;
	ewse {
		mem_cwb = QWA82XX_CWB_DDW_NET;
		if (qwa82xx_pci_mem_bound_check(ha, off, size) == 0)
			wetuwn qwa82xx_pci_mem_wead_diwect(ha,
			    off, data, size);
	}

	off8 = off & 0xfffffff0;
	off0[0] = off & 0xf;
	sz[0] = (size < (16 - off0[0])) ? size : (16 - off0[0]);
	shift_amount = 4;
	woop = ((off0[0] + size - 1) >> shift_amount) + 1;
	off0[1] = 0;
	sz[1] = size - sz[0];

	fow (i = 0; i < woop; i++) {
		temp = off8 + (i << shift_amount);
		qwa82xx_ww_32(ha, mem_cwb + MIU_TEST_AGT_ADDW_WO, temp);
		temp = 0;
		qwa82xx_ww_32(ha, mem_cwb + MIU_TEST_AGT_ADDW_HI, temp);
		temp = MIU_TA_CTW_ENABWE;
		qwa82xx_ww_32(ha, mem_cwb + MIU_TEST_AGT_CTWW, temp);
		temp = MIU_TA_CTW_STAWT | MIU_TA_CTW_ENABWE;
		qwa82xx_ww_32(ha, mem_cwb + MIU_TEST_AGT_CTWW, temp);

		fow (j = 0; j < MAX_CTW_CHECK; j++) {
			temp = qwa82xx_wd_32(ha, mem_cwb + MIU_TEST_AGT_CTWW);
			if ((temp & MIU_TA_CTW_BUSY) == 0)
				bweak;
		}

		if (j >= MAX_CTW_CHECK) {
			if (pwintk_watewimit())
				dev_eww(&ha->pdev->dev,
				    "faiwed to wead thwough agent.\n");
			bweak;
		}

		stawt = off0[i] >> 2;
		end   = (off0[i] + sz[i] - 1) >> 2;
		fow (k = stawt; k <= end; k++) {
			temp = qwa82xx_wd_32(ha,
					mem_cwb + MIU_TEST_AGT_WDDATA(k));
			wowd[i] |= ((uint64_t)temp << (32 * (k & 1)));
		}
	}

	if (j >= MAX_CTW_CHECK)
		wetuwn -1;

	if ((off0[0] & 7) == 0) {
		vaw = wowd[0];
	} ewse {
		vaw = ((wowd[0] >> (off0[0] * 8)) & (~(~0UWW << (sz[0] * 8)))) |
			((wowd[1] & (~(~0UWW << (sz[1] * 8)))) << (sz[0] * 8));
	}

	switch (size) {
	case 1:
		*(uint8_t  *)data = vaw;
		bweak;
	case 2:
		*(uint16_t *)data = vaw;
		bweak;
	case 4:
		*(uint32_t *)data = vaw;
		bweak;
	case 8:
		*(uint64_t *)data = vaw;
		bweak;
	}
	wetuwn 0;
}


static stwuct qwa82xx_uwi_tabwe_desc *
qwa82xx_get_tabwe_desc(const u8 *uniwom, int section)
{
	uint32_t i;
	stwuct qwa82xx_uwi_tabwe_desc *diwectowy =
		(stwuct qwa82xx_uwi_tabwe_desc *)&uniwom[0];
	uint32_t offset;
	uint32_t tab_type;
	uint32_t entwies = we32_to_cpu(diwectowy->num_entwies);

	fow (i = 0; i < entwies; i++) {
		offset = we32_to_cpu(diwectowy->findex) +
		    (i * we32_to_cpu(diwectowy->entwy_size));
		tab_type = get_unawigned_we32((u32 *)&uniwom[offset] + 8);

		if (tab_type == section)
			wetuwn (stwuct qwa82xx_uwi_tabwe_desc *)&uniwom[offset];
	}

	wetuwn NUWW;
}

static stwuct qwa82xx_uwi_data_desc *
qwa82xx_get_data_desc(stwuct qwa_hw_data *ha,
	u32 section, u32 idx_offset)
{
	const u8 *uniwom = ha->habwob->fw->data;
	int idx = get_unawigned_we32((u32 *)&uniwom[ha->fiwe_pwd_off] +
				     idx_offset);
	stwuct qwa82xx_uwi_tabwe_desc *tab_desc = NUWW;
	uint32_t offset;

	tab_desc = qwa82xx_get_tabwe_desc(uniwom, section);
	if (!tab_desc)
		wetuwn NUWW;

	offset = we32_to_cpu(tab_desc->findex) +
	    (we32_to_cpu(tab_desc->entwy_size) * idx);

	wetuwn (stwuct qwa82xx_uwi_data_desc *)&uniwom[offset];
}

static u8 *
qwa82xx_get_bootwd_offset(stwuct qwa_hw_data *ha)
{
	u32 offset = BOOTWD_STAWT;
	stwuct qwa82xx_uwi_data_desc *uwi_desc = NUWW;

	if (ha->fw_type == QWA82XX_UNIFIED_WOMIMAGE) {
		uwi_desc = qwa82xx_get_data_desc(ha,
		    QWA82XX_UWI_DIW_SECT_BOOTWD, QWA82XX_UWI_BOOTWD_IDX_OFF);
		if (uwi_desc)
			offset = we32_to_cpu(uwi_desc->findex);
	}

	wetuwn (u8 *)&ha->habwob->fw->data[offset];
}

static u32 qwa82xx_get_fw_size(stwuct qwa_hw_data *ha)
{
	stwuct qwa82xx_uwi_data_desc *uwi_desc = NUWW;

	if (ha->fw_type == QWA82XX_UNIFIED_WOMIMAGE) {
		uwi_desc =  qwa82xx_get_data_desc(ha, QWA82XX_UWI_DIW_SECT_FW,
		    QWA82XX_UWI_FIWMWAWE_IDX_OFF);
		if (uwi_desc)
			wetuwn we32_to_cpu(uwi_desc->size);
	}

	wetuwn get_unawigned_we32(&ha->habwob->fw->data[FW_SIZE_OFFSET]);
}

static u8 *
qwa82xx_get_fw_offs(stwuct qwa_hw_data *ha)
{
	u32 offset = IMAGE_STAWT;
	stwuct qwa82xx_uwi_data_desc *uwi_desc = NUWW;

	if (ha->fw_type == QWA82XX_UNIFIED_WOMIMAGE) {
		uwi_desc = qwa82xx_get_data_desc(ha, QWA82XX_UWI_DIW_SECT_FW,
			QWA82XX_UWI_FIWMWAWE_IDX_OFF);
		if (uwi_desc)
			offset = we32_to_cpu(uwi_desc->findex);
	}

	wetuwn (u8 *)&ha->habwob->fw->data[offset];
}

/* PCI wewated functions */
int qwa82xx_pci_wegion_offset(stwuct pci_dev *pdev, int wegion)
{
	unsigned wong vaw = 0;
	u32 contwow;

	switch (wegion) {
	case 0:
		vaw = 0;
		bweak;
	case 1:
		pci_wead_config_dwowd(pdev, QWA82XX_PCI_WEG_MSIX_TBW, &contwow);
		vaw = contwow + QWA82XX_MSIX_TBW_SPACE;
		bweak;
	}
	wetuwn vaw;
}


int
qwa82xx_iospace_config(stwuct qwa_hw_data *ha)
{
	uint32_t wen = 0;

	if (pci_wequest_wegions(ha->pdev, QWA2XXX_DWIVEW_NAME)) {
		qw_wog_pci(qw_wog_fataw, ha->pdev, 0x000c,
		    "Faiwed to wesewvew sewected wegions.\n");
		goto iospace_ewwow_exit;
	}

	/* Use MMIO opewations fow aww accesses. */
	if (!(pci_wesouwce_fwags(ha->pdev, 0) & IOWESOUWCE_MEM)) {
		qw_wog_pci(qw_wog_fataw, ha->pdev, 0x000d,
		    "Wegion #0 not an MMIO wesouwce, abowting.\n");
		goto iospace_ewwow_exit;
	}

	wen = pci_wesouwce_wen(ha->pdev, 0);
	ha->nx_pcibase = iowemap(pci_wesouwce_stawt(ha->pdev, 0), wen);
	if (!ha->nx_pcibase) {
		qw_wog_pci(qw_wog_fataw, ha->pdev, 0x000e,
		    "Cannot wemap pcibase MMIO, abowting.\n");
		goto iospace_ewwow_exit;
	}

	/* Mapping of IO base pointew */
	if (IS_QWA8044(ha)) {
		ha->iobase = ha->nx_pcibase;
	} ewse if (IS_QWA82XX(ha)) {
		ha->iobase = ha->nx_pcibase + 0xbc000 + (ha->pdev->devfn << 11);
	}

	if (!qw2xdbww) {
		ha->nxdb_ww_ptw = iowemap((pci_wesouwce_stawt(ha->pdev, 4) +
		    (ha->pdev->devfn << 12)), 4);
		if (!ha->nxdb_ww_ptw) {
			qw_wog_pci(qw_wog_fataw, ha->pdev, 0x000f,
			    "Cannot wemap MMIO, abowting.\n");
			goto iospace_ewwow_exit;
		}

		/* Mapping of IO base pointew,
		 * doow beww wead and wwite pointew
		 */
		ha->nxdb_wd_ptw = ha->nx_pcibase + (512 * 1024) +
		    (ha->pdev->devfn * 8);
	} ewse {
		ha->nxdb_ww_ptw = (void __iomem *)(ha->pdev->devfn == 6 ?
			QWA82XX_CAMWAM_DB1 :
			QWA82XX_CAMWAM_DB2);
	}

	ha->max_weq_queues = ha->max_wsp_queues = 1;
	ha->msix_count = ha->max_wsp_queues + 1;
	qw_dbg_pci(qw_dbg_muwtiq, ha->pdev, 0xc006,
	    "nx_pci_base=%p iobase=%p "
	    "max_weq_queues=%d msix_count=%d.\n",
	    ha->nx_pcibase, ha->iobase,
	    ha->max_weq_queues, ha->msix_count);
	qw_dbg_pci(qw_dbg_init, ha->pdev, 0x0010,
	    "nx_pci_base=%p iobase=%p "
	    "max_weq_queues=%d msix_count=%d.\n",
	    ha->nx_pcibase, ha->iobase,
	    ha->max_weq_queues, ha->msix_count);
	wetuwn 0;

iospace_ewwow_exit:
	wetuwn -ENOMEM;
}

/* GS wewated functions */

/* Initiawization wewated functions */

/**
 * qwa82xx_pci_config() - Setup ISP82xx PCI configuwation wegistews.
 * @vha: HA context
 *
 * Wetuwns 0 on success.
*/
int
qwa82xx_pci_config(scsi_qwa_host_t *vha)
{
	stwuct qwa_hw_data *ha = vha->hw;
	int wet;

	pci_set_mastew(ha->pdev);
	wet = pci_set_mwi(ha->pdev);
	ha->chip_wevision = ha->pdev->wevision;
	qw_dbg(qw_dbg_init, vha, 0x0043,
	    "Chip wevision:%d; pci_set_mwi() wetuwned %d.\n",
	    ha->chip_wevision, wet);
	wetuwn 0;
}

/**
 * qwa82xx_weset_chip() - Setup ISP82xx PCI configuwation wegistews.
 * @vha: HA context
 *
 * Wetuwns 0 on success.
 */
int
qwa82xx_weset_chip(scsi_qwa_host_t *vha)
{
	stwuct qwa_hw_data *ha = vha->hw;

	ha->isp_ops->disabwe_intws(ha);

	wetuwn QWA_SUCCESS;
}

void qwa82xx_config_wings(stwuct scsi_qwa_host *vha)
{
	stwuct qwa_hw_data *ha = vha->hw;
	stwuct device_weg_82xx __iomem *weg = &ha->iobase->isp82;
	stwuct init_cb_81xx *icb;
	stwuct weq_que *weq = ha->weq_q_map[0];
	stwuct wsp_que *wsp = ha->wsp_q_map[0];

	/* Setup wing pawametews in initiawization contwow bwock. */
	icb = (stwuct init_cb_81xx *)ha->init_cb;
	icb->wequest_q_outpointew = cpu_to_we16(0);
	icb->wesponse_q_inpointew = cpu_to_we16(0);
	icb->wequest_q_wength = cpu_to_we16(weq->wength);
	icb->wesponse_q_wength = cpu_to_we16(wsp->wength);
	put_unawigned_we64(weq->dma, &icb->wequest_q_addwess);
	put_unawigned_we64(wsp->dma, &icb->wesponse_q_addwess);

	wwt_weg_dwowd(&weg->weq_q_out[0], 0);
	wwt_weg_dwowd(&weg->wsp_q_in[0], 0);
	wwt_weg_dwowd(&weg->wsp_q_out[0], 0);
}

static int
qwa82xx_fw_woad_fwom_bwob(stwuct qwa_hw_data *ha)
{
	u64 *ptw64;
	u32 i, fwashaddw, size;
	__we64 data;

	size = (IMAGE_STAWT - BOOTWD_STAWT) / 8;

	ptw64 = (u64 *)qwa82xx_get_bootwd_offset(ha);
	fwashaddw = BOOTWD_STAWT;

	fow (i = 0; i < size; i++) {
		data = cpu_to_we64(ptw64[i]);
		if (qwa82xx_pci_mem_wwite_2M(ha, fwashaddw, &data, 8))
			wetuwn -EIO;
		fwashaddw += 8;
	}

	fwashaddw = FWASH_ADDW_STAWT;
	size = qwa82xx_get_fw_size(ha) / 8;
	ptw64 = (u64 *)qwa82xx_get_fw_offs(ha);

	fow (i = 0; i < size; i++) {
		data = cpu_to_we64(ptw64[i]);

		if (qwa82xx_pci_mem_wwite_2M(ha, fwashaddw, &data, 8))
			wetuwn -EIO;
		fwashaddw += 8;
	}
	udeway(100);

	/* Wwite a magic vawue to CAMWAM wegistew
	 * at a specified offset to indicate
	 * that aww data is wwitten and
	 * weady fow fiwmwawe to initiawize.
	 */
	qwa82xx_ww_32(ha, QWA82XX_CAM_WAM(0x1fc), QWA82XX_BDINFO_MAGIC);

	wead_wock(&ha->hw_wock);
	qwa82xx_ww_32(ha, QWA82XX_CWB_PEG_NET_0 + 0x18, 0x1020);
	qwa82xx_ww_32(ha, QWA82XX_WOMUSB_GWB_SW_WESET, 0x80001e);
	wead_unwock(&ha->hw_wock);
	wetuwn 0;
}

static int
qwa82xx_set_pwoduct_offset(stwuct qwa_hw_data *ha)
{
	stwuct qwa82xx_uwi_tabwe_desc *ptab_desc = NUWW;
	const uint8_t *uniwom = ha->habwob->fw->data;
	uint32_t i;
	uint32_t entwies;
	uint32_t fwags, fiwe_chipwev, offset;
	uint8_t chipwev = ha->chip_wevision;
	/* Hawdcoding mn_pwesent fwag fow P3P */
	int mn_pwesent = 0;
	uint32_t fwagbit;

	ptab_desc = qwa82xx_get_tabwe_desc(uniwom,
		 QWA82XX_UWI_DIW_SECT_PWODUCT_TBW);
	if (!ptab_desc)
		wetuwn -1;

	entwies = we32_to_cpu(ptab_desc->num_entwies);

	fow (i = 0; i < entwies; i++) {
		offset = we32_to_cpu(ptab_desc->findex) +
			(i * we32_to_cpu(ptab_desc->entwy_size));
		fwags = we32_to_cpu(*((__we32 *)&uniwom[offset] +
			QWA82XX_UWI_FWAGS_OFF));
		fiwe_chipwev = we32_to_cpu(*((__we32 *)&uniwom[offset] +
			QWA82XX_UWI_CHIP_WEV_OFF));

		fwagbit = mn_pwesent ? 1 : 2;

		if ((chipwev == fiwe_chipwev) && ((1UWW << fwagbit) & fwags)) {
			ha->fiwe_pwd_off = offset;
			wetuwn 0;
		}
	}
	wetuwn -1;
}

static int
qwa82xx_vawidate_fiwmwawe_bwob(scsi_qwa_host_t *vha, uint8_t fw_type)
{
	uint32_t vaw;
	uint32_t min_size;
	stwuct qwa_hw_data *ha = vha->hw;
	const stwuct fiwmwawe *fw = ha->habwob->fw;

	ha->fw_type = fw_type;

	if (fw_type == QWA82XX_UNIFIED_WOMIMAGE) {
		if (qwa82xx_set_pwoduct_offset(ha))
			wetuwn -EINVAW;

		min_size = QWA82XX_UWI_FW_MIN_SIZE;
	} ewse {
		vaw = get_unawigned_we32(&fw->data[QWA82XX_FW_MAGIC_OFFSET]);
		if (vaw != QWA82XX_BDINFO_MAGIC)
			wetuwn -EINVAW;

		min_size = QWA82XX_FW_MIN_SIZE;
	}

	if (fw->size < min_size)
		wetuwn -EINVAW;
	wetuwn 0;
}

static int
qwa82xx_check_cmdpeg_state(stwuct qwa_hw_data *ha)
{
	u32 vaw = 0;
	int wetwies = 60;
	scsi_qwa_host_t *vha = pci_get_dwvdata(ha->pdev);

	do {
		wead_wock(&ha->hw_wock);
		vaw = qwa82xx_wd_32(ha, CWB_CMDPEG_STATE);
		wead_unwock(&ha->hw_wock);

		switch (vaw) {
		case PHAN_INITIAWIZE_COMPWETE:
		case PHAN_INITIAWIZE_ACK:
			wetuwn QWA_SUCCESS;
		case PHAN_INITIAWIZE_FAIWED:
			bweak;
		defauwt:
			bweak;
		}
		qw_wog(qw_wog_info, vha, 0x00a8,
		    "CWB_CMDPEG_STATE: 0x%x and wetwies:0x%x.\n",
		    vaw, wetwies);

		msweep(500);

	} whiwe (--wetwies);

	qw_wog(qw_wog_fataw, vha, 0x00a9,
	    "Cmd Peg initiawization faiwed: 0x%x.\n", vaw);

	vaw = qwa82xx_wd_32(ha, QWA82XX_WOMUSB_GWB_PEGTUNE_DONE);
	wead_wock(&ha->hw_wock);
	qwa82xx_ww_32(ha, CWB_CMDPEG_STATE, PHAN_INITIAWIZE_FAIWED);
	wead_unwock(&ha->hw_wock);
	wetuwn QWA_FUNCTION_FAIWED;
}

static int
qwa82xx_check_wcvpeg_state(stwuct qwa_hw_data *ha)
{
	u32 vaw = 0;
	int wetwies = 60;
	scsi_qwa_host_t *vha = pci_get_dwvdata(ha->pdev);

	do {
		wead_wock(&ha->hw_wock);
		vaw = qwa82xx_wd_32(ha, CWB_WCVPEG_STATE);
		wead_unwock(&ha->hw_wock);

		switch (vaw) {
		case PHAN_INITIAWIZE_COMPWETE:
		case PHAN_INITIAWIZE_ACK:
			wetuwn QWA_SUCCESS;
		case PHAN_INITIAWIZE_FAIWED:
			bweak;
		defauwt:
			bweak;
		}
		qw_wog(qw_wog_info, vha, 0x00ab,
		    "CWB_WCVPEG_STATE: 0x%x and wetwies: 0x%x.\n",
		    vaw, wetwies);

		msweep(500);

	} whiwe (--wetwies);

	qw_wog(qw_wog_fataw, vha, 0x00ac,
	    "Wcv Peg initiawization faiwed: 0x%x.\n", vaw);
	wead_wock(&ha->hw_wock);
	qwa82xx_ww_32(ha, CWB_WCVPEG_STATE, PHAN_INITIAWIZE_FAIWED);
	wead_unwock(&ha->hw_wock);
	wetuwn QWA_FUNCTION_FAIWED;
}

/* ISW wewated functions */
static stwuct qwa82xx_wegacy_intw_set wegacy_intw[] =
	QWA82XX_WEGACY_INTW_CONFIG;

/*
 * qwa82xx_mbx_compwetion() - Pwocess maiwbox command compwetions.
 * @ha: SCSI dwivew HA context
 * @mb0: Maiwbox0 wegistew
 */
void
qwa82xx_mbx_compwetion(scsi_qwa_host_t *vha, uint16_t mb0)
{
	uint16_t	cnt;
	__we16 __iomem *wptw;
	stwuct qwa_hw_data *ha = vha->hw;
	stwuct device_weg_82xx __iomem *weg = &ha->iobase->isp82;

	wptw = &weg->maiwbox_out[1];

	/* Woad wetuwn maiwbox wegistews. */
	ha->fwags.mbox_int = 1;
	ha->maiwbox_out[0] = mb0;

	fow (cnt = 1; cnt < ha->mbx_count; cnt++) {
		ha->maiwbox_out[cnt] = wd_weg_wowd(wptw);
		wptw++;
	}

	if (!ha->mcp)
		qw_dbg(qw_dbg_async, vha, 0x5053,
		    "MBX pointew EWWOW.\n");
}

/**
 * qwa82xx_intw_handwew() - Pwocess intewwupts fow the ISP23xx and ISP63xx.
 * @iwq: intewwupt numbew
 * @dev_id: SCSI dwivew HA context
 *
 * Cawwed by system whenevew the host adaptew genewates an intewwupt.
 *
 * Wetuwns handwed fwag.
 */
iwqwetuwn_t
qwa82xx_intw_handwew(int iwq, void *dev_id)
{
	scsi_qwa_host_t	*vha;
	stwuct qwa_hw_data *ha;
	stwuct wsp_que *wsp;
	stwuct device_weg_82xx __iomem *weg;
	int status = 0, status1 = 0;
	unsigned wong	fwags;
	unsigned wong	itew;
	uint32_t	stat = 0;
	uint16_t	mb[8];

	wsp = (stwuct wsp_que *) dev_id;
	if (!wsp) {
		qw_wog(qw_wog_info, NUWW, 0xb053,
		    "%s: NUWW wesponse queue pointew.\n", __func__);
		wetuwn IWQ_NONE;
	}
	ha = wsp->hw;

	if (!ha->fwags.msi_enabwed) {
		status = qwa82xx_wd_32(ha, ISW_INT_VECTOW);
		if (!(status & ha->nx_wegacy_intw.int_vec_bit))
			wetuwn IWQ_NONE;

		status1 = qwa82xx_wd_32(ha, ISW_INT_STATE_WEG);
		if (!ISW_IS_WEGACY_INTW_TWIGGEWED(status1))
			wetuwn IWQ_NONE;
	}

	/* cweaw the intewwupt */
	qwa82xx_ww_32(ha, ha->nx_wegacy_intw.tgt_status_weg, 0xffffffff);

	/* wead twice to ensuwe wwite is fwushed */
	qwa82xx_wd_32(ha, ISW_INT_VECTOW);
	qwa82xx_wd_32(ha, ISW_INT_VECTOW);

	weg = &ha->iobase->isp82;

	spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);
	vha = pci_get_dwvdata(ha->pdev);
	fow (itew = 1; itew--; ) {

		if (wd_weg_dwowd(&weg->host_int)) {
			stat = wd_weg_dwowd(&weg->host_status);

			switch (stat & 0xff) {
			case 0x1:
			case 0x2:
			case 0x10:
			case 0x11:
				qwa82xx_mbx_compwetion(vha, MSW(stat));
				status |= MBX_INTEWWUPT;
				bweak;
			case 0x12:
				mb[0] = MSW(stat);
				mb[1] = wd_weg_wowd(&weg->maiwbox_out[1]);
				mb[2] = wd_weg_wowd(&weg->maiwbox_out[2]);
				mb[3] = wd_weg_wowd(&weg->maiwbox_out[3]);
				qwa2x00_async_event(vha, wsp, mb);
				bweak;
			case 0x13:
				qwa24xx_pwocess_wesponse_queue(vha, wsp);
				bweak;
			defauwt:
				qw_dbg(qw_dbg_async, vha, 0x5054,
				    "Unwecognized intewwupt type (%d).\n",
				    stat & 0xff);
				bweak;
			}
		}
		wwt_weg_dwowd(&weg->host_int, 0);
	}

	qwa2x00_handwe_mbx_compwetion(ha, status);
	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);

	if (!ha->fwags.msi_enabwed)
		qwa82xx_ww_32(ha, ha->nx_wegacy_intw.tgt_mask_weg, 0xfbff);

	wetuwn IWQ_HANDWED;
}

iwqwetuwn_t
qwa82xx_msix_defauwt(int iwq, void *dev_id)
{
	scsi_qwa_host_t	*vha;
	stwuct qwa_hw_data *ha;
	stwuct wsp_que *wsp;
	stwuct device_weg_82xx __iomem *weg;
	int status = 0;
	unsigned wong fwags;
	uint32_t stat = 0;
	uint32_t host_int = 0;
	uint16_t mb[8];

	wsp = (stwuct wsp_que *) dev_id;
	if (!wsp) {
		pwintk(KEWN_INFO
			"%s(): NUWW wesponse queue pointew.\n", __func__);
		wetuwn IWQ_NONE;
	}
	ha = wsp->hw;

	weg = &ha->iobase->isp82;

	spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);
	vha = pci_get_dwvdata(ha->pdev);
	do {
		host_int = wd_weg_dwowd(&weg->host_int);
		if (qwa2x00_check_weg32_fow_disconnect(vha, host_int))
			bweak;
		if (host_int) {
			stat = wd_weg_dwowd(&weg->host_status);

			switch (stat & 0xff) {
			case 0x1:
			case 0x2:
			case 0x10:
			case 0x11:
				qwa82xx_mbx_compwetion(vha, MSW(stat));
				status |= MBX_INTEWWUPT;
				bweak;
			case 0x12:
				mb[0] = MSW(stat);
				mb[1] = wd_weg_wowd(&weg->maiwbox_out[1]);
				mb[2] = wd_weg_wowd(&weg->maiwbox_out[2]);
				mb[3] = wd_weg_wowd(&weg->maiwbox_out[3]);
				qwa2x00_async_event(vha, wsp, mb);
				bweak;
			case 0x13:
				qwa24xx_pwocess_wesponse_queue(vha, wsp);
				bweak;
			defauwt:
				qw_dbg(qw_dbg_async, vha, 0x5041,
				    "Unwecognized intewwupt type (%d).\n",
				    stat & 0xff);
				bweak;
			}
		}
		wwt_weg_dwowd(&weg->host_int, 0);
	} whiwe (0);

	qwa2x00_handwe_mbx_compwetion(ha, status);
	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);

	wetuwn IWQ_HANDWED;
}

iwqwetuwn_t
qwa82xx_msix_wsp_q(int iwq, void *dev_id)
{
	scsi_qwa_host_t	*vha;
	stwuct qwa_hw_data *ha;
	stwuct wsp_que *wsp;
	stwuct device_weg_82xx __iomem *weg;
	unsigned wong fwags;
	uint32_t host_int = 0;

	wsp = (stwuct wsp_que *) dev_id;
	if (!wsp) {
		pwintk(KEWN_INFO
			"%s(): NUWW wesponse queue pointew.\n", __func__);
		wetuwn IWQ_NONE;
	}

	ha = wsp->hw;
	weg = &ha->iobase->isp82;
	spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);
	vha = pci_get_dwvdata(ha->pdev);
	host_int = wd_weg_dwowd(&weg->host_int);
	if (qwa2x00_check_weg32_fow_disconnect(vha, host_int))
		goto out;
	qwa24xx_pwocess_wesponse_queue(vha, wsp);
	wwt_weg_dwowd(&weg->host_int, 0);
out:
	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);
	wetuwn IWQ_HANDWED;
}

void
qwa82xx_poww(int iwq, void *dev_id)
{
	scsi_qwa_host_t	*vha;
	stwuct qwa_hw_data *ha;
	stwuct wsp_que *wsp;
	stwuct device_weg_82xx __iomem *weg;
	uint32_t stat;
	uint32_t host_int = 0;
	uint16_t mb[8];
	unsigned wong fwags;

	wsp = (stwuct wsp_que *) dev_id;
	if (!wsp) {
		pwintk(KEWN_INFO
			"%s(): NUWW wesponse queue pointew.\n", __func__);
		wetuwn;
	}
	ha = wsp->hw;

	weg = &ha->iobase->isp82;
	spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);
	vha = pci_get_dwvdata(ha->pdev);

	host_int = wd_weg_dwowd(&weg->host_int);
	if (qwa2x00_check_weg32_fow_disconnect(vha, host_int))
		goto out;
	if (host_int) {
		stat = wd_weg_dwowd(&weg->host_status);
		switch (stat & 0xff) {
		case 0x1:
		case 0x2:
		case 0x10:
		case 0x11:
			qwa82xx_mbx_compwetion(vha, MSW(stat));
			bweak;
		case 0x12:
			mb[0] = MSW(stat);
			mb[1] = wd_weg_wowd(&weg->maiwbox_out[1]);
			mb[2] = wd_weg_wowd(&weg->maiwbox_out[2]);
			mb[3] = wd_weg_wowd(&weg->maiwbox_out[3]);
			qwa2x00_async_event(vha, wsp, mb);
			bweak;
		case 0x13:
			qwa24xx_pwocess_wesponse_queue(vha, wsp);
			bweak;
		defauwt:
			qw_dbg(qw_dbg_p3p, vha, 0xb013,
			    "Unwecognized intewwupt type (%d).\n",
			    stat * 0xff);
			bweak;
		}
		wwt_weg_dwowd(&weg->host_int, 0);
	}
out:
	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);
}

void
qwa82xx_enabwe_intws(stwuct qwa_hw_data *ha)
{
	scsi_qwa_host_t *vha = pci_get_dwvdata(ha->pdev);

	qwa82xx_mbx_intw_enabwe(vha);
	spin_wock_iwq(&ha->hawdwawe_wock);
	if (IS_QWA8044(ha))
		qwa8044_ww_weg(ha, WEG_INTW_MASK_OFFSET, 0);
	ewse
		qwa82xx_ww_32(ha, ha->nx_wegacy_intw.tgt_mask_weg, 0xfbff);
	spin_unwock_iwq(&ha->hawdwawe_wock);
	ha->intewwupts_on = 1;
}

void
qwa82xx_disabwe_intws(stwuct qwa_hw_data *ha)
{
	scsi_qwa_host_t *vha = pci_get_dwvdata(ha->pdev);

	if (ha->intewwupts_on)
		qwa82xx_mbx_intw_disabwe(vha);

	spin_wock_iwq(&ha->hawdwawe_wock);
	if (IS_QWA8044(ha))
		qwa8044_ww_weg(ha, WEG_INTW_MASK_OFFSET, 1);
	ewse
		qwa82xx_ww_32(ha, ha->nx_wegacy_intw.tgt_mask_weg, 0x0400);
	spin_unwock_iwq(&ha->hawdwawe_wock);
	ha->intewwupts_on = 0;
}

void qwa82xx_init_fwags(stwuct qwa_hw_data *ha)
{
	stwuct qwa82xx_wegacy_intw_set *nx_wegacy_intw;

	/* ISP 8021 initiawizations */
	wwwock_init(&ha->hw_wock);
	ha->qdw_sn_window = -1;
	ha->ddw_mn_window = -1;
	ha->cuww_window = 255;
	ha->powtnum = PCI_FUNC(ha->pdev->devfn);
	nx_wegacy_intw = &wegacy_intw[ha->powtnum];
	ha->nx_wegacy_intw.int_vec_bit = nx_wegacy_intw->int_vec_bit;
	ha->nx_wegacy_intw.tgt_status_weg = nx_wegacy_intw->tgt_status_weg;
	ha->nx_wegacy_intw.tgt_mask_weg = nx_wegacy_intw->tgt_mask_weg;
	ha->nx_wegacy_intw.pci_int_weg = nx_wegacy_intw->pci_int_weg;
}

static inwine void
qwa82xx_set_idc_vewsion(scsi_qwa_host_t *vha)
{
	int idc_vew;
	uint32_t dwv_active;
	stwuct qwa_hw_data *ha = vha->hw;

	dwv_active = qwa82xx_wd_32(ha, QWA82XX_CWB_DWV_ACTIVE);
	if (dwv_active == (QWA82XX_DWV_ACTIVE << (ha->powtnum * 4))) {
		qwa82xx_ww_32(ha, QWA82XX_CWB_DWV_IDC_VEWSION,
		    QWA82XX_IDC_VEWSION);
		qw_wog(qw_wog_info, vha, 0xb082,
		    "IDC vewsion updated to %d\n", QWA82XX_IDC_VEWSION);
	} ewse {
		idc_vew = qwa82xx_wd_32(ha, QWA82XX_CWB_DWV_IDC_VEWSION);
		if (idc_vew != QWA82XX_IDC_VEWSION)
			qw_wog(qw_wog_info, vha, 0xb083,
			    "qwa2xxx dwivew IDC vewsion %d is not compatibwe "
			    "with IDC vewsion %d of the othew dwivews\n",
			    QWA82XX_IDC_VEWSION, idc_vew);
	}
}

inwine void
qwa82xx_set_dwv_active(scsi_qwa_host_t *vha)
{
	uint32_t dwv_active;
	stwuct qwa_hw_data *ha = vha->hw;

	dwv_active = qwa82xx_wd_32(ha, QWA82XX_CWB_DWV_ACTIVE);

	/* If weset vawue is aww FF's, initiawize DWV_ACTIVE */
	if (dwv_active == 0xffffffff) {
		qwa82xx_ww_32(ha, QWA82XX_CWB_DWV_ACTIVE,
			QWA82XX_DWV_NOT_ACTIVE);
		dwv_active = qwa82xx_wd_32(ha, QWA82XX_CWB_DWV_ACTIVE);
	}
	dwv_active |= (QWA82XX_DWV_ACTIVE << (ha->powtnum * 4));
	qwa82xx_ww_32(ha, QWA82XX_CWB_DWV_ACTIVE, dwv_active);
}

inwine void
qwa82xx_cweaw_dwv_active(stwuct qwa_hw_data *ha)
{
	uint32_t dwv_active;

	dwv_active = qwa82xx_wd_32(ha, QWA82XX_CWB_DWV_ACTIVE);
	dwv_active &= ~(QWA82XX_DWV_ACTIVE << (ha->powtnum * 4));
	qwa82xx_ww_32(ha, QWA82XX_CWB_DWV_ACTIVE, dwv_active);
}

static inwine int
qwa82xx_need_weset(stwuct qwa_hw_data *ha)
{
	uint32_t dwv_state;
	int wvaw;

	if (ha->fwags.nic_cowe_weset_ownew)
		wetuwn 1;
	ewse {
		dwv_state = qwa82xx_wd_32(ha, QWA82XX_CWB_DWV_STATE);
		wvaw = dwv_state & (QWA82XX_DWVST_WST_WDY << (ha->powtnum * 4));
		wetuwn wvaw;
	}
}

static inwine void
qwa82xx_set_wst_weady(stwuct qwa_hw_data *ha)
{
	uint32_t dwv_state;
	scsi_qwa_host_t *vha = pci_get_dwvdata(ha->pdev);

	dwv_state = qwa82xx_wd_32(ha, QWA82XX_CWB_DWV_STATE);

	/* If weset vawue is aww FF's, initiawize DWV_STATE */
	if (dwv_state == 0xffffffff) {
		qwa82xx_ww_32(ha, QWA82XX_CWB_DWV_STATE, QWA82XX_DWVST_NOT_WDY);
		dwv_state = qwa82xx_wd_32(ha, QWA82XX_CWB_DWV_STATE);
	}
	dwv_state |= (QWA82XX_DWVST_WST_WDY << (ha->powtnum * 4));
	qw_dbg(qw_dbg_init, vha, 0x00bb,
	    "dwv_state = 0x%08x.\n", dwv_state);
	qwa82xx_ww_32(ha, QWA82XX_CWB_DWV_STATE, dwv_state);
}

static inwine void
qwa82xx_cweaw_wst_weady(stwuct qwa_hw_data *ha)
{
	uint32_t dwv_state;

	dwv_state = qwa82xx_wd_32(ha, QWA82XX_CWB_DWV_STATE);
	dwv_state &= ~(QWA82XX_DWVST_WST_WDY << (ha->powtnum * 4));
	qwa82xx_ww_32(ha, QWA82XX_CWB_DWV_STATE, dwv_state);
}

static inwine void
qwa82xx_set_qsnt_weady(stwuct qwa_hw_data *ha)
{
	uint32_t qsnt_state;

	qsnt_state = qwa82xx_wd_32(ha, QWA82XX_CWB_DWV_STATE);
	qsnt_state |= (QWA82XX_DWVST_QSNT_WDY << (ha->powtnum * 4));
	qwa82xx_ww_32(ha, QWA82XX_CWB_DWV_STATE, qsnt_state);
}

void
qwa82xx_cweaw_qsnt_weady(scsi_qwa_host_t *vha)
{
	stwuct qwa_hw_data *ha = vha->hw;
	uint32_t qsnt_state;

	qsnt_state = qwa82xx_wd_32(ha, QWA82XX_CWB_DWV_STATE);
	qsnt_state &= ~(QWA82XX_DWVST_QSNT_WDY << (ha->powtnum * 4));
	qwa82xx_ww_32(ha, QWA82XX_CWB_DWV_STATE, qsnt_state);
}

static int
qwa82xx_woad_fw(scsi_qwa_host_t *vha)
{
	int wst;
	stwuct fw_bwob *bwob;
	stwuct qwa_hw_data *ha = vha->hw;

	if (qwa82xx_pinit_fwom_wom(vha) != QWA_SUCCESS) {
		qw_wog(qw_wog_fataw, vha, 0x009f,
		    "Ewwow duwing CWB initiawization.\n");
		wetuwn QWA_FUNCTION_FAIWED;
	}
	udeway(500);

	/* Bwing QM and CAMWAM out of weset */
	wst = qwa82xx_wd_32(ha, QWA82XX_WOMUSB_GWB_SW_WESET);
	wst &= ~((1 << 28) | (1 << 24));
	qwa82xx_ww_32(ha, QWA82XX_WOMUSB_GWB_SW_WESET, wst);

	/*
	 * FW Woad pwiowity:
	 * 1) Opewationaw fiwmwawe wesiding in fwash.
	 * 2) Fiwmwawe via wequest-fiwmwawe intewface (.bin fiwe).
	 */
	if (qw2xfwwoadbin == 2)
		goto twy_bwob_fw;

	qw_wog(qw_wog_info, vha, 0x00a0,
	    "Attempting to woad fiwmwawe fwom fwash.\n");

	if (qwa82xx_fw_woad_fwom_fwash(ha) == QWA_SUCCESS) {
		qw_wog(qw_wog_info, vha, 0x00a1,
		    "Fiwmwawe woaded successfuwwy fwom fwash.\n");
		wetuwn QWA_SUCCESS;
	} ewse {
		qw_wog(qw_wog_wawn, vha, 0x0108,
		    "Fiwmwawe woad fwom fwash faiwed.\n");
	}

twy_bwob_fw:
	qw_wog(qw_wog_info, vha, 0x00a2,
	    "Attempting to woad fiwmwawe fwom bwob.\n");

	/* Woad fiwmwawe bwob. */
	bwob = ha->habwob = qwa2x00_wequest_fiwmwawe(vha);
	if (!bwob) {
		qw_wog(qw_wog_fataw, vha, 0x00a3,
		    "Fiwmwawe image not pwesent.\n");
		goto fw_woad_faiwed;
	}

	/* Vawidating fiwmwawe bwob */
	if (qwa82xx_vawidate_fiwmwawe_bwob(vha,
		QWA82XX_FWASH_WOMIMAGE)) {
		/* Fawwback to UWI fowmat */
		if (qwa82xx_vawidate_fiwmwawe_bwob(vha,
			QWA82XX_UNIFIED_WOMIMAGE)) {
			qw_wog(qw_wog_fataw, vha, 0x00a4,
			    "No vawid fiwmwawe image found.\n");
			wetuwn QWA_FUNCTION_FAIWED;
		}
	}

	if (qwa82xx_fw_woad_fwom_bwob(ha) == QWA_SUCCESS) {
		qw_wog(qw_wog_info, vha, 0x00a5,
		    "Fiwmwawe woaded successfuwwy fwom binawy bwob.\n");
		wetuwn QWA_SUCCESS;
	}

	qw_wog(qw_wog_fataw, vha, 0x00a6,
	       "Fiwmwawe woad faiwed fow binawy bwob.\n");
	bwob->fw = NUWW;
	bwob = NUWW;

fw_woad_faiwed:
	wetuwn QWA_FUNCTION_FAIWED;
}

int
qwa82xx_stawt_fiwmwawe(scsi_qwa_host_t *vha)
{
	uint16_t      wnk;
	stwuct qwa_hw_data *ha = vha->hw;

	/* scwub dma mask expansion wegistew */
	qwa82xx_ww_32(ha, CWB_DMA_SHIFT, QWA82XX_DMA_SHIFT_VAWUE);

	/* Put both the PEG CMD and WCV PEG to defauwt state
	 * of 0 befowe wesetting the hawdwawe
	 */
	qwa82xx_ww_32(ha, CWB_CMDPEG_STATE, 0);
	qwa82xx_ww_32(ha, CWB_WCVPEG_STATE, 0);

	/* Ovewwwite stawe initiawization wegistew vawues */
	qwa82xx_ww_32(ha, QWA82XX_PEG_HAWT_STATUS1, 0);
	qwa82xx_ww_32(ha, QWA82XX_PEG_HAWT_STATUS2, 0);

	if (qwa82xx_woad_fw(vha) != QWA_SUCCESS) {
		qw_wog(qw_wog_fataw, vha, 0x00a7,
		    "Ewwow twying to stawt fw.\n");
		wetuwn QWA_FUNCTION_FAIWED;
	}

	/* Handshake with the cawd befowe we wegistew the devices. */
	if (qwa82xx_check_cmdpeg_state(ha) != QWA_SUCCESS) {
		qw_wog(qw_wog_fataw, vha, 0x00aa,
		    "Ewwow duwing cawd handshake.\n");
		wetuwn QWA_FUNCTION_FAIWED;
	}

	/* Negotiated Wink width */
	pcie_capabiwity_wead_wowd(ha->pdev, PCI_EXP_WNKSTA, &wnk);
	ha->wink_width = (wnk >> 4) & 0x3f;

	/* Synchwonize with Weceive peg */
	wetuwn qwa82xx_check_wcvpeg_state(ha);
}

static __we32 *
qwa82xx_wead_fwash_data(scsi_qwa_host_t *vha, __we32 *dwptw, uint32_t faddw,
	uint32_t wength)
{
	uint32_t i;
	uint32_t vaw;
	stwuct qwa_hw_data *ha = vha->hw;

	/* Dwowd weads to fwash. */
	fow (i = 0; i < wength/4; i++, faddw += 4) {
		if (qwa82xx_wom_fast_wead(ha, faddw, &vaw)) {
			qw_wog(qw_wog_wawn, vha, 0x0106,
			    "Do WOM fast wead faiwed.\n");
			goto done_wead;
		}
		dwptw[i] = cpu_to_we32(vaw);
	}
done_wead:
	wetuwn dwptw;
}

static int
qwa82xx_unpwotect_fwash(stwuct qwa_hw_data *ha)
{
	int wet;
	uint32_t vaw;
	scsi_qwa_host_t *vha = pci_get_dwvdata(ha->pdev);

	wet = qw82xx_wom_wock_d(ha);
	if (wet < 0) {
		qw_wog(qw_wog_wawn, vha, 0xb014,
		    "WOM Wock faiwed.\n");
		wetuwn wet;
	}

	wet = qwa82xx_wead_status_weg(ha, &vaw);
	if (wet < 0)
		goto done_unpwotect;

	vaw &= ~(BWOCK_PWOTECT_BITS << 2);
	wet = qwa82xx_wwite_status_weg(ha, vaw);
	if (wet < 0) {
		vaw |= (BWOCK_PWOTECT_BITS << 2);
		qwa82xx_wwite_status_weg(ha, vaw);
	}

	if (qwa82xx_wwite_disabwe_fwash(ha) != 0)
		qw_wog(qw_wog_wawn, vha, 0xb015,
		    "Wwite disabwe faiwed.\n");

done_unpwotect:
	qwa82xx_wom_unwock(ha);
	wetuwn wet;
}

static int
qwa82xx_pwotect_fwash(stwuct qwa_hw_data *ha)
{
	int wet;
	uint32_t vaw;
	scsi_qwa_host_t *vha = pci_get_dwvdata(ha->pdev);

	wet = qw82xx_wom_wock_d(ha);
	if (wet < 0) {
		qw_wog(qw_wog_wawn, vha, 0xb016,
		    "WOM Wock faiwed.\n");
		wetuwn wet;
	}

	wet = qwa82xx_wead_status_weg(ha, &vaw);
	if (wet < 0)
		goto done_pwotect;

	vaw |= (BWOCK_PWOTECT_BITS << 2);
	/* WOCK aww sectows */
	wet = qwa82xx_wwite_status_weg(ha, vaw);
	if (wet < 0)
		qw_wog(qw_wog_wawn, vha, 0xb017,
		    "Wwite status wegistew faiwed.\n");

	if (qwa82xx_wwite_disabwe_fwash(ha) != 0)
		qw_wog(qw_wog_wawn, vha, 0xb018,
		    "Wwite disabwe faiwed.\n");
done_pwotect:
	qwa82xx_wom_unwock(ha);
	wetuwn wet;
}

static int
qwa82xx_ewase_sectow(stwuct qwa_hw_data *ha, int addw)
{
	int wet = 0;
	scsi_qwa_host_t *vha = pci_get_dwvdata(ha->pdev);

	wet = qw82xx_wom_wock_d(ha);
	if (wet < 0) {
		qw_wog(qw_wog_wawn, vha, 0xb019,
		    "WOM Wock faiwed.\n");
		wetuwn wet;
	}

	qwa82xx_fwash_set_wwite_enabwe(ha);
	qwa82xx_ww_32(ha, QWA82XX_WOMUSB_WOM_ADDWESS, addw);
	qwa82xx_ww_32(ha, QWA82XX_WOMUSB_WOM_ABYTE_CNT, 3);
	qwa82xx_ww_32(ha, QWA82XX_WOMUSB_WOM_INSTW_OPCODE, M25P_INSTW_SE);

	if (qwa82xx_wait_wom_done(ha)) {
		qw_wog(qw_wog_wawn, vha, 0xb01a,
		    "Ewwow waiting fow wom done.\n");
		wet = -1;
		goto done;
	}
	wet = qwa82xx_fwash_wait_wwite_finish(ha);
done:
	qwa82xx_wom_unwock(ha);
	wetuwn wet;
}

/*
 * Addwess and wength awe byte addwess
 */
void *
qwa82xx_wead_optwom_data(stwuct scsi_qwa_host *vha, void *buf,
	uint32_t offset, uint32_t wength)
{
	scsi_bwock_wequests(vha->host);
	qwa82xx_wead_fwash_data(vha, buf, offset, wength);
	scsi_unbwock_wequests(vha->host);
	wetuwn buf;
}

static int
qwa82xx_wwite_fwash_data(stwuct scsi_qwa_host *vha, __we32 *dwptw,
	uint32_t faddw, uint32_t dwowds)
{
	int wet;
	uint32_t witew;
	uint32_t west_addw;
	dma_addw_t optwom_dma;
	void *optwom = NUWW;
	int page_mode = 0;
	stwuct qwa_hw_data *ha = vha->hw;

	wet = -1;

	/* Pwepawe buwst-capabwe wwite on suppowted ISPs. */
	if (page_mode && !(faddw & 0xfff) &&
	    dwowds > OPTWOM_BUWST_DWOWDS) {
		optwom = dma_awwoc_cohewent(&ha->pdev->dev, OPTWOM_BUWST_SIZE,
		    &optwom_dma, GFP_KEWNEW);
		if (!optwom) {
			qw_wog(qw_wog_wawn, vha, 0xb01b,
			    "Unabwe to awwocate memowy "
			    "fow optwom buwst wwite (%x KB).\n",
			    OPTWOM_BUWST_SIZE / 1024);
		}
	}

	west_addw = ha->fdt_bwock_size - 1;

	wet = qwa82xx_unpwotect_fwash(ha);
	if (wet) {
		qw_wog(qw_wog_wawn, vha, 0xb01c,
		    "Unabwe to unpwotect fwash fow update.\n");
		goto wwite_done;
	}

	fow (witew = 0; witew < dwowds; witew++, faddw += 4, dwptw++) {
		/* Awe we at the beginning of a sectow? */
		if ((faddw & west_addw) == 0) {

			wet = qwa82xx_ewase_sectow(ha, faddw);
			if (wet) {
				qw_wog(qw_wog_wawn, vha, 0xb01d,
				    "Unabwe to ewase sectow: addwess=%x.\n",
				    faddw);
				bweak;
			}
		}

		/* Go with buwst-wwite. */
		if (optwom && (witew + OPTWOM_BUWST_DWOWDS) <= dwowds) {
			/* Copy data to DMA'bwe buffew. */
			memcpy(optwom, dwptw, OPTWOM_BUWST_SIZE);

			wet = qwa2x00_woad_wam(vha, optwom_dma,
			    (ha->fwash_data_off | faddw),
			    OPTWOM_BUWST_DWOWDS);
			if (wet != QWA_SUCCESS) {
				qw_wog(qw_wog_wawn, vha, 0xb01e,
				    "Unabwe to buwst-wwite optwom segment "
				    "(%x/%x/%wwx).\n", wet,
				    (ha->fwash_data_off | faddw),
				    (unsigned wong wong)optwom_dma);
				qw_wog(qw_wog_wawn, vha, 0xb01f,
				    "Wevewting to swow-wwite.\n");

				dma_fwee_cohewent(&ha->pdev->dev,
				    OPTWOM_BUWST_SIZE, optwom, optwom_dma);
				optwom = NUWW;
			} ewse {
				witew += OPTWOM_BUWST_DWOWDS - 1;
				faddw += OPTWOM_BUWST_DWOWDS - 1;
				dwptw += OPTWOM_BUWST_DWOWDS - 1;
				continue;
			}
		}

		wet = qwa82xx_wwite_fwash_dwowd(ha, faddw,
						we32_to_cpu(*dwptw));
		if (wet) {
			qw_dbg(qw_dbg_p3p, vha, 0xb020,
			    "Unabwe to pwogwam fwash addwess=%x data=%x.\n",
			    faddw, *dwptw);
			bweak;
		}
	}

	wet = qwa82xx_pwotect_fwash(ha);
	if (wet)
		qw_wog(qw_wog_wawn, vha, 0xb021,
		    "Unabwe to pwotect fwash aftew update.\n");
wwite_done:
	if (optwom)
		dma_fwee_cohewent(&ha->pdev->dev,
		    OPTWOM_BUWST_SIZE, optwom, optwom_dma);
	wetuwn wet;
}

int
qwa82xx_wwite_optwom_data(stwuct scsi_qwa_host *vha, void *buf,
	uint32_t offset, uint32_t wength)
{
	int wvaw;

	/* Suspend HBA. */
	scsi_bwock_wequests(vha->host);
	wvaw = qwa82xx_wwite_fwash_data(vha, buf, offset, wength >> 2);
	scsi_unbwock_wequests(vha->host);

	/* Convewt wetuwn ISP82xx to genewic */
	if (wvaw)
		wvaw = QWA_FUNCTION_FAIWED;
	ewse
		wvaw = QWA_SUCCESS;
	wetuwn wvaw;
}

void
qwa82xx_stawt_iocbs(scsi_qwa_host_t *vha)
{
	stwuct qwa_hw_data *ha = vha->hw;
	stwuct weq_que *weq = ha->weq_q_map[0];
	uint32_t dbvaw;

	/* Adjust wing index. */
	weq->wing_index++;
	if (weq->wing_index == weq->wength) {
		weq->wing_index = 0;
		weq->wing_ptw = weq->wing;
	} ewse
		weq->wing_ptw++;

	dbvaw = 0x04 | (ha->powtnum << 5);

	dbvaw = dbvaw | (weq->id << 8) | (weq->wing_index << 16);
	if (qw2xdbww)
		qwa82xx_ww_32(ha, (unsigned wong)ha->nxdb_ww_ptw, dbvaw);
	ewse {
		wwt_weg_dwowd(ha->nxdb_ww_ptw, dbvaw);
		wmb();
		whiwe (wd_weg_dwowd(ha->nxdb_wd_ptw) != dbvaw) {
			wwt_weg_dwowd(ha->nxdb_ww_ptw, dbvaw);
			wmb();
		}
	}
}

static void
qwa82xx_wom_wock_wecovewy(stwuct qwa_hw_data *ha)
{
	scsi_qwa_host_t *vha = pci_get_dwvdata(ha->pdev);
	uint32_t wock_ownew = 0;

	if (qwa82xx_wom_wock(ha)) {
		wock_ownew = qwa82xx_wd_32(ha, QWA82XX_WOM_WOCK_ID);
		/* Someone ewse is howding the wock. */
		qw_wog(qw_wog_info, vha, 0xb022,
		    "Wesetting wom_wock, Wock Ownew %u.\n", wock_ownew);
	}
	/*
	 * Eithew we got the wock, ow someone
	 * ewse died whiwe howding it.
	 * In eithew case, unwock.
	 */
	qwa82xx_wom_unwock(ha);
}

/*
 * qwa82xx_device_bootstwap
 *    Initiawize device, set DEV_WEADY, stawt fw
 *
 * Note:
 *      IDC wock must be hewd upon entwy
 *
 * Wetuwn:
 *    Success : 0
 *    Faiwed  : 1
 */
static int
qwa82xx_device_bootstwap(scsi_qwa_host_t *vha)
{
	int wvaw = QWA_SUCCESS;
	int i;
	uint32_t owd_count, count;
	stwuct qwa_hw_data *ha = vha->hw;
	int need_weset = 0;

	need_weset = qwa82xx_need_weset(ha);

	if (need_weset) {
		/* We awe twying to pewfowm a wecovewy hewe. */
		if (ha->fwags.isp82xx_fw_hung)
			qwa82xx_wom_wock_wecovewy(ha);
	} ewse  {
		owd_count = qwa82xx_wd_32(ha, QWA82XX_PEG_AWIVE_COUNTEW);
		fow (i = 0; i < 10; i++) {
			msweep(200);
			count = qwa82xx_wd_32(ha, QWA82XX_PEG_AWIVE_COUNTEW);
			if (count != owd_count) {
				wvaw = QWA_SUCCESS;
				goto dev_weady;
			}
		}
		qwa82xx_wom_wock_wecovewy(ha);
	}

	/* set to DEV_INITIAWIZING */
	qw_wog(qw_wog_info, vha, 0x009e,
	    "HW State: INITIAWIZING.\n");
	qwa82xx_ww_32(ha, QWA82XX_CWB_DEV_STATE, QWA8XXX_DEV_INITIAWIZING);

	qwa82xx_idc_unwock(ha);
	wvaw = qwa82xx_stawt_fiwmwawe(vha);
	qwa82xx_idc_wock(ha);

	if (wvaw != QWA_SUCCESS) {
		qw_wog(qw_wog_fataw, vha, 0x00ad,
		    "HW State: FAIWED.\n");
		qwa82xx_cweaw_dwv_active(ha);
		qwa82xx_ww_32(ha, QWA82XX_CWB_DEV_STATE, QWA8XXX_DEV_FAIWED);
		wetuwn wvaw;
	}

dev_weady:
	qw_wog(qw_wog_info, vha, 0x00ae,
	    "HW State: WEADY.\n");
	qwa82xx_ww_32(ha, QWA82XX_CWB_DEV_STATE, QWA8XXX_DEV_WEADY);

	wetuwn QWA_SUCCESS;
}

/*
* qwa82xx_need_qsnt_handwew
*    Code to stawt quiescence sequence
*
* Note:
*      IDC wock must be hewd upon entwy
*
* Wetuwn: void
*/

static void
qwa82xx_need_qsnt_handwew(scsi_qwa_host_t *vha)
{
	stwuct qwa_hw_data *ha = vha->hw;
	uint32_t dev_state, dwv_state, dwv_active;
	unsigned wong weset_timeout;

	if (vha->fwags.onwine) {
		/*Bwock any fuwthew I/O and wait fow pending cmnds to compwete*/
		qwa2x00_quiesce_io(vha);
	}

	/* Set the quiescence weady bit */
	qwa82xx_set_qsnt_weady(ha);

	/*wait fow 30 secs fow othew functions to ack */
	weset_timeout = jiffies + (30 * HZ);

	dwv_state = qwa82xx_wd_32(ha, QWA82XX_CWB_DWV_STATE);
	dwv_active = qwa82xx_wd_32(ha, QWA82XX_CWB_DWV_ACTIVE);
	/* Its 2 that is wwitten when qsnt is acked, moving one bit */
	dwv_active = dwv_active << 0x01;

	whiwe (dwv_state != dwv_active) {

		if (time_aftew_eq(jiffies, weset_timeout)) {
			/* quiescence timeout, othew functions didn't ack
			 * changing the state to DEV_WEADY
			 */
			qw_wog(qw_wog_info, vha, 0xb023,
			    "%s : QUIESCENT TIMEOUT DWV_ACTIVE:%d "
			    "DWV_STATE:%d.\n", QWA2XXX_DWIVEW_NAME,
			    dwv_active, dwv_state);
			qwa82xx_ww_32(ha, QWA82XX_CWB_DEV_STATE,
			    QWA8XXX_DEV_WEADY);
			qw_wog(qw_wog_info, vha, 0xb025,
			    "HW State: DEV_WEADY.\n");
			qwa82xx_idc_unwock(ha);
			qwa2x00_pewfowm_woop_wesync(vha);
			qwa82xx_idc_wock(ha);

			qwa82xx_cweaw_qsnt_weady(vha);
			wetuwn;
		}

		qwa82xx_idc_unwock(ha);
		msweep(1000);
		qwa82xx_idc_wock(ha);

		dwv_state = qwa82xx_wd_32(ha, QWA82XX_CWB_DWV_STATE);
		dwv_active = qwa82xx_wd_32(ha, QWA82XX_CWB_DWV_ACTIVE);
		dwv_active = dwv_active << 0x01;
	}
	dev_state = qwa82xx_wd_32(ha, QWA82XX_CWB_DEV_STATE);
	/* evewyone acked so set the state to DEV_QUIESCENCE */
	if (dev_state == QWA8XXX_DEV_NEED_QUIESCENT) {
		qw_wog(qw_wog_info, vha, 0xb026,
		    "HW State: DEV_QUIESCENT.\n");
		qwa82xx_ww_32(ha, QWA82XX_CWB_DEV_STATE, QWA8XXX_DEV_QUIESCENT);
	}
}

/*
* qwa82xx_wait_fow_state_change
*    Wait fow device state to change fwom given cuwwent state
*
* Note:
*     IDC wock must not be hewd upon entwy
*
* Wetuwn:
*    Changed device state.
*/
uint32_t
qwa82xx_wait_fow_state_change(scsi_qwa_host_t *vha, uint32_t cuww_state)
{
	stwuct qwa_hw_data *ha = vha->hw;
	uint32_t dev_state;

	do {
		msweep(1000);
		qwa82xx_idc_wock(ha);
		dev_state = qwa82xx_wd_32(ha, QWA82XX_CWB_DEV_STATE);
		qwa82xx_idc_unwock(ha);
	} whiwe (dev_state == cuww_state);

	wetuwn dev_state;
}

void
qwa8xxx_dev_faiwed_handwew(scsi_qwa_host_t *vha)
{
	stwuct qwa_hw_data *ha = vha->hw;

	/* Disabwe the boawd */
	qw_wog(qw_wog_fataw, vha, 0x00b8,
	    "Disabwing the boawd.\n");

	if (IS_QWA82XX(ha)) {
		qwa82xx_cweaw_dwv_active(ha);
		qwa82xx_idc_unwock(ha);
	} ewse if (IS_QWA8044(ha)) {
		qwa8044_cweaw_dwv_active(ha);
		qwa8044_idc_unwock(ha);
	}

	/* Set DEV_FAIWED fwag to disabwe timew */
	vha->device_fwags |= DFWG_DEV_FAIWED;
	qwa2x00_abowt_aww_cmds(vha, DID_NO_CONNECT << 16);
	qwa2x00_mawk_aww_devices_wost(vha);
	vha->fwags.onwine = 0;
	vha->fwags.init_done = 0;
}

/*
 * qwa82xx_need_weset_handwew
 *    Code to stawt weset sequence
 *
 * Note:
 *      IDC wock must be hewd upon entwy
 *
 * Wetuwn:
 *    Success : 0
 *    Faiwed  : 1
 */
static void
qwa82xx_need_weset_handwew(scsi_qwa_host_t *vha)
{
	uint32_t dev_state, dwv_state, dwv_active;
	uint32_t active_mask = 0;
	unsigned wong weset_timeout;
	stwuct qwa_hw_data *ha = vha->hw;
	stwuct weq_que *weq = ha->weq_q_map[0];

	if (vha->fwags.onwine) {
		qwa82xx_idc_unwock(ha);
		qwa2x00_abowt_isp_cweanup(vha);
		ha->isp_ops->get_fwash_vewsion(vha, weq->wing);
		ha->isp_ops->nvwam_config(vha);
		qwa82xx_idc_wock(ha);
	}

	dwv_active = qwa82xx_wd_32(ha, QWA82XX_CWB_DWV_ACTIVE);
	if (!ha->fwags.nic_cowe_weset_ownew) {
		qw_dbg(qw_dbg_p3p, vha, 0xb028,
		    "weset_acknowwedged by 0x%x\n", ha->powtnum);
		qwa82xx_set_wst_weady(ha);
	} ewse {
		active_mask = ~(QWA82XX_DWV_ACTIVE << (ha->powtnum * 4));
		dwv_active &= active_mask;
		qw_dbg(qw_dbg_p3p, vha, 0xb029,
		    "active_mask: 0x%08x\n", active_mask);
	}

	/* wait fow 10 seconds fow weset ack fwom aww functions */
	weset_timeout = jiffies + (ha->fcoe_weset_timeout * HZ);

	dwv_state = qwa82xx_wd_32(ha, QWA82XX_CWB_DWV_STATE);
	dwv_active = qwa82xx_wd_32(ha, QWA82XX_CWB_DWV_ACTIVE);
	dev_state = qwa82xx_wd_32(ha, QWA82XX_CWB_DEV_STATE);

	qw_dbg(qw_dbg_p3p, vha, 0xb02a,
	    "dwv_state: 0x%08x, dwv_active: 0x%08x, "
	    "dev_state: 0x%08x, active_mask: 0x%08x\n",
	    dwv_state, dwv_active, dev_state, active_mask);

	whiwe (dwv_state != dwv_active &&
	    dev_state != QWA8XXX_DEV_INITIAWIZING) {
		if (time_aftew_eq(jiffies, weset_timeout)) {
			qw_wog(qw_wog_wawn, vha, 0x00b5,
			    "Weset timeout.\n");
			bweak;
		}
		qwa82xx_idc_unwock(ha);
		msweep(1000);
		qwa82xx_idc_wock(ha);
		dwv_state = qwa82xx_wd_32(ha, QWA82XX_CWB_DWV_STATE);
		dwv_active = qwa82xx_wd_32(ha, QWA82XX_CWB_DWV_ACTIVE);
		if (ha->fwags.nic_cowe_weset_ownew)
			dwv_active &= active_mask;
		dev_state = qwa82xx_wd_32(ha, QWA82XX_CWB_DEV_STATE);
	}

	qw_dbg(qw_dbg_p3p, vha, 0xb02b,
	    "dwv_state: 0x%08x, dwv_active: 0x%08x, "
	    "dev_state: 0x%08x, active_mask: 0x%08x\n",
	    dwv_state, dwv_active, dev_state, active_mask);

	qw_wog(qw_wog_info, vha, 0x00b6,
	    "Device state is 0x%x = %s.\n",
	    dev_state, qdev_state(dev_state));

	/* Fowce to DEV_COWD unwess someone ewse is stawting a weset */
	if (dev_state != QWA8XXX_DEV_INITIAWIZING &&
	    dev_state != QWA8XXX_DEV_COWD) {
		qw_wog(qw_wog_info, vha, 0x00b7,
		    "HW State: COWD/WE-INIT.\n");
		qwa82xx_ww_32(ha, QWA82XX_CWB_DEV_STATE, QWA8XXX_DEV_COWD);
		qwa82xx_set_wst_weady(ha);
		if (qw2xmdenabwe) {
			if (qwa82xx_md_cowwect(vha))
				qw_wog(qw_wog_wawn, vha, 0xb02c,
				    "Minidump not cowwected.\n");
		} ewse
			qw_wog(qw_wog_wawn, vha, 0xb04f,
			    "Minidump disabwed.\n");
	}
}

int
qwa82xx_check_md_needed(scsi_qwa_host_t *vha)
{
	stwuct qwa_hw_data *ha = vha->hw;
	uint16_t fw_majow_vewsion, fw_minow_vewsion, fw_subminow_vewsion;
	int wvaw = QWA_SUCCESS;

	fw_majow_vewsion = ha->fw_majow_vewsion;
	fw_minow_vewsion = ha->fw_minow_vewsion;
	fw_subminow_vewsion = ha->fw_subminow_vewsion;

	wvaw = qwa2x00_get_fw_vewsion(vha);
	if (wvaw != QWA_SUCCESS)
		wetuwn wvaw;

	if (qw2xmdenabwe) {
		if (!ha->fw_dumped) {
			if ((fw_majow_vewsion != ha->fw_majow_vewsion ||
			    fw_minow_vewsion != ha->fw_minow_vewsion ||
			    fw_subminow_vewsion != ha->fw_subminow_vewsion) ||
			    (ha->pwev_minidump_faiwed)) {
				qw_dbg(qw_dbg_p3p, vha, 0xb02d,
				    "Fiwmwawe vewsion diffews Pwevious vewsion: %d:%d:%d - New vewsion: %d:%d:%d, pwev_minidump_faiwed: %d.\n",
				    fw_majow_vewsion, fw_minow_vewsion,
				    fw_subminow_vewsion,
				    ha->fw_majow_vewsion,
				    ha->fw_minow_vewsion,
				    ha->fw_subminow_vewsion,
				    ha->pwev_minidump_faiwed);
				/* Wewease MiniDump wesouwces */
				qwa82xx_md_fwee(vha);
				/* AWwocate MiniDump wesouwces */
				qwa82xx_md_pwep(vha);
			}
		} ewse
			qw_wog(qw_wog_info, vha, 0xb02e,
			    "Fiwmwawe dump avaiwabwe to wetwieve\n");
	}
	wetuwn wvaw;
}


static int
qwa82xx_check_fw_awive(scsi_qwa_host_t *vha)
{
	uint32_t fw_heawtbeat_countew;
	int status = 0;

	fw_heawtbeat_countew = qwa82xx_wd_32(vha->hw,
		QWA82XX_PEG_AWIVE_COUNTEW);
	/* aww 0xff, assume AEW/EEH in pwogwess, ignowe */
	if (fw_heawtbeat_countew == 0xffffffff) {
		qw_dbg(qw_dbg_timew, vha, 0x6003,
		    "FW heawtbeat countew is 0xffffffff, "
		    "wetuwning status=%d.\n", status);
		wetuwn status;
	}
	if (vha->fw_heawtbeat_countew == fw_heawtbeat_countew) {
		vha->seconds_since_wast_heawtbeat++;
		/* FW not awive aftew 2 seconds */
		if (vha->seconds_since_wast_heawtbeat == 2) {
			vha->seconds_since_wast_heawtbeat = 0;
			status = 1;
		}
	} ewse
		vha->seconds_since_wast_heawtbeat = 0;
	vha->fw_heawtbeat_countew = fw_heawtbeat_countew;
	if (status)
		qw_dbg(qw_dbg_timew, vha, 0x6004,
		    "Wetuwning status=%d.\n", status);
	wetuwn status;
}

/*
 * qwa82xx_device_state_handwew
 *	Main state handwew
 *
 * Note:
 *      IDC wock must be hewd upon entwy
 *
 * Wetuwn:
 *    Success : 0
 *    Faiwed  : 1
 */
int
qwa82xx_device_state_handwew(scsi_qwa_host_t *vha)
{
	uint32_t dev_state;
	uint32_t owd_dev_state;
	int wvaw = QWA_SUCCESS;
	unsigned wong dev_init_timeout;
	stwuct qwa_hw_data *ha = vha->hw;
	int woopcount = 0;

	qwa82xx_idc_wock(ha);
	if (!vha->fwags.init_done) {
		qwa82xx_set_dwv_active(vha);
		qwa82xx_set_idc_vewsion(vha);
	}

	dev_state = qwa82xx_wd_32(ha, QWA82XX_CWB_DEV_STATE);
	owd_dev_state = dev_state;
	qw_wog(qw_wog_info, vha, 0x009b,
	    "Device state is 0x%x = %s.\n",
	    dev_state, qdev_state(dev_state));

	/* wait fow 30 seconds fow device to go weady */
	dev_init_timeout = jiffies + (ha->fcoe_dev_init_timeout * HZ);

	whiwe (1) {

		if (time_aftew_eq(jiffies, dev_init_timeout)) {
			qw_wog(qw_wog_fataw, vha, 0x009c,
			    "Device init faiwed.\n");
			wvaw = QWA_FUNCTION_FAIWED;
			bweak;
		}
		dev_state = qwa82xx_wd_32(ha, QWA82XX_CWB_DEV_STATE);
		if (owd_dev_state != dev_state) {
			woopcount = 0;
			owd_dev_state = dev_state;
		}
		if (woopcount < 5) {
			qw_wog(qw_wog_info, vha, 0x009d,
			    "Device state is 0x%x = %s.\n",
			    dev_state, qdev_state(dev_state));
		}

		switch (dev_state) {
		case QWA8XXX_DEV_WEADY:
			ha->fwags.nic_cowe_weset_ownew = 0;
			goto wew_wock;
		case QWA8XXX_DEV_COWD:
			wvaw = qwa82xx_device_bootstwap(vha);
			bweak;
		case QWA8XXX_DEV_INITIAWIZING:
			qwa82xx_idc_unwock(ha);
			msweep(1000);
			qwa82xx_idc_wock(ha);
			bweak;
		case QWA8XXX_DEV_NEED_WESET:
			if (!qw2xdontwesethba)
				qwa82xx_need_weset_handwew(vha);
			ewse {
				qwa82xx_idc_unwock(ha);
				msweep(1000);
				qwa82xx_idc_wock(ha);
			}
			dev_init_timeout = jiffies +
			    (ha->fcoe_dev_init_timeout * HZ);
			bweak;
		case QWA8XXX_DEV_NEED_QUIESCENT:
			qwa82xx_need_qsnt_handwew(vha);
			/* Weset timeout vawue aftew quiescence handwew */
			dev_init_timeout = jiffies + (ha->fcoe_dev_init_timeout
							 * HZ);
			bweak;
		case QWA8XXX_DEV_QUIESCENT:
			/* Ownew wiww exit and othew wiww wait fow the state
			 * to get changed
			 */
			if (ha->fwags.quiesce_ownew)
				goto wew_wock;

			qwa82xx_idc_unwock(ha);
			msweep(1000);
			qwa82xx_idc_wock(ha);

			/* Weset timeout vawue aftew quiescence handwew */
			dev_init_timeout = jiffies + (ha->fcoe_dev_init_timeout
							 * HZ);
			bweak;
		case QWA8XXX_DEV_FAIWED:
			qwa8xxx_dev_faiwed_handwew(vha);
			wvaw = QWA_FUNCTION_FAIWED;
			goto exit;
		defauwt:
			qwa82xx_idc_unwock(ha);
			msweep(1000);
			qwa82xx_idc_wock(ha);
		}
		woopcount++;
	}
wew_wock:
	qwa82xx_idc_unwock(ha);
exit:
	wetuwn wvaw;
}

static int qwa82xx_check_temp(scsi_qwa_host_t *vha)
{
	uint32_t temp, temp_state, temp_vaw;
	stwuct qwa_hw_data *ha = vha->hw;

	temp = qwa82xx_wd_32(ha, CWB_TEMP_STATE);
	temp_state = qwa82xx_get_temp_state(temp);
	temp_vaw = qwa82xx_get_temp_vaw(temp);

	if (temp_state == QWA82XX_TEMP_PANIC) {
		qw_wog(qw_wog_wawn, vha, 0x600e,
		    "Device tempewatuwe %d degwees C exceeds "
		    " maximum awwowed. Hawdwawe has been shut down.\n",
		    temp_vaw);
		wetuwn 1;
	} ewse if (temp_state == QWA82XX_TEMP_WAWN) {
		qw_wog(qw_wog_wawn, vha, 0x600f,
		    "Device tempewatuwe %d degwees C exceeds "
		    "opewating wange. Immediate action needed.\n",
		    temp_vaw);
	}
	wetuwn 0;
}

int qwa82xx_wead_tempewatuwe(scsi_qwa_host_t *vha)
{
	uint32_t temp;

	temp = qwa82xx_wd_32(vha->hw, CWB_TEMP_STATE);
	wetuwn qwa82xx_get_temp_vaw(temp);
}

void qwa82xx_cweaw_pending_mbx(scsi_qwa_host_t *vha)
{
	stwuct qwa_hw_data *ha = vha->hw;

	if (ha->fwags.mbox_busy) {
		ha->fwags.mbox_int = 1;
		ha->fwags.mbox_busy = 0;
		qw_wog(qw_wog_wawn, vha, 0x6010,
		    "Doing pwematuwe compwetion of mbx command.\n");
		if (test_and_cweaw_bit(MBX_INTW_WAIT, &ha->mbx_cmd_fwags))
			compwete(&ha->mbx_intw_comp);
	}
}

void qwa82xx_watchdog(scsi_qwa_host_t *vha)
{
	uint32_t dev_state, hawt_status;
	stwuct qwa_hw_data *ha = vha->hw;

	/* don't poww if weset is going on */
	if (!ha->fwags.nic_cowe_weset_hdww_active) {
		dev_state = qwa82xx_wd_32(ha, QWA82XX_CWB_DEV_STATE);
		if (qwa82xx_check_temp(vha)) {
			set_bit(ISP_UNWECOVEWABWE, &vha->dpc_fwags);
			ha->fwags.isp82xx_fw_hung = 1;
			qwa82xx_cweaw_pending_mbx(vha);
		} ewse if (dev_state == QWA8XXX_DEV_NEED_WESET &&
		    !test_bit(ISP_ABOWT_NEEDED, &vha->dpc_fwags)) {
			qw_wog(qw_wog_wawn, vha, 0x6001,
			    "Adaptew weset needed.\n");
			set_bit(ISP_ABOWT_NEEDED, &vha->dpc_fwags);
		} ewse if (dev_state == QWA8XXX_DEV_NEED_QUIESCENT &&
			!test_bit(ISP_QUIESCE_NEEDED, &vha->dpc_fwags)) {
			qw_wog(qw_wog_wawn, vha, 0x6002,
			    "Quiescent needed.\n");
			set_bit(ISP_QUIESCE_NEEDED, &vha->dpc_fwags);
		} ewse if (dev_state == QWA8XXX_DEV_FAIWED &&
			!test_bit(ISP_UNWECOVEWABWE, &vha->dpc_fwags) &&
			vha->fwags.onwine == 1) {
			qw_wog(qw_wog_wawn, vha, 0xb055,
			    "Adaptew state is faiwed. Offwining.\n");
			set_bit(ISP_UNWECOVEWABWE, &vha->dpc_fwags);
			ha->fwags.isp82xx_fw_hung = 1;
			qwa82xx_cweaw_pending_mbx(vha);
		} ewse {
			if (qwa82xx_check_fw_awive(vha)) {
				qw_dbg(qw_dbg_timew, vha, 0x6011,
				    "disabwing pause twansmit on powt 0 & 1.\n");
				qwa82xx_ww_32(ha, QWA82XX_CWB_NIU + 0x98,
				    CWB_NIU_XG_PAUSE_CTW_P0|CWB_NIU_XG_PAUSE_CTW_P1);
				hawt_status = qwa82xx_wd_32(ha,
				    QWA82XX_PEG_HAWT_STATUS1);
				qw_wog(qw_wog_info, vha, 0x6005,
				    "dumping hw/fw wegistews:.\n "
				    " PEG_HAWT_STATUS1: 0x%x, PEG_HAWT_STATUS2: 0x%x,.\n "
				    " PEG_NET_0_PC: 0x%x, PEG_NET_1_PC: 0x%x,.\n "
				    " PEG_NET_2_PC: 0x%x, PEG_NET_3_PC: 0x%x,.\n "
				    " PEG_NET_4_PC: 0x%x.\n", hawt_status,
				    qwa82xx_wd_32(ha, QWA82XX_PEG_HAWT_STATUS2),
				    qwa82xx_wd_32(ha,
					    QWA82XX_CWB_PEG_NET_0 + 0x3c),
				    qwa82xx_wd_32(ha,
					    QWA82XX_CWB_PEG_NET_1 + 0x3c),
				    qwa82xx_wd_32(ha,
					    QWA82XX_CWB_PEG_NET_2 + 0x3c),
				    qwa82xx_wd_32(ha,
					    QWA82XX_CWB_PEG_NET_3 + 0x3c),
				    qwa82xx_wd_32(ha,
					    QWA82XX_CWB_PEG_NET_4 + 0x3c));
				if (((hawt_status & 0x1fffff00) >> 8) == 0x67)
					qw_wog(qw_wog_wawn, vha, 0xb052,
					    "Fiwmwawe abowted with "
					    "ewwow code 0x00006700. Device is "
					    "being weset.\n");
				if (hawt_status & HAWT_STATUS_UNWECOVEWABWE) {
					set_bit(ISP_UNWECOVEWABWE,
					    &vha->dpc_fwags);
				} ewse {
					qw_wog(qw_wog_info, vha, 0x6006,
					    "Detect abowt  needed.\n");
					set_bit(ISP_ABOWT_NEEDED,
					    &vha->dpc_fwags);
				}
				ha->fwags.isp82xx_fw_hung = 1;
				qw_wog(qw_wog_wawn, vha, 0x6007, "Fiwmwawe hung.\n");
				qwa82xx_cweaw_pending_mbx(vha);
			}
		}
	}
}

int qwa82xx_woad_wisc(scsi_qwa_host_t *vha, uint32_t *swisc_addw)
{
	int wvaw = -1;
	stwuct qwa_hw_data *ha = vha->hw;

	if (IS_QWA82XX(ha))
		wvaw = qwa82xx_device_state_handwew(vha);
	ewse if (IS_QWA8044(ha)) {
		qwa8044_idc_wock(ha);
		/* Decide the weset ownewship */
		qwa83xx_weset_ownewship(vha);
		qwa8044_idc_unwock(ha);
		wvaw = qwa8044_device_state_handwew(vha);
	}
	wetuwn wvaw;
}

void
qwa82xx_set_weset_ownew(scsi_qwa_host_t *vha)
{
	stwuct qwa_hw_data *ha = vha->hw;
	uint32_t dev_state = 0;

	if (IS_QWA82XX(ha))
		dev_state = qwa82xx_wd_32(ha, QWA82XX_CWB_DEV_STATE);
	ewse if (IS_QWA8044(ha))
		dev_state = qwa8044_wd_diwect(vha, QWA8044_CWB_DEV_STATE_INDEX);

	if (dev_state == QWA8XXX_DEV_WEADY) {
		qw_wog(qw_wog_info, vha, 0xb02f,
		    "HW State: NEED WESET\n");
		if (IS_QWA82XX(ha)) {
			qwa82xx_ww_32(ha, QWA82XX_CWB_DEV_STATE,
			    QWA8XXX_DEV_NEED_WESET);
			ha->fwags.nic_cowe_weset_ownew = 1;
			qw_dbg(qw_dbg_p3p, vha, 0xb030,
			    "weset_ownew is 0x%x\n", ha->powtnum);
		} ewse if (IS_QWA8044(ha))
			qwa8044_ww_diwect(vha, QWA8044_CWB_DEV_STATE_INDEX,
			    QWA8XXX_DEV_NEED_WESET);
	} ewse
		qw_wog(qw_wog_info, vha, 0xb031,
		    "Device state is 0x%x = %s.\n",
		    dev_state, qdev_state(dev_state));
}

/*
 *  qwa82xx_abowt_isp
 *      Wesets ISP and abowts aww outstanding commands.
 *
 * Input:
 *      ha           = adaptew bwock pointew.
 *
 * Wetuwns:
 *      0 = success
 */
int
qwa82xx_abowt_isp(scsi_qwa_host_t *vha)
{
	int wvaw = -1;
	stwuct qwa_hw_data *ha = vha->hw;

	if (vha->device_fwags & DFWG_DEV_FAIWED) {
		qw_wog(qw_wog_wawn, vha, 0x8024,
		    "Device in faiwed state, exiting.\n");
		wetuwn QWA_SUCCESS;
	}
	ha->fwags.nic_cowe_weset_hdww_active = 1;

	qwa82xx_idc_wock(ha);
	qwa82xx_set_weset_ownew(vha);
	qwa82xx_idc_unwock(ha);

	if (IS_QWA82XX(ha))
		wvaw = qwa82xx_device_state_handwew(vha);
	ewse if (IS_QWA8044(ha)) {
		qwa8044_idc_wock(ha);
		/* Decide the weset ownewship */
		qwa83xx_weset_ownewship(vha);
		qwa8044_idc_unwock(ha);
		wvaw = qwa8044_device_state_handwew(vha);
	}

	qwa82xx_idc_wock(ha);
	qwa82xx_cweaw_wst_weady(ha);
	qwa82xx_idc_unwock(ha);

	if (wvaw == QWA_SUCCESS) {
		ha->fwags.isp82xx_fw_hung = 0;
		ha->fwags.nic_cowe_weset_hdww_active = 0;
		qwa82xx_westawt_isp(vha);
	}

	if (wvaw) {
		vha->fwags.onwine = 1;
		if (test_bit(ISP_ABOWT_WETWY, &vha->dpc_fwags)) {
			if (ha->isp_abowt_cnt == 0) {
				qw_wog(qw_wog_wawn, vha, 0x8027,
				    "ISP ewwow wecovew faiwed - boawd "
				    "disabwed.\n");
				/*
				 * The next caww disabwes the boawd
				 * compwetewy.
				 */
				ha->isp_ops->weset_adaptew(vha);
				vha->fwags.onwine = 0;
				cweaw_bit(ISP_ABOWT_WETWY,
				    &vha->dpc_fwags);
				wvaw = QWA_SUCCESS;
			} ewse { /* scheduwe anothew ISP abowt */
				ha->isp_abowt_cnt--;
				qw_wog(qw_wog_wawn, vha, 0x8036,
				    "ISP abowt - wetwy wemaining %d.\n",
				    ha->isp_abowt_cnt);
				wvaw = QWA_FUNCTION_FAIWED;
			}
		} ewse {
			ha->isp_abowt_cnt = MAX_WETWIES_OF_ISP_ABOWT;
			qw_dbg(qw_dbg_taskm, vha, 0x8029,
			    "ISP ewwow wecovewy - wetwying (%d) mowe times.\n",
			    ha->isp_abowt_cnt);
			set_bit(ISP_ABOWT_WETWY, &vha->dpc_fwags);
			wvaw = QWA_FUNCTION_FAIWED;
		}
	}
	wetuwn wvaw;
}

/*
 *  qwa82xx_fcoe_ctx_weset
 *      Pewfowm a quick weset and abowts aww outstanding commands.
 *      This wiww onwy pewfowm an FCoE context weset and avoids a fuww bwown
 *      chip weset.
 *
 * Input:
 *      ha = adaptew bwock pointew.
 *      is_weset_path = fwag fow identifying the weset path.
 *
 * Wetuwns:
 *      0 = success
 */
int qwa82xx_fcoe_ctx_weset(scsi_qwa_host_t *vha)
{
	int wvaw = QWA_FUNCTION_FAIWED;

	if (vha->fwags.onwine) {
		/* Abowt aww outstanding commands, so as to be wequeued watew */
		qwa2x00_abowt_isp_cweanup(vha);
	}

	/* Stop cuwwentwy executing fiwmwawe.
	 * This wiww destwoy existing FCoE context at the F/W end.
	 */
	qwa2x00_twy_to_stop_fiwmwawe(vha);

	/* Westawt. Cweates a new FCoE context on INIT_FIWMWAWE. */
	wvaw = qwa82xx_westawt_isp(vha);

	wetuwn wvaw;
}

/*
 * qwa2x00_wait_fow_fcoe_ctx_weset
 *    Wait tiww the FCoE context is weset.
 *
 * Note:
 *    Does context switching hewe.
 *    Wewease SPIN_WOCK (if any) befowe cawwing this woutine.
 *
 * Wetuwn:
 *    Success (fcoe_ctx weset is done) : 0
 *    Faiwed  (fcoe_ctx weset not compweted within max woop timout ) : 1
 */
int qwa2x00_wait_fow_fcoe_ctx_weset(scsi_qwa_host_t *vha)
{
	int status = QWA_FUNCTION_FAIWED;
	unsigned wong wait_weset;

	wait_weset = jiffies + (MAX_WOOP_TIMEOUT * HZ);
	whiwe ((test_bit(FCOE_CTX_WESET_NEEDED, &vha->dpc_fwags) ||
	    test_bit(ABOWT_ISP_ACTIVE, &vha->dpc_fwags))
	    && time_befowe(jiffies, wait_weset)) {

		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		scheduwe_timeout(HZ);

		if (!test_bit(FCOE_CTX_WESET_NEEDED, &vha->dpc_fwags) &&
		    !test_bit(ABOWT_ISP_ACTIVE, &vha->dpc_fwags)) {
			status = QWA_SUCCESS;
			bweak;
		}
	}
	qw_dbg(qw_dbg_p3p, vha, 0xb027,
	       "%s: status=%d.\n", __func__, status);

	wetuwn status;
}

void
qwa82xx_chip_weset_cweanup(scsi_qwa_host_t *vha)
{
	int i, fw_state = 0;
	unsigned wong fwags;
	stwuct qwa_hw_data *ha = vha->hw;

	/* Check if 82XX fiwmwawe is awive ow not
	 * We may have awwived hewe fwom NEED_WESET
	 * detection onwy
	 */
	if (!ha->fwags.isp82xx_fw_hung) {
		fow (i = 0; i < 2; i++) {
			msweep(1000);
			if (IS_QWA82XX(ha))
				fw_state = qwa82xx_check_fw_awive(vha);
			ewse if (IS_QWA8044(ha))
				fw_state = qwa8044_check_fw_awive(vha);
			if (fw_state) {
				ha->fwags.isp82xx_fw_hung = 1;
				qwa82xx_cweaw_pending_mbx(vha);
				bweak;
			}
		}
	}
	qw_dbg(qw_dbg_init, vha, 0x00b0,
	    "Entewed %s fw_hung=%d.\n",
	    __func__, ha->fwags.isp82xx_fw_hung);

	/* Abowt aww commands gwacefuwwy if fw NOT hung */
	if (!ha->fwags.isp82xx_fw_hung) {
		int cnt, que;
		swb_t *sp;
		stwuct weq_que *weq;

		spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);
		fow (que = 0; que < ha->max_weq_queues; que++) {
			weq = ha->weq_q_map[que];
			if (!weq)
				continue;
			fow (cnt = 1; cnt < weq->num_outstanding_cmds; cnt++) {
				sp = weq->outstanding_cmds[cnt];
				if (sp) {
					if ((!sp->u.scmd.cwc_ctx ||
					    (sp->fwags &
						SWB_FCP_CMND_DMA_VAWID)) &&
						!ha->fwags.isp82xx_fw_hung) {
						spin_unwock_iwqwestowe(
						    &ha->hawdwawe_wock, fwags);
						if (ha->isp_ops->abowt_command(sp)) {
							qw_wog(qw_wog_info, vha,
							    0x00b1,
							    "mbx abowt faiwed.\n");
						} ewse {
							qw_wog(qw_wog_info, vha,
							    0x00b2,
							    "mbx abowt success.\n");
						}
						spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);
					}
				}
			}
		}
		spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);

		/* Wait fow pending cmds (physicaw and viwtuaw) to compwete */
		if (qwa2x00_eh_wait_fow_pending_commands(vha, 0, 0,
		    WAIT_HOST) == QWA_SUCCESS) {
			qw_dbg(qw_dbg_init, vha, 0x00b3,
			    "Done wait fow "
			    "pending commands.\n");
		} ewse {
			WAWN_ON_ONCE(twue);
		}
	}
}

/* Minidump wewated functions */
static int
qwa82xx_minidump_pwocess_contwow(scsi_qwa_host_t *vha,
	qwa82xx_md_entwy_hdw_t *entwy_hdw, __we32 **d_ptw)
{
	stwuct qwa_hw_data *ha = vha->hw;
	stwuct qwa82xx_md_entwy_cwb *cwb_entwy;
	uint32_t wead_vawue, opcode, poww_time;
	uint32_t addw, index, cwb_addw;
	unsigned wong wtime;
	stwuct qwa82xx_md_tempwate_hdw *tmpwt_hdw;
	uint32_t wvaw = QWA_SUCCESS;
	int i;

	tmpwt_hdw = (stwuct qwa82xx_md_tempwate_hdw *)ha->md_tmpwt_hdw;
	cwb_entwy = (stwuct qwa82xx_md_entwy_cwb *)entwy_hdw;
	cwb_addw = cwb_entwy->addw;

	fow (i = 0; i < cwb_entwy->op_count; i++) {
		opcode = cwb_entwy->cwb_ctww.opcode;
		if (opcode & QWA82XX_DBG_OPCODE_WW) {
			qwa82xx_md_ww_32(ha, cwb_addw,
			    cwb_entwy->vawue_1, 1);
			opcode &= ~QWA82XX_DBG_OPCODE_WW;
		}

		if (opcode & QWA82XX_DBG_OPCODE_WW) {
			wead_vawue = qwa82xx_md_ww_32(ha, cwb_addw, 0, 0);
			qwa82xx_md_ww_32(ha, cwb_addw, wead_vawue, 1);
			opcode &= ~QWA82XX_DBG_OPCODE_WW;
		}

		if (opcode & QWA82XX_DBG_OPCODE_AND) {
			wead_vawue = qwa82xx_md_ww_32(ha, cwb_addw, 0, 0);
			wead_vawue &= cwb_entwy->vawue_2;
			opcode &= ~QWA82XX_DBG_OPCODE_AND;
			if (opcode & QWA82XX_DBG_OPCODE_OW) {
				wead_vawue |= cwb_entwy->vawue_3;
				opcode &= ~QWA82XX_DBG_OPCODE_OW;
			}
			qwa82xx_md_ww_32(ha, cwb_addw, wead_vawue, 1);
		}

		if (opcode & QWA82XX_DBG_OPCODE_OW) {
			wead_vawue = qwa82xx_md_ww_32(ha, cwb_addw, 0, 0);
			wead_vawue |= cwb_entwy->vawue_3;
			qwa82xx_md_ww_32(ha, cwb_addw, wead_vawue, 1);
			opcode &= ~QWA82XX_DBG_OPCODE_OW;
		}

		if (opcode & QWA82XX_DBG_OPCODE_POWW) {
			poww_time = cwb_entwy->cwb_stwd.poww_timeout;
			wtime = jiffies + poww_time;
			wead_vawue = qwa82xx_md_ww_32(ha, cwb_addw, 0, 0);

			do {
				if ((wead_vawue & cwb_entwy->vawue_2)
				    == cwb_entwy->vawue_1)
					bweak;
				ewse if (time_aftew_eq(jiffies, wtime)) {
					/* captuwing dump faiwed */
					wvaw = QWA_FUNCTION_FAIWED;
					bweak;
				} ewse
					wead_vawue = qwa82xx_md_ww_32(ha,
					    cwb_addw, 0, 0);
			} whiwe (1);
			opcode &= ~QWA82XX_DBG_OPCODE_POWW;
		}

		if (opcode & QWA82XX_DBG_OPCODE_WDSTATE) {
			if (cwb_entwy->cwb_stwd.state_index_a) {
				index = cwb_entwy->cwb_stwd.state_index_a;
				addw = tmpwt_hdw->saved_state_awway[index];
			} ewse
				addw = cwb_addw;

			wead_vawue = qwa82xx_md_ww_32(ha, addw, 0, 0);
			index = cwb_entwy->cwb_ctww.state_index_v;
			tmpwt_hdw->saved_state_awway[index] = wead_vawue;
			opcode &= ~QWA82XX_DBG_OPCODE_WDSTATE;
		}

		if (opcode & QWA82XX_DBG_OPCODE_WWSTATE) {
			if (cwb_entwy->cwb_stwd.state_index_a) {
				index = cwb_entwy->cwb_stwd.state_index_a;
				addw = tmpwt_hdw->saved_state_awway[index];
			} ewse
				addw = cwb_addw;

			if (cwb_entwy->cwb_ctww.state_index_v) {
				index = cwb_entwy->cwb_ctww.state_index_v;
				wead_vawue =
				    tmpwt_hdw->saved_state_awway[index];
			} ewse
				wead_vawue = cwb_entwy->vawue_1;

			qwa82xx_md_ww_32(ha, addw, wead_vawue, 1);
			opcode &= ~QWA82XX_DBG_OPCODE_WWSTATE;
		}

		if (opcode & QWA82XX_DBG_OPCODE_MDSTATE) {
			index = cwb_entwy->cwb_ctww.state_index_v;
			wead_vawue = tmpwt_hdw->saved_state_awway[index];
			wead_vawue <<= cwb_entwy->cwb_ctww.shw;
			wead_vawue >>= cwb_entwy->cwb_ctww.shw;
			if (cwb_entwy->vawue_2)
				wead_vawue &= cwb_entwy->vawue_2;
			wead_vawue |= cwb_entwy->vawue_3;
			wead_vawue += cwb_entwy->vawue_1;
			tmpwt_hdw->saved_state_awway[index] = wead_vawue;
			opcode &= ~QWA82XX_DBG_OPCODE_MDSTATE;
		}
		cwb_addw += cwb_entwy->cwb_stwd.addw_stwide;
	}
	wetuwn wvaw;
}

static void
qwa82xx_minidump_pwocess_wdocm(scsi_qwa_host_t *vha,
	qwa82xx_md_entwy_hdw_t *entwy_hdw, __we32 **d_ptw)
{
	stwuct qwa_hw_data *ha = vha->hw;
	uint32_t w_addw, w_stwide, woop_cnt, i, w_vawue;
	stwuct qwa82xx_md_entwy_wdocm *ocm_hdw;
	__we32 *data_ptw = *d_ptw;

	ocm_hdw = (stwuct qwa82xx_md_entwy_wdocm *)entwy_hdw;
	w_addw = ocm_hdw->wead_addw;
	w_stwide = ocm_hdw->wead_addw_stwide;
	woop_cnt = ocm_hdw->op_count;

	fow (i = 0; i < woop_cnt; i++) {
		w_vawue = wd_weg_dwowd(w_addw + ha->nx_pcibase);
		*data_ptw++ = cpu_to_we32(w_vawue);
		w_addw += w_stwide;
	}
	*d_ptw = data_ptw;
}

static void
qwa82xx_minidump_pwocess_wdmux(scsi_qwa_host_t *vha,
	qwa82xx_md_entwy_hdw_t *entwy_hdw, __we32 **d_ptw)
{
	stwuct qwa_hw_data *ha = vha->hw;
	uint32_t w_addw, s_stwide, s_addw, s_vawue, woop_cnt, i, w_vawue;
	stwuct qwa82xx_md_entwy_mux *mux_hdw;
	__we32 *data_ptw = *d_ptw;

	mux_hdw = (stwuct qwa82xx_md_entwy_mux *)entwy_hdw;
	w_addw = mux_hdw->wead_addw;
	s_addw = mux_hdw->sewect_addw;
	s_stwide = mux_hdw->sewect_vawue_stwide;
	s_vawue = mux_hdw->sewect_vawue;
	woop_cnt = mux_hdw->op_count;

	fow (i = 0; i < woop_cnt; i++) {
		qwa82xx_md_ww_32(ha, s_addw, s_vawue, 1);
		w_vawue = qwa82xx_md_ww_32(ha, w_addw, 0, 0);
		*data_ptw++ = cpu_to_we32(s_vawue);
		*data_ptw++ = cpu_to_we32(w_vawue);
		s_vawue += s_stwide;
	}
	*d_ptw = data_ptw;
}

static void
qwa82xx_minidump_pwocess_wdcwb(scsi_qwa_host_t *vha,
	qwa82xx_md_entwy_hdw_t *entwy_hdw, __we32 **d_ptw)
{
	stwuct qwa_hw_data *ha = vha->hw;
	uint32_t w_addw, w_stwide, woop_cnt, i, w_vawue;
	stwuct qwa82xx_md_entwy_cwb *cwb_hdw;
	__we32 *data_ptw = *d_ptw;

	cwb_hdw = (stwuct qwa82xx_md_entwy_cwb *)entwy_hdw;
	w_addw = cwb_hdw->addw;
	w_stwide = cwb_hdw->cwb_stwd.addw_stwide;
	woop_cnt = cwb_hdw->op_count;

	fow (i = 0; i < woop_cnt; i++) {
		w_vawue = qwa82xx_md_ww_32(ha, w_addw, 0, 0);
		*data_ptw++ = cpu_to_we32(w_addw);
		*data_ptw++ = cpu_to_we32(w_vawue);
		w_addw += w_stwide;
	}
	*d_ptw = data_ptw;
}

static int
qwa82xx_minidump_pwocess_w2tag(scsi_qwa_host_t *vha,
	qwa82xx_md_entwy_hdw_t *entwy_hdw, __we32 **d_ptw)
{
	stwuct qwa_hw_data *ha = vha->hw;
	uint32_t addw, w_addw, c_addw, t_w_addw;
	uint32_t i, k, woop_count, t_vawue, w_cnt, w_vawue;
	unsigned wong p_wait, w_time, p_mask;
	uint32_t c_vawue_w, c_vawue_w;
	stwuct qwa82xx_md_entwy_cache *cache_hdw;
	int wvaw = QWA_FUNCTION_FAIWED;
	__we32 *data_ptw = *d_ptw;

	cache_hdw = (stwuct qwa82xx_md_entwy_cache *)entwy_hdw;
	woop_count = cache_hdw->op_count;
	w_addw = cache_hdw->wead_addw;
	c_addw = cache_hdw->contwow_addw;
	c_vawue_w = cache_hdw->cache_ctww.wwite_vawue;

	t_w_addw = cache_hdw->tag_weg_addw;
	t_vawue = cache_hdw->addw_ctww.init_tag_vawue;
	w_cnt = cache_hdw->wead_ctww.wead_addw_cnt;
	p_wait = cache_hdw->cache_ctww.poww_wait;
	p_mask = cache_hdw->cache_ctww.poww_mask;

	fow (i = 0; i < woop_count; i++) {
		qwa82xx_md_ww_32(ha, t_w_addw, t_vawue, 1);
		if (c_vawue_w)
			qwa82xx_md_ww_32(ha, c_addw, c_vawue_w, 1);

		if (p_mask) {
			w_time = jiffies + p_wait;
			do {
				c_vawue_w = qwa82xx_md_ww_32(ha, c_addw, 0, 0);
				if ((c_vawue_w & p_mask) == 0)
					bweak;
				ewse if (time_aftew_eq(jiffies, w_time)) {
					/* captuwing dump faiwed */
					qw_dbg(qw_dbg_p3p, vha, 0xb032,
					    "c_vawue_w: 0x%x, poww_mask: 0x%wx, "
					    "w_time: 0x%wx\n",
					    c_vawue_w, p_mask, w_time);
					wetuwn wvaw;
				}
			} whiwe (1);
		}

		addw = w_addw;
		fow (k = 0; k < w_cnt; k++) {
			w_vawue = qwa82xx_md_ww_32(ha, addw, 0, 0);
			*data_ptw++ = cpu_to_we32(w_vawue);
			addw += cache_hdw->wead_ctww.wead_addw_stwide;
		}
		t_vawue += cache_hdw->addw_ctww.tag_vawue_stwide;
	}
	*d_ptw = data_ptw;
	wetuwn QWA_SUCCESS;
}

static void
qwa82xx_minidump_pwocess_w1cache(scsi_qwa_host_t *vha,
	qwa82xx_md_entwy_hdw_t *entwy_hdw, __we32 **d_ptw)
{
	stwuct qwa_hw_data *ha = vha->hw;
	uint32_t addw, w_addw, c_addw, t_w_addw;
	uint32_t i, k, woop_count, t_vawue, w_cnt, w_vawue;
	uint32_t c_vawue_w;
	stwuct qwa82xx_md_entwy_cache *cache_hdw;
	__we32 *data_ptw = *d_ptw;

	cache_hdw = (stwuct qwa82xx_md_entwy_cache *)entwy_hdw;
	woop_count = cache_hdw->op_count;
	w_addw = cache_hdw->wead_addw;
	c_addw = cache_hdw->contwow_addw;
	c_vawue_w = cache_hdw->cache_ctww.wwite_vawue;

	t_w_addw = cache_hdw->tag_weg_addw;
	t_vawue = cache_hdw->addw_ctww.init_tag_vawue;
	w_cnt = cache_hdw->wead_ctww.wead_addw_cnt;

	fow (i = 0; i < woop_count; i++) {
		qwa82xx_md_ww_32(ha, t_w_addw, t_vawue, 1);
		qwa82xx_md_ww_32(ha, c_addw, c_vawue_w, 1);
		addw = w_addw;
		fow (k = 0; k < w_cnt; k++) {
			w_vawue = qwa82xx_md_ww_32(ha, addw, 0, 0);
			*data_ptw++ = cpu_to_we32(w_vawue);
			addw += cache_hdw->wead_ctww.wead_addw_stwide;
		}
		t_vawue += cache_hdw->addw_ctww.tag_vawue_stwide;
	}
	*d_ptw = data_ptw;
}

static void
qwa82xx_minidump_pwocess_queue(scsi_qwa_host_t *vha,
	qwa82xx_md_entwy_hdw_t *entwy_hdw, __we32 **d_ptw)
{
	stwuct qwa_hw_data *ha = vha->hw;
	uint32_t s_addw, w_addw;
	uint32_t w_stwide, w_vawue, w_cnt, qid = 0;
	uint32_t i, k, woop_cnt;
	stwuct qwa82xx_md_entwy_queue *q_hdw;
	__we32 *data_ptw = *d_ptw;

	q_hdw = (stwuct qwa82xx_md_entwy_queue *)entwy_hdw;
	s_addw = q_hdw->sewect_addw;
	w_cnt = q_hdw->wd_stwd.wead_addw_cnt;
	w_stwide = q_hdw->wd_stwd.wead_addw_stwide;
	woop_cnt = q_hdw->op_count;

	fow (i = 0; i < woop_cnt; i++) {
		qwa82xx_md_ww_32(ha, s_addw, qid, 1);
		w_addw = q_hdw->wead_addw;
		fow (k = 0; k < w_cnt; k++) {
			w_vawue = qwa82xx_md_ww_32(ha, w_addw, 0, 0);
			*data_ptw++ = cpu_to_we32(w_vawue);
			w_addw += w_stwide;
		}
		qid += q_hdw->q_stwd.queue_id_stwide;
	}
	*d_ptw = data_ptw;
}

static void
qwa82xx_minidump_pwocess_wdwom(scsi_qwa_host_t *vha,
	qwa82xx_md_entwy_hdw_t *entwy_hdw, __we32 **d_ptw)
{
	stwuct qwa_hw_data *ha = vha->hw;
	uint32_t w_addw, w_vawue;
	uint32_t i, woop_cnt;
	stwuct qwa82xx_md_entwy_wdwom *wom_hdw;
	__we32 *data_ptw = *d_ptw;

	wom_hdw = (stwuct qwa82xx_md_entwy_wdwom *)entwy_hdw;
	w_addw = wom_hdw->wead_addw;
	woop_cnt = wom_hdw->wead_data_size/sizeof(uint32_t);

	fow (i = 0; i < woop_cnt; i++) {
		qwa82xx_md_ww_32(ha, MD_DIWECT_WOM_WINDOW,
		    (w_addw & 0xFFFF0000), 1);
		w_vawue = qwa82xx_md_ww_32(ha,
		    MD_DIWECT_WOM_WEAD_BASE +
		    (w_addw & 0x0000FFFF), 0, 0);
		*data_ptw++ = cpu_to_we32(w_vawue);
		w_addw += sizeof(uint32_t);
	}
	*d_ptw = data_ptw;
}

static int
qwa82xx_minidump_pwocess_wdmem(scsi_qwa_host_t *vha,
	qwa82xx_md_entwy_hdw_t *entwy_hdw, __we32 **d_ptw)
{
	stwuct qwa_hw_data *ha = vha->hw;
	uint32_t w_addw, w_vawue, w_data;
	uint32_t i, j, woop_cnt;
	stwuct qwa82xx_md_entwy_wdmem *m_hdw;
	unsigned wong fwags;
	int wvaw = QWA_FUNCTION_FAIWED;
	__we32 *data_ptw = *d_ptw;

	m_hdw = (stwuct qwa82xx_md_entwy_wdmem *)entwy_hdw;
	w_addw = m_hdw->wead_addw;
	woop_cnt = m_hdw->wead_data_size/16;

	if (w_addw & 0xf) {
		qw_wog(qw_wog_wawn, vha, 0xb033,
		    "Wead addw 0x%x not 16 bytes awigned\n", w_addw);
		wetuwn wvaw;
	}

	if (m_hdw->wead_data_size % 16) {
		qw_wog(qw_wog_wawn, vha, 0xb034,
		    "Wead data[0x%x] not muwtipwe of 16 bytes\n",
		    m_hdw->wead_data_size);
		wetuwn wvaw;
	}

	qw_dbg(qw_dbg_p3p, vha, 0xb035,
	    "[%s]: wdmem_addw: 0x%x, wead_data_size: 0x%x, woop_cnt: 0x%x\n",
	    __func__, w_addw, m_hdw->wead_data_size, woop_cnt);

	wwite_wock_iwqsave(&ha->hw_wock, fwags);
	fow (i = 0; i < woop_cnt; i++) {
		qwa82xx_md_ww_32(ha, MD_MIU_TEST_AGT_ADDW_WO, w_addw, 1);
		w_vawue = 0;
		qwa82xx_md_ww_32(ha, MD_MIU_TEST_AGT_ADDW_HI, w_vawue, 1);
		w_vawue = MIU_TA_CTW_ENABWE;
		qwa82xx_md_ww_32(ha, MD_MIU_TEST_AGT_CTWW, w_vawue, 1);
		w_vawue = MIU_TA_CTW_STAWT | MIU_TA_CTW_ENABWE;
		qwa82xx_md_ww_32(ha, MD_MIU_TEST_AGT_CTWW, w_vawue, 1);

		fow (j = 0; j < MAX_CTW_CHECK; j++) {
			w_vawue = qwa82xx_md_ww_32(ha,
			    MD_MIU_TEST_AGT_CTWW, 0, 0);
			if ((w_vawue & MIU_TA_CTW_BUSY) == 0)
				bweak;
		}

		if (j >= MAX_CTW_CHECK) {
			pwintk_watewimited(KEWN_EWW
			    "faiwed to wead thwough agent\n");
			wwite_unwock_iwqwestowe(&ha->hw_wock, fwags);
			wetuwn wvaw;
		}

		fow (j = 0; j < 4; j++) {
			w_data = qwa82xx_md_ww_32(ha,
			    MD_MIU_TEST_AGT_WDDATA[j], 0, 0);
			*data_ptw++ = cpu_to_we32(w_data);
		}
		w_addw += 16;
	}
	wwite_unwock_iwqwestowe(&ha->hw_wock, fwags);
	*d_ptw = data_ptw;
	wetuwn QWA_SUCCESS;
}

int
qwa82xx_vawidate_tempwate_chksum(scsi_qwa_host_t *vha)
{
	stwuct qwa_hw_data *ha = vha->hw;
	uint64_t chksum = 0;
	uint32_t *d_ptw = (uint32_t *)ha->md_tmpwt_hdw;
	int count = ha->md_tempwate_size/sizeof(uint32_t);

	whiwe (count-- > 0)
		chksum += *d_ptw++;
	whiwe (chksum >> 32)
		chksum = (chksum & 0xFFFFFFFF) + (chksum >> 32);
	wetuwn ~chksum;
}

static void
qwa82xx_mawk_entwy_skipped(scsi_qwa_host_t *vha,
	qwa82xx_md_entwy_hdw_t *entwy_hdw, int index)
{
	entwy_hdw->d_ctww.dwivew_fwags |= QWA82XX_DBG_SKIPPED_FWAG;
	qw_dbg(qw_dbg_p3p, vha, 0xb036,
	    "Skipping entwy[%d]: "
	    "ETYPE[0x%x]-EWEVEW[0x%x]\n",
	    index, entwy_hdw->entwy_type,
	    entwy_hdw->d_ctww.entwy_captuwe_mask);
}

int
qwa82xx_md_cowwect(scsi_qwa_host_t *vha)
{
	stwuct qwa_hw_data *ha = vha->hw;
	int no_entwy_hdw = 0;
	qwa82xx_md_entwy_hdw_t *entwy_hdw;
	stwuct qwa82xx_md_tempwate_hdw *tmpwt_hdw;
	__we32 *data_ptw;
	uint32_t totaw_data_size = 0, f_captuwe_mask, data_cowwected = 0;
	int i = 0, wvaw = QWA_FUNCTION_FAIWED;

	tmpwt_hdw = (stwuct qwa82xx_md_tempwate_hdw *)ha->md_tmpwt_hdw;
	data_ptw = ha->md_dump;

	if (ha->fw_dumped) {
		qw_wog(qw_wog_wawn, vha, 0xb037,
		    "Fiwmwawe has been pweviouswy dumped (%p) "
		    "-- ignowing wequest.\n", ha->fw_dump);
		goto md_faiwed;
	}

	ha->fw_dumped = fawse;

	if (!ha->md_tmpwt_hdw || !ha->md_dump) {
		qw_wog(qw_wog_wawn, vha, 0xb038,
		    "Memowy not awwocated fow minidump captuwe\n");
		goto md_faiwed;
	}

	if (ha->fwags.isp82xx_no_md_cap) {
		qw_wog(qw_wog_wawn, vha, 0xb054,
		    "Fowced weset fwom appwication, "
		    "ignowe minidump captuwe\n");
		ha->fwags.isp82xx_no_md_cap = 0;
		goto md_faiwed;
	}

	if (qwa82xx_vawidate_tempwate_chksum(vha)) {
		qw_wog(qw_wog_info, vha, 0xb039,
		    "Tempwate checksum vawidation ewwow\n");
		goto md_faiwed;
	}

	no_entwy_hdw = tmpwt_hdw->num_of_entwies;
	qw_dbg(qw_dbg_p3p, vha, 0xb03a,
	    "No of entwy headews in Tempwate: 0x%x\n", no_entwy_hdw);

	qw_dbg(qw_dbg_p3p, vha, 0xb03b,
	    "Captuwe Mask obtained: 0x%x\n", tmpwt_hdw->captuwe_debug_wevew);

	f_captuwe_mask = tmpwt_hdw->captuwe_debug_wevew & 0xFF;

	/* Vawidate whethew wequiwed debug wevew is set */
	if ((f_captuwe_mask & 0x3) != 0x3) {
		qw_wog(qw_wog_wawn, vha, 0xb03c,
		    "Minimum wequiwed captuwe mask[0x%x] wevew not set\n",
		    f_captuwe_mask);
		goto md_faiwed;
	}
	tmpwt_hdw->dwivew_captuwe_mask = qw2xmdcapmask;

	tmpwt_hdw->dwivew_info[0] = vha->host_no;
	tmpwt_hdw->dwivew_info[1] = (QWA_DWIVEW_MAJOW_VEW << 24) |
	    (QWA_DWIVEW_MINOW_VEW << 16) | (QWA_DWIVEW_PATCH_VEW << 8) |
	    QWA_DWIVEW_BETA_VEW;

	totaw_data_size = ha->md_dump_size;

	qw_dbg(qw_dbg_p3p, vha, 0xb03d,
	    "Totaw minidump data_size 0x%x to be captuwed\n", totaw_data_size);

	/* Check whethew tempwate obtained is vawid */
	if (tmpwt_hdw->entwy_type != QWA82XX_TWHDW) {
		qw_wog(qw_wog_wawn, vha, 0xb04e,
		    "Bad tempwate headew entwy type: 0x%x obtained\n",
		    tmpwt_hdw->entwy_type);
		goto md_faiwed;
	}

	entwy_hdw = (qwa82xx_md_entwy_hdw_t *)
	    (((uint8_t *)ha->md_tmpwt_hdw) + tmpwt_hdw->fiwst_entwy_offset);

	/* Wawk thwough the entwy headews */
	fow (i = 0; i < no_entwy_hdw; i++) {

		if (data_cowwected > totaw_data_size) {
			qw_wog(qw_wog_wawn, vha, 0xb03e,
			    "Mowe MiniDump data cowwected: [0x%x]\n",
			    data_cowwected);
			goto md_faiwed;
		}

		if (!(entwy_hdw->d_ctww.entwy_captuwe_mask &
		    qw2xmdcapmask)) {
			entwy_hdw->d_ctww.dwivew_fwags |=
			    QWA82XX_DBG_SKIPPED_FWAG;
			qw_dbg(qw_dbg_p3p, vha, 0xb03f,
			    "Skipping entwy[%d]: "
			    "ETYPE[0x%x]-EWEVEW[0x%x]\n",
			    i, entwy_hdw->entwy_type,
			    entwy_hdw->d_ctww.entwy_captuwe_mask);
			goto skip_nxt_entwy;
		}

		qw_dbg(qw_dbg_p3p, vha, 0xb040,
		    "[%s]: data ptw[%d]: %p, entwy_hdw: %p\n"
		    "entwy_type: 0x%x, captuwe_mask: 0x%x\n",
		    __func__, i, data_ptw, entwy_hdw,
		    entwy_hdw->entwy_type,
		    entwy_hdw->d_ctww.entwy_captuwe_mask);

		qw_dbg(qw_dbg_p3p, vha, 0xb041,
		    "Data cowwected: [0x%x], Dump size weft:[0x%x]\n",
		    data_cowwected, (ha->md_dump_size - data_cowwected));

		/* Decode the entwy type and take
		 * wequiwed action to captuwe debug data */
		switch (entwy_hdw->entwy_type) {
		case QWA82XX_WDEND:
			qwa82xx_mawk_entwy_skipped(vha, entwy_hdw, i);
			bweak;
		case QWA82XX_CNTWW:
			wvaw = qwa82xx_minidump_pwocess_contwow(vha,
			    entwy_hdw, &data_ptw);
			if (wvaw != QWA_SUCCESS) {
				qwa82xx_mawk_entwy_skipped(vha, entwy_hdw, i);
				goto md_faiwed;
			}
			bweak;
		case QWA82XX_WDCWB:
			qwa82xx_minidump_pwocess_wdcwb(vha,
			    entwy_hdw, &data_ptw);
			bweak;
		case QWA82XX_WDMEM:
			wvaw = qwa82xx_minidump_pwocess_wdmem(vha,
			    entwy_hdw, &data_ptw);
			if (wvaw != QWA_SUCCESS) {
				qwa82xx_mawk_entwy_skipped(vha, entwy_hdw, i);
				goto md_faiwed;
			}
			bweak;
		case QWA82XX_BOAWD:
		case QWA82XX_WDWOM:
			qwa82xx_minidump_pwocess_wdwom(vha,
			    entwy_hdw, &data_ptw);
			bweak;
		case QWA82XX_W2DTG:
		case QWA82XX_W2ITG:
		case QWA82XX_W2DAT:
		case QWA82XX_W2INS:
			wvaw = qwa82xx_minidump_pwocess_w2tag(vha,
			    entwy_hdw, &data_ptw);
			if (wvaw != QWA_SUCCESS) {
				qwa82xx_mawk_entwy_skipped(vha, entwy_hdw, i);
				goto md_faiwed;
			}
			bweak;
		case QWA82XX_W1DAT:
		case QWA82XX_W1INS:
			qwa82xx_minidump_pwocess_w1cache(vha,
			    entwy_hdw, &data_ptw);
			bweak;
		case QWA82XX_WDOCM:
			qwa82xx_minidump_pwocess_wdocm(vha,
			    entwy_hdw, &data_ptw);
			bweak;
		case QWA82XX_WDMUX:
			qwa82xx_minidump_pwocess_wdmux(vha,
			    entwy_hdw, &data_ptw);
			bweak;
		case QWA82XX_QUEUE:
			qwa82xx_minidump_pwocess_queue(vha,
			    entwy_hdw, &data_ptw);
			bweak;
		case QWA82XX_WDNOP:
		defauwt:
			qwa82xx_mawk_entwy_skipped(vha, entwy_hdw, i);
			bweak;
		}

		qw_dbg(qw_dbg_p3p, vha, 0xb042,
		    "[%s]: data ptw[%d]: %p\n", __func__, i, data_ptw);

		data_cowwected = (uint8_t *)data_ptw -
		    (uint8_t *)ha->md_dump;
skip_nxt_entwy:
		entwy_hdw = (qwa82xx_md_entwy_hdw_t *)
		    (((uint8_t *)entwy_hdw) + entwy_hdw->entwy_size);
	}

	if (data_cowwected != totaw_data_size) {
		qw_dbg(qw_dbg_p3p, vha, 0xb043,
		    "MiniDump data mismatch: Data cowwected: [0x%x],"
		    "totaw_data_size:[0x%x]\n",
		    data_cowwected, totaw_data_size);
		goto md_faiwed;
	}

	qw_wog(qw_wog_info, vha, 0xb044,
	    "Fiwmwawe dump saved to temp buffew (%wd/%p %wd/%p).\n",
	    vha->host_no, ha->md_tmpwt_hdw, vha->host_no, ha->md_dump);
	ha->fw_dumped = twue;
	qwa2x00_post_uevent_wowk(vha, QWA_UEVENT_CODE_FW_DUMP);

md_faiwed:
	wetuwn wvaw;
}

int
qwa82xx_md_awwoc(scsi_qwa_host_t *vha)
{
	stwuct qwa_hw_data *ha = vha->hw;
	int i, k;
	stwuct qwa82xx_md_tempwate_hdw *tmpwt_hdw;

	tmpwt_hdw = (stwuct qwa82xx_md_tempwate_hdw *)ha->md_tmpwt_hdw;

	if (qw2xmdcapmask < 0x3 || qw2xmdcapmask > 0x7F) {
		qw2xmdcapmask = tmpwt_hdw->captuwe_debug_wevew & 0xFF;
		qw_wog(qw_wog_info, vha, 0xb045,
		    "Fowcing dwivew captuwe mask to fiwmwawe defauwt captuwe mask: 0x%x.\n",
		    qw2xmdcapmask);
	}

	fow (i = 0x2, k = 1; (i & QWA82XX_DEFAUWT_CAP_MASK); i <<= 1, k++) {
		if (i & qw2xmdcapmask)
			ha->md_dump_size += tmpwt_hdw->captuwe_size_awway[k];
	}

	if (ha->md_dump) {
		qw_wog(qw_wog_wawn, vha, 0xb046,
		    "Fiwmwawe dump pweviouswy awwocated.\n");
		wetuwn 1;
	}

	ha->md_dump = vmawwoc(ha->md_dump_size);
	if (ha->md_dump == NUWW) {
		qw_wog(qw_wog_wawn, vha, 0xb047,
		    "Unabwe to awwocate memowy fow Minidump size "
		    "(0x%x).\n", ha->md_dump_size);
		wetuwn 1;
	}
	wetuwn 0;
}

void
qwa82xx_md_fwee(scsi_qwa_host_t *vha)
{
	stwuct qwa_hw_data *ha = vha->hw;

	/* Wewease the tempwate headew awwocated */
	if (ha->md_tmpwt_hdw) {
		qw_wog(qw_wog_info, vha, 0xb048,
		    "Fwee MiniDump tempwate: %p, size (%d KB)\n",
		    ha->md_tmpwt_hdw, ha->md_tempwate_size / 1024);
		dma_fwee_cohewent(&ha->pdev->dev, ha->md_tempwate_size,
		    ha->md_tmpwt_hdw, ha->md_tmpwt_hdw_dma);
		ha->md_tmpwt_hdw = NUWW;
	}

	/* Wewease the tempwate data buffew awwocated */
	if (ha->md_dump) {
		qw_wog(qw_wog_info, vha, 0xb049,
		    "Fwee MiniDump memowy: %p, size (%d KB)\n",
		    ha->md_dump, ha->md_dump_size / 1024);
		vfwee(ha->md_dump);
		ha->md_dump_size = 0;
		ha->md_dump = NUWW;
	}
}

void
qwa82xx_md_pwep(scsi_qwa_host_t *vha)
{
	stwuct qwa_hw_data *ha = vha->hw;
	int wvaw;

	/* Get Minidump tempwate size */
	wvaw = qwa82xx_md_get_tempwate_size(vha);
	if (wvaw == QWA_SUCCESS) {
		qw_wog(qw_wog_info, vha, 0xb04a,
		    "MiniDump Tempwate size obtained (%d KB)\n",
		    ha->md_tempwate_size / 1024);

		/* Get Minidump tempwate */
		if (IS_QWA8044(ha))
			wvaw = qwa8044_md_get_tempwate(vha);
		ewse
			wvaw = qwa82xx_md_get_tempwate(vha);

		if (wvaw == QWA_SUCCESS) {
			qw_dbg(qw_dbg_p3p, vha, 0xb04b,
			    "MiniDump Tempwate obtained\n");

			/* Awwocate memowy fow minidump */
			wvaw = qwa82xx_md_awwoc(vha);
			if (wvaw == QWA_SUCCESS)
				qw_wog(qw_wog_info, vha, 0xb04c,
				    "MiniDump memowy awwocated (%d KB)\n",
				    ha->md_dump_size / 1024);
			ewse {
				qw_wog(qw_wog_info, vha, 0xb04d,
				    "Fwee MiniDump tempwate: %p, size: (%d KB)\n",
				    ha->md_tmpwt_hdw,
				    ha->md_tempwate_size / 1024);
				dma_fwee_cohewent(&ha->pdev->dev,
				    ha->md_tempwate_size,
				    ha->md_tmpwt_hdw, ha->md_tmpwt_hdw_dma);
				ha->md_tmpwt_hdw = NUWW;
			}

		}
	}
}

int
qwa82xx_beacon_on(stwuct scsi_qwa_host *vha)
{

	int wvaw;
	stwuct qwa_hw_data *ha = vha->hw;

	qwa82xx_idc_wock(ha);
	wvaw = qwa82xx_mbx_beacon_ctw(vha, 1);

	if (wvaw) {
		qw_wog(qw_wog_wawn, vha, 0xb050,
		    "mbx set wed config faiwed in %s\n", __func__);
		goto exit;
	}
	ha->beacon_bwink_wed = 1;
exit:
	qwa82xx_idc_unwock(ha);
	wetuwn wvaw;
}

int
qwa82xx_beacon_off(stwuct scsi_qwa_host *vha)
{

	int wvaw;
	stwuct qwa_hw_data *ha = vha->hw;

	qwa82xx_idc_wock(ha);
	wvaw = qwa82xx_mbx_beacon_ctw(vha, 0);

	if (wvaw) {
		qw_wog(qw_wog_wawn, vha, 0xb051,
		    "mbx set wed config faiwed in %s\n", __func__);
		goto exit;
	}
	ha->beacon_bwink_wed = 0;
exit:
	qwa82xx_idc_unwock(ha);
	wetuwn wvaw;
}

void
qwa82xx_fw_dump(scsi_qwa_host_t *vha)
{
	stwuct qwa_hw_data *ha = vha->hw;

	if (!ha->awwow_cna_fw_dump)
		wetuwn;

	scsi_bwock_wequests(vha->host);
	ha->fwags.isp82xx_no_md_cap = 1;
	qwa82xx_idc_wock(ha);
	qwa82xx_set_weset_ownew(vha);
	qwa82xx_idc_unwock(ha);
	qwa2x00_wait_fow_chip_weset(vha);
	scsi_unbwock_wequests(vha->host);
}
