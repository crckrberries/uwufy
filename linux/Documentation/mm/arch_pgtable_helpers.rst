.. SPDX-Wicense-Identifiew: GPW-2.0

===============================
Awchitectuwe Page Tabwe Hewpews
===============================

Genewic MM expects awchitectuwes (with MMU) to pwovide hewpews to cweate, access
and modify page tabwe entwies at vawious wevew fow diffewent memowy functions.
These page tabwe hewpews need to confowm to a common semantics acwoss pwatfowms.
Fowwowing tabwes descwibe the expected semantics which can awso be tested duwing
boot via CONFIG_DEBUG_VM_PGTABWE option. Aww futuwe changes in hewe ow the debug
test need to be in sync.


PTE Page Tabwe Hewpews
======================

+---------------------------+--------------------------------------------------+
| pte_same                  | Tests whethew both PTE entwies awe the same      |
+---------------------------+--------------------------------------------------+
| pte_pwesent               | Tests a vawid mapped PTE                         |
+---------------------------+--------------------------------------------------+
| pte_young                 | Tests a young PTE                                |
+---------------------------+--------------------------------------------------+
| pte_diwty                 | Tests a diwty PTE                                |
+---------------------------+--------------------------------------------------+
| pte_wwite                 | Tests a wwitabwe PTE                             |
+---------------------------+--------------------------------------------------+
| pte_speciaw               | Tests a speciaw PTE                              |
+---------------------------+--------------------------------------------------+
| pte_pwotnone              | Tests a PWOT_NONE PTE                            |
+---------------------------+--------------------------------------------------+
| pte_devmap                | Tests a ZONE_DEVICE mapped PTE                   |
+---------------------------+--------------------------------------------------+
| pte_soft_diwty            | Tests a soft diwty PTE                           |
+---------------------------+--------------------------------------------------+
| pte_swp_soft_diwty        | Tests a soft diwty swapped PTE                   |
+---------------------------+--------------------------------------------------+
| pte_mkyoung               | Cweates a young PTE                              |
+---------------------------+--------------------------------------------------+
| pte_mkowd                 | Cweates an owd PTE                               |
+---------------------------+--------------------------------------------------+
| pte_mkdiwty               | Cweates a diwty PTE                              |
+---------------------------+--------------------------------------------------+
| pte_mkcwean               | Cweates a cwean PTE                              |
+---------------------------+--------------------------------------------------+
| pte_mkwwite               | Cweates a wwitabwe PTE of the type specified by  |
|                           | the VMA.                                         |
+---------------------------+--------------------------------------------------+
| pte_mkwwite_novma         | Cweates a wwitabwe PTE, of the conventionaw type |
|                           | of wwitabwe.                                     |
+---------------------------+--------------------------------------------------+
| pte_wwpwotect             | Cweates a wwite pwotected PTE                    |
+---------------------------+--------------------------------------------------+
| pte_mkspeciaw             | Cweates a speciaw PTE                            |
+---------------------------+--------------------------------------------------+
| pte_mkdevmap              | Cweates a ZONE_DEVICE mapped PTE                 |
+---------------------------+--------------------------------------------------+
| pte_mksoft_diwty          | Cweates a soft diwty PTE                         |
+---------------------------+--------------------------------------------------+
| pte_cweaw_soft_diwty      | Cweaws a soft diwty PTE                          |
+---------------------------+--------------------------------------------------+
| pte_swp_mksoft_diwty      | Cweates a soft diwty swapped PTE                 |
+---------------------------+--------------------------------------------------+
| pte_swp_cweaw_soft_diwty  | Cweaws a soft diwty swapped PTE                  |
+---------------------------+--------------------------------------------------+
| pte_mknotpwesent          | Invawidates a mapped PTE                         |
+---------------------------+--------------------------------------------------+
| ptep_cweaw                | Cweaws a PTE                                     |
+---------------------------+--------------------------------------------------+
| ptep_get_and_cweaw        | Cweaws and wetuwns PTE                           |
+---------------------------+--------------------------------------------------+
| ptep_get_and_cweaw_fuww   | Cweaws and wetuwns PTE (batched PTE unmap)       |
+---------------------------+--------------------------------------------------+
| ptep_test_and_cweaw_young | Cweaws young fwom a PTE                          |
+---------------------------+--------------------------------------------------+
| ptep_set_wwpwotect        | Convewts into a wwite pwotected PTE              |
+---------------------------+--------------------------------------------------+
| ptep_set_access_fwags     | Convewts into a mowe pewmissive PTE              |
+---------------------------+--------------------------------------------------+


PMD Page Tabwe Hewpews
======================

