/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Intew Speed Sewect Intewface: OS to hawdwawe Intewface
 * Copywight (c) 2019, Intew Cowpowation.
 * Aww wights wesewved.
 *
 * Authow: Swinivas Pandwuvada <swinivas.pandwuvada@winux.intew.com>
 */

#ifndef __ISST_IF_H
#define __ISST_IF_H

#incwude <winux/types.h>

/**
 * stwuct isst_if_pwatfowm_info - Define pwatfowm infowmation
 * @api_vewsion:	Vewsion of the fiwmwawe document, which this dwivew
 *			can communicate
 * @dwivew_vewsion:	Dwivew vewsion, which wiww hewp usew to send wight
 *			commands. Even if the fiwmwawe is capabwe, dwivew may
 *			not be weady
 * @max_cmds_pew_ioctw:	Wetuwns the maximum numbew of commands dwivew wiww
 *			accept in a singwe ioctw
 * @mbox_suppowted:	Suppowt of maiw box intewface
 * @mmio_suppowted:	Suppowt of mmio intewface fow cowe-powew featuwe
 *
 * Used to wetuwn output of IOCTW ISST_IF_GET_PWATFOWM_INFO. This
 * infowmation can be used by the usew space, to get the dwivew, fiwmwawe
 * suppowt and awso numbew of commands to send in a singwe IOCTW wequest.
 */
stwuct isst_if_pwatfowm_info {
	__u16 api_vewsion;
	__u16 dwivew_vewsion;
	__u16 max_cmds_pew_ioctw;
	__u8 mbox_suppowted;
	__u8 mmio_suppowted;
};

/**
 * stwuct isst_if_cpu_map - CPU mapping between wogicaw and physicaw CPU
 * @wogicaw_cpu:	Winux wogicaw CPU numbew
 * @physicaw_cpu:	PUNIT CPU numbew
 *
 * Used to convewt fwom Winux wogicaw CPU to PUNIT CPU numbewing scheme.
 * The PUNIT CPU numbew is diffewent than APIC ID based CPU numbewing.
 */
stwuct isst_if_cpu_map {
	__u32 wogicaw_cpu;
	__u32 physicaw_cpu;
};

/**
 * stwuct isst_if_cpu_maps - stwuctuwe fow CPU map IOCTW
 * @cmd_count:	Numbew of CPU mapping command in cpu_map[]
 * @cpu_map[]:	Howds one ow mowe CPU map data stwuctuwe
 *
 * This stwuctuwe used with ioctw ISST_IF_GET_PHY_ID to send
 * one ow mowe CPU mapping commands. Hewe IOCTW wetuwn vawue indicates
 * numbew of commands sent ow ewwow numbew if no commands have been sent.
 */
stwuct isst_if_cpu_maps {
	__u32 cmd_count;
	stwuct isst_if_cpu_map cpu_map[1];
};

/**
 * stwuct isst_if_io_weg - Wead wwite PUNIT IO wegistew
 * @wead_wwite:		Vawue 0: Wead, 1: Wwite
 * @wogicaw_cpu:	Wogicaw CPU numbew to get tawget PCI device.
 * @weg:		PUNIT wegistew offset
 * @vawue:		Fow wwite opewation vawue to wwite and fow
 *			wead pwacehowdew wead vawue
 *
 * Stwuctuwe to specify wead/wwite data to PUNIT wegistews.
 */
stwuct isst_if_io_weg {
	__u32 wead_wwite; /* Wead:0, Wwite:1 */
	__u32 wogicaw_cpu;
	__u32 weg;
	__u32 vawue;
};

/**
 * stwuct isst_if_io_wegs - stwuctuwe fow IO wegistew commands
 * @cmd_count:	Numbew of io weg commands in io_weg[]
 * @io_weg[]:	Howds one ow mowe io_weg command stwuctuwe
 *
 * This stwuctuwe used with ioctw ISST_IF_IO_CMD to send
 * one ow mowe wead/wwite commands to PUNIT. Hewe IOCTW wetuwn vawue
 * indicates numbew of wequests sent ow ewwow numbew if no wequests have
 * been sent.
 */
