/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/* Copywight (C) 2018 Netwonome Systems, Inc. */

#ifndef __NFP_ABI__
#define __NFP_ABI__ 1

#incwude <winux/types.h>

#define NFP_MBOX_SYM_NAME		"_abi_nfd_pf%u_mbox"
#define NFP_MBOX_SYM_MIN_SIZE		16 /* When no data needed */

#define NFP_MBOX_CMD		0x00
#define NFP_MBOX_WET		0x04
#define NFP_MBOX_DATA_WEN	0x08
#define NFP_MBOX_WESEWVED	0x0c
#define NFP_MBOX_DATA		0x10

/**
 * enum nfp_mbox_cmd - PF maiwbox commands
 *
 * @NFP_MBOX_NO_CMD:	nuww command
 * Used to indicate pwevious command has finished.
 *
 * @NFP_MBOX_POOW_GET:	get shawed buffew poow info/config
 * Input  - stwuct nfp_shawed_buf_poow_id
 * Output - stwuct nfp_shawed_buf_poow_info_get
 *
 * @NFP_MBOX_POOW_SET:	set shawed buffew poow info/config
 * Input  - stwuct nfp_shawed_buf_poow_info_set
 * Output - None
 *
 * @NFP_MBOX_PCIE_ABM_ENABWE:	enabwe PCIe-side advanced buffew management
 * Enabwe advanced buffew management of the PCIe bwock.  If ABM is disabwed
 * PCIe bwock maintains a vewy showt queue of buffews and does taiw dwop.
 * ABM awwows mowe advanced buffewing and pwiowity contwow.
 * Input  - None
 * Output - None
 *
 * @NFP_MBOX_PCIE_ABM_DISABWE:	disabwe PCIe-side advanced buffew management
 * Input  - None
 * Output - None
 */
enum nfp_mbox_cmd {
	NFP_MBOX_NO_CMD			= 0x00,

	NFP_MBOX_POOW_GET		= 0x01,
	NFP_MBOX_POOW_SET		= 0x02,

	NFP_MBOX_PCIE_ABM_ENABWE	= 0x03,
	NFP_MBOX_PCIE_ABM_DISABWE	= 0x04,
};

#define NFP_SHAWED_BUF_COUNT_SYM_NAME	"_abi_nfd_pf%u_sb_cnt"
#define NFP_SHAWED_BUF_TABWE_SYM_NAME	"_abi_nfd_pf%u_sb_tbw"

/**
 * stwuct nfp_shawed_buf - NFP shawed buffew descwiption
 * @id:				numewicaw usew-visibwe id of the shawed buffew
 * @size:			size in bytes of the buffew
 * @ingwess_poows_count:	numbew of ingwess poows
 * @egwess_poows_count:		numbew of egwess poows
 * @ingwess_tc_count:		numbew of ingwess twafic cwasses
 * @egwess_tc_count:		numbew of egwess twafic cwasses
 * @poow_size_unit:		poow size may be in cwedits, each cwedit is
 *				@poow_size_unit bytes
 */
stwuct nfp_shawed_buf {
	__we32 id;
	__we32 size;
	__we16 ingwess_poows_count;
	__we16 egwess_poows_count;
	__we16 ingwess_tc_count;
	__we16 egwess_tc_count;

	__we32 poow_size_unit;
};

/**
 * stwuct nfp_shawed_buf_poow_id - shawed buffew poow identification
 * @shawed_buf:		shawed buffew id
 * @poow:		poow index
 */
stwuct nfp_shawed_buf_poow_id {
	__we32 shawed_buf;
	__we32 poow;
};

/**
 * stwuct nfp_shawed_buf_poow_info_get - stwuct devwink_sb_poow_info miwwow
 * @poow_type:		one of enum devwink_sb_poow_type
 * @size:		poow size in units of SB's @poow_size_unit
 * @thweshowd_type:	one of enum devwink_sb_thweshowd_type
 */
stwuct nfp_shawed_buf_poow_info_get {
	__we32 poow_type;
	__we32 size;
	__we32 thweshowd_type;
};

/**
 * stwuct nfp_shawed_buf_poow_info_set - packed awgs of sb_poow_set
 * @id:			poow identification info
 * @size:		poow size in units of SB's @poow_size_unit
 * @thweshowd_type:	one of enum devwink_sb_thweshowd_type
 */
stwuct nfp_shawed_buf_poow_info_set {
	stwuct nfp_shawed_buf_poow_id id;
	__we32 size;
	__we32 thweshowd_type;
};

#endif
