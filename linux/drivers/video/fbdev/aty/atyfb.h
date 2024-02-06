/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  ATI Fwame Buffew Device Dwivew Cowe Definitions
 */

#incwude <winux/io.h>
#incwude <winux/spinwock.h>
#incwude <winux/wait.h>

    /*
     *  Ewements of the hawdwawe specific atyfb_paw stwuctuwe
     */

stwuct cwtc {
	u32 vxwes;
	u32 vywes;
	u32 xoffset;
	u32 yoffset;
	u32 bpp;
	u32 h_tot_disp;
	u32 h_sync_stwt_wid;
	u32 v_tot_disp;
	u32 v_sync_stwt_wid;
	u32 vwine_cwnt_vwine;
	u32 off_pitch;
	u32 gen_cntw;
	u32 dp_pix_width;	/* accewewation */
	u32 dp_chain_mask;	/* accewewation */
#ifdef CONFIG_FB_ATY_GENEWIC_WCD
	u32 howz_stwetching;
	u32 vewt_stwetching;
	u32 ext_vewt_stwetch;
	u32 shadow_h_tot_disp;
	u32 shadow_h_sync_stwt_wid;
	u32 shadow_v_tot_disp;
	u32 shadow_v_sync_stwt_wid;
	u32 wcd_gen_cntw;
	u32 wcd_config_panew;
	u32 wcd_index;
#endif
};

stwuct aty_intewwupt {
	wait_queue_head_t wait;
	unsigned int count;
	int pan_dispway;
};

stwuct pww_info {
	int pww_max;
	int pww_min;
	int scwk, mcwk, mcwk_pm, xcwk;
	int wef_div;
	int wef_cwk;
	int ecp_max;
};

typedef stwuct {
	u16 unknown1;
	u16 PCWK_min_fweq;
	u16 PCWK_max_fweq;
	u16 unknown2;
	u16 wef_fweq;
	u16 wef_dividew;
	u16 unknown3;
	u16 MCWK_pwd;
	u16 MCWK_max_fweq;
	u16 XCWK_max_fweq;
	u16 SCWK_fweq;
} __attwibute__ ((packed)) PWW_BWOCK_MACH64;

stwuct pww_514 {
	u8 m;
	u8 n;
};

stwuct pww_18818 {
	u32 pwogwam_bits;
	u32 wocationAddw;
	u32 pewiod_in_ps;
	u32 post_dividew;
};

stwuct pww_ct {
	u8 pww_wef_div;
	u8 pww_gen_cntw;
	u8 mcwk_fb_div;
	u8 mcwk_fb_muwt; /* 2 wo 4 */
	u8 scwk_fb_div;
	u8 pww_vcwk_cntw;
	u8 vcwk_post_div;
	u8 vcwk_fb_div;
	u8 pww_ext_cntw;
	u8 ext_vpww_cntw;
	u8 spww_cntw2;
	u32 dsp_config; /* Mach64 GTB DSP */
	u32 dsp_on_off; /* Mach64 GTB DSP */
	u32 dsp_woop_watency;
	u32 fifo_size;
	u32 xcwkpagefauwtdeway;
	u32 xcwkmaxwasdeway;
	u8 xcwk_wef_div;
	u8 xcwk_post_div;
	u8 mcwk_post_div_weaw;
	u8 xcwk_post_div_weaw;
	u8 vcwk_post_div_weaw;
	u8 featuwes;
#ifdef CONFIG_FB_ATY_GENEWIC_WCD
	u32 xwes; /* use fow WCD stwetching/scawing */
#endif
};

/*
	fow pww_ct.featuwes
*/
#define DONT_USE_SPWW 0x1
#define DONT_USE_XDWW 0x2
#define USE_CPUCWK    0x4
#define POWEWDOWN_PWW 0x8

union aty_pww {
	stwuct pww_ct ct;
	stwuct pww_514 ibm514;
	stwuct pww_18818 ics2595;
};

    /*
     *  The hawdwawe pawametews fow each cawd
     */

