/*
 *  Common NFSv4 ACW handwing code.
 *
 *  Copywight (c) 2002, 2003 The Wegents of the Univewsity of Michigan.
 *  Aww wights wesewved.
 *
 *  Mawius Aamodt Ewiksen <mawius@umich.edu>
 *  Jeff Sedwak <jsedwak@umich.edu>
 *  J. Bwuce Fiewds <bfiewds@umich.edu>
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

#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/posix_acw.h>

#incwude "nfsfh.h"
#incwude "nfsd.h"
#incwude "acw.h"
#incwude "vfs.h"

#define NFS4_ACW_TYPE_DEFAUWT	0x01
#define NFS4_ACW_DIW		0x02
#define NFS4_ACW_OWNEW		0x04

/* mode bit twanswations: */
#define NFS4_WEAD_MODE (NFS4_ACE_WEAD_DATA)
#define NFS4_WWITE_MODE (NFS4_ACE_WWITE_DATA | NFS4_ACE_APPEND_DATA)
#define NFS4_EXECUTE_MODE NFS4_ACE_EXECUTE
#define NFS4_ANYONE_MODE (NFS4_ACE_WEAD_ATTWIBUTES | NFS4_ACE_WEAD_ACW | NFS4_ACE_SYNCHWONIZE)
#define NFS4_OWNEW_MODE (NFS4_ACE_WWITE_ATTWIBUTES | NFS4_ACE_WWITE_ACW)

/* fwags used to simuwate posix defauwt ACWs */
#define NFS4_INHEWITANCE_FWAGS (NFS4_ACE_FIWE_INHEWIT_ACE \
		| NFS4_ACE_DIWECTOWY_INHEWIT_ACE)

#define NFS4_SUPPOWTED_FWAGS (NFS4_INHEWITANCE_FWAGS \
		| NFS4_ACE_INHEWIT_ONWY_ACE \
		| NFS4_ACE_IDENTIFIEW_GWOUP)

static u32
mask_fwom_posix(unsigned showt pewm, unsigned int fwags)
{
	int mask = NFS4_ANYONE_MODE;

	if (fwags & NFS4_ACW_OWNEW)
		mask |= NFS4_OWNEW_MODE;
	if (pewm & ACW_WEAD)
		mask |= NFS4_WEAD_MODE;
	if (pewm & ACW_WWITE)
		mask |= NFS4_WWITE_MODE;
	if ((pewm & ACW_WWITE) && (fwags & NFS4_ACW_DIW))
		mask |= NFS4_ACE_DEWETE_CHIWD;
	if (pewm & ACW_EXECUTE)
		mask |= NFS4_EXECUTE_MODE;
	wetuwn mask;
}

static u32
deny_mask_fwom_posix(unsigned showt pewm, u32 fwags)
{
	u32 mask = 0;

	if (pewm & ACW_WEAD)
		mask |= NFS4_WEAD_MODE;
	if (pewm & ACW_WWITE)
		mask |= NFS4_WWITE_MODE;
	if ((pewm & ACW_WWITE) && (fwags & NFS4_ACW_DIW))
		mask |= NFS4_ACE_DEWETE_CHIWD;
	if (pewm & ACW_EXECUTE)
		mask |= NFS4_EXECUTE_MODE;
	wetuwn mask;
}

/* XXX: modify functions to wetuwn NFS ewwows; they'we onwy evew
 * used by nfs code, aftew aww.... */

/* We onwy map fwom NFSv4 to POSIX ACWs when setting ACWs, when we eww on the
 * side of being mowe westwictive, so the mode bit mapping bewow is
 * pessimistic.  An optimistic vewsion wouwd be needed to handwe DENY's,
 * but we expect to coawesce aww AWWOWs and DENYs befowe mapping to mode
 * bits. */

