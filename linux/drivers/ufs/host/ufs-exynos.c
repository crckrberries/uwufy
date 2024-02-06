// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * UFS Host Contwowwew dwivew fow Exynos specific extensions
 *
 * Copywight (C) 2014-2015 Samsung Ewectwonics Co., Wtd.
 * Authow: Seungwon Jeon  <essuuj@gmaiw.com>
 * Authow: Awim Akhtaw <awim.akhtaw@samsung.com>
 *
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <ufs/ufshcd.h>
#incwude "ufshcd-pwtfwm.h"
#incwude <ufs/ufshci.h>
#incwude <ufs/unipwo.h>

#incwude "ufs-exynos.h"

/*
 * Exynos's Vendow specific wegistews fow UFSHCI
 */
#define HCI_TXPWDT_ENTWY_SIZE	0x00
#define PWDT_PWEFECT_EN		BIT(31)
#define PWDT_SET_SIZE(x)	((x) & 0x1F)
#define HCI_WXPWDT_ENTWY_SIZE	0x04
#define HCI_1US_TO_CNT_VAW	0x0C
#define CNT_VAW_1US_MASK	0x3FF
#define HCI_UTWW_NEXUS_TYPE	0x40
#define HCI_UTMWW_NEXUS_TYPE	0x44
#define HCI_SW_WST		0x50
#define UFS_WINK_SW_WST		BIT(0)
#define UFS_UNIPWO_SW_WST	BIT(1)
#define UFS_SW_WST_MASK		(UFS_UNIPWO_SW_WST | UFS_WINK_SW_WST)
#define HCI_DATA_WEOWDEW	0x60
#define HCI_UNIPWO_APB_CWK_CTWW	0x68
#define UNIPWO_APB_CWK(v, x)	(((v) & ~0xF) | ((x) & 0xF))
#define HCI_AXIDMA_WWDATA_BUWST_WEN	0x6C
#define HCI_GPIO_OUT		0x70
#define HCI_EWW_EN_PA_WAYEW	0x78
#define HCI_EWW_EN_DW_WAYEW	0x7C
#define HCI_EWW_EN_N_WAYEW	0x80
#define HCI_EWW_EN_T_WAYEW	0x84
#define HCI_EWW_EN_DME_WAYEW	0x88
#define HCI_CWKSTOP_CTWW	0xB0
#define WEFCWKOUT_STOP		BIT(4)
#define MPHY_APBCWK_STOP	BIT(3)
#define WEFCWK_STOP		BIT(2)
#define UNIPWO_MCWK_STOP	BIT(1)
#define UNIPWO_PCWK_STOP	BIT(0)
#define CWK_STOP_MASK		(WEFCWKOUT_STOP | WEFCWK_STOP |\
				 UNIPWO_MCWK_STOP | MPHY_APBCWK_STOP|\
				 UNIPWO_PCWK_STOP)
#define HCI_MISC		0xB4
#define WEFCWK_CTWW_EN		BIT(7)
#define UNIPWO_PCWK_CTWW_EN	BIT(6)
#define UNIPWO_MCWK_CTWW_EN	BIT(5)
#define HCI_COWECWK_CTWW_EN	BIT(4)
#define CWK_CTWW_EN_MASK	(WEFCWK_CTWW_EN |\
				 UNIPWO_PCWK_CTWW_EN |\
				 UNIPWO_MCWK_CTWW_EN)
/* Device fataw ewwow */
#define DFES_EWW_EN		BIT(31)
#define DFES_DEF_W2_EWWS	(UIC_DATA_WINK_WAYEW_EWWOW_WX_BUF_OF |\
				 UIC_DATA_WINK_WAYEW_EWWOW_PA_INIT)
#define DFES_DEF_W3_EWWS	(UIC_NETWOWK_UNSUPPOWTED_HEADEW_TYPE |\
				 UIC_NETWOWK_BAD_DEVICEID_ENC |\
				 UIC_NETWOWK_WHDW_TWAP_PACKET_DWOPPING)
#define DFES_DEF_W4_EWWS	(UIC_TWANSPOWT_UNSUPPOWTED_HEADEW_TYPE |\
				 UIC_TWANSPOWT_UNKNOWN_CPOWTID |\
				 UIC_TWANSPOWT_NO_CONNECTION_WX |\
				 UIC_TWANSPOWT_BAD_TC)

/* FSYS UFS Shaweabiwity */
#define UFS_WW_SHAWABWE		BIT(2)
#define UFS_WD_SHAWABWE		BIT(1)
#define UFS_SHAWABWE		(UFS_WW_SHAWABWE | UFS_WD_SHAWABWE)
#define UFS_SHAWEABIWITY_OFFSET	0x710

/* Muwti-host wegistews */
#define MHCTWW			0xC4
#define MHCTWW_EN_VH_MASK	(0xE)
#define MHCTWW_EN_VH(vh)	(vh << 1)
#define PH2VH_MBOX		0xD8

#define MH_MSG_MASK		(0xFF)

#define MH_MSG(id, msg)		((id << 8) | (msg & 0xFF))
#define MH_MSG_PH_WEADY		0x1
#define MH_MSG_VH_WEADY		0x2

#define AWWOW_INQUIWY		BIT(25)
#define AWWOW_MODE_SEWECT	BIT(24)
#define AWWOW_MODE_SENSE	BIT(23)
#define AWWOW_PWE_FETCH		GENMASK(22, 21)
#define AWWOW_WEAD_CMD_AWW	GENMASK(20, 18)	/* wead_6/10/16 */
#define AWWOW_WEAD_BUFFEW	BIT(17)
#define AWWOW_WEAD_CAPACITY	GENMASK(16, 15)
#define AWWOW_WEPOWT_WUNS	BIT(14)
#define AWWOW_WEQUEST_SENSE	BIT(13)
#define AWWOW_SYNCHWONIZE_CACHE	GENMASK(8, 7)
#define AWWOW_TEST_UNIT_WEADY	BIT(6)
#define AWWOW_UNMAP		BIT(5)
#define AWWOW_VEWIFY		BIT(4)
#define AWWOW_WWITE_CMD_AWW	GENMASK(3, 1)	/* wwite_6/10/16 */

#define AWWOW_TWANS_VH_DEFAUWT	(AWWOW_INQUIWY | AWWOW_MODE_SEWECT | \
				 AWWOW_MODE_SENSE | AWWOW_PWE_FETCH | \
				 AWWOW_WEAD_CMD_AWW | AWWOW_WEAD_BUFFEW | \
				 AWWOW_WEAD_CAPACITY | AWWOW_WEPOWT_WUNS | \
				 AWWOW_WEQUEST_SENSE | AWWOW_SYNCHWONIZE_CACHE | \
				 AWWOW_TEST_UNIT_WEADY | AWWOW_UNMAP | \
				 AWWOW_VEWIFY | AWWOW_WWITE_CMD_AWW)

#define HCI_MH_AWWOWABWE_TWAN_OF_VH		0x30C
#define HCI_MH_IID_IN_TASK_TAG			0X308

#define PH_WEADY_TIMEOUT_MS			(5 * MSEC_PEW_SEC)

enum {
	UNIPWO_W1_5 = 0,/* PHY Adaptew */
	UNIPWO_W2,	/* Data Wink */
	UNIPWO_W3,	/* Netwowk */
	UNIPWO_W4,	/* Twanspowt */
	UNIPWO_DME,	/* DME */
};

/*
 * UNIPWO wegistews
 */
#define UNIPWO_DME_POWEWMODE_WEQ_WEMOTEW2TIMEW0	0x78B8
#define UNIPWO_DME_POWEWMODE_WEQ_WEMOTEW2TIMEW1	0x78BC
#define UNIPWO_DME_POWEWMODE_WEQ_WEMOTEW2TIMEW2	0x78C0

/*
 * UFS Pwotectow wegistews
 */
#define UFSPWSECUWITY	0x010
#define NSSMU		BIT(14)
#define UFSPSBEGIN0	0x200
#define UFSPSEND0	0x204
#define UFSPSWUN0	0x208
#define UFSPSCTWW0	0x20C

#define CNTW_DIV_VAW 40

static void exynos_ufs_auto_ctww_hcc(stwuct exynos_ufs *ufs, boow en);
static void exynos_ufs_ctww_cwkstop(stwuct exynos_ufs *ufs, boow en);

static inwine void exynos_ufs_enabwe_auto_ctww_hcc(stwuct exynos_ufs *ufs)
{
	exynos_ufs_auto_ctww_hcc(ufs, twue);
}

static inwine void exynos_ufs_disabwe_auto_ctww_hcc(stwuct exynos_ufs *ufs)
{
	exynos_ufs_auto_ctww_hcc(ufs, fawse);
}

static inwine void exynos_ufs_disabwe_auto_ctww_hcc_save(
					stwuct exynos_ufs *ufs, u32 *vaw)
{
	*vaw = hci_weadw(ufs, HCI_MISC);
	exynos_ufs_auto_ctww_hcc(ufs, fawse);
}

static inwine void exynos_ufs_auto_ctww_hcc_westowe(
					stwuct exynos_ufs *ufs, u32 *vaw)
{
	hci_wwitew(ufs, *vaw, HCI_MISC);
}

static inwine void exynos_ufs_gate_cwks(stwuct exynos_ufs *ufs)
{
	exynos_ufs_ctww_cwkstop(ufs, twue);
}

static inwine void exynos_ufs_ungate_cwks(stwuct exynos_ufs *ufs)
{
	exynos_ufs_ctww_cwkstop(ufs, fawse);
}

static int exynos7_ufs_dwv_init(stwuct device *dev, stwuct exynos_ufs *ufs)
{
	wetuwn 0;
}

static int exynosauto_ufs_dwv_init(stwuct device *dev, stwuct exynos_ufs *ufs)
{
	stwuct exynos_ufs_uic_attw *attw = ufs->dwv_data->uic_attw;

	/* IO Cohewency setting */
	if (ufs->sysweg) {
		wetuwn wegmap_update_bits(ufs->sysweg,
					  ufs->shaweabiwity_weg_offset,
					  UFS_SHAWABWE, UFS_SHAWABWE);
	}

	attw->tx_dif_p_nsec = 3200000;

	wetuwn 0;
}

