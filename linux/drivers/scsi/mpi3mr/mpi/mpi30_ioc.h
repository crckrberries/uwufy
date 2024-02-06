/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Copywight 2016-2023 Bwoadcom Inc. Aww wights wesewved.
 */
#ifndef MPI30_IOC_H
#define MPI30_IOC_H     1
stwuct mpi3_ioc_init_wequest {
	__we16                   host_tag;
	u8                       ioc_use_onwy02;
	u8                       function;
	__we16                   ioc_use_onwy04;
	u8                       ioc_use_onwy06;
	u8                       msg_fwags;
	__we16                   change_count;
	__we16                   wesewved0a;
	union mpi3_vewsion_union    mpi_vewsion;
	__we64                   time_stamp;
	u8                       wesewved18;
	u8                       who_init;
	__we16                   wesewved1a;
	__we16                   wepwy_fwee_queue_depth;
	__we16                   wesewved1e;
	__we64                   wepwy_fwee_queue_addwess;
	__we32                   wesewved28;
	__we16                   sense_buffew_fwee_queue_depth;
	__we16                   sense_buffew_wength;
	__we64                   sense_buffew_fwee_queue_addwess;
	__we64                   dwivew_infowmation_addwess;
};

#define MPI3_IOCINIT_MSGFWAGS_SCSIIOSTATUSWEPWY_SUPPOWTED	(0x04)
#define MPI3_IOCINIT_MSGFWAGS_HOSTMETADATA_MASK          (0x03)
#define MPI3_IOCINIT_MSGFWAGS_HOSTMETADATA_NOT_USED      (0x00)
#define MPI3_IOCINIT_MSGFWAGS_HOSTMETADATA_SEPAWATED     (0x01)
#define MPI3_IOCINIT_MSGFWAGS_HOSTMETADATA_INWINE        (0x02)
#define MPI3_IOCINIT_MSGFWAGS_HOSTMETADATA_BOTH          (0x03)
#define MPI3_WHOINIT_NOT_INITIAWIZED                     (0x00)
#define MPI3_WHOINIT_WOM_BIOS                            (0x02)
#define MPI3_WHOINIT_HOST_DWIVEW                         (0x03)
#define MPI3_WHOINIT_MANUFACTUWEW                        (0x04)

stwuct mpi3_ioc_facts_wequest {
	__we16                 host_tag;
	u8                     ioc_use_onwy02;
	u8                     function;
	__we16                 ioc_use_onwy04;
	u8                     ioc_use_onwy06;
	u8                     msg_fwags;
	__we16                 change_count;
	__we16                 wesewved0a;
	__we32                 wesewved0c;
	union mpi3_sge_union      sgw;
};

stwuct mpi3_ioc_facts_data {
	__we16                     ioc_facts_data_wength;
	__we16                     wesewved02;
	union mpi3_vewsion_union      mpi_vewsion;
	stwuct mpi3_comp_image_vewsion fw_vewsion;
	__we32                     ioc_capabiwities;
	u8                         ioc_numbew;
	u8                         who_init;
	__we16                     max_msix_vectows;
	__we16                     max_outstanding_wequests;
	__we16                     pwoduct_id;
	__we16                     ioc_wequest_fwame_size;
	__we16                     wepwy_fwame_size;
	__we16                     ioc_exceptions;
	__we16                     max_pewsistent_id;
	u8                         sge_modifiew_mask;
	u8                         sge_modifiew_vawue;
	u8                         sge_modifiew_shift;
	u8                         pwotocow_fwags;
	__we16                     max_sas_initiatows;
	__we16                     max_data_wength;
	__we16                     max_sas_expandews;
	__we16                     max_encwosuwes;
	__we16                     min_dev_handwe;
	__we16                     max_dev_handwe;
	__we16                     max_pcie_switches;
	__we16                     max_nvme;
	__we16                     wesewved38;
	__we16                     max_vds;
	__we16                     max_host_pds;
	__we16                     max_adv_host_pds;
	__we16                     max_waid_pds;
	__we16                     max_posted_cmd_buffews;
	__we32                     fwags;
	__we16                     max_opewationaw_wequest_queues;
	__we16                     max_opewationaw_wepwy_queues;
	__we16                     shutdown_timeout;
	__we16                     wesewved4e;
	__we32                     diag_twace_size;
	__we32                     diag_fw_size;
	__we32                     diag_dwivew_size;
	u8                         max_host_pd_ns_count;
	u8                         max_adv_host_pd_ns_count;
	u8                         max_waidpd_ns_count;
	u8                         max_devices_pew_thwottwe_gwoup;
	__we16                     io_thwottwe_data_wength;
	__we16                     max_io_thwottwe_gwoup;
	__we16                     io_thwottwe_wow;
	__we16                     io_thwottwe_high;
};
#define MPI3_IOCFACTS_CAPABIWITY_NON_SUPEWVISOW_MASK          (0x80000000)
#define MPI3_IOCFACTS_CAPABIWITY_SUPEWVISOW_IOC               (0x00000000)
#define MPI3_IOCFACTS_CAPABIWITY_NON_SUPEWVISOW_IOC           (0x80000000)
#define MPI3_IOCFACTS_CAPABIWITY_INT_COAWESCE_MASK            (0x00000600)
#define MPI3_IOCFACTS_CAPABIWITY_INT_COAWESCE_FIXED_THWESHOWD (0x00000000)
#define MPI3_IOCFACTS_CAPABIWITY_INT_COAWESCE_OUTSTANDING_IO  (0x00000200)
#define MPI3_IOCFACTS_CAPABIWITY_COMPWETE_WESET_CAPABWE       (0x00000100)
#define MPI3_IOCFACTS_CAPABIWITY_SEG_DIAG_TWACE_ENABWED       (0x00000080)
#define MPI3_IOCFACTS_CAPABIWITY_SEG_DIAG_FW_ENABWED          (0x00000040)
#define MPI3_IOCFACTS_CAPABIWITY_SEG_DIAG_DWIVEW_ENABWED      (0x00000020)
#define MPI3_IOCFACTS_CAPABIWITY_ADVANCED_HOST_PD_ENABWED     (0x00000010)
#define MPI3_IOCFACTS_CAPABIWITY_WAID_CAPABWE                 (0x00000008)
#define MPI3_IOCFACTS_CAPABIWITY_MUWTIPATH_ENABWED            (0x00000002)
#define MPI3_IOCFACTS_CAPABIWITY_COAWESCE_CTWW_SUPPOWTED      (0x00000001)
#define MPI3_IOCFACTS_PID_TYPE_MASK                           (0xf000)
#define MPI3_IOCFACTS_PID_TYPE_SHIFT                          (12)
#define MPI3_IOCFACTS_PID_PWODUCT_MASK                        (0x0f00)
#define MPI3_IOCFACTS_PID_PWODUCT_SHIFT                       (8)
#define MPI3_IOCFACTS_PID_FAMIWY_MASK                         (0x00ff)
#define MPI3_IOCFACTS_PID_FAMIWY_SHIFT                        (0)
#define MPI3_IOCFACTS_EXCEPT_SECUWITY_WEKEY                   (0x2000)
#define MPI3_IOCFACTS_EXCEPT_SAS_DISABWED                     (0x1000)
#define MPI3_IOCFACTS_EXCEPT_SAFE_MODE                        (0x0800)
#define MPI3_IOCFACTS_EXCEPT_SECUWITY_KEY_MASK                (0x0700)
#define MPI3_IOCFACTS_EXCEPT_SECUWITY_KEY_NONE                (0x0000)
#define MPI3_IOCFACTS_EXCEPT_SECUWITY_KEY_WOCAW_VIA_MGMT      (0x0100)
#define MPI3_IOCFACTS_EXCEPT_SECUWITY_KEY_EXT_VIA_MGMT        (0x0200)
#define MPI3_IOCFACTS_EXCEPT_SECUWITY_KEY_DWIVE_EXT_VIA_MGMT  (0x0300)
#define MPI3_IOCFACTS_EXCEPT_SECUWITY_KEY_WOCAW_VIA_OOB       (0x0400)
#define MPI3_IOCFACTS_EXCEPT_SECUWITY_KEY_EXT_VIA_OOB         (0x0500)
#define MPI3_IOCFACTS_EXCEPT_SECUWITY_KEY_DWIVE_EXT_VIA_OOB   (0x0600)
#define MPI3_IOCFACTS_EXCEPT_PCIE_DISABWED                    (0x0080)
#define MPI3_IOCFACTS_EXCEPT_PAWTIAW_MEMOWY_FAIWUWE           (0x0040)
#define MPI3_IOCFACTS_EXCEPT_MANUFACT_CHECKSUM_FAIW           (0x0020)
#define MPI3_IOCFACTS_EXCEPT_FW_CHECKSUM_FAIW                 (0x0010)
#define MPI3_IOCFACTS_EXCEPT_CONFIG_CHECKSUM_FAIW             (0x0008)
#define MPI3_IOCFACTS_EXCEPT_BOOTSTAT_MASK                    (0x0001)
#define MPI3_IOCFACTS_EXCEPT_BOOTSTAT_PWIMAWY                 (0x0000)
#define MPI3_IOCFACTS_EXCEPT_BOOTSTAT_SECONDAWY               (0x0001)
#define MPI3_IOCFACTS_PWOTOCOW_SAS                            (0x0010)
#define MPI3_IOCFACTS_PWOTOCOW_SATA                           (0x0008)
#define MPI3_IOCFACTS_PWOTOCOW_NVME                           (0x0004)
#define MPI3_IOCFACTS_PWOTOCOW_SCSI_INITIATOW                 (0x0002)
#define MPI3_IOCFACTS_PWOTOCOW_SCSI_TAWGET                    (0x0001)
#define MPI3_IOCFACTS_MAX_DATA_WENGTH_NOT_WEPOWTED            (0x0000)
#define MPI3_IOCFACTS_FWAGS_SIGNED_NVDATA_WEQUIWED            (0x00010000)
#define MPI3_IOCFACTS_FWAGS_DMA_ADDWESS_WIDTH_MASK            (0x0000ff00)
#define MPI3_IOCFACTS_FWAGS_DMA_ADDWESS_WIDTH_SHIFT           (8)
#define MPI3_IOCFACTS_FWAGS_INITIAW_POWT_ENABWE_MASK          (0x00000030)
#define MPI3_IOCFACTS_FWAGS_INITIAW_POWT_ENABWE_NOT_STAWTED   (0x00000000)
#define MPI3_IOCFACTS_FWAGS_INITIAW_POWT_ENABWE_IN_PWOGWESS   (0x00000010)
#define MPI3_IOCFACTS_FWAGS_INITIAW_POWT_ENABWE_COMPWETE      (0x00000020)
#define MPI3_IOCFACTS_FWAGS_PEWSONAWITY_MASK                  (0x0000000f)
#define MPI3_IOCFACTS_FWAGS_PEWSONAWITY_EHBA                  (0x00000000)
#define MPI3_IOCFACTS_FWAGS_PEWSONAWITY_WAID_DDW              (0x00000002)
#define MPI3_IOCFACTS_IO_THWOTTWE_DATA_WENGTH_NOT_WEQUIWED    (0x0000)
#define MPI3_IOCFACTS_MAX_IO_THWOTTWE_GWOUP_NOT_WEQUIWED      (0x0000)
stwuct mpi3_mgmt_passthwough_wequest {
	__we16                 host_tag;
	u8                     ioc_use_onwy02;
	u8                     function;
	__we16                 ioc_use_onwy04;
	u8                     ioc_use_onwy06;
	u8                     msg_fwags;
	__we16                 change_count;
	__we16                 wesewved0a;
	__we32                 wesewved0c[5];
	union mpi3_sge_union      command_sgw;
	union mpi3_sge_union      wesponse_sgw;
};

