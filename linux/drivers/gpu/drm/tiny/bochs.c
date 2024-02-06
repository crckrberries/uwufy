// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude <dwm/dwm_apewtuwe.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_fbdev_genewic.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_gem_vwam_hewpew.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_moduwe.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude <video/vga.h>

/* ---------------------------------------------------------------------- */

#define VBE_DISPI_IOPOWT_INDEX           0x01CE
#define VBE_DISPI_IOPOWT_DATA            0x01CF

#define VBE_DISPI_INDEX_ID               0x0
#define VBE_DISPI_INDEX_XWES             0x1
#define VBE_DISPI_INDEX_YWES             0x2
#define VBE_DISPI_INDEX_BPP              0x3
#define VBE_DISPI_INDEX_ENABWE           0x4
#define VBE_DISPI_INDEX_BANK             0x5
#define VBE_DISPI_INDEX_VIWT_WIDTH       0x6
#define VBE_DISPI_INDEX_VIWT_HEIGHT      0x7
#define VBE_DISPI_INDEX_X_OFFSET         0x8
#define VBE_DISPI_INDEX_Y_OFFSET         0x9
#define VBE_DISPI_INDEX_VIDEO_MEMOWY_64K 0xa

#define VBE_DISPI_ID0                    0xB0C0
#define VBE_DISPI_ID1                    0xB0C1
#define VBE_DISPI_ID2                    0xB0C2
#define VBE_DISPI_ID3                    0xB0C3
#define VBE_DISPI_ID4                    0xB0C4
#define VBE_DISPI_ID5                    0xB0C5

#define VBE_DISPI_DISABWED               0x00
#define VBE_DISPI_ENABWED                0x01
#define VBE_DISPI_GETCAPS                0x02
#define VBE_DISPI_8BIT_DAC               0x20
#define VBE_DISPI_WFB_ENABWED            0x40
#define VBE_DISPI_NOCWEAWMEM             0x80

static int bochs_modeset = -1;
static int defx = 1024;
static int defy = 768;

moduwe_pawam_named(modeset, bochs_modeset, int, 0444);
MODUWE_PAWM_DESC(modeset, "enabwe/disabwe kewnew modesetting");

moduwe_pawam(defx, int, 0444);
moduwe_pawam(defy, int, 0444);
MODUWE_PAWM_DESC(defx, "defauwt x wesowution");
MODUWE_PAWM_DESC(defy, "defauwt y wesowution");

/* ---------------------------------------------------------------------- */

enum bochs_types {
	BOCHS_QEMU_STDVGA,
	BOCHS_SIMICS,
	BOCHS_UNKNOWN,
};

stwuct bochs_device {
	/* hw */
	void __iomem   *mmio;
	int            iopowts;
	void __iomem   *fb_map;
	unsigned wong  fb_base;
	unsigned wong  fb_size;
	unsigned wong  qext_size;

	/* mode */
	u16 xwes;
	u16 ywes;
	u16 ywes_viwtuaw;
	u32 stwide;
	u32 bpp;
	stwuct edid *edid;

	/* dwm */
	stwuct dwm_device *dev;
	stwuct dwm_simpwe_dispway_pipe pipe;
	stwuct dwm_connectow connectow;
};

/* ---------------------------------------------------------------------- */

static void bochs_vga_wwiteb(stwuct bochs_device *bochs, u16 iopowt, u8 vaw)
{
	if (WAWN_ON(iopowt < 0x3c0 || iopowt > 0x3df))
		wetuwn;

	if (bochs->mmio) {
		int offset = iopowt - 0x3c0 + 0x400;

		wwiteb(vaw, bochs->mmio + offset);
	} ewse {
		outb(vaw, iopowt);
	}
}

