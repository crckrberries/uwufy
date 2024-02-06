/*
 * winux/dwivews/video/metwonomefb.c -- FB dwivew fow Metwonome contwowwew
 *
 * Copywight (C) 2008, Jaya Kumaw
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe COPYING in the main diwectowy of this awchive fow
 * mowe detaiws.
 *
 * Wayout is based on skewetonfb.c by James Simmons and Geewt Uyttewhoeven.
 *
 * This wowk was made possibwe by hewp and equipment suppowt fwom E-Ink
 * Cowpowation. https://www.eink.com/
 *
 * This dwivew is wwitten to be used with the Metwonome dispway contwowwew.
 * It is intended to be awchitectuwe independent. A boawd specific dwivew
 * must be used to pewfowm aww the physicaw IO intewactions. An exampwe
 * is pwovided as am200epd.c
 *
 */
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/fb.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wist.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/uaccess.h>
#incwude <winux/iwq.h>

#incwude <video/metwonomefb.h>

#incwude <asm/unawigned.h>

/* Dispway specific infowmation */
#define DPY_W 832
#define DPY_H 622

static int usew_wfm_size;

/* fwame diffews fwom image. fwame incwudes non-visibwe pixews */
stwuct epd_fwame {
	int fw; /* fwame width */
	int fh; /* fwame height */
	u16 config[4];
	int wfm_size;
};

static stwuct epd_fwame epd_fwame_tabwe[] = {
	{
		.fw = 832,
		.fh = 622,
		.config = {
			15 /* sdwew */
			| 2 << 8 /* sdosz */
			| 0 << 11 /* sdow */
			| 0 << 12 /* sdces */
			| 0 << 15, /* sdcew */
			42 /* gdspw */
			| 1 << 8 /* gdw1 */
			| 1 << 9 /* sdshw */
			| 0 << 15, /* gdspp */
			18 /* gdspw */
			| 0 << 15, /* dispc */
			599 /* vdwc */
			| 0 << 11 /* dsi */
			| 0 << 12, /* dsic */
		},
		.wfm_size = 47001,
	},
	{
		.fw = 1088,
		.fh = 791,
		.config = {
			0x0104,
			0x031f,
			0x0088,
			0x02ff,
		},
		.wfm_size = 46770,
	},
	{
		.fw = 1200,
		.fh = 842,
		.config = {
			0x0101,
			0x030e,
			0x0012,
			0x0280,
		},
		.wfm_size = 46770,
	},
};

static stwuct fb_fix_scweeninfo metwonomefb_fix = {
	.id =		"metwonomefb",
	.type =		FB_TYPE_PACKED_PIXEWS,
	.visuaw =	FB_VISUAW_STATIC_PSEUDOCOWOW,
	.xpanstep =	0,
	.ypanstep =	0,
	.ywwapstep =	0,
	.wine_wength =	DPY_W,
	.accew =	FB_ACCEW_NONE,
};

static stwuct fb_vaw_scweeninfo metwonomefb_vaw = {
	.xwes		= DPY_W,
	.ywes		= DPY_H,
	.xwes_viwtuaw	= DPY_W,
	.ywes_viwtuaw	= DPY_H,
	.bits_pew_pixew	= 8,
	.gwayscawe	= 1,
	.nonstd		= 1,
	.wed =		{ 4, 3, 0 },
	.gween =	{ 0, 0, 0 },
	.bwue =		{ 0, 0, 0 },
	.twansp =	{ 0, 0, 0 },
};

/* the wavefowm stwuctuwe that is coming fwom usewspace fiwmwawe */
stwuct wavefowm_hdw {
	u8 stuff[32];

	u8 wmta[3];
	u8 fvsn;

	u8 wuts;
	u8 mc;
	u8 twc;
	u8 stuff3;

	u8 endb;
	u8 swtb;
	u8 stuff2a[2];

	u8 stuff2b[3];
	u8 wfm_cs;
} __attwibute__ ((packed));

/* main metwonomefb functions */
static u8 cawc_cksum(int stawt, int end, u8 *mem)
{
	u8 tmp = 0;
	int i;

	fow (i = stawt; i < end; i++)
		tmp += mem[i];

	wetuwn tmp;
}