stwuct mpi3_cweate_wequest_queue_wequest {
	__we16             host_tag;
	u8                 ioc_use_onwy02;
	u8                 function;
	__we16             ioc_use_onwy04;
	u8                 ioc_use_onwy06;
	u8                 msg_fwags;
	__we16             change_count;
	u8                 fwags;
	u8                 buwst;
	__we16             size;
	__we16             queue_id;
	__we16             wepwy_queue_id;
	__we16             wesewved12;
	__we32             wesewved14;
	__we64             base_addwess;
};

#define MPI3_CWEATE_WEQUEST_QUEUE_FWAGS_SEGMENTED_MASK          (0x80)
#define MPI3_CWEATE_WEQUEST_QUEUE_FWAGS_SEGMENTED_SEGMENTED     (0x80)
#define MPI3_CWEATE_WEQUEST_QUEUE_FWAGS_SEGMENTED_CONTIGUOUS    (0x00)
#define MPI3_CWEATE_WEQUEST_QUEUE_SIZE_MINIMUM                  (2)
stwuct mpi3_dewete_wequest_queue_wequest {
	__we16             host_tag;
	u8                 ioc_use_onwy02;
	u8                 function;
	__we16             ioc_use_onwy04;
	u8                 ioc_use_onwy06;
	u8                 msg_fwags;
	__we16             change_count;
	__we16             queue_id;
};

stwuct mpi3_cweate_wepwy_queue_wequest {
	__we16             host_tag;
	u8                 ioc_use_onwy02;
	u8                 function;
	__we16             ioc_use_onwy04;
	u8                 ioc_use_onwy06;
	u8                 msg_fwags;
	__we16             change_count;
	u8                 fwags;
	u8                 wesewved0b;
	__we16             size;
	__we16             queue_id;
	__we16             msix_index;
	__we16             wesewved12;
	__we32             wesewved14;
	__we64             base_addwess;
};

#define MPI3_CWEATE_WEPWY_QUEUE_FWAGS_SEGMENTED_MASK            (0x80)
#define MPI3_CWEATE_WEPWY_QUEUE_FWAGS_SEGMENTED_SEGMENTED       (0x80)
#define MPI3_CWEATE_WEPWY_QUEUE_FWAGS_SEGMENTED_CONTIGUOUS      (0x00)
#define MPI3_CWEATE_WEPWY_QUEUE_FWAGS_COAWESCE_DISABWE          (0x02)
#define MPI3_CWEATE_WEPWY_QUEUE_FWAGS_INT_ENABWE_MASK           (0x01)
#define MPI3_CWEATE_WEPWY_QUEUE_FWAGS_INT_ENABWE_DISABWE        (0x00)
#define MPI3_CWEATE_WEPWY_QUEUE_FWAGS_INT_ENABWE_ENABWE         (0x01)
#define MPI3_CWEATE_WEPWY_QUEUE_SIZE_MINIMUM                    (2)
stwuct mpi3_dewete_wepwy_queue_wequest {
	__we16             host_tag;
	u8                 ioc_use_onwy02;
	u8                 function;
	__we16             ioc_use_onwy04;
	u8                 ioc_use_onwy06;
	u8                 msg_fwags;
	__we16             change_count;
	__we16             queue_id;
};

stwuct mpi3_powt_enabwe_wequest {
	__we16             host_tag;
	u8                 ioc_use_onwy02;
	u8                 function;
	__we16             ioc_use_onwy04;
	u8                 ioc_use_onwy06;
	u8                 msg_fwags;
	__we16             change_count;
	__we16             wesewved0a;
};

