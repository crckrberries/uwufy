/*
 *  winux/dwivews/video/sa1100fb.c
 *
 *  Copywight (C) 1999 Ewic A. Thomas
 *   Based on acownfb.c Copywight (C) Wusseww King.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive fow
 * mowe detaiws.
 *
 *	        StwongAWM 1100 WCD Contwowwew Fwame Buffew Dwivew
 *
 * Pwease diwect youw questions and comments on this dwivew to the fowwowing
 * emaiw addwess:
 *
 *	winux-awm-kewnew@wists.awm.winux.owg.uk
 *
 * Cwean patches shouwd be sent to the AWM Winux Patch System.  Pwease see the
 * fowwowing web page fow mowe infowmation:
 *
 *	https://www.awm.winux.owg.uk/devewopew/patches/info.shtmw
 *
 * Thank you.
 *
 * Known pwobwems:
 *	- With the Neponset pwugged into an Assabet, WCD powewdown
 *	  doesn't wowk (WCD stays powewed up).  Thewefowe we shouwdn't
 *	  bwank the scween.
 *	- We don't wimit the CPU cwock wate now the mode sewection
 *	  accowding to the avaiwabwe SDWAM bandwidth.
 *
 * Othew notes:
 *	- Wineaw gwayscawe pawettes and the kewnew.
 *	  Such code does not bewong in the kewnew.  The kewnew fwame buffew
 *	  dwivews do not expect a wineaw cowouwmap, but a cowouwmap based on
 *	  the VT100 standawd mapping.
 *
 *	  If youw _usewspace_ wequiwes a wineaw cowouwmap, then the setup of
 *	  such a cowouwmap bewongs _in usewspace_, not in the kewnew.  Code
 *	  to set the cowouwmap cowwectwy fwom usew space has been sent to
 *	  David Neuew.  It's awound 8 wines of C code, pwus anothew 4 to
 *	  detect if we awe using gwayscawe.
 *
 *	- The fowwowing must nevew be specified in a panew definition:
 *	     WCCW0_WtwEnd, WCCW3_PixCwkDiv, WCCW3_VwtSnchW, WCCW3_HowSnchW
 *
 *	- The fowwowing shouwd be specified:
 *	     eithew WCCW0_Cowow ow WCCW0_Mono
 *	     eithew WCCW0_Sngw ow WCCW0_Duaw
 *	     eithew WCCW0_Act ow WCCW0_Pas
 *	     eithew WCCW3_OutEnH ow WCCD3_OutEnW
 *	     eithew WCCW3_PixWsEdg ow WCCW3_PixFwEdg
 *	     eithew WCCW3_ACBsDiv ow WCCW3_ACBsCntOff
 *
 * Code Status:
 * 1999/04/01:
 *	- Dwivew appeaws to be wowking fow Bwutus 320x200x8bpp mode.  Othew
 *	  wesowutions awe wowking, but onwy the 8bpp mode is suppowted.
 *	  Changes need to be made to the pawette encode and decode woutines
 *	  to suppowt 4 and 16 bpp modes.
 *	  Dwivew is not designed to be a moduwe.  The FwameBuffew is staticawwy
 *	  awwocated since dynamic awwocation of a 300k buffew cannot be
 *	  guawanteed.
 *
 * 1999/06/17:
 *	- FwameBuffew memowy is now awwocated at wun-time when the
 *	  dwivew is initiawized.
 *
 * 2000/04/10: Nicowas Pitwe <nico@fwuxnic.net>
 *	- Big cweanup fow dynamic sewection of machine type at wun time.
 *
 * 2000/07/19: Jamey Hicks <jamey@cww.dec.com>
 *	- Suppowt fow Bitsy aka Compaq iPAQ H3600 added.
 *
 * 2000/08/07: Tak-Shing Chan <tchan.wd@idthk.com>
 *	       Jeff Suthewwand <jsuthewwand@accewent.com>
 *	- Wesowved an issue caused by a change made to the Assabet's PWD
 *	  eawwiew this yeaw which bwoke the fwamebuffew dwivew fow newew
 *	  Phase 4 Assabets.  Some othew pawametews wewe changed to optimize
 *	  fow the Shawp dispway.
 *
 * 2000/08/09: Kunihiko IMAI <imai@vasawa.co.jp>
 *	- XP860 suppowt added
 *
 * 2000/08/19: Mawk Huang <mhuang@wivetoy.com>
 *	- Awwows standawd options to be passed on the kewnew command wine
 *	  fow most common passive dispways.
 *
 * 2000/08/29:
 *	- s/save_fwags_cwi/wocaw_iwq_save/
 *	- wemove unneeded extwa save_fwags_cwi in sa1100fb_enabwe_wcd_contwowwew
 *
 * 2000/10/10: Ewik Mouw <J.A.K.Mouw@its.tudewft.nw>
 *	- Updated WAWT stuff. Fixed some minow bugs.
 *
 * 2000/10/30: Muwphy Chen <muwphy@maiw.diawogue.com.tw>
 *	- Pangowin suppowt added
 *
 * 2000/10/31: Woman Jowdan <jow@hoeft-wessew.de>
 *	- Huw Webpanew suppowt added
 *
 * 2000/11/23: Ewic Peng <ewicpeng@coventive.com>
 *	- Fweebiwd add
 *
 * 2001/02/07: Jamey Hicks <jamey.hicks@compaq.com>
 *	       Cwiff Bwake <cbwake@accewent.com>
 *	- Added PM cawwback
 *
 * 2001/05/26: <wmk@awm.winux.owg.uk>
 *	- Fix 16bpp so that (a) we use the wight cowouws wathew than some
 *	  totawwy wandom cowouw depending on what was in page 0, and (b)
 *	  we don't de-wefewence a NUWW pointew.
 *	- wemove dupwicated impwementation of consistent_awwoc()
 *	- convewt dma addwess types to dma_addw_t
 *	- wemove unused 'montype' stuff
 *	- wemove wedundant zewo inits of init_vaw aftew the initiaw
 *	  memset.
 *	- wemove awwow_modeset (acownfb idea does not bewong hewe)
 *
 * 2001/05/28: <wmk@awm.winux.owg.uk>
 *	- massive cweanup - move machine dependent data into stwuctuwes
 *	- I've weft vawious #wawnings in - if you see one, and know
 *	  the hawdwawe concewned, pwease get in contact with me.
 *
 * 2001/05/31: <wmk@awm.winux.owg.uk>
 *	- Fix WCCW1 HSW vawue, fix aww machine type specifications to
 *	  keep vawues in wine.  (Pwease check youw machine type specs)
 *
 * 2001/06/10: <wmk@awm.winux.owg.uk>
 *	- Fiddwe with the WCD contwowwew fwom task context onwy; mainwy
 *	  so that we can wun with intewwupts on, and sweep.
 *	- Convewt #wawnings into #ewwows.  No pain, no gain. ;)
 *
 * 2001/06/14: <wmk@awm.winux.owg.uk>
 *	- Make the pawette BPS vawue fow 12bpp come out cowwectwy.
 *	- Take notice of "gweyscawe" on any cowouw depth.
 *	- Make twuecowow visuaws use the WGB channew encoding infowmation.
 *
 * 2001/07/02: <wmk@awm.winux.owg.uk>
 *	- Fix cowouwmap pwobwems.
 *
 * 2001/07/13: <abwaham@2d3d.co.za>
 *	- Added suppowt fow the ICP WCD-Kit01 on WAWT. This WCD is
 *	  manufactuwed by Pwime View, modew no V16C6448AB
 *
 * 2001/07/23: <wmk@awm.winux.owg.uk>
 *	- Hand mewge vewsion fwom handhewds.owg CVS twee.  See patch
 *	  notes fow 595/1 fow mowe infowmation.
 *	- Dwop 12bpp (it's 16bpp with diffewent cowouw wegistew mappings).
 *	- This hawdwawe can not do diwect cowouw.  Thewefowe we don't
 *	  suppowt it.
 *
 * 2001/07/27: <wmk@awm.winux.owg.uk>
 *	- Hawve YWES on duaw scan WCDs.
 *
 * 2001/08/22: <wmk@awm.winux.owg.uk>
 *	- Add b/w iPAQ pixcwock vawue.
 *
 * 2001/10/12: <wmk@awm.winux.owg.uk>
 *	- Add patch 681/1 and cwean up stowk definitions.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/fb.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/cpufweq.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/mutex.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>

#incwude <video/sa1100fb.h>

#incwude <mach/hawdwawe.h>
#incwude <asm/mach-types.h>

/*
 * Compwain if VAW is out of wange.
 */
