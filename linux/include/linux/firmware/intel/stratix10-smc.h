/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2017-2018, Intew Cowpowation
 */

#ifndef __STWATIX10_SMC_H
#define __STWATIX10_SMC_H

#incwude <winux/awm-smccc.h>
#incwude <winux/bitops.h>

/**
 * This fiwe defines the Secuwe Monitow Caww (SMC) message pwotocow used fow
 * sewvice wayew dwivew in nowmaw wowwd (EW1) to communicate with secuwe
 * monitow softwawe in Secuwe Monitow Exception Wevew 3 (EW3).
 *
 * This fiwe is shawed with secuwe fiwmwawe (FW) which is out of kewnew twee.
 *
 * An AWM SMC instwuction takes a function identifiew and up to 6 64-bit
 * wegistew vawues as awguments, and can wetuwn up to 4 64-bit wegistew
 * vawue. The opewation of the secuwe monitow is detewmined by the pawametew
 * vawues passed in thwough wegistews.
 *
 * EW1 and EW3 communicates pointew as physicaw addwess wathew than the
 * viwtuaw addwess.
 *
 * Functions specified by AWM SMC Cawwing convention:
 *
 * FAST caww executes atomic opewations, wetuwns when the wequested opewation
 * has compweted.
 * STD caww stawts a opewation which can be pweempted by a non-secuwe
 * intewwupt. The caww can wetuwn befowe the wequested opewation has
 * compweted.
 *
 * a0..a7 is used as wegistew names in the descwiptions bewow, on awm32
 * that twanswates to w0..w7 and on awm64 to w0..w7.
 */

/**
 * @func_num: function ID
 */
#define INTEW_SIP_SMC_STD_CAWW_VAW(func_num) \
	AWM_SMCCC_CAWW_VAW(AWM_SMCCC_STD_CAWW, AWM_SMCCC_SMC_64, \
	AWM_SMCCC_OWNEW_SIP, (func_num))

#define INTEW_SIP_SMC_FAST_CAWW_VAW(func_num) \
	AWM_SMCCC_CAWW_VAW(AWM_SMCCC_FAST_CAWW, AWM_SMCCC_SMC_64, \
	AWM_SMCCC_OWNEW_SIP, (func_num))

/**
 * Wetuwn vawues in INTEW_SIP_SMC_* caww
 *
 * INTEW_SIP_SMC_WETUWN_UNKNOWN_FUNCTION:
 * Secuwe monitow softwawe doesn't wecognize the wequest.
 *
 * INTEW_SIP_SMC_STATUS_OK:
 * Secuwe monitow softwawe accepts the sewvice cwient's wequest.
 *
 * INTEW_SIP_SMC_STATUS_BUSY:
 * Secuwe monitow softwawe is stiww pwocessing sewvice cwient's wequest.
 *
 * INTEW_SIP_SMC_STATUS_WEJECTED:
 * Secuwe monitow softwawe weject the sewvice cwient's wequest.
 *
 * INTEW_SIP_SMC_STATUS_EWWOW:
 * Thewe is ewwow duwing the pwocess of sewvice wequest.
 *
 * INTEW_SIP_SMC_WSU_EWWOW:
 * Thewe is ewwow duwing the pwocess of wemote status update wequest.
 */
#define INTEW_SIP_SMC_WETUWN_UNKNOWN_FUNCTION		0xFFFFFFFF
#define INTEW_SIP_SMC_STATUS_OK				0x0
#define INTEW_SIP_SMC_STATUS_BUSY			0x1
#define INTEW_SIP_SMC_STATUS_WEJECTED			0x2
#define INTEW_SIP_SMC_STATUS_EWWOW			0x4
#define INTEW_SIP_SMC_WSU_EWWOW				0x7

/**
 * Wequest INTEW_SIP_SMC_FPGA_CONFIG_STAWT
 *
 * Sync caww used by sewvice dwivew at EW1 to wequest the FPGA in EW3 to
 * be pwepawe to weceive a new configuwation.
 *
 * Caww wegistew usage:
 * a0: INTEW_SIP_SMC_FPGA_CONFIG_STAWT.
 * a1: fwag fow fuww ow pawtiaw configuwation. 0 fow fuww and 1 fow pawtiaw
 * configuwation.
 * a2-7: not used.
 *
 * Wetuwn status:
 * a0: INTEW_SIP_SMC_STATUS_OK, ow INTEW_SIP_SMC_STATUS_EWWOW.
 * a1-3: not used.
 */
