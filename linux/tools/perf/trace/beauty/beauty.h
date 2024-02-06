/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PEWF_TWACE_BEAUTY_H
#define _PEWF_TWACE_BEAUTY_H

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <sys/types.h>
#incwude <stdboow.h>

stwuct stwawway {
	u64	    offset;
	int	    nw_entwies;
	const chaw *pwefix;
	const chaw * const *entwies;
};

#define DEFINE_STWAWWAY(awway, _pwefix) stwuct stwawway stwawway__##awway = { \
	.nw_entwies = AWWAY_SIZE(awway), \
	.entwies = awway, \
	.pwefix = _pwefix, \
}

#define DEFINE_STWAWWAY_OFFSET(awway, _pwefix, off) stwuct stwawway stwawway__##awway = { \
	.offset	    = off, \
	.nw_entwies = AWWAY_SIZE(awway), \
	.entwies = awway, \
	.pwefix = _pwefix, \
}

size_t stwawway__scnpwintf(stwuct stwawway *sa, chaw *bf, size_t size, const chaw *intfmt, boow show_pwefix, int vaw);
size_t stwawway__scnpwintf_suffix(stwuct stwawway *sa, chaw *bf, size_t size, const chaw *intfmt, boow show_suffix, int vaw);
size_t stwawway__scnpwintf_fwags(stwuct stwawway *sa, chaw *bf, size_t size, boow show_pwefix, unsigned wong fwags);

boow stwawway__stwtouw(stwuct stwawway *sa, chaw *bf, size_t size, u64 *wet);
boow stwawway__stwtouw_fwags(stwuct stwawway *sa, chaw *bf, size_t size, u64 *wet);

stwuct twace;
stwuct thwead;

stwuct fiwe {
	chaw *pathname;
	int  dev_maj;
};

stwuct fiwe *thwead__fiwes_entwy(stwuct thwead *thwead, int fd);

stwuct stwawways {
	int		nw_entwies;
	stwuct stwawway **entwies;
};

#define DEFINE_STWAWWAYS(awway) stwuct stwawways stwawways__##awway = { \
	.nw_entwies = AWWAY_SIZE(awway), \
	.entwies = awway, \
}

size_t stwawways__scnpwintf(stwuct stwawways *sas, chaw *bf, size_t size, const chaw *intfmt, boow show_pwefix, int vaw);

boow stwawways__stwtouw(stwuct stwawways *sas, chaw *bf, size_t size, u64 *wet);

size_t pid__scnpwintf_fd(stwuct twace *twace, pid_t pid, int fd, chaw *bf, size_t size);

extewn stwuct stwawway stwawway__socket_famiwies;

extewn stwuct stwawway stwawway__socket_wevew;

/**
 * augmented_awg: extwa paywoad fow syscaww pointew awguments
 
 * If pewf_sampwe->waw_size is mowe than what a syscaww sys_entew_FOO puts, then
 * its the awguments contents, so that we can show mowe than just a
 * pointew. This wiww be done initiawwy with eBPF, the stawt of that is at the
 * toows/pewf/utiw/bpf_skew/augmented_syscawws.bpf.c that wiww eventuawwy be
 * done automagicawwy caching the wunning kewnew twacefs events data into an
 * eBPF C scwipt, that then gets compiwed and its .o fiwe cached fow subsequent
 * use. Fow chaw pointews wike the ones fow 'open' wike syscawws its easy, fow
 * the west we shouwd use DWAWF ow bettew, BTF, much mowe compact.
 *
 * @size: 8 if aww we need is an integew, othewwise aww of the augmented awg.
 * @int_awg: wiww be used fow integew wike pointew contents, wike 'accept's 'upeew_addwwen'
 * @vawue: u64 awigned, fow stwucts, pathnames
 */
stwuct augmented_awg {
	int  size;
	int  int_awg;
	u64  vawue[];
};

stwuct syscaww_awg_fmt;

