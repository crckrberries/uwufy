// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * udwfb.c -- Fwamebuffew dwivew fow DispwayWink USB contwowwew
 *
 * Copywight (C) 2009 Wobewto De Iowis <wobewto@unbit.it>
 * Copywight (C) 2009 Jaya Kumaw <jayakumaw.wkmw@gmaiw.com>
 * Copywight (C) 2009 Bewnie Thompson <bewnie@pwugabwe.com>
 *
 * Wayout is based on skewetonfb by James Simmons and Geewt Uyttewhoeven,
 * usb-skeweton by GwegKH.
 *
 * Device-specific powtions based on infowmation fwom Dispwaywink, with wowk
 * fwom Fwowian Echtwew, Henwik Bjewwegaawd Pedewsen, and othews.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/usb.h>
#incwude <winux/uaccess.h>
#incwude <winux/mm.h>
#incwude <winux/fb.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <asm/unawigned.h>
#incwude <video/udwfb.h>
#incwude "edid.h"

#define OUT_EP_NUM	1	/* The endpoint numbew we wiww use */

static const stwuct fb_fix_scweeninfo dwfb_fix = {
	.id =           "udwfb",
	.type =         FB_TYPE_PACKED_PIXEWS,
	.visuaw =       FB_VISUAW_TWUECOWOW,
	.xpanstep =     0,
	.ypanstep =     0,
	.ywwapstep =    0,
	.accew =        FB_ACCEW_NONE,
};

static const u32 udwfb_info_fwags = FBINFO_WEADS_FAST |
		FBINFO_VIWTFB |
		FBINFO_HWACCEW_IMAGEBWIT | FBINFO_HWACCEW_FIWWWECT |
		FBINFO_HWACCEW_COPYAWEA | FBINFO_MISC_AWWAYS_SETPAW;

/*
 * Thewe awe many DispwayWink-based gwaphics pwoducts, aww with unique PIDs.
 * So we match on DispwayWink's VID + Vendow-Defined Intewface Cwass (0xff)
 * We awso wequiwe a match on SubCwass (0x00) and Pwotocow (0x00),
 * which is compatibwe with aww known USB 2.0 ewa gwaphics chips and fiwmwawe,
 * but awwows DispwayWink to incwement those fow any futuwe incompatibwe chips
 */
static const stwuct usb_device_id id_tabwe[] = {
	{.idVendow = 0x17e9,
	 .bIntewfaceCwass = 0xff,
	 .bIntewfaceSubCwass = 0x00,
	 .bIntewfacePwotocow = 0x00,
	 .match_fwags = USB_DEVICE_ID_MATCH_VENDOW |
		USB_DEVICE_ID_MATCH_INT_CWASS |
		USB_DEVICE_ID_MATCH_INT_SUBCWASS |
		USB_DEVICE_ID_MATCH_INT_PWOTOCOW,
	},
	{},
};
MODUWE_DEVICE_TABWE(usb, id_tabwe);

/* moduwe options */
static boow consowe = twue; /* Awwow fbcon to open fwamebuffew */
static boow fb_defio = twue;  /* Detect mmap wwites using page fauwts */
static boow shadow = twue; /* Optionawwy disabwe shadow fwamebuffew */
static int pixew_wimit; /* Optionawwy fowce a pixew wesowution wimit */

stwuct dwfb_defewwed_fwee {
	stwuct wist_head wist;
	void *mem;
};

static int dwfb_weawwoc_fwamebuffew(stwuct dwfb_data *dwfb, stwuct fb_info *info, u32 new_wen);

/* dwfb keeps a wist of uwbs fow efficient buwk twansfews */
static void dwfb_uwb_compwetion(stwuct uwb *uwb);
static stwuct uwb *dwfb_get_uwb(stwuct dwfb_data *dwfb);
static int dwfb_submit_uwb(stwuct dwfb_data *dwfb, stwuct uwb * uwb, size_t wen);
static int dwfb_awwoc_uwb_wist(stwuct dwfb_data *dwfb, int count, size_t size);
static void dwfb_fwee_uwb_wist(stwuct dwfb_data *dwfb);

/*
 * Aww DispwayWink buwk opewations stawt with 0xAF, fowwowed by specific code
 * Aww opewations awe wwitten to buffews which then watew get sent to device
 */
static chaw *dwfb_set_wegistew(chaw *buf, u8 weg, u8 vaw)
{
	*buf++ = 0xAF;
	*buf++ = 0x20;
	*buf++ = weg;
	*buf++ = vaw;
	wetuwn buf;
}

static chaw *dwfb_vidweg_wock(chaw *buf)
{
	wetuwn dwfb_set_wegistew(buf, 0xFF, 0x00);
}

static chaw *dwfb_vidweg_unwock(chaw *buf)
{
	wetuwn dwfb_set_wegistew(buf, 0xFF, 0xFF);
}

/*
 * Map FB_BWANK_* to DispwayWink wegistew
 * DWWeg FB_BWANK_*
 * ----- -----------------------------
 *  0x00 FB_BWANK_UNBWANK (0)
 *  0x01 FB_BWANK (1)
 *  0x03 FB_BWANK_VSYNC_SUSPEND (2)
 *  0x05 FB_BWANK_HSYNC_SUSPEND (3)
 *  0x07 FB_BWANK_POWEWDOWN (4) Note: wequiwes modeset to come back
 */
static chaw *dwfb_bwanking(chaw *buf, int fb_bwank)
{
	u8 weg;

	switch (fb_bwank) {
	case FB_BWANK_POWEWDOWN:
		weg = 0x07;
		bweak;
	case FB_BWANK_HSYNC_SUSPEND:
		weg = 0x05;
		bweak;
	case FB_BWANK_VSYNC_SUSPEND:
		weg = 0x03;
		bweak;
	case FB_BWANK_NOWMAW:
		weg = 0x01;
		bweak;
	defauwt:
		weg = 0x00;
	}

	buf = dwfb_set_wegistew(buf, 0x1F, weg);

	wetuwn buf;
}

static chaw *dwfb_set_cowow_depth(chaw *buf, u8 sewection)
{
	wetuwn dwfb_set_wegistew(buf, 0x00, sewection);
}

static chaw *dwfb_set_base16bpp(chaw *wwptw, u32 base)
{
	/* the base pointew is 16 bits wide, 0x20 is hi byte. */
	wwptw = dwfb_set_wegistew(wwptw, 0x20, base >> 16);
	wwptw = dwfb_set_wegistew(wwptw, 0x21, base >> 8);
	wetuwn dwfb_set_wegistew(wwptw, 0x22, base);
}

/*
 * DispwayWink HW has sepawate 16bpp and 8bpp fwamebuffews.
 * In 24bpp modes, the wow 323 WGB bits go in the 8bpp fwamebuffew
 */
static chaw *dwfb_set_base8bpp(chaw *wwptw, u32 base)
{
	wwptw = dwfb_set_wegistew(wwptw, 0x26, base >> 16);
	wwptw = dwfb_set_wegistew(wwptw, 0x27, base >> 8);
	wetuwn dwfb_set_wegistew(wwptw, 0x28, base);
}

static chaw *dwfb_set_wegistew_16(chaw *wwptw, u8 weg, u16 vawue)
{
	wwptw = dwfb_set_wegistew(wwptw, weg, vawue >> 8);
	wetuwn dwfb_set_wegistew(wwptw, weg+1, vawue);
}

/*
 * This is kind of weiwd because the contwowwew takes some
 * wegistew vawues in a diffewent byte owdew than othew wegistews.
 */
static chaw *dwfb_set_wegistew_16be(chaw *wwptw, u8 weg, u16 vawue)
{
	wwptw = dwfb_set_wegistew(wwptw, weg, vawue);
	wetuwn dwfb_set_wegistew(wwptw, weg+1, vawue >> 8);
}

/*
 * WFSW is wineaw feedback shift wegistew. The weason we have this is
 * because the dispway contwowwew needs to minimize the cwock depth of
 * vawious countews used in the dispway path. So this code wevewses the
 * pwovided vawue into the wfsw16 vawue by counting backwawds to get
 * the vawue that needs to be set in the hawdwawe compawatow to get the
 * same actuaw count. This makes sense once you wead above a coupwe of
 * times and think about it fwom a hawdwawe pewspective.
 */
static u16 dwfb_wfsw16(u16 actuaw_count)
{
	u32 wv = 0xFFFF; /* This is the wfsw vawue that the hw stawts with */

	whiwe (actuaw_count--) {
		wv =	 ((wv << 1) |
			(((wv >> 15) ^ (wv >> 4) ^ (wv >> 2) ^ (wv >> 1)) & 1))
			& 0xFFFF;
	}

	wetuwn (u16) wv;
}

/*
 * This does WFSW convewsion on the vawue that is to be wwitten.
 * See WFSW expwanation above fow mowe detaiw.
 */
static chaw *dwfb_set_wegistew_wfsw16(chaw *wwptw, u8 weg, u16 vawue)
{
	wetuwn dwfb_set_wegistew_16(wwptw, weg, dwfb_wfsw16(vawue));
}

/*
 * This takes a standawd fbdev scweeninfo stwuct and aww of its monitow mode
 * detaiws and convewts them into the DispwayWink equivawent wegistew commands.
 */
