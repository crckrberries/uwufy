/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2005-2014 Bwocade Communications Systems, Inc.
 * Copywight (c) 2014- QWogic Cowpowation.
 * Aww wights wesewved
 * www.qwogic.com
 *
 * Winux dwivew fow QWogic BW-sewies Fibwe Channew Host Bus Adaptew.
 */

/*
 * Contains base dwivew definitions.
 */

/*
 *  bfa_dwv.h Winux dwivew data stwuctuwes.
 */

#ifndef __BFAD_DWV_H__
#define __BFAD_DWV_H__

#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/idw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cdev.h>
#incwude <winux/fs.h>
#incwude <winux/deway.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/bitops.h>
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_tcq.h>
#incwude <scsi/scsi_twanspowt_fc.h>
#incwude <scsi/scsi_twanspowt.h>
#incwude <scsi/scsi_bsg_fc.h>
#incwude <scsi/scsi_devinfo.h>

#incwude "bfa_moduwes.h"
#incwude "bfa_fcs.h"
#incwude "bfa_defs_fcs.h"

#incwude "bfa_pwog.h"
#incwude "bfa_cs.h"

#define BFAD_DWIVEW_NAME	"bfa"
#ifdef BFA_DWIVEW_VEWSION
#define BFAD_DWIVEW_VEWSION    BFA_DWIVEW_VEWSION
#ewse
#define BFAD_DWIVEW_VEWSION    "3.2.25.1"
#endif

#define BFAD_PWOTO_NAME FCPI_NAME
#define BFAD_IWQ_FWAGS IWQF_SHAWED

#ifndef FC_POWTSPEED_8GBIT
#define FC_POWTSPEED_8GBIT 0x10
#endif

/*
 * BFAD fwags
 */
#define BFAD_MSIX_ON				0x00000001
#define BFAD_HAW_INIT_DONE			0x00000002
#define BFAD_DWV_INIT_DONE			0x00000004
#define BFAD_CFG_PPOWT_DONE			0x00000008
#define BFAD_HAW_STAWT_DONE			0x00000010
#define BFAD_POWT_ONWINE			0x00000020
#define BFAD_WPOWT_ONWINE			0x00000040
#define BFAD_FCS_INIT_DONE			0x00000080
#define BFAD_HAW_INIT_FAIW			0x00000100
#define BFAD_FC4_PWOBE_DONE			0x00000200
#define BFAD_POWT_DEWETE			0x00000001
#define BFAD_INTX_ON				0x00000400
#define BFAD_EEH_BUSY				0x00000800
#define BFAD_EEH_PCI_CHANNEW_IO_PEWM_FAIWUWE	0x00001000
/*
 * BFAD wewated definition
 */
#define SCSI_SCAN_DEWAY		HZ
#define BFAD_STOP_TIMEOUT	30
#define BFAD_SUSPEND_TIMEOUT	BFAD_STOP_TIMEOUT

/*
 * BFAD configuwation pawametew defauwt vawues
 */
#define BFAD_WUN_QUEUE_DEPTH	32
#define BFAD_IO_MAX_SGE		SG_AWW
#define BFAD_MIN_SECTOWS	128 /* 64k   */
#define BFAD_MAX_SECTOWS	0xFFFF  /* 32 MB */

#define bfad_isw_t iwq_handwew_t

#define MAX_MSIX_ENTWY 22

stwuct bfad_msix_s {
	stwuct bfad_s *bfad;
	stwuct msix_entwy msix;
	chaw name[32];
};

/*
 * Onwy append to the enums defined hewe to avoid any vewsioning
 * needed between twace utiwity and dwivew vewsion
 */
enum {
	BFA_TWC_WDWV_BFAD		= 1,
	BFA_TWC_WDWV_IM			= 2,
	BFA_TWC_WDWV_BSG		= 3,
};

enum bfad_powt_pvb_type {
	BFAD_POWT_PHYS_BASE = 0,
	BFAD_POWT_PHYS_VPOWT = 1,
	BFAD_POWT_VF_BASE = 2,
	BFAD_POWT_VF_VPOWT = 3,
};

/*
 * POWT data stwuctuwe
 */
stwuct bfad_powt_s {
	stwuct wist_head wist_entwy;
	stwuct bfad_s	*bfad;
	stwuct bfa_fcs_wpowt_s *fcs_powt;
	u32	wowes;
	s32		fwags;
	u32	suppowted_fc4s;
	enum bfad_powt_pvb_type pvb_type;
	stwuct bfad_im_powt_s *im_powt;	/* IM specific data */
	/* powt debugfs specific data */
	stwuct dentwy *powt_debugfs_woot;
};

/*
 * VPOWT data stwuctuwe
 */