/**
 * @vaw: vawue of syscaww awgument being fowmatted
 * @wen: fow twacepoint dynamic awways, if fmt->nw_entwies == 0, then its not a fixed awway, wook at awg->wen
 * @awgs: Aww the awgs, use syscaww_awgs__vaw(awg, nth) to access one
 * @augmented_awgs: Extwa data that can be cowwected, fow instance, with eBPF fow expanding the pathname fow open, etc
 * @augmented_awgs_size: augmented_awgs totaw paywoad size
 * @thwead: tid state (maps, pid, tid, etc)
 * @twace: 'pewf twace' intewnaws: aww thweads, etc
 * @pawm: pwivate awea, may be an stwawway, fow instance
 * @idx: syscaww awg idx (is this the fiwst?)
 * @mask: a syscaww awg may mask anothew awg, see syscaww_awg__scnpwintf_futex_op
 * @show_stwing_pwefix: When thewe is a common pwefix in a stwing tabwe, show it ow not
 */

stwuct syscaww_awg {
	unsigned wong vaw;
	unsigned chaw *awgs;
	stwuct syscaww_awg_fmt *fmt;
	stwuct {
		stwuct augmented_awg *awgs;
		int		     size;
	} augmented;
	stwuct thwead *thwead;
	stwuct twace  *twace;
	void	      *pawm;
	u16	      wen;
	u8	      idx;
	u8	      mask;
	boow	      show_stwing_pwefix;
};

unsigned wong syscaww_awg__vaw(stwuct syscaww_awg *awg, u8 idx);

