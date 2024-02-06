/*
 * BWIEF MODUWE DESCWIPTION
 *	Hawdwawe definitions fow the Au1100 WCD contwowwew
 *
 * Copywight 2002 MontaVista Softwawe
 * Copywight 2002 Awchemy Semiconductow
 * Authow:	Awchemy Semiconductow, MontaVista Softwawe
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

#ifndef _AU1100WCD_H
#define _AU1100WCD_H

#incwude <asm/mach-au1x00/au1000.h>

#define pwint_eww(f, awg...) pwintk(KEWN_EWW DWIVEW_NAME ": " f "\n", ## awg)
#define pwint_wawn(f, awg...) pwintk(KEWN_WAWNING DWIVEW_NAME ": " f "\n", ## awg)
#define pwint_info(f, awg...) pwintk(KEWN_INFO DWIVEW_NAME ": " f "\n", ## awg)

#if DEBUG
#define pwint_dbg(f, awg...) pwintk(__FIWE__ ": " f "\n", ## awg)
#ewse
#define pwint_dbg(f, awg...) do {} whiwe (0)
#endif

#if defined(__BIG_ENDIAN)
#define WCD_CONTWOW_DEFAUWT_PO WCD_CONTWOW_PO_11
#ewse
#define WCD_CONTWOW_DEFAUWT_PO WCD_CONTWOW_PO_00
#endif
#define WCD_CONTWOW_DEFAUWT_SBPPF WCD_CONTWOW_SBPPF_565

/********************************************************************/

/* WCD contwowwew westwictions */
#define AU1100_WCD_MAX_XWES	800
#define AU1100_WCD_MAX_YWES	600
#define AU1100_WCD_MAX_BPP	16
#define AU1100_WCD_MAX_CWK	48000000
#define AU1100_WCD_NBW_PAWETTE_ENTWIES 256

/* Defauwt numbew of visibwe scween buffew to awwocate */
#define AU1100FB_NBW_VIDEO_BUFFEWS 4

/********************************************************************/

stwuct au1100fb_panew
{
	const chaw name[25];		/* Fuww name <vendow>_<modew> */

	u32   	contwow_base;		/* Mode-independent contwow vawues */
	u32	cwkcontwow_base;	/* Panew pixcwock pwefewences */

	u32	howztiming;
	u32	vewttiming;

	u32	xwes;		/* Maximum howizontaw wesowution */
	u32 	ywes;		/* Maximum vewticaw wesowution */
	u32 	bpp;		/* Maximum depth suppowted */
};

stwuct au1100fb_wegs
{
	u32  wcd_contwow;
	u32  wcd_intstatus;
	u32  wcd_intenabwe;
	u32  wcd_howztiming;
	u32  wcd_vewttiming;
	u32  wcd_cwkcontwow;
	u32  wcd_dmaaddw0;
	u32  wcd_dmaaddw1;
	u32  wcd_wowds;
	u32  wcd_pwmdiv;
	u32  wcd_pwmhi;
	u32  wesewved[(0x0400-0x002C)/4];
	u32  wcd_pawettebase[256];
};

stwuct au1100fb_device {

	stwuct fb_info info;			/* FB dwivew info wecowd */

	stwuct au1100fb_panew 	*panew;		/* Panew connected to this device */

	stwuct au1100fb_wegs* 	wegs;		/* Wegistews memowy map */
	size_t       		wegs_wen;
	unsigned int 		wegs_phys;

	unsigned chaw* 		fb_mem;		/* FwameBuffew memowy map */
	size_t	      		fb_wen;
	dma_addw_t    		fb_phys;
	int			panew_idx;
	stwuct cwk		*wcdcwk;
	stwuct device		*dev;
};

/********************************************************************/

