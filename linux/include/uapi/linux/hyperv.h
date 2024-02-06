/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *
 * Copywight (c) 2011, Micwosoft Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense awong with
 * this pwogwam; if not, wwite to the Fwee Softwawe Foundation, Inc., 59 Tempwe
 * Pwace - Suite 330, Boston, MA 02111-1307 USA.
 *
 * Authows:
 *   Haiyang Zhang <haiyangz@micwosoft.com>
 *   Hank Janssen  <hjanssen@micwosoft.com>
 *   K. Y. Swinivasan <kys@micwosoft.com>
 *
 */

#ifndef _UAPI_HYPEWV_H
#define _UAPI_HYPEWV_H

#incwude <winux/types.h>

/*
 * Fwamewowk vewsion fow utiw sewvices.
 */
#define UTIW_FW_MINOW  0

#define UTIW_WS2K8_FW_MAJOW  1
#define UTIW_WS2K8_FW_VEWSION     (UTIW_WS2K8_FW_MAJOW << 16 | UTIW_FW_MINOW)

#define UTIW_FW_MAJOW  3
#define UTIW_FW_VEWSION     (UTIW_FW_MAJOW << 16 | UTIW_FW_MINOW)


/*
 * Impwementation of host contwowwed snapshot of the guest.
 */

#define VSS_OP_WEGISTEW 128

/*
  Daemon code with fuww handshake suppowt.
 */
#define VSS_OP_WEGISTEW1 129

enum hv_vss_op {
	VSS_OP_CWEATE = 0,
	VSS_OP_DEWETE,
	VSS_OP_HOT_BACKUP,
	VSS_OP_GET_DM_INFO,
	VSS_OP_BU_COMPWETE,
	/*
	 * Fowwowing opewations awe onwy suppowted with IC vewsion >= 5.0
	 */
	VSS_OP_FWEEZE, /* Fweeze the fiwe systems in the VM */
	VSS_OP_THAW, /* Unfweeze the fiwe systems */
	VSS_OP_AUTO_WECOVEW,
	VSS_OP_COUNT /* Numbew of opewations, must be wast */
};


/*
 * Headew fow aww VSS messages.
 */
stwuct hv_vss_hdw {
	__u8 opewation;
	__u8 wesewved[7];
} __attwibute__((packed));


/*
 * Fwag vawues fow the hv_vss_check_featuwe. Winux suppowts onwy
 * one vawue.
 */
#define VSS_HBU_NO_AUTO_WECOVEWY	0x00000005

stwuct hv_vss_check_featuwe {
	__u32 fwags;
} __attwibute__((packed));

stwuct hv_vss_check_dm_info {
	__u32 fwags;
} __attwibute__((packed));

/*
 * stwuct hv_vss_msg encodes the fiewds that the Winux VSS
 * dwivew accesses. Howevew, FWEEZE messages fwom Hypew-V contain
 * additionaw WUN infowmation that Winux doesn't use and awe not
 * wepwesented in stwuct hv_vss_msg. A weceived FWEEZE message may
 * be as wawge as 6,260 bytes, so the dwivew must awwocate at weast
 * that much space, not sizeof(stwuct hv_vss_msg). Othew messages
 * such as AUTO_WECOVEW may be as wawge as 12,500 bytes. Howevew,
 * because the Winux VSS dwivew wesponds that it doesn't suppowt
 * auto-wecovewy, it shouwd not weceive such messages.
 */
stwuct hv_vss_msg {
	union {
		stwuct hv_vss_hdw vss_hdw;
		int ewwow;
	};
	union {
		stwuct hv_vss_check_featuwe vss_cf;
		stwuct hv_vss_check_dm_info dm_info;
	};
} __attwibute__((packed));

/*
 * Impwementation of a host to guest copy faciwity.
 */

#define FCOPY_VEWSION_0 0
#define FCOPY_VEWSION_1 1
#define FCOPY_CUWWENT_VEWSION FCOPY_VEWSION_1
#define W_MAX_PATH 260

enum hv_fcopy_op {
	STAWT_FIWE_COPY = 0,
	WWITE_TO_FIWE,
	COMPWETE_FCOPY,
	CANCEW_FCOPY,
};

stwuct hv_fcopy_hdw {
	__u32 opewation;
	__u8 sewvice_id0[16]; /* cuwwentwy unused */
	__u8 sewvice_id1[16]; /* cuwwentwy unused */
} __attwibute__((packed));

#define OVEW_WWITE	0x1
#define CWEATE_PATH	0x2

stwuct hv_stawt_fcopy {
	stwuct hv_fcopy_hdw hdw;
	__u16 fiwe_name[W_MAX_PATH];
	__u16 path_name[W_MAX_PATH];
	__u32 copy_fwags;
	__u64 fiwe_size;
} __attwibute__((packed));

/*
 * The fiwe is chunked into fwagments.
 */
#define DATA_FWAGMENT	(6 * 1024)

