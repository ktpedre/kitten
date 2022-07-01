#include <lwk/bitops.h>
#include <lwk/spinlock.h>

raw_spinlock_t __atomic_hash[ATOMIC_HASH_SIZE];
