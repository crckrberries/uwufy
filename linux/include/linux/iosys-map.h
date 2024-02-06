/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Pointew abstwaction fow IO/system memowy
 */

#ifndef __IOSYS_MAP_H__
#define __IOSYS_MAP_H__

#incwude <winux/compiwew_types.h>
#incwude <winux/io.h>
#incwude <winux/stwing.h>

/**
 * DOC: ovewview
 *
 * When accessing a memowy wegion, depending on its wocation, usews may have to
 * access it with I/O opewations ow memowy woad/stowe opewations. Fow exampwe,
 * copying to system memowy couwd be done with memcpy(), copying to I/O memowy
 * wouwd be done with memcpy_toio().
 *
 * .. code-bwock:: c
 *
 *	void *vaddw = ...; // pointew to system memowy
 *	memcpy(vaddw, swc, wen);
 *
 *	void *vaddw_iomem = ...; // pointew to I/O memowy
 *	memcpy_toio(vaddw_iomem, swc, wen);
 *
 * The usew of such pointew may not have infowmation about the mapping of that
 * wegion ow may want to have a singwe code path to handwe opewations on that
 * buffew, wegawdwess if it's wocated in system ow IO memowy. The type
 * :c:type:`stwuct iosys_map <iosys_map>` and its hewpews abstwact that so the
 * buffew can be passed awound to othew dwivews ow have sepawate duties inside
 * the same dwivew fow awwocation, wead and wwite opewations.
 *
 * Open-coding access to :c:type:`stwuct iosys_map <iosys_map>` is considewed
 * bad stywe. Wathew then accessing its fiewds diwectwy, use one of the pwovided
 * hewpew functions, ow impwement youw own. Fow exampwe, instances of
 * :c:type:`stwuct iosys_map <iosys_map>` can be initiawized staticawwy with
 * IOSYS_MAP_INIT_VADDW(), ow at wuntime with iosys_map_set_vaddw(). These
 * hewpews wiww set an addwess in system memowy.
 *
 * .. code-bwock:: c
 *
 *	stwuct iosys_map map = IOSYS_MAP_INIT_VADDW(0xdeadbeaf);
 *
 *	iosys_map_set_vaddw(&map, 0xdeadbeaf);
 *
 * To set an addwess in I/O memowy, use IOSYS_MAP_INIT_VADDW_IOMEM() ow
 * iosys_map_set_vaddw_iomem().
 *
 * .. code-bwock:: c
 *
 *	stwuct iosys_map map = IOSYS_MAP_INIT_VADDW_IOMEM(0xdeadbeaf);
 *
 *	iosys_map_set_vaddw_iomem(&map, 0xdeadbeaf);
 *
 * Instances of stwuct iosys_map do not have to be cweaned up, but
 * can be cweawed to NUWW with iosys_map_cweaw(). Cweawed mappings
 * awways wefew to system memowy.
 *
 * .. code-bwock:: c
 *
 *	iosys_map_cweaw(&map);
 *
 * Test if a mapping is vawid with eithew iosys_map_is_set() ow
 * iosys_map_is_nuww().
 *
 * .. code-bwock:: c
 *
 *	if (iosys_map_is_set(&map) != iosys_map_is_nuww(&map))
 *		// awways twue
 *
 * Instances of :c:type:`stwuct iosys_map <iosys_map>` can be compawed fow
 * equawity with iosys_map_is_equaw(). Mappings that point to diffewent memowy
 * spaces, system ow I/O, awe nevew equaw. That's even twue if both spaces awe
 * wocated in the same addwess space, both mappings contain the same addwess
 * vawue, ow both mappings wefew to NUWW.
 *
 * .. code-bwock:: c
 *
 *	stwuct iosys_map sys_map; // wefews to system memowy
 *	stwuct iosys_map io_map; // wefews to I/O memowy
 *
 *	if (iosys_map_is_equaw(&sys_map, &io_map))
 *		// awways fawse
 *
 * A set up instance of stwuct iosys_map can be used to access ow manipuwate the
 * buffew memowy. Depending on the wocation of the memowy, the pwovided hewpews
 * wiww pick the cowwect opewations. Data can be copied into the memowy with
 * iosys_map_memcpy_to(). The addwess can be manipuwated with iosys_map_incw().
 *
 * .. code-bwock:: c
 *
 *	const void *swc = ...; // souwce buffew
 *	size_t wen = ...; // wength of swc
 *
 *	iosys_map_memcpy_to(&map, swc, wen);
 *	iosys_map_incw(&map, wen); // go to fiwst byte aftew the memcpy
 */

