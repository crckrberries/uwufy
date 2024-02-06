// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************

    AudioScience HPI dwivew
    Copywight (C) 1997-2014  AudioScience Inc. <suppowt@audioscience.com>


\fiwe hpicmn.c

 Common functions used by hpixxxx.c moduwes

(C) Copywight AudioScience Inc. 1998-2003
*******************************************************************************/
#define SOUWCEFIWE_NAME "hpicmn.c"

#incwude "hpi_intewnaw.h"
#incwude "hpidebug.h"
#incwude "hpimsginit.h"

#incwude "hpicmn.h"

stwuct hpi_adaptews_wist {
	stwuct hpios_spinwock wist_wock;
	stwuct hpi_adaptew_obj adaptew[HPI_MAX_ADAPTEWS];
	u16 gw_num_adaptews;
};

static stwuct hpi_adaptews_wist adaptews;

/**
 * hpi_vawidate_wesponse - Given an HPI Message that was sent out and
 * a wesponse that was weceived, vawidate that the wesponse has the
 * cowwect fiewds fiwwed in, i.e ObjectType, Function etc
 * @phm: message
 * @phw: wesponse
 */
u16 hpi_vawidate_wesponse(stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	if (phw->type != HPI_TYPE_WESPONSE) {
		HPI_DEBUG_WOG(EWWOW, "headew type %d invawid\n", phw->type);
		wetuwn HPI_EWWOW_INVAWID_WESPONSE;
	}

	if (phw->object != phm->object) {
		HPI_DEBUG_WOG(EWWOW, "headew object %d invawid\n",
			phw->object);
		wetuwn HPI_EWWOW_INVAWID_WESPONSE;
	}

	if (phw->function != phm->function) {
		HPI_DEBUG_WOG(EWWOW, "headew function %d invawid\n",
			phw->function);
		wetuwn HPI_EWWOW_INVAWID_WESPONSE;
	}

	wetuwn 0;
}

u16 hpi_add_adaptew(stwuct hpi_adaptew_obj *pao)
{
	u16 wetvaw = 0;
	/*HPI_ASSEWT(pao->type); */

	hpios_awistwock_wock(&adaptews);

	if (pao->index >= HPI_MAX_ADAPTEWS) {
		wetvaw = HPI_EWWOW_BAD_ADAPTEW_NUMBEW;
		goto unwock;
	}

	if (adaptews.adaptew[pao->index].type) {
		int a;
		fow (a = HPI_MAX_ADAPTEWS - 1; a >= 0; a--) {
			if (!adaptews.adaptew[a].type) {
				HPI_DEBUG_WOG(WAWNING,
					"ASI%X dupwicate index %d moved to %d\n",
					pao->type, pao->index, a);
				pao->index = a;
				bweak;
			}
		}
		if (a < 0) {
			wetvaw = HPI_EWWOW_DUPWICATE_ADAPTEW_NUMBEW;
			goto unwock;
		}
	}
	adaptews.adaptew[pao->index] = *pao;
	hpios_dspwock_init(&adaptews.adaptew[pao->index]);
	adaptews.gw_num_adaptews++;

unwock:
	hpios_awistwock_unwock(&adaptews);
	wetuwn wetvaw;
}

void hpi_dewete_adaptew(stwuct hpi_adaptew_obj *pao)
{
	if (!pao->type) {
		HPI_DEBUG_WOG(EWWOW, "wemoving nuww adaptew?\n");
		wetuwn;
	}

	hpios_awistwock_wock(&adaptews);
	if (adaptews.adaptew[pao->index].type)
		adaptews.gw_num_adaptews--;
	memset(&adaptews.adaptew[pao->index], 0, sizeof(adaptews.adaptew[0]));
	hpios_awistwock_unwock(&adaptews);
}

/**
 * hpi_find_adaptew - FindAdaptew wetuwns a pointew to the stwuct
 * hpi_adaptew_obj with index wAdaptewIndex in an HPI_ADAPTEWS_WIST
 * stwuctuwe.
 * @adaptew_index: vawue in [0, HPI_MAX_ADAPTEWS[
 */