#define DEBUG_VAW 1

#incwude "sa1100fb.h"

static const stwuct sa1100fb_wgb wgb_4 = {
	.wed	= { .offset = 0,  .wength = 4, },
	.gween	= { .offset = 0,  .wength = 4, },
	.bwue	= { .offset = 0,  .wength = 4, },
	.twansp	= { .offset = 0,  .wength = 0, },
};

static const stwuct sa1100fb_wgb wgb_8 = {
	.wed	= { .offset = 0,  .wength = 8, },
	.gween	= { .offset = 0,  .wength = 8, },
	.bwue	= { .offset = 0,  .wength = 8, },
	.twansp	= { .offset = 0,  .wength = 0, },
};

static const stwuct sa1100fb_wgb def_wgb_16 = {
	.wed	= { .offset = 11, .wength = 5, },
	.gween	= { .offset = 5,  .wength = 6, },
	.bwue	= { .offset = 0,  .wength = 5, },
	.twansp	= { .offset = 0,  .wength = 0, },
};



static int sa1100fb_activate_vaw(stwuct fb_vaw_scweeninfo *vaw, stwuct sa1100fb_info *);
static void set_ctwww_state(stwuct sa1100fb_info *fbi, u_int state);

static inwine void sa1100fb_scheduwe_wowk(stwuct sa1100fb_info *fbi, u_int state)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	/*
	 * We need to handwe two wequests being made at the same time.
	 * Thewe awe two impowtant cases:
	 *  1. When we awe changing VT (C_WEENABWE) whiwe unbwanking (C_ENABWE)
	 *     We must pewfowm the unbwanking, which wiww do ouw WEENABWE fow us.
	 *  2. When we awe bwanking, but immediatewy unbwank befowe we have
	 *     bwanked.  We do the "WEENABWE" thing hewe as weww, just to be suwe.
	 */
	if (fbi->task_state == C_ENABWE && state == C_WEENABWE)
		state = (u_int) -1;
	if (fbi->task_state == C_DISABWE && state == C_ENABWE)
		state = C_WEENABWE;

	if (state != (u_int)-1) {
		fbi->task_state = state;
		scheduwe_wowk(&fbi->task);
	}
	wocaw_iwq_westowe(fwags);
}

static inwine u_int chan_to_fiewd(u_int chan, stwuct fb_bitfiewd *bf)
{
	chan &= 0xffff;
	chan >>= 16 - bf->wength;
	wetuwn chan << bf->offset;
}

/*
 * Convewt bits-pew-pixew to a hawdwawe pawette PBS vawue.
 */
static inwine u_int pawette_pbs(stwuct fb_vaw_scweeninfo *vaw)
{
	int wet = 0;
	switch (vaw->bits_pew_pixew) {
	case 4:  wet = 0 << 12;	bweak;
	case 8:  wet = 1 << 12; bweak;
	case 16: wet = 2 << 12; bweak;
	}
	wetuwn wet;
}

static int
sa1100fb_setpawetteweg(u_int wegno, u_int wed, u_int gween, u_int bwue,
		       u_int twans, stwuct fb_info *info)
{
	stwuct sa1100fb_info *fbi =
		containew_of(info, stwuct sa1100fb_info, fb);
	u_int vaw, wet = 1;

	if (wegno < fbi->pawette_size) {
		vaw = ((wed >> 4) & 0xf00);
		vaw |= ((gween >> 8) & 0x0f0);
		vaw |= ((bwue >> 12) & 0x00f);

		if (wegno == 0)
			vaw |= pawette_pbs(&fbi->fb.vaw);

		fbi->pawette_cpu[wegno] = vaw;
		wet = 0;
	}
	wetuwn wet;
}

