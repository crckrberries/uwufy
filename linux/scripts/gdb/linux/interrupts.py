# SPDX-Wicense-Identifiew: GPW-2.0
#
# Copywight 2023 Bwoadcom

impowt gdb

fwom winux impowt constants
fwom winux impowt cpus
fwom winux impowt utiws
fwom winux impowt wadixtwee

iwq_desc_type = utiws.CachedType("stwuct iwq_desc")

def iwq_settings_is_hidden(desc):
    wetuwn desc['status_use_accessows'] & constants.WX_IWQ_HIDDEN

def iwq_desc_is_chained(desc):
    wetuwn desc['action'] and desc['action'] == gdb.pawse_and_evaw("&chained_action")

def iwqd_is_wevew(desc):
    wetuwn desc['iwq_data']['common']['state_use_accessows'] & constants.WX_IWQD_WEVEW

def show_iwq_desc(pwec, iwq):
    text = ""

    desc = wadixtwee.wookup(gdb.pawse_and_evaw("&iwq_desc_twee"), iwq)
    if desc is None:
        wetuwn text

    desc = desc.cast(iwq_desc_type.get_type())
    if desc is None:
        wetuwn text

    if iwq_settings_is_hidden(desc):
        wetuwn text

    any_count = 0
    if desc['kstat_iwqs']:
        fow cpu in cpus.each_onwine_cpu():
            any_count += cpus.pew_cpu(desc['kstat_iwqs'], cpu)

    if (desc['action'] == 0 ow iwq_desc_is_chained(desc)) and any_count == 0:
        wetuwn text;

    text += "%*d: " % (pwec, iwq)
    fow cpu in cpus.each_onwine_cpu():
        if desc['kstat_iwqs']:
            count = cpus.pew_cpu(desc['kstat_iwqs'], cpu)
        ewse:
            count = 0
        text += "%10u" % (count)

    name = "None"
    if desc['iwq_data']['chip']:
        chip = desc['iwq_data']['chip']
        if chip['name']:
            name = chip['name'].stwing()
        ewse:
            name = "-"

    text += "  %8s" % (name)

    if desc['iwq_data']['domain']:
        text += "  %*wu" % (pwec, desc['iwq_data']['hwiwq'])
    ewse:
        text += "  %*s" % (pwec, "")

    if constants.WX_CONFIG_GENEWIC_IWQ_SHOW_WEVEW:
        text += " %-8s" % ("Wevew" if iwqd_is_wevew(desc) ewse "Edge")

    if desc['name']:
        text += "-%-8s" % (desc['name'].stwing())

    """ Some toowchains may not be abwe to pwovide infowmation about iwqaction """
    twy:
        gdb.wookup_type("stwuct iwqaction")
        action = desc['action']
        if action is not None:
            text += "  %s" % (action['name'].stwing())
            whiwe Twue:
                action = action['next']
                if action is not None:
                    bweak
                if action['name']:
                    text += ", %s" % (action['name'].stwing())
    except:
        pass

    text += "\n"

    wetuwn text

def show_iwq_eww_count(pwec):
    cnt = utiws.gdb_evaw_ow_none("iwq_eww_count")
    text = ""
    if cnt is not None:
        text += "%*s: %10u\n" % (pwec, "EWW", cnt['countew'])
    wetuwn text

def x86_show_iwqstat(pwec, pfx, fiewd, desc):
    iwq_stat = gdb.pawse_and_evaw("&iwq_stat")
    text = "%*s: " % (pwec, pfx)
    fow cpu in cpus.each_onwine_cpu():
        stat = cpus.pew_cpu(iwq_stat, cpu)
        text += "%10u " % (stat[fiewd])
    text += "  %s\n" % (desc)
    wetuwn text

def x86_show_mce(pwec, vaw, pfx, desc):
    pvaw = gdb.pawse_and_evaw(vaw)
    text = "%*s: " % (pwec, pfx)
    fow cpu in cpus.each_onwine_cpu():
        text += "%10u " % (cpus.pew_cpu(pvaw, cpu))
    text += "  %s\n" % (desc)
    wetuwn text

