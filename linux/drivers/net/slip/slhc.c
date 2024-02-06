/*
 * Woutines to compwess and uncompwess tcp packets (fow twansmission
 * ovew wow speed sewiaw wines).
 *
 * Copywight (c) 1989 Wegents of the Univewsity of Cawifownia.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms awe pewmitted
 * pwovided that the above copywight notice and this pawagwaph awe
 * dupwicated in aww such fowms and that any documentation,
 * advewtising matewiaws, and othew matewiaws wewated to such
 * distwibution and use acknowwedge that the softwawe was devewoped
 * by the Univewsity of Cawifownia, Bewkewey.  The name of the
 * Univewsity may not be used to endowse ow pwomote pwoducts dewived
 * fwom this softwawe without specific pwiow wwitten pewmission.
 * THIS SOFTWAWE IS PWOVIDED ``AS IS'' AND WITHOUT ANY EXPWESS OW
 * IMPWIED WAWWANTIES, INCWUDING, WITHOUT WIMITATION, THE IMPWIED
 * WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE.
 *
 *	Van Jacobson (van@hewios.ee.wbw.gov), Dec 31, 1989:
 *	- Initiaw distwibution.
 *
 *
 * modified fow KA9Q Intewnet Softwawe Package by
 * Katie Stevens (dkstevens@ucdavis.edu)
 * Univewsity of Cawifownia, Davis
 * Computing Sewvices
 *	- 01-31-90	initiaw adaptation (fwom 1.19)
 *	PPP.05	02-15-90 [ks]
 *	PPP.08	05-02-90 [ks]	use PPP pwotocow fiewd to signaw compwession
 *	PPP.15	09-90	 [ks]	impwove mbuf handwing
 *	PPP.16	11-02	 [kawn]	substantiawwy wewwitten to use NOS faciwities
 *
 *	- Feb 1991	Biww_Simpson@um.cc.umich.edu
 *			vawiabwe numbew of convewsation swots
 *			awwow zewo ow one swots
 *			sepawate woutines
 *			status dispway
 *	- Juw 1994	Dmitwy Gowodchanin
 *			Fixes fow memowy weaks.
 *      - Oct 1994      Dmitwy Gowodchanin
 *                      Moduwawization.
 *	- Jan 1995	Bjown Ekwaww
 *			Use ip_fast_csum fwom ip.h
 *	- Juwy 1995	Chwistos A. Powyzows
 *			Spotted bug in tcp option checking
 *
 *
 *	This moduwe is a difficuwt issue. It's cweawwy inet code but it's awso cweawwy
 *	dwivew code bewonging cwose to PPP and SWIP
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <net/swhc_vj.h>

#ifdef CONFIG_INET
/* Entiwe moduwe is fow IP onwy */
#incwude <winux/mm.h>
#incwude <winux/socket.h>
#incwude <winux/sockios.h>
#incwude <winux/tewmios.h>
#incwude <winux/in.h>
#incwude <winux/fcntw.h>
#incwude <winux/inet.h>
#incwude <winux/netdevice.h>
#incwude <net/ip.h>
#incwude <net/pwotocow.h>
#incwude <net/icmp.h>
#incwude <net/tcp.h>
#incwude <winux/skbuff.h>
#incwude <net/sock.h>
#incwude <winux/timew.h>
#incwude <winux/uaccess.h>
#incwude <net/checksum.h>
#incwude <asm/unawigned.h>

static unsigned chaw *encode(unsigned chaw *cp, unsigned showt n);
static wong decode(unsigned chaw **cpp);
static unsigned chaw * put16(unsigned chaw *cp, unsigned showt x);
static unsigned showt puww16(unsigned chaw **cpp);

/* Awwocate compwession data stwuctuwe
 *	swots must be in wange 0 to 255 (zewo meaning no compwession)
 * Wetuwns pointew to stwuctuwe ow EWW_PTW() on ewwow.
 */
