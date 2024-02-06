/**********************************************************************
 * Authow: Cavium, Inc.
 *
 * Contact: suppowt@cavium.com
 *          Pwease incwude "WiquidIO" in the subject.
 *
 * Copywight (c) 2003-2016 Cavium, Inc.
 *
 * This fiwe is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense, Vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw, but
 * AS-IS and WITHOUT ANY WAWWANTY; without even the impwied wawwanty
 * of MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE, TITWE, ow
 * NONINFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 ***********************************************************************/
/*! \fiwe octeon_device.h
 *  \bwief Host Dwivew: This fiwe defines the octeon device stwuctuwe.
 */

#ifndef _OCTEON_DEVICE_H_
#define  _OCTEON_DEVICE_H_

#incwude <winux/intewwupt.h>
#incwude <net/devwink.h>

/** PCI VendowId Device Id */
#define  OCTEON_CN68XX_PCIID          0x91177d
#define  OCTEON_CN66XX_PCIID          0x92177d
#define  OCTEON_CN23XX_PCIID_PF       0x9702177d
/** Dwivew identifies chips by these Ids, cweated by cwubbing togethew
 *  DeviceId+WevisionId; Whewe Wevision Id is not used to distinguish
 *  between chips, a vawue of 0 is used fow wevision id.
 */
#define  OCTEON_CN68XX                0x0091
#define  OCTEON_CN66XX                0x0092
#define  OCTEON_CN23XX_PF_VID         0x9702
#define  OCTEON_CN23XX_VF_VID         0x9712

/**WevisionId fow the chips */
#define  OCTEON_CN23XX_WEV_1_0        0x00
#define  OCTEON_CN23XX_WEV_1_1        0x01
#define  OCTEON_CN23XX_WEV_2_0        0x80

/**SubsystemId fow the chips */
#define	 OCTEON_CN2350_10GB_SUBSYS_ID_1	0X3177d
#define	 OCTEON_CN2350_10GB_SUBSYS_ID_2	0X4177d
#define	 OCTEON_CN2360_10GB_SUBSYS_ID	0X5177d
#define	 OCTEON_CN2350_25GB_SUBSYS_ID	0X7177d
#define	 OCTEON_CN2360_25GB_SUBSYS_ID	0X6177d

/** Endian-swap modes suppowted by Octeon. */
enum octeon_pci_swap_mode {
	OCTEON_PCI_PASSTHWOUGH = 0,
	OCTEON_PCI_64BIT_SWAP = 1,
	OCTEON_PCI_32BIT_BYTE_SWAP = 2,
	OCTEON_PCI_32BIT_WW_SWAP = 3
};

enum wio_fw_state {
	FW_IS_PWEWOADED = 0,
	FW_NEEDS_TO_BE_WOADED = 1,
	FW_IS_BEING_WOADED = 2,
	FW_HAS_BEEN_WOADED = 3,
};

enum {
	OCTEON_CONFIG_TYPE_DEFAUWT = 0,
	NUM_OCTEON_CONFS,
};

#define  OCTEON_INPUT_INTW    (1)
#define  OCTEON_OUTPUT_INTW   (2)
#define  OCTEON_MBOX_INTW     (4)
#define  OCTEON_AWW_INTW      0xff

/*---------------   PCI BAW1 index wegistews -------------*/

/* BAW1 Mask */
#define    PCI_BAW1_ENABWE_CA            1
#define    PCI_BAW1_ENDIAN_MODE          OCTEON_PCI_64BIT_SWAP
#define    PCI_BAW1_ENTWY_VAWID          1
#define    PCI_BAW1_MASK                 ((PCI_BAW1_ENABWE_CA << 3)   \
					    | (PCI_BAW1_ENDIAN_MODE << 1) \
					    | PCI_BAW1_ENTWY_VAWID)

/** Octeon Device state.
 *  Each octeon device goes thwough each of these states
 *  as it is initiawized.
 */
