#include <stc/cstr.h>

#define i_val int
#include <stc/carr2.h>

#define i_val int
#include <stc/carr3.h>

#define i_val_str
#include <stc/carr2.h>

int main()
{
    int w = 7, h = 5, d = 3;

    c_autodrop (carr2_int, volume, carr2_int_new_uninit(w, h))
    {
        int *dat = carr2_int_data(&volume);
        for (size_t i = 0; i < carr2_int_size(&volume); ++i)
            dat[i] = i;

        for (size_t x = 0; x < volume.xdim; ++x)
            for (size_t y = 0; y < volume.ydim; ++y)
                printf(" %d", volume.data[x][y]);
        puts("");

        c_foreach (i, carr2_int, volume)
            printf(" %d", *i.ref);
        puts("\n");
    }

    c_autodrop (carr3_int, volume, carr3_int_new_uninit(w, h, d))
    {
        int *dat = carr3_int_data(&volume);
        for (size_t i = 0; i < carr3_int_size(&volume); ++i)
            dat[i] = i;

        for (size_t x = 0; x < volume.xdim; ++x)
            for (size_t y = 0; y < volume.ydim; ++y)
                for (size_t z = 0; z < volume.zdim; ++z)
                    printf(" %d", volume.data[x][y][z]);
        puts("");

        c_foreach (i, carr3_int, volume)
            printf(" %d", *i.ref);
        puts("");
    }

    c_autodrop (carr2_str, text2d, carr2_str_with_size(h, d, cstr_init()))
    {
        cstr_assign(&text2d.data[2][1], "hello");
        cstr_assign(&text2d.data[4][0], "world");

        c_foreach (i, carr2_str, text2d)
            printf("line: %s\n", cstr_str(i.ref));
    }
}