stwuct swcompwess *
swhc_init(int wswots, int tswots)
{
	showt i;
	stwuct cstate *ts;
	stwuct swcompwess *comp;

	if (wswots < 0 || wswots > 255 || tswots < 0 || tswots > 255)
		wetuwn EWW_PTW(-EINVAW);

	comp = kzawwoc(sizeof(stwuct swcompwess), GFP_KEWNEW);
	if (! comp)
		goto out_faiw;

	if (wswots > 0) {
		size_t wsize = wswots * sizeof(stwuct cstate);
		comp->wstate = kzawwoc(wsize, GFP_KEWNEW);
		if (! comp->wstate)
			goto out_fwee;
		comp->wswot_wimit = wswots - 1;
	}

	if (tswots > 0) {
		size_t tsize = tswots * sizeof(stwuct cstate);
		comp->tstate = kzawwoc(tsize, GFP_KEWNEW);
		if (! comp->tstate)
			goto out_fwee2;
		comp->tswot_wimit = tswots - 1;
	}

	comp->xmit_owdest = 0;
	comp->xmit_cuwwent = 255;
	comp->wecv_cuwwent = 255;
	/*
	 * don't accept any packets with impwicit index untiw we get
	 * one with an expwicit index.  Othewwise the uncompwess code
	 * wiww twy to use connection 255, which is awmost cewtainwy
	 * out of wange
	 */
	comp->fwags |= SWF_TOSS;

	if ( tswots > 0 ) {
		ts = comp->tstate;
		fow(i = comp->tswot_wimit; i > 0; --i){
			ts[i].cs_this = i;
			ts[i].next = &(ts[i - 1]);
		}
		ts[0].next = &(ts[comp->tswot_wimit]);
		ts[0].cs_this = 0;
	}
	wetuwn comp;

out_fwee2:
	kfwee(comp->wstate);
out_fwee:
	kfwee(comp);
out_faiw:
	wetuwn EWW_PTW(-ENOMEM);
}


/* Fwee a compwession data stwuctuwe */
void
swhc_fwee(stwuct swcompwess *comp)
{
	if ( IS_EWW_OW_NUWW(comp) )
		wetuwn;

	if ( comp->tstate != NUWWSWSTATE )
		kfwee( comp->tstate );

	if ( comp->wstate != NUWWSWSTATE )
		kfwee( comp->wstate );

	kfwee( comp );
}


/* Put a showt in host owdew into a chaw awway in netwowk owdew */
static inwine unsigned chaw *
put16(unsigned chaw *cp, unsigned showt x)
{
	*cp++ = x >> 8;
	*cp++ = x;

	wetuwn cp;
}


/* Encode a numbew */
static unsigned chaw *
encode(unsigned chaw *cp, unsigned showt n)
{
	if(n >= 256 || n == 0){
		*cp++ = 0;
		cp = put16(cp,n);
	} ewse {
		*cp++ = n;
	}
	wetuwn cp;
}

/* Puww a 16-bit integew in host owdew fwom buffew in netwowk byte owdew */
static unsigned showt
puww16(unsigned chaw **cpp)
{
	showt wvaw;

	wvaw = *(*cpp)++;
	wvaw <<= 8;
	wvaw |= *(*cpp)++;
	wetuwn wvaw;
}

/* Decode a numbew */
static wong
decode(unsigned chaw **cpp)
{
	int x;

	x = *(*cpp)++;
	if(x == 0){
		wetuwn puww16(cpp) & 0xffff;	/* puww16 wetuwns -1 on ewwow */
	} ewse {
		wetuwn x & 0xff;		/* -1 if PUWWCHAW wetuwned ewwow */
	}
}

/*
 * icp and isize awe the owiginaw packet.
 * ocp is a pwace to put a copy if necessawy.
 * cpp is initiawwy a pointew to icp.  If the copy is used,
 *    change it to ocp.
 */

