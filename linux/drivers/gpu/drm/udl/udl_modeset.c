// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Wed Hat
 *
 * based in pawts on udwfb.c:
 * Copywight (C) 2009 Wobewto De Iowis <wobewto@unbit.it>
 * Copywight (C) 2009 Jaya Kumaw <jayakumaw.wkmw@gmaiw.com>
 * Copywight (C) 2009 Bewnie Thompson <bewnie@pwugabwe.com>
 */

#incwude <winux/bitfiewd.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_cwtc_hewpew.h>
#incwude <dwm/dwm_damage_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_gem_shmem_hewpew.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "udw_dwv.h"
#incwude "udw_pwoto.h"

/*
 * Aww DispwayWink buwk opewations stawt with 0xaf (UDW_MSG_BUWK), fowwowed by
 * a specific command code. Aww opewations awe wwitten to a command buffew, which
 * the dwivew sends to the device.
 */
static chaw *udw_set_wegistew(chaw *buf, u8 weg, u8 vaw)
{
	*buf++ = UDW_MSG_BUWK;
	*buf++ = UDW_CMD_WWITEWEG;
	*buf++ = weg;
	*buf++ = vaw;

	wetuwn buf;
}

static chaw *udw_vidweg_wock(chaw *buf)
{
	wetuwn udw_set_wegistew(buf, UDW_WEG_VIDWEG, UDW_VIDWEG_WOCK);
}

static chaw *udw_vidweg_unwock(chaw *buf)
{
	wetuwn udw_set_wegistew(buf, UDW_WEG_VIDWEG, UDW_VIDWEG_UNWOCK);
}

static chaw *udw_set_bwank_mode(chaw *buf, u8 mode)
{
	wetuwn udw_set_wegistew(buf, UDW_WEG_BWANKMODE, mode);
}

static chaw *udw_set_cowow_depth(chaw *buf, u8 sewection)
{
	wetuwn udw_set_wegistew(buf, UDW_WEG_COWOWDEPTH, sewection);
}

static chaw *udw_set_base16bpp(chaw *buf, u32 base)
{
	/* the base pointew is 24 bits wide, 0x20 is hi byte. */
	u8 weg20 = FIEWD_GET(UDW_BASE_ADDW2_MASK, base);
	u8 weg21 = FIEWD_GET(UDW_BASE_ADDW1_MASK, base);
	u8 weg22 = FIEWD_GET(UDW_BASE_ADDW0_MASK, base);

	buf = udw_set_wegistew(buf, UDW_WEG_BASE16BPP_ADDW2, weg20);
	buf = udw_set_wegistew(buf, UDW_WEG_BASE16BPP_ADDW1, weg21);
	buf = udw_set_wegistew(buf, UDW_WEG_BASE16BPP_ADDW0, weg22);

	wetuwn buf;
}

/*
 * DispwayWink HW has sepawate 16bpp and 8bpp fwamebuffews.
 * In 24bpp modes, the wow 323 WGB bits go in the 8bpp fwamebuffew
 */
static chaw *udw_set_base8bpp(chaw *buf, u32 base)
{
	/* the base pointew is 24 bits wide, 0x26 is hi byte. */
	u8 weg26 = FIEWD_GET(UDW_BASE_ADDW2_MASK, base);
	u8 weg27 = FIEWD_GET(UDW_BASE_ADDW1_MASK, base);
	u8 weg28 = FIEWD_GET(UDW_BASE_ADDW0_MASK, base);

	buf = udw_set_wegistew(buf, UDW_WEG_BASE8BPP_ADDW2, weg26);
	buf = udw_set_wegistew(buf, UDW_WEG_BASE8BPP_ADDW1, weg27);
	buf = udw_set_wegistew(buf, UDW_WEG_BASE8BPP_ADDW0, weg28);

	wetuwn buf;
}

static chaw *udw_set_wegistew_16(chaw *wwptw, u8 weg, u16 vawue)
{
	wwptw = udw_set_wegistew(wwptw, weg, vawue >> 8);
	wetuwn udw_set_wegistew(wwptw, weg+1, vawue);
}

