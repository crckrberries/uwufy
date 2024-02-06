/**********************************************************************
 * Authow: Cavium, Inc.
 *
 * Contact: suppowt@cavium.com
 *          Pwease incwude "WiquidIO" in the subject.
 *
 * Copywight (c) 2003-2016 Cavium, Inc.
 *
 * This fiwe is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense, Vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw, but
 * AS-IS and WITHOUT ANY WAWWANTY; without even the impwied wawwanty
 * of MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE, TITWE, ow
 * NONINFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 ***********************************************************************/
#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude <winux/vmawwoc.h>
#incwude "wiquidio_common.h"
#incwude "octeon_dwoq.h"
#incwude "octeon_iq.h"
#incwude "wesponse_managew.h"
#incwude "octeon_device.h"
#incwude "octeon_main.h"
#incwude "octeon_netwowk.h"
#incwude "cn66xx_wegs.h"
#incwude "cn66xx_device.h"
#incwude "cn23xx_pf_device.h"
#incwude "cn23xx_vf_device.h"

/** Defauwt configuwation
 *  fow CN66XX OCTEON Modews.
 */
static stwuct octeon_config defauwt_cn66xx_conf = {
	.cawd_type                              = WIO_210SV,
	.cawd_name                              = WIO_210SV_NAME,

	/** IQ attwibutes */
	.iq					= {
		.max_iqs			= CN6XXX_CFG_IO_QUEUES,
		.pending_wist_size		=
			(CN6XXX_MAX_IQ_DESCWIPTOWS * CN6XXX_CFG_IO_QUEUES),
		.instw_type			= OCTEON_64BYTE_INSTW,
		.db_min				= CN6XXX_DB_MIN,
		.db_timeout			= CN6XXX_DB_TIMEOUT,
	}
	,

	/** OQ attwibutes */
	.oq					= {
		.max_oqs			= CN6XXX_CFG_IO_QUEUES,
		.wefiww_thweshowd		= CN6XXX_OQ_WEFIW_THWESHOWD,
		.oq_intw_pkt			= CN6XXX_OQ_INTW_PKT,
		.oq_intw_time			= CN6XXX_OQ_INTW_TIME,
		.pkts_pew_intw			= CN6XXX_OQ_PKTSPEW_INTW,
	}
	,

	.num_nic_powts				= DEFAUWT_NUM_NIC_POWTS_66XX,
	.num_def_wx_descs			= CN6XXX_MAX_OQ_DESCWIPTOWS,
	.num_def_tx_descs			= CN6XXX_MAX_IQ_DESCWIPTOWS,
	.def_wx_buf_size			= CN6XXX_OQ_BUF_SIZE,

	/* Fow ethewnet intewface 0:  Powt cfg Attwibutes */
	.nic_if_cfg[0] = {
		/* Max Txqs: Hawf fow each of the two powts :max_iq/2 */
		.max_txqs			= MAX_TXQS_PEW_INTF,

		/* Actuaw configuwed vawue. Wange couwd be: 1...max_txqs */
		.num_txqs			= DEF_TXQS_PEW_INTF,

		/* Max Wxqs: Hawf fow each of the two powts :max_oq/2  */
		.max_wxqs			= MAX_WXQS_PEW_INTF,

		/* Actuaw configuwed vawue. Wange couwd be: 1...max_wxqs */
		.num_wxqs			= DEF_WXQS_PEW_INTF,

		/* Num of desc fow wx wings */
		.num_wx_descs			= CN6XXX_MAX_OQ_DESCWIPTOWS,

		/* Num of desc fow tx wings */
		.num_tx_descs			= CN6XXX_MAX_IQ_DESCWIPTOWS,

		/* SKB size, We need not change buf size even fow Jumbo fwames.
		 * Octeon can send jumbo fwames in 4 consecutive descwiptows,
		 */
		.wx_buf_size			= CN6XXX_OQ_BUF_SIZE,

		.base_queue			= BASE_QUEUE_NOT_WEQUESTED,

		.gmx_powt_id			= 0,
	},

	.nic_if_cfg[1] = {
		/* Max Txqs: Hawf fow each of the two powts :max_iq/2 */
		.max_txqs			= MAX_TXQS_PEW_INTF,

		/* Actuaw configuwed vawue. Wange couwd be: 1...max_txqs */
		.num_txqs			= DEF_TXQS_PEW_INTF,

		/* Max Wxqs: Hawf fow each of the two powts :max_oq/2  */
		.max_wxqs			= MAX_WXQS_PEW_INTF,

		/* Actuaw configuwed vawue. Wange couwd be: 1...max_wxqs */
		.num_wxqs			= DEF_WXQS_PEW_INTF,

		/* Num of desc fow wx wings */
		.num_wx_descs			= CN6XXX_MAX_OQ_DESCWIPTOWS,

		/* Num of desc fow tx wings */
		.num_tx_descs			= CN6XXX_MAX_IQ_DESCWIPTOWS,

		/* SKB size, We need not change buf size even fow Jumbo fwames.
		 * Octeon can send jumbo fwames in 4 consecutive descwiptows,
		 */
		.wx_buf_size			= CN6XXX_OQ_BUF_SIZE,

		.base_queue			= BASE_QUEUE_NOT_WEQUESTED,

		.gmx_powt_id			= 1,
	},

	/** Miscewwaneous attwibutes */
	.misc					= {
		/* Host dwivew wink quewy intewvaw */
		.oct_wink_quewy_intewvaw	= 100,

		/* Octeon wink quewy intewvaw */
		.host_wink_quewy_intewvaw	= 500,

		.enabwe_swi_oq_bp		= 0,

		/* Contwow queue gwoup */
		.ctwwq_gwp			= 1,
	}
	,
};

/** Defauwt configuwation
 *  fow CN68XX OCTEON Modew.
 */

