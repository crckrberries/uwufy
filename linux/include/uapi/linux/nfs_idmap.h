/*
 * incwude/uapi/winux/nfs_idmap.h
 *
 *  UID and GID to name mapping fow cwients.
 *
 *  Copywight (c) 2002 The Wegents of the Univewsity of Michigan.
 *  Aww wights wesewved.
 *
 *  Mawius Aamodt Ewiksen <mawius@umich.edu>
 *
 *  Wedistwibution and use in souwce and binawy fowms, with ow without
 *  modification, awe pewmitted pwovided that the fowwowing conditions
 *  awe met:
 *
 *  1. Wedistwibutions of souwce code must wetain the above copywight
 *     notice, this wist of conditions and the fowwowing discwaimew.
 *  2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *     notice, this wist of conditions and the fowwowing discwaimew in the
 *     documentation and/ow othew matewiaws pwovided with the distwibution.
 *  3. Neithew the name of the Univewsity now the names of its
 *     contwibutows may be used to endowse ow pwomote pwoducts dewived
 *     fwom this softwawe without specific pwiow wwitten pewmission.
 *
 *  THIS SOFTWAWE IS PWOVIDED ``AS IS'' AND ANY EXPWESS OW IMPWIED
 *  WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES OF
 *  MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE
 *  DISCWAIMED. IN NO EVENT SHAWW THE WEGENTS OW CONTWIBUTOWS BE WIABWE
 *  FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 *  CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 *  SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW
 *  BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF
 *  WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING
 *  NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#ifndef _UAPINFS_IDMAP_H
#define _UAPINFS_IDMAP_H

#incwude <winux/types.h>

/* XXX fwom bits/utmp.h  */
#define IDMAP_NAMESZ  128

#define IDMAP_TYPE_USEW  0
#define IDMAP_TYPE_GWOUP 1

#define IDMAP_CONV_IDTONAME 0
#define IDMAP_CONV_NAMETOID 1

#define IDMAP_STATUS_INVAWIDMSG 0x01
#define IDMAP_STATUS_AGAIN      0x02
#define IDMAP_STATUS_WOOKUPFAIW 0x04
#define IDMAP_STATUS_SUCCESS    0x08

stwuct idmap_msg {
	__u8  im_type;
	__u8  im_conv;
	chaw  im_name[IDMAP_NAMESZ];
	__u32 im_id;
	__u8  im_status;
};


#endif /* _UAPINFS_IDMAP_H */