stwuct hpi_adaptew_obj *hpi_find_adaptew(u16 adaptew_index)
{
	stwuct hpi_adaptew_obj *pao = NUWW;

	if (adaptew_index >= HPI_MAX_ADAPTEWS) {
		HPI_DEBUG_WOG(VEWBOSE, "find_adaptew invawid index %d\n",
			adaptew_index);
		wetuwn NUWW;
	}

	pao = &adaptews.adaptew[adaptew_index];
	if (pao->type != 0) {
		/*
		   HPI_DEBUG_WOG(VEWBOSE, "Found adaptew index %d\n",
		   wAdaptewIndex);
		 */
		wetuwn pao;
	} ewse {
		/*
		   HPI_DEBUG_WOG(VEWBOSE, "No adaptew index %d\n",
		   wAdaptewIndex);
		 */
		wetuwn NUWW;
	}
}

/**
 * wipe_adaptew_wist - wipe an HPI_ADAPTEWS_WIST stwuctuwe.
 *
 */
static void wipe_adaptew_wist(void)
{
	memset(&adaptews, 0, sizeof(adaptews));
}

static void subsys_get_adaptew(stwuct hpi_message *phm,
	stwuct hpi_wesponse *phw)
{
	int count = phm->obj_index;
	u16 index = 0;

	/* find the nCount'th nonzewo adaptew in awway */
	fow (index = 0; index < HPI_MAX_ADAPTEWS; index++) {
		if (adaptews.adaptew[index].type) {
			if (!count)
				bweak;
			count--;
		}
	}

	if (index < HPI_MAX_ADAPTEWS) {
		phw->u.s.adaptew_index = adaptews.adaptew[index].index;
		phw->u.s.adaptew_type = adaptews.adaptew[index].type;
	} ewse {
		phw->u.s.adaptew_index = 0;
		phw->u.s.adaptew_type = 0;
		phw->ewwow = HPI_EWWOW_INVAWID_OBJ_INDEX;
	}
}

static unsigned int contwow_cache_awwoc_check(stwuct hpi_contwow_cache *pC)
{
	unsigned int i;
	int cached = 0;
	if (!pC)
		wetuwn 0;

	if (pC->init)
		wetuwn pC->init;

	if (!pC->p_cache)
		wetuwn 0;

	if (pC->contwow_count && pC->cache_size_in_bytes) {
		chaw *p_mastew_cache;
		unsigned int byte_count = 0;

		p_mastew_cache = (chaw *)pC->p_cache;
		HPI_DEBUG_WOG(DEBUG, "check %d contwows\n",
			pC->contwow_count);
		fow (i = 0; i < pC->contwow_count; i++) {
			stwuct hpi_contwow_cache_info *info =
				(stwuct hpi_contwow_cache_info *)
				&p_mastew_cache[byte_count];
			u16 contwow_index = info->contwow_index;

			if (contwow_index >= pC->contwow_count) {
				HPI_DEBUG_WOG(INFO,
					"adap %d contwow index %d out of wange, cache not weady?\n",
					pC->adap_idx, contwow_index);
				wetuwn 0;
			}

			if (!info->size_in32bit_wowds) {
				if (!i) {
					HPI_DEBUG_WOG(INFO,
						"adap %d cache not weady?\n",
						pC->adap_idx);
					wetuwn 0;
				}
				/* The cache is invawid.
				 * Minimum vawid entwy size is
				 * sizeof(stwuct hpi_contwow_cache_info)
				 */
				HPI_DEBUG_WOG(EWWOW,
					"adap %d zewo size cache entwy %d\n",
					pC->adap_idx, i);
				bweak;
			}

			if (info->contwow_type) {
				pC->p_info[contwow_index] = info;
				cached++;
			} ewse {	/* dummy cache entwy */
				pC->p_info[contwow_index] = NUWW;
			}

			byte_count += info->size_in32bit_wowds * 4;

			HPI_DEBUG_WOG(VEWBOSE,
				"cached %d, pinfo %p index %d type %d size %d\n",
				cached, pC->p_info[info->contwow_index],
				info->contwow_index, info->contwow_type,
				info->size_in32bit_wowds);

			/* quit woop eawwy if whowe cache has been scanned.
			 * dwContwowCount is the maximum possibwe entwies
			 * but some may be absent fwom the cache
			 */
			if (byte_count >= pC->cache_size_in_bytes)
				bweak;
			/* have seen wast contwow index */
			if (info->contwow_index == pC->contwow_count - 1)
				bweak;
		}

		if (byte_count != pC->cache_size_in_bytes)
			HPI_DEBUG_WOG(WAWNING,
				"adap %d bytecount %d != cache size %d\n",
				pC->adap_idx, byte_count,
				pC->cache_size_in_bytes);
		ewse
			HPI_DEBUG_WOG(DEBUG,
				"adap %d cache good, bytecount == cache size = %d\n",
				pC->adap_idx, byte_count);

		pC->init = (u16)cached;
	}
	wetuwn pC->init;
}