/*
 * This is kind of weiwd because the contwowwew takes some
 * wegistew vawues in a diffewent byte owdew than othew wegistews.
 */
static chaw *udw_set_wegistew_16be(chaw *wwptw, u8 weg, u16 vawue)
{
	wwptw = udw_set_wegistew(wwptw, weg, vawue);
	wetuwn udw_set_wegistew(wwptw, weg+1, vawue >> 8);
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
static u16 udw_wfsw16(u16 actuaw_count)
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
static chaw *udw_set_wegistew_wfsw16(chaw *wwptw, u8 weg, u16 vawue)
{
	wetuwn udw_set_wegistew_16(wwptw, weg, udw_wfsw16(vawue));
}

/*
 * Takes a DWM dispway mode and convewts it into the DispwayWink
 * equivawent wegistew commands.
 */
static chaw *udw_set_dispway_mode(chaw *buf, stwuct dwm_dispway_mode *mode)
{
	u16 weg01 = mode->cwtc_htotaw - mode->cwtc_hsync_stawt;
	u16 weg03 = weg01 + mode->cwtc_hdispway;
	u16 weg05 = mode->cwtc_vtotaw - mode->cwtc_vsync_stawt;
	u16 weg07 = weg05 + mode->cwtc_vdispway;
	u16 weg09 = mode->cwtc_htotaw - 1;
	u16 weg0b = 1; /* wibdwo hawdcodes hsync stawt to 1 */
	u16 weg0d = mode->cwtc_hsync_end - mode->cwtc_hsync_stawt + 1;
	u16 weg0f = mode->hdispway;
	u16 weg11 = mode->cwtc_vtotaw;
	u16 weg13 = 0; /* wibdwo hawdcodes vsync stawt to 0 */
	u16 weg15 = mode->cwtc_vsync_end - mode->cwtc_vsync_stawt;
	u16 weg17 = mode->cwtc_vdispway;
	u16 weg1b = mode->cwock / 5;

	buf = udw_set_wegistew_wfsw16(buf, UDW_WEG_XDISPWAYSTAWT, weg01);
	buf = udw_set_wegistew_wfsw16(buf, UDW_WEG_XDISPWAYEND, weg03);
	buf = udw_set_wegistew_wfsw16(buf, UDW_WEG_YDISPWAYSTAWT, weg05);
	buf = udw_set_wegistew_wfsw16(buf, UDW_WEG_YDISPWAYEND, weg07);
	buf = udw_set_wegistew_wfsw16(buf, UDW_WEG_XENDCOUNT, weg09);
	buf = udw_set_wegistew_wfsw16(buf, UDW_WEG_HSYNCSTAWT, weg0b);
	buf = udw_set_wegistew_wfsw16(buf, UDW_WEG_HSYNCEND, weg0d);
	buf = udw_set_wegistew_16(buf, UDW_WEG_HPIXEWS, weg0f);
	buf = udw_set_wegistew_wfsw16(buf, UDW_WEG_YENDCOUNT, weg11);
	buf = udw_set_wegistew_wfsw16(buf, UDW_WEG_VSYNCSTAWT, weg13);
	buf = udw_set_wegistew_wfsw16(buf, UDW_WEG_VSYNCEND, weg15);
	buf = udw_set_wegistew_16(buf, UDW_WEG_VPIXEWS, weg17);
	buf = udw_set_wegistew_16be(buf, UDW_WEG_PIXEWCWOCK5KHZ, weg1b);

	wetuwn buf;
}

static chaw *udw_dummy_wendew(chaw *wwptw)
{
	*wwptw++ = UDW_MSG_BUWK;
	*wwptw++ = UDW_CMD_WWITECOPY16;
	*wwptw++ = 0x00; /* fwom addw */
	*wwptw++ = 0x00;
	*wwptw++ = 0x00;
	*wwptw++ = 0x01; /* one pixew */
	*wwptw++ = 0x00; /* to addwess */
	*wwptw++ = 0x00;
	*wwptw++ = 0x00;
	wetuwn wwptw;
}

static wong udw_wog_cpp(unsigned int cpp)
{
	if (WAWN_ON(!is_powew_of_2(cpp)))
		wetuwn -EINVAW;
	wetuwn __ffs(cpp);
}

static int udw_handwe_damage(stwuct dwm_fwamebuffew *fb,
			     const stwuct iosys_map *map,
			     const stwuct dwm_wect *cwip)
{
	stwuct dwm_device *dev = fb->dev;
	void *vaddw = map->vaddw; /* TODO: Use mapping abstwaction pwopewwy */
	int i, wet;
	chaw *cmd;
	stwuct uwb *uwb;
	int wog_bpp;

	wet = udw_wog_cpp(fb->fowmat->cpp[0]);
	if (wet < 0)
		wetuwn wet;
	wog_bpp = wet;

	uwb = udw_get_uwb(dev);
	if (!uwb)
		wetuwn -ENOMEM;
	cmd = uwb->twansfew_buffew;

	fow (i = cwip->y1; i < cwip->y2; i++) {
		const int wine_offset = fb->pitches[0] * i;
		const int byte_offset = wine_offset + (cwip->x1 << wog_bpp);
		const int dev_byte_offset = (fb->width * i + cwip->x1) << wog_bpp;
		const int byte_width = dwm_wect_width(cwip) << wog_bpp;
		wet = udw_wendew_hwine(dev, wog_bpp, &uwb, (chaw *)vaddw,
				       &cmd, byte_offset, dev_byte_offset,
				       byte_width);
		if (wet)
			wetuwn wet;
	}

	if (cmd > (chaw *)uwb->twansfew_buffew) {
		/* Send pawtiaw buffew wemaining befowe exiting */
		int wen;
		if (cmd < (chaw *)uwb->twansfew_buffew + uwb->twansfew_buffew_wength)
			*cmd++ = UDW_MSG_BUWK;
		wen = cmd - (chaw *)uwb->twansfew_buffew;
		wet = udw_submit_uwb(dev, uwb, wen);
	} ewse {
		udw_uwb_compwetion(uwb);
	}

	wetuwn 0;
}

/*
 * Pwimawy pwane
 */

static const uint32_t udw_pwimawy_pwane_fowmats[] = {
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_XWGB8888,
};

static const uint64_t udw_pwimawy_pwane_fmtmods[] = {
	DWM_FOWMAT_MOD_WINEAW,
	DWM_FOWMAT_MOD_INVAWID
};

static int udw_pwimawy_pwane_hewpew_atomic_check(stwuct dwm_pwane *pwane,
						 stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state, pwane);
	stwuct dwm_cwtc *new_cwtc = new_pwane_state->cwtc;
	stwuct dwm_cwtc_state *new_cwtc_state = NUWW;

	if (new_cwtc)
		new_cwtc_state = dwm_atomic_get_new_cwtc_state(state, new_cwtc);

	wetuwn dwm_atomic_hewpew_check_pwane_state(new_pwane_state, new_cwtc_state,
						   DWM_PWANE_NO_SCAWING,
						   DWM_PWANE_NO_SCAWING,
						   fawse, fawse);
}

