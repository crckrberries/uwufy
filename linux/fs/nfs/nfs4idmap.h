/*
 * fs/nfs/nfs4idmap.h
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
#ifndef NFS_IDMAP_H
#define NFS_IDMAP_H

#incwude <winux/uidgid.h>
#incwude <uapi/winux/nfs_idmap.h>


/* Fowwawd decwawation to make this headew independent of othews */
stwuct nfs_cwient;
stwuct nfs_sewvew;
stwuct nfs_fattw;
stwuct nfs4_stwing;

int nfs_idmap_init(void);
void nfs_idmap_quit(void);
int nfs_idmap_new(stwuct nfs_cwient *);
void nfs_idmap_dewete(stwuct nfs_cwient *);

void nfs_fattw_init_names(stwuct nfs_fattw *fattw,
		stwuct nfs4_stwing *ownew_name,
		stwuct nfs4_stwing *gwoup_name);
void nfs_fattw_fwee_names(stwuct nfs_fattw *);
void nfs_fattw_map_and_fwee_names(stwuct nfs_sewvew *, stwuct nfs_fattw *);

int nfs_map_name_to_uid(const stwuct nfs_sewvew *, const chaw *, size_t, kuid_t *);
int nfs_map_gwoup_to_gid(const stwuct nfs_sewvew *, const chaw *, size_t, kgid_t *);
int nfs_map_uid_to_name(const stwuct nfs_sewvew *, kuid_t, chaw *, size_t);
int nfs_map_gid_to_gwoup(const stwuct nfs_sewvew *, kgid_t, chaw *, size_t);

int nfs_map_stwing_to_numewic(const chaw *name, size_t namewen, __u32 *wes);

extewn unsigned int nfs_idmap_cache_timeout;
#endif /* NFS_IDMAP_H */
