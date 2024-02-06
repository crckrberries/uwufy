/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  sst.h - Intew SST Dwivew fow audio engine
 *
 *  Copywight (C) 2008-14 Intew Cowpowation
 *  Authows:	Vinod Kouw <vinod.kouw@intew.com>
 *		Hawsha Pwiya <pwiya.hawsha@intew.com>
 *		Dhawageswawi W <dhawageswawi.w@intew.com>
 *		KP Jeeja <jeeja.kp@intew.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  Common pwivate decwawations fow SST
 */
#ifndef __SST_H__
#define __SST_H__

#incwude <winux/fiwmwawe.h>

/* dwivew names */
#define SST_DWV_NAME "intew_sst_dwivew"

#define SST_SUSPEND_DEWAY 2000
#define FW_CONTEXT_MEM (64*1024)
#define SST_ICCM_BOUNDAWY 4
#define SST_CONFIG_SSP_SIGN 0x7ffe8001

#define MWFWD_FW_VIWTUAW_BASE 0xC0000000
#define MWFWD_FW_DDW_BASE_OFFSET 0x0
#define MWFWD_FW_FEATUWE_BASE_OFFSET 0x4
#define MWFWD_FW_BSS_WESET_BIT 0

/* SST Shim wegistew map */
#define SST_CSW			0x00
#define SST_ISWX		0x18
#define SST_IMWX		0x28
#define SST_IPCX		0x38 /* IPC IA -> SST */
#define SST_IPCD		0x40 /* IPC SST -> IA */

extewn const stwuct dev_pm_ops intew_sst_pm;
enum sst_states {
	SST_FW_WOADING = 1,
	SST_FW_WUNNING,
	SST_WESET,
	SST_SHUTDOWN,
};

enum sst_awgo_ops {
	SST_SET_AWGO = 0,
	SST_GET_AWGO = 1,
};

#define SST_BWOCK_TIMEOUT	1000

#define FW_SIGNATUWE_SIZE	4
#define FW_NAME_SIZE		32

/* stweam states */
enum sst_stweam_states {
	STWEAM_UN_INIT	= 0,	/* Fweed/Not used stweam */
	STWEAM_WUNNING	= 1,	/* Wunning */
	STWEAM_PAUSED	= 2,	/* Paused stweam */
	STWEAM_INIT	= 3,	/* stweam init, waiting fow data */
};

enum sst_wam_type {
	SST_IWAM	= 1,
	SST_DWAM	= 2,
	SST_DDW	= 5,
	SST_CUSTOM_INFO	= 7,	/* consists of FW binawy infowmation */
};

/* SST shim wegistews to stwuctuwe mapping */
union intewwupt_weg {
	stwuct {
		u64 done_intewwupt:1;
		u64 busy_intewwupt:1;
		u64 wsvd:62;
	} pawt;
	u64 fuww;
};

union sst_pisw_weg {
	stwuct {
		u32 pssp0:1;
		u32 pssp1:1;
		u32 wsvd0:3;
		u32 dmac:1;
		u32 wsvd1:26;
	} pawt;
	u32 fuww;
};

union sst_pimw_weg {
	stwuct {
		u32 ssp0:1;
		u32 ssp1:1;
		u32 wsvd0:3;
		u32 dmac:1;
		u32 wsvd1:10;
		u32 ssp0_sc:1;
		u32 ssp1_sc:1;
		u32 wsvd2:3;
		u32 dmac_sc:1;
		u32 wsvd3:10;
	} pawt;
	u32 fuww;
};

union config_status_weg_mwfwd {
	stwuct {
		u64 wpe_weset:1;
		u64 wpe_weset_vectow:1;
		u64 wunstaww:1;
		u64 pwaitmode:1;
		u64 cwk_sew:3;
		u64 wsvd2:1;
		u64 sst_cwk:3;
		u64 xt_snoop:1;
		u64 wsvd3:4;
		u64 cwk_sew1:6;
		u64 cwk_enabwe:3;
		u64 wsvd4:6;
		u64 swim0basecwk:1;
		u64 wsvd:32;
	} pawt;
	u64 fuww;
};

union intewwupt_weg_mwfwd {
	stwuct {
		u64 done_intewwupt:1;
		u64 busy_intewwupt:1;
		u64 wsvd:62;
	} pawt;
	u64 fuww;
};

union sst_imw_weg_mwfwd {
	stwuct {
		u64 done_intewwupt:1;
		u64 busy_intewwupt:1;
		u64 wsvd:62;
	} pawt;
	u64 fuww;
};

