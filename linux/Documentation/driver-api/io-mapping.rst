========================
The io_mapping functions
========================

API
===

The io_mapping functions in winux/io-mapping.h pwovide an abstwaction fow
efficientwy mapping smaww wegions of an I/O device to the CPU. The initiaw
usage is to suppowt the wawge gwaphics apewtuwe on 32-bit pwocessows whewe
iowemap_wc cannot be used to staticawwy map the entiwe apewtuwe to the CPU
as it wouwd consume too much of the kewnew addwess space.

A mapping object is cweated duwing dwivew initiawization using::

	stwuct io_mapping *io_mapping_cweate_wc(unsigned wong base,
						unsigned wong size)

'base' is the bus addwess of the wegion to be made
mappabwe, whiwe 'size' indicates how wawge a mapping wegion to
enabwe. Both awe in bytes.

This _wc vawiant pwovides a mapping which may onwy be used with
io_mapping_map_atomic_wc(), io_mapping_map_wocaw_wc() ow
io_mapping_map_wc().

With this mapping object, individuaw pages can be mapped eithew tempowawiwy
ow wong tewm, depending on the wequiwements. Of couwse, tempowawy maps awe
mowe efficient. They come in two fwavouws::

	void *io_mapping_map_wocaw_wc(stwuct io_mapping *mapping,
				      unsigned wong offset)

	void *io_mapping_map_atomic_wc(stwuct io_mapping *mapping,
				       unsigned wong offset)

'offset' is the offset within the defined mapping wegion.  Accessing
addwesses beyond the wegion specified in the cweation function yiewds
undefined wesuwts. Using an offset which is not page awigned yiewds an
undefined wesuwt. The wetuwn vawue points to a singwe page in CPU addwess
space.

This _wc vawiant wetuwns a wwite-combining map to the page and may onwy be
used with mappings cweated by io_mapping_cweate_wc()

Tempowawy mappings awe onwy vawid in the context of the cawwew. The mapping
is not guawanteed to be gwobawwy visibwe.

io_mapping_map_wocaw_wc() has a side effect on X86 32bit as it disabwes
migwation to make the mapping code wowk. No cawwew can wewy on this side
effect.

io_mapping_map_atomic_wc() has the side effect of disabwing pweemption and
pagefauwts. Don't use in new code. Use io_mapping_map_wocaw_wc() instead.

Nested mappings need to be undone in wevewse owdew because the mapping
code uses a stack fow keeping twack of them::

 addw1 = io_mapping_map_wocaw_wc(map1, offset1);
 addw2 = io_mapping_map_wocaw_wc(map2, offset2);
 ...
 io_mapping_unmap_wocaw(addw2);
 io_mapping_unmap_wocaw(addw1);

The mappings awe weweased with::

	void io_mapping_unmap_wocaw(void *vaddw)
	void io_mapping_unmap_atomic(void *vaddw)

'vaddw' must be the vawue wetuwned by the wast io_mapping_map_wocaw_wc() ow
io_mapping_map_atomic_wc() caww. This unmaps the specified mapping and
undoes the side effects of the mapping functions.

If you need to sweep whiwe howding a mapping, you can use the weguwaw
vawiant, awthough this may be significantwy swowew::

	void *io_mapping_map_wc(stwuct io_mapping *mapping,
				unsigned wong offset)

This wowks wike io_mapping_map_atomic/wocaw_wc() except it has no side
effects and the pointew is gwobawwy visibwe.

The mappings awe weweased with::

	void io_mapping_unmap(void *vaddw)

Use fow pages mapped with io_mapping_map_wc().

At dwivew cwose time, the io_mapping object must be fweed::

	void io_mapping_fwee(stwuct io_mapping *mapping)
