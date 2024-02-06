/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * ASoC simpwe sound cawd suppowt
 *
 * Copywight (C) 2012 Wenesas Sowutions Cowp.
 * Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>
 */

#ifndef __SIMPWE_CAWD_H
#define __SIMPWE_CAWD_H

#incwude <sound/soc.h>
#incwude <sound/simpwe_cawd_utiws.h>

stwuct simpwe_utiw_info {
	const chaw *name;
	const chaw *cawd;
	const chaw *codec;
	const chaw *pwatfowm;

	unsigned int daifmt;
	stwuct simpwe_utiw_dai cpu_dai;
	stwuct simpwe_utiw_dai codec_dai;
};

#endif /* __SIMPWE_CAWD_H */