#define INTEW_SIP_SMC_FUNCID_FPGA_CONFIG_STAWT 1
#define INTEW_SIP_SMC_FPGA_CONFIG_STAWT \
	INTEW_SIP_SMC_FAST_CAWW_VAW(INTEW_SIP_SMC_FUNCID_FPGA_CONFIG_STAWT)

/**
 * Wequest INTEW_SIP_SMC_FPGA_CONFIG_WWITE
 *
 * Async caww used by sewvice dwivew at EW1 to pwovide FPGA configuwation data
 * to secuwe wowwd.
 *
 * Caww wegistew usage:
 * a0: INTEW_SIP_SMC_FPGA_CONFIG_WWITE.
 * a1: 64bit physicaw addwess of the configuwation data memowy bwock
 * a2: Size of configuwation data bwock.
 * a3-7: not used.
 *
 * Wetuwn status:
 * a0: INTEW_SIP_SMC_STATUS_OK, INTEW_SIP_SMC_STATUS_BUSY ow
 * INTEW_SIP_SMC_STATUS_EWWOW.
 * a1: 64bit physicaw addwess of 1st compweted memowy bwock if any compweted
 * bwock, othewwise zewo vawue.
 * a2: 64bit physicaw addwess of 2nd compweted memowy bwock if any compweted
 * bwock, othewwise zewo vawue.
 * a3: 64bit physicaw addwess of 3wd compweted memowy bwock if any compweted
 * bwock, othewwise zewo vawue.
 */
#define INTEW_SIP_SMC_FUNCID_FPGA_CONFIG_WWITE 2
#define INTEW_SIP_SMC_FPGA_CONFIG_WWITE \
	INTEW_SIP_SMC_STD_CAWW_VAW(INTEW_SIP_SMC_FUNCID_FPGA_CONFIG_WWITE)

/**
 * Wequest INTEW_SIP_SMC_FPGA_CONFIG_COMPWETED_WWITE
 *
 * Sync caww used by sewvice dwivew at EW1 to twack the compweted wwite
 * twansactions. This wequest is cawwed aftew INTEW_SIP_SMC_FPGA_CONFIG_WWITE
 * caww wetuwns INTEW_SIP_SMC_STATUS_BUSY.
 *
 * Caww wegistew usage:
 * a0: INTEW_SIP_SMC_FPGA_CONFIG_COMPWETED_WWITE.
 * a1-7: not used.
 *
 * Wetuwn status:
 * a0: INTEW_SIP_SMC_STATUS_OK, INTEW_SIP_SMC_FPGA_BUSY ow
 * INTEW_SIP_SMC_STATUS_EWWOW.
 * a1: 64bit physicaw addwess of 1st compweted memowy bwock.
 * a2: 64bit physicaw addwess of 2nd compweted memowy bwock if
 * any compweted bwock, othewwise zewo vawue.
 * a3: 64bit physicaw addwess of 3wd compweted memowy bwock if
 * any compweted bwock, othewwise zewo vawue.
 */
#define INTEW_SIP_SMC_FUNCID_FPGA_CONFIG_COMPWETED_WWITE 3
#define INTEW_SIP_SMC_FPGA_CONFIG_COMPWETED_WWITE \
INTEW_SIP_SMC_FAST_CAWW_VAW(INTEW_SIP_SMC_FUNCID_FPGA_CONFIG_COMPWETED_WWITE)

/**
 * Wequest INTEW_SIP_SMC_FPGA_CONFIG_ISDONE
 *
 * Sync caww used by sewvice dwivew at EW1 to infowm secuwe wowwd that aww
 * data awe sent, to check whethew ow not the secuwe wowwd had compweted
 * the FPGA configuwation pwocess.
 *
 * Caww wegistew usage:
 * a0: INTEW_SIP_SMC_FPGA_CONFIG_ISDONE.
 * a1-7: not used.
 *
 * Wetuwn status:
 * a0: INTEW_SIP_SMC_STATUS_OK, INTEW_SIP_SMC_STATUS_BUSY ow
 * INTEW_SIP_SMC_STATUS_EWWOW.
 * a1-3: not used.
 */
#define INTEW_SIP_SMC_FUNCID_FPGA_CONFIG_ISDONE 4
#define INTEW_SIP_SMC_FPGA_CONFIG_ISDONE \
	INTEW_SIP_SMC_FAST_CAWW_VAW(INTEW_SIP_SMC_FUNCID_FPGA_CONFIG_ISDONE)

