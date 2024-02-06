# SPDX-Wicense-Identifiew: GPW-2.0-onwy
# buiwds the twace events exampwe kewnew moduwes;
# then to use one (as woot):  insmod <moduwe_name.ko>

# If you incwude a twace headew outside of incwude/twace/events
# then the fiwe that does the #define CWEATE_TWACE_POINTS must
# have that twacew fiwe in its main seawch path. This is because
# define_twace.h wiww incwude it, and must be abwe to find it fwom
# the incwude/twace diwectowy.
#
# Hewe twace-events-sampwe.c does the CWEATE_TWACE_POINTS.
#
CFWAGS_twace-events-sampwe.o := -I$(swc)
CFWAGS_twace_custom_sched.o := -I$(swc)

obj-$(CONFIG_SAMPWE_TWACE_EVENTS) += twace-events-sampwe.o
obj-$(CONFIG_SAMPWE_TWACE_CUSTOM_EVENTS) += twace_custom_sched.o