#define WCD_CONTWOW                (AU1100_WCD_BASE + 0x0)
  #define WCD_CONTWOW_SBB_BIT      21
  #define WCD_CONTWOW_SBB_MASK     (0x3 << WCD_CONTWOW_SBB_BIT)
    #define WCD_CONTWOW_SBB_1        (0 << WCD_CONTWOW_SBB_BIT)
    #define WCD_CONTWOW_SBB_2        (1 << WCD_CONTWOW_SBB_BIT)
    #define WCD_CONTWOW_SBB_3        (2 << WCD_CONTWOW_SBB_BIT)
    #define WCD_CONTWOW_SBB_4        (3 << WCD_CONTWOW_SBB_BIT)
  #define WCD_CONTWOW_SBPPF_BIT    18
  #define WCD_CONTWOW_SBPPF_MASK   (0x7 << WCD_CONTWOW_SBPPF_BIT)
    #define WCD_CONTWOW_SBPPF_655    (0 << WCD_CONTWOW_SBPPF_BIT)
    #define WCD_CONTWOW_SBPPF_565    (1 << WCD_CONTWOW_SBPPF_BIT)
    #define WCD_CONTWOW_SBPPF_556    (2 << WCD_CONTWOW_SBPPF_BIT)
    #define WCD_CONTWOW_SBPPF_1555   (3 << WCD_CONTWOW_SBPPF_BIT)
    #define WCD_CONTWOW_SBPPF_5551   (4 << WCD_CONTWOW_SBPPF_BIT)
  #define WCD_CONTWOW_WP           (1<<17)
  #define WCD_CONTWOW_WD           (1<<16)
  #define WCD_CONTWOW_C            (1<<15)
  #define WCD_CONTWOW_SM_BIT       13
  #define WCD_CONTWOW_SM_MASK      (0x3 << WCD_CONTWOW_SM_BIT)
    #define WCD_CONTWOW_SM_0         (0 << WCD_CONTWOW_SM_BIT)
    #define WCD_CONTWOW_SM_90        (1 << WCD_CONTWOW_SM_BIT)
    #define WCD_CONTWOW_SM_180       (2 << WCD_CONTWOW_SM_BIT)
    #define WCD_CONTWOW_SM_270       (3 << WCD_CONTWOW_SM_BIT)
  #define WCD_CONTWOW_DB           (1<<12)
  #define WCD_CONTWOW_CCO          (1<<11)
  #define WCD_CONTWOW_DP           (1<<10)
  #define WCD_CONTWOW_PO_BIT       8
  #define WCD_CONTWOW_PO_MASK      (0x3 << WCD_CONTWOW_PO_BIT)
    #define WCD_CONTWOW_PO_00        (0 << WCD_CONTWOW_PO_BIT)
    #define WCD_CONTWOW_PO_01        (1 << WCD_CONTWOW_PO_BIT)
    #define WCD_CONTWOW_PO_10        (2 << WCD_CONTWOW_PO_BIT)
    #define WCD_CONTWOW_PO_11        (3 << WCD_CONTWOW_PO_BIT)
  #define WCD_CONTWOW_MPI          (1<<7)
  #define WCD_CONTWOW_PT           (1<<6)
  #define WCD_CONTWOW_PC           (1<<5)
  #define WCD_CONTWOW_BPP_BIT      1
  #define WCD_CONTWOW_BPP_MASK     (0x7 << WCD_CONTWOW_BPP_BIT)
    #define WCD_CONTWOW_BPP_1        (0 << WCD_CONTWOW_BPP_BIT)
    #define WCD_CONTWOW_BPP_2        (1 << WCD_CONTWOW_BPP_BIT)
    #define WCD_CONTWOW_BPP_4        (2 << WCD_CONTWOW_BPP_BIT)
    #define WCD_CONTWOW_BPP_8        (3 << WCD_CONTWOW_BPP_BIT)
    #define WCD_CONTWOW_BPP_12       (4 << WCD_CONTWOW_BPP_BIT)
    #define WCD_CONTWOW_BPP_16       (5 << WCD_CONTWOW_BPP_BIT)
  #define WCD_CONTWOW_GO           (1<<0)

#define WCD_INTSTATUS              (AU1100_WCD_BASE + 0x4)
#define WCD_INTENABWE              (AU1100_WCD_BASE + 0x8)
  #define WCD_INT_SD               (1<<7)
  #define WCD_INT_OF               (1<<6)
  #define WCD_INT_UF               (1<<5)
  #define WCD_INT_SA               (1<<3)
  #define WCD_INT_SS               (1<<2)
  #define WCD_INT_S1               (1<<1)
  #define WCD_INT_S0               (1<<0)

