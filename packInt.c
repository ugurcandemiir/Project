#include "packInt.h"
#include <assert.h>

void putField(long value,int nBits,int offset,long store[]);
int getField(int offset,int nBits,long store[],int sprop);

void putInt(int value,long store[]) {
    int index=store[0]; // Offset in bits
    assert(index>=0); // Error if called after getInt
    putField(value,11,index*11,store);
    store[0]=index+1;
}

int storeUsed(long store[]) {
    int index=store[0];
    assert(index>=0); // Error if called after getInt
    return 1+(index*11)/64;
}

int getInt(long store[]) {
    int index=store[0];
    assert(index!=0);
    if (index>0) { index=0; } // Special case for first time!
    int value=getField(-index*11,11,store,1);
    store[0]=index-1;
    return value;
}

void putField(long value,int nBits,int offset,long store[]) {
    unsigned long mask=(1<<nBits)-1;
    value &= mask; // Turn off high order bits in value
    int idn=1+offset/64;
    int bit=offset%64;
    if (bit>(64-nBits)) { // Not enough room in current word
        int fit=64-bit;
        int ovfl=nBits-fit;
        unsigned long vovfl = value & ((1L<<ovfl)-1); // Zero out non-overflow bits
        unsigned long vfit = value>>ovfl; // Shift out overflow bits
        store[idn] |= vfit;
        vovfl <<= 64-ovfl;
        store[idn+1] = 0 | vovfl;
        return;
    }
    // Get here if everything fits in the current word
    mask <<= 64-(bit+nBits); // Shift mask into correct position
    store[idn]&=~mask; // Turn off bits under mask
    value <<= (64-(bit+nBits));
    store[idn]|=value;
}

int getField(int offset,int nBits,long store[],int sprop) {
    unsigned long value=0;
    int idn=1+offset/64;
    int bit=offset%64;
    if (bit>(64-nBits)) { // field doesn't fit in a single word
        int fit=64-bit;
        int ovfl=nBits-fit;
        value=store[idn] & ((1<<fit)-1); // Zero out all but last bits
        value<<=ovfl; // Shift to the right
        unsigned long mask=(1<<ovfl)-1; // Pick out ovfl bits
        mask <<=64-ovfl; // But the leftmost bits
        unsigned long value2=store[idn+1]&mask;
        value2 >>=64-ovfl; // Shift back to rightmost positions
        // Note... needs to be unsigned to avoid propagating an invalid sign bit!!!
        value |= value2;
    } else { // field fits in a single word
        unsigned long mask=(1<<nBits)-1;
        value = store[idn] & (mask<<(64-(bit+nBits)));
        value>>=64-(bit+nBits);
    }
    if (sprop) {
        //If the high order bit is on, propagate the sign bit
        unsigned long sb=1<<(nBits-1);
        unsigned long nprop=~((1<<nBits)-1);
        if (value & sb) value |=nprop;
    }
    return value; // C will truncate from long to int for me
}