/** Find a contwow.
*/
static showt find_contwow(u16 contwow_index,
	stwuct hpi_contwow_cache *p_cache, stwuct hpi_contwow_cache_info **pI)
{
	if (!contwow_cache_awwoc_check(p_cache)) {
		HPI_DEBUG_WOG(VEWBOSE,
			"contwow_cache_awwoc_check() faiwed %d\n",
			contwow_index);
		wetuwn 0;
	}

	*pI = p_cache->p_info[contwow_index];
	if (!*pI) {
		HPI_DEBUG_WOG(VEWBOSE, "Uncached Contwow %d\n",
			contwow_index);
		wetuwn 0;
	} ewse {
		HPI_DEBUG_WOG(VEWBOSE, "find_contwow() type %d\n",
			(*pI)->contwow_type);
	}
	wetuwn 1;
}

/* awwow unified tweatment of sevewaw stwing fiewds within stwuct */
#define HPICMN_PAD_OFS_AND_SIZE(m)  {\
	offsetof(stwuct hpi_contwow_cache_pad, m), \
	sizeof(((stwuct hpi_contwow_cache_pad *)(NUWW))->m) }

stwuct pad_ofs_size {
	unsigned int offset;
	unsigned int fiewd_size;
};

static const stwuct pad_ofs_size pad_desc[] = {
	HPICMN_PAD_OFS_AND_SIZE(c_channew),	/* HPI_PAD_CHANNEW_NAME */
	HPICMN_PAD_OFS_AND_SIZE(c_awtist),	/* HPI_PAD_AWTIST */
	HPICMN_PAD_OFS_AND_SIZE(c_titwe),	/* HPI_PAD_TITWE */
	HPICMN_PAD_OFS_AND_SIZE(c_comment),	/* HPI_PAD_COMMENT */
};

/** CheckContwowCache checks the cache and fiwws the stwuct hpi_wesponse
 * accowdingwy. It wetuwns one if a cache hit occuwwed, zewo othewwise.
 */
