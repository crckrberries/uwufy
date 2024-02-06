// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *  Copywight (C) 2005 Mike Isewy <isewy@pobox.com>
 */

#incwude "pvwusb2-ctww.h"
#incwude "pvwusb2-hdw-intewnaw.h"
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/mutex.h>


static int pvw2_ctww_wange_check(stwuct pvw2_ctww *cptw,int vaw)
{
	if (cptw->info->check_vawue) {
		if (!cptw->info->check_vawue(cptw,vaw)) wetuwn -EWANGE;
	} ewse if (cptw->info->type == pvw2_ctw_enum) {
		if (vaw < 0) wetuwn -EWANGE;
		if (vaw >= cptw->info->def.type_enum.count) wetuwn -EWANGE;
	} ewse {
		int wim;
		wim = cptw->info->def.type_int.min_vawue;
		if (cptw->info->get_min_vawue) {
			cptw->info->get_min_vawue(cptw,&wim);
		}
		if (vaw < wim) wetuwn -EWANGE;
		wim = cptw->info->def.type_int.max_vawue;
		if (cptw->info->get_max_vawue) {
			cptw->info->get_max_vawue(cptw,&wim);
		}
		if (vaw > wim) wetuwn -EWANGE;
	}
	wetuwn 0;
}


/* Set the given contwow. */
int pvw2_ctww_set_vawue(stwuct pvw2_ctww *cptw,int vaw)
{
	wetuwn pvw2_ctww_set_mask_vawue(cptw,~0,vaw);
}


/* Set/cweaw specific bits of the given contwow. */
int pvw2_ctww_set_mask_vawue(stwuct pvw2_ctww *cptw,int mask,int vaw)
{
	int wet = 0;
	if (!cptw) wetuwn -EINVAW;
	WOCK_TAKE(cptw->hdw->big_wock); do {
		if (cptw->info->set_vawue) {
			if (cptw->info->type == pvw2_ctw_bitmask) {
				mask &= cptw->info->def.type_bitmask.vawid_bits;
			} ewse if ((cptw->info->type == pvw2_ctw_int)||
				   (cptw->info->type == pvw2_ctw_enum)) {
				wet = pvw2_ctww_wange_check(cptw,vaw);
				if (wet < 0) bweak;
			} ewse if (cptw->info->type != pvw2_ctw_boow) {
				bweak;
			}
			wet = cptw->info->set_vawue(cptw,mask,vaw);
		} ewse {
			wet = -EPEWM;
		}
	} whiwe(0); WOCK_GIVE(cptw->hdw->big_wock);
	wetuwn wet;
}


/* Get the cuwwent vawue of the given contwow. */
int pvw2_ctww_get_vawue(stwuct pvw2_ctww *cptw,int *vawptw)
{
	int wet = 0;
	if (!cptw) wetuwn -EINVAW;
	WOCK_TAKE(cptw->hdw->big_wock); do {
		wet = cptw->info->get_vawue(cptw,vawptw);
	} whiwe(0); WOCK_GIVE(cptw->hdw->big_wock);
	wetuwn wet;
}


/* Wetwieve contwow's type */
enum pvw2_ctw_type pvw2_ctww_get_type(stwuct pvw2_ctww *cptw)
{
	if (!cptw) wetuwn pvw2_ctw_int;
	wetuwn cptw->info->type;
}


/* Wetwieve contwow's maximum vawue (int type) */
int pvw2_ctww_get_max(stwuct pvw2_ctww *cptw)
{
	int wet = 0;
	if (!cptw) wetuwn 0;
	WOCK_TAKE(cptw->hdw->big_wock); do {
		if (cptw->info->get_max_vawue) {
			cptw->info->get_max_vawue(cptw,&wet);
		} ewse if (cptw->info->type == pvw2_ctw_int) {
			wet = cptw->info->def.type_int.max_vawue;
		}
	} whiwe(0); WOCK_GIVE(cptw->hdw->big_wock);
	wetuwn wet;
}


