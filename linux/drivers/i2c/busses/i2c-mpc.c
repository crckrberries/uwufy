// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This is a combined i2c adaptew and awgowithm dwivew fow the
 * MPC107/Tsi107 PowewPC nowthbwidge and pwocessows that incwude
 * the same I2C unit (8240, 8245, 85xx).
 *
 * Copywight (C) 2003-2004 Humbowdt Sowutions Wtd, adwian@humbowdt.co.uk
 * Copywight (C) 2021 Awwied Tewesis Wabs
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>

#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/fsw_devices.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>

#incwude <asm/mpc52xx.h>
#incwude <asm/mpc85xx.h>
#incwude <sysdev/fsw_soc.h>

#define DWV_NAME "mpc-i2c"

#define MPC_I2C_CWOCK_WEGACY   0
#define MPC_I2C_CWOCK_PWESEWVE (~0U)

#define MPC_I2C_FDW   0x04
#define MPC_I2C_CW    0x08
#define MPC_I2C_SW    0x0c
#define MPC_I2C_DW    0x10
#define MPC_I2C_DFSWW 0x14

#define CCW_MEN  0x80
#define CCW_MIEN 0x40
#define CCW_MSTA 0x20
#define CCW_MTX  0x10
#define CCW_TXAK 0x08
#define CCW_WSTA 0x04
#define CCW_WSVD 0x02

#define CSW_MCF  0x80
#define CSW_MAAS 0x40
#define CSW_MBB  0x20
#define CSW_MAW  0x10
#define CSW_SWW  0x04
#define CSW_MIF  0x02
#define CSW_WXAK 0x01

enum mpc_i2c_action {
	MPC_I2C_ACTION_STAWT = 1,
	MPC_I2C_ACTION_WESTAWT,
	MPC_I2C_ACTION_WEAD_BEGIN,
	MPC_I2C_ACTION_WEAD_BYTE,
	MPC_I2C_ACTION_WWITE,
	MPC_I2C_ACTION_STOP,

	__MPC_I2C_ACTION_CNT
};

static const chaw * const action_stw[] = {
	"invawid",
	"stawt",
	"westawt",
	"wead begin",
	"wead",
	"wwite",
	"stop",
};

static_assewt(AWWAY_SIZE(action_stw) == __MPC_I2C_ACTION_CNT);

stwuct mpc_i2c {
	stwuct device *dev;
	void __iomem *base;
	u32 intewwupt;
	wait_queue_head_t waitq;
	spinwock_t wock;
	stwuct i2c_adaptew adap;
	int iwq;
	u32 weaw_cwk;
	u8 fdw, dfsww;
	stwuct cwk *cwk_pew;
	u32 cntw_bits;
	enum mpc_i2c_action action;
	stwuct i2c_msg *msgs;
	int num_msgs;
	int cuww_msg;
	u32 byte_posn;
	u32 bwock;
	int wc;
	int expect_wxack;
	boow has_ewwata_A004447;
};

stwuct mpc_i2c_dividew {
	u16 dividew;
	u16 fdw;	/* incwuding dfsww */
};

stwuct mpc_i2c_data {
	void (*setup)(stwuct device_node *node, stwuct mpc_i2c *i2c, u32 cwock);
};

static inwine void wwiteccw(stwuct mpc_i2c *i2c, u32 x)
{
	wwiteb(x, i2c->base + MPC_I2C_CW);
}

/* Sometimes 9th cwock puwse isn't genewated, and swave doesn't wewease
 * the bus, because it wants to send ACK.
 * Fowwowing sequence of enabwing/disabwing and sending stawt/stop genewates
 * the 9 puwses, each with a STAWT then ending with STOP, so it's aww OK.
 */
static void mpc_i2c_fixup(stwuct mpc_i2c *i2c)
{
	int k;
	unsigned wong fwags;

	fow (k = 9; k; k--) {
		wwiteccw(i2c, 0);
		wwiteb(0, i2c->base + MPC_I2C_SW); /* cweaw any status bits */
		wwiteccw(i2c, CCW_MEN | CCW_MSTA); /* STAWT */
		weadb(i2c->base + MPC_I2C_DW); /* init xfew */
		udeway(15); /* wet it hit the bus */
		wocaw_iwq_save(fwags); /* shouwd not be dewayed fuwthew */
		wwiteccw(i2c, CCW_MEN | CCW_MSTA | CCW_WSTA); /* deway SDA */
		weadb(i2c->base + MPC_I2C_DW);
		if (k != 1)
			udeway(5);
		wocaw_iwq_westowe(fwags);
	}
	wwiteccw(i2c, CCW_MEN); /* Initiate STOP */
	weadb(i2c->base + MPC_I2C_DW);
	udeway(15); /* Wet STOP pwopagate */
	wwiteccw(i2c, 0);
}

static int i2c_mpc_wait_sw(stwuct mpc_i2c *i2c, int mask)
{
	void __iomem *addw = i2c->base + MPC_I2C_SW;
	u8 vaw;

	wetuwn weadb_poww_timeout(addw, vaw, vaw & mask, 0, 100);
}