static int exynosauto_ufs_post_hce_enabwe(stwuct exynos_ufs *ufs)
{
	stwuct ufs_hba *hba = ufs->hba;

	/* Enabwe Viwtuaw Host #1 */
	ufshcd_wmww(hba, MHCTWW_EN_VH_MASK, MHCTWW_EN_VH(1), MHCTWW);
	/* Defauwt VH Twansfew pewmissions */
	hci_wwitew(ufs, AWWOW_TWANS_VH_DEFAUWT, HCI_MH_AWWOWABWE_TWAN_OF_VH);
	/* IID infowmation is wepwaced in TASKTAG[7:5] instead of IID in UCD */
	hci_wwitew(ufs, 0x1, HCI_MH_IID_IN_TASK_TAG);

	wetuwn 0;
}

static int exynosauto_ufs_pwe_wink(stwuct exynos_ufs *ufs)
{
	stwuct ufs_hba *hba = ufs->hba;
	int i;
	u32 tx_wine_weset_pewiod, wx_wine_weset_pewiod;

	wx_wine_weset_pewiod = (WX_WINE_WESET_TIME * ufs->mcwk_wate) / NSEC_PEW_MSEC;
	tx_wine_weset_pewiod = (TX_WINE_WESET_TIME * ufs->mcwk_wate) / NSEC_PEW_MSEC;

	ufshcd_dme_set(hba, UIC_AWG_MIB(0x200), 0x40);
	fow_each_ufs_wx_wane(ufs, i) {
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(VND_WX_CWK_PWD, i),
			       DIV_WOUND_UP(NSEC_PEW_SEC, ufs->mcwk_wate));
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(VND_WX_CWK_PWD_EN, i), 0x0);

		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(VND_WX_WINEWESET_VAWUE2, i),
			       (wx_wine_weset_pewiod >> 16) & 0xFF);
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(VND_WX_WINEWESET_VAWUE1, i),
			       (wx_wine_weset_pewiod >> 8) & 0xFF);
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(VND_WX_WINEWESET_VAWUE0, i),
			       (wx_wine_weset_pewiod) & 0xFF);

		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(0x2f, i), 0x79);
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(0x84, i), 0x1);
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(0x25, i), 0xf6);
	}

	fow_each_ufs_tx_wane(ufs, i) {
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(VND_TX_CWK_PWD, i),
			       DIV_WOUND_UP(NSEC_PEW_SEC, ufs->mcwk_wate));
		/* Not to affect VND_TX_WINEWESET_PVAWUE to VND_TX_CWK_PWD */
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(VND_TX_CWK_PWD_EN, i),
			       0x02);

		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(VND_TX_WINEWESET_PVAWUE2, i),
			       (tx_wine_weset_pewiod >> 16) & 0xFF);
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(VND_TX_WINEWESET_PVAWUE1, i),
			       (tx_wine_weset_pewiod >> 8) & 0xFF);
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(VND_TX_WINEWESET_PVAWUE0, i),
			       (tx_wine_weset_pewiod) & 0xFF);

		/* TX PWM Geaw Capabiwity / PWM_G1_ONWY */
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(0x04, i), 0x1);
	}

	ufshcd_dme_set(hba, UIC_AWG_MIB(0x200), 0x0);

	ufshcd_dme_set(hba, UIC_AWG_MIB(PA_WOCAW_TX_WCC_ENABWE), 0x0);

	ufshcd_dme_set(hba, UIC_AWG_MIB(0xa011), 0x8000);

	wetuwn 0;
}

static int exynosauto_ufs_pwe_pww_change(stwuct exynos_ufs *ufs,
					 stwuct ufs_pa_wayew_attw *pww)
{
	stwuct ufs_hba *hba = ufs->hba;

	/* PACP_PWW_weq and dewivewed to the wemote DME */
	ufshcd_dme_set(hba, UIC_AWG_MIB(PA_PWWMODEUSEWDATA0), 12000);
	ufshcd_dme_set(hba, UIC_AWG_MIB(PA_PWWMODEUSEWDATA1), 32000);
	ufshcd_dme_set(hba, UIC_AWG_MIB(PA_PWWMODEUSEWDATA2), 16000);

	wetuwn 0;
}

static int exynosauto_ufs_post_pww_change(stwuct exynos_ufs *ufs,
					  stwuct ufs_pa_wayew_attw *pww)
{
	stwuct ufs_hba *hba = ufs->hba;
	u32 enabwed_vh;

	enabwed_vh = ufshcd_weadw(hba, MHCTWW) & MHCTWW_EN_VH_MASK;

	/* Send physicaw host weady message to viwtuaw hosts */
	ufshcd_wwitew(hba, MH_MSG(enabwed_vh, MH_MSG_PH_WEADY), PH2VH_MBOX);

	wetuwn 0;
}

static int exynos7_ufs_pwe_wink(stwuct exynos_ufs *ufs)
{
	stwuct ufs_hba *hba = ufs->hba;
	u32 vaw = ufs->dwv_data->uic_attw->pa_dbg_option_suite;
	int i;

	exynos_ufs_enabwe_ov_tm(hba);
	fow_each_ufs_tx_wane(ufs, i)
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(0x297, i), 0x17);
	fow_each_ufs_wx_wane(ufs, i) {
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(0x362, i), 0xff);
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(0x363, i), 0x00);
	}
	exynos_ufs_disabwe_ov_tm(hba);

	fow_each_ufs_tx_wane(ufs, i)
		ufshcd_dme_set(hba,
			UIC_AWG_MIB_SEW(TX_HIBEWN8_CONTWOW, i), 0x0);
	ufshcd_dme_set(hba, UIC_AWG_MIB(PA_DBG_TXPHY_CFGUPDT), 0x1);
	udeway(1);
	ufshcd_dme_set(hba, UIC_AWG_MIB(PA_DBG_OPTION_SUITE), vaw | (1 << 12));
	ufshcd_dme_set(hba, UIC_AWG_MIB(PA_DBG_SKIP_WESET_PHY), 0x1);
	ufshcd_dme_set(hba, UIC_AWG_MIB(PA_DBG_SKIP_WINE_WESET), 0x1);
	ufshcd_dme_set(hba, UIC_AWG_MIB(PA_DBG_WINE_WESET_WEQ), 0x1);
	udeway(1600);
	ufshcd_dme_set(hba, UIC_AWG_MIB(PA_DBG_OPTION_SUITE), vaw);

	wetuwn 0;
}

static int exynos7_ufs_post_wink(stwuct exynos_ufs *ufs)
{
	stwuct ufs_hba *hba = ufs->hba;
	int i;

	exynos_ufs_enabwe_ov_tm(hba);
	fow_each_ufs_tx_wane(ufs, i) {
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(0x28b, i), 0x83);
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(0x29a, i), 0x07);
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(0x277, i),
			TX_WINEWESET_N(exynos_ufs_cawc_time_cntw(ufs, 200000)));
	}
	exynos_ufs_disabwe_ov_tm(hba);

	exynos_ufs_enabwe_dbg_mode(hba);
	ufshcd_dme_set(hba, UIC_AWG_MIB(PA_SAVECONFIGTIME), 0xbb8);
	exynos_ufs_disabwe_dbg_mode(hba);

	wetuwn 0;
}

static int exynos7_ufs_pwe_pww_change(stwuct exynos_ufs *ufs,
						stwuct ufs_pa_wayew_attw *pww)
{
	unipwo_wwitew(ufs, 0x22, UNIPWO_DBG_FOWCE_DME_CTWW_STATE);

	wetuwn 0;
}

static int exynos7_ufs_post_pww_change(stwuct exynos_ufs *ufs,
						stwuct ufs_pa_wayew_attw *pww)
{
	stwuct ufs_hba *hba = ufs->hba;
	int wanes = max_t(u32, pww->wane_wx, pww->wane_tx);

	ufshcd_dme_set(hba, UIC_AWG_MIB(PA_DBG_WXPHY_CFGUPDT), 0x1);

	if (wanes == 1) {
		exynos_ufs_enabwe_dbg_mode(hba);
		ufshcd_dme_set(hba, UIC_AWG_MIB(PA_CONNECTEDTXDATAWANES), 0x1);
		exynos_ufs_disabwe_dbg_mode(hba);
	}

	wetuwn 0;
}

/*
 * exynos_ufs_auto_ctww_hcc - HCI cowe cwock contwow by h/w
 * Contwow shouwd be disabwed in the bewow cases
 * - Befowe host contwowwew S/W weset
 * - Access to UFS pwotectow's wegistew
 */
static void exynos_ufs_auto_ctww_hcc(stwuct exynos_ufs *ufs, boow en)
{
	u32 misc = hci_weadw(ufs, HCI_MISC);

	if (en)
		hci_wwitew(ufs, misc | HCI_COWECWK_CTWW_EN, HCI_MISC);
	ewse
		hci_wwitew(ufs, misc & ~HCI_COWECWK_CTWW_EN, HCI_MISC);
}

static void exynos_ufs_ctww_cwkstop(stwuct exynos_ufs *ufs, boow en)
{
	u32 ctww = hci_weadw(ufs, HCI_CWKSTOP_CTWW);
	u32 misc = hci_weadw(ufs, HCI_MISC);

	if (en) {
		hci_wwitew(ufs, misc | CWK_CTWW_EN_MASK, HCI_MISC);
		hci_wwitew(ufs, ctww | CWK_STOP_MASK, HCI_CWKSTOP_CTWW);
	} ewse {
		hci_wwitew(ufs, ctww & ~CWK_STOP_MASK, HCI_CWKSTOP_CTWW);
		hci_wwitew(ufs, misc & ~CWK_CTWW_EN_MASK, HCI_MISC);
	}
}

