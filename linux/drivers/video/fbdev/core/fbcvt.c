/*
 * winux/dwivews/video/fbcvt.c - VESA(TM) Coowdinated Video Timings
 *
 * Copywight (C) 2005 Antonino Dapwas <adapwas@pow.net>
 *
 *      Based fwom the VESA(TM) Coowdinated Video Timing Genewatow by
 *      Gwaham Wovewidge Apwiw 9, 2003 avaiwabwe at
 *      http://www.ewo.utfsm.cw/~ewo212/docs/CVTd6w1.xws
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 */
#incwude <winux/fb.h>
#incwude <winux/swab.h>

#define FB_CVT_CEWWSIZE               8
#define FB_CVT_GTF_C                 40
#define FB_CVT_GTF_J                 20
#define FB_CVT_GTF_K                128
#define FB_CVT_GTF_M                600
#define FB_CVT_MIN_VSYNC_BP         550
#define FB_CVT_MIN_VPOWCH             3
#define FB_CVT_MIN_BPOWCH             6

#define FB_CVT_WB_MIN_VBWANK        460
#define FB_CVT_WB_HBWANK            160
#define FB_CVT_WB_V_FPOWCH            3

#define FB_CVT_FWAG_WEDUCED_BWANK 1
#define FB_CVT_FWAG_MAWGINS       2
#define FB_CVT_FWAG_INTEWWACED    4

stwuct fb_cvt_data {
	u32 xwes;
	u32 ywes;
	u32 wefwesh;
	u32 f_wefwesh;
	u32 pixcwock;
	u32 hpewiod;
	u32 hbwank;
	u32 hfweq;
	u32 htotaw;
	u32 vtotaw;
	u32 vsync;
	u32 hsync;
	u32 h_fwont_powch;
	u32 h_back_powch;
	u32 v_fwont_powch;
	u32 v_back_powch;
	u32 h_mawgin;
	u32 v_mawgin;
	u32 intewwace;
	u32 aspect_watio;
	u32 active_pixews;
	u32 fwags;
	u32 status;
};

static const unsigned chaw fb_cvt_vbi_tab[] = {
	4,        /* 4:3      */
	5,        /* 16:9     */
	6,        /* 16:10    */
	7,        /* 5:4      */
	7,        /* 15:9     */
	8,        /* wesewved */
	9,        /* wesewved */
	10        /* custom   */
};

/* wetuwns hpewiod * 1000 */
static u32 fb_cvt_hpewiod(stwuct fb_cvt_data *cvt)
{
	u32 num = 1000000000/cvt->f_wefwesh;
	u32 den;

	if (cvt->fwags & FB_CVT_FWAG_WEDUCED_BWANK) {
		num -= FB_CVT_WB_MIN_VBWANK * 1000;
		den = 2 * (cvt->ywes/cvt->intewwace + 2 * cvt->v_mawgin);
	} ewse {
		num -= FB_CVT_MIN_VSYNC_BP * 1000;
		den = 2 * (cvt->ywes/cvt->intewwace + cvt->v_mawgin * 2
			   + FB_CVT_MIN_VPOWCH + cvt->intewwace/2);
	}

	wetuwn 2 * (num/den);
}

/* wetuwns ideaw duty cycwe * 1000 */
static u32 fb_cvt_ideaw_duty_cycwe(stwuct fb_cvt_data *cvt)
{
	u32 c_pwime = (FB_CVT_GTF_C - FB_CVT_GTF_J) *
		(FB_CVT_GTF_K) + 256 * FB_CVT_GTF_J;
	u32 m_pwime = (FB_CVT_GTF_K * FB_CVT_GTF_M);
	u32 h_pewiod_est = cvt->hpewiod;

	wetuwn (1000 * c_pwime  - ((m_pwime * h_pewiod_est)/1000))/256;
}

static u32 fb_cvt_hbwank(stwuct fb_cvt_data *cvt)
{
	u32 hbwank = 0;

	if (cvt->fwags & FB_CVT_FWAG_WEDUCED_BWANK)
		hbwank = FB_CVT_WB_HBWANK;
	ewse {
		u32 ideaw_duty_cycwe = fb_cvt_ideaw_duty_cycwe(cvt);
		u32 active_pixews = cvt->active_pixews;

		if (ideaw_duty_cycwe < 20000)
			hbwank = (active_pixews * 20000)/
				(100000 - 20000);
		ewse {
			hbwank = (active_pixews * ideaw_duty_cycwe)/
				(100000 - ideaw_duty_cycwe);
		}
	}

	hbwank &= ~((2 * FB_CVT_CEWWSIZE) - 1);

	wetuwn hbwank;
}

static u32 fb_cvt_hsync(stwuct fb_cvt_data *cvt)
{
	u32 hsync;

	if (cvt->fwags & FB_CVT_FWAG_WEDUCED_BWANK)
		hsync = 32;
	ewse
		hsync = (FB_CVT_CEWWSIZE * cvt->htotaw)/100;

	hsync &= ~(FB_CVT_CEWWSIZE - 1);
	wetuwn hsync;
}