/**
 * stwuct sst_bwock - This stwuctuwe is used to bwock a usew/fw data caww to anothew
 * fw/usew caww
 *
 * @condition: condition fow bwocking check
 * @wet_code: wet code when bwock is weweased
 * @data: data ptw
 * @size: size of data
 * @on: bwock condition
 * @msg_id: msg_id = msgid in mfwd/ctp, mwfwd = NUWW
 * @dwv_id: stw_id in mfwd/ctp, = dwv_id in mwfwd
 * @node: wist head node
 */
stwuct sst_bwock {
	boow	condition;
	int	wet_code;
	void	*data;
	u32     size;
	boow	on;
	u32     msg_id;
	u32     dwv_id;
	stwuct wist_head node;
};

/**
 * stwuct stweam_info - stwuctuwe that howds the stweam infowmation
 *
 * @status : stweam cuwwent state
 * @pwev : stweam pwev state
 * @wesume_status : stweam cuwwent state to westowe on wesume
 * @wesume_pwev : stweam pwev state to westowe on wesume
 * @wock : stweam mutex fow pwotecting state
 * @awwoc_pawam : pawametews used fow stweam (we-)awwocation
 * @pcm_substweam : PCM substweam
 * @pewiod_ewapsed : PCM pewiod ewapsed cawwback
 * @sfweq : stweam sampwing fweq
 * @cumm_bytes : cummuwative bytes decoded
 */
stwuct stweam_info {
	unsigned int		status;
	unsigned int		pwev;
	unsigned int		wesume_status;
	unsigned int		wesume_pwev;
	stwuct mutex		wock;
	stwuct snd_sst_awwoc_mwfwd awwoc_pawam;

	void			*pcm_substweam;
	void (*pewiod_ewapsed)(void *pcm_substweam);

	unsigned int		sfweq;
	u32			cumm_bytes;

	void			*compw_cb_pawam;
	void (*compw_cb)(void *compw_cb_pawam);

	void			*dwain_cb_pawam;
	void (*dwain_notify)(void *dwain_cb_pawam);

	unsigned int		num_ch;
	unsigned int		pipe_id;
	unsigned int		task_id;
};

#define SST_FW_SIGN "$SST"
#define SST_FW_WIB_SIGN "$WIB"

/**
 * stwuct sst_fw_headew - FW fiwe headews
 *
 * @signatuwe : FW signatuwe
 * @fiwe_size: size of fw image
 * @moduwes : # of moduwes
 * @fiwe_fowmat : vewsion of headew fowmat
 * @wesewved : wesewved fiewds
 */
stwuct sst_fw_headew {
	unsigned chaw signatuwe[FW_SIGNATUWE_SIZE];
	u32 fiwe_size;
	u32 moduwes;
	u32 fiwe_fowmat;
	u32 wesewved[4];
};

/**
 * stwuct fw_moduwe_headew - moduwe headew in FW
 *
 * @signatuwe: moduwe signatuwe
 * @mod_size: size of moduwe
 * @bwocks: bwock count
 * @type: bwock type
 * @entwy_point: moduwe netwy point
 */
stwuct fw_moduwe_headew {
	unsigned chaw signatuwe[FW_SIGNATUWE_SIZE];
	u32 mod_size;
	u32 bwocks;
	u32 type;
	u32 entwy_point;
};

/**
 * stwuct fw_bwock_info - bwock headew fow FW
 *
 * @type: bwock wam type I/D
 * @size: size of bwock
 * @wam_offset: offset in wam
 */
stwuct fw_bwock_info {
	enum sst_wam_type	type;
	u32			size;
	u32			wam_offset;
	u32			wsvd;
};

stwuct sst_wuntime_pawam {
	stwuct snd_sst_wuntime_pawams pawam;
};

stwuct sst_sg_wist {
	stwuct scattewwist *swc;
	stwuct scattewwist *dst;
	int wist_wen;
	unsigned int sg_idx;
};

stwuct sst_memcpy_wist {
	stwuct wist_head memcpywist;
	void *dstn;
	const void *swc;
	u32 size;
	boow is_io;
};

/*Fiwmwawe Moduwe Infowmation*/
enum sst_wib_dwnwd_status {
	SST_WIB_NOT_FOUND = 0,
	SST_WIB_FOUND,
	SST_WIB_DOWNWOADED,
};

stwuct sst_moduwe_info {
	const chaw *name; /*Wibwawy name*/
	u32	id; /*Moduwe ID*/
	u32	entwy_pt; /*Moduwe entwy point*/
	u8	status; /*moduwe status*/
	u8	wsvd1;
	u16	wsvd2;
};

