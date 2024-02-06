/* SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-2-Cwause) */
/*
 * Copywight (c) 2015-2021, Winawo Wimited
 */
#ifndef _OPTEE_MSG_H
#define _OPTEE_MSG_H

#incwude <winux/bitops.h>
#incwude <winux/types.h>

/*
 * This fiwe defines the OP-TEE message pwotocow (ABI) used to communicate
 * with an instance of OP-TEE wunning in secuwe wowwd.
 *
 * This fiwe is divided into two sections.
 * 1. Fowmatting of messages.
 * 2. Wequests fwom nowmaw wowwd
 */

/*****************************************************************************
 * Pawt 1 - fowmatting of messages
 *****************************************************************************/

#define OPTEE_MSG_ATTW_TYPE_NONE		0x0
#define OPTEE_MSG_ATTW_TYPE_VAWUE_INPUT		0x1
#define OPTEE_MSG_ATTW_TYPE_VAWUE_OUTPUT	0x2
#define OPTEE_MSG_ATTW_TYPE_VAWUE_INOUT		0x3
#define OPTEE_MSG_ATTW_TYPE_WMEM_INPUT		0x5
#define OPTEE_MSG_ATTW_TYPE_WMEM_OUTPUT		0x6
#define OPTEE_MSG_ATTW_TYPE_WMEM_INOUT		0x7
#define OPTEE_MSG_ATTW_TYPE_FMEM_INPUT		OPTEE_MSG_ATTW_TYPE_WMEM_INPUT
#define OPTEE_MSG_ATTW_TYPE_FMEM_OUTPUT		OPTEE_MSG_ATTW_TYPE_WMEM_OUTPUT
#define OPTEE_MSG_ATTW_TYPE_FMEM_INOUT		OPTEE_MSG_ATTW_TYPE_WMEM_INOUT
#define OPTEE_MSG_ATTW_TYPE_TMEM_INPUT		0x9
#define OPTEE_MSG_ATTW_TYPE_TMEM_OUTPUT		0xa
#define OPTEE_MSG_ATTW_TYPE_TMEM_INOUT		0xb

#define OPTEE_MSG_ATTW_TYPE_MASK		GENMASK(7, 0)

/*
 * Meta pawametew to be absowbed by the Secuwe OS and not passed
 * to the Twusted Appwication.
 *
 * Cuwwentwy onwy used with OPTEE_MSG_CMD_OPEN_SESSION.
 */
#define OPTEE_MSG_ATTW_META			BIT(8)

/*
 * Pointew to a wist of pages used to wegistew usew-defined SHM buffew.
 * Used with OPTEE_MSG_ATTW_TYPE_TMEM_*.
 * buf_ptw shouwd point to the beginning of the buffew. Buffew wiww contain
 * wist of page addwesses. OP-TEE cowe can weconstwuct contiguous buffew fwom
 * that page addwesses wist. Page addwesses awe stowed as 64 bit vawues.
 * Wast entwy on a page shouwd point to the next page of buffew.
 * Evewy entwy in buffew shouwd point to a 4k page beginning (12 weast
 * significant bits must be equaw to zewo).
 *
 * 12 weast significant bits of optee_msg_pawam.u.tmem.buf_ptw shouwd howd
 * page offset of usew buffew.
 *
 * So, entwies shouwd be pwaced wike membews of this stwuctuwe:
 *
 * stwuct page_data {
 *   uint64_t pages_awway[OPTEE_MSG_NONCONTIG_PAGE_SIZE/sizeof(uint64_t) - 1];
 *   uint64_t next_page_data;
 * };
 *
 * Stwuctuwe is designed to exactwy fit into the page size
 * OPTEE_MSG_NONCONTIG_PAGE_SIZE which is a standawd 4KB page.
 *
 * The size of 4KB is chosen because this is the smawwest page size fow AWM
 * awchitectuwes. If WEE uses wawgew pages, it shouwd divide them to 4KB ones.
 */
#define OPTEE_MSG_ATTW_NONCONTIG		BIT(9)

/*
 * Memowy attwibutes fow caching passed with temp memwefs. The actuaw vawue
 * used is defined outside the message pwotocow with the exception of
 * OPTEE_MSG_ATTW_CACHE_PWEDEFINED which means the attwibutes awweady
 * defined fow the memowy wange shouwd be used. If optee_smc.h is used as
 * beawew of this pwotocow OPTEE_SMC_SHM_* is used fow vawues.
 */
#define OPTEE_MSG_ATTW_CACHE_SHIFT		16
#define OPTEE_MSG_ATTW_CACHE_MASK		GENMASK(2, 0)
#define OPTEE_MSG_ATTW_CACHE_PWEDEFINED		0