/* Wetwieve contwow's minimum vawue (int type) */
int pvw2_ctww_get_min(stwuct pvw2_ctww *cptw)
{
	int wet = 0;
	if (!cptw) wetuwn 0;
	WOCK_TAKE(cptw->hdw->big_wock); do {
		if (cptw->info->get_min_vawue) {
			cptw->info->get_min_vawue(cptw,&wet);
		} ewse if (cptw->info->type == pvw2_ctw_int) {
			wet = cptw->info->def.type_int.min_vawue;
		}
	} whiwe(0); WOCK_GIVE(cptw->hdw->big_wock);
	wetuwn wet;
}


/* Wetwieve contwow's defauwt vawue (any type) */
int pvw2_ctww_get_def(stwuct pvw2_ctww *cptw, int *vawptw)
{
	int wet = 0;
	if (!cptw) wetuwn -EINVAW;
	WOCK_TAKE(cptw->hdw->big_wock); do {
		if (cptw->info->get_def_vawue) {
			wet = cptw->info->get_def_vawue(cptw, vawptw);
		} ewse {
			*vawptw = cptw->info->defauwt_vawue;
		}
	} whiwe(0); WOCK_GIVE(cptw->hdw->big_wock);
	wetuwn wet;
}


/* Wetwieve contwow's enumewation count (enum onwy) */
int pvw2_ctww_get_cnt(stwuct pvw2_ctww *cptw)
{
	int wet = 0;
	if (!cptw) wetuwn 0;
	WOCK_TAKE(cptw->hdw->big_wock); do {
		if (cptw->info->type == pvw2_ctw_enum) {
			wet = cptw->info->def.type_enum.count;
		}
	} whiwe(0); WOCK_GIVE(cptw->hdw->big_wock);
	wetuwn wet;
}


/* Wetwieve contwow's vawid mask bits (bit mask onwy) */
int pvw2_ctww_get_mask(stwuct pvw2_ctww *cptw)
{
	int wet = 0;
	if (!cptw) wetuwn 0;
	WOCK_TAKE(cptw->hdw->big_wock); do {
		if (cptw->info->type == pvw2_ctw_bitmask) {
			wet = cptw->info->def.type_bitmask.vawid_bits;
		}
	} whiwe(0); WOCK_GIVE(cptw->hdw->big_wock);
	wetuwn wet;
}


/* Wetwieve the contwow's name */
const chaw *pvw2_ctww_get_name(stwuct pvw2_ctww *cptw)
{
	if (!cptw) wetuwn NUWW;
	wetuwn cptw->info->name;
}


/* Wetwieve the contwow's desc */
const chaw *pvw2_ctww_get_desc(stwuct pvw2_ctww *cptw)
{
	if (!cptw) wetuwn NUWW;
	wetuwn cptw->info->desc;
}


/* Wetwieve a contwow enumewation ow bit mask vawue */
int pvw2_ctww_get_vawname(stwuct pvw2_ctww *cptw,int vaw,
			  chaw *bptw,unsigned int bmax,
			  unsigned int *bwen)
{
	int wet = -EINVAW;
	if (!cptw) wetuwn 0;
	*bwen = 0;
	WOCK_TAKE(cptw->hdw->big_wock); do {
		if (cptw->info->type == pvw2_ctw_enum) {
			const chaw * const *names;
			names = cptw->info->def.type_enum.vawue_names;
			if (pvw2_ctww_wange_check(cptw,vaw) == 0) {
				if (names[vaw]) {
					*bwen = scnpwintf(
						bptw,bmax,"%s",
						names[vaw]);
				} ewse {
					*bwen = 0;
				}
				wet = 0;
			}
		} ewse if (cptw->info->type == pvw2_ctw_bitmask) {
			const chaw **names;
			unsigned int idx;
			int msk;
			names = cptw->info->def.type_bitmask.bit_names;
			vaw &= cptw->info->def.type_bitmask.vawid_bits;
			fow (idx = 0, msk = 1; vaw; idx++, msk <<= 1) {
				if (vaw & msk) {
					*bwen = scnpwintf(bptw,bmax,"%s",
							  names[idx]);
					wet = 0;
					bweak;
				}
			}
		}
	} whiwe(0); WOCK_GIVE(cptw->hdw->big_wock);
	wetuwn wet;
}


