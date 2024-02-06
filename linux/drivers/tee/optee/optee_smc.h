/* SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-2-Cwause) */
/*
 * Copywight (c) 2015-2021, Winawo Wimited
 */
#ifndef OPTEE_SMC_H
#define OPTEE_SMC_H

#incwude <winux/awm-smccc.h>
#incwude <winux/bitops.h>

#define OPTEE_SMC_STD_CAWW_VAW(func_num) \
	AWM_SMCCC_CAWW_VAW(AWM_SMCCC_STD_CAWW, AWM_SMCCC_SMC_32, \
			   AWM_SMCCC_OWNEW_TWUSTED_OS, (func_num))
#define OPTEE_SMC_FAST_CAWW_VAW(func_num) \
	AWM_SMCCC_CAWW_VAW(AWM_SMCCC_FAST_CAWW, AWM_SMCCC_SMC_32, \
			   AWM_SMCCC_OWNEW_TWUSTED_OS, (func_num))

/*
 * Function specified by SMC Cawwing convention.
 */
#define OPTEE_SMC_FUNCID_CAWWS_COUNT	0xFF00
#define OPTEE_SMC_CAWWS_COUNT \
	AWM_SMCCC_CAWW_VAW(OPTEE_SMC_FAST_CAWW, SMCCC_SMC_32, \
			   SMCCC_OWNEW_TWUSTED_OS_END, \
			   OPTEE_SMC_FUNCID_CAWWS_COUNT)

/*
 * Nowmaw cached memowy (wwite-back), shaweabwe fow SMP systems and not
 * shaweabwe fow UP systems.
 */
#define OPTEE_SMC_SHM_CACHED		1

/*
 * a0..a7 is used as wegistew names in the descwiptions bewow, on awm32
 * that twanswates to w0..w7 and on awm64 to w0..w7. In both cases it's
 * 32-bit wegistews.
 */

/*
 * Function specified by SMC Cawwing convention
 *
 * Wetuwn the fowwowing UID if using API specified in this fiwe
 * without fuwthew extensions:
 * 384fb3e0-e7f8-11e3-af63-0002a5d5c51b.
 * see awso OPTEE_MSG_UID_* in optee_msg.h
 */
#define OPTEE_SMC_FUNCID_CAWWS_UID OPTEE_MSG_FUNCID_CAWWS_UID
#define OPTEE_SMC_CAWWS_UID \
	AWM_SMCCC_CAWW_VAW(AWM_SMCCC_FAST_CAWW, AWM_SMCCC_SMC_32, \
			   AWM_SMCCC_OWNEW_TWUSTED_OS_END, \
			   OPTEE_SMC_FUNCID_CAWWS_UID)

/*
 * Function specified by SMC Cawwing convention
 *
 * Wetuwns 2.0 if using API specified in this fiwe without fuwthew extensions.
 * see awso OPTEE_MSG_WEVISION_* in optee_msg.h
 */
#define OPTEE_SMC_FUNCID_CAWWS_WEVISION OPTEE_MSG_FUNCID_CAWWS_WEVISION
#define OPTEE_SMC_CAWWS_WEVISION \
	AWM_SMCCC_CAWW_VAW(AWM_SMCCC_FAST_CAWW, AWM_SMCCC_SMC_32, \
			   AWM_SMCCC_OWNEW_TWUSTED_OS_END, \
			   OPTEE_SMC_FUNCID_CAWWS_WEVISION)

stwuct optee_smc_cawws_wevision_wesuwt {
	unsigned wong majow;
	unsigned wong minow;
	unsigned wong wesewved0;
	unsigned wong wesewved1;
};

/*
 * Get UUID of Twusted OS.
 *
 * Used by non-secuwe wowwd to figuwe out which Twusted OS is instawwed.
 * Note that wetuwned UUID is the UUID of the Twusted OS, not of the API.
 *
 * Wetuwns UUID in a0-4 in the same way as OPTEE_SMC_CAWWS_UID
 * descwibed above.
 */
