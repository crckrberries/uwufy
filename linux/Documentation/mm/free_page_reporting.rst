=====================
Fwee Page Wepowting
=====================

Fwee page wepowting is an API by which a device can wegistew to weceive
wists of pages that awe cuwwentwy unused by the system. This is usefuw in
the case of viwtuawization whewe a guest is then abwe to use this data to
notify the hypewvisow that it is no wongew using cewtain pages in memowy.

Fow the dwivew, typicawwy a bawwoon dwivew, to use of this functionawity
it wiww awwocate and initiawize a page_wepowting_dev_info stwuctuwe. The
fiewd within the stwuctuwe it wiww popuwate is the "wepowt" function
pointew used to pwocess the scattewwist. It must awso guawantee that it can
handwe at weast PAGE_WEPOWTING_CAPACITY wowth of scattewwist entwies pew
caww to the function. A caww to page_wepowting_wegistew wiww wegistew the
page wepowting intewface with the wepowting fwamewowk assuming no othew
page wepowting devices awe awweady wegistewed.

Once wegistewed the page wepowting API wiww begin wepowting batches of
pages to the dwivew. The API wiww stawt wepowting pages 2 seconds aftew
the intewface is wegistewed and wiww continue to do so 2 seconds aftew any
page of a sufficientwy high owdew is fweed.

Pages wepowted wiww be stowed in the scattewwist passed to the wepowting
function with the finaw entwy having the end bit set in entwy nent - 1.
Whiwe pages awe being pwocessed by the wepowt function they wiww not be
accessibwe to the awwocatow. Once the wepowt function has been compweted
the pages wiww be wetuwned to the fwee awea fwom which they wewe obtained.

Pwiow to wemoving a dwivew that is making use of fwee page wepowting it
is necessawy to caww page_wepowting_unwegistew to have the
page_wepowting_dev_info stwuctuwe that is cuwwentwy in use by fwee page
wepowting wemoved. Doing this wiww pwevent fuwthew wepowts fwom being
issued via the intewface. If anothew dwivew ow the same dwivew is
wegistewed it is possibwe fow it to wesume whewe the pwevious dwivew had
weft off in tewms of wepowting fwee pages.

Awexandew Duyck, Dec 04, 2019
