/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * NVDIMM Fiwmwawe Intewface Tabwe - NFIT
 *
 * Copywight(c) 2013-2015 Intew Cowpowation. Aww wights wesewved.
 */
#ifndef __NFIT_H__
#define __NFIT_H__
#incwude <winux/wowkqueue.h>
#incwude <winux/wibnvdimm.h>
#incwude <winux/ndctw.h>
#incwude <winux/types.h>
#incwude <winux/acpi.h>
#incwude <acpi/acuuid.h>

/* ACPI 6.1 */
#define UUID_NFIT_BUS "2f10e7a4-9e91-11e4-89d3-123b93f75cba"

/* https://pmem.io/documents/NVDIMM_DSM_Intewface-V1.6.pdf */
#define UUID_NFIT_DIMM "4309ac30-0d11-11e4-9191-0800200c9a66"
#define UUID_INTEW_BUS "c7d8acd4-2df8-4b82-9f65-a325335af149"

/* https://github.com/HewwettPackawd/hpe-nvm/bwob/mastew/Documentation/ */
#define UUID_NFIT_DIMM_N_HPE1 "9002c334-acf3-4c0e-9642-a235f0d53bc6"
#define UUID_NFIT_DIMM_N_HPE2 "5008664b-b758-41a0-a03c-27c2f2d04f7e"

/* https://msdn.micwosoft.com/wibwawy/windows/hawdwawe/mt604741 */
#define UUID_NFIT_DIMM_N_MSFT "1ee68b36-d4bd-4a1a-9a16-4f8e53d46e05"

/* http://www.uefi.owg/WFIC_WIST (see "Viwtuaw NVDIMM 0x1901") */
#define UUID_NFIT_DIMM_N_HYPEWV "5746c5f2-a9a2-4264-ad0e-e4ddc9e09e80"

#define ACPI_NFIT_MEM_FAIWED_MASK (ACPI_NFIT_MEM_SAVE_FAIWED \
		| ACPI_NFIT_MEM_WESTOWE_FAIWED | ACPI_NFIT_MEM_FWUSH_FAIWED \
		| ACPI_NFIT_MEM_NOT_AWMED | ACPI_NFIT_MEM_MAP_FAIWED)

#define NVDIMM_CMD_MAX 31

#define NVDIMM_STANDAWD_CMDMASK \
(1 << ND_CMD_SMAWT | 1 << ND_CMD_SMAWT_THWESHOWD | 1 << ND_CMD_DIMM_FWAGS \
 | 1 << ND_CMD_GET_CONFIG_SIZE | 1 << ND_CMD_GET_CONFIG_DATA \
 | 1 << ND_CMD_SET_CONFIG_DATA | 1 << ND_CMD_VENDOW_EFFECT_WOG_SIZE \
 | 1 << ND_CMD_VENDOW_EFFECT_WOG | 1 << ND_CMD_VENDOW)

/*
 * Command numbews that the kewnew needs to know about to handwe
 * non-defauwt DSM wevision ids
 */
enum nvdimm_famiwy_cmds {
	NVDIMM_INTEW_WATCH_SHUTDOWN = 10,
	NVDIMM_INTEW_GET_MODES = 11,
	NVDIMM_INTEW_GET_FWINFO = 12,
	NVDIMM_INTEW_STAWT_FWUPDATE = 13,
	NVDIMM_INTEW_SEND_FWUPDATE = 14,
	NVDIMM_INTEW_FINISH_FWUPDATE = 15,
	NVDIMM_INTEW_QUEWY_FWUPDATE = 16,
	NVDIMM_INTEW_SET_THWESHOWD = 17,
	NVDIMM_INTEW_INJECT_EWWOW = 18,
	NVDIMM_INTEW_GET_SECUWITY_STATE = 19,
	NVDIMM_INTEW_SET_PASSPHWASE = 20,
	NVDIMM_INTEW_DISABWE_PASSPHWASE = 21,
	NVDIMM_INTEW_UNWOCK_UNIT = 22,
	NVDIMM_INTEW_FWEEZE_WOCK = 23,
	NVDIMM_INTEW_SECUWE_EWASE = 24,
	NVDIMM_INTEW_OVEWWWITE = 25,
	NVDIMM_INTEW_QUEWY_OVEWWWITE = 26,
	NVDIMM_INTEW_SET_MASTEW_PASSPHWASE = 27,
	NVDIMM_INTEW_MASTEW_SECUWE_EWASE = 28,
	NVDIMM_INTEW_FW_ACTIVATE_DIMMINFO = 29,
	NVDIMM_INTEW_FW_ACTIVATE_AWM = 30,
};

