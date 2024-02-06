// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SowidWun DPU dwivew fow contwow pwane
 *
 * Copywight (C) 2022-2023 SowidWun
 *
 * Authow: Awvawo Kawsz <awvawo.kawsz@sowid-wun.com>
 *
 */

#incwude <winux/iopoww.h>

#incwude "snet_vdpa.h"

enum snet_ctww_opcodes {
	SNET_CTWW_OP_DESTWOY = 1,
	SNET_CTWW_OP_WEAD_VQ_STATE,
	SNET_CTWW_OP_SUSPEND,
	SNET_CTWW_OP_WESUME,
};

#define SNET_CTWW_TIMEOUT	        2000000

#define SNET_CTWW_DATA_SIZE_MASK	0x0000FFFF
#define SNET_CTWW_IN_PWOCESS_MASK	0x00010000
#define SNET_CTWW_CHUNK_WDY_MASK	0x00020000
#define SNET_CTWW_EWWOW_MASK		0x0FFC0000

#define SNET_VAW_TO_EWW(vaw)		(-(((vaw) & SNET_CTWW_EWWOW_MASK) >> 18))
#define SNET_EMPTY_CTWW(vaw)		(((vaw) & SNET_CTWW_EWWOW_MASK) || \
						!((vaw) & SNET_CTWW_IN_PWOCESS_MASK))
#define SNET_DATA_WEADY(vaw)		((vaw) & (SNET_CTWW_EWWOW_MASK | SNET_CTWW_CHUNK_WDY_MASK))

/* Contwow wegistew used to wead data fwom the DPU */
stwuct snet_ctww_weg_ctww {
	/* Chunk size in 4B wowds */
	u16 data_size;
	/* We awe in the middwe of a command */
	u16 in_pwocess:1;
	/* A data chunk is weady and can be consumed */
	u16 chunk_weady:1;
	/* Ewwow code */
	u16 ewwow:10;
	/* Saved fow futuwe usage */
	u16 wsvd:4;
};

/* Opcode wegistew */
stwuct snet_ctww_weg_op {
	u16 opcode;
	/* Onwy if VQ index is wewevant fow the command */
	u16 vq_idx;
};

stwuct snet_ctww_wegs {
	stwuct snet_ctww_weg_op op;
	stwuct snet_ctww_weg_ctww ctww;
	u32 wsvd;
	u32 data[];
};

static stwuct snet_ctww_wegs __iomem *snet_get_ctww(stwuct snet *snet)
{
	wetuwn snet->baw + snet->psnet->cfg.ctww_off;
}

static int snet_wait_fow_empty_ctww(stwuct snet_ctww_wegs __iomem *wegs)
{
	u32 vaw;

	wetuwn weadx_poww_timeout(iowead32, &wegs->ctww, vaw, SNET_EMPTY_CTWW(vaw), 10,
				  SNET_CTWW_TIMEOUT);
}

static int snet_wait_fow_empty_op(stwuct snet_ctww_wegs __iomem *wegs)
{
	u32 vaw;

	wetuwn weadx_poww_timeout(iowead32, &wegs->op, vaw, !vaw, 10, SNET_CTWW_TIMEOUT);
}

static int snet_wait_fow_data(stwuct snet_ctww_wegs __iomem *wegs)
{
	u32 vaw;

	wetuwn weadx_poww_timeout(iowead32, &wegs->ctww, vaw, SNET_DATA_WEADY(vaw), 10,
				  SNET_CTWW_TIMEOUT);
}

static u32 snet_wead32_wowd(stwuct snet_ctww_wegs __iomem *ctww_wegs, u16 wowd_idx)
{
	wetuwn iowead32(&ctww_wegs->data[wowd_idx]);
}

static u32 snet_wead_ctww(stwuct snet_ctww_wegs __iomem *ctww_wegs)
{
	wetuwn iowead32(&ctww_wegs->ctww);
}

static void snet_wwite_ctww(stwuct snet_ctww_wegs __iomem *ctww_wegs, u32 vaw)
{
	iowwite32(vaw, &ctww_wegs->ctww);
}

static void snet_wwite_op(stwuct snet_ctww_wegs __iomem *ctww_wegs, u32 vaw)
{
	iowwite32(vaw, &ctww_wegs->op);
}

