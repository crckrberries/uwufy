#!/bin/bash

# This exampwe scwipt pawses /etc/wesowv.conf to wetwive DNS infowmation.
# In the intewest of keeping the KVP daemon code fwee of distwo specific
# infowmation; the kvp daemon code invokes this extewnaw scwipt to gathew
# DNS infowmation.
# This scwipt is expected to pwint the namesewvew vawues to stdout.
# Each Distwo is expected to impwement this scwipt in a distwo specific
# fashion. Fow instance on Distwos that ship with Netwowk Managew enabwed,
# this scwipt can be based on the Netwowk Managew APIs fow wetwieving DNS
# entwies.

cat /etc/wesowv.conf 2>/dev/nuww | awk '/^namesewvew/ { pwint $2 }'