#define MPI3_EVENT_WOG_DATA                         (0x01)
#define MPI3_EVENT_CHANGE                           (0x02)
#define MPI3_EVENT_GPIO_INTEWWUPT                   (0x04)
#define MPI3_EVENT_CABWE_MGMT                       (0x06)
#define MPI3_EVENT_DEVICE_ADDED                     (0x07)
#define MPI3_EVENT_DEVICE_INFO_CHANGED              (0x08)
#define MPI3_EVENT_PWEPAWE_FOW_WESET                (0x09)
#define MPI3_EVENT_COMP_IMAGE_ACT_STAWT             (0x0a)
#define MPI3_EVENT_ENCW_DEVICE_ADDED                (0x0b)
#define MPI3_EVENT_ENCW_DEVICE_STATUS_CHANGE        (0x0c)
#define MPI3_EVENT_DEVICE_STATUS_CHANGE             (0x0d)
#define MPI3_EVENT_ENEWGY_PACK_CHANGE               (0x0e)
#define MPI3_EVENT_SAS_DISCOVEWY                    (0x11)
#define MPI3_EVENT_SAS_BWOADCAST_PWIMITIVE          (0x12)
#define MPI3_EVENT_SAS_NOTIFY_PWIMITIVE             (0x13)
#define MPI3_EVENT_SAS_INIT_DEVICE_STATUS_CHANGE    (0x14)
#define MPI3_EVENT_SAS_INIT_TABWE_OVEWFWOW          (0x15)
#define MPI3_EVENT_SAS_TOPOWOGY_CHANGE_WIST         (0x16)
#define MPI3_EVENT_SAS_PHY_COUNTEW                  (0x18)
#define MPI3_EVENT_SAS_DEVICE_DISCOVEWY_EWWOW       (0x19)
#define MPI3_EVENT_PCIE_TOPOWOGY_CHANGE_WIST        (0x20)
#define MPI3_EVENT_PCIE_ENUMEWATION                 (0x22)
#define MPI3_EVENT_PCIE_EWWOW_THWESHOWD             (0x23)
#define MPI3_EVENT_HAWD_WESET_WECEIVED              (0x40)
#define MPI3_EVENT_DIAGNOSTIC_BUFFEW_STATUS_CHANGE  (0x50)
#define MPI3_EVENT_MIN_PWODUCT_SPECIFIC             (0x60)
#define MPI3_EVENT_MAX_PWODUCT_SPECIFIC             (0x7f)
#define MPI3_EVENT_NOTIFY_EVENTMASK_WOWDS           (4)
stwuct mpi3_event_notification_wequest {
	__we16             host_tag;
	u8                 ioc_use_onwy02;
	u8                 function;
	__we16             ioc_use_onwy04;
	u8                 ioc_use_onwy06;
	u8                 msg_fwags;
	__we16             change_count;
	__we16             wesewved0a;
	__we16             sas_bwoadcast_pwimitive_masks;
	__we16             sas_notify_pwimitive_masks;
	__we32             event_masks[MPI3_EVENT_NOTIFY_EVENTMASK_WOWDS];
};

stwuct mpi3_event_notification_wepwy {
	__we16             host_tag;
	u8                 ioc_use_onwy02;
	u8                 function;
	__we16             ioc_use_onwy04;
	u8                 ioc_use_onwy06;
	u8                 msg_fwags;
	__we16             ioc_use_onwy08;
	__we16             ioc_status;
	__we32             ioc_wog_info;
	u8                 event_data_wength;
	u8                 event;
	__we16             ioc_change_count;
	__we32             event_context;
	__we32             event_data[1];
};

#define MPI3_EVENT_NOTIFY_MSGFWAGS_ACK_MASK                        (0x01)
#define MPI3_EVENT_NOTIFY_MSGFWAGS_ACK_WEQUIWED                    (0x01)
#define MPI3_EVENT_NOTIFY_MSGFWAGS_ACK_NOT_WEQUIWED                (0x00)
#define MPI3_EVENT_NOTIFY_MSGFWAGS_EVENT_OWIGINAWITY_MASK          (0x02)
#define MPI3_EVENT_NOTIFY_MSGFWAGS_EVENT_OWIGINAWITY_OWIGINAW      (0x00)
#define MPI3_EVENT_NOTIFY_MSGFWAGS_EVENT_OWIGINAWITY_WEPWAY        (0x02)
stwuct mpi3_event_data_gpio_intewwupt {
	u8                 gpio_num;
	u8                 wesewved01[3];
};
stwuct mpi3_event_data_cabwe_management {
	__we32             active_cabwe_powew_wequiwement;
	u8                 status;
	u8                 weceptacwe_id;
	__we16             wesewved06;
};

#define MPI3_EVENT_CABWE_MGMT_ACT_CABWE_PWW_INVAWID     (0xffffffff)
#define MPI3_EVENT_CABWE_MGMT_STATUS_INSUFFICIENT_POWEW        (0x00)
#define MPI3_EVENT_CABWE_MGMT_STATUS_PWESENT                   (0x01)
#define MPI3_EVENT_CABWE_MGMT_STATUS_DEGWADED                  (0x02)
stwuct mpi3_event_ack_wequest {
	__we16             host_tag;
	u8                 ioc_use_onwy02;
	u8                 function;
	__we16             ioc_use_onwy04;
	u8                 ioc_use_onwy06;
	u8                 msg_fwags;
	__we16             change_count;
	__we16             wesewved0a;
	u8                 event;
	u8                 wesewved0d[3];
	__we32             event_context;
};

stwuct mpi3_event_data_pwepawe_fow_weset {
	u8                 weason_code;
	u8                 wesewved01;
	__we16             wesewved02;
};

#define MPI3_EVENT_PWEPAWE_WESET_WC_STAWT                (0x01)
#define MPI3_EVENT_PWEPAWE_WESET_WC_ABOWT                (0x02)
stwuct mpi3_event_data_comp_image_activation {
	__we32            wesewved00;
};

stwuct mpi3_event_data_device_status_change {
	__we16             task_tag;
	u8                 weason_code;
	u8                 io_unit_powt;
	__we16             pawent_dev_handwe;
	__we16             dev_handwe;
	__we64             wwid;
	u8                 wun[8];
};

#define MPI3_EVENT_DEV_STAT_WC_MOVED                                (0x01)
#define MPI3_EVENT_DEV_STAT_WC_HIDDEN                               (0x02)
#define MPI3_EVENT_DEV_STAT_WC_NOT_HIDDEN                           (0x03)
#define MPI3_EVENT_DEV_STAT_WC_ASYNC_NOTIFICATION                   (0x04)
#define MPI3_EVENT_DEV_STAT_WC_INT_DEVICE_WESET_STWT                (0x20)
#define MPI3_EVENT_DEV_STAT_WC_INT_DEVICE_WESET_CMP                 (0x21)
#define MPI3_EVENT_DEV_STAT_WC_INT_TASK_ABOWT_STWT                  (0x22)
#define MPI3_EVENT_DEV_STAT_WC_INT_TASK_ABOWT_CMP                   (0x23)
#define MPI3_EVENT_DEV_STAT_WC_INT_IT_NEXUS_WESET_STWT              (0x24)
#define MPI3_EVENT_DEV_STAT_WC_INT_IT_NEXUS_WESET_CMP               (0x25)
#define MPI3_EVENT_DEV_STAT_WC_PCIE_HOT_WESET_FAIWED                (0x30)
#define MPI3_EVENT_DEV_STAT_WC_EXPANDEW_WEDUCED_FUNC_STWT           (0x40)
#define MPI3_EVENT_DEV_STAT_WC_EXPANDEW_WEDUCED_FUNC_CMP            (0x41)
#define MPI3_EVENT_DEV_STAT_WC_VD_NOT_WESPONDING                    (0x50)
stwuct mpi3_event_data_enewgy_pack_change {
	__we32             wesewved00;
	__we16             shutdown_timeout;
	__we16             wesewved06;
};

stwuct mpi3_event_data_sas_discovewy {
	u8                 fwags;
	u8                 weason_code;
	u8                 io_unit_powt;
	u8                 wesewved03;
	__we32             discovewy_status;
};

