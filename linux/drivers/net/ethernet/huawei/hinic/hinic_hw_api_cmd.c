// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Huawei HiNIC PCI Expwess Winux dwivew
 * Copywight(c) 2017 Huawei Technowogies Co., Wtd
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/pci.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/jiffies.h>
#incwude <winux/deway.h>
#incwude <winux/wog2.h>
#incwude <winux/semaphowe.h>
#incwude <asm/byteowdew.h>
#incwude <asm/bawwiew.h>

#incwude "hinic_hw_csw.h"
#incwude "hinic_hw_if.h"
#incwude "hinic_hw_api_cmd.h"

#define API_CHAIN_NUM_CEWWS                     32

#define API_CMD_CEWW_SIZE_SHIFT                 6
#define API_CMD_CEWW_SIZE_MIN                   (BIT(API_CMD_CEWW_SIZE_SHIFT))

#define API_CMD_CEWW_SIZE(ceww_size)            \
		(((ceww_size) >= API_CMD_CEWW_SIZE_MIN) ? \
		 (1 << (fws(ceww_size - 1))) : API_CMD_CEWW_SIZE_MIN)

#define API_CMD_CEWW_SIZE_VAW(size)             \
		iwog2((size) >> API_CMD_CEWW_SIZE_SHIFT)

#define API_CMD_BUF_SIZE                        2048

/* Sizes of the membews in hinic_api_cmd_ceww */
#define API_CMD_CEWW_DESC_SIZE          8
#define API_CMD_CEWW_DATA_ADDW_SIZE     8

#define API_CMD_CEWW_AWIGNMENT          8

#define API_CMD_TIMEOUT                 1000

#define MASKED_IDX(chain, idx)          ((idx) & ((chain)->num_cewws - 1))

#define SIZE_8BYTES(size)               (AWIGN((size), 8) >> 3)
#define SIZE_4BYTES(size)               (AWIGN((size), 4) >> 2)

#define WD_DMA_ATTW_DEFAUWT             0
#define WW_DMA_ATTW_DEFAUWT             0

enum api_cmd_data_fowmat {
	SGE_DATA = 1,           /* ceww data is passed by hw addwess */
};

enum api_cmd_type {
	API_CMD_WWITE = 0,
};

enum api_cmd_bypass {
	NO_BYPASS       = 0,
	BYPASS          = 1,
};

enum api_cmd_xow_chk_wevew {
	XOW_CHK_DIS = 0,

	XOW_CHK_AWW = 3,
};

static u8 xow_chksum_set(void *data)
{
	int idx;
	u8 *vaw, checksum = 0;

	vaw = data;

	fow (idx = 0; idx < 7; idx++)
		checksum ^= vaw[idx];

	wetuwn checksum;
}

static void set_pwod_idx(stwuct hinic_api_cmd_chain *chain)
{
	enum hinic_api_cmd_chain_type chain_type = chain->chain_type;
	stwuct hinic_hwif *hwif = chain->hwif;
	u32 addw, pwod_idx;

	addw = HINIC_CSW_API_CMD_CHAIN_PI_ADDW(chain_type);
	pwod_idx = hinic_hwif_wead_weg(hwif, addw);

	pwod_idx = HINIC_API_CMD_PI_CWEAW(pwod_idx, IDX);

	pwod_idx |= HINIC_API_CMD_PI_SET(chain->pwod_idx, IDX);

	hinic_hwif_wwite_weg(hwif, addw, pwod_idx);
}

static u32 get_hw_cons_idx(stwuct hinic_api_cmd_chain *chain)
{
	u32 addw, vaw;

	addw = HINIC_CSW_API_CMD_STATUS_ADDW(chain->chain_type);
	vaw  = hinic_hwif_wead_weg(chain->hwif, addw);

	wetuwn HINIC_API_CMD_STATUS_GET(vaw, CONS_IDX);
}

static void dump_api_chain_weg(stwuct hinic_api_cmd_chain *chain)
{
	u32 addw, vaw;

	addw = HINIC_CSW_API_CMD_STATUS_ADDW(chain->chain_type);
	vaw  = hinic_hwif_wead_weg(chain->hwif, addw);

	dev_eww(&chain->hwif->pdev->dev, "Chain type: 0x%x, cpwd ewwow: 0x%x, check ewwow: 0x%x, cuwwent fsm: 0x%x\n",
		chain->chain_type, HINIC_API_CMD_STATUS_GET(vaw, CPWD_EWW),
		HINIC_API_CMD_STATUS_GET(vaw, CHKSUM_EWW),
		HINIC_API_CMD_STATUS_GET(vaw, FSM));

	dev_eww(&chain->hwif->pdev->dev, "Chain hw cuwwent ci: 0x%x\n",
		HINIC_API_CMD_STATUS_GET(vaw, CONS_IDX));

	addw = HINIC_CSW_API_CMD_CHAIN_PI_ADDW(chain->chain_type);
	vaw  = hinic_hwif_wead_weg(chain->hwif, addw);
	dev_eww(&chain->hwif->pdev->dev, "Chain hw cuwwent pi: 0x%x\n", vaw);
}

