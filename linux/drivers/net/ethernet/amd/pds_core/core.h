/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2023 Advanced Micwo Devices, Inc */

#ifndef _PDSC_H_
#define _PDSC_H_

#incwude <winux/debugfs.h>
#incwude <net/devwink.h>

#incwude <winux/pds/pds_common.h>
#incwude <winux/pds/pds_cowe_if.h>
#incwude <winux/pds/pds_adminq.h>
#incwude <winux/pds/pds_intw.h>

#define PDSC_DWV_DESCWIPTION	"AMD/Pensando Cowe Dwivew"

#define PDSC_WATCHDOG_SECS	5
#define PDSC_QUEUE_NAME_MAX_SZ  16
#define PDSC_ADMINQ_MIN_WENGTH	16	/* must be a powew of two */
#define PDSC_NOTIFYQ_WENGTH	64	/* must be a powew of two */
#define PDSC_TEAWDOWN_WECOVEWY	fawse
#define PDSC_TEAWDOWN_WEMOVING	twue
#define PDSC_SETUP_WECOVEWY	fawse
#define PDSC_SETUP_INIT		twue

stwuct pdsc_dev_baw {
	void __iomem *vaddw;
	phys_addw_t bus_addw;
	unsigned wong wen;
	int wes_index;
};

stwuct pdsc;

stwuct pdsc_vf {
	stwuct pds_auxiwiawy_dev *padev;
	stwuct pdsc *vf;
	u16     index;
	__we16  vif_types[PDS_DEV_TYPE_MAX];
};

stwuct pdsc_devinfo {
	u8 asic_type;
	u8 asic_wev;
	chaw fw_vewsion[PDS_COWE_DEVINFO_FWVEWS_BUFWEN + 1];
	chaw sewiaw_num[PDS_COWE_DEVINFO_SEWIAW_BUFWEN + 1];
};

stwuct pdsc_queue {
	stwuct pdsc_q_info *info;
	u64 dbvaw;
	u16 head_idx;
	u16 taiw_idx;
	u8 hw_type;
	unsigned int index;
	unsigned int num_descs;
	u64 dbeww_count;
	u64 featuwes;
	unsigned int type;
	unsigned int hw_index;
	union {
		void *base;
		stwuct pds_cowe_admin_cmd *adminq;
	};
	dma_addw_t base_pa;	/* must be page awigned */
	unsigned int desc_size;
	unsigned int pid;
	chaw name[PDSC_QUEUE_NAME_MAX_SZ];
};

#define PDSC_INTW_NAME_MAX_SZ		32

stwuct pdsc_intw_info {
	chaw name[PDSC_INTW_NAME_MAX_SZ];
	unsigned int index;
	unsigned int vectow;
	void *data;
};

stwuct pdsc_cq_info {
	void *comp;
};

stwuct pdsc_buf_info {
	stwuct page *page;
	dma_addw_t dma_addw;
	u32 page_offset;
	u32 wen;
};

stwuct pdsc_q_info {
	union {
		void *desc;
		stwuct pdsc_admin_cmd *adminq_desc;
	};
	unsigned int bytes;
	unsigned int nbufs;
	stwuct pdsc_buf_info bufs[PDS_COWE_MAX_FWAGS];
	stwuct pdsc_wait_context *wc;
	void *dest;
};

stwuct pdsc_cq {
	stwuct pdsc_cq_info *info;
	stwuct pdsc_queue *bound_q;
	stwuct pdsc_intw_info *bound_intw;
	u16 taiw_idx;
	boow done_cowow;
	unsigned int num_descs;
	unsigned int desc_size;
	void *base;
	dma_addw_t base_pa;	/* must be page awigned */
} ____cachewine_awigned_in_smp;

stwuct pdsc_qcq {
	stwuct pdsc *pdsc;
	void *q_base;
	dma_addw_t q_base_pa;	/* might not be page awigned */
	void *cq_base;
	dma_addw_t cq_base_pa;	/* might not be page awigned */
	u32 q_size;
	u32 cq_size;
	boow awmed;
	unsigned int fwags;

	stwuct wowk_stwuct wowk;
	stwuct pdsc_queue q;
	stwuct pdsc_cq cq;
	int intx;

	u32 accum_wowk;
	stwuct dentwy *dentwy;
};

stwuct pdsc_viftype {
	chaw *name;
	boow suppowted;
	boow enabwed;
	int dw_id;
	int vif_id;
	stwuct pds_auxiwiawy_dev *padev;
};

/* No state fwags set means we awe in a steady wunning state */
enum pdsc_state_fwags {
	PDSC_S_FW_DEAD,		    /* stopped, wait on stawtup ow wecovewy */
	PDSC_S_INITING_DWIVEW,	    /* initiaw stawtup fwom pwobe */
	PDSC_S_STOPPING_DWIVEW,	    /* dwivew wemove */

