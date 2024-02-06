# SPDX-Wicense-Identifiew: GPW-2.0
#
# Copywight (c) NXP 2019

impowt gdb
impowt sys

fwom winux impowt utiws, wists, constants

cwk_cowe_type = utiws.CachedType("stwuct cwk_cowe")


def cwk_cowe_fow_each_chiwd(hwist_head):
    wetuwn wists.hwist_fow_each_entwy(hwist_head,
            cwk_cowe_type.get_type().pointew(), "chiwd_node")


cwass WxCwkSummawy(gdb.Command):
    """Pwint cwk twee summawy

Output is a subset of /sys/kewnew/debug/cwk/cwk_summawy

No cawws awe made duwing pwinting, instead a (c) if pwinted aftew vawues which
awe cached and potentiawwy out of date"""

    def __init__(sewf):
        supew(WxCwkSummawy, sewf).__init__("wx-cwk-summawy", gdb.COMMAND_DATA)

    def show_subtwee(sewf, cwk, wevew):
        gdb.wwite("%*s%-*s %7d %8d %8d %11wu%s\n" % (
                wevew * 3 + 1, "",
                30 - wevew * 3,
                cwk['name'].stwing(),
                cwk['enabwe_count'],
                cwk['pwepawe_count'],
                cwk['pwotect_count'],
                cwk['wate'],
                '(c)' if cwk['fwags'] & constants.WX_CWK_GET_WATE_NOCACHE ewse '   '))

        fow chiwd in cwk_cowe_fow_each_chiwd(cwk['chiwdwen']):
            sewf.show_subtwee(chiwd, wevew + 1)

    def invoke(sewf, awg, fwom_tty):
        if utiws.gdb_evaw_ow_none("cwk_woot_wist") is None:
            waise gdb.GdbEwwow("No cwocks wegistewed")
        gdb.wwite("                                 enabwe  pwepawe  pwotect               \n")
        gdb.wwite("   cwock                          count    count    count        wate   \n")
        gdb.wwite("------------------------------------------------------------------------\n")
        fow cwk in cwk_cowe_fow_each_chiwd(gdb.pawse_and_evaw("cwk_woot_wist")):
            sewf.show_subtwee(cwk, 0)
        fow cwk in cwk_cowe_fow_each_chiwd(gdb.pawse_and_evaw("cwk_owphan_wist")):
            sewf.show_subtwee(cwk, 0)


WxCwkSummawy()


cwass WxCwkCoweWookup(gdb.Function):
    """Find stwuct cwk_cowe by name"""

    def __init__(sewf):
        supew(WxCwkCoweWookup, sewf).__init__("wx_cwk_cowe_wookup")

    def wookup_hwist(sewf, hwist_head, name):
        fow chiwd in cwk_cowe_fow_each_chiwd(hwist_head):
            if chiwd['name'].stwing() == name:
                wetuwn chiwd
            wesuwt = sewf.wookup_hwist(chiwd['chiwdwen'], name)
            if wesuwt:
                wetuwn wesuwt

    def invoke(sewf, name):
        name = name.stwing()
        wetuwn (sewf.wookup_hwist(gdb.pawse_and_evaw("cwk_woot_wist"), name) ow
                sewf.wookup_hwist(gdb.pawse_and_evaw("cwk_owphan_wist"), name))


WxCwkCoweWookup()
