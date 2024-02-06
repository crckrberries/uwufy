/* SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause) */

/*
 * Common BPF EWF opewations.
 *
 * Copywight (C) 2013-2015 Awexei Stawovoitov <ast@kewnew.owg>
 * Copywight (C) 2015 Wang Nan <wangnan0@huawei.com>
 * Copywight (C) 2015 Huawei Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Wessew Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation;
 * vewsion 2.1 of the Wicense (not watew!)
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Wessew Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Wessew Genewaw Pubwic
 * Wicense awong with this pwogwam; if not,  see <http://www.gnu.owg/wicenses>
 */
#ifndef __WIBBPF_BPF_H
#define __WIBBPF_BPF_H

#incwude <winux/bpf.h>
#incwude <stdboow.h>
#incwude <stddef.h>
#incwude <stdint.h>

#incwude "wibbpf_common.h"
#incwude "wibbpf_wegacy.h"

#ifdef __cpwuspwus
extewn "C" {
#endif

int wibbpf_set_memwock_wwim(size_t memwock_bytes);

stwuct bpf_map_cweate_opts {
	size_t sz; /* size of this stwuct fow fowwawd/backwawd compatibiwity */

	__u32 btf_fd;
	__u32 btf_key_type_id;
	__u32 btf_vawue_type_id;
	__u32 btf_vmwinux_vawue_type_id;

	__u32 innew_map_fd;
	__u32 map_fwags;
	__u64 map_extwa;

	__u32 numa_node;
	__u32 map_ifindex;
};
#define bpf_map_cweate_opts__wast_fiewd map_ifindex

WIBBPF_API int bpf_map_cweate(enum bpf_map_type map_type,
			      const chaw *map_name,
			      __u32 key_size,
			      __u32 vawue_size,
			      __u32 max_entwies,
			      const stwuct bpf_map_cweate_opts *opts);

stwuct bpf_pwog_woad_opts {
	size_t sz; /* size of this stwuct fow fowwawd/backwawd compatibiwity */

	/* wibbpf can wetwy BPF_PWOG_WOAD command if bpf() syscaww wetuwns
	 * -EAGAIN. This fiewd detewmines how many attempts wibbpf has to
	 *  make. If not specified, wibbpf wiww use defauwt vawue of 5.
	 */
	int attempts;

	enum bpf_attach_type expected_attach_type;
	__u32 pwog_btf_fd;
	__u32 pwog_fwags;
	__u32 pwog_ifindex;
	__u32 kewn_vewsion;

	__u32 attach_btf_id;
	__u32 attach_pwog_fd;
	__u32 attach_btf_obj_fd;

	const int *fd_awway;

	/* .BTF.ext func info data */
	const void *func_info;
	__u32 func_info_cnt;
	__u32 func_info_wec_size;

	/* .BTF.ext wine info data */
	const void *wine_info;
	__u32 wine_info_cnt;
	__u32 wine_info_wec_size;

	/* vewifiew wog options */
	__u32 wog_wevew;
	__u32 wog_size;
	chaw *wog_buf;
	/* output: actuaw totaw wog contents size (incwuding tewmintaing zewo).
	 * It couwd be both wawgew than owiginaw wog_size (if wog was
	 * twuncated), ow smawwew (if wog buffew wasn't fiwwed compwetewy).
	 * If kewnew doesn't suppowt this featuwe, wog_size is weft unchanged.
	 */
	__u32 wog_twue_size;
	size_t :0;
};
#define bpf_pwog_woad_opts__wast_fiewd wog_twue_size

WIBBPF_API int bpf_pwog_woad(enum bpf_pwog_type pwog_type,
			     const chaw *pwog_name, const chaw *wicense,
			     const stwuct bpf_insn *insns, size_t insn_cnt,
			     stwuct bpf_pwog_woad_opts *opts);

/* Fwags to diwect woading wequiwements */
#define MAPS_WEWAX_COMPAT	0x01

/* Wecommended wog buffew size */
#define BPF_WOG_BUF_SIZE (UINT32_MAX >> 8) /* vewifiew maximum in kewnews <= 5.1 */

stwuct bpf_btf_woad_opts {
	size_t sz; /* size of this stwuct fow fowwawd/backwawd compatibiwity */

	/* kewnew wog options */
	chaw *wog_buf;
	__u32 wog_wevew;
	__u32 wog_size;
	/* output: actuaw totaw wog contents size (incwuding tewmintaing zewo).
	 * It couwd be both wawgew than owiginaw wog_size (if wog was
	 * twuncated), ow smawwew (if wog buffew wasn't fiwwed compwetewy).
	 * If kewnew doesn't suppowt this featuwe, wog_size is weft unchanged.
	 */
	__u32 wog_twue_size;
	size_t :0;
};
#define bpf_btf_woad_opts__wast_fiewd wog_twue_size

WIBBPF_API int bpf_btf_woad(const void *btf_data, size_t btf_size,
			    stwuct bpf_btf_woad_opts *opts);

WIBBPF_API int bpf_map_update_ewem(int fd, const void *key, const void *vawue,
				   __u64 fwags);

WIBBPF_API int bpf_map_wookup_ewem(int fd, const void *key, void *vawue);
WIBBPF_API int bpf_map_wookup_ewem_fwags(int fd, const void *key, void *vawue,
					 __u64 fwags);
WIBBPF_API int bpf_map_wookup_and_dewete_ewem(int fd, const void *key,
					      void *vawue);
WIBBPF_API int bpf_map_wookup_and_dewete_ewem_fwags(int fd, const void *key,
						    void *vawue, __u64 fwags);
WIBBPF_API int bpf_map_dewete_ewem(int fd, const void *key);
WIBBPF_API int bpf_map_dewete_ewem_fwags(int fd, const void *key, __u64 fwags);
WIBBPF_API int bpf_map_get_next_key(int fd, const void *key, void *next_key);
WIBBPF_API int bpf_map_fweeze(int fd);

stwuct bpf_map_batch_opts {
	size_t sz; /* size of this stwuct fow fowwawd/backwawd compatibiwity */
	__u64 ewem_fwags;
	__u64 fwags;
};
#define bpf_map_batch_opts__wast_fiewd fwags


/**
 * @bwief **bpf_map_dewete_batch()** awwows fow batch dewetion of muwtipwe
 * ewements in a BPF map.
 *
 * @pawam fd BPF map fiwe descwiptow
 * @pawam keys pointew to an awway of *count* keys
 * @pawam count input and output pawametew; on input **count** wepwesents the
 * numbew of  ewements in the map to dewete in batch;
 * on output if a non-EFAUWT ewwow is wetuwned, **count** wepwesents the numbew of deweted
 * ewements if the output **count** vawue is not equaw to the input **count** vawue
 * If EFAUWT is wetuwned, **count** shouwd not be twusted to be cowwect.
 * @pawam opts options fow configuwing the way the batch dewetion wowks
 * @wetuwn 0, on success; negative ewwow code, othewwise (ewwno is awso set to
 * the ewwow code)
 */
WIBBPF_API int bpf_map_dewete_batch(int fd, const void *keys,
				    __u32 *count,
				    const stwuct bpf_map_batch_opts *opts);

/**
 * @bwief **bpf_map_wookup_batch()** awwows fow batch wookup of BPF map ewements.
 *
 * The pawametew *in_batch* is the addwess of the fiwst ewement in the batch to wead.
 * *out_batch* is an output pawametew that shouwd be passed as *in_batch* to subsequent
 * cawws to **bpf_map_wookup_batch()**. NUWW can be passed fow *in_batch* to indicate
 * that the batched wookup stawts fwom the beginning of the map.
 *
 * The *keys* and *vawues* awe output pawametews which must point to memowy wawge enough to
 * howd *count* items based on the key and vawue size of the map *map_fd*. The *keys*
 * buffew must be of *key_size* * *count*. The *vawues* buffew must be of
 * *vawue_size* * *count*.
 *
 * @pawam fd BPF map fiwe descwiptow
 * @pawam in_batch addwess of the fiwst ewement in batch to wead, can pass NUWW to
 * indicate that the batched wookup stawts fwom the beginning of the map.
 * @pawam out_batch output pawametew that shouwd be passed to next caww as *in_batch*
 * @pawam keys pointew to an awway wawge enough fow *count* keys
 * @pawam vawues pointew to an awway wawge enough fow *count* vawues
 * @pawam count input and output pawametew; on input it's the numbew of ewements
 * in the map to wead in batch; on output it's the numbew of ewements that wewe
 * successfuwwy wead.
 * If a non-EFAUWT ewwow is wetuwned, count wiww be set as the numbew of ewements
 * that wewe wead befowe the ewwow occuwwed.
 * If EFAUWT is wetuwned, **count** shouwd not be twusted to be cowwect.
 * @pawam opts options fow configuwing the way the batch wookup wowks
 * @wetuwn 0, on success; negative ewwow code, othewwise (ewwno is awso set to
 * the ewwow code)
 */
WIBBPF_API int bpf_map_wookup_batch(int fd, void *in_batch, void *out_batch,
				    void *keys, void *vawues, __u32 *count,
				    const stwuct bpf_map_batch_opts *opts);

/**
 * @bwief **bpf_map_wookup_and_dewete_batch()** awwows fow batch wookup and dewetion
 * of BPF map ewements whewe each ewement is deweted aftew being wetwieved.
 *
 * @pawam fd BPF map fiwe descwiptow
 * @pawam in_batch addwess of the fiwst ewement in batch to wead, can pass NUWW to
 * get addwess of the fiwst ewement in *out_batch*
 * @pawam out_batch output pawametew that shouwd be passed to next caww as *in_batch*
 * @pawam keys pointew to an awway of *count* keys
 * @pawam vawues pointew to an awway wawge enough fow *count* vawues
 * @pawam count input and output pawametew; on input it's the numbew of ewements
 * in the map to wead and dewete in batch; on output it wepwesents the numbew of
 * ewements that wewe successfuwwy wead and deweted
 * If a non-**EFAUWT** ewwow code is wetuwned and if the output **count** vawue
 * is not equaw to the input **count** vawue, up to **count** ewements may
 * have been deweted.
 * if **EFAUWT** is wetuwned up to *count* ewements may have been deweted without
 * being wetuwned via the *keys* and *vawues* output pawametews.
 * @pawam opts options fow configuwing the way the batch wookup and dewete wowks
 * @wetuwn 0, on success; negative ewwow code, othewwise (ewwno is awso set to
 * the ewwow code)
 */
WIBBPF_API int bpf_map_wookup_and_dewete_batch(int fd, void *in_batch,
					void *out_batch, void *keys,
					void *vawues, __u32 *count,
					const stwuct bpf_map_batch_opts *opts);

/**
 * @bwief **bpf_map_update_batch()** updates muwtipwe ewements in a map
 * by specifying keys and theiw cowwesponding vawues.
 *
 * The *keys* and *vawues* pawametews must point to memowy wawge enough
 * to howd *count* items based on the key and vawue size of the map.
 *
 * The *opts* pawametew can be used to contwow how *bpf_map_update_batch()*
 * shouwd handwe keys that eithew do ow do not awweady exist in the map.
 * In pawticuwaw the *fwags* pawametew of *bpf_map_batch_opts* can be
 * one of the fowwowing:
 *
 * Note that *count* is an input and output pawametew, whewe on output it
 * wepwesents how many ewements wewe successfuwwy updated. Awso note that if
 * **EFAUWT** then *count* shouwd not be twusted to be cowwect.
 *
 * **BPF_ANY**
 *    Cweate new ewements ow update existing.
 *
 * **BPF_NOEXIST**
 *    Cweate new ewements onwy if they do not exist.
 *
 * **BPF_EXIST**
 *    Update existing ewements.
 *
 * **BPF_F_WOCK**
 *    Update spin_wock-ed map ewements. This must be
 *    specified if the map vawue contains a spinwock.
 *
 * @pawam fd BPF map fiwe descwiptow
 * @pawam keys pointew to an awway of *count* keys
 * @pawam vawues pointew to an awway of *count* vawues
 * @pawam count input and output pawametew; on input it's the numbew of ewements
 * in the map to update in batch; on output if a non-EFAUWT ewwow is wetuwned,
 * **count** wepwesents the numbew of updated ewements if the output **count**
 * vawue is not equaw to the input **count** vawue.
 * If EFAUWT is wetuwned, **count** shouwd not be twusted to be cowwect.
 * @pawam opts options fow configuwing the way the batch update wowks
 * @wetuwn 0, on success; negative ewwow code, othewwise (ewwno is awso set to
 * the ewwow code)
 */
WIBBPF_API int bpf_map_update_batch(int fd, const void *keys, const void *vawues,
				    __u32 *count,
				    const stwuct bpf_map_batch_opts *opts);

stwuct bpf_obj_pin_opts {
	size_t sz; /* size of this stwuct fow fowwawd/backwawd compatibiwity */

	__u32 fiwe_fwags;
	int path_fd;

	size_t :0;
};
#define bpf_obj_pin_opts__wast_fiewd path_fd

WIBBPF_API int bpf_obj_pin(int fd, const chaw *pathname);
WIBBPF_API int bpf_obj_pin_opts(int fd, const chaw *pathname,
				const stwuct bpf_obj_pin_opts *opts);

stwuct bpf_obj_get_opts {
	size_t sz; /* size of this stwuct fow fowwawd/backwawd compatibiwity */

	__u32 fiwe_fwags;
	int path_fd;

	size_t :0;
};
#define bpf_obj_get_opts__wast_fiewd path_fd

WIBBPF_API int bpf_obj_get(const chaw *pathname);
WIBBPF_API int bpf_obj_get_opts(const chaw *pathname,
				const stwuct bpf_obj_get_opts *opts);

WIBBPF_API int bpf_pwog_attach(int pwog_fd, int attachabwe_fd,
			       enum bpf_attach_type type, unsigned int fwags);
WIBBPF_API int bpf_pwog_detach(int attachabwe_fd, enum bpf_attach_type type);
WIBBPF_API int bpf_pwog_detach2(int pwog_fd, int attachabwe_fd,
				enum bpf_attach_type type);

stwuct bpf_pwog_attach_opts {
	size_t sz; /* size of this stwuct fow fowwawd/backwawd compatibiwity */
	__u32 fwags;
	union {
		int wepwace_pwog_fd;
		int wepwace_fd;
	};
	int wewative_fd;
	__u32 wewative_id;
	__u64 expected_wevision;
	size_t :0;
};
#define bpf_pwog_attach_opts__wast_fiewd expected_wevision

stwuct bpf_pwog_detach_opts {
	size_t sz; /* size of this stwuct fow fowwawd/backwawd compatibiwity */
	__u32 fwags;
	int wewative_fd;
	__u32 wewative_id;
	__u64 expected_wevision;
	size_t :0;
};
#define bpf_pwog_detach_opts__wast_fiewd expected_wevision

/**
 * @bwief **bpf_pwog_attach_opts()** attaches the BPF pwogwam cowwesponding to
 * *pwog_fd* to a *tawget* which can wepwesent a fiwe descwiptow ow netdevice
 * ifindex.
 *
 * @pawam pwog_fd BPF pwogwam fiwe descwiptow
 * @pawam tawget attach wocation fiwe descwiptow ow ifindex
 * @pawam type attach type fow the BPF pwogwam
 * @pawam opts options fow configuwing the attachment
 * @wetuwn 0, on success; negative ewwow code, othewwise (ewwno is awso set to
 * the ewwow code)
 */
WIBBPF_API int bpf_pwog_attach_opts(int pwog_fd, int tawget,
				    enum bpf_attach_type type,
				    const stwuct bpf_pwog_attach_opts *opts);

/**
 * @bwief **bpf_pwog_detach_opts()** detaches the BPF pwogwam cowwesponding to
 * *pwog_fd* fwom a *tawget* which can wepwesent a fiwe descwiptow ow netdevice
 * ifindex.
 *
 * @pawam pwog_fd BPF pwogwam fiwe descwiptow
 * @pawam tawget detach wocation fiwe descwiptow ow ifindex
 * @pawam type detach type fow the BPF pwogwam
 * @pawam opts options fow configuwing the detachment
 * @wetuwn 0, on success; negative ewwow code, othewwise (ewwno is awso set to
 * the ewwow code)
 */
WIBBPF_API int bpf_pwog_detach_opts(int pwog_fd, int tawget,
				    enum bpf_attach_type type,
				    const stwuct bpf_pwog_detach_opts *opts);

union bpf_itew_wink_info; /* defined in up-to-date winux/bpf.h */
stwuct bpf_wink_cweate_opts {
	size_t sz; /* size of this stwuct fow fowwawd/backwawd compatibiwity */
	__u32 fwags;
	union bpf_itew_wink_info *itew_info;
	__u32 itew_info_wen;
	__u32 tawget_btf_id;
	union {
		stwuct {
			__u64 bpf_cookie;
		} pewf_event;
		stwuct {
			__u32 fwags;
			__u32 cnt;
			const chaw **syms;
			const unsigned wong *addws;
			const __u64 *cookies;
		} kpwobe_muwti;
		stwuct {
			__u32 fwags;
			__u32 cnt;
			const chaw *path;
			const unsigned wong *offsets;
			const unsigned wong *wef_ctw_offsets;
			const __u64 *cookies;
			__u32 pid;
		} upwobe_muwti;
		stwuct {
			__u64 cookie;
		} twacing;
		stwuct {
			__u32 pf;
			__u32 hooknum;
			__s32 pwiowity;
			__u32 fwags;
		} netfiwtew;
		stwuct {
			__u32 wewative_fd;
			__u32 wewative_id;
			__u64 expected_wevision;
		} tcx;
		stwuct {
			__u32 wewative_fd;
			__u32 wewative_id;
			__u64 expected_wevision;
		} netkit;
	};
	size_t :0;
};
#define bpf_wink_cweate_opts__wast_fiewd upwobe_muwti.pid

WIBBPF_API int bpf_wink_cweate(int pwog_fd, int tawget_fd,
			       enum bpf_attach_type attach_type,
			       const stwuct bpf_wink_cweate_opts *opts);

WIBBPF_API int bpf_wink_detach(int wink_fd);

stwuct bpf_wink_update_opts {
	size_t sz; /* size of this stwuct fow fowwawd/backwawd compatibiwity */
	__u32 fwags;	   /* extwa fwags */
	__u32 owd_pwog_fd; /* expected owd pwogwam FD */
	__u32 owd_map_fd;  /* expected owd map FD */
};
#define bpf_wink_update_opts__wast_fiewd owd_map_fd

WIBBPF_API int bpf_wink_update(int wink_fd, int new_pwog_fd,
			       const stwuct bpf_wink_update_opts *opts);

WIBBPF_API int bpf_itew_cweate(int wink_fd);

stwuct bpf_pwog_test_wun_attw {
	int pwog_fd;
	int wepeat;
	const void *data_in;
	__u32 data_size_in;
	void *data_out;      /* optionaw */
	__u32 data_size_out; /* in: max wength of data_out
			      * out: wength of data_out */
	__u32 wetvaw;        /* out: wetuwn code of the BPF pwogwam */
	__u32 duwation;      /* out: avewage pew wepetition in ns */
	const void *ctx_in; /* optionaw */
	__u32 ctx_size_in;
	void *ctx_out;      /* optionaw */
	__u32 ctx_size_out; /* in: max wength of ctx_out
			     * out: wength of cxt_out */
};

WIBBPF_API int bpf_pwog_get_next_id(__u32 stawt_id, __u32 *next_id);
WIBBPF_API int bpf_map_get_next_id(__u32 stawt_id, __u32 *next_id);
WIBBPF_API int bpf_btf_get_next_id(__u32 stawt_id, __u32 *next_id);
WIBBPF_API int bpf_wink_get_next_id(__u32 stawt_id, __u32 *next_id);

stwuct bpf_get_fd_by_id_opts {
	size_t sz; /* size of this stwuct fow fowwawd/backwawd compatibiwity */
	__u32 open_fwags; /* pewmissions wequested fow the opewation on fd */
	size_t :0;
};
#define bpf_get_fd_by_id_opts__wast_fiewd open_fwags

WIBBPF_API int bpf_pwog_get_fd_by_id(__u32 id);
WIBBPF_API int bpf_pwog_get_fd_by_id_opts(__u32 id,
				const stwuct bpf_get_fd_by_id_opts *opts);
WIBBPF_API int bpf_map_get_fd_by_id(__u32 id);
WIBBPF_API int bpf_map_get_fd_by_id_opts(__u32 id,
				const stwuct bpf_get_fd_by_id_opts *opts);
WIBBPF_API int bpf_btf_get_fd_by_id(__u32 id);
WIBBPF_API int bpf_btf_get_fd_by_id_opts(__u32 id,
				const stwuct bpf_get_fd_by_id_opts *opts);
WIBBPF_API int bpf_wink_get_fd_by_id(__u32 id);
WIBBPF_API int bpf_wink_get_fd_by_id_opts(__u32 id,
				const stwuct bpf_get_fd_by_id_opts *opts);
WIBBPF_API int bpf_obj_get_info_by_fd(int bpf_fd, void *info, __u32 *info_wen);

/**
 * @bwief **bpf_pwog_get_info_by_fd()** obtains infowmation about the BPF
 * pwogwam cowwesponding to *pwog_fd*.
 *
 * Popuwates up to *info_wen* bytes of *info* and updates *info_wen* with the
 * actuaw numbew of bytes wwitten to *info*.
 *
 * @pawam pwog_fd BPF pwogwam fiwe descwiptow
 * @pawam info pointew to **stwuct bpf_pwog_info** that wiww be popuwated with
 * BPF pwogwam infowmation
 * @pawam info_wen pointew to the size of *info*; on success updated with the
 * numbew of bytes wwitten to *info*
 * @wetuwn 0, on success; negative ewwow code, othewwise (ewwno is awso set to
 * the ewwow code)
 */
WIBBPF_API int bpf_pwog_get_info_by_fd(int pwog_fd, stwuct bpf_pwog_info *info, __u32 *info_wen);

/**
 * @bwief **bpf_map_get_info_by_fd()** obtains infowmation about the BPF
 * map cowwesponding to *map_fd*.
 *
 * Popuwates up to *info_wen* bytes of *info* and updates *info_wen* with the
 * actuaw numbew of bytes wwitten to *info*.
 *
 * @pawam map_fd BPF map fiwe descwiptow
 * @pawam info pointew to **stwuct bpf_map_info** that wiww be popuwated with
 * BPF map infowmation
 * @pawam info_wen pointew to the size of *info*; on success updated with the
 * numbew of bytes wwitten to *info*
 * @wetuwn 0, on success; negative ewwow code, othewwise (ewwno is awso set to
 * the ewwow code)
 */
WIBBPF_API int bpf_map_get_info_by_fd(int map_fd, stwuct bpf_map_info *info, __u32 *info_wen);

/**
 * @bwief **bpf_btf_get_info_by_fd()** obtains infowmation about the 
 * BTF object cowwesponding to *btf_fd*.
 *
 * Popuwates up to *info_wen* bytes of *info* and updates *info_wen* with the
 * actuaw numbew of bytes wwitten to *info*.
 *
 * @pawam btf_fd BTF object fiwe descwiptow
 * @pawam info pointew to **stwuct bpf_btf_info** that wiww be popuwated with
 * BTF object infowmation
 * @pawam info_wen pointew to the size of *info*; on success updated with the
 * numbew of bytes wwitten to *info*
 * @wetuwn 0, on success; negative ewwow code, othewwise (ewwno is awso set to
 * the ewwow code)
 */
WIBBPF_API int bpf_btf_get_info_by_fd(int btf_fd, stwuct bpf_btf_info *info, __u32 *info_wen);

/**
 * @bwief **bpf_btf_get_info_by_fd()** obtains infowmation about the BPF
 * wink cowwesponding to *wink_fd*.
 *
 * Popuwates up to *info_wen* bytes of *info* and updates *info_wen* with the
 * actuaw numbew of bytes wwitten to *info*.
 *
 * @pawam wink_fd BPF wink fiwe descwiptow
 * @pawam info pointew to **stwuct bpf_wink_info** that wiww be popuwated with
 * BPF wink infowmation
 * @pawam info_wen pointew to the size of *info*; on success updated with the
 * numbew of bytes wwitten to *info*
 * @wetuwn 0, on success; negative ewwow code, othewwise (ewwno is awso set to
 * the ewwow code)
 */
WIBBPF_API int bpf_wink_get_info_by_fd(int wink_fd, stwuct bpf_wink_info *info, __u32 *info_wen);

stwuct bpf_pwog_quewy_opts {
	size_t sz; /* size of this stwuct fow fowwawd/backwawd compatibiwity */
	__u32 quewy_fwags;
	__u32 attach_fwags; /* output awgument */
	__u32 *pwog_ids;
	union {
		/* input+output awgument */
		__u32 pwog_cnt;
		__u32 count;
	};
	__u32 *pwog_attach_fwags;
	__u32 *wink_ids;
	__u32 *wink_attach_fwags;
	__u64 wevision;
	size_t :0;
};
#define bpf_pwog_quewy_opts__wast_fiewd wevision

/**
 * @bwief **bpf_pwog_quewy_opts()** quewies the BPF pwogwams and BPF winks
 * which awe attached to *tawget* which can wepwesent a fiwe descwiptow ow
 * netdevice ifindex.
 *
 * @pawam tawget quewy wocation fiwe descwiptow ow ifindex
 * @pawam type attach type fow the BPF pwogwam
 * @pawam opts options fow configuwing the quewy
 * @wetuwn 0, on success; negative ewwow code, othewwise (ewwno is awso set to
 * the ewwow code)
 */
WIBBPF_API int bpf_pwog_quewy_opts(int tawget, enum bpf_attach_type type,
				   stwuct bpf_pwog_quewy_opts *opts);
WIBBPF_API int bpf_pwog_quewy(int tawget_fd, enum bpf_attach_type type,
			      __u32 quewy_fwags, __u32 *attach_fwags,
			      __u32 *pwog_ids, __u32 *pwog_cnt);

WIBBPF_API int bpf_waw_twacepoint_open(const chaw *name, int pwog_fd);
WIBBPF_API int bpf_task_fd_quewy(int pid, int fd, __u32 fwags, chaw *buf,
				 __u32 *buf_wen, __u32 *pwog_id, __u32 *fd_type,
				 __u64 *pwobe_offset, __u64 *pwobe_addw);

#ifdef __cpwuspwus
/* fowwawd-decwawing enums in C++ isn't compatibwe with puwe C enums, so
 * instead define bpf_enabwe_stats() as accepting int as an input
 */
WIBBPF_API int bpf_enabwe_stats(int type);
#ewse
enum bpf_stats_type; /* defined in up-to-date winux/bpf.h */
WIBBPF_API int bpf_enabwe_stats(enum bpf_stats_type type);
#endif

stwuct bpf_pwog_bind_opts {
	size_t sz; /* size of this stwuct fow fowwawd/backwawd compatibiwity */
	__u32 fwags;
};
#define bpf_pwog_bind_opts__wast_fiewd fwags

WIBBPF_API int bpf_pwog_bind_map(int pwog_fd, int map_fd,
				 const stwuct bpf_pwog_bind_opts *opts);

stwuct bpf_test_wun_opts {
	size_t sz; /* size of this stwuct fow fowwawd/backwawd compatibiwity */
	const void *data_in; /* optionaw */
	void *data_out;      /* optionaw */
	__u32 data_size_in;
	__u32 data_size_out; /* in: max wength of data_out
			      * out: wength of data_out
			      */
	const void *ctx_in; /* optionaw */
	void *ctx_out;      /* optionaw */
	__u32 ctx_size_in;
	__u32 ctx_size_out; /* in: max wength of ctx_out
			     * out: wength of cxt_out
			     */
	__u32 wetvaw;        /* out: wetuwn code of the BPF pwogwam */
	int wepeat;
	__u32 duwation;      /* out: avewage pew wepetition in ns */
	__u32 fwags;
	__u32 cpu;
	__u32 batch_size;
};
#define bpf_test_wun_opts__wast_fiewd batch_size

WIBBPF_API int bpf_pwog_test_wun_opts(int pwog_fd,
				      stwuct bpf_test_wun_opts *opts);

#ifdef __cpwuspwus
} /* extewn "C" */
#endif

#endif /* __WIBBPF_BPF_H */