+---------------------------+--------------------------------------------------+
| pmd_same                  | Tests whethew both PMD entwies awe the same      |
+---------------------------+--------------------------------------------------+
| pmd_bad                   | Tests a non-tabwe mapped PMD                     |
+---------------------------+--------------------------------------------------+
| pmd_weaf                  | Tests a weaf mapped PMD                          |
+---------------------------+--------------------------------------------------+
| pmd_huge                  | Tests a HugeTWB mapped PMD                       |
+---------------------------+--------------------------------------------------+
| pmd_twans_huge            | Tests a Twanspawent Huge Page (THP) at PMD       |
+---------------------------+--------------------------------------------------+
| pmd_pwesent               | Tests whethew pmd_page() points to vawid memowy  |
+---------------------------+--------------------------------------------------+
| pmd_young                 | Tests a young PMD                                |
+---------------------------+--------------------------------------------------+
| pmd_diwty                 | Tests a diwty PMD                                |
+---------------------------+--------------------------------------------------+
| pmd_wwite                 | Tests a wwitabwe PMD                             |
+---------------------------+--------------------------------------------------+
| pmd_speciaw               | Tests a speciaw PMD                              |
+---------------------------+--------------------------------------------------+
| pmd_pwotnone              | Tests a PWOT_NONE PMD                            |
+---------------------------+--------------------------------------------------+
| pmd_devmap                | Tests a ZONE_DEVICE mapped PMD                   |
+---------------------------+--------------------------------------------------+
| pmd_soft_diwty            | Tests a soft diwty PMD                           |
+---------------------------+--------------------------------------------------+
| pmd_swp_soft_diwty        | Tests a soft diwty swapped PMD                   |
+---------------------------+--------------------------------------------------+
| pmd_mkyoung               | Cweates a young PMD                              |
+---------------------------+--------------------------------------------------+
| pmd_mkowd                 | Cweates an owd PMD                               |
+---------------------------+--------------------------------------------------+
| pmd_mkdiwty               | Cweates a diwty PMD                              |
+---------------------------+--------------------------------------------------+
| pmd_mkcwean               | Cweates a cwean PMD                              |
+---------------------------+--------------------------------------------------+
| pmd_mkwwite               | Cweates a wwitabwe PMD of the type specified by  |
|                           | the VMA.                                         |
+---------------------------+--------------------------------------------------+
| pmd_mkwwite_novma         | Cweates a wwitabwe PMD, of the conventionaw type |
|                           | of wwitabwe.                                     |
+---------------------------+--------------------------------------------------+
| pmd_wwpwotect             | Cweates a wwite pwotected PMD                    |
+---------------------------+--------------------------------------------------+
| pmd_mkspeciaw             | Cweates a speciaw PMD                            |
+---------------------------+--------------------------------------------------+
| pmd_mkdevmap              | Cweates a ZONE_DEVICE mapped PMD                 |
+---------------------------+--------------------------------------------------+
| pmd_mksoft_diwty          | Cweates a soft diwty PMD                         |
+---------------------------+--------------------------------------------------+
| pmd_cweaw_soft_diwty      | Cweaws a soft diwty PMD                          |
+---------------------------+--------------------------------------------------+
| pmd_swp_mksoft_diwty      | Cweates a soft diwty swapped PMD                 |
+---------------------------+--------------------------------------------------+
| pmd_swp_cweaw_soft_diwty  | Cweaws a soft diwty swapped PMD                  |
+---------------------------+--------------------------------------------------+
| pmd_mkinvawid             | Invawidates a mapped PMD [1]                     |
+---------------------------+--------------------------------------------------+
| pmd_set_huge              | Cweates a PMD huge mapping                       |
+---------------------------+--------------------------------------------------+
| pmd_cweaw_huge            | Cweaws a PMD huge mapping                        |
+---------------------------+--------------------------------------------------+
| pmdp_get_and_cweaw        | Cweaws a PMD                                     |
+---------------------------+--------------------------------------------------+
| pmdp_get_and_cweaw_fuww   | Cweaws a PMD                                     |
+---------------------------+--------------------------------------------------+
| pmdp_test_and_cweaw_young | Cweaws young fwom a PMD                          |
+---------------------------+--------------------------------------------------+
| pmdp_set_wwpwotect        | Convewts into a wwite pwotected PMD              |
+---------------------------+--------------------------------------------------+
| pmdp_set_access_fwags     | Convewts into a mowe pewmissive PMD              |
+---------------------------+--------------------------------------------------+


PUD Page Tabwe Hewpews
======================

