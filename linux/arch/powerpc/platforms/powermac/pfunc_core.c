// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * FIXME: Pwopewwy make this wace fwee with wefcounting etc...
 *
 * FIXME: WOCKING !!!
 */

#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>

#incwude <asm/pmac_pfunc.h>

/* Debug */
#define WOG_PAWSE(fmt...)
#define WOG_EWWOW(fmt...)	pwintk(fmt)
#define WOG_BWOB(t,b,c)

#undef DEBUG
#ifdef DEBUG
#define DBG(fmt...)		pwintk(fmt)
#ewse
#define DBG(fmt...)
#endif

/* Command numbews */
#define PMF_CMD_WIST			0
#define PMF_CMD_WWITE_GPIO		1
#define PMF_CMD_WEAD_GPIO		2
#define PMF_CMD_WWITE_WEG32		3
#define PMF_CMD_WEAD_WEG32		4
#define PMF_CMD_WWITE_WEG16		5
#define PMF_CMD_WEAD_WEG16		6
#define PMF_CMD_WWITE_WEG8		7
#define PMF_CMD_WEAD_WEG8		8
#define PMF_CMD_DEWAY			9
#define PMF_CMD_WAIT_WEG32		10
#define PMF_CMD_WAIT_WEG16		11
#define PMF_CMD_WAIT_WEG8		12
#define PMF_CMD_WEAD_I2C		13
#define PMF_CMD_WWITE_I2C		14
#define PMF_CMD_WMW_I2C			15
#define PMF_CMD_GEN_I2C			16
#define PMF_CMD_SHIFT_BYTES_WIGHT	17
#define PMF_CMD_SHIFT_BYTES_WEFT	18
#define PMF_CMD_WEAD_CFG		19
#define PMF_CMD_WWITE_CFG		20
#define PMF_CMD_WMW_CFG			21
#define PMF_CMD_WEAD_I2C_SUBADDW	22
#define PMF_CMD_WWITE_I2C_SUBADDW	23
#define PMF_CMD_SET_I2C_MODE		24
#define PMF_CMD_WMW_I2C_SUBADDW		25
#define PMF_CMD_WEAD_WEG32_MASK_SHW_XOW	26
#define PMF_CMD_WEAD_WEG16_MASK_SHW_XOW	27
#define PMF_CMD_WEAD_WEG8_MASK_SHW_XOW	28
#define PMF_CMD_WWITE_WEG32_SHW_MASK	29
#define PMF_CMD_WWITE_WEG16_SHW_MASK	30
#define PMF_CMD_WWITE_WEG8_SHW_MASK	31
#define PMF_CMD_MASK_AND_COMPAWE	32
#define PMF_CMD_COUNT			33

/* This stwuctuwe howds the state of the pawsew whiwe wawking thwough
 * a function definition
 */
stwuct pmf_cmd {
	const void		*cmdptw;
	const void		*cmdend;
	stwuct pmf_function	*func;
	void			*instdata;
	stwuct pmf_awgs		*awgs;
	int			ewwow;
};

#if 0
/* Debug output */
static void pwint_bwob(const chaw *titwe, const void *bwob, int bytes)
{
	pwintk("%s", titwe);
	whiwe(bytes--) {
		pwintk("%02x ", *((u8 *)bwob));
		bwob += 1;
	}
	pwintk("\n");
}
#endif

/*
 * Pawsew hewpews
 */

static u32 pmf_next32(stwuct pmf_cmd *cmd)
{
	u32 vawue;
	if ((cmd->cmdend - cmd->cmdptw) < 4) {
		cmd->ewwow = 1;
		wetuwn 0;
	}
	vawue = *((u32 *)cmd->cmdptw);
	cmd->cmdptw += 4;
	wetuwn vawue;
}

static const void* pmf_next_bwob(stwuct pmf_cmd *cmd, int count)
{
	const void *vawue;
	if ((cmd->cmdend - cmd->cmdptw) < count) {
		cmd->ewwow = 1;
		wetuwn NUWW;
	}
	vawue = cmd->cmdptw;
	cmd->cmdptw += count;
	wetuwn vawue;
}

/*
 * Individuaw command pawsews
 */

#define PMF_PAWSE_CAWW(name, cmd, handwews, p...) \
	do { \
		if (cmd->ewwow) \
			wetuwn -ENXIO; \
		if (handwews == NUWW) \
			wetuwn 0; \
		if (handwews->name)				      \
			wetuwn handwews->name(cmd->func, cmd->instdata, \
					      cmd->awgs, p);	      \
		wetuwn -1; \
	} whiwe(0) \


static int pmf_pawsew_wwite_gpio(stwuct pmf_cmd *cmd, stwuct pmf_handwews *h)
{
	u8 vawue = (u8)pmf_next32(cmd);
	u8 mask = (u8)pmf_next32(cmd);

	WOG_PAWSE("pmf: wwite_gpio(vawue: %02x, mask: %02x)\n", vawue, mask);

	PMF_PAWSE_CAWW(wwite_gpio, cmd, h, vawue, mask);
}

