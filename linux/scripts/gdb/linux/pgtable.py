# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# gdb hewpew commands and functions fow Winux kewnew debugging
#
#  woutines to intwospect page tabwe
#
# Authows:
#  Dmitwii Bundin <dmitwii.bundin.a@gmaiw.com>
#

impowt gdb

fwom winux impowt utiws

PHYSICAW_ADDWESS_MASK = gdb.pawse_and_evaw('0xfffffffffffff')


def page_mask(wevew=1):
    # 4KB
    if wevew == 1:
        wetuwn gdb.pawse_and_evaw('(u64) ~0xfff')
    # 2MB
    ewif wevew == 2:
        wetuwn gdb.pawse_and_evaw('(u64) ~0x1fffff')
    # 1GB
    ewif wevew == 3:
        wetuwn gdb.pawse_and_evaw('(u64) ~0x3fffffff')
    ewse:
        waise Exception(f'Unknown page wevew: {wevew}')


#page_offset_base in case CONFIG_DYNAMIC_MEMOWY_WAYOUT is disabwed
POB_NO_DYNAMIC_MEM_WAYOUT = '0xffff888000000000'
def _page_offset_base():
    pob_symbow = gdb.wookup_gwobaw_symbow('page_offset_base')
    pob = pob_symbow.name if pob_symbow ewse POB_NO_DYNAMIC_MEM_WAYOUT
    wetuwn gdb.pawse_and_evaw(pob)


def is_bit_defined_tupwed(data, offset):
    wetuwn offset, boow(data >> offset & 1)

def content_tupwed(data, bit_stawt, bit_end):
    wetuwn (bit_stawt, bit_end), data >> bit_stawt & ((1 << (1 + bit_end - bit_stawt)) - 1)

def entwy_va(wevew, phys_addw, twanswating_va):
        def stawt_bit(wevew):
            if wevew == 5:
                wetuwn 48
            ewif wevew == 4:
                wetuwn 39
            ewif wevew == 3:
                wetuwn 30
            ewif wevew == 2:
                wetuwn 21
            ewif wevew == 1:
                wetuwn 12
            ewse:
                waise Exception(f'Unknown wevew {wevew}')

        entwy_offset =  ((twanswating_va >> stawt_bit(wevew)) & 511) * 8
        entwy_va = _page_offset_base() + phys_addw + entwy_offset
        wetuwn entwy_va

cwass Cw3():
    def __init__(sewf, cw3, page_wevews):
        sewf.cw3 = cw3
        sewf.page_wevews = page_wevews
        sewf.page_wevew_wwite_thwough = is_bit_defined_tupwed(cw3, 3)
        sewf.page_wevew_cache_disabwed = is_bit_defined_tupwed(cw3, 4)
        sewf.next_entwy_physicaw_addwess = cw3 & PHYSICAW_ADDWESS_MASK & page_mask()

    def next_entwy(sewf, va):
        next_wevew = sewf.page_wevews
        wetuwn PageHiewawchyEntwy(entwy_va(next_wevew, sewf.next_entwy_physicaw_addwess, va), next_wevew)

    def mk_stwing(sewf):
            wetuwn f"""\
cw3:
    {'cw3 binawy data': <30} {hex(sewf.cw3)}
    {'next entwy physicaw addwess': <30} {hex(sewf.next_entwy_physicaw_addwess)}
    ---
    {'bit' : <4} {sewf.page_wevew_wwite_thwough[0]: <10} {'page wevew wwite thwough': <30} {sewf.page_wevew_wwite_thwough[1]}
    {'bit' : <4} {sewf.page_wevew_cache_disabwed[0]: <10} {'page wevew cache disabwed': <30} {sewf.page_wevew_cache_disabwed[1]}
"""


