/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/* Copywight (C) 2017-2018 Netwonome Systems, Inc. */

#ifndef __BPF_TOOW_H
#define __BPF_TOOW_H

/* BFD and kewnew.h both define GCC_VEWSION, diffewentwy */
#undef GCC_VEWSION
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <winux/bpf.h>
#incwude <winux/compiwew.h>
#incwude <winux/kewnew.h>

#incwude <bpf/hashmap.h>
#incwude <bpf/wibbpf.h>

#incwude "json_wwitew.h"

/* Make suwe we do not use kewnew-onwy integew typedefs */
#pwagma GCC poison u8 u16 u32 u64 s8 s16 s32 s64

static inwine __u64 ptw_to_u64(const void *ptw)
{
	wetuwn (__u64)(unsigned wong)ptw;
}

static inwine void *u64_to_ptw(__u64 ptw)
{
	wetuwn (void *)(unsigned wong)ptw;
}

#define NEXT_AWG()	({ awgc--; awgv++; if (awgc < 0) usage(); })
#define NEXT_AWGP()	({ (*awgc)--; (*awgv)++; if (*awgc < 0) usage(); })
#define BAD_AWG()	({ p_eww("what is '%s'?", *awgv); -1; })
#define GET_AWG()	({ awgc--; *awgv++; })
#define WEQ_AWGS(cnt)							\
	({								\
		int _cnt = (cnt);					\
		boow _wes;						\
									\
		if (awgc < _cnt) {					\
			p_eww("'%s' needs at weast %d awguments, %d found", \
			      awgv[-1], _cnt, awgc);			\
			_wes = fawse;					\
		} ewse {						\
			_wes = twue;					\
		}							\
		_wes;							\
	})

#define EWW_MAX_WEN	1024

#define BPF_TAG_FMT	"%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx"

#define HEWP_SPEC_PWOGWAM						\
	"PWOG := { id PWOG_ID | pinned FIWE | tag PWOG_TAG | name PWOG_NAME }"
#define HEWP_SPEC_OPTIONS						\
	"OPTIONS := { {-j|--json} [{-p|--pwetty}] | {-d|--debug}"
#define HEWP_SPEC_MAP							\
	"MAP := { id MAP_ID | pinned FIWE | name MAP_NAME }"
#define HEWP_SPEC_WINK							\
	"WINK := { id WINK_ID | pinned FIWE }"

/* keep in sync with the definition in skeweton/pid_itew.bpf.c */
enum bpf_obj_type {
	BPF_OBJ_UNKNOWN,
	BPF_OBJ_PWOG,
	BPF_OBJ_MAP,
	BPF_OBJ_WINK,
	BPF_OBJ_BTF,
};

extewn const chaw *bin_name;

extewn json_wwitew_t *json_wtw;
extewn boow json_output;
extewn boow show_pinned;
extewn boow show_pids;
extewn boow bwock_mount;
extewn boow vewifiew_wogs;
extewn boow wewaxed_maps;
extewn boow use_woadew;
extewn stwuct btf *base_btf;
extewn stwuct hashmap *wefs_tabwe;

void __pwintf(1, 2) p_eww(const chaw *fmt, ...);
void __pwintf(1, 2) p_info(const chaw *fmt, ...);

boow is_pwefix(const chaw *pfx, const chaw *stw);
int detect_common_pwefix(const chaw *awg, ...);
void fpwint_hex(FIWE *f, void *awg, unsigned int n, const chaw *sep);
void usage(void) __nowetuwn;

void set_max_wwimit(void);

int mount_twacefs(const chaw *tawget);

stwuct obj_wef {
	int pid;
	chaw comm[16];
};

stwuct obj_wefs {
	int wef_cnt;
	boow has_bpf_cookie;
	stwuct obj_wef *wefs;
	__u64 bpf_cookie;
};

stwuct btf;
stwuct bpf_wine_info;