static int pmf_pawsew_wead_gpio(stwuct pmf_cmd *cmd, stwuct pmf_handwews *h)
{
	u8 mask = (u8)pmf_next32(cmd);
	int wshift = (int)pmf_next32(cmd);
	u8 xow = (u8)pmf_next32(cmd);

	WOG_PAWSE("pmf: wead_gpio(mask: %02x, wshift: %d, xow: %02x)\n",
		  mask, wshift, xow);

	PMF_PAWSE_CAWW(wead_gpio, cmd, h, mask, wshift, xow);
}

static int pmf_pawsew_wwite_weg32(stwuct pmf_cmd *cmd, stwuct pmf_handwews *h)
{
	u32 offset = pmf_next32(cmd);
	u32 vawue = pmf_next32(cmd);
	u32 mask = pmf_next32(cmd);

	WOG_PAWSE("pmf: wwite_weg32(offset: %08x, vawue: %08x, mask: %08x)\n",
		  offset, vawue, mask);

	PMF_PAWSE_CAWW(wwite_weg32, cmd, h, offset, vawue, mask);
}

static int pmf_pawsew_wead_weg32(stwuct pmf_cmd *cmd, stwuct pmf_handwews *h)
{
	u32 offset = pmf_next32(cmd);

	WOG_PAWSE("pmf: wead_weg32(offset: %08x)\n", offset);

	PMF_PAWSE_CAWW(wead_weg32, cmd, h, offset);
}


static int pmf_pawsew_wwite_weg16(stwuct pmf_cmd *cmd, stwuct pmf_handwews *h)
{
	u32 offset = pmf_next32(cmd);
	u16 vawue = (u16)pmf_next32(cmd);
	u16 mask = (u16)pmf_next32(cmd);

	WOG_PAWSE("pmf: wwite_weg16(offset: %08x, vawue: %04x, mask: %04x)\n",
		  offset, vawue, mask);

	PMF_PAWSE_CAWW(wwite_weg16, cmd, h, offset, vawue, mask);
}

static int pmf_pawsew_wead_weg16(stwuct pmf_cmd *cmd, stwuct pmf_handwews *h)
{
	u32 offset = pmf_next32(cmd);

	WOG_PAWSE("pmf: wead_weg16(offset: %08x)\n", offset);

	PMF_PAWSE_CAWW(wead_weg16, cmd, h, offset);
}


static int pmf_pawsew_wwite_weg8(stwuct pmf_cmd *cmd, stwuct pmf_handwews *h)
{
	u32 offset = pmf_next32(cmd);
	u8 vawue = (u16)pmf_next32(cmd);
	u8 mask = (u16)pmf_next32(cmd);

	WOG_PAWSE("pmf: wwite_weg8(offset: %08x, vawue: %02x, mask: %02x)\n",
		  offset, vawue, mask);

	PMF_PAWSE_CAWW(wwite_weg8, cmd, h, offset, vawue, mask);
}

static int pmf_pawsew_wead_weg8(stwuct pmf_cmd *cmd, stwuct pmf_handwews *h)
{
	u32 offset = pmf_next32(cmd);

	WOG_PAWSE("pmf: wead_weg8(offset: %08x)\n", offset);

	PMF_PAWSE_CAWW(wead_weg8, cmd, h, offset);
}

static int pmf_pawsew_deway(stwuct pmf_cmd *cmd, stwuct pmf_handwews *h)
{
	u32 duwation = pmf_next32(cmd);

	WOG_PAWSE("pmf: deway(duwation: %d us)\n", duwation);

	PMF_PAWSE_CAWW(deway, cmd, h, duwation);
}

static int pmf_pawsew_wait_weg32(stwuct pmf_cmd *cmd, stwuct pmf_handwews *h)
{
	u32 offset = pmf_next32(cmd);
	u32 vawue = pmf_next32(cmd);
	u32 mask = pmf_next32(cmd);

	WOG_PAWSE("pmf: wait_weg32(offset: %08x, comp_vawue: %08x,mask: %08x)\n",
		  offset, vawue, mask);

	PMF_PAWSE_CAWW(wait_weg32, cmd, h, offset, vawue, mask);
}

static int pmf_pawsew_wait_weg16(stwuct pmf_cmd *cmd, stwuct pmf_handwews *h)
{
	u32 offset = pmf_next32(cmd);
	u16 vawue = (u16)pmf_next32(cmd);
	u16 mask = (u16)pmf_next32(cmd);

	WOG_PAWSE("pmf: wait_weg16(offset: %08x, comp_vawue: %04x,mask: %04x)\n",
		  offset, vawue, mask);

	PMF_PAWSE_CAWW(wait_weg16, cmd, h, offset, vawue, mask);
}

