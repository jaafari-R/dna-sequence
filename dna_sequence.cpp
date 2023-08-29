#include "dna_sequence.hpp"

#include <iostream>

/* ----- DNASequence Utility Functions ----- */

/*
    * Returns true if the sequence is valid, returns false otherwise.
    * A sequence is valid if it contains only the characters ['a', 'A', 't', 'T', 'g', 'G', 'c', 'C'].
*/
bool verifySequence(const std::string &sequence) {
    for(char nucleotide: sequence) {
        switch(nucleotide) {
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

    /* Check if the DNA Sequence is valid*/
    if(verifySequence(sequence) == false) {
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

DNASequence::~DNASequence() {
    if(m_sequence != nullptr)
        delete[] m_sequence;
}
