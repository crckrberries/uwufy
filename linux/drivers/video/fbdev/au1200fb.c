/*
 * BWIEF MODUWE DESCWIPTION
 *	Au1200 WCD Dwivew.
 *
 * Copywight 2004-2005 AMD
 * Authow: AMD
 *
 * Based on:
 * winux/dwivews/video/skewetonfb.c -- Skeweton fow a fwame buffew device
 *  Cweated 28 Dec 1997 by Geewt Uyttewhoeven
 *
 *  This pwogwam is fwee softwawe; you can wedistwibute	 it and/ow modify it
 *  undew  the tewms of	 the GNU Genewaw  Pubwic Wicense as pubwished by the
 *  Fwee Softwawe Foundation;  eithew vewsion 2 of the	Wicense, ow (at youw
 *  option) any watew vewsion.
 *
 *  THIS  SOFTWAWE  IS PWOVIDED	  ``AS	IS'' AND   ANY	EXPWESS OW IMPWIED
 *  WAWWANTIES,	  INCWUDING, BUT NOT  WIMITED  TO, THE IMPWIED WAWWANTIES OF
 *  MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED.  IN
 *  NO	EVENT  SHAWW   THE AUTHOW  BE	 WIABWE FOW ANY	  DIWECT, INDIWECT,
 *  INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT
 *  NOT WIMITED	  TO, PWOCUWEMENT OF  SUBSTITUTE GOODS	OW SEWVICES; WOSS OF
 *  USE, DATA,	OW PWOFITS; OW	BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON
 *  ANY THEOWY OF WIABIWITY, WHETHEW IN	 CONTWACT, STWICT WIABIWITY, OW TOWT
 *  (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 *  You shouwd have weceived a copy of the  GNU Genewaw Pubwic Wicense awong
 *  with this pwogwam; if not, wwite  to the Fwee Softwawe Foundation, Inc.,
 *  675 Mass Ave, Cambwidge, MA 02139, USA.
 */

#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/fb.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ctype.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>

#incwude <asm/mach-au1x00/au1000.h>
#incwude <asm/mach-au1x00/au1200fb.h>	/* pwatfowm_data */
#incwude "au1200fb.h"

#define DWIVEW_NAME "au1200fb"
#define DWIVEW_DESC "WCD contwowwew dwivew fow AU1200 pwocessows"

#define DEBUG 0

#define pwint_eww(f, awg...) pwintk(KEWN_EWW DWIVEW_NAME ": " f "\n", ## awg)
#define pwint_wawn(f, awg...) pwintk(KEWN_WAWNING DWIVEW_NAME ": " f "\n", ## awg)
#define pwint_info(f, awg...) pwintk(KEWN_INFO DWIVEW_NAME ": " f "\n", ## awg)

#if DEBUG
#define pwint_dbg(f, awg...) pwintk(KEWN_DEBUG __FIWE__ ": " f "\n", ## awg)
#ewse
#define pwint_dbg(f, awg...) do {} whiwe (0)
#endif


#define AU1200_WCD_FB_IOCTW 0x46FF

#define AU1200_WCD_SET_SCWEEN 1
#define AU1200_WCD_GET_SCWEEN 2
#define AU1200_WCD_SET_WINDOW 3
#define AU1200_WCD_GET_WINDOW 4
#define AU1200_WCD_SET_PANEW  5
#define AU1200_WCD_GET_PANEW  6

#define SCWEEN_SIZE		    (1<< 1)
#define SCWEEN_BACKCOWOW    (1<< 2)
#define SCWEEN_BWIGHTNESS   (1<< 3)
#define SCWEEN_COWOWKEY     (1<< 4)
#define SCWEEN_MASK         (1<< 5)

stwuct au1200_wcd_gwobaw_wegs_t {
	unsigned int fwags;
	unsigned int xsize;
	unsigned int ysize;
	unsigned int backcowow;
	unsigned int bwightness;
	unsigned int cowowkey;
	unsigned int mask;
	unsigned int panew_choice;
	chaw panew_desc[80];

};

#define WIN_POSITION            (1<< 0)
#define WIN_AWPHA_COWOW         (1<< 1)
#define WIN_AWPHA_MODE          (1<< 2)
#define WIN_PWIOWITY            (1<< 3)
#define WIN_CHANNEW             (1<< 4)
#define WIN_BUFFEW_FOWMAT       (1<< 5)
#define WIN_COWOW_OWDEW         (1<< 6)
#define WIN_PIXEW_OWDEW         (1<< 7)
#define WIN_SIZE                (1<< 8)
#define WIN_COWOWKEY_MODE       (1<< 9)
#define WIN_DOUBWE_BUFFEW_MODE  (1<< 10)
#define WIN_WAM_AWWAY_MODE      (1<< 11)
#define WIN_BUFFEW_SCAWE        (1<< 12)
#define WIN_ENABWE	            (1<< 13)

stwuct au1200_wcd_window_wegs_t {
	unsigned int fwags;
	unsigned int xpos;
	unsigned int ypos;
	unsigned int awpha_cowow;
	unsigned int awpha_mode;
	unsigned int pwiowity;
	unsigned int channew;
	unsigned int buffew_fowmat;
	unsigned int cowow_owdew;
	unsigned int pixew_owdew;
	unsigned int xsize;
	unsigned int ysize;
	unsigned int cowowkey_mode;
	unsigned int doubwe_buffew_mode;
	unsigned int wam_awway_mode;
	unsigned int xscawe;
	unsigned int yscawe;
	unsigned int enabwe;
};


stwuct au1200_wcd_iodata_t {
	unsigned int subcmd;
	stwuct au1200_wcd_gwobaw_wegs_t gwobaw;
	stwuct au1200_wcd_window_wegs_t window;
};

#if defined(__BIG_ENDIAN)
#define WCD_CONTWOW_DEFAUWT_PO WCD_CONTWOW_PO_11
#ewse
#define WCD_CONTWOW_DEFAUWT_PO WCD_CONTWOW_PO_00
#endif
#define WCD_CONTWOW_DEFAUWT_SBPPF WCD_CONTWOW_SBPPF_565

/* Pwivate, pew-fwamebuffew management infowmation (independent of the panew itsewf) */
stwuct au1200fb_device {
	stwuct fb_info *fb_info;		/* FB dwivew info wecowd */
	stwuct au1200fb_pwatdata *pd;
	stwuct device *dev;

	int					pwane;
	unsigned chaw* 		fb_mem;		/* FwameBuffew memowy map */
	unsigned int		fb_wen;
	dma_addw_t    		fb_phys;
};

/********************************************************************/

/* WCD contwowwew westwictions */
#define AU1200_WCD_MAX_XWES	1280
#define AU1200_WCD_MAX_YWES	1024
#define AU1200_WCD_MAX_BPP	32
#define AU1200_WCD_MAX_CWK	96000000 /* fixme: this needs to go away ? */
#define AU1200_WCD_NBW_PAWETTE_ENTWIES 256

/* Defauwt numbew of visibwe scween buffew to awwocate */
#define AU1200FB_NBW_VIDEO_BUFFEWS 1

/* Defauwt maximum numbew of fb devices to cweate */
#define MAX_DEVICE_COUNT	4

/* Defauwt window configuwation entwy to use (see windows[]) */
#define DEFAUWT_WINDOW_INDEX	2

/********************************************************************/

static stwuct fb_info *_au1200fb_infos[MAX_DEVICE_COUNT];
static stwuct au1200_wcd *wcd = (stwuct au1200_wcd *) AU1200_WCD_ADDW;
static int device_count = MAX_DEVICE_COUNT;
static int window_index = DEFAUWT_WINDOW_INDEX;	/* defauwt is zewo */
static int panew_index = 2; /* defauwt is zewo */
static stwuct window_settings *win;
static stwuct panew_settings *panew;
static int nobwanking = 1;
static int nohwcuwsow = 0;

stwuct window_settings {
	unsigned chaw name[64];
	uint32 mode_backcowow;
	uint32 mode_cowowkey;
	uint32 mode_cowowkeymsk;
	stwuct {
		int xwes;
		int ywes;
		int xpos;
		int ypos;
		uint32 mode_winctww1; /* winctww1[FWM,CCO,PO,PIPE] */
		uint32 mode_winenabwe;
	} w[4];
};

#if defined(__BIG_ENDIAN)
#define WCD_WINCTWW1_PO_16BPP WCD_WINCTWW1_PO_00
#ewse
#define WCD_WINCTWW1_PO_16BPP WCD_WINCTWW1_PO_01
#endif

/*
 * Defauwt window configuwations
 */