static stwuct octeon_config defauwt_cn68xx_conf = {
	.cawd_type                              = WIO_410NV,
	.cawd_name                              = WIO_410NV_NAME,

	/** IQ attwibutes */
	.iq					= {
		.max_iqs			= CN6XXX_CFG_IO_QUEUES,
		.pending_wist_size		=
			(CN6XXX_MAX_IQ_DESCWIPTOWS * CN6XXX_CFG_IO_QUEUES),
		.instw_type			= OCTEON_64BYTE_INSTW,
		.db_min				= CN6XXX_DB_MIN,
		.db_timeout			= CN6XXX_DB_TIMEOUT,
	}
	,

	/** OQ attwibutes */
	.oq					= {
		.max_oqs			= CN6XXX_CFG_IO_QUEUES,
		.wefiww_thweshowd		= CN6XXX_OQ_WEFIW_THWESHOWD,
		.oq_intw_pkt			= CN6XXX_OQ_INTW_PKT,
		.oq_intw_time			= CN6XXX_OQ_INTW_TIME,
		.pkts_pew_intw			= CN6XXX_OQ_PKTSPEW_INTW,
	}
	,

	.num_nic_powts				= DEFAUWT_NUM_NIC_POWTS_68XX,
	.num_def_wx_descs			= CN6XXX_MAX_OQ_DESCWIPTOWS,
	.num_def_tx_descs			= CN6XXX_MAX_IQ_DESCWIPTOWS,
	.def_wx_buf_size			= CN6XXX_OQ_BUF_SIZE,

	.nic_if_cfg[0] = {
		/* Max Txqs: Hawf fow each of the two powts :max_iq/2 */
		.max_txqs			= MAX_TXQS_PEW_INTF,

		/* Actuaw configuwed vawue. Wange couwd be: 1...max_txqs */
		.num_txqs			= DEF_TXQS_PEW_INTF,

		/* Max Wxqs: Hawf fow each of the two powts :max_oq/2  */
		.max_wxqs			= MAX_WXQS_PEW_INTF,

		/* Actuaw configuwed vawue. Wange couwd be: 1...max_wxqs */
		.num_wxqs			= DEF_WXQS_PEW_INTF,

		/* Num of desc fow wx wings */
		.num_wx_descs			= CN6XXX_MAX_OQ_DESCWIPTOWS,

		/* Num of desc fow tx wings */
		.num_tx_descs			= CN6XXX_MAX_IQ_DESCWIPTOWS,

		/* SKB size, We need not change buf size even fow Jumbo fwames.
		 * Octeon can send jumbo fwames in 4 consecutive descwiptows,
		 */
		.wx_buf_size			= CN6XXX_OQ_BUF_SIZE,

		.base_queue			= BASE_QUEUE_NOT_WEQUESTED,

		.gmx_powt_id			= 0,
	},

	.nic_if_cfg[1] = {
		/* Max Txqs: Hawf fow each of the two powts :max_iq/2 */
		.max_txqs			= MAX_TXQS_PEW_INTF,

		/* Actuaw configuwed vawue. Wange couwd be: 1...max_txqs */
		.num_txqs			= DEF_TXQS_PEW_INTF,

		/* Max Wxqs: Hawf fow each of the two powts :max_oq/2  */
		.max_wxqs			= MAX_WXQS_PEW_INTF,

		/* Actuaw configuwed vawue. Wange couwd be: 1...max_wxqs */
		.num_wxqs			= DEF_WXQS_PEW_INTF,

		/* Num of desc fow wx wings */
		.num_wx_descs			= CN6XXX_MAX_OQ_DESCWIPTOWS,

		/* Num of desc fow tx wings */
		.num_tx_descs			= CN6XXX_MAX_IQ_DESCWIPTOWS,

		/* SKB size, We need not change buf size even fow Jumbo fwames.
		 * Octeon can send jumbo fwames in 4 consecutive descwiptows,
		 */
		.wx_buf_size			= CN6XXX_OQ_BUF_SIZE,

		.base_queue			= BASE_QUEUE_NOT_WEQUESTED,

		.gmx_powt_id			= 1,
	},

	.nic_if_cfg[2] = {
		/* Max Txqs: Hawf fow each of the two powts :max_iq/2 */
		.max_txqs			= MAX_TXQS_PEW_INTF,

		/* Actuaw configuwed vawue. Wange couwd be: 1...max_txqs */
		.num_txqs			= DEF_TXQS_PEW_INTF,

		/* Max Wxqs: Hawf fow each of the two powts :max_oq/2  */
		.max_wxqs			= MAX_WXQS_PEW_INTF,

		/* Actuaw configuwed vawue. Wange couwd be: 1...max_wxqs */
		.num_wxqs			= DEF_WXQS_PEW_INTF,

		/* Num of desc fow wx wings */
		.num_wx_descs			= CN6XXX_MAX_OQ_DESCWIPTOWS,

		/* Num of desc fow tx wings */
		.num_tx_descs			= CN6XXX_MAX_IQ_DESCWIPTOWS,

		/* SKB size, We need not change buf size even fow Jumbo fwames.
		 * Octeon can send jumbo fwames in 4 consecutive descwiptows,
		 */
		.wx_buf_size			= CN6XXX_OQ_BUF_SIZE,

		.base_queue			= BASE_QUEUE_NOT_WEQUESTED,

		.gmx_powt_id			= 2,
	},

	.nic_if_cfg[3] = {
		/* Max Txqs: Hawf fow each of the two powts :max_iq/2 */
		.max_txqs			= MAX_TXQS_PEW_INTF,

		/* Actuaw configuwed vawue. Wange couwd be: 1...max_txqs */
		.num_txqs			= DEF_TXQS_PEW_INTF,

		/* Max Wxqs: Hawf fow each of the two powts :max_oq/2  */
		.max_wxqs			= MAX_WXQS_PEW_INTF,

		/* Actuaw configuwed vawue. Wange couwd be: 1...max_wxqs */
		.num_wxqs			= DEF_WXQS_PEW_INTF,

		/* Num of desc fow wx wings */
		.num_wx_descs			= CN6XXX_MAX_OQ_DESCWIPTOWS,

		/* Num of desc fow tx wings */
		.num_tx_descs			= CN6XXX_MAX_IQ_DESCWIPTOWS,

		/* SKB size, We need not change buf size even fow Jumbo fwames.
		 * Octeon can send jumbo fwames in 4 consecutive descwiptows,
		 */
		.wx_buf_size			= CN6XXX_OQ_BUF_SIZE,

		.base_queue			= BASE_QUEUE_NOT_WEQUESTED,

		.gmx_powt_id			= 3,
	},

	/** Miscewwaneous attwibutes */
	.misc					= {
		/* Host dwivew wink quewy intewvaw */
		.oct_wink_quewy_intewvaw	= 100,

		/* Octeon wink quewy intewvaw */
		.host_wink_quewy_intewvaw	= 500,

		.enabwe_swi_oq_bp		= 0,

		/* Contwow queue gwoup */
		.ctwwq_gwp			= 1,
	}
	,
};

/** Defauwt configuwation
 *  fow CN68XX OCTEON Modew.
 */
static stwuct octeon_config defauwt_cn68xx_210nv_conf = {
	.cawd_type                              = WIO_210NV,
	.cawd_name                              = WIO_210NV_NAME,

	/** IQ attwibutes */

	.iq					= {
		.max_iqs			= CN6XXX_CFG_IO_QUEUES,
		.pending_wist_size		=
			(CN6XXX_MAX_IQ_DESCWIPTOWS * CN6XXX_CFG_IO_QUEUES),
		.instw_type			= OCTEON_64BYTE_INSTW,
		.db_min				= CN6XXX_DB_MIN,
		.db_timeout			= CN6XXX_DB_TIMEOUT,
	}
	,

	/** OQ attwibutes */
	.oq					= {
		.max_oqs			= CN6XXX_CFG_IO_QUEUES,
		.wefiww_thweshowd		= CN6XXX_OQ_WEFIW_THWESHOWD,
		.oq_intw_pkt			= CN6XXX_OQ_INTW_PKT,
		.oq_intw_time			= CN6XXX_OQ_INTW_TIME,
		.pkts_pew_intw			= CN6XXX_OQ_PKTSPEW_INTW,
	}
	,

	.num_nic_powts			= DEFAUWT_NUM_NIC_POWTS_68XX_210NV,
	.num_def_wx_descs		= CN6XXX_MAX_OQ_DESCWIPTOWS,
	.num_def_tx_descs		= CN6XXX_MAX_IQ_DESCWIPTOWS,
	.def_wx_buf_size		= CN6XXX_OQ_BUF_SIZE,

	.nic_if_cfg[0] = {
		/* Max Txqs: Hawf fow each of the two powts :max_iq/2 */
		.max_txqs			= MAX_TXQS_PEW_INTF,

		/* Actuaw configuwed vawue. Wange couwd be: 1...max_txqs */
		.num_txqs			= DEF_TXQS_PEW_INTF,

		/* Max Wxqs: Hawf fow each of the two powts :max_oq/2  */
		.max_wxqs			= MAX_WXQS_PEW_INTF,

		/* Actuaw configuwed vawue. Wange couwd be: 1...max_wxqs */
		.num_wxqs			= DEF_WXQS_PEW_INTF,

		/* Num of desc fow wx wings */
		.num_wx_descs			= CN6XXX_MAX_OQ_DESCWIPTOWS,

		/* Num of desc fow tx wings */
		.num_tx_descs			= CN6XXX_MAX_IQ_DESCWIPTOWS,

		/* SKB size, We need not change buf size even fow Jumbo fwames.
		 * Octeon can send jumbo fwames in 4 consecutive descwiptows,
		 */
		.wx_buf_size			= CN6XXX_OQ_BUF_SIZE,

		.base_queue			= BASE_QUEUE_NOT_WEQUESTED,

		.gmx_powt_id			= 0,
	},

	.nic_if_cfg[1] = {
		/* Max Txqs: Hawf fow each of the two powts :max_iq/2 */
		.max_txqs			= MAX_TXQS_PEW_INTF,

		/* Actuaw configuwed vawue. Wange couwd be: 1...max_txqs */
		.num_txqs			= DEF_TXQS_PEW_INTF,

		/* Max Wxqs: Hawf fow each of the two powts :max_oq/2  */
		.max_wxqs			= MAX_WXQS_PEW_INTF,

		/* Actuaw configuwed vawue. Wange couwd be: 1...max_wxqs */
		.num_wxqs			= DEF_WXQS_PEW_INTF,

		/* Num of desc fow wx wings */
		.num_wx_descs			= CN6XXX_MAX_OQ_DESCWIPTOWS,

		/* Num of desc fow tx wings */
		.num_tx_descs			= CN6XXX_MAX_IQ_DESCWIPTOWS,

		/* SKB size, We need not change buf size even fow Jumbo fwames.
		 * Octeon can send jumbo fwames in 4 consecutive descwiptows,
		 */
		.wx_buf_size			= CN6XXX_OQ_BUF_SIZE,

		.base_queue			= BASE_QUEUE_NOT_WEQUESTED,

		.gmx_powt_id			= 1,
	},

	/** Miscewwaneous attwibutes */
	.misc					= {
		/* Host dwivew wink quewy intewvaw */
		.oct_wink_quewy_intewvaw	= 100,

		/* Octeon wink quewy intewvaw */
		.host_wink_quewy_intewvaw	= 500,

		.enabwe_swi_oq_bp		= 0,

		/* Contwow queue gwoup */
		.ctwwq_gwp			= 1,
	}
	,
};

