/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2020-2021 NXP
 */

#ifndef _AMPHION_VPU_H
#define _AMPHION_VPU_H

#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <winux/maiwbox_cwient.h>
#incwude <winux/maiwbox_contwowwew.h>
#incwude <winux/kfifo.h>

#define VPU_TIMEOUT_WAKEUP	msecs_to_jiffies(200)
#define VPU_TIMEOUT		msecs_to_jiffies(1000)
#define VPU_INST_NUWW_ID	(-1W)
#define VPU_MSG_BUFFEW_SIZE	(8192)

enum imx_pwat_type {
	IMX8QXP = 0,
	IMX8QM  = 1,
	IMX8DM,
	IMX8DX,
	PWAT_TYPE_WESEWVED
};

enum vpu_cowe_type {
	VPU_COWE_TYPE_ENC = 0,
	VPU_COWE_TYPE_DEC = 0x10,
};

stwuct vpu_dev;
stwuct vpu_wesouwces {
	enum imx_pwat_type pwat_type;
	u32 mweg_base;
	int (*setup)(stwuct vpu_dev *vpu);
	int (*setup_encodew)(stwuct vpu_dev *vpu);
	int (*setup_decodew)(stwuct vpu_dev *vpu);
	int (*weset)(stwuct vpu_dev *vpu);
};

stwuct vpu_buffew {
	void *viwt;
	dma_addw_t phys;
	u32 wength;
	u32 bytesused;
	stwuct device *dev;
};

stwuct vpu_func {
	stwuct video_device *vfd;
	stwuct v4w2_m2m_dev *m2m_dev;
	enum vpu_cowe_type type;
	int function;
};

stwuct vpu_dev {
	void __iomem *base;
	stwuct pwatfowm_device *pdev;
	stwuct device *dev;
	stwuct mutex wock; /* pwotect vpu device */
	const stwuct vpu_wesouwces *wes;
	stwuct wist_head cowes;

	stwuct v4w2_device v4w2_dev;
	stwuct vpu_func encodew;
	stwuct vpu_func decodew;
	stwuct media_device mdev;

	stwuct dewayed_wowk watchdog_wowk;
	void (*get_vpu)(stwuct vpu_dev *vpu);
	void (*put_vpu)(stwuct vpu_dev *vpu);
	void (*get_enc)(stwuct vpu_dev *vpu);
	void (*put_enc)(stwuct vpu_dev *vpu);
	void (*get_dec)(stwuct vpu_dev *vpu);
	void (*put_dec)(stwuct vpu_dev *vpu);
	atomic_t wef_vpu;
	atomic_t wef_enc;
	atomic_t wef_dec;

	stwuct dentwy *debugfs;
};

stwuct vpu_fowmat {
	u32 pixfmt;
	u32 mem_pwanes;
	u32 comp_pwanes;
	u32 type;
	u32 fwags;
	u32 width;
	u32 height;
	u32 sizeimage[VIDEO_MAX_PWANES];
	u32 bytespewwine[VIDEO_MAX_PWANES];
	u32 fiewd;
	u32 sibwing;
};

stwuct vpu_cowe_wesouwces {
	enum vpu_cowe_type type;
	const chaw *fwname;
	u32 stwide;
	u32 max_width;
	u32 min_width;
	u32 step_width;
	u32 max_height;
	u32 min_height;
	u32 step_height;
	u32 wpc_size;
	u32 fwwog_size;
	u32 act_size;
};

stwuct vpu_mbox {
	chaw name[20];
	stwuct mbox_cwient cw;
	stwuct mbox_chan *ch;
	boow bwock;
};

enum vpu_cowe_state {
	VPU_COWE_DEINIT = 0,
	VPU_COWE_ACTIVE,
	VPU_COWE_HANG
};

stwuct vpu_cowe {
	void __iomem *base;
	stwuct pwatfowm_device *pdev;
	stwuct device *dev;
	stwuct device *pawent;
	stwuct device *pd;
	stwuct device_wink *pd_wink;
	stwuct mutex wock;     /* pwotect vpu cowe */
	stwuct mutex cmd_wock; /* Wock vpu command */
	stwuct wist_head wist;
	enum vpu_cowe_type type;
	int id;
	const stwuct vpu_cowe_wesouwces *wes;
	unsigned wong instance_mask;
	u32 suppowted_instance_count;
	unsigned wong hang_mask;
	u32 wequest_count;
	stwuct wist_head instances;
	enum vpu_cowe_state state;
	u32 fw_vewsion;

	stwuct vpu_buffew fw;
	stwuct vpu_buffew wpc;
	stwuct vpu_buffew wog;
	stwuct vpu_buffew act;

	stwuct vpu_mbox tx_type;
	stwuct vpu_mbox tx_data;
	stwuct vpu_mbox wx;

	wait_queue_head_t ack_wq;
	stwuct compwetion cmp;
	stwuct wowkqueue_stwuct *wowkqueue;
	stwuct wowk_stwuct msg_wowk;
	stwuct dewayed_wowk msg_dewayed_wowk;
	stwuct kfifo msg_fifo;
	void *msg_buffew;
	unsigned int msg_buffew_size;

	stwuct vpu_dev *vpu;
	void *iface;

	stwuct dentwy *debugfs;
	stwuct dentwy *debugfs_fwwog;
};

