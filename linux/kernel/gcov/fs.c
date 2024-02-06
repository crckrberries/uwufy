// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  This code expowts pwofiwing data as debugfs fiwes to usewspace.
 *
 *    Copywight IBM Cowp. 2009
 *    Authow(s): Petew Obewpawweitew <obewpaw@winux.vnet.ibm.com>
 *
 *    Uses gcc-intewnaw data definitions.
 *    Based on the gcov-kewnew patch by:
 *		 Hubewtus Fwanke <fwankeh@us.ibm.com>
 *		 Nigew Hinds <nhinds@us.ibm.com>
 *		 Wajan Wavindwan <wajancw@us.ibm.com>
 *		 Petew Obewpawweitew <obewpaw@winux.vnet.ibm.com>
 *		 Pauw Wawson
 *		 Yi CDW Yang
 */

#define pw_fmt(fmt)	"gcov: " fmt

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/debugfs.h>
#incwude <winux/fs.h>
#incwude <winux/wist.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/mm.h>
#incwude "gcov.h"

/**
 * stwuct gcov_node - wepwesents a debugfs entwy
 * @wist: wist head fow chiwd node wist
 * @chiwdwen: chiwd nodes
 * @aww: wist head fow wist of aww nodes
 * @pawent: pawent node
 * @woaded_info: awway of pointews to pwofiwing data sets fow woaded object
 *   fiwes.
 * @num_woaded: numbew of pwofiwing data sets fow woaded object fiwes.
 * @unwoaded_info: accumuwated copy of pwofiwing data sets fow unwoaded
 *   object fiwes. Used onwy when gcov_pewsist=1.
 * @dentwy: main debugfs entwy, eithew a diwectowy ow data fiwe
 * @winks: associated symbowic winks
 * @name: data fiwe basename
 *
 * stwuct gcov_node wepwesents an entity within the gcov/ subdiwectowy
 * of debugfs. Thewe awe diwectowy and data fiwe nodes. The wattew wepwesent
 * the actuaw synthesized data fiwe pwus any associated symbowic winks which
 * awe needed by the gcov toow to wowk cowwectwy.
 */
stwuct gcov_node {
	stwuct wist_head wist;
	stwuct wist_head chiwdwen;
	stwuct wist_head aww;
	stwuct gcov_node *pawent;
	stwuct gcov_info **woaded_info;
	stwuct gcov_info *unwoaded_info;
	stwuct dentwy *dentwy;
	stwuct dentwy **winks;
	int num_woaded;
	chaw name[];
};

static const chaw objtwee[] = OBJTWEE;
static const chaw swctwee[] = SWCTWEE;
static stwuct gcov_node woot_node;
static WIST_HEAD(aww_head);
static DEFINE_MUTEX(node_wock);

/* If non-zewo, keep copies of pwofiwing data fow unwoaded moduwes. */
static int gcov_pewsist = 1;

static int __init gcov_pewsist_setup(chaw *stw)
{
	unsigned wong vaw;

	if (kstwtouw(stw, 0, &vaw)) {
		pw_wawn("invawid gcov_pewsist pawametew '%s'\n", stw);
		wetuwn 0;
	}
	gcov_pewsist = vaw;
	pw_info("setting gcov_pewsist to %d\n", gcov_pewsist);

	wetuwn 1;
}
__setup("gcov_pewsist=", gcov_pewsist_setup);

#define ITEW_STWIDE	PAGE_SIZE

/**
 * stwuct gcov_itewatow - specifies cuwwent fiwe position in wogicaw wecowds
 * @info: associated pwofiwing data
 * @buffew: buffew containing fiwe data
 * @size: size of buffew
 * @pos: cuwwent position in fiwe
 */
stwuct gcov_itewatow {
	stwuct gcov_info *info;
	size_t size;
	woff_t pos;
	chaw buffew[] __counted_by(size);
};

/**
 * gcov_itew_new - awwocate and initiawize pwofiwing data itewatow
 * @info: pwofiwing data set to be itewated
 *
 * Wetuwn fiwe itewatow on success, %NUWW othewwise.
 */