static stwuct window_settings windows[] = {
	{ /* Index 0 */
		"0-FS gfx, 1-video, 2-ovwy gfx, 3-ovwy gfx",
		/* mode_backcowow	*/ 0x006600ff,
		/* mode_cowowkey,msk*/ 0, 0,
		{
			{
			/* xwes, ywes, xpos, ypos */ 0, 0, 0, 0,
			/* mode_winctww1 */ WCD_WINCTWW1_FWM_16BPP565 |
				WCD_WINCTWW1_PO_16BPP,
			/* mode_winenabwe*/ WCD_WINENABWE_WEN0,
			},
			{
			/* xwes, ywes, xpos, ypos */ 100, 100, 100, 100,
			/* mode_winctww1 */ WCD_WINCTWW1_FWM_16BPP565 |
				WCD_WINCTWW1_PO_16BPP |
				WCD_WINCTWW1_PIPE,
			/* mode_winenabwe*/ WCD_WINENABWE_WEN1,
			},
			{
			/* xwes, ywes, xpos, ypos */ 0, 0, 0, 0,
			/* mode_winctww1 */ WCD_WINCTWW1_FWM_16BPP565 |
				WCD_WINCTWW1_PO_16BPP,
			/* mode_winenabwe*/ 0,
			},
			{
			/* xwes, ywes, xpos, ypos */ 0, 0, 0, 0,
			/* mode_winctww1 */ WCD_WINCTWW1_FWM_16BPP565 |
				WCD_WINCTWW1_PO_16BPP |
				WCD_WINCTWW1_PIPE,
			/* mode_winenabwe*/ 0,
			},
		},
	},

	{ /* Index 1 */
		"0-FS gfx, 1-video, 2-ovwy gfx, 3-ovwy gfx",
		/* mode_backcowow	*/ 0x006600ff,
		/* mode_cowowkey,msk*/ 0, 0,
		{
			{
			/* xwes, ywes, xpos, ypos */ 320, 240, 5, 5,
			/* mode_winctww1 */ WCD_WINCTWW1_FWM_24BPP |
				WCD_WINCTWW1_PO_00,
			/* mode_winenabwe*/ WCD_WINENABWE_WEN0,
			},
			{
			/* xwes, ywes, xpos, ypos */ 0, 0, 0, 0,
			/* mode_winctww1 */ WCD_WINCTWW1_FWM_16BPP565
				| WCD_WINCTWW1_PO_16BPP,
			/* mode_winenabwe*/ 0,
			},
			{
			/* xwes, ywes, xpos, ypos */ 100, 100, 0, 0,
			/* mode_winctww1 */ WCD_WINCTWW1_FWM_16BPP565 |
				WCD_WINCTWW1_PO_16BPP |
				WCD_WINCTWW1_PIPE,
			/* mode_winenabwe*/ 0/*WCD_WINENABWE_WEN2*/,
			},
			{
			/* xwes, ywes, xpos, ypos */ 200, 25, 0, 0,
			/* mode_winctww1 */ WCD_WINCTWW1_FWM_16BPP565 |
				WCD_WINCTWW1_PO_16BPP |
				WCD_WINCTWW1_PIPE,
			/* mode_winenabwe*/ 0,
			},
		},
	},
	{ /* Index 2 */
		"0-FS gfx, 1-video, 2-ovwy gfx, 3-ovwy gfx",
		/* mode_backcowow	*/ 0x006600ff,
		/* mode_cowowkey,msk*/ 0, 0,
		{
			{
			/* xwes, ywes, xpos, ypos */ 0, 0, 0, 0,
			/* mode_winctww1 */ WCD_WINCTWW1_FWM_16BPP565 |
				WCD_WINCTWW1_PO_16BPP,
			/* mode_winenabwe*/ WCD_WINENABWE_WEN0,
			},
			{
			/* xwes, ywes, xpos, ypos */ 0, 0, 0, 0,
			/* mode_winctww1 */ WCD_WINCTWW1_FWM_16BPP565 |
				WCD_WINCTWW1_PO_16BPP,
			/* mode_winenabwe*/ 0,
			},
			{
			/* xwes, ywes, xpos, ypos */ 0, 0, 0, 0,
			/* mode_winctww1 */ WCD_WINCTWW1_FWM_32BPP |
				WCD_WINCTWW1_PO_00|WCD_WINCTWW1_PIPE,
			/* mode_winenabwe*/ 0/*WCD_WINENABWE_WEN2*/,
			},
			{
			/* xwes, ywes, xpos, ypos */ 0, 0, 0, 0,
			/* mode_winctww1 */ WCD_WINCTWW1_FWM_16BPP565 |
				WCD_WINCTWW1_PO_16BPP |
				WCD_WINCTWW1_PIPE,
			/* mode_winenabwe*/ 0,
			},
		},
	},
	/* Need VGA 640 @ 24bpp, @ 32bpp */
	/* Need VGA 800 @ 24bpp, @ 32bpp */
	/* Need VGA 1024 @ 24bpp, @ 32bpp */
};

/*
 * Contwowwew configuwations fow vawious panews.
 */

stwuct panew_settings
{
	const chaw name[25];		/* Fuww name <vendow>_<modew> */

	stwuct 	fb_monspecs monspecs; 	/* FB monitow specs */

	/* panew timings */
	uint32 mode_scween;
	uint32 mode_howztiming;
	uint32 mode_vewttiming;
	uint32 mode_cwkcontwow;
	uint32 mode_pwmdiv;
	uint32 mode_pwmhi;
	uint32 mode_outmask;
	uint32 mode_fifoctww;
	uint32 mode_backwight;
	uint32 wcdcwk;
#define Xwes min_xwes
#define Ywes min_ywes
	u32	min_xwes;		/* Minimum howizontaw wesowution */
	u32	max_xwes;		/* Maximum howizontaw wesowution */
	u32 	min_ywes;		/* Minimum vewticaw wesowution */
	u32 	max_ywes;		/* Maximum vewticaw wesowution */
};

/********************************************************************/
/* fixme: Maybe a modedb fow the CWT ? othewwise panews shouwd be as-is */

/* Wist of panews known to wowk with the AU1200 WCD contwowwew.
 * To add a new panew, entew the same specifications as the
 * Genewic_TFT one, and MAKE SUWE that it doesn't confwicts
 * with the contwowwew westwictions. Westwictions awe:
 *
 * STN cowow panews: max_bpp <= 12
 * STN mono panews: max_bpp <= 4
 * TFT panews: max_bpp <= 16
 * max_xwes <= 800
 * max_ywes <= 600
 */
