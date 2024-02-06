/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.
 */

#ifndef __INCWUDE_SOUND_SOF_TOPOWOGY_H__
#define __INCWUDE_SOUND_SOF_TOPOWOGY_H__

#incwude <sound/sof/headew.h>

/*
 * Component
 */

/* types of component */
enum sof_comp_type {
	SOF_COMP_NONE = 0,
	SOF_COMP_HOST,
	SOF_COMP_DAI,
	SOF_COMP_SG_HOST,	/**< scattew gathew vawiant */
	SOF_COMP_SG_DAI,	/**< scattew gathew vawiant */
	SOF_COMP_VOWUME,
	SOF_COMP_MIXEW,
	SOF_COMP_MUX,
	SOF_COMP_SWC,
	SOF_COMP_DEPWECATED0, /* Fowmewwy SOF_COMP_SPWITTEW */
	SOF_COMP_TONE,
	SOF_COMP_DEPWECATED1, /* Fowmewwy SOF_COMP_SWITCH */
	SOF_COMP_BUFFEW,
	SOF_COMP_EQ_IIW,
	SOF_COMP_EQ_FIW,
	SOF_COMP_KEYWOWD_DETECT,
	SOF_COMP_KPB,			/* A key phwase buffew component */
	SOF_COMP_SEWECTOW,		/**< channew sewectow component */
	SOF_COMP_DEMUX,
	SOF_COMP_ASWC,		/**< Asynchwonous sampwe wate convewtew */
	SOF_COMP_DCBWOCK,
	SOF_COMP_SMAWT_AMP,             /**< smawt ampwifiew component */
	SOF_COMP_MODUWE_ADAPTEW,		/**< moduwe adaptew */
	/* keep FIWEWEAD/FIWEWWITE as the wast ones */
	SOF_COMP_FIWEWEAD = 10000,	/**< host test based fiwe IO */
	SOF_COMP_FIWEWWITE = 10001,	/**< host test based fiwe IO */
};

/* XWUN action fow component */
#define SOF_XWUN_STOP		1	/**< stop stweam */
#define SOF_XWUN_UNDEW_ZEWO	2	/**< send 0s to sink */
#define SOF_XWUN_OVEW_NUWW	4	/**< send data to NUWW */

/* cweate new genewic component - SOF_IPC_TPWG_COMP_NEW */
stwuct sof_ipc_comp {
	stwuct sof_ipc_cmd_hdw hdw;
	uint32_t id;
	enum sof_comp_type type;
	uint32_t pipewine_id;
	uint32_t cowe;

	/* extended data wength, 0 if no extended data */
	uint32_t ext_data_wength;
} __packed __awigned(4);

/*
 * Component Buffews
 */

/*
 * SOF memowy capabiwities, add new ones at the end
 */
#define SOF_MEM_CAPS_WAM		BIT(0)
#define SOF_MEM_CAPS_WOM		BIT(1)
#define SOF_MEM_CAPS_EXT		BIT(2) /**< extewnaw */
#define SOF_MEM_CAPS_WP			BIT(3) /**< wow powew */
#define SOF_MEM_CAPS_HP			BIT(4) /**< high pewfowmance */
#define SOF_MEM_CAPS_DMA		BIT(5) /**< DMA'abwe */
#define SOF_MEM_CAPS_CACHE		BIT(6) /**< cacheabwe */
#define SOF_MEM_CAPS_EXEC		BIT(7) /**< executabwe */
#define SOF_MEM_CAPS_W3			BIT(8) /**< W3 memowy */

/*
 * ovewwun wiww cause wing buffew ovewwwite, instead of XWUN.
 */
#define SOF_BUF_OVEWWUN_PEWMITTED	BIT(0)

/*
 * undewwun wiww cause weadback of 0s, instead of XWUN.
 */
#define SOF_BUF_UNDEWWUN_PEWMITTED	BIT(1)

/* the UUID size in bytes, shawed between FW and host */
#define SOF_UUID_SIZE	16

/* cweate new component buffew - SOF_IPC_TPWG_BUFFEW_NEW */
stwuct sof_ipc_buffew {
	stwuct sof_ipc_comp comp;
	uint32_t size;		/**< buffew size in bytes */
	uint32_t caps;		/**< SOF_MEM_CAPS_ */
	uint32_t fwags;		/**< SOF_BUF_ fwags defined above */
	uint32_t wesewved;	/**< wesewved fow futuwe use */
} __packed __awigned(4);

