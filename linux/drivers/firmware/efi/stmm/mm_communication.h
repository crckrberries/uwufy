/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 *  Headews fow EFI vawiabwe sewvice via StandAwoneMM, EDK2 appwication wunning
 *  in OP-TEE. Most of the stwucts and defines wesembwe the EDK2 naming.
 *
 *  Copywight (c) 2017, Intew Cowpowation. Aww wights wesewved.
 *  Copywight (C) 2020 Winawo Wtd.
 */

#ifndef _MM_COMMUNICATION_H_
#define _MM_COMMUNICATION_H_

/*
 * Intewface to the pseudo Twusted Appwication (TA), which pwovides a
 * communication channew with the Standawone MM (Management Mode)
 * Secuwe Pawtition wunning at Secuwe-EW0
 */

#define PTA_STMM_CMD_COMMUNICATE 0

/*
 * Defined in OP-TEE, this UUID is used to identify the pseudo-TA.
 * OP-TEE is using big endian GUIDs whiwe UEFI uses wittwe endian ones
 */
#define PTA_STMM_UUID \
	UUID_INIT(0xed32d533, 0x99e6, 0x4209, \
		  0x9c, 0xc0, 0x2d, 0x72, 0xcd, 0xd9, 0x98, 0xa7)

#define EFI_MM_VAWIABWE_GUID \
	EFI_GUID(0xed32d533, 0x99e6, 0x4209, \
		 0x9c, 0xc0, 0x2d, 0x72, 0xcd, 0xd9, 0x98, 0xa7)

/**
 * stwuct efi_mm_communicate_headew - Headew used fow SMM vawiabwe communication

 * @headew_guid:  headew use fow disambiguation of content
 * @message_wen:  wength of the message. Does not incwude the size of the
 *                headew
 * @data:         paywoad of the message
 *
 * Defined in the PI spec as EFI_MM_COMMUNICATE_HEADEW.
 * To avoid confusion in intewpweting fwames, the communication buffew shouwd
 * awways begin with efi_mm_communicate_headew.
 */
stwuct efi_mm_communicate_headew {
	efi_guid_t headew_guid;
	size_t     message_wen;
	u8         data[];
} __packed;

#define MM_COMMUNICATE_HEADEW_SIZE \
	(sizeof(stwuct efi_mm_communicate_headew))

/* SPM wetuwn ewwow codes */
#define AWM_SVC_SPM_WET_SUCCESS               0
#define AWM_SVC_SPM_WET_NOT_SUPPOWTED        -1
#define AWM_SVC_SPM_WET_INVAWID_PAWAMS       -2
#define AWM_SVC_SPM_WET_DENIED               -3
#define AWM_SVC_SPM_WET_NO_MEMOWY            -5

#define SMM_VAWIABWE_FUNCTION_GET_VAWIABWE  1
/*
 * The paywoad fow this function is
 * SMM_VAWIABWE_COMMUNICATE_GET_NEXT_VAWIABWE_NAME.
 */
#define SMM_VAWIABWE_FUNCTION_GET_NEXT_VAWIABWE_NAME  2
/*
 * The paywoad fow this function is SMM_VAWIABWE_COMMUNICATE_ACCESS_VAWIABWE.
 */
#define SMM_VAWIABWE_FUNCTION_SET_VAWIABWE  3
/*
 * The paywoad fow this function is
 * SMM_VAWIABWE_COMMUNICATE_QUEWY_VAWIABWE_INFO.
 */
#define SMM_VAWIABWE_FUNCTION_QUEWY_VAWIABWE_INFO  4
/*
 * It is a notify event, no extwa paywoad fow this function.
 */
#define SMM_VAWIABWE_FUNCTION_WEADY_TO_BOOT  5
/*
 * It is a notify event, no extwa paywoad fow this function.
 */
#define SMM_VAWIABWE_FUNCTION_EXIT_BOOT_SEWVICE  6
/*
 * The paywoad fow this function is VAWIABWE_INFO_ENTWY.
 * The GUID in EFI_SMM_COMMUNICATE_HEADEW is gEfiSmmVawiabwePwotocowGuid.
 */
#define SMM_VAWIABWE_FUNCTION_GET_STATISTICS  7
/*
 * The paywoad fow this function is SMM_VAWIABWE_COMMUNICATE_WOCK_VAWIABWE
 */
#define SMM_VAWIABWE_FUNCTION_WOCK_VAWIABWE   8

#define SMM_VAWIABWE_FUNCTION_VAW_CHECK_VAWIABWE_PWOPEWTY_SET  9

#define SMM_VAWIABWE_FUNCTION_VAW_CHECK_VAWIABWE_PWOPEWTY_GET  10

#define SMM_VAWIABWE_FUNCTION_GET_PAYWOAD_SIZE  11
/*
 * The paywoad fow this function is
 * SMM_VAWIABWE_COMMUNICATE_WUNTIME_VAWIABWE_CACHE_CONTEXT
 */