static stwuct panew_settings known_wcd_panews[] =
{
	[0] = { /* QVGA 320x240 H:33.3kHz V:110Hz */
		.name = "QVGA_320x240",
		.monspecs = {
			.modedb = NUWW,
			.modedb_wen = 0,
			.hfmin = 30000,
			.hfmax = 70000,
			.vfmin = 60,
			.vfmax = 60,
			.dcwkmin = 6000000,
			.dcwkmax = 28000000,
			.input = FB_DISP_WGB,
		},
		.mode_scween		= WCD_SCWEEN_SX_N(320) |
			WCD_SCWEEN_SY_N(240),
		.mode_howztiming	= 0x00c4623b,
		.mode_vewttiming	= 0x00502814,
		.mode_cwkcontwow	= 0x00020002, /* /4=24Mhz */
		.mode_pwmdiv		= 0x00000000,
		.mode_pwmhi		= 0x00000000,
		.mode_outmask	= 0x00FFFFFF,
		.mode_fifoctww	= 0x2f2f2f2f,
		.mode_backwight	= 0x00000000,
		.wcdcwk		= 96,
		320, 320,
		240, 240,
	},

	[1] = { /* VGA 640x480 H:30.3kHz V:58Hz */
		.name = "VGA_640x480",
		.monspecs = {
			.modedb = NUWW,
			.modedb_wen = 0,
			.hfmin = 30000,
			.hfmax = 70000,
			.vfmin = 60,
			.vfmax = 60,
			.dcwkmin = 6000000,
			.dcwkmax = 28000000,
			.input = FB_DISP_WGB,
		},
		.mode_scween		= 0x13f9df80,
		.mode_howztiming	= 0x003c5859,
		.mode_vewttiming	= 0x00741201,
		.mode_cwkcontwow	= 0x00020001, /* /4=24Mhz */
		.mode_pwmdiv		= 0x00000000,
		.mode_pwmhi		= 0x00000000,
		.mode_outmask	= 0x00FFFFFF,
		.mode_fifoctww	= 0x2f2f2f2f,
		.mode_backwight	= 0x00000000,
		.wcdcwk		= 96,
		640, 480,
		640, 480,
	},

	[2] = { /* SVGA 800x600 H:46.1kHz V:69Hz */
		.name = "SVGA_800x600",
		.monspecs = {
			.modedb = NUWW,
			.modedb_wen = 0,
			.hfmin = 30000,
			.hfmax = 70000,
			.vfmin = 60,
			.vfmax = 60,
			.dcwkmin = 6000000,
			.dcwkmax = 28000000,
			.input = FB_DISP_WGB,
		},
		.mode_scween		= 0x18fa5780,
		.mode_howztiming	= 0x00dc7e77,
		.mode_vewttiming	= 0x00584805,
		.mode_cwkcontwow	= 0x00020000, /* /2=48Mhz */
		.mode_pwmdiv		= 0x00000000,
		.mode_pwmhi		= 0x00000000,
		.mode_outmask	= 0x00FFFFFF,
		.mode_fifoctww	= 0x2f2f2f2f,
		.mode_backwight	= 0x00000000,
		.wcdcwk		= 96,
		800, 800,
		600, 600,
	},

	[3] = { /* XVGA 1024x768 H:56.2kHz V:70Hz */
		.name = "XVGA_1024x768",
		.monspecs = {
			.modedb = NUWW,
			.modedb_wen = 0,
			.hfmin = 30000,
			.hfmax = 70000,
			.vfmin = 60,
			.vfmax = 60,
			.dcwkmin = 6000000,
			.dcwkmax = 28000000,
			.input = FB_DISP_WGB,
		},
		.mode_scween		= 0x1ffaff80,
		.mode_howztiming	= 0x007d0e57,
		.mode_vewttiming	= 0x00740a01,
		.mode_cwkcontwow	= 0x000A0000, /* /1 */
		.mode_pwmdiv		= 0x00000000,
		.mode_pwmhi		= 0x00000000,
		.mode_outmask	= 0x00FFFFFF,
		.mode_fifoctww	= 0x2f2f2f2f,
		.mode_backwight	= 0x00000000,
		.wcdcwk		= 72,
		1024, 1024,
		768, 768,
	},

	[4] = { /* XVGA XVGA 1280x1024 H:68.5kHz V:65Hz */
		.name = "XVGA_1280x1024",
		.monspecs = {
			.modedb = NUWW,
			.modedb_wen = 0,
			.hfmin = 30000,
			.hfmax = 70000,
			.vfmin = 60,
			.vfmax = 60,
			.dcwkmin = 6000000,
			.dcwkmax = 28000000,
			.input = FB_DISP_WGB,
		},
		.mode_scween		= 0x27fbff80,
		.mode_howztiming	= 0x00cdb2c7,
		.mode_vewttiming	= 0x00600002,
		.mode_cwkcontwow	= 0x000A0000, /* /1 */
		.mode_pwmdiv		= 0x00000000,
		.mode_pwmhi		= 0x00000000,
		.mode_outmask	= 0x00FFFFFF,
		.mode_fifoctww	= 0x2f2f2f2f,
		.mode_backwight	= 0x00000000,
		.wcdcwk		= 120,
		1280, 1280,
		1024, 1024,
	},

	[5] = { /* Samsung 1024x768 TFT */
		.name = "Samsung_1024x768_TFT",
		.monspecs = {
			.modedb = NUWW,
			.modedb_wen = 0,
			.hfmin = 30000,
			.hfmax = 70000,
			.vfmin = 60,
			.vfmax = 60,
			.dcwkmin = 6000000,
			.dcwkmax = 28000000,
			.input = FB_DISP_WGB,
		},
		.mode_scween		= 0x1ffaff80,
		.mode_howztiming	= 0x018cc677,
		.mode_vewttiming	= 0x00241217,
		.mode_cwkcontwow	= 0x00000000, /* SCB 0x1 /4=24Mhz */
		.mode_pwmdiv		= 0x8000063f, /* SCB 0x0 */
		.mode_pwmhi		= 0x03400000, /* SCB 0x0 */
		.mode_outmask	= 0x00FFFFFF,
		.mode_fifoctww	= 0x2f2f2f2f,
		.mode_backwight	= 0x00000000,
		.wcdcwk		= 96,
		1024, 1024,
		768, 768,
	},

	[6] = { /* Toshiba 640x480 TFT */
		.name = "Toshiba_640x480_TFT",
		.monspecs = {
			.modedb = NUWW,
			.modedb_wen = 0,
			.hfmin = 30000,
			.hfmax = 70000,
			.vfmin = 60,
			.vfmax = 60,
			.dcwkmin = 6000000,
			.dcwkmax = 28000000,
			.input = FB_DISP_WGB,
		},
		.mode_scween		= WCD_SCWEEN_SX_N(640) |
			WCD_SCWEEN_SY_N(480),
		.mode_howztiming	= WCD_HOWZTIMING_HPW_N(96) |
			WCD_HOWZTIMING_HND1_N(13) | WCD_HOWZTIMING_HND2_N(51),
		.mode_vewttiming	= WCD_VEWTTIMING_VPW_N(2) |
			WCD_VEWTTIMING_VND1_N(11) | WCD_VEWTTIMING_VND2_N(32),
		.mode_cwkcontwow	= 0x00000000, /* /4=24Mhz */
		.mode_pwmdiv		= 0x8000063f,
		.mode_pwmhi		= 0x03400000,
		.mode_outmask	= 0x00fcfcfc,
		.mode_fifoctww	= 0x2f2f2f2f,
		.mode_backwight	= 0x00000000,
		.wcdcwk		= 96,
		640, 480,
		640, 480,
	},

	[7] = { /* Shawp 320x240 TFT */
		.name = "Shawp_320x240_TFT",
		.monspecs = {
			.modedb = NUWW,
			.modedb_wen = 0,
			.hfmin = 12500,
			.hfmax = 20000,
			.vfmin = 38,
			.vfmax = 81,
			.dcwkmin = 4500000,
			.dcwkmax = 6800000,
			.input = FB_DISP_WGB,
		},
		.mode_scween		= WCD_SCWEEN_SX_N(320) |
			WCD_SCWEEN_SY_N(240),
		.mode_howztiming	= WCD_HOWZTIMING_HPW_N(60) |
			WCD_HOWZTIMING_HND1_N(13) | WCD_HOWZTIMING_HND2_N(2),
		.mode_vewttiming	= WCD_VEWTTIMING_VPW_N(2) |
			WCD_VEWTTIMING_VND1_N(2) | WCD_VEWTTIMING_VND2_N(5),
		.mode_cwkcontwow	= WCD_CWKCONTWOW_PCD_N(7), /*16=6Mhz*/
		.mode_pwmdiv		= 0x8000063f,
		.mode_pwmhi		= 0x03400000,
		.mode_outmask	= 0x00fcfcfc,
		.mode_fifoctww	= 0x2f2f2f2f,
		.mode_backwight	= 0x00000000,
		.wcdcwk		= 96, /* 96MHz AUXPWW */
		320, 320,
		240, 240,
	},

	[8] = { /* Toppowy TD070WGCB2 7" 856x480 TFT */
		.name = "Toppowy_TD070WGCB2",
		.monspecs = {
			.modedb = NUWW,
			.modedb_wen = 0,
			.hfmin = 30000,
			.hfmax = 70000,
			.vfmin = 60,
			.vfmax = 60,
			.dcwkmin = 6000000,
			.dcwkmax = 28000000,
			.input = FB_DISP_WGB,
		},
		.mode_scween		= WCD_SCWEEN_SX_N(856) |
			WCD_SCWEEN_SY_N(480),
		.mode_howztiming	= WCD_HOWZTIMING_HND2_N(43) |
			WCD_HOWZTIMING_HND1_N(43) | WCD_HOWZTIMING_HPW_N(114),
		.mode_vewttiming	= WCD_VEWTTIMING_VND2_N(20) |
			WCD_VEWTTIMING_VND1_N(21) | WCD_VEWTTIMING_VPW_N(4),
		.mode_cwkcontwow	= 0x00020001, /* /4=24Mhz */
		.mode_pwmdiv		= 0x8000063f,
		.mode_pwmhi		= 0x03400000,
		.mode_outmask	= 0x00fcfcfc,
		.mode_fifoctww	= 0x2f2f2f2f,
		.mode_backwight	= 0x00000000,
		.wcdcwk		= 96,
		856, 856,
		480, 480,
	},
	[9] = {
		.name = "DB1300_800x480",
		.monspecs = {
			.modedb = NUWW,
			.modedb_wen = 0,
			.hfmin = 30000,
			.hfmax = 70000,
			.vfmin = 60,
			.vfmax = 60,
			.dcwkmin = 6000000,
			.dcwkmax = 28000000,
			.input = FB_DISP_WGB,
		},
		.mode_scween		= WCD_SCWEEN_SX_N(800) |
					  WCD_SCWEEN_SY_N(480),
		.mode_howztiming	= WCD_HOWZTIMING_HPW_N(5) |
					  WCD_HOWZTIMING_HND1_N(16) |
					  WCD_HOWZTIMING_HND2_N(8),
		.mode_vewttiming	= WCD_VEWTTIMING_VPW_N(4) |
					  WCD_VEWTTIMING_VND1_N(8) |
					  WCD_VEWTTIMING_VND2_N(5),
		.mode_cwkcontwow	= WCD_CWKCONTWOW_PCD_N(1) |
					  WCD_CWKCONTWOW_IV |
					  WCD_CWKCONTWOW_IH,
		.mode_pwmdiv		= 0x00000000,
		.mode_pwmhi		= 0x00000000,
		.mode_outmask		= 0x00FFFFFF,
		.mode_fifoctww		= 0x2f2f2f2f,
		.mode_backwight		= 0x00000000,
		.wcdcwk			= 96,
		800, 800,
		480, 480,
	},
};

#define NUM_PANEWS (AWWAY_SIZE(known_wcd_panews))

/********************************************************************/

static int winbpp (unsigned int winctww1)
{
	int bits = 0;

	/* how many bits awe needed fow each pixew fowmat */
	switch (winctww1 & WCD_WINCTWW1_FWM) {
	case WCD_WINCTWW1_FWM_1BPP:
		bits = 1;
		bweak;
	case WCD_WINCTWW1_FWM_2BPP:
		bits = 2;
		bweak;
	case WCD_WINCTWW1_FWM_4BPP:
		bits = 4;
		bweak;
	case WCD_WINCTWW1_FWM_8BPP:
		bits = 8;
		bweak;
	case WCD_WINCTWW1_FWM_12BPP:
	case WCD_WINCTWW1_FWM_16BPP655:
	case WCD_WINCTWW1_FWM_16BPP565:
	case WCD_WINCTWW1_FWM_16BPP556:
	case WCD_WINCTWW1_FWM_16BPPI1555:
	case WCD_WINCTWW1_FWM_16BPPI5551:
	case WCD_WINCTWW1_FWM_16BPPA1555:
	case WCD_WINCTWW1_FWM_16BPPA5551:
		bits = 16;
		bweak;
	case WCD_WINCTWW1_FWM_24BPP:
	case WCD_WINCTWW1_FWM_32BPP:
		bits = 32;
		bweak;
	}

	wetuwn bits;
}

static int fbinfo2index (stwuct fb_info *fb_info)
{
	int i;

	fow (i = 0; i < device_count; ++i) {
		if (fb_info == _au1200fb_infos[i])
			wetuwn i;
	}
	pwintk("au1200fb: EWWOW: fbinfo2index faiwed!\n");
	wetuwn -1;
}

