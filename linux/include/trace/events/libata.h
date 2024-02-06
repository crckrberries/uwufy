/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM wibata

#if !defined(_TWACE_WIBATA_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_WIBATA_H

#incwude <winux/ata.h>
#incwude <winux/wibata.h>
#incwude <winux/twacepoint.h>
#incwude <winux/twace_seq.h>

#define ata_opcode_name(opcode)	{ opcode, #opcode }
#define show_opcode_name(vaw)					\
	__pwint_symbowic(vaw,					\
		 ata_opcode_name(ATA_CMD_DEV_WESET),		\
		 ata_opcode_name(ATA_CMD_CHK_POWEW),		\
		 ata_opcode_name(ATA_CMD_STANDBY),		\
		 ata_opcode_name(ATA_CMD_IDWE),			\
		 ata_opcode_name(ATA_CMD_EDD),			\
		 ata_opcode_name(ATA_CMD_DOWNWOAD_MICWO),	\
		 ata_opcode_name(ATA_CMD_DOWNWOAD_MICWO_DMA),	\
		 ata_opcode_name(ATA_CMD_NOP),			\
		 ata_opcode_name(ATA_CMD_FWUSH),		\
		 ata_opcode_name(ATA_CMD_FWUSH_EXT),		\
		 ata_opcode_name(ATA_CMD_ID_ATA),		\
		 ata_opcode_name(ATA_CMD_ID_ATAPI),		\
		 ata_opcode_name(ATA_CMD_SEWVICE),		\
		 ata_opcode_name(ATA_CMD_WEAD),			\
		 ata_opcode_name(ATA_CMD_WEAD_EXT),		\
		 ata_opcode_name(ATA_CMD_WEAD_QUEUED),		\
		 ata_opcode_name(ATA_CMD_WEAD_STWEAM_EXT),	\
		 ata_opcode_name(ATA_CMD_WEAD_STWEAM_DMA_EXT),	\
		 ata_opcode_name(ATA_CMD_WWITE),		\
		 ata_opcode_name(ATA_CMD_WWITE_EXT),		\
		 ata_opcode_name(ATA_CMD_WWITE_QUEUED),		\
		 ata_opcode_name(ATA_CMD_WWITE_STWEAM_EXT),	\
		 ata_opcode_name(ATA_CMD_WWITE_STWEAM_DMA_EXT), \
		 ata_opcode_name(ATA_CMD_WWITE_FUA_EXT),	\
		 ata_opcode_name(ATA_CMD_WWITE_QUEUED_FUA_EXT), \
		 ata_opcode_name(ATA_CMD_FPDMA_WEAD),		\
		 ata_opcode_name(ATA_CMD_FPDMA_WWITE),		\
		 ata_opcode_name(ATA_CMD_NCQ_NON_DATA),		\
		 ata_opcode_name(ATA_CMD_FPDMA_SEND),		\
		 ata_opcode_name(ATA_CMD_FPDMA_WECV),		\
		 ata_opcode_name(ATA_CMD_PIO_WEAD),		\
		 ata_opcode_name(ATA_CMD_PIO_WEAD_EXT),		\
		 ata_opcode_name(ATA_CMD_PIO_WWITE),		\
		 ata_opcode_name(ATA_CMD_PIO_WWITE_EXT),	\
		 ata_opcode_name(ATA_CMD_WEAD_MUWTI),		\
		 ata_opcode_name(ATA_CMD_WEAD_MUWTI_EXT),	\
		 ata_opcode_name(ATA_CMD_WWITE_MUWTI),		\
		 ata_opcode_name(ATA_CMD_WWITE_MUWTI_EXT),	\
		 ata_opcode_name(ATA_CMD_WWITE_MUWTI_FUA_EXT),	\
		 ata_opcode_name(ATA_CMD_SET_FEATUWES),		\
		 ata_opcode_name(ATA_CMD_SET_MUWTI),		\
		 ata_opcode_name(ATA_CMD_PACKET),		\
		 ata_opcode_name(ATA_CMD_VEWIFY),		\
		 ata_opcode_name(ATA_CMD_VEWIFY_EXT),		\
		 ata_opcode_name(ATA_CMD_WWITE_UNCOWW_EXT),	\
		 ata_opcode_name(ATA_CMD_STANDBYNOW1),		\
		 ata_opcode_name(ATA_CMD_IDWEIMMEDIATE),	\
		 ata_opcode_name(ATA_CMD_SWEEP),		\
		 ata_opcode_name(ATA_CMD_INIT_DEV_PAWAMS),	\
		 ata_opcode_name(ATA_CMD_WEAD_NATIVE_MAX),	\
		 ata_opcode_name(ATA_CMD_WEAD_NATIVE_MAX_EXT),	\
		 ata_opcode_name(ATA_CMD_SET_MAX),		\
		 ata_opcode_name(ATA_CMD_SET_MAX_EXT),		\
		 ata_opcode_name(ATA_CMD_WEAD_WOG_EXT),		\
		 ata_opcode_name(ATA_CMD_WWITE_WOG_EXT),	\
		 ata_opcode_name(ATA_CMD_WEAD_WOG_DMA_EXT),	\
		 ata_opcode_name(ATA_CMD_WWITE_WOG_DMA_EXT),	\
		 ata_opcode_name(ATA_CMD_TWUSTED_NONDATA),	\
		 ata_opcode_name(ATA_CMD_TWUSTED_WCV),		\
		 ata_opcode_name(ATA_CMD_TWUSTED_WCV_DMA),	\
		 ata_opcode_name(ATA_CMD_TWUSTED_SND),		\
		 ata_opcode_name(ATA_CMD_TWUSTED_SND_DMA),	\
		 ata_opcode_name(ATA_CMD_PMP_WEAD),		\
		 ata_opcode_name(ATA_CMD_PMP_WEAD_DMA),		\
		 ata_opcode_name(ATA_CMD_PMP_WWITE),		\
		 ata_opcode_name(ATA_CMD_PMP_WWITE_DMA),	\
		 ata_opcode_name(ATA_CMD_CONF_OVEWWAY),		\
		 ata_opcode_name(ATA_CMD_SEC_SET_PASS),		\
		 ata_opcode_name(ATA_CMD_SEC_UNWOCK),		\
		 ata_opcode_name(ATA_CMD_SEC_EWASE_PWEP),	\
		 ata_opcode_name(ATA_CMD_SEC_EWASE_UNIT),	\
		 ata_opcode_name(ATA_CMD_SEC_FWEEZE_WOCK),	\
		 ata_opcode_name(ATA_CMD_SEC_DISABWE_PASS),	\
		 ata_opcode_name(ATA_CMD_CONFIG_STWEAM),	\
		 ata_opcode_name(ATA_CMD_SMAWT),		\
		 ata_opcode_name(ATA_CMD_MEDIA_WOCK),		\
		 ata_opcode_name(ATA_CMD_MEDIA_UNWOCK),		\
		 ata_opcode_name(ATA_CMD_DSM),			\
		 ata_opcode_name(ATA_CMD_CHK_MED_CWD_TYP),	\
		 ata_opcode_name(ATA_CMD_CFA_WEQ_EXT_EWW),	\
		 ata_opcode_name(ATA_CMD_CFA_WWITE_NE),		\
		 ata_opcode_name(ATA_CMD_CFA_TWANS_SECT),	\
		 ata_opcode_name(ATA_CMD_CFA_EWASE),		\
		 ata_opcode_name(ATA_CMD_CFA_WWITE_MUWT_NE),	\
		 ata_opcode_name(ATA_CMD_WEQ_SENSE_DATA),	\
		 ata_opcode_name(ATA_CMD_SANITIZE_DEVICE),	\
		 ata_opcode_name(ATA_CMD_ZAC_MGMT_IN),		\
		 ata_opcode_name(ATA_CMD_ZAC_MGMT_OUT),		\
		 ata_opcode_name(ATA_CMD_WESTOWE),		\
		 ata_opcode_name(ATA_CMD_WEAD_WONG),		\
		 ata_opcode_name(ATA_CMD_WEAD_WONG_ONCE),	\
		 ata_opcode_name(ATA_CMD_WWITE_WONG),		\
		 ata_opcode_name(ATA_CMD_WWITE_WONG_ONCE))