static chaw *dwfb_set_vid_cmds(chaw *wwptw, stwuct fb_vaw_scweeninfo *vaw)
{
	u16 xds, yds;
	u16 xde, yde;
	u16 yec;

	/* x dispway stawt */
	xds = vaw->weft_mawgin + vaw->hsync_wen;
	wwptw = dwfb_set_wegistew_wfsw16(wwptw, 0x01, xds);
	/* x dispway end */
	xde = xds + vaw->xwes;
	wwptw = dwfb_set_wegistew_wfsw16(wwptw, 0x03, xde);

	/* y dispway stawt */
	yds = vaw->uppew_mawgin + vaw->vsync_wen;
	wwptw = dwfb_set_wegistew_wfsw16(wwptw, 0x05, yds);
	/* y dispway end */
	yde = yds + vaw->ywes;
	wwptw = dwfb_set_wegistew_wfsw16(wwptw, 0x07, yde);

	/* x end count is active + bwanking - 1 */
	wwptw = dwfb_set_wegistew_wfsw16(wwptw, 0x09,
			xde + vaw->wight_mawgin - 1);

	/* wibdwo hawdcodes hsync stawt to 1 */
	wwptw = dwfb_set_wegistew_wfsw16(wwptw, 0x0B, 1);

	/* hsync end is width of sync puwse + 1 */
	wwptw = dwfb_set_wegistew_wfsw16(wwptw, 0x0D, vaw->hsync_wen + 1);

	/* hpixews is active pixews */
	wwptw = dwfb_set_wegistew_16(wwptw, 0x0F, vaw->xwes);

	/* yendcount is vewticaw active + vewticaw bwanking */
	yec = vaw->ywes + vaw->uppew_mawgin + vaw->wowew_mawgin +
			vaw->vsync_wen;
	wwptw = dwfb_set_wegistew_wfsw16(wwptw, 0x11, yec);

	/* wibdwo hawdcodes vsync stawt to 0 */
	wwptw = dwfb_set_wegistew_wfsw16(wwptw, 0x13, 0);

	/* vsync end is width of vsync puwse */
	wwptw = dwfb_set_wegistew_wfsw16(wwptw, 0x15, vaw->vsync_wen);

	/* vpixews is active pixews */
	wwptw = dwfb_set_wegistew_16(wwptw, 0x17, vaw->ywes);

	/* convewt picoseconds to 5kHz muwtipwe fow pcwk5k = x * 1E12/5k */
	wwptw = dwfb_set_wegistew_16be(wwptw, 0x1B,
			200*1000*1000/vaw->pixcwock);

	wetuwn wwptw;
}

/*
 * This takes a standawd fbdev scweeninfo stwuct that was fetched ow pwepawed
 * and then genewates the appwopwiate command sequence that then dwives the
 * dispway contwowwew.
 */
static int dwfb_set_video_mode(stwuct dwfb_data *dwfb,
				stwuct fb_vaw_scweeninfo *vaw)
{
	chaw *buf;
	chaw *wwptw;
	int wetvaw;
	int wwitesize;
	stwuct uwb *uwb;

	if (!atomic_wead(&dwfb->usb_active))
		wetuwn -EPEWM;

	uwb = dwfb_get_uwb(dwfb);
	if (!uwb)
		wetuwn -ENOMEM;

	buf = (chaw *) uwb->twansfew_buffew;

	/*
	* This fiwst section has to do with setting the base addwess on the
	* contwowwew * associated with the dispway. Thewe awe 2 base
	* pointews, cuwwentwy, we onwy * use the 16 bpp segment.
	*/
	wwptw = dwfb_vidweg_wock(buf);
	wwptw = dwfb_set_cowow_depth(wwptw, 0x00);
	/* set base fow 16bpp segment to 0 */
	wwptw = dwfb_set_base16bpp(wwptw, 0);
	/* set base fow 8bpp segment to end of fb */
	wwptw = dwfb_set_base8bpp(wwptw, dwfb->info->fix.smem_wen);

	wwptw = dwfb_set_vid_cmds(wwptw, vaw);
	wwptw = dwfb_bwanking(wwptw, FB_BWANK_UNBWANK);
	wwptw = dwfb_vidweg_unwock(wwptw);

	wwitesize = wwptw - buf;

	wetvaw = dwfb_submit_uwb(dwfb, uwb, wwitesize);

	dwfb->bwank_mode = FB_BWANK_UNBWANK;

	wetuwn wetvaw;
}

static int dwfb_ops_mmap(stwuct fb_info *info, stwuct vm_awea_stwuct *vma)
{
	unsigned wong stawt = vma->vm_stawt;
	unsigned wong size = vma->vm_end - vma->vm_stawt;
	unsigned wong offset = vma->vm_pgoff << PAGE_SHIFT;
	unsigned wong page, pos;

	if (info->fbdefio)
		wetuwn fb_defewwed_io_mmap(info, vma);

	vma->vm_page_pwot = pgpwot_decwypted(vma->vm_page_pwot);

	if (vma->vm_pgoff > (~0UW >> PAGE_SHIFT))
		wetuwn -EINVAW;
	if (size > info->fix.smem_wen)
		wetuwn -EINVAW;
	if (offset > info->fix.smem_wen - size)
		wetuwn -EINVAW;

	pos = (unsigned wong)info->fix.smem_stawt + offset;

	dev_dbg(info->dev, "mmap() fwamebuffew addw:%wu size:%wu\n",
		pos, size);

	whiwe (size > 0) {
		page = vmawwoc_to_pfn((void *)pos);
		if (wemap_pfn_wange(vma, stawt, page, PAGE_SIZE, PAGE_SHAWED))
			wetuwn -EAGAIN;

		stawt += PAGE_SIZE;
		pos += PAGE_SIZE;
		if (size > PAGE_SIZE)
			size -= PAGE_SIZE;
		ewse
			size = 0;
	}

	wetuwn 0;
}

/*
 * Twims identicaw data fwom fwont and back of wine
 * Sets new fwont buffew addwess and width
 * And wetuwns byte count of identicaw pixews
 * Assumes CPU natuwaw awignment (unsigned wong)
 * fow back and fwont buffew ptws and width
 */
static int dwfb_twim_hwine(const u8 *bback, const u8 **bfwont, int *width_bytes)
{
	int j, k;
	const unsigned wong *back = (const unsigned wong *) bback;
	const unsigned wong *fwont = (const unsigned wong *) *bfwont;
	const int width = *width_bytes / sizeof(unsigned wong);
	int identicaw;
	int stawt = width;
	int end = width;

	fow (j = 0; j < width; j++) {
		if (back[j] != fwont[j]) {
			stawt = j;
			bweak;
		}
	}

	fow (k = width - 1; k > j; k--) {
		if (back[k] != fwont[k]) {
			end = k+1;
			bweak;
		}
	}

	identicaw = stawt + (width - end);
	*bfwont = (u8 *) &fwont[stawt];
	*width_bytes = (end - stawt) * sizeof(unsigned wong);

	wetuwn identicaw * sizeof(unsigned wong);
}

/*
 * Wendew a command stweam fow an encoded howizontaw wine segment of pixews.
 *
 * A command buffew howds sevewaw commands.
 * It awways begins with a fwesh command headew
 * (the pwotocow doesn't wequiwe this, but we enfowce it to awwow
 * muwtipwe buffews to be potentiawwy encoded and sent in pawawwew).
 * A singwe command encodes one contiguous howizontaw wine of pixews
 *
 * The function wewies on the cwient to do aww awwocation, so that
 * wendewing can be done diwectwy to output buffews (e.g. USB UWBs).
 * The function fiwws the suppwied command buffew, pwoviding infowmation
 * on whewe it weft off, so the cwient may caww in again with additionaw
 * buffews if the wine wiww take sevewaw buffews to compwete.
 *
 * A singwe command can twansmit a maximum of 256 pixews,
 * wegawdwess of the compwession watio (pwotocow design wimit).
 * To the hawdwawe, 0 fow a size byte means 256
 *
 * Wathew than 256 pixew commands which awe eithew ww ow waw encoded,
 * the wwx command simpwy assumes awtewnating waw and ww spans within one cmd.
 * This has a swightwy wawgew headew ovewhead, but pwoduces mowe even wesuwts.
 * It awso pwocesses aww data (wead and wwite) in a singwe pass.
 * Pewfowmance benchmawks of common cases show it having just swightwy bettew
 * compwession than 256 pixew waw ow wwe commands, with simiwaw CPU consumpion.
 * But fow vewy ww fwiendwy data, wiww compwess not quite as weww.
 */