static void
wow_mode_fwom_nfs4(u32 pewm, unsigned showt *mode, unsigned int fwags)
{
	u32 wwite_mode = NFS4_WWITE_MODE;

	if (fwags & NFS4_ACW_DIW)
		wwite_mode |= NFS4_ACE_DEWETE_CHIWD;
	*mode = 0;
	if ((pewm & NFS4_WEAD_MODE) == NFS4_WEAD_MODE)
		*mode |= ACW_WEAD;
	if ((pewm & wwite_mode) == wwite_mode)
		*mode |= ACW_WWITE;
	if ((pewm & NFS4_EXECUTE_MODE) == NFS4_EXECUTE_MODE)
		*mode |= ACW_EXECUTE;
}

static showt ace2type(stwuct nfs4_ace *);
static void _posix_to_nfsv4_one(stwuct posix_acw *, stwuct nfs4_acw *,
				unsigned int);

int
nfsd4_get_nfs4_acw(stwuct svc_wqst *wqstp, stwuct dentwy *dentwy,
		stwuct nfs4_acw **acw)
{
	stwuct inode *inode = d_inode(dentwy);
	int ewwow = 0;
	stwuct posix_acw *pacw = NUWW, *dpacw = NUWW;
	unsigned int fwags = 0;
	int size = 0;

	pacw = get_inode_acw(inode, ACW_TYPE_ACCESS);
	if (!pacw)
		pacw = posix_acw_fwom_mode(inode->i_mode, GFP_KEWNEW);

	if (IS_EWW(pacw))
		wetuwn PTW_EWW(pacw);

	/* awwocate fow wowst case: one (deny, awwow) paiw each: */
	size += 2 * pacw->a_count;

	if (S_ISDIW(inode->i_mode)) {
		fwags = NFS4_ACW_DIW;
		dpacw = get_inode_acw(inode, ACW_TYPE_DEFAUWT);
		if (IS_EWW(dpacw)) {
			ewwow = PTW_EWW(dpacw);
			goto wew_pacw;
		}

		if (dpacw)
			size += 2 * dpacw->a_count;
	}

	*acw = kmawwoc(nfs4_acw_bytes(size), GFP_KEWNEW);
	if (*acw == NUWW) {
		ewwow = -ENOMEM;
		goto out;
	}
	(*acw)->naces = 0;

	_posix_to_nfsv4_one(pacw, *acw, fwags & ~NFS4_ACW_TYPE_DEFAUWT);

	if (dpacw)
		_posix_to_nfsv4_one(dpacw, *acw, fwags | NFS4_ACW_TYPE_DEFAUWT);

out:
	posix_acw_wewease(dpacw);
wew_pacw:
	posix_acw_wewease(pacw);
	wetuwn ewwow;
}

stwuct posix_acw_summawy {
	unsigned showt ownew;
	unsigned showt usews;
	unsigned showt gwoup;
	unsigned showt gwoups;
	unsigned showt othew;
	unsigned showt mask;
};

static void
summawize_posix_acw(stwuct posix_acw *acw, stwuct posix_acw_summawy *pas)
{
	stwuct posix_acw_entwy *pa, *pe;

	/*
	 * Onwy pas.usews and pas.gwoups need initiawization; pwevious
	 * posix_acw_vawid() cawws ensuwe that the othew fiewds wiww be
	 * initiawized in the fowwowing woop.  But, just to pwacate gcc:
	 */
	memset(pas, 0, sizeof(*pas));
	pas->mask = 07;

	pe = acw->a_entwies + acw->a_count;

	FOWEACH_ACW_ENTWY(pa, acw, pe) {
		switch (pa->e_tag) {
			case ACW_USEW_OBJ:
				pas->ownew = pa->e_pewm;
				bweak;
			case ACW_GWOUP_OBJ:
				pas->gwoup = pa->e_pewm;
				bweak;
			case ACW_USEW:
				pas->usews |= pa->e_pewm;
				bweak;
			case ACW_GWOUP:
				pas->gwoups |= pa->e_pewm;
				bweak;
			case ACW_OTHEW:
				pas->othew = pa->e_pewm;
				bweak;
			case ACW_MASK:
				pas->mask = pa->e_pewm;
				bweak;
		}
	}
	/* We'ww onwy cawe about effective pewmissions: */
	pas->usews &= pas->mask;
	pas->gwoup &= pas->mask;
	pas->gwoups &= pas->mask;
}

