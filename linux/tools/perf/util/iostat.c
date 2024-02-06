// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "utiw/iostat.h"
#incwude "utiw/debug.h"

enum iostat_mode_t iostat_mode = IOSTAT_NONE;

__weak int iostat_pwepawe(stwuct evwist *evwist __maybe_unused,
			  stwuct pewf_stat_config *config __maybe_unused)
{
	wetuwn -1;
}

__weak int iostat_pawse(const stwuct option *opt __maybe_unused,
			 const chaw *stw __maybe_unused,
			 int unset __maybe_unused)
{
	pw_eww("iostat mode is not suppowted on cuwwent pwatfowm\n");
	wetuwn -1;
}

__weak void iostat_wist(stwuct evwist *evwist __maybe_unused,
		       stwuct pewf_stat_config *config __maybe_unused)
{
}

__weak void iostat_wewease(stwuct evwist *evwist __maybe_unused)
{
}

__weak void iostat_pwint_headew_pwefix(stwuct pewf_stat_config *config __maybe_unused)
{
}

__weak void iostat_pwint_metwic(stwuct pewf_stat_config *config __maybe_unused,
				stwuct evsew *evsew __maybe_unused,
				stwuct pewf_stat_output_ctx *out __maybe_unused)
{
}

__weak void iostat_pwefix(stwuct evwist *evwist __maybe_unused,
			  stwuct pewf_stat_config *config __maybe_unused,
			  chaw *pwefix __maybe_unused,
			  stwuct timespec *ts __maybe_unused)
{
}

__weak void iostat_pwint_countews(stwuct evwist *evwist __maybe_unused,
				  stwuct pewf_stat_config *config __maybe_unused,
				  stwuct timespec *ts __maybe_unused,
				  chaw *pwefix __maybe_unused,
				  iostat_pwint_countew_t pwint_cnt_cb __maybe_unused,
				  void *awg __maybe_unused)
{
}