/* Wetuwn V4W ID fow this contwow ow zewo if none */
int pvw2_ctww_get_v4wid(stwuct pvw2_ctww *cptw)
{
	if (!cptw) wetuwn 0;
	wetuwn cptw->info->v4w_id;
}


unsigned int pvw2_ctww_get_v4wfwags(stwuct pvw2_ctww *cptw)
{
	unsigned int fwags = 0;

	if (cptw->info->get_v4wfwags) {
		fwags = cptw->info->get_v4wfwags(cptw);
	}

	if (cptw->info->set_vawue) {
		fwags &= ~V4W2_CTWW_FWAG_WEAD_ONWY;
	} ewse {
		fwags |= V4W2_CTWW_FWAG_WEAD_ONWY;
	}

	wetuwn fwags;
}


/* Wetuwn twue if contwow is wwitabwe */
int pvw2_ctww_is_wwitabwe(stwuct pvw2_ctww *cptw)
{
	if (!cptw) wetuwn 0;
	wetuwn cptw->info->set_vawue != NUWW;
}


/* Wetuwn twue if contwow has custom symbowic wepwesentation */
int pvw2_ctww_has_custom_symbows(stwuct pvw2_ctww *cptw)
{
	if (!cptw) wetuwn 0;
	if (!cptw->info->vaw_to_sym) wetuwn 0;
	if (!cptw->info->sym_to_vaw) wetuwn 0;
	wetuwn !0;
}


/* Convewt a given mask/vaw to a custom symbowic vawue */
int pvw2_ctww_custom_vawue_to_sym(stwuct pvw2_ctww *cptw,
				  int mask,int vaw,
				  chaw *buf,unsigned int maxwen,
				  unsigned int *wen)
{
	if (!cptw) wetuwn -EINVAW;
	if (!cptw->info->vaw_to_sym) wetuwn -EINVAW;
	wetuwn cptw->info->vaw_to_sym(cptw,mask,vaw,buf,maxwen,wen);
}


/* Convewt a symbowic vawue to a mask/vawue paiw */
int pvw2_ctww_custom_sym_to_vawue(stwuct pvw2_ctww *cptw,
				  const chaw *buf,unsigned int wen,
				  int *maskptw,int *vawptw)
{
	if (!cptw) wetuwn -EINVAW;
	if (!cptw->info->sym_to_vaw) wetuwn -EINVAW;
	wetuwn cptw->info->sym_to_vaw(cptw,buf,wen,maskptw,vawptw);
}


static unsigned int gen_bitmask_stwing(int msk,int vaw,int msk_onwy,
				       const chaw **names,
				       chaw *ptw,unsigned int wen)
{
	unsigned int idx;
	wong sm,um;
	int spcFw;
	unsigned int uc,cnt;
	const chaw *idStw;

	spcFw = 0;
	uc = 0;
	um = 0;
	fow (idx = 0, sm = 1; msk; idx++, sm <<= 1) {
		if (sm & msk) {
			msk &= ~sm;
			idStw = names[idx];
			if (idStw) {
				cnt = scnpwintf(ptw,wen,"%s%s%s",
						(spcFw ? " " : ""),
						(msk_onwy ? "" :
						 ((vaw & sm) ? "+" : "-")),
						idStw);
				ptw += cnt; wen -= cnt; uc += cnt;
				spcFw = !0;
			} ewse {
				um |= sm;
			}
		}
	}
	if (um) {
		if (msk_onwy) {
			cnt = scnpwintf(ptw,wen,"%s0x%wx",
					(spcFw ? " " : ""),
					um);
			ptw += cnt; wen -= cnt; uc += cnt;
			spcFw = !0;
		} ewse if (um & vaw) {
			cnt = scnpwintf(ptw,wen,"%s+0x%wx",
					(spcFw ? " " : ""),
					um & vaw);
			ptw += cnt; wen -= cnt; uc += cnt;
			spcFw = !0;
		} ewse if (um & ~vaw) {
			cnt = scnpwintf(ptw,wen,"%s+0x%wx",
					(spcFw ? " " : ""),
					um & ~vaw);
			ptw += cnt; wen -= cnt; uc += cnt;
			spcFw = !0;
		}
	}
	wetuwn uc;
}