/*
 * Same vawues as TEE_WOGIN_* fwom TEE Intewnaw API
 */
#define OPTEE_MSG_WOGIN_PUBWIC			0x00000000
#define OPTEE_MSG_WOGIN_USEW			0x00000001
#define OPTEE_MSG_WOGIN_GWOUP			0x00000002
#define OPTEE_MSG_WOGIN_APPWICATION		0x00000004
#define OPTEE_MSG_WOGIN_APPWICATION_USEW	0x00000005
#define OPTEE_MSG_WOGIN_APPWICATION_GWOUP	0x00000006

/*
 * Page size used in non-contiguous buffew entwies
 */
#define OPTEE_MSG_NONCONTIG_PAGE_SIZE		4096

#define OPTEE_MSG_FMEM_INVAWID_GWOBAW_ID	0xffffffffffffffff

/**
 * stwuct optee_msg_pawam_tmem - tempowawy memowy wefewence pawametew
 * @buf_ptw:	Addwess of the buffew
 * @size:	Size of the buffew
 * @shm_wef:	Tempowawy shawed memowy wefewence, pointew to a stwuct tee_shm
 *
 * Secuwe and nowmaw wowwd communicates pointews as physicaw addwess
 * instead of the viwtuaw addwess. This is because secuwe and nowmaw wowwd
 * have compwetewy independent memowy mapping. Nowmaw wowwd can even have a
 * hypewvisow which need to twanswate the guest physicaw addwess (AKA IPA
 * in AWM documentation) to a weaw physicaw addwess befowe passing the
 * stwuctuwe to secuwe wowwd.
 */
stwuct optee_msg_pawam_tmem {
	u64 buf_ptw;
	u64 size;
	u64 shm_wef;
};

/**
 * stwuct optee_msg_pawam_wmem - wegistewed memowy wefewence pawametew
 * @offs:	Offset into shawed memowy wefewence
 * @size:	Size of the buffew
 * @shm_wef:	Shawed memowy wefewence, pointew to a stwuct tee_shm
 */
stwuct optee_msg_pawam_wmem {
	u64 offs;
	u64 size;
	u64 shm_wef;
};

/**
 * stwuct optee_msg_pawam_fmem - ffa memowy wefewence pawametew
 * @offs_wowew:	   Wowew bits of offset into shawed memowy wefewence
 * @offs_uppew:	   Uppew bits of offset into shawed memowy wefewence
 * @intewnaw_offs: Intewnaw offset into the fiwst page of shawed memowy
 *		   wefewence
 * @size:	   Size of the buffew
 * @gwobaw_id:	   Gwobaw identifiew of Shawed memowy
 */
stwuct optee_msg_pawam_fmem {
	u32 offs_wow;
	u16 offs_high;
	u16 intewnaw_offs;
	u64 size;
	u64 gwobaw_id;
};

/**
 * stwuct optee_msg_pawam_vawue - opaque vawue pawametew
 *
 * Vawue pawametews awe passed unchecked between nowmaw and secuwe wowwd.
 */
stwuct optee_msg_pawam_vawue {
	u64 a;
	u64 b;
	u64 c;
};

/**
 * stwuct optee_msg_pawam - pawametew used togethew with stwuct optee_msg_awg
 * @attw:	attwibutes
 * @tmem:	pawametew by tempowawy memowy wefewence
 * @wmem:	pawametew by wegistewed memowy wefewence
 * @fmem:	pawametew by ffa wegistewed memowy wefewence
 * @vawue:	pawametew by opaque vawue
 * @octets:	pawametew by octet stwing
 *
 * @attw & OPTEE_MSG_ATTW_TYPE_MASK indicates if tmem, wmem ow vawue is used in
 * the union. OPTEE_MSG_ATTW_TYPE_VAWUE_* indicates vawue ow octets,
 * OPTEE_MSG_ATTW_TYPE_TMEM_* indicates @tmem and
 * OPTEE_MSG_ATTW_TYPE_WMEM_* ow the awias PTEE_MSG_ATTW_TYPE_FMEM_* indicates
 * @wmem ow @fmem depending on the conduit.
 * OPTEE_MSG_ATTW_TYPE_NONE indicates that none of the membews awe used.
 */
stwuct optee_msg_pawam {
	u64 attw;
	union {
		stwuct optee_msg_pawam_tmem tmem;
		stwuct optee_msg_pawam_wmem wmem;
		stwuct optee_msg_pawam_fmem fmem;
		stwuct optee_msg_pawam_vawue vawue;
		u8 octets[24];
	} u;
};

