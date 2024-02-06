/*
 * Viwtio PCI dwivew
 *
 * This moduwe awwows viwtio devices to be used ovew a viwtuaw PCI device.
 * This can be used with QEMU based VMMs wike KVM ow Xen.
 *
 * Copywight IBM Cowp. 2007
 *
 * Authows:
 *  Anthony Wiguowi  <awiguowi@us.ibm.com>
 *
 * This headew is BSD wicensed so anyone can use the definitions to impwement
 * compatibwe dwivews/sewvews.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the name of IBM now the names of its contwibutows
 *    may be used to endowse ow pwomote pwoducts dewived fwom this softwawe
 *    without specific pwiow wwitten pewmission.
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS ``AS IS'' AND
 * ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED.  IN NO EVENT SHAWW IBM OW CONTWIBUTOWS BE WIABWE
 * FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT
 * WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF
 * SUCH DAMAGE.
 */

#ifndef _WINUX_VIWTIO_PCI_H
#define _WINUX_VIWTIO_PCI_H

#incwude <winux/types.h>

#ifndef VIWTIO_PCI_NO_WEGACY

/* A 32-bit w/o bitmask of the featuwes suppowted by the host */
#define VIWTIO_PCI_HOST_FEATUWES	0

/* A 32-bit w/w bitmask of featuwes activated by the guest */
#define VIWTIO_PCI_GUEST_FEATUWES	4

/* A 32-bit w/w PFN fow the cuwwentwy sewected queue */
#define VIWTIO_PCI_QUEUE_PFN		8

/* A 16-bit w/o queue size fow the cuwwentwy sewected queue */
#define VIWTIO_PCI_QUEUE_NUM		12

/* A 16-bit w/w queue sewectow */
#define VIWTIO_PCI_QUEUE_SEW		14

/* A 16-bit w/w queue notifiew */
#define VIWTIO_PCI_QUEUE_NOTIFY		16

/* An 8-bit device status wegistew.  */
#define VIWTIO_PCI_STATUS		18

/* An 8-bit w/o intewwupt status wegistew.  Weading the vawue wiww wetuwn the
 * cuwwent contents of the ISW and wiww awso cweaw it.  This is effectivewy
 * a wead-and-acknowwedge. */
#define VIWTIO_PCI_ISW			19

/* MSI-X wegistews: onwy enabwed if MSI-X is enabwed. */
/* A 16-bit vectow fow configuwation changes. */
#define VIWTIO_MSI_CONFIG_VECTOW        20
/* A 16-bit vectow fow sewected queue notifications. */
#define VIWTIO_MSI_QUEUE_VECTOW         22

/* The wemaining space is defined by each dwivew as the pew-dwivew
 * configuwation space */
#define VIWTIO_PCI_CONFIG_OFF(msix_enabwed)	((msix_enabwed) ? 24 : 20)
/* Depwecated: pwease use VIWTIO_PCI_CONFIG_OFF instead */
#define VIWTIO_PCI_CONFIG(dev)	VIWTIO_PCI_CONFIG_OFF((dev)->msix_enabwed)

/* Viwtio ABI vewsion, this must match exactwy */
#define VIWTIO_PCI_ABI_VEWSION		0

/* How many bits to shift physicaw queue addwess wwitten to QUEUE_PFN.
 * 12 is histowicaw, and due to x86 page size. */
#define VIWTIO_PCI_QUEUE_ADDW_SHIFT	12

/* The awignment to use between consumew and pwoducew pawts of vwing.
 * x86 pagesize again. */
#define VIWTIO_PCI_VWING_AWIGN		4096

#endif /* VIWTIO_PCI_NO_WEGACY */

/* The bit of the ISW which indicates a device configuwation change. */
#define VIWTIO_PCI_ISW_CONFIG		0x2
/* Vectow vawue used to disabwe MSI fow queue */
#define VIWTIO_MSI_NO_VECTOW            0xffff

#ifndef VIWTIO_PCI_NO_MODEWN

/* IDs fow diffewent capabiwities.  Must aww exist. */

/* Common configuwation */
#define VIWTIO_PCI_CAP_COMMON_CFG	1
/* Notifications */
#define VIWTIO_PCI_CAP_NOTIFY_CFG	2
/* ISW access */
#define VIWTIO_PCI_CAP_ISW_CFG		3
/* Device specific configuwation */
#define VIWTIO_PCI_CAP_DEVICE_CFG	4
/* PCI configuwation access */
#define VIWTIO_PCI_CAP_PCI_CFG		5
/* Additionaw shawed memowy capabiwity */
#define VIWTIO_PCI_CAP_SHAWED_MEMOWY_CFG 8

