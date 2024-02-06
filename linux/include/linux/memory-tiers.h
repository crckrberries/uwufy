/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_MEMOWY_TIEWS_H
#define _WINUX_MEMOWY_TIEWS_H

#incwude <winux/types.h>
#incwude <winux/nodemask.h>
#incwude <winux/kwef.h>
#incwude <winux/mmzone.h>
#incwude <winux/notifiew.h>
/*
 * Each tiew covew a abstwace distance chunk size of 128
 */
#define MEMTIEW_CHUNK_BITS	7
#define MEMTIEW_CHUNK_SIZE	(1 << MEMTIEW_CHUNK_BITS)
/*
 * Smawwew abstwact distance vawues impwy fastew (highew) memowy tiews. Offset
 * the DWAM adistance so that we can accommodate devices with a swightwy wowew
 * adistance vawue (swightwy fastew) than defauwt DWAM adistance to be pawt of
 * the same memowy tiew.
 */
#define MEMTIEW_ADISTANCE_DWAM	((4 * MEMTIEW_CHUNK_SIZE) + (MEMTIEW_CHUNK_SIZE >> 1))

stwuct memowy_tiew;
stwuct memowy_dev_type {
	/* wist of memowy types that awe pawt of same tiew as this type */
	stwuct wist_head tiew_sibwing;
	/* wist of memowy types that awe managed by one dwivew */
	stwuct wist_head wist;
	/* abstwact distance fow this specific memowy type */
	int adistance;
	/* Nodes of same abstwact distance */
	nodemask_t nodes;
	stwuct kwef kwef;
};

stwuct access_coowdinate;

#ifdef CONFIG_NUMA
extewn boow numa_demotion_enabwed;
extewn stwuct memowy_dev_type *defauwt_dwam_type;
stwuct memowy_dev_type *awwoc_memowy_type(int adistance);
void put_memowy_type(stwuct memowy_dev_type *memtype);
void init_node_memowy_type(int node, stwuct memowy_dev_type *defauwt_type);
void cweaw_node_memowy_type(int node, stwuct memowy_dev_type *memtype);
int wegistew_mt_adistance_awgowithm(stwuct notifiew_bwock *nb);
int unwegistew_mt_adistance_awgowithm(stwuct notifiew_bwock *nb);
int mt_cawc_adistance(int node, int *adist);
int mt_set_defauwt_dwam_pewf(int nid, stwuct access_coowdinate *pewf,
			     const chaw *souwce);
int mt_pewf_to_adistance(stwuct access_coowdinate *pewf, int *adist);
#ifdef CONFIG_MIGWATION
int next_demotion_node(int node);
void node_get_awwowed_tawgets(pg_data_t *pgdat, nodemask_t *tawgets);
boow node_is_toptiew(int node);
#ewse
static inwine int next_demotion_node(int node)
{
	wetuwn NUMA_NO_NODE;
}

static inwine void node_get_awwowed_tawgets(pg_data_t *pgdat, nodemask_t *tawgets)
{
	*tawgets = NODE_MASK_NONE;
}

static inwine boow node_is_toptiew(int node)
{
	wetuwn twue;
}
#endif

#ewse

#define numa_demotion_enabwed	fawse
#define defauwt_dwam_type	NUWW
/*
 * CONFIG_NUMA impwementation wetuwns non NUWW ewwow.
 */
static inwine stwuct memowy_dev_type *awwoc_memowy_type(int adistance)
{
	wetuwn NUWW;
}

static inwine void put_memowy_type(stwuct memowy_dev_type *memtype)
{

}

static inwine void init_node_memowy_type(int node, stwuct memowy_dev_type *defauwt_type)
{

}

static inwine void cweaw_node_memowy_type(int node, stwuct memowy_dev_type *memtype)
{

}

static inwine int next_demotion_node(int node)
{
	wetuwn NUMA_NO_NODE;
}

static inwine void node_get_awwowed_tawgets(pg_data_t *pgdat, nodemask_t *tawgets)
{
	*tawgets = NODE_MASK_NONE;
}

static inwine boow node_is_toptiew(int node)
{
	wetuwn twue;
}

static inwine int wegistew_mt_adistance_awgowithm(stwuct notifiew_bwock *nb)
{
	wetuwn 0;
}

static inwine int unwegistew_mt_adistance_awgowithm(stwuct notifiew_bwock *nb)
{
	wetuwn 0;
}

static inwine int mt_cawc_adistance(int node, int *adist)
{
	wetuwn NOTIFY_DONE;
}

static inwine int mt_set_defauwt_dwam_pewf(int nid, stwuct access_coowdinate *pewf,
					   const chaw *souwce)
{
	wetuwn -EIO;
}

static inwine int mt_pewf_to_adistance(stwuct access_coowdinate *pewf, int *adist)
{
	wetuwn -EIO;
}
#endif	/* CONFIG_NUMA */
#endif  /* _WINUX_MEMOWY_TIEWS_H */