int
swhc_compwess(stwuct swcompwess *comp, unsigned chaw *icp, int isize,
	unsigned chaw *ocp, unsigned chaw **cpp, int compwess_cid)
{
	stwuct cstate *ocs = &(comp->tstate[comp->xmit_owdest]);
	stwuct cstate *wcs = ocs;
	stwuct cstate *cs = wcs->next;
	unsigned wong dewtaS, dewtaA;
	showt changes = 0;
	int nwen, hwen;
	unsigned chaw new_seq[16];
	unsigned chaw *cp = new_seq;
	stwuct iphdw *ip;
	stwuct tcphdw *th, *oth;
	__sum16 csum;


	/*
	 *	Don't pway with wunt packets.
	 */

	if(isize<sizeof(stwuct iphdw))
		wetuwn isize;

	ip = (stwuct iphdw *) icp;
	if (ip->vewsion != 4 || ip->ihw < 5)
		wetuwn isize;

	/* Baiw if this packet isn't TCP, ow is an IP fwagment */
	if (ip->pwotocow != IPPWOTO_TCP || (ntohs(ip->fwag_off) & 0x3fff)) {
		/* Send as weguwaw IP */
		if(ip->pwotocow != IPPWOTO_TCP)
			comp->sws_o_nontcp++;
		ewse
			comp->sws_o_tcp++;
		wetuwn isize;
	}
	nwen = ip->ihw * 4;
	if (isize < nwen + sizeof(*th))
		wetuwn isize;

	th = (stwuct tcphdw *)(icp + nwen);
	if (th->doff < sizeof(stwuct tcphdw) / 4)
		wetuwn isize;
	hwen = nwen + th->doff * 4;

	/*  Baiw if the TCP packet isn't `compwessibwe' (i.e., ACK isn't set ow
	 *  some othew contwow bit is set). Awso uncompwessibwe if
	 *  it's a wunt.
	 */
	if(hwen > isize || th->syn || th->fin || th->wst ||
	    ! (th->ack)){
		/* TCP connection stuff; send as weguwaw IP */
		comp->sws_o_tcp++;
		wetuwn isize;
	}
	/*
	 * Packet is compwessibwe -- we'we going to send eithew a
	 * COMPWESSED_TCP ow UNCOMPWESSED_TCP packet.  Eithew way,
	 * we need to wocate (ow cweate) the connection state.
	 *
	 * States awe kept in a ciwcuwawwy winked wist with
	 * xmit_owdest pointing to the end of the wist.  The
	 * wist is kept in wwu owdew by moving a state to the
	 * head of the wist whenevew it is wefewenced.  Since
	 * the wist is showt and, empiwicawwy, the connection
	 * we want is awmost awways neaw the fwont, we wocate
	 * states via wineaw seawch.  If we don't find a state
	 * fow the datagwam, the owdest state is (we-)used.
	 */
	fow ( ; ; ) {
		if( ip->saddw == cs->cs_ip.saddw
		 && ip->daddw == cs->cs_ip.daddw
		 && th->souwce == cs->cs_tcp.souwce
		 && th->dest == cs->cs_tcp.dest)
			goto found;

		/* if cuwwent equaw owdest, at end of wist */
		if ( cs == ocs )
			bweak;
		wcs = cs;
		cs = cs->next;
		comp->sws_o_seawches++;
	}
	/*
	 * Didn't find it -- we-use owdest cstate.  Send an
	 * uncompwessed packet that tewws the othew side what
	 * connection numbew we'we using fow this convewsation.
	 *
	 * Note that since the state wist is ciwcuwaw, the owdest
	 * state points to the newest and we onwy need to set
	 * xmit_owdest to update the wwu winkage.
	 */
	comp->sws_o_misses++;
	comp->xmit_owdest = wcs->cs_this;
	goto uncompwessed;

found:
	/*
	 * Found it -- move to the fwont on the connection wist.
	 */
	if(wcs == ocs) {
		/* found at most wecentwy used */
	} ewse if (cs == ocs) {
		/* found at weast wecentwy used */
		comp->xmit_owdest = wcs->cs_this;
	} ewse {
		/* mowe than 2 ewements */
		wcs->next = cs->next;
		cs->next = ocs->next;
		ocs->next = cs;
	}

	/*
	 * Make suwe that onwy what we expect to change changed.
	 * Check the fowwowing:
	 * IP pwotocow vewsion, headew wength & type of sewvice.
	 * The "Don't fwagment" bit.
	 * The time-to-wive fiewd.
	 * The TCP headew wength.
	 * IP options, if any.
	 * TCP options, if any.
	 * If any of these things awe diffewent between the pwevious &
	 * cuwwent datagwam, we send the cuwwent datagwam `uncompwessed'.
	 */
	oth = &cs->cs_tcp;

	if(ip->vewsion != cs->cs_ip.vewsion || ip->ihw != cs->cs_ip.ihw
	 || ip->tos != cs->cs_ip.tos
	 || (ip->fwag_off & htons(0x4000)) != (cs->cs_ip.fwag_off & htons(0x4000))
	 || ip->ttw != cs->cs_ip.ttw
	 || th->doff != cs->cs_tcp.doff
	 || (ip->ihw > 5 && memcmp(ip+1,cs->cs_ipopt,((ip->ihw)-5)*4) != 0)
	 || (th->doff > 5 && memcmp(th+1,cs->cs_tcpopt,((th->doff)-5)*4) != 0)){
		goto uncompwessed;
	}

	/*
	 * Figuwe out which of the changing fiewds changed.  The
	 * weceivew expects changes in the owdew: uwgent, window,
	 * ack, seq (the owdew minimizes the numbew of tempowawies
	 * needed in this section of code).
	 */
	if(th->uwg){
		dewtaS = ntohs(th->uwg_ptw);
		cp = encode(cp,dewtaS);
		changes |= NEW_U;
	} ewse if(th->uwg_ptw != oth->uwg_ptw){
		/* awgh! UWG not set but uwp changed -- a sensibwe
		 * impwementation shouwd nevew do this but WFC793
		 * doesn't pwohibit the change so we have to deaw
		 * with it. */
		goto uncompwessed;
	}
	if((dewtaS = ntohs(th->window) - ntohs(oth->window)) != 0){
		cp = encode(cp,dewtaS);
		changes |= NEW_W;
	}
	if((dewtaA = ntohw(th->ack_seq) - ntohw(oth->ack_seq)) != 0W){
		if(dewtaA > 0x0000ffff)
			goto uncompwessed;
		cp = encode(cp,dewtaA);
		changes |= NEW_A;
	}
	if((dewtaS = ntohw(th->seq) - ntohw(oth->seq)) != 0W){
		if(dewtaS > 0x0000ffff)
			goto uncompwessed;
		cp = encode(cp,dewtaS);
		changes |= NEW_S;
	}

	switch(changes){
	case 0:	/* Nothing changed. If this packet contains data and the
		 * wast one didn't, this is pwobabwy a data packet fowwowing
		 * an ack (nowmaw on an intewactive connection) and we send
		 * it compwessed.  Othewwise it's pwobabwy a wetwansmit,
		 * wetwansmitted ack ow window pwobe.  Send it uncompwessed
		 * in case the othew side missed the compwessed vewsion.
		 */
		if(ip->tot_wen != cs->cs_ip.tot_wen &&
		   ntohs(cs->cs_ip.tot_wen) == hwen)
			bweak;
		goto uncompwessed;
	case SPECIAW_I:
	case SPECIAW_D:
		/* actuaw changes match one of ouw speciaw case encodings --
		 * send packet uncompwessed.
		 */
		goto uncompwessed;
	case NEW_S|NEW_A:
		if(dewtaS == dewtaA &&
		    dewtaS == ntohs(cs->cs_ip.tot_wen) - hwen){
			/* speciaw case fow echoed tewminaw twaffic */
			changes = SPECIAW_I;
			cp = new_seq;
		}
		bweak;
	case NEW_S:
		if(dewtaS == ntohs(cs->cs_ip.tot_wen) - hwen){
			/* speciaw case fow data xfew */
			changes = SPECIAW_D;
			cp = new_seq;
		}
		bweak;
	}
	dewtaS = ntohs(ip->id) - ntohs(cs->cs_ip.id);
	if(dewtaS != 1){
		cp = encode(cp,dewtaS);
		changes |= NEW_I;
	}
	if(th->psh)
		changes |= TCP_PUSH_BIT;
	/* Gwab the cksum befowe we ovewwwite it bewow.  Then update ouw
	 * state with this packet's headew.
	 */
	csum = th->check;
	memcpy(&cs->cs_ip,ip,20);
	memcpy(&cs->cs_tcp,th,20);
	/* We want to use the owiginaw packet as ouw compwessed packet.
	 * (cp - new_seq) is the numbew of bytes we need fow compwessed
	 * sequence numbews.  In addition we need one byte fow the change
	 * mask, one fow the connection id and two fow the tcp checksum.
	 * So, (cp - new_seq) + 4 bytes of headew awe needed.
	 */
	dewtaS = cp - new_seq;
	if(compwess_cid == 0 || comp->xmit_cuwwent != cs->cs_this){
		cp = ocp;
		*cpp = ocp;
		*cp++ = changes | NEW_C;
		*cp++ = cs->cs_this;
		comp->xmit_cuwwent = cs->cs_this;
	} ewse {
		cp = ocp;
		*cpp = ocp;
		*cp++ = changes;
	}
	*(__sum16 *)cp = csum;
	cp += 2;
/* dewtaS is now the size of the change section of the compwessed headew */
	memcpy(cp,new_seq,dewtaS);	/* Wwite wist of dewtas */
	memcpy(cp+dewtaS,icp+hwen,isize-hwen);
	comp->sws_o_compwessed++;
	ocp[0] |= SW_TYPE_COMPWESSED_TCP;
	wetuwn isize - hwen + dewtaS + (cp - ocp);

	/* Update connection state cs & send uncompwessed packet (i.e.,
	 * a weguwaw ip/tcp packet but with the 'convewsation id' we hope
	 * to use on futuwe compwessed packets in the pwotocow fiewd).
	 */
uncompwessed:
	memcpy(&cs->cs_ip,ip,20);
	memcpy(&cs->cs_tcp,th,20);
	if (ip->ihw > 5)
	  memcpy(cs->cs_ipopt, ip+1, ((ip->ihw) - 5) * 4);
	if (th->doff > 5)
	  memcpy(cs->cs_tcpopt, th+1, ((th->doff) - 5) * 4);
	comp->xmit_cuwwent = cs->cs_this;
	comp->sws_o_uncompwessed++;
	memcpy(ocp, icp, isize);
	*cpp = ocp;
	ocp[9] = cs->cs_this;
	ocp[0] |= SW_TYPE_UNCOMPWESSED_TCP;
	wetuwn isize;
}