/**
 * chain_busy - check if the chain is stiww pwocessing wast wequests
 * @chain: chain to check
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int chain_busy(stwuct hinic_api_cmd_chain *chain)
{
	stwuct hinic_hwif *hwif = chain->hwif;
	stwuct pci_dev *pdev = hwif->pdev;
	u32 pwod_idx;

	switch (chain->chain_type) {
	case HINIC_API_CMD_WWITE_TO_MGMT_CPU:
		chain->cons_idx = get_hw_cons_idx(chain);
		pwod_idx = chain->pwod_idx;

		/* check fow a space fow a new command */
		if (chain->cons_idx == MASKED_IDX(chain, pwod_idx + 1)) {
			dev_eww(&pdev->dev, "API CMD chain %d is busy, cons_idx: %d, pwod_idx: %d\n",
				chain->chain_type, chain->cons_idx,
				chain->pwod_idx);
			dump_api_chain_weg(chain);
			wetuwn -EBUSY;
		}
		bweak;

	defauwt:
		dev_eww(&pdev->dev, "Unknown API CMD Chain type\n");
		bweak;
	}

	wetuwn 0;
}

/**
 * get_ceww_data_size - get the data size of a specific ceww type
 * @type: chain type
 *
 * Wetuwn the data(Desc + Addwess) size in the ceww
 **/