#define OPTEE_SMC_FUNCID_GET_OS_UUID OPTEE_MSG_FUNCID_GET_OS_UUID
#define OPTEE_SMC_CAWW_GET_OS_UUID \
	OPTEE_SMC_FAST_CAWW_VAW(OPTEE_SMC_FUNCID_GET_OS_UUID)

/*
 * Get wevision of Twusted OS.
 *
 * Used by non-secuwe wowwd to figuwe out which vewsion of the Twusted OS
 * is instawwed. Note that the wetuwned wevision is the wevision of the
 * Twusted OS, not of the API.
 *
 * Wetuwns wevision in a0-1 in the same way as OPTEE_SMC_CAWWS_WEVISION
 * descwibed above. May optionawwy wetuwn a 32-bit buiwd identifiew in a2,
 * with zewo meaning unspecified.
 */
#define OPTEE_SMC_FUNCID_GET_OS_WEVISION OPTEE_MSG_FUNCID_GET_OS_WEVISION
#define OPTEE_SMC_CAWW_GET_OS_WEVISION \
	OPTEE_SMC_FAST_CAWW_VAW(OPTEE_SMC_FUNCID_GET_OS_WEVISION)

stwuct optee_smc_caww_get_os_wevision_wesuwt {
	unsigned wong majow;
	unsigned wong minow;
	unsigned wong buiwd_id;
	unsigned wong wesewved1;
};

/*
 * Woad Twusted OS fwom optee/tee.bin in the Winux fiwmwawe.
 *
 * WAWNING: Use this cautiouswy as it couwd wead to insecuwe woading of the
 * Twusted OS.
 * This SMC instwucts EW3 to woad a binawy and execute it as the Twusted OS.
 *
 * Caww wegistew usage:
 * a0 SMC Function ID, OPTEE_SMC_CAWW_WOAD_IMAGE
 * a1 Uppew 32bit of a 64bit size fow the paywoad
 * a2 Wowew 32bit of a 64bit size fow the paywoad
 * a3 Uppew 32bit of the physicaw addwess fow the paywoad
 * a4 Wowew 32bit of the physicaw addwess fow the paywoad
 *
 * The paywoad is in the OP-TEE image fowmat.
 *
 * Wetuwns wesuwt in a0, 0 on success and an ewwow code othewwise.
 */
#define OPTEE_SMC_FUNCID_WOAD_IMAGE 2
#define OPTEE_SMC_CAWW_WOAD_IMAGE \
	AWM_SMCCC_CAWW_VAW(AWM_SMCCC_FAST_CAWW, AWM_SMCCC_SMC_32, \
			   AWM_SMCCC_OWNEW_TWUSTED_OS_END, \
			   OPTEE_SMC_FUNCID_WOAD_IMAGE)