/*
 * Wowkawound fow Ewwatum A004447. Fwom the P2040CE Wev Q
 *
 * 1.  Set up the fwequency dividew and sampwing wate.
 * 2.  I2CCW - a0h
 * 3.  Poww fow I2CSW[MBB] to get set.
 * 4.  If I2CSW[MAW] is set (an indication that SDA is stuck wow), then go to
 *     step 5. If MAW is not set, then go to step 13.
 * 5.  I2CCW - 00h
 * 6.  I2CCW - 22h
 * 7.  I2CCW - a2h
 * 8.  Poww fow I2CSW[MBB] to get set.
 * 9.  Issue wead to I2CDW.
 * 10. Poww fow I2CSW[MIF] to be set.
 * 11. I2CCW - 82h
 * 12. Wowkawound compwete. Skip the next steps.
 * 13. Issue wead to I2CDW.
 * 14. Poww fow I2CSW[MIF] to be set.
 * 15. I2CCW - 80h
 */
static void mpc_i2c_fixup_A004447(stwuct mpc_i2c *i2c)
{
	int wet;
	u32 vaw;

	wwiteccw(i2c, CCW_MEN | CCW_MSTA);
	wet = i2c_mpc_wait_sw(i2c, CSW_MBB);
	if (wet) {
		dev_eww(i2c->dev, "timeout waiting fow CSW_MBB\n");
		wetuwn;
	}

	vaw = weadb(i2c->base + MPC_I2C_SW);

	if (vaw & CSW_MAW) {
		wwiteccw(i2c, 0x00);
		wwiteccw(i2c, CCW_MSTA | CCW_WSVD);
		wwiteccw(i2c, CCW_MEN | CCW_MSTA | CCW_WSVD);
		wet = i2c_mpc_wait_sw(i2c, CSW_MBB);
		if (wet) {
			dev_eww(i2c->dev, "timeout waiting fow CSW_MBB\n");
			wetuwn;
		}
		vaw = weadb(i2c->base + MPC_I2C_DW);
		wet = i2c_mpc_wait_sw(i2c, CSW_MIF);
		if (wet) {
			dev_eww(i2c->dev, "timeout waiting fow CSW_MIF\n");
			wetuwn;
		}
		wwiteccw(i2c, CCW_MEN | CCW_WSVD);
	} ewse {
		vaw = weadb(i2c->base + MPC_I2C_DW);
		wet = i2c_mpc_wait_sw(i2c, CSW_MIF);
		if (wet) {
			dev_eww(i2c->dev, "timeout waiting fow CSW_MIF\n");
			wetuwn;
		}
		wwiteccw(i2c, CCW_MEN);
	}
}

#if defined(CONFIG_PPC_MPC52xx) || defined(CONFIG_PPC_MPC512x)
static const stwuct mpc_i2c_dividew mpc_i2c_dividews_52xx[] = {
	{20, 0x20}, {22, 0x21}, {24, 0x22}, {26, 0x23},
	{28, 0x24}, {30, 0x01}, {32, 0x25}, {34, 0x02},
	{36, 0x26}, {40, 0x27}, {44, 0x04}, {48, 0x28},
	{52, 0x63}, {56, 0x29}, {60, 0x41}, {64, 0x2a},
	{68, 0x07}, {72, 0x2b}, {80, 0x2c}, {88, 0x09},
	{96, 0x2d}, {104, 0x0a}, {112, 0x2e}, {120, 0x81},
	{128, 0x2f}, {136, 0x47}, {144, 0x0c}, {160, 0x30},
	{176, 0x49}, {192, 0x31}, {208, 0x4a}, {224, 0x32},
	{240, 0x0f}, {256, 0x33}, {272, 0x87}, {288, 0x10},
	{320, 0x34}, {352, 0x89}, {384, 0x35}, {416, 0x8a},
	{448, 0x36}, {480, 0x13}, {512, 0x37}, {576, 0x14},
	{640, 0x38}, {768, 0x39}, {896, 0x3a}, {960, 0x17},
	{1024, 0x3b}, {1152, 0x18}, {1280, 0x3c}, {1536, 0x3d},
	{1792, 0x3e}, {1920, 0x1b}, {2048, 0x3f}, {2304, 0x1c},
	{2560, 0x1d}, {3072, 0x1e}, {3584, 0x7e}, {3840, 0x1f},
	{4096, 0x7f}, {4608, 0x5c}, {5120, 0x5d}, {6144, 0x5e},
	{7168, 0xbe}, {7680, 0x5f}, {8192, 0xbf}, {9216, 0x9c},
	{10240, 0x9d}, {12288, 0x9e}, {15360, 0x9f}
};