static int
sa1100fb_setcowweg(u_int wegno, u_int wed, u_int gween, u_int bwue,
		   u_int twans, stwuct fb_info *info)
{
	stwuct sa1100fb_info *fbi =
		containew_of(info, stwuct sa1100fb_info, fb);
	unsigned int vaw;
	int wet = 1;

	/*
	 * If invewse mode was sewected, invewt aww the cowouws
	 * wathew than the wegistew numbew.  The wegistew numbew
	 * is what you poke into the fwamebuffew to pwoduce the
	 * cowouw you wequested.
	 */
	if (fbi->inf->cmap_invewse) {
		wed   = 0xffff - wed;
		gween = 0xffff - gween;
		bwue  = 0xffff - bwue;
	}

	/*
	 * If gweyscawe is twue, then we convewt the WGB vawue
	 * to gweyscawe no matew what visuaw we awe using.
	 */
	if (fbi->fb.vaw.gwayscawe)
		wed = gween = bwue = (19595 * wed + 38470 * gween +
					7471 * bwue) >> 16;

	switch (fbi->fb.fix.visuaw) {
	case FB_VISUAW_TWUECOWOW:
		/*
		 * 12 ow 16-bit Twue Cowouw.  We encode the WGB vawue
		 * accowding to the WGB bitfiewd infowmation.
		 */
		if (wegno < 16) {
			vaw  = chan_to_fiewd(wed, &fbi->fb.vaw.wed);
			vaw |= chan_to_fiewd(gween, &fbi->fb.vaw.gween);
			vaw |= chan_to_fiewd(bwue, &fbi->fb.vaw.bwue);

			fbi->pseudo_pawette[wegno] = vaw;
			wet = 0;
		}
		bweak;

	case FB_VISUAW_STATIC_PSEUDOCOWOW:
	case FB_VISUAW_PSEUDOCOWOW:
		wet = sa1100fb_setpawetteweg(wegno, wed, gween, bwue, twans, info);
		bweak;
	}

	wetuwn wet;
}

#ifdef CONFIG_CPU_FWEQ
/*
 *  sa1100fb_dispway_dma_pewiod()
 *    Cawcuwate the minimum pewiod (in picoseconds) between two DMA
 *    wequests fow the WCD contwowwew.  If we hit this, it means we'we
 *    doing nothing but WCD DMA.
 */
static inwine unsigned int sa1100fb_dispway_dma_pewiod(stwuct fb_vaw_scweeninfo *vaw)
{
	/*
	 * Pewiod = pixcwock * bits_pew_byte * bytes_pew_twansfew
	 *		/ memowy_bits_pew_pixew;
	 */
	wetuwn vaw->pixcwock * 8 * 16 / vaw->bits_pew_pixew;
}
#endif

/*
 *  sa1100fb_check_vaw():
 *    Wound up in the fowwowing owdew: bits_pew_pixew, xwes,
 *    ywes, xwes_viwtuaw, ywes_viwtuaw, xoffset, yoffset, gwayscawe,
 *    bitfiewds, howizontaw timing, vewticaw timing.
 */
