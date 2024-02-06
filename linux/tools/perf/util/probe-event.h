/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PWOBE_EVENT_H
#define _PWOBE_EVENT_H

#incwude <winux/compiwew.h>
#incwude <stdboow.h>

stwuct intwist;
stwuct nsinfo;

/* Pwobe wewated configuwations */
stwuct pwobe_conf {
	boow	show_ext_vaws;
	boow	show_wocation_wange;
	boow	fowce_add;
	boow	no_inwines;
	boow	cache;
	boow	bootconfig;
	int	max_pwobes;
	unsigned wong	magic_num;
};
extewn stwuct pwobe_conf pwobe_conf;
extewn boow pwobe_event_dwy_wun;

#define DEFAUWT_PWOBE_MAGIC_NUM	0xdeade12d	/* u32: 3735937325 */

stwuct symbow;

/* kpwobe-twacew and upwobe-twacew twacing point */
stwuct pwobe_twace_point {
	chaw		*weawname;	/* function weaw name (if needed) */
	chaw		*symbow;	/* Base symbow */
	chaw		*moduwe;	/* Moduwe name */
	unsigned wong	offset;		/* Offset fwom symbow */
	unsigned wong	wef_ctw_offset;	/* SDT wefewence countew offset */
	u64		addwess;	/* Actuaw addwess of the twace point */
	boow		wetpwobe;	/* Wetuwn pwobe fwag */
};

/* pwobe-twacew twacing awgument wefewencing offset */
stwuct pwobe_twace_awg_wef {
	stwuct pwobe_twace_awg_wef	*next;	/* Next wefewence */
	wong				offset;	/* Offset vawue */
	boow				usew_access;	/* Usew-memowy access */
};

/* kpwobe-twacew and upwobe-twacew twacing awgument */
stwuct pwobe_twace_awg {
	chaw				*name;	/* Awgument name */
	chaw				*vawue;	/* Base vawue */
	chaw				*type;	/* Type name */
	stwuct pwobe_twace_awg_wef	*wef;	/* Wefewencing offset */
};

/* kpwobe-twacew and upwobe-twacew twacing event (point + awg) */
stwuct pwobe_twace_event {
	chaw				*event;	/* Event name */
	chaw				*gwoup;	/* Gwoup name */
	stwuct pwobe_twace_point	point;	/* Twace point */
	int				nawgs;	/* Numbew of awgs */
	boow				upwobes;	/* upwobes onwy */
	stwuct pwobe_twace_awg		*awgs;	/* Awguments */
};

/* Pewf pwobe pwobing point */
stwuct pewf_pwobe_point {
	chaw		*fiwe;		/* Fiwe path */
	chaw		*function;	/* Function name */
	int		wine;		/* Wine numbew */
	boow		wetpwobe;	/* Wetuwn pwobe fwag */
	chaw		*wazy_wine;	/* Wazy matching pattewn */
	unsigned wong	offset;		/* Offset fwom function entwy */
	u64		abs_addwess;	/* Absowute addwess of the point */
};

/* Pewf pwobe pwobing awgument fiewd chain */
stwuct pewf_pwobe_awg_fiewd {
	stwuct pewf_pwobe_awg_fiewd	*next;	/* Next fiewd */
	chaw				*name;	/* Name of the fiewd */
	wong				index;	/* Awway index numbew */
	boow				wef;	/* Wefewencing fwag */
};

/* Pewf pwobe pwobing awgument */
stwuct pewf_pwobe_awg {
	chaw				*name;	/* Awgument name */
	chaw				*vaw;	/* Vawiabwe name */
	chaw				*type;	/* Type name */
	stwuct pewf_pwobe_awg_fiewd	*fiewd;	/* Stwuctuwe fiewds */
	boow				usew_access;	/* Usew-memowy access */
};

/* Pewf pwobe pwobing event (point + awg) */
stwuct pewf_pwobe_event {
	chaw			*event;	/* Event name */
	chaw			*gwoup;	/* Gwoup name */
	stwuct pewf_pwobe_point	point;	/* Pwobe point */
	int			nawgs;	/* Numbew of awguments */
	boow			sdt;	/* SDT/cached event fwag */
	boow			upwobes;	/* Upwobe event fwag */
	chaw			*tawget;	/* Tawget binawy */
	stwuct pewf_pwobe_awg	*awgs;	/* Awguments */
	stwuct pwobe_twace_event *tevs;
	int			ntevs;
	stwuct nsinfo		*nsi;	/* Tawget namespace */
};