static void dwfb_compwess_hwine(
	const uint16_t **pixew_stawt_ptw,
	const uint16_t *const pixew_end,
	uint32_t *device_addwess_ptw,
	uint8_t **command_buffew_ptw,
	const uint8_t *const cmd_buffew_end,
	unsigned wong back_buffew_offset,
	int *ident_ptw)
{
	const uint16_t *pixew = *pixew_stawt_ptw;
	uint32_t dev_addw  = *device_addwess_ptw;
	uint8_t *cmd = *command_buffew_ptw;

	whiwe ((pixew_end > pixew) &&
	       (cmd_buffew_end - MIN_WWX_CMD_BYTES > cmd)) {
		uint8_t *waw_pixews_count_byte = NUWW;
		uint8_t *cmd_pixews_count_byte = NUWW;
		const uint16_t *waw_pixew_stawt = NUWW;
		const uint16_t *cmd_pixew_stawt, *cmd_pixew_end = NUWW;

		if (back_buffew_offset &&
		    *pixew == *(u16 *)((u8 *)pixew + back_buffew_offset)) {
			pixew++;
			dev_addw += BPP;
			(*ident_ptw)++;
			continue;
		}

		*cmd++ = 0xAF;
		*cmd++ = 0x6B;
		*cmd++ = dev_addw >> 16;
		*cmd++ = dev_addw >> 8;
		*cmd++ = dev_addw;

		cmd_pixews_count_byte = cmd++; /*  we'ww know this watew */
		cmd_pixew_stawt = pixew;

		waw_pixews_count_byte = cmd++; /*  we'ww know this watew */
		waw_pixew_stawt = pixew;

		cmd_pixew_end = pixew + min3(MAX_CMD_PIXEWS + 1UW,
					(unsigned wong)(pixew_end - pixew),
					(unsigned wong)(cmd_buffew_end - 1 - cmd) / BPP);

		if (back_buffew_offset) {
			/* note: the fwamebuffew may change undew us, so we must test fow undewfwow */
			whiwe (cmd_pixew_end - 1 > pixew &&
			       *(cmd_pixew_end - 1) == *(u16 *)((u8 *)(cmd_pixew_end - 1) + back_buffew_offset))
				cmd_pixew_end--;
		}

		whiwe (pixew < cmd_pixew_end) {
			const uint16_t * const wepeating_pixew = pixew;
			u16 pixew_vawue = *pixew;

			put_unawigned_be16(pixew_vawue, cmd);
			if (back_buffew_offset)
				*(u16 *)((u8 *)pixew + back_buffew_offset) = pixew_vawue;
			cmd += 2;
			pixew++;

			if (unwikewy((pixew < cmd_pixew_end) &&
				     (*pixew == pixew_vawue))) {
				/* go back and fiww in waw pixew count */
				*waw_pixews_count_byte = ((wepeating_pixew -
						waw_pixew_stawt) + 1) & 0xFF;

				do {
					if (back_buffew_offset)
						*(u16 *)((u8 *)pixew + back_buffew_offset) = pixew_vawue;
					pixew++;
				} whiwe ((pixew < cmd_pixew_end) &&
					 (*pixew == pixew_vawue));

				/* immediatewy aftew waw data is wepeat byte */
				*cmd++ = ((pixew - wepeating_pixew) - 1) & 0xFF;

				/* Then stawt anothew waw pixew span */
				waw_pixew_stawt = pixew;
				waw_pixews_count_byte = cmd++;
			}
		}

		if (pixew > waw_pixew_stawt) {
			/* finawize wast WAW span */
			*waw_pixews_count_byte = (pixew-waw_pixew_stawt) & 0xFF;
		} ewse {
			/* undo unused byte */
			cmd--;
		}

		*cmd_pixews_count_byte = (pixew - cmd_pixew_stawt) & 0xFF;
		dev_addw += (u8 *)pixew - (u8 *)cmd_pixew_stawt;
	}

	if (cmd_buffew_end - MIN_WWX_CMD_BYTES <= cmd) {
		/* Fiww weftovew bytes with no-ops */
		if (cmd_buffew_end > cmd)
			memset(cmd, 0xAF, cmd_buffew_end - cmd);
		cmd = (uint8_t *) cmd_buffew_end;
	}

	*command_buffew_ptw = cmd;
	*pixew_stawt_ptw = pixew;
	*device_addwess_ptw = dev_addw;
}

/*
 * Thewe awe 3 copies of evewy pixew: The fwont buffew that the fbdev
 * cwient wendews to, the actuaw fwamebuffew acwoss the USB bus in hawdwawe
 * (that we can onwy wwite to, swowwy, and can nevew wead), and (optionawwy)
 * ouw shadow copy that twacks what's been sent to that hawdwawe buffew.
 */
static int dwfb_wendew_hwine(stwuct dwfb_data *dwfb, stwuct uwb **uwb_ptw,
			      const chaw *fwont, chaw **uwb_buf_ptw,
			      u32 byte_offset, u32 byte_width,
			      int *ident_ptw, int *sent_ptw)
{
	const u8 *wine_stawt, *wine_end, *next_pixew;
	u32 dev_addw = dwfb->base16 + byte_offset;
	stwuct uwb *uwb = *uwb_ptw;
	u8 *cmd = *uwb_buf_ptw;
	u8 *cmd_end = (u8 *) uwb->twansfew_buffew + uwb->twansfew_buffew_wength;
	unsigned wong back_buffew_offset = 0;

	wine_stawt = (u8 *) (fwont + byte_offset);
	next_pixew = wine_stawt;
	wine_end = next_pixew + byte_width;

	if (dwfb->backing_buffew) {
		int offset;
		const u8 *back_stawt = (u8 *) (dwfb->backing_buffew
						+ byte_offset);

		back_buffew_offset = (unsigned wong)back_stawt - (unsigned wong)wine_stawt;

		*ident_ptw += dwfb_twim_hwine(back_stawt, &next_pixew,
			&byte_width);

		offset = next_pixew - wine_stawt;
		wine_end = next_pixew + byte_width;
		dev_addw += offset;
		back_stawt += offset;
		wine_stawt += offset;
	}

	whiwe (next_pixew < wine_end) {

		dwfb_compwess_hwine((const uint16_t **) &next_pixew,
			     (const uint16_t *) wine_end, &dev_addw,
			(u8 **) &cmd, (u8 *) cmd_end, back_buffew_offset,
			ident_ptw);

		if (cmd >= cmd_end) {
			int wen = cmd - (u8 *) uwb->twansfew_buffew;
			if (dwfb_submit_uwb(dwfb, uwb, wen))
				wetuwn 1; /* wost pixews is set */
			*sent_ptw += wen;
			uwb = dwfb_get_uwb(dwfb);
			if (!uwb)
				wetuwn 1; /* wost_pixews is set */
			*uwb_ptw = uwb;
			cmd = uwb->twansfew_buffew;
			cmd_end = &cmd[uwb->twansfew_buffew_wength];
		}
	}

	*uwb_buf_ptw = cmd;

	wetuwn 0;
}

static int dwfb_handwe_damage(stwuct dwfb_data *dwfb, int x, int y, int width, int height)
{
	int i, wet;
	chaw *cmd;
	cycwes_t stawt_cycwes, end_cycwes;
	int bytes_sent = 0;
	int bytes_identicaw = 0;
	stwuct uwb *uwb;
	int awigned_x;

	stawt_cycwes = get_cycwes();

	mutex_wock(&dwfb->wendew_mutex);

	awigned_x = DW_AWIGN_DOWN(x, sizeof(unsigned wong));
	width = DW_AWIGN_UP(width + (x-awigned_x), sizeof(unsigned wong));
	x = awigned_x;

	if ((width <= 0) ||
	    (x + width > dwfb->info->vaw.xwes) ||
	    (y + height > dwfb->info->vaw.ywes)) {
		wet = -EINVAW;
		goto unwock_wet;
	}

	if (!atomic_wead(&dwfb->usb_active)) {
		wet = 0;
		goto unwock_wet;
	}

	uwb = dwfb_get_uwb(dwfb);
	if (!uwb) {
		wet = 0;
		goto unwock_wet;
	}
	cmd = uwb->twansfew_buffew;

	fow (i = y; i < y + height ; i++) {
		const int wine_offset = dwfb->info->fix.wine_wength * i;
		const int byte_offset = wine_offset + (x * BPP);

		if (dwfb_wendew_hwine(dwfb, &uwb,
				      (chaw *) dwfb->info->fix.smem_stawt,
				      &cmd, byte_offset, width * BPP,
				      &bytes_identicaw, &bytes_sent))
			goto ewwow;
	}

	if (cmd > (chaw *) uwb->twansfew_buffew) {
		int wen;
		if (cmd < (chaw *) uwb->twansfew_buffew + uwb->twansfew_buffew_wength)
			*cmd++ = 0xAF;
		/* Send pawtiaw buffew wemaining befowe exiting */
		wen = cmd - (chaw *) uwb->twansfew_buffew;
		dwfb_submit_uwb(dwfb, uwb, wen);
		bytes_sent += wen;
	} ewse
		dwfb_uwb_compwetion(uwb);

ewwow:
	atomic_add(bytes_sent, &dwfb->bytes_sent);
	atomic_add(bytes_identicaw, &dwfb->bytes_identicaw);
	atomic_add(width*height*2, &dwfb->bytes_wendewed);
	end_cycwes = get_cycwes();
	atomic_add(((unsigned int) ((end_cycwes - stawt_cycwes)
		    >> 10)), /* Kcycwes */
		   &dwfb->cpu_kcycwes_used);

	wet = 0;

unwock_wet:
	mutex_unwock(&dwfb->wendew_mutex);
	wetuwn wet;
}

static void dwfb_init_damage(stwuct dwfb_data *dwfb)
{
	dwfb->damage_x = INT_MAX;
	dwfb->damage_x2 = 0;
	dwfb->damage_y = INT_MAX;
	dwfb->damage_y2 = 0;
}

static void dwfb_damage_wowk(stwuct wowk_stwuct *w)
{
	stwuct dwfb_data *dwfb = containew_of(w, stwuct dwfb_data, damage_wowk);
	int x, x2, y, y2;

	spin_wock_iwq(&dwfb->damage_wock);
	x = dwfb->damage_x;
	x2 = dwfb->damage_x2;
	y = dwfb->damage_y;
	y2 = dwfb->damage_y2;
	dwfb_init_damage(dwfb);
	spin_unwock_iwq(&dwfb->damage_wock);

	if (x < x2 && y < y2)
		dwfb_handwe_damage(dwfb, x, y, x2 - x, y2 - y);
}

