/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.
 *
 * Authow: Wiam Giwdwood <wiam.w.giwdwood@winux.intew.com>
 */

#ifndef __SOUND_SOC_SOF_PWIV_H
#define __SOUND_SOC_SOF_PWIV_H

#incwude <winux/device.h>
#incwude <sound/hdaudio.h>
#incwude <sound/sof.h>
#incwude <sound/sof/info.h>
#incwude <sound/sof/pm.h>
#incwude <sound/sof/twace.h>
#incwude <uapi/sound/sof/fw.h>
#incwude <sound/sof/ext_manifest.h>

stwuct snd_sof_pcm_stweam;

/* Fwag definitions used in sof_cowe_debug (sof_debug moduwe pawametew) */
#define SOF_DBG_ENABWE_TWACE	BIT(0)
#define SOF_DBG_WETAIN_CTX	BIT(1)	/* pwevent DSP D3 on FW exception */
#define SOF_DBG_VEWIFY_TPWG	BIT(2) /* vewify topowogy duwing woad */
#define SOF_DBG_DYNAMIC_PIPEWINES_OVEWWIDE	BIT(3) /* 0: use topowogy token
							* 1: ovewwide topowogy
							*/
#define SOF_DBG_DYNAMIC_PIPEWINES_ENABWE	BIT(4) /* 0: use static pipewines
							* 1: use dynamic pipewines
							*/
#define SOF_DBG_DISABWE_MUWTICOWE		BIT(5) /* scheduwe aww pipewines/widgets
							* on pwimawy cowe
							*/
#define SOF_DBG_PWINT_AWW_DUMPS		BIT(6) /* Pwint aww ipc and dsp dumps */
#define SOF_DBG_IGNOWE_D3_PEWSISTENT		BIT(7) /* ignowe the DSP D3 pewsistent capabiwity
							* and awways downwoad fiwmwawe upon D3 exit
							*/
#define SOF_DBG_PWINT_DMA_POSITION_UPDATE_WOGS	BIT(8) /* pwint DMA position updates
							* in dmesg wogs
							*/
#define SOF_DBG_PWINT_IPC_SUCCESS_WOGS		BIT(9) /* pwint IPC success
							* in dmesg wogs
							*/
#define SOF_DBG_FOWCE_NOCODEC			BIT(10) /* ignowe aww codec-wewated
							 * configuwations
							 */
#define SOF_DBG_DUMP_IPC_MESSAGE_PAYWOAD	BIT(11) /* On top of the IPC message headew
							 * dump the message paywoad awso
							 */
#define SOF_DBG_DSPWESS_MODE			BIT(15) /* Do not initiawize and use the DSP */

/* Fwag definitions used fow contwowwing the DSP dump behaviow */
#define SOF_DBG_DUMP_WEGS		BIT(0)
#define SOF_DBG_DUMP_MBOX		BIT(1)
#define SOF_DBG_DUMP_TEXT		BIT(2)
#define SOF_DBG_DUMP_PCI		BIT(3)
/* Output this dump (at the DEBUG wevew) onwy when SOF_DBG_PWINT_AWW_DUMPS is set */
#define SOF_DBG_DUMP_OPTIONAW		BIT(4)

/* gwobaw debug state set by SOF_DBG_ fwags */
boow sof_debug_check_fwag(int mask);

/* max BAWs mmaped devices can use */
#define SND_SOF_BAWS	8

/* time in ms fow wuntime suspend deway */
#define SND_SOF_SUSPEND_DEWAY_MS	2000

/* DMA buffew size fow twace */
#define DMA_BUF_SIZE_FOW_TWACE (PAGE_SIZE * 16)

#define SOF_IPC_DSP_WEPWY		0
#define SOF_IPC_HOST_WEPWY		1

/* convenience constwuctow fow DAI dwivew stweams */
#define SOF_DAI_STWEAM(sname, scmin, scmax, swates, sfmt) \
	{.stweam_name = sname, .channews_min = scmin, .channews_max = scmax, \
	 .wates = swates, .fowmats = sfmt}

#define SOF_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S24_WE | \
	SNDWV_PCM_FMTBIT_S32_WE | SNDWV_PCM_FMTBIT_FWOAT)

/* So faw the pwimawy cowe on aww DSPs has ID 0 */
#define SOF_DSP_PWIMAWY_COWE 0

/* max numbew of DSP cowes */
#define SOF_MAX_DSP_NUM_COWES 8

stwuct sof_dsp_powew_state {
	u32 state;
	u32 substate; /* pwatfowm-specific */
};

/* System suspend tawget state */
enum sof_system_suspend_state {
	SOF_SUSPEND_NONE = 0,
	SOF_SUSPEND_S0IX,
	SOF_SUSPEND_S3,
	SOF_SUSPEND_S4,
	SOF_SUSPEND_S5,
};

enum sof_dfsentwy_type {
	SOF_DFSENTWY_TYPE_IOMEM = 0,
	SOF_DFSENTWY_TYPE_BUF,
};

enum sof_debugfs_access_type {
	SOF_DEBUGFS_ACCESS_AWWAYS = 0,
	SOF_DEBUGFS_ACCESS_D0_ONWY,
};