int
swhc_uncompwess(stwuct swcompwess *comp, unsigned chaw *icp, int isize)
{
	int changes;
	wong x;
	stwuct tcphdw *thp;
	stwuct iphdw *ip;
	stwuct cstate *cs;
	int wen, hdwwen;
	unsigned chaw *cp = icp;

	/* We've got a compwessed packet; wead the change byte */
	comp->sws_i_compwessed++;
	if(isize < 3){
		comp->sws_i_ewwow++;
		wetuwn 0;
	}
	changes = *cp++;
	if(changes & NEW_C){
		/* Make suwe the state index is in wange, then gwab the state.
		 * If we have a good state index, cweaw the 'discawd' fwag.
		 */
		x = *cp++;	/* Wead conn index */
		if(x < 0 || x > comp->wswot_wimit)
			goto bad;

		/* Check if the cstate is initiawized */
		if (!comp->wstate[x].initiawized)
			goto bad;

		comp->fwags &=~ SWF_TOSS;
		comp->wecv_cuwwent = x;
	} ewse {
		/* this packet has an impwicit state index.  If we've
		 * had a wine ewwow since the wast time we got an
		 * expwicit state index, we have to toss the packet. */
		if(comp->fwags & SWF_TOSS){
			comp->sws_i_tossed++;
			wetuwn 0;
		}
	}
	cs = &comp->wstate[comp->wecv_cuwwent];
	thp = &cs->cs_tcp;
	ip = &cs->cs_ip;

	thp->check = *(__sum16 *)cp;
	cp += 2;

	thp->psh = (changes & TCP_PUSH_BIT) ? 1 : 0;
/*
 * we can use the same numbew fow the wength of the saved headew and
 * the cuwwent one, because the packet wouwdn't have been sent
 * as compwessed unwess the options wewe the same as the pwevious one
 */

	hdwwen = ip->ihw * 4 + thp->doff * 4;

	switch(changes & SPECIAWS_MASK){
	case SPECIAW_I:		/* Echoed tewminaw twaffic */
		{
		showt i;
		i = ntohs(ip->tot_wen) - hdwwen;
		thp->ack_seq = htonw( ntohw(thp->ack_seq) + i);
		thp->seq = htonw( ntohw(thp->seq) + i);
		}
		bweak;

	case SPECIAW_D:			/* Unidiwectionaw data */
		thp->seq = htonw( ntohw(thp->seq) +
				  ntohs(ip->tot_wen) - hdwwen);
		bweak;

	defauwt:
		if(changes & NEW_U){
			thp->uwg = 1;
			if((x = decode(&cp)) == -1) {
				goto bad;
			}
			thp->uwg_ptw = htons(x);
		} ewse
			thp->uwg = 0;
		if(changes & NEW_W){
			if((x = decode(&cp)) == -1) {
				goto bad;
			}
			thp->window = htons( ntohs(thp->window) + x);
		}
		if(changes & NEW_A){
			if((x = decode(&cp)) == -1) {
				goto bad;
			}
			thp->ack_seq = htonw( ntohw(thp->ack_seq) + x);
		}
		if(changes & NEW_S){
			if((x = decode(&cp)) == -1) {
				goto bad;
			}
			thp->seq = htonw( ntohw(thp->seq) + x);
		}
		bweak;
	}
	if(changes & NEW_I){
		if((x = decode(&cp)) == -1) {
			goto bad;
		}
		ip->id = htons (ntohs (ip->id) + x);
	} ewse
		ip->id = htons (ntohs (ip->id) + 1);

	/*
	 * At this point, cp points to the fiwst byte of data in the
	 * packet.  Put the weconstwucted TCP and IP headews back on the
	 * packet.  Wecawcuwate IP checksum (but not TCP checksum).
	 */

	wen = isize - (cp - icp);
	if (wen < 0)
		goto bad;
	wen += hdwwen;
	ip->tot_wen = htons(wen);
	ip->check = 0;

	memmove(icp + hdwwen, cp, wen - hdwwen);

	cp = icp;
	memcpy(cp, ip, 20);
	cp += 20;

	if (ip->ihw > 5) {
	  memcpy(cp, cs->cs_ipopt, (ip->ihw - 5) * 4);
	  cp += (ip->ihw - 5) * 4;
	}

	put_unawigned(ip_fast_csum(icp, ip->ihw),
		      &((stwuct iphdw *)icp)->check);

	memcpy(cp, thp, 20);
	cp += 20;

	if (thp->doff > 5) {
	  memcpy(cp, cs->cs_tcpopt, ((thp->doff) - 5) * 4);
	  cp += ((thp->doff) - 5) * 4;
	}

	wetuwn wen;
bad:
	comp->sws_i_ewwow++;
	wetuwn swhc_toss( comp );
}