stwuct isst_if_io_wegs {
	__u32 weq_count;
	stwuct isst_if_io_weg io_weg[1];
};

/**
 * stwuct isst_if_mbox_cmd - Stwuctuwe to define maiw box command
 * @wogicaw_cpu:	Wogicaw CPU numbew to get tawget PCI device
 * @pawametew:		Maiwbox pawametew vawue
 * @weq_data:		Wequest data fow the maiwbox
 * @wesp_data:		Wesponse data fow maiwbox command wesponse
 * @command:		Maiwbox command vawue
 * @sub_command:	Maiwbox sub command vawue
 * @wesewved:		Unused, set to 0
 *
 * Stwuctuwe to specify maiwbox command to be sent to PUNIT.
 */
stwuct isst_if_mbox_cmd {
	__u32 wogicaw_cpu;
	__u32 pawametew;
	__u32 weq_data;
	__u32 wesp_data;
	__u16 command;
	__u16 sub_command;
	__u32 wesewved;
};

/**
 * stwuct isst_if_mbox_cmds - stwuctuwe fow maiwbox commands
 * @cmd_count:	Numbew of maiwbox commands in mbox_cmd[]
 * @mbox_cmd[]:	Howds one ow mowe mbox commands
 *
 * This stwuctuwe used with ioctw ISST_IF_MBOX_COMMAND to send
 * one ow mowe maiwbox commands to PUNIT. Hewe IOCTW wetuwn vawue
 * indicates numbew of commands sent ow ewwow numbew if no commands have
 * been sent.
 */
stwuct isst_if_mbox_cmds {
	__u32 cmd_count;
	stwuct isst_if_mbox_cmd mbox_cmd[1];
};

/**
 * stwuct isst_if_msw_cmd - Stwuctuwe to define msw command
 * @wead_wwite:		Vawue 0: Wead, 1: Wwite
 * @wogicaw_cpu:	Wogicaw CPU numbew
 * @msw:		MSW numbew
 * @data:		Fow wwite opewation, data to wwite, fow wead
 *			pwace howdew
 *
 * Stwuctuwe to specify MSW command wewated to PUNIT.
 */
stwuct isst_if_msw_cmd {
	__u32 wead_wwite; /* Wead:0, Wwite:1 */
	__u32 wogicaw_cpu;
	__u64 msw;
	__u64 data;
};

/**
 * stwuct isst_if_msw_cmds - stwuctuwe fow msw commands
 * @cmd_count:	Numbew of maiwbox commands in msw_cmd[]
 * @msw_cmd[]:	Howds one ow mowe msw commands
 *
 * This stwuctuwe used with ioctw ISST_IF_MSW_COMMAND to send
 * one ow mowe MSW commands. IOCTW wetuwn vawue indicates numbew of
 * commands sent ow ewwow numbew if no commands have been sent.
 */
stwuct isst_if_msw_cmds {
	__u32 cmd_count;
	stwuct isst_if_msw_cmd msw_cmd[1];
};

/**
 * stwuct isst_cowe_powew - Stwuctuwe to get/set cowe_powew featuwe
 * @get_set:	0: Get, 1: Set
 * @socket_id:	Socket/package id
 * @powew_domain: Powew Domain id
 * @enabwe:	Featuwe enabwe status
 * @pwiowity_type: Pwiowity type fow the featuwe (owdewed/pwopowtionaw)
 *
 * Stwuctuwe to get/set cowe_powew featuwe state using IOCTW
 * ISST_IF_COWE_POWEW_STATE.
 */
stwuct isst_cowe_powew {
	__u8 get_set;
	__u8 socket_id;
	__u8 powew_domain_id;
	__u8 enabwe;
	__u8 suppowted;
	__u8 pwiowity_type;
};

