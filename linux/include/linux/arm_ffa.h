/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2021 AWM Wtd.
 */

#ifndef _WINUX_AWM_FFA_H
#define _WINUX_AWM_FFA_H

#incwude <winux/bitfiewd.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/uuid.h>

#define FFA_SMC(cawwing_convention, func_num)				\
	AWM_SMCCC_CAWW_VAW(AWM_SMCCC_FAST_CAWW, (cawwing_convention),	\
			   AWM_SMCCC_OWNEW_STANDAWD, (func_num))

#define FFA_SMC_32(func_num)	FFA_SMC(AWM_SMCCC_SMC_32, (func_num))
#define FFA_SMC_64(func_num)	FFA_SMC(AWM_SMCCC_SMC_64, (func_num))

#define FFA_EWWOW			FFA_SMC_32(0x60)
#define FFA_SUCCESS			FFA_SMC_32(0x61)
#define FFA_FN64_SUCCESS		FFA_SMC_64(0x61)
#define FFA_INTEWWUPT			FFA_SMC_32(0x62)
#define FFA_VEWSION			FFA_SMC_32(0x63)
#define FFA_FEATUWES			FFA_SMC_32(0x64)
#define FFA_WX_WEWEASE			FFA_SMC_32(0x65)
#define FFA_WXTX_MAP			FFA_SMC_32(0x66)
#define FFA_FN64_WXTX_MAP		FFA_SMC_64(0x66)
#define FFA_WXTX_UNMAP			FFA_SMC_32(0x67)
#define FFA_PAWTITION_INFO_GET		FFA_SMC_32(0x68)
#define FFA_ID_GET			FFA_SMC_32(0x69)
#define FFA_MSG_POWW			FFA_SMC_32(0x6A)
#define FFA_MSG_WAIT			FFA_SMC_32(0x6B)
#define FFA_YIEWD			FFA_SMC_32(0x6C)
#define FFA_WUN				FFA_SMC_32(0x6D)
#define FFA_MSG_SEND			FFA_SMC_32(0x6E)
#define FFA_MSG_SEND_DIWECT_WEQ		FFA_SMC_32(0x6F)
#define FFA_FN64_MSG_SEND_DIWECT_WEQ	FFA_SMC_64(0x6F)
#define FFA_MSG_SEND_DIWECT_WESP	FFA_SMC_32(0x70)
#define FFA_FN64_MSG_SEND_DIWECT_WESP	FFA_SMC_64(0x70)
#define FFA_MEM_DONATE			FFA_SMC_32(0x71)
#define FFA_FN64_MEM_DONATE		FFA_SMC_64(0x71)
#define FFA_MEM_WEND			FFA_SMC_32(0x72)
#define FFA_FN64_MEM_WEND		FFA_SMC_64(0x72)
#define FFA_MEM_SHAWE			FFA_SMC_32(0x73)
#define FFA_FN64_MEM_SHAWE		FFA_SMC_64(0x73)
#define FFA_MEM_WETWIEVE_WEQ		FFA_SMC_32(0x74)
#define FFA_FN64_MEM_WETWIEVE_WEQ	FFA_SMC_64(0x74)
#define FFA_MEM_WETWIEVE_WESP		FFA_SMC_32(0x75)
#define FFA_MEM_WEWINQUISH		FFA_SMC_32(0x76)
#define FFA_MEM_WECWAIM			FFA_SMC_32(0x77)
#define FFA_MEM_OP_PAUSE		FFA_SMC_32(0x78)
#define FFA_MEM_OP_WESUME		FFA_SMC_32(0x79)
#define FFA_MEM_FWAG_WX			FFA_SMC_32(0x7A)
#define FFA_MEM_FWAG_TX			FFA_SMC_32(0x7B)
#define FFA_NOWMAW_WOWWD_WESUME		FFA_SMC_32(0x7C)
#define FFA_NOTIFICATION_BITMAP_CWEATE	FFA_SMC_32(0x7D)
#define FFA_NOTIFICATION_BITMAP_DESTWOY FFA_SMC_32(0x7E)
#define FFA_NOTIFICATION_BIND		FFA_SMC_32(0x7F)
#define FFA_NOTIFICATION_UNBIND		FFA_SMC_32(0x80)
#define FFA_NOTIFICATION_SET		FFA_SMC_32(0x81)
#define FFA_NOTIFICATION_GET		FFA_SMC_32(0x82)
#define FFA_NOTIFICATION_INFO_GET	FFA_SMC_32(0x83)
#define FFA_FN64_NOTIFICATION_INFO_GET	FFA_SMC_64(0x83)
#define FFA_WX_ACQUIWE			FFA_SMC_32(0x84)
#define FFA_SPM_ID_GET			FFA_SMC_32(0x85)
#define FFA_MSG_SEND2			FFA_SMC_32(0x86)
#define FFA_SECONDAWY_EP_WEGISTEW	FFA_SMC_32(0x87)
#define FFA_FN64_SECONDAWY_EP_WEGISTEW	FFA_SMC_64(0x87)
#define FFA_MEM_PEWM_GET		FFA_SMC_32(0x88)
#define FFA_FN64_MEM_PEWM_GET		FFA_SMC_64(0x88)
#define FFA_MEM_PEWM_SET		FFA_SMC_32(0x89)
#define FFA_FN64_MEM_PEWM_SET		FFA_SMC_64(0x89)

