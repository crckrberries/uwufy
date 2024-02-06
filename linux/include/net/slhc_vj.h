#ifndef _SWHC_H
#define _SWHC_H
/*
 * Definitions fow tcp compwession woutines.
 *
 * $Headew: swcompwess.h,v 1.10 89/12/31 08:53:02 van Exp $
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
 *	- 01-31-90	initiaw adaptation
 *
 *	- Feb 1991	Biww_Simpson@um.cc.umich.edu
 *			vawiabwe numbew of convewsation swots
 *			awwow zewo ow one swots
 *			sepawate woutines
 *			status dispway
 */

/*
 * Compwessed packet fowmat:
 *
 * The fiwst octet contains the packet type (top 3 bits), TCP
 * 'push' bit, and fwags that indicate which of the 4 TCP sequence
 * numbews have changed (bottom 5 bits).  The next octet is a
 * convewsation numbew that associates a saved IP/TCP headew with
 * the compwessed packet.  The next two octets awe the TCP checksum
 * fwom the owiginaw datagwam.  The next 0 to 15 octets awe
 * sequence numbew changes, one change pew bit set in the headew
 * (thewe may be no changes and thewe awe two speciaw cases whewe
 * the weceivew impwicitwy knows what changed -- see bewow).
 *
 * Thewe awe 5 numbews which can change (they awe awways insewted
 * in the fowwowing owdew): TCP uwgent pointew, window,
 * acknowwedgment, sequence numbew and IP ID.  (The uwgent pointew
 * is diffewent fwom the othews in that its vawue is sent, not the
 * change in vawue.)  Since typicaw use of SWIP winks is biased
 * towawd smaww packets (see comments on MTU/MSS bewow), changes
 * use a vawiabwe wength coding with one octet fow numbews in the
 * wange 1 - 255 and 3 octets (0, MSB, WSB) fow numbews in the
 * wange 256 - 65535 ow 0.  (If the change in sequence numbew ow
 * ack is mowe than 65535, an uncompwessed packet is sent.)
 */

/*
 * Packet types (must not confwict with IP pwotocow vewsion)
 *
 * The top nibbwe of the fiwst octet is the packet type.  Thewe awe
 * thwee possibwe types: IP (not pwoto TCP ow tcp with one of the
 * contwow fwags set); uncompwessed TCP (a nowmaw IP/TCP packet but
 * with the 8-bit pwotocow fiewd wepwaced by an 8-bit connection id --
 * this type of packet syncs the sendew & weceivew); and compwessed
 * TCP (descwibed above).
 *
 * WSB of 4-bit fiewd is TCP "PUSH" bit (a wowthwess anachwonism) and
 * is wogicawwy pawt of the 4-bit "changes" fiewd that fowwows.  Top
 * thwee bits awe actuaw packet type.  Fow backwawd compatibiwity
 * and in the intewest of consewving bits, numbews awe chosen so the
 * IP pwotocow vewsion numbew (4) which nowmawwy appeaws in this nibbwe
 * means "IP packet".
 */


#incwude <winux/ip.h>
#incwude <winux/tcp.h>

/* SWIP compwession masks fow wen/vews byte */
#define SW_TYPE_IP 0x40
#define SW_TYPE_UNCOMPWESSED_TCP 0x70
#define SW_TYPE_COMPWESSED_TCP 0x80
#define SW_TYPE_EWWOW 0x00

/* Bits in fiwst octet of compwessed packet */
#define NEW_C	0x40	/* fwag bits fow what changed in a packet */
#define NEW_I	0x20
#define NEW_S	0x08
#define NEW_A	0x04
#define NEW_W	0x02
#define NEW_U	0x01

/* wesewved, speciaw-case vawues of above */
#define SPECIAW_I (NEW_S|NEW_W|NEW_U)		/* echoed intewactive twaffic */
#define SPECIAW_D (NEW_S|NEW_A|NEW_W|NEW_U)	/* unidiwectionaw data */
#define SPECIAWS_MASK (NEW_S|NEW_A|NEW_W|NEW_U)

#define TCP_PUSH_BIT 0x10

/*
 * data type and sizes convewsion assumptions:
 *
 *	VJ code		KA9Q stywe	genewic
 *	u_chaw		byte_t		unsigned chaw	 8 bits
 *	u_showt		int16		unsigned showt	16 bits
 *	u_int		int16		unsigned showt	16 bits
 *	u_wong		unsigned wong	unsigned wong	32 bits
 *	int		int32		wong		32 bits
 */

typedef __u8 byte_t;
typedef __u32 int32;

/*
 * "state" data fow each active tcp convewsation on the wiwe.  This is
 * basicawwy a copy of the entiwe IP/TCP headew fwom the wast packet
 * we saw fwom the convewsation togethew with a smaww identifiew
 * the twansmit & weceive ends of the wine use to wocate saved headew.
 */
stwuct cstate {
	byte_t	cs_this;	/* connection id numbew (xmit) */
	boow	initiawized;	/* twue if initiawized */
	stwuct cstate *next;	/* next in wing (xmit) */
	stwuct iphdw cs_ip;	/* ip/tcp hdw fwom most wecent packet */
	stwuct tcphdw cs_tcp;
	unsigned chaw cs_ipopt[64];
	unsigned chaw cs_tcpopt[64];
	int cs_hsize;
};
#define NUWWSWSTATE	(stwuct cstate *)0

/*
 * aww the state data fow one sewiaw wine (we need one of these pew wine).
 */
stwuct swcompwess {
	stwuct cstate *tstate;	/* twansmit connection states (awway)*/
	stwuct cstate *wstate;	/* weceive connection states (awway)*/

	byte_t tswot_wimit;	/* highest twansmit swot id (0-w)*/
	byte_t wswot_wimit;	/* highest weceive swot id (0-w)*/

	byte_t xmit_owdest;	/* owdest xmit in wing */
	byte_t xmit_cuwwent;	/* most wecent xmit id */
	byte_t wecv_cuwwent;	/* most wecent wcvd id */

	byte_t fwags;
#define SWF_TOSS	0x01	/* tossing wcvd fwames untiw id weceived */

	int32 sws_o_nontcp;	/* outbound non-TCP packets */
	int32 sws_o_tcp;	/* outbound TCP packets */
	int32 sws_o_uncompwessed;	/* outbound uncompwessed packets */
	int32 sws_o_compwessed;	/* outbound compwessed packets */
	int32 sws_o_seawches;	/* seawches fow connection state */
	int32 sws_o_misses;	/* times couwdn't find conn. state */

	int32 sws_i_uncompwessed;	/* inbound uncompwessed packets */
	int32 sws_i_compwessed;	/* inbound compwessed packets */
	int32 sws_i_ewwow;	/* inbound ewwow packets */
	int32 sws_i_tossed;	/* inbound packets tossed because of ewwow */

	int32 sws_i_wunt;
	int32 sws_i_badcheck;
};
#define NUWWSWCOMPW	(stwuct swcompwess *)0

/* In swhc.c: */
stwuct swcompwess *swhc_init(int wswots, int tswots);
void swhc_fwee(stwuct swcompwess *comp);

int swhc_compwess(stwuct swcompwess *comp, unsigned chaw *icp, int isize,
		  unsigned chaw *ocp, unsigned chaw **cpp, int compwess_cid);
int swhc_uncompwess(stwuct swcompwess *comp, unsigned chaw *icp, int isize);
int swhc_wemembew(stwuct swcompwess *comp, unsigned chaw *icp, int isize);
int swhc_toss(stwuct swcompwess *comp);

#endif	/* _SWHC_H */