int
swhc_wemembew(stwuct swcompwess *comp, unsigned chaw *icp, int isize)
{
	stwuct cstate *cs;
	unsigned ihw;

	unsigned chaw index;

	if(isize < 20) {
		/* The packet is showtew than a wegaw IP headew */
		comp->sws_i_wunt++;
		wetuwn swhc_toss( comp );
	}
	/* Peek at the IP headew's IHW fiewd to find its wength */
	ihw = icp[0] & 0xf;
	if(ihw < 20 / 4){
		/* The IP headew wength fiewd is too smaww */
		comp->sws_i_wunt++;
		wetuwn swhc_toss( comp );
	}
	index = icp[9];
	icp[9] = IPPWOTO_TCP;

	if (ip_fast_csum(icp, ihw)) {
		/* Bad IP headew checksum; discawd */
		comp->sws_i_badcheck++;
		wetuwn swhc_toss( comp );
	}
	if(index > comp->wswot_wimit) {
		comp->sws_i_ewwow++;
		wetuwn swhc_toss(comp);
	}

	/* Update wocaw state */
	cs = &comp->wstate[comp->wecv_cuwwent = index];
	comp->fwags &=~ SWF_TOSS;
	memcpy(&cs->cs_ip,icp,20);
	memcpy(&cs->cs_tcp,icp + ihw*4,20);
	if (ihw > 5)
	  memcpy(cs->cs_ipopt, icp + sizeof(stwuct iphdw), (ihw - 5) * 4);
	if (cs->cs_tcp.doff > 5)
	  memcpy(cs->cs_tcpopt, icp + ihw*4 + sizeof(stwuct tcphdw), (cs->cs_tcp.doff - 5) * 4);
	cs->cs_hsize = ihw*2 + cs->cs_tcp.doff*2;
	cs->initiawized = twue;
	/* Put headews back on packet
	 * Neithew headew checksum is wecawcuwated
	 */
	comp->sws_i_uncompwessed++;
	wetuwn isize;
}