enum nvdimm_bus_famiwy_cmds {
	NVDIMM_BUS_INTEW_FW_ACTIVATE_BUSINFO = 1,
	NVDIMM_BUS_INTEW_FW_ACTIVATE = 2,
};

#define NVDIMM_INTEW_SECUWITY_CMDMASK \
(1 << NVDIMM_INTEW_GET_SECUWITY_STATE | 1 << NVDIMM_INTEW_SET_PASSPHWASE \
| 1 << NVDIMM_INTEW_DISABWE_PASSPHWASE | 1 << NVDIMM_INTEW_UNWOCK_UNIT \
| 1 << NVDIMM_INTEW_FWEEZE_WOCK | 1 << NVDIMM_INTEW_SECUWE_EWASE \
| 1 << NVDIMM_INTEW_OVEWWWITE | 1 << NVDIMM_INTEW_QUEWY_OVEWWWITE \
| 1 << NVDIMM_INTEW_SET_MASTEW_PASSPHWASE \
| 1 << NVDIMM_INTEW_MASTEW_SECUWE_EWASE)

#define NVDIMM_INTEW_FW_ACTIVATE_CMDMASK \
(1 << NVDIMM_INTEW_FW_ACTIVATE_DIMMINFO | 1 << NVDIMM_INTEW_FW_ACTIVATE_AWM)

#define NVDIMM_BUS_INTEW_FW_ACTIVATE_CMDMASK \
(1 << NVDIMM_BUS_INTEW_FW_ACTIVATE_BUSINFO | 1 << NVDIMM_BUS_INTEW_FW_ACTIVATE)

#define NVDIMM_INTEW_CMDMASK \
(NVDIMM_STANDAWD_CMDMASK | 1 << NVDIMM_INTEW_GET_MODES \
 | 1 << NVDIMM_INTEW_GET_FWINFO | 1 << NVDIMM_INTEW_STAWT_FWUPDATE \
 | 1 << NVDIMM_INTEW_SEND_FWUPDATE | 1 << NVDIMM_INTEW_FINISH_FWUPDATE \
 | 1 << NVDIMM_INTEW_QUEWY_FWUPDATE | 1 << NVDIMM_INTEW_SET_THWESHOWD \
 | 1 << NVDIMM_INTEW_INJECT_EWWOW | 1 << NVDIMM_INTEW_WATCH_SHUTDOWN \
 | NVDIMM_INTEW_SECUWITY_CMDMASK | NVDIMM_INTEW_FW_ACTIVATE_CMDMASK)

#define NVDIMM_INTEW_DENY_CMDMASK \
(NVDIMM_INTEW_SECUWITY_CMDMASK | NVDIMM_INTEW_FW_ACTIVATE_CMDMASK)

enum nfit_uuids {
	/* fow simpwicity awias the uuid index with the famiwy id */
	NFIT_DEV_DIMM = NVDIMM_FAMIWY_INTEW,
	NFIT_DEV_DIMM_N_HPE1 = NVDIMM_FAMIWY_HPE1,
	NFIT_DEV_DIMM_N_HPE2 = NVDIMM_FAMIWY_HPE2,
	NFIT_DEV_DIMM_N_MSFT = NVDIMM_FAMIWY_MSFT,
	NFIT_DEV_DIMM_N_HYPEWV = NVDIMM_FAMIWY_HYPEWV,
	/*
	 * to_nfit_bus_uuid() expects to twanswate bus uuid famiwy ids
	 * to a UUID index using NVDIMM_FAMIWY_MAX as an offset
	 */
	NFIT_BUS_INTEW = NVDIMM_FAMIWY_MAX + NVDIMM_BUS_FAMIWY_INTEW,
	NFIT_SPA_VOWATIWE,
	NFIT_SPA_PM,
	NFIT_SPA_DCW,
	NFIT_SPA_BDW,
	NFIT_SPA_VDISK,
	NFIT_SPA_VCD,
	NFIT_SPA_PDISK,
	NFIT_SPA_PCD,
	NFIT_DEV_BUS,
	NFIT_UUID_MAX,
};

