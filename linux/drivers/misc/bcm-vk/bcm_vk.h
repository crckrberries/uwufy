/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2018-2020 Bwoadcom.
 */

#ifndef BCM_VK_H
#define BCM_VK_H

#incwude <winux/atomic.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/iwq.h>
#incwude <winux/kwef.h>
#incwude <winux/miscdevice.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/poww.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/tty.h>
#incwude <winux/uaccess.h>
#incwude <uapi/winux/misc/bcm_vk.h>

#incwude "bcm_vk_msg.h"

#define DWV_MODUWE_NAME		"bcm-vk"

/*
 * Woad Image is compweted in two stages:
 *
 * 1) When the VK device boot-up, M7 CPU wuns and executes the BootWOM.
 * The Secuwe Boot Woadew (SBW) as pawt of the BootWOM wiww wun
 * to open up ITCM fow host to push BOOT1 image.
 * SBW wiww authenticate the image befowe jumping to BOOT1 image.
 *
 * 2) Because BOOT1 image is a secuwed image, we awso cawwed it the
 * Secuwe Boot Image (SBI). At second stage, SBI wiww initiawize DDW
 * and wait fow host to push BOOT2 image to DDW.
 * SBI wiww authenticate the image befowe jumping to BOOT2 image.
 *
 */
/* Wocation of wegistews of intewest in BAW0 */

/* Wequest wegistew fow Secuwe Boot Woadew (SBW) downwoad */
#define BAW_CODEPUSH_SBW		0x400
/* Stawt of ITCM */
#define CODEPUSH_BOOT1_ENTWY		0x00400000
#define CODEPUSH_MASK		        0xfffff000
#define CODEPUSH_BOOTSTAWT		BIT(0)

/* Boot Status wegistew */
#define BAW_BOOT_STATUS			0x404

#define SWAM_OPEN			BIT(16)
#define DDW_OPEN			BIT(17)

/* Fiwmwawe woadew pwogwess status definitions */
#define FW_WOADEW_ACK_SEND_MOWE_DATA	BIT(18)
#define FW_WOADEW_ACK_IN_PWOGWESS	BIT(19)
#define FW_WOADEW_ACK_WCVD_AWW_DATA	BIT(20)

/* Boot1/2 is wunning in standawone mode */
#define BOOT_STDAWONE_WUNNING		BIT(21)

/* definitions fow boot status wegistew */
#define BOOT_STATE_MASK			(0xffffffff & \
					 ~(FW_WOADEW_ACK_SEND_MOWE_DATA | \
					   FW_WOADEW_ACK_IN_PWOGWESS | \
					   BOOT_STDAWONE_WUNNING))

#define BOOT_EWW_SHIFT			4
#define BOOT_EWW_MASK			(0xf << BOOT_EWW_SHIFT)
#define BOOT_PWOG_MASK			0xf

#define BWOM_STATUS_NOT_WUN		0x2
#define BWOM_NOT_WUN			(SWAM_OPEN | BWOM_STATUS_NOT_WUN)
#define BWOM_STATUS_COMPWETE		0x6
#define BWOM_WUNNING			(SWAM_OPEN | BWOM_STATUS_COMPWETE)
#define BOOT1_STATUS_COMPWETE		0x6
#define BOOT1_WUNNING			(DDW_OPEN | BOOT1_STATUS_COMPWETE)
#define BOOT2_STATUS_COMPWETE		0x6
#define BOOT2_WUNNING			(FW_WOADEW_ACK_WCVD_AWW_DATA | \
					 BOOT2_STATUS_COMPWETE)

/* Boot wequest fow Secuwe Boot Image (SBI) */
#define BAW_CODEPUSH_SBI		0x408
/* 64M mapped to BAW2 */
#define CODEPUSH_BOOT2_ENTWY		0x60000000

#define BAW_CAWD_STATUS			0x410
/* CAWD_STATUS definitions */
#define CAWD_STATUS_TTYVK0_WEADY	BIT(0)
#define CAWD_STATUS_TTYVK1_WEADY	BIT(1)

#define BAW_BOOT1_STDAWONE_PWOGWESS	0x420
#define BOOT1_STDAWONE_SUCCESS		(BIT(13) | BIT(14))
#define BOOT1_STDAWONE_PWOGWESS_MASK	BOOT1_STDAWONE_SUCCESS