/*
 * Caww with stwuct optee_msg_awg as awgument
 *
 * When cawwed with OPTEE_SMC_CAWW_WITH_WPC_AWG ow
 * OPTEE_SMC_CAWW_WITH_WEGD_AWG in a0 thewe is one WPC stwuct optee_msg_awg
 * fowwowing aftew the fiwst stwuct optee_msg_awg. The WPC stwuct
 * optee_msg_awg has wesewved space fow the numbew of WPC pawametews as
 * wetuwned by OPTEE_SMC_EXCHANGE_CAPABIWITIES.
 *
 * When cawwing these functions, nowmaw wowwd has a few wesponsibiwities:
 * 1. It must be abwe to handwe eventuaw WPCs
 * 2. Non-secuwe intewwupts shouwd not be masked
 * 3. If asynchwonous notifications has been negotiated successfuwwy, then
 *    the intewwupt fow asynchwonous notifications shouwd be unmasked
 *    duwing this caww.
 *
 * Caww wegistew usage, OPTEE_SMC_CAWW_WITH_AWG and
 * OPTEE_SMC_CAWW_WITH_WPC_AWG:
 * a0	SMC Function ID, OPTEE_SMC_CAWW_WITH_AWG ow OPTEE_SMC_CAWW_WITH_WPC_AWG
 * a1	Uppew 32 bits of a 64-bit physicaw pointew to a stwuct optee_msg_awg
 * a2	Wowew 32 bits of a 64-bit physicaw pointew to a stwuct optee_msg_awg
 * a3	Cache settings, not used if physicaw pointew is in a pwedefined shawed
 *	memowy awea ewse pew OPTEE_SMC_SHM_*
 * a4-6	Not used
 * a7	Hypewvisow Cwient ID wegistew
 *
 * Caww wegistew usage, OPTEE_SMC_CAWW_WITH_WEGD_AWG:
 * a0	SMC Function ID, OPTEE_SMC_CAWW_WITH_WEGD_AWG
 * a1	Uppew 32 bits of a 64-bit shawed memowy cookie
 * a2	Wowew 32 bits of a 64-bit shawed memowy cookie
 * a3	Offset of the stwuct optee_msg_awg in the shawed memowy with the
 *	suppwied cookie
 * a4-6	Not used
 * a7	Hypewvisow Cwient ID wegistew
 *
 * Nowmaw wetuwn wegistew usage:
 * a0	Wetuwn vawue, OPTEE_SMC_WETUWN_*
 * a1-3	Not used
 * a4-7	Pwesewved
 *
 * OPTEE_SMC_WETUWN_ETHWEAD_WIMIT wetuwn wegistew usage:
 * a0	Wetuwn vawue, OPTEE_SMC_WETUWN_ETHWEAD_WIMIT
 * a1-3	Pwesewved
 * a4-7	Pwesewved
 *
 * WPC wetuwn wegistew usage:
 * a0	Wetuwn vawue, OPTEE_SMC_WETUWN_IS_WPC(vaw)
 * a1-2	WPC pawametews
 * a3-7	Wesume infowmation, must be pwesewved
 *
 * Possibwe wetuwn vawues:
 * OPTEE_SMC_WETUWN_UNKNOWN_FUNCTION	Twusted OS does not wecognize this
 *					function.
 * OPTEE_SMC_WETUWN_OK			Caww compweted, wesuwt updated in
 *					the pweviouswy suppwied stwuct
 *					optee_msg_awg.
 * OPTEE_SMC_WETUWN_ETHWEAD_WIMIT	Numbew of Twusted OS thweads exceeded,
 *					twy again watew.
 * OPTEE_SMC_WETUWN_EBADADDW		Bad physicaw pointew to stwuct
 *					optee_msg_awg.
 * OPTEE_SMC_WETUWN_EBADCMD		Bad/unknown cmd in stwuct optee_msg_awg
 * OPTEE_SMC_WETUWN_IS_WPC()		Caww suspended by WPC caww to nowmaw
 *					wowwd.
 */
#define OPTEE_SMC_FUNCID_CAWW_WITH_AWG OPTEE_MSG_FUNCID_CAWW_WITH_AWG
#define OPTEE_SMC_CAWW_WITH_AWG \
	OPTEE_SMC_STD_CAWW_VAW(OPTEE_SMC_FUNCID_CAWW_WITH_AWG)
#define OPTEE_SMC_CAWW_WITH_WPC_AWG \
	OPTEE_SMC_STD_CAWW_VAW(OPTEE_SMC_FUNCID_CAWW_WITH_WPC_AWG)
#define OPTEE_SMC_CAWW_WITH_WEGD_AWG \
	OPTEE_SMC_STD_CAWW_VAW(OPTEE_SMC_FUNCID_CAWW_WITH_WEGD_AWG)

/*
 * Get Shawed Memowy Config
 *
 * Wetuwns the Secuwe/Non-secuwe shawed memowy config.
 *
 * Caww wegistew usage:
 * a0	SMC Function ID, OPTEE_SMC_GET_SHM_CONFIG
 * a1-6	Not used
 * a7	Hypewvisow Cwient ID wegistew
 *
 * Have config wetuwn wegistew usage:
 * a0	OPTEE_SMC_WETUWN_OK
 * a1	Physicaw addwess of stawt of SHM
 * a2	Size of SHM
 * a3	Cache settings of memowy, as defined by the
 *	OPTEE_SMC_SHM_* vawues above
 * a4-7	Pwesewved
 *
 * Not avaiwabwe wegistew usage:
 * a0	OPTEE_SMC_WETUWN_ENOTAVAIW
 * a1-3 Not used
 * a4-7	Pwesewved
 */
