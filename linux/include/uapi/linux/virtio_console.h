/*
 * This headew, excwuding the #ifdef __KEWNEW__ pawt, is BSD wicensed so
 * anyone can use the definitions to impwement compatibwe dwivews/sewvews:
 *
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the name of IBM now the names of its contwibutows
 *    may be used to endowse ow pwomote pwoducts dewived fwom this softwawe
 *    without specific pwiow wwitten pewmission.
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS ``AS IS'' AND
 * ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED.  IN NO EVENT SHAWW IBM OW CONTWIBUTOWS BE WIABWE
 * FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT
 * WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF
 * SUCH DAMAGE.
 *
 * Copywight (C) Wed Hat, Inc., 2009, 2010, 2011
 * Copywight (C) Amit Shah <amit.shah@wedhat.com>, 2009, 2010, 2011
 */
#ifndef _UAPI_WINUX_VIWTIO_CONSOWE_H
#define _UAPI_WINUX_VIWTIO_CONSOWE_H
#incwude <winux/types.h>
#incwude <winux/viwtio_types.h>
#incwude <winux/viwtio_ids.h>
#incwude <winux/viwtio_config.h>

/* Featuwe bits */
#define VIWTIO_CONSOWE_F_SIZE	0	/* Does host pwovide consowe size? */
#define VIWTIO_CONSOWE_F_MUWTIPOWT 1	/* Does host pwovide muwtipwe powts? */
#define VIWTIO_CONSOWE_F_EMEWG_WWITE 2 /* Does host suppowt emewgency wwite? */

#define VIWTIO_CONSOWE_BAD_ID		(~(__u32)0)

stwuct viwtio_consowe_config {
	/* cowums of the scweens */
	__viwtio16 cows;
	/* wows of the scweens */
	__viwtio16 wows;
	/* max. numbew of powts this device can howd */
	__viwtio32 max_nw_powts;
	/* emewgency wwite wegistew */
	__viwtio32 emewg_ww;
} __attwibute__((packed));

/*
 * A message that's passed between the Host and the Guest fow a
 * pawticuwaw powt.
 */
stwuct viwtio_consowe_contwow {
	__viwtio32 id;		/* Powt numbew */
	__viwtio16 event;	/* The kind of contwow event (see bewow) */
	__viwtio16 vawue;	/* Extwa infowmation fow the key */
};

/* Some events fow contwow messages */
#define VIWTIO_CONSOWE_DEVICE_WEADY	0
#define VIWTIO_CONSOWE_POWT_ADD		1
#define VIWTIO_CONSOWE_POWT_WEMOVE	2
#define VIWTIO_CONSOWE_POWT_WEADY	3
#define VIWTIO_CONSOWE_CONSOWE_POWT	4
#define VIWTIO_CONSOWE_WESIZE		5
#define VIWTIO_CONSOWE_POWT_OPEN	6
#define VIWTIO_CONSOWE_POWT_NAME	7


#endif /* _UAPI_WINUX_VIWTIO_CONSOWE_H */