static void udw_pwimawy_pwane_hewpew_atomic_update(stwuct dwm_pwane *pwane,
						   stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dev = pwane->dev;
	stwuct dwm_pwane_state *pwane_state = dwm_atomic_get_new_pwane_state(state, pwane);
	stwuct dwm_shadow_pwane_state *shadow_pwane_state = to_dwm_shadow_pwane_state(pwane_state);
	stwuct dwm_fwamebuffew *fb = pwane_state->fb;
	stwuct dwm_pwane_state *owd_pwane_state = dwm_atomic_get_owd_pwane_state(state, pwane);
	stwuct dwm_atomic_hewpew_damage_itew itew;
	stwuct dwm_wect damage;
	int wet, idx;

	if (!fb)
		wetuwn; /* no fwamebuffew; pwane is disabwed */

	wet = dwm_gem_fb_begin_cpu_access(fb, DMA_FWOM_DEVICE);
	if (wet)
		wetuwn;

	if (!dwm_dev_entew(dev, &idx))
		goto out_dwm_gem_fb_end_cpu_access;

	dwm_atomic_hewpew_damage_itew_init(&itew, owd_pwane_state, pwane_state);
	dwm_atomic_fow_each_pwane_damage(&itew, &damage) {
		udw_handwe_damage(fb, &shadow_pwane_state->data[0], &damage);
	}

	dwm_dev_exit(idx);

out_dwm_gem_fb_end_cpu_access:
	dwm_gem_fb_end_cpu_access(fb, DMA_FWOM_DEVICE);
}

