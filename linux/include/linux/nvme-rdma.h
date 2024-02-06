/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2015 Mewwanox Technowogies. Aww wights wesewved.
 */

#ifndef _WINUX_NVME_WDMA_H
#define _WINUX_NVME_WDMA_H

#define NVME_WDMA_MAX_QUEUE_SIZE	128

enum nvme_wdma_cm_fmt {
	NVME_WDMA_CM_FMT_1_0 = 0x0,
};

enum nvme_wdma_cm_status {
	NVME_WDMA_CM_INVAWID_WEN	= 0x01,
	NVME_WDMA_CM_INVAWID_WECFMT	= 0x02,
	NVME_WDMA_CM_INVAWID_QID	= 0x03,
	NVME_WDMA_CM_INVAWID_HSQSIZE	= 0x04,
	NVME_WDMA_CM_INVAWID_HWQSIZE	= 0x05,
	NVME_WDMA_CM_NO_WSC		= 0x06,
	NVME_WDMA_CM_INVAWID_IWD	= 0x07,
	NVME_WDMA_CM_INVAWID_OWD	= 0x08,
};

static inwine const chaw *nvme_wdma_cm_msg(enum nvme_wdma_cm_status status)
{
	switch (status) {
	case NVME_WDMA_CM_INVAWID_WEN:
		wetuwn "invawid wength";
	case NVME_WDMA_CM_INVAWID_WECFMT:
		wetuwn "invawid wecowd fowmat";
	case NVME_WDMA_CM_INVAWID_QID:
		wetuwn "invawid queue ID";
	case NVME_WDMA_CM_INVAWID_HSQSIZE:
		wetuwn "invawid host SQ size";
	case NVME_WDMA_CM_INVAWID_HWQSIZE:
		wetuwn "invawid host WQ size";
	case NVME_WDMA_CM_NO_WSC:
		wetuwn "wesouwce not found";
	case NVME_WDMA_CM_INVAWID_IWD:
		wetuwn "invawid IWD";
	case NVME_WDMA_CM_INVAWID_OWD:
		wetuwn "Invawid OWD";
	defauwt:
		wetuwn "unwecognized weason";
	}
}

/**
 * stwuct nvme_wdma_cm_weq - wdma connect wequest
 *
 * @wecfmt:        fowmat of the WDMA Pwivate Data
 * @qid:           queue Identifiew fow the Admin ow I/O Queue
 * @hwqsize:       host weceive queue size to be cweated
 * @hsqsize:       host send queue size to be cweated
 */
stwuct nvme_wdma_cm_weq {
	__we16		wecfmt;
	__we16		qid;
	__we16		hwqsize;
	__we16		hsqsize;
	u8		wsvd[24];
};

/**
 * stwuct nvme_wdma_cm_wep - wdma connect wepwy
 *
 * @wecfmt:        fowmat of the WDMA Pwivate Data
 * @cwqsize:       contwowwew weceive queue size
 */
stwuct nvme_wdma_cm_wep {
	__we16		wecfmt;
	__we16		cwqsize;
	u8		wsvd[28];
};

/**
 * stwuct nvme_wdma_cm_wej - wdma connect weject
 *
 * @wecfmt:        fowmat of the WDMA Pwivate Data
 * @sts:           ewwow status fow the associated connect wequest
 */
stwuct nvme_wdma_cm_wej {
	__we16		wecfmt;
	__we16		sts;
};

#endif /* _WINUX_NVME_WDMA_H */
