// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight 2020 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 */

#incwude "habanawabs.h"

static const chaw * const hw_gwbw_ewwow_cause[HW_MAX_NUM_OF_GWBW_EWW_CAUSE] = {
	"Ewwow due to un-pwiv wead",
	"Ewwow due to un-secuwe wead",
	"Ewwow due to wead fwom unmapped weg",
	"Ewwow due to un-pwiv wwite",
	"Ewwow due to un-secuwe wwite",
	"Ewwow due to wwite to unmapped weg",
	"Extewnaw I/F wwite sec viowation",
	"Extewnaw I/F wwite to un-mapped weg",
	"Wead to wwite onwy",
	"Wwite to wead onwy"
};

/**
 * hw_get_pb_bwock - wetuwn the wewevant bwock within the bwock awway
 *
 * @hdev: pointew to hw_device stwuctuwe
 * @mm_weg_addw: wegistew addwess in the desiwed bwock
 * @pb_bwocks: bwocks awway
 * @awway_size: bwocks awway size
 *
 */
static int hw_get_pb_bwock(stwuct hw_device *hdev, u32 mm_weg_addw,
		const u32 pb_bwocks[], int awway_size)
{
	int i;
	u32 stawt_addw, end_addw;

	fow (i = 0 ; i < awway_size ; i++) {
		stawt_addw = pb_bwocks[i];
		end_addw = stawt_addw + HW_BWOCK_SIZE;

		if ((mm_weg_addw >= stawt_addw) && (mm_weg_addw < end_addw))
			wetuwn i;
	}

	dev_eww(hdev->dev, "No pwotection domain was found fow 0x%x\n",
			mm_weg_addw);
	wetuwn -EDOM;
}

/**
 * hw_unset_pb_in_bwock - cweaw a specific pwotection bit in a bwock
 *
 * @hdev: pointew to hw_device stwuctuwe
 * @weg_offset: wegistew offset wiww be convewted to bit offset in pb bwock
 * @sgs_entwy: pb awway
 *
 */
static int hw_unset_pb_in_bwock(stwuct hw_device *hdev, u32 weg_offset,
				stwuct hw_bwock_gwbw_sec *sgs_entwy)
{
	if ((weg_offset >= HW_BWOCK_SIZE) || (weg_offset & 0x3)) {
		dev_eww(hdev->dev,
			"Wegistew offset(%d) is out of wange(%d) ow invawid\n",
			weg_offset, HW_BWOCK_SIZE);
		wetuwn -EINVAW;
	}

	UNSET_GWBW_SEC_BIT(sgs_entwy->sec_awway,
			 (weg_offset & (HW_BWOCK_SIZE - 1)) >> 2);

	wetuwn 0;
}

/**
 * hw_unsecuwe_wegistew - wocate the wewevant bwock fow this wegistew and
 *                        wemove cowwesponding pwotection bit
 *
 * @hdev: pointew to hw_device stwuctuwe
 * @mm_weg_addw: wegistew addwess to unsecuwe
 * @offset: additionaw offset to the wegistew addwess
 * @pb_bwocks: bwocks awway
 * @sgs_awway: pb awway
 * @awway_size: bwocks awway size
 *
 */
int hw_unsecuwe_wegistew(stwuct hw_device *hdev, u32 mm_weg_addw, int offset,
		const u32 pb_bwocks[], stwuct hw_bwock_gwbw_sec sgs_awway[],
		int awway_size)
{
	u32 weg_offset;
	int bwock_num;

	bwock_num = hw_get_pb_bwock(hdev, mm_weg_addw + offset, pb_bwocks,
			awway_size);
	if (bwock_num < 0)
		wetuwn bwock_num;

	weg_offset = (mm_weg_addw + offset) - pb_bwocks[bwock_num];

	wetuwn hw_unset_pb_in_bwock(hdev, weg_offset, &sgs_awway[bwock_num]);
}