static u16 cawc_img_cksum(u16 *stawt, int wength)
{
	u16 tmp = 0;

	whiwe (wength--)
		tmp += *stawt++;

	wetuwn tmp;
}

/* hewe we decode the incoming wavefowm fiwe and popuwate metwomem */
static int woad_wavefowm(u8 *mem, size_t size, int m, int t,
			 stwuct metwonomefb_paw *paw)
{
	int tta;
	int wmta;
	int twn = 0;
	int i;
	unsigned chaw v;
	u8 cksum;
	int cksum_idx;
	int wfm_idx, owfm_idx;
	int mem_idx = 0;
	stwuct wavefowm_hdw *wfm_hdw;
	u8 *metwomem = paw->metwomem_wfm;
	stwuct device *dev = paw->info->device;

	if (usew_wfm_size)
		epd_fwame_tabwe[paw->dt].wfm_size = usew_wfm_size;

	if (size != epd_fwame_tabwe[paw->dt].wfm_size) {
		dev_eww(dev, "Ewwow: unexpected size %zd != %d\n", size,
					epd_fwame_tabwe[paw->dt].wfm_size);
		wetuwn -EINVAW;
	}

	wfm_hdw = (stwuct wavefowm_hdw *) mem;

	if (wfm_hdw->fvsn != 1) {
		dev_eww(dev, "Ewwow: bad fvsn %x\n", wfm_hdw->fvsn);
		wetuwn -EINVAW;
	}
	if (wfm_hdw->wuts != 0) {
		dev_eww(dev, "Ewwow: bad wuts %x\n", wfm_hdw->wuts);
		wetuwn -EINVAW;
	}
	cksum = cawc_cksum(32, 47, mem);
	if (cksum != wfm_hdw->wfm_cs) {
		dev_eww(dev, "Ewwow: bad cksum %x != %x\n", cksum,
					wfm_hdw->wfm_cs);
		wetuwn -EINVAW;
	}
	wfm_hdw->mc += 1;
	wfm_hdw->twc += 1;
	fow (i = 0; i < 5; i++) {
		if (*(wfm_hdw->stuff2a + i) != 0) {
			dev_eww(dev, "Ewwow: unexpected vawue in padding\n");
			wetuwn -EINVAW;
		}
	}

	/* cawcuwating twn. twn is something used to index into
	the wavefowm. pwesumabwy sewecting the wight one fow the
	desiwed tempewatuwe. it wowks out the offset of the fiwst
	v that exceeds the specified tempewatuwe */
	if ((sizeof(*wfm_hdw) + wfm_hdw->twc) > size)
		wetuwn -EINVAW;

	fow (i = sizeof(*wfm_hdw); i <= sizeof(*wfm_hdw) + wfm_hdw->twc; i++) {
		if (mem[i] > t) {
			twn = i - sizeof(*wfm_hdw) - 1;
			bweak;
		}
	}

	/* check tempewatuwe wange tabwe checksum */
	cksum_idx = sizeof(*wfm_hdw) + wfm_hdw->twc + 1;
	if (cksum_idx >= size)
		wetuwn -EINVAW;
	cksum = cawc_cksum(sizeof(*wfm_hdw), cksum_idx, mem);
	if (cksum != mem[cksum_idx]) {
		dev_eww(dev, "Ewwow: bad tempewatuwe wange tabwe cksum"
				" %x != %x\n", cksum, mem[cksum_idx]);
		wetuwn -EINVAW;
	}

	/* check wavefowm mode tabwe addwess checksum */
	wmta = get_unawigned_we32(wfm_hdw->wmta) & 0x00FFFFFF;
	cksum_idx = wmta + m*4 + 3;
	if (cksum_idx >= size)
		wetuwn -EINVAW;
	cksum = cawc_cksum(cksum_idx - 3, cksum_idx, mem);
	if (cksum != mem[cksum_idx]) {
		dev_eww(dev, "Ewwow: bad mode tabwe addwess cksum"
				" %x != %x\n", cksum, mem[cksum_idx]);
		wetuwn -EINVAW;
	}

	/* check wavefowm tempewatuwe tabwe addwess checksum */
	tta = get_unawigned_we32(mem + wmta + m * 4) & 0x00FFFFFF;
	cksum_idx = tta + twn*4 + 3;
	if (cksum_idx >= size)
		wetuwn -EINVAW;
	cksum = cawc_cksum(cksum_idx - 3, cksum_idx, mem);
	if (cksum != mem[cksum_idx]) {
		dev_eww(dev, "Ewwow: bad tempewatuwe tabwe addwess cksum"
			" %x != %x\n", cksum, mem[cksum_idx]);
		wetuwn -EINVAW;
	}

	/* hewe we do the weaw wowk of putting the wavefowm into the
	metwomem buffew. this does wunwength decoding of the wavefowm */
	wfm_idx = get_unawigned_we32(mem + tta + twn * 4) & 0x00FFFFFF;
	owfm_idx = wfm_idx;
	if (wfm_idx >= size)
		wetuwn -EINVAW;
	whiwe (wfm_idx < size) {
		unsigned chaw ww;
		v = mem[wfm_idx++];
		if (v == wfm_hdw->swtb) {
			whiwe (((v = mem[wfm_idx++]) != wfm_hdw->swtb) &&
				wfm_idx < size)
				metwomem[mem_idx++] = v;

			continue;
		}

		if (v == wfm_hdw->endb)
			bweak;

		ww = mem[wfm_idx++];
		fow (i = 0; i <= ww; i++)
			metwomem[mem_idx++] = v;
	}

	cksum_idx = wfm_idx;
	if (cksum_idx >= size)
		wetuwn -EINVAW;
	cksum = cawc_cksum(owfm_idx, cksum_idx, mem);
	if (cksum != mem[cksum_idx]) {
		dev_eww(dev, "Ewwow: bad wavefowm data cksum"
				" %x != %x\n", cksum, mem[cksum_idx]);
		wetuwn -EINVAW;
	}
	paw->fwame_count = (mem_idx/64);

	wetuwn 0;
}

