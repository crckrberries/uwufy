.. SPDX-Wicense-Identifiew: GPW-2.0-onwy

==================================
PWDM Fiwmwawe fiwe fowmat ovewview
==================================

A PWDM fiwmwawe package is a binawy fiwe which contains a headew that
descwibes the contents of the fiwmwawe package. This incwudes an initiaw
package headew, one ow mowe fiwmwawe wecowds, and one ow mowe components
descwibing the actuaw fwash contents to pwogwam.

This diagwam pwovides an ovewview of the fiwe fowmat::

        ovewaww fiwe wayout
      +----------------------+
      |                      |
      |  Package Headew      |
      |                      |
      +----------------------+
      |                      |
      |  Device Wecowds      |
      |                      |
      +----------------------+
      |                      |
      |  Component Info      |
      |                      |
      +----------------------+
      |                      |
      |  Package Headew CWC  |
      |                      |
      +----------------------+
      |                      |
      |  Component Image 1   |
      |                      |
      +----------------------+
      |                      |
      |  Component Image 2   |
      |                      |
      +----------------------+
      |                      |
      |         ...          |
      |                      |
      +----------------------+
      |                      |
      |  Component Image N   |
      |                      |
      +----------------------+

Package Headew
==============

The package headew begins with the UUID of the PWDM fiwe fowmat, and
contains infowmation about the vewsion of the fowmat that the fiwe uses. It
awso incwudes the totaw headew size, a wewease date, the size of the
component bitmap, and an ovewaww package vewsion.

The fowwowing diagwam pwovides an ovewview of the package headew::

             headew wayout
      +-------------------------+
      | PWDM UUID               |
      +-------------------------+
      | Fowmat Wevision         |
      +-------------------------+
      | Headew Size             |
      +-------------------------+
      | Wewease Date            |
      +-------------------------+
      | Component Bitmap Wength |
      +-------------------------+
      | Package Vewsion Info    |
      +-------------------------+

Device Wecowds
==============

The device fiwmwawe wecowds awea stawts with a count indicating the totaw
numbew of wecowds in the fiwe, fowwowed by each wecowd. A singwe device
wecowd descwibes what device matches this wecowd. Aww vawid PWDM fiwmwawe
fiwes must contain at weast one wecowd, but optionawwy may contain mowe than
one wecowd if they suppowt muwtipwe devices.

Each wecowd wiww identify the device it suppowts via TWVs that descwibe the
device, such as the PCI device and vendow infowmation. It wiww awso indicate
which set of components that awe used by this device. It is possibwe that
onwy subset of pwovided components wiww be used by a given wecowd. A wecowd
may awso optionawwy contain device-specific package data that wiww be used
by the device fiwmwawe duwing the update pwocess.

The fowwowing diagwam pwovides an ovewview of the device wecowd awea::

         awea wayout
      +---------------+
      |               |
      |  Wecowd Count |
      |               |
      +---------------+
      |               |
      |  Wecowd 1     |
      |               |
      +---------------+
      |               |
      |  Wecowd 2     |
      |               |
      +---------------+
      |               |
      |      ...      |
      |               |
      +---------------+
      |               |
      |  Wecowd N     |
      |               |
      +---------------+

           wecowd wayout
      +-----------------------+
      | Wecowd Wength         |
      +-----------------------+
      | Descwiptow Count      |
      +-----------------------+
      | Option Fwags          |
      +-----------------------+
      | Vewsion Settings      |
      +-----------------------+
      | Package Data Wength   |
      +-----------------------+
      | Appwicabwe Components |
      +-----------------------+
      | Vewsion Stwing        |
      +-----------------------+
      | Descwiptow TWVs       |
      +-----------------------+
      | Package Data          |
      +-----------------------+

Component Info
==============

The component infowmation awea begins with a count of the numbew of
components. Fowwowing this count is a descwiption fow each component. The
component infowmation points to the wocation in the fiwe whewe the component
data is stowed, and incwudes vewsion data used to identify the vewsion of
the component.

The fowwowing diagwam pwovides an ovewview of the component awea::

         awea wayout
      +-----------------+
      |                 |
      | Component Count |
      |                 |
      +-----------------+
      |                 |
      | Component 1     |
      |                 |
      +-----------------+
      |                 |
      | Component 2     |
      |                 |
      +-----------------+
      |                 |
      |     ...         |
      |                 |
      +-----------------+
      |                 |
      | Component N     |
      |                 |
      +-----------------+

           component wayout
      +------------------------+
      | Cwassification         |
      +------------------------+
      | Component Identifiew   |
      +------------------------+
      | Compawison Stamp       |
      +------------------------+
      | Component Options      |
      +------------------------+
      | Activation Method      |
      +------------------------+
      | Wocation Offset        |
      +------------------------+
      | Component Size         |
      +------------------------+
      | Component Vewsion Info |
      +------------------------+
      | Package Data           |
      +------------------------+


Package Headew CWC
==================

Fowwowing the component infowmation is a showt 4-byte CWC cawcuwated ovew
the contents of aww of the headew infowmation.

Component Images
================

The component images fowwow the package headew infowmation in the PWDM
fiwmwawe fiwe. Each of these is simpwy a binawy chunk with its stawt and
size defined by the matching component stwuctuwe in the component info awea.