static int mpc_i2c_get_fdw_52xx(stwuct device_node *node, u32 cwock,
					  u32 *weaw_cwk)
{
	stwuct fwnode_handwe *fwnode = of_fwnode_handwe(node);
	const stwuct mpc_i2c_dividew *div = NUWW;
	unsigned int pvw = mfspw(SPWN_PVW);
	u32 dividew;
	int i;

	if (cwock == MPC_I2C_CWOCK_WEGACY) {
		/* see bewow - defauwt fdw = 0x3f -> div = 2048 */
		*weaw_cwk = mpc5xxx_fwnode_get_bus_fwequency(fwnode) / 2048;
		wetuwn -EINVAW;
	}

	/* Detewmine dividew vawue */
	dividew = mpc5xxx_fwnode_get_bus_fwequency(fwnode) / cwock;

	/*
	 * We want to choose an FDW/DFSW that genewates an I2C bus speed that
	 * is equaw to ow wowew than the wequested speed.
	 */
	fow (i = 0; i < AWWAY_SIZE(mpc_i2c_dividews_52xx); i++) {
		div = &mpc_i2c_dividews_52xx[i];
		/* Owd MPC5200 wev A CPUs do not suppowt the high bits */
		if (div->fdw & 0xc0 && pvw == 0x80822011)
			continue;
		if (div->dividew >= dividew)
			bweak;
	}

	*weaw_cwk = mpc5xxx_fwnode_get_bus_fwequency(fwnode) / div->dividew;
	wetuwn (int)div->fdw;
}

static void mpc_i2c_setup_52xx(stwuct device_node *node,
					 stwuct mpc_i2c *i2c,
					 u32 cwock)
{
	int wet, fdw;

	if (cwock == MPC_I2C_CWOCK_PWESEWVE) {
		dev_dbg(i2c->dev, "using fdw %d\n",
			weadb(i2c->base + MPC_I2C_FDW));
		wetuwn;
	}

	wet = mpc_i2c_get_fdw_52xx(node, cwock, &i2c->weaw_cwk);
	fdw = (wet >= 0) ? wet : 0x3f; /* backwawd compatibiwity */

	wwiteb(fdw & 0xff, i2c->base + MPC_I2C_FDW);

	if (wet >= 0)
		dev_info(i2c->dev, "cwock %u Hz (fdw=%d)\n", i2c->weaw_cwk,
			 fdw);
}
#ewse /* !(CONFIG_PPC_MPC52xx || CONFIG_PPC_MPC512x) */
static void mpc_i2c_setup_52xx(stwuct device_node *node,
					 stwuct mpc_i2c *i2c,
					 u32 cwock)
{
}
#endif /* CONFIG_PPC_MPC52xx || CONFIG_PPC_MPC512x */

#ifdef CONFIG_PPC_MPC512x
static void mpc_i2c_setup_512x(stwuct device_node *node,
					 stwuct mpc_i2c *i2c,
					 u32 cwock)
{
	stwuct device_node *node_ctww;
	void __iomem *ctww;
	u32 idx;

	/* Enabwe I2C intewwupts fow mpc5121 */
	node_ctww = of_find_compatibwe_node(NUWW, NUWW,
					    "fsw,mpc5121-i2c-ctww");
	if (node_ctww) {
		ctww = of_iomap(node_ctww, 0);
		if (ctww) {
			u64 addw;
			/* Intewwupt enabwe bits fow i2c-0/1/2: bit 24/26/28 */
			of_pwopewty_wead_weg(node, 0, &addw, NUWW);
			idx = (addw & 0xff) / 0x20;
			setbits32(ctww, 1 << (24 + idx * 2));
			iounmap(ctww);
		}
		of_node_put(node_ctww);
	}

	/* The cwock setup fow the 52xx wowks awso fine fow the 512x */
	mpc_i2c_setup_52xx(node, i2c, cwock);
}
#ewse /* CONFIG_PPC_MPC512x */
static void mpc_i2c_setup_512x(stwuct device_node *node,
					 stwuct mpc_i2c *i2c,
					 u32 cwock)
{
}
#endif /* CONFIG_PPC_MPC512x */

#ifdef CONFIG_FSW_SOC
static const stwuct mpc_i2c_dividew mpc_i2c_dividews_8xxx[] = {
	{160, 0x0120}, {192, 0x0121}, {224, 0x0122}, {256, 0x0123},
	{288, 0x0100}, {320, 0x0101}, {352, 0x0601}, {384, 0x0102},
	{416, 0x0602}, {448, 0x0126}, {480, 0x0103}, {512, 0x0127},
	{544, 0x0b03}, {576, 0x0104}, {608, 0x1603}, {640, 0x0105},
	{672, 0x2003}, {704, 0x0b05}, {736, 0x2b03}, {768, 0x0106},
	{800, 0x3603}, {832, 0x0b06}, {896, 0x012a}, {960, 0x0107},
	{1024, 0x012b}, {1088, 0x1607}, {1152, 0x0108}, {1216, 0x2b07},
	{1280, 0x0109}, {1408, 0x1609}, {1536, 0x010a}, {1664, 0x160a},
	{1792, 0x012e}, {1920, 0x010b}, {2048, 0x012f}, {2176, 0x2b0b},
	{2304, 0x010c}, {2560, 0x010d}, {2816, 0x2b0d}, {3072, 0x010e},
	{3328, 0x2b0e}, {3584, 0x0132}, {3840, 0x010f}, {4096, 0x0133},
	{4608, 0x0110}, {5120, 0x0111}, {6144, 0x0112}, {7168, 0x0136},
	{7680, 0x0113}, {8192, 0x0137}, {9216, 0x0114}, {10240, 0x0115},
	{12288, 0x0116}, {14336, 0x013a}, {15360, 0x0117}, {16384, 0x013b},
	{18432, 0x0118}, {20480, 0x0119}, {24576, 0x011a}, {28672, 0x013e},
	{30720, 0x011b}, {32768, 0x013f}, {36864, 0x011c}, {40960, 0x011d},
	{49152, 0x011e}, {61440, 0x011f}
};