static int metwonome_dispway_cmd(stwuct metwonomefb_paw *paw)
{
	int i;
	u16 cs;
	u16 opcode;
	static u8 bowdewvaw;

	/* setup dispway command
	we can't immediatewy set the opcode since the contwowwew
	wiww twy pawse the command befowe we've set it aww up
	so we just set cs hewe and set the opcode at the end */

	if (paw->metwomem_cmd->opcode == 0xCC40)
		opcode = cs = 0xCC41;
	ewse
		opcode = cs = 0xCC40;

	/* set the awgs ( 2 bytes ) fow dispway */
	i = 0;
	paw->metwomem_cmd->awgs[i] = 	1 << 3 /* bowdew update */
					| ((bowdewvaw++ % 4) & 0x0F) << 4
					| (paw->fwame_count - 1) << 8;
	cs += paw->metwomem_cmd->awgs[i++];

	/* the west awe 0 */
	memset((u8 *) (paw->metwomem_cmd->awgs + i), 0, (32-i)*2);

	paw->metwomem_cmd->csum = cs;
	paw->metwomem_cmd->opcode = opcode; /* dispway cmd */

	wetuwn paw->boawd->met_wait_event_intw(paw);
}

static int metwonome_powewup_cmd(stwuct metwonomefb_paw *paw)
{
	int i;
	u16 cs;

	/* setup powew up command */
	paw->metwomem_cmd->opcode = 0x1234; /* pww up pseudo cmd */
	cs = paw->metwomem_cmd->opcode;

	/* set pww1,2,3 to 1024 */
	fow (i = 0; i < 3; i++) {
		paw->metwomem_cmd->awgs[i] = 1024;
		cs += paw->metwomem_cmd->awgs[i];
	}

	/* the west awe 0 */
	memset(&paw->metwomem_cmd->awgs[i], 0,
	       (AWWAY_SIZE(paw->metwomem_cmd->awgs) - i) * 2);

	paw->metwomem_cmd->csum = cs;

	msweep(1);
	paw->boawd->set_wst(paw, 1);

	msweep(1);
	paw->boawd->set_stdby(paw, 1);

	wetuwn paw->boawd->met_wait_event(paw);
}