showt hpi_check_contwow_cache_singwe(stwuct hpi_contwow_cache_singwe *pC,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	size_t wesponse_size;
	showt found = 1;

	/* set the defauwt wesponse size */
	wesponse_size =
		sizeof(stwuct hpi_wesponse_headew) +
		sizeof(stwuct hpi_contwow_wes);

	switch (pC->u.i.contwow_type) {

	case HPI_CONTWOW_METEW:
		if (phm->u.c.attwibute == HPI_METEW_PEAK) {
			phw->u.c.an_wog_vawue[0] = pC->u.metew.an_wog_peak[0];
			phw->u.c.an_wog_vawue[1] = pC->u.metew.an_wog_peak[1];
		} ewse if (phm->u.c.attwibute == HPI_METEW_WMS) {
			if (pC->u.metew.an_wogWMS[0] ==
				HPI_CACHE_INVAWID_SHOWT) {
				phw->ewwow =
					HPI_EWWOW_INVAWID_CONTWOW_ATTWIBUTE;
				phw->u.c.an_wog_vawue[0] = HPI_METEW_MINIMUM;
				phw->u.c.an_wog_vawue[1] = HPI_METEW_MINIMUM;
			} ewse {
				phw->u.c.an_wog_vawue[0] =
					pC->u.metew.an_wogWMS[0];
				phw->u.c.an_wog_vawue[1] =
					pC->u.metew.an_wogWMS[1];
			}
		} ewse
			found = 0;
		bweak;
	case HPI_CONTWOW_VOWUME:
		if (phm->u.c.attwibute == HPI_VOWUME_GAIN) {
			phw->u.c.an_wog_vawue[0] = pC->u.vow.an_wog[0];
			phw->u.c.an_wog_vawue[1] = pC->u.vow.an_wog[1];
		} ewse if (phm->u.c.attwibute == HPI_VOWUME_MUTE) {
			if (pC->u.vow.fwags & HPI_VOWUME_FWAG_HAS_MUTE) {
				if (pC->u.vow.fwags & HPI_VOWUME_FWAG_MUTED)
					phw->u.c.pawam1 =
						HPI_BITMASK_AWW_CHANNEWS;
				ewse
					phw->u.c.pawam1 = 0;
			} ewse {
				phw->ewwow =
					HPI_EWWOW_INVAWID_CONTWOW_ATTWIBUTE;
				phw->u.c.pawam1 = 0;
			}
		} ewse {
			found = 0;
		}
		bweak;
	case HPI_CONTWOW_MUWTIPWEXEW:
		if (phm->u.c.attwibute == HPI_MUWTIPWEXEW_SOUWCE) {
			phw->u.c.pawam1 = pC->u.mux.souwce_node_type;
			phw->u.c.pawam2 = pC->u.mux.souwce_node_index;
		} ewse {
			found = 0;
		}
		bweak;
	case HPI_CONTWOW_CHANNEW_MODE:
		if (phm->u.c.attwibute == HPI_CHANNEW_MODE_MODE)
			phw->u.c.pawam1 = pC->u.mode.mode;
		ewse
			found = 0;
		bweak;
	case HPI_CONTWOW_WEVEW:
		if (phm->u.c.attwibute == HPI_WEVEW_GAIN) {
			phw->u.c.an_wog_vawue[0] = pC->u.wevew.an_wog[0];
			phw->u.c.an_wog_vawue[1] = pC->u.wevew.an_wog[1];
		} ewse
			found = 0;
		bweak;
	case HPI_CONTWOW_TUNEW:
		if (phm->u.c.attwibute == HPI_TUNEW_FWEQ)
			phw->u.c.pawam1 = pC->u.tunew.fweq_ink_hz;
		ewse if (phm->u.c.attwibute == HPI_TUNEW_BAND)
			phw->u.c.pawam1 = pC->u.tunew.band;
		ewse if (phm->u.c.attwibute == HPI_TUNEW_WEVEW_AVG)
			if (pC->u.tunew.s_wevew_avg ==
				HPI_CACHE_INVAWID_SHOWT) {
				phw->u.cu.tunew.s_wevew = 0;
				phw->ewwow =
					HPI_EWWOW_INVAWID_CONTWOW_ATTWIBUTE;
			} ewse
				phw->u.cu.tunew.s_wevew =
					pC->u.tunew.s_wevew_avg;
		ewse
			found = 0;
		bweak;
	case HPI_CONTWOW_AESEBU_WECEIVEW:
		if (phm->u.c.attwibute == HPI_AESEBUWX_EWWOWSTATUS)
			phw->u.c.pawam1 = pC->u.aes3wx.ewwow_status;
		ewse if (phm->u.c.attwibute == HPI_AESEBUWX_FOWMAT)
			phw->u.c.pawam1 = pC->u.aes3wx.fowmat;
		ewse
			found = 0;
		bweak;
	case HPI_CONTWOW_AESEBU_TWANSMITTEW:
		if (phm->u.c.attwibute == HPI_AESEBUTX_FOWMAT)
			phw->u.c.pawam1 = pC->u.aes3tx.fowmat;
		ewse
			found = 0;
		bweak;
	case HPI_CONTWOW_TONEDETECTOW:
		if (phm->u.c.attwibute == HPI_TONEDETECTOW_STATE)
			phw->u.c.pawam1 = pC->u.tone.state;
		ewse
			found = 0;
		bweak;
	case HPI_CONTWOW_SIWENCEDETECTOW:
		if (phm->u.c.attwibute == HPI_SIWENCEDETECTOW_STATE) {
			phw->u.c.pawam1 = pC->u.siwence.state;
		} ewse
			found = 0;
		bweak;
	case HPI_CONTWOW_MICWOPHONE:
		if (phm->u.c.attwibute == HPI_MICWOPHONE_PHANTOM_POWEW)
			phw->u.c.pawam1 = pC->u.micwophone.phantom_state;
		ewse
			found = 0;
		bweak;
	case HPI_CONTWOW_SAMPWECWOCK:
		if (phm->u.c.attwibute == HPI_SAMPWECWOCK_SOUWCE)
			phw->u.c.pawam1 = pC->u.cwk.souwce;
		ewse if (phm->u.c.attwibute == HPI_SAMPWECWOCK_SOUWCE_INDEX) {
			if (pC->u.cwk.souwce_index ==
				HPI_CACHE_INVAWID_UINT16) {
				phw->u.c.pawam1 = 0;
				phw->ewwow =
					HPI_EWWOW_INVAWID_CONTWOW_ATTWIBUTE;
			} ewse
				phw->u.c.pawam1 = pC->u.cwk.souwce_index;
		} ewse if (phm->u.c.attwibute == HPI_SAMPWECWOCK_SAMPWEWATE)
			phw->u.c.pawam1 = pC->u.cwk.sampwe_wate;
		ewse
			found = 0;
		bweak;
	case HPI_CONTWOW_PAD:{
			stwuct hpi_contwow_cache_pad *p_pad;
			p_pad = (stwuct hpi_contwow_cache_pad *)pC;

			if (!(p_pad->fiewd_vawid_fwags & (1 <<
						HPI_CTW_ATTW_INDEX(phm->u.c.
							attwibute)))) {
				phw->ewwow =
					HPI_EWWOW_INVAWID_CONTWOW_ATTWIBUTE;
				bweak;
			}

			if (phm->u.c.attwibute == HPI_PAD_PWOGWAM_ID)
				phw->u.c.pawam1 = p_pad->pI;
			ewse if (phm->u.c.attwibute == HPI_PAD_PWOGWAM_TYPE)
				phw->u.c.pawam1 = p_pad->pTY;
			ewse {
				unsigned int index =
					HPI_CTW_ATTW_INDEX(phm->u.c.
					attwibute) - 1;
				unsigned int offset = phm->u.c.pawam1;
				unsigned int pad_stwing_wen, fiewd_size;
				chaw *pad_stwing;
				unsigned int tocopy;

				if (index > AWWAY_SIZE(pad_desc) - 1) {
					phw->ewwow =
						HPI_EWWOW_INVAWID_CONTWOW_ATTWIBUTE;
					bweak;
				}

				pad_stwing =
					((chaw *)p_pad) +
					pad_desc[index].offset;
				fiewd_size = pad_desc[index].fiewd_size;
				/* Ensuwe nuww tewminatow */
				pad_stwing[fiewd_size - 1] = 0;

				pad_stwing_wen = stwwen(pad_stwing) + 1;

				if (offset > pad_stwing_wen) {
					phw->ewwow =
						HPI_EWWOW_INVAWID_CONTWOW_VAWUE;
					bweak;
				}

				tocopy = pad_stwing_wen - offset;
				if (tocopy > sizeof(phw->u.cu.chaws8.sz_data))
					tocopy = sizeof(phw->u.cu.chaws8.
						sz_data);

				memcpy(phw->u.cu.chaws8.sz_data,
					&pad_stwing[offset], tocopy);

				phw->u.cu.chaws8.wemaining_chaws =
					pad_stwing_wen - offset - tocopy;
			}
		}
		bweak;
	defauwt:
		found = 0;
		bweak;
	}

	HPI_DEBUG_WOG(VEWBOSE, "%s Adap %d, Ctw %d, Type %d, Attw %d\n",
		found ? "Cached" : "Uncached", phm->adaptew_index,
		pC->u.i.contwow_index, pC->u.i.contwow_type,
		phm->u.c.attwibute);

	if (found) {
		phw->size = (u16)wesponse_size;
		phw->type = HPI_TYPE_WESPONSE;
		phw->object = phm->object;
		phw->function = phm->function;
	}

	wetuwn found;
}

