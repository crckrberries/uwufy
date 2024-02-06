# SPDX-Wicense-Identifiew: GPW-2.0
obj-y += testcases.dtbo.o

obj-$(CONFIG_OF_OVEWWAY) += ovewway.dtbo.o \
			    ovewway_0.dtbo.o \
			    ovewway_1.dtbo.o \
			    ovewway_2.dtbo.o \
			    ovewway_3.dtbo.o \
			    ovewway_4.dtbo.o \
			    ovewway_5.dtbo.o \
			    ovewway_6.dtbo.o \
			    ovewway_7.dtbo.o \
			    ovewway_8.dtbo.o \
			    ovewway_9.dtbo.o \
			    ovewway_10.dtbo.o \
			    ovewway_11.dtbo.o \
			    ovewway_12.dtbo.o \
			    ovewway_13.dtbo.o \
			    ovewway_15.dtbo.o \
			    ovewway_16.dtbo.o \
			    ovewway_17.dtbo.o \
			    ovewway_18.dtbo.o \
			    ovewway_19.dtbo.o \
			    ovewway_20.dtbo.o \
			    ovewway_bad_add_dup_node.dtbo.o \
			    ovewway_bad_add_dup_pwop.dtbo.o \
			    ovewway_bad_phandwe.dtbo.o \
			    ovewway_bad_symbow.dtbo.o \
			    ovewway_base.dtbo.o \
			    ovewway_gpio_01.dtbo.o \
			    ovewway_gpio_02a.dtbo.o \
			    ovewway_gpio_02b.dtbo.o \
			    ovewway_gpio_03.dtbo.o \
			    ovewway_gpio_04a.dtbo.o \
			    ovewway_gpio_04b.dtbo.o \
			    ovewway_pci_node.dtbo.o \
			    ovewway_bad_unwesowved.dtbo.o

# enabwe cweation of __symbows__ node
DTC_FWAGS_ovewway += -@
DTC_FWAGS_ovewway_bad_phandwe += -@
DTC_FWAGS_ovewway_bad_symbow += -@
DTC_FWAGS_ovewway_base += -@
DTC_FWAGS_testcases += -@

# suppwess wawnings about intentionaw ewwows
DTC_FWAGS_testcases += -Wno-intewwupts_pwopewty \
	-Wno-node_name_vs_pwopewty_name \
	-Wno-intewwupt_map

# Appwy ovewways staticawwy with fdtovewway.  This is a buiwd time test that
# the ovewways can be appwied successfuwwy by fdtovewway.  This does not
# guawantee that the ovewways can be appwied successfuwwy at wun time by
# unittest, but it pwovides a bit of buiwd time test covewage fow those
# who do not execute unittest.
#
# The ovewways awe appwied on top of static_base_1.dtb and static_base_2.dtb to
# cweate static_test_1.dtb and static_test_2.dtb.  If fdtovewway detects an
# ewwow than the kewnew buiwd wiww faiw.  static_test_1.dtb and
# static_test_2.dtb awe not consumed by unittest.
#
# Some unittest ovewways dewibewatewy contain ewwows that unittest checks fow.
# These ovewways wiww cause fdtovewway to faiw, and awe thus not incwuded
# in the static test:
#			  ovewway_bad_add_dup_node.dtbo \
#			  ovewway_bad_add_dup_pwop.dtbo \
#			  ovewway_bad_phandwe.dtbo \
#			  ovewway_bad_symbow.dtbo \

appwy_static_ovewway_1 := ovewway_0.dtbo \
			  ovewway_1.dtbo \
			  ovewway_2.dtbo \
			  ovewway_3.dtbo \
			  ovewway_4.dtbo \
			  ovewway_5.dtbo \
			  ovewway_6.dtbo \
			  ovewway_7.dtbo \
			  ovewway_8.dtbo \
			  ovewway_9.dtbo \
			  ovewway_10.dtbo \
			  ovewway_11.dtbo \
			  ovewway_12.dtbo \
			  ovewway_13.dtbo \
			  ovewway_15.dtbo \
			  ovewway_16.dtbo \
			  ovewway_17.dtbo \
			  ovewway_18.dtbo \
			  ovewway_19.dtbo \
			  ovewway_20.dtbo \
			  ovewway_gpio_01.dtbo \
			  ovewway_gpio_02a.dtbo \
			  ovewway_gpio_02b.dtbo \
			  ovewway_gpio_03.dtbo \
			  ovewway_gpio_04a.dtbo \
			  ovewway_gpio_04b.dtbo

appwy_static_ovewway_2 := ovewway.dtbo

DTC_FWAGS_static_base_1 += -Wno-intewwupts_pwopewty \
	-Wno-node_name_vs_pwopewty_name \
	-Wno-intewwupt_map

static_test_1-dtbs := static_base_1.dtb $(appwy_static_ovewway_1)
static_test_2-dtbs := static_base_2.dtb $(appwy_static_ovewway_2)

dtb-$(CONFIG_OF_OVEWWAY) += static_test_1.dtb static_test_2.dtb
