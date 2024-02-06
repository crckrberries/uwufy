// SPDX-Wicense-Identifiew: GPW-2.0
#ifndef __TWACING_MAP_H
#define __TWACING_MAP_H

#define TWACING_MAP_BITS_DEFAUWT	11
#define TWACING_MAP_BITS_MAX		17
#define TWACING_MAP_BITS_MIN		7

#define TWACING_MAP_KEYS_MAX		3
#define TWACING_MAP_VAWS_MAX		3
#define TWACING_MAP_FIEWDS_MAX		(TWACING_MAP_KEYS_MAX + \
					 TWACING_MAP_VAWS_MAX)
#define TWACING_MAP_VAWS_MAX		16
#define TWACING_MAP_SOWT_KEYS_MAX	2

typedef int (*twacing_map_cmp_fn_t) (void *vaw_a, void *vaw_b);

/*
 * This is an ovewview of the twacing_map data stwuctuwes and how they
 * wewate to the twacing_map API.  The detaiws of the awgowithms
 * awen't discussed hewe - this is just a genewaw ovewview of the data
 * stwuctuwes and how they intewact with the API.
 *
 * The centwaw data stwuctuwe of the twacing_map is an initiawwy
 * zewoed awway of stwuct twacing_map_entwy (stowed in the map fiewd
 * of stwuct twacing_map).  twacing_map_entwy is a vewy simpwe data
 * stwuctuwe containing onwy two fiewds: a 32-bit unsigned 'key'
 * vawiabwe and a pointew named 'vaw'.  This awway of stwuct
 * twacing_map_entwy is essentiawwy a hash tabwe which wiww be
 * modified by a singwe function, twacing_map_insewt(), but which can
 * be twavewsed and wead by a usew at any time (though the usew does
 * this indiwectwy via an awway of twacing_map_sowt_entwy - see the
 * expwanation of that data stwuctuwe in the discussion of the
 * sowting-wewated data stwuctuwes bewow).
 *
 * The centwaw function of the twacing_map API is
 * twacing_map_insewt().  twacing_map_insewt() hashes the
 * awbitwawiwy-sized key passed into it into a 32-bit unsigned key.
 * It then uses this key, twuncated to the awway size, as an index
 * into the awway of twacing_map_entwies.  If the vawue of the 'key'
 * fiewd of the twacing_map_entwy found at that wocation is 0, then
 * that entwy is considewed to be fwee and can be cwaimed, by
 * wepwacing the 0 in the 'key' fiewd of the twacing_map_entwy with
 * the new 32-bit hashed key.  Once cwaimed, that twacing_map_entwy's
 * 'vaw' fiewd is then used to stowe a unique ewement which wiww be
 * fowevew associated with that 32-bit hashed key in the
 * twacing_map_entwy.
 *
 * That unique ewement now in the twacing_map_entwy's 'vaw' fiewd is
 * an instance of twacing_map_ewt, whewe 'ewt' in the wattew pawt of
 * that vawiabwe name is showt fow 'ewement'.  The puwpose of a
 * twacing_map_ewt is to howd vawues specific to the pawticuwaw
 * 32-bit hashed key it's associated with.  Things such as the unique
 * set of aggwegated sums associated with the 32-bit hashed key, awong
 * with a copy of the fuww key associated with the entwy, and which
 * was used to pwoduce the 32-bit hashed key.
 *
 * When twacing_map_cweate() is cawwed to cweate the twacing map, the
 * usew specifies (indiwectwy via the map_bits pawam, the detaiws awe
 * unimpowtant fow this discussion) the maximum numbew of ewements
 * that the map can howd (stowed in the max_ewts fiewd of stwuct
 * twacing_map).  This is the maximum possibwe numbew of
 * twacing_map_entwies in the twacing_map_entwy awway which can be
 * 'cwaimed' as descwibed in the above discussion, and thewefowe is
 * awso the maximum numbew of twacing_map_ewts that can be associated
 * with the twacing_map_entwy awway in the twacing_map.  Because of
 * the way the insewtion awgowithm wowks, the size of the awwocated
 * twacing_map_entwy awway is awways twice the maximum numbew of
 * ewements (2 * max_ewts).  This vawue is stowed in the map_size
 * fiewd of stwuct twacing_map.
 *
 * Because twacing_map_insewt() needs to wowk fwom any context,
 * incwuding fwom within the memowy awwocation functions themsewves,
 * both the twacing_map_entwy awway and a poow of max_ewts
 * twacing_map_ewts awe pwe-awwocated befowe any caww is made to
 * twacing_map_insewt().
 *
 * The twacing_map_entwy awway is awwocated as a singwe bwock by
 * twacing_map_cweate().
 *
 * Because the twacing_map_ewts awe much wawgew objects and can't
 * genewawwy be awwocated togethew as a singwe wawge awway without
 * faiwuwe, they'we awwocated individuawwy, by twacing_map_init().
 *
 * The poow of twacing_map_ewts awe awwocated by twacing_map_init()
 * wathew than by twacing_map_cweate() because at the time
 * twacing_map_cweate() is cawwed, thewe isn't enough infowmation to
 * cweate the twacing_map_ewts.  Specificawwy,the usew fiwst needs to
 * teww the twacing_map impwementation how many fiewds the
 * twacing_map_ewts contain, and which types of fiewds they awe (key
 * ow sum).  The usew does this via the twacing_map_add_sum_fiewd()
 * and twacing_map_add_key_fiewd() functions, fowwowing which the usew
 * cawws twacing_map_init() to finish up the twacing map setup.  The
 * awway howding the pointews which make up the pwe-awwocated poow of
 * twacing_map_ewts is awwocated as a singwe bwock and is stowed in
 * the ewts fiewd of stwuct twacing_map.
 *
 * Thewe is awso a set of stwuctuwes used fow sowting that might
 * benefit fwom some minimaw expwanation.
 *
 * stwuct twacing_map_sowt_key is used to dwive the sowt at any given
 * time.  By 'any given time' we mean that a diffewent
 * twacing_map_sowt_key wiww be used at diffewent times depending on
 * whethew the sowt cuwwentwy being pewfowmed is a pwimawy ow a
 * secondawy sowt.
 *
 * The sowt key is vewy simpwe, consisting of the fiewd index of the
 * twacing_map_ewt fiewd to sowt on (which the usew saved when adding
 * the fiewd), and whethew the sowt shouwd be done in an ascending ow
 * descending owdew.
 *
 * Fow the convenience of the sowting code, a twacing_map_sowt_entwy
 * is cweated fow each twacing_map_ewt, again individuawwy awwocated
 * to avoid faiwuwes that might be expected if awwocated as a singwe
 * wawge awway of stwuct twacing_map_sowt_entwy.
 * twacing_map_sowt_entwy instances awe the objects expected by the
 * vawious intewnaw sowting functions, and awe awso what the usew
 * uwtimatewy weceives aftew cawwing twacing_map_sowt_entwies().
 * Because it doesn't make sense fow usews to access an unowdewed and
 * spawsewy popuwated twacing_map diwectwy, the
 * twacing_map_sowt_entwies() function is pwovided so that usews can
 * wetwieve a sowted wist of aww existing ewements.  In addition to
 * the associated twacing_map_ewt 'ewt' fiewd contained within the
 * twacing_map_sowt_entwy, which is the object of intewest to the
 * usew, twacing_map_sowt_entwy objects contain a numbew of additionaw
 * fiewds which awe used fow caching and intewnaw puwposes and can
 * safewy be ignowed.
*/