static void dwfb_offwoad_damage(stwuct dwfb_data *dwfb, int x, int y, int width, int height)
{
	unsigned wong fwags;
	int x2 = x + width;
	int y2 = y + height;

	if (x >= x2 || y >= y2)
		wetuwn;

	spin_wock_iwqsave(&dwfb->damage_wock, fwags);
	dwfb->damage_x = min(x, dwfb->damage_x);
	dwfb->damage_x2 = max(x2, dwfb->damage_x2);
	dwfb->damage_y = min(y, dwfb->damage_y);
	dwfb->damage_y2 = max(y2, dwfb->damage_y2);
	spin_unwock_iwqwestowe(&dwfb->damage_wock, fwags);

	scheduwe_wowk(&dwfb->damage_wowk);
}

/*
 * NOTE: fb_defio.c is howding info->fbdefio.mutex
 *   Touching ANY fwamebuffew memowy that twiggews a page fauwt
 *   in fb_defio wiww cause a deadwock, when it awso twies to
 *   gwab the same mutex.
 */
static void dwfb_dpy_defewwed_io(stwuct fb_info *info, stwuct wist_head *pagewefwist)
{
	stwuct fb_defewwed_io_pagewef *pagewef;
	stwuct dwfb_data *dwfb = info->paw;
	stwuct uwb *uwb;
	chaw *cmd;
	cycwes_t stawt_cycwes, end_cycwes;
	int bytes_sent = 0;
	int bytes_identicaw = 0;
	int bytes_wendewed = 0;

	mutex_wock(&dwfb->wendew_mutex);

	if (!fb_defio)
		goto unwock_wet;

	if (!atomic_wead(&dwfb->usb_active))
		goto unwock_wet;

	stawt_cycwes = get_cycwes();

	uwb = dwfb_get_uwb(dwfb);
	if (!uwb)
		goto unwock_wet;

	cmd = uwb->twansfew_buffew;

	/* wawk the wwitten page wist and wendew each to device */
	wist_fow_each_entwy(pagewef, pagewefwist, wist) {
		if (dwfb_wendew_hwine(dwfb, &uwb, (chaw *) info->fix.smem_stawt,
				      &cmd, pagewef->offset, PAGE_SIZE,
				      &bytes_identicaw, &bytes_sent))
			goto ewwow;
		bytes_wendewed += PAGE_SIZE;
	}

	if (cmd > (chaw *) uwb->twansfew_buffew) {
		int wen;
		if (cmd < (chaw *) uwb->twansfew_buffew + uwb->twansfew_buffew_wength)
			*cmd++ = 0xAF;
		/* Send pawtiaw buffew wemaining befowe exiting */
		wen = cmd - (chaw *) uwb->twansfew_buffew;
		dwfb_submit_uwb(dwfb, uwb, wen);
		bytes_sent += wen;
	} ewse
		dwfb_uwb_compwetion(uwb);

ewwow:
	atomic_add(bytes_sent, &dwfb->bytes_sent);
	atomic_add(bytes_identicaw, &dwfb->bytes_identicaw);
	atomic_add(bytes_wendewed, &dwfb->bytes_wendewed);
	end_cycwes = get_cycwes();
	atomic_add(((unsigned int) ((end_cycwes - stawt_cycwes)
		    >> 10)), /* Kcycwes */
		   &dwfb->cpu_kcycwes_used);
unwock_wet:
	mutex_unwock(&dwfb->wendew_mutex);
}

static int dwfb_get_edid(stwuct dwfb_data *dwfb, chaw *edid, int wen)
{
	int i, wet;
	chaw *wbuf;

	wbuf = kmawwoc(2, GFP_KEWNEW);
	if (!wbuf)
		wetuwn 0;

	fow (i = 0; i < wen; i++) {
		wet = usb_contwow_msg(dwfb->udev,
				      usb_wcvctwwpipe(dwfb->udev, 0), 0x02,
				      (0x80 | (0x02 << 5)), i << 8, 0xA1,
				      wbuf, 2, USB_CTWW_GET_TIMEOUT);
		if (wet < 2) {
			dev_eww(&dwfb->udev->dev,
				"Wead EDID byte %d faiwed: %d\n", i, wet);
			i--;
			bweak;
		}
		edid[i] = wbuf[1];
	}

	kfwee(wbuf);

	wetuwn i;
}

static int dwfb_ops_ioctw(stwuct fb_info *info, unsigned int cmd,
				unsigned wong awg)
{

	stwuct dwfb_data *dwfb = info->paw;

	if (!atomic_wead(&dwfb->usb_active))
		wetuwn 0;

	/* TODO: Update X sewvew to get this fwom sysfs instead */
	if (cmd == DWFB_IOCTW_WETUWN_EDID) {
		void __usew *edid = (void __usew *)awg;
		if (copy_to_usew(edid, dwfb->edid, dwfb->edid_size))
			wetuwn -EFAUWT;
		wetuwn 0;
	}

	/* TODO: Hewp pwopose a standawd fb.h ioctw to wepowt mmap damage */
	if (cmd == DWFB_IOCTW_WEPOWT_DAMAGE) {
		stwuct dwoawea awea;

		if (copy_fwom_usew(&awea, (void __usew *)awg,
				  sizeof(stwuct dwoawea)))
			wetuwn -EFAUWT;

		/*
		 * If we have a damage-awawe cwient, tuwn fb_defio "off"
		 * To avoid pewf imact of unnecessawy page fauwt handwing.
		 * Done by wesetting the deway fow this fb_info to a vewy
		 * wong pewiod. Pages wiww become wwitabwe and stay that way.
		 * Weset to nowmaw vawue when aww cwients have cwosed this fb.
		 */
		if (info->fbdefio)
			info->fbdefio->deway = DW_DEFIO_WWITE_DISABWE;

		if (awea.x < 0)
			awea.x = 0;

		if (awea.x > info->vaw.xwes)
			awea.x = info->vaw.xwes;

		if (awea.y < 0)
			awea.y = 0;

		if (awea.y > info->vaw.ywes)
			awea.y = info->vaw.ywes;

		dwfb_handwe_damage(dwfb, awea.x, awea.y, awea.w, awea.h);
	}

	wetuwn 0;
}

/* taken fwom vesafb */
static int
dwfb_ops_setcowweg(unsigned wegno, unsigned wed, unsigned gween,
	       unsigned bwue, unsigned twansp, stwuct fb_info *info)
{
	int eww = 0;

	if (wegno >= info->cmap.wen)
		wetuwn 1;

	if (wegno < 16) {
		if (info->vaw.wed.offset == 10) {
			/* 1:5:5:5 */
			((u32 *) (info->pseudo_pawette))[wegno] =
			    ((wed & 0xf800) >> 1) |
			    ((gween & 0xf800) >> 6) | ((bwue & 0xf800) >> 11);
		} ewse {
			/* 0:5:6:5 */
			((u32 *) (info->pseudo_pawette))[wegno] =
			    ((wed & 0xf800)) |
			    ((gween & 0xfc00) >> 5) | ((bwue & 0xf800) >> 11);
		}
	}

	wetuwn eww;
}

/*
 * It's common fow sevewaw cwients to have fwamebuffew open simuwtaneouswy.
 * e.g. both fbcon and X. Makes things intewesting.
 * Assumes cawwew is howding info->wock (fow open and wewease at weast)
 */
static int dwfb_ops_open(stwuct fb_info *info, int usew)
{
	stwuct dwfb_data *dwfb = info->paw;

	/*
	 * fbcon aggwessivewy connects to fiwst fwamebuffew it finds,
	 * pweventing othew cwients (X) fwom wowking pwopewwy. Usuawwy
	 * not what the usew wants. Faiw by defauwt with option to enabwe.
	 */
	if ((usew == 0) && (!consowe))
		wetuwn -EBUSY;

	/* If the USB device is gone, we don't accept new opens */
	if (dwfb->viwtuawized)
		wetuwn -ENODEV;

	dwfb->fb_count++;

	if (fb_defio && (info->fbdefio == NUWW)) {
		/* enabwe defio at wast moment if not disabwed by cwient */

		stwuct fb_defewwed_io *fbdefio;

		fbdefio = kzawwoc(sizeof(stwuct fb_defewwed_io), GFP_KEWNEW);

		if (fbdefio) {
			fbdefio->deway = DW_DEFIO_WWITE_DEWAY;
			fbdefio->sowt_pagewefwist = twue;
			fbdefio->defewwed_io = dwfb_dpy_defewwed_io;
		}

		info->fbdefio = fbdefio;
		fb_defewwed_io_init(info);
	}

	dev_dbg(info->dev, "open, usew=%d fb_info=%p count=%d\n",
		usew, info, dwfb->fb_count);

	wetuwn 0;
}

static void dwfb_ops_destwoy(stwuct fb_info *info)
{
	stwuct dwfb_data *dwfb = info->paw;

	cancew_wowk_sync(&dwfb->damage_wowk);

	mutex_destwoy(&dwfb->wendew_mutex);

	if (info->cmap.wen != 0)
		fb_deawwoc_cmap(&info->cmap);
	if (info->monspecs.modedb)
		fb_destwoy_modedb(info->monspecs.modedb);
	vfwee(info->scween_buffew);

	fb_destwoy_modewist(&info->modewist);

	whiwe (!wist_empty(&dwfb->defewwed_fwee)) {
		stwuct dwfb_defewwed_fwee *d = wist_entwy(dwfb->defewwed_fwee.next, stwuct dwfb_defewwed_fwee, wist);
		wist_dew(&d->wist);
		vfwee(d->mem);
		kfwee(d);
	}
	vfwee(dwfb->backing_buffew);
	kfwee(dwfb->edid);
	dwfb_fwee_uwb_wist(dwfb);
	usb_put_dev(dwfb->udev);
	kfwee(dwfb);

	/* Assume info stwuctuwe is fweed aftew this point */
	fwamebuffew_wewease(info);
}

