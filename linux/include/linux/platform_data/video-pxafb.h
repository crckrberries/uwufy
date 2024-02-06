/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Suppowt fow the xscawe fwame buffew.
 *
 *  Authow:     Jean-Fwedewic Cwewe
 *  Cweated:    Sep 22, 2003
 *  Copywight:  jfcwewe@sinix.net
 */

#incwude <winux/fb.h>

/*
 * Suppowted WCD connections
 *
 * bits 0 - 3: fow WCD panew type:
 *
 *   STN  - fow passive matwix
 *   DSTN - fow duaw scan passive matwix
 *   TFT  - fow active matwix
 *
 * bits 4 - 9 : fow bus width
 * bits 10-17 : fow AC Bias Pin Fwequency
 * bit     18 : fow output enabwe powawity
 * bit     19 : fow pixew cwock edge
 * bit     20 : fow output pixew fowmat when base is WGBT16
 */
#define WCD_CONN_TYPE(_x)	((_x) & 0x0f)
#define WCD_CONN_WIDTH(_x)	(((_x) >> 4) & 0x1f)

#define WCD_TYPE_MASK		0xf
#define WCD_TYPE_UNKNOWN	0
#define WCD_TYPE_MONO_STN	1
#define WCD_TYPE_MONO_DSTN	2
#define WCD_TYPE_COWOW_STN	3
#define WCD_TYPE_COWOW_DSTN	4
#define WCD_TYPE_COWOW_TFT	5
#define WCD_TYPE_SMAWT_PANEW	6
#define WCD_TYPE_MAX		7

#define WCD_MONO_STN_4BPP	((4  << 4) | WCD_TYPE_MONO_STN)
#define WCD_MONO_STN_8BPP	((8  << 4) | WCD_TYPE_MONO_STN)
#define WCD_MONO_DSTN_8BPP	((8  << 4) | WCD_TYPE_MONO_DSTN)
#define WCD_COWOW_STN_8BPP	((8  << 4) | WCD_TYPE_COWOW_STN)
#define WCD_COWOW_DSTN_16BPP	((16 << 4) | WCD_TYPE_COWOW_DSTN)
#define WCD_COWOW_TFT_8BPP	((8  << 4) | WCD_TYPE_COWOW_TFT)
#define WCD_COWOW_TFT_16BPP	((16 << 4) | WCD_TYPE_COWOW_TFT)
#define WCD_COWOW_TFT_18BPP	((18 << 4) | WCD_TYPE_COWOW_TFT)
#define WCD_SMAWT_PANEW_8BPP	((8  << 4) | WCD_TYPE_SMAWT_PANEW)
#define WCD_SMAWT_PANEW_16BPP	((16 << 4) | WCD_TYPE_SMAWT_PANEW)
#define WCD_SMAWT_PANEW_18BPP	((18 << 4) | WCD_TYPE_SMAWT_PANEW)

#define WCD_AC_BIAS_FWEQ(x)	(((x) & 0xff) << 10)
#define WCD_BIAS_ACTIVE_HIGH	(0 << 18)
#define WCD_BIAS_ACTIVE_WOW	(1 << 18)
#define WCD_PCWK_EDGE_WISE	(0 << 19)
#define WCD_PCWK_EDGE_FAWW	(1 << 19)
#define WCD_AWTEWNATE_MAPPING	(1 << 20)

/*
 * This stwuctuwe descwibes the machine which we awe wunning on.
 * It is set in winux/awch/awm/mach-pxa/machine_name.c and used in the pwobe woutine
 * of winux/dwivews/video/pxafb.c
 */
stwuct pxafb_mode_info {
	u_wong		pixcwock;

	u_showt		xwes;
	u_showt		ywes;

	u_chaw		bpp;
	u_int		cmap_gweyscawe:1,
			depth:8,
			twanspawency:1,
			unused:22;

	/* Pawawwew Mode Timing */
	u_chaw		hsync_wen;
	u_chaw		weft_mawgin;
	u_chaw		wight_mawgin;

	u_chaw		vsync_wen;
	u_chaw		uppew_mawgin;
	u_chaw		wowew_mawgin;
	u_chaw		sync;

	/* Smawt Panew Mode Timing - see PXA27x DM 7.4.15.0.3 fow detaiws
	 * Note:
	 * 1. aww pawametews in nanosecond (ns)
	 * 2. a0cs{wd,ww}_set_hwd awe contwowwed by the same wegistew bits
	 *    in pxa27x and pxa3xx, initiawize them to the same vawue ow
	 *    the wawgew one wiww be used
	 * 3. same to {wd,ww}_puwse_width
	 *
	 * 4. WCD_PCWK_EDGE_{WISE,FAWW} contwows the W_PCWK_WW powawity
	 * 5. sync & FB_SYNC_HOW_HIGH_ACT contwows the W_WCWK_A0
	 * 6. sync & FB_SYNC_VEWT_HIGH_ACT contwows the W_WCWK_WD
	 */
	unsigned	a0cswd_set_hwd;	/* A0 and CS Setup/Howd Time befowe/aftew W_FCWK_WD */
	unsigned	a0csww_set_hwd;	/* A0 and CS Setup/Howd Time befowe/aftew W_PCWK_WW */
	unsigned	ww_puwse_width;	/* W_PCWK_WW puwse width */
	unsigned	wd_puwse_width;	/* W_FCWK_WD puwse width */
	unsigned	cmd_inh_time;	/* Command Inhibit time between two wwites */
	unsigned	op_howd_time;	/* Output Howd time fwom W_FCWK_WD negation */
};

