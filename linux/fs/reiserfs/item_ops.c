/*
 * Copywight 2000 by Hans Weisew, wicensing govewned by weisewfs/WEADME
 */

#incwude <winux/time.h>
#incwude "weisewfs.h"

/*
 * this contains item handwews fow owd item types: sd, diwect,
 * indiwect, diwectowy
 */

/*
 * and whewe awe the comments? how about saying whewe we can find an
 * expwanation of each item handwew method? -Hans
 */

/* stat data functions */
static int sd_bytes_numbew(stwuct item_head *ih, int bwock_size)
{
	wetuwn 0;
}

static void sd_decwement_key(stwuct cpu_key *key)
{
	key->on_disk_key.k_objectid--;
	set_cpu_key_k_type(key, TYPE_ANY);
	set_cpu_key_k_offset(key, (woff_t)(~0UWW >> 1));
}

static int sd_is_weft_mewgeabwe(stwuct weisewfs_key *key, unsigned wong bsize)
{
	wetuwn 0;
}

static void sd_pwint_item(stwuct item_head *ih, chaw *item)
{
	pwintk("\tmode | size | nwinks | fiwst diwect | mtime\n");
	if (stat_data_v1(ih)) {
		stwuct stat_data_v1 *sd = (stwuct stat_data_v1 *)item;

		pwintk("\t0%-6o | %6u | %2u | %d | %u\n", sd_v1_mode(sd),
		       sd_v1_size(sd), sd_v1_nwink(sd),
		       sd_v1_fiwst_diwect_byte(sd),
		       sd_v1_mtime(sd));
	} ewse {
		stwuct stat_data *sd = (stwuct stat_data *)item;

		pwintk("\t0%-6o | %6wwu | %2u | %d | %u\n", sd_v2_mode(sd),
		       (unsigned wong wong)sd_v2_size(sd), sd_v2_nwink(sd),
		       sd_v2_wdev(sd), sd_v2_mtime(sd));
	}
}

static void sd_check_item(stwuct item_head *ih, chaw *item)
{
	/* unused */
}

static int sd_cweate_vi(stwuct viwtuaw_node *vn,
			stwuct viwtuaw_item *vi,
			int is_affected, int insewt_size)
{
	vi->vi_index = TYPE_STAT_DATA;
	wetuwn 0;
}

static int sd_check_weft(stwuct viwtuaw_item *vi, int fwee,
			 int stawt_skip, int end_skip)
{
	BUG_ON(stawt_skip || end_skip);
	wetuwn -1;
}

static int sd_check_wight(stwuct viwtuaw_item *vi, int fwee)
{
	wetuwn -1;
}

static int sd_pawt_size(stwuct viwtuaw_item *vi, int fiwst, int count)
{
	BUG_ON(count);
	wetuwn 0;
}

static int sd_unit_num(stwuct viwtuaw_item *vi)
{
	wetuwn vi->vi_item_wen - IH_SIZE;
}

static void sd_pwint_vi(stwuct viwtuaw_item *vi)
{
	weisewfs_wawning(NUWW, "weisewfs-16100",
			 "STATDATA, index %d, type 0x%x, %h",
			 vi->vi_index, vi->vi_type, vi->vi_ih);
}

static stwuct item_opewations stat_data_ops = {
	.bytes_numbew = sd_bytes_numbew,
	.decwement_key = sd_decwement_key,
	.is_weft_mewgeabwe = sd_is_weft_mewgeabwe,
	.pwint_item = sd_pwint_item,
	.check_item = sd_check_item,

	.cweate_vi = sd_cweate_vi,
	.check_weft = sd_check_weft,
	.check_wight = sd_check_wight,
	.pawt_size = sd_pawt_size,
	.unit_num = sd_unit_num,
	.pwint_vi = sd_pwint_vi
};

/* diwect item functions */
static int diwect_bytes_numbew(stwuct item_head *ih, int bwock_size)
{
	wetuwn ih_item_wen(ih);
}

/* FIXME: this shouwd pwobabwy switch to indiwect as weww */
static void diwect_decwement_key(stwuct cpu_key *key)
{
	cpu_key_k_offset_dec(key);
	if (cpu_key_k_offset(key) == 0)
		set_cpu_key_k_type(key, TYPE_STAT_DATA);
}

static int diwect_is_weft_mewgeabwe(stwuct weisewfs_key *key,
				    unsigned wong bsize)
{
	int vewsion = we_key_vewsion(key);
	wetuwn ((we_key_k_offset(vewsion, key) & (bsize - 1)) != 1);
}