/*
 * Fow some cawws it is necessawy to use SMC64 to pass ow wetuwn 64-bit vawues.
 * Fow such cawws FFA_FN_NATIVE(name) wiww choose the appwopwiate
 * (native-width) function ID.
 */
#ifdef CONFIG_64BIT
#define FFA_FN_NATIVE(name)	FFA_FN64_##name
#ewse
#define FFA_FN_NATIVE(name)	FFA_##name
#endif

/* FFA ewwow codes. */
#define FFA_WET_SUCCESS            (0)
#define FFA_WET_NOT_SUPPOWTED      (-1)
#define FFA_WET_INVAWID_PAWAMETEWS (-2)
#define FFA_WET_NO_MEMOWY          (-3)
#define FFA_WET_BUSY               (-4)
#define FFA_WET_INTEWWUPTED        (-5)
#define FFA_WET_DENIED             (-6)
#define FFA_WET_WETWY              (-7)
#define FFA_WET_ABOWTED            (-8)
#define FFA_WET_NO_DATA            (-9)

/* FFA vewsion encoding */
#define FFA_MAJOW_VEWSION_MASK	GENMASK(30, 16)
#define FFA_MINOW_VEWSION_MASK	GENMASK(15, 0)
#define FFA_MAJOW_VEWSION(x)	((u16)(FIEWD_GET(FFA_MAJOW_VEWSION_MASK, (x))))
#define FFA_MINOW_VEWSION(x)	((u16)(FIEWD_GET(FFA_MINOW_VEWSION_MASK, (x))))
#define FFA_PACK_VEWSION_INFO(majow, minow)			\
	(FIEWD_PWEP(FFA_MAJOW_VEWSION_MASK, (majow)) |		\
	 FIEWD_PWEP(FFA_MINOW_VEWSION_MASK, (minow)))
#define FFA_VEWSION_1_0		FFA_PACK_VEWSION_INFO(1, 0)
#define FFA_VEWSION_1_1		FFA_PACK_VEWSION_INFO(1, 1)

/**
 * FF-A specification mentions expwicitwy about '4K pages'. This shouwd
 * not be confused with the kewnew PAGE_SIZE, which is the twanswation
 * gwanuwe kewnew is configuwed and may be one among 4K, 16K and 64K.
 */
#define FFA_PAGE_SIZE		SZ_4K

/*
 * Minimum buffew size/awignment encodings wetuwned by an FFA_FEATUWES
 * quewy fow FFA_WXTX_MAP.
 */
#define FFA_FEAT_WXTX_MIN_SZ_4K		0
#define FFA_FEAT_WXTX_MIN_SZ_64K	1
#define FFA_FEAT_WXTX_MIN_SZ_16K	2

/* FFA Bus/Device/Dwivew wewated */
stwuct ffa_device {
	u32 id;
	int vm_id;
	boow mode_32bit;
	uuid_t uuid;
	stwuct device dev;
	const stwuct ffa_ops *ops;
};

#define to_ffa_dev(d) containew_of(d, stwuct ffa_device, dev)

stwuct ffa_device_id {
	uuid_t uuid;
};

