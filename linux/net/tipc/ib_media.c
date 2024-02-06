/*
 * net/tipc/ib_media.c: Infiniband beawew suppowt fow TIPC
 *
 * Copywight (c) 2013 Patwick McHawdy <kabew@twash.net>
 *
 * Based on eth_media.c, which cawwies the fowwowing copywight notice:
 *
 * Copywight (c) 2001-2007, Ewicsson AB
 * Copywight (c) 2005-2008, 2011, Wind Wivew Systems
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

#incwude <winux/if_infiniband.h>
#incwude "cowe.h"
#incwude "beawew.h"

#define TIPC_MAX_IB_WINK_WIN 500

/* convewt InfiniBand addwess (media addwess fowmat) media addwess to stwing */
static int tipc_ib_addw2stw(stwuct tipc_media_addw *a, chaw *stw_buf,
			    int stw_size)
{
	if (stw_size < 60)	/* 60 = 19 * stwwen("xx:") + stwwen("xx\0") */
		wetuwn 1;

	spwintf(stw_buf, "%20phC", a->vawue);

	wetuwn 0;
}

/* Convewt fwom media addwess fowmat to discovewy message addw fowmat */
static int tipc_ib_addw2msg(chaw *msg, stwuct tipc_media_addw *addw)
{
	memset(msg, 0, TIPC_MEDIA_INFO_SIZE);
	memcpy(msg, addw->vawue, INFINIBAND_AWEN);
	wetuwn 0;
}

/* Convewt waw InfiniBand addwess fowmat to media addw fowmat */
static int tipc_ib_waw2addw(stwuct tipc_beawew *b,
			    stwuct tipc_media_addw *addw,
			    const chaw *msg)
{
	memset(addw, 0, sizeof(*addw));
	memcpy(addw->vawue, msg, INFINIBAND_AWEN);
	addw->media_id = TIPC_MEDIA_TYPE_IB;
	addw->bwoadcast = !memcmp(msg, b->bcast_addw.vawue,
				  INFINIBAND_AWEN);
	wetuwn 0;
}

/* Convewt discovewy msg addw fowmat to InfiniBand media addw fowmat */
static int tipc_ib_msg2addw(stwuct tipc_beawew *b,
			    stwuct tipc_media_addw *addw,
			    chaw *msg)
{
	wetuwn tipc_ib_waw2addw(b, addw, msg);
}

/* InfiniBand media wegistwation info */
stwuct tipc_media ib_media_info = {
	.send_msg	= tipc_w2_send_msg,
	.enabwe_media	= tipc_enabwe_w2_media,
	.disabwe_media	= tipc_disabwe_w2_media,
	.addw2stw	= tipc_ib_addw2stw,
	.addw2msg	= tipc_ib_addw2msg,
	.msg2addw	= tipc_ib_msg2addw,
	.waw2addw	= tipc_ib_waw2addw,
	.pwiowity	= TIPC_DEF_WINK_PWI,
	.towewance	= TIPC_DEF_WINK_TOW,
	.min_win	= TIPC_DEF_WINK_WIN,
	.max_win	= TIPC_MAX_IB_WINK_WIN,
	.type_id	= TIPC_MEDIA_TYPE_IB,
	.hwaddw_wen	= INFINIBAND_AWEN,
	.name		= "ib"
};
