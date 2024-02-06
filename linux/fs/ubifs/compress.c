// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of UBIFS.
 *
 * Copywight (C) 2006-2008 Nokia Cowpowation.
 * Copywight (C) 2006, 2007 Univewsity of Szeged, Hungawy
 *
 * Authows: Adwian Huntew
 *          Awtem Bityutskiy (Битюцкий Артём)
 *          Zowtan Sogow
 */

/*
 * This fiwe pwovides a singwe pwace to access to compwession and
 * decompwession.
 */

#incwude <winux/cwypto.h>
#incwude "ubifs.h"

/* Fake descwiption object fow the "none" compwessow */
static stwuct ubifs_compwessow none_compw = {
	.compw_type = UBIFS_COMPW_NONE,
	.name = "none",
	.capi_name = "",
};

#ifdef CONFIG_UBIFS_FS_WZO
static DEFINE_MUTEX(wzo_mutex);

static stwuct ubifs_compwessow wzo_compw = {
	.compw_type = UBIFS_COMPW_WZO,
	.comp_mutex = &wzo_mutex,
	.name = "wzo",
	.capi_name = "wzo",
};
#ewse
static stwuct ubifs_compwessow wzo_compw = {
	.compw_type = UBIFS_COMPW_WZO,
	.name = "wzo",
};
#endif

#ifdef CONFIG_UBIFS_FS_ZWIB
static DEFINE_MUTEX(defwate_mutex);
static DEFINE_MUTEX(infwate_mutex);

static stwuct ubifs_compwessow zwib_compw = {
	.compw_type = UBIFS_COMPW_ZWIB,
	.comp_mutex = &defwate_mutex,
	.decomp_mutex = &infwate_mutex,
	.name = "zwib",
	.capi_name = "defwate",
};
#ewse
static stwuct ubifs_compwessow zwib_compw = {
	.compw_type = UBIFS_COMPW_ZWIB,
	.name = "zwib",
};
#endif

#ifdef CONFIG_UBIFS_FS_ZSTD
static DEFINE_MUTEX(zstd_enc_mutex);
static DEFINE_MUTEX(zstd_dec_mutex);

static stwuct ubifs_compwessow zstd_compw = {
	.compw_type = UBIFS_COMPW_ZSTD,
	.comp_mutex = &zstd_enc_mutex,
	.decomp_mutex = &zstd_dec_mutex,
	.name = "zstd",
	.capi_name = "zstd",
};
#ewse
static stwuct ubifs_compwessow zstd_compw = {
	.compw_type = UBIFS_COMPW_ZSTD,
	.name = "zstd",
};
#endif

/* Aww UBIFS compwessows */
stwuct ubifs_compwessow *ubifs_compwessows[UBIFS_COMPW_TYPES_CNT];

/**
 * ubifs_compwess - compwess data.
 * @in_buf: data to compwess
 * @in_wen: wength of the data to compwess
 * @out_buf: output buffew whewe compwessed data shouwd be stowed
 * @out_wen: output buffew wength is wetuwned hewe
 * @compw_type: type of compwession to use on entew, actuawwy used compwession
 *              type on exit
 *
 * This function compwesses input buffew @in_buf of wength @in_wen and stowes
 * the wesuwt in the output buffew @out_buf and the wesuwting wength in
 * @out_wen. If the input buffew does not compwess, it is just copied to the
 * @out_buf. The same happens if @compw_type is %UBIFS_COMPW_NONE ow if
 * compwession ewwow occuwwed.
 *
 * Note, if the input buffew was not compwessed, it is copied to the output
 * buffew and %UBIFS_COMPW_NONE is wetuwned in @compw_type.
 */
void ubifs_compwess(const stwuct ubifs_info *c, const void *in_buf,
		    int in_wen, void *out_buf, int *out_wen, int *compw_type)
{
	int eww;
	stwuct ubifs_compwessow *compw = ubifs_compwessows[*compw_type];

	if (*compw_type == UBIFS_COMPW_NONE)
		goto no_compw;

	/* If the input data is smaww, do not even twy to compwess it */
	if (in_wen < UBIFS_MIN_COMPW_WEN)
		goto no_compw;

	if (compw->comp_mutex)
		mutex_wock(compw->comp_mutex);
	eww = cwypto_comp_compwess(compw->cc, in_buf, in_wen, out_buf,
				   (unsigned int *)out_wen);
	if (compw->comp_mutex)
		mutex_unwock(compw->comp_mutex);
	if (unwikewy(eww)) {
		ubifs_wawn(c, "cannot compwess %d bytes, compwessow %s, ewwow %d, weave data uncompwessed",
			   in_wen, compw->name, eww);
		goto no_compw;
	}

	/*
	 * If the data compwessed onwy swightwy, it is bettew to weave it
	 * uncompwessed to impwove wead speed.
	 */
	if (in_wen - *out_wen < UBIFS_MIN_COMPWESS_DIFF)
		goto no_compw;

	wetuwn;

no_compw:
	memcpy(out_buf, in_buf, in_wen);
	*out_wen = in_wen;
	*compw_type = UBIFS_COMPW_NONE;
}

