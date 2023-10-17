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
    * compresses 4 nucleotides into 1 character from left to right
    * 'A' or 'a' become '00' in binary
    * 'T' or 't' become '01' in binary
    * 'G' or 'g' become '10' in binary
    * 'C' or 'c' become '11' in binary
*/
char compressNucleotides(const char *patch, size_t len = 4) {
    char compressed = 0;

    for(size_t i = 0; i < len; ++i) {
        switch(*patch) {
            // case 'A':
            // case 'a':
                // hash += 6 - i << 0;
                // break;
            case 'T':
            case 't':
                compressed += 1 << (6 - i*2);
                break;
            case 'G':
            case 'g':
                compressed += 2 << (6 - i*2);
                break;
            case 'C':
            case 'c':
                compressed += 3 << (6 - i*2);
                break;            
        }
        ++patch;
    }
    return compressed;
}

/*
    * Decompresses a patch of up to 4 Nucleotides from 1 char to a string
    * '00' becomes 'A'
    * '01' becomes 'T'
    * '10' becomes 'G'
    * '11' becomes 'C'
    * Example: 0b00011011 becomes "ATGC"
*/
std::string decompressNucleotides(const char compressed, size_t len = 4) {
    std::string decompressed(len, ' ');
    unsigned char offset = 6;
    char value;

    for(size_t i = 0; i < len; ++i) {
        value = (compressed >> offset) & 0b11;
        offset -= 2;

        switch(value) {
            case 0b00:
                decompressed[i] = 'A';
                break;
            case 0b01:
                decompressed[i] = 'T';
                break;
            case 0b10:
                decompressed[i] = 'G';
                break;
            case 0b11:
                decompressed[i] = 'C';
                break;
        }
    }
    return decompressed;
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
        *seq_ptr = compressNucleotides(sequence_string);
        ++seq_ptr;
        sequence_string += 4;
    }

    /* Check if we need nucleotides with padding at the end add them */
    if(size > 0)
        *seq_ptr = compressNucleotides(sequence_string, size);
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


void DNASequence::reverseSequence(size_t start, size_t end) {
    if(start >= this->m_size)
        return;

    char *sequence = this->m_sequence.get();
    size_t pos_start, pos_end, offset_start, offset_end;
    char start_val, end_val;

    /* make sure end points to the last specified element in the reversed subsequence */
    end = (end > this->m_size ? this->m_size : end) - 1;

    for(; start < end; ++start, --end) {
        pos_start = start / 4;
        pos_end = end / 4;
        offset_start = 6 - (start % 4) * 2;
        offset_end = 6 - (end % 4) * 2;

        start_val = (sequence[pos_start] >> offset_start) & 0b11;
        end_val = (sequence[pos_end] >> offset_end) &0b11;

        start_val ^= end_val;
        end_val ^= start_val;
        start_val ^= end_val;

        sequence[pos_start] = (sequence[pos_start] & (0b11111111 ^ (0b11 << offset_start))) | (start_val << offset_start);
        sequence[pos_end] = (sequence[pos_end] & (0b11111111 ^ (0b11 << offset_end))) | (end_val << offset_end);
    }
}


DNASequence DNASequence::slice(size_t start, size_t end) {
    std::string seq_slice;
    size_t i;
    const char *sequence = this->m_sequence.get();

    end = (end >= this->m_size ? this->m_size : end) - 1;

    if(start >= end) {
        return DNASequence();
    }

    i = start / 4;
    if(start % 4) {
        seq_slice.append(decompressNucleotides(sequence[i] << ((start % 4) * 2), 4 - start % 4));
        start += 4 - start % 4;
        ++i;
    }

    for(size_t loop_end = end - 3; start < loop_end; start += 4, i) {
        seq_slice.append(decompressNucleotides(sequence[i++]));
    }

    if(start != end) {
        seq_slice.append(decompressNucleotides(sequence[i], end + 1 - start));
    }

    return DNASequence(seq_slice);
}