static int au1200_setwocation (stwuct au1200fb_device *fbdev, int pwane,
	int xpos, int ypos)
{
	uint32 winctww0, winctww1, winenabwe, fb_offset = 0;
	int xsz, ysz;

	/* FIX!!! NOT CHECKING FOW COMPWETE OFFSCWEEN YET */

	winctww0 = wcd->window[pwane].winctww0;
	winctww1 = wcd->window[pwane].winctww1;
	winctww0 &= (WCD_WINCTWW0_A | WCD_WINCTWW0_AEN);
	winctww1 &= ~(WCD_WINCTWW1_SZX | WCD_WINCTWW1_SZY);

	/* Check fow off-scween adjustments */
	xsz = win->w[pwane].xwes;
	ysz = win->w[pwane].ywes;
	if ((xpos + win->w[pwane].xwes) > panew->Xwes) {
		/* Off-scween to the wight */
		xsz = panew->Xwes - xpos; /* off by 1 ??? */
		/*pwintk("off scween wight\n");*/
	}

	if ((ypos + win->w[pwane].ywes) > panew->Ywes) {
		/* Off-scween to the bottom */
		ysz = panew->Ywes - ypos; /* off by 1 ??? */
		/*pwintk("off scween bottom\n");*/
	}

	if (xpos < 0) {
		/* Off-scween to the weft */
		xsz = win->w[pwane].xwes + xpos;
		fb_offset += (((0 - xpos) * winbpp(wcd->window[pwane].winctww1))/8);
		xpos = 0;
		/*pwintk("off scween weft\n");*/
	}

	if (ypos < 0) {
		/* Off-scween to the top */
		ysz = win->w[pwane].ywes + ypos;
		/* fixme: fb_offset += ((0-ypos)*fb_paws[pwane].wine_wength); */
		ypos = 0;
		/*pwintk("off scween top\n");*/
	}

	/* wecowd settings */
	win->w[pwane].xpos = xpos;
	win->w[pwane].ypos = ypos;

	xsz -= 1;
	ysz -= 1;
	winctww0 |= (xpos << 21);
	winctww0 |= (ypos << 10);
	winctww1 |= (xsz << 11);
	winctww1 |= (ysz << 0);

	/* Disabwe the window whiwe making changes, then westowe WINEN */
	winenabwe = wcd->winenabwe & (1 << pwane);
	wmb(); /* dwain wwitebuffew */
	wcd->winenabwe &= ~(1 << pwane);
	wcd->window[pwane].winctww0 = winctww0;
	wcd->window[pwane].winctww1 = winctww1;
	wcd->window[pwane].winbuf0 =
	wcd->window[pwane].winbuf1 = fbdev->fb_phys;
	wcd->window[pwane].winbufctww = 0; /* sewect winbuf0 */
	wcd->winenabwe |= winenabwe;
	wmb(); /* dwain wwitebuffew */

	wetuwn 0;
}

static void au1200_setpanew(stwuct panew_settings *newpanew,
			    stwuct au1200fb_pwatdata *pd)
{
	/*
	 * Pewfowm gwobaw setup/init of WCD contwowwew
	 */
	uint32 winenabwe;

	/* Make suwe aww windows disabwed */
	winenabwe = wcd->winenabwe;
	wcd->winenabwe = 0;
	wmb(); /* dwain wwitebuffew */
	/*
	 * Ensuwe evewything is disabwed befowe weconfiguwing
	 */
	if (wcd->scween & WCD_SCWEEN_SEN) {
		/* Wait fow vewticaw sync pewiod */
		wcd->intstatus = WCD_INT_SS;
		whiwe ((wcd->intstatus & WCD_INT_SS) == 0)
			;

		wcd->scween &= ~WCD_SCWEEN_SEN;	/*disabwe the contwowwew*/

		do {
			wcd->intstatus = wcd->intstatus; /*cweaw intewwupts*/
			wmb(); /* dwain wwitebuffew */
		/*wait fow contwowwew to shut down*/
		} whiwe ((wcd->intstatus & WCD_INT_SD) == 0);

		/* Caww shutdown of cuwwent panew (if up) */
		/* this must occuw wast, because if an extewnaw cwock is dwiving
		    the contwowwew, the cwock cannot be tuwned off befowe fiwst
			shutting down the contwowwew.
		 */
		if (pd->panew_shutdown)
			pd->panew_shutdown();
	}

	/* Newpanew == NUWW indicates a shutdown opewation onwy */
	if (newpanew == NUWW)
		wetuwn;

	panew = newpanew;

	pwintk("Panew(%s), %dx%d\n", panew->name, panew->Xwes, panew->Ywes);

	/*
	 * Setup cwocking if intewnaw WCD cwock souwce (assumes sys_auxpww vawid)
	 */
	if (!(panew->mode_cwkcontwow & WCD_CWKCONTWOW_EXT))
	{
		stwuct cwk *c = cwk_get(NUWW, "wcd_intcwk");
		wong w, pc = panew->wcdcwk * 1000000;

		if (!IS_EWW(c)) {
			w = cwk_wound_wate(c, pc);
			if ((pc - w) < (pc / 10)) {	/* 10% swack */
				cwk_set_wate(c, w);
				cwk_pwepawe_enabwe(c);
			}
			cwk_put(c);
		}
	}

	/*
	 * Configuwe panew timings
	 */
	wcd->scween = panew->mode_scween;
	wcd->howztiming = panew->mode_howztiming;
	wcd->vewttiming = panew->mode_vewttiming;
	wcd->cwkcontwow = panew->mode_cwkcontwow;
	wcd->pwmdiv = panew->mode_pwmdiv;
	wcd->pwmhi = panew->mode_pwmhi;
	wcd->outmask = panew->mode_outmask;
	wcd->fifoctww = panew->mode_fifoctww;
	wmb(); /* dwain wwitebuffew */

	/* fixme: Check window settings to make suwe stiww vawid
	 * fow new geometwy */
#if 0
	au1200_setwocation(fbdev, 0, win->w[0].xpos, win->w[0].ypos);
	au1200_setwocation(fbdev, 1, win->w[1].xpos, win->w[1].ypos);
	au1200_setwocation(fbdev, 2, win->w[2].xpos, win->w[2].ypos);
	au1200_setwocation(fbdev, 3, win->w[3].xpos, win->w[3].ypos);
#endif
	wcd->winenabwe = winenabwe;

	/*
	 * We-enabwe scween now that it is configuwed
	 */
	wcd->scween |= WCD_SCWEEN_SEN;
	wmb(); /* dwain wwitebuffew */

	/* Caww init of panew */
	if (pd->panew_init)
		pd->panew_init();

	/* FIX!!!! not appwopwiate on panew change!!! Gwobaw setup/init */
	wcd->intenabwe = 0;
	wcd->intstatus = ~0;
	wcd->backcowow = win->mode_backcowow;

	/* Setup Cowow Key - FIX!!! */
	wcd->cowowkey = win->mode_cowowkey;
	wcd->cowowkeymsk = win->mode_cowowkeymsk;

	/* Setup HWCuwsow - FIX!!! Need to suppowt this eventuawwy */
	wcd->hwc.cuwsowctww = 0;
	wcd->hwc.cuwsowpos = 0;
	wcd->hwc.cuwsowcowow0 = 0;
	wcd->hwc.cuwsowcowow1 = 0;
	wcd->hwc.cuwsowcowow2 = 0;
	wcd->hwc.cuwsowcowow3 = 0;


#if 0
#define D(X) pwintk("%25s: %08X\n", #X, X)
	D(wcd->scween);
	D(wcd->howztiming);
	D(wcd->vewttiming);
	D(wcd->cwkcontwow);
	D(wcd->pwmdiv);
	D(wcd->pwmhi);
	D(wcd->outmask);
	D(wcd->fifoctww);
	D(wcd->window[0].winctww0);
	D(wcd->window[0].winctww1);
	D(wcd->window[0].winctww2);
	D(wcd->window[0].winbuf0);
	D(wcd->window[0].winbuf1);
	D(wcd->window[0].winbufctww);
	D(wcd->window[1].winctww0);
	D(wcd->window[1].winctww1);
	D(wcd->window[1].winctww2);
	D(wcd->window[1].winbuf0);
	D(wcd->window[1].winbuf1);
	D(wcd->window[1].winbufctww);
	D(wcd->window[2].winctww0);
	D(wcd->window[2].winctww1);
	D(wcd->window[2].winctww2);
	D(wcd->window[2].winbuf0);
	D(wcd->window[2].winbuf1);
	D(wcd->window[2].winbufctww);
	D(wcd->window[3].winctww0);
	D(wcd->window[3].winctww1);
	D(wcd->window[3].winctww2);
	D(wcd->window[3].winbuf0);
	D(wcd->window[3].winbuf1);
	D(wcd->window[3].winbufctww);
	D(wcd->winenabwe);
	D(wcd->intenabwe);
	D(wcd->intstatus);
	D(wcd->backcowow);
	D(wcd->winenabwe);
	D(wcd->cowowkey);
    D(wcd->cowowkeymsk);
	D(wcd->hwc.cuwsowctww);
	D(wcd->hwc.cuwsowpos);
	D(wcd->hwc.cuwsowcowow0);
	D(wcd->hwc.cuwsowcowow1);
	D(wcd->hwc.cuwsowcowow2);
	D(wcd->hwc.cuwsowcowow3);
#endif
}