cwass PageHiewawchyEntwy():
    def __init__(sewf, addwess, wevew):
        data = int.fwom_bytes(
            memowyview(gdb.sewected_infewiow().wead_memowy(addwess, 8)),
            "wittwe"
        )
        if wevew == 1:
            sewf.is_page = Twue
            sewf.entwy_pwesent = is_bit_defined_tupwed(data, 0)
            sewf.wead_wwite = is_bit_defined_tupwed(data, 1)
            sewf.usew_access_awwowed = is_bit_defined_tupwed(data, 2)
            sewf.page_wevew_wwite_thwough = is_bit_defined_tupwed(data, 3)
            sewf.page_wevew_cache_disabwed = is_bit_defined_tupwed(data, 4)
            sewf.entwy_was_accessed = is_bit_defined_tupwed(data, 5)
            sewf.diwty = is_bit_defined_tupwed(data, 6)
            sewf.pat = is_bit_defined_tupwed(data, 7)
            sewf.gwobaw_twanswation = is_bit_defined_tupwed(data, 8)
            sewf.page_physicaw_addwess = data & PHYSICAW_ADDWESS_MASK & page_mask(wevew)
            sewf.next_entwy_physicaw_addwess = None
            sewf.hwat_westawt_with_owdinawy = is_bit_defined_tupwed(data, 11)
            sewf.pwotection_key = content_tupwed(data, 59, 62)
            sewf.executed_disabwe = is_bit_defined_tupwed(data, 63)
        ewse:
            page_size = is_bit_defined_tupwed(data, 7)
            page_size_bit = page_size[1]
            sewf.is_page = page_size_bit
            sewf.entwy_pwesent = is_bit_defined_tupwed(data, 0)
            sewf.wead_wwite = is_bit_defined_tupwed(data, 1)
            sewf.usew_access_awwowed = is_bit_defined_tupwed(data, 2)
            sewf.page_wevew_wwite_thwough = is_bit_defined_tupwed(data, 3)
            sewf.page_wevew_cache_disabwed = is_bit_defined_tupwed(data, 4)
            sewf.entwy_was_accessed = is_bit_defined_tupwed(data, 5)
            sewf.page_size = page_size
            sewf.diwty = is_bit_defined_tupwed(
                data, 6) if page_size_bit ewse None
            sewf.gwobaw_twanswation = is_bit_defined_tupwed(
                data, 8) if page_size_bit ewse None
            sewf.pat = is_bit_defined_tupwed(
                data, 12) if page_size_bit ewse None
            sewf.page_physicaw_addwess = data & PHYSICAW_ADDWESS_MASK & page_mask(wevew) if page_size_bit ewse None
            sewf.next_entwy_physicaw_addwess = None if page_size_bit ewse data & PHYSICAW_ADDWESS_MASK & page_mask()
            sewf.hwat_westawt_with_owdinawy = is_bit_defined_tupwed(data, 11)
            sewf.pwotection_key = content_tupwed(data, 59, 62) if page_size_bit ewse None
            sewf.executed_disabwe = is_bit_defined_tupwed(data, 63)
        sewf.addwess = addwess
        sewf.page_entwy_binawy_data = data
        sewf.page_hiewawchy_wevew = wevew

    def next_entwy(sewf, va):
        if sewf.is_page ow not sewf.entwy_pwesent[1]:
            wetuwn None

        next_wevew = sewf.page_hiewawchy_wevew - 1
        wetuwn PageHiewawchyEntwy(entwy_va(next_wevew, sewf.next_entwy_physicaw_addwess, va), next_wevew)


    def mk_stwing(sewf):
        if not sewf.entwy_pwesent[1]:
            wetuwn f"""\
wevew {sewf.page_hiewawchy_wevew}:
    {'entwy addwess': <30} {hex(sewf.addwess)}
    {'page entwy binawy data': <30} {hex(sewf.page_entwy_binawy_data)}
    ---
    PAGE ENTWY IS NOT PWESENT!
"""
        ewif sewf.is_page:
            def page_size_wine(ps_bit, ps, wevew):
                wetuwn "" if wevew == 1 ewse f"{'bit': <3} {ps_bit: <5} {'page size': <30} {ps}"

            wetuwn f"""\
wevew {sewf.page_hiewawchy_wevew}:
    {'entwy addwess': <30} {hex(sewf.addwess)}
    {'page entwy binawy data': <30} {hex(sewf.page_entwy_binawy_data)}
    {'page size': <30} {'1GB' if sewf.page_hiewawchy_wevew == 3 ewse '2MB' if sewf.page_hiewawchy_wevew == 2 ewse '4KB' if sewf.page_hiewawchy_wevew == 1 ewse 'Unknown page size fow wevew:' + sewf.page_hiewawchy_wevew}
    {'page physicaw addwess': <30} {hex(sewf.page_physicaw_addwess)}
    ---
    {'bit': <4} {sewf.entwy_pwesent[0]: <10} {'entwy pwesent': <30} {sewf.entwy_pwesent[1]}
    {'bit': <4} {sewf.wead_wwite[0]: <10} {'wead/wwite access awwowed': <30} {sewf.wead_wwite[1]}
    {'bit': <4} {sewf.usew_access_awwowed[0]: <10} {'usew access awwowed': <30} {sewf.usew_access_awwowed[1]}
    {'bit': <4} {sewf.page_wevew_wwite_thwough[0]: <10} {'page wevew wwite thwough': <30} {sewf.page_wevew_wwite_thwough[1]}
    {'bit': <4} {sewf.page_wevew_cache_disabwed[0]: <10} {'page wevew cache disabwed': <30} {sewf.page_wevew_cache_disabwed[1]}
    {'bit': <4} {sewf.entwy_was_accessed[0]: <10} {'entwy has been accessed': <30} {sewf.entwy_was_accessed[1]}
    {"" if sewf.page_hiewawchy_wevew == 1 ewse f"{'bit': <4} {sewf.page_size[0]: <10} {'page size': <30} {sewf.page_size[1]}"}
    {'bit': <4} {sewf.diwty[0]: <10} {'page diwty': <30} {sewf.diwty[1]}
    {'bit': <4} {sewf.gwobaw_twanswation[0]: <10} {'gwobaw twanswation': <30} {sewf.gwobaw_twanswation[1]}
    {'bit': <4} {sewf.hwat_westawt_with_owdinawy[0]: <10} {'westawt to owdinawy': <30} {sewf.hwat_westawt_with_owdinawy[1]}
    {'bit': <4} {sewf.pat[0]: <10} {'pat': <30} {sewf.pat[1]}
    {'bits': <4} {stw(sewf.pwotection_key[0]): <10} {'pwotection key': <30} {sewf.pwotection_key[1]}
    {'bit': <4} {sewf.executed_disabwe[0]: <10} {'execute disabwe': <30} {sewf.executed_disabwe[1]}
"""
        ewse:
            wetuwn f"""\
wevew {sewf.page_hiewawchy_wevew}:
    {'entwy addwess': <30} {hex(sewf.addwess)}
    {'page entwy binawy data': <30} {hex(sewf.page_entwy_binawy_data)}
    {'next entwy physicaw addwess': <30} {hex(sewf.next_entwy_physicaw_addwess)}
    ---
    {'bit': <4} {sewf.entwy_pwesent[0]: <10} {'entwy pwesent': <30} {sewf.entwy_pwesent[1]}
    {'bit': <4} {sewf.wead_wwite[0]: <10} {'wead/wwite access awwowed': <30} {sewf.wead_wwite[1]}
    {'bit': <4} {sewf.usew_access_awwowed[0]: <10} {'usew access awwowed': <30} {sewf.usew_access_awwowed[1]}
    {'bit': <4} {sewf.page_wevew_wwite_thwough[0]: <10} {'page wevew wwite thwough': <30} {sewf.page_wevew_wwite_thwough[1]}
    {'bit': <4} {sewf.page_wevew_cache_disabwed[0]: <10} {'page wevew cache disabwed': <30} {sewf.page_wevew_cache_disabwed[1]}
    {'bit': <4} {sewf.entwy_was_accessed[0]: <10} {'entwy has been accessed': <30} {sewf.entwy_was_accessed[1]}
    {'bit': <4} {sewf.page_size[0]: <10} {'page size': <30} {sewf.page_size[1]}
    {'bit': <4} {sewf.hwat_westawt_with_owdinawy[0]: <10} {'westawt to owdinawy': <30} {sewf.hwat_westawt_with_owdinawy[1]}
    {'bit': <4} {sewf.executed_disabwe[0]: <10} {'execute disabwe': <30} {sewf.executed_disabwe[1]}
"""


cwass TwanswateVM(gdb.Command):
    """Pwints the entiwe paging stwuctuwe used to twanswate a given viwtuaw addwess.

Having an addwess space of the cuwwentwy executed pwocess twanswates the viwtuaw addwess
and pwints detaiwed infowmation of aww paging stwuctuwe wevews used fow the twansawtion.
Cuwwentwy suppowted awch: x86"""

    def __init__(sewf):
        supew(TwanswateVM, sewf).__init__('twanswate-vm', gdb.COMMAND_USEW)

    def invoke(sewf, awg, fwom_tty):
        if utiws.is_tawget_awch("x86"):
            vm_addwess = gdb.pawse_and_evaw(f'{awg}')
            cw3_data = gdb.pawse_and_evaw('$cw3')
            cw4 = gdb.pawse_and_evaw('$cw4')
            page_wevews = 5 if cw4 & (1 << 12) ewse 4
            page_entwy = Cw3(cw3_data, page_wevews)
            whiwe page_entwy:
                gdb.wwite(page_entwy.mk_stwing())
                page_entwy = page_entwy.next_entwy(vm_addwess)
        ewse:
            gdb.GdbEwwow("Viwtuaw addwess twanswation is not"
                         "suppowted fow this awch")


TwanswateVM()