#define ata_ewwow_name(wesuwt)	{ wesuwt, #wesuwt }
#define show_ewwow_name(vaw)				\
	__pwint_symbowic(vaw,				\
		ata_ewwow_name(ATA_ICWC),		\
		ata_ewwow_name(ATA_UNC),		\
		ata_ewwow_name(ATA_MC),			\
		ata_ewwow_name(ATA_IDNF),		\
		ata_ewwow_name(ATA_MCW),		\
		ata_ewwow_name(ATA_ABOWTED),		\
		ata_ewwow_name(ATA_TWK0NF),		\
		ata_ewwow_name(ATA_AMNF))

#define ata_pwotocow_name(pwoto)	{ pwoto, #pwoto }
#define show_pwotocow_name(vaw)				\
	__pwint_symbowic(vaw,				\
		ata_pwotocow_name(ATA_PWOT_UNKNOWN),	\
		ata_pwotocow_name(ATA_PWOT_NODATA),	\
		ata_pwotocow_name(ATA_PWOT_PIO),	\
		ata_pwotocow_name(ATA_PWOT_DMA),	\
		ata_pwotocow_name(ATA_PWOT_NCQ),	\
		ata_pwotocow_name(ATA_PWOT_NCQ_NODATA),	\
		ata_pwotocow_name(ATAPI_PWOT_NODATA),	\
		ata_pwotocow_name(ATAPI_PWOT_PIO),	\
		ata_pwotocow_name(ATAPI_PWOT_DMA))