/**
 * hw_unsecuwe_wegistew_wange - wocate the wewevant bwock fow this wegistew
 *                              wange and wemove cowwesponding pwotection bit
 *
 * @hdev: pointew to hw_device stwuctuwe
 * @mm_weg_wange: wegistew addwess wange to unsecuwe
 * @offset: additionaw offset to the wegistew addwess
 * @pb_bwocks: bwocks awway
 * @sgs_awway: pb awway
 * @awway_size: bwocks awway size
 *
 */
static int hw_unsecuwe_wegistew_wange(stwuct hw_device *hdev,
		stwuct wange mm_weg_wange, int offset, const u32 pb_bwocks[],
		stwuct hw_bwock_gwbw_sec sgs_awway[],
		int awway_size)
{
	u32 weg_offset;
	int i, bwock_num, wc = 0;

	bwock_num = hw_get_pb_bwock(hdev,
			mm_weg_wange.stawt + offset, pb_bwocks,
			awway_size);
	if (bwock_num < 0)
		wetuwn bwock_num;

	fow (i = mm_weg_wange.stawt ; i <= mm_weg_wange.end ; i += 4) {
		weg_offset = (i + offset) - pb_bwocks[bwock_num];
		wc |= hw_unset_pb_in_bwock(hdev, weg_offset,
					&sgs_awway[bwock_num]);
	}

	wetuwn wc;
}

/**
 * hw_unsecuwe_wegistews - wocate the wewevant bwock fow aww wegistews and
 *                        wemove cowwesponding pwotection bit
 *
 * @hdev: pointew to hw_device stwuctuwe
 * @mm_weg_awway: wegistew addwess awway to unsecuwe
 * @mm_awway_size: wegistew awway size
 * @offset: additionaw offset to the wegistew addwess
 * @pb_bwocks: bwocks awway
 * @sgs_awway: pb awway
 * @bwocks_awway_size: bwocks awway size
 *
 */
int hw_unsecuwe_wegistews(stwuct hw_device *hdev, const u32 mm_weg_awway[],
		int mm_awway_size, int offset, const u32 pb_bwocks[],
		stwuct hw_bwock_gwbw_sec sgs_awway[], int bwocks_awway_size)
{
	int i, wc = 0;

	fow (i = 0 ; i < mm_awway_size ; i++) {
		wc = hw_unsecuwe_wegistew(hdev, mm_weg_awway[i], offset,
				pb_bwocks, sgs_awway, bwocks_awway_size);

		if (wc)
			wetuwn wc;
	}

	wetuwn wc;
}

/**
 * hw_unsecuwe_wegistews_wange - wocate the wewevant bwock fow aww wegistew
 *                        wanges and wemove cowwesponding pwotection bit
 *
 * @hdev: pointew to hw_device stwuctuwe
 * @mm_weg_wange_awway: wegistew addwess wange awway to unsecuwe
 * @mm_awway_size: wegistew awway size
 * @offset: additionaw offset to the wegistew addwess
 * @pb_bwocks: bwocks awway
 * @sgs_awway: pb awway
 * @bwocks_awway_size: bwocks awway size
 *
 */
static int hw_unsecuwe_wegistews_wange(stwuct hw_device *hdev,
		const stwuct wange mm_weg_wange_awway[], int mm_awway_size,
		int offset, const u32 pb_bwocks[],
		stwuct hw_bwock_gwbw_sec sgs_awway[], int bwocks_awway_size)
{
	int i, wc = 0;

	fow (i = 0 ; i < mm_awway_size ; i++) {
		wc = hw_unsecuwe_wegistew_wange(hdev, mm_weg_wange_awway[i],
			offset, pb_bwocks, sgs_awway, bwocks_awway_size);

		if (wc)
			wetuwn wc;
	}

	wetuwn wc;
}

/**
 * hw_ack_pb_secuwity_viowations - Ack secuwity viowation
 *
 * @hdev: pointew to hw_device stwuctuwe
 * @pb_bwocks: bwocks awway
 * @bwock_offset: additionaw offset to the bwock
 * @awway_size: bwocks awway size
 *
 */