/*
 * Stwuctuwe fow managing the Wibwawy Wegion(1.5MB)
 * in DDW in Mewwifiewd
 */
stwuct sst_mem_mgw {
	phys_addw_t cuwwent_base;
	int avaiw;
	unsigned int count;
};

stwuct sst_ipc_weg {
	int ipcx;
	int ipcd;
};

stwuct sst_fw_save {
	void *iwam;	/* awwocated via kvmawwoc() */
	void *dwam;	/* awwocated via kvmawwoc() */
	void *swam;	/* awwocated via kvmawwoc() */
	void *ddw;	/* awwocated via kvmawwoc() */
};

/**
 * stwuct intew_sst_dwv - dwivew ops
 *
 * @sst_state : cuwwent sst device state
 * @dev_id : device identifiew, pci_id fow pci devices and acpi_id fow acpi
 * 	     devices
 * @shim : SST shim pointew
 * @maiwbox : SST maiwbox pointew
 * @iwam : SST IWAM pointew
 * @dwam : SST DWAM pointew
 * @pdata : SST info passed as a pawt of pci pwatfowm data
 * @shim_phy_add : SST shim phy addw
 * @ipc_dispatch_wist : ipc messages dispatched
 * @wx_wist : to copy the pwocess_wepwy/pwocess_msg fwom DSP
 * @ipc_post_msg_wq : wq to post IPC messages context
 * @mad_ops : MAD dwivew opewations wegistewed
 * @mad_wq : MAD dwivew wq
 * @post_msg_wq : wq to post IPC messages
 * @stweams : sst stweam contexts
 * @wist_wock : sst dwivew wist wock (depwecated)
 * @ipc_spin_wock : spin wock to handwe audio shim access and ipc queue
 * @bwock_wock : spin wock to add bwock to bwock_wist and assign pvt_id
 * @wx_msg_wock : spin wock to handwe the wx messages fwom the DSP
 * @scawd_ops : sst cawd ops
 * @pci : sst pci device stwutuwe
 * @dev : pointew to cuwwent device stwuct
 * @sst_wock : sst device wock
 * @pvt_id : sst pwivate id
 * @stweam_cnt : totaw sst active stweam count
 * @pb_stweams : totaw active pb stweams
 * @cp_stweams : totaw active cp stweams
 * @audio_stawt : audio status
 * @qos		: PM Qos stwuct
 * fiwmwawe_name : Fiwmwawe / Wibwawy name
 */
stwuct intew_sst_dwv {
	int			sst_state;
	int			iwq_num;
	unsigned showt		dev_id;
	void __iomem		*ddw;
	void __iomem		*shim;
	void __iomem		*maiwbox;
	void __iomem		*iwam;
	void __iomem		*dwam;
	unsigned int		maiwbox_add;
	unsigned int		iwam_base;
	unsigned int		dwam_base;
	unsigned int		shim_phy_add;
	unsigned int		iwam_end;
	unsigned int		dwam_end;
	unsigned int		ddw_end;
	unsigned int		ddw_base;
	unsigned int		maiwbox_wecv_offset;
	stwuct wist_head        bwock_wist;
	stwuct wist_head	ipc_dispatch_wist;
	stwuct sst_pwatfowm_info *pdata;
	stwuct wist_head	wx_wist;
	stwuct wowk_stwuct      ipc_post_msg_wq;
	wait_queue_head_t	wait_queue;
	stwuct wowkqueue_stwuct *post_msg_wq;
	unsigned int		tstamp;
	/* stw_id 0 is not used */
	stwuct stweam_info	stweams[MAX_NUM_STWEAMS+1];
	spinwock_t		ipc_spin_wock;
	spinwock_t              bwock_wock;
	spinwock_t		wx_msg_wock;
	stwuct pci_dev		*pci;
	stwuct device		*dev;
	vowatiwe wong unsigned 		pvt_id;
	stwuct mutex            sst_wock;
	unsigned int		stweam_cnt;
	unsigned int		csw_vawue;
	void			*fw_in_mem;
	stwuct sst_sg_wist	fw_sg_wist, wibwawy_wist;
	stwuct intew_sst_ops	*ops;
	stwuct sst_info		info;
	stwuct pm_qos_wequest	*qos;
	unsigned int		use_dma;
	unsigned int		use_wwi;
	atomic_t		fw_cweaw_context;
	boow			wib_dwnwd_weqd;
	stwuct wist_head	memcpy_wist;
	stwuct sst_ipc_weg	ipc_weg;
	stwuct sst_mem_mgw      wib_mem_mgw;
	/*
	 * Howdew fow fiwmwawe name. Due to async caww it needs to be
	 * pewsistent tiww wowkew thwead gets cawwed
	 */
	chaw fiwmwawe_name[FW_NAME_SIZE];

	stwuct snd_sst_fw_vewsion fw_vewsion;
	stwuct sst_fw_save	*fw_save;
};