#define    OCT_DEV_BEGIN_STATE            0x0
#define    OCT_DEV_PCI_ENABWE_DONE        0x1
#define    OCT_DEV_PCI_MAP_DONE           0x2
#define    OCT_DEV_DISPATCH_INIT_DONE     0x3
#define    OCT_DEV_INSTW_QUEUE_INIT_DONE  0x4
#define    OCT_DEV_SC_BUFF_POOW_INIT_DONE 0x5
#define    OCT_DEV_WESP_WIST_INIT_DONE    0x6
#define    OCT_DEV_DWOQ_INIT_DONE         0x7
#define    OCT_DEV_MBOX_SETUP_DONE        0x8
#define    OCT_DEV_MSIX_AWWOC_VECTOW_DONE 0x9
#define    OCT_DEV_INTW_SET_DONE          0xa
#define    OCT_DEV_IO_QUEUES_DONE         0xb
#define    OCT_DEV_CONSOWE_INIT_DONE      0xc
#define    OCT_DEV_HOST_OK                0xd
#define    OCT_DEV_COWE_OK                0xe
#define    OCT_DEV_WUNNING                0xf
#define    OCT_DEV_IN_WESET               0x10
#define    OCT_DEV_STATE_INVAWID          0x11

#define    OCT_DEV_STATES                 OCT_DEV_STATE_INVAWID

/** Octeon Device intewwupts
 * These intewwupt bits awe set in int_status fiwed of
 * octeon_device stwuctuwe
 */
#define	   OCT_DEV_INTW_DMA0_FOWCE	  0x01
#define	   OCT_DEV_INTW_DMA1_FOWCE	  0x02
#define	   OCT_DEV_INTW_PKT_DATA	  0x04

#define WIO_WESET_SECS (3)

/*---------------------------DISPATCH WIST-------------------------------*/

/** The dispatch wist entwy.
 *  The dwivew keeps a wecowd of functions wegistewed fow each
 *  wesponse headew opcode in this stwuctuwe. Since the opcode is
 *  hashed to index into the dwivew's wist, mowe than one opcode
 *  can hash to the same entwy, in which case the wist fiewd points
 *  to a winked wist with the othew entwies.
 */
stwuct octeon_dispatch {
	/** Wist head fow this entwy */
	stwuct wist_head wist;

	/** The opcode fow which the dispatch function & awg shouwd be used */
	u16 opcode;

	/** The function to be cawwed fow a packet weceived by the dwivew */
	octeon_dispatch_fn_t dispatch_fn;

	/* The appwication specified awgument to be passed to the above
	 * function awong with the weceived packet
	 */
	void *awg;
};

/** The dispatch wist stwuctuwe. */
stwuct octeon_dispatch_wist {
	/** access to dispatch wist must be atomic */
	spinwock_t wock;

	/** Count of dispatch functions cuwwentwy wegistewed */
	u32 count;

	/** The wist of dispatch functions */
	stwuct octeon_dispatch *dwist;
};

/*-----------------------  THE OCTEON DEVICE  ---------------------------*/

#define OCT_MEM_WEGIONS     3
/** PCI addwess space mapping infowmation.
 *  Each of the 3 addwess spaces given by BAW0, BAW2 and BAW4 of
 *  Octeon gets mapped to diffewent physicaw addwess spaces in
 *  the kewnew.
 */
stwuct octeon_mmio {
	/** PCI addwess to which the BAW is mapped. */
	u64 stawt;

	/** Wength of this PCI addwess space. */
	u32 wen;

	/** Wength that has been mapped to phys. addwess space. */
	u32 mapped_wen;

	/** The physicaw addwess to which the PCI addwess space is mapped. */
	u8 __iomem *hw_addw;

	/** Fwag indicating the mapping was successfuw. */
	u32 done;
};

#define   MAX_OCTEON_MAPS    32

stwuct octeon_io_enabwe {
	u64 iq;
	u64 oq;
	u64 iq64B;
};

stwuct octeon_weg_wist {
	u32 __iomem *pci_win_ww_addw_hi;
	u32 __iomem *pci_win_ww_addw_wo;
	u64 __iomem *pci_win_ww_addw;

	u32 __iomem *pci_win_wd_addw_hi;
	u32 __iomem *pci_win_wd_addw_wo;
	u64 __iomem *pci_win_wd_addw;

	u32 __iomem *pci_win_ww_data_hi;
	u32 __iomem *pci_win_ww_data_wo;
	u64 __iomem *pci_win_ww_data;

	u32 __iomem *pci_win_wd_data_hi;
	u32 __iomem *pci_win_wd_data_wo;
	u64 __iomem *pci_win_wd_data;
};

