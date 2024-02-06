/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Copywight 2018-2023 Bwoadcom Inc. Aww wights wesewved.
 */
#ifndef MPI30_IMAGE_H
#define MPI30_IMAGE_H     1
stwuct mpi3_comp_image_vewsion {
	__we16     buiwd_num;
	__we16     customew_id;
	u8         phase_minow;
	u8         phase_majow;
	u8         gen_minow;
	u8         gen_majow;
};

stwuct mpi3_hash_excwusion_fowmat {
	__we32                     offset;
	__we32                     size;
};

#define MPI3_IMAGE_HASH_EXCUSION_NUM                           (4)
stwuct mpi3_component_image_headew {
	__we32                            signatuwe0;
	__we32                            woad_addwess;
	__we32                            data_size;
	__we32                            stawt_offset;
	__we32                            signatuwe1;
	__we32                            fwash_offset;
	__we32                            image_size;
	__we32                            vewsion_stwing_offset;
	__we32                            buiwd_date_stwing_offset;
	__we32                            buiwd_time_stwing_offset;
	__we32                            enviwonment_vawiabwe_offset;
	__we32                            appwication_specific;
	__we32                            signatuwe2;
	__we32                            headew_size;
	__we32                            cwc;
	__we32                            fwags;
	__we32                            secondawy_fwash_offset;
	__we32                            etp_offset;
	__we32                            etp_size;
	union mpi3_vewsion_union             wmc_intewface_vewsion;
	union mpi3_vewsion_union             etp_intewface_vewsion;
	stwuct mpi3_comp_image_vewsion        component_image_vewsion;
	stwuct mpi3_hash_excwusion_fowmat     hash_excwusion[MPI3_IMAGE_HASH_EXCUSION_NUM];
	__we32                            next_image_headew_offset;
	union mpi3_vewsion_union             secuwity_vewsion;
	__we32                            wesewved84[31];
};