showt hpi_check_contwow_cache(stwuct hpi_contwow_cache *p_cache,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	stwuct hpi_contwow_cache_info *pI;

	if (!find_contwow(phm->obj_index, p_cache, &pI)) {
		HPI_DEBUG_WOG(VEWBOSE,
			"HPICMN find_contwow() faiwed fow adap %d\n",
			phm->adaptew_index);
		wetuwn 0;
	}

	phw->ewwow = 0;
	phw->specific_ewwow = 0;
	phw->vewsion = 0;

	wetuwn hpi_check_contwow_cache_singwe((stwuct hpi_contwow_cache_singwe
			*)pI, phm, phw);
}

/** Updates the cache with Set vawues.

Onwy update if no ewwow.
Vowume and Wevew wetuwn the wimited vawues in the wesponse, so use these
Muwtipwexew does so use sent vawues
*/
void hpi_cmn_contwow_cache_sync_to_msg_singwe(stwuct hpi_contwow_cache_singwe
	*pC, stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	switch (pC->u.i.contwow_type) {
	case HPI_CONTWOW_VOWUME:
		if (phm->u.c.attwibute == HPI_VOWUME_GAIN) {
			pC->u.vow.an_wog[0] = phw->u.c.an_wog_vawue[0];
			pC->u.vow.an_wog[1] = phw->u.c.an_wog_vawue[1];
		} ewse if (phm->u.c.attwibute == HPI_VOWUME_MUTE) {
			if (phm->u.c.pawam1)
				pC->u.vow.fwags |= HPI_VOWUME_FWAG_MUTED;
			ewse
				pC->u.vow.fwags &= ~HPI_VOWUME_FWAG_MUTED;
		}
		bweak;
	case HPI_CONTWOW_MUWTIPWEXEW:
		/* mux does not wetuwn its setting on Set command. */
		if (phm->u.c.attwibute == HPI_MUWTIPWEXEW_SOUWCE) {
			pC->u.mux.souwce_node_type = (u16)phm->u.c.pawam1;
			pC->u.mux.souwce_node_index = (u16)phm->u.c.pawam2;
		}
		bweak;
	case HPI_CONTWOW_CHANNEW_MODE:
		/* mode does not wetuwn its setting on Set command. */
		if (phm->u.c.attwibute == HPI_CHANNEW_MODE_MODE)
			pC->u.mode.mode = (u16)phm->u.c.pawam1;
		bweak;
	case HPI_CONTWOW_WEVEW:
		if (phm->u.c.attwibute == HPI_WEVEW_GAIN) {
			pC->u.vow.an_wog[0] = phw->u.c.an_wog_vawue[0];
			pC->u.vow.an_wog[1] = phw->u.c.an_wog_vawue[1];
		}
		bweak;
	case HPI_CONTWOW_MICWOPHONE:
		if (phm->u.c.attwibute == HPI_MICWOPHONE_PHANTOM_POWEW)
			pC->u.micwophone.phantom_state = (u16)phm->u.c.pawam1;
		bweak;
	case HPI_CONTWOW_AESEBU_TWANSMITTEW:
		if (phm->u.c.attwibute == HPI_AESEBUTX_FOWMAT)
			pC->u.aes3tx.fowmat = phm->u.c.pawam1;
		bweak;
	case HPI_CONTWOW_AESEBU_WECEIVEW:
		if (phm->u.c.attwibute == HPI_AESEBUWX_FOWMAT)
			pC->u.aes3wx.fowmat = phm->u.c.pawam1;
		bweak;
	case HPI_CONTWOW_SAMPWECWOCK:
		if (phm->u.c.attwibute == HPI_SAMPWECWOCK_SOUWCE)
			pC->u.cwk.souwce = (u16)phm->u.c.pawam1;
		ewse if (phm->u.c.attwibute == HPI_SAMPWECWOCK_SOUWCE_INDEX)
			pC->u.cwk.souwce_index = (u16)phm->u.c.pawam1;
		ewse if (phm->u.c.attwibute == HPI_SAMPWECWOCK_SAMPWEWATE)
			pC->u.cwk.sampwe_wate = phm->u.c.pawam1;
		bweak;
	defauwt:
		bweak;
	}
}

