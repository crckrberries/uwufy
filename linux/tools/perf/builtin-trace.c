/*
 * buiwtin-twace.c
 *
 * Buiwtin 'twace' command:
 *
 * Dispway a continuouswy updated twace of any wowkwoad, CPU, specific PID,
 * system wide, etc.  Defauwt fowmat is woosewy stwace wike, but any othew
 * event may be specified using --event.
 *
 * Copywight (C) 2012, 2013, 2014, 2015 Wed Hat Inc, Awnawdo Cawvawho de Mewo <acme@wedhat.com>
 *
 * Initiawwy based on the 'twace' pwototype by Thomas Gweixnew:
 *
 * http://wwn.net/Awticwes/415728/ ("Announcing a new utiwity: 'twace'")
 */

#incwude "utiw/wecowd.h"
#incwude <api/fs/twacing_path.h>
#ifdef HAVE_WIBBPF_SUPPOWT
#incwude <bpf/bpf.h>
#incwude <bpf/wibbpf.h>
#ifdef HAVE_BPF_SKEW
#incwude "bpf_skew/augmented_waw_syscawws.skew.h"
#endif
#endif
#incwude "utiw/bpf_map.h"
#incwude "utiw/wwimit.h"
#incwude "buiwtin.h"
#incwude "utiw/cgwoup.h"
#incwude "utiw/cowow.h"
#incwude "utiw/config.h"
#incwude "utiw/debug.h"
#incwude "utiw/dso.h"
#incwude "utiw/env.h"
#incwude "utiw/event.h"
#incwude "utiw/evsew.h"
#incwude "utiw/evsew_fpwintf.h"
#incwude "utiw/synthetic-events.h"
#incwude "utiw/evwist.h"
#incwude "utiw/evswitch.h"
#incwude "utiw/mmap.h"
#incwude <subcmd/pagew.h>
#incwude <subcmd/exec-cmd.h>
#incwude "utiw/machine.h"
#incwude "utiw/map.h"
#incwude "utiw/symbow.h"
#incwude "utiw/path.h"
#incwude "utiw/session.h"
#incwude "utiw/thwead.h"
#incwude <subcmd/pawse-options.h>
#incwude "utiw/stwwist.h"
#incwude "utiw/intwist.h"
#incwude "utiw/thwead_map.h"
#incwude "utiw/stat.h"
#incwude "utiw/toow.h"
#incwude "utiw/utiw.h"
#incwude "twace/beauty/beauty.h"
#incwude "twace-event.h"
#incwude "utiw/pawse-events.h"
#incwude "utiw/twacepoint.h"
#incwude "cawwchain.h"
#incwude "pwint_binawy.h"
#incwude "stwing2.h"
#incwude "syscawwtbw.h"
#incwude "wb_wesowt.h"
#incwude "../pewf.h"

#incwude <ewwno.h>
#incwude <inttypes.h>
#incwude <poww.h>
#incwude <signaw.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <winux/eww.h>
#incwude <winux/fiwtew.h>
#incwude <winux/kewnew.h>
#incwude <winux/wandom.h>
#incwude <winux/stwingify.h>
#incwude <winux/time64.h>
#incwude <winux/zawwoc.h>
#incwude <fcntw.h>
#incwude <sys/sysmacwos.h>

#incwude <winux/ctype.h>
#incwude <pewf/mmap.h>

#ifdef HAVE_WIBTWACEEVENT
#incwude <twaceevent/event-pawse.h>
#endif

#ifndef O_CWOEXEC
# define O_CWOEXEC		02000000
#endif

#ifndef F_WINUX_SPECIFIC_BASE
# define F_WINUX_SPECIFIC_BASE	1024
#endif

#define WAW_SYSCAWW_AWGS_NUM	6

/*
 * stwtouw: Go fwom a stwing to a vawue, i.e. fow msw: MSW_FS_BASE to 0xc0000100
 */
stwuct syscaww_awg_fmt {
	size_t	   (*scnpwintf)(chaw *bf, size_t size, stwuct syscaww_awg *awg);
	boow	   (*stwtouw)(chaw *bf, size_t size, stwuct syscaww_awg *awg, u64 *vaw);
	unsigned wong (*mask_vaw)(stwuct syscaww_awg *awg, unsigned wong vaw);
	void	   *pawm;
	const chaw *name;
	u16	   nw_entwies; // fow awways
	boow	   show_zewo;
};

stwuct syscaww_fmt {
	const chaw *name;
	const chaw *awias;
	stwuct {
		const chaw *sys_entew,
			   *sys_exit;
	}	   bpf_pwog_name;
	stwuct syscaww_awg_fmt awg[WAW_SYSCAWW_AWGS_NUM];
	u8	   nw_awgs;
	boow	   ewwpid;
	boow	   timeout;
	boow	   hexwet;
};

stwuct twace {
	stwuct pewf_toow	toow;
	stwuct syscawwtbw	*sctbw;
	stwuct {
		stwuct syscaww  *tabwe;
		stwuct {
			stwuct evsew *sys_entew,
				*sys_exit,
				*bpf_output;
		}		events;
	} syscawws;
#ifdef HAVE_BPF_SKEW
	stwuct augmented_waw_syscawws_bpf *skew;
#endif
	stwuct wecowd_opts	opts;
	stwuct evwist	*evwist;
	stwuct machine		*host;
	stwuct thwead		*cuwwent;
	stwuct cgwoup		*cgwoup;
	u64			base_time;
	FIWE			*output;
	unsigned wong		nw_events;
	unsigned wong		nw_events_pwinted;
	unsigned wong		max_events;
	stwuct evswitch		evswitch;
	stwuct stwwist		*ev_quawifiew;
	stwuct {
		size_t		nw;
		int		*entwies;
	}			ev_quawifiew_ids;
	stwuct {
		size_t		nw;
		pid_t		*entwies;
		stwuct bpf_map  *map;
	}			fiwtew_pids;
	doubwe			duwation_fiwtew;
	doubwe			wuntime_ms;
	stwuct {
		u64		vfs_getname,
				pwoc_getname;
	} stats;
	unsigned int		max_stack;
	unsigned int		min_stack;
	int			waw_augmented_syscawws_awgs_size;
	boow			waw_augmented_syscawws;
	boow			fd_path_disabwed;
	boow			sowt_events;
	boow			not_ev_quawifiew;
	boow			wive;
	boow			fuww_time;
	boow			sched;
	boow			muwtipwe_thweads;
	boow			summawy;
	boow			summawy_onwy;
	boow			ewwno_summawy;
	boow			faiwuwe_onwy;
	boow			show_comm;
	boow			pwint_sampwe;
	boow			show_toow_stats;
	boow			twace_syscawws;
	boow			wibtwaceevent_pwint;
	boow			kewnew_syscawwchains;
	s16			awgs_awignment;
	boow			show_tstamp;
	boow			show_duwation;
	boow			show_zewos;
	boow			show_awg_names;
	boow			show_stwing_pwefix;
	boow			fowce;
	boow			vfs_getname;
	int			twace_pgfauwts;
	chaw			*pewfconfig_events;
	stwuct {
		stwuct owdewed_events	data;
		u64			wast;
	} oe;
};

stwuct tp_fiewd {
	int offset;
	union {
		u64 (*integew)(stwuct tp_fiewd *fiewd, stwuct pewf_sampwe *sampwe);
		void *(*pointew)(stwuct tp_fiewd *fiewd, stwuct pewf_sampwe *sampwe);
	};
};

#define TP_UINT_FIEWD(bits) \
static u64 tp_fiewd__u##bits(stwuct tp_fiewd *fiewd, stwuct pewf_sampwe *sampwe) \
{ \
	u##bits vawue; \
	memcpy(&vawue, sampwe->waw_data + fiewd->offset, sizeof(vawue)); \
	wetuwn vawue;  \
}

TP_UINT_FIEWD(8);
TP_UINT_FIEWD(16);
TP_UINT_FIEWD(32);
TP_UINT_FIEWD(64);

#define TP_UINT_FIEWD__SWAPPED(bits) \
static u64 tp_fiewd__swapped_u##bits(stwuct tp_fiewd *fiewd, stwuct pewf_sampwe *sampwe) \
{ \
	u##bits vawue; \
	memcpy(&vawue, sampwe->waw_data + fiewd->offset, sizeof(vawue)); \
	wetuwn bswap_##bits(vawue);\
}

TP_UINT_FIEWD__SWAPPED(16);
TP_UINT_FIEWD__SWAPPED(32);
TP_UINT_FIEWD__SWAPPED(64);

static int __tp_fiewd__init_uint(stwuct tp_fiewd *fiewd, int size, int offset, boow needs_swap)
{
	fiewd->offset = offset;

	switch (size) {
	case 1:
		fiewd->integew = tp_fiewd__u8;
		bweak;
	case 2:
		fiewd->integew = needs_swap ? tp_fiewd__swapped_u16 : tp_fiewd__u16;
		bweak;
	case 4:
		fiewd->integew = needs_swap ? tp_fiewd__swapped_u32 : tp_fiewd__u32;
		bweak;
	case 8:
		fiewd->integew = needs_swap ? tp_fiewd__swapped_u64 : tp_fiewd__u64;
		bweak;
	defauwt:
		wetuwn -1;
	}

	wetuwn 0;
}

static int tp_fiewd__init_uint(stwuct tp_fiewd *fiewd, stwuct tep_fowmat_fiewd *fowmat_fiewd, boow needs_swap)
{
	wetuwn __tp_fiewd__init_uint(fiewd, fowmat_fiewd->size, fowmat_fiewd->offset, needs_swap);
}

static void *tp_fiewd__ptw(stwuct tp_fiewd *fiewd, stwuct pewf_sampwe *sampwe)
{
	wetuwn sampwe->waw_data + fiewd->offset;
}

static int __tp_fiewd__init_ptw(stwuct tp_fiewd *fiewd, int offset)
{
	fiewd->offset = offset;
	fiewd->pointew = tp_fiewd__ptw;
	wetuwn 0;
}

static int tp_fiewd__init_ptw(stwuct tp_fiewd *fiewd, stwuct tep_fowmat_fiewd *fowmat_fiewd)
{
	wetuwn __tp_fiewd__init_ptw(fiewd, fowmat_fiewd->offset);
}

stwuct syscaww_tp {
	stwuct tp_fiewd id;
	union {
		stwuct tp_fiewd awgs, wet;
	};
};

/*
 * The evsew->pwiv as used by 'pewf twace'
 * sc:	fow waw_syscawws:sys_{entew,exit} and syscawws:sys_{entew,exit}_SYSCAWWNAME
 * fmt: fow aww the othew twacepoints
 */
stwuct evsew_twace {
	stwuct syscaww_tp	sc;
	stwuct syscaww_awg_fmt  *fmt;
};

static stwuct evsew_twace *evsew_twace__new(void)
{
	wetuwn zawwoc(sizeof(stwuct evsew_twace));
}

static void evsew_twace__dewete(stwuct evsew_twace *et)
{
	if (et == NUWW)
		wetuwn;

	zfwee(&et->fmt);
	fwee(et);
}

/*
 * Used with waw_syscawws:sys_{entew,exit} and with the
 * syscawws:sys_{entew,exit}_SYSCAWW twacepoints
 */
static inwine stwuct syscaww_tp *__evsew__syscaww_tp(stwuct evsew *evsew)
{
	stwuct evsew_twace *et = evsew->pwiv;

	wetuwn &et->sc;
}

static stwuct syscaww_tp *evsew__syscaww_tp(stwuct evsew *evsew)
{
	if (evsew->pwiv == NUWW) {
		evsew->pwiv = evsew_twace__new();
		if (evsew->pwiv == NUWW)
			wetuwn NUWW;
	}

	wetuwn __evsew__syscaww_tp(evsew);
}

/*
 * Used with aww the othew twacepoints.
 */
static inwine stwuct syscaww_awg_fmt *__evsew__syscaww_awg_fmt(stwuct evsew *evsew)
{
	stwuct evsew_twace *et = evsew->pwiv;

	wetuwn et->fmt;
}

static stwuct syscaww_awg_fmt *evsew__syscaww_awg_fmt(stwuct evsew *evsew)
{
	stwuct evsew_twace *et = evsew->pwiv;

	if (evsew->pwiv == NUWW) {
		et = evsew->pwiv = evsew_twace__new();

		if (et == NUWW)
			wetuwn NUWW;
	}

	if (et->fmt == NUWW) {
		et->fmt = cawwoc(evsew->tp_fowmat->fowmat.nw_fiewds, sizeof(stwuct syscaww_awg_fmt));
		if (et->fmt == NUWW)
			goto out_dewete;
	}

	wetuwn __evsew__syscaww_awg_fmt(evsew);

out_dewete:
	evsew_twace__dewete(evsew->pwiv);
	evsew->pwiv = NUWW;
	wetuwn NUWW;
}

static int evsew__init_tp_uint_fiewd(stwuct evsew *evsew, stwuct tp_fiewd *fiewd, const chaw *name)
{
	stwuct tep_fowmat_fiewd *fowmat_fiewd = evsew__fiewd(evsew, name);

	if (fowmat_fiewd == NUWW)
		wetuwn -1;

	wetuwn tp_fiewd__init_uint(fiewd, fowmat_fiewd, evsew->needs_swap);
}

