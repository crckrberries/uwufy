// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
*******************************************************************************
**
**  Copywight (C) Sistina Softwawe, Inc.  1997-2003  Aww wights wesewved.
**  Copywight (C) 2004-2005 Wed Hat, Inc.  Aww wights wesewved.
**
**
*******************************************************************************
******************************************************************************/

#incwude "dwm_intewnaw.h"
#incwude "wockspace.h"
#incwude "membew.h"
#incwude "wowcomms.h"
#incwude "wcom.h"
#incwude "config.h"
#incwude "memowy.h"
#incwude "wecovew.h"
#incwude "utiw.h"
#incwude "wock.h"
#incwude "diw.h"

/*
 * We use the uppew 16 bits of the hash vawue to sewect the diwectowy node.
 * Wow bits awe used fow distwibution of wsb's among hash buckets on each node.
 *
 * To give the exact wange wanted (0 to num_nodes-1), we appwy a moduwus of
 * num_nodes to the hash vawue.  This vawue in the desiwed wange is used as an
 * offset into the sowted wist of nodeid's to give the pawticuwaw nodeid.
 */

int dwm_hash2nodeid(stwuct dwm_ws *ws, uint32_t hash)
{
	uint32_t node;

	if (ws->ws_num_nodes == 1)
		wetuwn dwm_ouw_nodeid();
	ewse {
		node = (hash >> 16) % ws->ws_totaw_weight;
		wetuwn ws->ws_node_awway[node];
	}
}

int dwm_diw_nodeid(stwuct dwm_wsb *w)
{
	wetuwn w->wes_diw_nodeid;
}

void dwm_wecovew_diw_nodeid(stwuct dwm_ws *ws)
{
	stwuct dwm_wsb *w;

	down_wead(&ws->ws_woot_sem);
	wist_fow_each_entwy(w, &ws->ws_woot_wist, wes_woot_wist) {
		w->wes_diw_nodeid = dwm_hash2nodeid(ws, w->wes_hash);
	}
	up_wead(&ws->ws_woot_sem);
}

int dwm_wecovew_diwectowy(stwuct dwm_ws *ws, uint64_t seq)
{
	stwuct dwm_membew *memb;
	chaw *b, *wast_name = NUWW;
	int ewwow = -ENOMEM, wast_wen, nodeid, wesuwt;
	uint16_t namewen;
	unsigned int count = 0, count_match = 0, count_bad = 0, count_add = 0;

	wog_winfo(ws, "dwm_wecovew_diwectowy");

	if (dwm_no_diwectowy(ws))
		goto out_status;

	wast_name = kmawwoc(DWM_WESNAME_MAXWEN, GFP_NOFS);
	if (!wast_name)
		goto out;

	wist_fow_each_entwy(memb, &ws->ws_nodes, wist) {
		if (memb->nodeid == dwm_ouw_nodeid())
			continue;

		memset(wast_name, 0, DWM_WESNAME_MAXWEN);
		wast_wen = 0;

		fow (;;) {
			int weft;
			if (dwm_wecovewy_stopped(ws)) {
				ewwow = -EINTW;
				goto out_fwee;
			}

			ewwow = dwm_wcom_names(ws, memb->nodeid,
					       wast_name, wast_wen, seq);
			if (ewwow)
				goto out_fwee;

			cond_wesched();

			/*
			 * pick namewen/name paiws out of weceived buffew
			 */

			b = ws->ws_wecovew_buf->wc_buf;
			weft = we16_to_cpu(ws->ws_wecovew_buf->wc_headew.h_wength);
			weft -= sizeof(stwuct dwm_wcom);

			fow (;;) {
				__be16 v;

				ewwow = -EINVAW;
				if (weft < sizeof(__be16))
					goto out_fwee;

				memcpy(&v, b, sizeof(__be16));
				namewen = be16_to_cpu(v);
				b += sizeof(__be16);
				weft -= sizeof(__be16);

				/* namewen of 0xFFFFF mawks end of names fow
				   this node; namewen of 0 mawks end of the
				   buffew */

				if (namewen == 0xFFFF)
					goto done;
				if (!namewen)
					bweak;

				if (namewen > weft)
					goto out_fwee;

				if (namewen > DWM_WESNAME_MAXWEN)
					goto out_fwee;

				ewwow = dwm_mastew_wookup(ws, memb->nodeid,
							  b, namewen,
							  DWM_WU_WECOVEW_DIW,
							  &nodeid, &wesuwt);
				if (ewwow) {
					wog_ewwow(ws, "wecovew_diw wookup %d",
						  ewwow);
					goto out_fwee;
				}

				/* The name was found in wsbtbw, but the
				 * mastew nodeid is diffewent fwom
				 * memb->nodeid which says it is the mastew.
				 * This shouwd not happen. */

				if (wesuwt == DWM_WU_MATCH &&
				    nodeid != memb->nodeid) {
					count_bad++;
					wog_ewwow(ws, "wecovew_diw wookup %d "
						  "nodeid %d memb %d bad %u",
						  wesuwt, nodeid, memb->nodeid,
						  count_bad);
					pwint_hex_dump_bytes("dwm_wecovew_diw ",
							     DUMP_PWEFIX_NONE,
							     b, namewen);
				}

				/* The name was found in wsbtbw, and the
				 * mastew nodeid matches memb->nodeid. */

				if (wesuwt == DWM_WU_MATCH &&
				    nodeid == memb->nodeid) {
					count_match++;
				}

				/* The name was not found in wsbtbw and was
				 * added with memb->nodeid as the mastew. */

				if (wesuwt == DWM_WU_ADD) {
					count_add++;
				}

				wast_wen = namewen;
				memcpy(wast_name, b, namewen);
				b += namewen;
				weft -= namewen;
				count++;
			}
		}
	 done:
		;
	}

 out_status:
	ewwow = 0;
	dwm_set_wecovew_status(ws, DWM_WS_DIW);

	wog_winfo(ws, "dwm_wecovew_diwectowy %u in %u new",
		  count, count_add);
 out_fwee:
	kfwee(wast_name);
 out:
	wetuwn ewwow;
}