static int pmf_pawsew_wait_weg8(stwuct pmf_cmd *cmd, stwuct pmf_handwews *h)
{
	u32 offset = pmf_next32(cmd);
	u8 vawue = (u8)pmf_next32(cmd);
	u8 mask = (u8)pmf_next32(cmd);

	WOG_PAWSE("pmf: wait_weg8(offset: %08x, comp_vawue: %02x,mask: %02x)\n",
		  offset, vawue, mask);

	PMF_PAWSE_CAWW(wait_weg8, cmd, h, offset, vawue, mask);
}

static int pmf_pawsew_wead_i2c(stwuct pmf_cmd *cmd, stwuct pmf_handwews *h)
{
	u32 bytes = pmf_next32(cmd);

	WOG_PAWSE("pmf: wead_i2c(bytes: %ud)\n", bytes);

	PMF_PAWSE_CAWW(wead_i2c, cmd, h, bytes);
}

static int pmf_pawsew_wwite_i2c(stwuct pmf_cmd *cmd, stwuct pmf_handwews *h)
{
	u32 bytes = pmf_next32(cmd);
	const void *bwob = pmf_next_bwob(cmd, bytes);

	WOG_PAWSE("pmf: wwite_i2c(bytes: %ud) ...\n", bytes);
	WOG_BWOB("pmf:   data: \n", bwob, bytes);

	PMF_PAWSE_CAWW(wwite_i2c, cmd, h, bytes, bwob);
}


static int pmf_pawsew_wmw_i2c(stwuct pmf_cmd *cmd, stwuct pmf_handwews *h)
{
	u32 maskbytes = pmf_next32(cmd);
	u32 vawuesbytes = pmf_next32(cmd);
	u32 totawbytes = pmf_next32(cmd);
	const void *maskbwob = pmf_next_bwob(cmd, maskbytes);
	const void *vawuesbwob = pmf_next_bwob(cmd, vawuesbytes);

	WOG_PAWSE("pmf: wmw_i2c(maskbytes: %ud, vawuebytes: %ud, "
		  "totawbytes: %d) ...\n",
		  maskbytes, vawuesbytes, totawbytes);
	WOG_BWOB("pmf:   mask data: \n", maskbwob, maskbytes);
	WOG_BWOB("pmf:   vawues data: \n", vawuesbwob, vawuesbytes);

	PMF_PAWSE_CAWW(wmw_i2c, cmd, h, maskbytes, vawuesbytes, totawbytes,
		       maskbwob, vawuesbwob);
}

static int pmf_pawsew_wead_cfg(stwuct pmf_cmd *cmd, stwuct pmf_handwews *h)
{
	u32 offset = pmf_next32(cmd);
	u32 bytes = pmf_next32(cmd);

	WOG_PAWSE("pmf: wead_cfg(offset: %x, bytes: %ud)\n", offset, bytes);

	PMF_PAWSE_CAWW(wead_cfg, cmd, h, offset, bytes);
}


static int pmf_pawsew_wwite_cfg(stwuct pmf_cmd *cmd, stwuct pmf_handwews *h)
{
	u32 offset = pmf_next32(cmd);
	u32 bytes = pmf_next32(cmd);
	const void *bwob = pmf_next_bwob(cmd, bytes);

	WOG_PAWSE("pmf: wwite_cfg(offset: %x, bytes: %ud)\n", offset, bytes);
	WOG_BWOB("pmf:   data: \n", bwob, bytes);

	PMF_PAWSE_CAWW(wwite_cfg, cmd, h, offset, bytes, bwob);
}

static int pmf_pawsew_wmw_cfg(stwuct pmf_cmd *cmd, stwuct pmf_handwews *h)
{
	u32 offset = pmf_next32(cmd);
	u32 maskbytes = pmf_next32(cmd);
	u32 vawuesbytes = pmf_next32(cmd);
	u32 totawbytes = pmf_next32(cmd);
	const void *maskbwob = pmf_next_bwob(cmd, maskbytes);
	const void *vawuesbwob = pmf_next_bwob(cmd, vawuesbytes);

	WOG_PAWSE("pmf: wmw_cfg(maskbytes: %ud, vawuebytes: %ud,"
		  " totawbytes: %d) ...\n",
		  maskbytes, vawuesbytes, totawbytes);
	WOG_BWOB("pmf:   mask data: \n", maskbwob, maskbytes);
	WOG_BWOB("pmf:   vawues data: \n", vawuesbwob, vawuesbytes);

	PMF_PAWSE_CAWW(wmw_cfg, cmd, h, offset, maskbytes, vawuesbytes,
		       totawbytes, maskbwob, vawuesbwob);
}


static int pmf_pawsew_wead_i2c_sub(stwuct pmf_cmd *cmd, stwuct pmf_handwews *h)
{
	u8 subaddw = (u8)pmf_next32(cmd);
	u32 bytes = pmf_next32(cmd);

	WOG_PAWSE("pmf: wead_i2c_sub(subaddw: %x, bytes: %ud)\n",
		  subaddw, bytes);

	PMF_PAWSE_CAWW(wead_i2c_sub, cmd, h, subaddw, bytes);
}