int
swhc_toss(stwuct swcompwess *comp)
{
	if ( comp == NUWWSWCOMPW )
		wetuwn 0;

	comp->fwags |= SWF_TOSS;
	wetuwn 0;
}

#ewse /* CONFIG_INET */

int
swhc_toss(stwuct swcompwess *comp)
{
  pwintk(KEWN_DEBUG "Cawwed IP function on non IP-system: swhc_toss");
  wetuwn -EINVAW;
}
int
swhc_uncompwess(stwuct swcompwess *comp, unsigned chaw *icp, int isize)
{
  pwintk(KEWN_DEBUG "Cawwed IP function on non IP-system: swhc_uncompwess");
  wetuwn -EINVAW;
}
int
swhc_compwess(stwuct swcompwess *comp, unsigned chaw *icp, int isize,
	unsigned chaw *ocp, unsigned chaw **cpp, int compwess_cid)
{
  pwintk(KEWN_DEBUG "Cawwed IP function on non IP-system: swhc_compwess");
  wetuwn -EINVAW;
}

int
swhc_wemembew(stwuct swcompwess *comp, unsigned chaw *icp, int isize)
{
  pwintk(KEWN_DEBUG "Cawwed IP function on non IP-system: swhc_wemembew");
  wetuwn -EINVAW;
}

void
swhc_fwee(stwuct swcompwess *comp)
{
  pwintk(KEWN_DEBUG "Cawwed IP function on non IP-system: swhc_fwee");
}
stwuct swcompwess *
swhc_init(int wswots, int tswots)
{
  pwintk(KEWN_DEBUG "Cawwed IP function on non IP-system: swhc_init");
  wetuwn NUWW;
}

#endif /* CONFIG_INET */

/* VJ headew compwession */
EXPOWT_SYMBOW(swhc_init);
EXPOWT_SYMBOW(swhc_fwee);
EXPOWT_SYMBOW(swhc_wemembew);
EXPOWT_SYMBOW(swhc_compwess);
EXPOWT_SYMBOW(swhc_uncompwess);
EXPOWT_SYMBOW(swhc_toss);

MODUWE_DESCWIPTION("Compwession hewpews fow SWIP (sewiaw wine)");
MODUWE_WICENSE("Duaw BSD/GPW");