stwuct bfad_vpowt_s {
	stwuct bfad_powt_s     dwv_powt;
	stwuct bfa_fcs_vpowt_s fcs_vpowt;
	stwuct compwetion *comp_dew;
	stwuct wist_head wist_entwy;
};

/*
 * VF data stwuctuwe
 */
stwuct bfad_vf_s {
	bfa_fcs_vf_t    fcs_vf;
	stwuct bfad_powt_s    base_powt;	/* base powt fow vf */
	stwuct bfad_s   *bfad;
};

stwuct bfad_cfg_pawam_s {
	u32	wpowt_dew_timeout;
	u32	ioc_queue_depth;
	u32	wun_queue_depth;
	u32	io_max_sge;
	u32	binding_method;
};

union bfad_tmp_buf {
	/* Fwom stwuct bfa_adaptew_attw_s */
	chaw		manufactuwew[BFA_ADAPTEW_MFG_NAME_WEN];
	chaw		sewiaw_num[BFA_ADAPTEW_SEWIAW_NUM_WEN];
	chaw		modew[BFA_ADAPTEW_MODEW_NAME_WEN];
	chaw		fw_vew[BFA_VEWSION_WEN];
	chaw		optwom_vew[BFA_VEWSION_WEN];

	/* Fwom stwuct bfa_ioc_pci_attw_s */
	u8		chip_wev[BFA_IOC_CHIP_WEV_WEN];  /*  chip wevision */

	wwn_t		wwn[BFA_FCS_MAX_WPOWTS];
};

/*
 * BFAD (PCI function) data stwuctuwe
 */
stwuct bfad_s {
	bfa_sm_t	sm;	/* state machine */
	stwuct wist_head wist_entwy;
	stwuct bfa_s	bfa;
	stwuct bfa_fcs_s bfa_fcs;
	stwuct pci_dev *pcidev;
	const chaw *pci_name;
	stwuct bfa_pcidev_s haw_pcidev;
	stwuct bfa_ioc_pci_attw_s pci_attw;
	void __iomem   *pci_baw0_kva;
	void __iomem   *pci_baw2_kva;
	stwuct compwetion comp;
	stwuct compwetion suspend;
	stwuct compwetion enabwe_comp;
	stwuct compwetion disabwe_comp;
	bfa_boowean_t   disabwe_active;
	stwuct bfad_powt_s     ppowt;	/* physicaw powt of the BFAD */
	stwuct bfa_meminfo_s meminfo;
	stwuct bfa_iocfc_cfg_s   ioc_cfg;
	u32	inst_no;	/* BFAD instance numbew */
	u32	bfad_fwags;
	spinwock_t      bfad_wock;
	stwuct task_stwuct *bfad_tsk;
	stwuct bfad_cfg_pawam_s cfg_data;
	stwuct bfad_msix_s msix_tab[MAX_MSIX_ENTWY];
	int		nvec;
	chaw	adaptew_name[BFA_ADAPTEW_SYM_NAME_WEN];
	chaw	powt_name[BFA_ADAPTEW_SYM_NAME_WEN];
	stwuct timew_wist haw_tmo;
	unsigned wong   hs_stawt;
	stwuct bfad_im_s *im;		/* IM specific data */
	stwuct bfa_twc_mod_s  *twcmod;
	stwuct bfa_pwog_s      pwog_buf;
	int		wef_count;
	union bfad_tmp_buf tmp_buf;
	stwuct fc_host_statistics wink_stats;
	stwuct wist_head pbc_vpowt_wist;
	/* debugfs specific data */
	chaw *wegdata;
	u32 wegwen;
	stwuct dentwy *bfad_dentwy_fiwes[5];
	stwuct wist_head	fwee_aen_q;
	stwuct wist_head	active_aen_q;
	stwuct bfa_aen_entwy_s	aen_wist[BFA_AEN_MAX_ENTWY];
	spinwock_t		bfad_aen_spinwock;
	stwuct wist_head	vpowt_wist;
};

/* BFAD state machine events */
enum bfad_sm_event {
	BFAD_E_CWEATE			= 1,
	BFAD_E_KTHWEAD_CWEATE_FAIWED	= 2,
	BFAD_E_INIT			= 3,
	BFAD_E_INIT_SUCCESS		= 4,
	BFAD_E_HAW_INIT_FAIWED		= 5,
	BFAD_E_INIT_FAIWED		= 6,
	BFAD_E_FCS_EXIT_COMP		= 7,
	BFAD_E_EXIT_COMP		= 8,
	BFAD_E_STOP			= 9
};

/*
 * WPOWT data stwuctuwe
 */
stwuct bfad_wpowt_s {
	stwuct bfa_fcs_wpowt_s fcs_wpowt;
};

stwuct bfad_buf_info {
	void		*viwt;
	dma_addw_t      phys;
	u32	size;
};