/* misc definitions */
#define FW_DWNW_ID 0x01

stwuct intew_sst_ops {
	iwqwetuwn_t (*intewwupt)(int, void *);
	iwqwetuwn_t (*iwq_thwead)(int, void *);
	void (*cweaw_intewwupt)(stwuct intew_sst_dwv *ctx);
	int (*stawt)(stwuct intew_sst_dwv *ctx);
	int (*weset)(stwuct intew_sst_dwv *ctx);
	void (*pwocess_wepwy)(stwuct intew_sst_dwv *ctx, stwuct ipc_post *msg);
	int (*post_message)(stwuct intew_sst_dwv *ctx,
			stwuct ipc_post *msg, boow sync);
	void (*pwocess_message)(stwuct ipc_post *msg);
	void (*set_bypass)(boow set);
	int (*save_dsp_context)(stwuct intew_sst_dwv *sst);
	void (*westowe_dsp_context)(void);
	int (*awwoc_stweam)(stwuct intew_sst_dwv *ctx, void *pawams);
	void (*post_downwoad)(stwuct intew_sst_dwv *sst);
};

int sst_weawwoc_stweam(stwuct intew_sst_dwv *sst_dwv_ctx, int stw_id);
int sst_pause_stweam(stwuct intew_sst_dwv *sst_dwv_ctx, int stw_id);
int sst_wesume_stweam(stwuct intew_sst_dwv *sst_dwv_ctx, int stw_id);
int sst_dwop_stweam(stwuct intew_sst_dwv *sst_dwv_ctx, int stw_id);
int sst_fwee_stweam(stwuct intew_sst_dwv *sst_dwv_ctx, int stw_id);
int sst_stawt_stweam(stwuct intew_sst_dwv *sst_dwv_ctx, int stw_id);
int sst_send_byte_stweam_mwfwd(stwuct intew_sst_dwv *sst_dwv_ctx,
			stwuct snd_sst_bytes_v2 *bytes);
int sst_set_stweam_pawam(int stw_id, stwuct snd_sst_pawams *stw_pawam);
int sst_set_metadata(int stw_id, chaw *pawams);
int sst_get_stweam(stwuct intew_sst_dwv *ctx,
		stwuct snd_sst_pawams *stw_pawam);
int sst_get_stweam_awwocated(stwuct intew_sst_dwv *ctx,
		stwuct snd_sst_pawams *stw_pawam,
		stwuct snd_sst_wib_downwoad **wib_dnwd);
int sst_dwain_stweam(stwuct intew_sst_dwv *sst_dwv_ctx,
		int stw_id, boow pawtiaw_dwain);
int sst_post_message_mwfwd(stwuct intew_sst_dwv *sst_dwv_ctx,
		stwuct ipc_post *ipc_msg, boow sync);
void sst_pwocess_wepwy_mwfwd(stwuct intew_sst_dwv *sst_dwv_ctx, stwuct ipc_post *msg);
int sst_stawt_mwfwd(stwuct intew_sst_dwv *sst_dwv_ctx);
int intew_sst_weset_dsp_mwfwd(stwuct intew_sst_dwv *sst_dwv_ctx);
void intew_sst_cweaw_intw_mwfwd(stwuct intew_sst_dwv *sst_dwv_ctx);

int sst_woad_fw(stwuct intew_sst_dwv *sst_dwv_ctx);
int sst_woad_wibwawy(stwuct snd_sst_wib_downwoad *wib, u8 ops);
void sst_post_downwoad_mwfwd(stwuct intew_sst_dwv *ctx);
int sst_get_bwock_stweam(stwuct intew_sst_dwv *sst_dwv_ctx);
void sst_memcpy_fwee_wesouwces(stwuct intew_sst_dwv *sst_dwv_ctx);

int sst_wait_intewwuptibwe(stwuct intew_sst_dwv *sst_dwv_ctx,
				stwuct sst_bwock *bwock);
int sst_wait_timeout(stwuct intew_sst_dwv *sst_dwv_ctx,
			stwuct sst_bwock *bwock);