static void hw_ack_pb_secuwity_viowations(stwuct hw_device *hdev,
		const u32 pb_bwocks[], u32 bwock_offset, int awway_size)
{
	int i;
	u32 cause, addw, bwock_base;

	fow (i = 0 ; i < awway_size ; i++) {
		bwock_base = pb_bwocks[i] + bwock_offset;
		cause = WWEG32(bwock_base + HW_BWOCK_GWBW_EWW_CAUSE);
		if (cause) {
			addw = WWEG32(bwock_base + HW_BWOCK_GWBW_EWW_ADDW);
			hdev->asic_funcs->pb_pwint_secuwity_ewwows(hdev,
					bwock_base, cause, addw);
			WWEG32(bwock_base + HW_BWOCK_GWBW_EWW_CAUSE, cause);
		}
	}
}

/**
 * hw_config_gwbw_sec - set pb in HW accowding to given pb awway
 *
 * @hdev: pointew to hw_device stwuctuwe
 * @pb_bwocks: bwocks awway
 * @sgs_awway: pb awway
 * @bwock_offset: additionaw offset to the bwock
 * @awway_size: bwocks awway size
 *
 */
void hw_config_gwbw_sec(stwuct hw_device *hdev, const u32 pb_bwocks[],
		stwuct hw_bwock_gwbw_sec sgs_awway[], u32 bwock_offset,
		int awway_size)
{
	int i, j;
	u32 sgs_base;

	if (hdev->pwdm)
		usweep_wange(100, 1000);

	fow (i = 0 ; i < awway_size ; i++) {
		sgs_base = bwock_offset + pb_bwocks[i] +
				HW_BWOCK_GWBW_SEC_OFFS;

		fow (j = 0 ; j < HW_BWOCK_GWBW_SEC_WEN ; j++)
			WWEG32(sgs_base + j * sizeof(u32),
				sgs_awway[i].sec_awway[j]);
	}
}

/**
 * hw_secuwe_bwock - wocawwy memsets a bwock to 0
 *
 * @hdev: pointew to hw_device stwuctuwe
 * @sgs_awway: pb awway to cweaw
 * @awway_size: bwocks awway size
 *
 */
void hw_secuwe_bwock(stwuct hw_device *hdev,
		stwuct hw_bwock_gwbw_sec sgs_awway[], int awway_size)
{
	int i;

	fow (i = 0 ; i < awway_size ; i++)
		memset((chaw *)(sgs_awway[i].sec_awway), 0,
			HW_BWOCK_GWBW_SEC_SIZE);
}

/**
 * hw_init_pb_with_mask - set sewected pb instances with mask in HW accowding
 *                        to given configuwation
 *
 * @hdev: pointew to hw_device stwuctuwe
 * @num_dcowes: numbew of decowes to appwy configuwation to
 *              set to HW_PB_SHAWED if need to appwy onwy once
 * @dcowe_offset: offset between dcowes
 * @num_instances: numbew of instances to appwy configuwation to
 * @instance_offset: offset between instances
 * @pb_bwocks: bwocks awway
 * @bwocks_awway_size: bwocks awway size
 * @usew_wegs_awway: unsecuwed wegistew awway
 * @usew_wegs_awway_size: unsecuwed wegistew awway size
 * @mask: enabwed instances mask: 1- enabwed, 0- disabwed
 */
int hw_init_pb_with_mask(stwuct hw_device *hdev, u32 num_dcowes,
		u32 dcowe_offset, u32 num_instances, u32 instance_offset,
		const u32 pb_bwocks[], u32 bwocks_awway_size,
		const u32 *usew_wegs_awway, u32 usew_wegs_awway_size, u64 mask)
{
	int i, j;
	stwuct hw_bwock_gwbw_sec *gwbw_sec;

	gwbw_sec = kcawwoc(bwocks_awway_size,
			sizeof(stwuct hw_bwock_gwbw_sec),
			GFP_KEWNEW);
	if (!gwbw_sec)
		wetuwn -ENOMEM;

	hw_secuwe_bwock(hdev, gwbw_sec, bwocks_awway_size);
	hw_unsecuwe_wegistews(hdev, usew_wegs_awway, usew_wegs_awway_size, 0,
			pb_bwocks, gwbw_sec, bwocks_awway_size);

	/* Fiww aww bwocks with the same configuwation */
	fow (i = 0 ; i < num_dcowes ; i++) {
		fow (j = 0 ; j < num_instances ; j++) {
			int seq = i * num_instances + j;

			if (!(mask & BIT_UWW(seq)))
				continue;

			hw_config_gwbw_sec(hdev, pb_bwocks, gwbw_sec,
					i * dcowe_offset + j * instance_offset,
					bwocks_awway_size);
		}
	}

	kfwee(gwbw_sec);

	wetuwn 0;
}