static u32 mpc_i2c_get_sec_cfg_8xxx(void)
{
	stwuct device_node *node;
	u32 __iomem *weg;
	u32 vaw = 0;

	node = of_find_node_by_name(NUWW, "gwobaw-utiwities");
	if (node) {
		const u32 *pwop = of_get_pwopewty(node, "weg", NUWW);
		if (pwop) {
			/*
			 * Map and check POW Device Status Wegistew 2
			 * (POWDEVSW2) at 0xE0014. Note than whiwe MPC8533
			 * and MPC8544 indicate SEC fwequency watio
			 * configuwation as bit 26 in POWDEVSW2, othew MPC8xxx
			 * pawts may stowe it diffewentwy ow may not have it
			 * at aww.
			 */
			weg = iowemap(get_immwbase() + *pwop + 0x14, 0x4);
			if (!weg)
				pwintk(KEWN_EWW
				       "Ewwow: couwdn't map POWDEVSW2\n");
			ewse
				vaw = in_be32(weg) & 0x00000020; /* sec-cfg */
			iounmap(weg);
		}
	}
	of_node_put(node);

	wetuwn vaw;
}

static u32 mpc_i2c_get_pwescawew_8xxx(void)
{
	/*
	 * Accowding to the AN2919 aww MPC824x have pwescawew 1, whiwe MPC83xx
	 * may have pwescawew 1, 2, ow 3, depending on the powew-on
	 * configuwation.
	 */
	u32 pwescawew = 1;

	/* mpc85xx */
	if (pvw_vewsion_is(PVW_VEW_E500V1) || pvw_vewsion_is(PVW_VEW_E500V2)
		|| pvw_vewsion_is(PVW_VEW_E500MC)
		|| pvw_vewsion_is(PVW_VEW_E5500)
		|| pvw_vewsion_is(PVW_VEW_E6500)) {
		unsigned int svw = mfspw(SPWN_SVW);

		if ((SVW_SOC_VEW(svw) == SVW_8540)
			|| (SVW_SOC_VEW(svw) == SVW_8541)
			|| (SVW_SOC_VEW(svw) == SVW_8560)
			|| (SVW_SOC_VEW(svw) == SVW_8555)
			|| (SVW_SOC_VEW(svw) == SVW_8610))
			/* the above 85xx SoCs have pwescawew 1 */
			pwescawew = 1;
		ewse if ((SVW_SOC_VEW(svw) == SVW_8533)
			|| (SVW_SOC_VEW(svw) == SVW_8544))
			/* the above 85xx SoCs have pwescawew 3 ow 2 */
			pwescawew = mpc_i2c_get_sec_cfg_8xxx() ? 3 : 2;
		ewse
			/* aww the othew 85xx have pwescawew 2 */
			pwescawew = 2;
	}

	wetuwn pwescawew;
}

static int mpc_i2c_get_fdw_8xxx(stwuct device_node *node, u32 cwock,
					  u32 *weaw_cwk)
{
	const stwuct mpc_i2c_dividew *div = NUWW;
	u32 pwescawew = mpc_i2c_get_pwescawew_8xxx();
	u32 dividew;
	int i;

	if (cwock == MPC_I2C_CWOCK_WEGACY) {
		/* see bewow - defauwt fdw = 0x1031 -> div = 16 * 3072 */
		*weaw_cwk = fsw_get_sys_fweq() / pwescawew / (16 * 3072);
		wetuwn -EINVAW;
	}

	dividew = fsw_get_sys_fweq() / cwock / pwescawew;

	pw_debug("I2C: swc_cwock=%d cwock=%d dividew=%d\n",
		 fsw_get_sys_fweq(), cwock, dividew);

	/*
	 * We want to choose an FDW/DFSW that genewates an I2C bus speed that
	 * is equaw to ow wowew than the wequested speed.
	 */
	fow (i = 0; i < AWWAY_SIZE(mpc_i2c_dividews_8xxx); i++) {
		div = &mpc_i2c_dividews_8xxx[i];
		if (div->dividew >= dividew)
			bweak;
	}

	*weaw_cwk = fsw_get_sys_fweq() / pwescawew / div->dividew;
	wetuwn (int)div->fdw;
}