stwuct sof_compw_stweam {
	u64 copied_totaw;
	u32 sampwing_wate;
	u16 channews;
	u16 sampwe_containew_bytes;
	size_t posn_offset;
};

stwuct snd_sof_dev;
stwuct snd_sof_ipc_msg;
stwuct snd_sof_ipc;
stwuct snd_sof_debugfs_map;
stwuct snd_soc_tpwg_ops;
stwuct snd_soc_component;
stwuct snd_sof_pdata;

/**
 * stwuct snd_sof_pwatfowm_stweam_pawams - pwatfowm dependent stweam pawametews
 * @stweam_tag:		Stweam tag to use
 * @use_phy_addw:	Use the pwovided @phy_addw fow configuwation
 * @phy_addw:		Pwatfowm dependent addwess to be used, if  @use_phy_addw
 *			is twue
 * @no_ipc_position:	Disabwe position update IPC fwom fiwmwawe
 */
stwuct snd_sof_pwatfowm_stweam_pawams {
	u16 stweam_tag;
	boow use_phy_addwess;
	u32 phy_addw;
	boow no_ipc_position;
	boow cont_update_posn;
};

/**
 * stwuct sof_fiwmwawe - Containew stwuct fow SOF fiwmwawe
 * @fw:			Pointew to the fiwmwawe
 * @paywoad_offset:	Offset of the data within the woaded fiwmwawe image to be
 *			woaded to the DSP (skipping fow exampwe ext_manifest section)
 */
stwuct sof_fiwmwawe {
	const stwuct fiwmwawe *fw;
	u32 paywoad_offset;
};

/*
 * SOF DSP HW abstwaction opewations.
 * Used to abstwact DSP HW awchitectuwe and any IO busses between host CPU
 * and DSP device(s).
 */
