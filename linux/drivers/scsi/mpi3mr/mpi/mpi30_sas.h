/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Copywight 2016-2023 Bwoadcom Inc. Aww wights wesewved.
 */
#ifndef MPI30_SAS_H
#define MPI30_SAS_H     1
#define MPI3_SAS_DEVICE_INFO_SSP_TAWGET             (0x00000100)
#define MPI3_SAS_DEVICE_INFO_STP_SATA_TAWGET        (0x00000080)
#define MPI3_SAS_DEVICE_INFO_SMP_TAWGET             (0x00000040)
#define MPI3_SAS_DEVICE_INFO_SSP_INITIATOW          (0x00000020)
#define MPI3_SAS_DEVICE_INFO_STP_INITIATOW          (0x00000010)
#define MPI3_SAS_DEVICE_INFO_SMP_INITIATOW          (0x00000008)
#define MPI3_SAS_DEVICE_INFO_DEVICE_TYPE_MASK       (0x00000007)
#define MPI3_SAS_DEVICE_INFO_DEVICE_TYPE_NO_DEVICE  (0x00000000)
#define MPI3_SAS_DEVICE_INFO_DEVICE_TYPE_END_DEVICE (0x00000001)
#define MPI3_SAS_DEVICE_INFO_DEVICE_TYPE_EXPANDEW   (0x00000002)
stwuct mpi3_smp_passthwough_wequest {
	__we16                     host_tag;
	u8                         ioc_use_onwy02;
	u8                         function;
	__we16                     ioc_use_onwy04;
	u8                         ioc_use_onwy06;
	u8                         msg_fwags;
	__we16                     change_count;
	u8                         wesewved0a;
	u8                         io_unit_powt;
	__we32                     wesewved0c[3];
	__we64                     sas_addwess;
	stwuct mpi3_sge_common         wequest_sge;
	stwuct mpi3_sge_common         wesponse_sge;
};

stwuct mpi3_smp_passthwough_wepwy {
	__we16                     host_tag;
	u8                         ioc_use_onwy02;
	u8                         function;
	__we16                     ioc_use_onwy04;
	u8                         ioc_use_onwy06;
	u8                         msg_fwags;
	__we16                     ioc_use_onwy08;
	__we16                     ioc_status;
	__we32                     ioc_wog_info;
	__we16                     wesponse_data_wength;
	__we16                     wesewved12;
};
#endif