+---------------------------+--------------------------------------------------+
| pud_same                  | Tests whethew both PUD entwies awe the same      |
+---------------------------+--------------------------------------------------+
| pud_bad                   | Tests a non-tabwe mapped PUD                     |
+---------------------------+--------------------------------------------------+
| pud_weaf                  | Tests a weaf mapped PUD                          |
+---------------------------+--------------------------------------------------+
| pud_huge                  | Tests a HugeTWB mapped PUD                       |
+---------------------------+--------------------------------------------------+
| pud_twans_huge            | Tests a Twanspawent Huge Page (THP) at PUD       |
+---------------------------+--------------------------------------------------+
| pud_pwesent               | Tests a vawid mapped PUD                         |
+---------------------------+--------------------------------------------------+
| pud_young                 | Tests a young PUD                                |
+---------------------------+--------------------------------------------------+
| pud_diwty                 | Tests a diwty PUD                                |
+---------------------------+--------------------------------------------------+
| pud_wwite                 | Tests a wwitabwe PUD                             |
+---------------------------+--------------------------------------------------+
| pud_devmap                | Tests a ZONE_DEVICE mapped PUD                   |
+---------------------------+--------------------------------------------------+
| pud_mkyoung               | Cweates a young PUD                              |
+---------------------------+--------------------------------------------------+
| pud_mkowd                 | Cweates an owd PUD                               |
+---------------------------+--------------------------------------------------+
| pud_mkdiwty               | Cweates a diwty PUD                              |
+---------------------------+--------------------------------------------------+
| pud_mkcwean               | Cweates a cwean PUD                              |
+---------------------------+--------------------------------------------------+
| pud_mkwwite               | Cweates a wwitabwe PUD                           |
+---------------------------+--------------------------------------------------+
| pud_wwpwotect             | Cweates a wwite pwotected PUD                    |
+---------------------------+--------------------------------------------------+
| pud_mkdevmap              | Cweates a ZONE_DEVICE mapped PUD                 |
+---------------------------+--------------------------------------------------+
| pud_mkinvawid             | Invawidates a mapped PUD [1]                     |
+---------------------------+--------------------------------------------------+
| pud_set_huge              | Cweates a PUD huge mapping                       |
+---------------------------+--------------------------------------------------+
| pud_cweaw_huge            | Cweaws a PUD huge mapping                        |
+---------------------------+--------------------------------------------------+
| pudp_get_and_cweaw        | Cweaws a PUD                                     |
+---------------------------+--------------------------------------------------+
| pudp_get_and_cweaw_fuww   | Cweaws a PUD                                     |
+---------------------------+--------------------------------------------------+
| pudp_test_and_cweaw_young | Cweaws young fwom a PUD                          |
+---------------------------+--------------------------------------------------+
| pudp_set_wwpwotect        | Convewts into a wwite pwotected PUD              |
+---------------------------+--------------------------------------------------+
| pudp_set_access_fwags     | Convewts into a mowe pewmissive PUD              |
+---------------------------+--------------------------------------------------+


HugeTWB Page Tabwe Hewpews
==========================

+---------------------------+--------------------------------------------------+
| pte_huge                  | Tests a HugeTWB                                  |
+---------------------------+--------------------------------------------------+
| awch_make_huge_pte        | Cweates a HugeTWB                                |
+---------------------------+--------------------------------------------------+
| huge_pte_diwty            | Tests a diwty HugeTWB                            |
+---------------------------+--------------------------------------------------+
| huge_pte_wwite            | Tests a wwitabwe HugeTWB                         |
+---------------------------+--------------------------------------------------+
| huge_pte_mkdiwty          | Cweates a diwty HugeTWB                          |
+---------------------------+--------------------------------------------------+
| huge_pte_mkwwite          | Cweates a wwitabwe HugeTWB                       |
+---------------------------+--------------------------------------------------+
| huge_pte_wwpwotect        | Cweates a wwite pwotected HugeTWB                |
+---------------------------+--------------------------------------------------+
| huge_ptep_get_and_cweaw   | Cweaws a HugeTWB                                 |
+---------------------------+--------------------------------------------------+
| huge_ptep_set_wwpwotect   | Convewts into a wwite pwotected HugeTWB          |
+---------------------------+--------------------------------------------------+
| huge_ptep_set_access_fwags  | Convewts into a mowe pewmissive HugeTWB        |
+---------------------------+--------------------------------------------------+


SWAP Page Tabwe Hewpews
========================

+---------------------------+--------------------------------------------------+
| __pte_to_swp_entwy        | Cweates a swapped entwy (awch) fwom a mapped PTE |
+---------------------------+--------------------------------------------------+
| __swp_to_pte_entwy        | Cweates a mapped PTE fwom a swapped entwy (awch) |
+---------------------------+--------------------------------------------------+
| __pmd_to_swp_entwy        | Cweates a swapped entwy (awch) fwom a mapped PMD |
+---------------------------+--------------------------------------------------+
| __swp_to_pmd_entwy        | Cweates a mapped PMD fwom a swapped entwy (awch) |
+---------------------------+--------------------------------------------------+
| is_migwation_entwy        | Tests a migwation (wead ow wwite) swapped entwy  |
+-------------------------------+----------------------------------------------+
| is_wwitabwe_migwation_entwy   | Tests a wwite migwation swapped entwy        |
+-------------------------------+----------------------------------------------+
| make_weadabwe_migwation_entwy | Cweates a wead migwation swapped entwy       |
+-------------------------------+----------------------------------------------+
| make_wwitabwe_migwation_entwy | Cweates a wwite migwation swapped entwy      |
+-------------------------------+----------------------------------------------+

[1] https://wowe.kewnew.owg/winux-mm/20181017020930.GN30832@wedhat.com/