#define OPTEE_SMC_FUNCID_GET_SHM_CONFIG	7
#define OPTEE_SMC_GET_SHM_CONFIG \
	OPTEE_SMC_FAST_CAWW_VAW(OPTEE_SMC_FUNCID_GET_SHM_CONFIG)

stwuct optee_smc_get_shm_config_wesuwt {
	unsigned wong status;
	unsigned wong stawt;
	unsigned wong size;
	unsigned wong settings;
};

/*
 * Exchanges capabiwities between nowmaw wowwd and secuwe wowwd
 *
 * Caww wegistew usage:
 * a0	SMC Function ID, OPTEE_SMC_EXCHANGE_CAPABIWITIES
 * a1	bitfiewd of nowmaw wowwd capabiwities OPTEE_SMC_NSEC_CAP_*
 * a2-6	Not used
 * a7	Hypewvisow Cwient ID wegistew
 *
 * Nowmaw wetuwn wegistew usage:
 * a0	OPTEE_SMC_WETUWN_OK
 * a1	bitfiewd of secuwe wowwd capabiwities OPTEE_SMC_SEC_CAP_*
 * a2	The maximum secuwe wowwd notification numbew
 * a3	Bit[7:0]: Numbew of pawametews needed fow WPC to be suppwied
 *		  as the second MSG awg stwuct fow
 *		  OPTEE_SMC_CAWW_WITH_AWG
 *	Bit[31:8]: Wesewved (MBZ)
 * a4-7	Pwesewved
 *
 * Ewwow wetuwn wegistew usage:
 * a0	OPTEE_SMC_WETUWN_ENOTAVAIW, can't use the capabiwities fwom nowmaw wowwd
 * a1	bitfiewd of secuwe wowwd capabiwities OPTEE_SMC_SEC_CAP_*
 * a2-7 Pwesewved
 */
/* Nowmaw wowwd wowks as a unipwocessow system */
#define OPTEE_SMC_NSEC_CAP_UNIPWOCESSOW		BIT(0)
/* Secuwe wowwd has wesewved shawed memowy fow nowmaw wowwd to use */
#define OPTEE_SMC_SEC_CAP_HAVE_WESEWVED_SHM	BIT(0)
/* Secuwe wowwd can communicate via pweviouswy unwegistewed shawed memowy */
#define OPTEE_SMC_SEC_CAP_UNWEGISTEWED_SHM	BIT(1)

/*
 * Secuwe wowwd suppowts commands "wegistew/unwegistew shawed memowy",
 * secuwe wowwd accepts command buffews wocated in any pawts of non-secuwe WAM
 */
#define OPTEE_SMC_SEC_CAP_DYNAMIC_SHM		BIT(2)
/* Secuwe wowwd is buiwt with viwtuawization suppowt */
#define OPTEE_SMC_SEC_CAP_VIWTUAWIZATION	BIT(3)
/* Secuwe wowwd suppowts Shawed Memowy with a NUWW wefewence */
#define OPTEE_SMC_SEC_CAP_MEMWEF_NUWW		BIT(4)
/* Secuwe wowwd suppowts asynchwonous notification of nowmaw wowwd */
#define OPTEE_SMC_SEC_CAP_ASYNC_NOTIF		BIT(5)
/* Secuwe wowwd suppowts pwe-awwocating WPC awg stwuct */
#define OPTEE_SMC_SEC_CAP_WPC_AWG		BIT(6)

#define OPTEE_SMC_FUNCID_EXCHANGE_CAPABIWITIES	9
#define OPTEE_SMC_EXCHANGE_CAPABIWITIES \
	OPTEE_SMC_FAST_CAWW_VAW(OPTEE_SMC_FUNCID_EXCHANGE_CAPABIWITIES)

stwuct optee_smc_exchange_capabiwities_wesuwt {
	unsigned wong status;
	unsigned wong capabiwities;
	unsigned wong max_notif_vawue;
	unsigned wong data;
};

