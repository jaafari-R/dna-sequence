

#ifndef DNA_SEQUENCE
#define DNA_SEQUENCE

#include <string>
#include <memory>

/*  
    * This class is a representation of a DNA Sequence,
    * A DNA Sequence is a sequence of Nucleotides each 
     Nucleotide can have one of the following values: A, T, G, C.
    * The DNA Sequence is stored in the heap memory, and is deleted when the DNASequence
     destructor is called.
*/
class DNASequence {
public:
    /* Create an empty DNA Sequence. */
    DNASequence();

    /* 
        * Create a DNA Sequence that equals the values presented in the string.
        * If the DNA Sequence has a character other than 'a', 't', 'g', 'c', 'A', 'T', 'G', 'C'
        * the created sequence will be empty and an error message will be printed/output
    */
    DNASequence(const std::string &sequence);
    
    /* 
        * Create a DNA Sequence that equals the values presented in the c string.
        * If the size is not provided, the c string must end with a string termination character ('\0' or 0).
        * If the DNA Sequence has a character other than 'a', 't', 'g', 'c', 'A', 'T', 'G', 'C'.
        * The created sequence will be empty and an error message will be printed/output.
    */
    DNASequence(const char* sequence, const size_t size);
    
    DNASequence(const DNASequence &sequence);

    /* Clears the DNA Sequence from the memory */
    ~DNASequence();

    /* 
        * Creates and Returns the pair sequence
        * In a Pair Sequence, each Nucleutide is replaced with its pair:
            A is replaced with T
            T is replaced with A
            G is replaced with C
            C is replaced with G
    */
    DNASequence pairSequence();

    /*
        * Reverses the sequence in the range [start, end)
           'end' is not included, the length of the reversed value is 
           end - start.
        * The sequence is 0-indexed.
        * If only 'start' was given (end == -1) or 'end' was bigger than the sequence size,
           then the sequence is reversed from 'start' to the end of the sequence.
        * If 'start' was not set (start == 0), then the entire sequence is reversed.
        * If 'start was set to a value bigger or equal to the the sequence length, then nothing happens
    */
    void reverseSequence(size_t start = 0, size_t end = -1);

    /* getters */
    size_t getSize();

private:
    std::unique_ptr<char> m_sequence;
    size_t m_size;
};

#endif