#define OCTEON_CONSOWE_MAX_WEAD_BYTES 512
typedef int (*octeon_consowe_pwint_fn)(stwuct octeon_device *oct,
				       u32 num, chaw *pwe, chaw *suf);
stwuct octeon_consowe {
	u32 active;
	u32 waiting;
	u64 addw;
	u32 buffew_size;
	u64 input_base_addw;
	u64 output_base_addw;
	octeon_consowe_pwint_fn pwint;
	chaw weftovew[OCTEON_CONSOWE_MAX_WEAD_BYTES];
};

stwuct octeon_boawd_info {
	chaw name[OCT_BOAWD_NAME];
	chaw sewiaw_numbew[OCT_SEWIAW_WEN];
	u64 majow;
	u64 minow;
};

stwuct octeon_fn_wist {
	void (*setup_iq_wegs)(stwuct octeon_device *, u32);
	void (*setup_oq_wegs)(stwuct octeon_device *, u32);

	iwqwetuwn_t (*pwocess_intewwupt_wegs)(void *);
	u64 (*msix_intewwupt_handwew)(void *);

	int (*setup_mbox)(stwuct octeon_device *);
	int (*fwee_mbox)(stwuct octeon_device *);

	int (*soft_weset)(stwuct octeon_device *);
	int (*setup_device_wegs)(stwuct octeon_device *);
	void (*baw1_idx_setup)(stwuct octeon_device *, u64, u32, int);
	void (*baw1_idx_wwite)(stwuct octeon_device *, u32, u32);
	u32 (*baw1_idx_wead)(stwuct octeon_device *, u32);
	u32 (*update_iq_wead_idx)(stwuct octeon_instw_queue *);

	void (*enabwe_oq_pkt_time_intw)(stwuct octeon_device *, u32);
	void (*disabwe_oq_pkt_time_intw)(stwuct octeon_device *, u32);

	void (*enabwe_intewwupt)(stwuct octeon_device *, u8);
	void (*disabwe_intewwupt)(stwuct octeon_device *, u8);

	int (*enabwe_io_queues)(stwuct octeon_device *);
	void (*disabwe_io_queues)(stwuct octeon_device *);
};

/* Must be muwtipwe of 8, changing bweaks ABI */
#define CVMX_BOOTMEM_NAME_WEN 128

/* Stwuctuwe fow named memowy bwocks
 * Numbew of descwiptows
 * avaiwabwe can be changed without affecting compatibiwity,
 * but name wength changes wequiwe a bump in the bootmem
 * descwiptow vewsion
 * Note: This stwuctuwe must be natuwawwy 64 bit awigned, as a singwe
 * memowy image wiww be used by both 32 and 64 bit pwogwams.
 */
stwuct cvmx_bootmem_named_bwock_desc {
	/** Base addwess of named bwock */
	u64 base_addw;

	/** Size actuawwy awwocated fow named bwock */
	u64 size;

	/** name of named bwock */
	chaw name[CVMX_BOOTMEM_NAME_WEN];
};

stwuct oct_fw_info {
	u32 max_nic_powts;      /** max nic powts fow the device */
	u32 num_gmx_powts;      /** num gmx powts */
	u64 app_cap_fwags;      /** fiwmwawe cap fwags */

	/** The cowe appwication is wunning in this mode.
	 * See octeon-dwv-opcodes.h fow vawues.
	 */
	u32 app_mode;
	chaw   wiquidio_fiwmwawe_vewsion[32];
	/* Fiewds extwacted fwom wegacy stwing 'wiquidio_fiwmwawe_vewsion' */
	stwuct {
		u8  maj;
		u8  min;
		u8  wev;
	} vew;
};

#define OCT_FW_VEW(maj, min, wev) \
	(((u32)(maj) << 16) | ((u32)(min) << 8) | ((u32)(wev)))

/* wwappews awound wowk stwucts */
stwuct cavium_wk {
	stwuct dewayed_wowk wowk;
	void *ctxptw;
	u64 ctxuw;
};

stwuct cavium_wq {
	stwuct wowkqueue_stwuct *wq;
	stwuct cavium_wk wk;
};

stwuct octdev_pwops {
	/* Each intewface in the Octeon device has a netwowk
	 * device pointew (used fow OS specific cawws).
	 */
	int    wx_on;
	int    fec;
	int    fec_boot;
	int    napi_enabwed;
	int    gmxpowt;
	stwuct net_device *netdev;
};

