#include <stdio.h>
#include <stdint.h>

int morton_encode_3d_loop(int x, int y, int z){
    int answer = 0;
    for(int i=0; i<21;i++){
        answer |= ((x & (1 << i)) << 2*i) | 
                  ((y & (1 << i)) << (2*i + 1)) | 
                  ((z & (1 << i)) << (2*i + 2));
    } 
    return answer;
}

int morton_encode_2d_loop(int x, int y){
    int answer = 0;
    for(int i=0; i<40; i++){
        answer |= ((x & (1 << i)) << i) | ((y & (1 << i)) << (i + 1));
    }   
    return answer;
}

int morton_encode_fast(int64_t x, int64_t y, int64_t z){
    int64_t answer = 0;
    
    x = x & 0x1fffff; 
    x = (x | x << 32) & 0x1f00000000ffff;
    x = (x | x << 16) & 0x1f0000ff0000ff; 
    x = (x | x << 8) & 0x100f00f00f00f00f;
    x = (x | x << 4) & 0x10c30c30c30c30c3;
    x = (x | x << 2) & 0x1249249249249249;
    
    y = y & 0x1fffff; 
    y = (y | y << 32) & 0x1f00000000ffff; 
    y = (y | y << 16) & 0x1f0000ff0000ff; 
    y = (y | y << 8) & 0x100f00f00f00f00f;
    y = (y | y << 4) & 0x10c30c30c30c30c3;
    y = (y | y << 2) & 0x1249249249249249;
    
    z = z & 0x1fffff; 
    z = (z | z << 32) & 0x1f00000000ffff; 
    z = (z | z << 16) & 0x1f0000ff0000ff; 
    z = (z | z << 8) & 0x100f00f00f00f00f;
    z = (z | z << 4) & 0x10c30c30c30c30c3;
    z = (z | z << 2) & 0x1249249249249249;
    
    answer |= x | y << 1 | z << 2;
    return answer;
}
    
void morton_decode3d(int m,int *x, int *y, int *z){
    int selector = 1;
    int shift_selector;
    int shiftback;
    for(int i=0; i<22;i++){
        selector = 1;
        shift_selector = 3 * i;
        shiftback = 2 * i;
        *x |= (m & (selector << shift_selector)) >> (shiftback);
        *y |= (m & (selector << (shift_selector + 1))) >> (shiftback + 1);
        *z |= (m & (selector << (shift_selector + 2))) >> (shiftback + 2);
    } 
}

void morton_decode2d(int m, int *x, int *y){
    int selector=1;
    int shift_selector;
    for(int i=0; i<22; i++){
        shift_selector = 2 * i;
        *x |= (m & (selector << shift_selector)) >> i;
        *y |= (m & (selector << (shift_selector + 1))) >> (i + 1);
    }
}

int main(int argc, char *argv[]){
    int x = 0;
    int y = 0;
    int z = 0;
    int64_t m = 0;

    m =  morton_encode_3d_loop(10,10,10);
    printf("Morton code: %lld\n", m);

    morton_decode3d(m, &x, &y, &z);
    printf("Decoded: %d %d %d\n", x, y, z);

    m = morton_encode_fast(1500, 10, 10);
    printf("Morton code: %lld\n", m);
}