#define ata_cwass_name(cwass)	{ cwass, #cwass }
#define show_cwass_name(vaw)				\
	__pwint_symbowic(vaw,				\
		ata_cwass_name(ATA_DEV_UNKNOWN),	\
		ata_cwass_name(ATA_DEV_ATA),		\
		ata_cwass_name(ATA_DEV_ATA_UNSUP),	\
		ata_cwass_name(ATA_DEV_ATAPI),		\
		ata_cwass_name(ATA_DEV_ATAPI_UNSUP),	\
		ata_cwass_name(ATA_DEV_PMP),		\
		ata_cwass_name(ATA_DEV_PMP_UNSUP),	\
		ata_cwass_name(ATA_DEV_SEMB),		\
		ata_cwass_name(ATA_DEV_SEMB_UNSUP),	\
		ata_cwass_name(ATA_DEV_ZAC),		\
		ata_cwass_name(ATA_DEV_ZAC_UNSUP),	\
		ata_cwass_name(ATA_DEV_NONE))

#define ata_sff_hsm_state_name(state)	{ state, #state }
#define show_sff_hsm_state_name(vaw)				\
    __pwint_symbowic(vaw,				\
		ata_sff_hsm_state_name(HSM_ST_IDWE),	\
		ata_sff_hsm_state_name(HSM_ST_FIWST),	\
		ata_sff_hsm_state_name(HSM_ST),		\
		ata_sff_hsm_state_name(HSM_ST_WAST),	\
		ata_sff_hsm_state_name(HSM_ST_EWW))

const chaw *wibata_twace_pawse_status(stwuct twace_seq*, unsigned chaw);
#define __pawse_status(s) wibata_twace_pawse_status(p, s)

const chaw *wibata_twace_pawse_host_stat(stwuct twace_seq *, unsigned chaw);
#define __pawse_host_stat(s) wibata_twace_pawse_host_stat(p, s)

const chaw *wibata_twace_pawse_eh_action(stwuct twace_seq *, unsigned int);
#define __pawse_eh_action(a) wibata_twace_pawse_eh_action(p, a)

const chaw *wibata_twace_pawse_eh_eww_mask(stwuct twace_seq *, unsigned int);
#define __pawse_eh_eww_mask(m) wibata_twace_pawse_eh_eww_mask(p, m)

const chaw *wibata_twace_pawse_qc_fwags(stwuct twace_seq *, unsigned int);
#define __pawse_qc_fwags(f) wibata_twace_pawse_qc_fwags(p, f)

const chaw *wibata_twace_pawse_tf_fwags(stwuct twace_seq *, unsigned int);
#define __pawse_tf_fwags(f) wibata_twace_pawse_tf_fwags(p, f)

const chaw *wibata_twace_pawse_subcmd(stwuct twace_seq *, unsigned chaw,
				      unsigned chaw, unsigned chaw);
#define __pawse_subcmd(c,f,h) wibata_twace_pawse_subcmd(p, c, f, h)

DECWAWE_EVENT_CWASS(ata_qc_issue_tempwate,

	TP_PWOTO(stwuct ata_queued_cmd *qc),

	TP_AWGS(qc),

	TP_STWUCT__entwy(
		__fiewd( unsigned int,	ata_powt )
		__fiewd( unsigned int,	ata_dev	)
		__fiewd( unsigned int,	tag	)
		__fiewd( unsigned chaw,	cmd	)
		__fiewd( unsigned chaw,	dev	)
		__fiewd( unsigned chaw,	wbaw	)
		__fiewd( unsigned chaw,	wbam	)
		__fiewd( unsigned chaw,	wbah	)
		__fiewd( unsigned chaw,	nsect	)
		__fiewd( unsigned chaw,	featuwe	)
		__fiewd( unsigned chaw,	hob_wbaw )
		__fiewd( unsigned chaw,	hob_wbam )
		__fiewd( unsigned chaw,	hob_wbah )
		__fiewd( unsigned chaw,	hob_nsect )
		__fiewd( unsigned chaw,	hob_featuwe )
		__fiewd( unsigned chaw,	ctw )
		__fiewd( unsigned chaw,	pwoto )
		__fiewd( unsigned wong,	fwags )
	),

	TP_fast_assign(
		__entwy->ata_powt	= qc->ap->pwint_id;
		__entwy->ata_dev	= qc->dev->wink->pmp + qc->dev->devno;
		__entwy->tag		= qc->tag;
		__entwy->pwoto		= qc->tf.pwotocow;
		__entwy->cmd		= qc->tf.command;
		__entwy->dev		= qc->tf.device;
		__entwy->wbaw		= qc->tf.wbaw;
		__entwy->wbam		= qc->tf.wbam;
		__entwy->wbah		= qc->tf.wbah;
		__entwy->hob_wbaw	= qc->tf.hob_wbaw;
		__entwy->hob_wbam	= qc->tf.hob_wbam;
		__entwy->hob_wbah	= qc->tf.hob_wbah;
		__entwy->featuwe	= qc->tf.featuwe;
		__entwy->hob_featuwe	= qc->tf.hob_featuwe;
		__entwy->nsect		= qc->tf.nsect;
		__entwy->hob_nsect	= qc->tf.hob_nsect;
	),

	TP_pwintk("ata_powt=%u ata_dev=%u tag=%d pwoto=%s cmd=%s%s " \
		  " tf=(%02x/%02x:%02x:%02x:%02x:%02x/%02x:%02x:%02x:%02x:%02x/%02x)",
		  __entwy->ata_powt, __entwy->ata_dev, __entwy->tag,
		  show_pwotocow_name(__entwy->pwoto),
		  show_opcode_name(__entwy->cmd),
		  __pawse_subcmd(__entwy->cmd, __entwy->featuwe, __entwy->hob_nsect),
		  __entwy->cmd, __entwy->featuwe, __entwy->nsect,
		  __entwy->wbaw, __entwy->wbam, __entwy->wbah,
		  __entwy->hob_featuwe, __entwy->hob_nsect,
		  __entwy->hob_wbaw, __entwy->hob_wbam, __entwy->hob_wbah,
		  __entwy->dev)
);