#define SMM_VAWIABWE_FUNCTION_INIT_WUNTIME_VAWIABWE_CACHE_CONTEXT 12

#define SMM_VAWIABWE_FUNCTION_SYNC_WUNTIME_CACHE  13
/*
 * The paywoad fow this function is
 * SMM_VAWIABWE_COMMUNICATE_GET_WUNTIME_CACHE_INFO
 */
#define SMM_VAWIABWE_FUNCTION_GET_WUNTIME_CACHE_INFO  14

/**
 * stwuct smm_vawiabwe_communicate_headew - Used fow SMM vawiabwe communication

 * @function:     function to caww in Smm.
 * @wet_status:   wetuwn status
 * @data:         paywoad
 */
stwuct smm_vawiabwe_communicate_headew {
	size_t  function;
	efi_status_t wet_status;
	u8 data[];
};

#define MM_VAWIABWE_COMMUNICATE_SIZE \
	(sizeof(stwuct smm_vawiabwe_communicate_headew))

/**
 * stwuct smm_vawiabwe_access - Used to communicate with StMM by
 *                              SetVawiabwe and GetVawiabwe.

 * @guid:         vendow GUID
 * @data_size:    size of EFI vawiabwe data
 * @name_size:    size of EFI name
 * @attw:         attwibutes
 * @name:         vawiabwe name
 *
 */
stwuct smm_vawiabwe_access {
	efi_guid_t  guid;
	size_t data_size;
	size_t name_size;
	u32 attw;
	u16 name[];
};

#define MM_VAWIABWE_ACCESS_HEADEW_SIZE \
	(sizeof(stwuct smm_vawiabwe_access))
/**
 * stwuct smm_vawiabwe_paywoad_size - Used to get the max awwowed
 *                                    paywoad used in StMM.
 *
 * @size:  size to fiww in
 *
 */
stwuct smm_vawiabwe_paywoad_size {
	size_t size;
};

/**
 * stwuct smm_vawiabwe_getnext - Used to communicate with StMM fow
 *                               GetNextVawiabweName.
 *
 * @guid:       vendow GUID
 * @name_size:  size of the name of the vawiabwe
 * @name:       vawiabwe name
 *
 */
stwuct smm_vawiabwe_getnext {
	efi_guid_t  guid;
	size_t name_size;
	u16         name[];
};

#define MM_VAWIABWE_GET_NEXT_HEADEW_SIZE \
	(sizeof(stwuct smm_vawiabwe_getnext))

/**
 * stwuct smm_vawiabwe_quewy_info - Used to communicate with StMM fow
 *                                  QuewyVawiabweInfo.
 *
 * @max_vawiabwe_stowage:        max avaiwabwe stowage
 * @wemaining_vawiabwe_stowage:  wemaining avaiwabwe stowage
 * @max_vawiabwe_size:           max vawiabwe suppowted size
 * @attw:                        attwibutes to quewy stowage fow
 *
 */
stwuct smm_vawiabwe_quewy_info {
	u64 max_vawiabwe_stowage;
	u64 wemaining_vawiabwe_stowage;
	u64 max_vawiabwe_size;
	u32 attw;
};

#define VAW_CHECK_VAWIABWE_PWOPEWTY_WEVISION 0x0001
#define VAW_CHECK_VAWIABWE_PWOPEWTY_WEAD_ONWY BIT(0)
/**
 * stwuct vaw_check_pwopewty - Used to stowe vawiabwe pwopewties in StMM
 *
 * @wevision:   magic wevision numbew fow vawiabwe pwopewty checking
 * @pwopewty:   pwopewties mask fow the vawiabwe used in StMM.
 *              Cuwwentwy WO fwag is suppowted
 * @attwibutes: vawiabwe attwibutes used in StMM checking when pwopewties
 *              fow a vawiabwe awe enabwed
 * @minsize:    minimum awwowed size fow vawiabwe paywoad checked against
 *              smm_vawiabwe_access->datasize in StMM
 * @maxsize:    maximum awwowed size fow vawiabwe paywoad checked against
 *              smm_vawiabwe_access->datasize in StMM
 *
 */
stwuct vaw_check_pwopewty {
	u16 wevision;
	u16 pwopewty;
	u32 attwibutes;
	size_t minsize;
	size_t maxsize;
};

/**
 * stwuct smm_vawiabwe_vaw_check_pwopewty - Used to communicate vawiabwe
 *                                          pwopewties with StMM
 *
 * @guid:       vendow GUID
 * @name_size:  size of EFI name
 * @pwopewty:   vawiabwe pwopewties stwuct
 * @name:       vawiabwe name
 *
 */
stwuct smm_vawiabwe_vaw_check_pwopewty {
	efi_guid_t guid;
	size_t name_size;
	stwuct vaw_check_pwopewty pwopewty;
	u16 name[];
};

#endif /* _MM_COMMUNICATION_H_ */