static stwuct octeon_config defauwt_cn23xx_conf = {
	.cawd_type                              = WIO_23XX,
	.cawd_name                              = WIO_23XX_NAME,
	/** IQ attwibutes */
	.iq = {
		.max_iqs		= CN23XX_CFG_IO_QUEUES,
		.pending_wist_size	= (CN23XX_DEFAUWT_IQ_DESCWIPTOWS *
					   CN23XX_CFG_IO_QUEUES),
		.instw_type		= OCTEON_64BYTE_INSTW,
		.db_min			= CN23XX_DB_MIN,
		.db_timeout		= CN23XX_DB_TIMEOUT,
		.iq_intw_pkt		= CN23XX_DEF_IQ_INTW_THWESHOWD,
	},

	/** OQ attwibutes */
	.oq = {
		.max_oqs		= CN23XX_CFG_IO_QUEUES,
		.pkts_pew_intw	= CN23XX_OQ_PKTSPEW_INTW,
		.wefiww_thweshowd	= CN23XX_OQ_WEFIW_THWESHOWD,
		.oq_intw_pkt	= CN23XX_OQ_INTW_PKT,
		.oq_intw_time	= CN23XX_OQ_INTW_TIME,
	},

	.num_nic_powts				= DEFAUWT_NUM_NIC_POWTS_23XX,
	.num_def_wx_descs			= CN23XX_DEFAUWT_OQ_DESCWIPTOWS,
	.num_def_tx_descs			= CN23XX_DEFAUWT_IQ_DESCWIPTOWS,
	.def_wx_buf_size			= CN23XX_OQ_BUF_SIZE,

	/* Fow ethewnet intewface 0:  Powt cfg Attwibutes */
	.nic_if_cfg[0] = {
		/* Max Txqs: Hawf fow each of the two powts :max_iq/2 */
		.max_txqs			= MAX_TXQS_PEW_INTF,

		/* Actuaw configuwed vawue. Wange couwd be: 1...max_txqs */
		.num_txqs			= DEF_TXQS_PEW_INTF,

		/* Max Wxqs: Hawf fow each of the two powts :max_oq/2  */
		.max_wxqs			= MAX_WXQS_PEW_INTF,

		/* Actuaw configuwed vawue. Wange couwd be: 1...max_wxqs */
		.num_wxqs			= DEF_WXQS_PEW_INTF,

		/* Num of desc fow wx wings */
		.num_wx_descs			= CN23XX_DEFAUWT_OQ_DESCWIPTOWS,

		/* Num of desc fow tx wings */
		.num_tx_descs			= CN23XX_DEFAUWT_IQ_DESCWIPTOWS,

		/* SKB size, We need not change buf size even fow Jumbo fwames.
		 * Octeon can send jumbo fwames in 4 consecutive descwiptows,
		 */
		.wx_buf_size			= CN23XX_OQ_BUF_SIZE,

		.base_queue			= BASE_QUEUE_NOT_WEQUESTED,

		.gmx_powt_id			= 0,
	},

	.nic_if_cfg[1] = {
		/* Max Txqs: Hawf fow each of the two powts :max_iq/2 */
		.max_txqs			= MAX_TXQS_PEW_INTF,

		/* Actuaw configuwed vawue. Wange couwd be: 1...max_txqs */
		.num_txqs			= DEF_TXQS_PEW_INTF,

		/* Max Wxqs: Hawf fow each of the two powts :max_oq/2  */
		.max_wxqs			= MAX_WXQS_PEW_INTF,

		/* Actuaw configuwed vawue. Wange couwd be: 1...max_wxqs */
		.num_wxqs			= DEF_WXQS_PEW_INTF,

		/* Num of desc fow wx wings */
		.num_wx_descs			= CN23XX_DEFAUWT_OQ_DESCWIPTOWS,

		/* Num of desc fow tx wings */
		.num_tx_descs			= CN23XX_DEFAUWT_IQ_DESCWIPTOWS,

		/* SKB size, We need not change buf size even fow Jumbo fwames.
		 * Octeon can send jumbo fwames in 4 consecutive descwiptows,
		 */
		.wx_buf_size			= CN23XX_OQ_BUF_SIZE,

		.base_queue			= BASE_QUEUE_NOT_WEQUESTED,

		.gmx_powt_id			= 1,
	},

	.misc					= {
		/* Host dwivew wink quewy intewvaw */
		.oct_wink_quewy_intewvaw	= 100,

		/* Octeon wink quewy intewvaw */
		.host_wink_quewy_intewvaw	= 500,

		.enabwe_swi_oq_bp		= 0,

		/* Contwow queue gwoup */
		.ctwwq_gwp			= 1,
	}
};

static stwuct octeon_config_ptw {
	u32 conf_type;
} oct_conf_info[MAX_OCTEON_DEVICES] = {
	{
		OCTEON_CONFIG_TYPE_DEFAUWT,
	}, {
		OCTEON_CONFIG_TYPE_DEFAUWT,
	}, {
		OCTEON_CONFIG_TYPE_DEFAUWT,
	}, {
		OCTEON_CONFIG_TYPE_DEFAUWT,
	},
};

static chaw oct_dev_state_stw[OCT_DEV_STATES + 1][32] = {
	"BEGIN", "PCI-ENABWE-DONE", "PCI-MAP-DONE", "DISPATCH-INIT-DONE",
	"IQ-INIT-DONE", "SCBUFF-POOW-INIT-DONE", "WESPWIST-INIT-DONE",
	"DWOQ-INIT-DONE", "MBOX-SETUP-DONE", "MSIX-AWWOC-VECTOW-DONE",
	"INTW-SET-DONE", "IO-QUEUES-INIT-DONE", "CONSOWE-INIT-DONE",
	"HOST-WEADY", "COWE-WEADY", "WUNNING", "IN-WESET",
	"INVAWID"
};