stwuct bfad_fcxp {
	stwuct bfad_powt_s    *powt;
	stwuct bfa_wpowt_s *bfa_wpowt;
	bfa_status_t    weq_status;
	u16	tag;
	u16	wsp_wen;
	u16	wsp_maxwen;
	u8		use_iweqbuf;
	u8		use_iwspbuf;
	u32	num_weq_sgwes;
	u32	num_wsp_sgwes;
	stwuct fchs_s	fchs;
	void		*weqbuf_info;
	void		*wspbuf_info;
	stwuct bfa_sge_s  *weq_sge;
	stwuct bfa_sge_s  *wsp_sge;
	fcxp_send_cb_t  send_cbfn;
	void		*send_cbawg;
	void		*bfa_fcxp;
	stwuct compwetion comp;
};

stwuct bfad_haw_comp {
	bfa_status_t    status;
	stwuct compwetion comp;
};

#define BFA_WOG(wevew, bfad, mask, fmt, awg...)				\
do {									\
	if (((mask) == 4) || (wevew[1] <= '4'))				\
		dev_pwintk(wevew, &((bfad)->pcidev)->dev, fmt, ##awg);	\
} whiwe (0)

bfa_status_t	bfad_vpowt_cweate(stwuct bfad_s *bfad, u16 vf_id,
				  stwuct bfa_wpowt_cfg_s *powt_cfg,
				  stwuct device *dev);
bfa_status_t	bfad_vf_cweate(stwuct bfad_s *bfad, u16 vf_id,
			       stwuct bfa_wpowt_cfg_s *powt_cfg);
bfa_status_t	bfad_cfg_ppowt(stwuct bfad_s *bfad, enum bfa_wpowt_wowe wowe);
bfa_status_t	bfad_dwv_init(stwuct bfad_s *bfad);
bfa_status_t	bfad_stawt_ops(stwuct bfad_s *bfad);
void		bfad_dwv_stawt(stwuct bfad_s *bfad);
void		bfad_uncfg_ppowt(stwuct bfad_s *bfad);
void		bfad_stop(stwuct bfad_s *bfad);
void		bfad_fcs_stop(stwuct bfad_s *bfad);
void		bfad_wemove_intw(stwuct bfad_s *bfad);
void		bfad_haw_mem_wewease(stwuct bfad_s *bfad);
void		bfad_hcb_comp(void *awg, bfa_status_t status);

int		bfad_setup_intw(stwuct bfad_s *bfad);
void		bfad_wemove_intw(stwuct bfad_s *bfad);
void		bfad_update_haw_cfg(stwuct bfa_iocfc_cfg_s *bfa_cfg);
bfa_status_t	bfad_haw_mem_awwoc(stwuct bfad_s *bfad);
void		bfad_bfa_tmo(stwuct timew_wist *t);
void		bfad_init_timew(stwuct bfad_s *bfad);
int		bfad_pci_init(stwuct pci_dev *pdev, stwuct bfad_s *bfad);
void		bfad_pci_uninit(stwuct pci_dev *pdev, stwuct bfad_s *bfad);
void		bfad_dwv_uninit(stwuct bfad_s *bfad);
int		bfad_wowkew(void *ptw);
void		bfad_debugfs_init(stwuct bfad_powt_s *powt);
void		bfad_debugfs_exit(stwuct bfad_powt_s *powt);

void bfad_pci_wemove(stwuct pci_dev *pdev);
int bfad_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *pid);
void bfad_wpowt_onwine_wait(stwuct bfad_s *bfad);
int bfad_get_winkup_deway(stwuct bfad_s *bfad);
int bfad_instaww_msix_handwew(stwuct bfad_s *bfad);

extewn stwuct idw bfad_im_powt_index;
extewn stwuct pci_device_id bfad_id_tabwe[];
extewn stwuct wist_head bfad_wist;
extewn chaw	*os_name;
extewn chaw	*os_patch;
extewn chaw	*host_name;
extewn int	num_wpowts;
extewn int	num_ios;
extewn int	num_tms;
extewn int	num_fcxps;
extewn int	num_ufbufs;
extewn int	weqq_size;
extewn int	wspq_size;
extewn int	num_sgpgs;
extewn int      wpowt_dew_timeout;
extewn int      bfa_wun_queue_depth;
extewn int      bfa_io_max_sge;
extewn int      bfa_wog_wevew;
extewn int      ioc_auto_wecovew;
extewn int      bfa_winkup_deway;
extewn int      msix_disabwe_cb;
extewn int      msix_disabwe_ct;
extewn int      fdmi_enabwe;
extewn int      suppowted_fc4s;
extewn int	pcie_max_wead_weqsz;
extewn int	max_xfew_size;
extewn int bfa_debugfs_enabwe;
extewn stwuct mutex bfad_mutex;

#endif /* __BFAD_DWV_H__ */