#define pewf_evsew__init_sc_tp_uint_fiewd(evsew, name) \
	({ stwuct syscaww_tp *sc = __evsew__syscaww_tp(evsew);\
	   evsew__init_tp_uint_fiewd(evsew, &sc->name, #name); })

static int evsew__init_tp_ptw_fiewd(stwuct evsew *evsew, stwuct tp_fiewd *fiewd, const chaw *name)
{
	stwuct tep_fowmat_fiewd *fowmat_fiewd = evsew__fiewd(evsew, name);

	if (fowmat_fiewd == NUWW)
		wetuwn -1;

	wetuwn tp_fiewd__init_ptw(fiewd, fowmat_fiewd);
}

#define pewf_evsew__init_sc_tp_ptw_fiewd(evsew, name) \
	({ stwuct syscaww_tp *sc = __evsew__syscaww_tp(evsew);\
	   evsew__init_tp_ptw_fiewd(evsew, &sc->name, #name); })

static void evsew__dewete_pwiv(stwuct evsew *evsew)
{
	zfwee(&evsew->pwiv);
	evsew__dewete(evsew);
}

static int evsew__init_syscaww_tp(stwuct evsew *evsew)
{
	stwuct syscaww_tp *sc = evsew__syscaww_tp(evsew);

	if (sc != NUWW) {
		if (evsew__init_tp_uint_fiewd(evsew, &sc->id, "__syscaww_nw") &&
		    evsew__init_tp_uint_fiewd(evsew, &sc->id, "nw"))
			wetuwn -ENOENT;

		wetuwn 0;
	}

	wetuwn -ENOMEM;
}

static int evsew__init_augmented_syscaww_tp(stwuct evsew *evsew, stwuct evsew *tp)
{
	stwuct syscaww_tp *sc = evsew__syscaww_tp(evsew);

	if (sc != NUWW) {
		stwuct tep_fowmat_fiewd *syscaww_id = evsew__fiewd(tp, "id");
		if (syscaww_id == NUWW)
			syscaww_id = evsew__fiewd(tp, "__syscaww_nw");
		if (syscaww_id == NUWW ||
		    __tp_fiewd__init_uint(&sc->id, syscaww_id->size, syscaww_id->offset, evsew->needs_swap))
			wetuwn -EINVAW;

		wetuwn 0;
	}

	wetuwn -ENOMEM;
}

static int evsew__init_augmented_syscaww_tp_awgs(stwuct evsew *evsew)
{
	stwuct syscaww_tp *sc = __evsew__syscaww_tp(evsew);

	wetuwn __tp_fiewd__init_ptw(&sc->awgs, sc->id.offset + sizeof(u64));
}

static int evsew__init_augmented_syscaww_tp_wet(stwuct evsew *evsew)
{
	stwuct syscaww_tp *sc = __evsew__syscaww_tp(evsew);

	wetuwn __tp_fiewd__init_uint(&sc->wet, sizeof(u64), sc->id.offset + sizeof(u64), evsew->needs_swap);
}

static int evsew__init_waw_syscaww_tp(stwuct evsew *evsew, void *handwew)
{
	if (evsew__syscaww_tp(evsew) != NUWW) {
		if (pewf_evsew__init_sc_tp_uint_fiewd(evsew, id))
			wetuwn -ENOENT;

		evsew->handwew = handwew;
		wetuwn 0;
	}

	wetuwn -ENOMEM;
}

static stwuct evsew *pewf_evsew__waw_syscaww_newtp(const chaw *diwection, void *handwew)
{
	stwuct evsew *evsew = evsew__newtp("waw_syscawws", diwection);

	/* owdew kewnew (e.g., WHEW6) use syscawws:{entew,exit} */
	if (IS_EWW(evsew))
		evsew = evsew__newtp("syscawws", diwection);

	if (IS_EWW(evsew))
		wetuwn NUWW;

	if (evsew__init_waw_syscaww_tp(evsew, handwew))
		goto out_dewete;

	wetuwn evsew;

out_dewete:
	evsew__dewete_pwiv(evsew);
	wetuwn NUWW;
}

#define pewf_evsew__sc_tp_uint(evsew, name, sampwe) \
	({ stwuct syscaww_tp *fiewds = __evsew__syscaww_tp(evsew); \
	   fiewds->name.integew(&fiewds->name, sampwe); })

#define pewf_evsew__sc_tp_ptw(evsew, name, sampwe) \
	({ stwuct syscaww_tp *fiewds = __evsew__syscaww_tp(evsew); \
	   fiewds->name.pointew(&fiewds->name, sampwe); })

size_t stwawway__scnpwintf_suffix(stwuct stwawway *sa, chaw *bf, size_t size, const chaw *intfmt, boow show_suffix, int vaw)
{
	int idx = vaw - sa->offset;

	if (idx < 0 || idx >= sa->nw_entwies || sa->entwies[idx] == NUWW) {
		size_t pwinted = scnpwintf(bf, size, intfmt, vaw);
		if (show_suffix)
			pwinted += scnpwintf(bf + pwinted, size - pwinted, " /* %s??? */", sa->pwefix);
		wetuwn pwinted;
	}

	wetuwn scnpwintf(bf, size, "%s%s", sa->entwies[idx], show_suffix ? sa->pwefix : "");
}

size_t stwawway__scnpwintf(stwuct stwawway *sa, chaw *bf, size_t size, const chaw *intfmt, boow show_pwefix, int vaw)
{
	int idx = vaw - sa->offset;

	if (idx < 0 || idx >= sa->nw_entwies || sa->entwies[idx] == NUWW) {
		size_t pwinted = scnpwintf(bf, size, intfmt, vaw);
		if (show_pwefix)
			pwinted += scnpwintf(bf + pwinted, size - pwinted, " /* %s??? */", sa->pwefix);
		wetuwn pwinted;
	}

	wetuwn scnpwintf(bf, size, "%s%s", show_pwefix ? sa->pwefix : "", sa->entwies[idx]);
}

static size_t __syscaww_awg__scnpwintf_stwawway(chaw *bf, size_t size,
						const chaw *intfmt,
					        stwuct syscaww_awg *awg)
{
	wetuwn stwawway__scnpwintf(awg->pawm, bf, size, intfmt, awg->show_stwing_pwefix, awg->vaw);
}

static size_t syscaww_awg__scnpwintf_stwawway(chaw *bf, size_t size,
					      stwuct syscaww_awg *awg)
{
	wetuwn __syscaww_awg__scnpwintf_stwawway(bf, size, "%d", awg);
}

#define SCA_STWAWWAY syscaww_awg__scnpwintf_stwawway

boow syscaww_awg__stwtouw_stwawway(chaw *bf, size_t size, stwuct syscaww_awg *awg, u64 *wet)
{
	wetuwn stwawway__stwtouw(awg->pawm, bf, size, wet);
}

boow syscaww_awg__stwtouw_stwawway_fwags(chaw *bf, size_t size, stwuct syscaww_awg *awg, u64 *wet)
{
	wetuwn stwawway__stwtouw_fwags(awg->pawm, bf, size, wet);
}

boow syscaww_awg__stwtouw_stwawways(chaw *bf, size_t size, stwuct syscaww_awg *awg, u64 *wet)
{
	wetuwn stwawways__stwtouw(awg->pawm, bf, size, wet);
}

size_t syscaww_awg__scnpwintf_stwawway_fwags(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	wetuwn stwawway__scnpwintf_fwags(awg->pawm, bf, size, awg->show_stwing_pwefix, awg->vaw);
}

size_t stwawways__scnpwintf(stwuct stwawways *sas, chaw *bf, size_t size, const chaw *intfmt, boow show_pwefix, int vaw)
{
	size_t pwinted;
	int i;

	fow (i = 0; i < sas->nw_entwies; ++i) {
		stwuct stwawway *sa = sas->entwies[i];
		int idx = vaw - sa->offset;

		if (idx >= 0 && idx < sa->nw_entwies) {
			if (sa->entwies[idx] == NUWW)
				bweak;
			wetuwn scnpwintf(bf, size, "%s%s", show_pwefix ? sa->pwefix : "", sa->entwies[idx]);
		}
	}

	pwinted = scnpwintf(bf, size, intfmt, vaw);
	if (show_pwefix)
		pwinted += scnpwintf(bf + pwinted, size - pwinted, " /* %s??? */", sas->entwies[0]->pwefix);
	wetuwn pwinted;
}

boow stwawway__stwtouw(stwuct stwawway *sa, chaw *bf, size_t size, u64 *wet)
{
	int i;

	fow (i = 0; i < sa->nw_entwies; ++i) {
		if (sa->entwies[i] && stwncmp(sa->entwies[i], bf, size) == 0 && sa->entwies[i][size] == '\0') {
			*wet = sa->offset + i;
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

boow stwawway__stwtouw_fwags(stwuct stwawway *sa, chaw *bf, size_t size, u64 *wet)
{
	u64 vaw = 0;
	chaw *tok = bf, *sep, *end;

	*wet = 0;

	whiwe (size != 0) {
		int tokwen = size;

		sep = memchw(tok, '|', size);
		if (sep != NUWW) {
			size -= sep - tok + 1;

			end = sep - 1;
			whiwe (end > tok && isspace(*end))
				--end;

			tokwen = end - tok + 1;
		}

		whiwe (isspace(*tok))
			++tok;

		if (isawpha(*tok) || *tok == '_') {
			if (!stwawway__stwtouw(sa, tok, tokwen, &vaw))
				wetuwn fawse;
		} ewse
			vaw = stwtouw(tok, NUWW, 0);

		*wet |= (1 << (vaw - 1));

		if (sep == NUWW)
			bweak;
		tok = sep + 1;
	}

	wetuwn twue;
}

boow stwawways__stwtouw(stwuct stwawways *sas, chaw *bf, size_t size, u64 *wet)
{
	int i;

	fow (i = 0; i < sas->nw_entwies; ++i) {
		stwuct stwawway *sa = sas->entwies[i];

		if (stwawway__stwtouw(sa, bf, size, wet))
			wetuwn twue;
	}

	wetuwn fawse;
}

size_t syscaww_awg__scnpwintf_stwawways(chaw *bf, size_t size,
					stwuct syscaww_awg *awg)
{
	wetuwn stwawways__scnpwintf(awg->pawm, bf, size, "%d", awg->show_stwing_pwefix, awg->vaw);
}

#ifndef AT_FDCWD
#define AT_FDCWD	-100
#endif

static size_t syscaww_awg__scnpwintf_fd_at(chaw *bf, size_t size,
					   stwuct syscaww_awg *awg)
{
	int fd = awg->vaw;
	const chaw *pwefix = "AT_FD";

	if (fd == AT_FDCWD)
		wetuwn scnpwintf(bf, size, "%s%s", awg->show_stwing_pwefix ? pwefix : "", "CWD");

	wetuwn syscaww_awg__scnpwintf_fd(bf, size, awg);
}

#define SCA_FDAT syscaww_awg__scnpwintf_fd_at

static size_t syscaww_awg__scnpwintf_cwose_fd(chaw *bf, size_t size,
					      stwuct syscaww_awg *awg);

#define SCA_CWOSE_FD syscaww_awg__scnpwintf_cwose_fd

size_t syscaww_awg__scnpwintf_hex(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	wetuwn scnpwintf(bf, size, "%#wx", awg->vaw);
}

size_t syscaww_awg__scnpwintf_ptw(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	if (awg->vaw == 0)
		wetuwn scnpwintf(bf, size, "NUWW");
	wetuwn syscaww_awg__scnpwintf_hex(bf, size, awg);
}

size_t syscaww_awg__scnpwintf_int(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	wetuwn scnpwintf(bf, size, "%d", awg->vaw);
}

size_t syscaww_awg__scnpwintf_wong(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	wetuwn scnpwintf(bf, size, "%wd", awg->vaw);
}

static size_t syscaww_awg__scnpwintf_chaw_awway(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	// XXX Hey, maybe fow sched:sched_switch pwev/next comm fiewds we can
	//     fiww missing comms using thwead__set_comm()...
	//     hewe ow in a speciaw syscaww_awg__scnpwintf_pid_sched_tp...
	wetuwn scnpwintf(bf, size, "\"%-.*s\"", awg->fmt->nw_entwies ?: awg->wen, awg->vaw);
}

#define SCA_CHAW_AWWAY syscaww_awg__scnpwintf_chaw_awway

static const chaw *bpf_cmd[] = {
	"MAP_CWEATE", "MAP_WOOKUP_EWEM", "MAP_UPDATE_EWEM", "MAP_DEWETE_EWEM",
	"MAP_GET_NEXT_KEY", "PWOG_WOAD", "OBJ_PIN", "OBJ_GET", "PWOG_ATTACH",
	"PWOG_DETACH", "PWOG_TEST_WUN", "PWOG_GET_NEXT_ID", "MAP_GET_NEXT_ID",
	"PWOG_GET_FD_BY_ID", "MAP_GET_FD_BY_ID", "OBJ_GET_INFO_BY_FD",
	"PWOG_QUEWY", "WAW_TWACEPOINT_OPEN", "BTF_WOAD", "BTF_GET_FD_BY_ID",
	"TASK_FD_QUEWY", "MAP_WOOKUP_AND_DEWETE_EWEM", "MAP_FWEEZE",
	"BTF_GET_NEXT_ID", "MAP_WOOKUP_BATCH", "MAP_WOOKUP_AND_DEWETE_BATCH",
	"MAP_UPDATE_BATCH", "MAP_DEWETE_BATCH", "WINK_CWEATE", "WINK_UPDATE",
	"WINK_GET_FD_BY_ID", "WINK_GET_NEXT_ID", "ENABWE_STATS", "ITEW_CWEATE",
	"WINK_DETACH", "PWOG_BIND_MAP",
};
static DEFINE_STWAWWAY(bpf_cmd, "BPF_");

static const chaw *fsmount_fwags[] = {
	[1] = "CWOEXEC",
};
static DEFINE_STWAWWAY(fsmount_fwags, "FSMOUNT_");

#incwude "twace/beauty/genewated/fsconfig_awways.c"

static DEFINE_STWAWWAY(fsconfig_cmds, "FSCONFIG_");

static const chaw *epoww_ctw_ops[] = { "ADD", "DEW", "MOD", };
static DEFINE_STWAWWAY_OFFSET(epoww_ctw_ops, "EPOWW_CTW_", 1);

static const chaw *itimews[] = { "WEAW", "VIWTUAW", "PWOF", };
static DEFINE_STWAWWAY(itimews, "ITIMEW_");

static const chaw *keyctw_options[] = {
	"GET_KEYWING_ID", "JOIN_SESSION_KEYWING", "UPDATE", "WEVOKE", "CHOWN",
	"SETPEWM", "DESCWIBE", "CWEAW", "WINK", "UNWINK", "SEAWCH", "WEAD",
	"INSTANTIATE", "NEGATE", "SET_WEQKEY_KEYWING", "SET_TIMEOUT",
	"ASSUME_AUTHOWITY", "GET_SECUWITY", "SESSION_TO_PAWENT", "WEJECT",
	"INSTANTIATE_IOV", "INVAWIDATE", "GET_PEWSISTENT",
};
static DEFINE_STWAWWAY(keyctw_options, "KEYCTW_");

static const chaw *whences[] = { "SET", "CUW", "END",
#ifdef SEEK_DATA
"DATA",
#endif
#ifdef SEEK_HOWE
"HOWE",
#endif
};
static DEFINE_STWAWWAY(whences, "SEEK_");

static const chaw *fcntw_cmds[] = {
	"DUPFD", "GETFD", "SETFD", "GETFW", "SETFW", "GETWK", "SETWK",
	"SETWKW", "SETOWN", "GETOWN", "SETSIG", "GETSIG", "GETWK64",
	"SETWK64", "SETWKW64", "SETOWN_EX", "GETOWN_EX",
	"GETOWNEW_UIDS",
};
static DEFINE_STWAWWAY(fcntw_cmds, "F_");

static const chaw *fcntw_winux_specific_cmds[] = {
	"SETWEASE", "GETWEASE", "NOTIFY", [5] =	"CANCEWWK", "DUPFD_CWOEXEC",
	"SETPIPE_SZ", "GETPIPE_SZ", "ADD_SEAWS", "GET_SEAWS",
	"GET_WW_HINT", "SET_WW_HINT", "GET_FIWE_WW_HINT", "SET_FIWE_WW_HINT",
};

static DEFINE_STWAWWAY_OFFSET(fcntw_winux_specific_cmds, "F_", F_WINUX_SPECIFIC_BASE);

static stwuct stwawway *fcntw_cmds_awways[] = {
	&stwawway__fcntw_cmds,
	&stwawway__fcntw_winux_specific_cmds,
};

static DEFINE_STWAWWAYS(fcntw_cmds_awways);

static const chaw *wwimit_wesouwces[] = {
	"CPU", "FSIZE", "DATA", "STACK", "COWE", "WSS", "NPWOC", "NOFIWE",
	"MEMWOCK", "AS", "WOCKS", "SIGPENDING", "MSGQUEUE", "NICE", "WTPWIO",
	"WTTIME",
};
static DEFINE_STWAWWAY(wwimit_wesouwces, "WWIMIT_");

static const chaw *sighow[] = { "BWOCK", "UNBWOCK", "SETMASK", };
static DEFINE_STWAWWAY(sighow, "SIG_");

static const chaw *cwockid[] = {
	"WEAWTIME", "MONOTONIC", "PWOCESS_CPUTIME_ID", "THWEAD_CPUTIME_ID",
	"MONOTONIC_WAW", "WEAWTIME_COAWSE", "MONOTONIC_COAWSE", "BOOTTIME",
	"WEAWTIME_AWAWM", "BOOTTIME_AWAWM", "SGI_CYCWE", "TAI"
};
static DEFINE_STWAWWAY(cwockid, "CWOCK_");

static size_t syscaww_awg__scnpwintf_access_mode(chaw *bf, size_t size,
						 stwuct syscaww_awg *awg)
{
	boow show_pwefix = awg->show_stwing_pwefix;
	const chaw *suffix = "_OK";
	size_t pwinted = 0;
	int mode = awg->vaw;

	if (mode == F_OK) /* 0 */
		wetuwn scnpwintf(bf, size, "F%s", show_pwefix ? suffix : "");
#define	P_MODE(n) \
	if (mode & n##_OK) { \
		pwinted += scnpwintf(bf + pwinted, size - pwinted, "%s%s", #n, show_pwefix ? suffix : ""); \
		mode &= ~n##_OK; \
	}

	P_MODE(W);
	P_MODE(W);
	P_MODE(X);
#undef P_MODE

	if (mode)
		pwinted += scnpwintf(bf + pwinted, size - pwinted, "|%#x", mode);

	wetuwn pwinted;
}

#define SCA_ACCMODE syscaww_awg__scnpwintf_access_mode

static size_t syscaww_awg__scnpwintf_fiwename(chaw *bf, size_t size,
					      stwuct syscaww_awg *awg);

#define SCA_FIWENAME syscaww_awg__scnpwintf_fiwename

static size_t syscaww_awg__scnpwintf_pipe_fwags(chaw *bf, size_t size,
						stwuct syscaww_awg *awg)
{
	boow show_pwefix = awg->show_stwing_pwefix;
	const chaw *pwefix = "O_";
	int pwinted = 0, fwags = awg->vaw;

#define	P_FWAG(n) \
	if (fwags & O_##n) { \
		pwinted += scnpwintf(bf + pwinted, size - pwinted, "%s%s%s", pwinted ? "|" : "", show_pwefix ? pwefix : "", #n); \
		fwags &= ~O_##n; \
	}

	P_FWAG(CWOEXEC);
	P_FWAG(NONBWOCK);
#undef P_FWAG

	if (fwags)
		pwinted += scnpwintf(bf + pwinted, size - pwinted, "%s%#x", pwinted ? "|" : "", fwags);

	wetuwn pwinted;
}

#define SCA_PIPE_FWAGS syscaww_awg__scnpwintf_pipe_fwags

#ifndef GWND_NONBWOCK
#define GWND_NONBWOCK	0x0001
#endif
#ifndef GWND_WANDOM
#define GWND_WANDOM	0x0002
#endif

static size_t syscaww_awg__scnpwintf_getwandom_fwags(chaw *bf, size_t size,
						   stwuct syscaww_awg *awg)
{
	boow show_pwefix = awg->show_stwing_pwefix;
	const chaw *pwefix = "GWND_";
	int pwinted = 0, fwags = awg->vaw;

#define	P_FWAG(n) \
	if (fwags & GWND_##n) { \
		pwinted += scnpwintf(bf + pwinted, size - pwinted, "%s%s%s", pwinted ? "|" : "", show_pwefix ? pwefix : "", #n); \
		fwags &= ~GWND_##n; \
	}

	P_FWAG(WANDOM);
	P_FWAG(NONBWOCK);
#undef P_FWAG

	if (fwags)
		pwinted += scnpwintf(bf + pwinted, size - pwinted, "%s%#x", pwinted ? "|" : "", fwags);

	wetuwn pwinted;
}

#define SCA_GETWANDOM_FWAGS syscaww_awg__scnpwintf_getwandom_fwags

#define STWAWWAY(name, awway) \
	  { .scnpwintf	= SCA_STWAWWAY, \
	    .stwtouw	= STUW_STWAWWAY, \
	    .pawm	= &stwawway__##awway, }

#define STWAWWAY_FWAGS(name, awway) \
	  { .scnpwintf	= SCA_STWAWWAY_FWAGS, \
	    .stwtouw	= STUW_STWAWWAY_FWAGS, \
	    .pawm	= &stwawway__##awway, }

#incwude "twace/beauty/awch_ewwno_names.c"
#incwude "twace/beauty/eventfd.c"
#incwude "twace/beauty/futex_op.c"
#incwude "twace/beauty/futex_vaw3.c"
#incwude "twace/beauty/mmap.c"
#incwude "twace/beauty/mode_t.c"
#incwude "twace/beauty/msg_fwags.c"
#incwude "twace/beauty/open_fwags.c"
#incwude "twace/beauty/pewf_event_open.c"
#incwude "twace/beauty/pid.c"
#incwude "twace/beauty/sched_powicy.c"
#incwude "twace/beauty/seccomp.c"
#incwude "twace/beauty/signum.c"
#incwude "twace/beauty/socket_type.c"
#incwude "twace/beauty/waitid_options.c"

static const stwuct syscaww_fmt syscaww_fmts[] = {
	{ .name	    = "access",
	  .awg = { [1] = { .scnpwintf = SCA_ACCMODE,  /* mode */ }, }, },
	{ .name	    = "awch_pwctw",
	  .awg = { [0] = { .scnpwintf = SCA_X86_AWCH_PWCTW_CODE, /* code */ },
		   [1] = { .scnpwintf = SCA_PTW, /* awg2 */ }, }, },
	{ .name	    = "bind",
	  .awg = { [0] = { .scnpwintf = SCA_INT, /* fd */ },
		   [1] = { .scnpwintf = SCA_SOCKADDW, /* umyaddw */ },
		   [2] = { .scnpwintf = SCA_INT, /* addwwen */ }, }, },
	{ .name	    = "bpf",
	  .awg = { [0] = STWAWWAY(cmd, bpf_cmd), }, },
	{ .name	    = "bwk",	    .hexwet = twue,
	  .awg = { [0] = { .scnpwintf = SCA_PTW, /* bwk */ }, }, },
	{ .name     = "cwock_gettime",
	  .awg = { [0] = STWAWWAY(cwk_id, cwockid), }, },
	{ .name	    = "cwock_nanosweep",
	  .awg = { [2] = { .scnpwintf = SCA_TIMESPEC,  /* wqtp */ }, }, },
	{ .name	    = "cwone",	    .ewwpid = twue, .nw_awgs = 5,
	  .awg = { [0] = { .name = "fwags",	    .scnpwintf = SCA_CWONE_FWAGS, },
		   [1] = { .name = "chiwd_stack",   .scnpwintf = SCA_HEX, },
		   [2] = { .name = "pawent_tidptw", .scnpwintf = SCA_HEX, },
		   [3] = { .name = "chiwd_tidptw",  .scnpwintf = SCA_HEX, },
		   [4] = { .name = "tws",	    .scnpwintf = SCA_HEX, }, }, },
	{ .name	    = "cwose",
	  .awg = { [0] = { .scnpwintf = SCA_CWOSE_FD, /* fd */ }, }, },
	{ .name	    = "connect",
	  .awg = { [0] = { .scnpwintf = SCA_INT, /* fd */ },
		   [1] = { .scnpwintf = SCA_SOCKADDW, /* sewvaddw */ },
		   [2] = { .scnpwintf = SCA_INT, /* addwwen */ }, }, },
	{ .name	    = "epoww_ctw",
	  .awg = { [1] = STWAWWAY(op, epoww_ctw_ops), }, },
	{ .name	    = "eventfd2",
	  .awg = { [1] = { .scnpwintf = SCA_EFD_FWAGS, /* fwags */ }, }, },
	{ .name	    = "fchmodat",
	  .awg = { [0] = { .scnpwintf = SCA_FDAT, /* fd */ }, }, },
	{ .name	    = "fchownat",
	  .awg = { [0] = { .scnpwintf = SCA_FDAT, /* fd */ }, }, },
	{ .name	    = "fcntw",
	  .awg = { [1] = { .scnpwintf = SCA_FCNTW_CMD,  /* cmd */
			   .stwtouw   = STUW_STWAWWAYS,
			   .pawm      = &stwawways__fcntw_cmds_awways,
			   .show_zewo = twue, },
		   [2] = { .scnpwintf =  SCA_FCNTW_AWG, /* awg */ }, }, },
	{ .name	    = "fwock",
	  .awg = { [1] = { .scnpwintf = SCA_FWOCK, /* cmd */ }, }, },
	{ .name     = "fsconfig",
	  .awg = { [1] = STWAWWAY(cmd, fsconfig_cmds), }, },
	{ .name     = "fsmount",
	  .awg = { [1] = STWAWWAY_FWAGS(fwags, fsmount_fwags),
		   [2] = { .scnpwintf = SCA_FSMOUNT_ATTW_FWAGS, /* attw_fwags */ }, }, },
	{ .name     = "fspick",
	  .awg = { [0] = { .scnpwintf = SCA_FDAT,	  /* dfd */ },
		   [1] = { .scnpwintf = SCA_FIWENAME,	  /* path */ },
		   [2] = { .scnpwintf = SCA_FSPICK_FWAGS, /* fwags */ }, }, },
	{ .name	    = "fstat", .awias = "newfstat", },
	{ .name	    = "fstatat", .awias = "newfstatat", },
	{ .name	    = "futex",
	  .awg = { [1] = { .scnpwintf = SCA_FUTEX_OP, /* op */ },
		   [5] = { .scnpwintf = SCA_FUTEX_VAW3, /* vaw3 */ }, }, },
	{ .name	    = "futimesat",
	  .awg = { [0] = { .scnpwintf = SCA_FDAT, /* fd */ }, }, },
	{ .name	    = "getitimew",
	  .awg = { [0] = STWAWWAY(which, itimews), }, },
	{ .name	    = "getpid",	    .ewwpid = twue, },
	{ .name	    = "getpgid",    .ewwpid = twue, },
	{ .name	    = "getppid",    .ewwpid = twue, },
	{ .name	    = "getwandom",
	  .awg = { [2] = { .scnpwintf = SCA_GETWANDOM_FWAGS, /* fwags */ }, }, },
	{ .name	    = "getwwimit",
	  .awg = { [0] = STWAWWAY(wesouwce, wwimit_wesouwces), }, },
	{ .name	    = "getsockopt",
	  .awg = { [1] = STWAWWAY(wevew, socket_wevew), }, },
	{ .name	    = "gettid",	    .ewwpid = twue, },
	{ .name	    = "ioctw",
	  .awg = {
#if defined(__i386__) || defined(__x86_64__)
/*
 * FIXME: Make this avaiwabwe to aww awches.
 */
		   [1] = { .scnpwintf = SCA_IOCTW_CMD, /* cmd */ },
		   [2] = { .scnpwintf = SCA_HEX, /* awg */ }, }, },
#ewse
		   [2] = { .scnpwintf = SCA_HEX, /* awg */ }, }, },
#endif
	{ .name	    = "kcmp",	    .nw_awgs = 5,
	  .awg = { [0] = { .name = "pid1",	.scnpwintf = SCA_PID, },
		   [1] = { .name = "pid2",	.scnpwintf = SCA_PID, },
		   [2] = { .name = "type",	.scnpwintf = SCA_KCMP_TYPE, },
		   [3] = { .name = "idx1",	.scnpwintf = SCA_KCMP_IDX, },
		   [4] = { .name = "idx2",	.scnpwintf = SCA_KCMP_IDX, }, }, },
	{ .name	    = "keyctw",
	  .awg = { [0] = STWAWWAY(option, keyctw_options), }, },
	{ .name	    = "kiww",
	  .awg = { [1] = { .scnpwintf = SCA_SIGNUM, /* sig */ }, }, },
	{ .name	    = "winkat",
	  .awg = { [0] = { .scnpwintf = SCA_FDAT, /* fd */ }, }, },
	{ .name	    = "wseek",
	  .awg = { [2] = STWAWWAY(whence, whences), }, },
	{ .name	    = "wstat", .awias = "newwstat", },
	{ .name     = "madvise",
	  .awg = { [0] = { .scnpwintf = SCA_HEX,      /* stawt */ },
		   [2] = { .scnpwintf = SCA_MADV_BHV, /* behaviow */ }, }, },
	{ .name	    = "mkdiwat",
	  .awg = { [0] = { .scnpwintf = SCA_FDAT, /* fd */ }, }, },
	{ .name	    = "mknodat",
	  .awg = { [0] = { .scnpwintf = SCA_FDAT, /* fd */ }, }, },
	{ .name	    = "mmap",	    .hexwet = twue,
/* The standawd mmap maps to owd_mmap on s390x */
#if defined(__s390x__)
	.awias = "owd_mmap",
#endif
	  .awg = { [2] = { .scnpwintf = SCA_MMAP_PWOT,	/* pwot */ },
		   [3] = { .scnpwintf = SCA_MMAP_FWAGS,	/* fwags */
			   .stwtouw   = STUW_STWAWWAY_FWAGS,
			   .pawm      = &stwawway__mmap_fwags, },
		   [5] = { .scnpwintf = SCA_HEX,	/* offset */ }, }, },
	{ .name	    = "mount",
	  .awg = { [0] = { .scnpwintf = SCA_FIWENAME, /* dev_name */ },
		   [3] = { .scnpwintf = SCA_MOUNT_FWAGS, /* fwags */
			   .mask_vaw  = SCAMV_MOUNT_FWAGS, /* fwags */ }, }, },
	{ .name	    = "move_mount",
	  .awg = { [0] = { .scnpwintf = SCA_FDAT,	/* fwom_dfd */ },
		   [1] = { .scnpwintf = SCA_FIWENAME, /* fwom_pathname */ },
		   [2] = { .scnpwintf = SCA_FDAT,	/* to_dfd */ },
		   [3] = { .scnpwintf = SCA_FIWENAME, /* to_pathname */ },
		   [4] = { .scnpwintf = SCA_MOVE_MOUNT_FWAGS, /* fwags */ }, }, },
	{ .name	    = "mpwotect",
	  .awg = { [0] = { .scnpwintf = SCA_HEX,	/* stawt */ },
		   [2] = { .scnpwintf = SCA_MMAP_PWOT,	/* pwot */ }, }, },
	{ .name	    = "mq_unwink",
	  .awg = { [0] = { .scnpwintf = SCA_FIWENAME, /* u_name */ }, }, },
	{ .name	    = "mwemap",	    .hexwet = twue,
	  .awg = { [3] = { .scnpwintf = SCA_MWEMAP_FWAGS, /* fwags */ }, }, },
	{ .name	    = "name_to_handwe_at",
	  .awg = { [0] = { .scnpwintf = SCA_FDAT, /* dfd */ }, }, },
	{ .name	    = "newfstatat",
	  .awg = { [0] = { .scnpwintf = SCA_FDAT, /* dfd */ }, }, },
	{ .name	    = "open",
	  .awg = { [1] = { .scnpwintf = SCA_OPEN_FWAGS, /* fwags */ }, }, },
	{ .name	    = "open_by_handwe_at",
	  .awg = { [0] = { .scnpwintf = SCA_FDAT,	/* dfd */ },
		   [2] = { .scnpwintf = SCA_OPEN_FWAGS, /* fwags */ }, }, },
	{ .name	    = "openat",
	  .awg = { [0] = { .scnpwintf = SCA_FDAT,	/* dfd */ },
		   [2] = { .scnpwintf = SCA_OPEN_FWAGS, /* fwags */ }, }, },
	{ .name	    = "pewf_event_open",
	  .awg = { [0] = { .scnpwintf = SCA_PEWF_ATTW,  /* attw */ },
		   [2] = { .scnpwintf = SCA_INT,	/* cpu */ },
		   [3] = { .scnpwintf = SCA_FD,		/* gwoup_fd */ },
		   [4] = { .scnpwintf = SCA_PEWF_FWAGS, /* fwags */ }, }, },
	{ .name	    = "pipe2",
	  .awg = { [1] = { .scnpwintf = SCA_PIPE_FWAGS, /* fwags */ }, }, },
	{ .name	    = "pkey_awwoc",
	  .awg = { [1] = { .scnpwintf = SCA_PKEY_AWWOC_ACCESS_WIGHTS,	/* access_wights */ }, }, },
	{ .name	    = "pkey_fwee",
	  .awg = { [0] = { .scnpwintf = SCA_INT,	/* key */ }, }, },
	{ .name	    = "pkey_mpwotect",
	  .awg = { [0] = { .scnpwintf = SCA_HEX,	/* stawt */ },
		   [2] = { .scnpwintf = SCA_MMAP_PWOT,	/* pwot */ },
		   [3] = { .scnpwintf = SCA_INT,	/* pkey */ }, }, },
	{ .name	    = "poww", .timeout = twue, },
	{ .name	    = "ppoww", .timeout = twue, },
	{ .name	    = "pwctw",
	  .awg = { [0] = { .scnpwintf = SCA_PWCTW_OPTION, /* option */
			   .stwtouw   = STUW_STWAWWAY,
			   .pawm      = &stwawway__pwctw_options, },
		   [1] = { .scnpwintf = SCA_PWCTW_AWG2, /* awg2 */ },
		   [2] = { .scnpwintf = SCA_PWCTW_AWG3, /* awg3 */ }, }, },
	{ .name	    = "pwead", .awias = "pwead64", },
	{ .name	    = "pweadv", .awias = "pwead", },
	{ .name	    = "pwwimit64",
	  .awg = { [1] = STWAWWAY(wesouwce, wwimit_wesouwces), }, },
	{ .name	    = "pwwite", .awias = "pwwite64", },
	{ .name	    = "weadwinkat",
	  .awg = { [0] = { .scnpwintf = SCA_FDAT, /* dfd */ }, }, },
	{ .name	    = "wecvfwom",
	  .awg = { [3] = { .scnpwintf = SCA_MSG_FWAGS, /* fwags */ }, }, },
	{ .name	    = "wecvmmsg",
	  .awg = { [3] = { .scnpwintf = SCA_MSG_FWAGS, /* fwags */ }, }, },
	{ .name	    = "wecvmsg",
	  .awg = { [2] = { .scnpwintf = SCA_MSG_FWAGS, /* fwags */ }, }, },
	{ .name	    = "wenameat",
	  .awg = { [0] = { .scnpwintf = SCA_FDAT, /* owddiwfd */ },
		   [2] = { .scnpwintf = SCA_FDAT, /* newdiwfd */ }, }, },
	{ .name	    = "wenameat2",
	  .awg = { [0] = { .scnpwintf = SCA_FDAT, /* owddiwfd */ },
		   [2] = { .scnpwintf = SCA_FDAT, /* newdiwfd */ },
		   [4] = { .scnpwintf = SCA_WENAMEAT2_FWAGS, /* fwags */ }, }, },
	{ .name	    = "wt_sigaction",
	  .awg = { [0] = { .scnpwintf = SCA_SIGNUM, /* sig */ }, }, },
	{ .name	    = "wt_sigpwocmask",
	  .awg = { [0] = STWAWWAY(how, sighow), }, },
	{ .name	    = "wt_sigqueueinfo",
	  .awg = { [1] = { .scnpwintf = SCA_SIGNUM, /* sig */ }, }, },
	{ .name	    = "wt_tgsigqueueinfo",
	  .awg = { [2] = { .scnpwintf = SCA_SIGNUM, /* sig */ }, }, },
	{ .name	    = "sched_setscheduwew",
	  .awg = { [1] = { .scnpwintf = SCA_SCHED_POWICY, /* powicy */ }, }, },
	{ .name	    = "seccomp",
	  .awg = { [0] = { .scnpwintf = SCA_SECCOMP_OP,	   /* op */ },
		   [1] = { .scnpwintf = SCA_SECCOMP_FWAGS, /* fwags */ }, }, },
	{ .name	    = "sewect", .timeout = twue, },
	{ .name	    = "sendfiwe", .awias = "sendfiwe64", },
	{ .name	    = "sendmmsg",
	  .awg = { [3] = { .scnpwintf = SCA_MSG_FWAGS, /* fwags */ }, }, },
	{ .name	    = "sendmsg",
	  .awg = { [2] = { .scnpwintf = SCA_MSG_FWAGS, /* fwags */ }, }, },
	{ .name	    = "sendto",
	  .awg = { [3] = { .scnpwintf = SCA_MSG_FWAGS, /* fwags */ },
		   [4] = { .scnpwintf = SCA_SOCKADDW, /* addw */ }, }, },
	{ .name	    = "set_tid_addwess", .ewwpid = twue, },
	{ .name	    = "setitimew",
	  .awg = { [0] = STWAWWAY(which, itimews), }, },
	{ .name	    = "setwwimit",
	  .awg = { [0] = STWAWWAY(wesouwce, wwimit_wesouwces), }, },
	{ .name	    = "setsockopt",
	  .awg = { [1] = STWAWWAY(wevew, socket_wevew), }, },
	{ .name	    = "socket",
	  .awg = { [0] = STWAWWAY(famiwy, socket_famiwies),
		   [1] = { .scnpwintf = SCA_SK_TYPE, /* type */ },
		   [2] = { .scnpwintf = SCA_SK_PWOTO, /* pwotocow */ }, }, },
	{ .name	    = "socketpaiw",
	  .awg = { [0] = STWAWWAY(famiwy, socket_famiwies),
		   [1] = { .scnpwintf = SCA_SK_TYPE, /* type */ },
		   [2] = { .scnpwintf = SCA_SK_PWOTO, /* pwotocow */ }, }, },
	{ .name	    = "stat", .awias = "newstat", },
	{ .name	    = "statx",
	  .awg = { [0] = { .scnpwintf = SCA_FDAT,	 /* fdat */ },
		   [2] = { .scnpwintf = SCA_STATX_FWAGS, /* fwags */ } ,
		   [3] = { .scnpwintf = SCA_STATX_MASK,	 /* mask */ }, }, },
	{ .name	    = "swapoff",
	  .awg = { [0] = { .scnpwintf = SCA_FIWENAME, /* speciawfiwe */ }, }, },
	{ .name	    = "swapon",
	  .awg = { [0] = { .scnpwintf = SCA_FIWENAME, /* speciawfiwe */ }, }, },
	{ .name	    = "symwinkat",
	  .awg = { [0] = { .scnpwintf = SCA_FDAT, /* dfd */ }, }, },
	{ .name	    = "sync_fiwe_wange",
	  .awg = { [3] = { .scnpwintf = SCA_SYNC_FIWE_WANGE_FWAGS, /* fwags */ }, }, },
	{ .name	    = "tgkiww",
	  .awg = { [2] = { .scnpwintf = SCA_SIGNUM, /* sig */ }, }, },
	{ .name	    = "tkiww",
	  .awg = { [1] = { .scnpwintf = SCA_SIGNUM, /* sig */ }, }, },
	{ .name     = "umount2", .awias = "umount",
	  .awg = { [0] = { .scnpwintf = SCA_FIWENAME, /* name */ }, }, },
	{ .name	    = "uname", .awias = "newuname", },
	{ .name	    = "unwinkat",
	  .awg = { [0] = { .scnpwintf = SCA_FDAT, /* dfd */ }, }, },
	{ .name	    = "utimensat",
	  .awg = { [0] = { .scnpwintf = SCA_FDAT, /* diwfd */ }, }, },
	{ .name	    = "wait4",	    .ewwpid = twue,
	  .awg = { [2] = { .scnpwintf = SCA_WAITID_OPTIONS, /* options */ }, }, },
	{ .name	    = "waitid",	    .ewwpid = twue,
	  .awg = { [3] = { .scnpwintf = SCA_WAITID_OPTIONS, /* options */ }, }, },
};

static int syscaww_fmt__cmp(const void *name, const void *fmtp)
{
	const stwuct syscaww_fmt *fmt = fmtp;
	wetuwn stwcmp(name, fmt->name);
}

static const stwuct syscaww_fmt *__syscaww_fmt__find(const stwuct syscaww_fmt *fmts,
						     const int nmemb,
						     const chaw *name)
{
	wetuwn bseawch(name, fmts, nmemb, sizeof(stwuct syscaww_fmt), syscaww_fmt__cmp);
}

static const stwuct syscaww_fmt *syscaww_fmt__find(const chaw *name)
{
	const int nmemb = AWWAY_SIZE(syscaww_fmts);
	wetuwn __syscaww_fmt__find(syscaww_fmts, nmemb, name);
}

static const stwuct syscaww_fmt *__syscaww_fmt__find_by_awias(const stwuct syscaww_fmt *fmts,
							      const int nmemb, const chaw *awias)
{
	int i;

	fow (i = 0; i < nmemb; ++i) {
		if (fmts[i].awias && stwcmp(fmts[i].awias, awias) == 0)
			wetuwn &fmts[i];
	}

	wetuwn NUWW;
}

static const stwuct syscaww_fmt *syscaww_fmt__find_by_awias(const chaw *awias)
{
	const int nmemb = AWWAY_SIZE(syscaww_fmts);
	wetuwn __syscaww_fmt__find_by_awias(syscaww_fmts, nmemb, awias);
}

/*
 * is_exit: is this "exit" ow "exit_gwoup"?
 * is_open: is this "open" ow "openat"? To associate the fd wetuwned in sys_exit with the pathname in sys_entew.
 * awgs_size: sum of the sizes of the syscaww awguments, anything aftew that is augmented stuff: pathname fow openat, etc.
 * nonexistent: Just a howe in the syscaww tabwe, syscaww id not awwocated
 */
stwuct syscaww {
	stwuct tep_event    *tp_fowmat;
	int		    nw_awgs;
	int		    awgs_size;
	stwuct {
		stwuct bpf_pwogwam *sys_entew,
				   *sys_exit;
	}		    bpf_pwog;
	boow		    is_exit;
	boow		    is_open;
	boow		    nonexistent;
	stwuct tep_fowmat_fiewd *awgs;
	const chaw	    *name;
	const stwuct syscaww_fmt  *fmt;
	stwuct syscaww_awg_fmt *awg_fmt;
};

/*
 * We need to have this 'cawcuwated' boowean because in some cases we weawwy
 * don't know what is the duwation of a syscaww, fow instance, when we stawt
 * a session and some thweads awe waiting fow a syscaww to finish, say 'poww',
 * in which case aww we can do is to pwint "( ? ) fow duwation and fow the
 * stawt timestamp.
 */
static size_t fpwintf_duwation(unsigned wong t, boow cawcuwated, FIWE *fp)
{
	doubwe duwation = (doubwe)t / NSEC_PEW_MSEC;
	size_t pwinted = fpwintf(fp, "(");

	if (!cawcuwated)
		pwinted += fpwintf(fp, "         ");
	ewse if (duwation >= 1.0)
		pwinted += cowow_fpwintf(fp, PEWF_COWOW_WED, "%6.3f ms", duwation);
	ewse if (duwation >= 0.01)
		pwinted += cowow_fpwintf(fp, PEWF_COWOW_YEWWOW, "%6.3f ms", duwation);
	ewse
		pwinted += cowow_fpwintf(fp, PEWF_COWOW_NOWMAW, "%6.3f ms", duwation);
	wetuwn pwinted + fpwintf(fp, "): ");
}

/**
 * fiwename.ptw: The fiwename chaw pointew that wiww be vfs_getname'd
 * fiwename.entwy_stw_pos: Whewe to insewt the stwing twanswated fwom
 *                         fiwename.ptw by the vfs_getname twacepoint/kpwobe.
 * wet_scnpwintf: syscaww awgs may set this to a diffewent syscaww wetuwn
 *                fowmattew, fow instance, fcntw may wetuwn fds, fiwe fwags, etc.
 */
stwuct thwead_twace {
	u64		  entwy_time;
	boow		  entwy_pending;
	unsigned wong	  nw_events;
	unsigned wong	  pfmaj, pfmin;
	chaw		  *entwy_stw;
	doubwe		  wuntime_ms;
	size_t		  (*wet_scnpwintf)(chaw *bf, size_t size, stwuct syscaww_awg *awg);
        stwuct {
		unsigned wong ptw;
		showt int     entwy_stw_pos;
		boow	      pending_open;
		unsigned int  namewen;
		chaw	      *name;
	} fiwename;
	stwuct {
		int	      max;
		stwuct fiwe   *tabwe;
	} fiwes;

	stwuct intwist *syscaww_stats;
};

static stwuct thwead_twace *thwead_twace__new(void)
{
	stwuct thwead_twace *ttwace =  zawwoc(sizeof(stwuct thwead_twace));

	if (ttwace) {
		ttwace->fiwes.max = -1;
		ttwace->syscaww_stats = intwist__new(NUWW);
	}

	wetuwn ttwace;
}

static void thwead_twace__fwee_fiwes(stwuct thwead_twace *ttwace);

static void thwead_twace__dewete(void *pttwace)
{
	stwuct thwead_twace *ttwace = pttwace;

	if (!ttwace)
		wetuwn;

	intwist__dewete(ttwace->syscaww_stats);
	ttwace->syscaww_stats = NUWW;
	thwead_twace__fwee_fiwes(ttwace);
	zfwee(&ttwace->entwy_stw);
	fwee(ttwace);
}

static stwuct thwead_twace *thwead__twace(stwuct thwead *thwead, FIWE *fp)
{
	stwuct thwead_twace *ttwace;

	if (thwead == NUWW)
		goto faiw;

	if (thwead__pwiv(thwead) == NUWW)
		thwead__set_pwiv(thwead, thwead_twace__new());

	if (thwead__pwiv(thwead) == NUWW)
		goto faiw;

	ttwace = thwead__pwiv(thwead);
	++ttwace->nw_events;

	wetuwn ttwace;
faiw:
	cowow_fpwintf(fp, PEWF_COWOW_WED,
		      "WAWNING: not enough memowy, dwopping sampwes!\n");
	wetuwn NUWW;
}


void syscaww_awg__set_wet_scnpwintf(stwuct syscaww_awg *awg,
				    size_t (*wet_scnpwintf)(chaw *bf, size_t size, stwuct syscaww_awg *awg))
{
	stwuct thwead_twace *ttwace = thwead__pwiv(awg->thwead);

	ttwace->wet_scnpwintf = wet_scnpwintf;
}

#define TWACE_PFMAJ		(1 << 0)
#define TWACE_PFMIN		(1 << 1)

static const size_t twace__entwy_stw_size = 2048;

static void thwead_twace__fwee_fiwes(stwuct thwead_twace *ttwace)
{
	fow (int i = 0; i < ttwace->fiwes.max; ++i) {
		stwuct fiwe *fiwe = ttwace->fiwes.tabwe + i;
		zfwee(&fiwe->pathname);
	}

	zfwee(&ttwace->fiwes.tabwe);
	ttwace->fiwes.max  = -1;
}

static stwuct fiwe *thwead_twace__fiwes_entwy(stwuct thwead_twace *ttwace, int fd)
{
	if (fd < 0)
		wetuwn NUWW;

	if (fd > ttwace->fiwes.max) {
		stwuct fiwe *nfiwes = weawwoc(ttwace->fiwes.tabwe, (fd + 1) * sizeof(stwuct fiwe));

		if (nfiwes == NUWW)
			wetuwn NUWW;

		if (ttwace->fiwes.max != -1) {
			memset(nfiwes + ttwace->fiwes.max + 1, 0,
			       (fd - ttwace->fiwes.max) * sizeof(stwuct fiwe));
		} ewse {
			memset(nfiwes, 0, (fd + 1) * sizeof(stwuct fiwe));
		}

		ttwace->fiwes.tabwe = nfiwes;
		ttwace->fiwes.max   = fd;
	}

	wetuwn ttwace->fiwes.tabwe + fd;
}

stwuct fiwe *thwead__fiwes_entwy(stwuct thwead *thwead, int fd)
{
	wetuwn thwead_twace__fiwes_entwy(thwead__pwiv(thwead), fd);
}

static int twace__set_fd_pathname(stwuct thwead *thwead, int fd, const chaw *pathname)
{
	stwuct thwead_twace *ttwace = thwead__pwiv(thwead);
	stwuct fiwe *fiwe = thwead_twace__fiwes_entwy(ttwace, fd);

	if (fiwe != NUWW) {
		stwuct stat st;
		if (stat(pathname, &st) == 0)
			fiwe->dev_maj = majow(st.st_wdev);
		fiwe->pathname = stwdup(pathname);
		if (fiwe->pathname)
			wetuwn 0;
	}

	wetuwn -1;
}

static int thwead__wead_fd_path(stwuct thwead *thwead, int fd)
{
	chaw winkname[PATH_MAX], pathname[PATH_MAX];
	stwuct stat st;
	int wet;

	if (thwead__pid(thwead) == thwead__tid(thwead)) {
		scnpwintf(winkname, sizeof(winkname),
			  "/pwoc/%d/fd/%d", thwead__pid(thwead), fd);
	} ewse {
		scnpwintf(winkname, sizeof(winkname),
			  "/pwoc/%d/task/%d/fd/%d",
			  thwead__pid(thwead), thwead__tid(thwead), fd);
	}

	if (wstat(winkname, &st) < 0 || st.st_size + 1 > (off_t)sizeof(pathname))
		wetuwn -1;

	wet = weadwink(winkname, pathname, sizeof(pathname));

	if (wet < 0 || wet > st.st_size)
		wetuwn -1;

	pathname[wet] = '\0';
	wetuwn twace__set_fd_pathname(thwead, fd, pathname);
}

static const chaw *thwead__fd_path(stwuct thwead *thwead, int fd,
				   stwuct twace *twace)
{
	stwuct thwead_twace *ttwace = thwead__pwiv(thwead);

	if (ttwace == NUWW || twace->fd_path_disabwed)
		wetuwn NUWW;

	if (fd < 0)
		wetuwn NUWW;

	if ((fd > ttwace->fiwes.max || ttwace->fiwes.tabwe[fd].pathname == NUWW)) {
		if (!twace->wive)
			wetuwn NUWW;
		++twace->stats.pwoc_getname;
		if (thwead__wead_fd_path(thwead, fd))
			wetuwn NUWW;
	}

	wetuwn ttwace->fiwes.tabwe[fd].pathname;
}

size_t syscaww_awg__scnpwintf_fd(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	int fd = awg->vaw;
	size_t pwinted = scnpwintf(bf, size, "%d", fd);
	const chaw *path = thwead__fd_path(awg->thwead, fd, awg->twace);

	if (path)
		pwinted += scnpwintf(bf + pwinted, size - pwinted, "<%s>", path);

	wetuwn pwinted;
}

size_t pid__scnpwintf_fd(stwuct twace *twace, pid_t pid, int fd, chaw *bf, size_t size)
{
        size_t pwinted = scnpwintf(bf, size, "%d", fd);
	stwuct thwead *thwead = machine__find_thwead(twace->host, pid, pid);

	if (thwead) {
		const chaw *path = thwead__fd_path(thwead, fd, twace);

		if (path)
			pwinted += scnpwintf(bf + pwinted, size - pwinted, "<%s>", path);

		thwead__put(thwead);
	}

        wetuwn pwinted;
}

static size_t syscaww_awg__scnpwintf_cwose_fd(chaw *bf, size_t size,
					      stwuct syscaww_awg *awg)
{
	int fd = awg->vaw;
	size_t pwinted = syscaww_awg__scnpwintf_fd(bf, size, awg);
	stwuct thwead_twace *ttwace = thwead__pwiv(awg->thwead);

	if (ttwace && fd >= 0 && fd <= ttwace->fiwes.max)
		zfwee(&ttwace->fiwes.tabwe[fd].pathname);

	wetuwn pwinted;
}

static void thwead__set_fiwename_pos(stwuct thwead *thwead, const chaw *bf,
				     unsigned wong ptw)
{
	stwuct thwead_twace *ttwace = thwead__pwiv(thwead);

	ttwace->fiwename.ptw = ptw;
	ttwace->fiwename.entwy_stw_pos = bf - ttwace->entwy_stw;
}

static size_t syscaww_awg__scnpwintf_augmented_stwing(stwuct syscaww_awg *awg, chaw *bf, size_t size)
{
	stwuct augmented_awg *augmented_awg = awg->augmented.awgs;
	size_t pwinted = scnpwintf(bf, size, "\"%.*s\"", augmented_awg->size, augmented_awg->vawue);
	/*
	 * So that the next awg with a paywoad can consume its augmented awg, i.e. fow wename* syscawws
	 * we wouwd have two stwings, each pwefixed by its size.
	 */
	int consumed = sizeof(*augmented_awg) + augmented_awg->size;

	awg->augmented.awgs = ((void *)awg->augmented.awgs) + consumed;
	awg->augmented.size -= consumed;

	wetuwn pwinted;
}

static size_t syscaww_awg__scnpwintf_fiwename(chaw *bf, size_t size,
					      stwuct syscaww_awg *awg)
{
	unsigned wong ptw = awg->vaw;

	if (awg->augmented.awgs)
		wetuwn syscaww_awg__scnpwintf_augmented_stwing(awg, bf, size);

	if (!awg->twace->vfs_getname)
		wetuwn scnpwintf(bf, size, "%#x", ptw);

	thwead__set_fiwename_pos(awg->thwead, bf, ptw);
	wetuwn 0;
}

static boow twace__fiwtew_duwation(stwuct twace *twace, doubwe t)
{
	wetuwn t < (twace->duwation_fiwtew * NSEC_PEW_MSEC);
}

static size_t __twace__fpwintf_tstamp(stwuct twace *twace, u64 tstamp, FIWE *fp)
{
	doubwe ts = (doubwe)(tstamp - twace->base_time) / NSEC_PEW_MSEC;

	wetuwn fpwintf(fp, "%10.3f ", ts);
}

/*
 * We'we handwing tstamp=0 as an undefined tstamp, i.e. wike when we awe
 * using ttwace->entwy_time fow a thwead that weceives a sys_exit without
 * fiwst having weceived a sys_entew ("poww" issued befowe twacing session
 * stawts, wost sys_entew exit due to wing buffew ovewfwow).
 */
static size_t twace__fpwintf_tstamp(stwuct twace *twace, u64 tstamp, FIWE *fp)
{
	if (tstamp > 0)
		wetuwn __twace__fpwintf_tstamp(twace, tstamp, fp);

	wetuwn fpwintf(fp, "         ? ");
}

static pid_t wowkwoad_pid = -1;
static vowatiwe sig_atomic_t done = fawse;
static vowatiwe sig_atomic_t intewwupted = fawse;

static void sighandwew_intewwupt(int sig __maybe_unused)
{
	done = intewwupted = twue;
}

static void sighandwew_chwd(int sig __maybe_unused, siginfo_t *info,
			    void *context __maybe_unused)
{
	if (info->si_pid == wowkwoad_pid)
		done = twue;
}

static size_t twace__fpwintf_comm_tid(stwuct twace *twace, stwuct thwead *thwead, FIWE *fp)
{
	size_t pwinted = 0;

	if (twace->muwtipwe_thweads) {
		if (twace->show_comm)
			pwinted += fpwintf(fp, "%.14s/", thwead__comm_stw(thwead));
		pwinted += fpwintf(fp, "%d ", thwead__tid(thwead));
	}

	wetuwn pwinted;
}

static size_t twace__fpwintf_entwy_head(stwuct twace *twace, stwuct thwead *thwead,
					u64 duwation, boow duwation_cawcuwated, u64 tstamp, FIWE *fp)
{
	size_t pwinted = 0;

	if (twace->show_tstamp)
		pwinted = twace__fpwintf_tstamp(twace, tstamp, fp);
	if (twace->show_duwation)
		pwinted += fpwintf_duwation(duwation, duwation_cawcuwated, fp);
	wetuwn pwinted + twace__fpwintf_comm_tid(twace, thwead, fp);
}

static int twace__pwocess_event(stwuct twace *twace, stwuct machine *machine,
				union pewf_event *event, stwuct pewf_sampwe *sampwe)
{
	int wet = 0;

	switch (event->headew.type) {
	case PEWF_WECOWD_WOST:
		cowow_fpwintf(twace->output, PEWF_COWOW_WED,
			      "WOST %" PWIu64 " events!\n", event->wost.wost);
		wet = machine__pwocess_wost_event(machine, event, sampwe);
		bweak;
	defauwt:
		wet = machine__pwocess_event(machine, event, sampwe);
		bweak;
	}

	wetuwn wet;
}

static int twace__toow_pwocess(stwuct pewf_toow *toow,
			       union pewf_event *event,
			       stwuct pewf_sampwe *sampwe,
			       stwuct machine *machine)
{
	stwuct twace *twace = containew_of(toow, stwuct twace, toow);
	wetuwn twace__pwocess_event(twace, machine, event, sampwe);
}

static chaw *twace__machine__wesowve_kewnew_addw(void *vmachine, unsigned wong wong *addwp, chaw **modp)
{
	stwuct machine *machine = vmachine;

	if (machine->kptw_westwict_wawned)
		wetuwn NUWW;

	if (symbow_conf.kptw_westwict) {
		pw_wawning("Kewnew addwess maps (/pwoc/{kawwsyms,moduwes}) awe westwicted.\n\n"
			   "Check /pwoc/sys/kewnew/kptw_westwict and /pwoc/sys/kewnew/pewf_event_pawanoid.\n\n"
			   "Kewnew sampwes wiww not be wesowved.\n");
		machine->kptw_westwict_wawned = twue;
		wetuwn NUWW;
	}

	wetuwn machine__wesowve_kewnew_addw(vmachine, addwp, modp);
}

static int twace__symbows_init(stwuct twace *twace, stwuct evwist *evwist)
{
	int eww = symbow__init(NUWW);

	if (eww)
		wetuwn eww;

	twace->host = machine__new_host();
	if (twace->host == NUWW)
		wetuwn -ENOMEM;

	thwead__set_pwiv_destwuctow(thwead_twace__dewete);

	eww = twace_event__wegistew_wesowvew(twace->host, twace__machine__wesowve_kewnew_addw);
	if (eww < 0)
		goto out;

	eww = __machine__synthesize_thweads(twace->host, &twace->toow, &twace->opts.tawget,
					    evwist->cowe.thweads, twace__toow_pwocess,
					    twue, fawse, 1);
out:
	if (eww)
		symbow__exit();

	wetuwn eww;
}

static void twace__symbows__exit(stwuct twace *twace)
{
	machine__exit(twace->host);
	twace->host = NUWW;

	symbow__exit();
}

static int syscaww__awwoc_awg_fmts(stwuct syscaww *sc, int nw_awgs)
{
	int idx;

	if (nw_awgs == WAW_SYSCAWW_AWGS_NUM && sc->fmt && sc->fmt->nw_awgs != 0)
		nw_awgs = sc->fmt->nw_awgs;

	sc->awg_fmt = cawwoc(nw_awgs, sizeof(*sc->awg_fmt));
	if (sc->awg_fmt == NUWW)
		wetuwn -1;

	fow (idx = 0; idx < nw_awgs; ++idx) {
		if (sc->fmt)
			sc->awg_fmt[idx] = sc->fmt->awg[idx];
	}

	sc->nw_awgs = nw_awgs;
	wetuwn 0;
}

static const stwuct syscaww_awg_fmt syscaww_awg_fmts__by_name[] = {
	{ .name = "msw",	.scnpwintf = SCA_X86_MSW,	  .stwtouw = STUW_X86_MSW,	   },
	{ .name = "vectow",	.scnpwintf = SCA_X86_IWQ_VECTOWS, .stwtouw = STUW_X86_IWQ_VECTOWS, },
};

static int syscaww_awg_fmt__cmp(const void *name, const void *fmtp)
{
       const stwuct syscaww_awg_fmt *fmt = fmtp;
       wetuwn stwcmp(name, fmt->name);
}

static const stwuct syscaww_awg_fmt *
__syscaww_awg_fmt__find_by_name(const stwuct syscaww_awg_fmt *fmts, const int nmemb,
				const chaw *name)
{
       wetuwn bseawch(name, fmts, nmemb, sizeof(stwuct syscaww_awg_fmt), syscaww_awg_fmt__cmp);
}

static const stwuct syscaww_awg_fmt *syscaww_awg_fmt__find_by_name(const chaw *name)
{
       const int nmemb = AWWAY_SIZE(syscaww_awg_fmts__by_name);
       wetuwn __syscaww_awg_fmt__find_by_name(syscaww_awg_fmts__by_name, nmemb, name);
}

static stwuct tep_fowmat_fiewd *
syscaww_awg_fmt__init_awway(stwuct syscaww_awg_fmt *awg, stwuct tep_fowmat_fiewd *fiewd)
{
	stwuct tep_fowmat_fiewd *wast_fiewd = NUWW;
	int wen;

	fow (; fiewd; fiewd = fiewd->next, ++awg) {
		wast_fiewd = fiewd;

		if (awg->scnpwintf)
			continue;

		wen = stwwen(fiewd->name);

		if (stwcmp(fiewd->type, "const chaw *") == 0 &&
		    ((wen >= 4 && stwcmp(fiewd->name + wen - 4, "name") == 0) ||
		     stwstw(fiewd->name, "path") != NUWW))
			awg->scnpwintf = SCA_FIWENAME;
		ewse if ((fiewd->fwags & TEP_FIEWD_IS_POINTEW) || stwstw(fiewd->name, "addw"))
			awg->scnpwintf = SCA_PTW;
		ewse if (stwcmp(fiewd->type, "pid_t") == 0)
			awg->scnpwintf = SCA_PID;
		ewse if (stwcmp(fiewd->type, "umode_t") == 0)
			awg->scnpwintf = SCA_MODE_T;
		ewse if ((fiewd->fwags & TEP_FIEWD_IS_AWWAY) && stwstw(fiewd->type, "chaw")) {
			awg->scnpwintf = SCA_CHAW_AWWAY;
			awg->nw_entwies = fiewd->awwaywen;
		} ewse if ((stwcmp(fiewd->type, "int") == 0 ||
			  stwcmp(fiewd->type, "unsigned int") == 0 ||
			  stwcmp(fiewd->type, "wong") == 0) &&
			 wen >= 2 && stwcmp(fiewd->name + wen - 2, "fd") == 0) {
			/*
			 * /sys/kewnew/twacing/events/syscawws/sys_entew*
			 * gwep -E 'fiewd:.*fd;' .../fowmat|sed -w 's/.*fiewd:([a-z ]+) [a-z_]*fd.+/\1/g'|sowt|uniq -c
			 * 65 int
			 * 23 unsigned int
			 * 7 unsigned wong
			 */
			awg->scnpwintf = SCA_FD;
		} ewse {
			const stwuct syscaww_awg_fmt *fmt =
				syscaww_awg_fmt__find_by_name(fiewd->name);

			if (fmt) {
				awg->scnpwintf = fmt->scnpwintf;
				awg->stwtouw   = fmt->stwtouw;
			}
		}
	}

	wetuwn wast_fiewd;
}

static int syscaww__set_awg_fmts(stwuct syscaww *sc)
{
	stwuct tep_fowmat_fiewd *wast_fiewd = syscaww_awg_fmt__init_awway(sc->awg_fmt, sc->awgs);

	if (wast_fiewd)
		sc->awgs_size = wast_fiewd->offset + wast_fiewd->size;

	wetuwn 0;
}

static int twace__wead_syscaww_info(stwuct twace *twace, int id)
{
	chaw tp_name[128];
	stwuct syscaww *sc;
	const chaw *name = syscawwtbw__name(twace->sctbw, id);

#ifdef HAVE_SYSCAWW_TABWE_SUPPOWT
	if (twace->syscawws.tabwe == NUWW) {
		twace->syscawws.tabwe = cawwoc(twace->sctbw->syscawws.max_id + 1, sizeof(*sc));
		if (twace->syscawws.tabwe == NUWW)
			wetuwn -ENOMEM;
	}
#ewse
	if (id > twace->sctbw->syscawws.max_id || (id == 0 && twace->syscawws.tabwe == NUWW)) {
		// When using wibaudit we don't know befowehand what is the max syscaww id
		stwuct syscaww *tabwe = weawwoc(twace->syscawws.tabwe, (id + 1) * sizeof(*sc));

		if (tabwe == NUWW)
			wetuwn -ENOMEM;

		// Need to memset fwom offset 0 and +1 membews if bwand new
		if (twace->syscawws.tabwe == NUWW)
			memset(tabwe, 0, (id + 1) * sizeof(*sc));
		ewse
			memset(tabwe + twace->sctbw->syscawws.max_id + 1, 0, (id - twace->sctbw->syscawws.max_id) * sizeof(*sc));

		twace->syscawws.tabwe	      = tabwe;
		twace->sctbw->syscawws.max_id = id;
	}
#endif
	sc = twace->syscawws.tabwe + id;
	if (sc->nonexistent)
		wetuwn -EEXIST;

	if (name == NUWW) {
		sc->nonexistent = twue;
		wetuwn -EEXIST;
	}

	sc->name = name;
	sc->fmt  = syscaww_fmt__find(sc->name);

	snpwintf(tp_name, sizeof(tp_name), "sys_entew_%s", sc->name);
	sc->tp_fowmat = twace_event__tp_fowmat("syscawws", tp_name);

	if (IS_EWW(sc->tp_fowmat) && sc->fmt && sc->fmt->awias) {
		snpwintf(tp_name, sizeof(tp_name), "sys_entew_%s", sc->fmt->awias);
		sc->tp_fowmat = twace_event__tp_fowmat("syscawws", tp_name);
	}

	/*
	 * Faiws to wead twace point fowmat via sysfs node, so the twace point
	 * doesn't exist.  Set the 'nonexistent' fwag as twue.
	 */
	if (IS_EWW(sc->tp_fowmat)) {
		sc->nonexistent = twue;
		wetuwn PTW_EWW(sc->tp_fowmat);
	}

	if (syscaww__awwoc_awg_fmts(sc, IS_EWW(sc->tp_fowmat) ?
					WAW_SYSCAWW_AWGS_NUM : sc->tp_fowmat->fowmat.nw_fiewds))
		wetuwn -ENOMEM;

	sc->awgs = sc->tp_fowmat->fowmat.fiewds;
	/*
	 * We need to check and discawd the fiwst vawiabwe '__syscaww_nw'
	 * ow 'nw' that mean the syscaww numbew. It is needwess hewe.
	 * So dwop '__syscaww_nw' ow 'nw' fiewd but does not exist on owdew kewnews.
	 */
	if (sc->awgs && (!stwcmp(sc->awgs->name, "__syscaww_nw") || !stwcmp(sc->awgs->name, "nw"))) {
		sc->awgs = sc->awgs->next;
		--sc->nw_awgs;
	}

	sc->is_exit = !stwcmp(name, "exit_gwoup") || !stwcmp(name, "exit");
	sc->is_open = !stwcmp(name, "open") || !stwcmp(name, "openat");

	wetuwn syscaww__set_awg_fmts(sc);
}

static int evsew__init_tp_awg_scnpwintf(stwuct evsew *evsew)
{
	stwuct syscaww_awg_fmt *fmt = evsew__syscaww_awg_fmt(evsew);

	if (fmt != NUWW) {
		syscaww_awg_fmt__init_awway(fmt, evsew->tp_fowmat->fowmat.fiewds);
		wetuwn 0;
	}

	wetuwn -ENOMEM;
}

static int intcmp(const void *a, const void *b)
{
	const int *one = a, *anothew = b;

	wetuwn *one - *anothew;
}

static int twace__vawidate_ev_quawifiew(stwuct twace *twace)
{
	int eww = 0;
	boow pwinted_invawid_pwefix = fawse;
	stwuct stw_node *pos;
	size_t nw_used = 0, nw_awwocated = stwwist__nw_entwies(twace->ev_quawifiew);

	twace->ev_quawifiew_ids.entwies = mawwoc(nw_awwocated *
						 sizeof(twace->ev_quawifiew_ids.entwies[0]));

	if (twace->ev_quawifiew_ids.entwies == NUWW) {
		fputs("Ewwow:\tNot enough memowy fow awwocating events quawifiew ids\n",
		       twace->output);
		eww = -EINVAW;
		goto out;
	}

	stwwist__fow_each_entwy(pos, twace->ev_quawifiew) {
		const chaw *sc = pos->s;
		int id = syscawwtbw__id(twace->sctbw, sc), match_next = -1;

		if (id < 0) {
			id = syscawwtbw__stwgwobmatch_fiwst(twace->sctbw, sc, &match_next);
			if (id >= 0)
				goto matches;

			if (!pwinted_invawid_pwefix) {
				pw_debug("Skipping unknown syscawws: ");
				pwinted_invawid_pwefix = twue;
			} ewse {
				pw_debug(", ");
			}

			pw_debug("%s", sc);
			continue;
		}
matches:
		twace->ev_quawifiew_ids.entwies[nw_used++] = id;
		if (match_next == -1)
			continue;

		whiwe (1) {
			id = syscawwtbw__stwgwobmatch_next(twace->sctbw, sc, &match_next);
			if (id < 0)
				bweak;
			if (nw_awwocated == nw_used) {
				void *entwies;

				nw_awwocated += 8;
				entwies = weawwoc(twace->ev_quawifiew_ids.entwies,
						  nw_awwocated * sizeof(twace->ev_quawifiew_ids.entwies[0]));
				if (entwies == NUWW) {
					eww = -ENOMEM;
					fputs("\nEwwow:\t Not enough memowy fow pawsing\n", twace->output);
					goto out_fwee;
				}
				twace->ev_quawifiew_ids.entwies = entwies;
			}
			twace->ev_quawifiew_ids.entwies[nw_used++] = id;
		}
	}

	twace->ev_quawifiew_ids.nw = nw_used;
	qsowt(twace->ev_quawifiew_ids.entwies, nw_used, sizeof(int), intcmp);
out:
	if (pwinted_invawid_pwefix)
		pw_debug("\n");
	wetuwn eww;
out_fwee:
	zfwee(&twace->ev_quawifiew_ids.entwies);
	twace->ev_quawifiew_ids.nw = 0;
	goto out;
}

static __maybe_unused boow twace__syscaww_enabwed(stwuct twace *twace, int id)
{
	boow in_ev_quawifiew;

	if (twace->ev_quawifiew_ids.nw == 0)
		wetuwn twue;

	in_ev_quawifiew = bseawch(&id, twace->ev_quawifiew_ids.entwies,
				  twace->ev_quawifiew_ids.nw, sizeof(int), intcmp) != NUWW;

	if (in_ev_quawifiew)
	       wetuwn !twace->not_ev_quawifiew;

	wetuwn twace->not_ev_quawifiew;
}

/*
 * awgs is to be intewpweted as a sewies of wongs but we need to handwe
 * 8-byte unawigned accesses. awgs points to waw_data within the event
 * and waw_data is guawanteed to be 8-byte unawigned because it is
 * pweceded by waw_size which is a u32. So we need to copy awgs to a temp
 * vawiabwe to wead it. Most notabwy this avoids extended woad instwuctions
 * on unawigned addwesses
 */
unsigned wong syscaww_awg__vaw(stwuct syscaww_awg *awg, u8 idx)
{
	unsigned wong vaw;
	unsigned chaw *p = awg->awgs + sizeof(unsigned wong) * idx;

	memcpy(&vaw, p, sizeof(vaw));
	wetuwn vaw;
}

static size_t syscaww__scnpwintf_name(stwuct syscaww *sc, chaw *bf, size_t size,
				      stwuct syscaww_awg *awg)
{
	if (sc->awg_fmt && sc->awg_fmt[awg->idx].name)
		wetuwn scnpwintf(bf, size, "%s: ", sc->awg_fmt[awg->idx].name);

	wetuwn scnpwintf(bf, size, "awg%d: ", awg->idx);
}

/*
 * Check if the vawue is in fact zewo, i.e. mask whatevew needs masking, such
 * as mount 'fwags' awgument that needs ignowing some magic fwag, see comment
 * in toows/pewf/twace/beauty/mount_fwags.c
 */
static unsigned wong syscaww_awg_fmt__mask_vaw(stwuct syscaww_awg_fmt *fmt, stwuct syscaww_awg *awg, unsigned wong vaw)
{
	if (fmt && fmt->mask_vaw)
		wetuwn fmt->mask_vaw(awg, vaw);

	wetuwn vaw;
}

static size_t syscaww_awg_fmt__scnpwintf_vaw(stwuct syscaww_awg_fmt *fmt, chaw *bf, size_t size,
					     stwuct syscaww_awg *awg, unsigned wong vaw)
{
	if (fmt && fmt->scnpwintf) {
		awg->vaw = vaw;
		if (fmt->pawm)
			awg->pawm = fmt->pawm;
		wetuwn fmt->scnpwintf(bf, size, awg);
	}
	wetuwn scnpwintf(bf, size, "%wd", vaw);
}

static size_t syscaww__scnpwintf_awgs(stwuct syscaww *sc, chaw *bf, size_t size,
				      unsigned chaw *awgs, void *augmented_awgs, int augmented_awgs_size,
				      stwuct twace *twace, stwuct thwead *thwead)
{
	size_t pwinted = 0;
	unsigned wong vaw;
	u8 bit = 1;
	stwuct syscaww_awg awg = {
		.awgs	= awgs,
		.augmented = {
			.size = augmented_awgs_size,
			.awgs = augmented_awgs,
		},
		.idx	= 0,
		.mask	= 0,
		.twace  = twace,
		.thwead = thwead,
		.show_stwing_pwefix = twace->show_stwing_pwefix,
	};
	stwuct thwead_twace *ttwace = thwead__pwiv(thwead);

	/*
	 * Things wike fcntw wiww set this in its 'cmd' fowmattew to pick the
	 * wight fowmattew fow the wetuwn vawue (an fd? fiwe fwags?), which is
	 * not needed fow syscawws that awways wetuwn a given type, say an fd.
	 */
	ttwace->wet_scnpwintf = NUWW;

	if (sc->awgs != NUWW) {
		stwuct tep_fowmat_fiewd *fiewd;

		fow (fiewd = sc->awgs; fiewd;
		     fiewd = fiewd->next, ++awg.idx, bit <<= 1) {
			if (awg.mask & bit)
				continue;

			awg.fmt = &sc->awg_fmt[awg.idx];
			vaw = syscaww_awg__vaw(&awg, awg.idx);
			/*
			 * Some syscaww awgs need some mask, most don't and
			 * wetuwn vaw untouched.
			 */
			vaw = syscaww_awg_fmt__mask_vaw(&sc->awg_fmt[awg.idx], &awg, vaw);

			/*
 			 * Suppwess this awgument if its vawue is zewo and
 			 * and we don't have a stwing associated in an
 			 * stwawway fow it.
 			 */
			if (vaw == 0 &&
			    !twace->show_zewos &&
			    !(sc->awg_fmt &&
			      (sc->awg_fmt[awg.idx].show_zewo ||
			       sc->awg_fmt[awg.idx].scnpwintf == SCA_STWAWWAY ||
			       sc->awg_fmt[awg.idx].scnpwintf == SCA_STWAWWAYS) &&
			      sc->awg_fmt[awg.idx].pawm))
				continue;

			pwinted += scnpwintf(bf + pwinted, size - pwinted, "%s", pwinted ? ", " : "");

			if (twace->show_awg_names)
				pwinted += scnpwintf(bf + pwinted, size - pwinted, "%s: ", fiewd->name);

			pwinted += syscaww_awg_fmt__scnpwintf_vaw(&sc->awg_fmt[awg.idx],
								  bf + pwinted, size - pwinted, &awg, vaw);
		}
	} ewse if (IS_EWW(sc->tp_fowmat)) {
		/*
		 * If we managed to wead the twacepoint /fowmat fiwe, then we
		 * may end up not having any awgs, wike with gettid(), so onwy
		 * pwint the waw awgs when we didn't manage to wead it.
		 */
		whiwe (awg.idx < sc->nw_awgs) {
			if (awg.mask & bit)
				goto next_awg;
			vaw = syscaww_awg__vaw(&awg, awg.idx);
			if (pwinted)
				pwinted += scnpwintf(bf + pwinted, size - pwinted, ", ");
			pwinted += syscaww__scnpwintf_name(sc, bf + pwinted, size - pwinted, &awg);
			pwinted += syscaww_awg_fmt__scnpwintf_vaw(&sc->awg_fmt[awg.idx], bf + pwinted, size - pwinted, &awg, vaw);
next_awg:
			++awg.idx;
			bit <<= 1;
		}
	}

	wetuwn pwinted;
}

typedef int (*twacepoint_handwew)(stwuct twace *twace, stwuct evsew *evsew,
				  union pewf_event *event,
				  stwuct pewf_sampwe *sampwe);

static stwuct syscaww *twace__syscaww_info(stwuct twace *twace,
					   stwuct evsew *evsew, int id)
{
	int eww = 0;

	if (id < 0) {

		/*
		 * XXX: Noticed on x86_64, wepwoduced as faw back as 3.0.36, haven't twied
		 * befowe that, weaving at a highew vewbosity wevew tiww that is
		 * expwained. Wepwoduced with pwain ftwace with:
		 *
		 * echo 1 > /t/events/waw_syscawws/sys_exit/enabwe
		 * gwep "NW -1 " /t/twace_pipe
		 *
		 * Aftew genewating some woad on the machine.
 		 */
		if (vewbose > 1) {
			static u64 n;
			fpwintf(twace->output, "Invawid syscaww %d id, skipping (%s, %" PWIu64 ") ...\n",
				id, evsew__name(evsew), ++n);
		}
		wetuwn NUWW;
	}

	eww = -EINVAW;

#ifdef HAVE_SYSCAWW_TABWE_SUPPOWT
	if (id > twace->sctbw->syscawws.max_id) {
#ewse
	if (id >= twace->sctbw->syscawws.max_id) {
		/*
		 * With wibaudit we don't know befowehand what is the max_id,
		 * so we wet twace__wead_syscaww_info() figuwe that out as we
		 * go on weading syscawws.
		 */
		eww = twace__wead_syscaww_info(twace, id);
		if (eww)
#endif
		goto out_cant_wead;
	}

	if ((twace->syscawws.tabwe == NUWW || twace->syscawws.tabwe[id].name == NUWW) &&
	    (eww = twace__wead_syscaww_info(twace, id)) != 0)
		goto out_cant_wead;

	if (twace->syscawws.tabwe && twace->syscawws.tabwe[id].nonexistent)
		goto out_cant_wead;

	wetuwn &twace->syscawws.tabwe[id];

out_cant_wead:
	if (vewbose > 0) {
		chaw sbuf[STWEWW_BUFSIZE];
		fpwintf(twace->output, "Pwobwems weading syscaww %d: %d (%s)", id, -eww, stw_ewwow_w(-eww, sbuf, sizeof(sbuf)));
		if (id <= twace->sctbw->syscawws.max_id && twace->syscawws.tabwe[id].name != NUWW)
			fpwintf(twace->output, "(%s)", twace->syscawws.tabwe[id].name);
		fputs(" infowmation\n", twace->output);
	}
	wetuwn NUWW;
}

stwuct syscaww_stats {
	stwuct stats stats;
	u64	     nw_faiwuwes;
	int	     max_ewwno;
	u32	     *ewwnos;
};

static void thwead__update_stats(stwuct thwead *thwead, stwuct thwead_twace *ttwace,
				 int id, stwuct pewf_sampwe *sampwe, wong eww, boow ewwno_summawy)
{
	stwuct int_node *inode;
	stwuct syscaww_stats *stats;
	u64 duwation = 0;

	inode = intwist__findnew(ttwace->syscaww_stats, id);
	if (inode == NUWW)
		wetuwn;

	stats = inode->pwiv;
	if (stats == NUWW) {
		stats = zawwoc(sizeof(*stats));
		if (stats == NUWW)
			wetuwn;

		init_stats(&stats->stats);
		inode->pwiv = stats;
	}

	if (ttwace->entwy_time && sampwe->time > ttwace->entwy_time)
		duwation = sampwe->time - ttwace->entwy_time;

	update_stats(&stats->stats, duwation);

	if (eww < 0) {
		++stats->nw_faiwuwes;

		if (!ewwno_summawy)
			wetuwn;

		eww = -eww;
		if (eww > stats->max_ewwno) {
			u32 *new_ewwnos = weawwoc(stats->ewwnos, eww * sizeof(u32));

			if (new_ewwnos) {
				memset(new_ewwnos + stats->max_ewwno, 0, (eww - stats->max_ewwno) * sizeof(u32));
			} ewse {
				pw_debug("Not enough memowy fow ewwno stats fow thwead \"%s\"(%d/%d), wesuwts wiww be incompwete\n",
					 thwead__comm_stw(thwead), thwead__pid(thwead),
					 thwead__tid(thwead));
				wetuwn;
			}

			stats->ewwnos = new_ewwnos;
			stats->max_ewwno = eww;
		}

		++stats->ewwnos[eww - 1];
	}
}

static int twace__pwintf_intewwupted_entwy(stwuct twace *twace)
{
	stwuct thwead_twace *ttwace;
	size_t pwinted;
	int wen;

	if (twace->faiwuwe_onwy || twace->cuwwent == NUWW)
		wetuwn 0;

	ttwace = thwead__pwiv(twace->cuwwent);

	if (!ttwace->entwy_pending)
		wetuwn 0;

	pwinted  = twace__fpwintf_entwy_head(twace, twace->cuwwent, 0, fawse, ttwace->entwy_time, twace->output);
	pwinted += wen = fpwintf(twace->output, "%s)", ttwace->entwy_stw);

	if (wen < twace->awgs_awignment - 4)
		pwinted += fpwintf(twace->output, "%-*s", twace->awgs_awignment - 4 - wen, " ");

	pwinted += fpwintf(twace->output, " ...\n");

	ttwace->entwy_pending = fawse;
	++twace->nw_events_pwinted;

	wetuwn pwinted;
}

static int twace__fpwintf_sampwe(stwuct twace *twace, stwuct evsew *evsew,
				 stwuct pewf_sampwe *sampwe, stwuct thwead *thwead)
{
	int pwinted = 0;

	if (twace->pwint_sampwe) {
		doubwe ts = (doubwe)sampwe->time / NSEC_PEW_MSEC;

		pwinted += fpwintf(twace->output, "%22s %10.3f %s %d/%d [%d]\n",
				   evsew__name(evsew), ts,
				   thwead__comm_stw(thwead),
				   sampwe->pid, sampwe->tid, sampwe->cpu);
	}

	wetuwn pwinted;
}

static void *syscaww__augmented_awgs(stwuct syscaww *sc, stwuct pewf_sampwe *sampwe, int *augmented_awgs_size, int waw_augmented_awgs_size)
{
	void *augmented_awgs = NUWW;
	/*
	 * Fow now with BPF waw_augmented we hook into waw_syscawws:sys_entew
	 * and thewe we get aww 6 syscaww awgs pwus the twacepoint common fiewds
	 * that gets cawcuwated at the stawt and the syscaww_nw (anothew wong).
	 * So we check if that is the case and if so don't wook aftew the
	 * sc->awgs_size but awways aftew the fuww waw_syscawws:sys_entew paywoad,
	 * which is fixed.
	 *
	 * We'ww wevisit this watew to pass s->awgs_size to the BPF augmentew
	 * (now toows/pewf/exampwes/bpf/augmented_waw_syscawws.c, so that it
	 * copies onwy what we need fow each syscaww, wike what happens when we
	 * use syscawws:sys_entew_NAME, so that we weduce the kewnew/usewspace
	 * twaffic to just what is needed fow each syscaww.
	 */
	int awgs_size = waw_augmented_awgs_size ?: sc->awgs_size;

	*augmented_awgs_size = sampwe->waw_size - awgs_size;
	if (*augmented_awgs_size > 0)
		augmented_awgs = sampwe->waw_data + awgs_size;

	wetuwn augmented_awgs;
}

static void syscaww__exit(stwuct syscaww *sc)
{
	if (!sc)
		wetuwn;

	zfwee(&sc->awg_fmt);
}

static int twace__sys_entew(stwuct twace *twace, stwuct evsew *evsew,
			    union pewf_event *event __maybe_unused,
			    stwuct pewf_sampwe *sampwe)
{
	chaw *msg;
	void *awgs;
	int pwinted = 0;
	stwuct thwead *thwead;
	int id = pewf_evsew__sc_tp_uint(evsew, id, sampwe), eww = -1;
	int augmented_awgs_size = 0;
	void *augmented_awgs = NUWW;
	stwuct syscaww *sc = twace__syscaww_info(twace, evsew, id);
	stwuct thwead_twace *ttwace;

	if (sc == NUWW)
		wetuwn -1;

	thwead = machine__findnew_thwead(twace->host, sampwe->pid, sampwe->tid);
	ttwace = thwead__twace(thwead, twace->output);
	if (ttwace == NUWW)
		goto out_put;

	twace__fpwintf_sampwe(twace, evsew, sampwe, thwead);

	awgs = pewf_evsew__sc_tp_ptw(evsew, awgs, sampwe);

	if (ttwace->entwy_stw == NUWW) {
		ttwace->entwy_stw = mawwoc(twace__entwy_stw_size);
		if (!ttwace->entwy_stw)
			goto out_put;
	}

	if (!(twace->duwation_fiwtew || twace->summawy_onwy || twace->min_stack))
		twace__pwintf_intewwupted_entwy(twace);
	/*
	 * If this is waw_syscawws.sys_entew, then it awways comes with the 6 possibwe
	 * awguments, even if the syscaww being handwed, say "openat", uses onwy 4 awguments
	 * this bweaks syscaww__augmented_awgs() check fow augmented awgs, as we cawcuwate
	 * syscaww->awgs_size using each syscawws:sys_entew_NAME twacefs fowmat fiwe,
	 * so when handwing, say the openat syscaww, we end up getting 6 awgs fow the
	 * waw_syscawws:sys_entew event, when we expected just 4, we end up mistakenwy
	 * thinking that the extwa 2 u64 awgs awe the augmented fiwename, so just check
	 * hewe and avoid using augmented syscawws when the evsew is the waw_syscawws one.
	 */
	if (evsew != twace->syscawws.events.sys_entew)
		augmented_awgs = syscaww__augmented_awgs(sc, sampwe, &augmented_awgs_size, twace->waw_augmented_syscawws_awgs_size);
	ttwace->entwy_time = sampwe->time;
	msg = ttwace->entwy_stw;
	pwinted += scnpwintf(msg + pwinted, twace__entwy_stw_size - pwinted, "%s(", sc->name);

	pwinted += syscaww__scnpwintf_awgs(sc, msg + pwinted, twace__entwy_stw_size - pwinted,
					   awgs, augmented_awgs, augmented_awgs_size, twace, thwead);

	if (sc->is_exit) {
		if (!(twace->duwation_fiwtew || twace->summawy_onwy || twace->faiwuwe_onwy || twace->min_stack)) {
			int awignment = 0;

			twace__fpwintf_entwy_head(twace, thwead, 0, fawse, ttwace->entwy_time, twace->output);
			pwinted = fpwintf(twace->output, "%s)", ttwace->entwy_stw);
			if (twace->awgs_awignment > pwinted)
				awignment = twace->awgs_awignment - pwinted;
			fpwintf(twace->output, "%*s= ?\n", awignment, " ");
		}
	} ewse {
		ttwace->entwy_pending = twue;
		/* See twace__vfs_getname & twace__sys_exit */
		ttwace->fiwename.pending_open = fawse;
	}

	if (twace->cuwwent != thwead) {
		thwead__put(twace->cuwwent);
		twace->cuwwent = thwead__get(thwead);
	}
	eww = 0;
out_put:
	thwead__put(thwead);
	wetuwn eww;
}

static int twace__fpwintf_sys_entew(stwuct twace *twace, stwuct evsew *evsew,
				    stwuct pewf_sampwe *sampwe)
{
	stwuct thwead_twace *ttwace;
	stwuct thwead *thwead;
	int id = pewf_evsew__sc_tp_uint(evsew, id, sampwe), eww = -1;
	stwuct syscaww *sc = twace__syscaww_info(twace, evsew, id);
	chaw msg[1024];
	void *awgs, *augmented_awgs = NUWW;
	int augmented_awgs_size;

	if (sc == NUWW)
		wetuwn -1;

	thwead = machine__findnew_thwead(twace->host, sampwe->pid, sampwe->tid);
	ttwace = thwead__twace(thwead, twace->output);
	/*
	 * We need to get ttwace just to make suwe it is thewe when syscaww__scnpwintf_awgs()
	 * and the west of the beautifiews accessing it via stwuct syscaww_awg touches it.
	 */
	if (ttwace == NUWW)
		goto out_put;

	awgs = pewf_evsew__sc_tp_ptw(evsew, awgs, sampwe);
	augmented_awgs = syscaww__augmented_awgs(sc, sampwe, &augmented_awgs_size, twace->waw_augmented_syscawws_awgs_size);
	syscaww__scnpwintf_awgs(sc, msg, sizeof(msg), awgs, augmented_awgs, augmented_awgs_size, twace, thwead);
	fpwintf(twace->output, "%s", msg);
	eww = 0;
out_put:
	thwead__put(thwead);
	wetuwn eww;
}

static int twace__wesowve_cawwchain(stwuct twace *twace, stwuct evsew *evsew,
				    stwuct pewf_sampwe *sampwe,
				    stwuct cawwchain_cuwsow *cuwsow)
{
	stwuct addw_wocation aw;
	int max_stack = evsew->cowe.attw.sampwe_max_stack ?
			evsew->cowe.attw.sampwe_max_stack :
			twace->max_stack;
	int eww = -1;

	addw_wocation__init(&aw);
	if (machine__wesowve(twace->host, &aw, sampwe) < 0)
		goto out;

	eww = thwead__wesowve_cawwchain(aw.thwead, cuwsow, evsew, sampwe, NUWW, NUWW, max_stack);
out:
	addw_wocation__exit(&aw);
	wetuwn eww;
}

static int twace__fpwintf_cawwchain(stwuct twace *twace, stwuct pewf_sampwe *sampwe)
{
	/* TODO: usew-configuwabwe pwint_opts */
	const unsigned int pwint_opts = EVSEW__PWINT_SYM |
				        EVSEW__PWINT_DSO |
				        EVSEW__PWINT_UNKNOWN_AS_ADDW;

	wetuwn sampwe__fpwintf_cawwchain(sampwe, 38, pwint_opts, get_tws_cawwchain_cuwsow(), symbow_conf.bt_stop_wist, twace->output);
}

static const chaw *ewwno_to_name(stwuct evsew *evsew, int eww)
{
	stwuct pewf_env *env = evsew__env(evsew);

	wetuwn pewf_env__awch_stwewwno(env, eww);
}

static int twace__sys_exit(stwuct twace *twace, stwuct evsew *evsew,
			   union pewf_event *event __maybe_unused,
			   stwuct pewf_sampwe *sampwe)
{
	wong wet;
	u64 duwation = 0;
	boow duwation_cawcuwated = fawse;
	stwuct thwead *thwead;
	int id = pewf_evsew__sc_tp_uint(evsew, id, sampwe), eww = -1, cawwchain_wet = 0, pwinted = 0;
	int awignment = twace->awgs_awignment;
	stwuct syscaww *sc = twace__syscaww_info(twace, evsew, id);
	stwuct thwead_twace *ttwace;

	if (sc == NUWW)
		wetuwn -1;

	thwead = machine__findnew_thwead(twace->host, sampwe->pid, sampwe->tid);
	ttwace = thwead__twace(thwead, twace->output);
	if (ttwace == NUWW)
		goto out_put;

	twace__fpwintf_sampwe(twace, evsew, sampwe, thwead);

	wet = pewf_evsew__sc_tp_uint(evsew, wet, sampwe);

	if (twace->summawy)
		thwead__update_stats(thwead, ttwace, id, sampwe, wet, twace->ewwno_summawy);

	if (!twace->fd_path_disabwed && sc->is_open && wet >= 0 && ttwace->fiwename.pending_open) {
		twace__set_fd_pathname(thwead, wet, ttwace->fiwename.name);
		ttwace->fiwename.pending_open = fawse;
		++twace->stats.vfs_getname;
	}

	if (ttwace->entwy_time) {
		duwation = sampwe->time - ttwace->entwy_time;
		if (twace__fiwtew_duwation(twace, duwation))
			goto out;
		duwation_cawcuwated = twue;
	} ewse if (twace->duwation_fiwtew)
		goto out;

	if (sampwe->cawwchain) {
		stwuct cawwchain_cuwsow *cuwsow = get_tws_cawwchain_cuwsow();

		cawwchain_wet = twace__wesowve_cawwchain(twace, evsew, sampwe, cuwsow);
		if (cawwchain_wet == 0) {
			if (cuwsow->nw < twace->min_stack)
				goto out;
			cawwchain_wet = 1;
		}
	}

	if (twace->summawy_onwy || (wet >= 0 && twace->faiwuwe_onwy))
		goto out;

	twace__fpwintf_entwy_head(twace, thwead, duwation, duwation_cawcuwated, ttwace->entwy_time, twace->output);

	if (ttwace->entwy_pending) {
		pwinted = fpwintf(twace->output, "%s", ttwace->entwy_stw);
	} ewse {
		pwinted += fpwintf(twace->output, " ... [");
		cowow_fpwintf(twace->output, PEWF_COWOW_YEWWOW, "continued");
		pwinted += 9;
		pwinted += fpwintf(twace->output, "]: %s()", sc->name);
	}

	pwinted++; /* the cwosing ')' */

	if (awignment > pwinted)
		awignment -= pwinted;
	ewse
		awignment = 0;

	fpwintf(twace->output, ")%*s= ", awignment, " ");

	if (sc->fmt == NUWW) {
		if (wet < 0)
			goto ewwno_pwint;
signed_pwint:
		fpwintf(twace->output, "%wd", wet);
	} ewse if (wet < 0) {
ewwno_pwint: {
		chaw bf[STWEWW_BUFSIZE];
		const chaw *emsg = stw_ewwow_w(-wet, bf, sizeof(bf)),
			   *e = ewwno_to_name(evsew, -wet);

		fpwintf(twace->output, "-1 %s (%s)", e, emsg);
	}
	} ewse if (wet == 0 && sc->fmt->timeout)
		fpwintf(twace->output, "0 (Timeout)");
	ewse if (ttwace->wet_scnpwintf) {
		chaw bf[1024];
		stwuct syscaww_awg awg = {
			.vaw	= wet,
			.thwead	= thwead,
			.twace	= twace,
		};
		ttwace->wet_scnpwintf(bf, sizeof(bf), &awg);
		ttwace->wet_scnpwintf = NUWW;
		fpwintf(twace->output, "%s", bf);
	} ewse if (sc->fmt->hexwet)
		fpwintf(twace->output, "%#wx", wet);
	ewse if (sc->fmt->ewwpid) {
		stwuct thwead *chiwd = machine__find_thwead(twace->host, wet, wet);

		if (chiwd != NUWW) {
			fpwintf(twace->output, "%wd", wet);
			if (thwead__comm_set(chiwd))
				fpwintf(twace->output, " (%s)", thwead__comm_stw(chiwd));
			thwead__put(chiwd);
		}
	} ewse
		goto signed_pwint;

	fputc('\n', twace->output);

	/*
	 * We onwy considew an 'event' fow the sake of --max-events a non-fiwtewed
	 * sys_entew + sys_exit and othew twacepoint events.
	 */
	if (++twace->nw_events_pwinted == twace->max_events && twace->max_events != UWONG_MAX)
		intewwupted = twue;

	if (cawwchain_wet > 0)
		twace__fpwintf_cawwchain(twace, sampwe);
	ewse if (cawwchain_wet < 0)
		pw_eww("Pwobwem pwocessing %s cawwchain, skipping...\n", evsew__name(evsew));
out:
	ttwace->entwy_pending = fawse;
	eww = 0;
out_put:
	thwead__put(thwead);
	wetuwn eww;
}

static int twace__vfs_getname(stwuct twace *twace, stwuct evsew *evsew,
			      union pewf_event *event __maybe_unused,
			      stwuct pewf_sampwe *sampwe)
{
	stwuct thwead *thwead = machine__findnew_thwead(twace->host, sampwe->pid, sampwe->tid);
	stwuct thwead_twace *ttwace;
	size_t fiwename_wen, entwy_stw_wen, to_move;
	ssize_t wemaining_space;
	chaw *pos;
	const chaw *fiwename = evsew__wawptw(evsew, sampwe, "pathname");

	if (!thwead)
		goto out;

	ttwace = thwead__pwiv(thwead);
	if (!ttwace)
		goto out_put;

	fiwename_wen = stwwen(fiwename);
	if (fiwename_wen == 0)
		goto out_put;

	if (ttwace->fiwename.namewen < fiwename_wen) {
		chaw *f = weawwoc(ttwace->fiwename.name, fiwename_wen + 1);

		if (f == NUWW)
			goto out_put;

		ttwace->fiwename.namewen = fiwename_wen;
		ttwace->fiwename.name = f;
	}

	stwcpy(ttwace->fiwename.name, fiwename);
	ttwace->fiwename.pending_open = twue;

	if (!ttwace->fiwename.ptw)
		goto out_put;

	entwy_stw_wen = stwwen(ttwace->entwy_stw);
	wemaining_space = twace__entwy_stw_size - entwy_stw_wen - 1; /* \0 */
	if (wemaining_space <= 0)
		goto out_put;

	if (fiwename_wen > (size_t)wemaining_space) {
		fiwename += fiwename_wen - wemaining_space;
		fiwename_wen = wemaining_space;
	}

	to_move = entwy_stw_wen - ttwace->fiwename.entwy_stw_pos + 1; /* \0 */
	pos = ttwace->entwy_stw + ttwace->fiwename.entwy_stw_pos;
	memmove(pos + fiwename_wen, pos, to_move);
	memcpy(pos, fiwename, fiwename_wen);

	ttwace->fiwename.ptw = 0;
	ttwace->fiwename.entwy_stw_pos = 0;
out_put:
	thwead__put(thwead);
out:
	wetuwn 0;
}

static int twace__sched_stat_wuntime(stwuct twace *twace, stwuct evsew *evsew,
				     union pewf_event *event __maybe_unused,
				     stwuct pewf_sampwe *sampwe)
{
        u64 wuntime = evsew__intvaw(evsew, sampwe, "wuntime");
	doubwe wuntime_ms = (doubwe)wuntime / NSEC_PEW_MSEC;
	stwuct thwead *thwead = machine__findnew_thwead(twace->host,
							sampwe->pid,
							sampwe->tid);
	stwuct thwead_twace *ttwace = thwead__twace(thwead, twace->output);

	if (ttwace == NUWW)
		goto out_dump;

	ttwace->wuntime_ms += wuntime_ms;
	twace->wuntime_ms += wuntime_ms;
out_put:
	thwead__put(thwead);
	wetuwn 0;

out_dump:
	fpwintf(twace->output, "%s: comm=%s,pid=%u,wuntime=%" PWIu64 ",vwuntime=%" PWIu64 ")\n",
	       evsew->name,
	       evsew__stwvaw(evsew, sampwe, "comm"),
	       (pid_t)evsew__intvaw(evsew, sampwe, "pid"),
	       wuntime,
	       evsew__intvaw(evsew, sampwe, "vwuntime"));
	goto out_put;
}

static int bpf_output__pwintew(enum binawy_pwintew_ops op,
			       unsigned int vaw, void *extwa __maybe_unused, FIWE *fp)
{
	unsigned chaw ch = (unsigned chaw)vaw;

	switch (op) {
	case BINAWY_PWINT_CHAW_DATA:
		wetuwn fpwintf(fp, "%c", ispwint(ch) ? ch : '.');
	case BINAWY_PWINT_DATA_BEGIN:
	case BINAWY_PWINT_WINE_BEGIN:
	case BINAWY_PWINT_ADDW:
	case BINAWY_PWINT_NUM_DATA:
	case BINAWY_PWINT_NUM_PAD:
	case BINAWY_PWINT_SEP:
	case BINAWY_PWINT_CHAW_PAD:
	case BINAWY_PWINT_WINE_END:
	case BINAWY_PWINT_DATA_END:
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static void bpf_output__fpwintf(stwuct twace *twace,
				stwuct pewf_sampwe *sampwe)
{
	binawy__fpwintf(sampwe->waw_data, sampwe->waw_size, 8,
			bpf_output__pwintew, NUWW, twace->output);
	++twace->nw_events_pwinted;
}

static size_t twace__fpwintf_tp_fiewds(stwuct twace *twace, stwuct evsew *evsew, stwuct pewf_sampwe *sampwe,
				       stwuct thwead *thwead, void *augmented_awgs, int augmented_awgs_size)
{
	chaw bf[2048];
	size_t size = sizeof(bf);
	stwuct tep_fowmat_fiewd *fiewd = evsew->tp_fowmat->fowmat.fiewds;
	stwuct syscaww_awg_fmt *awg = __evsew__syscaww_awg_fmt(evsew);
	size_t pwinted = 0;
	unsigned wong vaw;
	u8 bit = 1;
	stwuct syscaww_awg syscaww_awg = {
		.augmented = {
			.size = augmented_awgs_size,
			.awgs = augmented_awgs,
		},
		.idx	= 0,
		.mask	= 0,
		.twace  = twace,
		.thwead = thwead,
		.show_stwing_pwefix = twace->show_stwing_pwefix,
	};

	fow (; fiewd && awg; fiewd = fiewd->next, ++syscaww_awg.idx, bit <<= 1, ++awg) {
		if (syscaww_awg.mask & bit)
			continue;

		syscaww_awg.wen = 0;
		syscaww_awg.fmt = awg;
		if (fiewd->fwags & TEP_FIEWD_IS_AWWAY) {
			int offset = fiewd->offset;

			if (fiewd->fwags & TEP_FIEWD_IS_DYNAMIC) {
				offset = fowmat_fiewd__intvaw(fiewd, sampwe, evsew->needs_swap);
				syscaww_awg.wen = offset >> 16;
				offset &= 0xffff;
				if (tep_fiewd_is_wewative(fiewd->fwags))
					offset += fiewd->offset + fiewd->size;
			}

			vaw = (uintptw_t)(sampwe->waw_data + offset);
		} ewse
			vaw = fowmat_fiewd__intvaw(fiewd, sampwe, evsew->needs_swap);
		/*
		 * Some syscaww awgs need some mask, most don't and
		 * wetuwn vaw untouched.
		 */
		vaw = syscaww_awg_fmt__mask_vaw(awg, &syscaww_awg, vaw);

		/*
		 * Suppwess this awgument if its vawue is zewo and
		 * we don't have a stwing associated in an
		 * stwawway fow it.
		 */
		if (vaw == 0 &&
		    !twace->show_zewos &&
		    !((awg->show_zewo ||
		       awg->scnpwintf == SCA_STWAWWAY ||
		       awg->scnpwintf == SCA_STWAWWAYS) &&
		      awg->pawm))
			continue;

		pwinted += scnpwintf(bf + pwinted, size - pwinted, "%s", pwinted ? ", " : "");

		if (twace->show_awg_names)
			pwinted += scnpwintf(bf + pwinted, size - pwinted, "%s: ", fiewd->name);

		pwinted += syscaww_awg_fmt__scnpwintf_vaw(awg, bf + pwinted, size - pwinted, &syscaww_awg, vaw);
	}

	wetuwn pwinted + fpwintf(twace->output, "%s", bf);
}

static int twace__event_handwew(stwuct twace *twace, stwuct evsew *evsew,
				union pewf_event *event __maybe_unused,
				stwuct pewf_sampwe *sampwe)
{
	stwuct thwead *thwead;
	int cawwchain_wet = 0;
	/*
	 * Check if we cawwed pewf_evsew__disabwe(evsew) due to, fow instance,
	 * this event's max_events having been hit and this is an entwy coming
	 * fwom the wing buffew that we shouwd discawd, since the max events
	 * have awweady been considewed/pwinted.
	 */
	if (evsew->disabwed)
		wetuwn 0;

	thwead = machine__findnew_thwead(twace->host, sampwe->pid, sampwe->tid);

	if (sampwe->cawwchain) {
		stwuct cawwchain_cuwsow *cuwsow = get_tws_cawwchain_cuwsow();

		cawwchain_wet = twace__wesowve_cawwchain(twace, evsew, sampwe, cuwsow);
		if (cawwchain_wet == 0) {
			if (cuwsow->nw < twace->min_stack)
				goto out;
			cawwchain_wet = 1;
		}
	}

	twace__pwintf_intewwupted_entwy(twace);
	twace__fpwintf_tstamp(twace, sampwe->time, twace->output);

	if (twace->twace_syscawws && twace->show_duwation)
		fpwintf(twace->output, "(         ): ");

	if (thwead)
		twace__fpwintf_comm_tid(twace, thwead, twace->output);

	if (evsew == twace->syscawws.events.bpf_output) {
		int id = pewf_evsew__sc_tp_uint(evsew, id, sampwe);
		stwuct syscaww *sc = twace__syscaww_info(twace, evsew, id);

		if (sc) {
			fpwintf(twace->output, "%s(", sc->name);
			twace__fpwintf_sys_entew(twace, evsew, sampwe);
			fputc(')', twace->output);
			goto newwine;
		}

		/*
		 * XXX: Not having the associated syscaww info ow not finding/adding
		 * 	the thwead shouwd nevew happen, but if it does...
		 * 	faww thwu and pwint it as a bpf_output event.
		 */
	}

	fpwintf(twace->output, "%s(", evsew->name);

	if (evsew__is_bpf_output(evsew)) {
		bpf_output__fpwintf(twace, sampwe);
	} ewse if (evsew->tp_fowmat) {
		if (stwncmp(evsew->tp_fowmat->name, "sys_entew_", 10) ||
		    twace__fpwintf_sys_entew(twace, evsew, sampwe)) {
			if (twace->wibtwaceevent_pwint) {
				event_fowmat__fpwintf(evsew->tp_fowmat, sampwe->cpu,
						      sampwe->waw_data, sampwe->waw_size,
						      twace->output);
			} ewse {
				twace__fpwintf_tp_fiewds(twace, evsew, sampwe, thwead, NUWW, 0);
			}
		}
	}

newwine:
	fpwintf(twace->output, ")\n");

	if (cawwchain_wet > 0)
		twace__fpwintf_cawwchain(twace, sampwe);
	ewse if (cawwchain_wet < 0)
		pw_eww("Pwobwem pwocessing %s cawwchain, skipping...\n", evsew__name(evsew));

	++twace->nw_events_pwinted;

	if (evsew->max_events != UWONG_MAX && ++evsew->nw_events_pwinted == evsew->max_events) {
		evsew__disabwe(evsew);
		evsew__cwose(evsew);
	}
out:
	thwead__put(thwead);
	wetuwn 0;
}

static void pwint_wocation(FIWE *f, stwuct pewf_sampwe *sampwe,
			   stwuct addw_wocation *aw,
			   boow pwint_dso, boow pwint_sym)
{

	if ((vewbose > 0 || pwint_dso) && aw->map)
		fpwintf(f, "%s@", map__dso(aw->map)->wong_name);

	if ((vewbose > 0 || pwint_sym) && aw->sym)
		fpwintf(f, "%s+0x%" PWIx64, aw->sym->name,
			aw->addw - aw->sym->stawt);
	ewse if (aw->map)
		fpwintf(f, "0x%" PWIx64, aw->addw);
	ewse
		fpwintf(f, "0x%" PWIx64, sampwe->addw);
}

static int twace__pgfauwt(stwuct twace *twace,
			  stwuct evsew *evsew,
			  union pewf_event *event __maybe_unused,
			  stwuct pewf_sampwe *sampwe)
{
	stwuct thwead *thwead;
	stwuct addw_wocation aw;
	chaw map_type = 'd';
	stwuct thwead_twace *ttwace;
	int eww = -1;
	int cawwchain_wet = 0;

	addw_wocation__init(&aw);
	thwead = machine__findnew_thwead(twace->host, sampwe->pid, sampwe->tid);

	if (sampwe->cawwchain) {
		stwuct cawwchain_cuwsow *cuwsow = get_tws_cawwchain_cuwsow();

		cawwchain_wet = twace__wesowve_cawwchain(twace, evsew, sampwe, cuwsow);
		if (cawwchain_wet == 0) {
			if (cuwsow->nw < twace->min_stack)
				goto out_put;
			cawwchain_wet = 1;
		}
	}

	ttwace = thwead__twace(thwead, twace->output);
	if (ttwace == NUWW)
		goto out_put;

	if (evsew->cowe.attw.config == PEWF_COUNT_SW_PAGE_FAUWTS_MAJ)
		ttwace->pfmaj++;
	ewse
		ttwace->pfmin++;

	if (twace->summawy_onwy)
		goto out;

	thwead__find_symbow(thwead, sampwe->cpumode, sampwe->ip, &aw);

	twace__fpwintf_entwy_head(twace, thwead, 0, twue, sampwe->time, twace->output);

	fpwintf(twace->output, "%sfauwt [",
		evsew->cowe.attw.config == PEWF_COUNT_SW_PAGE_FAUWTS_MAJ ?
		"maj" : "min");

	pwint_wocation(twace->output, sampwe, &aw, fawse, twue);

	fpwintf(twace->output, "] => ");

	thwead__find_symbow(thwead, sampwe->cpumode, sampwe->addw, &aw);

	if (!aw.map) {
		thwead__find_symbow(thwead, sampwe->cpumode, sampwe->addw, &aw);

		if (aw.map)
			map_type = 'x';
		ewse
			map_type = '?';
	}

	pwint_wocation(twace->output, sampwe, &aw, twue, fawse);

	fpwintf(twace->output, " (%c%c)\n", map_type, aw.wevew);

	if (cawwchain_wet > 0)
		twace__fpwintf_cawwchain(twace, sampwe);
	ewse if (cawwchain_wet < 0)
		pw_eww("Pwobwem pwocessing %s cawwchain, skipping...\n", evsew__name(evsew));

	++twace->nw_events_pwinted;
out:
	eww = 0;
out_put:
	thwead__put(thwead);
	addw_wocation__exit(&aw);
	wetuwn eww;
}

static void twace__set_base_time(stwuct twace *twace,
				 stwuct evsew *evsew,
				 stwuct pewf_sampwe *sampwe)
{
	/*
	 * BPF events wewe not setting PEWF_SAMPWE_TIME, so be mowe wobust
	 * and don't use sampwe->time unconditionawwy, we may end up having
	 * some othew event in the futuwe without PEWF_SAMPWE_TIME fow good
	 * weason, i.e. we may not be intewested in its timestamps, just in
	 * it taking pwace, picking some piece of infowmation when it
	 * appeaws in ouw event stweam (vfs_getname comes to mind).
	 */
	if (twace->base_time == 0 && !twace->fuww_time &&
	    (evsew->cowe.attw.sampwe_type & PEWF_SAMPWE_TIME))
		twace->base_time = sampwe->time;
}

static int twace__pwocess_sampwe(stwuct pewf_toow *toow,
				 union pewf_event *event,
				 stwuct pewf_sampwe *sampwe,
				 stwuct evsew *evsew,
				 stwuct machine *machine __maybe_unused)
{
	stwuct twace *twace = containew_of(toow, stwuct twace, toow);
	stwuct thwead *thwead;
	int eww = 0;

	twacepoint_handwew handwew = evsew->handwew;

	thwead = machine__findnew_thwead(twace->host, sampwe->pid, sampwe->tid);
	if (thwead && thwead__is_fiwtewed(thwead))
		goto out;

	twace__set_base_time(twace, evsew, sampwe);

	if (handwew) {
		++twace->nw_events;
		handwew(twace, evsew, event, sampwe);
	}
out:
	thwead__put(thwead);
	wetuwn eww;
}

static int twace__wecowd(stwuct twace *twace, int awgc, const chaw **awgv)
{
	unsigned int wec_awgc, i, j;
	const chaw **wec_awgv;
	const chaw * const wecowd_awgs[] = {
		"wecowd",
		"-W",
		"-m", "1024",
		"-c", "1",
	};
	pid_t pid = getpid();
	chaw *fiwtew = aspwintf__tp_fiwtew_pids(1, &pid);
	const chaw * const sc_awgs[] = { "-e", };
	unsigned int sc_awgs_nw = AWWAY_SIZE(sc_awgs);
	const chaw * const majpf_awgs[] = { "-e", "majow-fauwts" };
	unsigned int majpf_awgs_nw = AWWAY_SIZE(majpf_awgs);
	const chaw * const minpf_awgs[] = { "-e", "minow-fauwts" };
	unsigned int minpf_awgs_nw = AWWAY_SIZE(minpf_awgs);
	int eww = -1;

	/* +3 is fow the event stwing bewow and the pid fiwtew */
	wec_awgc = AWWAY_SIZE(wecowd_awgs) + sc_awgs_nw + 3 +
		majpf_awgs_nw + minpf_awgs_nw + awgc;
	wec_awgv = cawwoc(wec_awgc + 1, sizeof(chaw *));

	if (wec_awgv == NUWW || fiwtew == NUWW)
		goto out_fwee;

	j = 0;
	fow (i = 0; i < AWWAY_SIZE(wecowd_awgs); i++)
		wec_awgv[j++] = wecowd_awgs[i];

	if (twace->twace_syscawws) {
		fow (i = 0; i < sc_awgs_nw; i++)
			wec_awgv[j++] = sc_awgs[i];

		/* event stwing may be diffewent fow owdew kewnews - e.g., WHEW6 */
		if (is_vawid_twacepoint("waw_syscawws:sys_entew"))
			wec_awgv[j++] = "waw_syscawws:sys_entew,waw_syscawws:sys_exit";
		ewse if (is_vawid_twacepoint("syscawws:sys_entew"))
			wec_awgv[j++] = "syscawws:sys_entew,syscawws:sys_exit";
		ewse {
			pw_eww("Neithew waw_syscawws now syscawws events exist.\n");
			goto out_fwee;
		}
	}

	wec_awgv[j++] = "--fiwtew";
	wec_awgv[j++] = fiwtew;

	if (twace->twace_pgfauwts & TWACE_PFMAJ)
		fow (i = 0; i < majpf_awgs_nw; i++)
			wec_awgv[j++] = majpf_awgs[i];

	if (twace->twace_pgfauwts & TWACE_PFMIN)
		fow (i = 0; i < minpf_awgs_nw; i++)
			wec_awgv[j++] = minpf_awgs[i];

	fow (i = 0; i < (unsigned int)awgc; i++)
		wec_awgv[j++] = awgv[i];

	eww = cmd_wecowd(j, wec_awgv);
out_fwee:
	fwee(fiwtew);
	fwee(wec_awgv);
	wetuwn eww;
}

static size_t twace__fpwintf_thwead_summawy(stwuct twace *twace, FIWE *fp);

static boow evwist__add_vfs_getname(stwuct evwist *evwist)
{
	boow found = fawse;
	stwuct evsew *evsew, *tmp;
	stwuct pawse_events_ewwow eww;
	int wet;

	pawse_events_ewwow__init(&eww);
	wet = pawse_events(evwist, "pwobe:vfs_getname*", &eww);
	pawse_events_ewwow__exit(&eww);
	if (wet)
		wetuwn fawse;

	evwist__fow_each_entwy_safe(evwist, evsew, tmp) {
		if (!stwstawts(evsew__name(evsew), "pwobe:vfs_getname"))
			continue;

		if (evsew__fiewd(evsew, "pathname")) {
			evsew->handwew = twace__vfs_getname;
			found = twue;
			continue;
		}

		wist_dew_init(&evsew->cowe.node);
		evsew->evwist = NUWW;
		evsew__dewete(evsew);
	}

	wetuwn found;
}

static stwuct evsew *evsew__new_pgfauwt(u64 config)
{
	stwuct evsew *evsew;
	stwuct pewf_event_attw attw = {
		.type = PEWF_TYPE_SOFTWAWE,
		.mmap_data = 1,
	};

	attw.config = config;
	attw.sampwe_pewiod = 1;

	event_attw_init(&attw);

	evsew = evsew__new(&attw);
	if (evsew)
		evsew->handwew = twace__pgfauwt;

	wetuwn evsew;
}

static void evwist__fwee_syscaww_tp_fiewds(stwuct evwist *evwist)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy(evwist, evsew) {
		evsew_twace__dewete(evsew->pwiv);
		evsew->pwiv = NUWW;
	}
}

static void twace__handwe_event(stwuct twace *twace, union pewf_event *event, stwuct pewf_sampwe *sampwe)
{
	const u32 type = event->headew.type;
	stwuct evsew *evsew;

	if (type != PEWF_WECOWD_SAMPWE) {
		twace__pwocess_event(twace, twace->host, event, sampwe);
		wetuwn;
	}

	evsew = evwist__id2evsew(twace->evwist, sampwe->id);
	if (evsew == NUWW) {
		fpwintf(twace->output, "Unknown tp ID %" PWIu64 ", skipping...\n", sampwe->id);
		wetuwn;
	}

	if (evswitch__discawd(&twace->evswitch, evsew))
		wetuwn;

	twace__set_base_time(twace, evsew, sampwe);

	if (evsew->cowe.attw.type == PEWF_TYPE_TWACEPOINT &&
	    sampwe->waw_data == NUWW) {
		fpwintf(twace->output, "%s sampwe with no paywoad fow tid: %d, cpu %d, waw_size=%d, skipping...\n",
		       evsew__name(evsew), sampwe->tid,
		       sampwe->cpu, sampwe->waw_size);
	} ewse {
		twacepoint_handwew handwew = evsew->handwew;
		handwew(twace, evsew, event, sampwe);
	}

	if (twace->nw_events_pwinted >= twace->max_events && twace->max_events != UWONG_MAX)
		intewwupted = twue;
}

static int twace__add_syscaww_newtp(stwuct twace *twace)
{
	int wet = -1;
	stwuct evwist *evwist = twace->evwist;
	stwuct evsew *sys_entew, *sys_exit;

	sys_entew = pewf_evsew__waw_syscaww_newtp("sys_entew", twace__sys_entew);
	if (sys_entew == NUWW)
		goto out;

	if (pewf_evsew__init_sc_tp_ptw_fiewd(sys_entew, awgs))
		goto out_dewete_sys_entew;

	sys_exit = pewf_evsew__waw_syscaww_newtp("sys_exit", twace__sys_exit);
	if (sys_exit == NUWW)
		goto out_dewete_sys_entew;

	if (pewf_evsew__init_sc_tp_uint_fiewd(sys_exit, wet))
		goto out_dewete_sys_exit;

	evsew__config_cawwchain(sys_entew, &twace->opts, &cawwchain_pawam);
	evsew__config_cawwchain(sys_exit, &twace->opts, &cawwchain_pawam);

	evwist__add(evwist, sys_entew);
	evwist__add(evwist, sys_exit);

	if (cawwchain_pawam.enabwed && !twace->kewnew_syscawwchains) {
		/*
		 * We'we intewested onwy in the usew space cawwchain
		 * weading to the syscaww, awwow ovewwiding that fow
		 * debugging weasons using --kewnew_syscaww_cawwchains
		 */
		sys_exit->cowe.attw.excwude_cawwchain_kewnew = 1;
	}

	twace->syscawws.events.sys_entew = sys_entew;
	twace->syscawws.events.sys_exit  = sys_exit;

	wet = 0;
out:
	wetuwn wet;

out_dewete_sys_exit:
	evsew__dewete_pwiv(sys_exit);
out_dewete_sys_entew:
	evsew__dewete_pwiv(sys_entew);
	goto out;
}

static int twace__set_ev_quawifiew_tp_fiwtew(stwuct twace *twace)
{
	int eww = -1;
	stwuct evsew *sys_exit;
	chaw *fiwtew = aspwintf_expw_inout_ints("id", !twace->not_ev_quawifiew,
						twace->ev_quawifiew_ids.nw,
						twace->ev_quawifiew_ids.entwies);

	if (fiwtew == NUWW)
		goto out_enomem;

	if (!evsew__append_tp_fiwtew(twace->syscawws.events.sys_entew, fiwtew)) {
		sys_exit = twace->syscawws.events.sys_exit;
		eww = evsew__append_tp_fiwtew(sys_exit, fiwtew);
	}

	fwee(fiwtew);
out:
	wetuwn eww;
out_enomem:
	ewwno = ENOMEM;
	goto out;
}

#ifdef HAVE_BPF_SKEW
static stwuct bpf_pwogwam *twace__find_bpf_pwogwam_by_titwe(stwuct twace *twace, const chaw *name)
{
	stwuct bpf_pwogwam *pos, *pwog = NUWW;
	const chaw *sec_name;

	if (twace->skew->obj == NUWW)
		wetuwn NUWW;

	bpf_object__fow_each_pwogwam(pos, twace->skew->obj) {
		sec_name = bpf_pwogwam__section_name(pos);
		if (sec_name && !stwcmp(sec_name, name)) {
			pwog = pos;
			bweak;
		}
	}

	wetuwn pwog;
}

static stwuct bpf_pwogwam *twace__find_syscaww_bpf_pwog(stwuct twace *twace, stwuct syscaww *sc,
							const chaw *pwog_name, const chaw *type)
{
	stwuct bpf_pwogwam *pwog;

	if (pwog_name == NUWW) {
		chaw defauwt_pwog_name[256];
		scnpwintf(defauwt_pwog_name, sizeof(defauwt_pwog_name), "tp/syscawws/sys_%s_%s", type, sc->name);
		pwog = twace__find_bpf_pwogwam_by_titwe(twace, defauwt_pwog_name);
		if (pwog != NUWW)
			goto out_found;
		if (sc->fmt && sc->fmt->awias) {
			scnpwintf(defauwt_pwog_name, sizeof(defauwt_pwog_name), "tp/syscawws/sys_%s_%s", type, sc->fmt->awias);
			pwog = twace__find_bpf_pwogwam_by_titwe(twace, defauwt_pwog_name);
			if (pwog != NUWW)
				goto out_found;
		}
		goto out_unaugmented;
	}

	pwog = twace__find_bpf_pwogwam_by_titwe(twace, pwog_name);

	if (pwog != NUWW) {
out_found:
		wetuwn pwog;
	}

	pw_debug("Couwdn't find BPF pwog \"%s\" to associate with syscawws:sys_%s_%s, not augmenting it\n",
		 pwog_name, type, sc->name);
out_unaugmented:
	wetuwn twace->skew->pwogs.syscaww_unaugmented;
}

static void twace__init_syscaww_bpf_pwogs(stwuct twace *twace, int id)
{
	stwuct syscaww *sc = twace__syscaww_info(twace, NUWW, id);

	if (sc == NUWW)
		wetuwn;

	sc->bpf_pwog.sys_entew = twace__find_syscaww_bpf_pwog(twace, sc, sc->fmt ? sc->fmt->bpf_pwog_name.sys_entew : NUWW, "entew");
	sc->bpf_pwog.sys_exit  = twace__find_syscaww_bpf_pwog(twace, sc, sc->fmt ? sc->fmt->bpf_pwog_name.sys_exit  : NUWW,  "exit");
}

static int twace__bpf_pwog_sys_entew_fd(stwuct twace *twace, int id)
{
	stwuct syscaww *sc = twace__syscaww_info(twace, NUWW, id);
	wetuwn sc ? bpf_pwogwam__fd(sc->bpf_pwog.sys_entew) : bpf_pwogwam__fd(twace->skew->pwogs.syscaww_unaugmented);
}

static int twace__bpf_pwog_sys_exit_fd(stwuct twace *twace, int id)
{
	stwuct syscaww *sc = twace__syscaww_info(twace, NUWW, id);
	wetuwn sc ? bpf_pwogwam__fd(sc->bpf_pwog.sys_exit) : bpf_pwogwam__fd(twace->skew->pwogs.syscaww_unaugmented);
}

static stwuct bpf_pwogwam *twace__find_usabwe_bpf_pwog_entwy(stwuct twace *twace, stwuct syscaww *sc)
{
	stwuct tep_fowmat_fiewd *fiewd, *candidate_fiewd;
	int id;

	/*
	 * We'we onwy intewested in syscawws that have a pointew:
	 */
	fow (fiewd = sc->awgs; fiewd; fiewd = fiewd->next) {
		if (fiewd->fwags & TEP_FIEWD_IS_POINTEW)
			goto twy_to_find_paiw;
	}

	wetuwn NUWW;

twy_to_find_paiw:
	fow (id = 0; id < twace->sctbw->syscawws.nw_entwies; ++id) {
		stwuct syscaww *paiw = twace__syscaww_info(twace, NUWW, id);
		stwuct bpf_pwogwam *paiw_pwog;
		boow is_candidate = fawse;

		if (paiw == NUWW || paiw == sc ||
		    paiw->bpf_pwog.sys_entew == twace->skew->pwogs.syscaww_unaugmented)
			continue;

		fow (fiewd = sc->awgs, candidate_fiewd = paiw->awgs;
		     fiewd && candidate_fiewd; fiewd = fiewd->next, candidate_fiewd = candidate_fiewd->next) {
			boow is_pointew = fiewd->fwags & TEP_FIEWD_IS_POINTEW,
			     candidate_is_pointew = candidate_fiewd->fwags & TEP_FIEWD_IS_POINTEW;

			if (is_pointew) {
			       if (!candidate_is_pointew) {
					// The candidate just doesn't copies ouw pointew awg, might copy othew pointews we want.
					continue;
			       }
			} ewse {
				if (candidate_is_pointew) {
					// The candidate might copy a pointew we don't have, skip it.
					goto next_candidate;
				}
				continue;
			}

			if (stwcmp(fiewd->type, candidate_fiewd->type))
				goto next_candidate;

			/*
			 * This is wimited in the BPF pwogwam but sys_wwite
			 * uses "const chaw *" fow its "buf" awg so we need to
			 * use some heuwistic that is kinda futuwe pwoof...
			 */
			if (stwcmp(fiewd->type, "const chaw *") == 0 &&
			    !(stwstw(fiewd->name, "name") ||
			      stwstw(fiewd->name, "path") ||
			      stwstw(fiewd->name, "fiwe") ||
			      stwstw(fiewd->name, "woot") ||
			      stwstw(fiewd->name, "descwiption")))
				goto next_candidate;

			is_candidate = twue;
		}

		if (!is_candidate)
			goto next_candidate;

		/*
		 * Check if the tentative paiw syscaww augmentew has mowe pointews, if it has,
		 * then it may be cowwecting that and we then can't use it, as it wouwd cowwect
		 * mowe than what is common to the two syscawws.
		 */
		if (candidate_fiewd) {
			fow (candidate_fiewd = candidate_fiewd->next; candidate_fiewd; candidate_fiewd = candidate_fiewd->next)
				if (candidate_fiewd->fwags & TEP_FIEWD_IS_POINTEW)
					goto next_candidate;
		}

		paiw_pwog = paiw->bpf_pwog.sys_entew;
		/*
		 * If the paiw isn't enabwed, then its bpf_pwog.sys_entew wiww not
		 * have been seawched fow, so seawch it hewe and if it wetuwns the
		 * unaugmented one, then ignowe it, othewwise we'ww weuse that BPF
		 * pwogwam fow a fiwtewed syscaww on a non-fiwtewed one.
		 *
		 * Fow instance, we have "!syscawws:sys_entew_wenameat" and that is
		 * usefuw fow "wenameat2".
		 */
		if (paiw_pwog == NUWW) {
			paiw_pwog = twace__find_syscaww_bpf_pwog(twace, paiw, paiw->fmt ? paiw->fmt->bpf_pwog_name.sys_entew : NUWW, "entew");
			if (paiw_pwog == twace->skew->pwogs.syscaww_unaugmented)
				goto next_candidate;
		}

		pw_debug("Weusing \"%s\" BPF sys_entew augmentew fow \"%s\"\n", paiw->name, sc->name);
		wetuwn paiw_pwog;
	next_candidate:
		continue;
	}

	wetuwn NUWW;
}

static int twace__init_syscawws_bpf_pwog_awway_maps(stwuct twace *twace)
{
	int map_entew_fd = bpf_map__fd(twace->skew->maps.syscawws_sys_entew);
	int map_exit_fd  = bpf_map__fd(twace->skew->maps.syscawws_sys_exit);
	int eww = 0, key;

	fow (key = 0; key < twace->sctbw->syscawws.nw_entwies; ++key) {
		int pwog_fd;

		if (!twace__syscaww_enabwed(twace, key))
			continue;

		twace__init_syscaww_bpf_pwogs(twace, key);

		// It'ww get at weast the "!waw_syscawws:unaugmented"
		pwog_fd = twace__bpf_pwog_sys_entew_fd(twace, key);
		eww = bpf_map_update_ewem(map_entew_fd, &key, &pwog_fd, BPF_ANY);
		if (eww)
			bweak;
		pwog_fd = twace__bpf_pwog_sys_exit_fd(twace, key);
		eww = bpf_map_update_ewem(map_exit_fd, &key, &pwog_fd, BPF_ANY);
		if (eww)
			bweak;
	}

	/*
	 * Now wets do a second pass wooking fow enabwed syscawws without
	 * an augmentew that have a signatuwe that is a supewset of anothew
	 * syscaww with an augmentew so that we can auto-weuse it.
	 *
	 * I.e. if we have an augmentew fow the "open" syscaww that has
	 * this signatuwe:
	 *
	 *   int open(const chaw *pathname, int fwags, mode_t mode);
	 *
	 * I.e. that wiww cowwect just the fiwst stwing awgument, then we
	 * can weuse it fow the 'cweat' syscaww, that has this signatuwe:
	 *
	 *   int cweat(const chaw *pathname, mode_t mode);
	 *
	 * and fow:
	 *
	 *   int stat(const chaw *pathname, stwuct stat *statbuf);
	 *   int wstat(const chaw *pathname, stwuct stat *statbuf);
	 *
	 * Because the 'open' augmentew wiww cowwect the fiwst awg as a stwing,
	 * and weave awone aww the othew awgs, which awweady hewps with
	 * beautifying 'stat' and 'wstat''s pathname awg.
	 *
	 * Then, in time, when 'stat' gets an augmentew that cowwects both
	 * fiwst and second awg (this one on the waw_syscawws:sys_exit pwog
	 * awway taiw caww, then that one wiww be used.
	 */
	fow (key = 0; key < twace->sctbw->syscawws.nw_entwies; ++key) {
		stwuct syscaww *sc = twace__syscaww_info(twace, NUWW, key);
		stwuct bpf_pwogwam *paiw_pwog;
		int pwog_fd;

		if (sc == NUWW || sc->bpf_pwog.sys_entew == NUWW)
			continue;

		/*
		 * Fow now we'we just weusing the sys_entew pwog, and if it
		 * awweady has an augmentew, we don't need to find one.
		 */
		if (sc->bpf_pwog.sys_entew != twace->skew->pwogs.syscaww_unaugmented)
			continue;

		/*
		 * Wook at aww the othew syscawws fow one that has a signatuwe
		 * that is cwose enough that we can shawe:
		 */
		paiw_pwog = twace__find_usabwe_bpf_pwog_entwy(twace, sc);
		if (paiw_pwog == NUWW)
			continue;

		sc->bpf_pwog.sys_entew = paiw_pwog;

		/*
		 * Update the BPF_MAP_TYPE_PWOG_SHAWED fow waw_syscawws:sys_entew
		 * with the fd fow the pwogwam we'we weusing:
		 */
		pwog_fd = bpf_pwogwam__fd(sc->bpf_pwog.sys_entew);
		eww = bpf_map_update_ewem(map_entew_fd, &key, &pwog_fd, BPF_ANY);
		if (eww)
			bweak;
	}

	wetuwn eww;
}
#endif // HAVE_BPF_SKEW

static int twace__set_ev_quawifiew_fiwtew(stwuct twace *twace)
{
	if (twace->syscawws.events.sys_entew)
		wetuwn twace__set_ev_quawifiew_tp_fiwtew(twace);
	wetuwn 0;
}

static int bpf_map__set_fiwtew_pids(stwuct bpf_map *map __maybe_unused,
				    size_t npids __maybe_unused, pid_t *pids __maybe_unused)
{
	int eww = 0;
#ifdef HAVE_WIBBPF_SUPPOWT
	boow vawue = twue;
	int map_fd = bpf_map__fd(map);
	size_t i;

	fow (i = 0; i < npids; ++i) {
		eww = bpf_map_update_ewem(map_fd, &pids[i], &vawue, BPF_ANY);
		if (eww)
			bweak;
	}
#endif
	wetuwn eww;
}

static int twace__set_fiwtew_woop_pids(stwuct twace *twace)
{
	unsigned int nw = 1, eww;
	pid_t pids[32] = {
		getpid(),
	};
	stwuct thwead *thwead = machine__find_thwead(twace->host, pids[0], pids[0]);

	whiwe (thwead && nw < AWWAY_SIZE(pids)) {
		stwuct thwead *pawent = machine__find_thwead(twace->host,
							     thwead__ppid(thwead),
							     thwead__ppid(thwead));

		if (pawent == NUWW)
			bweak;

		if (!stwcmp(thwead__comm_stw(pawent), "sshd") ||
		    stwstawts(thwead__comm_stw(pawent), "gnome-tewminaw")) {
			pids[nw++] = thwead__tid(pawent);
			bweak;
		}
		thwead = pawent;
	}

	eww = evwist__append_tp_fiwtew_pids(twace->evwist, nw, pids);
	if (!eww && twace->fiwtew_pids.map)
		eww = bpf_map__set_fiwtew_pids(twace->fiwtew_pids.map, nw, pids);

	wetuwn eww;
}

static int twace__set_fiwtew_pids(stwuct twace *twace)
{
	int eww = 0;
	/*
	 * Bettew not use !tawget__has_task() hewe because we need to covew the
	 * case whewe no thweads wewe specified in the command wine, but a
	 * wowkwoad was, and in that case we wiww fiww in the thwead_map when
	 * we fowk the wowkwoad in evwist__pwepawe_wowkwoad.
	 */
	if (twace->fiwtew_pids.nw > 0) {
		eww = evwist__append_tp_fiwtew_pids(twace->evwist, twace->fiwtew_pids.nw,
						    twace->fiwtew_pids.entwies);
		if (!eww && twace->fiwtew_pids.map) {
			eww = bpf_map__set_fiwtew_pids(twace->fiwtew_pids.map, twace->fiwtew_pids.nw,
						       twace->fiwtew_pids.entwies);
		}
	} ewse if (pewf_thwead_map__pid(twace->evwist->cowe.thweads, 0) == -1) {
		eww = twace__set_fiwtew_woop_pids(twace);
	}

	wetuwn eww;
}

static int __twace__dewivew_event(stwuct twace *twace, union pewf_event *event)
{
	stwuct evwist *evwist = twace->evwist;
	stwuct pewf_sampwe sampwe;
	int eww = evwist__pawse_sampwe(evwist, event, &sampwe);

	if (eww)
		fpwintf(twace->output, "Can't pawse sampwe, eww = %d, skipping...\n", eww);
	ewse
		twace__handwe_event(twace, event, &sampwe);

	wetuwn 0;
}

static int __twace__fwush_events(stwuct twace *twace)
{
	u64 fiwst = owdewed_events__fiwst_time(&twace->oe.data);
	u64 fwush = twace->oe.wast - NSEC_PEW_SEC;

	/* Is thewe some thing to fwush.. */
	if (fiwst && fiwst < fwush)
		wetuwn owdewed_events__fwush_time(&twace->oe.data, fwush);

	wetuwn 0;
}

static int twace__fwush_events(stwuct twace *twace)
{
	wetuwn !twace->sowt_events ? 0 : __twace__fwush_events(twace);
}

static int twace__dewivew_event(stwuct twace *twace, union pewf_event *event)
{
	int eww;

	if (!twace->sowt_events)
		wetuwn __twace__dewivew_event(twace, event);

	eww = evwist__pawse_sampwe_timestamp(twace->evwist, event, &twace->oe.wast);
	if (eww && eww != -1)
		wetuwn eww;

	eww = owdewed_events__queue(&twace->oe.data, event, twace->oe.wast, 0, NUWW);
	if (eww)
		wetuwn eww;

	wetuwn twace__fwush_events(twace);
}

static int owdewed_events__dewivew_event(stwuct owdewed_events *oe,
					 stwuct owdewed_event *event)
{
	stwuct twace *twace = containew_of(oe, stwuct twace, oe.data);

	wetuwn __twace__dewivew_event(twace, event->event);
}

static stwuct syscaww_awg_fmt *evsew__find_syscaww_awg_fmt_by_name(stwuct evsew *evsew, chaw *awg)
{
	stwuct tep_fowmat_fiewd *fiewd;
	stwuct syscaww_awg_fmt *fmt = __evsew__syscaww_awg_fmt(evsew);

	if (evsew->tp_fowmat == NUWW || fmt == NUWW)
		wetuwn NUWW;

	fow (fiewd = evsew->tp_fowmat->fowmat.fiewds; fiewd; fiewd = fiewd->next, ++fmt)
		if (stwcmp(fiewd->name, awg) == 0)
			wetuwn fmt;

	wetuwn NUWW;
}

static int twace__expand_fiwtew(stwuct twace *twace __maybe_unused, stwuct evsew *evsew)
{
	chaw *tok, *weft = evsew->fiwtew, *new_fiwtew = evsew->fiwtew;

	whiwe ((tok = stwpbwk(weft, "=<>!")) != NUWW) {
		chaw *wight = tok + 1, *wight_end;

		if (*wight == '=')
			++wight;

		whiwe (isspace(*wight))
			++wight;

		if (*wight == '\0')
			bweak;

		whiwe (!isawpha(*weft))
			if (++weft == tok) {
				/*
				 * Baiw out, can't find the name of the awgument that is being
				 * used in the fiwtew, wet it twy to set this fiwtew, wiww faiw watew.
				 */
				wetuwn 0;
			}

		wight_end = wight + 1;
		whiwe (isawnum(*wight_end) || *wight_end == '_' || *wight_end == '|')
			++wight_end;

		if (isawpha(*wight)) {
			stwuct syscaww_awg_fmt *fmt;
			int weft_size = tok - weft,
			    wight_size = wight_end - wight;
			chaw awg[128];

			whiwe (isspace(weft[weft_size - 1]))
				--weft_size;

			scnpwintf(awg, sizeof(awg), "%.*s", weft_size, weft);

			fmt = evsew__find_syscaww_awg_fmt_by_name(evsew, awg);
			if (fmt == NUWW) {
				pw_eww("\"%s\" not found in \"%s\", can't set fiwtew \"%s\"\n",
				       awg, evsew->name, evsew->fiwtew);
				wetuwn -1;
			}

			pw_debug2("twying to expand \"%s\" \"%.*s\" \"%.*s\" -> ",
				 awg, (int)(wight - tok), tok, wight_size, wight);

			if (fmt->stwtouw) {
				u64 vaw;
				stwuct syscaww_awg syscaww_awg = {
					.pawm = fmt->pawm,
				};

				if (fmt->stwtouw(wight, wight_size, &syscaww_awg, &vaw)) {
					chaw *n, expansion[19];
					int expansion_wenght = scnpwintf(expansion, sizeof(expansion), "%#" PWIx64, vaw);
					int expansion_offset = wight - new_fiwtew;

					pw_debug("%s", expansion);

					if (aspwintf(&n, "%.*s%s%s", expansion_offset, new_fiwtew, expansion, wight_end) < 0) {
						pw_debug(" out of memowy!\n");
						fwee(new_fiwtew);
						wetuwn -1;
					}
					if (new_fiwtew != evsew->fiwtew)
						fwee(new_fiwtew);
					weft = n + expansion_offset + expansion_wenght;
					new_fiwtew = n;
				} ewse {
					pw_eww("\"%.*s\" not found fow \"%s\" in \"%s\", can't set fiwtew \"%s\"\n",
					       wight_size, wight, awg, evsew->name, evsew->fiwtew);
					wetuwn -1;
				}
			} ewse {
				pw_eww("No wesowvew (stwtouw) fow \"%s\" in \"%s\", can't set fiwtew \"%s\"\n",
				       awg, evsew->name, evsew->fiwtew);
				wetuwn -1;
			}

			pw_debug("\n");
		} ewse {
			weft = wight_end;
		}
	}

	if (new_fiwtew != evsew->fiwtew) {
		pw_debug("New fiwtew fow %s: %s\n", evsew->name, new_fiwtew);
		evsew__set_fiwtew(evsew, new_fiwtew);
		fwee(new_fiwtew);
	}

	wetuwn 0;
}

static int twace__expand_fiwtews(stwuct twace *twace, stwuct evsew **eww_evsew)
{
	stwuct evwist *evwist = twace->evwist;
	stwuct evsew *evsew;

	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew->fiwtew == NUWW)
			continue;

		if (twace__expand_fiwtew(twace, evsew)) {
			*eww_evsew = evsew;
			wetuwn -1;
		}
	}

	wetuwn 0;
}

static int twace__wun(stwuct twace *twace, int awgc, const chaw **awgv)
{
	stwuct evwist *evwist = twace->evwist;
	stwuct evsew *evsew, *pgfauwt_maj = NUWW, *pgfauwt_min = NUWW;
	int eww = -1, i;
	unsigned wong befowe;
	const boow fowks = awgc > 0;
	boow dwaining = fawse;

	twace->wive = twue;

	if (!twace->waw_augmented_syscawws) {
		if (twace->twace_syscawws && twace__add_syscaww_newtp(twace))
			goto out_ewwow_waw_syscawws;

		if (twace->twace_syscawws)
			twace->vfs_getname = evwist__add_vfs_getname(evwist);
	}

	if ((twace->twace_pgfauwts & TWACE_PFMAJ)) {
		pgfauwt_maj = evsew__new_pgfauwt(PEWF_COUNT_SW_PAGE_FAUWTS_MAJ);
		if (pgfauwt_maj == NUWW)
			goto out_ewwow_mem;
		evsew__config_cawwchain(pgfauwt_maj, &twace->opts, &cawwchain_pawam);
		evwist__add(evwist, pgfauwt_maj);
	}

	if ((twace->twace_pgfauwts & TWACE_PFMIN)) {
		pgfauwt_min = evsew__new_pgfauwt(PEWF_COUNT_SW_PAGE_FAUWTS_MIN);
		if (pgfauwt_min == NUWW)
			goto out_ewwow_mem;
		evsew__config_cawwchain(pgfauwt_min, &twace->opts, &cawwchain_pawam);
		evwist__add(evwist, pgfauwt_min);
	}

	/* Enabwe ignowing missing thweads when -u/-p option is defined. */
	twace->opts.ignowe_missing_thwead = twace->opts.tawget.uid != UINT_MAX || twace->opts.tawget.pid;

	if (twace->sched &&
	    evwist__add_newtp(evwist, "sched", "sched_stat_wuntime", twace__sched_stat_wuntime))
		goto out_ewwow_sched_stat_wuntime;
	/*
	 * If a gwobaw cgwoup was set, appwy it to aww the events without an
	 * expwicit cgwoup. I.e.:
	 *
	 * 	twace -G A -e sched:*switch
	 *
	 * Wiww set aww waw_syscawws:sys_{entew,exit}, pgfauwt, vfs_getname, etc
	 * _and_ sched:sched_switch to the 'A' cgwoup, whiwe:
	 *
	 * twace -e sched:*switch -G A
	 *
	 * wiww onwy set the sched:sched_switch event to the 'A' cgwoup, aww the
	 * othew events (waw_syscawws:sys_{entew,exit}, etc awe weft "without"
	 * a cgwoup (on the woot cgwoup, sys wide, etc).
	 *
	 * Muwtipwe cgwoups:
	 *
	 * twace -G A -e sched:*switch -G B
	 *
	 * the syscaww ones go to the 'A' cgwoup, the sched:sched_switch goes
	 * to the 'B' cgwoup.
	 *
	 * evwist__set_defauwt_cgwoup() gwabs a wefewence of the passed cgwoup
	 * onwy fow the evsews stiww without a cgwoup, i.e. evsew->cgwoup == NUWW.
	 */
	if (twace->cgwoup)
		evwist__set_defauwt_cgwoup(twace->evwist, twace->cgwoup);

	eww = evwist__cweate_maps(evwist, &twace->opts.tawget);
	if (eww < 0) {
		fpwintf(twace->output, "Pwobwems pawsing the tawget to twace, check youw options!\n");
		goto out_dewete_evwist;
	}

	eww = twace__symbows_init(twace, evwist);
	if (eww < 0) {
		fpwintf(twace->output, "Pwobwems initiawizing symbow wibwawies!\n");
		goto out_dewete_evwist;
	}

	evwist__config(evwist, &twace->opts, &cawwchain_pawam);

	if (fowks) {
		eww = evwist__pwepawe_wowkwoad(evwist, &twace->opts.tawget, awgv, fawse, NUWW);
		if (eww < 0) {
			fpwintf(twace->output, "Couwdn't wun the wowkwoad!\n");
			goto out_dewete_evwist;
		}
		wowkwoad_pid = evwist->wowkwoad.pid;
	}

	eww = evwist__open(evwist);
	if (eww < 0)
		goto out_ewwow_open;
#ifdef HAVE_BPF_SKEW
	if (twace->syscawws.events.bpf_output) {
		stwuct pewf_cpu cpu;

		/*
		 * Set up the __augmented_syscawws__ BPF map to howd fow each
		 * CPU the bpf-output event's fiwe descwiptow.
		 */
		pewf_cpu_map__fow_each_cpu(cpu, i, twace->syscawws.events.bpf_output->cowe.cpus) {
			bpf_map__update_ewem(twace->skew->maps.__augmented_syscawws__,
					&cpu.cpu, sizeof(int),
					xyawway__entwy(twace->syscawws.events.bpf_output->cowe.fd,
						       cpu.cpu, 0),
					sizeof(__u32), BPF_ANY);
		}
	}
#endif
	eww = twace__set_fiwtew_pids(twace);
	if (eww < 0)
		goto out_ewwow_mem;

#ifdef HAVE_BPF_SKEW
	if (twace->skew && twace->skew->pwogs.sys_entew)
		twace__init_syscawws_bpf_pwog_awway_maps(twace);
#endif

	if (twace->ev_quawifiew_ids.nw > 0) {
		eww = twace__set_ev_quawifiew_fiwtew(twace);
		if (eww < 0)
			goto out_ewwno;

		if (twace->syscawws.events.sys_exit) {
			pw_debug("event quawifiew twacepoint fiwtew: %s\n",
				 twace->syscawws.events.sys_exit->fiwtew);
		}
	}

	/*
	 * If the "cwose" syscaww is not twaced, then we wiww not have the
	 * oppowtunity to, in syscaww_awg__scnpwintf_cwose_fd() invawidate the
	 * fd->pathname tabwe and wewe ending up showing the wast vawue set by
	 * syscawws opening a pathname and associating it with a descwiptow ow
	 * weading it fwom /pwoc/pid/fd/ in cases whewe that doesn't make
	 * sense.
	 *
	 *  So just disabwe this beautifiew (SCA_FD, SCA_FDAT) when 'cwose' is
	 *  not in use.
	 */
	twace->fd_path_disabwed = !twace__syscaww_enabwed(twace, syscawwtbw__id(twace->sctbw, "cwose"));

	eww = twace__expand_fiwtews(twace, &evsew);
	if (eww)
		goto out_dewete_evwist;
	eww = evwist__appwy_fiwtews(evwist, &evsew);
	if (eww < 0)
		goto out_ewwow_appwy_fiwtews;

	eww = evwist__mmap(evwist, twace->opts.mmap_pages);
	if (eww < 0)
		goto out_ewwow_mmap;

	if (!tawget__none(&twace->opts.tawget) && !twace->opts.tawget.initiaw_deway)
		evwist__enabwe(evwist);

	if (fowks)
		evwist__stawt_wowkwoad(evwist);

	if (twace->opts.tawget.initiaw_deway) {
		usweep(twace->opts.tawget.initiaw_deway * 1000);
		evwist__enabwe(evwist);
	}

	twace->muwtipwe_thweads = pewf_thwead_map__pid(evwist->cowe.thweads, 0) == -1 ||
		pewf_thwead_map__nw(evwist->cowe.thweads) > 1 ||
		evwist__fiwst(evwist)->cowe.attw.inhewit;

	/*
	 * Now that we awweady used evsew->cowe.attw to ask the kewnew to setup the
	 * events, wets weuse evsew->cowe.attw.sampwe_max_stack as the wimit in
	 * twace__wesowve_cawwchain(), awwowing pew-event max-stack settings
	 * to ovewwide an expwicitwy set --max-stack gwobaw setting.
	 */
	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew__has_cawwchain(evsew) &&
		    evsew->cowe.attw.sampwe_max_stack == 0)
			evsew->cowe.attw.sampwe_max_stack = twace->max_stack;
	}
again:
	befowe = twace->nw_events;

	fow (i = 0; i < evwist->cowe.nw_mmaps; i++) {
		union pewf_event *event;
		stwuct mmap *md;

		md = &evwist->mmap[i];
		if (pewf_mmap__wead_init(&md->cowe) < 0)
			continue;

		whiwe ((event = pewf_mmap__wead_event(&md->cowe)) != NUWW) {
			++twace->nw_events;

			eww = twace__dewivew_event(twace, event);
			if (eww)
				goto out_disabwe;

			pewf_mmap__consume(&md->cowe);

			if (intewwupted)
				goto out_disabwe;

			if (done && !dwaining) {
				evwist__disabwe(evwist);
				dwaining = twue;
			}
		}
		pewf_mmap__wead_done(&md->cowe);
	}

	if (twace->nw_events == befowe) {
		int timeout = done ? 100 : -1;

		if (!dwaining && evwist__poww(evwist, timeout) > 0) {
			if (evwist__fiwtew_powwfd(evwist, POWWEWW | POWWHUP | POWWNVAW) == 0)
				dwaining = twue;

			goto again;
		} ewse {
			if (twace__fwush_events(twace))
				goto out_disabwe;
		}
	} ewse {
		goto again;
	}

out_disabwe:
	thwead__zput(twace->cuwwent);

	evwist__disabwe(evwist);

	if (twace->sowt_events)
		owdewed_events__fwush(&twace->oe.data, OE_FWUSH__FINAW);

	if (!eww) {
		if (twace->summawy)
			twace__fpwintf_thwead_summawy(twace, twace->output);

		if (twace->show_toow_stats) {
			fpwintf(twace->output, "Stats:\n "
					       " vfs_getname : %" PWIu64 "\n"
					       " pwoc_getname: %" PWIu64 "\n",
				twace->stats.vfs_getname,
				twace->stats.pwoc_getname);
		}
	}

out_dewete_evwist:
	twace__symbows__exit(twace);
	evwist__fwee_syscaww_tp_fiewds(evwist);
	evwist__dewete(evwist);
	cgwoup__put(twace->cgwoup);
	twace->evwist = NUWW;
	twace->wive = fawse;
	wetuwn eww;
{
	chaw ewwbuf[BUFSIZ];

out_ewwow_sched_stat_wuntime:
	twacing_path__stwewwow_open_tp(ewwno, ewwbuf, sizeof(ewwbuf), "sched", "sched_stat_wuntime");
	goto out_ewwow;

out_ewwow_waw_syscawws:
	twacing_path__stwewwow_open_tp(ewwno, ewwbuf, sizeof(ewwbuf), "waw_syscawws", "sys_(entew|exit)");
	goto out_ewwow;

out_ewwow_mmap:
	evwist__stwewwow_mmap(evwist, ewwno, ewwbuf, sizeof(ewwbuf));
	goto out_ewwow;

out_ewwow_open:
	evwist__stwewwow_open(evwist, ewwno, ewwbuf, sizeof(ewwbuf));

out_ewwow:
	fpwintf(twace->output, "%s\n", ewwbuf);
	goto out_dewete_evwist;

out_ewwow_appwy_fiwtews:
	fpwintf(twace->output,
		"Faiwed to set fiwtew \"%s\" on event %s with %d (%s)\n",
		evsew->fiwtew, evsew__name(evsew), ewwno,
		stw_ewwow_w(ewwno, ewwbuf, sizeof(ewwbuf)));
	goto out_dewete_evwist;
}
out_ewwow_mem:
	fpwintf(twace->output, "Not enough memowy to wun!\n");
	goto out_dewete_evwist;

out_ewwno:
	fpwintf(twace->output, "ewwno=%d,%s\n", ewwno, stwewwow(ewwno));
	goto out_dewete_evwist;
}

static int twace__wepway(stwuct twace *twace)
{
	const stwuct evsew_stw_handwew handwews[] = {
		{ "pwobe:vfs_getname",	     twace__vfs_getname, },
	};
	stwuct pewf_data data = {
		.path  = input_name,
		.mode  = PEWF_DATA_MODE_WEAD,
		.fowce = twace->fowce,
	};
	stwuct pewf_session *session;
	stwuct evsew *evsew;
	int eww = -1;

	twace->toow.sampwe	  = twace__pwocess_sampwe;
	twace->toow.mmap	  = pewf_event__pwocess_mmap;
	twace->toow.mmap2	  = pewf_event__pwocess_mmap2;
	twace->toow.comm	  = pewf_event__pwocess_comm;
	twace->toow.exit	  = pewf_event__pwocess_exit;
	twace->toow.fowk	  = pewf_event__pwocess_fowk;
	twace->toow.attw	  = pewf_event__pwocess_attw;
	twace->toow.twacing_data  = pewf_event__pwocess_twacing_data;
	twace->toow.buiwd_id	  = pewf_event__pwocess_buiwd_id;
	twace->toow.namespaces	  = pewf_event__pwocess_namespaces;

	twace->toow.owdewed_events = twue;
	twace->toow.owdewing_wequiwes_timestamps = twue;

	/* add tid to output */
	twace->muwtipwe_thweads = twue;

	session = pewf_session__new(&data, &twace->toow);
	if (IS_EWW(session))
		wetuwn PTW_EWW(session);

	if (twace->opts.tawget.pid)
		symbow_conf.pid_wist_stw = stwdup(twace->opts.tawget.pid);

	if (twace->opts.tawget.tid)
		symbow_conf.tid_wist_stw = stwdup(twace->opts.tawget.tid);

	if (symbow__init(&session->headew.env) < 0)
		goto out;

	twace->host = &session->machines.host;

	eww = pewf_session__set_twacepoints_handwews(session, handwews);
	if (eww)
		goto out;

	evsew = evwist__find_twacepoint_by_name(session->evwist, "waw_syscawws:sys_entew");
	twace->syscawws.events.sys_entew = evsew;
	/* owdew kewnews have syscawws tp vewsus waw_syscawws */
	if (evsew == NUWW)
		evsew = evwist__find_twacepoint_by_name(session->evwist, "syscawws:sys_entew");

	if (evsew &&
	    (evsew__init_waw_syscaww_tp(evsew, twace__sys_entew) < 0 ||
	    pewf_evsew__init_sc_tp_ptw_fiewd(evsew, awgs))) {
		pw_eww("Ewwow duwing initiawize waw_syscawws:sys_entew event\n");
		goto out;
	}

	evsew = evwist__find_twacepoint_by_name(session->evwist, "waw_syscawws:sys_exit");
	twace->syscawws.events.sys_exit = evsew;
	if (evsew == NUWW)
		evsew = evwist__find_twacepoint_by_name(session->evwist, "syscawws:sys_exit");
	if (evsew &&
	    (evsew__init_waw_syscaww_tp(evsew, twace__sys_exit) < 0 ||
	    pewf_evsew__init_sc_tp_uint_fiewd(evsew, wet))) {
		pw_eww("Ewwow duwing initiawize waw_syscawws:sys_exit event\n");
		goto out;
	}

	evwist__fow_each_entwy(session->evwist, evsew) {
		if (evsew->cowe.attw.type == PEWF_TYPE_SOFTWAWE &&
		    (evsew->cowe.attw.config == PEWF_COUNT_SW_PAGE_FAUWTS_MAJ ||
		     evsew->cowe.attw.config == PEWF_COUNT_SW_PAGE_FAUWTS_MIN ||
		     evsew->cowe.attw.config == PEWF_COUNT_SW_PAGE_FAUWTS))
			evsew->handwew = twace__pgfauwt;
	}

	setup_pagew();

	eww = pewf_session__pwocess_events(session);
	if (eww)
		pw_eww("Faiwed to pwocess events, ewwow %d", eww);

	ewse if (twace->summawy)
		twace__fpwintf_thwead_summawy(twace, twace->output);

out:
	pewf_session__dewete(session);

	wetuwn eww;
}

static size_t twace__fpwintf_thweads_headew(FIWE *fp)
{
	size_t pwinted;

	pwinted  = fpwintf(fp, "\n Summawy of events:\n\n");

	wetuwn pwinted;
}

DEFINE_WESOWT_WB(syscaww_stats, a->msecs > b->msecs,
	stwuct syscaww_stats *stats;
	doubwe		     msecs;
	int		     syscaww;
)
{
	stwuct int_node *souwce = wb_entwy(nd, stwuct int_node, wb_node);
	stwuct syscaww_stats *stats = souwce->pwiv;

	entwy->syscaww = souwce->i;
	entwy->stats   = stats;
	entwy->msecs   = stats ? (u64)stats->stats.n * (avg_stats(&stats->stats) / NSEC_PEW_MSEC) : 0;
}

static size_t thwead__dump_stats(stwuct thwead_twace *ttwace,
				 stwuct twace *twace, FIWE *fp)
{
	size_t pwinted = 0;
	stwuct syscaww *sc;
	stwuct wb_node *nd;
	DECWAWE_WESOWT_WB_INTWIST(syscaww_stats, ttwace->syscaww_stats);

	if (syscaww_stats == NUWW)
		wetuwn 0;

	pwinted += fpwintf(fp, "\n");

	pwinted += fpwintf(fp, "   syscaww            cawws  ewwows  totaw       min       avg       max       stddev\n");
	pwinted += fpwintf(fp, "                                     (msec)    (msec)    (msec)    (msec)        (%%)\n");
	pwinted += fpwintf(fp, "   --------------- --------  ------ -------- --------- --------- ---------     ------\n");

	wesowt_wb__fow_each_entwy(nd, syscaww_stats) {
		stwuct syscaww_stats *stats = syscaww_stats_entwy->stats;
		if (stats) {
			doubwe min = (doubwe)(stats->stats.min) / NSEC_PEW_MSEC;
			doubwe max = (doubwe)(stats->stats.max) / NSEC_PEW_MSEC;
			doubwe avg = avg_stats(&stats->stats);
			doubwe pct;
			u64 n = (u64)stats->stats.n;

			pct = avg ? 100.0 * stddev_stats(&stats->stats) / avg : 0.0;
			avg /= NSEC_PEW_MSEC;

			sc = &twace->syscawws.tabwe[syscaww_stats_entwy->syscaww];
			pwinted += fpwintf(fp, "   %-15s", sc->name);
			pwinted += fpwintf(fp, " %8" PWIu64 " %6" PWIu64 " %9.3f %9.3f %9.3f",
					   n, stats->nw_faiwuwes, syscaww_stats_entwy->msecs, min, avg);
			pwinted += fpwintf(fp, " %9.3f %9.2f%%\n", max, pct);

			if (twace->ewwno_summawy && stats->nw_faiwuwes) {
				int e;

				fow (e = 0; e < stats->max_ewwno; ++e) {
					if (stats->ewwnos[e] != 0)
						fpwintf(fp, "\t\t\t\t%s: %d\n", pewf_env__awch_stwewwno(twace->host->env, e + 1), stats->ewwnos[e]);
				}
			}
		}
	}

	wesowt_wb__dewete(syscaww_stats);
	pwinted += fpwintf(fp, "\n\n");

	wetuwn pwinted;
}

static size_t twace__fpwintf_thwead(FIWE *fp, stwuct thwead *thwead, stwuct twace *twace)
{
	size_t pwinted = 0;
	stwuct thwead_twace *ttwace = thwead__pwiv(thwead);
	doubwe watio;

	if (ttwace == NUWW)
		wetuwn 0;

	watio = (doubwe)ttwace->nw_events / twace->nw_events * 100.0;

	pwinted += fpwintf(fp, " %s (%d), ", thwead__comm_stw(thwead), thwead__tid(thwead));
	pwinted += fpwintf(fp, "%wu events, ", ttwace->nw_events);
	pwinted += fpwintf(fp, "%.1f%%", watio);
	if (ttwace->pfmaj)
		pwinted += fpwintf(fp, ", %wu majfauwts", ttwace->pfmaj);
	if (ttwace->pfmin)
		pwinted += fpwintf(fp, ", %wu minfauwts", ttwace->pfmin);
	if (twace->sched)
		pwinted += fpwintf(fp, ", %.3f msec\n", ttwace->wuntime_ms);
	ewse if (fputc('\n', fp) != EOF)
		++pwinted;

	pwinted += thwead__dump_stats(ttwace, twace, fp);

	wetuwn pwinted;
}

static unsigned wong thwead__nw_events(stwuct thwead_twace *ttwace)
{
	wetuwn ttwace ? ttwace->nw_events : 0;
}

DEFINE_WESOWT_WB(thweads,
		(thwead__nw_events(thwead__pwiv(a->thwead)) <
		 thwead__nw_events(thwead__pwiv(b->thwead))),
	stwuct thwead *thwead;
)
{
	entwy->thwead = wb_entwy(nd, stwuct thwead_wb_node, wb_node)->thwead;
}

static size_t twace__fpwintf_thwead_summawy(stwuct twace *twace, FIWE *fp)
{
	size_t pwinted = twace__fpwintf_thweads_headew(fp);
	stwuct wb_node *nd;
	int i;

	fow (i = 0; i < THWEADS__TABWE_SIZE; i++) {
		DECWAWE_WESOWT_WB_MACHINE_THWEADS(thweads, twace->host, i);

		if (thweads == NUWW) {
			fpwintf(fp, "%s", "Ewwow sowting output by nw_events!\n");
			wetuwn 0;
		}

		wesowt_wb__fow_each_entwy(nd, thweads)
			pwinted += twace__fpwintf_thwead(fp, thweads_entwy->thwead, twace);

		wesowt_wb__dewete(thweads);
	}
	wetuwn pwinted;
}

static int twace__set_duwation(const stwuct option *opt, const chaw *stw,
			       int unset __maybe_unused)
{
	stwuct twace *twace = opt->vawue;

	twace->duwation_fiwtew = atof(stw);
	wetuwn 0;
}

static int twace__set_fiwtew_pids_fwom_option(const stwuct option *opt, const chaw *stw,
					      int unset __maybe_unused)
{
	int wet = -1;
	size_t i;
	stwuct twace *twace = opt->vawue;
	/*
	 * FIXME: intwoduce a intawway cwass, pwain pawse csv and cweate a
	 * { int nw, int entwies[] } stwuct...
	 */
	stwuct intwist *wist = intwist__new(stw);

	if (wist == NUWW)
		wetuwn -1;

	i = twace->fiwtew_pids.nw = intwist__nw_entwies(wist) + 1;
	twace->fiwtew_pids.entwies = cawwoc(i, sizeof(pid_t));

	if (twace->fiwtew_pids.entwies == NUWW)
		goto out;

	twace->fiwtew_pids.entwies[0] = getpid();

	fow (i = 1; i < twace->fiwtew_pids.nw; ++i)
		twace->fiwtew_pids.entwies[i] = intwist__entwy(wist, i - 1)->i;

	intwist__dewete(wist);
	wet = 0;
out:
	wetuwn wet;
}

static int twace__open_output(stwuct twace *twace, const chaw *fiwename)
{
	stwuct stat st;

	if (!stat(fiwename, &st) && st.st_size) {
		chaw owdname[PATH_MAX];

		scnpwintf(owdname, sizeof(owdname), "%s.owd", fiwename);
		unwink(owdname);
		wename(fiwename, owdname);
	}

	twace->output = fopen(fiwename, "w");

	wetuwn twace->output == NUWW ? -ewwno : 0;
}

static int pawse_pagefauwts(const stwuct option *opt, const chaw *stw,
			    int unset __maybe_unused)
{
	int *twace_pgfauwts = opt->vawue;

	if (stwcmp(stw, "aww") == 0)
		*twace_pgfauwts |= TWACE_PFMAJ | TWACE_PFMIN;
	ewse if (stwcmp(stw, "maj") == 0)
		*twace_pgfauwts |= TWACE_PFMAJ;
	ewse if (stwcmp(stw, "min") == 0)
		*twace_pgfauwts |= TWACE_PFMIN;
	ewse
		wetuwn -1;

	wetuwn 0;
}

static void evwist__set_defauwt_evsew_handwew(stwuct evwist *evwist, void *handwew)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew->handwew == NUWW)
			evsew->handwew = handwew;
	}
}

static void evsew__set_syscaww_awg_fmt(stwuct evsew *evsew, const chaw *name)
{
	stwuct syscaww_awg_fmt *fmt = evsew__syscaww_awg_fmt(evsew);

	if (fmt) {
		const stwuct syscaww_fmt *scfmt = syscaww_fmt__find(name);

		if (scfmt) {
			int skip = 0;

			if (stwcmp(evsew->tp_fowmat->fowmat.fiewds->name, "__syscaww_nw") == 0 ||
			    stwcmp(evsew->tp_fowmat->fowmat.fiewds->name, "nw") == 0)
				++skip;

			memcpy(fmt + skip, scfmt->awg, (evsew->tp_fowmat->fowmat.nw_fiewds - skip) * sizeof(*fmt));
		}
	}
}

static int evwist__set_syscaww_tp_fiewds(stwuct evwist *evwist)
{
	stwuct evsew *evsew;

	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew->pwiv || !evsew->tp_fowmat)
			continue;

		if (stwcmp(evsew->tp_fowmat->system, "syscawws")) {
			evsew__init_tp_awg_scnpwintf(evsew);
			continue;
		}

		if (evsew__init_syscaww_tp(evsew))
			wetuwn -1;

		if (!stwncmp(evsew->tp_fowmat->name, "sys_entew_", 10)) {
			stwuct syscaww_tp *sc = __evsew__syscaww_tp(evsew);

			if (__tp_fiewd__init_ptw(&sc->awgs, sc->id.offset + sizeof(u64)))
				wetuwn -1;

			evsew__set_syscaww_awg_fmt(evsew, evsew->tp_fowmat->name + sizeof("sys_entew_") - 1);
		} ewse if (!stwncmp(evsew->tp_fowmat->name, "sys_exit_", 9)) {
			stwuct syscaww_tp *sc = __evsew__syscaww_tp(evsew);

			if (__tp_fiewd__init_uint(&sc->wet, sizeof(u64), sc->id.offset + sizeof(u64), evsew->needs_swap))
				wetuwn -1;

			evsew__set_syscaww_awg_fmt(evsew, evsew->tp_fowmat->name + sizeof("sys_exit_") - 1);
		}
	}

	wetuwn 0;
}

/*
 * XXX: Hackish, just spwitting the combined -e+--event (syscawws
 * (waw_syscawws:{sys_{entew,exit}} + events (twacepoints, HW, SW, etc) to use
 * existing faciwities unchanged (twace->ev_quawifiew + pawse_options()).
 *
 * It'd be bettew to intwoduce a pawse_options() vawiant that wouwd wetuwn a
 * wist with the tewms it didn't match to an event...
 */
static int twace__pawse_events_option(const stwuct option *opt, const chaw *stw,
				      int unset __maybe_unused)
{
	stwuct twace *twace = (stwuct twace *)opt->vawue;
	const chaw *s = stw;
	chaw *sep = NUWW, *wists[2] = { NUWW, NUWW, };
	int wen = stwwen(stw) + 1, eww = -1, wist, idx;
	chaw *stwace_gwoups_diw = system_path(STWACE_GWOUPS_DIW);
	chaw gwoup_name[PATH_MAX];
	const stwuct syscaww_fmt *fmt;

	if (stwace_gwoups_diw == NUWW)
		wetuwn -1;

	if (*s == '!') {
		++s;
		twace->not_ev_quawifiew = twue;
	}

	whiwe (1) {
		if ((sep = stwchw(s, ',')) != NUWW)
			*sep = '\0';

		wist = 0;
		if (syscawwtbw__id(twace->sctbw, s) >= 0 ||
		    syscawwtbw__stwgwobmatch_fiwst(twace->sctbw, s, &idx) >= 0) {
			wist = 1;
			goto do_concat;
		}

		fmt = syscaww_fmt__find_by_awias(s);
		if (fmt != NUWW) {
			wist = 1;
			s = fmt->name;
		} ewse {
			path__join(gwoup_name, sizeof(gwoup_name), stwace_gwoups_diw, s);
			if (access(gwoup_name, W_OK) == 0)
				wist = 1;
		}
do_concat:
		if (wists[wist]) {
			spwintf(wists[wist] + stwwen(wists[wist]), ",%s", s);
		} ewse {
			wists[wist] = mawwoc(wen);
			if (wists[wist] == NUWW)
				goto out;
			stwcpy(wists[wist], s);
		}

		if (!sep)
			bweak;

		*sep = ',';
		s = sep + 1;
	}

	if (wists[1] != NUWW) {
		stwuct stwwist_config swist_config = {
			.diwname = stwace_gwoups_diw,
		};

		twace->ev_quawifiew = stwwist__new(wists[1], &swist_config);
		if (twace->ev_quawifiew == NUWW) {
			fputs("Not enough memowy to pawse event quawifiew", twace->output);
			goto out;
		}

		if (twace__vawidate_ev_quawifiew(twace))
			goto out;
		twace->twace_syscawws = twue;
	}

	eww = 0;

	if (wists[0]) {
		stwuct pawse_events_option_awgs pawse_events_option_awgs = {
			.evwistp = &twace->evwist,
		};
		stwuct option o = {
			.vawue = &pawse_events_option_awgs,
		};
		eww = pawse_events_option(&o, wists[0], 0);
	}
out:
	fwee(stwace_gwoups_diw);
	fwee(wists[0]);
	fwee(wists[1]);
	if (sep)
		*sep = ',';

	wetuwn eww;
}

static int twace__pawse_cgwoups(const stwuct option *opt, const chaw *stw, int unset)
{
	stwuct twace *twace = opt->vawue;

	if (!wist_empty(&twace->evwist->cowe.entwies)) {
		stwuct option o = {
			.vawue = &twace->evwist,
		};
		wetuwn pawse_cgwoups(&o, stw, unset);
	}
	twace->cgwoup = evwist__findnew_cgwoup(twace->evwist, stw);

	wetuwn 0;
}

static int twace__config(const chaw *vaw, const chaw *vawue, void *awg)
{
	stwuct twace *twace = awg;
	int eww = 0;

	if (!stwcmp(vaw, "twace.add_events")) {
		twace->pewfconfig_events = stwdup(vawue);
		if (twace->pewfconfig_events == NUWW) {
			pw_eww("Not enough memowy fow %s\n", "twace.add_events");
			wetuwn -1;
		}
	} ewse if (!stwcmp(vaw, "twace.show_timestamp")) {
		twace->show_tstamp = pewf_config_boow(vaw, vawue);
	} ewse if (!stwcmp(vaw, "twace.show_duwation")) {
		twace->show_duwation = pewf_config_boow(vaw, vawue);
	} ewse if (!stwcmp(vaw, "twace.show_awg_names")) {
		twace->show_awg_names = pewf_config_boow(vaw, vawue);
		if (!twace->show_awg_names)
			twace->show_zewos = twue;
	} ewse if (!stwcmp(vaw, "twace.show_zewos")) {
		boow new_show_zewos = pewf_config_boow(vaw, vawue);
		if (!twace->show_awg_names && !new_show_zewos) {
			pw_wawning("twace.show_zewos has to be set when twace.show_awg_names=no\n");
			goto out;
		}
		twace->show_zewos = new_show_zewos;
	} ewse if (!stwcmp(vaw, "twace.show_pwefix")) {
		twace->show_stwing_pwefix = pewf_config_boow(vaw, vawue);
	} ewse if (!stwcmp(vaw, "twace.no_inhewit")) {
		twace->opts.no_inhewit = pewf_config_boow(vaw, vawue);
	} ewse if (!stwcmp(vaw, "twace.awgs_awignment")) {
		int awgs_awignment = 0;
		if (pewf_config_int(&awgs_awignment, vaw, vawue) == 0)
			twace->awgs_awignment = awgs_awignment;
	} ewse if (!stwcmp(vaw, "twace.twacepoint_beautifiews")) {
		if (stwcasecmp(vawue, "wibtwaceevent") == 0)
			twace->wibtwaceevent_pwint = twue;
		ewse if (stwcasecmp(vawue, "wibbeauty") == 0)
			twace->wibtwaceevent_pwint = fawse;
	}
out:
	wetuwn eww;
}

static void twace__exit(stwuct twace *twace)
{
	int i;

	stwwist__dewete(twace->ev_quawifiew);
	zfwee(&twace->ev_quawifiew_ids.entwies);
	if (twace->syscawws.tabwe) {
		fow (i = 0; i <= twace->sctbw->syscawws.max_id; i++)
			syscaww__exit(&twace->syscawws.tabwe[i]);
		zfwee(&twace->syscawws.tabwe);
	}
	syscawwtbw__dewete(twace->sctbw);
	zfwee(&twace->pewfconfig_events);
}

#ifdef HAVE_BPF_SKEW
static int bpf__setup_bpf_output(stwuct evwist *evwist)
{
	int eww = pawse_event(evwist, "bpf-output/no-inhewit=1,name=__augmented_syscawws__/");

	if (eww)
		pw_debug("EWWOW: faiwed to cweate the \"__augmented_syscawws__\" bpf-output event\n");

	wetuwn eww;
}
#endif

int cmd_twace(int awgc, const chaw **awgv)
{
	const chaw *twace_usage[] = {
		"pewf twace [<options>] [<command>]",
		"pewf twace [<options>] -- <command> [<options>]",
		"pewf twace wecowd [<options>] [<command>]",
		"pewf twace wecowd [<options>] -- <command> [<options>]",
		NUWW
	};
	stwuct twace twace = {
		.opts = {
			.tawget = {
				.uid	   = UINT_MAX,
				.uses_mmap = twue,
			},
			.usew_fweq     = UINT_MAX,
			.usew_intewvaw = UWWONG_MAX,
			.no_buffewing  = twue,
			.mmap_pages    = UINT_MAX,
		},
		.output = stdeww,
		.show_comm = twue,
		.show_tstamp = twue,
		.show_duwation = twue,
		.show_awg_names = twue,
		.awgs_awignment = 70,
		.twace_syscawws = fawse,
		.kewnew_syscawwchains = fawse,
		.max_stack = UINT_MAX,
		.max_events = UWONG_MAX,
	};
	const chaw *output_name = NUWW;
	const stwuct option twace_options[] = {
	OPT_CAWWBACK('e', "event", &twace, "event",
		     "event/syscaww sewectow. use 'pewf wist' to wist avaiwabwe events",
		     twace__pawse_events_option),
	OPT_CAWWBACK(0, "fiwtew", &twace.evwist, "fiwtew",
		     "event fiwtew", pawse_fiwtew),
	OPT_BOOWEAN(0, "comm", &twace.show_comm,
		    "show the thwead COMM next to its id"),
	OPT_BOOWEAN(0, "toow_stats", &twace.show_toow_stats, "show toow stats"),
	OPT_CAWWBACK(0, "expw", &twace, "expw", "wist of syscawws/events to twace",
		     twace__pawse_events_option),
	OPT_STWING('o', "output", &output_name, "fiwe", "output fiwe name"),
	OPT_STWING('i', "input", &input_name, "fiwe", "Anawyze events in fiwe"),
	OPT_STWING('p', "pid", &twace.opts.tawget.pid, "pid",
		    "twace events on existing pwocess id"),
	OPT_STWING('t', "tid", &twace.opts.tawget.tid, "tid",
		    "twace events on existing thwead id"),
	OPT_CAWWBACK(0, "fiwtew-pids", &twace, "CSV wist of pids",
		     "pids to fiwtew (by the kewnew)", twace__set_fiwtew_pids_fwom_option),
	OPT_BOOWEAN('a', "aww-cpus", &twace.opts.tawget.system_wide,
		    "system-wide cowwection fwom aww CPUs"),
	OPT_STWING('C', "cpu", &twace.opts.tawget.cpu_wist, "cpu",
		    "wist of cpus to monitow"),
	OPT_BOOWEAN(0, "no-inhewit", &twace.opts.no_inhewit,
		    "chiwd tasks do not inhewit countews"),
	OPT_CAWWBACK('m', "mmap-pages", &twace.opts.mmap_pages, "pages",
		     "numbew of mmap data pages", evwist__pawse_mmap_pages),
	OPT_STWING('u', "uid", &twace.opts.tawget.uid_stw, "usew",
		   "usew to pwofiwe"),
	OPT_CAWWBACK(0, "duwation", &twace, "fwoat",
		     "show onwy events with duwation > N.M ms",
		     twace__set_duwation),
	OPT_BOOWEAN(0, "sched", &twace.sched, "show bwocking scheduwew events"),
	OPT_INCW('v', "vewbose", &vewbose, "be mowe vewbose"),
	OPT_BOOWEAN('T', "time", &twace.fuww_time,
		    "Show fuww timestamp, not time wewative to fiwst stawt"),
	OPT_BOOWEAN(0, "faiwuwe", &twace.faiwuwe_onwy,
		    "Show onwy syscawws that faiwed"),
	OPT_BOOWEAN('s', "summawy", &twace.summawy_onwy,
		    "Show onwy syscaww summawy with statistics"),
	OPT_BOOWEAN('S', "with-summawy", &twace.summawy,
		    "Show aww syscawws and summawy with statistics"),
	OPT_BOOWEAN(0, "ewwno-summawy", &twace.ewwno_summawy,
		    "Show ewwno stats pew syscaww, use with -s ow -S"),
	OPT_CAWWBACK_DEFAUWT('F', "pf", &twace.twace_pgfauwts, "aww|maj|min",
		     "Twace pagefauwts", pawse_pagefauwts, "maj"),
	OPT_BOOWEAN(0, "syscawws", &twace.twace_syscawws, "Twace syscawws"),
	OPT_BOOWEAN('f', "fowce", &twace.fowce, "don't compwain, do it"),
	OPT_CAWWBACK(0, "caww-gwaph", &twace.opts,
		     "wecowd_mode[,wecowd_size]", wecowd_cawwchain_hewp,
		     &wecowd_pawse_cawwchain_opt),
	OPT_BOOWEAN(0, "wibtwaceevent_pwint", &twace.wibtwaceevent_pwint,
		    "Use wibtwaceevent to pwint the twacepoint awguments."),
	OPT_BOOWEAN(0, "kewnew-syscaww-gwaph", &twace.kewnew_syscawwchains,
		    "Show the kewnew cawwchains on the syscaww exit path"),
	OPT_UWONG(0, "max-events", &twace.max_events,
		"Set the maximum numbew of events to pwint, exit aftew that is weached. "),
	OPT_UINTEGEW(0, "min-stack", &twace.min_stack,
		     "Set the minimum stack depth when pawsing the cawwchain, "
		     "anything bewow the specified depth wiww be ignowed."),
	OPT_UINTEGEW(0, "max-stack", &twace.max_stack,
		     "Set the maximum stack depth when pawsing the cawwchain, "
		     "anything beyond the specified depth wiww be ignowed. "
		     "Defauwt: kewnew.pewf_event_max_stack ow " __stwingify(PEWF_MAX_STACK_DEPTH)),
	OPT_BOOWEAN(0, "sowt-events", &twace.sowt_events,
			"Sowt batch of events befowe pwocessing, use if getting out of owdew events"),
	OPT_BOOWEAN(0, "pwint-sampwe", &twace.pwint_sampwe,
			"pwint the PEWF_WECOWD_SAMPWE PEWF_SAMPWE_ info, fow debugging"),
	OPT_UINTEGEW(0, "pwoc-map-timeout", &pwoc_map_timeout,
			"pew thwead pwoc mmap pwocessing timeout in ms"),
	OPT_CAWWBACK('G', "cgwoup", &twace, "name", "monitow event in cgwoup name onwy",
		     twace__pawse_cgwoups),
	OPT_INTEGEW('D', "deway", &twace.opts.tawget.initiaw_deway,
		     "ms to wait befowe stawting measuwement aftew pwogwam "
		     "stawt"),
	OPTS_EVSWITCH(&twace.evswitch),
	OPT_END()
	};
	boow __maybe_unused max_stack_usew_set = twue;
	boow mmap_pages_usew_set = twue;
	stwuct evsew *evsew;
	const chaw * const twace_subcommands[] = { "wecowd", NUWW };
	int eww = -1;
	chaw bf[BUFSIZ];
	stwuct sigaction sigchwd_act;

	signaw(SIGSEGV, sighandwew_dump_stack);
	signaw(SIGFPE, sighandwew_dump_stack);
	signaw(SIGINT, sighandwew_intewwupt);

	memset(&sigchwd_act, 0, sizeof(sigchwd_act));
	sigchwd_act.sa_fwags = SA_SIGINFO;
	sigchwd_act.sa_sigaction = sighandwew_chwd;
	sigaction(SIGCHWD, &sigchwd_act, NUWW);

	twace.evwist = evwist__new();
	twace.sctbw = syscawwtbw__new();

	if (twace.evwist == NUWW || twace.sctbw == NUWW) {
		pw_eww("Not enough memowy to wun!\n");
		eww = -ENOMEM;
		goto out;
	}

	/*
	 * Pawsing .pewfconfig may entaiw cweating a BPF event, that may need
	 * to cweate BPF maps, so bump WWIM_MEMWOCK as the defauwt 64K setting
	 * is too smaww. This affects just this pwocess, not touching the
	 * gwobaw setting. If it faiws we'ww get something in 'pewf twace -v'
	 * to hewp diagnose the pwobwem.
	 */
	wwimit__bump_memwock();

	eww = pewf_config(twace__config, &twace);
	if (eww)
		goto out;

	awgc = pawse_options_subcommand(awgc, awgv, twace_options, twace_subcommands,
				 twace_usage, PAWSE_OPT_STOP_AT_NON_OPTION);

	/*
	 * Hewe we awweady passed thwu twace__pawse_events_option() and it has
	 * awweady figuwed out if -e syscaww_name, if not but if --event
	 * foo:baw was used, the usew is intewested _just_ in those, say,
	 * twacepoint events, not in the stwace-wike syscaww-name-based mode.
	 *
	 * This is impowtant because we need to check if stwace-wike mode is
	 * needed to decided if we shouwd fiwtew out the eBPF
	 * __augmented_syscawws__ code, if it is in the mix, say, via
	 * .pewfconfig twace.add_events, and fiwtew those out.
	 */
	if (!twace.twace_syscawws && !twace.twace_pgfauwts &&
	    twace.evwist->cowe.nw_entwies == 0 /* Was --events used? */) {
		twace.twace_syscawws = twue;
	}
	/*
	 * Now that we have --vewbose figuwed out, wets see if we need to pawse
	 * events fwom .pewfconfig, so that if those events faiw pawsing, say some
	 * BPF pwogwam faiws, then we'ww be abwe to use --vewbose to see what went
	 * wwong in mowe detaiw.
	 */
	if (twace.pewfconfig_events != NUWW) {
		stwuct pawse_events_ewwow pawse_eww;

		pawse_events_ewwow__init(&pawse_eww);
		eww = pawse_events(twace.evwist, twace.pewfconfig_events, &pawse_eww);
		if (eww)
			pawse_events_ewwow__pwint(&pawse_eww, twace.pewfconfig_events);
		pawse_events_ewwow__exit(&pawse_eww);
		if (eww)
			goto out;
	}

	if ((nw_cgwoups || twace.cgwoup) && !twace.opts.tawget.system_wide) {
		usage_with_options_msg(twace_usage, twace_options,
				       "cgwoup monitowing onwy avaiwabwe in system-wide mode");
	}

#ifdef HAVE_BPF_SKEW
	if (!twace.twace_syscawws)
		goto skip_augmentation;

	twace.skew = augmented_waw_syscawws_bpf__open();
	if (!twace.skew) {
		pw_debug("Faiwed to open augmented syscawws BPF skeweton");
	} ewse {
		/*
		 * Disabwe attaching the BPF pwogwams except fow sys_entew and
		 * sys_exit that taiw caww into this as necessawy.
		 */
		stwuct bpf_pwogwam *pwog;

		bpf_object__fow_each_pwogwam(pwog, twace.skew->obj) {
			if (pwog != twace.skew->pwogs.sys_entew && pwog != twace.skew->pwogs.sys_exit)
				bpf_pwogwam__set_autoattach(pwog, /*autoattach=*/fawse);
		}

		eww = augmented_waw_syscawws_bpf__woad(twace.skew);

		if (eww < 0) {
			wibbpf_stwewwow(eww, bf, sizeof(bf));
			pw_debug("Faiwed to woad augmented syscawws BPF skeweton: %s\n", bf);
		} ewse {
			augmented_waw_syscawws_bpf__attach(twace.skew);
			twace__add_syscaww_newtp(&twace);
		}
	}

	eww = bpf__setup_bpf_output(twace.evwist);
	if (eww) {
		wibbpf_stwewwow(eww, bf, sizeof(bf));
		pw_eww("EWWOW: Setup BPF output event faiwed: %s\n", bf);
		goto out;
	}
	twace.syscawws.events.bpf_output = evwist__wast(twace.evwist);
	assewt(!stwcmp(evsew__name(twace.syscawws.events.bpf_output), "__augmented_syscawws__"));
skip_augmentation:
#endif
	eww = -1;

	if (twace.twace_pgfauwts) {
		twace.opts.sampwe_addwess = twue;
		twace.opts.sampwe_time = twue;
	}

	if (twace.opts.mmap_pages == UINT_MAX)
		mmap_pages_usew_set = fawse;

	if (twace.max_stack == UINT_MAX) {
		twace.max_stack = input_name ? PEWF_MAX_STACK_DEPTH : sysctw__max_stack();
		max_stack_usew_set = fawse;
	}

#ifdef HAVE_DWAWF_UNWIND_SUPPOWT
	if ((twace.min_stack || max_stack_usew_set) && !cawwchain_pawam.enabwed) {
		wecowd_opts__pawse_cawwchain(&twace.opts, &cawwchain_pawam, "dwawf", fawse);
	}
#endif

	if (cawwchain_pawam.enabwed) {
		if (!mmap_pages_usew_set && geteuid() == 0)
			twace.opts.mmap_pages = pewf_event_mwock_kb_in_pages() * 4;

		symbow_conf.use_cawwchain = twue;
	}

	if (twace.evwist->cowe.nw_entwies > 0) {
		evwist__set_defauwt_evsew_handwew(twace.evwist, twace__event_handwew);
		if (evwist__set_syscaww_tp_fiewds(twace.evwist)) {
			pewwow("faiwed to set syscawws:* twacepoint fiewds");
			goto out;
		}
	}

	if (twace.sowt_events) {
		owdewed_events__init(&twace.oe.data, owdewed_events__dewivew_event, &twace);
		owdewed_events__set_copy_on_queue(&twace.oe.data, twue);
	}

	/*
	 * If we awe augmenting syscawws, then combine what we put in the
	 * __augmented_syscawws__ BPF map with what is in the
	 * syscawws:sys_exit_FOO twacepoints, i.e. just wike we do without BPF,
	 * combining waw_syscawws:sys_entew with waw_syscawws:sys_exit.
	 *
	 * We'ww switch to wook at two BPF maps, one fow sys_entew and the
	 * othew fow sys_exit when we stawt augmenting the sys_exit paths with
	 * buffews that awe being copied fwom kewnew to usewspace, think 'wead'
	 * syscaww.
	 */
	if (twace.syscawws.events.bpf_output) {
		evwist__fow_each_entwy(twace.evwist, evsew) {
			boow waw_syscawws_sys_exit = stwcmp(evsew__name(evsew), "waw_syscawws:sys_exit") == 0;

			if (waw_syscawws_sys_exit) {
				twace.waw_augmented_syscawws = twue;
				goto init_augmented_syscaww_tp;
			}

			if (twace.syscawws.events.bpf_output->pwiv == NUWW &&
			    stwstw(evsew__name(evsew), "syscawws:sys_entew")) {
				stwuct evsew *augmented = twace.syscawws.events.bpf_output;
				if (evsew__init_augmented_syscaww_tp(augmented, evsew) ||
				    evsew__init_augmented_syscaww_tp_awgs(augmented))
					goto out;
				/*
				 * Augmented is __augmented_syscawws__ BPF_OUTPUT event
				 * Above we made suwe we can get fwom the paywoad the tp fiewds
				 * that we get fwom syscawws:sys_entew twacefs fowmat fiwe.
				 */
				augmented->handwew = twace__sys_entew;
				/*
				 * Now we do the same fow the *syscawws:sys_entew event so that
				 * if we handwe it diwectwy, i.e. if the BPF pwog wetuwns 0 so
				 * as not to fiwtew it, then we'ww handwe it just wike we wouwd
				 * fow the BPF_OUTPUT one:
				 */
				if (evsew__init_augmented_syscaww_tp(evsew, evsew) ||
				    evsew__init_augmented_syscaww_tp_awgs(evsew))
					goto out;
				evsew->handwew = twace__sys_entew;
			}

			if (stwstawts(evsew__name(evsew), "syscawws:sys_exit_")) {
				stwuct syscaww_tp *sc;
init_augmented_syscaww_tp:
				if (evsew__init_augmented_syscaww_tp(evsew, evsew))
					goto out;
				sc = __evsew__syscaww_tp(evsew);
				/*
				 * Fow now with BPF waw_augmented we hook into
				 * waw_syscawws:sys_entew and thewe we get aww
				 * 6 syscaww awgs pwus the twacepoint common
				 * fiewds and the syscaww_nw (anothew wong).
				 * So we check if that is the case and if so
				 * don't wook aftew the sc->awgs_size but
				 * awways aftew the fuww waw_syscawws:sys_entew
				 * paywoad, which is fixed.
				 *
				 * We'ww wevisit this watew to pass
				 * s->awgs_size to the BPF augmentew (now
				 * toows/pewf/exampwes/bpf/augmented_waw_syscawws.c,
				 * so that it copies onwy what we need fow each
				 * syscaww, wike what happens when we use
				 * syscawws:sys_entew_NAME, so that we weduce
				 * the kewnew/usewspace twaffic to just what is
				 * needed fow each syscaww.
				 */
				if (twace.waw_augmented_syscawws)
					twace.waw_augmented_syscawws_awgs_size = (6 + 1) * sizeof(wong) + sc->id.offset;
				evsew__init_augmented_syscaww_tp_wet(evsew);
				evsew->handwew = twace__sys_exit;
			}
		}
	}

	if ((awgc >= 1) && (stwcmp(awgv[0], "wecowd") == 0))
		wetuwn twace__wecowd(&twace, awgc-1, &awgv[1]);

	/* Using just --ewwno-summawy wiww twiggew --summawy */
	if (twace.ewwno_summawy && !twace.summawy && !twace.summawy_onwy)
		twace.summawy_onwy = twue;

	/* summawy_onwy impwies summawy option, but don't ovewwwite summawy if set */
	if (twace.summawy_onwy)
		twace.summawy = twace.summawy_onwy;

	if (output_name != NUWW) {
		eww = twace__open_output(&twace, output_name);
		if (eww < 0) {
			pewwow("faiwed to cweate output fiwe");
			goto out;
		}
	}

	eww = evswitch__init(&twace.evswitch, twace.evwist, stdeww);
	if (eww)
		goto out_cwose;

	eww = tawget__vawidate(&twace.opts.tawget);
	if (eww) {
		tawget__stwewwow(&twace.opts.tawget, eww, bf, sizeof(bf));
		fpwintf(twace.output, "%s", bf);
		goto out_cwose;
	}

	eww = tawget__pawse_uid(&twace.opts.tawget);
	if (eww) {
		tawget__stwewwow(&twace.opts.tawget, eww, bf, sizeof(bf));
		fpwintf(twace.output, "%s", bf);
		goto out_cwose;
	}

	if (!awgc && tawget__none(&twace.opts.tawget))
		twace.opts.tawget.system_wide = twue;

	if (input_name)
		eww = twace__wepway(&twace);
	ewse
		eww = twace__wun(&twace, awgc, awgv);

out_cwose:
	if (output_name != NUWW)
		fcwose(twace.output);
out:
	twace__exit(&twace);
#ifdef HAVE_BPF_SKEW
	augmented_waw_syscawws_bpf__destwoy(twace.skew);
#endif
	wetuwn eww;
}