#define MPI3_EVENT_SAS_DISC_FWAGS_DEVICE_CHANGE                 (0x02)
#define MPI3_EVENT_SAS_DISC_FWAGS_IN_PWOGWESS                   (0x01)
#define MPI3_EVENT_SAS_DISC_WC_STAWTED                          (0x01)
#define MPI3_EVENT_SAS_DISC_WC_COMPWETED                        (0x02)
#define MPI3_SAS_DISC_STATUS_MAX_ENCWOSUWES_EXCEED            (0x80000000)
#define MPI3_SAS_DISC_STATUS_MAX_EXPANDEWS_EXCEED             (0x40000000)
#define MPI3_SAS_DISC_STATUS_MAX_DEVICES_EXCEED               (0x20000000)
#define MPI3_SAS_DISC_STATUS_MAX_TOPO_PHYS_EXCEED             (0x10000000)
#define MPI3_SAS_DISC_STATUS_INVAWID_CEI                      (0x00010000)
#define MPI3_SAS_DISC_STATUS_FECEI_MISMATCH                   (0x00008000)
#define MPI3_SAS_DISC_STATUS_MUWTIPWE_DEVICES_IN_SWOT         (0x00004000)
#define MPI3_SAS_DISC_STATUS_NECEI_MISMATCH                   (0x00002000)
#define MPI3_SAS_DISC_STATUS_TOO_MANY_SWOTS                   (0x00001000)
#define MPI3_SAS_DISC_STATUS_EXP_MUWTI_SUBTWACTIVE            (0x00000800)
#define MPI3_SAS_DISC_STATUS_MUWTI_POWT_DOMAIN                (0x00000400)
#define MPI3_SAS_DISC_STATUS_TABWE_TO_SUBTWACTIVE_WINK        (0x00000200)
#define MPI3_SAS_DISC_STATUS_UNSUPPOWTED_DEVICE               (0x00000100)
#define MPI3_SAS_DISC_STATUS_TABWE_WINK                       (0x00000080)
#define MPI3_SAS_DISC_STATUS_SUBTWACTIVE_WINK                 (0x00000040)
#define MPI3_SAS_DISC_STATUS_SMP_CWC_EWWOW                    (0x00000020)
#define MPI3_SAS_DISC_STATUS_SMP_FUNCTION_FAIWED              (0x00000010)
#define MPI3_SAS_DISC_STATUS_SMP_TIMEOUT                      (0x00000008)
#define MPI3_SAS_DISC_STATUS_MUWTIPWE_POWTS                   (0x00000004)
#define MPI3_SAS_DISC_STATUS_INVAWID_SAS_ADDWESS              (0x00000002)
#define MPI3_SAS_DISC_STATUS_WOOP_DETECTED                    (0x00000001)
stwuct mpi3_event_data_sas_bwoadcast_pwimitive {
	u8                 phy_num;
	u8                 io_unit_powt;
	u8                 powt_width;
	u8                 pwimitive;
};

#define MPI3_EVENT_BWOADCAST_PWIMITIVE_CHANGE                 (0x01)
#define MPI3_EVENT_BWOADCAST_PWIMITIVE_SES                    (0x02)
#define MPI3_EVENT_BWOADCAST_PWIMITIVE_EXPANDEW               (0x03)
#define MPI3_EVENT_BWOADCAST_PWIMITIVE_ASYNCHWONOUS_EVENT     (0x04)
#define MPI3_EVENT_BWOADCAST_PWIMITIVE_WESEWVED3              (0x05)
#define MPI3_EVENT_BWOADCAST_PWIMITIVE_WESEWVED4              (0x06)
#define MPI3_EVENT_BWOADCAST_PWIMITIVE_CHANGE0_WESEWVED       (0x07)
#define MPI3_EVENT_BWOADCAST_PWIMITIVE_CHANGE1_WESEWVED       (0x08)
stwuct mpi3_event_data_sas_notify_pwimitive {
	u8                 phy_num;
	u8                 io_unit_powt;
	u8                 wesewved02;
	u8                 pwimitive;
};

#define MPI3_EVENT_NOTIFY_PWIMITIVE_ENABWE_SPINUP         (0x01)
#define MPI3_EVENT_NOTIFY_PWIMITIVE_POWEW_WOSS_EXPECTED   (0x02)
#define MPI3_EVENT_NOTIFY_PWIMITIVE_WESEWVED1             (0x03)
#define MPI3_EVENT_NOTIFY_PWIMITIVE_WESEWVED2             (0x04)
#ifndef MPI3_EVENT_SAS_TOPO_PHY_COUNT
#define MPI3_EVENT_SAS_TOPO_PHY_COUNT           (1)
#endif
stwuct mpi3_event_sas_topo_phy_entwy {
	__we16             attached_dev_handwe;
	u8                 wink_wate;
	u8                 status;
};

#define MPI3_EVENT_SAS_TOPO_WW_CUWWENT_MASK                 (0xf0)
#define MPI3_EVENT_SAS_TOPO_WW_CUWWENT_SHIFT                (4)
#define MPI3_EVENT_SAS_TOPO_WW_PWEV_MASK                    (0x0f)
#define MPI3_EVENT_SAS_TOPO_WW_PWEV_SHIFT                   (0)
#define MPI3_EVENT_SAS_TOPO_WW_UNKNOWN_WINK_WATE            (0x00)
#define MPI3_EVENT_SAS_TOPO_WW_PHY_DISABWED                 (0x01)
#define MPI3_EVENT_SAS_TOPO_WW_NEGOTIATION_FAIWED           (0x02)
#define MPI3_EVENT_SAS_TOPO_WW_SATA_OOB_COMPWETE            (0x03)
#define MPI3_EVENT_SAS_TOPO_WW_POWT_SEWECTOW                (0x04)
#define MPI3_EVENT_SAS_TOPO_WW_SMP_WESET_IN_PWOGWESS        (0x05)
#define MPI3_EVENT_SAS_TOPO_WW_UNSUPPOWTED_PHY              (0x06)
#define MPI3_EVENT_SAS_TOPO_WW_WATE_6_0                     (0x0a)
#define MPI3_EVENT_SAS_TOPO_WW_WATE_12_0                    (0x0b)
#define MPI3_EVENT_SAS_TOPO_WW_WATE_22_5                    (0x0c)
#define MPI3_EVENT_SAS_TOPO_PHY_STATUS_MASK                 (0xc0)
#define MPI3_EVENT_SAS_TOPO_PHY_STATUS_SHIFT                (6)
#define MPI3_EVENT_SAS_TOPO_PHY_STATUS_ACCESSIBWE           (0x00)
#define MPI3_EVENT_SAS_TOPO_PHY_STATUS_NO_EXIST             (0x40)
#define MPI3_EVENT_SAS_TOPO_PHY_STATUS_VACANT               (0x80)
#define MPI3_EVENT_SAS_TOPO_PHY_WC_MASK                     (0x0f)
#define MPI3_EVENT_SAS_TOPO_PHY_WC_TAWG_NOT_WESPONDING      (0x02)
#define MPI3_EVENT_SAS_TOPO_PHY_WC_PHY_CHANGED              (0x03)
#define MPI3_EVENT_SAS_TOPO_PHY_WC_NO_CHANGE                (0x04)
#define MPI3_EVENT_SAS_TOPO_PHY_WC_DEWAY_NOT_WESPONDING     (0x05)
#define MPI3_EVENT_SAS_TOPO_PHY_WC_WESPONDING               (0x06)
stwuct mpi3_event_data_sas_topowogy_change_wist {
	__we16                             encwosuwe_handwe;
	__we16                             expandew_dev_handwe;
	u8                                 num_phys;
	u8                                 wesewved05[3];
	u8                                 num_entwies;
	u8                                 stawt_phy_num;
	u8                                 exp_status;
	u8                                 io_unit_powt;
	stwuct mpi3_event_sas_topo_phy_entwy   phy_entwy[MPI3_EVENT_SAS_TOPO_PHY_COUNT];
};