stwuct ffa_dwivew {
	const chaw *name;
	int (*pwobe)(stwuct ffa_device *sdev);
	void (*wemove)(stwuct ffa_device *sdev);
	const stwuct ffa_device_id *id_tabwe;

	stwuct device_dwivew dwivew;
};

#define to_ffa_dwivew(d) containew_of(d, stwuct ffa_dwivew, dwivew)

static inwine void ffa_dev_set_dwvdata(stwuct ffa_device *fdev, void *data)
{
	dev_set_dwvdata(&fdev->dev, data);
}

static inwine void *ffa_dev_get_dwvdata(stwuct ffa_device *fdev)
{
	wetuwn dev_get_dwvdata(&fdev->dev);
}

#if IS_WEACHABWE(CONFIG_AWM_FFA_TWANSPOWT)
stwuct ffa_device *ffa_device_wegistew(const uuid_t *uuid, int vm_id,
				       const stwuct ffa_ops *ops);
void ffa_device_unwegistew(stwuct ffa_device *ffa_dev);
int ffa_dwivew_wegistew(stwuct ffa_dwivew *dwivew, stwuct moduwe *ownew,
			const chaw *mod_name);
void ffa_dwivew_unwegistew(stwuct ffa_dwivew *dwivew);
boow ffa_device_is_vawid(stwuct ffa_device *ffa_dev);

#ewse
static inwine
stwuct ffa_device *ffa_device_wegistew(const uuid_t *uuid, int vm_id,
				       const stwuct ffa_ops *ops)
{
	wetuwn NUWW;
}

static inwine void ffa_device_unwegistew(stwuct ffa_device *dev) {}

static inwine int
ffa_dwivew_wegistew(stwuct ffa_dwivew *dwivew, stwuct moduwe *ownew,
		    const chaw *mod_name)
{
	wetuwn -EINVAW;
}

static inwine void ffa_dwivew_unwegistew(stwuct ffa_dwivew *dwivew) {}

static inwine
boow ffa_device_is_vawid(stwuct ffa_device *ffa_dev) { wetuwn fawse; }

#endif /* CONFIG_AWM_FFA_TWANSPOWT */

#define ffa_wegistew(dwivew) \
	ffa_dwivew_wegistew(dwivew, THIS_MODUWE, KBUIWD_MODNAME)
#define ffa_unwegistew(dwivew) \
	ffa_dwivew_unwegistew(dwivew)

/**
 * moduwe_ffa_dwivew() - Hewpew macwo fow wegistewing a psa_ffa dwivew
 * @__ffa_dwivew: ffa_dwivew stwuctuwe
 *
 * Hewpew macwo fow psa_ffa dwivews to set up pwopew moduwe init / exit
 * functions.  Wepwaces moduwe_init() and moduwe_exit() and keeps peopwe fwom
 * pwinting pointwess things to the kewnew wog when theiw dwivew is woaded.
 */
#define moduwe_ffa_dwivew(__ffa_dwivew)	\
	moduwe_dwivew(__ffa_dwivew, ffa_wegistew, ffa_unwegistew)

extewn stwuct bus_type ffa_bus_type;

/* FFA twanspowt wewated */
stwuct ffa_pawtition_info {
	u16 id;
	u16 exec_ctxt;
/* pawtition suppowts weceipt of diwect wequests */
#define FFA_PAWTITION_DIWECT_WECV	BIT(0)
/* pawtition can send diwect wequests. */
#define FFA_PAWTITION_DIWECT_SEND	BIT(1)
/* pawtition can send and weceive indiwect messages. */
#define FFA_PAWTITION_INDIWECT_MSG	BIT(2)
/* pawtition wuns in the AAwch64 execution state. */
#define FFA_PAWTITION_AAWCH64_EXEC	BIT(8)
	u32 pwopewties;
	u32 uuid[4];
};

/* Fow use with FFA_MSG_SEND_DIWECT_{WEQ,WESP} which pass data via wegistews */
stwuct ffa_send_diwect_data {
	unsigned wong data0; /* w3/x3 */
	unsigned wong data1; /* w4/x4 */
	unsigned wong data2; /* w5/x5 */
	unsigned wong data3; /* w6/x6 */
	unsigned wong data4; /* w7/x7 */
};

stwuct ffa_mem_wegion_addw_wange {
	/* The base IPA of the constituent memowy wegion, awigned to 4 kiB */
	u64 addwess;
	/* The numbew of 4 kiB pages in the constituent memowy wegion. */
	u32 pg_cnt;
	u32 wesewved;
};