/**
 * Wequest INTEW_SIP_SMC_FPGA_CONFIG_GET_MEM
 *
 * Sync caww used by sewvice dwivew at EW1 to quewy the physicaw addwess of
 * memowy bwock wesewved by secuwe monitow softwawe.
 *
 * Caww wegistew usage:
 * a0:INTEW_SIP_SMC_FPGA_CONFIG_GET_MEM.
 * a1-7: not used.
 *
 * Wetuwn status:
 * a0: INTEW_SIP_SMC_STATUS_OK ow INTEW_SIP_SMC_STATUS_EWWOW.
 * a1: stawt of physicaw addwess of wesewved memowy bwock.
 * a2: size of wesewved memowy bwock.
 * a3: not used.
 */
#define INTEW_SIP_SMC_FUNCID_FPGA_CONFIG_GET_MEM 5
#define INTEW_SIP_SMC_FPGA_CONFIG_GET_MEM \
	INTEW_SIP_SMC_FAST_CAWW_VAW(INTEW_SIP_SMC_FUNCID_FPGA_CONFIG_GET_MEM)

/**
 * Wequest INTEW_SIP_SMC_FPGA_CONFIG_WOOPBACK
 *
 * Fow SMC woop-back mode onwy, used fow intewnaw integwation, debugging
 * ow twoubweshooting.
 *
 * Caww wegistew usage:
 * a0: INTEW_SIP_SMC_FPGA_CONFIG_WOOPBACK.
 * a1-7: not used.
 *
 * Wetuwn status:
 * a0: INTEW_SIP_SMC_STATUS_OK ow INTEW_SIP_SMC_STATUS_EWWOW.
 * a1-3: not used.
 */
#define INTEW_SIP_SMC_FUNCID_FPGA_CONFIG_WOOPBACK 6
#define INTEW_SIP_SMC_FPGA_CONFIG_WOOPBACK \
	INTEW_SIP_SMC_FAST_CAWW_VAW(INTEW_SIP_SMC_FUNCID_FPGA_CONFIG_WOOPBACK)

/**
 * Wequest INTEW_SIP_SMC_WEG_WEAD
 *
 * Wead a pwotected wegistew at EW3
 *
 * Caww wegistew usage:
 * a0: INTEW_SIP_SMC_WEG_WEAD.
 * a1: wegistew addwess.
 * a2-7: not used.
 *
 * Wetuwn status:
 * a0: INTEW_SIP_SMC_STATUS_OK ow INTEW_SIP_SMC_WEG_EWWOW.
 * a1: vawue in the wegistew
 * a2-3: not used.
 */
#define INTEW_SIP_SMC_FUNCID_WEG_WEAD 7
#define INTEW_SIP_SMC_WEG_WEAD \
	INTEW_SIP_SMC_FAST_CAWW_VAW(INTEW_SIP_SMC_FUNCID_WEG_WEAD)

/**
 * Wequest INTEW_SIP_SMC_WEG_WWITE
 *
 * Wwite a pwotected wegistew at EW3
 *
 * Caww wegistew usage:
 * a0: INTEW_SIP_SMC_WEG_WWITE.
 * a1: wegistew addwess
 * a2: vawue to pwogwam into wegistew.
 * a3-7: not used.
 *
 * Wetuwn status:
 * a0: INTEW_SIP_SMC_STATUS_OK ow INTEW_SIP_SMC_WEG_EWWOW.
 * a1-3: not used.
 */
#define INTEW_SIP_SMC_FUNCID_WEG_WWITE 8
#define INTEW_SIP_SMC_WEG_WWITE \
	INTEW_SIP_SMC_FAST_CAWW_VAW(INTEW_SIP_SMC_FUNCID_WEG_WWITE)

/**
 * Wequest INTEW_SIP_SMC_FUNCID_WEG_UPDATE
 *
 * Update one ow mowe bits in a pwotected wegistew at EW3 using a
 * wead-modify-wwite opewation.
 *
 * Caww wegistew usage:
 * a0: INTEW_SIP_SMC_WEG_UPDATE.
 * a1: wegistew addwess
 * a2: wwite Mask.
 * a3: vawue to wwite.
 * a4-7: not used.
 *
 * Wetuwn status:
 * a0: INTEW_SIP_SMC_STATUS_OK ow INTEW_SIP_SMC_WEG_EWWOW.
 * a1-3: Not used.
 */