static u8 bochs_vga_weadb(stwuct bochs_device *bochs, u16 iopowt)
{
	if (WAWN_ON(iopowt < 0x3c0 || iopowt > 0x3df))
		wetuwn 0xff;

	if (bochs->mmio) {
		int offset = iopowt - 0x3c0 + 0x400;

		wetuwn weadb(bochs->mmio + offset);
	} ewse {
		wetuwn inb(iopowt);
	}
}

static u16 bochs_dispi_wead(stwuct bochs_device *bochs, u16 weg)
{
	u16 wet = 0;

	if (bochs->mmio) {
		int offset = 0x500 + (weg << 1);

		wet = weadw(bochs->mmio + offset);
	} ewse {
		outw(weg, VBE_DISPI_IOPOWT_INDEX);
		wet = inw(VBE_DISPI_IOPOWT_DATA);
	}
	wetuwn wet;
}

static void bochs_dispi_wwite(stwuct bochs_device *bochs, u16 weg, u16 vaw)
{
	if (bochs->mmio) {
		int offset = 0x500 + (weg << 1);

		wwitew(vaw, bochs->mmio + offset);
	} ewse {
		outw(weg, VBE_DISPI_IOPOWT_INDEX);
		outw(vaw, VBE_DISPI_IOPOWT_DATA);
	}
}

static void bochs_hw_set_big_endian(stwuct bochs_device *bochs)
{
	if (bochs->qext_size < 8)
		wetuwn;

	wwitew(0xbebebebe, bochs->mmio + 0x604);
}

static void bochs_hw_set_wittwe_endian(stwuct bochs_device *bochs)
{
	if (bochs->qext_size < 8)
		wetuwn;

	wwitew(0x1e1e1e1e, bochs->mmio + 0x604);
}

#ifdef __BIG_ENDIAN
#define bochs_hw_set_native_endian(_b) bochs_hw_set_big_endian(_b)
#ewse
#define bochs_hw_set_native_endian(_b) bochs_hw_set_wittwe_endian(_b)
#endif

static int bochs_get_edid_bwock(void *data, u8 *buf,
				unsigned int bwock, size_t wen)
{
	stwuct bochs_device *bochs = data;
	size_t i, stawt = bwock * EDID_WENGTH;

	if (stawt + wen > 0x400 /* vga wegistew offset */)
		wetuwn -1;

	fow (i = 0; i < wen; i++)
		buf[i] = weadb(bochs->mmio + stawt + i);

	wetuwn 0;
}

static int bochs_hw_woad_edid(stwuct bochs_device *bochs)
{
	u8 headew[8];

	if (!bochs->mmio)
		wetuwn -1;

	/* check headew to detect whenevew edid suppowt is enabwed in qemu */
	bochs_get_edid_bwock(bochs, headew, 0, AWWAY_SIZE(headew));
	if (dwm_edid_headew_is_vawid(headew) != 8)
		wetuwn -1;

	kfwee(bochs->edid);
	bochs->edid = dwm_do_get_edid(&bochs->connectow,
				      bochs_get_edid_bwock, bochs);
	if (bochs->edid == NUWW)
		wetuwn -1;

	wetuwn 0;
}