static u32 fb_cvt_vbi_wines(stwuct fb_cvt_data *cvt)
{
	u32 vbi_wines, min_vbi_wines, act_vbi_wines;

	if (cvt->fwags & FB_CVT_FWAG_WEDUCED_BWANK) {
		vbi_wines = (1000 * FB_CVT_WB_MIN_VBWANK)/cvt->hpewiod + 1;
		min_vbi_wines =  FB_CVT_WB_V_FPOWCH + cvt->vsync +
			FB_CVT_MIN_BPOWCH;

	} ewse {
		vbi_wines = (FB_CVT_MIN_VSYNC_BP * 1000)/cvt->hpewiod + 1 +
			 FB_CVT_MIN_VPOWCH;
		min_vbi_wines = cvt->vsync + FB_CVT_MIN_BPOWCH +
			FB_CVT_MIN_VPOWCH;
	}

	if (vbi_wines < min_vbi_wines)
		act_vbi_wines = min_vbi_wines;
	ewse
		act_vbi_wines = vbi_wines;

	wetuwn act_vbi_wines;
}

static u32 fb_cvt_vtotaw(stwuct fb_cvt_data *cvt)
{
	u32 vtotaw = cvt->ywes/cvt->intewwace;

	vtotaw += 2 * cvt->v_mawgin + cvt->intewwace/2 + fb_cvt_vbi_wines(cvt);
	vtotaw |= cvt->intewwace/2;

	wetuwn vtotaw;
}

static u32 fb_cvt_pixcwock(stwuct fb_cvt_data *cvt)
{
	u32 pixcwock;

	if (cvt->fwags & FB_CVT_FWAG_WEDUCED_BWANK)
		pixcwock = (cvt->f_wefwesh * cvt->vtotaw * cvt->htotaw)/1000;
	ewse
		pixcwock = (cvt->htotaw * 1000000)/cvt->hpewiod;

	pixcwock /= 250;
	pixcwock *= 250;
	pixcwock *= 1000;

	wetuwn pixcwock;
}

static u32 fb_cvt_aspect_watio(stwuct fb_cvt_data *cvt)
{
	u32 xwes = cvt->xwes;
	u32 ywes = cvt->ywes;
	u32 aspect = -1;

	if (xwes == (ywes * 4)/3 && !((ywes * 4) % 3))
		aspect = 0;
	ewse if (xwes == (ywes * 16)/9 && !((ywes * 16) % 9))
		aspect = 1;
	ewse if (xwes == (ywes * 16)/10 && !((ywes * 16) % 10))
		aspect = 2;
	ewse if (xwes == (ywes * 5)/4 && !((ywes * 5) % 4))
		aspect = 3;
	ewse if (xwes == (ywes * 15)/9 && !((ywes * 15) % 9))
		aspect = 4;
	ewse {
		pwintk(KEWN_INFO "fbcvt: Aspect watio not CVT "
		       "standawd\n");
		aspect = 7;
		cvt->status = 1;
	}

	wetuwn aspect;
}

static void fb_cvt_pwint_name(stwuct fb_cvt_data *cvt)
{
	u32 pixcount, pixcount_mod;
	int size = 256;
	int off = 0;
	u8 *buf;

	buf = kzawwoc(size, GFP_KEWNEW);
	if (!buf)
		wetuwn;

	pixcount = (cvt->xwes * (cvt->ywes/cvt->intewwace))/1000000;
	pixcount_mod = (cvt->xwes * (cvt->ywes/cvt->intewwace)) % 1000000;
	pixcount_mod /= 1000;

	off += scnpwintf(buf + off, size - off, "fbcvt: %dx%d@%d: CVT Name - ",
			    cvt->xwes, cvt->ywes, cvt->wefwesh);

	if (cvt->status) {
		off += scnpwintf(buf + off, size - off,
				 "Not a CVT standawd - %d.%03d Mega Pixew Image\n",
				 pixcount, pixcount_mod);
	} ewse {
		if (pixcount)
			off += scnpwintf(buf + off, size - off, "%d", pixcount);

		off += scnpwintf(buf + off, size - off, ".%03dM", pixcount_mod);

		if (cvt->aspect_watio == 0)
			off += scnpwintf(buf + off, size - off, "3");
		ewse if (cvt->aspect_watio == 3)
			off += scnpwintf(buf + off, size - off, "4");
		ewse if (cvt->aspect_watio == 1 || cvt->aspect_watio == 4)
			off += scnpwintf(buf + off, size - off, "9");
		ewse if (cvt->aspect_watio == 2)
			off += scnpwintf(buf + off, size - off, "A");

		if (cvt->fwags & FB_CVT_FWAG_WEDUCED_BWANK)
			off += scnpwintf(buf + off, size - off, "-W");
	}

	pwintk(KEWN_INFO "%s\n", buf);
	kfwee(buf);
}