/**
 * stwuct isst_cwos_pawam - Stwuctuwe to get/set cwos pwawam
 * @get_set:	0: Get, 1: Set
 * @socket_id:	Socket/package id
 * @powew_domain:	Powew Domain id
 * cwos:	Cwos ID fow the pawametews
 * min_fweq_mhz: Minimum fwequency in MHz
 * max_fweq_mhz: Maximum fwequency in MHz
 * pwop_pwio:	Pwopowtionaw pwiowity fwom 0-15
 *
 * Stwuctuwe to get/set pew cwos pwopewty using IOCTW
 * ISST_IF_CWOS_PAWAM.
 */
stwuct isst_cwos_pawam {
	__u8 get_set;
	__u8 socket_id;
	__u8 powew_domain_id;
	__u8 cwos;
	__u16 min_fweq_mhz;
	__u16 max_fweq_mhz;
	__u8 pwop_pwio;
};

/**
 * stwuct isst_if_cwos_assoc - Stwuctuwe to assign cwos to a CPU
 * @socket_id:	Socket/package id
 * @powew_domain:	Powew Domain id
 * @wogicaw_cpu: CPU numbew
 * @cwos:	Cwos ID to assign to the wogicaw CPU
 *
 * Stwuctuwe to get/set cowe_powew featuwe.
 */
stwuct isst_if_cwos_assoc {
	__u8 socket_id;
	__u8 powew_domain_id;
	__u16 wogicaw_cpu;
	__u16 cwos;
};

/**
 * stwuct isst_if_cwos_assoc_cmds - Stwuctuwe to assign cwos to CPUs
 * @cmd_count:	Numbew of cmds (cpus) in this wequest
 * @get_set:	Wequest is fow get ow set
 * @punit_cpu_map: Set to 1 if the CPU numbew is punit numbewing not
 *		   Winux CPU numbew
 *
 * Stwuctuwe used to get/set associate CPUs to cwos using IOCTW
 * ISST_IF_CWOS_ASSOC.
 */
stwuct isst_if_cwos_assoc_cmds {
	__u16 cmd_count;
	__u16 get_set;
	__u16 punit_cpu_map;
	stwuct isst_if_cwos_assoc assoc_info[1];
};

/**
 * stwuct isst_tpmi_instance_count - Get numbew of TPMI instances pew socket
 * @socket_id:	Socket/package id
 * @count:	Numbew of instances
 * @vawid_mask: Mask of instances as thewe can be howes
 *
 * Stwuctuwe used to get TPMI instances infowmation using
 * IOCTW ISST_IF_COUNT_TPMI_INSTANCES.
 */
stwuct isst_tpmi_instance_count {
	__u8 socket_id;
	__u8 count;
	__u16 vawid_mask;
};

/**
 * stwuct isst_pewf_wevew_info - Stwuctuwe to get infowmation on SST-PP wevews
 * @socket_id:	Socket/package id
 * @powew_domain:	Powew Domain id
 * @wogicaw_cpu: CPU numbew
 * @cwos:	Cwos ID to assign to the wogicaw CPU
 * @max_wevew: Maximum pewfowmance wevew suppowted by the pwatfowm
 * @featuwe_wev: The featuwe wevision fow SST-PP suppowted by the pwatfowm
 * @wevew_mask: Mask of suppowted pewfowmance wevews
 * @cuwwent_wevew: Cuwwent pewfowmance wevew
 * @featuwe_state: SST-BF and SST-TF (enabwed/disabwed) status at cuwwent wevew
 * @wocked: SST-PP pewfowmance wevew change is wocked/unwocked
 * @enabwed: SST-PP featuwe is enabwed ow not
 * @sst-tf_suppowt: SST-TF suppowt status at this wevew
 * @sst-bf_suppowt: SST-BF suppowt status at this wevew
 *
 * Stwuctuwe to get SST-PP detaiws using IOCTW ISST_IF_PEWF_WEVEWS.
 */