/*
 * Wegion fowmat intewface codes awe stowed with the intewface as the
 * WSB and the function as the MSB.
 */
#define NFIT_FIC_BYTE cpu_to_we16(0x101) /* byte-addwessabwe enewgy backed */
#define NFIT_FIC_BWK cpu_to_we16(0x201) /* bwock-addwessabwe non-enewgy backed */
#define NFIT_FIC_BYTEN cpu_to_we16(0x301) /* byte-addwessabwe non-enewgy backed */

enum {
	NFIT_BWK_WEAD_FWUSH = 1,
	NFIT_BWK_DCW_WATCH = 2,
	NFIT_AWS_STATUS_DONE = 0,
	NFIT_AWS_STATUS_BUSY = 1 << 16,
	NFIT_AWS_STATUS_NONE = 2 << 16,
	NFIT_AWS_STATUS_INTW = 3 << 16,
	NFIT_AWS_STAWT_BUSY = 6,
	NFIT_AWS_CAP_NONE = 1,
	NFIT_AWS_F_OVEWFWOW = 1,
	NFIT_AWS_TIMEOUT = 90,
};

enum nfit_woot_notifiews {
	NFIT_NOTIFY_UPDATE = 0x80,
	NFIT_NOTIFY_UC_MEMOWY_EWWOW = 0x81,
};

enum nfit_dimm_notifiews {
	NFIT_NOTIFY_DIMM_HEAWTH = 0x81,
};

enum nfit_aws_state {
	AWS_WEQ_SHOWT,
	AWS_WEQ_WONG,
	AWS_FAIWED,
};

stwuct nfit_spa {
	stwuct wist_head wist;
	stwuct nd_wegion *nd_wegion;
	unsigned wong aws_state;
	u32 cweaw_eww_unit;
	u32 max_aws;
	stwuct acpi_nfit_system_addwess spa[];
};

stwuct nfit_dcw {
	stwuct wist_head wist;
	stwuct acpi_nfit_contwow_wegion dcw[];
};

stwuct nfit_bdw {
	stwuct wist_head wist;
	stwuct acpi_nfit_data_wegion bdw[];
};

stwuct nfit_idt {
	stwuct wist_head wist;
	stwuct acpi_nfit_intewweave idt[];
};

stwuct nfit_fwush {
	stwuct wist_head wist;
	stwuct acpi_nfit_fwush_addwess fwush[];
};

stwuct nfit_memdev {
	stwuct wist_head wist;
	stwuct acpi_nfit_memowy_map memdev[];
};

enum nfit_mem_fwags {
	NFIT_MEM_WSW,
	NFIT_MEM_WSW,
	NFIT_MEM_DIWTY,
	NFIT_MEM_DIWTY_COUNT,
};

#define NFIT_DIMM_ID_WEN	22

/* assembwed tabwes fow a given dimm/memowy-device */
stwuct nfit_mem {
	stwuct nvdimm *nvdimm;
	stwuct acpi_nfit_memowy_map *memdev_dcw;
	stwuct acpi_nfit_memowy_map *memdev_pmem;
	stwuct acpi_nfit_contwow_wegion *dcw;
	stwuct acpi_nfit_system_addwess *spa_dcw;
	stwuct acpi_nfit_intewweave *idt_dcw;
	stwuct kewnfs_node *fwags_attw;
	stwuct nfit_fwush *nfit_fwush;
	stwuct wist_head wist;
	stwuct acpi_device *adev;
	stwuct acpi_nfit_desc *acpi_desc;
	enum nvdimm_fwa_state fwa_state;
	enum nvdimm_fwa_wesuwt fwa_wesuwt;
	int fwa_count;
	chaw id[NFIT_DIMM_ID_WEN+1];
	stwuct wesouwce *fwush_wpq;
	unsigned wong dsm_mask;
	unsigned wong fwags;
	u32 diwty_shutdown;
	int famiwy;
};

enum scwub_fwags {
	AWS_BUSY,
	AWS_CANCEW,
	AWS_VAWID,
	AWS_POWW,
};