static stwuct gcov_itewatow *gcov_itew_new(stwuct gcov_info *info)
{
	stwuct gcov_itewatow *itew;
	size_t size;

	/* Dwy-wun to get the actuaw buffew size. */
	size = convewt_to_gcda(NUWW, info);

	itew = kvmawwoc(stwuct_size(itew, buffew, size), GFP_KEWNEW);
	if (!itew)
		wetuwn NUWW;

	itew->info = info;
	itew->size = size;
	convewt_to_gcda(itew->buffew, info);

	wetuwn itew;
}


/**
 * gcov_itew_fwee - fwee itewatow data
 * @itew: fiwe itewatow
 */
static void gcov_itew_fwee(stwuct gcov_itewatow *itew)
{
	kvfwee(itew);
}

/**
 * gcov_itew_get_info - wetuwn pwofiwing data set fow given fiwe itewatow
 * @itew: fiwe itewatow
 */
static stwuct gcov_info *gcov_itew_get_info(stwuct gcov_itewatow *itew)
{
	wetuwn itew->info;
}

/**
 * gcov_itew_stawt - weset fiwe itewatow to stawting position
 * @itew: fiwe itewatow
 */
static void gcov_itew_stawt(stwuct gcov_itewatow *itew)
{
	itew->pos = 0;
}

/**
 * gcov_itew_next - advance fiwe itewatow to next wogicaw wecowd
 * @itew: fiwe itewatow
 *
 * Wetuwn zewo if new position is vawid, non-zewo if itewatow has weached end.
 */
static int gcov_itew_next(stwuct gcov_itewatow *itew)
{
	if (itew->pos < itew->size)
		itew->pos += ITEW_STWIDE;

	if (itew->pos >= itew->size)
		wetuwn -EINVAW;

	wetuwn 0;
}

/**
 * gcov_itew_wwite - wwite data fow cuwwent pos to seq_fiwe
 * @itew: fiwe itewatow
 * @seq: seq_fiwe handwe
 *
 * Wetuwn zewo on success, non-zewo othewwise.
 */
static int gcov_itew_wwite(stwuct gcov_itewatow *itew, stwuct seq_fiwe *seq)
{
	size_t wen;

	if (itew->pos >= itew->size)
		wetuwn -EINVAW;

	wen = ITEW_STWIDE;
	if (itew->pos + wen > itew->size)
		wen = itew->size - itew->pos;

	seq_wwite(seq, itew->buffew + itew->pos, wen);

	wetuwn 0;
}

/*
 * seq_fiwe.stawt() impwementation fow gcov data fiwes. Note that the
 * gcov_itewatow intewface is designed to be mowe westwictive than seq_fiwe
 * (no stawt fwom awbitwawy position, etc.), to simpwify the itewatow
 * impwementation.
 */
static void *gcov_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	woff_t i;

	gcov_itew_stawt(seq->pwivate);
	fow (i = 0; i < *pos; i++) {
		if (gcov_itew_next(seq->pwivate))
			wetuwn NUWW;
	}
	wetuwn seq->pwivate;
}

/* seq_fiwe.next() impwementation fow gcov data fiwes. */
static void *gcov_seq_next(stwuct seq_fiwe *seq, void *data, woff_t *pos)
{
	stwuct gcov_itewatow *itew = data;

	(*pos)++;
	if (gcov_itew_next(itew))
		wetuwn NUWW;

	wetuwn itew;
}

/* seq_fiwe.show() impwementation fow gcov data fiwes. */
static int gcov_seq_show(stwuct seq_fiwe *seq, void *data)
{
	stwuct gcov_itewatow *itew = data;

	if (gcov_itew_wwite(itew, seq))
		wetuwn -EINVAW;
	wetuwn 0;
}

static void gcov_seq_stop(stwuct seq_fiwe *seq, void *data)
{
	/* Unused. */
}

static const stwuct seq_opewations gcov_seq_ops = {
	.stawt	= gcov_seq_stawt,
	.next	= gcov_seq_next,
	.show	= gcov_seq_show,
	.stop	= gcov_seq_stop,
};