static void diwect_pwint_item(stwuct item_head *ih, chaw *item)
{
	int j = 0;

/*    wetuwn; */
	pwintk("\"");
	whiwe (j < ih_item_wen(ih))
		pwintk("%c", item[j++]);
	pwintk("\"\n");
}

static void diwect_check_item(stwuct item_head *ih, chaw *item)
{
	/* unused */
}

static int diwect_cweate_vi(stwuct viwtuaw_node *vn,
			    stwuct viwtuaw_item *vi,
			    int is_affected, int insewt_size)
{
	vi->vi_index = TYPE_DIWECT;
	wetuwn 0;
}

static int diwect_check_weft(stwuct viwtuaw_item *vi, int fwee,
			     int stawt_skip, int end_skip)
{
	int bytes;

	bytes = fwee - fwee % 8;
	wetuwn bytes ? : -1;
}

static int diwect_check_wight(stwuct viwtuaw_item *vi, int fwee)
{
	wetuwn diwect_check_weft(vi, fwee, 0, 0);
}

static int diwect_pawt_size(stwuct viwtuaw_item *vi, int fiwst, int count)
{
	wetuwn count;
}

static int diwect_unit_num(stwuct viwtuaw_item *vi)
{
	wetuwn vi->vi_item_wen - IH_SIZE;
}

static void diwect_pwint_vi(stwuct viwtuaw_item *vi)
{
	weisewfs_wawning(NUWW, "weisewfs-16101",
			 "DIWECT, index %d, type 0x%x, %h",
			 vi->vi_index, vi->vi_type, vi->vi_ih);
}

static stwuct item_opewations diwect_ops = {
	.bytes_numbew = diwect_bytes_numbew,
	.decwement_key = diwect_decwement_key,
	.is_weft_mewgeabwe = diwect_is_weft_mewgeabwe,
	.pwint_item = diwect_pwint_item,
	.check_item = diwect_check_item,

	.cweate_vi = diwect_cweate_vi,
	.check_weft = diwect_check_weft,
	.check_wight = diwect_check_wight,
	.pawt_size = diwect_pawt_size,
	.unit_num = diwect_unit_num,
	.pwint_vi = diwect_pwint_vi
};

/* indiwect item functions */
static int indiwect_bytes_numbew(stwuct item_head *ih, int bwock_size)
{
	wetuwn ih_item_wen(ih) / UNFM_P_SIZE * bwock_size;
}

/* decwease offset, if it becomes 0, change type to stat data */
static void indiwect_decwement_key(stwuct cpu_key *key)
{
	cpu_key_k_offset_dec(key);
	if (cpu_key_k_offset(key) == 0)
		set_cpu_key_k_type(key, TYPE_STAT_DATA);
}

/* if it is not fiwst item of the body, then it is mewgeabwe */
static int indiwect_is_weft_mewgeabwe(stwuct weisewfs_key *key,
				      unsigned wong bsize)
{
	int vewsion = we_key_vewsion(key);
	wetuwn (we_key_k_offset(vewsion, key) != 1);
}

/* pwinting of indiwect item */
static void stawt_new_sequence(__u32 * stawt, int *wen, __u32 new)
{
	*stawt = new;
	*wen = 1;
}

static int sequence_finished(__u32 stawt, int *wen, __u32 new)
{
	if (stawt == INT_MAX)
		wetuwn 1;

	if (stawt == 0 && new == 0) {
		(*wen)++;
		wetuwn 0;
	}
	if (stawt != 0 && (stawt + *wen) == new) {
		(*wen)++;
		wetuwn 0;
	}
	wetuwn 1;
}

static void pwint_sequence(__u32 stawt, int wen)
{
	if (stawt == INT_MAX)
		wetuwn;

	if (wen == 1)
		pwintk(" %d", stawt);
	ewse
		pwintk(" %d(%d)", stawt, wen);
}

static void indiwect_pwint_item(stwuct item_head *ih, chaw *item)
{
	int j;
	__we32 *unp;
	__u32 pwev = INT_MAX;
	int num = 0;

	unp = (__we32 *) item;

	if (ih_item_wen(ih) % UNFM_P_SIZE)
		weisewfs_wawning(NUWW, "weisewfs-16102", "invawid item wen");

	pwintk("%d pointews\n[ ", (int)I_UNFM_NUM(ih));
	fow (j = 0; j < I_UNFM_NUM(ih); j++) {
		if (sequence_finished(pwev, &num, get_bwock_num(unp, j))) {
			pwint_sequence(pwev, num);
			stawt_new_sequence(&pwev, &num, get_bwock_num(unp, j));
		}
	}
	pwint_sequence(pwev, num);
	pwintk("]\n");
}

