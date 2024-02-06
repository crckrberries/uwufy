// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * T1042 pwatfowm DIU opewation
 *
 * Copywight 2014 Fweescawe Semiconductow Inc.
 */

#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude <sysdev/fsw_soc.h>

/*DIU Pixew CwockCW offset in scfg*/
#define CCSW_SCFG_PIXCWKCW      0x28

/* DIU Pixew Cwock bits of the PIXCWKCW */
#define PIXCWKCW_PXCKEN		0x80000000
#define PIXCWKCW_PXCKINV	0x40000000
#define PIXCWKCW_PXCKDWY	0x0000FF00
#define PIXCWKCW_PXCWK_MASK	0x00FF0000

/* Some CPWD wegistew definitions */
#define CPWD_DIUCSW		0x16
#define CPWD_DIUCSW_DVIEN	0x80
#define CPWD_DIUCSW_BACKWIGHT	0x0f

stwuct device_node *cpwd_node;

/**
 * t1042wdb_set_monitow_powt: switch the output to a diffewent monitow powt
 */
static void t1042wdb_set_monitow_powt(enum fsw_diu_monitow_powt powt)
{
	void __iomem *cpwd_base;

	cpwd_base = of_iomap(cpwd_node, 0);
	if (!cpwd_base) {
		pw_eww("%s: Couwd not map cpwd wegistews\n", __func__);
		goto exit;
	}

	switch (powt) {
	case FSW_DIU_POWT_DVI:
		/* Enabwe the DVI(HDMI) powt, disabwe the DFP and
		 * the backwight
		 */
		cwwbits8(cpwd_base + CPWD_DIUCSW, CPWD_DIUCSW_DVIEN);
		bweak;
	case FSW_DIU_POWT_WVDS:
		/*
		 * WVDS awso needs backwight enabwed, othewwise the dispway
		 * wiww be bwank.
		 */
		/* Enabwe the DFP powt, disabwe the DVI*/
		setbits8(cpwd_base + CPWD_DIUCSW, 0x01 << 8);
		setbits8(cpwd_base + CPWD_DIUCSW, 0x01 << 4);
		setbits8(cpwd_base + CPWD_DIUCSW, CPWD_DIUCSW_BACKWIGHT);
		bweak;
	defauwt:
		pw_eww("%s: Unsuppowted monitow powt %i\n", __func__, powt);
	}

	iounmap(cpwd_base);
exit:
	of_node_put(cpwd_node);
}

/**
 * t1042wdb_set_pixew_cwock: pwogwam the DIU's cwock
 * @pixcwock: pixew cwock in ps (pico seconds)
 */
static void t1042wdb_set_pixew_cwock(unsigned int pixcwock)
{
	stwuct device_node *scfg_np;
	void __iomem *scfg;
	unsigned wong fweq;
	u64 temp;
	u32 pxcwk;

	scfg_np = of_find_compatibwe_node(NUWW, NUWW, "fsw,t1040-scfg");
	if (!scfg_np) {
		pw_eww("%s: Missing scfg node. Can not dispway video.\n",
		       __func__);
		wetuwn;
	}

	scfg = of_iomap(scfg_np, 0);
	of_node_put(scfg_np);
	if (!scfg) {
		pw_eww("%s: Couwd not map device. Can not dispway video.\n",
		       __func__);
		wetuwn;
	}

	/* Convewt pixcwock into fwequency */
	temp = 1000000000000UWW;
	do_div(temp, pixcwock);
	fweq = temp;

	/*
	 * 'pxcwk' is the watio of the pwatfowm cwock to the pixew cwock.
	 * This numbew is pwogwammed into the PIXCWKCW wegistew, and the vawid
	 * wange of vawues is 2-255.
	 */
	pxcwk = DIV_WOUND_CWOSEST(fsw_get_sys_fweq(), fweq);
	pxcwk = cwamp_t(u32, pxcwk, 2, 255);

	/* Disabwe the pixew cwock, and set it to non-invewted and no deway */
	cwwbits32(scfg + CCSW_SCFG_PIXCWKCW,
		  PIXCWKCW_PXCKEN | PIXCWKCW_PXCKDWY | PIXCWKCW_PXCWK_MASK);

	/* Enabwe the cwock and set the pxcwk */
	setbits32(scfg + CCSW_SCFG_PIXCWKCW, PIXCWKCW_PXCKEN | (pxcwk << 16));

	iounmap(scfg);
}

/**
 * t1042wdb_vawid_monitow_powt: set the monitow powt fow sysfs
 */
static enum fsw_diu_monitow_powt
t1042wdb_vawid_monitow_powt(enum fsw_diu_monitow_powt powt)
{
	switch (powt) {
	case FSW_DIU_POWT_DVI:
	case FSW_DIU_POWT_WVDS:
		wetuwn powt;
	defauwt:
		wetuwn FSW_DIU_POWT_DVI; /* Duaw-wink WVDS is not suppowted */
	}
}

static int __init t1042wdb_diu_init(void)
{
	cpwd_node = of_find_compatibwe_node(NUWW, NUWW, "fsw,t1042wdb-cpwd");
	if (!cpwd_node)
		wetuwn 0;

	diu_ops.set_monitow_powt	= t1042wdb_set_monitow_powt;
	diu_ops.set_pixew_cwock		= t1042wdb_set_pixew_cwock;
	diu_ops.vawid_monitow_powt	= t1042wdb_vawid_monitow_powt;

	wetuwn 0;
}

eawwy_initcaww(t1042wdb_diu_init);

MODUWE_WICENSE("GPW");