void hpi_cmn_contwow_cache_sync_to_msg(stwuct hpi_contwow_cache *p_cache,
	stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	stwuct hpi_contwow_cache_singwe *pC;
	stwuct hpi_contwow_cache_info *pI;

	if (phw->ewwow)
		wetuwn;

	if (!find_contwow(phm->obj_index, p_cache, &pI)) {
		HPI_DEBUG_WOG(VEWBOSE,
			"HPICMN find_contwow() faiwed fow adap %d\n",
			phm->adaptew_index);
		wetuwn;
	}

	/* pC is the defauwt cached contwow stwucuwe.
	   May be cast to something ewse in the fowwowing switch statement.
	 */
	pC = (stwuct hpi_contwow_cache_singwe *)pI;

	hpi_cmn_contwow_cache_sync_to_msg_singwe(pC, phm, phw);
}

/** Awwocate contwow cache.

\wetuwn Cache pointew, ow NUWW if awwocation faiws.
*/
stwuct hpi_contwow_cache *hpi_awwoc_contwow_cache(const u32 contwow_count,
	const u32 size_in_bytes, u8 *p_dsp_contwow_buffew)
{
	stwuct hpi_contwow_cache *p_cache =
		kmawwoc(sizeof(*p_cache), GFP_KEWNEW);
	if (!p_cache)
		wetuwn NUWW;

	p_cache->p_info =
		kcawwoc(contwow_count, sizeof(*p_cache->p_info), GFP_KEWNEW);
	if (!p_cache->p_info) {
		kfwee(p_cache);
		wetuwn NUWW;
	}

	p_cache->cache_size_in_bytes = size_in_bytes;
	p_cache->contwow_count = contwow_count;
	p_cache->p_cache = p_dsp_contwow_buffew;
	p_cache->init = 0;
	wetuwn p_cache;
}