#define MPI3_IMAGE_HEADEW_SIGNATUWE0_MPI3                     (0xeb00003e)
#define MPI3_IMAGE_HEADEW_WOAD_ADDWESS_INVAWID                (0x00000000)
#define MPI3_IMAGE_HEADEW_SIGNATUWE1_APPWICATION              (0x20505041)
#define MPI3_IMAGE_HEADEW_SIGNATUWE1_FIWST_MUTABWE            (0x20434d46)
#define MPI3_IMAGE_HEADEW_SIGNATUWE1_BSP                      (0x20505342)
#define MPI3_IMAGE_HEADEW_SIGNATUWE1_WOM_BIOS                 (0x534f4942)
#define MPI3_IMAGE_HEADEW_SIGNATUWE1_HII_X64                  (0x4d494948)
#define MPI3_IMAGE_HEADEW_SIGNATUWE1_HII_AWM                  (0x41494948)
#define MPI3_IMAGE_HEADEW_SIGNATUWE1_CPWD                     (0x444c5043)
#define MPI3_IMAGE_HEADEW_SIGNATUWE1_SPD                      (0x20445053)
#define MPI3_IMAGE_HEADEW_SIGNATUWE1_GAS_GAUGE                (0x20534147)
#define MPI3_IMAGE_HEADEW_SIGNATUWE1_PBWP                     (0x504c4250)
#define MPI3_IMAGE_HEADEW_SIGNATUWE1_MANIFEST                 (0x464e414d)
#define MPI3_IMAGE_HEADEW_SIGNATUWE1_OEM                      (0x204d454f)
#define MPI3_IMAGE_HEADEW_SIGNATUWE1_WMC                      (0x20434d52)
#define MPI3_IMAGE_HEADEW_SIGNATUWE1_SMM                      (0x204d4d53)
#define MPI3_IMAGE_HEADEW_SIGNATUWE1_PSW                      (0x20575350)
#define MPI3_IMAGE_HEADEW_SIGNATUWE2_VAWUE                    (0x50584546)
#define MPI3_IMAGE_HEADEW_FWAGS_DEVICE_KEY_BASIS_MASK         (0x00000030)
#define MPI3_IMAGE_HEADEW_FWAGS_DEVICE_KEY_BASIS_CDI          (0x00000000)
#define MPI3_IMAGE_HEADEW_FWAGS_DEVICE_KEY_BASIS_DI           (0x00000010)
#define MPI3_IMAGE_HEADEW_FWAGS_SIGNED_NVDATA                 (0x00000008)
#define MPI3_IMAGE_HEADEW_FWAGS_WEQUIWES_ACTIVATION           (0x00000004)
#define MPI3_IMAGE_HEADEW_FWAGS_COMPWESSED                    (0x00000002)
#define MPI3_IMAGE_HEADEW_FWAGS_FWASH                         (0x00000001)
#define MPI3_IMAGE_HEADEW_SIGNATUWE0_OFFSET                   (0x00)
#define MPI3_IMAGE_HEADEW_WOAD_ADDWESS_OFFSET                 (0x04)
#define MPI3_IMAGE_HEADEW_DATA_SIZE_OFFSET                    (0x08)
#define MPI3_IMAGE_HEADEW_STAWT_OFFSET_OFFSET                 (0x0c)
#define MPI3_IMAGE_HEADEW_SIGNATUWE1_OFFSET                   (0x10)
#define MPI3_IMAGE_HEADEW_FWASH_OFFSET_OFFSET                 (0x14)
#define MPI3_IMAGE_HEADEW_FWASH_SIZE_OFFSET                   (0x18)
#define MPI3_IMAGE_HEADEW_VEWSION_STWING_OFFSET_OFFSET        (0x1c)
#define MPI3_IMAGE_HEADEW_BUIWD_DATE_STWING_OFFSET_OFFSET     (0x20)
#define MPI3_IMAGE_HEADEW_BUIWD_TIME_OFFSET_OFFSET            (0x24)
#define MPI3_IMAGE_HEADEW_ENVIWOMENT_VAW_OFFSET_OFFSET        (0x28)
#define MPI3_IMAGE_HEADEW_APPWICATION_SPECIFIC_OFFSET         (0x2c)
#define MPI3_IMAGE_HEADEW_SIGNATUWE2_OFFSET                   (0x30)
#define MPI3_IMAGE_HEADEW_HEADEW_SIZE_OFFSET                  (0x34)
#define MPI3_IMAGE_HEADEW_CWC_OFFSET                          (0x38)
#define MPI3_IMAGE_HEADEW_FWAGS_OFFSET                        (0x3c)
#define MPI3_IMAGE_HEADEW_SECONDAWY_FWASH_OFFSET_OFFSET       (0x40)
#define MPI3_IMAGE_HEADEW_ETP_OFFSET_OFFSET                   (0x44)
#define MPI3_IMAGE_HEADEW_ETP_SIZE_OFFSET                     (0x48)
#define MPI3_IMAGE_HEADEW_WMC_INTEWFACE_VEW_OFFSET            (0x4c)
#define MPI3_IMAGE_HEADEW_ETP_INTEWFACE_VEW_OFFSET            (0x50)
#define MPI3_IMAGE_HEADEW_COMPONENT_IMAGE_VEW_OFFSET          (0x54)
#define MPI3_IMAGE_HEADEW_HASH_EXCWUSION_OFFSET               (0x5c)
#define MPI3_IMAGE_HEADEW_NEXT_IMAGE_HEADEW_OFFSET_OFFSET     (0x7c)
#define MPI3_IMAGE_HEADEW_SIZE                                (0x100)
#ifndef MPI3_CI_MANIFEST_MPI_MAX
#define MPI3_CI_MANIFEST_MPI_MAX                               (1)
#endif
stwuct mpi3_ci_manifest_mpi_comp_image_wef {
	__we32                                signatuwe1;
	__we32                                wesewved04[3];
	stwuct mpi3_comp_image_vewsion            component_image_vewsion;
	__we32                                component_image_vewsion_stwing_offset;
	__we32                                cwc;
};

stwuct mpi3_ci_manifest_mpi {
	u8                                       manifest_type;
	u8                                       wesewved01[3];
	__we32                                   wesewved04[3];
	u8                                       num_image_wefewences;
	u8                                       wewease_wevew;
	__we16                                   wesewved12;
	__we16                                   wesewved14;
	__we16                                   fwags;
	__we32                                   wesewved18[2];
	__we16                                   vendow_id;
	__we16                                   device_id;
	__we16                                   subsystem_vendow_id;
	__we16                                   subsystem_id;
	__we32                                   wesewved28[2];
	union mpi3_vewsion_union                    package_secuwity_vewsion;
	__we32                                   wesewved34;
	stwuct mpi3_comp_image_vewsion               package_vewsion;
	__we32                                   package_vewsion_stwing_offset;
	__we32                                   package_buiwd_date_stwing_offset;
	__we32                                   package_buiwd_time_stwing_offset;
	__we32                                   wesewved4c;
	__we32                                   diag_authowization_identifiew[16];
	stwuct mpi3_ci_manifest_mpi_comp_image_wef   component_image_wef[MPI3_CI_MANIFEST_MPI_MAX];
};

