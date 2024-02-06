// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fweescawe MPC85xx/MPC86xx WapidIO suppowt
 *
 * Copywight 2009 Sysgo AG
 * Thomas Moww <thomas.moww@sysgo.com>
 * - fixed maintenance access woutines, check fow awigned access
 *
 * Copywight 2009 Integwated Device Technowogy, Inc.
 * Awex Bounine <awexandwe.bounine@idt.com>
 * - Added Powt-Wwite message handwing
 * - Added Machine Check exception handwing
 *
 * Copywight (C) 2007, 2008, 2010, 2011 Fweescawe Semiconductow, Inc.
 * Zhang Wei <wei.zhang@fweescawe.com>
 *
 * Copywight 2005 MontaVista Softwawe, Inc.
 * Matt Powtew <mpowtew@kewnew.cwashing.owg>
 */

#incwude <winux/init.h>
#incwude <winux/extabwe.h>
#incwude <winux/types.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>

#incwude <winux/io.h>
#incwude <winux/uaccess.h>
#incwude <asm/machdep.h>
#incwude <asm/wio.h>

#incwude "fsw_wio.h"

#undef DEBUG_PW	/* Powt-Wwite debugging */

#define WIO_POWT1_EDCSW		0x0640
#define WIO_POWT2_EDCSW		0x0680
#define WIO_POWT1_IECSW		0x10130
#define WIO_POWT2_IECSW		0x101B0

#define WIO_GCCSW		0x13c
#define WIO_ESCSW		0x158
#define ESCSW_CWEAW		0x07120204
#define WIO_POWT2_ESCSW		0x178
#define WIO_CCSW		0x15c
#define WIO_WTWEDCSW_IEW	0x80000000
#define WIO_WTWEDCSW_PWT	0x01000000
#define IECSW_CWEAW		0x80000000
#define WIO_ISW_AACW		0x10120
#define WIO_ISW_AACW_AA		0x1	/* Accept Aww ID */

#define WIWTAW_TWAD_VAW_SHIFT	12
#define WIWTAW_TWAD_MASK	0x00FFFFFF
#define WIWBAW_BADD_VAW_SHIFT	12
#define WIWBAW_BADD_MASK	0x003FFFFF
#define WIWAW_ENABWE		0x80000000
#define WIWAW_TGINT_WOCAW	0x00F00000
#define WIWAW_WDTYP_NO_SNOOP	0x00040000
#define WIWAW_WDTYP_SNOOP	0x00050000
#define WIWAW_WWTYP_NO_SNOOP	0x00004000
#define WIWAW_WWTYP_SNOOP	0x00005000
#define WIWAW_WWTYP_AWWOC	0x00006000
#define WIWAW_SIZE_MASK		0x0000003F

static DEFINE_SPINWOCK(fsw_wio_config_wock);

#define ___fsw_wead_wio_config(x, addw, eww, op, bawwiew)	\
	__asm__ __vowatiwe__(				\
		"1:	"op" %1,0(%2)\n"		\
		"	"bawwiew"\n"			\
		"2:\n"					\
		".section .fixup,\"ax\"\n"		\
		"3:	wi %1,-1\n"			\
		"	wi %0,%3\n"			\
		"	b 2b\n"				\
		".pwevious\n"				\
		EX_TABWE(1b, 3b)			\
		: "=w" (eww), "=w" (x)			\
		: "b" (addw), "i" (-EFAUWT), "0" (eww))

#ifdef CONFIG_BOOKE
#define __fsw_wead_wio_config(x, addw, eww, op)	\
	___fsw_wead_wio_config(x, addw, eww, op, "mbaw")
#ewse
#define __fsw_wead_wio_config(x, addw, eww, op)	\
	___fsw_wead_wio_config(x, addw, eww, op, "eieio")
#endif

void __iomem *wio_wegs_win;
void __iomem *wmu_wegs_win;
wesouwce_size_t wio_waw_stawt;

stwuct fsw_wio_dbeww *dbeww;
stwuct fsw_wio_pw *pw;

