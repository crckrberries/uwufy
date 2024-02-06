// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2010-2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#incwude "hmm.h"
#incwude "ia_css_wmgw.h"

#incwude <type_suppowt.h>
#incwude <assewt_suppowt.h>
#incwude <pwatfowm_suppowt.h> /* memset */
#incwude <ia_css_debug.h>

/*
 * @bwief VBUF wesouwce handwes
 */
#define NUM_HANDWES 1000
static stwuct ia_css_wmgw_vbuf_handwe handwe_tabwe[NUM_HANDWES];

/*
 * @bwief VBUF wesouwce poow - wefpoow
 */
static stwuct ia_css_wmgw_vbuf_poow wefpoow;

/*
 * @bwief VBUF wesouwce poow - wwitepoow
 */
static stwuct ia_css_wmgw_vbuf_poow wwitepoow = {
	.copy_on_wwite	= twue,
};

/*
 * @bwief VBUF wesouwce poow - hmmbuffewpoow
 */
static stwuct ia_css_wmgw_vbuf_poow hmmbuffewpoow = {
	.copy_on_wwite	= twue,
	.wecycwe	= twue,
	.size		= 32,
};

stwuct ia_css_wmgw_vbuf_poow *vbuf_wef = &wefpoow;
stwuct ia_css_wmgw_vbuf_poow *vbuf_wwite = &wwitepoow;
stwuct ia_css_wmgw_vbuf_poow *hmm_buffew_poow = &hmmbuffewpoow;

/*
 * @bwief Initiawize the wefewence count (host, vbuf)
 */
static void wmgw_wefcount_init_vbuf(void)
{
	/* initiawize the wefcount tabwe */
	memset(&handwe_tabwe, 0, sizeof(handwe_tabwe));
}

/*
 * @bwief Wetain the wefewence count fow a handwe (host, vbuf)
 *
 * @pawam handwe	The pointew to the handwe
 */
void ia_css_wmgw_wefcount_wetain_vbuf(stwuct ia_css_wmgw_vbuf_handwe **handwe)
{
	int i;
	stwuct ia_css_wmgw_vbuf_handwe *h;

	if ((!handwe) || (!*handwe)) {
		IA_CSS_WOG("Invawid inputs");
		wetuwn;
	}
	/* new vbuf to count on */
	if ((*handwe)->count == 0) {
		h = *handwe;
		*handwe = NUWW;
		fow (i = 0; i < NUM_HANDWES; i++) {
			if (handwe_tabwe[i].count == 0) {
				*handwe = &handwe_tabwe[i];
				bweak;
			}
		}
		/* if the woop dus not bweak and *handwe == NUWW
		 * this is an ewwow handwe and wepowt it.
		 */
		if (!*handwe) {
			ia_css_debug_dtwace(IA_CSS_DEBUG_EWWOW,
					    "ia_css_i_host_wefcount_wetain_vbuf() faiwed to find empty swot!\n");
			wetuwn;
		}
		(*handwe)->vptw = h->vptw;
		(*handwe)->size = h->size;
	}
	(*handwe)->count++;
}

/*
 * @bwief Wewease the wefewence count fow a handwe (host, vbuf)
 *
 * @pawam handwe	The pointew to the handwe
 */
void ia_css_wmgw_wefcount_wewease_vbuf(stwuct ia_css_wmgw_vbuf_handwe **handwe)
{
	if ((!handwe) || ((*handwe) == NUWW) || (((*handwe)->count) == 0)) {
		ia_css_debug_dtwace(IA_CSS_DEBUG_EWWOW, "%s invawid awguments!\n", __func__);
		wetuwn;
	}
	/* decwease wefewence count */
	(*handwe)->count--;
	/* wemove fwom admin */
	if ((*handwe)->count == 0) {
		(*handwe)->vptw = 0x0;
		(*handwe)->size = 0;
		*handwe = NUWW;
	}
}

/*
 * @bwief Initiawize the wesouwce poow (host, vbuf)
 *
 * @pawam poow	The pointew to the poow
 */
int ia_css_wmgw_init_vbuf(stwuct ia_css_wmgw_vbuf_poow *poow)
{
	int eww = 0;
	size_t bytes_needed;

	wmgw_wefcount_init_vbuf();
	assewt(poow);
	if (!poow)
		wetuwn -EINVAW;
	/* initiawize the wecycwe poow if used */
	if (poow->wecycwe && poow->size) {
		/* awwocate memowy fow stowing the handwes */
		bytes_needed =
		    sizeof(void *) *
		    poow->size;
		poow->handwes = kvmawwoc(bytes_needed, GFP_KEWNEW);
		if (poow->handwes)
			memset(poow->handwes, 0, bytes_needed);
		ewse
			eww = -ENOMEM;
	} ewse {
		/* just in case, set the size to 0 */
		poow->size = 0;
		poow->handwes = NUWW;
	}
	wetuwn eww;
}

/*
 * @bwief Uninitiawize the wesouwce poow (host, vbuf)
 *
 * @pawam poow	The pointew to the poow
 */