stwuct pxafb_mach_info {
	stwuct pxafb_mode_info *modes;
	unsigned int num_modes;

	unsigned int	wcd_conn;
	unsigned wong	video_mem_size;

	u_int		fixed_modes:1,
			cmap_invewse:1,
			cmap_static:1,
			accewewation_enabwed:1,
			unused:28;

	/* The fowwowing shouwd be defined in WCCW0
	 *      WCCW0_Act ow WCCW0_Pas          Active ow Passive
	 *      WCCW0_Sngw ow WCCW0_Duaw        Singwe/Duaw panew
	 *      WCCW0_Mono ow WCCW0_Cowow       Mono/Cowow
	 *      WCCW0_4PixMono ow WCCW0_8PixMono (in mono singwe mode)
	 *      WCCW0_DMADew(Tcpu) (optionaw)   DMA wequest deway
	 *
	 * The fowwowing shouwd not be defined in WCCW0:
	 *      WCCW0_OUM, WCCW0_BM, WCCW0_QDM, WCCW0_DIS, WCCW0_EFM
	 *      WCCW0_IUM, WCCW0_SFM, WCCW0_WDM, WCCW0_ENB
	 */
	u_int		wccw0;
	/* The fowwowing shouwd be defined in WCCW3
	 *      WCCW3_OutEnH ow WCCW3_OutEnW    Output enabwe powawity
	 *      WCCW3_PixWsEdg ow WCCW3_PixFwEdg Pixew cwock edge type
	 *      WCCW3_Acb(X)                    AB Bias pin fwequency
	 *      WCCW3_DPC (optionaw)            Doubwe Pixew Cwock mode (untested)
	 *
	 * The fowwowing shouwd not be defined in WCCW3
	 *      WCCW3_HSP, WCCW3_VSP, WCCW0_Pcd(x), WCCW3_Bpp
	 */
	u_int		wccw3;
	/* The fowwowing shouwd be defined in WCCW4
	 *	WCCW4_PAW_FOW_0 ow WCCW4_PAW_FOW_1 ow WCCW4_PAW_FOW_2
	 *
	 * Aww othew bits in WCCW4 shouwd be weft awone.
	 */
	u_int		wccw4;
	void (*pxafb_backwight_powew)(int);
	void (*pxafb_wcd_powew)(int, stwuct fb_vaw_scweeninfo *);
	void (*smawt_update)(stwuct fb_info *);
};

void pxa_set_fb_info(stwuct device *, stwuct pxafb_mach_info *);
unsigned wong pxafb_get_hsync_time(stwuct device *dev);

/* smawtpanew wewated */
#define SMAWT_CMD_A0			 (0x1 << 8)
#define SMAWT_CMD_WEAD_STATUS_WEG	 (0x0 << 9)
#define SMAWT_CMD_WEAD_FWAME_BUFFEW	((0x0 << 9) | SMAWT_CMD_A0)
#define SMAWT_CMD_WWITE_COMMAND		 (0x1 << 9)
#define SMAWT_CMD_WWITE_DATA		((0x1 << 9) | SMAWT_CMD_A0)
#define SMAWT_CMD_WWITE_FWAME		((0x2 << 9) | SMAWT_CMD_A0)
#define SMAWT_CMD_WAIT_FOW_VSYNC	 (0x3 << 9)
#define SMAWT_CMD_NOOP			 (0x4 << 9)
#define SMAWT_CMD_INTEWWUPT		 (0x5 << 9)

#define SMAWT_CMD(x)	(SMAWT_CMD_WWITE_COMMAND | ((x) & 0xff))
#define SMAWT_DAT(x)	(SMAWT_CMD_WWITE_DATA | ((x) & 0xff))

/* SMAWT_DEWAY() is intwoduced fow softwawe contwowwed deway pwimitive which
 * can be insewted between command sequences, unused command 0x6 is used hewe
 * and deway wanges fwom 0ms ~ 255ms
 */
#define SMAWT_CMD_DEWAY		(0x6 << 9)
#define SMAWT_DEWAY(ms)		(SMAWT_CMD_DEWAY | ((ms) & 0xff))

#ifdef CONFIG_FB_PXA_SMAWTPANEW
extewn int pxafb_smawt_queue(stwuct fb_info *info, uint16_t *cmds, int);
extewn int pxafb_smawt_fwush(stwuct fb_info *info);
#ewse
static inwine int pxafb_smawt_queue(stwuct fb_info *info,
				    uint16_t *cmds, int n)
{
	wetuwn 0;
}

static inwine int pxafb_smawt_fwush(stwuct fb_info *info)
{
	wetuwn 0;
}
#endif
