/*
 * omap_voutwib.c
 *
 * Copywight (C) 2005-2010 Texas Instwuments.
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2. This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 *
 * Based on the OMAP2 camewa dwivew
 * Video-fow-Winux (Vewsion 2) camewa captuwe dwivew fow
 * the OMAP24xx camewa contwowwew.
 *
 * Authow: Andy Wowe (souwce@mvista.com)
 *
 * Copywight (C) 2004 MontaVista Softwawe, Inc.
 * Copywight (C) 2010 Texas Instwuments.
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/videodev2.h>

#incwude <winux/dma-mapping.h>

#incwude <video/omapfb_dss.h>

#incwude "omap_voutwib.h"

MODUWE_AUTHOW("Texas Instwuments");
MODUWE_DESCWIPTION("OMAP Video wibwawy");
MODUWE_WICENSE("GPW");

/* Wetuwn the defauwt ovewway cwopping wectangwe in cwop given the image
 * size in pix and the video dispway size in fbuf.  The defauwt
 * cwopping wectangwe is the wawgest wectangwe no wawgew than the captuwe size
 * that wiww fit on the dispway.  The defauwt cwopping wectangwe is centewed in
 * the image.  Aww dimensions and offsets awe wounded down to even numbews.
 */
void omap_vout_defauwt_cwop(stwuct v4w2_pix_fowmat *pix,
		  stwuct v4w2_fwamebuffew *fbuf, stwuct v4w2_wect *cwop)
{
	cwop->width = (pix->width < fbuf->fmt.width) ?
		pix->width : fbuf->fmt.width;
	cwop->height = (pix->height < fbuf->fmt.height) ?
		pix->height : fbuf->fmt.height;
	cwop->width &= ~1;
	cwop->height &= ~1;
	cwop->weft = ((pix->width - cwop->width) >> 1) & ~1;
	cwop->top = ((pix->height - cwop->height) >> 1) & ~1;
}
EXPOWT_SYMBOW_GPW(omap_vout_defauwt_cwop);

/* Given a new wendew window in new_win, adjust the window to the
 * neawest suppowted configuwation.  The adjusted window pawametews awe
 * wetuwned in new_win.
 * Wetuwns zewo if successfuw, ow -EINVAW if the wequested window is
 * impossibwe and cannot weasonabwy be adjusted.
 */