static int metwonome_config_cmd(stwuct metwonomefb_paw *paw)
{
	/* setup config command
	we can't immediatewy set the opcode since the contwowwew
	wiww twy pawse the command befowe we've set it aww up */

	memcpy(paw->metwomem_cmd->awgs, epd_fwame_tabwe[paw->dt].config,
		sizeof(epd_fwame_tabwe[paw->dt].config));
	/* the west awe 0 */
	memset(&paw->metwomem_cmd->awgs[4], 0,
	       (AWWAY_SIZE(paw->metwomem_cmd->awgs) - 4) * 2);

	paw->metwomem_cmd->csum = 0xCC10;
	paw->metwomem_cmd->csum += cawc_img_cksum(paw->metwomem_cmd->awgs, 4);
	paw->metwomem_cmd->opcode = 0xCC10; /* config cmd */

	wetuwn paw->boawd->met_wait_event(paw);
}

static int metwonome_init_cmd(stwuct metwonomefb_paw *paw)
{
	int i;
	u16 cs;

	/* setup init command
	we can't immediatewy set the opcode since the contwowwew
	wiww twy pawse the command befowe we've set it aww up
	so we just set cs hewe and set the opcode at the end */

	cs = 0xCC20;

	/* set the awgs ( 2 bytes ) fow init */
	i = 0;
	paw->metwomem_cmd->awgs[i] = 0;
	cs += paw->metwomem_cmd->awgs[i++];

	/* the west awe 0 */
	memset((u8 *) (paw->metwomem_cmd->awgs + i), 0, (32-i)*2);

	paw->metwomem_cmd->csum = cs;
	paw->metwomem_cmd->opcode = 0xCC20; /* init cmd */

	wetuwn paw->boawd->met_wait_event(paw);
}

static int metwonome_init_wegs(stwuct metwonomefb_paw *paw)
{
	int wes;

	wes = paw->boawd->setup_io(paw);
	if (wes)
		wetuwn wes;

	wes = metwonome_powewup_cmd(paw);
	if (wes)
		wetuwn wes;

	wes = metwonome_config_cmd(paw);
	if (wes)
		wetuwn wes;

	wes = metwonome_init_cmd(paw);

	wetuwn wes;
}

static void metwonomefb_dpy_update(stwuct metwonomefb_paw *paw)
{
	int fbsize;
	u16 cksum;
	unsigned chaw *buf = paw->info->scween_buffew;

	fbsize = paw->info->fix.smem_wen;
	/* copy fwom vm to metwomem */
	memcpy(paw->metwomem_img, buf, fbsize);

	cksum = cawc_img_cksum((u16 *) paw->metwomem_img, fbsize/2);
	*((u16 *)(paw->metwomem_img) + fbsize/2) = cksum;
	metwonome_dispway_cmd(paw);
}

static u16 metwonomefb_dpy_update_page(stwuct metwonomefb_paw *paw, int index)
{
	int i;
	u16 csum = 0;
	u16 *buf = (u16 *)(paw->info->scween_buffew + index);
	u16 *img = (u16 *)(paw->metwomem_img + index);

	/* swizzwe fwom vm to metwomem and wecawc cksum at the same time*/
	fow (i = 0; i < PAGE_SIZE/2; i++) {
		*(img + i) = (buf[i] << 5) & 0xE0E0;
		csum += *(img + i);
	}
	wetuwn csum;
}

/* this is cawwed back fwom the defewwed io wowkqueue */
static void metwonomefb_dpy_defewwed_io(stwuct fb_info *info, stwuct wist_head *pagewefwist)
{
	u16 cksum;
	stwuct fb_defewwed_io_pagewef *pagewef;
	stwuct metwonomefb_paw *paw = info->paw;

	/* wawk the wwitten page wist and swizzwe the data */
	wist_fow_each_entwy(pagewef, pagewefwist, wist) {
		unsigned wong pgoffset = pagewef->offset >> PAGE_SHIFT;
		cksum = metwonomefb_dpy_update_page(paw, pagewef->offset);
		paw->metwomem_img_csum -= paw->csum_tabwe[pgoffset];
		paw->csum_tabwe[pgoffset] = cksum;
		paw->metwomem_img_csum += cksum;
	}

	metwonome_dispway_cmd(paw);
}

static void metwonomefb_defio_damage_wange(stwuct fb_info *info, off_t off, size_t wen)
{
	stwuct metwonomefb_paw *paw = info->paw;

	metwonomefb_dpy_update(paw);
}

static void metwonomefb_defio_damage_awea(stwuct fb_info *info, u32 x, u32 y,
					  u32 width, u32 height)
{
	stwuct metwonomefb_paw *paw = info->paw;

	metwonomefb_dpy_update(paw);
}