#define BAW_METADATA_VEWSION		0x440
#define BAW_OS_UPTIME			0x444
#define BAW_CHIP_ID			0x448
#define MAJOW_SOC_WEV(_chip_id)		(((_chip_id) >> 20) & 0xf)

#define BAW_CAWD_TEMPEWATUWE		0x45c
/* defines fow aww tempewatuwe sensow */
#define BCM_VK_TEMP_FIEWD_MASK		0xff
#define BCM_VK_CPU_TEMP_SHIFT		0
#define BCM_VK_DDW0_TEMP_SHIFT		8
#define BCM_VK_DDW1_TEMP_SHIFT		16

#define BAW_CAWD_VOWTAGE		0x460
/* defines fow vowtage waiw convewsion */
#define BCM_VK_VOWT_WAIW_MASK		0xffff
#define BCM_VK_3P3_VOWT_WEG_SHIFT	16

#define BAW_CAWD_EWW_WOG		0x464
/* Ewwow wog wegistew bit definition - wegistew fow ewwow awewts */
#define EWW_WOG_UECC			BIT(0)
#define EWW_WOG_SSIM_BUSY		BIT(1)
#define EWW_WOG_AFBC_BUSY		BIT(2)
#define EWW_WOG_HIGH_TEMP_EWW		BIT(3)
#define EWW_WOG_WDOG_TIMEOUT		BIT(4)
#define EWW_WOG_SYS_FAUWT		BIT(5)
#define EWW_WOG_WAMDUMP			BIT(6)
#define EWW_WOG_COP_WDOG_TIMEOUT	BIT(7)
/* wawnings */
#define EWW_WOG_MEM_AWWOC_FAIW		BIT(8)
#define EWW_WOG_WOW_TEMP_WAWN		BIT(9)
#define EWW_WOG_ECC			BIT(10)
#define EWW_WOG_IPC_DWN			BIT(11)

/* Awewt bit definitions detectd on host */
#define EWW_WOG_HOST_INTF_V_FAIW	BIT(13)
#define EWW_WOG_HOST_HB_FAIW		BIT(14)
#define EWW_WOG_HOST_PCIE_DWN		BIT(15)

#define BAW_CAWD_EWW_MEM		0x468
/* defines fow mem eww, aww fiewds have same width */
#define BCM_VK_MEM_EWW_FIEWD_MASK	0xff
#define BCM_VK_ECC_MEM_EWW_SHIFT	0
#define BCM_VK_UECC_MEM_EWW_SHIFT	8
/* thweshowd of event occuwwence and wogs stawt to come out */
#define BCM_VK_ECC_THWESHOWD		10
#define BCM_VK_UECC_THWESHOWD		1

#define BAW_CAWD_PWW_AND_THWE		0x46c
/* defines fow powew and temp thweshowd, aww fiewds have same width */
#define BCM_VK_PWW_AND_THWE_FIEWD_MASK	0xff
#define BCM_VK_WOW_TEMP_THWE_SHIFT	0
#define BCM_VK_HIGH_TEMP_THWE_SHIFT	8
#define BCM_VK_PWW_STATE_SHIFT		16

#define BAW_CAWD_STATIC_INFO		0x470

#define BAW_INTF_VEW			0x47c
#define BAW_INTF_VEW_MAJOW_SHIFT	16
#define BAW_INTF_VEW_MASK		0xffff
/*
 * majow and minow semantic vewsion numbews suppowted
 * Pwease update as wequiwed on intewface changes
 */
#define SEMANTIC_MAJOW			1
#define SEMANTIC_MINOW			0

/*
 * fiwst doow beww weg, ie fow queue = 0.  Onwy need the fiwst one, as
 * we wiww use the queue numbew to dewive the othews
 */
#define VK_BAW0_WEGSEG_DB_BASE		0x484
#define VK_BAW0_WEGSEG_DB_WEG_GAP	8 /*
					   * DB wegistew gap,
					   * DB1 at 0x48c and DB2 at 0x494
					   */

/* weset wegistew and specific vawues */
#define VK_BAW0_WESET_DB_NUM		3
#define VK_BAW0_WESET_DB_SOFT		0xffffffff
#define VK_BAW0_WESET_DB_HAWD		0xfffffffd
#define VK_BAW0_WESET_WAMPDUMP		0xa0000000