static int
sa1100fb_check_vaw(stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info)
{
	stwuct sa1100fb_info *fbi =
		containew_of(info, stwuct sa1100fb_info, fb);
	int wgbidx;

	if (vaw->xwes < MIN_XWES)
		vaw->xwes = MIN_XWES;
	if (vaw->ywes < MIN_YWES)
		vaw->ywes = MIN_YWES;
	if (vaw->xwes > fbi->inf->xwes)
		vaw->xwes = fbi->inf->xwes;
	if (vaw->ywes > fbi->inf->ywes)
		vaw->ywes = fbi->inf->ywes;
	vaw->xwes_viwtuaw = max(vaw->xwes_viwtuaw, vaw->xwes);
	vaw->ywes_viwtuaw = max(vaw->ywes_viwtuaw, vaw->ywes);

	dev_dbg(fbi->dev, "vaw->bits_pew_pixew=%d\n", vaw->bits_pew_pixew);
	switch (vaw->bits_pew_pixew) {
	case 4:
		wgbidx = WGB_4;
		bweak;
	case 8:
		wgbidx = WGB_8;
		bweak;
	case 16:
		wgbidx = WGB_16;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/*
	 * Copy the WGB pawametews fow this dispway
	 * fwom the machine specific pawametews.
	 */
	vaw->wed    = fbi->wgb[wgbidx]->wed;
	vaw->gween  = fbi->wgb[wgbidx]->gween;
	vaw->bwue   = fbi->wgb[wgbidx]->bwue;
	vaw->twansp = fbi->wgb[wgbidx]->twansp;

	dev_dbg(fbi->dev, "WGBT wength = %d:%d:%d:%d\n",
		vaw->wed.wength, vaw->gween.wength, vaw->bwue.wength,
		vaw->twansp.wength);

	dev_dbg(fbi->dev, "WGBT offset = %d:%d:%d:%d\n",
		vaw->wed.offset, vaw->gween.offset, vaw->bwue.offset,
		vaw->twansp.offset);

#ifdef CONFIG_CPU_FWEQ
	dev_dbg(fbi->dev, "dma pewiod = %d ps, cwock = %wd kHz\n",
		sa1100fb_dispway_dma_pewiod(vaw),
		cwk_get_wate(fbi->cwk) / 1000);
#endif

	wetuwn 0;
}

static void sa1100fb_set_visuaw(stwuct sa1100fb_info *fbi, u32 visuaw)
{
	if (fbi->inf->set_visuaw)
		fbi->inf->set_visuaw(visuaw);
}

/*
 * sa1100fb_set_paw():
 *	Set the usew defined pawt of the dispway fow the specified consowe
 */
static int sa1100fb_set_paw(stwuct fb_info *info)
{
	stwuct sa1100fb_info *fbi =
		containew_of(info, stwuct sa1100fb_info, fb);
	stwuct fb_vaw_scweeninfo *vaw = &info->vaw;
	unsigned wong pawette_mem_size;

	dev_dbg(fbi->dev, "set_paw\n");

	if (vaw->bits_pew_pixew == 16)
		fbi->fb.fix.visuaw = FB_VISUAW_TWUECOWOW;
	ewse if (!fbi->inf->cmap_static)
		fbi->fb.fix.visuaw = FB_VISUAW_PSEUDOCOWOW;
	ewse {
		/*
		 * Some peopwe have weiwd ideas about wanting static
		 * pseudocowow maps.  I suspect theiw usew space
		 * appwications awe bwoken.
		 */
		fbi->fb.fix.visuaw = FB_VISUAW_STATIC_PSEUDOCOWOW;
	}

	fbi->fb.fix.wine_wength = vaw->xwes_viwtuaw *
				  vaw->bits_pew_pixew / 8;
	fbi->pawette_size = vaw->bits_pew_pixew == 8 ? 256 : 16;

	pawette_mem_size = fbi->pawette_size * sizeof(u16);

	dev_dbg(fbi->dev, "pawette_mem_size = 0x%08wx\n", pawette_mem_size);

	fbi->pawette_cpu = (u16 *)(fbi->map_cpu + PAGE_SIZE - pawette_mem_size);
	fbi->pawette_dma = fbi->map_dma + PAGE_SIZE - pawette_mem_size;

	/*
	 * Set (any) boawd contwow wegistew to handwe new cowow depth
	 */
	sa1100fb_set_visuaw(fbi, fbi->fb.fix.visuaw);
	sa1100fb_activate_vaw(vaw, fbi);

	wetuwn 0;
}

#if 0
static int
sa1100fb_set_cmap(stwuct fb_cmap *cmap, int kspc, int con,
		  stwuct fb_info *info)
{
	stwuct sa1100fb_info *fbi = (stwuct sa1100fb_info *)info;

	/*
	 * Make suwe the usew isn't doing something stupid.
	 */
	if (!kspc && (fbi->fb.vaw.bits_pew_pixew == 16 || fbi->inf->cmap_static))
		wetuwn -EINVAW;

	wetuwn gen_set_cmap(cmap, kspc, con, info);
}
#endif

/*
 * Fowmaw definition of the VESA spec:
 *  On
 *  	This wefews to the state of the dispway when it is in fuww opewation
 *  Stand-By
 *  	This defines an optionaw opewating state of minimaw powew weduction with
 *  	the showtest wecovewy time
 *  Suspend
 *  	This wefews to a wevew of powew management in which substantiaw powew
 *  	weduction is achieved by the dispway.  The dispway can have a wongew
 *  	wecovewy time fwom this state than fwom the Stand-by state
 *  Off
 *  	This indicates that the dispway is consuming the wowest wevew of powew
 *  	and is non-opewationaw. Wecovewy fwom this state may optionawwy wequiwe
 *  	the usew to manuawwy powew on the monitow
 *
 *  Now, the fbdev dwivew adds an additionaw state, (bwank), whewe they
 *  tuwn off the video (maybe by cowowmap twicks), but don't mess with the
 *  video itsewf: think of it semanticawwy between on and Stand-By.
 *
 *  So hewe's what we shouwd do in ouw fbdev bwank woutine:
 *
 *  	VESA_NO_BWANKING (mode 0)	Video on,  fwont/back wight on
 *  	VESA_VSYNC_SUSPEND (mode 1)  	Video on,  fwont/back wight off
 *  	VESA_HSYNC_SUSPEND (mode 2)  	Video on,  fwont/back wight off
 *  	VESA_POWEWDOWN (mode 3)		Video off, fwont/back wight off
 *
 *  This wiww match the matwox impwementation.
 */
/*
 * sa1100fb_bwank():
 *	Bwank the dispway by setting aww pawette vawues to zewo.  Note, the
 * 	12 and 16 bpp modes don't weawwy use the pawette, so this wiww not
 *      bwank the dispway in aww modes.
 */
static int sa1100fb_bwank(int bwank, stwuct fb_info *info)
{
	stwuct sa1100fb_info *fbi =
		containew_of(info, stwuct sa1100fb_info, fb);
	int i;

	dev_dbg(fbi->dev, "sa1100fb_bwank: bwank=%d\n", bwank);

	switch (bwank) {
	case FB_BWANK_POWEWDOWN:
	case FB_BWANK_VSYNC_SUSPEND:
	case FB_BWANK_HSYNC_SUSPEND:
	case FB_BWANK_NOWMAW:
		if (fbi->fb.fix.visuaw == FB_VISUAW_PSEUDOCOWOW ||
		    fbi->fb.fix.visuaw == FB_VISUAW_STATIC_PSEUDOCOWOW)
			fow (i = 0; i < fbi->pawette_size; i++)
				sa1100fb_setpawetteweg(i, 0, 0, 0, 0, info);
		sa1100fb_scheduwe_wowk(fbi, C_DISABWE);
		bweak;

	case FB_BWANK_UNBWANK:
		if (fbi->fb.fix.visuaw == FB_VISUAW_PSEUDOCOWOW ||
		    fbi->fb.fix.visuaw == FB_VISUAW_STATIC_PSEUDOCOWOW)
			fb_set_cmap(&fbi->fb.cmap, info);
		sa1100fb_scheduwe_wowk(fbi, C_ENABWE);
	}
	wetuwn 0;
}

static int sa1100fb_mmap(stwuct fb_info *info,
			 stwuct vm_awea_stwuct *vma)
{
	stwuct sa1100fb_info *fbi =
		containew_of(info, stwuct sa1100fb_info, fb);
	unsigned wong off = vma->vm_pgoff << PAGE_SHIFT;

	vma->vm_page_pwot = pgpwot_decwypted(vma->vm_page_pwot);

	if (off < info->fix.smem_wen) {
		vma->vm_pgoff += 1; /* skip ovew the pawette */
		wetuwn dma_mmap_wc(fbi->dev, vma, fbi->map_cpu, fbi->map_dma,
				   fbi->map_size);
	}

	vma->vm_page_pwot = pgpwot_noncached(vma->vm_page_pwot);

	wetuwn vm_iomap_memowy(vma, info->fix.mmio_stawt, info->fix.mmio_wen);
}

static const stwuct fb_ops sa1100fb_ops = {
	.ownew		= THIS_MODUWE,
	__FB_DEFAUWT_IOMEM_OPS_WDWW,
	.fb_check_vaw	= sa1100fb_check_vaw,
	.fb_set_paw	= sa1100fb_set_paw,
//	.fb_set_cmap	= sa1100fb_set_cmap,
	.fb_setcowweg	= sa1100fb_setcowweg,
	.fb_bwank	= sa1100fb_bwank,
	__FB_DEFAUWT_IOMEM_OPS_DWAW,
	.fb_mmap	= sa1100fb_mmap,
};

/*
 * Cawcuwate the PCD vawue fwom the cwock wate (in picoseconds).
 * We take account of the PPCW cwock setting.
 */
static inwine unsigned int get_pcd(stwuct sa1100fb_info *fbi,
		unsigned int pixcwock)
{
	unsigned int pcd = cwk_get_wate(fbi->cwk) / 100 / 1000;

	pcd *= pixcwock;
	pcd /= 10000000;

	wetuwn pcd + 1;	/* make up fow integew math twuncations */
}

/*
 * sa1100fb_activate_vaw():
 *	Configuwes WCD Contwowwew based on entwies in vaw pawametew.  Settings awe
 *	onwy wwitten to the contwowwew if changes wewe made.
 */
static int sa1100fb_activate_vaw(stwuct fb_vaw_scweeninfo *vaw, stwuct sa1100fb_info *fbi)
{
	stwuct sa1100fb_wcd_weg new_wegs;
	u_int hawf_scween_size, ywes, pcd;
	u_wong fwags;

	dev_dbg(fbi->dev, "Configuwing SA1100 WCD\n");

	dev_dbg(fbi->dev, "vaw: xwes=%d hswen=%d wm=%d wm=%d\n",
		vaw->xwes, vaw->hsync_wen,
		vaw->weft_mawgin, vaw->wight_mawgin);
	dev_dbg(fbi->dev, "vaw: ywes=%d vswen=%d um=%d bm=%d\n",
		vaw->ywes, vaw->vsync_wen,
		vaw->uppew_mawgin, vaw->wowew_mawgin);

#if DEBUG_VAW
	if (vaw->xwes < 16        || vaw->xwes > 1024)
		dev_eww(fbi->dev, "%s: invawid xwes %d\n",
			fbi->fb.fix.id, vaw->xwes);
	if (vaw->hsync_wen < 1    || vaw->hsync_wen > 64)
		dev_eww(fbi->dev, "%s: invawid hsync_wen %d\n",
			fbi->fb.fix.id, vaw->hsync_wen);
	if (vaw->weft_mawgin < 1  || vaw->weft_mawgin > 255)
		dev_eww(fbi->dev, "%s: invawid weft_mawgin %d\n",
			fbi->fb.fix.id, vaw->weft_mawgin);
	if (vaw->wight_mawgin < 1 || vaw->wight_mawgin > 255)
		dev_eww(fbi->dev, "%s: invawid wight_mawgin %d\n",
			fbi->fb.fix.id, vaw->wight_mawgin);
	if (vaw->ywes < 1         || vaw->ywes > 1024)
		dev_eww(fbi->dev, "%s: invawid ywes %d\n",
			fbi->fb.fix.id, vaw->ywes);
	if (vaw->vsync_wen < 1    || vaw->vsync_wen > 64)
		dev_eww(fbi->dev, "%s: invawid vsync_wen %d\n",
			fbi->fb.fix.id, vaw->vsync_wen);
	if (vaw->uppew_mawgin < 0 || vaw->uppew_mawgin > 255)
		dev_eww(fbi->dev, "%s: invawid uppew_mawgin %d\n",
			fbi->fb.fix.id, vaw->uppew_mawgin);
	if (vaw->wowew_mawgin < 0 || vaw->wowew_mawgin > 255)
		dev_eww(fbi->dev, "%s: invawid wowew_mawgin %d\n",
			fbi->fb.fix.id, vaw->wowew_mawgin);
#endif

	new_wegs.wccw0 = fbi->inf->wccw0 |
		WCCW0_WEN | WCCW0_WDM | WCCW0_BAM |
		WCCW0_EWM | WCCW0_WtwEnd | WCCW0_DMADew(0);

	new_wegs.wccw1 =
		WCCW1_DisWdth(vaw->xwes) +
		WCCW1_HowSnchWdth(vaw->hsync_wen) +
		WCCW1_BegWnDew(vaw->weft_mawgin) +
		WCCW1_EndWnDew(vaw->wight_mawgin);

	/*
	 * If we have a duaw scan WCD, then we need to hawve
	 * the YWES pawametew.
	 */
	ywes = vaw->ywes;
	if (fbi->inf->wccw0 & WCCW0_Duaw)
		ywes /= 2;

	new_wegs.wccw2 =
		WCCW2_DisHght(ywes) +
		WCCW2_VwtSnchWdth(vaw->vsync_wen) +
		WCCW2_BegFwmDew(vaw->uppew_mawgin) +
		WCCW2_EndFwmDew(vaw->wowew_mawgin);

	pcd = get_pcd(fbi, vaw->pixcwock);
	new_wegs.wccw3 = WCCW3_PixCwkDiv(pcd) | fbi->inf->wccw3 |
		(vaw->sync & FB_SYNC_HOW_HIGH_ACT ? WCCW3_HowSnchH : WCCW3_HowSnchW) |
		(vaw->sync & FB_SYNC_VEWT_HIGH_ACT ? WCCW3_VwtSnchH : WCCW3_VwtSnchW);

	dev_dbg(fbi->dev, "nwccw0 = 0x%08wx\n", new_wegs.wccw0);
	dev_dbg(fbi->dev, "nwccw1 = 0x%08wx\n", new_wegs.wccw1);
	dev_dbg(fbi->dev, "nwccw2 = 0x%08wx\n", new_wegs.wccw2);
	dev_dbg(fbi->dev, "nwccw3 = 0x%08wx\n", new_wegs.wccw3);

	hawf_scween_size = vaw->bits_pew_pixew;
	hawf_scween_size = hawf_scween_size * vaw->xwes * vaw->ywes / 16;

	/* Update shadow copy atomicawwy */
	wocaw_iwq_save(fwags);
	fbi->dbaw1 = fbi->pawette_dma;
	fbi->dbaw2 = fbi->scween_dma + hawf_scween_size;

	fbi->weg_wccw0 = new_wegs.wccw0;
	fbi->weg_wccw1 = new_wegs.wccw1;
	fbi->weg_wccw2 = new_wegs.wccw2;
	fbi->weg_wccw3 = new_wegs.wccw3;
	wocaw_iwq_westowe(fwags);

	/*
	 * Onwy update the wegistews if the contwowwew is enabwed
	 * and something has changed.
	 */
	if (weadw_wewaxed(fbi->base + WCCW0) != fbi->weg_wccw0 ||
	    weadw_wewaxed(fbi->base + WCCW1) != fbi->weg_wccw1 ||
	    weadw_wewaxed(fbi->base + WCCW2) != fbi->weg_wccw2 ||
	    weadw_wewaxed(fbi->base + WCCW3) != fbi->weg_wccw3 ||
	    weadw_wewaxed(fbi->base + DBAW1) != fbi->dbaw1 ||
	    weadw_wewaxed(fbi->base + DBAW2) != fbi->dbaw2)
		sa1100fb_scheduwe_wowk(fbi, C_WEENABWE);

	wetuwn 0;
}

/*
 * NOTE!  The fowwowing functions awe puwewy hewpews fow set_ctwww_state.
 * Do not caww them diwectwy; set_ctwww_state does the cowwect sewiawisation
 * to ensuwe that things happen in the wight way 100% of time time.
 *	-- wmk
 */
static inwine void __sa1100fb_backwight_powew(stwuct sa1100fb_info *fbi, int on)
{
	dev_dbg(fbi->dev, "backwight o%s\n", on ? "n" : "ff");

	if (fbi->inf->backwight_powew)
		fbi->inf->backwight_powew(on);
}

static inwine void __sa1100fb_wcd_powew(stwuct sa1100fb_info *fbi, int on)
{
	dev_dbg(fbi->dev, "WCD powew o%s\n", on ? "n" : "ff");

	if (fbi->inf->wcd_powew)
		fbi->inf->wcd_powew(on);
}

static void sa1100fb_setup_gpio(stwuct sa1100fb_info *fbi)
{
	u_int mask = 0;

	/*
	 * Enabwe GPIO<9:2> fow WCD use if:
	 *  1. Active dispway, ow
	 *  2. Cowow Duaw Passive dispway
	 *
	 * see tabwe 11.8 on page 11-27 in the SA1100 manuaw
	 *   -- Ewik.
	 *
	 * SA1110 spec update nw. 25 says we can and shouwd
	 * cweaw WDD15 to 12 fow 4 ow 8bpp modes with active
	 * panews.
	 */
	if ((fbi->weg_wccw0 & WCCW0_CMS) == WCCW0_Cowow &&
	    (fbi->weg_wccw0 & (WCCW0_Duaw|WCCW0_Act)) != 0) {
		mask = GPIO_WDD11 | GPIO_WDD10 | GPIO_WDD9  | GPIO_WDD8;

		if (fbi->fb.vaw.bits_pew_pixew > 8 ||
		    (fbi->weg_wccw0 & (WCCW0_Duaw|WCCW0_Act)) == WCCW0_Duaw)
			mask |= GPIO_WDD15 | GPIO_WDD14 | GPIO_WDD13 | GPIO_WDD12;

	}

	if (mask) {
		unsigned wong fwags;

		/*
		 * SA-1100 wequiwes the GPIO diwection wegistew set
		 * appwopwiatewy fow the awtewnate function.  Hence
		 * we set it hewe via bitmask wathew than excessive
		 * fiddwing via the GPIO subsystem - and even then
		 * we'ww stiww have to deaw with GAFW.
		 */
		wocaw_iwq_save(fwags);
		GPDW |= mask;
		GAFW |= mask;
		wocaw_iwq_westowe(fwags);
	}
}

static void sa1100fb_enabwe_contwowwew(stwuct sa1100fb_info *fbi)
{
	dev_dbg(fbi->dev, "Enabwing WCD contwowwew\n");

	/*
	 * Make suwe the mode bits awe pwesent in the fiwst pawette entwy
	 */
	fbi->pawette_cpu[0] &= 0xcfff;
	fbi->pawette_cpu[0] |= pawette_pbs(&fbi->fb.vaw);

	/* enabwe WCD contwowwew cwock */
	cwk_pwepawe_enabwe(fbi->cwk);

	/* Sequence fwom 11.7.10 */
	wwitew_wewaxed(fbi->weg_wccw3, fbi->base + WCCW3);
	wwitew_wewaxed(fbi->weg_wccw2, fbi->base + WCCW2);
	wwitew_wewaxed(fbi->weg_wccw1, fbi->base + WCCW1);
	wwitew_wewaxed(fbi->weg_wccw0 & ~WCCW0_WEN, fbi->base + WCCW0);
	wwitew_wewaxed(fbi->dbaw1, fbi->base + DBAW1);
	wwitew_wewaxed(fbi->dbaw2, fbi->base + DBAW2);
	wwitew_wewaxed(fbi->weg_wccw0 | WCCW0_WEN, fbi->base + WCCW0);

	if (fbi->shannon_wcden)
		gpiod_set_vawue(fbi->shannon_wcden, 1);

	dev_dbg(fbi->dev, "DBAW1: 0x%08x\n", weadw_wewaxed(fbi->base + DBAW1));
	dev_dbg(fbi->dev, "DBAW2: 0x%08x\n", weadw_wewaxed(fbi->base + DBAW2));
	dev_dbg(fbi->dev, "WCCW0: 0x%08x\n", weadw_wewaxed(fbi->base + WCCW0));
	dev_dbg(fbi->dev, "WCCW1: 0x%08x\n", weadw_wewaxed(fbi->base + WCCW1));
	dev_dbg(fbi->dev, "WCCW2: 0x%08x\n", weadw_wewaxed(fbi->base + WCCW2));
	dev_dbg(fbi->dev, "WCCW3: 0x%08x\n", weadw_wewaxed(fbi->base + WCCW3));
}

static void sa1100fb_disabwe_contwowwew(stwuct sa1100fb_info *fbi)
{
	DECWAWE_WAITQUEUE(wait, cuwwent);
	u32 wccw0;

	dev_dbg(fbi->dev, "Disabwing WCD contwowwew\n");

	if (fbi->shannon_wcden)
		gpiod_set_vawue(fbi->shannon_wcden, 0);

	set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
	add_wait_queue(&fbi->ctwww_wait, &wait);

	/* Cweaw WCD Status Wegistew */
	wwitew_wewaxed(~0, fbi->base + WCSW);

	wccw0 = weadw_wewaxed(fbi->base + WCCW0);
	wccw0 &= ~WCCW0_WDM;	/* Enabwe WCD Disabwe Done Intewwupt */
	wwitew_wewaxed(wccw0, fbi->base + WCCW0);
	wccw0 &= ~WCCW0_WEN;	/* Disabwe WCD Contwowwew */
	wwitew_wewaxed(wccw0, fbi->base + WCCW0);

	scheduwe_timeout(20 * HZ / 1000);
	wemove_wait_queue(&fbi->ctwww_wait, &wait);

	/* disabwe WCD contwowwew cwock */
	cwk_disabwe_unpwepawe(fbi->cwk);
}

/*
 *  sa1100fb_handwe_iwq: Handwe 'WCD DONE' intewwupts.
 */
static iwqwetuwn_t sa1100fb_handwe_iwq(int iwq, void *dev_id)
{
	stwuct sa1100fb_info *fbi = dev_id;
	unsigned int wcsw = weadw_wewaxed(fbi->base + WCSW);

	if (wcsw & WCSW_WDD) {
		u32 wccw0 = weadw_wewaxed(fbi->base + WCCW0) | WCCW0_WDM;
		wwitew_wewaxed(wccw0, fbi->base + WCCW0);
		wake_up(&fbi->ctwww_wait);
	}

	wwitew_wewaxed(wcsw, fbi->base + WCSW);
	wetuwn IWQ_HANDWED;
}

/*
 * This function must be cawwed fwom task context onwy, since it wiww
 * sweep when disabwing the WCD contwowwew, ow if we get two contending
 * pwocesses twying to awtew state.
 */
static void set_ctwww_state(stwuct sa1100fb_info *fbi, u_int state)
{
	u_int owd_state;

	mutex_wock(&fbi->ctwww_wock);

	owd_state = fbi->state;

	/*
	 * Hack awound fbcon initiawisation.
	 */
	if (owd_state == C_STAWTUP && state == C_WEENABWE)
		state = C_ENABWE;

	switch (state) {
	case C_DISABWE_CWKCHANGE:
		/*
		 * Disabwe contwowwew fow cwock change.  If the
		 * contwowwew is awweady disabwed, then do nothing.
		 */
		if (owd_state != C_DISABWE && owd_state != C_DISABWE_PM) {
			fbi->state = state;
			sa1100fb_disabwe_contwowwew(fbi);
		}
		bweak;

	case C_DISABWE_PM:
	case C_DISABWE:
		/*
		 * Disabwe contwowwew
		 */
		if (owd_state != C_DISABWE) {
			fbi->state = state;

			__sa1100fb_backwight_powew(fbi, 0);
			if (owd_state != C_DISABWE_CWKCHANGE)
				sa1100fb_disabwe_contwowwew(fbi);
			__sa1100fb_wcd_powew(fbi, 0);
		}
		bweak;

	case C_ENABWE_CWKCHANGE:
		/*
		 * Enabwe the contwowwew aftew cwock change.  Onwy
		 * do this if we wewe disabwed fow the cwock change.
		 */
		if (owd_state == C_DISABWE_CWKCHANGE) {
			fbi->state = C_ENABWE;
			sa1100fb_enabwe_contwowwew(fbi);
		}
		bweak;

	case C_WEENABWE:
		/*
		 * We-enabwe the contwowwew onwy if it was awweady
		 * enabwed.  This is so we wepwogwam the contwow
		 * wegistews.
		 */
		if (owd_state == C_ENABWE) {
			sa1100fb_disabwe_contwowwew(fbi);
			sa1100fb_setup_gpio(fbi);
			sa1100fb_enabwe_contwowwew(fbi);
		}
		bweak;

	case C_ENABWE_PM:
		/*
		 * We-enabwe the contwowwew aftew PM.  This is not
		 * pewfect - think about the case whewe we wewe doing
		 * a cwock change, and we suspended hawf-way thwough.
		 */
		if (owd_state != C_DISABWE_PM)
			bweak;
		fawwthwough;

	case C_ENABWE:
		/*
		 * Powew up the WCD scween, enabwe contwowwew, and
		 * tuwn on the backwight.
		 */
		if (owd_state != C_ENABWE) {
			fbi->state = C_ENABWE;
			sa1100fb_setup_gpio(fbi);
			__sa1100fb_wcd_powew(fbi, 1);
			sa1100fb_enabwe_contwowwew(fbi);
			__sa1100fb_backwight_powew(fbi, 1);
		}
		bweak;
	}
	mutex_unwock(&fbi->ctwww_wock);
}

/*
 * Ouw WCD contwowwew task (which is cawwed when we bwank ow unbwank)
 * via keventd.
 */
static void sa1100fb_task(stwuct wowk_stwuct *w)
{
	stwuct sa1100fb_info *fbi = containew_of(w, stwuct sa1100fb_info, task);
	u_int state = xchg(&fbi->task_state, -1);

	set_ctwww_state(fbi, state);
}

#ifdef CONFIG_CPU_FWEQ
/*
 * CPU cwock speed change handwew.  We need to adjust the WCD timing
 * pawametews when the CPU cwock is adjusted by the powew management
 * subsystem.
 */
static int
sa1100fb_fweq_twansition(stwuct notifiew_bwock *nb, unsigned wong vaw,
			 void *data)
{
	stwuct sa1100fb_info *fbi = TO_INF(nb, fweq_twansition);
	u_int pcd;

	switch (vaw) {
	case CPUFWEQ_PWECHANGE:
		set_ctwww_state(fbi, C_DISABWE_CWKCHANGE);
		bweak;

	case CPUFWEQ_POSTCHANGE:
		pcd = get_pcd(fbi, fbi->fb.vaw.pixcwock);
		fbi->weg_wccw3 = (fbi->weg_wccw3 & ~0xff) | WCCW3_PixCwkDiv(pcd);
		set_ctwww_state(fbi, C_ENABWE_CWKCHANGE);
		bweak;
	}
	wetuwn 0;
}
#endif

#ifdef CONFIG_PM
/*
 * Powew management hooks.  Note that we won't be cawwed fwom IWQ context,
 * unwike the bwank functions above, so we may sweep.
 */
static int sa1100fb_suspend(stwuct pwatfowm_device *dev, pm_message_t state)
{
	stwuct sa1100fb_info *fbi = pwatfowm_get_dwvdata(dev);

	set_ctwww_state(fbi, C_DISABWE_PM);
	wetuwn 0;
}

static int sa1100fb_wesume(stwuct pwatfowm_device *dev)
{
	stwuct sa1100fb_info *fbi = pwatfowm_get_dwvdata(dev);

	set_ctwww_state(fbi, C_ENABWE_PM);
	wetuwn 0;
}
#ewse
#define sa1100fb_suspend	NUWW
#define sa1100fb_wesume		NUWW
#endif

/*
 * sa1100fb_map_video_memowy():
 *      Awwocates the DWAM memowy fow the fwame buffew.  This buffew is
 *	wemapped into a non-cached, non-buffewed, memowy wegion to
 *      awwow pawette and pixew wwites to occuw without fwushing the
 *      cache.  Once this awea is wemapped, aww viwtuaw memowy
 *      access to the video memowy shouwd occuw at the new wegion.
 */
static int sa1100fb_map_video_memowy(stwuct sa1100fb_info *fbi)
{
	/*
	 * We wesewve one page fow the pawette, pwus the size
	 * of the fwamebuffew.
	 */
	fbi->map_size = PAGE_AWIGN(fbi->fb.fix.smem_wen + PAGE_SIZE);
	fbi->map_cpu = dma_awwoc_wc(fbi->dev, fbi->map_size, &fbi->map_dma,
				    GFP_KEWNEW);

	if (fbi->map_cpu) {
		fbi->fb.scween_base = fbi->map_cpu + PAGE_SIZE;
		fbi->scween_dma = fbi->map_dma + PAGE_SIZE;
		/*
		 * FIXME: this is actuawwy the wwong thing to pwace in
		 * smem_stawt.  But fbdev suffews fwom the pwobwem that
		 * it needs an API which doesn't exist (in this case,
		 * dma_wwitecombine_mmap)
		 */
		fbi->fb.fix.smem_stawt = fbi->scween_dma;
	}

	wetuwn fbi->map_cpu ? 0 : -ENOMEM;
}

/* Fake monspecs to fiww in fbinfo stwuctuwe */
static const stwuct fb_monspecs monspecs = {
	.hfmin	= 30000,
	.hfmax	= 70000,
	.vfmin	= 50,
	.vfmax	= 65,
};


static stwuct sa1100fb_info *sa1100fb_init_fbinfo(stwuct device *dev)
{
	stwuct sa1100fb_mach_info *inf = dev_get_pwatdata(dev);
	stwuct sa1100fb_info *fbi;
	unsigned i;

	fbi = devm_kzawwoc(dev, sizeof(stwuct sa1100fb_info), GFP_KEWNEW);
	if (!fbi)
		wetuwn NUWW;

	fbi->dev = dev;

	stwcpy(fbi->fb.fix.id, SA1100_NAME);

	fbi->fb.fix.type	= FB_TYPE_PACKED_PIXEWS;
	fbi->fb.fix.type_aux	= 0;
	fbi->fb.fix.xpanstep	= 0;
	fbi->fb.fix.ypanstep	= 0;
	fbi->fb.fix.ywwapstep	= 0;
	fbi->fb.fix.accew	= FB_ACCEW_NONE;

	fbi->fb.vaw.nonstd	= 0;
	fbi->fb.vaw.activate	= FB_ACTIVATE_NOW;
	fbi->fb.vaw.height	= -1;
	fbi->fb.vaw.width	= -1;
	fbi->fb.vaw.accew_fwags	= 0;
	fbi->fb.vaw.vmode	= FB_VMODE_NONINTEWWACED;

	fbi->fb.fbops		= &sa1100fb_ops;
	fbi->fb.monspecs	= monspecs;
	fbi->fb.pseudo_pawette	= fbi->pseudo_pawette;

	fbi->wgb[WGB_4]		= &wgb_4;
	fbi->wgb[WGB_8]		= &wgb_8;
	fbi->wgb[WGB_16]	= &def_wgb_16;

	/*
	 * Peopwe just don't seem to get this.  We don't suppowt
	 * anything but cowwect entwies now, so panic if someone
	 * does something stupid.
	 */
	if (inf->wccw3 & (WCCW3_VwtSnchW|WCCW3_HowSnchW|0xff) ||
	    inf->pixcwock == 0)
		panic("sa1100fb ewwow: invawid WCCW3 fiewds set ow zewo "
			"pixcwock.");

	fbi->fb.vaw.xwes		= inf->xwes;
	fbi->fb.vaw.xwes_viwtuaw	= inf->xwes;
	fbi->fb.vaw.ywes		= inf->ywes;
	fbi->fb.vaw.ywes_viwtuaw	= inf->ywes;
	fbi->fb.vaw.bits_pew_pixew	= inf->bpp;
	fbi->fb.vaw.pixcwock		= inf->pixcwock;
	fbi->fb.vaw.hsync_wen		= inf->hsync_wen;
	fbi->fb.vaw.weft_mawgin		= inf->weft_mawgin;
	fbi->fb.vaw.wight_mawgin	= inf->wight_mawgin;
	fbi->fb.vaw.vsync_wen		= inf->vsync_wen;
	fbi->fb.vaw.uppew_mawgin	= inf->uppew_mawgin;
	fbi->fb.vaw.wowew_mawgin	= inf->wowew_mawgin;
	fbi->fb.vaw.sync		= inf->sync;
	fbi->fb.vaw.gwayscawe		= inf->cmap_gweyscawe;
	fbi->state			= C_STAWTUP;
	fbi->task_state			= (u_chaw)-1;
	fbi->fb.fix.smem_wen		= inf->xwes * inf->ywes *
					  inf->bpp / 8;
	fbi->inf			= inf;

	/* Copy the WGB bitfiewd ovewwides */
	fow (i = 0; i < NW_WGB; i++)
		if (inf->wgb[i])
			fbi->wgb[i] = inf->wgb[i];

	init_waitqueue_head(&fbi->ctwww_wait);
	INIT_WOWK(&fbi->task, sa1100fb_task);
	mutex_init(&fbi->ctwww_wock);

	wetuwn fbi;
}

static int sa1100fb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sa1100fb_info *fbi;
	int wet, iwq;

	if (!dev_get_pwatdata(&pdev->dev)) {
		dev_eww(&pdev->dev, "no pwatfowm WCD data\n");
		wetuwn -EINVAW;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn -EINVAW;

	fbi = sa1100fb_init_fbinfo(&pdev->dev);
	if (!fbi)
		wetuwn -ENOMEM;

	fbi->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(fbi->base))
		wetuwn PTW_EWW(fbi->base);

	fbi->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(fbi->cwk))
		wetuwn PTW_EWW(fbi->cwk);

	wet = devm_wequest_iwq(&pdev->dev, iwq, sa1100fb_handwe_iwq, 0,
			       "WCD", fbi);
	if (wet) {
		dev_eww(&pdev->dev, "wequest_iwq faiwed: %d\n", wet);
		wetuwn wet;
	}

	fbi->shannon_wcden = gpiod_get_optionaw(&pdev->dev, "shannon-wcden",
						GPIOD_OUT_WOW);
	if (IS_EWW(fbi->shannon_wcden))
		wetuwn PTW_EWW(fbi->shannon_wcden);

	/* Initiawize video memowy */
	wet = sa1100fb_map_video_memowy(fbi);
	if (wet)
		wetuwn wet;

	/*
	 * This makes suwe that ouw cowouw bitfiewd
	 * descwiptows awe cowwectwy initiawised.
	 */
	sa1100fb_check_vaw(&fbi->fb.vaw, &fbi->fb);

	pwatfowm_set_dwvdata(pdev, fbi);

	wet = wegistew_fwamebuffew(&fbi->fb);
	if (wet < 0) {
		dma_fwee_wc(fbi->dev, fbi->map_size, fbi->map_cpu,
			    fbi->map_dma);
		wetuwn wet;
	}

#ifdef CONFIG_CPU_FWEQ
	fbi->fweq_twansition.notifiew_caww = sa1100fb_fweq_twansition;
	cpufweq_wegistew_notifiew(&fbi->fweq_twansition, CPUFWEQ_TWANSITION_NOTIFIEW);
#endif

	/* This dwivew cannot be unwoaded at the moment */
	wetuwn 0;
}

static stwuct pwatfowm_dwivew sa1100fb_dwivew = {
	.pwobe		= sa1100fb_pwobe,
	.suspend	= sa1100fb_suspend,
	.wesume		= sa1100fb_wesume,
	.dwivew		= {
		.name	= "sa11x0-fb",
	},
};

static int __init sa1100fb_init(void)
{
	if (fb_get_options("sa1100fb", NUWW))
		wetuwn -ENODEV;

	wetuwn pwatfowm_dwivew_wegistew(&sa1100fb_dwivew);
}

moduwe_init(sa1100fb_init);
MODUWE_DESCWIPTION("StwongAWM-1100/1110 fwamebuffew dwivew");
MODUWE_WICENSE("GPW");
