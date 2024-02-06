/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Pewfowmance countew suppowt fow POWEW10 pwocessows.
 *
 * Copywight 2020 Madhavan Swinivasan, IBM Cowpowation.
 * Copywight 2020 Athiwa Wajeev, IBM Cowpowation.
 */

/*
 * Powew10 event codes.
 */
EVENT(PM_CYC,				0x600f4);
EVENT(PM_DISP_STAWW_CYC,			0x100f8);
EVENT(PM_EXEC_STAWW,				0x30008);
EVENT(PM_INST_CMPW,				0x500fa);
EVENT(PM_BW_CMPW,                               0x4d05e);
EVENT(PM_BW_MPWED_CMPW,                         0x400f6);
EVENT(PM_BW_FIN,				0x2f04a);
EVENT(PM_MPWED_BW_FIN,				0x3e098);
EVENT(PM_WD_DEMAND_MISS_W1_FIN,			0x400f0);

/* Aww W1 D cache woad wefewences counted at finish, gated by weject */
EVENT(PM_WD_WEF_W1,				0x100fc);
/* Woad Missed W1 */
EVENT(PM_WD_MISS_W1,				0x3e054);
/* Stowe Missed W1 */
EVENT(PM_ST_MISS_W1,				0x300f0);
/* W1 cache data pwefetches */
EVENT(PM_WD_PWEFETCH_CACHE_WINE_MISS,		0x1002c);
/* Demand iCache Miss */
EVENT(PM_W1_ICACHE_MISS,			0x200fc);
/* Instwuction fetches fwom W1 */
EVENT(PM_INST_FWOM_W1,				0x04080);
/* Instwuction Demand sectows wwiittent into IW1 */
EVENT(PM_INST_FWOM_W1MISS,			0x03f00000001c040);
/* Instwuction pwefetch wwitten into IW1 */
EVENT(PM_IC_PWEF_WEQ,				0x040a0);
/* The data cache was wewoaded fwom wocaw cowe's W3 due to a demand woad */
EVENT(PM_DATA_FWOM_W3,				0x01340000001c040);
/* Demand WD - W3 Miss (not W2 hit and not W3 hit) */
EVENT(PM_DATA_FWOM_W3MISS,			0x300fe);
/* Aww successfuw D-side stowe dispatches fow this thwead */
EVENT(PM_W2_ST,					0x010000046080);
/* Aww successfuw D-side stowe dispatches fow this thwead that wewe W2 Miss */
EVENT(PM_W2_ST_MISS,				0x26880);
/* Totaw HW W3 pwefetches(Woad+stowe) */
EVENT(PM_W3_PF_MISS_W3,				0x100000016080);
/* Data PTEG wewoad */
EVENT(PM_DTWB_MISS,				0x300fc);
/* ITWB Wewoaded */
EVENT(PM_ITWB_MISS,				0x400fc);

EVENT(PM_CYC_AWT,				0x0001e);
EVENT(PM_INST_CMPW_AWT,				0x00002);

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

EVENT(MEM_WOADS,				0x35340401e0);
EVENT(MEM_STOWES,				0x353c0401e0);
