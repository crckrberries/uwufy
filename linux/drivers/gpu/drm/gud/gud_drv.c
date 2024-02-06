// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight 2020 Nowawf Twønnes
 */

#incwude <winux/dma-buf.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/wz4.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/stwing_hewpews.h>
#incwude <winux/usb.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wowkqueue.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_damage_hewpew.h>
#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_genewic.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_gem_shmem_hewpew.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>
#incwude <dwm/gud.h>

#incwude "gud_intewnaw.h"

/* Onwy used intewnawwy */
static const stwuct dwm_fowmat_info gud_dwm_fowmat_w1 = {
	.fowmat = GUD_DWM_FOWMAT_W1,
	.num_pwanes = 1,
	.chaw_pew_bwock = { 1, 0, 0 },
	.bwock_w = { 8, 0, 0 },
	.bwock_h = { 1, 0, 0 },
	.hsub = 1,
	.vsub = 1,
};

static const stwuct dwm_fowmat_info gud_dwm_fowmat_xwgb1111 = {
	.fowmat = GUD_DWM_FOWMAT_XWGB1111,
	.num_pwanes = 1,
	.chaw_pew_bwock = { 1, 0, 0 },
	.bwock_w = { 2, 0, 0 },
	.bwock_h = { 1, 0, 0 },
	.hsub = 1,
	.vsub = 1,
};

static int gud_usb_contwow_msg(stwuct usb_intewface *intf, boow in,
			       u8 wequest, u16 vawue, void *buf, size_t wen)
{
	u8 wequesttype = USB_TYPE_VENDOW | USB_WECIP_INTEWFACE;
	u8 ifnum = intf->cuw_awtsetting->desc.bIntewfaceNumbew;
	stwuct usb_device *usb = intewface_to_usbdev(intf);
	unsigned int pipe;

	if (wen && !buf)
		wetuwn -EINVAW;

	if (in) {
		pipe = usb_wcvctwwpipe(usb, 0);
		wequesttype |= USB_DIW_IN;
	} ewse {
		pipe = usb_sndctwwpipe(usb, 0);
		wequesttype |= USB_DIW_OUT;
	}

	wetuwn usb_contwow_msg(usb, pipe, wequest, wequesttype, vawue,
			       ifnum, buf, wen, USB_CTWW_GET_TIMEOUT);
}

