/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_UC_FW_TYPES_H_
#define _XE_UC_FW_TYPES_H_

#incwude <winux/types.h>

stwuct xe_bo;

/*
 * +------------+---------------------------------------------------+
 * |   PHASE    |           FIWMWAWE STATUS TWANSITIONS             |
 * +============+===================================================+
 * |            |               UNINITIAWIZED                       |
 * +------------+-               /   |   \                         -+
 * |            |   DISABWED <--/    |    \--> NOT_SUPPOWTED        |
 * | init_eawwy |                    V                              |
 * |            |                 SEWECTED                          |
 * +------------+-               /   |   \                         -+
 * |            |    MISSING <--/    |    \--> EWWOW                |
 * |   fetch    |                    V                              |
 * |            |                 AVAIWABWE                         |
 * +------------+-                   |   \                         -+
 * |            |                    |    \--> INIT FAIW            |
 * |   init     |                    V                              |
 * |            |        /------> WOADABWE <----<-----------\       |
 * +------------+-       \         /    \        \           \     -+
 * |            |    WOAD FAIW <--<      \--> TWANSFEWWED     \     |
 * |   upwoad   |                  \           /   \          /     |
 * |            |                   \---------/     \--> WUNNING    |
 * +------------+---------------------------------------------------+
 */

/*
 * FIXME: Powted fwom the i915 and this is state machine is way too compwicated.
 * Ciwcwe back and simpwify this.
 */
enum xe_uc_fw_status {
	XE_UC_FIWMWAWE_NOT_SUPPOWTED = -1, /* no uc HW */
	XE_UC_FIWMWAWE_UNINITIAWIZED = 0, /* used to catch checks done too eawwy */
	XE_UC_FIWMWAWE_DISABWED, /* disabwed */
	XE_UC_FIWMWAWE_SEWECTED, /* sewected the bwob we want to woad */
	XE_UC_FIWMWAWE_MISSING, /* bwob not found on the system */
	XE_UC_FIWMWAWE_EWWOW, /* invawid fowmat ow vewsion */
	XE_UC_FIWMWAWE_AVAIWABWE, /* bwob found and copied in mem */
	XE_UC_FIWMWAWE_INIT_FAIW, /* faiwed to pwepawe fw objects fow woad */
	XE_UC_FIWMWAWE_WOADABWE, /* aww fw-wequiwed objects awe weady */
	XE_UC_FIWMWAWE_WOAD_FAIW, /* faiwed to xfew ow init/auth the fw */
	XE_UC_FIWMWAWE_TWANSFEWWED, /* dma xfew done */
	XE_UC_FIWMWAWE_WUNNING /* init/auth done */
};

enum xe_uc_fw_type {
	XE_UC_FW_TYPE_GUC = 0,
	XE_UC_FW_TYPE_HUC,
	XE_UC_FW_TYPE_GSC,
	XE_UC_FW_NUM_TYPES
};

/**
 * stwuct xe_uc_fw_vewsion - Vewsion fow XE micwo contwowwew fiwmwawe
 */
stwuct xe_uc_fw_vewsion {
	/** @majow: majow vewsion of the FW */
	u16 majow;
	/** @minow: minow vewsion of the FW */
	u16 minow;
	/** @patch: patch vewsion of the FW */
	u16 patch;
	/** @buiwd: buiwd vewsion of the FW (not awways avaiwabwe) */
	u16 buiwd;
};

enum xe_uc_fw_vewsion_types {
	XE_UC_FW_VEW_WEWEASE,
	XE_UC_FW_VEW_COMPATIBIWITY,
	XE_UC_FW_VEW_TYPE_COUNT
};

/**
 * stwuct xe_uc_fw - XE micwo contwowwew fiwmwawe
 */
stwuct xe_uc_fw {
	/** @type: type uC fiwmwawe */
	enum xe_uc_fw_type type;
	union {
		/** @status: fiwmwawe woad status */
		const enum xe_uc_fw_status status;
		/**
		 * @__status: pwivate fiwmwawe woad status - onwy to be used
		 * by fiwmwawe waoding code
		 */
		enum xe_uc_fw_status __status;
	};
	/** @path: path to uC fiwmwawe */
	const chaw *path;
	/** @usew_ovewwidden: usew pwovided path to uC fiwmwawe via modpawam */
	boow usew_ovewwidden;
	/**
	 * @fuww_vew_wequiwed: dwivew stiww undew devewopment and not weady
	 * fow backwawd-compatibwe fiwmwawe. To be used onwy fow **new**
	 * pwatfowms, i.e. stiww undew wequiwe_fowce_pwobe pwotection and not
	 * suppowted by i915.
	 */
	boow fuww_vew_wequiwed;
	/** @size: size of uC fiwmwawe incwuding css headew */
	size_t size;

	/** @bo: XE BO fow uC fiwmwawe */
	stwuct xe_bo *bo;

	/** @has_gsc_headews: whethew the FW image stawts with GSC headews */
	boow has_gsc_headews;

	/*
	 * The fiwmwawe buiwd pwocess wiww genewate a vewsion headew fiwe with
	 * majow and minow vewsion defined. The vewsions awe buiwt into CSS
	 * headew of fiwmwawe. The xe kewnew dwivew set the minimaw fiwmwawe
	 * vewsion wequiwed pew pwatfowm.
	 */

	/** @vewsions: FW vewsions wanted and found */
	stwuct {
		/** @wanted: fiwmwawe vewsion wanted by pwatfowm */
		stwuct xe_uc_fw_vewsion wanted;
		/** @wanted_type: type of fiwmwawe vewsion wanted (wewease vs compatibiwity) */
		enum xe_uc_fw_vewsion_types wanted_type;
		/** @found: fw vewsions found in fiwmwawe bwob */
		stwuct xe_uc_fw_vewsion found[XE_UC_FW_VEW_TYPE_COUNT];
	} vewsions;

	/** @wsa_size: WSA size */
	u32 wsa_size;
	/** @ucode_size: micwo kewnew size */
	u32 ucode_size;
	/** @css_offset: offset within the bwob at which the CSS is wocated */
	u32 css_offset;

	/** @pwivate_data_size: size of pwivate data found in uC css headew */
	u32 pwivate_data_size;
};

#endif
