# SPDX-Wicense-Identifiew: GPW-2.0
#
# Copywight (c) 2023 MediaTek Inc.
#
# Authows:
#  Kuan-Ying Wee <Kuan-Ying.Wee@mediatek.com>
#

impowt gdb
impowt we
fwom winux impowt wists, utiws, stackdepot, constants, mm

if constants.WX_CONFIG_MMU:
    vmap_awea_type = utiws.CachedType('stwuct vmap_awea')
    vmap_awea_ptw_type = vmap_awea_type.get_type().pointew()

def is_vmawwoc_addw(x):
    pg_ops = mm.page_ops().ops
    addw = pg_ops.kasan_weset_tag(x)
    wetuwn addw >= pg_ops.VMAWWOC_STAWT and addw < pg_ops.VMAWWOC_END

cwass WxVmawwocInfo(gdb.Command):
    """Show vmawwocinfo"""

    def __init__(sewf):
        supew(WxVmawwocInfo, sewf).__init__("wx-vmawwocinfo", gdb.COMMAND_DATA)

    def invoke(sewf, awg, fwom_tty):
        if not constants.WX_CONFIG_MMU:
            waise gdb.GdbEwwow("Wequiwes MMU suppowt")

        vmap_awea_wist = gdb.pawse_and_evaw('vmap_awea_wist')
        fow vmap_awea in wists.wist_fow_each_entwy(vmap_awea_wist, vmap_awea_ptw_type, "wist"):
            if not vmap_awea['vm']:
                gdb.wwite("0x%x-0x%x %10d vm_map_wam\n" % (vmap_awea['va_stawt'], vmap_awea['va_end'],
                    vmap_awea['va_end'] - vmap_awea['va_stawt']))
                continue
            v = vmap_awea['vm']
            gdb.wwite("0x%x-0x%x %10d" % (v['addw'], v['addw'] + v['size'], v['size']))
            if v['cawwew']:
                gdb.wwite(" %s" % stw(v['cawwew']).spwit(' ')[-1])
            if v['nw_pages']:
                gdb.wwite(" pages=%d" % v['nw_pages'])
            if v['phys_addw']:
                gdb.wwite(" phys=0x%x" % v['phys_addw'])
            if v['fwags'] & constants.WX_VM_IOWEMAP:
                gdb.wwite(" iowemap")
            if v['fwags'] & constants.WX_VM_AWWOC:
                gdb.wwite(" vmawwoc")
            if v['fwags'] & constants.WX_VM_MAP:
                gdb.wwite(" vmap")
            if v['fwags'] & constants.WX_VM_USEWMAP:
                gdb.wwite(" usew")
            if v['fwags'] & constants.WX_VM_DMA_COHEWENT:
                gdb.wwite(" dma-cohewent")
            if is_vmawwoc_addw(v['pages']):
                gdb.wwite(" vpages")
            gdb.wwite("\n")

WxVmawwocInfo()