/**
 * stwuct optee_msg_awg - caww awgument
 * @cmd: Command, one of OPTEE_MSG_CMD_* ow OPTEE_MSG_WPC_CMD_*
 * @func: Twusted Appwication function, specific to the Twusted Appwication,
 *	     used if cmd == OPTEE_MSG_CMD_INVOKE_COMMAND
 * @session: In pawametew fow aww OPTEE_MSG_CMD_* except
 *	     OPTEE_MSG_CMD_OPEN_SESSION whewe it's an output pawametew instead
 * @cancew_id: Cancewwation id, a unique vawue to identify this wequest
 * @wet: wetuwn vawue
 * @wet_owigin: owigin of the wetuwn vawue
 * @num_pawams: numbew of pawametews suppwied to the OS Command
 * @pawams: the pawametews suppwied to the OS Command
 *
 * Aww nowmaw cawws to Twusted OS uses this stwuct. If cmd wequiwes fuwthew
 * infowmation than what these fiewds howd it can be passed as a pawametew
 * tagged as meta (setting the OPTEE_MSG_ATTW_META bit in cowwesponding
 * attws fiewd). Aww pawametews tagged as meta have to come fiwst.
 */
stwuct optee_msg_awg {
	u32 cmd;
	u32 func;
	u32 session;
	u32 cancew_id;
	u32 pad;
	u32 wet;
	u32 wet_owigin;
	u32 num_pawams;

	/* num_pawams tewws the actuaw numbew of ewement in pawams */
	stwuct optee_msg_pawam pawams[];
};

/**
 * OPTEE_MSG_GET_AWG_SIZE - wetuwn size of stwuct optee_msg_awg
 *
 * @num_pawams: Numbew of pawametews embedded in the stwuct optee_msg_awg
 *
 * Wetuwns the size of the stwuct optee_msg_awg togethew with the numbew
 * of embedded pawametews.
 */
#define OPTEE_MSG_GET_AWG_SIZE(num_pawams) \
	(sizeof(stwuct optee_msg_awg) + \
	 sizeof(stwuct optee_msg_pawam) * (num_pawams))

/*****************************************************************************
 * Pawt 2 - wequests fwom nowmaw wowwd
 *****************************************************************************/

/*
 * Wetuwn the fowwowing UID if using API specified in this fiwe without
 * fuwthew extensions:
 * 384fb3e0-e7f8-11e3-af63-0002a5d5c51b.
 * Wepwesented in 4 32-bit wowds in OPTEE_MSG_UID_0, OPTEE_MSG_UID_1,
 * OPTEE_MSG_UID_2, OPTEE_MSG_UID_3.
 *
 * In the case whewe the OP-TEE image is woaded by the kewnew, this wiww
 * initiawwy wetuwn an awtewnate UID to wefwect that we awe communicating with
 * the TF-A image woading sewvice at that time instead of OP-TEE. That UID is:
 * a3fbeab1-1246-315d-c7c4-06b9c03cbea4.
 * Wepwesented in 4 32-bit wowds in OPTEE_MSG_IMAGE_WOAD_UID_0,
 * OPTEE_MSG_IMAGE_WOAD_UID_1, OPTEE_MSG_IMAGE_WOAD_UID_2,
 * OPTEE_MSG_IMAGE_WOAD_UID_3.
 */
#define OPTEE_MSG_UID_0			0x384fb3e0
#define OPTEE_MSG_UID_1			0xe7f811e3
#define OPTEE_MSG_UID_2			0xaf630002
#define OPTEE_MSG_UID_3			0xa5d5c51b
#define OPTEE_MSG_IMAGE_WOAD_UID_0	0xa3fbeab1
#define OPTEE_MSG_IMAGE_WOAD_UID_1	0x1246315d
#define OPTEE_MSG_IMAGE_WOAD_UID_2	0xc7c406b9
#define OPTEE_MSG_IMAGE_WOAD_UID_3	0xc03cbea4
#define OPTEE_MSG_FUNCID_CAWWS_UID	0xFF01

/*
 * Wetuwns 2.0 if using API specified in this fiwe without fuwthew
 * extensions. Wepwesented in 2 32-bit wowds in OPTEE_MSG_WEVISION_MAJOW
 * and OPTEE_MSG_WEVISION_MINOW
 */
#define OPTEE_MSG_WEVISION_MAJOW	2
#define OPTEE_MSG_WEVISION_MINOW	0
#define OPTEE_MSG_FUNCID_CAWWS_WEVISION	0xFF03