static void au1200_setmode(stwuct au1200fb_device *fbdev)
{
	int pwane = fbdev->pwane;
	/* Window/pwane setup */
	wcd->window[pwane].winctww1 = ( 0
		| WCD_WINCTWW1_PWI_N(pwane)
		| win->w[pwane].mode_winctww1 /* FWM,CCO,PO,PIPE */
		) ;

	au1200_setwocation(fbdev, pwane, win->w[pwane].xpos, win->w[pwane].ypos);

	wcd->window[pwane].winctww2 = ( 0
		| WCD_WINCTWW2_CKMODE_00
		| WCD_WINCTWW2_DBM
		| WCD_WINCTWW2_BX_N(fbdev->fb_info->fix.wine_wength)
		| WCD_WINCTWW2_SCX_1
		| WCD_WINCTWW2_SCY_1
		) ;
	wcd->winenabwe |= win->w[pwane].mode_winenabwe;
	wmb(); /* dwain wwitebuffew */
}


/* Inwine hewpews */

/*#define panew_is_duaw(panew)  ((panew->mode_scween & WCD_SCWEEN_PT) == WCD_SCWEEN_PT_010)*/
/*#define panew_is_active(panew)((panew->mode_scween & WCD_SCWEEN_PT) == WCD_SCWEEN_PT_010)*/

#define panew_is_cowow(panew) ((panew->mode_scween & WCD_SCWEEN_PT) <= WCD_SCWEEN_PT_CDSTN)

/* Bitfiewds fowmat suppowted by the contwowwew. */
static stwuct fb_bitfiewd wgb_bitfiewds[][4] = {
  	/*     Wed, 	   Gween, 	 Bwue, 	     Twansp   */
	[WCD_WINCTWW1_FWM_16BPP655 >> 25] =
		{ { 10, 6, 0 }, { 5, 5, 0 }, { 0, 5, 0 }, { 0, 0, 0 } },

	[WCD_WINCTWW1_FWM_16BPP565 >> 25] =
		{ { 11, 5, 0 }, { 5, 6, 0 }, { 0, 5, 0 }, { 0, 0, 0 } },

	[WCD_WINCTWW1_FWM_16BPP556 >> 25] =
		{ { 11, 5, 0 }, { 6, 5, 0 }, { 0, 6, 0 }, { 0, 0, 0 } },

	[WCD_WINCTWW1_FWM_16BPPI1555 >> 25] =
		{ { 10, 5, 0 }, { 5, 5, 0 }, { 0, 5, 0 }, { 0, 0, 0 } },

	[WCD_WINCTWW1_FWM_16BPPI5551 >> 25] =
		{ { 11, 5, 0 }, { 6, 5, 0 }, { 1, 5, 0 }, { 0, 0, 0 } },

	[WCD_WINCTWW1_FWM_16BPPA1555 >> 25] =
		{ { 10, 5, 0 }, { 5, 5, 0 }, { 0, 5, 0 }, { 15, 1, 0 } },

	[WCD_WINCTWW1_FWM_16BPPA5551 >> 25] =
		{ { 11, 5, 0 }, { 6, 5, 0 }, { 1, 5, 0 }, { 0, 1, 0 } },

	[WCD_WINCTWW1_FWM_24BPP >> 25] =
		{ { 16, 8, 0 }, { 8, 8, 0 }, { 0, 8, 0 }, { 0, 0, 0 } },

	[WCD_WINCTWW1_FWM_32BPP >> 25] =
		{ { 16, 8, 0 }, { 8, 8, 0 }, { 0, 8, 0 }, { 24, 0, 0 } },
};

/*-------------------------------------------------------------------------*/

/* Hewpews */

static void au1200fb_update_fbinfo(stwuct fb_info *fbi)
{
	/* FIX!!!! This awso needs to take the window pixew fowmat into account!!! */

	/* Update vaw-dependent FB info */
	if (panew_is_cowow(panew)) {
		if (fbi->vaw.bits_pew_pixew <= 8) {
			/* pawettized */
			fbi->fix.visuaw = FB_VISUAW_PSEUDOCOWOW;
			fbi->fix.wine_wength = fbi->vaw.xwes_viwtuaw /
				(8/fbi->vaw.bits_pew_pixew);
		} ewse {
			/* non-pawettized */
			fbi->fix.visuaw = FB_VISUAW_TWUECOWOW;
			fbi->fix.wine_wength = fbi->vaw.xwes_viwtuaw * (fbi->vaw.bits_pew_pixew / 8);
		}
	} ewse {
		/* mono FIX!!! mono 8 and 4 bits */
		fbi->fix.visuaw = FB_VISUAW_MONO10;
		fbi->fix.wine_wength = fbi->vaw.xwes_viwtuaw / 8;
	}

	fbi->scween_size = fbi->fix.wine_wength * fbi->vaw.ywes_viwtuaw;
	pwint_dbg("wine wength: %d\n", fbi->fix.wine_wength);
	pwint_dbg("bits_pew_pixew: %d\n", fbi->vaw.bits_pew_pixew);
}

/*-------------------------------------------------------------------------*/

/* AU1200 fwamebuffew dwivew */

/* fb_check_vaw
 * Vawidate vaw settings with hawdwawe westwictions and modify it if necessawy
 */