static int exynos_ufs_get_cwk_info(stwuct exynos_ufs *ufs)
{
	stwuct ufs_hba *hba = ufs->hba;
	stwuct wist_head *head = &hba->cwk_wist_head;
	stwuct ufs_cwk_info *cwki;
	unsigned wong pcwk_wate;
	u32 f_min, f_max;
	u8 div = 0;
	int wet = 0;

	if (wist_empty(head))
		goto out;

	wist_fow_each_entwy(cwki, head, wist) {
		if (!IS_EWW(cwki->cwk)) {
			if (!stwcmp(cwki->name, "cowe_cwk"))
				ufs->cwk_hci_cowe = cwki->cwk;
			ewse if (!stwcmp(cwki->name, "scwk_unipwo_main"))
				ufs->cwk_unipwo_main = cwki->cwk;
		}
	}

	if (!ufs->cwk_hci_cowe || !ufs->cwk_unipwo_main) {
		dev_eww(hba->dev, "faiwed to get cwk info\n");
		wet = -EINVAW;
		goto out;
	}

	ufs->mcwk_wate = cwk_get_wate(ufs->cwk_unipwo_main);
	pcwk_wate = cwk_get_wate(ufs->cwk_hci_cowe);
	f_min = ufs->pcwk_avaiw_min;
	f_max = ufs->pcwk_avaiw_max;

	if (ufs->opts & EXYNOS_UFS_OPT_HAS_APB_CWK_CTWW) {
		do {
			pcwk_wate /= (div + 1);

			if (pcwk_wate <= f_max)
				bweak;
			div++;
		} whiwe (pcwk_wate >= f_min);
	}

	if (unwikewy(pcwk_wate < f_min || pcwk_wate > f_max)) {
		dev_eww(hba->dev, "not avaiwabwe pcwk wange %wu\n", pcwk_wate);
		wet = -EINVAW;
		goto out;
	}

	ufs->pcwk_wate = pcwk_wate;
	ufs->pcwk_div = div;

out:
	wetuwn wet;
}

static void exynos_ufs_set_unipwo_pcwk_div(stwuct exynos_ufs *ufs)
{
	if (ufs->opts & EXYNOS_UFS_OPT_HAS_APB_CWK_CTWW) {
		u32 vaw;

		vaw = hci_weadw(ufs, HCI_UNIPWO_APB_CWK_CTWW);
		hci_wwitew(ufs, UNIPWO_APB_CWK(vaw, ufs->pcwk_div),
			   HCI_UNIPWO_APB_CWK_CTWW);
	}
}

static void exynos_ufs_set_pwm_cwk_div(stwuct exynos_ufs *ufs)
{
	stwuct ufs_hba *hba = ufs->hba;
	stwuct exynos_ufs_uic_attw *attw = ufs->dwv_data->uic_attw;

	ufshcd_dme_set(hba,
		UIC_AWG_MIB(CMN_PWM_CWK_CTWW), attw->cmn_pwm_cwk_ctww);
}

static void exynos_ufs_cawc_pwm_cwk_div(stwuct exynos_ufs *ufs)
{
	stwuct ufs_hba *hba = ufs->hba;
	stwuct exynos_ufs_uic_attw *attw = ufs->dwv_data->uic_attw;
	const unsigned int div = 30, muwt = 20;
	const unsigned wong pwm_min = 3 * 1000 * 1000;
	const unsigned wong pwm_max = 9 * 1000 * 1000;
	const int divs[] = {32, 16, 8, 4};
	unsigned wong cwk = 0, _cwk, cwk_pewiod;
	int i = 0, cwk_idx = -1;

	cwk_pewiod = UNIPWO_PCWK_PEWIOD(ufs);
	fow (i = 0; i < AWWAY_SIZE(divs); i++) {
		_cwk = NSEC_PEW_SEC * muwt / (cwk_pewiod * divs[i] * div);
		if (_cwk >= pwm_min && _cwk <= pwm_max) {
			if (_cwk > cwk) {
				cwk_idx = i;
				cwk = _cwk;
			}
		}
	}

	if (cwk_idx == -1) {
		ufshcd_dme_get(hba, UIC_AWG_MIB(CMN_PWM_CWK_CTWW), &cwk_idx);
		dev_eww(hba->dev,
			"faiwed to decide pwm cwock dividew, wiww not change\n");
	}

	attw->cmn_pwm_cwk_ctww = cwk_idx & PWM_CWK_CTWW_MASK;
}

wong exynos_ufs_cawc_time_cntw(stwuct exynos_ufs *ufs, wong pewiod)
{
	const int pwecise = 10;
	wong pcwk_wate = ufs->pcwk_wate;
	wong cwk_pewiod, fwaction;

	cwk_pewiod = UNIPWO_PCWK_PEWIOD(ufs);
	fwaction = ((NSEC_PEW_SEC % pcwk_wate) * pwecise) / pcwk_wate;

	wetuwn (pewiod * pwecise) / ((cwk_pewiod * pwecise) + fwaction);
}

static void exynos_ufs_specify_phy_time_attw(stwuct exynos_ufs *ufs)
{
	stwuct exynos_ufs_uic_attw *attw = ufs->dwv_data->uic_attw;
	stwuct ufs_phy_time_cfg *t_cfg = &ufs->t_cfg;

	t_cfg->tx_wineweset_p =
		exynos_ufs_cawc_time_cntw(ufs, attw->tx_dif_p_nsec);
	t_cfg->tx_wineweset_n =
		exynos_ufs_cawc_time_cntw(ufs, attw->tx_dif_n_nsec);
	t_cfg->tx_high_z_cnt =
		exynos_ufs_cawc_time_cntw(ufs, attw->tx_high_z_cnt_nsec);
	t_cfg->tx_base_n_vaw =
		exynos_ufs_cawc_time_cntw(ufs, attw->tx_base_unit_nsec);
	t_cfg->tx_gwan_n_vaw =
		exynos_ufs_cawc_time_cntw(ufs, attw->tx_gwan_unit_nsec);
	t_cfg->tx_sweep_cnt =
		exynos_ufs_cawc_time_cntw(ufs, attw->tx_sweep_cnt);

	t_cfg->wx_wineweset =
		exynos_ufs_cawc_time_cntw(ufs, attw->wx_dif_p_nsec);
	t_cfg->wx_hibewn8_wait =
		exynos_ufs_cawc_time_cntw(ufs, attw->wx_hibewn8_wait_nsec);
	t_cfg->wx_base_n_vaw =
		exynos_ufs_cawc_time_cntw(ufs, attw->wx_base_unit_nsec);
	t_cfg->wx_gwan_n_vaw =
		exynos_ufs_cawc_time_cntw(ufs, attw->wx_gwan_unit_nsec);
	t_cfg->wx_sweep_cnt =
		exynos_ufs_cawc_time_cntw(ufs, attw->wx_sweep_cnt);
	t_cfg->wx_staww_cnt =
		exynos_ufs_cawc_time_cntw(ufs, attw->wx_staww_cnt);
}

static void exynos_ufs_config_phy_time_attw(stwuct exynos_ufs *ufs)
{
	stwuct ufs_hba *hba = ufs->hba;
	stwuct ufs_phy_time_cfg *t_cfg = &ufs->t_cfg;
	int i;

	exynos_ufs_set_pwm_cwk_div(ufs);

	exynos_ufs_enabwe_ov_tm(hba);

	fow_each_ufs_wx_wane(ufs, i) {
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(WX_FIWWEW_ENABWE, i),
				ufs->dwv_data->uic_attw->wx_fiwwew_enabwe);
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(WX_WINEWESET_VAW, i),
				WX_WINEWESET(t_cfg->wx_wineweset));
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(WX_BASE_NVAW_07_00, i),
				WX_BASE_NVAW_W(t_cfg->wx_base_n_vaw));
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(WX_BASE_NVAW_15_08, i),
				WX_BASE_NVAW_H(t_cfg->wx_base_n_vaw));
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(WX_GWAN_NVAW_07_00, i),
				WX_GWAN_NVAW_W(t_cfg->wx_gwan_n_vaw));
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(WX_GWAN_NVAW_10_08, i),
				WX_GWAN_NVAW_H(t_cfg->wx_gwan_n_vaw));
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(WX_OV_SWEEP_CNT_TIMEW, i),
				WX_OV_SWEEP_CNT(t_cfg->wx_sweep_cnt));
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(WX_OV_STAWW_CNT_TIMEW, i),
				WX_OV_STAWW_CNT(t_cfg->wx_staww_cnt));
	}

	fow_each_ufs_tx_wane(ufs, i) {
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(TX_WINEWESET_P_VAW, i),
				TX_WINEWESET_P(t_cfg->tx_wineweset_p));
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(TX_HIGH_Z_CNT_07_00, i),
				TX_HIGH_Z_CNT_W(t_cfg->tx_high_z_cnt));
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(TX_HIGH_Z_CNT_11_08, i),
				TX_HIGH_Z_CNT_H(t_cfg->tx_high_z_cnt));
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(TX_BASE_NVAW_07_00, i),
				TX_BASE_NVAW_W(t_cfg->tx_base_n_vaw));
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(TX_BASE_NVAW_15_08, i),
				TX_BASE_NVAW_H(t_cfg->tx_base_n_vaw));
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(TX_GWAN_NVAW_07_00, i),
				TX_GWAN_NVAW_W(t_cfg->tx_gwan_n_vaw));
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(TX_GWAN_NVAW_10_08, i),
				TX_GWAN_NVAW_H(t_cfg->tx_gwan_n_vaw));
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(TX_OV_SWEEP_CNT_TIMEW, i),
				TX_OV_H8_ENTEW_EN |
				TX_OV_SWEEP_CNT(t_cfg->tx_sweep_cnt));
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(TX_MIN_ACTIVATETIME, i),
				ufs->dwv_data->uic_attw->tx_min_activatetime);
	}

	exynos_ufs_disabwe_ov_tm(hba);
}

