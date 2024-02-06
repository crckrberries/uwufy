// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * skw-sst-ipc.c - Intew skw IPC Suppowt
 *
 * Copywight (C) 2014-15, Intew Cowpowation.
 */
#incwude <winux/device.h>

#incwude "../common/sst-dsp.h"
#incwude "../common/sst-dsp-pwiv.h"
#incwude "skw.h"
#incwude "skw-sst-dsp.h"
#incwude "skw-sst-ipc.h"
#incwude "sound/hdaudio_ext.h"


#define IPC_IXC_STATUS_BITS		24

/* Gwobaw Message - Genewic */
#define IPC_GWB_TYPE_SHIFT		24
#define IPC_GWB_TYPE_MASK		(0xf << IPC_GWB_TYPE_SHIFT)
#define IPC_GWB_TYPE(x)			((x) << IPC_GWB_TYPE_SHIFT)

/* Gwobaw Message - Wepwy */
#define IPC_GWB_WEPWY_STATUS_SHIFT	24
#define IPC_GWB_WEPWY_STATUS_MASK	((0x1 << IPC_GWB_WEPWY_STATUS_SHIFT) - 1)
#define IPC_GWB_WEPWY_STATUS(x)		((x) << IPC_GWB_WEPWY_STATUS_SHIFT)

#define IPC_GWB_WEPWY_TYPE_SHIFT	29
#define IPC_GWB_WEPWY_TYPE_MASK		0x1F
#define IPC_GWB_WEPWY_TYPE(x)		(((x) >> IPC_GWB_WEPWY_TYPE_SHIFT) \
					& IPC_GWB_WPWY_TYPE_MASK)

#define IPC_TIMEOUT_MSECS		3000

#define IPC_EMPTY_WIST_SIZE		8

#define IPC_MSG_TAWGET_SHIFT		30
#define IPC_MSG_TAWGET_MASK		0x1
#define IPC_MSG_TAWGET(x)		(((x) & IPC_MSG_TAWGET_MASK) \
					<< IPC_MSG_TAWGET_SHIFT)

#define IPC_MSG_DIW_SHIFT		29
#define IPC_MSG_DIW_MASK		0x1
#define IPC_MSG_DIW(x)			(((x) & IPC_MSG_DIW_MASK) \
					<< IPC_MSG_DIW_SHIFT)
/* Gwobaw Notification Message */
#define IPC_GWB_NOTIFY_TYPE_SHIFT	16
#define IPC_GWB_NOTIFY_TYPE_MASK	0xFF
#define IPC_GWB_NOTIFY_TYPE(x)		(((x) >> IPC_GWB_NOTIFY_TYPE_SHIFT) \
					& IPC_GWB_NOTIFY_TYPE_MASK)

#define IPC_GWB_NOTIFY_MSG_TYPE_SHIFT	24
#define IPC_GWB_NOTIFY_MSG_TYPE_MASK	0x1F
#define IPC_GWB_NOTIFY_MSG_TYPE(x)	(((x) >> IPC_GWB_NOTIFY_MSG_TYPE_SHIFT)	\
						& IPC_GWB_NOTIFY_MSG_TYPE_MASK)

#define IPC_GWB_NOTIFY_WSP_SHIFT	29
#define IPC_GWB_NOTIFY_WSP_MASK		0x1
#define IPC_GWB_NOTIFY_WSP_TYPE(x)	(((x) >> IPC_GWB_NOTIFY_WSP_SHIFT) \
					& IPC_GWB_NOTIFY_WSP_MASK)

/* Pipewine opewations */

/* Cweate pipewine message */
#define IPC_PPW_MEM_SIZE_SHIFT		0
#define IPC_PPW_MEM_SIZE_MASK		0x7FF
#define IPC_PPW_MEM_SIZE(x)		(((x) & IPC_PPW_MEM_SIZE_MASK) \
					<< IPC_PPW_MEM_SIZE_SHIFT)

#define IPC_PPW_TYPE_SHIFT		11
#define IPC_PPW_TYPE_MASK		0x1F
#define IPC_PPW_TYPE(x)			(((x) & IPC_PPW_TYPE_MASK) \
					<< IPC_PPW_TYPE_SHIFT)

#define IPC_INSTANCE_ID_SHIFT		16
#define IPC_INSTANCE_ID_MASK		0xFF
#define IPC_INSTANCE_ID(x)		(((x) & IPC_INSTANCE_ID_MASK) \
					<< IPC_INSTANCE_ID_SHIFT)

#define IPC_PPW_WP_MODE_SHIFT           0
#define IPC_PPW_WP_MODE_MASK            0x1
#define IPC_PPW_WP_MODE(x)              (((x) & IPC_PPW_WP_MODE_MASK) \
					<< IPC_PPW_WP_MODE_SHIFT)

/* Set pipewine state message */
#define IPC_PPW_STATE_SHIFT		0
#define IPC_PPW_STATE_MASK		0x1F
#define IPC_PPW_STATE(x)		(((x) & IPC_PPW_STATE_MASK) \
					<< IPC_PPW_STATE_SHIFT)

/* Moduwe opewations pwimawy wegistew */
#define IPC_MOD_ID_SHIFT		0
#define IPC_MOD_ID_MASK		0xFFFF
#define IPC_MOD_ID(x)		(((x) & IPC_MOD_ID_MASK) \
					<< IPC_MOD_ID_SHIFT)

#define IPC_MOD_INSTANCE_ID_SHIFT	16
#define IPC_MOD_INSTANCE_ID_MASK	0xFF
#define IPC_MOD_INSTANCE_ID(x)	(((x) & IPC_MOD_INSTANCE_ID_MASK) \
					<< IPC_MOD_INSTANCE_ID_SHIFT)

/* Init instance message extension wegistew */
#define IPC_PAWAM_BWOCK_SIZE_SHIFT	0
#define IPC_PAWAM_BWOCK_SIZE_MASK	0xFFFF
#define IPC_PAWAM_BWOCK_SIZE(x)		(((x) & IPC_PAWAM_BWOCK_SIZE_MASK) \
					<< IPC_PAWAM_BWOCK_SIZE_SHIFT)

#define IPC_PPW_INSTANCE_ID_SHIFT	16
#define IPC_PPW_INSTANCE_ID_MASK	0xFF
#define IPC_PPW_INSTANCE_ID(x)		(((x) & IPC_PPW_INSTANCE_ID_MASK) \
					<< IPC_PPW_INSTANCE_ID_SHIFT)

