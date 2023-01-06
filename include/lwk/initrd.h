#ifndef _LWK_INITRD_H
#define _LWK_INITRD_H

int
initrd_is_initrd(paddr_t initrd_start,
                 paddr_t initrd_end);


uint8_t * 
unpack_initrd(paddr_t initrd_start,
              paddr_t initrd_end);



#endif