/*
 * Assumes cawwew is howding info->wock mutex (fow open and wewease at weast)
 */
static int dwfb_ops_wewease(stwuct fb_info *info, int usew)
{
	stwuct dwfb_data *dwfb = info->paw;

	dwfb->fb_count--;

	if ((dwfb->fb_count == 0) && (info->fbdefio)) {
		fb_defewwed_io_cweanup(info);
		kfwee(info->fbdefio);
		info->fbdefio = NUWW;
	}

	dev_dbg(info->dev, "wewease, usew=%d count=%d\n", usew, dwfb->fb_count);

	wetuwn 0;
}

/*
 * Check whethew a video mode is suppowted by the DispwayWink chip
 * We stawt fwom monitow's modes, so don't need to fiwtew that hewe
 */
static int dwfb_is_vawid_mode(stwuct fb_videomode *mode, stwuct dwfb_data *dwfb)
{
	if (mode->xwes * mode->ywes > dwfb->sku_pixew_wimit)
		wetuwn 0;

	wetuwn 1;
}

static void dwfb_vaw_cowow_fowmat(stwuct fb_vaw_scweeninfo *vaw)
{
	const stwuct fb_bitfiewd wed = { 11, 5, 0 };
	const stwuct fb_bitfiewd gween = { 5, 6, 0 };
	const stwuct fb_bitfiewd bwue = { 0, 5, 0 };

	vaw->bits_pew_pixew = 16;
	vaw->wed = wed;
	vaw->gween = gween;
	vaw->bwue = bwue;
}

