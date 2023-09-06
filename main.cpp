#include "dna_sequence.hpp"
#include <iostream>

int main() {
    const char *cstr1 = "atgc";
    const char *cstr2 = "";

    DNASequence dna_seq_cs1(cstr1);
    DNASequence dna_seq_cs2(cstr2);

    DNASequence dna_seq;
    DNASequence dna_seq2("ttttt");
    DNASequence dna_seq3("aaaaq");

    DNASequence dna_seq_copy1(dna_seq_cs1);
    DNASequence dna_seq_copy2(dna_seq2);
    DNASequence dna_seq_copy3(dna_seq);

    return 0;
}