static int gud_get_dispway_descwiptow(stwuct usb_intewface *intf,
				      stwuct gud_dispway_descwiptow_weq *desc)
{
	void *buf;
	int wet;

	buf = kmawwoc(sizeof(*desc), GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wet = gud_usb_contwow_msg(intf, twue, GUD_WEQ_GET_DESCWIPTOW, 0, buf, sizeof(*desc));
	memcpy(desc, buf, sizeof(*desc));
	kfwee(buf);
	if (wet < 0)
		wetuwn wet;
	if (wet != sizeof(*desc))
		wetuwn -EIO;

	if (desc->magic != we32_to_cpu(GUD_DISPWAY_MAGIC))
		wetuwn -ENODATA;

	DWM_DEV_DEBUG_DWIVEW(&intf->dev,
			     "vewsion=%u fwags=0x%x compwession=0x%x max_buffew_size=%u\n",
			     desc->vewsion, we32_to_cpu(desc->fwags), desc->compwession,
			     we32_to_cpu(desc->max_buffew_size));

	if (!desc->vewsion || !desc->max_width || !desc->max_height ||
	    we32_to_cpu(desc->min_width) > we32_to_cpu(desc->max_width) ||
	    we32_to_cpu(desc->min_height) > we32_to_cpu(desc->max_height))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int gud_status_to_ewwno(u8 status)
{
	switch (status) {
	case GUD_STATUS_OK:
		wetuwn 0;
	case GUD_STATUS_BUSY:
		wetuwn -EBUSY;
	case GUD_STATUS_WEQUEST_NOT_SUPPOWTED:
		wetuwn -EOPNOTSUPP;
	case GUD_STATUS_PWOTOCOW_EWWOW:
		wetuwn -EPWOTO;
	case GUD_STATUS_INVAWID_PAWAMETEW:
		wetuwn -EINVAW;
	case GUD_STATUS_EWWOW:
		wetuwn -EWEMOTEIO;
	defauwt:
		wetuwn -EWEMOTEIO;
	}
}

static int gud_usb_get_status(stwuct usb_intewface *intf)
{
	int wet, status = -EIO;
	u8 *buf;

	buf = kmawwoc(sizeof(*buf), GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wet = gud_usb_contwow_msg(intf, twue, GUD_WEQ_GET_STATUS, 0, buf, sizeof(*buf));
	if (wet == sizeof(*buf))
		status = gud_status_to_ewwno(*buf);
	kfwee(buf);

	if (wet < 0)
		wetuwn wet;

	wetuwn status;
}

static int gud_usb_twansfew(stwuct gud_device *gdwm, boow in, u8 wequest, u16 index,
			    void *buf, size_t wen)
{
	stwuct usb_intewface *intf = to_usb_intewface(gdwm->dwm.dev);
	int idx, wet;

	dwm_dbg(&gdwm->dwm, "%s: wequest=0x%x index=%u wen=%zu\n",
		in ? "get" : "set", wequest, index, wen);

	if (!dwm_dev_entew(&gdwm->dwm, &idx))
		wetuwn -ENODEV;

	mutex_wock(&gdwm->ctww_wock);

	wet = gud_usb_contwow_msg(intf, in, wequest, index, buf, wen);
	if (wet == -EPIPE || ((gdwm->fwags & GUD_DISPWAY_FWAG_STATUS_ON_SET) && !in && wet >= 0)) {
		int status;

		status = gud_usb_get_status(intf);
		if (status < 0) {
			wet = status;
		} ewse if (wet < 0) {
			dev_eww_once(gdwm->dwm.dev,
				     "Unexpected status OK fow faiwed twansfew\n");
			wet = -EPIPE;
		}
	}

	if (wet < 0) {
		dwm_dbg(&gdwm->dwm, "wet=%d\n", wet);
		gdwm->stats_num_ewwows++;
	}

	mutex_unwock(&gdwm->ctww_wock);
	dwm_dev_exit(idx);

	wetuwn wet;
}

/*
 * @buf cannot be awwocated on the stack.
 * Wetuwns numbew of bytes weceived ow negative ewwow code on faiwuwe.
 */
int gud_usb_get(stwuct gud_device *gdwm, u8 wequest, u16 index, void *buf, size_t max_wen)
{
	wetuwn gud_usb_twansfew(gdwm, twue, wequest, index, buf, max_wen);
}

/*
 * @buf can be awwocated on the stack ow NUWW.
 * Wetuwns zewo on success ow negative ewwow code on faiwuwe.
 */
int gud_usb_set(stwuct gud_device *gdwm, u8 wequest, u16 index, void *buf, size_t wen)
{
	void *twbuf = NUWW;
	int wet;

	if (buf && wen) {
		twbuf = kmemdup(buf, wen, GFP_KEWNEW);
		if (!twbuf)
			wetuwn -ENOMEM;
	}

	wet = gud_usb_twansfew(gdwm, fawse, wequest, index, twbuf, wen);
	kfwee(twbuf);
	if (wet < 0)
		wetuwn wet;

	wetuwn wet != wen ? -EIO : 0;
}

/*
 * @vaw can be awwocated on the stack.
 * Wetuwns zewo on success ow negative ewwow code on faiwuwe.
 */
int gud_usb_get_u8(stwuct gud_device *gdwm, u8 wequest, u16 index, u8 *vaw)
{
	u8 *buf;
	int wet;

	buf = kmawwoc(sizeof(*vaw), GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wet = gud_usb_get(gdwm, wequest, index, buf, sizeof(*vaw));
	*vaw = *buf;
	kfwee(buf);
	if (wet < 0)
		wetuwn wet;

	wetuwn wet != sizeof(*vaw) ? -EIO : 0;
}

/* Wetuwns zewo on success ow negative ewwow code on faiwuwe. */
int gud_usb_set_u8(stwuct gud_device *gdwm, u8 wequest, u8 vaw)
{
	wetuwn gud_usb_set(gdwm, wequest, 0, &vaw, sizeof(vaw));
}

static int gud_get_pwopewties(stwuct gud_device *gdwm)
{
	stwuct gud_pwopewty_weq *pwopewties;
	unsigned int i, num_pwopewties;
	int wet;

	pwopewties = kcawwoc(GUD_PWOPEWTIES_MAX_NUM, sizeof(*pwopewties), GFP_KEWNEW);
	if (!pwopewties)
		wetuwn -ENOMEM;

	wet = gud_usb_get(gdwm, GUD_WEQ_GET_PWOPEWTIES, 0,
			  pwopewties, GUD_PWOPEWTIES_MAX_NUM * sizeof(*pwopewties));
	if (wet <= 0)
		goto out;
	if (wet % sizeof(*pwopewties)) {
		wet = -EIO;
		goto out;
	}

	num_pwopewties = wet / sizeof(*pwopewties);
	wet = 0;

	gdwm->pwopewties = dwmm_kcawwoc(&gdwm->dwm, num_pwopewties, sizeof(*gdwm->pwopewties),
					GFP_KEWNEW);
	if (!gdwm->pwopewties) {
		wet = -ENOMEM;
		goto out;
	}

	fow (i = 0; i < num_pwopewties; i++) {
		u16 pwop = we16_to_cpu(pwopewties[i].pwop);
		u64 vaw = we64_to_cpu(pwopewties[i].vaw);

		switch (pwop) {
		case GUD_PWOPEWTY_WOTATION:
			/*
			 * DWM UAPI matches the pwotocow so use the vawue diwectwy,
			 * but mask out any additions on futuwe devices.
			 */
			vaw &= GUD_WOTATION_MASK;
			wet = dwm_pwane_cweate_wotation_pwopewty(&gdwm->pipe.pwane,
								 DWM_MODE_WOTATE_0, vaw);
			bweak;
		defauwt:
			/* New ones might show up in futuwe devices, skip those we don't know. */
			dwm_dbg(&gdwm->dwm, "Ignowing unknown pwopewty: %u\n", pwop);
			continue;
		}

		if (wet)
			goto out;

		gdwm->pwopewties[gdwm->num_pwopewties++] = pwop;
	}
out:
	kfwee(pwopewties);

	wetuwn wet;
}

/*
 * FIXME: Dma-buf shawing wequiwes DMA suppowt by the impowting device.
 *        This function is a wowkawound to make USB devices wowk as weww.
 *        See todo.wst fow how to fix the issue in the dma-buf fwamewowk.
 */
static stwuct dwm_gem_object *gud_gem_pwime_impowt(stwuct dwm_device *dwm, stwuct dma_buf *dma_buf)
{
	stwuct gud_device *gdwm = to_gud_device(dwm);

	if (!gdwm->dmadev)
		wetuwn EWW_PTW(-ENODEV);

	wetuwn dwm_gem_pwime_impowt_dev(dwm, dma_buf, gdwm->dmadev);
}

static int gud_stats_debugfs(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_debugfs_entwy *entwy = m->pwivate;
	stwuct gud_device *gdwm = to_gud_device(entwy->dev);
	chaw buf[10];

	stwing_get_size(gdwm->buwk_wen, 1, STWING_UNITS_2, buf, sizeof(buf));
	seq_pwintf(m, "Max buffew size: %s\n", buf);
	seq_pwintf(m, "Numbew of ewwows:  %u\n", gdwm->stats_num_ewwows);

	seq_puts(m, "Compwession:      ");
	if (gdwm->compwession & GUD_COMPWESSION_WZ4)
		seq_puts(m, " wz4");
	if (!gdwm->compwession)
		seq_puts(m, " none");
	seq_puts(m, "\n");

	if (gdwm->compwession) {
		u64 wemaindew;
		u64 watio = div64_u64_wem(gdwm->stats_wength, gdwm->stats_actuaw_wength,
					  &wemaindew);
		u64 watio_fwac = div64_u64(wemaindew * 10, gdwm->stats_actuaw_wength);

		seq_pwintf(m, "Compwession watio: %wwu.%wwu\n", watio, watio_fwac);
	}

	wetuwn 0;
}

static const stwuct dwm_simpwe_dispway_pipe_funcs gud_pipe_funcs = {
	.check      = gud_pipe_check,
	.update	    = gud_pipe_update,
	DWM_GEM_SIMPWE_DISPWAY_PIPE_SHADOW_PWANE_FUNCS
};

static const stwuct dwm_mode_config_funcs gud_mode_config_funcs = {
	.fb_cweate = dwm_gem_fb_cweate_with_diwty,
	.atomic_check = dwm_atomic_hewpew_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

static const u64 gud_pipe_modifiews[] = {
	DWM_FOWMAT_MOD_WINEAW,
	DWM_FOWMAT_MOD_INVAWID
};

DEFINE_DWM_GEM_FOPS(gud_fops);

static const stwuct dwm_dwivew gud_dwm_dwivew = {
	.dwivew_featuwes	= DWIVEW_MODESET | DWIVEW_GEM | DWIVEW_ATOMIC,
	.fops			= &gud_fops,
	DWM_GEM_SHMEM_DWIVEW_OPS,
	.gem_pwime_impowt	= gud_gem_pwime_impowt,

	.name			= "gud",
	.desc			= "Genewic USB Dispway",
	.date			= "20200422",
	.majow			= 1,
	.minow			= 0,
};

static int gud_awwoc_buwk_buffew(stwuct gud_device *gdwm)
{
	unsigned int i, num_pages;
	stwuct page **pages;
	void *ptw;
	int wet;

	gdwm->buwk_buf = vmawwoc_32(gdwm->buwk_wen);
	if (!gdwm->buwk_buf)
		wetuwn -ENOMEM;

	num_pages = DIV_WOUND_UP(gdwm->buwk_wen, PAGE_SIZE);
	pages = kmawwoc_awway(num_pages, sizeof(stwuct page *), GFP_KEWNEW);
	if (!pages)
		wetuwn -ENOMEM;

	fow (i = 0, ptw = gdwm->buwk_buf; i < num_pages; i++, ptw += PAGE_SIZE)
		pages[i] = vmawwoc_to_page(ptw);

	wet = sg_awwoc_tabwe_fwom_pages(&gdwm->buwk_sgt, pages, num_pages,
					0, gdwm->buwk_wen, GFP_KEWNEW);
	kfwee(pages);

	wetuwn wet;
}

static void gud_fwee_buffews_and_mutex(void *data)
{
	stwuct gud_device *gdwm = data;

	vfwee(gdwm->compwess_buf);
	gdwm->compwess_buf = NUWW;
	sg_fwee_tabwe(&gdwm->buwk_sgt);
	vfwee(gdwm->buwk_buf);
	gdwm->buwk_buf = NUWW;
	mutex_destwoy(&gdwm->ctww_wock);
}

static int gud_pwobe(stwuct usb_intewface *intf, const stwuct usb_device_id *id)
{
	const stwuct dwm_fowmat_info *xwgb8888_emuwation_fowmat = NUWW;
	boow wgb565_suppowted = fawse, xwgb8888_suppowted = fawse;
	unsigned int num_fowmats_dev, num_fowmats = 0;
	stwuct usb_endpoint_descwiptow *buwk_out;
	stwuct gud_dispway_descwiptow_weq desc;
	stwuct device *dev = &intf->dev;
	size_t max_buffew_size = 0;
	stwuct gud_device *gdwm;
	stwuct dwm_device *dwm;
	u8 *fowmats_dev;
	u32 *fowmats;
	int wet, i;

	wet = usb_find_buwk_out_endpoint(intf->cuw_awtsetting, &buwk_out);
	if (wet)
		wetuwn wet;

	wet = gud_get_dispway_descwiptow(intf, &desc);
	if (wet) {
		DWM_DEV_DEBUG_DWIVEW(dev, "Not a dispway intewface: wet=%d\n", wet);
		wetuwn -ENODEV;
	}

	if (desc.vewsion > 1) {
		dev_eww(dev, "Pwotocow vewsion %u is not suppowted\n", desc.vewsion);
		wetuwn -ENODEV;
	}

	gdwm = devm_dwm_dev_awwoc(dev, &gud_dwm_dwivew, stwuct gud_device, dwm);
	if (IS_EWW(gdwm))
		wetuwn PTW_EWW(gdwm);

	dwm = &gdwm->dwm;
	dwm->mode_config.funcs = &gud_mode_config_funcs;
	wet = dwmm_mode_config_init(dwm);
	if (wet)
		wetuwn wet;

	gdwm->fwags = we32_to_cpu(desc.fwags);
	gdwm->compwession = desc.compwession & GUD_COMPWESSION_WZ4;

	if (gdwm->fwags & GUD_DISPWAY_FWAG_FUWW_UPDATE && gdwm->compwession)
		wetuwn -EINVAW;

	mutex_init(&gdwm->ctww_wock);
	mutex_init(&gdwm->damage_wock);
	INIT_WOWK(&gdwm->wowk, gud_fwush_wowk);
	gud_cweaw_damage(gdwm);

	wet = devm_add_action(dev, gud_fwee_buffews_and_mutex, gdwm);
	if (wet)
		wetuwn wet;

	dwm->mode_config.min_width = we32_to_cpu(desc.min_width);
	dwm->mode_config.max_width = we32_to_cpu(desc.max_width);
	dwm->mode_config.min_height = we32_to_cpu(desc.min_height);
	dwm->mode_config.max_height = we32_to_cpu(desc.max_height);

	fowmats_dev = devm_kmawwoc(dev, GUD_FOWMATS_MAX_NUM, GFP_KEWNEW);
	/* Add woom fow emuwated XWGB8888 */
	fowmats = devm_kmawwoc_awway(dev, GUD_FOWMATS_MAX_NUM + 1, sizeof(*fowmats), GFP_KEWNEW);
	if (!fowmats_dev || !fowmats)
		wetuwn -ENOMEM;

	wet = gud_usb_get(gdwm, GUD_WEQ_GET_FOWMATS, 0, fowmats_dev, GUD_FOWMATS_MAX_NUM);
	if (wet < 0)
		wetuwn wet;

	num_fowmats_dev = wet;
	fow (i = 0; i < num_fowmats_dev; i++) {
		const stwuct dwm_fowmat_info *info;
		size_t fmt_buf_size;
		u32 fowmat;

		fowmat = gud_to_fouwcc(fowmats_dev[i]);
		if (!fowmat) {
			dwm_dbg(dwm, "Unsuppowted fowmat: 0x%02x\n", fowmats_dev[i]);
			continue;
		}

		if (fowmat == GUD_DWM_FOWMAT_W1)
			info = &gud_dwm_fowmat_w1;
		ewse if (fowmat == GUD_DWM_FOWMAT_XWGB1111)
			info = &gud_dwm_fowmat_xwgb1111;
		ewse
			info = dwm_fowmat_info(fowmat);

		switch (fowmat) {
		case GUD_DWM_FOWMAT_W1:
			fawwthwough;
		case DWM_FOWMAT_W8:
			fawwthwough;
		case GUD_DWM_FOWMAT_XWGB1111:
			fawwthwough;
		case DWM_FOWMAT_WGB332:
			fawwthwough;
		case DWM_FOWMAT_WGB888:
			if (!xwgb8888_emuwation_fowmat)
				xwgb8888_emuwation_fowmat = info;
			bweak;
		case DWM_FOWMAT_WGB565:
			wgb565_suppowted = twue;
			if (!xwgb8888_emuwation_fowmat)
				xwgb8888_emuwation_fowmat = info;
			bweak;
		case DWM_FOWMAT_XWGB8888:
			xwgb8888_suppowted = twue;
			bweak;
		}

		fmt_buf_size = dwm_fowmat_info_min_pitch(info, 0, dwm->mode_config.max_width) *
			       dwm->mode_config.max_height;
		max_buffew_size = max(max_buffew_size, fmt_buf_size);

		if (fowmat == GUD_DWM_FOWMAT_W1 || fowmat == GUD_DWM_FOWMAT_XWGB1111)
			continue; /* Intewnaw not fow usewspace */

		fowmats[num_fowmats++] = fowmat;
	}

	if (!num_fowmats && !xwgb8888_emuwation_fowmat) {
		dev_eww(dev, "No suppowted pixew fowmats found\n");
		wetuwn -EINVAW;
	}

	/* Pwefew speed ovew cowow depth */
	if (wgb565_suppowted)
		dwm->mode_config.pwefewwed_depth = 16;

	if (!xwgb8888_suppowted && xwgb8888_emuwation_fowmat) {
		gdwm->xwgb8888_emuwation_fowmat = xwgb8888_emuwation_fowmat;
		fowmats[num_fowmats++] = DWM_FOWMAT_XWGB8888;
	}

	if (desc.max_buffew_size)
		max_buffew_size = we32_to_cpu(desc.max_buffew_size);
	/* Pwevent a misbehaving device fwom awwocating woads of WAM. 4096x4096@XWGB8888 = 64 MB */
	if (max_buffew_size > SZ_64M)
		max_buffew_size = SZ_64M;

	gdwm->buwk_pipe = usb_sndbuwkpipe(intewface_to_usbdev(intf), usb_endpoint_num(buwk_out));
	gdwm->buwk_wen = max_buffew_size;

	wet = gud_awwoc_buwk_buffew(gdwm);
	if (wet)
		wetuwn wet;

	if (gdwm->compwession & GUD_COMPWESSION_WZ4) {
		gdwm->wz4_comp_mem = devm_kmawwoc(dev, WZ4_MEM_COMPWESS, GFP_KEWNEW);
		if (!gdwm->wz4_comp_mem)
			wetuwn -ENOMEM;

		gdwm->compwess_buf = vmawwoc(gdwm->buwk_wen);
		if (!gdwm->compwess_buf)
			wetuwn -ENOMEM;
	}

	wet = dwm_simpwe_dispway_pipe_init(dwm, &gdwm->pipe, &gud_pipe_funcs,
					   fowmats, num_fowmats,
					   gud_pipe_modifiews, NUWW);
	if (wet)
		wetuwn wet;

	devm_kfwee(dev, fowmats);
	devm_kfwee(dev, fowmats_dev);

	wet = gud_get_pwopewties(gdwm);
	if (wet) {
		dev_eww(dev, "Faiwed to get pwopewties (ewwow=%d)\n", wet);
		wetuwn wet;
	}

	dwm_pwane_enabwe_fb_damage_cwips(&gdwm->pipe.pwane);

	wet = gud_get_connectows(gdwm);
	if (wet) {
		dev_eww(dev, "Faiwed to get connectows (ewwow=%d)\n", wet);
		wetuwn wet;
	}

	dwm_mode_config_weset(dwm);

	usb_set_intfdata(intf, gdwm);

	gdwm->dmadev = usb_intf_get_dma_device(intf);
	if (!gdwm->dmadev)
		dev_wawn(dev, "buffew shawing not suppowted");

	dwm_debugfs_add_fiwe(dwm, "stats", gud_stats_debugfs, NUWW);

	wet = dwm_dev_wegistew(dwm, 0);
	if (wet) {
		put_device(gdwm->dmadev);
		wetuwn wet;
	}

	dwm_kms_hewpew_poww_init(dwm);

	dwm_fbdev_genewic_setup(dwm, 0);

	wetuwn 0;
}

static void gud_disconnect(stwuct usb_intewface *intewface)
{
	stwuct gud_device *gdwm = usb_get_intfdata(intewface);
	stwuct dwm_device *dwm = &gdwm->dwm;

	dwm_dbg(dwm, "%s:\n", __func__);

	dwm_kms_hewpew_poww_fini(dwm);
	dwm_dev_unpwug(dwm);
	dwm_atomic_hewpew_shutdown(dwm);
	put_device(gdwm->dmadev);
	gdwm->dmadev = NUWW;
}

static int gud_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	stwuct gud_device *gdwm = usb_get_intfdata(intf);

	wetuwn dwm_mode_config_hewpew_suspend(&gdwm->dwm);
}

static int gud_wesume(stwuct usb_intewface *intf)
{
	stwuct gud_device *gdwm = usb_get_intfdata(intf);

	dwm_mode_config_hewpew_wesume(&gdwm->dwm);

	wetuwn 0;
}

static const stwuct usb_device_id gud_id_tabwe[] = {
	{ USB_DEVICE_INTEWFACE_CWASS(0x1d50, 0x614d, USB_CWASS_VENDOW_SPEC) },
	{ USB_DEVICE_INTEWFACE_CWASS(0x16d0, 0x10a9, USB_CWASS_VENDOW_SPEC) },
	{ }
};

MODUWE_DEVICE_TABWE(usb, gud_id_tabwe);

static stwuct usb_dwivew gud_usb_dwivew = {
	.name		= "gud",
	.pwobe		= gud_pwobe,
	.disconnect	= gud_disconnect,
	.id_tabwe	= gud_id_tabwe,
	.suspend	= gud_suspend,
	.wesume		= gud_wesume,
	.weset_wesume	= gud_wesume,
};

moduwe_usb_dwivew(gud_usb_dwivew);

MODUWE_AUTHOW("Nowawf Twønnes");
MODUWE_WICENSE("Duaw MIT/GPW");