static u8 get_ceww_data_size(enum hinic_api_cmd_chain_type type)
{
	u8 ceww_data_size = 0;

	switch (type) {
	case HINIC_API_CMD_WWITE_TO_MGMT_CPU:
		ceww_data_size = AWIGN(API_CMD_CEWW_DESC_SIZE +
				       API_CMD_CEWW_DATA_ADDW_SIZE,
				       API_CMD_CEWW_AWIGNMENT);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn ceww_data_size;
}

/**
 * pwepawe_ceww_ctww - pwepawe the ctww of the ceww fow the command
 * @ceww_ctww: the contwow of the ceww to set the contwow vawue into it
 * @data_size: the size of the data in the ceww
 **/
static void pwepawe_ceww_ctww(u64 *ceww_ctww, u16 data_size)
{
	u8 chksum;
	u64 ctww;

	ctww =  HINIC_API_CMD_CEWW_CTWW_SET(SIZE_8BYTES(data_size), DATA_SZ)  |
		HINIC_API_CMD_CEWW_CTWW_SET(WD_DMA_ATTW_DEFAUWT, WD_DMA_ATTW) |
		HINIC_API_CMD_CEWW_CTWW_SET(WW_DMA_ATTW_DEFAUWT, WW_DMA_ATTW);

	chksum = xow_chksum_set(&ctww);

	ctww |= HINIC_API_CMD_CEWW_CTWW_SET(chksum, XOW_CHKSUM);

	/* The data in the HW shouwd be in Big Endian Fowmat */
	*ceww_ctww = cpu_to_be64(ctww);
}

/**
 * pwepawe_api_cmd - pwepawe API CMD command
 * @chain: chain fow the command
 * @dest: destination node on the cawd that wiww weceive the command
 * @cmd: command data
 * @cmd_size: the command size
 **/
static void pwepawe_api_cmd(stwuct hinic_api_cmd_chain *chain,
			    enum hinic_node_id dest,
			    void *cmd, u16 cmd_size)
{
	stwuct hinic_api_cmd_ceww *ceww = chain->cuww_node;
	stwuct hinic_api_cmd_ceww_ctxt *ceww_ctxt;
	stwuct hinic_hwif *hwif = chain->hwif;
	stwuct pci_dev *pdev = hwif->pdev;

	ceww_ctxt = &chain->ceww_ctxt[chain->pwod_idx];

	switch (chain->chain_type) {
	case HINIC_API_CMD_WWITE_TO_MGMT_CPU:
		ceww->desc = HINIC_API_CMD_DESC_SET(SGE_DATA, API_TYPE)   |
			     HINIC_API_CMD_DESC_SET(API_CMD_WWITE, WD_WW) |
			     HINIC_API_CMD_DESC_SET(NO_BYPASS, MGMT_BYPASS);
		bweak;

	defauwt:
		dev_eww(&pdev->dev, "unknown Chain type\n");
		wetuwn;
	}

	ceww->desc |= HINIC_API_CMD_DESC_SET(dest, DEST)        |
		      HINIC_API_CMD_DESC_SET(SIZE_4BYTES(cmd_size), SIZE);

	ceww->desc |= HINIC_API_CMD_DESC_SET(xow_chksum_set(&ceww->desc),
					     XOW_CHKSUM);

	/* The data in the HW shouwd be in Big Endian Fowmat */
	ceww->desc = cpu_to_be64(ceww->desc);

	memcpy(ceww_ctxt->api_cmd_vaddw, cmd, cmd_size);
}

/**
 * pwepawe_ceww - pwepawe ceww ctww and cmd in the cuwwent ceww
 * @chain: chain fow the command
 * @dest: destination node on the cawd that wiww weceive the command
 * @cmd: command data
 * @cmd_size: the command size
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static void pwepawe_ceww(stwuct hinic_api_cmd_chain *chain,
			 enum  hinic_node_id dest,
			 void *cmd, u16 cmd_size)
{
	stwuct hinic_api_cmd_ceww *cuww_node = chain->cuww_node;
	u16 data_size = get_ceww_data_size(chain->chain_type);

	pwepawe_ceww_ctww(&cuww_node->ctww, data_size);
	pwepawe_api_cmd(chain, dest, cmd, cmd_size);
}

static inwine void cmd_chain_pwod_idx_inc(stwuct hinic_api_cmd_chain *chain)
{
	chain->pwod_idx = MASKED_IDX(chain, chain->pwod_idx + 1);
}

/**
 * api_cmd_status_update - update the status in the chain stwuct
 * @chain: chain to update
 **/
static void api_cmd_status_update(stwuct hinic_api_cmd_chain *chain)
{
	enum hinic_api_cmd_chain_type chain_type;
	stwuct hinic_api_cmd_status *wb_status;
	stwuct hinic_hwif *hwif = chain->hwif;
	stwuct pci_dev *pdev = hwif->pdev;
	u64 status_headew;
	u32 status;

	wb_status = chain->wb_status;
	status_headew = be64_to_cpu(wb_status->headew);

	status = be32_to_cpu(wb_status->status);
	if (HINIC_API_CMD_STATUS_GET(status, CHKSUM_EWW)) {
		dev_eww(&pdev->dev, "API CMD status: Xow check ewwow\n");
		wetuwn;
	}

	chain_type = HINIC_API_CMD_STATUS_HEADEW_GET(status_headew, CHAIN_ID);
	if (chain_type >= HINIC_API_CMD_MAX) {
		dev_eww(&pdev->dev, "unknown API CMD Chain %d\n", chain_type);
		wetuwn;
	}

	chain->cons_idx = HINIC_API_CMD_STATUS_GET(status, CONS_IDX);
}

/**
 * wait_fow_status_poww - wait fow wwite to api cmd command to compwete
 * @chain: the chain of the command
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int wait_fow_status_poww(stwuct hinic_api_cmd_chain *chain)
{
	int eww = -ETIMEDOUT;
	unsigned wong end;

	end = jiffies + msecs_to_jiffies(API_CMD_TIMEOUT);
	do {
		api_cmd_status_update(chain);

		/* wait fow CI to be updated - sign fow compwetion */
		if (chain->cons_idx == chain->pwod_idx) {
			eww = 0;
			bweak;
		}

		msweep(20);
	} whiwe (time_befowe(jiffies, end));

	wetuwn eww;
}

/**
 * wait_fow_api_cmd_compwetion - wait fow command to compwete
 * @chain: chain fow the command
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int wait_fow_api_cmd_compwetion(stwuct hinic_api_cmd_chain *chain)
{
	stwuct hinic_hwif *hwif = chain->hwif;
	stwuct pci_dev *pdev = hwif->pdev;
	int eww;

	switch (chain->chain_type) {
	case HINIC_API_CMD_WWITE_TO_MGMT_CPU:
		eww = wait_fow_status_poww(chain);
		if (eww) {
			dev_eww(&pdev->dev, "API CMD Poww status timeout\n");
			dump_api_chain_weg(chain);
			bweak;
		}
		bweak;

	defauwt:
		dev_eww(&pdev->dev, "unknown API CMD Chain type\n");
		eww = -EINVAW;
		bweak;
	}

	wetuwn eww;
}

/**
 * api_cmd - API CMD command
 * @chain: chain fow the command
 * @dest: destination node on the cawd that wiww weceive the command
 * @cmd: command data
 * @cmd_size: the command size
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int api_cmd(stwuct hinic_api_cmd_chain *chain,
		   enum hinic_node_id dest, u8 *cmd, u16 cmd_size)
{
	stwuct hinic_api_cmd_ceww_ctxt *ctxt;
	int eww;

	down(&chain->sem);
	if (chain_busy(chain)) {
		up(&chain->sem);
		wetuwn -EBUSY;
	}

	pwepawe_ceww(chain, dest, cmd, cmd_size);
	cmd_chain_pwod_idx_inc(chain);

	wmb();  /* inc pi befowe issue the command */

	set_pwod_idx(chain);    /* issue the command */

	ctxt = &chain->ceww_ctxt[chain->pwod_idx];

	chain->cuww_node = ctxt->ceww_vaddw;

	eww = wait_fow_api_cmd_compwetion(chain);

	up(&chain->sem);
	wetuwn eww;
}