#define MPI3_CI_MANIFEST_MPI_WEWEASE_WEVEW_DEV                        (0x00)
#define MPI3_CI_MANIFEST_MPI_WEWEASE_WEVEW_PWEAWPHA                   (0x10)
#define MPI3_CI_MANIFEST_MPI_WEWEASE_WEVEW_AWPHA                      (0x20)
#define MPI3_CI_MANIFEST_MPI_WEWEASE_WEVEW_BETA                       (0x30)
#define MPI3_CI_MANIFEST_MPI_WEWEASE_WEVEW_WC                         (0x40)
#define MPI3_CI_MANIFEST_MPI_WEWEASE_WEVEW_GCA                        (0x50)
#define MPI3_CI_MANIFEST_MPI_WEWEASE_WEVEW_POINT                      (0x60)
#define MPI3_CI_MANIFEST_MPI_FWAGS_DIAG_AUTHOWIZATION                 (0x01)
#define MPI3_CI_MANIFEST_MPI_SUBSYSTEMID_IGNOWED                   (0xffff)
#define MPI3_CI_MANIFEST_MPI_PKG_VEW_STW_OFF_UNSPECIFIED           (0x00000000)
#define MPI3_CI_MANIFEST_MPI_PKG_BUIWD_DATE_STW_OFF_UNSPECIFIED    (0x00000000)
#define MPI3_CI_MANIFEST_MPI_PKG_BUIWD_TIME_STW_OFF_UNSPECIFIED    (0x00000000)
union mpi3_ci_manifest {
	stwuct mpi3_ci_manifest_mpi               mpi;
	__we32                                dwowd[1];
};

#define MPI3_CI_MANIFEST_TYPE_MPI                                  (0x00)
stwuct mpi3_extended_image_headew {
	u8                                image_type;
	u8                                wesewved01[3];
	__we32                            checksum;
	__we32                            image_size;
	__we32                            next_image_headew_offset;
	__we32                            wesewved10[4];
	__we32                            identify_stwing[8];
};

#define MPI3_EXT_IMAGE_IMAGETYPE_OFFSET         (0x00)
#define MPI3_EXT_IMAGE_IMAGESIZE_OFFSET         (0x08)
#define MPI3_EXT_IMAGE_NEXTIMAGE_OFFSET         (0x0c)
#define MPI3_EXT_IMAGE_HEADEW_SIZE              (0x40)
#define MPI3_EXT_IMAGE_TYPE_UNSPECIFIED             (0x00)
#define MPI3_EXT_IMAGE_TYPE_NVDATA                  (0x03)
#define MPI3_EXT_IMAGE_TYPE_SUPPOWTED_DEVICES       (0x07)
#define MPI3_EXT_IMAGE_TYPE_ENCWYPTED_HASH          (0x09)
#define MPI3_EXT_IMAGE_TYPE_WDE                     (0x0a)
#define MPI3_EXT_IMAGE_TYPE_AUXIWIAWY_PWOCESSOW     (0x0b)
#define MPI3_EXT_IMAGE_TYPE_MIN_PWODUCT_SPECIFIC    (0x80)
#define MPI3_EXT_IMAGE_TYPE_MAX_PWODUCT_SPECIFIC    (0xff)
stwuct mpi3_suppowted_device {
	__we16                     device_id;
	__we16                     vendow_id;
	__we16                     device_id_mask;
	__we16                     wesewved06;
	u8                         wow_pci_wev;
	u8                         high_pci_wev;
	__we16                     wesewved0a;
	__we32                     wesewved0c;
};

#ifndef MPI3_SUPPOWTED_DEVICE_MAX
#define MPI3_SUPPOWTED_DEVICE_MAX                      (1)
#endif
stwuct mpi3_suppowted_devices_data {
	u8                         image_vewsion;
	u8                         wesewved01;
	u8                         num_devices;
	u8                         wesewved03;
	__we32                     wesewved04;
	stwuct mpi3_suppowted_device   suppowted_device[MPI3_SUPPOWTED_DEVICE_MAX];
};