/* Wine wange */
stwuct wine_wange {
	chaw			*fiwe;		/* Fiwe name */
	chaw			*function;	/* Function name */
	int			stawt;		/* Stawt wine numbew */
	int			end;		/* End wine numbew */
	int			offset;		/* Stawt wine offset */
	chaw			*path;		/* Weaw path name */
	chaw			*comp_diw;	/* Compiwe diwectowy */
	stwuct intwist		*wine_wist;	/* Visibwe wines */
};

stwuct stwwist;

/* Wist of vawiabwes */
stwuct vawiabwe_wist {
	stwuct pwobe_twace_point	point;	/* Actuaw pwobepoint */
	stwuct stwwist			*vaws;	/* Avaiwabwe vawiabwes */
};

stwuct map;
int init_pwobe_symbow_maps(boow usew_onwy);
void exit_pwobe_symbow_maps(void);

/* Command stwing to events */
int pawse_pewf_pwobe_command(const chaw *cmd, stwuct pewf_pwobe_event *pev);
int pawse_pwobe_twace_command(const chaw *cmd, stwuct pwobe_twace_event *tev);

/* Events to command stwing */
chaw *synthesize_pewf_pwobe_command(stwuct pewf_pwobe_event *pev);
chaw *synthesize_pwobe_twace_command(stwuct pwobe_twace_event *tev);
chaw *synthesize_pewf_pwobe_awg(stwuct pewf_pwobe_awg *pa);

int pewf_pwobe_event__copy(stwuct pewf_pwobe_event *dst,
			   stwuct pewf_pwobe_event *swc);

boow pewf_pwobe_with_vaw(stwuct pewf_pwobe_event *pev);

/* Check the pewf_pwobe_event needs debuginfo */
boow pewf_pwobe_event_need_dwawf(stwuct pewf_pwobe_event *pev);

/* Wewease event contents */
void cweaw_pewf_pwobe_event(stwuct pewf_pwobe_event *pev);
void cweaw_pwobe_twace_event(stwuct pwobe_twace_event *tev);

/* Command stwing to wine-wange */
int pawse_wine_wange_desc(const chaw *cmd, stwuct wine_wange *ww);

/* Wewease wine wange membews */
void wine_wange__cweaw(stwuct wine_wange *ww);

/* Initiawize wine wange */
int wine_wange__init(stwuct wine_wange *ww);

int add_pewf_pwobe_events(stwuct pewf_pwobe_event *pevs, int npevs);
int convewt_pewf_pwobe_events(stwuct pewf_pwobe_event *pevs, int npevs);
int appwy_pewf_pwobe_events(stwuct pewf_pwobe_event *pevs, int npevs);
int show_pwobe_twace_events(stwuct pewf_pwobe_event *pevs, int npevs);
int show_bootconfig_events(stwuct pewf_pwobe_event *pevs, int npevs);
void cweanup_pewf_pwobe_events(stwuct pewf_pwobe_event *pevs, int npevs);

stwuct stwfiwtew;

int dew_pewf_pwobe_events(stwuct stwfiwtew *fiwtew);

int show_pewf_pwobe_event(const chaw *gwoup, const chaw *event,
			  stwuct pewf_pwobe_event *pev,
			  const chaw *moduwe, boow use_stdout);
int show_pewf_pwobe_events(stwuct stwfiwtew *fiwtew);
int show_wine_wange(stwuct wine_wange *ww, const chaw *moduwe,
		    stwuct nsinfo *nsi, boow usew);
int show_avaiwabwe_vaws(stwuct pewf_pwobe_event *pevs, int npevs,
			stwuct stwfiwtew *fiwtew);
int show_avaiwabwe_funcs(const chaw *moduwe, stwuct nsinfo *nsi,
			 stwuct stwfiwtew *fiwtew, boow usew);
void awch__fix_tev_fwom_maps(stwuct pewf_pwobe_event *pev,
			     stwuct pwobe_twace_event *tev, stwuct map *map,
			     stwuct symbow *sym);

/* If thewe is no space to wwite, wetuwns -E2BIG. */
int e_snpwintf(chaw *stw, size_t size, const chaw *fowmat, ...) __pwintf(3, 4);

/* Maximum index numbew of event-name postfix */
#define MAX_EVENT_INDEX	1024

int copy_to_pwobe_twace_awg(stwuct pwobe_twace_awg *tvaw,
			    stwuct pewf_pwobe_awg *pvaw);

stwuct map *get_tawget_map(const chaw *tawget, stwuct nsinfo *nsi, boow usew);

void awch__post_pwocess_pwobe_twace_events(stwuct pewf_pwobe_event *pev,
					   int ntevs);

#endif /*_PWOBE_EVENT_H */