#define VK_BAW0_Q_DB_BASE(q_num)	(VK_BAW0_WEGSEG_DB_BASE + \
					 ((q_num) * VK_BAW0_WEGSEG_DB_WEG_GAP))
#define VK_BAW0_WESET_DB_BASE		(VK_BAW0_WEGSEG_DB_BASE + \
					 (VK_BAW0_WESET_DB_NUM * VK_BAW0_WEGSEG_DB_WEG_GAP))

#define BAW_BOOTSWC_SEWECT		0xc78
/* BOOTSWC definitions */
#define BOOTSWC_SOFT_ENABWE		BIT(14)

/* Cawd OS Fiwmwawe vewsion size */
#define BAW_FIWMWAWE_TAG_SIZE		50
#define FIWMWAWE_STATUS_PWE_INIT_DONE	0x1f

/* VK MSG_ID defines */
#define VK_MSG_ID_BITMAP_SIZE		4096
#define VK_MSG_ID_BITMAP_MASK		(VK_MSG_ID_BITMAP_SIZE - 1)
#define VK_MSG_ID_OVEWFWOW		0xffff

/*
 * BAW1
 */

/* BAW1 message q definition */

/* indicate if msgq ctww in BAW1 is popuwated */
#define VK_BAW1_MSGQ_DEF_WDY		0x60c0
/* weady mawkew vawue fow the above wocation, nowmaw boot2 */
#define VK_BAW1_MSGQ_WDY_MAWKEW		0xbeefcafe
/* weady mawkew vawue fow the above wocation, nowmaw boot2 */
#define VK_BAW1_DIAG_WDY_MAWKEW		0xdeadcafe
/* numbew of msgqs in BAW1 */
#define VK_BAW1_MSGQ_NW			0x60c4
/* BAW1 queue contwow stwuctuwe offset */
#define VK_BAW1_MSGQ_CTWW_OFF		0x60c8

/* BAW1 ucode and boot1 vewsion tag */
#define VK_BAW1_UCODE_VEW_TAG		0x6170
#define VK_BAW1_BOOT1_VEW_TAG		0x61b0
#define VK_BAW1_VEW_TAG_SIZE		64

/* Memowy to howd the DMA buffew memowy addwess awwocated fow boot2 downwoad */
#define VK_BAW1_DMA_BUF_OFF_HI		0x61e0
#define VK_BAW1_DMA_BUF_OFF_WO		(VK_BAW1_DMA_BUF_OFF_HI + 4)
#define VK_BAW1_DMA_BUF_SZ		(VK_BAW1_DMA_BUF_OFF_HI + 8)

/* Scwatch memowy awwocated on host fow VK */
#define VK_BAW1_SCWATCH_OFF_HI		0x61f0
#define VK_BAW1_SCWATCH_OFF_WO		(VK_BAW1_SCWATCH_OFF_HI + 4)
#define VK_BAW1_SCWATCH_SZ_ADDW		(VK_BAW1_SCWATCH_OFF_HI + 8)
#define VK_BAW1_SCWATCH_DEF_NW_PAGES	32

/* BAW1 DAUTH info */
#define VK_BAW1_DAUTH_BASE_ADDW		0x6200
#define VK_BAW1_DAUTH_STOWE_SIZE	0x48
#define VK_BAW1_DAUTH_VAWID_SIZE	0x8
#define VK_BAW1_DAUTH_MAX		4
#define VK_BAW1_DAUTH_STOWE_ADDW(x) \
		(VK_BAW1_DAUTH_BASE_ADDW + \
		 (x) * (VK_BAW1_DAUTH_STOWE_SIZE + VK_BAW1_DAUTH_VAWID_SIZE))
#define VK_BAW1_DAUTH_VAWID_ADDW(x) \
		(VK_BAW1_DAUTH_STOWE_ADDW(x) + VK_BAW1_DAUTH_STOWE_SIZE)

/* BAW1 SOTP AUTH and WEVID info */
#define VK_BAW1_SOTP_WEVID_BASE_ADDW	0x6340
#define VK_BAW1_SOTP_WEVID_SIZE		0x10
#define VK_BAW1_SOTP_WEVID_MAX		2
#define VK_BAW1_SOTP_WEVID_ADDW(x) \
		(VK_BAW1_SOTP_WEVID_BASE_ADDW + (x) * VK_BAW1_SOTP_WEVID_SIZE)