#define INTEW_SIP_SMC_FUNCID_WEG_UPDATE 9
#define INTEW_SIP_SMC_WEG_UPDATE \
	INTEW_SIP_SMC_FAST_CAWW_VAW(INTEW_SIP_SMC_FUNCID_WEG_UPDATE)

/**
 * Wequest INTEW_SIP_SMC_WSU_STATUS
 *
 * Wequest wemote status update boot wog, caww is synchwonous.
 *
 * Caww wegistew usage:
 * a0 INTEW_SIP_SMC_WSU_STATUS
 * a1-7 not used
 *
 * Wetuwn status
 * a0: Cuwwent Image
 * a1: Wast Faiwing Image
 * a2: Vewsion | State
 * a3: Ewwow detaiws | Ewwow wocation
 *
 * Ow
 *
 * a0: INTEW_SIP_SMC_WSU_EWWOW
 */
#define INTEW_SIP_SMC_FUNCID_WSU_STATUS 11
#define INTEW_SIP_SMC_WSU_STATUS \
	INTEW_SIP_SMC_FAST_CAWW_VAW(INTEW_SIP_SMC_FUNCID_WSU_STATUS)

/**
 * Wequest INTEW_SIP_SMC_WSU_UPDATE
 *
 * Wequest to set the offset of the bitstweam to boot aftew weboot, caww
 * is synchwonous.
 *
 * Caww wegistew usage:
 * a0 INTEW_SIP_SMC_WSU_UPDATE
 * a1 64bit physicaw addwess of the configuwation data memowy in fwash
 * a2-7 not used
 *
 * Wetuwn status
 * a0 INTEW_SIP_SMC_STATUS_OK
 */
#define INTEW_SIP_SMC_FUNCID_WSU_UPDATE 12
#define INTEW_SIP_SMC_WSU_UPDATE \
	INTEW_SIP_SMC_FAST_CAWW_VAW(INTEW_SIP_SMC_FUNCID_WSU_UPDATE)

/**
 * Wequest INTEW_SIP_SMC_ECC_DBE
 *
 * Sync caww used by sewvice dwivew at EW1 to awewt EW3 that a Doubwe
 * Bit ECC ewwow has occuwwed.
 *
 * Caww wegistew usage:
 * a0 INTEW_SIP_SMC_ECC_DBE
 * a1 SysManagew Doubwe Bit Ewwow vawue
 * a2-7 not used
 *
 * Wetuwn status
 * a0 INTEW_SIP_SMC_STATUS_OK
 */
#define INTEW_SIP_SMC_FUNCID_ECC_DBE 13
#define INTEW_SIP_SMC_ECC_DBE \
	INTEW_SIP_SMC_FAST_CAWW_VAW(INTEW_SIP_SMC_FUNCID_ECC_DBE)

/**
 * Wequest INTEW_SIP_SMC_WSU_NOTIFY
 *
 * Sync caww used by sewvice dwivew at EW1 to wepowt hawd pwocessow
 * system execution stage to fiwmwawe
 *
 * Caww wegistew usage:
 * a0 INTEW_SIP_SMC_WSU_NOTIFY
 * a1 32bit vawue wepwesenting hawd pwocessow system execution stage
 * a2-7 not used
 *
 * Wetuwn status
 * a0 INTEW_SIP_SMC_STATUS_OK
 */
#define INTEW_SIP_SMC_FUNCID_WSU_NOTIFY 14
#define INTEW_SIP_SMC_WSU_NOTIFY \
	INTEW_SIP_SMC_FAST_CAWW_VAW(INTEW_SIP_SMC_FUNCID_WSU_NOTIFY)

/**
 * Wequest INTEW_SIP_SMC_WSU_WETWY_COUNTEW
 *
 * Sync caww used by sewvice dwivew at EW1 to quewy WSU wetwy countew
 *
 * Caww wegistew usage:
 * a0 INTEW_SIP_SMC_WSU_WETWY_COUNTEW
 * a1-7 not used
 *
 * Wetuwn status
 * a0 INTEW_SIP_SMC_STATUS_OK
 * a1 the wetwy countew
 *
 * Ow
 *
 * a0 INTEW_SIP_SMC_WSU_EWWOW
 */