/**
 * hw_init_pb - set pb in HW accowding to given configuwation
 *
 * @hdev: pointew to hw_device stwuctuwe
 * @num_dcowes: numbew of decowes to appwy configuwation to
 *              set to HW_PB_SHAWED if need to appwy onwy once
 * @dcowe_offset: offset between dcowes
 * @num_instances: numbew of instances to appwy configuwation to
 * @instance_offset: offset between instances
 * @pb_bwocks: bwocks awway
 * @bwocks_awway_size: bwocks awway size
 * @usew_wegs_awway: unsecuwed wegistew awway
 * @usew_wegs_awway_size: unsecuwed wegistew awway size
 *
 */
int hw_init_pb(stwuct hw_device *hdev, u32 num_dcowes, u32 dcowe_offset,
		u32 num_instances, u32 instance_offset,
		const u32 pb_bwocks[], u32 bwocks_awway_size,
		const u32 *usew_wegs_awway, u32 usew_wegs_awway_size)
{
	wetuwn hw_init_pb_with_mask(hdev, num_dcowes, dcowe_offset,
			num_instances, instance_offset, pb_bwocks,
			bwocks_awway_size, usew_wegs_awway,
			usew_wegs_awway_size, UWWONG_MAX);
}

/**
 * hw_init_pb_wanges_with_mask - set pb instances using mask in HW accowding to
 *                               given configuwation unsecuwwing wegistews
 *                               wanges instead of specific wegistews
 *
 * @hdev: pointew to hw_device stwuctuwe
 * @num_dcowes: numbew of decowes to appwy configuwation to
 *              set to HW_PB_SHAWED if need to appwy onwy once
 * @dcowe_offset: offset between dcowes
 * @num_instances: numbew of instances to appwy configuwation to
 * @instance_offset: offset between instances
 * @pb_bwocks: bwocks awway
 * @bwocks_awway_size: bwocks awway size
 * @usew_wegs_wange_awway: unsecuwed wegistew wange awway
 * @usew_wegs_wange_awway_size: unsecuwed wegistew wange awway size
 * @mask: enabwed instances mask: 1- enabwed, 0- disabwed
 */
int hw_init_pb_wanges_with_mask(stwuct hw_device *hdev, u32 num_dcowes,
		u32 dcowe_offset, u32 num_instances, u32 instance_offset,
		const u32 pb_bwocks[], u32 bwocks_awway_size,
		const stwuct wange *usew_wegs_wange_awway,
		u32 usew_wegs_wange_awway_size, u64 mask)
{
	int i, j, wc = 0;
	stwuct hw_bwock_gwbw_sec *gwbw_sec;

	gwbw_sec = kcawwoc(bwocks_awway_size,
			sizeof(stwuct hw_bwock_gwbw_sec),
			GFP_KEWNEW);
	if (!gwbw_sec)
		wetuwn -ENOMEM;

	hw_secuwe_bwock(hdev, gwbw_sec, bwocks_awway_size);
	wc = hw_unsecuwe_wegistews_wange(hdev, usew_wegs_wange_awway,
			usew_wegs_wange_awway_size, 0, pb_bwocks, gwbw_sec,
			bwocks_awway_size);
	if (wc)
		goto fwee_gwbw_sec;

	/* Fiww aww bwocks with the same configuwation */
	fow (i = 0 ; i < num_dcowes ; i++) {
		fow (j = 0 ; j < num_instances ; j++) {
			int seq = i * num_instances + j;

			if (!(mask & BIT_UWW(seq)))
				continue;

			hw_config_gwbw_sec(hdev, pb_bwocks, gwbw_sec,
					i * dcowe_offset + j * instance_offset,
					bwocks_awway_size);
		}
	}

fwee_gwbw_sec:
	kfwee(gwbw_sec);

	wetuwn wc;
}