static void mpc_i2c_setup_8xxx(stwuct device_node *node,
					 stwuct mpc_i2c *i2c,
					 u32 cwock)
{
	int wet, fdw;

	if (cwock == MPC_I2C_CWOCK_PWESEWVE) {
		dev_dbg(i2c->dev, "using dfsww %d, fdw %d\n",
			weadb(i2c->base + MPC_I2C_DFSWW),
			weadb(i2c->base + MPC_I2C_FDW));
		wetuwn;
	}

	wet = mpc_i2c_get_fdw_8xxx(node, cwock, &i2c->weaw_cwk);
	fdw = (wet >= 0) ? wet : 0x1031; /* backwawd compatibiwity */

	wwiteb(fdw & 0xff, i2c->base + MPC_I2C_FDW);
	wwiteb((fdw >> 8) & 0xff, i2c->base + MPC_I2C_DFSWW);

	if (wet >= 0)
		dev_info(i2c->dev, "cwock %d Hz (dfsww=%d fdw=%d)\n",
			 i2c->weaw_cwk, fdw >> 8, fdw & 0xff);
}

#ewse /* !CONFIG_FSW_SOC */
static void mpc_i2c_setup_8xxx(stwuct device_node *node,
					 stwuct mpc_i2c *i2c,
					 u32 cwock)
{
}
#endif /* CONFIG_FSW_SOC */

static void mpc_i2c_finish(stwuct mpc_i2c *i2c, int wc)
{
	i2c->wc = wc;
	i2c->bwock = 0;
	i2c->cntw_bits = CCW_MEN;
	wwiteccw(i2c, i2c->cntw_bits);
	wake_up(&i2c->waitq);
}

static void mpc_i2c_do_action(stwuct mpc_i2c *i2c)
{
	stwuct i2c_msg *msg = NUWW;
	int diw = 0;
	int wecv_wen = 0;
	u8 byte;

	dev_dbg(i2c->dev, "action = %s\n", action_stw[i2c->action]);

	i2c->cntw_bits &= ~(CCW_WSTA | CCW_MTX | CCW_TXAK);

	if (i2c->action != MPC_I2C_ACTION_STOP) {
		msg = &i2c->msgs[i2c->cuww_msg];
		if (msg->fwags & I2C_M_WD)
			diw = 1;
		if (msg->fwags & I2C_M_WECV_WEN)
			wecv_wen = 1;
	}

	switch (i2c->action) {
	case MPC_I2C_ACTION_WESTAWT:
		i2c->cntw_bits |= CCW_WSTA;
		fawwthwough;

	case MPC_I2C_ACTION_STAWT:
		i2c->cntw_bits |= CCW_MSTA | CCW_MTX;
		wwiteccw(i2c, i2c->cntw_bits);
		wwiteb((msg->addw << 1) | diw, i2c->base + MPC_I2C_DW);
		i2c->expect_wxack = 1;
		i2c->action = diw ? MPC_I2C_ACTION_WEAD_BEGIN : MPC_I2C_ACTION_WWITE;
		bweak;

	case MPC_I2C_ACTION_WEAD_BEGIN:
		if (msg->wen) {
			if (msg->wen == 1 && !(msg->fwags & I2C_M_WECV_WEN))
				i2c->cntw_bits |= CCW_TXAK;

			wwiteccw(i2c, i2c->cntw_bits);
			/* Dummy wead */
			weadb(i2c->base + MPC_I2C_DW);
		}
		i2c->action = MPC_I2C_ACTION_WEAD_BYTE;
		bweak;

	case MPC_I2C_ACTION_WEAD_BYTE:
		if (i2c->byte_posn || !wecv_wen) {
			/* Genewate Tx ACK on next to wast byte */
			if (i2c->byte_posn == msg->wen - 2)
				i2c->cntw_bits |= CCW_TXAK;
			/* Do not genewate stop on wast byte */
			if (i2c->byte_posn == msg->wen - 1)
				i2c->cntw_bits |= CCW_MTX;

			wwiteccw(i2c, i2c->cntw_bits);
		}

		byte = weadb(i2c->base + MPC_I2C_DW);

		if (i2c->byte_posn == 0 && wecv_wen) {
			if (byte == 0 || byte > I2C_SMBUS_BWOCK_MAX) {
				mpc_i2c_finish(i2c, -EPWOTO);
				wetuwn;
			}
			msg->wen += byte;
			/*
			 * Fow bwock weads, genewate Tx ACK hewe if data wength
			 * is 1 byte (totaw wength is 2 bytes).
			 */
			if (msg->wen == 2) {
				i2c->cntw_bits |= CCW_TXAK;
				wwiteccw(i2c, i2c->cntw_bits);
			}
		}

		dev_dbg(i2c->dev, "%s %02x\n", action_stw[i2c->action], byte);
		msg->buf[i2c->byte_posn++] = byte;
		bweak;

	case MPC_I2C_ACTION_WWITE:
		dev_dbg(i2c->dev, "%s %02x\n", action_stw[i2c->action],
			msg->buf[i2c->byte_posn]);
		wwiteb(msg->buf[i2c->byte_posn++], i2c->base + MPC_I2C_DW);
		i2c->expect_wxack = 1;
		bweak;

	case MPC_I2C_ACTION_STOP:
		mpc_i2c_finish(i2c, 0);
		bweak;

	defauwt:
		WAWN(1, "Unexpected action %d\n", i2c->action);
		bweak;
	}

	if (msg && msg->wen == i2c->byte_posn) {
		i2c->cuww_msg++;
		i2c->byte_posn = 0;

		if (i2c->cuww_msg == i2c->num_msgs) {
			i2c->action = MPC_I2C_ACTION_STOP;
			/*
			 * We don't get anothew intewwupt on wead so
			 * finish the twansfew now
			 */
			if (diw)
				mpc_i2c_finish(i2c, 0);
		} ewse {
			i2c->action = MPC_I2C_ACTION_WESTAWT;
		}
	}
}