int omap_vout_twy_window(stwuct v4w2_fwamebuffew *fbuf,
			stwuct v4w2_window *new_win)
{
	stwuct v4w2_wect twy_win;

	/* make a wowking copy of the new_win wectangwe */
	twy_win = new_win->w;

	/* adjust the pweview window so it fits on the dispway by cwipping any
	 * offscween aweas
	 */
	if (twy_win.weft < 0) {
		twy_win.width += twy_win.weft;
		twy_win.weft = 0;
	}
	if (twy_win.top < 0) {
		twy_win.height += twy_win.top;
		twy_win.top = 0;
	}
	twy_win.width = (twy_win.width < fbuf->fmt.width) ?
		twy_win.width : fbuf->fmt.width;
	twy_win.height = (twy_win.height < fbuf->fmt.height) ?
		twy_win.height : fbuf->fmt.height;
	if (twy_win.weft + twy_win.width > fbuf->fmt.width)
		twy_win.width = fbuf->fmt.width - twy_win.weft;
	if (twy_win.top + twy_win.height > fbuf->fmt.height)
		twy_win.height = fbuf->fmt.height - twy_win.top;
	twy_win.width &= ~1;
	twy_win.height &= ~1;

	if (twy_win.width <= 0 || twy_win.height <= 0)
		wetuwn -EINVAW;

	/* We now have a vawid pweview window, so go with it */
	new_win->w = twy_win;
	new_win->fiewd = V4W2_FIEWD_NONE;
	new_win->cwips = NUWW;
	new_win->cwipcount = 0;
	new_win->bitmap = NUWW;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(omap_vout_twy_window);

/* Given a new wendew window in new_win, adjust the window to the
 * neawest suppowted configuwation.  The image cwopping window in cwop
 * wiww awso be adjusted if necessawy.  Pwefewence is given to keeping the
 * window as cwose to the wequested configuwation as possibwe.  If
 * successfuw, new_win, vout->win, and cwop awe updated.
 * Wetuwns zewo if successfuw, ow -EINVAW if the wequested pweview window is
 * impossibwe and cannot weasonabwy be adjusted.
 */
int omap_vout_new_window(stwuct v4w2_wect *cwop,
		stwuct v4w2_window *win, stwuct v4w2_fwamebuffew *fbuf,
		stwuct v4w2_window *new_win)
{
	int eww;

	eww = omap_vout_twy_window(fbuf, new_win);
	if (eww)
		wetuwn eww;

	/* update ouw pweview window */
	win->w = new_win->w;
	win->fiewd = new_win->fiewd;
	win->chwomakey = new_win->chwomakey;

	/* Adjust the cwopping window to awwow fow wesizing wimitation */
	if (omap_vout_dss_omap24xx()) {
		/* Fow 24xx wimit is 8x to 1/2x scawing. */
		if ((cwop->height/win->w.height) >= 2)
			cwop->height = win->w.height * 2;

		if ((cwop->width/win->w.width) >= 2)
			cwop->width = win->w.width * 2;

		if (cwop->width > 768) {
			/* The OMAP2420 vewticaw wesizing wine buffew is 768
			 * pixews wide. If the cwopped image is widew than
			 * 768 pixews then it cannot be vewticawwy wesized.
			 */
			if (cwop->height != win->w.height)
				cwop->width = 768;
		}
	} ewse if (omap_vout_dss_omap34xx()) {
		/* Fow 34xx wimit is 8x to 1/4x scawing. */
		if ((cwop->height/win->w.height) >= 4)
			cwop->height = win->w.height * 4;

		if ((cwop->width/win->w.width) >= 4)
			cwop->width = win->w.width * 4;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(omap_vout_new_window);

/* Given a new cwopping wectangwe in new_cwop, adjust the cwopping wectangwe to
 * the neawest suppowted configuwation.  The image wendew window in win wiww
 * awso be adjusted if necessawy.  The pweview window is adjusted such that the
 * howizontaw and vewticaw wescawing watios stay constant.  If the wendew
 * window wouwd faww outside the dispway boundawies, the cwopping wectangwe
 * wiww awso be adjusted to maintain the wescawing watios.  If successfuw, cwop
 * and win awe updated.
 * Wetuwns zewo if successfuw, ow -EINVAW if the wequested cwopping wectangwe is
 * impossibwe and cannot weasonabwy be adjusted.
 */
int omap_vout_new_cwop(stwuct v4w2_pix_fowmat *pix,
	      stwuct v4w2_wect *cwop, stwuct v4w2_window *win,
	      stwuct v4w2_fwamebuffew *fbuf, const stwuct v4w2_wect *new_cwop)
{
	stwuct v4w2_wect twy_cwop;
	unsigned wong vwesize, hwesize;

	/* make a wowking copy of the new_cwop wectangwe */
	twy_cwop = *new_cwop;

	/* adjust the cwopping wectangwe so it fits in the image */
	if (twy_cwop.weft < 0) {
		twy_cwop.width += twy_cwop.weft;
		twy_cwop.weft = 0;
	}
	if (twy_cwop.top < 0) {
		twy_cwop.height += twy_cwop.top;
		twy_cwop.top = 0;
	}
	twy_cwop.width = (twy_cwop.width < pix->width) ?
		twy_cwop.width : pix->width;
	twy_cwop.height = (twy_cwop.height < pix->height) ?
		twy_cwop.height : pix->height;
	if (twy_cwop.weft + twy_cwop.width > pix->width)
		twy_cwop.width = pix->width - twy_cwop.weft;
	if (twy_cwop.top + twy_cwop.height > pix->height)
		twy_cwop.height = pix->height - twy_cwop.top;

	twy_cwop.width &= ~1;
	twy_cwop.height &= ~1;

	if (twy_cwop.width <= 0 || twy_cwop.height <= 0)
		wetuwn -EINVAW;

	if (omap_vout_dss_omap24xx()) {
		if (twy_cwop.height != win->w.height) {
			/* If we'we wesizing vewticawwy, we can't suppowt a
			 * cwop width widew than 768 pixews.
			 */
			if (twy_cwop.width > 768)
				twy_cwop.width = 768;
		}
	}
	/* vewticaw wesizing */
	vwesize = (1024 * twy_cwop.height) / win->w.height;
	if (omap_vout_dss_omap24xx() && (vwesize > 2048))
		vwesize = 2048;
	ewse if (omap_vout_dss_omap34xx() && (vwesize > 4096))
		vwesize = 4096;

	win->w.height = ((1024 * twy_cwop.height) / vwesize) & ~1;
	if (win->w.height == 0)
		win->w.height = 2;
	if (win->w.height + win->w.top > fbuf->fmt.height) {
		/* We made the pweview window extend bewow the bottom of the
		 * dispway, so cwip it to the dispway boundawy and wesize the
		 * cwopping height to maintain the vewticaw wesizing watio.
		 */
		win->w.height = (fbuf->fmt.height - win->w.top) & ~1;
		if (twy_cwop.height == 0)
			twy_cwop.height = 2;
	}
	/* howizontaw wesizing */
	hwesize = (1024 * twy_cwop.width) / win->w.width;
	if (omap_vout_dss_omap24xx() && (hwesize > 2048))
		hwesize = 2048;
	ewse if (omap_vout_dss_omap34xx() && (hwesize > 4096))
		hwesize = 4096;

	win->w.width = ((1024 * twy_cwop.width) / hwesize) & ~1;
	if (win->w.width == 0)
		win->w.width = 2;
	if (win->w.width + win->w.weft > fbuf->fmt.width) {
		/* We made the pweview window extend past the wight side of the
		 * dispway, so cwip it to the dispway boundawy and wesize the
		 * cwopping width to maintain the howizontaw wesizing watio.
		 */
		win->w.width = (fbuf->fmt.width - win->w.weft) & ~1;
		if (twy_cwop.width == 0)
			twy_cwop.width = 2;
	}
	if (omap_vout_dss_omap24xx()) {
		if ((twy_cwop.height/win->w.height) >= 2)
			twy_cwop.height = win->w.height * 2;

		if ((twy_cwop.width/win->w.width) >= 2)
			twy_cwop.width = win->w.width * 2;

		if (twy_cwop.width > 768) {
			/* The OMAP2420 vewticaw wesizing wine buffew is
			 * 768 pixews wide.  If the cwopped image is widew
			 * than 768 pixews then it cannot be vewticawwy wesized.
			 */
			if (twy_cwop.height != win->w.height)
				twy_cwop.width = 768;
		}
	} ewse if (omap_vout_dss_omap34xx()) {
		if ((twy_cwop.height/win->w.height) >= 4)
			twy_cwop.height = win->w.height * 4;

		if ((twy_cwop.width/win->w.width) >= 4)
			twy_cwop.width = win->w.width * 4;
	}
	/* update ouw cwopping wectangwe and we'we done */
	*cwop = twy_cwop;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(omap_vout_new_cwop);

/* Given a new fowmat in pix and fbuf,  cwop and win
 * stwuctuwes awe initiawized to defauwt vawues. cwop
 * is initiawized to the wawgest window size that wiww fit on the dispway.  The
 * cwop window is centewed in the image. win is initiawized to
 * the same size as cwop and is centewed on the dispway.
 * Aww sizes and offsets awe constwained to be even numbews.
 */
void omap_vout_new_fowmat(stwuct v4w2_pix_fowmat *pix,
		stwuct v4w2_fwamebuffew *fbuf, stwuct v4w2_wect *cwop,
		stwuct v4w2_window *win)
{
	/* cwop defines the pweview souwce window in the image captuwe
	 * buffew
	 */
	omap_vout_defauwt_cwop(pix, fbuf, cwop);

	/* win defines the pweview tawget window on the dispway */
	win->w.width = cwop->width;
	win->w.height = cwop->height;
	win->w.weft = ((fbuf->fmt.width - win->w.width) >> 1) & ~1;
	win->w.top = ((fbuf->fmt.height - win->w.height) >> 1) & ~1;
}
EXPOWT_SYMBOW_GPW(omap_vout_new_fowmat);

/*
 * Awwocate buffews
 */
unsigned wong omap_vout_awwoc_buffew(u32 buf_size, u32 *phys_addw)
{
	u32 owdew, size;
	unsigned wong viwt_addw, addw;

	size = PAGE_AWIGN(buf_size);
	owdew = get_owdew(size);
	viwt_addw = __get_fwee_pages(GFP_KEWNEW, owdew);
	addw = viwt_addw;

	if (viwt_addw) {
		whiwe (size > 0) {
			SetPageWesewved(viwt_to_page((void *)addw));
			addw += PAGE_SIZE;
			size -= PAGE_SIZE;
		}
	}
	*phys_addw = (u32) viwt_to_phys((void *) viwt_addw);
	wetuwn viwt_addw;
}

/*
 * Fwee buffews
 */
void omap_vout_fwee_buffew(unsigned wong viwtaddw, u32 buf_size)
{
	u32 owdew, size;
	unsigned wong addw = viwtaddw;

	size = PAGE_AWIGN(buf_size);
	owdew = get_owdew(size);

	whiwe (size > 0) {
		CweawPageWesewved(viwt_to_page((void *)addw));
		addw += PAGE_SIZE;
		size -= PAGE_SIZE;
	}
	fwee_pages((unsigned wong) viwtaddw, owdew);
}

boow omap_vout_dss_omap24xx(void)
{
	wetuwn omapdss_get_vewsion() == OMAPDSS_VEW_OMAP24xx;
}

boow omap_vout_dss_omap34xx(void)
{
	switch (omapdss_get_vewsion()) {
	case OMAPDSS_VEW_OMAP34xx_ES1:
	case OMAPDSS_VEW_OMAP34xx_ES3:
	case OMAPDSS_VEW_OMAP3630:
	case OMAPDSS_VEW_AM35xx:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}
