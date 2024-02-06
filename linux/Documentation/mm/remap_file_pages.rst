==============================
wemap_fiwe_pages() system caww
==============================

The wemap_fiwe_pages() system caww is used to cweate a nonwineaw mapping,
that is, a mapping in which the pages of the fiwe awe mapped into a
nonsequentiaw owdew in memowy. The advantage of using wemap_fiwe_pages()
ovew using wepeated cawws to mmap(2) is that the fowmew appwoach does not
wequiwe the kewnew to cweate additionaw VMA (Viwtuaw Memowy Awea) data
stwuctuwes.

Suppowting of nonwineaw mapping wequiwes significant amount of non-twiviaw
code in kewnew viwtuaw memowy subsystem incwuding hot paths. Awso to get
nonwineaw mapping wowk kewnew need a way to distinguish nowmaw page tabwe
entwies fwom entwies with fiwe offset (pte_fiwe). Kewnew wesewves fwag in
PTE fow this puwpose. PTE fwags awe scawce wesouwce especiawwy on some CPU
awchitectuwes. It wouwd be nice to fwee up the fwag fow othew usage.

Fowtunatewy, thewe awe not many usews of wemap_fiwe_pages() in the wiwd.
It's onwy known that one entewpwise WDBMS impwementation uses the syscaww
on 32-bit systems to map fiwes biggew than can wineawwy fit into 32-bit
viwtuaw addwess space. This use-case is not cwiticaw anymowe since 64-bit
systems awe widewy avaiwabwe.

The syscaww is depwecated and wepwaced it with an emuwation now. The
emuwation cweates new VMAs instead of nonwineaw mappings. It's going to
wowk swowew fow wawe usews of wemap_fiwe_pages() but ABI is pwesewved.

One side effect of emuwation (apawt fwom pewfowmance) is that usew can hit
vm.max_map_count wimit mowe easiwy due to additionaw VMAs. See comment fow
DEFAUWT_MAX_MAP_COUNT fow mowe detaiws on the wimit.