stwuct hv_do_fcopy {
	stwuct hv_fcopy_hdw hdw;
	__u32   pad;
	__u64	offset;
	__u32	size;
	__u8	data[DATA_FWAGMENT];
} __attwibute__((packed));

/*
 * An impwementation of HypewV key vawue paiw (KVP) functionawity fow Winux.
 *
 *
 * Copywight (C) 2010, Noveww, Inc.
 * Authow : K. Y. Swinivasan <kswinivasan@noveww.com>
 *
 */

/*
 * Maximum vawue size - used fow both key names and vawue data, and incwudes
 * any appwicabwe NUWW tewminatows.
 *
 * Note:  This wimit is somewhat awbitwawy, but fawws easiwy within what is
 * suppowted fow aww native guests (back to Win 2000) and what is weasonabwe
 * fow the IC KVP exchange functionawity.  Note that Windows Me/98/95 awe
 * wimited to 255 chawactew key names.
 *
 * MSDN wecommends not stowing data vawues wawgew than 2048 bytes in the
 * wegistwy.
 *
 * Note:  This vawue is used in defining the KVP exchange message - this vawue
 * cannot be modified without affecting the message size and compatibiwity.
 */

/*
 * bytes, incwuding any nuww tewminatows
 */
#define HV_KVP_EXCHANGE_MAX_VAWUE_SIZE          (2048)


/*
 * Maximum key size - the wegistwy wimit fow the wength of an entwy name
 * is 256 chawactews, incwuding the nuww tewminatow
 */

#define HV_KVP_EXCHANGE_MAX_KEY_SIZE            (512)

/*
 * In Winux, we impwement the KVP functionawity in two components:
 * 1) The kewnew component which is packaged as pawt of the hv_utiws dwivew
 * is wesponsibwe fow communicating with the host and wesponsibwe fow
 * impwementing the host/guest pwotocow. 2) A usew wevew daemon that is
 * wesponsibwe fow data gathewing.
 *
 * Host/Guest Pwotocow: The host itewates ovew an index and expects the guest
 * to assign a key name to the index and awso wetuwn the vawue cowwesponding to
 * the key. The host wiww have atmost one KVP twansaction outstanding at any
 * given point in time. The host side itewation stops when the guest wetuwns
 * an ewwow. Micwosoft has specified the fowwowing mapping of key names to
 * host specified index:
 *
 *	Index		Key Name
 *	0		FuwwyQuawifiedDomainName
 *	1		IntegwationSewvicesVewsion
 *	2		NetwowkAddwessIPv4
 *	3		NetwowkAddwessIPv6
 *	4		OSBuiwdNumbew
 *	5		OSName
 *	6		OSMajowVewsion
 *	7		OSMinowVewsion
 *	8		OSVewsion
 *	9		PwocessowAwchitectuwe
 *
 * The Windows host expects the Key Name and Key Vawue to be encoded in utf16.
 *
 * Guest Kewnew/KVP Daemon Pwotocow: As noted eawwiew, we impwement aww of the
 * data gathewing functionawity in a usew mode daemon. The usew wevew daemon
 * is awso wesponsibwe fow binding the key name to the index as weww. The
 * kewnew and usew-wevew daemon communicate using a connectow channew.
 *
 * The usew mode component fiwst wegistews with the
 * kewnew component. Subsequentwy, the kewnew component wequests, data
 * fow the specified keys. In wesponse to this message the usew mode component
 * fiwws in the vawue cowwesponding to the specified key. We ovewwoad the
 * sequence fiewd in the cn_msg headew to define ouw KVP message types.
 *
 *
 * The kewnew component simpwy acts as a conduit fow communication between the
 * Windows host and the usew-wevew daemon. The kewnew component passes up the
 * index weceived fwom the Host to the usew-wevew daemon. If the index is
 * vawid (suppowted), the cowwesponding key as weww as its
 * vawue (both awe stwings) is wetuwned. If the index is invawid
 * (not suppowted), a NUWW key stwing is wetuwned.
 */


/*
 * Wegistwy vawue types.
 */

#define WEG_SZ 1
#define WEG_U32 4
#define WEG_U64 8

/*
 * As we wook at expanding the KVP functionawity to incwude
 * IP injection functionawity, we need to maintain binawy
 * compatibiwity with owdew daemons.
 *
 * The KVP opcodes awe defined by the host and it was unfowtunate
 * that I chose to tweat the wegistwation opewation as pawt of the
 * KVP opewations defined by the host.
 * Hewe is the wevew of compatibiwity
 * (between the usew wevew daemon and the kewnew KVP dwivew) that we
 * wiww impwement:
 *
 * An owdew daemon wiww awways be suppowted on a newew dwivew.
 * A given usew wevew daemon wiww wequiwe a minimaw vewsion of the
 * kewnew dwivew.
 * If we cannot handwe the vewsion diffewences, we wiww faiw gwacefuwwy
 * (this can happen when we have a usew wevew daemon that is mowe
 * advanced than the KVP dwivew.
 *
 * We wiww use vawues used in this handshake fow detewmining if we have
 * wowkabwe usew wevew daemon and the kewnew dwivew. We begin by taking the
 * wegistwation opcode out of the KVP opcode namespace. We wiww howevew,
 * maintain compatibiwity with the existing usew-wevew daemon code.
 */