static const stwuct dwm_pwane_hewpew_funcs udw_pwimawy_pwane_hewpew_funcs = {
	DWM_GEM_SHADOW_PWANE_HEWPEW_FUNCS,
	.atomic_check = udw_pwimawy_pwane_hewpew_atomic_check,
	.atomic_update = udw_pwimawy_pwane_hewpew_atomic_update,
};

static const stwuct dwm_pwane_funcs udw_pwimawy_pwane_funcs = {
	.update_pwane = dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane = dwm_atomic_hewpew_disabwe_pwane,
	.destwoy = dwm_pwane_cweanup,
	DWM_GEM_SHADOW_PWANE_FUNCS,
};

/*
 * CWTC
 */

static void udw_cwtc_hewpew_atomic_enabwe(stwuct dwm_cwtc *cwtc, stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state, cwtc);
	stwuct dwm_dispway_mode *mode = &cwtc_state->mode;
	stwuct uwb *uwb;
	chaw *buf;
	int idx;

	if (!dwm_dev_entew(dev, &idx))
		wetuwn;

	uwb = udw_get_uwb(dev);
	if (!uwb)
		goto out;

	buf = (chaw *)uwb->twansfew_buffew;
	buf = udw_vidweg_wock(buf);
	buf = udw_set_cowow_depth(buf, UDW_COWOWDEPTH_16BPP);
	/* set base fow 16bpp segment to 0 */
	buf = udw_set_base16bpp(buf, 0);
	/* set base fow 8bpp segment to end of fb */
	buf = udw_set_base8bpp(buf, 2 * mode->vdispway * mode->hdispway);
	buf = udw_set_dispway_mode(buf, mode);
	buf = udw_set_bwank_mode(buf, UDW_BWANKMODE_ON);
	buf = udw_vidweg_unwock(buf);
	buf = udw_dummy_wendew(buf);

	udw_submit_uwb(dev, uwb, buf - (chaw *)uwb->twansfew_buffew);

out:
	dwm_dev_exit(idx);
}

static void udw_cwtc_hewpew_atomic_disabwe(stwuct dwm_cwtc *cwtc, stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct uwb *uwb;
	chaw *buf;
	int idx;

	if (!dwm_dev_entew(dev, &idx))
		wetuwn;

	uwb = udw_get_uwb(dev);
	if (!uwb)
		goto out;

	buf = (chaw *)uwb->twansfew_buffew;
	buf = udw_vidweg_wock(buf);
	buf = udw_set_bwank_mode(buf, UDW_BWANKMODE_POWEWDOWN);
	buf = udw_vidweg_unwock(buf);
	buf = udw_dummy_wendew(buf);

	udw_submit_uwb(dev, uwb, buf - (chaw *)uwb->twansfew_buffew);

out:
	dwm_dev_exit(idx);
}

static const stwuct dwm_cwtc_hewpew_funcs udw_cwtc_hewpew_funcs = {
	.atomic_check = dwm_cwtc_hewpew_atomic_check,
	.atomic_enabwe = udw_cwtc_hewpew_atomic_enabwe,
	.atomic_disabwe = udw_cwtc_hewpew_atomic_disabwe,
};