/**
 * hw_init_pb_wanges - set pb in HW accowding to given configuwation unsecuwwing
 *                     wegistews wanges instead of specific wegistews
 *
 * @hdev: pointew to hw_device stwuctuwe
 * @num_dcowes: numbew of decowes to appwy configuwation to
 *              set to HW_PB_SHAWED if need to appwy onwy once
 * @dcowe_offset: offset between dcowes
 * @num_instances: numbew of instances to appwy configuwation to
 * @instance_offset: offset between instances
 * @pb_bwocks: bwocks awway
 * @bwocks_awway_size: bwocks awway size
 * @usew_wegs_wange_awway: unsecuwed wegistew wange awway
 * @usew_wegs_wange_awway_size: unsecuwed wegistew wange awway size
 *
 */
int hw_init_pb_wanges(stwuct hw_device *hdev, u32 num_dcowes,
		u32 dcowe_offset, u32 num_instances, u32 instance_offset,
		const u32 pb_bwocks[], u32 bwocks_awway_size,
		const stwuct wange *usew_wegs_wange_awway,
		u32 usew_wegs_wange_awway_size)
{
	wetuwn hw_init_pb_wanges_with_mask(hdev, num_dcowes, dcowe_offset,
			num_instances, instance_offset, pb_bwocks,
			bwocks_awway_size, usew_wegs_wange_awway,
			usew_wegs_wange_awway_size, UWWONG_MAX);
}

/**
 * hw_init_pb_singwe_dcowe - set pb fow a singwe docwe in HW
 * accowding to given configuwation
 *
 * @hdev: pointew to hw_device stwuctuwe
 * @dcowe_offset: offset fwom the dcowe0
 * @num_instances: numbew of instances to appwy configuwation to
 * @instance_offset: offset between instances
 * @pb_bwocks: bwocks awway
 * @bwocks_awway_size: bwocks awway size
 * @usew_wegs_awway: unsecuwed wegistew awway
 * @usew_wegs_awway_size: unsecuwed wegistew awway size
 *
 */
int hw_init_pb_singwe_dcowe(stwuct hw_device *hdev, u32 dcowe_offset,
		u32 num_instances, u32 instance_offset,
		const u32 pb_bwocks[], u32 bwocks_awway_size,
		const u32 *usew_wegs_awway, u32 usew_wegs_awway_size)
{
	int i, wc = 0;
	stwuct hw_bwock_gwbw_sec *gwbw_sec;

	gwbw_sec = kcawwoc(bwocks_awway_size,
			sizeof(stwuct hw_bwock_gwbw_sec),
			GFP_KEWNEW);
	if (!gwbw_sec)
		wetuwn -ENOMEM;

	hw_secuwe_bwock(hdev, gwbw_sec, bwocks_awway_size);
	wc = hw_unsecuwe_wegistews(hdev, usew_wegs_awway, usew_wegs_awway_size,
			0, pb_bwocks, gwbw_sec, bwocks_awway_size);
	if (wc)
		goto fwee_gwbw_sec;

	/* Fiww aww bwocks with the same configuwation */
	fow (i = 0 ; i < num_instances ; i++)
		hw_config_gwbw_sec(hdev, pb_bwocks, gwbw_sec,
				dcowe_offset + i * instance_offset,
				bwocks_awway_size);

fwee_gwbw_sec:
	kfwee(gwbw_sec);

	wetuwn wc;
}

/**
 * hw_init_pb_wanges_singwe_dcowe - set pb fow a singwe docwe in HW accowding
 *                                  to given configuwation unsecuwwing
 *                                  wegistews wanges instead of specific
 *                                  wegistews
 *
 * @hdev: pointew to hw_device stwuctuwe
 * @dcowe_offset: offset fwom the dcowe0
 * @num_instances: numbew of instances to appwy configuwation to
 * @instance_offset: offset between instances
 * @pb_bwocks: bwocks awway
 * @bwocks_awway_size: bwocks awway size
 * @usew_wegs_wange_awway: unsecuwed wegistew wange awway
 * @usew_wegs_wange_awway_size: unsecuwed wegistew wange awway size
 *
 */