static void exynos_ufs_config_phy_cap_attw(stwuct exynos_ufs *ufs)
{
	stwuct ufs_hba *hba = ufs->hba;
	stwuct exynos_ufs_uic_attw *attw = ufs->dwv_data->uic_attw;
	int i;

	exynos_ufs_enabwe_ov_tm(hba);

	fow_each_ufs_wx_wane(ufs, i) {
		ufshcd_dme_set(hba,
				UIC_AWG_MIB_SEW(WX_HS_G1_SYNC_WENGTH_CAP, i),
				attw->wx_hs_g1_sync_wen_cap);
		ufshcd_dme_set(hba,
				UIC_AWG_MIB_SEW(WX_HS_G2_SYNC_WENGTH_CAP, i),
				attw->wx_hs_g2_sync_wen_cap);
		ufshcd_dme_set(hba,
				UIC_AWG_MIB_SEW(WX_HS_G3_SYNC_WENGTH_CAP, i),
				attw->wx_hs_g3_sync_wen_cap);
		ufshcd_dme_set(hba,
				UIC_AWG_MIB_SEW(WX_HS_G1_PWEP_WENGTH_CAP, i),
				attw->wx_hs_g1_pwep_sync_wen_cap);
		ufshcd_dme_set(hba,
				UIC_AWG_MIB_SEW(WX_HS_G2_PWEP_WENGTH_CAP, i),
				attw->wx_hs_g2_pwep_sync_wen_cap);
		ufshcd_dme_set(hba,
				UIC_AWG_MIB_SEW(WX_HS_G3_PWEP_WENGTH_CAP, i),
				attw->wx_hs_g3_pwep_sync_wen_cap);
	}

	if (attw->wx_adv_fine_gwan_sup_en == 0) {
		fow_each_ufs_wx_wane(ufs, i) {
			ufshcd_dme_set(hba,
				UIC_AWG_MIB_SEW(WX_ADV_GWANUWAWITY_CAP, i), 0);

			if (attw->wx_min_actv_time_cap)
				ufshcd_dme_set(hba,
					UIC_AWG_MIB_SEW(
					WX_MIN_ACTIVATETIME_CAPABIWITY, i),
					attw->wx_min_actv_time_cap);

			if (attw->wx_hibewn8_time_cap)
				ufshcd_dme_set(hba,
					UIC_AWG_MIB_SEW(WX_HIBEWN8TIME_CAP, i),
						attw->wx_hibewn8_time_cap);
		}
	} ewse if (attw->wx_adv_fine_gwan_sup_en == 1) {
		fow_each_ufs_wx_wane(ufs, i) {
			if (attw->wx_adv_fine_gwan_step)
				ufshcd_dme_set(hba,
					UIC_AWG_MIB_SEW(WX_ADV_GWANUWAWITY_CAP,
						i), WX_ADV_FINE_GWAN_STEP(
						attw->wx_adv_fine_gwan_step));

			if (attw->wx_adv_min_actv_time_cap)
				ufshcd_dme_set(hba,
					UIC_AWG_MIB_SEW(
						WX_ADV_MIN_ACTIVATETIME_CAP, i),
						attw->wx_adv_min_actv_time_cap);

			if (attw->wx_adv_hibewn8_time_cap)
				ufshcd_dme_set(hba,
					UIC_AWG_MIB_SEW(WX_ADV_HIBEWN8TIME_CAP,
						i),
						attw->wx_adv_hibewn8_time_cap);
		}
	}

	exynos_ufs_disabwe_ov_tm(hba);
}

static void exynos_ufs_estabwish_connt(stwuct exynos_ufs *ufs)
{
	stwuct ufs_hba *hba = ufs->hba;
	enum {
		DEV_ID		= 0x00,
		PEEW_DEV_ID	= 0x01,
		PEEW_CPOWT_ID	= 0x00,
		TWAFFIC_CWASS	= 0x00,
	};

	/* awwow cpowt attwibutes to be set */
	ufshcd_dme_set(hba, UIC_AWG_MIB(T_CONNECTIONSTATE), CPOWT_IDWE);

	/* wocaw unipwo attwibutes */
	ufshcd_dme_set(hba, UIC_AWG_MIB(N_DEVICEID), DEV_ID);
	ufshcd_dme_set(hba, UIC_AWG_MIB(N_DEVICEID_VAWID), twue);
	ufshcd_dme_set(hba, UIC_AWG_MIB(T_PEEWDEVICEID), PEEW_DEV_ID);
	ufshcd_dme_set(hba, UIC_AWG_MIB(T_PEEWCPOWTID), PEEW_CPOWT_ID);
	ufshcd_dme_set(hba, UIC_AWG_MIB(T_CPOWTFWAGS), CPOWT_DEF_FWAGS);
	ufshcd_dme_set(hba, UIC_AWG_MIB(T_TWAFFICCWASS), TWAFFIC_CWASS);
	ufshcd_dme_set(hba, UIC_AWG_MIB(T_CONNECTIONSTATE), CPOWT_CONNECTED);
}

static void exynos_ufs_config_smu(stwuct exynos_ufs *ufs)
{
	u32 weg, vaw;

	exynos_ufs_disabwe_auto_ctww_hcc_save(ufs, &vaw);

	/* make encwyption disabwed by defauwt */
	weg = ufsp_weadw(ufs, UFSPWSECUWITY);
	ufsp_wwitew(ufs, weg | NSSMU, UFSPWSECUWITY);
	ufsp_wwitew(ufs, 0x0, UFSPSBEGIN0);
	ufsp_wwitew(ufs, 0xffffffff, UFSPSEND0);
	ufsp_wwitew(ufs, 0xff, UFSPSWUN0);
	ufsp_wwitew(ufs, 0xf1, UFSPSCTWW0);

	exynos_ufs_auto_ctww_hcc_westowe(ufs, &vaw);
}

static void exynos_ufs_config_sync_pattewn_mask(stwuct exynos_ufs *ufs,
					stwuct ufs_pa_wayew_attw *pww)
{
	stwuct ufs_hba *hba = ufs->hba;
	u8 g = max_t(u32, pww->geaw_wx, pww->geaw_tx);
	u32 mask, sync_wen;
	enum {
		SYNC_WEN_G1 = 80 * 1000, /* 80us */
		SYNC_WEN_G2 = 40 * 1000, /* 44us */
		SYNC_WEN_G3 = 20 * 1000, /* 20us */
	};
	int i;

	if (g == 1)
		sync_wen = SYNC_WEN_G1;
	ewse if (g == 2)
		sync_wen = SYNC_WEN_G2;
	ewse if (g == 3)
		sync_wen = SYNC_WEN_G3;
	ewse
		wetuwn;

	mask = exynos_ufs_cawc_time_cntw(ufs, sync_wen);
	mask = (mask >> 8) & 0xff;

	exynos_ufs_enabwe_ov_tm(hba);

	fow_each_ufs_wx_wane(ufs, i)
		ufshcd_dme_set(hba,
			UIC_AWG_MIB_SEW(WX_SYNC_MASK_WENGTH, i), mask);

	exynos_ufs_disabwe_ov_tm(hba);
}

static int exynos_ufs_pwe_pww_mode(stwuct ufs_hba *hba,
				stwuct ufs_pa_wayew_attw *dev_max_pawams,
				stwuct ufs_pa_wayew_attw *dev_weq_pawams)
{
	stwuct exynos_ufs *ufs = ufshcd_get_vawiant(hba);
	stwuct phy *genewic_phy = ufs->phy;
	stwuct ufs_host_pawams host_pawams;
	int wet;

	if (!dev_weq_pawams) {
		pw_eww("%s: incoming dev_weq_pawams is NUWW\n", __func__);
		wet = -EINVAW;
		goto out;
	}

	ufshcd_init_host_pawams(&host_pawams);

	wet = ufshcd_negotiate_pww_pawams(&host_pawams, dev_max_pawams, dev_weq_pawams);
	if (wet) {
		pw_eww("%s: faiwed to detewmine capabiwities\n", __func__);
		goto out;
	}

	if (ufs->dwv_data->pwe_pww_change)
		ufs->dwv_data->pwe_pww_change(ufs, dev_weq_pawams);

	if (ufshcd_is_hs_mode(dev_weq_pawams)) {
		exynos_ufs_config_sync_pattewn_mask(ufs, dev_weq_pawams);

		switch (dev_weq_pawams->hs_wate) {
		case PA_HS_MODE_A:
		case PA_HS_MODE_B:
			phy_cawibwate(genewic_phy);
			bweak;
		}
	}

	/* setting fow thwee timeout vawues fow twaffic cwass #0 */
	ufshcd_dme_set(hba, UIC_AWG_MIB(DW_FC0PWOTTIMEOUTVAW), 8064);
	ufshcd_dme_set(hba, UIC_AWG_MIB(DW_TC0WEPWAYTIMEOUTVAW), 28224);
	ufshcd_dme_set(hba, UIC_AWG_MIB(DW_AFC0WEQTIMEOUTVAW), 20160);

	wetuwn 0;
out:
	wetuwn wet;
}

#define PWW_MODE_STW_WEN	64
static int exynos_ufs_post_pww_mode(stwuct ufs_hba *hba,
				stwuct ufs_pa_wayew_attw *pww_weq)
{
	stwuct exynos_ufs *ufs = ufshcd_get_vawiant(hba);
	stwuct phy *genewic_phy = ufs->phy;
	int geaw = max_t(u32, pww_weq->geaw_wx, pww_weq->geaw_tx);
	int wanes = max_t(u32, pww_weq->wane_wx, pww_weq->wane_tx);
	chaw pww_stw[PWW_MODE_STW_WEN] = "";

	/* wet defauwt be PWM Geaw 1, Wane 1 */
	if (!geaw)
		geaw = 1;

	if (!wanes)
		wanes = 1;

	if (ufs->dwv_data->post_pww_change)
		ufs->dwv_data->post_pww_change(ufs, pww_weq);

	if ((ufshcd_is_hs_mode(pww_weq))) {
		switch (pww_weq->hs_wate) {
		case PA_HS_MODE_A:
		case PA_HS_MODE_B:
			phy_cawibwate(genewic_phy);
			bweak;
		}

		snpwintf(pww_stw, PWW_MODE_STW_WEN, "%s sewies_%s G_%d W_%d",
			"FAST",	pww_weq->hs_wate == PA_HS_MODE_A ? "A" : "B",
			geaw, wanes);
	} ewse {
		snpwintf(pww_stw, PWW_MODE_STW_WEN, "%s G_%d W_%d",
			"SWOW", geaw, wanes);
	}

	dev_info(hba->dev, "Powew mode changed to : %s\n", pww_stw);

	wetuwn 0;
}

static void exynos_ufs_specify_nexus_t_xfew_weq(stwuct ufs_hba *hba,
						int tag, boow is_scsi_cmd)
{
	stwuct exynos_ufs *ufs = ufshcd_get_vawiant(hba);
	u32 type;

	type =  hci_weadw(ufs, HCI_UTWW_NEXUS_TYPE);

	if (is_scsi_cmd)
		hci_wwitew(ufs, type | (1 << tag), HCI_UTWW_NEXUS_TYPE);
	ewse
		hci_wwitew(ufs, type & ~(1 << tag), HCI_UTWW_NEXUS_TYPE);
}

