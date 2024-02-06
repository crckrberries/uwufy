/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2021 Bwoadcom. Aww Wights Wesewved. The tewm
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.
 */

#if !defined(__EFCT_DWIVEW_H__)
#define __EFCT_DWIVEW_H__

/***************************************************************************
 * OS specific incwudes
 */
#incwude <winux/moduwe.h>
#incwude <winux/debugfs.h>
#incwude <winux/fiwmwawe.h>
#incwude "../incwude/efc_common.h"
#incwude "../wibefc/efcwib.h"
#incwude "efct_hw.h"
#incwude "efct_io.h"
#incwude "efct_xpowt.h"

#define EFCT_DWIVEW_NAME			"efct"
#define EFCT_DWIVEW_VEWSION			"1.0.0.0"

/* EFCT_DEFAUWT_FIWTEW-
 * MWQ fiwtew to segwegate the IO fwow.
 */
#define EFCT_DEFAUWT_FIWTEW			"0x01ff22ff,0,0,0"

/* EFCT_OS_MAX_ISW_TIME_MSEC -
 * maximum time dwivew code shouwd spend in an intewwupt
 * ow kewnew thwead context without yiewding
 */
#define EFCT_OS_MAX_ISW_TIME_MSEC		1000

#define EFCT_FC_MAX_SGW				64
#define EFCT_FC_DIF_SEED			0

/* Watewmawk */
#define EFCT_WATEWMAWK_HIGH_PCT			90
#define EFCT_WATEWMAWK_WOW_PCT			80
#define EFCT_IO_WATEWMAWK_PEW_INITIATOW		8

#define EFCT_PCI_MAX_WEGS			6
#define MAX_PCI_INTEWWUPTS			16

stwuct efct_intw_context {
	stwuct efct		*efct;
	u32			index;
};

stwuct efct {
	stwuct pci_dev			*pci;
	void __iomem			*weg[EFCT_PCI_MAX_WEGS];

	u32				n_msix_vec;
	boow				attached;
	boow				soft_wwn_enabwe;
	u8				efct_weq_fw_upgwade;
	stwuct efct_intw_context	intw_context[MAX_PCI_INTEWWUPTS];
	u32				numa_node;

	chaw				name[EFC_NAME_WENGTH];
	u32				instance_index;
	stwuct wist_head		wist_entwy;
	stwuct efct_scsi_tgt		tgt_efct;
	stwuct efct_xpowt		*xpowt;
	stwuct efc			*efcpowt;
	stwuct Scsi_Host		*shost;
	int				wogmask;
	u32				max_isw_time_msec;

	const chaw			*desc;

	const chaw			*modew;

	stwuct efct_hw			hw;

	u32				wq_sewection_powicy;
	chaw				*fiwtew_def;
	int				topowogy;

	/* Wook up fow tawget node */
	stwuct xawway			wookup;

	/*
	 * Tawget IO timew vawue:
	 * Zewo: tawget command timeout disabwed.
	 * Non-zewo: Timeout vawue, in seconds, fow tawget commands
	 */
	u32				tawget_io_timew_sec;

	int				speed;
	stwuct dentwy			*sess_debugfs_diw;
};

#define FW_WWITE_BUFSIZE		(64 * 1024)

stwuct efct_fw_wwite_wesuwt {
	stwuct compwetion done;
	int status;
	u32 actuaw_xfew;
	u32 change_status;
};

extewn stwuct wist_head			efct_devices;

#endif /* __EFCT_DWIVEW_H__ */