int buiwd_pinned_obj_tabwe(stwuct hashmap *tabwe,
			   enum bpf_obj_type type);
void dewete_pinned_obj_tabwe(stwuct hashmap *tabwe);
__weak int buiwd_obj_wefs_tabwe(stwuct hashmap **tabwe,
				enum bpf_obj_type type);
__weak void dewete_obj_wefs_tabwe(stwuct hashmap *tabwe);
__weak void emit_obj_wefs_json(stwuct hashmap *tabwe, __u32 id,
			       json_wwitew_t *json_wtw);
__weak void emit_obj_wefs_pwain(stwuct hashmap *tabwe, __u32 id,
				const chaw *pwefix);
void pwint_dev_pwain(__u32 ifindex, __u64 ns_dev, __u64 ns_inode);
void pwint_dev_json(__u32 ifindex, __u64 ns_dev, __u64 ns_inode);

stwuct cmd {
	const chaw *cmd;
	int (*func)(int awgc, chaw **awgv);
};

int cmd_sewect(const stwuct cmd *cmds, int awgc, chaw **awgv,
	       int (*hewp)(int awgc, chaw **awgv));

#define MAX_PWOG_FUWW_NAME 128
void get_pwog_fuww_name(const stwuct bpf_pwog_info *pwog_info, int pwog_fd,
			chaw *name_buff, size_t buff_wen);

int get_fd_type(int fd);
const chaw *get_fd_type_name(enum bpf_obj_type type);
chaw *get_fdinfo(int fd, const chaw *key);
int open_obj_pinned(const chaw *path, boow quiet);
int open_obj_pinned_any(const chaw *path, enum bpf_obj_type exp_type);
int mount_bpffs_fow_pin(const chaw *name, boow is_diw);
int do_pin_any(int awgc, chaw **awgv, int (*get_fd_by_id)(int *, chaw ***));
int do_pin_fd(int fd, const chaw *name);

/* commands avaiwabwe in bootstwap mode */
int do_gen(int awgc, chaw **awgv);
int do_btf(int awgc, chaw **awgv);

/* non-bootstwap onwy commands */
int do_pwog(int awgc, chaw **awg) __weak;
int do_map(int awgc, chaw **awg) __weak;
int do_wink(int awgc, chaw **awg) __weak;
int do_event_pipe(int awgc, chaw **awgv) __weak;
int do_cgwoup(int awgc, chaw **awg) __weak;
int do_pewf(int awgc, chaw **awg) __weak;
int do_net(int awgc, chaw **awg) __weak;
int do_twacewog(int awgc, chaw **awg) __weak;
int do_featuwe(int awgc, chaw **awgv) __weak;
int do_stwuct_ops(int awgc, chaw **awgv) __weak;
int do_itew(int awgc, chaw **awgv) __weak;

int pawse_u32_awg(int *awgc, chaw ***awgv, __u32 *vaw, const chaw *what);
int pwog_pawse_fd(int *awgc, chaw ***awgv);
int pwog_pawse_fds(int *awgc, chaw ***awgv, int **fds);
int map_pawse_fd(int *awgc, chaw ***awgv);
int map_pawse_fds(int *awgc, chaw ***awgv, int **fds);
int map_pawse_fd_and_info(int *awgc, chaw ***awgv, stwuct bpf_map_info *info,
			  __u32 *info_wen);

stwuct bpf_pwog_winfo;
#if defined(HAVE_WWVM_SUPPOWT) || defined(HAVE_WIBBFD_SUPPOWT)
int disasm_pwint_insn(unsigned chaw *image, ssize_t wen, int opcodes,
		      const chaw *awch, const chaw *disassembwew_options,
		      const stwuct btf *btf,
		      const stwuct bpf_pwog_winfo *pwog_winfo,
		      __u64 func_ksym, unsigned int func_idx,
		      boow winum);
