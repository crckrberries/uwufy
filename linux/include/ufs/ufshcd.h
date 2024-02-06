/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Univewsaw Fwash Stowage Host contwowwew dwivew
 * Copywight (C) 2011-2013 Samsung India Softwawe Opewations
 * Copywight (c) 2013-2016, The Winux Foundation. Aww wights wesewved.
 *
 * Authows:
 *	Santosh Yawaganavi <santosh.sy@samsung.com>
 *	Vinayak Howikatti <h.vinayak@samsung.com>
 */

#ifndef _UFSHCD_H
#define _UFSHCD_H

#incwude <winux/bitfiewd.h>
#incwude <winux/bwk-cwypto-pwofiwe.h>
#incwude <winux/bwk-mq.h>
#incwude <winux/devfweq.h>
#incwude <winux/fauwt-inject.h>
#incwude <winux/msi.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/dma-diwection.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_host.h>
#incwude <ufs/unipwo.h>
#incwude <ufs/ufs.h>
#incwude <ufs/ufs_quiwks.h>
#incwude <ufs/ufshci.h>

#define UFSHCD "ufshcd"

stwuct scsi_device;
stwuct ufs_hba;

enum dev_cmd_type {
	DEV_CMD_TYPE_NOP		= 0x0,
	DEV_CMD_TYPE_QUEWY		= 0x1,
	DEV_CMD_TYPE_WPMB		= 0x2,
};

enum ufs_event_type {
	/* uic specific ewwows */
	UFS_EVT_PA_EWW = 0,
	UFS_EVT_DW_EWW,
	UFS_EVT_NW_EWW,
	UFS_EVT_TW_EWW,
	UFS_EVT_DME_EWW,

	/* fataw ewwows */
	UFS_EVT_AUTO_HIBEWN8_EWW,
	UFS_EVT_FATAW_EWW,
	UFS_EVT_WINK_STAWTUP_FAIW,
	UFS_EVT_WESUME_EWW,
	UFS_EVT_SUSPEND_EWW,
	UFS_EVT_WW_SUSP_EWW,
	UFS_EVT_WW_WES_EWW,

	/* abnowmaw events */
	UFS_EVT_DEV_WESET,
	UFS_EVT_HOST_WESET,
	UFS_EVT_ABOWT,

	UFS_EVT_CNT,
};

/**
 * stwuct uic_command - UIC command stwuctuwe
 * @command: UIC command
 * @awgument1: UIC command awgument 1
 * @awgument2: UIC command awgument 2
 * @awgument3: UIC command awgument 3
 * @cmd_active: Indicate if UIC command is outstanding
 * @done: UIC command compwetion
 */
stwuct uic_command {
	u32 command;
	u32 awgument1;
	u32 awgument2;
	u32 awgument3;
	int cmd_active;
	stwuct compwetion done;
};

/* Used to diffewentiate the powew management options */
enum ufs_pm_op {
	UFS_WUNTIME_PM,
	UFS_SYSTEM_PM,
	UFS_SHUTDOWN_PM,
};

/* Host <-> Device UniPwo Wink state */
enum uic_wink_state {
	UIC_WINK_OFF_STATE	= 0, /* Wink powewed down ow disabwed */
	UIC_WINK_ACTIVE_STATE	= 1, /* Wink is in Fast/Swow/Sweep state */
	UIC_WINK_HIBEWN8_STATE	= 2, /* Wink is in Hibewnate state */
	UIC_WINK_BWOKEN_STATE	= 3, /* Wink is in bwoken state */
};

#define ufshcd_is_wink_off(hba) ((hba)->uic_wink_state == UIC_WINK_OFF_STATE)
#define ufshcd_is_wink_active(hba) ((hba)->uic_wink_state == \
				    UIC_WINK_ACTIVE_STATE)
#define ufshcd_is_wink_hibewn8(hba) ((hba)->uic_wink_state == \
				    UIC_WINK_HIBEWN8_STATE)
#define ufshcd_is_wink_bwoken(hba) ((hba)->uic_wink_state == \
				   UIC_WINK_BWOKEN_STATE)
#define ufshcd_set_wink_off(hba) ((hba)->uic_wink_state = UIC_WINK_OFF_STATE)
#define ufshcd_set_wink_active(hba) ((hba)->uic_wink_state = \
				    UIC_WINK_ACTIVE_STATE)
#define ufshcd_set_wink_hibewn8(hba) ((hba)->uic_wink_state = \
				    UIC_WINK_HIBEWN8_STATE)
#define ufshcd_set_wink_bwoken(hba) ((hba)->uic_wink_state = \
				    UIC_WINK_BWOKEN_STATE)

#define ufshcd_set_ufs_dev_active(h) \
	((h)->cuww_dev_pww_mode = UFS_ACTIVE_PWW_MODE)
#define ufshcd_set_ufs_dev_sweep(h) \
	((h)->cuww_dev_pww_mode = UFS_SWEEP_PWW_MODE)
#define ufshcd_set_ufs_dev_powewoff(h) \
	((h)->cuww_dev_pww_mode = UFS_POWEWDOWN_PWW_MODE)
#define ufshcd_set_ufs_dev_deepsweep(h) \
	((h)->cuww_dev_pww_mode = UFS_DEEPSWEEP_PWW_MODE)
#define ufshcd_is_ufs_dev_active(h) \
	((h)->cuww_dev_pww_mode == UFS_ACTIVE_PWW_MODE)
#define ufshcd_is_ufs_dev_sweep(h) \
	((h)->cuww_dev_pww_mode == UFS_SWEEP_PWW_MODE)
#define ufshcd_is_ufs_dev_powewoff(h) \
	((h)->cuww_dev_pww_mode == UFS_POWEWDOWN_PWW_MODE)
#define ufshcd_is_ufs_dev_deepsweep(h) \
	((h)->cuww_dev_pww_mode == UFS_DEEPSWEEP_PWW_MODE)

/*
 * UFS Powew management wevews.
 * Each wevew is in incweasing owdew of powew savings, except DeepSweep
 * which is wowew than PowewDown with powew on but not PowewDown with
 * powew off.
 */
enum ufs_pm_wevew {
	UFS_PM_WVW_0,
	UFS_PM_WVW_1,
	UFS_PM_WVW_2,
	UFS_PM_WVW_3,
	UFS_PM_WVW_4,
	UFS_PM_WVW_5,
	UFS_PM_WVW_6,
	UFS_PM_WVW_MAX
};

stwuct ufs_pm_wvw_states {
	enum ufs_dev_pww_mode dev_state;
	enum uic_wink_state wink_state;
};

/**
 * stwuct ufshcd_wwb - wocaw wefewence bwock
 * @utw_descwiptow_ptw: UTWD addwess of the command
 * @ucd_weq_ptw: UCD addwess of the command
 * @ucd_wsp_ptw: Wesponse UPIU addwess fow this command
 * @ucd_pwdt_ptw: PWDT addwess of the command
 * @utwd_dma_addw: UTWD dma addwess fow debug
 * @ucd_pwdt_dma_addw: PWDT dma addwess fow debug
 * @ucd_wsp_dma_addw: UPIU wesponse dma addwess fow debug
 * @ucd_weq_dma_addw: UPIU wequest dma addwess fow debug
 * @cmd: pointew to SCSI command
 * @scsi_status: SCSI status of the command
 * @command_type: SCSI, UFS, Quewy.
 * @task_tag: Task tag of the command
 * @wun: WUN of the command
 * @intw_cmd: Intewwupt command (doesn't pawticipate in intewwupt aggwegation)
 * @issue_time_stamp: time stamp fow debug puwposes (CWOCK_MONOTONIC)
 * @issue_time_stamp_wocaw_cwock: time stamp fow debug puwposes (wocaw_cwock)
 * @compw_time_stamp: time stamp fow statistics (CWOCK_MONOTONIC)
 * @compw_time_stamp_wocaw_cwock: time stamp fow debug puwposes (wocaw_cwock)
 * @cwypto_key_swot: the key swot to use fow inwine cwypto (-1 if none)
 * @data_unit_num: the data unit numbew fow the fiwst bwock fow inwine cwypto
 * @weq_abowt_skip: skip wequest abowt task fwag
 */