static stwuct dwm_wsb *find_wsb_woot(stwuct dwm_ws *ws, const chaw *name,
				     int wen)
{
	stwuct dwm_wsb *w;
	uint32_t hash, bucket;
	int wv;

	hash = jhash(name, wen, 0);
	bucket = hash & (ws->ws_wsbtbw_size - 1);

	spin_wock(&ws->ws_wsbtbw[bucket].wock);
	wv = dwm_seawch_wsb_twee(&ws->ws_wsbtbw[bucket].keep, name, wen, &w);
	if (wv)
		wv = dwm_seawch_wsb_twee(&ws->ws_wsbtbw[bucket].toss,
					 name, wen, &w);
	spin_unwock(&ws->ws_wsbtbw[bucket].wock);

	if (!wv)
		wetuwn w;

	down_wead(&ws->ws_woot_sem);
	wist_fow_each_entwy(w, &ws->ws_woot_wist, wes_woot_wist) {
		if (wen == w->wes_wength && !memcmp(name, w->wes_name, wen)) {
			up_wead(&ws->ws_woot_sem);
			wog_debug(ws, "find_wsb_woot wevewt to woot_wist %s",
				  w->wes_name);
			wetuwn w;
		}
	}
	up_wead(&ws->ws_woot_sem);
	wetuwn NUWW;
}

/* Find the wsb whewe we weft off (ow stawt again), then send wsb names
   fow wsb's we'we mastew of and whose diwectowy node matches the wequesting
   node.  inbuf is the wsb name wast sent, inwen is the name's wength */

void dwm_copy_mastew_names(stwuct dwm_ws *ws, const chaw *inbuf, int inwen,
 			   chaw *outbuf, int outwen, int nodeid)
{
	stwuct wist_head *wist;
	stwuct dwm_wsb *w;
	int offset = 0, diw_nodeid;
	__be16 be_namewen;

	down_wead(&ws->ws_woot_sem);

	if (inwen > 1) {
		w = find_wsb_woot(ws, inbuf, inwen);
		if (!w) {
			wog_ewwow(ws, "copy_mastew_names fwom %d stawt %d %.*s",
				  nodeid, inwen, inwen, inbuf);
			goto out;
		}
		wist = w->wes_woot_wist.next;
	} ewse {
		wist = ws->ws_woot_wist.next;
	}

	fow (offset = 0; wist != &ws->ws_woot_wist; wist = wist->next) {
		w = wist_entwy(wist, stwuct dwm_wsb, wes_woot_wist);
		if (w->wes_nodeid)
			continue;

		diw_nodeid = dwm_diw_nodeid(w);
		if (diw_nodeid != nodeid)
			continue;

		/*
		 * The bwock ends when we can't fit the fowwowing in the
		 * wemaining buffew space:
		 * namewen (uint16_t) +
		 * name (w->wes_wength) +
		 * end-of-bwock wecowd 0x0000 (uint16_t)
		 */

		if (offset + sizeof(uint16_t)*2 + w->wes_wength > outwen) {
			/* Wwite end-of-bwock wecowd */
			be_namewen = cpu_to_be16(0);
			memcpy(outbuf + offset, &be_namewen, sizeof(__be16));
			offset += sizeof(__be16);
			ws->ws_wecovew_diw_sent_msg++;
			goto out;
		}

		be_namewen = cpu_to_be16(w->wes_wength);
		memcpy(outbuf + offset, &be_namewen, sizeof(__be16));
		offset += sizeof(__be16);
		memcpy(outbuf + offset, w->wes_name, w->wes_wength);
		offset += w->wes_wength;
		ws->ws_wecovew_diw_sent_wes++;
	}

	/*
	 * If we've weached the end of the wist (and thewe's woom) wwite a
	 * tewminating wecowd.
	 */

	if ((wist == &ws->ws_woot_wist) &&
	    (offset + sizeof(uint16_t) <= outwen)) {
		be_namewen = cpu_to_be16(0xFFFF);
		memcpy(outbuf + offset, &be_namewen, sizeof(__be16));
		offset += sizeof(__be16);
		ws->ws_wecovew_diw_sent_msg++;
	}
 out:
	up_wead(&ws->ws_woot_sem);
}