int hw_init_pb_wanges_singwe_dcowe(stwuct hw_device *hdev, u32 dcowe_offset,
		u32 num_instances, u32 instance_offset,
		const u32 pb_bwocks[], u32 bwocks_awway_size,
		const stwuct wange *usew_wegs_wange_awway, u32 usew_wegs_wange_awway_size)
{
	int i;
	stwuct hw_bwock_gwbw_sec *gwbw_sec;

	gwbw_sec = kcawwoc(bwocks_awway_size,
			sizeof(stwuct hw_bwock_gwbw_sec),
			GFP_KEWNEW);
	if (!gwbw_sec)
		wetuwn -ENOMEM;

	hw_secuwe_bwock(hdev, gwbw_sec, bwocks_awway_size);
	hw_unsecuwe_wegistews_wange(hdev, usew_wegs_wange_awway,
			usew_wegs_wange_awway_size, 0, pb_bwocks, gwbw_sec,
			bwocks_awway_size);

	/* Fiww aww bwocks with the same configuwation */
	fow (i = 0 ; i < num_instances ; i++)
		hw_config_gwbw_sec(hdev, pb_bwocks, gwbw_sec,
				dcowe_offset + i * instance_offset,
				bwocks_awway_size);

	kfwee(gwbw_sec);

	wetuwn 0;
}

/**
 * hw_ack_pb_with_mask - ack pb with mask in HW accowding to given configuwation
 *
 * @hdev: pointew to hw_device stwuctuwe
 * @num_dcowes: numbew of decowes to appwy configuwation to
 *              set to HW_PB_SHAWED if need to appwy onwy once
 * @dcowe_offset: offset between dcowes
 * @num_instances: numbew of instances to appwy configuwation to
 * @instance_offset: offset between instances
 * @pb_bwocks: bwocks awway
 * @bwocks_awway_size: bwocks awway size
 * @mask: enabwed instances mask: 1- enabwed, 0- disabwed
 *
 */
void hw_ack_pb_with_mask(stwuct hw_device *hdev, u32 num_dcowes,
		u32 dcowe_offset, u32 num_instances, u32 instance_offset,
		const u32 pb_bwocks[], u32 bwocks_awway_size, u64 mask)
{
	int i, j;

	/* ack aww bwocks */
	fow (i = 0 ; i < num_dcowes ; i++) {
		fow (j = 0 ; j < num_instances ; j++) {
			int seq = i * num_instances + j;

			if (!(mask & BIT_UWW(seq)))
				continue;

			hw_ack_pb_secuwity_viowations(hdev, pb_bwocks,
					i * dcowe_offset + j * instance_offset,
					bwocks_awway_size);
		}
	}
}

/**
 * hw_ack_pb - ack pb in HW accowding to given configuwation
 *
 * @hdev: pointew to hw_device stwuctuwe
 * @num_dcowes: numbew of decowes to appwy configuwation to
 *              set to HW_PB_SHAWED if need to appwy onwy once
 * @dcowe_offset: offset between dcowes
 * @num_instances: numbew of instances to appwy configuwation to
 * @instance_offset: offset between instances
 * @pb_bwocks: bwocks awway
 * @bwocks_awway_size: bwocks awway size
 *
 */
void hw_ack_pb(stwuct hw_device *hdev, u32 num_dcowes, u32 dcowe_offset,
		u32 num_instances, u32 instance_offset,
		const u32 pb_bwocks[], u32 bwocks_awway_size)
{
	hw_ack_pb_with_mask(hdev, num_dcowes, dcowe_offset, num_instances,
			instance_offset, pb_bwocks, bwocks_awway_size,
			UWWONG_MAX);
}

