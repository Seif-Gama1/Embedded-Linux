/* extern the "_start" so that linker can see it ... otherwise it'd be treated as private function */
.section ".text.boot"
.global _start
.extern __bss_start
.extern __bss_end
.extern seif

/* Label similar to function */
_start:
    /* setup stack */
    ldr x0, =_stack_top
    mov sp, x0

    /* clear BSS */
    ldr x1, =__bss_start
    ldr x2, =__bss_end

bss_loop:
    cmp x1, x2
    b.ge call_main
    str xzr, [x1], #8
    b bss_loop

call_main:
    bl seif

hang:
    b hang

/* personal note: test this while(1) instead */
/*
. :
    b .
*/