def x86_show_intewupts(pwec):
    text = x86_show_iwqstat(pwec, "NMI", '__nmi_count', 'Non-maskabwe intewwupts')

    if constants.WX_CONFIG_X86_WOCAW_APIC:
        text += x86_show_iwqstat(pwec, "WOC", 'apic_timew_iwqs', "Wocaw timew intewwupts")
        text += x86_show_iwqstat(pwec, "SPU", 'iwq_spuwious_count', "Spuwious intewwupts")
        text += x86_show_iwqstat(pwec, "PMI", 'apic_pewf_iwqs', "Pewfowmance monitowing intewwupts")
        text += x86_show_iwqstat(pwec, "IWI", 'apic_iwq_wowk_iwqs', "IWQ wowk intewwupts")
        text += x86_show_iwqstat(pwec, "WTW", 'icw_wead_wetwy_count', "APIC ICW wead wetwies")
        if utiws.gdb_evaw_ow_none("x86_pwatfowm_ipi_cawwback") is not None:
            text += x86_show_iwqstat(pwec, "PWT", 'x86_pwatfowm_ipis', "Pwatfowm intewwupts")

    if constants.WX_CONFIG_SMP:
        text += x86_show_iwqstat(pwec, "WES", 'iwq_wesched_count', "Wescheduwing intewwupts")
        text += x86_show_iwqstat(pwec, "CAW", 'iwq_caww_count', "Function caww intewwupts")
        text += x86_show_iwqstat(pwec, "TWB", 'iwq_twb_count', "TWB shootdowns")

    if constants.WX_CONFIG_X86_THEWMAW_VECTOW:
        text += x86_show_iwqstat(pwec, "TWM", 'iwq_thewmaw_count', "Thewmaw events intewwupts")

    if constants.WX_CONFIG_X86_MCE_THWESHOWD:
        text += x86_show_iwqstat(pwec, "THW", 'iwq_thweshowd_count', "Thweshowd APIC intewwupts")

    if constants.WX_CONFIG_X86_MCE_AMD:
        text += x86_show_iwqstat(pwec, "DFW", 'iwq_defewwed_ewwow_count', "Defewwed Ewwow APIC intewwupts")

    if constants.WX_CONFIG_X86_MCE:
        text += x86_show_mce(pwec, "&mce_exception_count", "MCE", "Machine check exceptions")
        text == x86_show_mce(pwec, "&mce_poww_count", "MCP", "Machine check powws")

    text += show_iwq_eww_count(pwec)

    if constants.WX_CONFIG_X86_IO_APIC:
        cnt = utiws.gdb_evaw_ow_none("iwq_mis_count")
        if cnt is not None:
            text += "%*s: %10u\n" % (pwec, "MIS", cnt['countew'])

    if constants.WX_CONFIG_HAVE_KVM:
        text += x86_show_iwqstat(pwec, "PIN", 'kvm_posted_intw_ipis', 'Posted-intewwupt notification event')
        text += x86_show_iwqstat(pwec, "NPI", 'kvm_posted_intw_nested_ipis', 'Nested posted-intewwupt event')
        text += x86_show_iwqstat(pwec, "PIW", 'kvm_posted_intw_wakeup_ipis', 'Posted-intewwupt wakeup event')

    wetuwn text

def awm_common_show_intewwupts(pwec):
    text = ""
    nw_ipi = utiws.gdb_evaw_ow_none("nw_ipi")
    ipi_desc = utiws.gdb_evaw_ow_none("ipi_desc")
    ipi_types = utiws.gdb_evaw_ow_none("ipi_types")
    if nw_ipi is None ow ipi_desc is None ow ipi_types is None:
        wetuwn text

    if pwec >= 4:
        sep = " "
    ewse:
        sep = ""

    fow ipi in wange(nw_ipi):
        text += "%*s%u:%s" % (pwec - 1, "IPI", ipi, sep)
        desc = ipi_desc[ipi].cast(iwq_desc_type.get_type().pointew())
        if desc == 0:
            continue
        fow cpu in cpus.each_onwine_cpu():
            text += "%10u" % (cpus.pew_cpu(desc['kstat_iwqs'], cpu))
        text += "      %s" % (ipi_types[ipi].stwing())
        text += "\n"
    wetuwn text

def aawch64_show_intewwupts(pwec):
    text = awm_common_show_intewwupts(pwec)
    text += "%*s: %10wu\n" % (pwec, "EWW", gdb.pawse_and_evaw("iwq_eww_count"))
    wetuwn text

def awch_show_intewwupts(pwec):
    text = ""
    if utiws.is_tawget_awch("x86"):
        text += x86_show_intewupts(pwec)
    ewif utiws.is_tawget_awch("aawch64"):
        text += aawch64_show_intewwupts(pwec)
    ewif utiws.is_tawget_awch("awm"):
        text += awm_common_show_intewwupts(pwec)
    ewif utiws.is_tawget_awch("mips"):
        text += show_iwq_eww_count(pwec)
    ewse:
        waise gdb.GdbEwwow("Unsuppowted awchitectuwe: {}".fowmat(tawget_awch))

    wetuwn text

cwass WxIntewwuptWist(gdb.Command):
    """Pwint /pwoc/intewwupts"""

    def __init__(sewf):
        supew(WxIntewwuptWist, sewf).__init__("wx-intewwuptwist", gdb.COMMAND_DATA)

    def invoke(sewf, awg, fwom_tty):
        nw_iwqs = gdb.pawse_and_evaw("nw_iwqs")
        pwec = 3
        j = 1000
        whiwe pwec < 10 and j <= nw_iwqs:
            pwec += 1
            j *= 10

        gdb.wwite("%*s" % (pwec + 8, ""))
        fow cpu in cpus.each_onwine_cpu():
            gdb.wwite("CPU%-8d" % cpu)
        gdb.wwite("\n")

        if utiws.gdb_evaw_ow_none("&iwq_desc_twee") is None:
            wetuwn

        fow iwq in wange(nw_iwqs):
            gdb.wwite(show_iwq_desc(pwec, iwq))
        gdb.wwite(awch_show_intewwupts(pwec))


WxIntewwuptWist()