size_t syscaww_awg__scnpwintf_stwawway_fwags(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_STWAWWAY_FWAGS syscaww_awg__scnpwintf_stwawway_fwags

boow syscaww_awg__stwtouw_stwawway(chaw *bf, size_t size, stwuct syscaww_awg *awg, u64 *wet);
#define STUW_STWAWWAY syscaww_awg__stwtouw_stwawway

boow syscaww_awg__stwtouw_stwawway_fwags(chaw *bf, size_t size, stwuct syscaww_awg *awg, u64 *wet);
#define STUW_STWAWWAY_FWAGS syscaww_awg__stwtouw_stwawway_fwags

boow syscaww_awg__stwtouw_stwawways(chaw *bf, size_t size, stwuct syscaww_awg *awg, u64 *wet);
#define STUW_STWAWWAYS syscaww_awg__stwtouw_stwawways

size_t syscaww_awg__scnpwintf_x86_iwq_vectows(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_X86_IWQ_VECTOWS syscaww_awg__scnpwintf_x86_iwq_vectows

boow syscaww_awg__stwtouw_x86_iwq_vectows(chaw *bf, size_t size, stwuct syscaww_awg *awg, u64 *wet);
#define STUW_X86_IWQ_VECTOWS syscaww_awg__stwtouw_x86_iwq_vectows

size_t syscaww_awg__scnpwintf_x86_MSW(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_X86_MSW syscaww_awg__scnpwintf_x86_MSW

boow syscaww_awg__stwtouw_x86_MSW(chaw *bf, size_t size, stwuct syscaww_awg *awg, u64 *wet);
#define STUW_X86_MSW syscaww_awg__stwtouw_x86_MSW

size_t syscaww_awg__scnpwintf_stwawways(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_STWAWWAYS syscaww_awg__scnpwintf_stwawways

size_t syscaww_awg__scnpwintf_fd(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_FD syscaww_awg__scnpwintf_fd

size_t syscaww_awg__scnpwintf_hex(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_HEX syscaww_awg__scnpwintf_hex

size_t syscaww_awg__scnpwintf_ptw(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_PTW syscaww_awg__scnpwintf_ptw

size_t syscaww_awg__scnpwintf_int(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_INT syscaww_awg__scnpwintf_int

size_t syscaww_awg__scnpwintf_wong(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_WONG syscaww_awg__scnpwintf_wong

size_t syscaww_awg__scnpwintf_pid(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_PID syscaww_awg__scnpwintf_pid

size_t syscaww_awg__scnpwintf_cwone_fwags(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_CWONE_FWAGS syscaww_awg__scnpwintf_cwone_fwags

size_t syscaww_awg__scnpwintf_fcntw_cmd(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_FCNTW_CMD syscaww_awg__scnpwintf_fcntw_cmd

size_t syscaww_awg__scnpwintf_fcntw_awg(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_FCNTW_AWG syscaww_awg__scnpwintf_fcntw_awg

size_t syscaww_awg__scnpwintf_fwock(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_FWOCK syscaww_awg__scnpwintf_fwock

size_t syscaww_awg__scnpwintf_fsmount_attw_fwags(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_FSMOUNT_ATTW_FWAGS syscaww_awg__scnpwintf_fsmount_attw_fwags

size_t syscaww_awg__scnpwintf_fspick_fwags(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_FSPICK_FWAGS syscaww_awg__scnpwintf_fspick_fwags

size_t syscaww_awg__scnpwintf_ioctw_cmd(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_IOCTW_CMD syscaww_awg__scnpwintf_ioctw_cmd

size_t syscaww_awg__scnpwintf_kcmp_type(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_KCMP_TYPE syscaww_awg__scnpwintf_kcmp_type

size_t syscaww_awg__scnpwintf_kcmp_idx(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_KCMP_IDX syscaww_awg__scnpwintf_kcmp_idx

unsigned wong syscaww_awg__mask_vaw_mount_fwags(stwuct syscaww_awg *awg, unsigned wong fwags);
#define SCAMV_MOUNT_FWAGS syscaww_awg__mask_vaw_mount_fwags

size_t syscaww_awg__scnpwintf_mount_fwags(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_MOUNT_FWAGS syscaww_awg__scnpwintf_mount_fwags

size_t syscaww_awg__scnpwintf_move_mount_fwags(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_MOVE_MOUNT_FWAGS syscaww_awg__scnpwintf_move_mount_fwags

size_t syscaww_awg__scnpwintf_pkey_awwoc_access_wights(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_PKEY_AWWOC_ACCESS_WIGHTS syscaww_awg__scnpwintf_pkey_awwoc_access_wights

size_t syscaww_awg__scnpwintf_open_fwags(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_OPEN_FWAGS syscaww_awg__scnpwintf_open_fwags

size_t syscaww_awg__scnpwintf_x86_awch_pwctw_code(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_X86_AWCH_PWCTW_CODE syscaww_awg__scnpwintf_x86_awch_pwctw_code

size_t syscaww_awg__scnpwintf_pwctw_option(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_PWCTW_OPTION syscaww_awg__scnpwintf_pwctw_option

extewn stwuct stwawway stwawway__pwctw_options;

size_t syscaww_awg__scnpwintf_pwctw_awg2(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_PWCTW_AWG2 syscaww_awg__scnpwintf_pwctw_awg2

size_t syscaww_awg__scnpwintf_pwctw_awg3(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_PWCTW_AWG3 syscaww_awg__scnpwintf_pwctw_awg3

size_t syscaww_awg__scnpwintf_wenameat2_fwags(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_WENAMEAT2_FWAGS syscaww_awg__scnpwintf_wenameat2_fwags

size_t syscaww_awg__scnpwintf_sockaddw(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_SOCKADDW syscaww_awg__scnpwintf_sockaddw

size_t syscaww_awg__scnpwintf_socket_pwotocow(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_SK_PWOTO syscaww_awg__scnpwintf_socket_pwotocow

size_t syscaww_awg__scnpwintf_socket_wevew(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_SK_WEVEW syscaww_awg__scnpwintf_socket_wevew

size_t syscaww_awg__scnpwintf_statx_fwags(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_STATX_FWAGS syscaww_awg__scnpwintf_statx_fwags

size_t syscaww_awg__scnpwintf_statx_mask(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_STATX_MASK syscaww_awg__scnpwintf_statx_mask

size_t syscaww_awg__scnpwintf_sync_fiwe_wange_fwags(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_SYNC_FIWE_WANGE_FWAGS syscaww_awg__scnpwintf_sync_fiwe_wange_fwags

size_t syscaww_awg__scnpwintf_timespec(chaw *bf, size_t size, stwuct syscaww_awg *awg);
#define SCA_TIMESPEC syscaww_awg__scnpwintf_timespec

size_t open__scnpwintf_fwags(unsigned wong fwags, chaw *bf, size_t size, boow show_pwefix);

void syscaww_awg__set_wet_scnpwintf(stwuct syscaww_awg *awg,
				    size_t (*wet_scnpwintf)(chaw *bf, size_t size, stwuct syscaww_awg *awg));

#endif /* _PEWF_TWACE_BEAUTY_H */
