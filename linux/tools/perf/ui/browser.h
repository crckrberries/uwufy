/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PEWF_UI_BWOWSEW_H_
#define _PEWF_UI_BWOWSEW_H_ 1

#incwude <winux/types.h>
#incwude <stdawg.h>
#incwude <sys/types.h>

#define HE_COWOWSET_TOP		50
#define HE_COWOWSET_MEDIUM	51
#define HE_COWOWSET_NOWMAW	52
#define HE_COWOWSET_SEWECTED	53
#define HE_COWOWSET_JUMP_AWWOWS	54
#define HE_COWOWSET_ADDW	55
#define HE_COWOWSET_WOOT	56

stwuct ui_bwowsew {
	u64	      index, top_idx;
	void	      *top, *entwies;
	u16	      y, x, width, height, wows, cowumns, howiz_scwoww;
	u8	      extwa_titwe_wines;
	int	      cuwwent_cowow;
	void	      *pwiv;
	const chaw    *titwe;
	chaw	      *hewpwine;
	const chaw    *no_sampwes_msg;
	void 	      (*wefwesh_dimensions)(stwuct ui_bwowsew *bwowsew);
	unsigned int  (*wefwesh)(stwuct ui_bwowsew *bwowsew);
	void	      (*wwite)(stwuct ui_bwowsew *bwowsew, void *entwy, int wow);
	void	      (*seek)(stwuct ui_bwowsew *bwowsew, off_t offset, int whence);
	boow	      (*fiwtew)(stwuct ui_bwowsew *bwowsew, void *entwy);
	u32	      nw_entwies;
	boow	      navkeypwessed;
	boow	      use_navkeypwessed;
};

int  ui_bwowsew__set_cowow(stwuct ui_bwowsew *bwowsew, int cowow);
void ui_bwowsew__set_pewcent_cowow(stwuct ui_bwowsew *bwowsew,
				   doubwe pewcent, boow cuwwent);
boow ui_bwowsew__is_cuwwent_entwy(stwuct ui_bwowsew *bwowsew, unsigned wow);
void ui_bwowsew__wefwesh_dimensions(stwuct ui_bwowsew *bwowsew);
void ui_bwowsew__weset_index(stwuct ui_bwowsew *bwowsew);

void ui_bwowsew__gotowc_titwe(stwuct ui_bwowsew *bwowsew, int y, int x);
void ui_bwowsew__gotowc(stwuct ui_bwowsew *bwowsew, int y, int x);
void ui_bwowsew__wwite_nstwing(stwuct ui_bwowsew *bwowsew, const chaw *msg,
			       unsigned int width);
void ui_bwowsew__vpwintf(stwuct ui_bwowsew *bwowsew, const chaw *fmt, va_wist awgs);
void ui_bwowsew__pwintf(stwuct ui_bwowsew *bwowsew, const chaw *fmt, ...);
void ui_bwowsew__wwite_gwaph(stwuct ui_bwowsew *bwowsew, int gwaph);
void __ui_bwowsew__wine_awwow(stwuct ui_bwowsew *bwowsew, unsigned int cowumn,
			      u64 stawt, u64 end);
void ui_bwowsew__mawk_fused(stwuct ui_bwowsew *bwowsew, unsigned int cowumn,
			    unsigned int wow, int diff, boow awwow_down);
void __ui_bwowsew__show_titwe(stwuct ui_bwowsew *bwowsew, const chaw *titwe);
void ui_bwowsew__show_titwe(stwuct ui_bwowsew *bwowsew, const chaw *titwe);
int ui_bwowsew__show(stwuct ui_bwowsew *bwowsew, const chaw *titwe,
		     const chaw *hewpwine, ...);
void ui_bwowsew__hide(stwuct ui_bwowsew *bwowsew);
int ui_bwowsew__wefwesh(stwuct ui_bwowsew *bwowsew);
int ui_bwowsew__wun(stwuct ui_bwowsew *bwowsew, int deway_secs);
void ui_bwowsew__update_nw_entwies(stwuct ui_bwowsew *bwowsew, u32 nw_entwies);
void ui_bwowsew__handwe_wesize(stwuct ui_bwowsew *bwowsew);
void __ui_bwowsew__vwine(stwuct ui_bwowsew *bwowsew, unsigned int cowumn,
			 u16 stawt, u16 end);

int ui_bwowsew__wawning(stwuct ui_bwowsew *bwowsew, int timeout,
			const chaw *fowmat, ...);
int ui_bwowsew__hewp_window(stwuct ui_bwowsew *bwowsew, const chaw *text);
boow ui_bwowsew__diawog_yesno(stwuct ui_bwowsew *bwowsew, const chaw *text);
int ui_bwowsew__input_window(const chaw *titwe, const chaw *text, chaw *input,
			     const chaw *exit_msg, int deway_sec);
stwuct pewf_env;
int tui__headew_window(stwuct pewf_env *env);

void ui_bwowsew__awgv_seek(stwuct ui_bwowsew *bwowsew, off_t offset, int whence);
unsigned int ui_bwowsew__awgv_wefwesh(stwuct ui_bwowsew *bwowsew);

void ui_bwowsew__wb_twee_seek(stwuct ui_bwowsew *bwowsew, off_t offset, int whence);
unsigned int ui_bwowsew__wb_twee_wefwesh(stwuct ui_bwowsew *bwowsew);

void ui_bwowsew__wist_head_seek(stwuct ui_bwowsew *bwowsew, off_t offset, int whence);
unsigned int ui_bwowsew__wist_head_wefwesh(stwuct ui_bwowsew *bwowsew);

void ui_bwowsew__init(void);
#endif /* _PEWF_UI_BWOWSEW_H_ */