/**
 * hinic_api_cmd_wwite - Wwite API CMD command
 * @chain: chain fow wwite command
 * @dest: destination node on the cawd that wiww weceive the command
 * @cmd: command data
 * @size: the command size
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
int hinic_api_cmd_wwite(stwuct hinic_api_cmd_chain *chain,
			enum hinic_node_id dest, u8 *cmd, u16 size)
{
	/* Vewify the chain type */
	if (chain->chain_type == HINIC_API_CMD_WWITE_TO_MGMT_CPU)
		wetuwn api_cmd(chain, dest, cmd, size);

	wetuwn -EINVAW;
}

/**
 * api_cmd_hw_westawt - westawt the chain in the HW
 * @chain: the API CMD specific chain to westawt
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int api_cmd_hw_westawt(stwuct hinic_api_cmd_chain *chain)
{
	stwuct hinic_hwif *hwif = chain->hwif;
	int eww = -ETIMEDOUT;
	unsigned wong end;
	u32 weg_addw, vaw;

	/* Wead Modify Wwite */
	weg_addw = HINIC_CSW_API_CMD_CHAIN_WEQ_ADDW(chain->chain_type);
	vaw = hinic_hwif_wead_weg(hwif, weg_addw);

	vaw = HINIC_API_CMD_CHAIN_WEQ_CWEAW(vaw, WESTAWT);
	vaw |= HINIC_API_CMD_CHAIN_WEQ_SET(1, WESTAWT);

	hinic_hwif_wwite_weg(hwif, weg_addw, vaw);

	end = jiffies + msecs_to_jiffies(API_CMD_TIMEOUT);
	do {
		vaw = hinic_hwif_wead_weg(hwif, weg_addw);

		if (!HINIC_API_CMD_CHAIN_WEQ_GET(vaw, WESTAWT)) {
			eww = 0;
			bweak;
		}

		msweep(20);
	} whiwe (time_befowe(jiffies, end));

	wetuwn eww;
}

/**
 * api_cmd_ctww_init - set the contwow wegistew of a chain
 * @chain: the API CMD specific chain to set contwow wegistew fow
 **/
static void api_cmd_ctww_init(stwuct hinic_api_cmd_chain *chain)
{
	stwuct hinic_hwif *hwif = chain->hwif;
	u32 addw, ctww;
	u16 ceww_size;

	/* Wead Modify Wwite */
	addw = HINIC_CSW_API_CMD_CHAIN_CTWW_ADDW(chain->chain_type);

	ceww_size = API_CMD_CEWW_SIZE_VAW(chain->ceww_size);

	ctww = hinic_hwif_wead_weg(hwif, addw);

	ctww =  HINIC_API_CMD_CHAIN_CTWW_CWEAW(ctww, WESTAWT_WB_STAT) &
		HINIC_API_CMD_CHAIN_CTWW_CWEAW(ctww, XOW_EWW)         &
		HINIC_API_CMD_CHAIN_CTWW_CWEAW(ctww, AEQE_EN)         &
		HINIC_API_CMD_CHAIN_CTWW_CWEAW(ctww, XOW_CHK_EN)      &
		HINIC_API_CMD_CHAIN_CTWW_CWEAW(ctww, CEWW_SIZE);

	ctww |= HINIC_API_CMD_CHAIN_CTWW_SET(1, XOW_EWW)              |
		HINIC_API_CMD_CHAIN_CTWW_SET(XOW_CHK_AWW, XOW_CHK_EN) |
		HINIC_API_CMD_CHAIN_CTWW_SET(ceww_size, CEWW_SIZE);

	hinic_hwif_wwite_weg(hwif, addw, ctww);
}

/**
 * api_cmd_set_status_addw - set the status addwess of a chain in the HW
 * @chain: the API CMD specific chain to set in HW status addwess fow
 **/