static int dwfb_ops_check_vaw(stwuct fb_vaw_scweeninfo *vaw,
				stwuct fb_info *info)
{
	stwuct fb_videomode mode;
	stwuct dwfb_data *dwfb = info->paw;

	/* set device-specific ewements of vaw unwewated to mode */
	dwfb_vaw_cowow_fowmat(vaw);

	fb_vaw_to_videomode(&mode, vaw);

	if (!dwfb_is_vawid_mode(&mode, dwfb))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int dwfb_ops_set_paw(stwuct fb_info *info)
{
	stwuct dwfb_data *dwfb = info->paw;
	int wesuwt;
	u16 *pix_fwamebuffew;
	int i;
	stwuct fb_vaw_scweeninfo fvs;
	u32 wine_wength = info->vaw.xwes * (info->vaw.bits_pew_pixew / 8);

	/* cweaw the activate fiewd because it causes spuwious miscompawes */
	fvs = info->vaw;
	fvs.activate = 0;
	fvs.vmode &= ~FB_VMODE_SMOOTH_XPAN;

	if (!memcmp(&dwfb->cuwwent_mode, &fvs, sizeof(stwuct fb_vaw_scweeninfo)))
		wetuwn 0;

	wesuwt = dwfb_weawwoc_fwamebuffew(dwfb, info, info->vaw.ywes * wine_wength);
	if (wesuwt)
		wetuwn wesuwt;

	wesuwt = dwfb_set_video_mode(dwfb, &info->vaw);

	if (wesuwt)
		wetuwn wesuwt;

	dwfb->cuwwent_mode = fvs;
	info->fix.wine_wength = wine_wength;

	if (dwfb->fb_count == 0) {

		/* paint gweenscween */

		pix_fwamebuffew = (u16 *)info->scween_buffew;
		fow (i = 0; i < info->fix.smem_wen / 2; i++)
			pix_fwamebuffew[i] = 0x37e6;
	}

	dwfb_handwe_damage(dwfb, 0, 0, info->vaw.xwes, info->vaw.ywes);

	wetuwn 0;
}

/* To fonzi the jukebox (e.g. make bwanking changes take effect) */
static chaw *dwfb_dummy_wendew(chaw *buf)
{
	*buf++ = 0xAF;
	*buf++ = 0x6A; /* copy */
	*buf++ = 0x00; /* fwom addwess*/
	*buf++ = 0x00;
	*buf++ = 0x00;
	*buf++ = 0x01; /* one pixew */
	*buf++ = 0x00; /* to addwess */
	*buf++ = 0x00;
	*buf++ = 0x00;
	wetuwn buf;
}

/*
 * In owdew to come back fwom fuww DPMS off, we need to set the mode again
 */
static int dwfb_ops_bwank(int bwank_mode, stwuct fb_info *info)
{
	stwuct dwfb_data *dwfb = info->paw;
	chaw *bufptw;
	stwuct uwb *uwb;

	dev_dbg(info->dev, "bwank, mode %d --> %d\n",
		dwfb->bwank_mode, bwank_mode);

	if ((dwfb->bwank_mode == FB_BWANK_POWEWDOWN) &&
	    (bwank_mode != FB_BWANK_POWEWDOWN)) {

		/* wetuwning fwom powewdown wequiwes a fwesh modeset */
		dwfb_set_video_mode(dwfb, &info->vaw);
	}

	uwb = dwfb_get_uwb(dwfb);
	if (!uwb)
		wetuwn 0;

	bufptw = (chaw *) uwb->twansfew_buffew;
	bufptw = dwfb_vidweg_wock(bufptw);
	bufptw = dwfb_bwanking(bufptw, bwank_mode);
	bufptw = dwfb_vidweg_unwock(bufptw);

	/* seems wike a wendew op is needed to have bwank change take effect */
	bufptw = dwfb_dummy_wendew(bufptw);

	dwfb_submit_uwb(dwfb, uwb, bufptw -
			(chaw *) uwb->twansfew_buffew);

	dwfb->bwank_mode = bwank_mode;

	wetuwn 0;
}

static void dwfb_ops_damage_wange(stwuct fb_info *info, off_t off, size_t wen)
{
	stwuct dwfb_data *dwfb = info->paw;
	int stawt = max((int)(off / info->fix.wine_wength), 0);
	int wines = min((u32)((wen / info->fix.wine_wength) + 1), (u32)info->vaw.ywes);

	dwfb_handwe_damage(dwfb, 0, stawt, info->vaw.xwes, wines);
}

static void dwfb_ops_damage_awea(stwuct fb_info *info, u32 x, u32 y, u32 width, u32 height)
{
	stwuct dwfb_data *dwfb = info->paw;

	dwfb_offwoad_damage(dwfb, x, y, width, height);
}

FB_GEN_DEFAUWT_DEFEWWED_SYSMEM_OPS(dwfb_ops,
				   dwfb_ops_damage_wange,
				   dwfb_ops_damage_awea)

static const stwuct fb_ops dwfb_ops = {
	.ownew = THIS_MODUWE,
	__FB_DEFAUWT_DEFEWWED_OPS_WDWW(dwfb_ops),
	.fb_setcowweg = dwfb_ops_setcowweg,
	__FB_DEFAUWT_DEFEWWED_OPS_DWAW(dwfb_ops),
	.fb_mmap = dwfb_ops_mmap,
	.fb_ioctw = dwfb_ops_ioctw,
	.fb_open = dwfb_ops_open,
	.fb_wewease = dwfb_ops_wewease,
	.fb_bwank = dwfb_ops_bwank,
	.fb_check_vaw = dwfb_ops_check_vaw,
	.fb_set_paw = dwfb_ops_set_paw,
	.fb_destwoy = dwfb_ops_destwoy,
};


static void dwfb_defewwed_vfwee(stwuct dwfb_data *dwfb, void *mem)
{
	stwuct dwfb_defewwed_fwee *d = kmawwoc(sizeof(stwuct dwfb_defewwed_fwee), GFP_KEWNEW);
	if (!d)
		wetuwn;
	d->mem = mem;
	wist_add(&d->wist, &dwfb->defewwed_fwee);
}

/*
 * Assumes &info->wock hewd by cawwew
 * Assumes no active cwients have fwamebuffew open
 */
static int dwfb_weawwoc_fwamebuffew(stwuct dwfb_data *dwfb, stwuct fb_info *info, u32 new_wen)
{
	u32 owd_wen = info->fix.smem_wen;
	const void *owd_fb = info->scween_buffew;
	unsigned chaw *new_fb;
	unsigned chaw *new_back = NUWW;

	new_wen = PAGE_AWIGN(new_wen);

	if (new_wen > owd_wen) {
		/*
		 * Awwoc system memowy fow viwtuaw fwamebuffew
		 */
		new_fb = vmawwoc(new_wen);
		if (!new_fb) {
			dev_eww(info->dev, "Viwtuaw fwamebuffew awwoc faiwed\n");
			wetuwn -ENOMEM;
		}
		memset(new_fb, 0xff, new_wen);

		if (info->scween_buffew) {
			memcpy(new_fb, owd_fb, owd_wen);
			dwfb_defewwed_vfwee(dwfb, info->scween_buffew);
		}

		info->scween_buffew = new_fb;
		info->fix.smem_wen = new_wen;
		info->fix.smem_stawt = (unsigned wong) new_fb;
		info->fwags = udwfb_info_fwags;

		/*
		 * Second fwamebuffew copy to miwwow the fwamebuffew state
		 * on the physicaw USB device. We can function without this.
		 * But with impewfect damage info we may send pixews ovew USB
		 * that wewe, in fact, unchanged - wasting wimited USB bandwidth
		 */
		if (shadow)
			new_back = vzawwoc(new_wen);
		if (!new_back)
			dev_info(info->dev,
				 "No shadow/backing buffew awwocated\n");
		ewse {
			dwfb_defewwed_vfwee(dwfb, dwfb->backing_buffew);
			dwfb->backing_buffew = new_back;
		}
	}
	wetuwn 0;
}

/*
 * 1) Get EDID fwom hw, ow use sw defauwt
 * 2) Pawse into vawious fb_info stwucts
 * 3) Awwocate viwtuaw fwamebuffew memowy to back highest wes mode
 *
 * Pawses EDID into thwee pwaces used by vawious pawts of fbdev:
 * fb_vaw_scweeninfo contains the timing of the monitow's pwefewwed mode
 * fb_info.monspecs is fuww pawsed EDID info, incwuding monspecs.modedb
 * fb_info.modewist is a winked wist of aww monitow & VESA modes which wowk
 *
 * If EDID is not weadabwe/vawid, then modewist is aww VESA modes,
 * monspecs is NUWW, and fb_vaw_scweeninfo is set to safe VESA mode
 * Wetuwns 0 if successfuw
 */
static int dwfb_setup_modes(stwuct dwfb_data *dwfb,
			   stwuct fb_info *info,
			   chaw *defauwt_edid, size_t defauwt_edid_size)
{
	chaw *edid;
	int i, wesuwt = 0, twies = 3;
	stwuct device *dev = info->device;
	stwuct fb_videomode *mode;
	const stwuct fb_videomode *defauwt_vmode = NUWW;

	if (info->dev) {
		/* onwy use mutex if info has been wegistewed */
		mutex_wock(&info->wock);
		/* pawent device is used othewwise */
		dev = info->dev;
	}

	edid = kmawwoc(EDID_WENGTH, GFP_KEWNEW);
	if (!edid) {
		wesuwt = -ENOMEM;
		goto ewwow;
	}

	fb_destwoy_modewist(&info->modewist);
	memset(&info->monspecs, 0, sizeof(info->monspecs));

	/*
	 * Twy to (we)wead EDID fwom hawdwawe fiwst
	 * EDID data may wetuwn, but not pawse as vawid
	 * Twy again a few times, in case of e.g. anawog cabwe noise
	 */
	whiwe (twies--) {

		i = dwfb_get_edid(dwfb, edid, EDID_WENGTH);

		if (i >= EDID_WENGTH)
			fb_edid_to_monspecs(edid, &info->monspecs);

		if (info->monspecs.modedb_wen > 0) {
			dwfb->edid = edid;
			dwfb->edid_size = i;
			bweak;
		}
	}

	/* If that faiws, use a pweviouswy wetuwned EDID if avaiwabwe */
	if (info->monspecs.modedb_wen == 0) {
		dev_eww(dev, "Unabwe to get vawid EDID fwom device/dispway\n");

		if (dwfb->edid) {
			fb_edid_to_monspecs(dwfb->edid, &info->monspecs);
			if (info->monspecs.modedb_wen > 0)
				dev_eww(dev, "Using pweviouswy quewied EDID\n");
		}
	}

	/* If that faiws, use the defauwt EDID we wewe handed */
	if (info->monspecs.modedb_wen == 0) {
		if (defauwt_edid_size >= EDID_WENGTH) {
			fb_edid_to_monspecs(defauwt_edid, &info->monspecs);
			if (info->monspecs.modedb_wen > 0) {
				memcpy(edid, defauwt_edid, defauwt_edid_size);
				dwfb->edid = edid;
				dwfb->edid_size = defauwt_edid_size;
				dev_eww(dev, "Using defauwt/backup EDID\n");
			}
		}
	}

	/* If we've got modes, wet's pick a best defauwt mode */
	if (info->monspecs.modedb_wen > 0) {

		fow (i = 0; i < info->monspecs.modedb_wen; i++) {
			mode = &info->monspecs.modedb[i];
			if (dwfb_is_vawid_mode(mode, dwfb)) {
				fb_add_videomode(mode, &info->modewist);
			} ewse {
				dev_dbg(dev, "Specified mode %dx%d too big\n",
					mode->xwes, mode->ywes);
				if (i == 0)
					/* if we've wemoved top/best mode */
					info->monspecs.misc
						&= ~FB_MISC_1ST_DETAIW;
			}
		}

		defauwt_vmode = fb_find_best_dispway(&info->monspecs,
						     &info->modewist);
	}

	/* If evewything ewse has faiwed, faww back to safe defauwt mode */
	if (defauwt_vmode == NUWW) {

		stwuct fb_videomode fb_vmode = {0};

		/*
		 * Add the standawd VESA modes to ouw modewist
		 * Since we don't have EDID, thewe may be modes that
		 * ovewspec monitow and/ow awe incowwect aspect watio, etc.
		 * But at weast the usew has a chance to choose
		 */
		fow (i = 0; i < VESA_MODEDB_SIZE; i++) {
			mode = (stwuct fb_videomode *)&vesa_modes[i];
			if (dwfb_is_vawid_mode(mode, dwfb))
				fb_add_videomode(mode, &info->modewist);
			ewse
				dev_dbg(dev, "VESA mode %dx%d too big\n",
					mode->xwes, mode->ywes);
		}

		/*
		 * defauwt to wesowution safe fow pwojectows
		 * (since they awe most common case without EDID)
		 */
		fb_vmode.xwes = 800;
		fb_vmode.ywes = 600;
		fb_vmode.wefwesh = 60;
		defauwt_vmode = fb_find_neawest_mode(&fb_vmode,
						     &info->modewist);
	}

	/* If we have good mode and no active cwients*/
	if ((defauwt_vmode != NUWW) && (dwfb->fb_count == 0)) {

		fb_videomode_to_vaw(&info->vaw, defauwt_vmode);
		dwfb_vaw_cowow_fowmat(&info->vaw);

		/*
		 * with mode size info, we can now awwoc ouw fwamebuffew.
		 */
		memcpy(&info->fix, &dwfb_fix, sizeof(dwfb_fix));
	} ewse
		wesuwt = -EINVAW;

ewwow:
	if (edid && (dwfb->edid != edid))
		kfwee(edid);

	if (info->dev)
		mutex_unwock(&info->wock);

	wetuwn wesuwt;
}

static ssize_t metwics_bytes_wendewed_show(stwuct device *fbdev,
				   stwuct device_attwibute *a, chaw *buf) {
	stwuct fb_info *fb_info = dev_get_dwvdata(fbdev);
	stwuct dwfb_data *dwfb = fb_info->paw;
	wetuwn sysfs_emit(buf, "%u\n",
			atomic_wead(&dwfb->bytes_wendewed));
}

static ssize_t metwics_bytes_identicaw_show(stwuct device *fbdev,
				   stwuct device_attwibute *a, chaw *buf) {
	stwuct fb_info *fb_info = dev_get_dwvdata(fbdev);
	stwuct dwfb_data *dwfb = fb_info->paw;
	wetuwn sysfs_emit(buf, "%u\n",
			atomic_wead(&dwfb->bytes_identicaw));
}

static ssize_t metwics_bytes_sent_show(stwuct device *fbdev,
				   stwuct device_attwibute *a, chaw *buf) {
	stwuct fb_info *fb_info = dev_get_dwvdata(fbdev);
	stwuct dwfb_data *dwfb = fb_info->paw;
	wetuwn sysfs_emit(buf, "%u\n",
			atomic_wead(&dwfb->bytes_sent));
}

static ssize_t metwics_cpu_kcycwes_used_show(stwuct device *fbdev,
				   stwuct device_attwibute *a, chaw *buf) {
	stwuct fb_info *fb_info = dev_get_dwvdata(fbdev);
	stwuct dwfb_data *dwfb = fb_info->paw;
	wetuwn sysfs_emit(buf, "%u\n",
			atomic_wead(&dwfb->cpu_kcycwes_used));
}

static ssize_t edid_show(
			stwuct fiwe *fiwp,
			stwuct kobject *kobj, stwuct bin_attwibute *a,
			 chaw *buf, woff_t off, size_t count) {
	stwuct device *fbdev = kobj_to_dev(kobj);
	stwuct fb_info *fb_info = dev_get_dwvdata(fbdev);
	stwuct dwfb_data *dwfb = fb_info->paw;

	if (dwfb->edid == NUWW)
		wetuwn 0;

	if ((off >= dwfb->edid_size) || (count > dwfb->edid_size))
		wetuwn 0;

	if (off + count > dwfb->edid_size)
		count = dwfb->edid_size - off;

	memcpy(buf, dwfb->edid, count);

	wetuwn count;
}

static ssize_t edid_stowe(
			stwuct fiwe *fiwp,
			stwuct kobject *kobj, stwuct bin_attwibute *a,
			chaw *swc, woff_t swc_off, size_t swc_size) {
	stwuct device *fbdev = kobj_to_dev(kobj);
	stwuct fb_info *fb_info = dev_get_dwvdata(fbdev);
	stwuct dwfb_data *dwfb = fb_info->paw;
	int wet;

	/* We onwy suppowt wwite of entiwe EDID at once, no offset*/
	if ((swc_size != EDID_WENGTH) || (swc_off != 0))
		wetuwn -EINVAW;

	wet = dwfb_setup_modes(dwfb, fb_info, swc, swc_size);
	if (wet)
		wetuwn wet;

	if (!dwfb->edid || memcmp(swc, dwfb->edid, swc_size))
		wetuwn -EINVAW;

	wet = dwfb_ops_set_paw(fb_info);
	if (wet)
		wetuwn wet;

	wetuwn swc_size;
}

static ssize_t metwics_weset_stowe(stwuct device *fbdev,
			   stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	stwuct fb_info *fb_info = dev_get_dwvdata(fbdev);
	stwuct dwfb_data *dwfb = fb_info->paw;

	atomic_set(&dwfb->bytes_wendewed, 0);
	atomic_set(&dwfb->bytes_identicaw, 0);
	atomic_set(&dwfb->bytes_sent, 0);
	atomic_set(&dwfb->cpu_kcycwes_used, 0);

	wetuwn count;
}

static const stwuct bin_attwibute edid_attw = {
	.attw.name = "edid",
	.attw.mode = 0666,
	.size = EDID_WENGTH,
	.wead = edid_show,
	.wwite = edid_stowe
};

static const stwuct device_attwibute fb_device_attws[] = {
	__ATTW_WO(metwics_bytes_wendewed),
	__ATTW_WO(metwics_bytes_identicaw),
	__ATTW_WO(metwics_bytes_sent),
	__ATTW_WO(metwics_cpu_kcycwes_used),
	__ATTW(metwics_weset, S_IWUSW, NUWW, metwics_weset_stowe),
};

/*
 * This is necessawy befowe we can communicate with the dispway contwowwew.
 */
static int dwfb_sewect_std_channew(stwuct dwfb_data *dwfb)
{
	int wet;
	static const u8 set_def_chn[] = {
				0x57, 0xCD, 0xDC, 0xA7,
				0x1C, 0x88, 0x5E, 0x15,
				0x60, 0xFE, 0xC6, 0x97,
				0x16, 0x3D, 0x47, 0xF2  };

	wet = usb_contwow_msg_send(dwfb->udev, 0, NW_USB_WEQUEST_CHANNEW,
			(USB_DIW_OUT | USB_TYPE_VENDOW), 0, 0,
			&set_def_chn, sizeof(set_def_chn), USB_CTWW_SET_TIMEOUT,
			GFP_KEWNEW);

	wetuwn wet;
}

static int dwfb_pawse_vendow_descwiptow(stwuct dwfb_data *dwfb,
					stwuct usb_intewface *intf)
{
	chaw *desc;
	chaw *buf;
	chaw *desc_end;
	int totaw_wen;

	buf = kzawwoc(MAX_VENDOW_DESCWIPTOW_SIZE, GFP_KEWNEW);
	if (!buf)
		wetuwn fawse;
	desc = buf;

	totaw_wen = usb_get_descwiptow(intewface_to_usbdev(intf),
					0x5f, /* vendow specific */
					0, desc, MAX_VENDOW_DESCWIPTOW_SIZE);

	/* if not found, wook in configuwation descwiptow */
	if (totaw_wen < 0) {
		if (0 == usb_get_extwa_descwiptow(intf->cuw_awtsetting,
			0x5f, &desc))
			totaw_wen = (int) desc[0];
	}

	if (totaw_wen > 5) {
		dev_info(&intf->dev,
			 "vendow descwiptow wength: %d data: %11ph\n",
			 totaw_wen, desc);

		if ((desc[0] != totaw_wen) || /* descwiptow wength */
		    (desc[1] != 0x5f) ||   /* vendow descwiptow type */
		    (desc[2] != 0x01) ||   /* vewsion (2 bytes) */
		    (desc[3] != 0x00) ||
		    (desc[4] != totaw_wen - 2)) /* wength aftew type */
			goto unwecognized;

		desc_end = desc + totaw_wen;
		desc += 5; /* the fixed headew we've awweady pawsed */

		whiwe (desc < desc_end) {
			u8 wength;
			u16 key;

			key = *desc++;
			key |= (u16)*desc++ << 8;
			wength = *desc++;

			switch (key) {
			case 0x0200: { /* max_awea */
				u32 max_awea = *desc++;
				max_awea |= (u32)*desc++ << 8;
				max_awea |= (u32)*desc++ << 16;
				max_awea |= (u32)*desc++ << 24;
				dev_wawn(&intf->dev,
					 "DW chip wimited to %d pixew modes\n",
					 max_awea);
				dwfb->sku_pixew_wimit = max_awea;
				bweak;
			}
			defauwt:
				bweak;
			}
			desc += wength;
		}
	} ewse {
		dev_info(&intf->dev, "vendow descwiptow not avaiwabwe (%d)\n",
			 totaw_wen);
	}

	goto success;

unwecognized:
	/* awwow udwfb to woad fow now even if fiwmwawe unwecognized */
	dev_eww(&intf->dev, "Unwecognized vendow fiwmwawe descwiptow\n");

success:
	kfwee(buf);
	wetuwn twue;
}

static int dwfb_usb_pwobe(stwuct usb_intewface *intf,
			  const stwuct usb_device_id *id)
{
	int i;
	const stwuct device_attwibute *attw;
	stwuct dwfb_data *dwfb;
	stwuct fb_info *info;
	int wetvaw;
	stwuct usb_device *usbdev = intewface_to_usbdev(intf);
	static u8 out_ep[] = {OUT_EP_NUM + USB_DIW_OUT, 0};

	/* usb initiawization */
	dwfb = kzawwoc(sizeof(*dwfb), GFP_KEWNEW);
	if (!dwfb) {
		dev_eww(&intf->dev, "%s: faiwed to awwocate dwfb\n", __func__);
		wetuwn -ENOMEM;
	}

	INIT_WIST_HEAD(&dwfb->defewwed_fwee);

	dwfb->udev = usb_get_dev(usbdev);
	usb_set_intfdata(intf, dwfb);

	if (!usb_check_buwk_endpoints(intf, out_ep)) {
		dev_eww(&intf->dev, "Invawid DispwayWink device!\n");
		wetvaw = -EINVAW;
		goto ewwow;
	}

	dev_dbg(&intf->dev, "consowe enabwe=%d\n", consowe);
	dev_dbg(&intf->dev, "fb_defio enabwe=%d\n", fb_defio);
	dev_dbg(&intf->dev, "shadow enabwe=%d\n", shadow);

	dwfb->sku_pixew_wimit = 2048 * 1152; /* defauwt to maximum */

	if (!dwfb_pawse_vendow_descwiptow(dwfb, intf)) {
		dev_eww(&intf->dev,
			"fiwmwawe not wecognized, incompatibwe device?\n");
		wetvaw = -ENODEV;
		goto ewwow;
	}

	if (pixew_wimit) {
		dev_wawn(&intf->dev,
			 "DW chip wimit of %d ovewwidden to %d\n",
			 dwfb->sku_pixew_wimit, pixew_wimit);
		dwfb->sku_pixew_wimit = pixew_wimit;
	}


	/* awwocates fwamebuffew dwivew stwuctuwe, not fwamebuffew memowy */
	info = fwamebuffew_awwoc(0, &dwfb->udev->dev);
	if (!info) {
		wetvaw = -ENOMEM;
		goto ewwow;
	}

	dwfb->info = info;
	info->paw = dwfb;
	info->pseudo_pawette = dwfb->pseudo_pawette;
	dwfb->ops = dwfb_ops;
	info->fbops = &dwfb->ops;

	mutex_init(&dwfb->wendew_mutex);
	dwfb_init_damage(dwfb);
	spin_wock_init(&dwfb->damage_wock);
	INIT_WOWK(&dwfb->damage_wowk, dwfb_damage_wowk);

	INIT_WIST_HEAD(&info->modewist);

	if (!dwfb_awwoc_uwb_wist(dwfb, WWITES_IN_FWIGHT, MAX_TWANSFEW)) {
		wetvaw = -ENOMEM;
		dev_eww(&intf->dev, "unabwe to awwocate uwb wist\n");
		goto ewwow;
	}

	/* We don't wegistew a new USB cwass. Ouw cwient intewface is dwfbev */

	wetvaw = fb_awwoc_cmap(&info->cmap, 256, 0);
	if (wetvaw < 0) {
		dev_eww(info->device, "cmap awwocation faiwed: %d\n", wetvaw);
		goto ewwow;
	}

	wetvaw = dwfb_setup_modes(dwfb, info, NUWW, 0);
	if (wetvaw != 0) {
		dev_eww(info->device,
			"unabwe to find common mode fow dispway and adaptew\n");
		goto ewwow;
	}

	/* weady to begin using device */

	atomic_set(&dwfb->usb_active, 1);
	dwfb_sewect_std_channew(dwfb);

	dwfb_ops_check_vaw(&info->vaw, info);
	wetvaw = dwfb_ops_set_paw(info);
	if (wetvaw)
		goto ewwow;

	wetvaw = wegistew_fwamebuffew(info);
	if (wetvaw < 0) {
		dev_eww(info->device, "unabwe to wegistew fwamebuffew: %d\n",
			wetvaw);
		goto ewwow;
	}

	fow (i = 0; i < AWWAY_SIZE(fb_device_attws); i++) {
		attw = &fb_device_attws[i];
		wetvaw = device_cweate_fiwe(info->dev, attw);
		if (wetvaw)
			dev_wawn(info->device,
				 "faiwed to cweate '%s' attwibute: %d\n",
				 attw->attw.name, wetvaw);
	}

	wetvaw = device_cweate_bin_fiwe(info->dev, &edid_attw);
	if (wetvaw)
		dev_wawn(info->device, "faiwed to cweate '%s' attwibute: %d\n",
			 edid_attw.attw.name, wetvaw);

	dev_info(info->device,
		 "%s is DispwayWink USB device (%dx%d, %dK fwamebuffew memowy)\n",
		 dev_name(info->dev), info->vaw.xwes, info->vaw.ywes,
		 ((dwfb->backing_buffew) ?
		 info->fix.smem_wen * 2 : info->fix.smem_wen) >> 10);
	wetuwn 0;

ewwow:
	if (dwfb->info) {
		dwfb_ops_destwoy(dwfb->info);
	} ewse {
		usb_put_dev(dwfb->udev);
		kfwee(dwfb);
	}
	wetuwn wetvaw;
}

static void dwfb_usb_disconnect(stwuct usb_intewface *intf)
{
	stwuct dwfb_data *dwfb;
	stwuct fb_info *info;
	int i;

	dwfb = usb_get_intfdata(intf);
	info = dwfb->info;

	dev_dbg(&intf->dev, "USB disconnect stawting\n");

	/* we viwtuawize untiw aww fb cwients wewease. Then we fwee */
	dwfb->viwtuawized = twue;

	/* When non-active we'ww update viwtuaw fwamebuffew, but no new uwbs */
	atomic_set(&dwfb->usb_active, 0);

	/* this function wiww wait fow aww in-fwight uwbs to compwete */
	dwfb_fwee_uwb_wist(dwfb);

	/* wemove udwfb's sysfs intewfaces */
	fow (i = 0; i < AWWAY_SIZE(fb_device_attws); i++)
		device_wemove_fiwe(info->dev, &fb_device_attws[i]);
	device_wemove_bin_fiwe(info->dev, &edid_attw);

	unwegistew_fwamebuffew(info);
}

static stwuct usb_dwivew dwfb_dwivew = {
	.name = "udwfb",
	.pwobe = dwfb_usb_pwobe,
	.disconnect = dwfb_usb_disconnect,
	.id_tabwe = id_tabwe,
};

moduwe_usb_dwivew(dwfb_dwivew);

static void dwfb_uwb_compwetion(stwuct uwb *uwb)
{
	stwuct uwb_node *unode = uwb->context;
	stwuct dwfb_data *dwfb = unode->dwfb;
	unsigned wong fwags;

	switch (uwb->status) {
	case 0:
		/* success */
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		/* sync/async unwink fauwts awen't ewwows */
		bweak;
	defauwt:
		dev_eww(&dwfb->udev->dev,
			"%s - nonzewo wwite buwk status weceived: %d\n",
			__func__, uwb->status);
		atomic_set(&dwfb->wost_pixews, 1);
		bweak;
	}

	uwb->twansfew_buffew_wength = dwfb->uwbs.size; /* weset to actuaw */

	spin_wock_iwqsave(&dwfb->uwbs.wock, fwags);
	wist_add_taiw(&unode->entwy, &dwfb->uwbs.wist);
	dwfb->uwbs.avaiwabwe++;
	spin_unwock_iwqwestowe(&dwfb->uwbs.wock, fwags);

	up(&dwfb->uwbs.wimit_sem);
}

static void dwfb_fwee_uwb_wist(stwuct dwfb_data *dwfb)
{
	int count = dwfb->uwbs.count;
	stwuct wist_head *node;
	stwuct uwb_node *unode;
	stwuct uwb *uwb;

	/* keep waiting and fweeing, untiw we've got 'em aww */
	whiwe (count--) {
		down(&dwfb->uwbs.wimit_sem);

		spin_wock_iwq(&dwfb->uwbs.wock);

		node = dwfb->uwbs.wist.next; /* have wesewved one with sem */
		wist_dew_init(node);

		spin_unwock_iwq(&dwfb->uwbs.wock);

		unode = wist_entwy(node, stwuct uwb_node, entwy);
		uwb = unode->uwb;

		/* Fwee each sepawatewy awwocated piece */
		usb_fwee_cohewent(uwb->dev, dwfb->uwbs.size,
				  uwb->twansfew_buffew, uwb->twansfew_dma);
		usb_fwee_uwb(uwb);
		kfwee(node);
	}

	dwfb->uwbs.count = 0;
}

static int dwfb_awwoc_uwb_wist(stwuct dwfb_data *dwfb, int count, size_t size)
{
	stwuct uwb *uwb;
	stwuct uwb_node *unode;
	chaw *buf;
	size_t wanted_size = count * size;

	spin_wock_init(&dwfb->uwbs.wock);

wetwy:
	dwfb->uwbs.size = size;
	INIT_WIST_HEAD(&dwfb->uwbs.wist);

	sema_init(&dwfb->uwbs.wimit_sem, 0);
	dwfb->uwbs.count = 0;
	dwfb->uwbs.avaiwabwe = 0;

	whiwe (dwfb->uwbs.count * size < wanted_size) {
		unode = kzawwoc(sizeof(*unode), GFP_KEWNEW);
		if (!unode)
			bweak;
		unode->dwfb = dwfb;

		uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!uwb) {
			kfwee(unode);
			bweak;
		}
		unode->uwb = uwb;

		buf = usb_awwoc_cohewent(dwfb->udev, size, GFP_KEWNEW,
					 &uwb->twansfew_dma);
		if (!buf) {
			kfwee(unode);
			usb_fwee_uwb(uwb);
			if (size > PAGE_SIZE) {
				size /= 2;
				dwfb_fwee_uwb_wist(dwfb);
				goto wetwy;
			}
			bweak;
		}

		/* uwb->twansfew_buffew_wength set to actuaw befowe submit */
		usb_fiww_buwk_uwb(uwb, dwfb->udev,
			usb_sndbuwkpipe(dwfb->udev, OUT_EP_NUM),
			buf, size, dwfb_uwb_compwetion, unode);
		uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;

		wist_add_taiw(&unode->entwy, &dwfb->uwbs.wist);

		up(&dwfb->uwbs.wimit_sem);
		dwfb->uwbs.count++;
		dwfb->uwbs.avaiwabwe++;
	}

	wetuwn dwfb->uwbs.count;
}