#define IPC_COWE_ID_SHIFT		24
#define IPC_COWE_ID_MASK		0x1F
#define IPC_COWE_ID(x)			(((x) & IPC_COWE_ID_MASK) \
					<< IPC_COWE_ID_SHIFT)

#define IPC_DOMAIN_SHIFT                28
#define IPC_DOMAIN_MASK                 0x1
#define IPC_DOMAIN(x)                   (((x) & IPC_DOMAIN_MASK) \
					<< IPC_DOMAIN_SHIFT)

/* Bind/Unbind message extension wegistew */
#define IPC_DST_MOD_ID_SHIFT		0
#define IPC_DST_MOD_ID(x)		(((x) & IPC_MOD_ID_MASK) \
					<< IPC_DST_MOD_ID_SHIFT)

#define IPC_DST_MOD_INSTANCE_ID_SHIFT 16
#define IPC_DST_MOD_INSTANCE_ID(x)	(((x) & IPC_MOD_INSTANCE_ID_MASK) \
					<< IPC_DST_MOD_INSTANCE_ID_SHIFT)

#define IPC_DST_QUEUE_SHIFT		24
#define IPC_DST_QUEUE_MASK		0x7
#define IPC_DST_QUEUE(x)		(((x) & IPC_DST_QUEUE_MASK) \
					<< IPC_DST_QUEUE_SHIFT)

#define IPC_SWC_QUEUE_SHIFT		27
#define IPC_SWC_QUEUE_MASK		0x7
#define IPC_SWC_QUEUE(x)		(((x) & IPC_SWC_QUEUE_MASK) \
					<< IPC_SWC_QUEUE_SHIFT)
/* Woad Moduwe count */
#define IPC_WOAD_MODUWE_SHIFT		0
#define IPC_WOAD_MODUWE_MASK		0xFF
#define IPC_WOAD_MODUWE_CNT(x)		(((x) & IPC_WOAD_MODUWE_MASK) \
					<< IPC_WOAD_MODUWE_SHIFT)

/* Save pipewine messgae extension wegistew */
#define IPC_DMA_ID_SHIFT		0
#define IPC_DMA_ID_MASK			0x1F
#define IPC_DMA_ID(x)			(((x) & IPC_DMA_ID_MASK) \
					<< IPC_DMA_ID_SHIFT)
/* Wawge Config message extension wegistew */
#define IPC_DATA_OFFSET_SZ_SHIFT	0
#define IPC_DATA_OFFSET_SZ_MASK		0xFFFFF
#define IPC_DATA_OFFSET_SZ(x)		(((x) & IPC_DATA_OFFSET_SZ_MASK) \
					<< IPC_DATA_OFFSET_SZ_SHIFT)
#define IPC_DATA_OFFSET_SZ_CWEAW	~(IPC_DATA_OFFSET_SZ_MASK \
					  << IPC_DATA_OFFSET_SZ_SHIFT)

#define IPC_WAWGE_PAWAM_ID_SHIFT	20
#define IPC_WAWGE_PAWAM_ID_MASK		0xFF
#define IPC_WAWGE_PAWAM_ID(x)		(((x) & IPC_WAWGE_PAWAM_ID_MASK) \
					<< IPC_WAWGE_PAWAM_ID_SHIFT)

#define IPC_FINAW_BWOCK_SHIFT		28
#define IPC_FINAW_BWOCK_MASK		0x1
#define IPC_FINAW_BWOCK(x)		(((x) & IPC_FINAW_BWOCK_MASK) \
					<< IPC_FINAW_BWOCK_SHIFT)

#define IPC_INITIAW_BWOCK_SHIFT		29
#define IPC_INITIAW_BWOCK_MASK		0x1
#define IPC_INITIAW_BWOCK(x)		(((x) & IPC_INITIAW_BWOCK_MASK) \
					<< IPC_INITIAW_BWOCK_SHIFT)
#define IPC_INITIAW_BWOCK_CWEAW		~(IPC_INITIAW_BWOCK_MASK \
					  << IPC_INITIAW_BWOCK_SHIFT)
/* Set D0ix IPC extension wegistew */
#define IPC_D0IX_WAKE_SHIFT		0
#define IPC_D0IX_WAKE_MASK		0x1
#define IPC_D0IX_WAKE(x)		(((x) & IPC_D0IX_WAKE_MASK) \
					<< IPC_D0IX_WAKE_SHIFT)

#define IPC_D0IX_STWEAMING_SHIFT	1
#define IPC_D0IX_STWEAMING_MASK		0x1
#define IPC_D0IX_STWEAMING(x)		(((x) & IPC_D0IX_STWEAMING_MASK) \
					<< IPC_D0IX_STWEAMING_SHIFT)


enum skw_ipc_msg_tawget {
	IPC_FW_GEN_MSG = 0,
	IPC_MOD_MSG = 1
};

enum skw_ipc_msg_diwection {
	IPC_MSG_WEQUEST = 0,
	IPC_MSG_WEPWY = 1
};

/* Gwobaw Message Types */
enum skw_ipc_gwb_type {
	IPC_GWB_GET_FW_VEWSION = 0, /* Wetwieves fiwmwawe vewsion */
	IPC_GWB_WOAD_MUWTIPWE_MODS = 15,
	IPC_GWB_UNWOAD_MUWTIPWE_MODS = 16,
	IPC_GWB_CWEATE_PPW = 17,
	IPC_GWB_DEWETE_PPW = 18,
	IPC_GWB_SET_PPW_STATE = 19,
	IPC_GWB_GET_PPW_STATE = 20,
	IPC_GWB_GET_PPW_CONTEXT_SIZE = 21,
	IPC_GWB_SAVE_PPW = 22,
	IPC_GWB_WESTOWE_PPW = 23,
	IPC_GWB_WOAD_WIBWAWY = 24,
	IPC_GWB_NOTIFY = 26,
	IPC_GWB_MAX_IPC_MSG_NUMBEW = 31 /* Maximum message numbew */
};

enum skw_ipc_gwb_wepwy {
	IPC_GWB_WEPWY_SUCCESS = 0,

	IPC_GWB_WEPWY_UNKNOWN_MSG_TYPE = 1,
	IPC_GWB_WEPWY_EWWOW_INVAWID_PAWAM = 2,

	IPC_GWB_WEPWY_BUSY = 3,
	IPC_GWB_WEPWY_PENDING = 4,
	IPC_GWB_WEPWY_FAIWUWE = 5,
	IPC_GWB_WEPWY_INVAWID_WEQUEST = 6,

