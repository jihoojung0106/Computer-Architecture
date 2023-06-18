#/-------------------------------------------------------------------------------------------------
#/ 4190.308 Computer Architecture                                                       Spring 2023
#/
#// @file
#// @brief Image blending (vector operations)
#//        This module implements a function that blends two images together filter (assembly
#//        integer vector version)
#//
#//
#// @section changelog Change Log
#// 2023/MM/DD Your Name Comment
#//
#/-------------------------------------------------------------------------------------------------

    .option nopic
    .attribute unaligned_access, 0
    .attribute stack_align, 16

    .text
    .align 4
    .globl blend_asm
    .type  blend_asm, @function

# struct Image {                 Ofs
#     uint8 *data;                 0
#     int height;                  4
#     int width;                   8
#     int channels;               12
# };

# int blend_asm(                 Reg
#       struct Image *blended,    a0
#       struct Image *img1,       a1
#       struct Image *img2,       a2
#       int overlay,              a3
#       int alpha                 a4
#     )
blend_asm:

    # Check parameters

    li    t0, 1
    bne   a3, t0, .OverlayError   # if overlay != 1 goto .OverlayError

    lw    t1, 12(a1)              # t1 = img1->channels
    lw    t2, 12(a2)              # t2 = img2->channels
    li    t0, 4
    bne   t1, t0, .ChannelError   # if img1->channels != 4 goto .ChannelError
    bne   t2, t0, .ChannelError   # if img2->channels != 4 goto .ChannelError

    # more error checks if deemed necessary
    addi sp, sp, -48
    sw s0, 0(sp)
    sw s1, 4(sp)
    sw s2, 8(sp)
    sw s3, 12(sp)
    sw s4, 16(sp)
    sw s5, 20(sp)
    sw s6, 24(sp)
    sw s7, 28(sp)
    sw s8, 32(sp)
    sw s9, 36(sp)
    sw s10, 40(sp)
    sw s11, 44(sp)


    # Initialize blended image
    lw      s11,4(a1)    #s11 = img1.height
    lw      s3,8(a1)    #s3 = img1.width
    li      s4,4        #s4=img1.channels =4
    sw      s11,4(a0)    #t1 = blended.height=img1.height
    sw      s3,8(a0)    #t2 = blended.width=img1.width
    sw      s4,12(a0)    #t3 = blended.channels=4
    lw      s8,0(a2)    #img2.data ->s8
    li      s5,256
    lw      s0,0(a0)   #s0=blended.data
    lw      s10,0(a1)    #t5=img1.data
    j       .L20


.L20:
    addi t1,x0,0 #t1=y=0
    j .L21

.L24:
    addi t2,x0,0 #t2=x=0
    j       .L22

.L23:
    add     t4,s8,t3    #t4=first + img2.data
    lw      t5,0(t4)    #t5=*(img2.data+first)
    srli    t5, t5 ,24  #t5=img2.data[first+3]<-alpha value
    mul     t4,t5,a4    #t4=alpha_combined=img2.data[first+3]*alpha
    srli    t4,t4,8     #t4=alpha_combined<<8

    add     t5,s10,t3    #t5=first + img1.data
    add     s1,s8,t3    #t5=first + img2.data
    lw      t6,0(t5)    #t5=img1.data[first+3]<<24 | img1.data[first+2]<<16 | img1.data[first+1]<<8 | img1.data[first]->value1
    lw      s1,0(s1)    #s6=img2.data[first+3]<<24 | img2.data[first+2]<<16 | img2.data[first+1]<<8 | img2.data[first]->value2
    srli    a6, t6 ,24  #a6=img1.data[first+3]
    svunpack s2,t6     #t5=vunpack(value1) -> unpack_one
    svunpack s7,s1      #s7=vunpack(value2) -> unpack_two
    sub      s9,s5,t4   #s9=(1<<8)-unpack_one
    svbrdcst t0,s9      #t0=vbrdcst(((1<<8)-alpha_combined)) -> unpack_alpha_one
    svbrdcst t6,t4      #t6=vbrdcst((alpha_combined)) -> unpack_alpha_two
    add     t5,s0,t3    #t5=first + blended.data
    svmul     t0,t0,s2 #t0=vmul(unpack_one,unpack_alpha_one) -> unpack_one_mul
    svmul     s1,t6,s7  #t6=vmul(unpack_one,unpack_alpha_two) -> unpack_two_mul
    svadd     s2,s1,t0  #s2=vadd(unpack_one_mul,unpack_two_mul) -> added
    svpack    t0,s2,a6  #t0=vpack(added,img1.data[first+3]) -> result
    sw      t0,0(t5)    #store result in right place in blended.data
    addi    t2,t2,1     #x++
    addi    t3,t3,4

.L22:
    blt     t2,s3,.L23 #t2=x t2=x<img1.width
    addi    t1,t1,1     #t1=t1+1 -> y++

.L21:
    mul     s6,s3,t1    #s6=y*img1.width
    mul     s6,s6,s4
    add     t3,s6,x0
    #li t4,3
    #blt     t1,t4,.L24
    #ebreak
     blt     t1,s11,.L24 #if t1=y<img1.height
     lw s0, 0(sp)
     lw s1, 4(sp)
     lw s2, 8(sp)
     lw s3, 12(sp)
     lw s4, 16(sp)
     lw s5, 20(sp)
     lw s6, 24(sp)
     lw s7, 28(sp)
     lw s8, 32(sp)
     lw s9, 36(sp)
     lw s10, 40(sp)
     lw s11, 44(sp)
     addi sp, sp, 48
     mv a0,x0
     ret


.OverlayError:
    li    a0, -1
    ret

.ChannelError:
    li    a0, -2
    ret