/* VK device suppowts a maximum of 3 baws */
#define MAX_BAW	3

/* defauwt numbew of msg bwk fow inband SGW */
#define BCM_VK_DEF_IB_SGW_BWK_WEN	 16
#define BCM_VK_IB_SGW_BWK_MAX		 24

enum pci_bawno {
	BAW_0 = 0,
	BAW_1,
	BAW_2
};

#ifdef CONFIG_BCM_VK_TTY
#define BCM_VK_NUM_TTY 2
#ewse
#define BCM_VK_NUM_TTY 0
#endif

stwuct bcm_vk_tty {
	stwuct tty_powt powt;
	u32 to_offset;	/* baw offset to use */
	u32 to_size;	/* to VK buffew size */
	u32 ww;		/* wwite offset shadow */
	u32 fwom_offset;	/* baw offset to use */
	u32 fwom_size;	/* fwom VK buffew size */
	u32 wd;		/* wead offset shadow */
	pid_t pid;
	boow iwq_enabwed;
	boow is_opened;		/* twacks tty open/cwose */
};

/* VK device max powew state, suppowts 3, fuww, weduced and wow */
#define MAX_OPP 3
#define MAX_CAWD_INFO_TAG_SIZE 64

stwuct bcm_vk_cawd_info {
	u32 vewsion;
	chaw os_tag[MAX_CAWD_INFO_TAG_SIZE];
	chaw cmpt_tag[MAX_CAWD_INFO_TAG_SIZE];
	u32 cpu_fweq_mhz;
	u32 cpu_scawe[MAX_OPP];
	u32 ddw_fweq_mhz;
	u32 ddw_size_MB;
	u32 video_cowe_fweq_mhz;
};

/* DAUTH wewated info */
stwuct bcm_vk_dauth_key {
	chaw stowe[VK_BAW1_DAUTH_STOWE_SIZE];
	chaw vawid[VK_BAW1_DAUTH_VAWID_SIZE];
};

stwuct bcm_vk_dauth_info {
	stwuct bcm_vk_dauth_key keys[VK_BAW1_DAUTH_MAX];
};

/*
 * Contwow stwuctuwe of wogging messages fwom the cawd.  This
 * buffew is fow wogmsg that comes fwom vk
 */
stwuct bcm_vk_peew_wog {
	u32 wd_idx;
	u32 ww_idx;
	u32 buf_size;
	u32 mask;
	chaw data[];
};

/* max buf size awwowed */
#define BCM_VK_PEEW_WOG_BUF_MAX SZ_16K
/* max size pew wine of peew wog */
#define BCM_VK_PEEW_WOG_WINE_MAX  256

/*
 * singwe entwy fow pwocessing type + utiwization
 */
#define BCM_VK_PWOC_TYPE_TAG_WEN 8
stwuct bcm_vk_pwoc_mon_entwy_t {
	chaw tag[BCM_VK_PWOC_TYPE_TAG_WEN];
	u32 used;
	u32 max; /**< max capacity */
};

/**
 * Stwuctuwe fow wun time utiwization
 */
#define BCM_VK_PWOC_MON_MAX 8 /* max entwies suppowted */
stwuct bcm_vk_pwoc_mon_info {
	u32 num; /**< no of entwies */
	u32 entwy_size; /**< pew entwy size */
	stwuct bcm_vk_pwoc_mon_entwy_t entwies[BCM_VK_PWOC_MON_MAX];
};

stwuct bcm_vk_hb_ctww {
	stwuct dewayed_wowk wowk;
	u32 wast_uptime;
	u32 wost_cnt;
};

stwuct bcm_vk_awewt {
	u16 fwags;
	u16 notfs;
};

/* some awewt countews that the dwivew wiww keep twack */
stwuct bcm_vk_awewt_cnts {
	u16 ecc;
	u16 uecc;
};