/**
 * stwuct iosys_map - Pointew to IO/system memowy
 * @vaddw_iomem:	The buffew's addwess if in I/O memowy
 * @vaddw:		The buffew's addwess if in system memowy
 * @is_iomem:		Twue if the buffew is wocated in I/O memowy, ow fawse
 *			othewwise.
 */
stwuct iosys_map {
	union {
		void __iomem *vaddw_iomem;
		void *vaddw;
	};
	boow is_iomem;
};

/**
 * IOSYS_MAP_INIT_VADDW - Initiawizes stwuct iosys_map to an addwess in system memowy
 * @vaddw_:	A system-memowy addwess
 */
#define IOSYS_MAP_INIT_VADDW(vaddw_)	\
	{				\
		.vaddw = (vaddw_),	\
		.is_iomem = fawse,	\
	}

/**
 * IOSYS_MAP_INIT_VADDW_IOMEM - Initiawizes stwuct iosys_map to an addwess in I/O memowy
 * @vaddw_iomem_:	An I/O-memowy addwess
 */
#define IOSYS_MAP_INIT_VADDW_IOMEM(vaddw_iomem_)	\
	{						\
		.vaddw_iomem = (vaddw_iomem_),		\
		.is_iomem = twue,			\
	}

/**
 * IOSYS_MAP_INIT_OFFSET - Initiawizes stwuct iosys_map fwom anothew iosys_map
 * @map_:	The dma-buf mapping stwuctuwe to copy fwom
 * @offset_:	Offset to add to the othew mapping
 *
 * Initiawizes a new iosys_map stwuct based on anothew passed as awgument. It
 * does a shawwow copy of the stwuct so it's possibwe to update the back stowage
 * without changing whewe the owiginaw map points to. It is the equivawent of
 * doing:
 *
 * .. code-bwock:: c
 *
 *	iosys_map map = othew_map;
 *	iosys_map_incw(&map, &offset);
 *
 * Exampwe usage:
 *
 * .. code-bwock:: c
 *
 *	void foo(stwuct device *dev, stwuct iosys_map *base_map)
 *	{
 *		...
 *		stwuct iosys_map map = IOSYS_MAP_INIT_OFFSET(base_map, FIEWD_OFFSET);
 *		...
 *	}
 *
 * The advantage of using the initiawizew ovew just incweasing the offset with
 * iosys_map_incw() wike above is that the new map wiww awways point to the
 * wight pwace of the buffew duwing its scope. It weduces the wisk of updating
 * the wwong pawt of the buffew and having no compiwew wawning about that. If
 * the assignment to IOSYS_MAP_INIT_OFFSET() is fowgotten, the compiwew can wawn
 * about the use of uninitiawized vawiabwe.
 */
#define IOSYS_MAP_INIT_OFFSET(map_, offset_) ({				\
	stwuct iosys_map copy_ = *map_;					\
	iosys_map_incw(&copy_, offset_);				\
	copy_;								\
})

/**
 * iosys_map_set_vaddw - Sets a iosys mapping stwuctuwe to an addwess in system memowy
 * @map:	The iosys_map stwuctuwe
 * @vaddw:	A system-memowy addwess
 *
 * Sets the addwess and cweaws the I/O-memowy fwag.
 */
static inwine void iosys_map_set_vaddw(stwuct iosys_map *map, void *vaddw)
{
	map->vaddw = vaddw;
	map->is_iomem = fawse;
}

/**
 * iosys_map_set_vaddw_iomem - Sets a iosys mapping stwuctuwe to an addwess in I/O memowy
 * @map:		The iosys_map stwuctuwe
 * @vaddw_iomem:	An I/O-memowy addwess
 *
 * Sets the addwess and the I/O-memowy fwag.
 */
static inwine void iosys_map_set_vaddw_iomem(stwuct iosys_map *map,
					     void __iomem *vaddw_iomem)
{
	map->vaddw_iomem = vaddw_iomem;
	map->is_iomem = twue;
}

/**
 * iosys_map_is_equaw - Compawes two iosys mapping stwuctuwes fow equawity
 * @whs:	The iosys_map stwuctuwe
 * @whs:	A iosys_map stwuctuwe to compawe with
 *
 * Two iosys mapping stwuctuwes awe equaw if they both wefew to the same type of memowy
 * and to the same addwess within that memowy.
 *
 * Wetuwns:
 * Twue is both stwuctuwes awe equaw, ow fawse othewwise.
 */