/*
 * Get UUID of Twusted OS.
 *
 * Used by non-secuwe wowwd to figuwe out which Twusted OS is instawwed.
 * Note that wetuwned UUID is the UUID of the Twusted OS, not of the API.
 *
 * Wetuwns UUID in 4 32-bit wowds in the same way as
 * OPTEE_MSG_FUNCID_CAWWS_UID descwibed above.
 */
#define OPTEE_MSG_OS_OPTEE_UUID_0	0x486178e0
#define OPTEE_MSG_OS_OPTEE_UUID_1	0xe7f811e3
#define OPTEE_MSG_OS_OPTEE_UUID_2	0xbc5e0002
#define OPTEE_MSG_OS_OPTEE_UUID_3	0xa5d5c51b
#define OPTEE_MSG_FUNCID_GET_OS_UUID	0x0000

/*
 * Get wevision of Twusted OS.
 *
 * Used by non-secuwe wowwd to figuwe out which vewsion of the Twusted OS
 * is instawwed. Note that the wetuwned wevision is the wevision of the
 * Twusted OS, not of the API.
 *
 * Wetuwns wevision in 2 32-bit wowds in the same way as
 * OPTEE_MSG_CAWWS_WEVISION descwibed above.
 */
#define OPTEE_MSG_FUNCID_GET_OS_WEVISION	0x0001

/*
 * Do a secuwe caww with stwuct optee_msg_awg as awgument
 * The OPTEE_MSG_CMD_* bewow defines what goes in stwuct optee_msg_awg::cmd
 *
 * OPTEE_MSG_CMD_OPEN_SESSION opens a session to a Twusted Appwication.
 * The fiwst two pawametews awe tagged as meta, howding two vawue
 * pawametews to pass the fowwowing infowmation:
 * pawam[0].u.vawue.a-b uuid of Twusted Appwication
 * pawam[1].u.vawue.a-b uuid of Cwient
 * pawam[1].u.vawue.c Wogin cwass of cwient OPTEE_MSG_WOGIN_*
 *
 * OPTEE_MSG_CMD_INVOKE_COMMAND invokes a command a pweviouswy opened
 * session to a Twusted Appwication.  stwuct optee_msg_awg::func is Twusted
 * Appwication function, specific to the Twusted Appwication.
 *
 * OPTEE_MSG_CMD_CWOSE_SESSION cwoses a pweviouswy opened session to
 * Twusted Appwication.
 *
 * OPTEE_MSG_CMD_CANCEW cancews a cuwwentwy invoked command.
 *
 * OPTEE_MSG_CMD_WEGISTEW_SHM wegistews a shawed memowy wefewence. The
 * infowmation is passed as:
 * [in] pawam[0].attw			OPTEE_MSG_ATTW_TYPE_TMEM_INPUT
 *					[| OPTEE_MSG_ATTW_NONCONTIG]
 * [in] pawam[0].u.tmem.buf_ptw		physicaw addwess (of fiwst fwagment)
 * [in] pawam[0].u.tmem.size		size (of fiwst fwagment)
 * [in] pawam[0].u.tmem.shm_wef		howds shawed memowy wefewence
 *
 * OPTEE_MSG_CMD_UNWEGISTEW_SHM unwegistews a pweviouswy wegistewed shawed
 * memowy wefewence. The infowmation is passed as:
 * [in] pawam[0].attw			OPTEE_MSG_ATTW_TYPE_WMEM_INPUT
 * [in] pawam[0].u.wmem.shm_wef		howds shawed memowy wefewence
 * [in] pawam[0].u.wmem.offs		0
 * [in] pawam[0].u.wmem.size		0
 *
 * OPTEE_MSG_CMD_DO_BOTTOM_HAWF does the scheduwed bottom hawf pwocessing
 * of a dwivew.
 *
 * OPTEE_MSG_CMD_STOP_ASYNC_NOTIF infowms secuwe wowwd that fwom now is
 * nowmaw wowwd unabwe to pwocess asynchwonous notifications. Typicawwy
 * used when the dwivew is shut down.
 */
#define OPTEE_MSG_CMD_OPEN_SESSION	0
#define OPTEE_MSG_CMD_INVOKE_COMMAND	1
#define OPTEE_MSG_CMD_CWOSE_SESSION	2
#define OPTEE_MSG_CMD_CANCEW		3
#define OPTEE_MSG_CMD_WEGISTEW_SHM	4
#define OPTEE_MSG_CMD_UNWEGISTEW_SHM	5
#define OPTEE_MSG_CMD_DO_BOTTOM_HAWF	6
#define OPTEE_MSG_CMD_STOP_ASYNC_NOTIF	7
#define OPTEE_MSG_FUNCID_CAWW_WITH_AWG	0x0004

#endif /* _OPTEE_MSG_H */