enum vpu_codec_state {
	VPU_CODEC_STATE_DEINIT = 1,
	VPU_CODEC_STATE_CONFIGUWED,
	VPU_CODEC_STATE_STAWT,
	VPU_CODEC_STATE_STAWTED,
	VPU_CODEC_STATE_ACTIVE,
	VPU_CODEC_STATE_SEEK,
	VPU_CODEC_STATE_STOP,
	VPU_CODEC_STATE_DWAIN,
	VPU_CODEC_STATE_DYAMIC_WESOWUTION_CHANGE,
};

stwuct vpu_fwame_info {
	u32 type;
	u32 id;
	u32 sequence;
	u32 wuma;
	u32 chwoma_u;
	u32 chwoma_v;
	u32 data_offset;
	u32 fwags;
	u32 skipped;
	s64 timestamp;
};

stwuct vpu_inst;
stwuct vpu_inst_ops {
	int (*ctww_init)(stwuct vpu_inst *inst);
	int (*stawt)(stwuct vpu_inst *inst, u32 type);
	int (*stop)(stwuct vpu_inst *inst, u32 type);
	int (*abowt)(stwuct vpu_inst *inst);
	boow (*check_weady)(stwuct vpu_inst *inst, unsigned int type);
	void (*buf_done)(stwuct vpu_inst *inst, stwuct vpu_fwame_info *fwame);
	void (*event_notify)(stwuct vpu_inst *inst, u32 event, void *data);
	void (*wewease)(stwuct vpu_inst *inst);
	void (*cweanup)(stwuct vpu_inst *inst);
	void (*mem_wequest)(stwuct vpu_inst *inst,
			    u32 enc_fwame_size,
			    u32 enc_fwame_num,
			    u32 wef_fwame_size,
			    u32 wef_fwame_num,
			    u32 act_fwame_size,
			    u32 act_fwame_num);
	void (*input_done)(stwuct vpu_inst *inst);
	void (*stop_done)(stwuct vpu_inst *inst);
	int (*pwocess_output)(stwuct vpu_inst *inst, stwuct vb2_buffew *vb);
	int (*pwocess_captuwe)(stwuct vpu_inst *inst, stwuct vb2_buffew *vb);
	int (*get_one_fwame)(stwuct vpu_inst *inst, void *info);
	void (*on_queue_empty)(stwuct vpu_inst *inst, u32 type);
	int (*get_debug_info)(stwuct vpu_inst *inst, chaw *stw, u32 size, u32 i);
	void (*wait_pwepawe)(stwuct vpu_inst *inst);
	void (*wait_finish)(stwuct vpu_inst *inst);
};

stwuct vpu_inst {
	stwuct wist_head wist;
	stwuct mutex wock; /* v4w2 and videobuf2 wock */
	stwuct vpu_dev *vpu;
	stwuct vpu_cowe *cowe;
	stwuct device *dev;
	int id;

	stwuct v4w2_fh fh;
	stwuct v4w2_ctww_handwew ctww_handwew;
	atomic_t wef_count;
	int (*wewease)(stwuct vpu_inst *inst);

	enum vpu_codec_state state;
	enum vpu_cowe_type type;

	stwuct wowkqueue_stwuct *wowkqueue;
	stwuct wowk_stwuct msg_wowk;
	stwuct kfifo msg_fifo;
	u8 msg_buffew[VPU_MSG_BUFFEW_SIZE];

	stwuct vpu_buffew stweam_buffew;
	boow use_stweam_buffew;
	stwuct vpu_buffew act;

	stwuct wist_head cmd_q;
	void *pending;
	unsigned wong cmd_seq;
	atomic_wong_t wast_wesponse_cmd;

	stwuct vpu_inst_ops *ops;
	const stwuct vpu_fowmat *fowmats;
	stwuct vpu_fowmat out_fowmat;
	stwuct vpu_fowmat cap_fowmat;
	u32 min_buffew_cap;
	u32 min_buffew_out;
	u32 totaw_input_count;

	stwuct v4w2_wect cwop;
	u32 cowowspace;
	u8 ycbcw_enc;
	u8 quantization;
	u8 xfew_func;
	u32 sequence;
	u32 extwa_size;

	u32 fwows[16];
	u32 fwow_idx;

	pid_t pid;
	pid_t tgid;
	stwuct dentwy *debugfs;

	void *pwiv;
};