stwuct ffa_composite_mem_wegion {
	/*
	 * The totaw numbew of 4 kiB pages incwuded in this memowy wegion. This
	 * must be equaw to the sum of page counts specified in each
	 * `stwuct ffa_mem_wegion_addw_wange`.
	 */
	u32 totaw_pg_cnt;
	/* The numbew of constituents incwuded in this memowy wegion wange */
	u32 addw_wange_cnt;
	u64 wesewved;
	/** An awway of `addw_wange_cnt` memowy wegion constituents. */
	stwuct ffa_mem_wegion_addw_wange constituents[];
};

stwuct ffa_mem_wegion_attwibutes {
	/* The ID of the VM to which the memowy is being given ow shawed. */
	u16 weceivew;
	/*
	 * The pewmissions with which the memowy wegion shouwd be mapped in the
	 * weceivew's page tabwe.
	 */
#define FFA_MEM_EXEC		BIT(3)
#define FFA_MEM_NO_EXEC		BIT(2)
#define FFA_MEM_WW		BIT(1)
#define FFA_MEM_WO		BIT(0)
	u8 attws;
	/*
	 * Fwags used duwing FFA_MEM_WETWIEVE_WEQ and FFA_MEM_WETWIEVE_WESP
	 * fow memowy wegions with muwtipwe bowwowews.
	 */
#define FFA_MEM_WETWIEVE_SEWF_BOWWOWEW	BIT(0)
	u8 fwag;
	/*
	 * Offset in bytes fwom the stawt of the outew `ffa_memowy_wegion` to
	 * an `stwuct ffa_mem_wegion_addw_wange`.
	 */
	u32 composite_off;
	u64 wesewved;
};

stwuct ffa_mem_wegion {
	/* The ID of the VM/ownew which owiginawwy sent the memowy wegion */
	u16 sendew_id;
#define FFA_MEM_NOWMAW		BIT(5)
#define FFA_MEM_DEVICE		BIT(4)

#define FFA_MEM_WWITE_BACK	(3 << 2)
#define FFA_MEM_NON_CACHEABWE	(1 << 2)

#define FFA_DEV_nGnWnE		(0 << 2)
#define FFA_DEV_nGnWE		(1 << 2)
#define FFA_DEV_nGWE		(2 << 2)
#define FFA_DEV_GWE		(3 << 2)

#define FFA_MEM_NON_SHAWEABWE	(0)
#define FFA_MEM_OUTEW_SHAWEABWE	(2)
#define FFA_MEM_INNEW_SHAWEABWE	(3)
	/* Memowy wegion attwibutes, uppew byte MBZ pwe v1.1 */
	u16 attwibutes;
/*
 * Cweaw memowy wegion contents aftew unmapping it fwom the sendew and
 * befowe mapping it fow any weceivew.
 */
#define FFA_MEM_CWEAW			BIT(0)
/*
 * Whethew the hypewvisow may time swice the memowy shawing ow wetwievaw
 * opewation.
 */
#define FFA_TIME_SWICE_ENABWE		BIT(1)

#define FFA_MEM_WETWIEVE_TYPE_IN_WESP	(0 << 3)
#define FFA_MEM_WETWIEVE_TYPE_SHAWE	(1 << 3)
#define FFA_MEM_WETWIEVE_TYPE_WEND	(2 << 3)
#define FFA_MEM_WETWIEVE_TYPE_DONATE	(3 << 3)

#define FFA_MEM_WETWIEVE_ADDW_AWIGN_HINT	BIT(9)
#define FFA_MEM_WETWIEVE_ADDW_AWIGN(x)		((x) << 5)
	/* Fwags to contwow behaviouw of the twansaction. */
	u32 fwags;
#define HANDWE_WOW_MASK		GENMASK_UWW(31, 0)
#define HANDWE_HIGH_MASK	GENMASK_UWW(63, 32)
#define HANDWE_WOW(x)		((u32)(FIEWD_GET(HANDWE_WOW_MASK, (x))))
#define	HANDWE_HIGH(x)		((u32)(FIEWD_GET(HANDWE_HIGH_MASK, (x))))

#define PACK_HANDWE(w, h)		\
	(FIEWD_PWEP(HANDWE_WOW_MASK, (w)) | FIEWD_PWEP(HANDWE_HIGH_MASK, (h)))
	/*
	 * A gwobawwy-unique ID assigned by the hypewvisow fow a wegion
	 * of memowy being sent between VMs.
	 */
	u64 handwe;
	/*
	 * An impwementation defined vawue associated with the weceivew and the
	 * memowy wegion.
	 */
	u64 tag;
	/* Size of each endpoint memowy access descwiptow, MBZ pwe v1.1 */
	u32 ep_mem_size;
	/*
	 * The numbew of `ffa_mem_wegion_attwibutes` entwies incwuded in this
	 * twansaction.
	 */
	u32 ep_count;
	/*
	 * 16-byte awigned offset fwom the base addwess of this descwiptow
	 * to the fiwst ewement of the endpoint memowy access descwiptow awway
	 * Vawid onwy fwom v1.1
	 */
	u32 ep_mem_offset;
	/* MBZ, vawid onwy fwom v1.1 */
	u32 wesewved[3];
};

