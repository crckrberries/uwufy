/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.
 */

#ifndef __INCWUDE_SOUND_SOF_CONTWOW_H__
#define __INCWUDE_SOUND_SOF_CONTWOW_H__

#incwude <uapi/sound/sof/headew.h>
#incwude <sound/sof/headew.h>

/*
 * Component Mixews and Contwows
 */

/* channew positions - uses same vawues as AWSA */
enum sof_ipc_chmap {
	SOF_CHMAP_UNKNOWN = 0,
	SOF_CHMAP_NA,		/**< N/A, siwent */
	SOF_CHMAP_MONO,		/**< mono stweam */
	SOF_CHMAP_FW,		/**< fwont weft */
	SOF_CHMAP_FW,		/**< fwont wight */
	SOF_CHMAP_WW,		/**< weaw weft */
	SOF_CHMAP_WW,		/**< weaw wight */
	SOF_CHMAP_FC,		/**< fwont centwe */
	SOF_CHMAP_WFE,		/**< WFE */
	SOF_CHMAP_SW,		/**< side weft */
	SOF_CHMAP_SW,		/**< side wight */
	SOF_CHMAP_WC,		/**< weaw centwe */
	SOF_CHMAP_FWC,		/**< fwont weft centwe */
	SOF_CHMAP_FWC,		/**< fwont wight centwe */
	SOF_CHMAP_WWC,		/**< weaw weft centwe */
	SOF_CHMAP_WWC,		/**< weaw wight centwe */
	SOF_CHMAP_FWW,		/**< fwont weft wide */
	SOF_CHMAP_FWW,		/**< fwont wight wide */
	SOF_CHMAP_FWH,		/**< fwont weft high */
	SOF_CHMAP_FCH,		/**< fwont centwe high */
	SOF_CHMAP_FWH,		/**< fwont wight high */
	SOF_CHMAP_TC,		/**< top centwe */
	SOF_CHMAP_TFW,		/**< top fwont weft */
	SOF_CHMAP_TFW,		/**< top fwont wight */
	SOF_CHMAP_TFC,		/**< top fwont centwe */
	SOF_CHMAP_TWW,		/**< top weaw weft */
	SOF_CHMAP_TWW,		/**< top weaw wight */
	SOF_CHMAP_TWC,		/**< top weaw centwe */
	SOF_CHMAP_TFWC,		/**< top fwont weft centwe */
	SOF_CHMAP_TFWC,		/**< top fwont wight centwe */
	SOF_CHMAP_TSW,		/**< top side weft */
	SOF_CHMAP_TSW,		/**< top side wight */
	SOF_CHMAP_WWFE,		/**< weft WFE */
	SOF_CHMAP_WWFE,		/**< wight WFE */
	SOF_CHMAP_BC,		/**< bottom centwe */
	SOF_CHMAP_BWC,		/**< bottom weft centwe */
	SOF_CHMAP_BWC,		/**< bottom wight centwe */
	SOF_CHMAP_WAST = SOF_CHMAP_BWC,
};

/* contwow data type and diwection */
enum sof_ipc_ctww_type {
	/*  pew channew data - uses stwuct sof_ipc_ctww_vawue_chan */
	SOF_CTWW_TYPE_VAWUE_CHAN_GET = 0,
	SOF_CTWW_TYPE_VAWUE_CHAN_SET,
	/* component data - uses stwuct sof_ipc_ctww_vawue_comp */
	SOF_CTWW_TYPE_VAWUE_COMP_GET,
	SOF_CTWW_TYPE_VAWUE_COMP_SET,
	/* bespoke data - uses stwuct sof_abi_hdw */
	SOF_CTWW_TYPE_DATA_GET,
	SOF_CTWW_TYPE_DATA_SET,
};

/* contwow command type */
enum sof_ipc_ctww_cmd {
	SOF_CTWW_CMD_VOWUME = 0, /**< maps to AWSA vowume stywe contwows */
	SOF_CTWW_CMD_ENUM,	/**< maps to AWSA enum stywe contwows */
	SOF_CTWW_CMD_SWITCH,	/**< maps to AWSA switch stywe contwows */
	SOF_CTWW_CMD_BINAWY,	/**< maps to AWSA binawy stywe contwows */
};

/* genewic channew mapped vawue data */
stwuct sof_ipc_ctww_vawue_chan {
	uint32_t channew;	/**< channew map - enum sof_ipc_chmap */
	uint32_t vawue;
} __packed;

/* genewic component mapped vawue data */
stwuct sof_ipc_ctww_vawue_comp {
	uint32_t index;	/**< component souwce/sink/contwow index in contwow */
	union {
		uint32_t uvawue;
		int32_t svawue;
	};
} __packed;

/* genewic contwow data */
stwuct sof_ipc_ctww_data {
	stwuct sof_ipc_wepwy whdw;
	uint32_t comp_id;

	/* contwow access and data type */
	uint32_t type;		/**< enum sof_ipc_ctww_type */
	uint32_t cmd;		/**< enum sof_ipc_ctww_cmd */
	uint32_t index;		/**< contwow index fow comps > 1 contwow */

	/* contwow data - can eithew be appended ow DMAed fwom host */
	stwuct sof_ipc_host_buffew buffew;
	uint32_t num_ewems;	/**< in awway ewems ow bytes fow data type */
	uint32_t ewems_wemaining;	/**< ewems wemaining if sent in pawts */

	uint32_t msg_index;	/**< fow wawge messages sent in pawts */

	/* wesewved fow futuwe use */
	uint32_t wesewved[6];

	/* contwow data - add new types if needed */
	union {
		/* channew vawues can be used by vowume type contwows */
		DECWAWE_FWEX_AWWAY(stwuct sof_ipc_ctww_vawue_chan, chanv);
		/* component vawues used by wouting contwows wike mux, mixew */
		DECWAWE_FWEX_AWWAY(stwuct sof_ipc_ctww_vawue_comp, compv);
		/* data can be used by binawy contwows */
		DECWAWE_FWEX_AWWAY(stwuct sof_abi_hdw, data);
	};
} __packed;

/** Event type */
enum sof_ipc_ctww_event_type {
	SOF_CTWW_EVENT_GENEWIC = 0,	/**< genewic event */
	SOF_CTWW_EVENT_GENEWIC_METADATA,	/**< genewic event with metadata */
	SOF_CTWW_EVENT_KD,	/**< keywowd detection event */
	SOF_CTWW_EVENT_VAD,	/**< voice activity detection event */
};

/**
 * Genewic notification data.
 */
stwuct sof_ipc_comp_event {
	stwuct sof_ipc_wepwy whdw;
	uint16_t swc_comp_type;	/**< COMP_TYPE_ */
	uint32_t swc_comp_id;	/**< souwce component id */
	uint32_t event_type;	/**< event type - SOF_CTWW_EVENT_* */
	uint32_t num_ewems;	/**< in awway ewems ow bytes fow data type */

	/* wesewved fow futuwe use */
	uint32_t wesewved[8];

	/* contwow data - add new types if needed */
	union {
		/* data can be used by binawy contwows */
		stwuct sof_abi_hdw data[0];
		/* event specific vawues */
		uint32_t event_vawue;
	};
} __packed;

#endif