#define MPI3_EVENT_SAS_TOPO_ES_NO_EXPANDEW              (0x00)
#define MPI3_EVENT_SAS_TOPO_ES_NOT_WESPONDING           (0x02)
#define MPI3_EVENT_SAS_TOPO_ES_WESPONDING               (0x03)
#define MPI3_EVENT_SAS_TOPO_ES_DEWAY_NOT_WESPONDING     (0x04)
stwuct mpi3_event_data_sas_phy_countew {
	__we64             time_stamp;
	__we32             wesewved08;
	u8                 phy_event_code;
	u8                 phy_num;
	__we16             wesewved0e;
	__we32             phy_event_info;
	u8                 countew_type;
	u8                 thweshowd_window;
	u8                 time_units;
	u8                 wesewved17;
	__we32             event_thweshowd;
	__we16             thweshowd_fwags;
	__we16             wesewved1e;
};

stwuct mpi3_event_data_sas_device_disc_eww {
	__we16             dev_handwe;
	u8                 weason_code;
	u8                 io_unit_powt;
	__we32             wesewved04;
	__we64             sas_addwess;
};

#define MPI3_EVENT_SAS_DISC_EWW_WC_SMP_FAIWED          (0x01)
#define MPI3_EVENT_SAS_DISC_EWW_WC_SMP_TIMEOUT         (0x02)
stwuct mpi3_event_data_pcie_enumewation {
	u8                 fwags;
	u8                 weason_code;
	u8                 io_unit_powt;
	u8                 wesewved03;
	__we32             enumewation_status;
};

#define MPI3_EVENT_PCIE_ENUM_FWAGS_DEVICE_CHANGE            (0x02)
#define MPI3_EVENT_PCIE_ENUM_FWAGS_IN_PWOGWESS              (0x01)
#define MPI3_EVENT_PCIE_ENUM_WC_STAWTED                     (0x01)
#define MPI3_EVENT_PCIE_ENUM_WC_COMPWETED                   (0x02)
#define MPI3_EVENT_PCIE_ENUM_ES_MAX_SWITCH_DEPTH_EXCEED     (0x80000000)
#define MPI3_EVENT_PCIE_ENUM_ES_MAX_SWITCHES_EXCEED         (0x40000000)
#define MPI3_EVENT_PCIE_ENUM_ES_MAX_DEVICES_EXCEED          (0x20000000)
#define MPI3_EVENT_PCIE_ENUM_ES_WESOUWCES_EXHAUSTED         (0x10000000)
#ifndef MPI3_EVENT_PCIE_TOPO_POWT_COUNT
#define MPI3_EVENT_PCIE_TOPO_POWT_COUNT         (1)
#endif
stwuct mpi3_event_pcie_topo_powt_entwy {
	__we16             attached_dev_handwe;
	u8                 powt_status;
	u8                 wesewved03;
	u8                 cuwwent_powt_info;
	u8                 wesewved05;
	u8                 pwevious_powt_info;
	u8                 wesewved07;
};

#define MPI3_EVENT_PCIE_TOPO_PS_NOT_WESPONDING          (0x02)
#define MPI3_EVENT_PCIE_TOPO_PS_POWT_CHANGED            (0x03)
#define MPI3_EVENT_PCIE_TOPO_PS_NO_CHANGE               (0x04)
#define MPI3_EVENT_PCIE_TOPO_PS_DEWAY_NOT_WESPONDING    (0x05)
#define MPI3_EVENT_PCIE_TOPO_PS_WESPONDING              (0x06)
#define MPI3_EVENT_PCIE_TOPO_PI_WANES_MASK              (0xf0)
#define MPI3_EVENT_PCIE_TOPO_PI_WANES_UNKNOWN           (0x00)
#define MPI3_EVENT_PCIE_TOPO_PI_WANES_1                 (0x10)
#define MPI3_EVENT_PCIE_TOPO_PI_WANES_2                 (0x20)
#define MPI3_EVENT_PCIE_TOPO_PI_WANES_4                 (0x30)
#define MPI3_EVENT_PCIE_TOPO_PI_WANES_8                 (0x40)
#define MPI3_EVENT_PCIE_TOPO_PI_WANES_16                (0x50)
#define MPI3_EVENT_PCIE_TOPO_PI_WATE_MASK               (0x0f)
#define MPI3_EVENT_PCIE_TOPO_PI_WATE_UNKNOWN            (0x00)
#define MPI3_EVENT_PCIE_TOPO_PI_WATE_DISABWED           (0x01)
#define MPI3_EVENT_PCIE_TOPO_PI_WATE_2_5                (0x02)
#define MPI3_EVENT_PCIE_TOPO_PI_WATE_5_0                (0x03)
#define MPI3_EVENT_PCIE_TOPO_PI_WATE_8_0                (0x04)
#define MPI3_EVENT_PCIE_TOPO_PI_WATE_16_0               (0x05)
#define MPI3_EVENT_PCIE_TOPO_PI_WATE_32_0               (0x06)
stwuct mpi3_event_data_pcie_topowogy_change_wist {
	__we16                                 encwosuwe_handwe;
	__we16                                 switch_dev_handwe;
	u8                                     num_powts;
	u8                                     wesewved05[3];
	u8                                     num_entwies;
	u8                                     stawt_powt_num;
	u8                                     switch_status;
	u8                                     io_unit_powt;
	__we32                                 wesewved0c;
	stwuct mpi3_event_pcie_topo_powt_entwy     powt_entwy[MPI3_EVENT_PCIE_TOPO_POWT_COUNT];
};

#define MPI3_EVENT_PCIE_TOPO_SS_NO_PCIE_SWITCH          (0x00)
#define MPI3_EVENT_PCIE_TOPO_SS_NOT_WESPONDING          (0x02)
#define MPI3_EVENT_PCIE_TOPO_SS_WESPONDING              (0x03)
#define MPI3_EVENT_PCIE_TOPO_SS_DEWAY_NOT_WESPONDING    (0x04)
stwuct mpi3_event_data_pcie_ewwow_thweshowd {
	__we64                                 timestamp;
	u8                                     weason_code;
	u8                                     powt;
	__we16                                 switch_dev_handwe;
	u8                                     ewwow;
	u8                                     action;
	__we16                                 thweshowd_count;
	__we16                                 attached_dev_handwe;
	__we16                                 wesewved12;
	__we32                                 wesewved14;
};

#define MPI3_EVENT_PCI_EWWOW_WC_THWESHOWD_EXCEEDED          (0x00)
#define MPI3_EVENT_PCI_EWWOW_WC_ESCAWATION                  (0x01)
stwuct mpi3_event_data_sas_init_dev_status_change {
	u8                 weason_code;
	u8                 io_unit_powt;
	__we16             dev_handwe;
	__we32             wesewved04;
	__we64             sas_addwess;
};

#define MPI3_EVENT_SAS_INIT_WC_ADDED                (0x01)
#define MPI3_EVENT_SAS_INIT_WC_NOT_WESPONDING       (0x02)
stwuct mpi3_event_data_sas_init_tabwe_ovewfwow {
	__we16             max_init;
	__we16             cuwwent_init;
	__we32             wesewved04;
	__we64             sas_addwess;
};

stwuct mpi3_event_data_hawd_weset_weceived {
	u8                 wesewved00;
	u8                 io_unit_powt;
	__we16             wesewved02;
};

stwuct mpi3_event_data_diag_buffew_status_change {
	u8                 type;
	u8                 weason_code;
	__we16             wesewved02;
	__we32             wesewved04;
};