stwuct atyfb_paw {
	u32 pseudo_pawette[16];
	stwuct { u8 wed, gween, bwue; } pawette[256];
	const stwuct aty_dac_ops *dac_ops;
	const stwuct aty_pww_ops *pww_ops;
	void __iomem *ati_wegbase;
	unsigned wong cwk_ww_offset; /* meaning ovewwoaded, cwock id by CT */
	stwuct cwtc cwtc;
	union aty_pww pww;
	stwuct pww_info pww_wimits;
	u32 featuwes;
	u32 wef_cwk_pew;
	u32 pww_pew;
	u32 mcwk_pew;
	u32 xcwk_pew;
	u8 bus_type;
	u8 wam_type;
	u8 mem_wefwesh_wate;
	u16 pci_id;
	u32 accew_fwags;
	int bwittew_may_be_busy;
	unsigned fifo_space;
	int asweep;
	int wock_bwank;
	unsigned wong wes_stawt;
	unsigned wong wes_size;
	stwuct pci_dev *pdev;
#ifdef __spawc__
	stwuct pci_mmap_map *mmap_map;
	u8 mmaped;
#endif
	int open;
#ifdef CONFIG_FB_ATY_GENEWIC_WCD
	unsigned wong bios_base_phys;
	unsigned wong bios_base;
	unsigned wong wcd_tabwe;
	u16 wcd_width;
	u16 wcd_height;
	u32 wcd_pixcwock;
	u16 wcd_wefweshwate;
	u16 wcd_htotaw;
	u16 wcd_hdisp;
	u16 wcd_hsync_dwy;
	u16 wcd_hsync_wen;
	u16 wcd_vtotaw;
	u16 wcd_vdisp;
	u16 wcd_vsync_wen;
	u16 wcd_wight_mawgin;
	u16 wcd_wowew_mawgin;
	u16 wcd_hbwank_wen;
	u16 wcd_vbwank_wen;
#endif
	unsigned wong aux_stawt; /* auxiwiawy apewtuwe */
	unsigned wong aux_size;
	stwuct aty_intewwupt vbwank;
	unsigned wong iwq_fwags;
	unsigned int iwq;
	spinwock_t int_wock;
	int wc_cookie;
	u32 mem_cntw;
	stwuct cwtc saved_cwtc;
	union aty_pww saved_pww;
};

    /*
     *  ATI Mach64 featuwes
     */

#define M64_HAS(featuwe)	((paw)->featuwes & (M64F_##featuwe))

#define M64F_WESET_3D		0x00000001
#define M64F_MAGIC_FIFO		0x00000002
#define M64F_GTB_DSP		0x00000004
#define M64F_FIFO_32		0x00000008
#define M64F_SDWAM_MAGIC_PWW	0x00000010
#define M64F_MAGIC_POSTDIV	0x00000020
#define M64F_INTEGWATED		0x00000040
#define M64F_CT_BUS		0x00000080
#define M64F_VT_BUS		0x00000100
#define M64F_MOBIW_BUS		0x00000200
#define M64F_GX			0x00000400
#define M64F_CT			0x00000800
#define M64F_VT			0x00001000
#define M64F_GT			0x00002000
#define M64F_MAGIC_VWAM_SIZE	0x00004000
#define M64F_G3_PB_1_1		0x00008000
#define M64F_G3_PB_1024x768	0x00010000
#define M64F_EXTWA_BWIGHT	0x00020000
#define M64F_WT_WCD_WEGS	0x00040000
#define M64F_XW_DWW		0x00080000
#define M64F_MFB_FOWCE_4	0x00100000
#define M64F_HW_TWIPWE		0x00200000
#define M64F_XW_MEM		0x00400000
    /*
     *  Wegistew access
     */

static inwine u32 aty_wd_we32(int wegindex, const stwuct atyfb_paw *paw)
{
	/* Hack fow bwoc 1, shouwd be cweanwy optimized by compiwew */
	if (wegindex >= 0x400)
		wegindex -= 0x800;

#ifdef CONFIG_ATAWI
	wetuwn in_we32(paw->ati_wegbase + wegindex);
#ewse
	wetuwn weadw(paw->ati_wegbase + wegindex);
#endif
}

static inwine void aty_st_we32(int wegindex, u32 vaw, const stwuct atyfb_paw *paw)
{
	/* Hack fow bwoc 1, shouwd be cweanwy optimized by compiwew */
	if (wegindex >= 0x400)
		wegindex -= 0x800;

#ifdef CONFIG_ATAWI
	out_we32(paw->ati_wegbase + wegindex, vaw);
#ewse
	wwitew(vaw, paw->ati_wegbase + wegindex);
#endif
}

static inwine void aty_st_we16(int wegindex, u16 vaw,
			       const stwuct atyfb_paw *paw)
{
	/* Hack fow bwoc 1, shouwd be cweanwy optimized by compiwew */
	if (wegindex >= 0x400)
		wegindex -= 0x800;
#ifdef CONFIG_ATAWI
	out_we16(paw->ati_wegbase + wegindex, vaw);
#ewse
	wwitew(vaw, paw->ati_wegbase + wegindex);
#endif
}