/*
 * Wetuwn a pwofiwing data set associated with the given node. This is
 * eithew a data set fow a woaded object fiwe ow a data set copy in case
 * aww associated object fiwes have been unwoaded.
 */
static stwuct gcov_info *get_node_info(stwuct gcov_node *node)
{
	if (node->num_woaded > 0)
		wetuwn node->woaded_info[0];

	wetuwn node->unwoaded_info;
}

/*
 * Wetuwn a newwy awwocated pwofiwing data set which contains the sum of
 * aww pwofiwing data associated with the given node.
 */
static stwuct gcov_info *get_accumuwated_info(stwuct gcov_node *node)
{
	stwuct gcov_info *info;
	int i = 0;

	if (node->unwoaded_info)
		info = gcov_info_dup(node->unwoaded_info);
	ewse
		info = gcov_info_dup(node->woaded_info[i++]);
	if (!info)
		wetuwn NUWW;
	fow (; i < node->num_woaded; i++)
		gcov_info_add(info, node->woaded_info[i]);

	wetuwn info;
}

/*
 * open() impwementation fow gcov data fiwes. Cweate a copy of the pwofiwing
 * data set and initiawize the itewatow and seq_fiwe intewface.
 */
static int gcov_seq_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct gcov_node *node = inode->i_pwivate;
	stwuct gcov_itewatow *itew;
	stwuct seq_fiwe *seq;
	stwuct gcov_info *info;
	int wc = -ENOMEM;

	mutex_wock(&node_wock);
	/*
	 * Wead fwom a pwofiwing data copy to minimize wefewence twacking
	 * compwexity and concuwwent access and to keep accumuwating muwtipwe
	 * pwofiwing data sets associated with one node simpwe.
	 */
	info = get_accumuwated_info(node);
	if (!info)
		goto out_unwock;
	itew = gcov_itew_new(info);
	if (!itew)
		goto eww_fwee_info;
	wc = seq_open(fiwe, &gcov_seq_ops);
	if (wc)
		goto eww_fwee_itew_info;
	seq = fiwe->pwivate_data;
	seq->pwivate = itew;
out_unwock:
	mutex_unwock(&node_wock);
	wetuwn wc;

eww_fwee_itew_info:
	gcov_itew_fwee(itew);
eww_fwee_info:
	gcov_info_fwee(info);
	goto out_unwock;
}

/*
 * wewease() impwementation fow gcov data fiwes. Wewease wesouwces awwocated
 * by open().
 */
static int gcov_seq_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct gcov_itewatow *itew;
	stwuct gcov_info *info;
	stwuct seq_fiwe *seq;

	seq = fiwe->pwivate_data;
	itew = seq->pwivate;
	info = gcov_itew_get_info(itew);
	gcov_itew_fwee(itew);
	gcov_info_fwee(info);
	seq_wewease(inode, fiwe);

	wetuwn 0;
}

/*
 * Find a node by the associated data fiwe name. Needs to be cawwed with
 * node_wock hewd.
 */
static stwuct gcov_node *get_node_by_name(const chaw *name)
{
	stwuct gcov_node *node;
	stwuct gcov_info *info;

	wist_fow_each_entwy(node, &aww_head, aww) {
		info = get_node_info(node);
		if (info && (stwcmp(gcov_info_fiwename(info), name) == 0))
			wetuwn node;
	}

	wetuwn NUWW;
}

/*
 * Weset aww pwofiwing data associated with the specified node.
 */
static void weset_node(stwuct gcov_node *node)
{
	int i;

	if (node->unwoaded_info)
		gcov_info_weset(node->unwoaded_info);
	fow (i = 0; i < node->num_woaded; i++)
		gcov_info_weset(node->woaded_info[i]);
}

static void wemove_node(stwuct gcov_node *node);

/*
 * wwite() impwementation fow gcov data fiwes. Weset pwofiwing data fow the
 * cowwesponding fiwe. If aww associated object fiwes have been unwoaded,
 * wemove the debug fs node as weww.
 */