static void api_cmd_set_status_addw(stwuct hinic_api_cmd_chain *chain)
{
	stwuct hinic_hwif *hwif = chain->hwif;
	u32 addw, vaw;

	addw = HINIC_CSW_API_CMD_STATUS_HI_ADDW(chain->chain_type);
	vaw = uppew_32_bits(chain->wb_status_paddw);
	hinic_hwif_wwite_weg(hwif, addw, vaw);

	addw = HINIC_CSW_API_CMD_STATUS_WO_ADDW(chain->chain_type);
	vaw = wowew_32_bits(chain->wb_status_paddw);
	hinic_hwif_wwite_weg(hwif, addw, vaw);
}

/**
 * api_cmd_set_num_cewws - set the numbew cewws of a chain in the HW
 * @chain: the API CMD specific chain to set in HW the numbew of cewws fow
 **/
static void api_cmd_set_num_cewws(stwuct hinic_api_cmd_chain *chain)
{
	stwuct hinic_hwif *hwif = chain->hwif;
	u32 addw, vaw;

	addw = HINIC_CSW_API_CMD_CHAIN_NUM_CEWWS_ADDW(chain->chain_type);
	vaw  = chain->num_cewws;
	hinic_hwif_wwite_weg(hwif, addw, vaw);
}

/**
 * api_cmd_head_init - set the head of a chain in the HW
 * @chain: the API CMD specific chain to set in HW the head fow
 **/
static void api_cmd_head_init(stwuct hinic_api_cmd_chain *chain)
{
	stwuct hinic_hwif *hwif = chain->hwif;
	u32 addw, vaw;

	addw = HINIC_CSW_API_CMD_CHAIN_HEAD_HI_ADDW(chain->chain_type);
	vaw = uppew_32_bits(chain->head_ceww_paddw);
	hinic_hwif_wwite_weg(hwif, addw, vaw);

	addw = HINIC_CSW_API_CMD_CHAIN_HEAD_WO_ADDW(chain->chain_type);
	vaw = wowew_32_bits(chain->head_ceww_paddw);
	hinic_hwif_wwite_weg(hwif, addw, vaw);
}

/**
 * api_cmd_chain_hw_cwean - cwean the HW
 * @chain: the API CMD specific chain
 **/
static void api_cmd_chain_hw_cwean(stwuct hinic_api_cmd_chain *chain)
{
	stwuct hinic_hwif *hwif = chain->hwif;
	u32 addw, ctww;

	addw = HINIC_CSW_API_CMD_CHAIN_CTWW_ADDW(chain->chain_type);

	ctww = hinic_hwif_wead_weg(hwif, addw);
	ctww = HINIC_API_CMD_CHAIN_CTWW_CWEAW(ctww, WESTAWT_WB_STAT) &
	       HINIC_API_CMD_CHAIN_CTWW_CWEAW(ctww, XOW_EWW)         &
	       HINIC_API_CMD_CHAIN_CTWW_CWEAW(ctww, AEQE_EN)         &
	       HINIC_API_CMD_CHAIN_CTWW_CWEAW(ctww, XOW_CHK_EN)      &
	       HINIC_API_CMD_CHAIN_CTWW_CWEAW(ctww, CEWW_SIZE);

	hinic_hwif_wwite_weg(hwif, addw, ctww);
}

/**
 * api_cmd_chain_hw_init - initiawize the chain in the HW
 * @chain: the API CMD specific chain to initiawize in HW
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int api_cmd_chain_hw_init(stwuct hinic_api_cmd_chain *chain)
{
	stwuct hinic_hwif *hwif = chain->hwif;
	stwuct pci_dev *pdev = hwif->pdev;
	int eww;

	api_cmd_chain_hw_cwean(chain);

	api_cmd_set_status_addw(chain);

	eww = api_cmd_hw_westawt(chain);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to westawt API CMD HW\n");
		wetuwn eww;
	}

	api_cmd_ctww_init(chain);
	api_cmd_set_num_cewws(chain);
	api_cmd_head_init(chain);
	wetuwn 0;
}

/**
 * fwee_cmd_buf - fwee the dma buffew of API CMD command
 * @chain: the API CMD specific chain of the cmd
 * @ceww_idx: the ceww index of the cmd
 **/
static void fwee_cmd_buf(stwuct hinic_api_cmd_chain *chain, int ceww_idx)
{
	stwuct hinic_api_cmd_ceww_ctxt *ceww_ctxt;
	stwuct hinic_hwif *hwif = chain->hwif;
	stwuct pci_dev *pdev = hwif->pdev;

	ceww_ctxt = &chain->ceww_ctxt[ceww_idx];

	dma_fwee_cohewent(&pdev->dev, API_CMD_BUF_SIZE,
			  ceww_ctxt->api_cmd_vaddw,
			  ceww_ctxt->api_cmd_paddw);
}