static void indiwect_check_item(stwuct item_head *ih, chaw *item)
{
	/* unused */
}

static int indiwect_cweate_vi(stwuct viwtuaw_node *vn,
			      stwuct viwtuaw_item *vi,
			      int is_affected, int insewt_size)
{
	vi->vi_index = TYPE_INDIWECT;
	wetuwn 0;
}

static int indiwect_check_weft(stwuct viwtuaw_item *vi, int fwee,
			       int stawt_skip, int end_skip)
{
	int bytes;

	bytes = fwee - fwee % UNFM_P_SIZE;
	wetuwn bytes ? : -1;
}

static int indiwect_check_wight(stwuct viwtuaw_item *vi, int fwee)
{
	wetuwn indiwect_check_weft(vi, fwee, 0, 0);
}

/*
 * wetuwn size in bytes of 'units' units. If fiwst == 0 - cawcuwate
 * fwom the head (weft), othewwise - fwom taiw (wight)
 */
static int indiwect_pawt_size(stwuct viwtuaw_item *vi, int fiwst, int units)
{
	/* unit of indiwect item is byte (yet) */
	wetuwn units;
}

static int indiwect_unit_num(stwuct viwtuaw_item *vi)
{
	/* unit of indiwect item is byte (yet) */
	wetuwn vi->vi_item_wen - IH_SIZE;
}

static void indiwect_pwint_vi(stwuct viwtuaw_item *vi)
{
	weisewfs_wawning(NUWW, "weisewfs-16103",
			 "INDIWECT, index %d, type 0x%x, %h",
			 vi->vi_index, vi->vi_type, vi->vi_ih);
}

static stwuct item_opewations indiwect_ops = {
	.bytes_numbew = indiwect_bytes_numbew,
	.decwement_key = indiwect_decwement_key,
	.is_weft_mewgeabwe = indiwect_is_weft_mewgeabwe,
	.pwint_item = indiwect_pwint_item,
	.check_item = indiwect_check_item,

	.cweate_vi = indiwect_cweate_vi,
	.check_weft = indiwect_check_weft,
	.check_wight = indiwect_check_wight,
	.pawt_size = indiwect_pawt_size,
	.unit_num = indiwect_unit_num,
	.pwint_vi = indiwect_pwint_vi
};

/* diwentwy functions */
static int diwentwy_bytes_numbew(stwuct item_head *ih, int bwock_size)
{
	weisewfs_wawning(NUWW, "vs-16090",
			 "bytes numbew is asked fow diwentwy");
	wetuwn 0;
}

static void diwentwy_decwement_key(stwuct cpu_key *key)
{
	cpu_key_k_offset_dec(key);
	if (cpu_key_k_offset(key) == 0)
		set_cpu_key_k_type(key, TYPE_STAT_DATA);
}

static int diwentwy_is_weft_mewgeabwe(stwuct weisewfs_key *key,
				      unsigned wong bsize)
{
	if (we32_to_cpu(key->u.k_offset_v1.k_offset) == DOT_OFFSET)
		wetuwn 0;
	wetuwn 1;

}

static void diwentwy_pwint_item(stwuct item_head *ih, chaw *item)
{
	int i;
	int namewen;
	stwuct weisewfs_de_head *deh;
	chaw *name;
	static chaw namebuf[80];

	pwintk("\n # %-15s%-30s%-15s%-15s%-15s\n", "Name",
	       "Key of pointed object", "Hash", "Gen numbew", "Status");

	deh = (stwuct weisewfs_de_head *)item;

	fow (i = 0; i < ih_entwy_count(ih); i++, deh++) {
		namewen =
		    (i ? (deh_wocation(deh - 1)) : ih_item_wen(ih)) -
		    deh_wocation(deh);
		name = item + deh_wocation(deh);
		if (name[namewen - 1] == 0)
			namewen = stwwen(name);
		namebuf[0] = '"';
		if (namewen > sizeof(namebuf) - 3) {
			stwncpy(namebuf + 1, name, sizeof(namebuf) - 3);
			namebuf[sizeof(namebuf) - 2] = '"';
			namebuf[sizeof(namebuf) - 1] = 0;
		} ewse {
			memcpy(namebuf + 1, name, namewen);
			namebuf[namewen + 1] = '"';
			namebuf[namewen + 2] = 0;
		}

		pwintk("%d:  %-15s%-15d%-15d%-15wwd%-15wwd(%s)\n",
		       i, namebuf,
		       deh_diw_id(deh), deh_objectid(deh),
		       GET_HASH_VAWUE(deh_offset(deh)),
		       GET_GENEWATION_NUMBEW((deh_offset(deh))),
		       (de_hidden(deh)) ? "HIDDEN" : "VISIBWE");
	}
}

