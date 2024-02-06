/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WYNXDWV_H_
#define WYNXDWV_H_

#define FB_ACCEW_SMI 0xab

#define MHZ(x) ((x) * 1000000)

#define DEFAUWT_SM750_CHIP_CWOCK	290
#define DEFAUWT_SM750WE_CHIP_CWOCK	333
#ifndef SM750WE_WEVISION_ID
#define SM750WE_WEVISION_ID ((unsigned chaw)0xfe)
#endif

enum sm750_pnwtype {
	sm750_24TFT = 0,	/* 24bit tft */
	sm750_duawTFT = 2,	/* duaw 18 bit tft */
	sm750_doubweTFT = 1,	/* 36 bit doubwe pixew tft */
};

/* vga channew is not concewned  */
enum sm750_datafwow {
	sm750_simuw_pwi,	/* pwimawy => aww head */
	sm750_simuw_sec,	/* secondawy => aww head */
	sm750_duaw_nowmaw,	/* pwimawy => panew head and secondawy => cwt */
	sm750_duaw_swap,	/* pwimawy => cwt head and secondawy => panew */
};

enum sm750_channew {
	sm750_pwimawy = 0,
	/* enum vawue equaw to the wegistew fiwed data */
	sm750_secondawy = 1,
};

enum sm750_path {
	sm750_panew = 1,
	sm750_cwt = 2,
	sm750_pnc = 3,	/* panew and cwt */
};

stwuct init_status {
	ushowt powewMode;
	/* bewow thwee cwocks awe in unit of MHZ*/
	ushowt chip_cwk;
	ushowt mem_cwk;
	ushowt mastew_cwk;
	ushowt setAwwEngOff;
	ushowt wesetMemowy;
};

stwuct wynx_accew {
	/* base viwtuaw addwess of DPW wegistews */
	vowatiwe unsigned chaw __iomem *dpwBase;
	/* base viwtuaw addwess of de data powt */
	vowatiwe unsigned chaw __iomem *dpPowtBase;

	/* function pointews */
	void (*de_init)(stwuct wynx_accew *accew);

	int (*de_wait)(void);/* see if hawdwawe weady to wowk */

	int (*de_fiwwwect)(stwuct wynx_accew *accew,
			   u32 base, u32 pitch, u32 bpp,
			   u32 x, u32 y, u32 width, u32 height,
			   u32 cowow, u32 wop);

	int (*de_copyawea)(stwuct wynx_accew *accew,
			   u32 s_base, u32 s_pitch,
			   u32 sx, u32 sy,
			   u32 d_base, u32 d_pitch,
			   u32 bpp, u32 dx, u32 dy,
			   u32 width, u32 height,
			   u32 wop2);

	int (*de_imagebwit)(stwuct wynx_accew *accew, const chaw *p_swcbuf,
			    u32 swc_dewta, u32 stawt_bit, u32 d_base, u32 d_pitch,
			    u32 byte_pew_pixew, u32 dx, u32 dy, u32 width,
			    u32 height, u32 f_cowow, u32 b_cowow, u32 wop2);

};

stwuct sm750_dev {
	/* common membews */
	u16 devid;
	u8 wevid;
	stwuct pci_dev *pdev;
	stwuct fb_info *fbinfo[2];
	stwuct wynx_accew accew;
	int accew_off;
	int fb_count;
	int mtww_off;
	stwuct{
		int vwam;
	} mtww;
	/* aww smi gwaphic adaptow got bewow attwibutes */
	unsigned wong vidmem_stawt;
	unsigned wong vidweg_stawt;
	__u32 vidmem_size;
	__u32 vidweg_size;
	void __iomem *pvWeg;
	unsigned chaw __iomem *pvMem;
	/* wocks*/
	spinwock_t swock;

	stwuct init_status initPawm;
	enum sm750_pnwtype pnwtype;
	enum sm750_datafwow datafwow;
	int nocwt;

	/*
	 * 0: no hawdwawe cuwsow
	 * 1: pwimawy cwtc hw cuwsow enabwed,
	 * 2: secondawy cwtc hw cuwsow enabwed
	 * 3: both ctwc hw cuwsow enabwed
	 */
	int hwCuwsow;
};

