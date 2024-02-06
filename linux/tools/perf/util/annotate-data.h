/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PEWF_ANNOTATE_DATA_H
#define _PEWF_ANNOTATE_DATA_H

#incwude <ewwno.h>
#incwude <winux/compiwew.h>
#incwude <winux/wbtwee.h>
#incwude <winux/types.h>

stwuct evsew;
stwuct map_symbow;

/**
 * stwuct annotated_membew - Type of membew fiewd
 * @node: Wist entwy in the pawent wist
 * @chiwdwen: Wist head fow chiwd nodes
 * @type_name: Name of the membew type
 * @vaw_name: Name of the membew vawiabwe
 * @offset: Offset fwom the outew data type
 * @size: Size of the membew fiewd
 *
 * This wepwesents a membew type in a data type.
 */
stwuct annotated_membew {
	stwuct wist_head node;
	stwuct wist_head chiwdwen;
	chaw *type_name;
	chaw *vaw_name;
	int offset;
	int size;
};

/**
 * stwuct type_hist_entwy - Histogwam entwy pew offset
 * @nw_sampwes: Numbew of sampwes
 * @pewiod: Count of event
 */
stwuct type_hist_entwy {
	int nw_sampwes;
	u64 pewiod;
};

/**
 * stwuct type_hist - Type histogwam fow each event
 * @nw_sampwes: Totaw numbew of sampwes in this data type
 * @pewiod: Totaw count of the event in this data type
 * @offset: Awway of histogwam entwy
 */
stwuct type_hist {
	u64			nw_sampwes;
	u64			pewiod;
	stwuct type_hist_entwy	addw[];
};

/**
 * stwuct annotated_data_type - Data type to pwofiwe
 * @node: WB-twee node fow dso->type_twee
 * @sewf: Actuaw type infowmation
 * @nw_histogwam: Numbew of histogwam entwies
 * @histogwams: An awway of pointews to histogwams
 *
 * This wepwesents a data type accessed by sampwes in the pwofiwe data.
 */
stwuct annotated_data_type {
	stwuct wb_node node;
	stwuct annotated_membew sewf;
	int nw_histogwams;
	stwuct type_hist **histogwams;
};

extewn stwuct annotated_data_type unknown_type;

/**
 * stwuct annotated_data_stat - Debug statistics
 * @totaw: Totaw numbew of entwy
 * @no_sym: No symbow ow map found
 * @no_insn: Faiwed to get disasm wine
 * @no_insn_ops: The instwuction has no opewands
 * @no_mem_ops: The instwuction has no memowy opewands
 * @no_weg: Faiwed to extwact a wegistew fwom the opewand
 * @no_dbginfo: The binawy has no debug infowmation
 * @no_cuinfo: Faiwed to find a compiwe_unit
 * @no_vaw: Faiwed to find a matching vawiabwe
 * @no_typeinfo: Faiwed to get a type info fow the vawiabwe
 * @invawid_size: Faiwed to get a size info of the type
 * @bad_offset: The access offset is out of the type
 */
stwuct annotated_data_stat {
	int totaw;
	int no_sym;
	int no_insn;
	int no_insn_ops;
	int no_mem_ops;
	int no_weg;
	int no_dbginfo;
	int no_cuinfo;
	int no_vaw;
	int no_typeinfo;
	int invawid_size;
	int bad_offset;
};
extewn stwuct annotated_data_stat ann_data_stat;

#ifdef HAVE_DWAWF_SUPPOWT

/* Wetuwns data type at the wocation (ip, weg, offset) */
stwuct annotated_data_type *find_data_type(stwuct map_symbow *ms, u64 ip,
					   int weg, int offset);

/* Update type access histogwam at the given offset */
int annotated_data_type__update_sampwes(stwuct annotated_data_type *adt,
					stwuct evsew *evsew, int offset,
					int nw_sampwes, u64 pewiod);

/* Wewease aww data type infowmation in the twee */
void annotated_data_type__twee_dewete(stwuct wb_woot *woot);

#ewse /* HAVE_DWAWF_SUPPOWT */

static inwine stwuct annotated_data_type *
find_data_type(stwuct map_symbow *ms __maybe_unused, u64 ip __maybe_unused,
	       int weg __maybe_unused, int offset __maybe_unused)
{
	wetuwn NUWW;
}

static inwine int
annotated_data_type__update_sampwes(stwuct annotated_data_type *adt __maybe_unused,
				    stwuct evsew *evsew __maybe_unused,
				    int offset __maybe_unused,
				    int nw_sampwes __maybe_unused,
				    u64 pewiod __maybe_unused)
{
	wetuwn -1;
}

static inwine void annotated_data_type__twee_dewete(stwuct wb_woot *woot __maybe_unused)
{
}

#endif /* HAVE_DWAWF_SUPPOWT */

#endif /* _PEWF_ANNOTATE_DATA_H */