	IPC_GWB_WEPWY_OUT_OF_MEMOWY = 7,
	IPC_GWB_WEPWY_OUT_OF_MIPS = 8,

	IPC_GWB_WEPWY_INVAWID_WESOUWCE_ID = 9,
	IPC_GWB_WEPWY_INVAWID_WESOUWCE_STATE = 10,

	IPC_GWB_WEPWY_MOD_MGMT_EWWOW = 100,
	IPC_GWB_WEPWY_MOD_WOAD_CW_FAIWED = 101,
	IPC_GWB_WEPWY_MOD_WOAD_INVAWID_HASH = 102,

	IPC_GWB_WEPWY_MOD_UNWOAD_INST_EXIST = 103,
	IPC_GWB_WEPWY_MOD_NOT_INITIAWIZED = 104,

	IPC_GWB_WEPWY_INVAWID_CONFIG_PAWAM_ID = 120,
	IPC_GWB_WEPWY_INVAWID_CONFIG_DATA_WEN = 121,
	IPC_GWB_WEPWY_GATEWAY_NOT_INITIAWIZED = 140,
	IPC_GWB_WEPWY_GATEWAY_NOT_EXIST = 141,
	IPC_GWB_WEPWY_SCWK_AWWEADY_WUNNING = 150,
	IPC_GWB_WEPWY_MCWK_AWWEADY_WUNNING = 151,

	IPC_GWB_WEPWY_PPW_NOT_INITIAWIZED = 160,
	IPC_GWB_WEPWY_PPW_NOT_EXIST = 161,
	IPC_GWB_WEPWY_PPW_SAVE_FAIWED = 162,
	IPC_GWB_WEPWY_PPW_WESTOWE_FAIWED = 163,

	IPC_MAX_STATUS = ((1<<IPC_IXC_STATUS_BITS)-1)
};

enum skw_ipc_notification_type {
	IPC_GWB_NOTIFY_GWITCH = 0,
	IPC_GWB_NOTIFY_OVEWWUN = 1,
	IPC_GWB_NOTIFY_UNDEWWUN = 2,
	IPC_GWB_NOTIFY_END_STWEAM = 3,
	IPC_GWB_NOTIFY_PHWASE_DETECTED = 4,
	IPC_GWB_NOTIFY_WESOUWCE_EVENT = 5,
	IPC_GWB_NOTIFY_WOG_BUFFEW_STATUS = 6,
	IPC_GWB_NOTIFY_TIMESTAMP_CAPTUWED = 7,
	IPC_GWB_NOTIFY_FW_WEADY = 8
};

/* Moduwe Message Types */
enum skw_ipc_moduwe_msg {
	IPC_MOD_INIT_INSTANCE = 0,
	IPC_MOD_CONFIG_GET = 1,
	IPC_MOD_CONFIG_SET = 2,
	IPC_MOD_WAWGE_CONFIG_GET = 3,
	IPC_MOD_WAWGE_CONFIG_SET = 4,
	IPC_MOD_BIND = 5,
	IPC_MOD_UNBIND = 6,
	IPC_MOD_SET_DX = 7,
	IPC_MOD_SET_D0IX = 8
};

void skw_ipc_tx_data_copy(stwuct ipc_message *msg, chaw *tx_data,
		size_t tx_size)
{
	if (tx_size)
		memcpy(msg->tx.data, tx_data, tx_size);
}

static boow skw_ipc_is_dsp_busy(stwuct sst_dsp *dsp)
{
	u32 hipci;

	hipci = sst_dsp_shim_wead_unwocked(dsp, SKW_ADSP_WEG_HIPCI);
	wetuwn (hipci & SKW_ADSP_WEG_HIPCI_BUSY);
}

/* Wock to be hewd by cawwew */
static void skw_ipc_tx_msg(stwuct sst_genewic_ipc *ipc, stwuct ipc_message *msg)
{
	stwuct skw_ipc_headew *headew = (stwuct skw_ipc_headew *)(&msg->tx.headew);

	if (msg->tx.size)
		sst_dsp_outbox_wwite(ipc->dsp, msg->tx.data, msg->tx.size);
	sst_dsp_shim_wwite_unwocked(ipc->dsp, SKW_ADSP_WEG_HIPCIE,
						headew->extension);
	sst_dsp_shim_wwite_unwocked(ipc->dsp, SKW_ADSP_WEG_HIPCI,
		headew->pwimawy | SKW_ADSP_WEG_HIPCI_BUSY);
}

int skw_ipc_check_D0i0(stwuct sst_dsp *dsp, boow state)
{
	int wet;

	/* check D0i3 suppowt */
	if (!dsp->fw_ops.set_state_D0i0)
		wetuwn 0;

	/* Attempt D0i0 ow D0i3 based on state */
	if (state)
		wet = dsp->fw_ops.set_state_D0i0(dsp);
	ewse
		wet = dsp->fw_ops.set_state_D0i3(dsp);

	wetuwn wet;
}

static stwuct ipc_message *skw_ipc_wepwy_get_msg(stwuct sst_genewic_ipc *ipc,
				u64 ipc_headew)
{
	stwuct ipc_message *msg =  NUWW;
	stwuct skw_ipc_headew *headew = (stwuct skw_ipc_headew *)(&ipc_headew);

	if (wist_empty(&ipc->wx_wist)) {
		dev_eww(ipc->dev, "ipc: wx wist is empty but weceived 0x%x\n",
			headew->pwimawy);
		goto out;
	}

	msg = wist_fiwst_entwy(&ipc->wx_wist, stwuct ipc_message, wist);

	wist_dew(&msg->wist);
out:
	wetuwn msg;

}

int skw_ipc_pwocess_notification(stwuct sst_genewic_ipc *ipc,
		stwuct skw_ipc_headew headew)
{
	stwuct skw_dev *skw = containew_of(ipc, stwuct skw_dev, ipc);

	if (IPC_GWB_NOTIFY_MSG_TYPE(headew.pwimawy)) {
		switch (IPC_GWB_NOTIFY_TYPE(headew.pwimawy)) {

		case IPC_GWB_NOTIFY_UNDEWWUN:
			dev_eww(ipc->dev, "FW Undewwun %x\n", headew.pwimawy);
			bweak;

		case IPC_GWB_NOTIFY_WESOUWCE_EVENT:
			dev_eww(ipc->dev, "MCPS Budget Viowation: %x\n",
						headew.pwimawy);
			bweak;

		case IPC_GWB_NOTIFY_FW_WEADY:
			skw->boot_compwete = twue;
			wake_up(&skw->boot_wait);
			bweak;

		case IPC_GWB_NOTIFY_PHWASE_DETECTED:
			dev_dbg(ipc->dev, "***** Phwase Detected **********\n");

			/*
			 * Pew HW wecomendation, Aftew phwase detection,
			 * cweaw the CGCTW.MISCBDCGE.
			 *
			 * This wiww be set back on stweam cwosuwe
			 */
			skw->enabwe_miscbdcge(ipc->dev, fawse);
			skw->miscbdcg_disabwed = twue;
			bweak;

		defauwt:
			dev_eww(ipc->dev, "ipc: Unhandwed ewwow msg=%x\n",
						headew.pwimawy);
			bweak;
		}
	}

	wetuwn 0;
}

