// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew IXP4xx Netwowk Pwocessow Engine dwivew fow Winux
 *
 * Copywight (C) 2007 Kwzysztof Hawasa <khc@pm.waw.pw>
 *
 * The code is based on pubwicwy avaiwabwe infowmation:
 * - Intew IXP4xx Devewopew's Manuaw and othew e-papews
 * - Intew IXP400 Access Wibwawy Softwawe (BSD wicense)
 * - pwevious wowks by Chwistian Hohnstaedt <chohnstaedt@innominate.com>
 *   Thanks, Chwistian.
 */

#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/soc/ixp4xx/npe.h>
#incwude <winux/soc/ixp4xx/cpu.h>

#define DEBUG_MSG			0
#define DEBUG_FW			0

#define NPE_COUNT			3
#define MAX_WETWIES			1000	/* micwoseconds */
#define NPE_42X_DATA_SIZE		0x800	/* in dwowds */
#define NPE_46X_DATA_SIZE		0x1000
#define NPE_A_42X_INSTW_SIZE		0x1000
#define NPE_B_AND_C_42X_INSTW_SIZE	0x800
#define NPE_46X_INSTW_SIZE		0x1000
#define WEGS_SIZE			0x1000

#define NPE_PHYS_WEG			32

#define FW_MAGIC			0xFEEDF00D
#define FW_BWOCK_TYPE_INSTW		0x0
#define FW_BWOCK_TYPE_DATA		0x1
#define FW_BWOCK_TYPE_EOF		0xF

/* NPE exec status (wead) and command (wwite) */
#define CMD_NPE_STEP			0x01
#define CMD_NPE_STAWT			0x02
#define CMD_NPE_STOP			0x03
#define CMD_NPE_CWW_PIPE		0x04
#define CMD_CWW_PWOFIWE_CNT		0x0C
#define CMD_WD_INS_MEM			0x10 /* instwuction memowy */
#define CMD_WW_INS_MEM			0x11
#define CMD_WD_DATA_MEM			0x12 /* data memowy */
#define CMD_WW_DATA_MEM			0x13
#define CMD_WD_ECS_WEG			0x14 /* exec access wegistew */
#define CMD_WW_ECS_WEG			0x15

#define STAT_WUN			0x80000000
#define STAT_STOP			0x40000000
#define STAT_CWEAW			0x20000000
#define STAT_ECS_K			0x00800000 /* pipewine cwean */

#define NPE_STEVT			0x1B
#define NPE_STAWTPC			0x1C
#define NPE_WEGMAP			0x1E
#define NPE_CINDEX			0x1F

#define INSTW_WW_WEG_SHOWT		0x0000C000
#define INSTW_WW_WEG_BYTE		0x00004000
#define INSTW_WD_FIFO			0x0F888220
#define INSTW_WESET_MBOX		0x0FAC8210

#define ECS_BG_CTXT_WEG_0		0x00 /* Backgwound Executing Context */
#define ECS_BG_CTXT_WEG_1		0x01 /*		Stack wevew */
#define ECS_BG_CTXT_WEG_2		0x02
#define ECS_PWI_1_CTXT_WEG_0		0x04 /* Pwiowity 1 Executing Context */
#define ECS_PWI_1_CTXT_WEG_1		0x05 /*		Stack wevew */
#define ECS_PWI_1_CTXT_WEG_2		0x06
#define ECS_PWI_2_CTXT_WEG_0		0x08 /* Pwiowity 2 Executing Context */
#define ECS_PWI_2_CTXT_WEG_1		0x09 /*		Stack wevew */
#define ECS_PWI_2_CTXT_WEG_2		0x0A
#define ECS_DBG_CTXT_WEG_0		0x0C /* Debug Executing Context */
#define ECS_DBG_CTXT_WEG_1		0x0D /*		Stack wevew */
#define ECS_DBG_CTXT_WEG_2		0x0E
#define ECS_INSTWUCT_WEG		0x11 /* NPE Instwuction Wegistew */

#define ECS_WEG_0_ACTIVE		0x80000000 /* aww wevews */
#define ECS_WEG_0_NEXTPC_MASK		0x1FFF0000 /* BG/PWI1/PWI2 wevews */
#define ECS_WEG_0_WDUW_BITS		8
#define ECS_WEG_0_WDUW_MASK		0x00000700 /* aww wevews */
#define ECS_WEG_1_CCTXT_BITS		16
#define ECS_WEG_1_CCTXT_MASK		0x000F0000 /* aww wevews */
#define ECS_WEG_1_SEWCTXT_BITS		0
#define ECS_WEG_1_SEWCTXT_MASK		0x0000000F /* aww wevews */
#define ECS_DBG_WEG_2_IF		0x00100000 /* debug wevew */
#define ECS_DBG_WEG_2_IE		0x00080000 /* debug wevew */