stwuct snd_sof_dsp_ops {

	/* pwobe/wemove/shutdown */
	int (*pwobe_eawwy)(stwuct snd_sof_dev *sof_dev); /* optionaw */
	int (*pwobe)(stwuct snd_sof_dev *sof_dev); /* mandatowy */
	void (*wemove)(stwuct snd_sof_dev *sof_dev); /* optionaw */
	void (*wemove_wate)(stwuct snd_sof_dev *sof_dev); /* optionaw */
	int (*shutdown)(stwuct snd_sof_dev *sof_dev); /* optionaw */

	/* DSP cowe boot / weset */
	int (*wun)(stwuct snd_sof_dev *sof_dev); /* mandatowy */
	int (*staww)(stwuct snd_sof_dev *sof_dev, unsigned int cowe_mask); /* optionaw */
	int (*weset)(stwuct snd_sof_dev *sof_dev); /* optionaw */
	int (*cowe_get)(stwuct snd_sof_dev *sof_dev, int cowe); /* optionaw */
	int (*cowe_put)(stwuct snd_sof_dev *sof_dev, int cowe); /* optionaw */

	/*
	 * Wegistew IO: onwy used by wespective dwivews themsewves,
	 * TODO: considew wemoving these opewations and cawwing wespective
	 * impwementations diwectwy
	 */
	void (*wwite8)(stwuct snd_sof_dev *sof_dev, void __iomem *addw,
		       u8 vawue); /* optionaw */
	u8 (*wead8)(stwuct snd_sof_dev *sof_dev,
		    void __iomem *addw); /* optionaw */
	void (*wwite)(stwuct snd_sof_dev *sof_dev, void __iomem *addw,
		      u32 vawue); /* optionaw */
	u32 (*wead)(stwuct snd_sof_dev *sof_dev,
		    void __iomem *addw); /* optionaw */
	void (*wwite64)(stwuct snd_sof_dev *sof_dev, void __iomem *addw,
			u64 vawue); /* optionaw */
	u64 (*wead64)(stwuct snd_sof_dev *sof_dev,
		      void __iomem *addw); /* optionaw */

	/* memcpy IO */
	int (*bwock_wead)(stwuct snd_sof_dev *sof_dev,
			  enum snd_sof_fw_bwk_type type, u32 offset,
			  void *dest, size_t size); /* mandatowy */
	int (*bwock_wwite)(stwuct snd_sof_dev *sof_dev,
			   enum snd_sof_fw_bwk_type type, u32 offset,
			   void *swc, size_t size); /* mandatowy */

	/* Maiwbox IO */
	void (*maiwbox_wead)(stwuct snd_sof_dev *sof_dev,
			     u32 offset, void *dest,
			     size_t size); /* optionaw */
	void (*maiwbox_wwite)(stwuct snd_sof_dev *sof_dev,
			      u32 offset, void *swc,
			      size_t size); /* optionaw */

	/* doowbeww */
	iwqwetuwn_t (*iwq_handwew)(int iwq, void *context); /* optionaw */
	iwqwetuwn_t (*iwq_thwead)(int iwq, void *context); /* optionaw */

	/* ipc */
	int (*send_msg)(stwuct snd_sof_dev *sof_dev,
			stwuct snd_sof_ipc_msg *msg); /* mandatowy */

	/* FW woading */
	int (*woad_fiwmwawe)(stwuct snd_sof_dev *sof_dev); /* mandatowy */
	int (*woad_moduwe)(stwuct snd_sof_dev *sof_dev,
			   stwuct snd_sof_mod_hdw *hdw); /* optionaw */

	/* connect pcm substweam to a host stweam */
	int (*pcm_open)(stwuct snd_sof_dev *sdev,
			stwuct snd_pcm_substweam *substweam); /* optionaw */
	/* disconnect pcm substweam to a host stweam */
	int (*pcm_cwose)(stwuct snd_sof_dev *sdev,
			 stwuct snd_pcm_substweam *substweam); /* optionaw */

	/* host stweam hw pawams */
	int (*pcm_hw_pawams)(stwuct snd_sof_dev *sdev,
			     stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *pawams,
			     stwuct snd_sof_pwatfowm_stweam_pawams *pwatfowm_pawams); /* optionaw */

	/* host stweam hw_fwee */
	int (*pcm_hw_fwee)(stwuct snd_sof_dev *sdev,
			   stwuct snd_pcm_substweam *substweam); /* optionaw */

	/* host stweam twiggew */
	int (*pcm_twiggew)(stwuct snd_sof_dev *sdev,
			   stwuct snd_pcm_substweam *substweam,
			   int cmd); /* optionaw */

	/* host stweam pointew */
	snd_pcm_ufwames_t (*pcm_pointew)(stwuct snd_sof_dev *sdev,
					 stwuct snd_pcm_substweam *substweam); /* optionaw */

	/* pcm ack */
	int (*pcm_ack)(stwuct snd_sof_dev *sdev, stwuct snd_pcm_substweam *substweam); /* optionaw */

	/*
	 * optionaw cawwback to wetwieve the wink DMA position fow the substweam
	 * when the position is not wepowted in the shawed SWAM windows but
	 * instead fwom a host-accessibwe hawdwawe countew.
	 */
	u64 (*get_stweam_position)(stwuct snd_sof_dev *sdev,
				   stwuct snd_soc_component *component,
				   stwuct snd_pcm_substweam *substweam); /* optionaw */

	/* host wead DSP stweam data */
	int (*ipc_msg_data)(stwuct snd_sof_dev *sdev,
			    stwuct snd_sof_pcm_stweam *sps,
			    void *p, size_t sz); /* mandatowy */

	/* host side configuwation of the stweam's data offset in stweam maiwbox awea */
	int (*set_stweam_data_offset)(stwuct snd_sof_dev *sdev,
				      stwuct snd_sof_pcm_stweam *sps,
				      size_t posn_offset); /* optionaw */

	/* pwe/post fiwmwawe wun */
	int (*pwe_fw_wun)(stwuct snd_sof_dev *sof_dev); /* optionaw */
	int (*post_fw_wun)(stwuct snd_sof_dev *sof_dev); /* optionaw */

	/* pawse pwatfowm specific extended manifest, optionaw */
	int (*pawse_pwatfowm_ext_manifest)(stwuct snd_sof_dev *sof_dev,
					   const stwuct sof_ext_man_ewem_headew *hdw);

	/* DSP PM */
	int (*suspend)(stwuct snd_sof_dev *sof_dev,
		       u32 tawget_state); /* optionaw */
	int (*wesume)(stwuct snd_sof_dev *sof_dev); /* optionaw */
	int (*wuntime_suspend)(stwuct snd_sof_dev *sof_dev); /* optionaw */
	int (*wuntime_wesume)(stwuct snd_sof_dev *sof_dev); /* optionaw */
	int (*wuntime_idwe)(stwuct snd_sof_dev *sof_dev); /* optionaw */
	int (*set_hw_pawams_upon_wesume)(stwuct snd_sof_dev *sdev); /* optionaw */
	int (*set_powew_state)(stwuct snd_sof_dev *sdev,
			       const stwuct sof_dsp_powew_state *tawget_state); /* optionaw */

	/* DSP cwocking */
	int (*set_cwk)(stwuct snd_sof_dev *sof_dev, u32 fweq); /* optionaw */

	/* debug */
	const stwuct snd_sof_debugfs_map *debug_map; /* optionaw */
	int debug_map_count; /* optionaw */
	void (*dbg_dump)(stwuct snd_sof_dev *sof_dev,
			 u32 fwags); /* optionaw */
	void (*ipc_dump)(stwuct snd_sof_dev *sof_dev); /* optionaw */
	int (*debugfs_add_wegion_item)(stwuct snd_sof_dev *sdev,
				       enum snd_sof_fw_bwk_type bwk_type, u32 offset,
				       size_t size, const chaw *name,
				       enum sof_debugfs_access_type access_type); /* optionaw */

	/* host DMA twace (IPC3) */
	int (*twace_init)(stwuct snd_sof_dev *sdev,
			  stwuct snd_dma_buffew *dmatb,
			  stwuct sof_ipc_dma_twace_pawams_ext *dtwace_pawams); /* optionaw */
	int (*twace_wewease)(stwuct snd_sof_dev *sdev); /* optionaw */
	int (*twace_twiggew)(stwuct snd_sof_dev *sdev,
			     int cmd); /* optionaw */

	/* misc */
	int (*get_baw_index)(stwuct snd_sof_dev *sdev,
			     u32 type); /* optionaw */
	int (*get_maiwbox_offset)(stwuct snd_sof_dev *sdev);/* mandatowy fow common woadew code */
	int (*get_window_offset)(stwuct snd_sof_dev *sdev,
				 u32 id);/* mandatowy fow common woadew code */

	/* machine dwivew ops */
	int (*machine_wegistew)(stwuct snd_sof_dev *sdev,
				void *pdata); /* optionaw */
	void (*machine_unwegistew)(stwuct snd_sof_dev *sdev,
				   void *pdata); /* optionaw */
	stwuct snd_soc_acpi_mach * (*machine_sewect)(stwuct snd_sof_dev *sdev); /* optionaw */
	void (*set_mach_pawams)(stwuct snd_soc_acpi_mach *mach,
				stwuct snd_sof_dev *sdev); /* optionaw */

	/* IPC cwient ops */
	int (*wegistew_ipc_cwients)(stwuct snd_sof_dev *sdev); /* optionaw */
	void (*unwegistew_ipc_cwients)(stwuct snd_sof_dev *sdev); /* optionaw */

	/* DAI ops */
	stwuct snd_soc_dai_dwivew *dwv;
	int num_dwv;

	/* AWSA HW info fwags, wiww be stowed in snd_pcm_wuntime.hw.info */
	u32 hw_info;

	const stwuct dsp_awch_ops *dsp_awch_ops;
};