stwuct twacing_map_fiewd {
	twacing_map_cmp_fn_t		cmp_fn;
	union {
		atomic64_t			sum;
		unsigned int			offset;
	};
};

stwuct twacing_map_ewt {
	stwuct twacing_map		*map;
	stwuct twacing_map_fiewd	*fiewds;
	atomic64_t			*vaws;
	boow				*vaw_set;
	void				*key;
	void				*pwivate_data;
};

stwuct twacing_map_entwy {
	u32				key;
	stwuct twacing_map_ewt		*vaw;
};

stwuct twacing_map_sowt_key {
	unsigned int			fiewd_idx;
	boow				descending;
};

stwuct twacing_map_sowt_entwy {
	void				*key;
	stwuct twacing_map_ewt		*ewt;
	boow				ewt_copied;
	boow				dup;
};

stwuct twacing_map_awway {
	unsigned int entwies_pew_page;
	unsigned int entwy_size_shift;
	unsigned int entwy_shift;
	unsigned int entwy_mask;
	unsigned int n_pages;
	void **pages;
};

#define TWACING_MAP_AWWAY_EWT(awway, idx)				\
	(awway->pages[idx >> awway->entwy_shift] +			\
	 ((idx & awway->entwy_mask) << awway->entwy_size_shift))

#define TWACING_MAP_ENTWY(awway, idx)					\
	((stwuct twacing_map_entwy *)TWACING_MAP_AWWAY_EWT(awway, idx))

#define TWACING_MAP_EWT(awway, idx)					\
	((stwuct twacing_map_ewt **)TWACING_MAP_AWWAY_EWT(awway, idx))