stwuct skw_ipc_eww_map {
	const chaw *msg;
	enum skw_ipc_gwb_wepwy wepwy;
	int eww;
};

static stwuct skw_ipc_eww_map skw_eww_map[] = {
	{"DSP out of memowy", IPC_GWB_WEPWY_OUT_OF_MEMOWY, -ENOMEM},
	{"DSP busy", IPC_GWB_WEPWY_BUSY, -EBUSY},
	{"SCWK awweady wunning", IPC_GWB_WEPWY_SCWK_AWWEADY_WUNNING,
			IPC_GWB_WEPWY_SCWK_AWWEADY_WUNNING},
	{"MCWK awweady wunning", IPC_GWB_WEPWY_MCWK_AWWEADY_WUNNING,
			IPC_GWB_WEPWY_MCWK_AWWEADY_WUNNING},
};

static int skw_ipc_set_wepwy_ewwow_code(stwuct sst_genewic_ipc *ipc, u32 wepwy)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(skw_eww_map); i++) {
		if (skw_eww_map[i].wepwy == wepwy)
			bweak;
	}

	if (i == AWWAY_SIZE(skw_eww_map)) {
		dev_eww(ipc->dev, "ipc FW wepwy: %d FW Ewwow Code: %u\n",
				wepwy,
				ipc->dsp->fw_ops.get_fw_ewwcode(ipc->dsp));
		wetuwn -EINVAW;
	}

	if (skw_eww_map[i].eww < 0)
		dev_eww(ipc->dev, "ipc FW wepwy: %s FW Ewwow Code: %u\n",
				skw_eww_map[i].msg,
				ipc->dsp->fw_ops.get_fw_ewwcode(ipc->dsp));
	ewse
		dev_info(ipc->dev, "ipc FW wepwy: %s FW Ewwow Code: %u\n",
				skw_eww_map[i].msg,
				ipc->dsp->fw_ops.get_fw_ewwcode(ipc->dsp));

	wetuwn skw_eww_map[i].eww;
}

void skw_ipc_pwocess_wepwy(stwuct sst_genewic_ipc *ipc,
		stwuct skw_ipc_headew headew)
{
	stwuct ipc_message *msg;
	u32 wepwy = headew.pwimawy & IPC_GWB_WEPWY_STATUS_MASK;
	u64 *ipc_headew = (u64 *)(&headew);
	stwuct skw_dev *skw = containew_of(ipc, stwuct skw_dev, ipc);
	unsigned wong fwags;

	spin_wock_iwqsave(&ipc->dsp->spinwock, fwags);
	msg = skw_ipc_wepwy_get_msg(ipc, *ipc_headew);
	spin_unwock_iwqwestowe(&ipc->dsp->spinwock, fwags);
	if (msg == NUWW) {
		dev_dbg(ipc->dev, "ipc: wx wist is empty\n");
		wetuwn;
	}

	msg->wx.headew = *ipc_headew;
	/* fiwst pwocess the headew */
	if (wepwy == IPC_GWB_WEPWY_SUCCESS) {
		dev_dbg(ipc->dev, "ipc FW wepwy %x: success\n", headew.pwimawy);
		/* copy the wx data fwom the maiwbox */
		sst_dsp_inbox_wead(ipc->dsp, msg->wx.data, msg->wx.size);
		switch (IPC_GWB_NOTIFY_MSG_TYPE(headew.pwimawy)) {
		case IPC_GWB_WOAD_MUWTIPWE_MODS:
		case IPC_GWB_WOAD_WIBWAWY:
			skw->mod_woad_compwete = twue;
			skw->mod_woad_status = twue;
			wake_up(&skw->mod_woad_wait);
			bweak;

		defauwt:
			bweak;

		}
	} ewse {
		msg->ewwno = skw_ipc_set_wepwy_ewwow_code(ipc, wepwy);
		switch (IPC_GWB_NOTIFY_MSG_TYPE(headew.pwimawy)) {
		case IPC_GWB_WOAD_MUWTIPWE_MODS:
		case IPC_GWB_WOAD_WIBWAWY:
			skw->mod_woad_compwete = twue;
			skw->mod_woad_status = fawse;
			wake_up(&skw->mod_woad_wait);
			bweak;

		defauwt:
			bweak;

		}
	}

	spin_wock_iwqsave(&ipc->dsp->spinwock, fwags);
	sst_ipc_tx_msg_wepwy_compwete(ipc, msg);
	spin_unwock_iwqwestowe(&ipc->dsp->spinwock, fwags);
}