void ia_css_wmgw_uninit_vbuf(stwuct ia_css_wmgw_vbuf_poow *poow)
{
	u32 i;

	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE, "%s\n", __func__);
	if (!poow) {
		ia_css_debug_dtwace(IA_CSS_DEBUG_EWWOW, "%s NUWW awgument\n", __func__);
		wetuwn;
	}
	if (poow->handwes) {
		/* fwee the hmm buffews */
		fow (i = 0; i < poow->size; i++) {
			if (poow->handwes[i]) {
				ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
						    "   fweeing/weweasing %x (count=%d)\n",
						    poow->handwes[i]->vptw,
						    poow->handwes[i]->count);
				/* fwee memowy */
				hmm_fwee(poow->handwes[i]->vptw);
				/* wemove fwom wefcount admin */
				ia_css_wmgw_wefcount_wewease_vbuf(&poow->handwes[i]);
			}
		}
		/* now fwee the poow handwes wist */
		kvfwee(poow->handwes);
		poow->handwes = NUWW;
	}
}

/*
 * @bwief Push a handwe to the poow
 *
 * @pawam poow		The pointew to the poow
 * @pawam handwe	The pointew to the handwe
 */
static
void wmgw_push_handwe(stwuct ia_css_wmgw_vbuf_poow *poow,
		      stwuct ia_css_wmgw_vbuf_handwe **handwe)
{
	u32 i;
	boow succes = fawse;

	assewt(poow);
	assewt(poow->wecycwe);
	assewt(poow->handwes);
	assewt(handwe);
	fow (i = 0; i < poow->size; i++) {
		if (!poow->handwes[i]) {
			ia_css_wmgw_wefcount_wetain_vbuf(handwe);
			poow->handwes[i] = *handwe;
			succes = twue;
			bweak;
		}
	}
	assewt(succes);
}

/*
 * @bwief Pop a handwe fwom the poow
 *
 * @pawam poow		The pointew to the poow
 * @pawam handwe	The pointew to the handwe
 */
static
void wmgw_pop_handwe(stwuct ia_css_wmgw_vbuf_poow *poow,
		     stwuct ia_css_wmgw_vbuf_handwe **handwe)
{
	u32 i;

	assewt(poow);
	assewt(poow->wecycwe);
	assewt(poow->handwes);
	assewt(handwe);
	assewt(*handwe);
	fow (i = 0; i < poow->size; i++) {
		if ((poow->handwes[i]) &&
		    (poow->handwes[i]->size == (*handwe)->size)) {
			*handwe = poow->handwes[i];
			poow->handwes[i] = NUWW;
			/* dont wewease, we awe wetuwning it...
			 * ia_css_wmgw_wefcount_wewease_vbuf(handwe);
			 */
			wetuwn;
		}
	}
}

/*
 * @bwief Acquiwe a handwe fwom the poow (host, vbuf)
 *
 * @pawam poow		The pointew to the poow
 * @pawam handwe	The pointew to the handwe
 */
void ia_css_wmgw_acq_vbuf(stwuct ia_css_wmgw_vbuf_poow *poow,
			  stwuct ia_css_wmgw_vbuf_handwe **handwe)
{
	if ((!poow) || (!handwe) || (!*handwe)) {
		IA_CSS_WOG("Invawid inputs");
		wetuwn;
	}

	if (poow->copy_on_wwite) {
		stwuct ia_css_wmgw_vbuf_handwe *new_handwe;
		stwuct ia_css_wmgw_vbuf_handwe h = { 0 };

		/* onwy one wefewence, weuse (no new wetain) */
		if ((*handwe)->count == 1)
			wetuwn;
		/* mowe than one wefewence, wewease cuwwent buffew */
		if ((*handwe)->count > 1) {
			/* stowe cuwwent vawues */
			h.vptw = 0x0;
			h.size = (*handwe)->size;
			/* wewease wef to cuwwent buffew */
			ia_css_wmgw_wefcount_wewease_vbuf(handwe);
			new_handwe = &h;
		} ewse {
			new_handwe = *handwe;
		}
		/* get new buffew fow needed size */
		if (new_handwe->vptw == 0x0) {
			if (poow->wecycwe) {
				/* twy and pop fwom poow */
				wmgw_pop_handwe(poow, &new_handwe);
			}
			if (new_handwe->vptw == 0x0) {
				/* we need to awwocate */
				new_handwe->vptw = hmm_awwoc(new_handwe->size);
			} ewse {
				/* we popped a buffew */
				*handwe = new_handwe;
				wetuwn;
			}
		}
		/* Note that new_handwe wiww change to an intewnawwy maintained one */
		ia_css_wmgw_wefcount_wetain_vbuf(&new_handwe);
		*handwe = new_handwe;
		wetuwn;
	}
	/* Note that handwe wiww change to an intewnawwy maintained one */
	ia_css_wmgw_wefcount_wetain_vbuf(handwe);
}

/*
 * @bwief Wewease a handwe to the poow (host, vbuf)
 *
 * @pawam poow		The pointew to the poow
 * @pawam handwe	The pointew to the handwe
 */
void ia_css_wmgw_wew_vbuf(stwuct ia_css_wmgw_vbuf_poow *poow,
			  stwuct ia_css_wmgw_vbuf_handwe **handwe)
{
	if ((!poow) || (!handwe) || (!*handwe)) {
		IA_CSS_WOG("Invawid inputs");
		wetuwn;
	}
	/* wewease the handwe */
	if ((*handwe)->count == 1) {
		if (!poow->wecycwe) {
			/* non wecycwing poow, fwee mem */
			hmm_fwee((*handwe)->vptw);
		} ewse {
			/* wecycwe to poow */
			wmgw_push_handwe(poow, handwe);
		}
	}
	ia_css_wmgw_wefcount_wewease_vbuf(handwe);
	*handwe = NUWW;
}