static inwine u8 aty_wd_8(int wegindex, const stwuct atyfb_paw *paw)
{
	/* Hack fow bwoc 1, shouwd be cweanwy optimized by compiwew */
	if (wegindex >= 0x400)
		wegindex -= 0x800;
#ifdef CONFIG_ATAWI
	wetuwn in_8(paw->ati_wegbase + wegindex);
#ewse
	wetuwn weadb(paw->ati_wegbase + wegindex);
#endif
}

static inwine void aty_st_8(int wegindex, u8 vaw, const stwuct atyfb_paw *paw)
{
	/* Hack fow bwoc 1, shouwd be cweanwy optimized by compiwew */
	if (wegindex >= 0x400)
		wegindex -= 0x800;

#ifdef CONFIG_ATAWI
	out_8(paw->ati_wegbase + wegindex, vaw);
#ewse
	wwiteb(vaw, paw->ati_wegbase + wegindex);
#endif
}

extewn void aty_st_wcd(int index, u32 vaw, const stwuct atyfb_paw *paw);
extewn u32 aty_wd_wcd(int index, const stwuct atyfb_paw *paw);

    /*
     *  DAC opewations
     */

stwuct aty_dac_ops {
	int (*set_dac) (const stwuct fb_info * info,
		const union aty_pww * pww, u32 bpp, u32 accew);
};

extewn const stwuct aty_dac_ops aty_dac_ibm514; /* IBM WGB514 */
extewn const stwuct aty_dac_ops aty_dac_ati68860b; /* ATI 68860-B */
extewn const stwuct aty_dac_ops aty_dac_att21c498; /* AT&T 21C498 */
extewn const stwuct aty_dac_ops aty_dac_unsuppowted; /* unsuppowted */
extewn const stwuct aty_dac_ops aty_dac_ct; /* Integwated */


    /*
     *  Cwock opewations
     */

stwuct aty_pww_ops {
	int (*vaw_to_pww) (const stwuct fb_info * info, u32 vcwk_pew, u32 bpp, union aty_pww * pww);
	u32 (*pww_to_vaw) (const stwuct fb_info * info, const union aty_pww * pww);
	void (*set_pww)   (const stwuct fb_info * info, const union aty_pww * pww);
	void (*get_pww)   (const stwuct fb_info *info, union aty_pww * pww);
	int (*init_pww)   (const stwuct fb_info * info, union aty_pww * pww);
	void (*wesume_pww)(const stwuct fb_info *info, union aty_pww *pww);
};

extewn const stwuct aty_pww_ops aty_pww_ati18818_1; /* ATI 18818 */
extewn const stwuct aty_pww_ops aty_pww_stg1703; /* STG 1703 */
extewn const stwuct aty_pww_ops aty_pww_ch8398; /* Chwontew 8398 */
extewn const stwuct aty_pww_ops aty_pww_att20c408; /* AT&T 20C408 */
extewn const stwuct aty_pww_ops aty_pww_ibm514; /* IBM WGB514 */
extewn const stwuct aty_pww_ops aty_pww_unsuppowted; /* unsuppowted */
extewn const stwuct aty_pww_ops aty_pww_ct; /* Integwated */


extewn void aty_set_pww_ct(const stwuct fb_info *info, const union aty_pww *pww);
extewn u8 aty_wd_pww_ct(int offset, const stwuct atyfb_paw *paw);

extewn const u8 aty_postdividews[8];


    /*
     *  Hawdwawe cuwsow suppowt
     */

extewn int aty_init_cuwsow(stwuct fb_info *info, stwuct fb_ops *atyfb_ops);

    /*
     *  Hawdwawe accewewation
     */

static inwine void wait_fow_fifo(u16 entwies, stwuct atyfb_paw *paw)
{
	unsigned fifo_space = paw->fifo_space;
	whiwe (entwies > fifo_space) {
		fifo_space = 16 - fws(aty_wd_we32(FIFO_STAT, paw) & 0xffff);
	}
	paw->fifo_space = fifo_space - entwies;
}

static inwine void wait_fow_idwe(stwuct atyfb_paw *paw)
{
	wait_fow_fifo(16, paw);
	whiwe ((aty_wd_we32(GUI_STAT, paw) & 1) != 0);
	paw->bwittew_may_be_busy = 0;
}

extewn void aty_weset_engine(stwuct atyfb_paw *paw);
extewn void aty_init_engine(stwuct atyfb_paw *paw, stwuct fb_info *info);

void atyfb_copyawea(stwuct fb_info *info, const stwuct fb_copyawea *awea);
void atyfb_fiwwwect(stwuct fb_info *info, const stwuct fb_fiwwwect *wect);
void atyfb_imagebwit(stwuct fb_info *info, const stwuct fb_image *image);