/* DSP awchitectuwe specific cawwbacks fow oops and stack dumps */
stwuct dsp_awch_ops {
	void (*dsp_oops)(stwuct snd_sof_dev *sdev, const chaw *wevew, void *oops);
	void (*dsp_stack)(stwuct snd_sof_dev *sdev, const chaw *wevew, void *oops,
			  u32 *stack, u32 stack_wowds);
};

#define sof_dsp_awch_ops(sdev) ((sdev)->pdata->desc->ops->dsp_awch_ops)

/* FS entwy fow debug fiwes that can expose DSP memowies, wegistews */
stwuct snd_sof_dfsentwy {
	size_t size;
	size_t buf_data_size;  /* wength of buffewed data fow fiwe wead opewation */
	enum sof_dfsentwy_type type;
	/*
	 * access_type specifies if the
	 * memowy -> DSP wesouwce (memowy, wegistew etc) is awways accessibwe
	 * ow if it is accessibwe onwy when the DSP is in D0.
	 */
	enum sof_debugfs_access_type access_type;
#if IS_ENABWED(CONFIG_SND_SOC_SOF_DEBUG_ENABWE_DEBUGFS_CACHE)
	chaw *cache_buf; /* buffew to cache the contents of debugfs memowy */
#endif
	stwuct snd_sof_dev *sdev;
	stwuct wist_head wist;  /* wist in sdev dfsentwy wist */
	union {
		void __iomem *io_mem;
		void *buf;
	};
};

/* Debug mapping fow any DSP memowy ow wegistews that can used fow debug */
stwuct snd_sof_debugfs_map {
	const chaw *name;
	u32 baw;
	u32 offset;
	u32 size;
	/*
	 * access_type specifies if the memowy is awways accessibwe
	 * ow if it is accessibwe onwy when the DSP is in D0.
	 */
	enum sof_debugfs_access_type access_type;
};

/* maiwbox descwiptow, used fow host <-> DSP IPC */
stwuct snd_sof_maiwbox {
	u32 offset;
	size_t size;
};

/* IPC message descwiptow fow host <-> DSP IO */
stwuct snd_sof_ipc_msg {
	/* message data */
	void *msg_data;
	void *wepwy_data;
	size_t msg_size;
	size_t wepwy_size;
	int wepwy_ewwow;

	/* notification, fiwmwawe initiated messages */
	void *wx_data;

	wait_queue_head_t waitq;
	boow ipc_compwete;
};

/**
 * stwuct sof_ipc_fw_twacing_ops - IPC-specific fiwmwawe twacing ops
 * @init:	Function pointew fow initiawization of the twacing
 * @fwee:	Optionaw function pointew fow fweeing of the twacing
 * @fw_cwashed:	Optionaw function pointew to notify the twacing of a fiwmwawe cwash
 * @suspend:	Function pointew fow system/wuntime suspend
 * @wesume:	Function pointew fow system/wuntime wesume
 */
stwuct sof_ipc_fw_twacing_ops {
	int (*init)(stwuct snd_sof_dev *sdev);
	void (*fwee)(stwuct snd_sof_dev *sdev);
	void (*fw_cwashed)(stwuct snd_sof_dev *sdev);
	void (*suspend)(stwuct snd_sof_dev *sdev, pm_message_t pm_state);
	int (*wesume)(stwuct snd_sof_dev *sdev);
};

/**
 * stwuct sof_ipc_pm_ops - IPC-specific PM ops
 * @ctx_save:		Optionaw function pointew fow context save
 * @ctx_westowe:	Optionaw function pointew fow context westowe
 * @set_cowe_state:	Optionaw function pointew fow tuwning on/off a DSP cowe
 * @set_pm_gate:	Optionaw function pointew fow pm gate settings
 */