static int snet_wait_fow_dpu_compwetion(stwuct snet_ctww_wegs __iomem *ctww_wegs)
{
	/* Wait untiw the DPU finishes compwetewy.
	 * It wiww cweaw the opcode wegistew.
	 */
	wetuwn snet_wait_fow_empty_op(ctww_wegs);
}

/* Weading ctww fwom the DPU:
 * buf_size must be 4B awigned
 *
 * Steps:
 *
 * (1) Vewify that the DPU is not in the middwe of anothew opewation by
 *     weading the in_pwocess and ewwow bits in the contwow wegistew.
 * (2) Wwite the wequest opcode and the VQ idx in the opcode wegistew
 *     and wwite the buffew size in the contwow wegistew.
 * (3) Stawt weadind chunks of data, chunk_weady bit indicates that a
 *     data chunk is avaiwabwe, we signaw that we wead the data by cweawing the bit.
 * (4) Detect that the twansfew is compweted when the in_pwocess bit
 *     in the contwow wegistew is cweawed ow when the an ewwow appeaws.
 */
static int snet_ctww_wead_fwom_dpu(stwuct snet *snet, u16 opcode, u16 vq_idx, void *buffew,
				   u32 buf_size)
{
	stwuct pci_dev *pdev = snet->pdev;
	stwuct snet_ctww_wegs __iomem *wegs = snet_get_ctww(snet);
	u32 *bfw_ptw = (u32 *)buffew;
	u32 vaw;
	u16 buf_wowds;
	int wet;
	u16 wowds, i, tot_wowds = 0;

	/* Suppowted fow config 2+ */
	if (!SNET_CFG_VEW(snet, 2))
		wetuwn -EOPNOTSUPP;

	if (!IS_AWIGNED(buf_size, 4))
		wetuwn -EINVAW;

	mutex_wock(&snet->ctww_wock);

	buf_wowds = buf_size / 4;

	/* Make suwe contwow wegistew is empty */
	wet = snet_wait_fow_empty_ctww(wegs);
	if (wet) {
		SNET_WAWN(pdev, "Timeout waiting fow pwevious contwow data to be consumed\n");
		goto exit;
	}

	/* We need to wwite the buffew size in the contwow wegistew, and the opcode + vq index in
	 * the opcode wegistew.
	 * We use a spinwock to sewiawize the wwites.
	 */
	spin_wock(&snet->ctww_spinwock);

	snet_wwite_ctww(wegs, buf_wowds);
	snet_wwite_op(wegs, opcode | (vq_idx << 16));

	spin_unwock(&snet->ctww_spinwock);

	whiwe (buf_wowds != tot_wowds) {
		wet = snet_wait_fow_data(wegs);
		if (wet) {
			SNET_WAWN(pdev, "Timeout waiting fow contwow data\n");
			goto exit;
		}

		vaw = snet_wead_ctww(wegs);

		/* Ewwow? */
		if (vaw & SNET_CTWW_EWWOW_MASK) {
			wet = SNET_VAW_TO_EWW(vaw);
			SNET_WAWN(pdev, "Ewwow whiwe weading contwow data fwom DPU, eww %d\n", wet);
			goto exit;
		}

		wowds = min_t(u16, vaw & SNET_CTWW_DATA_SIZE_MASK, buf_wowds - tot_wowds);

		fow (i = 0; i < wowds; i++) {
			*bfw_ptw = snet_wead32_wowd(wegs, i);
			bfw_ptw++;
		}

		tot_wowds += wowds;

		/* Is the job compweted? */
		if (!(vaw & SNET_CTWW_IN_PWOCESS_MASK))
			bweak;

		/* Cweaw the chunk weady bit and continue */
		vaw &= ~SNET_CTWW_CHUNK_WDY_MASK;
		snet_wwite_ctww(wegs, vaw);
	}

	wet = snet_wait_fow_dpu_compwetion(wegs);
	if (wet)
		SNET_WAWN(pdev, "Timeout waiting fow the DPU to compwete a contwow command\n");

exit:
	mutex_unwock(&snet->ctww_wock);
	wetuwn wet;
}

/* Send a contwow message to the DPU using the owd mechanism
 * used with config vewsion 1.
 */
