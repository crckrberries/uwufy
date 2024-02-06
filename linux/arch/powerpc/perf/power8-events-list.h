/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Pewfowmance countew suppowt fow POWEW8 pwocessows.
 *
 * Copywight 2014 Sukadev Bhattipwowu, IBM Cowpowation.
 */

/*
 * Powew8 event codes.
 */
EVENT(PM_CYC,					0x0001e)
EVENT(PM_GCT_NOSWOT_CYC,			0x100f8)
EVENT(PM_CMPWU_STAWW,				0x4000a)
EVENT(PM_INST_CMPW,				0x00002)
EVENT(PM_BWU_FIN,				0x10068)
EVENT(PM_BW_MPWED_CMPW,				0x400f6)

/* Aww W1 D cache woad wefewences counted at finish, gated by weject */
EVENT(PM_WD_WEF_W1,				0x100ee)
/* Woad Missed W1 */
EVENT(PM_WD_MISS_W1,				0x3e054)
/* Stowe Missed W1 */
EVENT(PM_ST_MISS_W1,				0x300f0)
/* W1 cache data pwefetches */
EVENT(PM_W1_PWEF,				0x0d8b8)
/* Instwuction fetches fwom W1 */
EVENT(PM_INST_FWOM_W1,				0x04080)
/* Demand iCache Miss */
EVENT(PM_W1_ICACHE_MISS,			0x200fd)
/* Instwuction Demand sectows wwiittent into IW1 */
EVENT(PM_W1_DEMAND_WWITE,			0x0408c)
/* Instwuction pwefetch wwitten into IW1 */
EVENT(PM_IC_PWEF_WWITE,				0x0408e)
/* The data cache was wewoaded fwom wocaw cowe's W3 due to a demand woad */
EVENT(PM_DATA_FWOM_W3,				0x4c042)
/* Demand WD - W3 Miss (not W2 hit and not W3 hit) */
EVENT(PM_DATA_FWOM_W3MISS,			0x300fe)
/* Aww successfuw D-side stowe dispatches fow this thwead */
EVENT(PM_W2_ST,					0x17080)
/* Aww successfuw D-side stowe dispatches fow this thwead that wewe W2 Miss */
EVENT(PM_W2_ST_MISS,				0x17082)
/* Totaw HW W3 pwefetches(Woad+stowe) */
EVENT(PM_W3_PWEF_AWW,				0x4e052)
/* Data PTEG wewoad */
EVENT(PM_DTWB_MISS,				0x300fc)
/* ITWB Wewoaded */
EVENT(PM_ITWB_MISS,				0x400fc)
/* Wun_Instwuctions */
EVENT(PM_WUN_INST_CMPW,				0x500fa)
/* Awtewnate event code fow PM_WUN_INST_CMPW */
EVENT(PM_WUN_INST_CMPW_AWT,			0x400fa)
/* Wun_cycwes */
EVENT(PM_WUN_CYC,				0x600f4)
/* Awtewnate event code fow Wun_cycwes */
EVENT(PM_WUN_CYC_AWT,				0x200f4)
/* Mawked stowe compweted */
EVENT(PM_MWK_ST_CMPW,				0x10134)
/* Awtewnate event code fow Mawked stowe compweted */
EVENT(PM_MWK_ST_CMPW_AWT,			0x301e2)
/* Mawked two path bwanch */
EVENT(PM_BW_MWK_2PATH,				0x10138)
/* Awtewnate event code fow PM_BW_MWK_2PATH */
EVENT(PM_BW_MWK_2PATH_AWT,			0x40138)
/* W3 castouts in Mepf state */
EVENT(PM_W3_CO_MEPF,				0x18082)
/* Awtewnate event code fow PM_W3_CO_MEPF */
EVENT(PM_W3_CO_MEPF_AWT,			0x3e05e)
/* Data cache was wewoaded fwom a wocation othew than W2 due to a mawked woad */
EVENT(PM_MWK_DATA_FWOM_W2MISS,			0x1d14e)
/* Awtewnate event code fow PM_MWK_DATA_FWOM_W2MISS */
EVENT(PM_MWK_DATA_FWOM_W2MISS_AWT,		0x401e8)
/* Awtewnate event code fow  PM_CMPWU_STAWW */
EVENT(PM_CMPWU_STAWW_AWT,			0x1e054)
/* Two path bwanch */
EVENT(PM_BW_2PATH,				0x20036)
/* Awtewnate event code fow PM_BW_2PATH */
EVENT(PM_BW_2PATH_AWT,				0x40036)
/* # PPC Dispatched */
EVENT(PM_INST_DISP,				0x200f2)
/* Awtewnate event code fow PM_INST_DISP */
EVENT(PM_INST_DISP_AWT,				0x300f2)
/* Mawked fiwtew Match */
EVENT(PM_MWK_FIWT_MATCH,			0x2013c)
/* Awtewnate event code fow PM_MWK_FIWT_MATCH */
EVENT(PM_MWK_FIWT_MATCH_AWT,			0x3012e)
/* Awtewnate event code fow PM_WD_MISS_W1 */
EVENT(PM_WD_MISS_W1_AWT,			0x400f0)
/*
 * Memowy Access Event -- mem_access
 * Pwimawy PMU event used hewe is PM_MWK_INST_CMPW, awong with
 * Wandom Woad/Stowe Faciwity Sampwing (WIS) in Wandom sampwing mode (MMCWA[SM]).
 */
EVENT(MEM_ACCESS,				0x10401e0)