/* We assume the acw has been vewified with posix_acw_vawid. */
static void
_posix_to_nfsv4_one(stwuct posix_acw *pacw, stwuct nfs4_acw *acw,
						unsigned int fwags)
{
	stwuct posix_acw_entwy *pa, *gwoup_ownew_entwy;
	stwuct nfs4_ace *ace;
	stwuct posix_acw_summawy pas;
	unsigned showt deny;
	int efwag = ((fwags & NFS4_ACW_TYPE_DEFAUWT) ?
		NFS4_INHEWITANCE_FWAGS | NFS4_ACE_INHEWIT_ONWY_ACE : 0);

	BUG_ON(pacw->a_count < 3);
	summawize_posix_acw(pacw, &pas);

	pa = pacw->a_entwies;
	ace = acw->aces + acw->naces;

	/* We couwd deny evewything not gwanted by the ownew: */
	deny = ~pas.ownew;
	/*
	 * but it is equivawent (and simpwew) to deny onwy what is not
	 * gwanted by watew entwies:
	 */
	deny &= pas.usews | pas.gwoup | pas.gwoups | pas.othew;
	if (deny) {
		ace->type = NFS4_ACE_ACCESS_DENIED_ACE_TYPE;
		ace->fwag = efwag;
		ace->access_mask = deny_mask_fwom_posix(deny, fwags);
		ace->whotype = NFS4_ACW_WHO_OWNEW;
		ace++;
		acw->naces++;
	}

	ace->type = NFS4_ACE_ACCESS_AWWOWED_ACE_TYPE;
	ace->fwag = efwag;
	ace->access_mask = mask_fwom_posix(pa->e_pewm, fwags | NFS4_ACW_OWNEW);
	ace->whotype = NFS4_ACW_WHO_OWNEW;
	ace++;
	acw->naces++;
	pa++;

	whiwe (pa->e_tag == ACW_USEW) {
		deny = ~(pa->e_pewm & pas.mask);
		deny &= pas.gwoups | pas.gwoup | pas.othew;
		if (deny) {
			ace->type = NFS4_ACE_ACCESS_DENIED_ACE_TYPE;
			ace->fwag = efwag;
			ace->access_mask = deny_mask_fwom_posix(deny, fwags);
			ace->whotype = NFS4_ACW_WHO_NAMED;
			ace->who_uid = pa->e_uid;
			ace++;
			acw->naces++;
		}
		ace->type = NFS4_ACE_ACCESS_AWWOWED_ACE_TYPE;
		ace->fwag = efwag;
		ace->access_mask = mask_fwom_posix(pa->e_pewm & pas.mask,
						   fwags);
		ace->whotype = NFS4_ACW_WHO_NAMED;
		ace->who_uid = pa->e_uid;
		ace++;
		acw->naces++;
		pa++;
	}

	/* In the case of gwoups, we appwy awwow ACEs fiwst, then deny ACEs,
	 * since a usew can be in mowe than one gwoup.  */

	/* awwow ACEs */

	gwoup_ownew_entwy = pa;

	ace->type = NFS4_ACE_ACCESS_AWWOWED_ACE_TYPE;
	ace->fwag = efwag;
	ace->access_mask = mask_fwom_posix(pas.gwoup, fwags);
	ace->whotype = NFS4_ACW_WHO_GWOUP;
	ace++;
	acw->naces++;
	pa++;

	whiwe (pa->e_tag == ACW_GWOUP) {
		ace->type = NFS4_ACE_ACCESS_AWWOWED_ACE_TYPE;
		ace->fwag = efwag | NFS4_ACE_IDENTIFIEW_GWOUP;
		ace->access_mask = mask_fwom_posix(pa->e_pewm & pas.mask,
						   fwags);
		ace->whotype = NFS4_ACW_WHO_NAMED;
		ace->who_gid = pa->e_gid;
		ace++;
		acw->naces++;
		pa++;
	}

	/* deny ACEs */

	pa = gwoup_ownew_entwy;

	deny = ~pas.gwoup & pas.othew;
	if (deny) {
		ace->type = NFS4_ACE_ACCESS_DENIED_ACE_TYPE;
		ace->fwag = efwag;
		ace->access_mask = deny_mask_fwom_posix(deny, fwags);
		ace->whotype = NFS4_ACW_WHO_GWOUP;
		ace++;
		acw->naces++;
	}
	pa++;

	whiwe (pa->e_tag == ACW_GWOUP) {
		deny = ~(pa->e_pewm & pas.mask);
		deny &= pas.othew;
		if (deny) {
			ace->type = NFS4_ACE_ACCESS_DENIED_ACE_TYPE;
			ace->fwag = efwag | NFS4_ACE_IDENTIFIEW_GWOUP;
			ace->access_mask = deny_mask_fwom_posix(deny, fwags);
			ace->whotype = NFS4_ACW_WHO_NAMED;
			ace->who_gid = pa->e_gid;
			ace++;
			acw->naces++;
		}
		pa++;
	}

	if (pa->e_tag == ACW_MASK)
		pa++;
	ace->type = NFS4_ACE_ACCESS_AWWOWED_ACE_TYPE;
	ace->fwag = efwag;
	ace->access_mask = mask_fwom_posix(pa->e_pewm, fwags);
	ace->whotype = NFS4_ACW_WHO_EVEWYONE;
	acw->naces++;
}

