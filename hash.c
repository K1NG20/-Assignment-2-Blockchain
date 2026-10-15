#include "hash.h"

unsigned char* SSHA(const unsigned char* msg, size_t length) {
    unsigned char A, B, C, D, E; //Initial Seed Value
    A = 56;
    B = 99;
    C = 102;
    D = 67;
    E = 76;

    for (int i = 0; i < length; i++) {
        for (int round = 0; round < 8; round++) {
            //unsigned char g = (B & C) | (C & D);
            unsigned char old_A = A;
            unsigned char old_B = B;
            unsigned char old_C = C;
            unsigned char old_D = D;
            unsigned char old_E = E;

            A = old_E;
            B = old_A;
            C = ((old_A >> 2) ^ (old_B >> 1)) + old_E;
            D = (old_B & old_C) | (old_D & old_C);
            E = D + old_B + msg[i];
            
        }
    }
    unsigned char* digest = (unsigned char*)malloc(DIGEST_SIZE * sizeof(unsigned char));
    digest[0] = A;
    digest[1] = B;
    digest[2] = C;
    digest[3] = D;
    digest[4] = E;
    return digest;
}

#include <stddef.h>
#include <stdlib.h>

unsigned char* SSHA2(const unsigned char* msg, size_t lenght)
{
    if (msg == NULL && lenght > 0) {
        return NULL;
    }

    unsigned char A = 56;
    unsigned char B = 99;
    unsigned char C = 102;
    unsigned char D = 67;
    unsigned char E = 76;

    for (size_t i = 0; i < lenght; i++) {
        for (int round = 0; round < 8; round++) {

            unsigned char shiftA = A >> 2;
            unsigned char shiftB = B >> 1;

            unsigned char and1 = B & C;
            unsigned char and2 = C & D;
            unsigned char orResult = and1 | and2;

            unsigned char newA = E;
            unsigned char newB = A;
            unsigned char newC = (unsigned char)(shiftA + E);
            unsigned char newD = shiftA ^ shiftB;
            unsigned char newE =
                (unsigned char)(shiftB + orResult + msg[i]);

            A = newA;
            B = newB;
            C = newC;
            D = newD;
            E = newE;
        }
    }

    unsigned char* hash = malloc(5);

    if (hash == NULL) {
        return NULL;
    }

    hash[0] = A;
    hash[1] = B;
    hash[2] = C;
    hash[3] = D;
    hash[4] = E;

    return hash;
}

int digest_equal(struct Digest digest1, struct Digest digest2) {
    return ((digest1.hash0 == digest2.hash0) &&
        (digest1.hash1 == digest2.hash1) &&
        (digest1.hash2 == digest2.hash2) &&
        (digest1.hash3 == digest2.hash3) &&
        (digest1.hash4 == digest2.hash4));
}

void printDigest(struct Digest digest) {
    printf("%d %d %d %d %d\n", digest.hash0, digest.hash1, digest.hash2, digest.hash3, digest.hash4);
}