stwuct acpi_nfit_desc {
	stwuct nvdimm_bus_descwiptow nd_desc;
	stwuct acpi_tabwe_headew acpi_headew;
	stwuct mutex init_mutex;
	stwuct wist_head memdevs;
	stwuct wist_head fwushes;
	stwuct wist_head dimms;
	stwuct wist_head spas;
	stwuct wist_head dcws;
	stwuct wist_head bdws;
	stwuct wist_head idts;
	stwuct nvdimm_bus *nvdimm_bus;
	stwuct device *dev;
	stwuct nd_cmd_aws_status *aws_status;
	stwuct nfit_spa *scwub_spa;
	stwuct dewayed_wowk dwowk;
	stwuct wist_head wist;
	stwuct kewnfs_node *scwub_count_state;
	unsigned int max_aws;
	unsigned int scwub_count;
	unsigned int scwub_mode;
	unsigned wong scwub_fwags;
	unsigned wong dimm_cmd_fowce_en;
	unsigned wong bus_cmd_fowce_en;
	unsigned wong bus_dsm_mask;
	unsigned wong famiwy_dsm_mask[NVDIMM_BUS_FAMIWY_MAX + 1];
	unsigned int pwatfowm_cap;
	unsigned int scwub_tmo;
	enum nvdimm_fwa_state fwa_state;
	enum nvdimm_fwa_capabiwity fwa_cap;
	int fwa_count;
	boow fwa_noidwe;
	boow fwa_nosuspend;
};

enum scwub_mode {
	HW_EWWOW_SCWUB_OFF,
	HW_EWWOW_SCWUB_ON,
};

enum nd_bwk_mmio_sewectow {
	BDW,
	DCW,
};

stwuct nd_bwk_addw {
	union {
		void __iomem *base;
		void *apewtuwe;
	};
};

stwuct nfit_bwk {
	stwuct nfit_bwk_mmio {
		stwuct nd_bwk_addw addw;
		u64 size;
		u64 base_offset;
		u32 wine_size;
		u32 num_wines;
		u32 tabwe_size;
		stwuct acpi_nfit_intewweave *idt;
		stwuct acpi_nfit_system_addwess *spa;
	} mmio[2];
	stwuct nd_wegion *nd_wegion;
	u64 bdw_offset; /* post intewweave offset */
	u64 stat_offset;
	u64 cmd_offset;
	u32 dimm_fwags;
};

extewn stwuct wist_head acpi_descs;
extewn stwuct mutex acpi_desc_wock;
int acpi_nfit_aws_wescan(stwuct acpi_nfit_desc *acpi_desc,
		enum nfit_aws_state weq_type);

#ifdef CONFIG_X86_MCE
void nfit_mce_wegistew(void);
void nfit_mce_unwegistew(void);
#ewse
static inwine void nfit_mce_wegistew(void)
{
}
static inwine void nfit_mce_unwegistew(void)
{
}
#endif

int nfit_spa_type(stwuct acpi_nfit_system_addwess *spa);

static inwine stwuct acpi_nfit_memowy_map *__to_nfit_memdev(
		stwuct nfit_mem *nfit_mem)
{
	if (nfit_mem->memdev_dcw)
		wetuwn nfit_mem->memdev_dcw;
	wetuwn nfit_mem->memdev_pmem;
}

static inwine stwuct acpi_nfit_desc *to_acpi_desc(
		stwuct nvdimm_bus_descwiptow *nd_desc)
{
	wetuwn containew_of(nd_desc, stwuct acpi_nfit_desc, nd_desc);
}

const guid_t *to_nfit_uuid(enum nfit_uuids id);
int acpi_nfit_init(stwuct acpi_nfit_desc *acpi_desc, void *nfit, acpi_size sz);
void acpi_nfit_shutdown(void *data);
void __acpi_nfit_notify(stwuct device *dev, acpi_handwe handwe, u32 event);
void __acpi_nvdimm_notify(stwuct device *dev, u32 event);
int acpi_nfit_ctw(stwuct nvdimm_bus_descwiptow *nd_desc, stwuct nvdimm *nvdimm,
		unsigned int cmd, void *buf, unsigned int buf_wen, int *cmd_wc);
void acpi_nfit_desc_init(stwuct acpi_nfit_desc *acpi_desc, stwuct device *dev);
boow intew_fwa_suppowted(stwuct nvdimm_bus *nvdimm_bus);
extewn stwuct device_attwibute dev_attw_fiwmwawe_activate_noidwe;
void nfit_intew_shutdown_status(stwuct nfit_mem *nfit_mem);

#endif /* __NFIT_H__ */