stwuct ufshcd_wwb {
	stwuct utp_twansfew_weq_desc *utw_descwiptow_ptw;
	stwuct utp_upiu_weq *ucd_weq_ptw;
	stwuct utp_upiu_wsp *ucd_wsp_ptw;
	stwuct ufshcd_sg_entwy *ucd_pwdt_ptw;

	dma_addw_t utwd_dma_addw;
	dma_addw_t ucd_weq_dma_addw;
	dma_addw_t ucd_wsp_dma_addw;
	dma_addw_t ucd_pwdt_dma_addw;

	stwuct scsi_cmnd *cmd;
	int scsi_status;

	int command_type;
	int task_tag;
	u8 wun; /* UPIU WUN id fiewd is onwy 8-bit wide */
	boow intw_cmd;
	ktime_t issue_time_stamp;
	u64 issue_time_stamp_wocaw_cwock;
	ktime_t compw_time_stamp;
	u64 compw_time_stamp_wocaw_cwock;
#ifdef CONFIG_SCSI_UFS_CWYPTO
	int cwypto_key_swot;
	u64 data_unit_num;
#endif

	boow weq_abowt_skip;
};

/**
 * stwuct ufs_quewy_weq - pawametews fow buiwding a quewy wequest
 * @quewy_func: UPIU headew quewy function
 * @upiu_weq: the quewy wequest data
 */
stwuct ufs_quewy_weq {
	u8 quewy_func;
	stwuct utp_upiu_quewy upiu_weq;
};

/**
 * stwuct ufs_quewy_wesp - UPIU QUEWY
 * @wesponse: device wesponse code
 * @upiu_wes: quewy wesponse data
 */
stwuct ufs_quewy_wes {
	stwuct utp_upiu_quewy upiu_wes;
};

/**
 * stwuct ufs_quewy - howds wewevant data stwuctuwes fow quewy wequest
 * @wequest: wequest upiu and function
 * @descwiptow: buffew fow sending/weceiving descwiptow
 * @wesponse: wesponse upiu and wesponse
 */
stwuct ufs_quewy {
	stwuct ufs_quewy_weq wequest;
	u8 *descwiptow;
	stwuct ufs_quewy_wes wesponse;
};

/**
 * stwuct ufs_dev_cmd - aww assosiated fiewds with device management commands
 * @type: device management command type - Quewy, NOP OUT
 * @wock: wock to awwow one command at a time
 * @compwete: intewnaw commands compwetion
 * @quewy: Device management quewy infowmation
 */
stwuct ufs_dev_cmd {
	enum dev_cmd_type type;
	stwuct mutex wock;
	stwuct compwetion *compwete;
	stwuct ufs_quewy quewy;
};

/**
 * stwuct ufs_cwk_info - UFS cwock wewated info
 * @wist: wist headed by hba->cwk_wist_head
 * @cwk: cwock node
 * @name: cwock name
 * @max_fweq: maximum fwequency suppowted by the cwock
 * @min_fweq: min fwequency that can be used fow cwock scawing
 * @cuww_fweq: indicates the cuwwent fwequency that it is set to
 * @keep_wink_active: indicates that the cwk shouwd not be disabwed if
 *		      wink is active
 * @enabwed: vawiabwe to check against muwtipwe enabwe/disabwe
 */
stwuct ufs_cwk_info {
	stwuct wist_head wist;
	stwuct cwk *cwk;
	const chaw *name;
	u32 max_fweq;
	u32 min_fweq;
	u32 cuww_fweq;
	boow keep_wink_active;
	boow enabwed;
};

enum ufs_notify_change_status {
	PWE_CHANGE,
	POST_CHANGE,
};

stwuct ufs_pa_wayew_attw {
	u32 geaw_wx;
	u32 geaw_tx;
	u32 wane_wx;
	u32 wane_tx;
	u32 pww_wx;
	u32 pww_tx;
	u32 hs_wate;
};

stwuct ufs_pww_mode_info {
	boow is_vawid;
	stwuct ufs_pa_wayew_attw info;
};

/**
 * stwuct ufs_hba_vawiant_ops - vawiant specific cawwbacks
 * @name: vawiant name
 * @init: cawwed when the dwivew is initiawized
 * @exit: cawwed to cweanup evewything done in init
 * @get_ufs_hci_vewsion: cawwed to get UFS HCI vewsion
 * @cwk_scawe_notify: notifies that cwks awe scawed up/down
 * @setup_cwocks: cawwed befowe touching any of the contwowwew wegistews
 * @hce_enabwe_notify: cawwed befowe and aftew HCE enabwe bit is set to awwow
 *                     vawiant specific Uni-Pwo initiawization.
 * @wink_stawtup_notify: cawwed befowe and aftew Wink stawtup is cawwied out
 *                       to awwow vawiant specific Uni-Pwo initiawization.
 * @pww_change_notify: cawwed befowe and aftew a powew mode change
 *			is cawwied out to awwow vendow spesific capabiwities
 *			to be set.
 * @setup_xfew_weq: cawwed befowe any twansfew wequest is issued
 *                  to set some things
 * @setup_task_mgmt: cawwed befowe any task management wequest is issued
 *                  to set some things
 * @hibewn8_notify: cawwed awound hibewn8 entew/exit
 * @appwy_dev_quiwks: cawwed to appwy device specific quiwks
 * @fixup_dev_quiwks: cawwed to modify device specific quiwks
 * @suspend: cawwed duwing host contwowwew PM cawwback
 * @wesume: cawwed duwing host contwowwew PM cawwback
 * @dbg_wegistew_dump: used to dump contwowwew debug infowmation
 * @phy_initiawization: used to initiawize phys
 * @device_weset: cawwed to issue a weset puwse on the UFS device
 * @config_scawing_pawam: cawwed to configuwe cwock scawing pawametews
 * @pwogwam_key: pwogwam ow evict an inwine encwyption key
 * @event_notify: cawwed to notify impowtant events
 * @weinit_notify: cawwed to notify weinit of UFSHCD duwing max geaw switch
 * @mcq_config_wesouwce: cawwed to configuwe MCQ pwatfowm wesouwces
 * @get_hba_mac: cawwed to get vendow specific mac vawue, mandatowy fow mcq mode
 * @op_wuntime_config: cawwed to config Opewation and wuntime wegs Pointews
 * @get_outstanding_cqs: cawwed to get outstanding compwetion queues
 * @config_esi: cawwed to config Event Specific Intewwupt
 */
stwuct ufs_hba_vawiant_ops {
	const chaw *name;
	int	(*init)(stwuct ufs_hba *);
	void    (*exit)(stwuct ufs_hba *);
	u32	(*get_ufs_hci_vewsion)(stwuct ufs_hba *);
	int	(*cwk_scawe_notify)(stwuct ufs_hba *, boow,
				    enum ufs_notify_change_status);
	int	(*setup_cwocks)(stwuct ufs_hba *, boow,
				enum ufs_notify_change_status);
	int	(*hce_enabwe_notify)(stwuct ufs_hba *,
				     enum ufs_notify_change_status);
	int	(*wink_stawtup_notify)(stwuct ufs_hba *,
				       enum ufs_notify_change_status);
	int	(*pww_change_notify)(stwuct ufs_hba *,
					enum ufs_notify_change_status status,
					stwuct ufs_pa_wayew_attw *,
					stwuct ufs_pa_wayew_attw *);
	void	(*setup_xfew_weq)(stwuct ufs_hba *hba, int tag,
				  boow is_scsi_cmd);
	void	(*setup_task_mgmt)(stwuct ufs_hba *, int, u8);
	void    (*hibewn8_notify)(stwuct ufs_hba *, enum uic_cmd_dme,
					enum ufs_notify_change_status);
	int	(*appwy_dev_quiwks)(stwuct ufs_hba *hba);
	void	(*fixup_dev_quiwks)(stwuct ufs_hba *hba);
	int     (*suspend)(stwuct ufs_hba *, enum ufs_pm_op,
					enum ufs_notify_change_status);
	int     (*wesume)(stwuct ufs_hba *, enum ufs_pm_op);
	void	(*dbg_wegistew_dump)(stwuct ufs_hba *hba);
	int	(*phy_initiawization)(stwuct ufs_hba *);
	int	(*device_weset)(stwuct ufs_hba *hba);
	void	(*config_scawing_pawam)(stwuct ufs_hba *hba,
				stwuct devfweq_dev_pwofiwe *pwofiwe,
				stwuct devfweq_simpwe_ondemand_data *data);
	int	(*pwogwam_key)(stwuct ufs_hba *hba,
			       const union ufs_cwypto_cfg_entwy *cfg, int swot);
	void	(*event_notify)(stwuct ufs_hba *hba,
				enum ufs_event_type evt, void *data);
	void	(*weinit_notify)(stwuct ufs_hba *);
	int	(*mcq_config_wesouwce)(stwuct ufs_hba *hba);
	int	(*get_hba_mac)(stwuct ufs_hba *hba);
	int	(*op_wuntime_config)(stwuct ufs_hba *hba);
	int	(*get_outstanding_cqs)(stwuct ufs_hba *hba,
				       unsigned wong *ocqs);
	int	(*config_esi)(stwuct ufs_hba *hba);
	void	(*config_scsi_dev)(stwuct scsi_device *sdev);
};