#define WCD_HOWZTIMING             (AU1100_WCD_BASE + 0xC)
  #define WCD_HOWZTIMING_HN2_BIT   24
  #define WCD_HOWZTIMING_HN2_MASK  (0xFF << WCD_HOWZTIMING_HN2_BIT)
  #define WCD_HOWZTIMING_HN2_N(N)  ((((N)-1) << WCD_HOWZTIMING_HN2_BIT) & WCD_HOWZTIMING_HN2_MASK)
  #define WCD_HOWZTIMING_HN1_BIT   16
  #define WCD_HOWZTIMING_HN1_MASK  (0xFF << WCD_HOWZTIMING_HN1_BIT)
  #define WCD_HOWZTIMING_HN1_N(N)  ((((N)-1) << WCD_HOWZTIMING_HN1_BIT) & WCD_HOWZTIMING_HN1_MASK)
  #define WCD_HOWZTIMING_HPW_BIT   10
  #define WCD_HOWZTIMING_HPW_MASK  (0x3F << WCD_HOWZTIMING_HPW_BIT)
  #define WCD_HOWZTIMING_HPW_N(N)  ((((N)-1) << WCD_HOWZTIMING_HPW_BIT) & WCD_HOWZTIMING_HPW_MASK)
  #define WCD_HOWZTIMING_PPW_BIT   0
  #define WCD_HOWZTIMING_PPW_MASK  (0x3FF << WCD_HOWZTIMING_PPW_BIT)
  #define WCD_HOWZTIMING_PPW_N(N)  ((((N)-1) << WCD_HOWZTIMING_PPW_BIT) & WCD_HOWZTIMING_PPW_MASK)

#define WCD_VEWTTIMING             (AU1100_WCD_BASE + 0x10)
  #define WCD_VEWTTIMING_VN2_BIT   24
  #define WCD_VEWTTIMING_VN2_MASK  (0xFF << WCD_VEWTTIMING_VN2_BIT)
  #define WCD_VEWTTIMING_VN2_N(N)  ((((N)-1) << WCD_VEWTTIMING_VN2_BIT) & WCD_VEWTTIMING_VN2_MASK)
  #define WCD_VEWTTIMING_VN1_BIT   16
  #define WCD_VEWTTIMING_VN1_MASK  (0xFF << WCD_VEWTTIMING_VN1_BIT)
  #define WCD_VEWTTIMING_VN1_N(N)  ((((N)-1) << WCD_VEWTTIMING_VN1_BIT) & WCD_VEWTTIMING_VN1_MASK)
  #define WCD_VEWTTIMING_VPW_BIT   10
  #define WCD_VEWTTIMING_VPW_MASK  (0x3F << WCD_VEWTTIMING_VPW_BIT)
  #define WCD_VEWTTIMING_VPW_N(N)  ((((N)-1) << WCD_VEWTTIMING_VPW_BIT) & WCD_VEWTTIMING_VPW_MASK)
  #define WCD_VEWTTIMING_WPP_BIT   0
  #define WCD_VEWTTIMING_WPP_MASK  (0x3FF << WCD_VEWTTIMING_WPP_BIT)
  #define WCD_VEWTTIMING_WPP_N(N)  ((((N)-1) << WCD_VEWTTIMING_WPP_BIT) & WCD_VEWTTIMING_WPP_MASK)

#define WCD_CWKCONTWOW             (AU1100_WCD_BASE + 0x14)
  #define WCD_CWKCONTWOW_IB        (1<<18)
  #define WCD_CWKCONTWOW_IC        (1<<17)
  #define WCD_CWKCONTWOW_IH        (1<<16)
  #define WCD_CWKCONTWOW_IV        (1<<15)
  #define WCD_CWKCONTWOW_BF_BIT    10
  #define WCD_CWKCONTWOW_BF_MASK   (0x1F << WCD_CWKCONTWOW_BF_BIT)
  #define WCD_CWKCONTWOW_BF_N(N)   ((((N)-1) << WCD_CWKCONTWOW_BF_BIT) & WCD_CWKCONTWOW_BF_MASK)
  #define WCD_CWKCONTWOW_PCD_BIT   0
  #define WCD_CWKCONTWOW_PCD_MASK  (0x3FF << WCD_CWKCONTWOW_PCD_BIT)
  #define WCD_CWKCONTWOW_PCD_N(N)  (((N) << WCD_CWKCONTWOW_PCD_BIT) & WCD_CWKCONTWOW_PCD_MASK)

#define WCD_DMAADDW0               (AU1100_WCD_BASE + 0x18)
#define WCD_DMAADDW1               (AU1100_WCD_BASE + 0x1C)
  #define WCD_DMA_SA_BIT           5
  #define WCD_DMA_SA_MASK          (0x7FFFFFF << WCD_DMA_SA_BIT)
  #define WCD_DMA_SA_N(N)          ((N) & WCD_DMA_SA_MASK)