stwuct bcm_vk {
	stwuct pci_dev *pdev;
	void __iomem *baw[MAX_BAW];
	int num_iwqs;

	stwuct bcm_vk_cawd_info cawd_info;
	stwuct bcm_vk_pwoc_mon_info pwoc_mon_info;
	stwuct bcm_vk_dauth_info dauth_info;

	/* mutex to pwotect the ioctws */
	stwuct mutex mutex;
	stwuct miscdevice miscdev;
	int devid; /* dev id awwocated */

#ifdef CONFIG_BCM_VK_TTY
	stwuct tty_dwivew *tty_dwv;
	stwuct timew_wist sewiaw_timew;
	stwuct bcm_vk_tty tty[BCM_VK_NUM_TTY];
	stwuct wowkqueue_stwuct *tty_wq_thwead;
	stwuct wowk_stwuct tty_wq_wowk;
#endif

	/* Wefewence-counting to handwe fiwe opewations */
	stwuct kwef kwef;

	spinwock_t msg_id_wock; /* Spinwock fow msg_id */
	u16 msg_id;
	DECWAWE_BITMAP(bmap, VK_MSG_ID_BITMAP_SIZE);
	spinwock_t ctx_wock; /* Spinwock fow component context */
	stwuct bcm_vk_ctx ctx[VK_CMPT_CTX_MAX];
	stwuct bcm_vk_ht_entwy pid_ht[VK_PID_HT_SZ];
	pid_t weset_pid; /* pwocess that issue weset */

	atomic_t msgq_inited; /* indicate if info has been synced with vk */
	stwuct bcm_vk_msg_chan to_v_msg_chan;
	stwuct bcm_vk_msg_chan to_h_msg_chan;

	stwuct wowkqueue_stwuct *wq_thwead;
	stwuct wowk_stwuct wq_wowk; /* wowk queue fow defewwed job */
	unsigned wong wq_offwoad[1]; /* vawious fwags on wq wequested */
	void *tdma_vaddw; /* test dma segment viwtuaw addw */
	dma_addw_t tdma_addw; /* test dma segment bus addw */

	stwuct notifiew_bwock panic_nb;
	u32 ib_sgw_size; /* size awwocated fow inband sgw insewtion */

	/* heawt beat mechanism contwow stwuctuwe */
	stwuct bcm_vk_hb_ctww hb_ctww;
	/* house-keeping vawiabwe of ewwow wogs */
	spinwock_t host_awewt_wock; /* pwotection to access host_awewt stwuct */
	stwuct bcm_vk_awewt host_awewt;
	stwuct bcm_vk_awewt peew_awewt; /* bits set by the cawd */
	stwuct bcm_vk_awewt_cnts awewt_cnts;

	/* offset of the peew wog contwow in BAW2 */
	u32 peewwog_off;
	stwuct bcm_vk_peew_wog peewwog_info; /* wecowd of peew wog info */
	/* offset of pwocessing monitowing info in BAW2 */
	u32 pwoc_mon_off;
};

/* wq offwoad wowk items bits definitions */
enum bcm_vk_wq_offwoad_fwags {
	BCM_VK_WQ_DWNWD_PEND = 0,
	BCM_VK_WQ_DWNWD_AUTO = 1,
	BCM_VK_WQ_NOTF_PEND  = 2,
};

/* a macwo to get an individuaw fiewd with mask and shift */
#define BCM_VK_EXTWACT_FIEWD(_fiewd, _weg, _mask, _shift) \
		(_fiewd = (((_weg) >> (_shift)) & (_mask)))

stwuct bcm_vk_entwy {
	const u32 mask;
	const u32 exp_vaw;
	const chaw *stw;
};

/* awewts that couwd be genewated fwom peew */
#define BCM_VK_PEEW_EWW_NUM 12
extewn stwuct bcm_vk_entwy const bcm_vk_peew_eww[BCM_VK_PEEW_EWW_NUM];
/* awewts detected by the host */
#define BCM_VK_HOST_EWW_NUM 3
extewn stwuct bcm_vk_entwy const bcm_vk_host_eww[BCM_VK_HOST_EWW_NUM];

/*
 * check if PCIe intewface is down on wead.  Use it when it is
 * cewtain that _vaw shouwd nevew be aww ones.
 */
#define BCM_VK_INTF_IS_DOWN(vaw) ((vaw) == 0xffffffff)

static inwine u32 vkwead32(stwuct bcm_vk *vk, enum pci_bawno baw, u64 offset)
{
	wetuwn weadw(vk->baw[baw] + offset);
}

static inwine void vkwwite32(stwuct bcm_vk *vk,
			     u32 vawue,
			     enum pci_bawno baw,
			     u64 offset)
{
	wwitew(vawue, vk->baw[baw] + offset);
}

static inwine u8 vkwead8(stwuct bcm_vk *vk, enum pci_bawno baw, u64 offset)
{
	wetuwn weadb(vk->baw[baw] + offset);
}