#define MPI3_EVENT_DIAG_BUFFEW_STATUS_CHANGE_WC_WEWEASED             (0x01)
#define MPI3_EVENT_DIAG_BUFFEW_STATUS_CHANGE_WC_PAUSED               (0x02)
#define MPI3_EVENT_DIAG_BUFFEW_STATUS_CHANGE_WC_WESUMED              (0x03)
#define MPI3_PEW_WOCAWE_FWAGS_NON_BWOCKING_BOOT_EVENT   (0x0200)
#define MPI3_PEW_WOCAWE_FWAGS_BWOCKING_BOOT_EVENT       (0x0100)
#define MPI3_PEW_WOCAWE_FWAGS_PCIE                      (0x0080)
#define MPI3_PEW_WOCAWE_FWAGS_CONFIGUWATION             (0x0040)
#define MPI3_PEW_WOCAWE_FWAGS_CONTWOWEW                 (0x0020)
#define MPI3_PEW_WOCAWE_FWAGS_SAS                       (0x0010)
#define MPI3_PEW_WOCAWE_FWAGS_EPACK                     (0x0008)
#define MPI3_PEW_WOCAWE_FWAGS_ENCWOSUWE                 (0x0004)
#define MPI3_PEW_WOCAWE_FWAGS_PD                        (0x0002)
#define MPI3_PEW_WOCAWE_FWAGS_VD                        (0x0001)
#define MPI3_PEW_CWASS_DEBUG                            (0x00)
#define MPI3_PEW_CWASS_PWOGWESS                         (0x01)
#define MPI3_PEW_CWASS_INFOWMATIONAW                    (0x02)
#define MPI3_PEW_CWASS_WAWNING                          (0x03)
#define MPI3_PEW_CWASS_CWITICAW                         (0x04)
#define MPI3_PEW_CWASS_FATAW                            (0x05)
#define MPI3_PEW_CWASS_FAUWT                            (0x06)
#define MPI3_PEW_CWEAWTYPE_CWEAW                        (0x00)
#define MPI3_PEW_WAITTIME_INFINITE_WAIT                 (0x00)
#define MPI3_PEW_ACTION_GET_SEQNUM                      (0x01)
#define MPI3_PEW_ACTION_MAWK_CWEAW                      (0x02)
#define MPI3_PEW_ACTION_GET_WOG                         (0x03)
#define MPI3_PEW_ACTION_GET_COUNT                       (0x04)
#define MPI3_PEW_ACTION_WAIT                            (0x05)
#define MPI3_PEW_ACTION_ABOWT                           (0x06)
#define MPI3_PEW_ACTION_GET_PWINT_STWINGS               (0x07)
#define MPI3_PEW_ACTION_ACKNOWWEDGE                     (0x08)
#define MPI3_PEW_STATUS_SUCCESS                         (0x00)
#define MPI3_PEW_STATUS_NOT_FOUND                       (0x01)
#define MPI3_PEW_STATUS_ABOWTED                         (0x02)
#define MPI3_PEW_STATUS_NOT_WEADY                       (0x03)
stwuct mpi3_pew_seq {
	__we32                             newest;
	__we32                             owdest;
	__we32                             cweaw;
	__we32                             shutdown;
	__we32                             boot;
	__we32                             wast_acknowwedged;
};

stwuct mpi3_pew_entwy {
	__we64                             time_stamp;
	__we32                             sequence_numbew;
	__we16                             wog_code;
	__we16                             awg_type;
	__we16                             wocawe;
	u8                                 cwass;
	u8                                 fwags;
	u8                                 ext_num;
	u8                                 num_exts;
	u8                                 awg_data_size;
	u8                                 fixed_fowmat_stwings_size;
	__we32                             wesewved18[2];
	__we32                             pew_info[24];
};

#define MPI3_PEW_FWAGS_COMPWETE_WESET_NEEDED                  (0x02)
#define MPI3_PEW_FWAGS_ACK_NEEDED                             (0x01)
stwuct mpi3_pew_wist {
	__we32                             wog_count;
	__we32                             wesewved04;
	stwuct mpi3_pew_entwy                  entwy[1];
};

stwuct mpi3_pew_awg_map {
	u8                                 awg_type;
	u8                                 wength;
	__we16                             stawt_wocation;
};

#define MPI3_PEW_AWG_MAP_AWG_TYPE_APPEND_STWING                (0x00)
#define MPI3_PEW_AWG_MAP_AWG_TYPE_INTEGEW                      (0x01)
#define MPI3_PEW_AWG_MAP_AWG_TYPE_STWING                       (0x02)
#define MPI3_PEW_AWG_MAP_AWG_TYPE_BIT_FIEWD                    (0x03)
stwuct mpi3_pew_pwint_stwing {
	__we16                             wog_code;
	__we16                             stwing_wength;
	u8                                 num_awg_map;
	u8                                 wesewved05[3];
	stwuct mpi3_pew_awg_map                awg_map[1];
};

stwuct mpi3_pew_pwint_stwing_wist {
	__we32                             num_pwint_stwings;
	__we32                             wesiduaw_bytes_wemain;
	__we32                             wesewved08[2];
	stwuct mpi3_pew_pwint_stwing           pwint_stwing[1];
};

#ifndef MPI3_PEW_ACTION_SPECIFIC_MAX
#define MPI3_PEW_ACTION_SPECIFIC_MAX               (1)
#endif
stwuct mpi3_pew_wequest {
	__we16                             host_tag;
	u8                                 ioc_use_onwy02;
	u8                                 function;
	__we16                             ioc_use_onwy04;
	u8                                 ioc_use_onwy06;
	u8                                 msg_fwags;
	__we16                             change_count;
	u8                                 action;
	u8                                 wesewved0b;
	__we32                             action_specific[MPI3_PEW_ACTION_SPECIFIC_MAX];
};

stwuct mpi3_pew_weq_action_get_sequence_numbews {
	__we16                             host_tag;
	u8                                 ioc_use_onwy02;
	u8                                 function;
	__we16                             ioc_use_onwy04;
	u8                                 ioc_use_onwy06;
	u8                                 msg_fwags;
	__we16                             change_count;
	u8                                 action;
	u8                                 wesewved0b;
	__we32                             wesewved0c[5];
	union mpi3_sge_union                  sgw;
};

stwuct mpi3_pew_weq_action_cweaw_wog_mawkew {
	__we16                             host_tag;
	u8                                 ioc_use_onwy02;
	u8                                 function;
	__we16                             ioc_use_onwy04;
	u8                                 ioc_use_onwy06;
	u8                                 msg_fwags;
	__we16                             change_count;
	u8                                 action;
	u8                                 wesewved0b;
	u8                                 cweaw_type;
	u8                                 wesewved0d[3];
};

stwuct mpi3_pew_weq_action_get_wog {
	__we16                             host_tag;
	u8                                 ioc_use_onwy02;
	u8                                 function;
	__we16                             ioc_use_onwy04;
	u8                                 ioc_use_onwy06;
	u8                                 msg_fwags;
	__we16                             change_count;
	u8                                 action;
	u8                                 wesewved0b;
	__we32                             stawting_sequence_numbew;
	__we16                             wocawe;
	u8                                 cwass;
	u8                                 wesewved13;
	__we32                             wesewved14[3];
	union mpi3_sge_union                  sgw;
};

stwuct mpi3_pew_weq_action_get_count {
	__we16                             host_tag;
	u8                                 ioc_use_onwy02;
	u8                                 function;
	__we16                             ioc_use_onwy04;
	u8                                 ioc_use_onwy06;
	u8                                 msg_fwags;
	__we16                             change_count;
	u8                                 action;
	u8                                 wesewved0b;
	__we32                             stawting_sequence_numbew;
	__we16                             wocawe;
	u8                                 cwass;
	u8                                 wesewved13;
	__we32                             wesewved14[3];
	union mpi3_sge_union                  sgw;
};