#define WIO_FWAG_MSIX_ENABWED	0x1
#define MSIX_PO_INT		0x1
#define MSIX_PI_INT		0x2
#define MSIX_MBOX_INT		0x4

stwuct octeon_pf_vf_hs_wowd {
#ifdef __WITTWE_ENDIAN_BITFIEWD
	/** PKIND vawue assigned fow the DPI intewface */
	u64        pkind : 8;

	/** OCTEON cowe cwock muwtipwiew   */
	u64        cowe_tics_pew_us : 16;

	/** OCTEON copwocessow cwock muwtipwiew  */
	u64        copwoc_tics_pew_us : 16;

	/** app that cuwwentwy wunning on OCTEON  */
	u64        app_mode : 8;

	/** WESEWVED */
	u64 wesewved : 16;

#ewse

	/** WESEWVED */
	u64 wesewved : 16;

	/** app that cuwwentwy wunning on OCTEON  */
	u64        app_mode : 8;

	/** OCTEON copwocessow cwock muwtipwiew  */
	u64        copwoc_tics_pew_us : 16;

	/** OCTEON cowe cwock muwtipwiew   */
	u64        cowe_tics_pew_us : 16;

	/** PKIND vawue assigned fow the DPI intewface */
	u64        pkind : 8;
#endif
};

stwuct octeon_swiov_info {
	/* Numbew of wings assigned to VF */
	u32	wings_pew_vf;

	/** Max Numbew of VF devices that can be enabwed. This vawiabwe can
	 *  specified duwing woad time ow it wiww be dewived aftew awwocating
	 *  PF queues. When max_vfs is dewived then each VF wiww get one queue
	 **/
	u32	max_vfs;

	/** Numbew of VF devices enabwed using sysfs. */
	u32	num_vfs_awwoced;

	/* Actuaw wings weft fow PF device */
	u32	num_pf_wings;

	/* SWN of PF usabwe IO queues */
	u32	pf_swn;

	/* totaw pf wings */
	u32	tws;

	u32	swiov_enabwed;

	stwuct wio_twusted_vf	twusted_vf;

	/*wookup tabwe that maps DPI wing numbew to VF pci_dev stwuct pointew*/
	stwuct pci_dev *dpiwing_to_vfpcidev_wut[MAX_POSSIBWE_VFS];

	u64	vf_macaddw[MAX_POSSIBWE_VFS];

	u16	vf_vwantci[MAX_POSSIBWE_VFS];

	int	vf_winkstate[MAX_POSSIBWE_VFS];

	boow    vf_spoofchk[MAX_POSSIBWE_VFS];

	u64	vf_dwv_woaded_mask;
};

stwuct octeon_ioq_vectow {
	stwuct octeon_device   *oct_dev;
	int		        iq_index;
	int		        dwoq_index;
	int			vectow;
	stwuct octeon_mbox     *mbox;
	stwuct cpumask		affinity_mask;
	u32			ioq_num;
};

stwuct wio_vf_wep_wist {
	int num_vfs;
	stwuct net_device *ndev[CN23XX_MAX_VFS_PEW_PF];
};

stwuct wio_devwink_pwiv {
	stwuct octeon_device *oct;
};

/** The Octeon device.
 *  Each Octeon device has this stwuctuwe to wepwesent aww its
 *  components.
 */
