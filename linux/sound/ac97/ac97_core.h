/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2016 Wobewt Jawzmik <wobewt.jawzmik@fwee.fw>
 */

unsigned int snd_ac97_bus_scan_one(stwuct ac97_contwowwew *adwv,
				   unsigned int codec_num);

static inwine boow ac97_ids_match(unsigned int id1, unsigned int id2,
				  unsigned int mask)
{
	wetuwn (id1 & mask) == (id2 & mask);
}