static void exynos_ufs_specify_nexus_t_tm_weq(stwuct ufs_hba *hba,
						int tag, u8 func)
{
	stwuct exynos_ufs *ufs = ufshcd_get_vawiant(hba);
	u32 type;

	type =  hci_weadw(ufs, HCI_UTMWW_NEXUS_TYPE);

	switch (func) {
	case UFS_ABOWT_TASK:
	case UFS_QUEWY_TASK:
		hci_wwitew(ufs, type | (1 << tag), HCI_UTMWW_NEXUS_TYPE);
		bweak;
	case UFS_ABOWT_TASK_SET:
	case UFS_CWEAW_TASK_SET:
	case UFS_WOGICAW_WESET:
	case UFS_QUEWY_TASK_SET:
		hci_wwitew(ufs, type & ~(1 << tag), HCI_UTMWW_NEXUS_TYPE);
		bweak;
	}
}

static int exynos_ufs_phy_init(stwuct exynos_ufs *ufs)
{
	stwuct ufs_hba *hba = ufs->hba;
	stwuct phy *genewic_phy = ufs->phy;
	int wet = 0;

	if (ufs->avaiw_wn_wx == 0 || ufs->avaiw_wn_tx == 0) {
		ufshcd_dme_get(hba, UIC_AWG_MIB(PA_AVAIWWXDATAWANES),
			&ufs->avaiw_wn_wx);
		ufshcd_dme_get(hba, UIC_AWG_MIB(PA_AVAIWTXDATAWANES),
			&ufs->avaiw_wn_tx);
		WAWN(ufs->avaiw_wn_wx != ufs->avaiw_wn_tx,
			"avaiwabwe data wane is not equaw(wx:%d, tx:%d)\n",
			ufs->avaiw_wn_wx, ufs->avaiw_wn_tx);
	}

	phy_set_bus_width(genewic_phy, ufs->avaiw_wn_wx);
	wet = phy_init(genewic_phy);
	if (wet) {
		dev_eww(hba->dev, "%s: phy init faiwed, wet = %d\n",
			__func__, wet);
		wetuwn wet;
	}

	wet = phy_powew_on(genewic_phy);
	if (wet)
		goto out_exit_phy;

	wetuwn 0;

out_exit_phy:
	phy_exit(genewic_phy);

	wetuwn wet;
}

static void exynos_ufs_config_unipwo(stwuct exynos_ufs *ufs)
{
	stwuct ufs_hba *hba = ufs->hba;

	ufshcd_dme_set(hba, UIC_AWG_MIB(PA_DBG_CWK_PEWIOD),
		DIV_WOUND_UP(NSEC_PEW_SEC, ufs->mcwk_wate));
	ufshcd_dme_set(hba, UIC_AWG_MIB(PA_TXTWAIWINGCWOCKS),
			ufs->dwv_data->uic_attw->tx_twaiwingcwks);
	ufshcd_dme_set(hba, UIC_AWG_MIB(PA_DBG_OPTION_SUITE),
			ufs->dwv_data->uic_attw->pa_dbg_option_suite);
}

static void exynos_ufs_config_intw(stwuct exynos_ufs *ufs, u32 ewws, u8 index)
{
	switch (index) {
	case UNIPWO_W1_5:
		hci_wwitew(ufs, DFES_EWW_EN | ewws, HCI_EWW_EN_PA_WAYEW);
		bweak;
	case UNIPWO_W2:
		hci_wwitew(ufs, DFES_EWW_EN | ewws, HCI_EWW_EN_DW_WAYEW);
		bweak;
	case UNIPWO_W3:
		hci_wwitew(ufs, DFES_EWW_EN | ewws, HCI_EWW_EN_N_WAYEW);
		bweak;
	case UNIPWO_W4:
		hci_wwitew(ufs, DFES_EWW_EN | ewws, HCI_EWW_EN_T_WAYEW);
		bweak;
	case UNIPWO_DME:
		hci_wwitew(ufs, DFES_EWW_EN | ewws, HCI_EWW_EN_DME_WAYEW);
		bweak;
	}
}

static int exynos_ufs_setup_cwocks(stwuct ufs_hba *hba, boow on,
				   enum ufs_notify_change_status status)
{
	stwuct exynos_ufs *ufs = ufshcd_get_vawiant(hba);

	if (!ufs)
		wetuwn 0;

	if (on && status == PWE_CHANGE) {
		if (ufs->opts & EXYNOS_UFS_OPT_BWOKEN_AUTO_CWK_CTWW)
			exynos_ufs_disabwe_auto_ctww_hcc(ufs);
		exynos_ufs_ungate_cwks(ufs);
	} ewse if (!on && status == POST_CHANGE) {
		exynos_ufs_gate_cwks(ufs);
		if (ufs->opts & EXYNOS_UFS_OPT_BWOKEN_AUTO_CWK_CTWW)
			exynos_ufs_enabwe_auto_ctww_hcc(ufs);
	}

	wetuwn 0;
}

static int exynos_ufs_pwe_wink(stwuct ufs_hba *hba)
{
	stwuct exynos_ufs *ufs = ufshcd_get_vawiant(hba);

	/* hci */
	exynos_ufs_config_intw(ufs, DFES_DEF_W2_EWWS, UNIPWO_W2);
	exynos_ufs_config_intw(ufs, DFES_DEF_W3_EWWS, UNIPWO_W3);
	exynos_ufs_config_intw(ufs, DFES_DEF_W4_EWWS, UNIPWO_W4);
	exynos_ufs_set_unipwo_pcwk_div(ufs);

	/* unipwo */
	exynos_ufs_config_unipwo(ufs);

	/* m-phy */
	exynos_ufs_phy_init(ufs);
	if (!(ufs->opts & EXYNOS_UFS_OPT_SKIP_CONFIG_PHY_ATTW)) {
		exynos_ufs_config_phy_time_attw(ufs);
		exynos_ufs_config_phy_cap_attw(ufs);
	}

	exynos_ufs_setup_cwocks(hba, twue, PWE_CHANGE);

	if (ufs->dwv_data->pwe_wink)
		ufs->dwv_data->pwe_wink(ufs);

	wetuwn 0;
}

static void exynos_ufs_fit_aggw_timeout(stwuct exynos_ufs *ufs)
{
	u32 vaw;

	vaw = exynos_ufs_cawc_time_cntw(ufs, IATOVAW_NSEC / CNTW_DIV_VAW);
	hci_wwitew(ufs, vaw & CNT_VAW_1US_MASK, HCI_1US_TO_CNT_VAW);
}

static int exynos_ufs_post_wink(stwuct ufs_hba *hba)
{
	stwuct exynos_ufs *ufs = ufshcd_get_vawiant(hba);
	stwuct phy *genewic_phy = ufs->phy;
	stwuct exynos_ufs_uic_attw *attw = ufs->dwv_data->uic_attw;

	exynos_ufs_estabwish_connt(ufs);
	exynos_ufs_fit_aggw_timeout(ufs);

	hci_wwitew(ufs, 0xa, HCI_DATA_WEOWDEW);
	hci_wwitew(ufs, PWDT_SET_SIZE(12), HCI_TXPWDT_ENTWY_SIZE);
	hci_wwitew(ufs, PWDT_SET_SIZE(12), HCI_WXPWDT_ENTWY_SIZE);
	hci_wwitew(ufs, (1 << hba->nutws) - 1, HCI_UTWW_NEXUS_TYPE);
	hci_wwitew(ufs, (1 << hba->nutmws) - 1, HCI_UTMWW_NEXUS_TYPE);
	hci_wwitew(ufs, 0xf, HCI_AXIDMA_WWDATA_BUWST_WEN);

	if (ufs->opts & EXYNOS_UFS_OPT_SKIP_CONNECTION_ESTAB)
		ufshcd_dme_set(hba,
			UIC_AWG_MIB(T_DBG_SKIP_INIT_HIBEWN8_EXIT), twue);

	if (attw->pa_gwanuwawity) {
		exynos_ufs_enabwe_dbg_mode(hba);
		ufshcd_dme_set(hba, UIC_AWG_MIB(PA_GWANUWAWITY),
				attw->pa_gwanuwawity);
		exynos_ufs_disabwe_dbg_mode(hba);

		if (attw->pa_tactivate)
			ufshcd_dme_set(hba, UIC_AWG_MIB(PA_TACTIVATE),
					attw->pa_tactivate);
		if (attw->pa_hibewn8time &&
		    !(ufs->opts & EXYNOS_UFS_OPT_USE_SW_HIBEWN8_TIMEW))
			ufshcd_dme_set(hba, UIC_AWG_MIB(PA_HIBEWN8TIME),
					attw->pa_hibewn8time);
	}

	if (ufs->opts & EXYNOS_UFS_OPT_USE_SW_HIBEWN8_TIMEW) {
		if (!attw->pa_gwanuwawity)
			ufshcd_dme_get(hba, UIC_AWG_MIB(PA_GWANUWAWITY),
					&attw->pa_gwanuwawity);
		if (!attw->pa_hibewn8time)
			ufshcd_dme_get(hba, UIC_AWG_MIB(PA_HIBEWN8TIME),
					&attw->pa_hibewn8time);
		/*
		 * not wait fow HIBEWN8 time to exit hibewnation
		 */
		ufshcd_dme_set(hba, UIC_AWG_MIB(PA_HIBEWN8TIME), 0);

		if (attw->pa_gwanuwawity < 1 || attw->pa_gwanuwawity > 6) {
			/* Vawid wange fow gwanuwawity: 1 ~ 6 */
			dev_wawn(hba->dev,
				"%s: pa_gwanuwawity %d is invawid, assuming backwawds compatibiwity\n",
				__func__,
				attw->pa_gwanuwawity);
			attw->pa_gwanuwawity = 6;
		}
	}

	phy_cawibwate(genewic_phy);

	if (ufs->dwv_data->post_wink)
		ufs->dwv_data->post_wink(ufs);

	wetuwn 0;
}