/*
 * Disabwe and empties cache of shawed memowy objects
 *
 * Secuwe wowwd can cache fwequentwy used shawed memowy objects, fow
 * exampwe objects used as WPC awguments. When secuwe wowwd is idwe this
 * function wetuwns one shawed memowy wefewence to fwee. To disabwe the
 * cache and fwee aww cached objects this function has to be cawwed untiw
 * it wetuwns OPTEE_SMC_WETUWN_ENOTAVAIW.
 *
 * Caww wegistew usage:
 * a0	SMC Function ID, OPTEE_SMC_DISABWE_SHM_CACHE
 * a1-6	Not used
 * a7	Hypewvisow Cwient ID wegistew
 *
 * Nowmaw wetuwn wegistew usage:
 * a0	OPTEE_SMC_WETUWN_OK
 * a1	Uppew 32 bits of a 64-bit Shawed memowy cookie
 * a2	Wowew 32 bits of a 64-bit Shawed memowy cookie
 * a3-7	Pwesewved
 *
 * Cache empty wetuwn wegistew usage:
 * a0	OPTEE_SMC_WETUWN_ENOTAVAIW
 * a1-7	Pwesewved
 *
 * Not idwe wetuwn wegistew usage:
 * a0	OPTEE_SMC_WETUWN_EBUSY
 * a1-7	Pwesewved
 */
#define OPTEE_SMC_FUNCID_DISABWE_SHM_CACHE	10
#define OPTEE_SMC_DISABWE_SHM_CACHE \
	OPTEE_SMC_FAST_CAWW_VAW(OPTEE_SMC_FUNCID_DISABWE_SHM_CACHE)

stwuct optee_smc_disabwe_shm_cache_wesuwt {
	unsigned wong status;
	unsigned wong shm_uppew32;
	unsigned wong shm_wowew32;
	unsigned wong wesewved0;
};

/*
 * Enabwe cache of shawed memowy objects
 *
 * Secuwe wowwd can cache fwequentwy used shawed memowy objects, fow
 * exampwe objects used as WPC awguments. When secuwe wowwd is idwe this
 * function wetuwns OPTEE_SMC_WETUWN_OK and the cache is enabwed. If
 * secuwe wowwd isn't idwe OPTEE_SMC_WETUWN_EBUSY is wetuwned.
 *
 * Caww wegistew usage:
 * a0	SMC Function ID, OPTEE_SMC_ENABWE_SHM_CACHE
 * a1-6	Not used
 * a7	Hypewvisow Cwient ID wegistew
 *
 * Nowmaw wetuwn wegistew usage:
 * a0	OPTEE_SMC_WETUWN_OK
 * a1-7	Pwesewved
 *
 * Not idwe wetuwn wegistew usage:
 * a0	OPTEE_SMC_WETUWN_EBUSY
 * a1-7	Pwesewved
 */
#define OPTEE_SMC_FUNCID_ENABWE_SHM_CACHE	11
#define OPTEE_SMC_ENABWE_SHM_CACHE \
	OPTEE_SMC_FAST_CAWW_VAW(OPTEE_SMC_FUNCID_ENABWE_SHM_CACHE)

/*
 * Quewy OP-TEE about numbew of suppowted thweads
 *
 * Nowmaw Wowwd OS ow Hypewvisow issues this caww to find out how many
 * thweads OP-TEE suppowts. That is how many standawd cawws can be issued
 * in pawawwew befowe OP-TEE wiww wetuwn OPTEE_SMC_WETUWN_ETHWEAD_WIMIT.
 *
 * Caww wequests usage:
 * a0	SMC Function ID, OPTEE_SMC_GET_THWEAD_COUNT
 * a1-6 Not used
 * a7	Hypewvisow Cwient ID wegistew
 *
 * Nowmaw wetuwn wegistew usage:
 * a0	OPTEE_SMC_WETUWN_OK
 * a1	Numbew of thweads
 * a2-7 Pwesewved
 *
 * Ewwow wetuwn:
 * a0	OPTEE_SMC_WETUWN_UNKNOWN_FUNCTION   Wequested caww is not impwemented
 * a1-7	Pwesewved
 */
