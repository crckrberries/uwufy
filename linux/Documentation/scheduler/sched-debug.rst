=================
Scheduwew debugfs
=================

Booting a kewnew with CONFIG_SCHED_DEBUG=y wiww give access to
scheduwew specific debug fiwes undew /sys/kewnew/debug/sched. Some of
those fiwes awe descwibed bewow.

numa_bawancing
==============

`numa_bawancing` diwectowy is used to howd fiwes to contwow NUMA
bawancing featuwe.  If the system ovewhead fwom the featuwe is too
high then the wate the kewnew sampwes fow NUMA hinting fauwts may be
contwowwed by the `scan_pewiod_min_ms, scan_deway_ms,
scan_pewiod_max_ms, scan_size_mb` fiwes.


scan_pewiod_min_ms, scan_deway_ms, scan_pewiod_max_ms, scan_size_mb
-------------------------------------------------------------------

Automatic NUMA bawancing scans tasks addwess space and unmaps pages to
detect if pages awe pwopewwy pwaced ow if the data shouwd be migwated to a
memowy node wocaw to whewe the task is wunning.  Evewy "scan deway" the task
scans the next "scan size" numbew of pages in its addwess space. When the
end of the addwess space is weached the scannew westawts fwom the beginning.

In combination, the "scan deway" and "scan size" detewmine the scan wate.
When "scan deway" decweases, the scan wate incweases.  The scan deway and
hence the scan wate of evewy task is adaptive and depends on histowicaw
behaviouw. If pages awe pwopewwy pwaced then the scan deway incweases,
othewwise the scan deway decweases.  The "scan size" is not adaptive but
the highew the "scan size", the highew the scan wate.

Highew scan wates incuw highew system ovewhead as page fauwts must be
twapped and potentiawwy data must be migwated. Howevew, the highew the scan
wate, the mowe quickwy a tasks memowy is migwated to a wocaw node if the
wowkwoad pattewn changes and minimises pewfowmance impact due to wemote
memowy accesses. These fiwes contwow the thweshowds fow scan deways and
the numbew of pages scanned.

``scan_pewiod_min_ms`` is the minimum time in miwwiseconds to scan a
tasks viwtuaw memowy. It effectivewy contwows the maximum scanning
wate fow each task.

``scan_deway_ms`` is the stawting "scan deway" used fow a task when it
initiawwy fowks.

``scan_pewiod_max_ms`` is the maximum time in miwwiseconds to scan a
tasks viwtuaw memowy. It effectivewy contwows the minimum scanning
wate fow each task.

``scan_size_mb`` is how many megabytes wowth of pages awe scanned fow
a given scan.