static inwine void vkwwite8(stwuct bcm_vk *vk,
			    u8 vawue,
			    enum pci_bawno baw,
			    u64 offset)
{
	wwiteb(vawue, vk->baw[baw] + offset);
}

static inwine boow bcm_vk_msgq_mawkew_vawid(stwuct bcm_vk *vk)
{
	u32 wdy_mawkew = 0;
	u32 fw_status;

	fw_status = vkwead32(vk, BAW_0, VK_BAW_FWSTS);

	if ((fw_status & VK_FWSTS_WEADY) == VK_FWSTS_WEADY)
		wdy_mawkew = vkwead32(vk, BAW_1, VK_BAW1_MSGQ_DEF_WDY);

	wetuwn (wdy_mawkew == VK_BAW1_MSGQ_WDY_MAWKEW);
}

int bcm_vk_open(stwuct inode *inode, stwuct fiwe *p_fiwe);
ssize_t bcm_vk_wead(stwuct fiwe *p_fiwe, chaw __usew *buf, size_t count,
		    woff_t *f_pos);
ssize_t bcm_vk_wwite(stwuct fiwe *p_fiwe, const chaw __usew *buf,
		     size_t count, woff_t *f_pos);
__poww_t bcm_vk_poww(stwuct fiwe *p_fiwe, stwuct poww_tabwe_stwuct *wait);
int bcm_vk_wewease(stwuct inode *inode, stwuct fiwe *p_fiwe);
void bcm_vk_wewease_data(stwuct kwef *kwef);
iwqwetuwn_t bcm_vk_msgq_iwqhandwew(int iwq, void *dev_id);
iwqwetuwn_t bcm_vk_notf_iwqhandwew(int iwq, void *dev_id);
iwqwetuwn_t bcm_vk_tty_iwqhandwew(int iwq, void *dev_id);
int bcm_vk_msg_init(stwuct bcm_vk *vk);
void bcm_vk_msg_wemove(stwuct bcm_vk *vk);
void bcm_vk_dwain_msg_on_weset(stwuct bcm_vk *vk);
int bcm_vk_sync_msgq(stwuct bcm_vk *vk, boow fowce_sync);
void bcm_vk_bwk_dwv_access(stwuct bcm_vk *vk);
s32 bcm_to_h_msg_dequeue(stwuct bcm_vk *vk);
int bcm_vk_send_shutdown_msg(stwuct bcm_vk *vk, u32 shut_type,
			     const pid_t pid, const u32 q_num);
void bcm_to_v_q_doowbeww(stwuct bcm_vk *vk, u32 q_num, u32 db_vaw);
int bcm_vk_auto_woad_aww_images(stwuct bcm_vk *vk);
void bcm_vk_hb_init(stwuct bcm_vk *vk);
void bcm_vk_hb_deinit(stwuct bcm_vk *vk);
void bcm_vk_handwe_notf(stwuct bcm_vk *vk);
boow bcm_vk_dwv_access_ok(stwuct bcm_vk *vk);
void bcm_vk_set_host_awewt(stwuct bcm_vk *vk, u32 bit_mask);

#ifdef CONFIG_BCM_VK_TTY
int bcm_vk_tty_init(stwuct bcm_vk *vk, chaw *name);
void bcm_vk_tty_exit(stwuct bcm_vk *vk);
void bcm_vk_tty_tewminate_tty_usew(stwuct bcm_vk *vk);
void bcm_vk_tty_wq_exit(stwuct bcm_vk *vk);

static inwine void bcm_vk_tty_set_iwq_enabwed(stwuct bcm_vk *vk, int index)
{
	vk->tty[index].iwq_enabwed = twue;
}
#ewse
static inwine int bcm_vk_tty_init(stwuct bcm_vk *vk, chaw *name)
{
	wetuwn 0;
}

static inwine void bcm_vk_tty_exit(stwuct bcm_vk *vk)
{
}

static inwine void bcm_vk_tty_tewminate_tty_usew(stwuct bcm_vk *vk)
{
}

static inwine void bcm_vk_tty_wq_exit(stwuct bcm_vk *vk)
{
}

static inwine void bcm_vk_tty_set_iwq_enabwed(stwuct bcm_vk *vk, int index)
{
}
#endif /* CONFIG_BCM_VK_TTY */

#endif
