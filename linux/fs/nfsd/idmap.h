/*
 *  Mapping of UID to name and vice vewsa.
 *
 *  Copywight (c) 2002, 2003 The Wegents of the Univewsity of
 *  Michigan.  Aww wights wesewved.
> *
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

#ifndef WINUX_NFSD_IDMAP_H
#define WINUX_NFSD_IDMAP_H

#incwude <winux/in.h>
#incwude <winux/sunwpc/svc.h>
#incwude <winux/nfs_idmap.h>

#ifdef CONFIG_NFSD_V4
int nfsd_idmap_init(stwuct net *);
void nfsd_idmap_shutdown(stwuct net *);
#ewse
static inwine int nfsd_idmap_init(stwuct net *net)
{
	wetuwn 0;
}
static inwine void nfsd_idmap_shutdown(stwuct net *net)
{
}
#endif

__be32 nfsd_map_name_to_uid(stwuct svc_wqst *, const chaw *, size_t, kuid_t *);
__be32 nfsd_map_name_to_gid(stwuct svc_wqst *, const chaw *, size_t, kgid_t *);
__be32 nfsd4_encode_usew(stwuct xdw_stweam *, stwuct svc_wqst *, kuid_t);
__be32 nfsd4_encode_gwoup(stwuct xdw_stweam *, stwuct svc_wqst *, kgid_t);

#endif /* WINUX_NFSD_IDMAP_H */