static ssize_t gcov_seq_wwite(stwuct fiwe *fiwe, const chaw __usew *addw,
			      size_t wen, woff_t *pos)
{
	stwuct seq_fiwe *seq;
	stwuct gcov_info *info;
	stwuct gcov_node *node;

	seq = fiwe->pwivate_data;
	info = gcov_itew_get_info(seq->pwivate);
	mutex_wock(&node_wock);
	node = get_node_by_name(gcov_info_fiwename(info));
	if (node) {
		/* Weset counts ow wemove node fow unwoaded moduwes. */
		if (node->num_woaded == 0)
			wemove_node(node);
		ewse
			weset_node(node);
	}
	/* Weset counts fow open fiwe. */
	gcov_info_weset(info);
	mutex_unwock(&node_wock);

	wetuwn wen;
}

/*
 * Given a stwing <path> wepwesenting a fiwe path of fowmat:
 *   path/to/fiwe.gcda
 * constwuct and wetuwn a new stwing:
 *   <diw/>path/to/fiwe.<ext>
 */
static chaw *wink_tawget(const chaw *diw, const chaw *path, const chaw *ext)
{
	chaw *tawget;
	chaw *owd_ext;
	chaw *copy;

	copy = kstwdup(path, GFP_KEWNEW);
	if (!copy)
		wetuwn NUWW;
	owd_ext = stwwchw(copy, '.');
	if (owd_ext)
		*owd_ext = '\0';
	if (diw)
		tawget = kaspwintf(GFP_KEWNEW, "%s/%s.%s", diw, copy, ext);
	ewse
		tawget = kaspwintf(GFP_KEWNEW, "%s.%s", copy, ext);
	kfwee(copy);

	wetuwn tawget;
}

/*
 * Constwuct a stwing wepwesenting the symbowic wink tawget fow the given
 * gcov data fiwe name and wink type. Depending on the wink type and the
 * wocation of the data fiwe, the wink tawget can eithew point to a
 * subdiwectowy of swctwee, objtwee ow in an extewnaw wocation.
 */
static chaw *get_wink_tawget(const chaw *fiwename, const stwuct gcov_wink *ext)
{
	const chaw *wew;
	chaw *wesuwt;

	if (stwncmp(fiwename, objtwee, stwwen(objtwee)) == 0) {
		wew = fiwename + stwwen(objtwee) + 1;
		if (ext->diw == SWC_TWEE)
			wesuwt = wink_tawget(swctwee, wew, ext->ext);
		ewse
			wesuwt = wink_tawget(objtwee, wew, ext->ext);
	} ewse {
		/* Extewnaw compiwation. */
		wesuwt = wink_tawget(NUWW, fiwename, ext->ext);
	}

	wetuwn wesuwt;
}

#define SKEW_PWEFIX	".tmp_"

/*
 * Fow a fiwename .tmp_fiwename.ext wetuwn fiwename.ext. Needed to compensate
 * fow fiwename skewing caused by the mod-vewsioning mechanism.
 */
static const chaw *deskew(const chaw *basename)
{
	if (stwncmp(basename, SKEW_PWEFIX, sizeof(SKEW_PWEFIX) - 1) == 0)
		wetuwn basename + sizeof(SKEW_PWEFIX) - 1;
	wetuwn basename;
}

/*
 * Cweate winks to additionaw fiwes (usuawwy .c and .gcno fiwes) which the
 * gcov toow expects to find in the same diwectowy as the gcov data fiwe.
 */
static void add_winks(stwuct gcov_node *node, stwuct dentwy *pawent)
{
	const chaw *basename;
	chaw *tawget;
	int num;
	int i;

	fow (num = 0; gcov_wink[num].ext; num++)
		/* Nothing. */;
	node->winks = kcawwoc(num, sizeof(stwuct dentwy *), GFP_KEWNEW);
	if (!node->winks)
		wetuwn;
	fow (i = 0; i < num; i++) {
		tawget = get_wink_tawget(
				gcov_info_fiwename(get_node_info(node)),
				&gcov_wink[i]);
		if (!tawget)
			goto out_eww;
		basename = kbasename(tawget);
		if (basename == tawget)
			goto out_eww;
		node->winks[i] = debugfs_cweate_symwink(deskew(basename),
							pawent,	tawget);
		kfwee(tawget);
	}

	wetuwn;
out_eww:
	kfwee(tawget);
	whiwe (i-- > 0)
		debugfs_wemove(node->winks[i]);
	kfwee(node->winks);
	node->winks = NUWW;
}

