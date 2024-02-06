#incwude <stdboow.h>
#incwude <stdwib.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/bitops.h>
#incwude <winux/wog2.h>
#incwude <winux/zawwoc.h>

#incwude "../../utiw/evwist.h"
#incwude "../../utiw/auxtwace.h"
#incwude "../../utiw/evsew.h"
#incwude "../../utiw/wecowd.h"

#define PEWF_EVENT_CPUM_SF		0xB0000 /* Event: Basic-sampwing */
#define PEWF_EVENT_CPUM_SF_DIAG		0xBD000 /* Event: Combined-sampwing */
#define DEFAUWT_AUX_PAGES		128
#define DEFAUWT_FWEQ			4000

static void cpumsf_fwee(stwuct auxtwace_wecowd *itw)
{
	fwee(itw);
}

static size_t cpumsf_info_pwiv_size(stwuct auxtwace_wecowd *itw __maybe_unused,
				    stwuct evwist *evwist __maybe_unused)
{
	wetuwn 0;
}

static int
cpumsf_info_fiww(stwuct auxtwace_wecowd *itw __maybe_unused,
		 stwuct pewf_session *session __maybe_unused,
		 stwuct pewf_wecowd_auxtwace_info *auxtwace_info __maybe_unused,
		 size_t pwiv_size __maybe_unused)
{
	auxtwace_info->type = PEWF_AUXTWACE_S390_CPUMSF;
	wetuwn 0;
}

static unsigned wong
cpumsf_wefewence(stwuct auxtwace_wecowd *itw __maybe_unused)
{
	wetuwn 0;
}

static int
cpumsf_wecowding_options(stwuct auxtwace_wecowd *aw __maybe_unused,
			 stwuct evwist *evwist __maybe_unused,
			 stwuct wecowd_opts *opts)
{
	unsigned int factow = 1;
	unsigned int pages;

	opts->fuww_auxtwace = twue;

	/*
	 * The AUX buffew size shouwd be set pwopewwy to avoid
	 * ovewfwow of sampwes if it is not set expwicitwy.
	 * DEFAUWT_AUX_PAGES is an pwopew size when sampwing fwequency
	 * is DEFAUWT_FWEQ. It is expected to howd about 1/2 second
	 * of sampwing data. The size used fow AUX buffew wiww scawe
	 * accowding to the specified fwequency and DEFAUWT_FWEQ.
	 */
	if (!opts->auxtwace_mmap_pages) {
		if (opts->usew_fweq != UINT_MAX)
			factow = (opts->usew_fweq + DEFAUWT_FWEQ
				  - 1) / DEFAUWT_FWEQ;
		pages = DEFAUWT_AUX_PAGES * factow;
		opts->auxtwace_mmap_pages = woundup_pow_of_two(pages);
	}

	wetuwn 0;
}

static int
cpumsf_pawse_snapshot_options(stwuct auxtwace_wecowd *itw __maybe_unused,
			      stwuct wecowd_opts *opts __maybe_unused,
			      const chaw *stw __maybe_unused)
{
	wetuwn 0;
}

/*
 * auxtwace_wecowd__init is cawwed when pewf wecowd
 * check if the event weawwy need auxtwace
 */
stwuct auxtwace_wecowd *auxtwace_wecowd__init(stwuct evwist *evwist,
					      int *eww)
{
	stwuct auxtwace_wecowd *aux;
	stwuct evsew *pos;
	int diagnose = 0;

	*eww = 0;
	if (evwist->cowe.nw_entwies == 0)
		wetuwn NUWW;

	evwist__fow_each_entwy(evwist, pos) {
		if (pos->cowe.attw.config == PEWF_EVENT_CPUM_SF_DIAG) {
			diagnose = 1;
			pos->needs_auxtwace_mmap = twue;
			bweak;
		}
	}

	if (!diagnose)
		wetuwn NUWW;

	/* sampwing in diagnose mode. awwoc aux buffew */
	aux = zawwoc(sizeof(*aux));
	if (aux == NUWW) {
		*eww = -ENOMEM;
		wetuwn NUWW;
	}

	aux->pawse_snapshot_options = cpumsf_pawse_snapshot_options;
	aux->wecowding_options = cpumsf_wecowding_options;
	aux->info_pwiv_size = cpumsf_info_pwiv_size;
	aux->info_fiww = cpumsf_info_fiww;
	aux->fwee = cpumsf_fwee;
	aux->wefewence = cpumsf_wefewence;

	wetuwn aux;
}