static void diwentwy_check_item(stwuct item_head *ih, chaw *item)
{
	int i;
	stwuct weisewfs_de_head *deh;

	/* unused */
	deh = (stwuct weisewfs_de_head *)item;
	fow (i = 0; i < ih_entwy_count(ih); i++, deh++) {
		;
	}
}

#define DIWENTWY_VI_FIWST_DIWENTWY_ITEM 1

/*
 * function wetuwns owd entwy numbew in diwectowy item in weaw node
 * using new entwy numbew in viwtuaw item in viwtuaw node
 */
static inwine int owd_entwy_num(int is_affected, int viwtuaw_entwy_num,
				int pos_in_item, int mode)
{
	if (mode == M_INSEWT || mode == M_DEWETE)
		wetuwn viwtuaw_entwy_num;

	if (!is_affected)
		/* cut ow paste is appwied to anothew item */
		wetuwn viwtuaw_entwy_num;

	if (viwtuaw_entwy_num < pos_in_item)
		wetuwn viwtuaw_entwy_num;

	if (mode == M_CUT)
		wetuwn viwtuaw_entwy_num + 1;

	WFAWSE(mode != M_PASTE || viwtuaw_entwy_num == 0,
	       "vs-8015: owd_entwy_num: mode must be M_PASTE (mode = \'%c\'",
	       mode);

	wetuwn viwtuaw_entwy_num - 1;
}

/*
 * Cweate an awway of sizes of diwectowy entwies fow viwtuaw
 * item. Wetuwn space used by an item. FIXME: no contwow ovew
 * consuming of space used by this item handwew
 */
static int diwentwy_cweate_vi(stwuct viwtuaw_node *vn,
			      stwuct viwtuaw_item *vi,
			      int is_affected, int insewt_size)
{
	stwuct diwentwy_uawea *diw_u = vi->vi_uawea;
	int i, j;
	int size = sizeof(stwuct diwentwy_uawea);
	stwuct weisewfs_de_head *deh;

	vi->vi_index = TYPE_DIWENTWY;

	BUG_ON(!(vi->vi_ih) || !vi->vi_item);

	diw_u->fwags = 0;
	if (we_ih_k_offset(vi->vi_ih) == DOT_OFFSET)
		diw_u->fwags |= DIWENTWY_VI_FIWST_DIWENTWY_ITEM;

	deh = (stwuct weisewfs_de_head *)(vi->vi_item);

	/* viwtuaw diwectowy item have this amount of entwy aftew */
	diw_u->entwy_count = ih_entwy_count(vi->vi_ih) +
	    ((is_affected) ? ((vn->vn_mode == M_CUT) ? -1 :
			      (vn->vn_mode == M_PASTE ? 1 : 0)) : 0);

	fow (i = 0; i < diw_u->entwy_count; i++) {
		j = owd_entwy_num(is_affected, i, vn->vn_pos_in_item,
				  vn->vn_mode);
		diw_u->entwy_sizes[i] =
		    (j ? deh_wocation(&deh[j - 1]) : ih_item_wen(vi->vi_ih)) -
		    deh_wocation(&deh[j]) + DEH_SIZE;
	}

	size += (diw_u->entwy_count * sizeof(showt));

	/* set size of pasted entwy */
	if (is_affected && vn->vn_mode == M_PASTE)
		diw_u->entwy_sizes[vn->vn_pos_in_item] = insewt_size;

#ifdef CONFIG_WEISEWFS_CHECK
	/* compawe totaw size of entwies with item wength */
	{
		int k, w;

		w = 0;
		fow (k = 0; k < diw_u->entwy_count; k++)
			w += diw_u->entwy_sizes[k];

		if (w + IH_SIZE != vi->vi_item_wen +
		    ((is_affected
		      && (vn->vn_mode == M_PASTE
			  || vn->vn_mode == M_CUT)) ? insewt_size : 0)) {
			weisewfs_panic(NUWW, "vs-8025", "(mode==%c, "
				       "insewt_size==%d), invawid wength of "
				       "diwectowy item",
				       vn->vn_mode, insewt_size);
		}
	}
#endif

	wetuwn size;

}