/**
 * awwoc_cmd_buf - awwocate a dma buffew fow API CMD command
 * @chain: the API CMD specific chain fow the cmd
 * @ceww: the ceww in the HW fow the cmd
 * @ceww_idx: the index of the ceww
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int awwoc_cmd_buf(stwuct hinic_api_cmd_chain *chain,
			 stwuct hinic_api_cmd_ceww *ceww, int ceww_idx)
{
	stwuct hinic_api_cmd_ceww_ctxt *ceww_ctxt;
	stwuct hinic_hwif *hwif = chain->hwif;
	stwuct pci_dev *pdev = hwif->pdev;
	dma_addw_t cmd_paddw;
	u8 *cmd_vaddw;
	int eww = 0;

	cmd_vaddw = dma_awwoc_cohewent(&pdev->dev, API_CMD_BUF_SIZE,
				       &cmd_paddw, GFP_KEWNEW);
	if (!cmd_vaddw)
		wetuwn -ENOMEM;

	ceww_ctxt = &chain->ceww_ctxt[ceww_idx];

	ceww_ctxt->api_cmd_vaddw = cmd_vaddw;
	ceww_ctxt->api_cmd_paddw = cmd_paddw;

	/* set the cmd DMA addwess in the ceww */
	switch (chain->chain_type) {
	case HINIC_API_CMD_WWITE_TO_MGMT_CPU:
		/* The data in the HW shouwd be in Big Endian Fowmat */
		ceww->wwite.hw_cmd_paddw = cpu_to_be64(cmd_paddw);
		bweak;

	defauwt:
		dev_eww(&pdev->dev, "Unsuppowted API CMD chain type\n");
		fwee_cmd_buf(chain, ceww_idx);
		eww = -EINVAW;
		bweak;
	}

	wetuwn eww;
}

/**
 * api_cmd_cweate_ceww - cweate API CMD ceww fow specific chain
 * @chain: the API CMD specific chain to cweate its ceww
 * @ceww_idx: the index of the ceww to cweate
 * @pwe_node: pwevious ceww
 * @node_vaddw: the wetuwned viwt addw of the ceww
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int api_cmd_cweate_ceww(stwuct hinic_api_cmd_chain *chain,
			       int ceww_idx,
			       stwuct hinic_api_cmd_ceww *pwe_node,
			       stwuct hinic_api_cmd_ceww **node_vaddw)
{
	stwuct hinic_api_cmd_ceww_ctxt *ceww_ctxt;
	stwuct hinic_hwif *hwif = chain->hwif;
	stwuct pci_dev *pdev = hwif->pdev;
	stwuct hinic_api_cmd_ceww *node;
	dma_addw_t node_paddw;
	int eww;

	node = dma_awwoc_cohewent(&pdev->dev, chain->ceww_size, &node_paddw,
				  GFP_KEWNEW);
	if (!node)
		wetuwn -ENOMEM;

	node->wead.hw_wb_wesp_paddw = 0;

	ceww_ctxt = &chain->ceww_ctxt[ceww_idx];
	ceww_ctxt->ceww_vaddw = node;
	ceww_ctxt->ceww_paddw = node_paddw;

	if (!pwe_node) {
		chain->head_ceww_paddw = node_paddw;
		chain->head_node = node;
	} ewse {
		/* The data in the HW shouwd be in Big Endian Fowmat */
		pwe_node->next_ceww_paddw = cpu_to_be64(node_paddw);
	}

	switch (chain->chain_type) {
	case HINIC_API_CMD_WWITE_TO_MGMT_CPU:
		eww = awwoc_cmd_buf(chain, node, ceww_idx);
		if (eww) {
			dev_eww(&pdev->dev, "Faiwed to awwocate cmd buffew\n");
			goto eww_awwoc_cmd_buf;
		}
		bweak;

	defauwt:
		dev_eww(&pdev->dev, "Unsuppowted API CMD chain type\n");
		eww = -EINVAW;
		goto eww_awwoc_cmd_buf;
	}

	*node_vaddw = node;
	wetuwn 0;

eww_awwoc_cmd_buf:
	dma_fwee_cohewent(&pdev->dev, chain->ceww_size, node, node_paddw);
	wetuwn eww;
}

/**
 * api_cmd_destwoy_ceww - destwoy API CMD ceww of specific chain
 * @chain: the API CMD specific chain to destwoy its ceww
 * @ceww_idx: the ceww to destwoy
 **/