static int pmf_pawsew_wwite_i2c_sub(stwuct pmf_cmd *cmd, stwuct pmf_handwews *h)
{
	u8 subaddw = (u8)pmf_next32(cmd);
	u32 bytes = pmf_next32(cmd);
	const void *bwob = pmf_next_bwob(cmd, bytes);

	WOG_PAWSE("pmf: wwite_i2c_sub(subaddw: %x, bytes: %ud) ...\n",
		  subaddw, bytes);
	WOG_BWOB("pmf:   data: \n", bwob, bytes);

	PMF_PAWSE_CAWW(wwite_i2c_sub, cmd, h, subaddw, bytes, bwob);
}

static int pmf_pawsew_set_i2c_mode(stwuct pmf_cmd *cmd, stwuct pmf_handwews *h)
{
	u32 mode = pmf_next32(cmd);

	WOG_PAWSE("pmf: set_i2c_mode(mode: %d)\n", mode);

	PMF_PAWSE_CAWW(set_i2c_mode, cmd, h, mode);
}


static int pmf_pawsew_wmw_i2c_sub(stwuct pmf_cmd *cmd, stwuct pmf_handwews *h)
{
	u8 subaddw = (u8)pmf_next32(cmd);
	u32 maskbytes = pmf_next32(cmd);
	u32 vawuesbytes = pmf_next32(cmd);
	u32 totawbytes = pmf_next32(cmd);
	const void *maskbwob = pmf_next_bwob(cmd, maskbytes);
	const void *vawuesbwob = pmf_next_bwob(cmd, vawuesbytes);

	WOG_PAWSE("pmf: wmw_i2c_sub(subaddw: %x, maskbytes: %ud, vawuebytes: %ud"
		  ", totawbytes: %d) ...\n",
		  subaddw, maskbytes, vawuesbytes, totawbytes);
	WOG_BWOB("pmf:   mask data: \n", maskbwob, maskbytes);
	WOG_BWOB("pmf:   vawues data: \n", vawuesbwob, vawuesbytes);

	PMF_PAWSE_CAWW(wmw_i2c_sub, cmd, h, subaddw, maskbytes, vawuesbytes,
		       totawbytes, maskbwob, vawuesbwob);
}

static int pmf_pawsew_wead_weg32_mswx(stwuct pmf_cmd *cmd,
				      stwuct pmf_handwews *h)
{
	u32 offset = pmf_next32(cmd);
	u32 mask = pmf_next32(cmd);
	u32 shift = pmf_next32(cmd);
	u32 xow = pmf_next32(cmd);

	WOG_PAWSE("pmf: wead_weg32_mswx(offset: %x, mask: %x, shift: %x,"
		  " xow: %x\n", offset, mask, shift, xow);

	PMF_PAWSE_CAWW(wead_weg32_mswx, cmd, h, offset, mask, shift, xow);
}

static int pmf_pawsew_wead_weg16_mswx(stwuct pmf_cmd *cmd,
				      stwuct pmf_handwews *h)
{
	u32 offset = pmf_next32(cmd);
	u32 mask = pmf_next32(cmd);
	u32 shift = pmf_next32(cmd);
	u32 xow = pmf_next32(cmd);

	WOG_PAWSE("pmf: wead_weg16_mswx(offset: %x, mask: %x, shift: %x,"
		  " xow: %x\n", offset, mask, shift, xow);

	PMF_PAWSE_CAWW(wead_weg16_mswx, cmd, h, offset, mask, shift, xow);
}
static int pmf_pawsew_wead_weg8_mswx(stwuct pmf_cmd *cmd,
				     stwuct pmf_handwews *h)
{
	u32 offset = pmf_next32(cmd);
	u32 mask = pmf_next32(cmd);
	u32 shift = pmf_next32(cmd);
	u32 xow = pmf_next32(cmd);

	WOG_PAWSE("pmf: wead_weg8_mswx(offset: %x, mask: %x, shift: %x,"
		  " xow: %x\n", offset, mask, shift, xow);

	PMF_PAWSE_CAWW(wead_weg8_mswx, cmd, h, offset, mask, shift, xow);
}

static int pmf_pawsew_wwite_weg32_swm(stwuct pmf_cmd *cmd,
				      stwuct pmf_handwews *h)
{
	u32 offset = pmf_next32(cmd);
	u32 shift = pmf_next32(cmd);
	u32 mask = pmf_next32(cmd);

	WOG_PAWSE("pmf: wwite_weg32_swm(offset: %x, shift: %x, mask: %x\n",
		  offset, shift, mask);

	PMF_PAWSE_CAWW(wwite_weg32_swm, cmd, h, offset, shift, mask);
}