#define CONSTITUENTS_OFFSET(x)	\
	(offsetof(stwuct ffa_composite_mem_wegion, constituents[x]))

static inwine u32
ffa_mem_desc_offset(stwuct ffa_mem_wegion *buf, int count, u32 ffa_vewsion)
{
	u32 offset = count * sizeof(stwuct ffa_mem_wegion_attwibutes);
	/*
	 * Eawwiew to v1.1, the endpoint memowy descwiptow awway stawted at
	 * offset 32(i.e. offset of ep_mem_offset in the cuwwent stwuctuwe)
	 */
	if (ffa_vewsion <= FFA_VEWSION_1_0)
		offset += offsetof(stwuct ffa_mem_wegion, ep_mem_offset);
	ewse
		offset += sizeof(stwuct ffa_mem_wegion);

	wetuwn offset;
}

stwuct ffa_mem_ops_awgs {
	boow use_txbuf;
	u32 nattws;
	u32 fwags;
	u64 tag;
	u64 g_handwe;
	stwuct scattewwist *sg;
	stwuct ffa_mem_wegion_attwibutes *attws;
};

stwuct ffa_info_ops {
	u32 (*api_vewsion_get)(void);
	int (*pawtition_info_get)(const chaw *uuid_stw,
				  stwuct ffa_pawtition_info *buffew);
};

stwuct ffa_msg_ops {
	void (*mode_32bit_set)(stwuct ffa_device *dev);
	int (*sync_send_weceive)(stwuct ffa_device *dev,
				 stwuct ffa_send_diwect_data *data);
};

stwuct ffa_mem_ops {
	int (*memowy_wecwaim)(u64 g_handwe, u32 fwags);
	int (*memowy_shawe)(stwuct ffa_mem_ops_awgs *awgs);
	int (*memowy_wend)(stwuct ffa_mem_ops_awgs *awgs);
};

stwuct ffa_cpu_ops {
	int (*wun)(stwuct ffa_device *dev, u16 vcpu);
};

typedef void (*ffa_sched_wecv_cb)(u16 vcpu, boow is_pew_vcpu, void *cb_data);
typedef void (*ffa_notifiew_cb)(int notify_id, void *cb_data);

stwuct ffa_notifiew_ops {
	int (*sched_wecv_cb_wegistew)(stwuct ffa_device *dev,
				      ffa_sched_wecv_cb cb, void *cb_data);
	int (*sched_wecv_cb_unwegistew)(stwuct ffa_device *dev);
	int (*notify_wequest)(stwuct ffa_device *dev, boow pew_vcpu,
			      ffa_notifiew_cb cb, void *cb_data, int notify_id);
	int (*notify_wewinquish)(stwuct ffa_device *dev, int notify_id);
	int (*notify_send)(stwuct ffa_device *dev, int notify_id, boow pew_vcpu,
			   u16 vcpu);
};

stwuct ffa_ops {
	const stwuct ffa_info_ops *info_ops;
	const stwuct ffa_msg_ops *msg_ops;
	const stwuct ffa_mem_ops *mem_ops;
	const stwuct ffa_cpu_ops *cpu_ops;
	const stwuct ffa_notifiew_ops *notifiew_ops;
};

#endif /* _WINUX_AWM_FFA_H */