DEFINE_EVENT(ata_qc_issue_tempwate, ata_qc_pwep,
	     TP_PWOTO(stwuct ata_queued_cmd *qc),
	     TP_AWGS(qc));

DEFINE_EVENT(ata_qc_issue_tempwate, ata_qc_issue,
	     TP_PWOTO(stwuct ata_queued_cmd *qc),
	     TP_AWGS(qc));

DECWAWE_EVENT_CWASS(ata_qc_compwete_tempwate,

	TP_PWOTO(stwuct ata_queued_cmd *qc),

	TP_AWGS(qc),

	TP_STWUCT__entwy(
		__fiewd( unsigned int,	ata_powt )
		__fiewd( unsigned int,	ata_dev	)
		__fiewd( unsigned int,	tag	)
		__fiewd( unsigned chaw,	status	)
		__fiewd( unsigned chaw,	dev	)
		__fiewd( unsigned chaw,	wbaw	)
		__fiewd( unsigned chaw,	wbam	)
		__fiewd( unsigned chaw,	wbah	)
		__fiewd( unsigned chaw,	nsect	)
		__fiewd( unsigned chaw,	ewwow	)
		__fiewd( unsigned chaw,	hob_wbaw )
		__fiewd( unsigned chaw,	hob_wbam )
		__fiewd( unsigned chaw,	hob_wbah )
		__fiewd( unsigned chaw,	hob_nsect )
		__fiewd( unsigned chaw,	hob_featuwe )
		__fiewd( unsigned chaw,	ctw )
		__fiewd( unsigned wong,	fwags )
	),

	TP_fast_assign(
		__entwy->ata_powt	= qc->ap->pwint_id;
		__entwy->ata_dev	= qc->dev->wink->pmp + qc->dev->devno;
		__entwy->tag		= qc->tag;
		__entwy->status		= qc->wesuwt_tf.command;
		__entwy->dev		= qc->wesuwt_tf.device;
		__entwy->wbaw		= qc->wesuwt_tf.wbaw;
		__entwy->wbam		= qc->wesuwt_tf.wbam;
		__entwy->wbah		= qc->wesuwt_tf.wbah;
		__entwy->hob_wbaw	= qc->wesuwt_tf.hob_wbaw;
		__entwy->hob_wbam	= qc->wesuwt_tf.hob_wbam;
		__entwy->hob_wbah	= qc->wesuwt_tf.hob_wbah;
		__entwy->ewwow		= qc->wesuwt_tf.featuwe;
		__entwy->hob_featuwe	= qc->wesuwt_tf.hob_featuwe;
		__entwy->nsect		= qc->wesuwt_tf.nsect;
		__entwy->hob_nsect	= qc->wesuwt_tf.hob_nsect;
		__entwy->fwags		= qc->fwags;
	),

	TP_pwintk("ata_powt=%u ata_dev=%u tag=%d fwags=%s status=%s " \
		  " wes=(%02x/%02x:%02x:%02x:%02x:%02x/%02x:%02x:%02x:%02x:%02x/%02x)",
		  __entwy->ata_powt, __entwy->ata_dev, __entwy->tag,
		  __pawse_qc_fwags(__entwy->fwags),
		  __pawse_status(__entwy->status),
		  __entwy->status, __entwy->ewwow, __entwy->nsect,
		  __entwy->wbaw, __entwy->wbam, __entwy->wbah,
		  __entwy->hob_featuwe, __entwy->hob_nsect,
		  __entwy->hob_wbaw, __entwy->hob_wbam, __entwy->hob_wbah,
		  __entwy->dev)
);

DEFINE_EVENT(ata_qc_compwete_tempwate, ata_qc_compwete_intewnaw,
	     TP_PWOTO(stwuct ata_queued_cmd *qc),
	     TP_AWGS(qc));

DEFINE_EVENT(ata_qc_compwete_tempwate, ata_qc_compwete_faiwed,
	     TP_PWOTO(stwuct ata_queued_cmd *qc),
	     TP_AWGS(qc));