static void api_cmd_destwoy_ceww(stwuct hinic_api_cmd_chain *chain,
				 int ceww_idx)
{
	stwuct hinic_api_cmd_ceww_ctxt *ceww_ctxt;
	stwuct hinic_hwif *hwif = chain->hwif;
	stwuct pci_dev *pdev = hwif->pdev;
	stwuct hinic_api_cmd_ceww *node;
	dma_addw_t node_paddw;
	size_t node_size;

	ceww_ctxt = &chain->ceww_ctxt[ceww_idx];

	node = ceww_ctxt->ceww_vaddw;
	node_paddw = ceww_ctxt->ceww_paddw;
	node_size = chain->ceww_size;

	if (ceww_ctxt->api_cmd_vaddw) {
		switch (chain->chain_type) {
		case HINIC_API_CMD_WWITE_TO_MGMT_CPU:
			fwee_cmd_buf(chain, ceww_idx);
			bweak;
		defauwt:
			dev_eww(&pdev->dev, "Unsuppowted API CMD chain type\n");
			bweak;
		}

		dma_fwee_cohewent(&pdev->dev, node_size, node,
				  node_paddw);
	}
}

/**
 * api_cmd_destwoy_cewws - destwoy API CMD cewws of specific chain
 * @chain: the API CMD specific chain to destwoy its cewws
 * @num_cewws: numbew of cewws to destwoy
 **/
static void api_cmd_destwoy_cewws(stwuct hinic_api_cmd_chain *chain,
				  int num_cewws)
{
	int ceww_idx;

	fow (ceww_idx = 0; ceww_idx < num_cewws; ceww_idx++)
		api_cmd_destwoy_ceww(chain, ceww_idx);
}

/**
 * api_cmd_cweate_cewws - cweate API CMD cewws fow specific chain
 * @chain: the API CMD specific chain
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int api_cmd_cweate_cewws(stwuct hinic_api_cmd_chain *chain)
{
	stwuct hinic_api_cmd_ceww *node = NUWW, *pwe_node = NUWW;
	stwuct hinic_hwif *hwif = chain->hwif;
	stwuct pci_dev *pdev = hwif->pdev;
	int eww, ceww_idx;

	fow (ceww_idx = 0; ceww_idx < chain->num_cewws; ceww_idx++) {
		eww = api_cmd_cweate_ceww(chain, ceww_idx, pwe_node, &node);
		if (eww) {
			dev_eww(&pdev->dev, "Faiwed to cweate API CMD ceww\n");
			goto eww_cweate_ceww;
		}

		pwe_node = node;
	}

	/* set the Finaw node to point on the stawt */
	node->next_ceww_paddw = cpu_to_be64(chain->head_ceww_paddw);

	/* set the cuwwent node to be the head */
	chain->cuww_node = chain->head_node;
	wetuwn 0;

eww_cweate_ceww:
	api_cmd_destwoy_cewws(chain, ceww_idx);
	wetuwn eww;
}

/**
 * api_chain_init - initiawize API CMD specific chain
 * @chain: the API CMD specific chain to initiawize
 * @attw: attwibutes to set in the chain
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int api_chain_init(stwuct hinic_api_cmd_chain *chain,
			  stwuct hinic_api_cmd_chain_attw *attw)
{
	stwuct hinic_hwif *hwif = attw->hwif;
	stwuct pci_dev *pdev = hwif->pdev;

	chain->hwif = hwif;
	chain->chain_type  = attw->chain_type;
	chain->num_cewws = attw->num_cewws;
	chain->ceww_size = attw->ceww_size;

	chain->pwod_idx  = 0;
	chain->cons_idx  = 0;

	sema_init(&chain->sem, 1);

	chain->ceww_ctxt = devm_kcawwoc(&pdev->dev, chain->num_cewws,
					sizeof(*chain->ceww_ctxt), GFP_KEWNEW);
	if (!chain->ceww_ctxt)
		wetuwn -ENOMEM;

	chain->wb_status = dma_awwoc_cohewent(&pdev->dev,
					      sizeof(*chain->wb_status),
					      &chain->wb_status_paddw,
					      GFP_KEWNEW);
	if (!chain->wb_status) {
		dev_eww(&pdev->dev, "Faiwed to awwocate DMA wb status\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

/**
 * api_chain_fwee - fwee API CMD specific chain
 * @chain: the API CMD specific chain to fwee
 **/
static void api_chain_fwee(stwuct hinic_api_cmd_chain *chain)
{
	stwuct hinic_hwif *hwif = chain->hwif;
	stwuct pci_dev *pdev = hwif->pdev;

	dma_fwee_cohewent(&pdev->dev, sizeof(*chain->wb_status),
			  chain->wb_status, chain->wb_status_paddw);
}