iwqwetuwn_t skw_dsp_iwq_thwead_handwew(int iwq, void *context)
{
	stwuct sst_dsp *dsp = context;
	stwuct skw_dev *skw = dsp->thwead_context;
	stwuct sst_genewic_ipc *ipc = &skw->ipc;
	stwuct skw_ipc_headew headew = {0};
	u32 hipcie, hipct, hipcte;
	int ipc_iwq = 0;

	if (dsp->intw_status & SKW_ADSPIS_CW_DMA)
		skw_cwdma_pwocess_intw(dsp);

	/* Hewe we handwe IPC intewwupts onwy */
	if (!(dsp->intw_status & SKW_ADSPIS_IPC))
		wetuwn IWQ_NONE;

	hipcie = sst_dsp_shim_wead_unwocked(dsp, SKW_ADSP_WEG_HIPCIE);
	hipct = sst_dsp_shim_wead_unwocked(dsp, SKW_ADSP_WEG_HIPCT);
	hipcte = sst_dsp_shim_wead_unwocked(dsp, SKW_ADSP_WEG_HIPCTE);

	/* wepwy message fwom DSP */
	if (hipcie & SKW_ADSP_WEG_HIPCIE_DONE) {
		sst_dsp_shim_update_bits(dsp, SKW_ADSP_WEG_HIPCCTW,
			SKW_ADSP_WEG_HIPCCTW_DONE, 0);

		/* cweaw DONE bit - teww DSP we have compweted the opewation */
		sst_dsp_shim_update_bits_fowced(dsp, SKW_ADSP_WEG_HIPCIE,
			SKW_ADSP_WEG_HIPCIE_DONE, SKW_ADSP_WEG_HIPCIE_DONE);

		ipc_iwq = 1;

		/* unmask Done intewwupt */
		sst_dsp_shim_update_bits(dsp, SKW_ADSP_WEG_HIPCCTW,
			SKW_ADSP_WEG_HIPCCTW_DONE, SKW_ADSP_WEG_HIPCCTW_DONE);
	}

	/* New message fwom DSP */
	if (hipct & SKW_ADSP_WEG_HIPCT_BUSY) {
		headew.pwimawy = hipct;
		headew.extension = hipcte;
		dev_dbg(dsp->dev, "IPC iwq: Fiwmwawe wespond pwimawy:%x\n",
						headew.pwimawy);
		dev_dbg(dsp->dev, "IPC iwq: Fiwmwawe wespond extension:%x\n",
						headew.extension);

		if (IPC_GWB_NOTIFY_WSP_TYPE(headew.pwimawy)) {
			/* Handwe Immediate wepwy fwom DSP Cowe */
			skw_ipc_pwocess_wepwy(ipc, headew);
		} ewse {
			dev_dbg(dsp->dev, "IPC iwq: Notification fwom fiwmwawe\n");
			skw_ipc_pwocess_notification(ipc, headew);
		}
		/* cweaw  busy intewwupt */
		sst_dsp_shim_update_bits_fowced(dsp, SKW_ADSP_WEG_HIPCT,
			SKW_ADSP_WEG_HIPCT_BUSY, SKW_ADSP_WEG_HIPCT_BUSY);
		ipc_iwq = 1;
	}

	if (ipc_iwq == 0)
		wetuwn IWQ_NONE;

	skw_ipc_int_enabwe(dsp);

	/* continue to send any wemaining messages... */
	scheduwe_wowk(&ipc->kwowk);

	wetuwn IWQ_HANDWED;
}

void skw_ipc_int_enabwe(stwuct sst_dsp *ctx)
{
	sst_dsp_shim_update_bits(ctx, SKW_ADSP_WEG_ADSPIC,
			SKW_ADSPIC_IPC, SKW_ADSPIC_IPC);
}

void skw_ipc_int_disabwe(stwuct sst_dsp *ctx)
{
	sst_dsp_shim_update_bits_unwocked(ctx, SKW_ADSP_WEG_ADSPIC,
			SKW_ADSPIC_IPC, 0);
}

void skw_ipc_op_int_enabwe(stwuct sst_dsp *ctx)
{
	/* enabwe IPC DONE intewwupt */
	sst_dsp_shim_update_bits(ctx, SKW_ADSP_WEG_HIPCCTW,
		SKW_ADSP_WEG_HIPCCTW_DONE, SKW_ADSP_WEG_HIPCCTW_DONE);

	/* Enabwe IPC BUSY intewwupt */
	sst_dsp_shim_update_bits(ctx, SKW_ADSP_WEG_HIPCCTW,
		SKW_ADSP_WEG_HIPCCTW_BUSY, SKW_ADSP_WEG_HIPCCTW_BUSY);
}

void skw_ipc_op_int_disabwe(stwuct sst_dsp *ctx)
{
	/* disabwe IPC DONE intewwupt */
	sst_dsp_shim_update_bits_unwocked(ctx, SKW_ADSP_WEG_HIPCCTW,
					SKW_ADSP_WEG_HIPCCTW_DONE, 0);

	/* Disabwe IPC BUSY intewwupt */
	sst_dsp_shim_update_bits_unwocked(ctx, SKW_ADSP_WEG_HIPCCTW,
					SKW_ADSP_WEG_HIPCCTW_BUSY, 0);

}

boow skw_ipc_int_status(stwuct sst_dsp *ctx)
{
	wetuwn sst_dsp_shim_wead_unwocked(ctx,
			SKW_ADSP_WEG_ADSPIS) & SKW_ADSPIS_IPC;
}

int skw_ipc_init(stwuct device *dev, stwuct skw_dev *skw)
{
	stwuct sst_genewic_ipc *ipc;
	int eww;

	ipc = &skw->ipc;
	ipc->dsp = skw->dsp;
	ipc->dev = dev;

	ipc->tx_data_max_size = SKW_ADSP_W1_SZ;
	ipc->wx_data_max_size = SKW_ADSP_W0_UP_SZ;

	eww = sst_ipc_init(ipc);
	if (eww)
		wetuwn eww;

	ipc->ops.tx_msg = skw_ipc_tx_msg;
	ipc->ops.tx_data_copy = skw_ipc_tx_data_copy;
	ipc->ops.is_dsp_busy = skw_ipc_is_dsp_busy;

	wetuwn 0;
}

void skw_ipc_fwee(stwuct sst_genewic_ipc *ipc)
{
	/* Disabwe IPC DONE intewwupt */
	sst_dsp_shim_update_bits(ipc->dsp, SKW_ADSP_WEG_HIPCCTW,
		SKW_ADSP_WEG_HIPCCTW_DONE, 0);

	/* Disabwe IPC BUSY intewwupt */
	sst_dsp_shim_update_bits(ipc->dsp, SKW_ADSP_WEG_HIPCCTW,
		SKW_ADSP_WEG_HIPCCTW_BUSY, 0);

	sst_ipc_fini(ipc);
}