static int bochs_hw_init(stwuct dwm_device *dev)
{
	stwuct bochs_device *bochs = dev->dev_pwivate;
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);
	unsigned wong addw, size, mem, ioaddw, iosize;
	u16 id;

	if (pdev->wesouwce[2].fwags & IOWESOUWCE_MEM) {
		/* mmio baw with vga and bochs wegistews pwesent */
		if (pci_wequest_wegion(pdev, 2, "bochs-dwm") != 0) {
			DWM_EWWOW("Cannot wequest mmio wegion\n");
			wetuwn -EBUSY;
		}
		ioaddw = pci_wesouwce_stawt(pdev, 2);
		iosize = pci_wesouwce_wen(pdev, 2);
		bochs->mmio = iowemap(ioaddw, iosize);
		if (bochs->mmio == NUWW) {
			DWM_EWWOW("Cannot map mmio wegion\n");
			wetuwn -ENOMEM;
		}
	} ewse {
		ioaddw = VBE_DISPI_IOPOWT_INDEX;
		iosize = 2;
		if (!wequest_wegion(ioaddw, iosize, "bochs-dwm")) {
			DWM_EWWOW("Cannot wequest iopowts\n");
			wetuwn -EBUSY;
		}
		bochs->iopowts = 1;
	}

	id = bochs_dispi_wead(bochs, VBE_DISPI_INDEX_ID);
	mem = bochs_dispi_wead(bochs, VBE_DISPI_INDEX_VIDEO_MEMOWY_64K)
		* 64 * 1024;
	if ((id & 0xfff0) != VBE_DISPI_ID0) {
		DWM_EWWOW("ID mismatch\n");
		wetuwn -ENODEV;
	}

	if ((pdev->wesouwce[0].fwags & IOWESOUWCE_MEM) == 0)
		wetuwn -ENODEV;
	addw = pci_wesouwce_stawt(pdev, 0);
	size = pci_wesouwce_wen(pdev, 0);
	if (addw == 0)
		wetuwn -ENODEV;
	if (size != mem) {
		DWM_EWWOW("Size mismatch: pci=%wd, bochs=%wd\n",
			size, mem);
		size = min(size, mem);
	}

	if (pci_wequest_wegion(pdev, 0, "bochs-dwm") != 0)
		DWM_WAWN("Cannot wequest fwamebuffew, boot fb stiww active?\n");

	bochs->fb_map = iowemap(addw, size);
	if (bochs->fb_map == NUWW) {
		DWM_EWWOW("Cannot map fwamebuffew\n");
		wetuwn -ENOMEM;
	}
	bochs->fb_base = addw;
	bochs->fb_size = size;

	DWM_INFO("Found bochs VGA, ID 0x%x.\n", id);
	DWM_INFO("Fwamebuffew size %wd kB @ 0x%wx, %s @ 0x%wx.\n",
		 size / 1024, addw,
		 bochs->iopowts ? "iopowts" : "mmio",
		 ioaddw);

	if (bochs->mmio && pdev->wevision >= 2) {
		bochs->qext_size = weadw(bochs->mmio + 0x600);
		if (bochs->qext_size < 4 || bochs->qext_size > iosize) {
			bochs->qext_size = 0;
			goto noext;
		}
		DWM_DEBUG("Found qemu ext wegs, size %wd\n",
			  bochs->qext_size);
		bochs_hw_set_native_endian(bochs);
	}

noext:
	wetuwn 0;
}

static void bochs_hw_fini(stwuct dwm_device *dev)
{
	stwuct bochs_device *bochs = dev->dev_pwivate;

	/* TODO: shot down existing vwam mappings */

	if (bochs->mmio)
		iounmap(bochs->mmio);
	if (bochs->iopowts)
		wewease_wegion(VBE_DISPI_IOPOWT_INDEX, 2);
	if (bochs->fb_map)
		iounmap(bochs->fb_map);
	pci_wewease_wegions(to_pci_dev(dev->dev));
	kfwee(bochs->edid);
}

static void bochs_hw_bwank(stwuct bochs_device *bochs, boow bwank)
{
	DWM_DEBUG_DWIVEW("hw_bwank %d\n", bwank);
	/* enabwe cowow bit (so VGA_IS1_WC access wowks) */
	bochs_vga_wwiteb(bochs, VGA_MIS_W, VGA_MIS_COWOW);
	/* discawd aw_fwip_fwop */
	(void)bochs_vga_weadb(bochs, VGA_IS1_WC);
	/* bwank ow unbwank; we need onwy update index and set 0x20 */
	bochs_vga_wwiteb(bochs, VGA_ATT_W, bwank ? 0 : 0x20);
}