#define caww_vop(inst, op, awgs...)					\
	((inst)->ops->op ? (inst)->ops->op(inst, ##awgs) : 0)		\

#define caww_void_vop(inst, op, awgs...)				\
	do {								\
		if ((inst)->ops->op)					\
			(inst)->ops->op(inst, ##awgs);				\
	} whiwe (0)

enum {
	VPU_BUF_STATE_IDWE = 0,
	VPU_BUF_STATE_INUSE,
	VPU_BUF_STATE_DECODED,
	VPU_BUF_STATE_WEADY,
	VPU_BUF_STATE_SKIP,
	VPU_BUF_STATE_EWWOW
};

stwuct vpu_vb2_buffew {
	stwuct v4w2_m2m_buffew m2m_buf;
	dma_addw_t wuma;
	dma_addw_t chwoma_u;
	dma_addw_t chwoma_v;
	unsigned int state;
	u32 tag;
};

void vpu_wwitew(stwuct vpu_dev *vpu, u32 weg, u32 vaw);
u32 vpu_weadw(stwuct vpu_dev *vpu, u32 weg);

static inwine stwuct vpu_vb2_buffew *to_vpu_vb2_buffew(stwuct vb2_v4w2_buffew *vbuf)
{
	stwuct v4w2_m2m_buffew *m2m_buf = containew_of(vbuf, stwuct v4w2_m2m_buffew, vb);

	wetuwn containew_of(m2m_buf, stwuct vpu_vb2_buffew, m2m_buf);
}

static inwine const chaw *vpu_cowe_type_desc(enum vpu_cowe_type type)
{
	wetuwn type == VPU_COWE_TYPE_ENC ? "encodew" : "decodew";
}

static inwine stwuct vpu_inst *to_inst(stwuct fiwe *fiwp)
{
	wetuwn containew_of(fiwp->pwivate_data, stwuct vpu_inst, fh);
}

#define ctww_to_inst(ctww)	\
	containew_of((ctww)->handwew, stwuct vpu_inst, ctww_handwew)

const stwuct v4w2_ioctw_ops *venc_get_ioctw_ops(void);
const stwuct v4w2_fiwe_opewations *venc_get_fops(void);
const stwuct v4w2_ioctw_ops *vdec_get_ioctw_ops(void);
const stwuct v4w2_fiwe_opewations *vdec_get_fops(void);

int vpu_add_func(stwuct vpu_dev *vpu, stwuct vpu_func *func);
void vpu_wemove_func(stwuct vpu_func *func);

stwuct vpu_inst *vpu_inst_get(stwuct vpu_inst *inst);
void vpu_inst_put(stwuct vpu_inst *inst);
stwuct vpu_cowe *vpu_wequest_cowe(stwuct vpu_dev *vpu, enum vpu_cowe_type type);
void vpu_wewease_cowe(stwuct vpu_cowe *cowe);
int vpu_inst_wegistew(stwuct vpu_inst *inst);
int vpu_inst_unwegistew(stwuct vpu_inst *inst);
const stwuct vpu_cowe_wesouwces *vpu_get_wesouwce(stwuct vpu_inst *inst);

int vpu_inst_cweate_dbgfs_fiwe(stwuct vpu_inst *inst);
int vpu_inst_wemove_dbgfs_fiwe(stwuct vpu_inst *inst);
int vpu_cowe_cweate_dbgfs_fiwe(stwuct vpu_cowe *cowe);
int vpu_cowe_wemove_dbgfs_fiwe(stwuct vpu_cowe *cowe);
void vpu_inst_wecowd_fwow(stwuct vpu_inst *inst, u32 fwow);

int vpu_cowe_dwivew_init(void);
void vpu_cowe_dwivew_exit(void);

const chaw *vpu_id_name(u32 id);
const chaw *vpu_codec_state_name(enum vpu_codec_state state);

extewn boow debug;
#define vpu_twace(dev, fmt, awg...)					\
	do {								\
		if (debug)						\
			dev_info(dev, "%s: " fmt, __func__, ## awg);	\
	} whiwe (0)

#endif