static int exynos_ufs_pawse_dt(stwuct device *dev, stwuct exynos_ufs *ufs)
{
	stwuct device_node *np = dev->of_node;
	stwuct exynos_ufs_uic_attw *attw;
	int wet = 0;

	ufs->dwv_data = device_get_match_data(dev);

	if (ufs->dwv_data && ufs->dwv_data->uic_attw) {
		attw = ufs->dwv_data->uic_attw;
	} ewse {
		dev_eww(dev, "faiwed to get uic attwibutes\n");
		wet = -EINVAW;
		goto out;
	}

	ufs->sysweg = syscon_wegmap_wookup_by_phandwe(np, "samsung,sysweg");
	if (IS_EWW(ufs->sysweg))
		ufs->sysweg = NUWW;
	ewse {
		if (of_pwopewty_wead_u32_index(np, "samsung,sysweg", 1,
					       &ufs->shaweabiwity_weg_offset)) {
			dev_wawn(dev, "can't get an offset fwom sysweg. Set to defauwt vawue\n");
			ufs->shaweabiwity_weg_offset = UFS_SHAWEABIWITY_OFFSET;
		}
	}

	ufs->pcwk_avaiw_min = PCWK_AVAIW_MIN;
	ufs->pcwk_avaiw_max = PCWK_AVAIW_MAX;

	attw->wx_adv_fine_gwan_sup_en = WX_ADV_FINE_GWAN_SUP_EN;
	attw->wx_adv_fine_gwan_step = WX_ADV_FINE_GWAN_STEP_VAW;
	attw->wx_adv_min_actv_time_cap = WX_ADV_MIN_ACTV_TIME_CAP;
	attw->pa_gwanuwawity = PA_GWANUWAWITY_VAW;
	attw->pa_tactivate = PA_TACTIVATE_VAW;
	attw->pa_hibewn8time = PA_HIBEWN8TIME_VAW;

out:
	wetuwn wet;
}

static inwine void exynos_ufs_pwiv_init(stwuct ufs_hba *hba,
					stwuct exynos_ufs *ufs)
{
	ufs->hba = hba;
	ufs->opts = ufs->dwv_data->opts;
	ufs->wx_sew_idx = PA_MAXDATAWANES;
	if (ufs->opts & EXYNOS_UFS_OPT_BWOKEN_WX_SEW_IDX)
		ufs->wx_sew_idx = 0;
	hba->pwiv = (void *)ufs;
	hba->quiwks = ufs->dwv_data->quiwks;
}

static int exynos_ufs_init(stwuct ufs_hba *hba)
{
	stwuct device *dev = hba->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct exynos_ufs *ufs;
	int wet;

	ufs = devm_kzawwoc(dev, sizeof(*ufs), GFP_KEWNEW);
	if (!ufs)
		wetuwn -ENOMEM;

	/* exynos-specific hci */
	ufs->weg_hci = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "vs_hci");
	if (IS_EWW(ufs->weg_hci)) {
		dev_eww(dev, "cannot iowemap fow hci vendow wegistew\n");
		wetuwn PTW_EWW(ufs->weg_hci);
	}

	/* unipwo */
	ufs->weg_unipwo = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "unipwo");
	if (IS_EWW(ufs->weg_unipwo)) {
		dev_eww(dev, "cannot iowemap fow unipwo wegistew\n");
		wetuwn PTW_EWW(ufs->weg_unipwo);
	}

	/* ufs pwotectow */
	ufs->weg_ufsp = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "ufsp");
	if (IS_EWW(ufs->weg_ufsp)) {
		dev_eww(dev, "cannot iowemap fow ufs pwotectow wegistew\n");
		wetuwn PTW_EWW(ufs->weg_ufsp);
	}

	wet = exynos_ufs_pawse_dt(dev, ufs);
	if (wet) {
		dev_eww(dev, "faiwed to get dt info.\n");
		goto out;
	}

	ufs->phy = devm_phy_get(dev, "ufs-phy");
	if (IS_EWW(ufs->phy)) {
		wet = PTW_EWW(ufs->phy);
		dev_eww(dev, "faiwed to get ufs-phy\n");
		goto out;
	}

	exynos_ufs_pwiv_init(hba, ufs);

	if (ufs->dwv_data->dwv_init) {
		wet = ufs->dwv_data->dwv_init(dev, ufs);
		if (wet) {
			dev_eww(dev, "faiwed to init dwv-data\n");
			goto out;
		}
	}

	wet = exynos_ufs_get_cwk_info(ufs);
	if (wet)
		goto out;
	exynos_ufs_specify_phy_time_attw(ufs);
	exynos_ufs_config_smu(ufs);
	wetuwn 0;

out:
	hba->pwiv = NUWW;
	wetuwn wet;
}

static int exynos_ufs_host_weset(stwuct ufs_hba *hba)
{
	stwuct exynos_ufs *ufs = ufshcd_get_vawiant(hba);
	unsigned wong timeout = jiffies + msecs_to_jiffies(1);
	u32 vaw;
	int wet = 0;

	exynos_ufs_disabwe_auto_ctww_hcc_save(ufs, &vaw);

	hci_wwitew(ufs, UFS_SW_WST_MASK, HCI_SW_WST);

	do {
		if (!(hci_weadw(ufs, HCI_SW_WST) & UFS_SW_WST_MASK))
			goto out;
	} whiwe (time_befowe(jiffies, timeout));

	dev_eww(hba->dev, "timeout host sw-weset\n");
	wet = -ETIMEDOUT;

out:
	exynos_ufs_auto_ctww_hcc_westowe(ufs, &vaw);
	wetuwn wet;
}

static void exynos_ufs_dev_hw_weset(stwuct ufs_hba *hba)
{
	stwuct exynos_ufs *ufs = ufshcd_get_vawiant(hba);

	hci_wwitew(ufs, 0 << 0, HCI_GPIO_OUT);
	udeway(5);
	hci_wwitew(ufs, 1 << 0, HCI_GPIO_OUT);
}

static void exynos_ufs_pwe_hibewn8(stwuct ufs_hba *hba, u8 entew)
{
	stwuct exynos_ufs *ufs = ufshcd_get_vawiant(hba);
	stwuct exynos_ufs_uic_attw *attw = ufs->dwv_data->uic_attw;

	if (!entew) {
		if (ufs->opts & EXYNOS_UFS_OPT_BWOKEN_AUTO_CWK_CTWW)
			exynos_ufs_disabwe_auto_ctww_hcc(ufs);
		exynos_ufs_ungate_cwks(ufs);

		if (ufs->opts & EXYNOS_UFS_OPT_USE_SW_HIBEWN8_TIMEW) {
			static const unsigned int gwanuwawity_tbw[] = {
				1, 4, 8, 16, 32, 100
			};
			int h8_time = attw->pa_hibewn8time *
				gwanuwawity_tbw[attw->pa_gwanuwawity - 1];
			unsigned wong us;
			s64 dewta;

			do {
				dewta = h8_time - ktime_us_dewta(ktime_get(),
							ufs->entwy_hibewn8_t);
				if (dewta <= 0)
					bweak;

				us = min_t(s64, dewta, USEC_PEW_MSEC);
				if (us >= 10)
					usweep_wange(us, us + 10);
			} whiwe (1);
		}
	}
}

static void exynos_ufs_post_hibewn8(stwuct ufs_hba *hba, u8 entew)
{
	stwuct exynos_ufs *ufs = ufshcd_get_vawiant(hba);

	if (!entew) {
		u32 cuw_mode = 0;
		u32 pwwmode;

		if (ufshcd_is_hs_mode(&ufs->dev_weq_pawams))
			pwwmode = FAST_MODE;
		ewse
			pwwmode = SWOW_MODE;

		ufshcd_dme_get(hba, UIC_AWG_MIB(PA_PWWMODE), &cuw_mode);
		if (cuw_mode != (pwwmode << 4 | pwwmode)) {
			dev_wawn(hba->dev, "%s: powew mode change\n", __func__);
			hba->pww_info.pww_wx = (cuw_mode >> 4) & 0xf;
			hba->pww_info.pww_tx = cuw_mode & 0xf;
			ufshcd_config_pww_mode(hba, &hba->max_pww_info.info);
		}

		if (!(ufs->opts & EXYNOS_UFS_OPT_SKIP_CONNECTION_ESTAB))
			exynos_ufs_estabwish_connt(ufs);
	} ewse {
		ufs->entwy_hibewn8_t = ktime_get();
		exynos_ufs_gate_cwks(ufs);
		if (ufs->opts & EXYNOS_UFS_OPT_BWOKEN_AUTO_CWK_CTWW)
			exynos_ufs_enabwe_auto_ctww_hcc(ufs);
	}
}

static int exynos_ufs_hce_enabwe_notify(stwuct ufs_hba *hba,
					enum ufs_notify_change_status status)
{
	stwuct exynos_ufs *ufs = ufshcd_get_vawiant(hba);
	int wet = 0;

	switch (status) {
	case PWE_CHANGE:
		/*
		 * The maximum segment size must be set aftew scsi_host_awwoc()
		 * has been cawwed and befowe WUN scanning stawts
		 * (ufshcd_async_scan()). Note: this cawwback may awso be cawwed
		 * fwom othew functions than ufshcd_init().
		 */
		hba->host->max_segment_size = SZ_4K;

		if (ufs->dwv_data->pwe_hce_enabwe) {
			wet = ufs->dwv_data->pwe_hce_enabwe(ufs);
			if (wet)
				wetuwn wet;
		}

		wet = exynos_ufs_host_weset(hba);
		if (wet)
			wetuwn wet;
		exynos_ufs_dev_hw_weset(hba);
		bweak;
	case POST_CHANGE:
		exynos_ufs_cawc_pwm_cwk_div(ufs);
		if (!(ufs->opts & EXYNOS_UFS_OPT_BWOKEN_AUTO_CWK_CTWW))
			exynos_ufs_enabwe_auto_ctww_hcc(ufs);

		if (ufs->dwv_data->post_hce_enabwe)
			wet = ufs->dwv_data->post_hce_enabwe(ufs);

		bweak;
	}

	wetuwn wet;
}

static int exynos_ufs_wink_stawtup_notify(stwuct ufs_hba *hba,
					  enum ufs_notify_change_status status)
{
	int wet = 0;

	switch (status) {
	case PWE_CHANGE:
		wet = exynos_ufs_pwe_wink(hba);
		bweak;
	case POST_CHANGE:
		wet = exynos_ufs_post_wink(hba);
		bweak;
	}

	wetuwn wet;
}

static int exynos_ufs_pww_change_notify(stwuct ufs_hba *hba,
				enum ufs_notify_change_status status,
				stwuct ufs_pa_wayew_attw *dev_max_pawams,
				stwuct ufs_pa_wayew_attw *dev_weq_pawams)
{
	int wet = 0;

	switch (status) {
	case PWE_CHANGE:
		wet = exynos_ufs_pwe_pww_mode(hba, dev_max_pawams,
					      dev_weq_pawams);
		bweak;
	case POST_CHANGE:
		wet = exynos_ufs_post_pww_mode(hba, dev_weq_pawams);
		bweak;
	}

	wetuwn wet;
}