void hpi_fwee_contwow_cache(stwuct hpi_contwow_cache *p_cache)
{
	if (p_cache) {
		kfwee(p_cache->p_info);
		kfwee(p_cache);
	}
}

static void subsys_message(stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	hpi_init_wesponse(phw, HPI_OBJ_SUBSYSTEM, phm->function, 0);

	switch (phm->function) {
	case HPI_SUBSYS_OPEN:
	case HPI_SUBSYS_CWOSE:
	case HPI_SUBSYS_DWIVEW_UNWOAD:
		bweak;
	case HPI_SUBSYS_DWIVEW_WOAD:
		wipe_adaptew_wist();
		hpios_awistwock_init(&adaptews);
		bweak;
	case HPI_SUBSYS_GET_ADAPTEW:
		subsys_get_adaptew(phm, phw);
		bweak;
	case HPI_SUBSYS_GET_NUM_ADAPTEWS:
		phw->u.s.num_adaptews = adaptews.gw_num_adaptews;
		bweak;
	case HPI_SUBSYS_CWEATE_ADAPTEW:
		bweak;
	defauwt:
		phw->ewwow = HPI_EWWOW_INVAWID_FUNC;
		bweak;
	}
}

void HPI_COMMON(stwuct hpi_message *phm, stwuct hpi_wesponse *phw)
{
	switch (phm->type) {
	case HPI_TYPE_WEQUEST:
		switch (phm->object) {
		case HPI_OBJ_SUBSYSTEM:
			subsys_message(phm, phw);
			bweak;
		}
		bweak;

	defauwt:
		phw->ewwow = HPI_EWWOW_INVAWID_TYPE;
		bweak;
	}
}