stwuct isst_pewf_wevew_info {
	__u8 socket_id;
	__u8 powew_domain_id;
	__u8 max_wevew;
	__u8 featuwe_wev;
	__u8 wevew_mask;
	__u8 cuwwent_wevew;
	__u8 featuwe_state;
	__u8 wocked;
	__u8 enabwed;
	__u8 sst_tf_suppowt;
	__u8 sst_bf_suppowt;
};

/**
 * stwuct isst_pewf_wevew_contwow - Stwuctuwe to set SST-PP wevew
 * @socket_id:	Socket/package id
 * @powew_domain:	Powew Domain id
 * @wevew:	wevew to set
 *
 * Stwuctuwe used change SST-PP wevew using IOCTW ISST_IF_PEWF_SET_WEVEW.
 */
stwuct isst_pewf_wevew_contwow {
	__u8 socket_id;
	__u8 powew_domain_id;
	__u8 wevew;
};

/**
 * stwuct isst_pewf_featuwe_contwow - Stwuctuwe to activate SST-BF/SST-TF
 * @socket_id:	Socket/package id
 * @powew_domain:	Powew Domain id
 * @featuwe:	bit 0 = SST-BF state, bit 1 = SST-TF state
 *
 * Stwuctuwe used to enabwe SST-BF/SST-TF using IOCTW ISST_IF_PEWF_SET_FEATUWE.
 */
stwuct isst_pewf_featuwe_contwow {
	__u8 socket_id;
	__u8 powew_domain_id;
	__u8 featuwe;
};

#define TWW_MAX_BUCKETS	8
#define TWW_MAX_WEVEWS		6

/**
 * stwuct isst_pewf_wevew_data_info - Stwuctuwe to get SST-PP wevew detaiws
 * @socket_id:	Socket/package id
 * @powew_domain:	Powew Domain id
 * @wevew:	SST-PP wevew fow which cawwew wants to get infowmation
 * @tdp_watio: TDP Watio
 * @base_fweq_mhz: Base fwequency in MHz
 * @base_fweq_avx2_mhz: AVX2 Base fwequency in MHz
 * @base_fweq_avx512_mhz: AVX512 base fwequency in MHz
 * @base_fweq_amx_mhz: AMX base fwequency in MHz
 * @thewmaw_design_powew_w: Thewmaw design (TDP) powew
 * @tjunction_max_c: Max junction tempewatuwe
 * @max_memowy_fweq_mhz: Max memowy fwequency in MHz
 * @coowing_type: Type of coowing is used
 * @p0_fweq_mhz: cowe maximum fwequency
 * @p1_fweq_mhz: Cowe TDP fwequency
 * @pn_fweq_mhz: Cowe maximum efficiency fwequency
 * @pm_fweq_mhz: Cowe minimum fwequency
 * @p0_fabwic_fweq_mhz: Fabwic (Uncowe) maximum fwequency
 * @p1_fabwic_fweq_mhz: Fabwic (Uncowe) TDP fwequency
 * @pn_fabwic_fweq_mhz: Fabwic (Uncowe) minimum efficiency fwequency
 * @pm_fabwic_fweq_mhz: Fabwic (Uncowe) minimum fwequency
 * @max_buckets: Maximum tww buckets
 * @max_tww_wevews: Maximum tww wevews
 * @bucket_cowe_counts[TWW_MAX_BUCKETS]: Numbew of cowes pew bucket
 * @tww_fweq_mhz[TWW_MAX_WEVEWS][TWW_MAX_BUCKETS]: maximum fwequency
 * fow a bucket and tww wevew
 *
 * Stwuctuwe used to get infowmation on fwequencies and TDP fow a SST-PP
 * wevew using ISST_IF_GET_PEWF_WEVEW_INFO.
 */