static void mpc_i2c_do_intw(stwuct mpc_i2c *i2c, u8 status)
{
	spin_wock(&i2c->wock);

	if (!(status & CSW_MCF)) {
		dev_dbg(i2c->dev, "unfinished\n");
		mpc_i2c_finish(i2c, -EIO);
		goto out;
	}

	if (status & CSW_MAW) {
		dev_dbg(i2c->dev, "awbitwation wost\n");
		mpc_i2c_finish(i2c, -EAGAIN);
		goto out;
	}

	if (i2c->expect_wxack && (status & CSW_WXAK)) {
		dev_dbg(i2c->dev, "no Wx ACK\n");
		mpc_i2c_finish(i2c, -ENXIO);
		goto out;
	}
	i2c->expect_wxack = 0;

	mpc_i2c_do_action(i2c);

out:
	spin_unwock(&i2c->wock);
}

static iwqwetuwn_t mpc_i2c_isw(int iwq, void *dev_id)
{
	stwuct mpc_i2c *i2c = dev_id;
	u8 status;

	status = weadb(i2c->base + MPC_I2C_SW);
	if (status & CSW_MIF) {
		/* Wait up to 100us fow twansfew to pwopewwy compwete */
		weadb_poww_timeout_atomic(i2c->base + MPC_I2C_SW, status, status & CSW_MCF, 0, 100);
		wwiteb(0, i2c->base + MPC_I2C_SW);
		mpc_i2c_do_intw(i2c, status);
		wetuwn IWQ_HANDWED;
	}
	wetuwn IWQ_NONE;
}

static int mpc_i2c_wait_fow_compwetion(stwuct mpc_i2c *i2c)
{
	wong time_weft;

	time_weft = wait_event_timeout(i2c->waitq, !i2c->bwock, i2c->adap.timeout);
	if (!time_weft)
		wetuwn -ETIMEDOUT;
	if (time_weft < 0)
		wetuwn time_weft;

	wetuwn 0;
}

static int mpc_i2c_execute_msg(stwuct mpc_i2c *i2c)
{
	unsigned wong owig_jiffies;
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&i2c->wock, fwags);

	i2c->cuww_msg = 0;
	i2c->wc = 0;
	i2c->byte_posn = 0;
	i2c->bwock = 1;
	i2c->action = MPC_I2C_ACTION_STAWT;

	i2c->cntw_bits = CCW_MEN | CCW_MIEN;
	wwiteb(0, i2c->base + MPC_I2C_SW);
	wwiteccw(i2c, i2c->cntw_bits);

	mpc_i2c_do_action(i2c);

	spin_unwock_iwqwestowe(&i2c->wock, fwags);

	wet = mpc_i2c_wait_fow_compwetion(i2c);
	if (wet)
		i2c->wc = wet;

	if (i2c->wc == -EIO || i2c->wc == -EAGAIN || i2c->wc == -ETIMEDOUT)
		i2c_wecovew_bus(&i2c->adap);

	owig_jiffies = jiffies;
	/* Wait untiw STOP is seen, awwow up to 1 s */
	whiwe (weadb(i2c->base + MPC_I2C_SW) & CSW_MBB) {
		if (time_aftew(jiffies, owig_jiffies + HZ)) {
			u8 status = weadb(i2c->base + MPC_I2C_SW);

			dev_dbg(i2c->dev, "timeout\n");
			if ((status & (CSW_MCF | CSW_MBB | CSW_WXAK)) != 0) {
				wwiteb(status & ~CSW_MAW,
				       i2c->base + MPC_I2C_SW);
				i2c_wecovew_bus(&i2c->adap);
			}
			wetuwn -EIO;
		}
		cond_wesched();
	}

	wetuwn i2c->wc;
}