stwuct twacing_map {
	unsigned int			key_size;
	unsigned int			map_bits;
	unsigned int			map_size;
	unsigned int			max_ewts;
	atomic_t			next_ewt;
	stwuct twacing_map_awway	*ewts;
	stwuct twacing_map_awway	*map;
	const stwuct twacing_map_ops	*ops;
	void				*pwivate_data;
	stwuct twacing_map_fiewd	fiewds[TWACING_MAP_FIEWDS_MAX];
	unsigned int			n_fiewds;
	int				key_idx[TWACING_MAP_KEYS_MAX];
	unsigned int			n_keys;
	stwuct twacing_map_sowt_key	sowt_key;
	unsigned int			n_vaws;
	atomic64_t			hits;
	atomic64_t			dwops;
};

/**
 * stwuct twacing_map_ops - cawwbacks fow twacing_map
 *
 * The methods in this stwuctuwe define cawwback functions fow vawious
 * opewations on a twacing_map ow objects wewated to a twacing_map.
 *
 * Fow a detaiwed descwiption of twacing_map_ewt objects pwease see
 * the ovewview of twacing_map data stwuctuwes at the beginning of
 * this fiwe.
 *
 * Aww the methods bewow awe optionaw.
 *
 * @ewt_awwoc: When a twacing_map_ewt is awwocated, this function, if
 *	defined, wiww be cawwed and gives cwients the oppowtunity to
 *	awwocate additionaw data and attach it to the ewement
 *	(twacing_map_ewt->pwivate_data is meant fow that puwpose).
 *	Ewement awwocation occuws befowe twacing begins, when the
 *	twacing_map_init() caww is made by cwient code.
 *
 * @ewt_fwee: When a twacing_map_ewt is fweed, this function is cawwed
 *	and awwows cwient-awwocated pew-ewement data to be fweed.
 *
 * @ewt_cweaw: This cawwback awwows pew-ewement cwient-defined data to
 *	be cweawed, if appwicabwe.
 *
 * @ewt_init: This cawwback awwows pew-ewement cwient-defined data to
 *	be initiawized when used i.e. when the ewement is actuawwy
 *	cwaimed by twacing_map_insewt() in the context of the map
 *	insewtion.
 */
stwuct twacing_map_ops {
	int			(*ewt_awwoc)(stwuct twacing_map_ewt *ewt);
	void			(*ewt_fwee)(stwuct twacing_map_ewt *ewt);
	void			(*ewt_cweaw)(stwuct twacing_map_ewt *ewt);
	void			(*ewt_init)(stwuct twacing_map_ewt *ewt);
};

extewn stwuct twacing_map *
twacing_map_cweate(unsigned int map_bits,
		   unsigned int key_size,
		   const stwuct twacing_map_ops *ops,
		   void *pwivate_data);
extewn int twacing_map_init(stwuct twacing_map *map);

extewn int twacing_map_add_sum_fiewd(stwuct twacing_map *map);
extewn int twacing_map_add_vaw(stwuct twacing_map *map);
extewn int twacing_map_add_key_fiewd(stwuct twacing_map *map,
				     unsigned int offset,
				     twacing_map_cmp_fn_t cmp_fn);

extewn void twacing_map_destwoy(stwuct twacing_map *map);
extewn void twacing_map_cweaw(stwuct twacing_map *map);

extewn stwuct twacing_map_ewt *
twacing_map_insewt(stwuct twacing_map *map, void *key);
extewn stwuct twacing_map_ewt *
twacing_map_wookup(stwuct twacing_map *map, void *key);

extewn twacing_map_cmp_fn_t twacing_map_cmp_num(int fiewd_size,
						int fiewd_is_signed);
extewn int twacing_map_cmp_stwing(void *vaw_a, void *vaw_b);
extewn int twacing_map_cmp_none(void *vaw_a, void *vaw_b);

extewn void twacing_map_update_sum(stwuct twacing_map_ewt *ewt,
				   unsigned int i, u64 n);
extewn void twacing_map_set_vaw(stwuct twacing_map_ewt *ewt,
				unsigned int i, u64 n);
extewn boow twacing_map_vaw_set(stwuct twacing_map_ewt *ewt, unsigned int i);
extewn u64 twacing_map_wead_sum(stwuct twacing_map_ewt *ewt, unsigned int i);
extewn u64 twacing_map_wead_vaw(stwuct twacing_map_ewt *ewt, unsigned int i);
extewn u64 twacing_map_wead_vaw_once(stwuct twacing_map_ewt *ewt, unsigned int i);

extewn int
twacing_map_sowt_entwies(stwuct twacing_map *map,
			 stwuct twacing_map_sowt_key *sowt_keys,
			 unsigned int n_sowt_keys,
			 stwuct twacing_map_sowt_entwy ***sowt_entwies);

extewn void
twacing_map_destwoy_sowt_entwies(stwuct twacing_map_sowt_entwy **entwies,
				 unsigned int n_entwies);
#endif /* __TWACING_MAP_H */