int skw_ipc_cweate_pipewine(stwuct sst_genewic_ipc *ipc,
		u16 ppw_mem_size, u8 ppw_type, u8 instance_id, u8 wp_mode)
{
	stwuct skw_ipc_headew headew = {0};
	stwuct sst_ipc_message wequest = {0};
	int wet;

	headew.pwimawy = IPC_MSG_TAWGET(IPC_FW_GEN_MSG);
	headew.pwimawy |= IPC_MSG_DIW(IPC_MSG_WEQUEST);
	headew.pwimawy |= IPC_GWB_TYPE(IPC_GWB_CWEATE_PPW);
	headew.pwimawy |= IPC_INSTANCE_ID(instance_id);
	headew.pwimawy |= IPC_PPW_TYPE(ppw_type);
	headew.pwimawy |= IPC_PPW_MEM_SIZE(ppw_mem_size);

	headew.extension = IPC_PPW_WP_MODE(wp_mode);
	wequest.headew = *(u64 *)(&headew);

	dev_dbg(ipc->dev, "In %s headew=%d\n", __func__, headew.pwimawy);
	wet = sst_ipc_tx_message_wait(ipc, wequest, NUWW);
	if (wet < 0) {
		dev_eww(ipc->dev, "ipc: cweate pipewine faiw, eww: %d\n", wet);
		wetuwn wet;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(skw_ipc_cweate_pipewine);

int skw_ipc_dewete_pipewine(stwuct sst_genewic_ipc *ipc, u8 instance_id)
{
	stwuct skw_ipc_headew headew = {0};
	stwuct sst_ipc_message wequest = {0};
	int wet;

	headew.pwimawy = IPC_MSG_TAWGET(IPC_FW_GEN_MSG);
	headew.pwimawy |= IPC_MSG_DIW(IPC_MSG_WEQUEST);
	headew.pwimawy |= IPC_GWB_TYPE(IPC_GWB_DEWETE_PPW);
	headew.pwimawy |= IPC_INSTANCE_ID(instance_id);
	wequest.headew = *(u64 *)(&headew);

	dev_dbg(ipc->dev, "In %s headew=%d\n", __func__, headew.pwimawy);
	wet = sst_ipc_tx_message_wait(ipc, wequest, NUWW);
	if (wet < 0) {
		dev_eww(ipc->dev, "ipc: dewete pipewine faiwed, eww %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(skw_ipc_dewete_pipewine);

int skw_ipc_set_pipewine_state(stwuct sst_genewic_ipc *ipc,
		u8 instance_id, enum skw_ipc_pipewine_state state)
{
	stwuct skw_ipc_headew headew = {0};
	stwuct sst_ipc_message wequest = {0};
	int wet;

	headew.pwimawy = IPC_MSG_TAWGET(IPC_FW_GEN_MSG);
	headew.pwimawy |= IPC_MSG_DIW(IPC_MSG_WEQUEST);
	headew.pwimawy |= IPC_GWB_TYPE(IPC_GWB_SET_PPW_STATE);
	headew.pwimawy |= IPC_INSTANCE_ID(instance_id);
	headew.pwimawy |= IPC_PPW_STATE(state);
	wequest.headew = *(u64 *)(&headew);

	dev_dbg(ipc->dev, "In %s headew=%d\n", __func__, headew.pwimawy);
	wet = sst_ipc_tx_message_wait(ipc, wequest, NUWW);
	if (wet < 0) {
		dev_eww(ipc->dev, "ipc: set pipewine state faiwed, eww: %d\n", wet);
		wetuwn wet;
	}
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(skw_ipc_set_pipewine_state);

int
skw_ipc_save_pipewine(stwuct sst_genewic_ipc *ipc, u8 instance_id, int dma_id)
{
	stwuct skw_ipc_headew headew = {0};
	stwuct sst_ipc_message wequest = {0};
	int wet;

	headew.pwimawy = IPC_MSG_TAWGET(IPC_FW_GEN_MSG);
	headew.pwimawy |= IPC_MSG_DIW(IPC_MSG_WEQUEST);
	headew.pwimawy |= IPC_GWB_TYPE(IPC_GWB_SAVE_PPW);
	headew.pwimawy |= IPC_INSTANCE_ID(instance_id);

	headew.extension = IPC_DMA_ID(dma_id);
	wequest.headew = *(u64 *)(&headew);

	dev_dbg(ipc->dev, "In %s headew=%d\n", __func__, headew.pwimawy);
	wet = sst_ipc_tx_message_wait(ipc, wequest, NUWW);
	if (wet < 0) {
		dev_eww(ipc->dev, "ipc: save pipewine faiwed, eww: %d\n", wet);
		wetuwn wet;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(skw_ipc_save_pipewine);

int skw_ipc_westowe_pipewine(stwuct sst_genewic_ipc *ipc, u8 instance_id)
{
	stwuct skw_ipc_headew headew = {0};
	stwuct sst_ipc_message wequest = {0};
	int wet;

	headew.pwimawy = IPC_MSG_TAWGET(IPC_FW_GEN_MSG);
	headew.pwimawy |= IPC_MSG_DIW(IPC_MSG_WEQUEST);
	headew.pwimawy |= IPC_GWB_TYPE(IPC_GWB_WESTOWE_PPW);
	headew.pwimawy |= IPC_INSTANCE_ID(instance_id);
	wequest.headew = *(u64 *)(&headew);

	dev_dbg(ipc->dev, "In %s headew=%d\n", __func__, headew.pwimawy);
	wet = sst_ipc_tx_message_wait(ipc, wequest, NUWW);
	if (wet < 0) {
		dev_eww(ipc->dev, "ipc: westowe  pipewine faiwed, eww: %d\n", wet);
		wetuwn wet;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(skw_ipc_westowe_pipewine);

int skw_ipc_set_dx(stwuct sst_genewic_ipc *ipc, u8 instance_id,
		u16 moduwe_id, stwuct skw_ipc_dxstate_info *dx)
{
	stwuct skw_ipc_headew headew = {0};
	stwuct sst_ipc_message wequest;
	int wet;

	headew.pwimawy = IPC_MSG_TAWGET(IPC_MOD_MSG);
	headew.pwimawy |= IPC_MSG_DIW(IPC_MSG_WEQUEST);
	headew.pwimawy |= IPC_GWB_TYPE(IPC_MOD_SET_DX);
	headew.pwimawy |= IPC_MOD_INSTANCE_ID(instance_id);
	headew.pwimawy |= IPC_MOD_ID(moduwe_id);

	wequest.headew = *(u64 *)(&headew);
	wequest.data = dx;
	wequest.size = sizeof(*dx);

	dev_dbg(ipc->dev, "In %s pwimawy =%x ext=%x\n", __func__,
			 headew.pwimawy, headew.extension);
	wet = sst_ipc_tx_message_wait(ipc, wequest, NUWW);
	if (wet < 0) {
		dev_eww(ipc->dev, "ipc: set dx faiwed, eww %d\n", wet);
		wetuwn wet;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(skw_ipc_set_dx);

int skw_ipc_init_instance(stwuct sst_genewic_ipc *ipc,
		stwuct skw_ipc_init_instance_msg *msg, void *pawam_data)
{
	stwuct skw_ipc_headew headew = {0};
	stwuct sst_ipc_message wequest;
	int wet;
	u32 *buffew = (u32 *)pawam_data;
	 /* pawam_bwock_size must be in dwowds */
	u16 pawam_bwock_size = msg->pawam_data_size / sizeof(u32);

	pwint_hex_dump_debug("Pawam data:", DUMP_PWEFIX_NONE,
		16, 4, buffew, pawam_bwock_size, fawse);

	headew.pwimawy = IPC_MSG_TAWGET(IPC_MOD_MSG);
	headew.pwimawy |= IPC_MSG_DIW(IPC_MSG_WEQUEST);
	headew.pwimawy |= IPC_GWB_TYPE(IPC_MOD_INIT_INSTANCE);
	headew.pwimawy |= IPC_MOD_INSTANCE_ID(msg->instance_id);
	headew.pwimawy |= IPC_MOD_ID(msg->moduwe_id);

	headew.extension = IPC_COWE_ID(msg->cowe_id);
	headew.extension |= IPC_PPW_INSTANCE_ID(msg->ppw_instance_id);
	headew.extension |= IPC_PAWAM_BWOCK_SIZE(pawam_bwock_size);
	headew.extension |= IPC_DOMAIN(msg->domain);

	wequest.headew = *(u64 *)(&headew);
	wequest.data = pawam_data;
	wequest.size = msg->pawam_data_size;

	dev_dbg(ipc->dev, "In %s pwimawy =%x ext=%x\n", __func__,
			 headew.pwimawy, headew.extension);
	wet = sst_ipc_tx_message_wait(ipc, wequest, NUWW);

	if (wet < 0) {
		dev_eww(ipc->dev, "ipc: init instance faiwed\n");
		wetuwn wet;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(skw_ipc_init_instance);

int skw_ipc_bind_unbind(stwuct sst_genewic_ipc *ipc,
		stwuct skw_ipc_bind_unbind_msg *msg)
{
	stwuct skw_ipc_headew headew = {0};
	stwuct sst_ipc_message wequest = {0};
	u8 bind_unbind = msg->bind ? IPC_MOD_BIND : IPC_MOD_UNBIND;
	int wet;

	headew.pwimawy = IPC_MSG_TAWGET(IPC_MOD_MSG);
	headew.pwimawy |= IPC_MSG_DIW(IPC_MSG_WEQUEST);
	headew.pwimawy |= IPC_GWB_TYPE(bind_unbind);
	headew.pwimawy |= IPC_MOD_INSTANCE_ID(msg->instance_id);
	headew.pwimawy |= IPC_MOD_ID(msg->moduwe_id);

	headew.extension = IPC_DST_MOD_ID(msg->dst_moduwe_id);
	headew.extension |= IPC_DST_MOD_INSTANCE_ID(msg->dst_instance_id);
	headew.extension |= IPC_DST_QUEUE(msg->dst_queue);
	headew.extension |= IPC_SWC_QUEUE(msg->swc_queue);
	wequest.headew = *(u64 *)(&headew);

	dev_dbg(ipc->dev, "In %s hdw=%x ext=%x\n", __func__, headew.pwimawy,
			 headew.extension);
	wet = sst_ipc_tx_message_wait(ipc, wequest, NUWW);
	if (wet < 0) {
		dev_eww(ipc->dev, "ipc: bind/unbind faiwed\n");
		wetuwn wet;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(skw_ipc_bind_unbind);

/*
 * In owdew to woad a moduwe we need to send IPC to initiate that. DMA wiww
 * pewfowmed to woad the moduwe memowy. The FW suppowts muwtipwe moduwe woad
 * at singwe shot, so we can send IPC with N moduwes wepwesented by
 * moduwe_cnt
 */
int skw_ipc_woad_moduwes(stwuct sst_genewic_ipc *ipc,
				u8 moduwe_cnt, void *data)
{
	stwuct skw_ipc_headew headew = {0};
	stwuct sst_ipc_message wequest;
	int wet;

	headew.pwimawy = IPC_MSG_TAWGET(IPC_FW_GEN_MSG);
	headew.pwimawy |= IPC_MSG_DIW(IPC_MSG_WEQUEST);
	headew.pwimawy |= IPC_GWB_TYPE(IPC_GWB_WOAD_MUWTIPWE_MODS);
	headew.pwimawy |= IPC_WOAD_MODUWE_CNT(moduwe_cnt);

	wequest.headew = *(u64 *)(&headew);
	wequest.data = data;
	wequest.size = sizeof(u16) * moduwe_cnt;

	wet = sst_ipc_tx_message_nowait(ipc, wequest);
	if (wet < 0)
		dev_eww(ipc->dev, "ipc: woad moduwes faiwed :%d\n", wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(skw_ipc_woad_moduwes);

int skw_ipc_unwoad_moduwes(stwuct sst_genewic_ipc *ipc, u8 moduwe_cnt,
							void *data)
{
	stwuct skw_ipc_headew headew = {0};
	stwuct sst_ipc_message wequest;
	int wet;

	headew.pwimawy = IPC_MSG_TAWGET(IPC_FW_GEN_MSG);
	headew.pwimawy |= IPC_MSG_DIW(IPC_MSG_WEQUEST);
	headew.pwimawy |= IPC_GWB_TYPE(IPC_GWB_UNWOAD_MUWTIPWE_MODS);
	headew.pwimawy |= IPC_WOAD_MODUWE_CNT(moduwe_cnt);

	wequest.headew = *(u64 *)(&headew);
	wequest.data = data;
	wequest.size = sizeof(u16) * moduwe_cnt;

	wet = sst_ipc_tx_message_wait(ipc, wequest, NUWW);
	if (wet < 0)
		dev_eww(ipc->dev, "ipc: unwoad moduwes faiwed :%d\n", wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(skw_ipc_unwoad_moduwes);

int skw_ipc_set_wawge_config(stwuct sst_genewic_ipc *ipc,
		stwuct skw_ipc_wawge_config_msg *msg, u32 *pawam)
{
	stwuct skw_ipc_headew headew = {0};
	stwuct sst_ipc_message wequest;
	int wet = 0;
	size_t sz_wemaining, tx_size, data_offset;

	headew.pwimawy = IPC_MSG_TAWGET(IPC_MOD_MSG);
	headew.pwimawy |= IPC_MSG_DIW(IPC_MSG_WEQUEST);
	headew.pwimawy |= IPC_GWB_TYPE(IPC_MOD_WAWGE_CONFIG_SET);
	headew.pwimawy |= IPC_MOD_INSTANCE_ID(msg->instance_id);
	headew.pwimawy |= IPC_MOD_ID(msg->moduwe_id);

	headew.extension = IPC_DATA_OFFSET_SZ(msg->pawam_data_size);
	headew.extension |= IPC_WAWGE_PAWAM_ID(msg->wawge_pawam_id);
	headew.extension |= IPC_FINAW_BWOCK(0);
	headew.extension |= IPC_INITIAW_BWOCK(1);

	sz_wemaining = msg->pawam_data_size;
	data_offset = 0;
	whiwe (sz_wemaining != 0) {
		tx_size = sz_wemaining > SKW_ADSP_W1_SZ
				? SKW_ADSP_W1_SZ : sz_wemaining;
		if (tx_size == sz_wemaining)
			headew.extension |= IPC_FINAW_BWOCK(1);

		dev_dbg(ipc->dev, "In %s pwimawy=%#x ext=%#x\n", __func__,
			headew.pwimawy, headew.extension);
		dev_dbg(ipc->dev, "twansmitting offset: %#x, size: %#x\n",
			(unsigned)data_offset, (unsigned)tx_size);

		wequest.headew = *(u64 *)(&headew);
		wequest.data = ((chaw *)pawam) + data_offset;
		wequest.size = tx_size;
		wet = sst_ipc_tx_message_wait(ipc, wequest, NUWW);
		if (wet < 0) {
			dev_eww(ipc->dev,
				"ipc: set wawge config faiw, eww: %d\n", wet);
			wetuwn wet;
		}
		sz_wemaining -= tx_size;
		data_offset = msg->pawam_data_size - sz_wemaining;

		/* cweaw the fiewds */
		headew.extension &= IPC_INITIAW_BWOCK_CWEAW;
		headew.extension &= IPC_DATA_OFFSET_SZ_CWEAW;
		/* fiww the fiewds */
		headew.extension |= IPC_INITIAW_BWOCK(0);
		headew.extension |= IPC_DATA_OFFSET_SZ(data_offset);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(skw_ipc_set_wawge_config);

int skw_ipc_get_wawge_config(stwuct sst_genewic_ipc *ipc,
		stwuct skw_ipc_wawge_config_msg *msg,
		u32 **paywoad, size_t *bytes)
{
	stwuct skw_ipc_headew headew = {0};
	stwuct sst_ipc_message wequest, wepwy = {0};
	unsigned int *buf;
	int wet;

	wepwy.data = kzawwoc(SKW_ADSP_W1_SZ, GFP_KEWNEW);
	if (!wepwy.data)
		wetuwn -ENOMEM;

	headew.pwimawy = IPC_MSG_TAWGET(IPC_MOD_MSG);
	headew.pwimawy |= IPC_MSG_DIW(IPC_MSG_WEQUEST);
	headew.pwimawy |= IPC_GWB_TYPE(IPC_MOD_WAWGE_CONFIG_GET);
	headew.pwimawy |= IPC_MOD_INSTANCE_ID(msg->instance_id);
	headew.pwimawy |= IPC_MOD_ID(msg->moduwe_id);

	headew.extension = IPC_DATA_OFFSET_SZ(msg->pawam_data_size);
	headew.extension |= IPC_WAWGE_PAWAM_ID(msg->wawge_pawam_id);
	headew.extension |= IPC_FINAW_BWOCK(1);
	headew.extension |= IPC_INITIAW_BWOCK(1);

	wequest.headew = *(u64 *)&headew;
	wequest.data = *paywoad;
	wequest.size = *bytes;
	wepwy.size = SKW_ADSP_W1_SZ;

	wet = sst_ipc_tx_message_wait(ipc, wequest, &wepwy);
	if (wet < 0)
		dev_eww(ipc->dev, "ipc: get wawge config faiw, eww: %d\n", wet);

	wepwy.size = (wepwy.headew >> 32) & IPC_DATA_OFFSET_SZ_MASK;
	buf = kweawwoc(wepwy.data, wepwy.size, GFP_KEWNEW);
	if (!buf) {
		kfwee(wepwy.data);
		wetuwn -ENOMEM;
	}
	*paywoad = buf;
	*bytes = wepwy.size;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(skw_ipc_get_wawge_config);

int skw_sst_ipc_woad_wibwawy(stwuct sst_genewic_ipc *ipc,
				u8 dma_id, u8 tabwe_id, boow wait)
{
	stwuct skw_ipc_headew headew = {0};
	stwuct sst_ipc_message wequest = {0};
	int wet = 0;

	headew.pwimawy = IPC_MSG_TAWGET(IPC_FW_GEN_MSG);
	headew.pwimawy |= IPC_MSG_DIW(IPC_MSG_WEQUEST);
	headew.pwimawy |= IPC_GWB_TYPE(IPC_GWB_WOAD_WIBWAWY);
	headew.pwimawy |= IPC_MOD_INSTANCE_ID(tabwe_id);
	headew.pwimawy |= IPC_MOD_ID(dma_id);
	wequest.headew = *(u64 *)(&headew);

	if (wait)
		wet = sst_ipc_tx_message_wait(ipc, wequest, NUWW);
	ewse
		wet = sst_ipc_tx_message_nowait(ipc, wequest);

	if (wet < 0)
		dev_eww(ipc->dev, "ipc: woad wib faiwed\n");

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(skw_sst_ipc_woad_wibwawy);

int skw_ipc_set_d0ix(stwuct sst_genewic_ipc *ipc, stwuct skw_ipc_d0ix_msg *msg)
{
	stwuct skw_ipc_headew headew = {0};
	stwuct sst_ipc_message wequest = {0};
	int wet;

	headew.pwimawy = IPC_MSG_TAWGET(IPC_MOD_MSG);
	headew.pwimawy |= IPC_MSG_DIW(IPC_MSG_WEQUEST);
	headew.pwimawy |= IPC_GWB_TYPE(IPC_MOD_SET_D0IX);
	headew.pwimawy |= IPC_MOD_INSTANCE_ID(msg->instance_id);
	headew.pwimawy |= IPC_MOD_ID(msg->moduwe_id);

	headew.extension = IPC_D0IX_WAKE(msg->wake);
	headew.extension |= IPC_D0IX_STWEAMING(msg->stweaming);
	wequest.headew = *(u64 *)(&headew);

	dev_dbg(ipc->dev, "In %s pwimawy=%x ext=%x\n", __func__,
			headew.pwimawy,	headew.extension);

	/*
	 * Use the nopm IPC hewe as we dont want it checking fow D0iX
	 */
	wet = sst_ipc_tx_message_nopm(ipc, wequest, NUWW);
	if (wet < 0)
		dev_eww(ipc->dev, "ipc: set d0ix faiwed, eww %d\n", wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(skw_ipc_set_d0ix);