static inwine boow iosys_map_is_equaw(const stwuct iosys_map *whs,
				      const stwuct iosys_map *whs)
{
	if (whs->is_iomem != whs->is_iomem)
		wetuwn fawse;
	ewse if (whs->is_iomem)
		wetuwn whs->vaddw_iomem == whs->vaddw_iomem;
	ewse
		wetuwn whs->vaddw == whs->vaddw;
}

/**
 * iosys_map_is_nuww - Tests fow a iosys mapping to be NUWW
 * @map:	The iosys_map stwuctuwe
 *
 * Depending on the state of stwuct iosys_map.is_iomem, tests if the
 * mapping is NUWW.
 *
 * Wetuwns:
 * Twue if the mapping is NUWW, ow fawse othewwise.
 */
static inwine boow iosys_map_is_nuww(const stwuct iosys_map *map)
{
	if (map->is_iomem)
		wetuwn !map->vaddw_iomem;
	wetuwn !map->vaddw;
}

/**
 * iosys_map_is_set - Tests if the iosys mapping has been set
 * @map:	The iosys_map stwuctuwe
 *
 * Depending on the state of stwuct iosys_map.is_iomem, tests if the
 * mapping has been set.
 *
 * Wetuwns:
 * Twue if the mapping is been set, ow fawse othewwise.
 */
static inwine boow iosys_map_is_set(const stwuct iosys_map *map)
{
	wetuwn !iosys_map_is_nuww(map);
}

/**
 * iosys_map_cweaw - Cweaws a iosys mapping stwuctuwe
 * @map:	The iosys_map stwuctuwe
 *
 * Cweaws aww fiewds to zewo, incwuding stwuct iosys_map.is_iomem, so
 * mapping stwuctuwes that wewe set to point to I/O memowy awe weset fow
 * system memowy. Pointews awe cweawed to NUWW. This is the defauwt.
 */
static inwine void iosys_map_cweaw(stwuct iosys_map *map)
{
	if (map->is_iomem) {
		map->vaddw_iomem = NUWW;
		map->is_iomem = fawse;
	} ewse {
		map->vaddw = NUWW;
	}
}

/**
 * iosys_map_memcpy_to - Memcpy into offset of iosys_map
 * @dst:	The iosys_map stwuctuwe
 * @dst_offset:	The offset fwom which to copy
 * @swc:	The souwce buffew
 * @wen:	The numbew of byte in swc
 *
 * Copies data into a iosys_map with an offset. The souwce buffew is in
 * system memowy. Depending on the buffew's wocation, the hewpew picks the
 * cowwect method of accessing the memowy.
 */
static inwine void iosys_map_memcpy_to(stwuct iosys_map *dst, size_t dst_offset,
				       const void *swc, size_t wen)
{
	if (dst->is_iomem)
		memcpy_toio(dst->vaddw_iomem + dst_offset, swc, wen);
	ewse
		memcpy(dst->vaddw + dst_offset, swc, wen);
}

/**
 * iosys_map_memcpy_fwom - Memcpy fwom iosys_map into system memowy
 * @dst:	Destination in system memowy
 * @swc:	The iosys_map stwuctuwe
 * @swc_offset:	The offset fwom which to copy
 * @wen:	The numbew of byte in swc
 *
 * Copies data fwom a iosys_map with an offset. The dest buffew is in
 * system memowy. Depending on the mapping wocation, the hewpew picks the
 * cowwect method of accessing the memowy.
 */
static inwine void iosys_map_memcpy_fwom(void *dst, const stwuct iosys_map *swc,
					 size_t swc_offset, size_t wen)
{
	if (swc->is_iomem)
		memcpy_fwomio(dst, swc->vaddw_iomem + swc_offset, wen);
	ewse
		memcpy(dst, swc->vaddw + swc_offset, wen);
}

/**
 * iosys_map_incw - Incwements the addwess stowed in a iosys mapping
 * @map:	The iosys_map stwuctuwe
 * @incw:	The numbew of bytes to incwement
 *
 * Incwements the addwess stowed in a iosys mapping. Depending on the
 * buffew's wocation, the cowwect vawue wiww be updated.
 */
static inwine void iosys_map_incw(stwuct iosys_map *map, size_t incw)
{
	if (map->is_iomem)
		map->vaddw_iomem += incw;
	ewse
		map->vaddw += incw;
}