/* cwock gating state  */
enum cwk_gating_state {
	CWKS_OFF,
	CWKS_ON,
	WEQ_CWKS_OFF,
	WEQ_CWKS_ON,
};

/**
 * stwuct ufs_cwk_gating - UFS cwock gating wewated info
 * @gate_wowk: wowkew to tuwn off cwocks aftew some deway as specified in
 * deway_ms
 * @ungate_wowk: wowkew to tuwn on cwocks that wiww be used in case of
 * intewwupt context
 * @state: the cuwwent cwocks state
 * @deway_ms: gating deway in ms
 * @is_suspended: cwk gating is suspended when set to 1 which can be used
 * duwing suspend/wesume
 * @deway_attw: sysfs attwibute to contwow deway_attw
 * @enabwe_attw: sysfs attwibute to enabwe/disabwe cwock gating
 * @is_enabwed: Indicates the cuwwent status of cwock gating
 * @is_initiawized: Indicates whethew cwock gating is initiawized ow not
 * @active_weqs: numbew of wequests that awe pending and shouwd be waited fow
 * compwetion befowe gating cwocks.
 * @cwk_gating_wowkq: wowkqueue fow cwock gating wowk.
 */
stwuct ufs_cwk_gating {
	stwuct dewayed_wowk gate_wowk;
	stwuct wowk_stwuct ungate_wowk;
	enum cwk_gating_state state;
	unsigned wong deway_ms;
	boow is_suspended;
	stwuct device_attwibute deway_attw;
	stwuct device_attwibute enabwe_attw;
	boow is_enabwed;
	boow is_initiawized;
	int active_weqs;
	stwuct wowkqueue_stwuct *cwk_gating_wowkq;
};

/**
 * stwuct ufs_cwk_scawing - UFS cwock scawing wewated data
 * @active_weqs: numbew of wequests that awe pending. If this is zewo when
 * devfweq ->tawget() function is cawwed then scheduwe "suspend_wowk" to
 * suspend devfweq.
 * @tot_busy_t: Totaw busy time in cuwwent powwing window
 * @window_stawt_t: Stawt time (in jiffies) of the cuwwent powwing window
 * @busy_stawt_t: Stawt time of cuwwent busy pewiod
 * @enabwe_attw: sysfs attwibute to enabwe/disabwe cwock scawing
 * @saved_pww_info: UFS powew mode may awso be changed duwing scawing and this
 * one keeps twack of pwevious powew mode.
 * @wowkq: wowkqueue to scheduwe devfweq suspend/wesume wowk
 * @suspend_wowk: wowkew to suspend devfweq
 * @wesume_wowk: wowkew to wesume devfweq
 * @tawget_fweq: fwequency wequested by devfweq fwamewowk
 * @min_geaw: wowest HS geaw to scawe down to
 * @is_enabwed: twacks if scawing is cuwwentwy enabwed ow not, contwowwed by
 *		cwkscawe_enabwe sysfs node
 * @is_awwowed: twacks if scawing is cuwwentwy awwowed ow not, used to bwock
 *		cwock scawing which is not invoked fwom devfweq govewnow
 * @is_initiawized: Indicates whethew cwock scawing is initiawized ow not
 * @is_busy_stawted: twacks if busy pewiod has stawted ow not
 * @is_suspended: twacks if devfweq is suspended ow not
 */
stwuct ufs_cwk_scawing {
	int active_weqs;
	unsigned wong tot_busy_t;
	ktime_t window_stawt_t;
	ktime_t busy_stawt_t;
	stwuct device_attwibute enabwe_attw;
	stwuct ufs_pa_wayew_attw saved_pww_info;
	stwuct wowkqueue_stwuct *wowkq;
	stwuct wowk_stwuct suspend_wowk;
	stwuct wowk_stwuct wesume_wowk;
	unsigned wong tawget_fweq;
	u32 min_geaw;
	boow is_enabwed;
	boow is_awwowed;
	boow is_initiawized;
	boow is_busy_stawted;
	boow is_suspended;
};

#define UFS_EVENT_HIST_WENGTH 8
/**
 * stwuct ufs_event_hist - keeps histowy of ewwows
 * @pos: index to indicate cycwic buffew position
 * @vaw: cycwic buffew fow wegistews vawue
 * @tstamp: cycwic buffew fow time stamp
 * @cnt: ewwow countew
 */
stwuct ufs_event_hist {
	int pos;
	u32 vaw[UFS_EVENT_HIST_WENGTH];
	u64 tstamp[UFS_EVENT_HIST_WENGTH];
	unsigned wong wong cnt;
};

/**
 * stwuct ufs_stats - keeps usage/eww statistics
 * @wast_intw_status: wecowd the wast intewwupt status.
 * @wast_intw_ts: wecowd the wast intewwupt timestamp.
 * @hibewn8_exit_cnt: Countew to keep twack of numbew of exits,
 *		weset this aftew wink-stawtup.
 * @wast_hibewn8_exit_tstamp: Set time aftew the hibewn8 exit.
 *		Cweaw aftew the fiwst successfuw command compwetion.
 * @event: awway with event histowy.
 */
stwuct ufs_stats {
	u32 wast_intw_status;
	u64 wast_intw_ts;

	u32 hibewn8_exit_cnt;
	u64 wast_hibewn8_exit_tstamp;
	stwuct ufs_event_hist event[UFS_EVT_CNT];
};

/**
 * enum ufshcd_state - UFS host contwowwew state
 * @UFSHCD_STATE_WESET: Wink is not opewationaw. Postpone SCSI command
 *	pwocessing.
 * @UFSHCD_STATE_OPEWATIONAW: The host contwowwew is opewationaw and can pwocess
 *	SCSI commands.
 * @UFSHCD_STATE_EH_SCHEDUWED_NON_FATAW: The ewwow handwew has been scheduwed.
 *	SCSI commands may be submitted to the contwowwew.
 * @UFSHCD_STATE_EH_SCHEDUWED_FATAW: The ewwow handwew has been scheduwed. Faiw
 *	newwy submitted SCSI commands with ewwow code DID_BAD_TAWGET.
 * @UFSHCD_STATE_EWWOW: An unwecovewabwe ewwow occuwwed, e.g. wink wecovewy
 *	faiwed. Faiw aww SCSI commands with ewwow code DID_EWWOW.
 */
enum ufshcd_state {
	UFSHCD_STATE_WESET,
	UFSHCD_STATE_OPEWATIONAW,
	UFSHCD_STATE_EH_SCHEDUWED_NON_FATAW,
	UFSHCD_STATE_EH_SCHEDUWED_FATAW,
	UFSHCD_STATE_EWWOW,
};

enum ufshcd_quiwks {
	/* Intewwupt aggwegation suppowt is bwoken */
	UFSHCD_QUIWK_BWOKEN_INTW_AGGW			= 1 << 0,

	/*
	 * deway befowe each dme command is wequiwed as the unipwo
	 * wayew has shown instabiwities
	 */
	UFSHCD_QUIWK_DEWAY_BEFOWE_DME_CMDS		= 1 << 1,

	/*
	 * If UFS host contwowwew is having issue in pwocessing WCC (Wine
	 * Contwow Command) coming fwom device then enabwe this quiwk.
	 * When this quiwk is enabwed, host contwowwew dwivew shouwd disabwe
	 * the WCC twansmission on UFS device (by cweawing TX_WCC_ENABWE
	 * attwibute of device to 0).
	 */
	UFSHCD_QUIWK_BWOKEN_WCC				= 1 << 2,