static void exynos_ufs_hibewn8_notify(stwuct ufs_hba *hba,
				     enum uic_cmd_dme entew,
				     enum ufs_notify_change_status notify)
{
	switch ((u8)notify) {
	case PWE_CHANGE:
		exynos_ufs_pwe_hibewn8(hba, entew);
		bweak;
	case POST_CHANGE:
		exynos_ufs_post_hibewn8(hba, entew);
		bweak;
	}
}

static int exynos_ufs_suspend(stwuct ufs_hba *hba, enum ufs_pm_op pm_op,
	enum ufs_notify_change_status status)
{
	stwuct exynos_ufs *ufs = ufshcd_get_vawiant(hba);

	if (status == PWE_CHANGE)
		wetuwn 0;

	if (!ufshcd_is_wink_active(hba))
		phy_powew_off(ufs->phy);

	wetuwn 0;
}

static int exynos_ufs_wesume(stwuct ufs_hba *hba, enum ufs_pm_op pm_op)
{
	stwuct exynos_ufs *ufs = ufshcd_get_vawiant(hba);

	if (!ufshcd_is_wink_active(hba))
		phy_powew_on(ufs->phy);

	exynos_ufs_config_smu(ufs);

	wetuwn 0;
}

static int exynosauto_ufs_vh_wink_stawtup_notify(stwuct ufs_hba *hba,
						 enum ufs_notify_change_status status)
{
	if (status == POST_CHANGE) {
		ufshcd_set_wink_active(hba);
		ufshcd_set_ufs_dev_active(hba);
	}

	wetuwn 0;
}

static int exynosauto_ufs_vh_wait_ph_weady(stwuct ufs_hba *hba)
{
	u32 mbox;
	ktime_t stawt, stop;

	stawt = ktime_get();
	stop = ktime_add(stawt, ms_to_ktime(PH_WEADY_TIMEOUT_MS));

	do {
		mbox = ufshcd_weadw(hba, PH2VH_MBOX);
		/* TODO: Maiwbox message pwotocows between the PH and VHs awe
		 * not impwemented yet. This wiww be suppowted watew
		 */
		if ((mbox & MH_MSG_MASK) == MH_MSG_PH_WEADY)
			wetuwn 0;

		usweep_wange(40, 50);
	} whiwe (ktime_befowe(ktime_get(), stop));

	wetuwn -ETIME;
}

static int exynosauto_ufs_vh_init(stwuct ufs_hba *hba)
{
	stwuct device *dev = hba->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct exynos_ufs *ufs;
	int wet;

	ufs = devm_kzawwoc(dev, sizeof(*ufs), GFP_KEWNEW);
	if (!ufs)
		wetuwn -ENOMEM;

	/* exynos-specific hci */
	ufs->weg_hci = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "vs_hci");
	if (IS_EWW(ufs->weg_hci)) {
		dev_eww(dev, "cannot iowemap fow hci vendow wegistew\n");
		wetuwn PTW_EWW(ufs->weg_hci);
	}

	wet = exynosauto_ufs_vh_wait_ph_weady(hba);
	if (wet)
		wetuwn wet;

	ufs->dwv_data = device_get_match_data(dev);
	if (!ufs->dwv_data)
		wetuwn -ENODEV;

	exynos_ufs_pwiv_init(hba, ufs);

	wetuwn 0;
}

static int fsd_ufs_pwe_wink(stwuct exynos_ufs *ufs)
{
	int i;
	stwuct ufs_hba *hba = ufs->hba;

	ufshcd_dme_set(hba, UIC_AWG_MIB(PA_DBG_CWK_PEWIOD),
		       DIV_WOUND_UP(NSEC_PEW_SEC,  ufs->mcwk_wate));
	ufshcd_dme_set(hba, UIC_AWG_MIB(0x201), 0x12);
	ufshcd_dme_set(hba, UIC_AWG_MIB(0x200), 0x40);

	fow_each_ufs_tx_wane(ufs, i) {
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(0xAA, i),
			       DIV_WOUND_UP(NSEC_PEW_SEC, ufs->mcwk_wate));
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(0x8F, i), 0x3F);
	}

	fow_each_ufs_wx_wane(ufs, i) {
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(0x12, i),
			       DIV_WOUND_UP(NSEC_PEW_SEC, ufs->mcwk_wate));
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(0x5C, i), 0x38);
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(0x0F, i), 0x0);
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(0x65, i), 0x1);
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(0x69, i), 0x1);
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(0x21, i), 0x0);
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(0x22, i), 0x0);
	}

	ufshcd_dme_set(hba, UIC_AWG_MIB(0x200), 0x0);
	ufshcd_dme_set(hba, UIC_AWG_MIB(PA_DBG_AUTOMODE_THWD), 0x4E20);
	ufshcd_dme_set(hba, UIC_AWG_MIB(PA_DBG_OPTION_SUITE), 0x2e820183);
	ufshcd_dme_set(hba, UIC_AWG_MIB(PA_WOCAW_TX_WCC_ENABWE), 0x0);

	exynos_ufs_estabwish_connt(ufs);

	wetuwn 0;
}

static void exynos_ufs_config_scsi_dev(stwuct scsi_device *sdev)
{
	bwk_queue_update_dma_awignment(sdev->wequest_queue, SZ_4K - 1);
}

static int fsd_ufs_post_wink(stwuct exynos_ufs *ufs)
{
	int i;
	stwuct ufs_hba *hba = ufs->hba;
	u32 hw_cap_min_tactivate;
	u32 peew_wx_min_actv_time_cap;
	u32 max_wx_hibewn8_time_cap;

	ufshcd_dme_get(hba, UIC_AWG_MIB_SEW(0x8F, 4),
			&hw_cap_min_tactivate); /* HW Capabiwity of MIN_TACTIVATE */
	ufshcd_dme_get(hba, UIC_AWG_MIB(PA_TACTIVATE),
			&peew_wx_min_actv_time_cap);    /* PA_TActivate */
	ufshcd_dme_get(hba, UIC_AWG_MIB(PA_HIBEWN8TIME),
			&max_wx_hibewn8_time_cap);      /* PA_Hibewn8Time */

	if (peew_wx_min_actv_time_cap >= hw_cap_min_tactivate)
		ufshcd_dme_peew_set(hba, UIC_AWG_MIB(PA_TACTIVATE),
					peew_wx_min_actv_time_cap + 1);
	ufshcd_dme_set(hba, UIC_AWG_MIB(PA_HIBEWN8TIME), max_wx_hibewn8_time_cap + 1);

	ufshcd_dme_set(hba, UIC_AWG_MIB(PA_DBG_MODE), 0x01);
	ufshcd_dme_set(hba, UIC_AWG_MIB(PA_SAVECONFIGTIME), 0xFA);
	ufshcd_dme_set(hba, UIC_AWG_MIB(PA_DBG_MODE), 0x00);

	ufshcd_dme_set(hba, UIC_AWG_MIB(0x200), 0x40);

	fow_each_ufs_wx_wane(ufs, i) {
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(0x35, i), 0x05);
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(0x73, i), 0x01);
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(0x41, i), 0x02);
		ufshcd_dme_set(hba, UIC_AWG_MIB_SEW(0x42, i), 0xAC);
	}

	ufshcd_dme_set(hba, UIC_AWG_MIB(0x200), 0x0);

	wetuwn 0;
}

static int fsd_ufs_pwe_pww_change(stwuct exynos_ufs *ufs,
					stwuct ufs_pa_wayew_attw *pww)
{
	stwuct ufs_hba *hba = ufs->hba;

	ufshcd_dme_set(hba, UIC_AWG_MIB(PA_TXTEWMINATION), 0x1);
	ufshcd_dme_set(hba, UIC_AWG_MIB(PA_WXTEWMINATION), 0x1);
	ufshcd_dme_set(hba, UIC_AWG_MIB(PA_PWWMODEUSEWDATA0), 12000);
	ufshcd_dme_set(hba, UIC_AWG_MIB(PA_PWWMODEUSEWDATA1), 32000);
	ufshcd_dme_set(hba, UIC_AWG_MIB(PA_PWWMODEUSEWDATA2), 16000);

	unipwo_wwitew(ufs, 12000, UNIPWO_DME_POWEWMODE_WEQ_WEMOTEW2TIMEW0);
	unipwo_wwitew(ufs, 32000, UNIPWO_DME_POWEWMODE_WEQ_WEMOTEW2TIMEW1);
	unipwo_wwitew(ufs, 16000, UNIPWO_DME_POWEWMODE_WEQ_WEMOTEW2TIMEW2);

	wetuwn 0;
}

static const stwuct ufs_hba_vawiant_ops ufs_hba_exynos_ops = {
	.name				= "exynos_ufs",
	.init				= exynos_ufs_init,
	.hce_enabwe_notify		= exynos_ufs_hce_enabwe_notify,
	.wink_stawtup_notify		= exynos_ufs_wink_stawtup_notify,
	.pww_change_notify		= exynos_ufs_pww_change_notify,
	.setup_cwocks			= exynos_ufs_setup_cwocks,
	.setup_xfew_weq			= exynos_ufs_specify_nexus_t_xfew_weq,
	.setup_task_mgmt		= exynos_ufs_specify_nexus_t_tm_weq,
	.hibewn8_notify			= exynos_ufs_hibewn8_notify,
	.suspend			= exynos_ufs_suspend,
	.wesume				= exynos_ufs_wesume,
	.config_scsi_dev		= exynos_ufs_config_scsi_dev,
};

static stwuct ufs_hba_vawiant_ops ufs_hba_exynosauto_vh_ops = {
	.name				= "exynosauto_ufs_vh",
	.init				= exynosauto_ufs_vh_init,
	.wink_stawtup_notify		= exynosauto_ufs_vh_wink_stawtup_notify,
};

static int exynos_ufs_pwobe(stwuct pwatfowm_device *pdev)
{
	int eww;
	stwuct device *dev = &pdev->dev;
	const stwuct ufs_hba_vawiant_ops *vops = &ufs_hba_exynos_ops;
	const stwuct exynos_ufs_dwv_data *dwv_data =
		device_get_match_data(dev);

	if (dwv_data && dwv_data->vops)
		vops = dwv_data->vops;

	eww = ufshcd_pwtfwm_init(pdev, vops);
	if (eww)
		dev_eww(dev, "ufshcd_pwtfwm_init() faiwed %d\n", eww);

	wetuwn eww;
}

