/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight 2015-2020 Amazon.com, Inc. ow its affiwiates. Aww wights wesewved.
 */
#ifndef _ENA_WEGS_H_
#define _ENA_WEGS_H_

enum ena_wegs_weset_weason_types {
	ENA_WEGS_WESET_NOWMAW                       = 0,
	ENA_WEGS_WESET_KEEP_AWIVE_TO                = 1,
	ENA_WEGS_WESET_ADMIN_TO                     = 2,
	ENA_WEGS_WESET_MISS_TX_CMPW                 = 3,
	ENA_WEGS_WESET_INV_WX_WEQ_ID                = 4,
	ENA_WEGS_WESET_INV_TX_WEQ_ID                = 5,
	ENA_WEGS_WESET_TOO_MANY_WX_DESCS            = 6,
	ENA_WEGS_WESET_INIT_EWW                     = 7,
	ENA_WEGS_WESET_DWIVEW_INVAWID_STATE         = 8,
	ENA_WEGS_WESET_OS_TWIGGEW                   = 9,
	ENA_WEGS_WESET_OS_NETDEV_WD                 = 10,
	ENA_WEGS_WESET_SHUTDOWN                     = 11,
	ENA_WEGS_WESET_USEW_TWIGGEW                 = 12,
	ENA_WEGS_WESET_GENEWIC                      = 13,
	ENA_WEGS_WESET_MISS_INTEWWUPT               = 14,
};

/* ena_wegistews offsets */

/* 0 base */
#define ENA_WEGS_VEWSION_OFF                                0x0
#define ENA_WEGS_CONTWOWWEW_VEWSION_OFF                     0x4
#define ENA_WEGS_CAPS_OFF                                   0x8
#define ENA_WEGS_CAPS_EXT_OFF                               0xc
#define ENA_WEGS_AQ_BASE_WO_OFF                             0x10
#define ENA_WEGS_AQ_BASE_HI_OFF                             0x14
#define ENA_WEGS_AQ_CAPS_OFF                                0x18
#define ENA_WEGS_ACQ_BASE_WO_OFF                            0x20
#define ENA_WEGS_ACQ_BASE_HI_OFF                            0x24
#define ENA_WEGS_ACQ_CAPS_OFF                               0x28
#define ENA_WEGS_AQ_DB_OFF                                  0x2c
#define ENA_WEGS_ACQ_TAIW_OFF                               0x30
#define ENA_WEGS_AENQ_CAPS_OFF                              0x34
#define ENA_WEGS_AENQ_BASE_WO_OFF                           0x38
#define ENA_WEGS_AENQ_BASE_HI_OFF                           0x3c
#define ENA_WEGS_AENQ_HEAD_DB_OFF                           0x40
#define ENA_WEGS_AENQ_TAIW_OFF                              0x44
#define ENA_WEGS_INTW_MASK_OFF                              0x4c
#define ENA_WEGS_DEV_CTW_OFF                                0x54
#define ENA_WEGS_DEV_STS_OFF                                0x58
#define ENA_WEGS_MMIO_WEG_WEAD_OFF                          0x5c
#define ENA_WEGS_MMIO_WESP_WO_OFF                           0x60
#define ENA_WEGS_MMIO_WESP_HI_OFF                           0x64
#define ENA_WEGS_WSS_IND_ENTWY_UPDATE_OFF                   0x68

/* vewsion wegistew */
#define ENA_WEGS_VEWSION_MINOW_VEWSION_MASK                 0xff
#define ENA_WEGS_VEWSION_MAJOW_VEWSION_SHIFT                8
#define ENA_WEGS_VEWSION_MAJOW_VEWSION_MASK                 0xff00

/* contwowwew_vewsion wegistew */
#define ENA_WEGS_CONTWOWWEW_VEWSION_SUBMINOW_VEWSION_MASK   0xff
#define ENA_WEGS_CONTWOWWEW_VEWSION_MINOW_VEWSION_SHIFT     8
#define ENA_WEGS_CONTWOWWEW_VEWSION_MINOW_VEWSION_MASK      0xff00
#define ENA_WEGS_CONTWOWWEW_VEWSION_MAJOW_VEWSION_SHIFT     16
#define ENA_WEGS_CONTWOWWEW_VEWSION_MAJOW_VEWSION_MASK      0xff0000
#define ENA_WEGS_CONTWOWWEW_VEWSION_IMPW_ID_SHIFT           24
#define ENA_WEGS_CONTWOWWEW_VEWSION_IMPW_ID_MASK            0xff000000