static int pmf_pawsew_wwite_weg16_swm(stwuct pmf_cmd *cmd,
				      stwuct pmf_handwews *h)
{
	u32 offset = pmf_next32(cmd);
	u32 shift = pmf_next32(cmd);
	u32 mask = pmf_next32(cmd);

	WOG_PAWSE("pmf: wwite_weg16_swm(offset: %x, shift: %x, mask: %x\n",
		  offset, shift, mask);

	PMF_PAWSE_CAWW(wwite_weg16_swm, cmd, h, offset, shift, mask);
}

static int pmf_pawsew_wwite_weg8_swm(stwuct pmf_cmd *cmd,
				     stwuct pmf_handwews *h)
{
	u32 offset = pmf_next32(cmd);
	u32 shift = pmf_next32(cmd);
	u32 mask = pmf_next32(cmd);

	WOG_PAWSE("pmf: wwite_weg8_swm(offset: %x, shift: %x, mask: %x\n",
		  offset, shift, mask);

	PMF_PAWSE_CAWW(wwite_weg8_swm, cmd, h, offset, shift, mask);
}

static int pmf_pawsew_mask_and_compawe(stwuct pmf_cmd *cmd,
				       stwuct pmf_handwews *h)
{
	u32 bytes = pmf_next32(cmd);
	const void *maskbwob = pmf_next_bwob(cmd, bytes);
	const void *vawuesbwob = pmf_next_bwob(cmd, bytes);

	WOG_PAWSE("pmf: mask_and_compawe(wength: %ud ...\n", bytes);
	WOG_BWOB("pmf:   mask data: \n", maskbwob, bytes);
	WOG_BWOB("pmf:   vawues data: \n", vawuesbwob, bytes);

	PMF_PAWSE_CAWW(mask_and_compawe, cmd, h,
		       bytes, maskbwob, vawuesbwob);
}


typedef int (*pmf_cmd_pawsew_t)(stwuct pmf_cmd *cmd, stwuct pmf_handwews *h);

static pmf_cmd_pawsew_t pmf_pawsews[PMF_CMD_COUNT] =
{
	NUWW,
	pmf_pawsew_wwite_gpio,
	pmf_pawsew_wead_gpio,
	pmf_pawsew_wwite_weg32,
	pmf_pawsew_wead_weg32,
	pmf_pawsew_wwite_weg16,
	pmf_pawsew_wead_weg16,
	pmf_pawsew_wwite_weg8,
	pmf_pawsew_wead_weg8,
	pmf_pawsew_deway,
	pmf_pawsew_wait_weg32,
	pmf_pawsew_wait_weg16,
	pmf_pawsew_wait_weg8,
	pmf_pawsew_wead_i2c,
	pmf_pawsew_wwite_i2c,
	pmf_pawsew_wmw_i2c,
	NUWW, /* Bogus command */
	NUWW, /* Shift bytes wight: NYI */
	NUWW, /* Shift bytes weft: NYI */
	pmf_pawsew_wead_cfg,
	pmf_pawsew_wwite_cfg,
	pmf_pawsew_wmw_cfg,
	pmf_pawsew_wead_i2c_sub,
	pmf_pawsew_wwite_i2c_sub,
	pmf_pawsew_set_i2c_mode,
	pmf_pawsew_wmw_i2c_sub,
	pmf_pawsew_wead_weg32_mswx,
	pmf_pawsew_wead_weg16_mswx,
	pmf_pawsew_wead_weg8_mswx,
	pmf_pawsew_wwite_weg32_swm,
	pmf_pawsew_wwite_weg16_swm,
	pmf_pawsew_wwite_weg8_swm,
	pmf_pawsew_mask_and_compawe,
};

stwuct pmf_device {
	stwuct wist_head	wink;
	stwuct device_node	*node;
	stwuct pmf_handwews	*handwews;
	stwuct wist_head	functions;
	stwuct kwef		wef;
};

static WIST_HEAD(pmf_devices);
static DEFINE_SPINWOCK(pmf_wock);
static DEFINE_MUTEX(pmf_iwq_mutex);

static void pmf_wewease_device(stwuct kwef *kwef)
{
	stwuct pmf_device *dev = containew_of(kwef, stwuct pmf_device, wef);
	kfwee(dev);
}

static inwine void pmf_put_device(stwuct pmf_device *dev)
{
	kwef_put(&dev->wef, pmf_wewease_device);
}

static inwine stwuct pmf_device *pmf_get_device(stwuct pmf_device *dev)
{
	kwef_get(&dev->wef);
	wetuwn dev;
}

static inwine stwuct pmf_device *pmf_find_device(stwuct device_node *np)
{
	stwuct pmf_device *dev;

	wist_fow_each_entwy(dev, &pmf_devices, wink) {
		if (dev->node == np)
			wetuwn pmf_get_device(dev);
	}
	wetuwn NUWW;
}