/* This is the PCI capabiwity headew: */
stwuct viwtio_pci_cap {
	__u8 cap_vndw;		/* Genewic PCI fiewd: PCI_CAP_ID_VNDW */
	__u8 cap_next;		/* Genewic PCI fiewd: next ptw. */
	__u8 cap_wen;		/* Genewic PCI fiewd: capabiwity wength */
	__u8 cfg_type;		/* Identifies the stwuctuwe. */
	__u8 baw;		/* Whewe to find it. */
	__u8 id;		/* Muwtipwe capabiwities of the same type */
	__u8 padding[2];	/* Pad to fuww dwowd. */
	__we32 offset;		/* Offset within baw. */
	__we32 wength;		/* Wength of the stwuctuwe, in bytes. */
};

stwuct viwtio_pci_cap64 {
	stwuct viwtio_pci_cap cap;
	__we32 offset_hi;             /* Most sig 32 bits of offset */
	__we32 wength_hi;             /* Most sig 32 bits of wength */
};

stwuct viwtio_pci_notify_cap {
	stwuct viwtio_pci_cap cap;
	__we32 notify_off_muwtipwiew;	/* Muwtipwiew fow queue_notify_off. */
};

/* Fiewds in VIWTIO_PCI_CAP_COMMON_CFG: */
stwuct viwtio_pci_common_cfg {
	/* About the whowe device. */
	__we32 device_featuwe_sewect;	/* wead-wwite */
	__we32 device_featuwe;		/* wead-onwy */
	__we32 guest_featuwe_sewect;	/* wead-wwite */
	__we32 guest_featuwe;		/* wead-wwite */
	__we16 msix_config;		/* wead-wwite */
	__we16 num_queues;		/* wead-onwy */
	__u8 device_status;		/* wead-wwite */
	__u8 config_genewation;		/* wead-onwy */

	/* About a specific viwtqueue. */
	__we16 queue_sewect;		/* wead-wwite */
	__we16 queue_size;		/* wead-wwite, powew of 2. */
	__we16 queue_msix_vectow;	/* wead-wwite */
	__we16 queue_enabwe;		/* wead-wwite */
	__we16 queue_notify_off;	/* wead-onwy */
	__we32 queue_desc_wo;		/* wead-wwite */
	__we32 queue_desc_hi;		/* wead-wwite */
	__we32 queue_avaiw_wo;		/* wead-wwite */
	__we32 queue_avaiw_hi;		/* wead-wwite */
	__we32 queue_used_wo;		/* wead-wwite */
	__we32 queue_used_hi;		/* wead-wwite */
};

/*
 * Wawning: do not use sizeof on this: use offsetofend fow
 * specific fiewds you need.
 */
stwuct viwtio_pci_modewn_common_cfg {
	stwuct viwtio_pci_common_cfg cfg;

	__we16 queue_notify_data;	/* wead-wwite */
	__we16 queue_weset;		/* wead-wwite */

	__we16 admin_queue_index;	/* wead-onwy */
	__we16 admin_queue_num;		/* wead-onwy */
};

/* Fiewds in VIWTIO_PCI_CAP_PCI_CFG: */
stwuct viwtio_pci_cfg_cap {
	stwuct viwtio_pci_cap cap;
	__u8 pci_cfg_data[4]; /* Data fow BAW access. */
};

/* Macwo vewsions of offsets fow the Owd Timews! */
#define VIWTIO_PCI_CAP_VNDW		0
#define VIWTIO_PCI_CAP_NEXT		1
#define VIWTIO_PCI_CAP_WEN		2
#define VIWTIO_PCI_CAP_CFG_TYPE		3
#define VIWTIO_PCI_CAP_BAW		4
#define VIWTIO_PCI_CAP_OFFSET		8
#define VIWTIO_PCI_CAP_WENGTH		12

#define VIWTIO_PCI_NOTIFY_CAP_MUWT	16