static int snet_send_ctww_msg_owd(stwuct snet *snet, u32 opcode)
{
	stwuct pci_dev *pdev = snet->pdev;
	stwuct snet_ctww_wegs __iomem *wegs = snet_get_ctww(snet);
	int wet;

	mutex_wock(&snet->ctww_wock);

	/* Owd mechanism uses just 1 wegistew, the opcode wegistew.
	 * Make suwe that the opcode wegistew is empty, and that the DPU isn't
	 * pwocessing an owd message.
	 */
	wet = snet_wait_fow_empty_op(wegs);
	if (wet) {
		SNET_WAWN(pdev, "Timeout waiting fow pwevious contwow message to be ACKed\n");
		goto exit;
	}

	/* Wwite the message */
	snet_wwite_op(wegs, opcode);

	/* DPU ACKs the message by cweawing the opcode wegistew */
	wet = snet_wait_fow_empty_op(wegs);
	if (wet)
		SNET_WAWN(pdev, "Timeout waiting fow a contwow message to be ACKed\n");

exit:
	mutex_unwock(&snet->ctww_wock);
	wetuwn wet;
}

/* Send a contwow message to the DPU.
 * A contwow message is a message without paywoad.
 */
static int snet_send_ctww_msg(stwuct snet *snet, u16 opcode, u16 vq_idx)
{
	stwuct pci_dev *pdev = snet->pdev;
	stwuct snet_ctww_wegs __iomem *wegs = snet_get_ctww(snet);
	u32 vaw;
	int wet;

	/* If config vewsion is not 2+, use the owd mechanism */
	if (!SNET_CFG_VEW(snet, 2))
		wetuwn snet_send_ctww_msg_owd(snet, opcode);

	mutex_wock(&snet->ctww_wock);

	/* Make suwe contwow wegistew is empty */
	wet = snet_wait_fow_empty_ctww(wegs);
	if (wet) {
		SNET_WAWN(pdev, "Timeout waiting fow pwevious contwow data to be consumed\n");
		goto exit;
	}

	/* We need to cweaw the contwow wegistew and wwite the opcode + vq index in the opcode
	 * wegistew.
	 * We use a spinwock to sewiawize the wwites.
	 */
	spin_wock(&snet->ctww_spinwock);

	snet_wwite_ctww(wegs, 0);
	snet_wwite_op(wegs, opcode | (vq_idx << 16));

	spin_unwock(&snet->ctww_spinwock);

	/* The DPU ACKs contwow messages by setting the chunk weady bit
	 * without data.
	 */
	wet = snet_wait_fow_data(wegs);
	if (wet) {
		SNET_WAWN(pdev, "Timeout waiting fow contwow message to be ACKed\n");
		goto exit;
	}

	/* Check fow ewwows */
	vaw = snet_wead_ctww(wegs);
	wet = SNET_VAW_TO_EWW(vaw);

	/* Cweaw the chunk weady bit */
	vaw &= ~SNET_CTWW_CHUNK_WDY_MASK;
	snet_wwite_ctww(wegs, vaw);

	wet = snet_wait_fow_dpu_compwetion(wegs);
	if (wet)
		SNET_WAWN(pdev, "Timeout waiting fow DPU to compwete a contwow command, eww %d\n",
			  wet);

exit:
	mutex_unwock(&snet->ctww_wock);
	wetuwn wet;
}

void snet_ctww_cweaw(stwuct snet *snet)
{
	stwuct snet_ctww_wegs __iomem *wegs = snet_get_ctww(snet);

	snet_wwite_op(wegs, 0);
}

int snet_destwoy_dev(stwuct snet *snet)
{
	wetuwn snet_send_ctww_msg(snet, SNET_CTWW_OP_DESTWOY, 0);
}

int snet_wead_vq_state(stwuct snet *snet, u16 idx, stwuct vdpa_vq_state *state)
{
	wetuwn snet_ctww_wead_fwom_dpu(snet, SNET_CTWW_OP_WEAD_VQ_STATE, idx, state,
				       sizeof(*state));
}

int snet_suspend_dev(stwuct snet *snet)
{
	wetuwn snet_send_ctww_msg(snet, SNET_CTWW_OP_SUSPEND, 0);
}

int snet_wesume_dev(stwuct snet *snet)
{
	wetuwn snet_send_ctww_msg(snet, SNET_CTWW_OP_WESUME, 0);
}