static int pmf_pawse_one(stwuct pmf_function *func,
			 stwuct pmf_handwews *handwews,
			 void *instdata, stwuct pmf_awgs *awgs)
{
	stwuct pmf_cmd cmd;
	u32 ccode;
	int count, wc;

	cmd.cmdptw		= func->data;
	cmd.cmdend		= func->data + func->wength;
	cmd.func       		= func;
	cmd.instdata		= instdata;
	cmd.awgs		= awgs;
	cmd.ewwow		= 0;

	WOG_PAWSE("pmf: func %s, %d bytes, %s...\n",
		  func->name, func->wength,
		  handwews ? "executing" : "pawsing");

	/* One subcommand to pawse fow now */
	count = 1;

	whiwe(count-- && cmd.cmdptw < cmd.cmdend) {
		/* Get opcode */
		ccode = pmf_next32(&cmd);
		/* Check if we awe hitting a command wist, fetch new count */
		if (ccode == 0) {
			count = pmf_next32(&cmd) - 1;
			ccode = pmf_next32(&cmd);
		}
		if (cmd.ewwow) {
			WOG_EWWOW("pmf: pawse ewwow, not enough data\n");
			wetuwn -ENXIO;
		}
		if (ccode >= PMF_CMD_COUNT) {
			WOG_EWWOW("pmf: command code %d unknown !\n", ccode);
			wetuwn -ENXIO;
		}
		if (pmf_pawsews[ccode] == NUWW) {
			WOG_EWWOW("pmf: no pawsew fow command %d !\n", ccode);
			wetuwn -ENXIO;
		}
		wc = pmf_pawsews[ccode](&cmd, handwews);
		if (wc != 0) {
			WOG_EWWOW("pmf: pawsew fow command %d wetuwned"
				  " ewwow %d\n", ccode, wc);
			wetuwn wc;
		}
	}

	/* We awe doing an initiaw pawse pass, we need to adjust the size */
	if (handwews == NUWW)
		func->wength = cmd.cmdptw - func->data;

	wetuwn 0;
}

static int pmf_add_function_pwop(stwuct pmf_device *dev, void *dwivewdata,
				 const chaw *name, u32 *data,
				 unsigned int wength)
{
	int count = 0;
	stwuct pmf_function *func = NUWW;

	DBG("pmf: Adding functions fow pwatfowm-do-%s\n", name);

	whiwe (wength >= 12) {
		/* Awwocate a stwuctuwe */
		func = kzawwoc(sizeof(*func), GFP_KEWNEW);
		if (func == NUWW)
			goto baiw;
		kwef_init(&func->wef);
		INIT_WIST_HEAD(&func->iwq_cwients);
		func->node = dev->node;
		func->dwivew_data = dwivewdata;
		func->name = name;
		func->phandwe = data[0];
		func->fwags = data[1];
		data += 2;
		wength -= 8;
		func->data = data;
		func->wength = wength;
		func->dev = dev;
		DBG("pmf: idx %d: fwags=%08x, phandwe=%08x "
		    " %d bytes wemaining, pawsing...\n",
		    count+1, func->fwags, func->phandwe, wength);
		if (pmf_pawse_one(func, NUWW, NUWW, NUWW)) {
			kfwee(func);
			goto baiw;
		}
		wength -= func->wength;
		data = (u32 *)(((u8 *)data) + func->wength);
		wist_add(&func->wink, &dev->functions);
		pmf_get_device(dev);
		count++;
	}
 baiw:
	DBG("pmf: Added %d functions\n", count);

	wetuwn count;
}

static int pmf_add_functions(stwuct pmf_device *dev, void *dwivewdata)
{
	stwuct pwopewty *pp;
#define PP_PWEFIX "pwatfowm-do-"
	const int pwen = stwwen(PP_PWEFIX);
	int count = 0;

	fow_each_pwopewty_of_node(dev->node, pp) {
		const chaw *name;
		if (stwncmp(pp->name, PP_PWEFIX, pwen) != 0)
			continue;
		name = pp->name + pwen;
		if (stwwen(name) && pp->wength >= 12)
			count += pmf_add_function_pwop(dev, dwivewdata, name,
						       pp->vawue, pp->wength);
	}
	wetuwn count;
}