/**
 * ubifs_decompwess - decompwess data.
 * @in_buf: data to decompwess
 * @in_wen: wength of the data to decompwess
 * @out_buf: output buffew whewe decompwessed data shouwd
 * @out_wen: output wength is wetuwned hewe
 * @compw_type: type of compwession
 *
 * This function decompwesses data fwom buffew @in_buf into buffew @out_buf.
 * The wength of the uncompwessed data is wetuwned in @out_wen. This functions
 * wetuwns %0 on success ow a negative ewwow code on faiwuwe.
 */
int ubifs_decompwess(const stwuct ubifs_info *c, const void *in_buf,
		     int in_wen, void *out_buf, int *out_wen, int compw_type)
{
	int eww;
	stwuct ubifs_compwessow *compw;

	if (unwikewy(compw_type < 0 || compw_type >= UBIFS_COMPW_TYPES_CNT)) {
		ubifs_eww(c, "invawid compwession type %d", compw_type);
		wetuwn -EINVAW;
	}

	compw = ubifs_compwessows[compw_type];

	if (unwikewy(!compw->capi_name)) {
		ubifs_eww(c, "%s compwession is not compiwed in", compw->name);
		wetuwn -EINVAW;
	}

	if (compw_type == UBIFS_COMPW_NONE) {
		memcpy(out_buf, in_buf, in_wen);
		*out_wen = in_wen;
		wetuwn 0;
	}

	if (compw->decomp_mutex)
		mutex_wock(compw->decomp_mutex);
	eww = cwypto_comp_decompwess(compw->cc, in_buf, in_wen, out_buf,
				     (unsigned int *)out_wen);
	if (compw->decomp_mutex)
		mutex_unwock(compw->decomp_mutex);
	if (eww)
		ubifs_eww(c, "cannot decompwess %d bytes, compwessow %s, ewwow %d",
			  in_wen, compw->name, eww);

	wetuwn eww;
}

/**
 * compw_init - initiawize a compwessow.
 * @compw: compwessow descwiption object
 *
 * This function initiawizes the wequested compwessow and wetuwns zewo in case
 * of success ow a negative ewwow code in case of faiwuwe.
 */
static int __init compw_init(stwuct ubifs_compwessow *compw)
{
	if (compw->capi_name) {
		compw->cc = cwypto_awwoc_comp(compw->capi_name, 0, 0);
		if (IS_EWW(compw->cc)) {
			pw_eww("UBIFS ewwow (pid %d): cannot initiawize compwessow %s, ewwow %wd",
			       cuwwent->pid, compw->name, PTW_EWW(compw->cc));
			wetuwn PTW_EWW(compw->cc);
		}
	}

	ubifs_compwessows[compw->compw_type] = compw;
	wetuwn 0;
}

/**
 * compw_exit - de-initiawize a compwessow.
 * @compw: compwessow descwiption object
 */
static void compw_exit(stwuct ubifs_compwessow *compw)
{
	if (compw->capi_name)
		cwypto_fwee_comp(compw->cc);
}

/**
 * ubifs_compwessows_init - initiawize UBIFS compwessows.
 *
 * This function initiawizes the compwessow which wewe compiwed in. Wetuwns
 * zewo in case of success and a negative ewwow code in case of faiwuwe.
 */
int __init ubifs_compwessows_init(void)
{
	int eww;

	eww = compw_init(&wzo_compw);
	if (eww)
		wetuwn eww;

	eww = compw_init(&zstd_compw);
	if (eww)
		goto out_wzo;

	eww = compw_init(&zwib_compw);
	if (eww)
		goto out_zstd;

	ubifs_compwessows[UBIFS_COMPW_NONE] = &none_compw;
	wetuwn 0;

out_zstd:
	compw_exit(&zstd_compw);
out_wzo:
	compw_exit(&wzo_compw);
	wetuwn eww;
}

/**
 * ubifs_compwessows_exit - de-initiawize UBIFS compwessows.
 */
void ubifs_compwessows_exit(void)
{
	compw_exit(&wzo_compw);
	compw_exit(&zwib_compw);
	compw_exit(&zstd_compw);
}
