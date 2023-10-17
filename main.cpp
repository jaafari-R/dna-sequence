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
    char* cs = dna_seq4.getSequenceCStr();
    std::cout << s << std::endl;
    std::cout << cs << std::endl;
    dna_seq4.reverseSequence();
    s = dna_seq4.getSequenceStr();
    cs = dna_seq4.getSequenceCStr();
    std::cout << s << std::endl;
    std::cout << cs<< std::endl;
    std::cout << dna_seq4.pairSequence().getSequenceStr() << std::endl;
    std::cout << dna_seq4.pairSequence().getSequenceCStr() << std::endl;

    // slice test
    DNASequence inc_seq("aatttccccggggg");
    DNASequence inc_seq_slice = inc_seq.slice(3, 11);
    std::cout << inc_seq_slice.getSequenceStr() << std::endl;

    // findSubsequence & countSubsequence test
    DNASequence find_seq1("aaaaaa");
    std::cout << "Found 'aaaaa' at: ";
    for(auto subseq_start: find_seq1.findSubsequence("aaaaa"))
        std::cout << subseq_start << "  ";
    std::cout << std::endl;
    std::cout << "'aaaaa' has occured " << find_seq1.countSubsequence("aaaaa") << " times." << std::endl;
    std::cout << "Found 'tt' at: ";
    for(auto subseq_start: find_seq1.findSubsequence("tt"))
        std::cout << subseq_start << "  ";
    std::cout << std::endl;

    DNASequence find_seq2("actgggtcgtacggt");
    std::cout << "Found 'cgt' at: ";
    for(auto subseq_start: find_seq2.findSubsequence("cgt"))
        std::cout << subseq_start << "  ";
    std::cout << std::endl;
    std::cout << "Found 'ggt' at: ";
    for(auto subseq_start: find_seq2.findSubsequence("ggt"))
        std::cout << subseq_start << "  ";
    std::cout << std::endl;

    DNASequence find_seq3("gatgcatatatatatatatttat");
    std::cout << "Found the first 3 'at' at: ";
    for(auto subseq_start: find_seq3.findSubsequence(std::string("at"), 3))
        std::cout << subseq_start << "  ";
    std::cout << std::endl;    

    return 0;
}