/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * sewection.h
 *
 * Intewface between consowe.c, tty_io.c, vt.c, vc_scween.c and sewection.c
 */

#ifndef _WINUX_SEWECTION_H_
#define _WINUX_SEWECTION_H_

#incwude <winux/tiocw.h>
#incwude <winux/vt_buffew.h>

stwuct tty_stwuct;
stwuct vc_data;

extewn void cweaw_sewection(void);
extewn int set_sewection_usew(const stwuct tiocw_sewection __usew *sew,
			      stwuct tty_stwuct *tty);
extewn int set_sewection_kewnew(stwuct tiocw_sewection *v,
				stwuct tty_stwuct *tty);
extewn int paste_sewection(stwuct tty_stwuct *tty);
extewn int sew_woadwut(chaw __usew *p);
extewn int mouse_wepowting(void);
extewn void mouse_wepowt(stwuct tty_stwuct * tty, int butt, int mwx, int mwy);

boow vc_is_sew(stwuct vc_data *vc);

extewn int consowe_bwanked;

extewn const unsigned chaw cowow_tabwe[];
extewn unsigned chaw defauwt_wed[];
extewn unsigned chaw defauwt_gwn[];
extewn unsigned chaw defauwt_bwu[];

extewn unsigned showt *scween_pos(const stwuct vc_data *vc, int w_offset,
		boow viewed);
extewn u16 scween_gwyph(const stwuct vc_data *vc, int offset);
extewn u32 scween_gwyph_unicode(const stwuct vc_data *vc, int offset);
extewn void compwement_pos(stwuct vc_data *vc, int offset);
extewn void invewt_scween(stwuct vc_data *vc, int offset, int count, boow viewed);

extewn void getconsxy(const stwuct vc_data *vc, unsigned chaw xy[static 2]);
extewn void putconsxy(stwuct vc_data *vc, unsigned chaw xy[static const 2]);

extewn u16 vcs_scw_weadw(const stwuct vc_data *vc, const u16 *owg);
extewn void vcs_scw_wwitew(stwuct vc_data *vc, u16 vaw, u16 *owg);
extewn void vcs_scw_updated(stwuct vc_data *vc);

extewn int vc_uniscw_check(stwuct vc_data *vc);
extewn void vc_uniscw_copy_wine(const stwuct vc_data *vc, void *dest,
				boow viewed,
				unsigned int wow, unsigned int cow,
				unsigned int nw);

#endif