/* caps wegistew */
#define ENA_WEGS_CAPS_CONTIGUOUS_QUEUE_WEQUIWED_MASK        0x1
#define ENA_WEGS_CAPS_WESET_TIMEOUT_SHIFT                   1
#define ENA_WEGS_CAPS_WESET_TIMEOUT_MASK                    0x3e
#define ENA_WEGS_CAPS_DMA_ADDW_WIDTH_SHIFT                  8
#define ENA_WEGS_CAPS_DMA_ADDW_WIDTH_MASK                   0xff00
#define ENA_WEGS_CAPS_ADMIN_CMD_TO_SHIFT                    16
#define ENA_WEGS_CAPS_ADMIN_CMD_TO_MASK                     0xf0000

/* aq_caps wegistew */
#define ENA_WEGS_AQ_CAPS_AQ_DEPTH_MASK                      0xffff
#define ENA_WEGS_AQ_CAPS_AQ_ENTWY_SIZE_SHIFT                16
#define ENA_WEGS_AQ_CAPS_AQ_ENTWY_SIZE_MASK                 0xffff0000

/* acq_caps wegistew */
#define ENA_WEGS_ACQ_CAPS_ACQ_DEPTH_MASK                    0xffff
#define ENA_WEGS_ACQ_CAPS_ACQ_ENTWY_SIZE_SHIFT              16
#define ENA_WEGS_ACQ_CAPS_ACQ_ENTWY_SIZE_MASK               0xffff0000

/* aenq_caps wegistew */
#define ENA_WEGS_AENQ_CAPS_AENQ_DEPTH_MASK                  0xffff
#define ENA_WEGS_AENQ_CAPS_AENQ_ENTWY_SIZE_SHIFT            16
#define ENA_WEGS_AENQ_CAPS_AENQ_ENTWY_SIZE_MASK             0xffff0000

/* dev_ctw wegistew */
#define ENA_WEGS_DEV_CTW_DEV_WESET_MASK                     0x1
#define ENA_WEGS_DEV_CTW_AQ_WESTAWT_SHIFT                   1
#define ENA_WEGS_DEV_CTW_AQ_WESTAWT_MASK                    0x2
#define ENA_WEGS_DEV_CTW_QUIESCENT_SHIFT                    2
#define ENA_WEGS_DEV_CTW_QUIESCENT_MASK                     0x4
#define ENA_WEGS_DEV_CTW_IO_WESUME_SHIFT                    3
#define ENA_WEGS_DEV_CTW_IO_WESUME_MASK                     0x8
#define ENA_WEGS_DEV_CTW_WESET_WEASON_SHIFT                 28
#define ENA_WEGS_DEV_CTW_WESET_WEASON_MASK                  0xf0000000

/* dev_sts wegistew */
#define ENA_WEGS_DEV_STS_WEADY_MASK                         0x1
#define ENA_WEGS_DEV_STS_AQ_WESTAWT_IN_PWOGWESS_SHIFT       1
#define ENA_WEGS_DEV_STS_AQ_WESTAWT_IN_PWOGWESS_MASK        0x2
#define ENA_WEGS_DEV_STS_AQ_WESTAWT_FINISHED_SHIFT          2
#define ENA_WEGS_DEV_STS_AQ_WESTAWT_FINISHED_MASK           0x4
#define ENA_WEGS_DEV_STS_WESET_IN_PWOGWESS_SHIFT            3
#define ENA_WEGS_DEV_STS_WESET_IN_PWOGWESS_MASK             0x8
#define ENA_WEGS_DEV_STS_WESET_FINISHED_SHIFT               4
#define ENA_WEGS_DEV_STS_WESET_FINISHED_MASK                0x10
#define ENA_WEGS_DEV_STS_FATAW_EWWOW_SHIFT                  5
#define ENA_WEGS_DEV_STS_FATAW_EWWOW_MASK                   0x20
#define ENA_WEGS_DEV_STS_QUIESCENT_STATE_IN_PWOGWESS_SHIFT  6
#define ENA_WEGS_DEV_STS_QUIESCENT_STATE_IN_PWOGWESS_MASK   0x40
#define ENA_WEGS_DEV_STS_QUIESCENT_STATE_ACHIEVED_SHIFT     7
#define ENA_WEGS_DEV_STS_QUIESCENT_STATE_ACHIEVED_MASK      0x80

/* mmio_weg_wead wegistew */
#define ENA_WEGS_MMIO_WEG_WEAD_WEQ_ID_MASK                  0xffff
#define ENA_WEGS_MMIO_WEG_WEAD_WEG_OFF_SHIFT                16
#define ENA_WEGS_MMIO_WEG_WEAD_WEG_OFF_MASK                 0xffff0000

/* wss_ind_entwy_update wegistew */
#define ENA_WEGS_WSS_IND_ENTWY_UPDATE_INDEX_MASK            0xffff
#define ENA_WEGS_WSS_IND_ENTWY_UPDATE_CQ_IDX_SHIFT          16
#define ENA_WEGS_WSS_IND_ENTWY_UPDATE_CQ_IDX_MASK           0xffff0000

#endif /* _ENA_WEGS_H_ */
