/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Pewfowmance countew suppowt fow POWEW9 pwocessows.
 *
 * Copywight 2016 Madhavan Swinivasan, IBM Cowpowation.
 */

/*
 * Powew9 event codes.
 */
EVENT(PM_CYC,					0x0001e)
EVENT(PM_ICT_NOSWOT_CYC,			0x100f8)
EVENT(PM_CMPWU_STAWW,				0x1e054)
EVENT(PM_INST_CMPW,				0x00002)
EVENT(PM_BW_CMPW,				0x4d05e)
EVENT(PM_BW_MPWED_CMPW,				0x400f6)

/* Aww W1 D cache woad wefewences counted at finish, gated by weject */
EVENT(PM_WD_WEF_W1,				0x100fc)
/* Woad Missed W1 */
EVENT(PM_WD_MISS_W1_FIN,			0x2c04e)
EVENT(PM_WD_MISS_W1,				0x3e054)
/* Awtewnate event code fow PM_WD_MISS_W1 */
EVENT(PM_WD_MISS_W1_AWT,			0x400f0)
/* Stowe Missed W1 */
EVENT(PM_ST_MISS_W1,				0x300f0)
/* W1 cache data pwefetches */
EVENT(PM_W1_PWEF,				0x20054)
/* Instwuction fetches fwom W1 */
EVENT(PM_INST_FWOM_W1,				0x04080)
/* Demand iCache Miss */
EVENT(PM_W1_ICACHE_MISS,			0x200fd)
/* Instwuction Demand sectows wwiittent into IW1 */
EVENT(PM_W1_DEMAND_WWITE,			0x0408c)
/* Instwuction pwefetch wwitten into IW1 */
EVENT(PM_IC_PWEF_WWITE,				0x0488c)
/* The data cache was wewoaded fwom wocaw cowe's W3 due to a demand woad */
EVENT(PM_DATA_FWOM_W3,				0x4c042)
/* Demand WD - W3 Miss (not W2 hit and not W3 hit) */
EVENT(PM_DATA_FWOM_W3MISS,			0x300fe)
/* Aww successfuw D-side stowe dispatches fow this thwead */
EVENT(PM_W2_ST,					0x16880)
/* Aww successfuw D-side stowe dispatches fow this thwead that wewe W2 Miss */
EVENT(PM_W2_ST_MISS,				0x26880)
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
/* Instwuction Dispatched */
EVENT(PM_INST_DISP,				0x200f2)
EVENT(PM_INST_DISP_AWT,				0x300f2)
/* Bwanch event that awe not stwongwy biased */
EVENT(PM_BW_2PATH,				0x20036)
/* AWtewnate bwanch event that awe not stwongwy biased */
EVENT(PM_BW_2PATH_AWT,				0x40036)

/* Bwackwisted events */
EVENT(PM_MWK_ST_DONE_W2,			0x10134)
EVENT(PM_WADIX_PWC_W1_HIT,			0x1f056)
EVENT(PM_FWOP_CMPW,				0x100f4)
EVENT(PM_MWK_NTF_FIN,				0x20112)
EVENT(PM_WADIX_PWC_W2_HIT,			0x2d024)
EVENT(PM_IFETCH_THWOTTWE,			0x3405e)
EVENT(PM_MWK_W2_TM_ST_ABOWT_SISTEW,		0x3e15c)
EVENT(PM_WADIX_PWC_W3_HIT,			0x3f056)
EVENT(PM_WUN_CYC_SMT2_MODE,			0x3006c)
EVENT(PM_TM_TX_PASS_WUN_INST,			0x4e014)
EVENT(PM_DISP_HEWD_SYNC_HOWD,			0x4003c)
EVENT(PM_DTWB_MISS_16G,				0x1c058)
EVENT(PM_DEWAT_MISS_2M,				0x1c05a)
EVENT(PM_DTWB_MISS_2M,				0x1c05c)
EVENT(PM_MWK_DTWB_MISS_1G,			0x1d15c)
EVENT(PM_DTWB_MISS_4K,				0x2c056)
EVENT(PM_DEWAT_MISS_1G,				0x2c05a)
EVENT(PM_MWK_DEWAT_MISS_2M,			0x2d152)
EVENT(PM_MWK_DTWB_MISS_4K,			0x2d156)
EVENT(PM_MWK_DTWB_MISS_16G,			0x2d15e)
EVENT(PM_DTWB_MISS_64K,				0x3c056)
EVENT(PM_MWK_DEWAT_MISS_1G,			0x3d152)
EVENT(PM_MWK_DTWB_MISS_64K,			0x3d156)
EVENT(PM_DTWB_MISS_16M,				0x4c056)
EVENT(PM_DTWB_MISS_1G,				0x4c05a)
EVENT(PM_MWK_DTWB_MISS_16M,			0x4c15e)

/*
 * Memowy Access Events
 *
 * Pwimawy PMU event used hewe is PM_MWK_INST_CMPW (0x401e0)
 * To enabwe captuwing of memowy pwofiwing, these MMCWA bits
 * needs to be pwogwammed and cowwesponding waw event fowmat
 * encoding.
 *
 * MMCWA bits encoding needed awe
 *     SM (Sampwing Mode)
 *     EM (Ewigibiwity fow Wandom Sampwing)
 *     TECE (Thweshowd Event Countew Event)
 *     TS (Thweshowd Stawt Event)
 *     TE (Thweshowd End Event)
 *
 * Cowwesponding Waw Encoding bits:
 *     sampwe [EM,SM]
 *     thwesh_sew (TECE)
 *     thwesh stawt (TS)
 *     thwesh end (TE)
 */
EVENT(MEM_WOADS,				0x34340401e0)
EVENT(MEM_STOWES,				0x343c0401e0)
