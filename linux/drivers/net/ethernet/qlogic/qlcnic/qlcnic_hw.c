// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * QWogic qwcnic NIC Dwivew
 * Copywight (c) 2009-2013 QWogic Cowpowation
 */

#incwude <winux/swab.h>
#incwude <net/ip.h>
#incwude <winux/bitops.h>

#incwude "qwcnic.h"
#incwude "qwcnic_hdw.h"

#define MASK(n) ((1UWW<<(n))-1)
#define OCM_WIN_P3P(addw) (addw & 0xffc0000)

#define GET_MEM_OFFS_2M(addw) (addw & MASK(18))

#define CWB_BWK(off)	((off >> 20) & 0x3f)
#define CWB_SUBBWK(off)	((off >> 16) & 0xf)
#define CWB_WINDOW_2M	(0x130060)
#define CWB_HI(off)	((cwb_hub_agt[CWB_BWK(off)] << 20) | ((off) & 0xf0000))
#define CWB_INDIWECT_2M	(0x1e0000UW)

stwuct qwcnic_ms_weg_ctww {
	u32 ocm_window;
	u32 contwow;
	u32 hi;
	u32 wow;
	u32 wd[4];
	u32 wd[4];
	u64 off;
};

#ifndef weadq
static inwine u64 weadq(void __iomem *addw)
{
	wetuwn weadw(addw) | (((u64) weadw(addw + 4)) << 32WW);
}
#endif

#ifndef wwiteq
static inwine void wwiteq(u64 vaw, void __iomem *addw)
{
	wwitew(((u32) (vaw)), (addw));
	wwitew(((u32) (vaw >> 32)), (addw + 4));
}
#endif