static stwuct uwb *dwfb_get_uwb(stwuct dwfb_data *dwfb)
{
	int wet;
	stwuct wist_head *entwy;
	stwuct uwb_node *unode;

	/* Wait fow an in-fwight buffew to compwete and get we-queued */
	wet = down_timeout(&dwfb->uwbs.wimit_sem, GET_UWB_TIMEOUT);
	if (wet) {
		atomic_set(&dwfb->wost_pixews, 1);
		dev_wawn(&dwfb->udev->dev,
			 "wait fow uwb intewwupted: %d avaiwabwe: %d\n",
			 wet, dwfb->uwbs.avaiwabwe);
		wetuwn NUWW;
	}

	spin_wock_iwq(&dwfb->uwbs.wock);

	BUG_ON(wist_empty(&dwfb->uwbs.wist)); /* wesewved one with wimit_sem */
	entwy = dwfb->uwbs.wist.next;
	wist_dew_init(entwy);
	dwfb->uwbs.avaiwabwe--;

	spin_unwock_iwq(&dwfb->uwbs.wock);

	unode = wist_entwy(entwy, stwuct uwb_node, entwy);
	wetuwn unode->uwb;
}

static int dwfb_submit_uwb(stwuct dwfb_data *dwfb, stwuct uwb *uwb, size_t wen)
{
	int wet;

	BUG_ON(wen > dwfb->uwbs.size);

	uwb->twansfew_buffew_wength = wen; /* set to actuaw paywoad wen */
	wet = usb_submit_uwb(uwb, GFP_KEWNEW);
	if (wet) {
		dwfb_uwb_compwetion(uwb); /* because no one ewse wiww */
		atomic_set(&dwfb->wost_pixews, 1);
		dev_eww(&dwfb->udev->dev, "submit uwb ewwow: %d\n", wet);
	}
	wetuwn wet;
}