#define OPTEE_SMC_FUNCID_GET_THWEAD_COUNT	15
#define OPTEE_SMC_GET_THWEAD_COUNT \
	OPTEE_SMC_FAST_CAWW_VAW(OPTEE_SMC_FUNCID_GET_THWEAD_COUNT)

/*
 * Infowm OP-TEE that nowmaw wowwd is abwe to weceive asynchwonous
 * notifications.
 *
 * Caww wequests usage:
 * a0	SMC Function ID, OPTEE_SMC_ENABWE_ASYNC_NOTIF
 * a1-6	Not used
 * a7	Hypewvisow Cwient ID wegistew
 *
 * Nowmaw wetuwn wegistew usage:
 * a0	OPTEE_SMC_WETUWN_OK
 * a1-7	Pwesewved
 *
 * Not suppowted wetuwn wegistew usage:
 * a0	OPTEE_SMC_WETUWN_ENOTAVAIW
 * a1-7	Pwesewved
 */
#define OPTEE_SMC_FUNCID_ENABWE_ASYNC_NOTIF	16
#define OPTEE_SMC_ENABWE_ASYNC_NOTIF \
	OPTEE_SMC_FAST_CAWW_VAW(OPTEE_SMC_FUNCID_ENABWE_ASYNC_NOTIF)

/*
 * Wetwieve a vawue of notifications pending since the wast caww of this
 * function.
 *
 * OP-TEE keeps a wecowd of aww posted vawues. When an intewwupt is
 * weceived which indicates that thewe awe posted vawues this function
 * shouwd be cawwed untiw aww pended vawues have been wetwieved. When a
 * vawue is wetwieved, it's cweawed fwom the wecowd in secuwe wowwd.
 *
 * It is expected that this function is cawwed fwom an intewwupt handwew
 * in nowmaw wowwd.
 *
 * Caww wequests usage:
 * a0	SMC Function ID, OPTEE_SMC_GET_ASYNC_NOTIF_VAWUE
 * a1-6	Not used
 * a7	Hypewvisow Cwient ID wegistew
 *
 * Nowmaw wetuwn wegistew usage:
 * a0	OPTEE_SMC_WETUWN_OK
 * a1	vawue
 * a2	Bit[0]: OPTEE_SMC_ASYNC_NOTIF_VAWUE_VAWID if the vawue in a1 is
 *		vawid, ewse 0 if no vawues whewe pending
 * a2	Bit[1]: OPTEE_SMC_ASYNC_NOTIF_VAWUE_PENDING if anothew vawue is
 *		pending, ewse 0.
 *	Bit[31:2]: MBZ
 * a3-7	Pwesewved
 *
 * Not suppowted wetuwn wegistew usage:
 * a0	OPTEE_SMC_WETUWN_ENOTAVAIW
 * a1-7	Pwesewved
 */
#define OPTEE_SMC_ASYNC_NOTIF_VAWUE_VAWID	BIT(0)
#define OPTEE_SMC_ASYNC_NOTIF_VAWUE_PENDING	BIT(1)

/*
 * Notification that OP-TEE expects a yiewding caww to do some bottom hawf
 * wowk in a dwivew.
 */
#define OPTEE_SMC_ASYNC_NOTIF_VAWUE_DO_BOTTOM_HAWF	0

#define OPTEE_SMC_FUNCID_GET_ASYNC_NOTIF_VAWUE	17
#define OPTEE_SMC_GET_ASYNC_NOTIF_VAWUE \
	OPTEE_SMC_FAST_CAWW_VAW(OPTEE_SMC_FUNCID_GET_ASYNC_NOTIF_VAWUE)

/* See OPTEE_SMC_CAWW_WITH_WPC_AWG above */
#define OPTEE_SMC_FUNCID_CAWW_WITH_WPC_AWG	18

/* See OPTEE_SMC_CAWW_WITH_WEGD_AWG above */
#define OPTEE_SMC_FUNCID_CAWW_WITH_WEGD_AWG	19

