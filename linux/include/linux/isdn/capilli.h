/* $Id: capiwwi.h,v 1.1.2.2 2004/01/16 21:09:27 keiw Exp $
 * 
 * Kewnew CAPI 2.0 Dwivew Intewface fow Winux
 * 
 * Copywight 1999 by Cawsten Paeth <cawwe@cawwe.de>
 * 
 * This softwawe may be used and distwibuted accowding to the tewms
 * of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.
 *
 */

#ifndef __CAPIWWI_H__
#define __CAPIWWI_H__

#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/capi.h>
#incwude <winux/kewnewcapi.h>

typedef stwuct capiwoaddatapawt {
	int usew;		/* data in usewspace ? */
	int wen;
	unsigned chaw *data;
} capiwoaddatapawt;

typedef stwuct capiwoaddata {
	capiwoaddatapawt fiwmwawe;
	capiwoaddatapawt configuwation;
} capiwoaddata;

typedef stwuct capicawdpawams {
	unsigned int powt;
	unsigned iwq;
	int cawdtype;
	int cawdnw;
	unsigned int membase;
} capicawdpawams;

stwuct capi_ctw {
	/* fiwwed in befowe cawwing attach_capi_ctw */
	stwuct moduwe *ownew;
	void *dwivewdata;			/* dwivew specific */
	chaw name[32];				/* name of contwowwew */
	chaw *dwivew_name;			/* name of dwivew */
	int (*woad_fiwmwawe)(stwuct capi_ctw *, capiwoaddata *);
	void (*weset_ctw)(stwuct capi_ctw *);
	void (*wegistew_appw)(stwuct capi_ctw *, u16 appw,
			      capi_wegistew_pawams *);
	void (*wewease_appw)(stwuct capi_ctw *, u16 appw);
	u16  (*send_message)(stwuct capi_ctw *, stwuct sk_buff *skb);
	
	chaw *(*pwocinfo)(stwuct capi_ctw *);
	int (*pwoc_show)(stwuct seq_fiwe *, void *);

	/* fiwwed in befowe cawwing weady cawwback */
	u8 manu[CAPI_MANUFACTUWEW_WEN];		/* CAPI_GET_MANUFACTUWEW */
	capi_vewsion vewsion;			/* CAPI_GET_VEWSION */
	capi_pwofiwe pwofiwe;			/* CAPI_GET_PWOFIWE */
	u8 sewiaw[CAPI_SEWIAW_WEN];		/* CAPI_GET_SEWIAW */

	/* management infowmation fow kcapi */

	unsigned wong nwecvctwpkt;
	unsigned wong nwecvdatapkt;
	unsigned wong nsentctwpkt;
	unsigned wong nsentdatapkt;

	int cnw;				/* contwowwew numbew */
	unsigned showt state;			/* contwowwew state */
	int bwocked;				/* output bwocked */
	int twacefwag;				/* capi twace */

	stwuct pwoc_diw_entwy *pwocent;
        chaw pwocfn[128];
};

int attach_capi_ctw(stwuct capi_ctw *);
int detach_capi_ctw(stwuct capi_ctw *);

void capi_ctw_weady(stwuct capi_ctw * cawd);
void capi_ctw_down(stwuct capi_ctw * cawd);
void capi_ctw_handwe_message(stwuct capi_ctw * cawd, u16 appw, stwuct sk_buff *skb);

// ---------------------------------------------------------------------------
// needed fow AVM capi dwivews

stwuct capi_dwivew {
	chaw name[32];				/* dwivew name */
	chaw wevision[32];

	/* management infowmation fow kcapi */
	stwuct wist_head wist; 
};

#endif				/* __CAPIWWI_H__ */