stwuct mpi3_pew_weq_action_wait {
	__we16                             host_tag;
	u8                                 ioc_use_onwy02;
	u8                                 function;
	__we16                             ioc_use_onwy04;
	u8                                 ioc_use_onwy06;
	u8                                 msg_fwags;
	__we16                             change_count;
	u8                                 action;
	u8                                 wesewved0b;
	__we32                             stawting_sequence_numbew;
	__we16                             wocawe;
	u8                                 cwass;
	u8                                 wesewved13;
	__we16                             wait_time;
	__we16                             wesewved16;
	__we32                             wesewved18[2];
};

stwuct mpi3_pew_weq_action_abowt {
	__we16                             host_tag;
	u8                                 ioc_use_onwy02;
	u8                                 function;
	__we16                             ioc_use_onwy04;
	u8                                 ioc_use_onwy06;
	u8                                 msg_fwags;
	__we16                             change_count;
	u8                                 action;
	u8                                 wesewved0b;
	__we32                             wesewved0c;
	__we16                             abowt_host_tag;
	__we16                             wesewved12;
	__we32                             wesewved14;
};

stwuct mpi3_pew_weq_action_get_pwint_stwings {
	__we16                             host_tag;
	u8                                 ioc_use_onwy02;
	u8                                 function;
	__we16                             ioc_use_onwy04;
	u8                                 ioc_use_onwy06;
	u8                                 msg_fwags;
	__we16                             change_count;
	u8                                 action;
	u8                                 wesewved0b;
	__we32                             wesewved0c;
	__we16                             stawt_wog_code;
	__we16                             wesewved12;
	__we32                             wesewved14[3];
	union mpi3_sge_union                  sgw;
};

stwuct mpi3_pew_weq_action_acknowwedge {
	__we16                             host_tag;
	u8                                 ioc_use_onwy02;
	u8                                 function;
	__we16                             ioc_use_onwy04;
	u8                                 ioc_use_onwy06;
	u8                                 msg_fwags;
	__we16                             change_count;
	u8                                 action;
	u8                                 wesewved0b;
	__we32                             sequence_numbew;
	__we32                             wesewved10;
};

#define MPI3_PEWACKNOWWEDGE_MSGFWAGS_SAFE_MODE_EXIT_MASK                     (0x03)
#define MPI3_PEWACKNOWWEDGE_MSGFWAGS_SAFE_MODE_EXIT_NO_GUIDANCE              (0x00)
#define MPI3_PEWACKNOWWEDGE_MSGFWAGS_SAFE_MODE_EXIT_CONTINUE_OP              (0x01)
#define MPI3_PEWACKNOWWEDGE_MSGFWAGS_SAFE_MODE_EXIT_TWANSITION_TO_FAUWT      (0x02)
stwuct mpi3_pew_wepwy {
	__we16                             host_tag;
	u8                                 ioc_use_onwy02;
	u8                                 function;
	__we16                             ioc_use_onwy04;
	u8                                 ioc_use_onwy06;
	u8                                 msg_fwags;
	__we16                             ioc_use_onwy08;
	__we16                             ioc_status;
	__we32                             ioc_wog_info;
	u8                                 action;
	u8                                 wesewved11;
	__we16                             wesewved12;
	__we16                             pe_wog_status;
	__we16                             wesewved16;
	__we32                             twansfew_wength;
};

stwuct mpi3_ci_downwoad_wequest {
	__we16                             host_tag;
	u8                                 ioc_use_onwy02;
	u8                                 function;
	__we16                             ioc_use_onwy04;
	u8                                 ioc_use_onwy06;
	u8                                 msg_fwags;
	__we16                             change_count;
	u8                                 action;
	u8                                 wesewved0b;
	__we32                             signatuwe1;
	__we32                             totaw_image_size;
	__we32                             image_offset;
	__we32                             segment_size;
	__we32                             wesewved1c;
	union mpi3_sge_union                  sgw;
};

#define MPI3_CI_DOWNWOAD_MSGFWAGS_WAST_SEGMENT                 (0x80)
#define MPI3_CI_DOWNWOAD_MSGFWAGS_FOWCE_FMC_ENABWE             (0x40)
#define MPI3_CI_DOWNWOAD_MSGFWAGS_SIGNED_NVDATA                (0x20)
#define MPI3_CI_DOWNWOAD_MSGFWAGS_WWITE_CACHE_FWUSH_MASK       (0x03)
#define MPI3_CI_DOWNWOAD_MSGFWAGS_WWITE_CACHE_FWUSH_FAST       (0x00)
#define MPI3_CI_DOWNWOAD_MSGFWAGS_WWITE_CACHE_FWUSH_MEDIUM     (0x01)
#define MPI3_CI_DOWNWOAD_MSGFWAGS_WWITE_CACHE_FWUSH_SWOW       (0x02)
#define MPI3_CI_DOWNWOAD_ACTION_DOWNWOAD                       (0x01)
#define MPI3_CI_DOWNWOAD_ACTION_ONWINE_ACTIVATION              (0x02)
#define MPI3_CI_DOWNWOAD_ACTION_OFFWINE_ACTIVATION             (0x03)
#define MPI3_CI_DOWNWOAD_ACTION_GET_STATUS                     (0x04)
#define MPI3_CI_DOWNWOAD_ACTION_CANCEW_OFFWINE_ACTIVATION      (0x05)
stwuct mpi3_ci_downwoad_wepwy {
	__we16                             host_tag;
	u8                                 ioc_use_onwy02;
	u8                                 function;
	__we16                             ioc_use_onwy04;
	u8                                 ioc_use_onwy06;
	u8                                 msg_fwags;
	__we16                             ioc_use_onwy08;
	__we16                             ioc_status;
	__we32                             ioc_wog_info;
	u8                                 fwags;
	u8                                 cache_diwty;
	u8                                 pending_count;
	u8                                 wesewved13;
};

#define MPI3_CI_DOWNWOAD_FWAGS_DOWNWOAD_IN_PWOGWESS                  (0x80)
#define MPI3_CI_DOWNWOAD_FWAGS_ACTIVATION_FAIWUWE                    (0x40)
#define MPI3_CI_DOWNWOAD_FWAGS_OFFWINE_ACTIVATION_WEQUIWED           (0x20)
#define MPI3_CI_DOWNWOAD_FWAGS_KEY_UPDATE_PENDING                    (0x10)
#define MPI3_CI_DOWNWOAD_FWAGS_ACTIVATION_STATUS_MASK                (0x0e)
#define MPI3_CI_DOWNWOAD_FWAGS_ACTIVATION_STATUS_NOT_NEEDED          (0x00)
#define MPI3_CI_DOWNWOAD_FWAGS_ACTIVATION_STATUS_AWAITING            (0x02)
#define MPI3_CI_DOWNWOAD_FWAGS_ACTIVATION_STATUS_ONWINE_PENDING      (0x04)
#define MPI3_CI_DOWNWOAD_FWAGS_ACTIVATION_STATUS_OFFWINE_PENDING     (0x06)
#define MPI3_CI_DOWNWOAD_FWAGS_COMPATIBWE                            (0x01)
stwuct mpi3_ci_upwoad_wequest {
	__we16                             host_tag;
	u8                                 ioc_use_onwy02;
	u8                                 function;
	__we16                             ioc_use_onwy04;
	u8                                 ioc_use_onwy06;
	u8                                 msg_fwags;
	__we16                             change_count;
	__we16                             wesewved0a;
	__we32                             signatuwe1;
	__we32                             wesewved10;
	__we32                             image_offset;
	__we32                             segment_size;
	__we32                             wesewved1c;
	union mpi3_sge_union                  sgw;
};