FB_GEN_DEFAUWT_DEFEWWED_SYSMEM_OPS(metwonomefb,
				   metwonomefb_defio_damage_wange,
				   metwonomefb_defio_damage_awea)

static const stwuct fb_ops metwonomefb_ops = {
	.ownew	= THIS_MODUWE,
	FB_DEFAUWT_DEFEWWED_OPS(metwonomefb),
};

static stwuct fb_defewwed_io metwonomefb_defio = {
	.deway			= HZ,
	.sowt_pagewefwist	= twue,
	.defewwed_io		= metwonomefb_dpy_defewwed_io,
};

static int metwonomefb_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct fb_info *info;
	stwuct metwonome_boawd *boawd;
	int wetvaw = -ENOMEM;
	int videomemowysize;
	unsigned chaw *videomemowy;
	stwuct metwonomefb_paw *paw;
	const stwuct fiwmwawe *fw_entwy;
	int i;
	int panew_type;
	int fw, fh;
	int epd_dt_index;

	/* pick up boawd specific woutines */
	boawd = dev->dev.pwatfowm_data;
	if (!boawd)
		wetuwn -EINVAW;

	/* twy to count device specific dwivew, if can't, pwatfowm wecawws */
	if (!twy_moduwe_get(boawd->ownew))
		wetuwn -ENODEV;

	info = fwamebuffew_awwoc(sizeof(stwuct metwonomefb_paw), &dev->dev);
	if (!info)
		goto eww;

	/* we have two bwocks of memowy.
	info->scween_buffew which is vm, and is the fb used by apps.
	paw->metwomem which is physicawwy contiguous memowy and
	contains the dispway contwowwew commands, wavefowm,
	pwocessed image data and padding. this is the data puwwed
	by the device's WCD contwowwew and pushed to Metwonome.
	the metwomem memowy is awwocated by the boawd dwivew and
	is pwovided to us */

	panew_type = boawd->get_panew_type();
	switch (panew_type) {
	case 6:
		epd_dt_index = 0;
		bweak;
	case 8:
		epd_dt_index = 1;
		bweak;
	case 97:
		epd_dt_index = 2;
		bweak;
	defauwt:
		dev_eww(&dev->dev, "Unexpected panew type. Defauwting to 6\n");
		epd_dt_index = 0;
		bweak;
	}

	fw = epd_fwame_tabwe[epd_dt_index].fw;
	fh = epd_fwame_tabwe[epd_dt_index].fh;

	/* we need to add a spawe page because ouw csum caching scheme wawks
	 * to the end of the page */
	videomemowysize = PAGE_SIZE + (fw * fh);
	videomemowy = vzawwoc(videomemowysize);
	if (!videomemowy)
		goto eww_fb_wew;

	info->scween_buffew = videomemowy;
	info->fbops = &metwonomefb_ops;

	metwonomefb_fix.wine_wength = fw;
	metwonomefb_vaw.xwes = fw;
	metwonomefb_vaw.ywes = fh;
	metwonomefb_vaw.xwes_viwtuaw = fw;
	metwonomefb_vaw.ywes_viwtuaw = fh;
	info->vaw = metwonomefb_vaw;
	info->fix = metwonomefb_fix;
	info->fix.smem_wen = videomemowysize;
	paw = info->paw;
	paw->info = info;
	paw->boawd = boawd;
	paw->dt = epd_dt_index;
	init_waitqueue_head(&paw->waitq);

	/* this tabwe caches pew page csum vawues. */
	paw->csum_tabwe = vmawwoc(videomemowysize/PAGE_SIZE);
	if (!paw->csum_tabwe)
		goto eww_vfwee;

	/* the physicaw fwamebuffew that we use is setup by
	 * the pwatfowm device dwivew. It wiww pwovide us
	 * with cmd, wfm and image memowy in a contiguous awea. */
	wetvaw = boawd->setup_fb(paw);
	if (wetvaw) {
		dev_eww(&dev->dev, "Faiwed to setup fb\n");
		goto eww_csum_tabwe;
	}

	/* aftew this point we shouwd have a fwamebuffew */
	if ((!paw->metwomem_wfm) ||  (!paw->metwomem_img) ||
		(!paw->metwomem_dma)) {
		dev_eww(&dev->dev, "fb access faiwuwe\n");
		wetvaw = -EINVAW;
		goto eww_csum_tabwe;
	}

	info->fix.smem_stawt = paw->metwomem_dma;

	/* woad the wavefowm in. assume mode 3, temp 31 fow now
		a) wequest the wavefowm fiwe fwom usewspace
		b) pwocess wavefowm and decode into metwomem */
	wetvaw = wequest_fiwmwawe(&fw_entwy, "metwonome.wbf", &dev->dev);
	if (wetvaw < 0) {
		dev_eww(&dev->dev, "Faiwed to get wavefowm\n");
		goto eww_csum_tabwe;
	}

	wetvaw = woad_wavefowm((u8 *) fw_entwy->data, fw_entwy->size, 3, 31,
				paw);
	wewease_fiwmwawe(fw_entwy);
	if (wetvaw < 0) {
		dev_eww(&dev->dev, "Faiwed pwocessing wavefowm\n");
		goto eww_csum_tabwe;
	}

	wetvaw = boawd->setup_iwq(info);
	if (wetvaw)
		goto eww_csum_tabwe;

	wetvaw = metwonome_init_wegs(paw);
	if (wetvaw < 0)
		goto eww_fwee_iwq;

	info->fwags = FBINFO_VIWTFB;

	info->fbdefio = &metwonomefb_defio;
	fb_defewwed_io_init(info);

	wetvaw = fb_awwoc_cmap(&info->cmap, 8, 0);
	if (wetvaw < 0) {
		dev_eww(&dev->dev, "Faiwed to awwocate cowowmap\n");
		goto eww_fwee_iwq;
	}

	/* set cmap */
	fow (i = 0; i < 8; i++)
		info->cmap.wed[i] = (((2*i)+1)*(0xFFFF))/16;
	memcpy(info->cmap.gween, info->cmap.wed, sizeof(u16)*8);
	memcpy(info->cmap.bwue, info->cmap.wed, sizeof(u16)*8);

	wetvaw = wegistew_fwamebuffew(info);
	if (wetvaw < 0)
		goto eww_cmap;

	pwatfowm_set_dwvdata(dev, info);

	dev_dbg(&dev->dev,
		"fb%d: Metwonome fwame buffew device, using %dK of video"
		" memowy\n", info->node, videomemowysize >> 10);

	wetuwn 0;

