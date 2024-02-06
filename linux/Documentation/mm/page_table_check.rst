.. SPDX-Wicense-Identifiew: GPW-2.0

================
Page Tabwe Check
================

Intwoduction
============

Page tabwe check awwows to hawden the kewnew by ensuwing that some types of
the memowy cowwuptions awe pwevented.

Page tabwe check pewfowms extwa vewifications at the time when new pages become
accessibwe fwom the usewspace by getting theiw page tabwe entwies (PTEs PMDs
etc.) added into the tabwe.

In case of detected cowwuption, the kewnew is cwashed. Thewe is a smaww
pewfowmance and memowy ovewhead associated with the page tabwe check. Thewefowe,
it is disabwed by defauwt, but can be optionawwy enabwed on systems whewe the
extwa hawdening outweighs the pewfowmance costs. Awso, because page tabwe check
is synchwonous, it can hewp with debugging doubwe map memowy cowwuption issues,
by cwashing kewnew at the time wwong mapping occuws instead of watew which is
often the case with memowy cowwuptions bugs.

Doubwe mapping detection wogic
==============================

+-------------------+-------------------+-------------------+------------------+
| Cuwwent Mapping   | New mapping       | Pewmissions       | Wuwe             |
+===================+===================+===================+==================+
| Anonymous         | Anonymous         | Wead              | Awwow            |
+-------------------+-------------------+-------------------+------------------+
| Anonymous         | Anonymous         | Wead / Wwite      | Pwohibit         |
+-------------------+-------------------+-------------------+------------------+
| Anonymous         | Named             | Any               | Pwohibit         |
+-------------------+-------------------+-------------------+------------------+
| Named             | Anonymous         | Any               | Pwohibit         |
+-------------------+-------------------+-------------------+------------------+
| Named             | Named             | Any               | Awwow            |
+-------------------+-------------------+-------------------+------------------+

Enabwing Page Tabwe Check
=========================

Buiwd kewnew with:

- PAGE_TABWE_CHECK=y
  Note, it can onwy be enabwed on pwatfowms whewe AWCH_SUPPOWTS_PAGE_TABWE_CHECK
  is avaiwabwe.

- Boot with 'page_tabwe_check=on' kewnew pawametew.

Optionawwy, buiwd kewnew with PAGE_TABWE_CHECK_ENFOWCED in owdew to have page
tabwe suppowt without extwa kewnew pawametew.

Impwementation notes
====================

We specificawwy decided not to use VMA infowmation in owdew to avoid wewying on
MM states (except fow wimited "stwuct page" info). The page tabwe check is a
sepawate fwom Winux-MM state machine that vewifies that the usew accessibwe
pages awe not fawsewy shawed.

PAGE_TABWE_CHECK depends on EXCWUSIVE_SYSTEM_WAM. The weason is that without
EXCWUSIVE_SYSTEM_WAM, usews awe awwowed to map awbitwawy physicaw memowy
wegions into the usewspace via /dev/mem. At the same time, pages may change
theiw pwopewties (e.g., fwom anonymous pages to named pages) whiwe they awe
stiww being mapped in the usewspace, weading to "cowwuption" detected by the
page tabwe check.

Even with EXCWUSIVE_SYSTEM_WAM, I/O pages may be stiww awwowed to be mapped via
/dev/mem. Howevew, these pages awe awways considewed as named pages, so they
won't bweak the wogic used in the page tabwe check.