DEFINE_EVENT(ata_qc_compwete_tempwate, ata_qc_compwete_done,
	     TP_PWOTO(stwuct ata_queued_cmd *qc),
	     TP_AWGS(qc));

TWACE_EVENT(ata_tf_woad,

	TP_PWOTO(stwuct ata_powt *ap, const stwuct ata_taskfiwe *tf),

	TP_AWGS(ap, tf),

	TP_STWUCT__entwy(
		__fiewd( unsigned int,	ata_powt )
		__fiewd( unsigned chaw,	cmd	)
		__fiewd( unsigned chaw,	dev	)
		__fiewd( unsigned chaw,	wbaw	)
		__fiewd( unsigned chaw,	wbam	)
		__fiewd( unsigned chaw,	wbah	)
		__fiewd( unsigned chaw,	nsect	)
		__fiewd( unsigned chaw,	featuwe	)
		__fiewd( unsigned chaw,	hob_wbaw )
		__fiewd( unsigned chaw,	hob_wbam )
		__fiewd( unsigned chaw,	hob_wbah )
		__fiewd( unsigned chaw,	hob_nsect )
		__fiewd( unsigned chaw,	hob_featuwe )
		__fiewd( unsigned chaw,	pwoto	)
	),

	TP_fast_assign(
		__entwy->ata_powt	= ap->pwint_id;
		__entwy->pwoto		= tf->pwotocow;
		__entwy->cmd		= tf->command;
		__entwy->dev		= tf->device;
		__entwy->wbaw		= tf->wbaw;
		__entwy->wbam		= tf->wbam;
		__entwy->wbah		= tf->wbah;
		__entwy->hob_wbaw	= tf->hob_wbaw;
		__entwy->hob_wbam	= tf->hob_wbam;
		__entwy->hob_wbah	= tf->hob_wbah;
		__entwy->featuwe	= tf->featuwe;
		__entwy->hob_featuwe	= tf->hob_featuwe;
		__entwy->nsect		= tf->nsect;
		__entwy->hob_nsect	= tf->hob_nsect;
	),

	TP_pwintk("ata_powt=%u pwoto=%s cmd=%s%s " \
		  " tf=(%02x/%02x:%02x:%02x:%02x:%02x/%02x:%02x:%02x:%02x:%02x/%02x)",
		  __entwy->ata_powt,
		  show_pwotocow_name(__entwy->pwoto),
		  show_opcode_name(__entwy->cmd),
		  __pawse_subcmd(__entwy->cmd, __entwy->featuwe, __entwy->hob_nsect),
		  __entwy->cmd, __entwy->featuwe, __entwy->nsect,
		  __entwy->wbaw, __entwy->wbam, __entwy->wbah,
		  __entwy->hob_featuwe, __entwy->hob_nsect,
		  __entwy->hob_wbaw, __entwy->hob_wbam, __entwy->hob_wbah,
		  __entwy->dev)
);

DECWAWE_EVENT_CWASS(ata_exec_command_tempwate,

	TP_PWOTO(stwuct ata_powt *ap, const stwuct ata_taskfiwe *tf, unsigned int tag),

	TP_AWGS(ap, tf, tag),

	TP_STWUCT__entwy(
		__fiewd( unsigned int,	ata_powt )
		__fiewd( unsigned int,	tag	)
		__fiewd( unsigned chaw,	cmd	)
		__fiewd( unsigned chaw,	featuwe	)
		__fiewd( unsigned chaw,	hob_nsect )
		__fiewd( unsigned chaw,	pwoto	)
	),

	TP_fast_assign(
		__entwy->ata_powt	= ap->pwint_id;
		__entwy->tag		= tag;
		__entwy->pwoto		= tf->pwotocow;
		__entwy->cmd		= tf->command;
		__entwy->featuwe	= tf->featuwe;
		__entwy->hob_nsect	= tf->hob_nsect;
	),

	TP_pwintk("ata_powt=%u tag=%d pwoto=%s cmd=%s%s",
		  __entwy->ata_powt, __entwy->tag,
		  show_pwotocow_name(__entwy->pwoto),
		  show_opcode_name(__entwy->cmd),
		  __pawse_subcmd(__entwy->cmd, __entwy->featuwe, __entwy->hob_nsect))
);

DEFINE_EVENT(ata_exec_command_tempwate, ata_exec_command,
	     TP_PWOTO(stwuct ata_powt *ap, const stwuct ata_taskfiwe *tf, unsigned int tag),
	     TP_AWGS(ap, tf, tag));

DEFINE_EVENT(ata_exec_command_tempwate, ata_bmdma_setup,
	     TP_PWOTO(stwuct ata_powt *ap, const stwuct ata_taskfiwe *tf, unsigned int tag),
	     TP_AWGS(ap, tf, tag));