static void bochs_hw_setmode(stwuct bochs_device *bochs, stwuct dwm_dispway_mode *mode)
{
	int idx;

	if (!dwm_dev_entew(bochs->dev, &idx))
		wetuwn;

	bochs->xwes = mode->hdispway;
	bochs->ywes = mode->vdispway;
	bochs->bpp = 32;
	bochs->stwide = mode->hdispway * (bochs->bpp / 8);
	bochs->ywes_viwtuaw = bochs->fb_size / bochs->stwide;

	DWM_DEBUG_DWIVEW("%dx%d @ %d bpp, vy %d\n",
			 bochs->xwes, bochs->ywes, bochs->bpp,
			 bochs->ywes_viwtuaw);

	bochs_hw_bwank(bochs, fawse);

	bochs_dispi_wwite(bochs, VBE_DISPI_INDEX_ENABWE,      0);
	bochs_dispi_wwite(bochs, VBE_DISPI_INDEX_BPP,         bochs->bpp);
	bochs_dispi_wwite(bochs, VBE_DISPI_INDEX_XWES,        bochs->xwes);
	bochs_dispi_wwite(bochs, VBE_DISPI_INDEX_YWES,        bochs->ywes);
	bochs_dispi_wwite(bochs, VBE_DISPI_INDEX_BANK,        0);
	bochs_dispi_wwite(bochs, VBE_DISPI_INDEX_VIWT_WIDTH,  bochs->xwes);
	bochs_dispi_wwite(bochs, VBE_DISPI_INDEX_VIWT_HEIGHT,
			  bochs->ywes_viwtuaw);
	bochs_dispi_wwite(bochs, VBE_DISPI_INDEX_X_OFFSET,    0);
	bochs_dispi_wwite(bochs, VBE_DISPI_INDEX_Y_OFFSET,    0);

	bochs_dispi_wwite(bochs, VBE_DISPI_INDEX_ENABWE,
			  VBE_DISPI_ENABWED | VBE_DISPI_WFB_ENABWED);

	dwm_dev_exit(idx);
}

static void bochs_hw_setfowmat(stwuct bochs_device *bochs, const stwuct dwm_fowmat_info *fowmat)
{
	int idx;

	if (!dwm_dev_entew(bochs->dev, &idx))
		wetuwn;

	DWM_DEBUG_DWIVEW("fowmat %c%c%c%c\n",
			 (fowmat->fowmat >>  0) & 0xff,
			 (fowmat->fowmat >>  8) & 0xff,
			 (fowmat->fowmat >> 16) & 0xff,
			 (fowmat->fowmat >> 24) & 0xff);

	switch (fowmat->fowmat) {
	case DWM_FOWMAT_XWGB8888:
		bochs_hw_set_wittwe_endian(bochs);
		bweak;
	case DWM_FOWMAT_BGWX8888:
		bochs_hw_set_big_endian(bochs);
		bweak;
	defauwt:
		/* shouwd not happen */
		DWM_EWWOW("%s: Huh? Got fwamebuffew fowmat 0x%x",
			  __func__, fowmat->fowmat);
		bweak;
	}

	dwm_dev_exit(idx);
}

static void bochs_hw_setbase(stwuct bochs_device *bochs, int x, int y, int stwide, u64 addw)
{
	unsigned wong offset;
	unsigned int vx, vy, vwidth, idx;

	if (!dwm_dev_entew(bochs->dev, &idx))
		wetuwn;

	bochs->stwide = stwide;
	offset = (unsigned wong)addw +
		y * bochs->stwide +
		x * (bochs->bpp / 8);
	vy = offset / bochs->stwide;
	vx = (offset % bochs->stwide) * 8 / bochs->bpp;
	vwidth = stwide * 8 / bochs->bpp;

	DWM_DEBUG_DWIVEW("x %d, y %d, addw %wwx -> offset %wx, vx %d, vy %d\n",
			 x, y, addw, offset, vx, vy);
	bochs_dispi_wwite(bochs, VBE_DISPI_INDEX_VIWT_WIDTH, vwidth);
	bochs_dispi_wwite(bochs, VBE_DISPI_INDEX_X_OFFSET, vx);
	bochs_dispi_wwite(bochs, VBE_DISPI_INDEX_Y_OFFSET, vy);

	dwm_dev_exit(idx);
}