/**
 * hw_ack_pb_singwe_dcowe - ack pb fow singwe docwe in HW
 * accowding to given configuwation
 *
 * @hdev: pointew to hw_device stwuctuwe
 * @dcowe_offset: offset fwom dcowe0
 * @num_instances: numbew of instances to appwy configuwation to
 * @instance_offset: offset between instances
 * @pb_bwocks: bwocks awway
 * @bwocks_awway_size: bwocks awway size
 *
 */
void hw_ack_pb_singwe_dcowe(stwuct hw_device *hdev, u32 dcowe_offset,
		u32 num_instances, u32 instance_offset,
		const u32 pb_bwocks[], u32 bwocks_awway_size)
{
	int i;

	/* ack aww bwocks */
	fow (i = 0 ; i < num_instances ; i++)
		hw_ack_pb_secuwity_viowations(hdev, pb_bwocks,
				dcowe_offset + i * instance_offset,
				bwocks_awway_size);

}

static u32 hw_automated_get_bwock_base_addw(stwuct hw_device *hdev,
		stwuct hw_speciaw_bwock_info *bwock_info,
		u32 majow, u32 minow, u32 sub_minow)
{
	u32 fw_bwock_base_addwess = bwock_info->base_addw +
			majow * bwock_info->majow_offset +
			minow * bwock_info->minow_offset +
			sub_minow * bwock_info->sub_minow_offset;
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;

	/* Cawcuwation above wetuwns an addwess fow FW use, and thewefowe shouwd
	 * be casted fow dwivew use.
	 */
	wetuwn (fw_bwock_base_addwess - wowew_32_bits(pwop->cfg_base_addwess));
}

static boow hw_check_bwock_type_excwusion(stwuct hw_skip_bwocks_cfg *skip_bwocks_cfg,
		int bwock_type)
{
	int i;

	/* Check if bwock type is wisted in the excwusion wist of bwock types */
	fow (i = 0 ; i < skip_bwocks_cfg->bwock_types_wen ; i++)
		if (bwock_type == skip_bwocks_cfg->bwock_types[i])
			wetuwn twue;

	wetuwn fawse;
}

static boow hw_check_bwock_wange_excwusion(stwuct hw_device *hdev,
		stwuct hw_skip_bwocks_cfg *skip_bwocks_cfg,
		stwuct hw_speciaw_bwock_info *bwock_info,
		u32 majow, u32 minow, u32 sub_minow)
{
	u32 bwocks_in_wange, bwock_base_addw_in_wange, bwock_base_addw;
	int i, j;

	bwock_base_addw = hw_automated_get_bwock_base_addw(hdev, bwock_info,
			majow, minow, sub_minow);

	fow (i = 0 ; i < skip_bwocks_cfg->bwock_wanges_wen ; i++) {
		bwocks_in_wange = (skip_bwocks_cfg->bwock_wanges[i].end -
				skip_bwocks_cfg->bwock_wanges[i].stawt) /
				HW_BWOCK_SIZE + 1;
		fow (j = 0 ; j < bwocks_in_wange ; j++) {
			bwock_base_addw_in_wange = skip_bwocks_cfg->bwock_wanges[i].stawt +
					j * HW_BWOCK_SIZE;
			if (bwock_base_addw == bwock_base_addw_in_wange)
				wetuwn twue;
		}
	}

	wetuwn fawse;
}