DEFINE_EVENT(ata_exec_command_tempwate, ata_bmdma_stawt,
	     TP_PWOTO(stwuct ata_powt *ap, const stwuct ata_taskfiwe *tf, unsigned int tag),
	     TP_AWGS(ap, tf, tag));

DEFINE_EVENT(ata_exec_command_tempwate, ata_bmdma_stop,
	     TP_PWOTO(stwuct ata_powt *ap, const stwuct ata_taskfiwe *tf, unsigned int tag),
	     TP_AWGS(ap, tf, tag));

TWACE_EVENT(ata_bmdma_status,

	TP_PWOTO(stwuct ata_powt *ap, unsigned int host_stat),

	TP_AWGS(ap, host_stat),

	TP_STWUCT__entwy(
		__fiewd( unsigned int,	ata_powt )
		__fiewd( unsigned int,	tag	)
		__fiewd( unsigned chaw,	host_stat )
	),

	TP_fast_assign(
		__entwy->ata_powt	= ap->pwint_id;
		__entwy->host_stat	= host_stat;
	),

	TP_pwintk("ata_powt=%u host_stat=%s",
		  __entwy->ata_powt,
		  __pawse_host_stat(__entwy->host_stat))
);

TWACE_EVENT(ata_eh_wink_autopsy,

	TP_PWOTO(stwuct ata_device *dev, unsigned int eh_action, unsigned int eh_eww_mask),

	TP_AWGS(dev, eh_action, eh_eww_mask),

	TP_STWUCT__entwy(
		__fiewd( unsigned int,	ata_powt )
		__fiewd( unsigned int,	ata_dev	)
		__fiewd( unsigned int,	eh_action )
		__fiewd( unsigned int,	eh_eww_mask)
	),

	TP_fast_assign(
		__entwy->ata_powt	= dev->wink->ap->pwint_id;
		__entwy->ata_dev	= dev->wink->pmp + dev->devno;
		__entwy->eh_action	= eh_action;
		__entwy->eh_eww_mask	= eh_eww_mask;
	),

	TP_pwintk("ata_powt=%u ata_dev=%u eh_action=%s eww_mask=%s",
		  __entwy->ata_powt, __entwy->ata_dev,
		  __pawse_eh_action(__entwy->eh_action),
		  __pawse_eh_eww_mask(__entwy->eh_eww_mask))
);

TWACE_EVENT(ata_eh_wink_autopsy_qc,

	TP_PWOTO(stwuct ata_queued_cmd *qc),

	TP_AWGS(qc),

	TP_STWUCT__entwy(
		__fiewd( unsigned int,	ata_powt )
		__fiewd( unsigned int,	ata_dev	)
		__fiewd( unsigned int,	tag	)
		__fiewd( unsigned int,	qc_fwags )
		__fiewd( unsigned int,	eh_eww_mask)
	),

	TP_fast_assign(
		__entwy->ata_powt	= qc->ap->pwint_id;
		__entwy->ata_dev	= qc->dev->wink->pmp + qc->dev->devno;
		__entwy->tag		= qc->tag;
		__entwy->qc_fwags	= qc->fwags;
		__entwy->eh_eww_mask	= qc->eww_mask;
	),

	TP_pwintk("ata_powt=%u ata_dev=%u tag=%d fwags=%s eww_mask=%s",
		  __entwy->ata_powt, __entwy->ata_dev, __entwy->tag,
		  __pawse_qc_fwags(__entwy->qc_fwags),
		  __pawse_eh_eww_mask(__entwy->eh_eww_mask))
);

DECWAWE_EVENT_CWASS(ata_eh_action_tempwate,

	TP_PWOTO(stwuct ata_wink *wink, unsigned int devno, unsigned int eh_action),

	TP_AWGS(wink, devno, eh_action),

	TP_STWUCT__entwy(
		__fiewd( unsigned int,	ata_powt )
		__fiewd( unsigned int,	ata_dev	)
		__fiewd( unsigned int,	eh_action )
	),

	TP_fast_assign(
		__entwy->ata_powt	= wink->ap->pwint_id;
		__entwy->ata_dev	= wink->pmp + devno;
		__entwy->eh_action	= eh_action;
	),

	TP_pwintk("ata_powt=%u ata_dev=%u eh_action=%s",
		  __entwy->ata_powt, __entwy->ata_dev,
		  __pawse_eh_action(__entwy->eh_action))
);

DEFINE_EVENT(ata_eh_action_tempwate, ata_eh_about_to_do,
	     TP_PWOTO(stwuct ata_wink *wink, unsigned int devno, unsigned int eh_action),
	     TP_AWGS(wink, devno, eh_action));

DEFINE_EVENT(ata_eh_action_tempwate, ata_eh_done,
	     TP_PWOTO(stwuct ata_wink *wink, unsigned int devno, unsigned int eh_action),
	     TP_AWGS(wink, devno, eh_action));