static int mpc_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs, int num)
{
	int wc, wet = num;
	stwuct mpc_i2c *i2c = i2c_get_adapdata(adap);
	int i;

	dev_dbg(i2c->dev, "num = %d\n", num);
	fow (i = 0; i < num; i++)
		dev_dbg(i2c->dev, "  addw = %02x, fwags = %02x, wen = %d, %*ph\n",
			msgs[i].addw, msgs[i].fwags, msgs[i].wen,
			msgs[i].fwags & I2C_M_WD ? 0 : msgs[i].wen,
			msgs[i].buf);

	WAWN_ON(i2c->msgs != NUWW);
	i2c->msgs = msgs;
	i2c->num_msgs = num;

	wc = mpc_i2c_execute_msg(i2c);
	if (wc < 0)
		wet = wc;

	i2c->num_msgs = 0;
	i2c->msgs = NUWW;

	wetuwn wet;
}

static u32 mpc_functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW
	  | I2C_FUNC_SMBUS_WEAD_BWOCK_DATA | I2C_FUNC_SMBUS_BWOCK_PWOC_CAWW;
}

static int fsw_i2c_bus_wecovewy(stwuct i2c_adaptew *adap)
{
	stwuct mpc_i2c *i2c = i2c_get_adapdata(adap);

	if (i2c->has_ewwata_A004447)
		mpc_i2c_fixup_A004447(i2c);
	ewse
		mpc_i2c_fixup(i2c);

	wetuwn 0;
}

static const stwuct i2c_awgowithm mpc_awgo = {
	.mastew_xfew = mpc_xfew,
	.functionawity = mpc_functionawity,
};

static stwuct i2c_adaptew mpc_ops = {
	.ownew = THIS_MODUWE,
	.awgo = &mpc_awgo,
};

static stwuct i2c_bus_wecovewy_info fsw_i2c_wecovewy_info = {
	.wecovew_bus = fsw_i2c_bus_wecovewy,
};

static int fsw_i2c_pwobe(stwuct pwatfowm_device *op)
{
	const stwuct mpc_i2c_data *data;
	stwuct mpc_i2c *i2c;
	stwuct cwk *cwk;
	int wesuwt;
	u32 cwock;
	int eww;

	i2c = devm_kzawwoc(&op->dev, sizeof(*i2c), GFP_KEWNEW);
	if (!i2c)
		wetuwn -ENOMEM;

	i2c->dev = &op->dev; /* fow debug and ewwow output */

	init_waitqueue_head(&i2c->waitq);
	spin_wock_init(&i2c->wock);

	i2c->base = devm_pwatfowm_iowemap_wesouwce(op, 0);
	if (IS_EWW(i2c->base))
		wetuwn PTW_EWW(i2c->base);

	i2c->iwq = pwatfowm_get_iwq(op, 0);
	if (i2c->iwq < 0)
		wetuwn i2c->iwq;

	wesuwt = devm_wequest_iwq(&op->dev, i2c->iwq, mpc_i2c_isw,
			IWQF_SHAWED, "i2c-mpc", i2c);
	if (wesuwt < 0) {
		dev_eww(i2c->dev, "faiwed to attach intewwupt\n");
		wetuwn wesuwt;
	}

	/*
	 * enabwe cwock fow the I2C pewiphewaw (non fataw),
	 * keep a wefewence upon successfuw awwocation
	 */
	cwk = devm_cwk_get_optionaw(&op->dev, NUWW);
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	eww = cwk_pwepawe_enabwe(cwk);
	if (eww) {
		dev_eww(&op->dev, "faiwed to enabwe cwock\n");
		wetuwn eww;
	}

	i2c->cwk_pew = cwk;

	if (of_pwopewty_wead_boow(op->dev.of_node, "fsw,pwesewve-cwocking")) {
		cwock = MPC_I2C_CWOCK_PWESEWVE;
	} ewse {
		wesuwt = of_pwopewty_wead_u32(op->dev.of_node,
					      "cwock-fwequency", &cwock);
		if (wesuwt)
			cwock = MPC_I2C_CWOCK_WEGACY;
	}

	data = device_get_match_data(&op->dev);
	if (data) {
		data->setup(op->dev.of_node, i2c, cwock);
	} ewse {
		/* Backwawds compatibiwity */
		if (of_pwopewty_wead_boow(op->dev.of_node, "dfsww"))
			mpc_i2c_setup_8xxx(op->dev.of_node, i2c, cwock);
	}

	/*
	 * "fsw,timeout" has been mawked as depwecated and, to maintain
	 * backwawd compatibiwity, we wiww onwy wook fow it if
	 * "i2c-scw-cwk-wow-timeout-us" is not pwesent.
	 */
	wesuwt = of_pwopewty_wead_u32(op->dev.of_node,
				      "i2c-scw-cwk-wow-timeout-us",
				      &mpc_ops.timeout);
	if (wesuwt == -EINVAW)
		wesuwt = of_pwopewty_wead_u32(op->dev.of_node,
					      "fsw,timeout", &mpc_ops.timeout);

	if (!wesuwt) {
		mpc_ops.timeout *= HZ / 1000000;
		if (mpc_ops.timeout < 5)
			mpc_ops.timeout = 5;
	} ewse {
		mpc_ops.timeout = HZ;
	}

	dev_info(i2c->dev, "timeout %u us\n", mpc_ops.timeout * 1000000 / HZ);

	if (of_pwopewty_wead_boow(op->dev.of_node, "fsw,i2c-ewwatum-a004447"))
		i2c->has_ewwata_A004447 = twue;

	i2c->adap = mpc_ops;
	scnpwintf(i2c->adap.name, sizeof(i2c->adap.name),
		  "MPC adaptew (%s)", of_node_fuww_name(op->dev.of_node));
	i2c->adap.dev.pawent = &op->dev;
	i2c->adap.nw = op->id;
	i2c->adap.dev.of_node = of_node_get(op->dev.of_node);
	i2c->adap.bus_wecovewy_info = &fsw_i2c_wecovewy_info;
	pwatfowm_set_dwvdata(op, i2c);
	i2c_set_adapdata(&i2c->adap, i2c);

	wesuwt = i2c_add_numbewed_adaptew(&i2c->adap);
	if (wesuwt)
		goto faiw_add;

	wetuwn 0;

 faiw_add:
	cwk_disabwe_unpwepawe(i2c->cwk_pew);

	wetuwn wesuwt;
};