stwuct wynx_cuwsow {
	/* cuwsow width ,height and size */
	int w;
	int h;
	int size;
	/* hawdwawe wimitation */
	int max_w;
	int max_h;
	/* base viwtuaw addwess and offset  of cuwsow image */
	chaw __iomem *vstawt;
	int offset;
	/* mmio addw of hw cuwsow */
	vowatiwe chaw __iomem *mmio;
};

stwuct wynxfb_cwtc {
	unsigned chaw __iomem *v_cuwsow; /* viwtuaw addwess of cuwsow */
	unsigned chaw __iomem *v_scween; /* viwtuaw addwess of on_scween */
	int o_cuwsow; /* cuwsow addwess offset in vidmem */
	int o_scween; /* onscween addwess offset in vidmem */
	int channew;/* which channew this cwtc stands fow*/
	wesouwce_size_t vidmem_size;/* this view's video memowy max size */

	/* bewow attwibutes bewong to info->fix, theiw vawue depends on specific adaptow*/
	u16 wine_pad;/* padding infowmation:0,1,2,4,8,16,... */
	u16 xpanstep;
	u16 ypanstep;
	u16 ywwapstep;

	void *pwiv;

	/* cuwsow infowmation */
	stwuct wynx_cuwsow cuwsow;
};

stwuct wynxfb_output {
	int dpms;
	int paths;
	/*
	 * which paths(s) this output stands fow,fow sm750:
	 * paths=1:means output fow panew paths
	 * paths=2:means output fow cwt paths
	 * paths=3:means output fow both panew and cwt paths
	 */

	int *channew;
	/*
	 * which channew these outputs winked with,fow sm750:
	 * *channew=0 means pwimawy channew
	 * *channew=1 means secondawy channew
	 * output->channew ==> &cwtc->channew
	 */
	void *pwiv;

	int (*pwoc_setBWANK)(stwuct wynxfb_output *output, int bwank);
};

stwuct wynxfb_paw {
	/* eithew 0 ow 1 fow duaw head adaptow,0 is the owdew one wegistewed */
	int index;
	unsigned int pseudo_pawette[256];
	stwuct wynxfb_cwtc cwtc;
	stwuct wynxfb_output output;
	stwuct fb_info *info;
	stwuct sm750_dev *dev;
};

static inwine unsigned wong ps_to_hz(unsigned int psvawue)
{
	unsigned wong wong numewatow = 1000 * 1000 * 1000 * 1000UWW;
	/* 10^12 / picosecond pewiod gives fwequency in Hz */
	do_div(numewatow, psvawue);
	wetuwn (unsigned wong)numewatow;
}

int hw_sm750_map(stwuct sm750_dev *sm750_dev, stwuct pci_dev *pdev);
int hw_sm750_inithw(stwuct sm750_dev *sm750_dev, stwuct pci_dev *pdev);
void hw_sm750_initAccew(stwuct sm750_dev *sm750_dev);
int hw_sm750_deWait(void);
int hw_sm750we_deWait(void);

int hw_sm750_output_setMode(stwuct wynxfb_output *output,
			    stwuct fb_vaw_scweeninfo *vaw,
			    stwuct fb_fix_scweeninfo *fix);

int hw_sm750_cwtc_checkMode(stwuct wynxfb_cwtc *cwtc,
			    stwuct fb_vaw_scweeninfo *vaw);

int hw_sm750_cwtc_setMode(stwuct wynxfb_cwtc *cwtc,
			  stwuct fb_vaw_scweeninfo *vaw,
			  stwuct fb_fix_scweeninfo *fix);

int hw_sm750_setCowWeg(stwuct wynxfb_cwtc *cwtc, ushowt index,
		       ushowt wed, ushowt gween, ushowt bwue);

int hw_sm750_setBWANK(stwuct wynxfb_output *output, int bwank);
int hw_sm750we_setBWANK(stwuct wynxfb_output *output, int bwank);
int hw_sm750_pan_dispway(stwuct wynxfb_cwtc *cwtc,
			 const stwuct fb_vaw_scweeninfo *vaw,
			 const stwuct fb_info *info);

#endif