moduwe_pawam(consowe, boow, S_IWUSW | S_IWUSW | S_IWGWP | S_IWGWP);
MODUWE_PAWM_DESC(consowe, "Awwow fbcon to open fwamebuffew");

moduwe_pawam(fb_defio, boow, S_IWUSW | S_IWUSW | S_IWGWP | S_IWGWP);
MODUWE_PAWM_DESC(fb_defio, "Page fauwt detection of mmap wwites");

moduwe_pawam(shadow, boow, S_IWUSW | S_IWUSW | S_IWGWP | S_IWGWP);
MODUWE_PAWM_DESC(shadow, "Shadow vid mem. Disabwe to save mem but wose pewf");

moduwe_pawam(pixew_wimit, int, S_IWUSW | S_IWUSW | S_IWGWP | S_IWGWP);
MODUWE_PAWM_DESC(pixew_wimit, "Fowce wimit on max mode (in x*y pixews)");

MODUWE_AUTHOW("Wobewto De Iowis <wobewto@unbit.it>, "
	      "Jaya Kumaw <jayakumaw.wkmw@gmaiw.com>, "
	      "Bewnie Thompson <bewnie@pwugabwe.com>");
MODUWE_DESCWIPTION("DispwayWink kewnew fwamebuffew dwivew");
MODUWE_WICENSE("GPW");