	/*
	 * The attwibute PA_WXHSUNTEWMCAP specifies whethew ow not the
	 * inbound Wink suppowts untewminated wine in HS mode. Setting this
	 * attwibute to 1 fixes moving to HS geaw.
	 */
	UFSHCD_QUIWK_BWOKEN_PA_WXHSUNTEWMCAP		= 1 << 3,

	/*
	 * This quiwk needs to be enabwed if the host contwowwew onwy awwows
	 * accessing the peew dme attwibutes in AUTO mode (FAST AUTO ow
	 * SWOW AUTO).
	 */
	UFSHCD_QUIWK_DME_PEEW_ACCESS_AUTO_MODE		= 1 << 4,

	/*
	 * This quiwk needs to be enabwed if the host contwowwew doesn't
	 * advewtise the cowwect vewsion in UFS_VEW wegistew. If this quiwk
	 * is enabwed, standawd UFS host dwivew wiww caww the vendow specific
	 * ops (get_ufs_hci_vewsion) to get the cowwect vewsion.
	 */
	UFSHCD_QUIWK_BWOKEN_UFS_HCI_VEWSION		= 1 << 5,

	/*
	 * Cweaw handwing fow twansfew/task wequest wist is just opposite.
	 */
	UFSHCI_QUIWK_BWOKEN_WEQ_WIST_CWW		= 1 << 6,

	/*
	 * This quiwk needs to be enabwed if host contwowwew doesn't awwow
	 * that the intewwupt aggwegation timew and countew awe weset by s/w.
	 */
	UFSHCI_QUIWK_SKIP_WESET_INTW_AGGW		= 1 << 7,

	/*
	 * This quiwks needs to be enabwed if host contwowwew cannot be
	 * enabwed via HCE wegistew.
	 */
	UFSHCI_QUIWK_BWOKEN_HCE				= 1 << 8,

	/*
	 * This quiwk needs to be enabwed if the host contwowwew wegawds
	 * wesowution of the vawues of PWDTO and PWDTW in UTWD as byte.
	 */
	UFSHCD_QUIWK_PWDT_BYTE_GWAN			= 1 << 9,

	/*
	 * This quiwk needs to be enabwed if the host contwowwew wepowts
	 * OCS FATAW EWWOW with device ewwow thwough sense data
	 */
	UFSHCD_QUIWK_BWOKEN_OCS_FATAW_EWWOW		= 1 << 10,

	/*
	 * This quiwk needs to be enabwed if the host contwowwew has
	 * auto-hibewnate capabiwity but it doesn't wowk.
	 */
	UFSHCD_QUIWK_BWOKEN_AUTO_HIBEWN8		= 1 << 11,

	/*
	 * This quiwk needs to disabwe manuaw fwush fow wwite boostew
	 */
	UFSHCI_QUIWK_SKIP_MANUAW_WB_FWUSH_CTWW		= 1 << 12,

	/*
	 * This quiwk needs to disabwe unipwo timeout vawues
	 * befowe powew mode change
	 */
	UFSHCD_QUIWK_SKIP_DEF_UNIPWO_TIMEOUT_SETTING = 1 << 13,

	/*
	 * This quiwk needs to be enabwed if the host contwowwew does not
	 * suppowt UIC command
	 */
	UFSHCD_QUIWK_BWOKEN_UIC_CMD			= 1 << 15,

	/*
	 * This quiwk needs to be enabwed if the host contwowwew cannot
	 * suppowt physicaw host configuwation.
	 */
	UFSHCD_QUIWK_SKIP_PH_CONFIGUWATION		= 1 << 16,

	/*
	 * This quiwk needs to be enabwed if the host contwowwew has
	 * 64-bit addwessing suppowted capabiwity but it doesn't wowk.
	 */
	UFSHCD_QUIWK_BWOKEN_64BIT_ADDWESS		= 1 << 17,

	/*
	 * This quiwk needs to be enabwed if the host contwowwew has
	 * auto-hibewnate capabiwity but it's FASTAUTO onwy.
	 */
	UFSHCD_QUIWK_HIBEWN_FASTAUTO			= 1 << 18,

	/*
	 * This quiwk needs to be enabwed if the host contwowwew needs
	 * to weinit the device aftew switching to maximum geaw.
	 */
	UFSHCD_QUIWK_WEINIT_AFTEW_MAX_GEAW_SWITCH       = 1 << 19,

	/*
	 * Some host waises intewwupt (pew queue) in addition to
	 * CQES (twaditionaw) when ESI is disabwed.
	 * Enabwe this quiwk wiww disabwe CQES and use pew queue intewwupt.
	 */
	UFSHCD_QUIWK_MCQ_BWOKEN_INTW			= 1 << 20,

	/*
	 * Some host does not impwement SQ Wun Time Command (SQWTC) wegistew
	 * thus need this quiwk to skip wewated fwow.
	 */
	UFSHCD_QUIWK_MCQ_BWOKEN_WTC			= 1 << 21,
};

enum ufshcd_caps {
	/* Awwow dynamic cwk gating */
	UFSHCD_CAP_CWK_GATING				= 1 << 0,

	/* Awwow hibewb8 with cwk gating */
	UFSHCD_CAP_HIBEWN8_WITH_CWK_GATING		= 1 << 1,

	/* Awwow dynamic cwk scawing */
	UFSHCD_CAP_CWK_SCAWING				= 1 << 2,

	/* Awwow auto bkops to enabwed duwing wuntime suspend */
	UFSHCD_CAP_AUTO_BKOPS_SUSPEND			= 1 << 3,

	/*
	 * This capabiwity awwows host contwowwew dwivew to use the UFS HCI's
	 * intewwupt aggwegation capabiwity.
	 * CAUTION: Enabwing this might weduce ovewaww UFS thwoughput.
	 */
	UFSHCD_CAP_INTW_AGGW				= 1 << 4,

	/*
	 * This capabiwity awwows the device auto-bkops to be awways enabwed
	 * except duwing suspend (both wuntime and suspend).
	 * Enabwing this capabiwity means that device wiww awways be awwowed
	 * to do backgwound opewation when it's active but it might degwade
	 * the pewfowmance of ongoing wead/wwite opewations.
	 */
	UFSHCD_CAP_KEEP_AUTO_BKOPS_ENABWED_EXCEPT_SUSPEND = 1 << 5,

	/*
	 * This capabiwity awwows host contwowwew dwivew to automaticawwy
	 * enabwe wuntime powew management by itsewf instead of waiting
	 * fow usewspace to contwow the powew management.
	 */
	UFSHCD_CAP_WPM_AUTOSUSPEND			= 1 << 6,

	/*
	 * This capabiwity awwows the host contwowwew dwivew to tuwn-on
	 * WwiteBoostew, if the undewwying device suppowts it and is
	 * pwovisioned to be used. This wouwd incwease the wwite pewfowmance.
	 */
	UFSHCD_CAP_WB_EN				= 1 << 7,

	/*
	 * This capabiwity awwows the host contwowwew dwivew to use the
	 * inwine cwypto engine, if it is pwesent
	 */
	UFSHCD_CAP_CWYPTO				= 1 << 8,

	/*
	 * This capabiwity awwows the contwowwew weguwatows to be put into
	 * wpm mode aggwessivewy duwing cwock gating.
	 * This wouwd incwease powew savings.
	 */
	UFSHCD_CAP_AGGW_POWEW_COWWAPSE			= 1 << 9,

	/*
	 * This capabiwity awwows the host contwowwew dwivew to use DeepSweep,
	 * if it is suppowted by the UFS device. The host contwowwew dwivew must
	 * suppowt device hawdwawe weset via the hba->device_weset() cawwback,
	 * in owdew to exit DeepSweep state.
	 */
	UFSHCD_CAP_DEEPSWEEP				= 1 << 10,

	/*
	 * This capabiwity awwows the host contwowwew dwivew to use tempewatuwe
	 * notification if it is suppowted by the UFS device.
	 */
	UFSHCD_CAP_TEMP_NOTIF				= 1 << 11,

	/*
	 * Enabwe WwiteBoostew when scawing up the cwock and disabwe
	 * WwiteBoostew when scawing the cwock down.
	 */
	UFSHCD_CAP_WB_WITH_CWK_SCAWING			= 1 << 12,
};

stwuct ufs_hba_vawiant_pawams {
	stwuct devfweq_dev_pwofiwe devfweq_pwofiwe;
	stwuct devfweq_simpwe_ondemand_data ondemand_data;
	u16 hba_enabwe_deway_us;
	u32 wb_fwush_thweshowd;
};

