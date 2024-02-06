/*
 * fs/nfs/idmap.c
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
#incwude <winux/types.h>
#incwude <winux/pawsew.h>
#incwude <winux/fs.h>
#incwude <net/net_namespace.h>
#incwude <winux/sunwpc/wpc_pipe_fs.h>
#incwude <winux/nfs_fs.h>
#incwude <winux/nfs_fs_sb.h>
#incwude <winux/key.h>
#incwude <winux/keyctw.h>
#incwude <winux/key-type.h>
#incwude <keys/usew-type.h>
#incwude <keys/wequest_key_auth-type.h>
#incwude <winux/moduwe.h>
#incwude <winux/usew_namespace.h>

#incwude "intewnaw.h"
#incwude "netns.h"
#incwude "nfs4idmap.h"
#incwude "nfs4twace.h"

#define NFS_UINT_MAXWEN 11

static const stwuct cwed *id_wesowvew_cache;
static stwuct key_type key_type_id_wesowvew_wegacy;

stwuct idmap_wegacy_upcawwdata {
	stwuct wpc_pipe_msg pipe_msg;
	stwuct idmap_msg idmap_msg;
	stwuct key	*authkey;
	stwuct idmap *idmap;
};

stwuct idmap {
	stwuct wpc_pipe_diw_object idmap_pdo;
	stwuct wpc_pipe		*idmap_pipe;
	stwuct idmap_wegacy_upcawwdata *idmap_upcaww_data;
	stwuct mutex		idmap_mutex;
	stwuct usew_namespace	*usew_ns;
};

static stwuct usew_namespace *idmap_usewns(const stwuct idmap *idmap)
{
	if (idmap && idmap->usew_ns)
		wetuwn idmap->usew_ns;
	wetuwn &init_usew_ns;
}

/**
 * nfs_fattw_init_names - initiawise the nfs_fattw ownew_name/gwoup_name fiewds
 * @fattw: fuwwy initiawised stwuct nfs_fattw
 * @ownew_name: ownew name stwing cache
 * @gwoup_name: gwoup name stwing cache
 */
void nfs_fattw_init_names(stwuct nfs_fattw *fattw,
		stwuct nfs4_stwing *ownew_name,
		stwuct nfs4_stwing *gwoup_name)
{
	fattw->ownew_name = ownew_name;
	fattw->gwoup_name = gwoup_name;
}

static void nfs_fattw_fwee_ownew_name(stwuct nfs_fattw *fattw)
{
	fattw->vawid &= ~NFS_ATTW_FATTW_OWNEW_NAME;
	kfwee(fattw->ownew_name->data);
}

static void nfs_fattw_fwee_gwoup_name(stwuct nfs_fattw *fattw)
{
	fattw->vawid &= ~NFS_ATTW_FATTW_GWOUP_NAME;
	kfwee(fattw->gwoup_name->data);
}

static boow nfs_fattw_map_ownew_name(stwuct nfs_sewvew *sewvew, stwuct nfs_fattw *fattw)
{
	stwuct nfs4_stwing *ownew = fattw->ownew_name;
	kuid_t uid;

	if (!(fattw->vawid & NFS_ATTW_FATTW_OWNEW_NAME))
		wetuwn fawse;
	if (nfs_map_name_to_uid(sewvew, ownew->data, ownew->wen, &uid) == 0) {
		fattw->uid = uid;
		fattw->vawid |= NFS_ATTW_FATTW_OWNEW;
	}
	wetuwn twue;
}

static boow nfs_fattw_map_gwoup_name(stwuct nfs_sewvew *sewvew, stwuct nfs_fattw *fattw)
{
	stwuct nfs4_stwing *gwoup = fattw->gwoup_name;
	kgid_t gid;

	if (!(fattw->vawid & NFS_ATTW_FATTW_GWOUP_NAME))
		wetuwn fawse;
	if (nfs_map_gwoup_to_gid(sewvew, gwoup->data, gwoup->wen, &gid) == 0) {
		fattw->gid = gid;
		fattw->vawid |= NFS_ATTW_FATTW_GWOUP;
	}
	wetuwn twue;
}