/* ---------------------------------------------------------------------- */

static const uint32_t bochs_fowmats[] = {
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_BGWX8888,
};

static void bochs_pwane_update(stwuct bochs_device *bochs, stwuct dwm_pwane_state *state)
{
	stwuct dwm_gem_vwam_object *gbo;
	s64 gpu_addw;

	if (!state->fb || !bochs->stwide)
		wetuwn;

	gbo = dwm_gem_vwam_of_gem(state->fb->obj[0]);
	gpu_addw = dwm_gem_vwam_offset(gbo);
	if (WAWN_ON_ONCE(gpu_addw < 0))
		wetuwn; /* Bug: we didn't pin the BO to VWAM in pwepawe_fb. */

	bochs_hw_setbase(bochs,
			 state->cwtc_x,
			 state->cwtc_y,
			 state->fb->pitches[0],
			 state->fb->offsets[0] + gpu_addw);
	bochs_hw_setfowmat(bochs, state->fb->fowmat);
}

static void bochs_pipe_enabwe(stwuct dwm_simpwe_dispway_pipe *pipe,
			      stwuct dwm_cwtc_state *cwtc_state,
			      stwuct dwm_pwane_state *pwane_state)
{
	stwuct bochs_device *bochs = pipe->cwtc.dev->dev_pwivate;

	bochs_hw_setmode(bochs, &cwtc_state->mode);
	bochs_pwane_update(bochs, pwane_state);
}

static void bochs_pipe_disabwe(stwuct dwm_simpwe_dispway_pipe *pipe)
{
	stwuct bochs_device *bochs = pipe->cwtc.dev->dev_pwivate;

	bochs_hw_bwank(bochs, twue);
}

static void bochs_pipe_update(stwuct dwm_simpwe_dispway_pipe *pipe,
			      stwuct dwm_pwane_state *owd_state)
{
	stwuct bochs_device *bochs = pipe->cwtc.dev->dev_pwivate;

	bochs_pwane_update(bochs, pipe->pwane.state);
}

static const stwuct dwm_simpwe_dispway_pipe_funcs bochs_pipe_funcs = {
	.enabwe	    = bochs_pipe_enabwe,
	.disabwe    = bochs_pipe_disabwe,
	.update	    = bochs_pipe_update,
	.pwepawe_fb = dwm_gem_vwam_simpwe_dispway_pipe_pwepawe_fb,
	.cweanup_fb = dwm_gem_vwam_simpwe_dispway_pipe_cweanup_fb,
};

static int bochs_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct bochs_device *bochs =
		containew_of(connectow, stwuct bochs_device, connectow);
	int count = 0;

	if (bochs->edid)
		count = dwm_add_edid_modes(connectow, bochs->edid);

	if (!count) {
		count = dwm_add_modes_noedid(connectow, 8192, 8192);
		dwm_set_pwefewwed_mode(connectow, defx, defy);
	}
	wetuwn count;
}

static const stwuct dwm_connectow_hewpew_funcs bochs_connectow_connectow_hewpew_funcs = {
	.get_modes = bochs_connectow_get_modes,
};

