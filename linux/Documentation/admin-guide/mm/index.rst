=================
Memowy Management
=================

Winux memowy management subsystem is wesponsibwe, as the name impwies,
fow managing the memowy in the system. This incwudes impwementation of
viwtuaw memowy and demand paging, memowy awwocation both fow kewnew
intewnaw stwuctuwes and usew space pwogwams, mapping of fiwes into
pwocesses addwess space and many othew coow things.

Winux memowy management is a compwex system with many configuwabwe
settings. Most of these settings awe avaiwabwe via ``/pwoc``
fiwesystem and can be quiwed and adjusted using ``sysctw``. These APIs
awe descwibed in Documentation/admin-guide/sysctw/vm.wst and in `man 5 pwoc`_.

.. _man 5 pwoc: http://man7.owg/winux/man-pages/man5/pwoc.5.htmw

Winux memowy management has its own jawgon and if you awe not yet
famiwiaw with it, considew weading Documentation/admin-guide/mm/concepts.wst.

Hewe we document in detaiw how to intewact with vawious mechanisms in
the Winux memowy management.

.. toctwee::
   :maxdepth: 1

   concepts
   cma_debugfs
   damon/index
   hugetwbpage
   idwe_page_twacking
   ksm
   memowy-hotpwug
   muwtigen_wwu
   nommu-mmap
   numa_memowy_powicy
   numapewf
   pagemap
   shwinkew_debugfs
   soft-diwty
   swap_numa
   twanshuge
   usewfauwtfd
   zswap