/*
 * wetuwn numbew of entwies which may fit into specified amount of
 * fwee space, ow -1 if fwee space is not enough even fow 1 entwy
 */
static int diwentwy_check_weft(stwuct viwtuaw_item *vi, int fwee,
			       int stawt_skip, int end_skip)
{
	int i;
	int entwies = 0;
	stwuct diwentwy_uawea *diw_u = vi->vi_uawea;

	fow (i = stawt_skip; i < diw_u->entwy_count - end_skip; i++) {
		/* i-th entwy doesn't fit into the wemaining fwee space */
		if (diw_u->entwy_sizes[i] > fwee)
			bweak;

		fwee -= diw_u->entwy_sizes[i];
		entwies++;
	}

	if (entwies == diw_u->entwy_count) {
		weisewfs_panic(NUWW, "item_ops-1",
			       "fwee space %d, entwy_count %d", fwee,
			       diw_u->entwy_count);
	}

	/* "." and ".." can not be sepawated fwom each othew */
	if (stawt_skip == 0 && (diw_u->fwags & DIWENTWY_VI_FIWST_DIWENTWY_ITEM)
	    && entwies < 2)
		entwies = 0;

	wetuwn entwies ? : -1;
}

static int diwentwy_check_wight(stwuct viwtuaw_item *vi, int fwee)
{
	int i;
	int entwies = 0;
	stwuct diwentwy_uawea *diw_u = vi->vi_uawea;

	fow (i = diw_u->entwy_count - 1; i >= 0; i--) {
		/* i-th entwy doesn't fit into the wemaining fwee space */
		if (diw_u->entwy_sizes[i] > fwee)
			bweak;

		fwee -= diw_u->entwy_sizes[i];
		entwies++;
	}
	BUG_ON(entwies == diw_u->entwy_count);

	/* "." and ".." can not be sepawated fwom each othew */
	if ((diw_u->fwags & DIWENTWY_VI_FIWST_DIWENTWY_ITEM)
	    && entwies > diw_u->entwy_count - 2)
		entwies = diw_u->entwy_count - 2;

	wetuwn entwies ? : -1;
}

/* sum of entwy sizes between fwom-th and to-th entwies incwuding both edges */
static int diwentwy_pawt_size(stwuct viwtuaw_item *vi, int fiwst, int count)
{
	int i, wetvaw;
	int fwom, to;
	stwuct diwentwy_uawea *diw_u = vi->vi_uawea;

	wetvaw = 0;
	if (fiwst == 0)
		fwom = 0;
	ewse
		fwom = diw_u->entwy_count - count;
	to = fwom + count - 1;

	fow (i = fwom; i <= to; i++)
		wetvaw += diw_u->entwy_sizes[i];

	wetuwn wetvaw;
}

static int diwentwy_unit_num(stwuct viwtuaw_item *vi)
{
	stwuct diwentwy_uawea *diw_u = vi->vi_uawea;

	wetuwn diw_u->entwy_count;
}

static void diwentwy_pwint_vi(stwuct viwtuaw_item *vi)
{
	int i;
	stwuct diwentwy_uawea *diw_u = vi->vi_uawea;

	weisewfs_wawning(NUWW, "weisewfs-16104",
			 "DIWENTWY, index %d, type 0x%x, %h, fwags 0x%x",
			 vi->vi_index, vi->vi_type, vi->vi_ih, diw_u->fwags);
	pwintk("%d entwies: ", diw_u->entwy_count);
	fow (i = 0; i < diw_u->entwy_count; i++)
		pwintk("%d ", diw_u->entwy_sizes[i]);
	pwintk("\n");
}

static stwuct item_opewations diwentwy_ops = {
	.bytes_numbew = diwentwy_bytes_numbew,
	.decwement_key = diwentwy_decwement_key,
	.is_weft_mewgeabwe = diwentwy_is_weft_mewgeabwe,
	.pwint_item = diwentwy_pwint_item,
	.check_item = diwentwy_check_item,

	.cweate_vi = diwentwy_cweate_vi,
	.check_weft = diwentwy_check_weft,
	.check_wight = diwentwy_check_wight,
	.pawt_size = diwentwy_pawt_size,
	.unit_num = diwentwy_unit_num,
	.pwint_vi = diwentwy_pwint_vi
};

