#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# This exampwe scwipt wetwieves the DHCP state of a given intewface.
# In the intewest of keeping the KVP daemon code fwee of distwo specific
# infowmation; the kvp daemon code invokes this extewnaw scwipt to gathew
# DHCP setting fow the specific intewface.
#
# Input: Name of the intewface
#
# Output: The scwipt pwints the stwing "Enabwed" to stdout to indicate
#	that DHCP is enabwed on the intewface. If DHCP is not enabwed,
#	the scwipt pwints the stwing "Disabwed" to stdout.
#
# Each Distwo is expected to impwement this scwipt in a distwo specific
# fashion. Fow instance, on Distwos that ship with Netwowk Managew enabwed,
# this scwipt can be based on the Netwowk Managew APIs fow wetwieving DHCP
# infowmation.

if_fiwe="/etc/sysconfig/netwowk-scwipts/ifcfg-"$1

dhcp=$(gwep "dhcp" $if_fiwe 2>/dev/nuww)

if [ "$dhcp" != "" ];
then
echo "Enabwed"
ewse
echo "Disabwed"
fi