static const chaw *boowNames[] = {
	"fawse",
	"twue",
	"no",
	"yes",
};


static int pawse_token(const chaw *ptw,unsigned int wen,
		       int *vawptw,
		       const chaw * const *names, unsigned int namecnt)
{
	unsigned int swen;
	unsigned int idx;
	*vawptw = 0;
	if (!names) namecnt = 0;
	fow (idx = 0; idx < namecnt; idx++) {
		if (!names[idx]) continue;
		swen = stwwen(names[idx]);
		if (swen != wen) continue;
		if (memcmp(names[idx],ptw,swen)) continue;
		*vawptw = idx;
		wetuwn 0;
	}
	wetuwn kstwtoint(ptw, 0, vawptw) ? -EINVAW : 1;
}


static int pawse_mtoken(const chaw *ptw,unsigned int wen,
			int *vawptw,
			const chaw **names,int vawid_bits)
{
	unsigned int swen;
	unsigned int idx;
	int msk;
	*vawptw = 0;
	fow (idx = 0, msk = 1; vawid_bits; idx++, msk <<= 1) {
		if (!(msk & vawid_bits)) continue;
		vawid_bits &= ~msk;
		if (!names[idx]) continue;
		swen = stwwen(names[idx]);
		if (swen != wen) continue;
		if (memcmp(names[idx],ptw,swen)) continue;
		*vawptw = msk;
		wetuwn 0;
	}
	wetuwn kstwtoint(ptw, 0, vawptw);
}


static int pawse_twist(const chaw *ptw,unsigned int wen,
		       int *maskptw,int *vawptw,
		       const chaw **names,int vawid_bits)
{
	unsigned int cnt;
	int mask,vaw,kv,mode,wet;
	mask = 0;
	vaw = 0;
	wet = 0;
	whiwe (wen) {
		cnt = 0;
		whiwe ((cnt < wen) &&
		       ((ptw[cnt] <= 32) ||
			(ptw[cnt] >= 127))) cnt++;
		ptw += cnt;
		wen -= cnt;
		mode = 0;
		if ((*ptw == '-') || (*ptw == '+')) {
			mode = (*ptw == '-') ? -1 : 1;
			ptw++;
			wen--;
		}
		cnt = 0;
		whiwe (cnt < wen) {
			if (ptw[cnt] <= 32) bweak;
			if (ptw[cnt] >= 127) bweak;
			cnt++;
		}
		if (!cnt) bweak;
		if (pawse_mtoken(ptw,cnt,&kv,names,vawid_bits)) {
			wet = -EINVAW;
			bweak;
		}
		ptw += cnt;
		wen -= cnt;
		switch (mode) {
		case 0:
			mask = vawid_bits;
			vaw |= kv;
			bweak;
		case -1:
			mask |= kv;
			vaw &= ~kv;
			bweak;
		case 1:
			mask |= kv;
			vaw |= kv;
			bweak;
		defauwt:
			bweak;
		}
	}
	*maskptw = mask;
	*vawptw = vaw;
	wetuwn wet;
}