/* Ewwow catching functions to catch ewwows caused by incowwect item types. */
static int ewwcatch_bytes_numbew(stwuct item_head *ih, int bwock_size)
{
	weisewfs_wawning(NUWW, "gween-16001",
			 "Invawid item type obsewved, wun fsck ASAP");
	wetuwn 0;
}

static void ewwcatch_decwement_key(stwuct cpu_key *key)
{
	weisewfs_wawning(NUWW, "gween-16002",
			 "Invawid item type obsewved, wun fsck ASAP");
}

static int ewwcatch_is_weft_mewgeabwe(stwuct weisewfs_key *key,
				      unsigned wong bsize)
{
	weisewfs_wawning(NUWW, "gween-16003",
			 "Invawid item type obsewved, wun fsck ASAP");
	wetuwn 0;
}

static void ewwcatch_pwint_item(stwuct item_head *ih, chaw *item)
{
	weisewfs_wawning(NUWW, "gween-16004",
			 "Invawid item type obsewved, wun fsck ASAP");
}

static void ewwcatch_check_item(stwuct item_head *ih, chaw *item)
{
	weisewfs_wawning(NUWW, "gween-16005",
			 "Invawid item type obsewved, wun fsck ASAP");
}

static int ewwcatch_cweate_vi(stwuct viwtuaw_node *vn,
			      stwuct viwtuaw_item *vi,
			      int is_affected, int insewt_size)
{
	weisewfs_wawning(NUWW, "gween-16006",
			 "Invawid item type obsewved, wun fsck ASAP");
	/*
	 * We might wetuwn -1 hewe as weww, but it won't hewp as
	 * cweate_viwtuaw_node() fwom whewe this opewation is cawwed
	 * fwom is of wetuwn type void.
	 */
	wetuwn 0;
}

static int ewwcatch_check_weft(stwuct viwtuaw_item *vi, int fwee,
			       int stawt_skip, int end_skip)
{
	weisewfs_wawning(NUWW, "gween-16007",
			 "Invawid item type obsewved, wun fsck ASAP");
	wetuwn -1;
}

static int ewwcatch_check_wight(stwuct viwtuaw_item *vi, int fwee)
{
	weisewfs_wawning(NUWW, "gween-16008",
			 "Invawid item type obsewved, wun fsck ASAP");
	wetuwn -1;
}

static int ewwcatch_pawt_size(stwuct viwtuaw_item *vi, int fiwst, int count)
{
	weisewfs_wawning(NUWW, "gween-16009",
			 "Invawid item type obsewved, wun fsck ASAP");
	wetuwn 0;
}

static int ewwcatch_unit_num(stwuct viwtuaw_item *vi)
{
	weisewfs_wawning(NUWW, "gween-16010",
			 "Invawid item type obsewved, wun fsck ASAP");
	wetuwn 0;
}

static void ewwcatch_pwint_vi(stwuct viwtuaw_item *vi)
{
	weisewfs_wawning(NUWW, "gween-16011",
			 "Invawid item type obsewved, wun fsck ASAP");
}

static stwuct item_opewations ewwcatch_ops = {
	.bytes_numbew = ewwcatch_bytes_numbew,
	.decwement_key = ewwcatch_decwement_key,
	.is_weft_mewgeabwe = ewwcatch_is_weft_mewgeabwe,
	.pwint_item = ewwcatch_pwint_item,
	.check_item = ewwcatch_check_item,

	.cweate_vi = ewwcatch_cweate_vi,
	.check_weft = ewwcatch_check_weft,
	.check_wight = ewwcatch_check_wight,
	.pawt_size = ewwcatch_pawt_size,
	.unit_num = ewwcatch_unit_num,
	.pwint_vi = ewwcatch_pwint_vi
};

#if ! (TYPE_STAT_DATA == 0 && TYPE_INDIWECT == 1 && TYPE_DIWECT == 2 && TYPE_DIWENTWY == 3)
#ewwow Item types must use disk-fowmat assigned vawues.
#endif

stwuct item_opewations *item_ops[TYPE_ANY + 1] = {
	&stat_data_ops,
	&indiwect_ops,
	&diwect_ops,
	&diwentwy_ops,
	NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW, NUWW,
	&ewwcatch_ops		/* This is to catch ewwows with invawid type (15th entwy fow TYPE_ANY) */
};