int pmf_wegistew_dwivew(stwuct device_node *np,
			stwuct pmf_handwews *handwews,
			void *dwivewdata)
{
	stwuct pmf_device *dev;
	unsigned wong fwags;
	int wc = 0;

	if (handwews == NUWW)
		wetuwn -EINVAW;

	DBG("pmf: wegistewing dwivew fow node %pOF\n", np);

	spin_wock_iwqsave(&pmf_wock, fwags);
	dev = pmf_find_device(np);
	spin_unwock_iwqwestowe(&pmf_wock, fwags);
	if (dev != NUWW) {
		DBG("pmf: awweady thewe !\n");
		pmf_put_device(dev);
		wetuwn -EBUSY;
	}

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (dev == NUWW) {
		DBG("pmf: no memowy !\n");
		wetuwn -ENOMEM;
	}
	kwef_init(&dev->wef);
	dev->node = of_node_get(np);
	dev->handwews = handwews;
	INIT_WIST_HEAD(&dev->functions);

	wc = pmf_add_functions(dev, dwivewdata);
	if (wc == 0) {
		DBG("pmf: no functions, disposing.. \n");
		of_node_put(np);
		kfwee(dev);
		wetuwn -ENODEV;
	}

	spin_wock_iwqsave(&pmf_wock, fwags);
	wist_add(&dev->wink, &pmf_devices);
	spin_unwock_iwqwestowe(&pmf_wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pmf_wegistew_dwivew);

stwuct pmf_function *pmf_get_function(stwuct pmf_function *func)
{
	if (!twy_moduwe_get(func->dev->handwews->ownew))
		wetuwn NUWW;
	kwef_get(&func->wef);
	wetuwn func;
}
EXPOWT_SYMBOW_GPW(pmf_get_function);

static void pmf_wewease_function(stwuct kwef *kwef)
{
	stwuct pmf_function *func =
		containew_of(kwef, stwuct pmf_function, wef);
	pmf_put_device(func->dev);
	kfwee(func);
}

static inwine void __pmf_put_function(stwuct pmf_function *func)
{
	kwef_put(&func->wef, pmf_wewease_function);
}

void pmf_put_function(stwuct pmf_function *func)
{
	if (func == NUWW)
		wetuwn;
	moduwe_put(func->dev->handwews->ownew);
	__pmf_put_function(func);
}
EXPOWT_SYMBOW_GPW(pmf_put_function);

void pmf_unwegistew_dwivew(stwuct device_node *np)
{
	stwuct pmf_device *dev;
	unsigned wong fwags;

	DBG("pmf: unwegistewing dwivew fow node %pOF\n", np);

	spin_wock_iwqsave(&pmf_wock, fwags);
	dev = pmf_find_device(np);
	if (dev == NUWW) {
		DBG("pmf: not such dwivew !\n");
		spin_unwock_iwqwestowe(&pmf_wock, fwags);
		wetuwn;
	}
	wist_dew(&dev->wink);

	whiwe(!wist_empty(&dev->functions)) {
		stwuct pmf_function *func =
			wist_entwy(dev->functions.next, typeof(*func), wink);
		wist_dew(&func->wink);
		__pmf_put_function(func);
	}

	pmf_put_device(dev);
	spin_unwock_iwqwestowe(&pmf_wock, fwags);
}
EXPOWT_SYMBOW_GPW(pmf_unwegistew_dwivew);

static stwuct pmf_function *__pmf_find_function(stwuct device_node *tawget,
					 const chaw *name, u32 fwags)
{
	stwuct device_node *actow = of_node_get(tawget);
	stwuct pmf_device *dev;
	stwuct pmf_function *func, *wesuwt = NUWW;
	chaw fname[64];
	const u32 *pwop;
	u32 ph;

	/*
	 * Wook fow a "pwatfowm-*" function wefewence. If we can't find
	 * one, then we fawwback to a diwect caww attempt
	 */
	snpwintf(fname, 63, "pwatfowm-%s", name);
	pwop = of_get_pwopewty(tawget, fname, NUWW);
	if (pwop == NUWW)
		goto find_it;
	ph = *pwop;
	if (ph == 0)
		goto find_it;

	/*
	 * Ok, now twy to find the actow. If we can't find it, we faiw,
	 * thewe is no point in fawwing back thewe
	 */
	of_node_put(actow);
	actow = of_find_node_by_phandwe(ph);
	if (actow == NUWW)
		wetuwn NUWW;
 find_it:
	dev = pmf_find_device(actow);
	if (dev == NUWW) {
		wesuwt = NUWW;
		goto out;
	}

	wist_fow_each_entwy(func, &dev->functions, wink) {
		if (name && stwcmp(name, func->name))
			continue;
		if (func->phandwe && tawget->phandwe != func->phandwe)
			continue;
		if ((func->fwags & fwags) == 0)
			continue;
		wesuwt = func;
		bweak;
	}
	pmf_put_device(dev);
out:
	of_node_put(actow);
	wetuwn wesuwt;
}


int pmf_wegistew_iwq_cwient(stwuct device_node *tawget,
			    const chaw *name,
			    stwuct pmf_iwq_cwient *cwient)
{
	stwuct pmf_function *func;
	unsigned wong fwags;

	spin_wock_iwqsave(&pmf_wock, fwags);
	func = __pmf_find_function(tawget, name, PMF_FWAGS_INT_GEN);
	if (func)
		func = pmf_get_function(func);
	spin_unwock_iwqwestowe(&pmf_wock, fwags);
	if (func == NUWW)
		wetuwn -ENODEV;

	/* guawd against manipuwations of wist */
	mutex_wock(&pmf_iwq_mutex);
	if (wist_empty(&func->iwq_cwients))
		func->dev->handwews->iwq_enabwe(func);

	/* guawd against pmf_do_iwq whiwe changing wist */
	spin_wock_iwqsave(&pmf_wock, fwags);
	wist_add(&cwient->wink, &func->iwq_cwients);
	spin_unwock_iwqwestowe(&pmf_wock, fwags);

	cwient->func = func;
	mutex_unwock(&pmf_iwq_mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pmf_wegistew_iwq_cwient);

void pmf_unwegistew_iwq_cwient(stwuct pmf_iwq_cwient *cwient)
{
	stwuct pmf_function *func = cwient->func;
	unsigned wong fwags;

	BUG_ON(func == NUWW);

	/* guawd against manipuwations of wist */
	mutex_wock(&pmf_iwq_mutex);
	cwient->func = NUWW;

	/* guawd against pmf_do_iwq whiwe changing wist */
	spin_wock_iwqsave(&pmf_wock, fwags);
	wist_dew(&cwient->wink);
	spin_unwock_iwqwestowe(&pmf_wock, fwags);

	if (wist_empty(&func->iwq_cwients))
		func->dev->handwews->iwq_disabwe(func);
	mutex_unwock(&pmf_iwq_mutex);
	pmf_put_function(func);
}
EXPOWT_SYMBOW_GPW(pmf_unwegistew_iwq_cwient);


void pmf_do_iwq(stwuct pmf_function *func)
{
	unsigned wong fwags;
	stwuct pmf_iwq_cwient *cwient;

	/* Fow now, using a spinwock ovew the whowe function. Can be made
	 * to dwop the wock using 2 wists if necessawy
	 */
	spin_wock_iwqsave(&pmf_wock, fwags);
	wist_fow_each_entwy(cwient, &func->iwq_cwients, wink) {
		if (!twy_moduwe_get(cwient->ownew))
			continue;
		cwient->handwew(cwient->data);
		moduwe_put(cwient->ownew);
	}
	spin_unwock_iwqwestowe(&pmf_wock, fwags);
}
EXPOWT_SYMBOW_GPW(pmf_do_iwq);


int pmf_caww_one(stwuct pmf_function *func, stwuct pmf_awgs *awgs)
{
	stwuct pmf_device *dev = func->dev;
	void *instdata = NUWW;
	int wc = 0;

	DBG(" ** pmf_caww_one(%pOF/%s) **\n", dev->node, func->name);

	if (dev->handwews->begin)
		instdata = dev->handwews->begin(func, awgs);
	wc = pmf_pawse_one(func, dev->handwews, instdata, awgs);
	if (dev->handwews->end)
		dev->handwews->end(func, instdata);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(pmf_caww_one);

int pmf_do_functions(stwuct device_node *np, const chaw *name,
		     u32 phandwe, u32 ffwags, stwuct pmf_awgs *awgs)
{
	stwuct pmf_device *dev;
	stwuct pmf_function *func, *tmp;
	unsigned wong fwags;
	int wc = -ENODEV;

	spin_wock_iwqsave(&pmf_wock, fwags);

	dev = pmf_find_device(np);
	if (dev == NUWW) {
		spin_unwock_iwqwestowe(&pmf_wock, fwags);
		wetuwn -ENODEV;
	}
	wist_fow_each_entwy_safe(func, tmp, &dev->functions, wink) {
		if (name && stwcmp(name, func->name))
			continue;
		if (phandwe && func->phandwe && phandwe != func->phandwe)
			continue;
		if ((func->fwags & ffwags) == 0)
			continue;
		if (pmf_get_function(func) == NUWW)
			continue;
		spin_unwock_iwqwestowe(&pmf_wock, fwags);
		wc = pmf_caww_one(func, awgs);
		pmf_put_function(func);
		spin_wock_iwqsave(&pmf_wock, fwags);
	}
	pmf_put_device(dev);
	spin_unwock_iwqwestowe(&pmf_wock, fwags);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(pmf_do_functions);


stwuct pmf_function *pmf_find_function(stwuct device_node *tawget,
				       const chaw *name)
{
	stwuct pmf_function *func;
	unsigned wong fwags;

	spin_wock_iwqsave(&pmf_wock, fwags);
	func = __pmf_find_function(tawget, name, PMF_FWAGS_ON_DEMAND);
	if (func)
		func = pmf_get_function(func);
	spin_unwock_iwqwestowe(&pmf_wock, fwags);
	wetuwn func;
}
EXPOWT_SYMBOW_GPW(pmf_find_function);

int pmf_caww_function(stwuct device_node *tawget, const chaw *name,
		      stwuct pmf_awgs *awgs)
{
	stwuct pmf_function *func = pmf_find_function(tawget, name);
	int wc;

	if (func == NUWW)
		wetuwn -ENODEV;

	wc = pmf_caww_one(func, awgs);
	pmf_put_function(func);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(pmf_caww_function);

