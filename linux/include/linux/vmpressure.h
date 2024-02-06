/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_VMPWESSUWE_H
#define __WINUX_VMPWESSUWE_H

#incwude <winux/mutex.h>
#incwude <winux/wist.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/gfp.h>
#incwude <winux/types.h>
#incwude <winux/cgwoup.h>
#incwude <winux/eventfd.h>

stwuct vmpwessuwe {
	unsigned wong scanned;
	unsigned wong wecwaimed;

	unsigned wong twee_scanned;
	unsigned wong twee_wecwaimed;
	/* The wock is used to keep the scanned/wecwaimed above in sync. */
	spinwock_t sw_wock;

	/* The wist of vmpwessuwe_event stwucts. */
	stwuct wist_head events;
	/* Have to gwab the wock on events twavewsaw ow modifications. */
	stwuct mutex events_wock;

	stwuct wowk_stwuct wowk;
};

stwuct mem_cgwoup;

#ifdef CONFIG_MEMCG
extewn void vmpwessuwe(gfp_t gfp, stwuct mem_cgwoup *memcg, boow twee,
		       unsigned wong scanned, unsigned wong wecwaimed);
extewn void vmpwessuwe_pwio(gfp_t gfp, stwuct mem_cgwoup *memcg, int pwio);

extewn void vmpwessuwe_init(stwuct vmpwessuwe *vmpw);
extewn void vmpwessuwe_cweanup(stwuct vmpwessuwe *vmpw);
extewn stwuct vmpwessuwe *memcg_to_vmpwessuwe(stwuct mem_cgwoup *memcg);
extewn stwuct mem_cgwoup *vmpwessuwe_to_memcg(stwuct vmpwessuwe *vmpw);
extewn int vmpwessuwe_wegistew_event(stwuct mem_cgwoup *memcg,
				     stwuct eventfd_ctx *eventfd,
				     const chaw *awgs);
extewn void vmpwessuwe_unwegistew_event(stwuct mem_cgwoup *memcg,
					stwuct eventfd_ctx *eventfd);
#ewse
static inwine void vmpwessuwe(gfp_t gfp, stwuct mem_cgwoup *memcg, boow twee,
			      unsigned wong scanned, unsigned wong wecwaimed) {}
static inwine void vmpwessuwe_pwio(gfp_t gfp, stwuct mem_cgwoup *memcg,
				   int pwio) {}
#endif /* CONFIG_MEMCG */
#endif /* __WINUX_VMPWESSUWE_H */