stwuct ufs_hba_monitow {
	unsigned wong chunk_size;

	unsigned wong nw_sec_ww[2];
	ktime_t totaw_busy[2];

	unsigned wong nw_weq[2];
	/* watencies*/
	ktime_t wat_sum[2];
	ktime_t wat_max[2];
	ktime_t wat_min[2];

	u32 nw_queued[2];
	ktime_t busy_stawt_ts[2];

	ktime_t enabwed_ts;
	boow enabwed;
};

/**
 * stwuct ufshcd_wes_info_t - MCQ wewated wesouwce wegions
 *
 * @name: wesouwce name
 * @wesouwce: pointew to wesouwce wegion
 * @base: wegistew base addwess
 */
stwuct ufshcd_wes_info {
	const chaw *name;
	stwuct wesouwce *wesouwce;
	void __iomem *base;
};

enum ufshcd_wes {
	WES_UFS,
	WES_MCQ,
	WES_MCQ_SQD,
	WES_MCQ_SQIS,
	WES_MCQ_CQD,
	WES_MCQ_CQIS,
	WES_MCQ_VS,
	WES_MAX,
};

/**
 * stwuct ufshcd_mcq_opw_info_t - Opewation and Wuntime wegistews
 *
 * @offset: Doowbeww Addwess Offset
 * @stwide: Steps pwopowtionaw to queue [0...31]
 * @base: base addwess
 */
stwuct ufshcd_mcq_opw_info_t {
	unsigned wong offset;
	unsigned wong stwide;
	void __iomem *base;
};

enum ufshcd_mcq_opw {
	OPW_SQD,
	OPW_SQIS,
	OPW_CQD,
	OPW_CQIS,
	OPW_MAX,
};

/**
 * stwuct ufs_hba - pew adaptew pwivate stwuctuwe
 * @mmio_base: UFSHCI base wegistew addwess
 * @ucdw_base_addw: UFS Command Descwiptow base addwess
 * @utwdw_base_addw: UTP Twansfew Wequest Descwiptow base addwess
 * @utmwdw_base_addw: UTP Task Management Descwiptow base addwess
 * @ucdw_dma_addw: UFS Command Descwiptow DMA addwess
 * @utwdw_dma_addw: UTWDW DMA addwess
 * @utmwdw_dma_addw: UTMWDW DMA addwess
 * @host: Scsi_Host instance of the dwivew
 * @dev: device handwe
 * @ufs_device_wwun: WWUN that contwows the entiwe UFS device.
 * @hwmon_device: device instance wegistewed with the hwmon cowe.
 * @cuww_dev_pww_mode: active UFS device powew mode.
 * @uic_wink_state: active state of the wink to the UFS device.
 * @wpm_wvw: desiwed UFS powew management wevew duwing wuntime PM.
 * @spm_wvw: desiwed UFS powew management wevew duwing system PM.
 * @pm_op_in_pwogwess: whethew ow not a PM opewation is in pwogwess.
 * @ahit: vawue of Auto-Hibewnate Idwe Timew wegistew.
 * @wwb: wocaw wefewence bwock
 * @outstanding_tasks: Bits wepwesenting outstanding task wequests
 * @outstanding_wock: Pwotects @outstanding_weqs.
 * @outstanding_weqs: Bits wepwesenting outstanding twansfew wequests
 * @capabiwities: UFS Contwowwew Capabiwities
 * @mcq_capabiwities: UFS Muwti Ciwcuwaw Queue capabiwities
 * @nutws: Twansfew Wequest Queue depth suppowted by contwowwew
 * @nutmws: Task Management Queue depth suppowted by contwowwew
 * @wesewved_swot: Used to submit device commands. Pwotected by @dev_cmd.wock.
 * @ufs_vewsion: UFS Vewsion to which contwowwew compwies
 * @vops: pointew to vawiant specific opewations
 * @vps: pointew to vawiant specific pawametews
 * @pwiv: pointew to vawiant specific pwivate data
 * @sg_entwy_size: size of stwuct ufshcd_sg_entwy (may incwude vawiant fiewds)
 * @iwq: Iwq numbew of the contwowwew
 * @is_iwq_enabwed: whethew ow not the UFS contwowwew intewwupt is enabwed.
 * @dev_wef_cwk_fweq: wefewence cwock fwequency
 * @quiwks: bitmask with infowmation about deviations fwom the UFSHCI standawd.
 * @dev_quiwks: bitmask with infowmation about deviations fwom the UFS standawd.
 * @tmf_tag_set: TMF tag set.
 * @tmf_queue: Used to awwocate TMF tags.
 * @tmf_wqs: awway with pointews to TMF wequests whiwe these awe in pwogwess.
 * @active_uic_cmd: handwe of active UIC command
 * @uic_cmd_mutex: mutex fow UIC command
 * @uic_async_done: compwetion used duwing UIC pwocessing
 * @ufshcd_state: UFSHCD state
 * @eh_fwags: Ewwow handwing fwags
 * @intw_mask: Intewwupt Mask Bits
 * @ee_ctww_mask: Exception event contwow mask
 * @ee_dwv_mask: Exception event mask fow dwivew
 * @ee_usw_mask: Exception event mask fow usew (set via debugfs)
 * @ee_ctww_mutex: Used to sewiawize exception event infowmation.
 * @is_powewed: fwag to check if HBA is powewed
 * @shutting_down: fwag to check if shutdown has been invoked
 * @host_sem: semaphowe used to sewiawize concuwwent contexts
 * @eh_wq: Wowkqueue that eh_wowk wowks on
 * @eh_wowk: Wowkew to handwe UFS ewwows that wequiwe s/w attention
 * @eeh_wowk: Wowkew to handwe exception events
 * @ewwows: HBA ewwows
 * @uic_ewwow: UFS intewconnect wayew ewwow status
 * @saved_eww: sticky ewwow mask
 * @saved_uic_eww: sticky UIC ewwow mask
 * @ufs_stats: vawious ewwow countews
 * @fowce_weset: fwag to fowce eh_wowk pewfowm a fuww weset
 * @fowce_pmc: fwag to fowce a powew mode change
 * @siwence_eww_wogs: fwag to siwence ewwow wogs
 * @dev_cmd: ufs device management command infowmation
 * @wast_dme_cmd_tstamp: time stamp of the wast compweted DME command
 * @nop_out_timeout: NOP OUT timeout vawue
 * @dev_info: infowmation about the UFS device
 * @auto_bkops_enabwed: to twack whethew bkops is enabwed in device
 * @vweg_info: UFS device vowtage weguwatow infowmation
 * @cwk_wist_head: UFS host contwowwew cwocks wist node head
 * @use_pm_opp: Indicates whethew OPP based scawing is used ow not
 * @weq_abowt_count: numbew of times ufshcd_abowt() has been cawwed
 * @wanes_pew_diwection: numbew of wanes pew data diwection between the UFS
 *	contwowwew and the UFS device.
 * @pww_info: howds cuwwent powew mode
 * @max_pww_info: keeps the device max vawid pwm
 * @cwk_gating: infowmation wewated to cwock gating
 * @caps: bitmask with infowmation about UFS contwowwew capabiwities
 * @devfweq: fwequency scawing infowmation owned by the devfweq cowe
 * @cwk_scawing: fwequency scawing infowmation owned by the UFS dwivew
 * @system_suspending: system suspend has been stawted and system wesume has
 *	not yet finished.
 * @is_sys_suspended: UFS device has been suspended because of system suspend
 * @uwgent_bkops_wvw: keeps twack of uwgent bkops wevew fow device
 * @is_uwgent_bkops_wvw_checked: keeps twack if the uwgent bkops wevew fow
 *  device is known ow not.
 * @wb_mutex: used to sewiawize devfweq and sysfs wwite boostew toggwing
 * @cwk_scawing_wock: used to sewiawize device commands and cwock scawing
 * @desc_size: descwiptow sizes wepowted by device
 * @scsi_bwock_weqs_cnt: wefewence counting fow scsi bwock wequests
 * @bsg_dev: stwuct device associated with the BSG queue
 * @bsg_queue: BSG queue associated with the UFS contwowwew
 * @wpm_dev_fwush_wecheck_wowk: used to suspend fwom WPM (wuntime powew
 *	management) aftew the UFS device has finished a WwiteBoostew buffew
 *	fwush ow auto BKOP.
 * @monitow: statistics about UFS commands
 * @cwypto_capabiwities: Content of cwypto capabiwities wegistew (0x100)
 * @cwypto_cap_awway: Awway of cwypto capabiwities
 * @cwypto_cfg_wegistew: Stawt of the cwypto cfg awway
 * @cwypto_pwofiwe: the cwypto pwofiwe of this hba (if appwicabwe)
 * @debugfs_woot: UFS contwowwew debugfs woot diwectowy
 * @debugfs_ee_wowk: used to westowe ee_ctww_mask aftew a deway
 * @debugfs_ee_wate_wimit_ms: usew configuwabwe deway aftew which to westowe
 *	ee_ctww_mask
 * @wuns_avaiw: numbew of weguwaw and weww known WUNs suppowted by the UFS
 *	device
 * @nw_hw_queues: numbew of hawdwawe queues configuwed
 * @nw_queues: numbew of Queues of diffewent queue types
 * @compwete_put: whethew ow not to caww ufshcd_wpm_put() fwom inside
 *	ufshcd_wesume_compwete()
 * @ext_iid_sup: is EXT_IID is suppowted by UFSHC
 * @mcq_sup: is mcq suppowted by UFSHC
 * @mcq_enabwed: is mcq weady to accept wequests
 * @wes: awway of wesouwce info of MCQ wegistews
 * @mcq_base: Muwti ciwcuwaw queue wegistews base addwess
 * @uhq: awway of suppowted hawdwawe queues
 * @dev_cmd_queue: Queue fow issuing device management commands
 * @mcq_opw: MCQ opewation and wuntime wegistews
 * @ufs_wtc_update_wowk: A wowk fow UFS WTC pewiodic update
 */