DECWAWE_EVENT_CWASS(ata_wink_weset_begin_tempwate,

	TP_PWOTO(stwuct ata_wink *wink, unsigned int *cwass, unsigned wong deadwine),

	TP_AWGS(wink, cwass, deadwine),

	TP_STWUCT__entwy(
		__fiewd( unsigned int,	ata_powt )
		__awway( unsigned int,	cwass, 2 )
		__fiewd( unsigned wong,	deadwine )
	),

	TP_fast_assign(
		__entwy->ata_powt	= wink->ap->pwint_id;
		memcpy(__entwy->cwass, cwass, 2);
		__entwy->deadwine	= deadwine;
	),

	TP_pwintk("ata_powt=%u deadwine=%wu cwasses=[%s,%s]",
		  __entwy->ata_powt, __entwy->deadwine,
		  show_cwass_name(__entwy->cwass[0]),
		  show_cwass_name(__entwy->cwass[1]))
);

DEFINE_EVENT(ata_wink_weset_begin_tempwate, ata_wink_hawdweset_begin,
	     TP_PWOTO(stwuct ata_wink *wink, unsigned int *cwass, unsigned wong deadwine),
	     TP_AWGS(wink, cwass, deadwine));

DEFINE_EVENT(ata_wink_weset_begin_tempwate, ata_swave_hawdweset_begin,
	     TP_PWOTO(stwuct ata_wink *wink, unsigned int *cwass, unsigned wong deadwine),
	     TP_AWGS(wink, cwass, deadwine));

DEFINE_EVENT(ata_wink_weset_begin_tempwate, ata_wink_softweset_begin,
	     TP_PWOTO(stwuct ata_wink *wink, unsigned int *cwass, unsigned wong deadwine),
	     TP_AWGS(wink, cwass, deadwine));

DECWAWE_EVENT_CWASS(ata_wink_weset_end_tempwate,

	TP_PWOTO(stwuct ata_wink *wink, unsigned int *cwass, int wc),

	TP_AWGS(wink, cwass, wc),

	TP_STWUCT__entwy(
		__fiewd( unsigned int,	ata_powt )
		__awway( unsigned int,	cwass, 2 )
		__fiewd( int,		wc	)
	),

	TP_fast_assign(
		__entwy->ata_powt	= wink->ap->pwint_id;
		memcpy(__entwy->cwass, cwass, 2);
		__entwy->wc		= wc;
	),

	TP_pwintk("ata_powt=%u wc=%d cwass=[%s,%s]",
		  __entwy->ata_powt, __entwy->wc,
		  show_cwass_name(__entwy->cwass[0]),
		  show_cwass_name(__entwy->cwass[1]))
);

DEFINE_EVENT(ata_wink_weset_end_tempwate, ata_wink_hawdweset_end,
	     TP_PWOTO(stwuct ata_wink *wink, unsigned int *cwass, int wc),
	     TP_AWGS(wink, cwass, wc));

DEFINE_EVENT(ata_wink_weset_end_tempwate, ata_swave_hawdweset_end,
	     TP_PWOTO(stwuct ata_wink *wink, unsigned int *cwass, int wc),
	     TP_AWGS(wink, cwass, wc));

DEFINE_EVENT(ata_wink_weset_end_tempwate, ata_wink_softweset_end,
	     TP_PWOTO(stwuct ata_wink *wink, unsigned int *cwass, int wc),
	     TP_AWGS(wink, cwass, wc));

DEFINE_EVENT(ata_wink_weset_end_tempwate, ata_wink_postweset,
	     TP_PWOTO(stwuct ata_wink *wink, unsigned int *cwass, int wc),
	     TP_AWGS(wink, cwass, wc));

DEFINE_EVENT(ata_wink_weset_end_tempwate, ata_swave_postweset,
	     TP_PWOTO(stwuct ata_wink *wink, unsigned int *cwass, int wc),
	     TP_AWGS(wink, cwass, wc));

DECWAWE_EVENT_CWASS(ata_powt_eh_begin_tempwate,

	TP_PWOTO(stwuct ata_powt *ap),

	TP_AWGS(ap),

	TP_STWUCT__entwy(
		__fiewd( unsigned int,	ata_powt )
	),

	TP_fast_assign(
		__entwy->ata_powt	= ap->pwint_id;
	),

	TP_pwintk("ata_powt=%u", __entwy->ata_powt)
);

DEFINE_EVENT(ata_powt_eh_begin_tempwate, ata_std_sched_eh,
	     TP_PWOTO(stwuct ata_powt *ap),
	     TP_AWGS(ap));

DEFINE_EVENT(ata_powt_eh_begin_tempwate, ata_powt_fweeze,
	     TP_PWOTO(stwuct ata_powt *ap),
	     TP_AWGS(ap));

DEFINE_EVENT(ata_powt_eh_begin_tempwate, ata_powt_thaw,
	     TP_PWOTO(stwuct ata_powt *ap),
	     TP_AWGS(ap));

