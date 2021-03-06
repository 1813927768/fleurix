#ifndef VM_H
#define VM_H

#include <file.h>

/* each vma asscociated with a file descripter, on page fault raised
 * do what it deserves. */
struct vma {
    uint            v_flag;
    uint            v_base; // must be one page aligned
    uint            v_size; // must be one page aligned
    struct inode   *v_ino;  // inode
    uint            v_ioff; // keep block aligned
};

#define VMA_RDONLY  0x1  // read only
#define VMA_STACK   0x2  // this vma indicates a stack, which grows downwards.
#define VMA_ZERO    0x4  // demand-zero
#define VMA_MMAP    0x8  // mapped from a file
#define VMA_PRIVATE 0x10 // Copy On Write

/*
 * each proc got one struct vm, which indicated it's page directory
 * and misc on address space.
 * */
struct vm {
    struct pde  *vm_pgd;
    uint         vm_entry;
    struct vma   vm_area[0];  // trick here, treat the fields downblow as an array.
    struct vma   vm_text;
    struct vma   vm_data;
    struct vma   vm_bss;
    struct vma   vm_heap;
    struct vma   vm_stack;
};

#define NVMA 5

#define VM_STACK 0x80000000 /* 2gb */

/*
 * proc0's page directory, initialize the kernel's address space here.
 * */
extern struct pde pgd0[];

#endif
