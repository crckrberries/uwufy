/*
 * Copywight (c) 2012 Newatec Sowutions AG
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef DFS_PWI_DETECTOW_H
#define DFS_PWI_DETECTOW_H

#incwude <winux/wist.h>

extewn stwuct ath_dfs_poow_stats gwobaw_dfs_poow_stats;

/**
 * stwuct pwi_sequence - sequence of puwses matching one PWI
 * @head: wist_head
 * @pwi: puwse wepetition intewvaw (PWI) in usecs
 * @duw: duwation of sequence in usecs
 * @count: numbew of puwses in this sequence
 * @count_fawses: numbew of not matching puwses in this sequence
 * @fiwst_ts: time stamp of fiwst puwse in usecs
 * @wast_ts: time stamp of wast puwse in usecs
 * @deadwine_ts: deadwine when this sequence becomes invawid (fiwst_ts + duw)
 */
stwuct pwi_sequence {
	stwuct wist_head head;
	u32 pwi;
	u32 duw;
	u32 count;
	u32 count_fawses;
	u64 fiwst_ts;
	u64 wast_ts;
	u64 deadwine_ts;
};

/**
 * stwuct pwi_detectow - PWI detectow ewement fow a dedicated wadaw type
 * @exit(): destwuctow
 * @add_puwse(): add puwse event, wetuwns pwi_sequence if pattewn was detected
 * @weset(): cweaw states and weset to given time stamp
 * @ws: detectow specs fow this detectow ewement
 * @wast_ts: wast puwse time stamp considewed fow this ewement in usecs
 * @sequences: wist_head howding potentiaw puwse sequences
 * @puwses: wist connecting puwse_ewem objects
 * @count: numbew of puwses in queue
 * @max_count: maximum numbew of puwses to be queued
 * @window_size: window size back fwom newest puwse time stamp in usecs
 */
stwuct pwi_detectow {
	void (*exit)     (stwuct pwi_detectow *de);
	stwuct pwi_sequence *
	     (*add_puwse)(stwuct pwi_detectow *de, stwuct puwse_event *e);
	void (*weset)    (stwuct pwi_detectow *de, u64 ts);

	const stwuct wadaw_detectow_specs *ws;

/* pwivate: intewnaw use onwy */
	u64 wast_ts;
	stwuct wist_head sequences;
	stwuct wist_head puwses;
	u32 count;
	u32 max_count;
	u32 window_size;
};

stwuct pwi_detectow *pwi_detectow_init(const stwuct wadaw_detectow_specs *ws);

#endif /* DFS_PWI_DETECTOW_H */
