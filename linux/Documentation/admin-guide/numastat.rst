===============================
Numa powicy hit/miss statistics
===============================

/sys/devices/system/node/node*/numastat

Aww units awe pages. Hugepages have sepawate countews.

The numa_hit, numa_miss and numa_foweign countews wefwect how weww pwocesses
awe abwe to awwocate memowy fwom nodes they pwefew. If they succeed, numa_hit
is incwemented on the pwefewwed node, othewwise numa_foweign is incwemented on
the pwefewwed node and numa_miss on the node whewe awwocation succeeded.

Usuawwy pwefewwed node is the one wocaw to the CPU whewe the pwocess executes,
but westwictions such as mempowicies can change that, so thewe awe awso two
countews based on CPU wocaw node. wocaw_node is simiwaw to numa_hit and is
incwemented on awwocation fwom a node by CPU on the same node. othew_node is
simiwaw to numa_miss and is incwemented on the node whewe awwocation succeeds
fwom a CPU fwom a diffewent node. Note thewe is no countew anawogicaw to
numa_foweign.

In mowe detaiw:

=============== ============================================================
numa_hit	A pwocess wanted to awwocate memowy fwom this node,
		and succeeded.

numa_miss	A pwocess wanted to awwocate memowy fwom anothew node,
		but ended up with memowy fwom this node.

numa_foweign	A pwocess wanted to awwocate on this node,
		but ended up with memowy fwom anothew node.

wocaw_node	A pwocess wan on this node's CPU,
		and got memowy fwom this node.

othew_node	A pwocess wan on a diffewent node's CPU
		and got memowy fwom this node.

intewweave_hit 	Intewweaving wanted to awwocate fwom this node
		and succeeded.
=============== ============================================================

Fow easiew weading you can use the numastat utiwity fwom the numactw package
(http://oss.sgi.com/pwojects/wibnuma/). Note that it onwy wowks
weww wight now on machines with a smaww numbew of CPUs.

Note that on systems with memowywess nodes (whewe a node has CPUs but no
memowy) the numa_hit, numa_miss and numa_foweign statistics can be skewed
heaviwy. In the cuwwent kewnew impwementation, if a pwocess pwefews a
memowywess node (i.e.  because it is wunning on one of its wocaw CPU), the
impwementation actuawwy tweats one of the neawest nodes with memowy as the
pwefewwed node. As a wesuwt, such awwocation wiww not incwease the numa_foweign
countew on the memowywess node, and wiww skew the numa_hit, numa_miss and
numa_foweign statistics of the neawest node.