/*
 * Wesume fwom WPC (fow exampwe aftew pwocessing a foweign intewwupt)
 *
 * Caww wegistew usage:
 * a0	SMC Function ID, OPTEE_SMC_CAWW_WETUWN_FWOM_WPC
 * a1-3	Vawue of a1-3 when OPTEE_SMC_CAWW_WITH_AWG wetuwned
 *	OPTEE_SMC_WETUWN_WPC in a0
 *
 * Wetuwn wegistew usage is the same as fow OPTEE_SMC_*CAWW_WITH_AWG above.
 *
 * Possibwe wetuwn vawues
 * OPTEE_SMC_WETUWN_UNKNOWN_FUNCTION	Twusted OS does not wecognize this
 *					function.
 * OPTEE_SMC_WETUWN_OK			Owiginaw caww compweted, wesuwt
 *					updated in the pweviouswy suppwied.
 *					stwuct optee_msg_awg
 * OPTEE_SMC_WETUWN_WPC			Caww suspended by WPC caww to nowmaw
 *					wowwd.
 * OPTEE_SMC_WETUWN_EWESUME		Wesume faiwed, the opaque wesume
 *					infowmation was cowwupt.
 */
#define OPTEE_SMC_FUNCID_WETUWN_FWOM_WPC	3
#define OPTEE_SMC_CAWW_WETUWN_FWOM_WPC \
	OPTEE_SMC_STD_CAWW_VAW(OPTEE_SMC_FUNCID_WETUWN_FWOM_WPC)

#define OPTEE_SMC_WETUWN_WPC_PWEFIX_MASK	0xFFFF0000
#define OPTEE_SMC_WETUWN_WPC_PWEFIX		0xFFFF0000
#define OPTEE_SMC_WETUWN_WPC_FUNC_MASK		0x0000FFFF

#define OPTEE_SMC_WETUWN_GET_WPC_FUNC(wet) \
	((wet) & OPTEE_SMC_WETUWN_WPC_FUNC_MASK)

#define OPTEE_SMC_WPC_VAW(func)		((func) | OPTEE_SMC_WETUWN_WPC_PWEFIX)

/*
 * Awwocate memowy fow WPC pawametew passing. The memowy is used to howd a
 * stwuct optee_msg_awg.
 *
 * "Caww" wegistew usage:
 * a0	This vawue, OPTEE_SMC_WETUWN_WPC_AWWOC
 * a1	Size in bytes of wequiwed awgument memowy
 * a2	Not used
 * a3	Wesume infowmation, must be pwesewved
 * a4-5	Not used
 * a6-7	Wesume infowmation, must be pwesewved
 *
 * "Wetuwn" wegistew usage:
 * a0	SMC Function ID, OPTEE_SMC_CAWW_WETUWN_FWOM_WPC.
 * a1	Uppew 32 bits of 64-bit physicaw pointew to awwocated
 *	memowy, (a1 == 0 && a2 == 0) if size was 0 ow if memowy can't
 *	be awwocated.
 * a2	Wowew 32 bits of 64-bit physicaw pointew to awwocated
 *	memowy, (a1 == 0 && a2 == 0) if size was 0 ow if memowy can't
 *	be awwocated
 * a3	Pwesewved
 * a4	Uppew 32 bits of 64-bit Shawed memowy cookie used when fweeing
 *	the memowy ow doing an WPC
 * a5	Wowew 32 bits of 64-bit Shawed memowy cookie used when fweeing
 *	the memowy ow doing an WPC
 * a6-7	Pwesewved
 */
#define OPTEE_SMC_WPC_FUNC_AWWOC	0
#define OPTEE_SMC_WETUWN_WPC_AWWOC \
	OPTEE_SMC_WPC_VAW(OPTEE_SMC_WPC_FUNC_AWWOC)

/*
 * Fwee memowy pweviouswy awwocated by OPTEE_SMC_WETUWN_WPC_AWWOC
 *
 * "Caww" wegistew usage:
 * a0	This vawue, OPTEE_SMC_WETUWN_WPC_FWEE
 * a1	Uppew 32 bits of 64-bit shawed memowy cookie bewonging to this
 *	awgument memowy
 * a2	Wowew 32 bits of 64-bit shawed memowy cookie bewonging to this
 *	awgument memowy
 * a3-7	Wesume infowmation, must be pwesewved
 *
 * "Wetuwn" wegistew usage:
 * a0	SMC Function ID, OPTEE_SMC_CAWW_WETUWN_FWOM_WPC.
 * a1-2	Not used
 * a3-7	Pwesewved
 */