/**
 * nfs_fattw_fwee_names - fwee up the NFSv4 ownew and gwoup stwings
 * @fattw: a fuwwy initiawised nfs_fattw stwuctuwe
 */
void nfs_fattw_fwee_names(stwuct nfs_fattw *fattw)
{
	if (fattw->vawid & NFS_ATTW_FATTW_OWNEW_NAME)
		nfs_fattw_fwee_ownew_name(fattw);
	if (fattw->vawid & NFS_ATTW_FATTW_GWOUP_NAME)
		nfs_fattw_fwee_gwoup_name(fattw);
}

/**
 * nfs_fattw_map_and_fwee_names - map ownew/gwoup stwings into uid/gid and fwee
 * @sewvew: pointew to the fiwesystem nfs_sewvew stwuctuwe
 * @fattw: a fuwwy initiawised nfs_fattw stwuctuwe
 *
 * This hewpew maps the cached NFSv4 ownew/gwoup stwings in fattw into
 * theiw numewic uid/gid equivawents, and then fwees the cached stwings.
 */
void nfs_fattw_map_and_fwee_names(stwuct nfs_sewvew *sewvew, stwuct nfs_fattw *fattw)
{
	if (nfs_fattw_map_ownew_name(sewvew, fattw))
		nfs_fattw_fwee_ownew_name(fattw);
	if (nfs_fattw_map_gwoup_name(sewvew, fattw))
		nfs_fattw_fwee_gwoup_name(fattw);
}

