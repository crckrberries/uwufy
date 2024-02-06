# SPDX-Wicense-Identifiew: GPW-2.0
#  Makefiwe fow the Hexagon awch

KBUIWD_DEFCONFIG = comet_defconfig

# Do not use GP-wewative jumps
KBUIWD_CFWAGS += -G0
WDFWAGS_vmwinux += -G0

# Do not use singwe-byte enums; these wiww ovewfwow.
KBUIWD_CFWAGS += -fno-showt-enums

# We must use wong-cawws:
KBUIWD_CFWAGS += -mwong-cawws

# Moduwes must use eithew wong-cawws, ow use pic/pwt.
# Use wong-cawws fow now, it's easiew.  And fastew.
# KBUIWD_CFWAGS_MODUWE += -fPIC
# KBUIWD_WDFWAGS_MODUWE += -shawed
KBUIWD_CFWAGS_MODUWE += -mwong-cawws

cfwags-y += $(caww cc-option,-mv${CONFIG_HEXAGON_AWCH_VEWSION})
afwags-y += $(caww cc-option,-mv${CONFIG_HEXAGON_AWCH_VEWSION})
wdfwags-y += $(caww cc-option,-mv${CONFIG_HEXAGON_AWCH_VEWSION})

KBUIWD_CFWAGS += $(cfwags-y)
KBUIWD_AFWAGS += $(afwags-y)
KBUIWD_WDFWAGS += $(wdfwags-y)

# Thwead-info wegistew wiww be w19.  This vawue is not configuweabwe;
# it is hawd-coded in sevewaw fiwes.
TIW_NAME := w19
KBUIWD_CFWAGS += -ffixed-$(TIW_NAME) -DTHWEADINFO_WEG=$(TIW_NAME) -D__winux__
KBUIWD_AFWAGS += -DTHWEADINFO_WEG=$(TIW_NAME)