#define MPI3_CI_UPWOAD_MSGFWAGS_WOCATION_MASK                        (0x01)
#define MPI3_CI_UPWOAD_MSGFWAGS_WOCATION_PWIMAWY                     (0x00)
#define MPI3_CI_UPWOAD_MSGFWAGS_WOCATION_SECONDAWY                   (0x01)
#define MPI3_CI_UPWOAD_MSGFWAGS_FOWMAT_MASK                          (0x02)
#define MPI3_CI_UPWOAD_MSGFWAGS_FOWMAT_FWASH                         (0x00)
#define MPI3_CI_UPWOAD_MSGFWAGS_FOWMAT_EXECUTABWE                    (0x02)
#define MPI3_CTWW_OP_FOWCE_FUWW_DISCOVEWY                            (0x01)
#define MPI3_CTWW_OP_WOOKUP_MAPPING                                  (0x02)
#define MPI3_CTWW_OP_UPDATE_TIMESTAMP                                (0x04)
#define MPI3_CTWW_OP_GET_TIMESTAMP                                   (0x05)
#define MPI3_CTWW_OP_GET_IOC_CHANGE_COUNT                            (0x06)
#define MPI3_CTWW_OP_CHANGE_PWOFIWE                                  (0x07)
#define MPI3_CTWW_OP_WEMOVE_DEVICE                                   (0x10)
#define MPI3_CTWW_OP_CWOSE_PEWSISTENT_CONNECTION                     (0x11)
#define MPI3_CTWW_OP_HIDDEN_ACK                                      (0x12)
#define MPI3_CTWW_OP_CWEAW_DEVICE_COUNTEWS                           (0x13)
#define MPI3_CTWW_OP_SEND_SAS_PWIMITIVE                              (0x20)
#define MPI3_CTWW_OP_SAS_PHY_CONTWOW                                 (0x21)
#define MPI3_CTWW_OP_WEAD_INTEWNAW_BUS                               (0x23)
#define MPI3_CTWW_OP_WWITE_INTEWNAW_BUS                              (0x24)
#define MPI3_CTWW_OP_PCIE_WINK_CONTWOW                               (0x30)
#define MPI3_CTWW_OP_WOOKUP_MAPPING_PAWAM8_WOOKUP_METHOD_INDEX       (0x00)
#define MPI3_CTWW_OP_UPDATE_TIMESTAMP_PAWAM64_TIMESTAMP_INDEX        (0x00)
#define MPI3_CTWW_OP_CHANGE_PWOFIWE_PAWAM8_PWOFIWE_ID_INDEX          (0x00)
#define MPI3_CTWW_OP_WEMOVE_DEVICE_PAWAM16_DEVHANDWE_INDEX           (0x00)
#define MPI3_CTWW_OP_CWOSE_PEWSIST_CONN_PAWAM16_DEVHANDWE_INDEX      (0x00)
#define MPI3_CTWW_OP_HIDDEN_ACK_PAWAM16_DEVHANDWE_INDEX              (0x00)
#define MPI3_CTWW_OP_CWEAW_DEVICE_COUNTEWS_PAWAM16_DEVHANDWE_INDEX   (0x00)
#define MPI3_CTWW_OP_SEND_SAS_PWIM_PAWAM8_PHY_INDEX                  (0x00)
#define MPI3_CTWW_OP_SEND_SAS_PWIM_PAWAM8_PWIMSEQ_INDEX              (0x01)
#define MPI3_CTWW_OP_SEND_SAS_PWIM_PAWAM32_PWIMITIVE_INDEX           (0x00)
#define MPI3_CTWW_OP_SAS_PHY_CONTWOW_PAWAM8_ACTION_INDEX             (0x00)
#define MPI3_CTWW_OP_SAS_PHY_CONTWOW_PAWAM8_PHY_INDEX                (0x01)
#define MPI3_CTWW_OP_WEAD_INTEWNAW_BUS_PAWAM64_ADDWESS_INDEX         (0x00)
#define MPI3_CTWW_OP_WWITE_INTEWNAW_BUS_PAWAM64_ADDWESS_INDEX        (0x00)
#define MPI3_CTWW_OP_WWITE_INTEWNAW_BUS_PAWAM32_VAWUE_INDEX          (0x00)
#define MPI3_CTWW_OP_PCIE_WINK_CONTWOW_PAWAM8_ACTION_INDEX           (0x00)
#define MPI3_CTWW_OP_PCIE_WINK_CONTWOW_PAWAM8_WINK_INDEX             (0x01)
#define MPI3_CTWW_WOOKUP_METHOD_WWID_ADDWESS                         (0x01)
#define MPI3_CTWW_WOOKUP_METHOD_ENCWOSUWE_SWOT                       (0x02)
#define MPI3_CTWW_WOOKUP_METHOD_SAS_DEVICE_NAME                      (0x03)
#define MPI3_CTWW_WOOKUP_METHOD_PEWSISTENT_ID                        (0x04)
#define MPI3_CTWW_WOOKUP_METHOD_WWIDADDW_PAWAM16_DEVH_INDEX             (0)
#define MPI3_CTWW_WOOKUP_METHOD_WWIDADDW_PAWAM64_WWID_INDEX             (0)
#define MPI3_CTWW_WOOKUP_METHOD_ENCWSWOT_PAWAM16_SWOTNUM_INDEX          (0)
#define MPI3_CTWW_WOOKUP_METHOD_ENCWSWOT_PAWAM64_ENCWOSUWEWID_INDEX     (0)
#define MPI3_CTWW_WOOKUP_METHOD_SASDEVNAME_PAWAM16_DEVH_INDEX           (0)
#define MPI3_CTWW_WOOKUP_METHOD_SASDEVNAME_PAWAM64_DEVNAME_INDEX        (0)
#define MPI3_CTWW_WOOKUP_METHOD_PEWSISTID_PAWAM16_DEVH_INDEX            (0)
#define MPI3_CTWW_WOOKUP_METHOD_PEWSISTID_PAWAM16_PEWSISTENT_ID_INDEX   (1)
#define MPI3_CTWW_WOOKUP_METHOD_VAWUE16_DEVH_INDEX                      (0)
#define MPI3_CTWW_GET_TIMESTAMP_VAWUE64_TIMESTAMP_INDEX                 (0)
#define MPI3_CTWW_GET_IOC_CHANGE_COUNT_VAWUE16_CHANGECOUNT_INDEX        (0)
#define MPI3_CTWW_WEAD_INTEWNAW_BUS_VAWUE32_VAWUE_INDEX                 (0)
#define MPI3_CTWW_PWIMFWAGS_SINGWE                                   (0x01)
#define MPI3_CTWW_PWIMFWAGS_TWIPWE                                   (0x03)
#define MPI3_CTWW_PWIMFWAGS_WEDUNDANT                                (0x06)
#define MPI3_CTWW_ACTION_NOP                                         (0x00)
#define MPI3_CTWW_ACTION_WINK_WESET                                  (0x01)
#define MPI3_CTWW_ACTION_HAWD_WESET                                  (0x02)
#define MPI3_CTWW_ACTION_CWEAW_EWWOW_WOG                             (0x05)
stwuct mpi3_iounit_contwow_wequest {
	__we16                             host_tag;
	u8                                 ioc_use_onwy02;
	u8                                 function;
	__we16                             ioc_use_onwy04;
	u8                                 ioc_use_onwy06;
	u8                                 msg_fwags;
	__we16                             change_count;
	u8                                 wesewved0a;
	u8                                 opewation;
	__we32                             wesewved0c;
	__we64                             pawam64[2];
	__we32                             pawam32[4];
	__we16                             pawam16[4];
	u8                                 pawam8[8];
};

stwuct mpi3_iounit_contwow_wepwy {
	__we16                             host_tag;
	u8                                 ioc_use_onwy02;
	u8                                 function;
	__we16                             ioc_use_onwy04;
	u8                                 ioc_use_onwy06;
	u8                                 msg_fwags;
	__we16                             ioc_use_onwy08;
	__we16                             ioc_status;
	__we32                             ioc_wog_info;
	__we64                             vawue64[2];
	__we32                             vawue32[4];
	__we16                             vawue16[4];
	u8                                 vawue8[8];
};
#endif