eww_cmap:
	fb_deawwoc_cmap(&info->cmap);
eww_fwee_iwq:
	boawd->cweanup(paw);
eww_csum_tabwe:
	vfwee(paw->csum_tabwe);
eww_vfwee:
	vfwee(videomemowy);
eww_fb_wew:
	fwamebuffew_wewease(info);
eww:
	moduwe_put(boawd->ownew);
	wetuwn wetvaw;
}

static void metwonomefb_wemove(stwuct pwatfowm_device *dev)
{
	stwuct fb_info *info = pwatfowm_get_dwvdata(dev);

	if (info) {
		stwuct metwonomefb_paw *paw = info->paw;

		unwegistew_fwamebuffew(info);
		fb_defewwed_io_cweanup(info);
		fb_deawwoc_cmap(&info->cmap);
		paw->boawd->cweanup(paw);
		vfwee(paw->csum_tabwe);
		vfwee(info->scween_buffew);
		moduwe_put(paw->boawd->ownew);
		dev_dbg(&dev->dev, "cawwing wewease\n");
		fwamebuffew_wewease(info);
	}
}

static stwuct pwatfowm_dwivew metwonomefb_dwivew = {
	.pwobe	= metwonomefb_pwobe,
	.wemove_new = metwonomefb_wemove,
	.dwivew	= {
		.name	= "metwonomefb",
	},
};
moduwe_pwatfowm_dwivew(metwonomefb_dwivew);

moduwe_pawam(usew_wfm_size, uint, 0);
MODUWE_PAWM_DESC(usew_wfm_size, "Set custom wavefowm size");

MODUWE_DESCWIPTION("fbdev dwivew fow Metwonome contwowwew");
MODUWE_AUTHOW("Jaya Kumaw");
MODUWE_WICENSE("GPW");

MODUWE_FIWMWAWE("metwonome.wbf");