bool DNASequence::matchSubsequence(const char* subsequence, size_t size, size_t start_index) {
    // passed subsequence size is longer than the sequence slice length starting at start_index
    if(this->m_size - start_index < size)
        return false;
    
    for(size_t subseq_end = start_index + size; start_index < subseq_end; ++start_index) {
        char nucleotide = *(subsequence++);
        // Get upper case nucleotides
        switch(nucleotide) {
            case 'a':
                nucleotide = 'A';
                break;
            case 't':
                nucleotide = 'T';
                break;
            case 'c':
                nucleotide = 'C';
                break;
            case 'g':
                nucleotide = 'G';
                break;
        }

        // Compare
        if((*this)[start_index] != nucleotide)
            return false;
    }
    return true;
}


bool DNASequence::matchSubsequence(const std::string &subsequence, size_t start_index) {
    return matchSubsequence(&subsequence[0], subsequence.size(), start_index);
}


std::vector<size_t> DNASequence::findSubsequence(const char* subsequence, const size_t size, size_t n) {
    std::vector<size_t> subsequence_occurances;

    for(size_t subseq_start = 0, loop_end = this->m_size + 1 - size; subseq_start < loop_end && n; ++subseq_start) {
        if(matchSubsequence(subsequence, size, subseq_start)) {
            subsequence_occurances.push_back(subseq_start);
            --n;
        }
    }

    return subsequence_occurances;
}


std::vector<size_t> DNASequence::findSubsequence(const std::string &subsequence, size_t n) {
    return findSubsequence(&subsequence[0], subsequence.size(), n);
}


size_t DNASequence::countSubsequence(const char* subsequence, size_t size) {
    return findSubsequence(subsequence, size).size();
}


size_t DNASequence::countSubsequence(const std::string &subsequence) {
    return findSubsequence(subsequence).size();
}


bool DNASequence::hasSubsequence(const std::string &subsequence) {
    return findSubsequence(subsequence, 1).size() == 1;
}


bool DNASequence::hasSubsequence(const char* subsequence, size_t size) {
    return findSubsequence(subsequence, size, 1).size() == 1;
}


size_t DNASequence::findNthSubsequence(const std::string &subsequence, size_t n) {
    return findSubsequence(subsequence, n).back();
}


size_t DNASequence::findNthSubsequence(const char* subsequence, size_t size, size_t n) {
    return findSubsequence(subsequence, n).back();
}

/* -- Operators -- */

char DNASequence::operator[](size_t index) {
    if(index >= this->m_size)
        return '-';

    char val = '-';
    size_t pos = index % 4;
    index /= 4;


    switch((this->m_sequence.get()[index] >> (6 - pos * 2)) & 3) {
        case 0:
            val = 'A';
            break;
        case 1:
            val = 'T';
            break;
        case 2:
            val = 'G';
            break;
        case 3:
            val = 'C';
            break;
    }

    return val;
}


/* -- Getters -- */

size_t DNASequence::getSize() {
    return this->m_size;
}

std::string DNASequence::getSequenceStr() {
    std::string sequence_str(this->m_size, '\0');
    size_t size = this->m_size;
    char *seq_ptr = this->m_sequence.get();
    size_t i, loop_end;


    for(i = 0, loop_end = size - 3; i < loop_end; i += 4) {
        sequence_str.replace(i, 4, decompressNucleotides(*seq_ptr));
        ++seq_ptr;
    }
    if(i != size)
        sequence_str.replace(i, size - i, decompressNucleotides(*seq_ptr, size - i));

    return sequence_str;
}

char* DNASequence::getSequenceCStr() {
    char *sequence_str =  new char[this->m_size + 1];

    size_t size = this->m_size;
    std::string nucleotides_patch(4, ' ');
    char *seq_ptr = this->m_sequence.get();
    size_t i, j, loop_end;

    for(i = 0, loop_end = size - 3; i < loop_end;) {
        nucleotides_patch.replace(0, 4, decompressNucleotides(*seq_ptr));
        for(j = 0; j < 4; ++j, ++i)
            sequence_str[i] = nucleotides_patch[j];
        ++seq_ptr;
    }
    if(i != size) {
        nucleotides_patch = decompressNucleotides(*seq_ptr, size - i);
        for(j = 0; i < size; ++j, ++i)
            sequence_str[i] = nucleotides_patch[j];
    }
    sequence_str[this->m_size] = '\0';

    return sequence_str;
}