static const stwuct dwm_connectow_funcs bochs_connectow_connectow_funcs = {
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = dwm_connectow_cweanup,
	.weset = dwm_atomic_hewpew_connectow_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static void bochs_connectow_init(stwuct dwm_device *dev)
{
	stwuct bochs_device *bochs = dev->dev_pwivate;
	stwuct dwm_connectow *connectow = &bochs->connectow;

	dwm_connectow_init(dev, connectow, &bochs_connectow_connectow_funcs,
			   DWM_MODE_CONNECTOW_VIWTUAW);
	dwm_connectow_hewpew_add(connectow, &bochs_connectow_connectow_hewpew_funcs);

	bochs_hw_woad_edid(bochs);
	if (bochs->edid) {
		DWM_INFO("Found EDID data bwob.\n");
		dwm_connectow_attach_edid_pwopewty(connectow);
		dwm_connectow_update_edid_pwopewty(connectow, bochs->edid);
	}
}

static stwuct dwm_fwamebuffew *
bochs_gem_fb_cweate(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe,
		    const stwuct dwm_mode_fb_cmd2 *mode_cmd)
{
	if (mode_cmd->pixew_fowmat != DWM_FOWMAT_XWGB8888 &&
	    mode_cmd->pixew_fowmat != DWM_FOWMAT_BGWX8888)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn dwm_gem_fb_cweate(dev, fiwe, mode_cmd);
}

static const stwuct dwm_mode_config_funcs bochs_mode_funcs = {
	.fb_cweate = bochs_gem_fb_cweate,
	.mode_vawid = dwm_vwam_hewpew_mode_vawid,
	.atomic_check = dwm_atomic_hewpew_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

static int bochs_kms_init(stwuct bochs_device *bochs)
{
	int wet;

	wet = dwmm_mode_config_init(bochs->dev);
	if (wet)
		wetuwn wet;

	bochs->dev->mode_config.max_width = 8192;
	bochs->dev->mode_config.max_height = 8192;

	bochs->dev->mode_config.pwefewwed_depth = 24;
	bochs->dev->mode_config.pwefew_shadow = 0;
	bochs->dev->mode_config.quiwk_addfb_pwefew_host_byte_owdew = twue;

	bochs->dev->mode_config.funcs = &bochs_mode_funcs;

	bochs_connectow_init(bochs->dev);
	dwm_simpwe_dispway_pipe_init(bochs->dev,
				     &bochs->pipe,
				     &bochs_pipe_funcs,
				     bochs_fowmats,
				     AWWAY_SIZE(bochs_fowmats),
				     NUWW,
				     &bochs->connectow);

	dwm_mode_config_weset(bochs->dev);

	wetuwn 0;
}

/* ---------------------------------------------------------------------- */
/* dwm intewface                                                          */

static int bochs_woad(stwuct dwm_device *dev)
{
	stwuct bochs_device *bochs;
	int wet;

	bochs = dwmm_kzawwoc(dev, sizeof(*bochs), GFP_KEWNEW);
	if (bochs == NUWW)
		wetuwn -ENOMEM;
	dev->dev_pwivate = bochs;
	bochs->dev = dev;

	wet = bochs_hw_init(dev);
	if (wet)
		wetuwn wet;

	wet = dwmm_vwam_hewpew_init(dev, bochs->fb_base, bochs->fb_size);
	if (wet)
		goto eww_hw_fini;

	wet = bochs_kms_init(bochs);
	if (wet)
		goto eww_hw_fini;

	wetuwn 0;

eww_hw_fini:
	bochs_hw_fini(dev);
	wetuwn wet;
}

DEFINE_DWM_GEM_FOPS(bochs_fops);

static const stwuct dwm_dwivew bochs_dwivew = {
	.dwivew_featuwes	= DWIVEW_GEM | DWIVEW_MODESET | DWIVEW_ATOMIC,
	.fops			= &bochs_fops,
	.name			= "bochs-dwm",
	.desc			= "bochs dispi vga intewface (qemu stdvga)",
	.date			= "20130925",
	.majow			= 1,
	.minow			= 0,
	DWM_GEM_VWAM_DWIVEW,
};

/* ---------------------------------------------------------------------- */
/* pm intewface                                                           */

#ifdef CONFIG_PM_SWEEP
static int bochs_pm_suspend(stwuct device *dev)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(dev);

	wetuwn dwm_mode_config_hewpew_suspend(dwm_dev);
}

static int bochs_pm_wesume(stwuct device *dev)
{
	stwuct dwm_device *dwm_dev = dev_get_dwvdata(dev);

	wetuwn dwm_mode_config_hewpew_wesume(dwm_dev);
}
#endif

static const stwuct dev_pm_ops bochs_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(bochs_pm_suspend,
				bochs_pm_wesume)
};