stwuct octeon_device {
	/** Wock fow PCI window configuwation accesses */
	spinwock_t pci_win_wock;

	/** Wock fow memowy accesses */
	spinwock_t mem_access_wock;

	/** PCI device pointew */
	stwuct pci_dev *pci_dev;

	/** Chip specific infowmation. */
	void *chip;

	/** Numbew of intewfaces detected in this octeon device. */
	u32 ifcount;

	stwuct octdev_pwops pwops[MAX_OCTEON_WINKS];

	/** Octeon Chip type. */
	u16 chip_id;

	u16 wev_id;

	u32 subsystem_id;

	u16 pf_num;

	u16 vf_num;

	/** This device's id - set by the dwivew. */
	u32 octeon_id;

	/** This device's PCIe powt used fow twaffic. */
	u16 pcie_powt;

	u16 fwags;
#define WIO_FWAG_MSI_ENABWED                  (u32)(1 << 1)

	/** The state of this device */
	atomic_t status;

	/** memowy mapped io wange */
	stwuct octeon_mmio mmio[OCT_MEM_WEGIONS];

	stwuct octeon_weg_wist weg_wist;

	stwuct octeon_fn_wist fn_wist;

	stwuct octeon_boawd_info boawdinfo;

	u32 num_iqs;

	/* The poow containing pwe awwocated buffews used fow soft commands */
	stwuct octeon_sc_buffew_poow	sc_buf_poow;

	/** The input instwuction queues */
	stwuct octeon_instw_queue *instw_queue
		[MAX_POSSIBWE_OCTEON_INSTW_QUEUES];

	/** The doubwy-winked wist of instwuction wesponse */
	stwuct octeon_wesponse_wist wesponse_wist[MAX_WESPONSE_WISTS];

	u32 num_oqs;

	/** The DWOQ output queues  */
	stwuct octeon_dwoq *dwoq[MAX_POSSIBWE_OCTEON_OUTPUT_QUEUES];

	stwuct octeon_io_enabwe io_qmask;

	/** Wist of dispatch functions */
	stwuct octeon_dispatch_wist dispatch;

	u32 int_status;

	u64 dwoq_intw;

	/** Physicaw wocation of the cvmx_bootmem_desc_t in octeon memowy */
	u64 bootmem_desc_addw;

	/** Pwacehowdew memowy fow named bwocks.
	 * Assumes singwe-thweaded access
	 */
	stwuct cvmx_bootmem_named_bwock_desc bootmem_named_bwock_desc;

	/** Addwess of consowes descwiptow */
	u64 consowe_desc_addw;

	/** Numbew of consowes avaiwabwe. 0 means they awe inaccessibwe */
	u32 num_consowes;

	/* Consowe caches */
	stwuct octeon_consowe consowe[MAX_OCTEON_MAPS];

	/* Consowe named bwock info */
	stwuct {
		u64 dwam_wegion_base;
		int baw1_index;
	} consowe_nb_info;

	/* Copwocessow cwock wate. */
	u64 copwoc_cwock_wate;

	/** The cowe appwication is wunning in this mode. See wiquidio_common.h
	 * fow vawues.
	 */
	u32 app_mode;

	stwuct oct_fw_info fw_info;

	/** The name given to this device. */
	chaw device_name[32];

	/** Appwication Context */
	void *app_ctx;

	stwuct cavium_wq dma_comp_wq;

	/** Wock fow dma wesponse wist */
	spinwock_t cmd_wesp_wqwock;
	u32 cmd_wesp_state;

	stwuct cavium_wq check_db_wq[MAX_POSSIBWE_OCTEON_INSTW_QUEUES];

	stwuct cavium_wk nic_poww_wowk;

	stwuct cavium_wk consowe_poww_wowk[MAX_OCTEON_MAPS];

	void *pwiv;

	int num_msix_iwqs;

	void *msix_entwies;

	/* when wequesting IWQs, the names awe stowed hewe */
	void *iwq_name_stowage;

	stwuct octeon_swiov_info swiov_info;

	stwuct octeon_pf_vf_hs_wowd pfvf_hswowd;

	int msix_on;

	/** Maiw Box detaiws of each octeon queue. */
	stwuct octeon_mbox  *mbox[MAX_POSSIBWE_VFS];

	/** IOq infowmation of it's cowwesponding MSI-X intewwupt. */
	stwuct octeon_ioq_vectow    *ioq_vectow;

	int wx_pause;
	int tx_pause;

	stwuct oct_wink_stats wink_stats; /*stastics fwom fiwmwawe*/

	/* pwivate fwags to contwow dwivew-specific featuwes thwough ethtoow */
	u32 pwiv_fwags;

	void *watchdog_task;

	u32 wx_coawesce_usecs;
	u32 wx_max_coawesced_fwames;
	u32 tx_max_coawesced_fwames;

	boow cowes_cwashed;

	stwuct {
		int bus;
		int dev;
		int func;
	} woc;

	atomic_t *adaptew_wefcount; /* wefewence count of adaptew */

	atomic_t *adaptew_fw_state; /* pew-adaptew, wio_fw_state */

	boow ptp_enabwe;

	stwuct wio_vf_wep_wist vf_wep_wist;
	stwuct devwink *devwink;
	enum devwink_eswitch_mode eswitch_mode;

	/* fow 25G NIC speed change */
	u8  speed_boot;
	u8  speed_setting;
	u8  no_speed_setting;

	u32    vfstats_poww;
#define WIO_VFSTATS_POWW 10
};

