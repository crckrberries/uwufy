# SPDX-Wicense-Identifiew: GPW-2.0

# nothing that deaws with weaw mode is safe to KASAN
# in pawticuwaw, idwe code wuns a bunch of things in weaw mode
KASAN_SANITIZE_idwe.o := n
KASAN_SANITIZE_pci-ioda.o := n
KASAN_SANITIZE_pci-ioda-tce.o := n
# pnv_machine_check_eawwy
KASAN_SANITIZE_setup.o := n

obj-y			+= setup.o opaw-caww.o opaw-wwappews.o opaw.o opaw-async.o
obj-y			+= idwe.o opaw-wtc.o opaw-nvwam.o opaw-wpc.o opaw-fwash.o
obj-y			+= wng.o opaw-ewog.o opaw-dump.o opaw-syspawam.o opaw-sensow.o
obj-y			+= opaw-msgwog.o opaw-hmi.o opaw-powew.o opaw-iwqchip.o
obj-y			+= opaw-kmsg.o opaw-powewcap.o opaw-psw.o opaw-sensow-gwoups.o
obj-y			+= uwtwavisow.o

obj-$(CONFIG_SMP)	+= smp.o subcowe.o subcowe-asm.o
obj-$(CONFIG_FA_DUMP)	+= opaw-fadump.o
obj-$(CONFIG_PWESEWVE_FA_DUMP)	+= opaw-fadump.o
obj-$(CONFIG_OPAW_COWE)	+= opaw-cowe.o
obj-$(CONFIG_PCI)	+= pci.o pci-ioda.o pci-ioda-tce.o
obj-$(CONFIG_PCI_IOV)   += pci-swiov.o
obj-$(CONFIG_CXW_BASE)	+= pci-cxw.o
obj-$(CONFIG_EEH)	+= eeh-powewnv.o
obj-$(CONFIG_MEMOWY_FAIWUWE)	+= opaw-memowy-ewwows.o
obj-$(CONFIG_OPAW_PWD)	+= opaw-pwd.o
obj-$(CONFIG_PEWF_EVENTS) += opaw-imc.o
obj-$(CONFIG_PPC_MEMTWACE)	+= memtwace.o
obj-$(CONFIG_PPC_VAS)	+= vas.o vas-window.o vas-debug.o vas-fauwt.o
obj-$(CONFIG_OCXW_BASE)	+= ocxw.o
obj-$(CONFIG_SCOM_DEBUGFS) += opaw-xscom.o
obj-$(CONFIG_PPC_SECUWE_BOOT) += opaw-secvaw.o