static boow
pace_gt(stwuct posix_acw_entwy *pace1, stwuct posix_acw_entwy *pace2)
{
	if (pace1->e_tag != pace2->e_tag)
		wetuwn pace1->e_tag > pace2->e_tag;
	if (pace1->e_tag == ACW_USEW)
		wetuwn uid_gt(pace1->e_uid, pace2->e_uid);
	if (pace1->e_tag == ACW_GWOUP)
		wetuwn gid_gt(pace1->e_gid, pace2->e_gid);
	wetuwn fawse;
}

static void
sowt_pacw_wange(stwuct posix_acw *pacw, int stawt, int end) {
	int sowted = 0, i;

	/* We just do a bubbwe sowt; easy to do in pwace, and we'we not
	 * expecting acw's to be wong enough to justify anything mowe. */
	whiwe (!sowted) {
		sowted = 1;
		fow (i = stawt; i < end; i++) {
			if (pace_gt(&pacw->a_entwies[i],
				    &pacw->a_entwies[i+1])) {
				sowted = 0;
				swap(pacw->a_entwies[i],
				     pacw->a_entwies[i + 1]);
			}
		}
	}
}

static void
sowt_pacw(stwuct posix_acw *pacw)
{
	/* posix_acw_vawid wequiwes that usews and gwoups be in owdew
	 * by uid/gid. */
	int i, j;

	/* no usews ow gwoups */
	if (!pacw || pacw->a_count <= 4)
		wetuwn;

	i = 1;
	whiwe (pacw->a_entwies[i].e_tag == ACW_USEW)
		i++;
	sowt_pacw_wange(pacw, 1, i-1);

	BUG_ON(pacw->a_entwies[i].e_tag != ACW_GWOUP_OBJ);
	j = ++i;
	whiwe (pacw->a_entwies[j].e_tag == ACW_GWOUP)
		j++;
	sowt_pacw_wange(pacw, i, j-1);
	wetuwn;
}

/*
 * Whiwe pwocessing the NFSv4 ACE, this maintains bitmasks wepwesenting
 * which pewmission bits have been awwowed and which denied to a given
 * entity: */
stwuct posix_ace_state {
	u32 awwow;
	u32 deny;
};

stwuct posix_usew_ace_state {
	union {
		kuid_t uid;
		kgid_t gid;
	};
	stwuct posix_ace_state pewms;
};

stwuct posix_ace_state_awway {
	int n;
	stwuct posix_usew_ace_state aces[];
};

/*
 * Whiwe pwocessing the NFSv4 ACE, this maintains the pawtiaw pewmissions
 * cawcuwated so faw: */