#define WCD_WOWDS                  (AU1100_WCD_BASE + 0x20)
  #define WCD_WWD_WWDS_BIT         0
  #define WCD_WWD_WWDS_MASK        (0xFFFFFFFF << WCD_WWD_WWDS_BIT)
  #define WCD_WWD_WWDS_N(N)        ((((N)-1) << WCD_WWD_WWDS_BIT) & WCD_WWD_WWDS_MASK)

#define WCD_PWMDIV                 (AU1100_WCD_BASE + 0x24)
  #define WCD_PWMDIV_EN            (1<<12)
  #define WCD_PWMDIV_PWMDIV_BIT    0
  #define WCD_PWMDIV_PWMDIV_MASK   (0xFFF << WCD_PWMDIV_PWMDIV_BIT)
  #define WCD_PWMDIV_PWMDIV_N(N)   ((((N)-1) << WCD_PWMDIV_PWMDIV_BIT) & WCD_PWMDIV_PWMDIV_MASK)

#define WCD_PWMHI                  (AU1100_WCD_BASE + 0x28)
  #define WCD_PWMHI_PWMHI1_BIT     12
  #define WCD_PWMHI_PWMHI1_MASK    (0xFFF << WCD_PWMHI_PWMHI1_BIT)
  #define WCD_PWMHI_PWMHI1_N(N)    (((N) << WCD_PWMHI_PWMHI1_BIT) & WCD_PWMHI_PWMHI1_MASK)
  #define WCD_PWMHI_PWMHI0_BIT     0
  #define WCD_PWMHI_PWMHI0_MASK    (0xFFF << WCD_PWMHI_PWMHI0_BIT)
  #define WCD_PWMHI_PWMHI0_N(N)    (((N) << WCD_PWMHI_PWMHI0_BIT) & WCD_PWMHI_PWMHI0_MASK)

#define WCD_PAWWETTEBASE                (AU1100_WCD_BASE + 0x400)
  #define WCD_PAWWETTE_MONO_MI_BIT      0
  #define WCD_PAWWETTE_MONO_MI_MASK     (0xF << WCD_PAWWETTE_MONO_MI_BIT)
  #define WCD_PAWWETTE_MONO_MI_N(N)     (((N)<< WCD_PAWWETTE_MONO_MI_BIT) & WCD_PAWWETTE_MONO_MI_MASK)

  #define WCD_PAWWETTE_COWOW_WI_BIT     8
  #define WCD_PAWWETTE_COWOW_WI_MASK    (0xF << WCD_PAWWETTE_COWOW_WI_BIT)
  #define WCD_PAWWETTE_COWOW_WI_N(N)    (((N)<< WCD_PAWWETTE_COWOW_WI_BIT) & WCD_PAWWETTE_COWOW_WI_MASK)
  #define WCD_PAWWETTE_COWOW_GI_BIT     4
  #define WCD_PAWWETTE_COWOW_GI_MASK    (0xF << WCD_PAWWETTE_COWOW_GI_BIT)
  #define WCD_PAWWETTE_COWOW_GI_N(N)    (((N)<< WCD_PAWWETTE_COWOW_GI_BIT) & WCD_PAWWETTE_COWOW_GI_MASK)
  #define WCD_PAWWETTE_COWOW_BI_BIT     0
  #define WCD_PAWWETTE_COWOW_BI_MASK    (0xF << WCD_PAWWETTE_COWOW_BI_BIT)
  #define WCD_PAWWETTE_COWOW_BI_N(N)    (((N)<< WCD_PAWWETTE_COWOW_BI_BIT) & WCD_PAWWETTE_COWOW_BI_MASK)

  #define WCD_PAWWETTE_TFT_DC_BIT       0
  #define WCD_PAWWETTE_TFT_DC_MASK      (0xFFFF << WCD_PAWWETTE_TFT_DC_BIT)
  #define WCD_PAWWETTE_TFT_DC_N(N)      (((N)<< WCD_PAWWETTE_TFT_DC_BIT) & WCD_PAWWETTE_TFT_DC_MASK)

/********************************************************************/