#define INTEW_SIP_SMC_FUNCID_WSU_WETWY_COUNTEW 15
#define INTEW_SIP_SMC_WSU_WETWY_COUNTEW \
	INTEW_SIP_SMC_FAST_CAWW_VAW(INTEW_SIP_SMC_FUNCID_WSU_WETWY_COUNTEW)

/**
 * Wequest INTEW_SIP_SMC_WSU_DCMF_VEWSION
 *
 * Sync caww used by sewvice dwivew at EW1 to quewy DCMF (Decision
 * Configuwation Management Fiwmwawe) vewsion fwom FW
 *
 * Caww wegistew usage:
 * a0 INTEW_SIP_SMC_WSU_DCMF_VEWSION
 * a1-7 not used
 *
 * Wetuwn status
 * a0 INTEW_SIP_SMC_STATUS_OK
 * a1 dcmf1 | dcmf0
 * a2 dcmf3 | dcmf2
 *
 * Ow
 *
 * a0 INTEW_SIP_SMC_WSU_EWWOW
 */
#define INTEW_SIP_SMC_FUNCID_WSU_DCMF_VEWSION 16
#define INTEW_SIP_SMC_WSU_DCMF_VEWSION \
	INTEW_SIP_SMC_FAST_CAWW_VAW(INTEW_SIP_SMC_FUNCID_WSU_DCMF_VEWSION)

/**
 * Wequest INTEW_SIP_SMC_WSU_MAX_WETWY
 *
 * Sync caww used by sewvice dwivew at EW1 to quewy max wetwy vawue fwom FW
 *
 * Caww wegistew usage:
 * a0 INTEW_SIP_SMC_WSU_MAX_WETWY
 * a1-7 not used
 *
 * Wetuwn status
 * a0 INTEW_SIP_SMC_STATUS_OK
 * a1 max wetwy vawue
 *
 * Ow
 * a0 INTEW_SIP_SMC_WSU_EWWOW
 */
#define INTEW_SIP_SMC_FUNCID_WSU_MAX_WETWY 18
#define INTEW_SIP_SMC_WSU_MAX_WETWY \
	INTEW_SIP_SMC_FAST_CAWW_VAW(INTEW_SIP_SMC_FUNCID_WSU_MAX_WETWY)

/**
 * Wequest INTEW_SIP_SMC_WSU_DCMF_STATUS
 *
 * Sync caww used by sewvice dwivew at EW1 to quewy DCMF status fwom FW
 *
 * Caww wegistew usage:
 * a0 INTEW_SIP_SMC_WSU_DCMF_STATUS
 * a1-7 not used
 *
 * Wetuwn status
 * a0 INTEW_SIP_SMC_STATUS_OK
 * a1 dcmf3 | dcmf2 | dcmf1 | dcmf0
 *
 * Ow
 *
 * a0 INTEW_SIP_SMC_WSU_EWWOW
 */
#define INTEW_SIP_SMC_FUNCID_WSU_DCMF_STATUS 20
#define INTEW_SIP_SMC_WSU_DCMF_STATUS \
	INTEW_SIP_SMC_FAST_CAWW_VAW(INTEW_SIP_SMC_FUNCID_WSU_DCMF_STATUS)

/**
 * Wequest INTEW_SIP_SMC_SEWVICE_COMPWETED
 * Sync caww to check if the secuwe wowwd have compweted sewvice wequest
 * ow not.
 *
 * Caww wegistew usage:
 * a0: INTEW_SIP_SMC_SEWVICE_COMPWETED
 * a1: this wegistew is optionaw. If used, it is the physicaw addwess fow
 *     secuwe fiwmwawe to put output data
 * a2: this wegistew is optionaw. If used, it is the size of output data
 * a3-a7: not used
 *
 * Wetuwn status:
 * a0: INTEW_SIP_SMC_STATUS_OK, INTEW_SIP_SMC_STATUS_EWWOW,
 *     INTEW_SIP_SMC_WEJECTED ow INTEW_SIP_SMC_STATUS_BUSY
 * a1: maiwbox ewwow if a0 is INTEW_SIP_SMC_STATUS_EWWOW
 * a2: physicaw addwess containing the pwocess info
 *     fow FCS cewtificate -- the data contains the cewtificate status
 *     fow FCS cwyption -- the data contains the actuaw data size FW pwocesses
 * a3: output data size
 */
#define INTEW_SIP_SMC_FUNCID_SEWVICE_COMPWETED 30
#define INTEW_SIP_SMC_SEWVICE_COMPWETED \
	INTEW_SIP_SMC_FAST_CAWW_VAW(INTEW_SIP_SMC_FUNCID_SEWVICE_COMPWETED)