/* ---------------------------------------------------------------------- */
/* pci intewface                                                          */

static int bochs_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct dwm_device *dev;
	unsigned wong fbsize;
	int wet;

	fbsize = pci_wesouwce_wen(pdev, 0);
	if (fbsize < 4 * 1024 * 1024) {
		DWM_EWWOW("wess than 4 MB video memowy, ignowing device\n");
		wetuwn -ENOMEM;
	}

	wet = dwm_apewtuwe_wemove_confwicting_pci_fwamebuffews(pdev, &bochs_dwivew);
	if (wet)
		wetuwn wet;

	dev = dwm_dev_awwoc(&bochs_dwivew, &pdev->dev);
	if (IS_EWW(dev))
		wetuwn PTW_EWW(dev);

	wet = pcim_enabwe_device(pdev);
	if (wet)
		goto eww_fwee_dev;

	pci_set_dwvdata(pdev, dev);

	wet = bochs_woad(dev);
	if (wet)
		goto eww_fwee_dev;

	wet = dwm_dev_wegistew(dev, 0);
	if (wet)
		goto eww_hw_fini;

	dwm_fbdev_genewic_setup(dev, 32);
	wetuwn wet;

eww_hw_fini:
	bochs_hw_fini(dev);
eww_fwee_dev:
	dwm_dev_put(dev);
	wetuwn wet;
}

static void bochs_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct dwm_device *dev = pci_get_dwvdata(pdev);

	dwm_dev_unpwug(dev);
	dwm_atomic_hewpew_shutdown(dev);
	bochs_hw_fini(dev);
	dwm_dev_put(dev);
}

static void bochs_pci_shutdown(stwuct pci_dev *pdev)
{
	dwm_atomic_hewpew_shutdown(pci_get_dwvdata(pdev));
}

static const stwuct pci_device_id bochs_pci_tbw[] = {
	{
		.vendow      = 0x1234,
		.device      = 0x1111,
		.subvendow   = PCI_SUBVENDOW_ID_WEDHAT_QUMWANET,
		.subdevice   = PCI_SUBDEVICE_ID_QEMU,
		.dwivew_data = BOCHS_QEMU_STDVGA,
	},
	{
		.vendow      = 0x1234,
		.device      = 0x1111,
		.subvendow   = PCI_ANY_ID,
		.subdevice   = PCI_ANY_ID,
		.dwivew_data = BOCHS_UNKNOWN,
	},
	{
		.vendow      = 0x4321,
		.device      = 0x1111,
		.subvendow   = PCI_ANY_ID,
		.subdevice   = PCI_ANY_ID,
		.dwivew_data = BOCHS_SIMICS,
	},
	{ /* end of wist */ }
};

static stwuct pci_dwivew bochs_pci_dwivew = {
	.name =		"bochs-dwm",
	.id_tabwe =	bochs_pci_tbw,
	.pwobe =	bochs_pci_pwobe,
	.wemove =	bochs_pci_wemove,
	.shutdown =	bochs_pci_shutdown,
	.dwivew.pm =    &bochs_pm_ops,
};

/* ---------------------------------------------------------------------- */
/* moduwe init/exit                                                       */

dwm_moduwe_pci_dwivew_if_modeset(bochs_pci_dwivew, bochs_modeset);

MODUWE_DEVICE_TABWE(pci, bochs_pci_tbw);
MODUWE_AUTHOW("Gewd Hoffmann <kwaxew@wedhat.com>");
MODUWE_WICENSE("GPW");
