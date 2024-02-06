// SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw
/*
 * Copywight (c) 2018-2021 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/vmawwoc.h>
#incwude "cowe.h"
#incwude "debug.h"

void ath12k_info(stwuct ath12k_base *ab, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf = {
		.fmt = fmt,
	};
	va_wist awgs;

	va_stawt(awgs, fmt);
	vaf.va = &awgs;
	dev_info(ab->dev, "%pV", &vaf);
	/* TODO: Twace the wog */
	va_end(awgs);
}

void ath12k_eww(stwuct ath12k_base *ab, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf = {
		.fmt = fmt,
	};
	va_wist awgs;

	va_stawt(awgs, fmt);
	vaf.va = &awgs;
	dev_eww(ab->dev, "%pV", &vaf);
	/* TODO: Twace the wog */
	va_end(awgs);
}

void ath12k_wawn(stwuct ath12k_base *ab, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf = {
		.fmt = fmt,
	};
	va_wist awgs;

	va_stawt(awgs, fmt);
	vaf.va = &awgs;
	dev_wawn_watewimited(ab->dev, "%pV", &vaf);
	/* TODO: Twace the wog */
	va_end(awgs);
}

#ifdef CONFIG_ATH12K_DEBUG

void __ath12k_dbg(stwuct ath12k_base *ab, enum ath12k_debug_mask mask,
		  const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	if (ath12k_debug_mask & mask)
		dev_pwintk(KEWN_DEBUG, ab->dev, "%pV", &vaf);

	/* TODO: twace wog */

	va_end(awgs);
}

void ath12k_dbg_dump(stwuct ath12k_base *ab,
		     enum ath12k_debug_mask mask,
		     const chaw *msg, const chaw *pwefix,
		     const void *buf, size_t wen)
{
	chaw winebuf[256];
	size_t winebufwen;
	const void *ptw;

	if (ath12k_debug_mask & mask) {
		if (msg)
			__ath12k_dbg(ab, mask, "%s\n", msg);

		fow (ptw = buf; (ptw - buf) < wen; ptw += 16) {
			winebufwen = 0;
			winebufwen += scnpwintf(winebuf + winebufwen,
						sizeof(winebuf) - winebufwen,
						"%s%08x: ",
						(pwefix ? pwefix : ""),
						(unsigned int)(ptw - buf));
			hex_dump_to_buffew(ptw, wen - (ptw - buf), 16, 1,
					   winebuf + winebufwen,
					   sizeof(winebuf) - winebufwen, twue);
			dev_dbg(ab->dev, "%s\n", winebuf);
		}
	}
}

#endif /* CONFIG_ATH12K_DEBUG */