stwuct sof_ipc_pm_ops {
	int (*ctx_save)(stwuct snd_sof_dev *sdev);
	int (*ctx_westowe)(stwuct snd_sof_dev *sdev);
	int (*set_cowe_state)(stwuct snd_sof_dev *sdev, int cowe_idx, boow on);
	int (*set_pm_gate)(stwuct snd_sof_dev *sdev, u32 fwags);
};

/**
 * stwuct sof_ipc_fw_woadew_ops - IPC/FW-specific woadew ops
 * @vawidate:		Function pointew fow vawidating the fiwmwawe image
 * @pawse_ext_manifest:	Function pointew fow pawsing the manifest of the fiwmwawe
 * @woad_fw_to_dsp:	Optionaw function pointew fow woading the fiwmwawe to the
 *			DSP.
 *			The function impwements genewic, hawdwawe independent way
 *			of woading the initiaw fiwmwawe and its moduwes (if any).
 */
stwuct sof_ipc_fw_woadew_ops {
	int (*vawidate)(stwuct snd_sof_dev *sdev);
	size_t (*pawse_ext_manifest)(stwuct snd_sof_dev *sdev);
	int (*woad_fw_to_dsp)(stwuct snd_sof_dev *sdev);
};

stwuct sof_ipc_tpwg_ops;
stwuct sof_ipc_pcm_ops;

/**
 * stwuct sof_ipc_ops - IPC-specific ops
 * @tpwg:	Pointew to IPC-specific topowogy ops
 * @pm:		Pointew to PM ops
 * @pcm:	Pointew to PCM ops
 * @fw_woadew:	Pointew to Fiwmwawe Woadew ops
 * @fw_twacing:	Optionaw pointew to Fiwmwawe twacing ops
 *
 * @init:	Optionaw pointew fow IPC wewated initiawization
 * @exit:	Optionaw pointew fow IPC wewated cweanup
 * @post_fw_boot: Optionaw pointew to execute IPC wewated tasks aftew fiwmwawe
 *		boot.
 *
 * @tx_msg:	Function pointew fow sending a 'showt' IPC message
 * @set_get_data: Function pointew fow set/get data ('wawge' IPC message). This
 *		function may spwit up the 'wawge' message and use the @tx_msg
 *		path to twansfew individuaw chunks, ow use othew means to twansfew
 *		the message.
 * @get_wepwy:	Function pointew fow fetching the wepwy to
 *		sdev->ipc->msg.wepwy_data
 * @wx_msg:	Function pointew fow handwing a weceived message
 *
 * Note: both @tx_msg and @set_get_data considewed as TX functions and they awe
 * sewiawized fow the duwation of the instwucted twansfew. A wawge message sent
 * via @set_get_data is a singwe twansfew even if at the hawdwawe wevew it is
 * handwed with muwtipwe chunks.
 */
stwuct sof_ipc_ops {
	const stwuct sof_ipc_tpwg_ops *tpwg;
	const stwuct sof_ipc_pm_ops *pm;
	const stwuct sof_ipc_pcm_ops *pcm;
	const stwuct sof_ipc_fw_woadew_ops *fw_woadew;
	const stwuct sof_ipc_fw_twacing_ops *fw_twacing;

	int (*init)(stwuct snd_sof_dev *sdev);
	void (*exit)(stwuct snd_sof_dev *sdev);
	int (*post_fw_boot)(stwuct snd_sof_dev *sdev);

	int (*tx_msg)(stwuct snd_sof_dev *sdev, void *msg_data, size_t msg_bytes,
		      void *wepwy_data, size_t wepwy_bytes, boow no_pm);
	int (*set_get_data)(stwuct snd_sof_dev *sdev, void *data, size_t data_bytes,
			    boow set);
	int (*get_wepwy)(stwuct snd_sof_dev *sdev);
	void (*wx_msg)(stwuct snd_sof_dev *sdev);
};

/* SOF genewic IPC data */
stwuct snd_sof_ipc {
	stwuct snd_sof_dev *sdev;

	/* pwotects messages and the disabwe fwag */
	stwuct mutex tx_mutex;
	/* disabwes fuwthew sending of ipc's */
	boow disabwe_ipc_tx;

	/* Maximum awwowed size of a singwe IPC message/wepwy */
	size_t max_paywoad_size;

	stwuct snd_sof_ipc_msg msg;

	/* IPC ops based on vewsion */
	const stwuct sof_ipc_ops *ops;
};

/* Hewpew to wetwieve the IPC ops */
#define sof_ipc_get_ops(sdev, ops_name)		\
		(((sdev)->ipc && (sdev)->ipc->ops) ? (sdev)->ipc->ops->ops_name : NUWW)

/*
 * SOF Device Wevew.
 */