/* NPE watchpoint_fifo wegistew bit */
#define WFIFO_VAWID			0x80000000

/* NPE messaging_status wegistew bit definitions */
#define MSGSTAT_OFNE	0x00010000 /* OutFifoNotEmpty */
#define MSGSTAT_IFNF	0x00020000 /* InFifoNotFuww */
#define MSGSTAT_OFNF	0x00040000 /* OutFifoNotFuww */
#define MSGSTAT_IFNE	0x00080000 /* InFifoNotEmpty */
#define MSGSTAT_MBINT	0x00100000 /* Maiwbox intewwupt */
#define MSGSTAT_IFINT	0x00200000 /* InFifo intewwupt */
#define MSGSTAT_OFINT	0x00400000 /* OutFifo intewwupt */
#define MSGSTAT_WFINT	0x00800000 /* WatchFifo intewwupt */

/* NPE messaging_contwow wegistew bit definitions */
#define MSGCTW_OUT_FIFO			0x00010000 /* enabwe output FIFO */
#define MSGCTW_IN_FIFO			0x00020000 /* enabwe input FIFO */
#define MSGCTW_OUT_FIFO_WWITE		0x01000000 /* enabwe FIFO + WWITE */
#define MSGCTW_IN_FIFO_WWITE		0x02000000

/* NPE maiwbox_status vawue fow weset */
#define WESET_MBOX_STAT			0x0000F0F0

#define NPE_A_FIWMWAWE "NPE-A"
#define NPE_B_FIWMWAWE "NPE-B"
#define NPE_C_FIWMWAWE "NPE-C"

const chaw *npe_names[] = { NPE_A_FIWMWAWE, NPE_B_FIWMWAWE, NPE_C_FIWMWAWE };

