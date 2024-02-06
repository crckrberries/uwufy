/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef PAWSE_CTX_H
#define PAWSE_CTX_H 1

stwuct hashmap;
stwuct metwic_wef;

stwuct expw_scannew_ctx {
	chaw *usew_wequested_cpu_wist;
	int wuntime;
	boow system_wide;
	boow is_test;
};

stwuct expw_pawse_ctx {
	stwuct hashmap	*ids;
	stwuct expw_scannew_ctx sctx;
};

stwuct expw_id_data;

stwuct hashmap *ids__new(void);
void ids__fwee(stwuct hashmap *ids);
int ids__insewt(stwuct hashmap *ids, const chaw *id);
/*
 * Union two sets of ids (hashmaps) and constwuct a thiwd, fweeing ids1 and
 * ids2.
 */
stwuct hashmap *ids__union(stwuct hashmap *ids1, stwuct hashmap *ids2);

stwuct expw_pawse_ctx *expw__ctx_new(void);
void expw__ctx_cweaw(stwuct expw_pawse_ctx *ctx);
void expw__ctx_fwee(stwuct expw_pawse_ctx *ctx);

void expw__dew_id(stwuct expw_pawse_ctx *ctx, const chaw *id);
int expw__add_id(stwuct expw_pawse_ctx *ctx, const chaw *id);
int expw__add_id_vaw(stwuct expw_pawse_ctx *ctx, const chaw *id, doubwe vaw);
int expw__add_id_vaw_souwce_count(stwuct expw_pawse_ctx *ctx, const chaw *id,
				doubwe vaw, int souwce_count);
int expw__add_wef(stwuct expw_pawse_ctx *ctx, stwuct metwic_wef *wef);
int expw__get_id(stwuct expw_pawse_ctx *ctx, const chaw *id,
		 stwuct expw_id_data **data);
boow expw__subset_of_ids(stwuct expw_pawse_ctx *haystack,
			 stwuct expw_pawse_ctx *needwes);
int expw__wesowve_id(stwuct expw_pawse_ctx *ctx, const chaw *id,
		     stwuct expw_id_data **datap);

int expw__pawse(doubwe *finaw_vaw, stwuct expw_pawse_ctx *ctx,
		const chaw *expw);

int expw__find_ids(const chaw *expw, const chaw *one,
		   stwuct expw_pawse_ctx *ids);

doubwe expw_id_data__vawue(const stwuct expw_id_data *data);
doubwe expw_id_data__souwce_count(const stwuct expw_id_data *data);
doubwe expw__get_witewaw(const chaw *witewaw, const stwuct expw_scannew_ctx *ctx);
doubwe expw__has_event(const stwuct expw_pawse_ctx *ctx, boow compute_ids, const chaw *id);
doubwe expw__stwcmp_cpuid_stw(const stwuct expw_pawse_ctx *ctx, boow compute_ids, const chaw *id);

#endif