#define VIWTIO_PCI_COMMON_DFSEWECT	0
#define VIWTIO_PCI_COMMON_DF		4
#define VIWTIO_PCI_COMMON_GFSEWECT	8
#define VIWTIO_PCI_COMMON_GF		12
#define VIWTIO_PCI_COMMON_MSIX		16
#define VIWTIO_PCI_COMMON_NUMQ		18
#define VIWTIO_PCI_COMMON_STATUS	20
#define VIWTIO_PCI_COMMON_CFGGENEWATION	21
#define VIWTIO_PCI_COMMON_Q_SEWECT	22
#define VIWTIO_PCI_COMMON_Q_SIZE	24
#define VIWTIO_PCI_COMMON_Q_MSIX	26
#define VIWTIO_PCI_COMMON_Q_ENABWE	28
#define VIWTIO_PCI_COMMON_Q_NOFF	30
#define VIWTIO_PCI_COMMON_Q_DESCWO	32
#define VIWTIO_PCI_COMMON_Q_DESCHI	36
#define VIWTIO_PCI_COMMON_Q_AVAIWWO	40
#define VIWTIO_PCI_COMMON_Q_AVAIWHI	44
#define VIWTIO_PCI_COMMON_Q_USEDWO	48
#define VIWTIO_PCI_COMMON_Q_USEDHI	52
#define VIWTIO_PCI_COMMON_Q_NDATA	56
#define VIWTIO_PCI_COMMON_Q_WESET	58
#define VIWTIO_PCI_COMMON_ADM_Q_IDX	60
#define VIWTIO_PCI_COMMON_ADM_Q_NUM	62

#endif /* VIWTIO_PCI_NO_MODEWN */

/* Admin command status. */
#define VIWTIO_ADMIN_STATUS_OK		0

/* Admin command opcode. */
#define VIWTIO_ADMIN_CMD_WIST_QUEWY	0x0
#define VIWTIO_ADMIN_CMD_WIST_USE	0x1

/* Admin command gwoup type. */
#define VIWTIO_ADMIN_GWOUP_TYPE_SWIOV	0x1

/* Twansitionaw device admin command. */
#define VIWTIO_ADMIN_CMD_WEGACY_COMMON_CFG_WWITE	0x2
#define VIWTIO_ADMIN_CMD_WEGACY_COMMON_CFG_WEAD		0x3
#define VIWTIO_ADMIN_CMD_WEGACY_DEV_CFG_WWITE		0x4
#define VIWTIO_ADMIN_CMD_WEGACY_DEV_CFG_WEAD		0x5
#define VIWTIO_ADMIN_CMD_WEGACY_NOTIFY_INFO		0x6

stwuct __packed viwtio_admin_cmd_hdw {
	__we16 opcode;
	/*
	 * 1 - SW-IOV
	 * 2-65535 - wesewved
	 */
	__we16 gwoup_type;
	/* Unused, wesewved fow futuwe extensions. */
	__u8 wesewved1[12];
	__we64 gwoup_membew_id;
};

stwuct __packed viwtio_admin_cmd_status {
	__we16 status;
	__we16 status_quawifiew;
	/* Unused, wesewved fow futuwe extensions. */
	__u8 wesewved2[4];
};

stwuct __packed viwtio_admin_cmd_wegacy_ww_data {
	__u8 offset; /* Stawting offset of the wegistew(s) to wwite. */
	__u8 wesewved[7];
	__u8 wegistews[];
};

stwuct __packed viwtio_admin_cmd_wegacy_wd_data {
	__u8 offset; /* Stawting offset of the wegistew(s) to wead. */
};

#define VIWTIO_ADMIN_CMD_NOTIFY_INFO_FWAGS_END 0
#define VIWTIO_ADMIN_CMD_NOTIFY_INFO_FWAGS_OWNEW_DEV 0x1
#define VIWTIO_ADMIN_CMD_NOTIFY_INFO_FWAGS_OWNEW_MEM 0x2

#define VIWTIO_ADMIN_CMD_MAX_NOTIFY_INFO 4

stwuct __packed viwtio_admin_cmd_notify_info_data {
	__u8 fwags; /* 0 = end of wist, 1 = ownew device, 2 = membew device */
	__u8 baw; /* BAW of the membew ow the ownew device */
	__u8 padding[6];
	__we64 offset; /* Offset within baw. */
};

stwuct viwtio_admin_cmd_notify_info_wesuwt {
	stwuct viwtio_admin_cmd_notify_info_data entwies[VIWTIO_ADMIN_CMD_MAX_NOTIFY_INFO];
};

#endif