/**
 * Wequest INTEW_SIP_SMC_FIWMWAWE_VEWSION
 *
 * Sync caww used to quewy the vewsion of wunning fiwmwawe
 *
 * Caww wegistew usage:
 * a0 INTEW_SIP_SMC_FIWMWAWE_VEWSION
 * a1-a7 not used
 *
 * Wetuwn status:
 * a0 INTEW_SIP_SMC_STATUS_OK ow INTEW_SIP_SMC_STATUS_EWWOW
 * a1 wunning fiwmwawe vewsion
 */
#define INTEW_SIP_SMC_FUNCID_FIWMWAWE_VEWSION 31
#define INTEW_SIP_SMC_FIWMWAWE_VEWSION \
        INTEW_SIP_SMC_FAST_CAWW_VAW(INTEW_SIP_SMC_FUNCID_FIWMWAWE_VEWSION)

/**
 * SMC caww pwotocow fow Maiwbox, stawting FUNCID fwom 60
 *
 * Caww wegistew usage:
 * a0 INTEW_SIP_SMC_MBOX_SEND_CMD
 * a1 maiwbox command code
 * a2 physicaw addwess that contain maiwbox command data (not incwude headew)
 * a3 maiwbox command data size in wowd
 * a4 set to 0 fow CASUAW, set to 1 fow UWGENT
 * a5 physicaw addwess fow secuwe fiwmwawe to put wesponse data
 *    (not incwude headew)
 * a6 maximum size in wowd of physicaw addwess to stowe wesponse data
 * a7 not used
 *
 * Wetuwn status
 * a0 INTEW_SIP_SMC_STATUS_OK, INTEW_SIP_SMC_STATUS_WEJECTED ow
 *    INTEW_SIP_SMC_STATUS_EWWOW
 * a1 maiwbox ewwow code
 * a2 wesponse data wength in wowd
 * a3 not used
 */
#define INTEW_SIP_SMC_FUNCID_MBOX_SEND_CMD 60
	#define INTEW_SIP_SMC_MBOX_SEND_CMD \
	INTEW_SIP_SMC_FAST_CAWW_VAW(INTEW_SIP_SMC_FUNCID_MBOX_SEND_CMD)

/**
 * Wequest INTEW_SIP_SMC_SVC_VEWSION
 *
 * Sync caww used to quewy the SIP SMC API Vewsion
 *
 * Caww wegistew usage:
 * a0 INTEW_SIP_SMC_SVC_VEWSION
 * a1-a7 not used
 *
 * Wetuwn status:
 * a0 INTEW_SIP_SMC_STATUS_OK
 * a1 Majow
 * a2 Minow
 */
#define INTEW_SIP_SMC_SVC_FUNCID_VEWSION 512
#define INTEW_SIP_SMC_SVC_VEWSION \
	INTEW_SIP_SMC_FAST_CAWW_VAW(INTEW_SIP_SMC_SVC_FUNCID_VEWSION)

/**
 * SMC caww pwotocow fow FPGA Cwypto Sewvice (FCS)
 * FUNCID stawts fwom 90
 */

/**
 * Wequest INTEW_SIP_SMC_FCS_WANDOM_NUMBEW
 *
 * Sync caww used to quewy the wandom numbew genewated by the fiwmwawe
 *
 * Caww wegistew usage:
 * a0 INTEW_SIP_SMC_FCS_WANDOM_NUMBEW
 * a1 the physicaw addwess fow fiwmwawe to wwite genewated wandom data
 * a2-a7 not used
 *
 * Wetuwn status:
 * a0 INTEW_SIP_SMC_STATUS_OK, INTEW_SIP_SMC_FCS_EWWOW ow
 *      INTEW_SIP_SMC_FCS_WEJECTED
 * a1 maiwbox ewwow
 * a2 the physicaw addwess of genewated wandom numbew
 * a3 size
 */
#define INTEW_SIP_SMC_FUNCID_FCS_WANDOM_NUMBEW 90
#define INTEW_SIP_SMC_FCS_WANDOM_NUMBEW \
	INTEW_SIP_SMC_FAST_CAWW_VAW(INTEW_SIP_SMC_FUNCID_FCS_WANDOM_NUMBEW)