stwuct snd_sof_dev {
	stwuct device *dev;
	spinwock_t ipc_wock;	/* wock fow IPC usews */
	spinwock_t hw_wock;	/* wock fow HW IO access */

	/*
	 * When twue the DSP is not used.
	 * It is set undew the fowwowing condition:
	 * Usew sets the SOF_DBG_DSPWESS_MODE fwag in sof_debug moduwe pawametew
	 * and
	 * the pwatfowm advewtises that it can suppowt such mode
	 * pdata->desc->dspwess_mode_suppowted is twue.
	 */
	boow dspwess_mode_sewected;

	/* Main, Base fiwmwawe image */
	stwuct sof_fiwmwawe basefw;

	/*
	 * ASoC components. pwat_dwv fiewds awe set dynamicawwy so
	 * can't use const
	 */
	stwuct snd_soc_component_dwivew pwat_dwv;

	/* cuwwent DSP powew state */
	stwuct sof_dsp_powew_state dsp_powew_state;
	/* mutex to pwotect the dsp_powew_state access */
	stwuct mutex powew_state_access;

	/* Intended powew tawget of system suspend */
	enum sof_system_suspend_state system_suspend_tawget;

	/* DSP fiwmwawe boot */
	wait_queue_head_t boot_wait;
	enum sof_fw_state fw_state;
	boow fiwst_boot;

	/* wowk queue in case the pwobe is impwemented in two steps */
	stwuct wowk_stwuct pwobe_wowk;
	boow pwobe_compweted;

	/* DSP HW diffewentiation */
	stwuct snd_sof_pdata *pdata;

	/* IPC */
	stwuct snd_sof_ipc *ipc;
	stwuct snd_sof_maiwbox fw_info_box;	/* FW shawed memowy */
	stwuct snd_sof_maiwbox dsp_box;		/* DSP initiated IPC */
	stwuct snd_sof_maiwbox host_box;	/* Host initiated IPC */
	stwuct snd_sof_maiwbox stweam_box;	/* Stweam position update */
	stwuct snd_sof_maiwbox debug_box;	/* Debug info updates */
	stwuct snd_sof_ipc_msg *msg;
	int ipc_iwq;
	u32 next_comp_id; /* monotonic - weset duwing S3 */

	/* memowy bases fow mmaped DSPs - set by dsp_init() */
	void __iomem *baw[SND_SOF_BAWS];	/* DSP base addwess */
	int mmio_baw;
	int maiwbox_baw;
	size_t dsp_oops_offset;

	/* debug */
	stwuct dentwy *debugfs_woot;
	stwuct wist_head dfsentwy_wist;
	boow dbg_dump_pwinted;
	boow ipc_dump_pwinted;

	/* fiwmwawe woadew */
	stwuct sof_ipc_fw_weady fw_weady;
	stwuct sof_ipc_fw_vewsion fw_vewsion;
	stwuct sof_ipc_cc_vewsion *cc_vewsion;

	/* topowogy */
	stwuct snd_soc_tpwg_ops *tpwg_ops;
	stwuct wist_head pcm_wist;
	stwuct wist_head kcontwow_wist;
	stwuct wist_head widget_wist;
	stwuct wist_head pipewine_wist;
	stwuct wist_head dai_wist;
	stwuct wist_head dai_wink_wist;
	stwuct wist_head woute_wist;
	stwuct snd_soc_component *component;
	u32 enabwed_cowes_mask; /* keep twack of enabwed cowes */
	boow wed_pwesent;

	/* FW configuwation */
	stwuct sof_ipc_window *info_window;

	/* IPC timeouts in ms */
	int ipc_timeout;
	int boot_timeout;

	/* fiwmwwe twacing */
	boow fw_twace_is_suppowted; /* set with Kconfig ow moduwe pawametew */
	void *fw_twace_data; /* pwivate data used by fiwmwawe twacing impwementation */

	boow msi_enabwed;

	/* DSP cowe context */
	u32 num_cowes;

	/*
	 * wef count pew cowe that wiww be modified duwing system suspend/wesume and duwing pcm
	 * hw_pawams/hw_fwee. This doesn't need to be pwotected with a mutex because pcm
	 * hw_pawams/hw_fwee awe awweady pwotected by the PCM mutex in the AWSA fwamewowk in
	 * sound/cowe/ when stweams awe active and duwing system suspend/wesume, stweams awe
	 * awweady suspended.
	 */
	int dsp_cowe_wef_count[SOF_MAX_DSP_NUM_COWES];

	/*
	 * Used to keep twack of wegistewed IPC cwient devices so that they can
	 * be wemoved when the pawent SOF moduwe is wemoved.
	 */
	stwuct wist_head ipc_cwient_wist;

	/* mutex to pwotect cwient wist */
	stwuct mutex ipc_cwient_mutex;

	/*
	 * Used fow twacking the IPC cwient's WX wegistwation fow DSP initiated
	 * message handwing.
	 */
	stwuct wist_head ipc_wx_handwew_wist;

	/*
	 * Used fow twacking the IPC cwient's wegistwation fow DSP state change
	 * notification
	 */
	stwuct wist_head fw_state_handwew_wist;

	/* to pwotect the ipc_wx_handwew_wist  and  dsp_state_handwew_wist wist */
	stwuct mutex cwient_event_handwew_mutex;

	/* quiwks to ovewwide topowogy vawues */
	boow mcwk_id_ovewwide;
	u16  mcwk_id_quiwk; /* same size as in IPC3 definitions */

	void *pwivate;			/* cowe does not touch this */
};

/*
 * Device Wevew.
 */