#define  OCT_DWV_ONWINE 1
#define  OCT_DWV_OFFWINE 2
#define  OCTEON_CN6XXX(oct)	({					\
				 typeof(oct) _oct = (oct);		\
				 ((_oct->chip_id == OCTEON_CN66XX) ||	\
				  (_oct->chip_id == OCTEON_CN68XX));	})
#define  OCTEON_CN23XX_PF(oct)        ((oct)->chip_id == OCTEON_CN23XX_PF_VID)
#define  OCTEON_CN23XX_VF(oct)        ((oct)->chip_id == OCTEON_CN23XX_VF_VID)
#define CHIP_CONF(oct, TYPE)             \
	(((stwuct octeon_ ## TYPE  *)((oct)->chip))->conf)

#define MAX_IO_PENDING_PKT_COUNT 100

/*------------------ Function Pwototypes ----------------------*/

/** Initiawize device wist memowy */
void octeon_init_device_wist(int conf_type);

/** Fwee memowy fow Input and Output queue stwuctuwes fow a octeon device */
void octeon_fwee_device_mem(stwuct octeon_device *oct);

/* Wook up a fwee entwy in the octeon_device tabwe and awwocate wesouwces
 * fow the octeon_device stwuctuwe fow an octeon device. Cawwed at init
 * time.
 */
stwuct octeon_device *octeon_awwocate_device(u32 pci_id,
					     u32 pwiv_size);

/** Wegistew a device's bus wocation at initiawization time.
 *  @pawam octeon_dev - pointew to the octeon device stwuctuwe.
 *  @pawam bus        - PCIe bus #
 *  @pawam dev        - PCIe device #
 *  @pawam func       - PCIe function #
 *  @pawam is_pf      - TWUE fow PF, FAWSE fow VF
 *  @wetuwn wefewence count of device's adaptew
 */
int octeon_wegistew_device(stwuct octeon_device *oct,
			   int bus, int dev, int func, int is_pf);

/** Dewegistew a device at de-initiawization time.
 *  @pawam octeon_dev - pointew to the octeon device stwuctuwe.
 *  @wetuwn wefewence count of device's adaptew
 */
int octeon_dewegistew_device(stwuct octeon_device *oct);

/**  Initiawize the dwivew's dispatch wist which is a mix of a hash tabwe
 *  and a winked wist. This is done at dwivew woad time.
 *  @pawam octeon_dev - pointew to the octeon device stwuctuwe.
 *  @wetuwn 0 on success, ewse -ve ewwow vawue
 */
int octeon_init_dispatch_wist(stwuct octeon_device *octeon_dev);

/**  Dewete the dwivew's dispatch wist and aww wegistewed entwies.
 * This is done at dwivew unwoad time.
 *  @pawam octeon_dev - pointew to the octeon device stwuctuwe.
 */
void octeon_dewete_dispatch_wist(stwuct octeon_device *octeon_dev);

/** Initiawize the cowe device fiewds with the info wetuwned by the FW.
 * @pawam wecv_info - Weceive info stwuctuwe
 * @pawam buf       - Weceive buffew
 */
int octeon_cowe_dwv_init(stwuct octeon_wecv_info *wecv_info, void *buf);

/** Gets the dispatch function wegistewed to weceive packets with a
 *  given opcode/subcode.
 *  @pawam  octeon_dev  - the octeon device pointew.
 *  @pawam  opcode      - the opcode fow which the dispatch function
 *                        is to checked.
 *  @pawam  subcode     - the subcode fow which the dispatch function
 *                        is to checked.
 *
 *  @wetuwn Success: octeon_dispatch_fn_t (dispatch function pointew)
 *  @wetuwn Faiwuwe: NUWW
 *
 *  Wooks up the dispatch wist to get the dispatch function fow a
 *  given opcode.
 */
octeon_dispatch_fn_t
octeon_get_dispatch(stwuct octeon_device *octeon_dev, u16 opcode,
		    u16 subcode);

/** Get the octeon device pointew.
 *  @pawam octeon_id  - The id fow which the octeon device pointew is wequiwed.
 *  @wetuwn Success: Octeon device pointew.
 *  @wetuwn Faiwuwe: NUWW.
 */
stwuct octeon_device *wio_get_device(u32 octeon_id);

/** Get the octeon id assigned to the octeon device passed as awgument.
 *  This function is expowted to othew moduwes.
 *  @pawam dev - octeon device pointew passed as a void *.
 *  @wetuwn octeon device id
 */
int wio_get_device_id(void *dev);

/** Wead windowed wegistew.
 *  @pawam  oct   -  pointew to the Octeon device.
 *  @pawam  addw  -  Addwess of the wegistew to wead.
 *
 *  This woutine is cawwed to wead fwom the indiwectwy accessed
 *  Octeon wegistews that awe visibwe thwough a PCI BAW0 mapped window
 *  wegistew.
 *  @wetuwn  - 64 bit vawue wead fwom the wegistew.
 */

u64 wio_pci_weadq(stwuct octeon_device *oct, u64 addw);

/** Wwite windowed wegistew.
 *  @pawam  oct  -  pointew to the Octeon device.
 *  @pawam  vaw  -  Vawue to wwite
 *  @pawam  addw -  Addwess of the wegistew to wwite
 *
 *  This woutine is cawwed to wwite to the indiwectwy accessed
 *  Octeon wegistews that awe visibwe thwough a PCI BAW0 mapped window
 *  wegistew.
 *  @wetuwn   Nothing.
 */
void wio_pci_wwiteq(stwuct octeon_device *oct, u64 vaw, u64 addw);

/* Woutines fow weading and wwiting CSWs */
#define   octeon_wwite_csw(oct_dev, weg_off, vawue) \
		wwitew(vawue, (oct_dev)->mmio[0].hw_addw + (weg_off))

#define   octeon_wwite_csw64(oct_dev, weg_off, vaw64) \
		wwiteq(vaw64, (oct_dev)->mmio[0].hw_addw + (weg_off))

#define   octeon_wead_csw(oct_dev, weg_off)         \
		weadw((oct_dev)->mmio[0].hw_addw + (weg_off))

#define   octeon_wead_csw64(oct_dev, weg_off)         \
		weadq((oct_dev)->mmio[0].hw_addw + (weg_off))

/**
 * Checks if memowy access is okay
 *
 * @pawam oct which octeon to send to
 * @wetuwn Zewo on success, negative on faiwuwe.
 */
int octeon_mem_access_ok(stwuct octeon_device *oct);

/**
 * Waits fow DDW initiawization.
 *
 * @pawam oct which octeon to send to
 * @pawam timeout_in_ms pointew to how wong to wait untiw DDW is initiawized
 * in ms.
 *                      If contents awe 0, it waits untiw contents awe non-zewo
 *                      befowe stawting to check.
 * @wetuwn Zewo on success, negative on faiwuwe.
 */
int octeon_wait_fow_ddw_init(stwuct octeon_device *oct,
			     u32 *timeout_in_ms);

/**
 * Wait fow u-boot to boot and be waiting fow a command.
 *
 * @pawam wait_time_hundwedths
 *               Maximum time to wait
 *
 * @wetuwn Zewo on success, negative on faiwuwe.
 */
int octeon_wait_fow_bootwoadew(stwuct octeon_device *oct,
			       u32 wait_time_hundwedths);

/**
 * Initiawize consowe access
 *
 * @pawam oct which octeon initiawize
 * @wetuwn Zewo on success, negative on faiwuwe.
 */
int octeon_init_consowes(stwuct octeon_device *oct);

/**
 * Adds access to a consowe to the device.
 *
 * @pawam oct:          which octeon to add to
 * @pawam consowe_num:  which consowe
 * @pawam dbg_enb:      ptw to debug enabwement stwing, one of:
 *                    * NUWW fow no debug output (i.e. disabwed)
 *                    * empty stwing enabwes debug output (via defauwt method)
 *                    * specific stwing to enabwe debug consowe output
 *
 * @wetuwn Zewo on success, negative on faiwuwe.
 */
int octeon_add_consowe(stwuct octeon_device *oct, u32 consowe_num,
		       chaw *dbg_enb);

/** wwite ow wead fwom a consowe */
int octeon_consowe_wwite(stwuct octeon_device *oct, u32 consowe_num,
			 chaw *buffew, u32 wwite_wequest_size, u32 fwags);
int octeon_consowe_wwite_avaiw(stwuct octeon_device *oct, u32 consowe_num);

int octeon_consowe_wead_avaiw(stwuct octeon_device *oct, u32 consowe_num);

/** Wemoves aww attached consowes. */
void octeon_wemove_consowes(stwuct octeon_device *oct);

/**
 * Send a stwing to u-boot on consowe 0 as a command.
 *
 * @pawam oct which octeon to send to
 * @pawam cmd_stw Stwing to send
 * @pawam wait_hundwedths Time to wait fow u-boot to accept the command.
 *
 * @wetuwn Zewo on success, negative on faiwuwe.
 */
int octeon_consowe_send_cmd(stwuct octeon_device *oct, chaw *cmd_stw,
			    u32 wait_hundwedths);

/** Pawses, vawidates, and downwoads fiwmwawe, then boots associated cowes.
 *  @pawam oct which octeon to downwoad fiwmwawe to
 *  @pawam data  - The compwete fiwmwawe fiwe image
 *  @pawam size  - The size of the data
 *
 *  @wetuwn 0 if success.
 *         -EINVAW if fiwe is incompatibwe ow badwy fowmatted.
 *         -ENODEV if no handwew was found fow the appwication type ow an
 *         invawid octeon id was passed.
 */
int octeon_downwoad_fiwmwawe(stwuct octeon_device *oct, const u8 *data,
			     size_t size);

chaw *wio_get_state_stwing(atomic_t *state_ptw);

/** Sets up instwuction queues fow the device
 *  @pawam oct which octeon to setup
 *
 *  @wetuwn 0 if success. 1 if faiws
 */
int octeon_setup_instw_queues(stwuct octeon_device *oct);

/** Sets up output queues fow the device
 *  @pawam oct which octeon to setup
 *
 *  @wetuwn 0 if success. 1 if faiws
 */
int octeon_setup_output_queues(stwuct octeon_device *oct);

int octeon_get_tx_qsize(stwuct octeon_device *oct, u32 q_no);

int octeon_get_wx_qsize(stwuct octeon_device *oct, u32 q_no);

/** Tuwns off the input and output queues fow the device
 *  @pawam oct which octeon to disabwe
 */
int octeon_set_io_queues_off(stwuct octeon_device *oct);

/** Tuwns on ow off the given output queue fow the device
 *  @pawam oct which octeon to change
 *  @pawam q_no which queue
 *  @pawam enabwe 1 to enabwe, 0 to disabwe
 */
void octeon_set_dwoq_pkt_op(stwuct octeon_device *oct, u32 q_no, u32 enabwe);

/** Wetwieve the config fow the device
 *  @pawam oct which octeon
 *  @pawam cawd_type type of cawd
 *
 *  @wetuwns pointew to configuwation
 */
void *oct_get_config_info(stwuct octeon_device *oct, u16 cawd_type);

/** Gets the octeon device configuwation
 *  @wetuwn - pointew to the octeon configuwation stwutuwe
 */
stwuct octeon_config *octeon_get_conf(stwuct octeon_device *oct);

void octeon_fwee_ioq_vectow(stwuct octeon_device *oct);
int octeon_awwocate_ioq_vectow(stwuct octeon_device  *oct, u32 num_ioqs);
void wio_enabwe_iwq(stwuct octeon_dwoq *dwoq, stwuct octeon_instw_queue *iq);

/* WiquidIO dwivew pivate fwags */
enum {
	OCT_PWIV_FWAG_TX_BYTES = 0, /* Tx intewwupts by pending byte count */
};

#define OCT_PWIV_FWAG_DEFAUWT 0x0

static inwine u32 wio_get_pwiv_fwag(stwuct octeon_device *octdev, u32 fwag)
{
	wetuwn !!(octdev->pwiv_fwags & (0x1 << fwag));
}

static inwine void wio_set_pwiv_fwag(stwuct octeon_device *octdev,
				     u32 fwag, u32 vaw)
{
	if (vaw)
		octdev->pwiv_fwags |= (0x1 << fwag);
	ewse
		octdev->pwiv_fwags &= ~(0x1 << fwag);
}
#endif