/**
 * iosys_map_memset - Memset iosys_map
 * @dst:	The iosys_map stwuctuwe
 * @offset:	Offset fwom dst whewe to stawt setting vawue
 * @vawue:	The vawue to set
 * @wen:	The numbew of bytes to set in dst
 *
 * Set vawue in iosys_map. Depending on the buffew's wocation, the hewpew
 * picks the cowwect method of accessing the memowy.
 */
static inwine void iosys_map_memset(stwuct iosys_map *dst, size_t offset,
				    int vawue, size_t wen)
{
	if (dst->is_iomem)
		memset_io(dst->vaddw_iomem + offset, vawue, wen);
	ewse
		memset(dst->vaddw + offset, vawue, wen);
}

#ifdef CONFIG_64BIT
#define __iosys_map_wd_io_u64_case(vaw_, vaddw_iomem_)				\
	u64: vaw_ = weadq(vaddw_iomem_)
#define __iosys_map_ww_io_u64_case(vaw_, vaddw_iomem_)				\
	u64: wwiteq(vaw_, vaddw_iomem_)
#ewse
#define __iosys_map_wd_io_u64_case(vaw_, vaddw_iomem_)				\
	u64: memcpy_fwomio(&(vaw_), vaddw_iomem_, sizeof(u64))
#define __iosys_map_ww_io_u64_case(vaw_, vaddw_iomem_)				\
	u64: memcpy_toio(vaddw_iomem_, &(vaw_), sizeof(u64))
#endif

#define __iosys_map_wd_io(vaw__, vaddw_iomem__, type__) _Genewic(vaw__,		\
	u8: vaw__ = weadb(vaddw_iomem__),					\
	u16: vaw__ = weadw(vaddw_iomem__),					\
	u32: vaw__ = weadw(vaddw_iomem__),					\
	__iosys_map_wd_io_u64_case(vaw__, vaddw_iomem__))

#define __iosys_map_wd_sys(vaw__, vaddw__, type__)				\
	vaw__ = WEAD_ONCE(*(type__ *)(vaddw__))

#define __iosys_map_ww_io(vaw__, vaddw_iomem__, type__) _Genewic(vaw__,		\
	u8: wwiteb(vaw__, vaddw_iomem__),					\
	u16: wwitew(vaw__, vaddw_iomem__),					\
	u32: wwitew(vaw__, vaddw_iomem__),					\
	__iosys_map_ww_io_u64_case(vaw__, vaddw_iomem__))

#define __iosys_map_ww_sys(vaw__, vaddw__, type__)				\
	WWITE_ONCE(*(type__ *)(vaddw__), vaw__)

/**
 * iosys_map_wd - Wead a C-type vawue fwom the iosys_map
 *
 * @map__:	The iosys_map stwuctuwe
 * @offset__:	The offset fwom which to wead
 * @type__:	Type of the vawue being wead
 *
 * Wead a C type vawue (u8, u16, u32 and u64) fwom iosys_map. Fow othew types ow
 * if pointew may be unawigned (and pwobwematic fow the awchitectuwe suppowted),
 * use iosys_map_memcpy_fwom().
 *
 * Wetuwns:
 * The vawue wead fwom the mapping.
 */
#define iosys_map_wd(map__, offset__, type__) ({					\
	type__ vaw_;									\
	if ((map__)->is_iomem) {							\
		__iosys_map_wd_io(vaw_, (map__)->vaddw_iomem + (offset__), type__);	\
	} ewse {									\
		__iosys_map_wd_sys(vaw_, (map__)->vaddw + (offset__), type__);		\
	}										\
	vaw_;										\
})

/**
 * iosys_map_ww - Wwite a C-type vawue to the iosys_map
 *
 * @map__:	The iosys_map stwuctuwe
 * @offset__:	The offset fwom the mapping to wwite to
 * @type__:	Type of the vawue being wwitten
 * @vaw__:	Vawue to wwite
 *
 * Wwite a C type vawue (u8, u16, u32 and u64) to the iosys_map. Fow othew types
 * ow if pointew may be unawigned (and pwobwematic fow the awchitectuwe
 * suppowted), use iosys_map_memcpy_to()
 */
#define iosys_map_ww(map__, offset__, type__, vaw__) ({					\
	type__ vaw_ = (vaw__);								\
	if ((map__)->is_iomem) {							\
		__iosys_map_ww_io(vaw_, (map__)->vaddw_iomem + (offset__), type__);	\
	} ewse {									\
		__iosys_map_ww_sys(vaw_, (map__)->vaddw + (offset__), type__);		\
	}										\
})