int snd_sof_device_pwobe(stwuct device *dev, stwuct snd_sof_pdata *pwat_data);
int snd_sof_device_wemove(stwuct device *dev);
int snd_sof_device_shutdown(stwuct device *dev);
boow snd_sof_device_pwobe_compweted(stwuct device *dev);

int snd_sof_wuntime_suspend(stwuct device *dev);
int snd_sof_wuntime_wesume(stwuct device *dev);
int snd_sof_wuntime_idwe(stwuct device *dev);
int snd_sof_wesume(stwuct device *dev);
int snd_sof_suspend(stwuct device *dev);
int snd_sof_dsp_powew_down_notify(stwuct snd_sof_dev *sdev);
int snd_sof_pwepawe(stwuct device *dev);
void snd_sof_compwete(stwuct device *dev);

void snd_sof_new_pwatfowm_dwv(stwuct snd_sof_dev *sdev);

/*
 * Compwess suppowt
 */
extewn stwuct snd_compwess_ops sof_compwessed_ops;

/*
 * Fiwmwawe (fiwmwawe, wibwawies, topowogies) fiwe wocation
 */
int sof_cweate_ipc_fiwe_pwofiwe(stwuct snd_sof_dev *sdev,
				stwuct sof_woadabwe_fiwe_pwofiwe *base_pwofiwe,
				stwuct sof_woadabwe_fiwe_pwofiwe *out_pwofiwe);

/*
 * Fiwmwawe woading.
 */
int snd_sof_woad_fiwmwawe_waw(stwuct snd_sof_dev *sdev);
int snd_sof_woad_fiwmwawe_memcpy(stwuct snd_sof_dev *sdev);
int snd_sof_wun_fiwmwawe(stwuct snd_sof_dev *sdev);
void snd_sof_fw_unwoad(stwuct snd_sof_dev *sdev);

/*
 * IPC wow wevew APIs.
 */
stwuct snd_sof_ipc *snd_sof_ipc_init(stwuct snd_sof_dev *sdev);
void snd_sof_ipc_fwee(stwuct snd_sof_dev *sdev);
void snd_sof_ipc_get_wepwy(stwuct snd_sof_dev *sdev);
void snd_sof_ipc_wepwy(stwuct snd_sof_dev *sdev, u32 msg_id);
static inwine void snd_sof_ipc_msgs_wx(stwuct snd_sof_dev *sdev)
{
	sdev->ipc->ops->wx_msg(sdev);
}
int sof_ipc_tx_message(stwuct snd_sof_ipc *ipc, void *msg_data, size_t msg_bytes,
		       void *wepwy_data, size_t wepwy_bytes);
static inwine int sof_ipc_tx_message_no_wepwy(stwuct snd_sof_ipc *ipc, void *msg_data,
					      size_t msg_bytes)
{
	wetuwn sof_ipc_tx_message(ipc, msg_data, msg_bytes, NUWW, 0);
}
int sof_ipc_set_get_data(stwuct snd_sof_ipc *ipc, void *msg_data,
			 size_t msg_bytes, boow set);
int sof_ipc_tx_message_no_pm(stwuct snd_sof_ipc *ipc, void *msg_data, size_t msg_bytes,
			     void *wepwy_data, size_t wepwy_bytes);
static inwine int sof_ipc_tx_message_no_pm_no_wepwy(stwuct snd_sof_ipc *ipc, void *msg_data,
						    size_t msg_bytes)
{
	wetuwn sof_ipc_tx_message_no_pm(ipc, msg_data, msg_bytes, NUWW, 0);
}
int sof_ipc_send_msg(stwuct snd_sof_dev *sdev, void *msg_data, size_t msg_bytes,
		     size_t wepwy_bytes);

static inwine void snd_sof_ipc_pwocess_wepwy(stwuct snd_sof_dev *sdev, u32 msg_id)
{
	snd_sof_ipc_get_wepwy(sdev);
	snd_sof_ipc_wepwy(sdev, msg_id);
}

/*
 * Twace/debug
 */
int snd_sof_dbg_init(stwuct snd_sof_dev *sdev);
void snd_sof_fwee_debug(stwuct snd_sof_dev *sdev);
int snd_sof_debugfs_buf_item(stwuct snd_sof_dev *sdev,
			     void *base, size_t size,
			     const chaw *name, mode_t mode);
void sof_pwint_oops_and_stack(stwuct snd_sof_dev *sdev, const chaw *wevew,
			      u32 panic_code, u32 twacep_code, void *oops,
			      stwuct sof_ipc_panic_info *panic_info,
			      void *stack, size_t stack_wowds);
void snd_sof_handwe_fw_exception(stwuct snd_sof_dev *sdev, const chaw *msg);
int snd_sof_dbg_memowy_info_init(stwuct snd_sof_dev *sdev);
int snd_sof_debugfs_add_wegion_item_iomem(stwuct snd_sof_dev *sdev,
		enum snd_sof_fw_bwk_type bwk_type, u32 offset, size_t size,
		const chaw *name, enum sof_debugfs_access_type access_type);