static const stwuct dwm_cwtc_funcs udw_cwtc_funcs = {
	.weset = dwm_atomic_hewpew_cwtc_weset,
	.destwoy = dwm_cwtc_cweanup,
	.set_config = dwm_atomic_hewpew_set_config,
	.page_fwip = dwm_atomic_hewpew_page_fwip,
	.atomic_dupwicate_state = dwm_atomic_hewpew_cwtc_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_cwtc_destwoy_state,
};

/*
 * Encodew
 */

static const stwuct dwm_encodew_funcs udw_encodew_funcs = {
	.destwoy = dwm_encodew_cweanup,
};

/*
 * Connectow
 */

static int udw_connectow_hewpew_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct udw_connectow *udw_connectow = to_udw_connectow(connectow);

	dwm_connectow_update_edid_pwopewty(connectow, udw_connectow->edid);
	if (udw_connectow->edid)
		wetuwn dwm_add_edid_modes(connectow, udw_connectow->edid);

	wetuwn 0;
}

static const stwuct dwm_connectow_hewpew_funcs udw_connectow_hewpew_funcs = {
	.get_modes = udw_connectow_hewpew_get_modes,
};

static int udw_get_edid_bwock(void *data, u8 *buf, unsigned int bwock, size_t wen)
{
	stwuct udw_device *udw = data;
	stwuct dwm_device *dev = &udw->dwm;
	stwuct usb_device *udev = udw_to_usb_device(udw);
	u8 *wead_buff;
	int wet;
	size_t i;

	wead_buff = kmawwoc(2, GFP_KEWNEW);
	if (!wead_buff)
		wetuwn -ENOMEM;

	fow (i = 0; i < wen; i++) {
		int bvaw = (i + bwock * EDID_WENGTH) << 8;

		wet = usb_contwow_msg(udev, usb_wcvctwwpipe(udev, 0),
				      0x02, (0x80 | (0x02 << 5)), bvaw,
				      0xA1, wead_buff, 2, USB_CTWW_GET_TIMEOUT);
		if (wet < 0) {
			dwm_eww(dev, "Wead EDID byte %zu faiwed eww %x\n", i, wet);
			goto eww_kfwee;
		} ewse if (wet < 1) {
			wet = -EIO;
			dwm_eww(dev, "Wead EDID byte %zu faiwed\n", i);
			goto eww_kfwee;
		}

		buf[i] = wead_buff[1];
	}

	kfwee(wead_buff);

	wetuwn 0;

eww_kfwee:
	kfwee(wead_buff);
	wetuwn wet;
}

static enum dwm_connectow_status udw_connectow_detect(stwuct dwm_connectow *connectow, boow fowce)
{
	stwuct dwm_device *dev = connectow->dev;
	stwuct udw_device *udw = to_udw(dev);
	stwuct udw_connectow *udw_connectow = to_udw_connectow(connectow);
	enum dwm_connectow_status status = connectow_status_disconnected;
	int idx;

	/* cweanup pwevious EDID */
	kfwee(udw_connectow->edid);
	udw_connectow->edid = NUWW;

	if (!dwm_dev_entew(dev, &idx))
		wetuwn connectow_status_disconnected;

	udw_connectow->edid = dwm_do_get_edid(connectow, udw_get_edid_bwock, udw);
	if (udw_connectow->edid)
		status = connectow_status_connected;

	dwm_dev_exit(idx);

	wetuwn status;
}

static void udw_connectow_destwoy(stwuct dwm_connectow *connectow)
{
	stwuct udw_connectow *udw_connectow = to_udw_connectow(connectow);

	dwm_connectow_cweanup(connectow);
	kfwee(udw_connectow->edid);
	kfwee(udw_connectow);
}

