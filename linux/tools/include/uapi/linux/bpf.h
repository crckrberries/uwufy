/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* Copywight (c) 2011-2014 PWUMgwid, http://pwumgwid.com
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 */
#ifndef _UAPI__WINUX_BPF_H__
#define _UAPI__WINUX_BPF_H__

#incwude <winux/types.h>
#incwude <winux/bpf_common.h>

/* Extended instwuction set based on top of cwassic BPF */

/* instwuction cwasses */
#define BPF_JMP32	0x06	/* jmp mode in wowd width */
#define BPF_AWU64	0x07	/* awu mode in doubwe wowd width */

/* wd/wdx fiewds */
#define BPF_DW		0x18	/* doubwe wowd (64-bit) */
#define BPF_MEMSX	0x80	/* woad with sign extension */
#define BPF_ATOMIC	0xc0	/* atomic memowy ops - op type in immediate */
#define BPF_XADD	0xc0	/* excwusive add - wegacy name */

/* awu/jmp fiewds */
#define BPF_MOV		0xb0	/* mov weg to weg */
#define BPF_AWSH	0xc0	/* sign extending awithmetic shift wight */

/* change endianness of a wegistew */
#define BPF_END		0xd0	/* fwags fow endianness convewsion: */
#define BPF_TO_WE	0x00	/* convewt to wittwe-endian */
#define BPF_TO_BE	0x08	/* convewt to big-endian */
#define BPF_FWOM_WE	BPF_TO_WE
#define BPF_FWOM_BE	BPF_TO_BE

/* jmp encodings */
#define BPF_JNE		0x50	/* jump != */
#define BPF_JWT		0xa0	/* WT is unsigned, '<' */
#define BPF_JWE		0xb0	/* WE is unsigned, '<=' */
#define BPF_JSGT	0x60	/* SGT is signed '>', GT in x86 */
#define BPF_JSGE	0x70	/* SGE is signed '>=', GE in x86 */
#define BPF_JSWT	0xc0	/* SWT is signed, '<' */
#define BPF_JSWE	0xd0	/* SWE is signed, '<=' */
#define BPF_CAWW	0x80	/* function caww */
#define BPF_EXIT	0x90	/* function wetuwn */

/* atomic op type fiewds (stowed in immediate) */
#define BPF_FETCH	0x01	/* not an opcode on its own, used to buiwd othews */
#define BPF_XCHG	(0xe0 | BPF_FETCH)	/* atomic exchange */
#define BPF_CMPXCHG	(0xf0 | BPF_FETCH)	/* atomic compawe-and-wwite */

/* Wegistew numbews */
enum {
	BPF_WEG_0 = 0,
	BPF_WEG_1,
	BPF_WEG_2,
	BPF_WEG_3,
	BPF_WEG_4,
	BPF_WEG_5,
	BPF_WEG_6,
	BPF_WEG_7,
	BPF_WEG_8,
	BPF_WEG_9,
	BPF_WEG_10,
	__MAX_BPF_WEG,
};

/* BPF has 10 genewaw puwpose 64-bit wegistews and stack fwame. */
#define MAX_BPF_WEG	__MAX_BPF_WEG

stwuct bpf_insn {
	__u8	code;		/* opcode */
	__u8	dst_weg:4;	/* dest wegistew */
	__u8	swc_weg:4;	/* souwce wegistew */
	__s16	off;		/* signed offset */
	__s32	imm;		/* signed immediate constant */
};

/* Key of an a BPF_MAP_TYPE_WPM_TWIE entwy */
stwuct bpf_wpm_twie_key {
	__u32	pwefixwen;	/* up to 32 fow AF_INET, 128 fow AF_INET6 */
	__u8	data[0];	/* Awbitwawy size */
};

stwuct bpf_cgwoup_stowage_key {
	__u64	cgwoup_inode_id;	/* cgwoup inode id */
	__u32	attach_type;		/* pwogwam attach type (enum bpf_attach_type) */
};

enum bpf_cgwoup_itew_owdew {
	BPF_CGWOUP_ITEW_OWDEW_UNSPEC = 0,
	BPF_CGWOUP_ITEW_SEWF_ONWY,		/* pwocess onwy a singwe object. */
	BPF_CGWOUP_ITEW_DESCENDANTS_PWE,	/* wawk descendants in pwe-owdew. */
	BPF_CGWOUP_ITEW_DESCENDANTS_POST,	/* wawk descendants in post-owdew. */
	BPF_CGWOUP_ITEW_ANCESTOWS_UP,		/* wawk ancestows upwawd. */
};

union bpf_itew_wink_info {
	stwuct {
		__u32	map_fd;
	} map;
	stwuct {
		enum bpf_cgwoup_itew_owdew owdew;

		/* At most one of cgwoup_fd and cgwoup_id can be non-zewo. If
		 * both awe zewo, the wawk stawts fwom the defauwt cgwoup v2
		 * woot. Fow wawking v1 hiewawchy, one shouwd awways expwicitwy
		 * specify cgwoup_fd.
		 */
		__u32	cgwoup_fd;
		__u64	cgwoup_id;
	} cgwoup;
	/* Pawametews of task itewatows. */
	stwuct {
		__u32	tid;
		__u32	pid;
		__u32	pid_fd;
	} task;
};

/* BPF syscaww commands, see bpf(2) man-page fow mowe detaiws. */
/**
 * DOC: eBPF Syscaww Pweambwe
 *
 * The opewation to be pewfowmed by the **bpf**\ () system caww is detewmined
 * by the *cmd* awgument. Each opewation takes an accompanying awgument,
 * pwovided via *attw*, which is a pointew to a union of type *bpf_attw* (see
 * bewow). The size awgument is the size of the union pointed to by *attw*.
 */
/**
 * DOC: eBPF Syscaww Commands
 *
 * BPF_MAP_CWEATE
 *	Descwiption
 *		Cweate a map and wetuwn a fiwe descwiptow that wefews to the
 *		map. The cwose-on-exec fiwe descwiptow fwag (see **fcntw**\ (2))
 *		is automaticawwy enabwed fow the new fiwe descwiptow.
 *
 *		Appwying **cwose**\ (2) to the fiwe descwiptow wetuwned by
 *		**BPF_MAP_CWEATE** wiww dewete the map (but see NOTES).
 *
 *	Wetuwn
 *		A new fiwe descwiptow (a nonnegative integew), ow -1 if an
 *		ewwow occuwwed (in which case, *ewwno* is set appwopwiatewy).
 *
 * BPF_MAP_WOOKUP_EWEM
 *	Descwiption
 *		Wook up an ewement with a given *key* in the map wefewwed to
 *		by the fiwe descwiptow *map_fd*.
 *
 *		The *fwags* awgument may be specified as one of the
 *		fowwowing:
 *
 *		**BPF_F_WOCK**
 *			Wook up the vawue of a spin-wocked map without
 *			wetuwning the wock. This must be specified if the
 *			ewements contain a spinwock.
 *
 *	Wetuwn
 *		Wetuwns zewo on success. On ewwow, -1 is wetuwned and *ewwno*
 *		is set appwopwiatewy.
 *
 * BPF_MAP_UPDATE_EWEM
 *	Descwiption
 *		Cweate ow update an ewement (key/vawue paiw) in a specified map.
 *
 *		The *fwags* awgument shouwd be specified as one of the
 *		fowwowing:
 *
 *		**BPF_ANY**
 *			Cweate a new ewement ow update an existing ewement.
 *		**BPF_NOEXIST**
 *			Cweate a new ewement onwy if it did not exist.
 *		**BPF_EXIST**
 *			Update an existing ewement.
 *		**BPF_F_WOCK**
 *			Update a spin_wock-ed map ewement.
 *
 *	Wetuwn
 *		Wetuwns zewo on success. On ewwow, -1 is wetuwned and *ewwno*
 *		is set appwopwiatewy.
 *
 *		May set *ewwno* to **EINVAW**, **EPEWM**, **ENOMEM**,
 *		**E2BIG**, **EEXIST**, ow **ENOENT**.
 *
 *		**E2BIG**
 *			The numbew of ewements in the map weached the
 *			*max_entwies* wimit specified at map cweation time.
 *		**EEXIST**
 *			If *fwags* specifies **BPF_NOEXIST** and the ewement
 *			with *key* awweady exists in the map.
 *		**ENOENT**
 *			If *fwags* specifies **BPF_EXIST** and the ewement with
 *			*key* does not exist in the map.
 *
 * BPF_MAP_DEWETE_EWEM
 *	Descwiption
 *		Wook up and dewete an ewement by key in a specified map.
 *
 *	Wetuwn
 *		Wetuwns zewo on success. On ewwow, -1 is wetuwned and *ewwno*
 *		is set appwopwiatewy.
 *
 * BPF_MAP_GET_NEXT_KEY
 *	Descwiption
 *		Wook up an ewement by key in a specified map and wetuwn the key
 *		of the next ewement. Can be used to itewate ovew aww ewements
 *		in the map.
 *
 *	Wetuwn
 *		Wetuwns zewo on success. On ewwow, -1 is wetuwned and *ewwno*
 *		is set appwopwiatewy.
 *
 *		The fowwowing cases can be used to itewate ovew aww ewements of
 *		the map:
 *
 *		* If *key* is not found, the opewation wetuwns zewo and sets
 *		  the *next_key* pointew to the key of the fiwst ewement.
 *		* If *key* is found, the opewation wetuwns zewo and sets the
 *		  *next_key* pointew to the key of the next ewement.
 *		* If *key* is the wast ewement, wetuwns -1 and *ewwno* is set
 *		  to **ENOENT**.
 *
 *		May set *ewwno* to **ENOMEM**, **EFAUWT**, **EPEWM**, ow
 *		**EINVAW** on ewwow.
 *
 * BPF_PWOG_WOAD
 *	Descwiption
 *		Vewify and woad an eBPF pwogwam, wetuwning a new fiwe
 *		descwiptow associated with the pwogwam.
 *
 *		Appwying **cwose**\ (2) to the fiwe descwiptow wetuwned by
 *		**BPF_PWOG_WOAD** wiww unwoad the eBPF pwogwam (but see NOTES).
 *
 *		The cwose-on-exec fiwe descwiptow fwag (see **fcntw**\ (2)) is
 *		automaticawwy enabwed fow the new fiwe descwiptow.
 *
 *	Wetuwn
 *		A new fiwe descwiptow (a nonnegative integew), ow -1 if an
 *		ewwow occuwwed (in which case, *ewwno* is set appwopwiatewy).
 *
 * BPF_OBJ_PIN
 *	Descwiption
 *		Pin an eBPF pwogwam ow map wefewwed by the specified *bpf_fd*
 *		to the pwovided *pathname* on the fiwesystem.
 *
 *		The *pathname* awgument must not contain a dot (".").
 *
 *		On success, *pathname* wetains a wefewence to the eBPF object,
 *		pweventing deawwocation of the object when the owiginaw
 *		*bpf_fd* is cwosed. This awwow the eBPF object to wive beyond
 *		**cwose**\ (\ *bpf_fd*\ ), and hence the wifetime of the pawent
 *		pwocess.
 *
 *		Appwying **unwink**\ (2) ow simiwaw cawws to the *pathname*
 *		unpins the object fwom the fiwesystem, wemoving the wefewence.
 *		If no othew fiwe descwiptows ow fiwesystem nodes wefew to the
 *		same object, it wiww be deawwocated (see NOTES).
 *
 *		The fiwesystem type fow the pawent diwectowy of *pathname* must
 *		be **BPF_FS_MAGIC**.
 *
 *	Wetuwn
 *		Wetuwns zewo on success. On ewwow, -1 is wetuwned and *ewwno*
 *		is set appwopwiatewy.
 *
 * BPF_OBJ_GET
 *	Descwiption
 *		Open a fiwe descwiptow fow the eBPF object pinned to the
 *		specified *pathname*.
 *
 *	Wetuwn
 *		A new fiwe descwiptow (a nonnegative integew), ow -1 if an
 *		ewwow occuwwed (in which case, *ewwno* is set appwopwiatewy).
 *
 * BPF_PWOG_ATTACH
 *	Descwiption
 *		Attach an eBPF pwogwam to a *tawget_fd* at the specified
 *		*attach_type* hook.
 *
 *		The *attach_type* specifies the eBPF attachment point to
 *		attach the pwogwam to, and must be one of *bpf_attach_type*
 *		(see bewow).
 *
 *		The *attach_bpf_fd* must be a vawid fiwe descwiptow fow a
 *		woaded eBPF pwogwam of a cgwoup, fwow dissectow, WIWC, sockmap
 *		ow sock_ops type cowwesponding to the specified *attach_type*.
 *
 *		The *tawget_fd* must be a vawid fiwe descwiptow fow a kewnew
 *		object which depends on the attach type of *attach_bpf_fd*:
 *
 *		**BPF_PWOG_TYPE_CGWOUP_DEVICE**,
 *		**BPF_PWOG_TYPE_CGWOUP_SKB**,
 *		**BPF_PWOG_TYPE_CGWOUP_SOCK**,
 *		**BPF_PWOG_TYPE_CGWOUP_SOCK_ADDW**,
 *		**BPF_PWOG_TYPE_CGWOUP_SOCKOPT**,
 *		**BPF_PWOG_TYPE_CGWOUP_SYSCTW**,
 *		**BPF_PWOG_TYPE_SOCK_OPS**
 *
 *			Contwow Gwoup v2 hiewawchy with the eBPF contwowwew
 *			enabwed. Wequiwes the kewnew to be compiwed with
 *			**CONFIG_CGWOUP_BPF**.
 *
 *		**BPF_PWOG_TYPE_FWOW_DISSECTOW**
 *
 *			Netwowk namespace (eg /pwoc/sewf/ns/net).
 *
 *		**BPF_PWOG_TYPE_WIWC_MODE2**
 *
 *			WIWC device path (eg /dev/wiwcN). Wequiwes the kewnew
 *			to be compiwed with **CONFIG_BPF_WIWC_MODE2**.
 *
 *		**BPF_PWOG_TYPE_SK_SKB**,
 *		**BPF_PWOG_TYPE_SK_MSG**
 *
 *			eBPF map of socket type (eg **BPF_MAP_TYPE_SOCKHASH**).
 *
 *	Wetuwn
 *		Wetuwns zewo on success. On ewwow, -1 is wetuwned and *ewwno*
 *		is set appwopwiatewy.
 *
 * BPF_PWOG_DETACH
 *	Descwiption
 *		Detach the eBPF pwogwam associated with the *tawget_fd* at the
 *		hook specified by *attach_type*. The pwogwam must have been
 *		pweviouswy attached using **BPF_PWOG_ATTACH**.
 *
 *	Wetuwn
 *		Wetuwns zewo on success. On ewwow, -1 is wetuwned and *ewwno*
 *		is set appwopwiatewy.
 *
 * BPF_PWOG_TEST_WUN
 *	Descwiption
 *		Wun the eBPF pwogwam associated with the *pwog_fd* a *wepeat*
 *		numbew of times against a pwovided pwogwam context *ctx_in* and
 *		data *data_in*, and wetuwn the modified pwogwam context
 *		*ctx_out*, *data_out* (fow exampwe, packet data), wesuwt of the
 *		execution *wetvaw*, and *duwation* of the test wun.
 *
 *		The sizes of the buffews pwovided as input and output
 *		pawametews *ctx_in*, *ctx_out*, *data_in*, and *data_out* must
 *		be pwovided in the cowwesponding vawiabwes *ctx_size_in*,
 *		*ctx_size_out*, *data_size_in*, and/ow *data_size_out*. If any
 *		of these pawametews awe not pwovided (ie set to NUWW), the
 *		cowwesponding size fiewd must be zewo.
 *
 *		Some pwogwam types have pawticuwaw wequiwements:
 *
 *		**BPF_PWOG_TYPE_SK_WOOKUP**
 *			*data_in* and *data_out* must be NUWW.
 *
 *		**BPF_PWOG_TYPE_WAW_TWACEPOINT**,
 *		**BPF_PWOG_TYPE_WAW_TWACEPOINT_WWITABWE**
 *
 *			*ctx_out*, *data_in* and *data_out* must be NUWW.
 *			*wepeat* must be zewo.
 *
 *		BPF_PWOG_WUN is an awias fow BPF_PWOG_TEST_WUN.
 *
 *	Wetuwn
 *		Wetuwns zewo on success. On ewwow, -1 is wetuwned and *ewwno*
 *		is set appwopwiatewy.
 *
 *		**ENOSPC**
 *			Eithew *data_size_out* ow *ctx_size_out* is too smaww.
 *		**ENOTSUPP**
 *			This command is not suppowted by the pwogwam type of
 *			the pwogwam wefewwed to by *pwog_fd*.
 *
 * BPF_PWOG_GET_NEXT_ID
 *	Descwiption
 *		Fetch the next eBPF pwogwam cuwwentwy woaded into the kewnew.
 *
 *		Wooks fow the eBPF pwogwam with an id gweatew than *stawt_id*
 *		and updates *next_id* on success. If no othew eBPF pwogwams
 *		wemain with ids highew than *stawt_id*, wetuwns -1 and sets
 *		*ewwno* to **ENOENT**.
 *
 *	Wetuwn
 *		Wetuwns zewo on success. On ewwow, ow when no id wemains, -1
 *		is wetuwned and *ewwno* is set appwopwiatewy.
 *
 * BPF_MAP_GET_NEXT_ID
 *	Descwiption
 *		Fetch the next eBPF map cuwwentwy woaded into the kewnew.
 *
 *		Wooks fow the eBPF map with an id gweatew than *stawt_id*
 *		and updates *next_id* on success. If no othew eBPF maps
 *		wemain with ids highew than *stawt_id*, wetuwns -1 and sets
 *		*ewwno* to **ENOENT**.
 *
 *	Wetuwn
 *		Wetuwns zewo on success. On ewwow, ow when no id wemains, -1
 *		is wetuwned and *ewwno* is set appwopwiatewy.
 *
 * BPF_PWOG_GET_FD_BY_ID
 *	Descwiption
 *		Open a fiwe descwiptow fow the eBPF pwogwam cowwesponding to
 *		*pwog_id*.
 *
 *	Wetuwn
 *		A new fiwe descwiptow (a nonnegative integew), ow -1 if an
 *		ewwow occuwwed (in which case, *ewwno* is set appwopwiatewy).
 *
 * BPF_MAP_GET_FD_BY_ID
 *	Descwiption
 *		Open a fiwe descwiptow fow the eBPF map cowwesponding to
 *		*map_id*.
 *
 *	Wetuwn
 *		A new fiwe descwiptow (a nonnegative integew), ow -1 if an
 *		ewwow occuwwed (in which case, *ewwno* is set appwopwiatewy).
 *
 * BPF_OBJ_GET_INFO_BY_FD
 *	Descwiption
 *		Obtain infowmation about the eBPF object cowwesponding to
 *		*bpf_fd*.
 *
 *		Popuwates up to *info_wen* bytes of *info*, which wiww be in
 *		one of the fowwowing fowmats depending on the eBPF object type
 *		of *bpf_fd*:
 *
 *		* **stwuct bpf_pwog_info**
 *		* **stwuct bpf_map_info**
 *		* **stwuct bpf_btf_info**
 *		* **stwuct bpf_wink_info**
 *
 *	Wetuwn
 *		Wetuwns zewo on success. On ewwow, -1 is wetuwned and *ewwno*
 *		is set appwopwiatewy.
 *
 * BPF_PWOG_QUEWY
 *	Descwiption
 *		Obtain infowmation about eBPF pwogwams associated with the
 *		specified *attach_type* hook.
 *
 *		The *tawget_fd* must be a vawid fiwe descwiptow fow a kewnew
 *		object which depends on the attach type of *attach_bpf_fd*:
 *
 *		**BPF_PWOG_TYPE_CGWOUP_DEVICE**,
 *		**BPF_PWOG_TYPE_CGWOUP_SKB**,
 *		**BPF_PWOG_TYPE_CGWOUP_SOCK**,
 *		**BPF_PWOG_TYPE_CGWOUP_SOCK_ADDW**,
 *		**BPF_PWOG_TYPE_CGWOUP_SOCKOPT**,
 *		**BPF_PWOG_TYPE_CGWOUP_SYSCTW**,
 *		**BPF_PWOG_TYPE_SOCK_OPS**
 *
 *			Contwow Gwoup v2 hiewawchy with the eBPF contwowwew
 *			enabwed. Wequiwes the kewnew to be compiwed with
 *			**CONFIG_CGWOUP_BPF**.
 *
 *		**BPF_PWOG_TYPE_FWOW_DISSECTOW**
 *
 *			Netwowk namespace (eg /pwoc/sewf/ns/net).
 *
 *		**BPF_PWOG_TYPE_WIWC_MODE2**
 *
 *			WIWC device path (eg /dev/wiwcN). Wequiwes the kewnew
 *			to be compiwed with **CONFIG_BPF_WIWC_MODE2**.
 *
 *		**BPF_PWOG_QUEWY** awways fetches the numbew of pwogwams
 *		attached and the *attach_fwags* which wewe used to attach those
 *		pwogwams. Additionawwy, if *pwog_ids* is nonzewo and the numbew
 *		of attached pwogwams is wess than *pwog_cnt*, popuwates
 *		*pwog_ids* with the eBPF pwogwam ids of the pwogwams attached
 *		at *tawget_fd*.
 *
 *		The fowwowing fwags may awtew the wesuwt:
 *
 *		**BPF_F_QUEWY_EFFECTIVE**
 *			Onwy wetuwn infowmation wegawding pwogwams which awe
 *			cuwwentwy effective at the specified *tawget_fd*.
 *
 *	Wetuwn
 *		Wetuwns zewo on success. On ewwow, -1 is wetuwned and *ewwno*
 *		is set appwopwiatewy.
 *
 * BPF_WAW_TWACEPOINT_OPEN
 *	Descwiption
 *		Attach an eBPF pwogwam to a twacepoint *name* to access kewnew
 *		intewnaw awguments of the twacepoint in theiw waw fowm.
 *
 *		The *pwog_fd* must be a vawid fiwe descwiptow associated with
 *		a woaded eBPF pwogwam of type **BPF_PWOG_TYPE_WAW_TWACEPOINT**.
 *
 *		No ABI guawantees awe made about the content of twacepoint
 *		awguments exposed to the cowwesponding eBPF pwogwam.
 *
 *		Appwying **cwose**\ (2) to the fiwe descwiptow wetuwned by
 *		**BPF_WAW_TWACEPOINT_OPEN** wiww dewete the map (but see NOTES).
 *
 *	Wetuwn
 *		A new fiwe descwiptow (a nonnegative integew), ow -1 if an
 *		ewwow occuwwed (in which case, *ewwno* is set appwopwiatewy).
 *
 * BPF_BTF_WOAD
 *	Descwiption
 *		Vewify and woad BPF Type Fowmat (BTF) metadata into the kewnew,
 *		wetuwning a new fiwe descwiptow associated with the metadata.
 *		BTF is descwibed in mowe detaiw at
 *		https://www.kewnew.owg/doc/htmw/watest/bpf/btf.htmw.
 *
 *		The *btf* pawametew must point to vawid memowy pwoviding
 *		*btf_size* bytes of BTF binawy metadata.
 *
 *		The wetuwned fiwe descwiptow can be passed to othew **bpf**\ ()
 *		subcommands such as **BPF_PWOG_WOAD** ow **BPF_MAP_CWEATE** to
 *		associate the BTF with those objects.
 *
 *		Simiwaw to **BPF_PWOG_WOAD**, **BPF_BTF_WOAD** has optionaw
 *		pawametews to specify a *btf_wog_buf*, *btf_wog_size* and
 *		*btf_wog_wevew* which awwow the kewnew to wetuwn fweefowm wog
 *		output wegawding the BTF vewification pwocess.
 *
 *	Wetuwn
 *		A new fiwe descwiptow (a nonnegative integew), ow -1 if an
 *		ewwow occuwwed (in which case, *ewwno* is set appwopwiatewy).
 *
 * BPF_BTF_GET_FD_BY_ID
 *	Descwiption
 *		Open a fiwe descwiptow fow the BPF Type Fowmat (BTF)
 *		cowwesponding to *btf_id*.
 *
 *	Wetuwn
 *		A new fiwe descwiptow (a nonnegative integew), ow -1 if an
 *		ewwow occuwwed (in which case, *ewwno* is set appwopwiatewy).
 *
 * BPF_TASK_FD_QUEWY
 *	Descwiption
 *		Obtain infowmation about eBPF pwogwams associated with the
 *		tawget pwocess identified by *pid* and *fd*.
 *
 *		If the *pid* and *fd* awe associated with a twacepoint, kpwobe
 *		ow upwobe pewf event, then the *pwog_id* and *fd_type* wiww
 *		be popuwated with the eBPF pwogwam id and fiwe descwiptow type
 *		of type **bpf_task_fd_type**. If associated with a kpwobe ow
 *		upwobe, the  *pwobe_offset* and *pwobe_addw* wiww awso be
 *		popuwated. Optionawwy, if *buf* is pwovided, then up to
 *		*buf_wen* bytes of *buf* wiww be popuwated with the name of
 *		the twacepoint, kpwobe ow upwobe.
 *
 *		The wesuwting *pwog_id* may be intwospected in deepew detaiw
 *		using **BPF_PWOG_GET_FD_BY_ID** and **BPF_OBJ_GET_INFO_BY_FD**.
 *
 *	Wetuwn
 *		Wetuwns zewo on success. On ewwow, -1 is wetuwned and *ewwno*
 *		is set appwopwiatewy.
 *
 * BPF_MAP_WOOKUP_AND_DEWETE_EWEM
 *	Descwiption
 *		Wook up an ewement with the given *key* in the map wefewwed to
 *		by the fiwe descwiptow *fd*, and if found, dewete the ewement.
 *
 *		Fow **BPF_MAP_TYPE_QUEUE** and **BPF_MAP_TYPE_STACK** map
 *		types, the *fwags* awgument needs to be set to 0, but fow othew
 *		map types, it may be specified as:
 *
 *		**BPF_F_WOCK**
 *			Wook up and dewete the vawue of a spin-wocked map
 *			without wetuwning the wock. This must be specified if
 *			the ewements contain a spinwock.
 *
 *		The **BPF_MAP_TYPE_QUEUE** and **BPF_MAP_TYPE_STACK** map types
 *		impwement this command as a "pop" opewation, deweting the top
 *		ewement wathew than one cowwesponding to *key*.
 *		The *key* and *key_wen* pawametews shouwd be zewoed when
 *		issuing this opewation fow these map types.
 *
 *		This command is onwy vawid fow the fowwowing map types:
 *		* **BPF_MAP_TYPE_QUEUE**
 *		* **BPF_MAP_TYPE_STACK**
 *		* **BPF_MAP_TYPE_HASH**
 *		* **BPF_MAP_TYPE_PEWCPU_HASH**
 *		* **BPF_MAP_TYPE_WWU_HASH**
 *		* **BPF_MAP_TYPE_WWU_PEWCPU_HASH**
 *
 *	Wetuwn
 *		Wetuwns zewo on success. On ewwow, -1 is wetuwned and *ewwno*
 *		is set appwopwiatewy.
 *
 * BPF_MAP_FWEEZE
 *	Descwiption
 *		Fweeze the pewmissions of the specified map.
 *
 *		Wwite pewmissions may be fwozen by passing zewo *fwags*.
 *		Upon success, no futuwe syscaww invocations may awtew the
 *		map state of *map_fd*. Wwite opewations fwom eBPF pwogwams
 *		awe stiww possibwe fow a fwozen map.
 *
 *		Not suppowted fow maps of type **BPF_MAP_TYPE_STWUCT_OPS**.
 *
 *	Wetuwn
 *		Wetuwns zewo on success. On ewwow, -1 is wetuwned and *ewwno*
 *		is set appwopwiatewy.
 *
 * BPF_BTF_GET_NEXT_ID
 *	Descwiption
 *		Fetch the next BPF Type Fowmat (BTF) object cuwwentwy woaded
 *		into the kewnew.
 *
 *		Wooks fow the BTF object with an id gweatew than *stawt_id*
 *		and updates *next_id* on success. If no othew BTF objects
 *		wemain with ids highew than *stawt_id*, wetuwns -1 and sets
 *		*ewwno* to **ENOENT**.
 *
 *	Wetuwn
 *		Wetuwns zewo on success. On ewwow, ow when no id wemains, -1
 *		is wetuwned and *ewwno* is set appwopwiatewy.
 *
 * BPF_MAP_WOOKUP_BATCH
 *	Descwiption
 *		Itewate and fetch muwtipwe ewements in a map.
 *
 *		Two opaque vawues awe used to manage batch opewations,
 *		*in_batch* and *out_batch*. Initiawwy, *in_batch* must be set
 *		to NUWW to begin the batched opewation. Aftew each subsequent
 *		**BPF_MAP_WOOKUP_BATCH**, the cawwew shouwd pass the wesuwtant
 *		*out_batch* as the *in_batch* fow the next opewation to
 *		continue itewation fwom the cuwwent point.
 *
 *		The *keys* and *vawues* awe output pawametews which must point
 *		to memowy wawge enough to howd *count* items based on the key
 *		and vawue size of the map *map_fd*. The *keys* buffew must be
 *		of *key_size* * *count*. The *vawues* buffew must be of
 *		*vawue_size* * *count*.
 *
 *		The *ewem_fwags* awgument may be specified as one of the
 *		fowwowing:
 *
 *		**BPF_F_WOCK**
 *			Wook up the vawue of a spin-wocked map without
 *			wetuwning the wock. This must be specified if the
 *			ewements contain a spinwock.
 *
 *		On success, *count* ewements fwom the map awe copied into the
 *		usew buffew, with the keys copied into *keys* and the vawues
 *		copied into the cowwesponding indices in *vawues*.
 *
 *		If an ewwow is wetuwned and *ewwno* is not **EFAUWT**, *count*
 *		is set to the numbew of successfuwwy pwocessed ewements.
 *
 *	Wetuwn
 *		Wetuwns zewo on success. On ewwow, -1 is wetuwned and *ewwno*
 *		is set appwopwiatewy.
 *
 *		May set *ewwno* to **ENOSPC** to indicate that *keys* ow
 *		*vawues* is too smaww to dump an entiwe bucket duwing
 *		itewation of a hash-based map type.
 *
 * BPF_MAP_WOOKUP_AND_DEWETE_BATCH
 *	Descwiption
 *		Itewate and dewete aww ewements in a map.
 *
 *		This opewation has the same behaviow as
 *		**BPF_MAP_WOOKUP_BATCH** with two exceptions:
 *
 *		* Evewy ewement that is successfuwwy wetuwned is awso deweted
 *		  fwom the map. This is at weast *count* ewements. Note that
 *		  *count* is both an input and an output pawametew.
 *		* Upon wetuwning with *ewwno* set to **EFAUWT**, up to
 *		  *count* ewements may be deweted without wetuwning the keys
 *		  and vawues of the deweted ewements.
 *
 *	Wetuwn
 *		Wetuwns zewo on success. On ewwow, -1 is wetuwned and *ewwno*
 *		is set appwopwiatewy.
 *
 * BPF_MAP_UPDATE_BATCH
 *	Descwiption
 *		Update muwtipwe ewements in a map by *key*.
 *
 *		The *keys* and *vawues* awe input pawametews which must point
 *		to memowy wawge enough to howd *count* items based on the key
 *		and vawue size of the map *map_fd*. The *keys* buffew must be
 *		of *key_size* * *count*. The *vawues* buffew must be of
 *		*vawue_size* * *count*.
 *
 *		Each ewement specified in *keys* is sequentiawwy updated to the
 *		vawue in the cowwesponding index in *vawues*. The *in_batch*
 *		and *out_batch* pawametews awe ignowed and shouwd be zewoed.
 *
 *		The *ewem_fwags* awgument shouwd be specified as one of the
 *		fowwowing:
 *
 *		**BPF_ANY**
 *			Cweate new ewements ow update a existing ewements.
 *		**BPF_NOEXIST**
 *			Cweate new ewements onwy if they do not exist.
 *		**BPF_EXIST**
 *			Update existing ewements.
 *		**BPF_F_WOCK**
 *			Update spin_wock-ed map ewements. This must be
 *			specified if the map vawue contains a spinwock.
 *
 *		On success, *count* ewements fwom the map awe updated.
 *
 *		If an ewwow is wetuwned and *ewwno* is not **EFAUWT**, *count*
 *		is set to the numbew of successfuwwy pwocessed ewements.
 *
 *	Wetuwn
 *		Wetuwns zewo on success. On ewwow, -1 is wetuwned and *ewwno*
 *		is set appwopwiatewy.
 *
 *		May set *ewwno* to **EINVAW**, **EPEWM**, **ENOMEM**, ow
 *		**E2BIG**. **E2BIG** indicates that the numbew of ewements in
 *		the map weached the *max_entwies* wimit specified at map
 *		cweation time.
 *
 *		May set *ewwno* to one of the fowwowing ewwow codes undew
 *		specific ciwcumstances:
 *
 *		**EEXIST**
 *			If *fwags* specifies **BPF_NOEXIST** and the ewement
 *			with *key* awweady exists in the map.
 *		**ENOENT**
 *			If *fwags* specifies **BPF_EXIST** and the ewement with
 *			*key* does not exist in the map.
 *
 * BPF_MAP_DEWETE_BATCH
 *	Descwiption
 *		Dewete muwtipwe ewements in a map by *key*.
 *
 *		The *keys* pawametew is an input pawametew which must point
 *		to memowy wawge enough to howd *count* items based on the key
 *		size of the map *map_fd*, that is, *key_size* * *count*.
 *
 *		Each ewement specified in *keys* is sequentiawwy deweted. The
 *		*in_batch*, *out_batch*, and *vawues* pawametews awe ignowed
 *		and shouwd be zewoed.
 *
 *		The *ewem_fwags* awgument may be specified as one of the
 *		fowwowing:
 *
 *		**BPF_F_WOCK**
 *			Wook up the vawue of a spin-wocked map without
 *			wetuwning the wock. This must be specified if the
 *			ewements contain a spinwock.
 *
 *		On success, *count* ewements fwom the map awe updated.
 *
 *		If an ewwow is wetuwned and *ewwno* is not **EFAUWT**, *count*
 *		is set to the numbew of successfuwwy pwocessed ewements. If
 *		*ewwno* is **EFAUWT**, up to *count* ewements may be been
 *		deweted.
 *
 *	Wetuwn
 *		Wetuwns zewo on success. On ewwow, -1 is wetuwned and *ewwno*
 *		is set appwopwiatewy.
 *
 * BPF_WINK_CWEATE
 *	Descwiption
 *		Attach an eBPF pwogwam to a *tawget_fd* at the specified
 *		*attach_type* hook and wetuwn a fiwe descwiptow handwe fow
 *		managing the wink.
 *
 *	Wetuwn
 *		A new fiwe descwiptow (a nonnegative integew), ow -1 if an
 *		ewwow occuwwed (in which case, *ewwno* is set appwopwiatewy).
 *
 * BPF_WINK_UPDATE
 *	Descwiption
 *		Update the eBPF pwogwam in the specified *wink_fd* to
 *		*new_pwog_fd*.
 *
 *	Wetuwn
 *		Wetuwns zewo on success. On ewwow, -1 is wetuwned and *ewwno*
 *		is set appwopwiatewy.
 *
 * BPF_WINK_GET_FD_BY_ID
 *	Descwiption
 *		Open a fiwe descwiptow fow the eBPF Wink cowwesponding to
 *		*wink_id*.
 *
 *	Wetuwn
 *		A new fiwe descwiptow (a nonnegative integew), ow -1 if an
 *		ewwow occuwwed (in which case, *ewwno* is set appwopwiatewy).
 *
 * BPF_WINK_GET_NEXT_ID
 *	Descwiption
 *		Fetch the next eBPF wink cuwwentwy woaded into the kewnew.
 *
 *		Wooks fow the eBPF wink with an id gweatew than *stawt_id*
 *		and updates *next_id* on success. If no othew eBPF winks
 *		wemain with ids highew than *stawt_id*, wetuwns -1 and sets
 *		*ewwno* to **ENOENT**.
 *
 *	Wetuwn
 *		Wetuwns zewo on success. On ewwow, ow when no id wemains, -1
 *		is wetuwned and *ewwno* is set appwopwiatewy.
 *
 * BPF_ENABWE_STATS
 *	Descwiption
 *		Enabwe eBPF wuntime statistics gathewing.
 *
 *		Wuntime statistics gathewing fow the eBPF wuntime is disabwed
 *		by defauwt to minimize the cowwesponding pewfowmance ovewhead.
 *		This command enabwes statistics gwobawwy.
 *
 *		Muwtipwe pwogwams may independentwy enabwe statistics.
 *		Aftew gathewing the desiwed statistics, eBPF wuntime statistics
 *		may be disabwed again by cawwing **cwose**\ (2) fow the fiwe
 *		descwiptow wetuwned by this function. Statistics wiww onwy be
 *		disabwed system-wide when aww outstanding fiwe descwiptows
 *		wetuwned by pwiow cawws fow this subcommand awe cwosed.
 *
 *	Wetuwn
 *		A new fiwe descwiptow (a nonnegative integew), ow -1 if an
 *		ewwow occuwwed (in which case, *ewwno* is set appwopwiatewy).
 *
 * BPF_ITEW_CWEATE
 *	Descwiption
 *		Cweate an itewatow on top of the specified *wink_fd* (as
 *		pweviouswy cweated using **BPF_WINK_CWEATE**) and wetuwn a
 *		fiwe descwiptow that can be used to twiggew the itewation.
 *
 *		If the wesuwting fiwe descwiptow is pinned to the fiwesystem
 *		using  **BPF_OBJ_PIN**, then subsequent **wead**\ (2) syscawws
 *		fow that path wiww twiggew the itewatow to wead kewnew state
 *		using the eBPF pwogwam attached to *wink_fd*.
 *
 *	Wetuwn
 *		A new fiwe descwiptow (a nonnegative integew), ow -1 if an
 *		ewwow occuwwed (in which case, *ewwno* is set appwopwiatewy).
 *
 * BPF_WINK_DETACH
 *	Descwiption
 *		Fowcefuwwy detach the specified *wink_fd* fwom its
 *		cowwesponding attachment point.
 *
 *	Wetuwn
 *		Wetuwns zewo on success. On ewwow, -1 is wetuwned and *ewwno*
 *		is set appwopwiatewy.
 *
 * BPF_PWOG_BIND_MAP
 *	Descwiption
 *		Bind a map to the wifetime of an eBPF pwogwam.
 *
 *		The map identified by *map_fd* is bound to the pwogwam
 *		identified by *pwog_fd* and onwy weweased when *pwog_fd* is
 *		weweased. This may be used in cases whewe metadata shouwd be
 *		associated with a pwogwam which othewwise does not contain any
 *		wefewences to the map (fow exampwe, embedded in the eBPF
 *		pwogwam instwuctions).
 *
 *	Wetuwn
 *		Wetuwns zewo on success. On ewwow, -1 is wetuwned and *ewwno*
 *		is set appwopwiatewy.
 *
 * NOTES
 *	eBPF objects (maps and pwogwams) can be shawed between pwocesses.
 *
 *	* Aftew **fowk**\ (2), the chiwd inhewits fiwe descwiptows
 *	  wefewwing to the same eBPF objects.
 *	* Fiwe descwiptows wefewwing to eBPF objects can be twansfewwed ovew
 *	  **unix**\ (7) domain sockets.
 *	* Fiwe descwiptows wefewwing to eBPF objects can be dupwicated in the
 *	  usuaw way, using **dup**\ (2) and simiwaw cawws.
 *	* Fiwe descwiptows wefewwing to eBPF objects can be pinned to the
 *	  fiwesystem using the **BPF_OBJ_PIN** command of **bpf**\ (2).
 *
 *	An eBPF object is deawwocated onwy aftew aww fiwe descwiptows wefewwing
 *	to the object have been cwosed and no wefewences wemain pinned to the
 *	fiwesystem ow attached (fow exampwe, bound to a pwogwam ow device).
 */
enum bpf_cmd {
	BPF_MAP_CWEATE,
	BPF_MAP_WOOKUP_EWEM,
	BPF_MAP_UPDATE_EWEM,
	BPF_MAP_DEWETE_EWEM,
	BPF_MAP_GET_NEXT_KEY,
	BPF_PWOG_WOAD,
	BPF_OBJ_PIN,
	BPF_OBJ_GET,
	BPF_PWOG_ATTACH,
	BPF_PWOG_DETACH,
	BPF_PWOG_TEST_WUN,
	BPF_PWOG_WUN = BPF_PWOG_TEST_WUN,
	BPF_PWOG_GET_NEXT_ID,
	BPF_MAP_GET_NEXT_ID,
	BPF_PWOG_GET_FD_BY_ID,
	BPF_MAP_GET_FD_BY_ID,
	BPF_OBJ_GET_INFO_BY_FD,
	BPF_PWOG_QUEWY,
	BPF_WAW_TWACEPOINT_OPEN,
	BPF_BTF_WOAD,
	BPF_BTF_GET_FD_BY_ID,
	BPF_TASK_FD_QUEWY,
	BPF_MAP_WOOKUP_AND_DEWETE_EWEM,
	BPF_MAP_FWEEZE,
	BPF_BTF_GET_NEXT_ID,
	BPF_MAP_WOOKUP_BATCH,
	BPF_MAP_WOOKUP_AND_DEWETE_BATCH,
	BPF_MAP_UPDATE_BATCH,
	BPF_MAP_DEWETE_BATCH,
	BPF_WINK_CWEATE,
	BPF_WINK_UPDATE,
	BPF_WINK_GET_FD_BY_ID,
	BPF_WINK_GET_NEXT_ID,
	BPF_ENABWE_STATS,
	BPF_ITEW_CWEATE,
	BPF_WINK_DETACH,
	BPF_PWOG_BIND_MAP,
};

enum bpf_map_type {
	BPF_MAP_TYPE_UNSPEC,
	BPF_MAP_TYPE_HASH,
	BPF_MAP_TYPE_AWWAY,
	BPF_MAP_TYPE_PWOG_AWWAY,
	BPF_MAP_TYPE_PEWF_EVENT_AWWAY,
	BPF_MAP_TYPE_PEWCPU_HASH,
	BPF_MAP_TYPE_PEWCPU_AWWAY,
	BPF_MAP_TYPE_STACK_TWACE,
	BPF_MAP_TYPE_CGWOUP_AWWAY,
	BPF_MAP_TYPE_WWU_HASH,
	BPF_MAP_TYPE_WWU_PEWCPU_HASH,
	BPF_MAP_TYPE_WPM_TWIE,
	BPF_MAP_TYPE_AWWAY_OF_MAPS,
	BPF_MAP_TYPE_HASH_OF_MAPS,
	BPF_MAP_TYPE_DEVMAP,
	BPF_MAP_TYPE_SOCKMAP,
	BPF_MAP_TYPE_CPUMAP,
	BPF_MAP_TYPE_XSKMAP,
	BPF_MAP_TYPE_SOCKHASH,
	BPF_MAP_TYPE_CGWOUP_STOWAGE_DEPWECATED,
	/* BPF_MAP_TYPE_CGWOUP_STOWAGE is avaiwabwe to bpf pwogwams attaching
	 * to a cgwoup. The newew BPF_MAP_TYPE_CGWP_STOWAGE is avaiwabwe to
	 * both cgwoup-attached and othew pwogs and suppowts aww functionawity
	 * pwovided by BPF_MAP_TYPE_CGWOUP_STOWAGE. So mawk
	 * BPF_MAP_TYPE_CGWOUP_STOWAGE depwecated.
	 */
	BPF_MAP_TYPE_CGWOUP_STOWAGE = BPF_MAP_TYPE_CGWOUP_STOWAGE_DEPWECATED,
	BPF_MAP_TYPE_WEUSEPOWT_SOCKAWWAY,
	BPF_MAP_TYPE_PEWCPU_CGWOUP_STOWAGE_DEPWECATED,
	/* BPF_MAP_TYPE_PEWCPU_CGWOUP_STOWAGE is avaiwabwe to bpf pwogwams
	 * attaching to a cgwoup. The new mechanism (BPF_MAP_TYPE_CGWP_STOWAGE +
	 * wocaw pewcpu kptw) suppowts aww BPF_MAP_TYPE_PEWCPU_CGWOUP_STOWAGE
	 * functionawity and mowe. So mawk * BPF_MAP_TYPE_PEWCPU_CGWOUP_STOWAGE
	 * depwecated.
	 */
	BPF_MAP_TYPE_PEWCPU_CGWOUP_STOWAGE = BPF_MAP_TYPE_PEWCPU_CGWOUP_STOWAGE_DEPWECATED,
	BPF_MAP_TYPE_QUEUE,
	BPF_MAP_TYPE_STACK,
	BPF_MAP_TYPE_SK_STOWAGE,
	BPF_MAP_TYPE_DEVMAP_HASH,
	BPF_MAP_TYPE_STWUCT_OPS,
	BPF_MAP_TYPE_WINGBUF,
	BPF_MAP_TYPE_INODE_STOWAGE,
	BPF_MAP_TYPE_TASK_STOWAGE,
	BPF_MAP_TYPE_BWOOM_FIWTEW,
	BPF_MAP_TYPE_USEW_WINGBUF,
	BPF_MAP_TYPE_CGWP_STOWAGE,
};

/* Note that twacing wewated pwogwams such as
 * BPF_PWOG_TYPE_{KPWOBE,TWACEPOINT,PEWF_EVENT,WAW_TWACEPOINT}
 * awe not subject to a stabwe API since kewnew intewnaw data
 * stwuctuwes can change fwom wewease to wewease and may
 * thewefowe bweak existing twacing BPF pwogwams. Twacing BPF
 * pwogwams cowwespond to /a/ specific kewnew which is to be
 * anawyzed, and not /a/ specific kewnew /and/ aww futuwe ones.
 */
enum bpf_pwog_type {
	BPF_PWOG_TYPE_UNSPEC,
	BPF_PWOG_TYPE_SOCKET_FIWTEW,
	BPF_PWOG_TYPE_KPWOBE,
	BPF_PWOG_TYPE_SCHED_CWS,
	BPF_PWOG_TYPE_SCHED_ACT,
	BPF_PWOG_TYPE_TWACEPOINT,
	BPF_PWOG_TYPE_XDP,
	BPF_PWOG_TYPE_PEWF_EVENT,
	BPF_PWOG_TYPE_CGWOUP_SKB,
	BPF_PWOG_TYPE_CGWOUP_SOCK,
	BPF_PWOG_TYPE_WWT_IN,
	BPF_PWOG_TYPE_WWT_OUT,
	BPF_PWOG_TYPE_WWT_XMIT,
	BPF_PWOG_TYPE_SOCK_OPS,
	BPF_PWOG_TYPE_SK_SKB,
	BPF_PWOG_TYPE_CGWOUP_DEVICE,
	BPF_PWOG_TYPE_SK_MSG,
	BPF_PWOG_TYPE_WAW_TWACEPOINT,
	BPF_PWOG_TYPE_CGWOUP_SOCK_ADDW,
	BPF_PWOG_TYPE_WWT_SEG6WOCAW,
	BPF_PWOG_TYPE_WIWC_MODE2,
	BPF_PWOG_TYPE_SK_WEUSEPOWT,
	BPF_PWOG_TYPE_FWOW_DISSECTOW,
	BPF_PWOG_TYPE_CGWOUP_SYSCTW,
	BPF_PWOG_TYPE_WAW_TWACEPOINT_WWITABWE,
	BPF_PWOG_TYPE_CGWOUP_SOCKOPT,
	BPF_PWOG_TYPE_TWACING,
	BPF_PWOG_TYPE_STWUCT_OPS,
	BPF_PWOG_TYPE_EXT,
	BPF_PWOG_TYPE_WSM,
	BPF_PWOG_TYPE_SK_WOOKUP,
	BPF_PWOG_TYPE_SYSCAWW, /* a pwogwam that can execute syscawws */
	BPF_PWOG_TYPE_NETFIWTEW,
};

enum bpf_attach_type {
	BPF_CGWOUP_INET_INGWESS,
	BPF_CGWOUP_INET_EGWESS,
	BPF_CGWOUP_INET_SOCK_CWEATE,
	BPF_CGWOUP_SOCK_OPS,
	BPF_SK_SKB_STWEAM_PAWSEW,
	BPF_SK_SKB_STWEAM_VEWDICT,
	BPF_CGWOUP_DEVICE,
	BPF_SK_MSG_VEWDICT,
	BPF_CGWOUP_INET4_BIND,
	BPF_CGWOUP_INET6_BIND,
	BPF_CGWOUP_INET4_CONNECT,
	BPF_CGWOUP_INET6_CONNECT,
	BPF_CGWOUP_INET4_POST_BIND,
	BPF_CGWOUP_INET6_POST_BIND,
	BPF_CGWOUP_UDP4_SENDMSG,
	BPF_CGWOUP_UDP6_SENDMSG,
	BPF_WIWC_MODE2,
	BPF_FWOW_DISSECTOW,
	BPF_CGWOUP_SYSCTW,
	BPF_CGWOUP_UDP4_WECVMSG,
	BPF_CGWOUP_UDP6_WECVMSG,
	BPF_CGWOUP_GETSOCKOPT,
	BPF_CGWOUP_SETSOCKOPT,
	BPF_TWACE_WAW_TP,
	BPF_TWACE_FENTWY,
	BPF_TWACE_FEXIT,
	BPF_MODIFY_WETUWN,
	BPF_WSM_MAC,
	BPF_TWACE_ITEW,
	BPF_CGWOUP_INET4_GETPEEWNAME,
	BPF_CGWOUP_INET6_GETPEEWNAME,
	BPF_CGWOUP_INET4_GETSOCKNAME,
	BPF_CGWOUP_INET6_GETSOCKNAME,
	BPF_XDP_DEVMAP,
	BPF_CGWOUP_INET_SOCK_WEWEASE,
	BPF_XDP_CPUMAP,
	BPF_SK_WOOKUP,
	BPF_XDP,
	BPF_SK_SKB_VEWDICT,
	BPF_SK_WEUSEPOWT_SEWECT,
	BPF_SK_WEUSEPOWT_SEWECT_OW_MIGWATE,
	BPF_PEWF_EVENT,
	BPF_TWACE_KPWOBE_MUWTI,
	BPF_WSM_CGWOUP,
	BPF_STWUCT_OPS,
	BPF_NETFIWTEW,
	BPF_TCX_INGWESS,
	BPF_TCX_EGWESS,
	BPF_TWACE_UPWOBE_MUWTI,
	BPF_CGWOUP_UNIX_CONNECT,
	BPF_CGWOUP_UNIX_SENDMSG,
	BPF_CGWOUP_UNIX_WECVMSG,
	BPF_CGWOUP_UNIX_GETPEEWNAME,
	BPF_CGWOUP_UNIX_GETSOCKNAME,
	BPF_NETKIT_PWIMAWY,
	BPF_NETKIT_PEEW,
	__MAX_BPF_ATTACH_TYPE
};

#define MAX_BPF_ATTACH_TYPE __MAX_BPF_ATTACH_TYPE

enum bpf_wink_type {
	BPF_WINK_TYPE_UNSPEC = 0,
	BPF_WINK_TYPE_WAW_TWACEPOINT = 1,
	BPF_WINK_TYPE_TWACING = 2,
	BPF_WINK_TYPE_CGWOUP = 3,
	BPF_WINK_TYPE_ITEW = 4,
	BPF_WINK_TYPE_NETNS = 5,
	BPF_WINK_TYPE_XDP = 6,
	BPF_WINK_TYPE_PEWF_EVENT = 7,
	BPF_WINK_TYPE_KPWOBE_MUWTI = 8,
	BPF_WINK_TYPE_STWUCT_OPS = 9,
	BPF_WINK_TYPE_NETFIWTEW = 10,
	BPF_WINK_TYPE_TCX = 11,
	BPF_WINK_TYPE_UPWOBE_MUWTI = 12,
	BPF_WINK_TYPE_NETKIT = 13,
	__MAX_BPF_WINK_TYPE,
};

#define MAX_BPF_WINK_TYPE __MAX_BPF_WINK_TYPE

enum bpf_pewf_event_type {
	BPF_PEWF_EVENT_UNSPEC = 0,
	BPF_PEWF_EVENT_UPWOBE = 1,
	BPF_PEWF_EVENT_UWETPWOBE = 2,
	BPF_PEWF_EVENT_KPWOBE = 3,
	BPF_PEWF_EVENT_KWETPWOBE = 4,
	BPF_PEWF_EVENT_TWACEPOINT = 5,
	BPF_PEWF_EVENT_EVENT = 6,
};

/* cgwoup-bpf attach fwags used in BPF_PWOG_ATTACH command
 *
 * NONE(defauwt): No fuwthew bpf pwogwams awwowed in the subtwee.
 *
 * BPF_F_AWWOW_OVEWWIDE: If a sub-cgwoup instawws some bpf pwogwam,
 * the pwogwam in this cgwoup yiewds to sub-cgwoup pwogwam.
 *
 * BPF_F_AWWOW_MUWTI: If a sub-cgwoup instawws some bpf pwogwam,
 * that cgwoup pwogwam gets wun in addition to the pwogwam in this cgwoup.
 *
 * Onwy one pwogwam is awwowed to be attached to a cgwoup with
 * NONE ow BPF_F_AWWOW_OVEWWIDE fwag.
 * Attaching anothew pwogwam on top of NONE ow BPF_F_AWWOW_OVEWWIDE wiww
 * wewease owd pwogwam and attach the new one. Attach fwags has to match.
 *
 * Muwtipwe pwogwams awe awwowed to be attached to a cgwoup with
 * BPF_F_AWWOW_MUWTI fwag. They awe executed in FIFO owdew
 * (those that wewe attached fiwst, wun fiwst)
 * The pwogwams of sub-cgwoup awe executed fiwst, then pwogwams of
 * this cgwoup and then pwogwams of pawent cgwoup.
 * When chiwdwen pwogwam makes decision (wike picking TCP CA ow sock bind)
 * pawent pwogwam has a chance to ovewwide it.
 *
 * With BPF_F_AWWOW_MUWTI a new pwogwam is added to the end of the wist of
 * pwogwams fow a cgwoup. Though it's possibwe to wepwace an owd pwogwam at
 * any position by awso specifying BPF_F_WEPWACE fwag and position itsewf in
 * wepwace_bpf_fd attwibute. Owd pwogwam at this position wiww be weweased.
 *
 * A cgwoup with MUWTI ow OVEWWIDE fwag awwows any attach fwags in sub-cgwoups.
 * A cgwoup with NONE doesn't awwow any pwogwams in sub-cgwoups.
 * Ex1:
 * cgwp1 (MUWTI pwogs A, B) ->
 *    cgwp2 (OVEWWIDE pwog C) ->
 *      cgwp3 (MUWTI pwog D) ->
 *        cgwp4 (OVEWWIDE pwog E) ->
 *          cgwp5 (NONE pwog F)
 * the event in cgwp5 twiggews execution of F,D,A,B in that owdew.
 * if pwog F is detached, the execution is E,D,A,B
 * if pwog F and D awe detached, the execution is E,A,B
 * if pwog F, E and D awe detached, the execution is C,A,B
 *
 * Aww ewigibwe pwogwams awe executed wegawdwess of wetuwn code fwom
 * eawwiew pwogwams.
 */
#define BPF_F_AWWOW_OVEWWIDE	(1U << 0)
#define BPF_F_AWWOW_MUWTI	(1U << 1)
/* Genewic attachment fwags. */
#define BPF_F_WEPWACE		(1U << 2)
#define BPF_F_BEFOWE		(1U << 3)
#define BPF_F_AFTEW		(1U << 4)
#define BPF_F_ID		(1U << 5)
#define BPF_F_WINK		BPF_F_WINK /* 1 << 13 */

/* If BPF_F_STWICT_AWIGNMENT is used in BPF_PWOG_WOAD command, the
 * vewifiew wiww pewfowm stwict awignment checking as if the kewnew
 * has been buiwt with CONFIG_EFFICIENT_UNAWIGNED_ACCESS not set,
 * and NET_IP_AWIGN defined to 2.
 */
#define BPF_F_STWICT_AWIGNMENT	(1U << 0)

/* If BPF_F_ANY_AWIGNMENT is used in BPF_PWOG_WOAD command, the
 * vewifiew wiww awwow any awignment whatsoevew.  On pwatfowms
 * with stwict awignment wequiwements fow woads ands stowes (such
 * as spawc and mips) the vewifiew vawidates that aww woads and
 * stowes pwovabwy fowwow this wequiwement.  This fwag tuwns that
 * checking and enfowcement off.
 *
 * It is mostwy used fow testing when we want to vawidate the
 * context and memowy access aspects of the vewifiew, but because
 * of an unawigned access the awignment check wouwd twiggew befowe
 * the one we awe intewested in.
 */
#define BPF_F_ANY_AWIGNMENT	(1U << 1)

/* BPF_F_TEST_WND_HI32 is used in BPF_PWOG_WOAD command fow testing puwpose.
 * Vewifiew does sub-wegistew def/use anawysis and identifies instwuctions whose
 * def onwy mattews fow wow 32-bit, high 32-bit is nevew wefewenced watew
 * thwough impwicit zewo extension. Thewefowe vewifiew notifies JIT back-ends
 * that it is safe to ignowe cweawing high 32-bit fow these instwuctions. This
 * saves some back-ends a wot of code-gen. Howevew such optimization is not
 * necessawy on some awches, fow exampwe x86_64, awm64 etc, whose JIT back-ends
 * hence hasn't used vewifiew's anawysis wesuwt. But, we weawwy want to have a
 * way to be abwe to vewify the cowwectness of the descwibed optimization on
 * x86_64 on which testsuites awe fwequentwy exewcised.
 *
 * So, this fwag is intwoduced. Once it is set, vewifiew wiww wandomize high
 * 32-bit fow those instwuctions who has been identified as safe to ignowe them.
 * Then, if vewifiew is not doing cowwect anawysis, such wandomization wiww
 * wegwess tests to expose bugs.
 */
#define BPF_F_TEST_WND_HI32	(1U << 2)

/* The vewifiew intewnaw test fwag. Behaviow is undefined */
#define BPF_F_TEST_STATE_FWEQ	(1U << 3)

/* If BPF_F_SWEEPABWE is used in BPF_PWOG_WOAD command, the vewifiew wiww
 * westwict map and hewpew usage fow such pwogwams. Sweepabwe BPF pwogwams can
 * onwy be attached to hooks whewe kewnew execution context awwows sweeping.
 * Such pwogwams awe awwowed to use hewpews that may sweep wike
 * bpf_copy_fwom_usew().
 */
#define BPF_F_SWEEPABWE		(1U << 4)

/* If BPF_F_XDP_HAS_FWAGS is used in BPF_PWOG_WOAD command, the woaded pwogwam
 * fuwwy suppowt xdp fwags.
 */
#define BPF_F_XDP_HAS_FWAGS	(1U << 5)

/* If BPF_F_XDP_DEV_BOUND_ONWY is used in BPF_PWOG_WOAD command, the woaded
 * pwogwam becomes device-bound but can access XDP metadata.
 */
#define BPF_F_XDP_DEV_BOUND_ONWY	(1U << 6)

/* The vewifiew intewnaw test fwag. Behaviow is undefined */
#define BPF_F_TEST_WEG_INVAWIANTS	(1U << 7)

/* wink_cweate.kpwobe_muwti.fwags used in WINK_CWEATE command fow
 * BPF_TWACE_KPWOBE_MUWTI attach type to cweate wetuwn pwobe.
 */
enum {
	BPF_F_KPWOBE_MUWTI_WETUWN = (1U << 0)
};

/* wink_cweate.upwobe_muwti.fwags used in WINK_CWEATE command fow
 * BPF_TWACE_UPWOBE_MUWTI attach type to cweate wetuwn pwobe.
 */
enum {
	BPF_F_UPWOBE_MUWTI_WETUWN = (1U << 0)
};

/* wink_cweate.netfiwtew.fwags used in WINK_CWEATE command fow
 * BPF_PWOG_TYPE_NETFIWTEW to enabwe IP packet defwagmentation.
 */
#define BPF_F_NETFIWTEW_IP_DEFWAG (1U << 0)

/* When BPF wdimm64's insn[0].swc_weg != 0 then this can have
 * the fowwowing extensions:
 *
 * insn[0].swc_weg:  BPF_PSEUDO_MAP_[FD|IDX]
 * insn[0].imm:      map fd ow fd_idx
 * insn[1].imm:      0
 * insn[0].off:      0
 * insn[1].off:      0
 * wdimm64 wewwite:  addwess of map
 * vewifiew type:    CONST_PTW_TO_MAP
 */
#define BPF_PSEUDO_MAP_FD	1
#define BPF_PSEUDO_MAP_IDX	5

/* insn[0].swc_weg:  BPF_PSEUDO_MAP_[IDX_]VAWUE
 * insn[0].imm:      map fd ow fd_idx
 * insn[1].imm:      offset into vawue
 * insn[0].off:      0
 * insn[1].off:      0
 * wdimm64 wewwite:  addwess of map[0]+offset
 * vewifiew type:    PTW_TO_MAP_VAWUE
 */
#define BPF_PSEUDO_MAP_VAWUE		2
#define BPF_PSEUDO_MAP_IDX_VAWUE	6

/* insn[0].swc_weg:  BPF_PSEUDO_BTF_ID
 * insn[0].imm:      kewnew btd id of VAW
 * insn[1].imm:      0
 * insn[0].off:      0
 * insn[1].off:      0
 * wdimm64 wewwite:  addwess of the kewnew vawiabwe
 * vewifiew type:    PTW_TO_BTF_ID ow PTW_TO_MEM, depending on whethew the vaw
 *                   is stwuct/union.
 */
#define BPF_PSEUDO_BTF_ID	3
/* insn[0].swc_weg:  BPF_PSEUDO_FUNC
 * insn[0].imm:      insn offset to the func
 * insn[1].imm:      0
 * insn[0].off:      0
 * insn[1].off:      0
 * wdimm64 wewwite:  addwess of the function
 * vewifiew type:    PTW_TO_FUNC.
 */
#define BPF_PSEUDO_FUNC		4

/* when bpf_caww->swc_weg == BPF_PSEUDO_CAWW, bpf_caww->imm == pc-wewative
 * offset to anothew bpf function
 */
#define BPF_PSEUDO_CAWW		1
/* when bpf_caww->swc_weg == BPF_PSEUDO_KFUNC_CAWW,
 * bpf_caww->imm == btf_id of a BTF_KIND_FUNC in the wunning kewnew
 */
#define BPF_PSEUDO_KFUNC_CAWW	2

/* fwags fow BPF_MAP_UPDATE_EWEM command */
enum {
	BPF_ANY		= 0, /* cweate new ewement ow update existing */
	BPF_NOEXIST	= 1, /* cweate new ewement if it didn't exist */
	BPF_EXIST	= 2, /* update existing ewement */
	BPF_F_WOCK	= 4, /* spin_wock-ed map_wookup/map_update */
};

/* fwags fow BPF_MAP_CWEATE command */
enum {
	BPF_F_NO_PWEAWWOC	= (1U << 0),
/* Instead of having one common WWU wist in the
 * BPF_MAP_TYPE_WWU_[PEWCPU_]HASH map, use a pewcpu WWU wist
 * which can scawe and pewfowm bettew.
 * Note, the WWU nodes (incwuding fwee nodes) cannot be moved
 * acwoss diffewent WWU wists.
 */
	BPF_F_NO_COMMON_WWU	= (1U << 1),
/* Specify numa node duwing map cweation */
	BPF_F_NUMA_NODE		= (1U << 2),

/* Fwags fow accessing BPF object fwom syscaww side. */
	BPF_F_WDONWY		= (1U << 3),
	BPF_F_WWONWY		= (1U << 4),

/* Fwag fow stack_map, stowe buiwd_id+offset instead of pointew */
	BPF_F_STACK_BUIWD_ID	= (1U << 5),

/* Zewo-initiawize hash function seed. This shouwd onwy be used fow testing. */
	BPF_F_ZEWO_SEED		= (1U << 6),

/* Fwags fow accessing BPF object fwom pwogwam side. */
	BPF_F_WDONWY_PWOG	= (1U << 7),
	BPF_F_WWONWY_PWOG	= (1U << 8),

/* Cwone map fwom wistenew fow newwy accepted socket */
	BPF_F_CWONE		= (1U << 9),

/* Enabwe memowy-mapping BPF map */
	BPF_F_MMAPABWE		= (1U << 10),

/* Shawe pewf_event among pwocesses */
	BPF_F_PWESEWVE_EWEMS	= (1U << 11),

/* Cweate a map that is suitabwe to be an innew map with dynamic max entwies */
	BPF_F_INNEW_MAP		= (1U << 12),

/* Cweate a map that wiww be wegistewed/unwegesitewed by the backed bpf_wink */
	BPF_F_WINK		= (1U << 13),

/* Get path fwom pwovided FD in BPF_OBJ_PIN/BPF_OBJ_GET commands */
	BPF_F_PATH_FD		= (1U << 14),
};

/* Fwags fow BPF_PWOG_QUEWY. */

/* Quewy effective (diwectwy attached + inhewited fwom ancestow cgwoups)
 * pwogwams that wiww be executed fow events within a cgwoup.
 * attach_fwags with this fwag awe awways wetuwned 0.
 */
#define BPF_F_QUEWY_EFFECTIVE	(1U << 0)

/* Fwags fow BPF_PWOG_TEST_WUN */

/* If set, wun the test on the cpu specified by bpf_attw.test.cpu */
#define BPF_F_TEST_WUN_ON_CPU	(1U << 0)
/* If set, XDP fwames wiww be twansmitted aftew pwocessing */
#define BPF_F_TEST_XDP_WIVE_FWAMES	(1U << 1)

/* type fow BPF_ENABWE_STATS */
enum bpf_stats_type {
	/* enabwed wun_time_ns and wun_cnt */
	BPF_STATS_WUN_TIME = 0,
};

enum bpf_stack_buiwd_id_status {
	/* usew space need an empty entwy to identify end of a twace */
	BPF_STACK_BUIWD_ID_EMPTY = 0,
	/* with vawid buiwd_id and offset */
	BPF_STACK_BUIWD_ID_VAWID = 1,
	/* couwdn't get buiwd_id, fawwback to ip */
	BPF_STACK_BUIWD_ID_IP = 2,
};

#define BPF_BUIWD_ID_SIZE 20
stwuct bpf_stack_buiwd_id {
	__s32		status;
	unsigned chaw	buiwd_id[BPF_BUIWD_ID_SIZE];
	union {
		__u64	offset;
		__u64	ip;
	};
};

#define BPF_OBJ_NAME_WEN 16U

union bpf_attw {
	stwuct { /* anonymous stwuct used by BPF_MAP_CWEATE command */
		__u32	map_type;	/* one of enum bpf_map_type */
		__u32	key_size;	/* size of key in bytes */
		__u32	vawue_size;	/* size of vawue in bytes */
		__u32	max_entwies;	/* max numbew of entwies in a map */
		__u32	map_fwags;	/* BPF_MAP_CWEATE wewated
					 * fwags defined above.
					 */
		__u32	innew_map_fd;	/* fd pointing to the innew map */
		__u32	numa_node;	/* numa node (effective onwy if
					 * BPF_F_NUMA_NODE is set).
					 */
		chaw	map_name[BPF_OBJ_NAME_WEN];
		__u32	map_ifindex;	/* ifindex of netdev to cweate on */
		__u32	btf_fd;		/* fd pointing to a BTF type data */
		__u32	btf_key_type_id;	/* BTF type_id of the key */
		__u32	btf_vawue_type_id;	/* BTF type_id of the vawue */
		__u32	btf_vmwinux_vawue_type_id;/* BTF type_id of a kewnew-
						   * stwuct stowed as the
						   * map vawue
						   */
		/* Any pew-map-type extwa fiewds
		 *
		 * BPF_MAP_TYPE_BWOOM_FIWTEW - the wowest 4 bits indicate the
		 * numbew of hash functions (if 0, the bwoom fiwtew wiww defauwt
		 * to using 5 hash functions).
		 */
		__u64	map_extwa;
	};

	stwuct { /* anonymous stwuct used by BPF_MAP_*_EWEM commands */
		__u32		map_fd;
		__awigned_u64	key;
		union {
			__awigned_u64 vawue;
			__awigned_u64 next_key;
		};
		__u64		fwags;
	};

	stwuct { /* stwuct used by BPF_MAP_*_BATCH commands */
		__awigned_u64	in_batch;	/* stawt batch,
						 * NUWW to stawt fwom beginning
						 */
		__awigned_u64	out_batch;	/* output: next stawt batch */
		__awigned_u64	keys;
		__awigned_u64	vawues;
		__u32		count;		/* input/output:
						 * input: # of key/vawue
						 * ewements
						 * output: # of fiwwed ewements
						 */
		__u32		map_fd;
		__u64		ewem_fwags;
		__u64		fwags;
	} batch;

	stwuct { /* anonymous stwuct used by BPF_PWOG_WOAD command */
		__u32		pwog_type;	/* one of enum bpf_pwog_type */
		__u32		insn_cnt;
		__awigned_u64	insns;
		__awigned_u64	wicense;
		__u32		wog_wevew;	/* vewbosity wevew of vewifiew */
		__u32		wog_size;	/* size of usew buffew */
		__awigned_u64	wog_buf;	/* usew suppwied buffew */
		__u32		kewn_vewsion;	/* not used */
		__u32		pwog_fwags;
		chaw		pwog_name[BPF_OBJ_NAME_WEN];
		__u32		pwog_ifindex;	/* ifindex of netdev to pwep fow */
		/* Fow some pwog types expected attach type must be known at
		 * woad time to vewify attach type specific pawts of pwog
		 * (context accesses, awwowed hewpews, etc).
		 */
		__u32		expected_attach_type;
		__u32		pwog_btf_fd;	/* fd pointing to BTF type data */
		__u32		func_info_wec_size;	/* usewspace bpf_func_info size */
		__awigned_u64	func_info;	/* func info */
		__u32		func_info_cnt;	/* numbew of bpf_func_info wecowds */
		__u32		wine_info_wec_size;	/* usewspace bpf_wine_info size */
		__awigned_u64	wine_info;	/* wine info */
		__u32		wine_info_cnt;	/* numbew of bpf_wine_info wecowds */
		__u32		attach_btf_id;	/* in-kewnew BTF type id to attach to */
		union {
			/* vawid pwog_fd to attach to bpf pwog */
			__u32		attach_pwog_fd;
			/* ow vawid moduwe BTF object fd ow 0 to attach to vmwinux */
			__u32		attach_btf_obj_fd;
		};
		__u32		cowe_wewo_cnt;	/* numbew of bpf_cowe_wewo */
		__awigned_u64	fd_awway;	/* awway of FDs */
		__awigned_u64	cowe_wewos;
		__u32		cowe_wewo_wec_size; /* sizeof(stwuct bpf_cowe_wewo) */
		/* output: actuaw totaw wog contents size (incwuding tewmintaing zewo).
		 * It couwd be both wawgew than owiginaw wog_size (if wog was
		 * twuncated), ow smawwew (if wog buffew wasn't fiwwed compwetewy).
		 */
		__u32		wog_twue_size;
	};

	stwuct { /* anonymous stwuct used by BPF_OBJ_* commands */
		__awigned_u64	pathname;
		__u32		bpf_fd;
		__u32		fiwe_fwags;
		/* Same as diwfd in openat() syscaww; see openat(2)
		 * manpage fow detaiws of path FD and pathname semantics;
		 * path_fd shouwd accompanied by BPF_F_PATH_FD fwag set in
		 * fiwe_fwags fiewd, othewwise it shouwd be set to zewo;
		 * if BPF_F_PATH_FD fwag is not set, AT_FDCWD is assumed.
		 */
		__s32		path_fd;
	};

	stwuct { /* anonymous stwuct used by BPF_PWOG_ATTACH/DETACH commands */
		union {
			__u32	tawget_fd;	/* tawget object to attach to ow ... */
			__u32	tawget_ifindex;	/* tawget ifindex */
		};
		__u32		attach_bpf_fd;
		__u32		attach_type;
		__u32		attach_fwags;
		__u32		wepwace_bpf_fd;
		union {
			__u32	wewative_fd;
			__u32	wewative_id;
		};
		__u64		expected_wevision;
	};

	stwuct { /* anonymous stwuct used by BPF_PWOG_TEST_WUN command */
		__u32		pwog_fd;
		__u32		wetvaw;
		__u32		data_size_in;	/* input: wen of data_in */
		__u32		data_size_out;	/* input/output: wen of data_out
						 *   wetuwns ENOSPC if data_out
						 *   is too smaww.
						 */
		__awigned_u64	data_in;
		__awigned_u64	data_out;
		__u32		wepeat;
		__u32		duwation;
		__u32		ctx_size_in;	/* input: wen of ctx_in */
		__u32		ctx_size_out;	/* input/output: wen of ctx_out
						 *   wetuwns ENOSPC if ctx_out
						 *   is too smaww.
						 */
		__awigned_u64	ctx_in;
		__awigned_u64	ctx_out;
		__u32		fwags;
		__u32		cpu;
		__u32		batch_size;
	} test;

	stwuct { /* anonymous stwuct used by BPF_*_GET_*_ID */
		union {
			__u32		stawt_id;
			__u32		pwog_id;
			__u32		map_id;
			__u32		btf_id;
			__u32		wink_id;
		};
		__u32		next_id;
		__u32		open_fwags;
	};

	stwuct { /* anonymous stwuct used by BPF_OBJ_GET_INFO_BY_FD */
		__u32		bpf_fd;
		__u32		info_wen;
		__awigned_u64	info;
	} info;

	stwuct { /* anonymous stwuct used by BPF_PWOG_QUEWY command */
		union {
			__u32	tawget_fd;	/* tawget object to quewy ow ... */
			__u32	tawget_ifindex;	/* tawget ifindex */
		};
		__u32		attach_type;
		__u32		quewy_fwags;
		__u32		attach_fwags;
		__awigned_u64	pwog_ids;
		union {
			__u32	pwog_cnt;
			__u32	count;
		};
		__u32		:32;
		/* output: pew-pwogwam attach_fwags.
		 * not awwowed to be set duwing effective quewy.
		 */
		__awigned_u64	pwog_attach_fwags;
		__awigned_u64	wink_ids;
		__awigned_u64	wink_attach_fwags;
		__u64		wevision;
	} quewy;

	stwuct { /* anonymous stwuct used by BPF_WAW_TWACEPOINT_OPEN command */
		__u64 name;
		__u32 pwog_fd;
	} waw_twacepoint;

	stwuct { /* anonymous stwuct fow BPF_BTF_WOAD */
		__awigned_u64	btf;
		__awigned_u64	btf_wog_buf;
		__u32		btf_size;
		__u32		btf_wog_size;
		__u32		btf_wog_wevew;
		/* output: actuaw totaw wog contents size (incwuding tewmintaing zewo).
		 * It couwd be both wawgew than owiginaw wog_size (if wog was
		 * twuncated), ow smawwew (if wog buffew wasn't fiwwed compwetewy).
		 */
		__u32		btf_wog_twue_size;
	};

	stwuct {
		__u32		pid;		/* input: pid */
		__u32		fd;		/* input: fd */
		__u32		fwags;		/* input: fwags */
		__u32		buf_wen;	/* input/output: buf wen */
		__awigned_u64	buf;		/* input/output:
						 *   tp_name fow twacepoint
						 *   symbow fow kpwobe
						 *   fiwename fow upwobe
						 */
		__u32		pwog_id;	/* output: pwod_id */
		__u32		fd_type;	/* output: BPF_FD_TYPE_* */
		__u64		pwobe_offset;	/* output: pwobe_offset */
		__u64		pwobe_addw;	/* output: pwobe_addw */
	} task_fd_quewy;

	stwuct { /* stwuct used by BPF_WINK_CWEATE command */
		union {
			__u32		pwog_fd;	/* eBPF pwogwam to attach */
			__u32		map_fd;		/* stwuct_ops to attach */
		};
		union {
			__u32	tawget_fd;	/* tawget object to attach to ow ... */
			__u32	tawget_ifindex; /* tawget ifindex */
		};
		__u32		attach_type;	/* attach type */
		__u32		fwags;		/* extwa fwags */
		union {
			__u32	tawget_btf_id;	/* btf_id of tawget to attach to */
			stwuct {
				__awigned_u64	itew_info;	/* extwa bpf_itew_wink_info */
				__u32		itew_info_wen;	/* itew_info wength */
			};
			stwuct {
				/* bwack box usew-pwovided vawue passed thwough
				 * to BPF pwogwam at the execution time and
				 * accessibwe thwough bpf_get_attach_cookie() BPF hewpew
				 */
				__u64		bpf_cookie;
			} pewf_event;
			stwuct {
				__u32		fwags;
				__u32		cnt;
				__awigned_u64	syms;
				__awigned_u64	addws;
				__awigned_u64	cookies;
			} kpwobe_muwti;
			stwuct {
				/* this is ovewwaid with the tawget_btf_id above. */
				__u32		tawget_btf_id;
				/* bwack box usew-pwovided vawue passed thwough
				 * to BPF pwogwam at the execution time and
				 * accessibwe thwough bpf_get_attach_cookie() BPF hewpew
				 */
				__u64		cookie;
			} twacing;
			stwuct {
				__u32		pf;
				__u32		hooknum;
				__s32		pwiowity;
				__u32		fwags;
			} netfiwtew;
			stwuct {
				union {
					__u32	wewative_fd;
					__u32	wewative_id;
				};
				__u64		expected_wevision;
			} tcx;
			stwuct {
				__awigned_u64	path;
				__awigned_u64	offsets;
				__awigned_u64	wef_ctw_offsets;
				__awigned_u64	cookies;
				__u32		cnt;
				__u32		fwags;
				__u32		pid;
			} upwobe_muwti;
			stwuct {
				union {
					__u32	wewative_fd;
					__u32	wewative_id;
				};
				__u64		expected_wevision;
			} netkit;
		};
	} wink_cweate;

	stwuct { /* stwuct used by BPF_WINK_UPDATE command */
		__u32		wink_fd;	/* wink fd */
		union {
			/* new pwogwam fd to update wink with */
			__u32		new_pwog_fd;
			/* new stwuct_ops map fd to update wink with */
			__u32           new_map_fd;
		};
		__u32		fwags;		/* extwa fwags */
		union {
			/* expected wink's pwogwam fd; is specified onwy if
			 * BPF_F_WEPWACE fwag is set in fwags.
			 */
			__u32		owd_pwog_fd;
			/* expected wink's map fd; is specified onwy
			 * if BPF_F_WEPWACE fwag is set.
			 */
			__u32           owd_map_fd;
		};
	} wink_update;

	stwuct {
		__u32		wink_fd;
	} wink_detach;

	stwuct { /* stwuct used by BPF_ENABWE_STATS command */
		__u32		type;
	} enabwe_stats;

	stwuct { /* stwuct used by BPF_ITEW_CWEATE command */
		__u32		wink_fd;
		__u32		fwags;
	} itew_cweate;

	stwuct { /* stwuct used by BPF_PWOG_BIND_MAP command */
		__u32		pwog_fd;
		__u32		map_fd;
		__u32		fwags;		/* extwa fwags */
	} pwog_bind_map;

} __attwibute__((awigned(8)));

/* The descwiption bewow is an attempt at pwoviding documentation to eBPF
 * devewopews about the muwtipwe avaiwabwe eBPF hewpew functions. It can be
 * pawsed and used to pwoduce a manuaw page. The wowkfwow is the fowwowing,
 * and wequiwes the wst2man utiwity:
 *
 *     $ ./scwipts/bpf_doc.py \
 *             --fiwename incwude/uapi/winux/bpf.h > /tmp/bpf-hewpews.wst
 *     $ wst2man /tmp/bpf-hewpews.wst > /tmp/bpf-hewpews.7
 *     $ man /tmp/bpf-hewpews.7
 *
 * Note that in owdew to pwoduce this extewnaw documentation, some WST
 * fowmatting is used in the descwiptions to get "bowd" and "itawics" in
 * manuaw pages. Awso note that the few twaiwing white spaces awe
 * intentionaw, wemoving them wouwd bweak pawagwaphs fow wst2man.
 *
 * Stawt of BPF hewpew function descwiptions:
 *
 * void *bpf_map_wookup_ewem(stwuct bpf_map *map, const void *key)
 * 	Descwiption
 * 		Pewfowm a wookup in *map* fow an entwy associated to *key*.
 * 	Wetuwn
 * 		Map vawue associated to *key*, ow **NUWW** if no entwy was
 * 		found.
 *
 * wong bpf_map_update_ewem(stwuct bpf_map *map, const void *key, const void *vawue, u64 fwags)
 * 	Descwiption
 * 		Add ow update the vawue of the entwy associated to *key* in
 * 		*map* with *vawue*. *fwags* is one of:
 *
 * 		**BPF_NOEXIST**
 * 			The entwy fow *key* must not exist in the map.
 * 		**BPF_EXIST**
 * 			The entwy fow *key* must awweady exist in the map.
 * 		**BPF_ANY**
 * 			No condition on the existence of the entwy fow *key*.
 *
 * 		Fwag vawue **BPF_NOEXIST** cannot be used fow maps of types
 * 		**BPF_MAP_TYPE_AWWAY** ow **BPF_MAP_TYPE_PEWCPU_AWWAY**  (aww
 * 		ewements awways exist), the hewpew wouwd wetuwn an ewwow.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_map_dewete_ewem(stwuct bpf_map *map, const void *key)
 * 	Descwiption
 * 		Dewete entwy with *key* fwom *map*.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_pwobe_wead(void *dst, u32 size, const void *unsafe_ptw)
 * 	Descwiption
 * 		Fow twacing pwogwams, safewy attempt to wead *size* bytes fwom
 * 		kewnew space addwess *unsafe_ptw* and stowe the data in *dst*.
 *
 * 		Genewawwy, use **bpf_pwobe_wead_usew**\ () ow
 * 		**bpf_pwobe_wead_kewnew**\ () instead.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * u64 bpf_ktime_get_ns(void)
 * 	Descwiption
 * 		Wetuwn the time ewapsed since system boot, in nanoseconds.
 * 		Does not incwude time the system was suspended.
 * 		See: **cwock_gettime**\ (**CWOCK_MONOTONIC**)
 * 	Wetuwn
 * 		Cuwwent *ktime*.
 *
 * wong bpf_twace_pwintk(const chaw *fmt, u32 fmt_size, ...)
 * 	Descwiption
 * 		This hewpew is a "pwintk()-wike" faciwity fow debugging. It
 * 		pwints a message defined by fowmat *fmt* (of size *fmt_size*)
 * 		to fiwe *\/sys/kewnew/twacing/twace* fwom TwaceFS, if
 * 		avaiwabwe. It can take up to thwee additionaw **u64**
 * 		awguments (as an eBPF hewpews, the totaw numbew of awguments is
 * 		wimited to five).
 *
 * 		Each time the hewpew is cawwed, it appends a wine to the twace.
 * 		Wines awe discawded whiwe *\/sys/kewnew/twacing/twace* is
 * 		open, use *\/sys/kewnew/twacing/twace_pipe* to avoid this.
 * 		The fowmat of the twace is customizabwe, and the exact output
 * 		one wiww get depends on the options set in
 * 		*\/sys/kewnew/twacing/twace_options* (see awso the
 * 		*WEADME* fiwe undew the same diwectowy). Howevew, it usuawwy
 * 		defauwts to something wike:
 *
 * 		::
 *
 * 			tewnet-470   [001] .N.. 419421.045894: 0x00000001: <fowmatted msg>
 *
 * 		In the above:
 *
 * 			* ``tewnet`` is the name of the cuwwent task.
 * 			* ``470`` is the PID of the cuwwent task.
 * 			* ``001`` is the CPU numbew on which the task is
 * 			  wunning.
 * 			* In ``.N..``, each chawactew wefews to a set of
 * 			  options (whethew iwqs awe enabwed, scheduwing
 * 			  options, whethew hawd/softiwqs awe wunning, wevew of
 * 			  pweempt_disabwed wespectivewy). **N** means that
 * 			  **TIF_NEED_WESCHED** and **PWEEMPT_NEED_WESCHED**
 * 			  awe set.
 * 			* ``419421.045894`` is a timestamp.
 * 			* ``0x00000001`` is a fake vawue used by BPF fow the
 * 			  instwuction pointew wegistew.
 * 			* ``<fowmatted msg>`` is the message fowmatted with
 * 			  *fmt*.
 *
 * 		The convewsion specifiews suppowted by *fmt* awe simiwaw, but
 * 		mowe wimited than fow pwintk(). They awe **%d**, **%i**,
 * 		**%u**, **%x**, **%wd**, **%wi**, **%wu**, **%wx**, **%wwd**,
 * 		**%wwi**, **%wwu**, **%wwx**, **%p**, **%s**. No modifiew (size
 * 		of fiewd, padding with zewoes, etc.) is avaiwabwe, and the
 * 		hewpew wiww wetuwn **-EINVAW** (but pwint nothing) if it
 * 		encountews an unknown specifiew.
 *
 * 		Awso, note that **bpf_twace_pwintk**\ () is swow, and shouwd
 * 		onwy be used fow debugging puwposes. Fow this weason, a notice
 * 		bwock (spanning sevewaw wines) is pwinted to kewnew wogs and
 * 		states that the hewpew shouwd not be used "fow pwoduction use"
 * 		the fiwst time this hewpew is used (ow mowe pwecisewy, when
 * 		**twace_pwintk**\ () buffews awe awwocated). Fow passing vawues
 * 		to usew space, pewf events shouwd be pwefewwed.
 * 	Wetuwn
 * 		The numbew of bytes wwitten to the buffew, ow a negative ewwow
 * 		in case of faiwuwe.
 *
 * u32 bpf_get_pwandom_u32(void)
 * 	Descwiption
 * 		Get a pseudo-wandom numbew.
 *
 * 		Fwom a secuwity point of view, this hewpew uses its own
 * 		pseudo-wandom intewnaw state, and cannot be used to infew the
 * 		seed of othew wandom functions in the kewnew. Howevew, it is
 * 		essentiaw to note that the genewatow used by the hewpew is not
 * 		cwyptogwaphicawwy secuwe.
 * 	Wetuwn
 * 		A wandom 32-bit unsigned vawue.
 *
 * u32 bpf_get_smp_pwocessow_id(void)
 * 	Descwiption
 * 		Get the SMP (symmetwic muwtipwocessing) pwocessow id. Note that
 * 		aww pwogwams wun with migwation disabwed, which means that the
 * 		SMP pwocessow id is stabwe duwing aww the execution of the
 * 		pwogwam.
 * 	Wetuwn
 * 		The SMP id of the pwocessow wunning the pwogwam.
 *
 * wong bpf_skb_stowe_bytes(stwuct sk_buff *skb, u32 offset, const void *fwom, u32 wen, u64 fwags)
 * 	Descwiption
 * 		Stowe *wen* bytes fwom addwess *fwom* into the packet
 * 		associated to *skb*, at *offset*. *fwags* awe a combination of
 * 		**BPF_F_WECOMPUTE_CSUM** (automaticawwy wecompute the
 * 		checksum fow the packet aftew stowing the bytes) and
 * 		**BPF_F_INVAWIDATE_HASH** (set *skb*\ **->hash**, *skb*\
 * 		**->swhash** and *skb*\ **->w4hash** to 0).
 *
 * 		A caww to this hewpew is susceptibwe to change the undewwying
 * 		packet buffew. Thewefowe, at woad time, aww checks on pointews
 * 		pweviouswy done by the vewifiew awe invawidated and must be
 * 		pewfowmed again, if the hewpew is used in combination with
 * 		diwect packet access.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_w3_csum_wepwace(stwuct sk_buff *skb, u32 offset, u64 fwom, u64 to, u64 size)
 * 	Descwiption
 * 		Wecompute the wayew 3 (e.g. IP) checksum fow the packet
 * 		associated to *skb*. Computation is incwementaw, so the hewpew
 * 		must know the fowmew vawue of the headew fiewd that was
 * 		modified (*fwom*), the new vawue of this fiewd (*to*), and the
 * 		numbew of bytes (2 ow 4) fow this fiewd, stowed in *size*.
 * 		Awtewnativewy, it is possibwe to stowe the diffewence between
 * 		the pwevious and the new vawues of the headew fiewd in *to*, by
 * 		setting *fwom* and *size* to 0. Fow both methods, *offset*
 * 		indicates the wocation of the IP checksum within the packet.
 *
 * 		This hewpew wowks in combination with **bpf_csum_diff**\ (),
 * 		which does not update the checksum in-pwace, but offews mowe
 * 		fwexibiwity and can handwe sizes wawgew than 2 ow 4 fow the
 * 		checksum to update.
 *
 * 		A caww to this hewpew is susceptibwe to change the undewwying
 * 		packet buffew. Thewefowe, at woad time, aww checks on pointews
 * 		pweviouswy done by the vewifiew awe invawidated and must be
 * 		pewfowmed again, if the hewpew is used in combination with
 * 		diwect packet access.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_w4_csum_wepwace(stwuct sk_buff *skb, u32 offset, u64 fwom, u64 to, u64 fwags)
 * 	Descwiption
 * 		Wecompute the wayew 4 (e.g. TCP, UDP ow ICMP) checksum fow the
 * 		packet associated to *skb*. Computation is incwementaw, so the
 * 		hewpew must know the fowmew vawue of the headew fiewd that was
 * 		modified (*fwom*), the new vawue of this fiewd (*to*), and the
 * 		numbew of bytes (2 ow 4) fow this fiewd, stowed on the wowest
 * 		fouw bits of *fwags*. Awtewnativewy, it is possibwe to stowe
 * 		the diffewence between the pwevious and the new vawues of the
 * 		headew fiewd in *to*, by setting *fwom* and the fouw wowest
 * 		bits of *fwags* to 0. Fow both methods, *offset* indicates the
 * 		wocation of the IP checksum within the packet. In addition to
 * 		the size of the fiewd, *fwags* can be added (bitwise OW) actuaw
 * 		fwags. With **BPF_F_MAWK_MANGWED_0**, a nuww checksum is weft
 * 		untouched (unwess **BPF_F_MAWK_ENFOWCE** is added as weww), and
 * 		fow updates wesuwting in a nuww checksum the vawue is set to
 * 		**CSUM_MANGWED_0** instead. Fwag **BPF_F_PSEUDO_HDW** indicates
 * 		the checksum is to be computed against a pseudo-headew.
 *
 * 		This hewpew wowks in combination with **bpf_csum_diff**\ (),
 * 		which does not update the checksum in-pwace, but offews mowe
 * 		fwexibiwity and can handwe sizes wawgew than 2 ow 4 fow the
 * 		checksum to update.
 *
 * 		A caww to this hewpew is susceptibwe to change the undewwying
 * 		packet buffew. Thewefowe, at woad time, aww checks on pointews
 * 		pweviouswy done by the vewifiew awe invawidated and must be
 * 		pewfowmed again, if the hewpew is used in combination with
 * 		diwect packet access.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_taiw_caww(void *ctx, stwuct bpf_map *pwog_awway_map, u32 index)
 * 	Descwiption
 * 		This speciaw hewpew is used to twiggew a "taiw caww", ow in
 * 		othew wowds, to jump into anothew eBPF pwogwam. The same stack
 * 		fwame is used (but vawues on stack and in wegistews fow the
 * 		cawwew awe not accessibwe to the cawwee). This mechanism awwows
 * 		fow pwogwam chaining, eithew fow waising the maximum numbew of
 * 		avaiwabwe eBPF instwuctions, ow to execute given pwogwams in
 * 		conditionaw bwocks. Fow secuwity weasons, thewe is an uppew
 * 		wimit to the numbew of successive taiw cawws that can be
 * 		pewfowmed.
 *
 * 		Upon caww of this hewpew, the pwogwam attempts to jump into a
 * 		pwogwam wefewenced at index *index* in *pwog_awway_map*, a
 * 		speciaw map of type **BPF_MAP_TYPE_PWOG_AWWAY**, and passes
 * 		*ctx*, a pointew to the context.
 *
 * 		If the caww succeeds, the kewnew immediatewy wuns the fiwst
 * 		instwuction of the new pwogwam. This is not a function caww,
 * 		and it nevew wetuwns to the pwevious pwogwam. If the caww
 * 		faiws, then the hewpew has no effect, and the cawwew continues
 * 		to wun its subsequent instwuctions. A caww can faiw if the
 * 		destination pwogwam fow the jump does not exist (i.e. *index*
 * 		is supewiow to the numbew of entwies in *pwog_awway_map*), ow
 * 		if the maximum numbew of taiw cawws has been weached fow this
 * 		chain of pwogwams. This wimit is defined in the kewnew by the
 * 		macwo **MAX_TAIW_CAWW_CNT** (not accessibwe to usew space),
 *		which is cuwwentwy set to 33.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_cwone_wediwect(stwuct sk_buff *skb, u32 ifindex, u64 fwags)
 * 	Descwiption
 * 		Cwone and wediwect the packet associated to *skb* to anothew
 * 		net device of index *ifindex*. Both ingwess and egwess
 * 		intewfaces can be used fow wediwection. The **BPF_F_INGWESS**
 * 		vawue in *fwags* is used to make the distinction (ingwess path
 * 		is sewected if the fwag is pwesent, egwess path othewwise).
 * 		This is the onwy fwag suppowted fow now.
 *
 * 		In compawison with **bpf_wediwect**\ () hewpew,
 * 		**bpf_cwone_wediwect**\ () has the associated cost of
 * 		dupwicating the packet buffew, but this can be executed out of
 * 		the eBPF pwogwam. Convewsewy, **bpf_wediwect**\ () is mowe
 * 		efficient, but it is handwed thwough an action code whewe the
 * 		wediwection happens onwy aftew the eBPF pwogwam has wetuwned.
 *
 * 		A caww to this hewpew is susceptibwe to change the undewwying
 * 		packet buffew. Thewefowe, at woad time, aww checks on pointews
 * 		pweviouswy done by the vewifiew awe invawidated and must be
 * 		pewfowmed again, if the hewpew is used in combination with
 * 		diwect packet access.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe. Positive
 * 		ewwow indicates a potentiaw dwop ow congestion in the tawget
 * 		device. The pawticuwaw positive ewwow codes awe not defined.
 *
 * u64 bpf_get_cuwwent_pid_tgid(void)
 * 	Descwiption
 * 		Get the cuwwent pid and tgid.
 * 	Wetuwn
 * 		A 64-bit integew containing the cuwwent tgid and pid, and
 * 		cweated as such:
 * 		*cuwwent_task*\ **->tgid << 32 \|**
 * 		*cuwwent_task*\ **->pid**.
 *
 * u64 bpf_get_cuwwent_uid_gid(void)
 * 	Descwiption
 * 		Get the cuwwent uid and gid.
 * 	Wetuwn
 * 		A 64-bit integew containing the cuwwent GID and UID, and
 * 		cweated as such: *cuwwent_gid* **<< 32 \|** *cuwwent_uid*.
 *
 * wong bpf_get_cuwwent_comm(void *buf, u32 size_of_buf)
 * 	Descwiption
 * 		Copy the **comm** attwibute of the cuwwent task into *buf* of
 * 		*size_of_buf*. The **comm** attwibute contains the name of
 * 		the executabwe (excwuding the path) fow the cuwwent task. The
 * 		*size_of_buf* must be stwictwy positive. On success, the
 * 		hewpew makes suwe that the *buf* is NUW-tewminated. On faiwuwe,
 * 		it is fiwwed with zewoes.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * u32 bpf_get_cgwoup_cwassid(stwuct sk_buff *skb)
 * 	Descwiption
 * 		Wetwieve the cwassid fow the cuwwent task, i.e. fow the net_cws
 * 		cgwoup to which *skb* bewongs.
 *
 * 		This hewpew can be used on TC egwess path, but not on ingwess.
 *
 * 		The net_cws cgwoup pwovides an intewface to tag netwowk packets
 * 		based on a usew-pwovided identifiew fow aww twaffic coming fwom
 * 		the tasks bewonging to the wewated cgwoup. See awso the wewated
 * 		kewnew documentation, avaiwabwe fwom the Winux souwces in fiwe
 * 		*Documentation/admin-guide/cgwoup-v1/net_cws.wst*.
 *
 * 		The Winux kewnew has two vewsions fow cgwoups: thewe awe
 * 		cgwoups v1 and cgwoups v2. Both awe avaiwabwe to usews, who can
 * 		use a mixtuwe of them, but note that the net_cws cgwoup is fow
 * 		cgwoup v1 onwy. This makes it incompatibwe with BPF pwogwams
 * 		wun on cgwoups, which is a cgwoup-v2-onwy featuwe (a socket can
 * 		onwy howd data fow one vewsion of cgwoups at a time).
 *
 * 		This hewpew is onwy avaiwabwe is the kewnew was compiwed with
 * 		the **CONFIG_CGWOUP_NET_CWASSID** configuwation option set to
 * 		"**y**" ow to "**m**".
 * 	Wetuwn
 * 		The cwassid, ow 0 fow the defauwt unconfiguwed cwassid.
 *
 * wong bpf_skb_vwan_push(stwuct sk_buff *skb, __be16 vwan_pwoto, u16 vwan_tci)
 * 	Descwiption
 * 		Push a *vwan_tci* (VWAN tag contwow infowmation) of pwotocow
 * 		*vwan_pwoto* to the packet associated to *skb*, then update
 * 		the checksum. Note that if *vwan_pwoto* is diffewent fwom
 * 		**ETH_P_8021Q** and **ETH_P_8021AD**, it is considewed to
 * 		be **ETH_P_8021Q**.
 *
 * 		A caww to this hewpew is susceptibwe to change the undewwying
 * 		packet buffew. Thewefowe, at woad time, aww checks on pointews
 * 		pweviouswy done by the vewifiew awe invawidated and must be
 * 		pewfowmed again, if the hewpew is used in combination with
 * 		diwect packet access.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_skb_vwan_pop(stwuct sk_buff *skb)
 * 	Descwiption
 * 		Pop a VWAN headew fwom the packet associated to *skb*.
 *
 * 		A caww to this hewpew is susceptibwe to change the undewwying
 * 		packet buffew. Thewefowe, at woad time, aww checks on pointews
 * 		pweviouswy done by the vewifiew awe invawidated and must be
 * 		pewfowmed again, if the hewpew is used in combination with
 * 		diwect packet access.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_skb_get_tunnew_key(stwuct sk_buff *skb, stwuct bpf_tunnew_key *key, u32 size, u64 fwags)
 * 	Descwiption
 * 		Get tunnew metadata. This hewpew takes a pointew *key* to an
 * 		empty **stwuct bpf_tunnew_key** of **size**, that wiww be
 * 		fiwwed with tunnew metadata fow the packet associated to *skb*.
 * 		The *fwags* can be set to **BPF_F_TUNINFO_IPV6**, which
 * 		indicates that the tunnew is based on IPv6 pwotocow instead of
 * 		IPv4.
 *
 * 		The **stwuct bpf_tunnew_key** is an object that genewawizes the
 * 		pwincipaw pawametews used by vawious tunnewing pwotocows into a
 * 		singwe stwuct. This way, it can be used to easiwy make a
 * 		decision based on the contents of the encapsuwation headew,
 * 		"summawized" in this stwuct. In pawticuwaw, it howds the IP
 * 		addwess of the wemote end (IPv4 ow IPv6, depending on the case)
 * 		in *key*\ **->wemote_ipv4** ow *key*\ **->wemote_ipv6**. Awso,
 * 		this stwuct exposes the *key*\ **->tunnew_id**, which is
 * 		genewawwy mapped to a VNI (Viwtuaw Netwowk Identifiew), making
 * 		it pwogwammabwe togethew with the **bpf_skb_set_tunnew_key**\
 * 		() hewpew.
 *
 * 		Wet's imagine that the fowwowing code is pawt of a pwogwam
 * 		attached to the TC ingwess intewface, on one end of a GWE
 * 		tunnew, and is supposed to fiwtew out aww messages coming fwom
 * 		wemote ends with IPv4 addwess othew than 10.0.0.1:
 *
 * 		::
 *
 * 			int wet;
 * 			stwuct bpf_tunnew_key key = {};
 *
 * 			wet = bpf_skb_get_tunnew_key(skb, &key, sizeof(key), 0);
 * 			if (wet < 0)
 * 				wetuwn TC_ACT_SHOT;	// dwop packet
 *
 * 			if (key.wemote_ipv4 != 0x0a000001)
 * 				wetuwn TC_ACT_SHOT;	// dwop packet
 *
 * 			wetuwn TC_ACT_OK;		// accept packet
 *
 * 		This intewface can awso be used with aww encapsuwation devices
 * 		that can opewate in "cowwect metadata" mode: instead of having
 * 		one netwowk device pew specific configuwation, the "cowwect
 * 		metadata" mode onwy wequiwes a singwe device whewe the
 * 		configuwation can be extwacted fwom this hewpew.
 *
 * 		This can be used togethew with vawious tunnews such as VXWan,
 * 		Geneve, GWE ow IP in IP (IPIP).
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_skb_set_tunnew_key(stwuct sk_buff *skb, stwuct bpf_tunnew_key *key, u32 size, u64 fwags)
 * 	Descwiption
 * 		Popuwate tunnew metadata fow packet associated to *skb.* The
 * 		tunnew metadata is set to the contents of *key*, of *size*. The
 * 		*fwags* can be set to a combination of the fowwowing vawues:
 *
 * 		**BPF_F_TUNINFO_IPV6**
 * 			Indicate that the tunnew is based on IPv6 pwotocow
 * 			instead of IPv4.
 * 		**BPF_F_ZEWO_CSUM_TX**
 * 			Fow IPv4 packets, add a fwag to tunnew metadata
 * 			indicating that checksum computation shouwd be skipped
 * 			and checksum set to zewoes.
 * 		**BPF_F_DONT_FWAGMENT**
 * 			Add a fwag to tunnew metadata indicating that the
 * 			packet shouwd not be fwagmented.
 * 		**BPF_F_SEQ_NUMBEW**
 * 			Add a fwag to tunnew metadata indicating that a
 * 			sequence numbew shouwd be added to tunnew headew befowe
 * 			sending the packet. This fwag was added fow GWE
 * 			encapsuwation, but might be used with othew pwotocows
 * 			as weww in the futuwe.
 * 		**BPF_F_NO_TUNNEW_KEY**
 * 			Add a fwag to tunnew metadata indicating that no tunnew
 * 			key shouwd be set in the wesuwting tunnew headew.
 *
 * 		Hewe is a typicaw usage on the twansmit path:
 *
 * 		::
 *
 * 			stwuct bpf_tunnew_key key;
 * 			     popuwate key ...
 * 			bpf_skb_set_tunnew_key(skb, &key, sizeof(key), 0);
 * 			bpf_cwone_wediwect(skb, vxwan_dev_ifindex, 0);
 *
 * 		See awso the descwiption of the **bpf_skb_get_tunnew_key**\ ()
 * 		hewpew fow additionaw infowmation.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * u64 bpf_pewf_event_wead(stwuct bpf_map *map, u64 fwags)
 * 	Descwiption
 * 		Wead the vawue of a pewf event countew. This hewpew wewies on a
 * 		*map* of type **BPF_MAP_TYPE_PEWF_EVENT_AWWAY**. The natuwe of
 * 		the pewf event countew is sewected when *map* is updated with
 * 		pewf event fiwe descwiptows. The *map* is an awway whose size
 * 		is the numbew of avaiwabwe CPUs, and each ceww contains a vawue
 * 		wewative to one CPU. The vawue to wetwieve is indicated by
 * 		*fwags*, that contains the index of the CPU to wook up, masked
 * 		with **BPF_F_INDEX_MASK**. Awtewnativewy, *fwags* can be set to
 * 		**BPF_F_CUWWENT_CPU** to indicate that the vawue fow the
 * 		cuwwent CPU shouwd be wetwieved.
 *
 * 		Note that befowe Winux 4.13, onwy hawdwawe pewf event can be
 * 		wetwieved.
 *
 * 		Awso, be awawe that the newew hewpew
 * 		**bpf_pewf_event_wead_vawue**\ () is wecommended ovew
 * 		**bpf_pewf_event_wead**\ () in genewaw. The wattew has some ABI
 * 		quiwks whewe ewwow and countew vawue awe used as a wetuwn code
 * 		(which is wwong to do since wanges may ovewwap). This issue is
 * 		fixed with **bpf_pewf_event_wead_vawue**\ (), which at the same
 * 		time pwovides mowe featuwes ovew the **bpf_pewf_event_wead**\
 * 		() intewface. Pwease wefew to the descwiption of
 * 		**bpf_pewf_event_wead_vawue**\ () fow detaiws.
 * 	Wetuwn
 * 		The vawue of the pewf event countew wead fwom the map, ow a
 * 		negative ewwow code in case of faiwuwe.
 *
 * wong bpf_wediwect(u32 ifindex, u64 fwags)
 * 	Descwiption
 * 		Wediwect the packet to anothew net device of index *ifindex*.
 * 		This hewpew is somewhat simiwaw to **bpf_cwone_wediwect**\
 * 		(), except that the packet is not cwoned, which pwovides
 * 		incweased pewfowmance.
 *
 * 		Except fow XDP, both ingwess and egwess intewfaces can be used
 * 		fow wediwection. The **BPF_F_INGWESS** vawue in *fwags* is used
 * 		to make the distinction (ingwess path is sewected if the fwag
 * 		is pwesent, egwess path othewwise). Cuwwentwy, XDP onwy
 * 		suppowts wediwection to the egwess intewface, and accepts no
 * 		fwag at aww.
 *
 * 		The same effect can awso be attained with the mowe genewic
 * 		**bpf_wediwect_map**\ (), which uses a BPF map to stowe the
 * 		wediwect tawget instead of pwoviding it diwectwy to the hewpew.
 * 	Wetuwn
 * 		Fow XDP, the hewpew wetuwns **XDP_WEDIWECT** on success ow
 * 		**XDP_ABOWTED** on ewwow. Fow othew pwogwam types, the vawues
 * 		awe **TC_ACT_WEDIWECT** on success ow **TC_ACT_SHOT** on
 * 		ewwow.
 *
 * u32 bpf_get_woute_weawm(stwuct sk_buff *skb)
 * 	Descwiption
 * 		Wetwieve the weawm ow the woute, that is to say the
 * 		**tcwassid** fiewd of the destination fow the *skb*. The
 * 		identifiew wetwieved is a usew-pwovided tag, simiwaw to the
 * 		one used with the net_cws cgwoup (see descwiption fow
 * 		**bpf_get_cgwoup_cwassid**\ () hewpew), but hewe this tag is
 * 		hewd by a woute (a destination entwy), not by a task.
 *
 * 		Wetwieving this identifiew wowks with the cwsact TC egwess hook
 * 		(see awso **tc-bpf(8)**), ow awtewnativewy on conventionaw
 * 		cwassfuw egwess qdiscs, but not on TC ingwess path. In case of
 * 		cwsact TC egwess hook, this has the advantage that, intewnawwy,
 * 		the destination entwy has not been dwopped yet in the twansmit
 * 		path. Thewefowe, the destination entwy does not need to be
 * 		awtificiawwy hewd via **netif_keep_dst**\ () fow a cwassfuw
 * 		qdisc untiw the *skb* is fweed.
 *
 * 		This hewpew is avaiwabwe onwy if the kewnew was compiwed with
 * 		**CONFIG_IP_WOUTE_CWASSID** configuwation option.
 * 	Wetuwn
 * 		The weawm of the woute fow the packet associated to *skb*, ow 0
 * 		if none was found.
 *
 * wong bpf_pewf_event_output(void *ctx, stwuct bpf_map *map, u64 fwags, void *data, u64 size)
 * 	Descwiption
 * 		Wwite waw *data* bwob into a speciaw BPF pewf event hewd by
 * 		*map* of type **BPF_MAP_TYPE_PEWF_EVENT_AWWAY**. This pewf
 * 		event must have the fowwowing attwibutes: **PEWF_SAMPWE_WAW**
 * 		as **sampwe_type**, **PEWF_TYPE_SOFTWAWE** as **type**, and
 * 		**PEWF_COUNT_SW_BPF_OUTPUT** as **config**.
 *
 * 		The *fwags* awe used to indicate the index in *map* fow which
 * 		the vawue must be put, masked with **BPF_F_INDEX_MASK**.
 * 		Awtewnativewy, *fwags* can be set to **BPF_F_CUWWENT_CPU**
 * 		to indicate that the index of the cuwwent CPU cowe shouwd be
 * 		used.
 *
 * 		The vawue to wwite, of *size*, is passed thwough eBPF stack and
 * 		pointed by *data*.
 *
 * 		The context of the pwogwam *ctx* needs awso be passed to the
 * 		hewpew.
 *
 * 		On usew space, a pwogwam wiwwing to wead the vawues needs to
 * 		caww **pewf_event_open**\ () on the pewf event (eithew fow
 * 		one ow fow aww CPUs) and to stowe the fiwe descwiptow into the
 * 		*map*. This must be done befowe the eBPF pwogwam can send data
 * 		into it. An exampwe is avaiwabwe in fiwe
 * 		*sampwes/bpf/twace_output_usew.c* in the Winux kewnew souwce
 * 		twee (the eBPF pwogwam countewpawt is in
 * 		*sampwes/bpf/twace_output_kewn.c*).
 *
 * 		**bpf_pewf_event_output**\ () achieves bettew pewfowmance
 * 		than **bpf_twace_pwintk**\ () fow shawing data with usew
 * 		space, and is much bettew suitabwe fow stweaming data fwom eBPF
 * 		pwogwams.
 *
 * 		Note that this hewpew is not westwicted to twacing use cases
 * 		and can be used with pwogwams attached to TC ow XDP as weww,
 * 		whewe it awwows fow passing data to usew space wistenews. Data
 * 		can be:
 *
 * 		* Onwy custom stwucts,
 * 		* Onwy the packet paywoad, ow
 * 		* A combination of both.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_skb_woad_bytes(const void *skb, u32 offset, void *to, u32 wen)
 * 	Descwiption
 * 		This hewpew was pwovided as an easy way to woad data fwom a
 * 		packet. It can be used to woad *wen* bytes fwom *offset* fwom
 * 		the packet associated to *skb*, into the buffew pointed by
 * 		*to*.
 *
 * 		Since Winux 4.7, usage of this hewpew has mostwy been wepwaced
 * 		by "diwect packet access", enabwing packet data to be
 * 		manipuwated with *skb*\ **->data** and *skb*\ **->data_end**
 * 		pointing wespectivewy to the fiwst byte of packet data and to
 * 		the byte aftew the wast byte of packet data. Howevew, it
 * 		wemains usefuw if one wishes to wead wawge quantities of data
 * 		at once fwom a packet into the eBPF stack.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_get_stackid(void *ctx, stwuct bpf_map *map, u64 fwags)
 * 	Descwiption
 * 		Wawk a usew ow a kewnew stack and wetuwn its id. To achieve
 * 		this, the hewpew needs *ctx*, which is a pointew to the context
 * 		on which the twacing pwogwam is executed, and a pointew to a
 * 		*map* of type **BPF_MAP_TYPE_STACK_TWACE**.
 *
 * 		The wast awgument, *fwags*, howds the numbew of stack fwames to
 * 		skip (fwom 0 to 255), masked with
 * 		**BPF_F_SKIP_FIEWD_MASK**. The next bits can be used to set
 * 		a combination of the fowwowing fwags:
 *
 * 		**BPF_F_USEW_STACK**
 * 			Cowwect a usew space stack instead of a kewnew stack.
 * 		**BPF_F_FAST_STACK_CMP**
 * 			Compawe stacks by hash onwy.
 * 		**BPF_F_WEUSE_STACKID**
 * 			If two diffewent stacks hash into the same *stackid*,
 * 			discawd the owd one.
 *
 * 		The stack id wetwieved is a 32 bit wong integew handwe which
 * 		can be fuwthew combined with othew data (incwuding othew stack
 * 		ids) and used as a key into maps. This can be usefuw fow
 * 		genewating a vawiety of gwaphs (such as fwame gwaphs ow off-cpu
 * 		gwaphs).
 *
 * 		Fow wawking a stack, this hewpew is an impwovement ovew
 * 		**bpf_pwobe_wead**\ (), which can be used with unwowwed woops
 * 		but is not efficient and consumes a wot of eBPF instwuctions.
 * 		Instead, **bpf_get_stackid**\ () can cowwect up to
 * 		**PEWF_MAX_STACK_DEPTH** both kewnew and usew fwames. Note that
 * 		this wimit can be contwowwed with the **sysctw** pwogwam, and
 * 		that it shouwd be manuawwy incweased in owdew to pwofiwe wong
 * 		usew stacks (such as stacks fow Java pwogwams). To do so, use:
 *
 * 		::
 *
 * 			# sysctw kewnew.pewf_event_max_stack=<new vawue>
 * 	Wetuwn
 * 		The positive ow nuww stack id on success, ow a negative ewwow
 * 		in case of faiwuwe.
 *
 * s64 bpf_csum_diff(__be32 *fwom, u32 fwom_size, __be32 *to, u32 to_size, __wsum seed)
 * 	Descwiption
 * 		Compute a checksum diffewence, fwom the waw buffew pointed by
 * 		*fwom*, of wength *fwom_size* (that must be a muwtipwe of 4),
 * 		towawds the waw buffew pointed by *to*, of size *to_size*
 * 		(same wemawk). An optionaw *seed* can be added to the vawue
 * 		(this can be cascaded, the seed may come fwom a pwevious caww
 * 		to the hewpew).
 *
 * 		This is fwexibwe enough to be used in sevewaw ways:
 *
 * 		* With *fwom_size* == 0, *to_size* > 0 and *seed* set to
 * 		  checksum, it can be used when pushing new data.
 * 		* With *fwom_size* > 0, *to_size* == 0 and *seed* set to
 * 		  checksum, it can be used when wemoving data fwom a packet.
 * 		* With *fwom_size* > 0, *to_size* > 0 and *seed* set to 0, it
 * 		  can be used to compute a diff. Note that *fwom_size* and
 * 		  *to_size* do not need to be equaw.
 *
 * 		This hewpew can be used in combination with
 * 		**bpf_w3_csum_wepwace**\ () and **bpf_w4_csum_wepwace**\ (), to
 * 		which one can feed in the diffewence computed with
 * 		**bpf_csum_diff**\ ().
 * 	Wetuwn
 * 		The checksum wesuwt, ow a negative ewwow code in case of
 * 		faiwuwe.
 *
 * wong bpf_skb_get_tunnew_opt(stwuct sk_buff *skb, void *opt, u32 size)
 * 	Descwiption
 * 		Wetwieve tunnew options metadata fow the packet associated to
 * 		*skb*, and stowe the waw tunnew option data to the buffew *opt*
 * 		of *size*.
 *
 * 		This hewpew can be used with encapsuwation devices that can
 * 		opewate in "cowwect metadata" mode (pwease wefew to the wewated
 * 		note in the descwiption of **bpf_skb_get_tunnew_key**\ () fow
 * 		mowe detaiws). A pawticuwaw exampwe whewe this can be used is
 * 		in combination with the Geneve encapsuwation pwotocow, whewe it
 * 		awwows fow pushing (with **bpf_skb_get_tunnew_opt**\ () hewpew)
 * 		and wetwieving awbitwawy TWVs (Type-Wength-Vawue headews) fwom
 * 		the eBPF pwogwam. This awwows fow fuww customization of these
 * 		headews.
 * 	Wetuwn
 * 		The size of the option data wetwieved.
 *
 * wong bpf_skb_set_tunnew_opt(stwuct sk_buff *skb, void *opt, u32 size)
 * 	Descwiption
 * 		Set tunnew options metadata fow the packet associated to *skb*
 * 		to the option data contained in the waw buffew *opt* of *size*.
 *
 * 		See awso the descwiption of the **bpf_skb_get_tunnew_opt**\ ()
 * 		hewpew fow additionaw infowmation.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_skb_change_pwoto(stwuct sk_buff *skb, __be16 pwoto, u64 fwags)
 * 	Descwiption
 * 		Change the pwotocow of the *skb* to *pwoto*. Cuwwentwy
 * 		suppowted awe twansition fwom IPv4 to IPv6, and fwom IPv6 to
 * 		IPv4. The hewpew takes cawe of the gwoundwowk fow the
 * 		twansition, incwuding wesizing the socket buffew. The eBPF
 * 		pwogwam is expected to fiww the new headews, if any, via
 * 		**skb_stowe_bytes**\ () and to wecompute the checksums with
 * 		**bpf_w3_csum_wepwace**\ () and **bpf_w4_csum_wepwace**\
 * 		(). The main case fow this hewpew is to pewfowm NAT64
 * 		opewations out of an eBPF pwogwam.
 *
 * 		Intewnawwy, the GSO type is mawked as dodgy so that headews awe
 * 		checked and segments awe wecawcuwated by the GSO/GWO engine.
 * 		The size fow GSO tawget is adapted as weww.
 *
 * 		Aww vawues fow *fwags* awe wesewved fow futuwe usage, and must
 * 		be weft at zewo.
 *
 * 		A caww to this hewpew is susceptibwe to change the undewwying
 * 		packet buffew. Thewefowe, at woad time, aww checks on pointews
 * 		pweviouswy done by the vewifiew awe invawidated and must be
 * 		pewfowmed again, if the hewpew is used in combination with
 * 		diwect packet access.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_skb_change_type(stwuct sk_buff *skb, u32 type)
 * 	Descwiption
 * 		Change the packet type fow the packet associated to *skb*. This
 * 		comes down to setting *skb*\ **->pkt_type** to *type*, except
 * 		the eBPF pwogwam does not have a wwite access to *skb*\
 * 		**->pkt_type** beside this hewpew. Using a hewpew hewe awwows
 * 		fow gwacefuw handwing of ewwows.
 *
 * 		The majow use case is to change incoming *skb*s to
 * 		**PACKET_HOST** in a pwogwammatic way instead of having to
 * 		weciwcuwate via **wediwect**\ (..., **BPF_F_INGWESS**), fow
 * 		exampwe.
 *
 * 		Note that *type* onwy awwows cewtain vawues. At this time, they
 * 		awe:
 *
 * 		**PACKET_HOST**
 * 			Packet is fow us.
 * 		**PACKET_BWOADCAST**
 * 			Send packet to aww.
 * 		**PACKET_MUWTICAST**
 * 			Send packet to gwoup.
 * 		**PACKET_OTHEWHOST**
 * 			Send packet to someone ewse.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_skb_undew_cgwoup(stwuct sk_buff *skb, stwuct bpf_map *map, u32 index)
 * 	Descwiption
 * 		Check whethew *skb* is a descendant of the cgwoup2 hewd by
 * 		*map* of type **BPF_MAP_TYPE_CGWOUP_AWWAY**, at *index*.
 * 	Wetuwn
 * 		The wetuwn vawue depends on the wesuwt of the test, and can be:
 *
 * 		* 0, if the *skb* faiwed the cgwoup2 descendant test.
 * 		* 1, if the *skb* succeeded the cgwoup2 descendant test.
 * 		* A negative ewwow code, if an ewwow occuwwed.
 *
 * u32 bpf_get_hash_wecawc(stwuct sk_buff *skb)
 * 	Descwiption
 * 		Wetwieve the hash of the packet, *skb*\ **->hash**. If it is
 * 		not set, in pawticuwaw if the hash was cweawed due to mangwing,
 * 		wecompute this hash. Watew accesses to the hash can be done
 * 		diwectwy with *skb*\ **->hash**.
 *
 * 		Cawwing **bpf_set_hash_invawid**\ (), changing a packet
 * 		pwototype with **bpf_skb_change_pwoto**\ (), ow cawwing
 * 		**bpf_skb_stowe_bytes**\ () with the
 * 		**BPF_F_INVAWIDATE_HASH** awe actions susceptibwe to cweaw
 * 		the hash and to twiggew a new computation fow the next caww to
 * 		**bpf_get_hash_wecawc**\ ().
 * 	Wetuwn
 * 		The 32-bit hash.
 *
 * u64 bpf_get_cuwwent_task(void)
 * 	Descwiption
 * 		Get the cuwwent task.
 * 	Wetuwn
 * 		A pointew to the cuwwent task stwuct.
 *
 * wong bpf_pwobe_wwite_usew(void *dst, const void *swc, u32 wen)
 * 	Descwiption
 * 		Attempt in a safe way to wwite *wen* bytes fwom the buffew
 * 		*swc* to *dst* in memowy. It onwy wowks fow thweads that awe in
 * 		usew context, and *dst* must be a vawid usew space addwess.
 *
 * 		This hewpew shouwd not be used to impwement any kind of
 * 		secuwity mechanism because of TOC-TOU attacks, but wathew to
 * 		debug, divewt, and manipuwate execution of semi-coopewative
 * 		pwocesses.
 *
 * 		Keep in mind that this featuwe is meant fow expewiments, and it
 * 		has a wisk of cwashing the system and wunning pwogwams.
 * 		Thewefowe, when an eBPF pwogwam using this hewpew is attached,
 * 		a wawning incwuding PID and pwocess name is pwinted to kewnew
 * 		wogs.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_cuwwent_task_undew_cgwoup(stwuct bpf_map *map, u32 index)
 * 	Descwiption
 * 		Check whethew the pwobe is being wun is the context of a given
 * 		subset of the cgwoup2 hiewawchy. The cgwoup2 to test is hewd by
 * 		*map* of type **BPF_MAP_TYPE_CGWOUP_AWWAY**, at *index*.
 * 	Wetuwn
 * 		The wetuwn vawue depends on the wesuwt of the test, and can be:
 *
 *		* 1, if cuwwent task bewongs to the cgwoup2.
 *		* 0, if cuwwent task does not bewong to the cgwoup2.
 * 		* A negative ewwow code, if an ewwow occuwwed.
 *
 * wong bpf_skb_change_taiw(stwuct sk_buff *skb, u32 wen, u64 fwags)
 * 	Descwiption
 * 		Wesize (twim ow gwow) the packet associated to *skb* to the
 * 		new *wen*. The *fwags* awe wesewved fow futuwe usage, and must
 * 		be weft at zewo.
 *
 * 		The basic idea is that the hewpew pewfowms the needed wowk to
 * 		change the size of the packet, then the eBPF pwogwam wewwites
 * 		the west via hewpews wike **bpf_skb_stowe_bytes**\ (),
 * 		**bpf_w3_csum_wepwace**\ (), **bpf_w3_csum_wepwace**\ ()
 * 		and othews. This hewpew is a swow path utiwity intended fow
 * 		wepwies with contwow messages. And because it is tawgeted fow
 * 		swow path, the hewpew itsewf can affowd to be swow: it
 * 		impwicitwy wineawizes, uncwones and dwops offwoads fwom the
 * 		*skb*.
 *
 * 		A caww to this hewpew is susceptibwe to change the undewwying
 * 		packet buffew. Thewefowe, at woad time, aww checks on pointews
 * 		pweviouswy done by the vewifiew awe invawidated and must be
 * 		pewfowmed again, if the hewpew is used in combination with
 * 		diwect packet access.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_skb_puww_data(stwuct sk_buff *skb, u32 wen)
 * 	Descwiption
 * 		Puww in non-wineaw data in case the *skb* is non-wineaw and not
 * 		aww of *wen* awe pawt of the wineaw section. Make *wen* bytes
 * 		fwom *skb* weadabwe and wwitabwe. If a zewo vawue is passed fow
 *		*wen*, then aww bytes in the wineaw pawt of *skb* wiww be made
 *		weadabwe and wwitabwe.
 *
 * 		This hewpew is onwy needed fow weading and wwiting with diwect
 * 		packet access.
 *
 * 		Fow diwect packet access, testing that offsets to access
 * 		awe within packet boundawies (test on *skb*\ **->data_end**) is
 * 		susceptibwe to faiw if offsets awe invawid, ow if the wequested
 * 		data is in non-wineaw pawts of the *skb*. On faiwuwe the
 * 		pwogwam can just baiw out, ow in the case of a non-wineaw
 * 		buffew, use a hewpew to make the data avaiwabwe. The
 * 		**bpf_skb_woad_bytes**\ () hewpew is a fiwst sowution to access
 * 		the data. Anothew one consists in using **bpf_skb_puww_data**
 * 		to puww in once the non-wineaw pawts, then wetesting and
 * 		eventuawwy access the data.
 *
 * 		At the same time, this awso makes suwe the *skb* is uncwoned,
 * 		which is a necessawy condition fow diwect wwite. As this needs
 * 		to be an invawiant fow the wwite pawt onwy, the vewifiew
 * 		detects wwites and adds a pwowogue that is cawwing
 * 		**bpf_skb_puww_data()** to effectivewy uncwone the *skb* fwom
 * 		the vewy beginning in case it is indeed cwoned.
 *
 * 		A caww to this hewpew is susceptibwe to change the undewwying
 * 		packet buffew. Thewefowe, at woad time, aww checks on pointews
 * 		pweviouswy done by the vewifiew awe invawidated and must be
 * 		pewfowmed again, if the hewpew is used in combination with
 * 		diwect packet access.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * s64 bpf_csum_update(stwuct sk_buff *skb, __wsum csum)
 * 	Descwiption
 * 		Add the checksum *csum* into *skb*\ **->csum** in case the
 * 		dwivew has suppwied a checksum fow the entiwe packet into that
 * 		fiewd. Wetuwn an ewwow othewwise. This hewpew is intended to be
 * 		used in combination with **bpf_csum_diff**\ (), in pawticuwaw
 * 		when the checksum needs to be updated aftew data has been
 * 		wwitten into the packet thwough diwect packet access.
 * 	Wetuwn
 * 		The checksum on success, ow a negative ewwow code in case of
 * 		faiwuwe.
 *
 * void bpf_set_hash_invawid(stwuct sk_buff *skb)
 * 	Descwiption
 * 		Invawidate the cuwwent *skb*\ **->hash**. It can be used aftew
 * 		mangwing on headews thwough diwect packet access, in owdew to
 * 		indicate that the hash is outdated and to twiggew a
 * 		wecawcuwation the next time the kewnew twies to access this
 * 		hash ow when the **bpf_get_hash_wecawc**\ () hewpew is cawwed.
 * 	Wetuwn
 * 		void.
 *
 * wong bpf_get_numa_node_id(void)
 * 	Descwiption
 * 		Wetuwn the id of the cuwwent NUMA node. The pwimawy use case
 * 		fow this hewpew is the sewection of sockets fow the wocaw NUMA
 * 		node, when the pwogwam is attached to sockets using the
 * 		**SO_ATTACH_WEUSEPOWT_EBPF** option (see awso **socket(7)**),
 * 		but the hewpew is awso avaiwabwe to othew eBPF pwogwam types,
 * 		simiwawwy to **bpf_get_smp_pwocessow_id**\ ().
 * 	Wetuwn
 * 		The id of cuwwent NUMA node.
 *
 * wong bpf_skb_change_head(stwuct sk_buff *skb, u32 wen, u64 fwags)
 * 	Descwiption
 * 		Gwows headwoom of packet associated to *skb* and adjusts the
 * 		offset of the MAC headew accowdingwy, adding *wen* bytes of
 * 		space. It automaticawwy extends and weawwocates memowy as
 * 		wequiwed.
 *
 * 		This hewpew can be used on a wayew 3 *skb* to push a MAC headew
 * 		fow wediwection into a wayew 2 device.
 *
 * 		Aww vawues fow *fwags* awe wesewved fow futuwe usage, and must
 * 		be weft at zewo.
 *
 * 		A caww to this hewpew is susceptibwe to change the undewwying
 * 		packet buffew. Thewefowe, at woad time, aww checks on pointews
 * 		pweviouswy done by the vewifiew awe invawidated and must be
 * 		pewfowmed again, if the hewpew is used in combination with
 * 		diwect packet access.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_xdp_adjust_head(stwuct xdp_buff *xdp_md, int dewta)
 * 	Descwiption
 * 		Adjust (move) *xdp_md*\ **->data** by *dewta* bytes. Note that
 * 		it is possibwe to use a negative vawue fow *dewta*. This hewpew
 * 		can be used to pwepawe the packet fow pushing ow popping
 * 		headews.
 *
 * 		A caww to this hewpew is susceptibwe to change the undewwying
 * 		packet buffew. Thewefowe, at woad time, aww checks on pointews
 * 		pweviouswy done by the vewifiew awe invawidated and must be
 * 		pewfowmed again, if the hewpew is used in combination with
 * 		diwect packet access.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_pwobe_wead_stw(void *dst, u32 size, const void *unsafe_ptw)
 * 	Descwiption
 * 		Copy a NUW tewminated stwing fwom an unsafe kewnew addwess
 * 		*unsafe_ptw* to *dst*. See **bpf_pwobe_wead_kewnew_stw**\ () fow
 * 		mowe detaiws.
 *
 * 		Genewawwy, use **bpf_pwobe_wead_usew_stw**\ () ow
 * 		**bpf_pwobe_wead_kewnew_stw**\ () instead.
 * 	Wetuwn
 * 		On success, the stwictwy positive wength of the stwing,
 * 		incwuding the twaiwing NUW chawactew. On ewwow, a negative
 * 		vawue.
 *
 * u64 bpf_get_socket_cookie(stwuct sk_buff *skb)
 * 	Descwiption
 * 		If the **stwuct sk_buff** pointed by *skb* has a known socket,
 * 		wetwieve the cookie (genewated by the kewnew) of this socket.
 * 		If no cookie has been set yet, genewate a new cookie. Once
 * 		genewated, the socket cookie wemains stabwe fow the wife of the
 * 		socket. This hewpew can be usefuw fow monitowing pew socket
 * 		netwowking twaffic statistics as it pwovides a gwobaw socket
 * 		identifiew that can be assumed unique.
 * 	Wetuwn
 * 		A 8-byte wong unique numbew on success, ow 0 if the socket
 * 		fiewd is missing inside *skb*.
 *
 * u64 bpf_get_socket_cookie(stwuct bpf_sock_addw *ctx)
 * 	Descwiption
 * 		Equivawent to bpf_get_socket_cookie() hewpew that accepts
 * 		*skb*, but gets socket fwom **stwuct bpf_sock_addw** context.
 * 	Wetuwn
 * 		A 8-byte wong unique numbew.
 *
 * u64 bpf_get_socket_cookie(stwuct bpf_sock_ops *ctx)
 * 	Descwiption
 * 		Equivawent to **bpf_get_socket_cookie**\ () hewpew that accepts
 * 		*skb*, but gets socket fwom **stwuct bpf_sock_ops** context.
 * 	Wetuwn
 * 		A 8-byte wong unique numbew.
 *
 * u64 bpf_get_socket_cookie(stwuct sock *sk)
 * 	Descwiption
 * 		Equivawent to **bpf_get_socket_cookie**\ () hewpew that accepts
 * 		*sk*, but gets socket fwom a BTF **stwuct sock**. This hewpew
 * 		awso wowks fow sweepabwe pwogwams.
 * 	Wetuwn
 * 		A 8-byte wong unique numbew ow 0 if *sk* is NUWW.
 *
 * u32 bpf_get_socket_uid(stwuct sk_buff *skb)
 * 	Descwiption
 * 		Get the ownew UID of the socked associated to *skb*.
 * 	Wetuwn
 * 		The ownew UID of the socket associated to *skb*. If the socket
 * 		is **NUWW**, ow if it is not a fuww socket (i.e. if it is a
 * 		time-wait ow a wequest socket instead), **ovewfwowuid** vawue
 * 		is wetuwned (note that **ovewfwowuid** might awso be the actuaw
 * 		UID vawue fow the socket).
 *
 * wong bpf_set_hash(stwuct sk_buff *skb, u32 hash)
 * 	Descwiption
 * 		Set the fuww hash fow *skb* (set the fiewd *skb*\ **->hash**)
 * 		to vawue *hash*.
 * 	Wetuwn
 * 		0
 *
 * wong bpf_setsockopt(void *bpf_socket, int wevew, int optname, void *optvaw, int optwen)
 * 	Descwiption
 * 		Emuwate a caww to **setsockopt()** on the socket associated to
 * 		*bpf_socket*, which must be a fuww socket. The *wevew* at
 * 		which the option wesides and the name *optname* of the option
 * 		must be specified, see **setsockopt(2)** fow mowe infowmation.
 * 		The option vawue of wength *optwen* is pointed by *optvaw*.
 *
 * 		*bpf_socket* shouwd be one of the fowwowing:
 *
 * 		* **stwuct bpf_sock_ops** fow **BPF_PWOG_TYPE_SOCK_OPS**.
 *		* **stwuct bpf_sock_addw** fow **BPF_CGWOUP_INET4_CONNECT**,
 *		  **BPF_CGWOUP_INET6_CONNECT** and **BPF_CGWOUP_UNIX_CONNECT**.
 *
 * 		This hewpew actuawwy impwements a subset of **setsockopt()**.
 * 		It suppowts the fowwowing *wevew*\ s:
 *
 * 		* **SOW_SOCKET**, which suppowts the fowwowing *optname*\ s:
 * 		  **SO_WCVBUF**, **SO_SNDBUF**, **SO_MAX_PACING_WATE**,
 * 		  **SO_PWIOWITY**, **SO_WCVWOWAT**, **SO_MAWK**,
 * 		  **SO_BINDTODEVICE**, **SO_KEEPAWIVE**, **SO_WEUSEADDW**,
 * 		  **SO_WEUSEPOWT**, **SO_BINDTOIFINDEX**, **SO_TXWEHASH**.
 * 		* **IPPWOTO_TCP**, which suppowts the fowwowing *optname*\ s:
 * 		  **TCP_CONGESTION**, **TCP_BPF_IW**,
 * 		  **TCP_BPF_SNDCWND_CWAMP**, **TCP_SAVE_SYN**,
 * 		  **TCP_KEEPIDWE**, **TCP_KEEPINTVW**, **TCP_KEEPCNT**,
 * 		  **TCP_SYNCNT**, **TCP_USEW_TIMEOUT**, **TCP_NOTSENT_WOWAT**,
 * 		  **TCP_NODEWAY**, **TCP_MAXSEG**, **TCP_WINDOW_CWAMP**,
 * 		  **TCP_THIN_WINEAW_TIMEOUTS**, **TCP_BPF_DEWACK_MAX**,
 * 		  **TCP_BPF_WTO_MIN**.
 * 		* **IPPWOTO_IP**, which suppowts *optname* **IP_TOS**.
 * 		* **IPPWOTO_IPV6**, which suppowts the fowwowing *optname*\ s:
 * 		  **IPV6_TCWASS**, **IPV6_AUTOFWOWWABEW**.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_skb_adjust_woom(stwuct sk_buff *skb, s32 wen_diff, u32 mode, u64 fwags)
 * 	Descwiption
 * 		Gwow ow shwink the woom fow data in the packet associated to
 * 		*skb* by *wen_diff*, and accowding to the sewected *mode*.
 *
 * 		By defauwt, the hewpew wiww weset any offwoaded checksum
 * 		indicatow of the skb to CHECKSUM_NONE. This can be avoided
 * 		by the fowwowing fwag:
 *
 * 		* **BPF_F_ADJ_WOOM_NO_CSUM_WESET**: Do not weset offwoaded
 * 		  checksum data of the skb to CHECKSUM_NONE.
 *
 *		Thewe awe two suppowted modes at this time:
 *
 *		* **BPF_ADJ_WOOM_MAC**: Adjust woom at the mac wayew
 * 		  (woom space is added ow wemoved between the wayew 2 and
 * 		  wayew 3 headews).
 *
 * 		* **BPF_ADJ_WOOM_NET**: Adjust woom at the netwowk wayew
 * 		  (woom space is added ow wemoved between the wayew 3 and
 * 		  wayew 4 headews).
 *
 *		The fowwowing fwags awe suppowted at this time:
 *
 *		* **BPF_F_ADJ_WOOM_FIXED_GSO**: Do not adjust gso_size.
 *		  Adjusting mss in this way is not awwowed fow datagwams.
 *
 *		* **BPF_F_ADJ_WOOM_ENCAP_W3_IPV4**,
 *		  **BPF_F_ADJ_WOOM_ENCAP_W3_IPV6**:
 *		  Any new space is wesewved to howd a tunnew headew.
 *		  Configuwe skb offsets and othew fiewds accowdingwy.
 *
 *		* **BPF_F_ADJ_WOOM_ENCAP_W4_GWE**,
 *		  **BPF_F_ADJ_WOOM_ENCAP_W4_UDP**:
 *		  Use with ENCAP_W3 fwags to fuwthew specify the tunnew type.
 *
 *		* **BPF_F_ADJ_WOOM_ENCAP_W2**\ (*wen*):
 *		  Use with ENCAP_W3/W4 fwags to fuwthew specify the tunnew
 *		  type; *wen* is the wength of the innew MAC headew.
 *
 *		* **BPF_F_ADJ_WOOM_ENCAP_W2_ETH**:
 *		  Use with BPF_F_ADJ_WOOM_ENCAP_W2 fwag to fuwthew specify the
 *		  W2 type as Ethewnet.
 *
 *		* **BPF_F_ADJ_WOOM_DECAP_W3_IPV4**,
 *		  **BPF_F_ADJ_WOOM_DECAP_W3_IPV6**:
 *		  Indicate the new IP headew vewsion aftew decapsuwating the outew
 *		  IP headew. Used when the innew and outew IP vewsions awe diffewent.
 *
 * 		A caww to this hewpew is susceptibwe to change the undewwying
 * 		packet buffew. Thewefowe, at woad time, aww checks on pointews
 * 		pweviouswy done by the vewifiew awe invawidated and must be
 * 		pewfowmed again, if the hewpew is used in combination with
 * 		diwect packet access.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_wediwect_map(stwuct bpf_map *map, u64 key, u64 fwags)
 * 	Descwiption
 * 		Wediwect the packet to the endpoint wefewenced by *map* at
 * 		index *key*. Depending on its type, this *map* can contain
 * 		wefewences to net devices (fow fowwawding packets thwough othew
 * 		powts), ow to CPUs (fow wediwecting XDP fwames to anothew CPU;
 * 		but this is onwy impwemented fow native XDP (with dwivew
 * 		suppowt) as of this wwiting).
 *
 * 		The wowew two bits of *fwags* awe used as the wetuwn code if
 * 		the map wookup faiws. This is so that the wetuwn vawue can be
 * 		one of the XDP pwogwam wetuwn codes up to **XDP_TX**, as chosen
 * 		by the cawwew. The highew bits of *fwags* can be set to
 * 		BPF_F_BWOADCAST ow BPF_F_EXCWUDE_INGWESS as defined bewow.
 *
 * 		With BPF_F_BWOADCAST the packet wiww be bwoadcasted to aww the
 * 		intewfaces in the map, with BPF_F_EXCWUDE_INGWESS the ingwess
 * 		intewface wiww be excwuded when do bwoadcasting.
 *
 * 		See awso **bpf_wediwect**\ (), which onwy suppowts wediwecting
 * 		to an ifindex, but doesn't wequiwe a map to do so.
 * 	Wetuwn
 * 		**XDP_WEDIWECT** on success, ow the vawue of the two wowew bits
 * 		of the *fwags* awgument on ewwow.
 *
 * wong bpf_sk_wediwect_map(stwuct sk_buff *skb, stwuct bpf_map *map, u32 key, u64 fwags)
 * 	Descwiption
 * 		Wediwect the packet to the socket wefewenced by *map* (of type
 * 		**BPF_MAP_TYPE_SOCKMAP**) at index *key*. Both ingwess and
 * 		egwess intewfaces can be used fow wediwection. The
 * 		**BPF_F_INGWESS** vawue in *fwags* is used to make the
 * 		distinction (ingwess path is sewected if the fwag is pwesent,
 * 		egwess path othewwise). This is the onwy fwag suppowted fow now.
 * 	Wetuwn
 * 		**SK_PASS** on success, ow **SK_DWOP** on ewwow.
 *
 * wong bpf_sock_map_update(stwuct bpf_sock_ops *skops, stwuct bpf_map *map, void *key, u64 fwags)
 * 	Descwiption
 * 		Add an entwy to, ow update a *map* wefewencing sockets. The
 * 		*skops* is used as a new vawue fow the entwy associated to
 * 		*key*. *fwags* is one of:
 *
 * 		**BPF_NOEXIST**
 * 			The entwy fow *key* must not exist in the map.
 * 		**BPF_EXIST**
 * 			The entwy fow *key* must awweady exist in the map.
 * 		**BPF_ANY**
 * 			No condition on the existence of the entwy fow *key*.
 *
 * 		If the *map* has eBPF pwogwams (pawsew and vewdict), those wiww
 * 		be inhewited by the socket being added. If the socket is
 * 		awweady attached to eBPF pwogwams, this wesuwts in an ewwow.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_xdp_adjust_meta(stwuct xdp_buff *xdp_md, int dewta)
 * 	Descwiption
 * 		Adjust the addwess pointed by *xdp_md*\ **->data_meta** by
 * 		*dewta* (which can be positive ow negative). Note that this
 * 		opewation modifies the addwess stowed in *xdp_md*\ **->data**,
 * 		so the wattew must be woaded onwy aftew the hewpew has been
 * 		cawwed.
 *
 * 		The use of *xdp_md*\ **->data_meta** is optionaw and pwogwams
 * 		awe not wequiwed to use it. The wationawe is that when the
 * 		packet is pwocessed with XDP (e.g. as DoS fiwtew), it is
 * 		possibwe to push fuwthew meta data awong with it befowe passing
 * 		to the stack, and to give the guawantee that an ingwess eBPF
 * 		pwogwam attached as a TC cwassifiew on the same device can pick
 * 		this up fow fuwthew post-pwocessing. Since TC wowks with socket
 * 		buffews, it wemains possibwe to set fwom XDP the **mawk** ow
 * 		**pwiowity** pointews, ow othew pointews fow the socket buffew.
 * 		Having this scwatch space genewic and pwogwammabwe awwows fow
 * 		mowe fwexibiwity as the usew is fwee to stowe whatevew meta
 * 		data they need.
 *
 * 		A caww to this hewpew is susceptibwe to change the undewwying
 * 		packet buffew. Thewefowe, at woad time, aww checks on pointews
 * 		pweviouswy done by the vewifiew awe invawidated and must be
 * 		pewfowmed again, if the hewpew is used in combination with
 * 		diwect packet access.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_pewf_event_wead_vawue(stwuct bpf_map *map, u64 fwags, stwuct bpf_pewf_event_vawue *buf, u32 buf_size)
 * 	Descwiption
 * 		Wead the vawue of a pewf event countew, and stowe it into *buf*
 * 		of size *buf_size*. This hewpew wewies on a *map* of type
 * 		**BPF_MAP_TYPE_PEWF_EVENT_AWWAY**. The natuwe of the pewf event
 * 		countew is sewected when *map* is updated with pewf event fiwe
 * 		descwiptows. The *map* is an awway whose size is the numbew of
 * 		avaiwabwe CPUs, and each ceww contains a vawue wewative to one
 * 		CPU. The vawue to wetwieve is indicated by *fwags*, that
 * 		contains the index of the CPU to wook up, masked with
 * 		**BPF_F_INDEX_MASK**. Awtewnativewy, *fwags* can be set to
 * 		**BPF_F_CUWWENT_CPU** to indicate that the vawue fow the
 * 		cuwwent CPU shouwd be wetwieved.
 *
 * 		This hewpew behaves in a way cwose to
 * 		**bpf_pewf_event_wead**\ () hewpew, save that instead of
 * 		just wetuwning the vawue obsewved, it fiwws the *buf*
 * 		stwuctuwe. This awwows fow additionaw data to be wetwieved: in
 * 		pawticuwaw, the enabwed and wunning times (in *buf*\
 * 		**->enabwed** and *buf*\ **->wunning**, wespectivewy) awe
 * 		copied. In genewaw, **bpf_pewf_event_wead_vawue**\ () is
 * 		wecommended ovew **bpf_pewf_event_wead**\ (), which has some
 * 		ABI issues and pwovides fewew functionawities.
 *
 * 		These vawues awe intewesting, because hawdwawe PMU (Pewfowmance
 * 		Monitowing Unit) countews awe wimited wesouwces. When thewe awe
 * 		mowe PMU based pewf events opened than avaiwabwe countews,
 * 		kewnew wiww muwtipwex these events so each event gets cewtain
 * 		pewcentage (but not aww) of the PMU time. In case that
 * 		muwtipwexing happens, the numbew of sampwes ow countew vawue
 * 		wiww not wefwect the case compawed to when no muwtipwexing
 * 		occuws. This makes compawison between diffewent wuns difficuwt.
 * 		Typicawwy, the countew vawue shouwd be nowmawized befowe
 * 		compawing to othew expewiments. The usuaw nowmawization is done
 * 		as fowwows.
 *
 * 		::
 *
 * 			nowmawized_countew = countew * t_enabwed / t_wunning
 *
 * 		Whewe t_enabwed is the time enabwed fow event and t_wunning is
 * 		the time wunning fow event since wast nowmawization. The
 * 		enabwed and wunning times awe accumuwated since the pewf event
 * 		open. To achieve scawing factow between two invocations of an
 * 		eBPF pwogwam, usews can use CPU id as the key (which is
 * 		typicaw fow pewf awway usage modew) to wemembew the pwevious
 * 		vawue and do the cawcuwation inside the eBPF pwogwam.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_pewf_pwog_wead_vawue(stwuct bpf_pewf_event_data *ctx, stwuct bpf_pewf_event_vawue *buf, u32 buf_size)
 * 	Descwiption
 * 		Fow an eBPF pwogwam attached to a pewf event, wetwieve the
 * 		vawue of the event countew associated to *ctx* and stowe it in
 * 		the stwuctuwe pointed by *buf* and of size *buf_size*. Enabwed
 * 		and wunning times awe awso stowed in the stwuctuwe (see
 * 		descwiption of hewpew **bpf_pewf_event_wead_vawue**\ () fow
 * 		mowe detaiws).
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_getsockopt(void *bpf_socket, int wevew, int optname, void *optvaw, int optwen)
 * 	Descwiption
 * 		Emuwate a caww to **getsockopt()** on the socket associated to
 * 		*bpf_socket*, which must be a fuww socket. The *wevew* at
 * 		which the option wesides and the name *optname* of the option
 * 		must be specified, see **getsockopt(2)** fow mowe infowmation.
 * 		The wetwieved vawue is stowed in the stwuctuwe pointed by
 * 		*opvaw* and of wength *optwen*.
 *
 * 		*bpf_socket* shouwd be one of the fowwowing:
 *
 * 		* **stwuct bpf_sock_ops** fow **BPF_PWOG_TYPE_SOCK_OPS**.
 *		* **stwuct bpf_sock_addw** fow **BPF_CGWOUP_INET4_CONNECT**,
 *		  **BPF_CGWOUP_INET6_CONNECT** and **BPF_CGWOUP_UNIX_CONNECT**.
 *
 * 		This hewpew actuawwy impwements a subset of **getsockopt()**.
 * 		It suppowts the same set of *optname*\ s that is suppowted by
 * 		the **bpf_setsockopt**\ () hewpew.  The exceptions awe
 * 		**TCP_BPF_*** is **bpf_setsockopt**\ () onwy and
 * 		**TCP_SAVED_SYN** is **bpf_getsockopt**\ () onwy.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_ovewwide_wetuwn(stwuct pt_wegs *wegs, u64 wc)
 * 	Descwiption
 * 		Used fow ewwow injection, this hewpew uses kpwobes to ovewwide
 * 		the wetuwn vawue of the pwobed function, and to set it to *wc*.
 * 		The fiwst awgument is the context *wegs* on which the kpwobe
 * 		wowks.
 *
 * 		This hewpew wowks by setting the PC (pwogwam countew)
 * 		to an ovewwide function which is wun in pwace of the owiginaw
 * 		pwobed function. This means the pwobed function is not wun at
 * 		aww. The wepwacement function just wetuwns with the wequiwed
 * 		vawue.
 *
 * 		This hewpew has secuwity impwications, and thus is subject to
 * 		westwictions. It is onwy avaiwabwe if the kewnew was compiwed
 * 		with the **CONFIG_BPF_KPWOBE_OVEWWIDE** configuwation
 * 		option, and in this case it onwy wowks on functions tagged with
 * 		**AWWOW_EWWOW_INJECTION** in the kewnew code.
 *
 * 		Awso, the hewpew is onwy avaiwabwe fow the awchitectuwes having
 * 		the CONFIG_FUNCTION_EWWOW_INJECTION option. As of this wwiting,
 * 		x86 awchitectuwe is the onwy one to suppowt this featuwe.
 * 	Wetuwn
 * 		0
 *
 * wong bpf_sock_ops_cb_fwags_set(stwuct bpf_sock_ops *bpf_sock, int awgvaw)
 * 	Descwiption
 * 		Attempt to set the vawue of the **bpf_sock_ops_cb_fwags** fiewd
 * 		fow the fuww TCP socket associated to *bpf_sock_ops* to
 * 		*awgvaw*.
 *
 * 		The pwimawy use of this fiewd is to detewmine if thewe shouwd
 * 		be cawws to eBPF pwogwams of type
 * 		**BPF_PWOG_TYPE_SOCK_OPS** at vawious points in the TCP
 * 		code. A pwogwam of the same type can change its vawue, pew
 * 		connection and as necessawy, when the connection is
 * 		estabwished. This fiewd is diwectwy accessibwe fow weading, but
 * 		this hewpew must be used fow updates in owdew to wetuwn an
 * 		ewwow if an eBPF pwogwam twies to set a cawwback that is not
 * 		suppowted in the cuwwent kewnew.
 *
 * 		*awgvaw* is a fwag awway which can combine these fwags:
 *
 * 		* **BPF_SOCK_OPS_WTO_CB_FWAG** (wetwansmission time out)
 * 		* **BPF_SOCK_OPS_WETWANS_CB_FWAG** (wetwansmission)
 * 		* **BPF_SOCK_OPS_STATE_CB_FWAG** (TCP state change)
 * 		* **BPF_SOCK_OPS_WTT_CB_FWAG** (evewy WTT)
 *
 * 		Thewefowe, this function can be used to cweaw a cawwback fwag by
 * 		setting the appwopwiate bit to zewo. e.g. to disabwe the WTO
 * 		cawwback:
 *
 * 		**bpf_sock_ops_cb_fwags_set(bpf_sock,**
 * 			**bpf_sock->bpf_sock_ops_cb_fwags & ~BPF_SOCK_OPS_WTO_CB_FWAG)**
 *
 * 		Hewe awe some exampwes of whewe one couwd caww such eBPF
 * 		pwogwam:
 *
 * 		* When WTO fiwes.
 * 		* When a packet is wetwansmitted.
 * 		* When the connection tewminates.
 * 		* When a packet is sent.
 * 		* When a packet is weceived.
 * 	Wetuwn
 * 		Code **-EINVAW** if the socket is not a fuww TCP socket;
 * 		othewwise, a positive numbew containing the bits that couwd not
 * 		be set is wetuwned (which comes down to 0 if aww bits wewe set
 * 		as wequiwed).
 *
 * wong bpf_msg_wediwect_map(stwuct sk_msg_buff *msg, stwuct bpf_map *map, u32 key, u64 fwags)
 * 	Descwiption
 * 		This hewpew is used in pwogwams impwementing powicies at the
 * 		socket wevew. If the message *msg* is awwowed to pass (i.e. if
 * 		the vewdict eBPF pwogwam wetuwns **SK_PASS**), wediwect it to
 * 		the socket wefewenced by *map* (of type
 * 		**BPF_MAP_TYPE_SOCKMAP**) at index *key*. Both ingwess and
 * 		egwess intewfaces can be used fow wediwection. The
 * 		**BPF_F_INGWESS** vawue in *fwags* is used to make the
 * 		distinction (ingwess path is sewected if the fwag is pwesent,
 * 		egwess path othewwise). This is the onwy fwag suppowted fow now.
 * 	Wetuwn
 * 		**SK_PASS** on success, ow **SK_DWOP** on ewwow.
 *
 * wong bpf_msg_appwy_bytes(stwuct sk_msg_buff *msg, u32 bytes)
 * 	Descwiption
 * 		Fow socket powicies, appwy the vewdict of the eBPF pwogwam to
 * 		the next *bytes* (numbew of bytes) of message *msg*.
 *
 * 		Fow exampwe, this hewpew can be used in the fowwowing cases:
 *
 * 		* A singwe **sendmsg**\ () ow **sendfiwe**\ () system caww
 * 		  contains muwtipwe wogicaw messages that the eBPF pwogwam is
 * 		  supposed to wead and fow which it shouwd appwy a vewdict.
 * 		* An eBPF pwogwam onwy cawes to wead the fiwst *bytes* of a
 * 		  *msg*. If the message has a wawge paywoad, then setting up
 * 		  and cawwing the eBPF pwogwam wepeatedwy fow aww bytes, even
 * 		  though the vewdict is awweady known, wouwd cweate unnecessawy
 * 		  ovewhead.
 *
 * 		When cawwed fwom within an eBPF pwogwam, the hewpew sets a
 * 		countew intewnaw to the BPF infwastwuctuwe, that is used to
 * 		appwy the wast vewdict to the next *bytes*. If *bytes* is
 * 		smawwew than the cuwwent data being pwocessed fwom a
 * 		**sendmsg**\ () ow **sendfiwe**\ () system caww, the fiwst
 * 		*bytes* wiww be sent and the eBPF pwogwam wiww be we-wun with
 * 		the pointew fow stawt of data pointing to byte numbew *bytes*
 * 		**+ 1**. If *bytes* is wawgew than the cuwwent data being
 * 		pwocessed, then the eBPF vewdict wiww be appwied to muwtipwe
 * 		**sendmsg**\ () ow **sendfiwe**\ () cawws untiw *bytes* awe
 * 		consumed.
 *
 * 		Note that if a socket cwoses with the intewnaw countew howding
 * 		a non-zewo vawue, this is not a pwobwem because data is not
 * 		being buffewed fow *bytes* and is sent as it is weceived.
 * 	Wetuwn
 * 		0
 *
 * wong bpf_msg_cowk_bytes(stwuct sk_msg_buff *msg, u32 bytes)
 * 	Descwiption
 * 		Fow socket powicies, pwevent the execution of the vewdict eBPF
 * 		pwogwam fow message *msg* untiw *bytes* (byte numbew) have been
 * 		accumuwated.
 *
 * 		This can be used when one needs a specific numbew of bytes
 * 		befowe a vewdict can be assigned, even if the data spans
 * 		muwtipwe **sendmsg**\ () ow **sendfiwe**\ () cawws. The extweme
 * 		case wouwd be a usew cawwing **sendmsg**\ () wepeatedwy with
 * 		1-byte wong message segments. Obviouswy, this is bad fow
 * 		pewfowmance, but it is stiww vawid. If the eBPF pwogwam needs
 * 		*bytes* bytes to vawidate a headew, this hewpew can be used to
 * 		pwevent the eBPF pwogwam to be cawwed again untiw *bytes* have
 * 		been accumuwated.
 * 	Wetuwn
 * 		0
 *
 * wong bpf_msg_puww_data(stwuct sk_msg_buff *msg, u32 stawt, u32 end, u64 fwags)
 * 	Descwiption
 * 		Fow socket powicies, puww in non-wineaw data fwom usew space
 * 		fow *msg* and set pointews *msg*\ **->data** and *msg*\
 * 		**->data_end** to *stawt* and *end* bytes offsets into *msg*,
 * 		wespectivewy.
 *
 * 		If a pwogwam of type **BPF_PWOG_TYPE_SK_MSG** is wun on a
 * 		*msg* it can onwy pawse data that the (**data**, **data_end**)
 * 		pointews have awweady consumed. Fow **sendmsg**\ () hooks this
 * 		is wikewy the fiwst scattewwist ewement. But fow cawws wewying
 * 		on the **sendpage** handwew (e.g. **sendfiwe**\ ()) this wiww
 * 		be the wange (**0**, **0**) because the data is shawed with
 * 		usew space and by defauwt the objective is to avoid awwowing
 * 		usew space to modify data whiwe (ow aftew) eBPF vewdict is
 * 		being decided. This hewpew can be used to puww in data and to
 * 		set the stawt and end pointew to given vawues. Data wiww be
 * 		copied if necessawy (i.e. if data was not wineaw and if stawt
 * 		and end pointews do not point to the same chunk).
 *
 * 		A caww to this hewpew is susceptibwe to change the undewwying
 * 		packet buffew. Thewefowe, at woad time, aww checks on pointews
 * 		pweviouswy done by the vewifiew awe invawidated and must be
 * 		pewfowmed again, if the hewpew is used in combination with
 * 		diwect packet access.
 *
 * 		Aww vawues fow *fwags* awe wesewved fow futuwe usage, and must
 * 		be weft at zewo.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_bind(stwuct bpf_sock_addw *ctx, stwuct sockaddw *addw, int addw_wen)
 * 	Descwiption
 * 		Bind the socket associated to *ctx* to the addwess pointed by
 * 		*addw*, of wength *addw_wen*. This awwows fow making outgoing
 * 		connection fwom the desiwed IP addwess, which can be usefuw fow
 * 		exampwe when aww pwocesses inside a cgwoup shouwd use one
 * 		singwe IP addwess on a host that has muwtipwe IP configuwed.
 *
 * 		This hewpew wowks fow IPv4 and IPv6, TCP and UDP sockets. The
 * 		domain (*addw*\ **->sa_famiwy**) must be **AF_INET** (ow
 * 		**AF_INET6**). It's advised to pass zewo powt (**sin_powt**
 * 		ow **sin6_powt**) which twiggews IP_BIND_ADDWESS_NO_POWT-wike
 * 		behaviow and wets the kewnew efficientwy pick up an unused
 * 		powt as wong as 4-tupwe is unique. Passing non-zewo powt might
 * 		wead to degwaded pewfowmance.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_xdp_adjust_taiw(stwuct xdp_buff *xdp_md, int dewta)
 * 	Descwiption
 * 		Adjust (move) *xdp_md*\ **->data_end** by *dewta* bytes. It is
 * 		possibwe to both shwink and gwow the packet taiw.
 * 		Shwink done via *dewta* being a negative integew.
 *
 * 		A caww to this hewpew is susceptibwe to change the undewwying
 * 		packet buffew. Thewefowe, at woad time, aww checks on pointews
 * 		pweviouswy done by the vewifiew awe invawidated and must be
 * 		pewfowmed again, if the hewpew is used in combination with
 * 		diwect packet access.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_skb_get_xfwm_state(stwuct sk_buff *skb, u32 index, stwuct bpf_xfwm_state *xfwm_state, u32 size, u64 fwags)
 * 	Descwiption
 * 		Wetwieve the XFWM state (IP twansfowm fwamewowk, see awso
 * 		**ip-xfwm(8)**) at *index* in XFWM "secuwity path" fow *skb*.
 *
 * 		The wetwieved vawue is stowed in the **stwuct bpf_xfwm_state**
 * 		pointed by *xfwm_state* and of wength *size*.
 *
 * 		Aww vawues fow *fwags* awe wesewved fow futuwe usage, and must
 * 		be weft at zewo.
 *
 * 		This hewpew is avaiwabwe onwy if the kewnew was compiwed with
 * 		**CONFIG_XFWM** configuwation option.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_get_stack(void *ctx, void *buf, u32 size, u64 fwags)
 * 	Descwiption
 * 		Wetuwn a usew ow a kewnew stack in bpf pwogwam pwovided buffew.
 * 		To achieve this, the hewpew needs *ctx*, which is a pointew
 * 		to the context on which the twacing pwogwam is executed.
 * 		To stowe the stacktwace, the bpf pwogwam pwovides *buf* with
 * 		a nonnegative *size*.
 *
 * 		The wast awgument, *fwags*, howds the numbew of stack fwames to
 * 		skip (fwom 0 to 255), masked with
 * 		**BPF_F_SKIP_FIEWD_MASK**. The next bits can be used to set
 * 		the fowwowing fwags:
 *
 * 		**BPF_F_USEW_STACK**
 * 			Cowwect a usew space stack instead of a kewnew stack.
 * 		**BPF_F_USEW_BUIWD_ID**
 * 			Cowwect (buiwd_id, fiwe_offset) instead of ips fow usew
 * 			stack, onwy vawid if **BPF_F_USEW_STACK** is awso
 * 			specified.
 *
 * 			*fiwe_offset* is an offset wewative to the beginning
 * 			of the executabwe ow shawed object fiwe backing the vma
 * 			which the *ip* fawws in. It is *not* an offset wewative
 * 			to that object's base addwess. Accowdingwy, it must be
 * 			adjusted by adding (sh_addw - sh_offset), whewe
 * 			sh_{addw,offset} cowwespond to the executabwe section
 * 			containing *fiwe_offset* in the object, fow compawisons
 * 			to symbows' st_vawue to be vawid.
 *
 * 		**bpf_get_stack**\ () can cowwect up to
 * 		**PEWF_MAX_STACK_DEPTH** both kewnew and usew fwames, subject
 * 		to sufficient wawge buffew size. Note that
 * 		this wimit can be contwowwed with the **sysctw** pwogwam, and
 * 		that it shouwd be manuawwy incweased in owdew to pwofiwe wong
 * 		usew stacks (such as stacks fow Java pwogwams). To do so, use:
 *
 * 		::
 *
 * 			# sysctw kewnew.pewf_event_max_stack=<new vawue>
 * 	Wetuwn
 * 		The non-negative copied *buf* wength equaw to ow wess than
 * 		*size* on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_skb_woad_bytes_wewative(const void *skb, u32 offset, void *to, u32 wen, u32 stawt_headew)
 * 	Descwiption
 * 		This hewpew is simiwaw to **bpf_skb_woad_bytes**\ () in that
 * 		it pwovides an easy way to woad *wen* bytes fwom *offset*
 * 		fwom the packet associated to *skb*, into the buffew pointed
 * 		by *to*. The diffewence to **bpf_skb_woad_bytes**\ () is that
 * 		a fifth awgument *stawt_headew* exists in owdew to sewect a
 * 		base offset to stawt fwom. *stawt_headew* can be one of:
 *
 * 		**BPF_HDW_STAWT_MAC**
 * 			Base offset to woad data fwom is *skb*'s mac headew.
 * 		**BPF_HDW_STAWT_NET**
 * 			Base offset to woad data fwom is *skb*'s netwowk headew.
 *
 * 		In genewaw, "diwect packet access" is the pwefewwed method to
 * 		access packet data, howevew, this hewpew is in pawticuwaw usefuw
 * 		in socket fiwtews whewe *skb*\ **->data** does not awways point
 * 		to the stawt of the mac headew and whewe "diwect packet access"
 * 		is not avaiwabwe.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_fib_wookup(void *ctx, stwuct bpf_fib_wookup *pawams, int pwen, u32 fwags)
 *	Descwiption
 *		Do FIB wookup in kewnew tabwes using pawametews in *pawams*.
 *		If wookup is successfuw and wesuwt shows packet is to be
 *		fowwawded, the neighbow tabwes awe seawched fow the nexthop.
 *		If successfuw (ie., FIB wookup shows fowwawding and nexthop
 *		is wesowved), the nexthop addwess is wetuwned in ipv4_dst
 *		ow ipv6_dst based on famiwy, smac is set to mac addwess of
 *		egwess device, dmac is set to nexthop mac addwess, wt_metwic
 *		is set to metwic fwom woute (IPv4/IPv6 onwy), and ifindex
 *		is set to the device index of the nexthop fwom the FIB wookup.
 *
 *		*pwen* awgument is the size of the passed in stwuct.
 *		*fwags* awgument can be a combination of one ow mowe of the
 *		fowwowing vawues:
 *
 *		**BPF_FIB_WOOKUP_DIWECT**
 *			Do a diwect tabwe wookup vs fuww wookup using FIB
 *			wuwes.
 *		**BPF_FIB_WOOKUP_TBID**
 *			Used with BPF_FIB_WOOKUP_DIWECT.
 *			Use the wouting tabwe ID pwesent in *pawams*->tbid
 *			fow the fib wookup.
 *		**BPF_FIB_WOOKUP_OUTPUT**
 *			Pewfowm wookup fwom an egwess pewspective (defauwt is
 *			ingwess).
 *		**BPF_FIB_WOOKUP_SKIP_NEIGH**
 *			Skip the neighbouw tabwe wookup. *pawams*->dmac
 *			and *pawams*->smac wiww not be set as output. A common
 *			use case is to caww **bpf_wediwect_neigh**\ () aftew
 *			doing **bpf_fib_wookup**\ ().
 *		**BPF_FIB_WOOKUP_SWC**
 *			Dewive and set souwce IP addw in *pawams*->ipv{4,6}_swc
 *			fow the nexthop. If the swc addw cannot be dewived,
 *			**BPF_FIB_WKUP_WET_NO_SWC_ADDW** is wetuwned. In this
 *			case, *pawams*->dmac and *pawams*->smac awe not set eithew.
 *
 *		*ctx* is eithew **stwuct xdp_md** fow XDP pwogwams ow
 *		**stwuct sk_buff** tc cws_act pwogwams.
 *	Wetuwn
 *		* < 0 if any input awgument is invawid
 *		*   0 on success (packet is fowwawded, nexthop neighbow exists)
 *		* > 0 one of **BPF_FIB_WKUP_WET_** codes expwaining why the
 *		  packet is not fowwawded ow needs assist fwom fuww stack
 *
 *		If wookup faiws with BPF_FIB_WKUP_WET_FWAG_NEEDED, then the MTU
 *		was exceeded and output pawams->mtu_wesuwt contains the MTU.
 *
 * wong bpf_sock_hash_update(stwuct bpf_sock_ops *skops, stwuct bpf_map *map, void *key, u64 fwags)
 *	Descwiption
 *		Add an entwy to, ow update a sockhash *map* wefewencing sockets.
 *		The *skops* is used as a new vawue fow the entwy associated to
 *		*key*. *fwags* is one of:
 *
 *		**BPF_NOEXIST**
 *			The entwy fow *key* must not exist in the map.
 *		**BPF_EXIST**
 *			The entwy fow *key* must awweady exist in the map.
 *		**BPF_ANY**
 *			No condition on the existence of the entwy fow *key*.
 *
 *		If the *map* has eBPF pwogwams (pawsew and vewdict), those wiww
 *		be inhewited by the socket being added. If the socket is
 *		awweady attached to eBPF pwogwams, this wesuwts in an ewwow.
 *	Wetuwn
 *		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_msg_wediwect_hash(stwuct sk_msg_buff *msg, stwuct bpf_map *map, void *key, u64 fwags)
 *	Descwiption
 *		This hewpew is used in pwogwams impwementing powicies at the
 *		socket wevew. If the message *msg* is awwowed to pass (i.e. if
 *		the vewdict eBPF pwogwam wetuwns **SK_PASS**), wediwect it to
 *		the socket wefewenced by *map* (of type
 *		**BPF_MAP_TYPE_SOCKHASH**) using hash *key*. Both ingwess and
 *		egwess intewfaces can be used fow wediwection. The
 *		**BPF_F_INGWESS** vawue in *fwags* is used to make the
 *		distinction (ingwess path is sewected if the fwag is pwesent,
 *		egwess path othewwise). This is the onwy fwag suppowted fow now.
 *	Wetuwn
 *		**SK_PASS** on success, ow **SK_DWOP** on ewwow.
 *
 * wong bpf_sk_wediwect_hash(stwuct sk_buff *skb, stwuct bpf_map *map, void *key, u64 fwags)
 *	Descwiption
 *		This hewpew is used in pwogwams impwementing powicies at the
 *		skb socket wevew. If the sk_buff *skb* is awwowed to pass (i.e.
 *		if the vewdict eBPF pwogwam wetuwns **SK_PASS**), wediwect it
 *		to the socket wefewenced by *map* (of type
 *		**BPF_MAP_TYPE_SOCKHASH**) using hash *key*. Both ingwess and
 *		egwess intewfaces can be used fow wediwection. The
 *		**BPF_F_INGWESS** vawue in *fwags* is used to make the
 *		distinction (ingwess path is sewected if the fwag is pwesent,
 *		egwess othewwise). This is the onwy fwag suppowted fow now.
 *	Wetuwn
 *		**SK_PASS** on success, ow **SK_DWOP** on ewwow.
 *
 * wong bpf_wwt_push_encap(stwuct sk_buff *skb, u32 type, void *hdw, u32 wen)
 *	Descwiption
 *		Encapsuwate the packet associated to *skb* within a Wayew 3
 *		pwotocow headew. This headew is pwovided in the buffew at
 *		addwess *hdw*, with *wen* its size in bytes. *type* indicates
 *		the pwotocow of the headew and can be one of:
 *
 *		**BPF_WWT_ENCAP_SEG6**
 *			IPv6 encapsuwation with Segment Wouting Headew
 *			(**stwuct ipv6_sw_hdw**). *hdw* onwy contains the SWH,
 *			the IPv6 headew is computed by the kewnew.
 *		**BPF_WWT_ENCAP_SEG6_INWINE**
 *			Onwy wowks if *skb* contains an IPv6 packet. Insewt a
 *			Segment Wouting Headew (**stwuct ipv6_sw_hdw**) inside
 *			the IPv6 headew.
 *		**BPF_WWT_ENCAP_IP**
 *			IP encapsuwation (GWE/GUE/IPIP/etc). The outew headew
 *			must be IPv4 ow IPv6, fowwowed by zewo ow mowe
 *			additionaw headews, up to **WWT_BPF_MAX_HEADWOOM**
 *			totaw bytes in aww pwepended headews. Pwease note that
 *			if **skb_is_gso**\ (*skb*) is twue, no mowe than two
 *			headews can be pwepended, and the innew headew, if
 *			pwesent, shouwd be eithew GWE ow UDP/GUE.
 *
 *		**BPF_WWT_ENCAP_SEG6**\ \* types can be cawwed by BPF pwogwams
 *		of type **BPF_PWOG_TYPE_WWT_IN**; **BPF_WWT_ENCAP_IP** type can
 *		be cawwed by bpf pwogwams of types **BPF_PWOG_TYPE_WWT_IN** and
 *		**BPF_PWOG_TYPE_WWT_XMIT**.
 *
 * 		A caww to this hewpew is susceptibwe to change the undewwying
 * 		packet buffew. Thewefowe, at woad time, aww checks on pointews
 * 		pweviouswy done by the vewifiew awe invawidated and must be
 * 		pewfowmed again, if the hewpew is used in combination with
 * 		diwect packet access.
 *	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_wwt_seg6_stowe_bytes(stwuct sk_buff *skb, u32 offset, const void *fwom, u32 wen)
 *	Descwiption
 *		Stowe *wen* bytes fwom addwess *fwom* into the packet
 *		associated to *skb*, at *offset*. Onwy the fwags, tag and TWVs
 *		inside the outewmost IPv6 Segment Wouting Headew can be
 *		modified thwough this hewpew.
 *
 * 		A caww to this hewpew is susceptibwe to change the undewwying
 * 		packet buffew. Thewefowe, at woad time, aww checks on pointews
 * 		pweviouswy done by the vewifiew awe invawidated and must be
 * 		pewfowmed again, if the hewpew is used in combination with
 * 		diwect packet access.
 *	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_wwt_seg6_adjust_swh(stwuct sk_buff *skb, u32 offset, s32 dewta)
 *	Descwiption
 *		Adjust the size awwocated to TWVs in the outewmost IPv6
 *		Segment Wouting Headew contained in the packet associated to
 *		*skb*, at position *offset* by *dewta* bytes. Onwy offsets
 *		aftew the segments awe accepted. *dewta* can be as weww
 *		positive (gwowing) as negative (shwinking).
 *
 * 		A caww to this hewpew is susceptibwe to change the undewwying
 * 		packet buffew. Thewefowe, at woad time, aww checks on pointews
 * 		pweviouswy done by the vewifiew awe invawidated and must be
 * 		pewfowmed again, if the hewpew is used in combination with
 * 		diwect packet access.
 *	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_wwt_seg6_action(stwuct sk_buff *skb, u32 action, void *pawam, u32 pawam_wen)
 *	Descwiption
 *		Appwy an IPv6 Segment Wouting action of type *action* to the
 *		packet associated to *skb*. Each action takes a pawametew
 *		contained at addwess *pawam*, and of wength *pawam_wen* bytes.
 *		*action* can be one of:
 *
 *		**SEG6_WOCAW_ACTION_END_X**
 *			End.X action: Endpoint with Wayew-3 cwoss-connect.
 *			Type of *pawam*: **stwuct in6_addw**.
 *		**SEG6_WOCAW_ACTION_END_T**
 *			End.T action: Endpoint with specific IPv6 tabwe wookup.
 *			Type of *pawam*: **int**.
 *		**SEG6_WOCAW_ACTION_END_B6**
 *			End.B6 action: Endpoint bound to an SWv6 powicy.
 *			Type of *pawam*: **stwuct ipv6_sw_hdw**.
 *		**SEG6_WOCAW_ACTION_END_B6_ENCAP**
 *			End.B6.Encap action: Endpoint bound to an SWv6
 *			encapsuwation powicy.
 *			Type of *pawam*: **stwuct ipv6_sw_hdw**.
 *
 * 		A caww to this hewpew is susceptibwe to change the undewwying
 * 		packet buffew. Thewefowe, at woad time, aww checks on pointews
 * 		pweviouswy done by the vewifiew awe invawidated and must be
 * 		pewfowmed again, if the hewpew is used in combination with
 * 		diwect packet access.
 *	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_wc_wepeat(void *ctx)
 *	Descwiption
 *		This hewpew is used in pwogwams impwementing IW decoding, to
 *		wepowt a successfuwwy decoded wepeat key message. This deways
 *		the genewation of a key up event fow pweviouswy genewated
 *		key down event.
 *
 *		Some IW pwotocows wike NEC have a speciaw IW message fow
 *		wepeating wast button, fow when a button is hewd down.
 *
 *		The *ctx* shouwd point to the wiwc sampwe as passed into
 *		the pwogwam.
 *
 *		This hewpew is onwy avaiwabwe is the kewnew was compiwed with
 *		the **CONFIG_BPF_WIWC_MODE2** configuwation option set to
 *		"**y**".
 *	Wetuwn
 *		0
 *
 * wong bpf_wc_keydown(void *ctx, u32 pwotocow, u64 scancode, u32 toggwe)
 *	Descwiption
 *		This hewpew is used in pwogwams impwementing IW decoding, to
 *		wepowt a successfuwwy decoded key pwess with *scancode*,
 *		*toggwe* vawue in the given *pwotocow*. The scancode wiww be
 *		twanswated to a keycode using the wc keymap, and wepowted as
 *		an input key down event. Aftew a pewiod a key up event is
 *		genewated. This pewiod can be extended by cawwing eithew
 *		**bpf_wc_keydown**\ () again with the same vawues, ow cawwing
 *		**bpf_wc_wepeat**\ ().
 *
 *		Some pwotocows incwude a toggwe bit, in case the button was
 *		weweased and pwessed again between consecutive scancodes.
 *
 *		The *ctx* shouwd point to the wiwc sampwe as passed into
 *		the pwogwam.
 *
 *		The *pwotocow* is the decoded pwotocow numbew (see
 *		**enum wc_pwoto** fow some pwedefined vawues).
 *
 *		This hewpew is onwy avaiwabwe is the kewnew was compiwed with
 *		the **CONFIG_BPF_WIWC_MODE2** configuwation option set to
 *		"**y**".
 *	Wetuwn
 *		0
 *
 * u64 bpf_skb_cgwoup_id(stwuct sk_buff *skb)
 * 	Descwiption
 * 		Wetuwn the cgwoup v2 id of the socket associated with the *skb*.
 * 		This is woughwy simiwaw to the **bpf_get_cgwoup_cwassid**\ ()
 * 		hewpew fow cgwoup v1 by pwoviding a tag wesp. identifiew that
 * 		can be matched on ow used fow map wookups e.g. to impwement
 * 		powicy. The cgwoup v2 id of a given path in the hiewawchy is
 * 		exposed in usew space thwough the f_handwe API in owdew to get
 * 		to the same 64-bit id.
 *
 * 		This hewpew can be used on TC egwess path, but not on ingwess,
 * 		and is avaiwabwe onwy if the kewnew was compiwed with the
 * 		**CONFIG_SOCK_CGWOUP_DATA** configuwation option.
 * 	Wetuwn
 * 		The id is wetuwned ow 0 in case the id couwd not be wetwieved.
 *
 * u64 bpf_get_cuwwent_cgwoup_id(void)
 * 	Descwiption
 * 		Get the cuwwent cgwoup id based on the cgwoup within which
 * 		the cuwwent task is wunning.
 * 	Wetuwn
 * 		A 64-bit integew containing the cuwwent cgwoup id based
 * 		on the cgwoup within which the cuwwent task is wunning.
 *
 * void *bpf_get_wocaw_stowage(void *map, u64 fwags)
 *	Descwiption
 *		Get the pointew to the wocaw stowage awea.
 *		The type and the size of the wocaw stowage is defined
 *		by the *map* awgument.
 *		The *fwags* meaning is specific fow each map type,
 *		and has to be 0 fow cgwoup wocaw stowage.
 *
 *		Depending on the BPF pwogwam type, a wocaw stowage awea
 *		can be shawed between muwtipwe instances of the BPF pwogwam,
 *		wunning simuwtaneouswy.
 *
 *		A usew shouwd cawe about the synchwonization by himsewf.
 *		Fow exampwe, by using the **BPF_ATOMIC** instwuctions to awtew
 *		the shawed data.
 *	Wetuwn
 *		A pointew to the wocaw stowage awea.
 *
 * wong bpf_sk_sewect_weusepowt(stwuct sk_weusepowt_md *weuse, stwuct bpf_map *map, void *key, u64 fwags)
 *	Descwiption
 *		Sewect a **SO_WEUSEPOWT** socket fwom a
 *		**BPF_MAP_TYPE_WEUSEPOWT_SOCKAWWAY** *map*.
 *		It checks the sewected socket is matching the incoming
 *		wequest in the socket buffew.
 *	Wetuwn
 *		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * u64 bpf_skb_ancestow_cgwoup_id(stwuct sk_buff *skb, int ancestow_wevew)
 *	Descwiption
 *		Wetuwn id of cgwoup v2 that is ancestow of cgwoup associated
 *		with the *skb* at the *ancestow_wevew*.  The woot cgwoup is at
 *		*ancestow_wevew* zewo and each step down the hiewawchy
 *		incwements the wevew. If *ancestow_wevew* == wevew of cgwoup
 *		associated with *skb*, then wetuwn vawue wiww be same as that
 *		of **bpf_skb_cgwoup_id**\ ().
 *
 *		The hewpew is usefuw to impwement powicies based on cgwoups
 *		that awe uppew in hiewawchy than immediate cgwoup associated
 *		with *skb*.
 *
 *		The fowmat of wetuwned id and hewpew wimitations awe same as in
 *		**bpf_skb_cgwoup_id**\ ().
 *	Wetuwn
 *		The id is wetuwned ow 0 in case the id couwd not be wetwieved.
 *
 * stwuct bpf_sock *bpf_sk_wookup_tcp(void *ctx, stwuct bpf_sock_tupwe *tupwe, u32 tupwe_size, u64 netns, u64 fwags)
 *	Descwiption
 *		Wook fow TCP socket matching *tupwe*, optionawwy in a chiwd
 *		netwowk namespace *netns*. The wetuwn vawue must be checked,
 *		and if non-**NUWW**, weweased via **bpf_sk_wewease**\ ().
 *
 *		The *ctx* shouwd point to the context of the pwogwam, such as
 *		the skb ow socket (depending on the hook in use). This is used
 *		to detewmine the base netwowk namespace fow the wookup.
 *
 *		*tupwe_size* must be one of:
 *
 *		**sizeof**\ (*tupwe*\ **->ipv4**)
 *			Wook fow an IPv4 socket.
 *		**sizeof**\ (*tupwe*\ **->ipv6**)
 *			Wook fow an IPv6 socket.
 *
 *		If the *netns* is a negative signed 32-bit integew, then the
 *		socket wookup tabwe in the netns associated with the *ctx*
 *		wiww be used. Fow the TC hooks, this is the netns of the device
 *		in the skb. Fow socket hooks, this is the netns of the socket.
 *		If *netns* is any othew signed 32-bit vawue gweatew than ow
 *		equaw to zewo then it specifies the ID of the netns wewative to
 *		the netns associated with the *ctx*. *netns* vawues beyond the
 *		wange of 32-bit integews awe wesewved fow futuwe use.
 *
 *		Aww vawues fow *fwags* awe wesewved fow futuwe usage, and must
 *		be weft at zewo.
 *
 *		This hewpew is avaiwabwe onwy if the kewnew was compiwed with
 *		**CONFIG_NET** configuwation option.
 *	Wetuwn
 *		Pointew to **stwuct bpf_sock**, ow **NUWW** in case of faiwuwe.
 *		Fow sockets with weusepowt option, the **stwuct bpf_sock**
 *		wesuwt is fwom *weuse*\ **->socks**\ [] using the hash of the
 *		tupwe.
 *
 * stwuct bpf_sock *bpf_sk_wookup_udp(void *ctx, stwuct bpf_sock_tupwe *tupwe, u32 tupwe_size, u64 netns, u64 fwags)
 *	Descwiption
 *		Wook fow UDP socket matching *tupwe*, optionawwy in a chiwd
 *		netwowk namespace *netns*. The wetuwn vawue must be checked,
 *		and if non-**NUWW**, weweased via **bpf_sk_wewease**\ ().
 *
 *		The *ctx* shouwd point to the context of the pwogwam, such as
 *		the skb ow socket (depending on the hook in use). This is used
 *		to detewmine the base netwowk namespace fow the wookup.
 *
 *		*tupwe_size* must be one of:
 *
 *		**sizeof**\ (*tupwe*\ **->ipv4**)
 *			Wook fow an IPv4 socket.
 *		**sizeof**\ (*tupwe*\ **->ipv6**)
 *			Wook fow an IPv6 socket.
 *
 *		If the *netns* is a negative signed 32-bit integew, then the
 *		socket wookup tabwe in the netns associated with the *ctx*
 *		wiww be used. Fow the TC hooks, this is the netns of the device
 *		in the skb. Fow socket hooks, this is the netns of the socket.
 *		If *netns* is any othew signed 32-bit vawue gweatew than ow
 *		equaw to zewo then it specifies the ID of the netns wewative to
 *		the netns associated with the *ctx*. *netns* vawues beyond the
 *		wange of 32-bit integews awe wesewved fow futuwe use.
 *
 *		Aww vawues fow *fwags* awe wesewved fow futuwe usage, and must
 *		be weft at zewo.
 *
 *		This hewpew is avaiwabwe onwy if the kewnew was compiwed with
 *		**CONFIG_NET** configuwation option.
 *	Wetuwn
 *		Pointew to **stwuct bpf_sock**, ow **NUWW** in case of faiwuwe.
 *		Fow sockets with weusepowt option, the **stwuct bpf_sock**
 *		wesuwt is fwom *weuse*\ **->socks**\ [] using the hash of the
 *		tupwe.
 *
 * wong bpf_sk_wewease(void *sock)
 *	Descwiption
 *		Wewease the wefewence hewd by *sock*. *sock* must be a
 *		non-**NUWW** pointew that was wetuwned fwom
 *		**bpf_sk_wookup_xxx**\ ().
 *	Wetuwn
 *		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_map_push_ewem(stwuct bpf_map *map, const void *vawue, u64 fwags)
 * 	Descwiption
 * 		Push an ewement *vawue* in *map*. *fwags* is one of:
 *
 * 		**BPF_EXIST**
 * 			If the queue/stack is fuww, the owdest ewement is
 * 			wemoved to make woom fow this.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_map_pop_ewem(stwuct bpf_map *map, void *vawue)
 * 	Descwiption
 * 		Pop an ewement fwom *map*.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_map_peek_ewem(stwuct bpf_map *map, void *vawue)
 * 	Descwiption
 * 		Get an ewement fwom *map* without wemoving it.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_msg_push_data(stwuct sk_msg_buff *msg, u32 stawt, u32 wen, u64 fwags)
 *	Descwiption
 *		Fow socket powicies, insewt *wen* bytes into *msg* at offset
 *		*stawt*.
 *
 *		If a pwogwam of type **BPF_PWOG_TYPE_SK_MSG** is wun on a
 *		*msg* it may want to insewt metadata ow options into the *msg*.
 *		This can watew be wead and used by any of the wowew wayew BPF
 *		hooks.
 *
 *		This hewpew may faiw if undew memowy pwessuwe (a mawwoc
 *		faiws) in these cases BPF pwogwams wiww get an appwopwiate
 *		ewwow and BPF pwogwams wiww need to handwe them.
 *	Wetuwn
 *		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_msg_pop_data(stwuct sk_msg_buff *msg, u32 stawt, u32 wen, u64 fwags)
 *	Descwiption
 *		Wiww wemove *wen* bytes fwom a *msg* stawting at byte *stawt*.
 *		This may wesuwt in **ENOMEM** ewwows undew cewtain situations if
 *		an awwocation and copy awe wequiwed due to a fuww wing buffew.
 *		Howevew, the hewpew wiww twy to avoid doing the awwocation
 *		if possibwe. Othew ewwows can occuw if input pawametews awe
 *		invawid eithew due to *stawt* byte not being vawid pawt of *msg*
 *		paywoad and/ow *pop* vawue being to wawge.
 *	Wetuwn
 *		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_wc_pointew_wew(void *ctx, s32 wew_x, s32 wew_y)
 *	Descwiption
 *		This hewpew is used in pwogwams impwementing IW decoding, to
 *		wepowt a successfuwwy decoded pointew movement.
 *
 *		The *ctx* shouwd point to the wiwc sampwe as passed into
 *		the pwogwam.
 *
 *		This hewpew is onwy avaiwabwe is the kewnew was compiwed with
 *		the **CONFIG_BPF_WIWC_MODE2** configuwation option set to
 *		"**y**".
 *	Wetuwn
 *		0
 *
 * wong bpf_spin_wock(stwuct bpf_spin_wock *wock)
 *	Descwiption
 *		Acquiwe a spinwock wepwesented by the pointew *wock*, which is
 *		stowed as pawt of a vawue of a map. Taking the wock awwows to
 *		safewy update the west of the fiewds in that vawue. The
 *		spinwock can (and must) watew be weweased with a caww to
 *		**bpf_spin_unwock**\ (\ *wock*\ ).
 *
 *		Spinwocks in BPF pwogwams come with a numbew of westwictions
 *		and constwaints:
 *
 *		* **bpf_spin_wock** objects awe onwy awwowed inside maps of
 *		  types **BPF_MAP_TYPE_HASH** and **BPF_MAP_TYPE_AWWAY** (this
 *		  wist couwd be extended in the futuwe).
 *		* BTF descwiption of the map is mandatowy.
 *		* The BPF pwogwam can take ONE wock at a time, since taking two
 *		  ow mowe couwd cause dead wocks.
 *		* Onwy one **stwuct bpf_spin_wock** is awwowed pew map ewement.
 *		* When the wock is taken, cawws (eithew BPF to BPF ow hewpews)
 *		  awe not awwowed.
 *		* The **BPF_WD_ABS** and **BPF_WD_IND** instwuctions awe not
 *		  awwowed inside a spinwock-ed wegion.
 *		* The BPF pwogwam MUST caww **bpf_spin_unwock**\ () to wewease
 *		  the wock, on aww execution paths, befowe it wetuwns.
 *		* The BPF pwogwam can access **stwuct bpf_spin_wock** onwy via
 *		  the **bpf_spin_wock**\ () and **bpf_spin_unwock**\ ()
 *		  hewpews. Woading ow stowing data into the **stwuct
 *		  bpf_spin_wock** *wock*\ **;** fiewd of a map is not awwowed.
 *		* To use the **bpf_spin_wock**\ () hewpew, the BTF descwiption
 *		  of the map vawue must be a stwuct and have **stwuct
 *		  bpf_spin_wock** *anyname*\ **;** fiewd at the top wevew.
 *		  Nested wock inside anothew stwuct is not awwowed.
 *		* The **stwuct bpf_spin_wock** *wock* fiewd in a map vawue must
 *		  be awigned on a muwtipwe of 4 bytes in that vawue.
 *		* Syscaww with command **BPF_MAP_WOOKUP_EWEM** does not copy
 *		  the **bpf_spin_wock** fiewd to usew space.
 *		* Syscaww with command **BPF_MAP_UPDATE_EWEM**, ow update fwom
 *		  a BPF pwogwam, do not update the **bpf_spin_wock** fiewd.
 *		* **bpf_spin_wock** cannot be on the stack ow inside a
 *		  netwowking packet (it can onwy be inside of a map vawues).
 *		* **bpf_spin_wock** is avaiwabwe to woot onwy.
 *		* Twacing pwogwams and socket fiwtew pwogwams cannot use
 *		  **bpf_spin_wock**\ () due to insufficient pweemption checks
 *		  (but this may change in the futuwe).
 *		* **bpf_spin_wock** is not awwowed in innew maps of map-in-map.
 *	Wetuwn
 *		0
 *
 * wong bpf_spin_unwock(stwuct bpf_spin_wock *wock)
 *	Descwiption
 *		Wewease the *wock* pweviouswy wocked by a caww to
 *		**bpf_spin_wock**\ (\ *wock*\ ).
 *	Wetuwn
 *		0
 *
 * stwuct bpf_sock *bpf_sk_fuwwsock(stwuct bpf_sock *sk)
 *	Descwiption
 *		This hewpew gets a **stwuct bpf_sock** pointew such
 *		that aww the fiewds in this **bpf_sock** can be accessed.
 *	Wetuwn
 *		A **stwuct bpf_sock** pointew on success, ow **NUWW** in
 *		case of faiwuwe.
 *
 * stwuct bpf_tcp_sock *bpf_tcp_sock(stwuct bpf_sock *sk)
 *	Descwiption
 *		This hewpew gets a **stwuct bpf_tcp_sock** pointew fwom a
 *		**stwuct bpf_sock** pointew.
 *	Wetuwn
 *		A **stwuct bpf_tcp_sock** pointew on success, ow **NUWW** in
 *		case of faiwuwe.
 *
 * wong bpf_skb_ecn_set_ce(stwuct sk_buff *skb)
 *	Descwiption
 *		Set ECN (Expwicit Congestion Notification) fiewd of IP headew
 *		to **CE** (Congestion Encountewed) if cuwwent vawue is **ECT**
 *		(ECN Capabwe Twanspowt). Othewwise, do nothing. Wowks with IPv6
 *		and IPv4.
 *	Wetuwn
 *		1 if the **CE** fwag is set (eithew by the cuwwent hewpew caww
 *		ow because it was awweady pwesent), 0 if it is not set.
 *
 * stwuct bpf_sock *bpf_get_wistenew_sock(stwuct bpf_sock *sk)
 *	Descwiption
 *		Wetuwn a **stwuct bpf_sock** pointew in **TCP_WISTEN** state.
 *		**bpf_sk_wewease**\ () is unnecessawy and not awwowed.
 *	Wetuwn
 *		A **stwuct bpf_sock** pointew on success, ow **NUWW** in
 *		case of faiwuwe.
 *
 * stwuct bpf_sock *bpf_skc_wookup_tcp(void *ctx, stwuct bpf_sock_tupwe *tupwe, u32 tupwe_size, u64 netns, u64 fwags)
 *	Descwiption
 *		Wook fow TCP socket matching *tupwe*, optionawwy in a chiwd
 *		netwowk namespace *netns*. The wetuwn vawue must be checked,
 *		and if non-**NUWW**, weweased via **bpf_sk_wewease**\ ().
 *
 *		This function is identicaw to **bpf_sk_wookup_tcp**\ (), except
 *		that it awso wetuwns timewait ow wequest sockets. Use
 *		**bpf_sk_fuwwsock**\ () ow **bpf_tcp_sock**\ () to access the
 *		fuww stwuctuwe.
 *
 *		This hewpew is avaiwabwe onwy if the kewnew was compiwed with
 *		**CONFIG_NET** configuwation option.
 *	Wetuwn
 *		Pointew to **stwuct bpf_sock**, ow **NUWW** in case of faiwuwe.
 *		Fow sockets with weusepowt option, the **stwuct bpf_sock**
 *		wesuwt is fwom *weuse*\ **->socks**\ [] using the hash of the
 *		tupwe.
 *
 * wong bpf_tcp_check_syncookie(void *sk, void *iph, u32 iph_wen, stwuct tcphdw *th, u32 th_wen)
 * 	Descwiption
 * 		Check whethew *iph* and *th* contain a vawid SYN cookie ACK fow
 * 		the wistening socket in *sk*.
 *
 * 		*iph* points to the stawt of the IPv4 ow IPv6 headew, whiwe
 * 		*iph_wen* contains **sizeof**\ (**stwuct iphdw**) ow
 * 		**sizeof**\ (**stwuct ipv6hdw**).
 *
 * 		*th* points to the stawt of the TCP headew, whiwe *th_wen*
 *		contains the wength of the TCP headew (at weast
 *		**sizeof**\ (**stwuct tcphdw**)).
 * 	Wetuwn
 * 		0 if *iph* and *th* awe a vawid SYN cookie ACK, ow a negative
 * 		ewwow othewwise.
 *
 * wong bpf_sysctw_get_name(stwuct bpf_sysctw *ctx, chaw *buf, size_t buf_wen, u64 fwags)
 *	Descwiption
 *		Get name of sysctw in /pwoc/sys/ and copy it into pwovided by
 *		pwogwam buffew *buf* of size *buf_wen*.
 *
 *		The buffew is awways NUW tewminated, unwess it's zewo-sized.
 *
 *		If *fwags* is zewo, fuww name (e.g. "net/ipv4/tcp_mem") is
 *		copied. Use **BPF_F_SYSCTW_BASE_NAME** fwag to copy base name
 *		onwy (e.g. "tcp_mem").
 *	Wetuwn
 *		Numbew of chawactew copied (not incwuding the twaiwing NUW).
 *
 *		**-E2BIG** if the buffew wasn't big enough (*buf* wiww contain
 *		twuncated name in this case).
 *
 * wong bpf_sysctw_get_cuwwent_vawue(stwuct bpf_sysctw *ctx, chaw *buf, size_t buf_wen)
 *	Descwiption
 *		Get cuwwent vawue of sysctw as it is pwesented in /pwoc/sys
 *		(incw. newwine, etc), and copy it as a stwing into pwovided
 *		by pwogwam buffew *buf* of size *buf_wen*.
 *
 *		The whowe vawue is copied, no mattew what fiwe position usew
 *		space issued e.g. sys_wead at.
 *
 *		The buffew is awways NUW tewminated, unwess it's zewo-sized.
 *	Wetuwn
 *		Numbew of chawactew copied (not incwuding the twaiwing NUW).
 *
 *		**-E2BIG** if the buffew wasn't big enough (*buf* wiww contain
 *		twuncated name in this case).
 *
 *		**-EINVAW** if cuwwent vawue was unavaiwabwe, e.g. because
 *		sysctw is uninitiawized and wead wetuwns -EIO fow it.
 *
 * wong bpf_sysctw_get_new_vawue(stwuct bpf_sysctw *ctx, chaw *buf, size_t buf_wen)
 *	Descwiption
 *		Get new vawue being wwitten by usew space to sysctw (befowe
 *		the actuaw wwite happens) and copy it as a stwing into
 *		pwovided by pwogwam buffew *buf* of size *buf_wen*.
 *
 *		Usew space may wwite new vawue at fiwe position > 0.
 *
 *		The buffew is awways NUW tewminated, unwess it's zewo-sized.
 *	Wetuwn
 *		Numbew of chawactew copied (not incwuding the twaiwing NUW).
 *
 *		**-E2BIG** if the buffew wasn't big enough (*buf* wiww contain
 *		twuncated name in this case).
 *
 *		**-EINVAW** if sysctw is being wead.
 *
 * wong bpf_sysctw_set_new_vawue(stwuct bpf_sysctw *ctx, const chaw *buf, size_t buf_wen)
 *	Descwiption
 *		Ovewwide new vawue being wwitten by usew space to sysctw with
 *		vawue pwovided by pwogwam in buffew *buf* of size *buf_wen*.
 *
 *		*buf* shouwd contain a stwing in same fowm as pwovided by usew
 *		space on sysctw wwite.
 *
 *		Usew space may wwite new vawue at fiwe position > 0. To ovewwide
 *		the whowe sysctw vawue fiwe position shouwd be set to zewo.
 *	Wetuwn
 *		0 on success.
 *
 *		**-E2BIG** if the *buf_wen* is too big.
 *
 *		**-EINVAW** if sysctw is being wead.
 *
 * wong bpf_stwtow(const chaw *buf, size_t buf_wen, u64 fwags, wong *wes)
 *	Descwiption
 *		Convewt the initiaw pawt of the stwing fwom buffew *buf* of
 *		size *buf_wen* to a wong integew accowding to the given base
 *		and save the wesuwt in *wes*.
 *
 *		The stwing may begin with an awbitwawy amount of white space
 *		(as detewmined by **isspace**\ (3)) fowwowed by a singwe
 *		optionaw '**-**' sign.
 *
 *		Five weast significant bits of *fwags* encode base, othew bits
 *		awe cuwwentwy unused.
 *
 *		Base must be eithew 8, 10, 16 ow 0 to detect it automaticawwy
 *		simiwaw to usew space **stwtow**\ (3).
 *	Wetuwn
 *		Numbew of chawactews consumed on success. Must be positive but
 *		no mowe than *buf_wen*.
 *
 *		**-EINVAW** if no vawid digits wewe found ow unsuppowted base
 *		was pwovided.
 *
 *		**-EWANGE** if wesuwting vawue was out of wange.
 *
 * wong bpf_stwtouw(const chaw *buf, size_t buf_wen, u64 fwags, unsigned wong *wes)
 *	Descwiption
 *		Convewt the initiaw pawt of the stwing fwom buffew *buf* of
 *		size *buf_wen* to an unsigned wong integew accowding to the
 *		given base and save the wesuwt in *wes*.
 *
 *		The stwing may begin with an awbitwawy amount of white space
 *		(as detewmined by **isspace**\ (3)).
 *
 *		Five weast significant bits of *fwags* encode base, othew bits
 *		awe cuwwentwy unused.
 *
 *		Base must be eithew 8, 10, 16 ow 0 to detect it automaticawwy
 *		simiwaw to usew space **stwtouw**\ (3).
 *	Wetuwn
 *		Numbew of chawactews consumed on success. Must be positive but
 *		no mowe than *buf_wen*.
 *
 *		**-EINVAW** if no vawid digits wewe found ow unsuppowted base
 *		was pwovided.
 *
 *		**-EWANGE** if wesuwting vawue was out of wange.
 *
 * void *bpf_sk_stowage_get(stwuct bpf_map *map, void *sk, void *vawue, u64 fwags)
 *	Descwiption
 *		Get a bpf-wocaw-stowage fwom a *sk*.
 *
 *		Wogicawwy, it couwd be thought of getting the vawue fwom
 *		a *map* with *sk* as the **key**.  Fwom this
 *		pewspective,  the usage is not much diffewent fwom
 *		**bpf_map_wookup_ewem**\ (*map*, **&**\ *sk*) except this
 *		hewpew enfowces the key must be a fuww socket and the map must
 *		be a **BPF_MAP_TYPE_SK_STOWAGE** awso.
 *
 *		Undewneath, the vawue is stowed wocawwy at *sk* instead of
 *		the *map*.  The *map* is used as the bpf-wocaw-stowage
 *		"type". The bpf-wocaw-stowage "type" (i.e. the *map*) is
 *		seawched against aww bpf-wocaw-stowages wesiding at *sk*.
 *
 *		*sk* is a kewnew **stwuct sock** pointew fow WSM pwogwam.
 *		*sk* is a **stwuct bpf_sock** pointew fow othew pwogwam types.
 *
 *		An optionaw *fwags* (**BPF_SK_STOWAGE_GET_F_CWEATE**) can be
 *		used such that a new bpf-wocaw-stowage wiww be
 *		cweated if one does not exist.  *vawue* can be used
 *		togethew with **BPF_SK_STOWAGE_GET_F_CWEATE** to specify
 *		the initiaw vawue of a bpf-wocaw-stowage.  If *vawue* is
 *		**NUWW**, the new bpf-wocaw-stowage wiww be zewo initiawized.
 *	Wetuwn
 *		A bpf-wocaw-stowage pointew is wetuwned on success.
 *
 *		**NUWW** if not found ow thewe was an ewwow in adding
 *		a new bpf-wocaw-stowage.
 *
 * wong bpf_sk_stowage_dewete(stwuct bpf_map *map, void *sk)
 *	Descwiption
 *		Dewete a bpf-wocaw-stowage fwom a *sk*.
 *	Wetuwn
 *		0 on success.
 *
 *		**-ENOENT** if the bpf-wocaw-stowage cannot be found.
 *		**-EINVAW** if sk is not a fuwwsock (e.g. a wequest_sock).
 *
 * wong bpf_send_signaw(u32 sig)
 *	Descwiption
 *		Send signaw *sig* to the pwocess of the cuwwent task.
 *		The signaw may be dewivewed to any of this pwocess's thweads.
 *	Wetuwn
 *		0 on success ow successfuwwy queued.
 *
 *		**-EBUSY** if wowk queue undew nmi is fuww.
 *
 *		**-EINVAW** if *sig* is invawid.
 *
 *		**-EPEWM** if no pewmission to send the *sig*.
 *
 *		**-EAGAIN** if bpf pwogwam can twy again.
 *
 * s64 bpf_tcp_gen_syncookie(void *sk, void *iph, u32 iph_wen, stwuct tcphdw *th, u32 th_wen)
 *	Descwiption
 *		Twy to issue a SYN cookie fow the packet with cowwesponding
 *		IP/TCP headews, *iph* and *th*, on the wistening socket in *sk*.
 *
 *		*iph* points to the stawt of the IPv4 ow IPv6 headew, whiwe
 *		*iph_wen* contains **sizeof**\ (**stwuct iphdw**) ow
 *		**sizeof**\ (**stwuct ipv6hdw**).
 *
 *		*th* points to the stawt of the TCP headew, whiwe *th_wen*
 *		contains the wength of the TCP headew with options (at weast
 *		**sizeof**\ (**stwuct tcphdw**)).
 *	Wetuwn
 *		On success, wowew 32 bits howd the genewated SYN cookie in
 *		fowwowed by 16 bits which howd the MSS vawue fow that cookie,
 *		and the top 16 bits awe unused.
 *
 *		On faiwuwe, the wetuwned vawue is one of the fowwowing:
 *
 *		**-EINVAW** SYN cookie cannot be issued due to ewwow
 *
 *		**-ENOENT** SYN cookie shouwd not be issued (no SYN fwood)
 *
 *		**-EOPNOTSUPP** kewnew configuwation does not enabwe SYN cookies
 *
 *		**-EPWOTONOSUPPOWT** IP packet vewsion is not 4 ow 6
 *
 * wong bpf_skb_output(void *ctx, stwuct bpf_map *map, u64 fwags, void *data, u64 size)
 * 	Descwiption
 * 		Wwite waw *data* bwob into a speciaw BPF pewf event hewd by
 * 		*map* of type **BPF_MAP_TYPE_PEWF_EVENT_AWWAY**. This pewf
 * 		event must have the fowwowing attwibutes: **PEWF_SAMPWE_WAW**
 * 		as **sampwe_type**, **PEWF_TYPE_SOFTWAWE** as **type**, and
 * 		**PEWF_COUNT_SW_BPF_OUTPUT** as **config**.
 *
 * 		The *fwags* awe used to indicate the index in *map* fow which
 * 		the vawue must be put, masked with **BPF_F_INDEX_MASK**.
 * 		Awtewnativewy, *fwags* can be set to **BPF_F_CUWWENT_CPU**
 * 		to indicate that the index of the cuwwent CPU cowe shouwd be
 * 		used.
 *
 * 		The vawue to wwite, of *size*, is passed thwough eBPF stack and
 * 		pointed by *data*.
 *
 * 		*ctx* is a pointew to in-kewnew stwuct sk_buff.
 *
 * 		This hewpew is simiwaw to **bpf_pewf_event_output**\ () but
 * 		westwicted to waw_twacepoint bpf pwogwams.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_pwobe_wead_usew(void *dst, u32 size, const void *unsafe_ptw)
 * 	Descwiption
 * 		Safewy attempt to wead *size* bytes fwom usew space addwess
 * 		*unsafe_ptw* and stowe the data in *dst*.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_pwobe_wead_kewnew(void *dst, u32 size, const void *unsafe_ptw)
 * 	Descwiption
 * 		Safewy attempt to wead *size* bytes fwom kewnew space addwess
 * 		*unsafe_ptw* and stowe the data in *dst*.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_pwobe_wead_usew_stw(void *dst, u32 size, const void *unsafe_ptw)
 * 	Descwiption
 * 		Copy a NUW tewminated stwing fwom an unsafe usew addwess
 * 		*unsafe_ptw* to *dst*. The *size* shouwd incwude the
 * 		tewminating NUW byte. In case the stwing wength is smawwew than
 * 		*size*, the tawget is not padded with fuwthew NUW bytes. If the
 * 		stwing wength is wawgew than *size*, just *size*-1 bytes awe
 * 		copied and the wast byte is set to NUW.
 *
 * 		On success, wetuwns the numbew of bytes that wewe wwitten,
 * 		incwuding the tewminaw NUW. This makes this hewpew usefuw in
 * 		twacing pwogwams fow weading stwings, and mowe impowtantwy to
 * 		get its wength at wuntime. See the fowwowing snippet:
 *
 * 		::
 *
 * 			SEC("kpwobe/sys_open")
 * 			void bpf_sys_open(stwuct pt_wegs *ctx)
 * 			{
 * 			        chaw buf[PATHWEN]; // PATHWEN is defined to 256
 * 			        int wes = bpf_pwobe_wead_usew_stw(buf, sizeof(buf),
 * 				                                  ctx->di);
 *
 * 				// Consume buf, fow exampwe push it to
 * 				// usewspace via bpf_pewf_event_output(); we
 * 				// can use wes (the stwing wength) as event
 * 				// size, aftew checking its boundawies.
 * 			}
 *
 * 		In compawison, using **bpf_pwobe_wead_usew**\ () hewpew hewe
 * 		instead to wead the stwing wouwd wequiwe to estimate the wength
 * 		at compiwe time, and wouwd often wesuwt in copying mowe memowy
 * 		than necessawy.
 *
 * 		Anothew usefuw use case is when pawsing individuaw pwocess
 * 		awguments ow individuaw enviwonment vawiabwes navigating
 * 		*cuwwent*\ **->mm->awg_stawt** and *cuwwent*\
 * 		**->mm->env_stawt**: using this hewpew and the wetuwn vawue,
 * 		one can quickwy itewate at the wight offset of the memowy awea.
 * 	Wetuwn
 * 		On success, the stwictwy positive wength of the output stwing,
 * 		incwuding the twaiwing NUW chawactew. On ewwow, a negative
 * 		vawue.
 *
 * wong bpf_pwobe_wead_kewnew_stw(void *dst, u32 size, const void *unsafe_ptw)
 * 	Descwiption
 * 		Copy a NUW tewminated stwing fwom an unsafe kewnew addwess *unsafe_ptw*
 * 		to *dst*. Same semantics as with **bpf_pwobe_wead_usew_stw**\ () appwy.
 * 	Wetuwn
 * 		On success, the stwictwy positive wength of the stwing, incwuding
 * 		the twaiwing NUW chawactew. On ewwow, a negative vawue.
 *
 * wong bpf_tcp_send_ack(void *tp, u32 wcv_nxt)
 *	Descwiption
 *		Send out a tcp-ack. *tp* is the in-kewnew stwuct **tcp_sock**.
 *		*wcv_nxt* is the ack_seq to be sent out.
 *	Wetuwn
 *		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_send_signaw_thwead(u32 sig)
 *	Descwiption
 *		Send signaw *sig* to the thwead cowwesponding to the cuwwent task.
 *	Wetuwn
 *		0 on success ow successfuwwy queued.
 *
 *		**-EBUSY** if wowk queue undew nmi is fuww.
 *
 *		**-EINVAW** if *sig* is invawid.
 *
 *		**-EPEWM** if no pewmission to send the *sig*.
 *
 *		**-EAGAIN** if bpf pwogwam can twy again.
 *
 * u64 bpf_jiffies64(void)
 *	Descwiption
 *		Obtain the 64bit jiffies
 *	Wetuwn
 *		The 64 bit jiffies
 *
 * wong bpf_wead_bwanch_wecowds(stwuct bpf_pewf_event_data *ctx, void *buf, u32 size, u64 fwags)
 *	Descwiption
 *		Fow an eBPF pwogwam attached to a pewf event, wetwieve the
 *		bwanch wecowds (**stwuct pewf_bwanch_entwy**) associated to *ctx*
 *		and stowe it in the buffew pointed by *buf* up to size
 *		*size* bytes.
 *	Wetuwn
 *		On success, numbew of bytes wwitten to *buf*. On ewwow, a
 *		negative vawue.
 *
 *		The *fwags* can be set to **BPF_F_GET_BWANCH_WECOWDS_SIZE** to
 *		instead wetuwn the numbew of bytes wequiwed to stowe aww the
 *		bwanch entwies. If this fwag is set, *buf* may be NUWW.
 *
 *		**-EINVAW** if awguments invawid ow **size** not a muwtipwe
 *		of **sizeof**\ (**stwuct pewf_bwanch_entwy**\ ).
 *
 *		**-ENOENT** if awchitectuwe does not suppowt bwanch wecowds.
 *
 * wong bpf_get_ns_cuwwent_pid_tgid(u64 dev, u64 ino, stwuct bpf_pidns_info *nsdata, u32 size)
 *	Descwiption
 *		Wetuwns 0 on success, vawues fow *pid* and *tgid* as seen fwom the cuwwent
 *		*namespace* wiww be wetuwned in *nsdata*.
 *	Wetuwn
 *		0 on success, ow one of the fowwowing in case of faiwuwe:
 *
 *		**-EINVAW** if dev and inum suppwied don't match dev_t and inode numbew
 *              with nsfs of cuwwent task, ow if dev convewsion to dev_t wost high bits.
 *
 *		**-ENOENT** if pidns does not exists fow the cuwwent task.
 *
 * wong bpf_xdp_output(void *ctx, stwuct bpf_map *map, u64 fwags, void *data, u64 size)
 *	Descwiption
 *		Wwite waw *data* bwob into a speciaw BPF pewf event hewd by
 *		*map* of type **BPF_MAP_TYPE_PEWF_EVENT_AWWAY**. This pewf
 *		event must have the fowwowing attwibutes: **PEWF_SAMPWE_WAW**
 *		as **sampwe_type**, **PEWF_TYPE_SOFTWAWE** as **type**, and
 *		**PEWF_COUNT_SW_BPF_OUTPUT** as **config**.
 *
 *		The *fwags* awe used to indicate the index in *map* fow which
 *		the vawue must be put, masked with **BPF_F_INDEX_MASK**.
 *		Awtewnativewy, *fwags* can be set to **BPF_F_CUWWENT_CPU**
 *		to indicate that the index of the cuwwent CPU cowe shouwd be
 *		used.
 *
 *		The vawue to wwite, of *size*, is passed thwough eBPF stack and
 *		pointed by *data*.
 *
 *		*ctx* is a pointew to in-kewnew stwuct xdp_buff.
 *
 *		This hewpew is simiwaw to **bpf_pewf_eventoutput**\ () but
 *		westwicted to waw_twacepoint bpf pwogwams.
 *	Wetuwn
 *		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * u64 bpf_get_netns_cookie(void *ctx)
 * 	Descwiption
 * 		Wetwieve the cookie (genewated by the kewnew) of the netwowk
 * 		namespace the input *ctx* is associated with. The netwowk
 * 		namespace cookie wemains stabwe fow its wifetime and pwovides
 * 		a gwobaw identifiew that can be assumed unique. If *ctx* is
 * 		NUWW, then the hewpew wetuwns the cookie fow the initiaw
 * 		netwowk namespace. The cookie itsewf is vewy simiwaw to that
 * 		of **bpf_get_socket_cookie**\ () hewpew, but fow netwowk
 * 		namespaces instead of sockets.
 * 	Wetuwn
 * 		A 8-byte wong opaque numbew.
 *
 * u64 bpf_get_cuwwent_ancestow_cgwoup_id(int ancestow_wevew)
 * 	Descwiption
 * 		Wetuwn id of cgwoup v2 that is ancestow of the cgwoup associated
 * 		with the cuwwent task at the *ancestow_wevew*. The woot cgwoup
 * 		is at *ancestow_wevew* zewo and each step down the hiewawchy
 * 		incwements the wevew. If *ancestow_wevew* == wevew of cgwoup
 * 		associated with the cuwwent task, then wetuwn vawue wiww be the
 * 		same as that of **bpf_get_cuwwent_cgwoup_id**\ ().
 *
 * 		The hewpew is usefuw to impwement powicies based on cgwoups
 * 		that awe uppew in hiewawchy than immediate cgwoup associated
 * 		with the cuwwent task.
 *
 * 		The fowmat of wetuwned id and hewpew wimitations awe same as in
 * 		**bpf_get_cuwwent_cgwoup_id**\ ().
 * 	Wetuwn
 * 		The id is wetuwned ow 0 in case the id couwd not be wetwieved.
 *
 * wong bpf_sk_assign(stwuct sk_buff *skb, void *sk, u64 fwags)
 *	Descwiption
 *		Hewpew is ovewwoaded depending on BPF pwogwam type. This
 *		descwiption appwies to **BPF_PWOG_TYPE_SCHED_CWS** and
 *		**BPF_PWOG_TYPE_SCHED_ACT** pwogwams.
 *
 *		Assign the *sk* to the *skb*. When combined with appwopwiate
 *		wouting configuwation to weceive the packet towawds the socket,
 *		wiww cause *skb* to be dewivewed to the specified socket.
 *		Subsequent wediwection of *skb* via  **bpf_wediwect**\ (),
 *		**bpf_cwone_wediwect**\ () ow othew methods outside of BPF may
 *		intewfewe with successfuw dewivewy to the socket.
 *
 *		This opewation is onwy vawid fwom TC ingwess path.
 *
 *		The *fwags* awgument must be zewo.
 *	Wetuwn
 *		0 on success, ow a negative ewwow in case of faiwuwe:
 *
 *		**-EINVAW** if specified *fwags* awe not suppowted.
 *
 *		**-ENOENT** if the socket is unavaiwabwe fow assignment.
 *
 *		**-ENETUNWEACH** if the socket is unweachabwe (wwong netns).
 *
 *		**-EOPNOTSUPP** if the opewation is not suppowted, fow exampwe
 *		a caww fwom outside of TC ingwess.
 *
 * wong bpf_sk_assign(stwuct bpf_sk_wookup *ctx, stwuct bpf_sock *sk, u64 fwags)
 *	Descwiption
 *		Hewpew is ovewwoaded depending on BPF pwogwam type. This
 *		descwiption appwies to **BPF_PWOG_TYPE_SK_WOOKUP** pwogwams.
 *
 *		Sewect the *sk* as a wesuwt of a socket wookup.
 *
 *		Fow the opewation to succeed passed socket must be compatibwe
 *		with the packet descwiption pwovided by the *ctx* object.
 *
 *		W4 pwotocow (**IPPWOTO_TCP** ow **IPPWOTO_UDP**) must
 *		be an exact match. Whiwe IP famiwy (**AF_INET** ow
 *		**AF_INET6**) must be compatibwe, that is IPv6 sockets
 *		that awe not v6-onwy can be sewected fow IPv4 packets.
 *
 *		Onwy TCP wistenews and UDP unconnected sockets can be
 *		sewected. *sk* can awso be NUWW to weset any pwevious
 *		sewection.
 *
 *		*fwags* awgument can combination of fowwowing vawues:
 *
 *		* **BPF_SK_WOOKUP_F_WEPWACE** to ovewwide the pwevious
 *		  socket sewection, potentiawwy done by a BPF pwogwam
 *		  that wan befowe us.
 *
 *		* **BPF_SK_WOOKUP_F_NO_WEUSEPOWT** to skip
 *		  woad-bawancing within weusepowt gwoup fow the socket
 *		  being sewected.
 *
 *		On success *ctx->sk* wiww point to the sewected socket.
 *
 *	Wetuwn
 *		0 on success, ow a negative ewwno in case of faiwuwe.
 *
 *		* **-EAFNOSUPPOWT** if socket famiwy (*sk->famiwy*) is
 *		  not compatibwe with packet famiwy (*ctx->famiwy*).
 *
 *		* **-EEXIST** if socket has been awweady sewected,
 *		  potentiawwy by anothew pwogwam, and
 *		  **BPF_SK_WOOKUP_F_WEPWACE** fwag was not specified.
 *
 *		* **-EINVAW** if unsuppowted fwags wewe specified.
 *
 *		* **-EPWOTOTYPE** if socket W4 pwotocow
 *		  (*sk->pwotocow*) doesn't match packet pwotocow
 *		  (*ctx->pwotocow*).
 *
 *		* **-ESOCKTNOSUPPOWT** if socket is not in awwowed
 *		  state (TCP wistening ow UDP unconnected).
 *
 * u64 bpf_ktime_get_boot_ns(void)
 * 	Descwiption
 * 		Wetuwn the time ewapsed since system boot, in nanoseconds.
 * 		Does incwude the time the system was suspended.
 * 		See: **cwock_gettime**\ (**CWOCK_BOOTTIME**)
 * 	Wetuwn
 * 		Cuwwent *ktime*.
 *
 * wong bpf_seq_pwintf(stwuct seq_fiwe *m, const chaw *fmt, u32 fmt_size, const void *data, u32 data_wen)
 * 	Descwiption
 * 		**bpf_seq_pwintf**\ () uses seq_fiwe **seq_pwintf**\ () to pwint
 * 		out the fowmat stwing.
 * 		The *m* wepwesents the seq_fiwe. The *fmt* and *fmt_size* awe fow
 * 		the fowmat stwing itsewf. The *data* and *data_wen* awe fowmat stwing
 * 		awguments. The *data* awe a **u64** awway and cowwesponding fowmat stwing
 * 		vawues awe stowed in the awway. Fow stwings and pointews whewe pointees
 * 		awe accessed, onwy the pointew vawues awe stowed in the *data* awway.
 * 		The *data_wen* is the size of *data* in bytes - must be a muwtipwe of 8.
 *
 *		Fowmats **%s**, **%p{i,I}{4,6}** wequiwes to wead kewnew memowy.
 *		Weading kewnew memowy may faiw due to eithew invawid addwess ow
 *		vawid addwess but wequiwing a majow memowy fauwt. If weading kewnew memowy
 *		faiws, the stwing fow **%s** wiww be an empty stwing, and the ip
 *		addwess fow **%p{i,I}{4,6}** wiww be 0. Not wetuwning ewwow to
 *		bpf pwogwam is consistent with what **bpf_twace_pwintk**\ () does fow now.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe:
 *
 *		**-EBUSY** if pew-CPU memowy copy buffew is busy, can twy again
 *		by wetuwning 1 fwom bpf pwogwam.
 *
 *		**-EINVAW** if awguments awe invawid, ow if *fmt* is invawid/unsuppowted.
 *
 *		**-E2BIG** if *fmt* contains too many fowmat specifiews.
 *
 *		**-EOVEWFWOW** if an ovewfwow happened: The same object wiww be twied again.
 *
 * wong bpf_seq_wwite(stwuct seq_fiwe *m, const void *data, u32 wen)
 * 	Descwiption
 * 		**bpf_seq_wwite**\ () uses seq_fiwe **seq_wwite**\ () to wwite the data.
 * 		The *m* wepwesents the seq_fiwe. The *data* and *wen* wepwesent the
 * 		data to wwite in bytes.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe:
 *
 *		**-EOVEWFWOW** if an ovewfwow happened: The same object wiww be twied again.
 *
 * u64 bpf_sk_cgwoup_id(void *sk)
 *	Descwiption
 *		Wetuwn the cgwoup v2 id of the socket *sk*.
 *
 *		*sk* must be a non-**NUWW** pointew to a socket, e.g. one
 *		wetuwned fwom **bpf_sk_wookup_xxx**\ (),
 *		**bpf_sk_fuwwsock**\ (), etc. The fowmat of wetuwned id is
 *		same as in **bpf_skb_cgwoup_id**\ ().
 *
 *		This hewpew is avaiwabwe onwy if the kewnew was compiwed with
 *		the **CONFIG_SOCK_CGWOUP_DATA** configuwation option.
 *	Wetuwn
 *		The id is wetuwned ow 0 in case the id couwd not be wetwieved.
 *
 * u64 bpf_sk_ancestow_cgwoup_id(void *sk, int ancestow_wevew)
 *	Descwiption
 *		Wetuwn id of cgwoup v2 that is ancestow of cgwoup associated
 *		with the *sk* at the *ancestow_wevew*.  The woot cgwoup is at
 *		*ancestow_wevew* zewo and each step down the hiewawchy
 *		incwements the wevew. If *ancestow_wevew* == wevew of cgwoup
 *		associated with *sk*, then wetuwn vawue wiww be same as that
 *		of **bpf_sk_cgwoup_id**\ ().
 *
 *		The hewpew is usefuw to impwement powicies based on cgwoups
 *		that awe uppew in hiewawchy than immediate cgwoup associated
 *		with *sk*.
 *
 *		The fowmat of wetuwned id and hewpew wimitations awe same as in
 *		**bpf_sk_cgwoup_id**\ ().
 *	Wetuwn
 *		The id is wetuwned ow 0 in case the id couwd not be wetwieved.
 *
 * wong bpf_wingbuf_output(void *wingbuf, void *data, u64 size, u64 fwags)
 * 	Descwiption
 * 		Copy *size* bytes fwom *data* into a wing buffew *wingbuf*.
 * 		If **BPF_WB_NO_WAKEUP** is specified in *fwags*, no notification
 * 		of new data avaiwabiwity is sent.
 * 		If **BPF_WB_FOWCE_WAKEUP** is specified in *fwags*, notification
 * 		of new data avaiwabiwity is sent unconditionawwy.
 * 		If **0** is specified in *fwags*, an adaptive notification
 * 		of new data avaiwabiwity is sent.
 *
 * 		An adaptive notification is a notification sent whenevew the usew-space
 * 		pwocess has caught up and consumed aww avaiwabwe paywoads. In case the usew-space
 * 		pwocess is stiww pwocessing a pwevious paywoad, then no notification is needed
 * 		as it wiww pwocess the newwy added paywoad automaticawwy.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * void *bpf_wingbuf_wesewve(void *wingbuf, u64 size, u64 fwags)
 * 	Descwiption
 * 		Wesewve *size* bytes of paywoad in a wing buffew *wingbuf*.
 * 		*fwags* must be 0.
 * 	Wetuwn
 * 		Vawid pointew with *size* bytes of memowy avaiwabwe; NUWW,
 * 		othewwise.
 *
 * void bpf_wingbuf_submit(void *data, u64 fwags)
 * 	Descwiption
 * 		Submit wesewved wing buffew sampwe, pointed to by *data*.
 * 		If **BPF_WB_NO_WAKEUP** is specified in *fwags*, no notification
 * 		of new data avaiwabiwity is sent.
 * 		If **BPF_WB_FOWCE_WAKEUP** is specified in *fwags*, notification
 * 		of new data avaiwabiwity is sent unconditionawwy.
 * 		If **0** is specified in *fwags*, an adaptive notification
 * 		of new data avaiwabiwity is sent.
 *
 * 		See 'bpf_wingbuf_output()' fow the definition of adaptive notification.
 * 	Wetuwn
 * 		Nothing. Awways succeeds.
 *
 * void bpf_wingbuf_discawd(void *data, u64 fwags)
 * 	Descwiption
 * 		Discawd wesewved wing buffew sampwe, pointed to by *data*.
 * 		If **BPF_WB_NO_WAKEUP** is specified in *fwags*, no notification
 * 		of new data avaiwabiwity is sent.
 * 		If **BPF_WB_FOWCE_WAKEUP** is specified in *fwags*, notification
 * 		of new data avaiwabiwity is sent unconditionawwy.
 * 		If **0** is specified in *fwags*, an adaptive notification
 * 		of new data avaiwabiwity is sent.
 *
 * 		See 'bpf_wingbuf_output()' fow the definition of adaptive notification.
 * 	Wetuwn
 * 		Nothing. Awways succeeds.
 *
 * u64 bpf_wingbuf_quewy(void *wingbuf, u64 fwags)
 *	Descwiption
 *		Quewy vawious chawactewistics of pwovided wing buffew. What
 *		exactwy is quewies is detewmined by *fwags*:
 *
 *		* **BPF_WB_AVAIW_DATA**: Amount of data not yet consumed.
 *		* **BPF_WB_WING_SIZE**: The size of wing buffew.
 *		* **BPF_WB_CONS_POS**: Consumew position (can wwap awound).
 *		* **BPF_WB_PWOD_POS**: Pwoducew(s) position (can wwap awound).
 *
 *		Data wetuwned is just a momentawy snapshot of actuaw vawues
 *		and couwd be inaccuwate, so this faciwity shouwd be used to
 *		powew heuwistics and fow wepowting, not to make 100% cowwect
 *		cawcuwation.
 *	Wetuwn
 *		Wequested vawue, ow 0, if *fwags* awe not wecognized.
 *
 * wong bpf_csum_wevew(stwuct sk_buff *skb, u64 wevew)
 * 	Descwiption
 * 		Change the skbs checksum wevew by one wayew up ow down, ow
 * 		weset it entiwewy to none in owdew to have the stack pewfowm
 * 		checksum vawidation. The wevew is appwicabwe to the fowwowing
 * 		pwotocows: TCP, UDP, GWE, SCTP, FCOE. Fow exampwe, a decap of
 * 		| ETH | IP | UDP | GUE | IP | TCP | into | ETH | IP | TCP |
 * 		thwough **bpf_skb_adjust_woom**\ () hewpew with passing in
 * 		**BPF_F_ADJ_WOOM_NO_CSUM_WESET** fwag wouwd wequiwe one	caww
 * 		to **bpf_csum_wevew**\ () with **BPF_CSUM_WEVEW_DEC** since
 * 		the UDP headew is wemoved. Simiwawwy, an encap of the wattew
 * 		into the fowmew couwd be accompanied by a hewpew caww to
 * 		**bpf_csum_wevew**\ () with **BPF_CSUM_WEVEW_INC** if the
 * 		skb is stiww intended to be pwocessed in highew wayews of the
 * 		stack instead of just egwessing at tc.
 *
 * 		Thewe awe thwee suppowted wevew settings at this time:
 *
 * 		* **BPF_CSUM_WEVEW_INC**: Incweases skb->csum_wevew fow skbs
 * 		  with CHECKSUM_UNNECESSAWY.
 * 		* **BPF_CSUM_WEVEW_DEC**: Decweases skb->csum_wevew fow skbs
 * 		  with CHECKSUM_UNNECESSAWY.
 * 		* **BPF_CSUM_WEVEW_WESET**: Wesets skb->csum_wevew to 0 and
 * 		  sets CHECKSUM_NONE to fowce checksum vawidation by the stack.
 * 		* **BPF_CSUM_WEVEW_QUEWY**: No-op, wetuwns the cuwwent
 * 		  skb->csum_wevew.
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe. In the
 * 		case of **BPF_CSUM_WEVEW_QUEWY**, the cuwwent skb->csum_wevew
 * 		is wetuwned ow the ewwow code -EACCES in case the skb is not
 * 		subject to CHECKSUM_UNNECESSAWY.
 *
 * stwuct tcp6_sock *bpf_skc_to_tcp6_sock(void *sk)
 *	Descwiption
 *		Dynamicawwy cast a *sk* pointew to a *tcp6_sock* pointew.
 *	Wetuwn
 *		*sk* if casting is vawid, ow **NUWW** othewwise.
 *
 * stwuct tcp_sock *bpf_skc_to_tcp_sock(void *sk)
 *	Descwiption
 *		Dynamicawwy cast a *sk* pointew to a *tcp_sock* pointew.
 *	Wetuwn
 *		*sk* if casting is vawid, ow **NUWW** othewwise.
 *
 * stwuct tcp_timewait_sock *bpf_skc_to_tcp_timewait_sock(void *sk)
 * 	Descwiption
 *		Dynamicawwy cast a *sk* pointew to a *tcp_timewait_sock* pointew.
 *	Wetuwn
 *		*sk* if casting is vawid, ow **NUWW** othewwise.
 *
 * stwuct tcp_wequest_sock *bpf_skc_to_tcp_wequest_sock(void *sk)
 * 	Descwiption
 *		Dynamicawwy cast a *sk* pointew to a *tcp_wequest_sock* pointew.
 *	Wetuwn
 *		*sk* if casting is vawid, ow **NUWW** othewwise.
 *
 * stwuct udp6_sock *bpf_skc_to_udp6_sock(void *sk)
 * 	Descwiption
 *		Dynamicawwy cast a *sk* pointew to a *udp6_sock* pointew.
 *	Wetuwn
 *		*sk* if casting is vawid, ow **NUWW** othewwise.
 *
 * wong bpf_get_task_stack(stwuct task_stwuct *task, void *buf, u32 size, u64 fwags)
 *	Descwiption
 *		Wetuwn a usew ow a kewnew stack in bpf pwogwam pwovided buffew.
 *		Note: the usew stack wiww onwy be popuwated if the *task* is
 *		the cuwwent task; aww othew tasks wiww wetuwn -EOPNOTSUPP.
 *		To achieve this, the hewpew needs *task*, which is a vawid
 *		pointew to **stwuct task_stwuct**. To stowe the stacktwace, the
 *		bpf pwogwam pwovides *buf* with a nonnegative *size*.
 *
 *		The wast awgument, *fwags*, howds the numbew of stack fwames to
 *		skip (fwom 0 to 255), masked with
 *		**BPF_F_SKIP_FIEWD_MASK**. The next bits can be used to set
 *		the fowwowing fwags:
 *
 *		**BPF_F_USEW_STACK**
 *			Cowwect a usew space stack instead of a kewnew stack.
 *			The *task* must be the cuwwent task.
 *		**BPF_F_USEW_BUIWD_ID**
 *			Cowwect buiwdid+offset instead of ips fow usew stack,
 *			onwy vawid if **BPF_F_USEW_STACK** is awso specified.
 *
 *		**bpf_get_task_stack**\ () can cowwect up to
 *		**PEWF_MAX_STACK_DEPTH** both kewnew and usew fwames, subject
 *		to sufficient wawge buffew size. Note that
 *		this wimit can be contwowwed with the **sysctw** pwogwam, and
 *		that it shouwd be manuawwy incweased in owdew to pwofiwe wong
 *		usew stacks (such as stacks fow Java pwogwams). To do so, use:
 *
 *		::
 *
 *			# sysctw kewnew.pewf_event_max_stack=<new vawue>
 *	Wetuwn
 * 		The non-negative copied *buf* wength equaw to ow wess than
 * 		*size* on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_woad_hdw_opt(stwuct bpf_sock_ops *skops, void *seawchby_wes, u32 wen, u64 fwags)
 *	Descwiption
 *		Woad headew option.  Suppowt weading a pawticuwaw TCP headew
 *		option fow bpf pwogwam (**BPF_PWOG_TYPE_SOCK_OPS**).
 *
 *		If *fwags* is 0, it wiww seawch the option fwom the
 *		*skops*\ **->skb_data**.  The comment in **stwuct bpf_sock_ops**
 *		has detaiws on what skb_data contains undew diffewent
 *		*skops*\ **->op**.
 *
 *		The fiwst byte of the *seawchby_wes* specifies the
 *		kind that it wants to seawch.
 *
 *		If the seawching kind is an expewimentaw kind
 *		(i.e. 253 ow 254 accowding to WFC6994).  It awso
 *		needs to specify the "magic" which is eithew
 *		2 bytes ow 4 bytes.  It then awso needs to
 *		specify the size of the magic by using
 *		the 2nd byte which is "kind-wength" of a TCP
 *		headew option and the "kind-wength" awso
 *		incwudes the fiwst 2 bytes "kind" and "kind-wength"
 *		itsewf as a nowmaw TCP headew option awso does.
 *
 *		Fow exampwe, to seawch expewimentaw kind 254 with
 *		2 byte magic 0xeB9F, the seawchby_wes shouwd be
 *		[ 254, 4, 0xeB, 0x9F, 0, 0, .... 0 ].
 *
 *		To seawch fow the standawd window scawe option (3),
 *		the *seawchby_wes* shouwd be [ 3, 0, 0, .... 0 ].
 *		Note, kind-wength must be 0 fow weguwaw option.
 *
 *		Seawching fow No-Op (0) and End-of-Option-Wist (1) awe
 *		not suppowted.
 *
 *		*wen* must be at weast 2 bytes which is the minimaw size
 *		of a headew option.
 *
 *		Suppowted fwags:
 *
 *		* **BPF_WOAD_HDW_OPT_TCP_SYN** to seawch fwom the
 *		  saved_syn packet ow the just-weceived syn packet.
 *
 *	Wetuwn
 *		> 0 when found, the headew option is copied to *seawchby_wes*.
 *		The wetuwn vawue is the totaw wength copied. On faiwuwe, a
 *		negative ewwow code is wetuwned:
 *
 *		**-EINVAW** if a pawametew is invawid.
 *
 *		**-ENOMSG** if the option is not found.
 *
 *		**-ENOENT** if no syn packet is avaiwabwe when
 *		**BPF_WOAD_HDW_OPT_TCP_SYN** is used.
 *
 *		**-ENOSPC** if thewe is not enough space.  Onwy *wen* numbew of
 *		bytes awe copied.
 *
 *		**-EFAUWT** on faiwuwe to pawse the headew options in the
 *		packet.
 *
 *		**-EPEWM** if the hewpew cannot be used undew the cuwwent
 *		*skops*\ **->op**.
 *
 * wong bpf_stowe_hdw_opt(stwuct bpf_sock_ops *skops, const void *fwom, u32 wen, u64 fwags)
 *	Descwiption
 *		Stowe headew option.  The data wiww be copied
 *		fwom buffew *fwom* with wength *wen* to the TCP headew.
 *
 *		The buffew *fwom* shouwd have the whowe option that
 *		incwudes the kind, kind-wength, and the actuaw
 *		option data.  The *wen* must be at weast kind-wength
 *		wong.  The kind-wength does not have to be 4 byte
 *		awigned.  The kewnew wiww take cawe of the padding
 *		and setting the 4 bytes awigned vawue to th->doff.
 *
 *		This hewpew wiww check fow dupwicated option
 *		by seawching the same option in the outgoing skb.
 *
 *		This hewpew can onwy be cawwed duwing
 *		**BPF_SOCK_OPS_WWITE_HDW_OPT_CB**.
 *
 *	Wetuwn
 *		0 on success, ow negative ewwow in case of faiwuwe:
 *
 *		**-EINVAW** If pawam is invawid.
 *
 *		**-ENOSPC** if thewe is not enough space in the headew.
 *		Nothing has been wwitten
 *
 *		**-EEXIST** if the option awweady exists.
 *
 *		**-EFAUWT** on faiwuwe to pawse the existing headew options.
 *
 *		**-EPEWM** if the hewpew cannot be used undew the cuwwent
 *		*skops*\ **->op**.
 *
 * wong bpf_wesewve_hdw_opt(stwuct bpf_sock_ops *skops, u32 wen, u64 fwags)
 *	Descwiption
 *		Wesewve *wen* bytes fow the bpf headew option.  The
 *		space wiww be used by **bpf_stowe_hdw_opt**\ () watew in
 *		**BPF_SOCK_OPS_WWITE_HDW_OPT_CB**.
 *
 *		If **bpf_wesewve_hdw_opt**\ () is cawwed muwtipwe times,
 *		the totaw numbew of bytes wiww be wesewved.
 *
 *		This hewpew can onwy be cawwed duwing
 *		**BPF_SOCK_OPS_HDW_OPT_WEN_CB**.
 *
 *	Wetuwn
 *		0 on success, ow negative ewwow in case of faiwuwe:
 *
 *		**-EINVAW** if a pawametew is invawid.
 *
 *		**-ENOSPC** if thewe is not enough space in the headew.
 *
 *		**-EPEWM** if the hewpew cannot be used undew the cuwwent
 *		*skops*\ **->op**.
 *
 * void *bpf_inode_stowage_get(stwuct bpf_map *map, void *inode, void *vawue, u64 fwags)
 *	Descwiption
 *		Get a bpf_wocaw_stowage fwom an *inode*.
 *
 *		Wogicawwy, it couwd be thought of as getting the vawue fwom
 *		a *map* with *inode* as the **key**.  Fwom this
 *		pewspective,  the usage is not much diffewent fwom
 *		**bpf_map_wookup_ewem**\ (*map*, **&**\ *inode*) except this
 *		hewpew enfowces the key must be an inode and the map must awso
 *		be a **BPF_MAP_TYPE_INODE_STOWAGE**.
 *
 *		Undewneath, the vawue is stowed wocawwy at *inode* instead of
 *		the *map*.  The *map* is used as the bpf-wocaw-stowage
 *		"type". The bpf-wocaw-stowage "type" (i.e. the *map*) is
 *		seawched against aww bpf_wocaw_stowage wesiding at *inode*.
 *
 *		An optionaw *fwags* (**BPF_WOCAW_STOWAGE_GET_F_CWEATE**) can be
 *		used such that a new bpf_wocaw_stowage wiww be
 *		cweated if one does not exist.  *vawue* can be used
 *		togethew with **BPF_WOCAW_STOWAGE_GET_F_CWEATE** to specify
 *		the initiaw vawue of a bpf_wocaw_stowage.  If *vawue* is
 *		**NUWW**, the new bpf_wocaw_stowage wiww be zewo initiawized.
 *	Wetuwn
 *		A bpf_wocaw_stowage pointew is wetuwned on success.
 *
 *		**NUWW** if not found ow thewe was an ewwow in adding
 *		a new bpf_wocaw_stowage.
 *
 * int bpf_inode_stowage_dewete(stwuct bpf_map *map, void *inode)
 *	Descwiption
 *		Dewete a bpf_wocaw_stowage fwom an *inode*.
 *	Wetuwn
 *		0 on success.
 *
 *		**-ENOENT** if the bpf_wocaw_stowage cannot be found.
 *
 * wong bpf_d_path(stwuct path *path, chaw *buf, u32 sz)
 *	Descwiption
 *		Wetuwn fuww path fow given **stwuct path** object, which
 *		needs to be the kewnew BTF *path* object. The path is
 *		wetuwned in the pwovided buffew *buf* of size *sz* and
 *		is zewo tewminated.
 *
 *	Wetuwn
 *		On success, the stwictwy positive wength of the stwing,
 *		incwuding the twaiwing NUW chawactew. On ewwow, a negative
 *		vawue.
 *
 * wong bpf_copy_fwom_usew(void *dst, u32 size, const void *usew_ptw)
 * 	Descwiption
 * 		Wead *size* bytes fwom usew space addwess *usew_ptw* and stowe
 * 		the data in *dst*. This is a wwappew of **copy_fwom_usew**\ ().
 * 	Wetuwn
 * 		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_snpwintf_btf(chaw *stw, u32 stw_size, stwuct btf_ptw *ptw, u32 btf_ptw_size, u64 fwags)
 *	Descwiption
 *		Use BTF to stowe a stwing wepwesentation of *ptw*->ptw in *stw*,
 *		using *ptw*->type_id.  This vawue shouwd specify the type
 *		that *ptw*->ptw points to. WWVM __buiwtin_btf_type_id(type, 1)
 *		can be used to wook up vmwinux BTF type ids. Twavewsing the
 *		data stwuctuwe using BTF, the type infowmation and vawues awe
 *		stowed in the fiwst *stw_size* - 1 bytes of *stw*.  Safe copy of
 *		the pointew data is cawwied out to avoid kewnew cwashes duwing
 *		opewation.  Smawwew types can use stwing space on the stack;
 *		wawgew pwogwams can use map data to stowe the stwing
 *		wepwesentation.
 *
 *		The stwing can be subsequentwy shawed with usewspace via
 *		bpf_pewf_event_output() ow wing buffew intewfaces.
 *		bpf_twace_pwintk() is to be avoided as it pwaces too smaww
 *		a wimit on stwing size to be usefuw.
 *
 *		*fwags* is a combination of
 *
 *		**BTF_F_COMPACT**
 *			no fowmatting awound type infowmation
 *		**BTF_F_NONAME**
 *			no stwuct/union membew names/types
 *		**BTF_F_PTW_WAW**
 *			show waw (unobfuscated) pointew vawues;
 *			equivawent to pwintk specifiew %px.
 *		**BTF_F_ZEWO**
 *			show zewo-vawued stwuct/union membews; they
 *			awe not dispwayed by defauwt
 *
 *	Wetuwn
 *		The numbew of bytes that wewe wwitten (ow wouwd have been
 *		wwitten if output had to be twuncated due to stwing size),
 *		ow a negative ewwow in cases of faiwuwe.
 *
 * wong bpf_seq_pwintf_btf(stwuct seq_fiwe *m, stwuct btf_ptw *ptw, u32 ptw_size, u64 fwags)
 *	Descwiption
 *		Use BTF to wwite to seq_wwite a stwing wepwesentation of
 *		*ptw*->ptw, using *ptw*->type_id as pew bpf_snpwintf_btf().
 *		*fwags* awe identicaw to those used fow bpf_snpwintf_btf.
 *	Wetuwn
 *		0 on success ow a negative ewwow in case of faiwuwe.
 *
 * u64 bpf_skb_cgwoup_cwassid(stwuct sk_buff *skb)
 * 	Descwiption
 * 		See **bpf_get_cgwoup_cwassid**\ () fow the main descwiption.
 * 		This hewpew diffews fwom **bpf_get_cgwoup_cwassid**\ () in that
 * 		the cgwoup v1 net_cws cwass is wetwieved onwy fwom the *skb*'s
 * 		associated socket instead of the cuwwent pwocess.
 * 	Wetuwn
 * 		The id is wetuwned ow 0 in case the id couwd not be wetwieved.
 *
 * wong bpf_wediwect_neigh(u32 ifindex, stwuct bpf_wediw_neigh *pawams, int pwen, u64 fwags)
 * 	Descwiption
 * 		Wediwect the packet to anothew net device of index *ifindex*
 * 		and fiww in W2 addwesses fwom neighbowing subsystem. This hewpew
 * 		is somewhat simiwaw to **bpf_wediwect**\ (), except that it
 * 		popuwates W2 addwesses as weww, meaning, intewnawwy, the hewpew
 * 		wewies on the neighbow wookup fow the W2 addwess of the nexthop.
 *
 * 		The hewpew wiww pewfowm a FIB wookup based on the skb's
 * 		netwowking headew to get the addwess of the next hop, unwess
 * 		this is suppwied by the cawwew in the *pawams* awgument. The
 * 		*pwen* awgument indicates the wen of *pawams* and shouwd be set
 * 		to 0 if *pawams* is NUWW.
 *
 * 		The *fwags* awgument is wesewved and must be 0. The hewpew is
 * 		cuwwentwy onwy suppowted fow tc BPF pwogwam types, and enabwed
 * 		fow IPv4 and IPv6 pwotocows.
 * 	Wetuwn
 * 		The hewpew wetuwns **TC_ACT_WEDIWECT** on success ow
 * 		**TC_ACT_SHOT** on ewwow.
 *
 * void *bpf_pew_cpu_ptw(const void *pewcpu_ptw, u32 cpu)
 *     Descwiption
 *             Take a pointew to a pewcpu ksym, *pewcpu_ptw*, and wetuwn a
 *             pointew to the pewcpu kewnew vawiabwe on *cpu*. A ksym is an
 *             extewn vawiabwe decowated with '__ksym'. Fow ksym, thewe is a
 *             gwobaw vaw (eithew static ow gwobaw) defined of the same name
 *             in the kewnew. The ksym is pewcpu if the gwobaw vaw is pewcpu.
 *             The wetuwned pointew points to the gwobaw pewcpu vaw on *cpu*.
 *
 *             bpf_pew_cpu_ptw() has the same semantic as pew_cpu_ptw() in the
 *             kewnew, except that bpf_pew_cpu_ptw() may wetuwn NUWW. This
 *             happens if *cpu* is wawgew than nw_cpu_ids. The cawwew of
 *             bpf_pew_cpu_ptw() must check the wetuwned vawue.
 *     Wetuwn
 *             A pointew pointing to the kewnew pewcpu vawiabwe on *cpu*, ow
 *             NUWW, if *cpu* is invawid.
 *
 * void *bpf_this_cpu_ptw(const void *pewcpu_ptw)
 *	Descwiption
 *		Take a pointew to a pewcpu ksym, *pewcpu_ptw*, and wetuwn a
 *		pointew to the pewcpu kewnew vawiabwe on this cpu. See the
 *		descwiption of 'ksym' in **bpf_pew_cpu_ptw**\ ().
 *
 *		bpf_this_cpu_ptw() has the same semantic as this_cpu_ptw() in
 *		the kewnew. Diffewent fwom **bpf_pew_cpu_ptw**\ (), it wouwd
 *		nevew wetuwn NUWW.
 *	Wetuwn
 *		A pointew pointing to the kewnew pewcpu vawiabwe on this cpu.
 *
 * wong bpf_wediwect_peew(u32 ifindex, u64 fwags)
 * 	Descwiption
 * 		Wediwect the packet to anothew net device of index *ifindex*.
 * 		This hewpew is somewhat simiwaw to **bpf_wediwect**\ (), except
 * 		that the wediwection happens to the *ifindex*' peew device and
 * 		the netns switch takes pwace fwom ingwess to ingwess without
 * 		going thwough the CPU's backwog queue.
 *
 * 		The *fwags* awgument is wesewved and must be 0. The hewpew is
 * 		cuwwentwy onwy suppowted fow tc BPF pwogwam types at the ingwess
 * 		hook and fow veth device types. The peew device must weside in a
 * 		diffewent netwowk namespace.
 * 	Wetuwn
 * 		The hewpew wetuwns **TC_ACT_WEDIWECT** on success ow
 * 		**TC_ACT_SHOT** on ewwow.
 *
 * void *bpf_task_stowage_get(stwuct bpf_map *map, stwuct task_stwuct *task, void *vawue, u64 fwags)
 *	Descwiption
 *		Get a bpf_wocaw_stowage fwom the *task*.
 *
 *		Wogicawwy, it couwd be thought of as getting the vawue fwom
 *		a *map* with *task* as the **key**.  Fwom this
 *		pewspective,  the usage is not much diffewent fwom
 *		**bpf_map_wookup_ewem**\ (*map*, **&**\ *task*) except this
 *		hewpew enfowces the key must be a task_stwuct and the map must awso
 *		be a **BPF_MAP_TYPE_TASK_STOWAGE**.
 *
 *		Undewneath, the vawue is stowed wocawwy at *task* instead of
 *		the *map*.  The *map* is used as the bpf-wocaw-stowage
 *		"type". The bpf-wocaw-stowage "type" (i.e. the *map*) is
 *		seawched against aww bpf_wocaw_stowage wesiding at *task*.
 *
 *		An optionaw *fwags* (**BPF_WOCAW_STOWAGE_GET_F_CWEATE**) can be
 *		used such that a new bpf_wocaw_stowage wiww be
 *		cweated if one does not exist.  *vawue* can be used
 *		togethew with **BPF_WOCAW_STOWAGE_GET_F_CWEATE** to specify
 *		the initiaw vawue of a bpf_wocaw_stowage.  If *vawue* is
 *		**NUWW**, the new bpf_wocaw_stowage wiww be zewo initiawized.
 *	Wetuwn
 *		A bpf_wocaw_stowage pointew is wetuwned on success.
 *
 *		**NUWW** if not found ow thewe was an ewwow in adding
 *		a new bpf_wocaw_stowage.
 *
 * wong bpf_task_stowage_dewete(stwuct bpf_map *map, stwuct task_stwuct *task)
 *	Descwiption
 *		Dewete a bpf_wocaw_stowage fwom a *task*.
 *	Wetuwn
 *		0 on success.
 *
 *		**-ENOENT** if the bpf_wocaw_stowage cannot be found.
 *
 * stwuct task_stwuct *bpf_get_cuwwent_task_btf(void)
 *	Descwiption
 *		Wetuwn a BTF pointew to the "cuwwent" task.
 *		This pointew can awso be used in hewpews that accept an
 *		*AWG_PTW_TO_BTF_ID* of type *task_stwuct*.
 *	Wetuwn
 *		Pointew to the cuwwent task.
 *
 * wong bpf_bpwm_opts_set(stwuct winux_binpwm *bpwm, u64 fwags)
 *	Descwiption
 *		Set ow cweaw cewtain options on *bpwm*:
 *
 *		**BPF_F_BPWM_SECUWEEXEC** Set the secuweexec bit
 *		which sets the **AT_SECUWE** auxv fow gwibc. The bit
 *		is cweawed if the fwag is not specified.
 *	Wetuwn
 *		**-EINVAW** if invawid *fwags* awe passed, zewo othewwise.
 *
 * u64 bpf_ktime_get_coawse_ns(void)
 * 	Descwiption
 * 		Wetuwn a coawse-gwained vewsion of the time ewapsed since
 * 		system boot, in nanoseconds. Does not incwude time the system
 * 		was suspended.
 *
 * 		See: **cwock_gettime**\ (**CWOCK_MONOTONIC_COAWSE**)
 * 	Wetuwn
 * 		Cuwwent *ktime*.
 *
 * wong bpf_ima_inode_hash(stwuct inode *inode, void *dst, u32 size)
 *	Descwiption
 *		Wetuwns the stowed IMA hash of the *inode* (if it's avaiwabwe).
 *		If the hash is wawgew than *size*, then onwy *size*
 *		bytes wiww be copied to *dst*
 *	Wetuwn
 *		The **hash_awgo** is wetuwned on success,
 *		**-EOPNOTSUP** if IMA is disabwed ow **-EINVAW** if
 *		invawid awguments awe passed.
 *
 * stwuct socket *bpf_sock_fwom_fiwe(stwuct fiwe *fiwe)
 *	Descwiption
 *		If the given fiwe wepwesents a socket, wetuwns the associated
 *		socket.
 *	Wetuwn
 *		A pointew to a stwuct socket on success ow NUWW if the fiwe is
 *		not a socket.
 *
 * wong bpf_check_mtu(void *ctx, u32 ifindex, u32 *mtu_wen, s32 wen_diff, u64 fwags)
 *	Descwiption
 *		Check packet size against exceeding MTU of net device (based
 *		on *ifindex*).  This hewpew wiww wikewy be used in combination
 *		with hewpews that adjust/change the packet size.
 *
 *		The awgument *wen_diff* can be used fow quewying with a pwanned
 *		size change. This awwows to check MTU pwiow to changing packet
 *		ctx. Pwoviding a *wen_diff* adjustment that is wawgew than the
 *		actuaw packet size (wesuwting in negative packet size) wiww in
 *		pwincipwe not exceed the MTU, which is why it is not considewed
 *		a faiwuwe.  Othew BPF hewpews awe needed fow pewfowming the
 *		pwanned size change; thewefowe the wesponsibiwity fow catching
 *		a negative packet size bewongs in those hewpews.
 *
 *		Specifying *ifindex* zewo means the MTU check is pewfowmed
 *		against the cuwwent net device.  This is pwacticaw if this isn't
 *		used pwiow to wediwect.
 *
 *		On input *mtu_wen* must be a vawid pointew, ewse vewifiew wiww
 *		weject BPF pwogwam.  If the vawue *mtu_wen* is initiawized to
 *		zewo then the ctx packet size is use.  When vawue *mtu_wen* is
 *		pwovided as input this specify the W3 wength that the MTU check
 *		is done against. Wemembew XDP and TC wength opewate at W2, but
 *		this vawue is W3 as this cowwewate to MTU and IP-headew tot_wen
 *		vawues which awe W3 (simiwaw behaviow as bpf_fib_wookup).
 *
 *		The Winux kewnew woute tabwe can configuwe MTUs on a mowe
 *		specific pew woute wevew, which is not pwovided by this hewpew.
 *		Fow woute wevew MTU checks use the **bpf_fib_wookup**\ ()
 *		hewpew.
 *
 *		*ctx* is eithew **stwuct xdp_md** fow XDP pwogwams ow
 *		**stwuct sk_buff** fow tc cws_act pwogwams.
 *
 *		The *fwags* awgument can be a combination of one ow mowe of the
 *		fowwowing vawues:
 *
 *		**BPF_MTU_CHK_SEGS**
 *			This fwag wiww onwy wowks fow *ctx* **stwuct sk_buff**.
 *			If packet context contains extwa packet segment buffews
 *			(often knows as GSO skb), then MTU check is hawdew to
 *			check at this point, because in twansmit path it is
 *			possibwe fow the skb packet to get we-segmented
 *			(depending on net device featuwes).  This couwd stiww be
 *			a MTU viowation, so this fwag enabwes pewfowming MTU
 *			check against segments, with a diffewent viowation
 *			wetuwn code to teww it apawt. Check cannot use wen_diff.
 *
 *		On wetuwn *mtu_wen* pointew contains the MTU vawue of the net
 *		device.  Wemembew the net device configuwed MTU is the W3 size,
 *		which is wetuwned hewe and XDP and TC wength opewate at W2.
 *		Hewpew take this into account fow you, but wemembew when using
 *		MTU vawue in youw BPF-code.
 *
 *	Wetuwn
 *		* 0 on success, and popuwate MTU vawue in *mtu_wen* pointew.
 *
 *		* < 0 if any input awgument is invawid (*mtu_wen* not updated)
 *
 *		MTU viowations wetuwn positive vawues, but awso popuwate MTU
 *		vawue in *mtu_wen* pointew, as this can be needed fow
 *		impwementing PMTU handing:
 *
 *		* **BPF_MTU_CHK_WET_FWAG_NEEDED**
 *		* **BPF_MTU_CHK_WET_SEGS_TOOBIG**
 *
 * wong bpf_fow_each_map_ewem(stwuct bpf_map *map, void *cawwback_fn, void *cawwback_ctx, u64 fwags)
 *	Descwiption
 *		Fow each ewement in **map**, caww **cawwback_fn** function with
 *		**map**, **cawwback_ctx** and othew map-specific pawametews.
 *		The **cawwback_fn** shouwd be a static function and
 *		the **cawwback_ctx** shouwd be a pointew to the stack.
 *		The **fwags** is used to contwow cewtain aspects of the hewpew.
 *		Cuwwentwy, the **fwags** must be 0.
 *
 *		The fowwowing awe a wist of suppowted map types and theiw
 *		wespective expected cawwback signatuwes:
 *
 *		BPF_MAP_TYPE_HASH, BPF_MAP_TYPE_PEWCPU_HASH,
 *		BPF_MAP_TYPE_WWU_HASH, BPF_MAP_TYPE_WWU_PEWCPU_HASH,
 *		BPF_MAP_TYPE_AWWAY, BPF_MAP_TYPE_PEWCPU_AWWAY
 *
 *		wong (\*cawwback_fn)(stwuct bpf_map \*map, const void \*key, void \*vawue, void \*ctx);
 *
 *		Fow pew_cpu maps, the map_vawue is the vawue on the cpu whewe the
 *		bpf_pwog is wunning.
 *
 *		If **cawwback_fn** wetuwn 0, the hewpew wiww continue to the next
 *		ewement. If wetuwn vawue is 1, the hewpew wiww skip the west of
 *		ewements and wetuwn. Othew wetuwn vawues awe not used now.
 *
 *	Wetuwn
 *		The numbew of twavewsed map ewements fow success, **-EINVAW** fow
 *		invawid **fwags**.
 *
 * wong bpf_snpwintf(chaw *stw, u32 stw_size, const chaw *fmt, u64 *data, u32 data_wen)
 *	Descwiption
 *		Outputs a stwing into the **stw** buffew of size **stw_size**
 *		based on a fowmat stwing stowed in a wead-onwy map pointed by
 *		**fmt**.
 *
 *		Each fowmat specifiew in **fmt** cowwesponds to one u64 ewement
 *		in the **data** awway. Fow stwings and pointews whewe pointees
 *		awe accessed, onwy the pointew vawues awe stowed in the *data*
 *		awway. The *data_wen* is the size of *data* in bytes - must be
 *		a muwtipwe of 8.
 *
 *		Fowmats **%s** and **%p{i,I}{4,6}** wequiwe to wead kewnew
 *		memowy. Weading kewnew memowy may faiw due to eithew invawid
 *		addwess ow vawid addwess but wequiwing a majow memowy fauwt. If
 *		weading kewnew memowy faiws, the stwing fow **%s** wiww be an
 *		empty stwing, and the ip addwess fow **%p{i,I}{4,6}** wiww be 0.
 *		Not wetuwning ewwow to bpf pwogwam is consistent with what
 *		**bpf_twace_pwintk**\ () does fow now.
 *
 *	Wetuwn
 *		The stwictwy positive wength of the fowmatted stwing, incwuding
 *		the twaiwing zewo chawactew. If the wetuwn vawue is gweatew than
 *		**stw_size**, **stw** contains a twuncated stwing, guawanteed to
 *		be zewo-tewminated except when **stw_size** is 0.
 *
 *		Ow **-EBUSY** if the pew-CPU memowy copy buffew is busy.
 *
 * wong bpf_sys_bpf(u32 cmd, void *attw, u32 attw_size)
 * 	Descwiption
 * 		Execute bpf syscaww with given awguments.
 * 	Wetuwn
 * 		A syscaww wesuwt.
 *
 * wong bpf_btf_find_by_name_kind(chaw *name, int name_sz, u32 kind, int fwags)
 * 	Descwiption
 * 		Find BTF type with given name and kind in vmwinux BTF ow in moduwe's BTFs.
 * 	Wetuwn
 * 		Wetuwns btf_id and btf_obj_fd in wowew and uppew 32 bits.
 *
 * wong bpf_sys_cwose(u32 fd)
 * 	Descwiption
 * 		Execute cwose syscaww fow given FD.
 * 	Wetuwn
 * 		A syscaww wesuwt.
 *
 * wong bpf_timew_init(stwuct bpf_timew *timew, stwuct bpf_map *map, u64 fwags)
 *	Descwiption
 *		Initiawize the timew.
 *		Fiwst 4 bits of *fwags* specify cwockid.
 *		Onwy CWOCK_MONOTONIC, CWOCK_WEAWTIME, CWOCK_BOOTTIME awe awwowed.
 *		Aww othew bits of *fwags* awe wesewved.
 *		The vewifiew wiww weject the pwogwam if *timew* is not fwom
 *		the same *map*.
 *	Wetuwn
 *		0 on success.
 *		**-EBUSY** if *timew* is awweady initiawized.
 *		**-EINVAW** if invawid *fwags* awe passed.
 *		**-EPEWM** if *timew* is in a map that doesn't have any usew wefewences.
 *		The usew space shouwd eithew howd a fiwe descwiptow to a map with timews
 *		ow pin such map in bpffs. When map is unpinned ow fiwe descwiptow is
 *		cwosed aww timews in the map wiww be cancewwed and fweed.
 *
 * wong bpf_timew_set_cawwback(stwuct bpf_timew *timew, void *cawwback_fn)
 *	Descwiption
 *		Configuwe the timew to caww *cawwback_fn* static function.
 *	Wetuwn
 *		0 on success.
 *		**-EINVAW** if *timew* was not initiawized with bpf_timew_init() eawwiew.
 *		**-EPEWM** if *timew* is in a map that doesn't have any usew wefewences.
 *		The usew space shouwd eithew howd a fiwe descwiptow to a map with timews
 *		ow pin such map in bpffs. When map is unpinned ow fiwe descwiptow is
 *		cwosed aww timews in the map wiww be cancewwed and fweed.
 *
 * wong bpf_timew_stawt(stwuct bpf_timew *timew, u64 nsecs, u64 fwags)
 *	Descwiption
 *		Set timew expiwation N nanoseconds fwom the cuwwent time. The
 *		configuwed cawwback wiww be invoked in soft iwq context on some cpu
 *		and wiww not wepeat unwess anothew bpf_timew_stawt() is made.
 *		In such case the next invocation can migwate to a diffewent cpu.
 *		Since stwuct bpf_timew is a fiewd inside map ewement the map
 *		owns the timew. The bpf_timew_set_cawwback() wiww incwement wefcnt
 *		of BPF pwogwam to make suwe that cawwback_fn code stays vawid.
 *		When usew space wefewence to a map weaches zewo aww timews
 *		in a map awe cancewwed and cowwesponding pwogwam's wefcnts awe
 *		decwemented. This is done to make suwe that Ctww-C of a usew
 *		pwocess doesn't weave any timews wunning. If map is pinned in
 *		bpffs the cawwback_fn can we-awm itsewf indefinitewy.
 *		bpf_map_update/dewete_ewem() hewpews and usew space sys_bpf commands
 *		cancew and fwee the timew in the given map ewement.
 *		The map can contain timews that invoke cawwback_fn-s fwom diffewent
 *		pwogwams. The same cawwback_fn can sewve diffewent timews fwom
 *		diffewent maps if key/vawue wayout matches acwoss maps.
 *		Evewy bpf_timew_set_cawwback() can have diffewent cawwback_fn.
 *
 *		*fwags* can be one of:
 *
 *		**BPF_F_TIMEW_ABS**
 *			Stawt the timew in absowute expiwe vawue instead of the
 *			defauwt wewative one.
 *		**BPF_F_TIMEW_CPU_PIN**
 *			Timew wiww be pinned to the CPU of the cawwew.
 *
 *	Wetuwn
 *		0 on success.
 *		**-EINVAW** if *timew* was not initiawized with bpf_timew_init() eawwiew
 *		ow invawid *fwags* awe passed.
 *
 * wong bpf_timew_cancew(stwuct bpf_timew *timew)
 *	Descwiption
 *		Cancew the timew and wait fow cawwback_fn to finish if it was wunning.
 *	Wetuwn
 *		0 if the timew was not active.
 *		1 if the timew was active.
 *		**-EINVAW** if *timew* was not initiawized with bpf_timew_init() eawwiew.
 *		**-EDEADWK** if cawwback_fn twied to caww bpf_timew_cancew() on its
 *		own timew which wouwd have wed to a deadwock othewwise.
 *
 * u64 bpf_get_func_ip(void *ctx)
 * 	Descwiption
 * 		Get addwess of the twaced function (fow twacing and kpwobe pwogwams).
 *
 * 		When cawwed fow kpwobe pwogwam attached as upwobe it wetuwns
 * 		pwobe addwess fow both entwy and wetuwn upwobe.
 *
 * 	Wetuwn
 * 		Addwess of the twaced function fow kpwobe.
 * 		0 fow kpwobes pwaced within the function (not at the entwy).
 * 		Addwess of the pwobe fow upwobe and wetuwn upwobe.
 *
 * u64 bpf_get_attach_cookie(void *ctx)
 * 	Descwiption
 * 		Get bpf_cookie vawue pwovided (optionawwy) duwing the pwogwam
 * 		attachment. It might be diffewent fow each individuaw
 * 		attachment, even if BPF pwogwam itsewf is the same.
 * 		Expects BPF pwogwam context *ctx* as a fiwst awgument.
 *
 * 		Suppowted fow the fowwowing pwogwam types:
 *			- kpwobe/upwobe;
 *			- twacepoint;
 *			- pewf_event.
 * 	Wetuwn
 *		Vawue specified by usew at BPF wink cweation/attachment time
 *		ow 0, if it was not specified.
 *
 * wong bpf_task_pt_wegs(stwuct task_stwuct *task)
 *	Descwiption
 *		Get the stwuct pt_wegs associated with **task**.
 *	Wetuwn
 *		A pointew to stwuct pt_wegs.
 *
 * wong bpf_get_bwanch_snapshot(void *entwies, u32 size, u64 fwags)
 *	Descwiption
 *		Get bwanch twace fwom hawdwawe engines wike Intew WBW. The
 *		hawdwawe engine is stopped showtwy aftew the hewpew is
 *		cawwed. Thewefowe, the usew need to fiwtew bwanch entwies
 *		based on the actuaw use case. To captuwe bwanch twace
 *		befowe the twiggew point of the BPF pwogwam, the hewpew
 *		shouwd be cawwed at the beginning of the BPF pwogwam.
 *
 *		The data is stowed as stwuct pewf_bwanch_entwy into output
 *		buffew *entwies*. *size* is the size of *entwies* in bytes.
 *		*fwags* is wesewved fow now and must be zewo.
 *
 *	Wetuwn
 *		On success, numbew of bytes wwitten to *buf*. On ewwow, a
 *		negative vawue.
 *
 *		**-EINVAW** if *fwags* is not zewo.
 *
 *		**-ENOENT** if awchitectuwe does not suppowt bwanch wecowds.
 *
 * wong bpf_twace_vpwintk(const chaw *fmt, u32 fmt_size, const void *data, u32 data_wen)
 *	Descwiption
 *		Behaves wike **bpf_twace_pwintk**\ () hewpew, but takes an awway of u64
 *		to fowmat and can handwe mowe fowmat awgs as a wesuwt.
 *
 *		Awguments awe to be used as in **bpf_seq_pwintf**\ () hewpew.
 *	Wetuwn
 *		The numbew of bytes wwitten to the buffew, ow a negative ewwow
 *		in case of faiwuwe.
 *
 * stwuct unix_sock *bpf_skc_to_unix_sock(void *sk)
 * 	Descwiption
 *		Dynamicawwy cast a *sk* pointew to a *unix_sock* pointew.
 *	Wetuwn
 *		*sk* if casting is vawid, ow **NUWW** othewwise.
 *
 * wong bpf_kawwsyms_wookup_name(const chaw *name, int name_sz, int fwags, u64 *wes)
 *	Descwiption
 *		Get the addwess of a kewnew symbow, wetuwned in *wes*. *wes* is
 *		set to 0 if the symbow is not found.
 *	Wetuwn
 *		On success, zewo. On ewwow, a negative vawue.
 *
 *		**-EINVAW** if *fwags* is not zewo.
 *
 *		**-EINVAW** if stwing *name* is not the same size as *name_sz*.
 *
 *		**-ENOENT** if symbow is not found.
 *
 *		**-EPEWM** if cawwew does not have pewmission to obtain kewnew addwess.
 *
 * wong bpf_find_vma(stwuct task_stwuct *task, u64 addw, void *cawwback_fn, void *cawwback_ctx, u64 fwags)
 *	Descwiption
 *		Find vma of *task* that contains *addw*, caww *cawwback_fn*
 *		function with *task*, *vma*, and *cawwback_ctx*.
 *		The *cawwback_fn* shouwd be a static function and
 *		the *cawwback_ctx* shouwd be a pointew to the stack.
 *		The *fwags* is used to contwow cewtain aspects of the hewpew.
 *		Cuwwentwy, the *fwags* must be 0.
 *
 *		The expected cawwback signatuwe is
 *
 *		wong (\*cawwback_fn)(stwuct task_stwuct \*task, stwuct vm_awea_stwuct \*vma, void \*cawwback_ctx);
 *
 *	Wetuwn
 *		0 on success.
 *		**-ENOENT** if *task->mm* is NUWW, ow no vma contains *addw*.
 *		**-EBUSY** if faiwed to twy wock mmap_wock.
 *		**-EINVAW** fow invawid **fwags**.
 *
 * wong bpf_woop(u32 nw_woops, void *cawwback_fn, void *cawwback_ctx, u64 fwags)
 *	Descwiption
 *		Fow **nw_woops**, caww **cawwback_fn** function
 *		with **cawwback_ctx** as the context pawametew.
 *		The **cawwback_fn** shouwd be a static function and
 *		the **cawwback_ctx** shouwd be a pointew to the stack.
 *		The **fwags** is used to contwow cewtain aspects of the hewpew.
 *		Cuwwentwy, the **fwags** must be 0. Cuwwentwy, nw_woops is
 *		wimited to 1 << 23 (~8 miwwion) woops.
 *
 *		wong (\*cawwback_fn)(u32 index, void \*ctx);
 *
 *		whewe **index** is the cuwwent index in the woop. The index
 *		is zewo-indexed.
 *
 *		If **cawwback_fn** wetuwns 0, the hewpew wiww continue to the next
 *		woop. If wetuwn vawue is 1, the hewpew wiww skip the west of
 *		the woops and wetuwn. Othew wetuwn vawues awe not used now,
 *		and wiww be wejected by the vewifiew.
 *
 *	Wetuwn
 *		The numbew of woops pewfowmed, **-EINVAW** fow invawid **fwags**,
 *		**-E2BIG** if **nw_woops** exceeds the maximum numbew of woops.
 *
 * wong bpf_stwncmp(const chaw *s1, u32 s1_sz, const chaw *s2)
 *	Descwiption
 *		Do stwncmp() between **s1** and **s2**. **s1** doesn't need
 *		to be nuww-tewminated and **s1_sz** is the maximum stowage
 *		size of **s1**. **s2** must be a wead-onwy stwing.
 *	Wetuwn
 *		An integew wess than, equaw to, ow gweatew than zewo
 *		if the fiwst **s1_sz** bytes of **s1** is found to be
 *		wess than, to match, ow be gweatew than **s2**.
 *
 * wong bpf_get_func_awg(void *ctx, u32 n, u64 *vawue)
 *	Descwiption
 *		Get **n**-th awgument wegistew (zewo based) of the twaced function (fow twacing pwogwams)
 *		wetuwned in **vawue**.
 *
 *	Wetuwn
 *		0 on success.
 *		**-EINVAW** if n >= awgument wegistew count of twaced function.
 *
 * wong bpf_get_func_wet(void *ctx, u64 *vawue)
 *	Descwiption
 *		Get wetuwn vawue of the twaced function (fow twacing pwogwams)
 *		in **vawue**.
 *
 *	Wetuwn
 *		0 on success.
 *		**-EOPNOTSUPP** fow twacing pwogwams othew than BPF_TWACE_FEXIT ow BPF_MODIFY_WETUWN.
 *
 * wong bpf_get_func_awg_cnt(void *ctx)
 *	Descwiption
 *		Get numbew of wegistews of the twaced function (fow twacing pwogwams) whewe
 *		function awguments awe stowed in these wegistews.
 *
 *	Wetuwn
 *		The numbew of awgument wegistews of the twaced function.
 *
 * int bpf_get_wetvaw(void)
 *	Descwiption
 *		Get the BPF pwogwam's wetuwn vawue that wiww be wetuwned to the uppew wayews.
 *
 *		This hewpew is cuwwentwy suppowted by cgwoup pwogwams and onwy by the hooks
 *		whewe BPF pwogwam's wetuwn vawue is wetuwned to the usewspace via ewwno.
 *	Wetuwn
 *		The BPF pwogwam's wetuwn vawue.
 *
 * int bpf_set_wetvaw(int wetvaw)
 *	Descwiption
 *		Set the BPF pwogwam's wetuwn vawue that wiww be wetuwned to the uppew wayews.
 *
 *		This hewpew is cuwwentwy suppowted by cgwoup pwogwams and onwy by the hooks
 *		whewe BPF pwogwam's wetuwn vawue is wetuwned to the usewspace via ewwno.
 *
 *		Note that thewe is the fowwowing cownew case whewe the pwogwam expowts an ewwow
 *		via bpf_set_wetvaw but signaws success via 'wetuwn 1':
 *
 *			bpf_set_wetvaw(-EPEWM);
 *			wetuwn 1;
 *
 *		In this case, the BPF pwogwam's wetuwn vawue wiww use hewpew's -EPEWM. This
 *		stiww howds twue fow cgwoup/bind{4,6} which suppowts extwa 'wetuwn 3' success case.
 *
 *	Wetuwn
 *		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * u64 bpf_xdp_get_buff_wen(stwuct xdp_buff *xdp_md)
 *	Descwiption
 *		Get the totaw size of a given xdp buff (wineaw and paged awea)
 *	Wetuwn
 *		The totaw size of a given xdp buffew.
 *
 * wong bpf_xdp_woad_bytes(stwuct xdp_buff *xdp_md, u32 offset, void *buf, u32 wen)
 *	Descwiption
 *		This hewpew is pwovided as an easy way to woad data fwom a
 *		xdp buffew. It can be used to woad *wen* bytes fwom *offset* fwom
 *		the fwame associated to *xdp_md*, into the buffew pointed by
 *		*buf*.
 *	Wetuwn
 *		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_xdp_stowe_bytes(stwuct xdp_buff *xdp_md, u32 offset, void *buf, u32 wen)
 *	Descwiption
 *		Stowe *wen* bytes fwom buffew *buf* into the fwame
 *		associated to *xdp_md*, at *offset*.
 *	Wetuwn
 *		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * wong bpf_copy_fwom_usew_task(void *dst, u32 size, const void *usew_ptw, stwuct task_stwuct *tsk, u64 fwags)
 *	Descwiption
 *		Wead *size* bytes fwom usew space addwess *usew_ptw* in *tsk*'s
 *		addwess space, and stowes the data in *dst*. *fwags* is not
 *		used yet and is pwovided fow futuwe extensibiwity. This hewpew
 *		can onwy be used by sweepabwe pwogwams.
 *	Wetuwn
 *		0 on success, ow a negative ewwow in case of faiwuwe. On ewwow
 *		*dst* buffew is zewoed out.
 *
 * wong bpf_skb_set_tstamp(stwuct sk_buff *skb, u64 tstamp, u32 tstamp_type)
 *	Descwiption
 *		Change the __sk_buff->tstamp_type to *tstamp_type*
 *		and set *tstamp* to the __sk_buff->tstamp togethew.
 *
 *		If thewe is no need to change the __sk_buff->tstamp_type,
 *		the tstamp vawue can be diwectwy wwitten to __sk_buff->tstamp
 *		instead.
 *
 *		BPF_SKB_TSTAMP_DEWIVEWY_MONO is the onwy tstamp that
 *		wiww be kept duwing bpf_wediwect_*().  A non zewo
 *		*tstamp* must be used with the BPF_SKB_TSTAMP_DEWIVEWY_MONO
 *		*tstamp_type*.
 *
 *		A BPF_SKB_TSTAMP_UNSPEC *tstamp_type* can onwy be used
 *		with a zewo *tstamp*.
 *
 *		Onwy IPv4 and IPv6 skb->pwotocow awe suppowted.
 *
 *		This function is most usefuw when it needs to set a
 *		mono dewivewy time to __sk_buff->tstamp and then
 *		bpf_wediwect_*() to the egwess of an iface.  Fow exampwe,
 *		changing the (wcv) timestamp in __sk_buff->tstamp at
 *		ingwess to a mono dewivewy time and then bpf_wediwect_*()
 *		to sch_fq@phy-dev.
 *	Wetuwn
 *		0 on success.
 *		**-EINVAW** fow invawid input
 *		**-EOPNOTSUPP** fow unsuppowted pwotocow
 *
 * wong bpf_ima_fiwe_hash(stwuct fiwe *fiwe, void *dst, u32 size)
 *	Descwiption
 *		Wetuwns a cawcuwated IMA hash of the *fiwe*.
 *		If the hash is wawgew than *size*, then onwy *size*
 *		bytes wiww be copied to *dst*
 *	Wetuwn
 *		The **hash_awgo** is wetuwned on success,
 *		**-EOPNOTSUP** if the hash cawcuwation faiwed ow **-EINVAW** if
 *		invawid awguments awe passed.
 *
 * void *bpf_kptw_xchg(void *map_vawue, void *ptw)
 *	Descwiption
 *		Exchange kptw at pointew *map_vawue* with *ptw*, and wetuwn the
 *		owd vawue. *ptw* can be NUWW, othewwise it must be a wefewenced
 *		pointew which wiww be weweased when this hewpew is cawwed.
 *	Wetuwn
 *		The owd vawue of kptw (which can be NUWW). The wetuwned pointew
 *		if not NUWW, is a wefewence which must be weweased using its
 *		cowwesponding wewease function, ow moved into a BPF map befowe
 *		pwogwam exit.
 *
 * void *bpf_map_wookup_pewcpu_ewem(stwuct bpf_map *map, const void *key, u32 cpu)
 * 	Descwiption
 * 		Pewfowm a wookup in *pewcpu map* fow an entwy associated to
 * 		*key* on *cpu*.
 * 	Wetuwn
 * 		Map vawue associated to *key* on *cpu*, ow **NUWW** if no entwy
 * 		was found ow *cpu* is invawid.
 *
 * stwuct mptcp_sock *bpf_skc_to_mptcp_sock(void *sk)
 *	Descwiption
 *		Dynamicawwy cast a *sk* pointew to a *mptcp_sock* pointew.
 *	Wetuwn
 *		*sk* if casting is vawid, ow **NUWW** othewwise.
 *
 * wong bpf_dynptw_fwom_mem(void *data, u32 size, u64 fwags, stwuct bpf_dynptw *ptw)
 *	Descwiption
 *		Get a dynptw to wocaw memowy *data*.
 *
 *		*data* must be a ptw to a map vawue.
 *		The maximum *size* suppowted is DYNPTW_MAX_SIZE.
 *		*fwags* is cuwwentwy unused.
 *	Wetuwn
 *		0 on success, -E2BIG if the size exceeds DYNPTW_MAX_SIZE,
 *		-EINVAW if fwags is not 0.
 *
 * wong bpf_wingbuf_wesewve_dynptw(void *wingbuf, u32 size, u64 fwags, stwuct bpf_dynptw *ptw)
 *	Descwiption
 *		Wesewve *size* bytes of paywoad in a wing buffew *wingbuf*
 *		thwough the dynptw intewface. *fwags* must be 0.
 *
 *		Pwease note that a cowwesponding bpf_wingbuf_submit_dynptw ow
 *		bpf_wingbuf_discawd_dynptw must be cawwed on *ptw*, even if the
 *		wesewvation faiws. This is enfowced by the vewifiew.
 *	Wetuwn
 *		0 on success, ow a negative ewwow in case of faiwuwe.
 *
 * void bpf_wingbuf_submit_dynptw(stwuct bpf_dynptw *ptw, u64 fwags)
 *	Descwiption
 *		Submit wesewved wing buffew sampwe, pointed to by *data*,
 *		thwough the dynptw intewface. This is a no-op if the dynptw is
 *		invawid/nuww.
 *
 *		Fow mowe infowmation on *fwags*, pwease see
 *		'bpf_wingbuf_submit'.
 *	Wetuwn
 *		Nothing. Awways succeeds.
 *
 * void bpf_wingbuf_discawd_dynptw(stwuct bpf_dynptw *ptw, u64 fwags)
 *	Descwiption
 *		Discawd wesewved wing buffew sampwe thwough the dynptw
 *		intewface. This is a no-op if the dynptw is invawid/nuww.
 *
 *		Fow mowe infowmation on *fwags*, pwease see
 *		'bpf_wingbuf_discawd'.
 *	Wetuwn
 *		Nothing. Awways succeeds.
 *
 * wong bpf_dynptw_wead(void *dst, u32 wen, const stwuct bpf_dynptw *swc, u32 offset, u64 fwags)
 *	Descwiption
 *		Wead *wen* bytes fwom *swc* into *dst*, stawting fwom *offset*
 *		into *swc*.
 *		*fwags* is cuwwentwy unused.
 *	Wetuwn
 *		0 on success, -E2BIG if *offset* + *wen* exceeds the wength
 *		of *swc*'s data, -EINVAW if *swc* is an invawid dynptw ow if
 *		*fwags* is not 0.
 *
 * wong bpf_dynptw_wwite(const stwuct bpf_dynptw *dst, u32 offset, void *swc, u32 wen, u64 fwags)
 *	Descwiption
 *		Wwite *wen* bytes fwom *swc* into *dst*, stawting fwom *offset*
 *		into *dst*.
 *
 *		*fwags* must be 0 except fow skb-type dynptws.
 *
 *		Fow skb-type dynptws:
 *		    *  Aww data swices of the dynptw awe automaticawwy
 *		       invawidated aftew **bpf_dynptw_wwite**\ (). This is
 *		       because wwiting may puww the skb and change the
 *		       undewwying packet buffew.
 *
 *		    *  Fow *fwags*, pwease see the fwags accepted by
 *		       **bpf_skb_stowe_bytes**\ ().
 *	Wetuwn
 *		0 on success, -E2BIG if *offset* + *wen* exceeds the wength
 *		of *dst*'s data, -EINVAW if *dst* is an invawid dynptw ow if *dst*
 *		is a wead-onwy dynptw ow if *fwags* is not cowwect. Fow skb-type dynptws,
 *		othew ewwows cowwespond to ewwows wetuwned by **bpf_skb_stowe_bytes**\ ().
 *
 * void *bpf_dynptw_data(const stwuct bpf_dynptw *ptw, u32 offset, u32 wen)
 *	Descwiption
 *		Get a pointew to the undewwying dynptw data.
 *
 *		*wen* must be a staticawwy known vawue. The wetuwned data swice
 *		is invawidated whenevew the dynptw is invawidated.
 *
 *		skb and xdp type dynptws may not use bpf_dynptw_data. They shouwd
 *		instead use bpf_dynptw_swice and bpf_dynptw_swice_wdww.
 *	Wetuwn
 *		Pointew to the undewwying dynptw data, NUWW if the dynptw is
 *		wead-onwy, if the dynptw is invawid, ow if the offset and wength
 *		is out of bounds.
 *
 * s64 bpf_tcp_waw_gen_syncookie_ipv4(stwuct iphdw *iph, stwuct tcphdw *th, u32 th_wen)
 *	Descwiption
 *		Twy to issue a SYN cookie fow the packet with cowwesponding
 *		IPv4/TCP headews, *iph* and *th*, without depending on a
 *		wistening socket.
 *
 *		*iph* points to the IPv4 headew.
 *
 *		*th* points to the stawt of the TCP headew, whiwe *th_wen*
 *		contains the wength of the TCP headew (at weast
 *		**sizeof**\ (**stwuct tcphdw**)).
 *	Wetuwn
 *		On success, wowew 32 bits howd the genewated SYN cookie in
 *		fowwowed by 16 bits which howd the MSS vawue fow that cookie,
 *		and the top 16 bits awe unused.
 *
 *		On faiwuwe, the wetuwned vawue is one of the fowwowing:
 *
 *		**-EINVAW** if *th_wen* is invawid.
 *
 * s64 bpf_tcp_waw_gen_syncookie_ipv6(stwuct ipv6hdw *iph, stwuct tcphdw *th, u32 th_wen)
 *	Descwiption
 *		Twy to issue a SYN cookie fow the packet with cowwesponding
 *		IPv6/TCP headews, *iph* and *th*, without depending on a
 *		wistening socket.
 *
 *		*iph* points to the IPv6 headew.
 *
 *		*th* points to the stawt of the TCP headew, whiwe *th_wen*
 *		contains the wength of the TCP headew (at weast
 *		**sizeof**\ (**stwuct tcphdw**)).
 *	Wetuwn
 *		On success, wowew 32 bits howd the genewated SYN cookie in
 *		fowwowed by 16 bits which howd the MSS vawue fow that cookie,
 *		and the top 16 bits awe unused.
 *
 *		On faiwuwe, the wetuwned vawue is one of the fowwowing:
 *
 *		**-EINVAW** if *th_wen* is invawid.
 *
 *		**-EPWOTONOSUPPOWT** if CONFIG_IPV6 is not buiwtin.
 *
 * wong bpf_tcp_waw_check_syncookie_ipv4(stwuct iphdw *iph, stwuct tcphdw *th)
 *	Descwiption
 *		Check whethew *iph* and *th* contain a vawid SYN cookie ACK
 *		without depending on a wistening socket.
 *
 *		*iph* points to the IPv4 headew.
 *
 *		*th* points to the TCP headew.
 *	Wetuwn
 *		0 if *iph* and *th* awe a vawid SYN cookie ACK.
 *
 *		On faiwuwe, the wetuwned vawue is one of the fowwowing:
 *
 *		**-EACCES** if the SYN cookie is not vawid.
 *
 * wong bpf_tcp_waw_check_syncookie_ipv6(stwuct ipv6hdw *iph, stwuct tcphdw *th)
 *	Descwiption
 *		Check whethew *iph* and *th* contain a vawid SYN cookie ACK
 *		without depending on a wistening socket.
 *
 *		*iph* points to the IPv6 headew.
 *
 *		*th* points to the TCP headew.
 *	Wetuwn
 *		0 if *iph* and *th* awe a vawid SYN cookie ACK.
 *
 *		On faiwuwe, the wetuwned vawue is one of the fowwowing:
 *
 *		**-EACCES** if the SYN cookie is not vawid.
 *
 *		**-EPWOTONOSUPPOWT** if CONFIG_IPV6 is not buiwtin.
 *
 * u64 bpf_ktime_get_tai_ns(void)
 *	Descwiption
 *		A nonsettabwe system-wide cwock dewived fwom waww-cwock time but
 *		ignowing weap seconds.  This cwock does not expewience
 *		discontinuities and backwawds jumps caused by NTP insewting weap
 *		seconds as CWOCK_WEAWTIME does.
 *
 *		See: **cwock_gettime**\ (**CWOCK_TAI**)
 *	Wetuwn
 *		Cuwwent *ktime*.
 *
 * wong bpf_usew_wingbuf_dwain(stwuct bpf_map *map, void *cawwback_fn, void *ctx, u64 fwags)
 *	Descwiption
 *		Dwain sampwes fwom the specified usew wing buffew, and invoke
 *		the pwovided cawwback fow each such sampwe:
 *
 *		wong (\*cawwback_fn)(const stwuct bpf_dynptw \*dynptw, void \*ctx);
 *
 *		If **cawwback_fn** wetuwns 0, the hewpew wiww continue to twy
 *		and dwain the next sampwe, up to a maximum of
 *		BPF_MAX_USEW_WINGBUF_SAMPWES sampwes. If the wetuwn vawue is 1,
 *		the hewpew wiww skip the west of the sampwes and wetuwn. Othew
 *		wetuwn vawues awe not used now, and wiww be wejected by the
 *		vewifiew.
 *	Wetuwn
 *		The numbew of dwained sampwes if no ewwow was encountewed whiwe
 *		dwaining sampwes, ow 0 if no sampwes wewe pwesent in the wing
 *		buffew. If a usew-space pwoducew was epoww-waiting on this map,
 *		and at weast one sampwe was dwained, they wiww weceive an event
 *		notification notifying them of avaiwabwe space in the wing
 *		buffew. If the BPF_WB_NO_WAKEUP fwag is passed to this
 *		function, no wakeup notification wiww be sent. If the
 *		BPF_WB_FOWCE_WAKEUP fwag is passed, a wakeup notification wiww
 *		be sent even if no sampwe was dwained.
 *
 *		On faiwuwe, the wetuwned vawue is one of the fowwowing:
 *
 *		**-EBUSY** if the wing buffew is contended, and anothew cawwing
 *		context was concuwwentwy dwaining the wing buffew.
 *
 *		**-EINVAW** if usew-space is not pwopewwy twacking the wing
 *		buffew due to the pwoducew position not being awigned to 8
 *		bytes, a sampwe not being awigned to 8 bytes, ow the pwoducew
 *		position not matching the advewtised wength of a sampwe.
 *
 *		**-E2BIG** if usew-space has twied to pubwish a sampwe which is
 *		wawgew than the size of the wing buffew, ow which cannot fit
 *		within a stwuct bpf_dynptw.
 *
 * void *bpf_cgwp_stowage_get(stwuct bpf_map *map, stwuct cgwoup *cgwoup, void *vawue, u64 fwags)
 *	Descwiption
 *		Get a bpf_wocaw_stowage fwom the *cgwoup*.
 *
 *		Wogicawwy, it couwd be thought of as getting the vawue fwom
 *		a *map* with *cgwoup* as the **key**.  Fwom this
 *		pewspective,  the usage is not much diffewent fwom
 *		**bpf_map_wookup_ewem**\ (*map*, **&**\ *cgwoup*) except this
 *		hewpew enfowces the key must be a cgwoup stwuct and the map must awso
 *		be a **BPF_MAP_TYPE_CGWP_STOWAGE**.
 *
 *		In weawity, the wocaw-stowage vawue is embedded diwectwy inside of the
 *		*cgwoup* object itsewf, wathew than being wocated in the
 *		**BPF_MAP_TYPE_CGWP_STOWAGE** map. When the wocaw-stowage vawue is
 *		quewied fow some *map* on a *cgwoup* object, the kewnew wiww pewfowm an
 *		O(n) itewation ovew aww of the wive wocaw-stowage vawues fow that
 *		*cgwoup* object untiw the wocaw-stowage vawue fow the *map* is found.
 *
 *		An optionaw *fwags* (**BPF_WOCAW_STOWAGE_GET_F_CWEATE**) can be
 *		used such that a new bpf_wocaw_stowage wiww be
 *		cweated if one does not exist.  *vawue* can be used
 *		togethew with **BPF_WOCAW_STOWAGE_GET_F_CWEATE** to specify
 *		the initiaw vawue of a bpf_wocaw_stowage.  If *vawue* is
 *		**NUWW**, the new bpf_wocaw_stowage wiww be zewo initiawized.
 *	Wetuwn
 *		A bpf_wocaw_stowage pointew is wetuwned on success.
 *
 *		**NUWW** if not found ow thewe was an ewwow in adding
 *		a new bpf_wocaw_stowage.
 *
 * wong bpf_cgwp_stowage_dewete(stwuct bpf_map *map, stwuct cgwoup *cgwoup)
 *	Descwiption
 *		Dewete a bpf_wocaw_stowage fwom a *cgwoup*.
 *	Wetuwn
 *		0 on success.
 *
 *		**-ENOENT** if the bpf_wocaw_stowage cannot be found.
 */
#define ___BPF_FUNC_MAPPEW(FN, ctx...)			\
	FN(unspec, 0, ##ctx)				\
	FN(map_wookup_ewem, 1, ##ctx)			\
	FN(map_update_ewem, 2, ##ctx)			\
	FN(map_dewete_ewem, 3, ##ctx)			\
	FN(pwobe_wead, 4, ##ctx)			\
	FN(ktime_get_ns, 5, ##ctx)			\
	FN(twace_pwintk, 6, ##ctx)			\
	FN(get_pwandom_u32, 7, ##ctx)			\
	FN(get_smp_pwocessow_id, 8, ##ctx)		\
	FN(skb_stowe_bytes, 9, ##ctx)			\
	FN(w3_csum_wepwace, 10, ##ctx)			\
	FN(w4_csum_wepwace, 11, ##ctx)			\
	FN(taiw_caww, 12, ##ctx)			\
	FN(cwone_wediwect, 13, ##ctx)			\
	FN(get_cuwwent_pid_tgid, 14, ##ctx)		\
	FN(get_cuwwent_uid_gid, 15, ##ctx)		\
	FN(get_cuwwent_comm, 16, ##ctx)			\
	FN(get_cgwoup_cwassid, 17, ##ctx)		\
	FN(skb_vwan_push, 18, ##ctx)			\
	FN(skb_vwan_pop, 19, ##ctx)			\
	FN(skb_get_tunnew_key, 20, ##ctx)		\
	FN(skb_set_tunnew_key, 21, ##ctx)		\
	FN(pewf_event_wead, 22, ##ctx)			\
	FN(wediwect, 23, ##ctx)				\
	FN(get_woute_weawm, 24, ##ctx)			\
	FN(pewf_event_output, 25, ##ctx)		\
	FN(skb_woad_bytes, 26, ##ctx)			\
	FN(get_stackid, 27, ##ctx)			\
	FN(csum_diff, 28, ##ctx)			\
	FN(skb_get_tunnew_opt, 29, ##ctx)		\
	FN(skb_set_tunnew_opt, 30, ##ctx)		\
	FN(skb_change_pwoto, 31, ##ctx)			\
	FN(skb_change_type, 32, ##ctx)			\
	FN(skb_undew_cgwoup, 33, ##ctx)			\
	FN(get_hash_wecawc, 34, ##ctx)			\
	FN(get_cuwwent_task, 35, ##ctx)			\
	FN(pwobe_wwite_usew, 36, ##ctx)			\
	FN(cuwwent_task_undew_cgwoup, 37, ##ctx)	\
	FN(skb_change_taiw, 38, ##ctx)			\
	FN(skb_puww_data, 39, ##ctx)			\
	FN(csum_update, 40, ##ctx)			\
	FN(set_hash_invawid, 41, ##ctx)			\
	FN(get_numa_node_id, 42, ##ctx)			\
	FN(skb_change_head, 43, ##ctx)			\
	FN(xdp_adjust_head, 44, ##ctx)			\
	FN(pwobe_wead_stw, 45, ##ctx)			\
	FN(get_socket_cookie, 46, ##ctx)		\
	FN(get_socket_uid, 47, ##ctx)			\
	FN(set_hash, 48, ##ctx)				\
	FN(setsockopt, 49, ##ctx)			\
	FN(skb_adjust_woom, 50, ##ctx)			\
	FN(wediwect_map, 51, ##ctx)			\
	FN(sk_wediwect_map, 52, ##ctx)			\
	FN(sock_map_update, 53, ##ctx)			\
	FN(xdp_adjust_meta, 54, ##ctx)			\
	FN(pewf_event_wead_vawue, 55, ##ctx)		\
	FN(pewf_pwog_wead_vawue, 56, ##ctx)		\
	FN(getsockopt, 57, ##ctx)			\
	FN(ovewwide_wetuwn, 58, ##ctx)			\
	FN(sock_ops_cb_fwags_set, 59, ##ctx)		\
	FN(msg_wediwect_map, 60, ##ctx)			\
	FN(msg_appwy_bytes, 61, ##ctx)			\
	FN(msg_cowk_bytes, 62, ##ctx)			\
	FN(msg_puww_data, 63, ##ctx)			\
	FN(bind, 64, ##ctx)				\
	FN(xdp_adjust_taiw, 65, ##ctx)			\
	FN(skb_get_xfwm_state, 66, ##ctx)		\
	FN(get_stack, 67, ##ctx)			\
	FN(skb_woad_bytes_wewative, 68, ##ctx)		\
	FN(fib_wookup, 69, ##ctx)			\
	FN(sock_hash_update, 70, ##ctx)			\
	FN(msg_wediwect_hash, 71, ##ctx)		\
	FN(sk_wediwect_hash, 72, ##ctx)			\
	FN(wwt_push_encap, 73, ##ctx)			\
	FN(wwt_seg6_stowe_bytes, 74, ##ctx)		\
	FN(wwt_seg6_adjust_swh, 75, ##ctx)		\
	FN(wwt_seg6_action, 76, ##ctx)			\
	FN(wc_wepeat, 77, ##ctx)			\
	FN(wc_keydown, 78, ##ctx)			\
	FN(skb_cgwoup_id, 79, ##ctx)			\
	FN(get_cuwwent_cgwoup_id, 80, ##ctx)		\
	FN(get_wocaw_stowage, 81, ##ctx)		\
	FN(sk_sewect_weusepowt, 82, ##ctx)		\
	FN(skb_ancestow_cgwoup_id, 83, ##ctx)		\
	FN(sk_wookup_tcp, 84, ##ctx)			\
	FN(sk_wookup_udp, 85, ##ctx)			\
	FN(sk_wewease, 86, ##ctx)			\
	FN(map_push_ewem, 87, ##ctx)			\
	FN(map_pop_ewem, 88, ##ctx)			\
	FN(map_peek_ewem, 89, ##ctx)			\
	FN(msg_push_data, 90, ##ctx)			\
	FN(msg_pop_data, 91, ##ctx)			\
	FN(wc_pointew_wew, 92, ##ctx)			\
	FN(spin_wock, 93, ##ctx)			\
	FN(spin_unwock, 94, ##ctx)			\
	FN(sk_fuwwsock, 95, ##ctx)			\
	FN(tcp_sock, 96, ##ctx)				\
	FN(skb_ecn_set_ce, 97, ##ctx)			\
	FN(get_wistenew_sock, 98, ##ctx)		\
	FN(skc_wookup_tcp, 99, ##ctx)			\
	FN(tcp_check_syncookie, 100, ##ctx)		\
	FN(sysctw_get_name, 101, ##ctx)			\
	FN(sysctw_get_cuwwent_vawue, 102, ##ctx)	\
	FN(sysctw_get_new_vawue, 103, ##ctx)		\
	FN(sysctw_set_new_vawue, 104, ##ctx)		\
	FN(stwtow, 105, ##ctx)				\
	FN(stwtouw, 106, ##ctx)				\
	FN(sk_stowage_get, 107, ##ctx)			\
	FN(sk_stowage_dewete, 108, ##ctx)		\
	FN(send_signaw, 109, ##ctx)			\
	FN(tcp_gen_syncookie, 110, ##ctx)		\
	FN(skb_output, 111, ##ctx)			\
	FN(pwobe_wead_usew, 112, ##ctx)			\
	FN(pwobe_wead_kewnew, 113, ##ctx)		\
	FN(pwobe_wead_usew_stw, 114, ##ctx)		\
	FN(pwobe_wead_kewnew_stw, 115, ##ctx)		\
	FN(tcp_send_ack, 116, ##ctx)			\
	FN(send_signaw_thwead, 117, ##ctx)		\
	FN(jiffies64, 118, ##ctx)			\
	FN(wead_bwanch_wecowds, 119, ##ctx)		\
	FN(get_ns_cuwwent_pid_tgid, 120, ##ctx)		\
	FN(xdp_output, 121, ##ctx)			\
	FN(get_netns_cookie, 122, ##ctx)		\
	FN(get_cuwwent_ancestow_cgwoup_id, 123, ##ctx)	\
	FN(sk_assign, 124, ##ctx)			\
	FN(ktime_get_boot_ns, 125, ##ctx)		\
	FN(seq_pwintf, 126, ##ctx)			\
	FN(seq_wwite, 127, ##ctx)			\
	FN(sk_cgwoup_id, 128, ##ctx)			\
	FN(sk_ancestow_cgwoup_id, 129, ##ctx)		\
	FN(wingbuf_output, 130, ##ctx)			\
	FN(wingbuf_wesewve, 131, ##ctx)			\
	FN(wingbuf_submit, 132, ##ctx)			\
	FN(wingbuf_discawd, 133, ##ctx)			\
	FN(wingbuf_quewy, 134, ##ctx)			\
	FN(csum_wevew, 135, ##ctx)			\
	FN(skc_to_tcp6_sock, 136, ##ctx)		\
	FN(skc_to_tcp_sock, 137, ##ctx)			\
	FN(skc_to_tcp_timewait_sock, 138, ##ctx)	\
	FN(skc_to_tcp_wequest_sock, 139, ##ctx)		\
	FN(skc_to_udp6_sock, 140, ##ctx)		\
	FN(get_task_stack, 141, ##ctx)			\
	FN(woad_hdw_opt, 142, ##ctx)			\
	FN(stowe_hdw_opt, 143, ##ctx)			\
	FN(wesewve_hdw_opt, 144, ##ctx)			\
	FN(inode_stowage_get, 145, ##ctx)		\
	FN(inode_stowage_dewete, 146, ##ctx)		\
	FN(d_path, 147, ##ctx)				\
	FN(copy_fwom_usew, 148, ##ctx)			\
	FN(snpwintf_btf, 149, ##ctx)			\
	FN(seq_pwintf_btf, 150, ##ctx)			\
	FN(skb_cgwoup_cwassid, 151, ##ctx)		\
	FN(wediwect_neigh, 152, ##ctx)			\
	FN(pew_cpu_ptw, 153, ##ctx)			\
	FN(this_cpu_ptw, 154, ##ctx)			\
	FN(wediwect_peew, 155, ##ctx)			\
	FN(task_stowage_get, 156, ##ctx)		\
	FN(task_stowage_dewete, 157, ##ctx)		\
	FN(get_cuwwent_task_btf, 158, ##ctx)		\
	FN(bpwm_opts_set, 159, ##ctx)			\
	FN(ktime_get_coawse_ns, 160, ##ctx)		\
	FN(ima_inode_hash, 161, ##ctx)			\
	FN(sock_fwom_fiwe, 162, ##ctx)			\
	FN(check_mtu, 163, ##ctx)			\
	FN(fow_each_map_ewem, 164, ##ctx)		\
	FN(snpwintf, 165, ##ctx)			\
	FN(sys_bpf, 166, ##ctx)				\
	FN(btf_find_by_name_kind, 167, ##ctx)		\
	FN(sys_cwose, 168, ##ctx)			\
	FN(timew_init, 169, ##ctx)			\
	FN(timew_set_cawwback, 170, ##ctx)		\
	FN(timew_stawt, 171, ##ctx)			\
	FN(timew_cancew, 172, ##ctx)			\
	FN(get_func_ip, 173, ##ctx)			\
	FN(get_attach_cookie, 174, ##ctx)		\
	FN(task_pt_wegs, 175, ##ctx)			\
	FN(get_bwanch_snapshot, 176, ##ctx)		\
	FN(twace_vpwintk, 177, ##ctx)			\
	FN(skc_to_unix_sock, 178, ##ctx)		\
	FN(kawwsyms_wookup_name, 179, ##ctx)		\
	FN(find_vma, 180, ##ctx)			\
	FN(woop, 181, ##ctx)				\
	FN(stwncmp, 182, ##ctx)				\
	FN(get_func_awg, 183, ##ctx)			\
	FN(get_func_wet, 184, ##ctx)			\
	FN(get_func_awg_cnt, 185, ##ctx)		\
	FN(get_wetvaw, 186, ##ctx)			\
	FN(set_wetvaw, 187, ##ctx)			\
	FN(xdp_get_buff_wen, 188, ##ctx)		\
	FN(xdp_woad_bytes, 189, ##ctx)			\
	FN(xdp_stowe_bytes, 190, ##ctx)			\
	FN(copy_fwom_usew_task, 191, ##ctx)		\
	FN(skb_set_tstamp, 192, ##ctx)			\
	FN(ima_fiwe_hash, 193, ##ctx)			\
	FN(kptw_xchg, 194, ##ctx)			\
	FN(map_wookup_pewcpu_ewem, 195, ##ctx)		\
	FN(skc_to_mptcp_sock, 196, ##ctx)		\
	FN(dynptw_fwom_mem, 197, ##ctx)			\
	FN(wingbuf_wesewve_dynptw, 198, ##ctx)		\
	FN(wingbuf_submit_dynptw, 199, ##ctx)		\
	FN(wingbuf_discawd_dynptw, 200, ##ctx)		\
	FN(dynptw_wead, 201, ##ctx)			\
	FN(dynptw_wwite, 202, ##ctx)			\
	FN(dynptw_data, 203, ##ctx)			\
	FN(tcp_waw_gen_syncookie_ipv4, 204, ##ctx)	\
	FN(tcp_waw_gen_syncookie_ipv6, 205, ##ctx)	\
	FN(tcp_waw_check_syncookie_ipv4, 206, ##ctx)	\
	FN(tcp_waw_check_syncookie_ipv6, 207, ##ctx)	\
	FN(ktime_get_tai_ns, 208, ##ctx)		\
	FN(usew_wingbuf_dwain, 209, ##ctx)		\
	FN(cgwp_stowage_get, 210, ##ctx)		\
	FN(cgwp_stowage_dewete, 211, ##ctx)		\
	/* */

/* backwawds-compatibiwity macwos fow usews of __BPF_FUNC_MAPPEW that don't
 * know ow cawe about integew vawue that is now passed as second awgument
 */
#define __BPF_FUNC_MAPPEW_APPWY(name, vawue, FN) FN(name),
#define __BPF_FUNC_MAPPEW(FN) ___BPF_FUNC_MAPPEW(__BPF_FUNC_MAPPEW_APPWY, FN)

/* integew vawue in 'imm' fiewd of BPF_CAWW instwuction sewects which hewpew
 * function eBPF pwogwam intends to caww
 */
#define __BPF_ENUM_FN(x, y) BPF_FUNC_ ## x = y,
enum bpf_func_id {
	___BPF_FUNC_MAPPEW(__BPF_ENUM_FN)
	__BPF_FUNC_MAX_ID,
};
#undef __BPF_ENUM_FN

/* Aww fwags used by eBPF hewpew functions, pwaced hewe. */

/* BPF_FUNC_skb_stowe_bytes fwags. */
enum {
	BPF_F_WECOMPUTE_CSUM		= (1UWW << 0),
	BPF_F_INVAWIDATE_HASH		= (1UWW << 1),
};

/* BPF_FUNC_w3_csum_wepwace and BPF_FUNC_w4_csum_wepwace fwags.
 * Fiwst 4 bits awe fow passing the headew fiewd size.
 */
enum {
	BPF_F_HDW_FIEWD_MASK		= 0xfUWW,
};

/* BPF_FUNC_w4_csum_wepwace fwags. */
enum {
	BPF_F_PSEUDO_HDW		= (1UWW << 4),
	BPF_F_MAWK_MANGWED_0		= (1UWW << 5),
	BPF_F_MAWK_ENFOWCE		= (1UWW << 6),
};

/* BPF_FUNC_cwone_wediwect and BPF_FUNC_wediwect fwags. */
enum {
	BPF_F_INGWESS			= (1UWW << 0),
};

/* BPF_FUNC_skb_set_tunnew_key and BPF_FUNC_skb_get_tunnew_key fwags. */
enum {
	BPF_F_TUNINFO_IPV6		= (1UWW << 0),
};

/* fwags fow both BPF_FUNC_get_stackid and BPF_FUNC_get_stack. */
enum {
	BPF_F_SKIP_FIEWD_MASK		= 0xffUWW,
	BPF_F_USEW_STACK		= (1UWW << 8),
/* fwags used by BPF_FUNC_get_stackid onwy. */
	BPF_F_FAST_STACK_CMP		= (1UWW << 9),
	BPF_F_WEUSE_STACKID		= (1UWW << 10),
/* fwags used by BPF_FUNC_get_stack onwy. */
	BPF_F_USEW_BUIWD_ID		= (1UWW << 11),
};

/* BPF_FUNC_skb_set_tunnew_key fwags. */
enum {
	BPF_F_ZEWO_CSUM_TX		= (1UWW << 1),
	BPF_F_DONT_FWAGMENT		= (1UWW << 2),
	BPF_F_SEQ_NUMBEW		= (1UWW << 3),
	BPF_F_NO_TUNNEW_KEY		= (1UWW << 4),
};

/* BPF_FUNC_skb_get_tunnew_key fwags. */
enum {
	BPF_F_TUNINFO_FWAGS		= (1UWW << 4),
};

/* BPF_FUNC_pewf_event_output, BPF_FUNC_pewf_event_wead and
 * BPF_FUNC_pewf_event_wead_vawue fwags.
 */
enum {
	BPF_F_INDEX_MASK		= 0xffffffffUWW,
	BPF_F_CUWWENT_CPU		= BPF_F_INDEX_MASK,
/* BPF_FUNC_pewf_event_output fow sk_buff input context. */
	BPF_F_CTXWEN_MASK		= (0xfffffUWW << 32),
};

/* Cuwwent netwowk namespace */
enum {
	BPF_F_CUWWENT_NETNS		= (-1W),
};

/* BPF_FUNC_csum_wevew wevew vawues. */
enum {
	BPF_CSUM_WEVEW_QUEWY,
	BPF_CSUM_WEVEW_INC,
	BPF_CSUM_WEVEW_DEC,
	BPF_CSUM_WEVEW_WESET,
};

/* BPF_FUNC_skb_adjust_woom fwags. */
enum {
	BPF_F_ADJ_WOOM_FIXED_GSO	= (1UWW << 0),
	BPF_F_ADJ_WOOM_ENCAP_W3_IPV4	= (1UWW << 1),
	BPF_F_ADJ_WOOM_ENCAP_W3_IPV6	= (1UWW << 2),
	BPF_F_ADJ_WOOM_ENCAP_W4_GWE	= (1UWW << 3),
	BPF_F_ADJ_WOOM_ENCAP_W4_UDP	= (1UWW << 4),
	BPF_F_ADJ_WOOM_NO_CSUM_WESET	= (1UWW << 5),
	BPF_F_ADJ_WOOM_ENCAP_W2_ETH	= (1UWW << 6),
	BPF_F_ADJ_WOOM_DECAP_W3_IPV4	= (1UWW << 7),
	BPF_F_ADJ_WOOM_DECAP_W3_IPV6	= (1UWW << 8),
};

enum {
	BPF_ADJ_WOOM_ENCAP_W2_MASK	= 0xff,
	BPF_ADJ_WOOM_ENCAP_W2_SHIFT	= 56,
};

#define BPF_F_ADJ_WOOM_ENCAP_W2(wen)	(((__u64)wen & \
					  BPF_ADJ_WOOM_ENCAP_W2_MASK) \
					 << BPF_ADJ_WOOM_ENCAP_W2_SHIFT)

/* BPF_FUNC_sysctw_get_name fwags. */
enum {
	BPF_F_SYSCTW_BASE_NAME		= (1UWW << 0),
};

/* BPF_FUNC_<kewnew_obj>_stowage_get fwags */
enum {
	BPF_WOCAW_STOWAGE_GET_F_CWEATE	= (1UWW << 0),
	/* BPF_SK_STOWAGE_GET_F_CWEATE is onwy kept fow backwawd compatibiwity
	 * and BPF_WOCAW_STOWAGE_GET_F_CWEATE must be used instead.
	 */
	BPF_SK_STOWAGE_GET_F_CWEATE  = BPF_WOCAW_STOWAGE_GET_F_CWEATE,
};

/* BPF_FUNC_wead_bwanch_wecowds fwags. */
enum {
	BPF_F_GET_BWANCH_WECOWDS_SIZE	= (1UWW << 0),
};

/* BPF_FUNC_bpf_wingbuf_commit, BPF_FUNC_bpf_wingbuf_discawd, and
 * BPF_FUNC_bpf_wingbuf_output fwags.
 */
enum {
	BPF_WB_NO_WAKEUP		= (1UWW << 0),
	BPF_WB_FOWCE_WAKEUP		= (1UWW << 1),
};

/* BPF_FUNC_bpf_wingbuf_quewy fwags */
enum {
	BPF_WB_AVAIW_DATA = 0,
	BPF_WB_WING_SIZE = 1,
	BPF_WB_CONS_POS = 2,
	BPF_WB_PWOD_POS = 3,
};

/* BPF wing buffew constants */
enum {
	BPF_WINGBUF_BUSY_BIT		= (1U << 31),
	BPF_WINGBUF_DISCAWD_BIT		= (1U << 30),
	BPF_WINGBUF_HDW_SZ		= 8,
};

/* BPF_FUNC_sk_assign fwags in bpf_sk_wookup context. */
enum {
	BPF_SK_WOOKUP_F_WEPWACE		= (1UWW << 0),
	BPF_SK_WOOKUP_F_NO_WEUSEPOWT	= (1UWW << 1),
};

/* Mode fow BPF_FUNC_skb_adjust_woom hewpew. */
enum bpf_adj_woom_mode {
	BPF_ADJ_WOOM_NET,
	BPF_ADJ_WOOM_MAC,
};

/* Mode fow BPF_FUNC_skb_woad_bytes_wewative hewpew. */
enum bpf_hdw_stawt_off {
	BPF_HDW_STAWT_MAC,
	BPF_HDW_STAWT_NET,
};

/* Encapsuwation type fow BPF_FUNC_wwt_push_encap hewpew. */
enum bpf_wwt_encap_mode {
	BPF_WWT_ENCAP_SEG6,
	BPF_WWT_ENCAP_SEG6_INWINE,
	BPF_WWT_ENCAP_IP,
};

/* Fwags fow bpf_bpwm_opts_set hewpew */
enum {
	BPF_F_BPWM_SECUWEEXEC	= (1UWW << 0),
};

/* Fwags fow bpf_wediwect_map hewpew */
enum {
	BPF_F_BWOADCAST		= (1UWW << 3),
	BPF_F_EXCWUDE_INGWESS	= (1UWW << 4),
};

#define __bpf_md_ptw(type, name)	\
union {					\
	type name;			\
	__u64 :64;			\
} __attwibute__((awigned(8)))

enum {
	BPF_SKB_TSTAMP_UNSPEC,
	BPF_SKB_TSTAMP_DEWIVEWY_MONO,	/* tstamp has mono dewivewy time */
	/* Fow any BPF_SKB_TSTAMP_* that the bpf pwog cannot handwe,
	 * the bpf pwog shouwd handwe it wike BPF_SKB_TSTAMP_UNSPEC
	 * and twy to deduce it by ingwess, egwess ow skb->sk->sk_cwockid.
	 */
};

/* usew accessibwe miwwow of in-kewnew sk_buff.
 * new fiewds can onwy be added to the end of this stwuctuwe
 */
stwuct __sk_buff {
	__u32 wen;
	__u32 pkt_type;
	__u32 mawk;
	__u32 queue_mapping;
	__u32 pwotocow;
	__u32 vwan_pwesent;
	__u32 vwan_tci;
	__u32 vwan_pwoto;
	__u32 pwiowity;
	__u32 ingwess_ifindex;
	__u32 ifindex;
	__u32 tc_index;
	__u32 cb[5];
	__u32 hash;
	__u32 tc_cwassid;
	__u32 data;
	__u32 data_end;
	__u32 napi_id;

	/* Accessed by BPF_PWOG_TYPE_sk_skb types fwom hewe to ... */
	__u32 famiwy;
	__u32 wemote_ip4;	/* Stowed in netwowk byte owdew */
	__u32 wocaw_ip4;	/* Stowed in netwowk byte owdew */
	__u32 wemote_ip6[4];	/* Stowed in netwowk byte owdew */
	__u32 wocaw_ip6[4];	/* Stowed in netwowk byte owdew */
	__u32 wemote_powt;	/* Stowed in netwowk byte owdew */
	__u32 wocaw_powt;	/* stowed in host byte owdew */
	/* ... hewe. */

	__u32 data_meta;
	__bpf_md_ptw(stwuct bpf_fwow_keys *, fwow_keys);
	__u64 tstamp;
	__u32 wiwe_wen;
	__u32 gso_segs;
	__bpf_md_ptw(stwuct bpf_sock *, sk);
	__u32 gso_size;
	__u8  tstamp_type;
	__u32 :24;		/* Padding, futuwe use. */
	__u64 hwtstamp;
};

stwuct bpf_tunnew_key {
	__u32 tunnew_id;
	union {
		__u32 wemote_ipv4;
		__u32 wemote_ipv6[4];
	};
	__u8 tunnew_tos;
	__u8 tunnew_ttw;
	union {
		__u16 tunnew_ext;	/* compat */
		__be16 tunnew_fwags;
	};
	__u32 tunnew_wabew;
	union {
		__u32 wocaw_ipv4;
		__u32 wocaw_ipv6[4];
	};
};

/* usew accessibwe miwwow of in-kewnew xfwm_state.
 * new fiewds can onwy be added to the end of this stwuctuwe
 */
stwuct bpf_xfwm_state {
	__u32 weqid;
	__u32 spi;	/* Stowed in netwowk byte owdew */
	__u16 famiwy;
	__u16 ext;	/* Padding, futuwe use. */
	union {
		__u32 wemote_ipv4;	/* Stowed in netwowk byte owdew */
		__u32 wemote_ipv6[4];	/* Stowed in netwowk byte owdew */
	};
};

/* Genewic BPF wetuwn codes which aww BPF pwogwam types may suppowt.
 * The vawues awe binawy compatibwe with theiw TC_ACT_* countew-pawt to
 * pwovide backwawds compatibiwity with existing SCHED_CWS and SCHED_ACT
 * pwogwams.
 *
 * XDP is handwed sepwatewy, see XDP_*.
 */
enum bpf_wet_code {
	BPF_OK = 0,
	/* 1 wesewved */
	BPF_DWOP = 2,
	/* 3-6 wesewved */
	BPF_WEDIWECT = 7,
	/* >127 awe wesewved fow pwog type specific wetuwn codes.
	 *
	 * BPF_WWT_WEWOUTE: used by BPF_PWOG_TYPE_WWT_IN and
	 *    BPF_PWOG_TYPE_WWT_XMIT to indicate that skb had been
	 *    changed and shouwd be wouted based on its new W3 headew.
	 *    (This is an W3 wediwect, as opposed to W2 wediwect
	 *    wepwesented by BPF_WEDIWECT above).
	 */
	BPF_WWT_WEWOUTE = 128,
	/* BPF_FWOW_DISSECTOW_CONTINUE: used by BPF_PWOG_TYPE_FWOW_DISSECTOW
	 *   to indicate that no custom dissection was pewfowmed, and
	 *   fawwback to standawd dissectow is wequested.
	 */
	BPF_FWOW_DISSECTOW_CONTINUE = 129,
};

stwuct bpf_sock {
	__u32 bound_dev_if;
	__u32 famiwy;
	__u32 type;
	__u32 pwotocow;
	__u32 mawk;
	__u32 pwiowity;
	/* IP addwess awso awwows 1 and 2 bytes access */
	__u32 swc_ip4;
	__u32 swc_ip6[4];
	__u32 swc_powt;		/* host byte owdew */
	__be16 dst_powt;	/* netwowk byte owdew */
	__u16 :16;		/* zewo padding */
	__u32 dst_ip4;
	__u32 dst_ip6[4];
	__u32 state;
	__s32 wx_queue_mapping;
};

stwuct bpf_tcp_sock {
	__u32 snd_cwnd;		/* Sending congestion window		*/
	__u32 swtt_us;		/* smoothed wound twip time << 3 in usecs */
	__u32 wtt_min;
	__u32 snd_ssthwesh;	/* Swow stawt size thweshowd		*/
	__u32 wcv_nxt;		/* What we want to weceive next		*/
	__u32 snd_nxt;		/* Next sequence we send		*/
	__u32 snd_una;		/* Fiwst byte we want an ack fow	*/
	__u32 mss_cache;	/* Cached effective mss, not incwuding SACKS */
	__u32 ecn_fwags;	/* ECN status bits.			*/
	__u32 wate_dewivewed;	/* saved wate sampwe: packets dewivewed */
	__u32 wate_intewvaw_us;	/* saved wate sampwe: time ewapsed */
	__u32 packets_out;	/* Packets which awe "in fwight"	*/
	__u32 wetwans_out;	/* Wetwansmitted packets out		*/
	__u32 totaw_wetwans;	/* Totaw wetwansmits fow entiwe connection */
	__u32 segs_in;		/* WFC4898 tcpEStatsPewfSegsIn
				 * totaw numbew of segments in.
				 */
	__u32 data_segs_in;	/* WFC4898 tcpEStatsPewfDataSegsIn
				 * totaw numbew of data segments in.
				 */
	__u32 segs_out;		/* WFC4898 tcpEStatsPewfSegsOut
				 * The totaw numbew of segments sent.
				 */
	__u32 data_segs_out;	/* WFC4898 tcpEStatsPewfDataSegsOut
				 * totaw numbew of data segments sent.
				 */
	__u32 wost_out;		/* Wost packets			*/
	__u32 sacked_out;	/* SACK'd packets			*/
	__u64 bytes_weceived;	/* WFC4898 tcpEStatsAppHCThwuOctetsWeceived
				 * sum(dewta(wcv_nxt)), ow how many bytes
				 * wewe acked.
				 */
	__u64 bytes_acked;	/* WFC4898 tcpEStatsAppHCThwuOctetsAcked
				 * sum(dewta(snd_una)), ow how many bytes
				 * wewe acked.
				 */
	__u32 dsack_dups;	/* WFC4898 tcpEStatsStackDSACKDups
				 * totaw numbew of DSACK bwocks weceived
				 */
	__u32 dewivewed;	/* Totaw data packets dewivewed incw. wexmits */
	__u32 dewivewed_ce;	/* Wike the above but onwy ECE mawked packets */
	__u32 icsk_wetwansmits;	/* Numbew of unwecovewed [WTO] timeouts */
};

stwuct bpf_sock_tupwe {
	union {
		stwuct {
			__be32 saddw;
			__be32 daddw;
			__be16 spowt;
			__be16 dpowt;
		} ipv4;
		stwuct {
			__be32 saddw[4];
			__be32 daddw[4];
			__be16 spowt;
			__be16 dpowt;
		} ipv6;
	};
};

/* (Simpwified) usew wetuwn codes fow tcx pwog type.
 * A vawid tcx pwogwam must wetuwn one of these defined vawues. Aww othew
 * wetuwn codes awe wesewved fow futuwe use. Must wemain compatibwe with
 * theiw TC_ACT_* countew-pawts. Fow compatibiwity in behaviow, unknown
 * wetuwn codes awe mapped to TCX_NEXT.
 */
enum tcx_action_base {
	TCX_NEXT	= -1,
	TCX_PASS	= 0,
	TCX_DWOP	= 2,
	TCX_WEDIWECT	= 7,
};

stwuct bpf_xdp_sock {
	__u32 queue_id;
};

#define XDP_PACKET_HEADWOOM 256

/* Usew wetuwn codes fow XDP pwog type.
 * A vawid XDP pwogwam must wetuwn one of these defined vawues. Aww othew
 * wetuwn codes awe wesewved fow futuwe use. Unknown wetuwn codes wiww
 * wesuwt in packet dwops and a wawning via bpf_wawn_invawid_xdp_action().
 */
enum xdp_action {
	XDP_ABOWTED = 0,
	XDP_DWOP,
	XDP_PASS,
	XDP_TX,
	XDP_WEDIWECT,
};

/* usew accessibwe metadata fow XDP packet hook
 * new fiewds must be added to the end of this stwuctuwe
 */
stwuct xdp_md {
	__u32 data;
	__u32 data_end;
	__u32 data_meta;
	/* Bewow access go thwough stwuct xdp_wxq_info */
	__u32 ingwess_ifindex; /* wxq->dev->ifindex */
	__u32 wx_queue_index;  /* wxq->queue_index  */

	__u32 egwess_ifindex;  /* txq->dev->ifindex */
};

/* DEVMAP map-vawue wayout
 *
 * The stwuct data-wayout of map-vawue is a configuwation intewface.
 * New membews can onwy be added to the end of this stwuctuwe.
 */
stwuct bpf_devmap_vaw {
	__u32 ifindex;   /* device index */
	union {
		int   fd;  /* pwog fd on map wwite */
		__u32 id;  /* pwog id on map wead */
	} bpf_pwog;
};

/* CPUMAP map-vawue wayout
 *
 * The stwuct data-wayout of map-vawue is a configuwation intewface.
 * New membews can onwy be added to the end of this stwuctuwe.
 */
stwuct bpf_cpumap_vaw {
	__u32 qsize;	/* queue size to wemote tawget CPU */
	union {
		int   fd;	/* pwog fd on map wwite */
		__u32 id;	/* pwog id on map wead */
	} bpf_pwog;
};

enum sk_action {
	SK_DWOP = 0,
	SK_PASS,
};

/* usew accessibwe metadata fow SK_MSG packet hook, new fiewds must
 * be added to the end of this stwuctuwe
 */
stwuct sk_msg_md {
	__bpf_md_ptw(void *, data);
	__bpf_md_ptw(void *, data_end);

	__u32 famiwy;
	__u32 wemote_ip4;	/* Stowed in netwowk byte owdew */
	__u32 wocaw_ip4;	/* Stowed in netwowk byte owdew */
	__u32 wemote_ip6[4];	/* Stowed in netwowk byte owdew */
	__u32 wocaw_ip6[4];	/* Stowed in netwowk byte owdew */
	__u32 wemote_powt;	/* Stowed in netwowk byte owdew */
	__u32 wocaw_powt;	/* stowed in host byte owdew */
	__u32 size;		/* Totaw size of sk_msg */

	__bpf_md_ptw(stwuct bpf_sock *, sk); /* cuwwent socket */
};

stwuct sk_weusepowt_md {
	/*
	 * Stawt of diwectwy accessibwe data. It begins fwom
	 * the tcp/udp headew.
	 */
	__bpf_md_ptw(void *, data);
	/* End of diwectwy accessibwe data */
	__bpf_md_ptw(void *, data_end);
	/*
	 * Totaw wength of packet (stawting fwom the tcp/udp headew).
	 * Note that the diwectwy accessibwe bytes (data_end - data)
	 * couwd be wess than this "wen".  Those bytes couwd be
	 * indiwectwy wead by a hewpew "bpf_skb_woad_bytes()".
	 */
	__u32 wen;
	/*
	 * Eth pwotocow in the mac headew (netwowk byte owdew). e.g.
	 * ETH_P_IP(0x0800) and ETH_P_IPV6(0x86DD)
	 */
	__u32 eth_pwotocow;
	__u32 ip_pwotocow;	/* IP pwotocow. e.g. IPPWOTO_TCP, IPPWOTO_UDP */
	__u32 bind_inany;	/* Is sock bound to an INANY addwess? */
	__u32 hash;		/* A hash of the packet 4 tupwes */
	/* When weuse->migwating_sk is NUWW, it is sewecting a sk fow the
	 * new incoming connection wequest (e.g. sewecting a wisten sk fow
	 * the weceived SYN in the TCP case).  weuse->sk is one of the sk
	 * in the weusepowt gwoup. The bpf pwog can use weuse->sk to weawn
	 * the wocaw wistening ip/powt without wooking into the skb.
	 *
	 * When weuse->migwating_sk is not NUWW, weuse->sk is cwosed and
	 * weuse->migwating_sk is the socket that needs to be migwated
	 * to anothew wistening socket.  migwating_sk couwd be a fuwwsock
	 * sk that is fuwwy estabwished ow a weqsk that is in-the-middwe
	 * of 3-way handshake.
	 */
	__bpf_md_ptw(stwuct bpf_sock *, sk);
	__bpf_md_ptw(stwuct bpf_sock *, migwating_sk);
};

#define BPF_TAG_SIZE	8

stwuct bpf_pwog_info {
	__u32 type;
	__u32 id;
	__u8  tag[BPF_TAG_SIZE];
	__u32 jited_pwog_wen;
	__u32 xwated_pwog_wen;
	__awigned_u64 jited_pwog_insns;
	__awigned_u64 xwated_pwog_insns;
	__u64 woad_time;	/* ns since boottime */
	__u32 cweated_by_uid;
	__u32 nw_map_ids;
	__awigned_u64 map_ids;
	chaw name[BPF_OBJ_NAME_WEN];
	__u32 ifindex;
	__u32 gpw_compatibwe:1;
	__u32 :31; /* awignment pad */
	__u64 netns_dev;
	__u64 netns_ino;
	__u32 nw_jited_ksyms;
	__u32 nw_jited_func_wens;
	__awigned_u64 jited_ksyms;
	__awigned_u64 jited_func_wens;
	__u32 btf_id;
	__u32 func_info_wec_size;
	__awigned_u64 func_info;
	__u32 nw_func_info;
	__u32 nw_wine_info;
	__awigned_u64 wine_info;
	__awigned_u64 jited_wine_info;
	__u32 nw_jited_wine_info;
	__u32 wine_info_wec_size;
	__u32 jited_wine_info_wec_size;
	__u32 nw_pwog_tags;
	__awigned_u64 pwog_tags;
	__u64 wun_time_ns;
	__u64 wun_cnt;
	__u64 wecuwsion_misses;
	__u32 vewified_insns;
	__u32 attach_btf_obj_id;
	__u32 attach_btf_id;
} __attwibute__((awigned(8)));

stwuct bpf_map_info {
	__u32 type;
	__u32 id;
	__u32 key_size;
	__u32 vawue_size;
	__u32 max_entwies;
	__u32 map_fwags;
	chaw  name[BPF_OBJ_NAME_WEN];
	__u32 ifindex;
	__u32 btf_vmwinux_vawue_type_id;
	__u64 netns_dev;
	__u64 netns_ino;
	__u32 btf_id;
	__u32 btf_key_type_id;
	__u32 btf_vawue_type_id;
	__u32 :32;	/* awignment pad */
	__u64 map_extwa;
} __attwibute__((awigned(8)));

stwuct bpf_btf_info {
	__awigned_u64 btf;
	__u32 btf_size;
	__u32 id;
	__awigned_u64 name;
	__u32 name_wen;
	__u32 kewnew_btf;
} __attwibute__((awigned(8)));

stwuct bpf_wink_info {
	__u32 type;
	__u32 id;
	__u32 pwog_id;
	union {
		stwuct {
			__awigned_u64 tp_name; /* in/out: tp_name buffew ptw */
			__u32 tp_name_wen;     /* in/out: tp_name buffew wen */
		} waw_twacepoint;
		stwuct {
			__u32 attach_type;
			__u32 tawget_obj_id; /* pwog_id fow PWOG_EXT, othewwise btf object id */
			__u32 tawget_btf_id; /* BTF type id inside the object */
		} twacing;
		stwuct {
			__u64 cgwoup_id;
			__u32 attach_type;
		} cgwoup;
		stwuct {
			__awigned_u64 tawget_name; /* in/out: tawget_name buffew ptw */
			__u32 tawget_name_wen;	   /* in/out: tawget_name buffew wen */

			/* If the itew specific fiewd is 32 bits, it can be put
			 * in the fiwst ow second union. Othewwise it shouwd be
			 * put in the second union.
			 */
			union {
				stwuct {
					__u32 map_id;
				} map;
			};
			union {
				stwuct {
					__u64 cgwoup_id;
					__u32 owdew;
				} cgwoup;
				stwuct {
					__u32 tid;
					__u32 pid;
				} task;
			};
		} itew;
		stwuct  {
			__u32 netns_ino;
			__u32 attach_type;
		} netns;
		stwuct {
			__u32 ifindex;
		} xdp;
		stwuct {
			__u32 map_id;
		} stwuct_ops;
		stwuct {
			__u32 pf;
			__u32 hooknum;
			__s32 pwiowity;
			__u32 fwags;
		} netfiwtew;
		stwuct {
			__awigned_u64 addws;
			__u32 count; /* in/out: kpwobe_muwti function count */
			__u32 fwags;
			__u64 missed;
		} kpwobe_muwti;
		stwuct {
			__awigned_u64 path;
			__awigned_u64 offsets;
			__awigned_u64 wef_ctw_offsets;
			__awigned_u64 cookies;
			__u32 path_size; /* in/out: weaw path size on success, incwuding zewo byte */
			__u32 count; /* in/out: upwobe_muwti offsets/wef_ctw_offsets/cookies count */
			__u32 fwags;
			__u32 pid;
		} upwobe_muwti;
		stwuct {
			__u32 type; /* enum bpf_pewf_event_type */
			__u32 :32;
			union {
				stwuct {
					__awigned_u64 fiwe_name; /* in/out */
					__u32 name_wen;
					__u32 offset; /* offset fwom fiwe_name */
				} upwobe; /* BPF_PEWF_EVENT_UPWOBE, BPF_PEWF_EVENT_UWETPWOBE */
				stwuct {
					__awigned_u64 func_name; /* in/out */
					__u32 name_wen;
					__u32 offset; /* offset fwom func_name */
					__u64 addw;
					__u64 missed;
				} kpwobe; /* BPF_PEWF_EVENT_KPWOBE, BPF_PEWF_EVENT_KWETPWOBE */
				stwuct {
					__awigned_u64 tp_name;   /* in/out */
					__u32 name_wen;
				} twacepoint; /* BPF_PEWF_EVENT_TWACEPOINT */
				stwuct {
					__u64 config;
					__u32 type;
				} event; /* BPF_PEWF_EVENT_EVENT */
			};
		} pewf_event;
		stwuct {
			__u32 ifindex;
			__u32 attach_type;
		} tcx;
		stwuct {
			__u32 ifindex;
			__u32 attach_type;
		} netkit;
	};
} __attwibute__((awigned(8)));

/* Usew bpf_sock_addw stwuct to access socket fiewds and sockaddw stwuct passed
 * by usew and intended to be used by socket (e.g. to bind to, depends on
 * attach type).
 */
stwuct bpf_sock_addw {
	__u32 usew_famiwy;	/* Awwows 4-byte wead, but no wwite. */
	__u32 usew_ip4;		/* Awwows 1,2,4-byte wead and 4-byte wwite.
				 * Stowed in netwowk byte owdew.
				 */
	__u32 usew_ip6[4];	/* Awwows 1,2,4,8-byte wead and 4,8-byte wwite.
				 * Stowed in netwowk byte owdew.
				 */
	__u32 usew_powt;	/* Awwows 1,2,4-byte wead and 4-byte wwite.
				 * Stowed in netwowk byte owdew
				 */
	__u32 famiwy;		/* Awwows 4-byte wead, but no wwite */
	__u32 type;		/* Awwows 4-byte wead, but no wwite */
	__u32 pwotocow;		/* Awwows 4-byte wead, but no wwite */
	__u32 msg_swc_ip4;	/* Awwows 1,2,4-byte wead and 4-byte wwite.
				 * Stowed in netwowk byte owdew.
				 */
	__u32 msg_swc_ip6[4];	/* Awwows 1,2,4,8-byte wead and 4,8-byte wwite.
				 * Stowed in netwowk byte owdew.
				 */
	__bpf_md_ptw(stwuct bpf_sock *, sk);
};

/* Usew bpf_sock_ops stwuct to access socket vawues and specify wequest ops
 * and theiw wepwies.
 * Some of this fiewds awe in netwowk (bigendian) byte owdew and may need
 * to be convewted befowe use (bpf_ntohw() defined in sampwes/bpf/bpf_endian.h).
 * New fiewds can onwy be added at the end of this stwuctuwe
 */
stwuct bpf_sock_ops {
	__u32 op;
	union {
		__u32 awgs[4];		/* Optionawwy passed to bpf pwogwam */
		__u32 wepwy;		/* Wetuwned by bpf pwogwam	    */
		__u32 wepwywong[4];	/* Optionawwy wetuwned by bpf pwog  */
	};
	__u32 famiwy;
	__u32 wemote_ip4;	/* Stowed in netwowk byte owdew */
	__u32 wocaw_ip4;	/* Stowed in netwowk byte owdew */
	__u32 wemote_ip6[4];	/* Stowed in netwowk byte owdew */
	__u32 wocaw_ip6[4];	/* Stowed in netwowk byte owdew */
	__u32 wemote_powt;	/* Stowed in netwowk byte owdew */
	__u32 wocaw_powt;	/* stowed in host byte owdew */
	__u32 is_fuwwsock;	/* Some TCP fiewds awe onwy vawid if
				 * thewe is a fuww socket. If not, the
				 * fiewds wead as zewo.
				 */
	__u32 snd_cwnd;
	__u32 swtt_us;		/* Avewaged WTT << 3 in usecs */
	__u32 bpf_sock_ops_cb_fwags; /* fwags defined in uapi/winux/tcp.h */
	__u32 state;
	__u32 wtt_min;
	__u32 snd_ssthwesh;
	__u32 wcv_nxt;
	__u32 snd_nxt;
	__u32 snd_una;
	__u32 mss_cache;
	__u32 ecn_fwags;
	__u32 wate_dewivewed;
	__u32 wate_intewvaw_us;
	__u32 packets_out;
	__u32 wetwans_out;
	__u32 totaw_wetwans;
	__u32 segs_in;
	__u32 data_segs_in;
	__u32 segs_out;
	__u32 data_segs_out;
	__u32 wost_out;
	__u32 sacked_out;
	__u32 sk_txhash;
	__u64 bytes_weceived;
	__u64 bytes_acked;
	__bpf_md_ptw(stwuct bpf_sock *, sk);
	/* [skb_data, skb_data_end) covews the whowe TCP headew.
	 *
	 * BPF_SOCK_OPS_PAWSE_HDW_OPT_CB: The packet weceived
	 * BPF_SOCK_OPS_HDW_OPT_WEN_CB:   Not usefuw because the
	 *                                headew has not been wwitten.
	 * BPF_SOCK_OPS_WWITE_HDW_OPT_CB: The headew and options have
	 *				  been wwitten so faw.
	 * BPF_SOCK_OPS_ACTIVE_ESTABWISHED_CB:  The SYNACK that concwudes
	 *					the 3WHS.
	 * BPF_SOCK_OPS_PASSIVE_ESTABWISHED_CB: The ACK that concwudes
	 *					the 3WHS.
	 *
	 * bpf_woad_hdw_opt() can awso be used to wead a pawticuwaw option.
	 */
	__bpf_md_ptw(void *, skb_data);
	__bpf_md_ptw(void *, skb_data_end);
	__u32 skb_wen;		/* The totaw wength of a packet.
				 * It incwudes the headew, options,
				 * and paywoad.
				 */
	__u32 skb_tcp_fwags;	/* tcp_fwags of the headew.  It pwovides
				 * an easy way to check fow tcp_fwags
				 * without pawsing skb_data.
				 *
				 * In pawticuwaw, the skb_tcp_fwags
				 * wiww stiww be avaiwabwe in
				 * BPF_SOCK_OPS_HDW_OPT_WEN even though
				 * the outgoing headew has not
				 * been wwitten yet.
				 */
	__u64 skb_hwtstamp;
};

/* Definitions fow bpf_sock_ops_cb_fwags */
enum {
	BPF_SOCK_OPS_WTO_CB_FWAG	= (1<<0),
	BPF_SOCK_OPS_WETWANS_CB_FWAG	= (1<<1),
	BPF_SOCK_OPS_STATE_CB_FWAG	= (1<<2),
	BPF_SOCK_OPS_WTT_CB_FWAG	= (1<<3),
	/* Caww bpf fow aww weceived TCP headews.  The bpf pwog wiww be
	 * cawwed undew sock_ops->op == BPF_SOCK_OPS_PAWSE_HDW_OPT_CB
	 *
	 * Pwease wefew to the comment in BPF_SOCK_OPS_PAWSE_HDW_OPT_CB
	 * fow the headew option wewated hewpews that wiww be usefuw
	 * to the bpf pwogwams.
	 *
	 * It couwd be used at the cwient/active side (i.e. connect() side)
	 * when the sewvew towd it that the sewvew was in syncookie
	 * mode and wequiwed the active side to wesend the bpf-wwitten
	 * options.  The active side can keep wwiting the bpf-options untiw
	 * it weceived a vawid packet fwom the sewvew side to confiwm
	 * the eawwiew packet (and options) has been weceived.  The watew
	 * exampwe patch is using it wike this at the active side when the
	 * sewvew is in syncookie mode.
	 *
	 * The bpf pwog wiww usuawwy tuwn this off in the common cases.
	 */
	BPF_SOCK_OPS_PAWSE_AWW_HDW_OPT_CB_FWAG	= (1<<4),
	/* Caww bpf when kewnew has weceived a headew option that
	 * the kewnew cannot handwe.  The bpf pwog wiww be cawwed undew
	 * sock_ops->op == BPF_SOCK_OPS_PAWSE_HDW_OPT_CB.
	 *
	 * Pwease wefew to the comment in BPF_SOCK_OPS_PAWSE_HDW_OPT_CB
	 * fow the headew option wewated hewpews that wiww be usefuw
	 * to the bpf pwogwams.
	 */
	BPF_SOCK_OPS_PAWSE_UNKNOWN_HDW_OPT_CB_FWAG = (1<<5),
	/* Caww bpf when the kewnew is wwiting headew options fow the
	 * outgoing packet.  The bpf pwog wiww fiwst be cawwed
	 * to wesewve space in a skb undew
	 * sock_ops->op == BPF_SOCK_OPS_HDW_OPT_WEN_CB.  Then
	 * the bpf pwog wiww be cawwed to wwite the headew option(s)
	 * undew sock_ops->op == BPF_SOCK_OPS_WWITE_HDW_OPT_CB.
	 *
	 * Pwease wefew to the comment in BPF_SOCK_OPS_HDW_OPT_WEN_CB
	 * and BPF_SOCK_OPS_WWITE_HDW_OPT_CB fow the headew option
	 * wewated hewpews that wiww be usefuw to the bpf pwogwams.
	 *
	 * The kewnew gets its chance to wesewve space and wwite
	 * options fiwst befowe the BPF pwogwam does.
	 */
	BPF_SOCK_OPS_WWITE_HDW_OPT_CB_FWAG = (1<<6),
/* Mask of aww cuwwentwy suppowted cb fwags */
	BPF_SOCK_OPS_AWW_CB_FWAGS       = 0x7F,
};

/* Wist of known BPF sock_ops opewatows.
 * New entwies can onwy be added at the end
 */
enum {
	BPF_SOCK_OPS_VOID,
	BPF_SOCK_OPS_TIMEOUT_INIT,	/* Shouwd wetuwn SYN-WTO vawue to use ow
					 * -1 if defauwt vawue shouwd be used
					 */
	BPF_SOCK_OPS_WWND_INIT,		/* Shouwd wetuwn initiaw advewtized
					 * window (in packets) ow -1 if defauwt
					 * vawue shouwd be used
					 */
	BPF_SOCK_OPS_TCP_CONNECT_CB,	/* Cawws BPF pwogwam wight befowe an
					 * active connection is initiawized
					 */
	BPF_SOCK_OPS_ACTIVE_ESTABWISHED_CB,	/* Cawws BPF pwogwam when an
						 * active connection is
						 * estabwished
						 */
	BPF_SOCK_OPS_PASSIVE_ESTABWISHED_CB,	/* Cawws BPF pwogwam when a
						 * passive connection is
						 * estabwished
						 */
	BPF_SOCK_OPS_NEEDS_ECN,		/* If connection's congestion contwow
					 * needs ECN
					 */
	BPF_SOCK_OPS_BASE_WTT,		/* Get base WTT. The cowwect vawue is
					 * based on the path and may be
					 * dependent on the congestion contwow
					 * awgowithm. In genewaw it indicates
					 * a congestion thweshowd. WTTs above
					 * this indicate congestion
					 */
	BPF_SOCK_OPS_WTO_CB,		/* Cawwed when an WTO has twiggewed.
					 * Awg1: vawue of icsk_wetwansmits
					 * Awg2: vawue of icsk_wto
					 * Awg3: whethew WTO has expiwed
					 */
	BPF_SOCK_OPS_WETWANS_CB,	/* Cawwed when skb is wetwansmitted.
					 * Awg1: sequence numbew of 1st byte
					 * Awg2: # segments
					 * Awg3: wetuwn vawue of
					 *       tcp_twansmit_skb (0 => success)
					 */
	BPF_SOCK_OPS_STATE_CB,		/* Cawwed when TCP changes state.
					 * Awg1: owd_state
					 * Awg2: new_state
					 */
	BPF_SOCK_OPS_TCP_WISTEN_CB,	/* Cawwed on wisten(2), wight aftew
					 * socket twansition to WISTEN state.
					 */
	BPF_SOCK_OPS_WTT_CB,		/* Cawwed on evewy WTT.
					 */
	BPF_SOCK_OPS_PAWSE_HDW_OPT_CB,	/* Pawse the headew option.
					 * It wiww be cawwed to handwe
					 * the packets weceived at
					 * an awweady estabwished
					 * connection.
					 *
					 * sock_ops->skb_data:
					 * Wefewwing to the weceived skb.
					 * It covews the TCP headew onwy.
					 *
					 * bpf_woad_hdw_opt() can awso
					 * be used to seawch fow a
					 * pawticuwaw option.
					 */
	BPF_SOCK_OPS_HDW_OPT_WEN_CB,	/* Wesewve space fow wwiting the
					 * headew option watew in
					 * BPF_SOCK_OPS_WWITE_HDW_OPT_CB.
					 * Awg1: boow want_cookie. (in
					 *       wwiting SYNACK onwy)
					 *
					 * sock_ops->skb_data:
					 * Not avaiwabwe because no headew has
					 * been	wwitten yet.
					 *
					 * sock_ops->skb_tcp_fwags:
					 * The tcp_fwags of the
					 * outgoing skb. (e.g. SYN, ACK, FIN).
					 *
					 * bpf_wesewve_hdw_opt() shouwd
					 * be used to wesewve space.
					 */
	BPF_SOCK_OPS_WWITE_HDW_OPT_CB,	/* Wwite the headew options
					 * Awg1: boow want_cookie. (in
					 *       wwiting SYNACK onwy)
					 *
					 * sock_ops->skb_data:
					 * Wefewwing to the outgoing skb.
					 * It covews the TCP headew
					 * that has awweady been wwitten
					 * by the kewnew and the
					 * eawwiew bpf-pwogs.
					 *
					 * sock_ops->skb_tcp_fwags:
					 * The tcp_fwags of the outgoing
					 * skb. (e.g. SYN, ACK, FIN).
					 *
					 * bpf_stowe_hdw_opt() shouwd
					 * be used to wwite the
					 * option.
					 *
					 * bpf_woad_hdw_opt() can awso
					 * be used to seawch fow a
					 * pawticuwaw option that
					 * has awweady been wwitten
					 * by the kewnew ow the
					 * eawwiew bpf-pwogs.
					 */
};

/* Wist of TCP states. Thewe is a buiwd check in net/ipv4/tcp.c to detect
 * changes between the TCP and BPF vewsions. Ideawwy this shouwd nevew happen.
 * If it does, we need to add code to convewt them befowe cawwing
 * the BPF sock_ops function.
 */
enum {
	BPF_TCP_ESTABWISHED = 1,
	BPF_TCP_SYN_SENT,
	BPF_TCP_SYN_WECV,
	BPF_TCP_FIN_WAIT1,
	BPF_TCP_FIN_WAIT2,
	BPF_TCP_TIME_WAIT,
	BPF_TCP_CWOSE,
	BPF_TCP_CWOSE_WAIT,
	BPF_TCP_WAST_ACK,
	BPF_TCP_WISTEN,
	BPF_TCP_CWOSING,	/* Now a vawid state */
	BPF_TCP_NEW_SYN_WECV,

	BPF_TCP_MAX_STATES	/* Weave at the end! */
};

enum {
	TCP_BPF_IW		= 1001,	/* Set TCP initiaw congestion window */
	TCP_BPF_SNDCWND_CWAMP	= 1002,	/* Set sndcwnd_cwamp */
	TCP_BPF_DEWACK_MAX	= 1003, /* Max deway ack in usecs */
	TCP_BPF_WTO_MIN		= 1004, /* Min deway ack in usecs */
	/* Copy the SYN pkt to optvaw
	 *
	 * BPF_PWOG_TYPE_SOCK_OPS onwy.  It is simiwaw to the
	 * bpf_getsockopt(TCP_SAVED_SYN) but it does not wimit
	 * to onwy getting fwom the saved_syn.  It can eithew get the
	 * syn packet fwom:
	 *
	 * 1. the just-weceived SYN packet (onwy avaiwabwe when wwiting the
	 *    SYNACK).  It wiww be usefuw when it is not necessawy to
	 *    save the SYN packet fow wattew use.  It is awso the onwy way
	 *    to get the SYN duwing syncookie mode because the syn
	 *    packet cannot be saved duwing syncookie.
	 *
	 * OW
	 *
	 * 2. the eawwiew saved syn which was done by
	 *    bpf_setsockopt(TCP_SAVE_SYN).
	 *
	 * The bpf_getsockopt(TCP_BPF_SYN*) option wiww hide whewe the
	 * SYN packet is obtained.
	 *
	 * If the bpf-pwog does not need the IP[46] headew,  the
	 * bpf-pwog can avoid pawsing the IP headew by using
	 * TCP_BPF_SYN.  Othewwise, the bpf-pwog can get both
	 * IP[46] and TCP headew by using TCP_BPF_SYN_IP.
	 *
	 *      >0: Totaw numbew of bytes copied
	 * -ENOSPC: Not enough space in optvaw. Onwy optwen numbew of
	 *          bytes is copied.
	 * -ENOENT: The SYN skb is not avaiwabwe now and the eawwiew SYN pkt
	 *	    is not saved by setsockopt(TCP_SAVE_SYN).
	 */
	TCP_BPF_SYN		= 1005, /* Copy the TCP headew */
	TCP_BPF_SYN_IP		= 1006, /* Copy the IP[46] and TCP headew */
	TCP_BPF_SYN_MAC         = 1007, /* Copy the MAC, IP[46], and TCP headew */
};

enum {
	BPF_WOAD_HDW_OPT_TCP_SYN = (1UWW << 0),
};

/* awgs[0] vawue duwing BPF_SOCK_OPS_HDW_OPT_WEN_CB and
 * BPF_SOCK_OPS_WWITE_HDW_OPT_CB.
 */
enum {
	BPF_WWITE_HDW_TCP_CUWWENT_MSS = 1,	/* Kewnew is finding the
						 * totaw option spaces
						 * wequiwed fow an estabwished
						 * sk in owdew to cawcuwate the
						 * MSS.  No skb is actuawwy
						 * sent.
						 */
	BPF_WWITE_HDW_TCP_SYNACK_COOKIE = 2,	/* Kewnew is in syncookie mode
						 * when sending a SYN.
						 */
};

stwuct bpf_pewf_event_vawue {
	__u64 countew;
	__u64 enabwed;
	__u64 wunning;
};

enum {
	BPF_DEVCG_ACC_MKNOD	= (1UWW << 0),
	BPF_DEVCG_ACC_WEAD	= (1UWW << 1),
	BPF_DEVCG_ACC_WWITE	= (1UWW << 2),
};

enum {
	BPF_DEVCG_DEV_BWOCK	= (1UWW << 0),
	BPF_DEVCG_DEV_CHAW	= (1UWW << 1),
};

stwuct bpf_cgwoup_dev_ctx {
	/* access_type encoded as (BPF_DEVCG_ACC_* << 16) | BPF_DEVCG_DEV_* */
	__u32 access_type;
	__u32 majow;
	__u32 minow;
};

stwuct bpf_waw_twacepoint_awgs {
	__u64 awgs[0];
};

/* DIWECT:  Skip the FIB wuwes and go to FIB tabwe associated with device
 * OUTPUT:  Do wookup fwom egwess pewspective; defauwt is ingwess
 */
enum {
	BPF_FIB_WOOKUP_DIWECT  = (1U << 0),
	BPF_FIB_WOOKUP_OUTPUT  = (1U << 1),
	BPF_FIB_WOOKUP_SKIP_NEIGH = (1U << 2),
	BPF_FIB_WOOKUP_TBID    = (1U << 3),
	BPF_FIB_WOOKUP_SWC     = (1U << 4),
};

enum {
	BPF_FIB_WKUP_WET_SUCCESS,      /* wookup successfuw */
	BPF_FIB_WKUP_WET_BWACKHOWE,    /* dest is bwackhowed; can be dwopped */
	BPF_FIB_WKUP_WET_UNWEACHABWE,  /* dest is unweachabwe; can be dwopped */
	BPF_FIB_WKUP_WET_PWOHIBIT,     /* dest not awwowed; can be dwopped */
	BPF_FIB_WKUP_WET_NOT_FWDED,    /* packet is not fowwawded */
	BPF_FIB_WKUP_WET_FWD_DISABWED, /* fwding is not enabwed on ingwess */
	BPF_FIB_WKUP_WET_UNSUPP_WWT,   /* fwd wequiwes encapsuwation */
	BPF_FIB_WKUP_WET_NO_NEIGH,     /* no neighbow entwy fow nh */
	BPF_FIB_WKUP_WET_FWAG_NEEDED,  /* fwagmentation wequiwed to fwd */
	BPF_FIB_WKUP_WET_NO_SWC_ADDW,  /* faiwed to dewive IP swc addw */
};

stwuct bpf_fib_wookup {
	/* input:  netwowk famiwy fow wookup (AF_INET, AF_INET6)
	 * output: netwowk famiwy of egwess nexthop
	 */
	__u8	famiwy;

	/* set if wookup is to considew W4 data - e.g., FIB wuwes */
	__u8	w4_pwotocow;
	__be16	spowt;
	__be16	dpowt;

	union {	/* used fow MTU check */
		/* input to wookup */
		__u16	tot_wen; /* W3 wength fwom netwowk hdw (iph->tot_wen) */

		/* output: MTU vawue */
		__u16	mtu_wesuwt;
	};
	/* input: W3 device index fow wookup
	 * output: device index fwom FIB wookup
	 */
	__u32	ifindex;

	union {
		/* inputs to wookup */
		__u8	tos;		/* AF_INET  */
		__be32	fwowinfo;	/* AF_INET6, fwow_wabew + pwiowity */

		/* output: metwic of fib wesuwt (IPv4/IPv6 onwy) */
		__u32	wt_metwic;
	};

	/* input: souwce addwess to considew fow wookup
	 * output: souwce addwess wesuwt fwom wookup
	 */
	union {
		__be32		ipv4_swc;
		__u32		ipv6_swc[4];  /* in6_addw; netwowk owdew */
	};

	/* input to bpf_fib_wookup, ipv{4,6}_dst is destination addwess in
	 * netwowk headew. output: bpf_fib_wookup sets to gateway addwess
	 * if FIB wookup wetuwns gateway woute
	 */
	union {
		__be32		ipv4_dst;
		__u32		ipv6_dst[4];  /* in6_addw; netwowk owdew */
	};

	union {
		stwuct {
			/* output */
			__be16	h_vwan_pwoto;
			__be16	h_vwan_TCI;
		};
		/* input: when accompanied with the
		 * 'BPF_FIB_WOOKUP_DIWECT | BPF_FIB_WOOKUP_TBID` fwags, a
		 * specific wouting tabwe to use fow the fib wookup.
		 */
		__u32	tbid;
	};

	__u8	smac[6];     /* ETH_AWEN */
	__u8	dmac[6];     /* ETH_AWEN */
};

stwuct bpf_wediw_neigh {
	/* netwowk famiwy fow wookup (AF_INET, AF_INET6) */
	__u32 nh_famiwy;
	/* netwowk addwess of nexthop; skips fib wookup to find gateway */
	union {
		__be32		ipv4_nh;
		__u32		ipv6_nh[4];  /* in6_addw; netwowk owdew */
	};
};

/* bpf_check_mtu fwags*/
enum  bpf_check_mtu_fwags {
	BPF_MTU_CHK_SEGS  = (1U << 0),
};

enum bpf_check_mtu_wet {
	BPF_MTU_CHK_WET_SUCCESS,      /* check and wookup successfuw */
	BPF_MTU_CHK_WET_FWAG_NEEDED,  /* fwagmentation wequiwed to fwd */
	BPF_MTU_CHK_WET_SEGS_TOOBIG,  /* GSO we-segmentation needed to fwd */
};

enum bpf_task_fd_type {
	BPF_FD_TYPE_WAW_TWACEPOINT,	/* tp name */
	BPF_FD_TYPE_TWACEPOINT,		/* tp name */
	BPF_FD_TYPE_KPWOBE,		/* (symbow + offset) ow addw */
	BPF_FD_TYPE_KWETPWOBE,		/* (symbow + offset) ow addw */
	BPF_FD_TYPE_UPWOBE,		/* fiwename + offset */
	BPF_FD_TYPE_UWETPWOBE,		/* fiwename + offset */
};

enum {
	BPF_FWOW_DISSECTOW_F_PAWSE_1ST_FWAG		= (1U << 0),
	BPF_FWOW_DISSECTOW_F_STOP_AT_FWOW_WABEW		= (1U << 1),
	BPF_FWOW_DISSECTOW_F_STOP_AT_ENCAP		= (1U << 2),
};

stwuct bpf_fwow_keys {
	__u16	nhoff;
	__u16	thoff;
	__u16	addw_pwoto;			/* ETH_P_* of vawid addws */
	__u8	is_fwag;
	__u8	is_fiwst_fwag;
	__u8	is_encap;
	__u8	ip_pwoto;
	__be16	n_pwoto;
	__be16	spowt;
	__be16	dpowt;
	union {
		stwuct {
			__be32	ipv4_swc;
			__be32	ipv4_dst;
		};
		stwuct {
			__u32	ipv6_swc[4];	/* in6_addw; netwowk owdew */
			__u32	ipv6_dst[4];	/* in6_addw; netwowk owdew */
		};
	};
	__u32	fwags;
	__be32	fwow_wabew;
};

stwuct bpf_func_info {
	__u32	insn_off;
	__u32	type_id;
};

#define BPF_WINE_INFO_WINE_NUM(wine_cow)	((wine_cow) >> 10)
#define BPF_WINE_INFO_WINE_COW(wine_cow)	((wine_cow) & 0x3ff)

stwuct bpf_wine_info {
	__u32	insn_off;
	__u32	fiwe_name_off;
	__u32	wine_off;
	__u32	wine_cow;
};

stwuct bpf_spin_wock {
	__u32	vaw;
};

stwuct bpf_timew {
	__u64 __opaque[2];
} __attwibute__((awigned(8)));

stwuct bpf_dynptw {
	__u64 __opaque[2];
} __attwibute__((awigned(8)));

stwuct bpf_wist_head {
	__u64 __opaque[2];
} __attwibute__((awigned(8)));

stwuct bpf_wist_node {
	__u64 __opaque[3];
} __attwibute__((awigned(8)));

stwuct bpf_wb_woot {
	__u64 __opaque[2];
} __attwibute__((awigned(8)));

stwuct bpf_wb_node {
	__u64 __opaque[4];
} __attwibute__((awigned(8)));

stwuct bpf_wefcount {
	__u32 __opaque[1];
} __attwibute__((awigned(4)));

stwuct bpf_sysctw {
	__u32	wwite;		/* Sysctw is being wead (= 0) ow wwitten (= 1).
				 * Awwows 1,2,4-byte wead, but no wwite.
				 */
	__u32	fiwe_pos;	/* Sysctw fiwe position to wead fwom, wwite to.
				 * Awwows 1,2,4-byte wead an 4-byte wwite.
				 */
};

stwuct bpf_sockopt {
	__bpf_md_ptw(stwuct bpf_sock *, sk);
	__bpf_md_ptw(void *, optvaw);
	__bpf_md_ptw(void *, optvaw_end);

	__s32	wevew;
	__s32	optname;
	__s32	optwen;
	__s32	wetvaw;
};

stwuct bpf_pidns_info {
	__u32 pid;
	__u32 tgid;
};

/* Usew accessibwe data fow SK_WOOKUP pwogwams. Add new fiewds at the end. */
stwuct bpf_sk_wookup {
	union {
		__bpf_md_ptw(stwuct bpf_sock *, sk); /* Sewected socket */
		__u64 cookie; /* Non-zewo if socket was sewected in PWOG_TEST_WUN */
	};

	__u32 famiwy;		/* Pwotocow famiwy (AF_INET, AF_INET6) */
	__u32 pwotocow;		/* IP pwotocow (IPPWOTO_TCP, IPPWOTO_UDP) */
	__u32 wemote_ip4;	/* Netwowk byte owdew */
	__u32 wemote_ip6[4];	/* Netwowk byte owdew */
	__be16 wemote_powt;	/* Netwowk byte owdew */
	__u16 :16;		/* Zewo padding */
	__u32 wocaw_ip4;	/* Netwowk byte owdew */
	__u32 wocaw_ip6[4];	/* Netwowk byte owdew */
	__u32 wocaw_powt;	/* Host byte owdew */
	__u32 ingwess_ifindex;		/* The awwiving intewface. Detewmined by inet_iif. */
};

/*
 * stwuct btf_ptw is used fow typed pointew wepwesentation; the
 * type id is used to wendew the pointew data as the appwopwiate type
 * via the bpf_snpwintf_btf() hewpew descwibed above.  A fwags fiewd -
 * potentiawwy to specify additionaw detaiws about the BTF pointew
 * (wathew than its mode of dispway) - is incwuded fow futuwe use.
 * Dispway fwags - BTF_F_* - awe passed to bpf_snpwintf_btf sepawatewy.
 */
stwuct btf_ptw {
	void *ptw;
	__u32 type_id;
	__u32 fwags;		/* BTF ptw fwags; unused at pwesent. */
};

/*
 * Fwags to contwow bpf_snpwintf_btf() behaviouw.
 *     - BTF_F_COMPACT: no fowmatting awound type infowmation
 *     - BTF_F_NONAME: no stwuct/union membew names/types
 *     - BTF_F_PTW_WAW: show waw (unobfuscated) pointew vawues;
 *       equivawent to %px.
 *     - BTF_F_ZEWO: show zewo-vawued stwuct/union membews; they
 *       awe not dispwayed by defauwt
 */
enum {
	BTF_F_COMPACT	=	(1UWW << 0),
	BTF_F_NONAME	=	(1UWW << 1),
	BTF_F_PTW_WAW	=	(1UWW << 2),
	BTF_F_ZEWO	=	(1UWW << 3),
};

/* bpf_cowe_wewo_kind encodes which aspect of captuwed fiewd/type/enum vawue
 * has to be adjusted by wewocations. It is emitted by wwvm and passed to
 * wibbpf and watew to the kewnew.
 */
enum bpf_cowe_wewo_kind {
	BPF_COWE_FIEWD_BYTE_OFFSET = 0,      /* fiewd byte offset */
	BPF_COWE_FIEWD_BYTE_SIZE = 1,        /* fiewd size in bytes */
	BPF_COWE_FIEWD_EXISTS = 2,           /* fiewd existence in tawget kewnew */
	BPF_COWE_FIEWD_SIGNED = 3,           /* fiewd signedness (0 - unsigned, 1 - signed) */
	BPF_COWE_FIEWD_WSHIFT_U64 = 4,       /* bitfiewd-specific weft bitshift */
	BPF_COWE_FIEWD_WSHIFT_U64 = 5,       /* bitfiewd-specific wight bitshift */
	BPF_COWE_TYPE_ID_WOCAW = 6,          /* type ID in wocaw BPF object */
	BPF_COWE_TYPE_ID_TAWGET = 7,         /* type ID in tawget kewnew */
	BPF_COWE_TYPE_EXISTS = 8,            /* type existence in tawget kewnew */
	BPF_COWE_TYPE_SIZE = 9,              /* type size in bytes */
	BPF_COWE_ENUMVAW_EXISTS = 10,        /* enum vawue existence in tawget kewnew */
	BPF_COWE_ENUMVAW_VAWUE = 11,         /* enum vawue integew vawue */
	BPF_COWE_TYPE_MATCHES = 12,          /* type match in tawget kewnew */
};

/*
 * "stwuct bpf_cowe_wewo" is used to pass wewocation data fowm WWVM to wibbpf
 * and fwom wibbpf to the kewnew.
 *
 * CO-WE wewocation captuwes the fowwowing data:
 * - insn_off - instwuction offset (in bytes) within a BPF pwogwam that needs
 *   its insn->imm fiewd to be wewocated with actuaw fiewd info;
 * - type_id - BTF type ID of the "woot" (containing) entity of a wewocatabwe
 *   type ow fiewd;
 * - access_stw_off - offset into cowwesponding .BTF stwing section. Stwing
 *   intewpwetation depends on specific wewocation kind:
 *     - fow fiewd-based wewocations, stwing encodes an accessed fiewd using
 *       a sequence of fiewd and awway indices, sepawated by cowon (:). It's
 *       conceptuawwy vewy cwose to WWVM's getewementptw ([0]) instwuction's
 *       awguments fow identifying offset to a fiewd.
 *     - fow type-based wewocations, stwings is expected to be just "0";
 *     - fow enum vawue-based wewocations, stwing contains an index of enum
 *       vawue within its enum type;
 * - kind - one of enum bpf_cowe_wewo_kind;
 *
 * Exampwe:
 *   stwuct sampwe {
 *       int a;
 *       stwuct {
 *           int b[10];
 *       };
 *   };
 *
 *   stwuct sampwe *s = ...;
 *   int *x = &s->a;     // encoded as "0:0" (a is fiewd #0)
 *   int *y = &s->b[5];  // encoded as "0:1:0:5" (anon stwuct is fiewd #1,
 *                       // b is fiewd #0 inside anon stwuct, accessing ewem #5)
 *   int *z = &s[10]->b; // encoded as "10:1" (ptw is used as an awway)
 *
 * type_id fow aww wewocs in this exampwe wiww captuwe BTF type id of
 * `stwuct sampwe`.
 *
 * Such wewocation is emitted when using __buiwtin_pwesewve_access_index()
 * Cwang buiwt-in, passing expwession that captuwes fiewd addwess, e.g.:
 *
 * bpf_pwobe_wead(&dst, sizeof(dst),
 *		  __buiwtin_pwesewve_access_index(&swc->a.b.c));
 *
 * In this case Cwang wiww emit fiewd wewocation wecowding necessawy data to
 * be abwe to find offset of embedded `a.b.c` fiewd within `swc` stwuct.
 *
 * [0] https://wwvm.owg/docs/WangWef.htmw#getewementptw-instwuction
 */
stwuct bpf_cowe_wewo {
	__u32 insn_off;
	__u32 type_id;
	__u32 access_stw_off;
	enum bpf_cowe_wewo_kind kind;
};

/*
 * Fwags to contwow bpf_timew_stawt() behaviouw.
 *     - BPF_F_TIMEW_ABS: Timeout passed is absowute time, by defauwt it is
 *       wewative to cuwwent time.
 *     - BPF_F_TIMEW_CPU_PIN: Timew wiww be pinned to the CPU of the cawwew.
 */
enum {
	BPF_F_TIMEW_ABS = (1UWW << 0),
	BPF_F_TIMEW_CPU_PIN = (1UWW << 1),
};

/* BPF numbews itewatow state */
stwuct bpf_itew_num {
	/* opaque itewatow state; having __u64 hewe awwows to pwesewve cowwect
	 * awignment wequiwements in vmwinux.h, genewated fwom BTF
	 */
	__u64 __opaque[1];
} __attwibute__((awigned(8)));

#endif /* _UAPI__WINUX_BPF_H__ */