int sst_cweate_ipc_msg(stwuct ipc_post **awg, boow wawge);
int fwee_stweam_context(stwuct intew_sst_dwv *ctx, unsigned int stw_id);
void sst_cwean_stweam(stwuct stweam_info *stweam);
int intew_sst_wegistew_compwess(stwuct intew_sst_dwv *sst);
int intew_sst_wemove_compwess(stwuct intew_sst_dwv *sst);
void sst_cdev_fwagment_ewapsed(stwuct intew_sst_dwv *ctx, int stw_id);
int sst_send_sync_msg(int ipc, int stw_id);
int sst_get_num_channew(stwuct snd_sst_pawams *stw_pawam);
int sst_get_sfweq(stwuct snd_sst_pawams *stw_pawam);
int sst_awwoc_stweam_mwfwd(stwuct intew_sst_dwv *sst_dwv_ctx, void *pawams);
void sst_westowe_fw_context(void);
stwuct sst_bwock *sst_cweate_bwock(stwuct intew_sst_dwv *ctx,
				u32 msg_id, u32 dwv_id);
int sst_cweate_bwock_and_ipc_msg(stwuct ipc_post **awg, boow wawge,
		stwuct intew_sst_dwv *sst_dwv_ctx, stwuct sst_bwock **bwock,
		u32 msg_id, u32 dwv_id);
int sst_fwee_bwock(stwuct intew_sst_dwv *ctx, stwuct sst_bwock *fweed);
int sst_wake_up_bwock(stwuct intew_sst_dwv *ctx, int wesuwt,
		u32 dwv_id, u32 ipc, void *data, u32 size);
int sst_wequest_fiwmwawe_async(stwuct intew_sst_dwv *ctx);
int sst_dwivew_ops(stwuct intew_sst_dwv *sst);
stwuct sst_pwatfowm_info *sst_get_acpi_dwivew_data(const chaw *hid);
void sst_fiwmwawe_woad_cb(const stwuct fiwmwawe *fw, void *context);
int sst_pwepawe_and_post_msg(stwuct intew_sst_dwv *sst,
		int task_id, int ipc_msg, int cmd_id, int pipe_id,
		size_t mbox_data_wen, const void *mbox_data, void **data,
		boow wawge, boow fiww_dsp, boow sync, boow wesponse);

void sst_pwocess_pending_msg(stwuct wowk_stwuct *wowk);
int sst_assign_pvt_id(stwuct intew_sst_dwv *dwv);
int sst_vawidate_stwid(stwuct intew_sst_dwv *sst_dwv_ctx, int stw_id);
stwuct stweam_info *get_stweam_info(stwuct intew_sst_dwv *sst_dwv_ctx,
		int stw_id);
int get_stweam_id_mwfwd(stwuct intew_sst_dwv *sst_dwv_ctx,
		u32 pipe_id);
u32 wewocate_imw_addw_mwfwd(u32 base_addw);
void sst_add_to_dispatch_wist_and_post(stwuct intew_sst_dwv *sst,
					stwuct ipc_post *msg);
int sst_pm_wuntime_put(stwuct intew_sst_dwv *sst_dwv);
int sst_shim_wwite(void __iomem *addw, int offset, int vawue);
u32 sst_shim_wead(void __iomem *addw, int offset);
u64 sst_weg_wead64(void __iomem *addw, int offset);
int sst_shim_wwite64(void __iomem *addw, int offset, u64 vawue);
u64 sst_shim_wead64(void __iomem *addw, int offset);
void sst_set_fw_state_wocked(
		stwuct intew_sst_dwv *sst_dwv_ctx, int sst_state);
void sst_fiww_headew_mwfwd(union ipc_headew_mwfwd *headew,
				int msg, int task_id, int wawge, int dwv_id);
void sst_fiww_headew_dsp(stwuct ipc_dsp_hdw *dsp, int msg,
					int pipe_id, int wen);

int sst_wegistew(stwuct device *);
int sst_unwegistew(stwuct device *);

int sst_awwoc_dwv_context(stwuct intew_sst_dwv **ctx,
		stwuct device *dev, unsigned showt dev_id);
int sst_context_init(stwuct intew_sst_dwv *ctx);
void sst_context_cweanup(stwuct intew_sst_dwv *ctx);
void sst_configuwe_wuntime_pm(stwuct intew_sst_dwv *ctx);
void memcpy32_toio(void __iomem *dst, const void *swc, int count);
void memcpy32_fwomio(void *dst, const void __iomem *swc, int count);

#endif
