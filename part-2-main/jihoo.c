#include <stdio.h>
#include <stdlib.h>
void binary(unsigned int num){

    //이진수 출력
    for (int i = 31; i >= 0; --i) { //32자리 숫자까지 나타냄
        int result = num >> i & 1;
        printf("%d", result);
    }
}


void compareBytes(const char *file1, const char *file2) {
    printf("heello\n");
    FILE *fp1 = fopen(file1, "rb");

    FILE *fp2 = fopen(file2, "rb");

    if (fp1 == NULL || fp2 == NULL) {
        printf("Failed to open files\n");
        exit(1);
    }

    fseek(fp1, 0, SEEK_END);
    long len1 = 512*512*4;
    rewind(fp1);

    fseek(fp2, 0, SEEK_END);
    long len2 = 512*512*4;
    rewind(fp2);

    if (len1 != len2) {
        printf("짱 틀림 : length of bytes objects differ\n");
        fclose(fp1);
        fclose(fp2);
        exit(1);
    }

    char *b1 = (char *)malloc(len1 * sizeof(char));
    char *b2 = (char *)malloc(len2 * sizeof(char));

    if (b1 == NULL || b2 == NULL) {
        printf("Memory allocation failed\n");
        fclose(fp1);
        fclose(fp2);
        exit(1);
    }

    fread(b1, sizeof(char), len1, fp1);
    fread(b2, sizeof(char), len2, fp2);

    int cnt = 0;
    int max_diff = 0;

    int width=512;
    int height=512;
    int channel=4;
    for (int i = 0; i < len1; i++) {
        int aa = (i / (channel*height));
        int bb = (i % (channel*height))/ channel;
        int cc = (i % (channel*height))% channel;
//        printf("Bytes differ at position [%d, %d, %d] %d  %d\n", aa,bb,cc, b1[i], b2[i]);
//        if(cc==1 && bb==283 && aa==112){
//            printf("correct [%d, %d, %d]: %d != %d\n", aa,bb,cc, b1[i], b2[i]);
//            binary(b1[i]);
//            printf("\t");
//            binary(b2[i]);
//            printf("\n");
//        }
//    if(cc==2 && bb==407 && aa==81){
//        printf("[%d, %d, %d]: %d != %d\n", aa,bb,cc, b1[i], b2[i]);
//        binary(b1[i]);
//        printf("\t");
//        binary(b2[i]);
//        printf("\n");
//    }
//    if(cc==2 && bb==109 && aa==266){
//        printf("[%d, %d, %d]: %d != %d\n", aa,bb,cc, b1[i], b2[i]);
//        binary(b1[i]);
//        printf("\t");
//            binary(b2[i]);
//            printf("\n");
//        }
        if (abs(b1[i] - b2[i]) >= 2) {
            printf("Bytes differ at position [%d, %d, %d]: %d != %d\n", aa,bb,cc, b1[i], b2[i]);
            if (max_diff < abs(b1[i] - b2[i])) {
                max_diff = abs(b1[i] - b2[i]);
            }
            cnt++;
        }
    }

    if (cnt == 0) {
        printf("Bytes objects are identical\n");
    }

    printf("cnt: %d (%lf), max diff: %d\n", cnt, (double)cnt / len1, max_diff);
    printf("len1: %ld\n", len1);
    printf("len2: %ld\n", len2);

    free(b1);
    free(b2);
    fclose(fp1);
    fclose(fp2);
}

int main() {
    // Choose file1 and file2 based on the files being compared
//    const char *file1 = "./images/reference/301_512_3x3_float.raw";
//    const char *file2 = "./images/301_512_3x3_float.raw";
//    const char *file1 = "./images/reference/301_512_3x3_int.raw";
//    const char *file2 = "./images/301_512_3x3_int.raw";

//    const char *file1 = "./images/reference/cat_512_7x7_int.raw";
//    const char *file2 = "./images/cat_512_7x7_int.raw";

//    const char *file1 = "./images/reference/cat_512_7x7_float.raw";
//    const char *file2 = "./images/cat_512_7x7_float.raw";
//
//    const char *file1 = "./images/reference/SNU_512_5x5_float.raw";
//    const char *file2 = "./images/SNU_512_5x5_float.raw";
//    const char *file1 = "./images/reference/SNU_512_5x5_int.raw";
//    const char *file2 = "./images/SNU_512_5x5_int.raw";
//    const char *file1 = "./images/reference/301_512_SNU_512_merge_0.5_float.raw";
//    const char *file2 = "./images/301_512_SNU_512_merge_0.5_float.raw";
//    const char *file1 = "./images/reference/301_512_SNU_512_overlay_0.1_float.raw";
//    const char *file2 = "./images/301_512_SNU_512_overlay_0.1_float.raw";
//    const char *file1 = "./images/reference/301_512_SNU_512_overlay_0.5_float.raw";
//    const char *file2 = "./images/301_512_SNU_512_overlay_0.5_float.raw";
//    const char *file1 = "./images/reference/301_512_SNU_512_overlay_0.8_float.raw";
//    const char *file2 = "./images/301_512_SNU_512_overlay_0.8_float.raw";
//    const char *file1 = "./images/reference/301_512_SNU_512_merge_0.5_float.raw";
//    const char *file2 = "./images/301_512_SNU_512_merge_0.5_float.raw";

//    const char *file1 = "./images/reference/301_512_SNU_512_overlay_0.1_float.raw";
//    const char *file2 = "./images/301_512_SNU_512_overlay_0.1_float.raw";
//
//    const char *file1 = "./images/reference/301_512_SNU_512_overlay_0.5_float.raw";
//    const char *file2 = "./images/301_512_SNU_512_overlay_0.5_float.raw";

//
//    const char *file1 = "./images/reference/301_512_SNU_512_overlay_0.8_float.raw";
//    const char *file2 = "./images/301_512_SNU_512_overlay_0.8_float.raw";
////
//    const char *file1 = "/Users/hi/Desktop/snu/5-1/computer_archi/lab2/part-1/images/301_512_SNU_512_overlay_0.1_int.raw";
//    const char *file2 = "./images/301_512_SNU_512_overlay_0.1_int.raw";
//
    const char *file1 = "./images/reference/301_512_SNU_512_overlay_0.1_int.raw";
    const char *file2 = "./images/301_512_SNU_512_overlay_0.1_int.raw";
//
//    const char *file1 = "./images/reference/301_512_SNU_512_overlay_0.5_int.raw";
//    const char *file2 = "./images/301_512_SNU_512_overlay_0.5_int.raw";
//
//
//    const char *file1 = "./images/reference/301_512_SNU_512_overlay_0.8_int.raw";
//    const char *file2 = "./images/301_512_SNU_512_overlay_0.8_int.raw";


    compareBytes(file1, file2);

    return 0;
}
