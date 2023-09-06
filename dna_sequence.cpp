#include "dna_sequence.hpp"

#include <iostream>

/* ----- DNASequence Utility Functions ----- */

/*
    * Returns true if the sequence is valid, returns false otherwise.
    * A sequence is valid if it contains only the characters ['a', 'A', 't', 'T', 'g', 'G', 'c', 'C'].
*/
bool verifySequence(const char *sequence, size_t length) {
    while(length--) {
        switch(*sequence) {
            case 'a':
            case 'A':
            case 't':
            case 'T':
            case 'g':
            case 'G':
            case 'c':
            case 'C':
                break;
            default:
                return false;
        }
        ++sequence;
    }
    return true;
}


/*
    * hashes 4 nucleotides into 1 character from left to right
    * 'A' or 'a' become '00' in binary
    * 'T' or 't' become '01' in binary
    * 'G' or 'g' become '10' in binary
    * 'C' or 'c' become '11' in binary
*/
char hashNucleotides(const char *patch, size_t len = 4) {
    char hash = 0;

    for(size_t i = 0; i < len; ++i) {
        switch(*patch) {
            // case 'A':
            // case 'a':
                // hash += 6 - i << 0;
                // break;
            case 'T':
            case 't':
                hash += 1 << (6 - i*2);
                break;
            case 'G':
            case 'g':
                hash += 2 << (6 - i*2);
                break;
            case 'C':
            case 'c':
                hash += 3 << (6 - i*2);
                break;            
        }
        ++patch;
    }
    return hash;
}

/*

*/
void fillSequence(std::unique_ptr<char> &sequence, const char *sequence_string, size_t size) {
    char *seq_ptr;
    
    /* Initialize DNA Sequence size and allocate memory for the sequence */
    sequence = std::unique_ptr<char>(new char[(size + 3) / 4]);
    seq_ptr = sequence.get();

    /* Copy and Compress DNA Sequence */
    for(; size > 3; size -= 4) {
        *seq_ptr = hashNucleotides(sequence_string);
        ++seq_ptr;
        sequence_string += 4;
    }

    /* Check if we need nucleotides with padding at the end add them */
    if(size > 0)
        *seq_ptr = hashNucleotides(sequence_string, size);
}

/* ---------- DNASequence Methods ---------- */

DNASequence::DNASequence() {
    this->m_sequence = nullptr;
    this->m_size = 0;
}


DNASequence::DNASequence(const std::string &sequence) {
    /* Check if the DNA Sequence is valid */
    if(verifySequence(&sequence[0], sequence.size()) == false) {
        printf("DNASequence Error: the provided sequence string has an invalid Nucleotide value!\n");
        this->m_size = 0;
        this->m_sequence = nullptr;
        return;
    }

    /* Fill in the sequence with Nuclutides and set its size */
    fillSequence(this->m_sequence, &sequence[0], sequence.size());
    this->m_size = sequence.size();
}


DNASequence::DNASequence(const char* sequence, size_t size = -1) {
    const char *seq_ptr;

    /* Get the sequence size */
    if(size == -1) {
        size = 0;
        seq_ptr = sequence;
        while(*seq_ptr != '\0') {
            ++size;
            ++seq_ptr;
        }
    }

    /* Check if the DNA Sequence is valid */
    if(verifySequence(sequence, size) == false) {
        printf("DNASequence Error: the provided sequence string has an invalid Nucleotide value!\n");
        this->m_size = 0;
        this->m_sequence = nullptr;
        return;
    }

    /* Fill in the sequence with Nuclutides and set its size */
    fillSequence(this->m_sequence, sequence, size);
    this->m_size = size;
}


DNASequence::DNASequence(const DNASequence &sequence) {
    size_t seq_size = (sequence.m_size + 3) / 4;

    this->m_size = sequence.m_size;
    this->m_sequence = std::unique_ptr<char>(new char[seq_size]);

    char *copy_seq_ptr = sequence.m_sequence.get();
    char *seq_ptr = this->m_sequence.get();

    for(size_t i = 0; i < seq_size; ++i) {
        *seq_ptr = *copy_seq_ptr;
        ++seq_ptr;
        ++copy_seq_ptr;
    }
}


DNASequence::~DNASequence() {}

DNASequence DNASequence::pairSequence() {
    DNASequence pair_sequence(*this);

    char *seq_ptr = pair_sequence.m_sequence.get();
    size_t seq_end = (pair_sequence.m_size + 3) / 4;
    
    for(size_t i = 0; i < seq_end; ++i) {
        *seq_ptr ^= 85;
        ++seq_ptr;
    }

    return pair_sequence;
}


/* -- Getters -- */

size_t DNASequence::getSize() {
    return this->m_size;
}

