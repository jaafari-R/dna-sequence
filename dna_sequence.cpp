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

    for(int i = 0; i < len; ++i) {
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

/* ---------- DNASequence Methods ---------- */

DNASequence::DNASequence() {
    this->m_sequence = nullptr;
    this->m_size = 0;
}


DNASequence::DNASequence(const std::string sequence) {
    char *seq_ptr;
    size_t i;

    /* Check if the DNA Sequence is valid */
    if(verifySequence(&sequence[0], sequence.size()) == false) {
        printf("DNASequence Error: the provided sequence string has an invalid Nucleotide value!\n");
        this->m_size = 0;
        this->m_sequence = nullptr;
        return;
    }

    /* Initialize DNA Sequence size and allocate memory for the sequence */
    this->m_size = sequence.size();
    this->m_sequence = new char[this->m_size / 4 + (this->m_size % 4 == 0 ? 0 : 1)];
    seq_ptr = this->m_sequence;

    /* Copy and Compress DNA Sequence */
    for(i = 4; i <= this->m_size; i += 4) {
        *seq_ptr = hashNucleotides(&sequence[i-4]);
        ++seq_ptr;
    }

    /* Check if we need nucleotides with padding at the end add them */
    i -= 4;
    if(i != this->m_size)
        *seq_ptr = hashNucleotides(&sequence[i], this->m_size - i + 1);
}


DNASequence::DNASequence(const char* sequence, const size_t size) {
    char *seq_ptr;
    size_t i;
    size_t size = 0;

    /* Get the sequence size */
    seq_ptr = sequence;
    while(*seq_ptr != '\0') {
        ++size;
        ++seq_ptr;
    }

    /* Check if the DNA Sequence is valid */
    if(verifySequence(sequence, size) == false) {
        printf("DNASequence Error: the provided sequence string has an invalid Nucleotide value!\n");
        this->m_size = 0;
        this->m_sequence = nullptr;
        return;
    }

    /* Initialize DNA Sequence size and allocate memory for the sequence */
    this->m_size = size;
    this->m_sequence = new char[size / 4 + (size % 4 == 0 ? 0 : 1)];
    seq_ptr = this->m_sequence;

    /* Copy and Compress DNA Sequence */
    for(; size > 3; size -= 4) {
        *seq_ptr = hashNucleotides(sequence);
        ++seq_ptr;
        sequence += 4;
    }

    /* Check if we need nucleotides with padding at the end add them */
    if(size > 0)
        *seq_ptr = hashNucleotides(sequence, size);
}


DNASequence::~DNASequence() {
    if(m_sequence != nullptr)
        delete[] m_sequence;
}