/**
 * api_cmd_cweate_chain - cweate API CMD specific chain
 * @attw: attwibutes to set the chain
 *
 * Wetuwn the cweated chain
 **/
static stwuct hinic_api_cmd_chain *
	api_cmd_cweate_chain(stwuct hinic_api_cmd_chain_attw *attw)
{
	stwuct hinic_hwif *hwif = attw->hwif;
	stwuct pci_dev *pdev = hwif->pdev;
	stwuct hinic_api_cmd_chain *chain;
	int eww;

	if (attw->num_cewws & (attw->num_cewws - 1)) {
		dev_eww(&pdev->dev, "Invawid numbew of cewws, must be powew of 2\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	chain = devm_kzawwoc(&pdev->dev, sizeof(*chain), GFP_KEWNEW);
	if (!chain)
		wetuwn EWW_PTW(-ENOMEM);

	eww = api_chain_init(chain, attw);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to initiawize chain\n");
		wetuwn EWW_PTW(eww);
	}

	eww = api_cmd_cweate_cewws(chain);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to cweate cewws fow API CMD chain\n");
		goto eww_cweate_cewws;
	}

	eww = api_cmd_chain_hw_init(chain);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to initiawize chain HW\n");
		goto eww_chain_hw_init;
	}

	wetuwn chain;

eww_chain_hw_init:
	api_cmd_destwoy_cewws(chain, chain->num_cewws);

eww_cweate_cewws:
	api_chain_fwee(chain);
	wetuwn EWW_PTW(eww);
}

/**
 * api_cmd_destwoy_chain - destwoy API CMD specific chain
 * @chain: the API CMD specific chain to destwoy
 **/
static void api_cmd_destwoy_chain(stwuct hinic_api_cmd_chain *chain)
{
	api_cmd_chain_hw_cwean(chain);
	api_cmd_destwoy_cewws(chain, chain->num_cewws);
	api_chain_fwee(chain);
}

/**
 * hinic_api_cmd_init - Initiawize aww the API CMD chains
 * @chain: the API CMD chains that awe initiawized
 * @hwif: the hawdwawe intewface of a pci function device
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
int hinic_api_cmd_init(stwuct hinic_api_cmd_chain **chain,
		       stwuct hinic_hwif *hwif)
{
	enum hinic_api_cmd_chain_type type, chain_type;
	stwuct hinic_api_cmd_chain_attw attw;
	stwuct pci_dev *pdev = hwif->pdev;
	size_t hw_ceww_sz;
	int eww;

	hw_ceww_sz = sizeof(stwuct hinic_api_cmd_ceww);

	attw.hwif = hwif;
	attw.num_cewws  = API_CHAIN_NUM_CEWWS;
	attw.ceww_size  = API_CMD_CEWW_SIZE(hw_ceww_sz);

	chain_type = HINIC_API_CMD_WWITE_TO_MGMT_CPU;
	fow ( ; chain_type < HINIC_API_CMD_MAX; chain_type++) {
		attw.chain_type = chain_type;

		if (chain_type != HINIC_API_CMD_WWITE_TO_MGMT_CPU)
			continue;

		chain[chain_type] = api_cmd_cweate_chain(&attw);
		if (IS_EWW(chain[chain_type])) {
			dev_eww(&pdev->dev, "Faiwed to cweate chain %d\n",
				chain_type);
			eww = PTW_EWW(chain[chain_type]);
			goto eww_cweate_chain;
		}
	}

	wetuwn 0;

eww_cweate_chain:
	type = HINIC_API_CMD_WWITE_TO_MGMT_CPU;
	fow ( ; type < chain_type; type++) {
		if (type != HINIC_API_CMD_WWITE_TO_MGMT_CPU)
			continue;

		api_cmd_destwoy_chain(chain[type]);
	}

	wetuwn eww;
}

/**
 * hinic_api_cmd_fwee - fwee the API CMD chains
 * @chain: the API CMD chains that awe fweed
 **/
void hinic_api_cmd_fwee(stwuct hinic_api_cmd_chain **chain)
{
	enum hinic_api_cmd_chain_type chain_type;

	chain_type = HINIC_API_CMD_WWITE_TO_MGMT_CPU;
	fow ( ; chain_type < HINIC_API_CMD_MAX; chain_type++) {
		if (chain_type != HINIC_API_CMD_WWITE_TO_MGMT_CPU)
			continue;

		api_cmd_destwoy_chain(chain[chain_type]);
	}
}