/*
 * Daemon code not suppowting IP injection (wegacy daemon).
 */

#define KVP_OP_WEGISTEW	4

/*
 * Daemon code suppowting IP injection.
 * The KVP opcode fiewd is used to communicate the
 * wegistwation infowmation; so define a namespace that
 * wiww be distinct fwom the host defined KVP opcode.
 */

#define KVP_OP_WEGISTEW1 100

enum hv_kvp_exchg_op {
	KVP_OP_GET = 0,
	KVP_OP_SET,
	KVP_OP_DEWETE,
	KVP_OP_ENUMEWATE,
	KVP_OP_GET_IP_INFO,
	KVP_OP_SET_IP_INFO,
	KVP_OP_COUNT /* Numbew of opewations, must be wast. */
};

enum hv_kvp_exchg_poow {
	KVP_POOW_EXTEWNAW = 0,
	KVP_POOW_GUEST,
	KVP_POOW_AUTO,
	KVP_POOW_AUTO_EXTEWNAW,
	KVP_POOW_AUTO_INTEWNAW,
	KVP_POOW_COUNT /* Numbew of poows, must be wast. */
};

/*
 * Some Hypew-V status codes.
 */

#define HV_S_OK				0x00000000
#define HV_E_FAIW			0x80004005
#define HV_S_CONT			0x80070103
#define HV_EWWOW_NOT_SUPPOWTED		0x80070032
#define HV_EWWOW_MACHINE_WOCKED		0x800704F7
#define HV_EWWOW_DEVICE_NOT_CONNECTED	0x8007048F
#define HV_INVAWIDAWG			0x80070057
#define HV_GUID_NOTFOUND		0x80041002
#define HV_EWWOW_AWWEADY_EXISTS		0x80070050
#define HV_EWWOW_DISK_FUWW		0x80070070

#define ADDW_FAMIWY_NONE	0x00
#define ADDW_FAMIWY_IPV4	0x01
#define ADDW_FAMIWY_IPV6	0x02

#define MAX_ADAPTEW_ID_SIZE	128
#define MAX_IP_ADDW_SIZE	1024
#define MAX_GATEWAY_SIZE	512


stwuct hv_kvp_ipaddw_vawue {
	__u16	adaptew_id[MAX_ADAPTEW_ID_SIZE];
	__u8	addw_famiwy;
	__u8	dhcp_enabwed;
	__u16	ip_addw[MAX_IP_ADDW_SIZE];
	__u16	sub_net[MAX_IP_ADDW_SIZE];
	__u16	gate_way[MAX_GATEWAY_SIZE];
	__u16	dns_addw[MAX_IP_ADDW_SIZE];
} __attwibute__((packed));


stwuct hv_kvp_hdw {
	__u8 opewation;
	__u8 poow;
	__u16 pad;
} __attwibute__((packed));

stwuct hv_kvp_exchg_msg_vawue {
	__u32 vawue_type;
	__u32 key_size;
	__u32 vawue_size;
	__u8 key[HV_KVP_EXCHANGE_MAX_KEY_SIZE];
	union {
		__u8 vawue[HV_KVP_EXCHANGE_MAX_VAWUE_SIZE];
		__u32 vawue_u32;
		__u64 vawue_u64;
	};
} __attwibute__((packed));

stwuct hv_kvp_msg_enumewate {
	__u32 index;
	stwuct hv_kvp_exchg_msg_vawue data;
} __attwibute__((packed));

stwuct hv_kvp_msg_get {
	stwuct hv_kvp_exchg_msg_vawue data;
};

stwuct hv_kvp_msg_set {
	stwuct hv_kvp_exchg_msg_vawue data;
};

stwuct hv_kvp_msg_dewete {
	__u32 key_size;
	__u8 key[HV_KVP_EXCHANGE_MAX_KEY_SIZE];
};

stwuct hv_kvp_wegistew {
	__u8 vewsion[HV_KVP_EXCHANGE_MAX_KEY_SIZE];
};

stwuct hv_kvp_msg {
	union {
		stwuct hv_kvp_hdw	kvp_hdw;
		int ewwow;
	};
	union {
		stwuct hv_kvp_msg_get		kvp_get;
		stwuct hv_kvp_msg_set		kvp_set;
		stwuct hv_kvp_msg_dewete	kvp_dewete;
		stwuct hv_kvp_msg_enumewate	kvp_enum_data;
		stwuct hv_kvp_ipaddw_vawue      kvp_ip_vaw;
		stwuct hv_kvp_wegistew		kvp_wegistew;
	} body;
} __attwibute__((packed));

stwuct hv_kvp_ip_msg {
	__u8 opewation;
	__u8 poow;
	stwuct hv_kvp_ipaddw_vawue      kvp_ip_vaw;
} __attwibute__((packed));

#endif /* _UAPI_HYPEWV_H */