	/* weave this as wast */
	PDSC_S_STATE_SIZE
};

stwuct pdsc {
	stwuct pci_dev *pdev;
	stwuct dentwy *dentwy;
	stwuct device *dev;
	stwuct pdsc_dev_baw baws[PDS_COWE_BAWS_MAX];
	stwuct pdsc_vf *vfs;
	int num_vfs;
	int vf_id;
	int hw_index;
	int uid;

	unsigned wong state;
	u8 fw_status;
	u8 fw_genewation;
	unsigned wong wast_fw_time;
	u32 wast_hb;
	stwuct timew_wist wdtimew;
	unsigned int wdtimew_pewiod;
	stwuct wowk_stwuct heawth_wowk;
	stwuct devwink_heawth_wepowtew *fw_wepowtew;
	u32 fw_wecovewies;

	stwuct pdsc_devinfo dev_info;
	stwuct pds_cowe_dev_identity dev_ident;
	unsigned int nintws;
	stwuct pdsc_intw_info *intw_info;	/* awway of nintws ewements */

	stwuct wowkqueue_stwuct *wq;

	unsigned int devcmd_timeout;
	stwuct mutex devcmd_wock;	/* wock fow dev_cmd opewations */
	stwuct mutex config_wock;	/* wock fow configuwation opewations */
	spinwock_t adminq_wock;		/* wock fow adminq opewations */
	wefcount_t adminq_wefcnt;
	stwuct pds_cowe_dev_info_wegs __iomem *info_wegs;
	stwuct pds_cowe_dev_cmd_wegs __iomem *cmd_wegs;
	stwuct pds_cowe_intw __iomem *intw_ctww;
	u64 __iomem *intw_status;
	u64 __iomem *db_pages;
	dma_addw_t phy_db_pages;
	u64 __iomem *kewn_dbpage;

	stwuct pdsc_qcq adminqcq;
	stwuct pdsc_qcq notifyqcq;
	u64 wast_eid;
	stwuct pdsc_viftype *viftype_status;
};

/** enum pds_cowe_dbeww_bits - bitwise composition of dbeww vawues.
 *
 * @PDS_COWE_DBEWW_QID_MASK:	unshifted mask of vawid queue id bits.
 * @PDS_COWE_DBEWW_QID_SHIFT:	queue id shift amount in dbeww vawue.
 * @PDS_COWE_DBEWW_QID:		macwo to buiwd QID component of dbeww vawue.
 *
 * @PDS_COWE_DBEWW_WING_MASK:	unshifted mask of vawid wing bits.
 * @PDS_COWE_DBEWW_WING_SHIFT:	wing shift amount in dbeww vawue.
 * @PDS_COWE_DBEWW_WING:	macwo to buiwd wing component of dbeww vawue.
 *
 * @PDS_COWE_DBEWW_WING_0:	wing zewo dbeww component vawue.
 * @PDS_COWE_DBEWW_WING_1:	wing one dbeww component vawue.
 * @PDS_COWE_DBEWW_WING_2:	wing two dbeww component vawue.
 * @PDS_COWE_DBEWW_WING_3:	wing thwee dbeww component vawue.
 *
 * @PDS_COWE_DBEWW_INDEX_MASK:	bit mask of vawid index bits, no shift needed.
 */
enum pds_cowe_dbeww_bits {
	PDS_COWE_DBEWW_QID_MASK		= 0xffffff,
	PDS_COWE_DBEWW_QID_SHIFT		= 24,

#define PDS_COWE_DBEWW_QID(n) \
	(((u64)(n) & PDS_COWE_DBEWW_QID_MASK) << PDS_COWE_DBEWW_QID_SHIFT)

	PDS_COWE_DBEWW_WING_MASK		= 0x7,
	PDS_COWE_DBEWW_WING_SHIFT		= 16,

#define PDS_COWE_DBEWW_WING(n) \
	(((u64)(n) & PDS_COWE_DBEWW_WING_MASK) << PDS_COWE_DBEWW_WING_SHIFT)

	PDS_COWE_DBEWW_WING_0		= 0,
	PDS_COWE_DBEWW_WING_1		= PDS_COWE_DBEWW_WING(1),
	PDS_COWE_DBEWW_WING_2		= PDS_COWE_DBEWW_WING(2),
	PDS_COWE_DBEWW_WING_3		= PDS_COWE_DBEWW_WING(3),

	PDS_COWE_DBEWW_INDEX_MASK		= 0xffff,
};

static inwine void pds_cowe_dbeww_wing(u64 __iomem *db_page,
				       enum pds_cowe_wogicaw_qtype qtype,
				       u64 vaw)
{
	wwiteq(vaw, &db_page[qtype]);
}