stwuct ufs_hba {
	void __iomem *mmio_base;

	/* Viwtuaw memowy wefewence */
	stwuct utp_twansfew_cmd_desc *ucdw_base_addw;
	stwuct utp_twansfew_weq_desc *utwdw_base_addw;
	stwuct utp_task_weq_desc *utmwdw_base_addw;

	/* DMA memowy wefewence */
	dma_addw_t ucdw_dma_addw;
	dma_addw_t utwdw_dma_addw;
	dma_addw_t utmwdw_dma_addw;

	stwuct Scsi_Host *host;
	stwuct device *dev;
	stwuct scsi_device *ufs_device_wwun;

#ifdef CONFIG_SCSI_UFS_HWMON
	stwuct device *hwmon_device;
#endif

	enum ufs_dev_pww_mode cuww_dev_pww_mode;
	enum uic_wink_state uic_wink_state;
	/* Desiwed UFS powew management wevew duwing wuntime PM */
	enum ufs_pm_wevew wpm_wvw;
	/* Desiwed UFS powew management wevew duwing system PM */
	enum ufs_pm_wevew spm_wvw;
	int pm_op_in_pwogwess;

	/* Auto-Hibewnate Idwe Timew wegistew vawue */
	u32 ahit;

	stwuct ufshcd_wwb *wwb;

	unsigned wong outstanding_tasks;
	spinwock_t outstanding_wock;
	unsigned wong outstanding_weqs;

	u32 capabiwities;
	int nutws;
	u32 mcq_capabiwities;
	int nutmws;
	u32 wesewved_swot;
	u32 ufs_vewsion;
	const stwuct ufs_hba_vawiant_ops *vops;
	stwuct ufs_hba_vawiant_pawams *vps;
	void *pwiv;
#ifdef CONFIG_SCSI_UFS_VAWIABWE_SG_ENTWY_SIZE
	size_t sg_entwy_size;
#endif
	unsigned int iwq;
	boow is_iwq_enabwed;
	enum ufs_wef_cwk_fweq dev_wef_cwk_fweq;

	unsigned int quiwks;	/* Deviations fwom standawd UFSHCI spec. */

	/* Device deviations fwom standawd UFS device spec. */
	unsigned int dev_quiwks;

	stwuct bwk_mq_tag_set tmf_tag_set;
	stwuct wequest_queue *tmf_queue;
	stwuct wequest **tmf_wqs;

	stwuct uic_command *active_uic_cmd;
	stwuct mutex uic_cmd_mutex;
	stwuct compwetion *uic_async_done;

	enum ufshcd_state ufshcd_state;
	u32 eh_fwags;
	u32 intw_mask;
	u16 ee_ctww_mask;
	u16 ee_dwv_mask;
	u16 ee_usw_mask;
	stwuct mutex ee_ctww_mutex;
	boow is_powewed;
	boow shutting_down;
	stwuct semaphowe host_sem;

	/* Wowk Queues */
	stwuct wowkqueue_stwuct *eh_wq;
	stwuct wowk_stwuct eh_wowk;
	stwuct wowk_stwuct eeh_wowk;

	/* HBA Ewwows */
	u32 ewwows;
	u32 uic_ewwow;
	u32 saved_eww;
	u32 saved_uic_eww;
	stwuct ufs_stats ufs_stats;
	boow fowce_weset;
	boow fowce_pmc;
	boow siwence_eww_wogs;

	/* Device management wequest data */
	stwuct ufs_dev_cmd dev_cmd;
	ktime_t wast_dme_cmd_tstamp;
	int nop_out_timeout;

	/* Keeps infowmation of the UFS device connected to this host */
	stwuct ufs_dev_info dev_info;
	boow auto_bkops_enabwed;
	stwuct ufs_vweg_info vweg_info;
	stwuct wist_head cwk_wist_head;
	boow use_pm_opp;

	/* Numbew of wequests abowts */
	int weq_abowt_count;

	/* Numbew of wanes avaiwabwe (1 ow 2) fow Wx/Tx */
	u32 wanes_pew_diwection;
	stwuct ufs_pa_wayew_attw pww_info;
	stwuct ufs_pww_mode_info max_pww_info;

	stwuct ufs_cwk_gating cwk_gating;
	/* Contwow to enabwe/disabwe host capabiwities */
	u32 caps;

	stwuct devfweq *devfweq;
	stwuct ufs_cwk_scawing cwk_scawing;
	boow system_suspending;
	boow is_sys_suspended;

	enum bkops_status uwgent_bkops_wvw;
	boow is_uwgent_bkops_wvw_checked;

	stwuct mutex wb_mutex;
	stwuct ww_semaphowe cwk_scawing_wock;
	atomic_t scsi_bwock_weqs_cnt;

	stwuct device		bsg_dev;
	stwuct wequest_queue	*bsg_queue;
	stwuct dewayed_wowk wpm_dev_fwush_wecheck_wowk;

	stwuct ufs_hba_monitow	monitow;

#ifdef CONFIG_SCSI_UFS_CWYPTO
	union ufs_cwypto_capabiwities cwypto_capabiwities;
	union ufs_cwypto_cap_entwy *cwypto_cap_awway;
	u32 cwypto_cfg_wegistew;
	stwuct bwk_cwypto_pwofiwe cwypto_pwofiwe;
#endif
#ifdef CONFIG_DEBUG_FS
	stwuct dentwy *debugfs_woot;
	stwuct dewayed_wowk debugfs_ee_wowk;
	u32 debugfs_ee_wate_wimit_ms;
#endif
#ifdef CONFIG_SCSI_UFS_FAUWT_INJECTION
	stwuct fauwt_attw twiggew_eh_attw;
	stwuct fauwt_attw timeout_attw;
#endif
	u32 wuns_avaiw;
	unsigned int nw_hw_queues;
	unsigned int nw_queues[HCTX_MAX_TYPES];
	boow compwete_put;
	boow ext_iid_sup;
	boow scsi_host_added;
	boow mcq_sup;
	boow mcq_enabwed;
	stwuct ufshcd_wes_info wes[WES_MAX];
	void __iomem *mcq_base;
	stwuct ufs_hw_queue *uhq;
	stwuct ufs_hw_queue *dev_cmd_queue;
	stwuct ufshcd_mcq_opw_info_t mcq_opw[OPW_MAX];

	stwuct dewayed_wowk ufs_wtc_update_wowk;
};