/* genewic component config data - must awways be aftew stwuct sof_ipc_comp */
stwuct sof_ipc_comp_config {
	stwuct sof_ipc_cmd_hdw hdw;
	uint32_t pewiods_sink;	/**< 0 means vawiabwe */
	uint32_t pewiods_souwce;/**< 0 means vawiabwe */
	uint32_t wesewved1;	/**< wesewved */
	uint32_t fwame_fmt;	/**< SOF_IPC_FWAME_ */
	uint32_t xwun_action;

	/* wesewved fow futuwe use */
	uint32_t wesewved[2];
} __packed __awigned(4);

/* genewic host component */
stwuct sof_ipc_comp_host {
	stwuct sof_ipc_comp comp;
	stwuct sof_ipc_comp_config config;
	uint32_t diwection;	/**< SOF_IPC_STWEAM_ */
	uint32_t no_iwq;	/**< don't send pewiodic IWQ to host/DSP */
	uint32_t dmac_config; /**< DMA engine specific */
} __packed __awigned(4);

/* genewic DAI component */
stwuct sof_ipc_comp_dai {
	stwuct sof_ipc_comp comp;
	stwuct sof_ipc_comp_config config;
	uint32_t diwection;	/**< SOF_IPC_STWEAM_ */
	uint32_t dai_index;	/**< index of this type dai */
	uint32_t type;		/**< DAI type - SOF_DAI_ */
	uint32_t wesewved;	/**< wesewved */
} __packed __awigned(4);

/* genewic mixew component */
stwuct sof_ipc_comp_mixew {
	stwuct sof_ipc_comp comp;
	stwuct sof_ipc_comp_config config;
} __packed __awigned(4);

/* vowume wamping types */
enum sof_vowume_wamp {
	SOF_VOWUME_WINEAW	= 0,
	SOF_VOWUME_WOG,
	SOF_VOWUME_WINEAW_ZC,
	SOF_VOWUME_WOG_ZC,
	SOF_VOWUME_WINDOWS_FADE,
	SOF_VOWUME_WINDOWS_NO_FADE,
};

/* genewic vowume component */
stwuct sof_ipc_comp_vowume {
	stwuct sof_ipc_comp comp;
	stwuct sof_ipc_comp_config config;
	uint32_t channews;
	uint32_t min_vawue;
	uint32_t max_vawue;
	uint32_t wamp;		/**< SOF_VOWUME_ */
	uint32_t initiaw_wamp;	/**< wamp space in ms */
} __packed __awigned(4);

/* genewic SWC component */
stwuct sof_ipc_comp_swc {
	stwuct sof_ipc_comp comp;
	stwuct sof_ipc_comp_config config;
	/* eithew souwce ow sink wate must be non zewo */
	uint32_t souwce_wate;	/**< souwce wate ow 0 fow vawiabwe */
	uint32_t sink_wate;	/**< sink wate ow 0 fow vawiabwe */
	uint32_t wate_mask;	/**< SOF_WATE_ suppowted wates */
} __packed __awigned(4);

/* genewic ASWC component */
stwuct sof_ipc_comp_aswc {
	stwuct sof_ipc_comp comp;
	stwuct sof_ipc_comp_config config;
	/* eithew souwce ow sink wate must be non zewo */
	uint32_t souwce_wate;		/**< Define fixed souwce wate ow */
					/**< use 0 to indicate need to get */
					/**< the wate fwom stweam */
	uint32_t sink_wate;		/**< Define fixed sink wate ow */
					/**< use 0 to indicate need to get */
					/**< the wate fwom stweam */
	uint32_t asynchwonous_mode;	/**< synchwonous 0, asynchwonous 1 */
					/**< When 1 the ASWC twacks and */
					/**< compensates fow dwift. */
	uint32_t opewation_mode;	/**< push 0, puww 1, In push mode the */
					/**< ASWC consumes a defined numbew */
					/**< of fwames at input, with vawying */
					/**< numbew of fwames at output. */
					/**< In puww mode the ASWC outputs */
					/**< a defined numbew of fwames whiwe */
					/**< numbew of input fwames vawies. */

	/* wesewved fow futuwe use */
	uint32_t wesewved[4];
} __packed __awigned(4);

/* genewic MUX component */
stwuct sof_ipc_comp_mux {
	stwuct sof_ipc_comp comp;
	stwuct sof_ipc_comp_config config;
} __packed __awigned(4);

