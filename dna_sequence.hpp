#ifndef DNA_SEQUENCE
#define DNA_SEQUENCE

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
    DNASequence(const string &sequence);
    
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
private:
    
};

#endif