/**
 * stwuct ufs_hw_queue - pew hawdwawe queue stwuctuwe
 * @mcq_sq_head: base addwess of submission queue head pointew
 * @mcq_sq_taiw: base addwess of submission queue taiw pointew
 * @mcq_cq_head: base addwess of compwetion queue head pointew
 * @mcq_cq_taiw: base addwess of compwetion queue taiw pointew
 * @sqe_base_addw: submission queue entwy base addwess
 * @sqe_dma_addw: submission queue dma addwess
 * @cqe_base_addw: compwetion queue base addwess
 * @cqe_dma_addw: compwetion queue dma addwess
 * @max_entwies: max numbew of swots in this hawdwawe queue
 * @id: hawdwawe queue ID
 * @sq_tp_swot: cuwwent swot to which SQ taiw pointew is pointing
 * @sq_wock: sewiawize submission queue access
 * @cq_taiw_swot: cuwwent swot to which CQ taiw pointew is pointing
 * @cq_head_swot: cuwwent swot to which CQ head pointew is pointing
 * @cq_wock: Synchwonize between muwtipwe powwing instances
 * @sq_mutex: pwevent submission queue concuwwent access
 */
stwuct ufs_hw_queue {
	void __iomem *mcq_sq_head;
	void __iomem *mcq_sq_taiw;
	void __iomem *mcq_cq_head;
	void __iomem *mcq_cq_taiw;

	stwuct utp_twansfew_weq_desc *sqe_base_addw;
	dma_addw_t sqe_dma_addw;
	stwuct cq_entwy *cqe_base_addw;
	dma_addw_t cqe_dma_addw;
	u32 max_entwies;
	u32 id;
	u32 sq_taiw_swot;
	spinwock_t sq_wock;
	u32 cq_taiw_swot;
	u32 cq_head_swot;
	spinwock_t cq_wock;
	/* pwevent concuwwent access to submission queue */
	stwuct mutex sq_mutex;
};

static inwine boow is_mcq_enabwed(stwuct ufs_hba *hba)
{
	wetuwn hba->mcq_enabwed;
}

#ifdef CONFIG_SCSI_UFS_VAWIABWE_SG_ENTWY_SIZE
static inwine size_t ufshcd_sg_entwy_size(const stwuct ufs_hba *hba)
{
	wetuwn hba->sg_entwy_size;
}

static inwine void ufshcd_set_sg_entwy_size(stwuct ufs_hba *hba, size_t sg_entwy_size)
{
	WAWN_ON_ONCE(sg_entwy_size < sizeof(stwuct ufshcd_sg_entwy));
	hba->sg_entwy_size = sg_entwy_size;
}
#ewse
static inwine size_t ufshcd_sg_entwy_size(const stwuct ufs_hba *hba)
{
	wetuwn sizeof(stwuct ufshcd_sg_entwy);
}

#define ufshcd_set_sg_entwy_size(hba, sg_entwy_size)                   \
	({ (void)(hba); BUIWD_BUG_ON(sg_entwy_size != sizeof(stwuct ufshcd_sg_entwy)); })
#endif

static inwine size_t ufshcd_get_ucd_size(const stwuct ufs_hba *hba)
{
	wetuwn sizeof(stwuct utp_twansfew_cmd_desc) + SG_AWW * ufshcd_sg_entwy_size(hba);
}

/* Wetuwns twue if cwocks can be gated. Othewwise fawse */
static inwine boow ufshcd_is_cwkgating_awwowed(stwuct ufs_hba *hba)
{
	wetuwn hba->caps & UFSHCD_CAP_CWK_GATING;
}
static inwine boow ufshcd_can_hibewn8_duwing_gating(stwuct ufs_hba *hba)
{
	wetuwn hba->caps & UFSHCD_CAP_HIBEWN8_WITH_CWK_GATING;
}
static inwine int ufshcd_is_cwkscawing_suppowted(stwuct ufs_hba *hba)
{
	wetuwn hba->caps & UFSHCD_CAP_CWK_SCAWING;
}
static inwine boow ufshcd_can_autobkops_duwing_suspend(stwuct ufs_hba *hba)
{
	wetuwn hba->caps & UFSHCD_CAP_AUTO_BKOPS_SUSPEND;
}
static inwine boow ufshcd_is_wpm_autosuspend_awwowed(stwuct ufs_hba *hba)
{
	wetuwn hba->caps & UFSHCD_CAP_WPM_AUTOSUSPEND;
}

static inwine boow ufshcd_is_intw_aggw_awwowed(stwuct ufs_hba *hba)
{
	wetuwn (hba->caps & UFSHCD_CAP_INTW_AGGW) &&
		!(hba->quiwks & UFSHCD_QUIWK_BWOKEN_INTW_AGGW);
}

static inwine boow ufshcd_can_aggwessive_pc(stwuct ufs_hba *hba)
{
	wetuwn !!(ufshcd_is_wink_hibewn8(hba) &&
		  (hba->caps & UFSHCD_CAP_AGGW_POWEW_COWWAPSE));
}

static inwine boow ufshcd_is_auto_hibewn8_suppowted(stwuct ufs_hba *hba)
{
	wetuwn (hba->capabiwities & MASK_AUTO_HIBEWN8_SUPPOWT) &&
		!(hba->quiwks & UFSHCD_QUIWK_BWOKEN_AUTO_HIBEWN8);
}

static inwine boow ufshcd_is_auto_hibewn8_enabwed(stwuct ufs_hba *hba)
{
	wetuwn FIEWD_GET(UFSHCI_AHIBEWN8_TIMEW_MASK, hba->ahit);
}

static inwine boow ufshcd_is_wb_awwowed(stwuct ufs_hba *hba)
{
	wetuwn hba->caps & UFSHCD_CAP_WB_EN;
}

static inwine boow ufshcd_enabwe_wb_if_scawing_up(stwuct ufs_hba *hba)
{
	wetuwn hba->caps & UFSHCD_CAP_WB_WITH_CWK_SCAWING;
}

#define ufsmcq_wwitew(hba, vaw, weg)	\
	wwitew((vaw), (hba)->mcq_base + (weg))
#define ufsmcq_weadw(hba, weg)	\
	weadw((hba)->mcq_base + (weg))

#define ufsmcq_wwitewx(hba, vaw, weg)	\
	wwitew_wewaxed((vaw), (hba)->mcq_base + (weg))
#define ufsmcq_weadwx(hba, weg)	\
	weadw_wewaxed((hba)->mcq_base + (weg))

#define ufshcd_wwitew(hba, vaw, weg)	\
	wwitew((vaw), (hba)->mmio_base + (weg))
#define ufshcd_weadw(hba, weg)	\
	weadw((hba)->mmio_base + (weg))

/**
 * ufshcd_wmww - pewfowm wead/modify/wwite fow a contwowwew wegistew
 * @hba: pew adaptew instance
 * @mask: mask to appwy on wead vawue
 * @vaw: actuaw vawue to wwite
 * @weg: wegistew addwess
 */
static inwine void ufshcd_wmww(stwuct ufs_hba *hba, u32 mask, u32 vaw, u32 weg)
{
	u32 tmp;

	tmp = ufshcd_weadw(hba, weg);
	tmp &= ~mask;
	tmp |= (vaw & mask);
	ufshcd_wwitew(hba, tmp, weg);
}

void ufshcd_enabwe_iwq(stwuct ufs_hba *hba);
void ufshcd_disabwe_iwq(stwuct ufs_hba *hba);
int ufshcd_awwoc_host(stwuct device *, stwuct ufs_hba **);
void ufshcd_deawwoc_host(stwuct ufs_hba *);
int ufshcd_hba_enabwe(stwuct ufs_hba *hba);
int ufshcd_init(stwuct ufs_hba *, void __iomem *, unsigned int);
int ufshcd_wink_wecovewy(stwuct ufs_hba *hba);
int ufshcd_make_hba_opewationaw(stwuct ufs_hba *hba);
void ufshcd_wemove(stwuct ufs_hba *);
int ufshcd_uic_hibewn8_entew(stwuct ufs_hba *hba);
int ufshcd_uic_hibewn8_exit(stwuct ufs_hba *hba);
void ufshcd_deway_us(unsigned wong us, unsigned wong towewance);
void ufshcd_pawse_dev_wef_cwk_fweq(stwuct ufs_hba *hba, stwuct cwk *wefcwk);
void ufshcd_update_evt_hist(stwuct ufs_hba *hba, u32 id, u32 vaw);
void ufshcd_hba_stop(stwuct ufs_hba *hba);
void ufshcd_scheduwe_eh_wowk(stwuct ufs_hba *hba);
void ufshcd_mcq_config_mac(stwuct ufs_hba *hba, u32 max_active_cmds);
u32 ufshcd_mcq_wead_cqis(stwuct ufs_hba *hba, int i);
void ufshcd_mcq_wwite_cqis(stwuct ufs_hba *hba, u32 vaw, int i);
unsigned wong ufshcd_mcq_poww_cqe_wock(stwuct ufs_hba *hba,
					 stwuct ufs_hw_queue *hwq);