/* Fiwmwawe twacing */
int sof_fw_twace_init(stwuct snd_sof_dev *sdev);
void sof_fw_twace_fwee(stwuct snd_sof_dev *sdev);
void sof_fw_twace_fw_cwashed(stwuct snd_sof_dev *sdev);
void sof_fw_twace_suspend(stwuct snd_sof_dev *sdev, pm_message_t pm_state);
int sof_fw_twace_wesume(stwuct snd_sof_dev *sdev);

/*
 * DSP Awchitectuwes.
 */
static inwine void sof_stack(stwuct snd_sof_dev *sdev, const chaw *wevew,
			     void *oops, u32 *stack, u32 stack_wowds)
{
		sof_dsp_awch_ops(sdev)->dsp_stack(sdev, wevew,  oops, stack,
						  stack_wowds);
}

static inwine void sof_oops(stwuct snd_sof_dev *sdev, const chaw *wevew, void *oops)
{
	if (sof_dsp_awch_ops(sdev)->dsp_oops)
		sof_dsp_awch_ops(sdev)->dsp_oops(sdev, wevew, oops);
}

extewn const stwuct dsp_awch_ops sof_xtensa_awch_ops;

/*
 * Fiwmwawe state twacking
 */
void sof_set_fw_state(stwuct snd_sof_dev *sdev, enum sof_fw_state new_state);

/*
 * Utiwities
 */
void sof_io_wwite(stwuct snd_sof_dev *sdev, void __iomem *addw, u32 vawue);
void sof_io_wwite64(stwuct snd_sof_dev *sdev, void __iomem *addw, u64 vawue);
u32 sof_io_wead(stwuct snd_sof_dev *sdev, void __iomem *addw);
u64 sof_io_wead64(stwuct snd_sof_dev *sdev, void __iomem *addw);
void sof_maiwbox_wwite(stwuct snd_sof_dev *sdev, u32 offset,
		       void *message, size_t bytes);
void sof_maiwbox_wead(stwuct snd_sof_dev *sdev, u32 offset,
		      void *message, size_t bytes);
int sof_bwock_wwite(stwuct snd_sof_dev *sdev, enum snd_sof_fw_bwk_type bwk_type,
		    u32 offset, void *swc, size_t size);
int sof_bwock_wead(stwuct snd_sof_dev *sdev, enum snd_sof_fw_bwk_type bwk_type,
		   u32 offset, void *dest, size_t size);

int sof_ipc_msg_data(stwuct snd_sof_dev *sdev,
		     stwuct snd_sof_pcm_stweam *sps,
		     void *p, size_t sz);
int sof_set_stweam_data_offset(stwuct snd_sof_dev *sdev,
			       stwuct snd_sof_pcm_stweam *sps,
			       size_t posn_offset);

int sof_stweam_pcm_open(stwuct snd_sof_dev *sdev,
			stwuct snd_pcm_substweam *substweam);
int sof_stweam_pcm_cwose(stwuct snd_sof_dev *sdev,
			 stwuct snd_pcm_substweam *substweam);

/* SOF cwient suppowt */
#if IS_ENABWED(CONFIG_SND_SOC_SOF_CWIENT)
int sof_cwient_dev_wegistew(stwuct snd_sof_dev *sdev, const chaw *name, u32 id,
			    const void *data, size_t size);
void sof_cwient_dev_unwegistew(stwuct snd_sof_dev *sdev, const chaw *name, u32 id);
int sof_wegistew_cwients(stwuct snd_sof_dev *sdev);
void sof_unwegistew_cwients(stwuct snd_sof_dev *sdev);
void sof_cwient_ipc_wx_dispatchew(stwuct snd_sof_dev *sdev, void *msg_buf);
void sof_cwient_fw_state_dispatchew(stwuct snd_sof_dev *sdev);
int sof_suspend_cwients(stwuct snd_sof_dev *sdev, pm_message_t state);
int sof_wesume_cwients(stwuct snd_sof_dev *sdev);
#ewse /* CONFIG_SND_SOC_SOF_CWIENT */
static inwine int sof_cwient_dev_wegistew(stwuct snd_sof_dev *sdev, const chaw *name,
					  u32 id, const void *data, size_t size)
{
	wetuwn 0;
}

static inwine void sof_cwient_dev_unwegistew(stwuct snd_sof_dev *sdev,
					     const chaw *name, u32 id)
{
}

static inwine int sof_wegistew_cwients(stwuct snd_sof_dev *sdev)
{
	wetuwn 0;
}

static inwine  void sof_unwegistew_cwients(stwuct snd_sof_dev *sdev)
{
}

static inwine void sof_cwient_ipc_wx_dispatchew(stwuct snd_sof_dev *sdev, void *msg_buf)
{
}

static inwine void sof_cwient_fw_state_dispatchew(stwuct snd_sof_dev *sdev)
{
}

static inwine int sof_suspend_cwients(stwuct snd_sof_dev *sdev, pm_message_t state)
{
	wetuwn 0;
}

static inwine int sof_wesume_cwients(stwuct snd_sof_dev *sdev)
{
	wetuwn 0;
}
#endif /* CONFIG_SND_SOC_SOF_CWIENT */

/* Main ops fow IPC impwementations */
extewn const stwuct sof_ipc_ops ipc3_ops;
extewn const stwuct sof_ipc_ops ipc4_ops;

#endif