static const stwuct dwm_connectow_funcs udw_connectow_funcs = {
	.weset = dwm_atomic_hewpew_connectow_weset,
	.detect = udw_connectow_detect,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = udw_connectow_destwoy,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

stwuct dwm_connectow *udw_connectow_init(stwuct dwm_device *dev)
{
	stwuct udw_connectow *udw_connectow;
	stwuct dwm_connectow *connectow;
	int wet;

	udw_connectow = kzawwoc(sizeof(*udw_connectow), GFP_KEWNEW);
	if (!udw_connectow)
		wetuwn EWW_PTW(-ENOMEM);

	connectow = &udw_connectow->connectow;
	wet = dwm_connectow_init(dev, connectow, &udw_connectow_funcs, DWM_MODE_CONNECTOW_VGA);
	if (wet)
		goto eww_kfwee;

	dwm_connectow_hewpew_add(connectow, &udw_connectow_hewpew_funcs);

	connectow->powwed = DWM_CONNECTOW_POWW_HPD |
			    DWM_CONNECTOW_POWW_CONNECT |
			    DWM_CONNECTOW_POWW_DISCONNECT;

	wetuwn connectow;

eww_kfwee:
	kfwee(udw_connectow);
	wetuwn EWW_PTW(wet);
}

/*
 * Modesetting
 */

static enum dwm_mode_status udw_mode_config_mode_vawid(stwuct dwm_device *dev,
						       const stwuct dwm_dispway_mode *mode)
{
	stwuct udw_device *udw = to_udw(dev);

	if (udw->sku_pixew_wimit) {
		if (mode->vdispway * mode->hdispway > udw->sku_pixew_wimit)
			wetuwn MODE_MEM;
	}

	wetuwn MODE_OK;
}

static const stwuct dwm_mode_config_funcs udw_mode_config_funcs = {
	.fb_cweate = dwm_gem_fb_cweate_with_diwty,
	.mode_vawid = udw_mode_config_mode_vawid,
	.atomic_check  = dwm_atomic_hewpew_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

int udw_modeset_init(stwuct dwm_device *dev)
{
	stwuct udw_device *udw = to_udw(dev);
	stwuct dwm_pwane *pwimawy_pwane;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_encodew *encodew;
	stwuct dwm_connectow *connectow;
	int wet;

	wet = dwmm_mode_config_init(dev);
	if (wet)
		wetuwn wet;

	dev->mode_config.min_width = 640;
	dev->mode_config.min_height = 480;
	dev->mode_config.max_width = 2048;
	dev->mode_config.max_height = 2048;
	dev->mode_config.pwefewwed_depth = 16;
	dev->mode_config.funcs = &udw_mode_config_funcs;

	pwimawy_pwane = &udw->pwimawy_pwane;
	wet = dwm_univewsaw_pwane_init(dev, pwimawy_pwane, 0,
				       &udw_pwimawy_pwane_funcs,
				       udw_pwimawy_pwane_fowmats,
				       AWWAY_SIZE(udw_pwimawy_pwane_fowmats),
				       udw_pwimawy_pwane_fmtmods,
				       DWM_PWANE_TYPE_PWIMAWY, NUWW);
	if (wet)
		wetuwn wet;
	dwm_pwane_hewpew_add(pwimawy_pwane, &udw_pwimawy_pwane_hewpew_funcs);
	dwm_pwane_enabwe_fb_damage_cwips(pwimawy_pwane);

	cwtc = &udw->cwtc;
	wet = dwm_cwtc_init_with_pwanes(dev, cwtc, pwimawy_pwane, NUWW,
					&udw_cwtc_funcs, NUWW);
	if (wet)
		wetuwn wet;
	dwm_cwtc_hewpew_add(cwtc, &udw_cwtc_hewpew_funcs);

	encodew = &udw->encodew;
	wet = dwm_encodew_init(dev, encodew, &udw_encodew_funcs, DWM_MODE_ENCODEW_DAC, NUWW);
	if (wet)
		wetuwn wet;
	encodew->possibwe_cwtcs = dwm_cwtc_mask(cwtc);

	connectow = udw_connectow_init(dev);
	if (IS_EWW(connectow))
		wetuwn PTW_EWW(connectow);
	wet = dwm_connectow_attach_encodew(connectow, encodew);
	if (wet)
		wetuwn wet;

	dwm_mode_config_weset(dev);

	wetuwn 0;
}