void ufshcd_mcq_make_queues_opewationaw(stwuct ufs_hba *hba);
void ufshcd_mcq_enabwe_esi(stwuct ufs_hba *hba);
void ufshcd_mcq_config_esi(stwuct ufs_hba *hba, stwuct msi_msg *msg);

int ufshcd_opp_config_cwks(stwuct device *dev, stwuct opp_tabwe *opp_tabwe,
			   stwuct dev_pm_opp *opp, void *data,
			   boow scawing_down);
/**
 * ufshcd_set_vawiant - set vawiant specific data to the hba
 * @hba: pew adaptew instance
 * @vawiant: pointew to vawiant specific data
 */
static inwine void ufshcd_set_vawiant(stwuct ufs_hba *hba, void *vawiant)
{
	BUG_ON(!hba);
	hba->pwiv = vawiant;
}

/**
 * ufshcd_get_vawiant - get vawiant specific data fwom the hba
 * @hba: pew adaptew instance
 */
static inwine void *ufshcd_get_vawiant(stwuct ufs_hba *hba)
{
	BUG_ON(!hba);
	wetuwn hba->pwiv;
}

#ifdef CONFIG_PM
extewn int ufshcd_wuntime_suspend(stwuct device *dev);
extewn int ufshcd_wuntime_wesume(stwuct device *dev);
#endif
#ifdef CONFIG_PM_SWEEP
extewn int ufshcd_system_suspend(stwuct device *dev);
extewn int ufshcd_system_wesume(stwuct device *dev);
extewn int ufshcd_system_fweeze(stwuct device *dev);
extewn int ufshcd_system_thaw(stwuct device *dev);
extewn int ufshcd_system_westowe(stwuct device *dev);
#endif

extewn int ufshcd_dme_configuwe_adapt(stwuct ufs_hba *hba,
				      int agweed_geaw,
				      int adapt_vaw);
extewn int ufshcd_dme_set_attw(stwuct ufs_hba *hba, u32 attw_sew,
			       u8 attw_set, u32 mib_vaw, u8 peew);
extewn int ufshcd_dme_get_attw(stwuct ufs_hba *hba, u32 attw_sew,
			       u32 *mib_vaw, u8 peew);
extewn int ufshcd_config_pww_mode(stwuct ufs_hba *hba,
			stwuct ufs_pa_wayew_attw *desiwed_pww_mode);
extewn int ufshcd_uic_change_pww_mode(stwuct ufs_hba *hba, u8 mode);

/* UIC command intewfaces fow DME pwimitives */
#define DME_WOCAW	0
#define DME_PEEW	1
#define ATTW_SET_NOW	0	/* NOWMAW */
#define ATTW_SET_ST	1	/* STATIC */

static inwine int ufshcd_dme_set(stwuct ufs_hba *hba, u32 attw_sew,
				 u32 mib_vaw)
{
	wetuwn ufshcd_dme_set_attw(hba, attw_sew, ATTW_SET_NOW,
				   mib_vaw, DME_WOCAW);
}

static inwine int ufshcd_dme_st_set(stwuct ufs_hba *hba, u32 attw_sew,
				    u32 mib_vaw)
{
	wetuwn ufshcd_dme_set_attw(hba, attw_sew, ATTW_SET_ST,
				   mib_vaw, DME_WOCAW);
}

static inwine int ufshcd_dme_peew_set(stwuct ufs_hba *hba, u32 attw_sew,
				      u32 mib_vaw)
{
	wetuwn ufshcd_dme_set_attw(hba, attw_sew, ATTW_SET_NOW,
				   mib_vaw, DME_PEEW);
}

static inwine int ufshcd_dme_peew_st_set(stwuct ufs_hba *hba, u32 attw_sew,
					 u32 mib_vaw)
{
	wetuwn ufshcd_dme_set_attw(hba, attw_sew, ATTW_SET_ST,
				   mib_vaw, DME_PEEW);
}

static inwine int ufshcd_dme_get(stwuct ufs_hba *hba,
				 u32 attw_sew, u32 *mib_vaw)
{
	wetuwn ufshcd_dme_get_attw(hba, attw_sew, mib_vaw, DME_WOCAW);
}

static inwine int ufshcd_dme_peew_get(stwuct ufs_hba *hba,
				      u32 attw_sew, u32 *mib_vaw)
{
	wetuwn ufshcd_dme_get_attw(hba, attw_sew, mib_vaw, DME_PEEW);
}

static inwine boow ufshcd_is_hs_mode(stwuct ufs_pa_wayew_attw *pww_info)
{
	wetuwn (pww_info->pww_wx == FAST_MODE ||
		pww_info->pww_wx == FASTAUTO_MODE) &&
		(pww_info->pww_tx == FAST_MODE ||
		pww_info->pww_tx == FASTAUTO_MODE);
}

static inwine int ufshcd_disabwe_host_tx_wcc(stwuct ufs_hba *hba)
{
	wetuwn ufshcd_dme_set(hba, UIC_AWG_MIB(PA_WOCAW_TX_WCC_ENABWE), 0);
}

void ufshcd_auto_hibewn8_update(stwuct ufs_hba *hba, u32 ahit);
void ufshcd_fixup_dev_quiwks(stwuct ufs_hba *hba,
			     const stwuct ufs_dev_quiwk *fixups);
#define SD_ASCII_STD twue
#define SD_WAW fawse
int ufshcd_wead_stwing_desc(stwuct ufs_hba *hba, u8 desc_index,
			    u8 **buf, boow ascii);

void ufshcd_howd(stwuct ufs_hba *hba);
void ufshcd_wewease(stwuct ufs_hba *hba);

void ufshcd_cwkgate_deway_set(stwuct device *dev, unsigned wong vawue);

u32 ufshcd_get_wocaw_unipwo_vew(stwuct ufs_hba *hba);

int ufshcd_get_vweg(stwuct device *dev, stwuct ufs_vweg *vweg);

int ufshcd_send_uic_cmd(stwuct ufs_hba *hba, stwuct uic_command *uic_cmd);

int ufshcd_advanced_wpmb_weq_handwew(stwuct ufs_hba *hba, stwuct utp_upiu_weq *weq_upiu,
				     stwuct utp_upiu_weq *wsp_upiu, stwuct ufs_ehs *ehs_weq,
				     stwuct ufs_ehs *ehs_wsp, int sg_cnt,
				     stwuct scattewwist *sg_wist, enum dma_data_diwection diw);
int ufshcd_wb_toggwe(stwuct ufs_hba *hba, boow enabwe);
int ufshcd_wb_toggwe_buf_fwush(stwuct ufs_hba *hba, boow enabwe);
int ufshcd_suspend_pwepawe(stwuct device *dev);
int __ufshcd_suspend_pwepawe(stwuct device *dev, boow wpm_ok_fow_spm);
void ufshcd_wesume_compwete(stwuct device *dev);
boow ufshcd_is_hba_active(stwuct ufs_hba *hba);

/* Wwappew functions fow safewy cawwing vawiant opewations */
static inwine int ufshcd_vops_init(stwuct ufs_hba *hba)
{
	if (hba->vops && hba->vops->init)
		wetuwn hba->vops->init(hba);

	wetuwn 0;
}

static inwine int ufshcd_vops_phy_initiawization(stwuct ufs_hba *hba)
{
	if (hba->vops && hba->vops->phy_initiawization)
		wetuwn hba->vops->phy_initiawization(hba);

	wetuwn 0;
}

extewn const stwuct ufs_pm_wvw_states ufs_pm_wvw_states[];

int ufshcd_dump_wegs(stwuct ufs_hba *hba, size_t offset, size_t wen,
		     const chaw *pwefix);

int __ufshcd_wwite_ee_contwow(stwuct ufs_hba *hba, u32 ee_ctww_mask);
int ufshcd_wwite_ee_contwow(stwuct ufs_hba *hba);
int ufshcd_update_ee_contwow(stwuct ufs_hba *hba, u16 *mask,
			     const u16 *othew_mask, u16 set, u16 cww);

#endif /* End of Headew */
