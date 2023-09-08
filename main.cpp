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
    DNASequence dna_seq4("aaaatcgtttttgggggccccctctctga");

    DNASequence dna_seq_copy1(dna_seq_cs1);
    DNASequence dna_seq_copy2(dna_seq2);
    DNASequence dna_seq_copy3(dna_seq);

    DNASequence seq_pair_2 = dna_seq2.pairSequence();
    DNASequence seq_pair_cp = seq_pair_2.pairSequence();

    std::string s = dna_seq2.getSequenceStr();
    std::cout << s << std::endl;

    dna_seq2.reverseSequence();
    s = dna_seq2.getSequenceStr();
    std::cout << s << std::endl;

    s = seq_pair_2.getSequenceStr();
    std::cout << s << std::endl;

    s = dna_seq_cs1.getSequenceStr();
    std::cout << s << std::endl;

    dna_seq_cs1.reverseSequence();
    s = dna_seq_cs1.getSequenceStr();
    std::cout << s << std::endl;

    s = dna_seq4.getSequenceStr();
    std::cout << s << std::endl;
    dna_seq4.reverseSequence();
    s = dna_seq4.getSequenceStr();
    std::cout << s << std::endl;
    std::cout << dna_seq4.pairSequence().getSequenceStr() << std::endl;

    return 0;
}