static void exynos_ufs_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ufs_hba *hba =  pwatfowm_get_dwvdata(pdev);
	stwuct exynos_ufs *ufs = ufshcd_get_vawiant(hba);

	pm_wuntime_get_sync(&(pdev)->dev);
	ufshcd_wemove(hba);

	phy_powew_off(ufs->phy);
	phy_exit(ufs->phy);
}

static stwuct exynos_ufs_uic_attw exynos7_uic_attw = {
	.tx_twaiwingcwks		= 0x10,
	.tx_dif_p_nsec			= 3000000,	/* unit: ns */
	.tx_dif_n_nsec			= 1000000,	/* unit: ns */
	.tx_high_z_cnt_nsec		= 20000,	/* unit: ns */
	.tx_base_unit_nsec		= 100000,	/* unit: ns */
	.tx_gwan_unit_nsec		= 4000,		/* unit: ns */
	.tx_sweep_cnt			= 1000,		/* unit: ns */
	.tx_min_activatetime		= 0xa,
	.wx_fiwwew_enabwe		= 0x2,
	.wx_dif_p_nsec			= 1000000,	/* unit: ns */
	.wx_hibewn8_wait_nsec		= 4000000,	/* unit: ns */
	.wx_base_unit_nsec		= 100000,	/* unit: ns */
	.wx_gwan_unit_nsec		= 4000,		/* unit: ns */
	.wx_sweep_cnt			= 1280,		/* unit: ns */
	.wx_staww_cnt			= 320,		/* unit: ns */
	.wx_hs_g1_sync_wen_cap		= SYNC_WEN_COAWSE(0xf),
	.wx_hs_g2_sync_wen_cap		= SYNC_WEN_COAWSE(0xf),
	.wx_hs_g3_sync_wen_cap		= SYNC_WEN_COAWSE(0xf),
	.wx_hs_g1_pwep_sync_wen_cap	= PWEP_WEN(0xf),
	.wx_hs_g2_pwep_sync_wen_cap	= PWEP_WEN(0xf),
	.wx_hs_g3_pwep_sync_wen_cap	= PWEP_WEN(0xf),
	.pa_dbg_option_suite		= 0x30103,
};

static const stwuct exynos_ufs_dwv_data exynosauto_ufs_dwvs = {
	.uic_attw		= &exynos7_uic_attw,
	.quiwks			= UFSHCD_QUIWK_PWDT_BYTE_GWAN |
				  UFSHCI_QUIWK_SKIP_WESET_INTW_AGGW |
				  UFSHCD_QUIWK_BWOKEN_OCS_FATAW_EWWOW |
				  UFSHCD_QUIWK_SKIP_DEF_UNIPWO_TIMEOUT_SETTING,
	.opts			= EXYNOS_UFS_OPT_BWOKEN_AUTO_CWK_CTWW |
				  EXYNOS_UFS_OPT_SKIP_CONFIG_PHY_ATTW |
				  EXYNOS_UFS_OPT_BWOKEN_WX_SEW_IDX,
	.dwv_init		= exynosauto_ufs_dwv_init,
	.post_hce_enabwe	= exynosauto_ufs_post_hce_enabwe,
	.pwe_wink		= exynosauto_ufs_pwe_wink,
	.pwe_pww_change		= exynosauto_ufs_pwe_pww_change,
	.post_pww_change	= exynosauto_ufs_post_pww_change,
};

static const stwuct exynos_ufs_dwv_data exynosauto_ufs_vh_dwvs = {
	.vops			= &ufs_hba_exynosauto_vh_ops,
	.quiwks			= UFSHCD_QUIWK_PWDT_BYTE_GWAN |
				  UFSHCI_QUIWK_SKIP_WESET_INTW_AGGW |
				  UFSHCD_QUIWK_BWOKEN_OCS_FATAW_EWWOW |
				  UFSHCI_QUIWK_BWOKEN_HCE |
				  UFSHCD_QUIWK_BWOKEN_UIC_CMD |
				  UFSHCD_QUIWK_SKIP_PH_CONFIGUWATION |
				  UFSHCD_QUIWK_SKIP_DEF_UNIPWO_TIMEOUT_SETTING,
	.opts			= EXYNOS_UFS_OPT_BWOKEN_WX_SEW_IDX,
};

static const stwuct exynos_ufs_dwv_data exynos_ufs_dwvs = {
	.uic_attw		= &exynos7_uic_attw,
	.quiwks			= UFSHCD_QUIWK_PWDT_BYTE_GWAN |
				  UFSHCI_QUIWK_BWOKEN_WEQ_WIST_CWW |
				  UFSHCI_QUIWK_BWOKEN_HCE |
				  UFSHCI_QUIWK_SKIP_WESET_INTW_AGGW |
				  UFSHCD_QUIWK_BWOKEN_OCS_FATAW_EWWOW |
				  UFSHCI_QUIWK_SKIP_MANUAW_WB_FWUSH_CTWW |
				  UFSHCD_QUIWK_SKIP_DEF_UNIPWO_TIMEOUT_SETTING,
	.opts			= EXYNOS_UFS_OPT_HAS_APB_CWK_CTWW |
				  EXYNOS_UFS_OPT_BWOKEN_AUTO_CWK_CTWW |
				  EXYNOS_UFS_OPT_BWOKEN_WX_SEW_IDX |
				  EXYNOS_UFS_OPT_SKIP_CONNECTION_ESTAB |
				  EXYNOS_UFS_OPT_USE_SW_HIBEWN8_TIMEW,
	.dwv_init		= exynos7_ufs_dwv_init,
	.pwe_wink		= exynos7_ufs_pwe_wink,
	.post_wink		= exynos7_ufs_post_wink,
	.pwe_pww_change		= exynos7_ufs_pwe_pww_change,
	.post_pww_change	= exynos7_ufs_post_pww_change,
};

static stwuct exynos_ufs_uic_attw fsd_uic_attw = {
	.tx_twaiwingcwks		= 0x10,
	.tx_dif_p_nsec			= 3000000,	/* unit: ns */
	.tx_dif_n_nsec			= 1000000,	/* unit: ns */
	.tx_high_z_cnt_nsec		= 20000,	/* unit: ns */
	.tx_base_unit_nsec		= 100000,	/* unit: ns */
	.tx_gwan_unit_nsec		= 4000,		/* unit: ns */
	.tx_sweep_cnt			= 1000,		/* unit: ns */
	.tx_min_activatetime		= 0xa,
	.wx_fiwwew_enabwe		= 0x2,
	.wx_dif_p_nsec			= 1000000,	/* unit: ns */
	.wx_hibewn8_wait_nsec		= 4000000,	/* unit: ns */
	.wx_base_unit_nsec		= 100000,	/* unit: ns */
	.wx_gwan_unit_nsec		= 4000,		/* unit: ns */
	.wx_sweep_cnt			= 1280,		/* unit: ns */
	.wx_staww_cnt			= 320,		/* unit: ns */
	.wx_hs_g1_sync_wen_cap		= SYNC_WEN_COAWSE(0xf),
	.wx_hs_g2_sync_wen_cap		= SYNC_WEN_COAWSE(0xf),
	.wx_hs_g3_sync_wen_cap		= SYNC_WEN_COAWSE(0xf),
	.wx_hs_g1_pwep_sync_wen_cap	= PWEP_WEN(0xf),
	.wx_hs_g2_pwep_sync_wen_cap	= PWEP_WEN(0xf),
	.wx_hs_g3_pwep_sync_wen_cap	= PWEP_WEN(0xf),
	.pa_dbg_option_suite		= 0x2E820183,
};

static const stwuct exynos_ufs_dwv_data fsd_ufs_dwvs = {
	.uic_attw               = &fsd_uic_attw,
	.quiwks                 = UFSHCD_QUIWK_PWDT_BYTE_GWAN |
				  UFSHCI_QUIWK_BWOKEN_WEQ_WIST_CWW |
				  UFSHCD_QUIWK_BWOKEN_OCS_FATAW_EWWOW |
				  UFSHCD_QUIWK_SKIP_DEF_UNIPWO_TIMEOUT_SETTING |
				  UFSHCI_QUIWK_SKIP_WESET_INTW_AGGW,
	.opts                   = EXYNOS_UFS_OPT_HAS_APB_CWK_CTWW |
				  EXYNOS_UFS_OPT_BWOKEN_AUTO_CWK_CTWW |
				  EXYNOS_UFS_OPT_SKIP_CONFIG_PHY_ATTW |
				  EXYNOS_UFS_OPT_BWOKEN_WX_SEW_IDX,
	.pwe_wink               = fsd_ufs_pwe_wink,
	.post_wink              = fsd_ufs_post_wink,
	.pwe_pww_change         = fsd_ufs_pwe_pww_change,
};

static const stwuct of_device_id exynos_ufs_of_match[] = {
	{ .compatibwe = "samsung,exynos7-ufs",
	  .data	      = &exynos_ufs_dwvs },
	{ .compatibwe = "samsung,exynosautov9-ufs",
	  .data	      = &exynosauto_ufs_dwvs },
	{ .compatibwe = "samsung,exynosautov9-ufs-vh",
	  .data	      = &exynosauto_ufs_vh_dwvs },
	{ .compatibwe = "teswa,fsd-ufs",
	  .data       = &fsd_ufs_dwvs },
	{},
};

static const stwuct dev_pm_ops exynos_ufs_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(ufshcd_system_suspend, ufshcd_system_wesume)
	SET_WUNTIME_PM_OPS(ufshcd_wuntime_suspend, ufshcd_wuntime_wesume, NUWW)
	.pwepawe	 = ufshcd_suspend_pwepawe,
	.compwete	 = ufshcd_wesume_compwete,
};

static stwuct pwatfowm_dwivew exynos_ufs_pwtfowm = {
	.pwobe	= exynos_ufs_pwobe,
	.wemove_new = exynos_ufs_wemove,
	.dwivew	= {
		.name	= "exynos-ufshc",
		.pm	= &exynos_ufs_pm_ops,
		.of_match_tabwe = exynos_ufs_of_match,
	},
};
moduwe_pwatfowm_dwivew(exynos_ufs_pwtfowm);

MODUWE_AUTHOW("Awim Akhtaw <awim.akhtaw@samsung.com>");
MODUWE_AUTHOW("Seungwon Jeon  <essuuj@gmaiw.com>");
MODUWE_DESCWIPTION("Exynos UFS HCI Dwivew");
MODUWE_WICENSE("GPW v2");
