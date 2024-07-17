// https://iq.opengenus.org/containers-cpp-stl/

#include <stdio.h>
#define i_key int
#define i_val int
#include "stc/smap.h"
#include "stc/algo/defer.h"

int main(void)
{
    c_scope {
        // empty map containers
        smap_int gquiz1 = {0}, gquiz2 = {0};
        c_defer({
            smap_int_drop(&gquiz1);
            smap_int_drop(&gquiz2);
        });
        // insert elements in random order
        smap_int_insert(&gquiz1, 2, 30);
        smap_int_insert(&gquiz1, 4, 20);
        smap_int_insert(&gquiz1, 7, 10);
        smap_int_insert(&gquiz1, 5, 50);
        smap_int_insert(&gquiz1, 3, 60);
        smap_int_insert(&gquiz1, 1, 40);
        smap_int_insert(&gquiz1, 6, 50);

        // printing map gquiz1
        printf("\nThe map gquiz1 is :\n\tKEY\tELEMENT\n");
        c_foreach (itr, smap_int, gquiz1)
            printf("\t%d\t%d\n", itr.ref->first, itr.ref->second);
        printf("\n");

        // assigning the elements from gquiz1 to gquiz2
        c_foreach (i, smap_int, gquiz1)
            smap_int_insert(&gquiz2, i.ref->first, i.ref->second);

        // print all elements of the map gquiz2
        printf("\nThe map gquiz2 is :\n\tKEY\tELEMENT\n");
        c_foreach (itr, smap_int, gquiz2)
            printf("\t%d\t%d\n", itr.ref->first, itr.ref->second);
        printf("\n");

        // remove all elements up to element with key=3 in gquiz2
        printf("\ngquiz2 after removal of elements less than key=3 :\n");
        printf("\tKEY\tELEMENT\n");
        smap_int_erase_range(&gquiz2, smap_int_begin(&gquiz2),
                                       smap_int_find(&gquiz2, 3));
        c_foreach (itr, smap_int, gquiz2)
            printf("\t%d\t%d\n", itr.ref->first, itr.ref->second);
        printf("\n");

        // remove all elements with key = 4
        int num = smap_int_erase(&gquiz2, 4);
        printf("\ngquiz2.erase(4) : %d removed\n", num);
        printf("\tKEY\tELEMENT\n");
        c_foreach (itr, smap_int, gquiz2)
            printf("\t%d\t%d\n", itr.ref->first, itr.ref->second);
        printf("\n");

        // lower bound and upper bound for map gquiz1 key = 5
        printf("gquiz1.lower_bound(5) : ");
        printf("\tKEY = %d\t", smap_int_lower_bound(&gquiz1, 5).ref->first);
        printf("\tELEMENT = %d\n", smap_int_lower_bound(&gquiz1, 5).ref->second);
        printf("gquiz1.upper_bound(5) : ");
        printf("\tKEY = %d\t", smap_int_lower_bound(&gquiz1, 5+1).ref->first);
        printf("\tELEMENT = %d\n", smap_int_lower_bound(&gquiz1, 5+1).ref->second);
    }
}
