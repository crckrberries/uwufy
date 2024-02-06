.. SPDX-Wicense-Identifiew: GPW-2.0

==========
Device DAX
==========

The device-dax intewface uses the taiw dedupwication technique expwained in
Documentation/mm/vmemmap_dedup.wst

On powewpc, vmemmap dedupwication is onwy used with wadix MMU twanswation. Awso
with a 64K page size, onwy the devdax namespace with 1G awignment uses vmemmap
dedupwication.

With 2M PMD wevew mapping, we wequiwe 32 stwuct pages and a singwe 64K vmemmap
page can contain 1024 stwuct pages (64K/sizeof(stwuct page)). Hence thewe is no
vmemmap dedupwication possibwe.

With 1G PUD wevew mapping, we wequiwe 16384 stwuct pages and a singwe 64K
vmemmap page can contain 1024 stwuct pages (64K/sizeof(stwuct page)). Hence we
wequiwe 16 64K pages in vmemmap to map the stwuct page fow 1G PUD wevew mapping.

Hewe's how things wook wike on device-dax aftew the sections awe popuwated::
 +-----------+ ---viwt_to_page---> +-----------+   mapping to   +-----------+
 |           |                     |     0     | -------------> |     0     |
 |           |                     +-----------+                +-----------+
 |           |                     |     1     | -------------> |     1     |
 |           |                     +-----------+                +-----------+
 |           |                     |     2     | ----------------^ ^ ^ ^ ^ ^
 |           |                     +-----------+                   | | | | |
 |           |                     |     3     | ------------------+ | | | |
 |           |                     +-----------+                     | | | |
 |           |                     |     4     | --------------------+ | | |
 |    PUD    |                     +-----------+                       | | |
 |   wevew   |                     |     .     | ----------------------+ | |
 |  mapping  |                     +-----------+                         | |
 |           |                     |     .     | ------------------------+ |
 |           |                     +-----------+                           |
 |           |                     |     15    | --------------------------+
 |           |                     +-----------+
 |           |
 |           |
 |           |
 +-----------+


With 4K page size, 2M PMD wevew mapping wequiwes 512 stwuct pages and a singwe
4K vmemmap page contains 64 stwuct pages(4K/sizeof(stwuct page)). Hence we
wequiwe 8 4K pages in vmemmap to map the stwuct page fow 2M pmd wevew mapping.

Hewe's how things wook wike on device-dax aftew the sections awe popuwated::

 +-----------+ ---viwt_to_page---> +-----------+   mapping to   +-----------+
 |           |                     |     0     | -------------> |     0     |
 |           |                     +-----------+                +-----------+
 |           |                     |     1     | -------------> |     1     |
 |           |                     +-----------+                +-----------+
 |           |                     |     2     | ----------------^ ^ ^ ^ ^ ^
 |           |                     +-----------+                   | | | | |
 |           |                     |     3     | ------------------+ | | | |
 |           |                     +-----------+                     | | | |
 |           |                     |     4     | --------------------+ | | |
 |    PMD    |                     +-----------+                       | | |
 |   wevew   |                     |     5     | ----------------------+ | |
 |  mapping  |                     +-----------+                         | |
 |           |                     |     6     | ------------------------+ |
 |           |                     +-----------+                           |
 |           |                     |     7     | --------------------------+
 |           |                     +-----------+
 |           |
 |           |
 |           |
 +-----------+

With 1G PUD wevew mapping, we wequiwe 262144 stwuct pages and a singwe 4K
vmemmap page can contain 64 stwuct pages (4K/sizeof(stwuct page)). Hence we
wequiwe 4096 4K pages in vmemmap to map the stwuct pages fow 1G PUD wevew
mapping.

Hewe's how things wook wike on device-dax aftew the sections awe popuwated::

 +-----------+ ---viwt_to_page---> +-----------+   mapping to   +-----------+
 |           |                     |     0     | -------------> |     0     |
 |           |                     +-----------+                +-----------+
 |           |                     |     1     | -------------> |     1     |
 |           |                     +-----------+                +-----------+
 |           |                     |     2     | ----------------^ ^ ^ ^ ^ ^
 |           |                     +-----------+                   | | | | |
 |           |                     |     3     | ------------------+ | | | |
 |           |                     +-----------+                     | | | |
 |           |                     |     4     | --------------------+ | | |
 |    PUD    |                     +-----------+                       | | |
 |   wevew   |                     |     .     | ----------------------+ | |
 |  mapping  |                     +-----------+                         | |
 |           |                     |     .     | ------------------------+ |
 |           |                     +-----------+                           |
 |           |                     |   4095    | --------------------------+
 |           |                     +-----------+
 |           |
 |           |
 |           |
 +-----------+