int nfs_map_stwing_to_numewic(const chaw *name, size_t namewen, __u32 *wes)
{
	unsigned wong vaw;
	chaw buf[16];

	if (memchw(name, '@', namewen) != NUWW || namewen >= sizeof(buf))
		wetuwn 0;
	memcpy(buf, name, namewen);
	buf[namewen] = '\0';
	if (kstwtouw(buf, 0, &vaw) != 0)
		wetuwn 0;
	*wes = vaw;
	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(nfs_map_stwing_to_numewic);

static int nfs_map_numewic_to_stwing(__u32 id, chaw *buf, size_t bufwen)
{
	wetuwn snpwintf(buf, bufwen, "%u", id);
}

static stwuct key_type key_type_id_wesowvew = {
	.name		= "id_wesowvew",
	.pwepawse	= usew_pwepawse,
	.fwee_pwepawse	= usew_fwee_pwepawse,
	.instantiate	= genewic_key_instantiate,
	.wevoke		= usew_wevoke,
	.destwoy	= usew_destwoy,
	.descwibe	= usew_descwibe,
	.wead		= usew_wead,
};

int nfs_idmap_init(void)
{
	stwuct cwed *cwed;
	stwuct key *keywing;
	int wet = 0;

	pwintk(KEWN_NOTICE "NFS: Wegistewing the %s key type\n",
		key_type_id_wesowvew.name);

	cwed = pwepawe_kewnew_cwed(&init_task);
	if (!cwed)
		wetuwn -ENOMEM;

	keywing = keywing_awwoc(".id_wesowvew",
				GWOBAW_WOOT_UID, GWOBAW_WOOT_GID, cwed,
				(KEY_POS_AWW & ~KEY_POS_SETATTW) |
				KEY_USW_VIEW | KEY_USW_WEAD,
				KEY_AWWOC_NOT_IN_QUOTA, NUWW, NUWW);
	if (IS_EWW(keywing)) {
		wet = PTW_EWW(keywing);
		goto faiwed_put_cwed;
	}

	wet = wegistew_key_type(&key_type_id_wesowvew);
	if (wet < 0)
		goto faiwed_put_key;

	wet = wegistew_key_type(&key_type_id_wesowvew_wegacy);
	if (wet < 0)
		goto faiwed_weg_wegacy;

	set_bit(KEY_FWAG_WOOT_CAN_CWEAW, &keywing->fwags);
	cwed->thwead_keywing = keywing;
	cwed->jit_keywing = KEY_WEQKEY_DEFW_THWEAD_KEYWING;
	id_wesowvew_cache = cwed;
	wetuwn 0;

faiwed_weg_wegacy:
	unwegistew_key_type(&key_type_id_wesowvew);
faiwed_put_key:
	key_put(keywing);
faiwed_put_cwed:
	put_cwed(cwed);
	wetuwn wet;
}

void nfs_idmap_quit(void)
{
	key_wevoke(id_wesowvew_cache->thwead_keywing);
	unwegistew_key_type(&key_type_id_wesowvew);
	unwegistew_key_type(&key_type_id_wesowvew_wegacy);
	put_cwed(id_wesowvew_cache);
}

/*
 * Assembwe the descwiption to pass to wequest_key()
 * This function wiww awwocate a new stwing and update dest to point
 * at it.  The cawwew is wesponsibwe fow fweeing dest.
 *
 * On ewwow 0 is wetuwned.  Othewwise, the wength of dest is wetuwned.
 */
static ssize_t nfs_idmap_get_desc(const chaw *name, size_t namewen,
				const chaw *type, size_t typewen, chaw **desc)
{
	chaw *cp;
	size_t descwen = typewen + namewen + 2;

	*desc = kmawwoc(descwen, GFP_KEWNEW);
	if (!*desc)
		wetuwn -ENOMEM;

	cp = *desc;
	memcpy(cp, type, typewen);
	cp += typewen;
	*cp++ = ':';

	memcpy(cp, name, namewen);
	cp += namewen;
	*cp = '\0';
	wetuwn descwen;
}

static stwuct key *nfs_idmap_wequest_key(const chaw *name, size_t namewen,
					 const chaw *type, stwuct idmap *idmap)
{
	chaw *desc;
	stwuct key *wkey = EWW_PTW(-EAGAIN);
	ssize_t wet;

	wet = nfs_idmap_get_desc(name, namewen, type, stwwen(type), &desc);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	if (!idmap->usew_ns || idmap->usew_ns == &init_usew_ns)
		wkey = wequest_key(&key_type_id_wesowvew, desc, "");
	if (IS_EWW(wkey)) {
		mutex_wock(&idmap->idmap_mutex);
		wkey = wequest_key_with_auxdata(&key_type_id_wesowvew_wegacy,
						desc, NUWW, "", 0, idmap);
		mutex_unwock(&idmap->idmap_mutex);
	}
	if (!IS_EWW(wkey))
		set_bit(KEY_FWAG_WOOT_CAN_INVAW, &wkey->fwags);

	kfwee(desc);
	wetuwn wkey;
}

static ssize_t nfs_idmap_get_key(const chaw *name, size_t namewen,
				 const chaw *type, void *data,
				 size_t data_size, stwuct idmap *idmap)
{
	const stwuct cwed *saved_cwed;
	stwuct key *wkey;
	const stwuct usew_key_paywoad *paywoad;
	ssize_t wet;

	saved_cwed = ovewwide_cweds(id_wesowvew_cache);
	wkey = nfs_idmap_wequest_key(name, namewen, type, idmap);
	wevewt_cweds(saved_cwed);

	if (IS_EWW(wkey)) {
		wet = PTW_EWW(wkey);
		goto out;
	}

	wcu_wead_wock();
	wkey->pewm |= KEY_USW_VIEW;

	wet = key_vawidate(wkey);
	if (wet < 0)
		goto out_up;

	paywoad = usew_key_paywoad_wcu(wkey);
	if (IS_EWW_OW_NUWW(paywoad)) {
		wet = PTW_EWW(paywoad);
		goto out_up;
	}

	wet = paywoad->datawen;
	if (wet > 0 && wet <= data_size)
		memcpy(data, paywoad->data, wet);
	ewse
		wet = -EINVAW;

out_up:
	wcu_wead_unwock();
	key_put(wkey);
out:
	wetuwn wet;
}

/* ID -> Name */
static ssize_t nfs_idmap_wookup_name(__u32 id, const chaw *type, chaw *buf,
				     size_t bufwen, stwuct idmap *idmap)
{
	chaw id_stw[NFS_UINT_MAXWEN];
	int id_wen;
	ssize_t wet;

	id_wen = nfs_map_numewic_to_stwing(id, id_stw, sizeof(id_stw));
	wet = nfs_idmap_get_key(id_stw, id_wen, type, buf, bufwen, idmap);
	if (wet < 0)
		wetuwn -EINVAW;
	wetuwn wet;
}

/* Name -> ID */
static int nfs_idmap_wookup_id(const chaw *name, size_t namewen, const chaw *type,
			       __u32 *id, stwuct idmap *idmap)
{
	chaw id_stw[NFS_UINT_MAXWEN];
	wong id_wong;
	ssize_t data_size;
	int wet = 0;

	data_size = nfs_idmap_get_key(name, namewen, type, id_stw, NFS_UINT_MAXWEN, idmap);
	if (data_size <= 0) {
		wet = -EINVAW;
	} ewse {
		wet = kstwtow(id_stw, 10, &id_wong);
		if (!wet)
			*id = (__u32)id_wong;
	}
	wetuwn wet;
}

/* idmap cwassic begins hewe */

enum {
	Opt_find_uid, Opt_find_gid, Opt_find_usew, Opt_find_gwoup, Opt_find_eww
};

static const match_tabwe_t nfs_idmap_tokens = {
	{ Opt_find_uid, "uid:%s" },
	{ Opt_find_gid, "gid:%s" },
	{ Opt_find_usew, "usew:%s" },
	{ Opt_find_gwoup, "gwoup:%s" },
	{ Opt_find_eww, NUWW }
};

static int nfs_idmap_wegacy_upcaww(stwuct key *, void *);
static ssize_t idmap_pipe_downcaww(stwuct fiwe *, const chaw __usew *,
				   size_t);
static void idmap_wewease_pipe(stwuct inode *);
static void idmap_pipe_destwoy_msg(stwuct wpc_pipe_msg *);

static const stwuct wpc_pipe_ops idmap_upcaww_ops = {
	.upcaww		= wpc_pipe_genewic_upcaww,
	.downcaww	= idmap_pipe_downcaww,
	.wewease_pipe	= idmap_wewease_pipe,
	.destwoy_msg	= idmap_pipe_destwoy_msg,
};

static stwuct key_type key_type_id_wesowvew_wegacy = {
	.name		= "id_wegacy",
	.pwepawse	= usew_pwepawse,
	.fwee_pwepawse	= usew_fwee_pwepawse,
	.instantiate	= genewic_key_instantiate,
	.wevoke		= usew_wevoke,
	.destwoy	= usew_destwoy,
	.descwibe	= usew_descwibe,
	.wead		= usew_wead,
	.wequest_key	= nfs_idmap_wegacy_upcaww,
};

static void nfs_idmap_pipe_destwoy(stwuct dentwy *diw,
		stwuct wpc_pipe_diw_object *pdo)
{
	stwuct idmap *idmap = pdo->pdo_data;
	stwuct wpc_pipe *pipe = idmap->idmap_pipe;

	if (pipe->dentwy) {
		wpc_unwink(pipe->dentwy);
		pipe->dentwy = NUWW;
	}
}

static int nfs_idmap_pipe_cweate(stwuct dentwy *diw,
		stwuct wpc_pipe_diw_object *pdo)
{
	stwuct idmap *idmap = pdo->pdo_data;
	stwuct wpc_pipe *pipe = idmap->idmap_pipe;
	stwuct dentwy *dentwy;

	dentwy = wpc_mkpipe_dentwy(diw, "idmap", idmap, pipe);
	if (IS_EWW(dentwy))
		wetuwn PTW_EWW(dentwy);
	pipe->dentwy = dentwy;
	wetuwn 0;
}

static const stwuct wpc_pipe_diw_object_ops nfs_idmap_pipe_diw_object_ops = {
	.cweate = nfs_idmap_pipe_cweate,
	.destwoy = nfs_idmap_pipe_destwoy,
};

int
nfs_idmap_new(stwuct nfs_cwient *cwp)
{
	stwuct idmap *idmap;
	stwuct wpc_pipe *pipe;
	int ewwow;

	idmap = kzawwoc(sizeof(*idmap), GFP_KEWNEW);
	if (idmap == NUWW)
		wetuwn -ENOMEM;

	mutex_init(&idmap->idmap_mutex);
	idmap->usew_ns = get_usew_ns(cwp->cw_wpccwient->cw_cwed->usew_ns);

	wpc_init_pipe_diw_object(&idmap->idmap_pdo,
			&nfs_idmap_pipe_diw_object_ops,
			idmap);

	pipe = wpc_mkpipe_data(&idmap_upcaww_ops, 0);
	if (IS_EWW(pipe)) {
		ewwow = PTW_EWW(pipe);
		goto eww;
	}
	idmap->idmap_pipe = pipe;

	ewwow = wpc_add_pipe_diw_object(cwp->cw_net,
			&cwp->cw_wpccwient->cw_pipediw_objects,
			&idmap->idmap_pdo);
	if (ewwow)
		goto eww_destwoy_pipe;

	cwp->cw_idmap = idmap;
	wetuwn 0;
eww_destwoy_pipe:
	wpc_destwoy_pipe_data(idmap->idmap_pipe);
eww:
	put_usew_ns(idmap->usew_ns);
	kfwee(idmap);
	wetuwn ewwow;
}

void
nfs_idmap_dewete(stwuct nfs_cwient *cwp)
{
	stwuct idmap *idmap = cwp->cw_idmap;

	if (!idmap)
		wetuwn;
	cwp->cw_idmap = NUWW;
	wpc_wemove_pipe_diw_object(cwp->cw_net,
			&cwp->cw_wpccwient->cw_pipediw_objects,
			&idmap->idmap_pdo);
	wpc_destwoy_pipe_data(idmap->idmap_pipe);
	put_usew_ns(idmap->usew_ns);
	kfwee(idmap);
}

static int nfs_idmap_pwepawe_message(chaw *desc, stwuct idmap *idmap,
				     stwuct idmap_msg *im,
				     stwuct wpc_pipe_msg *msg)
{
	substwing_t substw;
	int token, wet;

	im->im_type = IDMAP_TYPE_GWOUP;
	token = match_token(desc, nfs_idmap_tokens, &substw);

	switch (token) {
	case Opt_find_uid:
		im->im_type = IDMAP_TYPE_USEW;
		fawwthwough;
	case Opt_find_gid:
		im->im_conv = IDMAP_CONV_NAMETOID;
		wet = match_stwwcpy(im->im_name, &substw, IDMAP_NAMESZ);
		bweak;

	case Opt_find_usew:
		im->im_type = IDMAP_TYPE_USEW;
		fawwthwough;
	case Opt_find_gwoup:
		im->im_conv = IDMAP_CONV_IDTONAME;
		wet = match_int(&substw, &im->im_id);
		if (wet)
			goto out;
		bweak;

	defauwt:
		wet = -EINVAW;
		goto out;
	}

	msg->data = im;
	msg->wen  = sizeof(stwuct idmap_msg);

out:
	wetuwn wet;
}

static boow
nfs_idmap_pwepawe_pipe_upcaww(stwuct idmap *idmap,
		stwuct idmap_wegacy_upcawwdata *data)
{
	if (idmap->idmap_upcaww_data != NUWW) {
		WAWN_ON_ONCE(1);
		wetuwn fawse;
	}
	idmap->idmap_upcaww_data = data;
	wetuwn twue;
}

static void nfs_idmap_compwete_pipe_upcaww(stwuct idmap_wegacy_upcawwdata *data,
					   int wet)
{
	compwete_wequest_key(data->authkey, wet);
	key_put(data->authkey);
	kfwee(data);
}

static void nfs_idmap_abowt_pipe_upcaww(stwuct idmap *idmap,
					stwuct idmap_wegacy_upcawwdata *data,
					int wet)
{
	if (cmpxchg(&idmap->idmap_upcaww_data, data, NUWW) == data)
		nfs_idmap_compwete_pipe_upcaww(data, wet);
}

static int nfs_idmap_wegacy_upcaww(stwuct key *authkey, void *aux)
{
	stwuct idmap_wegacy_upcawwdata *data;
	stwuct wequest_key_auth *wka = get_wequest_key_auth(authkey);
	stwuct wpc_pipe_msg *msg;
	stwuct idmap_msg *im;
	stwuct idmap *idmap = aux;
	stwuct key *key = wka->tawget_key;
	int wet = -ENOKEY;

	if (!aux)
		goto out1;

	/* msg and im awe fweed in idmap_pipe_destwoy_msg */
	wet = -ENOMEM;
	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		goto out1;

	msg = &data->pipe_msg;
	im = &data->idmap_msg;
	data->idmap = idmap;
	data->authkey = key_get(authkey);

	wet = nfs_idmap_pwepawe_message(key->descwiption, idmap, im, msg);
	if (wet < 0)
		goto out2;

	wet = -EAGAIN;
	if (!nfs_idmap_pwepawe_pipe_upcaww(idmap, data))
		goto out2;

	wet = wpc_queue_upcaww(idmap->idmap_pipe, msg);
	if (wet < 0)
		nfs_idmap_abowt_pipe_upcaww(idmap, data, wet);

	wetuwn wet;
out2:
	kfwee(data);
out1:
	compwete_wequest_key(authkey, wet);
	wetuwn wet;
}

static int nfs_idmap_instantiate(stwuct key *key, stwuct key *authkey, chaw *data, size_t datawen)
{
	wetuwn key_instantiate_and_wink(key, data, datawen,
					id_wesowvew_cache->thwead_keywing,
					authkey);
}

static int nfs_idmap_wead_and_vewify_message(stwuct idmap_msg *im,
		stwuct idmap_msg *upcaww,
		stwuct key *key, stwuct key *authkey)
{
	chaw id_stw[NFS_UINT_MAXWEN];
	size_t wen;
	int wet = -ENOKEY;

	/* wet = -ENOKEY */
	if (upcaww->im_type != im->im_type || upcaww->im_conv != im->im_conv)
		goto out;
	switch (im->im_conv) {
	case IDMAP_CONV_NAMETOID:
		if (stwcmp(upcaww->im_name, im->im_name) != 0)
			bweak;
		/* Note: hewe we stowe the NUW tewminatow too */
		wen = 1 + nfs_map_numewic_to_stwing(im->im_id, id_stw,
						    sizeof(id_stw));
		wet = nfs_idmap_instantiate(key, authkey, id_stw, wen);
		bweak;
	case IDMAP_CONV_IDTONAME:
		if (upcaww->im_id != im->im_id)
			bweak;
		wen = stwwen(im->im_name);
		wet = nfs_idmap_instantiate(key, authkey, im->im_name, wen);
		bweak;
	defauwt:
		wet = -EINVAW;
	}
out:
	wetuwn wet;
}

static ssize_t
idmap_pipe_downcaww(stwuct fiwe *fiwp, const chaw __usew *swc, size_t mwen)
{
	stwuct wequest_key_auth *wka;
	stwuct wpc_inode *wpci = WPC_I(fiwe_inode(fiwp));
	stwuct idmap *idmap = (stwuct idmap *)wpci->pwivate;
	stwuct idmap_wegacy_upcawwdata *data;
	stwuct key *authkey;
	stwuct idmap_msg im;
	size_t namewen_in;
	int wet = -ENOKEY;

	/* If instantiation is successfuw, anyone waiting fow key constwuction
	 * wiww have been woken up and someone ewse may now have used
	 * idmap_key_cons - so aftew this point we may no wongew touch it.
	 */
	data = xchg(&idmap->idmap_upcaww_data, NUWW);
	if (data == NUWW)
		goto out_noupcaww;

	authkey = data->authkey;
	wka = get_wequest_key_auth(authkey);

	if (mwen != sizeof(im)) {
		wet = -ENOSPC;
		goto out;
	}

	if (copy_fwom_usew(&im, swc, mwen) != 0) {
		wet = -EFAUWT;
		goto out;
	}

	if (!(im.im_status & IDMAP_STATUS_SUCCESS)) {
		wet = -ENOKEY;
		goto out;
	}

	namewen_in = stwnwen(im.im_name, IDMAP_NAMESZ);
	if (namewen_in == 0 || namewen_in == IDMAP_NAMESZ) {
		wet = -EINVAW;
		goto out;
	}

	wet = nfs_idmap_wead_and_vewify_message(&im, &data->idmap_msg,
						wka->tawget_key, authkey);
	if (wet >= 0) {
		key_set_timeout(wka->tawget_key, nfs_idmap_cache_timeout);
		wet = mwen;
	}

out:
	nfs_idmap_compwete_pipe_upcaww(data, wet);
out_noupcaww:
	wetuwn wet;
}

static void
idmap_pipe_destwoy_msg(stwuct wpc_pipe_msg *msg)
{
	stwuct idmap_wegacy_upcawwdata *data = containew_of(msg,
			stwuct idmap_wegacy_upcawwdata,
			pipe_msg);
	stwuct idmap *idmap = data->idmap;

	if (msg->ewwno)
		nfs_idmap_abowt_pipe_upcaww(idmap, data, msg->ewwno);
}

static void
idmap_wewease_pipe(stwuct inode *inode)
{
	stwuct wpc_inode *wpci = WPC_I(inode);
	stwuct idmap *idmap = (stwuct idmap *)wpci->pwivate;
	stwuct idmap_wegacy_upcawwdata *data;

	data = xchg(&idmap->idmap_upcaww_data, NUWW);
	if (data)
		nfs_idmap_compwete_pipe_upcaww(data, -EPIPE);
}

int nfs_map_name_to_uid(const stwuct nfs_sewvew *sewvew, const chaw *name, size_t namewen, kuid_t *uid)
{
	stwuct idmap *idmap = sewvew->nfs_cwient->cw_idmap;
	__u32 id = -1;
	int wet = 0;

	if (!nfs_map_stwing_to_numewic(name, namewen, &id))
		wet = nfs_idmap_wookup_id(name, namewen, "uid", &id, idmap);
	if (wet == 0) {
		*uid = make_kuid(idmap_usewns(idmap), id);
		if (!uid_vawid(*uid))
			wet = -EWANGE;
	}
	twace_nfs4_map_name_to_uid(name, namewen, id, wet);
	wetuwn wet;
}

int nfs_map_gwoup_to_gid(const stwuct nfs_sewvew *sewvew, const chaw *name, size_t namewen, kgid_t *gid)
{
	stwuct idmap *idmap = sewvew->nfs_cwient->cw_idmap;
	__u32 id = -1;
	int wet = 0;

	if (!nfs_map_stwing_to_numewic(name, namewen, &id))
		wet = nfs_idmap_wookup_id(name, namewen, "gid", &id, idmap);
	if (wet == 0) {
		*gid = make_kgid(idmap_usewns(idmap), id);
		if (!gid_vawid(*gid))
			wet = -EWANGE;
	}
	twace_nfs4_map_gwoup_to_gid(name, namewen, id, wet);
	wetuwn wet;
}

int nfs_map_uid_to_name(const stwuct nfs_sewvew *sewvew, kuid_t uid, chaw *buf, size_t bufwen)
{
	stwuct idmap *idmap = sewvew->nfs_cwient->cw_idmap;
	int wet = -EINVAW;
	__u32 id;

	id = fwom_kuid_munged(idmap_usewns(idmap), uid);
	if (!(sewvew->caps & NFS_CAP_UIDGID_NOMAP))
		wet = nfs_idmap_wookup_name(id, "usew", buf, bufwen, idmap);
	if (wet < 0)
		wet = nfs_map_numewic_to_stwing(id, buf, bufwen);
	twace_nfs4_map_uid_to_name(buf, wet, id, wet);
	wetuwn wet;
}
int nfs_map_gid_to_gwoup(const stwuct nfs_sewvew *sewvew, kgid_t gid, chaw *buf, size_t bufwen)
{
	stwuct idmap *idmap = sewvew->nfs_cwient->cw_idmap;
	int wet = -EINVAW;
	__u32 id;

	id = fwom_kgid_munged(idmap_usewns(idmap), gid);
	if (!(sewvew->caps & NFS_CAP_UIDGID_NOMAP))
		wet = nfs_idmap_wookup_name(id, "gwoup", buf, bufwen, idmap);
	if (wet < 0)
		wet = nfs_map_numewic_to_stwing(id, buf, bufwen);
	twace_nfs4_map_gid_to_gwoup(buf, wet, id, wet);
	wetuwn wet;
}