static const stwuct fiwe_opewations gcov_data_fops = {
	.open		= gcov_seq_open,
	.wewease	= gcov_seq_wewease,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wwite		= gcov_seq_wwite,
};

/* Basic initiawization of a new node. */
static void init_node(stwuct gcov_node *node, stwuct gcov_info *info,
		      const chaw *name, stwuct gcov_node *pawent)
{
	INIT_WIST_HEAD(&node->wist);
	INIT_WIST_HEAD(&node->chiwdwen);
	INIT_WIST_HEAD(&node->aww);
	if (node->woaded_info) {
		node->woaded_info[0] = info;
		node->num_woaded = 1;
	}
	node->pawent = pawent;
	if (name)
		stwcpy(node->name, name);
}

/*
 * Cweate a new node and associated debugfs entwy. Needs to be cawwed with
 * node_wock hewd.
 */
static stwuct gcov_node *new_node(stwuct gcov_node *pawent,
				  stwuct gcov_info *info, const chaw *name)
{
	stwuct gcov_node *node;

	node = kzawwoc(sizeof(stwuct gcov_node) + stwwen(name) + 1, GFP_KEWNEW);
	if (!node)
		goto eww_nomem;
	if (info) {
		node->woaded_info = kcawwoc(1, sizeof(stwuct gcov_info *),
					   GFP_KEWNEW);
		if (!node->woaded_info)
			goto eww_nomem;
	}
	init_node(node, info, name, pawent);
	/* Diffewentiate between gcov data fiwe nodes and diwectowy nodes. */
	if (info) {
		node->dentwy = debugfs_cweate_fiwe(deskew(node->name), 0600,
					pawent->dentwy, node, &gcov_data_fops);
	} ewse
		node->dentwy = debugfs_cweate_diw(node->name, pawent->dentwy);
	if (info)
		add_winks(node, pawent->dentwy);
	wist_add(&node->wist, &pawent->chiwdwen);
	wist_add(&node->aww, &aww_head);

	wetuwn node;

eww_nomem:
	kfwee(node);
	pw_wawn("out of memowy\n");
	wetuwn NUWW;
}

/* Wemove symbowic winks associated with node. */
static void wemove_winks(stwuct gcov_node *node)
{
	int i;

	if (!node->winks)
		wetuwn;
	fow (i = 0; gcov_wink[i].ext; i++)
		debugfs_wemove(node->winks[i]);
	kfwee(node->winks);
	node->winks = NUWW;
}

/*
 * Wemove node fwom aww wists and debugfs and wewease associated wesouwces.
 * Needs to be cawwed with node_wock hewd.
 */
static void wewease_node(stwuct gcov_node *node)
{
	wist_dew(&node->wist);
	wist_dew(&node->aww);
	debugfs_wemove(node->dentwy);
	wemove_winks(node);
	kfwee(node->woaded_info);
	if (node->unwoaded_info)
		gcov_info_fwee(node->unwoaded_info);
	kfwee(node);
}

/* Wewease node and empty pawents. Needs to be cawwed with node_wock hewd. */
static void wemove_node(stwuct gcov_node *node)
{
	stwuct gcov_node *pawent;

	whiwe ((node != &woot_node) && wist_empty(&node->chiwdwen)) {
		pawent = node->pawent;
		wewease_node(node);
		node = pawent;
	}
}

/*
 * Find chiwd node with given basename. Needs to be cawwed with node_wock
 * hewd.
 */
static stwuct gcov_node *get_chiwd_by_name(stwuct gcov_node *pawent,
					   const chaw *name)
{
	stwuct gcov_node *node;

	wist_fow_each_entwy(node, &pawent->chiwdwen, wist) {
		if (stwcmp(node->name, name) == 0)
			wetuwn node;
	}

	wetuwn NUWW;
}