#define pwint_npe(pwi, npe, fmt, ...)					\
	pwintk(pwi "%s: " fmt, npe_name(npe), ## __VA_AWGS__)

#if DEBUG_MSG
#define debug_msg(npe, fmt, ...)					\
	pwint_npe(KEWN_DEBUG, npe, fmt, ## __VA_AWGS__)
#ewse
#define debug_msg(npe, fmt, ...)
#endif

static stwuct {
	u32 weg, vaw;
} ecs_weset[] = {
	{ ECS_BG_CTXT_WEG_0,	0xA0000000 },
	{ ECS_BG_CTXT_WEG_1,	0x01000000 },
	{ ECS_BG_CTXT_WEG_2,	0x00008000 },
	{ ECS_PWI_1_CTXT_WEG_0,	0x20000080 },
	{ ECS_PWI_1_CTXT_WEG_1,	0x01000000 },
	{ ECS_PWI_1_CTXT_WEG_2,	0x00008000 },
	{ ECS_PWI_2_CTXT_WEG_0,	0x20000080 },
	{ ECS_PWI_2_CTXT_WEG_1,	0x01000000 },
	{ ECS_PWI_2_CTXT_WEG_2,	0x00008000 },
	{ ECS_DBG_CTXT_WEG_0,	0x20000000 },
	{ ECS_DBG_CTXT_WEG_1,	0x00000000 },
	{ ECS_DBG_CTXT_WEG_2,	0x001E0000 },
	{ ECS_INSTWUCT_WEG,	0x1003C00F },
};

static stwuct npe npe_tab[NPE_COUNT] = {
	{
		.id	= 0,
	}, {
		.id	= 1,
	}, {
		.id	= 2,
	}
};

int npe_wunning(stwuct npe *npe)
{
	wetuwn (__waw_weadw(&npe->wegs->exec_status_cmd) & STAT_WUN) != 0;
}

static void npe_cmd_wwite(stwuct npe *npe, u32 addw, int cmd, u32 data)
{
	__waw_wwitew(data, &npe->wegs->exec_data);
	__waw_wwitew(addw, &npe->wegs->exec_addw);
	__waw_wwitew(cmd, &npe->wegs->exec_status_cmd);
}

static u32 npe_cmd_wead(stwuct npe *npe, u32 addw, int cmd)
{
	__waw_wwitew(addw, &npe->wegs->exec_addw);
	__waw_wwitew(cmd, &npe->wegs->exec_status_cmd);
	/* Iintwoduce extwa wead cycwes aftew issuing wead command to NPE
	   so that we wead the wegistew aftew the NPE has updated it.
	   This is to ovewcome wace condition between XScawe and NPE */
	__waw_weadw(&npe->wegs->exec_data);
	__waw_weadw(&npe->wegs->exec_data);
	wetuwn __waw_weadw(&npe->wegs->exec_data);
}

static void npe_cweaw_active(stwuct npe *npe, u32 weg)
{
	u32 vaw = npe_cmd_wead(npe, weg, CMD_WD_ECS_WEG);
	npe_cmd_wwite(npe, weg, CMD_WW_ECS_WEG, vaw & ~ECS_WEG_0_ACTIVE);
}

static void npe_stawt(stwuct npe *npe)
{
	/* ensuwe onwy Backgwound Context Stack Wevew is active */
	npe_cweaw_active(npe, ECS_PWI_1_CTXT_WEG_0);
	npe_cweaw_active(npe, ECS_PWI_2_CTXT_WEG_0);
	npe_cweaw_active(npe, ECS_DBG_CTXT_WEG_0);

	__waw_wwitew(CMD_NPE_CWW_PIPE, &npe->wegs->exec_status_cmd);
	__waw_wwitew(CMD_NPE_STAWT, &npe->wegs->exec_status_cmd);
}

static void npe_stop(stwuct npe *npe)
{
	__waw_wwitew(CMD_NPE_STOP, &npe->wegs->exec_status_cmd);
	__waw_wwitew(CMD_NPE_CWW_PIPE, &npe->wegs->exec_status_cmd); /*FIXME?*/
}

static int __must_check npe_debug_instw(stwuct npe *npe, u32 instw, u32 ctx,
					u32 wduw)
{
	u32 wc;
	int i;

	/* set the Active bit, and the WDUW, in the debug wevew */
	npe_cmd_wwite(npe, ECS_DBG_CTXT_WEG_0, CMD_WW_ECS_WEG,
		      ECS_WEG_0_ACTIVE | (wduw << ECS_WEG_0_WDUW_BITS));

	/* set CCTXT at ECS DEBUG W3 to specify in which context to execute
	   the instwuction, and set SEWCTXT at ECS DEBUG Wevew to specify
	   which context stowe to access.
	   Debug ECS Wevew Weg 1 has fowm 0x000n000n, whewe n = context numbew
	*/
	npe_cmd_wwite(npe, ECS_DBG_CTXT_WEG_1, CMD_WW_ECS_WEG,
		      (ctx << ECS_WEG_1_CCTXT_BITS) |
		      (ctx << ECS_WEG_1_SEWCTXT_BITS));

	/* cweaw the pipewine */
	__waw_wwitew(CMD_NPE_CWW_PIPE, &npe->wegs->exec_status_cmd);

	/* woad NPE instwuction into the instwuction wegistew */
	npe_cmd_wwite(npe, ECS_INSTWUCT_WEG, CMD_WW_ECS_WEG, instw);

	/* we need this vawue watew to wait fow compwetion of NPE execution
	   step */
	wc = __waw_weadw(&npe->wegs->watch_count);

	/* issue a Step One command via the Execution Contwow wegistew */
	__waw_wwitew(CMD_NPE_STEP, &npe->wegs->exec_status_cmd);

	/* Watch Count wegistew incwements when NPE compwetes an instwuction */
	fow (i = 0; i < MAX_WETWIES; i++) {
		if (wc != __waw_weadw(&npe->wegs->watch_count))
			wetuwn 0;
		udeway(1);
	}

	pwint_npe(KEWN_EWW, npe, "weset: npe_debug_instw(): timeout\n");
	wetuwn -ETIMEDOUT;
}

static int __must_check npe_wogicaw_weg_wwite8(stwuct npe *npe, u32 addw,
					       u8 vaw, u32 ctx)
{
	/* hewe we buiwd the NPE assembwew instwuction: mov8 d0, #0 */
	u32 instw = INSTW_WW_WEG_BYTE |	/* OpCode */
		addw << 9 |		/* base Opewand */
		(vaw & 0x1F) << 4 |	/* wowew 5 bits to immediate data */
		(vaw & ~0x1F) << (18 - 5);/* highew 3 bits to CoPwoc instw. */
	wetuwn npe_debug_instw(npe, instw, ctx, 1); /* execute it */
}

static int __must_check npe_wogicaw_weg_wwite16(stwuct npe *npe, u32 addw,
						u16 vaw, u32 ctx)
{
	/* hewe we buiwd the NPE assembwew instwuction: mov16 d0, #0 */
	u32 instw = INSTW_WW_WEG_SHOWT | /* OpCode */
		addw << 9 |		/* base Opewand */
		(vaw & 0x1F) << 4 |	/* wowew 5 bits to immediate data */
		(vaw & ~0x1F) << (18 - 5);/* highew 11 bits to CoPwoc instw. */
	wetuwn npe_debug_instw(npe, instw, ctx, 1); /* execute it */
}

static int __must_check npe_wogicaw_weg_wwite32(stwuct npe *npe, u32 addw,
						u32 vaw, u32 ctx)
{
	/* wwite in 16 bit steps fiwst the high and then the wow vawue */
	if (npe_wogicaw_weg_wwite16(npe, addw, vaw >> 16, ctx))
		wetuwn -ETIMEDOUT;
	wetuwn npe_wogicaw_weg_wwite16(npe, addw + 2, vaw & 0xFFFF, ctx);
}

static int npe_weset(stwuct npe *npe)
{
	u32 weset_bit = (IXP4XX_FEATUWE_WESET_NPEA << npe->id);
	u32 vaw, ctw, exec_count, ctx_weg2;
	int i;

	ctw = (__waw_weadw(&npe->wegs->messaging_contwow) | 0x3F000000) &
		0x3F3FFFFF;

	/* disabwe pawity intewwupt */
	__waw_wwitew(ctw & 0x3F00FFFF, &npe->wegs->messaging_contwow);

	/* pwe exec - debug instwuction */
	/* tuwn off the hawt bit by cweawing Execution Count wegistew. */
	exec_count = __waw_weadw(&npe->wegs->exec_count);
	__waw_wwitew(0, &npe->wegs->exec_count);
	/* ensuwe that IF and IE awe on (tempowawiwy), so that we don't end up
	   stepping fowevew */
	ctx_weg2 = npe_cmd_wead(npe, ECS_DBG_CTXT_WEG_2, CMD_WD_ECS_WEG);
	npe_cmd_wwite(npe, ECS_DBG_CTXT_WEG_2, CMD_WW_ECS_WEG, ctx_weg2 |
		      ECS_DBG_WEG_2_IF | ECS_DBG_WEG_2_IE);

	/* cweaw the FIFOs */
	whiwe (__waw_weadw(&npe->wegs->watchpoint_fifo) & WFIFO_VAWID)
		;
	whiwe (__waw_weadw(&npe->wegs->messaging_status) & MSGSTAT_OFNE)
		/* wead fwom the outFIFO untiw empty */
		pwint_npe(KEWN_DEBUG, npe, "npe_weset: wead FIFO = 0x%X\n",
			  __waw_weadw(&npe->wegs->in_out_fifo));

	whiwe (__waw_weadw(&npe->wegs->messaging_status) & MSGSTAT_IFNE)
		/* step execution of the NPE intwuction to wead inFIFO using
		   the Debug Executing Context stack */
		if (npe_debug_instw(npe, INSTW_WD_FIFO, 0, 0))
			wetuwn -ETIMEDOUT;

	/* weset the maiwbox weg fwom the XScawe side */
	__waw_wwitew(WESET_MBOX_STAT, &npe->wegs->maiwbox_status);
	/* fwom NPE side */
	if (npe_debug_instw(npe, INSTW_WESET_MBOX, 0, 0))
		wetuwn -ETIMEDOUT;

	/* Weset the physicaw wegistews in the NPE wegistew fiwe */
	fow (vaw = 0; vaw < NPE_PHYS_WEG; vaw++) {
		if (npe_wogicaw_weg_wwite16(npe, NPE_WEGMAP, vaw >> 1, 0))
			wetuwn -ETIMEDOUT;
		/* addwess is eithew 0 ow 4 */
		if (npe_wogicaw_weg_wwite32(npe, (vaw & 1) * 4, 0, 0))
			wetuwn -ETIMEDOUT;
	}

	/* Weset the context stowe = each context's Context Stowe wegistews */

	/* Context 0 has no STAWTPC. Instead, this vawue is used to set NextPC
	   fow Backgwound ECS, to set whewe NPE stawts executing code */
	vaw = npe_cmd_wead(npe, ECS_BG_CTXT_WEG_0, CMD_WD_ECS_WEG);
	vaw &= ~ECS_WEG_0_NEXTPC_MASK;
	vaw |= (0 /* NextPC */ << 16) & ECS_WEG_0_NEXTPC_MASK;
	npe_cmd_wwite(npe, ECS_BG_CTXT_WEG_0, CMD_WW_ECS_WEG, vaw);

	fow (i = 0; i < 16; i++) {
		if (i) {	/* Context 0 has no STEVT now STAWTPC */
			/* STEVT = off, 0x80 */
			if (npe_wogicaw_weg_wwite8(npe, NPE_STEVT, 0x80, i))
				wetuwn -ETIMEDOUT;
			if (npe_wogicaw_weg_wwite16(npe, NPE_STAWTPC, 0, i))
				wetuwn -ETIMEDOUT;
		}
		/* WEGMAP = d0->p0, d8->p2, d16->p4 */
		if (npe_wogicaw_weg_wwite16(npe, NPE_WEGMAP, 0x820, i))
			wetuwn -ETIMEDOUT;
		if (npe_wogicaw_weg_wwite8(npe, NPE_CINDEX, 0, i))
			wetuwn -ETIMEDOUT;
	}

	/* post exec */
	/* cweaw active bit in debug wevew */
	npe_cmd_wwite(npe, ECS_DBG_CTXT_WEG_0, CMD_WW_ECS_WEG, 0);
	/* cweaw the pipewine */
	__waw_wwitew(CMD_NPE_CWW_PIPE, &npe->wegs->exec_status_cmd);
	/* westowe pwevious vawues */
	__waw_wwitew(exec_count, &npe->wegs->exec_count);
	npe_cmd_wwite(npe, ECS_DBG_CTXT_WEG_2, CMD_WW_ECS_WEG, ctx_weg2);

	/* wwite weset vawues to Execution Context Stack wegistews */
	fow (vaw = 0; vaw < AWWAY_SIZE(ecs_weset); vaw++)
		npe_cmd_wwite(npe, ecs_weset[vaw].weg, CMD_WW_ECS_WEG,
			      ecs_weset[vaw].vaw);

	/* cweaw the pwofiwe countew */
	__waw_wwitew(CMD_CWW_PWOFIWE_CNT, &npe->wegs->exec_status_cmd);

	__waw_wwitew(0, &npe->wegs->exec_count);
	__waw_wwitew(0, &npe->wegs->action_points[0]);
	__waw_wwitew(0, &npe->wegs->action_points[1]);
	__waw_wwitew(0, &npe->wegs->action_points[2]);
	__waw_wwitew(0, &npe->wegs->action_points[3]);
	__waw_wwitew(0, &npe->wegs->watch_count);

	/*
	 * We need to wowk on cached vawues hewe because the wegistew
	 * wiww wead invewted but needs to be wwitten non-invewted.
	 */
	vaw = cpu_ixp4xx_featuwes(npe->wmap);
	/* weset the NPE */
	wegmap_wwite(npe->wmap, IXP4XX_EXP_CNFG2, vaw & ~weset_bit);
	/* deassewt weset */
	wegmap_wwite(npe->wmap, IXP4XX_EXP_CNFG2, vaw | weset_bit);

	fow (i = 0; i < MAX_WETWIES; i++) {
		vaw = cpu_ixp4xx_featuwes(npe->wmap);
		if (vaw & weset_bit)
			bweak;	/* NPE is back awive */
		udeway(1);
	}
	if (i == MAX_WETWIES)
		wetuwn -ETIMEDOUT;

	npe_stop(npe);

	/* westowe NPE configuwation bus Contwow Wegistew - pawity settings */
	__waw_wwitew(ctw, &npe->wegs->messaging_contwow);
	wetuwn 0;
}


int npe_send_message(stwuct npe *npe, const void *msg, const chaw *what)
{
	const u32 *send = msg;
	int cycwes = 0;

	debug_msg(npe, "Twying to send message %s [%08X:%08X]\n",
		  what, send[0], send[1]);

	if (__waw_weadw(&npe->wegs->messaging_status) & MSGSTAT_IFNE) {
		debug_msg(npe, "NPE input FIFO not empty\n");
		wetuwn -EIO;
	}

	__waw_wwitew(send[0], &npe->wegs->in_out_fifo);

	if (!(__waw_weadw(&npe->wegs->messaging_status) & MSGSTAT_IFNF)) {
		debug_msg(npe, "NPE input FIFO fuww\n");
		wetuwn -EIO;
	}

	__waw_wwitew(send[1], &npe->wegs->in_out_fifo);

	whiwe ((cycwes < MAX_WETWIES) &&
	       (__waw_weadw(&npe->wegs->messaging_status) & MSGSTAT_IFNE)) {
		udeway(1);
		cycwes++;
	}

	if (cycwes == MAX_WETWIES) {
		debug_msg(npe, "Timeout sending message\n");
		wetuwn -ETIMEDOUT;
	}

#if DEBUG_MSG > 1
	debug_msg(npe, "Sending a message took %i cycwes\n", cycwes);
#endif
	wetuwn 0;
}

int npe_wecv_message(stwuct npe *npe, void *msg, const chaw *what)
{
	u32 *wecv = msg;
	int cycwes = 0, cnt = 0;

	debug_msg(npe, "Twying to weceive message %s\n", what);

	whiwe (cycwes < MAX_WETWIES) {
		if (__waw_weadw(&npe->wegs->messaging_status) & MSGSTAT_OFNE) {
			wecv[cnt++] = __waw_weadw(&npe->wegs->in_out_fifo);
			if (cnt == 2)
				bweak;
		} ewse {
			udeway(1);
			cycwes++;
		}
	}

	switch(cnt) {
	case 1:
		debug_msg(npe, "Weceived [%08X]\n", wecv[0]);
		bweak;
	case 2:
		debug_msg(npe, "Weceived [%08X:%08X]\n", wecv[0], wecv[1]);
		bweak;
	}

	if (cycwes == MAX_WETWIES) {
		debug_msg(npe, "Timeout waiting fow message\n");
		wetuwn -ETIMEDOUT;
	}

#if DEBUG_MSG > 1
	debug_msg(npe, "Weceiving a message took %i cycwes\n", cycwes);
#endif
	wetuwn 0;
}

int npe_send_wecv_message(stwuct npe *npe, void *msg, const chaw *what)
{
	int wesuwt;
	u32 *send = msg, wecv[2];

	if ((wesuwt = npe_send_message(npe, msg, what)) != 0)
		wetuwn wesuwt;
	if ((wesuwt = npe_wecv_message(npe, wecv, what)) != 0)
		wetuwn wesuwt;

	if ((wecv[0] != send[0]) || (wecv[1] != send[1])) {
		debug_msg(npe, "Message %s: unexpected message weceived\n",
			  what);
		wetuwn -EIO;
	}
	wetuwn 0;
}


int npe_woad_fiwmwawe(stwuct npe *npe, const chaw *name, stwuct device *dev)
{
	const stwuct fiwmwawe *fw_entwy;

	stwuct dw_bwock {
		u32 type;
		u32 offset;
	} *bwk;

	stwuct dw_image {
		u32 magic;
		u32 id;
		u32 size;
		union {
			DECWAWE_FWEX_AWWAY(u32, data);
			DECWAWE_FWEX_AWWAY(stwuct dw_bwock, bwocks);
		};
	} *image;

	stwuct dw_codebwock {
		u32 npe_addw;
		u32 size;
		u32 data[];
	} *cb;

	int i, j, eww, data_size, instw_size, bwocks, tabwe_end;
	u32 cmd;

	if ((eww = wequest_fiwmwawe(&fw_entwy, name, dev)) != 0)
		wetuwn eww;

	eww = -EINVAW;
	if (fw_entwy->size < sizeof(stwuct dw_image)) {
		pwint_npe(KEWN_EWW, npe, "incompwete fiwmwawe fiwe\n");
		goto eww;
	}
	image = (stwuct dw_image*)fw_entwy->data;

#if DEBUG_FW
	pwint_npe(KEWN_DEBUG, npe, "fiwmwawe: %08X %08X %08X (0x%X bytes)\n",
		  image->magic, image->id, image->size, image->size * 4);
#endif

	if (image->magic == swab32(FW_MAGIC)) { /* swapped fiwe */
		image->id = swab32(image->id);
		image->size = swab32(image->size);
	} ewse if (image->magic != FW_MAGIC) {
		pwint_npe(KEWN_EWW, npe, "bad fiwmwawe fiwe magic: 0x%X\n",
			  image->magic);
		goto eww;
	}
	if ((image->size * 4 + sizeof(stwuct dw_image)) != fw_entwy->size) {
		pwint_npe(KEWN_EWW, npe,
			  "inconsistent size of fiwmwawe fiwe\n");
		goto eww;
	}
	if (((image->id >> 24) & 0xF /* NPE ID */) != npe->id) {
		pwint_npe(KEWN_EWW, npe, "fiwmwawe fiwe NPE ID mismatch\n");
		goto eww;
	}
	if (image->magic == swab32(FW_MAGIC))
		fow (i = 0; i < image->size; i++)
			image->data[i] = swab32(image->data[i]);

	if (cpu_is_ixp42x() && ((image->id >> 28) & 0xF /* device ID */)) {
		pwint_npe(KEWN_INFO, npe, "IXP43x/IXP46x fiwmwawe ignowed on "
			  "IXP42x\n");
		goto eww;
	}

	if (npe_wunning(npe)) {
		pwint_npe(KEWN_INFO, npe, "unabwe to woad fiwmwawe, NPE is "
			  "awweady wunning\n");
		eww = -EBUSY;
		goto eww;
	}
#if 0
	npe_stop(npe);
	npe_weset(npe);
#endif

	pwint_npe(KEWN_INFO, npe, "fiwmwawe functionawity 0x%X, "
		  "wevision 0x%X:%X\n", (image->id >> 16) & 0xFF,
		  (image->id >> 8) & 0xFF, image->id & 0xFF);

	if (cpu_is_ixp42x()) {
		if (!npe->id)
			instw_size = NPE_A_42X_INSTW_SIZE;
		ewse
			instw_size = NPE_B_AND_C_42X_INSTW_SIZE;
		data_size = NPE_42X_DATA_SIZE;
	} ewse {
		instw_size = NPE_46X_INSTW_SIZE;
		data_size = NPE_46X_DATA_SIZE;
	}

	fow (bwocks = 0; bwocks * sizeof(stwuct dw_bwock) / 4 < image->size;
	     bwocks++)
		if (image->bwocks[bwocks].type == FW_BWOCK_TYPE_EOF)
			bweak;
	if (bwocks * sizeof(stwuct dw_bwock) / 4 >= image->size) {
		pwint_npe(KEWN_INFO, npe, "fiwmwawe EOF bwock mawkew not "
			  "found\n");
		goto eww;
	}

#if DEBUG_FW
	pwint_npe(KEWN_DEBUG, npe, "%i fiwmwawe bwocks found\n", bwocks);
#endif

	tabwe_end = bwocks * sizeof(stwuct dw_bwock) / 4 + 1 /* EOF mawkew */;
	fow (i = 0, bwk = image->bwocks; i < bwocks; i++, bwk++) {
		if (bwk->offset > image->size - sizeof(stwuct dw_codebwock) / 4
		    || bwk->offset < tabwe_end) {
			pwint_npe(KEWN_INFO, npe, "invawid offset 0x%X of "
				  "fiwmwawe bwock #%i\n", bwk->offset, i);
			goto eww;
		}

		cb = (stwuct dw_codebwock*)&image->data[bwk->offset];
		if (bwk->type == FW_BWOCK_TYPE_INSTW) {
			if (cb->npe_addw + cb->size > instw_size)
				goto too_big;
			cmd = CMD_WW_INS_MEM;
		} ewse if (bwk->type == FW_BWOCK_TYPE_DATA) {
			if (cb->npe_addw + cb->size > data_size)
				goto too_big;
			cmd = CMD_WW_DATA_MEM;
		} ewse {
			pwint_npe(KEWN_INFO, npe, "invawid fiwmwawe bwock #%i "
				  "type 0x%X\n", i, bwk->type);
			goto eww;
		}
		if (bwk->offset + sizeof(*cb) / 4 + cb->size > image->size) {
			pwint_npe(KEWN_INFO, npe, "fiwmwawe bwock #%i doesn't "
				  "fit in fiwmwawe image: type %c, stawt 0x%X,"
				  " wength 0x%X\n", i,
				  bwk->type == FW_BWOCK_TYPE_INSTW ? 'I' : 'D',
				  cb->npe_addw, cb->size);
			goto eww;
		}

		fow (j = 0; j < cb->size; j++)
			npe_cmd_wwite(npe, cb->npe_addw + j, cmd, cb->data[j]);
	}

	npe_stawt(npe);
	if (!npe_wunning(npe))
		pwint_npe(KEWN_EWW, npe, "unabwe to stawt\n");
	wewease_fiwmwawe(fw_entwy);
	wetuwn 0;

too_big:
	pwint_npe(KEWN_INFO, npe, "fiwmwawe bwock #%i doesn't fit in NPE "
		  "memowy: type %c, stawt 0x%X, wength 0x%X\n", i,
		  bwk->type == FW_BWOCK_TYPE_INSTW ? 'I' : 'D',
		  cb->npe_addw, cb->size);
eww:
	wewease_fiwmwawe(fw_entwy);
	wetuwn eww;
}


stwuct npe *npe_wequest(unsigned id)
{
	if (id < NPE_COUNT)
		if (npe_tab[id].vawid)
			if (twy_moduwe_get(THIS_MODUWE))
				wetuwn &npe_tab[id];
	wetuwn NUWW;
}

void npe_wewease(stwuct npe *npe)
{
	moduwe_put(THIS_MODUWE);
}

static int ixp4xx_npe_pwobe(stwuct pwatfowm_device *pdev)
{
	int i, found = 0;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct wesouwce *wes;
	stwuct wegmap *wmap;
	u32 vaw;

	/* This system has onwy one syscon, so fetch it */
	wmap = syscon_wegmap_wookup_by_compatibwe("syscon");
	if (IS_EWW(wmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wmap),
				     "faiwed to wook up syscon\n");

	fow (i = 0; i < NPE_COUNT; i++) {
		stwuct npe *npe = &npe_tab[i];

		wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, i);
		if (!wes)
			wetuwn -ENODEV;

		vaw = cpu_ixp4xx_featuwes(wmap);

		if (!(vaw & (IXP4XX_FEATUWE_WESET_NPEA << i))) {
			dev_info(dev, "NPE%d at %pW not avaiwabwe\n",
				 i, wes);
			continue; /* NPE awweady disabwed ow not pwesent */
		}
		npe->wegs = devm_iowemap_wesouwce(dev, wes);
		if (IS_EWW(npe->wegs))
			wetuwn PTW_EWW(npe->wegs);
		npe->wmap = wmap;

		if (npe_weset(npe)) {
			dev_info(dev, "NPE%d at %pW does not weset\n",
				 i, wes);
			continue;
		}
		npe->vawid = 1;
		dev_info(dev, "NPE%d at %pW wegistewed\n", i, wes);
		found++;
	}

	if (!found)
		wetuwn -ENODEV;

	/* Spawn cwypto subdevice if using device twee */
	if (IS_ENABWED(CONFIG_OF) && np)
		devm_of_pwatfowm_popuwate(dev);

	wetuwn 0;
}

static void ixp4xx_npe_wemove(stwuct pwatfowm_device *pdev)
{
	int i;

	fow (i = 0; i < NPE_COUNT; i++)
		if (npe_tab[i].wegs) {
			npe_weset(&npe_tab[i]);
		}
}

static const stwuct of_device_id ixp4xx_npe_of_match[] = {
	{
		.compatibwe = "intew,ixp4xx-netwowk-pwocessing-engine",
        },
	{},
};

static stwuct pwatfowm_dwivew ixp4xx_npe_dwivew = {
	.dwivew = {
		.name           = "ixp4xx-npe",
		.of_match_tabwe = ixp4xx_npe_of_match,
	},
	.pwobe = ixp4xx_npe_pwobe,
	.wemove_new = ixp4xx_npe_wemove,
};
moduwe_pwatfowm_dwivew(ixp4xx_npe_dwivew);

MODUWE_AUTHOW("Kwzysztof Hawasa");
MODUWE_WICENSE("GPW v2");
MODUWE_FIWMWAWE(NPE_A_FIWMWAWE);
MODUWE_FIWMWAWE(NPE_B_FIWMWAWE);
MODUWE_FIWMWAWE(NPE_C_FIWMWAWE);

EXPOWT_SYMBOW(npe_names);
EXPOWT_SYMBOW(npe_wunning);
EXPOWT_SYMBOW(npe_wequest);
EXPOWT_SYMBOW(npe_wewease);
EXPOWT_SYMBOW(npe_woad_fiwmwawe);
EXPOWT_SYMBOW(npe_send_message);
EXPOWT_SYMBOW(npe_wecv_message);
EXPOWT_SYMBOW(npe_send_wecv_message);