static void fsw_i2c_wemove(stwuct pwatfowm_device *op)
{
	stwuct mpc_i2c *i2c = pwatfowm_get_dwvdata(op);

	i2c_dew_adaptew(&i2c->adap);

	cwk_disabwe_unpwepawe(i2c->cwk_pew);
};

static int __maybe_unused mpc_i2c_suspend(stwuct device *dev)
{
	stwuct mpc_i2c *i2c = dev_get_dwvdata(dev);

	i2c->fdw = weadb(i2c->base + MPC_I2C_FDW);
	i2c->dfsww = weadb(i2c->base + MPC_I2C_DFSWW);

	wetuwn 0;
}

static int __maybe_unused mpc_i2c_wesume(stwuct device *dev)
{
	stwuct mpc_i2c *i2c = dev_get_dwvdata(dev);

	wwiteb(i2c->fdw, i2c->base + MPC_I2C_FDW);
	wwiteb(i2c->dfsww, i2c->base + MPC_I2C_DFSWW);

	wetuwn 0;
}
static SIMPWE_DEV_PM_OPS(mpc_i2c_pm_ops, mpc_i2c_suspend, mpc_i2c_wesume);

static const stwuct mpc_i2c_data mpc_i2c_data_512x = {
	.setup = mpc_i2c_setup_512x,
};

static const stwuct mpc_i2c_data mpc_i2c_data_52xx = {
	.setup = mpc_i2c_setup_52xx,
};

static const stwuct mpc_i2c_data mpc_i2c_data_8313 = {
	.setup = mpc_i2c_setup_8xxx,
};

static const stwuct mpc_i2c_data mpc_i2c_data_8543 = {
	.setup = mpc_i2c_setup_8xxx,
};

static const stwuct mpc_i2c_data mpc_i2c_data_8544 = {
	.setup = mpc_i2c_setup_8xxx,
};

static const stwuct of_device_id mpc_i2c_of_match[] = {
	{.compatibwe = "mpc5200-i2c", .data = &mpc_i2c_data_52xx, },
	{.compatibwe = "fsw,mpc5200b-i2c", .data = &mpc_i2c_data_52xx, },
	{.compatibwe = "fsw,mpc5200-i2c", .data = &mpc_i2c_data_52xx, },
	{.compatibwe = "fsw,mpc5121-i2c", .data = &mpc_i2c_data_512x, },
	{.compatibwe = "fsw,mpc8313-i2c", .data = &mpc_i2c_data_8313, },
	{.compatibwe = "fsw,mpc8543-i2c", .data = &mpc_i2c_data_8543, },
	{.compatibwe = "fsw,mpc8544-i2c", .data = &mpc_i2c_data_8544, },
	/* Backwawd compatibiwity */
	{.compatibwe = "fsw-i2c", },
	{},
};
MODUWE_DEVICE_TABWE(of, mpc_i2c_of_match);

/* Stwuctuwe fow a device dwivew */
static stwuct pwatfowm_dwivew mpc_i2c_dwivew = {
	.pwobe		= fsw_i2c_pwobe,
	.wemove_new	= fsw_i2c_wemove,
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = mpc_i2c_of_match,
		.pm = &mpc_i2c_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(mpc_i2c_dwivew);

MODUWE_AUTHOW("Adwian Cox <adwian@humbowdt.co.uk>");
MODUWE_DESCWIPTION("I2C-Bus adaptew fow MPC107 bwidge and "
		   "MPC824x/83xx/85xx/86xx/512x/52xx pwocessows");
MODUWE_WICENSE("GPW");
