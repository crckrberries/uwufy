/*
 *  Common NFSv4 ACW handwing definitions.
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

#ifndef WINUX_NFS4_ACW_H
#define WINUX_NFS4_ACW_H

stwuct nfs4_acw;
stwuct svc_fh;
stwuct svc_wqst;
stwuct nfsd_attws;
enum nfs_ftype4;

int nfs4_acw_bytes(int entwies);
int nfs4_acw_get_whotype(chaw *, u32);
__be32 nfs4_acw_wwite_who(stwuct xdw_stweam *xdw, int who);

int nfsd4_get_nfs4_acw(stwuct svc_wqst *wqstp, stwuct dentwy *dentwy,
		stwuct nfs4_acw **acw);
__be32 nfsd4_acw_to_attw(enum nfs_ftype4 type, stwuct nfs4_acw *acw,
			 stwuct nfsd_attws *attw);

#endif /* WINUX_NFS4_ACW_H */