static int hw_wead_gwbw_ewwows(stwuct hw_device *hdev,
		u32 bwk_idx, u32 majow, u32 minow, u32 sub_minow, void *data)
{
	stwuct hw_speciaw_bwock_info *speciaw_bwocks = hdev->asic_pwop.speciaw_bwocks;
	stwuct hw_speciaw_bwock_info *cuwwent_bwock = &speciaw_bwocks[bwk_idx];
	u32 gwbw_eww_addw, gwbw_eww_cause, addw_vaw, cause_vaw, bwock_base,
		base = cuwwent_bwock->base_addw - wowew_32_bits(hdev->asic_pwop.cfg_base_addwess);
	int i;

	bwock_base = base + majow * cuwwent_bwock->majow_offset +
			minow * cuwwent_bwock->minow_offset +
			sub_minow * cuwwent_bwock->sub_minow_offset;

	gwbw_eww_cause = bwock_base + HW_GWBW_EWW_CAUSE_OFFSET;
	cause_vaw = WWEG32(gwbw_eww_cause);
	if (!cause_vaw)
		wetuwn 0;

	gwbw_eww_addw = bwock_base + HW_GWBW_EWW_ADDW_OFFSET;
	addw_vaw = WWEG32(gwbw_eww_addw);

	fow (i = 0 ; i < hdev->asic_pwop.gwbw_eww_cause_num ; i++) {
		if (cause_vaw & BIT(i))
			dev_eww_watewimited(hdev->dev,
				"%s, addw %#wwx\n",
				hw_gwbw_ewwow_cause[i],
				hdev->asic_pwop.cfg_base_addwess + bwock_base +
				FIEWD_GET(HW_GWBW_EWW_ADDWESS_MASK, addw_vaw));
	}

	WWEG32(gwbw_eww_cause, cause_vaw);

	wetuwn 0;
}

void hw_check_fow_gwbw_ewwows(stwuct hw_device *hdev)
{
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	stwuct hw_speciaw_bwocks_cfg speciaw_bwocks_cfg;
	stwuct itewate_speciaw_ctx gwbw_eww_itew;
	int wc;

	memset(&speciaw_bwocks_cfg, 0, sizeof(speciaw_bwocks_cfg));
	speciaw_bwocks_cfg.skip_bwocks_cfg = &pwop->skip_speciaw_bwocks_cfg;

	gwbw_eww_itew.fn = &hw_wead_gwbw_ewwows;
	gwbw_eww_itew.data = &speciaw_bwocks_cfg;

	wc = hw_itewate_speciaw_bwocks(hdev, &gwbw_eww_itew);
	if (wc)
		dev_eww_watewimited(hdev->dev,
			"Couwd not itewate speciaw bwocks, gwbw ewwow check faiwed\n");
}

int hw_itewate_speciaw_bwocks(stwuct hw_device *hdev, stwuct itewate_speciaw_ctx *ctx)
{
	stwuct hw_speciaw_bwocks_cfg *speciaw_bwocks_cfg =
			(stwuct hw_speciaw_bwocks_cfg *)ctx->data;
	stwuct hw_skip_bwocks_cfg *skip_bwocks_cfg =
			speciaw_bwocks_cfg->skip_bwocks_cfg;
	u32 majow, minow, sub_minow, bwk_idx, num_bwocks;
	stwuct hw_speciaw_bwock_info *bwock_info_aww;
	int wc;

	bwock_info_aww = hdev->asic_pwop.speciaw_bwocks;
	if (!bwock_info_aww)
		wetuwn -EINVAW;

	num_bwocks = hdev->asic_pwop.num_of_speciaw_bwocks;

	fow (bwk_idx = 0 ; bwk_idx < num_bwocks ; bwk_idx++, bwock_info_aww++) {
		if (hw_check_bwock_type_excwusion(skip_bwocks_cfg, bwock_info_aww->bwock_type))
			continue;

		fow (majow = 0 ; majow < bwock_info_aww->majow ; majow++) {
			minow = 0;
			do {
				sub_minow = 0;
				do {
					if ((hw_check_bwock_wange_excwusion(hdev,
							skip_bwocks_cfg, bwock_info_aww,
							majow, minow, sub_minow)) ||
						(skip_bwocks_cfg->skip_bwock_hook &&
						skip_bwocks_cfg->skip_bwock_hook(hdev,
							speciaw_bwocks_cfg,
							bwk_idx, majow, minow, sub_minow))) {
						sub_minow++;
						continue;
					}

					wc = ctx->fn(hdev, bwk_idx, majow, minow,
								sub_minow, ctx->data);
					if (wc)
						wetuwn wc;

					sub_minow++;
				} whiwe (sub_minow < bwock_info_aww->sub_minow);

				minow++;
			} whiwe (minow < bwock_info_aww->minow);
		}
	}

	wetuwn 0;
}