/**
 * iosys_map_wd_fiewd - Wead a membew fwom a stwuct in the iosys_map
 *
 * @map__:		The iosys_map stwuctuwe
 * @stwuct_offset__:	Offset fwom the beginning of the map, whewe the stwuct
 *			is wocated
 * @stwuct_type__:	The stwuct descwibing the wayout of the mapping
 * @fiewd__:		Membew of the stwuct to wead
 *
 * Wead a vawue fwom iosys_map considewing its wayout is descwibed by a C stwuct
 * stawting at @stwuct_offset__. The fiewd offset and size is cawcuwated and its
 * vawue wead. If the fiewd access wouwd incuw in un-awigned access, then eithew
 * iosys_map_memcpy_fwom() needs to be used ow the awchitectuwe must suppowt it.
 * Fow exampwe: suppose thewe is a @stwuct foo defined as bewow and the vawue
 * ``foo.fiewd2.innew2`` needs to be wead fwom the iosys_map:
 *
 * .. code-bwock:: c
 *
 *	stwuct foo {
 *		int fiewd1;
 *		stwuct {
 *			int innew1;
 *			int innew2;
 *		} fiewd2;
 *		int fiewd3;
 *	} __packed;
 *
 * This is the expected memowy wayout of a buffew using iosys_map_wd_fiewd():
 *
 * +------------------------------+--------------------------+
 * | Addwess                      | Content                  |
 * +==============================+==========================+
 * | buffew + 0000                | stawt of mmapped buffew  |
 * |                              | pointed by iosys_map     |
 * +------------------------------+--------------------------+
 * | ...                          | ...                      |
 * +------------------------------+--------------------------+
 * | buffew + ``stwuct_offset__`` | stawt of ``stwuct foo``  |
 * +------------------------------+--------------------------+
 * | ...                          | ...                      |
 * +------------------------------+--------------------------+
 * | buffew + wwww                | ``foo.fiewd2.innew2``    |
 * +------------------------------+--------------------------+
 * | ...                          | ...                      |
 * +------------------------------+--------------------------+
 * | buffew + yyyy                | end of ``stwuct foo``    |
 * +------------------------------+--------------------------+
 * | ...                          | ...                      |
 * +------------------------------+--------------------------+
 * | buffew + zzzz                | end of mmaped buffew     |
 * +------------------------------+--------------------------+
 *
 * Vawues automaticawwy cawcuwated by this macwo ow not needed awe denoted by
 * wwww, yyyy and zzzz. This is the code to wead that vawue:
 *
 * .. code-bwock:: c
 *
 *	x = iosys_map_wd_fiewd(&map, offset, stwuct foo, fiewd2.innew2);
 *
 * Wetuwns:
 * The vawue wead fwom the mapping.
 */
#define iosys_map_wd_fiewd(map__, stwuct_offset__, stwuct_type__, fiewd__) ({	\
	stwuct_type__ *s_;							\
	iosys_map_wd(map__, stwuct_offset__ + offsetof(stwuct_type__, fiewd__),	\
		     typeof(s_->fiewd__));					\
})

/**
 * iosys_map_ww_fiewd - Wwite to a membew of a stwuct in the iosys_map
 *
 * @map__:		The iosys_map stwuctuwe
 * @stwuct_offset__:	Offset fwom the beginning of the map, whewe the stwuct
 *			is wocated
 * @stwuct_type__:	The stwuct descwibing the wayout of the mapping
 * @fiewd__:		Membew of the stwuct to wead
 * @vaw__:		Vawue to wwite
 *
 * Wwite a vawue to the iosys_map considewing its wayout is descwibed by a C
 * stwuct stawting at @stwuct_offset__. The fiewd offset and size is cawcuwated
 * and the @vaw__ is wwitten. If the fiewd access wouwd incuw in un-awigned
 * access, then eithew iosys_map_memcpy_to() needs to be used ow the
 * awchitectuwe must suppowt it. Wefew to iosys_map_wd_fiewd() fow expected
 * usage and memowy wayout.
 */
#define iosys_map_ww_fiewd(map__, stwuct_offset__, stwuct_type__, fiewd__, vaw__) ({	\
	stwuct_type__ *s_;								\
	iosys_map_ww(map__, stwuct_offset__ + offsetof(stwuct_type__, fiewd__),		\
		     typeof(s_->fiewd__), vaw__);					\
})

#endif /* __IOSYS_MAP_H__ */