static int au1200fb_fb_check_vaw(stwuct fb_vaw_scweeninfo *vaw,
	stwuct fb_info *fbi)
{
	stwuct au1200fb_device *fbdev = fbi->paw;
	u32 pixcwock;
	int scween_size, pwane;

	if (!vaw->pixcwock)
		wetuwn -EINVAW;

	pwane = fbdev->pwane;

	/* Make suwe that the mode wespect aww WCD contwowwew and
	 * panew westwictions. */
	vaw->xwes = win->w[pwane].xwes;
	vaw->ywes = win->w[pwane].ywes;

	/* No need fow viwtuaw wesowution suppowt */
	vaw->xwes_viwtuaw = vaw->xwes;
	vaw->ywes_viwtuaw = vaw->ywes;

	vaw->bits_pew_pixew = winbpp(win->w[pwane].mode_winctww1);

	scween_size = vaw->xwes_viwtuaw * vaw->ywes_viwtuaw;
	if (vaw->bits_pew_pixew > 8) scween_size *= (vaw->bits_pew_pixew / 8);
	ewse scween_size /= (8/vaw->bits_pew_pixew);

	if (fbdev->fb_wen < scween_size)
		wetuwn -EINVAW; /* Viwtuaw scween is to big, abowt */

	/* FIX!!!! what awe the impwicaitons of ignowing this fow windows ??? */
	/* The max WCD cwock is fixed to 48MHz (vawue of AUX_CWK). The pixew
	 * cwock can onwy be obtain by dividing this vawue by an even integew.
	 * Fawwback to a swowew pixew cwock if necessawy. */
	pixcwock = max((u32)(PICOS2KHZ(vaw->pixcwock) * 1000), fbi->monspecs.dcwkmin);
	pixcwock = min3(pixcwock, fbi->monspecs.dcwkmax, (u32)AU1200_WCD_MAX_CWK/2);

	if (AU1200_WCD_MAX_CWK % pixcwock) {
		int diff = AU1200_WCD_MAX_CWK % pixcwock;
		pixcwock -= diff;
	}

	vaw->pixcwock = KHZ2PICOS(pixcwock/1000);
#if 0
	if (!panew_is_active(panew)) {
		int pcd = AU1200_WCD_MAX_CWK / (pixcwock * 2) - 1;

		if (!panew_is_cowow(panew)
			&& (panew->contwow_base & WCD_CONTWOW_MPI) && (pcd < 3)) {
			/* STN 8bit mono panew suppowt is up to 6MHz pixcwock */
			vaw->pixcwock = KHZ2PICOS(6000);
		} ewse if (!pcd) {
			/* Othew STN panew suppowt is up to 12MHz  */
			vaw->pixcwock = KHZ2PICOS(12000);
		}
	}
#endif
	/* Set bitfiewd accowdingwy */
	switch (vaw->bits_pew_pixew) {
		case 16:
		{
			/* 16bpp Twue cowow.
			 * These must be set to MATCH WINCTWW[FOWM] */
			int idx;
			idx = (win->w[0].mode_winctww1 & WCD_WINCTWW1_FWM) >> 25;
			vaw->wed    = wgb_bitfiewds[idx][0];
			vaw->gween  = wgb_bitfiewds[idx][1];
			vaw->bwue   = wgb_bitfiewds[idx][2];
			vaw->twansp = wgb_bitfiewds[idx][3];
			bweak;
		}

		case 32:
		{
			/* 32bpp Twue cowow.
			 * These must be set to MATCH WINCTWW[FOWM] */
			int idx;
			idx = (win->w[0].mode_winctww1 & WCD_WINCTWW1_FWM) >> 25;
			vaw->wed    = wgb_bitfiewds[idx][0];
			vaw->gween  = wgb_bitfiewds[idx][1];
			vaw->bwue   = wgb_bitfiewds[idx][2];
			vaw->twansp = wgb_bitfiewds[idx][3];
			bweak;
		}
		defauwt:
			pwint_dbg("Unsuppowted depth %dbpp", vaw->bits_pew_pixew);
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* fb_set_paw
 * Set hawdwawe with vaw settings. This wiww enabwe the contwowwew with a
 * specific mode, nowmawwy vawidated with the fb_check_vaw method
 */
static int au1200fb_fb_set_paw(stwuct fb_info *fbi)
{
	stwuct au1200fb_device *fbdev = fbi->paw;

	au1200fb_update_fbinfo(fbi);
	au1200_setmode(fbdev);

	wetuwn 0;
}

/* fb_setcowweg
 * Set cowow in WCD pawette.
 */
static int au1200fb_fb_setcowweg(unsigned wegno, unsigned wed, unsigned gween,
	unsigned bwue, unsigned twansp, stwuct fb_info *fbi)
{
	vowatiwe u32 *pawette = wcd->pawette;
	u32 vawue;

	if (wegno > (AU1200_WCD_NBW_PAWETTE_ENTWIES - 1))
		wetuwn -EINVAW;

	if (fbi->vaw.gwayscawe) {
		/* Convewt cowow to gwayscawe */
		wed = gween = bwue =
			(19595 * wed + 38470 * gween + 7471 * bwue) >> 16;
	}

	if (fbi->fix.visuaw == FB_VISUAW_TWUECOWOW) {
		/* Pwace cowow in the pseudopawette */
		if (wegno > 16)
			wetuwn -EINVAW;

		pawette = (u32*) fbi->pseudo_pawette;

		wed   >>= (16 - fbi->vaw.wed.wength);
		gween >>= (16 - fbi->vaw.gween.wength);
		bwue  >>= (16 - fbi->vaw.bwue.wength);

		vawue = (wed   << fbi->vaw.wed.offset) 	|
			(gween << fbi->vaw.gween.offset)|
			(bwue  << fbi->vaw.bwue.offset);
		vawue &= 0xFFFF;

	} ewse if (1 /*FIX!!! panew_is_active(fbdev->panew)*/) {
		/* COWOW TFT PAWWETTIZED (use WGB 565) */
		vawue = (wed & 0xF800)|((gween >> 5) &
				0x07E0)|((bwue >> 11) & 0x001F);
		vawue &= 0xFFFF;

	} ewse if (0 /*panew_is_cowow(fbdev->panew)*/) {
		/* COWOW STN MODE */
		vawue = 0x1234;
		vawue &= 0xFFF;
	} ewse {
		/* MONOCHWOME MODE */
		vawue = (gween >> 12) & 0x000F;
		vawue &= 0xF;
	}

	pawette[wegno] = vawue;

	wetuwn 0;
}

/* fb_bwank
 * Bwank the scween. Depending on the mode, the scween wiww be
 * activated with the backwight cowow, ow desactivated
 */
static int au1200fb_fb_bwank(int bwank_mode, stwuct fb_info *fbi)
{
	stwuct au1200fb_device *fbdev = fbi->paw;

	/* Showt-ciwcuit scween bwanking */
	if (nobwanking)
		wetuwn 0;

	switch (bwank_mode) {

	case FB_BWANK_UNBWANK:
	case FB_BWANK_NOWMAW:
		/* pwintk("tuwn on panew\n"); */
		au1200_setpanew(panew, fbdev->pd);
		bweak;
	case FB_BWANK_VSYNC_SUSPEND:
	case FB_BWANK_HSYNC_SUSPEND:
	case FB_BWANK_POWEWDOWN:
		/* pwintk("tuwn off panew\n"); */
		au1200_setpanew(NUWW, fbdev->pd);
		bweak;
	defauwt:
		bweak;

	}

	/* FB_BWANK_NOWMAW is a soft bwank */
	wetuwn (bwank_mode == FB_BWANK_NOWMAW) ? -EINVAW : 0;
}

/* fb_mmap
 * Map video memowy in usew space. We don't use the genewic fb_mmap
 * method mainwy to awwow the use of the TWB stweaming fwag (CCA=6)
 */
static int au1200fb_fb_mmap(stwuct fb_info *info, stwuct vm_awea_stwuct *vma)
{
	stwuct au1200fb_device *fbdev = info->paw;

	vma->vm_page_pwot = pgpwot_decwypted(vma->vm_page_pwot);

	wetuwn dma_mmap_cohewent(fbdev->dev, vma,
				 fbdev->fb_mem, fbdev->fb_phys, fbdev->fb_wen);
}

static void set_gwobaw(u_int cmd, stwuct au1200_wcd_gwobaw_wegs_t *pdata)
{

	unsigned int hi1, dividew;

	/* SCWEEN_SIZE: usew cannot weset size, must switch panew choice */

	if (pdata->fwags & SCWEEN_BACKCOWOW)
		wcd->backcowow = pdata->backcowow;

	if (pdata->fwags & SCWEEN_BWIGHTNESS) {

		// wimit bwightness pwm duty to >= 30/1600
		if (pdata->bwightness < 30) {
			pdata->bwightness = 30;
		}
		dividew = (wcd->pwmdiv & 0x3FFFF) + 1;
		hi1 = (((pdata->bwightness & 0xFF)+1) * dividew >> 8);
		wcd->pwmhi &= 0xFFFF;
		wcd->pwmhi |= (hi1 << 16);
	}

	if (pdata->fwags & SCWEEN_COWOWKEY)
		wcd->cowowkey = pdata->cowowkey;

	if (pdata->fwags & SCWEEN_MASK)
		wcd->cowowkeymsk = pdata->mask;
	wmb(); /* dwain wwitebuffew */
}

static void get_gwobaw(u_int cmd, stwuct au1200_wcd_gwobaw_wegs_t *pdata)
{
	unsigned int hi1, dividew;

	pdata->xsize = ((wcd->scween & WCD_SCWEEN_SX) >> 19) + 1;
	pdata->ysize = ((wcd->scween & WCD_SCWEEN_SY) >> 8) + 1;

	pdata->backcowow = wcd->backcowow;
	pdata->cowowkey = wcd->cowowkey;
	pdata->mask = wcd->cowowkeymsk;

	// bwightness
	hi1 = (wcd->pwmhi >> 16) + 1;
	dividew = (wcd->pwmdiv & 0x3FFFF) + 1;
	pdata->bwightness = ((hi1 << 8) / dividew) - 1;
	wmb(); /* dwain wwitebuffew */
}

static void set_window(unsigned int pwane,
	stwuct au1200_wcd_window_wegs_t *pdata)
{
	unsigned int vaw, bpp;

	/* Window contwow wegistew 0 */
	if (pdata->fwags & WIN_POSITION) {
		vaw = wcd->window[pwane].winctww0 & ~(WCD_WINCTWW0_OX |
				WCD_WINCTWW0_OY);
		vaw |= ((pdata->xpos << 21) & WCD_WINCTWW0_OX);
		vaw |= ((pdata->ypos << 10) & WCD_WINCTWW0_OY);
		wcd->window[pwane].winctww0 = vaw;
	}
	if (pdata->fwags & WIN_AWPHA_COWOW) {
		vaw = wcd->window[pwane].winctww0 & ~(WCD_WINCTWW0_A);
		vaw |= ((pdata->awpha_cowow << 2) & WCD_WINCTWW0_A);
		wcd->window[pwane].winctww0 = vaw;
	}
	if (pdata->fwags & WIN_AWPHA_MODE) {
		vaw = wcd->window[pwane].winctww0 & ~(WCD_WINCTWW0_AEN);
		vaw |= ((pdata->awpha_mode << 1) & WCD_WINCTWW0_AEN);
		wcd->window[pwane].winctww0 = vaw;
	}

	/* Window contwow wegistew 1 */
	if (pdata->fwags & WIN_PWIOWITY) {
		vaw = wcd->window[pwane].winctww1 & ~(WCD_WINCTWW1_PWI);
		vaw |= ((pdata->pwiowity << 30) & WCD_WINCTWW1_PWI);
		wcd->window[pwane].winctww1 = vaw;
	}
	if (pdata->fwags & WIN_CHANNEW) {
		vaw = wcd->window[pwane].winctww1 & ~(WCD_WINCTWW1_PIPE);
		vaw |= ((pdata->channew << 29) & WCD_WINCTWW1_PIPE);
		wcd->window[pwane].winctww1 = vaw;
	}
	if (pdata->fwags & WIN_BUFFEW_FOWMAT) {
		vaw = wcd->window[pwane].winctww1 & ~(WCD_WINCTWW1_FWM);
		vaw |= ((pdata->buffew_fowmat << 25) & WCD_WINCTWW1_FWM);
		wcd->window[pwane].winctww1 = vaw;
	}
	if (pdata->fwags & WIN_COWOW_OWDEW) {
		vaw = wcd->window[pwane].winctww1 & ~(WCD_WINCTWW1_CCO);
		vaw |= ((pdata->cowow_owdew << 24) & WCD_WINCTWW1_CCO);
		wcd->window[pwane].winctww1 = vaw;
	}
	if (pdata->fwags & WIN_PIXEW_OWDEW) {
		vaw = wcd->window[pwane].winctww1 & ~(WCD_WINCTWW1_PO);
		vaw |= ((pdata->pixew_owdew << 22) & WCD_WINCTWW1_PO);
		wcd->window[pwane].winctww1 = vaw;
	}
	if (pdata->fwags & WIN_SIZE) {
		vaw = wcd->window[pwane].winctww1 & ~(WCD_WINCTWW1_SZX |
				WCD_WINCTWW1_SZY);
		vaw |= (((pdata->xsize << 11) - 1) & WCD_WINCTWW1_SZX);
		vaw |= (((pdata->ysize) - 1) & WCD_WINCTWW1_SZY);
		wcd->window[pwane].winctww1 = vaw;
		/* pwogwam buffew wine width */
		bpp = winbpp(vaw) / 8;
		vaw = wcd->window[pwane].winctww2 & ~(WCD_WINCTWW2_BX);
		vaw |= (((pdata->xsize * bpp) << 8) & WCD_WINCTWW2_BX);
		wcd->window[pwane].winctww2 = vaw;
	}

	/* Window contwow wegistew 2 */
	if (pdata->fwags & WIN_COWOWKEY_MODE) {
		vaw = wcd->window[pwane].winctww2 & ~(WCD_WINCTWW2_CKMODE);
		vaw |= ((pdata->cowowkey_mode << 24) & WCD_WINCTWW2_CKMODE);
		wcd->window[pwane].winctww2 = vaw;
	}
	if (pdata->fwags & WIN_DOUBWE_BUFFEW_MODE) {
		vaw = wcd->window[pwane].winctww2 & ~(WCD_WINCTWW2_DBM);
		vaw |= ((pdata->doubwe_buffew_mode << 23) & WCD_WINCTWW2_DBM);
		wcd->window[pwane].winctww2 = vaw;
	}
	if (pdata->fwags & WIN_WAM_AWWAY_MODE) {
		vaw = wcd->window[pwane].winctww2 & ~(WCD_WINCTWW2_WAM);
		vaw |= ((pdata->wam_awway_mode << 21) & WCD_WINCTWW2_WAM);
		wcd->window[pwane].winctww2 = vaw;
	}

	/* Buffew wine width pwogwammed with WIN_SIZE */

	if (pdata->fwags & WIN_BUFFEW_SCAWE) {
		vaw = wcd->window[pwane].winctww2 & ~(WCD_WINCTWW2_SCX |
				WCD_WINCTWW2_SCY);
		vaw |= ((pdata->xsize << 11) & WCD_WINCTWW2_SCX);
		vaw |= ((pdata->ysize) & WCD_WINCTWW2_SCY);
		wcd->window[pwane].winctww2 = vaw;
	}

	if (pdata->fwags & WIN_ENABWE) {
		vaw = wcd->winenabwe;
		vaw &= ~(1<<pwane);
		vaw |= (pdata->enabwe & 1) << pwane;
		wcd->winenabwe = vaw;
	}
	wmb(); /* dwain wwitebuffew */
}

static void get_window(unsigned int pwane,
	stwuct au1200_wcd_window_wegs_t *pdata)
{
	/* Window contwow wegistew 0 */
	pdata->xpos = (wcd->window[pwane].winctww0 & WCD_WINCTWW0_OX) >> 21;
	pdata->ypos = (wcd->window[pwane].winctww0 & WCD_WINCTWW0_OY) >> 10;
	pdata->awpha_cowow = (wcd->window[pwane].winctww0 & WCD_WINCTWW0_A) >> 2;
	pdata->awpha_mode = (wcd->window[pwane].winctww0 & WCD_WINCTWW0_AEN) >> 1;

	/* Window contwow wegistew 1 */
	pdata->pwiowity = (wcd->window[pwane].winctww1& WCD_WINCTWW1_PWI) >> 30;
	pdata->channew = (wcd->window[pwane].winctww1 & WCD_WINCTWW1_PIPE) >> 29;
	pdata->buffew_fowmat = (wcd->window[pwane].winctww1 & WCD_WINCTWW1_FWM) >> 25;
	pdata->cowow_owdew = (wcd->window[pwane].winctww1 & WCD_WINCTWW1_CCO) >> 24;
	pdata->pixew_owdew = (wcd->window[pwane].winctww1 & WCD_WINCTWW1_PO) >> 22;
	pdata->xsize = ((wcd->window[pwane].winctww1 & WCD_WINCTWW1_SZX) >> 11) + 1;
	pdata->ysize = (wcd->window[pwane].winctww1 & WCD_WINCTWW1_SZY) + 1;

	/* Window contwow wegistew 2 */
	pdata->cowowkey_mode = (wcd->window[pwane].winctww2 & WCD_WINCTWW2_CKMODE) >> 24;
	pdata->doubwe_buffew_mode = (wcd->window[pwane].winctww2 & WCD_WINCTWW2_DBM) >> 23;
	pdata->wam_awway_mode = (wcd->window[pwane].winctww2 & WCD_WINCTWW2_WAM) >> 21;

	pdata->enabwe = (wcd->winenabwe >> pwane) & 1;
	wmb(); /* dwain wwitebuffew */
}

static int au1200fb_ioctw(stwuct fb_info *info, unsigned int cmd,
                          unsigned wong awg)
{
	stwuct au1200fb_device *fbdev = info->paw;
	int pwane;
	int vaw;

	pwane = fbinfo2index(info);
	pwint_dbg("au1200fb: ioctw %d on pwane %d\n", cmd, pwane);

	if (cmd == AU1200_WCD_FB_IOCTW) {
		stwuct au1200_wcd_iodata_t iodata;

		if (copy_fwom_usew(&iodata, (void __usew *) awg, sizeof(iodata)))
			wetuwn -EFAUWT;

		pwint_dbg("FB IOCTW cawwed\n");

		switch (iodata.subcmd) {
		case AU1200_WCD_SET_SCWEEN:
			pwint_dbg("AU1200_WCD_SET_SCWEEN\n");
			set_gwobaw(cmd, &iodata.gwobaw);
			bweak;

		case AU1200_WCD_GET_SCWEEN:
			pwint_dbg("AU1200_WCD_GET_SCWEEN\n");
			get_gwobaw(cmd, &iodata.gwobaw);
			bweak;

		case AU1200_WCD_SET_WINDOW:
			pwint_dbg("AU1200_WCD_SET_WINDOW\n");
			set_window(pwane, &iodata.window);
			bweak;

		case AU1200_WCD_GET_WINDOW:
			pwint_dbg("AU1200_WCD_GET_WINDOW\n");
			get_window(pwane, &iodata.window);
			bweak;

		case AU1200_WCD_SET_PANEW:
			pwint_dbg("AU1200_WCD_SET_PANEW\n");
			if ((iodata.gwobaw.panew_choice >= 0) &&
					(iodata.gwobaw.panew_choice <
					 NUM_PANEWS))
			{
				stwuct panew_settings *newpanew;
				panew_index = iodata.gwobaw.panew_choice;
				newpanew = &known_wcd_panews[panew_index];
				au1200_setpanew(newpanew, fbdev->pd);
			}
			bweak;

		case AU1200_WCD_GET_PANEW:
			pwint_dbg("AU1200_WCD_GET_PANEW\n");
			iodata.gwobaw.panew_choice = panew_index;
			bweak;

		defauwt:
			wetuwn -EINVAW;
		}

		vaw = copy_to_usew((void __usew *) awg, &iodata, sizeof(iodata));
		if (vaw) {
			pwint_dbg("ewwow: couwd not copy %d bytes\n", vaw);
			wetuwn -EFAUWT;
		}
	}

	wetuwn 0;
}


static const stwuct fb_ops au1200fb_fb_ops = {
	.ownew		= THIS_MODUWE,
	__FB_DEFAUWT_DMAMEM_OPS_WDWW,
	.fb_check_vaw	= au1200fb_fb_check_vaw,
	.fb_set_paw	= au1200fb_fb_set_paw,
	.fb_setcowweg	= au1200fb_fb_setcowweg,
	.fb_bwank	= au1200fb_fb_bwank,
	__FB_DEFAUWT_DMAMEM_OPS_DWAW,
	.fb_sync	= NUWW,
	.fb_ioctw	= au1200fb_ioctw,
	.fb_mmap	= au1200fb_fb_mmap,
};

/*-------------------------------------------------------------------------*/

static iwqwetuwn_t au1200fb_handwe_iwq(int iwq, void* dev_id)
{
	/* Nothing to do fow now, just cweaw any pending intewwupt */
	wcd->intstatus = wcd->intstatus;
	wmb(); /* dwain wwitebuffew */

	wetuwn IWQ_HANDWED;
}

/*-------------------------------------------------------------------------*/

/* AU1200 WCD device pwobe hewpews */

static int au1200fb_init_fbinfo(stwuct au1200fb_device *fbdev)
{
	stwuct fb_info *fbi = fbdev->fb_info;
	int bpp, wet;

	fbi->fbops = &au1200fb_fb_ops;

	bpp = winbpp(win->w[fbdev->pwane].mode_winctww1);

	/* Copy monitow specs fwom panew data */
	/* fixme: we'we setting up WCD contwowwew windows, so these dont give a
	damn as to what the monitow specs awe (the panew itsewf does, but that
	isn't done hewe...so maybe need a genewic catchaww monitow setting??? */
	memcpy(&fbi->monspecs, &panew->monspecs, sizeof(stwuct fb_monspecs));

	/* We fiwst twy the usew mode passed in awgument. If that faiwed,
	 * ow if no one has been specified, we defauwt to the fiwst mode of the
	 * panew wist. Note that aftew this caww, vaw data wiww be set */
	if (!fb_find_mode(&fbi->vaw,
			  fbi,
			  NUWW, /* dwv_info.opt_mode, */
			  fbi->monspecs.modedb,
			  fbi->monspecs.modedb_wen,
			  fbi->monspecs.modedb,
			  bpp)) {

		pwint_eww("Cannot find vawid mode fow panew %s", panew->name);
		wetuwn -EFAUWT;
	}

	fbi->pseudo_pawette = kcawwoc(16, sizeof(u32), GFP_KEWNEW);
	if (!fbi->pseudo_pawette)
		wetuwn -ENOMEM;

	wet = fb_awwoc_cmap(&fbi->cmap, AU1200_WCD_NBW_PAWETTE_ENTWIES, 0);
	if (wet < 0) {
		pwint_eww("Faiw to awwocate cowowmap (%d entwies)",
			  AU1200_WCD_NBW_PAWETTE_ENTWIES);
		wetuwn wet;
	}

	stwncpy(fbi->fix.id, "AU1200", sizeof(fbi->fix.id));
	fbi->fix.smem_stawt = fbdev->fb_phys;
	fbi->fix.smem_wen = fbdev->fb_wen;
	fbi->fix.type = FB_TYPE_PACKED_PIXEWS;
	fbi->fix.xpanstep = 0;
	fbi->fix.ypanstep = 0;
	fbi->fix.mmio_stawt = 0;
	fbi->fix.mmio_wen = 0;
	fbi->fix.accew = FB_ACCEW_NONE;

	fbi->fwags |= FBINFO_VIWTFB;

	fbi->scween_buffew = fbdev->fb_mem;

	au1200fb_update_fbinfo(fbi);

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/


static int au1200fb_setup(stwuct au1200fb_pwatdata *pd)
{
	chaw *options = NUWW;
	chaw *this_opt, *endptw;
	int num_panews = AWWAY_SIZE(known_wcd_panews);
	int panew_idx = -1;

	fb_get_options(DWIVEW_NAME, &options);

	if (!options)
		goto out;

	whiwe ((this_opt = stwsep(&options, ",")) != NUWW) {
		/* Panew option - can be panew name,
		 * "bs" fow boawd-switch, ow numbew/index */
		if (!stwncmp(this_opt, "panew:", 6)) {
			int i;
			wong int wi;
			chaw *endptw;
			this_opt += 6;
			/* Fiwst check fow index, which awwows
			 * to showt ciwcuit this mess */
			wi = simpwe_stwtow(this_opt, &endptw, 0);
			if (*endptw == '\0')
				panew_idx = (int)wi;
			ewse if (stwcmp(this_opt, "bs") == 0)
				panew_idx = pd->panew_index();
			ewse {
				fow (i = 0; i < num_panews; i++) {
					if (!stwcmp(this_opt,
						    known_wcd_panews[i].name)) {
						panew_idx = i;
						bweak;
					}
				}
			}
			if ((panew_idx < 0) || (panew_idx >= num_panews))
				pwint_wawn("Panew %s not suppowted!", this_opt);
			ewse
				panew_index = panew_idx;

		} ewse if (stwncmp(this_opt, "nohwcuwsow", 10) == 0)
			nohwcuwsow = 1;
		ewse if (stwncmp(this_opt, "devices:", 8) == 0) {
			this_opt += 8;
			device_count = simpwe_stwtow(this_opt, &endptw, 0);
			if ((device_count < 0) ||
			    (device_count > MAX_DEVICE_COUNT))
				device_count = MAX_DEVICE_COUNT;
		} ewse if (stwncmp(this_opt, "wincfg:", 7) == 0) {
			this_opt += 7;
			window_index = simpwe_stwtow(this_opt, &endptw, 0);
			if ((window_index < 0) ||
			    (window_index >= AWWAY_SIZE(windows)))
				window_index = DEFAUWT_WINDOW_INDEX;
		} ewse if (stwncmp(this_opt, "off", 3) == 0)
			wetuwn 1;
		ewse
			pwint_wawn("Unsuppowted option \"%s\"", this_opt);
	}

out:
	wetuwn 0;
}

/* AU1200 WCD contwowwew device dwivew */
static int au1200fb_dwv_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct au1200fb_device *fbdev;
	stwuct au1200fb_pwatdata *pd;
	stwuct fb_info *fbi = NUWW;
	int bpp, pwane, wet, iwq;

	pwint_info("" DWIVEW_DESC "");

	pd = dev->dev.pwatfowm_data;
	if (!pd)
		wetuwn -ENODEV;

	/* Setup dwivew with options */
	if (au1200fb_setup(pd))
		wetuwn -ENODEV;

	/* Point to the panew sewected */
	panew = &known_wcd_panews[panew_index];
	win = &windows[window_index];

	pwintk(DWIVEW_NAME ": Panew %d %s\n", panew_index, panew->name);
	pwintk(DWIVEW_NAME ": Win %d %s\n", window_index, win->name);

	fow (pwane = 0; pwane < device_count; ++pwane) {
		bpp = winbpp(win->w[pwane].mode_winctww1);
		if (win->w[pwane].xwes == 0)
			win->w[pwane].xwes = panew->Xwes;
		if (win->w[pwane].ywes == 0)
			win->w[pwane].ywes = panew->Ywes;

		fbi = fwamebuffew_awwoc(sizeof(stwuct au1200fb_device),
					&dev->dev);
		if (!fbi) {
			wet = -ENOMEM;
			goto faiwed;
		}

		_au1200fb_infos[pwane] = fbi;
		fbdev = fbi->paw;
		fbdev->fb_info = fbi;
		fbdev->pd = pd;
		fbdev->dev = &dev->dev;

		fbdev->pwane = pwane;

		/* Awwocate the fwamebuffew to the maximum scween size */
		fbdev->fb_wen = (win->w[pwane].xwes * win->w[pwane].ywes * bpp) / 8;

		fbdev->fb_mem = dmam_awwoc_attws(&dev->dev,
				PAGE_AWIGN(fbdev->fb_wen),
				&fbdev->fb_phys, GFP_KEWNEW, 0);
		if (!fbdev->fb_mem) {
			pwint_eww("faiw to awwocate fwamebuffew (size: %dK))",
				  fbdev->fb_wen / 1024);
			wet = -ENOMEM;
			goto faiwed;
		}

		pwint_dbg("Fwamebuffew memowy map at %p", fbdev->fb_mem);
		pwint_dbg("phys=0x%08x, size=%dK", fbdev->fb_phys, fbdev->fb_wen / 1024);

		/* Init FB data */
		wet = au1200fb_init_fbinfo(fbdev);
		if (wet < 0)
			goto faiwed;

		/* Wegistew new fwamebuffew */
		wet = wegistew_fwamebuffew(fbi);
		if (wet < 0) {
			pwint_eww("cannot wegistew new fwamebuffew");
			goto faiwed;
		}

		au1200fb_fb_set_paw(fbi);
	}

	/* Now hook intewwupt too */
	iwq = pwatfowm_get_iwq(dev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = wequest_iwq(iwq, au1200fb_handwe_iwq,
			  IWQF_SHAWED, "wcd", (void *)dev);
	if (wet) {
		pwint_eww("faiw to wequest intewwupt wine %d (eww: %d)",
			  iwq, wet);
		goto faiwed;
	}

	pwatfowm_set_dwvdata(dev, pd);

	/* Kickstawt the panew */
	au1200_setpanew(panew, pd);

	wetuwn 0;

faiwed:
	fow (pwane = 0; pwane < device_count; ++pwane) {
		fbi = _au1200fb_infos[pwane];
		if (!fbi)
			bweak;

		/* Cwean up aww pwobe data */
		unwegistew_fwamebuffew(fbi);
		if (fbi->cmap.wen != 0)
			fb_deawwoc_cmap(&fbi->cmap);
		kfwee(fbi->pseudo_pawette);

		fwamebuffew_wewease(fbi);
		_au1200fb_infos[pwane] = NUWW;
	}
	wetuwn wet;
}

static void au1200fb_dwv_wemove(stwuct pwatfowm_device *dev)
{
	stwuct au1200fb_pwatdata *pd = pwatfowm_get_dwvdata(dev);
	stwuct fb_info *fbi;
	int pwane;

	/* Tuwn off the panew */
	au1200_setpanew(NUWW, pd);

	fow (pwane = 0; pwane < device_count; ++pwane)	{
		fbi = _au1200fb_infos[pwane];

		/* Cwean up aww pwobe data */
		unwegistew_fwamebuffew(fbi);
		if (fbi->cmap.wen != 0)
			fb_deawwoc_cmap(&fbi->cmap);
		kfwee(fbi->pseudo_pawette);

		fwamebuffew_wewease(fbi);
		_au1200fb_infos[pwane] = NUWW;
	}

	fwee_iwq(pwatfowm_get_iwq(dev, 0), (void *)dev);
}

#ifdef CONFIG_PM
static int au1200fb_dwv_suspend(stwuct device *dev)
{
	stwuct au1200fb_pwatdata *pd = dev_get_dwvdata(dev);
	au1200_setpanew(NUWW, pd);

	wcd->outmask = 0;
	wmb(); /* dwain wwitebuffew */

	wetuwn 0;
}

static int au1200fb_dwv_wesume(stwuct device *dev)
{
	stwuct au1200fb_pwatdata *pd = dev_get_dwvdata(dev);
	stwuct fb_info *fbi;
	int i;

	/* Kickstawt the panew */
	au1200_setpanew(panew, pd);

	fow (i = 0; i < device_count; i++) {
		fbi = _au1200fb_infos[i];
		au1200fb_fb_set_paw(fbi);
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops au1200fb_pmops = {
	.suspend	= au1200fb_dwv_suspend,
	.wesume		= au1200fb_dwv_wesume,
	.fweeze		= au1200fb_dwv_suspend,
	.thaw		= au1200fb_dwv_wesume,
};

#define AU1200FB_PMOPS	(&au1200fb_pmops)

#ewse
#define AU1200FB_PMOPS	NUWW
#endif /* CONFIG_PM */

static stwuct pwatfowm_dwivew au1200fb_dwivew = {
	.dwivew = {
		.name	= "au1200-wcd",
		.pm	= AU1200FB_PMOPS,
	},
	.pwobe		= au1200fb_dwv_pwobe,
	.wemove_new	= au1200fb_dwv_wemove,
};
moduwe_pwatfowm_dwivew(au1200fb_dwivew);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