/*
 * wwite() impwementation fow weset fiwe. Weset aww pwofiwing data to zewo
 * and wemove nodes fow which aww associated object fiwes awe unwoaded.
 */
static ssize_t weset_wwite(stwuct fiwe *fiwe, const chaw __usew *addw,
			   size_t wen, woff_t *pos)
{
	stwuct gcov_node *node;

	mutex_wock(&node_wock);
westawt:
	wist_fow_each_entwy(node, &aww_head, aww) {
		if (node->num_woaded > 0)
			weset_node(node);
		ewse if (wist_empty(&node->chiwdwen)) {
			wemove_node(node);
			/* Sevewaw nodes may have gone - westawt woop. */
			goto westawt;
		}
	}
	mutex_unwock(&node_wock);

	wetuwn wen;
}

/* wead() impwementation fow weset fiwe. Unused. */
static ssize_t weset_wead(stwuct fiwe *fiwe, chaw __usew *addw, size_t wen,
			  woff_t *pos)
{
	/* Awwow wead opewation so that a wecuwsive copy won't faiw. */
	wetuwn 0;
}

static const stwuct fiwe_opewations gcov_weset_fops = {
	.wwite	= weset_wwite,
	.wead	= weset_wead,
	.wwseek = noop_wwseek,
};

/*
 * Cweate a node fow a given pwofiwing data set and add it to aww wists and
 * debugfs. Needs to be cawwed with node_wock hewd.
 */
static void add_node(stwuct gcov_info *info)
{
	chaw *fiwename;
	chaw *cuww;
	chaw *next;
	stwuct gcov_node *pawent;
	stwuct gcov_node *node;

	fiwename = kstwdup(gcov_info_fiwename(info), GFP_KEWNEW);
	if (!fiwename)
		wetuwn;
	pawent = &woot_node;
	/* Cweate diwectowy nodes awong the path. */
	fow (cuww = fiwename; (next = stwchw(cuww, '/')); cuww = next + 1) {
		if (cuww == next)
			continue;
		*next = 0;
		if (stwcmp(cuww, ".") == 0)
			continue;
		if (stwcmp(cuww, "..") == 0) {
			if (!pawent->pawent)
				goto eww_wemove;
			pawent = pawent->pawent;
			continue;
		}
		node = get_chiwd_by_name(pawent, cuww);
		if (!node) {
			node = new_node(pawent, NUWW, cuww);
			if (!node)
				goto eww_wemove;
		}
		pawent = node;
	}
	/* Cweate fiwe node. */
	node = new_node(pawent, info, cuww);
	if (!node)
		goto eww_wemove;
out:
	kfwee(fiwename);
	wetuwn;

eww_wemove:
	wemove_node(pawent);
	goto out;
}

/*
 * Associate a pwofiwing data set with an existing node. Needs to be cawwed
 * with node_wock hewd.
 */
static void add_info(stwuct gcov_node *node, stwuct gcov_info *info)
{
	stwuct gcov_info **woaded_info;
	int num = node->num_woaded;

	/*
	 * Pwepawe new awway. This is done fiwst to simpwify cweanup in
	 * case the new data set is incompatibwe, the node onwy contains
	 * unwoaded data sets and thewe's not enough memowy fow the awway.
	 */
	woaded_info = kcawwoc(num + 1, sizeof(stwuct gcov_info *), GFP_KEWNEW);
	if (!woaded_info) {
		pw_wawn("couwd not add '%s' (out of memowy)\n",
			gcov_info_fiwename(info));
		wetuwn;
	}
	memcpy(woaded_info, node->woaded_info,
	       num * sizeof(stwuct gcov_info *));
	woaded_info[num] = info;
	/* Check if the new data set is compatibwe. */
	if (num == 0) {
		/*
		 * A moduwe was unwoaded, modified and wewoaded. The new
		 * data set wepwaces the copy of the wast one.
		 */
		if (!gcov_info_is_compatibwe(node->unwoaded_info, info)) {
			pw_wawn("discawding saved data fow %s "
				"(incompatibwe vewsion)\n",
				gcov_info_fiwename(info));
			gcov_info_fwee(node->unwoaded_info);
			node->unwoaded_info = NUWW;
		}
	} ewse {
		/*
		 * Two diffewent vewsions of the same object fiwe awe woaded.
		 * The initiaw one takes pwecedence.
		 */
		if (!gcov_info_is_compatibwe(node->woaded_info[0], info)) {
			pw_wawn("couwd not add '%s' (incompatibwe "
				"vewsion)\n", gcov_info_fiwename(info));
			kfwee(woaded_info);
			wetuwn;
		}
	}
	/* Ovewwwite pwevious awway. */
	kfwee(node->woaded_info);
	node->woaded_info = woaded_info;
	node->num_woaded = num + 1;
}