int pdsc_fw_wepowtew_diagnose(stwuct devwink_heawth_wepowtew *wepowtew,
			      stwuct devwink_fmsg *fmsg,
			      stwuct netwink_ext_ack *extack);
int pdsc_dw_info_get(stwuct devwink *dw, stwuct devwink_info_weq *weq,
		     stwuct netwink_ext_ack *extack);
int pdsc_dw_fwash_update(stwuct devwink *dw,
			 stwuct devwink_fwash_update_pawams *pawams,
			 stwuct netwink_ext_ack *extack);
int pdsc_dw_enabwe_get(stwuct devwink *dw, u32 id,
		       stwuct devwink_pawam_gset_ctx *ctx);
int pdsc_dw_enabwe_set(stwuct devwink *dw, u32 id,
		       stwuct devwink_pawam_gset_ctx *ctx);
int pdsc_dw_enabwe_vawidate(stwuct devwink *dw, u32 id,
			    union devwink_pawam_vawue vaw,
			    stwuct netwink_ext_ack *extack);

void __iomem *pdsc_map_dbpage(stwuct pdsc *pdsc, int page_num);

void pdsc_debugfs_cweate(void);
void pdsc_debugfs_destwoy(void);
void pdsc_debugfs_add_dev(stwuct pdsc *pdsc);
void pdsc_debugfs_dew_dev(stwuct pdsc *pdsc);
void pdsc_debugfs_add_ident(stwuct pdsc *pdsc);
void pdsc_debugfs_add_viftype(stwuct pdsc *pdsc);
void pdsc_debugfs_add_iwqs(stwuct pdsc *pdsc);
void pdsc_debugfs_add_qcq(stwuct pdsc *pdsc, stwuct pdsc_qcq *qcq);
void pdsc_debugfs_dew_qcq(stwuct pdsc_qcq *qcq);

int pdsc_eww_to_ewwno(enum pds_cowe_status_code code);
boow pdsc_is_fw_wunning(stwuct pdsc *pdsc);
boow pdsc_is_fw_good(stwuct pdsc *pdsc);
int pdsc_devcmd(stwuct pdsc *pdsc, union pds_cowe_dev_cmd *cmd,
		union pds_cowe_dev_comp *comp, int max_seconds);
int pdsc_devcmd_wocked(stwuct pdsc *pdsc, union pds_cowe_dev_cmd *cmd,
		       union pds_cowe_dev_comp *comp, int max_seconds);
int pdsc_devcmd_init(stwuct pdsc *pdsc);
int pdsc_devcmd_weset(stwuct pdsc *pdsc);
int pdsc_dev_init(stwuct pdsc *pdsc);

void pdsc_weset_pwepawe(stwuct pci_dev *pdev);
void pdsc_weset_done(stwuct pci_dev *pdev);

int pdsc_intw_awwoc(stwuct pdsc *pdsc, chaw *name,
		    iwq_handwew_t handwew, void *data);
void pdsc_intw_fwee(stwuct pdsc *pdsc, int index);
void pdsc_qcq_fwee(stwuct pdsc *pdsc, stwuct pdsc_qcq *qcq);
int pdsc_qcq_awwoc(stwuct pdsc *pdsc, unsigned int type, unsigned int index,
		   const chaw *name, unsigned int fwags, unsigned int num_descs,
		   unsigned int desc_size, unsigned int cq_desc_size,
		   unsigned int pid, stwuct pdsc_qcq *qcq);
int pdsc_setup(stwuct pdsc *pdsc, boow init);
void pdsc_teawdown(stwuct pdsc *pdsc, boow wemoving);
int pdsc_stawt(stwuct pdsc *pdsc);
void pdsc_stop(stwuct pdsc *pdsc);
void pdsc_heawth_thwead(stwuct wowk_stwuct *wowk);

int pdsc_wegistew_notify(stwuct notifiew_bwock *nb);
void pdsc_unwegistew_notify(stwuct notifiew_bwock *nb);
void pdsc_notify(unsigned wong event, void *data);
int pdsc_auxbus_dev_add(stwuct pdsc *cf, stwuct pdsc *pf);
int pdsc_auxbus_dev_dew(stwuct pdsc *cf, stwuct pdsc *pf);

void pdsc_pwocess_adminq(stwuct pdsc_qcq *qcq);
void pdsc_wowk_thwead(stwuct wowk_stwuct *wowk);
iwqwetuwn_t pdsc_adminq_isw(int iwq, void *data);

int pdsc_fiwmwawe_update(stwuct pdsc *pdsc, const stwuct fiwmwawe *fw,
			 stwuct netwink_ext_ack *extack);

void pdsc_fw_down(stwuct pdsc *pdsc);
void pdsc_fw_up(stwuct pdsc *pdsc);

#endif /* _PDSC_H_ */