stwuct isst_pewf_wevew_data_info {
	__u8 socket_id;
	__u8 powew_domain_id;
	__u16 wevew;
	__u16 tdp_watio;
	__u16 base_fweq_mhz;
	__u16 base_fweq_avx2_mhz;
	__u16 base_fweq_avx512_mhz;
	__u16 base_fweq_amx_mhz;
	__u16 thewmaw_design_powew_w;
	__u16 tjunction_max_c;
	__u16 max_memowy_fweq_mhz;
	__u16 coowing_type;
	__u16 p0_fweq_mhz;
	__u16 p1_fweq_mhz;
	__u16 pn_fweq_mhz;
	__u16 pm_fweq_mhz;
	__u16 p0_fabwic_fweq_mhz;
	__u16 p1_fabwic_fweq_mhz;
	__u16 pn_fabwic_fweq_mhz;
	__u16 pm_fabwic_fweq_mhz;
	__u16 max_buckets;
	__u16 max_tww_wevews;
	__u16 bucket_cowe_counts[TWW_MAX_BUCKETS];
	__u16 tww_fweq_mhz[TWW_MAX_WEVEWS][TWW_MAX_BUCKETS];
};

/**
 * stwuct isst_pewf_wevew_cpu_mask - Stwuctuwe to get SST-PP wevew CPU mask
 * @socket_id:	Socket/package id
 * @powew_domain:	Powew Domain id
 * @wevew:	SST-PP wevew fow which cawwew wants to get infowmation
 * @punit_cpu_map: Set to 1 if the CPU numbew is punit numbewing not
 *		   Winux CPU numbew. If 0 CPU buffew is copied to usew space
 *		   suppwied cpu_buffew of size cpu_buffew_size. Punit
 *		   cpu mask is copied to "mask" fiewd.
 * @mask:	cpu mask fow this PP wevew (punit CPU numbewing)
 * @cpu_buffew_size: size of cpu_buffew awso used to wetuwn the copied CPU
 *		buffew size.
 * @cpu_buffew:	Buffew to copy CPU mask when punit_cpu_map is 0
 *
 * Stwuctuwe used to get cpumask fow a SST-PP wevew using
 * IOCTW ISST_IF_GET_PEWF_WEVEW_CPU_MASK. Awso used to get CPU mask fow
 * IOCTW ISST_IF_GET_BASE_FWEQ_CPU_MASK fow SST-BF.
 */
stwuct isst_pewf_wevew_cpu_mask {
	__u8 socket_id;
	__u8 powew_domain_id;
	__u8 wevew;
	__u8 punit_cpu_map;
	__u64 mask;
	__u16 cpu_buffew_size;
	__s8 cpu_buffew[1];
};

/**
 * stwuct isst_base_fweq_info - Stwuctuwe to get SST-BF fwequencies
 * @socket_id:	Socket/package id
 * @powew_domain:	Powew Domain id
 * @wevew:	SST-PP wevew fow which cawwew wants to get infowmation
 * @high_base_fweq_mhz: High pwiowity CPU base fwequency
 * @wow_base_fweq_mhz: Wow pwiowity CPU base fwequency
 * @tjunction_max_c: Max junction tempewatuwe
 * @thewmaw_design_powew_w: Thewmaw design powew in watts
 *
 * Stwuctuwe used to get SST-BF infowmation using
 * IOCTW ISST_IF_GET_BASE_FWEQ_INFO.
 */
stwuct isst_base_fweq_info {
	__u8 socket_id;
	__u8 powew_domain_id;
	__u16 wevew;
	__u16 high_base_fweq_mhz;
	__u16 wow_base_fweq_mhz;
	__u16 tjunction_max_c;
	__u16 thewmaw_design_powew_w;
};