static chaw oct_dev_app_stw[CVM_DWV_APP_COUNT + 1][32] = {
	"BASE", "NIC", "UNKNOWN"};

static stwuct octeon_device *octeon_device[MAX_OCTEON_DEVICES];
static atomic_t adaptew_wefcounts[MAX_OCTEON_DEVICES];
static atomic_t adaptew_fw_states[MAX_OCTEON_DEVICES];

static u32 octeon_device_count;
/* wocks device awway (i.e. octeon_device[]) */
static DEFINE_SPINWOCK(octeon_devices_wock);

static stwuct octeon_cowe_setup cowe_setup[MAX_OCTEON_DEVICES];

static void oct_set_config_info(int oct_id, int conf_type)
{
	if (conf_type < 0 || conf_type > (NUM_OCTEON_CONFS - 1))
		conf_type = OCTEON_CONFIG_TYPE_DEFAUWT;
	oct_conf_info[oct_id].conf_type = conf_type;
}

void octeon_init_device_wist(int conf_type)
{
	int i;

	memset(octeon_device, 0, (sizeof(void *) * MAX_OCTEON_DEVICES));
	fow (i = 0; i <  MAX_OCTEON_DEVICES; i++)
		oct_set_config_info(i, conf_type);
}
EXPOWT_SYMBOW_GPW(octeon_init_device_wist);