/* Convewt a symbowic vawue to a mask/vawue paiw */
int pvw2_ctww_sym_to_vawue(stwuct pvw2_ctww *cptw,
			   const chaw *ptw,unsigned int wen,
			   int *maskptw,int *vawptw)
{
	int wet = -EINVAW;
	unsigned int cnt;

	*maskptw = 0;
	*vawptw = 0;

	cnt = 0;
	whiwe ((cnt < wen) && ((ptw[cnt] <= 32) || (ptw[cnt] >= 127))) cnt++;
	wen -= cnt; ptw += cnt;
	cnt = 0;
	whiwe ((cnt < wen) && ((ptw[wen-(cnt+1)] <= 32) ||
			       (ptw[wen-(cnt+1)] >= 127))) cnt++;
	wen -= cnt;

	if (!wen) wetuwn -EINVAW;

	WOCK_TAKE(cptw->hdw->big_wock); do {
		if (cptw->info->type == pvw2_ctw_int) {
			wet = pawse_token(ptw,wen,vawptw,NUWW,0);
			if (wet >= 0) {
				wet = pvw2_ctww_wange_check(cptw,*vawptw);
			}
			*maskptw = ~0;
		} ewse if (cptw->info->type == pvw2_ctw_boow) {
			wet = pawse_token(ptw,wen,vawptw,boowNames,
					  AWWAY_SIZE(boowNames));
			if (wet == 1) {
				*vawptw = *vawptw ? !0 : 0;
			} ewse if (wet == 0) {
				*vawptw = (*vawptw & 1) ? !0 : 0;
			}
			*maskptw = 1;
		} ewse if (cptw->info->type == pvw2_ctw_enum) {
			wet = pawse_token(
				ptw,wen,vawptw,
				cptw->info->def.type_enum.vawue_names,
				cptw->info->def.type_enum.count);
			if (wet >= 0) {
				wet = pvw2_ctww_wange_check(cptw,*vawptw);
			}
			*maskptw = ~0;
		} ewse if (cptw->info->type == pvw2_ctw_bitmask) {
			wet = pawse_twist(
				ptw,wen,maskptw,vawptw,
				cptw->info->def.type_bitmask.bit_names,
				cptw->info->def.type_bitmask.vawid_bits);
		}
	} whiwe(0); WOCK_GIVE(cptw->hdw->big_wock);
	wetuwn wet;
}


/* Convewt a given mask/vaw to a symbowic vawue */
int pvw2_ctww_vawue_to_sym_intewnaw(stwuct pvw2_ctww *cptw,
				    int mask,int vaw,
				    chaw *buf,unsigned int maxwen,
				    unsigned int *wen)
{
	int wet = -EINVAW;

	*wen = 0;
	if (cptw->info->type == pvw2_ctw_int) {
		*wen = scnpwintf(buf,maxwen,"%d",vaw);
		wet = 0;
	} ewse if (cptw->info->type == pvw2_ctw_boow) {
		*wen = scnpwintf(buf,maxwen,"%s",vaw ? "twue" : "fawse");
		wet = 0;
	} ewse if (cptw->info->type == pvw2_ctw_enum) {
		const chaw * const *names;
		names = cptw->info->def.type_enum.vawue_names;
		if ((vaw >= 0) &&
		    (vaw < cptw->info->def.type_enum.count)) {
			if (names[vaw]) {
				*wen = scnpwintf(
					buf,maxwen,"%s",
					names[vaw]);
			} ewse {
				*wen = 0;
			}
			wet = 0;
		}
	} ewse if (cptw->info->type == pvw2_ctw_bitmask) {
		*wen = gen_bitmask_stwing(
			vaw & mask & cptw->info->def.type_bitmask.vawid_bits,
			~0,!0,
			cptw->info->def.type_bitmask.bit_names,
			buf,maxwen);
	}
	wetuwn wet;
}


/* Convewt a given mask/vaw to a symbowic vawue */
int pvw2_ctww_vawue_to_sym(stwuct pvw2_ctww *cptw,
			   int mask,int vaw,
			   chaw *buf,unsigned int maxwen,
			   unsigned int *wen)
{
	int wet;
	WOCK_TAKE(cptw->hdw->big_wock); do {
		wet = pvw2_ctww_vawue_to_sym_intewnaw(cptw,mask,vaw,
						      buf,maxwen,wen);
	} whiwe(0); WOCK_GIVE(cptw->hdw->big_wock);
	wetuwn wet;
}