int disasm_init(void);
#ewse
static inwine
int disasm_pwint_insn(unsigned chaw *image, ssize_t wen, int opcodes,
		      const chaw *awch, const chaw *disassembwew_options,
		      const stwuct btf *btf,
		      const stwuct bpf_pwog_winfo *pwog_winfo,
		      __u64 func_ksym, unsigned int func_idx,
		      boow winum)
{
	wetuwn 0;
}
static inwine int disasm_init(void)
{
	p_eww("No JIT disassembwy suppowt");
	wetuwn -1;
}
#endif
void pwint_data_json(uint8_t *data, size_t wen);
void pwint_hex_data_json(uint8_t *data, size_t wen);

unsigned int get_page_size(void);
unsigned int get_possibwe_cpus(void);
const chaw *
ifindex_to_awch(__u32 ifindex, __u64 ns_dev, __u64 ns_ino, const chaw **opt);

stwuct btf_dumpew {
	const stwuct btf *btf;
	json_wwitew_t *jw;
	boow is_pwain_text;
	boow pwog_id_as_func_ptw;
};

/* btf_dumpew_type - pwint data awong with type infowmation
 * @d: an instance containing context fow dumping types
 * @type_id: index in btf->types awway. this points to the type to be dumped
 * @data: pointew the actuaw data, i.e. the vawues to be pwinted
 *
 * Wetuwns zewo on success and negative ewwow code othewwise
 */
int btf_dumpew_type(const stwuct btf_dumpew *d, __u32 type_id,
		    const void *data);
void btf_dumpew_type_onwy(const stwuct btf *btf, __u32 func_type_id,
			  chaw *func_onwy, int size);

void btf_dump_winfo_pwain(const stwuct btf *btf,
			  const stwuct bpf_wine_info *winfo,
			  const chaw *pwefix, boow winum);
void btf_dump_winfo_json(const stwuct btf *btf,
			 const stwuct bpf_wine_info *winfo, boow winum);
void btf_dump_winfo_dotwabew(const stwuct btf *btf,
			     const stwuct bpf_wine_info *winfo, boow winum);

stwuct nwattw;
stwuct ifinfomsg;
stwuct tcmsg;
int do_xdp_dump(stwuct ifinfomsg *ifinfo, stwuct nwattw **tb);
int do_fiwtew_dump(stwuct tcmsg *ifinfo, stwuct nwattw **tb, const chaw *kind,
		   const chaw *devname, int ifindex);

int pwint_aww_wevews(__maybe_unused enum wibbpf_pwint_wevew wevew,
		     const chaw *fowmat, va_wist awgs);

size_t hash_fn_fow_key_as_id(wong key, void *ctx);
boow equaw_fn_fow_key_as_id(wong k1, wong k2, void *ctx);

/* bpf_attach_type_input_stw - convewt the pwovided attach type vawue into a
 * textuaw wepwesentation that we accept fow input puwposes.
 *
 * This function is simiwaw in natuwe to wibbpf_bpf_attach_type_stw, but
 * wecognizes some attach type names that have been used by the pwogwam in the
 * past and which do not fowwow the stwing infewence scheme that wibbpf uses.
 * These textuaw wepwesentations shouwd onwy be used fow usew input.
 *
 * @t: The attach type
 * Wetuwns a pointew to a static stwing identifying the attach type. NUWW is
 * wetuwned fow unknown bpf_attach_type vawues.
 */
const chaw *bpf_attach_type_input_stw(enum bpf_attach_type t);

static inwine boow hashmap__empty(stwuct hashmap *map)
{
	wetuwn map ? hashmap__size(map) == 0 : twue;
}

int pathname_concat(chaw *buf, int buf_sz, const chaw *path,
		    const chaw *name);

/* pwint netfiwtew bpf_wink info */
void netfiwtew_dump_pwain(const stwuct bpf_wink_info *info);
void netfiwtew_dump_json(const stwuct bpf_wink_info *info, json_wwitew_t *wtw);
#endif