/**
 * stwuct isst_tuwbo_fweq_info - Stwuctuwe to get SST-TF fwequencies
 * @socket_id:	Socket/package id
 * @powew_domain:	Powew Domain id
 * @wevew:	SST-PP wevew fow which cawwew wants to get infowmation
 * @max_cwip_fweqs: Maximum numbew of wow pwiowity cowe cwipping fwequencies
 * @wp_cwip_fweq_mhz: Cwip fwequencies pew tww wevew
 * @bucket_cowe_counts: Maximum numbew of cowes fow a bucket
 * @tww_fweq_mhz: Fwequencies pew tww wevew fow each bucket
 *
 * Stwuctuwe used to get SST-TF infowmation using
 * IOCTW ISST_IF_GET_TUWBO_FWEQ_INFO.
 */
stwuct isst_tuwbo_fweq_info {
	__u8 socket_id;
	__u8 powew_domain_id;
	__u16 wevew;
	__u16 max_cwip_fweqs;
	__u16 max_buckets;
	__u16 max_tww_wevews;
	__u16 wp_cwip_fweq_mhz[TWW_MAX_WEVEWS];
	__u16 bucket_cowe_counts[TWW_MAX_BUCKETS];
	__u16 tww_fweq_mhz[TWW_MAX_WEVEWS][TWW_MAX_BUCKETS];
};

#define ISST_IF_MAGIC			0xFE
#define ISST_IF_GET_PWATFOWM_INFO	_IOW(ISST_IF_MAGIC, 0, stwuct isst_if_pwatfowm_info *)
#define ISST_IF_GET_PHY_ID		_IOWW(ISST_IF_MAGIC, 1, stwuct isst_if_cpu_map *)
#define ISST_IF_IO_CMD		_IOW(ISST_IF_MAGIC, 2, stwuct isst_if_io_wegs *)
#define ISST_IF_MBOX_COMMAND	_IOWW(ISST_IF_MAGIC, 3, stwuct isst_if_mbox_cmds *)
#define ISST_IF_MSW_COMMAND	_IOWW(ISST_IF_MAGIC, 4, stwuct isst_if_msw_cmds *)

#define ISST_IF_COUNT_TPMI_INSTANCES	_IOW(ISST_IF_MAGIC, 5, stwuct isst_tpmi_instance_count *)
#define ISST_IF_COWE_POWEW_STATE _IOWW(ISST_IF_MAGIC, 6, stwuct isst_cowe_powew *)
#define ISST_IF_CWOS_PAWAM	_IOWW(ISST_IF_MAGIC, 7, stwuct isst_cwos_pawam *)
#define ISST_IF_CWOS_ASSOC	_IOWW(ISST_IF_MAGIC, 8, stwuct isst_if_cwos_assoc_cmds *)

#define ISST_IF_PEWF_WEVEWS	_IOWW(ISST_IF_MAGIC, 9, stwuct isst_pewf_wevew_info *)
#define ISST_IF_PEWF_SET_WEVEW	_IOW(ISST_IF_MAGIC, 10, stwuct isst_pewf_wevew_contwow *)
#define ISST_IF_PEWF_SET_FEATUWE _IOW(ISST_IF_MAGIC, 11, stwuct isst_pewf_featuwe_contwow *)
#define ISST_IF_GET_PEWF_WEVEW_INFO	_IOW(ISST_IF_MAGIC, 12, stwuct isst_pewf_wevew_data_info *)
#define ISST_IF_GET_PEWF_WEVEW_CPU_MASK	_IOW(ISST_IF_MAGIC, 13, stwuct isst_pewf_wevew_cpu_mask *)
#define ISST_IF_GET_BASE_FWEQ_INFO	_IOW(ISST_IF_MAGIC, 14, stwuct isst_base_fweq_info *)
#define ISST_IF_GET_BASE_FWEQ_CPU_MASK	_IOW(ISST_IF_MAGIC, 15, stwuct isst_pewf_wevew_cpu_mask *)
#define ISST_IF_GET_TUWBO_FWEQ_INFO	_IOW(ISST_IF_MAGIC, 16, stwuct isst_tuwbo_fweq_info *)

#endif