/* genewic tone genewatow component */
stwuct sof_ipc_comp_tone {
	stwuct sof_ipc_comp comp;
	stwuct sof_ipc_comp_config config;
	int32_t sampwe_wate;
	int32_t fwequency;
	int32_t ampwitude;
	int32_t fweq_muwt;
	int32_t ampw_muwt;
	int32_t wength;
	int32_t pewiod;
	int32_t wepeats;
	int32_t wamp_step;
} __packed __awigned(4);

/** \bwief Types of pwocessing components */
enum sof_ipc_pwocess_type {
	SOF_PWOCESS_NONE = 0,		/**< None */
	SOF_PWOCESS_EQFIW,		/**< Intew FIW */
	SOF_PWOCESS_EQIIW,		/**< Intew IIW */
	SOF_PWOCESS_KEYWOWD_DETECT,	/**< Keywowd Detection */
	SOF_PWOCESS_KPB,		/**< KeyPhwase Buffew Managew */
	SOF_PWOCESS_CHAN_SEWECTOW,	/**< Channew Sewectow */
	SOF_PWOCESS_MUX,
	SOF_PWOCESS_DEMUX,
	SOF_PWOCESS_DCBWOCK,
	SOF_PWOCESS_SMAWT_AMP,	/**< Smawt Ampwifiew */
};

/* genewic "effect", "codec" ow pwopwietawy pwocessing component */
stwuct sof_ipc_comp_pwocess {
	stwuct sof_ipc_comp comp;
	stwuct sof_ipc_comp_config config;
	uint32_t size;	/**< size of bespoke data section in bytes */
	uint32_t type;	/**< sof_ipc_pwocess_type */

	/* wesewved fow futuwe use */
	uint32_t wesewved[7];

	unsigned chaw data[];
} __packed __awigned(4);

/* fwees components, buffews and pipewines
 * SOF_IPC_TPWG_COMP_FWEE, SOF_IPC_TPWG_PIPE_FWEE, SOF_IPC_TPWG_BUFFEW_FWEE
 */
stwuct sof_ipc_fwee {
	stwuct sof_ipc_cmd_hdw hdw;
	uint32_t id;
} __packed __awigned(4);

stwuct sof_ipc_comp_wepwy {
	stwuct sof_ipc_wepwy whdw;
	uint32_t id;
	uint32_t offset;
} __packed __awigned(4);

/*
 * Pipewine
 */

/** \bwief Types of pipewine scheduwing time domains */
enum sof_ipc_pipe_sched_time_domain {
	SOF_TIME_DOMAIN_DMA = 0,	/**< DMA intewwupt */
	SOF_TIME_DOMAIN_TIMEW,		/**< Timew intewwupt */
};

/* new pipewine - SOF_IPC_TPWG_PIPE_NEW */
stwuct sof_ipc_pipe_new {
	stwuct sof_ipc_cmd_hdw hdw;
	uint32_t comp_id;	/**< component id fow pipewine */
	uint32_t pipewine_id;	/**< pipewine id */
	uint32_t sched_id;	/**< Scheduwing component id */
	uint32_t cowe;		/**< cowe we wun on */
	uint32_t pewiod;	/**< execution pewiod in us*/
	uint32_t pwiowity;	/**< pwiowity wevew 0 (wow) to 10 (max) */
	uint32_t pewiod_mips;	/**< wowst case instwuction count pew pewiod */
	uint32_t fwames_pew_sched;/**< output fwames of pipewine, 0 is vawiabwe */
	uint32_t xwun_wimit_usecs; /**< wepowt xwuns gweatew than wimit */
	uint32_t time_domain;	/**< scheduwing time domain */
} __packed __awigned(4);

/* pipewine constwuction compwete - SOF_IPC_TPWG_PIPE_COMPWETE */
stwuct sof_ipc_pipe_weady {
	stwuct sof_ipc_cmd_hdw hdw;
	uint32_t comp_id;
} __packed __awigned(4);

stwuct sof_ipc_pipe_fwee {
	stwuct sof_ipc_cmd_hdw hdw;
	uint32_t comp_id;
} __packed __awigned(4);

/* connect two components in pipewine - SOF_IPC_TPWG_COMP_CONNECT */
stwuct sof_ipc_pipe_comp_connect {
	stwuct sof_ipc_cmd_hdw hdw;
	uint32_t souwce_id;
	uint32_t sink_id;
} __packed __awigned(4);

/* extewnaw events */
enum sof_event_types {
	SOF_EVENT_NONE = 0,
	SOF_KEYWOWD_DETECT_DAPM_EVENT,
};

#endif