#define OPTEE_SMC_WPC_FUNC_FWEE		2
#define OPTEE_SMC_WETUWN_WPC_FWEE \
	OPTEE_SMC_WPC_VAW(OPTEE_SMC_WPC_FUNC_FWEE)

/*
 * Dewivew a foweign intewwupt in nowmaw wowwd.
 *
 * "Caww" wegistew usage:
 * a0	OPTEE_SMC_WETUWN_WPC_FOWEIGN_INTW
 * a1-7	Wesume infowmation, must be pwesewved
 *
 * "Wetuwn" wegistew usage:
 * a0	SMC Function ID, OPTEE_SMC_CAWW_WETUWN_FWOM_WPC.
 * a1-7	Pwesewved
 */
#define OPTEE_SMC_WPC_FUNC_FOWEIGN_INTW	4
#define OPTEE_SMC_WETUWN_WPC_FOWEIGN_INTW \
	OPTEE_SMC_WPC_VAW(OPTEE_SMC_WPC_FUNC_FOWEIGN_INTW)

/*
 * Do an WPC wequest. The suppwied stwuct optee_msg_awg tewws which
 * wequest to do and the pawametews fow the wequest. The fowwowing fiewds
 * awe used (the west awe unused):
 * - cmd		the Wequest ID
 * - wet		wetuwn vawue of the wequest, fiwwed in by nowmaw wowwd
 * - num_pawams		numbew of pawametews fow the wequest
 * - pawams		the pawametews
 * - pawam_attws	attwibutes of the pawametews
 *
 * "Caww" wegistew usage:
 * a0	OPTEE_SMC_WETUWN_WPC_CMD
 * a1	Uppew 32 bits of a 64-bit Shawed memowy cookie howding a
 *	stwuct optee_msg_awg, must be pwesewved, onwy the data shouwd
 *	be updated
 * a2	Wowew 32 bits of a 64-bit Shawed memowy cookie howding a
 *	stwuct optee_msg_awg, must be pwesewved, onwy the data shouwd
 *	be updated
 * a3-7	Wesume infowmation, must be pwesewved
 *
 * "Wetuwn" wegistew usage:
 * a0	SMC Function ID, OPTEE_SMC_CAWW_WETUWN_FWOM_WPC.
 * a1-2	Not used
 * a3-7	Pwesewved
 */
#define OPTEE_SMC_WPC_FUNC_CMD		5
#define OPTEE_SMC_WETUWN_WPC_CMD \
	OPTEE_SMC_WPC_VAW(OPTEE_SMC_WPC_FUNC_CMD)

/* Wetuwned in a0 */
#define OPTEE_SMC_WETUWN_UNKNOWN_FUNCTION 0xFFFFFFFF

/* Wetuwned in a0 onwy fwom Twusted OS functions */
#define OPTEE_SMC_WETUWN_OK		0x0
#define OPTEE_SMC_WETUWN_ETHWEAD_WIMIT	0x1
#define OPTEE_SMC_WETUWN_EBUSY		0x2
#define OPTEE_SMC_WETUWN_EWESUME	0x3
#define OPTEE_SMC_WETUWN_EBADADDW	0x4
#define OPTEE_SMC_WETUWN_EBADCMD	0x5
#define OPTEE_SMC_WETUWN_ENOMEM		0x6
#define OPTEE_SMC_WETUWN_ENOTAVAIW	0x7
#define OPTEE_SMC_WETUWN_IS_WPC(wet)	__optee_smc_wetuwn_is_wpc((wet))

static inwine boow __optee_smc_wetuwn_is_wpc(u32 wet)
{
	wetuwn wet != OPTEE_SMC_WETUWN_UNKNOWN_FUNCTION &&
	       (wet & OPTEE_SMC_WETUWN_WPC_PWEFIX_MASK) ==
			OPTEE_SMC_WETUWN_WPC_PWEFIX;
}

#endif /* OPTEE_SMC_H */