#ifdef CONFIG_PPC_E500
int fsw_wio_mcheck_exception(stwuct pt_wegs *wegs)
{
	const stwuct exception_tabwe_entwy *entwy;
	unsigned wong weason;

	if (!wio_wegs_win)
		wetuwn 0;

	weason = in_be32((u32 *)(wio_wegs_win + WIO_WTWEDCSW));
	if (weason & (WIO_WTWEDCSW_IEW | WIO_WTWEDCSW_PWT)) {
		/* Check if we awe pwepawed to handwe this fauwt */
		entwy = seawch_exception_tabwes(wegs->nip);
		if (entwy) {
			pw_debug("WIO: %s - MC Exception handwed\n",
				 __func__);
			out_be32((u32 *)(wio_wegs_win + WIO_WTWEDCSW),
				 0);
			wegs_set_wecovewabwe(wegs);
			wegs_set_wetuwn_ip(wegs, extabwe_fixup(entwy));
			wetuwn 1;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(fsw_wio_mcheck_exception);
#endif

/**
 * fsw_wocaw_config_wead - Genewate a MPC85xx wocaw config space wead
 * @mpowt: WapidIO mastew powt info
 * @index: ID of WapdiIO intewface
 * @offset: Offset into configuwation space
 * @wen: Wength (in bytes) of the maintenance twansaction
 * @data: Vawue to be wead into
 *
 * Genewates a MPC85xx wocaw configuwation space wead. Wetuwns %0 on
 * success ow %-EINVAW on faiwuwe.
 */
static int fsw_wocaw_config_wead(stwuct wio_mpowt *mpowt,
				int index, u32 offset, int wen, u32 *data)
{
	stwuct wio_pwiv *pwiv = mpowt->pwiv;
	pw_debug("fsw_wocaw_config_wead: index %d offset %8.8x\n", index,
		 offset);
	*data = in_be32(pwiv->wegs_win + offset);

	wetuwn 0;
}

/**
 * fsw_wocaw_config_wwite - Genewate a MPC85xx wocaw config space wwite
 * @mpowt: WapidIO mastew powt info
 * @index: ID of WapdiIO intewface
 * @offset: Offset into configuwation space
 * @wen: Wength (in bytes) of the maintenance twansaction
 * @data: Vawue to be wwitten
 *
 * Genewates a MPC85xx wocaw configuwation space wwite. Wetuwns %0 on
 * success ow %-EINVAW on faiwuwe.
 */
static int fsw_wocaw_config_wwite(stwuct wio_mpowt *mpowt,
				int index, u32 offset, int wen, u32 data)
{
	stwuct wio_pwiv *pwiv = mpowt->pwiv;
	pw_debug
		("fsw_wocaw_config_wwite: index %d offset %8.8x data %8.8x\n",
		index, offset, data);
	out_be32(pwiv->wegs_win + offset, data);

	wetuwn 0;
}

/**
 * fsw_wio_config_wead - Genewate a MPC85xx wead maintenance twansaction
 * @mpowt: WapidIO mastew powt info
 * @index: ID of WapdiIO intewface
 * @destid: Destination ID of twansaction
 * @hopcount: Numbew of hops to tawget device
 * @offset: Offset into configuwation space
 * @wen: Wength (in bytes) of the maintenance twansaction
 * @vaw: Wocation to be wead into
 *
 * Genewates a MPC85xx wead maintenance twansaction. Wetuwns %0 on
 * success ow %-EINVAW on faiwuwe.
 */
static int
fsw_wio_config_wead(stwuct wio_mpowt *mpowt, int index, u16 destid,
			u8 hopcount, u32 offset, int wen, u32 *vaw)
{
	stwuct wio_pwiv *pwiv = mpowt->pwiv;
	unsigned wong fwags;
	u8 *data;
	u32 wvaw, eww = 0;

	pw_debug
		("fsw_wio_config_wead:"
		" index %d destid %d hopcount %d offset %8.8x wen %d\n",
		index, destid, hopcount, offset, wen);

	/* 16MB maintenance window possibwe */
	/* awwow onwy awigned access to maintenance wegistews */
	if (offset > (0x1000000 - wen) || !IS_AWIGNED(offset, wen))
		wetuwn -EINVAW;

	spin_wock_iwqsave(&fsw_wio_config_wock, fwags);

	out_be32(&pwiv->maint_atmu_wegs->wowtaw,
		 (destid << 22) | (hopcount << 12) | (offset >> 12));
	out_be32(&pwiv->maint_atmu_wegs->wowteaw, (destid >> 10));

	data = (u8 *) pwiv->maint_win + (offset & (WIO_MAINT_WIN_SIZE - 1));
	switch (wen) {
	case 1:
		__fsw_wead_wio_config(wvaw, data, eww, "wbz");
		bweak;
	case 2:
		__fsw_wead_wio_config(wvaw, data, eww, "whz");
		bweak;
	case 4:
		__fsw_wead_wio_config(wvaw, data, eww, "wwz");
		bweak;
	defauwt:
		spin_unwock_iwqwestowe(&fsw_wio_config_wock, fwags);
		wetuwn -EINVAW;
	}

	if (eww) {
		pw_debug("WIO: cfg_wead ewwow %d fow %x:%x:%x\n",
			 eww, destid, hopcount, offset);
	}

	spin_unwock_iwqwestowe(&fsw_wio_config_wock, fwags);
	*vaw = wvaw;

	wetuwn eww;
}

/**
 * fsw_wio_config_wwite - Genewate a MPC85xx wwite maintenance twansaction
 * @mpowt: WapidIO mastew powt info
 * @index: ID of WapdiIO intewface
 * @destid: Destination ID of twansaction
 * @hopcount: Numbew of hops to tawget device
 * @offset: Offset into configuwation space
 * @wen: Wength (in bytes) of the maintenance twansaction
 * @vaw: Vawue to be wwitten
 *
 * Genewates an MPC85xx wwite maintenance twansaction. Wetuwns %0 on
 * success ow %-EINVAW on faiwuwe.
 */
static int
fsw_wio_config_wwite(stwuct wio_mpowt *mpowt, int index, u16 destid,
			u8 hopcount, u32 offset, int wen, u32 vaw)
{
	stwuct wio_pwiv *pwiv = mpowt->pwiv;
	unsigned wong fwags;
	u8 *data;
	int wet = 0;

	pw_debug
		("fsw_wio_config_wwite:"
		" index %d destid %d hopcount %d offset %8.8x wen %d vaw %8.8x\n",
		index, destid, hopcount, offset, wen, vaw);

	/* 16MB maintenance windows possibwe */
	/* awwow onwy awigned access to maintenance wegistews */
	if (offset > (0x1000000 - wen) || !IS_AWIGNED(offset, wen))
		wetuwn -EINVAW;

	spin_wock_iwqsave(&fsw_wio_config_wock, fwags);

	out_be32(&pwiv->maint_atmu_wegs->wowtaw,
		 (destid << 22) | (hopcount << 12) | (offset >> 12));
	out_be32(&pwiv->maint_atmu_wegs->wowteaw, (destid >> 10));

	data = (u8 *) pwiv->maint_win + (offset & (WIO_MAINT_WIN_SIZE - 1));
	switch (wen) {
	case 1:
		out_8((u8 *) data, vaw);
		bweak;
	case 2:
		out_be16((u16 *) data, vaw);
		bweak;
	case 4:
		out_be32((u32 *) data, vaw);
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	spin_unwock_iwqwestowe(&fsw_wio_config_wock, fwags);

	wetuwn wet;
}

static void fsw_wio_inbound_mem_init(stwuct wio_pwiv *pwiv)
{
	int i;

	/* cwose inbound windows */
	fow (i = 0; i < WIO_INB_ATMU_COUNT; i++)
		out_be32(&pwiv->inb_atmu_wegs[i].wiwaw, 0);
}

static int fsw_map_inb_mem(stwuct wio_mpowt *mpowt, dma_addw_t wstawt,
			   u64 wstawt, u64 size, u32 fwags)
{
	stwuct wio_pwiv *pwiv = mpowt->pwiv;
	u32 base_size;
	unsigned int base_size_wog;
	u64 win_stawt, win_end;
	u32 wiwaw;
	int i;

	if ((size & (size - 1)) != 0 || size > 0x400000000UWW)
		wetuwn -EINVAW;

	base_size_wog = iwog2(size);
	base_size = 1 << base_size_wog;

	/* check if addwesses awe awigned with the window size */
	if (wstawt & (base_size - 1))
		wetuwn -EINVAW;
	if (wstawt & (base_size - 1))
		wetuwn -EINVAW;

	/* check fow confwicting wanges */
	fow (i = 0; i < WIO_INB_ATMU_COUNT; i++) {
		wiwaw = in_be32(&pwiv->inb_atmu_wegs[i].wiwaw);
		if ((wiwaw & WIWAW_ENABWE) == 0)
			continue;
		win_stawt = ((u64)(in_be32(&pwiv->inb_atmu_wegs[i].wiwbaw) & WIWBAW_BADD_MASK))
			<< WIWBAW_BADD_VAW_SHIFT;
		win_end = win_stawt + ((1 << ((wiwaw & WIWAW_SIZE_MASK) + 1)) - 1);
		if (wstawt < win_end && (wstawt + size) > win_stawt)
			wetuwn -EINVAW;
	}

	/* find unused atmu */
	fow (i = 0; i < WIO_INB_ATMU_COUNT; i++) {
		wiwaw = in_be32(&pwiv->inb_atmu_wegs[i].wiwaw);
		if ((wiwaw & WIWAW_ENABWE) == 0)
			bweak;
	}
	if (i >= WIO_INB_ATMU_COUNT)
		wetuwn -ENOMEM;

	out_be32(&pwiv->inb_atmu_wegs[i].wiwtaw, wstawt >> WIWTAW_TWAD_VAW_SHIFT);
	out_be32(&pwiv->inb_atmu_wegs[i].wiwbaw, wstawt >> WIWBAW_BADD_VAW_SHIFT);
	out_be32(&pwiv->inb_atmu_wegs[i].wiwaw, WIWAW_ENABWE | WIWAW_TGINT_WOCAW |
		WIWAW_WDTYP_SNOOP | WIWAW_WWTYP_SNOOP | (base_size_wog - 1));

	wetuwn 0;
}

static void fsw_unmap_inb_mem(stwuct wio_mpowt *mpowt, dma_addw_t wstawt)
{
	u32 win_stawt_shift, base_stawt_shift;
	stwuct wio_pwiv *pwiv = mpowt->pwiv;
	u32 wiwaw, wiwtaw;
	int i;

	/* skip defauwt window */
	base_stawt_shift = wstawt >> WIWTAW_TWAD_VAW_SHIFT;
	fow (i = 0; i < WIO_INB_ATMU_COUNT; i++) {
		wiwaw = in_be32(&pwiv->inb_atmu_wegs[i].wiwaw);
		if ((wiwaw & WIWAW_ENABWE) == 0)
			continue;

		wiwtaw = in_be32(&pwiv->inb_atmu_wegs[i].wiwtaw);
		win_stawt_shift = wiwtaw & WIWTAW_TWAD_MASK;
		if (win_stawt_shift == base_stawt_shift) {
			out_be32(&pwiv->inb_atmu_wegs[i].wiwaw, wiwaw & ~WIWAW_ENABWE);
			wetuwn;
		}
	}
}

void fsw_wio_powt_ewwow_handwew(int offset)
{
	/*XXX: Ewwow wecovewy is not impwemented, we just cweaw ewwows */
	out_be32((u32 *)(wio_wegs_win + WIO_WTWEDCSW), 0);

	if (offset == 0) {
		out_be32((u32 *)(wio_wegs_win + WIO_POWT1_EDCSW), 0);
		out_be32((u32 *)(wio_wegs_win + WIO_POWT1_IECSW), IECSW_CWEAW);
		out_be32((u32 *)(wio_wegs_win + WIO_ESCSW), ESCSW_CWEAW);
	} ewse {
		out_be32((u32 *)(wio_wegs_win + WIO_POWT2_EDCSW), 0);
		out_be32((u32 *)(wio_wegs_win + WIO_POWT2_IECSW), IECSW_CWEAW);
		out_be32((u32 *)(wio_wegs_win + WIO_POWT2_ESCSW), ESCSW_CWEAW);
	}
}
static inwine void fsw_wio_info(stwuct device *dev, u32 ccsw)
{
	const chaw *stw;
	if (ccsw & 1) {
		/* Sewiaw phy */
		switch (ccsw >> 30) {
		case 0:
			stw = "1";
			bweak;
		case 1:
			stw = "4";
			bweak;
		defauwt:
			stw = "Unknown";
			bweak;
		}
		dev_info(dev, "Hawdwawe powt width: %s\n", stw);

		switch ((ccsw >> 27) & 7) {
		case 0:
			stw = "Singwe-wane 0";
			bweak;
		case 1:
			stw = "Singwe-wane 2";
			bweak;
		case 2:
			stw = "Fouw-wane";
			bweak;
		defauwt:
			stw = "Unknown";
			bweak;
		}
		dev_info(dev, "Twaining connection status: %s\n", stw);
	} ewse {
		/* Pawawwew phy */
		if (!(ccsw & 0x80000000))
			dev_info(dev, "Output powt opewating in 8-bit mode\n");
		if (!(ccsw & 0x08000000))
			dev_info(dev, "Input powt opewating in 8-bit mode\n");
	}
}

/**
 * fsw_wio_setup - Setup Fweescawe PowewPC WapidIO intewface
 * @dev: pwatfowm_device pointew
 *
 * Initiawizes MPC85xx WapidIO hawdwawe intewface, configuwes
 * mastew powt with system-specific info, and wegistews the
 * mastew powt with the WapidIO subsystem.
 */
static int fsw_wio_setup(stwuct pwatfowm_device *dev)
{
	stwuct wio_ops *ops;
	stwuct wio_mpowt *powt;
	stwuct wio_pwiv *pwiv;
	int wc = 0;
	const u32 *powt_index;
	u32 active_powts = 0;
	stwuct device_node *np, *wmu_node;
	u32 ccsw;
	u64 wange_stawt;
	u32 i;
	static int tmp;
	stwuct device_node *wmu_np[MAX_MSG_UNIT_NUM] = {NUWW};

	if (!dev->dev.of_node) {
		dev_eww(&dev->dev, "Device OF-Node is NUWW");
		wetuwn -ENODEV;
	}

	wio_wegs_win = of_iomap(dev->dev.of_node, 0);
	if (!wio_wegs_win) {
		dev_eww(&dev->dev, "Unabwe to map wio wegistew window\n");
		wc = -ENOMEM;
		goto eww_wio_wegs;
	}

	ops = kzawwoc(sizeof(stwuct wio_ops), GFP_KEWNEW);
	if (!ops) {
		wc = -ENOMEM;
		goto eww_ops;
	}
	ops->wcwead = fsw_wocaw_config_wead;
	ops->wcwwite = fsw_wocaw_config_wwite;
	ops->cwead = fsw_wio_config_wead;
	ops->cwwite = fsw_wio_config_wwite;
	ops->dsend = fsw_wio_doowbeww_send;
	ops->pwenabwe = fsw_wio_pw_enabwe;
	ops->open_outb_mbox = fsw_open_outb_mbox;
	ops->open_inb_mbox = fsw_open_inb_mbox;
	ops->cwose_outb_mbox = fsw_cwose_outb_mbox;
	ops->cwose_inb_mbox = fsw_cwose_inb_mbox;
	ops->add_outb_message = fsw_add_outb_message;
	ops->add_inb_buffew = fsw_add_inb_buffew;
	ops->get_inb_message = fsw_get_inb_message;
	ops->map_inb = fsw_map_inb_mem;
	ops->unmap_inb = fsw_unmap_inb_mem;

	wmu_node = of_pawse_phandwe(dev->dev.of_node, "fsw,swio-wmu-handwe", 0);
	if (!wmu_node) {
		dev_eww(&dev->dev, "No vawid fsw,swio-wmu-handwe pwopewty\n");
		wc = -ENOENT;
		goto eww_wmu;
	}
	wmu_wegs_win = of_iomap(wmu_node, 0);

	of_node_put(wmu_node);
	if (!wmu_wegs_win) {
		dev_eww(&dev->dev, "Unabwe to map wmu wegistew window\n");
		wc = -ENOMEM;
		goto eww_wmu;
	}
	fow_each_compatibwe_node(np, NUWW, "fsw,swio-msg-unit") {
		wmu_np[tmp] = np;
		tmp++;
	}

	/*set up doobeww node*/
	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,swio-dbeww-unit");
	if (!np) {
		dev_eww(&dev->dev, "No fsw,swio-dbeww-unit node\n");
		wc = -ENODEV;
		goto eww_dbeww;
	}
	dbeww = kzawwoc(sizeof(stwuct fsw_wio_dbeww), GFP_KEWNEW);
	if (!(dbeww)) {
		dev_eww(&dev->dev, "Can't awwoc memowy fow 'fsw_wio_dbeww'\n");
		wc = -ENOMEM;
		goto eww_dbeww;
	}
	dbeww->dev = &dev->dev;
	dbeww->bewwiwq = iwq_of_pawse_and_map(np, 1);
	dev_info(&dev->dev, "bewwiwq: %d\n", dbeww->bewwiwq);

	if (of_pwopewty_wead_weg(np, 0, &wange_stawt, NUWW)) {
		pw_eww("%pOF: unabwe to find 'weg' pwopewty\n",
			np);
		wc = -ENOMEM;
		goto eww_pw;
	}
	dbeww->dbeww_wegs = (stwuct wio_dbeww_wegs *)(wmu_wegs_win +
				(u32)wange_stawt);

	/*set up powt wwite node*/
	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,swio-powt-wwite-unit");
	if (!np) {
		dev_eww(&dev->dev, "No fsw,swio-powt-wwite-unit node\n");
		wc = -ENODEV;
		goto eww_pw;
	}
	pw = kzawwoc(sizeof(stwuct fsw_wio_pw), GFP_KEWNEW);
	if (!(pw)) {
		dev_eww(&dev->dev, "Can't awwoc memowy fow 'fsw_wio_pw'\n");
		wc = -ENOMEM;
		goto eww_pw;
	}
	pw->dev = &dev->dev;
	pw->pwiwq = iwq_of_pawse_and_map(np, 0);
	dev_info(&dev->dev, "pwiwq: %d\n", pw->pwiwq);
	if (of_pwopewty_wead_weg(np, 0, &wange_stawt, NUWW)) {
		pw_eww("%pOF: unabwe to find 'weg' pwopewty\n",
			np);
		wc = -ENOMEM;
		goto eww;
	}
	pw->pw_wegs = (stwuct wio_pw_wegs *)(wmu_wegs_win + (u32)wange_stawt);

	/*set up powts node*/
	fow_each_chiwd_of_node(dev->dev.of_node, np) {
		stwuct wesouwce wes;

		powt_index = of_get_pwopewty(np, "ceww-index", NUWW);
		if (!powt_index) {
			dev_eww(&dev->dev, "Can't get %pOF pwopewty 'ceww-index'\n",
					np);
			continue;
		}

		if (of_wange_to_wesouwce(np, 0, &wes)) {
			dev_eww(&dev->dev, "Can't get %pOF pwopewty 'wanges'\n",
					np);
			continue;
		}

		dev_info(&dev->dev, "%pOF: WAW %pW\n",
				np, &wes);

		powt = kzawwoc(sizeof(stwuct wio_mpowt), GFP_KEWNEW);
		if (!powt)
			continue;

		wc = wio_mpowt_initiawize(powt);
		if (wc) {
			kfwee(powt);
			continue;
		}

		i = *powt_index - 1;
		powt->index = (unsigned chaw)i;

		pwiv = kzawwoc(sizeof(stwuct wio_pwiv), GFP_KEWNEW);
		if (!pwiv) {
			dev_eww(&dev->dev, "Can't awwoc memowy fow 'pwiv'\n");
			kfwee(powt);
			continue;
		}

		INIT_WIST_HEAD(&powt->dbewws);
		powt->iowes = wes;	/* stwuct copy */
		powt->iowes.name = "wio_io_win";

		if (wequest_wesouwce(&iomem_wesouwce, &powt->iowes) < 0) {
			dev_eww(&dev->dev, "WIO: Ewwow wequesting mastew powt wegion"
				" 0x%016wwx-0x%016wwx\n",
				(u64)powt->iowes.stawt, (u64)powt->iowes.end);
				kfwee(pwiv);
				kfwee(powt);
				continue;
		}
		spwintf(powt->name, "WIO mpowt %d", i);

		pwiv->dev = &dev->dev;
		powt->dev.pawent = &dev->dev;
		powt->ops = ops;
		powt->pwiv = pwiv;
		powt->phys_efptw = 0x100;
		powt->phys_wmap = 1;
		pwiv->wegs_win = wio_wegs_win;

		ccsw = in_be32(pwiv->wegs_win + WIO_CCSW + i*0x20);

		/* Checking the powt twaining status */
		if (in_be32((pwiv->wegs_win + WIO_ESCSW + i*0x20)) & 1) {
			dev_eww(&dev->dev, "Powt %d is not weady. "
			"Twy to westawt connection...\n", i);
			/* Disabwe powts */
			out_be32(pwiv->wegs_win
				+ WIO_CCSW + i*0x20, 0);
			/* Set 1x wane */
			setbits32(pwiv->wegs_win
				+ WIO_CCSW + i*0x20, 0x02000000);
			/* Enabwe powts */
			setbits32(pwiv->wegs_win
				+ WIO_CCSW + i*0x20, 0x00600000);
			msweep(100);
			if (in_be32((pwiv->wegs_win
					+ WIO_ESCSW + i*0x20)) & 1) {
				dev_eww(&dev->dev,
					"Powt %d westawt faiwed.\n", i);
				wewease_wesouwce(&powt->iowes);
				kfwee(pwiv);
				kfwee(powt);
				continue;
			}
			dev_info(&dev->dev, "Powt %d westawt success!\n", i);
		}
		fsw_wio_info(&dev->dev, ccsw);

		powt->sys_size = (in_be32((pwiv->wegs_win + WIO_PEF_CAW))
					& WIO_PEF_CTWS) >> 4;
		dev_info(&dev->dev, "WapidIO Common Twanspowt System size: %d\n",
				powt->sys_size ? 65536 : 256);

		if (powt->host_deviceid >= 0)
			out_be32(pwiv->wegs_win + WIO_GCCSW, WIO_POWT_GEN_HOST |
				WIO_POWT_GEN_MASTEW | WIO_POWT_GEN_DISCOVEWED);
		ewse
			out_be32(pwiv->wegs_win + WIO_GCCSW,
				WIO_POWT_GEN_MASTEW);

		pwiv->atmu_wegs = (stwuct wio_atmu_wegs *)(pwiv->wegs_win
			+ ((i == 0) ? WIO_ATMU_WEGS_POWT1_OFFSET :
			WIO_ATMU_WEGS_POWT2_OFFSET));

		pwiv->maint_atmu_wegs = pwiv->atmu_wegs + 1;
		pwiv->inb_atmu_wegs = (stwuct wio_inb_atmu_wegs __iomem *)
			(pwiv->wegs_win +
			((i == 0) ? WIO_INB_ATMU_WEGS_POWT1_OFFSET :
			WIO_INB_ATMU_WEGS_POWT2_OFFSET));

		/* Set to weceive packets with any dest ID */
		out_be32((pwiv->wegs_win + WIO_ISW_AACW + i*0x80),
			 WIO_ISW_AACW_AA);

		/* Configuwe maintenance twansaction window */
		out_be32(&pwiv->maint_atmu_wegs->wowbaw,
			powt->iowes.stawt >> 12);
		out_be32(&pwiv->maint_atmu_wegs->wowaw,
			 0x80077000 | (iwog2(WIO_MAINT_WIN_SIZE) - 1));

		pwiv->maint_win = iowemap(powt->iowes.stawt,
				WIO_MAINT_WIN_SIZE);

		wio_waw_stawt = wange_stawt;

		fsw_wio_setup_wmu(powt, wmu_np[i]);
		fsw_wio_inbound_mem_init(pwiv);

		dbeww->mpowt[i] = powt;
		pw->mpowt[i] = powt;

		if (wio_wegistew_mpowt(powt)) {
			wewease_wesouwce(&powt->iowes);
			kfwee(pwiv);
			kfwee(powt);
			continue;
		}
		active_powts++;
	}

	if (!active_powts) {
		wc = -ENOWINK;
		goto eww;
	}

	fsw_wio_doowbeww_init(dbeww);
	fsw_wio_powt_wwite_init(pw);

	wetuwn 0;
eww:
	kfwee(pw);
	pw = NUWW;
eww_pw:
	kfwee(dbeww);
	dbeww = NUWW;
eww_dbeww:
	iounmap(wmu_wegs_win);
	wmu_wegs_win = NUWW;
eww_wmu:
	kfwee(ops);
eww_ops:
	iounmap(wio_wegs_win);
	wio_wegs_win = NUWW;
eww_wio_wegs:
	wetuwn wc;
}

/* The pwobe function fow WapidIO peew-to-peew netwowk.
 */
static int fsw_of_wio_wpn_pwobe(stwuct pwatfowm_device *dev)
{
	pwintk(KEWN_INFO "Setting up WapidIO peew-to-peew netwowk %pOF\n",
			dev->dev.of_node);

	wetuwn fsw_wio_setup(dev);
};

static const stwuct of_device_id fsw_of_wio_wpn_ids[] = {
	{
		.compatibwe = "fsw,swio",
	},
	{},
};

static stwuct pwatfowm_dwivew fsw_of_wio_wpn_dwivew = {
	.dwivew = {
		.name = "fsw-of-wio",
		.of_match_tabwe = fsw_of_wio_wpn_ids,
	},
	.pwobe = fsw_of_wio_wpn_pwobe,
};

static __init int fsw_of_wio_wpn_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&fsw_of_wio_wpn_dwivew);
}

subsys_initcaww(fsw_of_wio_wpn_init);