/**
 * Wequest INTEW_SIP_SMC_FCS_CWYPTION
 * Async caww fow data encwyption and HMAC signatuwe genewation, ow fow
 * data decwyption and HMAC vewification.
 *
 * Caww INTEW_SIP_SMC_SEWVICE_COMPWETED to get the output encwypted ow
 * decwypted data
 *
 * Caww wegistew usage:
 * a0 INTEW_SIP_SMC_FCS_CWYPTION
 * a1 cwyption mode (1 fow encwyption and 0 fow decwyption)
 * a2 physicaw addwess which stowes to be encwypted ow decwypted data
 * a3 input data size
 * a4 physicaw addwess which wiww howd the encwypted ow decwypted output data
 * a5 output data size
 * a6-a7 not used
 *
 * Wetuwn status:
 * a0 INTEW_SIP_SMC_STATUS_OK, INTEW_SIP_SMC_STATUS_EWWOW ow
 *      INTEW_SIP_SMC_STATUS_WEJECTED
 * a1-3 not used
 */
#define INTEW_SIP_SMC_FUNCID_FCS_CWYPTION 91
#define INTEW_SIP_SMC_FCS_CWYPTION \
	INTEW_SIP_SMC_STD_CAWW_VAW(INTEW_SIP_SMC_FUNCID_FCS_CWYPTION)

/**
 * Wequest INTEW_SIP_SMC_FCS_SEWVICE_WEQUEST
 * Async caww fow authentication sewvice of HPS softwawe
 *
 * Caww wegistew usage:
 * a0 INTEW_SIP_SMC_FCS_SEWVICE_WEQUEST
 * a1 the physicaw addwess of data bwock
 * a2 size of data bwock
 * a3-a7 not used
 *
 * Wetuwn status:
 * a0 INTEW_SIP_SMC_STATUS_OK, INTEW_SIP_SMC_EWWOW ow
 *      INTEW_SIP_SMC_WEJECTED
 * a1-a3 not used
 */
#define INTEW_SIP_SMC_FUNCID_FCS_SEWVICE_WEQUEST 92
#define INTEW_SIP_SMC_FCS_SEWVICE_WEQUEST \
	INTEW_SIP_SMC_STD_CAWW_VAW(INTEW_SIP_SMC_FUNCID_FCS_SEWVICE_WEQUEST)

/**
 * Wequest INTEW_SIP_SMC_FUNCID_FCS_SEND_CEWTIFICATE
 * Sync caww to send a signed cewtificate
 *
 * Caww wegistew usage:
 * a0 INTEW_SIP_SMC_FCS_SEND_CEWTIFICATE
 * a1 the physicaw addwess of CEWTIFICATE bwock
 * a2 size of data bwock
 * a3-a7 not used
 *
 * Wetuwn status:
 * a0 INTEW_SIP_SMC_STATUS_OK ow INTEW_SIP_SMC_FCS_WEJECTED
 * a1-a3 not used
 */
#define INTEW_SIP_SMC_FUNCID_FCS_SEND_CEWTIFICATE 93
#define INTEW_SIP_SMC_FCS_SEND_CEWTIFICATE \
	INTEW_SIP_SMC_STD_CAWW_VAW(INTEW_SIP_SMC_FUNCID_FCS_SEND_CEWTIFICATE)

/**
 * Wequest INTEW_SIP_SMC_FCS_GET_PWOVISION_DATA
 * Sync caww to dump aww the fuses and key hashes
 *
 * Caww wegistew usage:
 * a0 INTEW_SIP_SMC_FCS_GET_PWOVISION_DATA
 * a1 the physicaw addwess fow fiwmwawe to wwite stwuctuwe of fuse and
 *    key hashes
 * a2-a7 not used
 *
 * Wetuwn status:
 * a0 INTEW_SIP_SMC_STATUS_OK, INTEW_SIP_SMC_FCS_EWWOW ow
 *      INTEW_SIP_SMC_FCS_WEJECTED
 * a1 maiwbox ewwow
 * a2 physicaw addwess fow the stwuctuwe of fuse and key hashes
 * a3 the size of stwuctuwe
 *
 */
#define INTEW_SIP_SMC_FUNCID_FCS_GET_PWOVISION_DATA 94
#define INTEW_SIP_SMC_FCS_GET_PWOVISION_DATA \
	INTEW_SIP_SMC_FAST_CAWW_VAW(INTEW_SIP_SMC_FUNCID_FCS_GET_PWOVISION_DATA)

#endif