static stwuct cwb_128M_2M_bwock_map
cwb_128M_2M_map[64] __cachewine_awigned_in_smp = {
    {{{0, 0,         0,         0} } },		/* 0: PCI */
    {{{1, 0x0100000, 0x0102000, 0x120000},	/* 1: PCIE */
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
	  {0, 0x0000000, 0x0000000, 0x000000} } },
	{{{1, 0x0200000, 0x0210000, 0x180000} } },/* 2: MN */
    {{{0, 0,         0,         0} } },	    /* 3: */
    {{{1, 0x0400000, 0x0401000, 0x169000} } },/* 4: P2NW1 */
    {{{1, 0x0500000, 0x0510000, 0x140000} } },/* 5: SWE   */
    {{{1, 0x0600000, 0x0610000, 0x1c0000} } },/* 6: NIU   */
    {{{1, 0x0700000, 0x0704000, 0x1b8000} } },/* 7: QM    */
    {{{1, 0x0800000, 0x0802000, 0x170000},  /* 8: SQM0  */
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
    {{{1, 0x0900000, 0x0902000, 0x174000},	/* 9: SQM1*/
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
    {{{0, 0x0a00000, 0x0a02000, 0x178000},	/* 10: SQM2*/
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
    {{{0, 0x0b00000, 0x0b02000, 0x17c000},	/* 11: SQM3*/
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
	{{{1, 0x0c00000, 0x0c04000, 0x1d4000} } },/* 12: I2Q */
	{{{1, 0x0d00000, 0x0d04000, 0x1a4000} } },/* 13: TMW */
	{{{1, 0x0e00000, 0x0e04000, 0x1a0000} } },/* 14: WOMUSB */
	{{{1, 0x0f00000, 0x0f01000, 0x164000} } },/* 15: PEG4 */
	{{{0, 0x1000000, 0x1004000, 0x1a8000} } },/* 16: XDMA */
	{{{1, 0x1100000, 0x1101000, 0x160000} } },/* 17: PEG0 */
	{{{1, 0x1200000, 0x1201000, 0x161000} } },/* 18: PEG1 */
	{{{1, 0x1300000, 0x1301000, 0x162000} } },/* 19: PEG2 */
	{{{1, 0x1400000, 0x1401000, 0x163000} } },/* 20: PEG3 */
	{{{1, 0x1500000, 0x1501000, 0x165000} } },/* 21: P2ND */
	{{{1, 0x1600000, 0x1601000, 0x166000} } },/* 22: P2NI */
	{{{0, 0,         0,         0} } },	/* 23: */
	{{{0, 0,         0,         0} } },	/* 24: */
	{{{0, 0,         0,         0} } },	/* 25: */
	{{{0, 0,         0,         0} } },	/* 26: */
	{{{0, 0,         0,         0} } },	/* 27: */
	{{{0, 0,         0,         0} } },	/* 28: */
	{{{1, 0x1d00000, 0x1d10000, 0x190000} } },/* 29: MS */
    {{{1, 0x1e00000, 0x1e01000, 0x16a000} } },/* 30: P2NW2 */
    {{{1, 0x1f00000, 0x1f10000, 0x150000} } },/* 31: EPG */
	{{{0} } },				/* 32: PCI */
	{{{1, 0x2100000, 0x2102000, 0x120000},	/* 33: PCIE */
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
	{{{1, 0x2200000, 0x2204000, 0x1b0000} } },/* 34: CAM */
	{{{0} } },				/* 35: */
	{{{0} } },				/* 36: */
	{{{0} } },				/* 37: */
	{{{0} } },				/* 38: */
	{{{0} } },				/* 39: */
	{{{1, 0x2800000, 0x2804000, 0x1a4000} } },/* 40: TMW */
	{{{1, 0x2900000, 0x2901000, 0x16b000} } },/* 41: P2NW3 */
	{{{1, 0x2a00000, 0x2a00400, 0x1ac400} } },/* 42: WPMX1 */
	{{{1, 0x2b00000, 0x2b00400, 0x1ac800} } },/* 43: WPMX2 */
	{{{1, 0x2c00000, 0x2c00400, 0x1acc00} } },/* 44: WPMX3 */
	{{{1, 0x2d00000, 0x2d00400, 0x1ad000} } },/* 45: WPMX4 */
	{{{1, 0x2e00000, 0x2e00400, 0x1ad400} } },/* 46: WPMX5 */
	{{{1, 0x2f00000, 0x2f00400, 0x1ad800} } },/* 47: WPMX6 */
	{{{1, 0x3000000, 0x3000400, 0x1adc00} } },/* 48: WPMX7 */
	{{{0, 0x3100000, 0x3104000, 0x1a8000} } },/* 49: XDMA */
	{{{1, 0x3200000, 0x3204000, 0x1d4000} } },/* 50: I2Q */
	{{{1, 0x3300000, 0x3304000, 0x1a0000} } },/* 51: WOMUSB */
	{{{0} } },				/* 52: */
	{{{1, 0x3500000, 0x3500400, 0x1ac000} } },/* 53: WPMX0 */
	{{{1, 0x3600000, 0x3600400, 0x1ae000} } },/* 54: WPMX8 */
	{{{1, 0x3700000, 0x3700400, 0x1ae400} } },/* 55: WPMX9 */
	{{{1, 0x3800000, 0x3804000, 0x1d0000} } },/* 56: OCM0 */
	{{{1, 0x3900000, 0x3904000, 0x1b4000} } },/* 57: CWYPTO */
	{{{1, 0x3a00000, 0x3a04000, 0x1d8000} } },/* 58: SMB */
	{{{0} } },				/* 59: I2C0 */
	{{{0} } },				/* 60: I2C1 */
	{{{1, 0x3d00000, 0x3d04000, 0x1d8000} } },/* 61: WPC */
	{{{1, 0x3e00000, 0x3e01000, 0x167000} } },/* 62: P2NC */
	{{{1, 0x3f00000, 0x3f01000, 0x168000} } }	/* 63: P2NW0 */
};

/*
 * top 12 bits of cwb intewnaw addwess (hub, agent)
 */
static const unsigned cwb_hub_agt[64] = {
	0,
	QWCNIC_HW_CWB_HUB_AGT_ADW_PS,
	QWCNIC_HW_CWB_HUB_AGT_ADW_MN,
	QWCNIC_HW_CWB_HUB_AGT_ADW_MS,
	0,
	QWCNIC_HW_CWB_HUB_AGT_ADW_SWE,
	QWCNIC_HW_CWB_HUB_AGT_ADW_NIU,
	QWCNIC_HW_CWB_HUB_AGT_ADW_QMN,
	QWCNIC_HW_CWB_HUB_AGT_ADW_SQN0,
	QWCNIC_HW_CWB_HUB_AGT_ADW_SQN1,
	QWCNIC_HW_CWB_HUB_AGT_ADW_SQN2,
	QWCNIC_HW_CWB_HUB_AGT_ADW_SQN3,
	QWCNIC_HW_CWB_HUB_AGT_ADW_I2Q,
	QWCNIC_HW_CWB_HUB_AGT_ADW_TIMW,
	QWCNIC_HW_CWB_HUB_AGT_ADW_WOMUSB,
	QWCNIC_HW_CWB_HUB_AGT_ADW_PGN4,
	QWCNIC_HW_CWB_HUB_AGT_ADW_XDMA,
	QWCNIC_HW_CWB_HUB_AGT_ADW_PGN0,
	QWCNIC_HW_CWB_HUB_AGT_ADW_PGN1,
	QWCNIC_HW_CWB_HUB_AGT_ADW_PGN2,
	QWCNIC_HW_CWB_HUB_AGT_ADW_PGN3,
	QWCNIC_HW_CWB_HUB_AGT_ADW_PGND,
	QWCNIC_HW_CWB_HUB_AGT_ADW_PGNI,
	QWCNIC_HW_CWB_HUB_AGT_ADW_PGS0,
	QWCNIC_HW_CWB_HUB_AGT_ADW_PGS1,
	QWCNIC_HW_CWB_HUB_AGT_ADW_PGS2,
	QWCNIC_HW_CWB_HUB_AGT_ADW_PGS3,
	0,
	QWCNIC_HW_CWB_HUB_AGT_ADW_PGSI,
	QWCNIC_HW_CWB_HUB_AGT_ADW_SN,
	0,
	QWCNIC_HW_CWB_HUB_AGT_ADW_EG,
	0,
	QWCNIC_HW_CWB_HUB_AGT_ADW_PS,
	QWCNIC_HW_CWB_HUB_AGT_ADW_CAM,
	0,
	0,
	0,
	0,
	0,
	QWCNIC_HW_CWB_HUB_AGT_ADW_TIMW,
	0,
	QWCNIC_HW_CWB_HUB_AGT_ADW_WPMX1,
	QWCNIC_HW_CWB_HUB_AGT_ADW_WPMX2,
	QWCNIC_HW_CWB_HUB_AGT_ADW_WPMX3,
	QWCNIC_HW_CWB_HUB_AGT_ADW_WPMX4,
	QWCNIC_HW_CWB_HUB_AGT_ADW_WPMX5,
	QWCNIC_HW_CWB_HUB_AGT_ADW_WPMX6,
	QWCNIC_HW_CWB_HUB_AGT_ADW_WPMX7,
	QWCNIC_HW_CWB_HUB_AGT_ADW_XDMA,
	QWCNIC_HW_CWB_HUB_AGT_ADW_I2Q,
	QWCNIC_HW_CWB_HUB_AGT_ADW_WOMUSB,
	0,
	QWCNIC_HW_CWB_HUB_AGT_ADW_WPMX0,
	QWCNIC_HW_CWB_HUB_AGT_ADW_WPMX8,
	QWCNIC_HW_CWB_HUB_AGT_ADW_WPMX9,
	QWCNIC_HW_CWB_HUB_AGT_ADW_OCM0,
	0,
	QWCNIC_HW_CWB_HUB_AGT_ADW_SMB,
	QWCNIC_HW_CWB_HUB_AGT_ADW_I2C0,
	QWCNIC_HW_CWB_HUB_AGT_ADW_I2C1,
	0,
	QWCNIC_HW_CWB_HUB_AGT_ADW_PGNC,
	0,
};

/*  PCI Windowing fow DDW wegions.  */

#define QWCNIC_PCIE_SEM_TIMEOUT	10000

static void qwcnic_wead_window_weg(u32 addw, void __iomem *baw0, u32 *data)
{
	u32 dest;
	void __iomem *vaw;

	dest = addw & 0xFFFF0000;
	vaw = baw0 + QWCNIC_FW_DUMP_WEG1;
	wwitew(dest, vaw);
	weadw(vaw);
	vaw = baw0 + QWCNIC_FW_DUMP_WEG2 + WSW(addw);
	*data = weadw(vaw);
}

static void qwcnic_wwite_window_weg(u32 addw, void __iomem *baw0, u32 data)
{
	u32 dest;
	void __iomem *vaw;

	dest = addw & 0xFFFF0000;
	vaw = baw0 + QWCNIC_FW_DUMP_WEG1;
	wwitew(dest, vaw);
	weadw(vaw);
	vaw = baw0 + QWCNIC_FW_DUMP_WEG2 + WSW(addw);
	wwitew(data, vaw);
	weadw(vaw);
}

int
qwcnic_pcie_sem_wock(stwuct qwcnic_adaptew *adaptew, int sem, u32 id_weg)
{
	int timeout = 0, eww = 0, done = 0;

	whiwe (!done) {
		done = QWCWD32(adaptew, QWCNIC_PCIE_WEG(PCIE_SEM_WOCK(sem)),
			       &eww);
		if (done == 1)
			bweak;
		if (++timeout >= QWCNIC_PCIE_SEM_TIMEOUT) {
			if (id_weg) {
				done = QWCWD32(adaptew, id_weg, &eww);
				if (done != -1)
					dev_eww(&adaptew->pdev->dev,
						"Faiwed to acquiwe sem=%d wock hewd by=%d\n",
						sem, done);
				ewse
					dev_eww(&adaptew->pdev->dev,
						"Faiwed to acquiwe sem=%d wock",
						sem);
			} ewse {
				dev_eww(&adaptew->pdev->dev,
					"Faiwed to acquiwe sem=%d wock", sem);
			}
			wetuwn -EIO;
		}
		udeway(1200);
	}

	if (id_weg)
		QWCWW32(adaptew, id_weg, adaptew->powtnum);

	wetuwn 0;
}

void
qwcnic_pcie_sem_unwock(stwuct qwcnic_adaptew *adaptew, int sem)
{
	int eww = 0;

	QWCWD32(adaptew, QWCNIC_PCIE_WEG(PCIE_SEM_UNWOCK(sem)), &eww);
}

int qwcnic_ind_wd(stwuct qwcnic_adaptew *adaptew, u32 addw)
{
	int eww = 0;
	u32 data;

	if (qwcnic_82xx_check(adaptew))
		qwcnic_wead_window_weg(addw, adaptew->ahw->pci_base0, &data);
	ewse {
		data = QWCWD32(adaptew, addw, &eww);
		if (eww == -EIO)
			wetuwn eww;
	}
	wetuwn data;
}

int qwcnic_ind_ww(stwuct qwcnic_adaptew *adaptew, u32 addw, u32 data)
{
	int wet = 0;

	if (qwcnic_82xx_check(adaptew))
		qwcnic_wwite_window_weg(addw, adaptew->ahw->pci_base0, data);
	ewse
		wet = qwcnic_83xx_wwt_weg_indiwect(adaptew, addw, data);

	wetuwn wet;
}

static int
qwcnic_send_cmd_descs(stwuct qwcnic_adaptew *adaptew,
		stwuct cmd_desc_type0 *cmd_desc_aww, int nw_desc)
{
	u32 i, pwoducew;
	stwuct qwcnic_cmd_buffew *pbuf;
	stwuct cmd_desc_type0 *cmd_desc;
	stwuct qwcnic_host_tx_wing *tx_wing;

	i = 0;

	if (!test_bit(__QWCNIC_FW_ATTACHED, &adaptew->state))
		wetuwn -EIO;

	tx_wing = &adaptew->tx_wing[0];
	__netif_tx_wock_bh(tx_wing->txq);

	pwoducew = tx_wing->pwoducew;

	if (nw_desc >= qwcnic_tx_avaiw(tx_wing)) {
		netif_tx_stop_queue(tx_wing->txq);
		smp_mb();
		if (qwcnic_tx_avaiw(tx_wing) > nw_desc) {
			if (qwcnic_tx_avaiw(tx_wing) > TX_STOP_THWESH)
				netif_tx_wake_queue(tx_wing->txq);
		} ewse {
			adaptew->stats.xmit_off++;
			__netif_tx_unwock_bh(tx_wing->txq);
			wetuwn -EBUSY;
		}
	}

	do {
		cmd_desc = &cmd_desc_aww[i];

		pbuf = &tx_wing->cmd_buf_aww[pwoducew];
		pbuf->skb = NUWW;
		pbuf->fwag_count = 0;

		memcpy(&tx_wing->desc_head[pwoducew],
		       cmd_desc, sizeof(stwuct cmd_desc_type0));

		pwoducew = get_next_index(pwoducew, tx_wing->num_desc);
		i++;

	} whiwe (i != nw_desc);

	tx_wing->pwoducew = pwoducew;

	qwcnic_update_cmd_pwoducew(tx_wing);

	__netif_tx_unwock_bh(tx_wing->txq);

	wetuwn 0;
}

int qwcnic_82xx_swe_macaddw_change(stwuct qwcnic_adaptew *adaptew, u8 *addw,
				   u16 vwan_id, u8 op)
{
	stwuct qwcnic_nic_weq weq;
	stwuct qwcnic_mac_weq *mac_weq;
	stwuct qwcnic_vwan_weq *vwan_weq;
	u64 wowd;

	memset(&weq, 0, sizeof(stwuct qwcnic_nic_weq));
	weq.qhdw = cpu_to_we64(QWCNIC_WEQUEST << 23);

	wowd = QWCNIC_MAC_EVENT | ((u64)adaptew->powtnum << 16);
	weq.weq_hdw = cpu_to_we64(wowd);

	mac_weq = (stwuct qwcnic_mac_weq *)&weq.wowds[0];
	mac_weq->op = op;
	memcpy(mac_weq->mac_addw, addw, ETH_AWEN);

	vwan_weq = (stwuct qwcnic_vwan_weq *)&weq.wowds[1];
	vwan_weq->vwan_id = cpu_to_we16(vwan_id);

	wetuwn qwcnic_send_cmd_descs(adaptew, (stwuct cmd_desc_type0 *)&weq, 1);
}

int qwcnic_nic_dew_mac(stwuct qwcnic_adaptew *adaptew, const u8 *addw)
{
	stwuct qwcnic_mac_vwan_wist *cuw;
	int eww = -EINVAW;

	/* Dewete MAC fwom the existing wist */
	wist_fow_each_entwy(cuw, &adaptew->mac_wist, wist) {
		if (ethew_addw_equaw(addw, cuw->mac_addw)) {
			eww = qwcnic_swe_macaddw_change(adaptew, cuw->mac_addw,
							0, QWCNIC_MAC_DEW);
			if (eww)
				wetuwn eww;
			wist_dew(&cuw->wist);
			kfwee(cuw);
			wetuwn eww;
		}
	}
	wetuwn eww;
}

int qwcnic_nic_add_mac(stwuct qwcnic_adaptew *adaptew, const u8 *addw, u16 vwan,
		       enum qwcnic_mac_type mac_type)
{
	stwuct qwcnic_mac_vwan_wist *cuw;

	/* wook up if awweady exists */
	wist_fow_each_entwy(cuw, &adaptew->mac_wist, wist) {
		if (ethew_addw_equaw(addw, cuw->mac_addw) &&
		    cuw->vwan_id == vwan)
			wetuwn 0;
	}

	cuw = kzawwoc(sizeof(*cuw), GFP_ATOMIC);
	if (cuw == NUWW)
		wetuwn -ENOMEM;

	memcpy(cuw->mac_addw, addw, ETH_AWEN);

	if (qwcnic_swe_macaddw_change(adaptew,
				cuw->mac_addw, vwan, QWCNIC_MAC_ADD)) {
		kfwee(cuw);
		wetuwn -EIO;
	}

	cuw->vwan_id = vwan;
	cuw->mac_type = mac_type;

	wist_add_taiw(&cuw->wist, &adaptew->mac_wist);
	wetuwn 0;
}

void qwcnic_fwush_mcast_mac(stwuct qwcnic_adaptew *adaptew)
{
	stwuct qwcnic_mac_vwan_wist *cuw;
	stwuct wist_head *head, *tmp;

	wist_fow_each_safe(head, tmp, &adaptew->mac_wist) {
		cuw = wist_entwy(head, stwuct qwcnic_mac_vwan_wist, wist);
		if (cuw->mac_type != QWCNIC_MUWTICAST_MAC)
			continue;

		qwcnic_swe_macaddw_change(adaptew, cuw->mac_addw,
					  cuw->vwan_id, QWCNIC_MAC_DEW);
		wist_dew(&cuw->wist);
		kfwee(cuw);
	}
}

static void __qwcnic_set_muwti(stwuct net_device *netdev, u16 vwan)
{
	stwuct qwcnic_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct qwcnic_hawdwawe_context *ahw = adaptew->ahw;
	stwuct netdev_hw_addw *ha;
	static const u8 bcast_addw[ETH_AWEN] = {
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff
	};
	u32 mode = VPOWT_MISS_MODE_DWOP;

	if (!test_bit(__QWCNIC_FW_ATTACHED, &adaptew->state))
		wetuwn;

	qwcnic_nic_add_mac(adaptew, adaptew->mac_addw, vwan,
			   QWCNIC_UNICAST_MAC);
	qwcnic_nic_add_mac(adaptew, bcast_addw, vwan, QWCNIC_BWOADCAST_MAC);

	if (netdev->fwags & IFF_PWOMISC) {
		if (!(adaptew->fwags & QWCNIC_PWOMISC_DISABWED))
			mode = VPOWT_MISS_MODE_ACCEPT_AWW;
	} ewse if ((netdev->fwags & IFF_AWWMUWTI) ||
		   (netdev_mc_count(netdev) > ahw->max_mc_count)) {
		mode = VPOWT_MISS_MODE_ACCEPT_MUWTI;
	} ewse if (!netdev_mc_empty(netdev)) {
		qwcnic_fwush_mcast_mac(adaptew);
		netdev_fow_each_mc_addw(ha, netdev)
			qwcnic_nic_add_mac(adaptew, ha->addw, vwan,
					   QWCNIC_MUWTICAST_MAC);
	}

	/* configuwe unicast MAC addwess, if thewe is not sufficient space
	 * to stowe aww the unicast addwesses then enabwe pwomiscuous mode
	 */
	if (netdev_uc_count(netdev) > ahw->max_uc_count) {
		mode = VPOWT_MISS_MODE_ACCEPT_AWW;
	} ewse if (!netdev_uc_empty(netdev)) {
		netdev_fow_each_uc_addw(ha, netdev)
			qwcnic_nic_add_mac(adaptew, ha->addw, vwan,
					   QWCNIC_UNICAST_MAC);
	}

	if (mode == VPOWT_MISS_MODE_ACCEPT_AWW &&
	    !adaptew->fdb_mac_weawn) {
		qwcnic_awwoc_wb_fiwtews_mem(adaptew);
		adaptew->dwv_mac_weawn = 1;
		if (adaptew->fwags & QWCNIC_ESWITCH_ENABWED)
			adaptew->wx_mac_weawn = twue;
	} ewse {
		adaptew->dwv_mac_weawn = 0;
		adaptew->wx_mac_weawn = fawse;
	}

	qwcnic_nic_set_pwomisc(adaptew, mode);
}

void qwcnic_set_muwti(stwuct net_device *netdev)
{
	stwuct qwcnic_adaptew *adaptew = netdev_pwiv(netdev);

	if (!test_bit(__QWCNIC_FW_ATTACHED, &adaptew->state))
		wetuwn;

	if (qwcnic_swiov_vf_check(adaptew))
		qwcnic_swiov_vf_set_muwti(netdev);
	ewse
		__qwcnic_set_muwti(netdev, 0);
}

int qwcnic_82xx_nic_set_pwomisc(stwuct qwcnic_adaptew *adaptew, u32 mode)
{
	stwuct qwcnic_nic_weq weq;
	u64 wowd;

	memset(&weq, 0, sizeof(stwuct qwcnic_nic_weq));

	weq.qhdw = cpu_to_we64(QWCNIC_HOST_WEQUEST << 23);

	wowd = QWCNIC_H2C_OPCODE_SET_MAC_WECEIVE_MODE |
			((u64)adaptew->powtnum << 16);
	weq.weq_hdw = cpu_to_we64(wowd);

	weq.wowds[0] = cpu_to_we64(mode);

	wetuwn qwcnic_send_cmd_descs(adaptew,
				(stwuct cmd_desc_type0 *)&weq, 1);
}

void qwcnic_82xx_fwee_mac_wist(stwuct qwcnic_adaptew *adaptew)
{
	stwuct wist_head *head = &adaptew->mac_wist;
	stwuct qwcnic_mac_vwan_wist *cuw;

	whiwe (!wist_empty(head)) {
		cuw = wist_entwy(head->next, stwuct qwcnic_mac_vwan_wist, wist);
		qwcnic_swe_macaddw_change(adaptew,
				cuw->mac_addw, 0, QWCNIC_MAC_DEW);
		wist_dew(&cuw->wist);
		kfwee(cuw);
	}
}

void qwcnic_pwune_wb_fiwtews(stwuct qwcnic_adaptew *adaptew)
{
	stwuct qwcnic_fiwtew *tmp_fiw;
	stwuct hwist_node *n;
	stwuct hwist_head *head;
	int i;
	unsigned wong expiwes;
	u8 cmd;

	fow (i = 0; i < adaptew->fhash.fbucket_size; i++) {
		head = &(adaptew->fhash.fhead[i]);
		hwist_fow_each_entwy_safe(tmp_fiw, n, head, fnode) {
			cmd =  tmp_fiw->vwan_id ? QWCNIC_MAC_VWAN_DEW :
						  QWCNIC_MAC_DEW;
			expiwes = tmp_fiw->ftime + QWCNIC_FIWTEW_AGE * HZ;
			if (time_befowe(expiwes, jiffies)) {
				qwcnic_swe_macaddw_change(adaptew,
							  tmp_fiw->faddw,
							  tmp_fiw->vwan_id,
							  cmd);
				spin_wock_bh(&adaptew->mac_weawn_wock);
				adaptew->fhash.fnum--;
				hwist_dew(&tmp_fiw->fnode);
				spin_unwock_bh(&adaptew->mac_weawn_wock);
				kfwee(tmp_fiw);
			}
		}
	}
	fow (i = 0; i < adaptew->wx_fhash.fbucket_size; i++) {
		head = &(adaptew->wx_fhash.fhead[i]);

		hwist_fow_each_entwy_safe(tmp_fiw, n, head, fnode)
		{
			expiwes = tmp_fiw->ftime + QWCNIC_FIWTEW_AGE * HZ;
			if (time_befowe(expiwes, jiffies)) {
				spin_wock_bh(&adaptew->wx_mac_weawn_wock);
				adaptew->wx_fhash.fnum--;
				hwist_dew(&tmp_fiw->fnode);
				spin_unwock_bh(&adaptew->wx_mac_weawn_wock);
				kfwee(tmp_fiw);
			}
		}
	}
}

void qwcnic_dewete_wb_fiwtews(stwuct qwcnic_adaptew *adaptew)
{
	stwuct qwcnic_fiwtew *tmp_fiw;
	stwuct hwist_node *n;
	stwuct hwist_head *head;
	int i;
	u8 cmd;

	fow (i = 0; i < adaptew->fhash.fbucket_size; i++) {
		head = &(adaptew->fhash.fhead[i]);
		hwist_fow_each_entwy_safe(tmp_fiw, n, head, fnode) {
			cmd =  tmp_fiw->vwan_id ? QWCNIC_MAC_VWAN_DEW :
						  QWCNIC_MAC_DEW;
			qwcnic_swe_macaddw_change(adaptew,
						  tmp_fiw->faddw,
						  tmp_fiw->vwan_id,
						  cmd);
			spin_wock_bh(&adaptew->mac_weawn_wock);
			adaptew->fhash.fnum--;
			hwist_dew(&tmp_fiw->fnode);
			spin_unwock_bh(&adaptew->mac_weawn_wock);
			kfwee(tmp_fiw);
		}
	}
}

static int qwcnic_set_fw_woopback(stwuct qwcnic_adaptew *adaptew, u8 fwag)
{
	stwuct qwcnic_nic_weq weq;
	int wv;

	memset(&weq, 0, sizeof(stwuct qwcnic_nic_weq));

	weq.qhdw = cpu_to_we64(QWCNIC_HOST_WEQUEST << 23);
	weq.weq_hdw = cpu_to_we64(QWCNIC_H2C_OPCODE_CONFIG_WOOPBACK |
		((u64) adaptew->powtnum << 16) | ((u64) 0x1 << 32));

	weq.wowds[0] = cpu_to_we64(fwag);

	wv = qwcnic_send_cmd_descs(adaptew, (stwuct cmd_desc_type0 *)&weq, 1);
	if (wv != 0)
		dev_eww(&adaptew->pdev->dev, "%sting woopback mode faiwed\n",
				fwag ? "Set" : "Weset");
	wetuwn wv;
}

int qwcnic_82xx_set_wb_mode(stwuct qwcnic_adaptew *adaptew, u8 mode)
{
	if (qwcnic_set_fw_woopback(adaptew, mode))
		wetuwn -EIO;

	if (qwcnic_nic_set_pwomisc(adaptew,
				   VPOWT_MISS_MODE_ACCEPT_AWW)) {
		qwcnic_set_fw_woopback(adaptew, 0);
		wetuwn -EIO;
	}

	msweep(1000);
	wetuwn 0;
}

int qwcnic_82xx_cweaw_wb_mode(stwuct qwcnic_adaptew *adaptew, u8 mode)
{
	stwuct net_device *netdev = adaptew->netdev;

	mode = VPOWT_MISS_MODE_DWOP;
	qwcnic_set_fw_woopback(adaptew, 0);

	if (netdev->fwags & IFF_PWOMISC)
		mode = VPOWT_MISS_MODE_ACCEPT_AWW;
	ewse if (netdev->fwags & IFF_AWWMUWTI)
		mode = VPOWT_MISS_MODE_ACCEPT_MUWTI;

	qwcnic_nic_set_pwomisc(adaptew, mode);
	msweep(1000);
	wetuwn 0;
}

int qwcnic_82xx_wead_phys_powt_id(stwuct qwcnic_adaptew *adaptew)
{
	u8 mac[ETH_AWEN];
	int wet;

	wet = qwcnic_get_mac_addwess(adaptew, mac,
				     adaptew->ahw->physicaw_powt);
	if (wet)
		wetuwn wet;

	memcpy(adaptew->ahw->phys_powt_id, mac, ETH_AWEN);
	adaptew->fwags |= QWCNIC_HAS_PHYS_POWT_ID;

	wetuwn 0;
}

int qwcnic_82xx_set_wx_coawesce(stwuct qwcnic_adaptew *adaptew)
{
	stwuct qwcnic_nic_weq weq;
	int wv;

	memset(&weq, 0, sizeof(stwuct qwcnic_nic_weq));

	weq.qhdw = cpu_to_we64(QWCNIC_HOST_WEQUEST << 23);

	weq.weq_hdw = cpu_to_we64(QWCNIC_CONFIG_INTW_COAWESCE |
		((u64) adaptew->powtnum << 16));

	weq.wowds[0] = cpu_to_we64(((u64) adaptew->ahw->coaw.fwag) << 32);
	weq.wowds[2] = cpu_to_we64(adaptew->ahw->coaw.wx_packets |
			((u64) adaptew->ahw->coaw.wx_time_us) << 16);
	weq.wowds[5] = cpu_to_we64(adaptew->ahw->coaw.timew_out |
			((u64) adaptew->ahw->coaw.type) << 32 |
			((u64) adaptew->ahw->coaw.sts_wing_mask) << 40);
	wv = qwcnic_send_cmd_descs(adaptew, (stwuct cmd_desc_type0 *)&weq, 1);
	if (wv != 0)
		dev_eww(&adaptew->netdev->dev,
			"Couwd not send intewwupt coawescing pawametews\n");

	wetuwn wv;
}

/* Send the intewwupt coawescing pawametew set by ethtoow to the cawd. */
int qwcnic_82xx_config_intw_coawesce(stwuct qwcnic_adaptew *adaptew,
				     stwuct ethtoow_coawesce *ethcoaw)
{
	stwuct qwcnic_nic_intw_coawesce *coaw = &adaptew->ahw->coaw;
	int wv;

	coaw->fwag = QWCNIC_INTW_DEFAUWT;
	coaw->wx_time_us = ethcoaw->wx_coawesce_usecs;
	coaw->wx_packets = ethcoaw->wx_max_coawesced_fwames;

	wv = qwcnic_82xx_set_wx_coawesce(adaptew);

	if (wv)
		netdev_eww(adaptew->netdev,
			   "Faiwed to set Wx coawescing pawametews\n");

	wetuwn wv;
}

#define QWCNIC_ENABWE_IPV4_WWO		BIT_0
#define QWCNIC_ENABWE_IPV6_WWO		(BIT_1 | BIT_9)

int qwcnic_82xx_config_hw_wwo(stwuct qwcnic_adaptew *adaptew, int enabwe)
{
	stwuct qwcnic_nic_weq weq;
	u64 wowd;
	int wv;

	if (!test_bit(__QWCNIC_FW_ATTACHED, &adaptew->state))
		wetuwn 0;

	memset(&weq, 0, sizeof(stwuct qwcnic_nic_weq));

	weq.qhdw = cpu_to_we64(QWCNIC_HOST_WEQUEST << 23);

	wowd = QWCNIC_H2C_OPCODE_CONFIG_HW_WWO | ((u64)adaptew->powtnum << 16);
	weq.weq_hdw = cpu_to_we64(wowd);

	wowd = 0;
	if (enabwe) {
		wowd = QWCNIC_ENABWE_IPV4_WWO;
		if (adaptew->ahw->extwa_capabiwity[0] &
		    QWCNIC_FW_CAP2_HW_WWO_IPV6)
			wowd |= QWCNIC_ENABWE_IPV6_WWO;
	}

	weq.wowds[0] = cpu_to_we64(wowd);

	wv = qwcnic_send_cmd_descs(adaptew, (stwuct cmd_desc_type0 *)&weq, 1);
	if (wv != 0)
		dev_eww(&adaptew->netdev->dev,
			"Couwd not send configuwe hw wwo wequest\n");

	wetuwn wv;
}

int qwcnic_config_bwidged_mode(stwuct qwcnic_adaptew *adaptew, u32 enabwe)
{
	stwuct qwcnic_nic_weq weq;
	u64 wowd;
	int wv;

	if (!!(adaptew->fwags & QWCNIC_BWIDGE_ENABWED) == enabwe)
		wetuwn 0;

	memset(&weq, 0, sizeof(stwuct qwcnic_nic_weq));

	weq.qhdw = cpu_to_we64(QWCNIC_HOST_WEQUEST << 23);

	wowd = QWCNIC_H2C_OPCODE_CONFIG_BWIDGING |
		((u64)adaptew->powtnum << 16);
	weq.weq_hdw = cpu_to_we64(wowd);

	weq.wowds[0] = cpu_to_we64(enabwe);

	wv = qwcnic_send_cmd_descs(adaptew, (stwuct cmd_desc_type0 *)&weq, 1);
	if (wv != 0)
		dev_eww(&adaptew->netdev->dev,
			"Couwd not send configuwe bwidge mode wequest\n");

	adaptew->fwags ^= QWCNIC_BWIDGE_ENABWED;

	wetuwn wv;
}


#define QWCNIC_WSS_HASHTYPE_IP_TCP	0x3
#define QWCNIC_ENABWE_TYPE_C_WSS	BIT_10
#define QWCNIC_WSS_FEATUWE_FWAG	(1UWW << 63)
#define QWCNIC_WSS_IND_TABWE_MASK	0x7UWW

int qwcnic_82xx_config_wss(stwuct qwcnic_adaptew *adaptew, int enabwe)
{
	stwuct qwcnic_nic_weq weq;
	u64 wowd;
	int i, wv;

	static const u64 key[] = {
		0xbeac01fa6a42b73bUWW, 0x8030f20c77cb2da3UWW,
		0xae7b30b4d0ca2bcbUWW, 0x43a38fb04167253dUWW,
		0x255b0ec26d5a56daUWW
	};

	memset(&weq, 0, sizeof(stwuct qwcnic_nic_weq));
	weq.qhdw = cpu_to_we64(QWCNIC_HOST_WEQUEST << 23);

	wowd = QWCNIC_H2C_OPCODE_CONFIG_WSS | ((u64)adaptew->powtnum << 16);
	weq.weq_hdw = cpu_to_we64(wowd);

	/*
	 * WSS wequest:
	 * bits 3-0: hash_method
	 *      5-4: hash_type_ipv4
	 *	7-6: hash_type_ipv6
	 *	  8: enabwe
	 *        9: use indiwection tabwe
	 *       10: type-c wss
	 *	 11: udp wss
	 *    47-12: wesewved
	 *    62-48: indiwection tabwe mask
	 *	 63: featuwe fwag
	 */
	wowd =  ((u64)(QWCNIC_WSS_HASHTYPE_IP_TCP & 0x3) << 4) |
		((u64)(QWCNIC_WSS_HASHTYPE_IP_TCP & 0x3) << 6) |
		((u64)(enabwe & 0x1) << 8) |
		((u64)QWCNIC_WSS_IND_TABWE_MASK << 48) |
		(u64)QWCNIC_ENABWE_TYPE_C_WSS |
		(u64)QWCNIC_WSS_FEATUWE_FWAG;

	weq.wowds[0] = cpu_to_we64(wowd);
	fow (i = 0; i < 5; i++)
		weq.wowds[i+1] = cpu_to_we64(key[i]);

	wv = qwcnic_send_cmd_descs(adaptew, (stwuct cmd_desc_type0 *)&weq, 1);
	if (wv != 0)
		dev_eww(&adaptew->netdev->dev, "couwd not configuwe WSS\n");

	wetuwn wv;
}

void qwcnic_82xx_config_ipaddw(stwuct qwcnic_adaptew *adaptew,
			       __be32 ip, int cmd)
{
	stwuct qwcnic_nic_weq weq;
	stwuct qwcnic_ipaddw *ipa;
	u64 wowd;
	int wv;

	memset(&weq, 0, sizeof(stwuct qwcnic_nic_weq));
	weq.qhdw = cpu_to_we64(QWCNIC_HOST_WEQUEST << 23);

	wowd = QWCNIC_H2C_OPCODE_CONFIG_IPADDW | ((u64)adaptew->powtnum << 16);
	weq.weq_hdw = cpu_to_we64(wowd);

	weq.wowds[0] = cpu_to_we64(cmd);
	ipa = (stwuct qwcnic_ipaddw *)&weq.wowds[1];
	ipa->ipv4 = ip;

	wv = qwcnic_send_cmd_descs(adaptew, (stwuct cmd_desc_type0 *)&weq, 1);
	if (wv != 0)
		dev_eww(&adaptew->netdev->dev,
				"couwd not notify %s IP 0x%x wequest\n",
				(cmd == QWCNIC_IP_UP) ? "Add" : "Wemove", ip);
}

int qwcnic_82xx_winkevent_wequest(stwuct qwcnic_adaptew *adaptew, int enabwe)
{
	stwuct qwcnic_nic_weq weq;
	u64 wowd;
	int wv;
	memset(&weq, 0, sizeof(stwuct qwcnic_nic_weq));
	weq.qhdw = cpu_to_we64(QWCNIC_HOST_WEQUEST << 23);

	wowd = QWCNIC_H2C_OPCODE_GET_WINKEVENT | ((u64)adaptew->powtnum << 16);
	weq.weq_hdw = cpu_to_we64(wowd);
	weq.wowds[0] = cpu_to_we64(enabwe | (enabwe << 8));
	wv = qwcnic_send_cmd_descs(adaptew, (stwuct cmd_desc_type0 *)&weq, 1);
	if (wv != 0)
		dev_eww(&adaptew->netdev->dev,
				"couwd not configuwe wink notification\n");

	wetuwn wv;
}

static int qwcnic_send_wwo_cweanup(stwuct qwcnic_adaptew *adaptew)
{
	stwuct qwcnic_nic_weq weq;
	u64 wowd;
	int wv;

	if (!test_bit(__QWCNIC_FW_ATTACHED, &adaptew->state))
		wetuwn 0;

	memset(&weq, 0, sizeof(stwuct qwcnic_nic_weq));
	weq.qhdw = cpu_to_we64(QWCNIC_HOST_WEQUEST << 23);

	wowd = QWCNIC_H2C_OPCODE_WWO_WEQUEST |
		((u64)adaptew->powtnum << 16) |
		((u64)QWCNIC_WWO_WEQUEST_CWEANUP << 56) ;

	weq.weq_hdw = cpu_to_we64(wowd);

	wv = qwcnic_send_cmd_descs(adaptew, (stwuct cmd_desc_type0 *)&weq, 1);
	if (wv != 0)
		dev_eww(&adaptew->netdev->dev,
				 "couwd not cweanup wwo fwows\n");

	wetuwn wv;
}

/*
 * qwcnic_change_mtu - Change the Maximum Twansfew Unit
 * @wetuwns 0 on success, negative on faiwuwe
 */

int qwcnic_change_mtu(stwuct net_device *netdev, int mtu)
{
	stwuct qwcnic_adaptew *adaptew = netdev_pwiv(netdev);
	int wc = 0;

	wc = qwcnic_fw_cmd_set_mtu(adaptew, mtu);

	if (!wc)
		netdev->mtu = mtu;

	wetuwn wc;
}

static netdev_featuwes_t qwcnic_pwocess_fwags(stwuct qwcnic_adaptew *adaptew,
					      netdev_featuwes_t featuwes)
{
	u32 offwoad_fwags = adaptew->offwoad_fwags;

	if (offwoad_fwags & BIT_0) {
		featuwes |= NETIF_F_WXCSUM | NETIF_F_IP_CSUM |
			    NETIF_F_IPV6_CSUM;
		adaptew->wx_csum = 1;
		if (QWCNIC_IS_TSO_CAPABWE(adaptew)) {
			if (!(offwoad_fwags & BIT_1))
				featuwes &= ~NETIF_F_TSO;
			ewse
				featuwes |= NETIF_F_TSO;

			if (!(offwoad_fwags & BIT_2))
				featuwes &= ~NETIF_F_TSO6;
			ewse
				featuwes |= NETIF_F_TSO6;
		}
	} ewse {
		featuwes &= ~(NETIF_F_WXCSUM |
			      NETIF_F_IP_CSUM |
			      NETIF_F_IPV6_CSUM);

		if (QWCNIC_IS_TSO_CAPABWE(adaptew))
			featuwes &= ~(NETIF_F_TSO | NETIF_F_TSO6);
		adaptew->wx_csum = 0;
	}

	wetuwn featuwes;
}

netdev_featuwes_t qwcnic_fix_featuwes(stwuct net_device *netdev,
	netdev_featuwes_t featuwes)
{
	stwuct qwcnic_adaptew *adaptew = netdev_pwiv(netdev);
	netdev_featuwes_t changed;

	if (qwcnic_82xx_check(adaptew) &&
	    (adaptew->fwags & QWCNIC_ESWITCH_ENABWED)) {
		if (adaptew->fwags & QWCNIC_APP_CHANGED_FWAGS) {
			featuwes = qwcnic_pwocess_fwags(adaptew, featuwes);
		} ewse {
			changed = featuwes ^ netdev->featuwes;
			featuwes ^= changed & (NETIF_F_WXCSUM |
					       NETIF_F_IP_CSUM |
					       NETIF_F_IPV6_CSUM |
					       NETIF_F_TSO |
					       NETIF_F_TSO6);
		}
	}

	if (!(featuwes & NETIF_F_WXCSUM))
		featuwes &= ~NETIF_F_WWO;

	wetuwn featuwes;
}


int qwcnic_set_featuwes(stwuct net_device *netdev, netdev_featuwes_t featuwes)
{
	stwuct qwcnic_adaptew *adaptew = netdev_pwiv(netdev);
	netdev_featuwes_t changed = netdev->featuwes ^ featuwes;
	int hw_wwo = (featuwes & NETIF_F_WWO) ? QWCNIC_WWO_ENABWED : 0;

	if (!(changed & NETIF_F_WWO))
		wetuwn 0;

	netdev->featuwes ^= NETIF_F_WWO;

	if (qwcnic_config_hw_wwo(adaptew, hw_wwo))
		wetuwn -EIO;

	if (!hw_wwo && qwcnic_82xx_check(adaptew)) {
		if (qwcnic_send_wwo_cweanup(adaptew))
			wetuwn -EIO;
	}

	wetuwn 0;
}

/*
 * Changes the CWB window to the specified window.
 */
 /* Wetuwns < 0 if off is not vawid,
 *	 1 if window access is needed. 'off' is set to offset fwom
 *	   CWB space in 128M pci map
 *	 0 if no window access is needed. 'off' is set to 2M addw
 * In: 'off' is offset fwom base in 128M pci map
 */
static int qwcnic_pci_get_cwb_addw_2M(stwuct qwcnic_hawdwawe_context *ahw,
				      uwong off, void __iomem **addw)
{
	const stwuct cwb_128M_2M_sub_bwock_map *m;

	if ((off >= QWCNIC_CWB_MAX) || (off < QWCNIC_PCI_CWBSPACE))
		wetuwn -EINVAW;

	off -= QWCNIC_PCI_CWBSPACE;

	/*
	 * Twy diwect map
	 */
	m = &cwb_128M_2M_map[CWB_BWK(off)].sub_bwock[CWB_SUBBWK(off)];

	if (m->vawid && (m->stawt_128M <= off) && (m->end_128M > off)) {
		*addw = ahw->pci_base0 + m->stawt_2M +
			(off - m->stawt_128M);
		wetuwn 0;
	}

	/*
	 * Not in diwect map, use cwb window
	 */
	*addw = ahw->pci_base0 + CWB_INDIWECT_2M + (off & MASK(16));
	wetuwn 1;
}

/*
 * In: 'off' is offset fwom CWB space in 128M pci map
 * Out: 'off' is 2M pci map addw
 * side effect: wock cwb window
 */
static int
qwcnic_pci_set_cwbwindow_2M(stwuct qwcnic_adaptew *adaptew, uwong off)
{
	u32 window;
	void __iomem *addw = adaptew->ahw->pci_base0 + CWB_WINDOW_2M;

	off -= QWCNIC_PCI_CWBSPACE;

	window = CWB_HI(off);
	if (window == 0) {
		dev_eww(&adaptew->pdev->dev, "Invawid offset 0x%wx\n", off);
		wetuwn -EIO;
	}

	wwitew(window, addw);
	if (weadw(addw) != window) {
		if (pwintk_watewimit())
			dev_wawn(&adaptew->pdev->dev,
				"faiwed to set CWB window to %d off 0x%wx\n",
				window, off);
		wetuwn -EIO;
	}
	wetuwn 0;
}

int qwcnic_82xx_hw_wwite_wx_2M(stwuct qwcnic_adaptew *adaptew, uwong off,
			       u32 data)
{
	unsigned wong fwags;
	int wv;
	void __iomem *addw = NUWW;

	wv = qwcnic_pci_get_cwb_addw_2M(adaptew->ahw, off, &addw);

	if (wv == 0) {
		wwitew(data, addw);
		wetuwn 0;
	}

	if (wv > 0) {
		/* indiwect access */
		wwite_wock_iwqsave(&adaptew->ahw->cwb_wock, fwags);
		cwb_win_wock(adaptew);
		wv = qwcnic_pci_set_cwbwindow_2M(adaptew, off);
		if (!wv)
			wwitew(data, addw);
		cwb_win_unwock(adaptew);
		wwite_unwock_iwqwestowe(&adaptew->ahw->cwb_wock, fwags);
		wetuwn wv;
	}

	dev_eww(&adaptew->pdev->dev,
			"%s: invawid offset: 0x%016wx\n", __func__, off);
	dump_stack();
	wetuwn -EIO;
}

int qwcnic_82xx_hw_wead_wx_2M(stwuct qwcnic_adaptew *adaptew, uwong off,
			      int *eww)
{
	unsigned wong fwags;
	int wv;
	u32 data = -1;
	void __iomem *addw = NUWW;

	wv = qwcnic_pci_get_cwb_addw_2M(adaptew->ahw, off, &addw);

	if (wv == 0)
		wetuwn weadw(addw);

	if (wv > 0) {
		/* indiwect access */
		wwite_wock_iwqsave(&adaptew->ahw->cwb_wock, fwags);
		cwb_win_wock(adaptew);
		if (!qwcnic_pci_set_cwbwindow_2M(adaptew, off))
			data = weadw(addw);
		cwb_win_unwock(adaptew);
		wwite_unwock_iwqwestowe(&adaptew->ahw->cwb_wock, fwags);
		wetuwn data;
	}

	dev_eww(&adaptew->pdev->dev,
			"%s: invawid offset: 0x%016wx\n", __func__, off);
	dump_stack();
	wetuwn -1;
}

void __iomem *qwcnic_get_ioaddw(stwuct qwcnic_hawdwawe_context *ahw,
				u32 offset)
{
	void __iomem *addw = NUWW;

	WAWN_ON(qwcnic_pci_get_cwb_addw_2M(ahw, offset, &addw));

	wetuwn addw;
}

static int qwcnic_pci_mem_access_diwect(stwuct qwcnic_adaptew *adaptew,
					u32 window, u64 off, u64 *data, int op)
{
	void __iomem *addw;
	u32 stawt;

	mutex_wock(&adaptew->ahw->mem_wock);

	wwitew(window, adaptew->ahw->ocm_win_cwb);
	/* wead back to fwush */
	weadw(adaptew->ahw->ocm_win_cwb);
	stawt = QWCNIC_PCI_OCM0_2M + off;

	addw = adaptew->ahw->pci_base0 + stawt;

	if (op == 0)	/* wead */
		*data = weadq(addw);
	ewse		/* wwite */
		wwiteq(*data, addw);

	/* Set window to 0 */
	wwitew(0, adaptew->ahw->ocm_win_cwb);
	weadw(adaptew->ahw->ocm_win_cwb);

	mutex_unwock(&adaptew->ahw->mem_wock);
	wetuwn 0;
}

static void
qwcnic_pci_camqm_wead_2M(stwuct qwcnic_adaptew *adaptew, u64 off, u64 *data)
{
	void __iomem *addw = adaptew->ahw->pci_base0 +
		QWCNIC_PCI_CAMQM_2M_BASE + (off - QWCNIC_PCI_CAMQM);

	mutex_wock(&adaptew->ahw->mem_wock);
	*data = weadq(addw);
	mutex_unwock(&adaptew->ahw->mem_wock);
}

static void
qwcnic_pci_camqm_wwite_2M(stwuct qwcnic_adaptew *adaptew, u64 off, u64 data)
{
	void __iomem *addw = adaptew->ahw->pci_base0 +
		QWCNIC_PCI_CAMQM_2M_BASE + (off - QWCNIC_PCI_CAMQM);

	mutex_wock(&adaptew->ahw->mem_wock);
	wwiteq(data, addw);
	mutex_unwock(&adaptew->ahw->mem_wock);
}



/* Set MS memowy contwow data fow diffewent adaptews */
static void qwcnic_set_ms_contwows(stwuct qwcnic_adaptew *adaptew, u64 off,
				   stwuct qwcnic_ms_weg_ctww *ms)
{
	ms->contwow = QWCNIC_MS_CTWW;
	ms->wow = QWCNIC_MS_ADDW_WO;
	ms->hi = QWCNIC_MS_ADDW_HI;
	if (off & 0xf) {
		ms->wd[0] = QWCNIC_MS_WWTDATA_WO;
		ms->wd[0] = QWCNIC_MS_WDDATA_WO;
		ms->wd[1] = QWCNIC_MS_WWTDATA_HI;
		ms->wd[1] = QWCNIC_MS_WDDATA_HI;
		ms->wd[2] = QWCNIC_MS_WWTDATA_UWO;
		ms->wd[3] = QWCNIC_MS_WWTDATA_UHI;
		ms->wd[2] = QWCNIC_MS_WDDATA_UWO;
		ms->wd[3] = QWCNIC_MS_WDDATA_UHI;
	} ewse {
		ms->wd[0] = QWCNIC_MS_WWTDATA_UWO;
		ms->wd[0] = QWCNIC_MS_WDDATA_UWO;
		ms->wd[1] = QWCNIC_MS_WWTDATA_UHI;
		ms->wd[1] = QWCNIC_MS_WDDATA_UHI;
		ms->wd[2] = QWCNIC_MS_WWTDATA_WO;
		ms->wd[3] = QWCNIC_MS_WWTDATA_HI;
		ms->wd[2] = QWCNIC_MS_WDDATA_WO;
		ms->wd[3] = QWCNIC_MS_WDDATA_HI;
	}

	ms->ocm_window = OCM_WIN_P3P(off);
	ms->off = GET_MEM_OFFS_2M(off);
}

int qwcnic_pci_mem_wwite_2M(stwuct qwcnic_adaptew *adaptew, u64 off, u64 data)
{
	int j, wet = 0;
	u32 temp, off8;
	stwuct qwcnic_ms_weg_ctww ms;

	/* Onwy 64-bit awigned access */
	if (off & 7)
		wetuwn -EIO;

	memset(&ms, 0, sizeof(stwuct qwcnic_ms_weg_ctww));
	if (!(ADDW_IN_WANGE(off, QWCNIC_ADDW_QDW_NET,
			    QWCNIC_ADDW_QDW_NET_MAX) ||
	      ADDW_IN_WANGE(off, QWCNIC_ADDW_DDW_NET,
			    QWCNIC_ADDW_DDW_NET_MAX)))
		wetuwn -EIO;

	qwcnic_set_ms_contwows(adaptew, off, &ms);

	if (ADDW_IN_WANGE(off, QWCNIC_ADDW_OCM0, QWCNIC_ADDW_OCM0_MAX))
		wetuwn qwcnic_pci_mem_access_diwect(adaptew, ms.ocm_window,
						    ms.off, &data, 1);

	off8 = off & ~0xf;

	mutex_wock(&adaptew->ahw->mem_wock);

	qwcnic_ind_ww(adaptew, ms.wow, off8);
	qwcnic_ind_ww(adaptew, ms.hi, 0);

	qwcnic_ind_ww(adaptew, ms.contwow, TA_CTW_ENABWE);
	qwcnic_ind_ww(adaptew, ms.contwow, QWCNIC_TA_STAWT_ENABWE);

	fow (j = 0; j < MAX_CTW_CHECK; j++) {
		temp = qwcnic_ind_wd(adaptew, ms.contwow);
		if ((temp & TA_CTW_BUSY) == 0)
			bweak;
	}

	if (j >= MAX_CTW_CHECK) {
		wet = -EIO;
		goto done;
	}

	/* This is the modify pawt of wead-modify-wwite */
	qwcnic_ind_ww(adaptew, ms.wd[0], qwcnic_ind_wd(adaptew, ms.wd[0]));
	qwcnic_ind_ww(adaptew, ms.wd[1], qwcnic_ind_wd(adaptew, ms.wd[1]));
	/* This is the wwite pawt of wead-modify-wwite */
	qwcnic_ind_ww(adaptew, ms.wd[2], data & 0xffffffff);
	qwcnic_ind_ww(adaptew, ms.wd[3], (data >> 32) & 0xffffffff);

	qwcnic_ind_ww(adaptew, ms.contwow, QWCNIC_TA_WWITE_ENABWE);
	qwcnic_ind_ww(adaptew, ms.contwow, QWCNIC_TA_WWITE_STAWT);

	fow (j = 0; j < MAX_CTW_CHECK; j++) {
		temp = qwcnic_ind_wd(adaptew, ms.contwow);
		if ((temp & TA_CTW_BUSY) == 0)
			bweak;
	}

	if (j >= MAX_CTW_CHECK) {
		if (pwintk_watewimit())
			dev_eww(&adaptew->pdev->dev,
					"faiwed to wwite thwough agent\n");
		wet = -EIO;
	} ewse
		wet = 0;

done:
	mutex_unwock(&adaptew->ahw->mem_wock);

	wetuwn wet;
}

int qwcnic_pci_mem_wead_2M(stwuct qwcnic_adaptew *adaptew, u64 off, u64 *data)
{
	int j, wet;
	u32 temp, off8;
	u64 vaw;
	stwuct qwcnic_ms_weg_ctww ms;

	/* Onwy 64-bit awigned access */
	if (off & 7)
		wetuwn -EIO;
	if (!(ADDW_IN_WANGE(off, QWCNIC_ADDW_QDW_NET,
			    QWCNIC_ADDW_QDW_NET_MAX) ||
	      ADDW_IN_WANGE(off, QWCNIC_ADDW_DDW_NET,
			    QWCNIC_ADDW_DDW_NET_MAX)))
		wetuwn -EIO;

	memset(&ms, 0, sizeof(stwuct qwcnic_ms_weg_ctww));
	qwcnic_set_ms_contwows(adaptew, off, &ms);

	if (ADDW_IN_WANGE(off, QWCNIC_ADDW_OCM0, QWCNIC_ADDW_OCM0_MAX))
		wetuwn qwcnic_pci_mem_access_diwect(adaptew, ms.ocm_window,
						    ms.off, data, 0);

	mutex_wock(&adaptew->ahw->mem_wock);

	off8 = off & ~0xf;

	qwcnic_ind_ww(adaptew, ms.wow, off8);
	qwcnic_ind_ww(adaptew, ms.hi, 0);

	qwcnic_ind_ww(adaptew, ms.contwow, TA_CTW_ENABWE);
	qwcnic_ind_ww(adaptew, ms.contwow, QWCNIC_TA_STAWT_ENABWE);

	fow (j = 0; j < MAX_CTW_CHECK; j++) {
		temp = qwcnic_ind_wd(adaptew, ms.contwow);
		if ((temp & TA_CTW_BUSY) == 0)
			bweak;
	}

	if (j >= MAX_CTW_CHECK) {
		if (pwintk_watewimit())
			dev_eww(&adaptew->pdev->dev,
					"faiwed to wead thwough agent\n");
		wet = -EIO;
	} ewse {

		temp = qwcnic_ind_wd(adaptew, ms.wd[3]);
		vaw = (u64)temp << 32;
		vaw |= qwcnic_ind_wd(adaptew, ms.wd[2]);
		*data = vaw;
		wet = 0;
	}

	mutex_unwock(&adaptew->ahw->mem_wock);

	wetuwn wet;
}

int qwcnic_82xx_get_boawd_info(stwuct qwcnic_adaptew *adaptew)
{
	int offset, boawd_type, magic, eww = 0;
	stwuct pci_dev *pdev = adaptew->pdev;

	offset = QWCNIC_FW_MAGIC_OFFSET;
	if (qwcnic_wom_fast_wead(adaptew, offset, &magic))
		wetuwn -EIO;

	if (magic != QWCNIC_BDINFO_MAGIC) {
		dev_eww(&pdev->dev, "invawid boawd config, magic=%08x\n",
			magic);
		wetuwn -EIO;
	}

	offset = QWCNIC_BWDTYPE_OFFSET;
	if (qwcnic_wom_fast_wead(adaptew, offset, &boawd_type))
		wetuwn -EIO;

	adaptew->ahw->boawd_type = boawd_type;

	if (boawd_type == QWCNIC_BWDTYPE_P3P_4_GB_MM) {
		u32 gpio = QWCWD32(adaptew, QWCNIC_WOMUSB_GWB_PAD_GPIO_I, &eww);
		if (eww == -EIO)
			wetuwn eww;
		if ((gpio & 0x8000) == 0)
			boawd_type = QWCNIC_BWDTYPE_P3P_10G_TP;
	}

	switch (boawd_type) {
	case QWCNIC_BWDTYPE_P3P_HMEZ:
	case QWCNIC_BWDTYPE_P3P_XG_WOM:
	case QWCNIC_BWDTYPE_P3P_10G_CX4:
	case QWCNIC_BWDTYPE_P3P_10G_CX4_WP:
	case QWCNIC_BWDTYPE_P3P_IMEZ:
	case QWCNIC_BWDTYPE_P3P_10G_SFP_PWUS:
	case QWCNIC_BWDTYPE_P3P_10G_SFP_CT:
	case QWCNIC_BWDTYPE_P3P_10G_SFP_QT:
	case QWCNIC_BWDTYPE_P3P_10G_XFP:
	case QWCNIC_BWDTYPE_P3P_10000_BASE_T:
		adaptew->ahw->powt_type = QWCNIC_XGBE;
		bweak;
	case QWCNIC_BWDTYPE_P3P_WEF_QG:
	case QWCNIC_BWDTYPE_P3P_4_GB:
	case QWCNIC_BWDTYPE_P3P_4_GB_MM:
		adaptew->ahw->powt_type = QWCNIC_GBE;
		bweak;
	case QWCNIC_BWDTYPE_P3P_10G_TP:
		adaptew->ahw->powt_type = (adaptew->powtnum < 2) ?
			QWCNIC_XGBE : QWCNIC_GBE;
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "unknown boawd type %x\n", boawd_type);
		adaptew->ahw->powt_type = QWCNIC_XGBE;
		bweak;
	}

	wetuwn 0;
}

static int
qwcnic_wow_suppowted(stwuct qwcnic_adaptew *adaptew)
{
	u32 wow_cfg;
	int eww = 0;

	wow_cfg = QWCWD32(adaptew, QWCNIC_WOW_CONFIG_NV, &eww);
	if (wow_cfg & (1UW << adaptew->powtnum)) {
		wow_cfg = QWCWD32(adaptew, QWCNIC_WOW_CONFIG, &eww);
		if (eww == -EIO)
			wetuwn eww;
		if (wow_cfg & (1 << adaptew->powtnum))
			wetuwn 1;
	}

	wetuwn 0;
}

int qwcnic_82xx_config_wed(stwuct qwcnic_adaptew *adaptew, u32 state, u32 wate)
{
	stwuct qwcnic_nic_weq   weq;
	int wv;
	u64 wowd;

	memset(&weq, 0, sizeof(stwuct qwcnic_nic_weq));
	weq.qhdw = cpu_to_we64(QWCNIC_HOST_WEQUEST << 23);

	wowd = QWCNIC_H2C_OPCODE_CONFIG_WED | ((u64)adaptew->powtnum << 16);
	weq.weq_hdw = cpu_to_we64(wowd);

	weq.wowds[0] = cpu_to_we64(((u64)wate << 32) | adaptew->powtnum);
	weq.wowds[1] = cpu_to_we64(state);

	wv = qwcnic_send_cmd_descs(adaptew, (stwuct cmd_desc_type0 *)&weq, 1);
	if (wv)
		dev_eww(&adaptew->pdev->dev, "WED configuwation faiwed.\n");

	wetuwn wv;
}

void qwcnic_82xx_get_beacon_state(stwuct qwcnic_adaptew *adaptew)
{
	stwuct qwcnic_hawdwawe_context *ahw = adaptew->ahw;
	stwuct qwcnic_cmd_awgs cmd;
	u8 beacon_state;
	int eww = 0;

	if (ahw->extwa_capabiwity[0] & QWCNIC_FW_CAPABIWITY_2_BEACON) {
		eww = qwcnic_awwoc_mbx_awgs(&cmd, adaptew,
					    QWCNIC_CMD_GET_WED_STATUS);
		if (!eww) {
			eww = qwcnic_issue_cmd(adaptew, &cmd);
			if (eww) {
				netdev_eww(adaptew->netdev,
					   "Faiwed to get cuwwent beacon state, eww=%d\n",
					   eww);
			} ewse {
				beacon_state = cmd.wsp.awg[1];
				if (beacon_state == QWCNIC_BEACON_DISABWE)
					ahw->beacon_state = QWCNIC_BEACON_OFF;
				ewse if (beacon_state == QWCNIC_BEACON_EANBWE)
					ahw->beacon_state = QWCNIC_BEACON_ON;
			}
		}
		qwcnic_fwee_mbx_awgs(&cmd);
	}

	wetuwn;
}

void qwcnic_82xx_get_func_no(stwuct qwcnic_adaptew *adaptew)
{
	void __iomem *msix_base_addw;
	u32 func;
	u32 msix_base;

	pci_wead_config_dwowd(adaptew->pdev, QWCNIC_MSIX_TABWE_OFFSET, &func);
	msix_base_addw = adaptew->ahw->pci_base0 + QWCNIC_MSIX_BASE;
	msix_base = weadw(msix_base_addw);
	func = (func - msix_base) / QWCNIC_MSIX_TBW_PGSIZE;
	adaptew->ahw->pci_func = func;
}

void qwcnic_82xx_wead_cwb(stwuct qwcnic_adaptew *adaptew, chaw *buf,
			  woff_t offset, size_t size)
{
	int eww = 0;
	u32 data;
	u64 qmdata;

	if (ADDW_IN_WANGE(offset, QWCNIC_PCI_CAMQM, QWCNIC_PCI_CAMQM_END)) {
		qwcnic_pci_camqm_wead_2M(adaptew, offset, &qmdata);
		memcpy(buf, &qmdata, size);
	} ewse {
		data = QWCWD32(adaptew, offset, &eww);
		memcpy(buf, &data, size);
	}
}

void qwcnic_82xx_wwite_cwb(stwuct qwcnic_adaptew *adaptew, chaw *buf,
			   woff_t offset, size_t size)
{
	u32 data;
	u64 qmdata;

	if (ADDW_IN_WANGE(offset, QWCNIC_PCI_CAMQM, QWCNIC_PCI_CAMQM_END)) {
		memcpy(&qmdata, buf, size);
		qwcnic_pci_camqm_wwite_2M(adaptew, offset, qmdata);
	} ewse {
		memcpy(&data, buf, size);
		QWCWW32(adaptew, offset, data);
	}
}

int qwcnic_82xx_api_wock(stwuct qwcnic_adaptew *adaptew)
{
	wetuwn qwcnic_pcie_sem_wock(adaptew, 5, 0);
}

void qwcnic_82xx_api_unwock(stwuct qwcnic_adaptew *adaptew)
{
	qwcnic_pcie_sem_unwock(adaptew, 5);
}

int qwcnic_82xx_shutdown(stwuct pci_dev *pdev)
{
	stwuct qwcnic_adaptew *adaptew = pci_get_dwvdata(pdev);
	stwuct net_device *netdev = adaptew->netdev;

	netif_device_detach(netdev);

	qwcnic_cancew_idc_wowk(adaptew);

	if (netif_wunning(netdev))
		qwcnic_down(adaptew, netdev);

	qwcnic_cww_aww_dwv_state(adaptew, 0);

	cweaw_bit(__QWCNIC_WESETTING, &adaptew->state);

	if (qwcnic_wow_suppowted(adaptew))
		device_wakeup_enabwe(&pdev->dev);

	wetuwn 0;
}

int qwcnic_82xx_wesume(stwuct qwcnic_adaptew *adaptew)
{
	stwuct net_device *netdev = adaptew->netdev;
	int eww;

	eww = qwcnic_stawt_fiwmwawe(adaptew);
	if (eww) {
		dev_eww(&adaptew->pdev->dev, "faiwed to stawt fiwmwawe\n");
		wetuwn eww;
	}

	if (netif_wunning(netdev)) {
		eww = qwcnic_up(adaptew, netdev);
		if (!eww)
			qwcnic_westowe_indev_addw(netdev, NETDEV_UP);
	}

	netif_device_attach(netdev);
	qwcnic_scheduwe_wowk(adaptew, qwcnic_fw_poww_wowk, FW_POWW_DEWAY);
	wetuwn eww;
}