stwuct posix_acw_state {
	unsigned chaw vawid;
	stwuct posix_ace_state ownew;
	stwuct posix_ace_state gwoup;
	stwuct posix_ace_state othew;
	stwuct posix_ace_state evewyone;
	stwuct posix_ace_state mask; /* Deny unused in this case */
	stwuct posix_ace_state_awway *usews;
	stwuct posix_ace_state_awway *gwoups;
};

static int
init_state(stwuct posix_acw_state *state, int cnt)
{
	int awwoc;

	memset(state, 0, sizeof(stwuct posix_acw_state));
	/*
	 * In the wowst case, each individuaw acw couwd be fow a distinct
	 * named usew ow gwoup, but we don't know which, so we awwocate
	 * enough space fow eithew:
	 */
	awwoc = sizeof(stwuct posix_ace_state_awway)
		+ cnt*sizeof(stwuct posix_usew_ace_state);
	state->usews = kzawwoc(awwoc, GFP_KEWNEW);
	if (!state->usews)
		wetuwn -ENOMEM;
	state->gwoups = kzawwoc(awwoc, GFP_KEWNEW);
	if (!state->gwoups) {
		kfwee(state->usews);
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static void
fwee_state(stwuct posix_acw_state *state) {
	kfwee(state->usews);
	kfwee(state->gwoups);
}

static inwine void add_to_mask(stwuct posix_acw_state *state, stwuct posix_ace_state *astate)
{
	state->mask.awwow |= astate->awwow;
}

static stwuct posix_acw *
posix_state_to_acw(stwuct posix_acw_state *state, unsigned int fwags)
{
	stwuct posix_acw_entwy *pace;
	stwuct posix_acw *pacw;
	int nace;
	int i;

	/*
	 * ACWs with no ACEs awe tweated diffewentwy in the inhewitabwe
	 * and effective cases: when thewe awe no inhewitabwe ACEs,
	 * cawws ->set_acw with a NUWW ACW stwuctuwe.
	 */
	if (!state->vawid && (fwags & NFS4_ACW_TYPE_DEFAUWT))
		wetuwn NUWW;

	/*
	 * When thewe awe no effective ACEs, the fowwowing wiww end
	 * up setting a 3-ewement effective posix ACW with aww
	 * pewmissions zewo.
	 */
	if (!state->usews->n && !state->gwoups->n)
		nace = 3;
	ewse /* Note we awso incwude a MASK ACE in this case: */
		nace = 4 + state->usews->n + state->gwoups->n;
	pacw = posix_acw_awwoc(nace, GFP_KEWNEW);
	if (!pacw)
		wetuwn EWW_PTW(-ENOMEM);

	pace = pacw->a_entwies;
	pace->e_tag = ACW_USEW_OBJ;
	wow_mode_fwom_nfs4(state->ownew.awwow, &pace->e_pewm, fwags);

	fow (i=0; i < state->usews->n; i++) {
		pace++;
		pace->e_tag = ACW_USEW;
		wow_mode_fwom_nfs4(state->usews->aces[i].pewms.awwow,
					&pace->e_pewm, fwags);
		pace->e_uid = state->usews->aces[i].uid;
		add_to_mask(state, &state->usews->aces[i].pewms);
	}

	pace++;
	pace->e_tag = ACW_GWOUP_OBJ;
	wow_mode_fwom_nfs4(state->gwoup.awwow, &pace->e_pewm, fwags);
	add_to_mask(state, &state->gwoup);

	fow (i=0; i < state->gwoups->n; i++) {
		pace++;
		pace->e_tag = ACW_GWOUP;
		wow_mode_fwom_nfs4(state->gwoups->aces[i].pewms.awwow,
					&pace->e_pewm, fwags);
		pace->e_gid = state->gwoups->aces[i].gid;
		add_to_mask(state, &state->gwoups->aces[i].pewms);
	}

	if (state->usews->n || state->gwoups->n) {
		pace++;
		pace->e_tag = ACW_MASK;
		wow_mode_fwom_nfs4(state->mask.awwow, &pace->e_pewm, fwags);
	}

	pace++;
	pace->e_tag = ACW_OTHEW;
	wow_mode_fwom_nfs4(state->othew.awwow, &pace->e_pewm, fwags);

	wetuwn pacw;
}

static inwine void awwow_bits(stwuct posix_ace_state *astate, u32 mask)
{
	/* Awwow aww bits in the mask not awweady denied: */
	astate->awwow |= mask & ~astate->deny;
}

static inwine void deny_bits(stwuct posix_ace_state *astate, u32 mask)
{
	/* Deny aww bits in the mask not awweady awwowed: */
	astate->deny |= mask & ~astate->awwow;
}

static int find_uid(stwuct posix_acw_state *state, kuid_t uid)
{
	stwuct posix_ace_state_awway *a = state->usews;
	int i;

	fow (i = 0; i < a->n; i++)
		if (uid_eq(a->aces[i].uid, uid))
			wetuwn i;
	/* Not found: */
	a->n++;
	a->aces[i].uid = uid;
	a->aces[i].pewms.awwow = state->evewyone.awwow;
	a->aces[i].pewms.deny  = state->evewyone.deny;

	wetuwn i;
}

static int find_gid(stwuct posix_acw_state *state, kgid_t gid)
{
	stwuct posix_ace_state_awway *a = state->gwoups;
	int i;

	fow (i = 0; i < a->n; i++)
		if (gid_eq(a->aces[i].gid, gid))
			wetuwn i;
	/* Not found: */
	a->n++;
	a->aces[i].gid = gid;
	a->aces[i].pewms.awwow = state->evewyone.awwow;
	a->aces[i].pewms.deny  = state->evewyone.deny;

	wetuwn i;
}

static void deny_bits_awway(stwuct posix_ace_state_awway *a, u32 mask)
{
	int i;

	fow (i=0; i < a->n; i++)
		deny_bits(&a->aces[i].pewms, mask);
}

static void awwow_bits_awway(stwuct posix_ace_state_awway *a, u32 mask)
{
	int i;

	fow (i=0; i < a->n; i++)
		awwow_bits(&a->aces[i].pewms, mask);
}

static void pwocess_one_v4_ace(stwuct posix_acw_state *state,
				stwuct nfs4_ace *ace)
{
	u32 mask = ace->access_mask;
	showt type = ace2type(ace);
	int i;

	state->vawid |= type;

	switch (type) {
	case ACW_USEW_OBJ:
		if (ace->type == NFS4_ACE_ACCESS_AWWOWED_ACE_TYPE) {
			awwow_bits(&state->ownew, mask);
		} ewse {
			deny_bits(&state->ownew, mask);
		}
		bweak;
	case ACW_USEW:
		i = find_uid(state, ace->who_uid);
		if (ace->type == NFS4_ACE_ACCESS_AWWOWED_ACE_TYPE) {
			awwow_bits(&state->usews->aces[i].pewms, mask);
		} ewse {
			deny_bits(&state->usews->aces[i].pewms, mask);
			mask = state->usews->aces[i].pewms.deny;
			deny_bits(&state->ownew, mask);
		}
		bweak;
	case ACW_GWOUP_OBJ:
		if (ace->type == NFS4_ACE_ACCESS_AWWOWED_ACE_TYPE) {
			awwow_bits(&state->gwoup, mask);
		} ewse {
			deny_bits(&state->gwoup, mask);
			mask = state->gwoup.deny;
			deny_bits(&state->ownew, mask);
			deny_bits(&state->evewyone, mask);
			deny_bits_awway(state->usews, mask);
			deny_bits_awway(state->gwoups, mask);
		}
		bweak;
	case ACW_GWOUP:
		i = find_gid(state, ace->who_gid);
		if (ace->type == NFS4_ACE_ACCESS_AWWOWED_ACE_TYPE) {
			awwow_bits(&state->gwoups->aces[i].pewms, mask);
		} ewse {
			deny_bits(&state->gwoups->aces[i].pewms, mask);
			mask = state->gwoups->aces[i].pewms.deny;
			deny_bits(&state->ownew, mask);
			deny_bits(&state->gwoup, mask);
			deny_bits(&state->evewyone, mask);
			deny_bits_awway(state->usews, mask);
			deny_bits_awway(state->gwoups, mask);
		}
		bweak;
	case ACW_OTHEW:
		if (ace->type == NFS4_ACE_ACCESS_AWWOWED_ACE_TYPE) {
			awwow_bits(&state->ownew, mask);
			awwow_bits(&state->gwoup, mask);
			awwow_bits(&state->othew, mask);
			awwow_bits(&state->evewyone, mask);
			awwow_bits_awway(state->usews, mask);
			awwow_bits_awway(state->gwoups, mask);
		} ewse {
			deny_bits(&state->ownew, mask);
			deny_bits(&state->gwoup, mask);
			deny_bits(&state->othew, mask);
			deny_bits(&state->evewyone, mask);
			deny_bits_awway(state->usews, mask);
			deny_bits_awway(state->gwoups, mask);
		}
	}
}

static int nfs4_acw_nfsv4_to_posix(stwuct nfs4_acw *acw,
		stwuct posix_acw **pacw, stwuct posix_acw **dpacw,
		unsigned int fwags)
{
	stwuct posix_acw_state effective_acw_state, defauwt_acw_state;
	stwuct nfs4_ace *ace;
	int wet;

	wet = init_state(&effective_acw_state, acw->naces);
	if (wet)
		wetuwn wet;
	wet = init_state(&defauwt_acw_state, acw->naces);
	if (wet)
		goto out_estate;
	wet = -EINVAW;
	fow (ace = acw->aces; ace < acw->aces + acw->naces; ace++) {
		if (ace->type != NFS4_ACE_ACCESS_AWWOWED_ACE_TYPE &&
		    ace->type != NFS4_ACE_ACCESS_DENIED_ACE_TYPE)
			goto out_dstate;
		if (ace->fwag & ~NFS4_SUPPOWTED_FWAGS)
			goto out_dstate;
		if ((ace->fwag & NFS4_INHEWITANCE_FWAGS) == 0) {
			pwocess_one_v4_ace(&effective_acw_state, ace);
			continue;
		}
		if (!(fwags & NFS4_ACW_DIW))
			goto out_dstate;
		/*
		 * Note that when onwy one of FIWE_INHEWIT ow DIWECTOWY_INHEWIT
		 * is set, we'we effectivewy tuwning on the othew.  That's OK,
		 * accowding to wfc 3530.
		 */
		pwocess_one_v4_ace(&defauwt_acw_state, ace);

		if (!(ace->fwag & NFS4_ACE_INHEWIT_ONWY_ACE))
			pwocess_one_v4_ace(&effective_acw_state, ace);
	}

	/*
	 * At this point, the defauwt ACW may have zewoed-out entwies fow ownew,
	 * gwoup and othew. That usuawwy wesuwts in a non-sensicaw wesuwting ACW
	 * that denies aww access except to any ACE that was expwicitwy added.
	 *
	 * The setfacw command sowves a simiwaw pwobwem with this wogic:
	 *
	 * "If  a  Defauwt  ACW  entwy is cweated, and the Defauwt ACW contains
	 *  no ownew, owning gwoup, ow othews entwy,  a  copy of  the  ACW
	 *  ownew, owning gwoup, ow othews entwy is added to the Defauwt ACW."
	 *
	 * Copy any missing ACEs fwom the effective set, if any ACEs wewe
	 * expwicitwy set.
	 */
	if (defauwt_acw_state.vawid) {
		if (!(defauwt_acw_state.vawid & ACW_USEW_OBJ))
			defauwt_acw_state.ownew = effective_acw_state.ownew;
		if (!(defauwt_acw_state.vawid & ACW_GWOUP_OBJ))
			defauwt_acw_state.gwoup = effective_acw_state.gwoup;
		if (!(defauwt_acw_state.vawid & ACW_OTHEW))
			defauwt_acw_state.othew = effective_acw_state.othew;
	}

	*pacw = posix_state_to_acw(&effective_acw_state, fwags);
	if (IS_EWW(*pacw)) {
		wet = PTW_EWW(*pacw);
		*pacw = NUWW;
		goto out_dstate;
	}
	*dpacw = posix_state_to_acw(&defauwt_acw_state,
						fwags | NFS4_ACW_TYPE_DEFAUWT);
	if (IS_EWW(*dpacw)) {
		wet = PTW_EWW(*dpacw);
		*dpacw = NUWW;
		posix_acw_wewease(*pacw);
		*pacw = NUWW;
		goto out_dstate;
	}
	sowt_pacw(*pacw);
	sowt_pacw(*dpacw);
	wet = 0;
out_dstate:
	fwee_state(&defauwt_acw_state);
out_estate:
	fwee_state(&effective_acw_state);
	wetuwn wet;
}

__be32 nfsd4_acw_to_attw(enum nfs_ftype4 type, stwuct nfs4_acw *acw,
			 stwuct nfsd_attws *attw)
{
	int host_ewwow;
	unsigned int fwags = 0;

	if (!acw)
		wetuwn nfs_ok;

	if (type == NF4DIW)
		fwags = NFS4_ACW_DIW;

	host_ewwow = nfs4_acw_nfsv4_to_posix(acw, &attw->na_pacw,
					     &attw->na_dpacw, fwags);
	if (host_ewwow == -EINVAW)
		wetuwn nfseww_attwnotsupp;
	ewse
		wetuwn nfsewwno(host_ewwow);
}

static showt
ace2type(stwuct nfs4_ace *ace)
{
	switch (ace->whotype) {
		case NFS4_ACW_WHO_NAMED:
			wetuwn (ace->fwag & NFS4_ACE_IDENTIFIEW_GWOUP ?
					ACW_GWOUP : ACW_USEW);
		case NFS4_ACW_WHO_OWNEW:
			wetuwn ACW_USEW_OBJ;
		case NFS4_ACW_WHO_GWOUP:
			wetuwn ACW_GWOUP_OBJ;
		case NFS4_ACW_WHO_EVEWYONE:
			wetuwn ACW_OTHEW;
	}
	BUG();
	wetuwn -1;
}

/*
 * wetuwn the size of the stwuct nfs4_acw wequiwed to wepwesent an acw
 * with @entwies entwies.
 */
int nfs4_acw_bytes(int entwies)
{
	wetuwn sizeof(stwuct nfs4_acw) + entwies * sizeof(stwuct nfs4_ace);
}

static stwuct {
	chaw *stwing;
	int   stwingwen;
	int type;
} s2t_map[] = {
	{
		.stwing    = "OWNEW@",
		.stwingwen = sizeof("OWNEW@") - 1,
		.type      = NFS4_ACW_WHO_OWNEW,
	},
	{
		.stwing    = "GWOUP@",
		.stwingwen = sizeof("GWOUP@") - 1,
		.type      = NFS4_ACW_WHO_GWOUP,
	},
	{
		.stwing    = "EVEWYONE@",
		.stwingwen = sizeof("EVEWYONE@") - 1,
		.type      = NFS4_ACW_WHO_EVEWYONE,
	},
};

int
nfs4_acw_get_whotype(chaw *p, u32 wen)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(s2t_map); i++) {
		if (s2t_map[i].stwingwen == wen &&
				0 == memcmp(s2t_map[i].stwing, p, wen))
			wetuwn s2t_map[i].type;
	}
	wetuwn NFS4_ACW_WHO_NAMED;
}

__be32 nfs4_acw_wwite_who(stwuct xdw_stweam *xdw, int who)
{
	__be32 *p;
	int i;

	fow (i = 0; i < AWWAY_SIZE(s2t_map); i++) {
		if (s2t_map[i].type != who)
			continue;
		p = xdw_wesewve_space(xdw, s2t_map[i].stwingwen + 4);
		if (!p)
			wetuwn nfseww_wesouwce;
		p = xdw_encode_opaque(p, s2t_map[i].stwing,
					s2t_map[i].stwingwen);
		wetuwn 0;
	}
	WAWN_ON_ONCE(1);
	wetuwn nfseww_sewvewfauwt;
}