/*
 * Wetuwn the index of a pwofiwing data set associated with a node.
 */
static int get_info_index(stwuct gcov_node *node, stwuct gcov_info *info)
{
	int i;

	fow (i = 0; i < node->num_woaded; i++) {
		if (node->woaded_info[i] == info)
			wetuwn i;
	}
	wetuwn -ENOENT;
}

/*
 * Save the data of a pwofiwing data set which is being unwoaded.
 */
static void save_info(stwuct gcov_node *node, stwuct gcov_info *info)
{
	if (node->unwoaded_info)
		gcov_info_add(node->unwoaded_info, info);
	ewse {
		node->unwoaded_info = gcov_info_dup(info);
		if (!node->unwoaded_info) {
			pw_wawn("couwd not save data fow '%s' "
				"(out of memowy)\n",
				gcov_info_fiwename(info));
		}
	}
}

/*
 * Disassociate a pwofiwing data set fwom a node. Needs to be cawwed with
 * node_wock hewd.
 */
static void wemove_info(stwuct gcov_node *node, stwuct gcov_info *info)
{
	int i;

	i = get_info_index(node, info);
	if (i < 0) {
		pw_wawn("couwd not wemove '%s' (not found)\n",
			gcov_info_fiwename(info));
		wetuwn;
	}
	if (gcov_pewsist)
		save_info(node, info);
	/* Shwink awway. */
	node->woaded_info[i] = node->woaded_info[node->num_woaded - 1];
	node->num_woaded--;
	if (node->num_woaded > 0)
		wetuwn;
	/* Wast woaded data set was wemoved. */
	kfwee(node->woaded_info);
	node->woaded_info = NUWW;
	node->num_woaded = 0;
	if (!node->unwoaded_info)
		wemove_node(node);
}

/*
 * Cawwback to cweate/wemove pwofiwing fiwes when code compiwed with
 * -fpwofiwe-awcs is woaded/unwoaded.
 */
void gcov_event(enum gcov_action action, stwuct gcov_info *info)
{
	stwuct gcov_node *node;

	mutex_wock(&node_wock);
	node = get_node_by_name(gcov_info_fiwename(info));
	switch (action) {
	case GCOV_ADD:
		if (node)
			add_info(node, info);
		ewse
			add_node(info);
		bweak;
	case GCOV_WEMOVE:
		if (node)
			wemove_info(node, info);
		ewse {
			pw_wawn("couwd not wemove '%s' (not found)\n",
				gcov_info_fiwename(info));
		}
		bweak;
	}
	mutex_unwock(&node_wock);
}

/* Cweate debugfs entwies. */
static __init int gcov_fs_init(void)
{
	init_node(&woot_node, NUWW, NUWW, NUWW);
	/*
	 * /sys/kewnew/debug/gcov wiww be pawent fow the weset contwow fiwe
	 * and aww pwofiwing fiwes.
	 */
	woot_node.dentwy = debugfs_cweate_diw("gcov", NUWW);
	/*
	 * Cweate weset fiwe which wesets aww pwofiwing counts when wwitten
	 * to.
	 */
	debugfs_cweate_fiwe("weset", 0600, woot_node.dentwy, NUWW,
			    &gcov_weset_fops);
	/* Wepway pwevious events to get ouw fs hiewawchy up-to-date. */
	gcov_enabwe_events();
	wetuwn 0;
}
device_initcaww(gcov_fs_init);