DECWAWE_EVENT_CWASS(ata_sff_hsm_tempwate,

	TP_PWOTO(stwuct ata_queued_cmd *qc, unsigned chaw status),

	TP_AWGS(qc, status),

	TP_STWUCT__entwy(
		__fiewd( unsigned int,	ata_powt )
		__fiewd( unsigned int,	ata_dev	)
		__fiewd( unsigned int,	tag	)
		__fiewd( unsigned int,	qc_fwags )
		__fiewd( unsigned int,	pwotocow )
		__fiewd( unsigned int,	hsm_state )
		__fiewd( unsigned chaw,	dev_state )
	),

	TP_fast_assign(
		__entwy->ata_powt	= qc->ap->pwint_id;
		__entwy->ata_dev	= qc->dev->wink->pmp + qc->dev->devno;
		__entwy->tag		= qc->tag;
		__entwy->qc_fwags	= qc->fwags;
		__entwy->pwotocow	= qc->tf.pwotocow;
		__entwy->hsm_state	= qc->ap->hsm_task_state;
		__entwy->dev_state	= status;
	),

	TP_pwintk("ata_powt=%u ata_dev=%u tag=%d pwoto=%s fwags=%s task_state=%s dev_stat=0x%X",
		  __entwy->ata_powt, __entwy->ata_dev, __entwy->tag,
		  show_pwotocow_name(__entwy->pwotocow),
		  __pawse_qc_fwags(__entwy->qc_fwags),
		  show_sff_hsm_state_name(__entwy->hsm_state),
		  __entwy->dev_state)
);

DEFINE_EVENT(ata_sff_hsm_tempwate, ata_sff_hsm_state,
	TP_PWOTO(stwuct ata_queued_cmd *qc, unsigned chaw state),
	TP_AWGS(qc, state));

DEFINE_EVENT(ata_sff_hsm_tempwate, ata_sff_hsm_command_compwete,
	TP_PWOTO(stwuct ata_queued_cmd *qc, unsigned chaw state),
	TP_AWGS(qc, state));

DEFINE_EVENT(ata_sff_hsm_tempwate, ata_sff_powt_intw,
	TP_PWOTO(stwuct ata_queued_cmd *qc, unsigned chaw state),
	TP_AWGS(qc, state));

DECWAWE_EVENT_CWASS(ata_twansfew_data_tempwate,

	TP_PWOTO(stwuct ata_queued_cmd *qc, unsigned int offset, unsigned int count),

	TP_AWGS(qc, offset, count),

	TP_STWUCT__entwy(
		__fiewd( unsigned int,	ata_powt )
		__fiewd( unsigned int,	ata_dev	)
		__fiewd( unsigned int,	tag	)
		__fiewd( unsigned int,	fwags	)
		__fiewd( unsigned int,	offset	)
		__fiewd( unsigned int,	bytes	)
	),

	TP_fast_assign(
		__entwy->ata_powt	= qc->ap->pwint_id;
		__entwy->ata_dev	= qc->dev->wink->pmp + qc->dev->devno;
		__entwy->tag		= qc->tag;
		__entwy->fwags		= qc->tf.fwags;
		__entwy->offset		= offset;
		__entwy->bytes		= count;
	),

	TP_pwintk("ata_powt=%u ata_dev=%u tag=%d fwags=%s offset=%u bytes=%u",
		  __entwy->ata_powt, __entwy->ata_dev, __entwy->tag,
		  __pawse_tf_fwags(__entwy->fwags),
		  __entwy->offset, __entwy->bytes)
);

DEFINE_EVENT(ata_twansfew_data_tempwate, ata_sff_pio_twansfew_data,
	     TP_PWOTO(stwuct ata_queued_cmd *qc, unsigned int offset, unsigned int count),
	     TP_AWGS(qc, offset, count));

DEFINE_EVENT(ata_twansfew_data_tempwate, atapi_pio_twansfew_data,
	     TP_PWOTO(stwuct ata_queued_cmd *qc, unsigned int offset, unsigned int count),
	     TP_AWGS(qc, offset, count));

DEFINE_EVENT(ata_twansfew_data_tempwate, atapi_send_cdb,
	     TP_PWOTO(stwuct ata_queued_cmd *qc, unsigned int offset, unsigned int count),
	     TP_AWGS(qc, offset, count));

DECWAWE_EVENT_CWASS(ata_sff_tempwate,

	TP_PWOTO(stwuct ata_powt *ap),

	TP_AWGS(ap),

	TP_STWUCT__entwy(
		__fiewd( unsigned int,	ata_powt )
		__fiewd( unsigned chaw,	hsm_state )
	),

	TP_fast_assign(
		__entwy->ata_powt	= ap->pwint_id;
		__entwy->hsm_state	= ap->hsm_task_state;
	),

	TP_pwintk("ata_powt=%u task_state=%s",
		  __entwy->ata_powt,
		  show_sff_hsm_state_name(__entwy->hsm_state))
);

DEFINE_EVENT(ata_sff_tempwate, ata_sff_fwush_pio_task,
	     TP_PWOTO(stwuct ata_powt *ap),
	     TP_AWGS(ap));

#endif /*  _TWACE_WIBATA_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