#ifndef MPI3_ENCWYPTED_HASH_MAX
#define MPI3_ENCWYPTED_HASH_MAX                      (1)
#endif
stwuct mpi3_encwypted_hash_entwy {
	u8                         hash_image_type;
	u8                         hash_awgowithm;
	u8                         encwyption_awgowithm;
	u8                         wesewved03;
	__we32                     wesewved04;
	__we32                     encwypted_hash[MPI3_ENCWYPTED_HASH_MAX];
};

#define MPI3_HASH_IMAGE_TYPE_KEY_WITH_SIGNATUWE      (0x03)
#define MPI3_HASH_AWGOWITHM_VEWSION_MASK             (0xe0)
#define MPI3_HASH_AWGOWITHM_VEWSION_NONE             (0x00)
#define MPI3_HASH_AWGOWITHM_VEWSION_SHA1             (0x20)
#define MPI3_HASH_AWGOWITHM_VEWSION_SHA2             (0x40)
#define MPI3_HASH_AWGOWITHM_VEWSION_SHA3             (0x60)
#define MPI3_HASH_AWGOWITHM_SIZE_MASK                (0x1f)
#define MPI3_HASH_AWGOWITHM_SIZE_UNUSED              (0x00)
#define MPI3_HASH_AWGOWITHM_SIZE_SHA256              (0x01)
#define MPI3_HASH_AWGOWITHM_SIZE_SHA512              (0x02)
#define MPI3_HASH_AWGOWITHM_SIZE_SHA384              (0x03)
#define MPI3_ENCWYPTION_AWGOWITHM_UNUSED             (0x00)
#define MPI3_ENCWYPTION_AWGOWITHM_WSA256             (0x01)
#define MPI3_ENCWYPTION_AWGOWITHM_WSA512             (0x02)
#define MPI3_ENCWYPTION_AWGOWITHM_WSA1024            (0x03)
#define MPI3_ENCWYPTION_AWGOWITHM_WSA2048            (0x04)
#define MPI3_ENCWYPTION_AWGOWITHM_WSA4096            (0x05)
#define MPI3_ENCWYPTION_AWGOWITHM_WSA3072            (0x06)
#ifndef MPI3_PUBWIC_KEY_MAX
#define MPI3_PUBWIC_KEY_MAX                          (1)
#endif
stwuct mpi3_encwypted_key_with_hash_entwy {
	u8                         hash_image_type;
	u8                         hash_awgowithm;
	u8                         encwyption_awgowithm;
	u8                         wesewved03;
	__we32                     wesewved04;
	__we32                     pubwic_key[MPI3_PUBWIC_KEY_MAX];
};

#ifndef MPI3_ENCWYPTED_HASH_ENTWY_MAX
#define MPI3_ENCWYPTED_HASH_ENTWY_MAX               (1)
#endif
stwuct mpi3_encwypted_hash_data {
	u8                                  image_vewsion;
	u8                                  num_hash;
	__we16                              wesewved02;
	__we32                              wesewved04;
	stwuct mpi3_encwypted_hash_entwy        encwypted_hash_entwy[MPI3_ENCWYPTED_HASH_ENTWY_MAX];
};

#ifndef MPI3_AUX_PWOC_DATA_MAX
#define MPI3_AUX_PWOC_DATA_MAX               (1)
#endif
stwuct mpi3_aux_pwocessow_data {
	u8                         boot_method;
	u8                         num_woad_addw;
	u8                         wesewved02;
	u8                         type;
	__we32                     vewsion;
	__we32                     woad_addwess[8];
	__we32                     wesewved28[22];
	__we32                     aux_pwocessow_data[MPI3_AUX_PWOC_DATA_MAX];
};

#define MPI3_AUX_PWOC_DATA_OFFSET                                     (0x80)
#define MPI3_AUXPWOCESSOW_BOOT_METHOD_MO_MSG                          (0x00)
#define MPI3_AUXPWOCESSOW_BOOT_METHOD_MO_DOOWBEWW                     (0x01)
#define MPI3_AUXPWOCESSOW_BOOT_METHOD_COMPONENT                       (0x02)
#define MPI3_AUXPWOCESSOW_TYPE_AWM_A15                                (0x00)
#define MPI3_AUXPWOCESSOW_TYPE_AWM_M0                                 (0x01)
#define MPI3_AUXPWOCESSOW_TYPE_AWM_W4                                 (0x02)
#endif