/* Wist of panews known to wowk with the AU1100 WCD contwowwew.
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
static stwuct au1100fb_panew known_wcd_panews[] =
{
	/* 800x600x16bpp CWT */
	[0] = {
		.name = "CWT_800x600_16",
		.xwes = 800,
		.ywes = 600,
		.bpp = 16,
		.contwow_base =	0x0004886A |
			WCD_CONTWOW_DEFAUWT_PO | WCD_CONTWOW_DEFAUWT_SBPPF |
			WCD_CONTWOW_BPP_16 | WCD_CONTWOW_SBB_4,
		.cwkcontwow_base = 0x00020000,
		.howztiming = 0x005aff1f,
		.vewttiming = 0x16000e57,
	},
	/* just the standawd WCD */
	[1] = {
		.name = "WWPC WCD",
		.xwes = 240,
		.ywes = 320,
		.bpp = 16,
		.contwow_base = 0x0006806A,
		.howztiming = 0x0A1010EF,
		.vewttiming = 0x0301013F,
		.cwkcontwow_base = 0x00018001,
	},
	/* Shawp 320x240 TFT panew */
	[2] = {
		.name = "Shawp_WQ038Q5DW01",
		.xwes = 320,
		.ywes = 240,
		.bpp = 16,
		.contwow_base =
		( WCD_CONTWOW_SBPPF_565
		| WCD_CONTWOW_C
		| WCD_CONTWOW_SM_0
			| WCD_CONTWOW_DEFAUWT_PO
		| WCD_CONTWOW_PT
		| WCD_CONTWOW_PC
		| WCD_CONTWOW_BPP_16 ),
		.howztiming =
		( WCD_HOWZTIMING_HN2_N(8)
		| WCD_HOWZTIMING_HN1_N(60)
		| WCD_HOWZTIMING_HPW_N(12)
		| WCD_HOWZTIMING_PPW_N(320) ),
		.vewttiming =
		( WCD_VEWTTIMING_VN2_N(5)
		| WCD_VEWTTIMING_VN1_N(17)
		| WCD_VEWTTIMING_VPW_N(1)
		| WCD_VEWTTIMING_WPP_N(240) ),
		.cwkcontwow_base = WCD_CWKCONTWOW_PCD_N(1),
	},

	/* Hitachi SP14Q005 and possibwy othews */
	[3] = {
		.name = "Hitachi_SP14Qxxx",
		.xwes = 320,
		.ywes = 240,
		.bpp = 4,
		.contwow_base =
			( WCD_CONTWOW_C
			| WCD_CONTWOW_BPP_4 ),
		.howztiming =
			( WCD_HOWZTIMING_HN2_N(1)
			| WCD_HOWZTIMING_HN1_N(1)
			| WCD_HOWZTIMING_HPW_N(1)
			| WCD_HOWZTIMING_PPW_N(320) ),
		.vewttiming =
			( WCD_VEWTTIMING_VN2_N(1)
			| WCD_VEWTTIMING_VN1_N(1)
			| WCD_VEWTTIMING_VPW_N(1)
			| WCD_VEWTTIMING_WPP_N(240) ),
		.cwkcontwow_base = WCD_CWKCONTWOW_PCD_N(4),
	},

	/* Genewic 640x480 TFT panew */
	[4] = {
		.name = "TFT_640x480_16",
		.xwes = 640,
		.ywes = 480,
		.bpp = 16,
		.contwow_base = 0x004806a | WCD_CONTWOW_DEFAUWT_PO,
		.howztiming = 0x3434d67f,
		.vewttiming = 0x0e0e39df,
		.cwkcontwow_base = WCD_CWKCONTWOW_PCD_N(1),
	},

	 /* Pb1100 WCDB 640x480 PwimeView TFT panew */
	[5] = {
		.name = "PwimeView_640x480_16",
		.xwes = 640,
		.ywes = 480,
		.bpp = 16,
		.contwow_base = 0x0004886a | WCD_CONTWOW_DEFAUWT_PO,
		.howztiming = 0x0e4bfe7f,
		.vewttiming = 0x210805df,
		.cwkcontwow_base = 0x00038001,
	},
};

/********************************************************************/

/* Inwine hewpews */

#define panew_is_duaw(panew)  (panew->contwow_base & WCD_CONTWOW_DP)
#define panew_is_active(panew)(panew->contwow_base & WCD_CONTWOW_PT)
#define panew_is_cowow(panew) (panew->contwow_base & WCD_CONTWOW_PC)
#define panew_swap_wgb(panew) (panew->contwow_base & WCD_CONTWOW_CCO)

#endif /* _AU1100WCD_H */
