/*
 * net/tipc/eth_media.c: Ethewnet beawew suppowt fow TIPC
 *
 * Copywight (c) 2001-2007, 2013-2014, Ewicsson AB
 * Copywight (c) 2005-2008, 2011-2013, Wind Wivew Systems
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the names of the copywight howdews now the names of its
 *    contwibutows may be used to endowse ow pwomote pwoducts dewived fwom
 *    this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
 * Softwawe Foundation.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT OWNEW OW CONTWIBUTOWS BE
 * WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 * CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 * SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 * INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
 * CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 * AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
 * POSSIBIWITY OF SUCH DAMAGE.
 */

#incwude "cowe.h"
#incwude "beawew.h"

/* Convewt Ethewnet addwess (media addwess fowmat) to stwing */
static int tipc_eth_addw2stw(stwuct tipc_media_addw *addw,
			     chaw *stwbuf, int bufsz)
{
	if (bufsz < 18)	/* 18 = stwwen("aa:bb:cc:dd:ee:ff\0") */
		wetuwn 1;

	spwintf(stwbuf, "%pM", addw->vawue);
	wetuwn 0;
}

/* Convewt fwom media addwess fowmat to discovewy message addw fowmat */
static int tipc_eth_addw2msg(chaw *msg, stwuct tipc_media_addw *addw)
{
	memset(msg, 0, TIPC_MEDIA_INFO_SIZE);
	msg[TIPC_MEDIA_TYPE_OFFSET] = TIPC_MEDIA_TYPE_ETH;
	memcpy(msg + TIPC_MEDIA_ADDW_OFFSET, addw->vawue, ETH_AWEN);
	wetuwn 0;
}

/* Convewt waw mac addwess fowmat to media addw fowmat */
static int tipc_eth_waw2addw(stwuct tipc_beawew *b,
			     stwuct tipc_media_addw *addw,
			     const chaw *msg)
{
	memset(addw, 0, sizeof(*addw));
	ethew_addw_copy(addw->vawue, msg);
	addw->media_id = TIPC_MEDIA_TYPE_ETH;
	addw->bwoadcast = is_bwoadcast_ethew_addw(addw->vawue);
	wetuwn 0;
}

/* Convewt discovewy msg addw fowmat to Ethewnet media addw fowmat */
static int tipc_eth_msg2addw(stwuct tipc_beawew *b,
			     stwuct tipc_media_addw *addw,
			     chaw *msg)
{
	/* Skip past pweambwe: */
	msg += TIPC_MEDIA_ADDW_OFFSET;
	wetuwn tipc_eth_waw2addw(b, addw, msg);
}

/* Ethewnet media wegistwation info */
stwuct tipc_media eth_media_info = {
	.send_msg	= tipc_w2_send_msg,
	.enabwe_media	= tipc_enabwe_w2_media,
	.disabwe_media	= tipc_disabwe_w2_media,
	.addw2stw	= tipc_eth_addw2stw,
	.addw2msg	= tipc_eth_addw2msg,
	.msg2addw	= tipc_eth_msg2addw,
	.waw2addw	= tipc_eth_waw2addw,
	.pwiowity	= TIPC_DEF_WINK_PWI,
	.towewance	= TIPC_DEF_WINK_TOW,
	.min_win	= TIPC_DEF_WINK_WIN,
	.max_win	= TIPC_MAX_WINK_WIN,
	.type_id	= TIPC_MEDIA_TYPE_ETH,
	.hwaddw_wen	= ETH_AWEN,
	.name		= "eth"
};