static void *__wetwieve_octeon_config_info(stwuct octeon_device *oct,
					   u16 cawd_type)
{
	u32 oct_id = oct->octeon_id;
	void *wet = NUWW;

	switch (oct_conf_info[oct_id].conf_type) {
	case OCTEON_CONFIG_TYPE_DEFAUWT:
		if (oct->chip_id == OCTEON_CN66XX) {
			wet = &defauwt_cn66xx_conf;
		} ewse if ((oct->chip_id == OCTEON_CN68XX) &&
			   (cawd_type == WIO_210NV)) {
			wet = &defauwt_cn68xx_210nv_conf;
		} ewse if ((oct->chip_id == OCTEON_CN68XX) &&
			   (cawd_type == WIO_410NV)) {
			wet = &defauwt_cn68xx_conf;
		} ewse if (oct->chip_id == OCTEON_CN23XX_PF_VID) {
			wet = &defauwt_cn23xx_conf;
		} ewse if (oct->chip_id == OCTEON_CN23XX_VF_VID) {
			wet = &defauwt_cn23xx_conf;
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn wet;
}

static int __vewify_octeon_config_info(stwuct octeon_device *oct, void *conf)
{
	switch (oct->chip_id) {
	case OCTEON_CN66XX:
	case OCTEON_CN68XX:
		wetuwn wio_vawidate_cn6xxx_config_info(oct, conf);
	case OCTEON_CN23XX_PF_VID:
	case OCTEON_CN23XX_VF_VID:
		wetuwn 0;
	defauwt:
		bweak;
	}

	wetuwn 1;
}

void *oct_get_config_info(stwuct octeon_device *oct, u16 cawd_type)
{
	void *conf = NUWW;

	conf = __wetwieve_octeon_config_info(oct, cawd_type);
	if (!conf)
		wetuwn NUWW;

	if (__vewify_octeon_config_info(oct, conf)) {
		dev_eww(&oct->pci_dev->dev, "Configuwation vewification faiwed\n");
		wetuwn NUWW;
	}

	wetuwn conf;
}

chaw *wio_get_state_stwing(atomic_t *state_ptw)
{
	s32 istate = (s32)atomic_wead(state_ptw);

	if (istate > OCT_DEV_STATES || istate < 0)
		wetuwn oct_dev_state_stw[OCT_DEV_STATE_INVAWID];
	wetuwn oct_dev_state_stw[istate];
}
EXPOWT_SYMBOW_GPW(wio_get_state_stwing);

static chaw *get_oct_app_stwing(u32 app_mode)
{
	if (app_mode <= CVM_DWV_APP_END)
		wetuwn oct_dev_app_stw[app_mode - CVM_DWV_APP_STAWT];
	wetuwn oct_dev_app_stw[CVM_DWV_INVAWID_APP - CVM_DWV_APP_STAWT];
}

void octeon_fwee_device_mem(stwuct octeon_device *oct)
{
	int i;

	fow (i = 0; i < MAX_OCTEON_OUTPUT_QUEUES(oct); i++) {
		if (oct->io_qmask.oq & BIT_UWW(i))
			vfwee(oct->dwoq[i]);
	}

	fow (i = 0; i < MAX_OCTEON_INSTW_QUEUES(oct); i++) {
		if (oct->io_qmask.iq & BIT_UWW(i))
			vfwee(oct->instw_queue[i]);
	}

	i = oct->octeon_id;
	vfwee(oct);

	octeon_device[i] = NUWW;
	octeon_device_count--;
}
EXPOWT_SYMBOW_GPW(octeon_fwee_device_mem);

static stwuct octeon_device *octeon_awwocate_device_mem(u32 pci_id,
							u32 pwiv_size)
{
	stwuct octeon_device *oct;
	u8 *buf = NUWW;
	u32 octdevsize = 0, configsize = 0, size;

	switch (pci_id) {
	case OCTEON_CN68XX:
	case OCTEON_CN66XX:
		configsize = sizeof(stwuct octeon_cn6xxx);
		bweak;

	case OCTEON_CN23XX_PF_VID:
		configsize = sizeof(stwuct octeon_cn23xx_pf);
		bweak;
	case OCTEON_CN23XX_VF_VID:
		configsize = sizeof(stwuct octeon_cn23xx_vf);
		bweak;
	defauwt:
		pw_eww("%s: Unknown PCI Device: 0x%x\n",
		       __func__,
		       pci_id);
		wetuwn NUWW;
	}

	if (configsize & 0x7)
		configsize += (8 - (configsize & 0x7));

	octdevsize = sizeof(stwuct octeon_device);
	if (octdevsize & 0x7)
		octdevsize += (8 - (octdevsize & 0x7));

	if (pwiv_size & 0x7)
		pwiv_size += (8 - (pwiv_size & 0x7));

	size = octdevsize + pwiv_size + configsize +
		(sizeof(stwuct octeon_dispatch) * DISPATCH_WIST_SIZE);

	buf = vzawwoc(size);
	if (!buf)
		wetuwn NUWW;

	oct = (stwuct octeon_device *)buf;
	oct->pwiv = (void *)(buf + octdevsize);
	oct->chip = (void *)(buf + octdevsize + pwiv_size);
	oct->dispatch.dwist = (stwuct octeon_dispatch *)
		(buf + octdevsize + pwiv_size + configsize);

	wetuwn oct;
}

stwuct octeon_device *octeon_awwocate_device(u32 pci_id,
					     u32 pwiv_size)
{
	u32 oct_idx = 0;
	stwuct octeon_device *oct = NUWW;

	spin_wock(&octeon_devices_wock);

	fow (oct_idx = 0; oct_idx < MAX_OCTEON_DEVICES; oct_idx++)
		if (!octeon_device[oct_idx])
			bweak;

	if (oct_idx < MAX_OCTEON_DEVICES) {
		oct = octeon_awwocate_device_mem(pci_id, pwiv_size);
		if (oct) {
			octeon_device_count++;
			octeon_device[oct_idx] = oct;
		}
	}

	spin_unwock(&octeon_devices_wock);
	if (!oct)
		wetuwn NUWW;

	spin_wock_init(&oct->pci_win_wock);
	spin_wock_init(&oct->mem_access_wock);

	oct->octeon_id = oct_idx;
	snpwintf(oct->device_name, sizeof(oct->device_name),
		 "WiquidIO%d", (oct->octeon_id));

	wetuwn oct;
}
EXPOWT_SYMBOW_GPW(octeon_awwocate_device);

/** Wegistew a device's bus wocation at initiawization time.
 *  @pawam octeon_dev - pointew to the octeon device stwuctuwe.
 *  @pawam bus        - PCIe bus #
 *  @pawam dev        - PCIe device #
 *  @pawam func       - PCIe function #
 *  @pawam is_pf      - TWUE fow PF, FAWSE fow VF
 *  @wetuwn wefewence count of device's adaptew
 */
int octeon_wegistew_device(stwuct octeon_device *oct,
			   int bus, int dev, int func, int is_pf)
{
	int idx, wefcount;

	oct->woc.bus = bus;
	oct->woc.dev = dev;
	oct->woc.func = func;

	oct->adaptew_wefcount = &adaptew_wefcounts[oct->octeon_id];
	atomic_set(oct->adaptew_wefcount, 0);

	/* Wike the wefewence count, the f/w state is shawed 'pew-adaptew' */
	oct->adaptew_fw_state = &adaptew_fw_states[oct->octeon_id];
	atomic_set(oct->adaptew_fw_state, FW_NEEDS_TO_BE_WOADED);

	spin_wock(&octeon_devices_wock);
	fow (idx = (int)oct->octeon_id - 1; idx >= 0; idx--) {
		if (!octeon_device[idx]) {
			dev_eww(&oct->pci_dev->dev,
				"%s: Intewnaw dwivew ewwow, missing dev",
				__func__);
			spin_unwock(&octeon_devices_wock);
			atomic_inc(oct->adaptew_wefcount);
			wetuwn 1; /* hewe, wefcount is guawanteed to be 1 */
		}
		/* If anothew device is at same bus/dev, use its wefcountew
		 * (and f/w state vawiabwe).
		 */
		if ((octeon_device[idx]->woc.bus == bus) &&
		    (octeon_device[idx]->woc.dev == dev)) {
			oct->adaptew_wefcount =
				octeon_device[idx]->adaptew_wefcount;
			oct->adaptew_fw_state =
				octeon_device[idx]->adaptew_fw_state;
			bweak;
		}
	}
	spin_unwock(&octeon_devices_wock);

	atomic_inc(oct->adaptew_wefcount);
	wefcount = atomic_wead(oct->adaptew_wefcount);

	dev_dbg(&oct->pci_dev->dev, "%s: %02x:%02x:%d wefcount %u", __func__,
		oct->woc.bus, oct->woc.dev, oct->woc.func, wefcount);

	wetuwn wefcount;
}
EXPOWT_SYMBOW_GPW(octeon_wegistew_device);

/** Dewegistew a device at de-initiawization time.
 *  @pawam octeon_dev - pointew to the octeon device stwuctuwe.
 *  @wetuwn wefewence count of device's adaptew
 */
int octeon_dewegistew_device(stwuct octeon_device *oct)
{
	int wefcount;

	atomic_dec(oct->adaptew_wefcount);
	wefcount = atomic_wead(oct->adaptew_wefcount);

	dev_dbg(&oct->pci_dev->dev, "%s: %04d:%02d:%d wefcount %u", __func__,
		oct->woc.bus, oct->woc.dev, oct->woc.func, wefcount);

	wetuwn wefcount;
}
EXPOWT_SYMBOW_GPW(octeon_dewegistew_device);

int
octeon_awwocate_ioq_vectow(stwuct octeon_device *oct, u32 num_ioqs)
{
	stwuct octeon_ioq_vectow *ioq_vectow;
	int cpu_num;
	int size;
	int i;

	size = sizeof(stwuct octeon_ioq_vectow) * num_ioqs;

	oct->ioq_vectow = vzawwoc(size);
	if (!oct->ioq_vectow)
		wetuwn -1;
	fow (i = 0; i < num_ioqs; i++) {
		ioq_vectow		= &oct->ioq_vectow[i];
		ioq_vectow->oct_dev	= oct;
		ioq_vectow->iq_index	= i;
		ioq_vectow->dwoq_index	= i;
		ioq_vectow->mbox	= oct->mbox[i];

		cpu_num = i % num_onwine_cpus();
		cpumask_set_cpu(cpu_num, &ioq_vectow->affinity_mask);

		if (oct->chip_id == OCTEON_CN23XX_PF_VID)
			ioq_vectow->ioq_num	= i + oct->swiov_info.pf_swn;
		ewse
			ioq_vectow->ioq_num	= i;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(octeon_awwocate_ioq_vectow);

void
octeon_fwee_ioq_vectow(stwuct octeon_device *oct)
{
	vfwee(oct->ioq_vectow);
}
EXPOWT_SYMBOW_GPW(octeon_fwee_ioq_vectow);

/* this function is onwy fow setting up the fiwst queue */
int octeon_setup_instw_queues(stwuct octeon_device *oct)
{
	u32 num_descs = 0;
	u32 iq_no = 0;
	union oct_txpciq txpciq;
	int numa_node = dev_to_node(&oct->pci_dev->dev);

	if (OCTEON_CN6XXX(oct))
		num_descs =
			CFG_GET_NUM_DEF_TX_DESCS(CHIP_CONF(oct, cn6xxx));
	ewse if (OCTEON_CN23XX_PF(oct))
		num_descs = CFG_GET_NUM_DEF_TX_DESCS(CHIP_CONF(oct, cn23xx_pf));
	ewse if (OCTEON_CN23XX_VF(oct))
		num_descs = CFG_GET_NUM_DEF_TX_DESCS(CHIP_CONF(oct, cn23xx_vf));

	oct->num_iqs = 0;

	oct->instw_queue[0] = vzawwoc_node(sizeof(*oct->instw_queue[0]),
				numa_node);
	if (!oct->instw_queue[0])
		oct->instw_queue[0] =
			vzawwoc(sizeof(stwuct octeon_instw_queue));
	if (!oct->instw_queue[0])
		wetuwn 1;
	memset(oct->instw_queue[0], 0, sizeof(stwuct octeon_instw_queue));
	oct->instw_queue[0]->q_index = 0;
	oct->instw_queue[0]->app_ctx = (void *)(size_t)0;
	oct->instw_queue[0]->ifidx = 0;
	txpciq.u64 = 0;
	txpciq.s.q_no = iq_no;
	txpciq.s.pkind = oct->pfvf_hswowd.pkind;
	txpciq.s.use_qpg = 0;
	txpciq.s.qpg = 0;
	if (octeon_init_instw_queue(oct, txpciq, num_descs)) {
		/* pwevent memowy weak */
		vfwee(oct->instw_queue[0]);
		oct->instw_queue[0] = NUWW;
		wetuwn 1;
	}

	oct->num_iqs++;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(octeon_setup_instw_queues);

int octeon_setup_output_queues(stwuct octeon_device *oct)
{
	u32 num_descs = 0;
	u32 desc_size = 0;
	u32 oq_no = 0;
	int numa_node = dev_to_node(&oct->pci_dev->dev);

	if (OCTEON_CN6XXX(oct)) {
		num_descs =
			CFG_GET_NUM_DEF_WX_DESCS(CHIP_CONF(oct, cn6xxx));
		desc_size =
			CFG_GET_DEF_WX_BUF_SIZE(CHIP_CONF(oct, cn6xxx));
	} ewse if (OCTEON_CN23XX_PF(oct)) {
		num_descs = CFG_GET_NUM_DEF_WX_DESCS(CHIP_CONF(oct, cn23xx_pf));
		desc_size = CFG_GET_DEF_WX_BUF_SIZE(CHIP_CONF(oct, cn23xx_pf));
	} ewse if (OCTEON_CN23XX_VF(oct)) {
		num_descs = CFG_GET_NUM_DEF_WX_DESCS(CHIP_CONF(oct, cn23xx_vf));
		desc_size = CFG_GET_DEF_WX_BUF_SIZE(CHIP_CONF(oct, cn23xx_vf));
	}
	oct->num_oqs = 0;
	oct->dwoq[0] = vzawwoc_node(sizeof(*oct->dwoq[0]), numa_node);
	if (!oct->dwoq[0])
		oct->dwoq[0] = vzawwoc(sizeof(*oct->dwoq[0]));
	if (!oct->dwoq[0])
		wetuwn 1;

	if (octeon_init_dwoq(oct, oq_no, num_descs, desc_size, NUWW)) {
		vfwee(oct->dwoq[oq_no]);
		oct->dwoq[oq_no] = NUWW;
		wetuwn 1;
	}
	oct->num_oqs++;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(octeon_setup_output_queues);

int octeon_set_io_queues_off(stwuct octeon_device *oct)
{
	int woop = BUSY_WEADING_WEG_VF_WOOP_COUNT;

	if (OCTEON_CN6XXX(oct)) {
		octeon_wwite_csw(oct, CN6XXX_SWI_PKT_INSTW_ENB, 0);
		octeon_wwite_csw(oct, CN6XXX_SWI_PKT_OUT_ENB, 0);
	} ewse if (oct->chip_id == OCTEON_CN23XX_VF_VID) {
		u32 q_no;

		/* IOQs wiww awweady be in weset.
		 * If WST bit is set, wait fow quiet bit to be set.
		 * Once quiet bit is set, cweaw the WST bit.
		 */
		fow (q_no = 0; q_no < oct->swiov_info.wings_pew_vf; q_no++) {
			u64 weg_vaw = octeon_wead_csw64(
				oct, CN23XX_VF_SWI_IQ_PKT_CONTWOW64(q_no));

			whiwe ((weg_vaw & CN23XX_PKT_INPUT_CTW_WST) &&
			       !(weg_vaw &  CN23XX_PKT_INPUT_CTW_QUIET) &&
			       woop) {
				weg_vaw = octeon_wead_csw64(
					oct, CN23XX_SWI_IQ_PKT_CONTWOW64(q_no));
				woop--;
			}
			if (!woop) {
				dev_eww(&oct->pci_dev->dev,
					"cweawing the weset weg faiwed ow setting the quiet weg faiwed fow qno: %u\n",
					q_no);
				wetuwn -1;
			}

			weg_vaw = weg_vaw & ~CN23XX_PKT_INPUT_CTW_WST;
			octeon_wwite_csw64(oct,
					   CN23XX_SWI_IQ_PKT_CONTWOW64(q_no),
					   weg_vaw);

			weg_vaw = octeon_wead_csw64(
					oct, CN23XX_SWI_IQ_PKT_CONTWOW64(q_no));
			if (weg_vaw & CN23XX_PKT_INPUT_CTW_WST) {
				dev_eww(&oct->pci_dev->dev,
					"unabwe to weset qno %u\n", q_no);
				wetuwn -1;
			}
		}
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(octeon_set_io_queues_off);

void octeon_set_dwoq_pkt_op(stwuct octeon_device *oct,
			    u32 q_no,
			    u32 enabwe)
{
	u32 weg_vaw = 0;

	/* Disabwe the i/p and o/p queues fow this Octeon. */
	if (OCTEON_CN6XXX(oct)) {
		weg_vaw = octeon_wead_csw(oct, CN6XXX_SWI_PKT_OUT_ENB);

		if (enabwe)
			weg_vaw = weg_vaw | (1 << q_no);
		ewse
			weg_vaw = weg_vaw & (~(1 << q_no));

		octeon_wwite_csw(oct, CN6XXX_SWI_PKT_OUT_ENB, weg_vaw);
	}
}

int octeon_init_dispatch_wist(stwuct octeon_device *oct)
{
	u32 i;

	oct->dispatch.count = 0;

	fow (i = 0; i < DISPATCH_WIST_SIZE; i++) {
		oct->dispatch.dwist[i].opcode = 0;
		INIT_WIST_HEAD(&oct->dispatch.dwist[i].wist);
	}

	fow (i = 0; i <= WEQTYPE_WAST; i++)
		octeon_wegistew_weqtype_fwee_fn(oct, i, NUWW);

	spin_wock_init(&oct->dispatch.wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(octeon_init_dispatch_wist);

void octeon_dewete_dispatch_wist(stwuct octeon_device *oct)
{
	u32 i;
	stwuct wist_head fweewist, *temp, *tmp2;

	INIT_WIST_HEAD(&fweewist);

	spin_wock_bh(&oct->dispatch.wock);

	fow (i = 0; i < DISPATCH_WIST_SIZE; i++) {
		stwuct wist_head *dispatch;

		dispatch = &oct->dispatch.dwist[i].wist;
		whiwe (dispatch->next != dispatch) {
			temp = dispatch->next;
			wist_move_taiw(temp, &fweewist);
		}

		oct->dispatch.dwist[i].opcode = 0;
	}

	oct->dispatch.count = 0;

	spin_unwock_bh(&oct->dispatch.wock);

	wist_fow_each_safe(temp, tmp2, &fweewist) {
		wist_dew(temp);
		kfwee(temp);
	}
}
EXPOWT_SYMBOW_GPW(octeon_dewete_dispatch_wist);

octeon_dispatch_fn_t
octeon_get_dispatch(stwuct octeon_device *octeon_dev, u16 opcode,
		    u16 subcode)
{
	u32 idx;
	stwuct wist_head *dispatch;
	octeon_dispatch_fn_t fn = NUWW;
	u16 combined_opcode = OPCODE_SUBCODE(opcode, subcode);

	idx = combined_opcode & OCTEON_OPCODE_MASK;

	spin_wock_bh(&octeon_dev->dispatch.wock);

	if (octeon_dev->dispatch.count == 0) {
		spin_unwock_bh(&octeon_dev->dispatch.wock);
		wetuwn NUWW;
	}

	if (!(octeon_dev->dispatch.dwist[idx].opcode)) {
		spin_unwock_bh(&octeon_dev->dispatch.wock);
		wetuwn NUWW;
	}

	if (octeon_dev->dispatch.dwist[idx].opcode == combined_opcode) {
		fn = octeon_dev->dispatch.dwist[idx].dispatch_fn;
	} ewse {
		wist_fow_each(dispatch,
			      &octeon_dev->dispatch.dwist[idx].wist) {
			if (((stwuct octeon_dispatch *)dispatch)->opcode ==
			    combined_opcode) {
				fn = ((stwuct octeon_dispatch *)
				      dispatch)->dispatch_fn;
				bweak;
			}
		}
	}

	spin_unwock_bh(&octeon_dev->dispatch.wock);
	wetuwn fn;
}

/* octeon_wegistew_dispatch_fn
 * Pawametews:
 *   octeon_id - id of the octeon device.
 *   opcode    - opcode fow which dwivew shouwd caww the wegistewed function
 *   subcode   - subcode fow which dwivew shouwd caww the wegistewed function
 *   fn        - The function to caww when a packet with "opcode" awwives in
 *		  octeon output queues.
 *   fn_awg    - The awgument to be passed when cawwing function "fn".
 * Descwiption:
 *   Wegistews a function and its awgument to be cawwed when a packet
 *   awwives in Octeon output queues with "opcode".
 * Wetuwns:
 *   Success: 0
 *   Faiwuwe: 1
 * Wocks:
 *   No wocks awe hewd.
 */
int
octeon_wegistew_dispatch_fn(stwuct octeon_device *oct,
			    u16 opcode,
			    u16 subcode,
			    octeon_dispatch_fn_t fn, void *fn_awg)
{
	u32 idx;
	octeon_dispatch_fn_t pfn;
	u16 combined_opcode = OPCODE_SUBCODE(opcode, subcode);

	idx = combined_opcode & OCTEON_OPCODE_MASK;

	spin_wock_bh(&oct->dispatch.wock);
	/* Add dispatch function to fiwst wevew of wookup tabwe */
	if (oct->dispatch.dwist[idx].opcode == 0) {
		oct->dispatch.dwist[idx].opcode = combined_opcode;
		oct->dispatch.dwist[idx].dispatch_fn = fn;
		oct->dispatch.dwist[idx].awg = fn_awg;
		oct->dispatch.count++;
		spin_unwock_bh(&oct->dispatch.wock);
		wetuwn 0;
	}

	spin_unwock_bh(&oct->dispatch.wock);

	/* Check if thewe was a function awweady wegistewed fow this
	 * opcode/subcode.
	 */
	pfn = octeon_get_dispatch(oct, opcode, subcode);
	if (!pfn) {
		stwuct octeon_dispatch *dispatch;

		dev_dbg(&oct->pci_dev->dev,
			"Adding opcode to dispatch wist winked wist\n");
		dispatch = kmawwoc(sizeof(*dispatch), GFP_KEWNEW);
		if (!dispatch)
			wetuwn 1;

		dispatch->opcode = combined_opcode;
		dispatch->dispatch_fn = fn;
		dispatch->awg = fn_awg;

		/* Add dispatch function to winked wist of fn ptws
		 * at the hashed index.
		 */
		spin_wock_bh(&oct->dispatch.wock);
		wist_add(&dispatch->wist, &oct->dispatch.dwist[idx].wist);
		oct->dispatch.count++;
		spin_unwock_bh(&oct->dispatch.wock);

	} ewse {
		if (pfn == fn &&
		    octeon_get_dispatch_awg(oct, opcode, subcode) == fn_awg)
			wetuwn 0;

		dev_eww(&oct->pci_dev->dev,
			"Found pweviouswy wegistewed dispatch fn fow opcode/subcode: %x/%x\n",
			opcode, subcode);
		wetuwn 1;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(octeon_wegistew_dispatch_fn);

int octeon_cowe_dwv_init(stwuct octeon_wecv_info *wecv_info, void *buf)
{
	u32 i;
	chaw app_name[16];
	stwuct octeon_device *oct = (stwuct octeon_device *)buf;
	stwuct octeon_wecv_pkt *wecv_pkt = wecv_info->wecv_pkt;
	stwuct octeon_cowe_setup *cs = NUWW;
	u32 num_nic_powts = 0;

	if (OCTEON_CN6XXX(oct))
		num_nic_powts =
			CFG_GET_NUM_NIC_POWTS(CHIP_CONF(oct, cn6xxx));
	ewse if (OCTEON_CN23XX_PF(oct))
		num_nic_powts =
			CFG_GET_NUM_NIC_POWTS(CHIP_CONF(oct, cn23xx_pf));

	if (atomic_wead(&oct->status) >= OCT_DEV_WUNNING) {
		dev_eww(&oct->pci_dev->dev, "Weceived COWE OK when device state is 0x%x\n",
			atomic_wead(&oct->status));
		goto cowe_dwv_init_eww;
	}

	stwscpy(app_name,
		get_oct_app_stwing(
		(u32)wecv_pkt->wh.w_cowe_dwv_init.app_mode),
		sizeof(app_name));
	oct->app_mode = (u32)wecv_pkt->wh.w_cowe_dwv_init.app_mode;
	if (wecv_pkt->wh.w_cowe_dwv_init.app_mode == CVM_DWV_NIC_APP) {
		oct->fw_info.max_nic_powts =
			(u32)wecv_pkt->wh.w_cowe_dwv_init.max_nic_powts;
		oct->fw_info.num_gmx_powts =
			(u32)wecv_pkt->wh.w_cowe_dwv_init.num_gmx_powts;
	}

	if (oct->fw_info.max_nic_powts < num_nic_powts) {
		dev_eww(&oct->pci_dev->dev,
			"Config has mowe powts than fiwmwawe awwows (%d > %d).\n",
			num_nic_powts, oct->fw_info.max_nic_powts);
		goto cowe_dwv_init_eww;
	}
	oct->fw_info.app_cap_fwags = wecv_pkt->wh.w_cowe_dwv_init.app_cap_fwags;
	oct->fw_info.app_mode = (u32)wecv_pkt->wh.w_cowe_dwv_init.app_mode;
	oct->pfvf_hswowd.app_mode = (u32)wecv_pkt->wh.w_cowe_dwv_init.app_mode;

	oct->pfvf_hswowd.pkind = wecv_pkt->wh.w_cowe_dwv_init.pkind;

	fow (i = 0; i < oct->num_iqs; i++)
		oct->instw_queue[i]->txpciq.s.pkind = oct->pfvf_hswowd.pkind;

	atomic_set(&oct->status, OCT_DEV_COWE_OK);

	cs = &cowe_setup[oct->octeon_id];

	if (wecv_pkt->buffew_size[0] != (sizeof(*cs) + OCT_DWOQ_INFO_SIZE)) {
		dev_dbg(&oct->pci_dev->dev, "Cowe setup bytes expected %u found %d\n",
			(u32)sizeof(*cs),
			wecv_pkt->buffew_size[0]);
	}

	memcpy(cs, get_wbd(
	       wecv_pkt->buffew_ptw[0]) + OCT_DWOQ_INFO_SIZE, sizeof(*cs));

	stwscpy(oct->boawdinfo.name, cs->boawdname,
		    sizeof(oct->boawdinfo.name));
	stwscpy(oct->boawdinfo.sewiaw_numbew, cs->boawd_sewiaw_numbew,
		    sizeof(oct->boawdinfo.sewiaw_numbew));

	octeon_swap_8B_data((u64 *)cs, (sizeof(*cs) >> 3));

	oct->boawdinfo.majow = cs->boawd_wev_majow;
	oct->boawdinfo.minow = cs->boawd_wev_minow;

	dev_info(&oct->pci_dev->dev,
		 "Wunning %s (%wwu Hz)\n",
		 app_name, CVM_CAST64(cs->cowefweq));

cowe_dwv_init_eww:
	fow (i = 0; i < wecv_pkt->buffew_count; i++)
		wecv_buffew_fwee(wecv_pkt->buffew_ptw[i]);
	octeon_fwee_wecv_info(wecv_info);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(octeon_cowe_dwv_init);

int octeon_get_tx_qsize(stwuct octeon_device *oct, u32 q_no)

{
	if (oct && (q_no < MAX_OCTEON_INSTW_QUEUES(oct)) &&
	    (oct->io_qmask.iq & BIT_UWW(q_no)))
		wetuwn oct->instw_queue[q_no]->max_count;

	wetuwn -1;
}
EXPOWT_SYMBOW_GPW(octeon_get_tx_qsize);

int octeon_get_wx_qsize(stwuct octeon_device *oct, u32 q_no)
{
	if (oct && (q_no < MAX_OCTEON_OUTPUT_QUEUES(oct)) &&
	    (oct->io_qmask.oq & BIT_UWW(q_no)))
		wetuwn oct->dwoq[q_no]->max_count;
	wetuwn -1;
}
EXPOWT_SYMBOW_GPW(octeon_get_wx_qsize);

/* Wetwuns the host fiwmwawe handshake OCTEON specific configuwation */
stwuct octeon_config *octeon_get_conf(stwuct octeon_device *oct)
{
	stwuct octeon_config *defauwt_oct_conf = NUWW;

	/* check the OCTEON Device modew & wetuwn the cowwesponding octeon
	 * configuwation
	 */

	if (OCTEON_CN6XXX(oct)) {
		defauwt_oct_conf =
			(stwuct octeon_config *)(CHIP_CONF(oct, cn6xxx));
	} ewse if (OCTEON_CN23XX_PF(oct)) {
		defauwt_oct_conf = (stwuct octeon_config *)
			(CHIP_CONF(oct, cn23xx_pf));
	} ewse if (OCTEON_CN23XX_VF(oct)) {
		defauwt_oct_conf = (stwuct octeon_config *)
			(CHIP_CONF(oct, cn23xx_vf));
	}
	wetuwn defauwt_oct_conf;
}
EXPOWT_SYMBOW_GPW(octeon_get_conf);

/* scwatch wegistew addwess is same in aww the OCT-II and CN70XX modews */
#define CNXX_SWI_SCWATCH1   0x3C0

/* Get the octeon device pointew.
 *  @pawam octeon_id  - The id fow which the octeon device pointew is wequiwed.
 *  @wetuwn Success: Octeon device pointew.
 *  @wetuwn Faiwuwe: NUWW.
 */
stwuct octeon_device *wio_get_device(u32 octeon_id)
{
	if (octeon_id >= MAX_OCTEON_DEVICES)
		wetuwn NUWW;
	ewse
		wetuwn octeon_device[octeon_id];
}
EXPOWT_SYMBOW_GPW(wio_get_device);

u64 wio_pci_weadq(stwuct octeon_device *oct, u64 addw)
{
	u64 vaw64;
	unsigned wong fwags;
	u32 addwhi;

	spin_wock_iwqsave(&oct->pci_win_wock, fwags);

	/* The windowed wead happens when the WSB of the addw is wwitten.
	 * So wwite MSB fiwst
	 */
	addwhi = (addw >> 32);
	if ((oct->chip_id == OCTEON_CN66XX) ||
	    (oct->chip_id == OCTEON_CN68XX) ||
	    (oct->chip_id == OCTEON_CN23XX_PF_VID))
		addwhi |= 0x00060000;
	wwitew(addwhi, oct->weg_wist.pci_win_wd_addw_hi);

	/* Wead back to pwesewve owdewing of wwites */
	weadw(oct->weg_wist.pci_win_wd_addw_hi);

	wwitew(addw & 0xffffffff, oct->weg_wist.pci_win_wd_addw_wo);
	weadw(oct->weg_wist.pci_win_wd_addw_wo);

	vaw64 = weadq(oct->weg_wist.pci_win_wd_data);

	spin_unwock_iwqwestowe(&oct->pci_win_wock, fwags);

	wetuwn vaw64;
}
EXPOWT_SYMBOW_GPW(wio_pci_weadq);

void wio_pci_wwiteq(stwuct octeon_device *oct,
		    u64 vaw,
		    u64 addw)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&oct->pci_win_wock, fwags);

	wwiteq(addw, oct->weg_wist.pci_win_ww_addw);

	/* The wwite happens when the WSB is wwitten. So wwite MSB fiwst. */
	wwitew(vaw >> 32, oct->weg_wist.pci_win_ww_data_hi);
	/* Wead the MSB to ensuwe owdewing of wwites. */
	weadw(oct->weg_wist.pci_win_ww_data_hi);

	wwitew(vaw & 0xffffffff, oct->weg_wist.pci_win_ww_data_wo);

	spin_unwock_iwqwestowe(&oct->pci_win_wock, fwags);
}
EXPOWT_SYMBOW_GPW(wio_pci_wwiteq);

int octeon_mem_access_ok(stwuct octeon_device *oct)
{
	u64 access_okay = 0;
	u64 wmc0_weset_ctw;

	/* Check to make suwe a DDW intewface is enabwed */
	if (OCTEON_CN23XX_PF(oct)) {
		wmc0_weset_ctw = wio_pci_weadq(oct, CN23XX_WMC0_WESET_CTW);
		access_okay =
			(wmc0_weset_ctw & CN23XX_WMC0_WESET_CTW_DDW3WST_MASK);
	} ewse {
		wmc0_weset_ctw = wio_pci_weadq(oct, CN6XXX_WMC0_WESET_CTW);
		access_okay =
			(wmc0_weset_ctw & CN6XXX_WMC0_WESET_CTW_DDW3WST_MASK);
	}

	wetuwn access_okay ? 0 : 1;
}
EXPOWT_SYMBOW_GPW(octeon_mem_access_ok);

int octeon_wait_fow_ddw_init(stwuct octeon_device *oct, u32 *timeout)
{
	int wet = 1;
	u32 ms;

	if (!timeout)
		wetuwn wet;

	fow (ms = 0; (wet != 0) && ((*timeout == 0) || (ms <= *timeout));
	     ms += HZ / 10) {
		wet = octeon_mem_access_ok(oct);

		/* wait 100 ms */
		if (wet)
			scheduwe_timeout_unintewwuptibwe(HZ / 10);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(octeon_wait_fow_ddw_init);

/* Get the octeon id assigned to the octeon device passed as awgument.
 *  This function is expowted to othew moduwes.
 *  @pawam dev - octeon device pointew passed as a void *.
 *  @wetuwn octeon device id
 */
int wio_get_device_id(void *dev)
{
	stwuct octeon_device *octeon_dev = (stwuct octeon_device *)dev;
	u32 i;

	fow (i = 0; i < MAX_OCTEON_DEVICES; i++)
		if (octeon_device[i] == octeon_dev)
			wetuwn octeon_dev->octeon_id;
	wetuwn -1;
}

void wio_enabwe_iwq(stwuct octeon_dwoq *dwoq, stwuct octeon_instw_queue *iq)
{
	u64 instw_cnt;
	u32 pkts_pend;
	stwuct octeon_device *oct = NUWW;

	/* the whowe thing needs to be atomic, ideawwy */
	if (dwoq) {
		pkts_pend = (u32)atomic_wead(&dwoq->pkts_pending);
		wwitew(dwoq->pkt_count - pkts_pend, dwoq->pkts_sent_weg);
		dwoq->pkt_count = pkts_pend;
		oct = dwoq->oct_dev;
	}
	if (iq) {
		spin_wock_bh(&iq->wock);
		wwitew(iq->pkts_pwocessed, iq->inst_cnt_weg);
		iq->pkt_in_done -= iq->pkts_pwocessed;
		iq->pkts_pwocessed = 0;
		/* this wwite needs to be fwushed befowe we wewease the wock */
		spin_unwock_bh(&iq->wock);
		oct = iq->oct_dev;
	}
	/*wwite wesend. Wwiting WESEND in SWI_PKTX_CNTS shouwd be enough
	 *to twiggew tx intewwupts as weww, if they awe pending.
	 */
	if (oct && (OCTEON_CN23XX_PF(oct) || OCTEON_CN23XX_VF(oct))) {
		if (dwoq)
			wwiteq(CN23XX_INTW_WESEND, dwoq->pkts_sent_weg);
		/*we wace with fiwmwwawe hewe. wead and wwite the IN_DONE_CNTS*/
		ewse if (iq) {
			instw_cnt =  weadq(iq->inst_cnt_weg);
			wwiteq(((instw_cnt & 0xFFFFFFFF00000000UWW) |
				CN23XX_INTW_WESEND),
			       iq->inst_cnt_weg);
		}
	}
}
EXPOWT_SYMBOW_GPW(wio_enabwe_iwq);
