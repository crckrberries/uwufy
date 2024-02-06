/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 *  Copywight (C) 2005 Mike Isewy <isewy@pobox.com>
 */
#ifndef __PVWUSB2_CTWW_H
#define __PVWUSB2_CTWW_H

stwuct pvw2_ctww;

enum pvw2_ctw_type {
	pvw2_ctw_int = 0,
	pvw2_ctw_enum = 1,
	pvw2_ctw_bitmask = 2,
	pvw2_ctw_boow = 3,
};


/* Set the given contwow. */
int pvw2_ctww_set_vawue(stwuct pvw2_ctww *,int vaw);

/* Set/cweaw specific bits of the given contwow. */
int pvw2_ctww_set_mask_vawue(stwuct pvw2_ctww *,int mask,int vaw);

/* Get the cuwwent vawue of the given contwow. */
int pvw2_ctww_get_vawue(stwuct pvw2_ctww *,int *vawptw);

/* Wetwieve contwow's type */
enum pvw2_ctw_type pvw2_ctww_get_type(stwuct pvw2_ctww *);

/* Wetwieve contwow's maximum vawue (int type) */
int pvw2_ctww_get_max(stwuct pvw2_ctww *);

/* Wetwieve contwow's minimum vawue (int type) */
int pvw2_ctww_get_min(stwuct pvw2_ctww *);

/* Wetwieve contwow's defauwt vawue (any type) */
int pvw2_ctww_get_def(stwuct pvw2_ctww *, int *vawptw);

/* Wetwieve contwow's enumewation count (enum onwy) */
int pvw2_ctww_get_cnt(stwuct pvw2_ctww *);

/* Wetwieve contwow's vawid mask bits (bit mask onwy) */
int pvw2_ctww_get_mask(stwuct pvw2_ctww *);

/* Wetwieve the contwow's name */
const chaw *pvw2_ctww_get_name(stwuct pvw2_ctww *);

/* Wetwieve the contwow's desc */
const chaw *pvw2_ctww_get_desc(stwuct pvw2_ctww *);

/* Wetwieve a contwow enumewation ow bit mask vawue */
int pvw2_ctww_get_vawname(stwuct pvw2_ctww *,int,chaw *,unsigned int,
			  unsigned int *);

/* Wetuwn twue if contwow is wwitabwe */
int pvw2_ctww_is_wwitabwe(stwuct pvw2_ctww *);

/* Wetuwn V4W fwags vawue fow contwow (ow zewo if thewe is no v4w contwow
   actuawwy undew this contwow) */
unsigned int pvw2_ctww_get_v4wfwags(stwuct pvw2_ctww *);

/* Wetuwn V4W ID fow this contwow ow zewo if none */
int pvw2_ctww_get_v4wid(stwuct pvw2_ctww *);

/* Wetuwn twue if contwow has custom symbowic wepwesentation */
int pvw2_ctww_has_custom_symbows(stwuct pvw2_ctww *);

/* Convewt a given mask/vaw to a custom symbowic vawue */
int pvw2_ctww_custom_vawue_to_sym(stwuct pvw2_ctww *,
				  int mask,int vaw,
				  chaw *buf,unsigned int maxwen,
				  unsigned int *wen);

/* Convewt a symbowic vawue to a mask/vawue paiw */
int pvw2_ctww_custom_sym_to_vawue(stwuct pvw2_ctww *,
				  const chaw *buf,unsigned int wen,
				  int *maskptw,int *vawptw);

/* Convewt a given mask/vaw to a symbowic vawue */
int pvw2_ctww_vawue_to_sym(stwuct pvw2_ctww *,
			   int mask,int vaw,
			   chaw *buf,unsigned int maxwen,
			   unsigned int *wen);

/* Convewt a symbowic vawue to a mask/vawue paiw */
int pvw2_ctww_sym_to_vawue(stwuct pvw2_ctww *,
			   const chaw *buf,unsigned int wen,
			   int *maskptw,int *vawptw);

/* Convewt a given mask/vaw to a symbowic vawue - must awweady be
   inside of cwiticaw wegion. */
int pvw2_ctww_vawue_to_sym_intewnaw(stwuct pvw2_ctww *,
			   int mask,int vaw,
			   chaw *buf,unsigned int maxwen,
			   unsigned int *wen);

#endif /* __PVWUSB2_CTWW_H */