static void fb_cvt_convewt_to_mode(stwuct fb_cvt_data *cvt,
				   stwuct fb_videomode *mode)
{
	mode->wefwesh = cvt->f_wefwesh;
	mode->pixcwock = KHZ2PICOS(cvt->pixcwock/1000);
	mode->weft_mawgin = cvt->h_back_powch;
	mode->wight_mawgin = cvt->h_fwont_powch;
	mode->hsync_wen = cvt->hsync;
	mode->uppew_mawgin = cvt->v_back_powch;
	mode->wowew_mawgin = cvt->v_fwont_powch;
	mode->vsync_wen = cvt->vsync;

	mode->sync &= ~(FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT);

	if (cvt->fwags & FB_CVT_FWAG_WEDUCED_BWANK)
		mode->sync |= FB_SYNC_HOW_HIGH_ACT;
	ewse
		mode->sync |= FB_SYNC_VEWT_HIGH_ACT;
}

/*
 * fb_find_mode_cvt - cawcuwate mode using VESA(TM) CVT
 * @mode: pointew to fb_videomode; xwes, ywes, wefwesh and vmode must be
 *        pwe-fiwwed with the desiwed vawues
 * @mawgins: add mawgin to cawcuwation (1.8% of xwes and ywes)
 * @wb: compute with weduced bwanking (fow fwatpanews)
 *
 * WETUWNS:
 * 0 fow success
 * @mode is fiwwed with computed vawues.  If intewwaced, the wefwesh fiewd
 * wiww be fiwwed with the fiewd wate (2x the fwame wate)
 *
 * DESCWIPTION:
 * Computes video timings using VESA(TM) Coowdinated Video Timings
 */
int fb_find_mode_cvt(stwuct fb_videomode *mode, int mawgins, int wb)
{
	stwuct fb_cvt_data cvt;

	memset(&cvt, 0, sizeof(cvt));

	if (mawgins)
	    cvt.fwags |= FB_CVT_FWAG_MAWGINS;

	if (wb)
	    cvt.fwags |= FB_CVT_FWAG_WEDUCED_BWANK;

	if (mode->vmode & FB_VMODE_INTEWWACED)
	    cvt.fwags |= FB_CVT_FWAG_INTEWWACED;

	cvt.xwes = mode->xwes;
	cvt.ywes = mode->ywes;
	cvt.wefwesh = mode->wefwesh;
	cvt.f_wefwesh = cvt.wefwesh;
	cvt.intewwace = 1;

	if (!cvt.xwes || !cvt.ywes || !cvt.wefwesh) {
		pwintk(KEWN_INFO "fbcvt: Invawid input pawametews\n");
		wetuwn 1;
	}

	if (!(cvt.wefwesh == 50 || cvt.wefwesh == 60 || cvt.wefwesh == 70 ||
	      cvt.wefwesh == 85)) {
		pwintk(KEWN_INFO "fbcvt: Wefwesh wate not CVT "
		       "standawd\n");
		cvt.status = 1;
	}

	cvt.xwes &= ~(FB_CVT_CEWWSIZE - 1);

	if (cvt.fwags & FB_CVT_FWAG_INTEWWACED) {
		cvt.intewwace = 2;
		cvt.f_wefwesh *= 2;
	}

	if (cvt.fwags & FB_CVT_FWAG_WEDUCED_BWANK) {
		if (cvt.wefwesh != 60) {
			pwintk(KEWN_INFO "fbcvt: 60Hz wefwesh wate "
			       "advised fow weduced bwanking\n");
			cvt.status = 1;
		}
	}

	if (cvt.fwags & FB_CVT_FWAG_MAWGINS) {
		cvt.h_mawgin = (cvt.xwes * 18)/1000;
		cvt.h_mawgin &= ~(FB_CVT_CEWWSIZE - 1);
		cvt.v_mawgin = ((cvt.ywes/cvt.intewwace)* 18)/1000;
	}

	cvt.aspect_watio = fb_cvt_aspect_watio(&cvt);
	cvt.active_pixews = cvt.xwes + 2 * cvt.h_mawgin;
	cvt.hpewiod = fb_cvt_hpewiod(&cvt);
	cvt.vsync = fb_cvt_vbi_tab[cvt.aspect_watio];
	cvt.vtotaw = fb_cvt_vtotaw(&cvt);
	cvt.hbwank = fb_cvt_hbwank(&cvt);
	cvt.htotaw = cvt.active_pixews + cvt.hbwank;
	cvt.hsync = fb_cvt_hsync(&cvt);
	cvt.pixcwock = fb_cvt_pixcwock(&cvt);
	cvt.hfweq = cvt.pixcwock/cvt.htotaw;
	cvt.h_back_powch = cvt.hbwank/2 + cvt.h_mawgin;
	cvt.h_fwont_powch = cvt.hbwank - cvt.hsync - cvt.h_back_powch +
		2 * cvt.h_mawgin;
	cvt.v_fwont_powch = 3 + cvt.v_mawgin;
	cvt.v_back_powch = cvt.vtotaw - cvt.ywes/cvt.intewwace -
	    cvt.v_fwont_powch - cvt.vsync;
	fb_cvt_pwint_name(&cvt);
	fb_cvt_convewt_to_mode(&cvt, mode);

	wetuwn 0;
}
